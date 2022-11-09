/*
 * Copyright (C) 2021 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <dm.h>
#include <errno.h>
#include <power/rk8xx_pmic.h>
#include <power/pmic.h>
#include <power/regulator.h>

#ifndef CONFIG_SPL_BUILD
#define ENABLE_DRIVER
#endif

/* Not used or exisit register and configure */
#define NA			-1

/* rk806 buck*/
#define RK806_BUCK_ON_VSEL(n)		(0x1a + n - 1)
#define RK806_BUCK_SLP_VSEL(n)		(0x24 + n - 1)
#define RK806_BUCK_CONFIG(n)		(0x10 + n - 1)
#define RK806_BUCK_VSEL_MASK		0xff

/* RK806 LDO */
#define RK806_NLDO_ON_VSEL(n)		(0x43 + n - 1)
#define RK806_NLDO_SLP_VSEL(n)		(0x48 + n - 1)
#define RK806_NLDO_VSEL_MASK		0xff
#define RK806_PLDO_ON_VSEL(n)		(0x4e + n - 1)
#define RK806_PLDO_SLP_VSEL(n)		(0x54 + n - 1)
#define RK806_PLDO_VSEL_MASK		0xff

/* RK806 ENABLE */
#define RK806_POWER_EN(n)		(0x00 + n)
#define RK806_NLDO_EN(n)		(0x03 + n)
#define RK806_PLDO_EN(n)		(0x04 + n)
#define RK806_RAMP_RATE_MASK1		0xc0
#define RK806_RAMP_RATE_REG1(n)		(0x10 + n)
#define RK806_RAMP_RATE_REG1_8		0xeb
#define RK806_RAMP_RATE_REG9_10		0xea

#define RK806_RAMP_RATE_4LSB_PER_1CLK	0x00/* LDO 100mV/uS buck 50mV/us */
#define RK806_RAMP_RATE_2LSB_PER_1CLK	0x01/* LDO 50mV/uS buck 25mV/us */
#define RK806_RAMP_RATE_1LSB_PER_1CLK	0x02/* LDO 25mV/uS buck 12.5mV/us */
#define RK806_RAMP_RATE_1LSB_PER_2CLK	0x03/* LDO 12.5mV/uS buck 6.25mV/us */

#define RK806_RAMP_RATE_1LSB_PER_4CLK	0x04/* LDO 6.28/2mV/uS buck 3.125mV/us */
#define RK806_RAMP_RATE_1LSB_PER_8CLK	0x05/* LDO 3.12mV/uS buck 1.56mV/us */
#define RK806_RAMP_RATE_1LSB_PER_13CLK	0x06/* LDO 1.9mV/uS buck 961mV/us */
#define RK806_RAMP_RATE_1LSB_PER_32CLK	0x07/* LDO 0.78mV/uS buck 0.39mV/us */

#define RK806_PLDO0_2_MSK(pldo)		(BIT(pldo + 5))
#define RK806_PLDO0_2_SET(pldo)		(BIT(pldo + 1) | RK806_PLDO0_2_MSK(pldo))
#define RK806_PLDO0_2_CLR(pldo)		RK806_PLDO0_2_MSK(pldo)

struct rk8xx_reg_info {
	uint min_uv;
	uint step_uv;
	u8 vsel_reg;
	u8 vsel_sleep_reg;
	u8 config_reg;
	u8 vsel_mask;
	u8 min_sel;
	/* only for buck now */
	u8 max_sel;
	u8 range_num;
};

