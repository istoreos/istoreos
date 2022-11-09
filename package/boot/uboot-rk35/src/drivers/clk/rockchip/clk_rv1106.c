// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2021 Rockchip Electronics Co., Ltd
 * Author: Elaine Zhang <zhangqing@rock-chips.com>
 */

#include <common.h>
#include <bitfield.h>
#include <clk-uclass.h>
#include <dm.h>
#include <errno.h>
#include <syscon.h>
#include <asm/arch-rockchip/clock.h>
#include <asm/arch-rockchip/cru_rv1106.h>
#include <asm/arch-rockchip/grf_rv1106.h>
#include <asm/arch-rockchip/hardware.h>
#include <asm/io.h>
#include <dm/lists.h>
#include <dt-bindings/clock/rv1106-cru.h>

DECLARE_GLOBAL_DATA_PTR;

#define DIV_TO_RATE(input_rate, div)	((input_rate) / ((div) + 1))

#ifndef CONFIG_ROCKCHIP_IMAGE_TINY
static struct rockchip_pll_rate_table rv1106_pll_rates[] = {
	/* _mhz, _refdiv, _fbdiv, _postdiv1, _postdiv2, _dsmpd, _frac */
	RK3036_PLL_RATE(1188000000, 1, 99, 2, 1, 1, 0),
	RK3036_PLL_RATE(1008000000, 1, 84, 2, 1, 1, 0),
	RK3036_PLL_RATE(1000000000, 3, 250, 2, 1, 1, 0),
	RK3036_PLL_RATE(816000000, 1, 68, 2, 1, 1, 0),
	RK3036_PLL_RATE(600000000, 1, 100, 4, 1, 1, 0),
	RK3036_PLL_RATE(594000000, 1, 99, 4, 1, 1, 0),
	{ /* sentinel */ },
};

static struct rockchip_pll_clock rv1106_pll_clks[] = {
	[APLL] = PLL(pll_rk3328, PLL_APLL, RV1106_PLL_CON(0),
		     RV1106_MODE_CON, 0, 10, 0, rv1106_pll_rates),
	[DPLL] = PLL(pll_rk3328, PLL_DPLL, RV1106_PLL_CON(16),
		     RV1106_SUBDDRMODE_CON, 0, 10, 0, NULL),
	[CPLL] = PLL(pll_rk3328, PLL_CPLL, RV1106_PLL_CON(8),
		     RV1106_MODE_CON, 2, 10, 0, rv1106_pll_rates),
	[GPLL] = PLL(pll_rk3328, PLL_GPLL, RV1106_PLL_CON(24),
		     RV1106_MODE_CON, 4, 10, 0, rv1106_pll_rates),
};
#endif

#ifndef CONFIG_SPL_BUILD
#define RV1106_CLK_DUMP(_id, _name, _iscru)	\
{						\
	.id = _id,				\
	.name = _name,				\
	.is_cru = _iscru,			\
}

static const struct rv1106_clk_info clks_dump[] = {
#ifndef CONFIG_ROCKCHIP_IMAGE_TINY
	RV1106_CLK_DUMP(PLL_APLL, "apll", true),
	RV1106_CLK_DUMP(PLL_DPLL, "dpll", true),
	RV1106_CLK_DUMP(PLL_GPLL, "gpll", true),
	RV1106_CLK_DUMP(PLL_CPLL, "cpll", true),
	RV1106_CLK_DUMP(ACLK_PERI_ROOT, "aclk_peri_root", true),
	RV1106_CLK_DUMP(HCLK_PERI_ROOT, "hclK_peri_root", true),
	RV1106_CLK_DUMP(PCLK_PERI_ROOT, "pclk_peri_root", true),
	RV1106_CLK_DUMP(ACLK_BUS_ROOT, "aclk_bus_root", true),
	RV1106_CLK_DUMP(PCLK_TOP_ROOT, "pclk_top_root", true),
	RV1106_CLK_DUMP(PCLK_PMU_ROOT, "pclk_pmu_root", true),
	RV1106_CLK_DUMP(HCLK_PMU_ROOT, "hclk_pmu_root", true),
#endif
};
#endif

#ifndef CONFIG_ROCKCHIP_IMAGE_TINY
static ulong rv1106_peri_get_clk(struct rv1106_clk_priv *priv, ulong clk_id)
{
	struct rv1106_cru *cru = priv->cru;
	u32 con, sel, rate;

	switch (clk_id) {
	case ACLK_PERI_ROOT:
		con = readl(&cru->peri_clksel_con[1]);
		sel = (con & ACLK_PERI_SEL_MASK) >> ACLK_PERI_SEL_SHIFT;
		if (sel == ACLK_PERI_SEL_400M)
			rate = 400 * MHz;
		else if (sel == ACLK_PERI_SEL_200M)
			rate = 200 * MHz;
		else if (sel == ACLK_PERI_SEL_100M)
			rate = 100 * MHz;
		else
			rate = OSC_HZ;
		break;
	case HCLK_PERI_ROOT:
		con = readl(&cru->peri_clksel_con[1]);
		sel = (con & HCLK_PERI_SEL_MASK) >> HCLK_PERI_SEL_SHIFT;
		if (sel == HCLK_PERI_SEL_200M)
			rate = 200 * MHz;
		else if (sel == HCLK_PERI_SEL_100M)
			rate = 100 * MHz;
		else if (sel == HCLK_PERI_SEL_50M)
			rate = 50 * MHz;
		else
			rate = OSC_HZ;
		break;
	case PCLK_PERI_ROOT:
		con = readl(&cru->peri_clksel_con[1]);
		sel = (con & PCLK_PERI_SEL_MASK) >> PCLK_PERI_SEL_SHIFT;
		if (sel == PCLK_PERI_SEL_100M)
			rate = 100 * MHz;
		else if (sel == PCLK_PERI_SEL_50M)
			rate = 50 * MHz;
		else
			rate = OSC_HZ;
		break;
	case ACLK_BUS_ROOT:
		con = readl(&cru->peri_clksel_con[9]);
		sel = (con & ACLK_BUS_SEL_MASK) >> ACLK_BUS_SEL_SHIFT;
		if (sel == ACLK_BUS_SEL_300M)
			rate = 300 * MHz;
		else if (sel == ACLK_BUS_SEL_200M)
			rate = 200 * MHz;
		else if (sel == ACLK_BUS_SEL_100M)
			rate = 100 * MHz;
		else
			rate = OSC_HZ;
		break;
	case PCLK_TOP_ROOT:
		con = readl(&cru->clksel_con[24]);
		sel = (con & PCLK_TOP_SEL_MASK) >> PCLK_TOP_SEL_SHIFT;
		if (sel == PCLK_TOP_SEL_100M)
			rate = 100 * MHz;
		else if (sel == PCLK_TOP_SEL_50M)
			rate = 50 * MHz;
		else
			rate = OSC_HZ;
		break;
	case PCLK_PMU_ROOT:
		con = readl(&cru->pmu_clksel_con[0]);
		sel = (con & PCLK_PMU_SEL_MASK) >> PCLK_PMU_SEL_SHIFT;
		if (sel == PCLK_PMU_SEL_100M)
			rate = 100 * MHz;
		else
			rate = OSC_HZ;
		break;
	case HCLK_PMU_ROOT:
		con = readl(&cru->pmu_clksel_con[0]);
		sel = (con & HCLK_PMU_SEL_MASK) >> HCLK_PMU_SEL_SHIFT;
		if (sel == HCLK_PMU_SEL_200M)
			rate = 200 * MHz;
		else if (sel == HCLK_PMU_SEL_100M)
			rate = 100 * MHz;
		else
			rate = OSC_HZ;
		break;
	default:
		return -ENOENT;
	}

	return rate;
}

