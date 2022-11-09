/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:	GPL-2.0
 */

#include <common.h>
#include <clk-uclass.h>
#include <dm.h>
#include <errno.h>
#include <syscon.h>
#include <asm/io.h>
#include <asm/arch-rockchip/clock.h>
#include <asm/arch-rockchip/cru_rk3128.h>
#include <asm/arch-rockchip/hardware.h>
#include <bitfield.h>
#include <dm/lists.h>
#include <dt-bindings/clock/rk3128-cru.h>
#include <linux/log2.h>

DECLARE_GLOBAL_DATA_PTR;

#define DIV_TO_RATE(input_rate, div)	((input_rate) / ((div) + 1))

#ifndef CONFIG_SPL_BUILD
#define RK3128_CLK_DUMP(_id, _name, _iscru)	\
{						\
	.id = _id,				\
	.name = _name,				\
	.is_cru = _iscru,			\
}
#endif

static struct rockchip_pll_rate_table rk3128_pll_rates[] = {
	/* _mhz, _refdiv, _fbdiv, _postdiv1, _postdiv2, _dsmpd, _frac */
#ifndef CONFIG_SPL_BUILD
	RK3036_PLL_RATE(1200000000, 1, 50, 1, 1, 1, 0),
	RK3036_PLL_RATE(1188000000, 1, 99, 2, 1, 1, 0),
	RK3036_PLL_RATE(1008000000, 1, 84, 2, 1, 1, 0),
#endif
	RK3036_PLL_RATE(816000000, 1, 68, 2, 1, 1, 0),
	RK3036_PLL_RATE(800000000, 1, 200, 6, 1, 1, 0),
	RK3036_PLL_RATE(600000000, 1, 75, 3, 1, 1, 0),
	RK3036_PLL_RATE(594000000, 1, 99, 4, 1, 1, 0),
	RK3036_PLL_RATE(500000000, 1, 125, 6, 1, 1, 0),
	RK3036_PLL_RATE(400000000, 1, 100, 6, 1, 1, 0),
	{ /* sentinel */ },
};

#define RK3128_CPUCLK_RATE(_rate, _aclk_div, _pclk_div)		\
{								\
	.rate	= _rate##U,					\
	.aclk_div = _aclk_div,					\
	.pclk_div = _pclk_div,					\
}

static struct rockchip_cpu_rate_table rk3128_cpu_rates[] = {
	RK3128_CPUCLK_RATE(1200000000, 1, 5),
	RK3128_CPUCLK_RATE(1008000000, 1, 5),
	RK3128_CPUCLK_RATE(816000000, 1, 3),
	RK3128_CPUCLK_RATE(600000000, 1, 3),
};

#ifndef CONFIG_SPL_BUILD
static const struct rk3128_clk_info clks_dump[] = {
	RK3128_CLK_DUMP(PLL_APLL, "apll", true),
	RK3128_CLK_DUMP(PLL_DPLL, "dpll", true),
	RK3128_CLK_DUMP(PLL_CPLL, "cpll", true),
	RK3128_CLK_DUMP(PLL_GPLL, "gpll", true),
	RK3128_CLK_DUMP(ARMCLK, "armclk", true),
	RK3128_CLK_DUMP(ACLK_CPU, "aclk_cpu", true),
	RK3128_CLK_DUMP(HCLK_CPU, "hclk_cpu", true),
	RK3128_CLK_DUMP(PCLK_CPU, "pclk_cpu", true),
	RK3128_CLK_DUMP(ACLK_PERI, "aclk_peri", true),
	RK3128_CLK_DUMP(HCLK_PERI, "hclk_peri", true),
	RK3128_CLK_DUMP(PCLK_PERI, "pclk_peri", true),
};
#endif

static struct rockchip_pll_clock rk3128_pll_clks[] = {
	[APLL] = PLL(pll_rk3036, PLL_APLL, RK2928_PLL_CON(0),
		     RK2928_MODE_CON, 0, 10, 0, rk3128_pll_rates),
	[DPLL] = PLL(pll_rk3036, PLL_DPLL, RK2928_PLL_CON(4),
		     RK2928_MODE_CON, 4, 10, 0, NULL),
	[CPLL] = PLL(pll_rk3036, PLL_CPLL, RK2928_PLL_CON(8),
		    RK2928_MODE_CON, 8, 10, 0, rk3128_pll_rates),
	[GPLL] = PLL(pll_rk3036, PLL_GPLL, RK2928_PLL_CON(12),
		     RK2928_MODE_CON, 12, 10, 0, rk3128_pll_rates),
};

