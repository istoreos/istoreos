// SPDX-License-Identifier: GPL-2.0
/*
 * (C) Copyright 2020 Rockchip Electronics Co., Ltd.
 */

#include <common.h>
#include <debug_uart.h>
#include <dm.h>
#include <ram.h>
#include <syscon.h>
#include <asm/io.h>
#include <asm/arch-rockchip/clock.h>
#include <asm/arch-rockchip/hardware.h>
#include <asm/arch-rockchip/rk_atags.h>
#include <asm/arch-rockchip/cru_rv1126.h>
#include <asm/arch-rockchip/grf_rv1126.h>
#include <asm/arch-rockchip/sdram_common.h>
#include <asm/arch-rockchip/sdram_rv1126.h>

/* define training flag */
#define CA_TRAINING			(0x1 << 0)
#define READ_GATE_TRAINING		(0x1 << 1)
#define WRITE_LEVELING			(0x1 << 2)
#define WRITE_TRAINING			(0x1 << 3)
#define READ_TRAINING			(0x1 << 4)
#define FULL_TRAINING			(0xff)

#define SKEW_RX_SIGNAL			(0)
#define SKEW_TX_SIGNAL			(1)
#define SKEW_CA_SIGNAL			(2)

#define DESKEW_MDF_ABS_VAL		(0)
#define DESKEW_MDF_DIFF_VAL		(1)

#ifdef CONFIG_TPL_BUILD
#ifndef CONFIG_TPL_TINY_FRAMEWORK
#error please defined CONFIG_TPL_TINY_FRAMEWORK for RV1126 !!!
#endif
#endif

#ifdef CONFIG_TPL_BUILD

struct dram_info {
	void __iomem *pctl;
	void __iomem *phy;
	struct rv1126_cru *cru;
	struct msch_regs *msch;
	struct rv1126_ddrgrf *ddrgrf;
	struct rv1126_grf *grf;
	struct ram_info info;
	struct rv1126_pmugrf *pmugrf;
	u32 sr_idle;
	u32 pd_idle;
};

#define GRF_BASE_ADDR			0xfe000000
#define PMU_GRF_BASE_ADDR		0xfe020000
#define DDR_GRF_BASE_ADDR		0xfe030000
#define BUS_SGRF_BASE_ADDR		0xfe0a0000
#define SERVER_MSCH_BASE_ADDR		0xfe800000
#define CRU_BASE_ADDR			0xff490000
#define DDR_PHY_BASE_ADDR		0xff4a0000
#define UPCTL2_BASE_ADDR		0xffa50000

#define SGRF_SOC_CON2			0x8
#define SGRF_SOC_CON12			0x30
#define SGRF_SOC_CON13			0x34

struct dram_info dram_info;

#if (CONFIG_ROCKCHIP_TPL_INIT_DRAM_TYPE == 3)
struct rv1126_sdram_params sdram_configs[] = {
	#include "sdram_inc/rv1126/sdram-rv1126-ddr3-detect-328.inc"
	#include "sdram_inc/rv1126/sdram-rv1126-ddr3-detect-396.inc"
	#include "sdram_inc/rv1126/sdram-rv1126-ddr3-detect-528.inc"
	#include "sdram_inc/rv1126/sdram-rv1126-ddr3-detect-664.inc"
	#include "sdram_inc/rv1126/sdram-rv1126-ddr3-detect-784.inc"
	#include "sdram_inc/rv1126/sdram-rv1126-ddr3-detect-924.inc"
	#include "sdram_inc/rv1126/sdram-rv1126-ddr3-detect-1056.inc"
};
#elif (CONFIG_ROCKCHIP_TPL_INIT_DRAM_TYPE == 0)
struct rv1126_sdram_params sdram_configs[] = {
	#include "sdram_inc/rv1126/sdram-rv1126-ddr4-detect-328.inc"
	#include "sdram_inc/rv1126/sdram-rv1126-ddr4-detect-396.inc"
	#include "sdram_inc/rv1126/sdram-rv1126-ddr4-detect-528.inc"
	#include "sdram_inc/rv1126/sdram-rv1126-ddr4-detect-664.inc"
	#include "sdram_inc/rv1126/sdram-rv1126-ddr4-detect-784.inc"
	#include "sdram_inc/rv1126/sdram-rv1126-ddr4-detect-924.inc"
	#include "sdram_inc/rv1126/sdram-rv1126-ddr4-detect-1056.inc"
};
#elif (CONFIG_ROCKCHIP_TPL_INIT_DRAM_TYPE == 6)
struct rv1126_sdram_params sdram_configs[] = {
	#include "sdram_inc/rv1126/sdram-rv1126-lpddr3-detect-328.inc"
	#include "sdram_inc/rv1126/sdram-rv1126-lpddr3-detect-396.inc"
	#include "sdram_inc/rv1126/sdram-rv1126-lpddr3-detect-528.inc"
	#include "sdram_inc/rv1126/sdram-rv1126-lpddr3-detect-664.inc"
	#include "sdram_inc/rv1126/sdram-rv1126-lpddr3-detect-784.inc"
	#include "sdram_inc/rv1126/sdram-rv1126-lpddr3-detect-924.inc"
	#include "sdram_inc/rv1126/sdram-rv1126-lpddr3-detect-1056.inc"
};
#elif (CONFIG_ROCKCHIP_TPL_INIT_DRAM_TYPE == 7)
struct rv1126_sdram_params sdram_configs[] = {
	#include "sdram_inc/rv1126/sdram-rv1126-lpddr4-detect-328.inc"
	#include "sdram_inc/rv1126/sdram-rv1126-lpddr4-detect-396.inc"
	#include "sdram_inc/rv1126/sdram-rv1126-lpddr4-detect-528.inc"
	#include "sdram_inc/rv1126/sdram-rv1126-lpddr4-detect-664.inc"
	#include "sdram_inc/rv1126/sdram-rv1126-lpddr4-detect-784.inc"
	#include "sdram_inc/rv1126/sdram-rv1126-lpddr4-detect-924.inc"
	#include "sdram_inc/rv1126/sdram-rv1126-lpddr4-detect-1056.inc"
};
#endif

u32 common_info[] = {
	#include "sdram_inc/rv1126/sdram-rv1126-loader_params.inc"
};

#if defined(CONFIG_CMD_DDR_TEST_TOOL)
static struct rw_trn_result rw_trn_result;
#endif

static struct rv1126_fsp_param fsp_param[MAX_IDX];

static u8 lp3_odt_value;

static s8 wrlvl_result[2][4];

/* DDR configuration 0-9 */
u16 ddr_cfg_2_rbc[] = {
	((0 << 8) | (3 << 5) | (0 << 4) | (1 << 3) | 3), /* 0 */
	((1 << 8) | (3 << 5) | (0 << 4) | (1 << 3) | 2), /* 1 */
	((1 << 8) | (2 << 5) | (0 << 4) | (1 << 3) | 3), /* 2 */
	((1 << 8) | (3 << 5) | (0 << 4) | (1 << 3) | 1), /* 3 */
	((0 << 8) | (2 << 5) | (0 << 4) | (1 << 3) | 4), /* 4 */
	((0 << 8) | (3 << 5) | (1 << 4) | (1 << 3) | 1), /* 5 */
	((0 << 8) | (3 << 5) | (1 << 4) | (1 << 3) | 2), /* 6 */
	((0 << 8) | (2 << 5) | (1 << 4) | (1 << 3) | 3), /* 7 */
	((1 << 8) | (3 << 5) | (0 << 4) | (0 << 3) | 2), /* 8 */
	((1 << 8) | (2 << 5) | (0 << 4) | (1 << 3) | 2) /* 9 */
};

/* DDR configuration 10-21 */
u8 ddr4_cfg_2_rbc[] = {
	((0 << 7) | (3 << 4) | (0 << 3) | (2 << 1) | 0), /* 10 */
	((1 << 7) | (2 << 4) | (0 << 3) | (2 << 1) | 0), /* 11 */
	((0 << 7) | (4 << 4) | (0 << 3) | (1 << 1) | 0), /* 12 */
	((1 << 7) | (3 << 4) | (0 << 3) | (1 << 1) | 0), /* 13 */
	((0 << 7) | (4 << 4) | (0 << 3) | (2 << 1) | 1), /* 14 */
	((1 << 7) | (3 << 4) | (0 << 3) | (2 << 1) | 1), /* 15 */
	((1 << 7) | (4 << 4) | (0 << 3) | (1 << 1) | 1), /* 16 */
	((0 << 7) | (2 << 4) | (1 << 3) | (2 << 1) | 0), /* 17 */
	((0 << 7) | (3 << 4) | (1 << 3) | (1 << 1) | 0), /* 18 */
	((0 << 7) | (3 << 4) | (1 << 3) | (2 << 1) | 1), /* 19 */
	((0 << 7) | (4 << 4) | (1 << 3) | (1 << 1) | 1), /* 20 */
	((1 << 7) | (4 << 4) | (0 << 3) | (0 << 1) | 0) /* 21 */
};

/* DDR configuration 22-28 */
u16 ddr_cfg_2_rbc_p2[] = {
	((1 << 8) | (3 << 5) | (0 << 4) | (1 << 3) | 0), /* 22 */
	((0 << 8) | (4 << 5) | (0 << 4) | (1 << 3) | 2), /* 23 */
	((1 << 8) | (3 << 5) | (0 << 4) | (0 << 3) | 3), /* 24 */
	((0 << 8) | (3 << 5) | (1 << 4) | (0 << 3) | 3), /* 25 */
	((0 << 8) | (4 << 5) | (1 << 4) | (0 << 3) | 2), /* 26 */
	((1 << 8) | (4 << 5) | (0 << 4) | (0 << 3) | 2), /* 27 */
	((0 << 8) | (4 << 5) | (0 << 4) | (0 << 3) | 3) /* 28 */
};

u8 d4_rbc_2_d3_rbc[][2] = {
	{10, 0},
	{11, 2},
	{12, 23},
	{13, 1},
	{14, 28},
	{15, 24},
	{16, 27},
	{17, 7},
	{18, 6},
	{19, 25},
	{20, 26},
	{21, 3}
};

u32 addrmap[29][9] = {
	{24, 0x00090909, 0x00000000, 0x00000000, 0x00001f00, 0x08080808,
		0x08080808, 0x00000f0f, 0x3f3f}, /* 0 */
	{23, 0x00080808, 0x00000000, 0x00000000, 0x00001f1f, 0x07070707,
		0x07070707, 0x00000f0f, 0x3f3f}, /* 1 */
	{23, 0x00090909, 0x00000000, 0x00000000, 0x00001f00, 0x08080808,
		0x0f080808, 0x00000f0f, 0x3f3f}, /* 2 */
	{22, 0x00070707, 0x00000000, 0x1f000000, 0x00001f1f, 0x06060606,
		0x06060606, 0x00000f0f, 0x3f3f}, /* 3 */
	{24, 0x000a0a0a, 0x00000000, 0x00000000, 0x00000000, 0x09090909,
		0x0f090909, 0x00000f0f, 0x3f3f}, /* 4 */
	{6, 0x00070707, 0x00000000, 0x1f000000, 0x00001f1f, 0x07070707,
		0x07070707, 0x00000f0f, 0x3f3f}, /* 5 */
	{7, 0x00080808, 0x00000000, 0x00000000, 0x00001f1f, 0x08080808,
		0x08080808, 0x00000f0f, 0x3f3f}, /* 6 */
	{8, 0x00090909, 0x00000000, 0x00000000, 0x00001f00, 0x09090909,
		0x0f090909, 0x00000f0f, 0x3f3f}, /* 7 */
	{22, 0x001f0808, 0x00000000, 0x00000000, 0x00001f1f, 0x06060606,
		0x06060606, 0x00000f0f, 0x3f3f}, /* 8 */
	{23, 0x00080808, 0x00000000, 0x00000000, 0x00001f1f, 0x07070707,
		0x0f070707, 0x00000f0f, 0x3f3f}, /* 9 */

	{24, 0x003f0a0a, 0x01010100, 0x01010101, 0x00001f1f, 0x08080808,
		0x08080808, 0x00000f0f, 0x0801}, /* 10 */
	{23, 0x003f0a0a, 0x01010100, 0x01010101, 0x00001f1f, 0x08080808,
		0x0f080808, 0x00000f0f, 0x0801}, /* 11 */
	{24, 0x003f0909, 0x00000007, 0x1f000000, 0x00001f1f, 0x07070707,
		0x07070707, 0x00000f07, 0x0700}, /* 12 */
	{23, 0x003f0909, 0x00000007, 0x1f000000, 0x00001f1f, 0x07070707,
		0x07070707, 0x00000f0f, 0x0700}, /* 13 */
	{24, 0x003f0909, 0x01010100, 0x01010101, 0x00001f1f, 0x07070707,
		0x07070707, 0x00000f07, 0x3f01}, /* 14 */
	{23, 0x003f0909, 0x01010100, 0x01010101, 0x00001f1f, 0x07070707,
		0x07070707, 0x00000f0f, 0x3f01}, /* 15 */
	{23, 0x003f0808, 0x00000007, 0x1f000000, 0x00001f1f, 0x06060606,
		0x06060606, 0x00000f06, 0x3f00}, /* 16 */
	{8, 0x003f0a0a, 0x01010100, 0x01010101, 0x00001f1f, 0x09090909,
		0x0f090909, 0x00000f0f, 0x0801}, /* 17 */
	{7, 0x003f0909, 0x00000007, 0x1f000000, 0x00001f1f, 0x08080808,
		0x08080808, 0x00000f0f, 0x0700}, /* 18 */
	{7, 0x003f0909, 0x01010100, 0x01010101, 0x00001f1f, 0x08080808,
		0x08080808, 0x00000f0f, 0x3f01}, /* 19 */

	{6, 0x003f0808, 0x00000007, 0x1f000000, 0x00001f1f, 0x07070707,
		0x07070707, 0x00000f07, 0x3f00}, /* 20 */
	{23, 0x003f0909, 0x00000006, 0x1f1f0000, 0x00001f1f, 0x06060606,
		0x06060606, 0x00000f06, 0x0600}, /* 21 */
	{21, 0x00060606, 0x00000000, 0x1f1f0000, 0x00001f1f, 0x05050505,
		0x05050505, 0x00000f0f, 0x3f3f}, /* 22 */

	{24, 0x00080808, 0x00000000, 0x00000000, 0x00001f1f, 0x07070707,
		0x07070707, 0x00000f07, 0x3f3f}, /* 23 */
	{23, 0x003f0909, 0x00000000, 0x00000000, 0x00001f00, 0x07070707,
		0x07070707, 0x00000f0f, 0x3f3f}, /* 24 */
	{7, 0x003f0909, 0x00000000, 0x00000000, 0x00001f00, 0x08080808,
		0x08080808, 0x00000f0f, 0x3f3f}, /* 25 */
	{6, 0x003f0808, 0x00000000, 0x00000000, 0x00001f1f, 0x07070707,
		0x07070707, 0x00000f07, 0x3f3f}, /* 26 */
	{23, 0x003f0808, 0x00000000, 0x00000000, 0x00001f1f, 0x06060606,
		0x06060606, 0x00000f06, 0x3f3f}, /* 27 */
	{24, 0x003f0909, 0x00000000, 0x00000000, 0x00001f00, 0x07070707,
		0x07070707, 0x00000f07, 0x3f3f} /* 28 */
};

static u8 dq_sel[22][3] = {
	{0x0, 0x17, 0x22},
	{0x1, 0x18, 0x23},
	{0x2, 0x19, 0x24},
	{0x3, 0x1a, 0x25},
	{0x4, 0x1b, 0x26},
	{0x5, 0x1c, 0x27},
	{0x6, 0x1d, 0x28},
	{0x7, 0x1e, 0x29},
	{0x8, 0x16, 0x21},
	{0x9, 0x1f, 0x2a},
	{0xa, 0x20, 0x2b},
	{0x10, 0x1, 0xc},
	{0x11, 0x2, 0xd},
	{0x12, 0x3, 0xe},
	{0x13, 0x4, 0xf},
	{0x14, 0x5, 0x10},
	{0x15, 0x6, 0x11},
	{0x16, 0x7, 0x12},
	{0x17, 0x8, 0x13},
	{0x18, 0x0, 0xb},
	{0x19, 0x9, 0x14},
	{0x1a, 0xa, 0x15}
};

static u16 grp_addr[4] = {
	ADD_GROUP_CS0_A,
	ADD_GROUP_CS0_B,
	ADD_GROUP_CS1_A,
	ADD_GROUP_CS1_B
};

static u8 wrlvl_result_offset[2][4] = {
	{0xa0 + 0x26, 0xa0 + 0x27, 0xd0 + 0x26, 0xd0 + 0x27},
	{0xa0 + 0x28, 0xa0 + 0x29, 0xd0 + 0x28, 0xd0 + 0x29},
};

static u16 dqs_dq_skew_adr[16] = {
	0x170 + 0,	/* SKEW_UPDATE_RX_CS0_DQS0 */
	0x170 + 0xb,	/* SKEW_UPDATE_RX_CS0_DQS1 */
	0x1d0 + 0,	/* SKEW_UPDATE_RX_CS0_DQS2 */
	0x1d0 + 0xb,	/* SKEW_UPDATE_RX_CS0_DQS3 */
	0x1a0 + 0,	/* SKEW_UPDATE_RX_CS1_DQS0 */
	0x1a0 + 0xb,	/* SKEW_UPDATE_RX_CS1_DQS1 */
	0x200 + 0,	/* SKEW_UPDATE_RX_CS1_DQS2 */
	0x200 + 0xb,	/* SKEW_UPDATE_RX_CS1_DQS3 */
	0x170 + 0x16,	/* SKEW_UPDATE_TX_CS0_DQS0 */
	0x170 + 0x21,	/* SKEW_UPDATE_TX_CS0_DQS1 */
	0x1d0 + 0x16,	/* SKEW_UPDATE_TX_CS0_DQS2 */
	0x1d0 + 0x21,	/* SKEW_UPDATE_TX_CS0_DQS3 */
	0x1a0 + 0x16,	/* SKEW_UPDATE_TX_CS1_DQS0 */
	0x1a0 + 0x21,	/* SKEW_UPDATE_TX_CS1_DQS1 */
	0x200 + 0x16,	/* SKEW_UPDATE_TX_CS1_DQS2 */
	0x200 + 0x21,	/* SKEW_UPDATE_TX_CS1_DQS3 */
};

static void rkclk_ddr_reset(struct dram_info *dram,
			    u32 ctl_srstn, u32 ctl_psrstn,
			    u32 phy_srstn, u32 phy_psrstn)
{
	writel(UPCTL2_SRSTN_REQ(ctl_srstn) | UPCTL2_PSRSTN_REQ(ctl_psrstn) |
	       UPCTL2_ASRSTN_REQ(ctl_srstn),
	       BUS_SGRF_BASE_ADDR + SGRF_SOC_CON13);

	writel(DDRPHY_SRSTN_REQ(phy_srstn) | DDRPHY_PSRSTN_REQ(phy_psrstn),
	       &dram->cru->softrst_con[12]);
}

static void rkclk_set_dpll(struct dram_info *dram, unsigned int hz)
{
	unsigned int refdiv, postdiv1, postdiv2, fbdiv;
	int delay = 1000;
	u32 mhz = hz / MHz;
	struct global_info *gbl_info;
	struct sdram_head_info_index_v2 *index =
		(struct sdram_head_info_index_v2 *)common_info;
	u32 ssmod_info;
	u32 dsmpd = 1;

	gbl_info = (struct global_info *)((void *)common_info +
		    index->global_index.offset * 4);
	ssmod_info = gbl_info->info_2t;
	refdiv = 1;
	if (mhz <= 100) {
		postdiv1 = 6;
		postdiv2 = 4;
	} else if (mhz <= 150) {
		postdiv1 = 4;
		postdiv2 = 4;
	} else if (mhz <= 200) {
		postdiv1 = 6;
		postdiv2 = 2;
	} else if (mhz <= 300) {
		postdiv1 = 4;
		postdiv2 = 2;
	} else if (mhz <= 400) {
		postdiv1 = 6;
		postdiv2 = 1;
	} else {
		postdiv1 = 4;
		postdiv2 = 1;
	}
	fbdiv = (mhz * refdiv * postdiv1 * postdiv2) / 24;

	writel(DPLL_MODE(CLOCK_FROM_XIN_OSC), &dram->cru->mode);

	writel(0x1f000000, &dram->cru->clksel_con[64]);
	writel(POSTDIV1(postdiv1) | FBDIV(fbdiv), &dram->cru->pll[1].con0);
	/* enable ssmod */
	if (PLL_SSMOD_SPREAD(ssmod_info)) {
		dsmpd = 0;
		clrsetbits_le32(&dram->cru->pll[1].con2,
				0xffffff << 0, 0x0 << 0);
		writel(SSMOD_SPREAD(PLL_SSMOD_SPREAD(ssmod_info)) |
		       SSMOD_DIVVAL(PLL_SSMOD_DIV(ssmod_info)) |
		       SSMOD_DOWNSPREAD(PLL_SSMOD_DOWNSPREAD(ssmod_info)) |
		       SSMOD_RESET(0) |
		       SSMOD_DIS_SSCG(0) |
		       SSMOD_BP(0),
		       &dram->cru->pll[1].con3);
	}
	writel(DSMPD(dsmpd) | POSTDIV2(postdiv2) | REFDIV(refdiv),
	       &dram->cru->pll[1].con1);

	while (delay > 0) {
		udelay(1);
		if (LOCK(readl(&dram->cru->pll[1].con1)))
			break;
		delay--;
	}

	writel(DPLL_MODE(CLOCK_FROM_PLL), &dram->cru->mode);
}

