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

static struct rockchip_mux_recalced_data rv1126_mux_recalced_data[] = {
	{
		.num = 0,
		.pin = 20,
		.reg = 0x10000,
		.bit = 0,
		.mask = 0xf
	},
	{
		.num = 0,
		.pin = 21,
		.reg = 0x10000,
		.bit = 4,
		.mask = 0xf
	},
	{
		.num = 0,
		.pin = 22,
		.reg = 0x10000,
		.bit = 8,
		.mask = 0xf
	},
	{
		.num = 0,
		.pin = 23,
		.reg = 0x10000,
		.bit = 12,
		.mask = 0xf
	},
};

static struct rockchip_mux_route_data rv1126_mux_route_data[] = {
	MR_TOPGRF(RK_GPIO3, RK_PD2, RK_FUNC_1, 0x10260, RK_GENMASK_VAL(0, 0, 0)), /* I2S0_MCLK_M0 */
	MR_TOPGRF(RK_GPIO3, RK_PB0, RK_FUNC_3, 0x10260, RK_GENMASK_VAL(0, 0, 1)), /* I2S0_MCLK_M1 */

	MR_TOPGRF(RK_GPIO0, RK_PD4, RK_FUNC_4, 0x10260, RK_GENMASK_VAL(3, 2, 0)), /* I2S1_MCLK_M0 */
	MR_TOPGRF(RK_GPIO1, RK_PD5, RK_FUNC_2, 0x10260, RK_GENMASK_VAL(3, 2, 1)), /* I2S1_MCLK_M1 */
	MR_TOPGRF(RK_GPIO2, RK_PC7, RK_FUNC_6, 0x10260, RK_GENMASK_VAL(3, 2, 2)), /* I2S1_MCLK_M2 */

	MR_TOPGRF(RK_GPIO1, RK_PD0, RK_FUNC_1, 0x10260, RK_GENMASK_VAL(4, 4, 0)), /* I2S2_MCLK_M0 */
	MR_TOPGRF(RK_GPIO2, RK_PB3, RK_FUNC_2, 0x10260, RK_GENMASK_VAL(4, 4, 1)), /* I2S2_MCLK_M1 */

	MR_TOPGRF(RK_GPIO3, RK_PD4, RK_FUNC_2, 0x10260, RK_GENMASK_VAL(12, 12, 0)), /* PDM_CLK0_M0 */
	MR_TOPGRF(RK_GPIO3, RK_PC0, RK_FUNC_3, 0x10260, RK_GENMASK_VAL(12, 12, 1)), /* PDM_CLK0_M1 */

	MR_TOPGRF(RK_GPIO3, RK_PC6, RK_FUNC_1, 0x10264, RK_GENMASK_VAL(0, 0, 0)), /* CIF_CLKOUT_M0 */
	MR_TOPGRF(RK_GPIO2, RK_PD1, RK_FUNC_3, 0x10264, RK_GENMASK_VAL(0, 0, 1)), /* CIF_CLKOUT_M1 */

	MR_TOPGRF(RK_GPIO3, RK_PA4, RK_FUNC_5, 0x10264, RK_GENMASK_VAL(5, 4, 0)), /* I2C3_SCL_M0 */
	MR_TOPGRF(RK_GPIO2, RK_PD4, RK_FUNC_7, 0x10264, RK_GENMASK_VAL(5, 4, 1)), /* I2C3_SCL_M1 */
	MR_TOPGRF(RK_GPIO1, RK_PD6, RK_FUNC_3, 0x10264, RK_GENMASK_VAL(5, 4, 2)), /* I2C3_SCL_M2 */

	MR_TOPGRF(RK_GPIO3, RK_PA0, RK_FUNC_7, 0x10264, RK_GENMASK_VAL(6, 6, 0)), /* I2C4_SCL_M0 */
	MR_TOPGRF(RK_GPIO4, RK_PA0, RK_FUNC_4, 0x10264, RK_GENMASK_VAL(6, 6, 1)), /* I2C4_SCL_M1 */