static ulong rk3128_armclk_set_clk(struct rk3128_clk_priv *priv, ulong hz)
{
	struct rk3128_cru *cru = priv->cru;
	const struct rockchip_cpu_rate_table *rate;
	ulong old_rate;

	rate = rockchip_get_cpu_settings(rk3128_cpu_rates, hz);
	if (!rate) {
		printf("%s unsupported rate\n", __func__);
		return -EINVAL;
	}

	/*
	 * select apll as cpu/core clock pll source and
	 * set up dependent divisors for PERI and ACLK clocks.
	 * core hz : apll = 1:1
	 */
	old_rate = rockchip_pll_get_rate(&rk3128_pll_clks[APLL],
					 priv->cru, APLL);
	if (old_rate > hz) {
		if (rockchip_pll_set_rate(&rk3128_pll_clks[APLL],
					  priv->cru, APLL, hz))
			return -EINVAL;
		rk_clrsetreg(&cru->cru_clksel_con[0],
			     CORE_CLK_PLL_SEL_MASK | CORE_DIV_CON_MASK,
			     CORE_CLK_PLL_SEL_APLL << CORE_CLK_PLL_SEL_SHIFT |
			     0 << CORE_DIV_CON_SHIFT);
		rk_clrsetreg(&cru->cru_clksel_con[1],
			     CORE_ACLK_DIV_MASK | CORE_DBG_DIV_MASK,
			     rate->aclk_div << CORE_ACLK_DIV_SHIFT |
			     rate->pclk_div << CORE_DBG_DIV_SHIFT);
	} else if (old_rate < hz) {
		rk_clrsetreg(&cru->cru_clksel_con[1],
			     CORE_ACLK_DIV_MASK | CORE_DBG_DIV_MASK,
			     rate->aclk_div << CORE_ACLK_DIV_SHIFT |
			     rate->pclk_div << CORE_DBG_DIV_SHIFT);
		rk_clrsetreg(&cru->cru_clksel_con[0],
			     CORE_CLK_PLL_SEL_MASK | CORE_DIV_CON_MASK,
			     CORE_CLK_PLL_SEL_APLL << CORE_CLK_PLL_SEL_SHIFT |
			     0 << CORE_DIV_CON_SHIFT);
		if (rockchip_pll_set_rate(&rk3128_pll_clks[APLL],
					  priv->cru, APLL, hz))
			return -EINVAL;
	}

	return rockchip_pll_get_rate(&rk3128_pll_clks[APLL], priv->cru, APLL);
}

static ulong rockchip_mmc_get_clk(struct rk3128_clk_priv *priv,
				  int periph)
{
	struct rk3128_cru *cru = priv->cru;
	uint src_rate;
	uint div, mux;
	u32 con;

	switch (periph) {
	case HCLK_EMMC:
	case SCLK_EMMC:
	case SCLK_EMMC_SAMPLE:
		con = readl(&cru->cru_clksel_con[12]);
		mux = (con & EMMC_PLL_MASK) >> EMMC_PLL_SHIFT;
		div = (con & EMMC_DIV_MASK) >> EMMC_DIV_SHIFT;
		break;
	case HCLK_SDMMC:
	case SCLK_SDMMC:
	case SCLK_SDMMC_SAMPLE:
		con = readl(&cru->cru_clksel_con[11]);
		mux = (con & MMC0_PLL_MASK) >> MMC0_PLL_SHIFT;
		div = (con & MMC0_DIV_MASK) >> MMC0_DIV_SHIFT;
		break;
	case HCLK_SDIO:
	case SCLK_SDIO:
	case SCLK_SDIO_SAMPLE:
		con = readl(&cru->cru_clksel_con[12]);
		mux = (con & SDIO_PLL_MASK) >> SDIO_PLL_SHIFT;
		div = (con & SDIO_DIV_MASK) >> SDIO_DIV_SHIFT;
		break;
	default:
		return -EINVAL;
	}

	src_rate = mux == EMMC_SEL_24M ? OSC_HZ : priv->gpll_hz;
	return DIV_TO_RATE(src_rate, div);
}

