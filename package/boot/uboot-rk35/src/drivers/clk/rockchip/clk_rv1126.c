// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
 * Author: Finley Xiao <finley.xiao@rock-chips.com>
 */

#include <common.h>
#include <bitfield.h>
#include <clk-uclass.h>
#include <dm.h>
#include <errno.h>
#include <syscon.h>
#include <asm/arch-rockchip/clock.h>
#include <asm/arch-rockchip/cru_rv1126.h>
#include <asm/arch-rockchip/grf_rv1126.h>
#include <asm/arch-rockchip/hardware.h>
#include <asm/io.h>
#include <dm/lists.h>
#include <dt-bindings/clock/rv1126-cru.h>

DECLARE_GLOBAL_DATA_PTR;

#define RV1126_CPUCLK_RATE(_rate, _aclk_div, _pclk_div)		\
{								\
	.rate	= _rate##U,					\
	.aclk_div = _aclk_div,					\
	.pclk_div = _pclk_div,					\
}

#define DIV_TO_RATE(input_rate, div)    ((input_rate) / ((div) + 1))

static struct rockchip_cpu_rate_table rv1126_cpu_rates[] = {
	RV1126_CPUCLK_RATE(1200000000, 1, 5),
	RV1126_CPUCLK_RATE(1008000000, 1, 5),
	RV1126_CPUCLK_RATE(816000000, 1, 3),
	RV1126_CPUCLK_RATE(600000000, 1, 3),
	RV1126_CPUCLK_RATE(408000000, 1, 1),
};

static struct rockchip_pll_rate_table rv1126_pll_rates[] = {
	/* _mhz, _refdiv, _fbdiv, _postdiv1, _postdiv2, _dsmpd, _frac */
	RK3036_PLL_RATE(1600000000, 3, 200, 1, 1, 1, 0),
	RK3036_PLL_RATE(1400000000, 3, 350, 2, 1, 1, 0),
	RK3036_PLL_RATE(1200000000, 1, 100, 2, 1, 1, 0),
	RK3036_PLL_RATE(1188000000, 1, 99, 2, 1, 1, 0),
	RK3036_PLL_RATE(1100000000, 3, 275, 2, 1, 1, 0),
	RK3036_PLL_RATE(1008000000, 1, 84, 2, 1, 1, 0),
	RK3036_PLL_RATE(1000000000, 3, 250, 2, 1, 1, 0),
	RK3036_PLL_RATE(816000000, 1, 68, 2, 1, 1, 0),
	RK3036_PLL_RATE(800000000, 3, 200, 2, 1, 1, 0),
	RK3036_PLL_RATE(600000000, 1, 100, 4, 1, 1, 0),
	RK3036_PLL_RATE(594000000, 1, 99, 4, 1, 1, 0),
	RK3036_PLL_RATE(500000000, 1, 125, 6, 1, 1, 0),
	RK3036_PLL_RATE(200000000, 1, 100, 6, 2, 1, 0),
	RK3036_PLL_RATE(100000000, 1, 100, 6, 4, 1, 0),
	{ /* sentinel */ },
};

static struct rockchip_pll_clock rv1126_pll_clks[] = {
	[APLL] = PLL(pll_rk3328, PLL_APLL, RV1126_PLL_CON(0),
		     RV1126_MODE_CON, 0, 10, 0, rv1126_pll_rates),
	[DPLL] = PLL(pll_rk3328, PLL_DPLL, RV1126_PLL_CON(8),
		     RV1126_MODE_CON, 2, 10, 0, NULL),
	[CPLL] = PLL(pll_rk3328, PLL_CPLL, RV1126_PLL_CON(16),
		     RV1126_MODE_CON, 4, 10, 0, rv1126_pll_rates),
	[HPLL] = PLL(pll_rk3328, PLL_HPLL, RV1126_PLL_CON(24),
		     RV1126_MODE_CON, 6, 10, 0, rv1126_pll_rates),
	[GPLL] = PLL(pll_rk3328, PLL_GPLL, RV1126_PMU_PLL_CON(0),
		     RV1126_PMU_MODE, 0, 10, 0, rv1126_pll_rates),
};

#ifndef CONFIG_SPL_BUILD
#define RV1126_CLK_DUMP(_id, _name, _iscru)	\
{						\
	.id = _id,				\
	.name = _name,				\
	.is_cru = _iscru,			\
}

static const struct rv1126_clk_info clks_dump[] = {
	RV1126_CLK_DUMP(PLL_APLL, "apll", true),
	RV1126_CLK_DUMP(PLL_DPLL, "dpll", true),
	RV1126_CLK_DUMP(PLL_GPLL, "gpll", false),
	RV1126_CLK_DUMP(PLL_CPLL, "cpll", true),
	RV1126_CLK_DUMP(PLL_HPLL, "hpll", true),
	RV1126_CLK_DUMP(ACLK_PDBUS, "aclk_pdbus", true),
	RV1126_CLK_DUMP(HCLK_PDBUS, "hclk_pdbus", true),
	RV1126_CLK_DUMP(PCLK_PDBUS, "pclk_pdbus", true),
	RV1126_CLK_DUMP(ACLK_PDPHP, "aclk_pdphp", true),
	RV1126_CLK_DUMP(HCLK_PDPHP, "hclk_pdphp", true),
	RV1126_CLK_DUMP(HCLK_PDAUDIO, "hclk_pdaudio", true),
	RV1126_CLK_DUMP(HCLK_PDCORE_NIU, "hclk_pdcore", true),
	RV1126_CLK_DUMP(PCLK_PDPMU, "pclk_pdpmu", false),
};
#endif

static ulong rv1126_gpll_set_rate(struct rv1126_clk_priv *priv,
				  struct rv1126_pmuclk_priv *pmu_priv,
				  ulong rate);
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

static ulong rv1126_gpll_get_pmuclk(struct rv1126_pmuclk_priv *priv)
{
	return rockchip_pll_get_rate(&rv1126_pll_clks[GPLL],
				     priv->pmucru, GPLL);
}

static ulong rv1126_gpll_set_pmuclk(struct rv1126_pmuclk_priv *pmu_priv, ulong rate)
{
	struct udevice *cru_dev;
	struct rv1126_clk_priv *priv;
	int ret;

	ret = uclass_get_device_by_driver(UCLASS_CLK,
					  DM_GET_DRIVER(rockchip_rv1126_cru),
					  &cru_dev);
	if (ret) {
		printf("%s: could not find cru device\n", __func__);
		return ret;
	}
	priv = dev_get_priv(cru_dev);

	if (rv1126_gpll_set_rate(priv, pmu_priv, rate)) {
		printf("%s: failed to set gpll rate %lu\n", __func__, rate);
		return -EINVAL;
	}
	return 0;
}

static ulong rv1126_rtc32k_get_pmuclk(struct rv1126_pmuclk_priv *priv)
{
	struct rv1126_pmucru *pmucru = priv->pmucru;
	unsigned long m, n;
	u32 fracdiv;

	fracdiv = readl(&pmucru->pmu_clksel_con[13]);
	m = fracdiv & CLK_RTC32K_FRAC_NUMERATOR_MASK;
	m >>= CLK_RTC32K_FRAC_NUMERATOR_SHIFT;
	n = fracdiv & CLK_RTC32K_FRAC_DENOMINATOR_MASK;
	n >>= CLK_RTC32K_FRAC_DENOMINATOR_SHIFT;

	return OSC_HZ * m / n;
}

static ulong rv1126_rtc32k_set_pmuclk(struct rv1126_pmuclk_priv *priv,
				      ulong rate)
{
	struct rv1126_pmucru *pmucru = priv->pmucru;
	unsigned long m, n, val;

	rk_clrsetreg(&pmucru->pmu_clksel_con[0], RTC32K_SEL_MASK,
		     RTC32K_SEL_OSC0_DIV32K << RTC32K_SEL_SHIFT);

	rational_best_approximation(rate, OSC_HZ,
				    GENMASK(16 - 1, 0),
				    GENMASK(16 - 1, 0),
				    &m, &n);
	val = m << CLK_RTC32K_FRAC_NUMERATOR_SHIFT | n;
	writel(val, &pmucru->pmu_clksel_con[13]);

	return rv1126_rtc32k_get_pmuclk(priv);
}

static ulong rv1126_i2c_get_pmuclk(struct rv1126_pmuclk_priv *priv,
				   ulong clk_id)
{
	struct rv1126_pmucru *pmucru = priv->pmucru;
	u32 div, con;

	switch (clk_id) {
	case CLK_I2C0:
		con = readl(&pmucru->pmu_clksel_con[2]);
		div = (con & CLK_I2C0_DIV_MASK) >> CLK_I2C0_DIV_SHIFT;
		break;
	case CLK_I2C2:
		con = readl(&pmucru->pmu_clksel_con[3]);
		div = (con & CLK_I2C1_DIV_MASK) >> CLK_I2C1_DIV_SHIFT;
		break;
	default:
		return -ENOENT;
	}

	return DIV_TO_RATE(priv->gpll_hz, div);
}

static ulong rv1126_i2c_set_pmuclk(struct rv1126_pmuclk_priv *priv,
				   ulong clk_id, ulong rate)
{
	struct rv1126_pmucru *pmucru = priv->pmucru;
	int src_clk_div;

	src_clk_div = DIV_ROUND_UP(priv->gpll_hz, rate);
	assert(src_clk_div - 1 <= 127);

	switch (clk_id) {
	case CLK_I2C0:
		rk_clrsetreg(&pmucru->pmu_clksel_con[2], CLK_I2C0_DIV_MASK,
			     (src_clk_div - 1) << CLK_I2C0_DIV_SHIFT);
		break;
	case CLK_I2C2:
		rk_clrsetreg(&pmucru->pmu_clksel_con[3], CLK_I2C2_DIV_MASK,
			     (src_clk_div - 1) << CLK_I2C2_DIV_SHIFT);
		break;
	default:
		return -ENOENT;
	}

	return rv1126_i2c_get_pmuclk(priv, clk_id);
}

static ulong rv1126_pwm_get_pmuclk(struct rv1126_pmuclk_priv *priv,
				   ulong clk_id)
{
	struct rv1126_pmucru *pmucru = priv->pmucru;
	u32 div, sel, con;

	switch (clk_id) {
	case CLK_PWM0:
		con = readl(&pmucru->pmu_clksel_con[6]);
		sel = (con & CLK_PWM0_SEL_MASK) >> CLK_PWM0_SEL_SHIFT;
		div = (con & CLK_PWM0_DIV_MASK) >> CLK_PWM0_DIV_SHIFT;
		if (sel == CLK_PWM0_SEL_XIN24M)
			return OSC_HZ;
		break;
	case CLK_PWM1:
		con = readl(&pmucru->pmu_clksel_con[6]);
		sel = (con & CLK_PWM1_SEL_MASK) >> CLK_PWM1_SEL_SHIFT;
		div = (con & CLK_PWM1_DIV_MASK) >> CLK_PWM1_DIV_SHIFT;
		if (sel == CLK_PWM1_SEL_XIN24M)
			return OSC_HZ;
		break;
	default:
		return -ENOENT;
	}

	return DIV_TO_RATE(priv->gpll_hz, div);
}

