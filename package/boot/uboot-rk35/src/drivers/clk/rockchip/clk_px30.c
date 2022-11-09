/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:	GPL-2.0
 */

#include <common.h>
#include <bitfield.h>
#include <clk-uclass.h>
#include <dm.h>
#include <errno.h>
#include <syscon.h>
#include <asm/arch-rockchip/clock.h>
#include <asm/arch-rockchip/cpu.h>
#include <asm/arch-rockchip/cru_px30.h>
#include <asm/arch-rockchip/hardware.h>
#include <asm/io.h>
#include <dm/lists.h>
#include <dt-bindings/clock/px30-cru.h>

DECLARE_GLOBAL_DATA_PTR;

enum {
	VCO_MAX_HZ	= 3200U * 1000000,
	VCO_MIN_HZ	= 800 * 1000000,
	OUTPUT_MAX_HZ	= 3200U * 1000000,
	OUTPUT_MIN_HZ	= 24 * 1000000,
};

#define PX30_VOP_PLL_LIMIT			600000000

#define PX30_PLL_RATE(_rate, _refdiv, _fbdiv, _postdiv1,	\
			_postdiv2, _dsmpd, _frac)		\
{								\
	.rate	= _rate##U,					\
	.fbdiv = _fbdiv,					\
	.postdiv1 = _postdiv1,					\
	.refdiv = _refdiv,					\
	.postdiv2 = _postdiv2,					\
	.dsmpd = _dsmpd,					\
	.frac = _frac,						\
}

#define PX30_CPUCLK_RATE(_rate, _aclk_div, _pclk_div)		\
{								\
	.rate	= _rate##U,					\
	.aclk_div = _aclk_div,					\
	.pclk_div = _pclk_div,					\
}

#define DIV_TO_RATE(input_rate, div)    ((input_rate) / ((div) + 1))

#define PX30_CLK_DUMP(_id, _name, _iscru)	\
{						\
	.id = _id,				\
	.name = _name,				\
	.is_cru = _iscru,			\
}

static struct pll_rate_table px30_pll_rates[] = {
	/* _mhz, _refdiv, _fbdiv, _postdiv1, _postdiv2, _dsmpd, _frac */
	PX30_PLL_RATE(1200000000, 1, 50, 1, 1, 1, 0),
	PX30_PLL_RATE(1188000000, 2, 99, 1, 1, 1, 0),
	PX30_PLL_RATE(1100000000, 12, 550, 1, 1, 1, 0),
	PX30_PLL_RATE(1008000000, 1, 84, 2, 1, 1, 0),
	PX30_PLL_RATE(1000000000, 6, 500, 2, 1, 1, 0),
	PX30_PLL_RATE(816000000, 1, 68, 2, 1, 1, 0),
	PX30_PLL_RATE(600000000, 1, 75, 3, 1, 1, 0),
};

static const struct px30_clk_info clks_dump[] = {
	PX30_CLK_DUMP(PLL_APLL, "apll", true),
	PX30_CLK_DUMP(PLL_DPLL, "dpll", true),
	PX30_CLK_DUMP(PLL_CPLL, "cpll", true),
	PX30_CLK_DUMP(PLL_NPLL, "npll", true),
	PX30_CLK_DUMP(PLL_GPLL, "gpll", false),
	PX30_CLK_DUMP(ACLK_BUS_PRE, "aclk_bus", true),
	PX30_CLK_DUMP(HCLK_BUS_PRE, "hclk_bus", true),
	PX30_CLK_DUMP(PCLK_BUS_PRE, "pclk_bus", true),
	PX30_CLK_DUMP(ACLK_PERI_PRE, "aclk_peri", true),
	PX30_CLK_DUMP(HCLK_PERI_PRE, "hclk_peri", true),
	PX30_CLK_DUMP(PCLK_PMU_PRE, "pclk_pmu", false),
};

static struct cpu_rate_table px30_cpu_rates[] = {
	PX30_CPUCLK_RATE(1200000000, 1, 5),
	PX30_CPUCLK_RATE(1008000000, 1, 5),
	PX30_CPUCLK_RATE(816000000, 1, 3),
	PX30_CPUCLK_RATE(600000000, 1, 3),
	PX30_CPUCLK_RATE(408000000, 1, 1),
};

static u8 pll_mode_shift[PLL_COUNT] = {
	APLL_MODE_SHIFT, DPLL_MODE_SHIFT, CPLL_MODE_SHIFT,
	NPLL_MODE_SHIFT, GPLL_MODE_SHIFT
};
static u32 pll_mode_mask[PLL_COUNT] = {
	APLL_MODE_MASK, DPLL_MODE_MASK, CPLL_MODE_MASK,
	NPLL_MODE_MASK, GPLL_MODE_MASK
};

static struct pll_rate_table auto_table;

static ulong px30_clk_get_pll_rate(struct px30_clk_priv *priv,
				   enum px30_pll_id pll_id);

static struct pll_rate_table *pll_clk_set_by_auto(u32 drate)
{
	struct pll_rate_table *rate = &auto_table;
	u32 ref_khz = OSC_HZ / KHz, refdiv, fbdiv = 0;
	u32 postdiv1, postdiv2 = 1;
	u32 fref_khz;
	u32 diff_khz, best_diff_khz;
	const u32 max_refdiv = 63, max_fbdiv = 3200, min_fbdiv = 16;
	const u32 max_postdiv1 = 7, max_postdiv2 = 7;
	u32 vco_khz;
	u32 rate_khz = drate / KHz;

	if (!drate) {
		printf("%s: the frequency can't be 0 Hz\n", __func__);
		return NULL;
	}

	postdiv1 = DIV_ROUND_UP(VCO_MIN_HZ / 1000, rate_khz);
	if (postdiv1 > max_postdiv1) {
		postdiv2 = DIV_ROUND_UP(postdiv1, max_postdiv1);
		postdiv1 = DIV_ROUND_UP(postdiv1, postdiv2);
	}

	vco_khz = rate_khz * postdiv1 * postdiv2;

	if (vco_khz < (VCO_MIN_HZ / KHz) || vco_khz > (VCO_MAX_HZ / KHz) ||
	    postdiv2 > max_postdiv2) {
		printf("%s: Cannot find out a supported VCO for Freq (%uHz)\n",
		       __func__, rate_khz);
		return NULL;
	}

	rate->postdiv1 = postdiv1;
	rate->postdiv2 = postdiv2;

	best_diff_khz = vco_khz;
	for (refdiv = 1; refdiv < max_refdiv && best_diff_khz; refdiv++) {
		fref_khz = ref_khz / refdiv;

		fbdiv = vco_khz / fref_khz;
		if ((fbdiv >= max_fbdiv) || (fbdiv <= min_fbdiv))
			continue;
		diff_khz = vco_khz - fbdiv * fref_khz;
		if (fbdiv + 1 < max_fbdiv && diff_khz > fref_khz / 2) {
			fbdiv++;
			diff_khz = fref_khz - diff_khz;
		}

		if (diff_khz >= best_diff_khz)
			continue;

		best_diff_khz = diff_khz;
		rate->refdiv = refdiv;
		rate->fbdiv = fbdiv;
	}

	if (best_diff_khz > 4 * (MHz / KHz)) {
		printf("%s: Failed to match output frequency %u bestis %u Hz\n",
		       __func__, rate_khz,
		       best_diff_khz * KHz);
		return NULL;
	}

	return rate;
}

static const struct pll_rate_table *get_pll_settings(unsigned long rate)
{
	unsigned int rate_count = ARRAY_SIZE(px30_pll_rates);
	int i;

	for (i = 0; i < rate_count; i++) {
		if (rate == px30_pll_rates[i].rate)
			return &px30_pll_rates[i];
	}

	return pll_clk_set_by_auto(rate);
}

static const struct cpu_rate_table *get_cpu_settings(unsigned long rate)
{
	unsigned int rate_count = ARRAY_SIZE(px30_cpu_rates);
	int i;

	for (i = 0; i < rate_count; i++) {
		if (rate == px30_cpu_rates[i].rate)
			return &px30_cpu_rates[i];
	}

	return NULL;
}

/*
 * How to calculate the PLL(from TRM V0.3 Part 1 Page 63):
 * Formulas also embedded within the Fractional PLL Verilog model:
 * If DSMPD = 1 (DSM is disabled, "integer mode")
 * FOUTVCO = FREF / REFDIV * FBDIV
 * FOUTPOSTDIV = FOUTVCO / POSTDIV1 / POSTDIV2
 * Where:
 * FOUTVCO = Fractional PLL non-divided output frequency
 * FOUTPOSTDIV = Fractional PLL divided output frequency
 *               (output of second post divider)
 * FREF = Fractional PLL input reference frequency, (the OSC_HZ 24MHz input)
 * REFDIV = Fractional PLL input reference clock divider
 * FBDIV = Integer value programmed into feedback divide
 *
 */
