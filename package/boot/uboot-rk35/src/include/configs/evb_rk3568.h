/*
 * SPDX-License-Identifier:     GPL-2.0+
 *
 * Copyright (c) 2020 Rockchip Electronics Co., Ltd
 */

#ifndef __CONFIGS_RK3568_EVB_H
#define __CONFIGS_RK3568_EVB_H

#include <configs/rk3568_common.h>

#ifndef CONFIG_SPL_BUILD

#undef ROCKCHIP_DEVICE_SETTINGS
#define ROCKCHIP_DEVICE_SETTINGS \
		"stdin=serial,usbkbd\0" \
		"stdout=serial,vidconsole\0" \
		"stderr=serial,vidconsole\0"

#define CONFIG_SYS_MMC_ENV_DEV		0

#undef CONFIG_BOOTCOMMAND
#define CONFIG_BOOTCOMMAND RKIMG_BOOTCOMMAND

#ifdef CONFIG_USB_FUNCTION_DFU
#define CONFIG_SET_DFU_ALT_INFO
#endif

#define DFU_ALT_BOOT_EMMC \
	"gpt raw 0x0 0x20000;" \
	"loader raw 0x20000 0xE0000;"\
	"uboot part 0 1;" \
	"boot part 0 2;" \
	"rootfs part 0 3;" \
	"userdata part 0 4\0"

#ifdef CONFIG_ANDROID_AB
#define DFU_ALT_BOOT_MTD_A \
	"gpt raw 0x0 0x20000;" \
	"loader raw 0x20000 0xE0000;"\
	"vnvm part vnvm;" \
	"uboot part uboot;" \
	"boot raw 0x700000 0x600000\0"

#define DFU_ALT_BOOT_MTD_B \
	"gpt raw 0x0 0x20000;" \
	"loader raw 0x20000 0xE0000;"\
	"vnvm part vnvm;" \
	"uboot part uboot;" \
	"boot raw 0xd00000 0x600000\0"
#else
#define DFU_ALT_BOOT_MTD \
	"gpt raw 0x0 0x20000;" \
	"loader raw 0x20000 0xE0000;"\
	"vnvm part vnvm;" \
	"uboot part uboot;" \
	"boot part boot;" \
	"rootfs partubi rootfs;" \
	"userdata partubi userdata\0"

#endif /* CONFIG_ANDROID_AB */
#endif /* CONFIG_SPL_BUILD */

/* 
 * TFTP speed up, by enable ip fragment, and set default blksize to MTU.
 * Use `env set tftpblocksize 16384` to override blksize, max CONFIG_NET_MAXDEFRAG.
 * MUST: CONFIG_TFTP_BLOCKSIZE <= CONFIG_NET_MAXDEFRAG
 */
#define CONFIG_IP_DEFRAG
/* ip fragment, CONFIG_NET_MAXDEFRAG , default 16384, max 65536 */
/* #define CONFIG_NET_MAXDEFRAG		16384 */
#define CONFIG_UDP_CHECKSUM
#define CONFIG_TFTP_BLOCKSIZE		1468

#endif /* __CONFIGS_RK3568_EVB_H */