static ulong rockchip_mmc_set_clk(struct rk3128_clk_priv *priv,
				  int periph, uint freq)
{
	struct rk3128_cru *cru = priv->cru;
	int src_clk_div;
	int mux;

	/* mmc clock defaulg div 2 internal, need provide double in cru */
	src_clk_div = DIV_ROUND_UP(priv->gpll_hz / 2, freq);

	if (src_clk_div > 128) {
		src_clk_div = DIV_ROUND_UP(OSC_HZ / 2, freq);
		mux = EMMC_SEL_24M;
	} else {
		mux = EMMC_SEL_GPLL;
	}

	switch (periph) {
	case HCLK_EMMC:
	case SCLK_EMMC:
		rk_clrsetreg(&cru->cru_clksel_con[12],
			     EMMC_PLL_MASK | EMMC_DIV_MASK,
			     mux << EMMC_PLL_SHIFT |
			     (src_clk_div - 1) << EMMC_DIV_SHIFT);
		break;
	case HCLK_SDMMC:
	case SCLK_SDMMC:
		rk_clrsetreg(&cru->cru_clksel_con[11],
			     MMC0_PLL_MASK | MMC0_DIV_MASK,
			     mux << MMC0_PLL_SHIFT |
			     (src_clk_div - 1) << MMC0_DIV_SHIFT);
		break;
	case HCLK_SDIO:
	case SCLK_SDIO:
		rk_clrsetreg(&cru->cru_clksel_con[12],
			     SDIO_PLL_MASK | SDIO_DIV_MASK,
			     mux << SDIO_PLL_SHIFT |
			     (src_clk_div - 1) << SDIO_DIV_SHIFT);
		break;
	default:
		return -EINVAL;
	}

	return rockchip_mmc_get_clk(priv, periph);
}

static ulong rk3128_peri_get_clk(struct rk3128_clk_priv *priv, ulong clk_id)
{
	struct rk3128_cru *cru = priv->cru;
	u32 div, con, parent;

	switch (clk_id) {
	case ACLK_PERI:
		con = readl(&cru->cru_clksel_con[10]);
		div = (con & ACLK_PERI_DIV_MASK) >> ACLK_PERI_DIV_SHIFT;
		parent = priv->gpll_hz;
		break;
	case PCLK_PERI:
	case PCLK_I2C0:
	case PCLK_I2C1:
	case PCLK_I2C2:
	case PCLK_I2C3:
	case PCLK_PWM:
	case PCLK_WDT:
		con = readl(&cru->cru_clksel_con[10]);
		div = (con & PCLK_PERI_DIV_MASK) >> PCLK_PERI_DIV_SHIFT;
		parent = rk3128_peri_get_clk(priv, ACLK_PERI);
		break;
	case HCLK_PERI:
		con = readl(&cru->cru_clksel_con[10]);
		div = (con & HCLK_PERI_DIV_MASK) >> HCLK_PERI_DIV_SHIFT;
		parent = rk3128_peri_get_clk(priv, ACLK_PERI);
		break;
	default:
		printf("do not support this peripheral bus\n");
		return -EINVAL;
	}

	return DIV_TO_RATE(parent, div);
}

static ulong rk3128_peri_set_clk(struct rk3128_clk_priv *priv,
				 ulong clk_id, uint hz)
{
	struct rk3128_cru *cru = priv->cru;
	int src_clk_div;

	switch (clk_id) {
	case ACLK_PERI:
		src_clk_div = DIV_ROUND_UP(priv->gpll_hz, hz);
		assert(src_clk_div - 1 < 32);
		rk_clrsetreg(&cru->cru_clksel_con[10],
			     PERI_PLL_SEL_MASK | ACLK_PERI_DIV_MASK,
			     PERI_PLL_SEL_GPLL << PERI_PLL_SEL_SHIFT |
			     (src_clk_div - 1) << ACLK_PERI_DIV_SHIFT);
		break;
	case PCLK_I2C0:
	case PCLK_I2C1:
	case PCLK_I2C2:
	case PCLK_I2C3:
	case PCLK_PWM:
	case PCLK_PERI:
		src_clk_div = DIV_ROUND_UP(rk3128_peri_get_clk(priv,
							       ACLK_PERI),
					   hz);
		assert(src_clk_div - 1 < 3);
		rk_clrsetreg(&cru->cru_clksel_con[10],
			     PCLK_PERI_DIV_MASK,
			     (src_clk_div - 1) << PCLK_PERI_DIV_SHIFT);
		break;
	case HCLK_PERI:
		src_clk_div = DIV_ROUND_UP(rk3128_peri_get_clk(priv,
							       ACLK_PERI),
					   hz);
		assert(src_clk_div - 1 < 7);
		rk_clrsetreg(&cru->cru_clksel_con[10],
			     HCLK_PERI_DIV_MASK,
			     (src_clk_div - 1) << HCLK_PERI_DIV_SHIFT);
		break;
	default:
		printf("do not support this peripheral bus\n");
		return -EINVAL;
	}

	return rk3128_peri_get_clk(priv, clk_id);
}