static void rkclk_configure_ddr(struct dram_info *dram,
				struct rv1126_sdram_params *sdram_params)
{
	/* for inno ddr phy need freq / 2 */
	rkclk_set_dpll(dram, sdram_params->base.ddr_freq * MHZ / 2);
}

static unsigned int
	calculate_ddrconfig(struct rv1126_sdram_params *sdram_params)
{
	struct sdram_cap_info *cap_info = &sdram_params->ch.cap_info;
	u32 cs, bw, die_bw, col, row, bank;
	u32 cs1_row;
	u32 i, tmp;
	u32 ddrconf = -1;
	u32 row_3_4;

	cs = cap_info->rank;
	bw = cap_info->bw;
	die_bw = cap_info->dbw;
	col = cap_info->col;
	row = cap_info->cs0_row;
	cs1_row = cap_info->cs1_row;
	bank = cap_info->bk;
	row_3_4 = cap_info->row_3_4;

	if (sdram_params->base.dramtype == DDR4) {
		if (cs == 2 && row == cs1_row && !row_3_4) {
			tmp = ((row - 13) << 4) | (1 << 3) | (bw << 1) |
			      die_bw;
			for (i = 17; i < 21; i++) {
				if (((tmp & 0xf) ==
				     (ddr4_cfg_2_rbc[i - 10] & 0xf)) &&
				    ((tmp & 0x70) <=
				     (ddr4_cfg_2_rbc[i - 10] & 0x70))) {
					ddrconf = i;
					goto out;
				}
			}
		}

		tmp = ((cs - 1) << 7) | ((row - 13) << 4) | (bw << 1) | die_bw;
		for (i = 10; i < 21; i++) {
			if (((tmp & 0xf) == (ddr4_cfg_2_rbc[i - 10] & 0xf)) &&
			    ((tmp & 0x70) <= (ddr4_cfg_2_rbc[i - 10] & 0x70)) &&
			    ((tmp & 0x80) <= (ddr4_cfg_2_rbc[i - 10] & 0x80))) {
				ddrconf = i;
				goto out;
			}
		}
	} else {
		if (cs == 2 && row == cs1_row && bank == 3) {
			for (i = 5; i < 8; i++) {
				if (((bw + col - 10) == (ddr_cfg_2_rbc[i] &
							 0x7)) &&
				    ((row - 13) << 5) <= (ddr_cfg_2_rbc[i] &
							  (0x7 << 5))) {
					ddrconf = i;
					goto out;
				}
			}
		}

		tmp = ((cs - 1) << 8) | ((row - 13) << 5) |
		      ((bw + col - 10) << 0);
		if (bank == 3)
			tmp |= (1 << 3);

		for (i = 0; i < 9; i++)
			if (((tmp & 0x1f) == (ddr_cfg_2_rbc[i] & 0x1f)) &&
			    ((tmp & (7 << 5)) <=
			     (ddr_cfg_2_rbc[i] & (7 << 5))) &&
			    ((tmp & (1 << 8)) <=
			     (ddr_cfg_2_rbc[i] & (1 << 8)))) {
				ddrconf = i;
				goto out;
			}

		for (i = 0; i < 7; i++)
			if (((tmp & 0x1f) == (ddr_cfg_2_rbc_p2[i] & 0x1f)) &&
			    ((tmp & (7 << 5)) <=
			     (ddr_cfg_2_rbc_p2[i] & (7 << 5))) &&
			    ((tmp & (1 << 8)) <=
			     (ddr_cfg_2_rbc_p2[i] & (1 << 8)))) {
				ddrconf = i + 22;
				goto out;
			}

		if (cs == 1 && bank == 3 && row <= 17 &&
		    (col + bw) == 12)
			ddrconf = 23;
	}

out:
	if (ddrconf > 28)
		printascii("calculate ddrconfig error\n");

	if (sdram_params->base.dramtype == DDR4) {
		for (i = 0; i < ARRAY_SIZE(d4_rbc_2_d3_rbc) ; i++) {
			if (ddrconf == d4_rbc_2_d3_rbc[i][0]) {
				if (ddrconf == 21 && row > 16)
					printascii("warn:ddrconf21 row > 16\n");
				else
					ddrconf = d4_rbc_2_d3_rbc[i][1];
				break;
			}
		}
	}

	return ddrconf;
}

static void sw_set_req(struct dram_info *dram)
{
	void __iomem *pctl_base = dram->pctl;

	/* clear sw_done=0 */
	writel(PCTL2_SW_DONE_CLEAR, pctl_base + DDR_PCTL2_SWCTL);
}

static void sw_set_ack(struct dram_info *dram)
{
	void __iomem *pctl_base = dram->pctl;

	/* set sw_done=1 */
	writel(PCTL2_SW_DONE, pctl_base + DDR_PCTL2_SWCTL);
	while (1) {
		/* wait programming done */
		if (readl(pctl_base + DDR_PCTL2_SWSTAT) &
				PCTL2_SW_DONE_ACK)
			break;
	}
}

static void set_ctl_address_map(struct dram_info *dram,
				struct rv1126_sdram_params *sdram_params)
{
	struct sdram_cap_info *cap_info = &sdram_params->ch.cap_info;
	void __iomem *pctl_base = dram->pctl;
	u32 ddrconf = cap_info->ddrconfig;
	u32 i, row;

	row = cap_info->cs0_row;
	if (sdram_params->base.dramtype == DDR4) {
		for (i = 0; i < ARRAY_SIZE(d4_rbc_2_d3_rbc) ; i++) {
			if (ddrconf == d4_rbc_2_d3_rbc[i][1]) {
				ddrconf = d4_rbc_2_d3_rbc[i][0];
				break;
			}
		}
	}

	if (ddrconf >= ARRAY_SIZE(addrmap)) {
		printascii("set ctl address map fail\n");
		return;
	}

	sdram_copy_to_reg((u32 *)(pctl_base + DDR_PCTL2_ADDRMAP0),
			  &addrmap[ddrconf][0], ARRAY_SIZE(addrmap[ddrconf]) * 4);

	/* unused row set to 0xf */
	for (i = 17; i >= row; i--)
		setbits_le32(pctl_base + DDR_PCTL2_ADDRMAP6 +
			((i - 12) * 8 / 32) * 4,
			0xf << ((i - 12) * 8 % 32));

	if (sdram_params->base.dramtype == LPDDR3 && cap_info->row_3_4)
		setbits_le32(pctl_base + DDR_PCTL2_ADDRMAP6, 1 << 31);
	if (sdram_params->base.dramtype == DDR4 && cap_info->bw == 0x1)
		setbits_le32(pctl_base + DDR_PCTL2_PCCFG, 1 << 8);

	if (cap_info->rank == 1)
		clrsetbits_le32(pctl_base + DDR_PCTL2_ADDRMAP0, 0x1f, 0x1f);
}

static void phy_pll_set(struct dram_info *dram, u32 freq, u32 wait)
{
	void __iomem *phy_base = dram->phy;
	u32 fbdiv, prediv, postdiv, postdiv_en;

	if (wait) {
		clrbits_le32(PHY_REG(phy_base, 0x53), PHY_PD_DISB);
		while (!(readl(PHY_REG(phy_base, 0x90)) & PHY_PLL_LOCK))
			continue;
	} else {
		freq /= MHz;
		prediv = 1;
		if (freq <= 200) {
			fbdiv = 16;
			postdiv = 2;
			postdiv_en = 1;
		} else if (freq <= 456) {
			fbdiv = 8;
			postdiv = 1;
			postdiv_en = 1;
		} else {
			fbdiv = 4;
			postdiv = 0;
			postdiv_en = 0;
		}
		writel(fbdiv & 0xff, PHY_REG(phy_base, 0x50));
		clrsetbits_le32(PHY_REG(phy_base, 0x51), PHY_PBDIV_BIT9_MASK,
				(fbdiv >> 8) & 1);
		clrsetbits_le32(PHY_REG(phy_base, 0x51), PHY_POSTDIV_EN_MASK,
				postdiv_en << PHY_POSTDIV_EN_SHIFT);

		clrsetbits_le32(PHY_REG(phy_base, 0x52),
				PHY_PREDIV_MASK << PHY_PREDIV_SHIFT, prediv);
		clrsetbits_le32(PHY_REG(phy_base, 0x53),
				PHY_POSTDIV_MASK << PHY_POSTDIV_SHIFT,
				postdiv << PHY_POSTDIV_SHIFT);
	}
}

static const u16 d3_phy_drv_2_ohm[][2] = {
	{PHY_DDR3_RON_455ohm, 455},
	{PHY_DDR3_RON_230ohm, 230},
	{PHY_DDR3_RON_153ohm, 153},
	{PHY_DDR3_RON_115ohm, 115},
	{PHY_DDR3_RON_91ohm, 91},
	{PHY_DDR3_RON_76ohm, 76},
	{PHY_DDR3_RON_65ohm, 65},
	{PHY_DDR3_RON_57ohm, 57},
	{PHY_DDR3_RON_51ohm, 51},
	{PHY_DDR3_RON_46ohm, 46},
	{PHY_DDR3_RON_41ohm, 41},
	{PHY_DDR3_RON_38ohm, 38},
	{PHY_DDR3_RON_35ohm, 35},
	{PHY_DDR3_RON_32ohm, 32},
	{PHY_DDR3_RON_30ohm, 30},
	{PHY_DDR3_RON_28ohm, 28},
	{PHY_DDR3_RON_27ohm, 27},
	{PHY_DDR3_RON_25ohm, 25},
	{PHY_DDR3_RON_24ohm, 24},
	{PHY_DDR3_RON_23ohm, 23},
	{PHY_DDR3_RON_22ohm, 22},
	{PHY_DDR3_RON_21ohm, 21},
	{PHY_DDR3_RON_20ohm, 20}
};

static u16 d3_phy_odt_2_ohm[][2] = {
	{PHY_DDR3_RTT_DISABLE, 0},
	{PHY_DDR3_RTT_561ohm, 561},
	{PHY_DDR3_RTT_282ohm, 282},
	{PHY_DDR3_RTT_188ohm, 188},
	{PHY_DDR3_RTT_141ohm, 141},
	{PHY_DDR3_RTT_113ohm, 113},
	{PHY_DDR3_RTT_94ohm, 94},
	{PHY_DDR3_RTT_81ohm, 81},
	{PHY_DDR3_RTT_72ohm, 72},
	{PHY_DDR3_RTT_64ohm, 64},
	{PHY_DDR3_RTT_58ohm, 58},
	{PHY_DDR3_RTT_52ohm, 52},
	{PHY_DDR3_RTT_48ohm, 48},
	{PHY_DDR3_RTT_44ohm, 44},
	{PHY_DDR3_RTT_41ohm, 41},
	{PHY_DDR3_RTT_38ohm, 38},
	{PHY_DDR3_RTT_37ohm, 37},
	{PHY_DDR3_RTT_34ohm, 34},
	{PHY_DDR3_RTT_32ohm, 32},
	{PHY_DDR3_RTT_31ohm, 31},
	{PHY_DDR3_RTT_29ohm, 29},
	{PHY_DDR3_RTT_28ohm, 28},
	{PHY_DDR3_RTT_27ohm, 27},
	{PHY_DDR3_RTT_25ohm, 25}
};

static u16 d4lp3_phy_drv_2_ohm[][2] = {
	{PHY_DDR4_LPDDR3_RON_482ohm, 482},
	{PHY_DDR4_LPDDR3_RON_244ohm, 244},
	{PHY_DDR4_LPDDR3_RON_162ohm, 162},
	{PHY_DDR4_LPDDR3_RON_122ohm, 122},
	{PHY_DDR4_LPDDR3_RON_97ohm, 97},
	{PHY_DDR4_LPDDR3_RON_81ohm, 81},
	{PHY_DDR4_LPDDR3_RON_69ohm, 69},
	{PHY_DDR4_LPDDR3_RON_61ohm, 61},
	{PHY_DDR4_LPDDR3_RON_54ohm, 54},
	{PHY_DDR4_LPDDR3_RON_48ohm, 48},
	{PHY_DDR4_LPDDR3_RON_44ohm, 44},
	{PHY_DDR4_LPDDR3_RON_40ohm, 40},
	{PHY_DDR4_LPDDR3_RON_37ohm, 37},
	{PHY_DDR4_LPDDR3_RON_34ohm, 34},
	{PHY_DDR4_LPDDR3_RON_32ohm, 32},
	{PHY_DDR4_LPDDR3_RON_30ohm, 30},
	{PHY_DDR4_LPDDR3_RON_28ohm, 28},
	{PHY_DDR4_LPDDR3_RON_27ohm, 27},
	{PHY_DDR4_LPDDR3_RON_25ohm, 25},
	{PHY_DDR4_LPDDR3_RON_24ohm, 24},
	{PHY_DDR4_LPDDR3_RON_23ohm, 23},
	{PHY_DDR4_LPDDR3_RON_22ohm, 22},
	{PHY_DDR4_LPDDR3_RON_21ohm, 21}
};

static u16 d4lp3_phy_odt_2_ohm[][2] = {
	{PHY_DDR4_LPDDR3_RTT_DISABLE, 0},
	{PHY_DDR4_LPDDR3_RTT_586ohm, 586},
	{PHY_DDR4_LPDDR3_RTT_294ohm, 294},
	{PHY_DDR4_LPDDR3_RTT_196ohm, 196},
	{PHY_DDR4_LPDDR3_RTT_148ohm, 148},
	{PHY_DDR4_LPDDR3_RTT_118ohm, 118},
	{PHY_DDR4_LPDDR3_RTT_99ohm, 99},
	{PHY_DDR4_LPDDR3_RTT_85ohm, 58},
	{PHY_DDR4_LPDDR3_RTT_76ohm, 76},
	{PHY_DDR4_LPDDR3_RTT_67ohm, 67},
	{PHY_DDR4_LPDDR3_RTT_60ohm, 60},
	{PHY_DDR4_LPDDR3_RTT_55ohm, 55},
	{PHY_DDR4_LPDDR3_RTT_50ohm, 50},
	{PHY_DDR4_LPDDR3_RTT_46ohm, 46},
	{PHY_DDR4_LPDDR3_RTT_43ohm, 43},
	{PHY_DDR4_LPDDR3_RTT_40ohm, 40},
	{PHY_DDR4_LPDDR3_RTT_38ohm, 38},
	{PHY_DDR4_LPDDR3_RTT_36ohm, 36},
	{PHY_DDR4_LPDDR3_RTT_34ohm, 34},
	{PHY_DDR4_LPDDR3_RTT_32ohm, 32},
	{PHY_DDR4_LPDDR3_RTT_31ohm, 31},
	{PHY_DDR4_LPDDR3_RTT_29ohm, 29},
	{PHY_DDR4_LPDDR3_RTT_28ohm, 28},
	{PHY_DDR4_LPDDR3_RTT_27ohm, 27}
};

static u16 lp4_phy_drv_2_ohm[][2] = {
	{PHY_LPDDR4_RON_501ohm, 501},
	{PHY_LPDDR4_RON_253ohm, 253},
	{PHY_LPDDR4_RON_168ohm, 168},
	{PHY_LPDDR4_RON_126ohm, 126},
	{PHY_LPDDR4_RON_101ohm, 101},
	{PHY_LPDDR4_RON_84ohm, 84},
	{PHY_LPDDR4_RON_72ohm, 72},
	{PHY_LPDDR4_RON_63ohm, 63},
	{PHY_LPDDR4_RON_56ohm, 56},
	{PHY_LPDDR4_RON_50ohm, 50},
	{PHY_LPDDR4_RON_46ohm, 46},
	{PHY_LPDDR4_RON_42ohm, 42},
	{PHY_LPDDR4_RON_38ohm, 38},
	{PHY_LPDDR4_RON_36ohm, 36},
	{PHY_LPDDR4_RON_33ohm, 33},
	{PHY_LPDDR4_RON_31ohm, 31},
	{PHY_LPDDR4_RON_29ohm, 29},
	{PHY_LPDDR4_RON_28ohm, 28},
	{PHY_LPDDR4_RON_26ohm, 26},
	{PHY_LPDDR4_RON_25ohm, 25},
	{PHY_LPDDR4_RON_24ohm, 24},
	{PHY_LPDDR4_RON_23ohm, 23},
	{PHY_LPDDR4_RON_22ohm, 22}
};

static u16 lp4_phy_odt_2_ohm[][2] = {
	{PHY_LPDDR4_RTT_DISABLE, 0},
	{PHY_LPDDR4_RTT_604ohm, 604},
	{PHY_LPDDR4_RTT_303ohm, 303},
	{PHY_LPDDR4_RTT_202ohm, 202},
	{PHY_LPDDR4_RTT_152ohm, 152},
	{PHY_LPDDR4_RTT_122ohm, 122},
	{PHY_LPDDR4_RTT_101ohm, 101},
	{PHY_LPDDR4_RTT_87ohm,	87},
	{PHY_LPDDR4_RTT_78ohm, 78},
	{PHY_LPDDR4_RTT_69ohm, 69},
	{PHY_LPDDR4_RTT_62ohm, 62},
	{PHY_LPDDR4_RTT_56ohm, 56},
	{PHY_LPDDR4_RTT_52ohm, 52},
	{PHY_LPDDR4_RTT_48ohm, 48},
	{PHY_LPDDR4_RTT_44ohm, 44},
	{PHY_LPDDR4_RTT_41ohm, 41},
	{PHY_LPDDR4_RTT_39ohm, 39},
	{PHY_LPDDR4_RTT_37ohm, 37},
	{PHY_LPDDR4_RTT_35ohm, 35},
	{PHY_LPDDR4_RTT_33ohm, 33},
	{PHY_LPDDR4_RTT_32ohm, 32},
	{PHY_LPDDR4_RTT_30ohm, 30},
	{PHY_LPDDR4_RTT_29ohm, 29},
	{PHY_LPDDR4_RTT_27ohm, 27}
};

static u32 lp4_odt_calc(u32 odt_ohm)
{
	u32 odt;

	if (odt_ohm == 0)
		odt = LPDDR4_DQODT_DIS;
	else if (odt_ohm <= 40)
		odt = LPDDR4_DQODT_40;
	else if (odt_ohm <= 48)
		odt = LPDDR4_DQODT_48;
	else if (odt_ohm <= 60)
		odt = LPDDR4_DQODT_60;
	else if (odt_ohm <= 80)
		odt = LPDDR4_DQODT_80;
	else if (odt_ohm <= 120)
		odt = LPDDR4_DQODT_120;
	else
		odt = LPDDR4_DQODT_240;

	return odt;
}

static void *get_ddr_drv_odt_info(u32 dramtype)
{
	struct sdram_head_info_index_v2 *index =
		(struct sdram_head_info_index_v2 *)common_info;
	void *ddr_info = 0;

	if (dramtype == DDR4)
		ddr_info = (void *)common_info + index->ddr4_index.offset * 4;
	else if (dramtype == DDR3)
		ddr_info = (void *)common_info + index->ddr3_index.offset * 4;
	else if (dramtype == LPDDR3)
		ddr_info = (void *)common_info + index->lp3_index.offset * 4;
	else if (dramtype == LPDDR4)
		ddr_info = (void *)common_info + index->lp4_index.offset * 4;
	else if (dramtype == LPDDR4X)
		ddr_info = (void *)common_info + index->lp4x_index.offset * 4;
	else
		printascii("unsupported dram type\n");
	return ddr_info;
}

