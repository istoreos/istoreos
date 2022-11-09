// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2020 Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <dm.h>
#include <dm/pinctrl.h>
#include <regmap.h>
#include <syscon.h>
#include <asm/arch-rockchip/cpu.h>

#include "pinctrl-rockchip.h"

static struct rockchip_mux_route_data rk3308_mux_route_data[] = {
	{
		/* rtc_clk */
		.bank_num = 0,
		.pin = 19,
		.func = 1,
		.route_offset = 0x314,
		.route_val = BIT(16 + 0) | BIT(0),
	}, {
		/* uart2_rxm0 */
		.bank_num = 1,
		.pin = 22,
		.func = 2,
		.route_offset = 0x314,
		.route_val = BIT(16 + 2) | BIT(16 + 3),
	}, {
		/* uart2_rxm1 */
		.bank_num = 4,
		.pin = 26,
		.func = 2,
		.route_offset = 0x314,
		.route_val = BIT(16 + 2) | BIT(16 + 3) | BIT(2),
	}, {
		/* i2c3_sdam0 */
		.bank_num = 0,
		.pin = 23,
		.func = 2,
		.route_offset = 0x314,
		.route_val = BIT(16 + 4),
	}, {
		/* i2c3_sdam1 */
		.bank_num = 3,
		.pin = 12,
		.func = 2,
		.route_offset = 0x314,
		.route_val = BIT(16 + 4) | BIT(4),
	}, {
		/* i2s-8ch-1-sclktxm0 */
		.bank_num = 1,
		.pin = 3,
		.func = 2,
		.route_offset = 0x308,
		.route_val = BIT(16 + 3),
	}, {
		/* i2s-8ch-1-sclkrxm0 */
		.bank_num = 1,
		.pin = 4,
		.func = 2,
		.route_offset = 0x308,
		.route_val = BIT(16 + 3),
	}, {
		/* i2s-8ch-1-sclktxm1 */
		.bank_num = 1,
		.pin = 13,
		.func = 2,
		.route_offset = 0x308,
		.route_val = BIT(16 + 3) | BIT(3),
	}, {
		/* i2s-8ch-1-sclkrxm1 */
		.bank_num = 1,
		.pin = 14,
		.func = 2,
		.route_offset = 0x308,
		.route_val = BIT(16 + 3) | BIT(3),
	}, {
		/* pdm-clkm0 */
		.bank_num = 1,
		.pin = 4,
		.func = 3,
		.route_offset = 0x308,
		.route_val = BIT(16 + 12) | BIT(16 + 13),
	}, {
		/* pdm-clkm1 */
		.bank_num = 1,
		.pin = 14,
		.func = 4,
		.route_offset = 0x308,
		.route_val = BIT(16 + 12) | BIT(16 + 13) | BIT(12),
	}, {
		/* pdm-clkm2 */
		.bank_num = 2,
		.pin = 6,
		.func = 2,
		.route_offset = 0x308,
		.route_val = BIT(16 + 12) | BIT(16 + 13) | BIT(13),
	}, {
		/* pdm-clkm-m2 */
		.bank_num = 2,
		.pin = 4,
		.func = 3,
		.route_offset = 0x600,
		.route_val = BIT(16 + 2) | BIT(2),
	},
};

