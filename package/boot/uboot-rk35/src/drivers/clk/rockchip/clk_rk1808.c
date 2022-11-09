// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2018 Fuzhou Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <bitfield.h>
#include <clk-uclass.h>
#include <dm.h>
#include <errno.h>
#include <syscon.h>
#include <clk.h>
#include <asm/arch-rockchip/clock.h>
#include <asm/arch-rockchip/cru_rk1808.h>
#include <asm/arch-rockchip/hardware.h>
#include <asm/io.h>
#include <dm/lists.h>
#include <dt-bindings/clock/rk1808-cru.h>
#include <div64.h>

DECLARE_GLOBAL_DATA_PTR;

#define RK1808_CPUCLK_RATE(_rate, _aclk_div, _pclk_div)		\
{								\
	.rate	= _rate##U,					\
	.aclk_div = _aclk_div,					\
	.pclk_div = _pclk_div,					\
}

#define DIV_TO_RATE(input_rate, div)    ((input_rate) / ((div) + 1))

static struct rockchip_pll_rate_table rk1808_pll_rates[] = {
	/* _mhz, _refdiv, _fbdiv, _postdiv1, _postdiv2, _dsmpd, _frac */
	RK3036_PLL_RATE(1200000000, 1, 50, 1, 1, 1, 0),
	RK3036_PLL_RATE(1188000000, 2, 99, 1, 1, 1, 0),
	RK3036_PLL_RATE(1100000000, 12, 550, 1, 1, 1, 0),
	RK3036_PLL_RATE(1008000000, 1, 84, 2, 1, 1, 0),
	RK3036_PLL_RATE(1000000000, 6, 500, 2, 1, 1, 0),
	RK3036_PLL_RATE(816000000, 1, 68, 2, 1, 1, 0),
	RK3036_PLL_RATE(800000000, 6, 400, 2, 1, 1, 0),
	RK3036_PLL_RATE(600000000, 1, 75, 3, 1, 1, 0),
	RK3036_PLL_RATE(594000000, 2, 99, 2, 1, 1, 0),
	RK3036_PLL_RATE(500000000, 6, 250, 2, 1, 1, 0),
	RK3036_PLL_RATE(200000000, 1, 200, 6, 4, 1, 0),
	RK3036_PLL_RATE(100000000, 1, 150, 6, 6, 1, 0),
	{ /* sentinel */ },
};

#ifndef CONFIG_SPL_BUILD
#define RK1808_CLK_DUMP(_id, _name, _iscru)	\
{						\
	.id = _id,				\
	.name = _name,				\
	.is_cru = _iscru,			\
}

static const struct rk1808_clk_info clks_dump[] = {
	RK1808_CLK_DUMP(PLL_APLL, "apll", true),
	RK1808_CLK_DUMP(PLL_DPLL, "dpll", true),
	RK1808_CLK_DUMP(PLL_CPLL, "cpll", true),
	RK1808_CLK_DUMP(PLL_GPLL, "gpll", true),
	RK1808_CLK_DUMP(PLL_NPLL, "npll", true),
	RK1808_CLK_DUMP(PLL_PPLL, "ppll", true),
	RK1808_CLK_DUMP(HSCLK_BUS_PRE, "hsclk_bus", true),
	RK1808_CLK_DUMP(MSCLK_BUS_PRE, "msclk_bus", true),
	RK1808_CLK_DUMP(LSCLK_BUS_PRE, "lsclk_bus", true),
	RK1808_CLK_DUMP(MSCLK_PERI, "msclk_peri", true),
	RK1808_CLK_DUMP(LSCLK_PERI, "lsclk_peri", true),
};
#endif

static struct rockchip_cpu_rate_table rk1808_cpu_rates[] = {
	RK1808_CPUCLK_RATE(1200000000, 1, 5),
	RK1808_CPUCLK_RATE(1008000000, 1, 5),
	RK1808_CPUCLK_RATE(816000000, 1, 3),
	RK1808_CPUCLK_RATE(600000000, 1, 3),
};

static struct rockchip_pll_clock rk1808_pll_clks[] = {
	[APLL] = PLL(pll_rk3036, PLL_APLL, RK1808_PLL_CON(0),
		     RK1808_MODE_CON, 0, 10, 0, rk1808_pll_rates),
	[DPLL] = PLL(pll_rk3036, PLL_DPLL, RK1808_PLL_CON(8),
		     RK1808_MODE_CON, 2, 10, 0, NULL),
	[CPLL] = PLL(pll_rk3036, PLL_CPLL, RK1808_PLL_CON(16),
		    RK1808_MODE_CON, 4, 10, 0, rk1808_pll_rates),
	[GPLL] = PLL(pll_rk3036, PLL_GPLL, RK1808_PLL_CON(24),
		     RK1808_MODE_CON, 6, 10, 0, rk1808_pll_rates),
	[NPLL] = PLL(pll_rk3036, PLL_NPLL, RK1808_PLL_CON(32),
		     RK1808_MODE_CON, 8, 10, 0, rk1808_pll_rates),
	[PPLL] = PLL(pll_rk3036, PLL_PPLL, RK1808_PMU_PLL_CON(0),
		     RK1808_PMU_MODE_CON, 0, 10, 0, rk1808_pll_rates),
};

#ifndef CONFIG_SPL_BUILD
static ulong rk1808_i2c_get_clk(struct rk1808_clk_priv *priv, ulong clk_id)
{
	struct rk1808_cru *cru = priv->cru;
	u32 div, con;

	switch (clk_id) {
	case SCLK_PMU_I2C0:
		con = readl(&cru->pmu_clksel_con[7]);
		div = (con & CLK_I2C0_DIV_CON_MASK) >> CLK_I2C0_DIV_CON_SHIFT;
		break;
	case SCLK_I2C1:
		con = readl(&cru->clksel_con[59]);
		div = (con & CLK_I2C1_DIV_CON_MASK)  >> CLK_I2C1_DIV_CON_SHIFT;
		break;
	case SCLK_I2C2:
		con = readl(&cru->clksel_con[59]);
		div = (con & CLK_I2C2_DIV_CON_MASK) >> CLK_I2C2_DIV_CON_SHIFT;
		break;
	case SCLK_I2C3:
		con = readl(&cru->clksel_con[60]);
		div = (con & CLK_I2C3_DIV_CON_MASK) >> CLK_I2C3_DIV_CON_SHIFT;
		break;
	case SCLK_I2C4:
		con = readl(&cru->clksel_con[71]);
		div = (con & CLK_I2C4_DIV_CON_MASK) >> CLK_I2C4_DIV_CON_SHIFT;
		break;
	case SCLK_I2C5:
		con = readl(&cru->clksel_con[71]);
		div = (con & CLK_I2C5_DIV_CON_MASK) >> CLK_I2C5_DIV_CON_SHIFT;
		break;
	default:
		printf("do not support this i2c bus\n");
		return -EINVAL;
	}

	return DIV_TO_RATE(priv->gpll_hz, div);
}