	MR_TOPGRF(RK_GPIO2, RK_PA5, RK_FUNC_7, 0x10264, RK_GENMASK_VAL(9, 8, 0)), /* I2C5_SCL_M0 */
	MR_TOPGRF(RK_GPIO3, RK_PB0, RK_FUNC_5, 0x10264, RK_GENMASK_VAL(9, 8, 1)), /* I2C5_SCL_M1 */
	MR_TOPGRF(RK_GPIO1, RK_PD0, RK_FUNC_4, 0x10264, RK_GENMASK_VAL(9, 8, 2)), /* I2C5_SCL_M2 */

	MR_TOPGRF(RK_GPIO3, RK_PC0, RK_FUNC_5, 0x10264, RK_GENMASK_VAL(11, 10, 0)), /* SPI1_CLK_M0 */
	MR_TOPGRF(RK_GPIO1, RK_PC6, RK_FUNC_3, 0x10264, RK_GENMASK_VAL(11, 10, 1)), /* SPI1_CLK_M1 */
	MR_TOPGRF(RK_GPIO2, RK_PD5, RK_FUNC_6, 0x10264, RK_GENMASK_VAL(11, 10, 2)), /* SPI1_CLK_M2 */

	MR_TOPGRF(RK_GPIO3, RK_PC0, RK_FUNC_2, 0x10264, RK_GENMASK_VAL(12, 12, 0)), /* RGMII_CLK_M0 */
	MR_TOPGRF(RK_GPIO2, RK_PB7, RK_FUNC_2, 0x10264, RK_GENMASK_VAL(12, 12, 1)), /* RGMII_CLK_M1 */

	MR_TOPGRF(RK_GPIO3, RK_PA1, RK_FUNC_3, 0x10264, RK_GENMASK_VAL(13, 13, 0)), /* CAN_TXD_M0 */
	MR_TOPGRF(RK_GPIO3, RK_PA7, RK_FUNC_5, 0x10264, RK_GENMASK_VAL(13, 13, 1)), /* CAN_TXD_M1 */

	MR_TOPGRF(RK_GPIO3, RK_PA4, RK_FUNC_6, 0x10268, RK_GENMASK_VAL(0, 0, 0)), /* PWM8_M0 */
	MR_TOPGRF(RK_GPIO2, RK_PD7, RK_FUNC_5, 0x10268, RK_GENMASK_VAL(0, 0, 1)), /* PWM8_M1 */

	MR_TOPGRF(RK_GPIO3, RK_PA5, RK_FUNC_6, 0x10268, RK_GENMASK_VAL(2, 2, 0)), /* PWM9_M0 */
	MR_TOPGRF(RK_GPIO2, RK_PD6, RK_FUNC_5, 0x10268, RK_GENMASK_VAL(2, 2, 1)), /* PWM9_M1 */

	MR_TOPGRF(RK_GPIO3, RK_PA6, RK_FUNC_6, 0x10268, RK_GENMASK_VAL(4, 4, 0)), /* PWM10_M0 */
	MR_TOPGRF(RK_GPIO2, RK_PD5, RK_FUNC_5, 0x10268, RK_GENMASK_VAL(4, 4, 1)), /* PWM10_M1 */

	MR_TOPGRF(RK_GPIO3, RK_PA7, RK_FUNC_6, 0x10268, RK_GENMASK_VAL(6, 6, 0)), /* PWM11_IR_M0 */
	MR_TOPGRF(RK_GPIO3, RK_PA1, RK_FUNC_5, 0x10268, RK_GENMASK_VAL(6, 6, 1)), /* PWM11_IR_M1 */

