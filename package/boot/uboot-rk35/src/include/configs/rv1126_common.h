/*
 * (C) Copyright 2019 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef __CONFIG_RV1126_COMMON_H
#define __CONFIG_RV1126_COMMON_H

#include "rockchip-common.h"

#define COUNTER_FREQUENCY		24000000
#define CONFIG_SYS_MALLOC_LEN		(32 << 20)
#define CONFIG_SYS_CBSIZE		1024
#define CONFIG_SKIP_LOWLEVEL_INIT
#define CONFIG_SYS_NS16550_MEM32

#ifdef CONFIG_SUPPORT_USBPLUG
#define CONFIG_SYS_TEXT_BASE		0x00000000
#else
#define CONFIG_SYS_TEXT_BASE		0x00600000
#endif

#define CONFIG_SYS_INIT_SP_ADDR		0x00800000
#define CONFIG_SYS_LOAD_ADDR		0x00e00800
#define CONFIG_SYS_BOOTM_LEN		(64 << 20)

/* SPL */
#define CONFIG_SPL_FRAMEWORK
#define CONFIG_SPL_TEXT_BASE		0x00000000
#define CONFIG_SPL_MAX_SIZE		0x30000
#define CONFIG_SPL_BSS_START_ADDR	0x00600000
#define CONFIG_SPL_BSS_MAX_SIZE		0x20000
#define CONFIG_SPL_STACK		0x00600000

#define GICD_BASE			0xfeff1000
#define GICC_BASE			0xfeff2000

/* secure boot otp rollback */
#define OTP_UBOOT_ROLLBACK_OFFSET	0x68
#define OTP_UBOOT_ROLLBACK_WORDS	2	/* 64 bits, 2 words */
#define OTP_ALL_ONES_NUM_BITS		32
#define OTP_SECURE_BOOT_ENABLE_ADDR	0x0
#define OTP_SECURE_BOOT_ENABLE_SIZE	1
#define OTP_RSA_HASH_ADDR		0x10
#define OTP_RSA_HASH_SIZE		32

/* MMC/SD IP block */
#define CONFIG_BOUNCE_BUFFER

/* Nand */
#define CONFIG_SYS_MAX_NAND_DEVICE	1
#define CONFIG_SYS_NAND_ONFI_DETECTION
#define CONFIG_SYS_NAND_PAGE_SIZE	2048
#define CONFIG_SYS_NAND_PAGE_COUNT	64
#define CONFIG_SYS_NAND_SIZE		(256 * 1024 * 1024)
#define CONFIG_SYS_NAND_U_BOOT_OFFS	0x4000

#define CONFIG_SYS_SDRAM_BASE		0
#define SDRAM_MAX_SIZE			0xfd000000

#define CONFIG_PERIPH_DEVICE_START_ADDR	(CONFIG_SYS_SDRAM_BASE + SDRAM_MAX_SIZE)
#define CONFIG_PERIPH_DEVICE_END_ADDR	SZ_4G

#define CONFIG_SYS_NONCACHED_MEMORY    (1 << 20)       /* 1 MiB */
#ifndef CONFIG_SPL_BUILD

/* usb mass storage */
#define CONFIG_USB_FUNCTION_MASS_STORAGE
#define CONFIG_ROCKUSB_G_DNL_PID	0x110b

/* memory size <= 128MB,  TEE: 0x3000000 - 0x3200000 */
#define ENV_MEM_LAYOUT_SETTINGS1	\
	"scriptaddr1=0x00000000\0"	\
	"pxefile_addr1_r=0x00100000\0"	\
	"fdt_addr1_r=0x02f00000\0"	\
	"kernel_addr1_r=0x02008000\0"	\
	"ramdisk_addr1_r=0x03200000\0"

/* memory size > 128MB */
#define ENV_MEM_LAYOUT_SETTINGS		\
	"scriptaddr=0x00000000\0"	\
	"pxefile_addr_r=0x00100000\0"	\
	"fdt_addr_r=0x08300000\0"	\
	"kernel_addr_r=0x02008000\0"	\
	"ramdisk_addr_r=0x0a200000\0"

#include <config_distro_bootcmd.h>
#define CONFIG_EXTRA_ENV_SETTINGS	\
	ENV_MEM_LAYOUT_SETTINGS		\
	ENV_MEM_LAYOUT_SETTINGS1	\
	"partitions=" PARTS_DEFAULT	\
	ROCKCHIP_DEVICE_SETTINGS	\
	RKIMG_DET_BOOTDEV		\
	BOOTENV_SHARED_RKNAND		\
	BOOTENV

#undef RKIMG_BOOTCOMMAND
#ifdef CONFIG_FIT_SIGNATURE
#define RKIMG_BOOTCOMMAND		\
	"boot_fit;"
#else
#define RKIMG_BOOTCOMMAND		\
	"boot_fit;"			\
	"boot_android ${devtype} ${devnum};"
#endif
#endif

#define CONFIG_PREBOOT

#endif
