// SPDX-License-Identifier:     GPL-2.0+
/*
 * Copyright (C) 2020 Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <debug_uart.h>
#include <dm.h>
#include <dt-structs.h>
#include <ram.h>
#include <regmap.h>
#include <syscon.h>
#include <asm/io.h>
#include <asm/arch-rockchip/clock.h>
#include <asm/arch-rockchip/hardware.h>
#include <asm/arch-rockchip/rk_atags.h>
#include <asm/arch-rockchip/timer.h>
#include <asm/arch-rockchip/grf_rk3308.h>
#include <asm/arch-rockchip/sdram.h>
#include <asm/arch-rockchip/sdram_rk3308.h>
#include <asm/arch-rockchip/sdram_rv1108_pctl_phy.h>

DECLARE_GLOBAL_DATA_PTR;

#define CRU_BASE		0xff500000
#define GRF_BASE		0xff000000
#define SGRF_BASE		0xff2b0000
#define DDR_PHY_BASE		0xff530000
#define DDR_PCTL_BASE		0xff010000
#define DDR_STANDBY_BASE	0xff030000
#define PMU_BASS_ADDR		0xff520000
#define SERVICE_MSCH_BASE	0xff5c8000

struct rk3308_ddr_gd ddr_gd = {
#include	"sdram-rk3308-ddr-skew.inc"
};

struct sdram_params sdram_configs[] = {
#if (CONFIG_ROCKCHIP_TPL_INIT_DRAM_TYPE == 3)
	#include "sdram_inc/rk3308/sdram-rk3308-ddr3-detect-589.inc"
#elif (CONFIG_ROCKCHIP_TPL_INIT_DRAM_TYPE == 2)
	#include "sdram_inc/rk3308/sdram-rk3308-ddr2-detect-451.inc"
#elif (CONFIG_ROCKCHIP_TPL_INIT_DRAM_TYPE == 5)
	#include "sdram_inc/rk3308/sdram-rk3308-lpddr2-detect-451.inc"
#endif
};

#define DDR3_DDR2_ODT_DISABLE_FREQ	(666)

#define DDR2_TRFC_256MBIT	(75)
#define DDR2_TRFC_512MBIT	(105)
#define DDR2_TRFC_1GBIT		(128)
#define DDR2_TRFC_2GBIT		(195)
#define DDR2_TRFC_4GBIT		(328)

#define DDR3_TRFC_512MBIT	(90)
#define DDR3_TRFC_1GBIT		(110)
#define DDR3_TRFC_2GBIT		(160)
#define DDR3_TRFC_4GBIT		(300)
#define DDR3_TRFC_8GBIT		(350)

#define LPDDR2_TRFC_8GBIT		(210) /*ns*/
#define LPDDR2_TRFC_4GBIT		(130) /*ns*/
#define LPDDR2_TREC_512MBIT		(90) /*ns*/

void enable_ddr_io_ret(struct dram_info *priv)
{
	rk_clrsetreg(&priv->pmu->sft_con_lo, DDR_IO_RET_CFG_MASK,
		     DDR_IO_RET_CFG << DDR_IO_RET_CFG_SHIFT);

	rk_clrsetreg(&priv->grf->upctl_con0, GRF_DDR_16BIT_EN_MASK,
		     GRF_DDR_16BIT_EN << GRF_DDR_16BIT_EN_SHIFT);
}

void pll_set(u32 pll_type, struct dram_info *priv,
	     struct rockchip_pll_rate_table *pll_priv)
{
	/* pll power down */
	rk_clrsetreg(&priv->cru->pll[pll_type].con1, PLLPD0_MASK,
		     PLLPD0_POWER_DOWN << PLLPD0_SHIFT);
	rk_clrsetreg(&priv->cru->pll[pll_type].con1,
		     DSMPD_MASK, pll_priv->dsmpd << DSMPD_SHIFT);

	/* set pll freq */
	rk_clrsetreg(&priv->cru->pll[pll_type].con0,
		     FBDIV_MASK | POSTDIV1_MASK,
		     pll_priv->fbdiv << FBDIV_SHIFT |
		     pll_priv->postdiv1 << POSTDIV1_SHIFT);
	rk_clrsetreg(&priv->cru->pll[pll_type].con1,
		     POSTDIV2_MASK | REFDIV_MASK,
		     pll_priv->postdiv2 << POSTDIV2_SHIFT |
		     pll_priv->refdiv << REFDIV_SHIFT);
	writel(pll_priv->frac << FRACDIV_SHIFT,
	       &priv->cru->pll[pll_type].con2);
	/* pll power up */
	rk_clrsetreg(&priv->cru->pll[pll_type].con1, PLLPD0_MASK,
		     PLLPD0_NO_POWER_DOWN << PLLPD0_SHIFT);

	/* wait until pll lock */
	while (!(readl(&priv->cru->pll[pll_type].con1) &
	       (1u << PLL_LOCK_SHIFT)))
		udelay(1);
}

void rkdclk_init(struct dram_info *priv,
		 struct sdram_params *params_priv)
{
	u32 ddr_pll_sel;
	u32 ddr_phy_div_con;
	u32 uart_div[5] = {15, 15, 15, 15, 15};
	struct rockchip_pll_rate_table rk3308_pll_div;

	/* DPLL VPLL0 VPLL1 mode in 24MHz*/
	rk_clrsetreg(&priv->cru->mode, VPLL1_WORK_MODE_MASK,
		     VPLL1_WORK_MODE_XIN_OSC0 << VPLL1_WORK_MODE_SHIFT);
	rk_clrsetreg(&priv->cru->mode, VPLL0_WORK_MODE_MASK,
		     VPLL0_WORK_MODE_XIN_OSC0 << VPLL0_WORK_MODE_SHIFT);
	rk_clrsetreg(&priv->cru->mode, DPLL_WORK_MODE_MASK,
		     DPLL_WORK_MODE_XIN_OSC0 << DPLL_WORK_MODE_SHIFT);

