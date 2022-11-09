/*
 * Copyright (C) (C) Copyright 2016-2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __DRIVER_RKNAND_H__
#define __DRIVER_RKNAND_H__

#include <asm/io.h>
#include <clk.h>
#include <asm/arch/clock.h>

/* Represents an NVM Express device. Each nvme_dev is a PCI function. */
struct rknand_dev {
	void *ioaddr;
	struct clk nandc_clk;
	struct clk nandc_hclk;
	u32 density;
	struct udevice *dev;

	/*
	 * read() - read from a block device
	 *
	 * @start:	Start block number to read (0=first)
	 * @blkcnt:	Number of blocks to read
	 * @buffer:	Destination buffer for data read
	 * @return 0 is OK, -1 is error.
	 */
	u32 (*read)(u8 lun, u32 start, u32 blkcnt, void *buffer);
	/*
	 * write() - write to a block device
	 *
	 * @dev:	Device to write to
	 * @start:	Start block number to write (0=first)
	 * @blkcnt:	Number of blocks to write
	 * @buffer:	Source buffer for data to write
	 * @return 0 is OK, -1 is error.
	 */
	u32 (*write)(u8 lun, u32 start, u32 blkcnt, const void *buffer);
	/*
	 * erase() - erase a section of a block device
	 *
	 * @dev:	Device to (partially) erase
	 * @start:	Start block number to erase (0=first)
	 * @blkcnt:	Number of blocks to erase
	 * @return 0 is OK, -1 is error.
	 */
	u32 (*erase)(u8 lun, u32 start, u32 blkcnt);
};

struct rknand_uclass_priv {
	struct rknand_dev *ndev;
};

u32 ftl_write(u8 lun, u32 start, u32 blkcnt, const void *buffer);
u32 ftl_read(u8 lun, u32 start, u32 blkcnt, void *buffer);
u32 ftl_discard(u8 lun, u32 start, u32 blkcnt);
u32 ftl_get_density(u8 lun);
int rk_ftl_init(u32 *reg_base);
u32 ftl_vendor_read(u32 index, u32 nsec, void *buf);
u32 ftl_vendor_write(u32 index, u32 nsec, void *buf);
#endif /* __DRIVER_RKNAND_H__ */
