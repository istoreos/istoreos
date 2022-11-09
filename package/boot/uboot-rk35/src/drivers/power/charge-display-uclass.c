/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <command.h>
#include <common.h>
#include <dm.h>
#include <power/charge_display.h>

int charge_display_show(struct udevice *dev)
{
	const struct dm_charge_display_ops *ops = dev_get_driver_ops(dev);

	if (!ops || !ops->show)
		return -ENOSYS;

	return ops->show(dev);
}

int charge_display(void)
{
	struct udevice *dev;
	int ret;

	ret = uclass_get_device(UCLASS_CHARGE_DISPLAY, 0, &dev);
	if (ret) {
		debug("Get charge display failed, ret=%d\n", ret);
		return ret;
	}

	return charge_display_show(dev);
}

UCLASS_DRIVER(charge_display) = {
	.id	= UCLASS_CHARGE_DISPLAY,
	.name	= "charge_display",
};
