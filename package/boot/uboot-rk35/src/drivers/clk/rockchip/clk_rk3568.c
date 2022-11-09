// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2020 Fuzhou Rockchip Electronics Co., Ltd
 * Author: Elaine Zhang <zhangqing@rock-chips.com>
 */

#include <common.h>
#include <bitfield.h>
#include <clk-uclass.h>
#include <dm.h>
#include <errno.h>
#include <syscon.h>
#include <asm/arch-rockchip/clock.h>
#include <asm/arch-rockchip/cru_rk3568.h>
#include <asm/arch-rockchip/grf_rk3568.h>
#include <asm/arch-rockchip/hardware.h>
#include <asm/io.h>
#include <dm/lists.h>
#include <dt-bindings/clock/rk3568-cru.h>

DECLARE_GLOBAL_DATA_PTR;

#define RK3568_CPUCLK_RATE(_rate, _aclk_div, _pclk_div)		\
{								\
	.rate	= _rate##U,					\
	.aclk_div = _aclk_div,					\
	.pclk_div = _pclk_div,					\
}

#define DIV_TO_RATE(input_rate, div)    ((input_rate) / ((div) + 1))

static struct rockchip_cpu_rate_table rk3568_cpu_rates[] = {
	RK3568_CPUCLK_RATE(1416000000, 1, 5),
	RK3568_CPUCLK_RATE(1296000000, 1, 5),
	RK3568_CPUCLK_RATE(1200000000, 1, 3),
	RK3568_CPUCLK_RATE(1104000000, 1, 3),
	RK3568_CPUCLK_RATE(1008000000, 1, 3),
	RK3568_CPUCLK_RATE(912000000, 1, 3),
	RK3568_CPUCLK_RATE(816000000, 1, 3),
	RK3568_CPUCLK_RATE(600000000, 1, 1),
	RK3568_CPUCLK_RATE(408000000, 1, 1),
	{ /* sentinel */ },
};

static struct rockchip_pll_rate_table rk3568_pll_rates[] = {
	/* _mhz, _refdiv, _fbdiv, _postdiv1, _postdiv2, _dsmpd, _frac */
	RK3036_PLL_RATE(1608000000, 1, 67, 1, 1, 1, 0),
	RK3036_PLL_RATE(1416000000, 1, 118, 2, 1, 1, 0),
	RK3036_PLL_RATE(1296000000, 1, 108, 2, 1, 1, 0),
	RK3036_PLL_RATE(1200000000, 1, 100, 2, 1, 1, 0),
	RK3036_PLL_RATE(1188000000, 1, 99, 2, 1, 1, 0),
	RK3036_PLL_RATE(1104000000, 1, 92, 2, 1, 1, 0),
	RK3036_PLL_RATE(1008000000, 1, 84, 2, 1, 1, 0),
	RK3036_PLL_RATE(1000000000, 3, 250, 2, 1, 1, 0),
	RK3036_PLL_RATE(912000000, 1, 76, 2, 1, 1, 0),
	RK3036_PLL_RATE(816000000, 1, 68, 2, 1, 1, 0),
	RK3036_PLL_RATE(600000000, 1, 100, 4, 1, 1, 0),
	RK3036_PLL_RATE(594000000, 1, 99, 4, 1, 1, 0),
	RK3036_PLL_RATE(500000000, 1, 125, 6, 1, 1, 0),
	RK3036_PLL_RATE(408000000, 1, 68, 2, 2, 1, 0),
	RK3036_PLL_RATE(400000000, 1, 100, 6, 1, 1, 0),
	RK3036_PLL_RATE(200000000, 1, 100, 6, 2, 1, 0),
	RK3036_PLL_RATE(100000000, 1, 150, 6, 6, 1, 0),
	{ /* sentinel */ },
};

static struct rockchip_pll_clock rk3568_pll_clks[] = {
	[APLL] = PLL(pll_rk3328, PLL_APLL, RK3568_PLL_CON(0),
		     RK3568_MODE_CON, 0, 10, 0, rk3568_pll_rates),
	[DPLL] = PLL(pll_rk3328, PLL_DPLL, RK3568_PLL_CON(8),
		     RK3568_MODE_CON, 2, 10, 0, NULL),
	[CPLL] = PLL(pll_rk3328, PLL_CPLL, RK3568_PLL_CON(24),
		     RK3568_MODE_CON, 4, 10, 0, rk3568_pll_rates),
	[GPLL] = PLL(pll_rk3328, PLL_HPLL, RK3568_PLL_CON(16),
		     RK3568_MODE_CON, 6, 10, 0, rk3568_pll_rates),
	[NPLL] = PLL(pll_rk3328, PLL_NPLL, RK3568_PLL_CON(32),
		     RK3568_MODE_CON, 10, 10, 0, rk3568_pll_rates),
	[VPLL] = PLL(pll_rk3328, PLL_VPLL, RK3568_PLL_CON(40),
		     RK3568_MODE_CON, 12, 10, 0, rk3568_pll_rates),
	[PPLL] = PLL(pll_rk3328, PLL_PPLL, RK3568_PMU_PLL_CON(0),
		     RK3568_PMU_MODE, 0, 10, 0, rk3568_pll_rates),
	[HPLL] = PLL(pll_rk3328, PLL_HPLL, RK3568_PMU_PLL_CON(16),
		     RK3568_PMU_MODE, 2, 10, 0, rk3568_pll_rates),
};

#ifndef CONFIG_SPL_BUILD
#define RK3568_CLK_DUMP(_id, _name, _iscru)	\
{						\
	.id = _id,				\
	.name = _name,				\
	.is_cru = _iscru,			\
}

static const struct rk3568_clk_info clks_dump[] = {
	RK3568_CLK_DUMP(PLL_APLL, "apll", true),
	RK3568_CLK_DUMP(PLL_DPLL, "dpll", true),
	RK3568_CLK_DUMP(PLL_GPLL, "gpll", true),
	RK3568_CLK_DUMP(PLL_CPLL, "cpll", true),
	RK3568_CLK_DUMP(PLL_NPLL, "npll", true),
	RK3568_CLK_DUMP(PLL_VPLL, "vpll", true),
	RK3568_CLK_DUMP(PLL_HPLL, "hpll", false),
	RK3568_CLK_DUMP(PLL_PPLL, "ppll", false),
	RK3568_CLK_DUMP(ARMCLK, "armclk", true),
	RK3568_CLK_DUMP(ACLK_BUS, "aclk_bus", true),
	RK3568_CLK_DUMP(PCLK_BUS, "pclk_bus", true),
	RK3568_CLK_DUMP(ACLK_TOP_HIGH, "aclk_top_high", true),
	RK3568_CLK_DUMP(ACLK_TOP_LOW, "aclk_top_low", true),
	RK3568_CLK_DUMP(HCLK_TOP, "hclk_top", true),
	RK3568_CLK_DUMP(PCLK_TOP, "pclk_top", true),
	RK3568_CLK_DUMP(ACLK_PERIMID, "aclk_perimid", true),
	RK3568_CLK_DUMP(HCLK_PERIMID, "hclk_perimid", true),
	RK3568_CLK_DUMP(PCLK_PMU, "pclk_pmu", false),
};
#endif

static ulong __maybe_unused
rk3568_pmu_pll_set_rate(struct rk3568_clk_priv *priv,
			ulong pll_id, ulong rate)
{
	struct udevice *pmucru_dev;
	struct rk3568_pmuclk_priv *pmu_priv;
	int ret;

	ret = uclass_get_device_by_driver(UCLASS_CLK,
					  DM_GET_DRIVER(rockchip_rk3568_pmucru),
					  &pmucru_dev);
	if (ret) {
		printf("%s: could not find pmucru device\n", __func__);
		return ret;
	}
	pmu_priv = dev_get_priv(pmucru_dev);

	rockchip_pll_set_rate(&rk3568_pll_clks[pll_id],
			      pmu_priv->pmucru, pll_id, rate);

	return 0;
}

static ulong rk3568_pmu_pll_get_rate(struct rk3568_clk_priv *priv,
				     ulong pll_id)
{
	struct udevice *pmucru_dev;
	struct rk3568_pmuclk_priv *pmu_priv;
	int ret;

	ret = uclass_get_device_by_driver(UCLASS_CLK,
					  DM_GET_DRIVER(rockchip_rk3568_pmucru),
					  &pmucru_dev);
	if (ret) {
		printf("%s: could not find pmucru device\n", __func__);
		return ret;
	}
	pmu_priv = dev_get_priv(pmucru_dev);

	return rockchip_pll_get_rate(&rk3568_pll_clks[pll_id],
				      pmu_priv->pmucru, pll_id);
}

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

static ulong rk3568_rtc32k_get_pmuclk(struct rk3568_pmuclk_priv *priv)
{
	struct rk3568_pmucru *pmucru = priv->pmucru;
	unsigned long m, n;
	u32 fracdiv;

	fracdiv = readl(&pmucru->pmu_clksel_con[1]);
	m = fracdiv & RTC32K_FRAC_NUMERATOR_MASK;
	m >>= RTC32K_FRAC_NUMERATOR_SHIFT;
	n = fracdiv & RTC32K_FRAC_DENOMINATOR_MASK;
	n >>= RTC32K_FRAC_DENOMINATOR_SHIFT;

	return OSC_HZ * m / n;
}

static ulong rk3568_rtc32k_set_pmuclk(struct rk3568_pmuclk_priv *priv,
				      ulong rate)
{
	struct rk3568_pmucru *pmucru = priv->pmucru;
	unsigned long m, n, val;

	rk_clrsetreg(&pmucru->pmu_clksel_con[0], RTC32K_SEL_MASK,
		     RTC32K_SEL_OSC0_DIV32K << RTC32K_SEL_SHIFT);

	rational_best_approximation(rate, OSC_HZ,
				    GENMASK(16 - 1, 0),
				    GENMASK(16 - 1, 0),
				    &m, &n);
	val = m << RTC32K_FRAC_NUMERATOR_SHIFT | n;
	writel(val, &pmucru->pmu_clksel_con[1]);

	return rk3568_rtc32k_get_pmuclk(priv);
}

static ulong rk3568_i2c_get_pmuclk(struct rk3568_pmuclk_priv *priv,
				   ulong clk_id)
{
	struct rk3568_pmucru *pmucru = priv->pmucru;
	u32 div, con;

	switch (clk_id) {
	case CLK_I2C0:
		con = readl(&pmucru->pmu_clksel_con[3]);
		div = (con & CLK_I2C0_DIV_MASK) >> CLK_I2C0_DIV_SHIFT;
		break;
	default:
		return -ENOENT;
	}

	return DIV_TO_RATE(priv->ppll_hz, div);
}

static ulong rk3568_i2c_set_pmuclk(struct rk3568_pmuclk_priv *priv,
				   ulong clk_id, ulong rate)
{
	struct rk3568_pmucru *pmucru = priv->pmucru;
	int src_clk_div;

	src_clk_div = DIV_ROUND_UP(priv->ppll_hz, rate);
	assert(src_clk_div - 1 <= 127);

	switch (clk_id) {
	case CLK_I2C0:
		rk_clrsetreg(&pmucru->pmu_clksel_con[3], CLK_I2C0_DIV_MASK,
			     (src_clk_div - 1) << CLK_I2C0_DIV_SHIFT);
		break;
	default:
		return -ENOENT;
	}

	return rk3568_i2c_get_pmuclk(priv, clk_id);
}

static ulong rk3568_pwm_get_pmuclk(struct rk3568_pmuclk_priv *priv,
				   ulong clk_id)
{
	struct rk3568_pmucru *pmucru = priv->pmucru;
	u32 div, sel, con, parent;

	switch (clk_id) {
	case CLK_PWM0:
		con = readl(&pmucru->pmu_clksel_con[6]);
		sel = (con & CLK_PWM0_SEL_MASK) >> CLK_PWM0_SEL_SHIFT;
		div = (con & CLK_PWM0_DIV_MASK) >> CLK_PWM0_DIV_SHIFT;
		if (sel == CLK_PWM0_SEL_XIN24M)
			parent = OSC_HZ;
		else
			parent = priv->ppll_hz;
		break;
	default:
		return -ENOENT;
	}

	return DIV_TO_RATE(parent, div);
}

static ulong rk3568_pwm_set_pmuclk(struct rk3568_pmuclk_priv *priv,
				   ulong clk_id, ulong rate)
{
	struct rk3568_pmucru *pmucru = priv->pmucru;
	int src_clk_div;

	switch (clk_id) {
	case CLK_PWM0:
		if (rate == OSC_HZ) {
			rk_clrsetreg(&pmucru->pmu_clksel_con[6],
				     CLK_PWM0_SEL_MASK | CLK_PWM0_DIV_MASK,
				     (CLK_PWM0_SEL_XIN24M <<
				      CLK_PWM0_SEL_SHIFT) |
				     0 << CLK_PWM0_SEL_SHIFT);
		} else {
			src_clk_div = DIV_ROUND_UP(priv->ppll_hz, rate);
			assert(src_clk_div - 1 <= 127);
			rk_clrsetreg(&pmucru->pmu_clksel_con[6],
				     CLK_PWM0_DIV_MASK | CLK_PWM0_DIV_MASK,
				     (CLK_PWM0_SEL_PPLL << CLK_PWM0_SEL_SHIFT) |
				     (src_clk_div - 1) << CLK_PWM0_DIV_SHIFT);
		}
		break;
	default:
		return -ENOENT;
	}

	return rk3568_pwm_get_pmuclk(priv, clk_id);
}

static ulong rk3568_pmu_get_pmuclk(struct rk3568_pmuclk_priv *priv)
{
	struct rk3568_pmucru *pmucru = priv->pmucru;
	u32 div, con, sel, parent;

	con = readl(&pmucru->pmu_clksel_con[2]);
	sel = (con & PCLK_PDPMU_SEL_MASK) >> PCLK_PDPMU_SEL_SHIFT;
	div = (con & PCLK_PDPMU_DIV_MASK) >> PCLK_PDPMU_DIV_SHIFT;
	if (sel)
		parent = GPLL_HZ;
	else
		parent = priv->ppll_hz;

	return DIV_TO_RATE(parent, div);
}

static ulong rk3568_pmu_set_pmuclk(struct rk3568_pmuclk_priv *priv,
				   ulong rate)
{
	struct rk3568_pmucru *pmucru = priv->pmucru;
	int src_clk_div;

	src_clk_div = DIV_ROUND_UP(priv->ppll_hz, rate);
	assert(src_clk_div - 1 <= 31);

	rk_clrsetreg(&pmucru->pmu_clksel_con[2],
		     PCLK_PDPMU_DIV_MASK | PCLK_PDPMU_SEL_MASK,
		     (PCLK_PDPMU_SEL_PPLL << PCLK_PDPMU_SEL_SHIFT) |
		     ((src_clk_div - 1) << PCLK_PDPMU_DIV_SHIFT));

	return rk3568_pmu_get_pmuclk(priv);
}