static const struct rk8xx_reg_info rk806_buck[] = {
	/* buck 1 */
	{  500000,   6250, RK806_BUCK_ON_VSEL(1), RK806_BUCK_SLP_VSEL(1), RK806_BUCK_CONFIG(1), RK806_BUCK_VSEL_MASK, 0x00, 0xa0, 3},
	{  1500000, 25000, RK806_BUCK_ON_VSEL(1), RK806_BUCK_SLP_VSEL(1), RK806_BUCK_CONFIG(1), RK806_BUCK_VSEL_MASK, 0xa1, 0xed, 3},
	{  3400000,     0, RK806_BUCK_ON_VSEL(1), RK806_BUCK_SLP_VSEL(1), RK806_BUCK_CONFIG(1), RK806_BUCK_VSEL_MASK, 0xee, 0xff, 3},
	/* buck 2 */
	{  500000,   6250, RK806_BUCK_ON_VSEL(2), RK806_BUCK_SLP_VSEL(2), RK806_BUCK_CONFIG(2), RK806_BUCK_VSEL_MASK, 0x00, 0xa0, 3},
	{  1500000, 25000, RK806_BUCK_ON_VSEL(2), RK806_BUCK_SLP_VSEL(2), RK806_BUCK_CONFIG(2), RK806_BUCK_VSEL_MASK, 0xa1, 0xed, 3},
	{  3400000,     0, RK806_BUCK_ON_VSEL(2), RK806_BUCK_SLP_VSEL(2), RK806_BUCK_CONFIG(2), RK806_BUCK_VSEL_MASK, 0xee, 0xff, 3},
	/* buck 3 */
	{  500000,   6250, RK806_BUCK_ON_VSEL(3), RK806_BUCK_SLP_VSEL(3), RK806_BUCK_CONFIG(3), RK806_BUCK_VSEL_MASK, 0x00, 0xa0, 3},
	{  1500000, 25000, RK806_BUCK_ON_VSEL(3), RK806_BUCK_SLP_VSEL(3), RK806_BUCK_CONFIG(3), RK806_BUCK_VSEL_MASK, 0xa1, 0xed, 3},
	{  3400000,     0, RK806_BUCK_ON_VSEL(3), RK806_BUCK_SLP_VSEL(3), RK806_BUCK_CONFIG(3), RK806_BUCK_VSEL_MASK, 0xee, 0xff, 3},
	/* buck 4 */
	{  500000,   6250, RK806_BUCK_ON_VSEL(4), RK806_BUCK_SLP_VSEL(4), RK806_BUCK_CONFIG(4), RK806_BUCK_VSEL_MASK, 0x00, 0xa0, 3},
	{  1500000, 25000, RK806_BUCK_ON_VSEL(4), RK806_BUCK_SLP_VSEL(4), RK806_BUCK_CONFIG(4), RK806_BUCK_VSEL_MASK, 0xa1, 0xed, 3},
	{  3400000,     0, RK806_BUCK_ON_VSEL(4), RK806_BUCK_SLP_VSEL(4), RK806_BUCK_CONFIG(4), RK806_BUCK_VSEL_MASK, 0xee, 0xff, 3},
	/* buck 5 */
	{  500000,   6250, RK806_BUCK_ON_VSEL(5), RK806_BUCK_SLP_VSEL(5), RK806_BUCK_CONFIG(5), RK806_BUCK_VSEL_MASK, 0x00, 0xa0, 3},
	{  1500000, 25000, RK806_BUCK_ON_VSEL(5), RK806_BUCK_SLP_VSEL(5), RK806_BUCK_CONFIG(5), RK806_BUCK_VSEL_MASK, 0xa1, 0xed, 3},
	{  3400000,     0, RK806_BUCK_ON_VSEL(5), RK806_BUCK_SLP_VSEL(5), RK806_BUCK_CONFIG(5), RK806_BUCK_VSEL_MASK, 0xee, 0xff, 3},
	/* buck 6 */
	{  500000,   6250, RK806_BUCK_ON_VSEL(6), RK806_BUCK_SLP_VSEL(6), RK806_BUCK_CONFIG(6), RK806_BUCK_VSEL_MASK, 0x00, 0xa0, 3},
	{  1500000, 25000, RK806_BUCK_ON_VSEL(6), RK806_BUCK_SLP_VSEL(6), RK806_BUCK_CONFIG(6), RK806_BUCK_VSEL_MASK, 0xa1, 0xed, 3},
	{  3400000,     0, RK806_BUCK_ON_VSEL(6), RK806_BUCK_SLP_VSEL(6), RK806_BUCK_CONFIG(6), RK806_BUCK_VSEL_MASK, 0xee, 0xff, 3},
	/* buck 7 */
	{  500000,   6250, RK806_BUCK_ON_VSEL(7), RK806_BUCK_SLP_VSEL(7), RK806_BUCK_CONFIG(7), RK806_BUCK_VSEL_MASK, 0x00, 0xa0, 3},
	{  1500000, 25000, RK806_BUCK_ON_VSEL(7), RK806_BUCK_SLP_VSEL(7), RK806_BUCK_CONFIG(7), RK806_BUCK_VSEL_MASK, 0xa1, 0xed, 3},
	{  3400000,     0, RK806_BUCK_ON_VSEL(7), RK806_BUCK_SLP_VSEL(7), RK806_BUCK_CONFIG(7), RK806_BUCK_VSEL_MASK, 0xee, 0xff, 3},
	/* buck 8 */
	{  500000,   6250, RK806_BUCK_ON_VSEL(8), RK806_BUCK_SLP_VSEL(8), RK806_BUCK_CONFIG(8), RK806_BUCK_VSEL_MASK, 0x00, 0xa0, 3},
	{  1500000, 25000, RK806_BUCK_ON_VSEL(8), RK806_BUCK_SLP_VSEL(8), RK806_BUCK_CONFIG(8), RK806_BUCK_VSEL_MASK, 0xa1, 0xed, 3},
	{  3400000,     0, RK806_BUCK_ON_VSEL(8), RK806_BUCK_SLP_VSEL(8), RK806_BUCK_CONFIG(8), RK806_BUCK_VSEL_MASK, 0xee, 0xff, 3},
	/* buck 9 */
	{  500000,   6250, RK806_BUCK_ON_VSEL(9), RK806_BUCK_SLP_VSEL(9), RK806_BUCK_CONFIG(9), RK806_BUCK_VSEL_MASK, 0x00, 0xa0, 3},
	{  1500000, 25000, RK806_BUCK_ON_VSEL(9), RK806_BUCK_SLP_VSEL(9), RK806_BUCK_CONFIG(9), RK806_BUCK_VSEL_MASK, 0xa1, 0xed, 3},
	{  3400000,     0, RK806_BUCK_ON_VSEL(9), RK806_BUCK_SLP_VSEL(9), RK806_BUCK_CONFIG(9), RK806_BUCK_VSEL_MASK, 0xee, 0xff, 3},
	/* buck 10 */
	{  500000,   6250, RK806_BUCK_ON_VSEL(10), RK806_BUCK_SLP_VSEL(10), RK806_BUCK_CONFIG(10), RK806_BUCK_VSEL_MASK, 0x00, 0xa0, 3},
	{  1500000, 25000, RK806_BUCK_ON_VSEL(10), RK806_BUCK_SLP_VSEL(10), RK806_BUCK_CONFIG(10), RK806_BUCK_VSEL_MASK, 0xa1, 0xed, 3},
	{  3400000,     0, RK806_BUCK_ON_VSEL(10), RK806_BUCK_SLP_VSEL(10), RK806_BUCK_CONFIG(10), RK806_BUCK_VSEL_MASK, 0xee, 0xff, 3},
};