static int rkclk_set_pll(struct px30_pll *pll, unsigned int *mode,
			 enum px30_pll_id pll_id,
			 unsigned long drate)
{
	const struct pll_rate_table *rate;
	uint vco_hz, output_hz;

	rate = get_pll_settings(drate);
	if (!rate) {
		printf("%s unsupport rate\n", __func__);
		return -EINVAL;
	}

	/* All PLLs have same VCO and output frequency range restrictions. */
	vco_hz = OSC_HZ / 1000 * rate->fbdiv / rate->refdiv * 1000;
	output_hz = vco_hz / rate->postdiv1 / rate->postdiv2;

	debug("PLL at %p: fb=%d, ref=%d, pst1=%d, pst2=%d, vco=%u Hz, output=%u Hz\n",
	      pll, rate->fbdiv, rate->refdiv, rate->postdiv1,
	      rate->postdiv2, vco_hz, output_hz);
	assert(vco_hz >= VCO_MIN_HZ && vco_hz <= VCO_MAX_HZ &&
	       output_hz >= OUTPUT_MIN_HZ && output_hz <= OUTPUT_MAX_HZ);

	/*
	 * When power on or changing PLL setting,
	 * we must force PLL into slow mode to ensure output stable clock.
	 */
	rk_clrsetreg(mode, pll_mode_mask[pll_id],
		     PLLMUX_FROM_XIN24M << pll_mode_shift[pll_id]);

	/* use integer mode */
	rk_setreg(&pll->con1, 1 << PLL_DSMPD_SHIFT);
	/* Power down */
	rk_setreg(&pll->con1, 1 << PLL_PD_SHIFT);

	rk_clrsetreg(&pll->con0,
		     PLL_POSTDIV1_MASK | PLL_FBDIV_MASK,
		     (rate->postdiv1 << PLL_POSTDIV1_SHIFT) | rate->fbdiv);
	rk_clrsetreg(&pll->con1, PLL_POSTDIV2_MASK | PLL_REFDIV_MASK,
		     (rate->postdiv2 << PLL_POSTDIV2_SHIFT |
		     rate->refdiv << PLL_REFDIV_SHIFT));

	/* Power Up */
	rk_clrreg(&pll->con1, 1 << PLL_PD_SHIFT);

	/* waiting for pll lock */
	while (!(readl(&pll->con1) & (1 << PLL_LOCK_STATUS_SHIFT)))
		udelay(1);

	rk_clrsetreg(mode, pll_mode_mask[pll_id],
		     PLLMUX_FROM_PLL << pll_mode_shift[pll_id]);

	return 0;
}

static uint32_t rkclk_pll_get_rate(struct px30_pll *pll, unsigned int *mode,
				   enum px30_pll_id pll_id)
{
	u32 refdiv, fbdiv, postdiv1, postdiv2;
	u32 con, shift, mask;

	con = readl(mode);
	shift = pll_mode_shift[pll_id];
	mask = pll_mode_mask[pll_id];

	switch ((con & mask) >> shift) {
	case PLLMUX_FROM_XIN24M:
		return OSC_HZ;
	case PLLMUX_FROM_PLL:
		/* normal mode */
		con = readl(&pll->con0);
		postdiv1 = (con & PLL_POSTDIV1_MASK) >> PLL_POSTDIV1_SHIFT;
		fbdiv = (con & PLL_FBDIV_MASK) >> PLL_FBDIV_SHIFT;
		con = readl(&pll->con1);
		postdiv2 = (con & PLL_POSTDIV2_MASK) >> PLL_POSTDIV2_SHIFT;
		refdiv = (con & PLL_REFDIV_MASK) >> PLL_REFDIV_SHIFT;
		return (24 * fbdiv / (refdiv * postdiv1 * postdiv2)) * 1000000;
	case PLLMUX_FROM_RTC32K:
	default:
		return 32768;
	}
}

static ulong px30_i2c_get_clk(struct px30_clk_priv *priv, ulong clk_id)
{
	struct px30_cru *cru = priv->cru;
	u32 div, con;

	switch (clk_id) {
	case SCLK_I2C0:
		con = readl(&cru->clksel_con[49]);
		div = con >> CLK_I2C0_DIV_CON_SHIFT & CLK_I2C_DIV_CON_MASK;
		break;
	case SCLK_I2C1:
		con = readl(&cru->clksel_con[49]);
		div = con >> CLK_I2C1_DIV_CON_SHIFT & CLK_I2C_DIV_CON_MASK;
		break;
	case SCLK_I2C2:
		con = readl(&cru->clksel_con[50]);
		div = con >> CLK_I2C2_DIV_CON_SHIFT & CLK_I2C_DIV_CON_MASK;
		break;
	case SCLK_I2C3:
		con = readl(&cru->clksel_con[50]);
		div = con >> CLK_I2C3_DIV_CON_SHIFT & CLK_I2C_DIV_CON_MASK;
		break;
	default:
		printf("do not support this i2c bus\n");
		return -EINVAL;
	}

	return DIV_TO_RATE(priv->gpll_hz, div);
}

static ulong px30_i2c_set_clk(struct px30_clk_priv *priv, ulong clk_id, uint hz)
{
	struct px30_cru *cru = priv->cru;
	int src_clk_div;

	src_clk_div = DIV_ROUND_UP(priv->gpll_hz, hz);
	assert(src_clk_div - 1 <= 127);

	switch (clk_id) {
	case SCLK_I2C0:
		rk_clrsetreg(&cru->clksel_con[49],
			     CLK_I2C_DIV_CON_MASK << CLK_I2C0_DIV_CON_SHIFT |
			     CLK_I2C_PLL_SEL_MASK << CLK_I2C0_PLL_SEL_SHIFT,
			     (src_clk_div - 1) << CLK_I2C0_DIV_CON_SHIFT |
			     CLK_I2C_PLL_SEL_GPLL << CLK_I2C0_PLL_SEL_SHIFT);
		break;
	case SCLK_I2C1:
		rk_clrsetreg(&cru->clksel_con[49],
			     CLK_I2C_DIV_CON_MASK << CLK_I2C1_DIV_CON_SHIFT |
			     CLK_I2C_PLL_SEL_MASK << CLK_I2C1_PLL_SEL_SHIFT,
			     (src_clk_div - 1) << CLK_I2C1_DIV_CON_SHIFT |
			     CLK_I2C_PLL_SEL_GPLL << CLK_I2C1_PLL_SEL_SHIFT);
		break;
	case SCLK_I2C2:
		rk_clrsetreg(&cru->clksel_con[50],
			     CLK_I2C_DIV_CON_MASK << CLK_I2C2_DIV_CON_SHIFT |
			     CLK_I2C_PLL_SEL_MASK << CLK_I2C2_PLL_SEL_SHIFT,
			     (src_clk_div - 1) << CLK_I2C2_DIV_CON_SHIFT |
			     CLK_I2C_PLL_SEL_GPLL << CLK_I2C2_PLL_SEL_SHIFT);
		break;
	case SCLK_I2C3:
		rk_clrsetreg(&cru->clksel_con[50],
			     CLK_I2C_DIV_CON_MASK << CLK_I2C3_DIV_CON_SHIFT |
			     CLK_I2C_PLL_SEL_MASK << CLK_I2C3_PLL_SEL_SHIFT,
			     (src_clk_div - 1) << CLK_I2C3_DIV_CON_SHIFT |
			     CLK_I2C_PLL_SEL_GPLL << CLK_I2C3_PLL_SEL_SHIFT);
		break;
	default:
		printf("do not support this i2c bus\n");
		return -EINVAL;
	}

	return px30_i2c_get_clk(priv, clk_id);
}

