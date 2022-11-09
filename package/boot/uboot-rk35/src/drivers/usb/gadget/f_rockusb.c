/*
 * Copyright 2017 Rockchip Electronics Co., Ltd
 * Frank Wang <frank.wang@rock-chips.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <asm/io.h>
#include <android_avb/avb_ops_user.h>
#include <android_avb/rk_avb_ops_user.h>
#include <asm/arch-rockchip/boot_mode.h>
#include <asm/arch-rockchip/chip_info.h>
#include <asm/arch-rockchip/rk_atags.h>
#include <write_keybox.h>
#include <linux/mtd/mtd.h>
#include <optee_include/OpteeClientInterface.h>

#ifdef CONFIG_ROCKCHIP_VENDOR_PARTITION
#include <asm/arch-rockchip/vendor.h>
#endif
#include <rockusb.h>

#define ROCKUSB_INTERFACE_CLASS	0xff
#define ROCKUSB_INTERFACE_SUB_CLASS	0x06
#define ROCKUSB_INTERFACE_PROTOCOL	0x05

#define ROCKCHIP_FLASH_BLOCK_SIZE	1024
#define ROCKCHIP_FLASH_PAGE_SIZE	4

static struct usb_interface_descriptor rkusb_intf_desc = {
	.bLength		= USB_DT_INTERFACE_SIZE,
	.bDescriptorType	= USB_DT_INTERFACE,
	.bInterfaceNumber	= 0x00,
	.bAlternateSetting	= 0x00,
	.bNumEndpoints		= 0x02,
	.bInterfaceClass	= ROCKUSB_INTERFACE_CLASS,
	.bInterfaceSubClass	= ROCKUSB_INTERFACE_SUB_CLASS,
	.bInterfaceProtocol	= ROCKUSB_INTERFACE_PROTOCOL,
};

static struct usb_descriptor_header *rkusb_fs_function[] = {
	(struct usb_descriptor_header *)&rkusb_intf_desc,
	(struct usb_descriptor_header *)&fsg_fs_bulk_in_desc,
	(struct usb_descriptor_header *)&fsg_fs_bulk_out_desc,
	NULL,
};

static struct usb_descriptor_header *rkusb_hs_function[] = {
	(struct usb_descriptor_header *)&rkusb_intf_desc,
	(struct usb_descriptor_header *)&fsg_hs_bulk_in_desc,
	(struct usb_descriptor_header *)&fsg_hs_bulk_out_desc,
	NULL,
};

static struct usb_descriptor_header *rkusb_ss_function[] = {
	(struct usb_descriptor_header *)&rkusb_intf_desc,
	(struct usb_descriptor_header *)&fsg_ss_bulk_in_desc,
	(struct usb_descriptor_header *)&fsg_ss_bulk_in_comp_desc,
	(struct usb_descriptor_header *)&fsg_ss_bulk_out_desc,
	(struct usb_descriptor_header *)&fsg_ss_bulk_out_comp_desc,
	NULL,
};

struct rk_flash_info {
	u32	flash_size;
	u16	block_size;
	u8	page_size;
	u8	ecc_bits;
	u8	access_time;
	u8	manufacturer;
	u8	flash_mask;
} __packed;

static int rkusb_rst_code; /* The subcode in reset command (0xFF) */

int g_dnl_bind_fixup(struct usb_device_descriptor *dev, const char *name)
{
	if (IS_RKUSB_UMS_DNL(name)) {
		/* Fix to Rockchip's VID and PID */
		dev->idVendor  = __constant_cpu_to_le16(0x2207);
		dev->idProduct = __constant_cpu_to_le16(CONFIG_ROCKUSB_G_DNL_PID);

		/* Enumerate as a loader device */
#if defined(CONFIG_SUPPORT_USBPLUG)
		dev->bcdUSB = cpu_to_le16(0x0200);
#else
		dev->bcdUSB = cpu_to_le16(0x0201);
#endif
	} else if (!strncmp(name, "usb_dnl_fastboot", 16)) {
		/* Fix to Google's VID and PID */
		dev->idVendor  = __constant_cpu_to_le16(0x18d1);
		dev->idProduct = __constant_cpu_to_le16(0xd00d);
	} else if (!strncmp(name, "usb_dnl_dfu", 11)) {
		/* Fix to Rockchip's VID and PID for DFU */
		dev->idVendor  = cpu_to_le16(0x2207);
		dev->idProduct = cpu_to_le16(0x0107);
	}

	return 0;
}