static struct rockchip_mux_route_data rk3308b_mux_route_data[] = {
	{
		/* rtc_clk */
		.bank_num = 0,
		.pin = 19,
		.func = 1,
		.route_offset = 0x314,
		.route_val = BIT(16 + 0) | BIT(0),
	}, {
		/* uart2_rxm0 */
		.bank_num = 1,
		.pin = 22,
		.func = 2,
		.route_offset = 0x314,
		.route_val = BIT(16 + 2) | BIT(16 + 3),
	}, {
		/* uart2_rxm1 */
		.bank_num = 4,
		.pin = 26,
		.func = 2,
		.route_offset = 0x314,
		.route_val = BIT(16 + 2) | BIT(16 + 3) | BIT(2),
	}, {
		/* i2c3_sdam0 */
		.bank_num = 0,
		.pin = 15,
		.func = 2,
		.route_offset = 0x608,
		.route_val = BIT(16 + 8) | BIT(16 + 9),
	}, {
		/* i2c3_sdam1 */
		.bank_num = 3,
		.pin = 12,
		.func = 2,
		.route_offset = 0x608,
		.route_val = BIT(16 + 8) | BIT(16 + 9) | BIT(8),
	}, {
		/* i2c3_sdam2 */
		.bank_num = 2,
		.pin = 0,
		.func = 3,
		.route_offset = 0x608,
		.route_val = BIT(16 + 8) | BIT(16 + 9) | BIT(9),
	}, {
		/* i2s-8ch-1-sclktxm0 */
		.bank_num = 1,
		.pin = 3,
		.func = 2,
		.route_offset = 0x308,
		.route_val = BIT(16 + 3),
	}, {
		/* i2s-8ch-1-sclkrxm0 */
		.bank_num = 1,
		.pin = 4,
		.func = 2,
		.route_offset = 0x308,
		.route_val = BIT(16 + 3),
	}, {
		/* i2s-8ch-1-sclktxm1 */
		.bank_num = 1,
		.pin = 13,
		.func = 2,
		.route_offset = 0x308,
		.route_val = BIT(16 + 3) | BIT(3),
	}, {
		/* i2s-8ch-1-sclkrxm1 */
		.bank_num = 1,
		.pin = 14,
		.func = 2,
		.route_offset = 0x308,
		.route_val = BIT(16 + 3) | BIT(3),
	}, {
		/* pdm-clkm0 */
		.bank_num = 1,
		.pin = 4,
		.func = 3,
		.route_offset = 0x308,
		.route_val =  BIT(16 + 12) | BIT(16 + 13),
	}, {
		/* pdm-clkm1 */
		.bank_num = 1,
		.pin = 14,
		.func = 4,
		.route_offset = 0x308,
		.route_val = BIT(16 + 12) | BIT(16 + 13) | BIT(12),
	}, {
		/* pdm-clkm2 */
		.bank_num = 2,
		.pin = 6,
		.func = 2,
		.route_offset = 0x308,
		.route_val = BIT(16 + 12) | BIT(16 + 13) | BIT(13),
	}, {
		/* pdm-clkm-m2 */
		.bank_num = 2,
		.pin = 4,
		.func = 3,
		.route_offset = 0x600,
		.route_val = BIT(16 + 2) | BIT(2),
	}, {
		/* spi1_miso */
		.bank_num = 3,
		.pin = 10,
		.func = 3,
		.route_offset = 0x314,
		.route_val = BIT(16 + 9),
	}, {
		/* spi1_miso_m1 */
		.bank_num = 2,
		.pin = 4,
		.func = 2,
		.route_offset = 0x314,
		.route_val = BIT(16 + 9) | BIT(9),
	}, {
		/* owire_m0 */
		.bank_num = 0,
		.pin = 11,
		.func = 3,
		.route_offset = 0x314,
		.route_val = BIT(16 + 10) | BIT(16 + 11),
	}, {
		/* owire_m1 */
		.bank_num = 1,
		.pin = 22,
		.func = 7,
		.route_offset = 0x314,
		.route_val = BIT(16 + 10) | BIT(16 + 11) | BIT(10),
	}, {
		/* owire_m2 */
		.bank_num = 2,
		.pin = 2,
		.func = 5,
		.route_offset = 0x314,
		.route_val = BIT(16 + 10) | BIT(16 + 11) | BIT(11),
	}, {
		/* can_rxd_m0 */
		.bank_num = 0,
		.pin = 11,
		.func = 2,
		.route_offset = 0x314,
		.route_val = BIT(16 + 12) | BIT(16 + 13),
	}, {
		/* can_rxd_m1 */
		.bank_num = 1,
		.pin = 22,
		.func = 5,
		.route_offset = 0x314,
		.route_val = BIT(16 + 12) | BIT(16 + 13) | BIT(12),
	}, {
		/* can_rxd_m2 */
		.bank_num = 2,
		.pin = 2,
		.func = 4,
		.route_offset = 0x314,
		.route_val = BIT(16 + 12) | BIT(16 + 13) | BIT(13),
	}, {
		/* mac_rxd0_m0 */
		.bank_num = 1,
		.pin = 20,
		.func = 3,
		.route_offset = 0x314,
		.route_val = BIT(16 + 14),
	}, {
		/* mac_rxd0_m1 */
		.bank_num = 4,
		.pin = 2,
		.func = 2,
		.route_offset = 0x314,
		.route_val = BIT(16 + 14) | BIT(14),
	}, {
		/* uart3_rx */
		.bank_num = 3,
		.pin = 12,
		.func = 4,
		.route_offset = 0x314,
		.route_val = BIT(16 + 15),
	}, {
		/* uart3_rx_m1 */
		.bank_num = 0,
		.pin = 17,
		.func = 3,
		.route_offset = 0x314,
		.route_val = BIT(16 + 15) | BIT(15),
	},
};
static struct rockchip_mux_recalced_data rk3308_mux_recalced_data[] = {
	{
		.num = 1,
		.pin = 14,
		.reg = 0x28,
		.bit = 12,
		.mask = 0x7
	}, {
		.num = 1,
		.pin = 15,
		.reg = 0x2c,
		.bit = 0,
		.mask = 0x3
	}, {
		.num = 1,
		.pin = 18,
		.reg = 0x30,
		.bit = 4,
		.mask = 0x7
	}, {
		.num = 1,
		.pin = 19,
		.reg = 0x30,
		.bit = 8,
		.mask = 0x7
	}, {
		.num = 1,
		.pin = 20,
		.reg = 0x30,
		.bit = 12,
		.mask = 0x7
	}, {
		.num = 1,
		.pin = 21,
		.reg = 0x34,
		.bit = 0,
		.mask = 0x7
	}, {
		.num = 1,
		.pin = 22,
		.reg = 0x34,
		.bit = 4,
		.mask = 0x7
	}, {
		.num = 1,
		.pin = 23,
		.reg = 0x34,
		.bit = 8,
		.mask = 0x7
	}, {
		.num = 3,
		.pin = 12,
		.reg = 0x68,
		.bit = 8,
		.mask = 0x7
	}, {
		.num = 3,
		.pin = 13,
		.reg = 0x68,
		.bit = 12,
		.mask = 0x7
	},
};

