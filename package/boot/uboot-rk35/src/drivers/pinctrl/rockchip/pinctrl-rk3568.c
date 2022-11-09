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

static struct rockchip_mux_route_data rk3568_mux_route_data[] = {
	MR_TOPGRF(RK_GPIO0, RK_PB3, RK_FUNC_2, 0x0300, RK_GENMASK_VAL(0, 0, 0)), /* CAN0 IO mux selection M0 */
	MR_TOPGRF(RK_GPIO2, RK_PA1, RK_FUNC_4, 0x0300, RK_GENMASK_VAL(0, 0, 1)), /* CAN0 IO mux selection M1 */
	MR_TOPGRF(RK_GPIO1, RK_PA1, RK_FUNC_3, 0x0300, RK_GENMASK_VAL(2, 2, 0)), /* CAN1 IO mux selection M0 */
	MR_TOPGRF(RK_GPIO4, RK_PC3, RK_FUNC_3, 0x0300, RK_GENMASK_VAL(2, 2, 1)), /* CAN1 IO mux selection M1 */
	MR_TOPGRF(RK_GPIO4, RK_PB5, RK_FUNC_3, 0x0300, RK_GENMASK_VAL(4, 4, 0)), /* CAN2 IO mux selection M0 */
	MR_TOPGRF(RK_GPIO2, RK_PB2, RK_FUNC_4, 0x0300, RK_GENMASK_VAL(4, 4, 1)), /* CAN2 IO mux selection M1 */
	MR_TOPGRF(RK_GPIO4, RK_PC4, RK_FUNC_1, 0x0300, RK_GENMASK_VAL(6, 6, 0)), /* EDPDP_HPDIN IO mux selection M0 */
	MR_TOPGRF(RK_GPIO0, RK_PC2, RK_FUNC_2, 0x0300, RK_GENMASK_VAL(6, 6, 1)), /* EDPDP_HPDIN IO mux selection M1 */
	MR_TOPGRF(RK_GPIO3, RK_PB1, RK_FUNC_3, 0x0300, RK_GENMASK_VAL(8, 8, 0)), /* GMAC1 IO mux selection M0 */
	MR_TOPGRF(RK_GPIO4, RK_PA7, RK_FUNC_3, 0x0300, RK_GENMASK_VAL(8, 8, 1)), /* GMAC1 IO mux selection M1 */
	MR_TOPGRF(RK_GPIO4, RK_PD1, RK_FUNC_1, 0x0300, RK_GENMASK_VAL(10, 10, 0)), /* HDMITX IO mux selection M0 */
	MR_TOPGRF(RK_GPIO0, RK_PC7, RK_FUNC_1, 0x0300, RK_GENMASK_VAL(10, 10, 1)), /* HDMITX IO mux selection M1 */
	MR_TOPGRF(RK_GPIO0, RK_PB6, RK_FUNC_1, 0x0300, RK_GENMASK_VAL(14, 14, 0)), /* I2C2 IO mux selection M0 */
	MR_TOPGRF(RK_GPIO4, RK_PB4, RK_FUNC_1, 0x0300, RK_GENMASK_VAL(14, 14, 1)), /* I2C2 IO mux selection M1 */
	MR_TOPGRF(RK_GPIO1, RK_PA0, RK_FUNC_1, 0x0304, RK_GENMASK_VAL(0, 0, 0)), /* I2C3 IO mux selection M0 */
	MR_TOPGRF(RK_GPIO3, RK_PB6, RK_FUNC_4, 0x0304, RK_GENMASK_VAL(0, 0, 1)), /* I2C3 IO mux selection M1 */
	MR_TOPGRF(RK_GPIO4, RK_PB2, RK_FUNC_1, 0x0304, RK_GENMASK_VAL(2, 2, 0)), /* I2C4 IO mux selection M0 */
	MR_TOPGRF(RK_GPIO2, RK_PB1, RK_FUNC_2, 0x0304, RK_GENMASK_VAL(2, 2, 1)), /* I2C4 IO mux selection M1 */
	MR_TOPGRF(RK_GPIO3, RK_PB4, RK_FUNC_4, 0x0304, RK_GENMASK_VAL(4, 4, 0)), /* I2C5 IO mux selection M0 */
	MR_TOPGRF(RK_GPIO4, RK_PD0, RK_FUNC_2, 0x0304, RK_GENMASK_VAL(4, 4, 1)), /* I2C5 IO mux selection M1 */
	MR_TOPGRF(RK_GPIO3, RK_PD2, RK_FUNC_1, 0x0304, RK_GENMASK_VAL(6, 6, 0)), /* PWM4 IO mux selection M0 */
	MR_TOPGRF(RK_GPIO3, RK_PD2, RK_FUNC_1, 0x0304, RK_GENMASK_VAL(6, 6, 1)), /* PWM4 IO mux selection M1 */
	MR_TOPGRF(RK_GPIO3, RK_PD2, RK_FUNC_1, 0x0304, RK_GENMASK_VAL(8, 8, 0)), /* PWM5 IO mux selection M0 */
	MR_TOPGRF(RK_GPIO3, RK_PD2, RK_FUNC_1, 0x0304, RK_GENMASK_VAL(8, 8, 1)), /* PWM5 IO mux selection M1 */
	MR_TOPGRF(RK_GPIO3, RK_PD2, RK_FUNC_1, 0x0304, RK_GENMASK_VAL(10, 10, 0)), /* PWM6 IO mux selection M0 */
	MR_TOPGRF(RK_GPIO3, RK_PD2, RK_FUNC_1, 0x0304, RK_GENMASK_VAL(10, 10, 1)), /* PWM6 IO mux selection M1 */
	MR_TOPGRF(RK_GPIO3, RK_PD2, RK_FUNC_1, 0x0304, RK_GENMASK_VAL(12, 12, 0)), /* PWM7 IO mux selection M0 */
	MR_TOPGRF(RK_GPIO3, RK_PD2, RK_FUNC_1, 0x0304, RK_GENMASK_VAL(12, 12, 1)), /* PWM7 IO mux selection M1 */
	MR_TOPGRF(RK_GPIO3, RK_PD2, RK_FUNC_1, 0x0304, RK_GENMASK_VAL(14, 14, 0)), /* PWM8 IO mux selection M0 */
	MR_TOPGRF(RK_GPIO3, RK_PD2, RK_FUNC_1, 0x0304, RK_GENMASK_VAL(14, 14, 1)), /* PWM8 IO mux selection M1 */
	MR_TOPGRF(RK_GPIO3, RK_PD2, RK_FUNC_1, 0x0308, RK_GENMASK_VAL(0, 0, 0)), /* PWM9 IO mux selection M0 */
	MR_TOPGRF(RK_GPIO3, RK_PD2, RK_FUNC_1, 0x0308, RK_GENMASK_VAL(0, 0, 1)), /* PWM9 IO mux selection M1 */
	MR_TOPGRF(RK_GPIO3, RK_PD2, RK_FUNC_1, 0x0308, RK_GENMASK_VAL(2, 2, 0)), /* PWM10 IO mux selection M0 */
	MR_TOPGRF(RK_GPIO3, RK_PD2, RK_FUNC_1, 0x0308, RK_GENMASK_VAL(2, 2, 1)), /* PWM10 IO mux selection M1 */
	MR_TOPGRF(RK_GPIO3, RK_PD2, RK_FUNC_1, 0x0308, RK_GENMASK_VAL(4, 4, 0)), /* PWM11 IO mux selection M0 */
	MR_TOPGRF(RK_GPIO3, RK_PD2, RK_FUNC_1, 0x0308, RK_GENMASK_VAL(4, 4, 1)), /* PWM11 IO mux selection M1 */
	MR_TOPGRF(RK_GPIO3, RK_PD2, RK_FUNC_1, 0x0308, RK_GENMASK_VAL(6, 6, 0)), /* PWM12 IO mux selection M0 */
	MR_TOPGRF(RK_GPIO3, RK_PD2, RK_FUNC_1, 0x0308, RK_GENMASK_VAL(6, 6, 1)), /* PWM12 IO mux selection M1 */
	MR_TOPGRF(RK_GPIO3, RK_PD2, RK_FUNC_1, 0x0308, RK_GENMASK_VAL(8, 8, 0)), /* PWM13 IO mux selection M0 */
	MR_TOPGRF(RK_GPIO3, RK_PD2, RK_FUNC_1, 0x0308, RK_GENMASK_VAL(8, 8, 1)), /* PWM13 IO mux selection M1 */
	MR_TOPGRF(RK_GPIO3, RK_PD2, RK_FUNC_1, 0x0308, RK_GENMASK_VAL(10, 10, 0)), /* PWM14 IO mux selection M0 */
	MR_TOPGRF(RK_GPIO3, RK_PD2, RK_FUNC_1, 0x0308, RK_GENMASK_VAL(10, 10, 1)), /* PWM14 IO mux selection M1 */
	MR_TOPGRF(RK_GPIO3, RK_PD2, RK_FUNC_1, 0x0308, RK_GENMASK_VAL(12, 12, 0)), /* PWM15 IO mux selection M0 */
	MR_TOPGRF(RK_GPIO3, RK_PD2, RK_FUNC_1, 0x0308, RK_GENMASK_VAL(12, 12, 1)), /* PWM15 IO mux selection M1 */
	MR_TOPGRF(RK_GPIO3, RK_PD2, RK_FUNC_3, 0x0308, RK_GENMASK_VAL(14, 14, 0)), /* SDMMC2 IO mux selection M0 */
	MR_TOPGRF(RK_GPIO3, RK_PA5, RK_FUNC_5, 0x0308, RK_GENMASK_VAL(14, 14, 1)), /* SDMMC2 IO mux selection M1 */
	MR_TOPGRF(RK_GPIO0, RK_PB5, RK_FUNC_2, 0x030c, RK_GENMASK_VAL(0, 0, 0)), /* SPI0 IO mux selection M0 */
	MR_TOPGRF(RK_GPIO2, RK_PD3, RK_FUNC_3, 0x030c, RK_GENMASK_VAL(0, 0, 1)), /* SPI0 IO mux selection M1 */
	MR_TOPGRF(RK_GPIO2, RK_PB5, RK_FUNC_3, 0x030c, RK_GENMASK_VAL(2, 2, 0)), /* SPI1 IO mux selection M0 */
	MR_TOPGRF(RK_GPIO3, RK_PC3, RK_FUNC_3, 0x030c, RK_GENMASK_VAL(2, 2, 1)), /* SPI1 IO mux selection M1 */
	MR_TOPGRF(RK_GPIO2, RK_PC1, RK_FUNC_4, 0x030c, RK_GENMASK_VAL(4, 4, 0)), /* SPI2 IO mux selection M0 */
	MR_TOPGRF(RK_GPIO3, RK_PA0, RK_FUNC_3, 0x030c, RK_GENMASK_VAL(4, 4, 1)), /* SPI2 IO mux selection M1 */
	MR_TOPGRF(RK_GPIO4, RK_PB3, RK_FUNC_4, 0x030c, RK_GENMASK_VAL(6, 6, 0)), /* SPI3 IO mux selection M0 */
	MR_TOPGRF(RK_GPIO4, RK_PC2, RK_FUNC_2, 0x030c, RK_GENMASK_VAL(6, 6, 1)), /* SPI3 IO mux selection M1 */
	MR_TOPGRF(RK_GPIO2, RK_PB4, RK_FUNC_2, 0x030c, RK_GENMASK_VAL(8, 8, 0)), /* UART1 IO mux selection M0 */
	MR_TOPGRF(RK_GPIO0, RK_PD1, RK_FUNC_1, 0x030c, RK_GENMASK_VAL(8, 8, 1)), /* UART1 IO mux selection M1 */
	MR_TOPGRF(RK_GPIO0, RK_PD1, RK_FUNC_1, 0x030c, RK_GENMASK_VAL(10, 10, 0)), /* UART2 IO mux selection M0 */
	MR_TOPGRF(RK_GPIO1, RK_PD5, RK_FUNC_2, 0x030c, RK_GENMASK_VAL(10, 10, 1)), /* UART2 IO mux selection M1 */
	MR_TOPGRF(RK_GPIO1, RK_PA1, RK_FUNC_2, 0x030c, RK_GENMASK_VAL(12, 12, 0)), /* UART3 IO mux selection M0 */
	MR_TOPGRF(RK_GPIO3, RK_PB7, RK_FUNC_4, 0x030c, RK_GENMASK_VAL(12, 12, 1)), /* UART3 IO mux selection M1 */
	MR_TOPGRF(RK_GPIO1, RK_PA6, RK_FUNC_2, 0x030c, RK_GENMASK_VAL(14, 14, 0)), /* UART4 IO mux selection M0 */
	MR_TOPGRF(RK_GPIO3, RK_PB2, RK_FUNC_4, 0x030c, RK_GENMASK_VAL(14, 14, 1)), /* UART4 IO mux selection M1 */
	MR_TOPGRF(RK_GPIO2, RK_PA2, RK_FUNC_3, 0x0310, RK_GENMASK_VAL(0, 0, 0)), /* UART5 IO mux selection M0 */
	MR_TOPGRF(RK_GPIO3, RK_PC2, RK_FUNC_4, 0x0310, RK_GENMASK_VAL(0, 0, 1)), /* UART5 IO mux selection M1 */
	MR_TOPGRF(RK_GPIO2, RK_PA4, RK_FUNC_3, 0x0310, RK_GENMASK_VAL(2, 2, 0)), /* UART6 IO mux selection M0 */
	MR_TOPGRF(RK_GPIO1, RK_PD5, RK_FUNC_3, 0x0310, RK_GENMASK_VAL(2, 2, 1)), /* UART6 IO mux selection M1 */
	MR_TOPGRF(RK_GPIO2, RK_PA6, RK_FUNC_3, 0x0310, RK_GENMASK_VAL(5, 4, 0)), /* UART7 IO mux selection M0 */
	MR_TOPGRF(RK_GPIO3, RK_PC4, RK_FUNC_4, 0x0310, RK_GENMASK_VAL(5, 4, 1)), /* UART7 IO mux selection M1 */
	MR_TOPGRF(RK_GPIO3, RK_PD2, RK_FUNC_1, 0x0310, RK_GENMASK_VAL(5, 4, 2)), /* UART7 IO mux selection M2 */
	MR_TOPGRF(RK_GPIO2, RK_PC5, RK_FUNC_3, 0x0310, RK_GENMASK_VAL(6, 6, 0)), /* UART8 IO mux selection M0 */
	MR_TOPGRF(RK_GPIO2, RK_PD7, RK_FUNC_4, 0x0310, RK_GENMASK_VAL(6, 6, 1)), /* UART8 IO mux selection M1 */
	MR_TOPGRF(RK_GPIO2, RK_PB0, RK_FUNC_3, 0x0310, RK_GENMASK_VAL(9, 8, 0)), /* UART9 IO mux selection M0 */
	MR_TOPGRF(RK_GPIO4, RK_PC5, RK_FUNC_4, 0x0310, RK_GENMASK_VAL(9, 8, 1)), /* UART9 IO mux selection M1 */
	MR_TOPGRF(RK_GPIO4, RK_PA4, RK_FUNC_4, 0x0310, RK_GENMASK_VAL(9, 8, 2)), /* UART9 IO mux selection M2 */
	MR_TOPGRF(RK_GPIO1, RK_PA2, RK_FUNC_1, 0x0310, RK_GENMASK_VAL(11, 10, 0)), /* I2S1 IO mux selection M0 */
	MR_TOPGRF(RK_GPIO3, RK_PC6, RK_FUNC_4, 0x0310, RK_GENMASK_VAL(11, 10, 1)), /* I2S1 IO mux selection M1 */
	MR_TOPGRF(RK_GPIO2, RK_PD0, RK_FUNC_5, 0x0310, RK_GENMASK_VAL(11, 10, 2)), /* I2S1 IO mux selection M2 */
	MR_TOPGRF(RK_GPIO2, RK_PC1, RK_FUNC_1, 0x0310, RK_GENMASK_VAL(12, 12, 0)), /* I2S2 IO mux selection M0 */
	MR_TOPGRF(RK_GPIO4, RK_PB6, RK_FUNC_5, 0x0310, RK_GENMASK_VAL(12, 12, 1)), /* I2S2 IO mux selection M1 */
	MR_TOPGRF(RK_GPIO3, RK_PA2, RK_FUNC_4, 0x0310, RK_GENMASK_VAL(14, 14, 0)), /* I2S3 IO mux selection M0 */
	MR_TOPGRF(RK_GPIO4, RK_PC2, RK_FUNC_5, 0x0310, RK_GENMASK_VAL(14, 14, 1)), /* I2S3 IO mux selection M1 */
	MR_TOPGRF(RK_GPIO1, RK_PA6, RK_FUNC_3, 0x0314, RK_GENMASK_VAL(0, 0, 0)), /* PDM IO mux selection M0 */
	MR_TOPGRF(RK_GPIO3, RK_PD6, RK_FUNC_5, 0x0314, RK_GENMASK_VAL(0, 0, 1)), /* PDM IO mux selection M1 */
	MR_TOPGRF(RK_GPIO0, RK_PA5, RK_FUNC_3, 0x0314, RK_GENMASK_VAL(3, 2, 0)), /* PCIE20 IO mux selection M0 */
	MR_TOPGRF(RK_GPIO2, RK_PD0, RK_FUNC_4, 0x0314, RK_GENMASK_VAL(3, 2, 1)), /* PCIE20 IO mux selection M1 */
	MR_TOPGRF(RK_GPIO1, RK_PB0, RK_FUNC_4, 0x0314, RK_GENMASK_VAL(3, 2, 2)), /* PCIE20 IO mux selection M2 */
	MR_TOPGRF(RK_GPIO0, RK_PA4, RK_FUNC_3, 0x0314, RK_GENMASK_VAL(5, 4, 0)), /* PCIE30X1 IO mux selection M0 */
	MR_TOPGRF(RK_GPIO2, RK_PD2, RK_FUNC_4, 0x0314, RK_GENMASK_VAL(5, 4, 1)), /* PCIE30X1 IO mux selection M1 */
	MR_TOPGRF(RK_GPIO1, RK_PA5, RK_FUNC_4, 0x0314, RK_GENMASK_VAL(5, 4, 2)), /* PCIE30X1 IO mux selection M2 */
	MR_TOPGRF(RK_GPIO0, RK_PA6, RK_FUNC_2, 0x0314, RK_GENMASK_VAL(7, 6, 0)), /* PCIE30X2 IO mux selection M0 */
	MR_TOPGRF(RK_GPIO2, RK_PD4, RK_FUNC_4, 0x0314, RK_GENMASK_VAL(7, 6, 1)), /* PCIE30X2 IO mux selection M1 */
	MR_TOPGRF(RK_GPIO4, RK_PC2, RK_FUNC_4, 0x0314, RK_GENMASK_VAL(7, 6, 2)), /* PCIE30X2 IO mux selection M2 */
};

