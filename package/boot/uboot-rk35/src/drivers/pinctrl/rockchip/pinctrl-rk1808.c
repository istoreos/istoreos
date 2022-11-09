// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2020 Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <dm.h>
#include <dm/pinctrl.h>
#include <regmap.h>
#include <syscon.h>

#include "pinctrl-rockchip.h"

static struct rockchip_mux_route_data rk1808_mux_route_data[] = {
	{
		/* i2c2m0_sda */
		.bank_num = 3,
		.pin = 12,
		.func = 2,
		.route_offset = 0x190,
		.route_val = BIT(16 + 3),
	}, {
		/* i2c2m1_sda */
		.bank_num = 1,
		.pin = 13,
		.func = 2,
		.route_offset = 0x190,
		.route_val = BIT(16 + 3) | BIT(3),
	}, {
		/* uart2_rxm0 */
		.bank_num = 4,
		.pin = 3,
		.func = 2,
		.route_offset = 0x190,
		.route_val = BIT(16 + 14) | BIT(16 + 15),
	}, {
		/* uart2_rxm1 */
		.bank_num = 2,
		.pin = 25,
		.func = 2,
		.route_offset = 0x190,
		.route_val = BIT(16 + 14) | BIT(14) | BIT(16 + 15),
	}, {
		/* uart2_rxm2 */
		.bank_num = 3,
		.pin = 4,
		.func = 2,
		.route_offset = 0x190,
		.route_val = BIT(16 + 14) | BIT(16 + 15) | BIT(15),
	},
};

static int rk1808_set_mux(struct rockchip_pin_bank *bank, int pin, int mux)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;
	int iomux_num = (pin / 8);
	struct regmap *regmap;
	int reg, ret, mask, mux_type;
	u8 bit;
	u32 data;

	debug("setting mux of GPIO%d-%d to %d\n", bank->bank_num, pin, mux);

	if (bank->iomux[iomux_num].type & IOMUX_SOURCE_PMU)
		regmap = priv->regmap_pmu;
	else if (bank->iomux[iomux_num].type & IOMUX_L_SOURCE_PMU)
		regmap = (pin % 8 < 4) ? priv->regmap_pmu : priv->regmap_base;
	else
		regmap = priv->regmap_base;

	/* get basic quadrupel of mux registers and the correct reg inside */
	mux_type = bank->iomux[iomux_num].type;
	reg = bank->iomux[iomux_num].offset;
	if (mux_type & IOMUX_WIDTH_4BIT) {
		if ((pin % 8) >= 4)
			reg += 0x4;
		bit = (pin % 4) * 4;
		mask = 0xf;
	} else {
		bit = (pin % 8) * 2;
		mask = 0x3;
	}

	if (bank->recalced_mask & BIT(pin))
		rockchip_get_recalced_mux(bank, pin, &reg, &bit, &mask);

	data = (mask << (bit + 16));
	data |= (mux & mask) << bit;
	ret = regmap_write(regmap, reg, data);

	return ret;
}

#define RK1808_PULL_PMU_OFFSET		0x10
#define RK1808_PULL_GRF_OFFSET		0x80
#define RK1808_PULL_PINS_PER_REG	8
#define RK1808_PULL_BITS_PER_PIN	2
#define RK1808_PULL_BANK_STRIDE		16

static void rk1808_calc_pull_reg_and_bit(struct rockchip_pin_bank *bank,
					 int pin_num,
					 struct regmap **regmap,
					 int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;

	if (bank->bank_num == 0) {
		*regmap = priv->regmap_pmu;
		*reg = RK1808_PULL_PMU_OFFSET;
	} else {
		*reg = RK1808_PULL_GRF_OFFSET;
		*regmap = priv->regmap_base;
	}

	*reg += ((pin_num / RK1808_PULL_PINS_PER_REG) * 4);
	*bit = (pin_num % RK1808_PULL_PINS_PER_REG);
	*bit *= RK1808_PULL_BITS_PER_PIN;
}

#define RK1808_DRV_PMU_OFFSET		0x20
#define RK1808_DRV_GRF_OFFSET		0x140
#define RK1808_DRV_BITS_PER_PIN		2
#define RK1808_DRV_PINS_PER_REG		8
#define RK1808_DRV_BANK_STRIDE		16

static void rk1808_calc_drv_reg_and_bit(struct rockchip_pin_bank *bank,
					int pin_num,
					struct regmap **regmap,
					int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;

	if (bank->bank_num == 0) {
		*regmap = priv->regmap_pmu;
		*reg = RK1808_DRV_PMU_OFFSET;
	} else {
		*regmap = priv->regmap_base;
		*reg = RK1808_DRV_GRF_OFFSET;
	}

	*reg += ((pin_num / RK1808_DRV_PINS_PER_REG) * 4);
	*bit = pin_num % RK1808_DRV_PINS_PER_REG;
	*bit *= RK1808_DRV_BITS_PER_PIN;
}

