/*
 * (C) Copyright 2016-2017 Rockchip Inc.
 *
 * SPDX-License-Identifier:     GPL-2.0
 *
 * Adapted from coreboot.
 */

#include <common.h>
#include <clk.h>
#include <dm.h>
#include <dt-structs.h>
#include <ram.h>
#include <regmap.h>
#include <syscon.h>
#include <asm/io.h>
#include <asm/arch-rockchip/clock.h>
#include <asm/arch-rockchip/sdram.h>
#include <asm/arch-rockchip/sdram_rk3399.h>
#include <asm/arch-rockchip/cru_rk3399.h>
#include <asm/arch-rockchip/grf_rk3399.h>
#include <asm/arch-rockchip/pmu_rk3399.h>
#include <asm/arch-rockchip/hardware.h>
#include <linux/err.h>
#include <time.h>

DECLARE_GLOBAL_DATA_PTR;

struct chan_info {
	struct rk3399_ddr_pctl_regs *pctl;
	struct rk3399_ddr_pi_regs *pi;
	struct rk3399_ddr_publ_regs *publ;
	struct msch_regs *msch;
};

struct dram_info {
#ifdef CONFIG_TPL_BUILD
	struct chan_info chan[2];
	struct clk ddr_clk;
	struct rk3399_cru *cru;
	struct rk3399_grf_regs *grf;
	struct rk3399_pmu_regs *pmu;
	struct rk3399_pmucru *pmucru;
	struct rk3399_pmusgrf_regs *pmusgrf;
	struct rk3399_ddr_cic_regs *cic;
#endif
	struct ram_info info;
	struct rk3399_pmugrf_regs *pmugrf;
};

#define PRESET_SGRF_HOLD(n)	((0x1 << (6 + 16)) | ((n) << 6))
#define PRESET_GPIO0_HOLD(n)	((0x1 << (7 + 16)) | ((n) << 7))
#define PRESET_GPIO1_HOLD(n)	((0x1 << (8 + 16)) | ((n) << 8))

#define PHY_DRV_ODT_HI_Z	0x0
#define PHY_DRV_ODT_240		0x1
#define PHY_DRV_ODT_120		0x8
#define PHY_DRV_ODT_80		0x9
#define PHY_DRV_ODT_60		0xc
#define PHY_DRV_ODT_48		0xd
#define PHY_DRV_ODT_40		0xe
#define PHY_DRV_ODT_34_3	0xf

#ifdef CONFIG_TPL_BUILD

struct rockchip_dmc_plat {
#if CONFIG_IS_ENABLED(OF_PLATDATA)
	struct dtd_rockchip_rk3399_dmc dtplat;
#else
	struct rk3399_sdram_params sdram_params;
#endif
	struct regmap *map;
};

u32 g_pwrup_srefresh_exit[2];

struct rk3399_sdram_params dfs_configs[] = {
#include "sdram-rk3399-lpddr4-400.inc"
#include "sdram-rk3399-lpddr4-800.inc"
};

#define CRU_SFTRST_DDR_CTRL(ch, n)	((0x1 << (8 + 16 + (ch) * 4)) | \
						((n) << (8 + (ch) * 4)))
#define CRU_SFTRST_DDR_PHY(ch, n)	((0x1 << (9 + 16 + (ch) * 4)) | \
						((n) << (9 + (ch) * 4)))
static void rkclk_ddr_reset(struct rk3399_cru *cru, u32 channel, u32 ctl,
			    u32 phy)
{
	channel &= 0x1;
	ctl &= 0x1;
	phy &= 0x1;
	writel(CRU_SFTRST_DDR_CTRL(channel, ctl) |
					CRU_SFTRST_DDR_PHY(channel, phy),
					&cru->softrst_con[4]);
}

static void phy_pctrl_reset(struct rk3399_cru *cru,
			    u32 channel)
{
	rkclk_ddr_reset(cru, channel, 1, 1);
	udelay(10);
	rkclk_ddr_reset(cru, channel, 1, 0);
	udelay(10);
	rkclk_ddr_reset(cru, channel, 0, 0);
	udelay(10);
}

static void phy_dll_bypass_set(struct rk3399_ddr_publ_regs *ddr_publ_regs,
			       u32 freq)
{
	u32 *denali_phy = ddr_publ_regs->denali_phy;

	/* From IP spec, only freq small than 125 can enter dll bypass mode */
	if (freq <= 125) {
		/* phy_sw_master_mode_X PHY_86/214/342/470 4bits offset_8 */
		setbits_le32(&denali_phy[86], (0x3 << 2) << 8);
		setbits_le32(&denali_phy[214], (0x3 << 2) << 8);
		setbits_le32(&denali_phy[342], (0x3 << 2) << 8);
		setbits_le32(&denali_phy[470], (0x3 << 2) << 8);

		/* phy_adrctl_sw_master_mode PHY_547/675/803 4bits offset_16 */
		setbits_le32(&denali_phy[547], (0x3 << 2) << 16);
		setbits_le32(&denali_phy[675], (0x3 << 2) << 16);
		setbits_le32(&denali_phy[803], (0x3 << 2) << 16);
	} else {
		/* phy_sw_master_mode_X PHY_86/214/342/470 4bits offset_8 */
		clrbits_le32(&denali_phy[86], (0x3 << 2) << 8);
		clrbits_le32(&denali_phy[214], (0x3 << 2) << 8);
		clrbits_le32(&denali_phy[342], (0x3 << 2) << 8);
		clrbits_le32(&denali_phy[470], (0x3 << 2) << 8);

		/* phy_adrctl_sw_master_mode PHY_547/675/803 4bits offset_16 */
		clrbits_le32(&denali_phy[547], (0x3 << 2) << 16);
		clrbits_le32(&denali_phy[675], (0x3 << 2) << 16);
		clrbits_le32(&denali_phy[803], (0x3 << 2) << 16);
	}
}

static void set_memory_map(const struct chan_info *chan, u32 channel,
			   const struct rk3399_sdram_params *sdram_params)
{
	const struct rk3399_sdram_channel *sdram_ch =
		&sdram_params->ch[channel];
	u32 *denali_ctl = chan->pctl->denali_ctl;
	u32 *denali_pi = chan->pi->denali_pi;
	u32 cs_map;
	u32 reduc;
	u32 row;

	/* Get row number from ddrconfig setting */
	if (sdram_ch->cap_info.ddrconfig < 2 ||
	    sdram_ch->cap_info.ddrconfig == 4)
		row = 16;
	else if (sdram_ch->cap_info.ddrconfig == 3 ||
		 sdram_ch->cap_info.ddrconfig == 5)
		row = 14;
	else
		row = 15;

	cs_map = (sdram_ch->cap_info.rank > 1) ? 3 : 1;
	reduc = (sdram_ch->cap_info.bw == 2) ? 0 : 1;

	/* Set the dram configuration to ctrl */
	clrsetbits_le32(&denali_ctl[191], 0xF, (12 - sdram_ch->cap_info.col));
	clrsetbits_le32(&denali_ctl[190], (0x3 << 16) | (0x7 << 24),
			((3 - sdram_ch->cap_info.bk) << 16) |
			((16 - row) << 24));

	clrsetbits_le32(&denali_ctl[196], 0x3 | (1 << 16),
			cs_map | (reduc << 16));

	/* PI_199 PI_COL_DIFF:RW:0:4 */
	clrsetbits_le32(&denali_pi[199], 0xF, (12 - sdram_ch->cap_info.col));

	/* PI_155 PI_ROW_DIFF:RW:24:3 PI_BANK_DIFF:RW:16:2 */
	clrsetbits_le32(&denali_pi[155], (0x3 << 16) | (0x7 << 24),
			((3 - sdram_ch->cap_info.bk) << 16) |
			((16 - row) << 24));
	if (sdram_params->base.dramtype == LPDDR4) {
		if (cs_map == 1)
			cs_map = 0x5;
		else if (cs_map == 2)
			cs_map = 0xa;
		else
			cs_map = 0xF;
	}

	/* PI_41 PI_CS_MAP:RW:24:4 */
	clrsetbits_le32(&denali_pi[41], 0xf << 24, cs_map << 24);
	if (sdram_ch->cap_info.rank == 1 &&
	    sdram_params->base.dramtype == DDR3)
		writel(0x2EC7FFFF, &denali_pi[34]);
}

static void phy_io_config(const struct chan_info *chan,
			  struct rk3399_sdram_params *sdram_params, u32 rd_vref,
			  u32 b_reg, u32 channel)
{
	u32 *denali_phy;
	u32 *denali_ctl;
	u32 vref_mode_dq = 0, vref_value_dq = 0;
	u32 vref_mode_ac = 0, vref_value_ac = 0;
	u32 mode_sel = 0;
	u32 boostp, boostn;
	u32 slewp, slewn;
	u32 speed;
	u32 rx_cm_input;
	u32 reg_value;
	u32 ds_value, odt_value;

	if (b_reg) {
		denali_phy = chan->publ->denali_phy;
		denali_ctl = chan->pctl->denali_ctl;
	} else {
		denali_phy = sdram_params->phy_regs.denali_phy;
		denali_ctl = sdram_params->pctl_regs.denali_ctl;
	}
	rd_vref *= 1000;
	/* vref setting & mode setting */
	if (sdram_params->base.dramtype == LPDDR4) {
		if (rd_vref < 36700) {
			/* MODE_LV[2:0] = LPDDR4 (Range 2)*/
			vref_mode_dq = 0x7;
			/* MODE[2:0]= LPDDR4 Range 2(0.4*VDDQ) */
			mode_sel = 0x5;
			vref_value_dq = (rd_vref - 3300) / 521;
		} else {
			/* MODE_LV[2:0] = LPDDR4 (Range 1)*/
			vref_mode_dq = 0x6;
			/* MODE[2:0]= LPDDR4 Range 1(0.33*VDDQ) */
			mode_sel = 0x4;
			vref_value_dq = (rd_vref - 15300) / 521;
		}
		vref_mode_ac = 0x6;
		/* VDDQ/3/2=16.8% */
		vref_value_ac = 0x3;
	} else if (sdram_params->base.dramtype == LPDDR3) {
		/* LPDDR3 */
		if (sdram_params->base.odt == 1) {
			vref_mode_dq = 0x5;  /*LPDDR3 ODT*/
			ds_value = readl(&denali_ctl[138]) & 0xf;
			odt_value = (readl(&denali_phy[6]) >> 4) & 0xf;
			if (ds_value == 0x3) {	/* 48ohm */
				switch (odt_value) {
				case PHY_DRV_ODT_240:
					vref_value_dq = 0x1B;
					break;
				case PHY_DRV_ODT_120:
					vref_value_dq = 0x26;
					break;
				case PHY_DRV_ODT_60:
					vref_value_dq = 0x36;
					break;
				}
			} else if (ds_value == 0x2) {  /* 40ohm */
				switch (odt_value) {
				case PHY_DRV_ODT_240:
					vref_value_dq = 0x19;
					break;
				case PHY_DRV_ODT_120:
					vref_value_dq = 0x23;
					break;
				case PHY_DRV_ODT_60:
					vref_value_dq = 0x31;
					break;
				}
			} else if (ds_value == 0x1) {  /*34.3ohm*/
				switch (odt_value) {
				case PHY_DRV_ODT_240:
					vref_value_dq = 0x17;
					break;
				case PHY_DRV_ODT_120:
					vref_value_dq = 0x20;
					break;
				case PHY_DRV_ODT_60:
					vref_value_dq = 0x2e;
					break;
				}
			}
		} else {
			vref_mode_dq = 0x2;
			vref_value_dq = 0x1f;
		}
		vref_mode_ac = 0x2;
		vref_value_ac = 0x1f;
		mode_sel = 0x0;
	} else if (sdram_params->base.dramtype == DDR3) {
		vref_mode_dq = 0x1;
		vref_value_dq = 0x1f;
		vref_mode_ac = 0x1;
		vref_value_ac = 0x1f;
		mode_sel = 0x1;
	}

	reg_value = (vref_mode_dq << 9) | (0x1 << 8) | vref_value_dq;
	/* PHY_913 PHY_PAD_VREF_CTRL_DQ_0 12bits offset_8 */
	clrsetbits_le32(&denali_phy[913], 0xfff << 8, reg_value << 8);
	/* PHY_914 PHY_PAD_VREF_CTRL_DQ_1 12bits offset_0 */
	clrsetbits_le32(&denali_phy[914], 0xfff, reg_value);
	/* PHY_914 PHY_PAD_VREF_CTRL_DQ_2 12bits offset_16 */
	clrsetbits_le32(&denali_phy[914], 0xfff << 16, reg_value << 16);
	/* PHY_915 PHY_PAD_VREF_CTRL_DQ_3 12bits offset_0 */
	clrsetbits_le32(&denali_phy[915], 0xfff, reg_value);

	reg_value = (vref_mode_ac << 9) | (0x1 << 8) | vref_value_ac;
	/* PHY_915 PHY_PAD_VREF_CTRL_AC 12bits offset_16 */
	clrsetbits_le32(&denali_phy[915], 0xfff << 16, reg_value << 16);

	/* PHY_924 PHY_PAD_FDBK_DRIVE */
	clrsetbits_le32(&denali_phy[924], 0x7 << 15, mode_sel << 15);
	/* PHY_926 PHY_PAD_DATA_DRIVE */
	clrsetbits_le32(&denali_phy[926], 0x7 << 6, mode_sel << 6);
	/* PHY_927 PHY_PAD_DQS_DRIVE */
	clrsetbits_le32(&denali_phy[927], 0x7 << 6, mode_sel << 6);
	/* PHY_928 PHY_PAD_ADDR_DRIVE */
	clrsetbits_le32(&denali_phy[928], 0x7 << 14, mode_sel << 14);
	/* PHY_929 PHY_PAD_CLK_DRIVE */
	clrsetbits_le32(&denali_phy[929], 0x7 << 14, mode_sel << 14);
	/* PHY_935 PHY_PAD_CKE_DRIVE */
	clrsetbits_le32(&denali_phy[935], 0x7 << 14, mode_sel << 14);
	/* PHY_937 PHY_PAD_RST_DRIVE */
	clrsetbits_le32(&denali_phy[937], 0x7 << 14, mode_sel << 14);
	/* PHY_939 PHY_PAD_CS_DRIVE */
	clrsetbits_le32(&denali_phy[939], 0x7 << 14, mode_sel << 14);

	/* BOOSTP_EN & BOOSTn_EN */
	if (sdram_params->base.dramtype == LPDDR4) {
		boostp = 0x1;
		boostn = 0x1;
		reg_value = ((boostp << 4) | boostn);
		/* PHY_925 PHY_PAD_FDBK_DRIVE2 */
		clrsetbits_le32(&denali_phy[925], 0xff << 8, reg_value << 8);
		/* PHY_926 PHY_PAD_DATA_DRIVE */
		clrsetbits_le32(&denali_phy[926], 0xff << 12, reg_value << 12);
		/* PHY_927 PHY_PAD_DQS_DRIVE */
		clrsetbits_le32(&denali_phy[927], 0xff << 14, reg_value << 14);
		/* PHY_928 PHY_PAD_ADDR_DRIVE */
		clrsetbits_le32(&denali_phy[928], 0xff << 20, reg_value << 20);
		/* PHY_929 PHY_PAD_CLK_DRIVE */
		clrsetbits_le32(&denali_phy[929], 0xff << 22, reg_value << 22);
		/* PHY_935 PHY_PAD_CKE_DRIVE */
		clrsetbits_le32(&denali_phy[935], 0xff << 20, reg_value << 20);
		/* PHY_937 PHY_PAD_RST_DRIVE */
		clrsetbits_le32(&denali_phy[937], 0xff << 20, reg_value << 20);
		/* PHY_939 PHY_PAD_CS_DRIVE */
		clrsetbits_le32(&denali_phy[939], 0xff << 20, reg_value << 20);
	}

	/* SLEWP & SLEWN */
	if (sdram_params->base.dramtype == LPDDR4) {
		slewp = 0x1;
		slewn = 0x1;
		reg_value = ((slewp << 3) | slewn);
		/* PHY_924 PHY_PAD_FDBK_DRIVE */
		clrsetbits_le32(&denali_phy[924], 0x3f << 8, reg_value << 8);
		/* PHY_926 PHY_PAD_DATA_DRIVE */
		clrsetbits_le32(&denali_phy[926], 0x3f, reg_value);
		/* PHY_927 PHY_PAD_DQS_DRIVE */
		clrsetbits_le32(&denali_phy[927], 0x3f, reg_value);
		/* PHY_928 PHY_PAD_ADDR_DRIVE */
		clrsetbits_le32(&denali_phy[928], 0x3f << 8, reg_value << 8);
		/* PHY_929 PHY_PAD_CLK_DRIVE */
		clrsetbits_le32(&denali_phy[929], 0x3f << 8, reg_value << 8);
		/* PHY_935 PHY_PAD_CKE_DRIVE */
		clrsetbits_le32(&denali_phy[935], 0x3f << 8, reg_value << 8);
		/* PHY_937 PHY_PAD_RST_DRIVE */
		clrsetbits_le32(&denali_phy[937], 0x3f << 8, reg_value << 8);
		/* PHY_939 PHY_PAD_CS_DRIVE */
		clrsetbits_le32(&denali_phy[939], 0x3f << 8, reg_value << 8);
	}

	/* speed setting */
	if (sdram_params->base.ddr_freq < 400 * MHz)
		speed = 0x0;
	else if (sdram_params->base.ddr_freq < 800 * MHz)
		speed = 0x1;
	else if (sdram_params->base.ddr_freq < 1200 * MHz)
		speed = 0x2;
	speed = 0x2;

	/* PHY_924 PHY_PAD_FDBK_DRIVE */
	clrsetbits_le32(&denali_phy[924], 0x3 << 21, speed << 21);
	/* PHY_926 PHY_PAD_DATA_DRIVE */
	clrsetbits_le32(&denali_phy[926], 0x3 << 9, speed << 9);
	/* PHY_927 PHY_PAD_DQS_DRIVE */
	clrsetbits_le32(&denali_phy[927], 0x3 << 9, speed << 9);
	/* PHY_928 PHY_PAD_ADDR_DRIVE */
	clrsetbits_le32(&denali_phy[928], 0x3 << 17, speed << 17);
	/* PHY_929 PHY_PAD_CLK_DRIVE */
	clrsetbits_le32(&denali_phy[929], 0x3 << 17, speed << 17);
	/* PHY_935 PHY_PAD_CKE_DRIVE */
	clrsetbits_le32(&denali_phy[935], 0x3 << 17, speed << 17);
	/* PHY_937 PHY_PAD_RST_DRIVE */
	clrsetbits_le32(&denali_phy[937], 0x3 << 17, speed << 17);
	/* PHY_939 PHY_PAD_CS_DRIVE */
	clrsetbits_le32(&denali_phy[939], 0x3 << 17, speed << 17);

	/* RX_CM_INPUT */
	if (sdram_params->base.dramtype == LPDDR4) {
		rx_cm_input = 0x1;
		/* PHY_924 PHY_PAD_FDBK_DRIVE */
		clrsetbits_le32(&denali_phy[924], 0x1 << 14, rx_cm_input << 14);
		/* PHY_926 PHY_PAD_DATA_DRIVE */
		clrsetbits_le32(&denali_phy[926], 0x1 << 11, rx_cm_input << 11);
		/* PHY_927 PHY_PAD_DQS_DRIVE */
		clrsetbits_le32(&denali_phy[927], 0x1 << 13, rx_cm_input << 13);
		/* PHY_928 PHY_PAD_ADDR_DRIVE */
		clrsetbits_le32(&denali_phy[928], 0x1 << 19, rx_cm_input << 19);
		/* PHY_929 PHY_PAD_CLK_DRIVE */
		clrsetbits_le32(&denali_phy[929], 0x1 << 21, rx_cm_input << 21);
		/* PHY_935 PHY_PAD_CKE_DRIVE */
		clrsetbits_le32(&denali_phy[935], 0x1 << 19, rx_cm_input << 19);
		/* PHY_937 PHY_PAD_RST_DRIVE */
		clrsetbits_le32(&denali_phy[937], 0x1 << 19, rx_cm_input << 19);
		/* PHY_939 PHY_PAD_CS_DRIVE */
		clrsetbits_le32(&denali_phy[939], 0x1 << 19, rx_cm_input << 19);
	}
}