	/* set PLL without level shift */
	rk_clrsetreg(&priv->cru->mode, VPLL1_CLK_SEL_MASK,
		     VPLL1_CLK_SEL_WITHOUT_LVL_SHIFT << VPLL1_CLK_SEL_SHIFT);
	rk_clrsetreg(&priv->cru->mode, VPLL0_CLK_SEL_MASK,
		     VPLL0_CLK_SEL_WITHOUT_LVL_SHIFT << VPLL0_CLK_SEL_SHIFT);
	rk_clrsetreg(&priv->cru->mode, DPLL_CLK_SEL_MASK,
		     DPLL_CLK_SEL_WITHOUT_LVL_SHIFT << DPLL_CLK_SEL_SHIFT);

	/* set vpll1 in 903.168MHz vco = 1.806GHz */
	rk3308_pll_div.refdiv = 2;
	rk3308_pll_div.fbdiv = 150;
	rk3308_pll_div.postdiv1 = 2;
	rk3308_pll_div.postdiv2 = 1;
	rk3308_pll_div.frac = 0x872B02;
	rk3308_pll_div.dsmpd = 0;
	pll_set(VPLL1, priv, &rk3308_pll_div);

	if (params_priv->ddr_timing_t.freq == 393) {
		/* set vpll0 in 786.432MHz vco = 3.146GHz */
		rk3308_pll_div.refdiv = 2;
		rk3308_pll_div.fbdiv = 262;
		rk3308_pll_div.postdiv1 = 4;
		rk3308_pll_div.postdiv2 = 1;
		rk3308_pll_div.frac = 0x24DD2F;
		rk3308_pll_div.dsmpd = 0;
	} else {
		/* set vpll0 in 1179.648MHz, vco = 2.359GHz*/
		rk3308_pll_div.refdiv = 2;
		rk3308_pll_div.fbdiv = 196;
		rk3308_pll_div.postdiv1 = 2;
		rk3308_pll_div.postdiv2 = 1;
		rk3308_pll_div.frac = 0x9BA5E3;
		rk3308_pll_div.dsmpd = 0;
	}
	pll_set(VPLL0, priv, &rk3308_pll_div);

	if (params_priv->ddr_timing_t.freq == 800) {
		ddr_pll_sel = 0;
		ddr_phy_div_con = 0;
	} else if (params_priv->ddr_timing_t.freq == 589) {
		ddr_pll_sel = 1;
		ddr_phy_div_con = 0;
	} else if (params_priv->ddr_timing_t.freq == 451) {
		ddr_pll_sel = 2;
		ddr_phy_div_con = 0;
	} else if (params_priv->ddr_timing_t.freq == 393) {
		ddr_pll_sel = 1;
		ddr_phy_div_con = 0;
	} else if (params_priv->ddr_timing_t.freq == 294) {
		ddr_pll_sel = 1;
		ddr_phy_div_con = 1;
	} else if (params_priv->ddr_timing_t.freq == 225) {
		ddr_pll_sel = 2;
		ddr_phy_div_con = 1;
	} else {
		printascii("err\n");
		while (1)
			;
	}

	/* dpll default set in 1300MHz */
	if (params_priv->ddr_timing_t.freq == 800) {
		/* set dpll in 1584 MHz ,vco=3.168G*/
		rk3308_pll_div.refdiv = 1;
		rk3308_pll_div.fbdiv = 132;
		rk3308_pll_div.postdiv1 = 2;
		rk3308_pll_div.postdiv2 = 1;
		rk3308_pll_div.frac = 0;
		rk3308_pll_div.dsmpd = 1;
	} else {
		/* 1300000000,vco = 1.3GHz */
		rk3308_pll_div.refdiv = 6;
		rk3308_pll_div.fbdiv = 325;
		rk3308_pll_div.postdiv1 = 1;
		rk3308_pll_div.postdiv2 = 1;
		rk3308_pll_div.frac = 0;
		rk3308_pll_div.dsmpd = 1;
	}

	pll_set(DPLL, priv, &rk3308_pll_div);

	/* set ddrphy freq */
	rk_clrsetreg(&priv->cru->clksel_con[1],
		     DDRPHY4X_PLL_CLK_SEL_MASK | DDRPHY4X_DIV_CON_MASK,
		     ddr_pll_sel << DDRPHY4X_PLL_CLK_SEL_SHIFT |
		     ddr_phy_div_con << DDRPHY4X_DIV_CON_SIHFT);