static const struct rk8xx_reg_info rk806_nldo[] = {
	/* nldo1 */
	{  500000, 12500, RK806_NLDO_ON_VSEL(1), RK806_NLDO_SLP_VSEL(1), NA, RK806_NLDO_VSEL_MASK, 0x00, },
	{  3400000,    0, RK806_NLDO_ON_VSEL(1), RK806_NLDO_SLP_VSEL(1), NA, RK806_NLDO_VSEL_MASK, 0xE8, },
	/* nldo2 */
	{  500000, 12500, RK806_NLDO_ON_VSEL(2), RK806_NLDO_SLP_VSEL(2), NA, RK806_NLDO_VSEL_MASK, 0x00, },
	{  3400000,    0, RK806_NLDO_ON_VSEL(2), RK806_NLDO_SLP_VSEL(2), NA, RK806_NLDO_VSEL_MASK, 0xE8, },
	/* nldo3 */
	{  500000, 12500, RK806_NLDO_ON_VSEL(3), RK806_NLDO_SLP_VSEL(3), NA, RK806_NLDO_VSEL_MASK, 0x00, },
	{  3400000,    0, RK806_NLDO_ON_VSEL(3), RK806_NLDO_SLP_VSEL(3), NA, RK806_NLDO_VSEL_MASK, 0xE8, },
	/* nldo4 */
	{  500000, 12500, RK806_NLDO_ON_VSEL(4), RK806_NLDO_SLP_VSEL(4), NA, RK806_NLDO_VSEL_MASK, 0x00, },
	{  3400000,    0, RK806_NLDO_ON_VSEL(4), RK806_NLDO_SLP_VSEL(4), NA, RK806_NLDO_VSEL_MASK, 0xE8, },
	/* nldo5 */
	{  500000, 12500, RK806_NLDO_ON_VSEL(5), RK806_NLDO_SLP_VSEL(5), NA, RK806_NLDO_VSEL_MASK, 0x00, },
	{  3400000,    0, RK806_NLDO_ON_VSEL(5), RK806_NLDO_SLP_VSEL(5), NA, RK806_NLDO_VSEL_MASK, 0xE8, },
};

