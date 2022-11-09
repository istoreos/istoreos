/*
 * (C) Copyright 2016 Heiko Stuebner <heiko@sntech.de>
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */
#ifndef _ASM_ARCH_CRU_RK3066_H
#define _ASM_ARCH_CRU_RK3066_H

#define OSC_HZ		(24 * 1000 * 1000)

#define APLL_HZ		(1416 * 1000000)
#define APLL_SAFE_HZ	(600 * 1000000)
#define GPLL_HZ		(594 * 1000000)
#define CPLL_HZ		(384 * 1000000)

/* The SRAM is clocked off aclk_cpu, so we want to max it out for boot speed */
#define CPU_ACLK_HZ	297000000
#define CPU_HCLK_HZ	148500000
#define CPU_PCLK_HZ	74250000
#define CPU_H2P_HZ	74250000

#define PERI_ACLK_HZ	148500000
#define PERI_HCLK_HZ	148500000
#define PERI_PCLK_HZ	74250000

/* Private data for the clock driver - used by rockchip_get_cru() */
struct rk3066_clk_priv {
	struct rk3066_grf *grf;
	struct rk3066_cru *cru;
	ulong rate;
	bool has_bwadj;
	ulong armclk_hz;
	ulong armclk_enter_hz;
	ulong armclk_init_hz;
	bool sync_kernel;
	bool set_armclk_rate;
};

struct rk3066_cru {
	struct rk3066_pll {
		u32 con0;
		u32 con1;
		u32 con2;
		u32 con3;
	} pll[4];
	u32 cru_mode_con;
	u32 cru_clksel_con[35];
	u32 cru_clkgate_con[10];
	u32 reserved1[2];
	u32 cru_glb_srst_fst_value;
	u32 cru_glb_srst_snd_value;
	u32 reserved2[2];
	u32 cru_softrst_con[9];
	u32 cru_misc_con;
	u32 reserved3[2];
	u32 cru_glb_cnt_th;
};
check_member(rk3066_cru, cru_glb_cnt_th, 0x0140);

struct rk3066_clk_info {
	unsigned long id;
	char *name;
	bool is_cru;
};

/* CRU_CLKSEL0_CON */
enum {
	/* a9_core_div: core = core_src / (a9_core_div + 1) */
	A9_CORE_DIV_SHIFT	= 9,
	A9_CORE_DIV_MASK	= 0x1f << A9_CORE_DIV_SHIFT,
	CORE_PLL_SHIFT		= 8,
	CORE_PLL_MASK		= 1 << CORE_PLL_SHIFT,
	CORE_PLL_SELECT_APLL	= 0,
	CORE_PLL_SELECT_GPLL,

	/* core peri div: core:core_peri = 2:1, 4:1, 8:1 or 16:1 */
	CORE_PERI_DIV_SHIFT	= 6,
	CORE_PERI_DIV_MASK	= 3 << CORE_PERI_DIV_SHIFT,

	/* aclk_cpu pll selection */
	CPU_ACLK_PLL_SHIFT	= 5,
	CPU_ACLK_PLL_MASK	= 1 << CPU_ACLK_PLL_SHIFT,
	CPU_ACLK_PLL_SELECT_APLL	= 0,
	CPU_ACLK_PLL_SELECT_GPLL,

	/* a9_cpu_div: aclk_cpu = cpu_src / (a9_cpu_div + 1) */
	A9_CPU_DIV_SHIFT	= 0,
	A9_CPU_DIV_MASK		= 0x1f << A9_CPU_DIV_SHIFT,
};

/* CRU_CLKSEL1_CON */
enum {
	/* ahb2apb_pclk_div: hclk_cpu:pclk_cpu = 1:1, 2:1 or 4:1 */
	AHB2APB_DIV_SHIFT	= 14,
	AHB2APB_DIV_MASK	= 3 << AHB2APB_DIV_SHIFT,

	/* cpu_pclk_div: aclk_cpu:pclk_cpu = 1:1, 2:1, 4:1 or 8:1 */
	CPU_PCLK_DIV_SHIFT	= 12,
	CPU_PCLK_DIV_MASK	= 3 << CPU_PCLK_DIV_SHIFT,

	/* cpu_hclk_div: aclk_cpu:hclk_cpu = 1:1, 2:1 or 4:1 */
	CPU_HCLK_DIV_SHIFT	= 8,
	CPU_HCLK_DIV_MASK	= 3 << CPU_HCLK_DIV_SHIFT,