static void set_lp4_vref(struct dram_info *dram, struct lp4_info *lp4_info,
			 u32 freq_mhz, u32 dst_fsp, u32 dramtype)
{
	void __iomem *pctl_base = dram->pctl;
	u32 ca_vref, dq_vref;

	if (freq_mhz <= LP4_CA_ODT_EN_FREQ(lp4_info->ca_odten_freq))
		ca_vref = LP4_CA_VREF(lp4_info->vref_when_odtoff);
	else
		ca_vref = LP4_CA_VREF(lp4_info->vref_when_odten);

	if (freq_mhz <= LP4_DQ_ODT_EN_FREQ(lp4_info->dq_odten_freq))
		dq_vref = LP4_DQ_VREF(lp4_info->vref_when_odtoff);
	else
		dq_vref = LP4_DQ_VREF(lp4_info->vref_when_odten);

	if (dramtype == LPDDR4) {
		if (ca_vref < 100)
			ca_vref = 100;
		if (ca_vref > 420)
			ca_vref = 420;

		if (ca_vref <= 300)
			ca_vref = (0 << 6) | (ca_vref - 100) / 4;
		else
			ca_vref = (1 << 6) | (ca_vref - 220) / 4;

		if (dq_vref < 100)
			dq_vref = 100;
		if (dq_vref > 420)
			dq_vref = 420;

		if (dq_vref <= 300)
			dq_vref = (0 << 6) | (dq_vref - 100) / 4;
		else
			dq_vref = (1 << 6) | (dq_vref - 220) / 4;
	} else {
		ca_vref = ca_vref * 11 / 6;
		if (ca_vref < 150)
			ca_vref = 150;
		if (ca_vref > 629)
			ca_vref = 629;

		if (ca_vref <= 449)
			ca_vref = (0 << 6) | (ca_vref - 150) / 4;
		else
			ca_vref = (1 << 6) | (ca_vref - 329) / 4;

		if (dq_vref < 150)
			dq_vref = 150;
		if (dq_vref > 629)
			dq_vref = 629;

		if (dq_vref <= 449)
			dq_vref = (0 << 6) | (dq_vref - 150) / 6;
		else
			dq_vref = (1 << 6) | (dq_vref - 329) / 6;
	}
	sw_set_req(dram);
	clrsetbits_le32(pctl_base + UMCTL2_REGS_FREQ(dst_fsp) +
			DDR_PCTL2_INIT6,
			PCTL2_MR_MASK << PCTL2_LPDDR4_MR12_SHIFT,
			ca_vref << PCTL2_LPDDR4_MR12_SHIFT);

	clrsetbits_le32(pctl_base + UMCTL2_REGS_FREQ(dst_fsp) +
			DDR_PCTL2_INIT7,
			PCTL2_MR_MASK << PCTL2_LPDDR4_MR14_SHIFT,
			dq_vref << PCTL2_LPDDR4_MR14_SHIFT);
	sw_set_ack(dram);
}

static void set_ds_odt(struct dram_info *dram,
		       struct rv1126_sdram_params *sdram_params, u32 dst_fsp)
{
	void __iomem *phy_base = dram->phy;
	void __iomem *pctl_base = dram->pctl;
	u32 dramtype = sdram_params->base.dramtype;
	struct ddr2_3_4_lp2_3_info *ddr_info;
	struct lp4_info *lp4_info;
	u32 i, j, tmp;
	const u16 (*p_drv)[2];
	const u16 (*p_odt)[2];
	u32 drv_info, sr_info;
	u32 phy_dq_drv_ohm, phy_clk_drv_ohm, phy_ca_drv_ohm, dram_drv_ohm;
	u32 phy_odt_ohm, dram_odt_ohm;
	u32 lp4_pu_cal, phy_lp4_drv_pd_en;
	u32 phy_odt_up_en, phy_odt_dn_en;
	u32 sr_dq, sr_clk;
	u32 freq = sdram_params->base.ddr_freq;
	u32 mr1_mr3, mr11, mr22, vref_out, vref_inner;
	u32 phy_clk_drv = 0, phy_odt = 0, phy_ca_drv = 0, dram_caodt_ohm = 0;
	u32 phy_dq_drv = 0;
	u32 phy_odt_up = 0, phy_odt_dn = 0;

	ddr_info = get_ddr_drv_odt_info(dramtype);
	lp4_info = (void *)ddr_info;

	if (!ddr_info)
		return;

	/* dram odt en freq control phy drv, dram odt and phy sr */
	if (freq <= DRAMODT_EN_FREQ(ddr_info->odten_freq)) {
		drv_info = ddr_info->drv_when_odtoff;
		dram_odt_ohm = 0;
		sr_info = ddr_info->sr_when_odtoff;
		phy_lp4_drv_pd_en =
			PHY_LP4_DRV_PULLDOWN_EN_ODTOFF(lp4_info->odt_info);
	} else {
		drv_info = ddr_info->drv_when_odten;
		dram_odt_ohm = ODT_INFO_DRAM_ODT(ddr_info->odt_info);
		sr_info = ddr_info->sr_when_odten;
		phy_lp4_drv_pd_en =
			PHY_LP4_DRV_PULLDOWN_EN_ODTEN(lp4_info->odt_info);
	}
	phy_dq_drv_ohm =
		DRV_INFO_PHY_DQ_DRV(drv_info);
	phy_clk_drv_ohm =
		DRV_INFO_PHY_CLK_DRV(drv_info);
	phy_ca_drv_ohm =
		DRV_INFO_PHY_CA_DRV(drv_info);

	sr_dq = DQ_SR_INFO(sr_info);
	sr_clk = CLK_SR_INFO(sr_info);

	/* phy odt en freq control dram drv and phy odt */
	if (freq <= PHYODT_EN_FREQ(ddr_info->odten_freq)) {
		dram_drv_ohm = DRV_INFO_DRAM_DQ_DRV(ddr_info->drv_when_odtoff);
		lp4_pu_cal = LP4_DRV_PU_CAL_ODTOFF(lp4_info->odt_info);
		phy_odt_ohm = 0;
		phy_odt_up_en = 0;
		phy_odt_dn_en = 0;
	} else {
		dram_drv_ohm =
			DRV_INFO_DRAM_DQ_DRV(ddr_info->drv_when_odten);
		phy_odt_ohm = ODT_INFO_PHY_ODT(ddr_info->odt_info);
		phy_odt_up_en =
			ODT_INFO_PULLUP_EN(ddr_info->odt_info);
		phy_odt_dn_en =
			ODT_INFO_PULLDOWN_EN(ddr_info->odt_info);
		lp4_pu_cal = LP4_DRV_PU_CAL_ODTEN(lp4_info->odt_info);
	}

	if (dramtype == LPDDR4 || dramtype == LPDDR4X) {
		if (phy_odt_ohm) {
			phy_odt_up_en = 0;
			phy_odt_dn_en = 1;
		}
		if (freq <= LP4_CA_ODT_EN_FREQ(lp4_info->ca_odten_freq))
			dram_caodt_ohm = 0;
		else
			dram_caodt_ohm =
				ODT_INFO_LP4_CA_ODT(lp4_info->odt_info);
	}

	if (dramtype == DDR3) {
		p_drv = d3_phy_drv_2_ohm;
		p_odt = d3_phy_odt_2_ohm;
	} else if (dramtype == LPDDR4 || dramtype == LPDDR4X) {
		p_drv = lp4_phy_drv_2_ohm;
		p_odt = lp4_phy_odt_2_ohm;
	} else {
		p_drv = d4lp3_phy_drv_2_ohm;
		p_odt = d4lp3_phy_odt_2_ohm;
	}

	for (i = ARRAY_SIZE(d3_phy_drv_2_ohm) - 1; ; i--) {
		if (phy_dq_drv_ohm <= *(*(p_drv + i) + 1)) {
			phy_dq_drv = **(p_drv + i);
			break;
		}
		if (i == 0)
			break;
	}
	for (i = ARRAY_SIZE(d3_phy_drv_2_ohm) - 1; ; i--) {
		if (phy_clk_drv_ohm <= *(*(p_drv + i) + 1)) {
			phy_clk_drv = **(p_drv + i);
			break;
		}
		if (i == 0)
			break;
	}
	for (i = ARRAY_SIZE(d3_phy_drv_2_ohm) - 1; ; i--) {
		if (phy_ca_drv_ohm <= *(*(p_drv + i) + 1)) {
			phy_ca_drv = **(p_drv + i);
			break;
		}
		if (i == 0)
			break;
	}
	if (!phy_odt_ohm)
		phy_odt = 0;
	else
		for (i = ARRAY_SIZE(d4lp3_phy_odt_2_ohm) - 1; ; i--) {
			if (phy_odt_ohm <= *(*(p_odt + i) + 1)) {
				phy_odt = **(p_odt + i);
				break;
			}
			if (i == 0)
				break;
		}

	if (dramtype != LPDDR4 && dramtype != LPDDR4X) {
		if (!phy_odt_ohm || (phy_odt_up_en && phy_odt_dn_en))
			vref_inner = 0x80;
		else if (phy_odt_up_en)
			vref_inner = (2 * dram_drv_ohm + phy_odt_ohm) * 128 /
				     (dram_drv_ohm + phy_odt_ohm);
		else
			vref_inner = phy_odt_ohm * 128 /
				(phy_odt_ohm + dram_drv_ohm);

		if (dramtype != DDR3 && dram_odt_ohm)
			vref_out = (2 * phy_dq_drv_ohm + dram_odt_ohm) * 128 /
				   (phy_dq_drv_ohm + dram_odt_ohm);
		else
			vref_out = 0x80;
	} else {
		/* for lp4 and lp4x*/
		if (phy_odt_ohm)
			vref_inner =
				(PHY_LP4_DQ_VREF(lp4_info->vref_when_odten) *
				 256) / 1000;
		else
			vref_inner =
				(PHY_LP4_DQ_VREF(lp4_info->vref_when_odtoff) *
				 256) / 1000;

		vref_out = 0x80;
	}

	/* default ZQCALIB bypass mode */
	clrsetbits_le32(PHY_REG(phy_base, 0x100), 0x1f, phy_ca_drv);
	clrsetbits_le32(PHY_REG(phy_base, 0x101), 0x1f, phy_ca_drv);
	clrsetbits_le32(PHY_REG(phy_base, 0x102), 0x1f, phy_clk_drv);
	clrsetbits_le32(PHY_REG(phy_base, 0x103), 0x1f, phy_clk_drv);
	if (dramtype == LPDDR4 || dramtype == LPDDR4X) {
		clrsetbits_le32(PHY_REG(phy_base, 0x107), 0x1f, phy_clk_drv);
		clrsetbits_le32(PHY_REG(phy_base, 0x108), 0x1f, phy_clk_drv);
	} else {
		clrsetbits_le32(PHY_REG(phy_base, 0x107), 0x1f, phy_ca_drv);
		clrsetbits_le32(PHY_REG(phy_base, 0x108), 0x1f, phy_ca_drv);
	}
	/* clk / cmd slew rate */
	clrsetbits_le32(PHY_REG(phy_base, 0x106), 0x1f, sr_clk);

	phy_lp4_drv_pd_en = (~phy_lp4_drv_pd_en) & 1;
	if (phy_odt_up_en)
		phy_odt_up = phy_odt;
	if (phy_odt_dn_en)
		phy_odt_dn = phy_odt;

	for (i = 0; i < 4; i++) {
		j = 0x110 + i * 0x10;
		clrsetbits_le32(PHY_REG(phy_base, j + 1), 0x1f, phy_odt_up);
		clrsetbits_le32(PHY_REG(phy_base, j), 0x1f, phy_odt_dn);
		clrsetbits_le32(PHY_REG(phy_base, j + 2), 0x1f, phy_dq_drv);
		clrsetbits_le32(PHY_REG(phy_base, j + 3), 0x1f, phy_dq_drv);
		writel(vref_inner, PHY_REG(phy_base, 0x118 + i * 0x10));

		clrsetbits_le32(PHY_REG(phy_base, 0x114 + i * 0x10),
				1 << 3, phy_lp4_drv_pd_en << 3);
		if (dramtype == LPDDR4 || dramtype == LPDDR4X)
			clrbits_le32(PHY_REG(phy_base, 0x114 + i * 0x10), BIT(5));
		/* dq slew rate */
		clrsetbits_le32(PHY_REG(phy_base, 0x117 + i * 0x10),
				0x1f, sr_dq);
	}

	/* reg_rx_vref_value_update */
	setbits_le32(PHY_REG(phy_base, 0x71), 1 << 5);
	clrbits_le32(PHY_REG(phy_base, 0x71), 1 << 5);

	/* RAM VREF */
	writel(vref_out, PHY_REG(phy_base, 0x105));
	if (dramtype == LPDDR3)
		udelay(100);

	if (dramtype == LPDDR4 || dramtype == LPDDR4X)
		set_lp4_vref(dram, lp4_info, freq, dst_fsp, dramtype);

	if (dramtype == DDR3 || dramtype == DDR4) {
		mr1_mr3 = readl(pctl_base + UMCTL2_REGS_FREQ(dst_fsp) +
				DDR_PCTL2_INIT3);
		mr1_mr3 = mr1_mr3 >> PCTL2_DDR34_MR1_SHIFT & PCTL2_MR_MASK;
	} else {
		mr1_mr3 = readl(pctl_base + UMCTL2_REGS_FREQ(dst_fsp) +
				DDR_PCTL2_INIT4);
		mr1_mr3 = mr1_mr3 >> PCTL2_LPDDR234_MR3_SHIFT & PCTL2_MR_MASK;
	}

	if (dramtype == DDR3) {
		mr1_mr3 &= ~(DDR3_DS_MASK | DDR3_RTT_NOM_MASK);
		if (dram_drv_ohm == 34)
			mr1_mr3 |= DDR3_DS_34;

		if (dram_odt_ohm == 0)
			mr1_mr3 |= DDR3_RTT_NOM_DIS;
		else if (dram_odt_ohm <= 40)
			mr1_mr3 |= DDR3_RTT_NOM_40;
		else if (dram_odt_ohm <= 60)
			mr1_mr3 |= DDR3_RTT_NOM_60;
		else
			mr1_mr3 |= DDR3_RTT_NOM_120;

	} else if (dramtype == DDR4) {
		mr1_mr3 &= ~(DDR4_DS_MASK | DDR4_RTT_NOM_MASK);
		if (dram_drv_ohm == 48)
			mr1_mr3 |= DDR4_DS_48;

		if (dram_odt_ohm == 0)
			mr1_mr3 |= DDR4_RTT_NOM_DIS;
		else if (dram_odt_ohm <= 34)
			mr1_mr3 |= DDR4_RTT_NOM_34;
		else if (dram_odt_ohm <= 40)
			mr1_mr3 |= DDR4_RTT_NOM_40;
		else if (dram_odt_ohm <= 48)
			mr1_mr3 |= DDR4_RTT_NOM_48;
		else if (dram_odt_ohm <= 60)
			mr1_mr3 |= DDR4_RTT_NOM_60;
		else
			mr1_mr3 |= DDR4_RTT_NOM_120;

	} else if (dramtype == LPDDR3) {
		if (dram_drv_ohm <= 34)
			mr1_mr3 |= LPDDR3_DS_34;
		else if (dram_drv_ohm <= 40)
			mr1_mr3 |= LPDDR3_DS_40;
		else if (dram_drv_ohm <= 48)
			mr1_mr3 |= LPDDR3_DS_48;
		else if (dram_drv_ohm <= 60)
			mr1_mr3 |= LPDDR3_DS_60;
		else if (dram_drv_ohm <= 80)
			mr1_mr3 |= LPDDR3_DS_80;

		if (dram_odt_ohm == 0)
			lp3_odt_value = LPDDR3_ODT_DIS;
		else if (dram_odt_ohm <= 60)
			lp3_odt_value = LPDDR3_ODT_60;
		else if (dram_odt_ohm <= 120)
			lp3_odt_value = LPDDR3_ODT_120;
		else
			lp3_odt_value = LPDDR3_ODT_240;
	} else {/* for lpddr4 and lpddr4x */
		/* MR3 for lp4 PU-CAL and PDDS */
		mr1_mr3 &= ~(LPDDR4_PDDS_MASK | LPDDR4_PU_CAL_MASK);
		mr1_mr3 |= lp4_pu_cal;

		tmp = lp4_odt_calc(dram_drv_ohm);
		if (!tmp)
			tmp = LPDDR4_PDDS_240;
		mr1_mr3 |= (tmp << LPDDR4_PDDS_SHIFT);

		/* MR11 for lp4 ca odt, dq odt set */
		mr11 = readl(pctl_base + UMCTL2_REGS_FREQ(dst_fsp) +
			     DDR_PCTL2_INIT6);
		mr11 = mr11 >> PCTL2_LPDDR4_MR11_SHIFT & PCTL2_MR_MASK;

		mr11 &= ~(LPDDR4_DQODT_MASK | LPDDR4_CAODT_MASK);

		tmp = lp4_odt_calc(dram_odt_ohm);
		mr11 |= (tmp << LPDDR4_DQODT_SHIFT);

		tmp = lp4_odt_calc(dram_caodt_ohm);
		mr11 |= (tmp << LPDDR4_CAODT_SHIFT);
		sw_set_req(dram);
		clrsetbits_le32(pctl_base + UMCTL2_REGS_FREQ(dst_fsp) +
				DDR_PCTL2_INIT6,
				PCTL2_MR_MASK << PCTL2_LPDDR4_MR11_SHIFT,
				mr11 << PCTL2_LPDDR4_MR11_SHIFT);
		sw_set_ack(dram);

		/* MR22 for soc odt/odt-ck/odt-cs/odt-ca */
		mr22 = readl(pctl_base + UMCTL2_REGS_FREQ(dst_fsp) +
			     DDR_PCTL2_INIT7);
		mr22 = mr22 >> PCTL2_LPDDR4_MR22_SHIFT & PCTL2_MR_MASK;
		mr22 &= ~LPDDR4_SOC_ODT_MASK;

		tmp = lp4_odt_calc(phy_odt_ohm);
		mr22 |= tmp;
		mr22 = mr22 |
		       (LP4_ODTE_CK_EN(lp4_info->cs_drv_ca_odt_info) <<
			LPDDR4_ODTE_CK_SHIFT) |
		       (LP4_ODTE_CS_EN(lp4_info->cs_drv_ca_odt_info) <<
			LPDDR4_ODTE_CS_SHIFT) |
		       (LP4_ODTD_CA_EN(lp4_info->cs_drv_ca_odt_info) <<
			LPDDR4_ODTD_CA_SHIFT);

		sw_set_req(dram);
		clrsetbits_le32(pctl_base + UMCTL2_REGS_FREQ(dst_fsp) +
				DDR_PCTL2_INIT7,
				PCTL2_MR_MASK << PCTL2_LPDDR4_MR22_SHIFT,
				mr22 << PCTL2_LPDDR4_MR22_SHIFT);
		sw_set_ack(dram);
	}

	if (dramtype == DDR4 || dramtype == DDR3) {
		sw_set_req(dram);
		clrsetbits_le32(pctl_base + UMCTL2_REGS_FREQ(dst_fsp) +
				DDR_PCTL2_INIT3,
				PCTL2_MR_MASK << PCTL2_DDR34_MR1_SHIFT,
				mr1_mr3 << PCTL2_DDR34_MR1_SHIFT);
		sw_set_ack(dram);
	} else {
		sw_set_req(dram);
		clrsetbits_le32(pctl_base + UMCTL2_REGS_FREQ(dst_fsp) +
				DDR_PCTL2_INIT4,
				PCTL2_MR_MASK << PCTL2_LPDDR234_MR3_SHIFT,
				mr1_mr3 << PCTL2_LPDDR234_MR3_SHIFT);
		sw_set_ack(dram);
	}
}

static int sdram_cmd_dq_path_remap(struct dram_info *dram,
				   struct rv1126_sdram_params *sdram_params)
{
	void __iomem *phy_base = dram->phy;
	u32 dramtype = sdram_params->base.dramtype;
	struct sdram_head_info_index_v2 *index =
		(struct sdram_head_info_index_v2 *)common_info;
	struct dq_map_info *map_info;

	map_info = (struct dq_map_info *)((void *)common_info +
		index->dq_map_index.offset * 4);

	if (dramtype == LPDDR4X)
		dramtype = LPDDR4;

	if (dramtype <= LPDDR4)
		writel((map_info->byte_map[dramtype / 4] >>
			((dramtype % 4) * 8)) & 0xff,
		       PHY_REG(phy_base, 0x4f));

	return 0;
}

static void phy_cfg(struct dram_info *dram,
		    struct rv1126_sdram_params *sdram_params)
{
	struct sdram_cap_info *cap_info = &sdram_params->ch.cap_info;
	void __iomem *phy_base = dram->phy;
	u32 i, dq_map, tmp;
	u32 byte1 = 0, byte0 = 0;