static ulong rk1808_i2c_set_clk(struct rk1808_clk_priv *priv,
				ulong clk_id, uint hz)
{
	struct rk1808_cru *cru = priv->cru;
	int src_clk_div;

	src_clk_div = DIV_ROUND_UP(priv->gpll_hz, hz);
	assert(src_clk_div - 1 < 127);

	switch (clk_id) {
	case SCLK_PMU_I2C0:
		rk_clrsetreg(&cru->pmu_clksel_con[7],
			     CLK_I2C0_DIV_CON_MASK | CLK_I2C0_PLL_SEL_MASK,
			     (src_clk_div - 1) << CLK_I2C0_DIV_CON_SHIFT |
			     CLK_I2C0_PLL_SEL_PPLL << CLK_I2C0_PLL_SEL_SHIFT);
		break;
	case SCLK_I2C1:
		rk_clrsetreg(&cru->clksel_con[59],
			     CLK_I2C1_DIV_CON_MASK | CLK_I2C1_PLL_SEL_MASK,
			     (src_clk_div - 1) << CLK_I2C1_DIV_CON_SHIFT |
			     CLK_I2C_PLL_SEL_GPLL << CLK_I2C1_PLL_SEL_SHIFT);
		break;
	case SCLK_I2C2:
		rk_clrsetreg(&cru->clksel_con[59],
			     CLK_I2C2_DIV_CON_MASK | CLK_I2C2_PLL_SEL_MASK,
			     (src_clk_div - 1) << CLK_I2C2_DIV_CON_SHIFT |
			     CLK_I2C_PLL_SEL_GPLL << CLK_I2C2_PLL_SEL_SHIFT);
		break;
	case SCLK_I2C3:
		rk_clrsetreg(&cru->clksel_con[60],
			     CLK_I2C3_DIV_CON_MASK | CLK_I2C3_PLL_SEL_MASK,
			     (src_clk_div - 1) << CLK_I2C3_DIV_CON_SHIFT |
			     CLK_I2C_PLL_SEL_GPLL << CLK_I2C3_PLL_SEL_SHIFT);
		break;
	case SCLK_I2C4:
		rk_clrsetreg(&cru->clksel_con[71],
			     CLK_I2C4_DIV_CON_MASK | CLK_I2C4_PLL_SEL_MASK,
			     (src_clk_div - 1) << CLK_I2C4_DIV_CON_SHIFT |
			     CLK_I2C_PLL_SEL_GPLL << CLK_I2C4_PLL_SEL_SHIFT);
		break;
	case SCLK_I2C5:
		rk_clrsetreg(&cru->clksel_con[71],
			     CLK_I2C5_DIV_CON_MASK | CLK_I2C5_PLL_SEL_MASK,
			     (src_clk_div - 1) << CLK_I2C5_DIV_CON_SHIFT |
			     CLK_I2C_PLL_SEL_GPLL << CLK_I2C5_PLL_SEL_SHIFT);
		break;
	default:
		printf("do not support this i2c bus\n");
		return -EINVAL;
	}

	return rk1808_i2c_get_clk(priv, clk_id);
}
#endif

static ulong rk1808_mmc_get_clk(struct rk1808_clk_priv *priv, uint clk_id)
{
	struct rk1808_cru *cru = priv->cru;
	u32 div, con, con_id;

	switch (clk_id) {
	case HCLK_SDMMC:
	case SCLK_SDMMC:
		con_id = 20;
		break;
	case HCLK_SDIO:
	case SCLK_SDIO:
		con_id = 22;
		break;
	case HCLK_EMMC:
	case SCLK_EMMC:
	case SCLK_EMMC_SAMPLE:
		con_id = 24;
		break;
	default:
		return -EINVAL;
	}

	con = readl(&cru->clksel_con[con_id]);
	div = (con & EMMC_DIV_MASK) >> EMMC_DIV_SHIFT;

	if ((con & EMMC_PLL_MASK) >> EMMC_PLL_SHIFT
	    == EMMC_SEL_24M)
		return DIV_TO_RATE(OSC_HZ, div) / 2;
	else
		return DIV_TO_RATE(priv->gpll_hz, div) / 2;
}

static ulong rk1808_mmc_set_clk(struct rk1808_clk_priv *priv,
				ulong clk_id, ulong set_rate)
{
	struct rk1808_cru *cru = priv->cru;
	int src_clk_div;
	u32 con_id;

	switch (clk_id) {
	case HCLK_SDMMC:
	case SCLK_SDMMC:
		con_id = 20;
		break;
	case HCLK_SDIO:
	case SCLK_SDIO:
		con_id = 22;
		break;
	case HCLK_EMMC:
	case SCLK_EMMC:
		con_id = 24;
		break;
	default:
		return -EINVAL;
	}

	/* Select clk_sdmmc/emmc source from GPLL by default */
	/* mmc clock defaulg div 2 internal, need provide double in cru */
	src_clk_div = DIV_ROUND_UP(priv->gpll_hz / 2, set_rate);

	if (src_clk_div > 127) {
		/* use 24MHz source for 400KHz clock */
		src_clk_div = DIV_ROUND_UP(OSC_HZ / 2, set_rate);
		rk_clrsetreg(&cru->clksel_con[con_id],
			     EMMC_PLL_MASK | EMMC_DIV_MASK,
			     EMMC_SEL_24M << EMMC_PLL_SHIFT |
			     (src_clk_div - 1) << EMMC_DIV_SHIFT);
	} else {
		rk_clrsetreg(&cru->clksel_con[con_id],
			     EMMC_PLL_MASK | EMMC_DIV_MASK,
			     EMMC_SEL_GPLL << EMMC_PLL_SHIFT |
			     (src_clk_div - 1) << EMMC_DIV_SHIFT);
	}
	rk_clrsetreg(&cru->clksel_con[con_id + 1], EMMC_CLK_SEL_MASK,
		     EMMC_CLK_SEL_EMMC);

	return rk1808_mmc_get_clk(priv, clk_id);
}

static ulong rk1808_sfc_get_clk(struct rk1808_clk_priv *priv, uint clk_id)
{
	struct rk1808_cru *cru = priv->cru;
	u32 div, con;

	con = readl(&cru->clksel_con[26]);
	div = (con & SFC_DIV_CON_MASK) >> SFC_DIV_CON_SHIFT;

	return DIV_TO_RATE(priv->gpll_hz, div);
}

static ulong rk1808_sfc_set_clk(struct rk1808_clk_priv *priv,
				ulong clk_id, ulong set_rate)
{
	struct rk1808_cru *cru = priv->cru;
	int src_clk_div;

	src_clk_div = DIV_ROUND_UP(priv->gpll_hz, set_rate);
	rk_clrsetreg(&cru->clksel_con[26],
		     SFC_PLL_SEL_MASK | SFC_DIV_CON_MASK,
		     0 << SFC_PLL_SEL_SHIFT |
		     (src_clk_div - 1) << SFC_DIV_CON_SHIFT);

	return rk1808_sfc_get_clk(priv, clk_id);
}

static ulong rk1808_saradc_get_clk(struct rk1808_clk_priv *priv)
{
	struct rk1808_cru *cru = priv->cru;
	u32 div, con;

	con = readl(&cru->clksel_con[63]);
	div = con & CLK_SARADC_DIV_CON_MASK;

	return DIV_TO_RATE(OSC_HZ, div);
}