static struct rockchip_mux_recalced_data rk3308b_mux_recalced_data[] = {
	{
		.num = 1,
		.pin = 14,
		.reg = 0x28,
		.bit = 12,
		.mask = 0xf
	}, {
		.num = 1,
		.pin = 15,
		.reg = 0x2c,
		.bit = 0,
		.mask = 0x3
	}, {
		.num = 1,
		.pin = 18,
		.reg = 0x30,
		.bit = 4,
		.mask = 0xf
	}, {
		.num = 1,
		.pin = 19,
		.reg = 0x30,
		.bit = 8,
		.mask = 0xf
	}, {
		.num = 1,
		.pin = 20,
		.reg = 0x30,
		.bit = 12,
		.mask = 0xf
	}, {
		.num = 1,
		.pin = 21,
		.reg = 0x34,
		.bit = 0,
		.mask = 0xf
	}, {
		.num = 1,
		.pin = 22,
		.reg = 0x34,
		.bit = 4,
		.mask = 0xf
	}, {
		.num = 1,
		.pin = 23,
		.reg = 0x34,
		.bit = 8,
		.mask = 0xf
	}, {
		.num = 3,
		.pin = 12,
		.reg = 0x68,
		.bit = 8,
		.mask = 0xf
	}, {
		.num = 3,
		.pin = 13,
		.reg = 0x68,
		.bit = 12,
		.mask = 0xf
	}, {
		.num = 2,
		.pin = 2,
		.reg = 0x608,
		.bit = 0,
		.mask = 0x7
	}, {
		.num = 2,
		.pin = 3,
		.reg = 0x608,
		.bit = 4,
		.mask = 0x7
	}, {
		.num = 2,
		.pin = 16,
		.reg = 0x610,
		.bit = 8,
		.mask = 0x7
	}, {
		.num = 3,
		.pin = 10,
		.reg = 0x610,
		.bit = 0,
		.mask = 0x7
	}, {
		.num = 3,
		.pin = 11,
		.reg = 0x610,
		.bit = 4,
		.mask = 0x7
	},
};

static int rk3308_set_mux(struct rockchip_pin_bank *bank, int pin, int mux)
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

#define RK3308_PULL_OFFSET		0xa0
#define RK3308_PULL_BITS_PER_PIN	2
#define RK3308_PULL_PINS_PER_REG	8
#define RK3308_PULL_BANK_STRIDE		16

static void rk3308_calc_pull_reg_and_bit(struct rockchip_pin_bank *bank,
					 int pin_num, struct regmap **regmap,
					 int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;

	*regmap = priv->regmap_base;
	*reg = RK3308_PULL_OFFSET;
	*reg += bank->bank_num * RK3308_PULL_BANK_STRIDE;
	*reg += ((pin_num / RK3308_PULL_PINS_PER_REG) * 4);

	*bit = (pin_num % RK3308_PULL_PINS_PER_REG);
	*bit *= RK3308_PULL_BITS_PER_PIN;
}

#define RK3308_DRV_GRF_OFFSET		0x100
#define RK3308_DRV_BITS_PER_PIN		2
#define RK3308_DRV_PINS_PER_REG		8
#define RK3308_DRV_BANK_STRIDE		16

