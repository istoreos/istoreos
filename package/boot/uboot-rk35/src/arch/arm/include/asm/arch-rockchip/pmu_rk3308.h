/* SPDX-License-Identifier:     GPL-2.0+ */
/*
 * Copyright (C) 2020 Rockchip Electronics Co., Ltd
 */

#ifndef _ASM_ARCH_PMU_RK3308_H
#define _ASM_ARCH_PMU_RK3308_H
struct rk3308_pmu {
	u32 reserved0[4];
	u32 wakeup_cfg2_lo;
	u32 reserved1;
	u32 pwrdn_con_lo;
	u32 reserved2;
	u32 pwrdn_st;
	u32 pwrmode_core_con_lo;
	u32 reserved3;
	u32 pwrmode_common_con_lo;
	u32 pwrmode_common_con_hi;
	u32 sft_con_lo;
	u32 sft_con_hi;
	u32 int_con_lo;
	u32 int_con_hi;
	u32 int_st;
	u32 reserved4[6];
	u32 core_pwr_st;
	u32 bus_idle_req_lo;
	u32 reserved5;
	u32 bus_idle_st;
	u32 power_st;
	u32 osc_cnt_lo;
	u32 osc_cnt_hi;
	u32 plllock_cnt_lo;
	u32 plllock_cnt_hi;
	u32 pllrst_cnt_lo;
	u32 pllrst_cnt_hi;
	u32 reserved6[2];
	u32 ddrio_pwron_cnt_lo;
	u32 ddrio_pwron_cnt_hi;
	u32 wakeup_rst_clr_cnt_lo;
	u32 wakeup_rst_clr_cnt_hi;
	u32 ddr_sref_st;
	u32 sys_reg0_lo;
	u32 sys_reg0_hi;
	u32 sys_reg1_lo;
	u32 sys_reg1_hi;
	u32 sys_reg2_lo;
	u32 sys_reg2_hi;
	u32 sys_reg3_lo;
	u32 sys_reg3_hi;
	u32 scu_pwrdn_cnt_lo;
	u32 scu_pwrdn_cnt_hi;
	u32 scu_pwrup_cnt_lo;
	u32 scu_pwrup_cnt_hi;
	u32 timeout_cnt_lo;
	u32 timeout_cnt_hi;
	u32 cpu0apm_con_lo;
	u32 cpu1apm_con_lo;
	u32 cpu2apm_con_lo;
	u32 cpu3apm_con_lo;
	u32 info_tx_con_lo;
};

check_member(rk3308_pmu, info_tx_con_lo, 0x00f0);
enum { /* SFT_CON_LO */
	DDR_IO_RET_CFG_SHIFT		= 8,
	DDR_IO_RET_CFG_MASK		= 1 << DDR_IO_RET_CFG_SHIFT,
	DDR_IO_RET_CFG			= 0,
};

#endif