static ulong rk3568_pmuclk_get_rate(struct clk *clk)
{
	struct rk3568_pmuclk_priv *priv = dev_get_priv(clk->dev);
	ulong rate = 0;

	if (!priv->ppll_hz) {
		printf("%s ppll=%lu\n", __func__, priv->ppll_hz);
		return -ENOENT;
	}

	debug("%s %ld\n", __func__, clk->id);
	switch (clk->id) {
	case PLL_PPLL:
		rate = rockchip_pll_get_rate(&rk3568_pll_clks[PPLL],
					     priv->pmucru, PPLL);
		break;
	case PLL_HPLL:
		rate = rockchip_pll_get_rate(&rk3568_pll_clks[HPLL],
					     priv->pmucru, HPLL);
		break;
	case CLK_RTC_32K:
	case CLK_RTC32K_FRAC:
		rate = rk3568_rtc32k_get_pmuclk(priv);
		break;
	case CLK_I2C0:
		rate = rk3568_i2c_get_pmuclk(priv, clk->id);
		break;
	case CLK_PWM0:
		rate = rk3568_pwm_get_pmuclk(priv, clk->id);
		break;
	case PCLK_PMU:
		rate = rk3568_pmu_get_pmuclk(priv);
		break;
	default:
		return -ENOENT;
	}

	return rate;
}

static ulong rk3568_pmuclk_set_rate(struct clk *clk, ulong rate)
{
	struct rk3568_pmuclk_priv *priv = dev_get_priv(clk->dev);
	ulong ret = 0;

	if (!priv->ppll_hz) {
		printf("%s ppll=%lu\n", __func__, priv->ppll_hz);
		return -ENOENT;
	}

	debug("%s %ld %ld\n", __func__, clk->id, rate);
	switch (clk->id) {
	case PLL_PPLL:
		ret = rockchip_pll_set_rate(&rk3568_pll_clks[PPLL],
					    priv->pmucru, PPLL, rate);
		priv->ppll_hz = rockchip_pll_get_rate(&rk3568_pll_clks[PPLL],
						      priv->pmucru, PPLL);
		break;
	case PLL_HPLL:
		ret = rockchip_pll_set_rate(&rk3568_pll_clks[HPLL],
					    priv->pmucru, HPLL, rate);
		priv->hpll_hz = rockchip_pll_get_rate(&rk3568_pll_clks[HPLL],
						      priv->pmucru, HPLL);
		break;
	case CLK_RTC_32K:
	case CLK_RTC32K_FRAC:
		ret = rk3568_rtc32k_set_pmuclk(priv, rate);
		break;
	case CLK_I2C0:
		ret = rk3568_i2c_set_pmuclk(priv, clk->id, rate);
		break;
	case CLK_PWM0:
		ret = rk3568_pwm_set_pmuclk(priv, clk->id, rate);
		break;
	case PCLK_PMU:
		ret = rk3568_pmu_set_pmuclk(priv, rate);
		break;
	default:
		return -ENOENT;
	}

	return ret;
}

static int rk3568_rtc32k_set_parent(struct clk *clk, struct clk *parent)
{
	struct rk3568_pmuclk_priv *priv = dev_get_priv(clk->dev);
	struct rk3568_pmucru *pmucru = priv->pmucru;

	if (parent->id == CLK_RTC32K_FRAC)
		rk_clrsetreg(&pmucru->pmu_clksel_con[0], RTC32K_SEL_MASK,
			     RTC32K_SEL_OSC0_DIV32K << RTC32K_SEL_SHIFT);
	else
		rk_clrsetreg(&pmucru->pmu_clksel_con[0], RTC32K_SEL_MASK,
			     RTC32K_SEL_OSC1_32K << RTC32K_SEL_SHIFT);

	return 0;
}

static int rk3568_pmuclk_set_parent(struct clk *clk, struct clk *parent)
{
	switch (clk->id) {
	case CLK_RTC_32K:
		return rk3568_rtc32k_set_parent(clk, parent);
	default:
		return -ENOENT;
	}
}

static struct clk_ops rk3568_pmuclk_ops = {
	.get_rate = rk3568_pmuclk_get_rate,
	.set_rate = rk3568_pmuclk_set_rate,
	.set_parent = rk3568_pmuclk_set_parent,
};

static int rk3568_pmuclk_probe(struct udevice *dev)
{
	struct rk3568_pmuclk_priv *priv = dev_get_priv(dev);
	int ret = 0;

	if (priv->ppll_hz != PPLL_HZ) {
		ret = rockchip_pll_set_rate(&rk3568_pll_clks[PPLL],
					    priv->pmucru,
					    PPLL, PPLL_HZ);
		if (!ret)
			priv->ppll_hz = PPLL_HZ;
	}

	/* Ungate PCIe30phy refclk_m and refclk_n */
	rk_clrsetreg(&priv->pmucru->pmu_clkgate_con[2], 0x3 << 13, 0 << 13);
	return 0;
}

static int rk3568_pmuclk_ofdata_to_platdata(struct udevice *dev)
{
	struct rk3568_pmuclk_priv *priv = dev_get_priv(dev);

	priv->pmucru = dev_read_addr_ptr(dev);

	return 0;
}

static int rk3568_pmuclk_bind(struct udevice *dev)
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
		sf_priv->sf_reset_offset = offsetof(struct rk3568_pmucru,
						    pmu_softrst_con[0]);
		sf_priv->sf_reset_num = 1;
		sf_child->priv = sf_priv;
	}

	return 0;
}

static const struct udevice_id rk3568_pmuclk_ids[] = {
	{ .compatible = "rockchip,rk3568-pmucru" },
	{ }
};

U_BOOT_DRIVER(rockchip_rk3568_pmucru) = {
	.name		= "rockchip_rk3568_pmucru",
	.id		= UCLASS_CLK,
	.of_match	= rk3568_pmuclk_ids,
	.priv_auto_alloc_size = sizeof(struct rk3568_pmuclk_priv),
	.ofdata_to_platdata = rk3568_pmuclk_ofdata_to_platdata,
	.ops		= &rk3568_pmuclk_ops,
	.bind		= rk3568_pmuclk_bind,
	.probe		= rk3568_pmuclk_probe,
};

static int rk3568_armclk_set_clk(struct rk3568_clk_priv *priv, ulong hz)
{
	struct rk3568_cru *cru = priv->cru;
	const struct rockchip_cpu_rate_table *rate;
	ulong old_rate;

	rate = rockchip_get_cpu_settings(rk3568_cpu_rates, hz);
	if (!rate) {
		printf("%s unsupported rate\n", __func__);
		return -EINVAL;
	}

	rk_clrsetreg(&cru->clksel_con[0],
		     CLK_CORE_PRE_SEL_MASK,
		     (CLK_CORE_PRE_SEL_SRC << CLK_CORE_PRE_SEL_SHIFT));
	rk_clrsetreg(&cru->clksel_con[2],
		     SCLK_CORE_PRE_SEL_MASK |
		     SCLK_CORE_SRC_SEL_MASK |
		     SCLK_CORE_SRC_DIV_MASK,
		     (SCLK_CORE_PRE_SEL_SRC <<
		      SCLK_CORE_PRE_SEL_SHIFT) |
		     (SCLK_CORE_SRC_SEL_APLL <<
		      SCLK_CORE_SRC_SEL_SHIFT) |
		     (1 << SCLK_CORE_SRC_DIV_SHIFT));

	/*
	 * set up dependent divisors for DBG and ACLK clocks.
	 */
	old_rate = rockchip_pll_get_rate(&rk3568_pll_clks[APLL],
					 priv->cru, APLL);
	if (old_rate > hz) {
		if (rockchip_pll_set_rate(&rk3568_pll_clks[APLL],
					  priv->cru, APLL, hz))
			return -EINVAL;
		rk_clrsetreg(&cru->clksel_con[3],
			     GICCLK_CORE_DIV_MASK | ATCLK_CORE_DIV_MASK,
			     rate->pclk_div << GICCLK_CORE_DIV_SHIFT |
			     rate->pclk_div << ATCLK_CORE_DIV_SHIFT);
		rk_clrsetreg(&cru->clksel_con[4],
			     PERIPHCLK_CORE_PRE_DIV_MASK |
			     PCLK_CORE_PRE_DIV_MASK,
			     rate->pclk_div << PCLK_CORE_PRE_DIV_SHIFT |
			     rate->pclk_div << PERIPHCLK_CORE_PRE_DIV_SHIFT);
		rk_clrsetreg(&cru->clksel_con[5],
			     ACLK_CORE_NDFT_DIV_MASK,
			     rate->aclk_div << ACLK_CORE_NDFT_DIV_SHIFT);
	} else if (old_rate < hz) {
		rk_clrsetreg(&cru->clksel_con[3],
			     GICCLK_CORE_DIV_MASK | ATCLK_CORE_DIV_MASK,
			     rate->pclk_div << GICCLK_CORE_DIV_SHIFT |
			     rate->pclk_div << ATCLK_CORE_DIV_SHIFT);
		rk_clrsetreg(&cru->clksel_con[4],
			     PERIPHCLK_CORE_PRE_DIV_MASK |
			     PCLK_CORE_PRE_DIV_MASK,
			     rate->pclk_div << PCLK_CORE_PRE_DIV_SHIFT |
			     rate->pclk_div << PERIPHCLK_CORE_PRE_DIV_SHIFT);
		rk_clrsetreg(&cru->clksel_con[5],
			     ACLK_CORE_NDFT_DIV_MASK,
			     rate->aclk_div << ACLK_CORE_NDFT_DIV_SHIFT);
		if (rockchip_pll_set_rate(&rk3568_pll_clks[APLL],
					  priv->cru, APLL, hz))
			return -EINVAL;
	}

	return 0;
}

static ulong rk3568_cpll_div_get_rate(struct rk3568_clk_priv *priv,
				      ulong clk_id)
{
	struct rk3568_cru *cru = priv->cru;
	int div, mask, shift, con;

	switch (clk_id) {
	case CPLL_500M:
		con = 78;
		mask = CPLL_500M_DIV_MASK;
		shift = CPLL_500M_DIV_SHIFT;
		break;
	case CPLL_333M:
		con = 79;
		mask = CPLL_333M_DIV_MASK;
		shift = CPLL_333M_DIV_SHIFT;
		break;
	case CPLL_250M:
		con = 79;
		mask = CPLL_250M_DIV_MASK;
		shift = CPLL_250M_DIV_SHIFT;
		break;
	case CPLL_125M:
		con = 80;
		mask = CPLL_125M_DIV_MASK;
		shift = CPLL_125M_DIV_SHIFT;
		break;
	case CPLL_100M:
		con = 82;
		mask = CPLL_100M_DIV_MASK;
		shift = CPLL_100M_DIV_SHIFT;
		break;
	case CPLL_62P5M:
		con = 80;
		mask = CPLL_62P5M_DIV_MASK;
		shift = CPLL_62P5M_DIV_SHIFT;
		break;
	case CPLL_50M:
		con = 81;
		mask = CPLL_50M_DIV_MASK;
		shift = CPLL_50M_DIV_SHIFT;
		break;
	case CPLL_25M:
		con = 81;
		mask = CPLL_25M_DIV_MASK;
		shift = CPLL_25M_DIV_SHIFT;
		break;
	default:
		return -ENOENT;
	}

	div = (readl(&cru->clksel_con[con]) & mask) >> shift;
	return DIV_TO_RATE(priv->cpll_hz, div);
}

static ulong rk3568_cpll_div_set_rate(struct rk3568_clk_priv *priv,
				      ulong clk_id, ulong rate)
{
	struct rk3568_cru *cru = priv->cru;
	int div, mask, shift, con;

	switch (clk_id) {
	case CPLL_500M:
		con = 78;
		mask = CPLL_500M_DIV_MASK;
		shift = CPLL_500M_DIV_SHIFT;
		break;
	case CPLL_333M:
		con = 79;
		mask = CPLL_333M_DIV_MASK;
		shift = CPLL_333M_DIV_SHIFT;
		break;
	case CPLL_250M:
		con = 79;
		mask = CPLL_250M_DIV_MASK;
		shift = CPLL_250M_DIV_SHIFT;
		break;
	case CPLL_125M:
		con = 80;
		mask = CPLL_125M_DIV_MASK;
		shift = CPLL_125M_DIV_SHIFT;
		break;
	case CPLL_100M:
		con = 82;
		mask = CPLL_100M_DIV_MASK;
		shift = CPLL_100M_DIV_SHIFT;
		break;
	case CPLL_62P5M:
		con = 80;
		mask = CPLL_62P5M_DIV_MASK;
		shift = CPLL_62P5M_DIV_SHIFT;
		break;
	case CPLL_50M:
		con = 81;
		mask = CPLL_50M_DIV_MASK;
		shift = CPLL_50M_DIV_SHIFT;
		break;
	case CPLL_25M:
		con = 81;
		mask = CPLL_25M_DIV_MASK;
		shift = CPLL_25M_DIV_SHIFT;
		break;
	default:
		return -ENOENT;
	}

	div = DIV_ROUND_UP(priv->cpll_hz, rate);
	assert(div - 1 <= 31);
	rk_clrsetreg(&cru->clksel_con[con],
		     mask, (div - 1) << shift);
	return rk3568_cpll_div_get_rate(priv, clk_id);
}

static ulong rk3568_bus_get_clk(struct rk3568_clk_priv *priv, ulong clk_id)
{
	struct rk3568_cru *cru = priv->cru;
	u32 con, sel, rate;

	switch (clk_id) {
	case ACLK_BUS:
		con = readl(&cru->clksel_con[50]);
		sel = (con & ACLK_BUS_SEL_MASK) >> ACLK_BUS_SEL_SHIFT;
		if (sel == ACLK_BUS_SEL_200M)
			rate = 200 * MHz;
		else if (sel == ACLK_BUS_SEL_150M)
			rate = 150 * MHz;
		else if (sel == ACLK_BUS_SEL_100M)
			rate = 100 * MHz;
		else
			rate = OSC_HZ;
		break;
	case PCLK_BUS:
	case PCLK_WDT_NS:
		con = readl(&cru->clksel_con[50]);
		sel = (con & PCLK_BUS_SEL_MASK) >> PCLK_BUS_SEL_SHIFT;
		if (sel == PCLK_BUS_SEL_100M)
			rate = 100 * MHz;
		else if (sel == PCLK_BUS_SEL_75M)
			rate = 75 * MHz;
		else if (sel == PCLK_BUS_SEL_50M)
			rate = 50 * MHz;
		else
			rate = OSC_HZ;
		break;
	default:
		return -ENOENT;
	}

	return rate;
}

static ulong rk3568_bus_set_clk(struct rk3568_clk_priv *priv,
				ulong clk_id, ulong rate)
{
	struct rk3568_cru *cru = priv->cru;
	int src_clk;

	switch (clk_id) {
	case ACLK_BUS:
		if (rate == 200 * MHz)
			src_clk = ACLK_BUS_SEL_200M;
		else if (rate == 150 * MHz)
			src_clk = ACLK_BUS_SEL_150M;
		else if (rate == 100 * MHz)
			src_clk = ACLK_BUS_SEL_100M;
		else
			src_clk = ACLK_BUS_SEL_24M;
		rk_clrsetreg(&cru->clksel_con[50],
			     ACLK_BUS_SEL_MASK,
			     src_clk << ACLK_BUS_SEL_SHIFT);
		break;
	case PCLK_BUS:
	case PCLK_WDT_NS:
		if (rate == 100 * MHz)
			src_clk = PCLK_BUS_SEL_100M;
		else if (rate == 75 * MHz)
			src_clk = PCLK_BUS_SEL_75M;
		else if (rate == 50 * MHz)
			src_clk = PCLK_BUS_SEL_50M;
		else
			src_clk = PCLK_BUS_SEL_24M;
		rk_clrsetreg(&cru->clksel_con[50],
			     PCLK_BUS_SEL_MASK,
			     src_clk << PCLK_BUS_SEL_SHIFT);
		break;

	default:
		printf("do not support this bus freq\n");
		return -EINVAL;
	}

	return rk3568_bus_get_clk(priv, clk_id);
}