/*
 * calculate best rational approximation for a given fraction
 * taking into account restricted register size, e.g. to find
 * appropriate values for a pll with 5 bit denominator and
 * 8 bit numerator register fields, trying to set up with a
 * frequency ratio of 3.1415, one would say:
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
static void rational_best_approximation(
	unsigned long given_numerator, unsigned long given_denominator,
	unsigned long max_numerator, unsigned long max_denominator,
	unsigned long *best_numerator, unsigned long *best_denominator)
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

static ulong px30_i2s_get_clk(struct px30_clk_priv *priv, ulong clk_id)
{
	u32 con, fracdiv, gate;
	u32 clk_src = GPLL_HZ / 2;
	unsigned long m, n;
	struct px30_cru *cru = priv->cru;

	switch (clk_id) {
	case SCLK_I2S1:
		con = readl(&cru->clksel_con[30]);
		fracdiv = readl(&cru->clksel_con[31]);
		gate = readl(&cru->clkgate_con[10]);
		n = fracdiv & CLK_I2S1_FRAC_NUMERATOR_MASK;
		n >>= CLK_I2S1_FRAC_NUMERATOR_SHIFT;
		m = fracdiv & CLK_I2S1_FRAC_DENOMINATOR_MASK;
		m >>= CLK_I2S1_FRAC_DENOMINATOR_SHIFT;
		debug("con30: 0x%x, gate: 0x%x, frac: 0x%x\n",
		      con, gate, fracdiv);
		break;
	default:
		printf("do not support this i2s bus\n");
		return -EINVAL;
	}

	return clk_src * n / m;
}

static ulong px30_i2s_set_clk(struct px30_clk_priv *priv, ulong clk_id, uint hz)
{
	u32 clk_src;
	unsigned long m, n, val;
	struct px30_cru *cru = priv->cru;

	clk_src = GPLL_HZ / 2;
	rational_best_approximation(hz, clk_src,
				    GENMASK(16 - 1, 0),
				    GENMASK(16 - 1, 0),
				    &m, &n);
	switch (clk_id) {
	case SCLK_I2S1:
		rk_clrsetreg(&cru->clksel_con[30],
			     CLK_I2S1_PLL_SEL_MASK, CLK_I2S1_PLL_SEL_GPLL);
		rk_clrsetreg(&cru->clksel_con[30],
			     CLK_I2S1_DIV_CON_MASK, 0x1);
		rk_clrsetreg(&cru->clksel_con[30],
			     CLK_I2S1_SEL_MASK, CLK_I2S1_SEL_FRAC);
		val = m << CLK_I2S1_FRAC_NUMERATOR_SHIFT | n;
		writel(val, &cru->clksel_con[31]);
		rk_clrsetreg(&cru->clkgate_con[10],
			     CLK_I2S1_OUT_MCLK_PAD_MASK,
			     CLK_I2S1_OUT_MCLK_PAD_ENABLE);
		break;
	default:
		printf("do not support this i2s bus\n");
		return -EINVAL;
	}

	return px30_i2s_get_clk(priv, clk_id);
}

static ulong px30_i2s1_mclk_get_clk(struct px30_clk_priv *priv, ulong clk_id)
{
	struct px30_cru *cru = priv->cru;
	u32 con;

	con = readl(&cru->clksel_con[30]);

	if (con & CLK_I2S1_OUT_SEL_MASK)
		return 12000000;

	return px30_i2s_get_clk(priv, SCLK_I2S1);
}

static ulong px30_i2s1_mclk_set_clk(struct px30_clk_priv *priv, ulong clk_id,
				    ulong hz)
{
	struct px30_cru *cru = priv->cru;

	if (hz == 12000000) {
		rk_clrsetreg(&cru->clksel_con[30], CLK_I2S1_OUT_SEL_MASK,
			     CLK_I2S1_OUT_SEL_OSC);
	} else {
		px30_i2s_set_clk(priv, SCLK_I2S1, hz);
		rk_clrsetreg(&cru->clksel_con[30], CLK_I2S1_OUT_SEL_MASK,
			     CLK_I2S1_OUT_SEL_I2S1);
	}

	rk_clrsetreg(&cru->clkgate_con[10], CLK_I2S1_OUT_MCLK_PAD_MASK,
		     CLK_I2S1_OUT_MCLK_PAD_ENABLE);

	return px30_i2s1_mclk_get_clk(priv, clk_id);
}

static ulong px30_nandc_get_clk(struct px30_clk_priv *priv)
{
	struct px30_cru *cru = priv->cru;
	u32 div, con;

	con = readl(&cru->clksel_con[15]);
	div = (con & NANDC_DIV_MASK) >> NANDC_DIV_SHIFT;

	return DIV_TO_RATE(priv->gpll_hz, div);
}

static ulong px30_nandc_set_clk(struct px30_clk_priv *priv,
				ulong set_rate)
{
	struct px30_cru *cru = priv->cru;
	int src_clk_div;

	/* Select nandc source from GPLL by default */
	/* nandc clock defaulg div 2 internal, need provide double in cru */
	src_clk_div = DIV_ROUND_UP(priv->gpll_hz, set_rate);
	assert(src_clk_div - 1 <= 31);

	rk_clrsetreg(&cru->clksel_con[15],
		     NANDC_CLK_SEL_MASK | NANDC_PLL_MASK |
		     NANDC_DIV_MASK,
		     NANDC_CLK_SEL_NANDC << NANDC_CLK_SEL_SHIFT |
		     NANDC_SEL_GPLL << NANDC_PLL_SHIFT |
		     (src_clk_div - 1) << NANDC_DIV_SHIFT);

	return px30_nandc_get_clk(priv);
}

