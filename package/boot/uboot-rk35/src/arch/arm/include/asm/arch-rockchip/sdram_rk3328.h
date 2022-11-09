/*
 * Copyright (C) 2016-2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef _ASM_ARCH_SDRAM_RK3328_H
#define _ASM_ARCH_SDRAM_RK3328_H
#include <asm/arch/sdram_common.h>
#include <asm/arch/sdram_pctl_px30.h>
#include <asm/arch/sdram_phy_px30.h>
#include <asm/arch/sdram_phy_ron_rtt_px30.h>

#define SR_IDLE		93
#define PD_IDLE		13
#define SDRAM_ADDR	0x00000000

/* noc registers define */
#define DDRCONF				0x8
#define DDRTIMING			0xc
#define DDRMODE				0x10
#define READLATENCY			0x14
#define AGING0				0x18
#define AGING1				0x1c
#define AGING2				0x20
#define AGING3				0x24
#define AGING4				0x28
#define AGING5				0x2c
#define ACTIVATE			0x38
#define DEVTODEV			0x3c
#define DDR4TIMING			0x40

/* DDR GRF */
#define DDR_GRF_CON(n)		(0 + (n) * 4)
#define DDR_GRF_STATUS_BASE	(0X100)
#define DDR_GRF_STATUS(n)	(DDR_GRF_STATUS_BASE + (n) * 4)

/* CRU_SOFTRESET_CON5 */
#define ddrphy_psrstn_req(n)    (((0x1 << 15) << 16) | ((n) << 15))
#define ddrphy_srstn_req(n)     (((0x1 << 14) << 16) | ((n) << 14))
#define ddrctrl_psrstn_req(n)	(((0x1 << 13) << 16) | ((n) << 13))
#define ddrctrl_srstn_req(n)	(((0x1 << 12) << 16) | ((n) << 12))
#define ddrmsch_srstn_req(n)	(((0x1 << 11) << 16) | ((n) << 11))
#define msch_srstn_req(n)		(((0x1 << 9) << 16) | ((n) << 9))
#define dfimon_srstn_req(n)		(((0x1 << 8) << 16) | ((n) << 8))
#define grf_ddr_srstn_req(n)	(((0x1 << 7) << 16) | ((n) << 7))
/* CRU_SOFTRESET_CON9 */
#define ddrctrl_asrstn_req(n)		(((0x1 << 9) << 16) | ((n) << 9))

/* CRU register */
#define CRU_PLL_CON(pll_id, n)	((pll_id)  * 0x20 + (n) * 4)
#define CRU_MODE				(0x80)
#define CRU_GLB_CNT_TH			(0x90)
#define CRU_CLKSEL_CON_BASE		0x100
#define CRU_CLKSELS_CON(i)		(CRU_CLKSEL_CON_BASE + ((i) * 4))
#define CRU_CLKGATE_CON_BASE		0x200
#define CRU_CLKGATE_CON(i)		(CRU_CLKGATE_CON_BASE + ((i) * 4))
#define CRU_CLKSFTRST_CON_BASE	0x300
#define CRU_CLKSFTRST_CON(i)	(CRU_CLKSFTRST_CON_BASE + ((i) * 4))

/* CRU_PLL_CON0 */
#define PB(n)         ((0x1 << (15 + 16)) | ((n) << 15))
#define POSTDIV1(n)   ((0x7 << (12 + 16)) | ((n) << 12))
#define FBDIV(n)      ((0xFFF << 16) | (n))

/* CRU_PLL_CON1 */
#define RSTMODE(n)    ((0x1 << (15 + 16)) | ((n) << 15))
#define RST(n)        ((0x1 << (14 + 16)) | ((n) << 14))
#define PD(n)         ((0x1 << (13 + 16)) | ((n) << 13))
#define DSMPD(n)      ((0x1 << (12 + 16)) | ((n) << 12))
#define LOCK(n)       (((n) >> 10) & 0x1)
#define POSTDIV2(n)   ((0x7 << (6 + 16)) | ((n) << 6))
#define REFDIV(n)     ((0x3F << 16) | (n))