static ulong rk3568_perimid_get_clk(struct rk3568_clk_priv *priv, ulong clk_id)
{
	struct rk3568_cru *cru = priv->cru;
	u32 con, sel, rate;

	switch (clk_id) {
	case ACLK_PERIMID:
		con = readl(&cru->clksel_con[10]);
		sel = (con & ACLK_PERIMID_SEL_MASK) >> ACLK_PERIMID_SEL_SHIFT;
		if (sel == ACLK_PERIMID_SEL_300M)
			rate = 300 * MHz;
		else if (sel == ACLK_PERIMID_SEL_200M)
			rate = 200 * MHz;
		else if (sel == ACLK_PERIMID_SEL_100M)
			rate = 100 * MHz;
		else
			rate = OSC_HZ;
		break;
	case HCLK_PERIMID:
		con = readl(&cru->clksel_con[10]);
		sel = (con & HCLK_PERIMID_SEL_MASK) >> HCLK_PERIMID_SEL_SHIFT;
		if (sel == HCLK_PERIMID_SEL_150M)
			rate = 150 * MHz;
		else if (sel == HCLK_PERIMID_SEL_100M)
			rate = 100 * MHz;
		else if (sel == HCLK_PERIMID_SEL_75M)
			rate = 75 * MHz;
		else
			rate = OSC_HZ;
		break;
	default:
		return -ENOENT;
	}

	return rate;
}

static ulong rk3568_perimid_set_clk(struct rk3568_clk_priv *priv,
				    ulong clk_id, ulong rate)
{
	struct rk3568_cru *cru = priv->cru;
	int src_clk;

	switch (clk_id) {
	case ACLK_PERIMID:
		if (rate == 300 * MHz)
			src_clk = ACLK_PERIMID_SEL_300M;
		else if (rate == 200 * MHz)
			src_clk = ACLK_PERIMID_SEL_200M;
		else if (rate == 100 * MHz)
			src_clk = ACLK_PERIMID_SEL_100M;
		else
			src_clk = ACLK_PERIMID_SEL_24M;
		rk_clrsetreg(&cru->clksel_con[10],
			     ACLK_PERIMID_SEL_MASK,
			     src_clk << ACLK_PERIMID_SEL_SHIFT);
		break;
	case HCLK_PERIMID:
		if (rate == 150 * MHz)
			src_clk = HCLK_PERIMID_SEL_150M;
		else if (rate == 100 * MHz)
			src_clk = HCLK_PERIMID_SEL_100M;
		else if (rate == 75 * MHz)
			src_clk = HCLK_PERIMID_SEL_75M;
		else
			src_clk = HCLK_PERIMID_SEL_24M;
		rk_clrsetreg(&cru->clksel_con[10],
			     HCLK_PERIMID_SEL_MASK,
			     src_clk << HCLK_PERIMID_SEL_SHIFT);
		break;

	default:
		printf("do not support this permid freq\n");
		return -EINVAL;
	}

	return rk3568_perimid_get_clk(priv, clk_id);
}

static ulong rk3568_top_get_clk(struct rk3568_clk_priv *priv, ulong clk_id)
{
	struct rk3568_cru *cru = priv->cru;
	u32 con, sel, rate;

	switch (clk_id) {
	case ACLK_TOP_HIGH:
		con = readl(&cru->clksel_con[73]);
		sel = (con & ACLK_TOP_HIGH_SEL_MASK) >> ACLK_TOP_HIGH_SEL_SHIFT;
		if (sel == ACLK_TOP_HIGH_SEL_500M)
			rate = 500 * MHz;
		else if (sel == ACLK_TOP_HIGH_SEL_400M)
			rate = 400 * MHz;
		else if (sel == ACLK_TOP_HIGH_SEL_300M)
			rate = 300 * MHz;
		else
			rate = OSC_HZ;
		break;
	case ACLK_TOP_LOW:
		con = readl(&cru->clksel_con[73]);
		sel = (con & ACLK_TOP_LOW_SEL_MASK) >> ACLK_TOP_LOW_SEL_SHIFT;
		if (sel == ACLK_TOP_LOW_SEL_400M)
			rate = 400 * MHz;
		else if (sel == ACLK_TOP_LOW_SEL_300M)
			rate = 300 * MHz;
		else if (sel == ACLK_TOP_LOW_SEL_200M)
			rate = 200 * MHz;
		else
			rate = OSC_HZ;
		break;
	case HCLK_TOP:
		con = readl(&cru->clksel_con[73]);
		sel = (con & HCLK_TOP_SEL_MASK) >> HCLK_TOP_SEL_SHIFT;
		if (sel == HCLK_TOP_SEL_150M)
			rate = 150 * MHz;
		else if (sel == HCLK_TOP_SEL_100M)
			rate = 100 * MHz;
		else if (sel == HCLK_TOP_SEL_75M)
			rate = 75 * MHz;
		else
			rate = OSC_HZ;
		break;
	case PCLK_TOP:
		con = readl(&cru->clksel_con[73]);
		sel = (con & PCLK_TOP_SEL_MASK) >> PCLK_TOP_SEL_SHIFT;
		if (sel == PCLK_TOP_SEL_100M)
			rate = 100 * MHz;
		else if (sel == PCLK_TOP_SEL_75M)
			rate = 75 * MHz;
		else if (sel == PCLK_TOP_SEL_50M)
			rate = 50 * MHz;
		else
			rate = OSC_HZ;
		break;
	default:
		return -ENOENT;
	}

	return rate;
}

static ulong rk3568_top_set_clk(struct rk3568_clk_priv *priv,
				ulong clk_id, ulong rate)
{
	struct rk3568_cru *cru = priv->cru;
	int src_clk;

	switch (clk_id) {
	case ACLK_TOP_HIGH:
		if (rate == 500 * MHz)
			src_clk = ACLK_TOP_HIGH_SEL_500M;
		else if (rate == 400 * MHz)
			src_clk = ACLK_TOP_HIGH_SEL_400M;
		else if (rate == 300 * MHz)
			src_clk = ACLK_TOP_HIGH_SEL_300M;
		else
			src_clk = ACLK_TOP_HIGH_SEL_24M;
		rk_clrsetreg(&cru->clksel_con[73],
			     ACLK_TOP_HIGH_SEL_MASK,
			     src_clk << ACLK_TOP_HIGH_SEL_SHIFT);
		break;
	case ACLK_TOP_LOW:
		if (rate == 400 * MHz)
			src_clk = ACLK_TOP_LOW_SEL_400M;
		else if (rate == 300 * MHz)
			src_clk = ACLK_TOP_LOW_SEL_300M;
		else if (rate == 200 * MHz)
			src_clk = ACLK_TOP_LOW_SEL_200M;
		else
			src_clk = ACLK_TOP_LOW_SEL_24M;
		rk_clrsetreg(&cru->clksel_con[73],
			     ACLK_TOP_LOW_SEL_MASK,
			     src_clk << ACLK_TOP_LOW_SEL_SHIFT);
		break;
	case HCLK_TOP:
		if (rate == 150 * MHz)
			src_clk = HCLK_TOP_SEL_150M;
		else if (rate == 100 * MHz)
			src_clk = HCLK_TOP_SEL_100M;
		else if (rate == 75 * MHz)
			src_clk = HCLK_TOP_SEL_75M;
		else
			src_clk = HCLK_TOP_SEL_24M;
		rk_clrsetreg(&cru->clksel_con[73],
			     HCLK_TOP_SEL_MASK,
			     src_clk << HCLK_TOP_SEL_SHIFT);
		break;
	case PCLK_TOP:
		if (rate == 100 * MHz)
			src_clk = PCLK_TOP_SEL_100M;
		else if (rate == 75 * MHz)
			src_clk = PCLK_TOP_SEL_75M;
		else if (rate == 50 * MHz)
			src_clk = PCLK_TOP_SEL_50M;
		else
			src_clk = PCLK_TOP_SEL_24M;
		rk_clrsetreg(&cru->clksel_con[73],
			     PCLK_TOP_SEL_MASK,
			     src_clk << PCLK_TOP_SEL_SHIFT);
		break;

	default:
		printf("do not support this permid freq\n");
		return -EINVAL;
	}

	return rk3568_top_get_clk(priv, clk_id);
}

static ulong rk3568_i2c_get_clk(struct rk3568_clk_priv *priv, ulong clk_id)
{
	struct rk3568_cru *cru = priv->cru;
	u32 sel, con;
	ulong rate;

	switch (clk_id) {
	case CLK_I2C1:
	case CLK_I2C2:
	case CLK_I2C3:
	case CLK_I2C4:
	case CLK_I2C5:
		con = readl(&cru->clksel_con[71]);
		sel = (con & CLK_I2C_SEL_MASK) >> CLK_I2C_SEL_SHIFT;
		if (sel == CLK_I2C_SEL_200M)
			rate = 200 * MHz;
		else if (sel == CLK_I2C_SEL_100M)
			rate = 100 * MHz;
		else if (sel == CLK_I2C_SEL_CPLL_100M)
			rate = 100 * MHz;
		else
			rate = OSC_HZ;
		break;
	default:
		return -ENOENT;
	}

	return rate;
}

static ulong rk3568_i2c_set_clk(struct rk3568_clk_priv *priv, ulong clk_id,
				ulong rate)
{
	struct rk3568_cru *cru = priv->cru;
	int src_clk;

	if (rate == 200 * MHz)
		src_clk = CLK_I2C_SEL_200M;
	else if (rate == 100 * MHz)
		src_clk = CLK_I2C_SEL_100M;
	else
		src_clk = CLK_I2C_SEL_24M;

	switch (clk_id) {
	case CLK_I2C1:
	case CLK_I2C2:
	case CLK_I2C3:
	case CLK_I2C4:
	case CLK_I2C5:
		rk_clrsetreg(&cru->clksel_con[71], CLK_I2C_SEL_MASK,
			     src_clk << CLK_I2C_SEL_SHIFT);
		break;
	default:
		return -ENOENT;
	}

	return rk3568_i2c_get_clk(priv, clk_id);
}

static ulong rk3568_spi_get_clk(struct rk3568_clk_priv *priv, ulong clk_id)
{
	struct rk3568_cru *cru = priv->cru;
	u32 sel, con;

	con = readl(&cru->clksel_con[72]);

	switch (clk_id) {
	case CLK_SPI0:
		sel = (con & CLK_SPI0_SEL_MASK) >> CLK_SPI0_SEL_SHIFT;
		break;
	case CLK_SPI1:
		sel = (con & CLK_SPI1_SEL_MASK) >> CLK_SPI1_SEL_SHIFT;
		break;
	case CLK_SPI2:
		sel = (con & CLK_SPI2_SEL_MASK) >> CLK_SPI2_SEL_SHIFT;
		break;
	case CLK_SPI3:
		sel = (con & CLK_SPI3_SEL_MASK) >> CLK_SPI3_SEL_SHIFT;
		break;
	default:
		return -ENOENT;
	}

	switch (sel) {
	case CLK_SPI_SEL_200M:
		return 200 * MHz;
	case CLK_SPI_SEL_24M:
		return OSC_HZ;
	case CLK_SPI_SEL_CPLL_100M:
		return 100 * MHz;
	default:
		return -ENOENT;
	}
}

static ulong rk3568_spi_set_clk(struct rk3568_clk_priv *priv,
				ulong clk_id, ulong rate)
{
	struct rk3568_cru *cru = priv->cru;
	int src_clk;

	if (rate == 200 * MHz)
		src_clk = CLK_SPI_SEL_200M;
	else if (rate == 100 * MHz)
		src_clk = CLK_SPI_SEL_CPLL_100M;
	else
		src_clk = CLK_SPI_SEL_24M;

	switch (clk_id) {
	case CLK_SPI0:
		rk_clrsetreg(&cru->clksel_con[72],
			     CLK_SPI0_SEL_MASK,
			     src_clk << CLK_SPI0_SEL_SHIFT);
		break;
	case CLK_SPI1:
		rk_clrsetreg(&cru->clksel_con[72],
			     CLK_SPI1_SEL_MASK,
			     src_clk << CLK_SPI1_SEL_SHIFT);
		break;
	case CLK_SPI2:
		rk_clrsetreg(&cru->clksel_con[72],
			     CLK_SPI2_SEL_MASK,
			     src_clk << CLK_SPI2_SEL_SHIFT);
		break;
	case CLK_SPI3:
		rk_clrsetreg(&cru->clksel_con[72],
			     CLK_SPI3_SEL_MASK,
			     src_clk << CLK_SPI3_SEL_SHIFT);
		break;
	default:
		return -ENOENT;
	}

	return rk3568_spi_get_clk(priv, clk_id);
}

static ulong rk3568_pwm_get_clk(struct rk3568_clk_priv *priv, ulong clk_id)
{
	struct rk3568_cru *cru = priv->cru;
	u32 sel, con;

	con = readl(&cru->clksel_con[72]);

	switch (clk_id) {
	case CLK_PWM1:
		sel = (con & CLK_PWM1_SEL_MASK) >> CLK_PWM1_SEL_SHIFT;
		break;
	case CLK_PWM2:
		sel = (con & CLK_PWM2_SEL_MASK) >> CLK_PWM2_SEL_SHIFT;
		break;
	case CLK_PWM3:
		sel = (con & CLK_PWM3_SEL_MASK) >> CLK_PWM3_SEL_SHIFT;
		break;
	default:
		return -ENOENT;
	}

	switch (sel) {
	case CLK_PWM_SEL_100M:
		return 100 * MHz;
	case CLK_PWM_SEL_24M:
		return OSC_HZ;
	case CLK_PWM_SEL_CPLL_100M:
		return 100 * MHz;
	default:
		return -ENOENT;
	}
}

static ulong rk3568_pwm_set_clk(struct rk3568_clk_priv *priv,
				ulong clk_id, ulong rate)
{
	struct rk3568_cru *cru = priv->cru;
	int src_clk;

	if (rate == 100 * MHz)
		src_clk = CLK_PWM_SEL_100M;
	else
		src_clk = CLK_PWM_SEL_24M;

	switch (clk_id) {
	case CLK_PWM1:
		rk_clrsetreg(&cru->clksel_con[72],
			     CLK_PWM1_SEL_MASK,
			     src_clk << CLK_PWM1_SEL_SHIFT);
		break;
	case CLK_PWM2:
		rk_clrsetreg(&cru->clksel_con[72],
			     CLK_PWM2_SEL_MASK,
			     src_clk << CLK_PWM2_SEL_SHIFT);
		break;
	case CLK_PWM3:
		rk_clrsetreg(&cru->clksel_con[72],
			     CLK_PWM3_SEL_MASK,
			     src_clk << CLK_PWM3_SEL_SHIFT);
		break;
	default:
		return -ENOENT;
	}

	return rk3568_pwm_get_clk(priv, clk_id);
}

