// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2018 Fuzhou Rockchip Electronics Co., Ltd
 */
#include <common.h>
#include <dm.h>
#include <errno.h>
#include <asm/gpio.h>
#include <power/regulator.h>
#include <i2c.h>
#include <asm/arch-rockchip/clock.h>
#include <asm/io.h>
#include <syscon.h>

DECLARE_GLOBAL_DATA_PTR;

/* Voltage setting */
#define FAN53555_VSEL0		0x00
#define FAN53555_VSEL1		0x01

#define TCS452X_VSEL0		0x11
#define TCS452X_VSEL1		0x10
#define TCS452X_TIME		0x13
#define TCS452X_COMMAND		0x14

/* Control register */
#define FAN53555_CONTROL	0x02
/* IC Type */
#define FAN53555_ID1		0x03
/* IC mask version */
#define FAN53555_ID2		0x04
/* Monitor register */
#define FAN53555_MONITOR	0x05

/* VSEL bit definitions */
#define VSEL_BUCK_EN		BIT(7)
#define VSEL_MODE		BIT(6)
#define VSEL_NSEL_MASK		0x3F

/* Chip ID and Version */
#define DIE_ID			0x0F/* ID1 */
#define DIE_REV			0x0F/* ID2 */
/* Control bit definitions */
#define CTL_OUTPUT_DISCHG	BIT(7)
#define CTL_SLEW_MASK		(0x7 << 4)
#define CTL_SLEW_SHIFT		4
#define CTL_RESET		BIT(2)

#define TCS_VSEL_NSEL_MASK	0x7f
#define TCS_VSEL0_MODE		BIT(7)
#define TCS_VSEL1_MODE		BIT(6)

#define TCS_SLEW_SHIFT		3
#define TCS_SLEW_MASK		(0x3 < 3)

#define FAN53555_NVOLTAGES_64	64/* Numbers of voltages */
#define FAN53555_NVOLTAGES_127	127/* Numbers of voltages */

enum fan53555_vendor {
	FAN53555_VENDOR_FAIRCHILD = 0,
	FAN53555_VENDOR_SILERGY,
	FAN53555_VENDOR_TCS,
};

/* IC Type */
enum {
	FAN53555_CHIP_ID_00 = 0,
	FAN53555_CHIP_ID_01,
	FAN53555_CHIP_ID_02,
	FAN53555_CHIP_ID_03,
	FAN53555_CHIP_ID_04,
	FAN53555_CHIP_ID_05,
	FAN53555_CHIP_ID_08 = 8,
};

/* IC mask revision */
enum {
	FAN53555_CHIP_REV_00 = 0x3,
	FAN53555_CHIP_REV_13 = 0xf,
};

enum {
	SILERGY_SYR82X = 8,
};

enum {
	FAN53555_VSEL_ID_0 = 0,
	FAN53555_VSEL_ID_1,
};

struct fan53555_regulator_info {
	enum fan53555_vendor vendor;
	struct udevice *dev;
	/* IC Type and Rev */
	int chip_id;
	int chip_rev;
	/* Voltage setting register */
	unsigned int vol_reg;
	unsigned int sleep_reg;
	unsigned int mode_reg;
	unsigned int vol_mask;
	unsigned int mode_mask;
	/* Voltage range and step(linear) */
	unsigned int vsel_min;
	unsigned int vsel_step;
	struct gpio_desc vsel_gpio;
	unsigned int sleep_vsel_id;
};

static int fan53555_write(struct udevice *dev, uint reg, const uint8_t *buff,
			  int len)
{
	int ret;

	ret = dm_i2c_write(dev, reg, buff, len);
	if (ret) {
		debug("%s: write reg 0x%02x failed, ret=%d\n",
		      __func__, reg, ret);
		return ret;
	}

	return 0;
}

static int fan53555_read(struct udevice *dev, uint reg, uint8_t *buff, int len)
{
	int ret;

	ret = dm_i2c_read(dev, reg, buff, len);
	if (ret) {
		debug("%s: read reg 0x%02x failed, ret=%d\n",
		      __func__, reg, ret);
		return ret;
	}

	return 0;
}