u16 ddr_cfg_2_rbc[] = {
	/*
	 * [5:4]  row(13+n)
	 * [3]    cs(0:0 cs, 1:2 cs)
	 * [2]  bank(0:0bank,1:8bank)
	 * [1:0]    col(11+n)
	 */
	/* row,        cs,       bank,   col */
	((3 << 4) | (0 << 3) | (1 << 2) | 0),
	((3 << 4) | (0 << 3) | (1 << 2) | 1),
	((2 << 4) | (0 << 3) | (1 << 2) | 2),
	((3 << 4) | (0 << 3) | (1 << 2) | 2),
	((2 << 4) | (0 << 3) | (1 << 2) | 3),
	((3 << 4) | (1 << 3) | (1 << 2) | 0),
	((3 << 4) | (1 << 3) | (1 << 2) | 1),
	((2 << 4) | (1 << 3) | (1 << 2) | 2),
	((3 << 4) | (0 << 3) | (0 << 2) | 1),
	((2 << 4) | (0 << 3) | (1 << 2) | 1),
};

u16 ddr4_cfg_2_rbc[] = {
	/***************************
	 * [6]	cs 0:0cs 1:2 cs
	 * [5:3]  row(13+n)
	 * [2]  cs(0:0 cs, 1:2 cs)
	 * [1]  bw    0: 16bit 1:32bit
	 * [0]  diebw 0:8bit 1:16bit
	 ***************************/
	/*  cs,       row,        cs,       bw,   diebw */
	((0 << 6) | (3 << 3) | (0 << 2) | (1 << 1) | 0),
	((1 << 6) | (2 << 3) | (0 << 2) | (1 << 1) | 0),
	((0 << 6) | (4 << 3) | (0 << 2) | (0 << 1) | 0),
	((1 << 6) | (3 << 3) | (0 << 2) | (0 << 1) | 0),
	((0 << 6) | (4 << 3) | (0 << 2) | (1 << 1) | 1),
	((1 << 6) | (3 << 3) | (0 << 2) | (1 << 1) | 1),
	((1 << 6) | (4 << 3) | (0 << 2) | (0 << 1) | 1),
	((0 << 6) | (2 << 3) | (1 << 2) | (1 << 1) | 0),
	((0 << 6) | (3 << 3) | (1 << 2) | (0 << 1) | 0),
	((0 << 6) | (3 << 3) | (1 << 2) | (1 << 1) | 1),
	((0 << 6) | (4 << 3) | (1 << 2) | (0 << 1) | 1),
};

u32 addrmap[21][9] = {
	/* map0  map1  map2  map3  map4  map5  map6  map7  map8 */
	{22, 0x00070707, 0x00000000, 0x1f000000, 0x00001f1f, 0x06060606,
		0x06060606, 0x00000f0f, 0x3f3f},
	{23, 0x00080808, 0x00000000, 0x00000000, 0x00001f1f, 0x07070707,
		0x07070707, 0x00000f0f, 0x3f3f},
	{23, 0x00090909, 0x00000000, 0x00000000, 0x00001f00, 0x08080808,
		0x0f080808, 0x00000f0f, 0x3f3f},
	{24, 0x00090909, 0x00000000, 0x00000000, 0x00001f00, 0x08080808,
		0x08080808, 0x00000f0f, 0x3f3f},
	{24, 0x000a0a0a, 0x00000000, 0x00000000, 0x00000000, 0x09090909,
		0x0f090909, 0x00000f0f, 0x3f3f},
	{6, 0x00070707, 0x00000000, 0x1f000000, 0x00001f1f, 0x07070707,
		0x07070707, 0x00000f0f, 0x3f3f},
	{7, 0x00080808, 0x00000000, 0x00000000, 0x00001f1f, 0x08080808,
		0x08080808, 0x00000f0f, 0x3f3f},
	{8, 0x00090909, 0x00000000, 0x00000000, 0x00001f00, 0x09090909,
		0x0f090909, 0x00000f0f, 0x3f3f},
	{22, 0x001f0808, 0x00000000, 0x00000000, 0x00001f1f, 0x06060606,
		0x06060606, 0x00000f0f, 0x3f3f},
	{23, 0x00080808, 0x00000000, 0x00000000, 0x00001f1f, 0x07070707,
		0x0f070707, 0x00000f0f, 0x3f3f},

	{24, 0x003f0a0a, 0x01010100, 0x01010101, 0x00001f1f, 0x08080808,
		0x08080808, 0x00000f0f, 0x0801},
	{23, 0x003f0a0a, 0x01010100, 0x01010101, 0x00001f1f, 0x08080808,
		0x0f080808, 0x00000f0f, 0x0801},
	{24, 0x003f0909, 0x00000007, 0x1f000000, 0x00001f1f, 0x07070707,
		0x07070707, 0x00000f07, 0x0700},
	{23, 0x003f0909, 0x00000007, 0x1f000000, 0x00001f1f, 0x07070707,
		0x07070707, 0x00000f0f, 0x0700},
	{24, 0x003f0909, 0x01010100, 0x01010101, 0x00001f1f, 0x07070707,
		0x07070707, 0x00000f07, 0x3f01},
	{23, 0x003f0909, 0x01010100, 0x01010101, 0x00001f1f, 0x07070707,
		0x07070707, 0x00000f0f, 0x3f01},
	{24, 0x003f0808, 0x00000007, 0x1f000000, 0x00001f1f, 0x06060606,
		0x06060606, 0x00000f06, 0x3f00},
	{8, 0x003f0a0a, 0x01010100, 0x01010101, 0x00001f1f, 0x09090909,
		0x0f090909, 0x00000f0f, 0x0801},
	{7, 0x003f0909, 0x00000007, 0x1f000000, 0x00001f1f, 0x08080808,
		0x08080808, 0x00000f0f, 0x0700},
	{7, 0x003f0909, 0x01010100, 0x01010101, 0x00001f1f, 0x08080808,
		0x08080808, 0x00000f0f, 0x3f01},

	{6, 0x003f0808, 0x00000007, 0x1f000000, 0x00001f1f, 0x07070707,
		0x07070707, 0x00000f07, 0x3f00}
};

