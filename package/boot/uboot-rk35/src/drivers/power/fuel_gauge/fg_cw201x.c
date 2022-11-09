/*
 * (C) Copyright 2008-2015 Fuzhou Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#include <common.h>
#include <asm/gpio.h>
#include <dm.h>
#include <dm/device.h>
#include <errno.h>
#include <fdtdec.h>
#include <i2c.h>
#include <linux/usb/phy-rockchip-usb2.h>
#include <malloc.h>
#include <power/battery.h>
#include <power/fuel_gauge.h>
#include <power/pmic.h>
#include "fg_regs.h"

DECLARE_GLOBAL_DATA_PTR;

#define COMPAT_ROCKCHIP_CW201X "cw201x"

#define REG_VERSION		0x0
#define REG_VCELL		0x2
#define REG_SOC			0x4
#define REG_RRT_ALERT		0x6
#define REG_CONFIG		0x8
#define REG_MODE		0xA
#define REG_BATINFO		0x10

#define MODE_SLEEP_MASK		(0x3 << 6)
#define MODE_SLEEP		(0x3 << 6)
#define MODE_NORMAL		(0x0 << 6)
#define MODE_QUICK_START	(0x3 << 4)
#define MODE_RESTART		(0xf << 0)

#define CONFIG_UPDATE_FLG	(0x1 << 1)
#define ATHD			(0x0 << 3)

enum charger_type {
	CHARGER_TYPE_NO = 0,
	CHARGER_TYPE_USB,
	CHARGER_TYPE_AC,
	CHARGER_TYPE_DC,
	CHARGER_TYPE_UNDEF,
};

struct cw201x_info {
	struct udevice *dev;
	int capacity;
	u32 *cw_bat_config_info;
	int divider_res1;
	int divider_res2;
	int hw_id_check;
	struct gpio_desc hw_id0;
	struct gpio_desc hw_id1;
	int support_dc_adp;
	struct gpio_desc dc_det_gpio;
	int dc_det_flag;
	bool dual_cell;
};

static u8 cw201x_read(struct cw201x_info *cw201x, u8 reg)
{
	u8 val;
	int ret;

	ret = dm_i2c_read(cw201x->dev, reg, &val, 1);
	if (ret) {
		debug("write error to device: %p register: %#x!",
		      cw201x->dev, reg);
		return ret;
	}

	return val;
}

static int cw201x_write(struct cw201x_info *cw201x, u8 reg, u8 val)
{
	int ret;

	ret = dm_i2c_write(cw201x->dev, reg, &val, 1);
	if (ret) {
		debug("write error to device: %p register: %#x!",
		      cw201x->dev, reg);
		return ret;
	}

	return 0;
}

static u16 cw201x_read_half_word(struct cw201x_info *cw201x, int reg)
{
	u8 vall, valh;
	u16 val;

	valh = cw201x_read(cw201x, reg);
	vall = cw201x_read(cw201x, reg + 1);
	val = ((u16)valh << 8) | vall;

	return val;
}

static int cw201x_parse_config_info(struct cw201x_info *cw201x)
{
	int ret;
	int i, len, size;
	const u8 *info;
	struct udevice *dev = cw201x->dev;

	if (dev_read_prop(dev, "bat_config_info", &len)) {
		len /= sizeof(u32);
		size = sizeof(*cw201x->cw_bat_config_info) * len;
		cw201x->cw_bat_config_info = calloc(size, 1);
		if (!cw201x->cw_bat_config_info) {
			debug("calloc cw_bat_config_info fail\n");
			return -EINVAL;
		}
		ret = dev_read_u32_array(dev, "bat_config_info",
					 cw201x->cw_bat_config_info, len);
		if (ret) {
			debug("fdtdec_get cw_bat_config_info fail\n");
			return -EINVAL;
		}

		return 0;
	}

	if (!dev_read_prop(dev, "cellwise,battery-profile", &len))
		return -EINVAL;

	size = sizeof(*cw201x->cw_bat_config_info) * len;
	cw201x->cw_bat_config_info = calloc(size, 1);
	if (!cw201x->cw_bat_config_info) {
		debug("calloc cw_bat_config_info fail\n");
		return -EINVAL;
	}

	info = dev_read_u8_array_ptr(dev, "cellwise,battery-profile", len);
	if (!info) {
		debug("fdtdec_get battery profile fail\n");
		return -EINVAL;
	}
	for (i = 0; i < len; i++) {
		cw201x->cw_bat_config_info[i] = info[i];
		debug("%#x ", cw201x->cw_bat_config_info[i]);
		if ((i+1) % 8 == 0)
			debug("\n");
	}

	return 0;
}

static int cw201x_ofdata_to_platdata(struct udevice *dev)
{
	struct cw201x_info *cw201x = dev_get_priv(dev);
	int ret;
	int hw_id0_val, hw_id1_val;

	cw201x->dev = dev;
	ret = cw201x_parse_config_info(cw201x);
	if (ret)
		return ret;

	cw201x->dual_cell = dev_read_bool(dev, "cellwise,dual-cell");
	ret = gpio_request_by_name_nodev(dev_ofnode(dev), "dc_det_gpio",
					 0, &cw201x->dc_det_gpio, GPIOD_IS_IN);
	if (!ret) {
		cw201x->support_dc_adp = 1;
		debug("DC is valid\n");
	} else {
		debug("DC is invalid, ret=%d\n", ret);
	}

	cw201x->hw_id_check = dev_read_u32_default(dev, "hw_id_check", 0);
	if (cw201x->hw_id_check) {
		ret = gpio_request_by_name_nodev(dev_ofnode(dev),
						 "hw_id0_gpio", 0,
						 &cw201x->hw_id0, GPIOD_IS_IN);
		if (ret)
			return -EINVAL;
		hw_id0_val = dm_gpio_get_value(&cw201x->hw_id0);

		ret = gpio_request_by_name_nodev(dev_ofnode(dev),
						 "hw_id1_gpio", 0,
						 &cw201x->hw_id1, GPIOD_IS_IN);
		if (ret)
			return -EINVAL;
		hw_id1_val = dm_gpio_get_value(&cw201x->hw_id1);

		/* ID1 = 0, ID0 = 1 : Battery */
		if (!hw_id0_val || hw_id1_val)
			return -EINVAL;
	}

	cw201x->divider_res1 = dev_read_u32_default(dev, "divider_res1", 0);
	cw201x->divider_res2 = dev_read_u32_default(dev, "divider_res2", 0);

	return 0;
}