static ulong rv1126_pwm_set_pmuclk(struct rv1126_pmuclk_priv *priv,
				   ulong clk_id, ulong rate)
{
	struct rv1126_pmucru *pmucru = priv->pmucru;
	int src_clk_div;

	switch (clk_id) {
	case CLK_PWM0:
		if (rate == OSC_HZ) {
			rk_clrsetreg(&pmucru->pmu_clksel_con[6],
				     CLK_PWM0_SEL_MASK,
				     CLK_PWM0_SEL_XIN24M << CLK_PWM0_SEL_SHIFT);
			rk_clrsetreg(&pmucru->pmu_clksel_con[6],
				     CLK_PWM0_DIV_MASK, 0);
		} else {
			src_clk_div = DIV_ROUND_UP(priv->gpll_hz, rate);
			assert(src_clk_div - 1 <= 127);
			rk_clrsetreg(&pmucru->pmu_clksel_con[6],
				     CLK_PWM0_DIV_MASK,
				     (src_clk_div - 1) << CLK_PWM0_DIV_SHIFT);
			rk_clrsetreg(&pmucru->pmu_clksel_con[6],
				     CLK_PWM0_SEL_MASK,
				     CLK_PWM0_SEL_GPLL << CLK_PWM0_SEL_SHIFT);
		}
		break;
	case CLK_PWM1:
		if (rate == OSC_HZ) {
			rk_clrsetreg(&pmucru->pmu_clksel_con[6],
				     CLK_PWM1_SEL_MASK,
				     CLK_PWM1_SEL_XIN24M << CLK_PWM1_SEL_SHIFT);
			rk_clrsetreg(&pmucru->pmu_clksel_con[6],
				     CLK_PWM1_DIV_MASK, 0);
		} else {
			src_clk_div = DIV_ROUND_UP(priv->gpll_hz, rate);
			assert(src_clk_div - 1 <= 127);
			rk_clrsetreg(&pmucru->pmu_clksel_con[6],
				     CLK_PWM1_DIV_MASK,
				     (src_clk_div - 1) << CLK_PWM1_DIV_SHIFT);
			rk_clrsetreg(&pmucru->pmu_clksel_con[6],
				     CLK_PWM1_SEL_MASK,
				     CLK_PWM1_SEL_GPLL << CLK_PWM1_SEL_SHIFT);
		}
		break;
	default:
		return -ENOENT;
	}

	return rv1126_pwm_get_pmuclk(priv, clk_id);
}

static ulong rv1126_spi_get_pmuclk(struct rv1126_pmuclk_priv *priv)
{
	struct rv1126_pmucru *pmucru = priv->pmucru;
	u32 div, con;

	con = readl(&pmucru->pmu_clksel_con[9]);
	div = (con & CLK_SPI0_DIV_MASK) >> CLK_SPI0_DIV_SHIFT;

	return DIV_TO_RATE(priv->gpll_hz, div);
}

static ulong rv1126_spi_set_pmuclk(struct rv1126_pmuclk_priv *priv,
				   ulong rate)
{
	struct rv1126_pmucru *pmucru = priv->pmucru;
	int src_clk_div;

	src_clk_div = DIV_ROUND_UP(priv->gpll_hz, rate);
	assert(src_clk_div - 1 <= 127);

	rk_clrsetreg(&pmucru->pmu_clksel_con[9],
		     CLK_SPI0_SEL_MASK | CLK_SPI0_DIV_MASK,
		     CLK_SPI0_SEL_GPLL << CLK_SPI0_SEL_SHIFT |
		     (src_clk_div - 1) << CLK_SPI0_DIV_SHIFT);

	return rv1126_spi_get_pmuclk(priv);
}

static ulong rv1126_pdpmu_get_pmuclk(struct rv1126_pmuclk_priv *priv)
{
	struct rv1126_pmucru *pmucru = priv->pmucru;
	u32 div, con;

	con = readl(&pmucru->pmu_clksel_con[1]);
	div = (con & PCLK_PDPMU_DIV_MASK) >> PCLK_PDPMU_DIV_SHIFT;

	return DIV_TO_RATE(priv->gpll_hz, div);
}

static ulong rv1126_pdpmu_set_pmuclk(struct rv1126_pmuclk_priv *priv,
				     ulong rate)
{
	struct rv1126_pmucru *pmucru = priv->pmucru;
	int src_clk_div;

	src_clk_div = DIV_ROUND_UP(priv->gpll_hz, rate);
	assert(src_clk_div - 1 <= 31);

	rk_clrsetreg(&pmucru->pmu_clksel_con[1],
		     PCLK_PDPMU_DIV_MASK,
		     (src_clk_div - 1) << PCLK_PDPMU_DIV_SHIFT);

	return rv1126_pdpmu_get_pmuclk(priv);
}

static ulong rv1126_pmuclk_get_rate(struct clk *clk)
{
	struct rv1126_pmuclk_priv *priv = dev_get_priv(clk->dev);
	ulong rate = 0;

	if (!priv->gpll_hz) {
		printf("%s gpll=%lu\n", __func__, priv->gpll_hz);
		return -ENOENT;
	}

	debug("%s %ld\n", __func__, clk->id);
	switch (clk->id) {
	case PLL_GPLL:
		rate = rv1126_gpll_get_pmuclk(priv);
		break;
	case CLK_RTC32K:
		rate = rv1126_rtc32k_get_pmuclk(priv);
		break;
	case CLK_I2C0:
	case CLK_I2C2:
		rate = rv1126_i2c_get_pmuclk(priv, clk->id);
		break;
	case CLK_PWM0:
	case CLK_PWM1:
		rate = rv1126_pwm_get_pmuclk(priv, clk->id);
		break;
	case CLK_SPI0:
		rate = rv1126_spi_get_pmuclk(priv);
		break;
	case PCLK_PDPMU:
		rate = rv1126_pdpmu_get_pmuclk(priv);
		break;
	default:
		return -ENOENT;
	}

	return rate;
}

static ulong rv1126_pmuclk_set_rate(struct clk *clk, ulong rate)
{
	struct rv1126_pmuclk_priv *priv = dev_get_priv(clk->dev);
	ulong ret = 0;

	if (!priv->gpll_hz) {
		printf("%s gpll=%lu\n", __func__, priv->gpll_hz);
		return -ENOENT;
	}

	debug("%s %ld %ld\n", __func__, clk->id, rate);
	switch (clk->id) {
	case PLL_GPLL:
		ret = rv1126_gpll_set_pmuclk(priv, rate);
		break;
	case CLK_RTC32K:
		ret = rv1126_rtc32k_set_pmuclk(priv, rate);
		break;
	case CLK_I2C0:
	case CLK_I2C2:
		ret = rv1126_i2c_set_pmuclk(priv, clk->id, rate);
		break;
	case CLK_PWM0:
	case CLK_PWM1:
		ret = rv1126_pwm_set_pmuclk(priv, clk->id, rate);
		break;
	case CLK_SPI0:
		ret = rv1126_spi_set_pmuclk(priv, rate);
		break;
	case PCLK_PDPMU:
		ret = rv1126_pdpmu_set_pmuclk(priv, rate);
		break;
	default:
		return -ENOENT;
	}

	return ret;
}

static int rv1126_rtc32k_set_parent(struct clk *clk, struct clk *parent)
{
	struct rv1126_pmuclk_priv *priv = dev_get_priv(clk->dev);
	struct rv1126_pmucru *pmucru = priv->pmucru;

	if (parent->id == CLK_OSC0_DIV32K)
		rk_clrsetreg(&pmucru->pmu_clksel_con[0], RTC32K_SEL_MASK,
			     RTC32K_SEL_OSC0_DIV32K << RTC32K_SEL_SHIFT);
	else
		rk_clrsetreg(&pmucru->pmu_clksel_con[0], RTC32K_SEL_MASK,
			     RTC32K_SEL_OSC1_32K << RTC32K_SEL_SHIFT);

	return 0;
}

static int rv1126_pmuclk_set_parent(struct clk *clk, struct clk *parent)
{
	switch (clk->id) {
	case CLK_RTC32K:
		return rv1126_rtc32k_set_parent(clk, parent);
	default:
		return -ENOENT;
	}
}
static struct clk_ops rv1126_pmuclk_ops = {
	.get_rate = rv1126_pmuclk_get_rate,
	.set_rate = rv1126_pmuclk_set_rate,
	.set_parent = rv1126_pmuclk_set_parent,
};

static int rv1126_pmuclk_probe(struct udevice *dev)
{
	struct rv1126_pmuclk_priv *priv = dev_get_priv(dev);

	priv->gpll_hz =	rv1126_gpll_get_pmuclk(priv);

	return 0;
}

static int rv1126_pmuclk_ofdata_to_platdata(struct udevice *dev)
{
	struct rv1126_pmuclk_priv *priv = dev_get_priv(dev);

	priv->pmucru = dev_read_addr_ptr(dev);

	return 0;
}

static int rv1126_pmuclk_bind(struct udevice *dev)
{
	int ret = 0;
	struct udevice *sf_child;
	struct softreset_reg *sf_priv;

	ret = device_bind_driver_to_node(dev, "rockchip_reset",
					 "reset", dev_ofnode(dev),
					 &sf_child);
	if (ret) {
		debug("Warning: No rockchip reset driver: ret=%d\n", ret);
	} else {
		sf_priv = malloc(sizeof(struct softreset_reg));
		sf_priv->sf_reset_offset = offsetof(struct rv1126_pmucru,
						    pmu_softrst_con[0]);
		sf_priv->sf_reset_num = 2;
		sf_child->priv = sf_priv;
	}

	return 0;
}

static const struct udevice_id rv1126_pmuclk_ids[] = {
	{ .compatible = "rockchip,rv1126-pmucru" },
	{ }
};

U_BOOT_DRIVER(rockchip_rv1126_pmucru) = {
	.name		= "rockchip_rv1126_pmucru",
	.id		= UCLASS_CLK,
	.of_match	= rv1126_pmuclk_ids,
	.priv_auto_alloc_size = sizeof(struct rv1126_pmuclk_priv),
	.ofdata_to_platdata = rv1126_pmuclk_ofdata_to_platdata,
	.ops		= &rv1126_pmuclk_ops,
	.bind		= rv1126_pmuclk_bind,
	.probe		= rv1126_pmuclk_probe,
};


