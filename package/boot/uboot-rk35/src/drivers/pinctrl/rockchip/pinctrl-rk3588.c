// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2021 Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <dm.h>
#include <dm/pinctrl.h>
#include <regmap.h>
#include <syscon.h>

#include "pinctrl-rockchip.h"

static int rk3588_set_mux(struct rockchip_pin_bank *bank, int pin, int mux)
{
	struct rockchip_pinctrl_priv *priv = bank->priv;
	struct regmap *regmap;
	int iomux_num = (pin / 8);
	int reg, ret, mask;
	u8 bit;
	u32 data;

	debug("setting mux of GPIO%d-%d to %d\n", bank->bank_num, pin, mux);

	regmap = priv->regmap_base;
	reg = bank->iomux[iomux_num].offset;
	if ((pin % 8) >= 4)
		reg += 0x4;
	bit = (pin % 4) * 4;
	mask = 0xf;

	if (bank->bank_num == 0) {
		if ((pin >= RK_PB4) && (pin <= RK_PD7)) {
			if (mux < 8) {
				reg += 0x4000 - 0xC; /* PMU2_IOC_BASE */
				data = (mask << (bit + 16));
				data |= (mux & mask) << bit;
				ret = regmap_write(regmap, reg, data);
			} else {
				u32 reg0 = 0;

				reg0 = reg + 0x4000 - 0xC; /* PMU2_IOC_BASE */
				data = (mask << (bit + 16));
				data |= 8 << bit;
				ret = regmap_write(regmap, reg0, data);

				reg0 = reg + 0x8000; /* BUS_IOC_BASE */
				data = (mask << (bit + 16));
				data |= mux << bit;
				regmap = priv->regmap_base;
				regmap_write(regmap, reg0, data);
			}
		} else {
			data = (mask << (bit + 16));
			data |= (mux & mask) << bit;
			ret = regmap_write(regmap, reg, data);
		}
		return ret;
	} else if (bank->bank_num > 0) {
		reg += 0x8000; /* BUS_IOC_BASE */
	}

	data = (mask << (bit + 16));
	data |= (mux & mask) << bit;

	return regmap_write(regmap, reg, data);
}

#define rk3588_DRV_PMU_OFFSET		0x70
#define rk3588_DRV_GRF_OFFSET		0x200
#define rk3588_DRV_BITS_PER_PIN		8
#define rk3588_DRV_PINS_PER_REG		2
#define rk3588_DRV_BANK_STRIDE		0x40

#define PMU1_IOC_REG		(0x0000)
#define PMU2_IOC_REG		(0x4000)
#define BUS_IOC_REG		(0x8000)
#define VCCIO1_4_IOC_REG	(0x9000)
#define VCCIO3_5_IOC_REG	(0xA000)
#define VCCIO2_IOC_REG		(0xB000)
#define VCCIO6_IOC_REG		(0xC000)
#define EMMC_IOC_REG		(0xD000)