	MR_TOPGRF(RK_GPIO1, RK_PA5, RK_FUNC_3, 0x10268, RK_GENMASK_VAL(8, 8, 0)), /* UART2_TX_M0 */
	MR_TOPGRF(RK_GPIO3, RK_PA2, RK_FUNC_1, 0x10268, RK_GENMASK_VAL(8, 8, 1)), /* UART2_TX_M1 */

	MR_TOPGRF(RK_GPIO3, RK_PC6, RK_FUNC_3, 0x10268, RK_GENMASK_VAL(11, 10, 0)), /* UART3_TX_M0 */
	MR_TOPGRF(RK_GPIO1, RK_PA7, RK_FUNC_2, 0x10268, RK_GENMASK_VAL(11, 10, 1)), /* UART3_TX_M1 */
	MR_TOPGRF(RK_GPIO3, RK_PA0, RK_FUNC_4, 0x10268, RK_GENMASK_VAL(11, 10, 2)), /* UART3_TX_M2 */

	MR_TOPGRF(RK_GPIO3, RK_PA4, RK_FUNC_4, 0x10268, RK_GENMASK_VAL(13, 12, 0)), /* UART4_TX_M0 */
	MR_TOPGRF(RK_GPIO2, RK_PA6, RK_FUNC_4, 0x10268, RK_GENMASK_VAL(13, 12, 1)), /* UART4_TX_M1 */
	MR_TOPGRF(RK_GPIO1, RK_PD5, RK_FUNC_3, 0x10268, RK_GENMASK_VAL(13, 12, 2)), /* UART4_TX_M2 */

	MR_TOPGRF(RK_GPIO3, RK_PA6, RK_FUNC_4, 0x10268, RK_GENMASK_VAL(15, 14, 0)), /* UART5_TX_M0 */
	MR_TOPGRF(RK_GPIO2, RK_PB0, RK_FUNC_4, 0x10268, RK_GENMASK_VAL(15, 14, 1)), /* UART5_TX_M1 */
	MR_TOPGRF(RK_GPIO2, RK_PA0, RK_FUNC_3, 0x10268, RK_GENMASK_VAL(15, 14, 2)), /* UART5_TX_M2 */

	MR_PMUGRF(RK_GPIO0, RK_PB6, RK_FUNC_3, 0x0114, RK_GENMASK_VAL(0, 0, 0)), /* PWM0_M0 */
	MR_PMUGRF(RK_GPIO2, RK_PB3, RK_FUNC_5, 0x0114, RK_GENMASK_VAL(0, 0, 1)), /* PWM0_M1 */

	MR_PMUGRF(RK_GPIO0, RK_PB7, RK_FUNC_3, 0x0114, RK_GENMASK_VAL(2, 2, 0)), /* PWM1_M0 */
	MR_PMUGRF(RK_GPIO2, RK_PB2, RK_FUNC_5, 0x0114, RK_GENMASK_VAL(2, 2, 1)), /* PWM1_M1 */

	MR_PMUGRF(RK_GPIO0, RK_PC0, RK_FUNC_3, 0x0114, RK_GENMASK_VAL(4, 4, 0)), /* PWM2_M0 */
	MR_PMUGRF(RK_GPIO2, RK_PB1, RK_FUNC_5, 0x0114, RK_GENMASK_VAL(4, 4, 1)), /* PWM2_M1 */

	MR_PMUGRF(RK_GPIO0, RK_PC1, RK_FUNC_3, 0x0114, RK_GENMASK_VAL(6, 6, 0)), /* PWM3_IR_M0 */
	MR_PMUGRF(RK_GPIO2, RK_PB0, RK_FUNC_5, 0x0114, RK_GENMASK_VAL(6, 6, 1)), /* PWM3_IR_M1 */

	MR_PMUGRF(RK_GPIO0, RK_PC2, RK_FUNC_3, 0x0114, RK_GENMASK_VAL(8, 8, 0)), /* PWM4_M0 */
	MR_PMUGRF(RK_GPIO2, RK_PA7, RK_FUNC_5, 0x0114, RK_GENMASK_VAL(8, 8, 1)), /* PWM4_M1 */