static int rv1126_armclk_set_clk(struct rv1126_clk_priv *priv, ulong hz)
{
	struct rv1126_cru *cru = priv->cru;
	const struct rockchip_cpu_rate_table *rate;
	ulong old_rate;

	rate = rockchip_get_cpu_settings(rv1126_cpu_rates, hz);
	if (!rate) {
		printf("%s unsupported rate\n", __func__);
		return -EINVAL;
	}

	/*
	 * set up dependent divisors for DBG and ACLK clocks.
	 */
	old_rate = rockchip_pll_get_rate(&rv1126_pll_clks[APLL],
					 priv->cru, APLL);
	if (old_rate > hz) {
		if (rockchip_pll_set_rate(&rv1126_pll_clks[APLL],
					  priv->cru, APLL, hz))
			return -EINVAL;
		rk_clrsetreg(&cru->clksel_con[1],
			     CORE_DBG_DIV_MASK | CORE_ACLK_DIV_MASK,
			     rate->pclk_div << CORE_DBG_DIV_SHIFT |
			     rate->aclk_div << CORE_ACLK_DIV_SHIFT);
	} else if (old_rate < hz) {
		rk_clrsetreg(&cru->clksel_con[1],
			     CORE_DBG_DIV_MASK | CORE_ACLK_DIV_MASK,
			     rate->pclk_div << CORE_DBG_DIV_SHIFT |
			     rate->aclk_div << CORE_ACLK_DIV_SHIFT);
		if (rockchip_pll_set_rate(&rv1126_pll_clks[APLL],
					  priv->cru, APLL, hz))
			return -EINVAL;
	}

	return 0;
}

static ulong rv1126_pdcore_get_clk(struct rv1126_clk_priv *priv)
{
	struct rv1126_cru *cru = priv->cru;
	u32 con, div;

	con = readl(&cru->clksel_con[0]);
	div = (con & CORE_HCLK_DIV_MASK) >> CORE_HCLK_DIV_SHIFT;

	return DIV_TO_RATE(priv->gpll_hz, div);
}

static ulong rv1126_pdcore_set_clk(struct rv1126_clk_priv *priv, ulong rate)
{
	struct rv1126_cru *cru = priv->cru;
	int src_clk_div;
	src_clk_div = DIV_ROUND_UP(priv->gpll_hz, rate);
	assert(src_clk_div - 1 <= 31);

	rk_clrsetreg(&cru->clksel_con[0], CORE_HCLK_DIV_MASK,
		     (src_clk_div - 1) << CORE_HCLK_DIV_SHIFT);

	return rv1126_pdcore_get_clk(priv);
}

static ulong rv1126_pdbus_get_clk(struct rv1126_clk_priv *priv, ulong clk_id)
{
	struct rv1126_cru *cru = priv->cru;
	u32 con, div, sel, parent;

	switch (clk_id) {
	case ACLK_PDBUS:
		con = readl(&cru->clksel_con[2]);
		div = (con & ACLK_PDBUS_DIV_MASK) >> ACLK_PDBUS_DIV_SHIFT;
		sel = (con & ACLK_PDBUS_SEL_MASK) >> ACLK_PDBUS_SEL_SHIFT;
		if (sel == ACLK_PDBUS_SEL_GPLL)
			parent = priv->gpll_hz;
		else if (sel == ACLK_PDBUS_SEL_CPLL)
			parent = priv->cpll_hz;
		else
			return -ENOENT;
		break;
	case HCLK_PDBUS:
		con = readl(&cru->clksel_con[2]);
		div = (con & HCLK_PDBUS_DIV_MASK) >> HCLK_PDBUS_DIV_SHIFT;
		sel = (con & HCLK_PDBUS_SEL_MASK) >> HCLK_PDBUS_SEL_SHIFT;
		if (sel == HCLK_PDBUS_SEL_GPLL)
			parent = priv->gpll_hz;
		else if (sel == HCLK_PDBUS_SEL_CPLL)
			parent = priv->cpll_hz;
		else
			return -ENOENT;
		break;
	case PCLK_PDBUS:
	case PCLK_WDT:
		con = readl(&cru->clksel_con[3]);
		div = (con & PCLK_PDBUS_DIV_MASK) >> PCLK_PDBUS_DIV_SHIFT;
		sel = (con & PCLK_PDBUS_SEL_MASK) >> PCLK_PDBUS_SEL_SHIFT;
		if (sel == PCLK_PDBUS_SEL_GPLL)
			parent = priv->gpll_hz;
		else if (sel == PCLK_PDBUS_SEL_CPLL)
			parent = priv->cpll_hz;
		else
			return -ENOENT;
		break;
	default:
		return -ENOENT;
	}

	return DIV_TO_RATE(parent, div);
}

static ulong rv1126_pdbus_set_clk(struct rv1126_clk_priv *priv, ulong clk_id,
				  ulong rate)
{
	struct rv1126_cru *cru = priv->cru;
	int src_clk_div, clk_sel;

	switch (clk_id) {
	case ACLK_PDBUS:
		if (CPLL_HZ % rate) {
			src_clk_div = DIV_ROUND_UP(priv->gpll_hz, rate);
			clk_sel = ACLK_PDBUS_SEL_GPLL;
		} else {
			src_clk_div = DIV_ROUND_UP(priv->cpll_hz, rate);
			clk_sel = ACLK_PDBUS_SEL_CPLL;
		}
		assert(src_clk_div - 1 <= 31);
		rk_clrsetreg(&cru->clksel_con[2],
			     ACLK_PDBUS_SEL_MASK | ACLK_PDBUS_DIV_MASK,
			     clk_sel << ACLK_PDBUS_SEL_SHIFT |
			     (src_clk_div - 1) << ACLK_PDBUS_DIV_SHIFT);
		break;
	case HCLK_PDBUS:
		src_clk_div = DIV_ROUND_UP(priv->gpll_hz, rate);
		assert(src_clk_div - 1 <= 31);
		rk_clrsetreg(&cru->clksel_con[2],
			     HCLK_PDBUS_SEL_MASK | HCLK_PDBUS_DIV_MASK,
			     HCLK_PDBUS_SEL_GPLL << HCLK_PDBUS_SEL_SHIFT |
			     (src_clk_div - 1) << HCLK_PDBUS_DIV_SHIFT);
		break;
	case PCLK_PDBUS:
	case PCLK_WDT:
		src_clk_div = DIV_ROUND_UP(priv->gpll_hz, rate);
		assert(src_clk_div - 1 <= 31);
		rk_clrsetreg(&cru->clksel_con[3],
			     PCLK_PDBUS_SEL_MASK | PCLK_PDBUS_DIV_MASK,
			     PCLK_PDBUS_SEL_GPLL << PCLK_PDBUS_SEL_SHIFT |
			     (src_clk_div - 1) << PCLK_PDBUS_DIV_SHIFT);
		break;

	default:
		printf("do not support this pdbus freq\n");
		return -EINVAL;
	}

	return rv1126_pdbus_get_clk(priv, clk_id);
}

static ulong rv1126_pdphp_get_clk(struct rv1126_clk_priv *priv, ulong clk_id)
{
	struct rv1126_cru *cru = priv->cru;
	u32 con, div, parent;

	switch (clk_id) {
	case ACLK_PDPHP:
		con = readl(&cru->clksel_con[53]);
		div = (con & ACLK_PDPHP_DIV_MASK) >> ACLK_PDPHP_DIV_SHIFT;
		parent = priv->gpll_hz;
		break;
	case HCLK_PDPHP:
		con = readl(&cru->clksel_con[53]);
		div = (con & HCLK_PDPHP_DIV_MASK) >> HCLK_PDPHP_DIV_SHIFT;
		parent = priv->gpll_hz;
		break;
	default:
		return -ENOENT;
	}

	return DIV_TO_RATE(parent, div);
}

static ulong rv1126_pdphp_set_clk(struct rv1126_clk_priv *priv, ulong clk_id,
				  ulong rate)
{
	struct rv1126_cru *cru = priv->cru;
	int src_clk_div;

	src_clk_div = DIV_ROUND_UP(priv->gpll_hz, rate);
	assert(src_clk_div - 1 <= 31);

	switch (clk_id) {
	case ACLK_PDPHP:
		rk_clrsetreg(&cru->clksel_con[53],
			     ACLK_PDPHP_SEL_MASK | ACLK_PDPHP_DIV_MASK,
			     ACLK_PDPHP_SEL_GPLL << ACLK_PDPHP_SEL_SHIFT |
			     (src_clk_div - 1) << ACLK_PDPHP_DIV_SHIFT);
		break;
	case HCLK_PDPHP:
		rk_clrsetreg(&cru->clksel_con[53],
			     HCLK_PDPHP_DIV_MASK,
			     (src_clk_div - 1) << HCLK_PDPHP_DIV_SHIFT);
		break;
	default:
		printf("do not support this pdphp freq\n");
		return -EINVAL;
	}

	return rv1126_pdphp_get_clk(priv, clk_id);
}

static ulong rv1126_pdaudio_get_clk(struct rv1126_clk_priv *priv)
{
	struct rv1126_cru *cru = priv->cru;
	u32 con, div;

	con = readl(&cru->clksel_con[26]);
	div = (con & HCLK_PDAUDIO_DIV_MASK) >> HCLK_PDAUDIO_DIV_SHIFT;

	return DIV_TO_RATE(priv->gpll_hz, div);
}

static ulong rv1126_pdaudio_set_clk(struct rv1126_clk_priv *priv, ulong rate)
{
	struct rv1126_cru *cru = priv->cru;
	int src_clk_div;

	src_clk_div = DIV_ROUND_UP(priv->gpll_hz, rate);
	assert(src_clk_div - 1 <= 31);

	rk_clrsetreg(&cru->clksel_con[26], HCLK_PDAUDIO_DIV_MASK,
		     (src_clk_div - 1) << HCLK_PDAUDIO_DIV_SHIFT);

	return rv1126_pdaudio_get_clk(priv);
}

static ulong rv1126_i2c_get_clk(struct rv1126_clk_priv *priv, ulong clk_id)
{
	struct rv1126_cru *cru = priv->cru;
	u32 div, con;

	switch (clk_id) {
	case CLK_I2C1:
		con = readl(&cru->clksel_con[5]);
		div = (con & CLK_I2C1_DIV_MASK) >> CLK_I2C1_DIV_SHIFT;
		break;
	case CLK_I2C3:
		con = readl(&cru->clksel_con[5]);
		div = (con & CLK_I2C3_DIV_MASK) >> CLK_I2C3_DIV_SHIFT;
		break;
	case CLK_I2C4:
		con = readl(&cru->clksel_con[6]);
		div = (con & CLK_I2C4_DIV_MASK) >> CLK_I2C4_DIV_SHIFT;
		break;
	case CLK_I2C5:
		con = readl(&cru->clksel_con[6]);
		div = (con & CLK_I2C5_DIV_MASK) >> CLK_I2C5_DIV_SHIFT;
		break;
	default:
		return -ENOENT;
	}

	return DIV_TO_RATE(priv->gpll_hz, div);
}

static ulong rv1126_i2c_set_clk(struct rv1126_clk_priv *priv, ulong clk_id,
				ulong rate)
{
	struct rv1126_cru *cru = priv->cru;
	int src_clk_div;

	src_clk_div = DIV_ROUND_UP(priv->gpll_hz, rate);
	assert(src_clk_div - 1 <= 127);

	switch (clk_id) {
	case CLK_I2C1:
		rk_clrsetreg(&cru->clksel_con[5], CLK_I2C1_DIV_MASK,
			     (src_clk_div - 1) << CLK_I2C1_DIV_SHIFT);
		break;
	case CLK_I2C3:
		rk_clrsetreg(&cru->clksel_con[5], CLK_I2C3_DIV_MASK,
			     (src_clk_div - 1) << CLK_I2C3_DIV_SHIFT);
		break;
	case CLK_I2C4:
		rk_clrsetreg(&cru->clksel_con[6], CLK_I2C4_DIV_MASK,
			     (src_clk_div - 1) << CLK_I2C4_DIV_SHIFT);
		break;
	case CLK_I2C5:
		rk_clrsetreg(&cru->clksel_con[6], CLK_I2C5_DIV_MASK,
			     (src_clk_div - 1) << CLK_I2C5_DIV_SHIFT);
		break;
	default:
		return -ENOENT;
	}

	return rv1126_i2c_get_clk(priv, clk_id);
}

