// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2022 Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <dm.h>
#include <dm/pinctrl.h>
#include <regmap.h>
#include <syscon.h>

#include "pinctrl-rockchip.h"

static int rv1106_set_mux(struct rockchip_pin_bank *bank, int pin, int mux)
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

	debug("iomux write reg = %x data = %x\n", reg, data);

	ret = regmap_write(regmap, reg, data);

	return ret;
}

#define RV1106_DRV_BITS_PER_PIN		8
#define RV1106_DRV_PINS_PER_REG		2
#define RV1106_DRV_GPIO0_OFFSET		0x10
#define RV1106_DRV_GPIO1_OFFSET		0x80
#define RV1106_DRV_GPIO2_OFFSET		0x100C0
#define RV1106_DRV_GPIO3_OFFSET		0x20100
#define RV1106_DRV_GPIO4_OFFSET		0x30020

static void rv1106_calc_drv_reg_and_bit(struct rockchip_pin_bank *bank,
					int pin_num, struct regmap **regmap,
					int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;

	/* GPIO0_IOC is located in PMU */
	switch (bank->bank_num) {
	case 0:
		*regmap = priv->regmap_pmu;
		*reg = RV1106_DRV_GPIO0_OFFSET;
		break;

	case 1:
		*regmap = priv->regmap_base;
		*reg = RV1106_DRV_GPIO1_OFFSET;
		break;

	case 2:
		*regmap = priv->regmap_base;
		*reg = RV1106_DRV_GPIO2_OFFSET;
		break;

	case 3:
		*regmap = priv->regmap_base;
		*reg = RV1106_DRV_GPIO3_OFFSET;
		break;

	case 4:
		*regmap = priv->regmap_base;
		*reg = RV1106_DRV_GPIO4_OFFSET;
		break;

	default:
		*regmap = priv->regmap_base;
		*reg = 0;
		dev_err(priv->dev, "unsupported bank_num %d\n", bank->bank_num);
		break;
	}

	*reg += ((pin_num / RV1106_DRV_PINS_PER_REG) * 4);
	*bit = pin_num % RV1106_DRV_PINS_PER_REG;
	*bit *= RV1106_DRV_BITS_PER_PIN;
}

static int rv1106_set_drive(struct rockchip_pin_bank *bank,
			    int pin_num, int strength)
{
	struct regmap *regmap;
	int reg, ret;
	u32 data;
	u8 bit;
	int drv = (1 << (strength + 1)) - 1;

	rv1106_calc_drv_reg_and_bit(bank, pin_num, &regmap, &reg, &bit);

	/* enable the write to the equivalent lower bits */
	data = ((1 << RV1106_DRV_BITS_PER_PIN) - 1) << (bit + 16);
	data |= (drv << bit);
	ret = regmap_write(regmap, reg, data);

	return ret;
}

#define RV1106_PULL_BITS_PER_PIN		2
#define RV1106_PULL_PINS_PER_REG		8
#define RV1106_PULL_GPIO0_OFFSET		0x38
#define RV1106_PULL_GPIO1_OFFSET		0x1C0
#define RV1106_PULL_GPIO2_OFFSET		0x101D0
#define RV1106_PULL_GPIO3_OFFSET		0x201E0
#define RV1106_PULL_GPIO4_OFFSET		0x30070

static void rv1106_calc_pull_reg_and_bit(struct rockchip_pin_bank *bank,
					 int pin_num, struct regmap **regmap,
					 int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;

	/* GPIO0_IOC is located in PMU */
	switch (bank->bank_num) {
	case 0:
		*regmap = priv->regmap_pmu;
		*reg = RV1106_PULL_GPIO0_OFFSET;
		break;

	case 1:
		*regmap = priv->regmap_base;
		*reg = RV1106_PULL_GPIO1_OFFSET;
		break;

	case 2:
		*regmap = priv->regmap_base;
		*reg = RV1106_PULL_GPIO2_OFFSET;
		break;

	case 3:
		*regmap = priv->regmap_base;
		*reg = RV1106_PULL_GPIO3_OFFSET;
		break;

	case 4:
		*regmap = priv->regmap_base;
		*reg = RV1106_PULL_GPIO4_OFFSET;
		break;

	default:
		*regmap = priv->regmap_base;
		*reg = 0;
		dev_err(priv->dev, "unsupported bank_num %d\n", bank->bank_num);
		break;
	}

	*reg += ((pin_num / RV1106_PULL_PINS_PER_REG) * 4);
	*bit = pin_num % RV1106_PULL_PINS_PER_REG;
	*bit *= RV1106_PULL_BITS_PER_PIN;
}

static int rv1106_set_pull(struct rockchip_pin_bank *bank,
			   int pin_num, int pull)
{
	struct regmap *regmap;
	int reg, ret;
	u8 bit, type;
	u32 data;

	if (pull == PIN_CONFIG_BIAS_PULL_PIN_DEFAULT)
		return -ENOTSUPP;

	rv1106_calc_pull_reg_and_bit(bank, pin_num, &regmap, &reg, &bit);
	type = bank->pull_type[pin_num / 8];
	ret = rockchip_translate_pull_value(type, pull);
	if (ret < 0) {
		debug("unsupported pull setting %d\n", pull);
		return ret;
	}

	/* enable the write to the equivalent lower bits */
	data = ((1 << RV1106_PULL_BITS_PER_PIN) - 1) << (bit + 16);

	data |= (ret << bit);
	ret = regmap_write(regmap, reg, data);

	return ret;
}

