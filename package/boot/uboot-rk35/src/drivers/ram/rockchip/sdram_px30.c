// SPDX-License-Identifier: GPL-2.0
/*
 * (C) Copyright 2018 Rockchip Electronics Co., Ltd.
 */

#include <common.h>
#include <debug_uart.h>
#include <dm.h>
#include <ram.h>
#include <syscon.h>
#include <asm/io.h>
#include <asm/arch-rockchip/clock.h>
#include <asm/arch-rockchip/cru_px30.h>
#include <asm/arch-rockchip/grf_px30.h>
#include <asm/arch-rockchip/hardware.h>
#include <asm/arch-rockchip/sdram.h>
#include <asm/arch-rockchip/sdram_px30.h>

/*
 * Because px30 sram size is small, so need define CONFIG_TPL_TINY_FRAMEWORK
 * to reduce TPL size when build TPL firmware.
 */
#ifdef CONFIG_TPL_BUILD
#ifndef CONFIG_TPL_TINY_FRAMEWORK
#error please defined CONFIG_TPL_TINY_FRAMEWORK for px30 !!!
#endif
#endif

#ifdef CONFIG_TPL_BUILD

DECLARE_GLOBAL_DATA_PTR;
struct dram_info {
	struct ddr_pctl_regs *pctl;
	struct ddr_phy_regs *phy;
	struct px30_cru *cru;
	struct msch_regs *msch;
	struct px30_ddr_grf_regs *ddr_grf;
	struct px30_grf *grf;
	struct ram_info info;
	struct px30_pmugrf *pmugrf;
};

#define PMUGRF_BASE_ADDR		0xFF010000
#define CRU_BASE_ADDR			0xFF2B0000
#define GRF_BASE_ADDR			0xFF140000
#define DDRC_BASE_ADDR			0xFF600000
#define DDR_PHY_BASE_ADDR		0xFF2A0000
#define SERVER_MSCH0_BASE_ADDR		0xFF530000
#define DDR_GRF_BASE_ADDR		0xff630000

struct dram_info dram_info;

struct px30_sdram_params sdram_configs[] = {
#ifdef CONFIG_ROCKCHIP_RK3326
#include	"sdram-px30-lpddr3-detect-333.inc"
#else
#include	"sdram-px30-ddr3-detect-333.inc"
#endif
};

struct ddr_phy_skew skew = {
#include	"sdram-px30-ddr_skew.inc"
};

static void rkclk_ddr_reset(struct dram_info *dram,
			    u32 ctl_srstn, u32 ctl_psrstn,
			    u32 phy_srstn, u32 phy_psrstn)
{
	writel(upctl2_srstn_req(ctl_srstn) | upctl2_psrstn_req(ctl_psrstn) |
	       upctl2_asrstn_req(ctl_srstn),
	       &dram->cru->softrst_con[1]);
	writel(ddrphy_srstn_req(phy_srstn) | ddrphy_psrstn_req(phy_psrstn),
	       &dram->cru->softrst_con[2]);
}