static ulong rv1126_spi_get_clk(struct rv1126_clk_priv *priv)
{
	struct rv1126_cru *cru = priv->cru;
	u32 div, con;

	con = readl(&cru->clksel_con[8]);
	div = (con & CLK_SPI1_DIV_MASK) >> CLK_SPI1_DIV_SHIFT;

	return DIV_TO_RATE(priv->gpll_hz, div);
}

static ulong rv1126_spi_set_clk(struct rv1126_clk_priv *priv, ulong rate)
{
	struct rv1126_cru *cru = priv->cru;
	int src_clk_div;

	src_clk_div = DIV_ROUND_UP(priv->gpll_hz, rate);
	assert(src_clk_div - 1 <= 127);

	rk_clrsetreg(&cru->clksel_con[8],
		     CLK_SPI1_SEL_MASK | CLK_SPI1_DIV_MASK,
		     CLK_SPI1_SEL_GPLL << CLK_SPI1_SEL_SHIFT |
		     (src_clk_div - 1) << CLK_SPI1_DIV_SHIFT);

	return rv1126_spi_get_clk(priv);
}

static ulong rv1126_pwm_get_clk(struct rv1126_clk_priv *priv)
{
	struct rv1126_cru *cru = priv->cru;
	u32 div, sel, con;

	con = readl(&cru->clksel_con[9]);
	sel = (con & CLK_PWM2_SEL_MASK) >> CLK_PWM2_SEL_SHIFT;
	div = (con & CLK_PWM2_DIV_MASK) >> CLK_PWM2_DIV_SHIFT;
	if (sel == CLK_PWM2_SEL_XIN24M)
		return OSC_HZ;

	return DIV_TO_RATE(priv->gpll_hz, div);
}

static ulong rv1126_pwm_set_clk(struct rv1126_clk_priv *priv, ulong rate)
{
	struct rv1126_cru *cru = priv->cru;
	int src_clk_div;

	if (rate == OSC_HZ) {
		rk_clrsetreg(&cru->clksel_con[9], CLK_PWM2_SEL_MASK,
			     CLK_PWM2_SEL_XIN24M << CLK_PWM2_SEL_SHIFT);
		rk_clrsetreg(&cru->clksel_con[9], CLK_PWM2_DIV_MASK, 0);
	} else {
		src_clk_div = DIV_ROUND_UP(priv->gpll_hz, rate);
		assert(src_clk_div - 1 <= 127);
		rk_clrsetreg(&cru->clksel_con[9], CLK_PWM2_DIV_MASK,
			     (src_clk_div - 1) << CLK_PWM2_DIV_SHIFT);
		rk_clrsetreg(&cru->clksel_con[9], CLK_PWM2_SEL_MASK,
			     CLK_PWM2_SEL_GPLL << CLK_PWM2_SEL_SHIFT);
	}

	return rv1126_pwm_get_clk(priv);
}

static ulong rv1126_saradc_get_clk(struct rv1126_clk_priv *priv)
{
	struct rv1126_cru *cru = priv->cru;
	u32 div, con;

	con = readl(&cru->clksel_con[20]);
	div = (con & CLK_SARADC_DIV_MASK) >> CLK_SARADC_DIV_SHIFT;

	return DIV_TO_RATE(OSC_HZ, div);
}

static ulong rv1126_saradc_set_clk(struct rv1126_clk_priv *priv, ulong rate)
{
	struct rv1126_cru *cru = priv->cru;
	int src_clk_div;

	src_clk_div = DIV_ROUND_UP(OSC_HZ, rate);
	assert(src_clk_div - 1 <= 2047);
	rk_clrsetreg(&cru->clksel_con[20], CLK_SARADC_DIV_MASK,
		     (src_clk_div - 1) << CLK_SARADC_DIV_SHIFT);

	return rv1126_saradc_get_clk(priv);
}

static ulong rv1126_crypto_get_clk(struct rv1126_clk_priv *priv, ulong clk_id)
{
	struct rv1126_cru *cru = priv->cru;
	u32 div, sel, con, parent;

	switch (clk_id) {
	case CLK_CRYPTO_CORE:
		con = readl(&cru->clksel_con[7]);
		div = (con & CLK_CRYPTO_CORE_DIV_MASK) >> CLK_CRYPTO_CORE_DIV_SHIFT;
		sel = (con & CLK_CRYPTO_CORE_SEL_MASK) >> CLK_CRYPTO_CORE_SEL_SHIFT;
		if (sel == CLK_CRYPTO_CORE_SEL_GPLL)
			parent = priv->gpll_hz;
		else if (sel == CLK_CRYPTO_CORE_SEL_CPLL)
			parent = priv->cpll_hz;
		else
			return -ENOENT;
		break;
	case CLK_CRYPTO_PKA:
		con = readl(&cru->clksel_con[7]);
		div = (con & CLK_CRYPTO_PKA_DIV_MASK) >> CLK_CRYPTO_PKA_DIV_SHIFT;
		sel = (con & CLK_CRYPTO_PKA_SEL_MASK) >> CLK_CRYPTO_PKA_SEL_SHIFT;
		if (sel == CLK_CRYPTO_PKA_SEL_GPLL)
			parent = priv->gpll_hz;
		else if (sel == CLK_CRYPTO_PKA_SEL_CPLL)
			parent = priv->cpll_hz;
		else
			return -ENOENT;
		break;
	case ACLK_CRYPTO:
		con = readl(&cru->clksel_con[4]);
		div = (con & ACLK_CRYPTO_DIV_MASK) >> ACLK_CRYPTO_DIV_SHIFT;
		sel = (con & ACLK_CRYPTO_SEL_MASK) >> ACLK_CRYPTO_SEL_SHIFT;
		if (sel == ACLK_CRYPTO_SEL_GPLL)
			parent = priv->gpll_hz;
		else if (sel == ACLK_CRYPTO_SEL_CPLL)
			parent = priv->cpll_hz;
		else
			return -ENOENT;
		break;
	default:
		return -ENOENT;
	}

	return DIV_TO_RATE(parent, div);
}

static ulong rv1126_crypto_set_clk(struct rv1126_clk_priv *priv, ulong clk_id,
				   ulong rate)
{
	struct rv1126_cru *cru = priv->cru;
	int src_clk_div;

	src_clk_div = DIV_ROUND_UP(priv->gpll_hz, rate);
	assert(src_clk_div - 1 <= 31);

	switch (clk_id) {
	case CLK_CRYPTO_CORE:
		rk_clrsetreg(&cru->clksel_con[7],
			     CLK_CRYPTO_CORE_SEL_MASK |
			     CLK_CRYPTO_CORE_DIV_MASK,
			     CLK_CRYPTO_CORE_SEL_GPLL <<
			     CLK_CRYPTO_CORE_SEL_SHIFT |
			     (src_clk_div - 1) << CLK_CRYPTO_CORE_DIV_SHIFT);
		break;
	case CLK_CRYPTO_PKA:
		rk_clrsetreg(&cru->clksel_con[7],
			     CLK_CRYPTO_PKA_SEL_MASK |
			     CLK_CRYPTO_PKA_DIV_MASK,
			     CLK_CRYPTO_PKA_SEL_GPLL <<
			     CLK_CRYPTO_PKA_SEL_SHIFT |
			     (src_clk_div - 1) << CLK_CRYPTO_PKA_DIV_SHIFT);
		break;
	case ACLK_CRYPTO:
		rk_clrsetreg(&cru->clksel_con[4],
			     ACLK_CRYPTO_SEL_MASK | ACLK_CRYPTO_DIV_MASK,
			     ACLK_CRYPTO_SEL_GPLL << ACLK_CRYPTO_SEL_SHIFT |
			     (src_clk_div - 1) << ACLK_CRYPTO_DIV_SHIFT);
		break;
	default:
		return -ENOENT;
	}

	return rv1126_crypto_get_clk(priv, clk_id);
}

static ulong rv1126_mmc_get_clk(struct rv1126_clk_priv *priv, ulong clk_id)
{
	struct rv1126_cru *cru = priv->cru;
	u32 div, sel, con, con_id;

	switch (clk_id) {
	case HCLK_SDMMC:
	case CLK_SDMMC:
		con_id = 55;
		break;
	case HCLK_SDIO:
	case CLK_SDIO:
		con_id = 56;
		break;
	case HCLK_EMMC:
	case CLK_EMMC:
	case SCLK_EMMC_SAMPLE:
		con_id = 57;
		break;
	default:
		return -ENOENT;
	}

	con = readl(&cru->clksel_con[con_id]);
	div = (con & EMMC_DIV_MASK) >> EMMC_DIV_SHIFT;
	sel = (con & EMMC_SEL_MASK) >> EMMC_SEL_SHIFT;
	if (sel == EMMC_SEL_GPLL)
		return DIV_TO_RATE(priv->gpll_hz, div) / 2;
	else if (sel == EMMC_SEL_CPLL)
		return DIV_TO_RATE(priv->cpll_hz, div) / 2;
	else if (sel == EMMC_SEL_XIN24M)
		return DIV_TO_RATE(OSC_HZ, div) / 2;

	return -ENOENT;
}

static ulong rv1126_mmc_set_clk(struct rv1126_clk_priv *priv, ulong clk_id,
				 ulong rate)
{
	struct rv1126_cru *cru = priv->cru;
	int src_clk_div;
	u32 con_id;

	switch (clk_id) {
	case HCLK_SDMMC:
	case CLK_SDMMC:
		con_id = 55;
		break;
	case HCLK_SDIO:
	case CLK_SDIO:
		con_id = 56;
		break;
	case HCLK_EMMC:
	case CLK_EMMC:
		con_id = 57;
		break;
	default:
		return -ENOENT;
	}

	/* Select clk_sdmmc/emmc source from GPLL by default */
	/* mmc clock defaulg div 2 internal, need provide double in cru */
	src_clk_div = DIV_ROUND_UP(priv->gpll_hz / 2, rate);

	if (src_clk_div > 127) {
		/* use 24MHz source for 400KHz clock */
		src_clk_div = DIV_ROUND_UP(OSC_HZ / 2, rate);
		rk_clrsetreg(&cru->clksel_con[con_id],
			     EMMC_SEL_MASK | EMMC_DIV_MASK,
			     EMMC_SEL_XIN24M << EMMC_SEL_SHIFT |
			     (src_clk_div - 1) << EMMC_DIV_SHIFT);
	} else {
		rk_clrsetreg(&cru->clksel_con[con_id],
			     EMMC_SEL_MASK | EMMC_DIV_MASK,
			     EMMC_SEL_GPLL << EMMC_SEL_SHIFT |
			     (src_clk_div - 1) << EMMC_DIV_SHIFT);
	}

	return rv1126_mmc_get_clk(priv, clk_id);
}