int fan53555_reg_read(struct udevice *dev, uint reg)
{
	u8 byte;
	int ret;

	debug("%s: reg=%x", __func__, reg);
	ret = fan53555_read(dev, reg, &byte, 1);
	debug(", value=%x, ret=%d\n", byte, ret);

	return ret ? ret : byte;
}

int fan53555_reg_write(struct udevice *dev, uint reg, uint value)
{
	u8 byte = value;
	int ret;

	debug("%s: reg=%x, value=%x", __func__, reg, value);
	ret = fan53555_write(dev, reg, &byte, 1);
	debug(", ret=%d\n", ret);

	return ret;
}

int  fan53555_clrsetbits(struct udevice *dev, uint reg, uint clr, uint set)
{
	u8 byte;
	int ret;

	ret = fan53555_reg_read(dev, reg);
	if (ret < 0)
		return ret;
	byte = (ret & ~clr) | set;

	return fan53555_reg_write(dev, reg, byte);
}

static int fan53555_regulator_set_enable(struct udevice *dev, bool enable)
{
	struct fan53555_regulator_info *priv = dev_get_priv(dev);
	int val, sleep_vsel_id;

	if (enable) {
		val = VSEL_BUCK_EN;
		sleep_vsel_id = !priv->sleep_vsel_id;
	} else {
		val = 0;
		sleep_vsel_id = priv->sleep_vsel_id;
	}

	if (dm_gpio_is_valid(&priv->vsel_gpio)) {
		dm_gpio_set_value(&priv->vsel_gpio, sleep_vsel_id);
		return 0;
	}
	fan53555_clrsetbits(dev, priv->vol_reg, VSEL_BUCK_EN, val);

	return 0;
}

static int fan53555_regulator_get_enable(struct udevice *dev)
{
	struct fan53555_regulator_info *priv = dev_get_priv(dev);
	int val;

	if (dm_gpio_is_valid(&priv->vsel_gpio)) {
		if (priv->sleep_vsel_id)
			return !dm_gpio_get_value(&priv->vsel_gpio);
		else
			return dm_gpio_get_value(&priv->vsel_gpio);
	}

	val = fan53555_reg_read(dev, priv->vol_reg);
	if (val & VSEL_BUCK_EN)
		return 1;
	else
		return 0;
}

static int fan53555_regulator_set_suspend_enable(struct udevice *dev,
						 bool enable)
{
	struct fan53555_regulator_info *priv = dev_get_priv(dev);
	int val;

	if (enable)
		val = VSEL_BUCK_EN;
	else
		val = 0;

	fan53555_clrsetbits(dev, priv->sleep_reg, VSEL_BUCK_EN, val);

	return 0;
}

static int fan53555_regulator_get_suspend_enable(struct udevice *dev)
{
	struct fan53555_regulator_info *priv = dev_get_priv(dev);
	int val;

	val = fan53555_reg_read(dev, priv->sleep_reg);
	if (val & VSEL_BUCK_EN)
		return 1;
	else
		return 0;
}

static int fan53555_regulator_get_voltage(struct udevice *dev)
{
	struct fan53555_regulator_info *priv = dev_get_priv(dev);
	int uvolt = 0, val;

	val = fan53555_reg_read(dev, priv->vol_reg);
	val &= priv->vol_mask;
	uvolt = (val * priv->vsel_step) + priv->vsel_min;

	return uvolt;
}

static int fan53555_regulator_set_voltage(struct udevice *dev, int uvolt)
{
	struct fan53555_regulator_info *priv = dev_get_priv(dev);
	int val;

	val = ((uvolt - priv->vsel_min) / priv->vsel_step);
	fan53555_clrsetbits(dev, priv->vol_reg, priv->vol_mask, val);

	return 0;
}