static const u32 rk3588_ds_regs[][2] = {
	{RK_GPIO0_A0, PMU1_IOC_REG + 0x0010},
	{RK_GPIO0_A4, PMU1_IOC_REG + 0x0014},
	{RK_GPIO0_B0, PMU1_IOC_REG + 0x0018},
	{RK_GPIO0_B4, PMU2_IOC_REG + 0x0014},
/*	{RK_GPIO0_C0, PMU2_IOC_REG + 0x0018},
	{RK_GPIO0_C4, PMU2_IOC_REG + 0x001C},
	{RK_GPIO0_D0, PMU2_IOC_REG + 0x0020},
	{RK_GPIO0_D4, PMU2_IOC_REG + 0x0024},*/
	{RK_GPIO1_A0, VCCIO1_4_IOC_REG + 0x0020},
/*	{RK_GPIO1_A4, VCCIO1_4_IOC_REG + 0x0024},
	{RK_GPIO1_B0, VCCIO1_4_IOC_REG + 0x0028},
	{RK_GPIO1_B4, VCCIO1_4_IOC_REG + 0x002C},
	{RK_GPIO1_C0, VCCIO1_4_IOC_REG + 0x0030},
	{RK_GPIO1_C4, VCCIO1_4_IOC_REG + 0x0034},
	{RK_GPIO1_D0, VCCIO1_4_IOC_REG + 0x0038},
	{RK_GPIO1_D4, VCCIO1_4_IOC_REG + 0x003C},*/
	{RK_GPIO2_A0, EMMC_IOC_REG + 0x0040},
/*	{RK_GPIO2_A4, EMMC_IOC_REG + 0x0044},
	{RK_GPIO2_B0, EMMC_IOC_REG + 0x0048},
	{RK_GPIO2_B4, EMMC_IOC_REG + 0x004C},
	{RK_GPIO2_C0, EMMC_IOC_REG + 0x0050},
	{RK_GPIO2_C4, EMMC_IOC_REG + 0x0054},
	{RK_GPIO2_D0, EMMC_IOC_REG + 0x0058},
	{RK_GPIO2_D4, EMMC_IOC_REG + 0x005C},*/
	{RK_GPIO3_A0, VCCIO3_5_IOC_REG + 0x0060},
/*	{RK_GPIO3_A4, VCCIO3_5_IOC_REG + 0x0064},
	{RK_GPIO3_B0, VCCIO3_5_IOC_REG + 0x0068},
	{RK_GPIO3_B4, VCCIO3_5_IOC_REG + 0x006C},
	{RK_GPIO3_C0, VCCIO3_5_IOC_REG + 0x0070},
	{RK_GPIO3_C4, VCCIO3_5_IOC_REG + 0x0074},
	{RK_GPIO3_D0, VCCIO3_5_IOC_REG + 0x0078},
	{RK_GPIO3_D4, VCCIO3_5_IOC_REG + 0x007C},*/
	{RK_GPIO4_A0, VCCIO6_IOC_REG + 0x0080},
/*	{RK_GPIO4_A4, VCCIO6_IOC_REG + 0x0084},
	{RK_GPIO4_B0, VCCIO6_IOC_REG + 0x0088},
	{RK_GPIO4_B4, VCCIO6_IOC_REG + 0x008C},
	{RK_GPIO4_C0, VCCIO6_IOC_REG + 0x0090},*/
};

static const u32 rk3588_p_regs[][2] = {
	{RK_GPIO0_A0, PMU1_IOC_REG + 0x0020},
	{RK_GPIO0_B0, PMU1_IOC_REG + 0x0024},
	{RK_GPIO0_B5, PMU2_IOC_REG + 0x0028},
	{RK_GPIO0_C0, PMU2_IOC_REG + 0x002C},
	{RK_GPIO0_D0, PMU2_IOC_REG + 0x0030},
	{RK_GPIO1_A0, VCCIO1_4_IOC_REG + 0x0110},
/*	{RK_GPIO1_B0, VCCIO1_4_IOC_REG + 0x0114},
	{RK_GPIO1_C0, VCCIO1_4_IOC_REG + 0x0118},
	{RK_GPIO1_D0, VCCIO1_4_IOC_REG + 0x011C},*/
	{RK_GPIO2_A0, EMMC_IOC_REG + 0x0120},
/*	{RK_GPIO2_D0, EMMC_IOC_REG + 0x012C},*/
	{RK_GPIO3_A0, VCCIO3_5_IOC_REG + 0x0130},
/*	{RK_GPIO3_B0, VCCIO3_5_IOC_REG + 0x0134},
	{RK_GPIO3_C0, VCCIO3_5_IOC_REG + 0x0138},
	{RK_GPIO3_D0, VCCIO3_5_IOC_REG + 0x013C},*/
	{RK_GPIO4_A0, VCCIO6_IOC_REG + 0x0140},
/*	{RK_GPIO4_B0, VCCIO6_IOC_REG + 0x0144},
	{RK_GPIO4_C0, VCCIO6_IOC_REG + 0x0148},
	{RK_GPIO4_D0, VCCIO2_IOC_REG + 0x014C},*/
};

