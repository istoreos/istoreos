/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2022 Rockchip Electronics Co. Ltd.
 * Author: Elaine Zhang <zhangqing@rock-chips.com>
 */

#ifndef _ASM_ARCH_CRU_RV1106_H
#define _ASM_ARCH_CRU_RV1106_H

#include <common.h>

#define MHz		1000000
#define KHz		1000
#define OSC_HZ		(24 * MHz)

#define APLL_HZ		(816 * MHz)
#define GPLL_HZ		(1188 * MHz)
#define CPLL_HZ		(1000 * MHz)

/* RV1106 pll id */
enum rv1106_pll_id {
	APLL,
	DPLL,
	CPLL,
	GPLL,
	PLL_COUNT,
};

struct rv1106_clk_info {
	unsigned long id;
	char *name;
	bool is_cru;
};

struct rv1106_clk_priv {
	struct rv1106_cru *cru;
	struct rv1106_grf *grf;
	ulong gpll_hz;
	ulong cpll_hz;
	ulong armclk_hz;
	ulong armclk_enter_hz;
	ulong armclk_init_hz;
	bool sync_kernel;
	bool set_armclk_rate;
};

struct rv1106_grf_clk_priv {
	struct rv1106_grf *grf;
};

struct rv1106_pll {
	unsigned int con0;
	unsigned int con1;
	unsigned int con2;
	unsigned int con3;
	unsigned int con4;
	unsigned int reserved0[3];
};

struct rv1106_cru {
	unsigned int reserved0[192];
	unsigned int pmu_clksel_con[8];
	unsigned int reserved1[312];
	unsigned int pmu_clkgate_con[3];
	unsigned int reserved2[125];
	unsigned int pmu_softrst_con[3];
	unsigned int reserved3[15741];
	struct rv1106_pll pll[4];
	unsigned int reserved4[128];
	unsigned int mode;
	unsigned int reserved5[31];
	unsigned int clksel_con[34];
	unsigned int reserved6[286];
	unsigned int clkgate_con[4];
	unsigned int reserved7[124];
	unsigned int softrst_con[3];
	unsigned int reserved8[125];
	unsigned int glb_cnt_th;
	unsigned int glb_rst_st;
	unsigned int glb_srst_fst;
	unsigned int glb_srst_snd;
	unsigned int glb_rst_con;
	unsigned int con[2];
	unsigned int sdmmc_con[2];
	unsigned int emmc_con[2];
	unsigned int reserved9[1461];
	unsigned int peri_clksel_con[12];
	unsigned int reserved10[308];
	unsigned int peri_clkgate_con[8];
	unsigned int reserved11[120];
	unsigned int peri_softrst_con[8];
	unsigned int reserved12[1592];
	unsigned int vi_clksel_con[4];
	unsigned int reserved13[316];
	unsigned int vi_clkgate_con[3];
	unsigned int reserved14[125];
	unsigned int vi_softrst_con[3];
	unsigned int reserved15[3645];
	unsigned int core_clksel_con[5];
	unsigned int reserved16[2043];
	unsigned int vepu_clksel_con[2];
	unsigned int reserved17[318];
	unsigned int vepu_clkgate_con[3];
	unsigned int reserved18[125];
	unsigned int vepu_softrst_con[2];
	unsigned int reserved19[1598];
	unsigned int vo_clksel_con[4];
	unsigned int reserved20[316];
	unsigned int vo_clkgate_con[3];
	unsigned int reserved21[125];
	unsigned int vo_softrst_con[4];
};
check_member(rv1106_cru, vo_softrst_con[0], 0x1ca00);

struct pll_rate_table {
	unsigned long rate;
	unsigned int fbdiv;
	unsigned int postdiv1;
	unsigned int refdiv;
	unsigned int postdiv2;
	unsigned int dsmpd;
	unsigned int frac;
};

#define RV1106_TOPCRU_BASE		0x10000
#define RV1106_SUBDDRCRU_BASE		0x1F000

#define RV1106_PLL_CON(x)		((x) * 0x4 + RV1106_TOPCRU_BASE)
#define RV1106_MODE_CON			(0x280 + RV1106_TOPCRU_BASE)
#define RV1106_SUBDDRMODE_CON		(0x280 + RV1106_SUBDDRCRU_BASE)

enum {
	/* CRU_PMU_CLK_SEL0_CON */
	CLK_I2C1_SEL_SHIFT		= 6,
	CLK_I2C1_SEL_MASK		= 0x3 << CLK_I2C1_SEL_SHIFT,
	CLK_I2C1_SEL_200M		= 0,
	CLK_I2C1_SEL_100M,
	CLK_I2C1_SEL_24M,
	CLK_I2C1_SEL_32K,
	HCLK_PMU_SEL_SHIFT		= 4,
	HCLK_PMU_SEL_MASK		= 0x3 << HCLK_PMU_SEL_SHIFT,
	HCLK_PMU_SEL_200M		= 0,
	HCLK_PMU_SEL_100M,
	HCLK_PMU_SEL_24M,
	PCLK_PMU_SEL_SHIFT		= 3,
	PCLK_PMU_SEL_MASK		= 0x1 << PCLK_PMU_SEL_SHIFT,
	PCLK_PMU_SEL_100M		= 0,
	PCLK_PMU_SEL_24M,

