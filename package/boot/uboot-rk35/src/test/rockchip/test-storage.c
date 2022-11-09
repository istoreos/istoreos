/*
 * (C) Copyright 2019 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#ifdef CONFIG_DM_RAMDISK
#include <boot_rkimg.h>
#endif
#include <cli.h>
#include <dm.h>
#include <environment.h>
#include <malloc.h>
#include <misc.h>
#ifdef CONFIG_RKIMG_BOOTLOADER
#include <sysmem.h>
#endif
#include <linux/ctype.h>
#ifdef CONFIG_ROCKCHIP_VENDOR_PARTITION
#include <asm/arch/vendor.h>
#endif
#include "test-rockchip.h"

#define DEFAULT_STORAGE_RW_PART		"userdata"
static enum if_type blk_get_type_by_name_and_num(char *devtype, int devnum)
{
	int type = -1;

	if (!strcmp(devtype, "mmc"))
		type = IF_TYPE_MMC;
#if defined(CONFIG_RKNAND) || defined(CONFIG_RKNANDC_NAND)
	else if (!strcmp(devtype, "rknand"))
		type = IF_TYPE_RKNAND;
#endif
#ifdef CONFIG_RKSFC_NAND
	else if (!strcmp(devtype, "rksfc") && devnum == 0)
		type = IF_TYPE_SPINAND;
#endif
#ifdef CONFIG_RKSFC_NOR
	else if (!strcmp(devtype, "rksfc") && devnum == 1)
		type = IF_TYPE_SPINOR;
#endif
#ifdef CONFIG_DM_RAMDISK
	else if (!strcmp(devtype, "ramdisk"))
		type = IF_TYPE_RAMDISK;
#endif
#ifdef CONFIG_MTD_BLK
	else if (!strcmp(devtype, "mtd"))
		type = IF_TYPE_MTD;
#endif
#ifdef CONFIG_SCSI
	else if (!strcmp(devtype, "scsi"))
		type = IF_TYPE_SCSI;
#endif
	else if (!strcmp(devtype, "usb"))
		type = IF_TYPE_USB;

	return type;
}

#if defined(CONFIG_MMC) ||\
	defined(CONFIG_RKNAND) ||\
	defined(CONFIG_DM_RAMDISK) ||\
	defined(CONFIG_USB_HOST) ||\
	defined(CONFIG_RKNANDC_NAND) ||\
	defined(CONFIG_RKSFC_NAND) ||\
	defined(CONFIG_RKSFC_NOR)
static int do_test_storage(cmd_tbl_t *cmdtp, int flag,
			   int argc, char *const argv[],
			   const char *devtype,
			   const char *devnum,
			   const char *label)
{
	struct blk_desc *dev_desc;
	disk_partition_t part;
	u32 blocks, round, sector;
	char *w_buf, *r_buf;
	char cmd[64];
	int i, ret;
	ulong ts;

	/* 1. Switch to device type/num */
	if (devtype && !strcmp(devtype, "usb")) {
		if (run_command("usb start", 0)) {
			printf("Switch to %s%s failed\n", devtype, devnum);
			ret = -ENODEV;
			goto err1;
		}
	} else if (devtype) {
		snprintf(cmd, sizeof(cmd), "%s dev %s", devtype, devnum);
		if (run_command(cmd, 0)) {
			printf("Switch to %s%s failed\n", devtype, devnum);
			ret = -ENODEV;
			goto err1;
		}
	}
	if (!devtype) {
		/* For blk test only */
#ifdef CONFIG_DM_RAMDISK
		dev_desc = rockchip_get_bootdev();
#else
		printf("%s Not support devtype!\n", __func__);
		return -EINVAL;
#endif
	} else {
		int if_type;
		int num = simple_strtoul(devnum, NULL, 10);

		if_type = blk_get_type_by_name_and_num((char *)devtype, num);
		dev_desc = blk_get_devnum_by_type(if_type, num);
	}
	if (!dev_desc) {
		ut_err("%s: failed to get blk desc\n", label);
		return -ENODEV;
	}

	/* 2. Get test partition */
	if (part_get_info_by_name(dev_desc,
				  DEFAULT_STORAGE_RW_PART, &part) < 0) {
		ut_err("%s: failed to find %s partition\n", label,
		       DEFAULT_STORAGE_RW_PART);
		return -EINVAL;
	}

	/* 32MB */
	sector = part.start;
	if (part.start + part.size > dev_desc->lba)
		part.size = dev_desc->lba - part.start;
	blocks = part.size > 0x10000 ? 0x10000 : part.size;
	round  = 4;

	/* Round up */
	if (blocks % 2)
		blocks += 1;

	printf("%s RW sectors on %s 0x%08x - 0x%08x(size: %ld MiB) for %d round\n\n",
	       label, DEFAULT_STORAGE_RW_PART,
	       sector, sector + blocks,
	       (blocks * dev_desc->blksz) >> 20, round);

	/* 3. Prepare memory */