static int fan53555_regulator_get_suspend_voltage(struct udevice *dev)
{
	struct fan53555_regulator_info *priv = dev_get_priv(dev);
	int uvolt = 0, val;

	val = fan53555_reg_read(dev, priv->sleep_reg);
	val &= priv->vol_mask;
	uvolt = (val * priv->vsel_step) + priv->vsel_min;

	return uvolt;
}

static int fan53555_regulator_set_suspend_voltage(struct udevice *dev,
						  int uvolt)
{
	struct fan53555_regulator_info *priv = dev_get_priv(dev);
	int val;

	val = ((uvolt - priv->vsel_min) / priv->vsel_step);
	fan53555_clrsetbits(dev, priv->sleep_reg, priv->vol_mask, val);

	return 0;
}

static int fan53555_voltages_setup_fairchild(struct fan53555_regulator_info *di)
{
	/* Init voltage range and step */
	switch (di->chip_id) {
	case FAN53555_CHIP_ID_00:
		switch (di->chip_rev) {
		case FAN53555_CHIP_REV_00:
			di->vsel_min = 600000;
			di->vsel_step = 10000;
			break;
		case FAN53555_CHIP_REV_13:
			di->vsel_min = 800000;
			di->vsel_step = 10000;
			break;
		default:
			dev_err(di->dev,
				"Chip ID %d with rev %d not supported!\n",
				di->chip_id, di->chip_rev);
			return -EINVAL;
		}
		break;
	case FAN53555_CHIP_ID_01:
	case FAN53555_CHIP_ID_03:
	case FAN53555_CHIP_ID_05:
	case FAN53555_CHIP_ID_08:
		di->vsel_min = 600000;
		di->vsel_step = 10000;
		break;
	case FAN53555_CHIP_ID_04:
		di->vsel_min = 603000;
		di->vsel_step = 12826;
		break;
	default:
		dev_err(di->dev,
			"Chip ID %d not supported!\n", di->chip_id);
		return -EINVAL;
	}
	di->vol_mask = VSEL_NSEL_MASK;

	return 0;
}

static int fan53555_voltages_setup_silergy(struct fan53555_regulator_info *di)
{
	/* Init voltage range and step */
	di->vsel_min = 712500;
	di->vsel_step = 12500;
	di->vol_mask = VSEL_NSEL_MASK;

	return 0;
}

static int fan53555_voltages_setup_tcs(struct fan53555_regulator_info *di)
{
	if (di->sleep_vsel_id) {
		di->sleep_reg = TCS452X_VSEL1;
		di->vol_reg = TCS452X_VSEL0;
	} else {
		di->sleep_reg = TCS452X_VSEL0;
		di->vol_reg = TCS452X_VSEL1;
	}

	di->vol_mask = TCS_VSEL_NSEL_MASK;

	/* Init voltage range and step */
	di->vsel_min = 600000;
	di->vsel_step = 6250;

	return 0;
}

/* For 00,01,03,05 options:
 * VOUT = 0.60V + NSELx * 10mV, from 0.60 to 1.23V.
 * For 04 option:
 * VOUT = 0.603V + NSELx * 12.826mV, from 0.603 to 1.411V.
 *
 */

static int fan53555_device_setup(struct fan53555_regulator_info *di)
{
	int ret = 0;

	/* Setup voltage control register */
	switch (di->sleep_vsel_id) {
	case FAN53555_VSEL_ID_0:
		di->sleep_reg = FAN53555_VSEL0;
		di->vol_reg = FAN53555_VSEL1;
		break;
	case FAN53555_VSEL_ID_1:
		di->sleep_reg = FAN53555_VSEL1;
		di->vol_reg = FAN53555_VSEL0;
		break;
	default:
		dev_err(di->dev, "Invalid VSEL ID!\n");
		return -EINVAL;
	}

	switch (di->vendor) {
	case FAN53555_VENDOR_FAIRCHILD:
		ret = fan53555_voltages_setup_fairchild(di);
		break;
	case FAN53555_VENDOR_SILERGY:
		ret = fan53555_voltages_setup_silergy(di);
		break;
	case FAN53555_VENDOR_TCS:
		ret = fan53555_voltages_setup_tcs(di);
		break;
	default:
		dev_err(di->dev, "vendor %d not supported!\n", di->vendor);
		return -EINVAL;
	}

	return ret;
}