static ulong rk3568_adc_get_clk(struct rk3568_clk_priv *priv, ulong clk_id)
{
	struct rk3568_cru *cru = priv->cru;
	u32 div, sel, con, prate;

	switch (clk_id) {
	case CLK_SARADC:
		return OSC_HZ;
	case CLK_TSADC_TSEN:
		con = readl(&cru->clksel_con[51]);
		div = (con & CLK_TSADC_TSEN_DIV_MASK) >>
		      CLK_TSADC_TSEN_DIV_SHIFT;
		sel = (con & CLK_TSADC_TSEN_SEL_MASK) >>
		      CLK_TSADC_TSEN_SEL_SHIFT;
		if (sel == CLK_TSADC_TSEN_SEL_24M)
			prate = OSC_HZ;
		else
			prate = 100 * MHz;
		return DIV_TO_RATE(prate, div);
	case CLK_TSADC:
		con = readl(&cru->clksel_con[51]);
		div = (con & CLK_TSADC_DIV_MASK) >> CLK_TSADC_DIV_SHIFT;
		prate = rk3568_adc_get_clk(priv, CLK_TSADC_TSEN);
		return DIV_TO_RATE(prate, div);
	default:
		return -ENOENT;
	}
}

static ulong rk3568_adc_set_clk(struct rk3568_clk_priv *priv,
				ulong clk_id, ulong rate)
{
	struct rk3568_cru *cru = priv->cru;
	int src_clk_div;
	ulong prate = 0;

	switch (clk_id) {
	case CLK_SARADC:
		return OSC_HZ;
	case CLK_TSADC_TSEN:
		if (!(OSC_HZ % rate)) {
			src_clk_div = DIV_ROUND_UP(OSC_HZ, rate);
			assert(src_clk_div - 1 <= 7);
			rk_clrsetreg(&cru->clksel_con[51],
				     CLK_TSADC_TSEN_SEL_MASK |
				     CLK_TSADC_TSEN_DIV_MASK,
				     (CLK_TSADC_TSEN_SEL_24M <<
				      CLK_TSADC_TSEN_SEL_SHIFT) |
				     (src_clk_div - 1) <<
				     CLK_TSADC_TSEN_DIV_SHIFT);
		} else {
			src_clk_div = DIV_ROUND_UP(100 * MHz, rate);
			assert(src_clk_div - 1 <= 7);
			rk_clrsetreg(&cru->clksel_con[51],
				     CLK_TSADC_TSEN_SEL_MASK |
				     CLK_TSADC_TSEN_DIV_MASK,
				     (CLK_TSADC_TSEN_SEL_100M <<
				      CLK_TSADC_TSEN_SEL_SHIFT) |
				     (src_clk_div - 1) <<
				     CLK_TSADC_TSEN_DIV_SHIFT);
		}
		break;
	case CLK_TSADC:
			prate = rk3568_adc_get_clk(priv, CLK_TSADC_TSEN);
			src_clk_div = DIV_ROUND_UP(prate, rate);
			assert(src_clk_div - 1 <= 128);
			rk_clrsetreg(&cru->clksel_con[51],
				     CLK_TSADC_DIV_MASK,
				     (src_clk_div - 1) << CLK_TSADC_DIV_SHIFT);
		break;
	default:
		return -ENOENT;
	}
	return rk3568_adc_get_clk(priv, clk_id);
}

static ulong rk3568_crypto_get_rate(struct rk3568_clk_priv *priv, ulong clk_id)
{
	struct rk3568_cru *cru = priv->cru;
	u32 sel, con;

	switch (clk_id) {
	case ACLK_SECURE_FLASH:
	case ACLK_CRYPTO_NS:
		con = readl(&cru->clksel_con[27]);
		sel = (con & ACLK_SECURE_FLASH_SEL_MASK) >>
		      ACLK_SECURE_FLASH_SEL_SHIFT;
		if (sel == ACLK_SECURE_FLASH_SEL_200M)
			return 200 * MHz;
		else if (sel == ACLK_SECURE_FLASH_SEL_150M)
			return 150 * MHz;
		else if (sel == ACLK_SECURE_FLASH_SEL_100M)
			return 100 * MHz;
		else
			return 24 * MHz;
	case HCLK_SECURE_FLASH:
	case HCLK_CRYPTO_NS:
	case CLK_CRYPTO_NS_RNG:
		con = readl(&cru->clksel_con[27]);
		sel = (con & HCLK_SECURE_FLASH_SEL_MASK) >>
		      HCLK_SECURE_FLASH_SEL_SHIFT;
		if (sel == HCLK_SECURE_FLASH_SEL_150M)
			return 150 * MHz;
		else if (sel == HCLK_SECURE_FLASH_SEL_100M)
			return 100 * MHz;
		else if (sel == HCLK_SECURE_FLASH_SEL_75M)
			return 75 * MHz;
		else
			return 24 * MHz;
	case CLK_CRYPTO_NS_CORE:
		con = readl(&cru->clksel_con[27]);
		sel = (con & CLK_CRYPTO_CORE_SEL_MASK) >>
		      CLK_CRYPTO_CORE_SEL_SHIFT;
		if (sel == CLK_CRYPTO_CORE_SEL_200M)
			return 200 * MHz;
		else if (sel == CLK_CRYPTO_CORE_SEL_150M)
			return 150 * MHz;
		else
			return 100 * MHz;
	case CLK_CRYPTO_NS_PKA:
		con = readl(&cru->clksel_con[27]);
		sel = (con & CLK_CRYPTO_PKA_SEL_MASK) >>
		      CLK_CRYPTO_PKA_SEL_SHIFT;
		if (sel == CLK_CRYPTO_PKA_SEL_300M)
			return 300 * MHz;
		else if (sel == CLK_CRYPTO_PKA_SEL_200M)
			return 200 * MHz;
		else
			return 100 * MHz;
	default:
		return -ENOENT;
	}
}

static ulong rk3568_crypto_set_rate(struct rk3568_clk_priv *priv,
				    ulong clk_id, ulong rate)
{
	struct rk3568_cru *cru = priv->cru;
	u32 src_clk, mask, shift;

	switch (clk_id) {
	case ACLK_SECURE_FLASH:
	case ACLK_CRYPTO_NS:
		mask = ACLK_SECURE_FLASH_SEL_MASK;
		shift = ACLK_SECURE_FLASH_SEL_SHIFT;
		if (rate == 200 * MHz)
			src_clk = ACLK_SECURE_FLASH_SEL_200M;
		else if (rate == 150 * MHz)
			src_clk = ACLK_SECURE_FLASH_SEL_150M;
		else if (rate == 100 * MHz)
			src_clk = ACLK_SECURE_FLASH_SEL_100M;
		else
			src_clk = ACLK_SECURE_FLASH_SEL_24M;
		break;
	case HCLK_SECURE_FLASH:
	case HCLK_CRYPTO_NS:
	case CLK_CRYPTO_NS_RNG:
		mask = HCLK_SECURE_FLASH_SEL_MASK;
		shift = HCLK_SECURE_FLASH_SEL_SHIFT;
		if (rate == 150 * MHz)
			src_clk = HCLK_SECURE_FLASH_SEL_150M;
		else if (rate == 100 * MHz)
			src_clk = HCLK_SECURE_FLASH_SEL_100M;
		else if (rate == 75 * MHz)
			src_clk = HCLK_SECURE_FLASH_SEL_75M;
		else
			src_clk = HCLK_SECURE_FLASH_SEL_24M;
		break;
	case CLK_CRYPTO_NS_CORE:
		mask = CLK_CRYPTO_CORE_SEL_MASK;
		shift = CLK_CRYPTO_CORE_SEL_SHIFT;
		if (rate == 200 * MHz)
			src_clk = CLK_CRYPTO_CORE_SEL_200M;
		else if (rate == 150 * MHz)
			src_clk = CLK_CRYPTO_CORE_SEL_150M;
		else
			src_clk = CLK_CRYPTO_CORE_SEL_100M;
		break;
	case CLK_CRYPTO_NS_PKA:
		mask = CLK_CRYPTO_PKA_SEL_MASK;
		shift = CLK_CRYPTO_PKA_SEL_SHIFT;
		if (rate == 300 * MHz)
			src_clk = CLK_CRYPTO_PKA_SEL_300M;
		else if (rate == 200 * MHz)
			src_clk = CLK_CRYPTO_PKA_SEL_200M;
		else
			src_clk = CLK_CRYPTO_PKA_SEL_100M;
		break;
	default:
		return -ENOENT;
	}

	rk_clrsetreg(&cru->clksel_con[27], mask, src_clk << shift);

	return rk3568_crypto_get_rate(priv, clk_id);
}

static ulong rk3568_sdmmc_get_clk(struct rk3568_clk_priv *priv, ulong clk_id)
{
	struct rk3568_cru *cru = priv->cru;
	u32 sel, con;

	switch (clk_id) {
	case HCLK_SDMMC0:
	case CLK_SDMMC0:
		con = readl(&cru->clksel_con[30]);
		sel = (con & CLK_SDMMC0_SEL_MASK) >> CLK_SDMMC0_SEL_SHIFT;
		break;
	case CLK_SDMMC1:
		con = readl(&cru->clksel_con[30]);
		sel = (con & CLK_SDMMC1_SEL_MASK) >> CLK_SDMMC1_SEL_SHIFT;
		break;
	case CLK_SDMMC2:
		con = readl(&cru->clksel_con[32]);
		sel = (con & CLK_SDMMC2_SEL_MASK) >> CLK_SDMMC2_SEL_SHIFT;
		break;
	default:
		return -ENOENT;
	}

	switch (sel) {
	case CLK_SDMMC_SEL_24M:
		return OSC_HZ;
	case CLK_SDMMC_SEL_400M:
		return 400 * MHz;
	case CLK_SDMMC_SEL_300M:
		return 300 * MHz;
	case CLK_SDMMC_SEL_100M:
		return 100 * MHz;
	case CLK_SDMMC_SEL_50M:
		return 50 * MHz;
	case CLK_SDMMC_SEL_750K:
		return 750 * KHz;
	default:
		return -ENOENT;
	}
}

static ulong rk3568_sdmmc_set_clk(struct rk3568_clk_priv *priv,
				  ulong clk_id, ulong rate)
{
	struct rk3568_cru *cru = priv->cru;
	int src_clk;

	switch (rate) {
	case OSC_HZ:
	case 26 * MHz:
		src_clk = CLK_SDMMC_SEL_24M;
		break;
	case 400 * MHz:
		src_clk = CLK_SDMMC_SEL_400M;
		break;
	case 300 * MHz:
		src_clk = CLK_SDMMC_SEL_300M;
		break;
	case 100 * MHz:
		src_clk = CLK_SDMMC_SEL_100M;
		break;
	case 52 * MHz:
	case 50 * MHz:
		src_clk = CLK_SDMMC_SEL_50M;
		break;
	case 750 * KHz:
	case 400 * KHz:
		src_clk = CLK_SDMMC_SEL_750K;
		break;
	default:
		return -ENOENT;
	}

	switch (clk_id) {
	case HCLK_SDMMC0:
	case CLK_SDMMC0:
		rk_clrsetreg(&cru->clksel_con[30],
			     CLK_SDMMC0_SEL_MASK,
			     src_clk << CLK_SDMMC0_SEL_SHIFT);
		break;
	case CLK_SDMMC1:
		rk_clrsetreg(&cru->clksel_con[30],
			     CLK_SDMMC1_SEL_MASK,
			     src_clk << CLK_SDMMC1_SEL_SHIFT);
		break;
	case CLK_SDMMC2:
		rk_clrsetreg(&cru->clksel_con[32],
			     CLK_SDMMC2_SEL_MASK,
			     src_clk << CLK_SDMMC2_SEL_SHIFT);
		break;
	default:
		return -ENOENT;
	}

	return rk3568_sdmmc_get_clk(priv, clk_id);
}

static ulong rk3568_sfc_get_clk(struct rk3568_clk_priv *priv)
{
	struct rk3568_cru *cru = priv->cru;
	u32 sel, con;

	con = readl(&cru->clksel_con[28]);
	sel = (con & SCLK_SFC_SEL_MASK) >> SCLK_SFC_SEL_SHIFT;
	switch (sel) {
	case SCLK_SFC_SEL_24M:
		return OSC_HZ;
	case SCLK_SFC_SEL_50M:
		return 50 * MHz;
	case SCLK_SFC_SEL_75M:
		return 75 * MHz;
	case SCLK_SFC_SEL_100M:
		return 100 * MHz;
	case SCLK_SFC_SEL_125M:
		return 125 * MHz;
	case SCLK_SFC_SEL_150M:
		return 150 * MHz;
	default:
		return -ENOENT;
	}
}

static ulong rk3568_sfc_set_clk(struct rk3568_clk_priv *priv, ulong rate)
{
	struct rk3568_cru *cru = priv->cru;
	int src_clk;

	switch (rate) {
	case OSC_HZ:
		src_clk = SCLK_SFC_SEL_24M;
		break;
	case 50 * MHz:
		src_clk = SCLK_SFC_SEL_50M;
		break;
	case 75 * MHz:
		src_clk = SCLK_SFC_SEL_75M;
		break;
	case 100 * MHz:
		src_clk = SCLK_SFC_SEL_100M;
		break;
	case 125 * MHz:
		src_clk = SCLK_SFC_SEL_125M;
		break;
	case 150 * MHz:
		src_clk = SCLK_SFC_SEL_150M;
		break;
	default:
		return -ENOENT;
	}

	rk_clrsetreg(&cru->clksel_con[28],
		     SCLK_SFC_SEL_MASK,
		     src_clk << SCLK_SFC_SEL_SHIFT);

	return rk3568_sfc_get_clk(priv);
}

static ulong rk3568_nand_get_clk(struct rk3568_clk_priv *priv)
{
	struct rk3568_cru *cru = priv->cru;
	u32 sel, con;

	con = readl(&cru->clksel_con[28]);
	sel = (con & NCLK_NANDC_SEL_MASK) >> NCLK_NANDC_SEL_SHIFT;
	switch (sel) {
	case NCLK_NANDC_SEL_200M:
		return 200 * MHz;
	case NCLK_NANDC_SEL_150M:
		return 150 * MHz;
	case NCLK_NANDC_SEL_100M:
		return 100 * MHz;
	case NCLK_NANDC_SEL_24M:
		return OSC_HZ;
	default:
		return -ENOENT;
	}
}

static ulong rk3568_nand_set_clk(struct rk3568_clk_priv *priv, ulong rate)
{
	struct rk3568_cru *cru = priv->cru;
	int src_clk;

	switch (rate) {
	case OSC_HZ:
		src_clk = NCLK_NANDC_SEL_24M;
		break;
	case 100 * MHz:
		src_clk = NCLK_NANDC_SEL_100M;
		break;
	case 150 * MHz:
		src_clk = NCLK_NANDC_SEL_150M;
		break;
	case 200 * MHz:
		src_clk = NCLK_NANDC_SEL_200M;
		break;
	default:
		return -ENOENT;
	}

	rk_clrsetreg(&cru->clksel_con[28],
		     NCLK_NANDC_SEL_MASK,
		     src_clk << NCLK_NANDC_SEL_SHIFT);

	return rk3568_nand_get_clk(priv);
}

