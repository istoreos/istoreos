/*
 * Copyright 2017 Rockchip Electronics Co., Ltd
 * Frank Wang <frank.wang@rock-chips.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __ROCKUSB_H__
#define __ROCKUSB_H__

#include <common.h>
#include <part.h>
#include <linux/usb/composite.h>

enum rkusb_cmd {
	RKUSB_TEST_UNIT_READY	= 0x00,
	RKUSB_READ_FLASH_ID	= 0x01,
	RKUSB_SET_DEVICE_ID	= 0x02,
	RKUSB_TEST_BAD_BLOCK	= 0x03,
	RKUSB_READ_10		= 0x04,
	RKUSB_WRITE_10		= 0x05,
	RKUSB_ERASE_10		= 0x06,
	RKUSB_WRITE_SPARE	= 0x07,
	RKUSB_READ_SPARE	= 0x08,
	RKUSB_ERASE_10_FORCE	= 0x0B,
	RKUSB_GET_VERSION	= 0x0C,
	RKUSB_LBA_READ_10	= 0x14,
	RKUSB_LBA_WRITE_10	= 0x15,
	RKUSB_ERASE_SYS_DISK	= 0x16,
	RKUSB_SDRAM_READ_10	= 0x17,
	RKUSB_SDRAM_WRITE_10	= 0x18,
	RKUSB_SDRAM_EXECUTE	= 0x19,
	RKUSB_READ_FLASH_INFO	= 0x1A,
	RKUSB_GET_CHIP_VER	= 0x1B,
	RKUSB_LOW_FORMAT	= 0x1C,
	RKUSB_SET_RESET_FLAG	= 0x1E,
	RKUSB_SPI_READ_10	= 0x21,
	RKUSB_SPI_WRITE_10	= 0x22,
	RKUSB_LBA_ERASE		= 0x25,
	RKUSB_VS_WRITE		= 0x26,
	RKUSB_VS_READ		= 0x27,
	RKUSB_GET_STORAGE_MEDIA = 0x2B,
	RKUSB_SESSION		= 0x30,
	RKUSB_READ_CAPACITY	= 0xAA,
	RKUSB_RESET		= 0xFF,
};

enum rkusb_rc {
	RKUSB_RC_ERROR		= -1,
	RKUSB_RC_CONTINUE	= 0,
	RKUSB_RC_FINISHED	= 1,
	RKUSB_RC_UNKNOWN_CMND	= 2,
};

#ifdef CONFIG_CMD_ROCKUSB
#define IS_RKUSB_UMS_DNL(name)	(!strncmp((name), "rkusb_ums_dnl", 13))
#else
#define IS_RKUSB_UMS_DNL(name)	0

struct fsg_buffhd;
struct fsg_dev;
struct fsg_common;
struct fsg_config;

static struct usb_descriptor_header *rkusb_fs_function[];
static struct usb_descriptor_header *rkusb_hs_function[];

static inline int rkusb_cmd_process(struct fsg_common *common,
				    struct fsg_buffhd *bh, int *reply)
{
	return -EPERM;
}
#endif

/* Wait at maximum 60 seconds for cable connection */
#define RKUSB_CABLE_READY_TIMEOUT	60
#define SECTOR_SIZE			0x200

#define RKUSB_READ_LIMIT_ADDR	        (32 * 2048)	/* 32MB */

struct rockusb {
	struct ums *ums;
	int ums_cnt;
};

#endif /* __ROCKUSB_H__ */
