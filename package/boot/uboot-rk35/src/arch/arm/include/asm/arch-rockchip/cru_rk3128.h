/*
 * Copyright (c) 2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef _ASM_ARCH_CRU_RK3128_H
#define _ASM_ARCH_CRU_RK3128_H

#include <common.h>

#define MHz		1000000
#define OSC_HZ		(24 * MHz)

#define APLL_HZ		(600 * MHz)
#define GPLL_HZ		(594 * MHz)
#define CPLL_HZ		(400 * MHz)
#define ACLK_BUS_HZ	(148500000)
#define ACLK_PERI_HZ	(148500000)

/* Private data for the clock driver - used by rockchip_get_cru() */
struct rk3128_clk_priv {
	struct rk3128_cru *cru;
	ulong gpll_hz;
	ulong armclk_hz;
	ulong armclk_enter_hz;
	ulong armclk_init_hz;
	bool sync_kernel;
	bool set_armclk_rate;
};

struct rk3128_cru {
	struct rk3128_pll {
		unsigned int con0;
		unsigned int con1;
		unsigned int con2;
		unsigned int con3;
	} pll[4];
	unsigned int cru_mode_con;
	unsigned int cru_clksel_con[35];
	unsigned int cru_clkgate_con[11];
	unsigned int reserved;
	unsigned int cru_glb_srst_fst_value;
	unsigned int cru_glb_srst_snd_value;
	unsigned int reserved1[2];
	unsigned int cru_softrst_con[9];
	unsigned int cru_misc_con;
	unsigned int reserved2[2];
	unsigned int cru_glb_cnt_th;
	unsigned int reserved3[3];
	unsigned int cru_glb_rst_st;
	unsigned int reserved4[(0x1c0 - 0x150) / 4 - 1];
	unsigned int cru_sdmmc_con[2];
	unsigned int cru_sdio_con[2];
	unsigned int reserved5[2];
	unsigned int cru_emmc_con[2];
	unsigned int reserved6[4];
	unsigned int cru_pll_prg_en;
};
check_member(rk3128_cru, cru_pll_prg_en, 0x01f0);

enum rk3128_pll_id {
	APLL,
	DPLL,
	CPLL,
	GPLL,
	PLL_COUNT,
};

struct rk3128_clk_info {
	unsigned long id;
	char *name;
	bool is_cru;
};

#define RK2928_PLL_CON(x)	((x) * 0x4)
#define RK2928_MODE_CON		0x40

enum {
	/* CRU_CLK_SEL0_CON */
	BUS_PLL_SEL_SHIFT	= 13,
	BUS_PLL_SEL_MASK	= 3 << BUS_PLL_SEL_SHIFT,
	BUS_PLL_SEL_CPLL	= 0,
	BUS_PLL_SEL_GPLL,
	BUS_PLL_SEL_GPLL_DIV2,
	BUS_PLL_SEL_GPLL_DIV3,
	ACLK_BUS_DIV_SHIFT	= 8,
	ACLK_BUS_DIV_MASK	= 0x1f << ACLK_BUS_DIV_SHIFT,
	CORE_CLK_PLL_SEL_SHIFT	= 7,
	CORE_CLK_PLL_SEL_MASK	= 1 << CORE_CLK_PLL_SEL_SHIFT,
	CORE_CLK_PLL_SEL_APLL	= 0,
	CORE_CLK_PLL_SEL_GPLL_DIV2,
	CORE_DIV_CON_SHIFT	= 0,
	CORE_DIV_CON_MASK	= 0x1f << CORE_DIV_CON_SHIFT,

	/* CRU_CLK_SEL1_CON */
	PCLK_BUS_DIV_SHIFT	= 12,
	PCLK_BUS_DIV_MASK	= 7 << PCLK_BUS_DIV_SHIFT,
	HCLK_BUS_DIV_SHIFT	= 8,
	HCLK_BUS_DIV_MASK	= 3 << HCLK_BUS_DIV_SHIFT,
	CORE_ACLK_DIV_SHIFT	= 4,
	CORE_ACLK_DIV_MASK	= 0x07 << CORE_ACLK_DIV_SHIFT,
	CORE_DBG_DIV_SHIFT	= 0,
	CORE_DBG_DIV_MASK	= 0x0f << CORE_DBG_DIV_SHIFT,

	/* CRU_CLK_SEL2_CON */
	NANDC_PLL_SEL_SHIFT	= 14,
	NANDC_PLL_SEL_MASK	= 3 << NANDC_PLL_SEL_SHIFT,
	NANDC_PLL_SEL_CPLL	= 0,
	NANDC_PLL_SEL_GPLL,
	NANDC_CLK_DIV_SHIFT	= 8,
	NANDC_CLK_DIV_MASK	= 0x1f << NANDC_CLK_DIV_SHIFT,
	PVTM_CLK_DIV_SHIFT	= 0,
	PVTM_CLK_DIV_MASK	= 0x3f << PVTM_CLK_DIV_SHIFT,