static void rk3308_calc_drv_reg_and_bit(struct rockchip_pin_bank *bank,
					int pin_num, struct regmap **regmap,
					int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;

	*regmap = priv->regmap_base;
	*reg = RK3308_DRV_GRF_OFFSET;
	*reg += bank->bank_num * RK3308_DRV_BANK_STRIDE;
	*reg += ((pin_num / RK3308_DRV_PINS_PER_REG) * 4);

	*bit = (pin_num % RK3308_DRV_PINS_PER_REG);
	*bit *= RK3308_DRV_BITS_PER_PIN;
}

#define RK3308_SCHMITT_PINS_PER_REG	8
#define RK3308_SCHMITT_BANK_STRIDE	16
#define RK3308_SCHMITT_GRF_OFFSET	0x1a0

static int rk3308_calc_schmitt_reg_and_bit(struct rockchip_pin_bank *bank,
					   int pin_num,
					   struct regmap **regmap,
					   int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;

	*regmap = priv->regmap_base;
	*reg = RK3308_SCHMITT_GRF_OFFSET;

	*reg += bank->bank_num * RK3308_SCHMITT_BANK_STRIDE;
	*reg += ((pin_num / RK3308_SCHMITT_PINS_PER_REG) * 4);
	*bit = pin_num % RK3308_SCHMITT_PINS_PER_REG;

	return 0;
}