static ulong rv1106_peri_set_clk(struct rv1106_clk_priv *priv,
				 ulong clk_id, ulong rate)
{
	struct rv1106_cru *cru = priv->cru;
	int src_clk;

	switch (clk_id) {
	case ACLK_PERI_ROOT:
		if (rate >= 396 * MHz)
			src_clk = ACLK_PERI_SEL_400M;
		else if (rate >= 198 * MHz)
			src_clk = ACLK_PERI_SEL_200M;
		else if (rate >= 99 * MHz)
			src_clk = ACLK_PERI_SEL_100M;
		else
			src_clk = ACLK_PERI_SEL_24M;
		rk_clrsetreg(&cru->peri_clksel_con[1],
			     ACLK_PERI_SEL_MASK,
			     src_clk << ACLK_PERI_SEL_SHIFT);
		break;
	case HCLK_PERI_ROOT:
		if (rate >= 198 * MHz)
			src_clk = HCLK_PERI_SEL_200M;
		else if (rate >= 99 * MHz)
			src_clk = HCLK_PERI_SEL_100M;
		else if (rate >= 48 * MHz)
			src_clk = HCLK_PERI_SEL_50M;
		else
			src_clk = HCLK_PERI_SEL_24M;
		rk_clrsetreg(&cru->peri_clksel_con[1],
			     HCLK_PERI_SEL_MASK,
			     src_clk << HCLK_PERI_SEL_SHIFT);
		break;
	case PCLK_PERI_ROOT:
		if (rate >= 99 * MHz)
			src_clk = PCLK_PERI_SEL_100M;
		else if (rate >= 48 * MHz)
			src_clk = PCLK_PERI_SEL_50M;
		else
			src_clk = PCLK_PERI_SEL_24M;
		rk_clrsetreg(&cru->peri_clksel_con[1],
			     PCLK_PERI_SEL_MASK,
			     src_clk << PCLK_PERI_SEL_SHIFT);
		break;
	case ACLK_BUS_ROOT:
		if (rate >= 297 * MHz)
			src_clk = ACLK_BUS_SEL_300M;
		else if (rate >= 198 * MHz)
			src_clk = ACLK_BUS_SEL_200M;
		else if (rate >= 99 * MHz)
			src_clk = ACLK_BUS_SEL_100M;
		else
			src_clk = ACLK_BUS_SEL_24M;
		rk_clrsetreg(&cru->peri_clksel_con[9],
			     ACLK_BUS_SEL_MASK,
			     src_clk << ACLK_BUS_SEL_SHIFT);
		break;
	case PCLK_TOP_ROOT:
		if (rate >= 99 * MHz)
			src_clk = PCLK_TOP_SEL_100M;
		else if (rate >= 48 * MHz)
			src_clk = PCLK_TOP_SEL_50M;
		else
			src_clk = PCLK_TOP_SEL_24M;
		rk_clrsetreg(&cru->clksel_con[24],
			     PCLK_TOP_SEL_MASK,
			     src_clk << PCLK_TOP_SEL_SHIFT);
		break;
	case PCLK_PMU_ROOT:
		if (rate >= 99 * MHz)
			src_clk = PCLK_PMU_SEL_100M;
		else
			src_clk = PCLK_PMU_SEL_24M;
		rk_clrsetreg(&cru->pmu_clksel_con[0],
			     PCLK_PMU_SEL_MASK,
			     src_clk << PCLK_PMU_SEL_SHIFT);
		break;
	case HCLK_PMU_ROOT:
		if (rate >= 198 * MHz)
			src_clk = HCLK_PMU_SEL_200M;
		else if (rate >= 99 * MHz)
			src_clk = HCLK_PMU_SEL_100M;
		else
			src_clk = HCLK_PMU_SEL_24M;
		rk_clrsetreg(&cru->pmu_clksel_con[0],
			     HCLK_PMU_SEL_MASK,
			     src_clk << HCLK_PMU_SEL_SHIFT);
		break;
	default:
		printf("do not support this permid freq\n");
		return -EINVAL;
	}

	return rv1106_peri_get_clk(priv, clk_id);
}

static ulong rv1106_i2c_get_clk(struct rv1106_clk_priv *priv, ulong clk_id)
{
	struct rv1106_cru *cru = priv->cru;
	u32 sel, con;
	ulong rate;

	switch (clk_id) {
	case CLK_I2C1:
		con = readl(&cru->pmu_clksel_con[0]);
		sel = (con & CLK_I2C1_SEL_MASK) >> CLK_I2C1_SEL_SHIFT;
		if (sel == CLK_I2C1_SEL_200M)
			rate = 200 * MHz;
		else if (sel == CLK_I2C1_SEL_100M)
			rate = 100 * MHz;
		else if (sel == CLK_I2C1_SEL_24M)
			rate = OSC_HZ;
		else
			rate = 32768;
		return rate;
	case CLK_I2C0:
		con = readl(&cru->peri_clksel_con[1]);
		sel = (con & CLK_I2C0_SEL_MASK) >> CLK_I2C0_SEL_SHIFT;
		break;
	case CLK_I2C2:
		con = readl(&cru->peri_clksel_con[1]);
		sel = (con & CLK_I2C2_SEL_MASK) >> CLK_I2C2_SEL_SHIFT;
		break;
	case CLK_I2C3:
		con = readl(&cru->peri_clksel_con[1]);
		sel = (con & CLK_I2C3_SEL_MASK) >> CLK_I2C3_SEL_SHIFT;
		break;
	case CLK_I2C4:
		con = readl(&cru->peri_clksel_con[2]);
		sel = (con & CLK_I2C4_SEL_MASK) >> CLK_I2C4_SEL_SHIFT;
		break;
	default:
		return -ENOENT;
	}

	if (sel == CLK_I2C0_SEL_200M)
		rate = 200 * MHz;
	else if (sel == CLK_I2C0_SEL_100M)
		rate = 100 * MHz;
	else if (sel == CLK_I2C0_SEL_50M)
		rate = 50 * MHz;
	else
		rate = OSC_HZ;

	return rate;
}
#endif

static ulong rv1106_crypto_get_clk(struct rv1106_clk_priv *priv, ulong clk_id)
{
	struct rv1106_cru *cru = priv->cru;
	u32 sel, con;

	switch (clk_id) {
	case CLK_CORE_CRYPTO:
		con = readl(&cru->peri_clksel_con[6]);
		sel = (con & CLK_CORE_CRYPTO_SEL_MASK) >>
		      CLK_CORE_CRYPTO_SEL_SHIFT;
		break;
	case CLK_PKA_CRYPTO:
		con = readl(&cru->peri_clksel_con[6]);
		sel = (con & CLK_PKA_CRYPTO_SEL_MASK) >>
		      CLK_PKA_CRYPTO_SEL_SHIFT;
		break;
	default:
		return -ENOENT;
	}
	switch (sel) {
	case CLK_CRYPTO_SEL_300M:
		return 300 * MHz;
	case CLK_CRYPTO_SEL_200M:
		return 200 * MHz;
	case CLK_CRYPTO_SEL_100M:
		return 100 * MHz;
	case CLK_CRYPTO_SEL_24M:
		return OSC_HZ;
	default:
		return -ENOENT;
	}
}