static ulong rk1808_saradc_set_clk(struct rk1808_clk_priv *priv, uint hz)
{
	struct rk1808_cru *cru = priv->cru;
	int src_clk_div;

	src_clk_div = DIV_ROUND_UP(OSC_HZ, hz);
	assert(src_clk_div - 1 < 2047);

	rk_clrsetreg(&cru->clksel_con[63],
		     CLK_SARADC_DIV_CON_MASK,
		     (src_clk_div - 1) << CLK_SARADC_DIV_CON_SHIFT);

	return rk1808_saradc_get_clk(priv);
}

#ifndef CONFIG_SPL_BUILD
static ulong rk1808_pwm_get_clk(struct rk1808_clk_priv *priv, ulong clk_id)
{
	struct rk1808_cru *cru = priv->cru;
	u32 div, con;

	switch (clk_id) {
	case SCLK_PWM0:
		con = readl(&cru->clksel_con[69]);
		div = (con & CLK_PWM0_DIV_CON_MASK) >> CLK_PWM0_DIV_CON_SHIFT;
		break;
	case SCLK_PWM1:
		con = readl(&cru->clksel_con[69]);
		div = (con & CLK_PWM1_DIV_CON_MASK) >> CLK_PWM1_DIV_CON_SHIFT;
		break;
	case SCLK_PWM2:
		con = readl(&cru->clksel_con[70]);
		div = (con & CLK_PWM2_DIV_CON_MASK) >> CLK_PWM2_DIV_CON_SHIFT;
		break;
	default:
		printf("do not support this pwm bus\n");
		return -EINVAL;
	}

	return DIV_TO_RATE(priv->gpll_hz, div);
}

static ulong rk1808_pwm_set_clk(struct rk1808_clk_priv *priv,
				ulong clk_id, uint hz)
{
	struct rk1808_cru *cru = priv->cru;
	int src_clk_div;

	src_clk_div = DIV_ROUND_UP(priv->gpll_hz, hz);
	assert(src_clk_div - 1 < 127);

	switch (clk_id) {
	case SCLK_PWM0:
		rk_clrsetreg(&cru->clksel_con[69],
			     CLK_PWM0_DIV_CON_MASK | CLK_PWM0_PLL_SEL_MASK,
			     (src_clk_div - 1) << CLK_PWM0_DIV_CON_SHIFT |
			     CLK_PWM_PLL_SEL_GPLL << CLK_PWM0_PLL_SEL_SHIFT);
		break;
	case SCLK_PWM1:
		rk_clrsetreg(&cru->clksel_con[69],
			     CLK_PWM1_DIV_CON_MASK | CLK_PWM1_PLL_SEL_MASK,
			     (src_clk_div - 1) << CLK_PWM1_DIV_CON_SHIFT |
			     CLK_PWM_PLL_SEL_GPLL << CLK_PWM1_PLL_SEL_SHIFT);
		break;
	case SCLK_PWM2:
		rk_clrsetreg(&cru->clksel_con[70],
			     CLK_PWM2_DIV_CON_MASK | CLK_PWM2_PLL_SEL_MASK,
			     (src_clk_div - 1) << CLK_PWM2_DIV_CON_SHIFT |
			     CLK_PWM_PLL_SEL_GPLL << CLK_PWM2_PLL_SEL_SHIFT);
		break;
	default:
		printf("do not support this pwm bus\n");
		return -EINVAL;
	}

	return rk1808_pwm_get_clk(priv, clk_id);
}

static ulong rk1808_tsadc_get_clk(struct rk1808_clk_priv *priv)
{
	struct rk1808_cru *cru = priv->cru;
	u32 div, con;

	con = readl(&cru->clksel_con[62]);
	div = con & CLK_SARADC_DIV_CON_MASK;

	return DIV_TO_RATE(OSC_HZ, div);
}

static ulong rk1808_tsadc_set_clk(struct rk1808_clk_priv *priv, uint hz)
{
	struct rk1808_cru *cru = priv->cru;
	int src_clk_div;

	src_clk_div = DIV_ROUND_UP(OSC_HZ, hz);
	assert(src_clk_div - 1 < 2047);

	rk_clrsetreg(&cru->clksel_con[62],
		     CLK_SARADC_DIV_CON_MASK,
		     (src_clk_div - 1) << CLK_SARADC_DIV_CON_SHIFT);

	return rk1808_tsadc_get_clk(priv);
}

static ulong rk1808_spi_get_clk(struct rk1808_clk_priv *priv, ulong clk_id)
{
	struct rk1808_cru *cru = priv->cru;
	u32 div, con;

	switch (clk_id) {
	case SCLK_SPI0:
		con = readl(&cru->clksel_con[60]);
		div = (con & CLK_SPI0_DIV_CON_MASK) >> CLK_SPI0_DIV_CON_SHIFT;
		break;
	case SCLK_SPI1:
		con = readl(&cru->clksel_con[61]);
		div = (con & CLK_SPI1_DIV_CON_MASK) >> CLK_SPI1_DIV_CON_SHIFT;
		break;
	case SCLK_SPI2:
		con = readl(&cru->clksel_con[61]);
		div = (con & CLK_SPI2_DIV_CON_MASK) >> CLK_SPI2_DIV_CON_SHIFT;
		break;
	default:
		printf("do not support this pwm bus\n");
		return -EINVAL;
	}

	return DIV_TO_RATE(priv->gpll_hz, div);
}

static ulong rk1808_spi_set_clk(struct rk1808_clk_priv *priv,
				ulong clk_id, uint hz)
{
	struct rk1808_cru *cru = priv->cru;
	int src_clk_div;

	src_clk_div = DIV_ROUND_UP(priv->gpll_hz, hz);
	assert(src_clk_div - 1 < 127);

	switch (clk_id) {
	case SCLK_SPI0:
		rk_clrsetreg(&cru->clksel_con[60],
			     CLK_SPI0_DIV_CON_MASK | CLK_SPI0_PLL_SEL_MASK,
			     (src_clk_div - 1) << CLK_SPI0_DIV_CON_SHIFT |
			     CLK_SPI_PLL_SEL_GPLL << CLK_SPI0_PLL_SEL_SHIFT);
		break;
	case SCLK_SPI1:
		rk_clrsetreg(&cru->clksel_con[61],
			     CLK_SPI1_DIV_CON_MASK | CLK_SPI1_PLL_SEL_MASK,
			     (src_clk_div - 1) << CLK_SPI1_DIV_CON_SHIFT |
			     CLK_SPI_PLL_SEL_GPLL << CLK_SPI1_PLL_SEL_SHIFT);
		break;
	case SCLK_SPI2:
		rk_clrsetreg(&cru->clksel_con[61],
			     CLK_SPI2_DIV_CON_MASK | CLK_SPI2_PLL_SEL_MASK,
			     (src_clk_div - 1) << CLK_SPI2_DIV_CON_SHIFT |
			     CLK_SPI_PLL_SEL_GPLL << CLK_SPI2_PLL_SEL_SHIFT);
		break;
	default:
		printf("do not support this pwm bus\n");
		return -EINVAL;
	}

	return rk1808_spi_get_clk(priv, clk_id);
}