static ulong rk3128_bus_get_clk(struct rk3128_clk_priv *priv, ulong clk_id)
{
	struct rk3128_cru *cru = priv->cru;
	u32 div, con, parent;

	switch (clk_id) {
	case ACLK_CPU:
		con = readl(&cru->cru_clksel_con[0]);
		div = (con & ACLK_BUS_DIV_MASK) >> ACLK_BUS_DIV_SHIFT;
		parent = priv->gpll_hz;
		break;
	case PCLK_CPU:
		con = readl(&cru->cru_clksel_con[1]);
		div = (con & PCLK_BUS_DIV_MASK) >> PCLK_BUS_DIV_SHIFT;
		parent = rk3128_bus_get_clk(priv, ACLK_CPU);
		break;
	case HCLK_CPU:
		con = readl(&cru->cru_clksel_con[1]);
		div = (con & HCLK_BUS_DIV_MASK) >> HCLK_BUS_DIV_SHIFT;
		parent = rk3128_bus_get_clk(priv, ACLK_CPU);
		break;
	default:
		printf("do not support this peripheral bus\n");
		return -EINVAL;
	}

	return DIV_TO_RATE(parent, div);
}

static ulong rk3128_bus_set_clk(struct rk3128_clk_priv *priv,
				ulong clk_id, uint hz)
{
	struct rk3128_cru *cru = priv->cru;
	int src_clk_div;

	switch (clk_id) {
	case ACLK_CPU:
		src_clk_div = DIV_ROUND_UP(priv->gpll_hz, hz);
		assert(src_clk_div - 1 < 32);
		rk_clrsetreg(&cru->cru_clksel_con[0],
			     BUS_PLL_SEL_MASK | ACLK_BUS_DIV_MASK,
			     BUS_PLL_SEL_GPLL << BUS_PLL_SEL_SHIFT |
			     (src_clk_div - 1) << ACLK_BUS_DIV_SHIFT);
		break;
	case PCLK_CPU:
		src_clk_div = DIV_ROUND_UP(rk3128_bus_get_clk(priv,
							      ACLK_CPU),
					   hz);
		assert(src_clk_div - 1 < 3);
		rk_clrsetreg(&cru->cru_clksel_con[1],
			     PCLK_BUS_DIV_MASK,
			     (src_clk_div - 1) << PCLK_BUS_DIV_SHIFT);
		break;
	case HCLK_CPU:
		src_clk_div = DIV_ROUND_UP(rk3128_bus_get_clk(priv,
							      ACLK_CPU),
					   hz);
		assert(src_clk_div - 1 < 7);
		rk_clrsetreg(&cru->cru_clksel_con[1],
			     HCLK_BUS_DIV_MASK,
			     (src_clk_div - 1) << HCLK_BUS_DIV_SHIFT);
		break;
	default:
		printf("do not support this peripheral bus\n");
		return -EINVAL;
	}

	return rk3128_bus_get_clk(priv, clk_id);
}

static ulong rk3128_spi_get_clk(struct rk3128_clk_priv *priv)
{
	struct rk3128_cru *cru = priv->cru;
	u32 div, con, parent;

	con = readl(&cru->cru_clksel_con[25]);
	div = (con & SPI_DIV_MASK) >> SPI_DIV_SHIFT;
	parent = priv->gpll_hz;

	return DIV_TO_RATE(parent, div);
}

static ulong rk3128_spi_set_clk(struct rk3128_clk_priv *priv, ulong hz)
{
	struct rk3128_cru *cru = priv->cru;
	int div;

	div = DIV_ROUND_UP(priv->gpll_hz, hz);
	assert(div - 1 < 128);
	rk_clrsetreg(&cru->cru_clksel_con[25],
		     SPI_PLL_SEL_MASK | SPI_DIV_MASK,
		     SPI_PLL_SEL_GPLL << SPI_PLL_SEL_SHIFT |
		     (div - 1) << SPI_DIV_SHIFT);
	return rk3128_spi_get_clk(priv);
}