struct io_setting {
	u32 mhz;
	u32 mr5;
	/* dram side */
	u32 dq_odt;
	u32 ca_odt;
	u32 pdds;
	u32 dq_vref;
	u32 ca_vref;
	/* phy side */
	u32 rd_odt;
	u32 wr_dq_drv;
	u32 wr_ca_drv;
	u32 wr_ckcs_drv;
	u32 rd_odt_en;
	u32 rd_vref;
};

struct io_setting lp4_io_set[] = {
	{
		50 * MHz,
		0,
		/* dram side */
		0,	/* dq_odt; */
		0,	/* ca_odt; */
		6,	/* pdds; */
		0x72,	/* dq_vref; */
		0x72,	/* ca_vref; */
		/* phy side */
		PHY_DRV_ODT_HI_Z,	/* rd_odt; */
		PHY_DRV_ODT_40,	/* wr_dq_drv; */
		PHY_DRV_ODT_40,	/* wr_ca_drv; */
		PHY_DRV_ODT_40,	/* wr_ckcs_drv; */
		0,	/* rd_odt_en;*/
		41,	/* rd_vref; (unit %, range 3.3% - 48.7%) */
	},
	{
		400 * MHz,
		0,
		/* dram side */
		0,	/* dq_odt; */
		0,	/* ca_odt; */
		6,	/* pdds; */
		0x72,	/* dq_vref; */
		0x72,	/* ca_vref; */
		/* phy side */
		PHY_DRV_ODT_HI_Z,	/* rd_odt; */
		PHY_DRV_ODT_40,	/* wr_dq_drv; */
		PHY_DRV_ODT_40,	/* wr_ca_drv; */
		PHY_DRV_ODT_40,	/* wr_ckcs_drv; */
		0,	/* rd_odt_en; */
		/* shmoo result, read signal 41% is the best */
		41,	/* rd_vref; (unit %, range 3.3% - 48.7%) */
	},
	{
		800 * MHz,
		0,
		/* dram side */
		0,	/* dq_odt; */
		0,	/* ca_odt; */
		1,	/* pdds; */
		0x72,	/* dq_vref; */
		0x72,	/* ca_vref; */
		/* phy side */
		PHY_DRV_ODT_40,	/* rd_odt; */
		PHY_DRV_ODT_40,	/* wr_dq_drv; */
		PHY_DRV_ODT_40,	/* wr_ca_drv; */
		PHY_DRV_ODT_40,	/* wr_ckcs_drv; */
		1,	/* rd_odt_en; */
		17,	/* rd_vref; (unit %, range 3.3% - 48.7%) */
	},
	{
		1066 * MHz,
		0,
		/* dram side */
		6,	/* dq_odt; */
		0,	/* ca_odt; */
		1,	/* pdds; */
		0x10,	/* dq_vref; */
		0x72,	/* ca_vref; */
		/* phy side */
		PHY_DRV_ODT_40,	/* rd_odt; */
		PHY_DRV_ODT_60,	/* wr_dq_drv; */
		PHY_DRV_ODT_40,	/* wr_ca_drv; */
		PHY_DRV_ODT_40,	/* wr_ckcs_drv; */
		1,	/* rd_odt_en; */
		17,	/* rd_vref; (unit %, range 3.3% - 48.7%) */
	},
};

static struct io_setting *get_io_set(struct rk3399_sdram_params *sdram_params,
				     u32 mr5)
{
	struct io_setting *io = NULL;
	u32 n;

	for (n = 0; n < ARRAY_SIZE(lp4_io_set); n++) {
		io = &lp4_io_set[n];
		if (io->mr5 != 0) {
			if (io->mhz >= sdram_params->base.ddr_freq &&
			    io->mr5 == mr5)
				break;
		} else {
			if (io->mhz >= sdram_params->base.ddr_freq)
				break;
		}
	}
	return io;
}

/*
 * b_reg: indicate whether set phy register
 * or just set sdram_params.
 * if b_reg = 0, channel, mr5 are not care
 */
static void set_ds_odt(const struct chan_info *chan,
		       struct rk3399_sdram_params *sdram_params, u32 b_reg,
		       u32 channel, u32 mr5)
{
	u32 *denali_phy;
	u32 *denali_ctl;
	u32 tsel_idle_en, tsel_wr_en, tsel_rd_en;
	u32 tsel_idle_select_p, tsel_rd_select_p;
	u32 tsel_idle_select_n, tsel_rd_select_n;
	u32 tsel_wr_select_dq_p, tsel_wr_select_ca_p;
	u32 tsel_wr_select_dq_n, tsel_wr_select_ca_n;
	u32 soc_odt = 0;
	u32 tsel_ckcs_select_p, tsel_ckcs_select_n;
	u32 reg_value;
	struct io_setting *io = NULL;

	if (b_reg) {
		denali_phy = chan->publ->denali_phy;
		denali_ctl = chan->pctl->denali_ctl;
	} else {
		denali_phy = sdram_params->phy_regs.denali_phy;
		denali_ctl = sdram_params->pctl_regs.denali_ctl;
	}

	if (sdram_params->base.dramtype == LPDDR4) {
		io = get_io_set(sdram_params, mr5);

		tsel_rd_select_p = PHY_DRV_ODT_HI_Z;
		tsel_rd_select_n = io->rd_odt;

		tsel_idle_select_p = PHY_DRV_ODT_HI_Z;
		tsel_idle_select_n = PHY_DRV_ODT_HI_Z;

		tsel_wr_select_dq_p = io->wr_dq_drv;
		tsel_wr_select_dq_n = PHY_DRV_ODT_34_3;

		tsel_wr_select_ca_p = io->wr_ca_drv;
		tsel_wr_select_ca_n = PHY_DRV_ODT_34_3;

		tsel_ckcs_select_p = io->wr_ckcs_drv;
		tsel_ckcs_select_n = PHY_DRV_ODT_34_3;

		switch (tsel_rd_select_n) {
		case PHY_DRV_ODT_240:
			soc_odt = 1;
			break;
		case PHY_DRV_ODT_120:
			soc_odt = 2;
			break;
		case PHY_DRV_ODT_80:
			soc_odt = 3;
			break;
		case PHY_DRV_ODT_60:
			soc_odt = 4;
			break;
		case PHY_DRV_ODT_48:
			soc_odt = 5;
			break;
		case PHY_DRV_ODT_40:
			soc_odt = 6;
			break;
		case PHY_DRV_ODT_34_3:
			soc_odt = 6;
			printf("LPDDR4 MR22 Soc ODT not support\n");
			break;
		case PHY_DRV_ODT_HI_Z:
		default:
			soc_odt = 0;
			break;
		}
	} else if (sdram_params->base.dramtype == LPDDR3) {
		tsel_rd_select_p = PHY_DRV_ODT_240;
		tsel_rd_select_n = PHY_DRV_ODT_HI_Z;

		tsel_idle_select_p = PHY_DRV_ODT_240;
		tsel_idle_select_n = PHY_DRV_ODT_HI_Z;

		tsel_wr_select_dq_p = PHY_DRV_ODT_34_3;
		tsel_wr_select_dq_n = PHY_DRV_ODT_34_3;

		tsel_wr_select_ca_p = PHY_DRV_ODT_34_3;
		tsel_wr_select_ca_n = PHY_DRV_ODT_34_3;

		tsel_ckcs_select_p = PHY_DRV_ODT_34_3;
		tsel_ckcs_select_n = PHY_DRV_ODT_34_3;
	} else {
		tsel_rd_select_p = PHY_DRV_ODT_240;
		tsel_rd_select_n = PHY_DRV_ODT_240;

		tsel_idle_select_p = PHY_DRV_ODT_240;
		tsel_idle_select_n = PHY_DRV_ODT_240;

		tsel_wr_select_dq_p = PHY_DRV_ODT_34_3;
		tsel_wr_select_dq_n = PHY_DRV_ODT_34_3;

		tsel_wr_select_ca_p = PHY_DRV_ODT_34_3;
		tsel_wr_select_ca_n = PHY_DRV_ODT_34_3;

		tsel_ckcs_select_p = PHY_DRV_ODT_34_3;
		tsel_ckcs_select_n = PHY_DRV_ODT_34_3;
	}

	if (sdram_params->base.dramtype == LPDDR4) {
		if (sdram_params->base.odt == 1) {
			tsel_rd_en = io->rd_odt_en;
			tsel_idle_en = 0;
		} else {
			tsel_rd_en = 0;
			tsel_idle_en = 0;
		}
	} else {
		tsel_rd_en = sdram_params->base.odt;
		tsel_idle_en = 0;
	}
	tsel_wr_en = 0;

#define CS0_MR22_VAL (0)
#define CS1_MR22_VAL (3)
	/* F0_0 */
	clrsetbits_le32(&denali_ctl[145], 0xFF << 16,
			(soc_odt | (CS0_MR22_VAL << 3)) << 16);
	/* F2_0, F1_0 */
	clrsetbits_le32(&denali_ctl[146], 0xFF00FF,
			((soc_odt | (CS0_MR22_VAL << 3)) << 16) |
			(soc_odt | (CS0_MR22_VAL << 3)));
	/* F0_1 */
	clrsetbits_le32(&denali_ctl[159], 0xFF << 16,
			(soc_odt | (CS1_MR22_VAL << 3)) << 16);
	/* F2_1, F1_1 */
	clrsetbits_le32(&denali_ctl[160], 0xFF00FF,
			((soc_odt | (CS1_MR22_VAL << 3)) << 16) |
			(soc_odt | (CS1_MR22_VAL << 3)));

	/*
	 * phy_dq_tsel_select_X 24bits DENALI_PHY_6/134/262/390 offset_0
	 * sets termination values for read/idle cycles and drive strength
	 * for write cycles for DQ/DM
	 */
	reg_value = tsel_rd_select_n | (tsel_rd_select_p << 0x4) |
		(tsel_wr_select_dq_n << 8) | (tsel_wr_select_dq_p << 12) |
		(tsel_idle_select_n << 16) | (tsel_idle_select_p << 20);
	clrsetbits_le32(&denali_phy[6], 0xffffff, reg_value);
	clrsetbits_le32(&denali_phy[134], 0xffffff, reg_value);
	clrsetbits_le32(&denali_phy[262], 0xffffff, reg_value);
	clrsetbits_le32(&denali_phy[390], 0xffffff, reg_value);

	/*
	 * phy_dqs_tsel_select_X 24bits DENALI_PHY_7/135/263/391 offset_0
	 * sets termination values for read/idle cycles and drive strength
	 * for write cycles for DQS
	 */
	clrsetbits_le32(&denali_phy[7], 0xffffff, reg_value);
	clrsetbits_le32(&denali_phy[135], 0xffffff, reg_value);
	clrsetbits_le32(&denali_phy[263], 0xffffff, reg_value);
	clrsetbits_le32(&denali_phy[391], 0xffffff, reg_value);

	/* phy_adr_tsel_select_ 8bits DENALI_PHY_544/672/800 offset_0 */
	reg_value = tsel_wr_select_ca_n | (tsel_wr_select_ca_p << 0x4);
	if (sdram_params->base.dramtype == LPDDR4) {
		/* LPDDR4 these register read always return 0, so
		 * can not use clrsetbits_le32(), need to write32
		 */
		writel((0x300 << 8) | reg_value, &denali_phy[544]);
		writel((0x300 << 8) | reg_value, &denali_phy[672]);
		writel((0x300 << 8) | reg_value, &denali_phy[800]);
	} else {
		clrsetbits_le32(&denali_phy[544], 0xff, reg_value);
		clrsetbits_le32(&denali_phy[672], 0xff, reg_value);
		clrsetbits_le32(&denali_phy[800], 0xff, reg_value);
	}

	/* phy_pad_addr_drive 8bits DENALI_PHY_928 offset_0 */
	clrsetbits_le32(&denali_phy[928], 0xff, reg_value);

	/* phy_pad_rst_drive 8bits DENALI_PHY_937 offset_0 */
	if (!b_reg)
		clrsetbits_le32(&denali_phy[937], 0xff, reg_value);

	/* phy_pad_cke_drive 8bits DENALI_PHY_935 offset_0 */
	clrsetbits_le32(&denali_phy[935], 0xff, reg_value);

	/* phy_pad_cs_drive 8bits DENALI_PHY_939 offset_0 */
	clrsetbits_le32(&denali_phy[939], 0xff,
			tsel_ckcs_select_n | (tsel_ckcs_select_p << 0x4));

	/* phy_pad_clk_drive 8bits DENALI_PHY_929 offset_0 */
	clrsetbits_le32(&denali_phy[929], 0xff,
			tsel_ckcs_select_n | (tsel_ckcs_select_p << 0x4));

	/* phy_pad_fdbk_drive 23bit DENALI_PHY_924/925 */
	clrsetbits_le32(&denali_phy[924], 0xff,
			tsel_wr_select_ca_n | (tsel_wr_select_ca_p << 4));
	clrsetbits_le32(&denali_phy[925], 0xff,
			tsel_wr_select_dq_n | (tsel_wr_select_dq_p << 4));

	/* phy_dq_tsel_enable_X 3bits DENALI_PHY_5/133/261/389 offset_16 */
	reg_value = (tsel_rd_en | (tsel_wr_en << 1) | (tsel_idle_en << 2))
		<< 16;
	clrsetbits_le32(&denali_phy[5], 0x7 << 16, reg_value);
	clrsetbits_le32(&denali_phy[133], 0x7 << 16, reg_value);
	clrsetbits_le32(&denali_phy[261], 0x7 << 16, reg_value);
	clrsetbits_le32(&denali_phy[389], 0x7 << 16, reg_value);

	/* phy_dqs_tsel_enable_X 3bits DENALI_PHY_6/134/262/390 offset_24 */
	reg_value = (tsel_rd_en | (tsel_wr_en << 1) | (tsel_idle_en << 2))
		<< 24;
	clrsetbits_le32(&denali_phy[6], 0x7 << 24, reg_value);
	clrsetbits_le32(&denali_phy[134], 0x7 << 24, reg_value);
	clrsetbits_le32(&denali_phy[262], 0x7 << 24, reg_value);
	clrsetbits_le32(&denali_phy[390], 0x7 << 24, reg_value);

	/* phy_adr_tsel_enable_ 1bit DENALI_PHY_518/646/774 offset_8 */
	reg_value = tsel_wr_en << 8;
	clrsetbits_le32(&denali_phy[518], 0x1 << 8, reg_value);
	clrsetbits_le32(&denali_phy[646], 0x1 << 8, reg_value);
	clrsetbits_le32(&denali_phy[774], 0x1 << 8, reg_value);

	/* phy_pad_addr_term tsel 1bit DENALI_PHY_933 offset_17 */
	reg_value = tsel_wr_en << 17;
	clrsetbits_le32(&denali_phy[933], 0x1 << 17, reg_value);
	/*
	 * pad_rst/cke/cs/clk_term tsel 1bits
	 * DENALI_PHY_938/936/940/934 offset_17
	 */
	clrsetbits_le32(&denali_phy[938], 0x1 << 17, reg_value);
	clrsetbits_le32(&denali_phy[936], 0x1 << 17, reg_value);
	clrsetbits_le32(&denali_phy[940], 0x1 << 17, reg_value);
	clrsetbits_le32(&denali_phy[934], 0x1 << 17, reg_value);

	/* phy_pad_fdbk_term 1bit DENALI_PHY_930 offset_17 */
	clrsetbits_le32(&denali_phy[930], 0x1 << 17, reg_value);

	if (sdram_params->base.dramtype == LPDDR4)
		phy_io_config(chan, sdram_params, io->rd_vref, b_reg, channel);
	else
		phy_io_config(chan, sdram_params, 0, b_reg, channel);
}