__maybe_unused
static inline void dump_cbw(struct fsg_bulk_cb_wrap *cbw)
{
	assert(!cbw);

	debug("%s:\n", __func__);
	debug("Signature %x\n", cbw->Signature);
	debug("Tag %x\n", cbw->Tag);
	debug("DataTransferLength %x\n", cbw->DataTransferLength);
	debug("Flags %x\n", cbw->Flags);
	debug("LUN %x\n", cbw->Lun);
	debug("Length %x\n", cbw->Length);
	debug("OptionCode %x\n", cbw->CDB[0]);
	debug("SubCode %x\n", cbw->CDB[1]);
	debug("SectorAddr %x\n", get_unaligned_be32(&cbw->CDB[2]));
	debug("BlkSectors %x\n\n", get_unaligned_be16(&cbw->CDB[7]));
}

static int rkusb_check_lun(struct fsg_common *common)
{
	struct fsg_lun *curlun;

	/* Check the LUN */
	if (common->lun >= 0 && common->lun < common->nluns) {
		curlun = &common->luns[common->lun];
		if (common->cmnd[0] != SC_REQUEST_SENSE) {
			curlun->sense_data = SS_NO_SENSE;
			curlun->info_valid = 0;
		}
	} else {
		curlun = NULL;
		common->bad_lun_okay = 0;

		/*
		 * INQUIRY and REQUEST SENSE commands are explicitly allowed
		 * to use unsupported LUNs; all others may not.
		 */
		if (common->cmnd[0] != SC_INQUIRY &&
		    common->cmnd[0] != SC_REQUEST_SENSE) {
			debug("unsupported LUN %d\n", common->lun);
			return -EINVAL;
		}
	}

	return 0;
}

static void __do_reset(struct usb_ep *ep, struct usb_request *req)
{
	u32 boot_flag = BOOT_NORMAL;

	if (rkusb_rst_code == 0x03)
		boot_flag = BOOT_BROM_DOWNLOAD;

	rkusb_rst_code = 0; /* restore to default */
	writel(boot_flag, (void *)CONFIG_ROCKCHIP_BOOT_MODE_REG);

	do_reset(NULL, 0, 0, NULL);
}

static int rkusb_do_reset(struct fsg_common *common,
			  struct fsg_buffhd *bh)
{
	common->data_size_from_cmnd = common->cmnd[4];
	common->residue = 0;
	bh->inreq->complete = __do_reset;
	bh->state = BUF_STATE_EMPTY;

	rkusb_rst_code = !common->cmnd[1] ? 0xff : common->cmnd[1];
	return 0;
}

static int rkusb_do_test_unit_ready(struct fsg_common *common,
				    struct fsg_buffhd *bh)
{
	common->residue = 0x06 << 24; /* Max block xfer support from host */
	common->data_dir = DATA_DIR_NONE;
	bh->state = BUF_STATE_EMPTY;

	return 0;
}

static int rkusb_do_read_flash_id(struct fsg_common *common,
				  struct fsg_buffhd *bh)
{
	u8 *buf = (u8 *)bh->buf;
	u32 len = 5;
	enum if_type type = ums[common->lun].block_dev.if_type;

	if (type == IF_TYPE_MMC)
		memcpy((void *)&buf[0], "EMMC ", 5);
	else if (type == IF_TYPE_RKNAND)
		memcpy((void *)&buf[0], "NAND ", 5);
	else
		memcpy((void *)&buf[0], "UNKN ", 5); /* unknown */

	/* Set data xfer size */
	common->residue = common->data_size_from_cmnd = len;
	common->data_size = len;

	return len;
}

static int rkusb_do_test_bad_block(struct fsg_common *common,
				   struct fsg_buffhd *bh)
{
	u8 *buf = (u8 *)bh->buf;
	u32 len = 64;

	memset((void *)&buf[0], 0, len);

	/* Set data xfer size */
	common->residue = common->data_size_from_cmnd = len;
	common->data_size = len;

	return len;
}

