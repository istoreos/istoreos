/*
 * (C) Copyright 2022 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <errno.h>
#include <dm.h>
#include <dm/device-internal.h>
#include <power/power_delivery/power_delivery.h>

DECLARE_GLOBAL_DATA_PTR;

int power_delivery_get_data(struct udevice *dev, struct power_delivery_data *pd_data)
{
	const struct dm_power_delivery_ops *ops = dev_get_driver_ops(dev);

	if (!ops || !ops->get_current || !ops->get_voltage || !ops->get_online)
		return -ENOSYS;

	pd_data->voltage = ops->get_voltage(dev);
	pd_data->current = ops->get_current(dev);
	pd_data->online = ops->get_online(dev);

	return 0;
}

UCLASS_DRIVER(power_delivery) = {
	.id		= UCLASS_PD,
	.name		= "power_delivery",
};