static ulong rv1106_crypto_set_clk(struct rv1106_clk_priv *priv,
				   ulong clk_id, ulong rate)
{
	struct rv1106_cru *cru = priv->cru;
	u32 sel;

	if (rate >= 297 * MHz)
		sel = CLK_CRYPTO_SEL_300M;
	else if (rate >= 198 * MHz)
		sel = CLK_CRYPTO_SEL_200M;
	else if (rate >= 99 * MHz)
		sel = CLK_CRYPTO_SEL_100M;
	else
		sel = CLK_CRYPTO_SEL_24M;

	switch (clk_id) {
	case CLK_CORE_CRYPTO:
		rk_clrsetreg(&cru->peri_clksel_con[6],
			     CLK_CORE_CRYPTO_SEL_MASK,
			     sel << CLK_CORE_CRYPTO_SEL_SHIFT);
		break;
	case CLK_PKA_CRYPTO:
		rk_clrsetreg(&cru->peri_clksel_con[6],
			     CLK_PKA_CRYPTO_SEL_MASK,
			     sel << CLK_PKA_CRYPTO_SEL_SHIFT);
		break;
	default:
		return -ENOENT;
	}
	return rv1106_crypto_get_clk(priv, clk_id);
}

static ulong rv1106_mmc_get_clk(struct rv1106_clk_priv *priv, ulong clk_id)
{
	struct rv1106_cru *cru = priv->cru;
	u32 div, sel, con, prate;

	switch (clk_id) {
	case CCLK_SRC_SDMMC:
	case HCLK_SDMMC:
		con = readl(&cru->vi_clksel_con[1]);
		sel = (con & CLK_SDMMC_SEL_MASK) >>
		      CLK_SDMMC_SEL_SHIFT;
		div = (con & CLK_SDMMC_DIV_MASK) >>
		      CLK_SDMMC_DIV_SHIFT;
		if (sel == CLK_MMC_SEL_400M)
			prate = 400 * MHz;
		else
			prate = OSC_HZ;
		return DIV_TO_RATE(prate, div);
	case CCLK_SRC_EMMC:
	case HCLK_EMMC:
		con = readl(&cru->peri_clksel_con[7]);
		sel = (con & CLK_EMMC_SEL_MASK) >>
		      CLK_EMMC_SEL_SHIFT;
		div = (con & CLK_EMMC_DIV_MASK) >>
		      CLK_EMMC_DIV_SHIFT;
		if (sel)
			prate = OSC_HZ;
		else
			prate = 400 * MHz;
		return DIV_TO_RATE(prate, div);
	case SCLK_SFC:
	case HCLK_SFC:
		con = readl(&cru->peri_clksel_con[7]);
		sel = (con & CLK_SFC_SEL_MASK) >>
		      CLK_SFC_SEL_SHIFT;
		div = (con & CLK_SFC_DIV_MASK) >>
		      CLK_SFC_DIV_SHIFT;
		if (sel == CLK_SFC_SEL_500M)
			prate = 500 * MHz;
		else if (sel == CLK_SFC_SEL_300M)
			prate = 300 * MHz;
		else if (sel == CLK_SFC_SEL_200M)
			prate = 200 * MHz;
		else
			prate = OSC_HZ;
		return DIV_TO_RATE(prate, div);
	default:
		return -ENOENT;
	}
}

static ulong rv1106_mmc_set_clk(struct rv1106_clk_priv *priv,
				ulong clk_id, ulong rate)
{
	struct rv1106_cru *cru = priv->cru;
	u32 sel, src_clk_div;
	ulong prate = 0;

	if ((OSC_HZ % rate) == 0) {
		sel = CLK_MMC_SEL_24M;
		prate = OSC_HZ;
	} else {
		sel = CLK_MMC_SEL_400M;
		prate = 400 * MHz;
	}
	src_clk_div = DIV_ROUND_UP(prate, rate);

	switch (clk_id) {
	case CCLK_SRC_SDMMC:
	case HCLK_SDMMC:
		if ((OSC_HZ % rate) == 0) {
			sel = CLK_MMC_SEL_24M;
			prate = OSC_HZ;
		} else {
			sel = CLK_MMC_SEL_400M;
			prate = 400 * MHz;
		}
		src_clk_div = DIV_ROUND_UP(prate, rate);
		rk_clrsetreg(&cru->vi_clksel_con[1],
			     CLK_SDMMC_SEL_MASK |
			     CLK_SDMMC_DIV_MASK,
			     (sel << CLK_SDMMC_SEL_SHIFT) |
			     ((src_clk_div - 1) <<
			      CLK_SDMMC_DIV_SHIFT));
		break;
	case CCLK_SRC_EMMC:
	case HCLK_EMMC:
		if ((OSC_HZ % rate) == 0) {
			sel = CLK_MMC_SEL_24M;
			prate = OSC_HZ;
		} else {
			sel = CLK_MMC_SEL_400M;
			prate = 400 * MHz;
		}
		src_clk_div = DIV_ROUND_UP(prate, rate);
		rk_clrsetreg(&cru->peri_clksel_con[7],
			     CLK_EMMC_SEL_MASK |
			     CLK_EMMC_DIV_MASK,
			     (sel << CLK_EMMC_SEL_SHIFT) |
			     ((src_clk_div - 1) <<
			      CLK_EMMC_DIV_SHIFT));
		break;
	case SCLK_SFC:
	case HCLK_SFC:
		if ((OSC_HZ % rate) == 0) {
			sel = CLK_SFC_SEL_24M;
			prate = OSC_HZ;
		} else if ((500 * MHz % rate) == 0) {
			sel = CLK_SFC_SEL_500M;
			prate = 500 * MHz;
		} else if ((300 * MHz % rate) == 0) {
			sel = CLK_SFC_SEL_300M;
			prate = 300 * MHz;
		} else {
			sel = CLK_SFC_SEL_200M;
			prate = 200 * MHz;
		}
		src_clk_div = DIV_ROUND_UP(prate, rate);
		rk_clrsetreg(&cru->peri_clksel_con[7],
			     CLK_SFC_SEL_MASK |
			     CLK_SFC_DIV_MASK,
			     (sel << CLK_SFC_SEL_SHIFT) |
			     ((src_clk_div - 1) <<
			      CLK_SFC_DIV_SHIFT));
		break;
	default:
		return -ENOENT;
	}
	return rv1106_mmc_get_clk(priv, clk_id);
}

#ifndef CONFIG_ROCKCHIP_IMAGE_TINY
static ulong rv1106_i2c_set_clk(struct rv1106_clk_priv *priv, ulong clk_id,
				ulong rate)
{
	struct rv1106_cru *cru = priv->cru;
	int src_clk;

	if (rate >= 198 * MHz)
		src_clk = CLK_I2C0_SEL_200M;
	else if (rate >= 99 * MHz)
		src_clk = CLK_I2C0_SEL_100M;
	else if (rate >= 48 * MHz)
		src_clk = CLK_I2C0_SEL_50M;
	else
		src_clk = CLK_I2C0_SEL_24M;

	switch (clk_id) {
	case CLK_I2C1:
		if (rate >= 198 * MHz)
			src_clk = CLK_I2C1_SEL_200M;
		else if (rate >= 99 * MHz)
			src_clk = CLK_I2C1_SEL_100M;
		else if (rate >= 24 * MHz)
			src_clk = CLK_I2C1_SEL_24M;
		else
			src_clk = CLK_I2C1_SEL_32K;
		rk_clrsetreg(&cru->clksel_con[71], CLK_I2C1_SEL_MASK,
			     src_clk << CLK_I2C1_SEL_SHIFT);
		return rv1106_i2c_get_clk(priv, clk_id);
	case CLK_I2C0:
		rk_clrsetreg(&cru->peri_clksel_con[1], CLK_I2C0_SEL_MASK,
			     src_clk << CLK_I2C0_SEL_SHIFT);
		break;
	case CLK_I2C2:
		rk_clrsetreg(&cru->peri_clksel_con[1], CLK_I2C2_SEL_MASK,
			     src_clk << CLK_I2C2_SEL_SHIFT);
		break;
	case CLK_I2C3:
		rk_clrsetreg(&cru->peri_clksel_con[1], CLK_I2C3_SEL_MASK,
			     src_clk << CLK_I2C3_SEL_SHIFT);
		break;
	case CLK_I2C4:
		rk_clrsetreg(&cru->peri_clksel_con[2], CLK_I2C4_SEL_MASK,
			     src_clk << CLK_I2C4_SEL_SHIFT);
		break;
	default:
		return -ENOENT;
	}

	return rv1106_i2c_get_clk(priv, clk_id);
}
#endif