static int rkusb_do_read_flash_info(struct fsg_common *common,
				    struct fsg_buffhd *bh)
{
	struct blk_desc *desc = &ums[common->lun].block_dev;
	u8 *buf = (u8 *)bh->buf;
	u32 len = sizeof(struct rk_flash_info);
	struct rk_flash_info finfo = {
		.block_size = ROCKCHIP_FLASH_BLOCK_SIZE,
		.ecc_bits = 0,
		.page_size = ROCKCHIP_FLASH_PAGE_SIZE,
		.access_time = 40,
		.manufacturer = 0,
		.flash_mask = 0
	};

	finfo.flash_size = (u32)desc->lba;

	if (desc->if_type == IF_TYPE_MTD &&
	    (desc->devnum == BLK_MTD_NAND ||
	    desc->devnum == BLK_MTD_SPI_NAND)) {
		struct mtd_info *mtd = (struct mtd_info *)desc->bdev->priv;

		if (mtd) {
			finfo.block_size = mtd->erasesize >> 9;
			finfo.page_size = mtd->writesize >> 9;
		}
	}

	if (desc->if_type == IF_TYPE_MTD && desc->devnum == BLK_MTD_SPI_NOR) {
		/* RV1126/RK3308 mtd spinor keep the former upgrade mode */
#if !defined(CONFIG_ROCKCHIP_RV1126) && !defined(CONFIG_ROCKCHIP_RK3308)
		finfo.block_size = 0x100; /* Aligned to 128KB */
#else
		finfo.block_size = ROCKCHIP_FLASH_BLOCK_SIZE;
#endif
	}

	debug("Flash info: block_size= %x page_size= %x\n", finfo.block_size,
	      finfo.page_size);

	if (finfo.flash_size)
		finfo.flash_mask = 1;

	memset((void *)&buf[0], 0, len);
	memcpy((void *)&buf[0], (void *)&finfo, len);

	/* Set data xfer size */
	common->residue = common->data_size_from_cmnd = len;
        /* legacy upgrade_tool does not set correct transfer size */
	common->data_size = len;

	return len;
}

static int rkusb_do_get_chip_info(struct fsg_common *common,
				  struct fsg_buffhd *bh)
{
	u8 *buf = (u8 *)bh->buf;
	u32 len = common->data_size;
	u32 chip_info[4];

	memset((void *)chip_info, 0, sizeof(chip_info));
	rockchip_rockusb_get_chip_info(chip_info);

	memset((void *)&buf[0], 0, len);
	memcpy((void *)&buf[0], (void *)chip_info, len);

	/* Set data xfer size */
	common->residue = common->data_size_from_cmnd = len;

	return len;
}

static int rkusb_do_lba_erase(struct fsg_common *common,
			      struct fsg_buffhd *bh)
{
	struct fsg_lun *curlun = &common->luns[common->lun];
	u32 lba, amount;
	loff_t file_offset;
	int rc;

	lba = get_unaligned_be32(&common->cmnd[2]);
	if (lba >= curlun->num_sectors) {
		curlun->sense_data = SS_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE;
		rc = -EINVAL;
		goto out;
	}

	file_offset = ((loff_t) lba) << 9;
	amount = get_unaligned_be16(&common->cmnd[7]) << 9;
	if (unlikely(amount == 0)) {
		curlun->sense_data = SS_INVALID_FIELD_IN_CDB;
		rc = -EIO;
		goto out;
	}

	/* Perform the erase */
	rc = ums[common->lun].erase_sector(&ums[common->lun],
			       file_offset / SECTOR_SIZE,
			       amount / SECTOR_SIZE);
	if (!rc) {
		curlun->sense_data = SS_MEDIUM_NOT_PRESENT;
		rc = -EIO;
	}

out:
	common->data_dir = DATA_DIR_NONE;
	bh->state = BUF_STATE_EMPTY;

	return rc;
}

static int rkusb_do_erase_force(struct fsg_common *common,
				struct fsg_buffhd *bh)
{
	struct blk_desc *desc = &ums[common->lun].block_dev;
	struct fsg_lun *curlun = &common->luns[common->lun];
	u16 block_size = ROCKCHIP_FLASH_BLOCK_SIZE;
	u32 lba, amount;
	loff_t file_offset;
	int rc;

	lba = get_unaligned_be32(&common->cmnd[2]);
	if (lba >= curlun->num_sectors) {
		curlun->sense_data = SS_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE;
		rc = -EINVAL;
		goto out;
	}