	/* set aclk_bus 216.7MHz */
	rk_clrsetreg(&priv->cru->clksel_con[5],
		     A_H_PCLK_BUS_PLL_SEL_MASK | ACLK_BUS_DIV_CON_MASK,
		     A_H_PCLK_BUS_PLL_SEL_DPLL << A_H_PCLK_BUS_PLL_SEL_SHIFT |
		     ACLK_BUS_DIV_CON_5 << ACLK_BUS_DIV_CON_SHIFT);
	/* set pclk_bus 50MHz,hclk_bus 92.857MHz */
	rk_clrsetreg(&priv->cru->clksel_con[6],
		     PCLK_BUS_DIV_CON_MASK | HCLK_BUS_DIV_CON_MASK,
		     PCLK_BUS_DIV_CON_25 << PCLK_BUS_DIV_CON_SHIFT |
		     HCLK_BUS_DIV_CON_13 << HCLK_BUS_DIV_CON_SHIFT);
	/* set crypto 92.857MHz,crypto_apk 92.857MHz */
	rk_clrsetreg(&priv->cru->clksel_con[7],
		     CLK_CRYPTO_APK_SEL_MASK | CLK_CRYPTO_APK_DIV_MASK |
		     CLK_CRYPTO_PLL_SEL_MASK | CLK_CRYPTO_DIV_CON_MASK,
		     CLK_CRYPTO_APK_SEL_DPLL << CLK_CRYPTO_APK_SEL_SHIFT |
		     CLK_CRYPTO_APK_DIV_13 << CLK_CRYPTO_APK_DIV_SHIFT |
		     CLK_CRYPTO_PLL_SEL_DPLL << CLK_CRYPTO_PLL_SEL_SHIFT |
		     CLK_CRYPTO_DIV_CON_13 << CLK_CRYPTO_DIV_CON_SHIFT);
	/* set aclk_peri 216.7MHz */
	rk_clrsetreg(&priv->cru->clksel_con[36],
		     A_H_P_PERI_PLL_SEL_MASK | ACLK_PERI_DIV_CON_MASK,
		     A_H_P_PERI_PLL_SEL_DPLL << A_H_P_PERI_PLL_SEL_SHIFT |
		     ACLK_PERI_DIV_CON_5 << ACLK_PERI_DIV_CON_SHIFT);
	/* set hclk_peri 92.857MHz,pclk_peri 46.428MHz */
	rk_clrsetreg(&priv->cru->clksel_con[37],
		     PCLK_PERI_DIV_CON_MASK | HCLK_PERI_DIV_CON_MASK,
		     PCLK_PERI_DIV_CON_27 << PCLK_PERI_DIV_CON_SHIFT |
		     HCLK_PERI_DIV_CON_13 << HCLK_PERI_DIV_CON_SHIFT);
	/* set NANDC 92.857MHz */
	rk_clrsetreg(&priv->cru->clksel_con[38],
		     CLK_NANDC_PLL_SEL_MASK |
		     CLK_NANDC_DIV_CON_MASK,
		     CLK_NANDC_PLL_SEL_DPLL << CLK_NANDC_PLL_SEL_SHIFT |
		     CLK_NANDC_DIV_CON_13 << CLK_NANDC_DIV_CON_SHIFT);
	/* set SDMMC 46.4/(internal freq_div 2)=23.2MHz */
	rk_clrsetreg(&priv->cru->clksel_con[39],
		     CLK_SDMMC_PLL_SEL_MASK |
		     CLK_SDMMC_DIV_CON_MASK,
		     CLK_SDMMC_PLL_SEL_DPLL << CLK_SDMMC_PLL_SEL_SHIFT |
		     CLK_SDMMC_DIV_CON_27 << CLK_SDMMC_DIV_CON_SHIFT);
	/* set emmc 46.4/(internal freq_div 2)=23.2MHz */
	rk_clrsetreg(&priv->cru->clksel_con[41],
		     CLK_EMMC_PLL_SEL_MASK |
		     CLK_EMMC_DIV_CON_MASK,
		     CLK_EMMC_PLL_SEL_DPLL << CLK_EMMC_PLL_SEL_SHIFT |
		     CLK_EMMC_DIV_CON_27 << CLK_EMMC_DIV_CON_SHIFT);
	/* set SFC 24.07/(internal freq_div 2)=12.0MHz */
	rk_clrsetreg(&priv->cru->clksel_con[42],
		     CLK_SFC_PLL_SEL_MASK | CLK_SFC_DIV_CON_MASK,
		     CLK_SFC_PLL_SEL_DPLL << CLK_SFC_PLL_SEL_SHIFT |
		     CLK_SFC_DIV_CON_53 << CLK_SFC_DIV_CON_SHIFT);
#if defined(CONFIG_DPLL_FREQ_1200MHZ)
	/*vco=1.2GHz*/
	rk3308_pll_div.refdiv = 2;
	rk3308_pll_div.fbdiv = 100;
	rk3308_pll_div.postdiv1 = 1;
	rk3308_pll_div.postdiv2 = 1;
	rk3308_pll_div.frac = 0;

	/* set dpll in 1200 MHz */
	pll_set(DPLL, priv, &rk3308_pll_div);