static void rkclk_set_dpll(struct dram_info *dram, unsigned int hz)
{
	unsigned int refdiv, postdiv1, postdiv2, fbdiv;
	int delay = 1000;
	u32 mhz = hz / MHz;

	refdiv = 1;
	if (mhz <= 300) {
		postdiv1 = 4;
		postdiv2 = 2;
	} else if (mhz <= 400) {
		postdiv1 = 6;
		postdiv2 = 1;
	} else if (mhz <= 600) {
		postdiv1 = 4;
		postdiv2 = 1;
	} else if (mhz <= 800) {
		postdiv1 = 3;
		postdiv2 = 1;
	} else if (mhz <= 1600) {
		postdiv1 = 2;
		postdiv2 = 1;
	} else {
		postdiv1 = 1;
		postdiv2 = 1;
	}
	fbdiv = (mhz * refdiv * postdiv1 * postdiv2) / 24;

	writel(DPLL_MODE(CLOCK_FROM_XIN_OSC), &dram->cru->mode);

	writel(POSTDIV1(postdiv1) | FBDIV(fbdiv), &dram->cru->pll[1].con0);
	writel(DSMPD(1) | POSTDIV2(postdiv2) | REFDIV(refdiv),
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
				struct px30_sdram_params *sdram_params)
{
	/* for inno ddr phy need 2*freq */
	rkclk_set_dpll(dram,  sdram_params->base.ddr_freq * MHz * 2);
}

/* return ddrconfig value
 *       (-1), find ddrconfig fail
 *       other, the ddrconfig value
 * only support cs0_row >= cs1_row
 */
static unsigned int calculate_ddrconfig(struct px30_sdram_params *sdram_params)
{
	struct sdram_cap_info *cap_info = &sdram_params->ch.cap_info;
	u32 bw, die_bw, col, bank;
	u32 i, tmp;
	u32 ddrconf = -1;

	bw = cap_info->bw;
	die_bw = cap_info->dbw;
	col = cap_info->col;
	bank = cap_info->bk;

	if (sdram_params->base.dramtype == DDR4) {
		if (die_bw == 0)
			ddrconf = 7 + bw;
		else
			ddrconf = 12 - bw;
		ddrconf = d4_rbc_2_d3_rbc[ddrconf - 7];
	} else {
		tmp = ((bank - 2) << 3) | (col + bw - 10);
		for (i = 0; i < 7; i++)
			if ((ddr_cfg_2_rbc[i] & 0xf) == tmp) {
				ddrconf = i;
				break;
			}
		if (i > 6)
			printascii("calculate ddrconfig error\n");
	}

	return ddrconf;
}

/*
 * calculate controller dram address map, and setting to register.
 * argument sdram_params->ch.ddrconf must be right value before
 * call this function.
 */
static void set_ctl_address_map(struct dram_info *dram,
				struct px30_sdram_params *sdram_params)
{
	struct sdram_cap_info *cap_info = &sdram_params->ch.cap_info;
	void __iomem *pctl_base = dram->pctl;
	u32 cs_pst, bg, max_row, ddrconf;
	u32 i;

	if (sdram_params->base.dramtype == DDR4)
		/*
		 * DDR4 8bit dram BG = 2(4bank groups),
		 * 16bit dram BG = 1 (2 bank groups)
		 */
		bg = (cap_info->dbw == 0) ? 2 : 1;
	else
		bg = 0;

	cs_pst = cap_info->bw + cap_info->col +
		bg + cap_info->bk + cap_info->cs0_row;
	if (cs_pst >= 32 || cap_info->rank == 1)
		writel(0x1f, pctl_base + DDR_PCTL2_ADDRMAP0);
	else
		writel(cs_pst - 8, pctl_base + DDR_PCTL2_ADDRMAP0);

	ddrconf = cap_info->ddrconfig;
	if (sdram_params->base.dramtype == DDR4) {
		for (i = 0; i < ARRAY_SIZE(d4_rbc_2_d3_rbc); i++) {
			if (d4_rbc_2_d3_rbc[i] == ddrconf) {
				ddrconf = 7 + i;
				break;
			}
		}
	}

	sdram_copy_to_reg((u32 *)(pctl_base + DDR_PCTL2_ADDRMAP1),
			  &addrmap[ddrconf][0], 8 * 4);
	max_row = cs_pst - 1 - 8 - (addrmap[ddrconf][5] & 0xf);

	if (max_row < 12)
		printascii("set addrmap fail\n");
	/* need to disable row ahead of rank by set to 0xf */
	for (i = 17; i > max_row; i--)
		clrsetbits_le32(pctl_base + DDR_PCTL2_ADDRMAP6 +
			((i - 12) * 8 / 32) * 4,
			0xf << ((i - 12) * 8 % 32),
			0xf << ((i - 12) * 8 % 32));

	if ((sdram_params->base.dramtype == LPDDR3 ||
	     sdram_params->base.dramtype == LPDDR2) &&
		 cap_info->row_3_4)
		setbits_le32(pctl_base + DDR_PCTL2_ADDRMAP6, 1 << 31);
	if (sdram_params->base.dramtype == DDR4 && cap_info->bw != 0x2)
		setbits_le32(pctl_base + DDR_PCTL2_PCCFG, 1 << 8);
}

/*
 * rank = 1: cs0
 * rank = 2: cs1
 */
int read_mr(struct dram_info *dram, u32 rank, u32 mr_num)
{
	void __iomem *ddr_grf_base = dram->ddr_grf;

	pctl_read_mr(dram->pctl, rank, mr_num);

	return (readl(ddr_grf_base + DDR_GRF_STATUS(0)) & 0xff);
}

#define MIN(a, b)	(((a) > (b)) ? (b) : (a))
#define MAX(a, b)	(((a) > (b)) ? (a) : (b))
static u32 check_rd_gate(struct dram_info *dram)
{
	void __iomem *phy_base = dram->phy;

	u32 max_val = 0;
	u32 min_val = 0xff;
	u32 gate[4];
	u32 i, bw;

	bw = (readl(PHY_REG(phy_base, 0x0)) >> 4) & 0xf;
	switch (bw) {
	case 0x1:
		bw = 1;
		break;
	case 0x3:
		bw = 2;
		break;
	case 0xf:
	default:
		bw = 4;
		break;
	}

	for (i = 0; i < bw; i++) {
		gate[i] = readl(PHY_REG(phy_base, 0xfb + i));
		max_val = MAX(max_val, gate[i]);
		min_val = MIN(min_val, gate[i]);
	}

	if (max_val > 0x80 || min_val < 0x20)
		return -1;
	else
		return 0;
}

static int data_training(struct dram_info *dram, u32 cs, u32 dramtype)
{
	void __iomem *pctl_base = dram->pctl;
	u32 dis_auto_zq = 0;
	u32 pwrctl;
	u32 ret;

	/* disable auto low-power */
	pwrctl = readl(pctl_base + DDR_PCTL2_PWRCTL);
	writel(0, pctl_base + DDR_PCTL2_PWRCTL);

	dis_auto_zq = pctl_dis_zqcs_aref(dram->pctl);

	ret = phy_data_training(dram->phy, cs, dramtype);

	pctl_rest_zqcs_aref(dram->pctl, dis_auto_zq);

	/* restore auto low-power */
	writel(pwrctl, pctl_base + DDR_PCTL2_PWRCTL);

	return ret;
}

static void dram_set_bw(struct dram_info *dram, u32 bw)
{
	phy_dram_set_bw(dram->phy, bw);
}

static void set_ddrconfig(struct dram_info *dram, u32 ddrconfig)
{
	writel(ddrconfig | (ddrconfig << 8), &dram->msch->deviceconf);
	rk_clrsetreg(&dram->grf->soc_noc_con[1], 0x3 << 14, 0 << 14);
}

static void sdram_msch_config(struct msch_regs *msch,
			      struct sdram_msch_timings *noc_timings,
			      struct sdram_cap_info *cap_info,
			      struct sdram_base_params *base)
{
	u64 cs_cap[2];

	cs_cap[0] = sdram_get_cs_cap(cap_info, 0, base->dramtype);
	cs_cap[1] = sdram_get_cs_cap(cap_info, 1, base->dramtype);
	writel(((((cs_cap[1] >> 20) / 64) & 0xff) << 8) |
			(((cs_cap[0] >> 20) / 64) & 0xff),
			&msch->devicesize);

	writel(noc_timings->ddrtiminga0.d32,
	       &msch->ddrtiminga0);
	writel(noc_timings->ddrtimingb0.d32,
	       &msch->ddrtimingb0);
	writel(noc_timings->ddrtimingc0.d32,
	       &msch->ddrtimingc0);
	writel(noc_timings->devtodev0.d32,
	       &msch->devtodev0);
	writel(noc_timings->ddrmode.d32, &msch->ddrmode);
	writel(noc_timings->ddr4timing.d32,
	       &msch->ddr4timing);
	writel(noc_timings->agingx0, &msch->agingx0);
	writel(noc_timings->agingx0, &msch->aging0);
	writel(noc_timings->agingx0, &msch->aging1);
	writel(noc_timings->agingx0, &msch->aging2);
	writel(noc_timings->agingx0, &msch->aging3);
}

static void dram_all_config(struct dram_info *dram,
			    struct px30_sdram_params *sdram_params)
{
	struct sdram_cap_info *cap_info = &sdram_params->ch.cap_info;
	u32 sys_reg2 = 0;
	u32 sys_reg3 = 0;

	set_ddrconfig(dram, cap_info->ddrconfig);
	sdram_org_config(cap_info, &sdram_params->base, &sys_reg2,
			 &sys_reg3, 0);
	writel(sys_reg2, &dram->pmugrf->os_reg[2]);
	writel(sys_reg3, &dram->pmugrf->os_reg[3]);
	sdram_msch_config(dram->msch, &sdram_params->ch.noc_timings, cap_info,
			  &sdram_params->base);
}

static void enable_low_power(struct dram_info *dram,
			     struct px30_sdram_params *sdram_params)
{
	void __iomem *pctl_base = dram->pctl;
	void __iomem *phy_base = dram->phy;
	void __iomem *ddr_grf_base = dram->ddr_grf;
	u32 grf_lp_con;

	/*
	 * bit0: grf_upctl_axi_cg_en = 1 enable upctl2 axi clk auto gating
	 * bit1: grf_upctl_apb_cg_en = 1 ungated axi,core clk for apb access
	 * bit2: grf_upctl_core_cg_en = 1 enable upctl2 core clk auto gating
	 * bit3: grf_selfref_type2_en = 0 disable core clk gating when type2 sr
	 * bit4: grf_upctl_syscreq_cg_en = 1
	 *       ungating coreclk when c_sysreq assert
	 * bit8-11: grf_auto_sr_dly = 6
	 */
	writel(0x1f1f0617, &dram->ddr_grf->ddr_grf_con[1]);

	if (sdram_params->base.dramtype == DDR4)
		grf_lp_con = (0x7 << 16) | (1 << 1);
	else if (sdram_params->base.dramtype == DDR3)
		grf_lp_con = (0x7 << 16) | (1 << 0);
	else
		grf_lp_con = (0x7 << 16) | (1 << 2);

	/* en lpckdis_en */
	grf_lp_con = grf_lp_con | (0x1 << (9 + 16)) | (0x1 << 9);
	writel(grf_lp_con, ddr_grf_base + DDR_GRF_LP_CON);

	/* off digit module clock when enter power down */
	setbits_le32(PHY_REG(phy_base, 7), 1 << 7);

	/* enable sr, pd */
	if (PD_IDLE == 0)
		clrbits_le32(pctl_base + DDR_PCTL2_PWRCTL, (1 << 1));
	else
		setbits_le32(pctl_base + DDR_PCTL2_PWRCTL, (1 << 1));
	if (SR_IDLE == 0)
		clrbits_le32(pctl_base + DDR_PCTL2_PWRCTL, 1);
	else
		setbits_le32(pctl_base + DDR_PCTL2_PWRCTL, 1);
	setbits_le32(pctl_base + DDR_PCTL2_PWRCTL, (1 << 3));
}

/*
 * pre_init: 0: pre init for dram cap detect
 * 1: detect correct cap(except cs1 row)info, than reinit
 * 2: after reinit, we detect cs1_row, if cs1_row not equal
 *    to cs0_row and cs is in middle on ddrconf map, we need
 *    to reinit dram, than set the correct ddrconf.
 */
static int sdram_init_(struct dram_info *dram,
		       struct px30_sdram_params *sdram_params, u32 pre_init)
{
	struct sdram_cap_info *cap_info = &sdram_params->ch.cap_info;
	void __iomem *pctl_base = dram->pctl;

	rkclk_ddr_reset(dram, 1, 1, 1, 1);
	udelay(10);
	/*
	 * dereset ddr phy psrstn to config pll,
	 * if using phy pll psrstn must be dereset
	 * before config pll
	 */
	rkclk_ddr_reset(dram, 1, 1, 1, 0);
	rkclk_configure_ddr(dram, sdram_params);

	/* release phy srst to provide clk to ctrl */
	rkclk_ddr_reset(dram, 1, 1, 0, 0);
	udelay(10);
	phy_soft_reset(dram->phy);
	/* release ctrl presetn, and config ctl registers */
	rkclk_ddr_reset(dram, 1, 0, 0, 0);
	pctl_cfg(dram->pctl, &sdram_params->pctl_regs, SR_IDLE, PD_IDLE);
	cap_info->ddrconfig = calculate_ddrconfig(sdram_params);
	set_ctl_address_map(dram, sdram_params);
	phy_cfg(dram->phy, &sdram_params->phy_regs, sdram_params->skew,
		&sdram_params->base, cap_info->bw);

	/* enable dfi_init_start to init phy after ctl srstn deassert */
	setbits_le32(pctl_base + DDR_PCTL2_DFIMISC, (1 << 5) | (1 << 4));

	rkclk_ddr_reset(dram, 0, 0, 0, 0);
	/* wait for dfi_init_done and dram init complete */
	while ((readl(pctl_base + DDR_PCTL2_STAT) & 0x7) == 0)
		continue;

	if (sdram_params->base.dramtype == LPDDR3)
		pctl_write_mr(dram->pctl, 3, 11, 3, LPDDR3);

	/* do ddr gate training */
redo_cs0_training:
	if (data_training(dram, 0, sdram_params->base.dramtype) != 0) {
		if (pre_init != 0)
			printascii("DTT cs0 error\n");
		return -1;
	}
	if (check_rd_gate(dram)) {
		printascii("re training cs0");
		goto redo_cs0_training;
	}

	if (sdram_params->base.dramtype == LPDDR3) {
		if ((read_mr(dram, 1, 8) & 0x3) != 0x3)
			return -1;
	} else if (sdram_params->base.dramtype == LPDDR2) {
		if ((read_mr(dram, 1, 8) & 0x3) != 0x0)
			return -1;
	}
	/* for px30: when 2cs, both 2 cs should be training */
	if (pre_init != 0 && cap_info->rank == 2) {
redo_cs1_training:
		if (data_training(dram, 1, sdram_params->base.dramtype) != 0) {
			printascii("DTT cs1 error\n");
			return -1;
		}
		if (check_rd_gate(dram)) {
			printascii("re training cs1");
			goto redo_cs1_training;
		}
	}

	if (sdram_params->base.dramtype == DDR4)
		pctl_write_vrefdq(dram->pctl, 0x3, 5670,
				  sdram_params->base.dramtype);

	dram_all_config(dram, sdram_params);
	enable_low_power(dram, sdram_params);

	return 0;
}

static int dram_detect_cap(struct dram_info *dram,
			   struct px30_sdram_params *sdram_params,
			   unsigned char channel)
{
	struct sdram_cap_info *cap_info = &sdram_params->ch.cap_info;

	/*
	 * for ddr3: ddrconf = 3
	 * for ddr4: ddrconf = 12
	 * for lpddr3: ddrconf = 3
	 * default bw = 1
	 */
	u32 bk, bktmp;
	u32 col, coltmp;
	u32 rowtmp;
	u32 cs;
	u32 bw = 1;
	u32 dram_type = sdram_params->base.dramtype;

	if (dram_type != DDR4) {
		/* detect col and bk for ddr3/lpddr3 */
		coltmp = 12;
		bktmp = 3;
		if (dram_type == LPDDR2)
			rowtmp = 15;
		else
			rowtmp = 16;

		if (sdram_detect_col(cap_info, coltmp) != 0)
			goto cap_err;
		sdram_detect_bank(cap_info, coltmp, bktmp);
		sdram_detect_dbw(cap_info, dram_type);
	} else {
		/* detect bg for ddr4 */
		coltmp = 10;
		bktmp = 4;
		rowtmp = 17;

		col = 10;
		bk = 2;
		cap_info->col = col;
		cap_info->bk = bk;
		sdram_detect_bg(cap_info, coltmp);
	}

	/* detect row */
	if (sdram_detect_row(cap_info, coltmp, bktmp, rowtmp) != 0)
		goto cap_err;

	/* detect row_3_4 */
	sdram_detect_row_3_4(cap_info, coltmp, bktmp);

	/* bw and cs detect using data training */
	if (data_training(dram, 1, dram_type) == 0)
		cs = 1;
	else
		cs = 0;
	cap_info->rank = cs + 1;

	dram_set_bw(dram, 2);
	if (data_training(dram, 0, dram_type) == 0)
		bw = 2;
	else
		bw = 1;
	cap_info->bw = bw;

	cap_info->cs0_high16bit_row = cap_info->cs0_row;
	if (cs) {
		cap_info->cs1_row = cap_info->cs0_row;
		cap_info->cs1_high16bit_row = cap_info->cs0_row;
	} else {
		cap_info->cs1_row = 0;
		cap_info->cs1_high16bit_row = 0;
	}

	return 0;
cap_err:
	return -1;
}

void get_ddr_param(struct px30_sdram_params *sdram_params,
		   struct ddr_param *ddr_param)
{
	struct sdram_cap_info *cap_info = &sdram_params->ch.cap_info;
	u32 dram_type = sdram_params->base.dramtype;
	u64 cs_cap[2];

	cs_cap[0] = sdram_get_cs_cap(cap_info, 0, dram_type);
	cs_cap[1] = sdram_get_cs_cap(cap_info, 1, dram_type);

	if (cap_info->row_3_4) {
		cs_cap[0] =  cs_cap[0] * 3 / 4;
		cs_cap[1] =  cs_cap[1] * 3 / 4;
	}

	if (cap_info->row_3_4 && cap_info->rank == 2) {
		ddr_param->count = 2;
		ddr_param->para[0] = 0;
		ddr_param->para[1] = cs_cap[0] * 4 / 3;
		ddr_param->para[2] = cs_cap[0];
		ddr_param->para[3] = cs_cap[1];
	} else {
		ddr_param->count = 1;
		ddr_param->para[0] = 0;
		ddr_param->para[1] = (u64)cs_cap[0] + (u64)cs_cap[1];
	}
}

/* return: 0 = success, other = fail */
static int sdram_init_detect(struct dram_info *dram,
			     struct px30_sdram_params *sdram_params)
{
	struct sdram_cap_info *cap_info = &sdram_params->ch.cap_info;
	u32 ret;
	u32 sys_reg = 0;
	u32 sys_reg3 = 0;

	if (sdram_init_(dram, sdram_params, 0) != 0)
		return -1;

	if (dram_detect_cap(dram, sdram_params, 0) != 0)
		return -1;

	/* modify bw, cs related timing */
	pctl_remodify_sdram_params(&sdram_params->pctl_regs, cap_info,
				   sdram_params->base.dramtype);
	/* reinit sdram by real dram cap */
	ret = sdram_init_(dram, sdram_params, 1);
	if (ret != 0)
		goto out;

	/* redetect cs1 row */
	sdram_detect_cs1_row(cap_info, sdram_params->base.dramtype);
	if (cap_info->cs1_row) {
		sys_reg = readl(&dram->pmugrf->os_reg[2]);
		sys_reg3 = readl(&dram->pmugrf->os_reg[3]);
		SYS_REG_ENC_CS1_ROW(cap_info->cs1_row,
				    sys_reg, sys_reg3, 0);
		writel(sys_reg, &dram->pmugrf->os_reg[2]);
		writel(sys_reg3, &dram->pmugrf->os_reg[3]);
	}

	ret = sdram_detect_high_row(cap_info, sdram_params->base.dramtype);

out:
	return ret;
}

struct px30_sdram_params
		*get_default_sdram_config(void)
{
	sdram_configs[0].skew = &skew;

	return &sdram_configs[0];
}

/* return: 0 = success, other = fail */
int sdram_init(void)
{
	struct px30_sdram_params *sdram_params;
	int ret = 0;
	struct ddr_param ddr_param;

	dram_info.phy = (void *)DDR_PHY_BASE_ADDR;
	dram_info.pctl = (void *)DDRC_BASE_ADDR;
	dram_info.grf = (void *)GRF_BASE_ADDR;
	dram_info.cru = (void *)CRU_BASE_ADDR;
	dram_info.msch = (void *)SERVER_MSCH0_BASE_ADDR;
	dram_info.ddr_grf = (void *)DDR_GRF_BASE_ADDR;
	dram_info.pmugrf = (void *)PMUGRF_BASE_ADDR;

	sdram_params = get_default_sdram_config();
	ret = sdram_init_detect(&dram_info, sdram_params);

	if (ret)
		goto error;

	get_ddr_param(sdram_params, &ddr_param);
	rockchip_setup_ddr_param(&ddr_param);
	sdram_print_ddr_info(&sdram_params->ch.cap_info,
			     &sdram_params->base, 0);

	printascii("out\n");
	return ret;
error:
	return (-1);
}
#endif /* CONFIG_TPL_BUILD */