	if (desc->if_type == IF_TYPE_MTD &&
	    (desc->devnum == BLK_MTD_NAND ||
	    desc->devnum == BLK_MTD_SPI_NAND)) {
		struct mtd_info *mtd = (struct mtd_info *)desc->bdev->priv;

		if (mtd)
			block_size = mtd->erasesize >> 9;
	}

	file_offset = ((loff_t)lba) * block_size;
	amount = get_unaligned_be16(&common->cmnd[7]) * block_size;

	debug("%s lba= %x, nsec= %x\n", __func__, lba,
	      (u32)get_unaligned_be16(&common->cmnd[7]));

	if (unlikely(amount == 0)) {
		curlun->sense_data = SS_INVALID_FIELD_IN_CDB;
		rc = -EIO;
		goto out;
	}

	/* Perform the erase */
	rc = ums[common->lun].erase_sector(&ums[common->lun],
					   file_offset,
					   amount);
	if (!rc) {
		curlun->sense_data = SS_MEDIUM_NOT_PRESENT;
		rc = -EIO;
	}

out:
	common->data_dir = DATA_DIR_NONE;
	bh->state = BUF_STATE_EMPTY;

	return rc;
}

#ifdef CONFIG_ROCKCHIP_VENDOR_PARTITION
static int rkusb_do_vs_write(struct fsg_common *common)
{
	struct fsg_lun		*curlun = &common->luns[common->lun];
	u16			type = get_unaligned_be16(&common->cmnd[4]);
	struct vendor_item	*vhead;
	struct fsg_buffhd	*bh;
	void			*data;
	int			rc;

	if (common->data_size >= (u32)65536) {
		/* _MUST_ small than 64K */
		curlun->sense_data = SS_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE;
		return -EINVAL;
	}

	common->residue         = common->data_size;
	common->usb_amount_left = common->data_size;

	/* Carry out the file writes */
	if (unlikely(common->data_size == 0))
		return -EIO; /* No data to write */

	for (;;) {
		if (common->usb_amount_left > 0) {
			/* Wait for the next buffer to become available */
			bh = common->next_buffhd_to_fill;
			if (bh->state != BUF_STATE_EMPTY)
				goto wait;

			/* Request the next buffer */
			common->usb_amount_left      -= common->data_size;
			bh->outreq->length	     = common->data_size;
			bh->bulk_out_intended_length = common->data_size;
			bh->outreq->short_not_ok     = 1;

			START_TRANSFER_OR(common, bulk_out, bh->outreq,
					  &bh->outreq_busy, &bh->state)
				/*
				 * Don't know what to do if
				 * common->fsg is NULL
				 */
				return -EIO;
			common->next_buffhd_to_fill = bh->next;
		} else {
			/* Then, wait for the data to become available */
			bh = common->next_buffhd_to_drain;
			if (bh->state != BUF_STATE_FULL)
				goto wait;

			common->next_buffhd_to_drain = bh->next;
			bh->state = BUF_STATE_EMPTY;

			/* Did something go wrong with the transfer? */
			if (bh->outreq->status != 0) {
				curlun->sense_data = SS_COMMUNICATION_FAILURE;
				curlun->info_valid = 1;
				break;
			}

			/* Perform the write */
			vhead = (struct vendor_item *)bh->buf;
			data  = bh->buf + sizeof(struct vendor_item);

			if (!type) {
				if (vhead->id == HDCP_14_HDMI_ID ||
				    vhead->id == HDCP_14_HDMIRX_ID) {
					rc = vendor_handle_hdcp(vhead);
					if (rc < 0) {
						curlun->sense_data = SS_WRITE_ERROR;
						return -EIO;
					}
				}

				/* Vendor storage */
				rc = vendor_storage_write(vhead->id,
							  (char __user *)data,
							  vhead->size);
				if (rc < 0) {
					curlun->sense_data = SS_WRITE_ERROR;
					return -EIO;
				}
			} else if (type == 1) {
				/* RPMB */
				rc =
				write_keybox_to_secure_storage((u8 *)data,
							       vhead->size);
				if (rc < 0) {
					curlun->sense_data = SS_WRITE_ERROR;
					return -EIO;
				}
			} else if (type == 2) {
				/* security storage */
#ifdef CONFIG_RK_AVB_LIBAVB_USER
				debug("%s call rk_avb_write_perm_attr %d, %d\n",
				      __func__, vhead->id, vhead->size);
				rc = rk_avb_write_perm_attr(vhead->id,
							    (char __user *)data,
							    vhead->size);
				if (rc < 0) {
					curlun->sense_data = SS_WRITE_ERROR;
					return -EIO;
				}
#else
				printf("Please enable CONFIG_RK_AVB_LIBAVB_USER\n");
#endif
			} else if (type == 3) {
				/* efuse or otp*/
#ifdef CONFIG_OPTEE_CLIENT
				if (memcmp(data, "TAEK", 4) == 0) {
					if (vhead->size - 8 != 32) {
						printf("check ta encryption key size fail!\n");
						curlun->sense_data = SS_WRITE_ERROR;
						return -EIO;
					}
					if (trusty_write_ta_encryption_key((uint32_t *)(data + 8), 8) != 0) {
						printf("trusty_write_ta_encryption_key error!");
						curlun->sense_data = SS_WRITE_ERROR;
						return -EIO;
					}
				} else if (memcmp(data, "EHUK", 4) == 0) {
					if (vhead->size - 8 != 32) {
						printf("check oem huk size fail!\n");
						curlun->sense_data = SS_WRITE_ERROR;
						return -EIO;
					}
					if (trusty_write_oem_huk((uint32_t *)(data + 8), 8) != 0) {
						printf("trusty_write_oem_huk error!");
						curlun->sense_data = SS_WRITE_ERROR;
						return -EIO;
					}
				} else {
					printf("Unknown tag\n");
					curlun->sense_data = SS_WRITE_ERROR;
					return -EIO;
				}
#else
				printf("Please enable CONFIG_OPTEE_CLIENT\n");
#endif
			} else {
				return -EINVAL;
			}

			common->residue -= common->data_size;

			/* Did the host decide to stop early? */
			if (bh->outreq->actual != bh->outreq->length)
				common->short_packet_received = 1;
			break; /* Command done */
		}
wait:
		/* Wait for something to happen */
		rc = sleep_thread(common);
		if (rc)
			return rc;
	}

	return -EIO; /* No default reply */
}

