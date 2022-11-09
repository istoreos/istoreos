// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2021 Rockchip Electronics Co., Ltd
 */
#include <common.h>
#include <dm.h>
#include <errno.h>
#include <i2c.h>
#include <syscon.h>
#include <asm/gpio.h>
#include <power/regulator.h>
#include <asm/arch/clock.h>
#include <asm/io.h>

DECLARE_GLOBAL_DATA_PTR;

/* Voltage setting */

#define RK860X_VSEL0_A		0x00
#define RK860X_VSEL1_A		0x01
#define RK860X_VSEL0_B		0x06
#define RK860X_VSEL1_B		0x07
#define RK860X_MAX_SET		0x08

/* Control register */
#define RK860X_CONTROL		0x02
/* IC Type */
#define RK860X_ID1		0x03
/* IC mask version */
#define RK860X_ID2		0x04
/* Monitor register */
#define RK860X_MONITOR		0x05

/* VSEL bit definitions */
#define VSEL_BUCK_EN		BIT(7)
#define VSEL_MODE		BIT(6)
#define VSEL_A_NSEL_MASK	0x3F
#define VSEL_B_NSEL_MASK	0xff

/* Chip ID */
#define DIE_ID			0x0F
#define DIE_REV			0x0F
/* Control bit definitions */
#define CTL_OUTPUT_DISCHG	BIT(7)
#define CTL_SLEW_MASK		(0x7 << 4)
#define CTL_SLEW_SHIFT		4
#define CTL_RESET		BIT(2)

#define RK860X_NVOLTAGES_64	64
#define RK860X_NVOLTAGES_160	160

/* IC Type */
enum {
	RK860X_CHIP_ID_00 = 0,
	RK860X_CHIP_ID_01,
	RK860X_CHIP_ID_02,
	RK860X_CHIP_ID_03,
};

struct rk860x_regulator_info {
	struct udevice *dev;
	/* IC Type and Rev */
	int chip_id;
	/* Voltage setting register */
	unsigned int vol_reg;
	unsigned int sleep_reg;
	unsigned int en_reg;
	unsigned int sleep_en_reg;
	unsigned int mode_reg;
	unsigned int vol_mask;
	unsigned int mode_mask;
	unsigned int n_voltages;
	/* Voltage range and step(linear) */
	unsigned int vsel_min;
	unsigned int vsel_step;
	struct gpio_desc vsel_gpio;
	struct gpio_desc en_gpio;
	unsigned int sleep_vsel_id;
};

