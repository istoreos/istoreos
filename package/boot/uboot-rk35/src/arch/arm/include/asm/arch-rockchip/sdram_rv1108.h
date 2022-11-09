/*
 * Copyright (C) 2018 Rockchip Electronics Co., Ltd
 * Author: Zhihuan He <huan.he@rock-chips.com>
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef _ASM_ARCH_SDRAM_RV1108_H
#define _ASM_ARCH_SDRAM_RV1108_H

#include <common.h>
#include <ram.h>
#include <asm/arch/cru_rv1108.h>
#include <asm/arch/grf_rv1108.h>
#include <asm/arch/pmu_rv1108.h>
#include <asm/arch/sdram_rv1108_pctl_phy.h>

#define SR_IDLE			3
#define PD_IDLE			64
#define SDRAM_BEGIN_ADDR	0x60000000
#define SDRAM_END_ADDR		0x80000000
#define PATTERN			(0x5aa5f00f)

struct rv1108_service_msch {
	u32 id_coreid;
	u32 id_revisionid;
	u32 ddrconf;
	u32 ddrtiming;
	u32 ddrmode;
	u32 readlatency;
	u32 reserveds1[8];
	u32 activate;
	u32 devtodev;
};

enum {
	/*memory scheduler ddrtiming*/
	BWRATIO_HALF_BW				= 0x80000000,
	BWRATIO_HALF_BW_DIS			= 0x0,
};

struct dram_info {
	struct rv1108_cru *cru;
	struct rv1108_grf *grf;
	struct rv1108_pmu *pmu;
	struct rv1108_pmu_grf *pmu_grf;
	struct ddr_phy *phy;
	struct ddr_pctl *pctl;
	struct rv1108_service_msch *service_msch;
	struct ram_info info;
};

struct sdram_params {
	u32 ddr_2t_en;
	struct ddr_config ddr_config_t;
	struct pll_div dpll_init_cfg;
	struct ddr_timing ddr_timing_t;
};

int check_rd_gate(struct dram_info *priv);
void enable_low_power(struct dram_info *priv,
		      struct sdram_params *params_priv);
void ddr_msch_cfg(struct dram_info *priv,
		  struct sdram_params *params_priv);
void ddr_msch_cfg_rbc(struct sdram_params *params_priv,
		      struct dram_info *priv);
void ddr_msch_get_max_col(struct dram_info *priv,
			  struct ddr_schedule *sch_priv);
void ddr_msch_get_max_row(struct dram_info *priv,
			  struct ddr_schedule *sch_priv);
void ddr_phy_dqs_rx_dll_cfg(struct dram_info *priv, u32 freq);
void ddr_phy_skew_cfg(struct dram_info *priv);
void enable_ddr_io_ret(struct dram_info *priv);
void modify_data_training(struct dram_info *priv,
			  struct sdram_params *params_priv);
void move_to_config_state(struct dram_info *priv);
void pctl_cfg_grf(struct dram_info *priv,
		  struct sdram_params *params_priv);
void phy_pctrl_reset_cru(struct dram_info *priv);
void rkdclk_init(struct dram_info *priv,
		 struct sdram_params *params_priv);
int rv1108_sdram_init(struct dram_info *sdram_priv,
		      struct sdram_params *params_priv);
void set_bw_grf(struct dram_info *priv);
void set_ds_odt(struct dram_info *priv,
		struct sdram_params *params_priv);

#endif
