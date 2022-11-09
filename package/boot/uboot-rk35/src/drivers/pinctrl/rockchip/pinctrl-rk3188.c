// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2019 Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <dm.h>
#include <dm/pinctrl.h>
#include <regmap.h>
#include <syscon.h>

#include "pinctrl-rockchip.h"

static int rk3188_set_mux(struct rockchip_pin_bank *bank, int pin, int mux)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;
	int iomux_num = (pin / 8);
	struct regmap *regmap;
	int reg, ret, mask, mux_type;
	u8 bit;
	u32 data;

	regmap = (bank->iomux[iomux_num].type & IOMUX_SOURCE_PMU)
				? priv->regmap_pmu : priv->regmap_base;

	/* get basic quadrupel of mux registers and the correct reg inside */
	mux_type = bank->iomux[iomux_num].type;
	reg = bank->iomux[iomux_num].offset;
	reg += rockchip_get_mux_data(mux_type, pin, &bit, &mask);

	data = (mask << (bit + 16));
	data |= (mux & mask) << bit;
	ret = regmap_write(regmap, reg, data);

	return ret;
}

#define RK3188_PULL_OFFSET		0x164
#define RK3188_PULL_PMU_OFFSET		0x64

static void rk3188_calc_pull_reg_and_bit(struct rockchip_pin_bank *bank,
					 int pin_num, struct regmap **regmap,
					 int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;

	/* The first 12 pins of the first bank are located elsewhere */
	if (bank->bank_num == 0 && pin_num < 12) {
		*regmap = priv->regmap_pmu;
		*reg = RK3188_PULL_PMU_OFFSET;

		*reg += ((pin_num / ROCKCHIP_PULL_PINS_PER_REG) * 4);
		*bit = pin_num % ROCKCHIP_PULL_PINS_PER_REG;
		*bit *= ROCKCHIP_PULL_BITS_PER_PIN;
	} else {
		*regmap = priv->regmap_base;
		*reg = RK3188_PULL_OFFSET;

		/* correct the offset, as it is the 2nd pull register */
		*reg -= 4;
		*reg += bank->bank_num * ROCKCHIP_PULL_BANK_STRIDE;
		*reg += ((pin_num / ROCKCHIP_PULL_PINS_PER_REG) * 4);

		/*
		 * The bits in these registers have an inverse ordering
		 * with the lowest pin being in bits 15:14 and the highest
		 * pin in bits 1:0
		 */
		*bit = 7 - (pin_num % ROCKCHIP_PULL_PINS_PER_REG);
		*bit *= ROCKCHIP_PULL_BITS_PER_PIN;
	}
}

static int rk3188_set_pull(struct rockchip_pin_bank *bank,
			   int pin_num, int pull)
{
	struct regmap *regmap;
	int reg, ret;
	u8 bit, type;
	u32 data;

	if (pull == PIN_CONFIG_BIAS_PULL_PIN_DEFAULT)
		return -ENOTSUPP;

	rk3188_calc_pull_reg_and_bit(bank, pin_num, &regmap, &reg, &bit);
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

static struct rockchip_pin_bank rk3188_pin_banks[] = {
	PIN_BANK_IOMUX_FLAGS(0, 32, "gpio0", IOMUX_GPIO_ONLY, 0, 0, 0),
	PIN_BANK(1, 32, "gpio1"),
	PIN_BANK(2, 32, "gpio2"),
	PIN_BANK(3, 32, "gpio3"),
};

static struct rockchip_pin_ctrl rk3188_pin_ctrl = {
	.pin_banks		= rk3188_pin_banks,
	.nr_banks		= ARRAY_SIZE(rk3188_pin_banks),
	.nr_pins		= 128,
	.grf_mux_offset		= 0x60,
	.set_mux		= rk3188_set_mux,
	.set_pull		= rk3188_set_pull,
};

static const struct udevice_id rk3188_pinctrl_ids[] = {
	{ .compatible = "rockchip,rk3188-pinctrl",
		.data = (ulong)&rk3188_pin_ctrl },
	{ }
};

U_BOOT_DRIVER(pinctrl_rk3188) = {
	.name		= "rockchip_rk3188_pinctrl",
	.id		= UCLASS_PINCTRL,
	.of_match	= rk3188_pinctrl_ids,
	.priv_auto_alloc_size = sizeof(struct rockchip_pinctrl_priv),
	.ops		= &rockchip_pinctrl_ops,
#if !CONFIG_IS_ENABLED(OF_PLATDATA)
	.bind		= dm_scan_fdt_dev,
#endif
	.probe		= rockchip_pinctrl_probe,
};