#define RK1808_SCHMITT_PMU_OFFSET		0x0040
#define RK1808_SCHMITT_GRF_OFFSET		0x0100
#define RK1808_SCHMITT_BANK_STRIDE		16
#define RK1808_SCHMITT_PINS_PER_REG		8

static int rk1808_calc_schmitt_reg_and_bit(struct rockchip_pin_bank *bank,
					   int pin_num,
					   struct regmap **regmap,
					   int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;

	if (bank->bank_num == 0) {
		*regmap = priv->regmap_pmu;
		*reg = RK1808_SCHMITT_PMU_OFFSET;
	} else {
		*regmap = priv->regmap_base;
		*reg = RK1808_SCHMITT_GRF_OFFSET;
		*reg += (bank->bank_num  - 1) * RK1808_SCHMITT_BANK_STRIDE;
	}
	*reg += ((pin_num / RK1808_SCHMITT_PINS_PER_REG) * 4);
	*bit = pin_num % RK1808_SCHMITT_PINS_PER_REG;

	return 0;
}

static int rk1808_set_pull(struct rockchip_pin_bank *bank,
			   int pin_num, int pull)
{
	struct regmap *regmap;
	int reg, ret;
	u8 bit, type;
	u32 data;

	if (pull == PIN_CONFIG_BIAS_PULL_PIN_DEFAULT)
		return -ENOTSUPP;

	rk1808_calc_pull_reg_and_bit(bank, pin_num, &regmap, &reg, &bit);
	type = bank->pull_type[pin_num / 8];
	ret = rockchip_translate_pull_value(type, pull);
	if (ret < 0) {
		debug("unsupported pull setting %d\n", pull);
		return ret;
	}

	/* enable the write to the equivalent lower bits */
	data = ((1 << ROCKCHIP_PULL_BITS_PER_PIN) - 1) << (bit + 16);

	data |= (ret << bit);
	ret = regmap_write(regmap, reg, data);

	return ret;
}

static int rk1808_set_drive(struct rockchip_pin_bank *bank,
			    int pin_num, int strength)
{
	struct regmap *regmap;
	int reg;
	u32 data;
	u8 bit;

	rk1808_calc_drv_reg_and_bit(bank, pin_num, &regmap, &reg, &bit);

	/* enable the write to the equivalent lower bits */
	data = ((1 << ROCKCHIP_DRV_BITS_PER_PIN) - 1) << (bit + 16);
	data |= (strength << bit);

	return regmap_write(regmap, reg, data);
}

static int rk1808_set_schmitt(struct rockchip_pin_bank *bank,
			      int pin_num, int enable)
{
	struct regmap *regmap;
	int reg;
	u8 bit;
	u32 data;

	rk1808_calc_schmitt_reg_and_bit(bank, pin_num, &regmap, &reg, &bit);
	/* enable the write to the equivalent lower bits */
	data = BIT(bit + 16) | (enable << bit);

	return regmap_write(regmap, reg, data);
}

static struct rockchip_pin_bank rk1808_pin_banks[] = {
	PIN_BANK_IOMUX_FLAGS(0, 32, "gpio0",
			     IOMUX_SOURCE_PMU,
			     IOMUX_SOURCE_PMU,
			     IOMUX_SOURCE_PMU,
			     IOMUX_SOURCE_PMU),
	PIN_BANK_IOMUX_FLAGS(1, 32, "gpio1",
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT),
	PIN_BANK_IOMUX_FLAGS(2, 32, "gpio2",
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT),
	PIN_BANK_IOMUX_FLAGS(3, 32, "gpio3",
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT),
	PIN_BANK_IOMUX_FLAGS(4, 32, "gpio4",
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT),
};

static const struct rockchip_pin_ctrl rk1808_pin_ctrl = {
	.pin_banks		= rk1808_pin_banks,
	.nr_banks		= ARRAY_SIZE(rk1808_pin_banks),
	.nr_pins		= 160,
	.iomux_routes		= rk1808_mux_route_data,
	.niomux_routes		= ARRAY_SIZE(rk1808_mux_route_data),
	.grf_mux_offset		= 0x0,
	.pmu_mux_offset		= 0x0,
	.set_mux		= rk1808_set_mux,
	.set_pull		= rk1808_set_pull,
	.set_drive		= rk1808_set_drive,
	.set_schmitt		= rk1808_set_schmitt,
};

static const struct udevice_id rk1808_pinctrl_ids[] = {
	{
		.compatible = "rockchip,rk1808-pinctrl",
		.data = (ulong)&rk1808_pin_ctrl
	},
	{ }
};

U_BOOT_DRIVER(pinctrl_rk1808) = {
	.name		= "rockchip_rk1808_pinctrl",
	.id		= UCLASS_PINCTRL,
	.of_match	= rk1808_pinctrl_ids,
	.priv_auto_alloc_size = sizeof(struct rockchip_pinctrl_priv),
	.ops		= &rockchip_pinctrl_ops,
#if !CONFIG_IS_ENABLED(OF_PLATDATA)
	.bind		= dm_scan_fdt_dev,
#endif
	.probe		= rockchip_pinctrl_probe,
};