static ulong rk3568_emmc_get_clk(struct rk3568_clk_priv *priv)
{
	struct rk3568_cru *cru = priv->cru;
	u32 sel, con;

	con = readl(&cru->clksel_con[28]);
	sel = (con & CCLK_EMMC_SEL_MASK) >> CCLK_EMMC_SEL_SHIFT;
	switch (sel) {
	case CCLK_EMMC_SEL_200M:
		return 200 * MHz;
	case CCLK_EMMC_SEL_150M:
		return 150 * MHz;
	case CCLK_EMMC_SEL_100M:
		return 100 * MHz;
	case CCLK_EMMC_SEL_50M:
		return 50 * MHz;
	case CCLK_EMMC_SEL_375K:
		return 375 * KHz;
	case CCLK_EMMC_SEL_24M:
		return OSC_HZ;
	default:
		return -ENOENT;
	}
}

static ulong rk3568_emmc_set_clk(struct rk3568_clk_priv *priv, ulong rate)
{
	struct rk3568_cru *cru = priv->cru;
	int src_clk;

	switch (rate) {
	case OSC_HZ:
		src_clk = CCLK_EMMC_SEL_24M;
		break;
	case 52 * MHz:
	case 50 * MHz:
		src_clk = CCLK_EMMC_SEL_50M;
		break;
	case 100 * MHz:
		src_clk = CCLK_EMMC_SEL_100M;
		break;
	case 150 * MHz:
		src_clk = CCLK_EMMC_SEL_150M;
		break;
	case 200 * MHz:
		src_clk = CCLK_EMMC_SEL_200M;
		break;
	case 400 * KHz:
	case 375 * KHz:
		src_clk = CCLK_EMMC_SEL_375K;
		break;
	default:
		return -ENOENT;
	}

	rk_clrsetreg(&cru->clksel_con[28],
		     CCLK_EMMC_SEL_MASK,
		     src_clk << CCLK_EMMC_SEL_SHIFT);

	return rk3568_emmc_get_clk(priv);
}

static ulong rk3568_emmc_get_bclk(struct rk3568_clk_priv *priv)
{
	struct rk3568_cru *cru = priv->cru;
	u32 sel, con;

	con = readl(&cru->clksel_con[28]);
	sel = (con & BCLK_EMMC_SEL_MASK) >> BCLK_EMMC_SEL_SHIFT;
	switch (sel) {
	case BCLK_EMMC_SEL_200M:
		return 200 * MHz;
	case BCLK_EMMC_SEL_150M:
		return 150 * MHz;
	case BCLK_EMMC_SEL_125M:
		return 125 * MHz;
	default:
		return -ENOENT;
	}
}

static ulong rk3568_emmc_set_bclk(struct rk3568_clk_priv *priv, ulong rate)
{
	struct rk3568_cru *cru = priv->cru;
	int src_clk;

	switch (rate) {
	case 200 * MHz:
		src_clk = BCLK_EMMC_SEL_200M;
		break;
	case 150 * MHz:
		src_clk = BCLK_EMMC_SEL_150M;
		break;
	case 125 * MHz:
		src_clk = BCLK_EMMC_SEL_125M;
		break;
	default:
		return -ENOENT;
	}

	rk_clrsetreg(&cru->clksel_con[28],
		     BCLK_EMMC_SEL_MASK,
		     src_clk << BCLK_EMMC_SEL_SHIFT);

	return rk3568_emmc_get_bclk(priv);
}

#ifndef CONFIG_SPL_BUILD
static ulong rk3568_aclk_vop_get_clk(struct rk3568_clk_priv *priv)
{
	struct rk3568_cru *cru = priv->cru;
	u32 div, sel, con, parent;

	con = readl(&cru->clksel_con[38]);
	div = (con & ACLK_VOP_PRE_DIV_MASK) >> ACLK_VOP_PRE_DIV_SHIFT;
	sel = (con & ACLK_VOP_PRE_SEL_MASK) >> ACLK_VOP_PRE_SEL_SHIFT;
	if (sel == ACLK_VOP_PRE_SEL_GPLL)
		parent = priv->gpll_hz;
	else if (sel == ACLK_VOP_PRE_SEL_CPLL)
		parent = priv->cpll_hz;
	else if (sel == ACLK_VOP_PRE_SEL_VPLL)
		parent = priv->vpll_hz;
	else
		parent = priv->hpll_hz;

	return DIV_TO_RATE(parent, div);
}

static ulong rk3568_aclk_vop_set_clk(struct rk3568_clk_priv *priv, ulong rate)
{
	struct rk3568_cru *cru = priv->cru;
	int src_clk_div, src_clk_mux;

	if ((priv->cpll_hz % rate) == 0) {
		src_clk_div = DIV_ROUND_UP(priv->cpll_hz, rate);
		src_clk_mux = ACLK_VOP_PRE_SEL_CPLL;
	} else {
		src_clk_div = DIV_ROUND_UP(priv->gpll_hz, rate);
		src_clk_mux = ACLK_VOP_PRE_SEL_GPLL;
	}
	assert(src_clk_div - 1 <= 31);
	rk_clrsetreg(&cru->clksel_con[38],
		     ACLK_VOP_PRE_SEL_MASK | ACLK_VOP_PRE_DIV_MASK,
		     src_clk_mux << ACLK_VOP_PRE_SEL_SHIFT |
		     (src_clk_div - 1) << ACLK_VOP_PRE_DIV_SHIFT);

	return rk3568_aclk_vop_get_clk(priv);
}

static ulong rk3568_dclk_vop_get_clk(struct rk3568_clk_priv *priv, ulong clk_id)
{
	struct rk3568_cru *cru = priv->cru;
	u32 conid, div, sel, con, parent;

	switch (clk_id) {
	case DCLK_VOP0:
		conid = 39;
		break;
	case DCLK_VOP1:
		conid = 40;
		break;
	case DCLK_VOP2:
		conid = 41;
		break;
	default:
		return -ENOENT;
	}

	con = readl(&cru->clksel_con[conid]);
	div = (con & DCLK0_VOP_DIV_MASK) >> DCLK0_VOP_DIV_SHIFT;
	sel = (con & DCLK0_VOP_SEL_MASK) >> DCLK0_VOP_SEL_SHIFT;
	if (sel == DCLK_VOP_SEL_HPLL)
		parent = rk3568_pmu_pll_get_rate(priv, HPLL);
	else if (sel == DCLK_VOP_SEL_VPLL)
		parent = rockchip_pll_get_rate(&rk3568_pll_clks[VPLL],
					       priv->cru, VPLL);
	else if (sel == DCLK_VOP_SEL_GPLL)
		parent = priv->gpll_hz;
	else if (sel == DCLK_VOP_SEL_CPLL)
		parent = priv->cpll_hz;
	else
		return -ENOENT;

	return DIV_TO_RATE(parent, div);
}

#define RK3568_VOP_PLL_LIMIT_FREQ 600000000

static ulong rk3568_dclk_vop_set_clk(struct rk3568_clk_priv *priv,
				     ulong clk_id, ulong rate)
{
	struct rk3568_cru *cru = priv->cru;
	ulong pll_rate, now, best_rate = 0;
	u32 i, conid, con, sel, div, best_div = 0, best_sel = 0;

	switch (clk_id) {
	case DCLK_VOP0:
		conid = 39;
		break;
	case DCLK_VOP1:
		conid = 40;
		break;
	case DCLK_VOP2:
		conid = 41;
		break;
	default:
		return -ENOENT;
	}

	con = readl(&cru->clksel_con[conid]);
	sel = (con & DCLK0_VOP_SEL_MASK) >> DCLK0_VOP_SEL_SHIFT;

	if (sel == DCLK_VOP_SEL_HPLL) {
		div = 1;
		rk_clrsetreg(&cru->clksel_con[conid],
			     DCLK0_VOP_DIV_MASK | DCLK0_VOP_SEL_MASK,
			     (DCLK_VOP_SEL_HPLL << DCLK0_VOP_SEL_SHIFT) |
			     ((div - 1) << DCLK0_VOP_DIV_SHIFT));
		rk3568_pmu_pll_set_rate(priv, HPLL, div * rate);
	} else if (sel == DCLK_VOP_SEL_VPLL) {
		div = DIV_ROUND_UP(RK3568_VOP_PLL_LIMIT_FREQ, rate);
		rk_clrsetreg(&cru->clksel_con[conid],
			     DCLK0_VOP_DIV_MASK | DCLK0_VOP_SEL_MASK,
			     (DCLK_VOP_SEL_VPLL << DCLK0_VOP_SEL_SHIFT) |
			     ((div - 1) << DCLK0_VOP_DIV_SHIFT));
		rockchip_pll_set_rate(&rk3568_pll_clks[VPLL],
				      priv->cru, VPLL, div * rate);
	} else {
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
			debug("p_rate=%lu, best_rate=%lu, div=%u, sel=%u\n",
			      pll_rate, best_rate, best_div, best_sel);
		}

		if (best_rate) {
			rk_clrsetreg(&cru->clksel_con[conid],
				     DCLK0_VOP_DIV_MASK | DCLK0_VOP_SEL_MASK,
				     best_sel << DCLK0_VOP_SEL_SHIFT |
				     (best_div - 1) << DCLK0_VOP_DIV_SHIFT);
		} else {
			printf("do not support this vop freq %lu\n", rate);
			return -EINVAL;
		}
	}
	return rk3568_dclk_vop_get_clk(priv, clk_id);
}

static ulong rk3568_gmac_src_get_clk(struct rk3568_clk_priv *priv,
				     ulong mac_id)
{
	struct rk3568_cru *cru = priv->cru;
	u32 sel, con;

	con = readl(&cru->clksel_con[31 + mac_id * 2]);
	sel = (con & CLK_MAC0_2TOP_SEL_MASK) >> CLK_MAC0_2TOP_SEL_SHIFT;

	switch (sel) {
	case CLK_MAC0_2TOP_SEL_125M:
		return 125 * MHz;
	case CLK_MAC0_2TOP_SEL_50M:
		return 50 * MHz;
	case CLK_MAC0_2TOP_SEL_25M:
		return 25 * MHz;
	case CLK_MAC0_2TOP_SEL_PPLL:
		return rk3568_pmu_pll_get_rate(priv, HPLL);
	default:
		return -ENOENT;
	}
}

static ulong rk3568_gmac_src_set_clk(struct rk3568_clk_priv *priv,
				     ulong mac_id, ulong rate)
{
	struct rk3568_cru *cru = priv->cru;
	int src_clk;

	switch (rate) {
	case 125 * MHz:
		src_clk = CLK_MAC0_2TOP_SEL_125M;
		break;
	case 50 * MHz:
		src_clk = CLK_MAC0_2TOP_SEL_50M;
		break;
	case 25 * MHz:
		src_clk = CLK_MAC0_2TOP_SEL_25M;
		break;
	default:
		return -ENOENT;
	}

	rk_clrsetreg(&cru->clksel_con[31 + mac_id * 2],
		     CLK_MAC0_2TOP_SEL_MASK,
		     src_clk << CLK_MAC0_2TOP_SEL_SHIFT);

	return rk3568_gmac_src_get_clk(priv, mac_id);
}

static ulong rk3568_gmac_out_get_clk(struct rk3568_clk_priv *priv,
				     ulong mac_id)
{
	struct rk3568_cru *cru = priv->cru;
	u32 sel, con;

	con = readl(&cru->clksel_con[31 + mac_id * 2]);
	sel = (con & CLK_MAC0_OUT_SEL_MASK) >> CLK_MAC0_OUT_SEL_SHIFT;

	switch (sel) {
	case CLK_MAC0_OUT_SEL_125M:
		return 125 * MHz;
	case CLK_MAC0_OUT_SEL_50M:
		return 50 * MHz;
	case CLK_MAC0_OUT_SEL_25M:
		return 25 * MHz;
	case CLK_MAC0_OUT_SEL_24M:
		return OSC_HZ;
	default:
		return -ENOENT;
	}
}

static ulong rk3568_gmac_out_set_clk(struct rk3568_clk_priv *priv,
				     ulong mac_id, ulong rate)
{
	struct rk3568_cru *cru = priv->cru;
	int src_clk;

	switch (rate) {
	case 125 * MHz:
		src_clk = CLK_MAC0_OUT_SEL_125M;
		break;
	case 50 * MHz:
		src_clk = CLK_MAC0_OUT_SEL_50M;
		break;
	case 25 * MHz:
		src_clk = CLK_MAC0_OUT_SEL_25M;
		break;
	case 24 * MHz:
		src_clk = CLK_MAC0_OUT_SEL_24M;
		break;
	default:
		return -ENOENT;
	}

	rk_clrsetreg(&cru->clksel_con[31 + mac_id * 2],
		     CLK_MAC0_OUT_SEL_MASK,
		     src_clk << CLK_MAC0_OUT_SEL_SHIFT);

	return rk3568_gmac_out_get_clk(priv, mac_id);
}

static ulong rk3568_gmac_ptp_ref_get_clk(struct rk3568_clk_priv *priv,
					 ulong mac_id)
{
	struct rk3568_cru *cru = priv->cru;
	u32 sel, con;

	con = readl(&cru->clksel_con[31 + mac_id * 2]);
	sel = (con & CLK_GMAC0_PTP_REF_SEL_MASK) >> CLK_GMAC0_PTP_REF_SEL_SHIFT;

	switch (sel) {
	case CLK_GMAC0_PTP_REF_SEL_62_5M:
		return 62500 * KHz;
	case CLK_GMAC0_PTP_REF_SEL_100M:
		return 100 * MHz;
	case CLK_GMAC0_PTP_REF_SEL_50M:
		return 50 * MHz;
	case CLK_GMAC0_PTP_REF_SEL_24M:
		return OSC_HZ;
	default:
		return -ENOENT;
	}
}

static ulong rk3568_gmac_ptp_ref_set_clk(struct rk3568_clk_priv *priv,
					 ulong mac_id, ulong rate)
{
	struct rk3568_cru *cru = priv->cru;
	int src_clk;

	switch (rate) {
	case 62500 * KHz:
		src_clk = CLK_GMAC0_PTP_REF_SEL_62_5M;
		break;
	case 100 * MHz:
		src_clk = CLK_GMAC0_PTP_REF_SEL_100M;
		break;
	case 50 * MHz:
		src_clk = CLK_GMAC0_PTP_REF_SEL_50M;
		break;
	case 24 * MHz:
		src_clk = CLK_GMAC0_PTP_REF_SEL_24M;
		break;
	default:
		return -ENOENT;
	}

	rk_clrsetreg(&cru->clksel_con[31 + mac_id * 2],
		     CLK_GMAC0_PTP_REF_SEL_MASK,
		     src_clk << CLK_GMAC0_PTP_REF_SEL_SHIFT);

	return rk3568_gmac_ptp_ref_get_clk(priv, mac_id);
}

static ulong rk3568_gmac_tx_rx_set_clk(struct rk3568_clk_priv *priv,
				       ulong mac_id, ulong rate)
{
	struct rk3568_cru *cru = priv->cru;
	u32 con, sel, div_sel;

	con = readl(&cru->clksel_con[31 + mac_id * 2]);
	sel = (con & RMII0_MODE_MASK) >> RMII0_MODE_SHIFT;

	if (sel == RMII0_MODE_SEL_RGMII) {
		if (rate == 2500000)
			div_sel = RGMII0_CLK_SEL_2_5M;
		else if (rate == 25000000)
			div_sel = RGMII0_CLK_SEL_25M;
		else
			div_sel = RGMII0_CLK_SEL_125M;
		rk_clrsetreg(&cru->clksel_con[31 + mac_id * 2],
			     RGMII0_CLK_SEL_MASK,
			     div_sel << RGMII0_CLK_SEL_SHIFT);
	} else if (sel == RMII0_MODE_SEL_RMII) {
		if (rate == 2500000)
			div_sel = RMII0_CLK_SEL_2_5M;
		else
			div_sel = RMII0_CLK_SEL_25M;
		rk_clrsetreg(&cru->clksel_con[31 + mac_id * 2],
			     RMII0_CLK_SEL_MASK,
			     div_sel << RMII0_CLK_SEL_SHIFT);
	}

	return 0;
}

