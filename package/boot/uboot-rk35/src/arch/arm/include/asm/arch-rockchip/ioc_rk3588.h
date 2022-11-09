/*
 * (C) Copyright 2021 Rockchip Electronics Co., Ltd.
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */
#ifndef _ASM_ARCH_IOC_RK3588_H
#define _ASM_ARCH_IOC_RK3588_H

#include <common.h>

struct rk3588_bus_ioc {
	uint32_t reserved0000[3];      /* Address Offset: 0x0000 */
	uint32_t gpio0b_iomux_sel_h;   /* Address Offset: 0x000C */
	uint32_t gpio0c_iomux_sel_l;   /* Address Offset: 0x0010 */
	uint32_t gpio0c_iomux_sel_h;   /* Address Offset: 0x0014 */
	uint32_t gpio0d_iomux_sel_l;   /* Address Offset: 0x0018 */
	uint32_t gpio0d_iomux_sel_h;   /* Address Offset: 0x001C */
	uint32_t gpio1a_iomux_sel_l;   /* Address Offset: 0x0020 */
	uint32_t gpio1a_iomux_sel_h;   /* Address Offset: 0x0024 */
	uint32_t gpio1b_iomux_sel_l;   /* Address Offset: 0x0028 */
	uint32_t gpio1b_iomux_sel_h;   /* Address Offset: 0x002C */
	uint32_t gpio1c_iomux_sel_l;   /* Address Offset: 0x0030 */
	uint32_t gpio1c_iomux_sel_h;   /* Address Offset: 0x0034 */
	uint32_t gpio1d_iomux_sel_l;   /* Address Offset: 0x0038 */
	uint32_t gpio1d_iomux_sel_h;   /* Address Offset: 0x003C */
	uint32_t gpio2a_iomux_sel_l;   /* Address Offset: 0x0040 */
	uint32_t gpio2a_iomux_sel_h;   /* Address Offset: 0x0044 */
	uint32_t gpio2b_iomux_sel_l;   /* Address Offset: 0x0048 */
	uint32_t gpio2b_iomux_sel_h;   /* Address Offset: 0x004C */
	uint32_t gpio2c_iomux_sel_l;   /* Address Offset: 0x0050 */
	uint32_t gpio2c_iomux_sel_h;   /* Address Offset: 0x0054 */
	uint32_t gpio2d_iomux_sel_l;   /* Address Offset: 0x0058 */
	uint32_t gpio2d_iomux_sel_h;   /* Address Offset: 0x005C */
	uint32_t gpio3a_iomux_sel_l;   /* Address Offset: 0x0060 */
	uint32_t gpio3a_iomux_sel_h;   /* Address Offset: 0x0064 */
	uint32_t gpio3b_iomux_sel_l;   /* Address Offset: 0x0068 */
	uint32_t gpio3b_iomux_sel_h;   /* Address Offset: 0x006C */
	uint32_t gpio3c_iomux_sel_l;   /* Address Offset: 0x0070 */
	uint32_t gpio3c_iomux_sel_h;   /* Address Offset: 0x0074 */
	uint32_t gpio3d_iomux_sel_l;   /* Address Offset: 0x0078 */
	uint32_t gpio3d_iomux_sel_h;   /* Address Offset: 0x007C */
	uint32_t gpio4a_iomux_sel_l;   /* Address Offset: 0x0080 */
	uint32_t gpio4a_iomux_sel_h;   /* Address Offset: 0x0084 */
	uint32_t gpio4b_iomux_sel_l;   /* Address Offset: 0x0088 */
	uint32_t gpio4b_iomux_sel_h;   /* Address Offset: 0x008C */
	uint32_t gpio4c_iomux_sel_l;   /* Address Offset: 0x0090 */
	uint32_t gpio4c_iomux_sel_h;   /* Address Offset: 0x0094 */
	uint32_t gpio4d_iomux_sel_l;   /* Address Offset: 0x0098 */
	uint32_t gpio4d_iomux_sel_h;   /* Address Offset: 0x009C */
};
check_member(rk3588_bus_ioc, gpio4d_iomux_sel_h, 0x009C);


struct rk3588_pmu1_ioc {
	uint32_t gpio0a_iomux_sel_l;   /* Address Offset: 0x0000 */
	uint32_t gpio0a_iomux_sel_h;   /* Address Offset: 0x0004 */
	uint32_t gpio0b_iomux_sel_l;   /* Address Offset: 0x0008 */
	uint32_t reserved0012;         /* Address Offset: 0x000C */
	uint32_t gpio0a_ds_l;          /* Address Offset: 0x0010 */
	uint32_t gpio0a_ds_h;          /* Address Offset: 0x0014 */
	uint32_t gpio0b_ds_l;          /* Address Offset: 0x0018 */
	uint32_t reserved0028;         /* Address Offset: 0x001C */
	uint32_t gpio0a_p;             /* Address Offset: 0x0020 */
	uint32_t gpio0b_p;             /* Address Offset: 0x0024 */
	uint32_t gpio0a_ie;            /* Address Offset: 0x0028 */
	uint32_t gpio0b_ie;            /* Address Offset: 0x002C */
	uint32_t gpio0a_smt;           /* Address Offset: 0x0030 */
	uint32_t gpio0b_smt;           /* Address Offset: 0x0034 */
	uint32_t gpio0a_pdis;          /* Address Offset: 0x0038 */
	uint32_t gpio0b_pdis;          /* Address Offset: 0x003C */
	uint32_t xin_con;              /* Address Offset: 0x0040 */
};
check_member(rk3588_pmu1_ioc, xin_con, 0x0040);

struct rk3588_pmu2_ioc {
	uint32_t gpio0b_iomux_sel_h;  /* Address Offset: 0x0000 */
	uint32_t gpio0c_iomux_sel_l;  /* Address Offset: 0x0004 */
	uint32_t gpio0c_iomux_sel_h;  /* Address Offset: 0x0008 */
	uint32_t gpio0d_iomux_sel_l;  /* Address Offset: 0x000C */
	uint32_t gpio0d_iomux_sel_h;  /* Address Offset: 0x0010 */
	uint32_t gpio0b_ds_h;         /* Address Offset: 0x0014 */
	uint32_t gpio0c_ds_l;         /* Address Offset: 0x0018 */
	uint32_t gpio0c_ds_h;         /* Address Offset: 0x001C */
	uint32_t gpio0d_ds_l;         /* Address Offset: 0x0020 */
	uint32_t gpio0d_ds_h;         /* Address Offset: 0x0024 */
	uint32_t gpio0b_p;            /* Address Offset: 0x0028 */
	uint32_t gpio0c_p;            /* Address Offset: 0x002C */
	uint32_t gpio0d_p;            /* Address Offset: 0x0030 */
	uint32_t gpio0b_ie;           /* Address Offset: 0x0034 */
	uint32_t gpio0c_ie;           /* Address Offset: 0x0038 */
	uint32_t gpio0d_ie;           /* Address Offset: 0x003C */
	uint32_t gpio0b_smt;          /* Address Offset: 0x0040 */
	uint32_t gpio0c_smt;          /* Address Offset: 0x0044 */
	uint32_t gpio0d_smt;          /* Address Offset: 0x0048 */
	uint32_t gpio0b_pdis;         /* Address Offset: 0x004C */
	uint32_t gpio0c_pdis;         /* Address Offset: 0x0050 */
	uint32_t gpio0d_pdis;         /* Address Offset: 0x0054 */
};
check_member(rk3588_pmu2_ioc, gpio0d_pdis, 0x0054);

#endif