#ifdef CONFIG_RKIMG_BOOTLOADER
	w_buf = sysmem_alloc_by_name("storage_w", blocks * dev_desc->blksz);
#else
	w_buf = memalign(CONFIG_SYS_CACHELINE_SIZE, blocks * dev_desc->blksz);
#endif
	if (!w_buf) {
		ut_err("%s: no sysmem for w_buf\n", label);
		ret = -ENOMEM;
		goto err1;
	}
#ifdef CONFIG_RKIMG_BOOTLOADER
	r_buf = sysmem_alloc_by_name("storage_r", blocks * dev_desc->blksz);
#else
	r_buf = memalign(CONFIG_SYS_CACHELINE_SIZE, blocks * dev_desc->blksz);
#endif
	if (!r_buf) {
		ut_err("%s: no sysmem for r_buf\n", label);
		ret = -ENOMEM;
		goto err2;
	}

	for (i = 0; i < blocks * dev_desc->blksz; i++) {
		w_buf[i] = i;
		r_buf[i] = 0;
	}

	/* 4. Write test */
	ts = get_timer(0);
	if (devtype) {
		snprintf(cmd, sizeof(cmd), "%s write 0x%x 0x%x 0x%x",
			 devtype, (u32)(ulong)w_buf, sector, blocks);
		for (i = 0; i < round; i++) {
			if (run_command(cmd, 0)) {
				ut_err("%s: failed to write @%d round\n", label, i);
				ret = -EIO;
				goto err3;
			}
		}
	} else {
		for (i = 0; i < round; i++) {
			ret = blk_dwrite(dev_desc, sector, blocks, w_buf);
			if (ret != blocks) {
				ut_err("%s: failed to write @%d round\n", label, i);
				ret = -EIO;
				goto err3;
			}
		}
	}

	ts = get_timer(0) - ts;
	printf("\n%s write: size %dMB, used %ldms, speed %ldMB/s\n",
	       label, blocks * round / 2048, ts, (blocks * round >> 1) / ts);

	/* 5. Read test */
	ts = get_timer(0);
	if (devtype) {
		snprintf(cmd, sizeof(cmd), "%s read 0x%x 0x%x 0x%x",
			 devtype, (u32)(ulong)r_buf, sector, blocks);

		for (i = 0; i < round; i++) {
			if (run_command(cmd, 0)) {
				ut_err("%s: failed to read @%d round\n", label, i);
				ret = -EIO;
				goto err3;
			}
		}
	} else {
		for (i = 0; i < round; i++) {
			ret = blk_dread(dev_desc, sector, blocks, r_buf);
			if (ret != blocks) {
				ut_err("%s: failed to read @%d round\n", label, i);
				ret = -EIO;
				goto err3;
			}
		}
	}

	ts = get_timer(0) - ts;
	printf("\n%s read: size %dMB, used %ldms, speed %ldMB/s\n",
	       label, blocks * round / 2048, ts, (blocks * round >> 1) / ts);

	/* 6. Verify the context */
	for (i = 0; i < blocks * dev_desc->blksz; i++) {
		if (w_buf[i] != r_buf[i]) {
			ut_err("%s: context compare error\n", label);
			ret = -EINVAL;
			goto err3;
		}
	}

	/* 7. Switch back to default system devnum */
	if (devtype && !strcmp(devtype, "mmc") && env_get("devnum") &&
	    strcmp(devnum, env_get("devnum"))) {
		ret = run_command(cmd, 0);
		if (ret) {
			ut_err("%s: failed to switch to mmc1\n", label);
			ret = -ENODEV;
			goto err3;
		}
	}

	ret = 0;
err3:
#ifdef CONFIG_RKIMG_BOOTLOADER
	sysmem_free((phys_addr_t)r_buf);
err2:
	sysmem_free((phys_addr_t)w_buf);
#else
	free(r_buf);
err2:
	free(w_buf);
#endif
err1:

	return ret;
}

#ifdef CONFIG_MMC
static int do_test_emmc(cmd_tbl_t *cmdtp, int flag,
			int argc, char *const argv[])
{
	return do_test_storage(cmdtp, flag, argc, argv, "mmc", "0", "MMC0");
}

static int do_test_sdmmc(cmd_tbl_t *cmdtp, int flag,
			 int argc, char *const argv[])
{
	return do_test_storage(cmdtp, flag, argc, argv, "mmc", "1", "MMC1");
}
#endif