	/* CRU_CLKSEL10_CON */
	PERI_PLL_SEL_SHIFT	= 14,
	PERI_PLL_SEL_MASK	= 3 << PERI_PLL_SEL_SHIFT,
	PERI_PLL_SEL_GPLL	= 0,
	PERI_PLL_SEL_CPLL,
	PERI_PLL_SEL_GPLL_DIV2,
	PERI_PLL_SEL_GPLL_DIV3,
	PCLK_PERI_DIV_SHIFT	= 12,
	PCLK_PERI_DIV_MASK	= 3 << PCLK_PERI_DIV_SHIFT,
	HCLK_PERI_DIV_SHIFT	= 8,
	HCLK_PERI_DIV_MASK	= 3 << HCLK_PERI_DIV_SHIFT,
	ACLK_PERI_DIV_SHIFT	= 0,
	ACLK_PERI_DIV_MASK	= 0x1f << ACLK_PERI_DIV_SHIFT,

	/* CRU_CLKSEL11_CON */
	SFC_PLL_SEL_SHIFT	= 14,
	SFC_PLL_SEL_MASK	= 3 << SFC_PLL_SEL_SHIFT,
	SFC_PLL_SEL_CPLL	= 0,
	SFC_PLL_SEL_GPLL,
	SFC_CLK_DIV_SHIFT	= 8,
	SFC_CLK_DIV_MASK	= 0x1f << SFC_CLK_DIV_SHIFT,
	MMC0_PLL_SHIFT		= 6,
	MMC0_PLL_MASK		= 3 << MMC0_PLL_SHIFT,
	MMC0_SEL_APLL		= 0,
	MMC0_SEL_GPLL,
	MMC0_SEL_GPLL_DIV2,
	MMC0_SEL_24M,
	MMC0_DIV_SHIFT		= 0,
	MMC0_DIV_MASK		= 0x3f << MMC0_DIV_SHIFT,

	/* CRU_CLKSEL12_CON */
	EMMC_PLL_SHIFT		= 14,
	EMMC_PLL_MASK		= 3 << EMMC_PLL_SHIFT,
	EMMC_SEL_APLL		= 0,
	EMMC_SEL_GPLL,
	EMMC_SEL_GPLL_DIV2,
	EMMC_SEL_24M,
	EMMC_DIV_SHIFT		= 8,
	EMMC_DIV_MASK		= 0x3f << EMMC_DIV_SHIFT,
	SDIO_PLL_SHIFT		= 6,
	SDIO_PLL_MASK		= 3 << SDIO_PLL_SHIFT,
	SDIO_SEL_APLL		= 0,
	SDIO_SEL_GPLL,
	SDIO_SEL_GPLL_DIV2,
	SDIO_SEL_24M,
	SDIO_DIV_SHIFT		= 0,
	SDIO_DIV_MASK		= 0x3f << SDIO_DIV_SHIFT,

	/* CLKSEL_CON24 */
	SARADC_DIV_CON_SHIFT	= 8,
	SARADC_DIV_CON_MASK	= GENMASK(15, 8),
	SARADC_DIV_CON_WIDTH	= 8,
	CLK_CRYPTO_DIV_CON_SHIFT= 0,
	CLK_CRYPTO_DIV_CON_MASK	= GENMASK(1, 0),

	/* CLKSEL_CON25 */
	SPI_PLL_SEL_SHIFT	= 8,
	SPI_PLL_SEL_MASK	= 0x3 << SPI_PLL_SEL_SHIFT,
	SPI_PLL_SEL_CPLL	= 0,
	SPI_PLL_SEL_GPLL,
	SPI_PLL_SEL_GPLL_DIV2,
	SPI_DIV_SHIFT		= 0,
	SPI_DIV_MASK		= 0x7f << SPI_DIV_SHIFT,

	/* CRU_CLKSEL27_CON*/
	DCLK_VOP_SEL_SHIFT	= 0,
	DCLK_VOP_SEL_MASK	= 1 << DCLK_VOP_SEL_SHIFT,
	DCLK_VOP_PLL_SEL_CPLL	= 0,
	DCLK_VOP_DIV_CON_SHIFT	= 8,
	DCLK_VOP_DIV_CON_MASK	= 0xff << DCLK_VOP_DIV_CON_SHIFT,

	/* CRU_CLKSEL31_CON */
	VIO0_PLL_SHIFT		= 5,
	VIO0_PLL_MASK		= 7 << VIO0_PLL_SHIFT,
	VI00_SEL_CPLL		= 0,
	VIO0_SEL_GPLL,
	VIO0_DIV_SHIFT		= 0,
	VIO0_DIV_MASK		= 0x1f << VIO0_DIV_SHIFT,
	VIO1_PLL_SHIFT		= 13,
	VIO1_PLL_MASK		= 7 << VIO1_PLL_SHIFT,
	VI01_SEL_CPLL		= 0,
	VIO1_SEL_GPLL,
	VIO1_DIV_SHIFT		= 8,
	VIO1_DIV_MASK		= 0x1f << VIO1_DIV_SHIFT,

	/* CRU_SOFTRST5_CON */
	DDRCTRL_PSRST_SHIFT	= 11,
	DDRCTRL_SRST_SHIFT	= 10,
	DDRPHY_PSRST_SHIFT	= 9,
	DDRPHY_SRST_SHIFT	= 8,
};
#endif
