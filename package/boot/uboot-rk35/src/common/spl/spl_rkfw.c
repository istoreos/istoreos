// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <android_image.h>
#include <errno.h>
#include <malloc.h>
#include <misc.h>
#include <spl.h>
#include <spl_rkfw.h>
#include <linux/kernel.h>
#include <asm/arch-rockchip/spl_resource_img.h>
#include <boot_rkimg.h>

#ifdef CONFIG_SPL_ATF
static const __aligned(16) struct s_fip_name_id fip_name_id[] = {
	{ BL30_IMAGE_NAME, UUID_SCP_FIRMWARE_BL30 },		/* optional */
	{ BL31_IMAGE_NAME, UUID_EL3_RUNTIME_FIRMWARE_BL31 },	/* mandatory */
	{ BL32_IMAGE_NAME, UUID_SECURE_PAYLOAD_BL32 },		/* optional */
};

static int file2comp_id(const char *file_name, u32 *comp_id)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(fip_name_id); i++) {
		if (!strcmp(file_name, fip_name_id[i].name)) {
			*comp_id = fip_name_id[i].id;
			return 0;
		}
	}

	return -ENOENT;
}

static int open_image(const char *image_name, tboot_entry *entry,
		      struct tag_tboot_header_2k *hdr)
{
	u32 i, component_num, sign_offset;
	component_data *pcompdata;
	boot_component *pcomp;
	int n_found = 0;
	u32 comp_id;
	int ret;

	ret = file2comp_id(image_name, &comp_id);
	if (ret) {
		printf("Can't find unknown image: %s\n", image_name);
		return ret;
	}

	component_num = (hdr->size >> 16) & 0xffff;
	sign_offset = (hdr->size & 0xffff) << 2;
	pcompdata = (component_data *)((char *)hdr + sizeof(tboot_header));
	pcomp = (boot_component *)((char *)hdr + sign_offset + SIGNATURE_SIZE);

	for (i = 0; i < component_num; i++) {
		if (comp_id == pcomp->component_id) {
			if (n_found < MAX_BL_CODE_NUM) {
				memcpy(&entry[n_found].component, pcomp,
				       sizeof(boot_component));
				memcpy(&entry[n_found].compdata, pcompdata,
				       sizeof(component_data));
				n_found++;
			} else {
				printf("Image num excess max: %d!\n",
				       MAX_BL_CODE_NUM);
				return -EINVAL;
			}
		} else {
			if (n_found > 0)
				break;
		}

		pcomp++;
		pcompdata++;
	}

	if (!n_found) {
		printf("No find %s\n", image_name);
		return -ENONET;
	}

	return n_found;
}

static int check_image(struct tag_tboot_header_2k *hdr)
{
	u32 hash_format[] = { 0, 160, 256, 256 };

	/* HASH format identifier */
	return (hash_format[hdr->flags & 0x3] == 0) ? -EINVAL : 0;
}

static int load_image(struct spl_load_info *info,
		      struct tag_tboot_header_2k *hdr,
		      u32 image_sector,
		      const char *image_name,
		      uintptr_t *entry_point)
{
	tboot_entry entry[MAX_BL_CODE_NUM];
	void *image_buf = NULL;
	ulong load_addr;
	u32 sect_off;
	u32 sect_cnt;
	int image_num;
	int i, ret;

	/* Parse components from image header */
	image_num = open_image(image_name, entry, hdr);
	if (image_num < 0)
		return image_num;

	/* Get all component */
	for (i = 0; i < image_num; i++) {
		load_addr = entry[i].compdata.load_addr;
		sect_cnt = entry[i].component.image_size;
		sect_off = entry[i].component.storage_addr;

		printf("%s[%d]: addr=0x%lx, size=0x%lx\n",
		       image_name, i, load_addr, (ulong)sect_cnt * 512);

		/*
		 * MMC/NAND controller DMA can't access sram region, so:
		 * data -> ddr buffer -> memcpy to sram region.
		 */
		if (load_addr < CONFIG_SYS_SDRAM_BASE ||
		    load_addr >= CONFIG_SYS_SDRAM_BASE + SDRAM_MAX_SIZE) {
			image_buf = memalign(ARCH_DMA_MINALIGN, sect_cnt * 512);
			if (!image_buf) {
				printf("%s: malloc failed\n", __func__);
				return -ENOMEM;
			}
		} else {
			image_buf = (void *)load_addr;
		}

		ret = info->read(info, image_sector + sect_off,
				 sect_cnt, image_buf);
		if (ret != sect_cnt) {
			printf("Read '%s' failed at sector: %ld, ret=%d\n",
			       image_name, (ulong)image_sector + sect_off, ret);
			return -EIO;
		}

		/* Verify component */
		ret = check_image(hdr);
		if (ret) {
			printf("%s[%d]: verify image fail!\n", image_name, i);
			return ret;
		}

		/* Handle sram region */
		if ((ulong)image_buf != load_addr) {
			memcpy((void *)load_addr, image_buf, sect_cnt << 9);
			free(image_buf);
		}

		/* Fill entry_point by first component */
		if (i == 0)
			*entry_point = (uintptr_t)load_addr;
	}

	return ret;
}

