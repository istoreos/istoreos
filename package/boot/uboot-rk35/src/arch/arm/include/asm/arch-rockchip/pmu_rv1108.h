/*
 * Copyright (C) 2018 Rockchip Electronics Co., Ltd
 * Author: Zhihuan He <huan.he@rock-chips.com>
 * SPDX-License-Identifier:	GPL-2.0
 */

#ifndef _ASM_ARCH_PMU_RV1108_H
#define _ASM_ARCH_PMU_RV1108_H

struct rv1108_pmu {
	u32 wakeup_cfg[3];
	u32 reserved0[2];
	u32 pwrmode_core_con;
	u32 pwrmode_common_con;
	u32 sft_con;
	u32 reserved1[7];
	u32 bus_idle_req;
	u32 bus_idle_st;
	u32 reserved2;
	u32 osc_cnt;
	u32 plllock_cnt;
	u32 reserved3;
	u32 stable_cnt;
	u32 reserved4;
	u32 wakeup_rst_clr_cnt;
	u32 ddr_sref_st;
	u32 sys_reg[4];
	u32 timeout_cnt;
};

check_member(rv1108_pmu, timeout_cnt, 0x0074);

enum { /* PMU_SFT_CON */
	DDR_IO_RET_SHIFT		= 11,
	DDR_IO_RET_EN			= 1 << DDR_IO_RET_SHIFT,
};

#endif

