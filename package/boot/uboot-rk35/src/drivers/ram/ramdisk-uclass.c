// SPDX-License-Identifier:     GPL-2.0+
/*
 * (C) Copyright 2018 Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <dm.h>
#include <ramdisk.h>
#include <dm/device-internal.h>
#include <dm/lists.h>
#include <dm/root.h>
#include <asm/arch/rk_atags.h>

DECLARE_GLOBAL_DATA_PTR;

static ulong ramdisk_bread(struct udevice *dev, lbaint_t start,
			   lbaint_t blkcnt, void *dst)
{
	const struct ramdisk_ops *ops = dev_get_driver_ops(dev->parent);
	struct blk_desc *desc = dev_get_uclass_platdata(dev);

	if (!blkcnt)
		return 0;

	if (!ops->read)
		return -ENOSYS;

	return ops->read(desc, start, blkcnt, dst);
}

static ulong ramdisk_bwrite(struct udevice *dev, lbaint_t start,
			    lbaint_t blkcnt, const void *src)
{
	const struct ramdisk_ops *ops = dev_get_driver_ops(dev->parent);
	struct blk_desc *desc = dev_get_uclass_platdata(dev);

	if (!blkcnt)
		return 0;

	if (!ops->write)
		return -ENOSYS;

	return ops->write(desc, start, blkcnt, src);
}

static ulong ramdisk_berase(struct udevice *dev,
			    lbaint_t start, lbaint_t blkcnt)
{
	const struct ramdisk_ops *ops = dev_get_driver_ops(dev->parent);
	struct blk_desc *desc = dev_get_uclass_platdata(dev);

	if (!blkcnt)
		return 0;

	if (!ops->erase)
		return -ENOSYS;

	return ops->erase(desc, start, blkcnt);
}

int dm_ramdisk_is_enabled(void)
{
	return (atags_is_available() && atags_get_tag(ATAG_RAM_PARTITION));
}

static const struct blk_ops ramdisk_blk_ops = {
	.read	= ramdisk_bread,
#ifndef CONFIG_SPL_BUILD
	.write	= ramdisk_bwrite,
	.erase	= ramdisk_berase,
#endif
};

U_BOOT_DRIVER(ramdisk_blk) = {
	.name		= "ramdisk_blk",
	.id		= UCLASS_BLK,
	.ops		= &ramdisk_blk_ops,
};

UCLASS_DRIVER(ramdisk) = {
	.id		= UCLASS_RAMDISK,
	.name		= "ramdisk",
	.flags		= DM_UC_FLAG_SEQ_ALIAS,
};
