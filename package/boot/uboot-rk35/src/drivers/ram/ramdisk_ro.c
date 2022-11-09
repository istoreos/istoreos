// SPDX-License-Identifier:     GPL-2.0+
/*
 * (C) Copyright 2018 Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <dm.h>
#include <dm/device-internal.h>
#include <dm/lists.h>
#include <dm/root.h>
#include <ramdisk.h>

DECLARE_GLOBAL_DATA_PTR;

static ulong ramdisk_ro_bread(struct blk_desc *desc, lbaint_t start,
			      lbaint_t blkcnt, void *dst)
{
	unsigned long b_size, b_start;

	/* Byte */
	b_start = start * desc->blksz;
	b_size = blkcnt * desc->blksz;

	if ((ulong)dst != (ulong)b_start)
		memcpy((char *)dst, (char *)b_start, b_size);
	else
		debug("%s: skip memcpy at: 0x%08lx\n", __func__, (ulong)b_start);

	debug("%s: b_start=0x%lx, b_size=0x%lx. dst=%p\n",
	      __func__, b_start, b_size, dst);

	return blkcnt;
}

static int ramdisk_ro_bind(struct udevice *dev)
{
	struct udevice *bdev;
	int ret;

	ret = blk_create_devicef(dev, "ramdisk_blk", "blk",
				 IF_TYPE_RAMDISK, 0, 512, 0, &bdev);
	if (ret) {
		debug("Can't create block device\n");
		return ret;
	}

	return 0;
}

static const struct ramdisk_ops ramdisk_ro_ops = {
	.read = ramdisk_ro_bread,
};

static const struct udevice_id ramdisk_ro_ids[] = {
	{ .compatible = "ramdisk-ro" },
	{ }
};

U_BOOT_DRIVER(ramdisk_ro) = {
	.name		= "ramdisk-ro",
	.id		= UCLASS_RAMDISK,
	.ops		= &ramdisk_ro_ops,
	.of_match	= ramdisk_ro_ids,
	.bind		= ramdisk_ro_bind,
};

U_BOOT_DEVICE(ramdisk_ro) = {
	.name		= "ramdisk-ro",
};