static const struct rk8xx_reg_info rk806_pldo[] = {
	/* pldo1 */
	{  500000, 12500, RK806_PLDO_ON_VSEL(1), RK806_PLDO_SLP_VSEL(1), NA, RK806_PLDO_VSEL_MASK, 0x00, },
	{  3400000,    0, RK806_PLDO_ON_VSEL(1), RK806_PLDO_SLP_VSEL(1), NA, RK806_PLDO_VSEL_MASK, 0xE8, },
	/* pldo2 */
	{  500000, 12500, RK806_PLDO_ON_VSEL(2), RK806_PLDO_SLP_VSEL(2), NA, RK806_PLDO_VSEL_MASK, 0x00, },
	{  3400000,    0, RK806_PLDO_ON_VSEL(2), RK806_PLDO_SLP_VSEL(2), NA, RK806_PLDO_VSEL_MASK, 0xE8, },
	/* pldo3 */
	{  500000, 12500, RK806_PLDO_ON_VSEL(3), RK806_PLDO_SLP_VSEL(3), NA, RK806_PLDO_VSEL_MASK, 0x00, },
	{  3400000,    0, RK806_PLDO_ON_VSEL(3), RK806_PLDO_SLP_VSEL(3), NA, RK806_PLDO_VSEL_MASK, 0xE8, },
	/* pldo4 */
	{  500000, 12500, RK806_PLDO_ON_VSEL(4), RK806_PLDO_SLP_VSEL(4), NA, RK806_PLDO_VSEL_MASK, 0x00, },
	{  3400000,    0, RK806_PLDO_ON_VSEL(4), RK806_PLDO_SLP_VSEL(4), NA, RK806_PLDO_VSEL_MASK, 0xE8, },
	/* pldo5 */
	{  500000, 12500, RK806_PLDO_ON_VSEL(5), RK806_PLDO_SLP_VSEL(5), NA, RK806_PLDO_VSEL_MASK, 0x00, },
	{  3400000,    0, RK806_PLDO_ON_VSEL(5), RK806_PLDO_SLP_VSEL(5), NA, RK806_PLDO_VSEL_MASK, 0xE8, },
	/* pldo6 */
	{  500000, 12500, RK806_PLDO_ON_VSEL(6), RK806_PLDO_SLP_VSEL(6), NA, RK806_PLDO_VSEL_MASK, 0x00, },
	{  3400000,    0, RK806_PLDO_ON_VSEL(6), RK806_PLDO_SLP_VSEL(6), NA, RK806_PLDO_VSEL_MASK, 0xE8, },
};

static const struct rk8xx_reg_info *get_buck_reg(struct udevice *pmic,
						 int num, int uvolt)
{
	struct rk8xx_priv *priv = dev_get_priv(pmic);

	switch (priv->variant) {
	case RK806_ID:
		switch (num) {
		case 0 ... 9:
			if (uvolt < 1500000)
				return &rk806_buck[num * 3 + 0];
			else if (uvolt < 3400000)
				return &rk806_buck[num * 3 + 1];
			else
				return &rk806_buck[num * 3 + 2];
			break;
		}
	default:
		return &rk806_buck[num * 3 + 0];
	}
}

static int _buck_set_value(struct udevice *pmic, int buck, int uvolt)
{
	const struct rk8xx_reg_info *info = get_buck_reg(pmic, buck, uvolt);
	int mask = info->vsel_mask;
	int val;

	if (info->vsel_reg == NA)
		return -EINVAL;

	if (info->step_uv == 0)	/* Fixed voltage */
		val = info->min_sel;
	else
		val = ((uvolt - info->min_uv) / info->step_uv) + info->min_sel;

	debug("%s: volt=%d, buck=%d, reg=0x%x, mask=0x%x, val=0x%x\n",
	      __func__, uvolt, buck + 1, info->vsel_reg, mask, val);

	return pmic_clrsetbits(pmic, info->vsel_reg, mask, val);
}

static int _buck_set_enable(struct udevice *pmic, int buck, bool enable)
{
	struct rk8xx_priv *priv = dev_get_priv(pmic);
	uint value, en_reg;
	int ret;

	switch (priv->variant) {
	case RK806_ID:
		en_reg = RK806_POWER_EN(buck / 4);
		if (enable)
			value = ((1 << buck % 4) | (1 << (buck % 4 + 4)));
		else
			value = ((0 << buck % 4) | (1 << (buck % 4 + 4)));

		ret = pmic_reg_write(pmic, en_reg, value);
		break;
	default:
		ret = -EINVAL;
	}

	return ret;
}

#ifdef ENABLE_DRIVER
static int _buck_set_suspend_value(struct udevice *pmic, int buck, int uvolt)
{
	const struct rk8xx_reg_info *info = get_buck_reg(pmic, buck, uvolt);
	int mask = info->vsel_mask;
	int val;

	if (info->vsel_sleep_reg == NA)
		return -EINVAL;

	if (info->step_uv == 0)
		val = info->min_sel;
	else
		val = ((uvolt - info->min_uv) / info->step_uv) + info->min_sel;

	debug("%s: volt=%d, buck=%d, reg=0x%x, mask=0x%x, val=0x%x\n",
	      __func__, uvolt, buck + 1, info->vsel_sleep_reg, mask, val);

	return pmic_clrsetbits(pmic, info->vsel_sleep_reg, mask, val);
}

static int _buck_get_enable(struct udevice *pmic, int buck)
{
	struct rk8xx_priv *priv = dev_get_priv(pmic);
	uint mask = 0;
	int ret = 0;

	switch (priv->variant) {
	case RK806_ID:
		mask = 1 << buck % 4;
		ret = pmic_reg_read(pmic, RK806_POWER_EN(buck / 4));
		break;
	default:
		ret = 0;
	}

	if (ret < 0)
		return ret;

	return ret & mask ? true : false;
}