#define RK1808_VOP_PLL_LIMIT_FREQ		600 * 1000000
static ulong rk1808_vop_get_clk(struct rk1808_clk_priv *priv, ulong clk_id)
{
	struct rk1808_cru *cru = priv->cru;
	u32 div, con, parent;

	switch (clk_id) {
	case ACLK_VOPRAW:
	case ACLK_VOPLITE:
		con = readl(&cru->clksel_con[4]);
		div = (con & ACLK_VOP_DIV_CON_MASK) >> ACLK_VOP_DIV_CON_SHIFT;
		parent = priv->gpll_hz;
		break;
	case HCLK_VOPRAW:
	case HCLK_VOPLITE:
		parent = rk1808_vop_get_clk(priv, ACLK_VOPRAW);
		con = readl(&cru->clksel_con[4]);
		div = (con & HCLK_VOP_DIV_CON_MASK) >> HCLK_VOP_DIV_CON_SHIFT;
		break;
	case DCLK_VOPRAW:
		con = readl(&cru->clksel_con[5]);
		div = con & DCLK_VOPRAW_DIV_CON_MASK;
		parent = rockchip_pll_get_rate(&rk1808_pll_clks[NPLL],
					       priv->cru, NPLL);
		break;
	case DCLK_VOPLITE:
		con = readl(&cru->clksel_con[7]);
		div = con & DCLK_VOPLITE_DIV_CON_MASK;
		parent = (con & DCLK_VOPLITE_PLL_SEL_MASK) >>
			 DCLK_VOPLITE_PLL_SEL_SHIFT;
		if (parent == DCLK_VOPLITE_PLL_SEL_NPLL)
			parent = rockchip_pll_get_rate(&rk1808_pll_clks[NPLL],
						       priv->cru, NPLL);
		else if (parent == DCLK_VOPLITE_PLL_SEL_CPLL)
			parent = priv->cpll_hz;
		else
			parent = priv->gpll_hz;
		break;
	default:
		return -ENOENT;
	}

	return DIV_TO_RATE(parent, div);
}

static ulong rk1808_vop_set_clk(struct rk1808_clk_priv *priv,
				ulong clk_id, uint hz)
{
	struct rk1808_cru *cru = priv->cru;
	int src_clk_div, parent;

	src_clk_div = DIV_ROUND_UP(priv->gpll_hz, hz);
	assert(src_clk_div - 1 < 31);

	switch (clk_id) {
	case ACLK_VOPRAW:
	case ACLK_VOPLITE:
		rk_clrsetreg(&cru->clksel_con[4],
			     ACLK_VOP_PLL_SEL_MASK | ACLK_VOP_DIV_CON_MASK,
			     ACLK_VOP_PLL_SEL_GPLL << ACLK_VOP_PLL_SEL_SHIFT |
			     (src_clk_div - 1) << ACLK_VOP_DIV_CON_SHIFT);
		break;
	case HCLK_VOPRAW:
	case HCLK_VOPLITE:
		src_clk_div =
			DIV_ROUND_UP(rk1808_vop_get_clk(priv, ACLK_VOPRAW), hz);
		assert(src_clk_div - 1 < 15);
		rk_clrsetreg(&cru->clksel_con[4],
			     HCLK_VOP_DIV_CON_MASK,
			     (src_clk_div - 1) << HCLK_VOP_DIV_CON_SHIFT);
		break;
	case DCLK_VOPRAW:
		/*
		 * vopb dclk source from npll, and equals to
		 */
		src_clk_div = DIV_ROUND_UP(RK1808_VOP_PLL_LIMIT_FREQ, hz);
		rk_clrsetreg(&cru->clksel_con[5],
			     DCLK_VOPRAW_SEL_MASK |
			     DCLK_VOPRAW_PLL_SEL_MASK |
			     DCLK_VOPRAW_DIV_CON_MASK,
			     (DCLK_VOPRAW_SEL_VOPRAW <<
			     DCLK_VOPRAW_SEL_SHIFT) |
			     (DCLK_VOPRAW_PLL_SEL_NPLL <<
			     DCLK_VOPRAW_PLL_SEL_SHIFT) |
			     ((src_clk_div - 1) << DCLK_VOPRAW_DIV_CON_SHIFT));
		rockchip_pll_set_rate(&rk1808_pll_clks[NPLL],
				      priv->cru, NPLL, src_clk_div * hz);

		break;
	case DCLK_VOPLITE:
		/*
		 * vopl dclk source from cpll, and equals to
		 */
		if (!(priv->cpll_hz % hz)) {
			parent = DCLK_VOPLITE_PLL_SEL_CPLL;
			src_clk_div = DIV_ROUND_UP(priv->cpll_hz, hz);
		} else if (!(priv->gpll_hz % hz)) {
			parent = DCLK_VOPLITE_PLL_SEL_GPLL;
			src_clk_div = DIV_ROUND_UP(priv->gpll_hz, hz);
		} else {
			parent = DCLK_VOPLITE_PLL_SEL_NPLL;
			src_clk_div = DIV_ROUND_UP(RK1808_VOP_PLL_LIMIT_FREQ,
						   hz);
			rockchip_pll_set_rate(&rk1808_pll_clks[NPLL],
					      priv->cru, NPLL,
					      src_clk_div * hz);
		}
		rk_clrsetreg(&cru->clksel_con[7],
			     DCLK_VOPLITE_SEL_MASK | DCLK_VOPLITE_PLL_SEL_MASK |
			     DCLK_VOPLITE_DIV_CON_MASK,
			     (DCLK_VOPLITE_SEL_VOPRAW <<
			     DCLK_VOPLITE_SEL_SHIFT) |
			     (parent << DCLK_VOPLITE_PLL_SEL_SHIFT) |
			     ((src_clk_div - 1) << DCLK_VOPLITE_DIV_CON_SHIFT));
		break;
	default:
		printf("do not support this vop freq\n");
		return -EINVAL;
	}

	return rk1808_vop_get_clk(priv, clk_id);
}

static ulong rk1808_mac_set_clk(struct clk *clk, uint hz)
{
	struct rk1808_clk_priv *priv = dev_get_priv(clk->dev);
	struct rk1808_cru *cru = priv->cru;
	u32 con = readl(&cru->clksel_con[26]);
	ulong pll_rate;
	u8 div;

	if ((con >> GMAC_PLL_SEL_SHIFT) & GMAC_PLL_SEL_NPLL)
		pll_rate = rockchip_pll_get_rate(&rk1808_pll_clks[NPLL],
						 priv->cru, NPLL);
	else if ((con >> GMAC_PLL_SEL_SHIFT) & GMAC_PLL_SEL_PPLL)
		pll_rate = rockchip_pll_get_rate(&rk1808_pll_clks[PPLL],
						 priv->cru, PPLL);
	else
		pll_rate = rockchip_pll_get_rate(&rk1808_pll_clks[CPLL],
						 priv->cru, CPLL);

	/*default set 50MHZ for gmac*/
	if (!hz)
		hz = 50000000;

	div = DIV_ROUND_UP(pll_rate, hz) - 1;
	assert(div < 32);
	rk_clrsetreg(&cru->clksel_con[26], CLK_GMAC_DIV_MASK,
		     div << CLK_GMAC_DIV_SHIFT);

	return DIV_TO_RATE(pll_rate, div);
}