	/* set aclk_bus 200MHz */
	rk_clrsetreg(&priv->cru->clksel_con[5],
		     A_H_PCLK_BUS_PLL_SEL_MASK | ACLK_BUS_DIV_CON_MASK,
		     A_H_PCLK_BUS_PLL_SEL_DPLL << A_H_PCLK_BUS_PLL_SEL_SHIFT |
		     ACLK_BUS_DIV_CON_5 << ACLK_BUS_DIV_CON_SHIFT);
	/* set pclk_bus 46.15MHz,hclk_bus 100MHz */
	rk_clrsetreg(&priv->cru->clksel_con[6],
		     PCLK_BUS_DIV_CON_MASK | HCLK_BUS_DIV_CON_MASK,
		     PCLK_BUS_DIV_CON_25 << PCLK_BUS_DIV_CON_SHIFT |
		     HCLK_BUS_DIV_CON_11 << HCLK_BUS_DIV_CON_SHIFT);
	/* set crypto,crypto_apk 100MHz */
	rk_clrsetreg(&priv->cru->clksel_con[7],
		     CLK_CRYPTO_APK_SEL_MASK | CLK_CRYPTO_APK_DIV_MASK |
		     CLK_CRYPTO_PLL_SEL_MASK | CLK_CRYPTO_DIV_CON_MASK,
		     CLK_CRYPTO_APK_SEL_DPLL << CLK_CRYPTO_APK_SEL_SHIFT |
		     CLK_CRYPTO_APK_DIV_11 << CLK_CRYPTO_APK_DIV_SHIFT |
		     CLK_CRYPTO_PLL_SEL_DPLL << CLK_CRYPTO_PLL_SEL_SHIFT |
		     CLK_CRYPTO_DIV_CON_11 << CLK_CRYPTO_DIV_CON_SHIFT);
	/* set aclk_peri 200MHz */
	rk_clrsetreg(&priv->cru->clksel_con[36],
		     A_H_P_PERI_PLL_SEL_MASK | ACLK_PERI_DIV_CON_MASK,
		     A_H_P_PERI_PLL_SEL_DPLL << A_H_P_PERI_PLL_SEL_SHIFT |
		     ACLK_PERI_DIV_CON_5 << ACLK_PERI_DIV_CON_SHIFT);
	/* set hclk_peri 100MHz,pclk_peri 50MHz */
	rk_clrsetreg(&priv->cru->clksel_con[37],
		     PCLK_PERI_DIV_CON_MASK | HCLK_PERI_DIV_CON_MASK,
		     PCLK_PERI_DIV_CON_23 << PCLK_PERI_DIV_CON_SHIFT |
		     HCLK_PERI_DIV_CON_11 << HCLK_PERI_DIV_CON_SHIFT);
	/* set NANDC 100MHz */
	rk_clrsetreg(&priv->cru->clksel_con[38],
		     CLK_NANDC_PLL_SEL_MASK |
		     CLK_NANDC_DIV_CON_MASK,
		     CLK_NANDC_PLL_SEL_DPLL << CLK_NANDC_PLL_SEL_SHIFT |
		     CLK_NANDC_DIV_CON_11 << CLK_NANDC_DIV_CON_SHIFT);
	/* set SDMMC 50MHz */
	rk_clrsetreg(&priv->cru->clksel_con[39],
		     CLK_SDMMC_PLL_SEL_MASK |
		     CLK_SDMMC_DIV_CON_MASK,
		     CLK_SDMMC_PLL_SEL_DPLL << CLK_SDMMC_PLL_SEL_SHIFT |
		     CLK_SDMMC_DIV_CON_23 << CLK_SDMMC_DIV_CON_SHIFT);
	/* set emmc 50MHz */
	rk_clrsetreg(&priv->cru->clksel_con[41],
		     CLK_EMMC_PLL_SEL_MASK |
		     CLK_EMMC_DIV_CON_MASK,
		     CLK_EMMC_PLL_SEL_DPLL << CLK_EMMC_PLL_SEL_SHIFT |
		     CLK_EMMC_DIV_CON_23 << CLK_EMMC_DIV_CON_SHIFT);
	/* set SFC 24MHz */
	rk_clrsetreg(&priv->cru->clksel_con[42],
		     CLK_SFC_PLL_SEL_MASK | CLK_SFC_DIV_CON_MASK,
		     CLK_SFC_PLL_SEL_DPLL << CLK_SFC_PLL_SEL_SHIFT |
		     CLK_SFC_DIV_CON_49 << CLK_SFC_DIV_CON_SHIFT);

#elif defined(CONFIG_DPLL_FREQ_748MHZ)
	/*vco=1.5GHz*/
	rk3308_pll_div.refdiv = 6;
	rk3308_pll_div.fbdiv = 374;
	rk3308_pll_div.postdiv1 = 2;
	rk3308_pll_div.postdiv2 = 1;
	rk3308_pll_div.frac = 0;

	/* set dpll in 748 MHz */
	pll_set(DPLL, priv, &rk3308_pll_div);

	/* set aclk_bus 187MHz */
	rk_clrsetreg(&priv->cru->clksel_con[5],
		     A_H_PCLK_BUS_PLL_SEL_MASK | ACLK_BUS_DIV_CON_MASK,
		     A_H_PCLK_BUS_PLL_SEL_DPLL << A_H_PCLK_BUS_PLL_SEL_SHIFT |
		     ACLK_BUS_DIV_CON_3 << ACLK_BUS_DIV_CON_SHIFT);
	/* set pclk_bus 46.75MHz,hclk_bus 93.5MHz */
	rk_clrsetreg(&priv->cru->clksel_con[6],
		     PCLK_BUS_DIV_CON_MASK | HCLK_BUS_DIV_CON_MASK,
		     PCLK_BUS_DIV_CON_15 << PCLK_BUS_DIV_CON_SHIFT |
		     HCLK_BUS_DIV_CON_7 << HCLK_BUS_DIV_CON_SHIFT);
	/* set crypto,crypto_apk 93.5MHz */
	rk_clrsetreg(&priv->cru->clksel_con[7],
		     CLK_CRYPTO_APK_SEL_MASK | CLK_CRYPTO_APK_DIV_MASK |
		     CLK_CRYPTO_PLL_SEL_MASK | CLK_CRYPTO_DIV_CON_MASK,
		     CLK_CRYPTO_APK_SEL_DPLL << CLK_CRYPTO_APK_SEL_SHIFT |
		     CLK_CRYPTO_APK_DIV_7 << CLK_CRYPTO_APK_DIV_SHIFT |
		     CLK_CRYPTO_PLL_SEL_DPLL << CLK_CRYPTO_PLL_SEL_SHIFT |
		     CLK_CRYPTO_DIV_CON_7 << CLK_CRYPTO_DIV_CON_SHIFT);
	/* set aclk_peri 187MHz */
	rk_clrsetreg(&priv->cru->clksel_con[36],
		     A_H_P_PERI_PLL_SEL_MASK | ACLK_PERI_DIV_CON_MASK,
		     A_H_P_PERI_PLL_SEL_DPLL << A_H_P_PERI_PLL_SEL_SHIFT |
		     ACLK_PERI_DIV_CON_3 << ACLK_PERI_DIV_CON_SHIFT);
	/* set hclk_peri 93.5MHz,pclk_peri 46.75MHz */
	rk_clrsetreg(&priv->cru->clksel_con[37],
		     PCLK_PERI_DIV_CON_MASK | HCLK_PERI_DIV_CON_MASK,
		     PCLK_PERI_DIV_CON_15 << PCLK_PERI_DIV_CON_SHIFT |
		     HCLK_PERI_DIV_CON_7 << HCLK_PERI_DIV_CON_SHIFT);
	/* set NANDC 93.5MHz */
	rk_clrsetreg(&priv->cru->clksel_con[38],
		     CLK_NANDC_PLL_SEL_MASK |
		     CLK_NANDC_DIV_CON_MASK,
		     CLK_NANDC_SEL50_ALWAYS << CLK_NANDC_SEL50_SHIFT |
		     CLK_NANDC_PLL_SEL_DPLL << CLK_NANDC_PLL_SEL_SHIFT |
		     CLK_NANDC_DIV_CON_7 << CLK_NANDC_DIV_CON_SHIFT);
	/* set NANDC 46.75MHz */
	rk_clrsetreg(&priv->cru->clksel_con[39],
		     CLK_SDMMC_PLL_SEL_MASK |
		     CLK_SDMMC_DIV_CON_MASK,
		     CLK_SDMMC_PLL_SEL_DPLL << CLK_SDMMC_PLL_SEL_SHIFT |
		     CLK_SDMMC_DIV_CON_15 << CLK_SDMMC_DIV_CON_SHIFT);
	/* set emmc 46.75MHz */
	rk_clrsetreg(&priv->cru->clksel_con[41],
		     CLK_EMMC_PLL_SEL_MASK |
		     CLK_EMMC_DIV_CON_MASK,
		     CLK_EMMC_PLL_SEL_DPLL << CLK_EMMC_PLL_SEL_SHIFT |
		     CLK_EMMC_DIV_CON_15 << CLK_EMMC_DIV_CON_SHIFT);
	/* set SFC 23.375MHz */
	rk_clrsetreg(&priv->cru->clksel_con[42],
		     CLK_SFC_PLL_SEL_MASK | CLK_SFC_DIV_CON_MASK,
		     CLK_SFC_PLL_SEL_DPLL << CLK_SFC_PLL_SEL_SHIFT |
		     CLK_SFC_DIV_CON_31 << CLK_SFC_DIV_CON_SHIFT);

#endif
	/* set spdif tx lower than 100Mhz */
	rk_clrsetreg(&priv->cru->clksel_con[48],
		     CLK_SPDIFTX_DIV_CON_MASK,
		     CLK_SPDIFTX_DIV_CON_15 << CLK_SPDIFTX_DIV_CON_SHIFT);