static ulong rk3568_ebc_get_clk(struct rk3568_clk_priv *priv)
{
	struct rk3568_cru *cru = priv->cru;
	u32 con, div, p_rate;

	con = readl(&cru->clksel_con[79]);
	div = (con & CPLL_333M_DIV_MASK) >> CPLL_333M_DIV_SHIFT;
	p_rate = DIV_TO_RATE(priv->cpll_hz, div);

	con = readl(&cru->clksel_con[43]);
	div = (con & DCLK_EBC_SEL_MASK) >> DCLK_EBC_SEL_SHIFT;
	switch (div) {
	case DCLK_EBC_SEL_GPLL_400M:
		return 400 * MHz;
	case DCLK_EBC_SEL_CPLL_333M:
		return p_rate;
	case DCLK_EBC_SEL_GPLL_200M:
		return 200 * MHz;
	default:
		return -ENOENT;
	}
}

static ulong rk3568_ebc_set_clk(struct rk3568_clk_priv *priv, ulong rate)
{
	struct rk3568_cru *cru = priv->cru;
	int src_clk_div;

	src_clk_div = DIV_ROUND_UP(priv->cpll_hz, rate);
	assert(src_clk_div - 1 <= 31);
	rk_clrsetreg(&cru->clksel_con[79],
		     CPLL_333M_DIV_MASK,
		     (src_clk_div - 1) << CPLL_333M_DIV_SHIFT);
	rk_clrsetreg(&cru->clksel_con[43],
		     DCLK_EBC_SEL_MASK,
		     DCLK_EBC_SEL_CPLL_333M << DCLK_EBC_SEL_SHIFT);

	return rk3568_ebc_get_clk(priv);
}

static ulong rk3568_rkvdec_get_clk(struct rk3568_clk_priv *priv, ulong clk_id)
{
	struct rk3568_cru *cru = priv->cru;
	u32 con, div, src, p_rate;

	switch (clk_id) {
	case ACLK_RKVDEC_PRE:
	case ACLK_RKVDEC:
		con = readl(&cru->clksel_con[47]);
		src = (con & ACLK_RKVDEC_SEL_MASK) >> ACLK_RKVDEC_SEL_SHIFT;
		div = (con & ACLK_RKVDEC_DIV_MASK) >> ACLK_RKVDEC_DIV_SHIFT;
		if (src == ACLK_RKVDEC_SEL_CPLL)
			p_rate = priv->cpll_hz;
		else
			p_rate = priv->gpll_hz;
		return DIV_TO_RATE(p_rate, div);
	case CLK_RKVDEC_CORE:
		con = readl(&cru->clksel_con[49]);
		src = (con & CLK_RKVDEC_CORE_SEL_MASK)
		      >> CLK_RKVDEC_CORE_SEL_SHIFT;
		div = (con & CLK_RKVDEC_CORE_DIV_MASK)
		      >> CLK_RKVDEC_CORE_DIV_SHIFT;
		if (src == CLK_RKVDEC_CORE_SEL_CPLL)
			p_rate = priv->cpll_hz;
		else if (src == CLK_RKVDEC_CORE_SEL_NPLL)
			p_rate = priv->npll_hz;
		else if (src == CLK_RKVDEC_CORE_SEL_VPLL)
			p_rate = priv->vpll_hz;
		else
			p_rate = priv->gpll_hz;
		return DIV_TO_RATE(p_rate, div);
	default:
		return -ENOENT;
	}
}

static ulong rk3568_rkvdec_set_clk(struct rk3568_clk_priv *priv,
				   ulong clk_id, ulong rate)
{
	struct rk3568_cru *cru = priv->cru;
	int src_clk_div, src, p_rate;

	switch (clk_id) {
	case ACLK_RKVDEC_PRE:
	case ACLK_RKVDEC:
		src = (readl(&cru->clksel_con[47]) & ACLK_RKVDEC_SEL_MASK)
		      >> ACLK_RKVDEC_SEL_SHIFT;
		if (src == ACLK_RKVDEC_SEL_CPLL)
			p_rate = priv->cpll_hz;
		else
			p_rate = priv->gpll_hz;
		src_clk_div = DIV_ROUND_UP(p_rate, rate);
		assert(src_clk_div - 1 <= 31);
		rk_clrsetreg(&cru->clksel_con[47],
			     ACLK_RKVDEC_SEL_MASK |
			     ACLK_RKVDEC_DIV_MASK,
			     (src << ACLK_RKVDEC_SEL_SHIFT) |
			     (src_clk_div - 1) << ACLK_RKVDEC_DIV_SHIFT);
		break;
	case CLK_RKVDEC_CORE:
		src = (readl(&cru->clksel_con[49]) & CLK_RKVDEC_CORE_SEL_MASK)
		      >> CLK_RKVDEC_CORE_SEL_SHIFT;
		if (src == CLK_RKVDEC_CORE_SEL_CPLL)
			p_rate = priv->cpll_hz;
		else if (src == CLK_RKVDEC_CORE_SEL_NPLL)
			p_rate = priv->npll_hz;
		else if (src == CLK_RKVDEC_CORE_SEL_VPLL)
			p_rate = priv->vpll_hz;
		else
			p_rate = priv->gpll_hz;
		src_clk_div = DIV_ROUND_UP(p_rate, rate);
		assert(src_clk_div - 1 <= 31);
		rk_clrsetreg(&cru->clksel_con[49],
			     CLK_RKVDEC_CORE_SEL_MASK |
			     CLK_RKVDEC_CORE_DIV_MASK,
			     (src << CLK_RKVDEC_CORE_SEL_SHIFT) |
			     (src_clk_div - 1) << CLK_RKVDEC_CORE_DIV_SHIFT);
		break;
	default:
		return -ENOENT;
	}

	return rk3568_rkvdec_get_clk(priv, clk_id);
}

static ulong rk3568_uart_get_rate(struct rk3568_clk_priv *priv, ulong clk_id)
{
	struct rk3568_cru *cru = priv->cru;
	u32 reg, con, fracdiv, div, src, p_src, p_rate;
	unsigned long m, n;

	switch (clk_id) {
	case SCLK_UART1:
		reg = 52;
		break;
	case SCLK_UART2:
		reg = 54;
		break;
	case SCLK_UART3:
		reg = 56;
		break;
	case SCLK_UART4:
		reg = 58;
		break;
	case SCLK_UART5:
		reg = 60;
		break;
	case SCLK_UART6:
		reg = 62;
		break;
	case SCLK_UART7:
		reg = 64;
		break;
	case SCLK_UART8:
		reg = 66;
		break;
	case SCLK_UART9:
		reg = 68;
		break;
	default:
		return -ENOENT;
	}
	con = readl(&cru->clksel_con[reg]);
	src = (con & CLK_UART_SEL_MASK) >> CLK_UART_SEL_SHIFT;
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

static ulong rk3568_uart_set_rate(struct rk3568_clk_priv *priv,
				  ulong clk_id, ulong rate)
{
	struct rk3568_cru *cru = priv->cru;
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
	case SCLK_UART1:
		reg = 52;
		break;
	case SCLK_UART2:
		reg = 54;
		break;
	case SCLK_UART3:
		reg = 56;
		break;
	case SCLK_UART4:
		reg = 58;
		break;
	case SCLK_UART5:
		reg = 60;
		break;
	case SCLK_UART6:
		reg = 62;
		break;
	case SCLK_UART7:
		reg = 64;
		break;
	case SCLK_UART8:
		reg = 66;
		break;
	case SCLK_UART9:
		reg = 68;
		break;
	default:
		return -ENOENT;
	}
	rk_clrsetreg(&cru->clksel_con[reg],
		     CLK_UART_SEL_MASK | CLK_UART_SRC_SEL_MASK |
		     CLK_UART_SRC_DIV_MASK,
		     (clk_src << CLK_UART_SRC_SEL_SHIFT) |
		     (uart_src << CLK_UART_SEL_SHIFT) |
		     ((div - 1) << CLK_UART_SRC_DIV_SHIFT));
	if (m && n) {
		val = m << CLK_UART_FRAC_NUMERATOR_SHIFT | n;
		writel(val, &cru->clksel_con[reg + 1]);
	}

	return rk3568_uart_get_rate(priv, clk_id);
}

static ulong rk3568_i2s3_get_rate(struct rk3568_clk_priv *priv, ulong clk_id)
{
	struct rk3568_cru *cru = priv->cru;
	struct rk3568_grf *grf = priv->grf;
	u32 con, div, src, p_rate;
	u32 reg, fracdiv, p_src;
	unsigned long m, n;

	switch (clk_id) {
	case I2S3_MCLKOUT_TX:
		con = readl(&cru->clksel_con[21]);
		src = (con & I2S3_MCLKOUT_TX_SEL_MASK) >>
		      I2S3_MCLKOUT_TX_SEL_SHIFT;
		if (src == I2S3_MCLKOUT_TX_SEL_12M)
			p_rate = 12000000;
		else
			p_rate = rk3568_i2s3_get_rate(priv, MCLK_I2S3_2CH_TX);
		return p_rate;
	case I2S3_MCLKOUT_RX:
		con = readl(&cru->clksel_con[83]);
		src = (con & I2S3_MCLKOUT_TX_SEL_MASK) >>
		      I2S3_MCLKOUT_TX_SEL_SHIFT;
		if (src == I2S3_MCLKOUT_TX_SEL_12M)
			p_rate = 12000000;
		else
			p_rate = rk3568_i2s3_get_rate(priv, MCLK_I2S3_2CH_RX);
		return p_rate;
	case I2S3_MCLKOUT:
		con = readl(&grf->soc_con2);
		src = (con & I2S3_MCLKOUT_SEL_MASK)
		      >> I2S3_MCLKOUT_SEL_SHIFT;
		if (src == I2S3_MCLKOUT_SEL_RX)
			p_rate = rk3568_i2s3_get_rate(priv, I2S3_MCLKOUT_RX);
		else
			p_rate = rk3568_i2s3_get_rate(priv, I2S3_MCLKOUT_TX);
		return p_rate;
	case MCLK_I2S3_2CH_RX:
		reg = 83;
		break;
	case MCLK_I2S3_2CH_TX:
		reg = 21;
		break;
	default:
		return -ENOENT;
	}

	con = readl(&cru->clksel_con[reg]);
	src = (con & CLK_I2S3_SEL_MASK) >> CLK_I2S3_SEL_SHIFT;
	div = (con & CLK_I2S3_SRC_DIV_MASK) >> CLK_I2S3_SRC_DIV_SHIFT;
	p_src = (con & CLK_I2S3_SRC_SEL_MASK) >> CLK_I2S3_SRC_SEL_SHIFT;
	if (p_src == CLK_I2S3_SRC_SEL_GPLL)
		p_rate = priv->gpll_hz;
	else if (p_src == CLK_I2S3_SRC_SEL_CPLL)
		p_rate = priv->cpll_hz;
	else
		p_rate = priv->npll_hz;
	if (src == CLK_I2S3_SEL_SRC) {
		return DIV_TO_RATE(p_rate, div);
	} else if (src == CLK_I2S3_SEL_FRAC) {
		fracdiv = readl(&cru->clksel_con[reg + 1]);
		n = fracdiv & CLK_I2S3_FRAC_NUMERATOR_MASK;
		n >>= CLK_I2S3_FRAC_NUMERATOR_SHIFT;
		m = fracdiv & CLK_I2S3_FRAC_DENOMINATOR_MASK;
		m >>= CLK_I2S3_FRAC_DENOMINATOR_SHIFT;
		return DIV_TO_RATE(p_rate, div) * n / m;
	} else {
		return OSC_HZ / 2;
	}
}

static ulong rk3568_i2s3_set_rate(struct rk3568_clk_priv *priv,
				  ulong clk_id, ulong rate)
{
	struct rk3568_cru *cru = priv->cru;
	struct rk3568_grf *grf = priv->grf;
	u32 reg, con, clk_src, i2s_src, div;
	unsigned long m = 0, n = 0, val;

	if (priv->gpll_hz % rate == 0) {
		clk_src = CLK_I2S3_SRC_SEL_GPLL;
		i2s_src = CLK_I2S3_SEL_SRC;
		div = DIV_ROUND_UP(priv->gpll_hz, rate);
	} else if (priv->cpll_hz % rate == 0) {
		clk_src = CLK_I2S3_SRC_SEL_CPLL;
		i2s_src = CLK_I2S3_SEL_SRC;
		div = DIV_ROUND_UP(priv->gpll_hz, rate);
	} else if (rate == OSC_HZ / 2) {
		clk_src = CLK_I2S3_SRC_SEL_GPLL;
		i2s_src = CLK_I2S3_SEL_XIN12M;
		div = 1;
	} else {
		clk_src = CLK_I2S3_SRC_SEL_GPLL;
		i2s_src = CLK_I2S3_SEL_FRAC;
		div = 1;
		rational_best_approximation(rate, priv->gpll_hz / div,
					    GENMASK(16 - 1, 0),
					    GENMASK(16 - 1, 0),
					    &m, &n);
	}

	switch (clk_id) {
	case I2S3_MCLKOUT_TX:
		if (rate == 12000000) {
			rk_clrsetreg(&cru->clksel_con[21],
				     I2S3_MCLKOUT_TX_SEL_MASK,
				     I2S3_MCLKOUT_TX_SEL_12M <<
				     I2S3_MCLKOUT_TX_SEL_SHIFT);
		} else {
			rk3568_i2s3_set_rate(priv, MCLK_I2S3_2CH_TX, rate),
			rk_clrsetreg(&cru->clksel_con[21],
				     I2S3_MCLKOUT_TX_SEL_MASK,
				     I2S3_MCLKOUT_TX_SEL_MCLK <<
				     I2S3_MCLKOUT_TX_SEL_SHIFT);
		}
		return rk3568_i2s3_get_rate(priv, clk_id);
	case I2S3_MCLKOUT_RX:
		if (rate == 12000000) {
			rk_clrsetreg(&cru->clksel_con[83],
				     I2S3_MCLKOUT_TX_SEL_MASK,
				     I2S3_MCLKOUT_TX_SEL_12M <<
				     I2S3_MCLKOUT_TX_SEL_SHIFT);
		} else {
			rk3568_i2s3_set_rate(priv, MCLK_I2S3_2CH_RX, rate),
			rk_clrsetreg(&cru->clksel_con[21],
				     I2S3_MCLKOUT_TX_SEL_MASK,
				     I2S3_MCLKOUT_TX_SEL_MCLK <<
				     I2S3_MCLKOUT_TX_SEL_SHIFT);
		}
		return rk3568_i2s3_get_rate(priv, clk_id);
	case I2S3_MCLKOUT:
		con = readl(&grf->soc_con2);
		clk_src = (con & I2S3_MCLKOUT_SEL_MASK)
		      >> I2S3_MCLKOUT_SEL_SHIFT;
		if (clk_src == I2S3_MCLKOUT_SEL_RX)
			rk3568_i2s3_set_rate(priv, I2S3_MCLKOUT_RX, rate);
		else
			rk3568_i2s3_set_rate(priv, I2S3_MCLKOUT_TX, rate);
		return rk3568_i2s3_get_rate(priv, clk_id);
	case MCLK_I2S3_2CH_RX:
		reg = 83;
		break;
	case MCLK_I2S3_2CH_TX:
		reg = 21;
		break;
	default:
		return -ENOENT;
	}

	rk_clrsetreg(&cru->clksel_con[reg],
		     CLK_I2S3_SEL_MASK | CLK_I2S3_SRC_SEL_MASK |
		     CLK_I2S3_SRC_DIV_MASK,
		     (clk_src << CLK_I2S3_SRC_SEL_SHIFT) |
		     (i2s_src << CLK_I2S3_SEL_SHIFT) |
		     ((div - 1) << CLK_I2S3_SRC_DIV_SHIFT));
	if (m && n) {
		val = m << CLK_I2S3_FRAC_NUMERATOR_SHIFT | n;
		writel(val, &cru->clksel_con[reg + 1]);
	}
	return rk3568_i2s3_get_rate(priv, clk_id);
}

