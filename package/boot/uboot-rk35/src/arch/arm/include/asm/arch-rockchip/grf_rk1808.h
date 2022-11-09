/* SPDX-License-Identifier:     GPL-2.0+ */
/*
 * (C) Copyright 2018 Rockchip Electronics Co., Ltd.
 *
 */
#ifndef _ASM_ARCH_GRF_rk1808_H
#define _ASM_ARCH_GRF_rk1808_H

#include <common.h>

struct rk1808_grf {
	unsigned int gpio1a_iomux_l;			/* 0x0000 */
	unsigned int gpio1a_iomux_h;			/* 0x0004 */
	unsigned int gpio1b_iomux_l;			/* 0x0008 */
	unsigned int gpio1b_iomux_h;			/* 0x000c */
	unsigned int reserved0[(0x20 - 0x0c) / 4 - 1];
	unsigned int gpio2a_iomux_l;			/* 0x0020 */
	unsigned int gpio2a_iomux_h;			/* 0x0024 */
	unsigned int gpio2b_iomux_l;			/* 0x0028 */
	unsigned int gpio2b_iomux_h;			/* 0x002c */
	unsigned int gpio2c_iomux_l;			/* 0x0030 */
	unsigned int gpio2c_iomux_h;			/* 0x0034 */
	unsigned int gpio2d_iomux_l;			/* 0x0038 */
	unsigned int reserved1;
	unsigned int gpio3a_iomux_l;			/* 0x0040 */
	unsigned int gpio3a_iomux_h;			/* 0x0044 */
	unsigned int gpio3b_iomux_l;			/* 0x0048 */
	unsigned int gpio3b_iomux_h;			/* 0x004c */
	unsigned int gpio3c_iomux_l;			/* 0x0050 */
	unsigned int gpio3c_iomux_h;			/* 0x0054 */
	unsigned int gpio3d_iomux_l;			/* 0x0058 */
	unsigned int reserved2;
	unsigned int gpio4a_iomux_l;			/* 0x0060 */
	unsigned int gpio4a_iomux_h;			/* 0x0064 */
	unsigned int gpio4b_iomux_l;			/* 0x0068 */
	unsigned int gpio4b_iomux_h;			/* 0x006c */
	unsigned int gpio4c_iomux_l;			/* 0x0070 */
	unsigned int gpio4c_iomux_h;			/* 0x0074 */
	unsigned int reserved3[(0x0080 - 0x0074) / 4 - 1];
	unsigned int gpio1a_p;				/* 0x0080 */
	unsigned int gpio1b_p;				/* 0x0084 */
	unsigned int gpio1c_p;				/* 0x0088 */
	unsigned int gpio1d_p;				/* 0x008c */
	unsigned int gpio2a_p;				/* 0x0090 */
	unsigned int gpio2b_p;				/* 0x0094 */
	unsigned int gpio2c_p;				/* 0x0098 */
	unsigned int gpio2d_p;				/* 0x009c */
	unsigned int gpio3a_p;				/* 0x00a0 */
	unsigned int gpio3b_p;				/* 0x00a4 */
	unsigned int gpio3c_p;				/* 0x00a8 */
	unsigned int gpio3d_p;				/* 0x00ac */
	unsigned int gpio4a_p;				/* 0x00b0 */
	unsigned int gpio4b_p;				/* 0x00b4 */
	unsigned int gpio4c_p;				/* 0x00b8 */
	unsigned int gpio4d_p;				/* 0x00bc */
	unsigned int gpio1a_sr;				/* 0x00c0 */
	unsigned int gpio1b_sr;				/* 0x00c4 */
	unsigned int gpio1c_sr;				/* 0x00c8 */
	unsigned int gpio1d_sr;				/* 0x00cc */
	unsigned int gpio2a_sr;				/* 0x00d0 */
	unsigned int gpio2b_sr;				/* 0x00d4 */
	unsigned int gpio2c_sr;				/* 0x00d8 */
	unsigned int gpio2d_sr;				/* 0x00dc */
	unsigned int gpio3a_sr;				/* 0x00e0 */
	unsigned int gpio3b_sr;				/* 0x00e4 */
	unsigned int gpio3c_sr;				/* 0x00e8 */
	unsigned int gpio3d_sr;				/* 0x00ec */
	unsigned int gpio4a_sr;				/* 0x00f0 */
	unsigned int gpio4b_sr;				/* 0x00f4 */
	unsigned int gpio4c_sr;				/* 0x00f8 */
	unsigned int gpio4d_sr;				/* 0x00fc */
	unsigned int gpio1a_smt;			/* 0x0100 */
	unsigned int gpio1b_smt;			/* 0x0104 */
	unsigned int gpio1c_smt;			/* 0x0108 */
	unsigned int gpio1d_smt;			/* 0x010c */
	unsigned int gpio2a_smt;			/* 0x0110 */
	unsigned int gpio2b_smt;			/* 0x0114 */
	unsigned int gpio2c_smt;			/* 0x0118 */
	unsigned int gpio2d_smt;			/* 0x011c */
	unsigned int gpio3a_smt;			/* 0x0120 */
	unsigned int gpio3b_smt;			/* 0x0124 */
	unsigned int gpio3c_smt;			/* 0x0128 */
	unsigned int gpio3d_smt;			/* 0x012c */
	unsigned int gpio4a_smt;			/* 0x0130 */
	unsigned int gpio4b_smt;			/* 0x0134 */
	unsigned int gpio4c_smt;			/* 0x0138 */
	unsigned int gpio4d_smt;			/* 0x013c */
	unsigned int gpio1a_e;				/* 0x0140 */
	unsigned int gpio1b_e;				/* 0x0144 */
	unsigned int gpio1c_e;				/* 0x0148 */
	unsigned int gpio1d_e;				/* 0x014c */
	unsigned int gpio2a_e;				/* 0x0150 */
	unsigned int gpio2b_e;				/* 0x0154 */
	unsigned int gpio2c_e;				/* 0x0158 */
	unsigned int gpio2d_e;				/* 0x015c */
	unsigned int gpio3a_e;				/* 0x0160 */
	unsigned int gpio3b_e;				/* 0x0164 */
	unsigned int gpio3c_e;				/* 0x0168 */
	unsigned int gpio3d_e;				/* 0x016c */
	unsigned int gpio4a_e;				/* 0x0170 */
	unsigned int gpio4b_e;				/* 0x0174 */
	unsigned int gpio4c_e;				/* 0x0178 */
	unsigned int gpio4d_e;				/* 0x017c */
	unsigned int reserved4[(0x0190 - 0x017c) / 4 - 1];
	unsigned int iofunc_con0;			/* 0x0190 */
	unsigned int reserved5[(0x0400 - 0x0190) / 4 - 1];
	unsigned int soc_con0;				/* 0x0400 */
	unsigned int soc_con1;				/* 0x0404 */
	unsigned int soc_con2;				/* 0x0408 */
	unsigned int soc_con3;				/* 0x040c */
	unsigned int soc_con4;				/* 0x0410 */
	unsigned int soc_con5;				/* 0x0414 */
	unsigned int reserved6[(0x0430 - 0x0414) / 4 - 1];
	unsigned int pd_vi_con0;			/* 0x0430 */
	unsigned int pd_vi_con1;			/* 0x0434 */
	unsigned int pd_vi_status;			/* 0x0438 */
	unsigned int reserved7;
	unsigned int pd_vo_con0;			/* 0x0440 */
	unsigned int pd_vo_con1;			/* 0x0444 */
	unsigned int reserved8[(0x0480 - 0x0444) / 4 - 1];
	unsigned int soc_status0;			/* 0x0480 */
	unsigned int reserved9[(0x0500 - 0x0480) / 4 - 1];
	unsigned int cpu_con0;				/* 0x0500 */
	unsigned int cpu_con1;				/* 0x0504 */
	unsigned int cpu_con2;				/* 0x0508 */
	unsigned int reserved10[(0x0520 - 0x0508) / 4 - 1];
	unsigned int cpu_status0;			/* 0x0520 */
	unsigned int cpu_status1;			/* 0x0524 */
	unsigned int reserved11[(0x0530 - 0x0524) / 4 - 1];
	unsigned int soc_noc_con0;			/* 0x0530 */
	unsigned int soc_noc_con1;			/* 0x0534 */
	unsigned int soc_noc_con2;			/* 0x0538 */
	unsigned int reserved12[(0x0600 - 0x0538) / 4 - 1];
	unsigned int ram_con0;				/* 0x0600 */
	unsigned int ram_con1;				/* 0x0604 */
	unsigned int ram_con2;				/* 0x0608 */
	unsigned int ram_con3;				/* 0x060c */
	unsigned int ram_con4;				/* 0x0610 */
	unsigned int reserved13[(0x0780 - 0x0610) / 4 - 1];
	unsigned int npupvtm_con0;			/* 0x0780 */
	unsigned int npupvtm_con1;			/* 0x0784 */
	unsigned int npupvtm_status0;			/* 0x0788 */
	unsigned int npupvtm_status1;			/* 0x078c */
	unsigned int reserved14[(0x0800 - 0x078c) / 4 - 1];
	unsigned int chip_id;				/* 0x0800 */
	unsigned int reserved15[(0x0900 - 0x0800) / 4 - 1];
	unsigned int mac_con0;				/* 0x0900 */
	unsigned int mac_con1;				/* 0x0904 */

};

