/*
 * Copyright (c) 2018 Fuzhou Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:	GPL-2.0
 */

#include <common.h>
#include <dm.h>
#include <dm/device-internal.h>
#include <dm/lists.h>
#include <dm/root.h>

#include "rkflash_blk.h"
#include "rkflash_debug.h"

ulong rkflash_bread(struct udevice *udev, lbaint_t start,
		    lbaint_t blkcnt, void *dst)
{
	struct blk_desc *block_dev = dev_get_uclass_platdata(udev);
	struct rkflash_info *priv = dev_get_priv(udev->parent);

	debug("%s lba %x cnt %x\n", __func__, (u32)start, (u32)blkcnt);
	if (blkcnt == 0)
		return 0;

	if ((start + blkcnt) > block_dev->lba)
		return -EINVAL;

	if (!priv->read)
		return -EINVAL;

	return (ulong)priv->read(udev->parent, (u32)start, (u32)blkcnt, dst);
}

ulong rkflash_bwrite(struct udevice *udev, lbaint_t start,
		     lbaint_t blkcnt, const void *src)
{
	struct blk_desc *block_dev = dev_get_uclass_platdata(udev);
	struct rkflash_info *priv = dev_get_priv(udev->parent);

	if (blkcnt == 0)
		return 0;

	if ((start + blkcnt) > block_dev->lba)
		return -EINVAL;

	if (!priv->write)
		return -EINVAL;

	return (ulong)priv->write(udev->parent, (u32)start, (u32)blkcnt, src);
}

ulong rkflash_berase(struct udevice *udev, lbaint_t start,
		     lbaint_t blkcnt)
{
	struct blk_desc *block_dev = dev_get_uclass_platdata(udev);
	struct rkflash_info *priv = dev_get_priv(udev->parent);

	if (blkcnt == 0)
		return 0;

	if ((start + blkcnt) > block_dev->lba)
		return -EINVAL;

	if (!priv->erase)
		return -EINVAL;

	return (ulong)priv->erase(udev->parent, (u32)start, (u32)blkcnt);
}

static int rkflash_blk_probe(struct udevice *udev)
{
	struct rkflash_info *priv = dev_get_priv(udev->parent);
	struct blk_desc *desc = dev_get_uclass_platdata(udev);
	char *product;

	if (desc->if_type != priv->flash_con_type)
		return  -ENODEV;

	switch (priv->flash_con_type) {
	case IF_TYPE_RKNAND:
		product = "rkflash-NandFlash";
		break;
	case IF_TYPE_SPINAND:
		product = "rkflash-SpiNand";
		break;
	case IF_TYPE_SPINOR:
		product = "rkflash-SpiNor";
		break;
	default:
		product = "unknown";
		break;
	}
	debug("%s %d %p ndev = %p %p\n", __func__, __LINE__,
	      udev, priv, udev->parent);
	priv->child_dev = udev;
	desc->lba = priv->density;
	desc->log2blksz = 9;
	desc->bdev = udev;
	sprintf(desc->vendor, "0x%.4x", 0x0308);
	memcpy(desc->product, product, strlen(product));
	memcpy(desc->revision, "V1.00", sizeof("V1.00"));
	part_init(desc);
	rkflash_test(udev);

	return 0;
}

static const struct blk_ops rkflash_blk_ops = {
	.read	= rkflash_bread,
	.write	= rkflash_bwrite,
	.erase	= rkflash_berase,
};

U_BOOT_DRIVER(rkflash_blk) = {
	.name		= "rkflash_blk",
	.id		= UCLASS_BLK,
	.ops		= &rkflash_blk_ops,
	.probe		= rkflash_blk_probe,
};