#define RV1106_SMT_BITS_PER_PIN		1
#define RV1106_SMT_PINS_PER_REG		8
#define RV1106_SMT_GPIO0_OFFSET		0x40
#define RV1106_SMT_GPIO1_OFFSET		0x280
#define RV1106_SMT_GPIO2_OFFSET		0x10290
#define RV1106_SMT_GPIO3_OFFSET		0x202A0
#define RV1106_SMT_GPIO4_OFFSET		0x300A0

static int rv1106_calc_schmitt_reg_and_bit(struct rockchip_pin_bank *bank,
					   int pin_num,
					   struct regmap **regmap,
					   int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;

	/* GPIO0_IOC is located in PMU */
	switch (bank->bank_num) {
	case 0:
		*regmap = priv->regmap_pmu;
		*reg = RV1106_SMT_GPIO0_OFFSET;
		break;

	case 1:
		*regmap = priv->regmap_base;
		*reg = RV1106_SMT_GPIO1_OFFSET;
		break;

	case 2:
		*regmap = priv->regmap_base;
		*reg = RV1106_SMT_GPIO2_OFFSET;
		break;

	case 3:
		*regmap = priv->regmap_base;
		*reg = RV1106_SMT_GPIO3_OFFSET;
		break;

	case 4:
		*regmap = priv->regmap_base;
		*reg = RV1106_SMT_GPIO4_OFFSET;
		break;

	default:
		*regmap = priv->regmap_base;
		*reg = 0;
		dev_err(priv->dev, "unsupported bank_num %d\n", bank->bank_num);
		break;
	}

	*reg += ((pin_num / RV1106_SMT_PINS_PER_REG) * 4);
	*bit = pin_num % RV1106_SMT_PINS_PER_REG;
	*bit *= RV1106_SMT_BITS_PER_PIN;

	return 0;
}

static int rv1106_set_schmitt(struct rockchip_pin_bank *bank,
			      int pin_num, int enable)
{
	struct regmap *regmap;
	int reg, ret;
	u32 data;
	u8 bit;

	rv1106_calc_schmitt_reg_and_bit(bank, pin_num, &regmap, &reg, &bit);

	/* enable the write to the equivalent lower bits */
	data = ((1 << RV1106_SMT_BITS_PER_PIN) - 1) << (bit + 16);
	data |= (enable << bit);
	ret = regmap_write(regmap, reg, data);

	return ret;
}

static struct rockchip_pin_bank rv1106_pin_banks[] = {
	PIN_BANK_IOMUX_FLAGS(0, 32, "gpio0",
			     IOMUX_WIDTH_4BIT | IOMUX_SOURCE_PMU,
			     IOMUX_WIDTH_4BIT | IOMUX_SOURCE_PMU,
			     IOMUX_WIDTH_4BIT | IOMUX_SOURCE_PMU,
			     IOMUX_WIDTH_4BIT | IOMUX_SOURCE_PMU),
	PIN_BANK_IOMUX_FLAGS_OFFSET(1, 32, "gpio1",
				    IOMUX_WIDTH_4BIT,
				    IOMUX_WIDTH_4BIT,
				    IOMUX_WIDTH_4BIT,
				    IOMUX_WIDTH_4BIT,
				    0, 0x08, 0x10, 0x18),
	PIN_BANK_IOMUX_FLAGS_OFFSET(2, 32, "gpio2",
				    IOMUX_WIDTH_4BIT,
				    IOMUX_WIDTH_4BIT,
				    IOMUX_WIDTH_4BIT,
				    IOMUX_WIDTH_4BIT,
				    0x10020, 0x10028, 0, 0),
	PIN_BANK_IOMUX_FLAGS_OFFSET(3, 32, "gpio3",
				    IOMUX_WIDTH_4BIT,
				    IOMUX_WIDTH_4BIT,
				    IOMUX_WIDTH_4BIT,
				    IOMUX_WIDTH_4BIT,
				    0x20040, 0x20048, 0x20050, 0x20058),
	PIN_BANK_IOMUX_FLAGS_OFFSET(4, 24, "gpio4",
				    IOMUX_WIDTH_4BIT,
				    IOMUX_WIDTH_4BIT,
				    IOMUX_WIDTH_4BIT,
				    0,
				    0x30000, 0x30008, 0x30010, 0),
};

static const struct rockchip_pin_ctrl rv1106_pin_ctrl = {
	.pin_banks		= rv1106_pin_banks,
	.nr_banks		= ARRAY_SIZE(rv1106_pin_banks),
	.nr_pins		= 152,
	.grf_mux_offset		= 0x0,
	.pmu_mux_offset		= 0x0,
	.set_mux		= rv1106_set_mux,
	.set_pull		= rv1106_set_pull,
	.set_drive		= rv1106_set_drive,
	.set_schmitt		= rv1106_set_schmitt,
};

static const struct udevice_id rv1106_pinctrl_ids[] = {
	{
		.compatible = "rockchip,rv1106-pinctrl",
		.data = (ulong)&rv1106_pin_ctrl
	},
	{ }
};

U_BOOT_DRIVER(pinctrl_rv1106) = {
	.name		= "rockchip_rv1106_pinctrl",
	.id		= UCLASS_PINCTRL,
	.of_match	= rv1106_pinctrl_ids,
	.priv_auto_alloc_size = sizeof(struct rockchip_pinctrl_priv),
	.ops		= &rockchip_pinctrl_ops,
#if !CONFIG_IS_ENABLED(OF_PLATDATA)
	.bind		= dm_scan_fdt_dev,
#endif
	.probe		= rockchip_pinctrl_probe,
};