check_member(rk1808_grf, gpio1a_iomux_l, 0x0000);
check_member(rk1808_grf, mac_con1, 0x0904);

struct rk1808_pmugrf {
	unsigned int gpio0al_iomux;
	unsigned int gpio0bl_iomux;
	unsigned int gpio0cl_iomux;
	unsigned int gpio0dl_iomux;
	unsigned int gpio0a_p;
	unsigned int gpio0b_p;
	unsigned int gpio0c_p;
	unsigned int gpio0d_p;
	unsigned int gpio0a_e;
	unsigned int gpio0b_e;
	unsigned int gpio0c_e;
	unsigned int gpio0d_e;
	unsigned int gpio0a_sr;
	unsigned int gpio0b_sr;
	unsigned int gpio0c_sr;
	unsigned int gpio0d_sr;
	unsigned int gpio0a_smt;
	unsigned int gpio0b_smt;
	unsigned int gpio0c_smt;
	unsigned int gpio0d_smt;
	unsigned int reserved1[(0x100 - 0x4c) / 4 - 1];
	unsigned int soc_con[5];
	unsigned int reserved2[(0x120 - 0x110) / 4 - 1];
	unsigned int soc_status;
	unsigned int reserved3[(0x140 - 0x120) / 4 - 1];
	unsigned int io_vsel0;
	unsigned int io_vsel1;
	unsigned int io_vsel_status;
	unsigned int reserved4[(0x180 - 0x148) / 4 - 1];
	unsigned int pvtm_con[2];
	unsigned int reserved5[2];
	unsigned int pvtm_status[2];
	unsigned int reserved6[(0x200 - 0x194) / 4 - 1];
	unsigned int os_reg[12];
	unsigned int reset_function_status;
	unsigned int reset_function_clr;
	unsigned int reserved7[(0x380 - 0x234) / 4 - 1];
	unsigned int sig_detect_con;
	unsigned int reserved8[(0x390 - 0x380) / 4 - 1];
	unsigned int sig_detect_status;
	unsigned int reserved9[(0x3a0 - 0x390) / 4 - 1];
	unsigned int sig_detect_status_clear;
	unsigned int reserved10[(0x3b0 - 0x3a0) / 4 - 1];
	unsigned int sdmmc_det_counter;
};

check_member(rk1808_pmugrf, sdmmc_det_counter, 0x3b0);
#endif