static int rkfw_load_trust(struct spl_load_info *info, u32 image_sector,
			   struct spl_image_info *spl_image,
			   int *found_rkfw, u32 try_count)
{
	struct tag_tboot_header_2k hdr;
	u32 sect_addr = image_sector;
	int blkcnt = 4;	/* header sectors, 2KB */
	int i, ret = 0;

	/* Find valid image header */
	for (i = 0; i < try_count; i++) {
		sect_addr = image_sector + (i * RKFW_RETRY_SECTOR_SIZE);
		if (blkcnt != info->read(info, sect_addr, blkcnt, &hdr))
			continue;

		if (hdr.tag == TBOOT_HEAD_TAG) {
			/* Mark it */
			*found_rkfw = 1;

			/* bl31 is mandatory */
			ret = load_image(info, &hdr, sect_addr,
					 BL31_IMAGE_NAME, &spl_image->entry_point);
			if (ret)
				continue;

			/* bl32 is optional */
			ret = load_image(info, &hdr, sect_addr,
					 BL32_IMAGE_NAME, &spl_image->entry_point_bl32);
			if (ret) {
				if (ret == -ENONET) {
					spl_image->entry_point_bl32 = -1;	/* Not exist */
					ret = 0;
				} else {
					continue;
				}
			}
			break;
		}
	}

	return ret;
}
#else /* op-tee */
static int rkfw_load_trust(struct spl_load_info *info, u32 image_sector,
			   struct spl_image_info *spl_image,
			   int *found_rkfw, u32 try_count)
{
	struct tag_second_loader_hdr hdr;
	int i, ret, blkcnt = 4;	/* header sectors, 2KB */
	char *load_addr;
	u32 sect_addr;

	/* Detect valid image header */
	for (i = 0; i < try_count; i++) {
		sect_addr = image_sector + (i * RKFW_RETRY_SECTOR_SIZE);
		ret = info->read(info, sect_addr, blkcnt, &hdr);
		if (ret != blkcnt)
			continue;

		if (!memcmp(hdr.magic, TBOOT_HEAD_TAG, 6)) {
			*found_rkfw = 1;
			spl_image->entry_point = (uintptr_t)hdr.loader_load_addr;
			/* Load full binary image(right behind header) */
			sect_addr += blkcnt;
			load_addr = (char *)((size_t)hdr.loader_load_addr);
			blkcnt = DIV_ROUND_UP(hdr.loader_load_size, 512);

			printf("tee.bin: addr=0x%lx, size=0x%lx\n",
			       (ulong)load_addr, (ulong)blkcnt * 512);
			ret = info->read(info, sect_addr, blkcnt, load_addr);
			if (ret != blkcnt)
				continue;

			break;
		}
	}

	if (i == try_count) {
		printf("Can not find usable trust\n");
		return -ENONET;
	}

	return 0;
}
#endif

static int rkfw_load_uboot(struct spl_load_info *info, u32 image_sector,
			   struct spl_image_info *spl_image, u32 try_count)
{
	struct tag_second_loader_hdr hdr;
	int i, ret, blkcnt = 4;	/* header sectors, 2KB */
	char *load_addr;
	u32 sect_addr;

	/* Detect valid image header */
	for (i = 0; i < try_count; i++) {
		sect_addr = image_sector + (i * RKFW_RETRY_SECTOR_SIZE);
		ret = info->read(info, sect_addr, blkcnt, &hdr);
		if (ret != blkcnt)
			continue;

		if (!memcmp(hdr.magic, LOADER_HARD_STR, 6)) {
			/* Load full binary image(right behind header) */
			sect_addr += blkcnt;
			load_addr = (char *)((size_t)hdr.loader_load_addr);
			blkcnt = DIV_ROUND_UP(hdr.loader_load_size, 512);

			printf("u-boot.bin: addr=0x%lx, size=0x%lx\n",
			       (ulong)load_addr, (ulong)blkcnt * 512);
			ret = info->read(info, sect_addr, blkcnt, load_addr);
			if (ret != blkcnt)
				continue;

			break;
		}
	}