static int _buck_set_ramp_delay(struct udevice *pmic, int buck, u32 ramp_delay)
{
	const struct rk8xx_reg_info *info = get_buck_reg(pmic, buck, 0);
	struct rk8xx_priv *priv = dev_get_priv(pmic);
	int ramp_value = 0, reg_value;
	int ramp_reg1, ramp_reg2;

	if (info->config_reg == NA)
		return -EINVAL;

	switch (priv->variant) {
	case RK806_ID:
		switch (ramp_delay) {
		case 1 ... 390:
			ramp_value = RK806_RAMP_RATE_1LSB_PER_32CLK;
			break;
		case 391 ... 961:
			ramp_value = RK806_RAMP_RATE_1LSB_PER_13CLK;
			break;
		case 962 ... 1560:
			ramp_value = RK806_RAMP_RATE_1LSB_PER_8CLK;
			break;
		case 1561 ... 3125:
			ramp_value = RK806_RAMP_RATE_1LSB_PER_4CLK;
			break;
		case 3126 ... 6250:
			ramp_value = RK806_RAMP_RATE_1LSB_PER_2CLK;
			break;
		case 6251 ... 12500:
			ramp_value = RK806_RAMP_RATE_1LSB_PER_1CLK;
			break;
		case 12501 ... 25000:
			ramp_value = RK806_RAMP_RATE_2LSB_PER_1CLK;
			break;
		case 25001 ... 50000: /* 50mV/us */
			ramp_value = RK806_RAMP_RATE_4LSB_PER_1CLK;
			break;
		default:
			ramp_value = RK806_RAMP_RATE_1LSB_PER_32CLK;
			printf("buck%d ramp_delay: %d not supported\n",
			       buck, ramp_delay);
			break;
		}
		break;
	default:
		ramp_value = RK806_RAMP_RATE_1LSB_PER_32CLK;
		return -EINVAL;
	}

	ramp_reg1 = RK806_RAMP_RATE_REG1(buck);
	if (buck < 8)
		ramp_reg2 = RK806_RAMP_RATE_REG1_8;
	else
		ramp_reg2 = RK806_RAMP_RATE_REG9_10;

	reg_value = pmic_reg_read(pmic, ramp_reg1);
	if (reg_value < 0) {
		printf("buck%d read ramp reg(0x%x) error: %d", buck, ramp_reg1, reg_value);
		return reg_value;
	}
	reg_value &= 0x3f;

	pmic_reg_write(pmic,
		       ramp_reg1,
		       reg_value | (ramp_value & 0x03) << 0x06);

	reg_value = pmic_reg_read(pmic, ramp_reg2);
	if (reg_value < 0) {
		printf("buck%d read ramp reg(0x%x) error: %d", buck, ramp_reg2, reg_value);
		return reg_value;
	}

	return pmic_reg_write(pmic,
			      ramp_reg2,
			      reg_value | (ramp_value & 0x04) << (buck % 8));
}

static int _buck_set_suspend_enable(struct udevice *pmic, int buck, bool enable)
{
	return 0;
}

static int _buck_get_suspend_enable(struct udevice *pmic, int buck)
{
	return 0;
}

static const struct rk8xx_reg_info *get_ldo_reg(struct udevice *pmic,
						int num, int uvolt)
{
	struct rk8xx_priv *priv = dev_get_priv(pmic);

	switch (priv->variant) {
	case RK806_ID:
		if (uvolt < 3400000)
			return &rk806_nldo[num * 2];
		else
			return &rk806_nldo[num * 2 + 1];
	default:
		return &rk806_nldo[num * 2];
	}
}

static const struct rk8xx_reg_info *get_pldo_reg(struct udevice *pmic,
						 int num, int uvolt)
{
	struct rk8xx_priv *priv = dev_get_priv(pmic);

	switch (priv->variant) {
	case RK806_ID:
		if (uvolt < 3400000)
			return &rk806_pldo[num * 2];
		else
			return &rk806_pldo[num * 2 + 1];
	default:
		return &rk806_pldo[num * 2];
	}
}

static int _ldo_get_enable(struct udevice *pmic, int ldo)
{
	struct rk8xx_priv *priv = dev_get_priv(pmic);
	uint mask = 0;
	int ret = 0;

	switch (priv->variant) {
	case RK806_ID:
		if (ldo < 4) {
			mask = 1 << ldo % 4;
			ret = pmic_reg_read(pmic, RK806_NLDO_EN(ldo / 4));
		} else {
			mask = 1 << 2;
			ret = pmic_reg_read(pmic, RK806_NLDO_EN(2));
		}
		break;
	default:
		return false;
	}

	if (ret < 0)
		return ret;

	return ret & mask ? true : false;
}