#if defined(CONFIG_RKNAND) || defined(CONFIG_RKNANDC_NAND)
static int do_test_rknand(cmd_tbl_t *cmdtp, int flag,
			  int argc, char *const argv[])
{
	return do_test_storage(cmdtp, flag, argc, argv, "rknand", "0", "RKNAND0");
}
#endif

#ifdef CONFIG_RKSFC_NAND
static int do_test_rkflash_spinand(cmd_tbl_t *cmdtp, int flag,
				   int argc, char *const argv[])
{
	return do_test_storage(cmdtp, flag, argc, argv, "rksfc", "0", "RKSFC0");
}
#endif

#ifdef CONFIG_RKSFC_NOR
static int do_test_rkflash_spinor(cmd_tbl_t *cmdtp, int flag,
				  int argc, char *const argv[])
{
	return do_test_storage(cmdtp, flag, argc, argv, "rksfc", "1", "RKSFC1");
}
#endif

#ifdef CONFIG_DM_RAMDISK
static int do_test_blk(cmd_tbl_t *cmdtp, int flag,
		       int argc, char *const argv[])
{
	return do_test_storage(cmdtp, flag, argc, argv, NULL, NULL, "BLK");
}
#endif

#ifdef CONFIG_SCSI
static int do_test_scsi(cmd_tbl_t *cmdtp, int flag,
			int argc, char *const argv[])
{
	return do_test_storage(cmdtp, flag, argc, argv, "scsi", "0", "BLK");
}
#endif

#endif/* defined(CONFIG_MMC) ||\
       * defined(CONFIG_RKNAND) ||\
       * defined(CONFIG_DM_RAMDISK) ||\
       * defined(CONFIG_USB_HOST) ||\
       * defined(CONFIG_RKNANDC_NAND) ||\
       * defined(CONFIG_RKSFC_NAND) ||\
       * defined(CONFIG_RKSFC_NOR)
       */

#if defined(CONFIG_OPTEE_CLIENT) && defined(CONFIG_MMC)
static int do_test_secure_storage(cmd_tbl_t *cmdtp, int flag,
				  int argc, char *const argv[])
{
	return run_command("mmc testsecurestorage", 0);
}
#endif

#if defined(CONFIG_CMD_SAVEENV) && !defined(CONFIG_ENV_IS_NOWHERE) && \
	!defined(CONFIG_SPL_BUILD)
static int do_test_env(cmd_tbl_t *cmdtp, int flag,
		       int argc, char *const argv[])
{
	int ret;

	ret = env_save();
	if (ret) {
		ut_err("env: failed to save, ret=%d\n", ret);
		return ret;
	}

	return env_load();
}
#endif

#ifdef CONFIG_ROCKCHIP_VENDOR_PARTITION
static int do_test_vendor(cmd_tbl_t *cmdtp, int flag,
			  int argc, char *const argv[])
{
	return vendor_storage_test();
}
#endif

#ifdef CONFIG_ROCKCHIP_EFUSE
static int do_test_efuse(cmd_tbl_t *cmdtp, int flag,
			 int argc, char *const argv[])
{
	struct udevice *dev;
	u8 fuses[128] = {0};
	int ret;

	ret = uclass_get_device(UCLASS_MISC, 0, &dev);
	if (ret) {
		ut_err("efuse: failed to get device, ret=%d\n", ret);
		return 0;
	}

	ret = misc_read(dev, 0, &fuses, sizeof(fuses));
	if (ret) {
		ut_err("efuse: failed to read, ret=%d\n", ret);
		return 0;
	}

	printf("Efuse-content:\n");
	print_buffer(0, fuses, 1, 128, 16);

	return 0;
}
#endif

#ifdef CONFIG_ROCKCHIP_OTP
static int do_test_otp(cmd_tbl_t *cmdtp, int flag,
		       int argc, char *const argv[])
{
	struct udevice *dev;
	u8 otps[64] = {0};
	int ret;

	/* retrieve the device */
	ret = uclass_get_device_by_driver(UCLASS_MISC, 0, &dev);
	if (ret) {
		ut_err("otp: failed to get device, ret=%d\n", ret);
		return 0;
	}

	ret = misc_read(dev, 0, &otps, sizeof(otps));
	if (ret) {
		ut_err("otp: failed to read, ret=%d\n", ret);
		return 0;
	}

	printf("Otp-content:\n");
	print_buffer(0, otps, 1, 64, 16);

	return 0;
}
#endif

#ifdef CONFIG_PARTITIONS
static int do_test_part(cmd_tbl_t *cmdtp, int flag,
			int argc, char *const argv[])
{
	return run_command("part list ${devtype} ${devnum}", 0);
}
#endif