static int rk1808_mac_set_speed_clk(struct clk *clk, ulong clk_id, uint hz)
{
	struct rk1808_clk_priv *priv = dev_get_priv(clk->dev);
	struct rk1808_cru *cru = priv->cru;
	u32 sel;

	switch (clk_id) {
	case SCLK_GMAC_RGMII_SPEED:
		if (hz == 125000000)
			sel = 0;
		else if (hz == 2500000)
			sel = 2;
		else
			sel = 3;
		rk_clrsetreg(&cru->clksel_con[27], RGMII_CLK_SEL_MASK,
			     sel << RGMII_CLK_SEL_SHIFT);
		break;
	case SCLK_GMAC_RMII_SPEED:
		if (hz == 2500000)
			sel = 0;
		else
			sel = 1;
		rk_clrsetreg(&cru->clksel_con[27], RMII_CLK_SEL_MASK,
			     sel << RMII_CLK_SEL_SHIFT);
		break;
	default:
		return -ENOENT;
	}
	return 0;
}

static ulong rk1808_crypto_get_clk(struct rk1808_clk_priv *priv, ulong clk_id)
{
	struct rk1808_cru *cru = priv->cru;
	u32 div, con, parent;

	switch (clk_id) {
	case SCLK_CRYPTO:
		con = readl(&cru->clksel_con[29]);
		div = (con & CRYPTO_DIV_MASK) >> CRYPTO_DIV_SHIFT;
		parent = priv->gpll_hz;
		break;
	case SCLK_CRYPTO_APK:
		con = readl(&cru->clksel_con[29]);
		div = (con & CRYPTO_APK_DIV_MASK) >> CRYPTO_APK_DIV_SHIFT;
		parent = priv->gpll_hz;
		break;
	default:
		return -ENOENT;
	}

	return DIV_TO_RATE(parent, div);
}

static ulong rk1808_crypto_set_clk(struct rk1808_clk_priv *priv, ulong clk_id,
				   ulong hz)
{
	struct rk1808_cru *cru = priv->cru;
	int src_clk_div;

	src_clk_div = DIV_ROUND_UP(priv->gpll_hz, hz);
	assert(src_clk_div - 1 <= 31);

	/*
	 * select gpll as crypto clock source and
	 * set up dependent divisors for crypto clocks.
	 */
	switch (clk_id) {
	case SCLK_CRYPTO:
		rk_clrsetreg(&cru->clksel_con[29],
			     CRYPTO_PLL_SEL_MASK | CRYPTO_DIV_MASK,
			     CRYPTO_PLL_SEL_GPLL << CRYPTO_PLL_SEL_SHIFT |
			     (src_clk_div - 1) << CRYPTO_DIV_SHIFT);
		break;
	case SCLK_CRYPTO_APK:
		rk_clrsetreg(&cru->clksel_con[29],
			     CRYPTO_APK_PLL_SEL_MASK | CRYPTO_APK_DIV_MASK,
			     CRYPTO_PLL_SEL_GPLL << CRYPTO_APK_SEL_SHIFT |
			     (src_clk_div - 1) << CRYPTO_APK_DIV_SHIFT);
		break;
	default:
		printf("do not support this peri freq\n");
		return -EINVAL;
	}

	return rk1808_crypto_get_clk(priv, clk_id);
}
#endif

static ulong rk1808_bus_get_clk(struct rk1808_clk_priv *priv, ulong clk_id)
{
	struct rk1808_cru *cru = priv->cru;
	u32 div, con, parent;

	switch (clk_id) {
	case HSCLK_BUS_PRE:
		con = readl(&cru->clksel_con[27]);
		div = (con & HSCLK_BUS_DIV_CON_MASK) >> HSCLK_BUS_DIV_CON_SHIFT;
		parent = priv->gpll_hz;
		break;
	case MSCLK_BUS_PRE:
		con = readl(&cru->clksel_con[28]);
		div = (con & MSCLK_BUS_DIV_CON_MASK) >> MSCLK_BUS_DIV_CON_SHIFT;
		parent = priv->gpll_hz;
		break;
	case LSCLK_BUS_PRE:
	case PCLK_WDT:
		con = readl(&cru->clksel_con[28]);
		div = (con & LSCLK_BUS_DIV_CON_MASK) >> LSCLK_BUS_DIV_CON_SHIFT;
		parent = priv->gpll_hz;
		break;
	default:
		return -ENOENT;
	}

	return DIV_TO_RATE(parent, div);
}

static ulong rk1808_bus_set_clk(struct rk1808_clk_priv *priv,
				ulong clk_id, ulong hz)
{
	struct rk1808_cru *cru = priv->cru;
	int src_clk_div;

	/*
	 * select gpll as pd_bus bus clock source and
	 * set up dependent divisors for PCLK/HCLK and ACLK clocks.
	 */
	switch (clk_id) {
	case HSCLK_BUS_PRE:
		src_clk_div = DIV_ROUND_UP(priv->gpll_hz, hz);
		assert(src_clk_div - 1 < 31);
		rk_clrsetreg(&cru->clksel_con[27],
			     CLK_BUS_PLL_SEL_MASK | HSCLK_BUS_DIV_CON_MASK,
			     CLK_BUS_PLL_SEL_GPLL << CLK_BUS_PLL_SEL_SHIFT |
			     (src_clk_div - 1) << HSCLK_BUS_DIV_CON_SHIFT);
		break;
	case MSCLK_BUS_PRE:
		src_clk_div = DIV_ROUND_UP(priv->gpll_hz, hz);
		assert(src_clk_div - 1 < 31);
		rk_clrsetreg(&cru->clksel_con[28],
			     CLK_BUS_PLL_SEL_MASK | MSCLK_BUS_DIV_CON_MASK,
			     CLK_BUS_PLL_SEL_GPLL << CLK_BUS_PLL_SEL_SHIFT |
			     (src_clk_div - 1) << MSCLK_BUS_DIV_CON_SHIFT);
		break;
	case LSCLK_BUS_PRE:
		src_clk_div = DIV_ROUND_UP(priv->gpll_hz, hz);
		assert(src_clk_div - 1 < 31);
		rk_clrsetreg(&cru->clksel_con[28],
			     CLK_BUS_PLL_SEL_MASK | LSCLK_BUS_DIV_CON_MASK,
			     CLK_BUS_PLL_SEL_GPLL << CLK_BUS_PLL_SEL_SHIFT |
			     (src_clk_div - 1) << LSCLK_BUS_DIV_CON_SHIFT);
		break;
	default:
		printf("do not support this bus freq\n");
		return -EINVAL;
	}

	return rk1808_bus_get_clk(priv, clk_id);
}

static ulong rk1808_peri_get_clk(struct rk1808_clk_priv *priv, ulong clk_id)
{
	struct rk1808_cru *cru = priv->cru;
	u32 div, con, parent;

	switch (clk_id) {
	case MSCLK_PERI:
		con = readl(&cru->clksel_con[19]);
		div = (con & MSCLK_PERI_DIV_CON_MASK) >>
		      MSCLK_PERI_DIV_CON_SHIFT;
		parent = priv->gpll_hz;
		break;
	case LSCLK_PERI:
		con = readl(&cru->clksel_con[19]);
		div = (con & LSCLK_PERI_DIV_CON_MASK) >>
		      LSCLK_PERI_DIV_CON_SHIFT;
		parent = priv->gpll_hz;
		break;
	default:
		return -ENOENT;
	}

	return DIV_TO_RATE(parent, div);
}