static void pctl_start(struct dram_info *dram,
		       struct rk3399_sdram_params *sdram_params,
		       u32 channel_mask)
{
	const struct chan_info *chan_0 = &dram->chan[0];
	const struct chan_info *chan_1 = &dram->chan[1];

	u32 *denali_ctl_0 = chan_0->pctl->denali_ctl;
	u32 *denali_phy_0 = chan_0->publ->denali_phy;
	u32 *denali_ctl_1 = chan_1->pctl->denali_ctl;
	u32 *denali_phy_1 = chan_1->publ->denali_phy;
	u32 count, byte, tmp;

	/* PHY_DLL_RST_EN */
	if (channel_mask & 1) {
		writel(0x01000000, &dram->grf->ddrc0_con0);
		clrsetbits_le32(&denali_phy_0[957], 0x3 << 24, 0x2 << 24);
	}

	if (channel_mask & 1) {
		count = 0;
		while (!(readl(&denali_ctl_0[203]) & (1 << 3))) {
			if (count > 1000) {
				printf("channel 0 init err!\n");
				while (1)
					;
			}
			udelay(1);
			count++;
		}

		writel(0x01000100, &dram->grf->ddrc0_con0);
		for (byte = 0; byte < 4; byte++)	{
			tmp = 0x820;
			writel((tmp << 16) | tmp,
			       &denali_phy_0[53 + (128 * byte)]);
			writel((tmp << 16) | tmp,
			       &denali_phy_0[54 + (128 * byte)]);
			writel((tmp << 16) | tmp,
			       &denali_phy_0[55 + (128 * byte)]);
			writel((tmp << 16) | tmp,
			       &denali_phy_0[56 + (128 * byte)]);
			writel((tmp << 16) | tmp,
			       &denali_phy_0[57 + (128 * byte)]);
			clrsetbits_le32(&denali_phy_0[58 + (128 * byte)],
					0xffff, tmp);
		}
		clrsetbits_le32(&denali_ctl_0[68], PWRUP_SREFRESH_EXIT,
				g_pwrup_srefresh_exit[0]);
	}

	if (channel_mask & 2) {
		writel(0x01000000, &dram->grf->ddrc1_con0);
		clrsetbits_le32(&denali_phy_1[957], 0x3 << 24, 0x2 << 24);
	}
	if (channel_mask & 2) {
		count = 0;
		while (!(readl(&denali_ctl_1[203]) & (1 << 3))) {
			if (count > 1000) {
				printf("channel 1 init err!\n");
				while (1)
					;
			}
			udelay(1);
			count++;
		}

		writel(0x01000100, &dram->grf->ddrc1_con0);
		for (byte = 0; byte < 4; byte++)	{
			tmp = 0x820;
			writel((tmp << 16) | tmp,
			       &denali_phy_1[53 + (128 * byte)]);
			writel((tmp << 16) | tmp,
			       &denali_phy_1[54 + (128 * byte)]);
			writel((tmp << 16) | tmp,
			       &denali_phy_1[55 + (128 * byte)]);
			writel((tmp << 16) | tmp,
			       &denali_phy_1[56 + (128 * byte)]);
			writel((tmp << 16) | tmp,
			       &denali_phy_1[57 + (128 * byte)]);
			clrsetbits_le32(&denali_phy_1[58 + (128 * byte)],
					0xffff, tmp);
		}

		clrsetbits_le32(&denali_ctl_1[68], PWRUP_SREFRESH_EXIT,
				g_pwrup_srefresh_exit[1]);

		/*
		 * restore channel 1 RESET original setting
		 * to avoid 240ohm too weak to prevent ESD test
		 */
		if (sdram_params->base.dramtype == LPDDR4)
			clrsetbits_le32(&denali_phy_1[937], 0xff,
					sdram_params->phy_regs.denali_phy[937] &
					0xFF);
	}
}

/* phy_fn = 0, PHY boot freq
 * phy_fn = 1, PHY index 0
 * phy_fn = 2, PHY index 1
 */
static struct rk3399_sdram_params
	*get_phy_index_params(u32 phy_fn,
			      struct rk3399_sdram_params *sdram_params)
{
	if (phy_fn == 0)
		return sdram_params;
	else if (phy_fn == 1)
		return &dfs_configs[1];
	else if (phy_fn == 2)
		return &dfs_configs[0];
	else
		return NULL;
}

/*
 * b_reg: indicate whether set phy register
 * or just set sdram_params.
 * if b_reg = 0, channel, mr5 are not care
 */
static void set_lp4_dq_odt(const struct chan_info *chan,
			   struct rk3399_sdram_params *sdram_params, u32 ctl_fn,
			   u32 en, u32 b_reg, u32 channel, u32 mr5)
{
	u32 *denali_ctl;
	u32 *denali_pi;
	u32 reg_value;
	struct io_setting *io;

	if (b_reg) {
		denali_pi = chan->pi->denali_pi;
		denali_ctl = chan->pctl->denali_ctl;
	} else {
		denali_pi = sdram_params->pi_regs.denali_pi;
		denali_ctl = sdram_params->pctl_regs.denali_ctl;
	}
	io = get_io_set(sdram_params, mr5);
	if (en)
		reg_value = io->dq_odt;
	else
		reg_value = 0;

	switch (ctl_fn) {
	case 0:
		clrsetbits_le32(&denali_ctl[139], 0x7 << 24, reg_value << 24);
		clrsetbits_le32(&denali_ctl[153], 0x7 << 24, reg_value << 24);

		clrsetbits_le32(&denali_pi[132], 0x7 << 0, (reg_value << 0));
		clrsetbits_le32(&denali_pi[139], 0x7 << 16, (reg_value << 16));
		clrsetbits_le32(&denali_pi[147], 0x7 << 0, (reg_value << 0));
		clrsetbits_le32(&denali_pi[154], 0x7 << 16, (reg_value << 16));
		break;
	case 1:
		clrsetbits_le32(&denali_ctl[140], 0x7 << 0, reg_value << 0);
		clrsetbits_le32(&denali_ctl[154], 0x7 << 0, reg_value << 0);

		clrsetbits_le32(&denali_pi[129], 0x7 << 16, (reg_value << 16));
		clrsetbits_le32(&denali_pi[137], 0x7 << 0, (reg_value << 0));
		clrsetbits_le32(&denali_pi[144], 0x7 << 16, (reg_value << 16));
		clrsetbits_le32(&denali_pi[152], 0x7 << 0, (reg_value << 0));
		break;
	case 2:
	default:
		clrsetbits_le32(&denali_ctl[140], 0x7 << 8, (reg_value << 8));
		clrsetbits_le32(&denali_ctl[154], 0x7 << 8, (reg_value << 8));

		clrsetbits_le32(&denali_pi[127], 0x7 << 0, (reg_value << 0));
		clrsetbits_le32(&denali_pi[134], 0x7 << 16, (reg_value << 16));
		clrsetbits_le32(&denali_pi[142], 0x7 << 0, (reg_value << 0));
		clrsetbits_le32(&denali_pi[149], 0x7 << 16, (reg_value << 16));
		break;
	}
}

/*
 * b_reg: indicate whether set phy register
 * or just set sdram_params.
 * if b_reg = 0, channel, mr5 are not care
 */
static void set_lp4_ca_odt(const struct chan_info *chan,
			   struct rk3399_sdram_params *sdram_params, u32 ctl_fn,
			   u32 en, u32 b_reg, u32 channel, u32 mr5)
{
	u32 *denali_ctl;
	u32 *denali_pi;
	u32 reg_value;
	struct io_setting *io;

	if (b_reg) {
		denali_pi = chan->pi->denali_pi;
		denali_ctl = chan->pctl->denali_ctl;
	} else {
		denali_pi = sdram_params->pi_regs.denali_pi;
		denali_ctl = sdram_params->pctl_regs.denali_ctl;
	}
	io = get_io_set(sdram_params, mr5);
	if (en)
		reg_value = io->ca_odt;
	else
		reg_value = 0;

	switch (ctl_fn) {
	case 0:
		clrsetbits_le32(&denali_ctl[139], 0x7 << 28, reg_value << 28);
		clrsetbits_le32(&denali_ctl[153], 0x7 << 28, reg_value << 28);

		clrsetbits_le32(&denali_pi[132], 0x7 << 4, reg_value << 4);
		clrsetbits_le32(&denali_pi[139], 0x7 << 20, reg_value << 20);
		clrsetbits_le32(&denali_pi[147], 0x7 << 4, reg_value << 4);
		clrsetbits_le32(&denali_pi[154], 0x7 << 20, reg_value << 20);
		break;
	case 1:
		clrsetbits_le32(&denali_ctl[140], 0x7 << 4, reg_value << 4);
		clrsetbits_le32(&denali_ctl[154], 0x7 << 4, reg_value << 4);

		clrsetbits_le32(&denali_pi[129], 0x7 << 20, reg_value << 20);
		clrsetbits_le32(&denali_pi[137], 0x7 << 4, reg_value << 4);
		clrsetbits_le32(&denali_pi[144], 0x7 << 20, reg_value << 20);
		clrsetbits_le32(&denali_pi[152], 0x7 << 4, reg_value << 4);
		break;
	case 2:
	default:
		clrsetbits_le32(&denali_ctl[140], 0x7 << 12, (reg_value << 12));
		clrsetbits_le32(&denali_ctl[154], 0x7 << 12, (reg_value << 12));

		clrsetbits_le32(&denali_pi[127], 0x7 << 4, reg_value << 4);
		clrsetbits_le32(&denali_pi[134], 0x7 << 20, reg_value << 20);
		clrsetbits_le32(&denali_pi[142], 0x7 << 4, reg_value << 4);
		clrsetbits_le32(&denali_pi[149], 0x7 << 20, reg_value << 20);
		break;
	}
}

/*
 * b_reg: indicate whether set phy register
 * or just set sdram_params.
 * if b_reg = 0, channel, mr5 are not care
 */
static void set_lp4_MR3(const struct chan_info *chan,
			struct rk3399_sdram_params *sdram_params, u32 ctl_fn,
			u32 b_reg, u32 channel, u32 mr5)
{
	u32 *denali_ctl;
	u32 *denali_pi;
	u32 reg_value;
	struct io_setting *io;

	if (b_reg) {
		denali_pi = chan->pi->denali_pi;
		denali_ctl = chan->pctl->denali_ctl;
	} else {
		denali_pi = sdram_params->pi_regs.denali_pi;
		denali_ctl = sdram_params->pctl_regs.denali_ctl;
	}
	io = get_io_set(sdram_params, mr5);

	reg_value = ((io->pdds << 3) | 1);
	switch (ctl_fn) {
	case 0:
		clrsetbits_le32(&denali_ctl[138], 0xFFFF, reg_value);
		clrsetbits_le32(&denali_ctl[152], 0xFFFF, reg_value);

		clrsetbits_le32(&denali_pi[131], 0xFFFF << 16, reg_value << 16);
		clrsetbits_le32(&denali_pi[139], 0xFFFF, reg_value);
		clrsetbits_le32(&denali_pi[146], 0xFFFF << 16, reg_value << 16);
		clrsetbits_le32(&denali_pi[154], 0xFFFF, reg_value);
		break;
	case 1:
		clrsetbits_le32(&denali_ctl[138], 0xFFFF << 16,
				reg_value << 16);
		clrsetbits_le32(&denali_ctl[152], 0xFFFF << 16,
				reg_value << 16);

		clrsetbits_le32(&denali_pi[129], 0xFFFF, reg_value);
		clrsetbits_le32(&denali_pi[136], 0xFFFF << 16, reg_value << 16);
		clrsetbits_le32(&denali_pi[144], 0xFFFF, reg_value);
		clrsetbits_le32(&denali_pi[151], 0xFFFF << 16, reg_value << 16);
		break;
	case 2:
	default:
		clrsetbits_le32(&denali_ctl[139], 0xFFFF, reg_value);
		clrsetbits_le32(&denali_ctl[153], 0xFFFF, reg_value);

		clrsetbits_le32(&denali_pi[126], 0xFFFF << 16, reg_value << 16);
		clrsetbits_le32(&denali_pi[134], 0xFFFF, reg_value);
		clrsetbits_le32(&denali_pi[141], 0xFFFF << 16, reg_value << 16);
		clrsetbits_le32(&denali_pi[149], 0xFFFF, reg_value);
		break;
	}
}

/*
 * b_reg: indicate whether set phy register
 * or just set sdram_params.
 * if b_reg = 0, channel, mr5 are not care
 */
static void set_lp4_MR12(const struct chan_info *chan,
			 struct rk3399_sdram_params *sdram_params, u32 ctl_fn,
			 u32 b_reg, u32 channel, u32 mr5)
{
	u32 *denali_ctl;
	u32 *denali_pi;
	u32 reg_value;
	struct io_setting *io;

	if (b_reg) {
		denali_pi = chan->pi->denali_pi;
		denali_ctl = chan->pctl->denali_ctl;
	} else {
		denali_pi = sdram_params->pi_regs.denali_pi;
		denali_ctl = sdram_params->pctl_regs.denali_ctl;
	}
	io = get_io_set(sdram_params, mr5);

	reg_value = io->ca_vref;
	switch (ctl_fn) {
	case 0:
		clrsetbits_le32(&denali_ctl[140], 0xFFFF << 16,
				reg_value << 16);
		clrsetbits_le32(&denali_ctl[154], 0xFFFF << 16,
				reg_value << 16);

		clrsetbits_le32(&denali_pi[132], 0xFF << 8, reg_value << 8);
		clrsetbits_le32(&denali_pi[139], 0xFF << 24, reg_value << 24);
		clrsetbits_le32(&denali_pi[147], 0xFF << 8, reg_value << 8);
		clrsetbits_le32(&denali_pi[154], 0xFF << 24, reg_value << 24);
		break;
	case 1:
		clrsetbits_le32(&denali_ctl[141], 0xFFFF, reg_value);
		clrsetbits_le32(&denali_ctl[155], 0xFFFF, reg_value);

		clrsetbits_le32(&denali_pi[129], 0xFF << 24, reg_value << 24);
		clrsetbits_le32(&denali_pi[137], 0xFF << 8, reg_value << 8);
		clrsetbits_le32(&denali_pi[144], 0xFF << 24, reg_value << 24);
		clrsetbits_le32(&denali_pi[152], 0xFF << 8, reg_value << 8);
		break;
	case 2:
	default:
		clrsetbits_le32(&denali_ctl[141], 0xFFFF << 16,
				reg_value << 16);
		clrsetbits_le32(&denali_ctl[155], 0xFFFF << 16,
				reg_value << 16);

		clrsetbits_le32(&denali_pi[127], 0xFF << 8, reg_value << 8);
		clrsetbits_le32(&denali_pi[134], 0xFF << 24, reg_value << 24);
		clrsetbits_le32(&denali_pi[142], 0xFF << 8, reg_value << 8);
		clrsetbits_le32(&denali_pi[149], 0xFF << 24, reg_value << 24);
		break;
	}
}

/*
 * b_reg: indicate whether set phy register
 * or just set sdram_params.
 * if b_reg = 0, channel, mr5 are not care
 */
