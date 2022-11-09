/*
 * (C) Copyright 2020 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef _power_delivery_H_
#define _power_delivery_H_

/* Capability */
#define FG_CAP_FUEL_GAUGE	BIT(0)
#define FG_CAP_CHARGER		BIT(1)

struct dm_power_delivery_ops {
	int (*get_voltage)(struct udevice *dev);
	int (*get_current)(struct udevice *dev);
	int (*get_online)(struct udevice *dev);
};

struct power_delivery_data {
	int voltage;
	int current;
	int online;
};

#ifdef CONFIG_DM_POWER_DELIVERY
int power_delivery_get_data(struct udevice *dev, struct power_delivery_data *pd_data);
#else
inline int power_delivery_get_data(struct udevice *dev,
				   struct power_delivery_data *pd_data)
{
	return -ENOSYS;
}
#endif
#endif