static ulong rk1808_peri_set_clk(struct rk1808_clk_priv *priv,
				 ulong clk_id, ulong hz)
{
	struct rk1808_cru *cru = priv->cru;
	int src_clk_div;

	src_clk_div = DIV_ROUND_UP(priv->gpll_hz, hz);
	assert(src_clk_div - 1 < 31);

	/*
	 * select gpll as pd_peri bus clock source and
	 * set up dependent divisors for HCLK and ACLK clocks.
	 */
	switch (clk_id) {
	case MSCLK_PERI:
		rk_clrsetreg(&cru->clksel_con[19],
			     CLK_PERI_PLL_SEL_MASK | MSCLK_PERI_DIV_CON_MASK,
			     CLK_PERI_PLL_SEL_GPLL << CLK_PERI_PLL_SEL_SHIFT |
			     (src_clk_div - 1) << MSCLK_PERI_DIV_CON_SHIFT);
		break;
	case LSCLK_PERI:
		rk_clrsetreg(&cru->clksel_con[19],
			     CLK_PERI_PLL_SEL_MASK | LSCLK_PERI_DIV_CON_MASK,
			     CLK_PERI_PLL_SEL_GPLL << CLK_PERI_PLL_SEL_SHIFT |
			     (src_clk_div - 1) << LSCLK_PERI_DIV_CON_SHIFT);
		break;
	default:
		printf("do not support this peri freq\n");
		return -EINVAL;
	}

	return rk1808_peri_get_clk(priv, clk_id);
}

static ulong rk1808_pclk_pmu_set_clk(struct rk1808_clk_priv *priv,
				     ulong clk_id, ulong parent_hz, ulong hz)
{
	struct rk1808_cru *cru = priv->cru;
	int src_clk_div;

	src_clk_div = DIV_ROUND_UP(parent_hz, hz);
	assert(src_clk_div - 1 < 31);

	rk_clrsetreg(&cru->pmu_clksel_con[0],
		     PCLK_PMU_DIV_CON_MASK,
		     (src_clk_div - 1) << PCLK_PMU_DIV_CON_SHIFT);

	return parent_hz / src_clk_div;
}

static ulong rk1808_armclk_set_clk(struct rk1808_clk_priv *priv, ulong hz)
{
	struct rk1808_cru *cru = priv->cru;
	const struct rockchip_cpu_rate_table *rate;
	ulong old_rate;

	rate = rockchip_get_cpu_settings(rk1808_cpu_rates, hz);
	if (!rate) {
		printf("%s unsupported rate\n", __func__);
		return -EINVAL;
	}

	/*
	 * select apll as cpu/core clock pll source and
	 * set up dependent divisors for PERI and ACLK clocks.
	 * core hz : apll = 1:1
	 */
	old_rate = rockchip_pll_get_rate(&rk1808_pll_clks[APLL],
					 priv->cru, APLL);
	if (old_rate > hz) {
		if (rockchip_pll_set_rate(&rk1808_pll_clks[APLL],
					  priv->cru, APLL, hz))
			return -EINVAL;
		rk_clrsetreg(&cru->clksel_con[0],
			     CORE_CLK_PLL_SEL_MASK | CORE_DIV_CON_MASK |
			     CORE_ACLK_DIV_MASK | CORE_DBG_DIV_MASK,
			     rate->aclk_div << CORE_ACLK_DIV_SHIFT |
			     rate->pclk_div << CORE_DBG_DIV_SHIFT |
			     CORE_CLK_PLL_SEL_APLL << CORE_CLK_PLL_SEL_SHIFT |
			     0 << CORE_DIV_CON_SHIFT);
	} else if (old_rate < hz) {
		rk_clrsetreg(&cru->clksel_con[0],
			     CORE_CLK_PLL_SEL_MASK | CORE_DIV_CON_MASK |
			     CORE_ACLK_DIV_MASK | CORE_DBG_DIV_MASK,
			     rate->aclk_div << CORE_ACLK_DIV_SHIFT |
			     rate->pclk_div << CORE_DBG_DIV_SHIFT |
			     CORE_CLK_PLL_SEL_APLL << CORE_CLK_PLL_SEL_SHIFT |
			     0 << CORE_DIV_CON_SHIFT);
		if (rockchip_pll_set_rate(&rk1808_pll_clks[APLL],
					  priv->cru, APLL, hz))
			return -EINVAL;
	}

	return rockchip_pll_get_rate(&rk1808_pll_clks[APLL], priv->cru, APLL);
}

static ulong rk1808_clk_get_rate(struct clk *clk)
{
	struct rk1808_clk_priv *priv = dev_get_priv(clk->dev);
	ulong rate = 0;

	debug("%s %ld\n", __func__, clk->id);
	switch (clk->id) {
	case PLL_APLL:
	case PLL_DPLL:
	case PLL_CPLL:
	case PLL_GPLL:
	case PLL_NPLL:
	case PLL_PPLL:
		rate = rockchip_pll_get_rate(&rk1808_pll_clks[clk->id - 1],
					     priv->cru, clk->id - 1);
		break;
	case ARMCLK:
		rate = rockchip_pll_get_rate(&rk1808_pll_clks[APLL],
					     priv->cru, APLL);
		break;
	case HCLK_SDMMC:
	case HCLK_EMMC:
	case HCLK_SDIO:
	case SCLK_SDMMC:
	case SCLK_EMMC:
	case SCLK_EMMC_SAMPLE:
	case SCLK_SDIO:
		rate = rk1808_mmc_get_clk(priv, clk->id);
		break;
	case SCLK_SFC:
		rate = rk1808_sfc_get_clk(priv, clk->id);
		break;
	case SCLK_SARADC:
		rate = rk1808_saradc_get_clk(priv);
		break;
#ifndef CONFIG_SPL_BUILD
	case SCLK_PMU_I2C0:
	case SCLK_I2C1:
	case SCLK_I2C2:
	case SCLK_I2C3:
	case SCLK_I2C4:
	case SCLK_I2C5:
		rate = rk1808_i2c_get_clk(priv, clk->id);
		break;
	case SCLK_PWM0:
	case SCLK_PWM1:
	case SCLK_PWM2:
		rate = rk1808_pwm_get_clk(priv, clk->id);
		break;
	case SCLK_TSADC:
		rate = rk1808_tsadc_get_clk(priv);
		break;
	case SCLK_SPI0:
	case SCLK_SPI1:
	case SCLK_SPI2:
		rate = rk1808_spi_get_clk(priv, clk->id);
		break;
	case ACLK_VOPRAW:
	case DCLK_VOPRAW:
	case ACLK_VOPLITE:
	case DCLK_VOPLITE:
		rate = rk1808_vop_get_clk(priv, clk->id);
		break;
	case SCLK_CRYPTO:
	case SCLK_CRYPTO_APK:
		rate = rk1808_crypto_get_clk(priv, clk->id);
		break;
#endif
	case HSCLK_BUS_PRE:
	case MSCLK_BUS_PRE:
	case LSCLK_BUS_PRE:
	case PCLK_WDT:
		rate = rk1808_bus_get_clk(priv, clk->id);
		break;
	case MSCLK_PERI:
	case LSCLK_PERI:
		rate = rk1808_peri_get_clk(priv, clk->id);
		break;
	default:
		return -ENOENT;
	}

	return rate;
}

