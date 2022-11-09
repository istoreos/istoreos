/* SPDX-License-Identifier:     GPL-2.0+ */
/*
 * (C) Copyright 2018 Rockchip Electronics Co., Ltd
 */

#ifndef __RAMDISK_H__
#define __RAMDISK_H__

struct ramdisk_ops {
	/*
	 * read() - read from a block device
	 *
	 * @desc:	Block descriptor
	 * @start:	Start block number to read
	 * @blkcnt:	Number of blocks to read
	 * @buffer:	Destination buffer for data read
	 *
	 * @return blkcnt is OK, otherwise is error.
	 */
	ulong (*read)(struct blk_desc *desc,
		      lbaint_t start, lbaint_t blkcnt, void *buffer);

	/*
	 * write() - write to a block device
	 *
	 * @desc:	Block descriptor
	 * @start:	Start block number to write
	 * @blkcnt:	Number of blocks to write
	 * @buffer:	Source buffer for data to write
	 *
	 * @return blkcnt is OK, otherwise is error.
	 */

	ulong (*write)(struct blk_desc *desc,
		       lbaint_t start, lbaint_t blkcnt, const void *buffer);
	/*
	 * erase() - erase a section of a block device
	 *
	 * @desc:	Block descriptor
	 * @start:	Start block number to erase
	 * @blkcnt:	Number of blocks to erase
	 *
	 * @return blkcnt is OK, otherwise is error.
	 */
	ulong (*erase)(struct blk_desc *desc, lbaint_t start, lbaint_t blkcnt);
};

int dm_ramdisk_is_enabled(void);

#endif /* __RAMDISK_H__ */