static int _ldo_set_enable(struct udevice *pmic, int ldo, bool enable)
{
	struct rk8xx_priv *priv = dev_get_priv(pmic);
	uint value, en_reg;
	int ret = 0;

	switch (priv->variant) {
	case RK806_ID:
		if (ldo < 4) {
			en_reg = RK806_NLDO_EN(0);
			if (enable)
				value = ((1 << ldo % 4) | (1 << (ldo % 4 + 4)));
			else
				value = ((0 << ldo % 4) | (1 << (ldo % 4 + 4)));
			ret = pmic_reg_write(pmic, en_reg, value);
		} else {
			en_reg = RK806_NLDO_EN(2);
			if (enable)
				value = 0x44;
			else
				value = 0x40;
			ret = pmic_reg_write(pmic, en_reg, value);
		}
		break;
	default:
		return -EINVAL;
	}

	return ret;
}

static int _pldo_get_enable(struct udevice *pmic, int pldo)
{
	struct rk8xx_priv *priv = dev_get_priv(pmic);
	uint mask = 0, en_reg;
	int ret = 0;

	switch (priv->variant) {
	case RK806_ID:
		if ((pldo < 3) || (pldo == 5)) {
			en_reg = RK806_PLDO_EN(0);
			mask = RK806_PLDO0_2_SET(pldo);
			if (pldo == 5)
				mask = (1 << 0);
			ret = pmic_reg_read(pmic, en_reg);
		} else if ((pldo == 3) || (pldo == 4)) {
			en_reg = RK806_PLDO_EN(1);
			if (pldo == 3)
				mask = (1 << 0);
			else
				mask = (1 << 1);
			ret = pmic_reg_read(pmic, en_reg);
		}
		break;

	default:
		return -EINVAL;
	}

	if (ret < 0)
		return ret;

	return ret & mask ? true : false;
}

static int _pldo_set_enable(struct udevice *pmic, int pldo, bool enable)
{
	struct rk8xx_priv *priv = dev_get_priv(pmic);
	uint value, en_reg;
	int ret = 0;

	switch (priv->variant) {
	case RK806_ID:
		if (pldo < 3) {
			en_reg = RK806_PLDO_EN(0);
			if (enable)
				value = RK806_PLDO0_2_SET(pldo);
			else
				value = RK806_PLDO0_2_CLR(pldo);
			ret = pmic_reg_write(pmic, en_reg, value);
		} else if (pldo == 3) {
			en_reg = RK806_PLDO_EN(1);
			if (enable)
				value = ((1 << 0) | (1 << 4));
			else
				value = (1 << 4);
			ret = pmic_reg_write(pmic, en_reg, value);
		} else if (pldo == 4) {
			en_reg = RK806_PLDO_EN(1);
			if (enable)
				value = ((1 << 1) | (1 << 5));
			else
				value = ((0 << 1) | (1 << 5));
			ret = pmic_reg_write(pmic, en_reg, value);
		} else if (pldo == 5) {
			en_reg = RK806_PLDO_EN(0);
			if (enable)
				value = ((1 << 0) | (1 << 4));
			else
				value = ((0 << 0) | (1 << 4));
			ret = pmic_reg_write(pmic, en_reg, value);
		}

		break;
	default:
		return -EINVAL;
	}

	return ret;
}

static int _ldo_set_suspend_enable(struct udevice *pmic, int ldo, bool enable)
{
	return 0;
}

static int _ldo_get_suspend_enable(struct udevice *pmic, int ldo)
{
	return 0;
}

static int buck_get_value(struct udevice *dev)
{
	int buck = dev->driver_data - 1;
	const struct rk8xx_reg_info *info = get_buck_reg(dev->parent, buck, 0);
	int mask = info->vsel_mask;
	int i, ret, val;

	if (info->vsel_reg == NA)
		return -EINVAL;

	ret = pmic_reg_read(dev->parent, info->vsel_reg);
	if (ret < 0)
		return ret;

	val = ret & mask;
	if (val >= info->min_sel && val <= info->max_sel)
		goto finish;

	/* unlucky to try */
	for (i = 1; i < info->range_num; i++) {
		info++;
		if (val <= info->max_sel && val >= info->min_sel)
			break;
	}

finish:
	return info->min_uv + (val - info->min_sel) * info->step_uv;
}

static int buck_set_value(struct udevice *dev, int uvolt)
{
	int buck = dev->driver_data - 1;

	return _buck_set_value(dev->parent, buck, uvolt);
}