static ulong rk1808_clk_set_rate(struct clk *clk, ulong rate)
{
	struct rk1808_clk_priv *priv = dev_get_priv(clk->dev);
	ulong ret = 0;

	debug("%s %ld %ld\n", __func__, clk->id, rate);
	switch (clk->id) {
	case PLL_APLL:
	case PLL_DPLL:
		ret = rockchip_pll_set_rate(&rk1808_pll_clks[clk->id - 1],
					    priv->cru, clk->id - 1, rate);
		break;
	case PLL_PPLL:
		ret = rk1808_pclk_pmu_set_clk(priv, clk->id, rate, PCLK_PMU_HZ);
		ret = rockchip_pll_set_rate(&rk1808_pll_clks[PPLL],
					    priv->cru, PPLL, rate);
		break;
	case PLL_CPLL:
		ret = rockchip_pll_set_rate(&rk1808_pll_clks[CPLL],
					    priv->cru, CPLL, rate);
		if (ret == 0)
			priv->cpll_hz = rate;
		break;
	case PLL_GPLL:
		ret = rockchip_pll_set_rate(&rk1808_pll_clks[GPLL],
					    priv->cru, GPLL, rate);
		if (ret == 0)
			priv->gpll_hz = rate;
		break;
	case PLL_NPLL:
		ret = rockchip_pll_set_rate(&rk1808_pll_clks[NPLL],
					    priv->cru, NPLL, rate);
		if (ret == 0)
			priv->npll_hz = rate;
		break;
	case ARMCLK:
		if (priv->armclk_hz)
			rk1808_armclk_set_clk(priv, rate);
		priv->armclk_hz = rate;
		break;
	case HCLK_SDMMC:
	case HCLK_EMMC:
	case HCLK_SDIO:
	case SCLK_SDMMC:
	case SCLK_EMMC:
	case SCLK_SDIO:
		ret = rk1808_mmc_set_clk(priv, clk->id, rate);
		break;
	case SCLK_SFC:
		ret = rk1808_sfc_set_clk(priv, clk->id, rate);
		break;
	case SCLK_SARADC:
		ret = rk1808_saradc_set_clk(priv, rate);
		break;
#ifndef CONFIG_SPL_BUILD
	case SCLK_PMU_I2C0:
	case SCLK_I2C1:
	case SCLK_I2C2:
	case SCLK_I2C3:
	case SCLK_I2C4:
	case SCLK_I2C5:
		ret = rk1808_i2c_set_clk(priv, clk->id, rate);
		break;
	case SCLK_PWM0:
	case SCLK_PWM1:
	case SCLK_PWM2:
		ret = rk1808_pwm_set_clk(priv, clk->id, rate);
		break;
	case SCLK_TSADC:
		ret = rk1808_tsadc_set_clk(priv, rate);
		break;
	case SCLK_SPI0:
	case SCLK_SPI1:
	case SCLK_SPI2:
		ret = rk1808_spi_set_clk(priv, clk->id, rate);
		break;
	case ACLK_VOPRAW:
	case DCLK_VOPRAW:
	case ACLK_VOPLITE:
	case DCLK_VOPLITE:
		ret = rk1808_vop_set_clk(priv, clk->id, rate);
		break;
	case SCLK_GMAC:
	case SCLK_GMAC_SRC:
		ret = rk1808_mac_set_clk(clk, rate);
		break;
	case SCLK_GMAC_RMII_SPEED:
	case SCLK_GMAC_RGMII_SPEED:
		ret = rk1808_mac_set_speed_clk(clk, clk->id, rate);
		break;
	case SCLK_CRYPTO:
	case SCLK_CRYPTO_APK:
		ret = rk1808_crypto_set_clk(priv, clk->id, rate);
		break;
#endif
	case HSCLK_BUS_PRE:
	case MSCLK_BUS_PRE:
	case LSCLK_BUS_PRE:
		ret = rk1808_bus_set_clk(priv, clk->id, rate);
		break;
	case MSCLK_PERI:
	case LSCLK_PERI:
		ret = rk1808_peri_set_clk(priv, clk->id, rate);
		break;
	case SCLK_32K_IOE:
		return 0;
	default:
		return -ENOENT;
	}

	return ret;
}

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