#ifdef CONFIG_USB_HOST
static int do_test_usb(cmd_tbl_t *cmdtp, int flag,
		       int argc, char *const argv[])
{
	run_command("usb start", 0);
	return do_test_storage(cmdtp, flag, argc, argv, "usb", "0", "usb0");
}
#endif

static cmd_tbl_t sub_cmd[] = {
#ifdef CONFIG_DM_RAMDISK
	UNIT_CMD_DEFINE(blk, 0),
#endif
#ifdef CONFIG_MMC
	UNIT_CMD_DEFINE(emmc, 0),
#endif
#ifdef CONFIG_ROCKCHIP_EFUSE
	UNIT_CMD_DEFINE(efuse, 0),
#endif
#if defined(CONFIG_CMD_SAVEENV) && !defined(CONFIG_ENV_IS_NOWHERE) && \
	!defined(CONFIG_SPL_BUILD)
	UNIT_CMD_DEFINE(env, 0),
#endif
#ifdef CONFIG_ROCKCHIP_OTP
	UNIT_CMD_DEFINE(otp, 0),
#endif
#if defined(CONFIG_RKNAND) || defined(CONFIG_RKNANDC_NAND)
	UNIT_CMD_DEFINE(rknand, 0),
#endif
#ifdef CONFIG_RKSFC_NAND
	UNIT_CMD_DEFINE(rkflash_spinand, 0),
#endif
#ifdef CONFIG_RKSFC_NOR
	UNIT_CMD_DEFINE(rkflash_spinor, 0),
#endif
#if defined(CONFIG_OPTEE_CLIENT) && defined(CONFIG_MMC)
	UNIT_CMD_DEFINE(secure_storage, 0),
#endif
#ifdef CONFIG_PARTITIONS
	UNIT_CMD_DEFINE(part, 0),
#endif
#ifdef CONFIG_USB_HOST
	UNIT_CMD_DEFINE(usb, 0),
#endif
#ifdef CONFIG_MMC
	UNIT_CMD_DEFINE(sdmmc, 0),
#endif
#ifdef CONFIG_ROCKCHIP_VENDOR_PARTITION
	UNIT_CMD_DEFINE(vendor, 0),
#endif
#ifdef CONFIG_SCSI
	UNIT_CMD_DEFINE(scsi, 0),
#endif
};

static char sub_cmd_help[] =
#ifdef CONFIG_DM_RAMDISK
"    [.] rktest blk                         - test blk layer read/write\n"
#endif
#ifdef CONFIG_MMC
"    [.] rktest emmc                        - test emmc read/write speed\n"
"    [.] rktest sdmmc                       - test sd card and fat fs read/write\n"
#endif
#if defined(CONFIG_RKNAND) || defined(CONFIG_RKNANDC_NAND)
"    [.] rktest rknand                      - test rknand read/write speed\n"
#endif
#ifdef CONFIG_RKSFC_NAND
"    [.] rktest rkflash_spinand             - test RKFLASH DM driver spinand read/write speed\n"
#endif
#ifdef CONFIG_RKSFC_NOR
"    [.] rktest rkflash_spinor              - test RKFLASH DM driver read/write speed\n"
#endif
#if defined(CONFIG_OPTEE_CLIENT) && defined(CONFIG_MMC)
"    [.] rktest secure_storage              - test secure storage\n"
#endif
#ifdef CONFIG_ROCKCHIP_VENDOR_PARTITION
"    [.] rktest vendor                      - test vendor storage read/write\n"
#endif
#ifdef CONFIG_ROCKCHIP_EFUSE
"    [.] rktest efuse                       - test efuse, dump content\n"
#endif
#ifdef CONFIG_ROCKCHIP_OTP
"    [.] rktest otp                         - test otp, dump content\n"
#endif
#if defined(CONFIG_CMD_SAVEENV) && !defined(CONFIG_ENV_IS_NOWHERE) && \
	!defined(CONFIG_SPL_BUILD)
"    [.] rktest env                         - test save env to storage\n"
#endif
#ifdef CONFIG_PARTITIONS
"    [.] rktest part                        - test part list\n"
#endif
#ifdef CONFIG_USB_HOST
"    [.] rktest usb                         - test usb disk\n"
#endif
#ifdef CONFIG_SCSI
"    [.] rktest scsi                        - test sata disk\n"
#endif
;

const struct cmd_group cmd_grp_storage = {
	.id	= TEST_ID_STORAGE,
	.help	= sub_cmd_help,
	.cmd	= sub_cmd,
	.cmd_n	= ARRAY_SIZE(sub_cmd),
};