	if (UART_INFO_ID(ddr_gd.head_info.g_uart_info) < 5)
		uart_div[UART_INFO_ID(ddr_gd.head_info.g_uart_info)] = 0;

	/* set uart0~4 lower than 100Mhz */
	rk_clrsetreg(&priv->cru->clksel_con[10],
		     CLK_UART0_DIV_CON_MASK,
		     uart_div[0] << CLK_UART0_DIV_CON_SHIFT);
	rk_clrsetreg(&priv->cru->clksel_con[13],
		     CLK_UART1_DIV_CON_MASK,
		     uart_div[1] << CLK_UART1_DIV_CON_SHIFT);
	rk_clrsetreg(&priv->cru->clksel_con[16],
		     CLK_UART2_DIV_CON_MASK,
		     uart_div[2] << CLK_UART2_DIV_CON_SHIFT);
	rk_clrsetreg(&priv->cru->clksel_con[19],
		     CLK_UART3_DIV_CON_MASK,
		     uart_div[3] << CLK_UART3_DIV_CON_SHIFT);
	rk_clrsetreg(&priv->cru->clksel_con[22],
		     CLK_UART4_DIV_CON_MASK,
		     uart_div[4] << CLK_UART4_DIV_CON_SHIFT);

	/* pll clk in pll out */
	rk_clrsetreg(&priv->cru->mode, VPLL1_WORK_MODE_MASK,
		     VPLL1_WORK_MODE_PLL << VPLL1_WORK_MODE_SHIFT);
	rk_clrsetreg(&priv->cru->mode, VPLL0_WORK_MODE_MASK,
		     VPLL0_WORK_MODE_PLL << VPLL0_WORK_MODE_SHIFT);
	rk_clrsetreg(&priv->cru->mode, DPLL_WORK_MODE_MASK,
		     DPLL_WORK_MODE_PLL << DPLL_WORK_MODE_SHIFT);
}

void phy_pctrl_reset_cru(struct dram_info *priv)
{
	rk_clrsetreg(&priv->cru->softrst_con[1],
		     PRESETN_DDRPHY_REQ_MASK | RESETN_DDRPHYDIV_REQ_MASK |
		     RESETN_DDRPHY_REQ_MASK | PRESETN_DDRUPCTL_REQ_MASK |
		     RESETN_DDRUPCTL_REQ_MASK,
		     PRESETN_DDRPHY_REQ_EN << PRESETN_DDRPHY_REQ_SHIFT |
		     RESETN_DDRPHYDIV_REQ_EN << RESETN_DDRPHYDIV_REQ_SHIFT |
		     RESETN_DDRPHY_REQ_EN << RESETN_DDRPHY_REQ_SHIFT |
		     PRESETN_DDRUPCTL_REQ_EN << PRESETN_DDRUPCTL_REQ_SHIFT |
		     RESETN_DDRUPCTL_REQ_EN << RESETN_DDRUPCTL_REQ_SHIFT);
	udelay(10);

	rk_clrsetreg(&priv->cru->softrst_con[1],
		     PRESETN_DDRPHY_REQ_MASK | RESETN_DDRPHYDIV_REQ_MASK |
		     RESETN_DDRPHY_REQ_MASK,
		     PRESETN_DDRPHY_REQ_DIS << PRESETN_DDRPHY_REQ_SHIFT |
		     RESETN_DDRPHYDIV_REQ_DIS << RESETN_DDRPHYDIV_REQ_SHIFT |
		     RESETN_DDRPHY_REQ_DIS << RESETN_DDRPHY_REQ_SHIFT);
	udelay(10);

	rk_clrsetreg(&priv->cru->softrst_con[1],
		     PRESETN_DDRUPCTL_REQ_MASK | RESETN_DDRUPCTL_REQ_MASK,
		     PRESETN_DDRUPCTL_REQ_DIS << PRESETN_DDRUPCTL_REQ_SHIFT |
		     RESETN_DDRUPCTL_REQ_DIS << RESETN_DDRUPCTL_REQ_SHIFT);
	udelay(10);
}