static int fan53555_regulator_ofdata_to_platdata(struct udevice *dev)
{
	struct fan53555_regulator_info *priv = dev_get_priv(dev);
	int ret;

	priv->sleep_vsel_id = dev_read_u32_default(dev,
						   "fcs,suspend-voltage-selector",
						   1);

	ret = gpio_request_by_name(dev, "vsel-gpios", 0,
				   &priv->vsel_gpio, GPIOD_IS_OUT);
	if (ret)
		dev_err(dev, "vsel-gpios- not found! Error: %d\n", ret);

	if (dm_gpio_is_valid(&priv->vsel_gpio))
		dm_gpio_set_value(&priv->vsel_gpio, !priv->sleep_vsel_id);

	priv->vendor = dev_get_driver_data(dev);

	return 0;
}

static int fan53555_regulator_probe(struct udevice *dev)
{
	struct fan53555_regulator_info *di = dev_get_priv(dev);
	struct dm_regulator_uclass_platdata *uc_pdata;
	u8 val;
	int ret;

	uc_pdata = dev_get_uclass_platdata(dev);
	uc_pdata->type = REGULATOR_TYPE_BUCK;
	uc_pdata->mode_count = 0;

	/* Get chip ID */
	val = fan53555_reg_read(dev, FAN53555_ID1);
	if (val < 0) {
		dev_err(dev, "Failed to get chip ID!\n");
		return val;
	}
	di->chip_id = val & DIE_ID;

	/* Get chip revision */
	val = fan53555_reg_read(dev, FAN53555_ID2);
	if (val < 0) {
		dev_err(dev, "Failed to get chip Rev!\n");
		return val;
	}
	di->chip_rev = val & DIE_REV;

	debug("FAN53555 Option[%d] Rev[%d] Detected!\n",
	      di->chip_id, di->chip_rev);

	/* Device init */
	ret = fan53555_device_setup(di);
	if (ret < 0) {
		dev_err(dev, "Failed to setup device!\n");
		return ret;
	}

	return 0;
}

static const struct udevice_id fan53555_id[] = {
	{
		.compatible = "fan53555",
		.data = FAN53555_VENDOR_FAIRCHILD,
	}, {
		.compatible = "silergy,syr827",
		.data = FAN53555_VENDOR_SILERGY,
	}, {
		.compatible = "silergy,syr828",
		.data = FAN53555_VENDOR_SILERGY,
	}, {
		.compatible = "tcs,tcs452x", /* tcs4525/4526 */
		.data = FAN53555_VENDOR_TCS,
	},
	{ },
};

static const struct dm_regulator_ops fan53555_regulator_ops = {
	.get_value  = fan53555_regulator_get_voltage,
	.set_value  = fan53555_regulator_set_voltage,
	.set_suspend_value = fan53555_regulator_set_suspend_voltage,
	.get_suspend_value = fan53555_regulator_get_suspend_voltage,
	.set_enable = fan53555_regulator_set_enable,
	.get_enable = fan53555_regulator_get_enable,
	.set_suspend_enable = fan53555_regulator_set_suspend_enable,
	.get_suspend_enable = fan53555_regulator_get_suspend_enable,
};

U_BOOT_DRIVER(fan53555_regulator) = {
	.name = "fan53555_regulator",
	.id = UCLASS_REGULATOR,
	.ops = &fan53555_regulator_ops,
	.probe = fan53555_regulator_probe,
	.of_match = fan53555_id,
	.ofdata_to_platdata = fan53555_regulator_ofdata_to_platdata,
	.priv_auto_alloc_size = sizeof(struct fan53555_regulator_info),
};