	if (i == try_count) {
		printf("Can not find usable uboot\n");
		return -ENONET;
	}

	/* Fill entry point */
#ifdef CONFIG_SPL_ATF
	spl_image->entry_point_bl33 = (uintptr_t)hdr.loader_load_addr;
#endif
#ifdef CONFIG_SPL_OPTEE
	spl_image->entry_point_os = (uintptr_t)hdr.loader_load_addr;
#endif
	return 0;
}

static int rkfw_load_kernel(struct spl_load_info *info, u32 image_sector,
			    struct spl_image_info *spl_image, u32 try_count)
{
	struct andr_img_hdr *hdr;
	int ret, cnt;
	int dtb_sector, ramdisk_sector, resource_sector;

	cnt = ALIGN(sizeof(struct andr_img_hdr), 512) >> 9;
	hdr = malloc(cnt * 512);
	if (!hdr)
		return -ENOMEM;

	ret = info->read(info, image_sector, cnt, (void *)hdr);
	if (ret != cnt) {
		ret = -EIO;
		goto out;
	}

	if (memcmp(hdr->magic, ANDR_BOOT_MAGIC, strlen(ANDR_BOOT_MAGIC)) != 0) {
		printf("SPL: boot image head magic error\n");
		ret = -EINVAL;
		goto out;
	}

	ramdisk_sector = ALIGN(hdr->kernel_size, hdr->page_size);
	resource_sector = ALIGN(hdr->kernel_size, hdr->page_size)
			+ ALIGN(hdr->ramdisk_size, hdr->page_size);
	dtb_sector = ALIGN(hdr->kernel_size, hdr->page_size)
			+ ALIGN(hdr->ramdisk_size, hdr->page_size)
			+ ALIGN(hdr->second_size, hdr->page_size);
	image_sector = image_sector + cnt;
	cnt = ALIGN(hdr->kernel_size, hdr->page_size) >> 9;

	/* Load kernel image */
#ifdef CONFIG_SPL_ROCKCHIP_HW_DECOMPRESS
	ret = info->read(info, image_sector, cnt,
			 (void *)CONFIG_SPL_KERNEL_COMPRESS_ADDR);
#else
	ret = info->read(info, image_sector, cnt, (void *)CONFIG_SPL_KERNEL_ADDR);
#endif
	if (ret != cnt) {
		ret = -EIO;
		goto out;
	}
#ifdef CONFIG_SPL_ROCKCHIP_HW_DECOMPRESS
	struct udevice *dev;
	u32 cap = DECOM_GZIP;

	dev = misc_decompress_get_device(cap);

	if (!dev)
		goto out;

	ret = misc_decompress_start(dev, CONFIG_SPL_KERNEL_COMPRESS_ADDR,
				    CONFIG_SPL_KERNEL_ADDR,
				    CONFIG_SPL_KERNEL_DECOM_LIMIT_SIZE);
	if (ret)
		goto out;

#endif

