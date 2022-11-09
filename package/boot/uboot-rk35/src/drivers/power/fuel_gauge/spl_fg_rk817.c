// SPDX-License-Identifier:     GPL-2.0+
/*
 * (C) Copyright 2020 Rockchip Electronics Co., Ltd
 *
 */

#include <common.h>
#include <dm.h>
#include <i2c.h>
#include <power/fuel_gauge.h>

#define DIV(div)		((div) ? (div) : 1)
#define BAT_VOL_H		0x0078
#define BAT_VOL_L		0x0079
#define VCALIB0_H		0x0093
#define VCALIB0_L		0x0094
#define VCALIB1_H		0x0095
#define VCALIB1_L		0x0096
#define GG_CON			0x0056
#define VIRTUAL_POWER_VOL	3600
#define INSTANT_MODE		0x02

struct rk817_battery_device {
	struct udevice *dev;
	int voltage_k;
	int voltage_b;
	u32 virtual_power;
	u32 bat_res_up;
	u32 bat_res_down;
};

static u8 rk817_bat_read(struct rk817_battery_device *battery, u8 reg)
{
	int ret;
	u8 buf;

	ret = dm_i2c_read(battery->dev, reg, &buf, 1);
	if (ret) {
		printf("%s: read reg 0x%02x failed, ret=%d\n",
		       __func__, reg, ret);
		return ret;
	}

	return buf;
}

static int rk817_bat_write(struct rk817_battery_device *battery,
			    u8 reg, u8 buf)
{
	int ret;

	ret = dm_i2c_write(battery->dev, reg, &buf, 1);
	if (ret) {
		printf("%s: write reg 0x%02x failed, ret=%d\n",
		       __func__, reg, ret);
		return ret;
	}

	return 0;
}

static int rk817_bat_get_vaclib0(struct rk817_battery_device *battery)
{
	int val = 0;

	val |= rk817_bat_read(battery, VCALIB0_L) << 0;
	val |= rk817_bat_read(battery, VCALIB0_H) << 8;

	return val;
}

static int rk817_bat_get_vaclib1(struct rk817_battery_device *battery)
{
	int val = 0;

	val |= rk817_bat_read(battery, VCALIB1_L) << 0;
	val |= rk817_bat_read(battery, VCALIB1_H) << 8;

	return val;
}

static void rk817_bat_init_voltage_kb(struct rk817_battery_device *battery)
{
	int vcalib0, vcalib1;

	vcalib0 = rk817_bat_get_vaclib0(battery);
	vcalib1 = rk817_bat_get_vaclib1(battery);

	battery->voltage_k = (1050 - 600) * 1000 / DIV(vcalib1 - vcalib0);
	battery->voltage_b = 1050 - (battery->voltage_k * vcalib1) / 1000;
}

static int rk817_bat_get_battery_voltage(struct rk817_battery_device *battery)
{
	int vol, val = 0;

	val |= rk817_bat_read(battery, BAT_VOL_L) << 0;
	val |= rk817_bat_read(battery, BAT_VOL_H) << 8;
	vol = battery->voltage_k * val / 1000 + battery->voltage_b;

	return (vol * battery->bat_res_up / battery->bat_res_down + vol);
}

static int rk817_bat_update_get_voltage(struct udevice *dev)
{
	struct rk817_battery_device *battery = dev_get_priv(dev);

	if (!battery->virtual_power && battery->voltage_k)
		return rk817_bat_get_battery_voltage(battery);
	else
		return VIRTUAL_POWER_VOL;
}

static struct dm_fuel_gauge_ops fg_ops = {
	.get_voltage = rk817_bat_update_get_voltage,
};

static int rk817_fg_ofdata_to_platdata(struct udevice *dev)
{
	struct rk817_battery_device *battery = dev_get_priv(dev);

	battery->dev = dev;
	battery->bat_res_up = dev_read_u32_default(dev, "bat_res_up", -1);
	if (battery->bat_res_up < 0) {
		printf("can't read bat_res_up\n");
		return -EINVAL;
	}

	battery->bat_res_down = dev_read_u32_default(dev, "bat_res_down", -1);
	if (battery->bat_res_down < 0) {
		printf("can't read bat_res_down\n");
		return -EINVAL;
	}

	battery->virtual_power = dev_read_u32_default(dev, "virtual_power", -1);

	return 0;
}

static int rk817_fg_init(struct rk817_battery_device *battery)
{
	u8 val;

	val = rk817_bat_read(battery, GG_CON);
	if (!(val & INSTANT_MODE)) {
		val |= INSTANT_MODE;
		rk817_bat_write(battery, GG_CON, val);
	}

	rk817_bat_init_voltage_kb(battery);

	return 0;
}

static int rk817_fg_probe(struct udevice *dev)
{
	return rk817_fg_init(dev_get_priv(dev));
}

static const struct udevice_id rk817_battery_ids[] = {
	{ .compatible = "rk817,battery" },
	{ }
};

U_BOOT_DRIVER(rk817_fg) = {
	.name = "rk817_fg",
	.id = UCLASS_FG,
	.of_match = rk817_battery_ids,
	.probe = rk817_fg_probe,
	.ops = &fg_ops,
	.ofdata_to_platdata = rk817_fg_ofdata_to_platdata,
	.priv_auto_alloc_size = sizeof(struct rk817_battery_device),
};