static int cw201x_get_vol(struct cw201x_info *cw201x)
{
	u16 value16, value16_1, value16_2, value16_3;
	int voltage;
	int res1, res2;
	int retry = 0;

__retry:
	value16 = cw201x_read_half_word(cw201x, REG_VCELL);
	if (value16 < 0)
		return -1;

	value16_1 = cw201x_read_half_word(cw201x, REG_VCELL);
	if (value16_1 < 0)
		return -1;

	value16_2 = cw201x_read_half_word(cw201x, REG_VCELL);
	if (value16_2 < 0)
		return -1;

	if (value16 > value16_1) {
		value16_3 = value16;
		value16 = value16_1;
		value16_1 = value16_3;
	}

	if (value16_1 > value16_2) {
		value16_3 = value16_1;
		value16_1 = value16_2;
		value16_2 = value16_3;
	}

	if (value16 > value16_1) {
		value16_3 = value16;
		value16 = value16_1;
		value16_1 = value16_3;
	}

	voltage = value16_1 * 312 / 1024;
	if (voltage <= 0 && retry < 10) {
		retry++;
		mdelay(20);
		goto __retry;
	}

	if (cw201x->divider_res1 &&
	    cw201x->divider_res2) {
		res1 = cw201x->divider_res1;
		res2 = cw201x->divider_res2;
		voltage = voltage * (res1 + res2) / res2;
	}

	if (cw201x->dual_cell)
		voltage *= 2;

	debug("the cw201x voltage=%d\n", voltage);
	return voltage;
}