static int rkusb_do_vs_read(struct fsg_common *common)
{
	struct fsg_lun		*curlun = &common->luns[common->lun];
	u16			type = get_unaligned_be16(&common->cmnd[4]);
	struct vendor_item	*vhead;
	struct fsg_buffhd	*bh;
	void			*data;
	int			rc;

	if (common->data_size >= (u32)65536) {
		/* _MUST_ small than 64K */
		curlun->sense_data = SS_LOGICAL_BLOCK_ADDRESS_OUT_OF_RANGE;
		return -EINVAL;
	}

	common->residue         = common->data_size;
	common->usb_amount_left = common->data_size;

	/* Carry out the file reads */
	if (unlikely(common->data_size == 0))
		return -EIO; /* No default reply */

	for (;;) {
		/* Wait for the next buffer to become available */
		bh = common->next_buffhd_to_fill;
		while (bh->state != BUF_STATE_EMPTY) {
			rc = sleep_thread(common);
			if (rc)
				return rc;
		}

		memset(bh->buf, 0, FSG_BUFLEN);
		vhead = (struct vendor_item *)bh->buf;
		data  = bh->buf + sizeof(struct vendor_item);
		vhead->id = get_unaligned_be16(&common->cmnd[2]);

		if (!type) {
			/* Vendor storage */
			rc = vendor_storage_read(vhead->id,
						 (char __user *)data,
						 common->data_size);
			if (!rc) {
				curlun->sense_data = SS_UNRECOVERED_READ_ERROR;
				return -EIO;
			}
			vhead->size = rc;
		} else if (type == 1) {
			/* RPMB */
			rc =
			read_raw_data_from_secure_storage((u8 *)data,
							  common->data_size);
			if (!rc) {
				curlun->sense_data = SS_UNRECOVERED_READ_ERROR;
				return -EIO;
			}
			vhead->size = rc;
		} else if (type == 2) {
			/* security storage */
#ifdef CONFIG_RK_AVB_LIBAVB_USER
			rc = rk_avb_read_perm_attr(vhead->id,
						   (char __user *)data,
						   vhead->size);
			if (rc < 0)
				return -EIO;
			vhead->size = rc;
#else
			printf("Please enable CONFIG_RK_AVB_LIBAVB_USER!\n");
#endif
		} else {
			return -EINVAL;
		}

		common->residue   -= common->data_size;
		bh->inreq->length = common->data_size;
		bh->state         = BUF_STATE_FULL;

		break; /* No more left to read */
	}

	return -EIO; /* No default reply */
}
#endif