static int rk860x_write(struct udevice *dev, uint reg, const uint8_t *buff,
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

static int rk860x_read(struct udevice *dev, uint reg, uint8_t *buff, int len)
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

int rk860x_reg_read(struct udevice *dev, uint reg)
{
	u8 byte;
	int ret;

	debug("%s: reg=%x", __func__, reg);
	ret = rk860x_read(dev, reg, &byte, 1);
	debug(", value=%x, ret=%d\n", byte, ret);

	return ret ? ret : byte;
}

int rk860x_reg_write(struct udevice *dev, uint reg, uint value)
{
	u8 byte = value;
	int ret;

	debug("%s: reg=%x, value=%x", __func__, reg, value);
	ret = rk860x_write(dev, reg, &byte, 1);
	debug(", ret=%d\n", ret);

	return ret;
}

int  rk860x_clrsetbits(struct udevice *dev, uint reg, uint clr, uint set)
{
	u8 byte;
	int ret;

	ret = rk860x_reg_read(dev, reg);
	if (ret < 0)
		return ret;
	byte = (ret & ~clr) | set;

	return rk860x_reg_write(dev, reg, byte);
}

static int rk860x_regulator_set_enable(struct udevice *dev, bool enable)
{
	struct rk860x_regulator_info *priv = dev_get_priv(dev);
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
	rk860x_clrsetbits(dev, priv->en_reg, VSEL_BUCK_EN, val);

	return 0;
}

static int rk860x_regulator_get_enable(struct udevice *dev)
{
	struct rk860x_regulator_info *priv = dev_get_priv(dev);
	int val;

	if (dm_gpio_is_valid(&priv->vsel_gpio)) {
		if (priv->sleep_vsel_id)
			return !dm_gpio_get_value(&priv->vsel_gpio);
		else
			return dm_gpio_get_value(&priv->vsel_gpio);
	}

	val = rk860x_reg_read(dev, priv->en_reg);
	if (val & VSEL_BUCK_EN)
		return 1;
	else
		return 0;
}

static int rk860x_regulator_set_suspend_enable(struct udevice *dev,
					       bool enable)
{
	struct rk860x_regulator_info *priv = dev_get_priv(dev);
	int val;

	if (enable)
		val = VSEL_BUCK_EN;
	else
		val = 0;

	rk860x_clrsetbits(dev, priv->sleep_en_reg, VSEL_BUCK_EN, val);

	return 0;
}

static int rk860x_regulator_get_suspend_enable(struct udevice *dev)
{
	struct rk860x_regulator_info *priv = dev_get_priv(dev);
	int val;

	val = rk860x_reg_read(dev, priv->sleep_en_reg);
	if (val & VSEL_BUCK_EN)
		return 1;
	else
		return 0;
}

static int rk860x_regulator_get_voltage(struct udevice *dev)
{
	struct rk860x_regulator_info *priv = dev_get_priv(dev);
	int uvolt = 0, val;

	val = rk860x_reg_read(dev, priv->vol_reg);
	val &= priv->vol_mask;
	uvolt = (val * priv->vsel_step) + priv->vsel_min;

	return uvolt;
}

static int rk860x_regulator_set_voltage(struct udevice *dev, int uvolt)
{
	struct rk860x_regulator_info *priv = dev_get_priv(dev);
	int val;

	val = ((uvolt - priv->vsel_min) / priv->vsel_step);
	rk860x_clrsetbits(dev, priv->vol_reg, priv->vol_mask, val);

	return 0;
}

static int rk860x_regulator_get_suspend_voltage(struct udevice *dev)
{
	struct rk860x_regulator_info *priv = dev_get_priv(dev);
	int uvolt = 0, val;

	val = rk860x_reg_read(dev, priv->sleep_reg);
	val &= priv->vol_mask;
	uvolt = (val * priv->vsel_step) + priv->vsel_min;

	return uvolt;
}

static int rk860x_regulator_set_suspend_voltage(struct udevice *dev,
						int uvolt)
{
	struct rk860x_regulator_info *priv = dev_get_priv(dev);
	int val;

	val = ((uvolt - priv->vsel_min) / priv->vsel_step);
	rk860x_clrsetbits(dev, priv->sleep_reg, priv->vol_mask, val);

	return 0;
}

/* For 00,01 options:
 * VOUT = 0.7125V + NSELx * 12.5mV, from 0.7125 to 1.5V.
 * For 02,03 options:
 * VOUT = 0.5V + NSELx * 6.25mV, from 0.5 to 1.5V.
 */
static int rk860x_device_setup(struct rk860x_regulator_info *di)
{
	int ret = 0;

	switch (di->chip_id) {
	case RK860X_CHIP_ID_00:
	case RK860X_CHIP_ID_01:
		di->vsel_min = 712500;
		di->vsel_step = 12500;
		di->n_voltages = RK860X_NVOLTAGES_64;
		di->vol_mask = VSEL_A_NSEL_MASK;
		if (di->sleep_vsel_id) {
			di->sleep_reg = RK860X_VSEL1_A;
			di->vol_reg = RK860X_VSEL0_A;
			di->mode_reg = RK860X_VSEL0_A;
			di->en_reg = RK860X_VSEL0_A;
			di->sleep_en_reg = RK860X_VSEL1_A;
		} else {
			di->sleep_reg = RK860X_VSEL0_A;
			di->vol_reg = RK860X_VSEL1_A;
			di->mode_reg = RK860X_VSEL1_A;
			di->en_reg = RK860X_VSEL1_A;
			di->sleep_en_reg = RK860X_VSEL0_A;
		}
		break;
	case RK860X_CHIP_ID_02:
	case RK860X_CHIP_ID_03:
		di->vsel_min = 500000;
		di->vsel_step = 6250;
		di->n_voltages = RK860X_NVOLTAGES_160;
		di->vol_mask = VSEL_B_NSEL_MASK;
		if (di->sleep_vsel_id) {
			di->sleep_reg = RK860X_VSEL1_B;
			di->vol_reg = RK860X_VSEL0_B;
			di->mode_reg = RK860X_VSEL0_A;
			di->en_reg = RK860X_VSEL0_A;
			di->sleep_en_reg = RK860X_VSEL1_A;
		} else {
			di->sleep_reg = RK860X_VSEL0_B;
			di->vol_reg = RK860X_VSEL1_B;
			di->mode_reg = RK860X_VSEL1_A;
			di->en_reg = RK860X_VSEL1_A;
			di->sleep_en_reg = RK860X_VSEL0_A;
		}
		break;
	default:
		dev_err(di->dev,
			"Chip ID %d not supported!\n",
			di->chip_id);
		return -EINVAL;
	}

	di->mode_mask = VSEL_MODE;

	return ret;
}

static int rk860x_regulator_ofdata_to_platdata(struct udevice *dev)
{
	struct rk860x_regulator_info *priv = dev_get_priv(dev);
	int ret;

	priv->sleep_vsel_id = dev_read_u32_default(dev,
						   "rockchip,suspend-voltage-selector",
						   1);

	ret = gpio_request_by_name(dev, "vsel-gpios", 0,
				   &priv->vsel_gpio, GPIOD_IS_OUT);
	if (ret)
		dev_err(dev, "vsel-gpios- not found! Error: %d\n", ret);

	if (dm_gpio_is_valid(&priv->vsel_gpio))
		dm_gpio_set_value(&priv->vsel_gpio, !priv->sleep_vsel_id);

	ret = gpio_request_by_name(dev, "en-gpios", 0,
				   &priv->en_gpio, GPIOD_IS_OUT);
	if (ret)
		dev_err(dev, "en-gpios- not found! Error: %d\n", ret);

	if (dm_gpio_is_valid(&priv->en_gpio))
		dm_gpio_set_value(&priv->en_gpio, 1);

	return 0;
}

static int rk860x_regulator_probe(struct udevice *dev)
{
	struct rk860x_regulator_info *di = dev_get_priv(dev);
	struct dm_regulator_uclass_platdata *uc_pdata;
	u8 val;
	int ret;

	uc_pdata = dev_get_uclass_platdata(dev);
	uc_pdata->type = REGULATOR_TYPE_BUCK;
	uc_pdata->mode_count = 0;

	/* Get chip ID */
	val = rk860x_reg_read(dev, RK860X_ID1);
	if (val < 0) {
		dev_err(dev, "Failed to get chip ID!\n");
		return val;
	}
	if ((val & DIE_ID) == 0x8)
		di->chip_id = RK860X_CHIP_ID_00;
	else
		di->chip_id = RK860X_CHIP_ID_02;

	debug("RK860X Option[%d] Detected!\n", val & DIE_ID);

	/* Device init */
	ret = rk860x_device_setup(di);
	if (ret < 0) {
		dev_err(dev, "Failed to setup device!\n");
		return ret;
	}

	return 0;
}

static const struct udevice_id rk860x_id[] = {
	{
		.compatible = "rockchip,rk8600",
	},
	{
		.compatible = "rockchip,rk8601",
	},
	{
		.compatible = "rockchip,rk8602",
	},
	{
		.compatible = "rockchip,rk8603",
	},
	{ },
};

static const struct dm_regulator_ops rk860x_regulator_ops = {
	.get_value  = rk860x_regulator_get_voltage,
	.set_value  = rk860x_regulator_set_voltage,
	.set_suspend_value = rk860x_regulator_set_suspend_voltage,
	.get_suspend_value = rk860x_regulator_get_suspend_voltage,
	.set_enable = rk860x_regulator_set_enable,
	.get_enable = rk860x_regulator_get_enable,
	.set_suspend_enable = rk860x_regulator_set_suspend_enable,
	.get_suspend_enable = rk860x_regulator_get_suspend_enable,
};

U_BOOT_DRIVER(rk860x_regulator) = {
	.name = "rk860x_regulator",
	.id = UCLASS_REGULATOR,
	.ops = &rk860x_regulator_ops,
	.probe = rk860x_regulator_probe,
	.of_match = rk860x_id,
	.ofdata_to_platdata = rk860x_regulator_ofdata_to_platdata,
	.priv_auto_alloc_size = sizeof(struct rk860x_regulator_info),
};