	/* core_aclk_div: cire:aclk_core = 1:1, 2:1, 3:1, 4:1 or 8:1 */
	CORE_ACLK_DIV_SHIFT	= 3,
	CORE_ACLK_DIV_MASK	= 7 << CORE_ACLK_DIV_SHIFT,
};

/* CRU_CLKSEL10_CON */
enum {
	PERI_SEL_PLL_SHIFT	= 15,
	PERI_SEL_PLL_MASK	= 1 << PERI_SEL_PLL_SHIFT,
	PERI_SEL_CPLL		= 0,
	PERI_SEL_GPLL,

	/* peri pclk div: aclk_bus:pclk_bus = 1:1, 2:1, 4:1 or 8:1 */
	PERI_PCLK_DIV_SHIFT	= 12,
	PERI_PCLK_DIV_MASK	= 3 << PERI_PCLK_DIV_SHIFT,

	/* peripheral bus hclk div:aclk_bus: hclk_bus = 1:1, 2:1 or 4:1 */
	PERI_HCLK_DIV_SHIFT	= 8,
	PERI_HCLK_DIV_MASK	= 3 << PERI_HCLK_DIV_SHIFT,

	/* peri aclk div: aclk_peri = periph_src / (peri_aclk_div + 1) */
	PERI_ACLK_DIV_SHIFT	= 0,
	PERI_ACLK_DIV_MASK	= 0x1f << PERI_ACLK_DIV_SHIFT,
};
/* CRU_CLKSEL11_CON */
enum {
	MMC0_DIV_SHIFT		= 0,
	MMC0_DIV_MASK		= 0x3f << MMC0_DIV_SHIFT,
};

/* CRU_CLKSEL12_CON */
enum {
	UART_PLL_SHIFT		= 15,
	UART_PLL_MASK		= 1 << UART_PLL_SHIFT,
	UART_PLL_SELECT_GENERAL	= 0,
	UART_PLL_SELECT_CODEC,

	EMMC_DIV_SHIFT		= 8,
	EMMC_DIV_MASK		= 0x3f << EMMC_DIV_SHIFT,

	SDIO_DIV_SHIFT		= 0,
	SDIO_DIV_MASK		= 0x3f << SDIO_DIV_SHIFT,
};

/* CRU_CLKSEL25_CON */
enum {
	SPI1_DIV_SHIFT		= 8,
	SPI1_DIV_MASK		= 0x7f << SPI1_DIV_SHIFT,

	SPI0_DIV_SHIFT		= 0,
	SPI0_DIV_MASK		= 0x7f << SPI0_DIV_SHIFT,
};

/* CRU_MODE_CON */
enum {
	GPLL_MODE_SHIFT		= 12,
	GPLL_MODE_MASK		= 3 << GPLL_MODE_SHIFT,
	GPLL_MODE_SLOW		= 0,
	GPLL_MODE_NORMAL,
	GPLL_MODE_DEEP,

	CPLL_MODE_SHIFT		= 8,
	CPLL_MODE_MASK		= 3 << CPLL_MODE_SHIFT,
	CPLL_MODE_SLOW		= 0,
	CPLL_MODE_NORMAL,
	CPLL_MODE_DEEP,

	DPLL_MODE_SHIFT		= 4,
	DPLL_MODE_MASK		= 3 << DPLL_MODE_SHIFT,
	DPLL_MODE_SLOW		= 0,
	DPLL_MODE_NORMAL,
	DPLL_MODE_DEEP,

	APLL_MODE_SHIFT		= 0,
	APLL_MODE_MASK		= 3 << APLL_MODE_SHIFT,
	APLL_MODE_SLOW		= 0,
	APLL_MODE_NORMAL,
	APLL_MODE_DEEP,
};

/* CRU_APLL_CON0 */
enum {
	CLKR_SHIFT		= 8,
	CLKR_MASK		= 0x3f << CLKR_SHIFT,

	CLKOD_SHIFT		= 0,
	CLKOD_MASK		= 0x3f << CLKOD_SHIFT,
};

/* CRU_APLL_CON1 */
enum {
	CLKF_SHIFT		= 0,
	CLKF_MASK		= 0x1fff << CLKF_SHIFT,
};

#endif