#ifndef CONFIG_SPL_BUILD
static ulong rk3128_saradc_get_clk(struct rk3128_clk_priv *priv)
{
	struct rk3128_cru *cru = priv->cru;
	u32 div, val;

	val = readl(&cru->cru_clksel_con[24]);
	div = bitfield_extract(val, SARADC_DIV_CON_SHIFT,
			       SARADC_DIV_CON_WIDTH);

	return DIV_TO_RATE(OSC_HZ, div);
}

static ulong rk3128_saradc_set_clk(struct rk3128_clk_priv *priv, uint hz)
{
	struct rk3128_cru *cru = priv->cru;
	int src_clk_div;

	src_clk_div = DIV_ROUND_UP(OSC_HZ, hz) - 1;
	assert(src_clk_div < 128);

	rk_clrsetreg(&cru->cru_clksel_con[24],
		     SARADC_DIV_CON_MASK,
		     src_clk_div << SARADC_DIV_CON_SHIFT);

	return rk3128_saradc_get_clk(priv);
}

#define RK3128_LCDC_PLL_LIMIT			600000000

static ulong rk3128_vop_set_clk(struct rk3128_clk_priv *priv,
				ulong clk_id, uint hz)
{
	struct rk3128_cru *cru = priv->cru;
	int src_clk_div;

	src_clk_div = GPLL_HZ / hz;
	assert(src_clk_div - 1 < 31);

	switch (clk_id) {
	case ACLK_LCDC0:
	case ACLK_VIO0:
		rk_clrsetreg(&cru->cru_clksel_con[31],
			     VIO0_PLL_MASK | VIO0_DIV_MASK,
			     VIO0_SEL_GPLL << VIO0_PLL_SHIFT |
			     (src_clk_div - 1) << VIO0_DIV_SHIFT);
		break;
	case ACLK_VIO1:
		rk_clrsetreg(&cru->cru_clksel_con[31],
			     VIO1_PLL_MASK | VIO1_DIV_MASK,
			     VIO1_SEL_GPLL << VIO1_PLL_SHIFT |
			     (src_clk_div - 1) << VIO1_DIV_SHIFT);
		break;
	case DCLK_VOP:
		src_clk_div = DIV_ROUND_UP(RK3128_LCDC_PLL_LIMIT, hz);
		rockchip_pll_set_rate(&rk3128_pll_clks[CPLL],
				      priv->cru, CPLL, src_clk_div * hz);
		rk_clrsetreg(&cru->cru_clksel_con[27],
			      DCLK_VOP_SEL_MASK | DCLK_VOP_DIV_CON_MASK,
			     DCLK_VOP_PLL_SEL_CPLL << DCLK_VOP_SEL_SHIFT |
			     (src_clk_div - 1) << DCLK_VOP_DIV_CON_SHIFT);
		break;
	default:
		printf("do not support this vop freq\n");
		return -EINVAL;
	}

	return hz;
}

static ulong rk3128_vop_get_rate(struct rk3128_clk_priv *priv, ulong clk_id)
{
	struct rk3128_cru *cru = priv->cru;
	u32 div, con, parent;

	switch (clk_id) {
	case ACLK_LCDC0:
	case ACLK_VIO0:
		con = readl(&cru->cru_clksel_con[31]);
		div = con  & 0x1f;
		parent = GPLL_HZ;
		break;
	case ACLK_VIO1:
		con = readl(&cru->cru_clksel_con[31]);
		div = (con >> 8) & 0x1f;
		parent = GPLL_HZ;
		break;
	case DCLK_VOP:
		con = readl(&cru->cru_clksel_con[27]);
		div = (con & DCLK_VOP_DIV_CON_MASK) >> DCLK_VOP_DIV_CON_SHIFT;
		parent = rockchip_pll_get_rate(&rk3128_pll_clks[CPLL],
					       priv->cru, CPLL);
		break;
	default:
		return -ENOENT;
	}
	return DIV_TO_RATE(parent, div);
}

static ulong rk3128_crypto_get_rate(struct rk3128_clk_priv *priv)
{
	struct rk3128_cru *cru = priv->cru;
	u32 div, val;

	val = readl(&cru->cru_clksel_con[24]);
	div = (val & CLK_CRYPTO_DIV_CON_MASK) >> CLK_CRYPTO_DIV_CON_SHIFT;

	return DIV_TO_RATE(rk3128_bus_get_clk(priv, ACLK_CPU), div);
}