	/* CRU_CLK_SEL5_CON */
	CLK_UART_SRC_SEL_SHIFT		= 5,
	CLK_UART_SRC_SEL_MASK		= 0x1 << CLK_UART_SRC_SEL_SHIFT,
	CLK_UART_SRC_SEL_GPLL		= 0,
	CLK_UART_SRC_SEL_CPLL,
	CLK_UART_SRC_DIV_SHIFT		= 0,
	CLK_UART_SRC_DIV_MASK		= 0x1f << CLK_UART_SRC_DIV_SHIFT,

	/* CRU_CLK_SEL6_CON */
	CLK_UART_FRAC_NUMERATOR_SHIFT	= 16,
	CLK_UART_FRAC_NUMERATOR_MASK	= 0xffff << 16,
	CLK_UART_FRAC_DENOMINATOR_SHIFT	= 0,
	CLK_UART_FRAC_DENOMINATOR_MASK	= 0xffff,

	/* CRU_CLK_SEL7_CON */
	CLK_UART_SEL_SHIFT		= 0,
	CLK_UART_SEL_MASK		= 0x3 << CLK_UART_SEL_SHIFT,
	CLK_UART_SEL_SRC		= 0,
	CLK_UART_SEL_FRAC,
	CLK_UART_SEL_XIN24M,

	/* CRU_CLK_SEL23_CON */
	DCLK_VOP_SEL_SHIFT		= 8,
	DCLK_VOP_SEL_MASK		= 0x1 << DCLK_VOP_SEL_SHIFT,
	DCLK_VOP_SEL_GPLL		= 0,
	DCLK_VOP_SEL_CPLL,
	DCLK_VOP_DIV_SHIFT		= 3,
	DCLK_VOP_DIV_MASK		= 0x1f << DCLK_VOP_DIV_SHIFT,

	/* CRU_CLK_SEL24_CON */
	PCLK_TOP_SEL_SHIFT		= 5,
	PCLK_TOP_SEL_MASK		= 0x3 << PCLK_TOP_SEL_SHIFT,
	PCLK_TOP_SEL_100M		= 0,
	PCLK_TOP_SEL_50M,
	PCLK_TOP_SEL_24M,

	/* CRU_PERI_CLK_SEL1_CON */
	CLK_I2C3_SEL_SHIFT		= 14,
	CLK_I2C3_SEL_MASK		= 0x3 << CLK_I2C3_SEL_SHIFT,
	CLK_I2C2_SEL_SHIFT		= 12,
	CLK_I2C2_SEL_MASK		= 0x3 << CLK_I2C2_SEL_SHIFT,
	CLK_I2C0_SEL_SHIFT		= 8,
	CLK_I2C0_SEL_MASK		= 0x3 << CLK_I2C0_SEL_SHIFT,
	CLK_I2C0_SEL_200M		= 0,
	CLK_I2C0_SEL_100M,
	CLK_I2C0_SEL_50M,
	CLK_I2C0_SEL_24M,
	HCLK_PERI_SEL_SHIFT		= 4,
	HCLK_PERI_SEL_MASK		= 0x3 << HCLK_PERI_SEL_SHIFT,
	HCLK_PERI_SEL_200M		= 0,
	HCLK_PERI_SEL_100M,
	HCLK_PERI_SEL_50M,
	HCLK_PERI_SEL_24M,
	ACLK_PERI_SEL_SHIFT		= 2,
	ACLK_PERI_SEL_MASK		= 0x3 << ACLK_PERI_SEL_SHIFT,
	ACLK_PERI_SEL_400M		= 0,
	ACLK_PERI_SEL_200M,
	ACLK_PERI_SEL_100M,
	ACLK_PERI_SEL_24M,
	PCLK_PERI_SEL_SHIFT		= 0,
	PCLK_PERI_SEL_MASK		= 0x3 << PCLK_PERI_SEL_SHIFT,
	PCLK_PERI_SEL_100M		= 0,
	PCLK_PERI_SEL_50M,
	PCLK_PERI_SEL_24M,

	/* CRU_PERI_CLK_SEL2_CON */
	CLK_I2C4_SEL_SHIFT		= 0,
	CLK_I2C4_SEL_MASK		= 0x3 << CLK_I2C4_SEL_SHIFT,