	sdram_cmd_dq_path_remap(dram, sdram_params);

	phy_pll_set(dram, sdram_params->base.ddr_freq * MHZ, 0);
	for (i = 0; sdram_params->phy_regs.phy[i][0] != 0xFFFFFFFF; i++) {
		writel(sdram_params->phy_regs.phy[i][1],
		       phy_base + sdram_params->phy_regs.phy[i][0]);
	}

	clrbits_le32(PHY_REG(phy_base, 0x62), BIT(5));
	dq_map = readl(PHY_REG(phy_base, 0x4f));
	for (i = 0; i < 4; i++) {
		if (((dq_map >> (i * 2)) & 0x3) == 0)
			byte0 = i;
		if (((dq_map >> (i * 2)) & 0x3) == 1)
			byte1 = i;
	}

	tmp = readl(PHY_REG(phy_base, 0xf)) & (~PHY_DQ_WIDTH_MASK);
	if (cap_info->bw == 2)
		tmp |= 0xf;
	else if (cap_info->bw == 1)
		tmp |= ((1 << byte0) | (1 << byte1));
	else
		tmp |= (1 << byte0);

	writel(tmp, PHY_REG(phy_base, 0xf));

	/* lpddr4 odt control by phy, enable cs0 odt */
	if (sdram_params->base.dramtype == LPDDR4 ||
	    sdram_params->base.dramtype == LPDDR4X)
		clrsetbits_le32(PHY_REG(phy_base, 0x20), 0x7 << 4,
				(1 << 6) | (1 << 4));
	/* for ca training ca vref choose range1 */
	setbits_le32(PHY_REG(phy_base, 0x1e), BIT(6));
	setbits_le32(PHY_REG(phy_base, 0x1f), BIT(6));
	/* for wr training PHY_0x7c[5], choose range0 */
	clrbits_le32(PHY_REG(phy_base, 0x7c), BIT(5));
}

static int update_refresh_reg(struct dram_info *dram)
{
	void __iomem *pctl_base = dram->pctl;
	u32 ret;

	ret = readl(pctl_base + DDR_PCTL2_RFSHCTL3) ^ (1 << 1);
	writel(ret, pctl_base + DDR_PCTL2_RFSHCTL3);

	return 0;
}

/*
 * rank = 1: cs0
 * rank = 2: cs1
 */
int read_mr(struct dram_info *dram, u32 rank, u32 mr_num, u32 dramtype)
{
	u32 ret;
	u32 i, temp;
	u32 dqmap;

	void __iomem *pctl_base = dram->pctl;
	struct sdram_head_info_index_v2 *index =
		(struct sdram_head_info_index_v2 *)common_info;
	struct dq_map_info *map_info;

	map_info = (struct dq_map_info *)((void *)common_info +
		index->dq_map_index.offset * 4);

	if (dramtype == LPDDR2)
		dqmap = map_info->lp2_dq0_7_map;
	else
		dqmap = map_info->lp3_dq0_7_map;

	pctl_read_mr(pctl_base, rank, mr_num);

	ret = (readl(&dram->ddrgrf->ddr_grf_status[0]) & 0xff);

	if (dramtype != LPDDR4) {
		temp = 0;
		for (i = 0; i < 8; i++) {
			temp = temp | (((ret >> i) & 0x1) <<
				       ((dqmap >> (i * 4)) & 0xf));
		}
	} else {
		temp = (readl(&dram->ddrgrf->ddr_grf_status[1]) & 0xff);
	}

	return temp;
}

/* before call this function autorefresh should be disabled */
void send_a_refresh(struct dram_info *dram)
{
	void __iomem *pctl_base = dram->pctl;

	while (readl(pctl_base + DDR_PCTL2_DBGSTAT) & 0x3)
		continue;
	writel(0x3, pctl_base + DDR_PCTL2_DBGCMD);
}

static void enter_sr(struct dram_info *dram, u32 en)
{
	void __iomem *pctl_base = dram->pctl;

	if (en) {
		setbits_le32(pctl_base + DDR_PCTL2_PWRCTL, PCTL2_SELFREF_SW);
		while (1) {
			if (((readl(pctl_base + DDR_PCTL2_STAT) &
			      PCTL2_SELFREF_TYPE_MASK) ==
			     PCTL2_SELFREF_TYPE_SR_NOT_AUTO) &&
			    ((readl(pctl_base + DDR_PCTL2_STAT) &
			      PCTL2_OPERATING_MODE_MASK) ==
			     PCTL2_OPERATING_MODE_SR))
				break;
		}
	} else {
		clrbits_le32(pctl_base + DDR_PCTL2_PWRCTL, PCTL2_SELFREF_SW);
		while ((readl(pctl_base + DDR_PCTL2_STAT) &
		       PCTL2_OPERATING_MODE_MASK) == PCTL2_OPERATING_MODE_SR)
			continue;
	}
}

void record_dq_prebit(struct dram_info *dram)
{
	u32 group, i, tmp;
	void __iomem *phy_base = dram->phy;

	for (group = 0; group < 4; group++) {
		for (i = 0; i < ARRAY_SIZE(dq_sel); i++) {
			/* l_loop_invdelaysel */
			writel(dq_sel[i][0], PHY_REG(phy_base,
						     grp_addr[group] + 0x2c));
			tmp = readl(PHY_REG(phy_base, grp_addr[group] + 0x2e));
			writel(tmp, PHY_REG(phy_base,
					    grp_addr[group] + dq_sel[i][1]));

			/* r_loop_invdelaysel */
			writel(dq_sel[i][0], PHY_REG(phy_base,
						     grp_addr[group] + 0x2d));
			tmp = readl(PHY_REG(phy_base, grp_addr[group] + 0x2f));
			writel(tmp, PHY_REG(phy_base,
					    grp_addr[group] + dq_sel[i][2]));
		}
	}
}

static void update_dq_rx_prebit(struct dram_info *dram)
{
	void __iomem *phy_base = dram->phy;

	clrsetbits_le32(PHY_REG(phy_base, 0x70), BIT(1) | BIT(6) | BIT(4),
			BIT(4));
	udelay(1);
	clrbits_le32(PHY_REG(phy_base, 0x70), BIT(4));
}

static void update_dq_tx_prebit(struct dram_info *dram)
{
	void __iomem *phy_base = dram->phy;

	clrbits_le32(PHY_REG(phy_base, 0x7a), BIT(1));
	setbits_le32(PHY_REG(phy_base, 0x2), BIT(3));
	setbits_le32(PHY_REG(phy_base, 0xc), BIT(6));
	udelay(1);
	clrbits_le32(PHY_REG(phy_base, 0xc), BIT(6));
}

static void update_ca_prebit(struct dram_info *dram)
{
	void __iomem *phy_base = dram->phy;

	clrbits_le32(PHY_REG(phy_base, 0x25), BIT(2));
	setbits_le32(PHY_REG(phy_base, 0x22), BIT(6));
	udelay(1);
	clrbits_le32(PHY_REG(phy_base, 0x22), BIT(6));
}

/*
 * dir: 0: de-skew = delta_*
 *	1: de-skew = reg val - delta_*
 * delta_dir: value for differential signal: clk/
 * delta_sig: value for single signal: ca/cmd
 */
static void modify_ca_deskew(struct dram_info *dram, u32 dir, int delta_dif,
			     int delta_sig, u32 cs, u32 dramtype)
{
	void __iomem *phy_base = dram->phy;
	u32 i, cs_en, tmp;
	u32 dfi_lp_stat = 0;

	if (cs == 0)
		cs_en = 1;
	else if (cs == 2)
		cs_en = 2;
	else
		cs_en = 3;

	if ((dramtype == LPDDR4 || dramtype == LPDDR4X) &&
	    ((readl(PHY_REG(phy_base, 0x60)) & BIT(5)) == 0)) {
		dfi_lp_stat = 1;
		setbits_le32(PHY_REG(phy_base, 0x60), BIT(5));
	}
	enter_sr(dram, 1);

	for (i = 0; i < 0x20; i++) {
		if (dir == DESKEW_MDF_ABS_VAL)
			tmp = delta_sig;
		else
			tmp = readl(PHY_REG(phy_base, 0x150 + i)) +
			      delta_sig;
		writel(tmp, PHY_REG(phy_base, 0x150 + i));
	}

	if (dir == DESKEW_MDF_ABS_VAL)
		tmp = delta_dif;
	else
		tmp = readl(PHY_REG(phy_base, 0x150 + 0x17)) -
		       delta_sig + delta_dif;
	writel(tmp, PHY_REG(phy_base, 0x150 + 0x17));
	writel(tmp, PHY_REG(phy_base, 0x150 + 0x18));
	if (dramtype == LPDDR4 || dramtype == LPDDR4X) {
		writel(tmp, PHY_REG(phy_base, 0x150 + 0x4));
		writel(tmp, PHY_REG(phy_base, 0x150 + 0xa));

		clrbits_le32(PHY_REG(phy_base, 0x10), cs_en << 6);
		update_ca_prebit(dram);
	}
	enter_sr(dram, 0);

	if (dfi_lp_stat)
		clrbits_le32(PHY_REG(phy_base, 0x60), BIT(5));

}

static u32 get_min_value(struct dram_info *dram, u32 signal, u32 rank)
{
	u32 i, j, offset = 0;
	u32 min = 0x3f;
	void __iomem *phy_base = dram->phy;
	u32 byte_en;

	if (signal == SKEW_TX_SIGNAL)
		offset = 8;

	if (signal == SKEW_CA_SIGNAL) {
		for (i = 0; i < 0x20; i++)
			min = MIN(min, readl(PHY_REG(phy_base, 0x150  + i)));
	} else {
		byte_en = readl(PHY_REG(phy_base, 0xf)) & 0xf;
		for (j = offset; j < offset + rank * 4; j++) {
			if (!((byte_en >> (j % 4)) & 1))
				continue;
			for (i = 0; i < 11; i++)
				min = MIN(min,
					  readl(PHY_REG(phy_base,
							dqs_dq_skew_adr[j] +
							i)));
		}
	}

	return min;
}

static u32 low_power_update(struct dram_info *dram, u32 en)
{
	void __iomem *pctl_base = dram->pctl;
	u32 lp_stat = 0;

	if (en) {
		setbits_le32(pctl_base + DDR_PCTL2_PWRCTL, en & 0xf);
	} else {
		lp_stat = readl(pctl_base + DDR_PCTL2_PWRCTL) & 0xf;
		clrbits_le32(pctl_base + DDR_PCTL2_PWRCTL, 0xf);
	}

	return lp_stat;
}

/*
 * signal:
 * dir: 0: de-skew = delta_*
 *	1: de-skew = reg val - delta_*
 * delta_dir: value for differential signal: dqs
 * delta_sig: value for single signal: dq/dm
 */
static void modify_dq_deskew(struct dram_info *dram, u32 signal, u32 dir,
			     int delta_dif, int delta_sig, u32 rank)
{
	void __iomem *phy_base = dram->phy;
	u32 i, j, tmp, offset;
	u32 byte_en;

	byte_en = readl(PHY_REG(phy_base, 0xf)) & 0xf;

	if (signal == SKEW_RX_SIGNAL)
		offset = 0;
	else
		offset = 8;

	for (j = offset; j < (offset + rank * 4); j++) {
		if (!((byte_en >> (j % 4)) & 1))
			continue;
		for (i = 0; i < 0x9; i++) {
			if (dir == DESKEW_MDF_ABS_VAL)
				tmp = delta_sig;
			else
				tmp = delta_sig + readl(PHY_REG(phy_base,
							dqs_dq_skew_adr[j] +
							i));
			writel(tmp, PHY_REG(phy_base, dqs_dq_skew_adr[j] + i));
		}
		if (dir == DESKEW_MDF_ABS_VAL)
			tmp = delta_dif;
		else
			tmp = delta_dif + readl(PHY_REG(phy_base,
						dqs_dq_skew_adr[j] + 9));
		writel(tmp, PHY_REG(phy_base, dqs_dq_skew_adr[j] + 9));
		writel(tmp, PHY_REG(phy_base, dqs_dq_skew_adr[j] + 0xa));
	}
	if (signal == SKEW_RX_SIGNAL)
		update_dq_rx_prebit(dram);
	else
		update_dq_tx_prebit(dram);
}

static int data_training_rg(struct dram_info *dram, u32 cs, u32 dramtype)
{
	void __iomem *phy_base = dram->phy;
	u32 ret;
	u32 dis_auto_zq = 0;
	u32 odt_val_up, odt_val_dn;
	u32 i, j;

	odt_val_dn = readl(PHY_REG(phy_base, 0x110));
	odt_val_up = readl(PHY_REG(phy_base, 0x111));

	if (dramtype != LPDDR4 || dramtype != LPDDR4X) {
		for (i = 0; i < 4; i++) {
			j = 0x110 + i * 0x10;
			writel(PHY_DDR4_LPDDR3_RTT_294ohm,
			       PHY_REG(phy_base, j));
			writel(PHY_DDR4_LPDDR3_RTT_DISABLE,
			       PHY_REG(phy_base, j + 0x1));
		}
	}
	dis_auto_zq = pctl_dis_zqcs_aref(dram->pctl);
	/* use normal read mode for data training */
	clrbits_le32(PHY_REG(phy_base, 0xc), BIT(1));

	if (dramtype == DDR4)
		setbits_le32(PHY_REG(phy_base, 0xc), BIT(1));

	/* choose training cs */
	clrsetbits_le32(PHY_REG(phy_base, 2), 0x33, (0x20 >> cs));
	/* enable gate training */
	clrsetbits_le32(PHY_REG(phy_base, 2), 0x33, (0x20 >> cs) | 1);
	udelay(50);
	ret = readl(PHY_REG(phy_base, 0x91));
	/* disable gate training */
	clrsetbits_le32(PHY_REG(phy_base, 2), 0x33, (0x20 >> cs) | 0);
	clrbits_le32(PHY_REG(phy_base, 2), 0x30);
	pctl_rest_zqcs_aref(dram->pctl, dis_auto_zq);

	ret = (ret & 0x2f) ^ (readl(PHY_REG(phy_base, 0xf)) & 0xf);

	if (dramtype != LPDDR4 || dramtype != LPDDR4X) {
		for (i = 0; i < 4; i++) {
			j = 0x110 + i * 0x10;
			writel(odt_val_dn, PHY_REG(phy_base, j));
			writel(odt_val_up, PHY_REG(phy_base, j + 0x1));
		}
	}
	return ret;
}

static int data_training_wl(struct dram_info *dram, u32 cs, u32 dramtype,
			    u32 rank)
{
	void __iomem *pctl_base = dram->pctl;
	void __iomem *phy_base = dram->phy;
	u32 dis_auto_zq = 0;
	u32 tmp;
	u32 cur_fsp;
	u32 timeout_us = 1000;

	dis_auto_zq = pctl_dis_zqcs_aref(dram->pctl);

	clrbits_le32(PHY_REG(phy_base, 0x7a), 0x1);

	cur_fsp = readl(pctl_base + DDR_PCTL2_MSTR2) & 0x3;
	tmp = readl(pctl_base + UMCTL2_REGS_FREQ(cur_fsp) + DDR_PCTL2_INIT3) &
	      0xffff;
	writel(tmp & 0xff, PHY_REG(phy_base, 0x3));

	/* disable another cs's output */
	if ((dramtype == DDR3 || dramtype == DDR4) && rank == 2)
		pctl_write_mr(dram->pctl, (cs + 1) & 1, 1, tmp | (1 << 12),
			      dramtype);
	if (dramtype == DDR3 || dramtype == DDR4)
		writel(0x40 | ((tmp >> 8) & 0x3f), PHY_REG(phy_base, 0x4));
	else
		writel(0x80 | ((tmp >> 8) & 0x3f), PHY_REG(phy_base, 0x4));

	/* choose cs */
	clrsetbits_le32(PHY_REG(phy_base, 2), (0x3 << 6) | (0x3 << 2),
			((0x2 >> cs) << 6) | (0 << 2));
	/* enable write leveling */
	clrsetbits_le32(PHY_REG(phy_base, 2), (0x3 << 6) | (0x3 << 2),
			((0x2 >> cs) << 6) | (1 << 2));

	while (1) {
		if ((readl(PHY_REG(phy_base, 0x92)) & 0xf) ==
		    (readl(PHY_REG(phy_base, 0xf)) & 0xf))
			break;

		udelay(1);
		if (timeout_us-- == 0) {
			printascii("error: write leveling timeout\n");
			while (1)
				;
		}
	}

	/* disable write leveling */
	clrsetbits_le32(PHY_REG(phy_base, 2), (0x3 << 6) | (0x3 << 2),
			((0x2 >> cs) << 6) | (0 << 2));
	clrsetbits_le32(PHY_REG(phy_base, 2), 0x3 << 6, 0 << 6);

	/* enable another cs's output */
	if ((dramtype == DDR3 || dramtype == DDR4) && rank == 2)
		pctl_write_mr(dram->pctl, (cs + 1) & 1, 1, tmp & ~(1 << 12),
			      dramtype);

	pctl_rest_zqcs_aref(dram->pctl, dis_auto_zq);

	return 0;
}

char pattern[32] = {
	0xaa, 0x55, 0xaa, 0x55, 0x55, 0xaa, 0x55, 0xaa,
	0x55, 0xaa, 0x55, 0xaa, 0xaa, 0x55, 0xaa, 0x55,
	0x55, 0x55, 0xaa, 0xaa, 0xaa, 0xaa, 0x55, 0x55,
	0xaa, 0xaa, 0x55, 0x55, 0x55, 0x55, 0xaa, 0xaa
};

static int data_training_rd(struct dram_info *dram, u32 cs, u32 dramtype,
			    u32 mhz)
{
	void __iomem *pctl_base = dram->pctl;
	void __iomem *phy_base = dram->phy;
	u32 trefi_1x, trfc_1x;
	u32 dis_auto_zq = 0;
	u32 timeout_us = 1000;
	u32 dqs_default;
	u32 cur_fsp;
	u32 vref_inner;
	u32 i;
	struct sdram_head_info_index_v2 *index =
		(struct sdram_head_info_index_v2 *)common_info;
	struct dq_map_info *map_info;

	vref_inner = readl(PHY_REG(phy_base, 0x128)) & 0xff;
	if (dramtype == DDR3 && vref_inner == 0x80) {
		for (i = 0; i < 4; i++)
			writel(vref_inner - 0xa,
			       PHY_REG(phy_base, 0x118 + i * 0x10));

		/* reg_rx_vref_value_update */
		setbits_le32(PHY_REG(phy_base, 0x71), 1 << 5);
		clrbits_le32(PHY_REG(phy_base, 0x71), 1 << 5);
	}

	map_info = (struct dq_map_info *)((void *)common_info +
		index->dq_map_index.offset * 4);
	/* only 1cs a time, 0:cs0 1 cs1 */
	if (cs > 1)
		return -1;

	dqs_default = 0xf;
	dis_auto_zq = pctl_dis_zqcs_aref(dram->pctl);

	cur_fsp = readl(pctl_base + DDR_PCTL2_MSTR2) & 0x3;
	/* config refresh timing */
	trefi_1x = ((readl(pctl_base + UMCTL2_REGS_FREQ(cur_fsp) +
			   DDR_PCTL2_RFSHTMG) >> 16) & 0xfff) * 32;
	trfc_1x = readl(pctl_base + UMCTL2_REGS_FREQ(cur_fsp) +
			DDR_PCTL2_RFSHTMG) & 0x3ff;
	/* reg_phy_trefi[7:0] and reg_phy_trefi[13:8] */
	clrsetbits_le32(PHY_REG(phy_base, 0x6e), 0xff, trefi_1x & 0xff);
	clrsetbits_le32(PHY_REG(phy_base, 0x6f), 0x3f, (trefi_1x >> 8) & 0x3f);
	/* reg_phy_trfc */
	clrsetbits_le32(PHY_REG(phy_base, 0x57), 0xff, trfc_1x);
	/* reg_max_refi_cnt */
	clrsetbits_le32(PHY_REG(phy_base, 0x61), 0xf << 4, 0x8 << 4);

	/* choose training cs */
	clrsetbits_le32(PHY_REG(phy_base, 0x71), 0x3 << 6, (0x2 >> cs) << 6);

	/* set dq map for ddr4 */
	if (dramtype == DDR4) {
		setbits_le32(PHY_REG(phy_base, 0x70), BIT(7));
		for (i = 0; i < 4; i++) {
			writel((map_info->ddr4_dq_map[cs * 2] >>
				((i % 4) * 8)) & 0xff,
				PHY_REG(phy_base, 0x238 + i));
			writel((map_info->ddr4_dq_map[cs * 2 + 1] >>
				((i % 4) * 8)) & 0xff,
				PHY_REG(phy_base, 0x2b8 + i));
		}
	}

	/* cha_l reg_l_rd_train_dqs_default[5:0] */
	clrsetbits_le32(PHY_REG(phy_base, 0x230), 0x3f, dqs_default);
	/* cha_h reg_h_rd_train_dqs_default[5:0] */
	clrsetbits_le32(PHY_REG(phy_base, 0x234), 0x3f, dqs_default);
	/* chb_l reg_l_rd_train_dqs_default[5:0] */
	clrsetbits_le32(PHY_REG(phy_base, 0x2b0), 0x3f, dqs_default);
	/* chb_h reg_h_rd_train_dqs_default[5:0] */
	clrsetbits_le32(PHY_REG(phy_base, 0x2b4), 0x3f, dqs_default);

	/* Choose the read train auto mode */
	clrsetbits_le32(PHY_REG(phy_base, 0x70), 0x3, 0x1);
	/* Enable the auto train of the read train */
	clrsetbits_le32(PHY_REG(phy_base, 0x70), 0x3, 0x3);

	/* Wait the train done. */
	while (1) {
		if ((readl(PHY_REG(phy_base, 0x93)) >> 7) & 0x1)
			break;

		udelay(1);
		if (timeout_us-- == 0) {
			printascii("error: read training timeout\n");
			return -1;
		}
	}

	/* Check the read train state */
	if ((readl(PHY_REG(phy_base, 0x240)) & 0x3) ||
	    (readl(PHY_REG(phy_base, 0x2c0)) & 0x3)) {
		printascii("error: read training error\n");
		return -1;
	}

	/* Exit the Read Training by setting */
	clrbits_le32(PHY_REG(phy_base, 0x70), BIT(1));

	pctl_rest_zqcs_aref(dram->pctl, dis_auto_zq);

	if (dramtype == DDR3 && vref_inner == 0x80) {
		for (i = 0; i < 4; i++)
			writel(vref_inner,
			       PHY_REG(phy_base, 0x118 + i * 0x10));

		/* reg_rx_vref_value_update */
		setbits_le32(PHY_REG(phy_base, 0x71), 1 << 5);
		clrbits_le32(PHY_REG(phy_base, 0x71), 1 << 5);
	}

	return 0;
}