int rk1808_mmc_get_phase(struct clk *clk)
{
	struct rk1808_clk_priv *priv = dev_get_priv(clk->dev);
	struct rk1808_cru *cru = priv->cru;
	u32 raw_value, delay_num;
	u16 degrees = 0;
	ulong rate;

	rate = rk1808_clk_get_rate(clk);

	if (rate < 0)
		return rate;

	if (clk->id == SCLK_EMMC_SAMPLE)
		raw_value = readl(&cru->emmc_con[1]);
	else if (clk->id == SCLK_SDMMC_SAMPLE)
		raw_value = readl(&cru->sdmmc_con[1]);
	else
		raw_value = readl(&cru->sdio_con[1]);

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

int rk1808_mmc_set_phase(struct clk *clk, u32 degrees)
{
	struct rk1808_clk_priv *priv = dev_get_priv(clk->dev);
	struct rk1808_cru *cru = priv->cru;
	u8 nineties, remainder, delay_num;
	u32 raw_value, delay;
	ulong rate;

	rate = rk1808_clk_get_rate(clk);

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
		writel(raw_value | 0xffff0000, &cru->emmc_con[1]);
	else if (clk->id == SCLK_SDMMC_SAMPLE)
		writel(raw_value | 0xffff0000, &cru->sdmmc_con[1]);
	else
		writel(raw_value | 0xffff0000, &cru->sdio_con[1]);

	debug("mmc set_phase(%d) delay_nums=%u reg=%#x actual_degrees=%d\n",
	      degrees, delay_num, raw_value, rk1808_mmc_get_phase(clk));

	return 0;
}

static int rk1808_clk_get_phase(struct clk *clk)
{
	int ret;

	debug("%s %ld\n", __func__, clk->id);
	switch (clk->id) {
	case SCLK_EMMC_SAMPLE:
	case SCLK_SDMMC_SAMPLE:
	case SCLK_SDIO_SAMPLE:
		ret = rk1808_mmc_get_phase(clk);
		break;
	default:
		return -ENOENT;
	}

	return ret;
}

static int rk1808_clk_set_phase(struct clk *clk, int degrees)
{
	int ret;

	debug("%s %ld\n", __func__, clk->id);
	switch (clk->id) {
	case SCLK_EMMC_SAMPLE:
	case SCLK_SDMMC_SAMPLE:
	case SCLK_SDIO_SAMPLE:
		ret = rk1808_mmc_set_phase(clk, degrees);
		break;
	default:
		return -ENOENT;
	}

	return ret;
}

#if CONFIG_IS_ENABLED(OF_CONTROL) && !CONFIG_IS_ENABLED(OF_PLATDATA)
static int rk1808_gmac_set_parent(struct clk *clk, struct clk *parent)
{
	struct rk1808_clk_priv *priv = dev_get_priv(clk->dev);
	struct rk1808_cru *cru = priv->cru;

	if (parent->id == SCLK_GMAC_SRC) {
		debug("%s: switching GAMC to SCLK_GMAC_SRC\n", __func__);
		rk_clrsetreg(&cru->clksel_con[27], RMII_EXTCLK_SEL_MASK,
			     RMII_EXTCLK_SEL_INT << RMII_EXTCLK_SEL_SHIFT);
	} else {
		debug("%s: switching GMAC to external clock\n", __func__);
		rk_clrsetreg(&cru->clksel_con[27], RMII_EXTCLK_SEL_MASK,
			     RMII_EXTCLK_SEL_EXT << RMII_EXTCLK_SEL_SHIFT);
	}
	return 0;
}

static int rk1808_clk_set_parent(struct clk *clk, struct clk *parent)
{
	switch (clk->id) {
	case SCLK_GMAC:
		return rk1808_gmac_set_parent(clk, parent);
	case SCLK_32K_IOE:
		return 0;
	default:
		return -ENOENT;
	}
}
#endif

static struct clk_ops rk1808_clk_ops = {
	.get_rate = rk1808_clk_get_rate,
	.set_rate = rk1808_clk_set_rate,
	.get_phase	= rk1808_clk_get_phase,
	.set_phase	= rk1808_clk_set_phase,
#if CONFIG_IS_ENABLED(OF_CONTROL) && !CONFIG_IS_ENABLED(OF_PLATDATA)
	.set_parent	= rk1808_clk_set_parent,
#endif
};

static int rk1808_clk_probe(struct udevice *dev)
{
	struct rk1808_clk_priv *priv = dev_get_priv(dev);
	int ret;
#ifndef CONFIG_SPL_BUILD
	ulong crypto_rate, crypto_apk_rate;
	ulong emmc_rate, sdmmc_rate, sfc_rate;
#endif

	priv->sync_kernel = false;
	if (!priv->armclk_enter_hz) {
		priv->armclk_enter_hz =
		rockchip_pll_get_rate(&rk1808_pll_clks[APLL],
				      priv->cru, APLL);
		priv->armclk_init_hz = priv->armclk_enter_hz;
	}
	if (rockchip_pll_get_rate(&rk1808_pll_clks[APLL],
				  priv->cru, APLL) != APLL_HZ) {
		ret = rk1808_armclk_set_clk(priv, APLL_HZ);
		if (ret < 0)
			printf("%s failed to set armclk rate\n", __func__);
		priv->armclk_init_hz = APLL_HZ;
	}
#ifdef CONFIG_SPL_BUILD
	/*
	 * The eMMC clk is depended on gpll, and the eMMC is needed to
	 * run 150MHz in HS200 mode. So set gpll to GPLL_HZ(594000000)
	 * which can be divided near to 150MHz.
	 */
	ret = rockchip_pll_set_rate(&rk1808_pll_clks[GPLL],
				    priv->cru, GPLL, GPLL_HZ);
	if (ret < 0)
		printf("%s failed to set gpll rate\n", __func__);
#endif
	priv->cpll_hz = rockchip_pll_get_rate(&rk1808_pll_clks[CPLL],
					      priv->cru, CPLL);
	priv->gpll_hz = rockchip_pll_get_rate(&rk1808_pll_clks[GPLL],
					      priv->cru, GPLL);
	priv->npll_hz = rockchip_pll_get_rate(&rk1808_pll_clks[NPLL],
					      priv->cru, NPLL);

#ifndef CONFIG_SPL_BUILD
	crypto_rate = rk1808_crypto_get_clk(priv, SCLK_CRYPTO);
	crypto_apk_rate = rk1808_crypto_get_clk(priv, SCLK_CRYPTO_APK);
	emmc_rate = rk1808_mmc_get_clk(priv, SCLK_EMMC);
	sdmmc_rate = rk1808_mmc_get_clk(priv, SCLK_SDMMC);
	sfc_rate = rk1808_sfc_get_clk(priv, SCLK_SFC);
#endif

	/* Process 'assigned-{clocks/clock-parents/clock-rates}' properties */
	ret = clk_set_defaults(dev);
	if (ret)
		debug("%s clk_set_defaults failed %d\n", __func__, ret);
	else
		priv->sync_kernel = true;

#ifndef CONFIG_SPL_BUILD
	rk1808_crypto_set_clk(priv, SCLK_CRYPTO, crypto_rate);
	rk1808_crypto_set_clk(priv, SCLK_CRYPTO_APK, crypto_apk_rate);
	rk1808_mmc_set_clk(priv, SCLK_EMMC, emmc_rate);
	rk1808_mmc_set_clk(priv, SCLK_SDMMC, sdmmc_rate);
	rk1808_sfc_set_clk(priv, SCLK_SFC, sfc_rate);
#endif

	return 0;
}

static int rk1808_clk_ofdata_to_platdata(struct udevice *dev)
{
	struct rk1808_clk_priv *priv = dev_get_priv(dev);

	priv->cru = dev_read_addr_ptr(dev);

	return 0;
}

static int rk1808_clk_bind(struct udevice *dev)
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
		priv->glb_srst_fst_value = offsetof(struct rk1808_cru,
						    glb_srst_fst);
		priv->glb_srst_snd_value = offsetof(struct rk1808_cru,
						    glb_srst_snd);
		sys_child->priv = priv;
	}

	ret = device_bind_driver_to_node(dev, "rockchip_reset", "reset",
					 dev_ofnode(dev), &sf_child);
	if (ret) {
		debug("Warning: No rockchip reset driver: ret=%d\n", ret);
	} else {
		sf_priv = malloc(sizeof(struct softreset_reg));
		sf_priv->sf_reset_offset = offsetof(struct rk1808_cru,
						    softrst_con[0]);
		sf_priv->sf_reset_num = 16;
		sf_child->priv = sf_priv;
	}

	return 0;
}

static const struct udevice_id rk1808_clk_ids[] = {
	{ .compatible = "rockchip,rk1808-cru" },
	{ }
};

U_BOOT_DRIVER(rockchip_rk1808_cru) = {
	.name		= "rockchip_rk1808_cru",
	.id		= UCLASS_CLK,
	.of_match	= rk1808_clk_ids,
	.priv_auto_alloc_size = sizeof(struct rk1808_clk_priv),
	.ofdata_to_platdata = rk1808_clk_ofdata_to_platdata,
	.ops		= &rk1808_clk_ops,
	.bind		= rk1808_clk_bind,
	.probe		= rk1808_clk_probe,
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
	struct rk1808_clk_priv *priv;
	const struct rk1808_clk_info *clk_dump;
	struct clk clk;
	unsigned long clk_count = ARRAY_SIZE(clks_dump);
	unsigned long rate;
	int i, ret;

	ret = uclass_get_device_by_driver(UCLASS_CLK,
					  DM_GET_DRIVER(rockchip_rk1808_cru),
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
