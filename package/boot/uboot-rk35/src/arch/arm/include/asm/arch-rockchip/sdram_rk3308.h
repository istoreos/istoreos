/* SPDX-License-Identifier:     GPL-2.0+ */
/*
 * Copyright (C) 2020 Rockchip Electronics Co., Ltd
 */

#ifndef _ASM_ARCH_SDRAM_RK3308_H
#define _ASM_ARCH_SDRAM_RK3308_H

#include <ram.h>
#include <asm/arch/cru_rk3308.h>
#include <asm/arch/grf_rk3308.h>
#include <asm/arch/pmu_rk3308.h>
#include <asm/arch/sdram_common.h>
#include <asm/arch/sdram_rv1108_pctl_phy.h>

#define CG_EXIT_TH		(250)

#define PATTERN			(0x5aa5f00f)

struct rk3308_ddr_standby {
	u32 con0;
	u32 con1;
	u32 status0;
};

struct rk3308_service_msch {
	u32 id_coreid;
	u32 id_revisionid;
	u32 ddrconf;
	u32 ddrtiming;
	u32 ddrmode;
	u32 readlatency;
};

enum {
	/* ddr standby */
	IDLE_TH_SHIFT				= 16,
	/* can not gate msch clk */
	MSCH_GATE_CLK_SHIFT			= 7,
	MSCH_GATE_CLK_EN			= 1,

	DDRPHY4X_GATE_SHIFT			= 6,
	DDRPHY4X_GATE_EN			= 1,

	UPCTL_CORE_CLK_GATE_SHIFT		= 5,
	UPCTL_CORE_CLK_GATE_EN			= 1,

	UPCTL_ACLK_GATE_SHIFT			= 4,
	UPCTL_ACLK_GATE_EN			= 1,

	CTL_IDLR_SHIFT				= 1,
	CTL_IDLR_EN				= 1,

	STDBY_EN_SHIFT				= 0,
	STDBY_EN				= 1,

	CG_EXIT_TH_SHIFT			= 16,

	STDBY_STATUS_SHIFT			= 0,
	STDBY_STATUS_MASK			= 0x7f << STDBY_STATUS_SHIFT,
	ST_STDBY				= 0x10,
};

enum {
	/* memory scheduler ddrtiming */
	BWRATIO_HALF_BW				= 0x80000000,
	BWRATIO_HALF_BW_DIS			= 0x0,

	PHY_TX_DE_SKEW_SHIFT			= 3,
	PHY_TX_DE_SKEW_EN			= 1,
};

struct dram_info {
	struct rk3308_cru *cru;
	struct rk3308_grf *grf;
	struct rk3308_sgrf *sgrf;
	struct rk3308_pmu *pmu;
	struct ddr_phy *phy;
	struct ddr_pctl *pctl;
	struct rk3308_ddr_standby *standby;
	struct rk3308_service_msch *service_msch;
	struct ram_info info;
};

struct sdram_params {
	u32 idle_pd;
	u32 idle_sr;
	u32 ddr_2t_en;
	u32 stdby_idle;
	struct ddr_config ddr_config_t;
	struct ddr_timing ddr_timing_t;
};

struct rk3308_ddr_skew {
	u32 a0_a1_skew[14];
	u32 cs0_dm0_skew[22];
};

struct rk3308_ddr_gd {
	struct sdram_head_info_v0 head_info;
	struct rk3308_ddr_skew ddr_skew;
};

int check_rd_gate(struct dram_info *priv);
void copy_to_reg(u32 *dest, const u32 *src, u32 n);
void enable_low_power(struct dram_info *priv,
		      struct sdram_params *params_priv);
void ddr_cap_info(size_t size);
void ddr_msch_cfg(struct dram_info *priv,
		  struct sdram_params *params_priv);
void ddr_msch_cfg_rbc(struct sdram_params *params_priv,
		      struct dram_info *priv);
void ddr_msch_get_max_col(struct dram_info *priv,
			  struct ddr_schedule *sch_priv);
void ddr_msch_get_max_row(struct dram_info *priv,
			  struct ddr_schedule *sch_priv);
void ddr_phy_skew_cfg(struct dram_info *priv);
void ddr_phy_dqs_rx_dll_cfg(struct dram_info *priv, u32 freq);
void enable_ddr_io_ret(struct dram_info *priv);
void modify_data_training(struct dram_info *priv,
			  struct sdram_params *params_priv);
void move_to_config_state(struct dram_info *priv);
void move_to_access_state(struct dram_info *priv);
void pctl_cfg_grf(struct dram_info *priv,
		  struct sdram_params *params_priv);
void phy_pctrl_reset_cru(struct dram_info *priv);
void print_dec(u32 n);
void rkdclk_init(struct dram_info *priv,
		 struct sdram_params *params_priv);
int rv1108_sdram_init(struct dram_info *sdram_priv,
		      struct sdram_params *params_priv);
void set_bw_grf(struct dram_info *priv);
void set_ds_odt(struct dram_info *priv,
		struct sdram_params *params_priv);

#endif