static int data_training_wr(struct dram_info *dram, u32 cs, u32 dramtype,
			    u32 mhz, u32 dst_fsp)
{
	void __iomem *pctl_base = dram->pctl;
	void __iomem *phy_base = dram->phy;
	u32 trefi_1x, trfc_1x;
	u32 dis_auto_zq = 0;
	u32 timeout_us = 1000;
	u32 cur_fsp;
	u32 mr_tmp, cl, cwl, phy_fsp, offset = 0;

	if (dramtype == LPDDR3 && mhz <= 400) {
		phy_fsp = (readl(PHY_REG(phy_base, 0xc)) >> 0x2) & 0x3;
		offset = (phy_fsp == 0) ? 0x5 : 0x387 + (phy_fsp - 1) * 3;
		cl = readl(PHY_REG(phy_base, offset));
		cwl = readl(PHY_REG(phy_base, offset + 2));

		clrsetbits_le32(PHY_REG(phy_base, offset), 0x1f, 0x8);
		clrsetbits_le32(PHY_REG(phy_base, offset + 2), 0x1f, 0x4);
		pctl_write_mr(dram->pctl, 3, 2, 0x6, dramtype);
	}

	dis_auto_zq = pctl_dis_zqcs_aref(dram->pctl);

	/* PHY_0x7b[7:0] reg_train_col_addr[7:0] */
	clrsetbits_le32(PHY_REG(phy_base, 0x7b), 0xff, 0x0);
	/* PHY_0x7c[4:2] reg_train_ba_addr[2:0] */
	clrsetbits_le32(PHY_REG(phy_base, 0x7c), 0x7 << 2, 0x0 << 2);
	/* PHY_0x7c[1:0] reg_train_col_addr[9:8] */
	clrsetbits_le32(PHY_REG(phy_base, 0x7c), 0x3, 0x0);
	/* PHY_0x7d[7:0] reg_train_row_addr[7:0] */
	clrsetbits_le32(PHY_REG(phy_base, 0x7d), 0xff, 0x0);
	/* PHY_0x7e[7:0] reg_train_row_addr[15:8] */
	clrsetbits_le32(PHY_REG(phy_base, 0x7e), 0xff, 0x0);

	/* PHY_0x71[3] wrtrain_check_data_value_random_gen */
	clrbits_le32(PHY_REG(phy_base, 0x71), BIT(3));

	/* config refresh timing */
	cur_fsp = readl(pctl_base + DDR_PCTL2_MSTR2) & 0x3;
	trefi_1x = ((readl(pctl_base + UMCTL2_REGS_FREQ(cur_fsp) +
			   DDR_PCTL2_RFSHTMG) >> 16) & 0xfff) * 32;
	trfc_1x = readl(pctl_base + UMCTL2_REGS_FREQ(cur_fsp) +
			DDR_PCTL2_RFSHTMG) & 0x3ff;
	/* reg_phy_trefi[7:0] and reg_phy_trefi[13:8] */
	clrsetbits_le32(PHY_REG(phy_base, 0x6e), 0xff, trefi_1x & 0xff);
	clrsetbits_le32(PHY_REG(phy_base, 0x6f), 0x3f, (trefi_1x >> 8) & 0x3f);
	/* reg_phy_trfc */
	clrsetbits_le32(PHY_REG(phy_base, 0x57), 0xff, trfc_1x);
	/* reg_max_refi_cnt */
	clrsetbits_le32(PHY_REG(phy_base, 0x61), 0xf << 4, 0x8 << 4);

	/* choose training cs */
	clrsetbits_le32(PHY_REG(phy_base, 0x7c), 0x3 << 6, (0x2 >> cs) << 6);

	/* PHY_0x7a [4] reg_wr_train_dqs_default_bypass */
	/* 0: Use the write-leveling value. */
	/* 1: use reg0x233 0x237 0x2b3 0x2b7 */
	setbits_le32(PHY_REG(phy_base, 0x7a), BIT(4));

	/* PHY_0x7a [0] reg_dq_wr_train_auto */
	setbits_le32(PHY_REG(phy_base, 0x7a), 0x1);

	/* PHY_0x7a [1] reg_dq_wr_train_en */
	setbits_le32(PHY_REG(phy_base, 0x7a), BIT(1));

	send_a_refresh(dram);

	while (1) {
		if ((readl(PHY_REG(phy_base, 0x92)) >> 7) & 0x1)
			break;

		udelay(1);
		if (timeout_us-- == 0) {
			printascii("error: write training timeout\n");
			while (1)
				;
		}
	}

	/* Check the write train state */
	if ((readl(PHY_REG(phy_base, 0x90)) >> 5) & 0x7) {
		printascii("error: write training error\n");
		return -1;
	}

	/* PHY_0x7a [1] reg_dq_wr_train_en */
	clrbits_le32(PHY_REG(phy_base, 0x7a), BIT(1));

	pctl_rest_zqcs_aref(dram->pctl, dis_auto_zq);

	/* save LPDDR4/LPDDR4X write vref to fsp_param for dfs */
	if (dramtype == LPDDR4 || dramtype == LPDDR4X) {
		fsp_param[dst_fsp].vref_dq[cs] =
			((readl(PHY_REG(phy_base, 0x384)) & 0x3f) +
			 (readl(PHY_REG(phy_base, 0x385)) & 0x3f)) / 2;
		/* add range info */
		fsp_param[dst_fsp].vref_dq[cs] |=
			((readl(PHY_REG(phy_base, 0x7c)) & BIT(5)) << 1);
	}

	if (dramtype == LPDDR3 && mhz <= 400) {
		clrsetbits_le32(PHY_REG(phy_base, offset), 0x1f, cl);
		clrsetbits_le32(PHY_REG(phy_base, offset + 2), 0x1f, cwl);
		mr_tmp = readl(pctl_base + UMCTL2_REGS_FREQ(cur_fsp) +
			       DDR_PCTL2_INIT3);
		pctl_write_mr(dram->pctl, 3, 2, mr_tmp & PCTL2_MR_MASK,
			      dramtype);
	}

	return 0;
}

static int data_training(struct dram_info *dram, u32 cs,
			 struct rv1126_sdram_params *sdram_params, u32 dst_fsp,
			 u32 training_flag)
{
	u32 ret = 0;

	if (training_flag == FULL_TRAINING)
		training_flag = READ_GATE_TRAINING | WRITE_LEVELING |
				WRITE_TRAINING | READ_TRAINING;

	if ((training_flag & WRITE_LEVELING) == WRITE_LEVELING) {
		ret = data_training_wl(dram, cs,
				       sdram_params->base.dramtype,
				       sdram_params->ch.cap_info.rank);
		if (ret != 0)
			goto out;
	}

	if ((training_flag & READ_GATE_TRAINING) == READ_GATE_TRAINING) {
		ret = data_training_rg(dram, cs,
				       sdram_params->base.dramtype);
		if (ret != 0)
			goto out;
	}

	if ((training_flag & READ_TRAINING) == READ_TRAINING) {
		ret = data_training_rd(dram, cs,
				       sdram_params->base.dramtype,
				       sdram_params->base.ddr_freq);
		if (ret != 0)
			goto out;
	}

	if ((training_flag & WRITE_TRAINING) == WRITE_TRAINING) {
		ret = data_training_wr(dram, cs,
				       sdram_params->base.dramtype,
				       sdram_params->base.ddr_freq, dst_fsp);
		if (ret != 0)
			goto out;
	}

out:
	return ret;
}

static int get_wrlvl_val(struct dram_info *dram,
			 struct rv1126_sdram_params *sdram_params)
{
	int i, j, clk_skew;
	void __iomem *phy_base = dram->phy;
	u32 lp_stat;
	int ret;

	lp_stat = low_power_update(dram, 0);

	clk_skew = 0x1f;
	modify_ca_deskew(dram, DESKEW_MDF_ABS_VAL, clk_skew, clk_skew, 3,
			 sdram_params->base.dramtype);

	ret = data_training(dram, 0, sdram_params, 0, WRITE_LEVELING);
	if (sdram_params->ch.cap_info.rank == 2)
		ret |= data_training(dram, 1, sdram_params, 0, WRITE_LEVELING);

	for (j = 0; j < 2; j++)
		for (i = 0; i < 4; i++)
			wrlvl_result[j][i] =
				(readl(PHY_REG(phy_base, wrlvl_result_offset[j][i])) & 0x3f) -
				clk_skew;

	low_power_update(dram, lp_stat);

	return ret;
}

#if defined(CONFIG_CMD_DDR_TEST_TOOL)
static void init_rw_trn_result_struct(struct rw_trn_result *result,
				      void __iomem *phy_base, u8 cs_num)
{
	int i;

	result->cs_num = cs_num;
	result->byte_en = readb(PHY_REG(dram_info.phy, 0xf)) &
			  PHY_DQ_WIDTH_MASK;
	for (i = 0; i < FSP_NUM; i++)
		result->fsp_mhz[i] = 0;
}

static void save_rw_trn_min_max(void __iomem *phy_base,
				struct cs_rw_trn_result *rd_result,
				struct cs_rw_trn_result *wr_result,
				u8 byte_en)
{
	u16 phy_ofs;
	u8 dqs;
	u8 dq;

	for (dqs = 0; dqs < BYTE_NUM; dqs++) {
		if ((byte_en & BIT(dqs)) == 0)
			continue;

		/* Channel A or B (low or high 16 bit) */
		phy_ofs = dqs < 2 ? 0x230 : 0x2b0;
		/* low or high 8 bit */
		phy_ofs += (dqs & 0x1) == 0 ? 0 : 0x9;
		for (dq = 0; dq < 8; dq++) {
			rd_result->dqs[dqs].dq_min[dq] =
				readb(PHY_REG(phy_base, phy_ofs + 0x15 + dq));
			rd_result->dqs[dqs].dq_max[dq] =
				readb(PHY_REG(phy_base, phy_ofs + 0x27 + dq));
			wr_result->dqs[dqs].dq_min[dq] =
				readb(PHY_REG(phy_base, phy_ofs + 0x3d + dq));
			wr_result->dqs[dqs].dq_max[dq] =
				readb(PHY_REG(phy_base, phy_ofs + 0x4f + dq));
		}
	}
}

static void save_rw_trn_deskew(void __iomem *phy_base,
			       struct fsp_rw_trn_result *result, u8 cs_num,
			       int min_val, bool rw)
{
	u16 phy_ofs;
	u8 cs;
	u8 dq;

	result->min_val = min_val;

	for (cs = 0; cs < cs_num; cs++) {
		phy_ofs = cs == 0 ? 0x170 : 0x1a0;
		phy_ofs += rw == SKEW_RX_SIGNAL ? 0x1 : 0x17;
		for (dq = 0; dq < 8; dq++) {
			result->cs[cs].dqs[0].dq_deskew[dq] =
				readb(PHY_REG(phy_base, phy_ofs + dq));
			result->cs[cs].dqs[1].dq_deskew[dq] =
				readb(PHY_REG(phy_base, phy_ofs + 0xb + dq));
			result->cs[cs].dqs[2].dq_deskew[dq] =
				readb(PHY_REG(phy_base, phy_ofs + 0x60 + dq));
			result->cs[cs].dqs[3].dq_deskew[dq] =
				readb(PHY_REG(phy_base, phy_ofs + 0x60 + 0xb + dq));
		}

		result->cs[cs].dqs[0].dqs_deskew =
			readb(PHY_REG(phy_base, phy_ofs + 0x8));
		result->cs[cs].dqs[1].dqs_deskew =
			readb(PHY_REG(phy_base, phy_ofs + 0xb + 0x8));
		result->cs[cs].dqs[2].dqs_deskew =
			readb(PHY_REG(phy_base, phy_ofs + 0x60 + 0x8));
		result->cs[cs].dqs[3].dqs_deskew =
			readb(PHY_REG(phy_base, phy_ofs + 0x60 + 0xb + 0x8));
	}
}

static void save_rw_trn_result_to_ddr(struct rw_trn_result *result)
{
	result->flag = DDR_DQ_EYE_FLAG;
	memcpy((void *)(RW_TRN_RESULT_ADDR), result, sizeof(*result));
}
#endif

static int high_freq_training(struct dram_info *dram,
			      struct rv1126_sdram_params *sdram_params,
			      u32 fsp)
{
	u32 i, j;
	void __iomem *phy_base = dram->phy;
	u32 dramtype = sdram_params->base.dramtype;
	int min_val;
	int dqs_skew, clk_skew, ca_skew;
	u8 byte_en;
	int ret;

	byte_en = readl(PHY_REG(phy_base, 0xf)) & PHY_DQ_WIDTH_MASK;
	dqs_skew = 0;
	for (j = 0; j < sdram_params->ch.cap_info.rank; j++) {
		for (i = 0; i < ARRAY_SIZE(wrlvl_result[0]); i++) {
			if ((byte_en & BIT(i)) != 0)
				dqs_skew += wrlvl_result[j][i];
		}
	}
	dqs_skew = dqs_skew /
		   (int)(sdram_params->ch.cap_info.rank * (1 << sdram_params->ch.cap_info.bw));

	clk_skew = 0x20 - dqs_skew;
	dqs_skew = 0x20;

	if (dramtype == LPDDR4 || dramtype == LPDDR4X) {
		min_val = 0xff;
		for (j = 0; j < sdram_params->ch.cap_info.rank; j++)
			for (i = 0; i < sdram_params->ch.cap_info.bw; i++)
				min_val = MIN(wrlvl_result[j][i], min_val);

		if (min_val < 0) {
			clk_skew = -min_val;
			ca_skew = -min_val;
		} else {
			clk_skew = 0;
			ca_skew = 0;
		}
	} else if (dramtype == LPDDR3) {
		ca_skew = clk_skew - 4;
	} else {
		ca_skew = clk_skew;
	}
	modify_ca_deskew(dram, DESKEW_MDF_ABS_VAL, clk_skew, ca_skew, 3,
			 dramtype);

	writel(wrlvl_result[0][0] + clk_skew, PHY_REG(phy_base, 0x233));
	writel(wrlvl_result[0][1] + clk_skew, PHY_REG(phy_base, 0x237));
	writel(wrlvl_result[0][2] + clk_skew, PHY_REG(phy_base, 0x2b3));
	writel(wrlvl_result[0][3] + clk_skew, PHY_REG(phy_base, 0x2b7));
	ret = data_training(dram, 0, sdram_params, fsp, READ_GATE_TRAINING |
			    READ_TRAINING | WRITE_TRAINING);
#if defined(CONFIG_CMD_DDR_TEST_TOOL)
	rw_trn_result.fsp_mhz[fsp] = (u16)sdram_params->base.ddr_freq;
	save_rw_trn_min_max(phy_base, &rw_trn_result.rd_fsp[fsp].cs[0],
			    &rw_trn_result.wr_fsp[fsp].cs[0],
			    rw_trn_result.byte_en);
#endif
	if (sdram_params->ch.cap_info.rank == 2) {
		writel(wrlvl_result[1][0] + clk_skew, PHY_REG(phy_base, 0x233));
		writel(wrlvl_result[1][1] + clk_skew, PHY_REG(phy_base, 0x237));
		writel(wrlvl_result[1][2] + clk_skew, PHY_REG(phy_base, 0x2b3));
		writel(wrlvl_result[1][3] + clk_skew, PHY_REG(phy_base, 0x2b7));
		ret |= data_training(dram, 1, sdram_params, fsp,
				     READ_GATE_TRAINING | READ_TRAINING |
				     WRITE_TRAINING);
#if defined(CONFIG_CMD_DDR_TEST_TOOL)
		save_rw_trn_min_max(phy_base, &rw_trn_result.rd_fsp[fsp].cs[1],
				    &rw_trn_result.wr_fsp[fsp].cs[1],
				    rw_trn_result.byte_en);
#endif
	}
	if (ret)
		goto out;

	record_dq_prebit(dram);

	min_val = get_min_value(dram, SKEW_RX_SIGNAL,
				sdram_params->ch.cap_info.rank) * -1;
	modify_dq_deskew(dram, SKEW_RX_SIGNAL, DESKEW_MDF_DIFF_VAL,
			 min_val, min_val, sdram_params->ch.cap_info.rank);
#if defined(CONFIG_CMD_DDR_TEST_TOOL)
	save_rw_trn_deskew(phy_base, &rw_trn_result.rd_fsp[fsp],
			   rw_trn_result.cs_num, (u8)(min_val * (-1)),
			   SKEW_RX_SIGNAL);
#endif

	min_val = MIN(get_min_value(dram, SKEW_TX_SIGNAL,
				    sdram_params->ch.cap_info.rank),
		      get_min_value(dram, SKEW_CA_SIGNAL,
				    sdram_params->ch.cap_info.rank)) * -1;

	/* clk = 0, rx all skew -7, tx - min_value */
	modify_ca_deskew(dram, DESKEW_MDF_DIFF_VAL, min_val, min_val, 3,
			 dramtype);

	modify_dq_deskew(dram, SKEW_TX_SIGNAL, DESKEW_MDF_DIFF_VAL,
			 min_val, min_val, sdram_params->ch.cap_info.rank);
#if defined(CONFIG_CMD_DDR_TEST_TOOL)
	save_rw_trn_deskew(phy_base, &rw_trn_result.wr_fsp[fsp],
			   rw_trn_result.cs_num, (u8)(min_val * (-1)),
			   SKEW_TX_SIGNAL);
#endif

	ret = data_training(dram, 0, sdram_params, 0, READ_GATE_TRAINING);
	if (sdram_params->ch.cap_info.rank == 2)
		ret |= data_training(dram, 1, sdram_params, 0,
				     READ_GATE_TRAINING);
out:
	return ret;
}

static void set_ddrconfig(struct dram_info *dram, u32 ddrconfig)
{
	writel(ddrconfig, &dram->msch->deviceconf);
	clrsetbits_le32(&dram->grf->noc_con0, 0x3 << 0, 0 << 0);
}

static void update_noc_timing(struct dram_info *dram,
			      struct rv1126_sdram_params *sdram_params)
{
	void __iomem *pctl_base = dram->pctl;
	u32 bw, bl;

	bw = 8 << sdram_params->ch.cap_info.bw;
	bl = ((readl(pctl_base + DDR_PCTL2_MSTR) >> 16) & 0xf) * 2;

