// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2018 Fuzhou Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <console.h>
#include <dvfs.h>

int dvfs_apply(struct udevice *dev)
{
	const struct dm_dvfs_ops *ops = device_get_ops(dev);

	if (!ops->apply)
		return -ENOSYS;

	return ops->apply(dev);
}

int dvfs_repeat_apply(struct udevice *dev)
{
	const struct dm_dvfs_ops *ops = device_get_ops(dev);

	if (!ops->repeat_apply)
		return -ENOSYS;

	return ops->repeat_apply(dev);
}

int dvfs_init(bool apply)
{
	struct udevice *dev;
	int ret;

	ret = uclass_get_device(UCLASS_DVFS, 0, &dev);
	if (ret) {
		if (ret != -ENODEV)
			printf("DVFS: Get dvfs device failed, ret=%d\n", ret);
		return ret;
	}

	if (apply)
		return dvfs_apply(dev);

	return 0;
}

UCLASS_DRIVER(dvfs) = {
	.id	= UCLASS_DVFS,
	.name	= "dvfs",
};
