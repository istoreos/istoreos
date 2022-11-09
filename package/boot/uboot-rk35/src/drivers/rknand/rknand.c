/*
 * Copyright (C) (C) Copyright 2016-2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <asm/arch/vendor.h>
#include <dm.h>
#include <dm/device-internal.h>
#include <dm/lists.h>
#include <dm/root.h>
#include "rknand.h"

struct blk_desc *rknand_get_blk_desc(struct rknand_dev *ndev)
{
	struct blk_desc *desc;
	struct udevice *dev;

	device_find_first_child(ndev->dev, &dev);
	if (!dev)
		return NULL;
	desc = dev_get_uclass_platdata(dev);

	return desc;
}

ulong rknand_bread(struct udevice *udev, lbaint_t start,
		       lbaint_t blkcnt, void *dst)
{
	struct blk_desc *block_dev = dev_get_uclass_platdata(udev);
	struct rknand_dev *ndev = dev_get_priv(udev->parent);
	int err;

	if (blkcnt == 0)
		return 0;

	if ((start + blkcnt) > block_dev->lba)
		return 0;

	if (ndev->read == NULL)
		return 0;

	err = ndev->read(0, (u32)start, (u32)blkcnt, dst);
	if (err)
		return err;

	return blkcnt;
}

ulong rknand_bwrite(struct udevice *udev, lbaint_t start,
		       lbaint_t blkcnt, const void *src)
{
	struct blk_desc *block_dev = dev_get_uclass_platdata(udev);
	struct rknand_dev *ndev = dev_get_priv(udev->parent);
	int err;

	if (blkcnt == 0)
		return 0;

	if ((start + blkcnt) > block_dev->lba)
		return 0;

	if (ndev->write == NULL)
		return 0;

	err = ndev->write(0, (u32)start, (u32)blkcnt, src);
	if (err)
		return err;

	return blkcnt;
}

ulong rknand_berase(struct udevice *udev, lbaint_t start,
			lbaint_t blkcnt)
{
	struct blk_desc *block_dev = dev_get_uclass_platdata(udev);
	struct rknand_dev *ndev = dev_get_priv(udev->parent);
	int err;

	if (blkcnt == 0)
		return 0;

	if ((start + blkcnt) > block_dev->lba)
		return 0;

	if (ndev->erase == NULL)
		return 0;

	err = ndev->erase(0, (u32)start, (u32)blkcnt);
	if (err)
		return err;

	return blkcnt;
}

int rkftl_nand_vendor_read(struct blk_desc *dev_desc,
			   u32 index,
			   u32 n_sec,
			   void *p_data)
{
	int ret;

	ret = ftl_vendor_read(index, n_sec, p_data);
	if (!ret)
		return n_sec;
	else
		return -EIO;
}

int rkftl_nand_vendor_write(struct blk_desc *dev_desc,
			    u32 index,
			    u32 n_sec,
			    void *p_data)
{
	int ret;

	ret = ftl_vendor_write(index, n_sec, p_data);
	if (!ret)
		return n_sec;
	else
		return -EIO;
}

int rknand_scan_namespace(void)
{
	struct uclass *uc;
	struct udevice *dev;
	int ret;

	ret = uclass_get(UCLASS_RKNAND, &uc);
	if (ret)
		return ret;

	uclass_foreach_dev(dev, uc) {
		debug("%s %d %p\n", __func__, __LINE__, dev);
		ret = device_probe(dev);
		if (ret)
			return ret;
	}

	return 0;
}

static int rknand_blk_bind(struct udevice *udev)
{
	struct udevice *bdev;
	int ret;

	ret = blk_create_devicef(udev, "rknand_blk", "blk",
				 IF_TYPE_RKNAND,
			0, 512, 0, &bdev);
	if (ret) {
		debug("Cannot create block device\n");
		return ret;
	}

	return 0;
}

static int rknand_blk_probe(struct udevice *udev)
{
	struct rknand_dev *ndev = dev_get_priv(udev->parent);
	struct blk_desc *desc = dev_get_uclass_platdata(udev);

	debug("%s %d %p ndev = %p %p\n", __func__, __LINE__,
	      udev, ndev, udev->parent);
	ndev->dev = udev;
	desc->if_type = IF_TYPE_RKNAND;
	desc->lba = ndev->density;
	desc->log2blksz = 9;
	desc->blksz = 512;
	desc->bdev = udev;
	desc->devnum = 0;
	sprintf(desc->vendor, "0x%.4x", 0x2207);
	memcpy(desc->product, "rknand", sizeof("rknand"));
	memcpy(desc->revision, "V1.00", sizeof("V1.00"));
	part_init(desc);
	return 0;
}

static int rockchip_nand_probe(struct udevice *udev)
{
	int ret;
	struct rknand_dev *ndev = dev_get_priv(udev);

	ndev->ioaddr = dev_read_addr_ptr(udev);
	ret = rk_ftl_init(ndev->ioaddr);
	if (!ret) {
		ndev->density = ftl_get_density(0);
		ndev->read = ftl_read;
		ndev->write = ftl_write;
		ndev->erase = ftl_discard;
#ifndef CONFIG_SPL_BUILD
#ifdef CONFIG_ROCKCHIP_VENDOR_PARTITION
		flash_vendor_dev_ops_register(rkftl_nand_vendor_read,
					      rkftl_nand_vendor_write);
#endif
#endif
	}

	return ret;
}

static const struct blk_ops rknand_blk_ops = {
	.read	= rknand_bread,
	.write	= rknand_bwrite,
	.erase	= rknand_berase,
};

static const struct udevice_id rockchip_nand_ids[] = {
	{ .compatible = "rockchip,rk-nandc" },
	{ }
};

U_BOOT_DRIVER(rknand_blk) = {
	.name		= "rknand_blk",
	.id		= UCLASS_BLK,
	.ops		= &rknand_blk_ops,
	.probe		= rknand_blk_probe,
};

UCLASS_DRIVER(rknand) = {
	.id		= UCLASS_RKNAND,
	.name		= "rknand",
	.flags		= DM_UC_FLAG_SEQ_ALIAS,
	.per_device_auto_alloc_size = sizeof(struct rknand_uclass_priv),
};

U_BOOT_DRIVER(rknand) = {
	.name		= "rknand",
	.id		= UCLASS_RKNAND,
	.of_match	= rockchip_nand_ids,
	.bind		= rknand_blk_bind,
	.probe		= rockchip_nand_probe,
	.priv_auto_alloc_size = sizeof(struct rknand_dev),
};