static const u32 rk3588_smt_regs[][2] = {
	{RK_GPIO0_A0, PMU1_IOC_REG + 0x0030},
	{RK_GPIO0_B0, PMU1_IOC_REG + 0x0034},
	{RK_GPIO0_B5, PMU2_IOC_REG + 0x0040},
	{RK_GPIO0_C0, PMU2_IOC_REG + 0x0044},
	{RK_GPIO0_D0, PMU2_IOC_REG + 0x0048},
	{RK_GPIO1_A0, VCCIO1_4_IOC_REG + 0x0210},
/*	{RK_GPIO1_B0, VCCIO1_4_IOC_REG + 0x0214},
	{RK_GPIO1_C0, VCCIO1_4_IOC_REG + 0x0218},
	{RK_GPIO1_D0, VCCIO1_4_IOC_REG + 0x021C},*/
	{RK_GPIO2_A0, EMMC_IOC_REG + 0x0220},
	{RK_GPIO2_D0, EMMC_IOC_REG + 0x022C},
	{RK_GPIO3_A0, VCCIO3_5_IOC_REG + 0x0230},
/*	{RK_GPIO3_B0, VCCIO3_5_IOC_REG + 0x0234},
	{RK_GPIO3_C0, VCCIO3_5_IOC_REG + 0x0238},
	{RK_GPIO3_D0, VCCIO3_5_IOC_REG + 0x023C},*/
	{RK_GPIO4_A0, VCCIO6_IOC_REG + 0x0240},
/*	{RK_GPIO4_B0, VCCIO6_IOC_REG + 0x0244},
	{RK_GPIO4_C0, VCCIO6_IOC_REG + 0x0248},
	{RK_GPIO4_D0, VCCIO2_IOC_REG + 0x024C},*/
};

#define RK3588_PULL_BITS_PER_PIN		2
#define RK3588_PULL_PINS_PER_REG		8

static void rk3588_calc_pull_reg_and_bit(struct rockchip_pin_bank *bank,
					 int pin_num, struct regmap **regmap,
					 int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *info = bank->priv;
	u8 bank_num = bank->bank_num;
	u32 pin = bank_num * 32 + pin_num;
	int i;

	for (i = ARRAY_SIZE(rk3588_p_regs) - 1; i >= 0; i--) {
		if (pin >= rk3588_p_regs[i][0]) {
			*reg = rk3588_p_regs[i][1];
			break;
		}
		BUG_ON(i == 0);
	}

	*regmap = info->regmap_base;
	*reg += ((pin - rk3588_p_regs[i][0]) / RK3588_PULL_PINS_PER_REG) * 4;
	*bit = pin_num % RK3588_PULL_PINS_PER_REG;
	*bit *= RK3588_PULL_BITS_PER_PIN;
}

#define RK3588_DRV_BITS_PER_PIN		4
#define RK3588_DRV_PINS_PER_REG		4

static void rk3588_calc_drv_reg_and_bit(struct rockchip_pin_bank *bank,
					int pin_num, struct regmap **regmap,
					int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *info = bank->priv;
	u8 bank_num = bank->bank_num;
	u32 pin = bank_num * 32 + pin_num;
	int i;

	for (i = ARRAY_SIZE(rk3588_ds_regs) - 1; i >= 0; i--) {
		if (pin >= rk3588_ds_regs[i][0]) {
			*reg = rk3588_ds_regs[i][1];
			break;
		}
		BUG_ON(i == 0);
	}

	*regmap = info->regmap_base;
	*reg += ((pin - rk3588_ds_regs[i][0]) / RK3588_DRV_PINS_PER_REG) * 4;
	*bit = pin_num % RK3588_DRV_PINS_PER_REG;
	*bit *= RK3588_DRV_BITS_PER_PIN;
}

#define RK3588_SMT_BITS_PER_PIN		1
#define RK3588_SMT_PINS_PER_REG		8

static int rk3588_calc_schmitt_reg_and_bit(struct rockchip_pin_bank *bank,
					   int pin_num, struct regmap **regmap,
					   int *reg, u8 *bit)
{
	struct rockchip_pinctrl_priv *info = bank->priv;
	u8 bank_num = bank->bank_num;
	u32 pin = bank_num * 32 + pin_num;
	int i;

	for (i = ARRAY_SIZE(rk3588_smt_regs) - 1; i >= 0; i--) {
		if (pin >= rk3588_smt_regs[i][0]) {
			*reg = rk3588_smt_regs[i][1];
			break;
		}
		BUG_ON(i == 0);
	}

	*regmap = info->regmap_base;
	*reg += ((pin - rk3588_smt_regs[i][0]) / RK3588_SMT_PINS_PER_REG) * 4;
	*bit = pin_num % RK3588_SMT_PINS_PER_REG;
	*bit *= RK3588_SMT_BITS_PER_PIN;

	return 0;
}