static int rk3568_set_mux(struct rockchip_pin_bank *bank, int pin, int mux)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;
	int iomux_num = (pin / 8);
	struct regmap *regmap;
	int reg, ret, mask;
	u8 bit;
	u32 data;

	debug("setting mux of GPIO%d-%d to %d\n", bank->bank_num, pin, mux);

	if (bank->iomux[iomux_num].type & IOMUX_SOURCE_PMU)
		regmap = priv->regmap_pmu;
	else
		regmap = priv->regmap_base;

	reg = bank->iomux[iomux_num].offset;
	if ((pin % 8) >= 4)
		reg += 0x4;
	bit = (pin % 4) * 4;
	mask = 0xf;

	data = (mask << (bit + 16));
	data |= (mux & mask) << bit;
	ret = regmap_write(regmap, reg, data);

	return ret;
}

#define RK3568_PULL_PMU_OFFSET		0x20
#define RK3568_PULL_GRF_OFFSET		0x80
#define RK3568_PULL_BITS_PER_PIN	2
#define RK3568_PULL_PINS_PER_REG	8
#define RK3568_PULL_BANK_STRIDE		0x10

static void rk3568_calc_pull_reg_and_bit(struct rockchip_pin_bank *bank,
					 int pin_num, struct regmap **regmap,
					 int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *info = bank->priv;

	if (bank->bank_num == 0) {
		*regmap = info->regmap_pmu;
		*reg = RK3568_PULL_PMU_OFFSET;
		*reg += bank->bank_num * RK3568_PULL_BANK_STRIDE;
	} else {
		*regmap = info->regmap_base;
		*reg = RK3568_PULL_GRF_OFFSET;
		*reg += (bank->bank_num - 1) * RK3568_PULL_BANK_STRIDE;
	}

	*reg += ((pin_num / RK3568_PULL_PINS_PER_REG) * 4);
	*bit = (pin_num % RK3568_PULL_PINS_PER_REG);
	*bit *= RK3568_PULL_BITS_PER_PIN;
}