static ulong rv1106_spi_get_clk(struct rv1106_clk_priv *priv, ulong clk_id)
{
	struct rv1106_cru *cru = priv->cru;
	u32 sel, con, rate;

	switch (clk_id) {
	case CLK_SPI0:
		con = readl(&cru->vepu_clksel_con[0]);
		sel = (con & CLK_SPI0_SEL_MASK) >> CLK_SPI0_SEL_SHIFT;
		break;
	case CLK_SPI1:
		con = readl(&cru->peri_clksel_con[6]);
		sel = (con & CLK_SPI1_SEL_MASK) >> CLK_SPI1_SEL_SHIFT;
		break;
	default:
		return -ENOENT;
	}
	if (sel == CLK_SPI0_SEL_200M)
		rate = 200 * MHz;
	else if (sel == CLK_SPI0_SEL_100M)
		rate = 100 * MHz;
	else if (sel == CLK_SPI0_SEL_50M)
		rate = 50 * MHz;
	else
		rate = OSC_HZ;

	return rate;
}

static ulong rv1106_spi_set_clk(struct rv1106_clk_priv *priv,
				ulong clk_id, ulong rate)
{
	struct rv1106_cru *cru = priv->cru;
	int src_clk;

	if (rate >= 198 * MHz)
		src_clk = CLK_SPI0_SEL_200M;
	else if (rate >= 99 * MHz)
		src_clk = CLK_SPI0_SEL_100M;
	else if (rate >= 48 * MHz)
		src_clk = CLK_SPI0_SEL_50M;
	else
		src_clk = CLK_SPI0_SEL_24M;

	switch (clk_id) {
	case CLK_SPI0:
		rk_clrsetreg(&cru->vepu_clksel_con[0], CLK_SPI0_SEL_MASK,
			     src_clk << CLK_SPI0_SEL_SHIFT);
		break;
	case CLK_SPI1:
		rk_clrsetreg(&cru->peri_clksel_con[6], CLK_SPI1_SEL_MASK,
			     src_clk << CLK_SPI1_SEL_SHIFT);
		break;
	default:
		return -ENOENT;
	}

	return rv1106_spi_get_clk(priv, clk_id);
}

#ifndef CONFIG_ROCKCHIP_IMAGE_TINY
static ulong rv1106_pwm_get_clk(struct rv1106_clk_priv *priv, ulong clk_id)
{
	struct rv1106_cru *cru = priv->cru;
	u32 sel, con;

	switch (clk_id) {
	case CLK_PWM0_PERI:
		con = readl(&cru->peri_clksel_con[11]);
		sel = (con & CLK_PWM0_SEL_MASK) >> CLK_PWM0_SEL_SHIFT;
		break;
	case CLK_PWM1_PERI:
		con = readl(&cru->peri_clksel_con[6]);
		sel = (con & CLK_PWM1_SEL_MASK) >> CLK_PWM1_SEL_SHIFT;
		break;
	case CLK_PWM2_PERI:
		con = readl(&cru->peri_clksel_con[6]);
		sel = (con & CLK_PWM2_SEL_MASK) >> CLK_PWM2_SEL_SHIFT;
		break;
	default:
		return -ENOENT;
	}

	switch (sel) {
	case CLK_PWM_SEL_100M:
		return 100 * MHz;
	case CLK_PWM_SEL_50M:
		return 100 * MHz;
	case CLK_PWM_SEL_24M:
		return OSC_HZ;
	default:
		return -ENOENT;
	}
}

static ulong rv1106_pwm_set_clk(struct rv1106_clk_priv *priv,
				ulong clk_id, ulong rate)
{
	struct rv1106_cru *cru = priv->cru;
	int src_clk;

	if (rate >= 99 * MHz)
		src_clk = CLK_PWM_SEL_100M;
	else if (rate >= 48 * MHz)
		src_clk = CLK_PWM_SEL_50M;
	else
		src_clk = CLK_PWM_SEL_24M;

	switch (clk_id) {
	case CLK_PWM0_PERI:
		rk_clrsetreg(&cru->peri_clksel_con[11],
			     CLK_PWM0_SEL_MASK,
			     src_clk << CLK_PWM0_SEL_SHIFT);
		break;
	case CLK_PWM1_PERI:
		rk_clrsetreg(&cru->peri_clksel_con[6],
			     CLK_PWM1_SEL_MASK,
			     src_clk << CLK_PWM1_SEL_SHIFT);
		break;
	case CLK_PWM2_PERI:
		rk_clrsetreg(&cru->peri_clksel_con[6],
			     CLK_PWM2_SEL_MASK,
			     src_clk << CLK_PWM2_SEL_SHIFT);
		break;
	default:
		return -ENOENT;
	}

	return rv1106_pwm_get_clk(priv, clk_id);
}
#endif

static ulong rv1106_adc_get_clk(struct rv1106_clk_priv *priv, ulong clk_id)
{
	struct rv1106_cru *cru = priv->cru;
	u32 div, con;

	switch (clk_id) {
	case CLK_SARADC:
		con = readl(&cru->peri_clksel_con[6]);
		div = (con & CLK_SARADC_DIV_MASK) >>
		      CLK_SARADC_DIV_SHIFT;
		return DIV_TO_RATE(OSC_HZ, div);
	case CLK_TSADC_TSEN:
		con = readl(&cru->vo_clksel_con[3]);
		div = (con & CLK_TSADC_TSEN_DIV_MASK) >>
		      CLK_TSADC_TSEN_DIV_SHIFT;
		return DIV_TO_RATE(OSC_HZ, div);
	case CLK_TSADC:
		con = readl(&cru->vo_clksel_con[3]);
		div = (con & CLK_TSADC_DIV_MASK) >> CLK_TSADC_DIV_SHIFT;
		return DIV_TO_RATE(OSC_HZ, div);
	default:
		return -ENOENT;
	}
}

static ulong rv1106_adc_set_clk(struct rv1106_clk_priv *priv,
				ulong clk_id, ulong rate)
{
	struct rv1106_cru *cru = priv->cru;
	int src_clk_div;

	src_clk_div = DIV_ROUND_UP(OSC_HZ, rate);

	switch (clk_id) {
	case CLK_SARADC:
		assert(src_clk_div - 1 <= 7);
		rk_clrsetreg(&cru->peri_clksel_con[6],
			     CLK_SARADC_DIV_MASK,
			     (src_clk_div - 1) <<
			     CLK_SARADC_DIV_SHIFT);
		break;
	case CLK_TSADC_TSEN:
		assert(src_clk_div - 1 <= 128);
		rk_clrsetreg(&cru->vo_clksel_con[3],
			     CLK_TSADC_TSEN_DIV_MASK,
			     (src_clk_div - 1) <<
			     CLK_TSADC_TSEN_DIV_SHIFT);
		break;
	case CLK_TSADC:
		assert(src_clk_div - 1 <= 128);
		rk_clrsetreg(&cru->vo_clksel_con[3],
			     CLK_TSADC_DIV_MASK,
			     (src_clk_div - 1) <<
			     CLK_TSADC_DIV_SHIFT);
		break;
	default:
		return -ENOENT;
	}
	return rv1106_adc_get_clk(priv, clk_id);
}