void pctl_cfg_grf(struct dram_info *priv,
		  struct sdram_params *params_priv)
{
	if (params_priv->ddr_config_t.ddr_type == DDR3 ||
	    params_priv->ddr_config_t.ddr_type == DDR2)
		rk_clrsetreg(&priv->grf->soc_con12, NOC_MSCH_MAINDDR3_MASK,
			     NOC_MSCH_MAINDDR3_EN << NOC_MSCH_MAINDDR3_SHIFT);
	else
		rk_clrsetreg(&priv->grf->soc_con12, NOC_MSCH_MAINDDR3_MASK,
			     NOC_MSCH_MAINDDR3_DIS << NOC_MSCH_MAINDDR3_SHIFT);
}

void ddr_msch_cfg(struct dram_info *priv,
		  struct sdram_params *params_priv)
{
	writel(BWRATIO_HALF_BW | params_priv->ddr_timing_t.noc_timing.d32,
	       &priv->service_msch->ddrtiming);
	writel(params_priv->ddr_timing_t.readlatency,
	       &priv->service_msch->readlatency);
}

void ddr_msch_cfg_rbc(struct sdram_params *params_priv,
		      struct dram_info *priv)
{
	int i = 0;

	if (params_priv->ddr_config_t.bank == 3) {
		/* bank = 8 */
		if (params_priv->ddr_config_t.col == 10)
			i = 1;
		else if (params_priv->ddr_config_t.col == 11)
			i = 2;
		else
			goto msch_err;

	} else if (params_priv->ddr_config_t.bank == 2) {
		/* bank = 4 */
		i = 0;
	} else {
		goto msch_err;
	}

	writel(i, &priv->service_msch->ddrconf);
	return;

msch_err:
	printascii("msch_err\n");
	while (1)
		;
}

void ddr_phy_skew_cfg(struct dram_info *priv)
{
	copy_to_reg(&priv->phy->phy_reg_ca_skew[0],
		    &ddr_gd.ddr_skew.a0_a1_skew[0], 14 * 4);
	copy_to_reg(&priv->phy->phy_reg_skew_cs0data[0],
		    &ddr_gd.ddr_skew.cs0_dm0_skew[0], 22 * 4);

	writel(PHY_TX_DE_SKEW_EN << PHY_TX_DE_SKEW_SHIFT,
	       &priv->phy->phy_reg2);
}

void set_ds_odt(struct dram_info *priv,
		struct sdram_params *params_priv)
{
	/* set phy drive resistance */
	writel(PHY_RON_RTT_56OHM, &priv->phy->phy_reg11);
	clrsetbits_le32(&priv->phy->phy_reg12, CMD_PRCOMP_MASK,
			PHY_RON_RTT_56OHM << CMD_PRCOMP_SHIFT);

	writel(PHY_RON_RTT_45OHM, &priv->phy->phy_reg16);
	writel(PHY_RON_RTT_45OHM, &priv->phy->phy_reg18);
	writel(PHY_RON_RTT_56OHM, &priv->phy->phy_reg20);
	writel(PHY_RON_RTT_56OHM, &priv->phy->phy_reg2f);
	writel(PHY_RON_RTT_56OHM, &priv->phy->phy_reg30);
	writel(PHY_RON_RTT_56OHM, &priv->phy->phy_reg3f);
	if (params_priv->ddr_config_t.ddr_type == LPDDR2) {
		writel(PHY_RON_RTT_DISABLE, &priv->phy->phy_reg21);
		writel(PHY_RON_RTT_DISABLE, &priv->phy->phy_reg2e);
		writel(PHY_RON_RTT_DISABLE, &priv->phy->phy_reg31);
		writel(PHY_RON_RTT_DISABLE, &priv->phy->phy_reg3e);
	} else {
		if (params_priv->ddr_timing_t.freq >
		    DDR3_DDR2_ODT_DISABLE_FREQ) {
			/*set phy odt*/
			writel(PHY_RON_RTT_225OHM, &priv->phy->phy_reg21);
			writel(PHY_RON_RTT_225OHM, &priv->phy->phy_reg2e);
			writel(PHY_RON_RTT_225OHM, &priv->phy->phy_reg31);
			writel(PHY_RON_RTT_225OHM, &priv->phy->phy_reg3e);
		} else {
			/*disable phy odt*/
			writel(PHY_RON_RTT_DISABLE, &priv->phy->phy_reg21);
			writel(PHY_RON_RTT_DISABLE, &priv->phy->phy_reg2e);
			writel(PHY_RON_RTT_DISABLE, &priv->phy->phy_reg31);
			writel(PHY_RON_RTT_DISABLE, &priv->phy->phy_reg3e);
		}
	}
}

void ddr_phy_dqs_rx_dll_cfg(struct dram_info *priv, u32 freq)
{
	if (freq > 736) {
		/* 22.5 degree delay */
		writel(LEFT_CHN_A_READ_DQS_22_5_DELAY, &priv->phy->phy_reg28);
		writel(RIGHT_CHN_A_READ_DQS_22_5_DELAY, &priv->phy->phy_reg38);
	} else if (freq > 441) {
		/* 45 degree delay */
		writel(LEFT_CHN_A_READ_DQS_45_DELAY, &priv->phy->phy_reg28);
		writel(RIGHT_CHN_A_READ_DQS_45_DELAY, &priv->phy->phy_reg38);
	}
}

void ddr_msch_get_max_col(struct dram_info *priv,
			  struct ddr_schedule *sch_priv)
{
	writel(2, &priv->service_msch->ddrconf);
	sch_priv->col = 11;
	sch_priv->bank = 3;
}

void ddr_msch_get_max_row(struct dram_info *priv,
			  struct ddr_schedule *sch_priv)
{
	writel(1, &priv->service_msch->ddrconf);
	sch_priv->row = 15;
	sch_priv->col = 10;
	sch_priv->bank = 3;
}

void enable_ddr_standby(struct dram_info *priv,
			struct sdram_params *params_priv)
{
	rk_clrsetreg(&priv->grf->upctl_con0, CYSYREQ_UPCTL_DDRSTDBY_MASK,
		     CYSYREQ_UPCTL_DDRSTDBY_EN <<
		     CYSYREQ_UPCTL_DDRSTDBY_SHIFT);