static ulong rv1126_sfc_get_clk(struct rv1126_clk_priv *priv)
{
	struct rv1126_cru *cru = priv->cru;
	u32 div, sel, con, parent;

	con = readl(&cru->clksel_con[58]);
	div = (con & SCLK_SFC_DIV_MASK) >> SCLK_SFC_DIV_SHIFT;
	sel = (con & SCLK_SFC_SEL_MASK) >> SCLK_SFC_SEL_SHIFT;
	if (sel == SCLK_SFC_SEL_GPLL)
		parent = priv->gpll_hz;
	else if (sel == SCLK_SFC_SEL_CPLL)
		parent = priv->cpll_hz;
	else
		return -ENOENT;

	return DIV_TO_RATE(parent, div);
}

static ulong rv1126_sfc_set_clk(struct rv1126_clk_priv *priv, ulong rate)
{
	struct rv1126_cru *cru = priv->cru;
	int src_clk_div;

	src_clk_div = DIV_ROUND_UP(priv->gpll_hz, rate);
	rk_clrsetreg(&cru->clksel_con[58],
		     SCLK_SFC_SEL_MASK | SCLK_SFC_DIV_MASK,
		     SCLK_SFC_SEL_GPLL << SCLK_SFC_SEL_SHIFT |
		     (src_clk_div - 1) << SCLK_SFC_DIV_SHIFT);

	return rv1126_sfc_get_clk(priv);
}

static ulong rv1126_nand_get_clk(struct rv1126_clk_priv *priv)
{
	struct rv1126_cru *cru = priv->cru;
	u32 div, sel, con, parent;

	con = readl(&cru->clksel_con[59]);
	div = (con & CLK_NANDC_DIV_MASK) >> CLK_NANDC_DIV_SHIFT;
	sel = (con & CLK_NANDC_SEL_MASK) >> CLK_NANDC_SEL_SHIFT;
	if (sel == CLK_NANDC_SEL_GPLL)
		parent = priv->gpll_hz;
	else if (sel == CLK_NANDC_SEL_CPLL)
		parent = priv->cpll_hz;
	else
		return -ENOENT;

	return DIV_TO_RATE(parent, div);
}

static ulong rv1126_nand_set_clk(struct rv1126_clk_priv *priv, ulong rate)
{
	struct rv1126_cru *cru = priv->cru;
	int src_clk_div;

	src_clk_div = DIV_ROUND_UP(priv->gpll_hz, rate);
	rk_clrsetreg(&cru->clksel_con[59],
		     CLK_NANDC_SEL_MASK | CLK_NANDC_DIV_MASK,
		     CLK_NANDC_SEL_GPLL << CLK_NANDC_SEL_SHIFT |
		     (src_clk_div - 1) << CLK_NANDC_DIV_SHIFT);

	return rv1126_nand_get_clk(priv);
}

static ulong rv1126_aclk_vop_get_clk(struct rv1126_clk_priv *priv)
{
	struct rv1126_cru *cru = priv->cru;
	u32 div, sel, con, parent;

	con = readl(&cru->clksel_con[45]);
	div = (con & ACLK_PDVO_DIV_MASK) >> ACLK_PDVO_DIV_SHIFT;
	sel = (con & ACLK_PDVO_SEL_MASK) >> ACLK_PDVO_SEL_SHIFT;
	if (sel == ACLK_PDVO_SEL_GPLL)
		parent = priv->gpll_hz;
	else if (sel == ACLK_PDVO_SEL_CPLL)
		parent = priv->cpll_hz;
	else
		return -ENOENT;

	return DIV_TO_RATE(parent, div);
}

static ulong rv1126_aclk_vop_set_clk(struct rv1126_clk_priv *priv, ulong rate)
{
	struct rv1126_cru *cru = priv->cru;
	int src_clk_div;

	src_clk_div = DIV_ROUND_UP(priv->gpll_hz, rate);
	assert(src_clk_div - 1 <= 31);
	rk_clrsetreg(&cru->clksel_con[45],
		     ACLK_PDVO_SEL_MASK | ACLK_PDVO_DIV_MASK,
		     ACLK_PDVO_SEL_GPLL << ACLK_PDVO_SEL_SHIFT |
		     (src_clk_div - 1) << ACLK_PDVO_DIV_SHIFT);

	return rv1126_aclk_vop_get_clk(priv);
}

static ulong rv1126_dclk_vop_get_clk(struct rv1126_clk_priv *priv)
{
	struct rv1126_cru *cru = priv->cru;
	u32 div, sel, con, parent;

	con = readl(&cru->clksel_con[47]);
	div = (con & DCLK_VOP_DIV_MASK) >> DCLK_VOP_DIV_SHIFT;
	sel = (con & DCLK_VOP_SEL_MASK) >> DCLK_VOP_SEL_SHIFT;
	if (sel == DCLK_VOP_SEL_GPLL)
		parent = priv->gpll_hz;
	else if (sel == DCLK_VOP_SEL_CPLL)
		parent = priv->cpll_hz;
	else
		return -ENOENT;

	return DIV_TO_RATE(parent, div);
}

static ulong rv1126_dclk_vop_set_clk(struct rv1126_clk_priv *priv, ulong rate)
{
	struct rv1126_cru *cru = priv->cru;
	ulong pll_rate, now, best_rate = 0;
	u32 i, div, best_div = 0, best_sel = 0;

	for (i = 0; i <= DCLK_VOP_SEL_CPLL; i++) {
		switch (i) {
		case DCLK_VOP_SEL_GPLL:
			pll_rate = priv->gpll_hz;
			break;
		case DCLK_VOP_SEL_CPLL:
			pll_rate = priv->cpll_hz;
			break;
		default:
			printf("do not support this vop pll sel\n");
			return -EINVAL;
		}

		div = DIV_ROUND_UP(pll_rate, rate);
		if (div > 255)
			continue;
		now = pll_rate / div;
		if (abs(rate - now) < abs(rate - best_rate)) {
			best_rate = now;
			best_div = div;
			best_sel = i;
		}
		debug("pll_rate=%lu, best_rate=%lu, best_div=%u, best_sel=%u\n",
		      pll_rate, best_rate, best_div, best_sel);
	}

	if (best_rate) {
		rk_clrsetreg(&cru->clksel_con[47],
			     DCLK_VOP_SEL_MASK | DCLK_VOP_DIV_MASK,
			     best_sel << DCLK_VOP_SEL_SHIFT |
			     (best_div - 1) << DCLK_VOP_DIV_SHIFT);
	} else {
		printf("do not support this vop freq %lu\n", rate);
		return -EINVAL;
	}


	return rv1126_dclk_vop_get_clk(priv);
}

static ulong rv1126_scr1_get_clk(struct rv1126_clk_priv *priv)
{
	struct rv1126_cru *cru = priv->cru;
	u32 div, sel, con, parent;

	con = readl(&cru->clksel_con[3]);
	div = (con & CLK_SCR1_DIV_MASK) >> CLK_SCR1_DIV_SHIFT;
	sel = (con & CLK_SCR1_SEL_MASK) >> CLK_SCR1_SEL_SHIFT;
	if (sel == CLK_SCR1_SEL_GPLL)
		parent = priv->gpll_hz;
	else if (sel == CLK_SCR1_SEL_CPLL)
		parent = priv->cpll_hz;
	else
		return -ENOENT;

	return DIV_TO_RATE(parent, div);
}

static ulong rv1126_scr1_set_clk(struct rv1126_clk_priv *priv, ulong rate)
{
	struct rv1126_cru *cru = priv->cru;
	int src_clk_div;

	src_clk_div = DIV_ROUND_UP(priv->gpll_hz, rate);
	assert(src_clk_div - 1 <= 31);
	rk_clrsetreg(&cru->clksel_con[3],
		     CLK_SCR1_SEL_MASK | CLK_SCR1_DIV_MASK,
		     CLK_SCR1_SEL_GPLL << CLK_SCR1_SEL_SHIFT |
		     (src_clk_div - 1) << CLK_SCR1_DIV_SHIFT);

	return rv1126_scr1_get_clk(priv);
}

static ulong rv1126_gmac_src_get_clk(struct rv1126_clk_priv *priv)
{
	struct rv1126_cru *cru = priv->cru;
	u32 div, sel, con, parent;

	con = readl(&cru->clksel_con[63]);
	div = (con & CLK_GMAC_SRC_DIV_MASK) >> CLK_GMAC_SRC_DIV_SHIFT;
	sel = (con & CLK_GMAC_SRC_SEL_MASK) >> CLK_GMAC_SRC_SEL_SHIFT;
	if (sel == CLK_GMAC_SRC_SEL_CPLL)
		parent = priv->cpll_hz;
	else if (sel == CLK_GMAC_SRC_SEL_GPLL)
		parent = priv->gpll_hz;
	else
		return -ENOENT;

	return DIV_TO_RATE(parent, div);
}

static ulong rv1126_gmac_src_set_clk(struct rv1126_clk_priv *priv, ulong rate)
{
	struct rv1126_cru *cru = priv->cru;
	int src_clk_div;

	src_clk_div = DIV_ROUND_UP(priv->cpll_hz, rate);
	assert(src_clk_div - 1 <= 31);
	rk_clrsetreg(&cru->clksel_con[63],
		     CLK_GMAC_SRC_SEL_MASK | CLK_GMAC_SRC_DIV_MASK,
		     CLK_GMAC_SRC_SEL_CPLL << CLK_GMAC_SRC_SEL_SHIFT |
		     (src_clk_div - 1) << CLK_GMAC_SRC_DIV_SHIFT);

	return rv1126_gmac_src_get_clk(priv);
}

static ulong rv1126_gmac_out_get_clk(struct rv1126_clk_priv *priv)
{
	struct rv1126_cru *cru = priv->cru;
	u32 div, sel, con, parent;

	con = readl(&cru->clksel_con[61]);
	div = (con & CLK_GMAC_OUT_DIV_MASK) >> CLK_GMAC_OUT_DIV_SHIFT;
	sel = (con & CLK_GMAC_OUT_SEL_MASK) >> CLK_GMAC_OUT_SEL_SHIFT;
	if (sel == CLK_GMAC_OUT_SEL_CPLL)
		parent = priv->cpll_hz;
	else if (sel == CLK_GMAC_OUT_SEL_GPLL)
		parent = priv->gpll_hz;
	else
		return -ENOENT;

	return DIV_TO_RATE(parent, div);
}

static ulong rv1126_gmac_out_set_clk(struct rv1126_clk_priv *priv, ulong rate)
{
	struct rv1126_cru *cru = priv->cru;
	int src_clk_div;

	src_clk_div = DIV_ROUND_UP(priv->cpll_hz, rate);
	assert(src_clk_div - 1 <= 31);
	rk_clrsetreg(&cru->clksel_con[61],
		     CLK_GMAC_OUT_SEL_MASK | CLK_GMAC_OUT_DIV_MASK,
		     CLK_GMAC_OUT_SEL_CPLL << CLK_GMAC_OUT_SEL_SHIFT |
		     (src_clk_div - 1) << CLK_GMAC_OUT_DIV_SHIFT);

	return rv1126_gmac_out_get_clk(priv);
}