	MR_PMUGRF(RK_GPIO0, RK_PC3, RK_FUNC_3, 0x0114, RK_GENMASK_VAL(10, 10, 0)), /* PWM5_M0 */
	MR_PMUGRF(RK_GPIO2, RK_PA6, RK_FUNC_5, 0x0114, RK_GENMASK_VAL(10, 10, 1)), /* PWM5_M1 */

	MR_PMUGRF(RK_GPIO0, RK_PB2, RK_FUNC_3, 0x0114, RK_GENMASK_VAL(12, 12, 0)), /* PWM6_M0 */
	MR_PMUGRF(RK_GPIO2, RK_PD4, RK_FUNC_5, 0x0114, RK_GENMASK_VAL(12, 12, 1)), /* PWM6_M1 */

	MR_PMUGRF(RK_GPIO0, RK_PB1, RK_FUNC_3, 0x0114, RK_GENMASK_VAL(14, 14, 0)), /* PWM7_IR_M0 */
	MR_PMUGRF(RK_GPIO3, RK_PA0, RK_FUNC_5, 0x0114, RK_GENMASK_VAL(14, 14, 1)), /* PWM7_IR_M1 */

	MR_PMUGRF(RK_GPIO0, RK_PB0, RK_FUNC_1, 0x0118, RK_GENMASK_VAL(1, 0, 0)), /* SPI0_CLK_M0 */
	MR_PMUGRF(RK_GPIO2, RK_PA1, RK_FUNC_1, 0x0118, RK_GENMASK_VAL(1, 0, 1)), /* SPI0_CLK_M1 */
	MR_PMUGRF(RK_GPIO2, RK_PB2, RK_FUNC_6, 0x0118, RK_GENMASK_VAL(1, 0, 2)), /* SPI0_CLK_M2 */

	MR_PMUGRF(RK_GPIO0, RK_PB6, RK_FUNC_2, 0x0118, RK_GENMASK_VAL(2, 2, 0)), /* UART1_TX_M0 */
	MR_PMUGRF(RK_GPIO1, RK_PD0, RK_FUNC_5, 0x0118, RK_GENMASK_VAL(2, 2, 1)), /* UART1_TX_M1 */
	MR_PMUGRF(RK_GPIO0, RK_PC3, RK_FUNC_1, 0x0118, RK_GENMASK_VAL(4, 4, 1)), /* I2C2 */
};

static int rv1126_set_mux(struct rockchip_pin_bank *bank, int pin, int mux)
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

#define RV1126_PULL_PMU_OFFSET		0x40
#define RV1126_PULL_GRF_GPIO1A0_OFFSET		0x10108
#define RV1126_PULL_PINS_PER_REG	8
#define RV1126_PULL_BITS_PER_PIN	2
#define RV1126_PULL_BANK_STRIDE		16
#define RV1126_GPIO_C4_D7(p)	(p >= 20 && p <= 31) /* GPIO0_C4 ~ GPIO0_D7 */

static void rv1126_calc_pull_reg_and_bit(struct rockchip_pin_bank *bank,
					 int pin_num, struct regmap **regmap,
					 int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;

	/* The first 24 pins of the first bank are located in PMU */
	if (bank->bank_num == 0) {
		if (RV1126_GPIO_C4_D7(pin_num)) {
			*regmap = priv->regmap_base;
			*reg = RV1126_PULL_GRF_GPIO1A0_OFFSET;
			*reg -= (((31 - pin_num) / RV1126_PULL_PINS_PER_REG + 1) * 4);
			*bit = pin_num % RV1126_PULL_PINS_PER_REG;
			*bit *= RV1126_PULL_BITS_PER_PIN;
			return;
		}
		*regmap = priv->regmap_pmu;
		*reg = RV1126_PULL_PMU_OFFSET;
	} else {
		*reg = RV1126_PULL_GRF_GPIO1A0_OFFSET;
		*regmap = priv->regmap_base;
		*reg += (bank->bank_num - 1) * RV1126_PULL_BANK_STRIDE;
	}

	*reg += ((pin_num / RV1126_PULL_PINS_PER_REG) * 4);
	*bit = (pin_num % RV1126_PULL_PINS_PER_REG);
	*bit *= RV1126_PULL_BITS_PER_PIN;
}