static void set_lp4_MR14(const struct chan_info *chan,
			 struct rk3399_sdram_params *sdram_params, u32 ctl_fn,
			 u32 b_reg, u32 channel, u32 mr5)
{
	u32 *denali_ctl;
	u32 *denali_pi;
	u32 reg_value;
	struct io_setting *io;

	if (b_reg) {
		denali_pi = chan->pi->denali_pi;
		denali_ctl = chan->pctl->denali_ctl;
	} else {
		denali_pi = sdram_params->pi_regs.denali_pi;
		denali_ctl = sdram_params->pctl_regs.denali_ctl;
	}
	io = get_io_set(sdram_params, mr5);

	reg_value = io->dq_vref;
	switch (ctl_fn) {
	case 0:
		clrsetbits_le32(&denali_ctl[142], 0xFFFF << 16,
				reg_value << 16);
		clrsetbits_le32(&denali_ctl[156], 0xFFFF << 16,
				reg_value << 16);

		clrsetbits_le32(&denali_pi[132], 0xFF << 16, reg_value << 16);
		clrsetbits_le32(&denali_pi[140], 0xFF << 0, reg_value << 0);
		clrsetbits_le32(&denali_pi[147], 0xFF << 16, reg_value << 16);
		clrsetbits_le32(&denali_pi[155], 0xFF << 0, reg_value << 0);
		break;
	case 1:
		clrsetbits_le32(&denali_ctl[143], 0xFFFF, reg_value);
		clrsetbits_le32(&denali_ctl[157], 0xFFFF, reg_value);

		clrsetbits_le32(&denali_pi[130], 0xFF << 0, reg_value << 0);
		clrsetbits_le32(&denali_pi[137], 0xFF << 16, reg_value << 16);
		clrsetbits_le32(&denali_pi[145], 0xFF << 0, reg_value << 0);
		clrsetbits_le32(&denali_pi[152], 0xFF << 16, reg_value << 16);
		break;
	case 2:
	default:
		clrsetbits_le32(&denali_ctl[143], 0xFFFF << 16,
				reg_value << 16);
		clrsetbits_le32(&denali_ctl[157], 0xFFFF << 16,
				reg_value << 16);

		clrsetbits_le32(&denali_pi[127], 0xFF << 16, reg_value << 16);
		clrsetbits_le32(&denali_pi[135], 0xFF << 0, reg_value << 0);
		clrsetbits_le32(&denali_pi[142], 0xFF << 16, reg_value << 16);
		clrsetbits_le32(&denali_pi[150], 0xFF << 0, reg_value << 0);
		break;
	}
}

static void modify_param(const struct chan_info *chan,
			 struct rk3399_sdram_params *sdram_params)
{
	struct rk3399_sdram_params *params;
	u32 *denali_ctl_params;
	u32 *denali_pi_params;
	u32 *denali_phy_params;

	denali_ctl_params = sdram_params->pctl_regs.denali_ctl;
	denali_pi_params = sdram_params->pi_regs.denali_pi;
	denali_phy_params = sdram_params->phy_regs.denali_phy;

	if (sdram_params->base.dramtype == LPDDR4) {
		set_lp4_dq_odt(chan, sdram_params, 2, 1, 0, 0, 0);
		set_lp4_ca_odt(chan, sdram_params, 2, 1, 0, 0, 0);
		set_lp4_MR3(chan, sdram_params, 2, 0, 0, 0);
		set_lp4_MR12(chan, sdram_params, 2, 0, 0, 0);
		set_lp4_MR14(chan, sdram_params, 2, 0, 0, 0);
		params = get_phy_index_params(0, sdram_params);
		set_ds_odt(chan, params, 0, 0, 0);
		/* read two cycle preamble */
		clrsetbits_le32(&denali_ctl_params[200], 0x3 << 24, 0x3 << 24);
		clrsetbits_le32(&denali_phy_params[7], 0x3 << 24, 0x3 << 24);
		clrsetbits_le32(&denali_phy_params[135], 0x3 << 24, 0x3 << 24);
		clrsetbits_le32(&denali_phy_params[263], 0x3 << 24, 0x3 << 24);
		clrsetbits_le32(&denali_phy_params[391], 0x3 << 24, 0x3 << 24);

		/* boot frequency two cycle preamble */
		clrsetbits_le32(&denali_phy_params[2], 0x3 << 16, 0x3 << 16);
		clrsetbits_le32(&denali_phy_params[130], 0x3 << 16, 0x3 << 16);
		clrsetbits_le32(&denali_phy_params[258], 0x3 << 16, 0x3 << 16);
		clrsetbits_le32(&denali_phy_params[386], 0x3 << 16, 0x3 << 16);

		clrsetbits_le32(&denali_pi_params[45], 0x3 << 8, 0x3 << 8);
		clrsetbits_le32(&denali_pi_params[58], 0x1, 0x1);

		/*
		 * bypass mode need PHY_SLICE_PWR_RDC_DISABLE_x = 1,
		 * boot frequency mode use bypass mode
		 */
		setbits_le32(&denali_phy_params[10], 1 << 16);
		setbits_le32(&denali_phy_params[138], 1 << 16);
		setbits_le32(&denali_phy_params[266], 1 << 16);
		setbits_le32(&denali_phy_params[394], 1 << 16);
	} else {
		/* modify PHY F0/F1/F2 params */
		params = get_phy_index_params(0, sdram_params);
		set_ds_odt(chan, params, 0, 0, 0);
	}

	clrsetbits_le32(&denali_pi_params[45], 0x1 << 24, 0x1 << 24);
	clrsetbits_le32(&denali_pi_params[61], 0x1 << 24, 0x1 << 24);
	clrsetbits_le32(&denali_pi_params[76], 0x1 << 24, 0x1 << 24);
	clrsetbits_le32(&denali_pi_params[77], 0x1, 0x1);
}

static int pctl_cfg(const struct chan_info *chan, u32 channel,
		    struct rk3399_sdram_params *sdram_params)
{
	u32 *denali_ctl = chan->pctl->denali_ctl;
	u32 *denali_pi = chan->pi->denali_pi;
	u32 *denali_phy = chan->publ->denali_phy;
	const u32 *params_ctl = sdram_params->pctl_regs.denali_ctl;
	const u32 *params_phy = sdram_params->phy_regs.denali_phy;
	u32 tmp, tmp1, tmp2;
	struct rk3399_sdram_params *params;
	u32 byte;

	modify_param(chan, sdram_params);
	/*
	 * work around controller bug:
	 * Do not program DRAM_CLASS until NO_PHY_IND_TRAIN_INT is programmed
	 */
	sdram_copy_to_reg(&denali_ctl[1], &params_ctl[1],
			  sizeof(struct rk3399_ddr_pctl_regs) - 4);
	writel(params_ctl[0], &denali_ctl[0]);

	/*
	 * two channel init at the same time, then ZQ Cal Start
	 * at the same time, it will use the same RZQ.
	 * to fix it: increase tINIT3 for channel 1, will avoid two
	 * channel ZQ Cal Start at the same time
	 */
	if (sdram_params->base.dramtype == LPDDR4 && channel == 1) {
		tmp = ((1000000 * (sdram_params->base.ddr_freq / MHz) + 999) /
		       1000);
		tmp1 = readl(&denali_ctl[14]);
		writel(tmp + tmp1, &denali_ctl[14]);
	}

	sdram_copy_to_reg(denali_pi, &sdram_params->pi_regs.denali_pi[0],
			  sizeof(struct rk3399_ddr_pi_regs));
	/* rank count need to set for init */
	set_memory_map(chan, channel, sdram_params);

	writel(sdram_params->phy_regs.denali_phy[910], &denali_phy[910]);
	writel(sdram_params->phy_regs.denali_phy[911], &denali_phy[911]);
	writel(sdram_params->phy_regs.denali_phy[912], &denali_phy[912]);

	if (sdram_params->base.dramtype == LPDDR4) {
		writel(sdram_params->phy_regs.denali_phy[898],
		       &denali_phy[898]);
		writel(sdram_params->phy_regs.denali_phy[919],
		       &denali_phy[919]);
	}

	g_pwrup_srefresh_exit[channel] = readl(&denali_ctl[68]) &
					 PWRUP_SREFRESH_EXIT;
	clrbits_le32(&denali_ctl[68], PWRUP_SREFRESH_EXIT);

	/* PHY_DLL_RST_EN */
	clrsetbits_le32(&denali_phy[957], 0x3 << 24, 1 << 24);

	setbits_le32(&denali_pi[0], START);
	setbits_le32(&denali_ctl[0], START);

	/* because LPDDR4 use PLL bypass mode for init
	 * not need to wait for the PLL to lock
	 */
	if (sdram_params->base.dramtype != LPDDR4) {
		/* wait lock */
		while (1) {
			tmp = readl(&denali_phy[920]);
			tmp1 = readl(&denali_phy[921]);
			tmp2 = readl(&denali_phy[922]);
			if ((((tmp >> 16) & 0x1) == 0x1) &&
			    (((tmp1 >> 16) & 0x1) == 0x1) &&
			    (((tmp1 >> 0) & 0x1) == 0x1) &&
			    (((tmp2 >> 0) & 0x1) == 0x1))
				break;
		}
	}

	sdram_copy_to_reg(&denali_phy[896], &params_phy[896], (958 - 895) * 4);
	sdram_copy_to_reg(&denali_phy[0], &params_phy[0], (90 - 0 + 1) * 4);
	sdram_copy_to_reg(&denali_phy[128],
			  &params_phy[128], (218 - 128 + 1) * 4);
	sdram_copy_to_reg(&denali_phy[256],
			  &params_phy[256], (346 - 256 + 1) * 4);
	sdram_copy_to_reg(&denali_phy[384],
			  &params_phy[384], (474 - 384 + 1) * 4);
	sdram_copy_to_reg(&denali_phy[512],
			  &params_phy[512], (549 - 512 + 1) * 4);
	sdram_copy_to_reg(&denali_phy[640],
			  &params_phy[640], (677 - 640 + 1) * 4);
	sdram_copy_to_reg(&denali_phy[768],
			  &params_phy[768], (805 - 768 + 1) * 4);

	if (sdram_params->base.dramtype == LPDDR4)
		params = get_phy_index_params(1, sdram_params);
	else
		params = get_phy_index_params(0, sdram_params);

	clrsetbits_le32(&params->phy_regs.denali_phy[896], 0x3 << 8,
			0 << 8);
	writel(params->phy_regs.denali_phy[896], &denali_phy[896]);

	writel(sdram_params->phy_regs.denali_phy[83] + (0x10 << 16),
	       &denali_phy[83]);
	writel(sdram_params->phy_regs.denali_phy[84] + (0x10 << 8),
	       &denali_phy[84]);
	writel(sdram_params->phy_regs.denali_phy[211] + (0x10 << 16),
	       &denali_phy[211]);
	writel(sdram_params->phy_regs.denali_phy[212] + (0x10 << 8),
	       &denali_phy[212]);
	writel(sdram_params->phy_regs.denali_phy[339] + (0x10 << 16),
	       &denali_phy[339]);
	writel(sdram_params->phy_regs.denali_phy[340] + (0x10 << 8),
	       &denali_phy[340]);
	writel(sdram_params->phy_regs.denali_phy[467] + (0x10 << 16),
	       &denali_phy[467]);
	writel(sdram_params->phy_regs.denali_phy[468] + (0x10 << 8),
	       &denali_phy[468]);

	if (sdram_params->base.dramtype == LPDDR4) {
		/*
		 * to improve write dqs and dq phase from 1.5ns to 3.5ns
		 * at 50MHz.
		 */
		for (byte = 0; byte < 4; byte++) {
			tmp = 0x680;
			clrsetbits_le32(&denali_phy[1 + (128 * byte)],
					0xfff << 8, tmp << 8);
		}
		/*
		 * to workaround 366ball two channel's RESET connect to
		 * one RESET signal of die
		 */
		if (channel == 1)
			clrsetbits_le32(&denali_phy[937], 0xff,
					PHY_DRV_ODT_240 |
					(PHY_DRV_ODT_240 << 0x4));
	}

	return 0;
}

static void select_per_cs_training_index(const struct chan_info *chan,
					 u32 rank)
{
	u32 *denali_phy = chan->publ->denali_phy;

	/* PHY_84 PHY_PER_CS_TRAINING_EN_0 1bit offset_16 */
	if ((readl(&denali_phy[84]) >> 16) & 1) {
		/*
		 * PHY_8/136/264/392
		 * phy_per_cs_training_index_X 1bit offset_24
		 */
		clrsetbits_le32(&denali_phy[8], 0x1 << 24, rank << 24);
		clrsetbits_le32(&denali_phy[136], 0x1 << 24, rank << 24);
		clrsetbits_le32(&denali_phy[264], 0x1 << 24, rank << 24);
		clrsetbits_le32(&denali_phy[392], 0x1 << 24, rank << 24);
	}
}

static void override_write_leveling_value(const struct chan_info *chan)
{
	u32 *denali_ctl = chan->pctl->denali_ctl;
	u32 *denali_phy = chan->publ->denali_phy;
	u32 byte;

	/* PHY_896 PHY_FREQ_SEL_MULTICAST_EN 1bit offset_0 */
	setbits_le32(&denali_phy[896], 1);

	/*
	 * PHY_8/136/264/392
	 * phy_per_cs_training_multicast_en_X 1bit offset_16
	 */
	clrsetbits_le32(&denali_phy[8], 0x1 << 16, 1 << 16);
	clrsetbits_le32(&denali_phy[136], 0x1 << 16, 1 << 16);
	clrsetbits_le32(&denali_phy[264], 0x1 << 16, 1 << 16);
	clrsetbits_le32(&denali_phy[392], 0x1 << 16, 1 << 16);

	for (byte = 0; byte < 4; byte++)
		clrsetbits_le32(&denali_phy[63 + (128 * byte)], 0xffff << 16,
				0x200 << 16);

	/* PHY_896 PHY_FREQ_SEL_MULTICAST_EN 1bit offset_0 */
	clrbits_le32(&denali_phy[896], 1);

	/* CTL_200 ctrlupd_req 1bit offset_8 */
	clrsetbits_le32(&denali_ctl[200], 0x1 << 8, 0x1 << 8);
}

static int data_training_ca(const struct chan_info *chan, u32 channel,
			    const struct rk3399_sdram_params *sdram_params)
{
	u32 *denali_pi = chan->pi->denali_pi;
	u32 *denali_phy = chan->publ->denali_phy;
	u32 i, tmp;
	u32 obs_0, obs_1, obs_2, obs_err = 0;
	u32 rank = sdram_params->ch[channel].cap_info.rank;
	u32 rank_mask;

	/* clear interrupt,PI_175 PI_INT_ACK:WR:0:17 */
	writel(0x00003f7c, (&denali_pi[175]));

	if (sdram_params->base.dramtype == LPDDR4)
		rank_mask = (rank == 1) ? 0x5 : 0xf;
	else
		rank_mask = (rank == 1) ? 0x1 : 0x3;

	for (i = 0; i < 4; i++) {
		if (!(rank_mask & (1 << i)))
			continue;
		select_per_cs_training_index(chan, i);
		/* PI_100 PI_CALVL_EN:RW:8:2 */
		clrsetbits_le32(&denali_pi[100], 0x3 << 8, 0x2 << 8);
		/* PI_92 PI_CALVL_REQ:WR:16:1,PI_CALVL_CS:RW:24:2 */
		clrsetbits_le32(&denali_pi[92],
				(0x1 << 16) | (0x3 << 24),
				(0x1 << 16) | (i << 24));

		/* Waiting for training complete */
		while (1) {
			/* PI_174 PI_INT_STATUS:RD:8:18 */
			tmp = readl(&denali_pi[174]) >> 8;
			/*
			 * check status obs
			 * PHY_532/660/789 phy_adr_calvl_obs1_:0:32
			 */
			obs_0 = readl(&denali_phy[532]);
			obs_1 = readl(&denali_phy[660]);
			obs_2 = readl(&denali_phy[788]);
			if (((obs_0 >> 30) & 0x3) ||
			    ((obs_1 >> 30) & 0x3) ||
			    ((obs_2 >> 30) & 0x3))
				obs_err = 1;
			if ((((tmp >> 11) & 0x1) == 0x1) &&
			    (((tmp >> 13) & 0x1) == 0x1) &&
			    (((tmp >> 5) & 0x1) == 0x0) &&
			    obs_err == 0)
				break;
			else if ((((tmp >> 5) & 0x1) == 0x1) ||
				 (obs_err == 1))
				return -EIO;
		}
		/* clear interrupt,PI_175 PI_INT_ACK:WR:0:17 */
		writel(0x00003f7c, (&denali_pi[175]));
	}
	clrbits_le32(&denali_pi[100], 0x3 << 8);

	return 0;
}