static int rkusb_do_get_storage_info(struct fsg_common *common,
				     struct fsg_buffhd *bh)
{
	enum if_type type = ums[common->lun].block_dev.if_type;
	int devnum = ums[common->lun].block_dev.devnum;
	u32 media = BOOT_TYPE_UNKNOWN;
	u32 len = common->data_size;
	u8 *buf = (u8 *)bh->buf;

	if (len > 4)
		len = 4;

	switch (type) {
	case IF_TYPE_MMC:
		media = BOOT_TYPE_EMMC;
		break;

	case IF_TYPE_SD:
		media = BOOT_TYPE_SD0;
		break;

	case IF_TYPE_MTD:
		if (devnum == BLK_MTD_SPI_NAND)
			media = BOOT_TYPE_MTD_BLK_SPI_NAND;
		else if (devnum == BLK_MTD_NAND)
			media = BOOT_TYPE_NAND;
		else
			media = BOOT_TYPE_MTD_BLK_SPI_NOR;
		break;

	case IF_TYPE_SCSI:
		media = BOOT_TYPE_SATA;
		break;

	case IF_TYPE_RKNAND:
		media = BOOT_TYPE_NAND;
		break;

	case IF_TYPE_NVME:
		media = BOOT_TYPE_PCIE;
		break;

	default:
		break;
	}

	memcpy((void *)&buf[0], (void *)&media, len);
	common->residue = len;
	common->data_size_from_cmnd = len;

	return len;
}

static int rkusb_do_read_capacity(struct fsg_common *common,
				  struct fsg_buffhd *bh)
{
	u8 *buf = (u8 *)bh->buf;
	u32 len = common->data_size;
	enum if_type type = ums[common->lun].block_dev.if_type;
	int devnum = ums[common->lun].block_dev.devnum;

	/*
	 * bit[0]: Direct LBA, 0: Disabled;
	 * bit[1]: Vendor Storage API, 0: Disabed (default);
	 * bit[2]: First 4M Access, 0: Disabled;
	 * bit[3]: Read LBA On, 0: Disabed (default);
	 * bit[4]: New Vendor Storage API, 0: Disabed;
	 * bit[5]: Read uart data from ram
	 * bit[6]: Read IDB config
	 * bit[7]: Read SecureMode
	 * bit[8]: New IDB feature
	 * bit[9]: Get storage media info
	 * bit[10:63}: Reserved.
	 */
	memset((void *)&buf[0], 0, len);
	if (type == IF_TYPE_MMC || type == IF_TYPE_SD || type == IF_TYPE_NVME)
		buf[0] = BIT(0) | BIT(2) | BIT(4);
	else
		buf[0] = BIT(0) | BIT(4);

	if (type == IF_TYPE_MTD &&
	    (devnum == BLK_MTD_NAND ||
	    devnum == BLK_MTD_SPI_NAND))
		buf[0] |= (1 << 6);

#if !defined(CONFIG_ROCKCHIP_RV1126) && !defined(CONFIG_ROCKCHIP_RK3308)
	if (type == IF_TYPE_MTD && devnum == BLK_MTD_SPI_NOR)
		buf[0] |= (1 << 6);
#endif

#if defined(CONFIG_ROCKCHIP_NEW_IDB)
	buf[1] = BIT(0);
#endif
	buf[1] |= BIT(1);

	/* Set data xfer size */
	common->residue = len;
	common->data_size_from_cmnd = len;

	return len;
}

static void rkusb_fixup_cbwcb(struct fsg_common *common,
			      struct fsg_buffhd *bh)
{
	struct usb_request      *req = bh->outreq;
	struct fsg_bulk_cb_wrap *cbw = req->buf;

	/* FIXME cbw.DataTransferLength was not set by Upgrade Tool */
	common->data_size = le32_to_cpu(cbw->DataTransferLength);
	if (common->data_size == 0) {
		common->data_size =
		get_unaligned_be16(&common->cmnd[7]) << 9;
		printf("Trasfer Length NOT set, please use new version tool\n");
		debug("%s %d, cmnd1 %x\n", __func__,
		      get_unaligned_be16(&common->cmnd[7]),
		      get_unaligned_be16(&common->cmnd[1]));
	}
	if (cbw->Flags & USB_BULK_IN_FLAG)
		common->data_dir = DATA_DIR_TO_HOST;
	else
		common->data_dir = DATA_DIR_FROM_HOST;

