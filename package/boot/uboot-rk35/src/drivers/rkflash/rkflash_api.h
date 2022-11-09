/*
 * Copyright (c) 2018 Fuzhou Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:	GPL-2.0
 */

#ifndef __RKFLASH_API_H
#define __RKFLASH_API_H

#define	FLASH_VENDOR_PART_START		8
#define	FLASH_VENDOR_PART_END		39	/* 8 + 8 * 4 - 1 */

#ifdef CONFIG_RKSFC_NOR
#include "sfc_nor.h"
#include "sfc.h"

int rksfc_nor_init(struct udevice *udev);
u32 rksfc_nor_get_capacity(struct udevice *udev);
int rksfc_nor_read(struct udevice *udev, u32 sec, u32 n_sec, void *p_data);
int rksfc_nor_write(struct udevice *udev,
		    u32 sec,
		    u32 n_sec,
		    const void *p_data);
int rksfc_nor_vendor_read(struct blk_desc *dev_desc,
			  u32 sec,
			  u32 n_sec,
			  void *p_data);
int rksfc_nor_vendor_write(struct blk_desc *dev_desc,
			   u32 sec,
			   u32 n_sec,
			   void *p_data);

#endif

#ifdef CONFIG_RKSFC_NAND
#include "sfc_nand.h"
#include "sfc.h"
#include "rk_sftl.h"
int rksfc_nand_init(struct udevice *udev);
u32 rksfc_nand_get_density(struct udevice *udev);
int rksfc_nand_read(struct udevice *udev, u32 index, u32 count, void *buf);
int rksfc_nand_write(struct udevice *udev,
		     u32 index,
		     u32 count,
		     const void *buf);
int rksfc_nand_vendor_read(struct blk_desc *dev_desc,
			   u32 sec,
			   u32 n_sec,
			   void *p_data);
int rksfc_nand_vendor_write(struct blk_desc *dev_desc,
			    u32 sec,
			    u32 n_sec,
			    void *p_data);
#endif

#ifdef CONFIG_RKNANDC_NAND
#include "flash.h"
#include "rk_sftl.h"
int rknand_flash_init(struct udevice *udev);
u32 rknand_flash_get_density(struct udevice *udev);
int rknand_flash_read(struct udevice *udev, u32 index, u32 count, void *buf);
int rknand_flash_write(struct udevice *udev,
		       u32 index,
		       u32 count,
		       const void *buf);
int rknand_flash_vendor_read(struct blk_desc *dev_desc,
			     u32 sec,
			     u32 n_sec,
			     void *p_data);
int rknand_flash_vendor_write(struct blk_desc *dev_desc,
			      u32 sec,
			      u32 n_sec,
			      void *p_data);

#endif
#endif