static ulong rv1126_gmac_tx_rx_set_clk(struct rv1126_clk_priv *priv, ulong rate)
{
	struct rv1126_cru *cru = priv->cru;
	u32 con, sel, div_sel;

	con = readl(&cru->gmac_con);
	sel = (con & GMAC_MODE_SEL_MASK) >> GMAC_MODE_SEL_SHIFT;

	if (sel == GMAC_RGMII_MODE) {
		if (rate == 2500000)
			div_sel = RGMII_CLK_DIV50;
		else if (rate == 25000000)
			div_sel = RGMII_CLK_DIV5;
		else
			div_sel = RGMII_CLK_DIV0;
		rk_clrsetreg(&cru->gmac_con, RGMII_CLK_SEL_MASK,
			     div_sel << RGMII_CLK_SEL_SHIFT);
	} else if (sel == GMAC_RMII_MODE) {
		if (rate == 2500000)
			div_sel = RMII_CLK_DIV20;
		else
			div_sel = RMII_CLK_DIV2;
		rk_clrsetreg(&cru->gmac_con, RMII_CLK_SEL_MASK,
			     div_sel << RMII_CLK_SEL_SHIFT);
	}

	return 0;
}

static ulong rv1126_pclk_gmac_get_clk(struct rv1126_clk_priv *priv)
{
	struct rv1126_cru *cru = priv->cru;
	u32 div, con, parent;

	parent = rv1126_pdphp_get_clk(priv, ACLK_PDPHP);

	con = readl(&cru->clksel_con[63]);
	div = (con & PCLK_GMAC_DIV_MASK) >> PCLK_GMAC_DIV_SHIFT;

	return DIV_TO_RATE(parent, div);
}

#if defined(CONFIG_SPL_BUILD) && defined(CONFIG_SPL_KERNEL_BOOT)
static ulong rv1126_clk_mipicsi_out_get_clk(struct rv1126_clk_priv *priv)
{
	struct rv1126_cru *cru = priv->cru;
	u32 div, fracdiv, sel, con, n, m, parent = priv->gpll_hz;

	con = readl(&cru->clksel_con[73]);
	div = (con & MIPICSI_OUT_DIV_MASK) >> MIPICSI_OUT_DIV_SHIFT;
	sel = (con & MIPICSI_OUT_SEL_MASK) >> MIPICSI_OUT_SEL_SHIFT;
	if (sel == MIPICSI_OUT_SEL_XIN24M) {
		return OSC_HZ;
	} else if (sel == MIPICSI_OUT_SEL_FRACDIV) {
		parent = DIV_TO_RATE(parent, div);
		fracdiv = readl(&cru->clksel_con[74]);
		n = (fracdiv & 0xffff0000) >> 16;
		m = fracdiv & 0xffff;
		return parent * n / m;
	}

	return DIV_TO_RATE(parent, div);
}

static ulong rv1126_clk_mipicsi_out_set_clk(struct rv1126_clk_priv *priv,
					    ulong rate)
{	struct rv1126_cru *cru = priv->cru;
	int src_clk_div;

	if (rate == OSC_HZ) {
		rk_clrsetreg(&cru->clksel_con[73], MIPICSI_OUT_SEL_MASK,
			     MIPICSI_OUT_SEL_XIN24M << MIPICSI_OUT_SEL_SHIFT);
	} else if (rate == 27000000) {
		src_clk_div = DIV_ROUND_UP(priv->gpll_hz, 297000000);
		rk_clrsetreg(&cru->clksel_con[73], MIPICSI_OUT_DIV_MASK,
			     (src_clk_div - 1) << MIPICSI_OUT_DIV_SHIFT);
		rk_clrsetreg(&cru->clksel_con[73], MIPICSI_OUT_SEL_MASK,
			     MIPICSI_OUT_SEL_FRACDIV << MIPICSI_OUT_SEL_SHIFT);
		writel(4 << 16 | 44, &cru->clksel_con[74]);
	} else {
		src_clk_div = DIV_ROUND_UP(priv->gpll_hz, rate);
		assert(src_clk_div - 1 <= 31);
		rk_clrsetreg(&cru->clksel_con[73], MIPICSI_OUT_DIV_MASK,
			     (src_clk_div - 1) << MIPICSI_OUT_DIV_SHIFT);
		rk_clrsetreg(&cru->clksel_con[73], MIPICSI_OUT_SEL_MASK,
			     MIPICSI_OUT_SEL_DIV << MIPICSI_OUT_SEL_SHIFT);
	}

	return rv1126_clk_mipicsi_out_get_clk(priv);
}

static ulong rv1126_clk_pdvi_ispp_get_clk(struct rv1126_clk_priv *priv,
					  ulong clk_id)
{
	struct rv1126_cru *cru = priv->cru;
	u32 div, sel, con, parent, con_id;

	switch (clk_id) {
	case ACLK_PDVI:
		con_id = 49;
		break;
	case ACLK_PDISPP:
		con_id = 68;
		break;
	case CLK_ISPP:
		con_id = 69;
		break;
	default:
		return -ENOENT;
	}

	con = readl(&cru->clksel_con[con_id]);
	div = (con & ACLK_PDVI_DIV_MASK) >> ACLK_PDVI_DIV_SHIFT;
	sel = (con & ACLK_PDVI_SEL_MASK) >> ACLK_PDVI_SEL_SHIFT;
	if (sel == ACLK_PDVI_SEL_GPLL)
		parent = priv->gpll_hz;
	else if (sel == ACLK_PDVI_SEL_CPLL)
		parent = priv->cpll_hz;
	else if (sel == ACLK_PDVI_SEL_HPLL)
		parent = priv->hpll_hz;
	else
		return -ENOENT;

	return DIV_TO_RATE(parent, div);
}

static ulong rv1126_clk_pdvi_ispp_set_clk(struct rv1126_clk_priv *priv,
					  ulong clk_id, ulong rate)
{
	struct rv1126_cru *cru = priv->cru;
	u32 parent, sel, src_clk_div, con_id;

	switch (clk_id) {
	case ACLK_PDVI:
		con_id = 49;
		break;
	case ACLK_PDISPP:
		con_id = 68;
		break;
	case CLK_ISPP:
		con_id = 69;
		break;
	default:
		return -ENOENT;
	}

	if (!(priv->cpll_hz % rate)) {
		parent = priv->cpll_hz;
		sel = ACLK_PDVI_SEL_CPLL;
	} else if (!(priv->hpll_hz % rate)) {
		parent = priv->hpll_hz;
		sel = ACLK_PDVI_SEL_HPLL;
	} else {
		parent = priv->gpll_hz;
		sel = ACLK_PDVI_SEL_GPLL;
	}

	src_clk_div = DIV_ROUND_UP(parent, rate);
	assert(src_clk_div - 1 <= 31);
	rk_clrsetreg(&cru->clksel_con[con_id],
		     ACLK_PDVI_SEL_MASK | ACLK_PDVI_DIV_MASK,
		     sel << ACLK_PDVI_SEL_SHIFT |
		     (src_clk_div - 1) << ACLK_PDVI_DIV_SHIFT);

	return rv1126_clk_pdvi_ispp_get_clk(priv, clk_id);
}

static ulong rv1126_clk_isp_get_clk(struct rv1126_clk_priv *priv)
{
	struct rv1126_cru *cru = priv->cru;
	u32 div, sel, con, parent;

	con = readl(&cru->clksel_con[50]);
	div = (con & CLK_ISP_DIV_MASK) >> CLK_ISP_DIV_SHIFT;
	sel = (con & CLK_ISP_SEL_MASK) >> CLK_ISP_SEL_SHIFT;
	if (sel == CLK_ISP_SEL_GPLL)
		parent = priv->gpll_hz;
	else if (sel == CLK_ISP_SEL_CPLL)
		parent = priv->cpll_hz;
	else if (sel == CLK_ISP_SEL_HPLL)
		parent = priv->hpll_hz;
	else
		return -ENOENT;

	return DIV_TO_RATE(parent, div);
}

static ulong rv1126_clk_isp_set_clk(struct rv1126_clk_priv *priv, ulong rate)
{
	struct rv1126_cru *cru = priv->cru;
	u32 parent, sel, src_clk_div;

	if (!(priv->cpll_hz % rate)) {
		parent = priv->cpll_hz;
		sel = CLK_ISP_SEL_CPLL;
	} else if (!(priv->hpll_hz % rate)) {
		parent = priv->hpll_hz;
		sel = CLK_ISP_SEL_HPLL;
	} else {
		parent = priv->gpll_hz;
		sel = CLK_ISP_SEL_GPLL;
	}

	src_clk_div = DIV_ROUND_UP(parent, rate);
	assert(src_clk_div - 1 <= 31);
	rk_clrsetreg(&cru->clksel_con[50],
		     CLK_ISP_SEL_MASK | CLK_ISP_DIV_MASK,
		     sel << CLK_ISP_SEL_SHIFT |
		     (src_clk_div - 1) << CLK_ISP_DIV_SHIFT);

	return rv1126_clk_isp_get_clk(priv);
}
#endif

static ulong rv1126_dclk_decom_get_clk(struct rv1126_clk_priv *priv)
{
	struct rv1126_cru *cru = priv->cru;
	u32 div, sel, con, parent;

	con = readl(&cru->clksel_con[25]);
	div = (con & DCLK_DECOM_DIV_MASK) >> DCLK_DECOM_DIV_SHIFT;
	sel = (con & DCLK_DECOM_SEL_MASK) >> DCLK_DECOM_SEL_SHIFT;
	if (sel == DCLK_DECOM_SEL_GPLL)
		parent = priv->gpll_hz;
	else if (sel == DCLK_DECOM_SEL_CPLL)
		parent = priv->cpll_hz;
	else
		return -ENOENT;

	return DIV_TO_RATE(parent, div);
}

static ulong rv1126_dclk_decom_set_clk(struct rv1126_clk_priv *priv, ulong rate)
{
	struct rv1126_cru *cru = priv->cru;
	u32 src_clk_div;

	src_clk_div = DIV_ROUND_UP(priv->gpll_hz, rate);
	assert(src_clk_div - 1 <= 127);
	rk_clrsetreg(&cru->clksel_con[25],
		     DCLK_DECOM_SEL_MASK | DCLK_DECOM_DIV_MASK,
		     DCLK_DECOM_SEL_GPLL << DCLK_DECOM_SEL_SHIFT |
		     (src_clk_div - 1) << DCLK_DECOM_DIV_SHIFT);

	return rv1126_dclk_decom_get_clk(priv);
}