static int data_training_wl(const struct chan_info *chan, u32 channel,
			    const struct rk3399_sdram_params *sdram_params)
{
	u32 *denali_pi = chan->pi->denali_pi;
	u32 *denali_phy = chan->publ->denali_phy;
	u32 i, tmp;
	u32 obs_0, obs_1, obs_2, obs_3, obs_err = 0;
	u32 rank = sdram_params->ch[channel].cap_info.rank;

	/* clear interrupt,PI_175 PI_INT_ACK:WR:0:17 */
	writel(0x00003f7c, (&denali_pi[175]));

	for (i = 0; i < rank; i++) {
		select_per_cs_training_index(chan, i);
		/* PI_60 PI_WRLVL_EN:RW:8:2 */
		clrsetbits_le32(&denali_pi[60], 0x3 << 8, 0x2 << 8);
		/* PI_59 PI_WRLVL_REQ:WR:8:1,PI_WRLVL_CS:RW:16:2 */
		clrsetbits_le32(&denali_pi[59],
				(0x1 << 8) | (0x3 << 16),
				(0x1 << 8) | (i << 16));

		/* Waiting for training complete */
		while (1) {
			/* PI_174 PI_INT_STATUS:RD:8:18 */
			tmp = readl(&denali_pi[174]) >> 8;

			/*
			 * check status obs, if error maybe can not
			 * get leveling done PHY_40/168/296/424
			 * phy_wrlvl_status_obs_X:0:13
			 */
			obs_0 = readl(&denali_phy[40]);
			obs_1 = readl(&denali_phy[168]);
			obs_2 = readl(&denali_phy[296]);
			obs_3 = readl(&denali_phy[424]);
			if (((obs_0 >> 12) & 0x1) ||
			    ((obs_1 >> 12) & 0x1) ||
			    ((obs_2 >> 12) & 0x1) ||
			    ((obs_3 >> 12) & 0x1))
				obs_err = 1;
			if ((((tmp >> 10) & 0x1) == 0x1) &&
			    (((tmp >> 13) & 0x1) == 0x1) &&
			    (((tmp >> 4) & 0x1) == 0x0) &&
			    obs_err == 0)
				break;
			else if ((((tmp >> 4) & 0x1) == 0x1) ||
				 (obs_err == 1))
				return -EIO;
		}
		/* clear interrupt,PI_175 PI_INT_ACK:WR:0:17 */
		writel(0x00003f7c, (&denali_pi[175]));
	}

	override_write_leveling_value(chan);
	clrbits_le32(&denali_pi[60], 0x3 << 8);

	return 0;
}

static int data_training_rg(const struct chan_info *chan, u32 channel,
			    const struct rk3399_sdram_params *sdram_params)
{
	u32 *denali_pi = chan->pi->denali_pi;
	u32 *denali_phy = chan->publ->denali_phy;
	u32 i, tmp;
	u32 obs_0, obs_1, obs_2, obs_3, obs_err = 0;
	u32 rank = sdram_params->ch[channel].cap_info.rank;

	/* clear interrupt,PI_175 PI_INT_ACK:WR:0:17 */
	writel(0x00003f7c, (&denali_pi[175]));

	for (i = 0; i < rank; i++) {
		select_per_cs_training_index(chan, i);
		/* PI_80 PI_RDLVL_GATE_EN:RW:24:2 */
		clrsetbits_le32(&denali_pi[80], 0x3 << 24, 0x2 << 24);
		/*
		 * PI_74 PI_RDLVL_GATE_REQ:WR:16:1
		 * PI_RDLVL_CS:RW:24:2
		 */
		clrsetbits_le32(&denali_pi[74],
				(0x1 << 16) | (0x3 << 24),
				(0x1 << 16) | (i << 24));

		/* Waiting for training complete */
		while (1) {
			/* PI_174 PI_INT_STATUS:RD:8:18 */
			tmp = readl(&denali_pi[174]) >> 8;

			/*
			 * check status obs
			 * PHY_43/171/299/427
			 *     PHY_GTLVL_STATUS_OBS_x:16:8
			 */
			obs_0 = readl(&denali_phy[43]);
			obs_1 = readl(&denali_phy[171]);
			obs_2 = readl(&denali_phy[299]);
			obs_3 = readl(&denali_phy[427]);
			if (((obs_0 >> (16 + 6)) & 0x3) ||
			    ((obs_1 >> (16 + 6)) & 0x3) ||
			    ((obs_2 >> (16 + 6)) & 0x3) ||
			    ((obs_3 >> (16 + 6)) & 0x3))
				obs_err = 1;
			if ((((tmp >> 9) & 0x1) == 0x1) &&
			    (((tmp >> 13) & 0x1) == 0x1) &&
			    (((tmp >> 3) & 0x1) == 0x0) &&
			    obs_err == 0)
				break;
			else if ((((tmp >> 3) & 0x1) == 0x1) ||
				 (obs_err == 1))
				return -EIO;
		}
		/* clear interrupt,PI_175 PI_INT_ACK:WR:0:17 */
		writel(0x00003f7c, (&denali_pi[175]));
	}
	clrbits_le32(&denali_pi[80], 0x3 << 24);

	return 0;
}

static int data_training_rl(const struct chan_info *chan, u32 channel,
			    const struct rk3399_sdram_params *sdram_params)
{
	u32 *denali_pi = chan->pi->denali_pi;
	u32 i, tmp;
	u32 rank = sdram_params->ch[channel].cap_info.rank;

	/* clear interrupt,PI_175 PI_INT_ACK:WR:0:17 */
	writel(0x00003f7c, (&denali_pi[175]));

	for (i = 0; i < rank; i++) {
		select_per_cs_training_index(chan, i);
		/* PI_80 PI_RDLVL_EN:RW:16:2 */
		clrsetbits_le32(&denali_pi[80], 0x3 << 16, 0x2 << 16);
		/* PI_74 PI_RDLVL_REQ:WR:8:1,PI_RDLVL_CS:RW:24:2 */
		clrsetbits_le32(&denali_pi[74],
				(0x1 << 8) | (0x3 << 24),
				(0x1 << 8) | (i << 24));

		/* Waiting for training complete */
		while (1) {
			/* PI_174 PI_INT_STATUS:RD:8:18 */
			tmp = readl(&denali_pi[174]) >> 8;

			/*
			 * make sure status obs not report error bit
			 * PHY_46/174/302/430
			 *     phy_rdlvl_status_obs_X:16:8
			 */
			if ((((tmp >> 8) & 0x1) == 0x1) &&
			    (((tmp >> 13) & 0x1) == 0x1) &&
			    (((tmp >> 2) & 0x1) == 0x0))
				break;
			else if (((tmp >> 2) & 0x1) == 0x1)
				return -EIO;
		}
		/* clear interrupt,PI_175 PI_INT_ACK:WR:0:17 */
		writel(0x00003f7c, (&denali_pi[175]));
	}
	clrbits_le32(&denali_pi[80], 0x3 << 16);

	return 0;
}

static int data_training_wdql(const struct chan_info *chan, u32 channel,
			      const struct rk3399_sdram_params *sdram_params)
{
	u32 *denali_pi = chan->pi->denali_pi;
	u32 i, tmp;
	u32 rank = sdram_params->ch[channel].cap_info.rank;
	u32 rank_mask;

	/* clear interrupt,PI_175 PI_INT_ACK:WR:0:17 */
	writel(0x00003f7c, (&denali_pi[175]));

	if (sdram_params->base.dramtype == LPDDR4)
		rank_mask = (rank == 1) ? 0x5 : 0xf;
	else
		rank_mask = (rank == 1) ? 0x1 : 0x3;

	for (i = 0; i < 4; i++) {
		if (!(rank_mask & (1 << i)))
			continue;

		select_per_cs_training_index(chan, i);
		/*
		 * disable PI_WDQLVL_VREF_EN before wdq leveling?
		 * PI_117 PI_WDQLVL_VREF_EN:RW:8:1
		 */
		clrbits_le32(&denali_pi[117], 0x1 << 8);
		/* PI_124 PI_WDQLVL_EN:RW:16:2 */
		clrsetbits_le32(&denali_pi[124], 0x3 << 16, 0x2 << 16);
		/* PI_121 PI_WDQLVL_REQ:WR:8:1,PI_WDQLVL_CS:RW:16:2 */
		clrsetbits_le32(&denali_pi[121],
				(0x1 << 8) | (0x3 << 16),
				(0x1 << 8) | (i << 16));

		/* Waiting for training complete */
		while (1) {
			/* PI_174 PI_INT_STATUS:RD:8:18 */
			tmp = readl(&denali_pi[174]) >> 8;
			if ((((tmp >> 12) & 0x1) == 0x1) &&
			    (((tmp >> 13) & 0x1) == 0x1) &&
			    (((tmp >> 6) & 0x1) == 0x0))
				break;
			else if (((tmp >> 6) & 0x1) == 0x1)
				return -EIO;
		}
		/* clear interrupt,PI_175 PI_INT_ACK:WR:0:17 */
		writel(0x00003f7c, (&denali_pi[175]));
	}
	clrbits_le32(&denali_pi[124], 0x3 << 16);

	return 0;
}

static int data_training(const struct chan_info *chan, u32 channel,
			 const struct rk3399_sdram_params *sdram_params,
			 u32 training_flag)
{
	u32 *denali_phy = chan->publ->denali_phy;
	int ret = 0;

	/* PHY_927 PHY_PAD_DQS_DRIVE  RPULL offset_22 */
	setbits_le32(&denali_phy[927], (1 << 22));

	if (training_flag == PI_FULL_TRAINING) {
		if (sdram_params->base.dramtype == LPDDR4) {
			training_flag = PI_WRITE_LEVELING |
					PI_READ_GATE_TRAINING |
					PI_READ_LEVELING | PI_WDQ_LEVELING;
		} else if (sdram_params->base.dramtype == LPDDR3) {
			training_flag = PI_CA_TRAINING | PI_WRITE_LEVELING |
					PI_READ_GATE_TRAINING;
		} else if (sdram_params->base.dramtype == DDR3) {
			training_flag = PI_WRITE_LEVELING |
					PI_READ_GATE_TRAINING |
					PI_READ_LEVELING;
		}
	}

	/* ca training(LPDDR4,LPDDR3 support) */
	if ((training_flag & PI_CA_TRAINING) == PI_CA_TRAINING) {
		ret = data_training_ca(chan, channel, sdram_params);
		if (ret != 0)
			goto out;
	}

	/* write leveling(LPDDR4,LPDDR3,DDR3 support) */
	if ((training_flag & PI_WRITE_LEVELING) == PI_WRITE_LEVELING) {
		ret = data_training_wl(chan, channel, sdram_params);
		if (ret != 0)
			goto out;
	}

	/* read gate training(LPDDR4,LPDDR3,DDR3 support) */
	if ((training_flag & PI_READ_GATE_TRAINING) == PI_READ_GATE_TRAINING) {
		ret = data_training_rg(chan, channel, sdram_params);
		if (ret != 0)
			goto out;
	}

	/* read leveling(LPDDR4,LPDDR3,DDR3 support) */
	if ((training_flag & PI_READ_LEVELING) == PI_READ_LEVELING) {
		ret = data_training_rl(chan, channel, sdram_params);
		if (ret != 0)
			goto out;
	}

	/* wdq leveling(LPDDR4 support) */
	if ((training_flag & PI_WDQ_LEVELING) == PI_WDQ_LEVELING) {
		ret = data_training_wdql(chan, channel, sdram_params);
		if (ret != 0)
			goto out;
	}

	/* PHY_927 PHY_PAD_DQS_DRIVE  RPULL offset_22 */
	clrbits_le32(&denali_phy[927], (1 << 22));

out:
	return ret;
}

static void set_ddrconfig(const struct chan_info *chan,
			  const struct rk3399_sdram_params *sdram_params,
			  unsigned char channel, u32 ddrconfig)
{
	/* only need to set ddrconfig */
	struct msch_regs *ddr_msch_regs = chan->msch;
	unsigned int cs0_cap = 0;
	unsigned int cs1_cap = 0;

	cs0_cap = (1 << (sdram_params->ch[channel].cap_info.cs0_row
			+ sdram_params->ch[channel].cap_info.col
			+ sdram_params->ch[channel].cap_info.bk
			+ sdram_params->ch[channel].cap_info.bw - 20));
	if (sdram_params->ch[channel].cap_info.rank > 1)
		cs1_cap = cs0_cap >> (sdram_params->ch[channel].cap_info.cs0_row
				- sdram_params->ch[channel].cap_info.cs1_row);
	if (sdram_params->ch[channel].cap_info.row_3_4) {
		cs0_cap = cs0_cap * 3 / 4;
		cs1_cap = cs1_cap * 3 / 4;
	}

	writel(ddrconfig | (ddrconfig << 8), &ddr_msch_regs->ddrconf);
	writel(((cs0_cap / 32) & 0xff) | (((cs1_cap / 32) & 0xff) << 8),
	       &ddr_msch_regs->ddrsize);
}

static void sdram_msch_config(struct msch_regs *msch,
			      struct sdram_msch_timings *noc_timings)
{
	writel(noc_timings->ddrtiminga0.d32,
	       &msch->ddrtiminga0.d32);
	writel(noc_timings->ddrtimingb0.d32,
	       &msch->ddrtimingb0.d32);
	writel(noc_timings->ddrtimingc0.d32,
	       &msch->ddrtimingc0.d32);
	writel(noc_timings->devtodev0.d32,
	       &msch->devtodev0.d32);
	writel(noc_timings->ddrmode.d32,
	       &msch->ddrmode.d32);
}

static void dram_all_config(struct dram_info *dram,
			    struct rk3399_sdram_params *sdram_params)
{
	u32 sys_reg2 = 0;
	u32 sys_reg3 = 0;
	unsigned int channel, idx;

	for (channel = 0, idx = 0;
	     (idx < sdram_params->base.num_channels) && (channel < 2);
	     channel++) {
		struct msch_regs *ddr_msch_regs;
		struct sdram_msch_timings *noc_timing;

		if (sdram_params->ch[channel].cap_info.col == 0)
			continue;
		idx++;
		sdram_org_config(&sdram_params->ch[channel].cap_info,
				 &sdram_params->base, &sys_reg2,
				 &sys_reg3, channel);
		ddr_msch_regs = dram->chan[channel].msch;
		noc_timing = &sdram_params->ch[channel].noc_timings;
		sdram_msch_config(ddr_msch_regs, noc_timing);

		/* rank 1 memory clock disable (dfi_dram_clk_disable = 1) */
		if (sdram_params->ch[channel].cap_info.rank == 1)
			setbits_le32(&dram->chan[channel].pctl->denali_ctl[276],
				     1 << 17);
	}

	writel(sys_reg2, &dram->pmugrf->os_reg2);
	writel(sys_reg3, &dram->pmugrf->os_reg3);
	rk_clrsetreg(&dram->pmusgrf->soc_con4, 0x1f << 10,
		     sdram_params->base.stride << 10);

	/* reboot hold register set */
	writel(PRESET_SGRF_HOLD(0) | PRESET_GPIO0_HOLD(1) |
		PRESET_GPIO1_HOLD(1),
		&dram->pmucru->pmucru_rstnhold_con[1]);
	clrsetbits_le32(&dram->cru->glb_rst_con, 0x3, 0x3);
}

static int switch_to_phy_index1(struct dram_info *dram,
				const struct rk3399_sdram_params *sdram_params)
{
	u32 channel;
	u32 *denali_phy;
	u32 ch_count = sdram_params->base.num_channels;
	int ret;
	int i = 0;

	writel(RK_CLRSETBITS(0x03 << 4 | 1 << 2 | 1,
			     1 << 4 | 1 << 2 | 1),
			&dram->cic->cic_ctrl0);
	while (!(readl(&dram->cic->cic_status0) & (1 << 2))) {
		mdelay(10);
		i++;
		if (i > 10) {
			debug("index1 frequency change overtime\n");
			return -ETIME;
		}
	}

	i = 0;
	writel(RK_CLRSETBITS(1 << 1, 1 << 1), &dram->cic->cic_ctrl0);
	while (!(readl(&dram->cic->cic_status0) & (1 << 0))) {
		mdelay(10);
		if (i > 10) {
			debug("index1 frequency done overtime\n");
			return -ETIME;
		}
	}

	for (channel = 0; channel < ch_count; channel++) {
		denali_phy = dram->chan[channel].publ->denali_phy;
		clrsetbits_le32(&denali_phy[896], (0x3 << 8) | 1, 1 << 8);
		ret = data_training(&dram->chan[channel], channel,
				    sdram_params, PI_FULL_TRAINING);
		if (ret) {
			debug("index1 training failed\n");
			return ret;
		}
	}

	return 0;
}

u16  ddr_cfg_2_rbc[] = {
		/*
		 * [6]	  highest bit col
		 * [5:3]  max row(14+n)
		 * [2]    insertion row
		 * [1:0]  col(9+n),col, data bus 32bit
		 *
		 * highbitcol, max_row, insertion_row,  col
		 */
		((0 << 6) | (2 << 3) | (0 << 2) | 0), /* 0 */
		((0 << 6) | (2 << 3) | (0 << 2) | 1), /* 1 */
		((0 << 6) | (1 << 3) | (0 << 2) | 2), /* 2 */
		((0 << 6) | (0 << 3) | (0 << 2) | 3), /* 3 */
		((0 << 6) | (2 << 3) | (1 << 2) | 1), /* 4 */
		((0 << 6) | (1 << 3) | (1 << 2) | 2), /* 5 */
		((1 << 6) | (0 << 3) | (0 << 2) | 2), /* 6 */
		((1 << 6) | (1 << 3) | (0 << 2) | 2), /* 7 */
};

