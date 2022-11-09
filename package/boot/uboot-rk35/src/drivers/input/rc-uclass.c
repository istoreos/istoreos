/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <dm.h>
#include <rc.h>

int rc_get_keycode(struct udevice *dev)
{
	const struct dm_rc_ops *ops = dev_get_driver_ops(dev);

	if (!ops || !ops->get_keycode)
		return -ENOSYS;

	return ops->get_keycode(dev);
}

int rc_get_repeat(struct udevice *dev)
{
	const struct dm_rc_ops *ops = dev_get_driver_ops(dev);

	if (!ops || !ops->get_repeat)
		return -ENOSYS;

	return ops->get_repeat(dev);
}

UCLASS_DRIVER(rc) = {
	.id		= UCLASS_RC,
	.name		= "rc",
};