static int rv1126_set_pull(struct rockchip_pin_bank *bank,
			   int pin_num, int pull)
{
	struct regmap *regmap;
	int reg, ret;
	u8 bit, type;
	u32 data;

	if (pull == PIN_CONFIG_BIAS_PULL_PIN_DEFAULT)
		return -ENOTSUPP;

	rv1126_calc_pull_reg_and_bit(bank, pin_num, &regmap, &reg, &bit);
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

#define RV1126_DRV_PMU_OFFSET		0x20
#define RV1126_DRV_GRF_GPIO1A0_OFFSET		0x10090
#define RV1126_DRV_BITS_PER_PIN		4
#define RV1126_DRV_PINS_PER_REG		4
#define RV1126_DRV_BANK_STRIDE		32

static void rv1126_calc_drv_reg_and_bit(struct rockchip_pin_bank *bank,
					int pin_num, struct regmap **regmap,
					int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;

	/* The first 24 pins of the first bank are located in PMU */
	if (bank->bank_num == 0) {
		if (RV1126_GPIO_C4_D7(pin_num)) {
			*regmap = priv->regmap_base;
			*reg = RV1126_DRV_GRF_GPIO1A0_OFFSET;
			*reg -= (((31 - pin_num) / RV1126_DRV_PINS_PER_REG + 1) * 4);
			*reg -= 0x4;
			*bit = pin_num % RV1126_DRV_PINS_PER_REG;
			*bit *= RV1126_DRV_BITS_PER_PIN;
			return;
		}
		*regmap = priv->regmap_pmu;
		*reg = RV1126_DRV_PMU_OFFSET;
	} else {
		*regmap = priv->regmap_base;
		*reg = RV1126_DRV_GRF_GPIO1A0_OFFSET;
		*reg += (bank->bank_num - 1) * RV1126_DRV_BANK_STRIDE;
	}

	*reg += ((pin_num / RV1126_DRV_PINS_PER_REG) * 4);
	*bit = pin_num % RV1126_DRV_PINS_PER_REG;
	*bit *= RV1126_DRV_BITS_PER_PIN;
}

static int rv1126_set_drive(struct rockchip_pin_bank *bank,
			    int pin_num, int strength)
{
	struct regmap *regmap;
	int reg;
	u32 data;
	u8 bit;

	rv1126_calc_drv_reg_and_bit(bank, pin_num, &regmap, &reg, &bit);

	/* enable the write to the equivalent lower bits */
	data = ((1 << ROCKCHIP_DRV_BITS_PER_PIN) - 1) << (bit + 16);
	data |= (strength << bit);

	return regmap_write(regmap, reg, data);
}

#define RV1126_SCHMITT_PMU_OFFSET		0x60
#define RV1126_SCHMITT_GRF_GPIO1A0_OFFSET		0x10188
#define RV1126_SCHMITT_BANK_STRIDE		16
#define RV1126_SCHMITT_PINS_PER_GRF_REG		8
#define RV1126_SCHMITT_PINS_PER_PMU_REG		8

static int rv1126_calc_schmitt_reg_and_bit(struct rockchip_pin_bank *bank,
					   int pin_num,
					   struct regmap **regmap,
					   int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;
	int pins_per_reg;

	if (bank->bank_num == 0) {
		if (RV1126_GPIO_C4_D7(pin_num)) {
			*regmap = priv->regmap_base;
			*reg = RV1126_SCHMITT_GRF_GPIO1A0_OFFSET;
			*reg -= (((31 - pin_num) / RV1126_SCHMITT_PINS_PER_GRF_REG + 1) * 4);
			*bit = pin_num % RV1126_SCHMITT_PINS_PER_GRF_REG;
			return 0;
		}
		*regmap = priv->regmap_pmu;
		*reg = RV1126_SCHMITT_PMU_OFFSET;
		pins_per_reg = RV1126_SCHMITT_PINS_PER_PMU_REG;
	} else {
		*regmap = priv->regmap_base;
		*reg = RV1126_SCHMITT_GRF_GPIO1A0_OFFSET;
		pins_per_reg = RV1126_SCHMITT_PINS_PER_GRF_REG;
		*reg += (bank->bank_num - 1) * RV1126_SCHMITT_BANK_STRIDE;
	}
	*reg += ((pin_num / pins_per_reg) * 4);
	*bit = pin_num % pins_per_reg;

	return 0;
}

static int rv1126_set_schmitt(struct rockchip_pin_bank *bank,
			      int pin_num, int enable)
{
	struct regmap *regmap;
	int reg;
	u8 bit;
	u32 data;

	rv1126_calc_schmitt_reg_and_bit(bank, pin_num, &regmap, &reg, &bit);
	/* enable the write to the equivalent lower bits */
	data = BIT(bit + 16) | (enable << bit);

	return regmap_write(regmap, reg, data);
}

static struct rockchip_pin_bank rv1126_pin_banks[] = {
	PIN_BANK_IOMUX_FLAGS(0, 32, "gpio0",
			     IOMUX_WIDTH_4BIT | IOMUX_SOURCE_PMU,
			     IOMUX_WIDTH_4BIT | IOMUX_SOURCE_PMU,
			     IOMUX_WIDTH_4BIT | IOMUX_L_SOURCE_PMU,
			     IOMUX_WIDTH_4BIT),
	PIN_BANK_IOMUX_FLAGS_OFFSET(1, 32, "gpio1",
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT,
			     0x10010, 0x10018, 0x10020, 0x10028),
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
	PIN_BANK_IOMUX_FLAGS(4, 2, "gpio4",
			     IOMUX_WIDTH_4BIT, 0, 0, 0),
};

static const struct rockchip_pin_ctrl rv1126_pin_ctrl = {
	.pin_banks		= rv1126_pin_banks,
	.nr_banks		= ARRAY_SIZE(rv1126_pin_banks),
	.nr_pins		= 130,
	.grf_mux_offset		= 0x10004, /* mux offset from GPIO0_D0 */
	.pmu_mux_offset		= 0x0,
	.iomux_routes		= rv1126_mux_route_data,
	.niomux_routes		= ARRAY_SIZE(rv1126_mux_route_data),
	.iomux_recalced		= rv1126_mux_recalced_data,
	.niomux_recalced	= ARRAY_SIZE(rv1126_mux_recalced_data),
	.set_mux		= rv1126_set_mux,
	.set_pull		= rv1126_set_pull,
	.set_drive		= rv1126_set_drive,
	.set_schmitt		= rv1126_set_schmitt,
};

static const struct udevice_id rv1126_pinctrl_ids[] = {
	{
		.compatible = "rockchip,rv1126-pinctrl",
		.data = (ulong)&rv1126_pin_ctrl
	},
	{ }
};

U_BOOT_DRIVER(pinctrl_rv1126) = {
	.name		= "rockchip_rv1126_pinctrl",
	.id		= UCLASS_PINCTRL,
	.of_match	= rv1126_pinctrl_ids,
	.priv_auto_alloc_size = sizeof(struct rockchip_pinctrl_priv),
	.ops		= &rockchip_pinctrl_ops,
#if !CONFIG_IS_ENABLED(OF_PLATDATA)
	.bind		= dm_scan_fdt_dev,
#endif
	.probe		= rockchip_pinctrl_probe,
};