	/* CRU_PERI_CLK_SEL6_CON */
	CLK_PWM2_SEL_SHIFT		= 11,
	CLK_PWM2_SEL_MASK		= 0x3 << CLK_PWM2_SEL_SHIFT,
	CLK_PWM1_SEL_SHIFT		= 9,
	CLK_PWM1_SEL_MASK		= 0x3 << CLK_PWM1_SEL_SHIFT,
	CLK_PWM_SEL_100M		= 0,
	CLK_PWM_SEL_50M,
	CLK_PWM_SEL_24M,
	CLK_PKA_CRYPTO_SEL_SHIFT	= 7,
	CLK_PKA_CRYPTO_SEL_MASK		= 0x3 << CLK_PKA_CRYPTO_SEL_SHIFT,
	CLK_CORE_CRYPTO_SEL_SHIFT	= 5,
	CLK_CORE_CRYPTO_SEL_MASK	= 0x3 << CLK_CORE_CRYPTO_SEL_SHIFT,
	CLK_CRYPTO_SEL_300M		= 0,
	CLK_CRYPTO_SEL_200M,
	CLK_CRYPTO_SEL_100M,
	CLK_CRYPTO_SEL_24M,
	CLK_SARADC_DIV_SHIFT		= 0,
	CLK_SARADC_DIV_MASK		= 0x7 << CLK_SARADC_DIV_SHIFT,
	CLK_SPI1_SEL_SHIFT		= 3,
	CLK_SPI1_SEL_MASK		= 0x3 << CLK_SPI1_SEL_SHIFT,

	/* CRU_PERI_CLK_SEL7_CON */
	CLK_SFC_SEL_SHIFT		= 12,
	CLK_SFC_SEL_MASK		= 0x3 << CLK_SFC_SEL_SHIFT,
	CLK_SFC_SEL_500M		= 0,
	CLK_SFC_SEL_300M,
	CLK_SFC_SEL_200M,
	CLK_SFC_SEL_24M,
	CLK_SFC_DIV_SHIFT		= 7,
	CLK_SFC_DIV_MASK		= 0x1f << CLK_SFC_DIV_SHIFT,
	CLK_EMMC_SEL_SHIFT		= 6,
	CLK_EMMC_SEL_MASK		= 0x1 << CLK_EMMC_SEL_SHIFT,
	CLK_MMC_SEL_400M		= 0,
	CLK_MMC_SEL_24M,
	CLK_EMMC_DIV_SHIFT		= 0,
	CLK_EMMC_DIV_MASK		= 0x3f << CLK_EMMC_DIV_SHIFT,

	/* CRU_PERI_CLK_SEL9_CON */
	ACLK_BUS_SEL_SHIFT		= 0,
	ACLK_BUS_SEL_MASK		= 0x3 << ACLK_BUS_SEL_SHIFT,
	ACLK_BUS_SEL_300M		= 0,
	ACLK_BUS_SEL_200M,
	ACLK_BUS_SEL_100M,
	ACLK_BUS_SEL_24M,

	/* CRU_PERI_CLK_SEL11_CON */
	CLK_PWM0_SEL_SHIFT		= 0,
	CLK_PWM0_SEL_MASK		= 0x3 << CLK_PWM0_SEL_SHIFT,

	/* CRU_VEPU_CLK_SEL0_CON */
	CLK_SPI0_SEL_SHIFT		= 12,
	CLK_SPI0_SEL_MASK		= 0x3 << CLK_SPI0_SEL_SHIFT,
	CLK_SPI0_SEL_200M		= 0,
	CLK_SPI0_SEL_100M,
	CLK_SPI0_SEL_50M,
	CLK_SPI0_SEL_24M,

	/* CRU_CORE_CLK_SEL0_CON */
	CLK_CORE_DIV_SHIFT		= 0,
	CLK_CORE_DIV_MASK		= 0x1f << CLK_CORE_DIV_SHIFT,

	/* CRU_VI_CLK_SEL1_CON */
	CLK_SDMMC_SEL_SHIFT		= 14,
	CLK_SDMMC_SEL_MASK		= 0x1 << CLK_SDMMC_SEL_SHIFT,
	CLK_SDMMC_DIV_SHIFT		= 8,
	CLK_SDMMC_DIV_MASK		= 0x3f << CLK_SDMMC_DIV_SHIFT,

	/* CRU_VO_CLK_SEL1_CON */
	ACLK_VOP_SEL_SHIFT		= 10,
	ACLK_VOP_SEL_MASK		= 0x3 << ACLK_VOP_SEL_SHIFT,
	ACLK_VOP_SEL_300M		= 0,
	ACLK_VOP_SEL_200M,
	ACLK_VOP_SEL_100M,
	ACLK_VOP_SEL_24M,

	/* CRU_VO_CLK_SEL3_CON */
	CLK_TSADC_TSEN_DIV_SHIFT	= 5,
	CLK_TSADC_TSEN_DIV_MASK		= 0x1F << CLK_TSADC_TSEN_DIV_SHIFT,
	CLK_TSADC_DIV_SHIFT		= 0,
	CLK_TSADC_DIV_MASK		= 0x1F << CLK_TSADC_DIV_SHIFT,
};
#endif