static int cw201x_dwc_otg_check_dpdm(void)
{
#if defined(CONFIG_PHY_ROCKCHIP_INNO_USB2) && !defined(CONFIG_SPL_BUILD)
	return rockchip_chg_get_type();
#else
	debug("rockchip_chg_get_type() is not implement\n");
	return CHARGER_TYPE_NO;
#endif
}

static int cw201x_get_usb_state(struct cw201x_info *cw201x)
{
	int charger_type;

	switch (cw201x_dwc_otg_check_dpdm()) {
	case 0:
		charger_type = CHARGER_TYPE_NO;
		break;
	case 1:
	case 3:
		charger_type = CHARGER_TYPE_USB;
		break;
	case 2:
		charger_type = CHARGER_TYPE_AC;
		break;
	default:
		charger_type = CHARGER_TYPE_NO;
		break;
	}

	return charger_type;
}

static bool cw201x_get_dc_state(struct cw201x_info *cw201x)
{
	if (dm_gpio_get_value(&cw201x->dc_det_gpio))
		return true;

	return false;
}

static bool cw201x_check_charge(struct cw201x_info *cw201x)
{
	if (cw201x_get_usb_state(cw201x) != CHARGER_TYPE_NO)
		return true;
	if (cw201x_get_dc_state(cw201x))
		return true;

	return false;
}

static int cw201x_get_soc(struct cw201x_info *cw201x)
{
	int cap, i = 0;

	while (i < 10) {
		cap = cw201x_read(cw201x, REG_SOC);
		if ((cap < 0) || (cap > 100))
			cap = cw201x->capacity;
		i++;
		if (cap)
			break;
	}
	cw201x->capacity = cap;

	return cw201x->capacity;
}

static int cw201x_update_get_soc(struct udevice *dev)
{
	struct cw201x_info *cw201x = dev_get_priv(dev);

	return cw201x_get_soc(cw201x);
}

static int cw201x_update_get_voltage(struct udevice *dev)
{
	struct cw201x_info *cw201x = dev_get_priv(dev);

	return cw201x_get_vol(cw201x);
}

static int cw201x_update_get_current(struct udevice *dev)
{
	return 0;
}

static bool cw201x_update_get_chrg_online(struct udevice *dev)
{
	struct cw201x_info *cw201x = dev_get_priv(dev);

	return cw201x_check_charge(cw201x);
}

static int cw201x_capability(struct udevice *dev)
{
	return FG_CAP_FUEL_GAUGE;
}

static struct dm_fuel_gauge_ops cw201x_fg_ops = {
	.capability = cw201x_capability,
	.get_soc = cw201x_update_get_soc,
	.get_voltage = cw201x_update_get_voltage,
	.get_current = cw201x_update_get_current,
	.get_chrg_online = cw201x_update_get_chrg_online,
};

static int cw201x_fg_cfg(struct cw201x_info *cw201x)
{
	u8 val = MODE_SLEEP;
	int i;

	if ((val & MODE_SLEEP_MASK) == MODE_SLEEP) {
		val = MODE_NORMAL;
		cw201x_write(cw201x, REG_MODE, val);
	}

	for (i = 0; i < 64; i++) {
		cw201x_write(cw201x, REG_BATINFO + i,
			     (u8)cw201x->cw_bat_config_info[i]);
	}

	return 0;
}

static int cw201x_fg_probe(struct udevice *dev)
{
	struct cw201x_info *cw201x = dev_get_priv(dev);

	cw201x->dev = dev;
	cw201x_fg_cfg(cw201x);

	debug("vol: %d, soc: %d\n",
	      cw201x_get_vol(cw201x), cw201x_get_soc(cw201x));

	return 0;
}

static const struct udevice_id cw201x_ids[] = {
	{ .compatible = "cw201x" },
	{ .compatible = "cellwise,cw2015" },
	{ }
};

U_BOOT_DRIVER(cw201x_fg) = {
	.name = "cw201x_fg",
	.id = UCLASS_FG,
	.of_match = cw201x_ids,
	.probe = cw201x_fg_probe,
	.ofdata_to_platdata = cw201x_ofdata_to_platdata,
	.ops = &cw201x_fg_ops,
	.priv_auto_alloc_size = sizeof(struct cw201x_info),
};