static int rk3308_set_pull(struct rockchip_pin_bank *bank,
			   int pin_num, int pull)
{
	struct regmap *regmap;
	int reg, ret;
	u8 bit, type;
	u32 data;

	if (pull == PIN_CONFIG_BIAS_PULL_PIN_DEFAULT)
		return -ENOTSUPP;

	rk3308_calc_pull_reg_and_bit(bank, pin_num, &regmap, &reg, &bit);
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

static int rk3308_set_drive(struct rockchip_pin_bank *bank,
			    int pin_num, int strength)
{
	struct regmap *regmap;
	int reg;
	u32 data;
	u8 bit;

	rk3308_calc_drv_reg_and_bit(bank, pin_num, &regmap, &reg, &bit);

	/* enable the write to the equivalent lower bits */
	data = ((1 << ROCKCHIP_DRV_BITS_PER_PIN) - 1) << (bit + 16);
	data |= (strength << bit);

	return regmap_write(regmap, reg, data);
}

static int rk3308_set_schmitt(struct rockchip_pin_bank *bank,
			      int pin_num, int enable)
{
	struct regmap *regmap;
	int reg;
	u8 bit;
	u32 data;

	rk3308_calc_schmitt_reg_and_bit(bank, pin_num, &regmap, &reg, &bit);
	/* enable the write to the equivalent lower bits */
	data = BIT(bit + 16) | (enable << bit);

	return regmap_write(regmap, reg, data);
}

static struct rockchip_pin_bank rk3308_pin_banks[] = {
	PIN_BANK_IOMUX_FLAGS(0, 32, "gpio0", IOMUX_8WIDTH_2BIT,
					     IOMUX_8WIDTH_2BIT,
					     IOMUX_8WIDTH_2BIT,
					     IOMUX_8WIDTH_2BIT),
	PIN_BANK_IOMUX_FLAGS(1, 32, "gpio1", IOMUX_8WIDTH_2BIT,
					     IOMUX_8WIDTH_2BIT,
					     IOMUX_8WIDTH_2BIT,
					     IOMUX_8WIDTH_2BIT),
	PIN_BANK_IOMUX_FLAGS(2, 32, "gpio2", IOMUX_8WIDTH_2BIT,
					     IOMUX_8WIDTH_2BIT,
					     IOMUX_8WIDTH_2BIT,
					     IOMUX_8WIDTH_2BIT),
	PIN_BANK_IOMUX_FLAGS(3, 32, "gpio3", IOMUX_8WIDTH_2BIT,
					     IOMUX_8WIDTH_2BIT,
					     IOMUX_8WIDTH_2BIT,
					     IOMUX_8WIDTH_2BIT),
	PIN_BANK_IOMUX_FLAGS(4, 32, "gpio4", IOMUX_8WIDTH_2BIT,
					     IOMUX_8WIDTH_2BIT,
					     IOMUX_8WIDTH_2BIT,
					     IOMUX_8WIDTH_2BIT),
};

static struct rockchip_pin_ctrl rk3308_pin_ctrl = {
	.pin_banks		= rk3308_pin_banks,
	.nr_banks		= ARRAY_SIZE(rk3308_pin_banks),
	.nr_pins		= 160,
	.grf_mux_offset		= 0x0,
	.iomux_recalced		= rk3308_mux_recalced_data,
	.niomux_recalced	= ARRAY_SIZE(rk3308_mux_recalced_data),
	.iomux_routes		= rk3308_mux_route_data,
	.niomux_routes		= ARRAY_SIZE(rk3308_mux_route_data),
	.set_mux		= rk3308_set_mux,
	.set_pull		= rk3308_set_pull,
	.set_drive		= rk3308_set_drive,
	.set_schmitt		= rk3308_set_schmitt,
};

static const struct rockchip_pin_ctrl rk3308b_pin_ctrl = {
	.pin_banks		= rk3308_pin_banks,
	.nr_banks		= ARRAY_SIZE(rk3308_pin_banks),
	.nr_pins		= 160,
	.grf_mux_offset		= 0x0,
	.iomux_recalced		= rk3308b_mux_recalced_data,
	.niomux_recalced	= ARRAY_SIZE(rk3308b_mux_recalced_data),
	.iomux_routes		= rk3308b_mux_route_data,
	.niomux_routes		= ARRAY_SIZE(rk3308b_mux_route_data),
	.set_mux		= rk3308_set_mux,
	.set_pull		= rk3308_set_pull,
	.set_drive		= rk3308_set_drive,
	.set_schmitt		= rk3308_set_schmitt,
};

static const struct udevice_id rk3308_pinctrl_ids[] = {
	{
		.compatible = "rockchip,rk3308-pinctrl",
		.data = (ulong)&rk3308_pin_ctrl
	},
	{ }
};

/* rk3308b SoC data initialize */
#define RK3308B_GRF_SOC_CON13			0x608
#define RK3308B_GRF_SOC_CON15			0x610

/* RK3308B_GRF_SOC_CON13 */
#define RK3308B_GRF_I2C3_IOFUNC_SRC_CTRL	(BIT(16 + 10) | BIT(10))
#define RK3308B_GRF_GPIO2A3_SEL_SRC_CTRL	(BIT(16 + 7)  | BIT(7))
#define RK3308B_GRF_GPIO2A2_SEL_SRC_CTRL	(BIT(16 + 3)  | BIT(3))

/* RK3308B_GRF_SOC_CON15 */
#define RK3308B_GRF_GPIO2C0_SEL_SRC_CTRL	(BIT(16 + 11) | BIT(11))
#define RK3308B_GRF_GPIO3B3_SEL_SRC_CTRL	(BIT(16 + 7)  | BIT(7))
#define RK3308B_GRF_GPIO3B2_SEL_SRC_CTRL	(BIT(16 + 3)  | BIT(3))

static int rk3308b_soc_data_init(struct udevice *dev)
{
	struct rockchip_pinctrl_priv *priv = dev_get_priv(dev);
	int ret;

	/*
	 * Enable the special ctrl  of selected sources.
	 */
	ret = regmap_write(priv->regmap_base, RK3308B_GRF_SOC_CON13,
			   RK3308B_GRF_I2C3_IOFUNC_SRC_CTRL |
			   RK3308B_GRF_GPIO2A3_SEL_SRC_CTRL |
			   RK3308B_GRF_GPIO2A2_SEL_SRC_CTRL);
	if (ret)
		return ret;

	ret = regmap_write(priv->regmap_base, RK3308B_GRF_SOC_CON15,
			   RK3308B_GRF_GPIO2C0_SEL_SRC_CTRL |
			   RK3308B_GRF_GPIO3B3_SEL_SRC_CTRL |
			   RK3308B_GRF_GPIO3B2_SEL_SRC_CTRL);
	if (ret)
		return ret;

	return 0;
}

static int rk3308_pinctrl_probe(struct udevice *dev)
{
	int ret;

	if (soc_is_rk3308b())
		dev->driver_data = (ulong)&rk3308b_pin_ctrl;

	ret = rockchip_pinctrl_probe(dev);
	if (ret)
		return ret;

	if (soc_is_rk3308b())
		ret = rk3308b_soc_data_init(dev);

	return ret;
}

U_BOOT_DRIVER(pinctrl_rk3308) = {
	.name		= "rockchip_rk3308_pinctrl",
	.id		= UCLASS_PINCTRL,
	.of_match	= rk3308_pinctrl_ids,
	.priv_auto_alloc_size = sizeof(struct rockchip_pinctrl_priv),
	.ops		= &rockchip_pinctrl_ops,
#if !CONFIG_IS_ENABLED(OF_PLATDATA)
	.bind		= dm_scan_fdt_dev,
#endif
	.probe		= rk3308_pinctrl_probe,
};