	/* update the noc timing related to data bus width */
	if ((bw / 8 * bl) <= 16)
		sdram_params->ch.noc_timings.ddrmode.b.burstsize = 0;
	else if ((bw / 8 * bl) == 32)
		sdram_params->ch.noc_timings.ddrmode.b.burstsize = 1;
	else if ((bw / 8 * bl) == 64)
		sdram_params->ch.noc_timings.ddrmode.b.burstsize = 2;
	else
		sdram_params->ch.noc_timings.ddrmode.b.burstsize = 3;

	sdram_params->ch.noc_timings.ddrtimingc0.b.burstpenalty =
		(bl * bw / 8) > 16 ? (bl / 4) : (16 / (bl * bw / 8)) * bl / 4;

	if (sdram_params->base.dramtype == LPDDR4 ||
	    sdram_params->base.dramtype == LPDDR4X) {
		sdram_params->ch.noc_timings.ddrmode.b.mwrsize =
			(bw == 16) ? 0x1 : 0x2;
		sdram_params->ch.noc_timings.ddrtimingc0.b.wrtomwr =
			3 * sdram_params->ch.noc_timings.ddrtimingc0.b.burstpenalty;
	}

	writel(sdram_params->ch.noc_timings.ddrtiminga0.d32,
	       &dram->msch->ddrtiminga0);
	writel(sdram_params->ch.noc_timings.ddrtimingb0.d32,
	       &dram->msch->ddrtimingb0);
	writel(sdram_params->ch.noc_timings.ddrtimingc0.d32,
	       &dram->msch->ddrtimingc0);
	writel(sdram_params->ch.noc_timings.devtodev0.d32,
	       &dram->msch->devtodev0);
	writel(sdram_params->ch.noc_timings.ddrmode.d32, &dram->msch->ddrmode);
	writel(sdram_params->ch.noc_timings.ddr4timing.d32,
	       &dram->msch->ddr4timing);
}

static int split_setup(struct dram_info *dram,
		       struct rv1126_sdram_params *sdram_params)
{
	struct sdram_cap_info *cap_info = &sdram_params->ch.cap_info;
	u32 dramtype = sdram_params->base.dramtype;
	u32 split_size, split_mode;
	u64 cs_cap[2], cap;

	cs_cap[0] = sdram_get_cs_cap(cap_info, 0, dramtype);
	cs_cap[1] = sdram_get_cs_cap(cap_info, 1, dramtype);
	/* only support the larger cap is in low 16bit */
	if (cap_info->cs0_high16bit_row < cap_info->cs0_row) {
		cap = cs_cap[0] / (1 << (cap_info->cs0_row -
		cap_info->cs0_high16bit_row));
	} else if ((cap_info->cs1_high16bit_row < cap_info->cs1_row) &&
		   (cap_info->rank == 2)) {
		if (!cap_info->cs1_high16bit_row)
			cap = cs_cap[0];
		else
			cap = cs_cap[0] + cs_cap[1] / (1 << (cap_info->cs1_row -
				cap_info->cs1_high16bit_row));
	} else {
		goto out;
	}
	split_size = (u32)(cap >> 24) & SPLIT_SIZE_MASK;
	if (cap_info->bw == 2)
		split_mode = SPLIT_MODE_32_L16_VALID;
	else
		split_mode = SPLIT_MODE_16_L8_VALID;

	rk_clrsetreg(&dram->ddrgrf->grf_ddrsplit_con,
		     (SPLIT_MODE_MASK << SPLIT_MODE_OFFSET) |
		     (SPLIT_BYPASS_MASK << SPLIT_BYPASS_OFFSET) |
		     (SPLIT_SIZE_MASK << SPLIT_SIZE_OFFSET),
		     (split_mode << SPLIT_MODE_OFFSET) |
		     (0x0 << SPLIT_BYPASS_OFFSET) |
		     (split_size << SPLIT_SIZE_OFFSET));

	rk_clrsetreg(BUS_SGRF_BASE_ADDR + SGRF_SOC_CON2,
		     MSCH_AXI_BYPASS_ALL_MASK << MSCH_AXI_BYPASS_ALL_SHIFT,
		     0x0 << MSCH_AXI_BYPASS_ALL_SHIFT);

out:
	return 0;
}

static void split_bypass(struct dram_info *dram)
{
	if ((readl(&dram->ddrgrf->grf_ddrsplit_con) &
	     (1 << SPLIT_BYPASS_OFFSET)) != 0)
		return;

	/* bypass split */
	rk_clrsetreg(&dram->ddrgrf->grf_ddrsplit_con,
		     (SPLIT_BYPASS_MASK << SPLIT_BYPASS_OFFSET) |
		     (SPLIT_SIZE_MASK << SPLIT_SIZE_OFFSET),
		     (0x1 << SPLIT_BYPASS_OFFSET) |
		     (0x0 << SPLIT_SIZE_OFFSET));
}

static void dram_all_config(struct dram_info *dram,
			    struct rv1126_sdram_params *sdram_params)
{
	struct sdram_cap_info *cap_info = &sdram_params->ch.cap_info;
	u32 dram_type = sdram_params->base.dramtype;
	void __iomem *pctl_base = dram->pctl;
	u32 sys_reg2 = 0;
	u32 sys_reg3 = 0;
	u64 cs_cap[2];
	u32 cs_pst;

	set_ddrconfig(dram, cap_info->ddrconfig);
	sdram_org_config(cap_info, &sdram_params->base, &sys_reg2,
			 &sys_reg3, 0);
	writel(sys_reg2, &dram->pmugrf->os_reg[2]);
	writel(sys_reg3, &dram->pmugrf->os_reg[3]);

	cs_cap[0] = sdram_get_cs_cap(cap_info, 0, dram_type);
	cs_cap[1] = sdram_get_cs_cap(cap_info, 1, dram_type);

	if (cap_info->rank == 2) {
		cs_pst = (readl(pctl_base + DDR_PCTL2_ADDRMAP0) & 0x1f) +
			6 + 2;
		if (cs_pst > 28)
			cs_cap[0] = 1llu << cs_pst;
	}

	writel(((((cs_cap[1] >> 20) / 64) & 0xff) << 8) |
			(((cs_cap[0] >> 20) / 64) & 0xff),
			&dram->msch->devicesize);
	update_noc_timing(dram, sdram_params);
}

static void enable_low_power(struct dram_info *dram,
			     struct rv1126_sdram_params *sdram_params)
{
	void __iomem *pctl_base = dram->pctl;
	u32 grf_lp_con;

	writel(0x1f1f0617, &dram->ddrgrf->ddr_grf_con[1]);

	if (sdram_params->base.dramtype == DDR4)
		grf_lp_con = (0x7 << 16) | (1 << 1);
	else if (sdram_params->base.dramtype == DDR3)
		grf_lp_con = (0x7 << 16) | (1 << 0);
	else
		grf_lp_con = (0x7 << 16) | (1 << 2);

	/* en lpckdis_en */
	grf_lp_con = grf_lp_con | (0x1 << (9 + 16)) | (0x1 << 9);
	writel(grf_lp_con, &dram->ddrgrf->ddr_grf_lp_con);

	/* enable sr, pd */
	if (dram->pd_idle == 0)
		clrbits_le32(pctl_base + DDR_PCTL2_PWRCTL, (1 << 1));
	else
		setbits_le32(pctl_base + DDR_PCTL2_PWRCTL, (1 << 1));
	if (dram->sr_idle == 0)
		clrbits_le32(pctl_base + DDR_PCTL2_PWRCTL, 1);
	else
		setbits_le32(pctl_base + DDR_PCTL2_PWRCTL, 1);
	setbits_le32(pctl_base + DDR_PCTL2_PWRCTL, (1 << 3));
}

static void ddr_set_atags(struct dram_info *dram,
			  struct rv1126_sdram_params *sdram_params)
{
	struct sdram_cap_info *cap_info = &sdram_params->ch.cap_info;
	u32 dram_type = sdram_params->base.dramtype;
	void __iomem *pctl_base = dram->pctl;
	struct tag_serial t_serial;
	struct tag_ddr_mem t_ddrmem;
	struct tag_soc_info t_socinfo;
	u64 cs_cap[2];
	u32 cs_pst = 0;
	u32 split, split_size;
	u64 reduce_cap = 0;

	cs_cap[0] = sdram_get_cs_cap(cap_info, 0, dram_type);
	cs_cap[1] = sdram_get_cs_cap(cap_info, 1, dram_type);

	memset(&t_serial, 0, sizeof(struct tag_serial));

	t_serial.version = 0;
	t_serial.enable = 1;
	t_serial.addr = CONFIG_DEBUG_UART_BASE;
	t_serial.baudrate = CONFIG_BAUDRATE;
	t_serial.m_mode = SERIAL_M_MODE_M0;
	t_serial.id = 2;

	atags_destroy();
	atags_set_tag(ATAG_SERIAL,  &t_serial);

	split = readl(&dram->ddrgrf->grf_ddrsplit_con);
	memset(&t_ddrmem, 0, sizeof(struct tag_ddr_mem));
	if (cap_info->row_3_4) {
		cs_cap[0] =  cs_cap[0] * 3 / 4;
		cs_cap[1] =  cs_cap[1] * 3 / 4;
	} else if (!(split & (1 << SPLIT_BYPASS_OFFSET))) {
		split_size = (split >> SPLIT_SIZE_OFFSET) & SPLIT_SIZE_MASK;
		reduce_cap = (cs_cap[0] + cs_cap[1] - (split_size << 24)) / 2;
	}
	t_ddrmem.version = 0;
	t_ddrmem.bank[0] = CONFIG_SYS_SDRAM_BASE;
	if (cs_cap[1]) {
		cs_pst = (readl(pctl_base + DDR_PCTL2_ADDRMAP0) & 0x1f) +
			6 + 2;
	}

	if (cs_cap[1] && cs_pst > 27) {
		t_ddrmem.count = 2;
		t_ddrmem.bank[1] = 1 << cs_pst;
		t_ddrmem.bank[2] = cs_cap[0];
		t_ddrmem.bank[3] = cs_cap[1] - reduce_cap;
	} else {
		t_ddrmem.count = 1;
		t_ddrmem.bank[1] = (u64)cs_cap[0] + (u64)cs_cap[1] - reduce_cap;
	}

	atags_set_tag(ATAG_DDR_MEM,  &t_ddrmem);

	memset(&t_socinfo, 0, sizeof(struct tag_soc_info));
	t_socinfo.version = 0;
	t_socinfo.name = 0x1126;
}

static void print_ddr_info(struct rv1126_sdram_params *sdram_params)
{
	u32 split;

	if ((readl(DDR_GRF_BASE_ADDR + DDR_GRF_SPLIT_CON) &
	     (1 << SPLIT_BYPASS_OFFSET)) != 0)
		split = 0;
	else
		split = readl(DDR_GRF_BASE_ADDR + DDR_GRF_SPLIT_CON) &
			SPLIT_SIZE_MASK;

	sdram_print_ddr_info(&sdram_params->ch.cap_info,
			     &sdram_params->base, split);
}

static int sdram_init_(struct dram_info *dram,
		       struct rv1126_sdram_params *sdram_params, u32 post_init)
{
	void __iomem *pctl_base = dram->pctl;
	void __iomem *phy_base = dram->phy;
	u32 ddr4_vref;
	u32 mr_tmp;

	rkclk_configure_ddr(dram, sdram_params);

	rkclk_ddr_reset(dram, 1, 1, 1, 1);
	udelay(10);

	rkclk_ddr_reset(dram, 1, 1, 1, 0);
	phy_cfg(dram, sdram_params);

	rkclk_ddr_reset(dram, 1, 1, 0, 0);
	phy_pll_set(dram, sdram_params->base.ddr_freq * MHZ, 1);

	rkclk_ddr_reset(dram, 1, 0, 0, 0);
	pctl_cfg(dram->pctl, &sdram_params->pctl_regs,
		 dram->sr_idle, dram->pd_idle);

	if (sdram_params->ch.cap_info.bw == 2) {
		/* 32bit interface use pageclose */
		setbits_le32(pctl_base + DDR_PCTL2_SCHED, 1 << 2);
		/* pageclose = 1, pageclose_timer = 0 will err in lp4 328MHz */
		clrsetbits_le32(pctl_base + DDR_PCTL2_SCHED1, 0xff, 0x1 << 0);
	} else {
		clrbits_le32(pctl_base + DDR_PCTL2_SCHED, 1 << 2);
	}

#ifdef CONFIG_ROCKCHIP_DRAM_EXTENDED_TEMP_SUPPORT
	u32 tmp, trefi;

	tmp = readl(pctl_base + DDR_PCTL2_RFSHTMG);
	trefi = (tmp >> 16) & 0xfff;
	writel((tmp & 0xf000ffff) | (trefi / 2) << 16,
	       pctl_base + DDR_PCTL2_RFSHTMG);
#endif

	/* set frequency_mode */
	setbits_le32(pctl_base + DDR_PCTL2_MSTR, 0x1 << 29);
	/* set target_frequency to Frequency 0 */
	clrsetbits_le32(pctl_base + DDR_PCTL2_MSTR2, 0x3, 0);

	set_ds_odt(dram, sdram_params, 0);
	sdram_params->ch.cap_info.ddrconfig = calculate_ddrconfig(sdram_params);
	set_ctl_address_map(dram, sdram_params);

	setbits_le32(pctl_base + DDR_PCTL2_DFIMISC, (1 << 5) | (1 << 4));

	rkclk_ddr_reset(dram, 0, 0, 0, 0);

	while ((readl(pctl_base + DDR_PCTL2_STAT) & 0x7) == 0)
		continue;

	if (sdram_params->base.dramtype == LPDDR3) {
		pctl_write_mr(dram->pctl, 3, 11, lp3_odt_value, LPDDR3);
	} else if (sdram_params->base.dramtype == LPDDR4 ||
		   sdram_params->base.dramtype == LPDDR4X) {
		mr_tmp = readl(pctl_base + DDR_PCTL2_INIT6);
		/* MR11 */
		pctl_write_mr(dram->pctl, 3, 11,
			      mr_tmp >> PCTL2_LPDDR4_MR11_SHIFT & PCTL2_MR_MASK,
			      LPDDR4);
		/* MR12 */
		pctl_write_mr(dram->pctl, 3, 12,
			      mr_tmp >> PCTL2_LPDDR4_MR12_SHIFT & PCTL2_MR_MASK,
			      LPDDR4);

		mr_tmp = readl(pctl_base + DDR_PCTL2_INIT7);
		/* MR22 */
		pctl_write_mr(dram->pctl, 3, 22,
			      mr_tmp >> PCTL2_LPDDR4_MR22_SHIFT & PCTL2_MR_MASK,
			      LPDDR4);
	}

	if (data_training(dram, 0, sdram_params, 0, READ_GATE_TRAINING) != 0) {
		if (post_init != 0)
			printascii("DTT cs0 error\n");
		return -1;
	}

	if (sdram_params->base.dramtype == LPDDR4) {
		mr_tmp = read_mr(dram, 1, 14, LPDDR4);

		if (mr_tmp != 0x4d)
			return -1;
	}

	if (sdram_params->base.dramtype == LPDDR4 ||
	    sdram_params->base.dramtype == LPDDR4X) {
		mr_tmp = readl(pctl_base + DDR_PCTL2_INIT7);
		/* MR14 */
		pctl_write_mr(dram->pctl, 3, 14,
			      mr_tmp >> PCTL2_LPDDR4_MR14_SHIFT & PCTL2_MR_MASK,
			      LPDDR4);
	}
	if (post_init != 0 && sdram_params->ch.cap_info.rank == 2) {
		if (data_training(dram, 1, sdram_params, 0,
				  READ_GATE_TRAINING) != 0) {
			printascii("DTT cs1 error\n");
			return -1;
		}
	}

	if (sdram_params->base.dramtype == DDR4) {
		ddr4_vref = readl(PHY_REG(phy_base, 0x105)) * 39;
		pctl_write_vrefdq(dram->pctl, 0x3, ddr4_vref,
				  sdram_params->base.dramtype);
	}

	dram_all_config(dram, sdram_params);
	enable_low_power(dram, sdram_params);

	return 0;
}

static u64 dram_detect_cap(struct dram_info *dram,
			   struct rv1126_sdram_params *sdram_params,
			   unsigned char channel)
{
	struct sdram_cap_info *cap_info = &sdram_params->ch.cap_info;
	void __iomem *pctl_base = dram->pctl;
	void __iomem *phy_base = dram->phy;
	u32 mr8;

	u32 bktmp;
	u32 coltmp;
	u32 rowtmp;
	u32 cs;
	u32 dram_type = sdram_params->base.dramtype;
	u32 pwrctl;
	u32 i, dq_map;
	u32 byte1 = 0, byte0 = 0;
	u32 tmp, byte;
	struct sdram_head_info_index_v2 *index = (struct sdram_head_info_index_v2 *)common_info;
	struct dq_map_info *map_info = (struct dq_map_info *)
				       ((void *)common_info + index->dq_map_index.offset * 4);

	cap_info->bw = dram_type == DDR3 ? 0 : 1;
	if (dram_type != LPDDR4 && dram_type != LPDDR4X) {
		if (dram_type != DDR4) {
			coltmp = 12;
			bktmp = 3;
			if (dram_type == LPDDR2)
				rowtmp = 15;
			else
				rowtmp = 16;

			if (sdram_detect_col(cap_info, coltmp) != 0)
				goto cap_err;

			sdram_detect_bank(cap_info, coltmp, bktmp);
			if (dram_type != LPDDR3)
				sdram_detect_dbw(cap_info, dram_type);
		} else {
			coltmp = 10;
			bktmp = 4;
			rowtmp = 17;

			cap_info->col = 10;
			cap_info->bk = 2;
			sdram_detect_bg(cap_info, coltmp);
		}

		if (sdram_detect_row(cap_info, coltmp, bktmp, rowtmp) != 0)
			goto cap_err;

		sdram_detect_row_3_4(cap_info, coltmp, bktmp);
	} else {
		cap_info->col = 10;
		cap_info->bk = 3;
		mr8 = read_mr(dram, 1, 8, dram_type);
		cap_info->dbw = ((mr8 >> 6) & 0x3) == 0 ? 1 : 0;
		mr8 = (mr8 >> 2) & 0xf;
		if (mr8 >= 0 && mr8 <= 6) {
			cap_info->cs0_row = 14 + (mr8 + 1) / 2;
		} else if (mr8 == 0xc) {
			cap_info->cs0_row = 13;
		} else {
			printascii("Cap ERR: Fail to get cap of LPDDR4/X from MR8\n");
			goto cap_err;
		}
		if (cap_info->dbw == 0)
			cap_info->cs0_row++;
		cap_info->row_3_4 = mr8 % 2 == 1 ? 1 : 0;
		if (cap_info->cs0_row >= 17) {
			printascii("Cap ERR: ");
			printascii("RV1126 LPDDR4/X cannot support row >= 17\n");
			goto cap_err;
			// cap_info->cs0_row = 16;
			// cap_info->row_3_4 = 0;
		}
	}

	pwrctl = readl(pctl_base + DDR_PCTL2_PWRCTL);
	writel(0, pctl_base + DDR_PCTL2_PWRCTL);

	if (data_training(dram, 1, sdram_params, 0, READ_GATE_TRAINING) == 0)
		cs = 1;
	else
		cs = 0;
	cap_info->rank = cs + 1;

	setbits_le32(PHY_REG(phy_base, 0xf), 0xf);

	tmp = data_training_rg(dram, 0, dram_type) & 0xf;

	if (tmp == 0) {
		cap_info->bw = 2;
	} else {
		if (dram_type == DDR3 || dram_type == DDR4) {
			dq_map = 0;
			byte = 0;
			for (i = 0; i < 4; i++) {
				if ((tmp & BIT(i)) == 0) {
					dq_map |= byte << (i * 2);
					byte++;
				}
			}
			cap_info->bw = byte / 2;
			for (i = 0; i < 4; i++) {
				if ((tmp & BIT(i)) != 0) {
					dq_map |= byte << (i * 2);
					byte++;
				}
			}
			clrsetbits_le32(&map_info->byte_map[0], 0xff << 24, dq_map << 24);
		} else {
			dq_map = readl(PHY_REG(phy_base, 0x4f));
			for (i = 0; i < 4; i++) {
				if (((dq_map >> (i * 2)) & 0x3) == 0)
					byte0 = i;
				if (((dq_map >> (i * 2)) & 0x3) == 1)
					byte1 = i;
			}
			clrsetbits_le32(PHY_REG(phy_base, 0xf), PHY_DQ_WIDTH_MASK,
					BIT(byte0) | BIT(byte1));
			if (data_training(dram, 0, sdram_params, 0, READ_GATE_TRAINING) == 0)
				cap_info->bw = 1;
			else
				cap_info->bw = 0;
		}
	}
	if (cap_info->bw > 0)
		cap_info->dbw = 1;

	writel(pwrctl, pctl_base + DDR_PCTL2_PWRCTL);

	cap_info->cs0_high16bit_row = cap_info->cs0_row;
	if (cs) {
		cap_info->cs1_row = cap_info->cs0_row;
		cap_info->cs1_high16bit_row = cap_info->cs0_row;
	} else {
		cap_info->cs1_row = 0;
		cap_info->cs1_high16bit_row = 0;
	}

	if (dram_type == LPDDR3)
		sdram_detect_dbw(cap_info, dram_type);

	return 0;
cap_err:
	return -1;
}

