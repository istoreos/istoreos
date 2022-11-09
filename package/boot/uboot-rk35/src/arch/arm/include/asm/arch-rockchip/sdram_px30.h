/* SPDX-License-Identifier:     GPL-2.0+ */
/*
 * Copyright (C) 2018 Rockchip Electronics Co., Ltd
 */

#ifndef _ASM_ARCH_SDRAM_PX30_H
#define _ASM_ARCH_SDRAM_PX30_H
#include <asm/arch/sdram_common.h>
#include <asm/arch/sdram_msch.h>
#include <asm/arch/sdram_pctl_px30.h>
#include <asm/arch/sdram_phy_px30.h>
#include <asm/arch/sdram_phy_ron_rtt_px30.h>

#define SR_IDLE				93
#define PD_IDLE				13

/* PMUGRF */
#define PMUGRF_OS_REG0			(0x200)
#define PMUGRF_OS_REG(n)		(PMUGRF_OS_REG0 + (n) * 4)

/* DDR GRF */
#define DDR_GRF_CON(n)			(0 + (n) * 4)
#define DDR_GRF_STATUS_BASE		(0X100)
#define DDR_GRF_STATUS(n)		(DDR_GRF_STATUS_BASE + (n) * 4)
#define DDR_GRF_LP_CON			(0x20)

#define SPLIT_MODE_32_L16_VALID		(0)
#define SPLIT_MODE_32_H16_VALID		(1)
#define SPLIT_MODE_16_L8_VALID		(2)
#define SPLIT_MODE_16_H8_VALID		(3)

#define DDR_GRF_SPLIT_CON		(0x8)
#define SPLIT_MODE_MASK			(0x3)
#define SPLIT_MODE_OFFSET		(9)
#define SPLIT_BYPASS_MASK		(1)
#define SPLIT_BYPASS_OFFSET		(8)
#define SPLIT_SIZE_MASK			(0xff)
#define SPLIT_SIZE_OFFSET		(0)

/* CRU define */
/* CRU_PLL_CON0 */
#define PB(n)				((0x1 << (15 + 16)) | ((n) << 15))
#define POSTDIV1(n)			((0x7 << (12 + 16)) | ((n) << 12))
#define FBDIV(n)			((0xFFF << 16) | (n))

/* CRU_PLL_CON1 */
#define RSTMODE(n)			((0x1 << (15 + 16)) | ((n) << 15))
#define RST(n)				((0x1 << (14 + 16)) | ((n) << 14))
#define PD(n)				((0x1 << (13 + 16)) | ((n) << 13))
#define DSMPD(n)			((0x1 << (12 + 16)) | ((n) << 12))
#define LOCK(n)				(((n) >> 10) & 0x1)
#define POSTDIV2(n)			((0x7 << (6 + 16)) | ((n) << 6))
#define REFDIV(n)			((0x3F << 16) | (n))

/* CRU_MODE */
#define CLOCK_FROM_XIN_OSC		(0)
#define CLOCK_FROM_PLL			(1)
#define CLOCK_FROM_RTC_32K		(2)
#define DPLL_MODE(n)			((0x3 << (4 + 16)) | ((n) << 4))

/* CRU_SOFTRESET_CON1 */
#define upctl2_psrstn_req(n)		(((0x1 << 6) << 16) | ((n) << 6))
#define upctl2_asrstn_req(n)		(((0x1 << 5) << 16) | ((n) << 5))
#define upctl2_srstn_req(n)		(((0x1 << 4) << 16) | ((n) << 4))

/* CRU_SOFTRESET_CON2 */
#define ddrphy_psrstn_req(n)		(((0x1 << 2) << 16) | ((n) << 2))
#define ddrphy_srstn_req(n)		(((0x1 << 0) << 16) | ((n) << 0))

/* CRU register */
#define CRU_PLL_CON(pll_id, n)		((pll_id)  * 0x20 + (n) * 4)
#define CRU_MODE			(0xa0)
#define CRU_GLB_CNT_TH			(0xb0)
#define CRU_CLKSEL_CON_BASE		0x100
#define CRU_CLKSELS_CON(i)		(CRU_CLKSEL_CON_BASE + ((i) * 4))
#define CRU_CLKGATE_CON_BASE		0x200
#define CRU_CLKGATE_CON(i)		(CRU_CLKGATE_CON_BASE + ((i) * 4))
#define CRU_CLKSFTRST_CON_BASE		0x300
#define CRU_CLKSFTRST_CON(i)		(CRU_CLKSFTRST_CON_BASE + ((i) * 4))

u8 ddr_cfg_2_rbc[] = {
	/*
	 * [6:4] max row: 13+n
	 * [3]  bank(0:4bank,1:8bank)
	 * [2:0]    col(10+n)
	 */
	((5 << 4) | (1 << 3) | 0), /* 0 */
	((5 << 4) | (1 << 3) | 1), /* 1 */
	((4 << 4) | (1 << 3) | 2), /* 2 */
	((3 << 4) | (1 << 3) | 3), /* 3 */
	((2 << 4) | (1 << 3) | 4), /* 4 */
	((5 << 4) | (0 << 3) | 2), /* 5 */
	((4 << 4) | (1 << 3) | 2), /* 6 */
	/*((0<<3)|3),*/	 /* 12 for ddr4 */
	/*((1<<3)|1),*/  /* 13 B,C exchange for rkvdec */
};