#define RK3568_DRV_PMU_OFFSET		0x70
#define RK3568_DRV_GRF_OFFSET		0x200
#define RK3568_DRV_BITS_PER_PIN		8
#define RK3568_DRV_PINS_PER_REG		2
#define RK3568_DRV_BANK_STRIDE		0x40

static void rk3568_calc_drv_reg_and_bit(struct rockchip_pin_bank *bank,
					int pin_num, struct regmap **regmap,
					int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *info = bank->priv;

	/* The first 32 pins of the first bank are located in PMU */
	if (bank->bank_num == 0) {
		*regmap = info->regmap_pmu;
		*reg = RK3568_DRV_PMU_OFFSET;
	} else {
		*regmap = info->regmap_base;
		*reg = RK3568_DRV_GRF_OFFSET;
		*reg += (bank->bank_num - 1) * RK3568_DRV_BANK_STRIDE;
	}

	*reg += ((pin_num / RK3568_DRV_PINS_PER_REG) * 4);
	*bit = (pin_num % RK3568_DRV_PINS_PER_REG);
	*bit *= RK3568_DRV_BITS_PER_PIN;
}

#define RK3568_SCHMITT_BITS_PER_PIN		2
#define RK3568_SCHMITT_PINS_PER_REG		8
#define RK3568_SCHMITT_BANK_STRIDE		0x10
#define RK3568_SCHMITT_GRF_OFFSET		0xc0
#define RK3568_SCHMITT_PMUGRF_OFFSET		0x30