static int dram_detect_cs1_row(struct dram_info *dram,
			       struct rv1126_sdram_params *sdram_params,
			       unsigned char channel)
{
	struct sdram_cap_info *cap_info = &sdram_params->ch.cap_info;
	void __iomem *pctl_base = dram->pctl;
	u32 ret = 0;
	void __iomem *test_addr;
	u32 row, bktmp, coltmp, bw;
	u64 cs0_cap;
	u32 byte_mask;
	u32 cs_pst;
	u32 cs_add = 0;
	u32 max_row;

	if (cap_info->rank == 2) {
		cs_pst = (readl(pctl_base + DDR_PCTL2_ADDRMAP0) & 0x1f) +
			6 + 2;
		if (cs_pst < 28)
			cs_add = 1;

		cs0_cap = 1 << cs_pst;

		if (sdram_params->base.dramtype == DDR4) {
			if (cap_info->dbw == 0)
				bktmp = cap_info->bk + 2;
			else
				bktmp = cap_info->bk + 1;
		} else {
			bktmp = cap_info->bk;
		}
		bw = cap_info->bw;
		coltmp = cap_info->col;

		if (bw == 2)
			byte_mask = 0xFFFF;
		else
			byte_mask = 0xFF;

		max_row = (cs_pst == 31) ? 30 : 31;

		max_row = max_row - bktmp - coltmp - bw - cs_add + 1;

		row = (cap_info->cs0_row > max_row) ? max_row :
			cap_info->cs0_row;

		for (; row > 12; row--) {
			test_addr = (void __iomem *)(CONFIG_SYS_SDRAM_BASE +
				    (u32)cs0_cap +
				    (1ul << (row + bktmp + coltmp +
					     cs_add + bw - 1ul)));

			writel(0, CONFIG_SYS_SDRAM_BASE + (u32)cs0_cap);
			writel(PATTERN, test_addr);

			if (((readl(test_addr) & byte_mask) ==
			     (PATTERN & byte_mask)) &&
			    ((readl(CONFIG_SYS_SDRAM_BASE + (u32)cs0_cap) &
			      byte_mask) == 0)) {
				ret = row;
				break;
			}
		}
	}

	return ret;
}

/* return: 0 = success, other = fail */
static int sdram_init_detect(struct dram_info *dram,
			     struct rv1126_sdram_params *sdram_params)
{
	struct sdram_cap_info *cap_info = &sdram_params->ch.cap_info;
	u32 ret;
	u32 sys_reg = 0;
	u32 sys_reg3 = 0;
	struct sdram_head_info_index_v2 *index =
		(struct sdram_head_info_index_v2 *)common_info;
	struct dq_map_info *map_info;

	map_info = (struct dq_map_info *)((void *)common_info +
		index->dq_map_index.offset * 4);

	if (sdram_init_(dram, sdram_params, 0)) {
		if (sdram_params->base.dramtype == DDR3) {
			clrsetbits_le32(&map_info->byte_map[0], 0xff << 24,
					((0x1 << 6) | (0x3 << 4) | (0x2 << 2) |
					(0x0 << 0)) << 24);
			if (sdram_init_(dram, sdram_params, 0))
				return -1;
		} else {
			return -1;
		}
	}

	if (sdram_params->base.dramtype == DDR3) {
		writel(PATTERN, CONFIG_SYS_SDRAM_BASE);
		if (readl(CONFIG_SYS_SDRAM_BASE) != PATTERN)
			return -1;
	}

	split_bypass(dram);
	if (dram_detect_cap(dram, sdram_params, 0) != 0)
		return -1;

	pctl_remodify_sdram_params(&sdram_params->pctl_regs, cap_info,
				   sdram_params->base.dramtype);
	ret = sdram_init_(dram, sdram_params, 1);
	if (ret != 0)
		goto out;

	cap_info->cs1_row =
		dram_detect_cs1_row(dram, sdram_params, 0);
	if (cap_info->cs1_row) {
		sys_reg = readl(&dram->pmugrf->os_reg[2]);
		sys_reg3 = readl(&dram->pmugrf->os_reg[3]);
		SYS_REG_ENC_CS1_ROW(cap_info->cs1_row,
				    sys_reg, sys_reg3, 0);
		writel(sys_reg, &dram->pmugrf->os_reg[2]);
		writel(sys_reg3, &dram->pmugrf->os_reg[3]);
	}

	sdram_detect_high_row(cap_info, sdram_params->base.dramtype);
	split_setup(dram, sdram_params);
out:
	return ret;
}

struct rv1126_sdram_params *get_default_sdram_config(u32 freq_mhz)
{
	u32 i;
	u32 offset = 0;
	struct ddr2_3_4_lp2_3_info *ddr_info;

	if (!freq_mhz) {
		ddr_info = get_ddr_drv_odt_info(sdram_configs[0].base.dramtype);
		if (ddr_info)
			freq_mhz =
				(ddr_info->ddr_freq0_1 >> DDR_FREQ_F0_SHIFT) &
				DDR_FREQ_MASK;
		else
			freq_mhz = 0;
	}

	for (i = 0; i < ARRAY_SIZE(sdram_configs); i++) {
		if (sdram_configs[i].base.ddr_freq == 0 ||
		    freq_mhz < sdram_configs[i].base.ddr_freq)
			break;
	}
	offset = i == 0 ? 0 : i - 1;

	return &sdram_configs[offset];
}

static const u16 pctl_need_update_reg[] = {
	DDR_PCTL2_RFSHTMG,
	DDR_PCTL2_INIT3,
	DDR_PCTL2_INIT4,
	DDR_PCTL2_INIT6,
	DDR_PCTL2_INIT7,
	DDR_PCTL2_DRAMTMG0,
	DDR_PCTL2_DRAMTMG1,
	DDR_PCTL2_DRAMTMG2,
	DDR_PCTL2_DRAMTMG3,
	DDR_PCTL2_DRAMTMG4,
	DDR_PCTL2_DRAMTMG5,
	DDR_PCTL2_DRAMTMG6,
	DDR_PCTL2_DRAMTMG7,
	DDR_PCTL2_DRAMTMG8,
	DDR_PCTL2_DRAMTMG9,
	DDR_PCTL2_DRAMTMG12,
	DDR_PCTL2_DRAMTMG13,
	DDR_PCTL2_DRAMTMG14,
	DDR_PCTL2_ZQCTL0,
	DDR_PCTL2_DFITMG0,
	DDR_PCTL2_ODTCFG
};

static const u16 phy_need_update_reg[] = {
	0x14,
	0x18,
	0x1c
};

static void pre_set_rate(struct dram_info *dram,
			 struct rv1126_sdram_params *sdram_params,
			 u32 dst_fsp, u32 dst_fsp_lp4)
{
	u32 i, j, find;
	void __iomem *pctl_base = dram->pctl;
	void __iomem *phy_base = dram->phy;
	u32 phy_offset;
	u32 mr_tmp;
	u32 dramtype = sdram_params->base.dramtype;

	sw_set_req(dram);
	/* pctl timing update */
	for (i = 0, find = 0; i < ARRAY_SIZE(pctl_need_update_reg); i++) {
		for (j = find; sdram_params->pctl_regs.pctl[j][0] != 0xFFFFFFFF;
		     j++) {
			if (sdram_params->pctl_regs.pctl[j][0] ==
			    pctl_need_update_reg[i]) {
				writel(sdram_params->pctl_regs.pctl[j][1],
				       pctl_base + UMCTL2_REGS_FREQ(dst_fsp) +
				       pctl_need_update_reg[i]);
				find = j;
				break;
			}
		}
	}

#ifdef CONFIG_ROCKCHIP_DRAM_EXTENDED_TEMP_SUPPORT
	u32 tmp, trefi;

	tmp = readl(pctl_base + UMCTL2_REGS_FREQ(dst_fsp) + DDR_PCTL2_RFSHTMG);
	trefi = (tmp >> 16) & 0xfff;
	writel((tmp & 0xf000ffff) | (trefi / 2) << 16,
	       pctl_base + UMCTL2_REGS_FREQ(dst_fsp) + DDR_PCTL2_RFSHTMG);
#endif

	sw_set_ack(dram);

	/* phy timing update */
	if (dst_fsp == 0)
		phy_offset = 0;
	else
		phy_offset = PHY_REG(0, 0x387 - 5 + (dst_fsp - 1) * 3);
	/* cl cwl al update */
	for (i = 0, find = 0; i < ARRAY_SIZE(phy_need_update_reg); i++) {
		for (j = find; sdram_params->phy_regs.phy[j][0] != 0xFFFFFFFF;
		     j++) {
			if (sdram_params->phy_regs.phy[j][0] ==
			    phy_need_update_reg[i]) {
				writel(sdram_params->phy_regs.phy[j][1],
				       phy_base + phy_offset +
				       phy_need_update_reg[i]);
				find = j;
				break;
			}
		}
	}

	set_ds_odt(dram, sdram_params, dst_fsp);
	if (dramtype == LPDDR4 || dramtype == LPDDR4X) {
		mr_tmp = readl(pctl_base + UMCTL2_REGS_FREQ(dst_fsp) +
			       DDR_PCTL2_INIT4);
		/* MR13 */
		pctl_write_mr(dram->pctl, 3, 13,
			      ((mr_tmp >> PCTL2_LPDDR4_MR13_SHIFT &
			       PCTL2_MR_MASK) & (~(BIT(7) | BIT(6)))) |
			      ((0x2 << 6) >> dst_fsp_lp4), dramtype);
		writel(((mr_tmp >> PCTL2_LPDDR4_MR13_SHIFT &
				      PCTL2_MR_MASK) & (~(BIT(7) | BIT(6)))) |
				      ((0x2 << 6) >> dst_fsp_lp4),
				       PHY_REG(phy_base, 0x1b));
		/* MR3 */
		pctl_write_mr(dram->pctl, 3, 3,
			      mr_tmp >> PCTL2_LPDDR234_MR3_SHIFT &
			      PCTL2_MR_MASK,
			      dramtype);
		writel(mr_tmp >> PCTL2_LPDDR234_MR3_SHIFT & PCTL2_MR_MASK,
		       PHY_REG(phy_base, 0x19));

		mr_tmp = readl(pctl_base + UMCTL2_REGS_FREQ(dst_fsp) +
			       DDR_PCTL2_INIT3);
		/* MR1 */
		pctl_write_mr(dram->pctl, 3, 1,
			      mr_tmp >> PCTL2_LPDDR234_MR1_SHIFT &
			      PCTL2_MR_MASK,
			      dramtype);
		writel(mr_tmp >> PCTL2_LPDDR234_MR1_SHIFT & PCTL2_MR_MASK,
		       PHY_REG(phy_base, 0x17));
		/* MR2 */
		pctl_write_mr(dram->pctl, 3, 2, mr_tmp & PCTL2_MR_MASK,
			      dramtype);
		writel(mr_tmp & PCTL2_MR_MASK,
		       PHY_REG(phy_base, 0x18));

		mr_tmp = readl(pctl_base + UMCTL2_REGS_FREQ(dst_fsp) +
			       DDR_PCTL2_INIT6);
		/* MR11 */
		pctl_write_mr(dram->pctl, 3, 11,
			      mr_tmp >> PCTL2_LPDDR4_MR11_SHIFT & PCTL2_MR_MASK,
			      dramtype);
		writel(mr_tmp >> PCTL2_LPDDR4_MR11_SHIFT & PCTL2_MR_MASK,
		       PHY_REG(phy_base, 0x1a));
		/* MR12 */
		pctl_write_mr(dram->pctl, 3, 12,
			      mr_tmp >> PCTL2_LPDDR4_MR12_SHIFT & PCTL2_MR_MASK,
			      dramtype);

		mr_tmp = readl(pctl_base + UMCTL2_REGS_FREQ(dst_fsp) +
			       DDR_PCTL2_INIT7);
		/* MR22 */
		pctl_write_mr(dram->pctl, 3, 22,
			      mr_tmp >> PCTL2_LPDDR4_MR22_SHIFT & PCTL2_MR_MASK,
			      dramtype);
		writel(mr_tmp >> PCTL2_LPDDR4_MR22_SHIFT & PCTL2_MR_MASK,
		       PHY_REG(phy_base, 0x1d));
		/* MR14 */
		pctl_write_mr(dram->pctl, 3, 14,
			      mr_tmp >> PCTL2_LPDDR4_MR14_SHIFT & PCTL2_MR_MASK,
			      dramtype);
		writel(mr_tmp >> PCTL2_LPDDR4_MR14_SHIFT & PCTL2_MR_MASK,
		       PHY_REG(phy_base, 0x1c));
	}

	update_noc_timing(dram, sdram_params);
}

static void save_fsp_param(struct dram_info *dram, u32 dst_fsp,
			   struct rv1126_sdram_params *sdram_params)
{
	void __iomem *pctl_base = dram->pctl;
	void __iomem *phy_base = dram->phy;
	struct rv1126_fsp_param *p_fsp_param = &fsp_param[dst_fsp];
	u32 temp, temp1;
	struct ddr2_3_4_lp2_3_info *ddr_info;

	ddr_info = get_ddr_drv_odt_info(sdram_params->base.dramtype);

	p_fsp_param->freq_mhz = sdram_params->base.ddr_freq;

	if (sdram_params->base.dramtype == LPDDR4 ||
	    sdram_params->base.dramtype == LPDDR4X) {
		p_fsp_param->rd_odt_up_en = 0;
		p_fsp_param->rd_odt_down_en = 1;
	} else {
		p_fsp_param->rd_odt_up_en =
			ODT_INFO_PULLUP_EN(ddr_info->odt_info);
		p_fsp_param->rd_odt_down_en =
			ODT_INFO_PULLDOWN_EN(ddr_info->odt_info);
	}

	if (p_fsp_param->rd_odt_up_en)
		p_fsp_param->rd_odt = readl(PHY_REG(phy_base, 0x111));
	else if (p_fsp_param->rd_odt_down_en)
		p_fsp_param->rd_odt = readl(PHY_REG(phy_base, 0x110));
	else
		p_fsp_param->rd_odt = 0;
	p_fsp_param->wr_dq_drv = readl(PHY_REG(phy_base, 0x112));
	p_fsp_param->wr_ca_drv = readl(PHY_REG(phy_base, 0x100));
	p_fsp_param->wr_ckcs_drv = readl(PHY_REG(phy_base, 0x102));
	p_fsp_param->vref_inner = readl(PHY_REG(phy_base, 0x128));
	p_fsp_param->vref_out = readl(PHY_REG(phy_base, 0x105));

	if (sdram_params->base.dramtype == DDR3) {
		temp = readl(pctl_base + UMCTL2_REGS_FREQ(dst_fsp) +
			     DDR_PCTL2_INIT3);
		temp = (temp >> PCTL2_DDR34_MR1_SHIFT) & PCTL2_MR_MASK;
		p_fsp_param->ds_pdds = temp & DDR3_DS_MASK;
		p_fsp_param->dq_odt = temp & DDR3_RTT_NOM_MASK;
		p_fsp_param->ca_odt = p_fsp_param->dq_odt;
	} else if (sdram_params->base.dramtype == DDR4) {
		temp = readl(pctl_base + UMCTL2_REGS_FREQ(dst_fsp) +
			     DDR_PCTL2_INIT3);
		temp = (temp >> PCTL2_DDR34_MR1_SHIFT) & PCTL2_MR_MASK;
		p_fsp_param->ds_pdds = temp & DDR4_DS_MASK;
		p_fsp_param->dq_odt = temp & DDR4_RTT_NOM_MASK;
		p_fsp_param->ca_odt = p_fsp_param->dq_odt;
	} else if (sdram_params->base.dramtype == LPDDR3) {
		temp = readl(pctl_base + UMCTL2_REGS_FREQ(dst_fsp) +
			     DDR_PCTL2_INIT4);
		temp = (temp >> PCTL2_LPDDR234_MR3_SHIFT) & PCTL2_MR_MASK;
		p_fsp_param->ds_pdds = temp & 0xf;

		p_fsp_param->dq_odt = lp3_odt_value;
		p_fsp_param->ca_odt = p_fsp_param->dq_odt;
	} else if (sdram_params->base.dramtype == LPDDR4 ||
		   sdram_params->base.dramtype == LPDDR4X) {
		temp = readl(pctl_base + UMCTL2_REGS_FREQ(dst_fsp) +
			     DDR_PCTL2_INIT4);
		temp = (temp >> PCTL2_LPDDR234_MR3_SHIFT) & PCTL2_MR_MASK;
		p_fsp_param->ds_pdds = temp & LPDDR4_PDDS_MASK;

		temp = readl(pctl_base + UMCTL2_REGS_FREQ(dst_fsp) +
			     DDR_PCTL2_INIT6);
		temp = (temp >> PCTL2_LPDDR4_MR11_SHIFT) & PCTL2_MR_MASK;
		p_fsp_param->dq_odt = temp & LPDDR4_DQODT_MASK;
		p_fsp_param->ca_odt = temp & LPDDR4_CAODT_MASK;

		temp = MAX(readl(PHY_REG(phy_base, 0x3ae)),
			   readl(PHY_REG(phy_base, 0x3ce)));
		temp1 = MIN(readl(PHY_REG(phy_base, 0x3be)),
			    readl(PHY_REG(phy_base, 0x3de)));
		p_fsp_param->vref_ca[0] = (temp + temp1) / 2;
		temp = MAX(readl(PHY_REG(phy_base, 0x3af)),
			   readl(PHY_REG(phy_base, 0x3cf)));
		temp1 = MIN(readl(PHY_REG(phy_base, 0x3bf)),
			    readl(PHY_REG(phy_base, 0x3df)));
		p_fsp_param->vref_ca[1] = (temp + temp1) / 2;
		p_fsp_param->vref_ca[0] |=
			(readl(PHY_REG(phy_base, 0x1e)) & BIT(6));
		p_fsp_param->vref_ca[1] |=
			(readl(PHY_REG(phy_base, 0x1e)) & BIT(6));

		p_fsp_param->lp4_drv_pd_en = (readl(PHY_REG(phy_base, 0x114)) >>
					      3) & 0x1;
	}

	p_fsp_param->noc_timings.ddrtiminga0 =
		sdram_params->ch.noc_timings.ddrtiminga0;
	p_fsp_param->noc_timings.ddrtimingb0 =
		sdram_params->ch.noc_timings.ddrtimingb0;
	p_fsp_param->noc_timings.ddrtimingc0 =
		sdram_params->ch.noc_timings.ddrtimingc0;
	p_fsp_param->noc_timings.devtodev0 =
		sdram_params->ch.noc_timings.devtodev0;
	p_fsp_param->noc_timings.ddrmode =
		sdram_params->ch.noc_timings.ddrmode;
	p_fsp_param->noc_timings.ddr4timing =
		sdram_params->ch.noc_timings.ddr4timing;
	p_fsp_param->noc_timings.agingx0 =
		sdram_params->ch.noc_timings.agingx0;
	p_fsp_param->noc_timings.aging0 =
		sdram_params->ch.noc_timings.aging0;
	p_fsp_param->noc_timings.aging1 =
		sdram_params->ch.noc_timings.aging1;
	p_fsp_param->noc_timings.aging2 =
		sdram_params->ch.noc_timings.aging2;
	p_fsp_param->noc_timings.aging3 =
		sdram_params->ch.noc_timings.aging3;

	p_fsp_param->flag = FSP_FLAG;
}

#ifndef CONFIG_SPL_KERNEL_BOOT
static void copy_fsp_param_to_ddr(void)
{
	memcpy((void *)FSP_PARAM_STORE_ADDR, (void *)&fsp_param,
	       sizeof(fsp_param));
}
#endif