static int buck_get_suspend_value(struct udevice *dev)
{
	int buck = dev->driver_data - 1;
	const struct rk8xx_reg_info *info = get_buck_reg(dev->parent, buck, 0);
	int mask = info->vsel_mask;
	int i, ret, val;

	if (info->vsel_sleep_reg == NA)
		return -EINVAL;

	ret = pmic_reg_read(dev->parent, info->vsel_sleep_reg);
	if (ret < 0)
		return ret;

	val = ret & mask;
	if (val <= info->max_sel && val >= info->min_sel)
		goto finish;

	/* unlucky to try */
	for (i = 1; i < info->range_num; i++) {
		info++;
		if (val <= info->max_sel && val >= info->min_sel)
			break;
	}

finish:
	return info->min_uv + (val - info->min_sel) * info->step_uv;
}

static int buck_set_suspend_value(struct udevice *dev, int uvolt)
{
	int buck = dev->driver_data - 1;

	return _buck_set_suspend_value(dev->parent, buck, uvolt);
}

static int buck_set_enable(struct udevice *dev, bool enable)
{
	int buck = dev->driver_data - 1;

	return _buck_set_enable(dev->parent, buck, enable);
}

static int buck_set_suspend_enable(struct udevice *dev, bool enable)
{
	int buck = dev->driver_data - 1;

	return _buck_set_suspend_enable(dev->parent, buck, enable);
}

static int buck_get_suspend_enable(struct udevice *dev)
{
	int buck = dev->driver_data - 1;

	return _buck_get_suspend_enable(dev->parent, buck);
}

static int buck_set_ramp_delay(struct udevice *dev, u32 ramp_delay)
{
	int buck = dev->driver_data - 1;

	return _buck_set_ramp_delay(dev->parent, buck, ramp_delay);
}

static int buck_get_enable(struct udevice *dev)
{
	int buck = dev->driver_data - 1;

	return _buck_get_enable(dev->parent, buck);
}

static int ldo_get_value(struct udevice *dev)
{
	int ldo = dev->driver_data - 1;
	const struct rk8xx_reg_info *info = get_ldo_reg(dev->parent, ldo, 0);
	int mask = info->vsel_mask;
	int ret, val;

	if (info->vsel_reg == NA)
		return -EINVAL;

	ret = pmic_reg_read(dev->parent, info->vsel_reg);
	if (ret < 0)
		return ret;
	val = ret & mask;

	return info->min_uv + val * info->step_uv;
}

static int ldo_set_value(struct udevice *dev, int uvolt)
{
	int ldo = dev->driver_data - 1;
	const struct rk8xx_reg_info *info = get_ldo_reg(dev->parent, ldo, uvolt);
	int mask = info->vsel_mask;
	int val;

	if (info->vsel_reg == NA)
		return -EINVAL;

	if (info->step_uv == 0)
		val = info->min_sel;
	else
		val = ((uvolt - info->min_uv) / info->step_uv) + info->min_sel;

	debug("%s: volt=%d, ldo=%d, reg=0x%x, mask=0x%x, val=0x%x\n",
	      __func__, uvolt, ldo + 1, info->vsel_reg, mask, val);

	return pmic_clrsetbits(dev->parent, info->vsel_reg, mask, val);
}

static int pldo_get_value(struct udevice *dev)
{
	int ldo = dev->driver_data - 1;
	const struct rk8xx_reg_info *info = get_pldo_reg(dev->parent, ldo, 0);
	int mask = info->vsel_mask;
	int ret, val;

	if (info->vsel_reg == NA)
		return -EINVAL;

	ret = pmic_reg_read(dev->parent, info->vsel_reg);
	if (ret < 0)
		return ret;
	val = ret & mask;

	return info->min_uv + val * info->step_uv;
}

static int pldo_set_value(struct udevice *dev, int uvolt)
{
	int ldo = dev->driver_data - 1;
	const struct rk8xx_reg_info *info = get_pldo_reg(dev->parent, ldo, uvolt);
	int mask = info->vsel_mask;
	int val;

	if (info->vsel_reg == NA)
		return -EINVAL;

	if (info->step_uv == 0)
		val = info->min_sel;
	else
		val = ((uvolt - info->min_uv) / info->step_uv) + info->min_sel;

	debug("%s: volt=%d, ldo=%d, reg=0x%x, mask=0x%x, val=0x%x\n",
	      __func__, uvolt, ldo + 1, info->vsel_reg, mask, val);

	return pmic_clrsetbits(dev->parent, info->vsel_reg, mask, val);
}

static int ldo_set_suspend_value(struct udevice *dev, int uvolt)
{
	int ldo = dev->driver_data - 1;
	const struct rk8xx_reg_info *info = get_ldo_reg(dev->parent, ldo, uvolt);
	int mask = info->vsel_mask;
	int val;

	if (info->vsel_sleep_reg == NA)
		return -EINVAL;

	if (info->step_uv == 0)
		val = info->min_sel;
	else
		val = ((uvolt - info->min_uv) / info->step_uv) + info->min_sel;

	debug("%s: volt=%d, ldo=%d, reg=0x%x, mask=0x%x, val=0x%x\n",
	      __func__, uvolt, ldo + 1, info->vsel_sleep_reg, mask, val);

	return pmic_clrsetbits(dev->parent, info->vsel_sleep_reg, mask, val);
}