	/* Not support */
	common->cmnd[1] = 0;
}

static int rkusb_cmd_process(struct fsg_common *common,
			     struct fsg_buffhd *bh, int *reply)
{
	struct usb_request	*req = bh->outreq;
	struct fsg_bulk_cb_wrap	*cbw = req->buf;
	int rc;

	dump_cbw(cbw);

	if (rkusb_check_lun(common)) {
		*reply = -EINVAL;
		return RKUSB_RC_ERROR;
	}

	switch (common->cmnd[0]) {
	case RKUSB_TEST_UNIT_READY:
		*reply = rkusb_do_test_unit_ready(common, bh);
		rc = RKUSB_RC_FINISHED;
		break;

	case RKUSB_READ_FLASH_ID:
		*reply = rkusb_do_read_flash_id(common, bh);
		rc = RKUSB_RC_FINISHED;
		break;

	case RKUSB_TEST_BAD_BLOCK:
		*reply = rkusb_do_test_bad_block(common, bh);
		rc = RKUSB_RC_FINISHED;
		break;

	case RKUSB_ERASE_10_FORCE:
		*reply = rkusb_do_erase_force(common, bh);
		rc = RKUSB_RC_FINISHED;
		break;

	case RKUSB_LBA_READ_10:
		rkusb_fixup_cbwcb(common, bh);
		common->cmnd[0] = SC_READ_10;
		common->cmnd[1] = 0; /* Not support */
		rc = RKUSB_RC_CONTINUE;
		break;

	case RKUSB_LBA_WRITE_10:
		rkusb_fixup_cbwcb(common, bh);
		common->cmnd[0] = SC_WRITE_10;
		common->cmnd[1] = 0; /* Not support */
		rc = RKUSB_RC_CONTINUE;
		break;

	case RKUSB_READ_FLASH_INFO:
		*reply = rkusb_do_read_flash_info(common, bh);
		rc = RKUSB_RC_FINISHED;
		break;

	case RKUSB_GET_CHIP_VER:
		*reply = rkusb_do_get_chip_info(common, bh);
		rc = RKUSB_RC_FINISHED;
		break;

	case RKUSB_LBA_ERASE:
		*reply = rkusb_do_lba_erase(common, bh);
		rc = RKUSB_RC_FINISHED;
		break;

#ifdef CONFIG_ROCKCHIP_VENDOR_PARTITION
	case RKUSB_VS_WRITE:
		*reply = rkusb_do_vs_write(common);
		rc = RKUSB_RC_FINISHED;
		break;

	case RKUSB_VS_READ:
		*reply = rkusb_do_vs_read(common);
		rc = RKUSB_RC_FINISHED;
		break;
#endif
	case RKUSB_GET_STORAGE_MEDIA:
		*reply = rkusb_do_get_storage_info(common, bh);
		rc = RKUSB_RC_FINISHED;
		break;

	case RKUSB_READ_CAPACITY:
		*reply = rkusb_do_read_capacity(common, bh);
		rc = RKUSB_RC_FINISHED;
		break;

	case RKUSB_RESET:
		*reply = rkusb_do_reset(common, bh);
		rc = RKUSB_RC_FINISHED;
		break;

	case RKUSB_READ_10:
	case RKUSB_WRITE_10:
		printf("CMD Not support, pls use new version Tool\n");
	case RKUSB_SET_DEVICE_ID:
	case RKUSB_ERASE_10:
	case RKUSB_WRITE_SPARE:
	case RKUSB_READ_SPARE:
	case RKUSB_GET_VERSION:
	case RKUSB_ERASE_SYS_DISK:
	case RKUSB_SDRAM_READ_10:
	case RKUSB_SDRAM_WRITE_10:
	case RKUSB_SDRAM_EXECUTE:
	case RKUSB_LOW_FORMAT:
	case RKUSB_SET_RESET_FLAG:
	case RKUSB_SPI_READ_10:
	case RKUSB_SPI_WRITE_10:
	case RKUSB_SESSION:
		/* Fall through */
	default:
		rc = RKUSB_RC_UNKNOWN_CMND;
		break;
	}

	return rc;
}

DECLARE_GADGET_BIND_CALLBACK(rkusb_ums_dnl, fsg_add);
