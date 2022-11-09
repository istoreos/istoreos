/*
 * Copyright (c) 2018 Fuzhou Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:	GPL-2.0
 */

#ifndef __RKFLASH_BLK_H__
#define __RKFLASH_BLK_H__

enum flash_con_type {
	FLASH_CON_TYPE_NANDC = 0,
	FLASH_CON_TYPE_SFC,
	FLASH_CON_TYPE_MAX,
};

enum flash_type {
	FLASH_TYPE_NANDC_NAND = 0,
	FLASH_TYPE_SFC_NOR,
	FLASH_TYPE_SFC_NAND,
	FLASH_TYPE_MAX,
};

struct flash_operation {
	int id;
	int (*flash_init)(struct udevice *udev);
	u32 (*flash_get_capacity)(struct udevice *udev);
	int (*flash_read)(struct udevice *udev,
			  u32 start,
			  u32 blkcnt,
			  void *buffer);
	int (*flash_write)(struct udevice *udev,
			   u32 start,
			   u32 blkcnt,
			   const void *buffer);
	int (*flash_erase)(struct udevice *udev,
			   u32 start,
			   u32 blkcnt);
	int (*vendor_read)(struct blk_desc *dev_desc,
			   u32 start,
			   u32 blkcnt,
			   void *buffer);
	int (*vendor_write)(struct blk_desc *dev_desc,
			    u32 start,
			    u32 blkcnt,
			    void *buffer);
};

struct rkflash_dev {
	u8 reserved[128];
};

struct rkflash_info {
	void *ioaddr;
	u32 flash_con_type;
	u32 freq;
	u32 density;
	struct udevice *child_dev;
	struct rkflash_dev flash_dev_info;
	/*
	 * read() - read from a block device
	 *
	 * @start:	Start block number to read (0=first)
	 * @blkcnt:	Number of blocks to read
	 * @buffer:	Destination buffer for data read
	 * @return 0 is OK, -1 is error.
	 */
	int (*read)(struct udevice *udev,
		    u32 start,
		    u32 blkcnt,
		    void *buffer);
	/*
	 * write() - write to a block device
	 *
	 * @dev:	Device to write to
	 * @start:	Start block number to write (0=first)
	 * @blkcnt:	Number of blocks to write
	 * @buffer:	Source buffer for data to write
	 * @return 0 is OK, -1 is error.
	 */
	int (*write)(struct udevice *udev,
		     u32 start,
		     u32 blkcnt,
		     const void *buffer);
	/*
	 * erase() - erase a section of a block device
	 *
	 * @dev:	Device to (partially) erase
	 * @start:	Start block number to erase (0=first)
	 * @blkcnt:	Number of blocks to erase
	 * @return 0 is OK, -1 is error.
	 */
	int (*erase)(struct udevice *udev,
		     u32 start,
		     u32 blkcnt);
};

struct rkflash_uclass_priv {
	struct rkflash_info *ndev;
};

#endif /* __RKSFC_BLK_H__ */