struct rk3328_ddr_grf_regs {
	u32 ddr_grf_con[4];
	u32 reserved[(0x100 - 0x10) / 4];
	u32 ddr_grf_status[11];
};

union noc_ddrtiming {
	u32 d32;
	struct {
		unsigned acttoact:6;
		unsigned rdtomiss:6;
		unsigned wrtomiss:6;
		unsigned burstlen:3;
		unsigned rdtowr:5;
		unsigned wrtord:5;
		unsigned bwratio:1;
	} b;
};

union noc_activate {
	u32 d32;
	struct {
		unsigned rrd:4;
		unsigned faw:6;
		unsigned fawbank:1;
		unsigned reserved1:21;
	} b;
};

union noc_devtodev {
	u32 d32;
	struct {
		unsigned busrdtord:2;
		unsigned busrdtowr:2;
		unsigned buswrtord:2;
		unsigned reserved2:26;
	} b;
};

union noc_ddr4timing {
	u32 d32;
	struct {
		unsigned ccdl:3;
		unsigned wrtordl:5;
		unsigned rrdl:4;
		unsigned reserved2:20;
	} b;
};

union noc_ddrmode {
	u32 d32;
	struct {
		unsigned autoprecharge:1;
		unsigned bwratioextended:1;
		unsigned reserved3:30;
	} b;
};

struct msch_regs {
	u32 coreid;
	u32 revisionid;
	u32 ddrconf;
	u32 ddrtiming;
	u32 ddrmode;
	u32 readlatency;
	u32 aging0;
	u32 aging1;
	u32 aging2;
	u32 aging3;
	u32 aging4;
	u32 aging5;
	u32 reserved[2];
	u32 activate;
	u32 devtodev;
	u32 ddr4_timing;
};

struct sdram_msch_timings {
	union noc_ddrtiming ddrtiming;
	union noc_ddrmode ddrmode;
	u32 readlatency;
	union noc_activate activate;
	union noc_devtodev devtodev;
	union noc_ddr4timing ddr4timing;
	u32 agingx0;
};

struct rk3328_sdram_channel {
	struct sdram_cap_info cap_info;
	struct sdram_msch_timings noc_timings;
};

struct rk3328_sdram_params {
	struct rk3328_sdram_channel ch;
	struct sdram_base_params base;
	struct ddr_pctl_regs pctl_regs;
	struct ddr_phy_regs phy_regs;
	struct ddr_phy_skew skew;
};

#endif