static ulong rk3128_crypto_set_rate(struct rk3128_clk_priv *priv,
				    uint hz)
{
	struct rk3128_cru *cru = priv->cru;
	int src_clk_div;
	uint p_rate;

	p_rate = rk3128_bus_get_clk(priv, ACLK_CPU);
	src_clk_div = DIV_ROUND_UP(p_rate, hz) - 1;
	assert(src_clk_div < 3);

	rk_clrsetreg(&cru->cru_clksel_con[24],
		     CLK_CRYPTO_DIV_CON_MASK,
		     src_clk_div << CLK_CRYPTO_DIV_CON_SHIFT);

	return rk3128_crypto_get_rate(priv);
}
#endif

static ulong rk3128_clk_get_rate(struct clk *clk)
{
	struct rk3128_clk_priv *priv = dev_get_priv(clk->dev);
	ulong rate = 0;

	switch (clk->id) {
	case PLL_APLL:
	case PLL_DPLL:
	case PLL_CPLL:
	case PLL_GPLL:
		rate =  rockchip_pll_get_rate(&rk3128_pll_clks[clk->id - 1],
					      priv->cru, clk->id - 1);
		break;
	case ARMCLK:
		rate = rockchip_pll_get_rate(&rk3128_pll_clks[APLL],
					     priv->cru, APLL);
		break;
	case HCLK_EMMC:
	case SCLK_EMMC:
	case HCLK_SDMMC:
	case SCLK_SDMMC:
	case HCLK_SDIO:
	case SCLK_SDIO:
		rate = rockchip_mmc_get_clk(priv, clk->id);
		break;
	case ACLK_PERI:
	case HCLK_PERI:
	case PCLK_PERI:
	case PCLK_I2C0:
	case PCLK_I2C1:
	case PCLK_I2C2:
	case PCLK_I2C3:
	case PCLK_PWM:
	case PCLK_WDT:
		rate = rk3128_peri_get_clk(priv, clk->id);
		break;
	case ACLK_CPU:
	case HCLK_CPU:
	case PCLK_CPU:
		rate = rk3128_bus_get_clk(priv, clk->id);
		break;
	case SCLK_SPI0:
		rate = rk3128_spi_get_clk(priv);
		break;
#ifndef CONFIG_SPL_BUILD
	case SCLK_SARADC:
		rate = rk3128_saradc_get_clk(priv);
		break;
	case DCLK_VOP:
	case ACLK_VIO0:
	case ACLK_VIO1:
	case ACLK_LCDC0:
		rate = rk3128_vop_get_rate(priv, clk->id);
		break;
	case SCLK_CRYPTO:
		rate = rk3128_crypto_get_rate(priv);
		break;
#endif
	default:
		return -ENOENT;
	}
	return rate;
}