static ulong rv1126_clk_get_rate(struct clk *clk)
{
	struct rv1126_clk_priv *priv = dev_get_priv(clk->dev);
	ulong rate = 0;

	if (!priv->gpll_hz) {
		printf("%s gpll=%lu\n", __func__, priv->gpll_hz);
		return -ENOENT;
	}

	switch (clk->id) {
	case PLL_APLL:
	case ARMCLK:
		rate = rockchip_pll_get_rate(&rv1126_pll_clks[APLL], priv->cru,
					     APLL);
		break;
	case PLL_CPLL:
		rate = rockchip_pll_get_rate(&rv1126_pll_clks[CPLL], priv->cru,
					     CPLL);
		break;
	case PLL_HPLL:
		rate = rockchip_pll_get_rate(&rv1126_pll_clks[HPLL], priv->cru,
					     HPLL);
		break;
	case PLL_DPLL:
		rate = rockchip_pll_get_rate(&rv1126_pll_clks[DPLL], priv->cru,
					     DPLL);
		break;
	case HCLK_PDCORE_NIU:
		rate = rv1126_pdcore_get_clk(priv);
		break;
	case ACLK_PDBUS:
	case HCLK_PDBUS:
	case PCLK_PDBUS:
	case PCLK_WDT:
		rate = rv1126_pdbus_get_clk(priv, clk->id);
		break;
	case ACLK_PDPHP:
	case HCLK_PDPHP:
		rate = rv1126_pdphp_get_clk(priv, clk->id);
		break;
	case HCLK_PDAUDIO:
		rate = rv1126_pdaudio_get_clk(priv);
		break;
	case CLK_I2C1:
	case CLK_I2C3:
	case CLK_I2C4:
	case CLK_I2C5:
		rate = rv1126_i2c_get_clk(priv, clk->id);
		break;
	case CLK_SPI1:
		rate = rv1126_spi_get_clk(priv);
		break;
	case CLK_PWM2:
		rate = rv1126_pwm_get_clk(priv);
		break;
	case CLK_SARADC:
		rate = rv1126_saradc_get_clk(priv);
		break;
	case CLK_CRYPTO_CORE:
	case CLK_CRYPTO_PKA:
	case ACLK_CRYPTO:
		rate = rv1126_crypto_get_clk(priv, clk->id);
		break;
	case CLK_SDMMC:
	case HCLK_SDMMC:
	case CLK_SDIO:
	case HCLK_SDIO:
	case CLK_EMMC:
	case HCLK_EMMC:
	case SCLK_EMMC_SAMPLE:
		rate = rv1126_mmc_get_clk(priv, clk->id);
		break;
	case SCLK_SFC:
		rate = rv1126_sfc_get_clk(priv);
		break;
	case CLK_NANDC:
		rate = rv1126_nand_get_clk(priv);
		break;
	case ACLK_PDVO:
	case ACLK_VOP:
		rate = rv1126_aclk_vop_get_clk(priv);
		break;
	case DCLK_VOP:
		rate = rv1126_dclk_vop_get_clk(priv);
		break;
	case CLK_SCR1_CORE:
		rate = rv1126_scr1_get_clk(priv);
		break;
	case CLK_GMAC_SRC:
		rate = rv1126_gmac_src_get_clk(priv);
		break;
	case CLK_GMAC_ETHERNET_OUT:
		rate = rv1126_gmac_out_get_clk(priv);
		break;
	case PCLK_GMAC:
		rate = rv1126_pclk_gmac_get_clk(priv);
		break;
#if defined(CONFIG_SPL_BUILD) && defined(CONFIG_SPL_KERNEL_BOOT)
	case CLK_MIPICSI_OUT:
		rate = rv1126_clk_mipicsi_out_get_clk(priv);
		break;
	case CLK_ISP:
		rate = rv1126_clk_isp_get_clk(priv);
		break;
	case ACLK_PDVI:
	case ACLK_PDISPP:
	case CLK_ISPP:
		rate = rv1126_clk_pdvi_ispp_get_clk(priv, clk->id);
		break;
#endif
	case DCLK_DECOM:
		rate = rv1126_dclk_decom_get_clk(priv);
		break;
	default:
		return -ENOENT;
	}

	return rate;
};