	/* Load ramdisk image */
	if (hdr->ramdisk_size) {
#ifdef CONFIG_SPL_ROCKCHIP_HW_DECOMPRESS
		ret = info->read(info, (ramdisk_sector >> 9) + image_sector,
				 ALIGN(hdr->ramdisk_size, hdr->page_size) >> 9,
				 (void *)CONFIG_SPL_RAMDISK_COMPRESS_ADDR);
#else
		ret = info->read(info, (ramdisk_sector >> 9) + image_sector,
				 ALIGN(hdr->ramdisk_size, hdr->page_size) >> 9,
				 (void *)CONFIG_SPL_RAMDISK_ADDR);
#endif
		if (ret != (ALIGN(hdr->ramdisk_size, hdr->page_size) >> 9)) {
			ret = -EIO;
			goto out;
		}
#ifdef CONFIG_SPL_ROCKCHIP_HW_DECOMPRESS
		int timeout = 10000;

		while (!misc_decompress_is_complete(dev)) {
			if (timeout < 0) {
				ret = -EIO;
				goto out;
			}

			timeout--;
			udelay(10);
		}

		ret = misc_decompress_stop(dev);
		if (ret)
			goto out;

		ret = misc_decompress_start(dev,
					    CONFIG_SPL_RAMDISK_COMPRESS_ADDR,
					    CONFIG_SPL_RAMDISK_ADDR,
					    CONFIG_SPL_RAMDISK_DECOM_LIMIT_SIZE);
		if (ret)
			goto out;
#endif
	}
#ifdef CONFIG_SPL_ROCKCHIP_HW_DECOMPRESS
	else {
		int timeout = 10000;

		while (!misc_decompress_is_complete(dev)) {
			if (timeout < 0) {
				ret = -EIO;
				goto out;
			}

			timeout--;
			udelay(10);
		}
	}
#endif
	/* Load resource, and checkout the dtb */
	if (hdr->second_size) {
		struct resource_img_hdr *head =
		   (struct resource_img_hdr *)(CONFIG_SPL_FDT_ADDR + 0x100000);

		ret = info->read(info, (resource_sector >> 9) + image_sector,
				 ALIGN(hdr->second_size, hdr->page_size) >> 9,
				 (void *)head);
		if (ret != (ALIGN(hdr->second_size, hdr->page_size) >> 9)) {
			ret = -EIO;
			goto out;
		}
#ifdef CONFIG_SPL_KERNEL_BOOT
		if (spl_resource_image_check_header(head)) {
			printf("Can't find kernel dtb in spl.");
		} else {
			struct resource_entry *entry;
			char *dtb_temp;

			entry = spl_resource_image_get_dtb_entry(head);
			if (!entry) {
				ret = -EIO;
				goto out;
			}

			dtb_temp = (char *)((char *)head + entry->f_offset * 512);
			memcpy((char *)CONFIG_SPL_FDT_ADDR, dtb_temp,
			       entry->f_size);
		}
#endif
	} else {
		/* Load dtb image */
		ret = info->read(info, (dtb_sector >> 9) + image_sector,
				 ALIGN(hdr->dtb_size, hdr->page_size) >> 9,
				 (void *)CONFIG_SPL_FDT_ADDR);
		if (ret != (ALIGN(hdr->dtb_size, hdr->page_size) >> 9)) {
			ret = -EIO;
			goto out;
		}
	}

	spl_image->fdt_addr = (void *)CONFIG_SPL_FDT_ADDR;
#ifdef CONFIG_SPL_OPTEE
	spl_image->entry_point_os = (uintptr_t)CONFIG_SPL_KERNEL_ADDR;
#endif
#ifdef CONFIG_SPL_ATF
	spl_image->entry_point_bl33 = CONFIG_SPL_KERNEL_ADDR;
#endif
	ret = 0;
out:
	free(hdr);

	return ret;
}

int spl_load_rkfw_image(struct spl_image_info *spl_image,
			struct spl_load_info *info)
{
	u32 uboot_sector = CONFIG_RKFW_U_BOOT_SECTOR;
	u32 trust_sector = CONFIG_RKFW_TRUST_SECTOR;
	u32 boot_sector  = CONFIG_RKFW_BOOT_SECTOR;
	int ret, try_count = RKFW_RETRY_SECTOR_TIMES;
	int found_rkfw = 0;
	char *part_name;
#ifdef CONFIG_SPL_LIBDISK_SUPPORT
	struct blk_desc *dev_desc = info->dev;
	disk_partition_t part_info;

	if (dev_desc) {
		if (part_get_info_by_name(dev_desc, PART_UBOOT, &part_info) > 0)
			uboot_sector = part_info.start;
		if (part_get_info_by_name(dev_desc, PART_TRUST, &part_info) > 0)
			trust_sector = part_info.start;
		if (part_get_info_by_name(dev_desc, PART_BOOT, &part_info) > 0)
			boot_sector = part_info.start;
	}
#endif
	/* u-boot or boot */
	if (spl_image->next_stage != SPL_NEXT_STAGE_UBOOT)
		uboot_sector = 0;

	ret = rkfw_load_trust(info, trust_sector, spl_image,
			      &found_rkfw, try_count);
	if (ret) {
		part_name = PART_TRUST;
		goto out;
	}

	if (uboot_sector) {
		ret = rkfw_load_uboot(info, uboot_sector, spl_image, try_count);
		if (ret) {
			part_name = PART_UBOOT;
			goto out;
		}
	} else {
		ret = rkfw_load_kernel(info, boot_sector, spl_image, try_count);
		if (ret) {
			part_name = PART_BOOT;
			goto out;
		}
	}

#if CONFIG_IS_ENABLED(LOAD_FIT)
	spl_image->fdt_addr = 0;
#endif
#ifdef CONFIG_SPL_ATF
	spl_image->os = IH_OS_ARM_TRUSTED_FIRMWARE;
#else
	spl_image->os = IH_OS_OP_TEE;
#endif

out:
	if (ret)
		printf("Load %s part failed! ret=%d\n", part_name, ret);

	/* If not found rockchip firmware, try others outside */
	return found_rkfw ? ret : -EAGAIN;
}