#ifndef CONFIG_ROCKCHIP_IMAGE_TINY
/*
 *
 * rational_best_approximation(31415, 10000,
 *		(1 << 8) - 1, (1 << 5) - 1, &n, &d);
 *
 * you may look at given_numerator as a fixed point number,
 * with the fractional part size described in given_denominator.
 *
 * for theoretical background, see:
 * http://en.wikipedia.org/wiki/Continued_fraction
 */
static void rational_best_approximation(unsigned long given_numerator,
					unsigned long given_denominator,
					unsigned long max_numerator,
					unsigned long max_denominator,
					unsigned long *best_numerator,
					unsigned long *best_denominator)
{
	unsigned long n, d, n0, d0, n1, d1;

	n = given_numerator;
	d = given_denominator;
	n0 = 0;
	d1 = 0;
	n1 = 1;
	d0 = 1;
	for (;;) {
		unsigned long t, a;

		if (n1 > max_numerator || d1 > max_denominator) {
			n1 = n0;
			d1 = d0;
			break;
		}
		if (d == 0)
			break;
		t = d;
		a = n / d;
		d = n % d;
		n = t;
		t = n0 + a * n1;
		n0 = n1;
		n1 = t;
		t = d0 + a * d1;
		d0 = d1;
		d1 = t;
	}
	*best_numerator = n1;
	*best_denominator = d1;
}

static ulong rv1106_uart_get_rate(struct rv1106_clk_priv *priv, ulong clk_id)
{
	struct rv1106_cru *cru = priv->cru;
	u32 reg, con, fracdiv, div, src, p_src, p_rate;
	unsigned long m, n;

	switch (clk_id) {
	case SCLK_UART0:
		reg = 5;
		break;
	case SCLK_UART1:
		reg = 7;
		break;
	case SCLK_UART2:
		reg = 9;
		break;
	case SCLK_UART3:
		reg = 11;
		break;
	case SCLK_UART4:
		reg = 13;
		break;
	case SCLK_UART5:
		reg = 15;
		break;
	default:
		return -ENOENT;
	}
	con = readl(&cru->clksel_con[reg + 2]);
	src = (con & CLK_UART_SEL_MASK) >> CLK_UART_SEL_SHIFT;
	con = readl(&cru->clksel_con[reg]);
	div = (con & CLK_UART_SRC_DIV_MASK) >> CLK_UART_SRC_DIV_SHIFT;
	p_src = (con & CLK_UART_SRC_SEL_MASK) >> CLK_UART_SRC_SEL_SHIFT;
	if (p_src == CLK_UART_SRC_SEL_GPLL)
		p_rate = priv->gpll_hz;
	else if (p_src == CLK_UART_SRC_SEL_CPLL)
		p_rate = priv->cpll_hz;
	else
		p_rate = 480000000;
	if (src == CLK_UART_SEL_SRC) {
		return DIV_TO_RATE(p_rate, div);
	} else if (src == CLK_UART_SEL_FRAC) {
		fracdiv = readl(&cru->clksel_con[reg + 1]);
		n = fracdiv & CLK_UART_FRAC_NUMERATOR_MASK;
		n >>= CLK_UART_FRAC_NUMERATOR_SHIFT;
		m = fracdiv & CLK_UART_FRAC_DENOMINATOR_MASK;
		m >>= CLK_UART_FRAC_DENOMINATOR_SHIFT;
		return DIV_TO_RATE(p_rate, div) * n / m;
	} else {
		return OSC_HZ;
	}
}

static ulong rv1106_uart_set_rate(struct rv1106_clk_priv *priv,
				  ulong clk_id, ulong rate)
{
	struct rv1106_cru *cru = priv->cru;
	u32 reg, clk_src, uart_src, div;
	unsigned long m = 0, n = 0, val;

	if (priv->gpll_hz % rate == 0) {
		clk_src = CLK_UART_SRC_SEL_GPLL;
		uart_src = CLK_UART_SEL_SRC;
		div = DIV_ROUND_UP(priv->gpll_hz, rate);
	} else if (priv->cpll_hz % rate == 0) {
		clk_src = CLK_UART_SRC_SEL_CPLL;
		uart_src = CLK_UART_SEL_SRC;
		div = DIV_ROUND_UP(priv->gpll_hz, rate);
	} else if (rate == OSC_HZ) {
		clk_src = CLK_UART_SRC_SEL_GPLL;
		uart_src = CLK_UART_SEL_XIN24M;
		div = 2;
	} else {
		clk_src = CLK_UART_SRC_SEL_GPLL;
		uart_src = CLK_UART_SEL_FRAC;
		div = 2;
		rational_best_approximation(rate, priv->gpll_hz / div,
					    GENMASK(16 - 1, 0),
					    GENMASK(16 - 1, 0),
					    &m, &n);
	}

	switch (clk_id) {
	case SCLK_UART0:
		reg = 5;
		break;
	case SCLK_UART1:
		reg = 7;
		break;
	case SCLK_UART2:
		reg = 9;
		break;
	case SCLK_UART3:
		reg = 11;
		break;
	case SCLK_UART4:
		reg = 13;
		break;
	case SCLK_UART5:
		reg = 15;
		break;
	default:
		return -ENOENT;
	}
	rk_clrsetreg(&cru->clksel_con[reg],
		     CLK_UART_SRC_SEL_MASK |
		     CLK_UART_SRC_DIV_MASK,
		     (clk_src << CLK_UART_SRC_SEL_SHIFT) |
		     ((div - 1) << CLK_UART_SRC_DIV_SHIFT));
	rk_clrsetreg(&cru->clksel_con[reg + 2],
		     CLK_UART_SEL_MASK,
		     uart_src << CLK_UART_SEL_SHIFT);
	if (m && n) {
		val = m << CLK_UART_FRAC_NUMERATOR_SHIFT | n;
		writel(val, &cru->clksel_con[reg + 1]);
	}

	return rv1106_uart_get_rate(priv, clk_id);
}

static ulong rv1106_vop_get_clk(struct rv1106_clk_priv *priv, ulong clk_id)
{
	struct rv1106_cru *cru = priv->cru;
	u32 div, sel, con;

	switch (clk_id) {
	case ACLK_VOP_ROOT:
	case ACLK_VOP:
		con = readl(&cru->vo_clksel_con[1]);
		sel = (con & ACLK_VOP_SEL_MASK) >> ACLK_VOP_SEL_SHIFT;
		if (sel == ACLK_VOP_SEL_300M)
			return 300 * MHz;
		else if (sel == ACLK_VOP_SEL_200M)
			return 200 * MHz;
		else if (sel == ACLK_VOP_SEL_100M)
			return 100 * MHz;
		else
			return  OSC_HZ;
	case DCLK_VOP_SRC:
	case DCLK_VOP:
		con = readl(&cru->clksel_con[23]);
		sel = (con & DCLK_VOP_SEL_MASK) >> DCLK_VOP_SEL_SHIFT;
		div = (con & DCLK_VOP_DIV_MASK) >> DCLK_VOP_DIV_SHIFT;
		if (sel == DCLK_VOP_SEL_GPLL)
			return DIV_TO_RATE(priv->gpll_hz, div);
		else
			return DIV_TO_RATE(priv->cpll_hz, div);
	default:
		return -ENOENT;
	}
}