static ulong px30_mmc_get_clk(struct px30_clk_priv *priv, uint clk_id)
{
	struct px30_cru *cru = priv->cru;
	u32 div, con, con_id;

	switch (clk_id) {
	case HCLK_SDMMC:
	case SCLK_SDMMC:
		con_id = 16;
		break;
	case HCLK_EMMC:
	case SCLK_EMMC:
	case SCLK_EMMC_SAMPLE:
		con_id = 20;
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

static ulong px30_mmc_set_clk(struct px30_clk_priv *priv,
			      ulong clk_id, ulong set_rate)
{
	struct px30_cru *cru = priv->cru;
	int src_clk_div;
	u32 con_id;

	switch (clk_id) {
	case HCLK_SDMMC:
	case SCLK_SDMMC:
		con_id = 16;
		break;
	case HCLK_EMMC:
	case SCLK_EMMC:
		con_id = 20;
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
	rk_clrsetreg(&cru->clksel_con[con_id +1], EMMC_CLK_SEL_MASK,
		     EMMC_CLK_SEL_EMMC);

	return px30_mmc_get_clk(priv, clk_id);
}

static ulong px30_sfc_get_clk(struct px30_clk_priv *priv, uint clk_id)
{
	struct px30_cru *cru = priv->cru;
	u32 div, con;

	con = readl(&cru->clksel_con[22]);
	div = (con & SFC_DIV_CON_MASK) >> SFC_DIV_CON_SHIFT;

	return DIV_TO_RATE(priv->gpll_hz, div);
}

static ulong px30_sfc_set_clk(struct px30_clk_priv *priv,
			      ulong clk_id, ulong set_rate)
{
	struct px30_cru *cru = priv->cru;
	int src_clk_div;

	src_clk_div = DIV_ROUND_UP(priv->gpll_hz, set_rate);
	rk_clrsetreg(&cru->clksel_con[22],
		     SFC_PLL_SEL_MASK | SFC_DIV_CON_MASK,
		     0 << SFC_PLL_SEL_SHIFT |
		     (src_clk_div - 1) << SFC_DIV_CON_SHIFT);

	return px30_sfc_get_clk(priv, clk_id);
}

static ulong px30_pwm_get_clk(struct px30_clk_priv *priv, ulong clk_id)
{
	struct px30_cru *cru = priv->cru;
	u32 div, con;

	switch (clk_id) {
	case SCLK_PWM0:
		con = readl(&cru->clksel_con[52]);
		div = con >> CLK_PWM0_DIV_CON_SHIFT & CLK_PWM_DIV_CON_MASK;
		break;
	case SCLK_PWM1:
		con = readl(&cru->clksel_con[52]);
		div = con >> CLK_PWM1_DIV_CON_SHIFT & CLK_PWM_DIV_CON_MASK;
		break;
	default:
		printf("do not support this pwm bus\n");
		return -EINVAL;
	}

	return DIV_TO_RATE(priv->gpll_hz, div);
}

static ulong px30_pwm_set_clk(struct px30_clk_priv *priv, ulong clk_id, uint hz)
{
	struct px30_cru *cru = priv->cru;
	int src_clk_div;

	src_clk_div = DIV_ROUND_UP(priv->gpll_hz, hz);
	assert(src_clk_div - 1 <= 127);

	switch (clk_id) {
	case SCLK_PWM0:
		rk_clrsetreg(&cru->clksel_con[52],
			     CLK_PWM_DIV_CON_MASK << CLK_PWM0_DIV_CON_SHIFT |
			     CLK_PWM_PLL_SEL_MASK << CLK_PWM0_PLL_SEL_SHIFT,
			     (src_clk_div - 1) << CLK_PWM0_DIV_CON_SHIFT |
			     CLK_PWM_PLL_SEL_GPLL << CLK_PWM0_PLL_SEL_SHIFT);
		break;
	case SCLK_PWM1:
		rk_clrsetreg(&cru->clksel_con[52],
			     CLK_PWM_DIV_CON_MASK << CLK_PWM1_DIV_CON_SHIFT |
			     CLK_PWM_PLL_SEL_MASK << CLK_PWM1_PLL_SEL_SHIFT,
			     (src_clk_div - 1) << CLK_PWM1_DIV_CON_SHIFT |
			     CLK_PWM_PLL_SEL_GPLL << CLK_PWM1_PLL_SEL_SHIFT);
		break;
	default:
		printf("do not support this pwm bus\n");
		return -EINVAL;
	}

	return px30_pwm_get_clk(priv, clk_id);
}

static ulong px30_saradc_get_clk(struct px30_clk_priv *priv)
{
	struct px30_cru *cru = priv->cru;
	u32 div, con;

	con = readl(&cru->clksel_con[55]);
	div = con >> CLK_SARADC_DIV_CON_SHIFT & CLK_SARADC_DIV_CON_MASK;

	return DIV_TO_RATE(OSC_HZ, div);
}

static ulong px30_saradc_set_clk(struct px30_clk_priv *priv, uint hz)
{
	struct px30_cru *cru = priv->cru;
	int src_clk_div;

	src_clk_div = DIV_ROUND_UP(OSC_HZ, hz);
	assert(src_clk_div - 1 <= 2047);

	rk_clrsetreg(&cru->clksel_con[55],
		     CLK_SARADC_DIV_CON_MASK,
		     (src_clk_div - 1) << CLK_SARADC_DIV_CON_SHIFT);

	return px30_saradc_get_clk(priv);
}

static ulong px30_tsadc_get_clk(struct px30_clk_priv *priv)
{
	struct px30_cru *cru = priv->cru;
	u32 div, con;

	con = readl(&cru->clksel_con[54]);
	div = con >> CLK_SARADC_DIV_CON_SHIFT & CLK_SARADC_DIV_CON_MASK;

	return DIV_TO_RATE(OSC_HZ, div);
}

static ulong px30_tsadc_set_clk(struct px30_clk_priv *priv, uint hz)
{
	struct px30_cru *cru = priv->cru;
	int src_clk_div;

	src_clk_div = DIV_ROUND_UP(OSC_HZ, hz);
	assert(src_clk_div - 1 <= 2047);

	rk_clrsetreg(&cru->clksel_con[54],
		     CLK_SARADC_DIV_CON_MASK,
		     (src_clk_div - 1) << CLK_SARADC_DIV_CON_SHIFT);

	return px30_tsadc_get_clk(priv);
}

static ulong px30_spi_get_clk(struct px30_clk_priv *priv, ulong clk_id)
{
	struct px30_cru *cru = priv->cru;
	u32 div, con;

	switch (clk_id) {
	case SCLK_SPI0:
		con = readl(&cru->clksel_con[53]);
		div = con >> CLK_SPI0_DIV_CON_SHIFT & CLK_SPI_DIV_CON_MASK;
		break;
	case SCLK_SPI1:
		con = readl(&cru->clksel_con[53]);
		div = con >> CLK_SPI1_DIV_CON_SHIFT & CLK_SPI_DIV_CON_MASK;
		break;
	default:
		printf("do not support this pwm bus\n");
		return -EINVAL;
	}

	return DIV_TO_RATE(priv->gpll_hz, div);
}

static ulong px30_spi_set_clk(struct px30_clk_priv *priv, ulong clk_id, uint hz)
{
	struct px30_cru *cru = priv->cru;
	int src_clk_div;

	src_clk_div = DIV_ROUND_UP(priv->gpll_hz, hz);
	assert(src_clk_div - 1 <= 127);

	switch (clk_id) {
	case SCLK_SPI0:
		rk_clrsetreg(&cru->clksel_con[53],
			     CLK_SPI_DIV_CON_MASK << CLK_SPI0_DIV_CON_SHIFT |
			     CLK_SPI_PLL_SEL_MASK << CLK_SPI0_PLL_SEL_SHIFT,
			     (src_clk_div - 1) << CLK_SPI0_DIV_CON_SHIFT |
			     CLK_SPI_PLL_SEL_GPLL << CLK_SPI0_PLL_SEL_SHIFT);
		break;
	case SCLK_SPI1:
		rk_clrsetreg(&cru->clksel_con[53],
			     CLK_SPI_DIV_CON_MASK << CLK_SPI1_DIV_CON_SHIFT |
			     CLK_SPI_PLL_SEL_MASK << CLK_SPI1_PLL_SEL_SHIFT,
			     (src_clk_div - 1) << CLK_SPI1_DIV_CON_SHIFT |
			     CLK_SPI_PLL_SEL_GPLL << CLK_SPI1_PLL_SEL_SHIFT);
		break;
	default:
		printf("do not support this pwm bus\n");
		return -EINVAL;
	}

	return px30_spi_get_clk(priv, clk_id);
}

static ulong px30_vop_get_clk(struct px30_clk_priv *priv, ulong clk_id)
{
	struct px30_cru *cru = priv->cru;
	u32 div, con, parent;

	switch (clk_id) {
	case ACLK_VOPB:
	case ACLK_VOPL:
		con = readl(&cru->clksel_con[3]);
		div = con & ACLK_VO_DIV_MASK;
		parent = priv->gpll_hz;
		break;
	case DCLK_VOPB:
		con = readl(&cru->clksel_con[5]);
		div = con & DCLK_VOPB_DIV_MASK;
		parent = rkclk_pll_get_rate(&cru->pll[CPLL], &cru->mode, CPLL);
		break;
	case DCLK_VOPL:
		con = readl(&cru->clksel_con[8]);
		div = con & DCLK_VOPL_DIV_MASK;
		parent = rkclk_pll_get_rate(&cru->pll[NPLL], &cru->mode, NPLL);
		break;
	default:
		return -ENOENT;
	}

	return DIV_TO_RATE(parent, div);
}

static ulong px30_vop_set_clk(struct px30_clk_priv *priv, ulong clk_id, uint hz)
{
	struct px30_cru *cru = priv->cru;
	ulong npll_hz;
	int src_clk_div;

	switch (clk_id) {
	case ACLK_VOPB:
	case ACLK_VOPL:
		src_clk_div = DIV_ROUND_UP(priv->gpll_hz, hz);
		assert(src_clk_div - 1 <= 31);
		rk_clrsetreg(&cru->clksel_con[3],
			     ACLK_VO_PLL_MASK | ACLK_VO_DIV_MASK,
			     ACLK_VO_SEL_GPLL << ACLK_VO_PLL_SHIFT |
			     (src_clk_div - 1) << ACLK_VO_DIV_SHIFT);
		break;
	case DCLK_VOPB:
		if (hz < PX30_VOP_PLL_LIMIT) {
			src_clk_div = DIV_ROUND_UP(PX30_VOP_PLL_LIMIT, hz);
			if (src_clk_div % 2)
				src_clk_div = src_clk_div - 1;
		} else {
			src_clk_div = 1;
		}
		assert(src_clk_div - 1 <= 255);
		rkclk_set_pll(&cru->pll[CPLL], &cru->mode, CPLL, hz * src_clk_div);
		rk_clrsetreg(&cru->clksel_con[5],
			     DCLK_VOPB_SEL_MASK | DCLK_VOPB_PLL_SEL_MASK |
			     DCLK_VOPB_DIV_MASK,
			     DCLK_VOPB_SEL_DIVOUT << DCLK_VOPB_SEL_SHIFT |
			     DCLK_VOPB_PLL_SEL_CPLL << DCLK_VOPB_PLL_SEL_SHIFT |
			     (src_clk_div - 1) << DCLK_VOPB_DIV_SHIFT);
		break;
	case DCLK_VOPL:
		npll_hz = px30_clk_get_pll_rate(priv, NPLL);
		if (npll_hz >= PX30_VOP_PLL_LIMIT && npll_hz >= hz && npll_hz % hz == 0) {
			src_clk_div = npll_hz / hz;
			assert(src_clk_div - 1 <= 255);
		} else {
			if (hz < PX30_VOP_PLL_LIMIT) {
				src_clk_div = DIV_ROUND_UP(PX30_VOP_PLL_LIMIT, hz);
				if (src_clk_div % 2)
					src_clk_div = src_clk_div - 1;
			} else {
				src_clk_div = 1;
			}
			assert(src_clk_div - 1 <= 255);
			rkclk_set_pll(&cru->pll[NPLL], &cru->mode, NPLL, hz * src_clk_div);
		}
		rk_clrsetreg(&cru->clksel_con[8],
			     DCLK_VOPL_SEL_MASK | DCLK_VOPL_PLL_SEL_MASK |
			     DCLK_VOPL_DIV_MASK,
			     DCLK_VOPL_SEL_DIVOUT << DCLK_VOPL_SEL_SHIFT |
			     DCLK_VOPL_PLL_SEL_NPLL << DCLK_VOPL_PLL_SEL_SHIFT |
			     (src_clk_div - 1) << DCLK_VOPL_DIV_SHIFT);
		break;
	default:
		printf("do not support this vop freq\n");
		return -EINVAL;
	}

	return px30_vop_get_clk(priv, clk_id);
}

static ulong px30_bus_get_clk(struct px30_clk_priv *priv, ulong clk_id)
{
	struct px30_cru *cru = priv->cru;
	u32 div, con, parent;

	switch (clk_id) {
	case ACLK_BUS_PRE:
		con = readl(&cru->clksel_con[23]);
		div = (con & BUS_ACLK_DIV_MASK) >> BUS_ACLK_DIV_SHIFT;
		parent = priv->gpll_hz;
		break;
	case HCLK_BUS_PRE:
		con = readl(&cru->clksel_con[24]);
		div = (con & BUS_HCLK_DIV_MASK) >> BUS_HCLK_DIV_SHIFT;
		parent = priv->gpll_hz;
		break;
	case PCLK_BUS_PRE:
	case PCLK_WDT_NS:
		parent = px30_bus_get_clk(priv, ACLK_BUS_PRE);
		con = readl(&cru->clksel_con[24]);
		div = (con & BUS_PCLK_DIV_MASK) >> BUS_PCLK_DIV_SHIFT;
		break;
	default:
		return -ENOENT;
	}

	return DIV_TO_RATE(parent, div);
}

static ulong px30_bus_set_clk(struct px30_clk_priv *priv, ulong clk_id,
			      ulong hz)
{
	struct px30_cru *cru = priv->cru;
	int src_clk_div;

	/*
	 * select gpll as pd_bus bus clock source and
	 * set up dependent divisors for PCLK/HCLK and ACLK clocks.
	 */
	switch (clk_id) {
	case ACLK_BUS_PRE:
		src_clk_div = DIV_ROUND_UP(priv->gpll_hz, hz);
		assert(src_clk_div - 1 <= 31);
		rk_clrsetreg(&cru->clksel_con[23],
			     BUS_PLL_SEL_MASK | BUS_ACLK_DIV_MASK,
			     BUS_PLL_SEL_GPLL << BUS_PLL_SEL_SHIFT |
			     (src_clk_div - 1) << BUS_ACLK_DIV_SHIFT);
		break;
	case HCLK_BUS_PRE:
		src_clk_div = DIV_ROUND_UP(priv->gpll_hz, hz);
		assert(src_clk_div - 1 <= 31);
		rk_clrsetreg(&cru->clksel_con[24],
			     BUS_PLL_SEL_MASK | BUS_HCLK_DIV_MASK,
			     BUS_PLL_SEL_GPLL << BUS_PLL_SEL_SHIFT |
			     (src_clk_div - 1) << BUS_HCLK_DIV_SHIFT);
		break;
	case PCLK_BUS_PRE:
		src_clk_div =
			DIV_ROUND_UP(px30_bus_get_clk(priv, ACLK_BUS_PRE), hz);
		assert(src_clk_div - 1 <= 3);
		rk_clrsetreg(&cru->clksel_con[24],
			     BUS_PCLK_DIV_MASK,
			     (src_clk_div - 1) << BUS_PCLK_DIV_SHIFT);
		break;
	default:
		printf("do not support this bus freq\n");
		return -EINVAL;
	}

	return px30_bus_get_clk(priv, clk_id);
}

static ulong px30_peri_get_clk(struct px30_clk_priv *priv, ulong clk_id)
{
	struct px30_cru *cru = priv->cru;
	u32 div, con, parent;

	switch (clk_id) {
	case ACLK_PERI_PRE:
		con = readl(&cru->clksel_con[14]);
		div = (con & PERI_ACLK_DIV_MASK) >> PERI_ACLK_DIV_SHIFT;
		parent = priv->gpll_hz;
		break;
	case HCLK_PERI_PRE:
		con = readl(&cru->clksel_con[14]);
		div = (con & PERI_HCLK_DIV_MASK) >> PERI_HCLK_DIV_SHIFT;
		parent = priv->gpll_hz;
		break;
	default:
		return -ENOENT;
	}

	return DIV_TO_RATE(parent, div);
}

static ulong px30_peri_set_clk(struct px30_clk_priv *priv, ulong clk_id,
			       ulong hz)
{
	struct px30_cru *cru = priv->cru;
	int src_clk_div;

	src_clk_div = DIV_ROUND_UP(priv->gpll_hz, hz);
	assert(src_clk_div - 1 <= 31);

	/*
	 * select gpll as pd_peri bus clock source and
	 * set up dependent divisors for HCLK and ACLK clocks.
	 */
	switch (clk_id) {
	case ACLK_PERI_PRE:
		rk_clrsetreg(&cru->clksel_con[14],
			     PERI_PLL_SEL_MASK | PERI_ACLK_DIV_MASK,
			     PERI_PLL_GPLL << PERI_PLL_SEL_SHIFT |
			     (src_clk_div - 1) << PERI_ACLK_DIV_SHIFT);
		break;
	case HCLK_PERI_PRE:
		rk_clrsetreg(&cru->clksel_con[14],
			     PERI_PLL_SEL_MASK | PERI_HCLK_DIV_MASK,
			     PERI_PLL_GPLL << PERI_PLL_SEL_SHIFT |
			     (src_clk_div - 1) << PERI_HCLK_DIV_SHIFT);
		break;
	default:
		printf("do not support this peri freq\n");
		return -EINVAL;
	}

	return px30_peri_get_clk(priv, clk_id);
}

static ulong px30_otp_get_clk(struct px30_clk_priv *priv, ulong clk_id)
{
	struct px30_cru *cru = priv->cru;
	u32 src, div, con, parent;

	if (soc_is_px30s()) {
		con = readl(&cru->clksel_con[56]);
		src = (con & CLK_OTP_S_SEL_MASK) >> CLK_OTP_S_SEL_SHIFT;
		div = (con & CLK_OTP_S_DIV_CON_MASK) >> CLK_OTP_S_DIV_CON_SHIFT;
		if (src)
			return DIV_TO_RATE(priv->gpll_hz, div);
		else
			return DIV_TO_RATE(OSC_HZ, div);
	}

	switch (clk_id) {
	case SCLK_OTP:
		con = readl(&cru->clksel_con[56]);
		div = (con & CLK_OTP_DIV_CON_MASK) >> CLK_OTP_DIV_CON_SHIFT;
		parent = OSC_HZ;
		break;
	case SCLK_OTP_USR:
		con = readl(&cru->clksel_con[56]);
		div = (con & CLK_OTP_USR_DIV_CON_MASK) >>
		      CLK_OTP_USR_DIV_CON_SHIFT;
		parent = px30_otp_get_clk(priv, SCLK_OTP);
		break;
	default:
		return -ENOENT;
	}

	return DIV_TO_RATE(parent, div);
}

static ulong px30_otp_set_clk(struct px30_clk_priv *priv, ulong clk_id,
			      ulong hz)
{
	struct px30_cru *cru = priv->cru;
	u32 src, div, parent;

	if (soc_is_px30s()) {
		if ((OSC_HZ % hz) == 0) {
			src = 0;
			parent = OSC_HZ;
		} else {
			src = 1;
			parent = priv->gpll_hz;
		}
		div = DIV_ROUND_UP(parent, hz);
		rk_clrsetreg(&cru->clksel_con[56],
			     CLK_OTP_S_SEL_MASK | CLK_OTP_S_DIV_CON_MASK,
			     src << CLK_OTP_S_SEL_SHIFT |
			     (div - 1) << CLK_OTP_S_DIV_CON_SHIFT);
		return px30_otp_get_clk(priv, clk_id);
	}

	switch (clk_id) {
	case SCLK_OTP:
		div = DIV_ROUND_UP(OSC_HZ, hz);
		rk_clrsetreg(&cru->clksel_con[56],
			     CLK_OTP_DIV_CON_MASK,
			     (div - 1) << CLK_OTP_DIV_CON_SHIFT);
		break;
	case SCLK_OTP_USR:
		div = DIV_ROUND_UP(px30_otp_get_clk(priv, SCLK_OTP), hz);
		rk_clrsetreg(&cru->clksel_con[56],
			     CLK_OTP_USR_DIV_CON_MASK,
			     (div - 1) << CLK_OTP_USR_DIV_CON_SHIFT);
		break;
	default:
		printf("do not support this peri freq\n");
		return -EINVAL;
	}

	return px30_otp_get_clk(priv, clk_id);
}

static ulong px30_crypto_get_clk(struct px30_clk_priv *priv, ulong clk_id)
{
	struct px30_cru *cru = priv->cru;
	u32 div, con, parent;

	switch (clk_id) {
	case SCLK_CRYPTO:
		con = readl(&cru->clksel_con[25]);
		div = (con & CRYPTO_DIV_MASK) >> CRYPTO_DIV_SHIFT;
		parent = priv->gpll_hz;
		break;
	case SCLK_CRYPTO_APK:
		con = readl(&cru->clksel_con[25]);
		div = (con & CRYPTO_APK_DIV_MASK) >> CRYPTO_APK_DIV_SHIFT;
		parent = priv->gpll_hz;
		break;
	default:
		return -ENOENT;
	}

	return DIV_TO_RATE(parent, div);
}

static ulong px30_crypto_set_clk(struct px30_clk_priv *priv, ulong clk_id,
				 ulong hz)
{
	struct px30_cru *cru = priv->cru;
	int src_clk_div;

	src_clk_div = DIV_ROUND_UP(priv->gpll_hz, hz);
	assert(src_clk_div - 1 <= 31);

	/*
	 * select gpll as crypto clock source and
	 * set up dependent divisors for crypto clocks.
	 */
	switch (clk_id) {
	case SCLK_CRYPTO:
		rk_clrsetreg(&cru->clksel_con[25],
			     CRYPTO_PLL_SEL_MASK | CRYPTO_DIV_MASK,
			     CRYPTO_PLL_SEL_GPLL << CRYPTO_PLL_SEL_SHIFT |
			     (src_clk_div - 1) << CRYPTO_DIV_SHIFT);
		break;
	case SCLK_CRYPTO_APK:
		rk_clrsetreg(&cru->clksel_con[25],
			     CRYPTO_APK_PLL_SEL_MASK | CRYPTO_APK_DIV_MASK,
			     CRYPTO_PLL_SEL_GPLL << CRYPTO_APK_SEL_SHIFT |
			     (src_clk_div - 1) << CRYPTO_APK_DIV_SHIFT);
		break;
	default:
		printf("do not support this peri freq\n");
		return -EINVAL;
	}

	return px30_crypto_get_clk(priv, clk_id);
}

#ifndef CONFIG_SPL_BUILD
static ulong px30_mac_set_clk(struct clk *clk, uint hz)
{
	struct px30_clk_priv *priv = dev_get_priv(clk->dev);
	struct px30_cru *cru = priv->cru;
	u32 con = readl(&cru->clksel_con[22]);
	ulong pll_rate;
	u8 div;

	if ((con >> GMAC_PLL_SEL_SHIFT) & GMAC_PLL_SEL_CPLL)
		pll_rate = px30_clk_get_pll_rate(priv, CPLL);
	else if ((con >> GMAC_PLL_SEL_SHIFT) & GMAC_PLL_SEL_NPLL)
		pll_rate = px30_clk_get_pll_rate(priv, NPLL);
	else
		pll_rate = priv->gpll_hz;

	/*default set 50MHZ for gmac*/
	if (!hz)
		hz = 50000000;

	div = DIV_ROUND_UP(pll_rate, hz) - 1;
	assert(div < 32);
	rk_clrsetreg(&cru->clksel_con[22], CLK_GMAC_DIV_MASK,
		     div << CLK_GMAC_DIV_SHIFT);

	return DIV_TO_RATE(pll_rate, div);
}

static int px30_mac_set_speed_clk(struct clk *clk, uint hz)
{
	struct px30_clk_priv *priv = dev_get_priv(clk->dev);
	struct px30_cru *cru = priv->cru;

	if (hz != 2500000 && hz != 25000000) {
		debug("Unsupported mac speed:%d\n", hz);
		return -EINVAL;
	}

	rk_clrsetreg(&cru->clksel_con[23], RMII_CLK_SEL_MASK,
		     ((hz == 2500000) ? 0 : 1) << RMII_CLK_SEL_SHIFT);

	return 0;
}

#endif

static int px30_clk_get_gpll_rate(ulong *rate)
{
	struct udevice *pmucru_dev;
	struct px30_pmuclk_priv *priv;
	int ret;

	ret = uclass_get_device_by_driver(UCLASS_CLK,
					  DM_GET_DRIVER(rockchip_px30_pmucru),
					  &pmucru_dev);
	if (ret) {
		printf("%s: could not find pmucru device\n", __func__);
		return ret;
	}
	priv = dev_get_priv(pmucru_dev);
	*rate =  priv->gpll_hz;

	return 0;
}

static ulong px30_clk_get_pll_rate(struct px30_clk_priv *priv,
				   enum px30_pll_id pll_id)
{
	struct px30_cru *cru = priv->cru;

	return rkclk_pll_get_rate(&cru->pll[pll_id], &cru->mode, pll_id);
}

static ulong px30_clk_set_pll_rate(struct px30_clk_priv *priv,
				   enum px30_pll_id pll_id, ulong hz)
{
	struct px30_cru *cru = priv->cru;

	if (rkclk_set_pll(&cru->pll[pll_id], &cru->mode, pll_id, hz))
		return -EINVAL;
	return rkclk_pll_get_rate(&cru->pll[pll_id], &cru->mode, pll_id);
}

static ulong px30_armclk_set_clk(struct px30_clk_priv *priv, ulong hz)
{
	struct px30_cru *cru = priv->cru;
	const struct cpu_rate_table *rate;
	ulong old_rate;

	rate = get_cpu_settings(hz);
	if (!rate) {
		printf("%s unsupport rate\n", __func__);
		return -EINVAL;
	}

	/*
	 * select apll as cpu/core clock pll source and
	 * set up dependent divisors for PERI and ACLK clocks.
	 * core hz : apll = 1:1
	 */
	old_rate = px30_clk_get_pll_rate(priv, APLL);
	if (old_rate > hz) {
		if (rkclk_set_pll(&cru->pll[APLL], &cru->mode, APLL, hz))
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
		if (rkclk_set_pll(&cru->pll[APLL], &cru->mode, APLL, hz))
			return -EINVAL;
	}

	return px30_clk_get_pll_rate(priv, APLL);
}

static ulong px30_clk_get_rate(struct clk *clk)
{
	struct px30_clk_priv *priv = dev_get_priv(clk->dev);
	ulong rate = 0;

	if (!priv->gpll_hz && clk->id > ARMCLK) {
		printf("%s gpll=%lu\n", __func__, priv->gpll_hz);
		return -ENOENT;
	}

	debug("%s %ld\n", __func__, clk->id);
	switch (clk->id) {
	case PLL_APLL:
		rate = px30_clk_get_pll_rate(priv, APLL);
		break;
	case PLL_DPLL:
		rate = px30_clk_get_pll_rate(priv, DPLL);
		break;
	case PLL_CPLL:
		rate = px30_clk_get_pll_rate(priv, CPLL);
		break;
	case PLL_NPLL:
		rate = px30_clk_get_pll_rate(priv, NPLL);
		break;
	case ARMCLK:
		rate = px30_clk_get_pll_rate(priv, APLL);
		break;
	case HCLK_SDMMC:
	case HCLK_EMMC:
	case SCLK_SDMMC:
	case SCLK_EMMC:
	case SCLK_EMMC_SAMPLE:
		rate = px30_mmc_get_clk(priv, clk->id);
		break;
	case SCLK_SFC:
		rate = px30_sfc_get_clk(priv, clk->id);
		break;
	case SCLK_I2C0:
	case SCLK_I2C1:
	case SCLK_I2C2:
	case SCLK_I2C3:
		rate = px30_i2c_get_clk(priv, clk->id);
		break;
	case SCLK_I2S1:
		rate = px30_i2s_get_clk(priv, clk->id);
		break;
	case SCLK_I2S1_OUT:
		rate = px30_i2s1_mclk_get_clk(priv, clk->id);
		break;
	case SCLK_PWM0:
	case SCLK_PWM1:
		rate = px30_pwm_get_clk(priv, clk->id);
		break;
	case SCLK_SARADC:
		rate = px30_saradc_get_clk(priv);
		break;
	case SCLK_TSADC:
		rate = px30_tsadc_get_clk(priv);
		break;
	case SCLK_SPI0:
	case SCLK_SPI1:
		rate = px30_spi_get_clk(priv, clk->id);
		break;
	case ACLK_VOPB:
	case ACLK_VOPL:
	case DCLK_VOPB:
	case DCLK_VOPL:
		rate = px30_vop_get_clk(priv, clk->id);
		break;
	case ACLK_BUS_PRE:
	case HCLK_BUS_PRE:
	case PCLK_BUS_PRE:
	case PCLK_WDT_NS:
		rate = px30_bus_get_clk(priv, clk->id);
		break;
	case ACLK_PERI_PRE:
	case HCLK_PERI_PRE:
		rate = px30_peri_get_clk(priv, clk->id);
		break;
	case SCLK_OTP:
	case SCLK_OTP_USR:
		rate = px30_otp_get_clk(priv, clk->id);
		break;
	case SCLK_CRYPTO:
	case SCLK_CRYPTO_APK:
		rate = px30_crypto_get_clk(priv, clk->id);
		break;
	default:
		return -ENOENT;
	}

	return rate;
}

static ulong px30_clk_set_rate(struct clk *clk, ulong rate)
{
	struct px30_clk_priv *priv = dev_get_priv(clk->dev);
	ulong ret = 0;

	if (!priv->gpll_hz && clk->id > ARMCLK) {
		printf("%s gpll=%lu\n", __func__, priv->gpll_hz);
		return -ENOENT;
	}

	debug("%s %ld %ld\n", __func__, clk->id, rate);
	switch (clk->id) {
	case PLL_NPLL:
		ret = px30_clk_set_pll_rate(priv, NPLL, rate);
		break;
	case ARMCLK:
		if (priv->armclk_hz)
			px30_armclk_set_clk(priv, rate);
		priv->armclk_hz = rate;
		break;
	case HCLK_SDMMC:
	case HCLK_EMMC:
	case SCLK_SDMMC:
	case SCLK_EMMC:
		ret = px30_mmc_set_clk(priv, clk->id, rate);
		break;
	case SCLK_SFC:
		ret = px30_sfc_set_clk(priv, clk->id, rate);
		break;
	case SCLK_I2C0:
	case SCLK_I2C1:
	case SCLK_I2C2:
	case SCLK_I2C3:
		ret = px30_i2c_set_clk(priv, clk->id, rate);
		break;
	case SCLK_I2S1:
		ret = px30_i2s_set_clk(priv, clk->id, rate);
		break;
	case SCLK_I2S1_OUT:
		ret = px30_i2s1_mclk_set_clk(priv, clk->id, rate);
		break;
	case SCLK_PWM0:
	case SCLK_PWM1:
		ret = px30_pwm_set_clk(priv, clk->id, rate);
		break;
	case SCLK_SARADC:
		ret = px30_saradc_set_clk(priv, rate);
		break;
	case SCLK_TSADC:
		ret = px30_tsadc_set_clk(priv, rate);
		break;
	case SCLK_SPI0:
	case SCLK_SPI1:
		ret = px30_spi_set_clk(priv, clk->id, rate);
		break;
	case ACLK_VOPB:
	case ACLK_VOPL:
	case DCLK_VOPB:
	case DCLK_VOPL:
		ret = px30_vop_set_clk(priv, clk->id, rate);
		break;
	case ACLK_BUS_PRE:
	case HCLK_BUS_PRE:
	case PCLK_BUS_PRE:
		ret = px30_bus_set_clk(priv, clk->id, rate);
		break;
	case ACLK_PERI_PRE:
	case HCLK_PERI_PRE:
		ret = px30_peri_set_clk(priv, clk->id, rate);
		break;
	case SCLK_OTP:
	case SCLK_OTP_USR:
		ret = px30_otp_set_clk(priv, clk->id, rate);
		break;
	case SCLK_CRYPTO:
	case SCLK_CRYPTO_APK:
		ret = px30_crypto_set_clk(priv, clk->id, rate);
		break;
#ifndef CONFIG_SPL_BUILD
	case SCLK_GMAC:
	case SCLK_GMAC_SRC:
		ret = px30_mac_set_clk(clk, rate);
		break;
	case SCLK_GMAC_RMII:
		ret = px30_mac_set_speed_clk(clk, rate);
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

int rockchip_mmc_get_phase(struct clk *clk)
{
	struct px30_clk_priv *priv = dev_get_priv(clk->dev);
	struct px30_cru *cru = priv->cru;
	u32 raw_value, delay_num;
	u16 degrees = 0;
	ulong rate;

	rate = px30_clk_get_rate(clk);

	if (rate < 0)
		return rate;

	if (clk->id == SCLK_EMMC_SAMPLE)
		raw_value = readl(&cru->emmc_con[1]);
	else
		raw_value = readl(&cru->sdmmc_con[1]);

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

int rockchip_mmc_set_phase(struct clk *clk, u32 degrees)
{
	struct px30_clk_priv *priv = dev_get_priv(clk->dev);
	struct px30_cru *cru = priv->cru;
	u8 nineties, remainder, delay_num;
	u32 raw_value, delay;
	ulong rate;

	rate = px30_clk_get_rate(clk);

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
	else
		writel(raw_value | 0xffff0000, &cru->sdmmc_con[1]);

	debug("mmc set_phase(%d) delay_nums=%u reg=%#x actual_degrees=%d\n",
	      degrees, delay_num, raw_value, rockchip_mmc_get_phase(clk));

	return 0;
}

static int px30_clk_get_phase(struct clk *clk)
{
	int ret;

	debug("%s %ld\n", __func__, clk->id);
	switch (clk->id) {
	case SCLK_EMMC_SAMPLE:
	case SCLK_SDMMC_SAMPLE:
		ret = rockchip_mmc_get_phase(clk);
		break;
	default:
		return -ENOENT;
	}

	return ret;
}

static int px30_clk_set_phase(struct clk *clk, int degrees)
{
	int ret;

	debug("%s %ld\n", __func__, clk->id);
	switch (clk->id) {
	case SCLK_EMMC_SAMPLE:
	case SCLK_SDMMC_SAMPLE:
		ret = rockchip_mmc_set_phase(clk, degrees);
		break;
	default:
		return -ENOENT;
	}

	return ret;
}

#if CONFIG_IS_ENABLED(OF_CONTROL) && !CONFIG_IS_ENABLED(OF_PLATDATA)
static int px30_gmac_set_parent(struct clk *clk, struct clk *parent)
{
	struct px30_clk_priv *priv = dev_get_priv(clk->dev);
	struct px30_cru *cru = priv->cru;

	if (parent->id == SCLK_GMAC_SRC) {
		debug("%s: switching GAMC to SCLK_GMAC_SRC\n", __func__);
		rk_clrsetreg(&cru->clksel_con[23], RMII_EXTCLK_SEL_MASK,
			     RMII_EXTCLK_SEL_INT << RMII_EXTCLK_SEL_SHIFT);
	} else {
		debug("%s: switching GMAC to external clock\n", __func__);
		rk_clrsetreg(&cru->clksel_con[23], RMII_EXTCLK_SEL_MASK,
			     RMII_EXTCLK_SEL_EXT << RMII_EXTCLK_SEL_SHIFT);
	}
	return 0;
}

static int px30_clk_set_parent(struct clk *clk, struct clk *parent)
{
	switch (clk->id) {
	case SCLK_GMAC:
		return px30_gmac_set_parent(clk, parent);
	default:
		return -ENOENT;
	}
}
#endif

static struct clk_ops px30_clk_ops = {
	.get_rate = px30_clk_get_rate,
	.set_rate = px30_clk_set_rate,
	.get_phase	= px30_clk_get_phase,
	.set_phase	= px30_clk_set_phase,
#if CONFIG_IS_ENABLED(OF_CONTROL) && !CONFIG_IS_ENABLED(OF_PLATDATA)
	.set_parent	= px30_clk_set_parent,
#endif
};

static int px30_clk_probe(struct udevice *dev)
{
	struct px30_clk_priv *priv = dev_get_priv(dev);
	int ret;

	priv->sync_kernel = false;
	if (!priv->armclk_enter_hz) {
		priv->armclk_enter_hz = px30_clk_get_pll_rate(priv, APLL);
		priv->armclk_init_hz = priv->armclk_enter_hz;
	}
	if (px30_clk_get_pll_rate(priv, APLL) != APLL_HZ) {
		ret = px30_armclk_set_clk(priv, APLL_HZ);
		if (ret < 0)
			printf("%s failed to set armclk rate\n", __func__);
		priv->armclk_init_hz = APLL_HZ;
	}

	/* Process 'assigned-{clocks/clock-parents/clock-rates}' properties */
	ret = clk_set_defaults(dev);
	if (ret)
		debug("%s clk_set_defaults failed %d\n", __func__, ret);
	else
		priv->sync_kernel = true;

	if (!priv->gpll_hz) {
		ret = px30_clk_get_gpll_rate(&priv->gpll_hz);
		if (ret) {
			printf("%s failed to get gpll rate\n", __func__);
			return ret;
		}
	}

	return 0;
}

static int px30_clk_ofdata_to_platdata(struct udevice *dev)
{
	struct px30_clk_priv *priv = dev_get_priv(dev);

	priv->cru = dev_read_addr_ptr(dev);

	return 0;
}

static int px30_clk_bind(struct udevice *dev)
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
		priv->glb_srst_fst_value = offsetof(struct px30_cru,
						    glb_srst_fst);
		priv->glb_srst_snd_value = offsetof(struct px30_cru,
						    glb_srst_snd);
		sys_child->priv = priv;
	}

	ret = device_bind_driver_to_node(dev, "rockchip_reset", "reset",
					 dev_ofnode(dev), &sf_child);
	if (ret) {
		debug("Warning: No rockchip reset driver: ret=%d\n", ret);
	} else {
		sf_priv = malloc(sizeof(struct softreset_reg));
		sf_priv->sf_reset_offset = offsetof(struct px30_cru,
						    softrst_con[0]);
		sf_priv->sf_reset_num = 12;
		sf_child->priv = sf_priv;
	}

	return 0;
}

static const struct udevice_id px30_clk_ids[] = {
	{ .compatible = "rockchip,px30-cru" },
	{ }
};

U_BOOT_DRIVER(rockchip_px30_cru) = {
	.name		= "rockchip_px30_cru",
	.id		= UCLASS_CLK,
	.of_match	= px30_clk_ids,
	.priv_auto_alloc_size = sizeof(struct px30_clk_priv),
	.ofdata_to_platdata = px30_clk_ofdata_to_platdata,
	.ops		= &px30_clk_ops,
	.bind		= px30_clk_bind,
	.probe		= px30_clk_probe,
};

static ulong px30_pclk_pmu_get_pmuclk(struct px30_pmuclk_priv *priv)
{
	struct px30_pmucru *pmucru = priv->pmucru;
	u32 div, con;

	con = readl(&pmucru->pmu_clksel_con[0]);
	div = (con & CLK_PMU_PCLK_DIV_MASK) >> CLK_PMU_PCLK_DIV_SHIFT;

	return DIV_TO_RATE(priv->gpll_hz, div);
}

static ulong px30_pclk_pmu_set_pmuclk(struct px30_pmuclk_priv *priv, ulong hz)
{
	struct px30_pmucru *pmucru = priv->pmucru;
	int src_clk_div;

	src_clk_div = DIV_ROUND_UP(priv->gpll_hz, hz);
	assert(src_clk_div - 1 <= 31);

	rk_clrsetreg(&pmucru->pmu_clksel_con[0],
		     CLK_PMU_PCLK_DIV_MASK,
		     (src_clk_div - 1) << CLK_PMU_PCLK_DIV_SHIFT);

	return px30_pclk_pmu_get_pmuclk(priv);
}

static ulong px30_gpll_get_pmuclk(struct px30_pmuclk_priv *priv)
{
	struct px30_pmucru *pmucru = priv->pmucru;

	return rkclk_pll_get_rate(&pmucru->pll, &pmucru->pmu_mode, GPLL);
}

static ulong px30_gpll_set_pmuclk(struct px30_pmuclk_priv *priv, ulong hz)
{
	struct udevice *cru_dev;
	struct px30_clk_priv *cru_priv;
	struct px30_pmucru *pmucru = priv->pmucru;
	u32 div;
	ulong emmc_rate, sdmmc_rate, nandc_rate, sfc_rate;
	ulong aclk_bus_rate, hclk_bus_rate, pclk_bus_rate;
	ulong aclk_peri_rate, hclk_peri_rate, pclk_pmu_rate;
	int ret;

	ret = uclass_get_device_by_name(UCLASS_CLK,
					"clock-controller@ff2b0000",
					 &cru_dev);
	if (ret) {
		printf("%s failed to get cru device\n", __func__);
		return ret;
	}
	cru_priv = dev_get_priv(cru_dev);

	if (priv->gpll_hz == hz)
		return priv->gpll_hz;

	cru_priv->gpll_hz = priv->gpll_hz;
	div = DIV_ROUND_UP(hz, priv->gpll_hz);

	/* save clock rate */
	aclk_bus_rate = px30_bus_get_clk(cru_priv, ACLK_BUS_PRE);
	hclk_bus_rate = px30_bus_get_clk(cru_priv, HCLK_BUS_PRE);
	pclk_bus_rate = px30_bus_get_clk(cru_priv, PCLK_BUS_PRE);
	aclk_peri_rate = px30_peri_get_clk(cru_priv, ACLK_PERI_PRE);
	hclk_peri_rate = px30_peri_get_clk(cru_priv, HCLK_PERI_PRE);
	pclk_pmu_rate = px30_pclk_pmu_get_pmuclk(priv);
	debug("%s aclk_bus=%lu, hclk_bus=%lu, pclk_bus=%lu\n", __func__,
	      aclk_bus_rate, hclk_bus_rate, pclk_bus_rate);
	debug("%s aclk_peri=%lu, hclk_peri=%lu, pclk_pmu=%lu\n", __func__,
	      aclk_peri_rate, hclk_peri_rate, pclk_pmu_rate);
	emmc_rate = px30_mmc_get_clk(cru_priv, SCLK_EMMC);
	sdmmc_rate = px30_mmc_get_clk(cru_priv, SCLK_SDMMC);
	nandc_rate = px30_nandc_get_clk(cru_priv);
	sfc_rate = px30_sfc_get_clk(cru_priv, SCLK_SFC);
	debug("%s emmc=%lu, sdmmc=%lu, nandc=%lu sfc=%lu\n", __func__,
	      emmc_rate, sdmmc_rate, nandc_rate, sfc_rate);

	/* avoid rate too large, reduce rate first */
	px30_bus_set_clk(cru_priv, ACLK_BUS_PRE, aclk_bus_rate / div);
	px30_bus_set_clk(cru_priv, HCLK_BUS_PRE, hclk_bus_rate / div);
	px30_bus_set_clk(cru_priv, PCLK_BUS_PRE, pclk_bus_rate / div);
	px30_peri_set_clk(cru_priv, ACLK_PERI_PRE, aclk_peri_rate / div);
	px30_peri_set_clk(cru_priv, HCLK_PERI_PRE, hclk_peri_rate / div);
	px30_pclk_pmu_set_pmuclk(priv, pclk_pmu_rate / div);

	px30_mmc_set_clk(cru_priv, SCLK_EMMC, emmc_rate / div);
	px30_mmc_set_clk(cru_priv, SCLK_SDMMC, sdmmc_rate / div);
	px30_nandc_set_clk(cru_priv, nandc_rate / div);
	px30_sfc_set_clk(cru_priv, SCLK_SFC, sfc_rate / div);

	/* change gpll rate */
	rkclk_set_pll(&pmucru->pll, &pmucru->pmu_mode, GPLL, hz);
	priv->gpll_hz = px30_gpll_get_pmuclk(priv);
	cru_priv->gpll_hz = priv->gpll_hz;

	/* restore clock rate */
	px30_bus_set_clk(cru_priv, ACLK_BUS_PRE, aclk_bus_rate);
	px30_bus_set_clk(cru_priv, HCLK_BUS_PRE, hclk_bus_rate);
	px30_bus_set_clk(cru_priv, PCLK_BUS_PRE, pclk_bus_rate);
	px30_peri_set_clk(cru_priv, ACLK_PERI_PRE, aclk_peri_rate);
	px30_peri_set_clk(cru_priv, HCLK_PERI_PRE, hclk_peri_rate);
	px30_pclk_pmu_set_pmuclk(priv, pclk_pmu_rate);

	px30_mmc_set_clk(cru_priv, SCLK_EMMC, emmc_rate);
	px30_mmc_set_clk(cru_priv, SCLK_SDMMC, sdmmc_rate);
	px30_nandc_set_clk(cru_priv, nandc_rate);
	px30_sfc_set_clk(cru_priv, SCLK_SFC, sfc_rate);

	return priv->gpll_hz;
}

static ulong px30_pmuclk_get_rate(struct clk *clk)
{
	struct px30_pmuclk_priv *priv = dev_get_priv(clk->dev);
	ulong rate = 0;

	debug("%s %ld\n", __func__, clk->id);
	switch (clk->id) {
	case PLL_GPLL:
		rate = px30_gpll_get_pmuclk(priv);
		break;
	case PCLK_PMU_PRE:
		rate = px30_pclk_pmu_get_pmuclk(priv);
		break;
	default:
		return -ENOENT;
	}

	return rate;
}

static ulong px30_pmuclk_set_rate(struct clk *clk, ulong rate)
{
	struct px30_pmuclk_priv *priv = dev_get_priv(clk->dev);
	ulong ret = 0;

	debug("%s %ld %ld\n", __func__, clk->id, rate);
	switch (clk->id) {
	case PLL_GPLL:
		ret = px30_gpll_set_pmuclk(priv, rate);
		break;
	case PCLK_PMU_PRE:
		ret = px30_pclk_pmu_set_pmuclk(priv, rate);
		break;
	default:
		return -ENOENT;
	}

	return ret;
}

static struct clk_ops px30_pmuclk_ops = {
	.get_rate = px30_pmuclk_get_rate,
	.set_rate = px30_pmuclk_set_rate,
};

static void px30_clk_init(struct px30_pmuclk_priv *priv)
{
	struct udevice *cru_dev;
	struct px30_clk_priv *cru_priv;
	ulong npll_hz;
	int ret;

	ret = uclass_get_device_by_name(UCLASS_CLK,
					"clock-controller@ff2b0000", &cru_dev);
	if (ret) {
		printf("%s failed to get cru device\n", __func__);
		return;
	}

	cru_priv = dev_get_priv(cru_dev);

	/* Source from xin_osc0_half before gpll rate. */
	px30_i2s1_mclk_set_clk(cru_priv, SCLK_I2S1_OUT, 12000000);

	priv->gpll_hz = px30_gpll_get_pmuclk(priv);
	if (priv->gpll_hz != GPLL_HZ) {
		ret = px30_gpll_set_pmuclk(priv, GPLL_HZ);
		if (ret < 0)
			printf("%s failed to set gpll rate\n", __func__);
	}

	cru_priv->gpll_hz = priv->gpll_hz;

	npll_hz = px30_clk_get_pll_rate(cru_priv, NPLL);
	if (npll_hz != NPLL_HZ) {
		ret = px30_clk_set_pll_rate(cru_priv, NPLL, NPLL_HZ);
		if (ret < 0)
			printf("%s failed to set npll rate\n", __func__);
	}

	px30_bus_set_clk(cru_priv, ACLK_BUS_PRE, ACLK_BUS_HZ);
	px30_bus_set_clk(cru_priv, HCLK_BUS_PRE, HCLK_BUS_HZ);
	px30_bus_set_clk(cru_priv, PCLK_BUS_PRE, PCLK_BUS_HZ);
	px30_peri_set_clk(cru_priv, ACLK_PERI_PRE, ACLK_PERI_HZ);
	px30_peri_set_clk(cru_priv, HCLK_PERI_PRE, HCLK_PERI_HZ);
	px30_pclk_pmu_set_pmuclk(priv, PCLK_PMU_HZ);

	/* Source from gpll as default set. */
	px30_i2s1_mclk_set_clk(cru_priv, SCLK_I2S1_OUT, 11289600);
}

static int px30_pmuclk_probe(struct udevice *dev)
{
	struct px30_pmuclk_priv *priv = dev_get_priv(dev);
	int ret;

	px30_clk_init(priv);

	/* Process 'assigned-{clocks/clock-parents/clock-rates}' properties */
	ret = clk_set_defaults(dev);
	if (ret)
		debug("%s clk_set_defaults failed %d\n", __func__, ret);

	return 0;
}

static int px30_pmuclk_ofdata_to_platdata(struct udevice *dev)
{
	struct px30_pmuclk_priv *priv = dev_get_priv(dev);

	priv->pmucru = dev_read_addr_ptr(dev);

	return 0;
}

static const struct udevice_id px30_pmuclk_ids[] = {
	{ .compatible = "rockchip,px30-pmucru" },
	{ }
};

U_BOOT_DRIVER(rockchip_px30_pmucru) = {
	.name		= "rockchip_px30_pmucru",
	.id		= UCLASS_CLK,
	.of_match	= px30_pmuclk_ids,
	.priv_auto_alloc_size = sizeof(struct px30_pmuclk_priv),
	.ofdata_to_platdata = px30_pmuclk_ofdata_to_platdata,
	.ops		= &px30_pmuclk_ops,
	.probe		= px30_pmuclk_probe,
};

/**
 * soc_clk_dump() - Print clock frequencies
 * Returns zero on success
 *
 * Implementation for the clk dump command.
 */
int soc_clk_dump(void)
{
	struct udevice *cru_dev, *pmucru_dev;
	struct px30_clk_priv *priv;
	const struct px30_clk_info *clk_dump;
	struct clk clk;
	unsigned long clk_count = ARRAY_SIZE(clks_dump);
	unsigned long rate;
	int i, ret;

	ret = uclass_get_device_by_driver(UCLASS_CLK,
					  DM_GET_DRIVER(rockchip_px30_cru),
					  &cru_dev);
	if (ret) {
		printf("%s failed to get cru device\n", __func__);
		return ret;
	}

	ret = uclass_get_device_by_driver(UCLASS_CLK,
					  DM_GET_DRIVER(rockchip_px30_pmucru),
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
