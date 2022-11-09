/* SPDX-License-Identifier:     GPL-2.0+ */
/*
 * (C) Copyright 2018 Rockchip Electronics Co., Ltd.
 *
 */

#ifndef __SOC_ROCKCHIP_RK3399_PMU_H__
#define __SOC_ROCKCHIP_RK3399_PMU_H__

struct rk3399_pmu_regs {
	u32 pmu_wakeup_cfg[5];
	u32 pmu_pwrdn_con;
	u32 pmu_pwrdn_st;
	u32 pmu_pll_con;
	u32 pmu_pwrmode_con;
	u32 pmu_sft_con;
	u32 pmu_int_con;
	u32 pmu_int_st;
	u32 pmu_gpio0_pos_int_con;
	u32 pmu_gpio0_net_int_con;
	u32 pmu_gpio1_pos_int_con;
	u32 pmu_gpio1_net_int_con;
	u32 pmu_gpio0_pos_int_st;
	u32 pmu_gpio0_net_int_st;
	u32 pmu_gpio1_pos_int_st;
	u32 pmu_gpio1_net_int_st;
	u32 pmu_pwrdn_inten;
	u32 pmu_pwrdn_status;
	u32 pmu_wakeup_status;
	u32 pmu_bus_clr;
	u32 pmu_bus_idle_req;
	u32 pmu_bus_idle_st;
	u32 pmu_bus_idle_ack;
	u32 pmu_cci500_con;
	u32 pmu_adb400_con;
	u32 pmu_adb400_st;
	u32 pmu_power_st;
	u32 pmu_core_pwr_st;
	u32 pmu_osc_cnt;
	u32 pmu_plllock_cnt;
	u32 pmu_pllrst_cnt;
	u32 pmu_stable_cnt;
	u32 pmu_ddrio_pwron_cnt;
	u32 pmu_wakeup_rst_clr_cnt;
	u32 pmu_ddr_sref_st;
	u32 pmu_scu_l_pwrdn_cnt;
	u32 pmu_scu_l_pwrup_cnt;
	u32 pmu_scu_b_pwrdn_cnt;
	u32 pmu_scu_b_pwrup_cnt;
	u32 pmu_gpu_pwrdn_cnt;
	u32 pmu_gpu_pwrup_cnt;
	u32 pmu_center_pwrdn_cnt;
	u32 pmu_center_pwrup_cnt;
	u32 pmu_timeout_cnt;
	u32 pmu_cpu0apm_con;
	u32 pmu_cpu1apm_con;
	u32 pmu_cpu2apm_con;
	u32 pmu_cpu3apm_con;
	u32 pmu_cpu0bpm_con;
	u32 pmu_cpu1bpm_con;
	u32 pmu_noc_auto_ena;
	u32 pmu_pwrdn_con1;
	u32 reserved0[0x4];
	u32 pmu_sys_reg_reg0;
	u32 pmu_sys_reg_reg1;
	u32 pmu_sys_reg_reg2;
	u32 pmu_sys_reg_reg3;
};

check_member(rk3399_pmu_regs, pmu_sys_reg_reg3, 0xfc);

#endif	/* __SOC_ROCKCHIP_RK3399_PMU_H__ */