static int ldo_get_suspend_value(struct udevice *dev)
{
	int ldo = dev->driver_data - 1;
	const struct rk8xx_reg_info *info = get_ldo_reg(dev->parent, ldo, 0);
	int mask = info->vsel_mask;
	int val, ret;

	if (info->vsel_sleep_reg == NA)
		return -EINVAL;

	ret = pmic_reg_read(dev->parent, info->vsel_sleep_reg);
	if (ret < 0)
		return ret;

	val = ret & mask;

	return info->min_uv + val * info->step_uv;
}

static int ldo_set_enable(struct udevice *dev, bool enable)
{
	int ldo = dev->driver_data - 1;

	return _ldo_set_enable(dev->parent, ldo, enable);
}

static int ldo_set_suspend_enable(struct udevice *dev, bool enable)
{
	int ldo = dev->driver_data - 1;

	return _ldo_set_suspend_enable(dev->parent, ldo, enable);
}

static int ldo_get_suspend_enable(struct udevice *dev)
{
	int ldo = dev->driver_data - 1;

	return _ldo_get_suspend_enable(dev->parent, ldo);
}

static int ldo_get_enable(struct udevice *dev)
{
	int ldo = dev->driver_data - 1;

	return _ldo_get_enable(dev->parent, ldo);
}

static int pldo_set_enable(struct udevice *dev, bool enable)
{
	int ldo = dev->driver_data - 1;

	return _pldo_set_enable(dev->parent, ldo, enable);
}

static int pldo_get_enable(struct udevice *dev)
{
	int ldo = dev->driver_data - 1;

	return _pldo_get_enable(dev->parent, ldo);
}

static int rk8xx_buck_probe(struct udevice *dev)
{
	struct dm_regulator_uclass_platdata *uc_pdata;

	uc_pdata = dev_get_uclass_platdata(dev);
	uc_pdata->type = REGULATOR_TYPE_BUCK;
	uc_pdata->mode_count = 0;

	return 0;
}

static int rk8xx_ldo_probe(struct udevice *dev)
{
	struct dm_regulator_uclass_platdata *uc_pdata;

	uc_pdata = dev_get_uclass_platdata(dev);
	uc_pdata->type = REGULATOR_TYPE_LDO;
	uc_pdata->mode_count = 0;

	return 0;
}

static int rk8xx_pldo_probe(struct udevice *dev)
{
	struct dm_regulator_uclass_platdata *uc_pdata;

	uc_pdata = dev_get_uclass_platdata(dev);
	uc_pdata->type = REGULATOR_TYPE_LDO;
	uc_pdata->mode_count = 0;

	return 0;
}

static const struct dm_regulator_ops rk8xx_buck_ops = {
	.get_value  = buck_get_value,
	.set_value  = buck_set_value,
	.set_suspend_value = buck_set_suspend_value,
	.get_suspend_value = buck_get_suspend_value,
	.get_enable = buck_get_enable,
	.set_enable = buck_set_enable,
	.set_suspend_enable = buck_set_suspend_enable,
	.get_suspend_enable = buck_get_suspend_enable,
	.set_ramp_delay = buck_set_ramp_delay,
};

static const struct dm_regulator_ops rk8xx_ldo_ops = {
	.get_value  = ldo_get_value,
	.set_value  = ldo_set_value,
	.set_suspend_value = ldo_set_suspend_value,
	.get_suspend_value = ldo_get_suspend_value,
	.get_enable = ldo_get_enable,
	.set_enable = ldo_set_enable,
	.set_suspend_enable = ldo_set_suspend_enable,
	.get_suspend_enable = ldo_get_suspend_enable,
};

static const struct dm_regulator_ops rk8xx_pldo_ops = {
	.get_value  = pldo_get_value,
	.set_value  = pldo_set_value,
	.get_enable = pldo_get_enable,
	.set_enable = pldo_set_enable,
};

U_BOOT_DRIVER(rk8xx_spi_buck) = {
	.name = "rk8xx_spi_buck",
	.id = UCLASS_REGULATOR,
	.ops = &rk8xx_buck_ops,
	.probe = rk8xx_buck_probe,
};

U_BOOT_DRIVER(rk8xx_spi_ldo) = {
	.name = "rk8xx_spi_ldo",
	.id = UCLASS_REGULATOR,
	.ops = &rk8xx_ldo_ops,
	.probe = rk8xx_ldo_probe,
};

U_BOOT_DRIVER(rk8xx_spi_pldo) = {
	.name = "rk8xx_spi_pldo",
	.id = UCLASS_REGULATOR,
	.ops = &rk8xx_pldo_ops,
	.probe = rk8xx_pldo_probe,
};
#endif
