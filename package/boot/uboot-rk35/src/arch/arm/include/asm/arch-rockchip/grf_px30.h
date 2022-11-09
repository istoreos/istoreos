/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd.
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */
#ifndef _ASM_ARCH_GRF_px30_H
#define _ASM_ARCH_GRF_px30_H

#include <common.h>

struct px30_grf {
	unsigned int gpio1al_iomux;
	unsigned int gpio1ah_iomux;
	unsigned int gpio1bl_iomux;
	unsigned int gpio1bh_iomux;
	unsigned int gpio1cl_iomux;
	unsigned int gpio1ch_iomux;
	unsigned int gpio1dl_iomux;
	unsigned int gpio1dh_iomux;

	unsigned int gpio2al_iomux;
	unsigned int gpio2ah_iomux;
	unsigned int gpio2bl_iomux;
	unsigned int gpio2bh_iomux;
	unsigned int gpio2cl_iomux;
	unsigned int gpio2ch_iomux;
	unsigned int gpio2dl_iomux;
	unsigned int gpio2dh_iomux;

	unsigned int gpio3al_iomux;
	unsigned int gpio3ah_iomux;
	unsigned int gpio3bl_iomux;
	unsigned int gpio3bh_iomux;
	unsigned int gpio3cl_iomux;
	unsigned int gpio3ch_iomux;
	unsigned int gpio3dl_iomux;
	unsigned int gpio3dh_iomux;

	unsigned int gpio1a_p;
	unsigned int gpio1b_p;
	unsigned int gpio1c_p;
	unsigned int gpio1d_p;
	unsigned int gpio2a_p;
	unsigned int gpio2b_p;
	unsigned int gpio2c_p;
	unsigned int gpio2d_p;
	unsigned int gpio3a_p;
	unsigned int gpio3b_p;
	unsigned int gpio3c_p;
	unsigned int gpio3d_p;
	unsigned int gpio1a_sr;
	unsigned int gpio1b_sr;
	unsigned int gpio1c_sr;
	unsigned int gpio1d_sr;
	unsigned int gpio2a_sr;
	unsigned int gpio2b_sr;
	unsigned int gpio2c_sr;
	unsigned int gpio2d_sr;
	unsigned int gpio3a_sr;
	unsigned int gpio3b_sr;
	unsigned int gpio3c_sr;
	unsigned int gpio3d_sr;
	unsigned int gpio1a_smt;
	unsigned int gpio1b_smt;
	unsigned int gpio1c_smt;
	unsigned int gpio1d_smt;
	unsigned int gpio2a_smt;
	unsigned int gpio2b_smt;
	unsigned int gpio2c_smt;
	unsigned int gpio2d_smt;
	unsigned int gpio3a_smt;
	unsigned int gpio3b_smt;
	unsigned int gpio3c_smt;
	unsigned int gpio3d_smt;
	unsigned int gpio1a_e;
	unsigned int gpio1b_e;
	unsigned int gpio1c_e;
	unsigned int gpio1d_e;
	unsigned int gpio2a_e;
	unsigned int gpio2b_e;
	unsigned int gpio2c_e;
	unsigned int gpio2d_e;
	unsigned int gpio3a_e;
	unsigned int gpio3b_e;
	unsigned int gpio3c_e;
	unsigned int gpio3d_e;

	unsigned int reserved0[(0x180 - 0x11C) / 4 - 1];
	unsigned int io_vsel;
	unsigned int iofunc_con0;
	unsigned int reserved1[(0x400 - 0x184) / 4 - 1];
	unsigned int soc_con[6];
	unsigned int reserved2[(0x480 - 0x414) / 4 - 1];
	unsigned int soc_status0;
	unsigned int reserved3[(0x500 - 0x480) / 4 - 1];
	unsigned int cpu_con[3];
	unsigned int reserved4[5];
	unsigned int cpu_status[2];
	unsigned int reserved5[2];
	unsigned int soc_noc_con[2];
	unsigned int reserved6[6];
	unsigned int ddr_bankhash[4];
	unsigned int reserved7[(0x700 - 0x55c) / 4 - 1];
	unsigned int host0_con[2];
	unsigned int reserved8[(0x880 - 0x704) / 4 - 1];
	unsigned int otg_con3;
	unsigned int reserved9[3];
	unsigned int host0_status4;
	unsigned int reserved10[(0x904 - 0x890) / 4 - 1];
	unsigned int mac_con1;
};

check_member(px30_grf, mac_con1, 0x904);

struct px30_pmugrf {
	unsigned int gpio0a_iomux;
	unsigned int gpio0b_iomux;
	unsigned int gpio0c_iomux;
	unsigned int reserved0[1];
	unsigned int gpio0a_p;
	unsigned int gpio0b_p;
	unsigned int gpio0c_p;
	unsigned int reserved1[1];
	unsigned int gpio0a_e;
	unsigned int gpio0b_e;
	unsigned int gpio0c_e;
	unsigned int reserved2[1];
	unsigned int gpio0l_sr;
	unsigned int gpio0h_sr;
	unsigned int gpio0l_smt;
	unsigned int gpio0h_smt;
	unsigned int reserved3[(0x100 - 0x3c) / 4 - 1];
	unsigned int soc_con[3];
	unsigned int failsafe_con;
	unsigned int reserved4[(0x180 - 0x10c) / 4 - 1];
	unsigned int pvtm_con[2];
	unsigned int reserved5[2];
	unsigned int pvtm_status[2];
	unsigned int reserved6[(0x200 - 0x194) / 4 - 1];
	unsigned int os_reg[12];
	unsigned int reset_function_status;
};

check_member(px30_pmugrf, reset_function_status, 0x230);

#endif