static ulong rv1106_vop_set_clk(struct rv1106_clk_priv *priv,
				ulong clk_id, ulong rate)
{
	struct rv1106_cru *cru = priv->cru;
	int div, sel;

	switch (clk_id) {
	case ACLK_VOP_ROOT:
	case ACLK_VOP:
		if (rate >= 297 * MHz)
			sel = ACLK_VOP_SEL_300M;
		else if (rate >= 198 * MHz)
			sel = ACLK_VOP_SEL_200M;
		else if (rate >= 99 * MHz)
			sel = ACLK_VOP_SEL_100M;
		else
			sel = ACLK_VOP_SEL_24M;
		rk_clrsetreg(&cru->vo_clksel_con[1],
			     ACLK_VOP_SEL_MASK,
			     sel << ACLK_VOP_SEL_SHIFT);
		break;
	case DCLK_VOP_SRC:
	case DCLK_VOP:
		if ((priv->cpll_hz % rate) == 0) {
			sel = DCLK_VOP_SEL_CPLL;
			div = DIV_ROUND_UP(priv->cpll_hz, rate);
		} else {
			sel = DCLK_VOP_SEL_GPLL;
			div = DIV_ROUND_UP(priv->gpll_hz, rate);
		}
		rk_clrsetreg(&cru->clksel_con[23],
			     DCLK_VOP_SEL_MASK |
			     DCLK_VOP_DIV_MASK,
			     sel << DCLK_VOP_SEL_SHIFT |
			     (div - 1) << DCLK_VOP_DIV_SHIFT);
		break;
	default:
		return -ENOENT;
	}

	return rv1106_vop_get_clk(priv, clk_id);
}
#endif

static ulong rv1106_clk_get_rate(struct clk *clk)
{
	struct rv1106_clk_priv *priv = dev_get_priv(clk->dev);
	ulong rate = 0;

	if (!priv->gpll_hz) {
		printf("%s gpll=%lu\n", __func__, priv->gpll_hz);
		return -ENOENT;
	}

	switch (clk->id) {
#ifndef CONFIG_ROCKCHIP_IMAGE_TINY
	case PLL_APLL:
		rate = rockchip_pll_get_rate(&rv1106_pll_clks[APLL], priv->cru,
					     APLL);
		break;
	case PLL_DPLL:
		rate = rockchip_pll_get_rate(&rv1106_pll_clks[DPLL], priv->cru,
					     DPLL);
		break;
	case PLL_CPLL:
		rate = rockchip_pll_get_rate(&rv1106_pll_clks[CPLL], priv->cru,
					     CPLL);
		break;
	case PLL_GPLL:
		rate = rockchip_pll_get_rate(&rv1106_pll_clks[GPLL], priv->cru,
					     GPLL);
		break;
	case ACLK_PERI_ROOT:
	case HCLK_PERI_ROOT:
	case PCLK_PERI_ROOT:
	case ACLK_BUS_ROOT:
	case PCLK_TOP_ROOT:
	case PCLK_PMU_ROOT:
	case HCLK_PMU_ROOT:
		rate = rv1106_peri_get_clk(priv, clk->id);
		break;
#endif
	case CLK_CORE_CRYPTO:
	case CLK_PKA_CRYPTO:
	case ACLK_CRYPTO:
		rate = rv1106_crypto_get_clk(priv, clk->id);
		break;
	case CCLK_SRC_SDMMC:
	case CCLK_SRC_EMMC:
	case SCLK_SFC:
	case HCLK_SDMMC:
	case HCLK_EMMC:
	case HCLK_SFC:
		rate = rv1106_mmc_get_clk(priv, clk->id);
		break;
#ifndef CONFIG_ROCKCHIP_IMAGE_TINY
	case CLK_I2C0:
	case CLK_I2C1:
	case CLK_I2C2:
	case CLK_I2C3:
	case CLK_I2C4:
		rate = rv1106_i2c_get_clk(priv, clk->id);
		break;
#endif
	case CLK_SPI0:
	case CLK_SPI1:
		rate = rv1106_spi_get_clk(priv, clk->id);
		break;
#ifndef CONFIG_ROCKCHIP_IMAGE_TINY
	case CLK_PWM0_PERI:
	case CLK_PWM1_PERI:
	case CLK_PWM2_PERI:
		rate = rv1106_pwm_get_clk(priv, clk->id);
		break;
#endif
	case CLK_SARADC:
	case CLK_TSADC_TSEN:
	case CLK_TSADC:
		rate = rv1106_adc_get_clk(priv, clk->id);
		break;
#ifndef CONFIG_ROCKCHIP_IMAGE_TINY
	case SCLK_UART0:
	case SCLK_UART1:
	case SCLK_UART2:
	case SCLK_UART3:
	case SCLK_UART4:
	case SCLK_UART5:
		rate = rv1106_uart_get_rate(priv, clk->id);
		break;
	case DCLK_VOP_SRC:
	case DCLK_VOP:
	case ACLK_VOP_ROOT:
	case ACLK_VOP:
		rate = rv1106_vop_get_clk(priv, clk->id);
		break;
#endif
	default:
		return -ENOENT;
	}

	return rate;
};

static ulong rv1106_clk_set_rate(struct clk *clk, ulong rate)
{
	struct rv1106_clk_priv *priv = dev_get_priv(clk->dev);
	ulong ret = 0;

	if (!priv->gpll_hz) {
		printf("%s gpll=%lu\n", __func__, priv->gpll_hz);
		return -ENOENT;
	}

	switch (clk->id) {
#ifndef CONFIG_ROCKCHIP_IMAGE_TINY
	case PLL_APLL:
		ret = rockchip_pll_set_rate(&rv1106_pll_clks[APLL], priv->cru,
					    APLL, rate);
		break;
	case PLL_CPLL:
		ret = rockchip_pll_set_rate(&rv1106_pll_clks[CPLL], priv->cru,
					    CPLL, rate);
		break;
	case PLL_GPLL:
		ret = rockchip_pll_set_rate(&rv1106_pll_clks[GPLL], priv->cru,
					    GPLL, rate);
		break;
	case ACLK_PERI_ROOT:
	case HCLK_PERI_ROOT:
	case PCLK_PERI_ROOT:
	case ACLK_BUS_ROOT:
	case PCLK_TOP_ROOT:
	case PCLK_PMU_ROOT:
	case HCLK_PMU_ROOT:
		ret = rv1106_peri_set_clk(priv, clk->id, rate);
		break;
#endif
	case CLK_CORE_CRYPTO:
	case CLK_PKA_CRYPTO:
	case ACLK_CRYPTO:
		ret = rv1106_crypto_set_clk(priv, clk->id, rate);
		break;
	case CCLK_SRC_SDMMC:
	case CCLK_SRC_EMMC:
	case SCLK_SFC:
	case HCLK_SDMMC:
	case HCLK_EMMC:
	case HCLK_SFC:
		ret = rv1106_mmc_set_clk(priv, clk->id, rate);
		break;
#ifndef CONFIG_ROCKCHIP_IMAGE_TINY
	case CLK_I2C0:
	case CLK_I2C1:
	case CLK_I2C2:
	case CLK_I2C3:
	case CLK_I2C4:
		ret = rv1106_i2c_set_clk(priv, clk->id, rate);
		break;
#endif
	case CLK_SPI0:
	case CLK_SPI1:
		ret = rv1106_spi_set_clk(priv, clk->id, rate);
		break;
#ifndef CONFIG_ROCKCHIP_IMAGE_TINY
	case CLK_PWM0_PERI:
	case CLK_PWM1_PERI:
	case CLK_PWM2_PERI:
		ret = rv1106_pwm_set_clk(priv, clk->id, rate);
		break;
#endif
	case CLK_SARADC:
	case CLK_TSADC_TSEN:
	case CLK_TSADC:
		ret = rv1106_adc_set_clk(priv, clk->id, rate);
		break;
#ifndef CONFIG_ROCKCHIP_IMAGE_TINY
	case SCLK_UART0:
	case SCLK_UART1:
	case SCLK_UART2:
	case SCLK_UART3:
	case SCLK_UART4:
	case SCLK_UART5:
		ret = rv1106_uart_set_rate(priv, clk->id, rate);
		break;
	case DCLK_VOP_SRC:
	case DCLK_VOP:
	case ACLK_VOP_ROOT:
	case ACLK_VOP:
		rate = rv1106_vop_set_clk(priv, clk->id, rate);
		break;
#endif
	default:
		return -ENOENT;
	}

	return ret;
};