static u32 calculate_ddrconfig(struct rk3399_sdram_params *sdram_params,
			       u32 channel)
{
	unsigned int i;
	unsigned int cs0_row = sdram_params->ch[channel].cap_info.cs0_row;
	unsigned int col = sdram_params->ch[channel].cap_info.col;
	unsigned int bw = sdram_params->ch[channel].cap_info.bw;

	col -= (bw == 2) ? 0 : 1;
	col -= 9;

	for (i = 0; i < 4; i++) {
		if ((col == (ddr_cfg_2_rbc[i] & 0x3)) &&
		    (cs0_row <= (((ddr_cfg_2_rbc[i] >> 3) & 0x7) + 14)))
			break;
	}

	if (i >= 4)
		i = -1;

	return i;
}

static unsigned char calculate_stride(struct rk3399_sdram_params *sdram_params)
{
	unsigned int gstride_type;
	unsigned int channel;
	unsigned int chinfo = 0;
	unsigned int cap = 0;
	unsigned int stride = -1;
	unsigned int ch_cap[2] = {0, 0};

	gstride_type = STRIDE_256B;

	for (channel = 0; channel < 2; channel++) {
		unsigned int cs0_cap = 0;
		unsigned int cs1_cap = 0;
		struct sdram_cap_info *cap_info =
			&sdram_params->ch[channel].cap_info;

		if (cap_info->col == 0)
			continue;

		cs0_cap = (1 << (cap_info->cs0_row + cap_info->col +
				 cap_info->bk + cap_info->bw - 20));
		if (cap_info->rank > 1)
			cs1_cap = cs0_cap >> (cap_info->cs0_row
					      - cap_info->cs1_row);
		if (cap_info->row_3_4) {
			cs0_cap = cs0_cap * 3 / 4;
			cs1_cap = cs1_cap * 3 / 4;
		}
		ch_cap[channel] = cs0_cap + cs1_cap;
		chinfo |= 1 << channel;
	}

	cap = ch_cap[0] + ch_cap[1];
	if (sdram_params->base.num_channels == 1) {
		if (chinfo & 1) /* channel a only */
			stride = 0x17;
		else /* channel b only */
			stride = 0x18;
	} else {/* 2 channel */
		if (ch_cap[0] == ch_cap[1]) {
			/* interleaved */
			if (gstride_type == PART_STRIDE) {
			/*
			 * first 64MB no interleaved other 256B interleaved
			 * if 786M+768M.useful space from 0-1280MB and
			 * 1536MB-1792MB
			 * if 1.5G+1.5G(continuous).useful space from 0-2560MB
			 * and 3072MB-3584MB
			 */
				stride = 0x1F;
			} else {
				switch (cap) {
				/* 512MB */
				case 512:
					stride = 0;
					break;
				/* 1GB unstride or 256B stride*/
				case 1024:
					stride = (gstride_type == UN_STRIDE) ?
						0x1 : 0x5;
					break;
				/*
				 * 768MB + 768MB same as total 2GB memory
				 * useful space: 0-768MB 1GB-1792MB
				 */
				case 1536:
				/* 2GB unstride or 256B or 512B stride */
				case 2048:
					stride = (gstride_type == UN_STRIDE) ?
						0x2 :
						((gstride_type == STRIDE_512B) ?
						 0xA : 0x9);
					break;
				/* 1536MB + 1536MB */
				case 3072:
					stride = (gstride_type == UN_STRIDE) ?
						0x3 :
						((gstride_type == STRIDE_512B) ?
						 0x12 : 0x11);
					break;
				/* 4GB  unstride or 128B,256B,512B,4KB stride */
				case 4096:
					stride = (gstride_type == UN_STRIDE) ?
						0x3 : (0xC + gstride_type);
					break;
				}
			}
		}
		if (ch_cap[0] == 2048 && ch_cap[1] == 1024) {
			/* 2GB + 1GB */
			stride = (gstride_type == UN_STRIDE) ? 0x3 : 0x19;
		}
		/*
		 * remain two channel capability not equal OR capability
		 * power function of 2
		 */
		if (stride == (-1)) {
			switch ((ch_cap[0] > ch_cap[1]) ?
				ch_cap[0] : ch_cap[1]) {
			case 256: /* 256MB + 128MB */
				stride = 0;
				break;
			case 512: /* 512MB + 256MB */
				stride = 1;
				break;
			case 1024:/* 1GB + 128MB/256MB/384MB/512MB/768MB */
				stride = 2;
				break;
			case 2048: /* 2GB + 128MB/256MB/384MB/512MB/768MB/1GB */
				stride = 3;
				break;
			default:
				break;
			}
		}
		if (stride == (-1))
			goto error;
	}
	switch (stride) {
	case 0xc:
		printf("128B stride\n");
		break;
	case 5:
	case 9:
	case 0xd:
	case 0x11:
	case 0x19:
		printf("256B stride\n");
		break;
	case 0xa:
	case 0xe:
	case 0x12:
		printf("512B stride\n");
		break;
	case 0xf:
		printf("4K stride\n");
		break;
	case 0x1f:
		printf("32MB + 256B stride\n");
		break;
	default:
		printf("no stride\n");
	}

	return stride;
error:
	printf("Cap not support!\n");
	return (-1);
}

static u32 get_ddr_stride(struct rk3399_pmusgrf_regs *pmusgrf)
{
	u32 val;

	val = (readl(&pmusgrf->soc_con4) >> 10) & 0x1F;

	return val;
}

static void set_ddr_stride(struct rk3399_pmusgrf_regs *pmusgrf, u32 stride)
{
	rk_clrsetreg(&pmusgrf->soc_con4, 0x1f << 10,
		     stride << 10);
}

static void set_cap_relate_config(const struct chan_info *chan,
				  struct rk3399_sdram_params *sdram_params,
				  unsigned int channel)
{
	u32 *denali_ctl = chan->pctl->denali_ctl;
	u32 tmp;
	struct sdram_msch_timings *noc_timing;

	if (sdram_params->base.dramtype == LPDDR3) {
		tmp = (8 << sdram_params->ch[channel].cap_info.bw) /
			(8 << sdram_params->ch[channel].cap_info.dbw);
		/* memdata_ratio
		 * 1 -> 0, 2 -> 1, 4 -> 2
		 */
		clrsetbits_le32(&denali_ctl[197], 0x7,
				(tmp >> 1));
		clrsetbits_le32(&denali_ctl[198], 0x7 << 8,
				(tmp >> 1) << 8);
	}
	noc_timing = &sdram_params->ch[channel].noc_timings;
	/*
	 * noc timing bw relate timing is 32 bit, and real bw is 16bit
	 * actually noc reg is setting at function dram_all_config
	 */
	if (sdram_params->ch[channel].cap_info.bw == 16 &&
	    noc_timing->ddrmode.b.mwrsize == 2) {
		if (noc_timing->ddrmode.b.burstsize)
			noc_timing->ddrmode.b.burstsize -= 1;
		noc_timing->ddrmode.b.mwrsize -= 1;
		noc_timing->ddrtimingc0.b.burstpenalty *= 2;
		noc_timing->ddrtimingc0.b.wrtomwr *= 2;
	}
}

static void clear_channel_params(struct rk3399_sdram_params *sdram_params,
				 unsigned int channel)
{
	sdram_params->ch[channel].cap_info.rank = 0;
	sdram_params->ch[channel].cap_info.col = 0;
	sdram_params->ch[channel].cap_info.bk = 0;
	sdram_params->ch[channel].cap_info.bw = 32;
	sdram_params->ch[channel].cap_info.dbw = 32;
	sdram_params->ch[channel].cap_info.row_3_4 = 0;
	sdram_params->ch[channel].cap_info.cs0_row = 0;
	sdram_params->ch[channel].cap_info.cs1_row = 0;
	sdram_params->ch[channel].cap_info.ddrconfig = 0;
}

/* CS0,n=1
 * CS1,n=2
 * CS0 & CS1, n=3
 * cs0_cap: MB unit
 */
static void dram_set_cs(const struct chan_info *chan, u32 cs_map, u32 cs0_cap,
			unsigned char dramtype)
{
	u32 *denali_ctl = chan->pctl->denali_ctl;
	u32 *denali_pi = chan->pi->denali_pi;
	struct msch_regs *ddr_msch_regs = chan->msch;

	clrsetbits_le32(&denali_ctl[196], 0x3, cs_map);
	writel((cs0_cap / 32) | (((4096 - cs0_cap) / 32) << 8),
	       &ddr_msch_regs->ddrsize);
	if (dramtype == LPDDR4) {
		if (cs_map == 1)
			cs_map = 0x5;
		else if (cs_map == 2)
			cs_map = 0xa;
		else
			cs_map = 0xF;
	}
	/*PI_41 PI_CS_MAP:RW:24:4*/
	clrsetbits_le32(&denali_pi[41],
			0xf << 24, cs_map << 24);
	if (cs_map == 1 && dramtype == DDR3)
		writel(0x2EC7FFFF, &denali_pi[34]);
}

static void dram_set_bw(const struct chan_info *chan, u32 bw)
{
	u32 *denali_ctl = chan->pctl->denali_ctl;

	if (bw == 2)
		clrbits_le32(&denali_ctl[196], 1 << 16);
	else
		setbits_le32(&denali_ctl[196], 1 << 16);
}

static void dram_set_max_col(const struct chan_info *chan, u32 bw, u32 *pcol)
{
	u32 *denali_ctl = chan->pctl->denali_ctl;
	struct msch_regs *ddr_msch_regs = chan->msch;
	u32 *denali_pi = chan->pi->denali_pi;
	u32 ddrconfig;

	clrbits_le32(&denali_ctl[191], 0xf);
	clrsetbits_le32(&denali_ctl[190],
			(7 << 24),
			((16 - ((bw == 2) ? 14 : 15)) << 24));
	/*PI_199 PI_COL_DIFF:RW:0:4*/
	clrbits_le32(&denali_pi[199], 0xf);
	/*PI_155 PI_ROW_DIFF:RW:24:3*/
	clrsetbits_le32(&denali_pi[155],
			(7 << 24),
			((16 - 12) << 24));
	ddrconfig = (bw == 2) ? 3 : 2;
	writel(ddrconfig | (ddrconfig << 8), &ddr_msch_regs->ddrconf);
	/* set max cs0 size */
	writel((4096 / 32) | ((0 / 32) << 8),
	       &ddr_msch_regs->ddrsize);

	*pcol = 12;
}

static void dram_set_max_bank(const struct chan_info *chan, u32 bw, u32 *pbank,
			      u32 *pcol)
{
	u32 *denali_ctl = chan->pctl->denali_ctl;
	u32 *denali_pi = chan->pi->denali_pi;

	clrbits_le32(&denali_ctl[191], 0xf);
	clrbits_le32(&denali_ctl[190], (3 << 16));
	/*PI_199 PI_COL_DIFF:RW:0:4*/
	clrbits_le32(&denali_pi[199], 0xf);
	/*PI_155 PI_BANK_DIFF:RW:16:2*/
	clrbits_le32(&denali_pi[155], (3 << 16));

	*pbank = 3;
	*pcol = 12;
}

static void dram_set_max_row(const struct chan_info *chan, u32 bw, u32 *prow,
			     u32 *pbank, u32 *pcol)
{
	u32 *denali_ctl = chan->pctl->denali_ctl;
	u32 *denali_pi = chan->pi->denali_pi;
	struct msch_regs *ddr_msch_regs = chan->msch;

	clrsetbits_le32(&denali_ctl[191], 0xf, 12 - 10);
	clrbits_le32(&denali_ctl[190],
		     (0x3 << 16) | (0x7 << 24));
	/*PI_199 PI_COL_DIFF:RW:0:4*/
	clrsetbits_le32(&denali_pi[199], 0xf, 12 - 10);
	/*PI_155 PI_ROW_DIFF:RW:24:3 PI_BANK_DIFF:RW:16:2*/
	clrbits_le32(&denali_pi[155],
		     (0x3 << 16) | (0x7 << 24));
	writel(1 | (1 << 8), &ddr_msch_regs->ddrconf);
	/* set max cs0 size */
	writel((4096 / 32) | ((0 / 32) << 8),
	       &ddr_msch_regs->ddrsize);

	*prow = 16;
	*pbank = 3;
	*pcol = (bw == 2) ? 10 : 11;
}

static u64 dram_detect_cap(struct dram_info *dram,
			   struct rk3399_sdram_params *sdram_params,
			   unsigned char channel)
{
	const struct chan_info *chan = &dram->chan[channel];
	struct sdram_cap_info *cap_info = &sdram_params->ch[channel].cap_info;
	u32 bw;
	u32 col_tmp;
	u32 bk_tmp;
	u32 row_tmp;
	u32 cs0_cap;
	u32 training_flag;
	u32 ddrconfig;

	/* detect bw */
	bw = 2;
	if (sdram_params->base.dramtype != LPDDR4) {
		dram_set_bw(chan, bw);
		cap_info->bw = bw;
		if (data_training(chan, channel, sdram_params,
				  PI_READ_GATE_TRAINING)) {
			bw = 1;
			dram_set_bw(chan, 1);
			cap_info->bw = bw;
			if (data_training(chan, channel, sdram_params,
					  PI_READ_GATE_TRAINING)) {
				printf("16bit error!!!\n");
				goto error;
			}
		}
	}
	/*
	 * LPDDR3 CA training msut be trigger before other training.
	 * DDR3 is not have CA training.
	 */
	if (sdram_params->base.dramtype == LPDDR3)
		training_flag = PI_WRITE_LEVELING;
	else
		training_flag = PI_FULL_TRAINING;

	if (sdram_params->base.dramtype != LPDDR4) {
		if (data_training(chan, channel, sdram_params, training_flag)) {
			printf("full training error!!!\n");
			goto error;
		}
	}

	/* detect col */
	dram_set_max_col(chan, bw, &col_tmp);
	if (sdram_detect_col(cap_info, col_tmp) != 0)
		goto error;

	/* detect bank */
	dram_set_max_bank(chan, bw, &bk_tmp, &col_tmp);
	sdram_detect_bank(cap_info, col_tmp, bk_tmp);

	/* detect row */
	dram_set_max_row(chan, bw, &row_tmp, &bk_tmp, &col_tmp);
	if (sdram_detect_row(cap_info, col_tmp, bk_tmp, row_tmp) != 0)
		goto error;

	/* detect row_3_4 */
	sdram_detect_row_3_4(cap_info, col_tmp, bk_tmp);

	/* set ddrconfig */
	cs0_cap = (1 << (cap_info->cs0_row + cap_info->col + cap_info->bk +
			 cap_info->bw - 20));
	if (cap_info->row_3_4)
		cs0_cap = cs0_cap * 3 / 4;

	cap_info->cs1_row = cap_info->cs0_row;
	set_memory_map(chan, channel, sdram_params);
	ddrconfig = calculate_ddrconfig(sdram_params, channel);
	if (-1 == ddrconfig)
		goto error;
	set_ddrconfig(chan, sdram_params, channel,
		      cap_info->ddrconfig);

	/* detect cs1 row */
	sdram_detect_cs1_row(cap_info, sdram_params->base.dramtype);

	/* detect die bw */
	sdram_detect_dbw(cap_info, sdram_params->base.dramtype);

	return 0;
error:
	return (-1);
}

/* read mr_num mode register
 * input: rank = 1: cs0, rank = 2: cs1
 *        mr_num: mode register number
 * output: buf
 */
static int read_mr(struct rk3399_ddr_pctl_regs *ddr_pctl_regs, u32 rank,
		   u32 mr_num, u32 *buf)
{
	s32 timeout = 100;

	writel(((1 << 16) |
			(((rank == 2) ? 1 : 0) << 8) |
			mr_num) << 8,
			&ddr_pctl_regs->denali_ctl[118]);
	while (0 == (readl(&ddr_pctl_regs->denali_ctl[203]) &
			((1 << 21) | (1 << 12)))) {
		udelay(1);
		if (timeout <= 0)
			goto error;
		timeout--;
	}
	if (!(readl(&ddr_pctl_regs->denali_ctl[203]) & (1 << 12))) {
		*buf = readl(&ddr_pctl_regs->denali_ctl[119]) & 0xFF;
	} else {
		printf("read mr error\n");
		printf("MRR_ERROR_STATUS = 0x%x\n",
		       readl(&ddr_pctl_regs->denali_ctl[17]) & 0x3);
		*buf = 0;
	}
	setbits_le32(&ddr_pctl_regs->denali_ctl[205], (1 << 21) | (1 << 12));
	return 0;
error:
	return (-1);
}

static int read_mr_for_detect(struct dram_info *dram, u32 channel, u32 rank,
			      struct rk3399_sdram_params *sdram_params)
{
	u64 cs0_cap;
	u32 stride;
	u32 cs = 0, col = 0, bk = 0, bw = 0, row_3_4 = 0;
	u32 cs0_row = 0, cs1_row = 0, ddrconfig = 0;
	u32 mr5, mr12, mr14;
	struct chan_info *chan =
		&dram->chan[channel];
	struct rk3399_ddr_pctl_regs *ddr_pctl_regs = chan->pctl;
	int ret = 0;
	u32 val;
	void __iomem *addr = NULL;