static int rk3588_set_pull(struct rockchip_pin_bank *bank,
			   int pin_num, int pull)
{
	struct regmap *regmap;
	int reg;
	u32 data;
	u8 bit;

	rk3588_calc_pull_reg_and_bit(bank, pin_num, &regmap, &reg, &bit);

	/* enable the write to the equivalent lower bits */
	data = ((1 << ROCKCHIP_PULL_BITS_PER_PIN) - 1) << (bit + 16);
	data |= (pull << bit);

	return regmap_write(regmap, reg, data);
}

static int rk3588_set_drive(struct rockchip_pin_bank *bank,
			    int pin_num, int strength)
{
	struct regmap *regmap;
	int reg;
	u32 data;
	u8 bit;

	rk3588_calc_drv_reg_and_bit(bank, pin_num, &regmap, &reg, &bit);

	/* enable the write to the equivalent lower bits */
	data = ((1 << rk3588_DRV_BITS_PER_PIN) - 1) << (bit + 16);
	data |= (strength << bit);

	return regmap_write(regmap, reg, data);
}

static int rk3588_set_schmitt(struct rockchip_pin_bank *bank,
			      int pin_num, int enable)
{
	struct regmap *regmap;
	int reg;
	u32 data;
	u8 bit;

	rk3588_calc_schmitt_reg_and_bit(bank, pin_num, &regmap, &reg, &bit);

	/* enable the write to the equivalent lower bits */
	data = ((1 << RK3588_SMT_BITS_PER_PIN) - 1) << (bit + 16);
	data |= (enable << bit);

	return regmap_write(regmap, reg, data);
}

static struct rockchip_pin_bank rk3588_pin_banks[] = {
	RK3588_PIN_BANK_FLAGS(0, 32, "gpio0",
			      IOMUX_WIDTH_4BIT, PULL_TYPE_IO_1V8_ONLY),
	RK3588_PIN_BANK_FLAGS(1, 32, "gpio1",
			      IOMUX_WIDTH_4BIT, PULL_TYPE_IO_1V8_ONLY),
	RK3588_PIN_BANK_FLAGS(2, 32, "gpio2",
			      IOMUX_WIDTH_4BIT, PULL_TYPE_IO_1V8_ONLY),
	RK3588_PIN_BANK_FLAGS(3, 32, "gpio3",
			      IOMUX_WIDTH_4BIT, PULL_TYPE_IO_1V8_ONLY),
	RK3588_PIN_BANK_FLAGS(4, 32, "gpio4",
			      IOMUX_WIDTH_4BIT, PULL_TYPE_IO_1V8_ONLY),
};

static const struct rockchip_pin_ctrl rk3588_pin_ctrl = {
	.pin_banks		= rk3588_pin_banks,
	.nr_banks		= ARRAY_SIZE(rk3588_pin_banks),
	.nr_pins		= 160,
	.set_mux		= rk3588_set_mux,
	.set_pull		= rk3588_set_pull,
	.set_drive		= rk3588_set_drive,
	.set_schmitt		= rk3588_set_schmitt,
};

static const struct udevice_id rk3588_pinctrl_ids[] = {
	{
		.compatible = "rockchip,rk3588-pinctrl",
		.data = (ulong)&rk3588_pin_ctrl
	},
	{ }
};

U_BOOT_DRIVER(pinctrl_rk3588) = {
	.name		= "rockchip_rk3588_pinctrl",
	.id		= UCLASS_PINCTRL,
	.of_match	= rk3588_pinctrl_ids,
	.priv_auto_alloc_size = sizeof(struct rockchip_pinctrl_priv),
	.ops		= &rockchip_pinctrl_ops,
#if !CONFIG_IS_ENABLED(OF_PLATDATA)
	.bind		= dm_scan_fdt_dev,
#endif
	.probe		= rockchip_pinctrl_probe,
};