static void pctl_modify_trfc(struct ddr_pctl_regs *pctl_regs,
			     struct sdram_cap_info *cap_info, u32 dram_type,
			     u32 freq)
{
	u64 cs0_cap;
	u32 die_cap;
	u32 trfc_ns, trfc4_ns;
	u32 trfc, txsnr;
	u32 txs_abort_fast = 0;
	u32 tmp;

	cs0_cap = sdram_get_cs_cap(cap_info, 0, dram_type);
	die_cap = (u32)(cs0_cap >> (20 + (cap_info->bw - cap_info->dbw)));

	switch (dram_type) {
	case DDR3:
		if (die_cap <= DIE_CAP_512MBIT)
			trfc_ns = 90;
		else if (die_cap <= DIE_CAP_1GBIT)
			trfc_ns = 110;
		else if (die_cap <= DIE_CAP_2GBIT)
			trfc_ns = 160;
		else if (die_cap <= DIE_CAP_4GBIT)
			trfc_ns = 260;
		else
			trfc_ns = 350;
		txsnr = MAX(5, ((trfc_ns + 10) * freq + 999) / 1000);
		break;

	case DDR4:
		if (die_cap <= DIE_CAP_2GBIT) {
			trfc_ns = 160;
			trfc4_ns = 90;
		} else if (die_cap <= DIE_CAP_4GBIT) {
			trfc_ns = 260;
			trfc4_ns = 110;
		} else if (die_cap <= DIE_CAP_8GBIT) {
			trfc_ns = 350;
			trfc4_ns = 160;
		} else {
			trfc_ns = 550;
			trfc4_ns = 260;
		}
		txsnr = ((trfc_ns + 10) * freq + 999) / 1000;
		txs_abort_fast = ((trfc4_ns + 10) * freq + 999) / 1000;
		break;

	case LPDDR3:
		if (die_cap <= DIE_CAP_4GBIT)
			trfc_ns = 130;
		else
			trfc_ns = 210;
		txsnr = MAX(2, ((trfc_ns + 10) * freq + 999) / 1000);
		break;

	case LPDDR4:
	case LPDDR4X:
		if (die_cap <= DIE_CAP_2GBIT)
			trfc_ns = 130;
		else if (die_cap <= DIE_CAP_4GBIT)
			trfc_ns = 180;
		else if (die_cap <= DIE_CAP_8GBIT)
			trfc_ns = 280;
		else
			trfc_ns = 380;
		txsnr = MAX(2, ((trfc_ns + 10) * freq + 999) / 1000);
		break;

	default:
		return;
	}
	trfc = (trfc_ns * freq + 999) / 1000;

	for (int i = 0; pctl_regs->pctl[i][0] != 0xffffffff; i++) {
		switch (pctl_regs->pctl[i][0]) {
		case DDR_PCTL2_RFSHTMG:
			tmp = pctl_regs->pctl[i][1];
			/* t_rfc_min */
			tmp &= ~((u32)0x3ff);
			tmp |= ((trfc + 1) / 2) & 0x3ff;
			pctl_regs->pctl[i][1] = tmp;
			break;

		case DDR_PCTL2_DRAMTMG8:
			if (dram_type == DDR3 || dram_type == DDR4) {
				tmp = pctl_regs->pctl[i][1];
				/* t_xs_x32 */
				tmp &= ~((u32)0x7f);
				tmp |= ((txsnr + 63) / 64) & 0x7f;

				if (dram_type == DDR4) {
					/* t_xs_abort_x32 */
					tmp &= ~((u32)(0x7f << 16));
					tmp |= (((txs_abort_fast + 63) / 64) & 0x7f) << 16;
					/* t_xs_fast_x32 */
					tmp &= ~((u32)(0x7f << 24));
					tmp |= (((txs_abort_fast + 63) / 64) & 0x7f) << 24;
				}

				pctl_regs->pctl[i][1] = tmp;
			}
			break;

		case DDR_PCTL2_DRAMTMG14:
			if (dram_type == LPDDR3 ||
			    dram_type == LPDDR4 || dram_type == LPDDR4X) {
				tmp = pctl_regs->pctl[i][1];
				/* t_xsr */
				tmp &= ~((u32)0xfff);
				tmp |= ((txsnr + 1) / 2) & 0xfff;
				pctl_regs->pctl[i][1] = tmp;
			}
			break;

		default:
			break;
		}
	}
}

void ddr_set_rate(struct dram_info *dram,
		  struct rv1126_sdram_params *sdram_params,
		  u32 freq, u32 cur_freq, u32 dst_fsp,
		  u32 dst_fsp_lp4, u32 training_en)
{
	u32 dest_dll_off, cur_init3, dst_init3, cur_fsp, cur_dll_off;
	u32 mr_tmp;
	u32 lp_stat;
	u32 dramtype = sdram_params->base.dramtype;
	struct rv1126_sdram_params *sdram_params_new;
	void __iomem *pctl_base = dram->pctl;
	void __iomem *phy_base = dram->phy;

	lp_stat = low_power_update(dram, 0);
	sdram_params_new = get_default_sdram_config(freq);
	sdram_params_new->ch.cap_info.rank = sdram_params->ch.cap_info.rank;
	sdram_params_new->ch.cap_info.bw = sdram_params->ch.cap_info.bw;

	pctl_modify_trfc(&sdram_params_new->pctl_regs,
			 &sdram_params->ch.cap_info, dramtype, freq);
	pre_set_rate(dram, sdram_params_new, dst_fsp, dst_fsp_lp4);

	while ((readl(pctl_base + DDR_PCTL2_STAT) &
			 PCTL2_OPERATING_MODE_MASK) ==
			 PCTL2_OPERATING_MODE_SR)
		continue;

	dest_dll_off = 0;
	dst_init3 = readl(pctl_base + UMCTL2_REGS_FREQ(dst_fsp) +
			  DDR_PCTL2_INIT3);
	if ((dramtype == DDR3 && (dst_init3 & 1)) ||
	    (dramtype == DDR4 && !(dst_init3 & 1)))
		dest_dll_off = 1;

	cur_fsp = readl(pctl_base + DDR_PCTL2_MSTR2) & 0x3;
	cur_init3 = readl(pctl_base + UMCTL2_REGS_FREQ(cur_fsp) +
			  DDR_PCTL2_INIT3);
	cur_init3 &= PCTL2_MR_MASK;
	cur_dll_off = 1;
	if ((dramtype == DDR3 && !(cur_init3 & 1)) ||
	    (dramtype == DDR4 && (cur_init3 & 1)))
		cur_dll_off = 0;

	if (!cur_dll_off) {
		if (dramtype == DDR3)
			cur_init3 |= 1;
		else
			cur_init3 &= ~1;
		pctl_write_mr(dram->pctl, 2, 1, cur_init3, dramtype);
	}

	setbits_le32(pctl_base + DDR_PCTL2_RFSHCTL3,
		     PCTL2_DIS_AUTO_REFRESH);
	update_refresh_reg(dram);

	enter_sr(dram, 1);

	writel(PMUGRF_CON_DDRPHY_BUFFEREN_MASK |
	       PMUGRF_CON_DDRPHY_BUFFEREN_EN,
	       &dram->pmugrf->soc_con[0]);
	sw_set_req(dram);
	clrbits_le32(pctl_base + DDR_PCTL2_DFIMISC,
		     PCTL2_DFI_INIT_COMPLETE_EN);
	sw_set_ack(dram);

	sw_set_req(dram);
	if ((dramtype == DDR3 || dramtype == DDR4) && dest_dll_off)
		setbits_le32(pctl_base + DDR_PCTL2_MSTR, PCTL2_DLL_OFF_MODE);
	else
		clrbits_le32(pctl_base + DDR_PCTL2_MSTR, PCTL2_DLL_OFF_MODE);

	setbits_le32(pctl_base + UMCTL2_REGS_FREQ(cur_fsp) + DDR_PCTL2_ZQCTL0,
		     PCTL2_DIS_SRX_ZQCL);
	setbits_le32(pctl_base + UMCTL2_REGS_FREQ(dst_fsp) + DDR_PCTL2_ZQCTL0,
		     PCTL2_DIS_SRX_ZQCL);
	sw_set_ack(dram);

	writel(DDR_MSCH_EN_MASK | (0x1 << DDR_MSCH_EN_SHIFT),
	       &dram->cru->clkgate_con[21]);
	writel(CLK_DDR_UPCTL_EN_MASK | ACLK_DDR_UPCTL_EN_MASK |
					(0x1 << CLK_DDR_UPCTL_EN_SHIFT) |
					(0x1 << ACLK_DDR_UPCTL_EN_SHIFT),
			BUS_SGRF_BASE_ADDR + SGRF_SOC_CON12);

	clrbits_le32(PHY_REG(phy_base, 0), ANALOG_DERESET | DIGITAL_DERESET);
	rkclk_set_dpll(dram, freq * MHz / 2);
	phy_pll_set(dram, freq * MHz, 0);
	phy_pll_set(dram, freq * MHz, 1);
	setbits_le32(PHY_REG(phy_base, 0), ANALOG_DERESET | DIGITAL_DERESET);

	writel(PMUGRF_CON_DDRPHY_BUFFEREN_MASK |
			PMUGRF_CON_DDRPHY_BUFFEREN_DIS,
			&dram->pmugrf->soc_con[0]);
	writel(DDR_MSCH_EN_MASK | (0x0 << DDR_MSCH_EN_SHIFT),
	       &dram->cru->clkgate_con[21]);
	writel(CLK_DDR_UPCTL_EN_MASK | ACLK_DDR_UPCTL_EN_MASK |
					(0x0 << CLK_DDR_UPCTL_EN_SHIFT) |
					(0x0 << ACLK_DDR_UPCTL_EN_SHIFT),
			BUS_SGRF_BASE_ADDR + SGRF_SOC_CON12);
	while ((readl(pctl_base + DDR_PCTL2_DFISTAT) &
	       PCTL2_DFI_INIT_COMPLETE) != PCTL2_DFI_INIT_COMPLETE)
		continue;

	sw_set_req(dram);
	setbits_le32(pctl_base + DDR_PCTL2_MSTR, 0x1 << 29);
	clrsetbits_le32(pctl_base + DDR_PCTL2_MSTR2, 0x3, dst_fsp);
	sw_set_ack(dram);
	update_refresh_reg(dram);
	clrsetbits_le32(PHY_REG(phy_base, 0xc), 0x3 << 2, dst_fsp << 2);

	enter_sr(dram, 0);

	setbits_le32(PHY_REG(phy_base, 0x71), 1 << 5);
	clrbits_le32(PHY_REG(phy_base, 0x71), 1 << 5);

	mr_tmp = readl(pctl_base + UMCTL2_REGS_FREQ(dst_fsp) + DDR_PCTL2_INIT4);
	if (dramtype == LPDDR3) {
		pctl_write_mr(dram->pctl, 3, 1,
			      (dst_init3 >> PCTL2_LPDDR234_MR1_SHIFT) &
			      PCTL2_MR_MASK,
			      dramtype);
		pctl_write_mr(dram->pctl, 3, 2, dst_init3 & PCTL2_MR_MASK,
			      dramtype);
		pctl_write_mr(dram->pctl, 3, 3,
			      (mr_tmp >> PCTL2_LPDDR234_MR3_SHIFT) &
			      PCTL2_MR_MASK,
			      dramtype);
		pctl_write_mr(dram->pctl, 3, 11, lp3_odt_value, dramtype);
	} else if ((dramtype == DDR3) || (dramtype == DDR4)) {
		pctl_write_mr(dram->pctl, 3, 1, dst_init3 & PCTL2_MR_MASK,
			      dramtype);
		if (!dest_dll_off) {
			pctl_write_mr(dram->pctl, 3, 0,
				      ((dst_init3 >> PCTL2_DDR34_MR0_SHIFT) &
				      PCTL2_MR_MASK) | DDR3_DLL_RESET,
				      dramtype);
			udelay(2);
		}
		pctl_write_mr(dram->pctl, 3, 0,
			      (dst_init3 >> PCTL2_DDR34_MR0_SHIFT &
			       PCTL2_MR_MASK) & (~DDR3_DLL_RESET),
			      dramtype);
		pctl_write_mr(dram->pctl, 3, 2,
			      ((mr_tmp >> PCTL2_DDR34_MR2_SHIFT) &
			       PCTL2_MR_MASK), dramtype);
		if (dramtype == DDR4) {
			pctl_write_mr(dram->pctl, 3, 3, mr_tmp & PCTL2_MR_MASK,
				      dramtype);
			mr_tmp = readl(pctl_base + UMCTL2_REGS_FREQ(dst_fsp) +
				       DDR_PCTL2_INIT6);
			pctl_write_mr(dram->pctl, 3, 4,
				      (mr_tmp >> PCTL2_DDR4_MR4_SHIFT) &
				       PCTL2_MR_MASK,
				      dramtype);
			pctl_write_mr(dram->pctl, 3, 5,
				      mr_tmp >> PCTL2_DDR4_MR5_SHIFT &
				      PCTL2_MR_MASK,
				      dramtype);

			mr_tmp = readl(pctl_base + UMCTL2_REGS_FREQ(dst_fsp) +
				       DDR_PCTL2_INIT7);
			pctl_write_mr(dram->pctl, 3, 6,
				      mr_tmp >> PCTL2_DDR4_MR6_SHIFT &
				      PCTL2_MR_MASK,
				      dramtype);
		}
	} else if (dramtype == LPDDR4 || dramtype == LPDDR4X) {
		pctl_write_mr(dram->pctl, 3, 13,
			      ((mr_tmp >> PCTL2_LPDDR4_MR13_SHIFT &
			       PCTL2_MR_MASK) & (~(BIT(7)))) |
			      dst_fsp_lp4 << 7, dramtype);
	}
	clrbits_le32(pctl_base + DDR_PCTL2_RFSHCTL3,
		     PCTL2_DIS_AUTO_REFRESH);
	update_refresh_reg(dram);

	/* training */
	high_freq_training(dram, sdram_params_new, dst_fsp);
	low_power_update(dram, lp_stat);

	save_fsp_param(dram, dst_fsp, sdram_params_new);
}

static void ddr_set_rate_for_fsp(struct dram_info *dram,
				 struct rv1126_sdram_params *sdram_params)
{
	struct ddr2_3_4_lp2_3_info *ddr_info;
	u32 f0;
	u32 dramtype = sdram_params->base.dramtype;
#ifndef CONFIG_SPL_KERNEL_BOOT
	u32 f1, f2, f3;
#endif

	ddr_info = get_ddr_drv_odt_info(dramtype);
	if (!ddr_info)
		return;

	f0 = (ddr_info->ddr_freq0_1 >> DDR_FREQ_F0_SHIFT) &
	     DDR_FREQ_MASK;

#ifndef CONFIG_SPL_KERNEL_BOOT
	memset((void *)FSP_PARAM_STORE_ADDR, 0, sizeof(fsp_param));
	memset((void *)&fsp_param, 0, sizeof(fsp_param));

	f1 = (ddr_info->ddr_freq0_1 >> DDR_FREQ_F1_SHIFT) &
	     DDR_FREQ_MASK;
	f2 = (ddr_info->ddr_freq2_3 >> DDR_FREQ_F2_SHIFT) &
	     DDR_FREQ_MASK;
	f3 = (ddr_info->ddr_freq2_3 >> DDR_FREQ_F3_SHIFT) &
	     DDR_FREQ_MASK;
#endif

	if (get_wrlvl_val(dram, sdram_params))
		printascii("get wrlvl value fail\n");

#ifndef CONFIG_SPL_KERNEL_BOOT
	printascii("change to: ");
	printdec(f1);
	printascii("MHz\n");
	ddr_set_rate(&dram_info, sdram_params, f1,
		     sdram_params->base.ddr_freq, 1, 1, 1);
	printascii("change to: ");
	printdec(f2);
	printascii("MHz\n");
	ddr_set_rate(&dram_info, sdram_params, f2, f1, 2, 0, 1);
	printascii("change to: ");
	printdec(f3);
	printascii("MHz\n");
	ddr_set_rate(&dram_info, sdram_params, f3, f2, 3, 1, 1);
#endif
	printascii("change to: ");
	printdec(f0);
	printascii("MHz(final freq)\n");
#ifndef CONFIG_SPL_KERNEL_BOOT
	ddr_set_rate(&dram_info, sdram_params, f0, f3, 0, 0, 1);
#else
	ddr_set_rate(&dram_info, sdram_params, f0, sdram_params->base.ddr_freq, 1, 1, 1);
#endif
}

int get_uart_config(void)
{
	struct sdram_head_info_index_v2 *index =
		(struct sdram_head_info_index_v2 *)common_info;
	struct global_info *gbl_info;

	gbl_info = (struct global_info *)((void *)common_info +
		index->global_index.offset * 4);

	return gbl_info->uart_info;
}

/* return: 0 = success, other = fail */
int sdram_init(void)
{
	struct rv1126_sdram_params *sdram_params;
	int ret = 0;
	struct sdram_head_info_index_v2 *index =
		(struct sdram_head_info_index_v2 *)common_info;
	struct global_info *gbl_info;

	dram_info.phy = (void *)DDR_PHY_BASE_ADDR;
	dram_info.pctl = (void *)UPCTL2_BASE_ADDR;
	dram_info.grf = (void *)GRF_BASE_ADDR;
	dram_info.cru = (void *)CRU_BASE_ADDR;
	dram_info.msch = (void *)SERVER_MSCH_BASE_ADDR;
	dram_info.ddrgrf = (void *)DDR_GRF_BASE_ADDR;
	dram_info.pmugrf = (void *)PMU_GRF_BASE_ADDR;

#ifdef CONFIG_ROCKCHIP_DRAM_EXTENDED_TEMP_SUPPORT
	printascii("extended temp support\n");
#endif
	if (index->version_info != 2 ||
	    (index->global_index.size != sizeof(struct global_info) / 4) ||
	    (index->ddr3_index.size !=
		sizeof(struct ddr2_3_4_lp2_3_info) / 4) ||
	    (index->ddr4_index.size !=
		sizeof(struct ddr2_3_4_lp2_3_info) / 4) ||
	    (index->lp3_index.size !=
		sizeof(struct ddr2_3_4_lp2_3_info) / 4) ||
	    (index->lp4_index.size != (sizeof(struct lp4_info) / 4)) ||
	    (index->lp4x_index.size != (sizeof(struct lp4_info) / 4)) ||
	    index->global_index.offset == 0 ||
	    index->ddr3_index.offset == 0 ||
	    index->ddr4_index.offset == 0 ||
	    index->lp3_index.offset == 0 ||
	    index->lp4_index.offset == 0 ||
	    index->lp4x_index.offset == 0) {
		printascii("common info error\n");
		goto error;
	}

	gbl_info = (struct global_info *)((void *)common_info +
		index->global_index.offset * 4);

	dram_info.sr_idle = SR_INFO(gbl_info->sr_pd_info);
	dram_info.pd_idle = PD_INFO(gbl_info->sr_pd_info);

	sdram_params = &sdram_configs[0];
	#if (CONFIG_ROCKCHIP_TPL_INIT_DRAM_TYPE == 8)
	for (j = 0; j < ARRAY_SIZE(sdram_configs); j++)
		sdram_configs[j].base.dramtype = LPDDR4X;
	#endif
	if (sdram_params->base.dramtype == DDR3 ||
	    sdram_params->base.dramtype == DDR4) {
		if (DDR_2T_INFO(gbl_info->info_2t))
			sdram_params->pctl_regs.pctl[0][1] |= 0x1 << 10;
		else
			sdram_params->pctl_regs.pctl[0][1] &=
				~(0x1 << 10);
	}
	ret = sdram_init_detect(&dram_info, sdram_params);
	if (ret) {
		sdram_print_dram_type(sdram_params->base.dramtype);
		printascii(", ");
		printdec(sdram_params->base.ddr_freq);
		printascii("MHz\n");
		goto error;
	}
	print_ddr_info(sdram_params);
#if defined(CONFIG_CMD_DDR_TEST_TOOL)
	init_rw_trn_result_struct(&rw_trn_result, dram_info.phy,
				  (u8)sdram_params->ch.cap_info.rank);
#endif

	ddr_set_rate_for_fsp(&dram_info, sdram_params);
#ifndef CONFIG_SPL_KERNEL_BOOT
	copy_fsp_param_to_ddr();
#endif

	ddr_set_atags(&dram_info, sdram_params);
#if defined(CONFIG_CMD_DDR_TEST_TOOL)
	save_rw_trn_result_to_ddr(&rw_trn_result);
#endif

	printascii("out\n");

	return ret;
error:
	printascii("error\n");
	return (-1);
}
#endif /* CONFIG_TPL_BUILD */