	stride = get_ddr_stride(dram->pmusgrf);

	if (sdram_params->ch[channel].cap_info.col == 0) {
		ret = -1;
		goto end;
	}

	cs = sdram_params->ch[channel].cap_info.rank;
	col = sdram_params->ch[channel].cap_info.col;
	bk = sdram_params->ch[channel].cap_info.bk;
	bw = sdram_params->ch[channel].cap_info.bw;
	row_3_4 = sdram_params->ch[channel].cap_info.row_3_4;
	cs0_row = sdram_params->ch[channel].cap_info.cs0_row;
	cs1_row = sdram_params->ch[channel].cap_info.cs1_row;
	ddrconfig = sdram_params->ch[channel].cap_info.ddrconfig;

	/* 2GB */
	sdram_params->ch[channel].cap_info.rank = 2;
	sdram_params->ch[channel].cap_info.col = 10;
	sdram_params->ch[channel].cap_info.bk = 3;
	sdram_params->ch[channel].cap_info.bw = 2;
	sdram_params->ch[channel].cap_info.row_3_4 = 0;
	sdram_params->ch[channel].cap_info.cs0_row = 15;
	sdram_params->ch[channel].cap_info.cs1_row = 15;
	sdram_params->ch[channel].cap_info.ddrconfig = 1;

	set_memory_map(chan, channel, sdram_params);
	sdram_params->ch[channel].cap_info.ddrconfig =
			calculate_ddrconfig(sdram_params, channel);
	set_ddrconfig(chan, sdram_params, channel,
		      sdram_params->ch[channel].cap_info.ddrconfig);
	set_cap_relate_config(chan, sdram_params, channel);

	cs0_cap = (1 << (sdram_params->ch[channel].cap_info.bw
			+ sdram_params->ch[channel].cap_info.col
			+ sdram_params->ch[channel].cap_info.bk
			+ sdram_params->ch[channel].cap_info.cs0_row));

	if (sdram_params->ch[channel].cap_info.row_3_4)
		cs0_cap = cs0_cap * 3 / 4;

	if (channel == 0)
		set_ddr_stride(dram->pmusgrf, 0x17);
	else
		set_ddr_stride(dram->pmusgrf, 0x18);

	/* !will soiled DRAM space here!
	 * read and write data to DRAM, avoid be optimized by compiler.
	 */
	if (rank == 1)
		addr = (void __iomem *)0x100;
	else if (rank == 2)
		addr = (void __iomem *)(cs0_cap + 0x100);

	val = readl(addr);
	writel(val + 1, addr);

	read_mr(ddr_pctl_regs, rank, 5, &mr5);
	read_mr(ddr_pctl_regs, rank, 12, &mr12);
	read_mr(ddr_pctl_regs, rank, 14, &mr14);

	if (mr5 == 0 || mr12 != 0x4d || mr14 != 0x4d) {
		ret = -1;
		goto end;
	}
end:
	sdram_params->ch[channel].cap_info.rank = cs;
	sdram_params->ch[channel].cap_info.col = col;
	sdram_params->ch[channel].cap_info.bk = bk;
	sdram_params->ch[channel].cap_info.bw = bw;
	sdram_params->ch[channel].cap_info.row_3_4 = row_3_4;
	sdram_params->ch[channel].cap_info.cs0_row = cs0_row;
	sdram_params->ch[channel].cap_info.cs1_row = cs1_row;
	sdram_params->ch[channel].cap_info.ddrconfig = ddrconfig;

	set_ddr_stride(dram->pmusgrf, stride);
	return ret;
}

static u32 get_phy_fn(struct rk3399_sdram_params *sdram_params, u32 ctl_fn)
{
	u32 lp4_phy_fn[] = {1, 0, 0xb};

	if (sdram_params->base.dramtype == LPDDR4)
		return lp4_phy_fn[ctl_fn];
	else
		return ctl_fn;
}

static u32 get_ctl_fn(struct rk3399_sdram_params *sdram_params, u32 phy_fn)
{
	u32 lp4_ctl_fn[] = {1, 0, 2};

	if (sdram_params->base.dramtype == LPDDR4)
		return lp4_ctl_fn[phy_fn];
	else
		return phy_fn;
}

static void dram_copy_phy_fn(struct dram_info *dram,
			     struct rk3399_sdram_params *sdram_params, u32 fn,
			     struct rk3399_sdram_params *f1_sdram_params,
			     u32 channel)
{
	u32 *denali_ctl;
	u32 *denali_phy;
	u32 *denali_phy_params;
	u32 speed = 0;
	u32 mr5;
	u32 ctl_fn;

	denali_ctl = dram->chan[channel].pctl->denali_ctl;
	denali_phy = dram->chan[channel].publ->denali_phy;
	denali_phy_params = f1_sdram_params->phy_regs.denali_phy;

	/* switch index */
	clrsetbits_le32(&denali_phy_params[896], 0x3 << 8,
			fn << 8);
	writel(denali_phy_params[896], &denali_phy[896]);

	/* phy_pll_ctrl_ca, phy_pll_ctrl */
	writel(denali_phy_params[911], &denali_phy[911]);
	/* phy_low_freq_sel */
	clrsetbits_le32(&denali_phy[913], 0x1,
			denali_phy_params[913] & 0x1);
	/* PHY_GRP_SLAVE_DELAY_X, phy_cslvl_dly_step */
	writel(denali_phy_params[916], &denali_phy[916]);
	writel(denali_phy_params[917], &denali_phy[917]);
	writel(denali_phy_params[918], &denali_phy[918]);
	/* phy_adrZ_sw_wraddr_shift_X  */
	writel(denali_phy_params[512], &denali_phy[512]);
	clrsetbits_le32(&denali_phy[513], 0xFFFF,
			denali_phy_params[513] & 0xFFFF);
	writel(denali_phy_params[640], &denali_phy[640]);
	clrsetbits_le32(&denali_phy[641], 0xFFFF,
			denali_phy_params[641] & 0xFFFF);
	writel(denali_phy_params[768], &denali_phy[768]);
	clrsetbits_le32(&denali_phy[769], 0xFFFF,
			denali_phy_params[769] & 0xFFFF);

	writel(denali_phy_params[544], &denali_phy[544]);
	writel(denali_phy_params[545], &denali_phy[545]);
	writel(denali_phy_params[546], &denali_phy[546]);
	writel(denali_phy_params[547], &denali_phy[547]);

	writel(denali_phy_params[672], &denali_phy[672]);
	writel(denali_phy_params[673], &denali_phy[673]);
	writel(denali_phy_params[674], &denali_phy[674]);
	writel(denali_phy_params[675], &denali_phy[675]);

	writel(denali_phy_params[800], &denali_phy[800]);
	writel(denali_phy_params[801], &denali_phy[801]);
	writel(denali_phy_params[802], &denali_phy[802]);
	writel(denali_phy_params[803], &denali_phy[803]);

	/*
	 * phy_adr_master_delay_start_X
	 * phy_adr_master_delay_step_X
	 * phy_adr_master_delay_wait_X
	 */
	writel(denali_phy_params[548], &denali_phy[548]);
	writel(denali_phy_params[676], &denali_phy[676]);
	writel(denali_phy_params[804], &denali_phy[804]);

	/* phy_adr_calvl_dly_step_X */
	writel(denali_phy_params[549], &denali_phy[549]);
	writel(denali_phy_params[677], &denali_phy[677]);
	writel(denali_phy_params[805], &denali_phy[805]);

	/*
	 * phy_clk_wrdm_slave_delay_X
	 * phy_clk_wrdqZ_slave_delay_X
	 * phy_clk_wrdqs_slave_delay_X
	 */
	sdram_copy_to_reg((u32 *)&denali_phy[59],
			  (u32 *)&denali_phy_params[59],
			  (63 - 58) * 4);
	sdram_copy_to_reg((u32 *)&denali_phy[187],
			  (u32 *)&denali_phy_params[187],
			  (191 - 186) * 4);
	sdram_copy_to_reg((u32 *)&denali_phy[315],
			  (u32 *)&denali_phy_params[315],
			  (319 - 314) * 4);
	sdram_copy_to_reg((u32 *)&denali_phy[443],
			  (u32 *)&denali_phy_params[443],
			  (447 - 442) * 4);

	/*
	 * phy_dqs_tsel_wr_timing_X 8bits DENALI_PHY_84/212/340/468 offset_8
	 * dqs_tsel_wr_end[7:4] add Half cycle
	 * phy_dq_tsel_wr_timing_X 8bits DENALI_PHY_83/211/339/467 offset_8
	 * dq_tsel_wr_end[7:4] add Half cycle
	 */
	writel(denali_phy_params[83] + (0x10 << 16), &denali_phy[83]);
	writel(denali_phy_params[84] + (0x10 << 8), &denali_phy[84]);
	writel(denali_phy_params[85], &denali_phy[85]);

	writel(denali_phy_params[211] + (0x10 << 16), &denali_phy[211]);
	writel(denali_phy_params[212] + (0x10 << 8), &denali_phy[212]);
	writel(denali_phy_params[213], &denali_phy[213]);

	writel(denali_phy_params[339] + (0x10 << 16), &denali_phy[339]);
	writel(denali_phy_params[340] + (0x10 << 8), &denali_phy[340]);
	writel(denali_phy_params[341], &denali_phy[341]);

	writel(denali_phy_params[467] + (0x10 << 16), &denali_phy[467]);
	writel(denali_phy_params[468] + (0x10 << 8), &denali_phy[468]);
	writel(denali_phy_params[469], &denali_phy[469]);

	/*
	 * phy_gtlvl_resp_wait_cnt_X
	 * phy_gtlvl_dly_step_X
	 * phy_wrlvl_resp_wait_cnt_X
	 * phy_gtlvl_final_step_X
	 * phy_gtlvl_back_step_X
	 * phy_rdlvl_dly_step_X
	 *
	 * phy_master_delay_step_X
	 * phy_master_delay_wait_X
	 * phy_wrlvl_dly_step_X
	 * phy_rptr_update_X
	 * phy_wdqlvl_dly_step_X
	 */
	writel(denali_phy_params[87], &denali_phy[87]);
	writel(denali_phy_params[88], &denali_phy[88]);
	writel(denali_phy_params[89], &denali_phy[89]);
	writel(denali_phy_params[90], &denali_phy[90]);

	writel(denali_phy_params[215], &denali_phy[215]);
	writel(denali_phy_params[216], &denali_phy[216]);
	writel(denali_phy_params[217], &denali_phy[217]);
	writel(denali_phy_params[218], &denali_phy[218]);

	writel(denali_phy_params[343], &denali_phy[343]);
	writel(denali_phy_params[344], &denali_phy[344]);
	writel(denali_phy_params[345], &denali_phy[345]);
	writel(denali_phy_params[346], &denali_phy[346]);

	writel(denali_phy_params[471], &denali_phy[471]);
	writel(denali_phy_params[472], &denali_phy[472]);
	writel(denali_phy_params[473], &denali_phy[473]);
	writel(denali_phy_params[474], &denali_phy[474]);

	/*
	 * phy_gtlvl_lat_adj_start_X
	 * phy_gtlvl_rddqs_slv_dly_start_X
	 * phy_rdlvl_rddqs_dq_slv_dly_start_X
	 * phy_wdqlvl_dqdm_slv_dly_start_X
	 */
	writel(denali_phy_params[80], &denali_phy[80]);
	writel(denali_phy_params[81], &denali_phy[81]);

	writel(denali_phy_params[208], &denali_phy[208]);
	writel(denali_phy_params[209], &denali_phy[209]);

	writel(denali_phy_params[336], &denali_phy[336]);
	writel(denali_phy_params[337], &denali_phy[337]);

	writel(denali_phy_params[464], &denali_phy[464]);
	writel(denali_phy_params[465], &denali_phy[465]);

	/*
	 * phy_master_delay_start_X
	 * phy_sw_master_mode_X
	 * phy_rddata_en_tsel_dly_X
	 */
	writel(denali_phy_params[86], &denali_phy[86]);
	writel(denali_phy_params[214], &denali_phy[214]);
	writel(denali_phy_params[342], &denali_phy[342]);
	writel(denali_phy_params[470], &denali_phy[470]);

	/*
	 * phy_rddqZ_slave_delay_X
	 * phy_rddqs_dqZ_fall_slave_delay_X
	 * phy_rddqs_dqZ_rise_slave_delay_X
	 * phy_rddqs_dm_fall_slave_delay_X
	 * phy_rddqs_dm_rise_slave_delay_X
	 * phy_rddqs_gate_slave_delay_X
	 * phy_wrlvl_delay_early_threshold_X
	 * phy_write_path_lat_add_X
	 * phy_rddqs_latency_adjust_X
	 * phy_wrlvl_delay_period_threshold_X
	 * phy_wrlvl_early_force_zero_X
	 */
	sdram_copy_to_reg((u32 *)&denali_phy[64],
			  (u32 *)&denali_phy_params[64],
			  (67 - 63) * 4);
	clrsetbits_le32(&denali_phy[68], 0xFFFFFC00,
			denali_phy_params[68] & 0xFFFFFC00);
	sdram_copy_to_reg((u32 *)&denali_phy[69],
			  (u32 *)&denali_phy_params[69],
			  (79 - 68) * 4);

	sdram_copy_to_reg((u32 *)&denali_phy[192],
			  (u32 *)&denali_phy_params[192],
			  (195 - 191) * 4);
	clrsetbits_le32(&denali_phy[196], 0xFFFFFC00,
			denali_phy_params[196] & 0xFFFFFC00);
	sdram_copy_to_reg((u32 *)&denali_phy[197],
			  (u32 *)&denali_phy_params[197],
			  (207 - 196) * 4);

	sdram_copy_to_reg((u32 *)&denali_phy[320],
			  (u32 *)&denali_phy_params[320],
			  (323 - 319) * 4);
	clrsetbits_le32(&denali_phy[324], 0xFFFFFC00,
			denali_phy_params[324] & 0xFFFFFC00);
	sdram_copy_to_reg((u32 *)&denali_phy[325],
			  (u32 *)&denali_phy_params[325],
			  (335 - 324) * 4);

	sdram_copy_to_reg((u32 *)&denali_phy[448],
			  (u32 *)&denali_phy_params[448],
			  (451 - 447) * 4);
	clrsetbits_le32(&denali_phy[452], 0xFFFFFC00,
			denali_phy_params[452] & 0xFFFFFC00);
	sdram_copy_to_reg((u32 *)&denali_phy[453],
			  (u32 *)&denali_phy_params[453],
			  (463 - 452) * 4);

	/* phy_two_cyc_preamble_X */
	clrsetbits_le32(&denali_phy[7], 0x3 << 24,
			denali_phy_params[7] & (0x3 << 24));
	clrsetbits_le32(&denali_phy[135], 0x3 << 24,
			denali_phy_params[135] & (0x3 << 24));
	clrsetbits_le32(&denali_phy[263], 0x3 << 24,
			denali_phy_params[263] & (0x3 << 24));
	clrsetbits_le32(&denali_phy[391], 0x3 << 24,
			denali_phy_params[391] & (0x3 << 24));

	/* speed */
	if (f1_sdram_params->base.ddr_freq < 400 * MHz)
		speed = 0x0;
	else if (f1_sdram_params->base.ddr_freq < 800 * MHz)
		speed = 0x1;
	else if (f1_sdram_params->base.ddr_freq < 1200 * MHz)
		speed = 0x2;

	/* PHY_924 PHY_PAD_FDBK_DRIVE */
	clrsetbits_le32(&denali_phy[924],
			0x3 << 21, speed << 21);
	/* PHY_926 PHY_PAD_DATA_DRIVE */
	clrsetbits_le32(&denali_phy[926],
			0x3 << 9, speed << 9);
	/* PHY_927 PHY_PAD_DQS_DRIVE */
	clrsetbits_le32(&denali_phy[927],
			0x3 << 9, speed << 9);
	/* PHY_928 PHY_PAD_ADDR_DRIVE */
	clrsetbits_le32(&denali_phy[928],
			0x3 << 17, speed << 17);
	/* PHY_929 PHY_PAD_CLK_DRIVE */
	clrsetbits_le32(&denali_phy[929],
			0x3 << 17, speed << 17);
	/* PHY_935 PHY_PAD_CKE_DRIVE */
	clrsetbits_le32(&denali_phy[935],
			0x3 << 17, speed << 17);
	/* PHY_937 PHY_PAD_RST_DRIVE */
	clrsetbits_le32(&denali_phy[937],
			0x3 << 17, speed << 17);
	/* PHY_939 PHY_PAD_CS_DRIVE */
	clrsetbits_le32(&denali_phy[939],
			0x3 << 17, speed << 17);

	if (f1_sdram_params->base.dramtype == LPDDR4) {
		read_mr(dram->chan[channel].pctl, 1, 5, &mr5);
		set_ds_odt(&dram->chan[channel], f1_sdram_params, 1, 0, mr5);
		set_ds_odt(&dram->chan[channel], f1_sdram_params, 1, 1, mr5);

		ctl_fn = get_ctl_fn(f1_sdram_params, fn);
		set_lp4_dq_odt(&dram->chan[channel], f1_sdram_params,
			       ctl_fn, 1, 1, 0, mr5);
		set_lp4_ca_odt(&dram->chan[channel], f1_sdram_params,
			       ctl_fn, 1, 1, 0, mr5);
		set_lp4_MR3(&dram->chan[channel], f1_sdram_params,
			    ctl_fn, 1, 0, mr5);
		set_lp4_MR12(&dram->chan[channel], f1_sdram_params,
			     ctl_fn, 1, 0, mr5);
		set_lp4_MR14(&dram->chan[channel], f1_sdram_params,
			     ctl_fn, 1, 0, mr5);

		set_lp4_dq_odt(&dram->chan[channel], f1_sdram_params,
			       ctl_fn, 1, 1, 1, mr5);
		set_lp4_ca_odt(&dram->chan[channel], f1_sdram_params,
			       ctl_fn, 1, 1, 1, mr5);
		set_lp4_MR3(&dram->chan[channel], f1_sdram_params,
			    ctl_fn, 1, 1, mr5);
		set_lp4_MR12(&dram->chan[channel], f1_sdram_params,
			     ctl_fn, 1, 1, mr5);
		set_lp4_MR14(&dram->chan[channel], f1_sdram_params,
			     ctl_fn, 1, 1, mr5);

		/*
		 * if phy_sw_master_mode_X not bypass mode,
		 * clear PHY_SLICE_PWR_RDC_DISABLE.
		 * NOTE: need use f1_sdram_params, not ddr_publ_regs
		 */
		if (!((denali_phy_params[86] >> 8)
			& (1 << 2))) {
			clrbits_le32(&denali_phy[10], 1 << 16);
			clrbits_le32(&denali_phy[138], 1 << 16);
			clrbits_le32(&denali_phy[266], 1 << 16);
			clrbits_le32(&denali_phy[394], 1 << 16);
		}

		/*
		 * when PHY_PER_CS_TRAINING_EN=1, W2W_DIFFCS_DLY_Fx can't
		 * smaller than 8
		 * NOTE: need use f1_sdram_params, not ddr_publ_regs
		 */
		if ((denali_phy_params[84] >> 16) & 1) {
			if (((readl(&denali_ctl[217 + ctl_fn]) >>
				16) & 0x1f) < 8)
				clrsetbits_le32(&denali_ctl[217 + ctl_fn],
						0x1f << 16,
						8 << 16);
		}
	}
}