	/* CG_EXIT_TH is equal phy dll lock time when we gate phy 4x clk */
	writel(CG_EXIT_TH << CG_EXIT_TH_SHIFT, &priv->standby->con1);

	if (params_priv->stdby_idle == 128) {
		if (params_priv->ddr_timing_t.freq == 451)
			params_priv->stdby_idle = 105;
		else if (params_priv->ddr_timing_t.freq == 393)
			params_priv->stdby_idle = 10;
	}
	writel(params_priv->stdby_idle << IDLE_TH_SHIFT |
		DDRPHY4X_GATE_EN << DDRPHY4X_GATE_SHIFT |
		UPCTL_CORE_CLK_GATE_EN << UPCTL_CORE_CLK_GATE_SHIFT |
		UPCTL_ACLK_GATE_EN << UPCTL_ACLK_GATE_SHIFT |
		CTL_IDLR_EN << CTL_IDLR_SHIFT |
		STDBY_EN << STDBY_EN_SHIFT, &priv->standby->con0);

	while (1) {
		if ((readl(&priv->standby->status0) &
		    STDBY_STATUS_MASK) == ST_STDBY) {
			break;
		}
	}
}

void ddr_set_atags(void)
{
	struct tag_serial t_serial;

	memset(&t_serial, 0, sizeof(struct tag_serial));
#ifdef CONFIG_DRAM_INIT_BUILD
	u32 uart_info;

	t_serial.version = 0;
	uart_info = ddr_gd.head_info.g_uart_info;
	if (UART_INFO_ID(uart_info) >= MAX_UART_NUMBER_) {
		t_serial.enable = 0;
	} else {
		t_serial.enable = 1;
		t_serial.baudrate = UART_INFO_BAUD(uart_info);
		t_serial.m_mode = UART_INFO_IOMUX(uart_info);
		t_serial.id = UART_INFO_ID(uart_info);
		if (UART_INFO_ID(uart_info) == 0)
			t_serial.addr = UART0_BASE;
		else if (UART_INFO_ID(uart_info) == 1)
			t_serial.addr = UART1_BASE;
		else if (UART_INFO_ID(uart_info) == 2)
			t_serial.addr = UART2_BASE;
		else if (UART_INFO_ID(uart_info) == 3)
			t_serial.addr = UART3_BASE;
		else
			t_serial.addr = UART4_BASE;
	}
#else
	/* set serial data to &t_serial */
#if defined(CONFIG_DEBUG_UART_BASE)
	t_serial.version = 0;
	t_serial.enable = 1;
	t_serial.addr = CONFIG_DEBUG_UART_BASE;
	t_serial.baudrate = CONFIG_BAUDRATE;

#if (CONFIG_DEBUG_UART_BASE == 0xFF0A0000)
	/* uart0 as debug uart */
	t_serial.m_mode = SERIAL_M_MODE_M0;
	t_serial.id = 0;
#elif (CONFIG_DEBUG_UART_BASE == 0xFF0B0000)
	/* uart1 as debug uart */
	t_serial.m_mode = SERIAL_M_MODE_M0;
	t_serial.id = 1;
#elif (CONFIG_DEBUG_UART_BASE == 0xFF0C0000)
#if (CONFIG_ROCKCHIP_UART_MUX_SEL_M == 0)
	t_serial.m_mode = SERIAL_M_MODE_M0;
#elif (CONFIG_ROCKCHIP_UART_MUX_SEL_M == 1)
	/* uart2 m1 as debug uart */
	t_serial.m_mode = SERIAL_M_MODE_M1;
#else
	#error "Please select M0 or M1 for uart2 !!!"
#endif
	t_serial.id = 2;
#elif (CONFIG_DEBUG_UART_BASE == 0xFF0D0000)
	/* uart3 as debug uart */
	t_serial.m_mode = SERIAL_M_MODE_M0;
	t_serial.id = 3;
#elif (CONFIG_DEBUG_UART_BASE == 0xFF0E0000)
	/* uart4 as debug uart */
	t_serial.m_mode = SERIAL_M_MODE_M0;
	t_serial.id = 4;
#else
	#error "Please select proper uart as debug uart !!!"
#endif

#endif /* defined(CONFIG_DEBUG_UART_BASE) */
#endif /* CONFIG_DRAM_INIT_BUILD */

	/* First pre-loader must call it before atags_set_tag() */
	atags_destroy();
	atags_set_tag(ATAG_SERIAL,  &t_serial);
}

static void modify_sdram_params(struct dram_info *priv,
				struct sdram_params *params_priv)
{
	u32 tmp = 0;
	u32 bw = 1;
	u32 nMHz = params_priv->ddr_timing_t.freq;

	size_t	size = 1llu << (bw +
		       params_priv->ddr_config_t.col +
		       params_priv->ddr_config_t.cs0_row +
		       params_priv->ddr_config_t.bank);

	move_to_config_state(priv);
	switch (params_priv->ddr_config_t.ddr_type) {
	case DDR2:
		if (size <= 0x4000000)
			tmp = DDR2_TRFC_512MBIT;
		else if (size <= 0x8000000)
			tmp = DDR2_TRFC_1GBIT;
		else if (size <= 0x10000000)
			tmp = DDR2_TRFC_2GBIT;
		else
			tmp = DDR2_TRFC_4GBIT;

		priv->pctl->trfc = (tmp * nMHz + 999) / 1000;
		tmp = (((tmp + 10) * nMHz + 999) / 1000);
		if (tmp < 200)
			tmp = 200;
		priv->pctl->texsr = tmp & 0x3FF;
		break;
	case DDR3:
		if (size <= 0x4000000)
			tmp = DDR3_TRFC_512MBIT;
		else if (size <= 0x8000000)
			tmp = DDR3_TRFC_1GBIT;
		else if (size <= 0x10000000)
			tmp = DDR3_TRFC_2GBIT;
		else if (size <= 0x20000000)
			tmp = DDR3_TRFC_4GBIT;
		else
			tmp = DDR3_TRFC_8GBIT;
		priv->pctl->trfc = (tmp * nMHz + 999) / 1000;
		break;
	case LPDDR2:
		if (size <= 0x4000000)
			tmp = LPDDR2_TREC_512MBIT;
		else if (size <= 0x20000000)
			tmp = LPDDR2_TRFC_4GBIT;
		else
			tmp = LPDDR2_TRFC_8GBIT;

		priv->pctl->trfc = (tmp * nMHz + 999) / 1000;
		tmp = (((tmp + 10) * nMHz + 999) / 1000);
		if (tmp < 2)
			tmp = 2;
		priv->pctl->texsr = tmp & 0x3FF;
		break;
	}
	move_to_access_state(priv);
}