#endif

static ulong rk3568_clk_get_rate(struct clk *clk)
{
	struct rk3568_clk_priv *priv = dev_get_priv(clk->dev);
	ulong rate = 0;

	if (!priv->gpll_hz) {
		printf("%s gpll=%lu\n", __func__, priv->gpll_hz);
		return -ENOENT;
	}

	switch (clk->id) {
	case PLL_APLL:
	case ARMCLK:
		rate = rockchip_pll_get_rate(&rk3568_pll_clks[APLL], priv->cru,
					     APLL);
		break;
	case PLL_CPLL:
		rate = rockchip_pll_get_rate(&rk3568_pll_clks[CPLL], priv->cru,
					     CPLL);
		break;
	case PLL_GPLL:
		rate = rockchip_pll_get_rate(&rk3568_pll_clks[GPLL], priv->cru,
					     GPLL);
		break;
	case PLL_NPLL:
		rate = rockchip_pll_get_rate(&rk3568_pll_clks[NPLL], priv->cru,
					     NPLL);
		break;
	case PLL_VPLL:
		rate = rockchip_pll_get_rate(&rk3568_pll_clks[VPLL], priv->cru,
					     VPLL);
		break;
	case PLL_DPLL:
		rate = rockchip_pll_get_rate(&rk3568_pll_clks[DPLL], priv->cru,
					     DPLL);
		break;
	case ACLK_BUS:
	case PCLK_BUS:
	case PCLK_WDT_NS:
		rate = rk3568_bus_get_clk(priv, clk->id);
		break;
	case ACLK_PERIMID:
	case HCLK_PERIMID:
		rate = rk3568_perimid_get_clk(priv, clk->id);
		break;
	case ACLK_TOP_HIGH:
	case ACLK_TOP_LOW:
	case HCLK_TOP:
	case PCLK_TOP:
		rate = rk3568_top_get_clk(priv, clk->id);
		break;
	case CLK_I2C1:
	case CLK_I2C2:
	case CLK_I2C3:
	case CLK_I2C4:
	case CLK_I2C5:
		rate = rk3568_i2c_get_clk(priv, clk->id);
		break;
	case CLK_SPI0:
	case CLK_SPI1:
	case CLK_SPI2:
	case CLK_SPI3:
		rate = rk3568_spi_get_clk(priv, clk->id);
		break;
	case CLK_PWM1:
	case CLK_PWM2:
	case CLK_PWM3:
		rate = rk3568_pwm_get_clk(priv, clk->id);
		break;
	case CLK_SARADC:
	case CLK_TSADC_TSEN:
	case CLK_TSADC:
		rate = rk3568_adc_get_clk(priv, clk->id);
		break;
	case HCLK_SDMMC0:
	case CLK_SDMMC0:
	case CLK_SDMMC1:
	case CLK_SDMMC2:
		rate = rk3568_sdmmc_get_clk(priv, clk->id);
		break;
	case SCLK_SFC:
		rate = rk3568_sfc_get_clk(priv);
		break;
	case NCLK_NANDC:
		rate = rk3568_nand_get_clk(priv);
		break;
	case CCLK_EMMC:
		rate = rk3568_emmc_get_clk(priv);
		break;
	case BCLK_EMMC:
		rate = rk3568_emmc_get_bclk(priv);
		break;
	case TCLK_EMMC:
		rate = OSC_HZ;
		break;
#ifndef CONFIG_SPL_BUILD
	case ACLK_VOP:
		rate = rk3568_aclk_vop_get_clk(priv);
		break;
	case DCLK_VOP0:
	case DCLK_VOP1:
	case DCLK_VOP2:
		rate = rk3568_dclk_vop_get_clk(priv, clk->id);
		break;
	case SCLK_GMAC0:
	case CLK_MAC0_2TOP:
	case CLK_MAC0_REFOUT:
		rate = rk3568_gmac_src_get_clk(priv, 0);
		break;
	case CLK_MAC0_OUT:
		rate = rk3568_gmac_out_get_clk(priv, 0);
		break;
	case CLK_GMAC0_PTP_REF:
		rate = rk3568_gmac_ptp_ref_get_clk(priv, 0);
		break;
	case SCLK_GMAC1:
	case CLK_MAC1_2TOP:
	case CLK_MAC1_REFOUT:
		rate = rk3568_gmac_src_get_clk(priv, 1);
		break;
	case CLK_MAC1_OUT:
		rate = rk3568_gmac_out_get_clk(priv, 1);
		break;
	case CLK_GMAC1_PTP_REF:
		rate = rk3568_gmac_ptp_ref_get_clk(priv, 1);
		break;
	case DCLK_EBC:
		rate = rk3568_ebc_get_clk(priv);
		break;
	case ACLK_RKVDEC_PRE:
	case ACLK_RKVDEC:
	case CLK_RKVDEC_CORE:
		rate = rk3568_rkvdec_get_clk(priv, clk->id);
		break;
	case TCLK_WDT_NS:
		rate = OSC_HZ;
		break;
	case SCLK_UART1:
	case SCLK_UART2:
	case SCLK_UART3:
	case SCLK_UART4:
	case SCLK_UART5:
	case SCLK_UART6:
	case SCLK_UART7:
	case SCLK_UART8:
	case SCLK_UART9:
		rate = rk3568_uart_get_rate(priv, clk->id);
		break;
	case I2S3_MCLKOUT_RX:
	case I2S3_MCLKOUT_TX:
	case MCLK_I2S3_2CH_RX:
	case MCLK_I2S3_2CH_TX:
	case I2S3_MCLKOUT:
		rate = rk3568_i2s3_get_rate(priv, clk->id);
		break;
#endif
	case ACLK_SECURE_FLASH:
	case ACLK_CRYPTO_NS:
	case HCLK_SECURE_FLASH:
	case HCLK_CRYPTO_NS:
	case CLK_CRYPTO_NS_RNG:
	case CLK_CRYPTO_NS_CORE:
	case CLK_CRYPTO_NS_PKA:
		rate = rk3568_crypto_get_rate(priv, clk->id);
		break;
	case CPLL_500M:
	case CPLL_333M:
	case CPLL_250M:
	case CPLL_125M:
	case CPLL_100M:
	case CPLL_62P5M:
	case CPLL_50M:
	case CPLL_25M:
		rate = rk3568_cpll_div_get_rate(priv, clk->id);
		break;
	default:
		return -ENOENT;
	}

	return rate;
};