static int rv1106_clk_set_parent(struct clk *clk, struct clk *parent)
{
	switch (clk->id) {
	default:
		return -ENOENT;
	}

	return 0;
}

static struct clk_ops rv1106_clk_ops = {
	.get_rate = rv1106_clk_get_rate,
	.set_rate = rv1106_clk_set_rate,
#if CONFIG_IS_ENABLED(OF_CONTROL) && !CONFIG_IS_ENABLED(OF_PLATDATA)
	.set_parent = rv1106_clk_set_parent,
#endif
};

#ifndef CONFIG_ROCKCHIP_IMAGE_TINY
static void rv1106_clk_init(struct rv1106_clk_priv *priv)
{
	int ret;

	priv->sync_kernel = false;
	if (!priv->armclk_enter_hz) {
		priv->armclk_enter_hz =
			rockchip_pll_get_rate(&rv1106_pll_clks[APLL],
					      priv->cru, APLL);
		priv->armclk_init_hz = priv->armclk_enter_hz;
	}

	if (priv->armclk_init_hz != APLL_HZ) {
			ret = rockchip_pll_set_rate(&rv1106_pll_clks[APLL], priv->cru,
						    APLL, APLL_HZ);
		if (!ret)
			priv->armclk_init_hz = APLL_HZ;
	}

	if (priv->cpll_hz != CPLL_HZ) {
		ret = rockchip_pll_set_rate(&rv1106_pll_clks[CPLL], priv->cru,
					    CPLL, CPLL_HZ);
		if (!ret)
			priv->cpll_hz = CPLL_HZ;
	}

	if (priv->gpll_hz != GPLL_HZ) {
		ret = rockchip_pll_set_rate(&rv1106_pll_clks[GPLL], priv->cru,
					    GPLL, GPLL_HZ);
		if (!ret)
			priv->gpll_hz = GPLL_HZ;
	}
}
#endif

static int rv1106_clk_probe(struct udevice *dev)
{
	struct rv1106_clk_priv *priv = dev_get_priv(dev);
#ifndef CONFIG_ROCKCHIP_IMAGE_TINY
	int ret;

	rv1106_clk_init(priv);

	/* Process 'assigned-{clocks/clock-parents/clock-rates}' properties */
	ret = clk_set_defaults(dev);
	if (ret)
		debug("%s clk_set_defaults failed %d\n", __func__, ret);
	else
		priv->sync_kernel = true;
#else
	priv->gpll_hz = GPLL_HZ;
	priv->cpll_hz = CPLL_HZ;
#endif
	rk_clrsetreg(&priv->cru->core_clksel_con[0],
		     CLK_CORE_DIV_MASK,
		     0 << CLK_CORE_DIV_SHIFT);
	return 0;
}

static int rv1106_clk_ofdata_to_platdata(struct udevice *dev)
{
	struct rv1106_clk_priv *priv = dev_get_priv(dev);

	priv->cru = dev_read_addr_ptr(dev);

	return 0;
}

static int rv1106_clk_bind(struct udevice *dev)
{
	int ret;
	struct udevice *sys_child, *sf_child;
	struct sysreset_reg *priv;
	struct softreset_reg *sf_priv;

	/* The reset driver does not have a device node, so bind it here */
	ret = device_bind_driver(dev, "rockchip_sysreset", "sysreset",
				 &sys_child);
	if (ret) {
		debug("Warning: No sysreset driver: ret=%d\n", ret);
	} else {
		priv = malloc(sizeof(struct sysreset_reg));
		priv->glb_srst_fst_value = offsetof(struct rv1106_cru,
						    glb_srst_fst);
		priv->glb_srst_snd_value = offsetof(struct rv1106_cru,
						    glb_srst_snd);
		sys_child->priv = priv;
	}

	ret = device_bind_driver_to_node(dev, "rockchip_reset", "reset",
					 dev_ofnode(dev), &sf_child);
	if (ret) {
		debug("Warning: No rockchip reset driver: ret=%d\n", ret);
	} else {
		sf_priv = malloc(sizeof(struct softreset_reg));
		sf_priv->sf_reset_offset = offsetof(struct rv1106_cru,
						    pmu_softrst_con[0]);
		sf_priv->sf_reset_num = 31745;
		sf_child->priv = sf_priv;
	}

	return 0;
}

static const struct udevice_id rv1106_clk_ids[] = {
	{ .compatible = "rockchip,rv1106-cru" },
	{ }
};

U_BOOT_DRIVER(rockchip_rv1106_cru) = {
	.name		= "rockchip_rv1106_cru",
	.id		= UCLASS_CLK,
	.of_match	= rv1106_clk_ids,
	.priv_auto_alloc_size = sizeof(struct rv1106_clk_priv),
	.ofdata_to_platdata = rv1106_clk_ofdata_to_platdata,
	.ops		= &rv1106_clk_ops,
	.bind		= rv1106_clk_bind,
	.probe		= rv1106_clk_probe,
};

static ulong rv1106_grfclk_get_rate(struct clk *clk)
{
	struct udevice *cru_dev;
	struct rv1106_clk_priv *cru_priv;
	int ret;
	ulong rate = 0;

	ret = uclass_get_device_by_driver(UCLASS_CLK,
					  DM_GET_DRIVER(rockchip_rv1106_cru),
					  &cru_dev);
	if (ret) {
		printf("%s: could not find cru device\n", __func__);
		return ret;
	}
	cru_priv = dev_get_priv(cru_dev);

	switch (clk->id) {
	case SCLK_EMMC_SAMPLE:
		rate = rv1106_mmc_get_clk(cru_priv, CCLK_SRC_EMMC) / 2;
		break;
	case SCLK_SDMMC_SAMPLE:
		rate = rv1106_mmc_get_clk(cru_priv, CCLK_SRC_SDMMC) / 2;
		break;
	case SCLK_SDIO_SAMPLE:
		rate = rv1106_mmc_get_clk(cru_priv, CCLK_SRC_SDIO) / 2;
		break;
	default:
		return -ENOENT;
	}

	return rate;
};

#define ROCKCHIP_MMC_DELAY_SEL		BIT(10)
#define ROCKCHIP_MMC_DEGREE_MASK	0x3
#define ROCKCHIP_MMC_DELAYNUM_OFFSET	2
#define ROCKCHIP_MMC_DELAYNUM_MASK	(0xff << ROCKCHIP_MMC_DELAYNUM_OFFSET)

#define PSECS_PER_SEC 1000000000000LL
/*
 * Each fine delay is between 44ps-77ps. Assume each fine delay is 60ps to
 * simplify calculations. So 45degs could be anywhere between 33deg and 57.8deg.
 */
#define ROCKCHIP_MMC_DELAY_ELEMENT_PSEC 60