static void dram_set_phy_fn(struct dram_info *dram,
			    struct rk3399_sdram_params *sdram_params, u32 fn,
			    struct rk3399_sdram_params *f1_sdram_params)
{
	u32 channel;

	for (channel = 0; channel < 2; channel++)
		dram_copy_phy_fn(dram, sdram_params, fn, f1_sdram_params,
				 channel);
}

static int dram_set_rate(struct dram_info *dram,
			 struct rk3399_sdram_params *sdram_params,
			 u32 fn, u32 hz)
{
	u32 channel;
	int ret_clk, ret[2];

	/* cci idle req stall */
	writel(0x70007, &dram->grf->soc_con0);
	/* enable all clk */
	setbits_le32(&dram->pmu->pmu_noc_auto_ena, (0x3 << 7));
	/* idle */
	setbits_le32(&dram->pmu->pmu_bus_idle_req, (0x3 << 18));
	while ((readl(&dram->pmu->pmu_bus_idle_st) & (0x3 << 18))
	       != (0x3 << 18))
		;

	/* change freq */
	writel((((0x3 << 4) | (1 << 2) | 1) << 16) |
		(fn << 4) | (1 << 2) | 1, &dram->cic->cic_ctrl0);
	while (!(readl(&dram->cic->cic_status0) & (1 << 2)))
		;

	ret_clk = clk_set_rate(&dram->ddr_clk, hz);
	if (ret_clk < 0) {
		printf("%s clk set failed %d\n", __func__, ret_clk);
		return ret_clk;
	}

	writel(0x20002, &dram->cic->cic_ctrl0);
	while (!(readl(&dram->cic->cic_status0) & (1 << 0)))
		;

	/* deidle */
	clrbits_le32(&dram->pmu->pmu_bus_idle_req, (0x3 << 18));
	while (readl(&dram->pmu->pmu_bus_idle_st) & (0x3 << 18))
		;

	/* clear enable all clk */
	clrbits_le32(&dram->pmu->pmu_noc_auto_ena, (0x3 << 7));

	/* LPDDR4 f2 can not do training, all training will fail */
	if (!(sdram_params->base.dramtype == LPDDR4 && fn == 2)) {
		for (channel = 0; channel < 2; channel++) {
			if (!(sdram_params->ch[channel].cap_info.col))
				continue;
			ret[channel] = data_training(&dram->chan[channel],
						     channel, sdram_params,
						     PI_FULL_TRAINING);
		}
		for (channel = 0; channel < 2; channel++) {
			if (!(sdram_params->ch[channel].cap_info.col))
				continue;
			if (ret[channel])
				printf("channel %d training failed!\n",
				       channel);
			else
				printf("channel %d training pass\n", channel);
		}
	}

	return 0;
}

static struct rk3399_sdram_params *g_sdram_params;
static void set_rate0(struct dram_info *dram)
{
	u32 ctl_fn;
	u32 phy_fn;

	ctl_fn = 0;
	phy_fn = get_phy_fn(g_sdram_params, ctl_fn);
	dram_set_phy_fn(dram, g_sdram_params, phy_fn, &dfs_configs[ctl_fn]);
	dram_set_rate(dram, g_sdram_params, ctl_fn,
		      dfs_configs[ctl_fn].base.ddr_freq);
	printf("change freq to %d MHz %d, %d\n",
	       dfs_configs[ctl_fn].base.ddr_freq / MHZ, ctl_fn, phy_fn);
}

static void set_rate1(struct dram_info *dram)
{
	u32 ctl_fn;
	u32 phy_fn;

	ctl_fn = 1;
	phy_fn = get_phy_fn(g_sdram_params, ctl_fn);
	dram_set_phy_fn(dram, g_sdram_params, phy_fn, &dfs_configs[ctl_fn]);
	dram_set_rate(dram, g_sdram_params, ctl_fn,
		      dfs_configs[ctl_fn].base.ddr_freq);
	printf("change freq to %d MHz %d, %d\n",
	       dfs_configs[ctl_fn].base.ddr_freq / MHZ, ctl_fn, phy_fn);
}

static int sdram_init(struct dram_info *dram,
		      struct rk3399_sdram_params *sdram_params)
{
	unsigned char dramtype = sdram_params->base.dramtype;
	unsigned int ddr_freq = sdram_params->base.ddr_freq;
	int channel;
	u32 rank;
	int ch;
	u32 tmp;
	u32 training_flag;

	debug("Starting SDRAM initialization...\n");

	if ((dramtype == DDR3 && ddr_freq > 933) ||
	    (dramtype == LPDDR3 && ddr_freq > 933) ||
	    (dramtype == LPDDR4 && ddr_freq > 800)) {
		debug("SDRAM frequency is to high!");
		return -E2BIG;
	}

	/* detect rank */
	for (ch = 0; ch < 2; ch++) {
		sdram_params->ch[ch].cap_info.rank = 2;
		for (rank = 2; rank != 0; rank--) {
			for (channel = 0; channel < 2; channel++) {
				const struct chan_info *chan =
					&dram->chan[channel];
				struct rk3399_cru *cru = dram->cru;
				struct rk3399_ddr_publ_regs *publ = chan->publ;

				phy_pctrl_reset(cru, channel);
				phy_dll_bypass_set(publ, ddr_freq);
				pctl_cfg(chan, channel, sdram_params);
			}

			/* start to trigger initialization */
			pctl_start(dram, sdram_params, 3);

			/* LPDDR2/LPDDR3 need to wait DAI complete, max 10us */
			if (dramtype == LPDDR3)
				udelay(10);

			tmp = (rank == 2) ? 3 : 1;
			dram_set_cs(&dram->chan[ch], tmp, 2048,
				    sdram_params->base.dramtype);
			sdram_params->ch[ch].cap_info.rank = rank;
			if (sdram_params->base.dramtype == LPDDR4) {
				/* two rank, then read_mr(cs1)
				 * one rank, then read_mr(cs0)
				 */
				if (!read_mr_for_detect(dram, ch, rank,
							sdram_params))
					break;
			} else {
				/*
				 * LPDDR3 CA training msut be trigger before
				 * other training.
				 * DDR3 is not have CA training.
				 * LPDDR4 need confirm here!
				 */
				if (sdram_params->base.dramtype == LPDDR3)
					training_flag = PI_CA_TRAINING |
							PI_READ_GATE_TRAINING;
				else
					training_flag = PI_READ_GATE_TRAINING;
				if (!(data_training(&dram->chan[ch], ch,
						    sdram_params,
						    training_flag)))
					break;
			}
		}
		sdram_params->ch[ch].cap_info.rank = rank;
	}

	sdram_params->base.num_channels = 0;
	for (channel = 0; channel < 2; channel++) {
		const struct chan_info *chan = &dram->chan[channel];
		struct sdram_cap_info *cap_info =
			&sdram_params->ch[channel].cap_info;

		if (cap_info->rank == 0) {
			clear_channel_params(sdram_params, 1);
			continue;
		} else {
			sdram_params->base.num_channels++;
		}

		printf("Channel ");
		printf(channel ? "1: " : "0: ");

		if (channel == 0)
			set_ddr_stride(dram->pmusgrf, 0x17);
		else
			set_ddr_stride(dram->pmusgrf, 0x18);

		if (dram_detect_cap(dram, sdram_params, channel)) {
			printf("Cap error!\n");
			continue;
		}

		sdram_print_ddr_info(cap_info, &sdram_params->base, 0);
		set_memory_map(chan, channel, sdram_params);
		cap_info->ddrconfig =
			calculate_ddrconfig(sdram_params, channel);
		if (-1 == cap_info->ddrconfig) {
			printf("no ddrconfig find, Cap not support!\n");
			continue;
		}
		set_ddrconfig(chan, sdram_params, channel, cap_info->ddrconfig);
		set_cap_relate_config(chan, sdram_params, channel);
	}

	if (sdram_params->base.num_channels == 0) {
		sdram_print_dram_type(sdram_params->base.dramtype);
		printf(" %dMHz\n", sdram_params->base.ddr_freq);
		return -1;
	}

	sdram_params->base.stride = calculate_stride(sdram_params);
	dram_all_config(dram, sdram_params);

	if (sdram_params->base.dramtype != LPDDR4)
		switch_to_phy_index1(dram, sdram_params);

	if (sdram_params->base.dramtype == LPDDR4) {
		g_sdram_params = sdram_params;
		set_rate0(dram);
		set_rate1(dram);
	}

	debug("Finish SDRAM initialization...\n");
	return 0;
}

static int rk3399_dmc_ofdata_to_platdata(struct udevice *dev)
{
#if !CONFIG_IS_ENABLED(OF_PLATDATA)
	struct rockchip_dmc_plat *plat = dev_get_platdata(dev);
	int ret;

	ret = dev_read_u32_array(dev, "rockchip,sdram-params",
				 (u32 *)&plat->sdram_params,
				 sizeof(plat->sdram_params) / sizeof(u32));
	if (ret) {
		printf("%s: Cannot read rockchip,sdram-params %d\n",
		       __func__, ret);
		return ret;
	}
	ret = regmap_init_mem(dev, &plat->map);
	if (ret)
		printf("%s: regmap failed %d\n", __func__, ret);

#endif
	return 0;
}

#if CONFIG_IS_ENABLED(OF_PLATDATA)
static int conv_of_platdata(struct udevice *dev)
{
	struct rockchip_dmc_plat *plat = dev_get_platdata(dev);
	struct dtd_rockchip_rk3399_dmc *dtplat = &plat->dtplat;
	int ret;

	ret = regmap_init_mem_platdata(dev, dtplat->reg,
				       ARRAY_SIZE(dtplat->reg) / 2,
				       &plat->map);
	if (ret)
		return ret;

	return 0;
}
#endif

static int rk3399_dmc_init(struct udevice *dev)
{
	struct dram_info *priv = dev_get_priv(dev);
	struct rockchip_dmc_plat *plat = dev_get_platdata(dev);
	int ret;
#if !CONFIG_IS_ENABLED(OF_PLATDATA)
	struct rk3399_sdram_params *params = &plat->sdram_params;
#else
	struct dtd_rockchip_rk3399_dmc *dtplat = &plat->dtplat;
	struct rk3399_sdram_params *params =
					(void *)dtplat->rockchip_sdram_params;

	ret = conv_of_platdata(dev);
	if (ret)
		return ret;
#endif

	priv->cic = syscon_get_first_range(ROCKCHIP_SYSCON_CIC);
	priv->grf = syscon_get_first_range(ROCKCHIP_SYSCON_GRF);
	priv->pmu = syscon_get_first_range(ROCKCHIP_SYSCON_PMU);
	priv->pmugrf = syscon_get_first_range(ROCKCHIP_SYSCON_PMUGRF);
	priv->pmusgrf = syscon_get_first_range(ROCKCHIP_SYSCON_PMUSGRF);
	priv->pmucru = rockchip_get_pmucru();
	priv->cru = rockchip_get_cru();
	priv->chan[0].pctl = regmap_get_range(plat->map, 0);
	priv->chan[0].pi = regmap_get_range(plat->map, 1);
	priv->chan[0].publ = regmap_get_range(plat->map, 2);
	priv->chan[0].msch = regmap_get_range(plat->map, 3);
	priv->chan[1].pctl = regmap_get_range(plat->map, 4);
	priv->chan[1].pi = regmap_get_range(plat->map, 5);
	priv->chan[1].publ = regmap_get_range(plat->map, 6);
	priv->chan[1].msch = regmap_get_range(plat->map, 7);

	debug("con reg %p %p %p %p %p %p %p %p\n",
	      priv->chan[0].pctl, priv->chan[0].pi,
	      priv->chan[0].publ, priv->chan[0].msch,
	      priv->chan[1].pctl, priv->chan[1].pi,
	      priv->chan[1].publ, priv->chan[1].msch);
	debug("cru %p, cic %p, grf %p, sgrf %p, pmucru %p, pmu %p\n", priv->cru,
	      priv->cic, priv->pmugrf, priv->pmusgrf, priv->pmucru, priv->pmu);
#if CONFIG_IS_ENABLED(OF_PLATDATA)
	ret = clk_get_by_index_platdata(dev, 0, dtplat->clocks, &priv->ddr_clk);
#else
	ret = clk_get_by_index(dev, 0, &priv->ddr_clk);
#endif
	if (ret) {
		printf("%s clk get failed %d\n", __func__, ret);
		return ret;
	}
	ret = clk_set_rate(&priv->ddr_clk, params->base.ddr_freq * MHz);
	if (ret < 0) {
		printf("%s clk set failed %d\n", __func__, ret);
		return ret;
	}
	ret = sdram_init(priv, params);
	if (ret < 0) {
		printf("%s DRAM init failed %d\n", __func__, ret);
		return ret;
	}

	return 0;
}
#endif

static int rk3399_dmc_probe(struct udevice *dev)
{
#ifdef CONFIG_TPL_BUILD
	if (rk3399_dmc_init(dev))
		return 0;
#else
	struct dram_info *priv = dev_get_priv(dev);

	priv->pmugrf = syscon_get_first_range(ROCKCHIP_SYSCON_PMUGRF);
	debug("%s: pmugrf=%p\n", __func__, priv->pmugrf);
	priv->info.base = CONFIG_SYS_SDRAM_BASE;
	priv->info.size =
		rockchip_sdram_size((phys_addr_t)&priv->pmugrf->os_reg2);
#ifdef CONFIG_SPL_BUILD
	struct ddr_param ddr_parem;

	ddr_parem.count = 1;
	ddr_parem.para[0] = priv->info.base;
	ddr_parem.para[1] = priv->info.size;
	rockchip_setup_ddr_param(&ddr_parem);
#endif

#endif
	return 0;
}

static int rk3399_dmc_get_info(struct udevice *dev, struct ram_info *info)
{
	struct dram_info *priv = dev_get_priv(dev);

	*info = priv->info;

	return 0;
}

static struct ram_ops rk3399_dmc_ops = {
	.get_info = rk3399_dmc_get_info,
};

static const struct udevice_id rk3399_dmc_ids[] = {
	{ .compatible = "rockchip,rk3399-dmc" },
	{ }
};

U_BOOT_DRIVER(dmc_rk3399) = {
	.name = "rockchip_rk3399_dmc",
	.id = UCLASS_RAM,
	.of_match = rk3399_dmc_ids,
	.ops = &rk3399_dmc_ops,
#ifdef CONFIG_TPL_BUILD
	.ofdata_to_platdata = rk3399_dmc_ofdata_to_platdata,
#endif
	.probe = rk3399_dmc_probe,
	.priv_auto_alloc_size = sizeof(struct dram_info),
#ifdef CONFIG_TPL_BUILD
	.platdata_auto_alloc_size = sizeof(struct rockchip_dmc_plat),
#endif
};