static int rk3568_calc_schmitt_reg_and_bit(struct rockchip_pin_bank *bank,
					   int pin_num, struct regmap **regmap,
					   int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *info = bank->priv;

	if (bank->bank_num == 0) {
		*regmap = info->regmap_pmu;
		*reg = RK3568_SCHMITT_PMUGRF_OFFSET;
	} else {
		*regmap = info->regmap_base;
		*reg = RK3568_SCHMITT_GRF_OFFSET;
		*reg += (bank->bank_num - 1) * RK3568_SCHMITT_BANK_STRIDE;
	}

	*reg += ((pin_num / RK3568_SCHMITT_PINS_PER_REG) * 4);
	*bit = pin_num % RK3568_SCHMITT_PINS_PER_REG;
	*bit *= RK3568_SCHMITT_BITS_PER_PIN;

	return 0;
}

static int rk3568_set_pull(struct rockchip_pin_bank *bank,
			   int pin_num, int pull)
{
	struct regmap *regmap;
	int reg, ret;
	u8 bit, type;
	u32 data;

	if (pull == PIN_CONFIG_BIAS_PULL_PIN_DEFAULT)
		return -ENOTSUPP;

	rk3568_calc_pull_reg_and_bit(bank, pin_num, &regmap, &reg, &bit);
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

static int rk3568_set_drive(struct rockchip_pin_bank *bank,
			    int pin_num, int strength)
{
	struct regmap *regmap;
	int reg;
	u32 data;
	u8 bit;
	int drv = (1 << (strength + 1)) - 1;
	int ret = 0;

	rk3568_calc_drv_reg_and_bit(bank, pin_num, &regmap, &reg, &bit);

	/* enable the write to the equivalent lower bits */
	data = ((1 << RK3568_DRV_BITS_PER_PIN) - 1) << (bit + 16);
	data |= (drv << bit);

	ret = regmap_write(regmap, reg, data);
	if (ret)
		return ret;

	if (bank->bank_num == 1 && pin_num == 21)
		reg = 0x0840;
	else if (bank->bank_num == 2 && pin_num == 2)
		reg = 0x0844;
	else if (bank->bank_num == 2 && pin_num == 8)
		reg = 0x0848;
	else if (bank->bank_num == 3 && pin_num == 0)
		reg = 0x084c;
	else if (bank->bank_num == 3 && pin_num == 6)
		reg = 0x0850;
	else if (bank->bank_num == 4 && pin_num == 0)
		reg = 0x0854;
	else
		return 0;

	data = ((1 << RK3568_DRV_BITS_PER_PIN) - 1) << 16;
	data |= drv;

	return regmap_write(regmap, reg, data);
}

static int rk3568_set_schmitt(struct rockchip_pin_bank *bank,
			      int pin_num, int enable)
{
	struct regmap *regmap;
	int reg;
	u32 data;
	u8 bit;

	rk3568_calc_schmitt_reg_and_bit(bank, pin_num, &regmap, &reg, &bit);

	/* enable the write to the equivalent lower bits */
	data = ((1 << RK3568_SCHMITT_BITS_PER_PIN) - 1) << (bit + 16);
	data |= (enable << bit);

	return regmap_write(regmap, reg, data);
}
static struct rockchip_pin_bank rk3568_pin_banks[] = {
	PIN_BANK_IOMUX_FLAGS(0, 32, "gpio0", IOMUX_SOURCE_PMU | IOMUX_WIDTH_4BIT,
			     IOMUX_SOURCE_PMU | IOMUX_WIDTH_4BIT,
			     IOMUX_SOURCE_PMU | IOMUX_WIDTH_4BIT,
			     IOMUX_SOURCE_PMU | IOMUX_WIDTH_4BIT),
	PIN_BANK_IOMUX_FLAGS(1, 32, "gpio1", IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT),
	PIN_BANK_IOMUX_FLAGS(2, 32, "gpio2", IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT),
	PIN_BANK_IOMUX_FLAGS(3, 32, "gpio3", IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT),
	PIN_BANK_IOMUX_FLAGS(4, 32, "gpio4", IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT,
			     IOMUX_WIDTH_4BIT),
};

static const struct rockchip_pin_ctrl rk3568_pin_ctrl = {
	.pin_banks		= rk3568_pin_banks,
	.nr_banks		= ARRAY_SIZE(rk3568_pin_banks),
	.nr_pins		= 160,
	.grf_mux_offset		= 0x0,
	.pmu_mux_offset		= 0x0,
	.iomux_routes		= rk3568_mux_route_data,
	.niomux_routes		= ARRAY_SIZE(rk3568_mux_route_data),
	.set_mux		= rk3568_set_mux,
	.set_pull		= rk3568_set_pull,
	.set_drive		= rk3568_set_drive,
	.set_schmitt		= rk3568_set_schmitt,
};

static const struct udevice_id rk3568_pinctrl_ids[] = {
	{
		.compatible = "rockchip,rk3568-pinctrl",
		.data = (ulong)&rk3568_pin_ctrl
	},
	{ }
};

U_BOOT_DRIVER(pinctrl_rk3568) = {
	.name		= "rockchip_rk3568_pinctrl",
	.id		= UCLASS_PINCTRL,
	.of_match	= rk3568_pinctrl_ids,
	.priv_auto_alloc_size = sizeof(struct rockchip_pinctrl_priv),
	.ops		= &rockchip_pinctrl_ops,
#if !CONFIG_IS_ENABLED(OF_PLATDATA)
	.bind		= dm_scan_fdt_dev,
#endif
	.probe		= rockchip_pinctrl_probe,
};