static ulong rk3568_clk_set_rate(struct clk *clk, ulong rate)
{
	struct rk3568_clk_priv *priv = dev_get_priv(clk->dev);
	ulong ret = 0;

	if (!priv->gpll_hz) {
		printf("%s gpll=%lu\n", __func__, priv->gpll_hz);
		return -ENOENT;
	}

	switch (clk->id) {
	case PLL_APLL:
	case ARMCLK:
		if (priv->armclk_hz)
			rk3568_armclk_set_clk(priv, rate);
		priv->armclk_hz = rate;
		break;
	case PLL_CPLL:
		ret = rockchip_pll_set_rate(&rk3568_pll_clks[CPLL], priv->cru,
					    CPLL, rate);
		priv->cpll_hz = rockchip_pll_get_rate(&rk3568_pll_clks[CPLL],
						      priv->cru, CPLL);
		break;
	case PLL_GPLL:
		ret = rockchip_pll_set_rate(&rk3568_pll_clks[GPLL], priv->cru,
					    GPLL, rate);
		priv->gpll_hz = rockchip_pll_get_rate(&rk3568_pll_clks[GPLL],
						      priv->cru, GPLL);
		break;
	case PLL_NPLL:
		ret = rockchip_pll_set_rate(&rk3568_pll_clks[NPLL], priv->cru,
					    NPLL, rate);
		break;
	case PLL_VPLL:
		ret = rockchip_pll_set_rate(&rk3568_pll_clks[VPLL], priv->cru,
					    VPLL, rate);
		priv->vpll_hz = rockchip_pll_get_rate(&rk3568_pll_clks[VPLL],
						      priv->cru,
						      VPLL);
		break;
	case ACLK_BUS:
	case PCLK_BUS:
	case PCLK_WDT_NS:
		ret = rk3568_bus_set_clk(priv, clk->id, rate);
		break;
	case ACLK_PERIMID:
	case HCLK_PERIMID:
		ret = rk3568_perimid_set_clk(priv, clk->id, rate);
		break;
	case ACLK_TOP_HIGH:
	case ACLK_TOP_LOW:
	case HCLK_TOP:
	case PCLK_TOP:
		ret = rk3568_top_set_clk(priv, clk->id, rate);
		break;
	case CLK_I2C1:
	case CLK_I2C2:
	case CLK_I2C3:
	case CLK_I2C4:
	case CLK_I2C5:
		ret = rk3568_i2c_set_clk(priv, clk->id, rate);
		break;
	case CLK_SPI0:
	case CLK_SPI1:
	case CLK_SPI2:
	case CLK_SPI3:
		ret = rk3568_spi_set_clk(priv, clk->id, rate);
		break;
	case CLK_PWM1:
	case CLK_PWM2:
	case CLK_PWM3:
		ret = rk3568_pwm_set_clk(priv, clk->id, rate);
		break;
	case CLK_SARADC:
	case CLK_TSADC_TSEN:
	case CLK_TSADC:
		ret = rk3568_adc_set_clk(priv, clk->id, rate);
		break;
	case HCLK_SDMMC0:
	case CLK_SDMMC0:
	case CLK_SDMMC1:
	case CLK_SDMMC2:
		ret = rk3568_sdmmc_set_clk(priv, clk->id, rate);
		break;
	case SCLK_SFC:
		ret = rk3568_sfc_set_clk(priv, rate);
		break;
	case NCLK_NANDC:
		ret = rk3568_nand_set_clk(priv, rate);
		break;
	case CCLK_EMMC:
		ret = rk3568_emmc_set_clk(priv, rate);
		break;
	case BCLK_EMMC:
		ret = rk3568_emmc_set_bclk(priv, rate);
		break;
	case TCLK_EMMC:
		ret = OSC_HZ;
		break;
#ifndef CONFIG_SPL_BUILD
	case ACLK_VOP:
		ret = rk3568_aclk_vop_set_clk(priv, rate);
		break;
	case DCLK_VOP0:
	case DCLK_VOP1:
	case DCLK_VOP2:
		ret = rk3568_dclk_vop_set_clk(priv, clk->id, rate);
		break;
	case SCLK_GMAC0:
	case CLK_MAC0_2TOP:
	case CLK_MAC0_REFOUT:
		ret = rk3568_gmac_src_set_clk(priv, 0, rate);
		break;
	case CLK_MAC0_OUT:
		ret = rk3568_gmac_out_set_clk(priv, 0, rate);
		break;
	case SCLK_GMAC0_RX_TX:
		ret = rk3568_gmac_tx_rx_set_clk(priv, 0, rate);
		break;
	case CLK_GMAC0_PTP_REF:
		ret = rk3568_gmac_ptp_ref_set_clk(priv, 0, rate);
		break;
	case SCLK_GMAC1:
	case CLK_MAC1_2TOP:
	case CLK_MAC1_REFOUT:
		ret = rk3568_gmac_src_set_clk(priv, 1, rate);
		break;
	case CLK_MAC1_OUT:
		ret = rk3568_gmac_out_set_clk(priv, 1, rate);
		break;
	case SCLK_GMAC1_RX_TX:
		ret = rk3568_gmac_tx_rx_set_clk(priv, 1, rate);
		break;
	case CLK_GMAC1_PTP_REF:
		ret = rk3568_gmac_ptp_ref_set_clk(priv, 1, rate);
		break;
	case DCLK_EBC:
		ret = rk3568_ebc_set_clk(priv, rate);
		break;
	case ACLK_RKVDEC_PRE:
	case ACLK_RKVDEC:
	case CLK_RKVDEC_CORE:
		ret = rk3568_rkvdec_set_clk(priv, clk->id, rate);
		break;
	case TCLK_WDT_NS:
		ret = OSC_HZ;
		break;
	case SCLK_UART1:
	case SCLK_UART2:
	case SCLK_UART3:
	case SCLK_UART4:
	case SCLK_UART5:
	case SCLK_UART6:
	case SCLK_UART7:
	case SCLK_UART8:
	case SCLK_UART9:
		ret = rk3568_uart_set_rate(priv, clk->id, rate);
		break;
	case I2S3_MCLKOUT_RX:
	case I2S3_MCLKOUT_TX:
	case MCLK_I2S3_2CH_RX:
	case MCLK_I2S3_2CH_TX:
	case I2S3_MCLKOUT:
		ret = rk3568_i2s3_set_rate(priv, clk->id, rate);
		break;
#endif
	case ACLK_SECURE_FLASH:
	case ACLK_CRYPTO_NS:
	case HCLK_SECURE_FLASH:
	case HCLK_CRYPTO_NS:
	case CLK_CRYPTO_NS_RNG:
	case CLK_CRYPTO_NS_CORE:
	case CLK_CRYPTO_NS_PKA:
		ret = rk3568_crypto_set_rate(priv, clk->id, rate);
		break;
	case CPLL_500M:
	case CPLL_333M:
	case CPLL_250M:
	case CPLL_125M:
	case CPLL_100M:
	case CPLL_62P5M:
	case CPLL_50M:
	case CPLL_25M:
		ret = rk3568_cpll_div_set_rate(priv, clk->id, rate);
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

int rk3568_mmc_get_phase(struct clk *clk)
{
	struct rk3568_clk_priv *priv = dev_get_priv(clk->dev);
	struct rk3568_cru *cru = priv->cru;
	u32 raw_value, delay_num;
	u16 degrees = 0;
	ulong rate;

	rate = rk3568_clk_get_rate(clk);
	if (rate < 0)
		return rate;

	if (clk->id == SCLK_EMMC_SAMPLE)
		raw_value = readl(&cru->emmc_con[1]);
	else if (clk->id == SCLK_SDMMC0_SAMPLE)
		raw_value = readl(&cru->sdmmc0_con[1]);
	else if (clk->id == SCLK_SDMMC1_SAMPLE)
		raw_value = readl(&cru->sdmmc1_con[1]);
	else
		raw_value = readl(&cru->sdmmc2_con[1]);

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

int rk3568_mmc_set_phase(struct clk *clk, u32 degrees)
{
	struct rk3568_clk_priv *priv = dev_get_priv(clk->dev);
	struct rk3568_cru *cru = priv->cru;
	u8 nineties, remainder, delay_num;
	u32 raw_value, delay;
	ulong rate;

	rate = rk3568_clk_get_rate(clk);
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
	else if (clk->id == SCLK_SDMMC0_SAMPLE)
		writel(raw_value | 0xffff0000, &cru->sdmmc0_con[1]);
	else if (clk->id == SCLK_SDMMC1_SAMPLE)
		writel(raw_value | 0xffff0000, &cru->sdmmc1_con[1]);
	else
		writel(raw_value | 0xffff0000, &cru->sdmmc2_con[1]);

	debug("mmc set_phase(%d) delay_nums=%u reg=%#x actual_degrees=%d\n",
	      degrees, delay_num, raw_value, rk3568_mmc_get_phase(clk));

	return 0;
}

static int rk3568_clk_get_phase(struct clk *clk)
{
	int ret;

	debug("%s %ld\n", __func__, clk->id);
	switch (clk->id) {
	case SCLK_EMMC_SAMPLE:
	case SCLK_SDMMC0_SAMPLE:
	case SCLK_SDMMC1_SAMPLE:
	case SCLK_SDMMC2_SAMPLE:
		ret = rk3568_mmc_get_phase(clk);
		break;
	default:
		return -ENOENT;
	}

	return ret;
}

static int rk3568_clk_set_phase(struct clk *clk, int degrees)
{
	int ret;

	debug("%s %ld\n", __func__, clk->id);
	switch (clk->id) {
	case SCLK_EMMC_SAMPLE:
	case SCLK_SDMMC0_SAMPLE:
	case SCLK_SDMMC1_SAMPLE:
	case SCLK_SDMMC2_SAMPLE:
		ret = rk3568_mmc_set_phase(clk, degrees);
		break;
	default:
		return -ENOENT;
	}

	return ret;
}

#if (IS_ENABLED(OF_CONTROL)) || (!IS_ENABLED(OF_PLATDATA))
static int rk3568_gmac0_src_set_parent(struct clk *clk, struct clk *parent)
{
	struct rk3568_clk_priv *priv = dev_get_priv(clk->dev);
	struct rk3568_cru *cru = priv->cru;

	if (parent->id == CLK_MAC0_2TOP)
		rk_clrsetreg(&cru->clksel_con[31],
			     RMII0_EXTCLK_SEL_MASK,
			     RMII0_EXTCLK_SEL_MAC0_TOP <<
			     RMII0_EXTCLK_SEL_SHIFT);
	else
		rk_clrsetreg(&cru->clksel_con[31],
			     RMII0_EXTCLK_SEL_MASK,
			     RMII0_EXTCLK_SEL_IO << RMII0_EXTCLK_SEL_SHIFT);
	return 0;
}

static int rk3568_gmac1_src_set_parent(struct clk *clk, struct clk *parent)
{
	struct rk3568_clk_priv *priv = dev_get_priv(clk->dev);
	struct rk3568_cru *cru = priv->cru;

	if (parent->id == CLK_MAC1_2TOP)
		rk_clrsetreg(&cru->clksel_con[33],
			     RMII0_EXTCLK_SEL_MASK,
			     RMII0_EXTCLK_SEL_MAC0_TOP <<
			     RMII0_EXTCLK_SEL_SHIFT);
	else
		rk_clrsetreg(&cru->clksel_con[33],
			     RMII0_EXTCLK_SEL_MASK,
			     RMII0_EXTCLK_SEL_IO << RMII0_EXTCLK_SEL_SHIFT);
	return 0;
}

static int rk3568_gmac0_tx_rx_set_parent(struct clk *clk, struct clk *parent)
{
	struct rk3568_clk_priv *priv = dev_get_priv(clk->dev);
	struct rk3568_cru *cru = priv->cru;

	if (parent->id == SCLK_GMAC0_RGMII_SPEED)
		rk_clrsetreg(&cru->clksel_con[31],
			     RMII0_MODE_MASK,
			     RMII0_MODE_SEL_RGMII << RMII0_MODE_SHIFT);
	else if (parent->id == SCLK_GMAC0_RMII_SPEED)
		rk_clrsetreg(&cru->clksel_con[31],
			     RMII0_MODE_MASK,
			     RMII0_MODE_SEL_RMII << RMII0_MODE_SHIFT);
	else
		rk_clrsetreg(&cru->clksel_con[31],
			     RMII0_MODE_MASK,
			     RMII0_MODE_SEL_GMII << RMII0_MODE_SHIFT);

	return 0;
}

static int rk3568_gmac1_tx_rx_set_parent(struct clk *clk, struct clk *parent)
{
	struct rk3568_clk_priv *priv = dev_get_priv(clk->dev);
	struct rk3568_cru *cru = priv->cru;

	if (parent->id == SCLK_GMAC1_RGMII_SPEED)
		rk_clrsetreg(&cru->clksel_con[33],
			     RMII0_MODE_MASK,
			     RMII0_MODE_SEL_RGMII << RMII0_MODE_SHIFT);
	else if (parent->id == SCLK_GMAC1_RMII_SPEED)
		rk_clrsetreg(&cru->clksel_con[33],
			     RMII0_MODE_MASK,
			     RMII0_MODE_SEL_RMII << RMII0_MODE_SHIFT);
	else
		rk_clrsetreg(&cru->clksel_con[33],
			     RMII0_MODE_MASK,
			     RMII0_MODE_SEL_GMII << RMII0_MODE_SHIFT);

	return 0;
}

static int __maybe_unused rk3568_dclk_vop_set_parent(struct clk *clk,
						     struct clk *parent)
{
	struct rk3568_clk_priv *priv = dev_get_priv(clk->dev);
	struct rk3568_cru *cru = priv->cru;
	u32 con_id;

	switch (clk->id) {
	case DCLK_VOP0:
		con_id = 39;
		break;
	case DCLK_VOP1:
		con_id = 40;
		break;
	case DCLK_VOP2:
		con_id = 41;
		break;
	default:
		return -EINVAL;
	}
	if (parent->id == PLL_VPLL) {
		rk_clrsetreg(&cru->clksel_con[con_id], DCLK0_VOP_SEL_MASK,
			     DCLK_VOP_SEL_VPLL << DCLK0_VOP_SEL_SHIFT);
	} else {
		rk_clrsetreg(&cru->clksel_con[con_id], DCLK0_VOP_SEL_MASK,
			     DCLK_VOP_SEL_HPLL << DCLK0_VOP_SEL_SHIFT);
	}

	return 0;
}

static int __maybe_unused rk3568_rkvdec_set_parent(struct clk *clk,
						   struct clk *parent)
{
	struct rk3568_clk_priv *priv = dev_get_priv(clk->dev);
	struct rk3568_cru *cru = priv->cru;
	u32 con_id, mask, shift;

	switch (clk->id) {
	case ACLK_RKVDEC_PRE:
		con_id = 47;
		mask = ACLK_RKVDEC_SEL_MASK;
		shift = ACLK_RKVDEC_SEL_SHIFT;
		break;
	case CLK_RKVDEC_CORE:
		con_id = 49;
		mask = CLK_RKVDEC_CORE_SEL_MASK;
		shift = CLK_RKVDEC_CORE_SEL_SHIFT;
		break;
	default:
		return -EINVAL;
	}
	if (parent->id == PLL_CPLL) {
		rk_clrsetreg(&cru->clksel_con[con_id], mask,
			     ACLK_RKVDEC_SEL_CPLL << shift);
	} else {
		rk_clrsetreg(&cru->clksel_con[con_id], mask,
			     ACLK_RKVDEC_SEL_GPLL << shift);
	}

	return 0;
}

static int __maybe_unused rk3568_i2s3_set_parent(struct clk *clk,
						 struct clk *parent)
{
	struct rk3568_clk_priv *priv = dev_get_priv(clk->dev);
	struct rk3568_grf *grf = priv->grf;

	switch (clk->id) {
	case I2S3_MCLK_IOE:
		if (parent->id == I2S3_MCLKOUT) {
			rk_clrsetreg(&grf->soc_con2, I2S3_MCLK_IOE_SEL_MASK,
				     I2S3_MCLK_IOE_SEL_CLKOUT <<
				     I2S3_MCLK_IOE_SEL_SHIFT);
		} else {
			rk_clrsetreg(&grf->soc_con2, I2S3_MCLK_IOE_SEL_MASK,
				     I2S3_MCLK_IOE_SEL_CLKIN <<
				     I2S3_MCLK_IOE_SEL_SHIFT);
		}
		break;
	case I2S3_MCLKOUT:
		if (parent->id == I2S3_MCLKOUT_RX) {
			rk_clrsetreg(&grf->soc_con2, I2S3_MCLKOUT_SEL_MASK,
				     I2S3_MCLKOUT_SEL_RX <<
				     I2S3_MCLKOUT_SEL_SHIFT);
		} else {
			rk_clrsetreg(&grf->soc_con2, I2S3_MCLKOUT_SEL_MASK,
				     I2S3_MCLKOUT_SEL_TX <<
				     I2S3_MCLKOUT_SEL_SHIFT);
		}
		break;
	default:
		return -EINVAL;
	}

	return 0;
}

static int rk3568_clk_set_parent(struct clk *clk, struct clk *parent)
{
	switch (clk->id) {
	case SCLK_GMAC0:
		return rk3568_gmac0_src_set_parent(clk, parent);
	case SCLK_GMAC1:
		return rk3568_gmac1_src_set_parent(clk, parent);
	case SCLK_GMAC0_RX_TX:
		return rk3568_gmac0_tx_rx_set_parent(clk, parent);
	case SCLK_GMAC1_RX_TX:
		return rk3568_gmac1_tx_rx_set_parent(clk, parent);
	case DCLK_VOP0:
	case DCLK_VOP1:
	case DCLK_VOP2:
		return rk3568_dclk_vop_set_parent(clk, parent);
	case ACLK_RKVDEC_PRE:
	case CLK_RKVDEC_CORE:
		return rk3568_rkvdec_set_parent(clk, parent);
	case I2S3_MCLK_IOE:
	case I2S3_MCLKOUT:
		return rk3568_i2s3_set_parent(clk, parent);
	default:
		return -ENOENT;
	}

	return 0;
}
#endif

static struct clk_ops rk3568_clk_ops = {
	.get_rate = rk3568_clk_get_rate,
	.set_rate = rk3568_clk_set_rate,
	.get_phase = rk3568_clk_get_phase,
	.set_phase = rk3568_clk_set_phase,
#if (IS_ENABLED(OF_CONTROL)) || (!IS_ENABLED(OF_PLATDATA))
	.set_parent = rk3568_clk_set_parent,
#endif
};

static void rk3568_clk_init(struct rk3568_clk_priv *priv)
{
	int ret;

	priv->sync_kernel = false;
	if (!priv->armclk_enter_hz) {
		priv->armclk_enter_hz =
			rockchip_pll_get_rate(&rk3568_pll_clks[APLL],
					      priv->cru, APLL);
		priv->armclk_init_hz = priv->armclk_enter_hz;
	}

	if (priv->armclk_init_hz != APLL_HZ) {
		ret = rk3568_armclk_set_clk(priv, APLL_HZ);
		if (!ret)
			priv->armclk_init_hz = APLL_HZ;
	}
	if (priv->cpll_hz != CPLL_HZ) {
		ret = rockchip_pll_set_rate(&rk3568_pll_clks[CPLL], priv->cru,
					    CPLL, CPLL_HZ);
		if (!ret)
			priv->cpll_hz = CPLL_HZ;
	}
	if (priv->gpll_hz != GPLL_HZ) {
		ret = rockchip_pll_set_rate(&rk3568_pll_clks[GPLL], priv->cru,
					    GPLL, GPLL_HZ);
		if (!ret)
			priv->gpll_hz = GPLL_HZ;
	}

#ifdef CONFIG_SPL_BUILD
	ret = rk3568_bus_set_clk(priv, ACLK_BUS, 150000000);
	if (ret < 0)
		printf("Fail to set the ACLK_BUS clock.\n");
#endif

	priv->ppll_hz = rk3568_pmu_pll_get_rate(priv, PPLL);
	priv->hpll_hz = rk3568_pmu_pll_get_rate(priv, HPLL);
}

static int rk3568_clk_probe(struct udevice *dev)
{
	struct rk3568_clk_priv *priv = dev_get_priv(dev);
	int ret;

	priv->grf = syscon_get_first_range(ROCKCHIP_SYSCON_GRF);
	if (IS_ERR(priv->grf))
		return PTR_ERR(priv->grf);

	rk3568_clk_init(priv);

	/* Process 'assigned-{clocks/clock-parents/clock-rates}' properties */
	ret = clk_set_defaults(dev);
	if (ret)
		debug("%s clk_set_defaults failed %d\n", __func__, ret);
	else
		priv->sync_kernel = true;

	return 0;
}

static int rk3568_clk_ofdata_to_platdata(struct udevice *dev)
{
	struct rk3568_clk_priv *priv = dev_get_priv(dev);

	priv->cru = dev_read_addr_ptr(dev);

	return 0;
}

static int rk3568_clk_bind(struct udevice *dev)
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
		priv->glb_srst_fst_value = offsetof(struct rk3568_cru,
						    glb_srst_fst);
		priv->glb_srst_snd_value = offsetof(struct rk3568_cru,
						    glb_srsr_snd);
		sys_child->priv = priv;
	}

	ret = device_bind_driver_to_node(dev, "rockchip_reset", "reset",
					 dev_ofnode(dev), &sf_child);
	if (ret) {
		debug("Warning: No rockchip reset driver: ret=%d\n", ret);
	} else {
		sf_priv = malloc(sizeof(struct softreset_reg));
		sf_priv->sf_reset_offset = offsetof(struct rk3568_cru,
						    softrst_con[0]);
		sf_priv->sf_reset_num = 30;
		sf_child->priv = sf_priv;
	}

	return 0;
}

static const struct udevice_id rk3568_clk_ids[] = {
	{ .compatible = "rockchip,rk3568-cru" },
	{ }
};

U_BOOT_DRIVER(rockchip_rk3568_cru) = {
	.name		= "rockchip_rk3568_cru",
	.id		= UCLASS_CLK,
	.of_match	= rk3568_clk_ids,
	.priv_auto_alloc_size = sizeof(struct rk3568_clk_priv),
	.ofdata_to_platdata = rk3568_clk_ofdata_to_platdata,
	.ops		= &rk3568_clk_ops,
	.bind		= rk3568_clk_bind,
	.probe		= rk3568_clk_probe,
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
	struct rk3568_clk_priv *priv;
	const struct rk3568_clk_info *clk_dump;
	struct clk clk;
	unsigned long clk_count = ARRAY_SIZE(clks_dump);
	unsigned long rate;
	int i, ret;

	ret = uclass_get_device_by_driver(UCLASS_CLK,
					  DM_GET_DRIVER(rockchip_rk3568_cru),
					  &cru_dev);
	if (ret) {
		printf("%s failed to get cru device\n", __func__);
		return ret;
	}

	ret = uclass_get_device_by_driver(UCLASS_CLK,
					  DM_GET_DRIVER(rockchip_rk3568_pmucru),
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