int rv1106_mmc_get_phase(struct clk *clk)
{
	struct rv1106_grf_clk_priv *priv = dev_get_priv(clk->dev);
	u32 raw_value = 0, delay_num;
	u16 degrees = 0;
	ulong rate;

	rate = rv1106_grfclk_get_rate(clk);
	if (rate < 0)
		return rate;

	if (clk->id == SCLK_EMMC_SAMPLE)
		raw_value = readl(&priv->grf->emmc_con1);
	else if (clk->id == SCLK_SDMMC_SAMPLE)
		raw_value = readl(&priv->grf->sdmmc_con1);
	else if (clk->id == SCLK_SDIO_SAMPLE)
		raw_value = readl(&priv->grf->sdio_con1);

	raw_value >>= 1;
	degrees = (raw_value & ROCKCHIP_MMC_DEGREE_MASK) * 90;

	if (raw_value & ROCKCHIP_MMC_DELAY_SEL) {
		/* degrees/delaynum * 10000 */
		unsigned long factor = (ROCKCHIP_MMC_DELAY_ELEMENT_PSEC / 10) *
					36 * (rate / 1000000);

		delay_num = (raw_value & ROCKCHIP_MMC_DELAYNUM_MASK);
		delay_num >>= ROCKCHIP_MMC_DELAYNUM_OFFSET;
		degrees += DIV_ROUND_CLOSEST(delay_num * factor, 10000);
	}

	return degrees % 360;
}

int rv1106_mmc_set_phase(struct clk *clk, u32 degrees)
{
	struct rv1106_grf_clk_priv *priv = dev_get_priv(clk->dev);
	u8 nineties, remainder, delay_num;
	u32 raw_value, delay;
	ulong rate;

	rate = rv1106_grfclk_get_rate(clk);
	if (rate < 0)
		return rate;

	nineties = degrees / 90;
	remainder = (degrees % 90);

	/*
	 * Convert to delay; do a little extra work to make sure we
	 * don't overflow 32-bit / 64-bit numbers.
	 */
	delay = 10000000; /* PSECS_PER_SEC / 10000 / 10 */
	delay *= remainder;
	delay = DIV_ROUND_CLOSEST(delay, (rate / 1000) * 36 *
				  (ROCKCHIP_MMC_DELAY_ELEMENT_PSEC / 10));

	delay_num = (u8)min_t(u32, delay, 255);

	raw_value = delay_num ? ROCKCHIP_MMC_DELAY_SEL : 0;
	raw_value |= delay_num << ROCKCHIP_MMC_DELAYNUM_OFFSET;
	raw_value |= nineties;

	raw_value <<= 1;
	if (clk->id == SCLK_EMMC_SAMPLE)
		writel(raw_value | 0xffff0000, &priv->grf->emmc_con1);
	else if (clk->id == SCLK_SDMMC_SAMPLE)
		writel(raw_value | 0xffff0000, &priv->grf->sdmmc_con1);
	else if (clk->id == SCLK_SDIO_SAMPLE)
		writel(raw_value | 0xffff0000, &priv->grf->sdio_con1);

	debug("mmc set_phase(%d) delay_nums=%u reg=%#x actual_degrees=%d\n",
	      degrees, delay_num, raw_value, rv1106_mmc_get_phase(clk));

	return 0;
}

static int rv1106_grfclk_get_phase(struct clk *clk)
{
	int ret;

	debug("%s %ld\n", __func__, clk->id);
	switch (clk->id) {
	case SCLK_EMMC_SAMPLE:
	case SCLK_SDMMC_SAMPLE:
	case SCLK_SDIO_SAMPLE:
		ret = rv1106_mmc_get_phase(clk);
		break;
	default:
		return -ENOENT;
	}
	return ret;
}

static int rv1106_grfclk_set_phase(struct clk *clk, int degrees)
{
	int ret;

	debug("%s %ld\n", __func__, clk->id);
	switch (clk->id) {
	case SCLK_EMMC_SAMPLE:
	case SCLK_SDMMC_SAMPLE:
	case SCLK_SDIO_SAMPLE:
		ret = rv1106_mmc_set_phase(clk, degrees);
		break;
	default:
		return -ENOENT;
	}

	return ret;
}

static struct clk_ops rv1106_grfclk_ops = {
	.get_rate = rv1106_grfclk_get_rate,
	.get_phase = rv1106_grfclk_get_phase,
	.set_phase = rv1106_grfclk_set_phase,
};

static int rv1106_grfclk_probe(struct udevice *dev)
{
	struct rv1106_grf_clk_priv *priv = dev_get_priv(dev);

	priv->grf = syscon_get_first_range(ROCKCHIP_SYSCON_GRF);
	if (IS_ERR(priv->grf))
		return PTR_ERR(priv->grf);

	return 0;
}

static int rv1106_grfclk_ofdata_to_platdata(struct udevice *dev)
{
	return 0;
}

static int rv1106_grfclk_bind(struct udevice *dev)
{
	return 0;
}

static const struct udevice_id rv1106_grfclk_ids[] = {
	{ .compatible = "rockchip,rv1106-grf-cru" },
	{ }
};

U_BOOT_DRIVER(rockchip_rv1106_grf_cru) = {
	.name		= "rockchip_rv1106_grf_cru",
	.id		= UCLASS_CLK,
	.of_match	= rv1106_grfclk_ids,
	.priv_auto_alloc_size = sizeof(struct rv1106_grf_clk_priv),
	.ofdata_to_platdata = rv1106_grfclk_ofdata_to_platdata,
	.ops		= &rv1106_grfclk_ops,
	.bind		= rv1106_grfclk_bind,
	.probe		= rv1106_grfclk_probe,
};

#ifndef CONFIG_SPL_BUILD
/**
 * soc_clk_dump() - Print clock frequencies
 * Returns zero on success
 *
 * Implementation for the clk dump command.
 */
int soc_clk_dump(void)
{
	struct udevice *cru_dev;
	struct rv1106_clk_priv *priv;
	const struct rv1106_clk_info *clk_dump;
	struct clk clk;
	unsigned long clk_count = ARRAY_SIZE(clks_dump);
	unsigned long rate;
	int i, ret;

	ret = uclass_get_device_by_driver(UCLASS_CLK,
					  DM_GET_DRIVER(rockchip_rv1106_cru),
					  &cru_dev);
	if (ret) {
		printf("%s failed to get cru device\n", __func__);
		return ret;
	}

	priv = dev_get_priv(cru_dev);
	printf("CLK: (%s. arm: enter %lu KHz, init %lu KHz, kernel %lu%s)\n",
	       priv->sync_kernel ? "sync kernel" : "uboot",
	       priv->armclk_enter_hz / 1000,
	       priv->armclk_init_hz / 1000,
	       priv->set_armclk_rate ? priv->armclk_hz / 1000 : 0,
	       priv->set_armclk_rate ? " KHz" : "N/A");
	for (i = 0; i < clk_count; i++) {
		clk_dump = &clks_dump[i];
		if (clk_dump->name) {
			clk.id = clk_dump->id;
			if (clk_dump->is_cru)
				ret = clk_request(cru_dev, &clk);
			if (ret < 0)
				return ret;

			rate = clk_get_rate(&clk);
			clk_free(&clk);
			if (i == 0) {
				if (rate < 0)
					printf("  %s %s\n", clk_dump->name,
					       "unknown");
				else
					printf("  %s %lu KHz\n", clk_dump->name,
					       rate / 1000);
			} else {
				if (rate < 0)
					printf("  %s %s\n", clk_dump->name,
					       "unknown");
				else
					printf("  %s %lu KHz\n", clk_dump->name,
					       rate / 1000);
			}
		}
	}

	return 0;
}
#endif
