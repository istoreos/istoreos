/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef __BOOT_ROCKCHIP_H_
#define __BOOT_ROCKCHIP_H_

/* This is a copy from Android boot loader */
enum _boot_mode {
	BOOT_MODE_NORMAL = 0,
	BOOT_MODE_RECOVERY,
	BOOT_MODE_BOOTLOADER,	/* Android: Fastboot mode */
	BOOT_MODE_LOADER,	/* Rockchip: Rockusb download mode */
	BOOT_MODE_CHARGING,
	BOOT_MODE_UMS,
	BOOT_MODE_BROM_DOWNLOAD,
	BOOT_MODE_PANIC,
	BOOT_MODE_WATCHDOG,
	BOOT_MODE_DFU,
	BOOT_MODE_UNDEFINE,
};

struct bootloader_message {
	char command[32];
	char status[32];
	char recovery[768];
	/*
	 * The 'recovery' field used to be 1024 bytes.  It has only ever
	 * been used to store the recovery command line, so 768 bytes
	 * should be plenty.  We carve off the last 256 bytes to store the
	 * stage string (for multistage packages) and possible future
	 * expansion.
	 */
	char stage[32];
	char slot_suffix[32];
	char reserved[192];
};

struct rockchip_image {
	uint32_t tag;
	uint32_t size;
	int8_t image[1];
	uint32_t crc;
};

#define RK_BLK_SIZE			512
#define TAG_KERNEL			0x4C4E524B
#define BCB_MESSAGE_BLK_OFFSET		(16 * 1024 >> 9)

#define PART_UBOOT			"uboot"
#define PART_TRUST			"trust"
#define PART_MISC			"misc"
#define PART_RESOURCE			"resource"
#define PART_KERNEL			"kernel"
#define PART_BOOT			"boot"
#define PART_VENDOR_BOOT		"vendor_boot"
#define PART_RECOVERY			"recovery"
#define PART_DTBO			"dtbo"
#define PART_LOGO			"logo"
#define PART_SYSTEM			"system"
#define PART_METADATA			"metadata"
#define PART_USERDATA			"userdata"

struct blk_desc *rockchip_get_bootdev(void);
void rockchip_set_bootdev(struct blk_desc *desc);
void board_run_recovery_wipe_data(void);
void setup_download_mode(void);
#ifdef CONFIG_ANDROID_BOOT_IMAGE
int get_bcb_recovery_msg(void);
#endif
int rockchip_read_dtb_file(void *fdt_addr);
int rockchip_ram_read_dtb_file(void *img, void *fdt_addr);
int init_kernel_dtb(void);
int fit_write_trusty_rollback_index(u32 trusty_index);
int get_bootdev_type(void);

#ifndef CONFIG_SPL_BUILD
int rockchip_get_boot_mode(void);
#else
int rockchip_get_boot_mode(struct blk_desc *dev_desc, u32 bcb_sector_offset);
#endif
#endif