static ulong rv1126_clk_set_rate(struct clk *clk, ulong rate)
{
	struct rv1126_clk_priv *priv = dev_get_priv(clk->dev);
	ulong ret = 0;

	if (!priv->gpll_hz) {
		printf("%s gpll=%lu\n", __func__, priv->gpll_hz);
		return -ENOENT;
	}

	switch (clk->id) {
	case PLL_APLL:
	case ARMCLK:
		if (priv->armclk_hz)
			rv1126_armclk_set_clk(priv, rate);
		priv->armclk_hz = rate;
		break;
	case PLL_CPLL:
		ret = rockchip_pll_set_rate(&rv1126_pll_clks[CPLL], priv->cru,
					    CPLL, rate);
		break;
	case PLL_HPLL:
		ret = rockchip_pll_set_rate(&rv1126_pll_clks[HPLL], priv->cru,
					    HPLL, rate);
		break;
	case ACLK_PDBUS:
	case HCLK_PDBUS:
	case PCLK_PDBUS:
	case PCLK_WDT:
		ret = rv1126_pdbus_set_clk(priv, clk->id, rate);
		break;
	case ACLK_PDPHP:
	case HCLK_PDPHP:
		ret = rv1126_pdphp_set_clk(priv, clk->id, rate);
		break;
	case HCLK_PDCORE_NIU:
		ret = rv1126_pdcore_set_clk(priv, rate);
		break;
	case HCLK_PDAUDIO:
		ret = rv1126_pdaudio_set_clk(priv, rate);
		break;
	case CLK_I2C1:
	case CLK_I2C3:
	case CLK_I2C4:
	case CLK_I2C5:
		ret = rv1126_i2c_set_clk(priv, clk->id, rate);
		break;
	case CLK_SPI1:
		ret = rv1126_spi_set_clk(priv, rate);
		break;
	case CLK_PWM2:
		ret = rv1126_pwm_set_clk(priv, rate);
		break;
	case CLK_SARADC:
		ret = rv1126_saradc_set_clk(priv, rate);
		break;
	case CLK_CRYPTO_CORE:
	case CLK_CRYPTO_PKA:
	case ACLK_CRYPTO:
		ret = rv1126_crypto_set_clk(priv, clk->id, rate);
		break;
	case CLK_SDMMC:
	case HCLK_SDMMC:
	case CLK_SDIO:
	case HCLK_SDIO:
	case CLK_EMMC:
	case HCLK_EMMC:
		ret = rv1126_mmc_set_clk(priv, clk->id, rate);
		break;
	case SCLK_SFC:
		ret = rv1126_sfc_set_clk(priv, rate);
		break;
	case CLK_NANDC:
		ret = rv1126_nand_set_clk(priv, rate);
		break;
	case ACLK_PDVO:
	case ACLK_VOP:
		ret = rv1126_aclk_vop_set_clk(priv, rate);
		break;
	case DCLK_VOP:
		ret = rv1126_dclk_vop_set_clk(priv, rate);
		break;
	case CLK_SCR1_CORE:
		ret = rv1126_scr1_set_clk(priv, rate);
		break;
	case CLK_GMAC_SRC:
		ret = rv1126_gmac_src_set_clk(priv, rate);
		break;
	case CLK_GMAC_ETHERNET_OUT:
		ret = rv1126_gmac_out_set_clk(priv, rate);
		break;
	case CLK_GMAC_TX_RX:
		ret = rv1126_gmac_tx_rx_set_clk(priv, rate);
		break;
#if defined(CONFIG_SPL_BUILD) && defined(CONFIG_SPL_KERNEL_BOOT)
	case CLK_MIPICSI_OUT:
		ret = rv1126_clk_mipicsi_out_set_clk(priv, rate);
		break;
	case CLK_ISP:
		ret = rv1126_clk_isp_set_clk(priv, rate);
		break;
	case ACLK_PDVI:
	case ACLK_PDISPP:
	case CLK_ISPP:
		ret = rv1126_clk_pdvi_ispp_set_clk(priv, clk->id, rate);
		break;
#endif
	case DCLK_DECOM:
		ret = rv1126_dclk_decom_set_clk(priv, rate);
		break;
	default:
		return -ENOENT;
	}

	return ret;
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

int rv1126_mmc_get_phase(struct clk *clk)
{
	struct rv1126_clk_priv *priv = dev_get_priv(clk->dev);
	struct rv1126_cru *cru = priv->cru;
	u32 raw_value, delay_num;
	u16 degrees = 0;
	ulong rate;

	rate = rv1126_clk_get_rate(clk);
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

int rv1126_mmc_set_phase(struct clk *clk, u32 degrees)
{
	struct rv1126_clk_priv *priv = dev_get_priv(clk->dev);
	struct rv1126_cru *cru = priv->cru;
	u8 nineties, remainder, delay_num;
	u32 raw_value, delay;
	ulong rate;

	rate = rv1126_clk_get_rate(clk);
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
	      degrees, delay_num, raw_value, rv1126_mmc_get_phase(clk));

	return 0;
}

static int rv1126_clk_get_phase(struct clk *clk)
{
	int ret;

	debug("%s %ld\n", __func__, clk->id);
	switch (clk->id) {
	case SCLK_EMMC_SAMPLE:
	case SCLK_SDMMC_SAMPLE:
	case SCLK_SDIO_SAMPLE:
		ret = rv1126_mmc_get_phase(clk);
		break;
	default:
		return -ENOENT;
	}

	return ret;
}

static int rv1126_clk_set_phase(struct clk *clk, int degrees)
{
	int ret;

	debug("%s %ld\n", __func__, clk->id);
	switch (clk->id) {
	case SCLK_EMMC_SAMPLE:
	case SCLK_SDMMC_SAMPLE:
	case SCLK_SDIO_SAMPLE:
		ret = rv1126_mmc_set_phase(clk, degrees);
		break;
	default:
		return -ENOENT;
	}

	return ret;
}

#if CONFIG_IS_ENABLED(OF_CONTROL) && !CONFIG_IS_ENABLED(OF_PLATDATA)
static int rv1126_gmac_src_set_parent(struct clk *clk, struct clk *parent)
{
	struct rv1126_clk_priv *priv = dev_get_priv(clk->dev);
	struct rv1126_grf *grf = priv->grf;

	if (parent->id == CLK_GMAC_SRC_M0)
		rk_clrsetreg(&grf->iofunc_con1, GMAC_SRC_SEL_MASK,
			     GMAC_SRC_SEL_M0 << GMAC_SRC_SEL_SHIFT);
	else if(parent->id == CLK_GMAC_SRC_M1)
		rk_clrsetreg(&grf->iofunc_con1, GMAC_SRC_SEL_MASK,
			     GMAC_SRC_SEL_M1 << GMAC_SRC_SEL_SHIFT);

	return 0;
}

static int rv1126_gmac_src_m0_set_parent(struct clk *clk, struct clk *parent)
{
	struct rv1126_clk_priv *priv = dev_get_priv(clk->dev);
	struct rv1126_cru *cru = priv->cru;

	if (parent->id == CLK_GMAC_DIV)
		rk_clrsetreg(&cru->gmac_con, GMAC_SRC_M0_SEL_MASK,
			     GMAC_SRC_M0_SEL_INT << GMAC_SRC_M0_SEL_SHIFT);
	else
		rk_clrsetreg(&cru->gmac_con, GMAC_SRC_M0_SEL_MASK,
			     GMAC_SRC_M0_SEL_EXT << GMAC_SRC_M0_SEL_SHIFT);

	return 0;
}

static int rv1126_gmac_src_m1_set_parent(struct clk *clk, struct clk *parent)
{
	struct rv1126_clk_priv *priv = dev_get_priv(clk->dev);
	struct rv1126_cru *cru = priv->cru;

	if (parent->id == CLK_GMAC_DIV)
		rk_clrsetreg(&cru->gmac_con, GMAC_SRC_M1_SEL_MASK,
			     GMAC_SRC_M1_SEL_INT << GMAC_SRC_M1_SEL_SHIFT);
	else
		rk_clrsetreg(&cru->gmac_con, GMAC_SRC_M1_SEL_MASK,
			     GMAC_SRC_M1_SEL_EXT << GMAC_SRC_M1_SEL_SHIFT);

	return 0;
}

static int rv1126_gmac_tx_rx_set_parent(struct clk *clk, struct clk *parent)
{
	struct rv1126_clk_priv *priv = dev_get_priv(clk->dev);
	struct rv1126_cru *cru = priv->cru;

	if (parent->id == RGMII_MODE_CLK)
		rk_clrsetreg(&cru->gmac_con, GMAC_MODE_SEL_MASK,
			     GMAC_RGMII_MODE << GMAC_MODE_SEL_SHIFT);
	else
		rk_clrsetreg(&cru->gmac_con, GMAC_MODE_SEL_MASK,
			     GMAC_RMII_MODE << GMAC_MODE_SEL_SHIFT);

	return 0;
}

static int rv1126_clk_set_parent(struct clk *clk, struct clk *parent)
{
	switch (clk->id) {
	case CLK_GMAC_SRC:
		return rv1126_gmac_src_set_parent(clk, parent);
	case CLK_GMAC_SRC_M0:
		return rv1126_gmac_src_m0_set_parent(clk, parent);
	case CLK_GMAC_SRC_M1:
		return rv1126_gmac_src_m1_set_parent(clk, parent);
	case CLK_GMAC_TX_RX:
		return rv1126_gmac_tx_rx_set_parent(clk, parent);
	default:
		return -ENOENT;
	}

	return 0;
}
#endif

static struct clk_ops rv1126_clk_ops = {
	.get_rate = rv1126_clk_get_rate,
	.set_rate = rv1126_clk_set_rate,
	.get_phase = rv1126_clk_get_phase,
	.set_phase = rv1126_clk_set_phase,
#if CONFIG_IS_ENABLED(OF_CONTROL) && !CONFIG_IS_ENABLED(OF_PLATDATA)
	.set_parent = rv1126_clk_set_parent,
#endif
};

static ulong rv1126_gpll_set_rate(struct rv1126_clk_priv *priv,
				  struct rv1126_pmuclk_priv *pmu_priv,
				  ulong rate)
{
	ulong emmc_rate, sfc_rate, nandc_rate;
	bool restore = false;

	if (priv->gpll_hz != OSC_HZ) {
		emmc_rate = rv1126_mmc_get_clk(priv, CLK_EMMC);
		sfc_rate = rv1126_sfc_get_clk(priv);
		nandc_rate = rv1126_nand_get_clk(priv);
		debug("%s emmc=%lu, sfc=%lu, nandc=%lu\n", __func__,
		      emmc_rate, sfc_rate, nandc_rate);
		restore = true;
	}

	/*
	 * the child div is big enough for gpll 1188MHz,
	 * even maskrom has change some clocks.
	 */
	if (rockchip_pll_set_rate(&rv1126_pll_clks[GPLL],
				  pmu_priv->pmucru, GPLL, rate))
		return -EINVAL;
	pmu_priv->gpll_hz = rate;
	priv->gpll_hz = rate;

	if (restore) {
		rv1126_mmc_set_clk(priv, CLK_EMMC, emmc_rate);
		rv1126_sfc_set_clk(priv,  sfc_rate);
		rv1126_nand_set_clk(priv, nandc_rate);
	}

	return 0;
}

static int rv1126_gpll_set_clk(struct rv1126_clk_priv *priv, ulong rate)
{
	struct udevice *pmucru_dev;
	struct rv1126_pmuclk_priv *pmu_priv;
	int ret;

	ret = uclass_get_device_by_driver(UCLASS_CLK,
					  DM_GET_DRIVER(rockchip_rv1126_pmucru),
					  &pmucru_dev);
	if (ret) {
		printf("%s: could not find pmucru device\n", __func__);
		return ret;
	}
	pmu_priv = dev_get_priv(pmucru_dev);
	priv->gpll_hz = pmu_priv->gpll_hz;

	if (rv1126_gpll_set_rate(priv, pmu_priv, rate)) {
		printf("%s: failed to set gpll rate %lu\n", __func__, rate);
		return -EINVAL;
	}

	rv1126_pdpmu_set_pmuclk(pmu_priv, PCLK_PDPMU_HZ);
	rv1126_rtc32k_set_pmuclk(pmu_priv, CLK_OSC0_DIV_HZ);

	return 0;
}

static void rv1126_clk_init(struct rv1126_clk_priv *priv)
{
	int ret;

	priv->sync_kernel = false;
	if (!priv->armclk_enter_hz) {
		priv->armclk_enter_hz =
			rockchip_pll_get_rate(&rv1126_pll_clks[APLL],
					      priv->cru, APLL);
		priv->armclk_init_hz = priv->armclk_enter_hz ;
	}

	if (priv->armclk_init_hz != APLL_HZ) {
		ret = rv1126_armclk_set_clk(priv, APLL_HZ);
		if (!ret)
			priv->armclk_init_hz = APLL_HZ;
	}
	if (priv->cpll_hz != CPLL_HZ) {
		ret = rockchip_pll_set_rate(&rv1126_pll_clks[CPLL], priv->cru,
					    CPLL, CPLL_HZ);
		if (!ret)
			priv->cpll_hz = CPLL_HZ;
	}
	if (priv->hpll_hz != HPLL_HZ) {
		ret = rockchip_pll_set_rate(&rv1126_pll_clks[HPLL], priv->cru,
					    HPLL, HPLL_HZ);
		if (!ret)
			priv->hpll_hz = HPLL_HZ;
	}
	if (priv->gpll_hz != GPLL_HZ)
		rv1126_gpll_set_clk(priv, GPLL_HZ);

	rv1126_pdbus_set_clk(priv, ACLK_PDBUS, ACLK_PDBUS_HZ);
	rv1126_pdbus_set_clk(priv, HCLK_PDBUS, HCLK_PDBUS_HZ);
	rv1126_pdbus_set_clk(priv, PCLK_PDBUS, PCLK_PDBUS_HZ);
	rv1126_pdphp_set_clk(priv, ACLK_PDPHP, ACLK_PDPHP_HZ);
	rv1126_pdphp_set_clk(priv, HCLK_PDPHP, HCLK_PDPHP_HZ);
	rv1126_pdcore_set_clk(priv, HCLK_PDCORE_HZ);
	rv1126_pdaudio_set_clk(priv, HCLK_PDAUDIO_HZ);
#if defined(CONFIG_SPL_BUILD) && defined(CONFIG_SPL_KERNEL_BOOT)
	rv1126_clk_pdvi_ispp_set_clk(priv, ACLK_PDVI, ACLK_PDVI_HZ);
	rv1126_clk_isp_set_clk(priv, CLK_ISP_HZ);
	rv1126_clk_pdvi_ispp_set_clk(priv, ACLK_PDISPP, ACLK_PDISPP_HZ);
	rv1126_clk_pdvi_ispp_set_clk(priv, CLK_ISPP, CLK_ISPP_HZ);
	rv1126_aclk_vop_set_clk(priv, ACLK_VOP_HZ);
	rv1126_dclk_vop_set_clk(priv, DCLK_VOP_HZ);
#endif
}

static int rv1126_clk_probe(struct udevice *dev)
{
	struct rv1126_clk_priv *priv = dev_get_priv(dev);
	int ret;

	priv->grf = syscon_get_first_range(ROCKCHIP_SYSCON_GRF);
	if (IS_ERR(priv->grf))
		return PTR_ERR(priv->grf);

	rv1126_clk_init(priv);

	/* Process 'assigned-{clocks/clock-parents/clock-rates}' properties */
	ret = clk_set_defaults(dev);
	if (ret)
		debug("%s clk_set_defaults failed %d\n", __func__, ret);
	else
		priv->sync_kernel = true;

	return 0;
}

static int rv1126_clk_ofdata_to_platdata(struct udevice *dev)
{
	struct rv1126_clk_priv *priv = dev_get_priv(dev);

	priv->cru = dev_read_addr_ptr(dev);

	return 0;
}

static int rv1126_clk_bind(struct udevice *dev)
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
		priv->glb_srst_fst_value = offsetof(struct rv1126_cru,
						    glb_srst_fst);
		priv->glb_srst_snd_value = offsetof(struct rv1126_cru,
						    glb_srst_snd);
		sys_child->priv = priv;
	}

	ret = device_bind_driver_to_node(dev, "rockchip_reset", "reset",
					 dev_ofnode(dev), &sf_child);
	if (ret) {
		debug("Warning: No rockchip reset driver: ret=%d\n", ret);
	} else {
		sf_priv = malloc(sizeof(struct softreset_reg));
		sf_priv->sf_reset_offset = offsetof(struct rv1126_cru,
						    softrst_con[0]);
		sf_priv->sf_reset_num = 15;
		sf_child->priv = sf_priv;
	}

	return 0;
}

static const struct udevice_id rv1126_clk_ids[] = {
	{ .compatible = "rockchip,rv1126-cru" },
	{ }
};

U_BOOT_DRIVER(rockchip_rv1126_cru) = {
	.name		= "rockchip_rv1126_cru",
	.id		= UCLASS_CLK,
	.of_match	= rv1126_clk_ids,
	.priv_auto_alloc_size = sizeof(struct rv1126_clk_priv),
	.ofdata_to_platdata = rv1126_clk_ofdata_to_platdata,
	.ops		= &rv1126_clk_ops,
	.bind		= rv1126_clk_bind,
	.probe		= rv1126_clk_probe,
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
	struct udevice *cru_dev, *pmucru_dev;
	struct rv1126_clk_priv *priv;
	const struct rv1126_clk_info *clk_dump;
	struct clk clk;
	unsigned long clk_count = ARRAY_SIZE(clks_dump);
	unsigned long rate;
	int i, ret;

	ret = uclass_get_device_by_driver(UCLASS_CLK,
					  DM_GET_DRIVER(rockchip_rv1126_cru),
					  &cru_dev);
	if (ret) {
		printf("%s failed to get cru device\n", __func__);
		return ret;
	}

	ret = uclass_get_device_by_driver(UCLASS_CLK,
					  DM_GET_DRIVER(rockchip_rv1126_pmucru),
					  &pmucru_dev);
	if (ret) {
		printf("%s failed to get pmucru device\n", __func__);
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
			else
				ret = clk_request(pmucru_dev, &clk);
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