static ulong rk3128_clk_set_rate(struct clk *clk, ulong rate)
{
	struct rk3128_clk_priv *priv = dev_get_priv(clk->dev);
	ulong ret = 0;

	switch (clk->id) {
	case PLL_APLL:
	case PLL_DPLL:
	case PLL_CPLL:
		ret = rockchip_pll_set_rate(&rk3128_pll_clks[clk->id - 1],
					    priv->cru, clk->id - 1, rate);
	case PLL_GPLL:
		ret = rockchip_pll_set_rate(&rk3128_pll_clks[GPLL],
					    priv->cru, GPLL, rate);
		priv->gpll_hz = rate;
		break;
	case ARMCLK:
		if (priv->armclk_hz)
			ret = rk3128_armclk_set_clk(priv, rate);
		priv->armclk_hz = rate;
		break;
	case HCLK_EMMC:
	case SCLK_EMMC:
	case SCLK_EMMC_SAMPLE:
	case HCLK_SDMMC:
	case SCLK_SDMMC:
	case SCLK_SDMMC_SAMPLE:
	case HCLK_SDIO:
	case SCLK_SDIO:
	case SCLK_SDIO_SAMPLE:
		ret = rockchip_mmc_set_clk(priv, clk->id, rate);
		break;
	case ACLK_PERI:
	case PCLK_PERI:
	case HCLK_PERI:
	case PCLK_I2C0:
	case PCLK_I2C1:
	case PCLK_I2C2:
	case PCLK_I2C3:
	case PCLK_PWM:
		ret = rk3128_peri_set_clk(priv, clk->id, rate);
		break;
	case ACLK_CPU:
	case HCLK_CPU:
	case PCLK_CPU:
		ret = rk3128_bus_set_clk(priv, clk->id, rate);
		break;
	case SCLK_SPI0:
		rate = rk3128_spi_set_clk(priv, rate);
		break;
#ifndef CONFIG_SPL_BUILD
	case SCLK_SARADC:
		ret = rk3128_saradc_set_clk(priv, rate);
		break;
	case DCLK_VOP:
	case ACLK_VIO0:
	case ACLK_VIO1:
	case ACLK_LCDC0:
		ret = rk3128_vop_set_clk(priv, clk->id, rate);
		break;
	case SCLK_CRYPTO:
		ret = rk3128_crypto_set_rate(priv, rate);
		break;
#endif
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

int rk3128_mmc_get_phase(struct clk *clk)
{
	struct rk3128_clk_priv *priv = dev_get_priv(clk->dev);
	struct rk3128_cru *cru = priv->cru;
	u32 raw_value, delay_num;
	u16 degrees = 0;
	ulong rate;

	rate = rk3128_clk_get_rate(clk);

	if (rate < 0)
		return rate;

	if (clk->id == SCLK_EMMC_SAMPLE)
		raw_value = readl(&cru->cru_emmc_con[1]);
	else if (clk->id == SCLK_SDMMC_SAMPLE)
		raw_value = readl(&cru->cru_sdmmc_con[1]);
	else
		raw_value = readl(&cru->cru_sdio_con[1]);

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

int rk3128_mmc_set_phase(struct clk *clk, u32 degrees)
{
	struct rk3128_clk_priv *priv = dev_get_priv(clk->dev);
	struct rk3128_cru *cru = priv->cru;
	u8 nineties, remainder, delay_num;
	u32 raw_value, delay;
	ulong rate;

	rate = rk3128_clk_get_rate(clk);

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
		writel(raw_value | 0xffff0000, &cru->cru_emmc_con[1]);
	else if (clk->id == SCLK_SDMMC_SAMPLE)
		writel(raw_value | 0xffff0000, &cru->cru_sdmmc_con[1]);
	else
		writel(raw_value | 0xffff0000, &cru->cru_sdio_con[1]);

	debug("mmc set_phase(%d) delay_nums=%u reg=%#x actual_degrees=%d\n",
	      degrees, delay_num, raw_value, rk3128_mmc_get_phase(clk));

	return 0;
}

static int rk3128_clk_get_phase(struct clk *clk)
{
	int ret;

	debug("%s %ld\n", __func__, clk->id);
	switch (clk->id) {
	case SCLK_EMMC_SAMPLE:
	case SCLK_SDMMC_SAMPLE:
	case SCLK_SDIO_SAMPLE:
		ret = rk3128_mmc_get_phase(clk);
		break;
	default:
		return -ENOENT;
	}

	return ret;
}

static int rk3128_clk_set_phase(struct clk *clk, int degrees)
{
	int ret;

	debug("%s %ld\n", __func__, clk->id);
	switch (clk->id) {
	case SCLK_EMMC_SAMPLE:
	case SCLK_SDMMC_SAMPLE:
	case SCLK_SDIO_SAMPLE:
		ret = rk3128_mmc_set_phase(clk, degrees);
		break;
	default:
		return -ENOENT;
	}

	return ret;
}

static struct clk_ops rk3128_clk_ops = {
	.get_rate	= rk3128_clk_get_rate,
	.set_rate	= rk3128_clk_set_rate,
	.get_phase	= rk3128_clk_get_phase,
	.set_phase	= rk3128_clk_set_phase,
};

static int rk3128_clk_ofdata_to_platdata(struct udevice *dev)
{
	struct rk3128_clk_priv *priv = dev_get_priv(dev);

	priv->cru = dev_read_addr_ptr(dev);

	return 0;
}

static void rkclk_init(struct rk3128_clk_priv *priv)
{
	if (rockchip_pll_get_rate(&rk3128_pll_clks[APLL],
				  priv->cru, APLL) != APLL_HZ)
		rk3128_armclk_set_clk(priv, APLL_HZ);

	priv->gpll_hz = rockchip_pll_get_rate(&rk3128_pll_clks[GPLL],
					      priv->cru, GPLL);
	rk3128_bus_set_clk(priv, ACLK_CPU, ACLK_BUS_HZ / 2);
	rk3128_peri_set_clk(priv, ACLK_PERI, ACLK_PERI_HZ / 2);
	rockchip_pll_set_rate(&rk3128_pll_clks[GPLL],
			      priv->cru, GPLL, GPLL_HZ);
	priv->gpll_hz = GPLL_HZ;
	rk_clrsetreg(&priv->cru->cru_clksel_con[2],
		     NANDC_PLL_SEL_MASK | NANDC_CLK_DIV_MASK,
		     NANDC_PLL_SEL_GPLL << NANDC_PLL_SEL_SHIFT |
		     3 << NANDC_CLK_DIV_SHIFT);
	rk_clrsetreg(&priv->cru->cru_clksel_con[11],
		     SFC_PLL_SEL_MASK | SFC_CLK_DIV_MASK,
		     SFC_PLL_SEL_GPLL << SFC_PLL_SEL_SHIFT |
		     9 << SFC_CLK_DIV_SHIFT);

	rk3128_bus_set_clk(priv, ACLK_CPU, ACLK_BUS_HZ);
	rk3128_bus_set_clk(priv, HCLK_CPU, ACLK_BUS_HZ / 2);
	rk3128_bus_set_clk(priv, PCLK_CPU, ACLK_BUS_HZ / 2);
	rk3128_peri_set_clk(priv, ACLK_PERI, ACLK_PERI_HZ);
	rk3128_peri_set_clk(priv, HCLK_PERI, ACLK_PERI_HZ / 2);
	rk3128_peri_set_clk(priv, PCLK_PERI, ACLK_PERI_HZ / 2);

	rockchip_pll_set_rate(&rk3128_pll_clks[CPLL],
			      priv->cru, CPLL, CPLL_HZ);
}

static int rk3128_clk_probe(struct udevice *dev)
{
	struct rk3128_clk_priv *priv = dev_get_priv(dev);

	priv->sync_kernel = false;
	if (!priv->armclk_enter_hz)
		priv->armclk_enter_hz =
		rockchip_pll_get_rate(&rk3128_pll_clks[APLL],
				      priv->cru, APLL);
	rkclk_init(priv);
	if (!priv->armclk_init_hz)
		priv->armclk_init_hz =
		rockchip_pll_get_rate(&rk3128_pll_clks[APLL],
				      priv->cru, APLL);

	return 0;
}

static int rk3128_clk_bind(struct udevice *dev)
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
		priv->glb_srst_fst_value = offsetof(struct rk3128_cru,
						    cru_glb_srst_fst_value);
		priv->glb_srst_snd_value = offsetof(struct rk3128_cru,
						    cru_glb_srst_snd_value);
		sys_child->priv = priv;
	}

	ret = device_bind_driver_to_node(dev, "rockchip_reset", "reset",
					 dev_ofnode(dev), &sf_child);
	if (ret) {
		debug("Warning: No rockchip reset driver: ret=%d\n", ret);
	} else {
		sf_priv = malloc(sizeof(struct softreset_reg));
		sf_priv->sf_reset_offset = offsetof(struct rk3128_cru,
						    cru_softrst_con[0]);
		sf_priv->sf_reset_num = 9;
		sf_child->priv = sf_priv;
	}

	return 0;
}

static const struct udevice_id rk3128_clk_ids[] = {
	{ .compatible = "rockchip,rk3128-cru" },
	{ .compatible = "rockchip,rk3126-cru" },
	{ }
};

U_BOOT_DRIVER(rockchip_rk3128_cru) = {
	.name		= "clk_rk3128",
	.id		= UCLASS_CLK,
	.of_match	= rk3128_clk_ids,
	.priv_auto_alloc_size = sizeof(struct rk3128_clk_priv),
	.ofdata_to_platdata = rk3128_clk_ofdata_to_platdata,
	.ops		= &rk3128_clk_ops,
	.bind		= rk3128_clk_bind,
	.probe		= rk3128_clk_probe,
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
	struct rk3128_clk_priv *priv;
	const struct rk3128_clk_info *clk_dump;
	struct clk clk;
	unsigned long clk_count = ARRAY_SIZE(clks_dump);
	unsigned long rate;
	int i, ret;

	ret = uclass_get_device_by_driver(UCLASS_CLK,
					  DM_GET_DRIVER(rockchip_rk3128_cru),
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