int check_rd_gate(struct dram_info *priv)
{
	u32 max_val = 0;
	u32 min_val = 0xff;
	u32 gate[2];

	gate[0] = readl(&priv->phy->phy_regfb);
	gate[1] = readl(&priv->phy->phy_regfc);
	max_val = max(gate[0], gate[1]);
	min_val = min(gate[0], gate[1]);

	if (max_val > 0x80 || min_val < 0x20)
		return -1;
	else
		return 0;
}

static u32 dram_test(u32 i, u32 dqs)
{
	for (phys_addr_t j = 4 * dqs; j < 0x2000; j += 8)
		writel(PATTERN + i, j);

	for (phys_addr_t j = 4 * dqs; j < 0x2000; j += 8)
		if ((PATTERN + i) != readl(j))
			return 1;

	return 0;
}

/**
 * modify_data_training() - Setting DQS gating calibration bypass,
 * scanning data training range and then select center one.
 */
#define PHY_REG3C(n)		(0x10 * (n))

void modify_data_training(struct dram_info *priv,
			  struct sdram_params *params_priv)
{
	u32 value = 0;
	u32 i = 0, dqs = 0;
	u32 max_value = 0, min_value = 0;

	writel(readl(&priv->phy->phy_regfb), &priv->phy->phy_reg2c);
	writel(readl(&priv->phy->phy_regfc), &priv->phy->phy_reg3c);

	/* DQS gating calibration bypass */
	setbits_le32(&priv->phy->phy_reg2, BIT(1));

	/* rk3308 only support DQS0, DQS1 */
	for (dqs = 0; dqs < 2; dqs++) {
		value = readl(&priv->phy->phy_regfb + dqs);
		i = 0;
		while (dram_test(i, dqs) == 0) {
			i++;
			writel(value + i,
			       &priv->phy->phy_reg2c + PHY_REG3C(dqs));
		}
		max_value = value + i - 1;

		i = 1;
		writel(value - i, &priv->phy->phy_reg2c + PHY_REG3C(dqs));
		while (dram_test(i, dqs) == 0) {
			i++;
			writel(value - i,
			       &priv->phy->phy_reg2c + PHY_REG3C(dqs));
		}
		min_value = value - i + 1;

		/* select center one as gate training result */
		writel((max_value + min_value + 1) / 2,
		       &priv->phy->phy_reg2c + PHY_REG3C(dqs));
	}
	printascii("REG2C: 0x");
	printhex8(readl(&priv->phy->phy_reg2c));
	printascii(", 0x");
	printhex8(readl(&priv->phy->phy_reg3c));
	printascii("\n");
}

void enable_low_power(struct dram_info *priv,
		      struct sdram_params *params_priv)
{
	move_to_config_state(priv);

	if (params_priv->idle_pd == 48 && params_priv->idle_sr == 10) {
		if (params_priv->ddr_timing_t.freq == 451) {
			params_priv->idle_sr = 28;
			params_priv->idle_pd = 7;
		} else if (params_priv->ddr_timing_t.freq == 393) {
			params_priv->idle_sr = 31;
			params_priv->idle_pd = 15;
		}
	}
	clrsetbits_le32(&priv->pctl->mcfg, PD_IDLE_MASK,
			params_priv->idle_pd << PD_IDLE_SHIFT);
	clrsetbits_le32(&priv->pctl->mcfg1,
			SR_IDLE_MASK | HW_EXIT_IDLE_EN_MASK,
			params_priv->idle_sr | HW_EXIT_IDLE_EN);

	/* uPCTL in low_power status because of auto self-refresh */
	writel(GO_STATE, &priv->pctl->sctl);
}

int get_uart_config(void)
{
	return ddr_gd.head_info.g_uart_info;
}

int sdram_init(void)
{
	struct dram_info sdram_priv;
	struct sdram_params *params = sdram_configs;

	sdram_priv.cru = (void *)CRU_BASE;
	sdram_priv.grf = (void *)GRF_BASE;
	sdram_priv.sgrf = (void *)SGRF_BASE;
	sdram_priv.phy = (void *)DDR_PHY_BASE;
	sdram_priv.pctl = (void *)DDR_PCTL_BASE;
	sdram_priv.standby = (void *)DDR_STANDBY_BASE;
	sdram_priv.pmu = (void *)PMU_BASS_ADDR;
	sdram_priv.service_msch = (void *)SERVICE_MSCH_BASE;
	params->idle_pd = PD_INFO(ddr_gd.head_info.g_sr_pd_idle);
	params->idle_sr = SR_INFO(ddr_gd.head_info.g_sr_pd_idle);
	params->ddr_2t_en = DDR_2T_INFO(ddr_gd.head_info.g_2t_info);
	params->stdby_idle = STANDBY_IDLE(ddr_gd.head_info.g_ch_info);

	rv1108_sdram_init(&sdram_priv, params);

	modify_sdram_params(&sdram_priv, params);

	if (params->idle_pd != 0 && params->idle_sr != 0)
		enable_ddr_standby(&sdram_priv, params);
	ddr_set_atags();
	printascii("OUT\n");

	return 0;
}