/*
 * for ddr4 if ddrconfig=7, upctl should set 7 and noc should
 * set to 1 for more efficient.
 * noc ddrconf, upctl addrmap
 * 1  7
 * 2  8
 * 3  9
 * 12 10
 * 5  11
 */
u8 d4_rbc_2_d3_rbc[] = {
	1, /* 7 */
	2, /* 8 */
	3, /* 9 */
	12, /* 10 */
	5, /* 11 */
};

/*
 * row higher than cs should be disabled by set to 0xf
 * rank addrmap calculate by real cap.
 */
u32 addrmap[][8] = {
	/* map0 map1,   map2,       map3,       map4,      map5
	 * map6,        map7,       map8
	 * -------------------------------------------------------
	 * bk2-0       col 5-2     col 9-6    col 11-10   row 11-0
	 * row 15-12   row 17-16   bg1,0
	 * -------------------------------------------------------
	 * 4,3,2       5-2         9-6                    6
	 *                         3,2
	 */
	{0x00060606, 0x00000000, 0x1f1f0000, 0x00001f1f, 0x05050505,
		0x05050505, 0x00000505, 0x3f3f}, /* 0 */
	{0x00070707, 0x00000000, 0x1f000000, 0x00001f1f, 0x06060606,
		0x06060606, 0x06060606, 0x3f3f}, /* 1 */
	{0x00080808, 0x00000000, 0x00000000, 0x00001f1f, 0x07070707,
		0x07070707, 0x00000f07, 0x3f3f}, /* 2 */
	{0x00090909, 0x00000000, 0x00000000, 0x00001f00, 0x08080808,
		0x08080808, 0x00000f0f, 0x3f3f}, /* 3 */
	{0x000a0a0a, 0x00000000, 0x00000000, 0x00000000, 0x09090909,
		0x0f090909, 0x00000f0f, 0x3f3f}, /* 4 */
	{0x00080808, 0x00000000, 0x00000000, 0x00001f1f, 0x06060606,
		0x06060606, 0x00000606, 0x3f3f}, /* 5 */
	{0x00080808, 0x00000000, 0x00000000, 0x00001f1f, 0x07070707,
		0x07070707, 0x00000f0f, 0x3f3f}, /* 6 */
	{0x003f0808, 0x00000006, 0x1f1f0000, 0x00001f1f, 0x06060606,
		0x06060606, 0x00000606, 0x0600}, /* 7 */
	{0x003f0909, 0x00000007, 0x1f000000, 0x00001f1f, 0x07070707,
		0x07070707, 0x00000f07, 0x0700}, /* 8 */
	{0x003f0a0a, 0x01010100, 0x01010101, 0x00001f1f, 0x08080808,
		0x08080808, 0x00000f0f, 0x0801}, /* 9 */
	{0x003f0909, 0x01010100, 0x01010101, 0x00001f1f, 0x07070707,
		0x07070707, 0x00000f07, 0x3f01}, /* 10 */
	{0x003f0808, 0x00000007, 0x1f000000, 0x00001f1f, 0x06060606,
		0x06060606, 0x00000606, 0x3f00}, /* 11 */
	/* when ddr4 12 map to 10, when ddr3 12 unused */
	{0x003f0909, 0x01010100, 0x01010101, 0x00001f1f, 0x07070707,
		0x07070707, 0x00000f07, 0x3f01}, /* 10 */
	{0x00070706, 0x00000000, 0x1f010000, 0x00001f1f, 0x06060606,
		0x06060606, 0x00000606, 0x3f3f}, /* 13 */
};

struct px30_ddr_grf_regs {
	u32 ddr_grf_con[4];
	u32 reserved1[(0x20 - 0x10) / 4];
	u32 ddr_grf_lp_con;
	u32 reserved2[(0x100 - 0x24) / 4];
	u32 ddr_grf_status[11];
};

struct msch_regs {
	u32 coreid;
	u32 revisionid;
	u32 deviceconf;
	u32 devicesize;
	u32 ddrtiminga0;
	u32 ddrtimingb0;
	u32 ddrtimingc0;
	u32 devtodev0;
	u32 reserved1[(0x110 - 0x20) / 4];
	u32 ddrmode;
	u32 ddr4timing;
	u32 reserved2[(0x1000 - 0x118) / 4];
	u32 agingx0;
	u32 reserved3[(0x1040 - 0x1004) / 4];
	u32 aging0;
	u32 aging1;
	u32 aging2;
	u32 aging3;
};

struct sdram_msch_timings {
	union noc_ddrtiminga0 ddrtiminga0;
	union noc_ddrtimingb0 ddrtimingb0;
	union noc_ddrtimingc0 ddrtimingc0;
	union noc_devtodev0 devtodev0;
	union noc_ddrmode ddrmode;
	union noc_ddr4timing ddr4timing;
	u32 agingx0;
};

struct px30_sdram_channel {
	struct sdram_cap_info cap_info;
	struct sdram_msch_timings noc_timings;
};

struct px30_sdram_params {
	struct px30_sdram_channel ch;
	struct sdram_base_params base;
	struct ddr_pctl_regs pctl_regs;
	struct ddr_phy_regs phy_regs;
	struct ddr_phy_skew *skew;
};
#endif
