/*
 * (C) Copyright 2018 Rockchip Electronics Co., Ltd.
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */
#ifndef _ASM_ARCH_GRF_rk3308_H
#define _ASM_ARCH_GRF_rk3308_H

#include <common.h>

struct rk3308_grf {
	unsigned int gpio0a_iomux;
	unsigned int reserved0;
	unsigned int gpio0b_iomux;
	unsigned int reserved1;
	unsigned int gpio0c_iomux;
	unsigned int reserved2[3];
	unsigned int gpio1a_iomux;
	unsigned int reserved3;
	unsigned int gpio1bl_iomux;
	unsigned int gpio1bh_iomux;
	unsigned int gpio1cl_iomux;
	unsigned int gpio1ch_iomux;
	unsigned int gpio1d_iomux;
	unsigned int reserved4;
	unsigned int gpio2a_iomux;
	unsigned int reserved5;
	unsigned int gpio2b_iomux;
	unsigned int reserved6;
	unsigned int gpio2c_iomux;
	unsigned int reserved7[3];
	unsigned int gpio3a_iomux;
	unsigned int reserved8;
	unsigned int gpio3b_iomux;
	unsigned int reserved9[5];
	unsigned int gpio4a_iomux;
	unsigned int reserved33;
	unsigned int gpio4b_iomux;
	unsigned int reserved10;
	unsigned int gpio4c_iomux;
	unsigned int reserved11;
	unsigned int gpio4d_iomux;
	unsigned int reserved34;
	unsigned int gpio0a_p;
	unsigned int gpio0b_p;
	unsigned int gpio0c_p;
	unsigned int reserved12;
	unsigned int gpio1a_p;
	unsigned int gpio1b_p;
	unsigned int gpio1c_p;
	unsigned int gpio1d_p;
	unsigned int gpio2a_p;
	unsigned int gpio2b_p;
	unsigned int gpio2c_p;
	unsigned int reserved13;
	unsigned int gpio3a_p;
	unsigned int gpio3b_p;
	unsigned int reserved14[2];
	unsigned int gpio4a_p;
	unsigned int gpio4b_p;
	unsigned int gpio4c_p;
	unsigned int gpio4d_p;
	unsigned int reserved15[(0x100 - 0xec) / 4 - 1];
	unsigned int gpio0a_e;
	unsigned int gpio0b_e;
	unsigned int gpio0c_e;
	unsigned int reserved16;
	unsigned int gpio1a_e;
	unsigned int gpio1b_e;
	unsigned int gpio1c_e;
	unsigned int gpio1d_e;
	unsigned int gpio2a_e;
	unsigned int gpio2b_e;
	unsigned int gpio2c_e;
	unsigned int reserved17;
	unsigned int gpio3a_e;
	unsigned int gpio3b_e;
	unsigned int reserved18[2];
	unsigned int gpio4a_e;
	unsigned int gpio4b_e;
	unsigned int gpio4c_e;
	unsigned int gpio4d_e;
	unsigned int gpio0a_sr;
	unsigned int gpio0b_sr;
	unsigned int gpio0c_sr;
	unsigned int reserved19;
	unsigned int gpio1a_sr;
	unsigned int gpio1b_sr;
	unsigned int gpio1c_sr;
	unsigned int gpio1d_sr;
	unsigned int gpio2a_sr;
	unsigned int gpio2b_sr;
	unsigned int gpio2c_sr;
	unsigned int reserved20;
	unsigned int gpio3a_sr;
	unsigned int gpio3b_sr;
	unsigned int reserved21[2];
	unsigned int gpio4a_sr;
	unsigned int gpio4b_sr;
	unsigned int gpio4c_sr;
	unsigned int gpio4d_sr;
	unsigned int gpio0a_smt;
	unsigned int gpio0b_smt;
	unsigned int gpio0c_smt;
	unsigned int reserved22;
	unsigned int gpio1a_smt;
	unsigned int gpio1b_smt;
	unsigned int gpio1c_smt;
	unsigned int gpio1d_smt;
	unsigned int gpio2a_smt;
	unsigned int gpio2b_smt;
	unsigned int gpio2c_smt;
	unsigned int reserved23;
	unsigned int gpio3a_smt;
	unsigned int gpio3b_smt;
	unsigned int reserved35[2];
	unsigned int gpio4a_smt;
	unsigned int gpio4b_smt;
	unsigned int gpio4c_smt;
	unsigned int gpio4d_smt;
	unsigned int reserved24[(0x300 - 0x1EC) / 4 - 1];
	unsigned int soc_con0;
	unsigned int soc_con1;
	unsigned int soc_con2;
	unsigned int soc_con3;
	unsigned int soc_con4;
	unsigned int soc_con5;
	unsigned int soc_con6;
	unsigned int soc_con7;
	unsigned int soc_con8;
	unsigned int soc_con9;
	unsigned int soc_con10;
	unsigned int reserved25[(0x380 - 0x328) / 4 - 1];
	unsigned int soc_status0;
	unsigned int reserved26[(0x400 - 0x380) / 4 - 1];
	unsigned int cpu_con0;
	unsigned int cpu_con1;
	unsigned int cpu_con2;
	unsigned int reserved27[(0x420 - 0x408) / 4 - 1];
	unsigned int cpu_status0;
	unsigned int cpu_status1;
	unsigned int reserved28[(0x440 - 0x424) / 4 - 1];
	unsigned int pvtm_con0;
	unsigned int pvtm_con1;
	unsigned int pvtm_status0;
	unsigned int pvtm_status1;
	unsigned int reserved29[(0x460 - 0x44C) / 4 - 1];
	unsigned int tsadc_tbl;
	unsigned int tsadc_tbh;
	unsigned int reserved30[(0x480 - 0x464) / 4 - 1];
	unsigned int host0_con0;
	unsigned int host0_con1;
	unsigned int otg_con0;
	unsigned int host0_status0;
	unsigned int reserved31[(0x4a0 - 0x48C) / 4 - 1];
	unsigned int mac_con0;
	unsigned int upctl_con0;
	unsigned int upctl_status0;
	unsigned int reserved32[(0x500 - 0x4A8) / 4 - 1];
	unsigned int os_reg0;
	unsigned int os_reg1;
	unsigned int os_reg2;
	unsigned int os_reg3;
	unsigned int os_reg4;
	unsigned int os_reg5;
	unsigned int os_reg6;
	unsigned int os_reg7;
	unsigned int os_reg8;
	unsigned int os_reg9;
	unsigned int os_reg10;
	unsigned int os_reg11;
	unsigned int reserved38[(0x600 - 0x52c) / 4 - 1];
	unsigned int soc_con12;
	unsigned int reserved39;
	unsigned int soc_con13;
	unsigned int soc_con14;
	unsigned int soc_con15;
	unsigned int reserved40[(0x800 - 0x610) / 4 - 1];
	unsigned int chip_id;
};
check_member(rk3308_grf, gpio0a_p, 0xa0);

struct rk3308_sgrf {
	unsigned int soc_con0;
	unsigned int soc_con1;
	unsigned int con_tzma_r0size;
	unsigned int con_secure0;
	unsigned int reserved0;
	unsigned int clk_timer_en;
	unsigned int clkgat_con;
	unsigned int fastboot_addr;
	unsigned int fastboot_en;
	unsigned int reserved1[(0x30 - 0x24) / 4];
	unsigned int srst_con;
};
check_member(rk3308_sgrf, fastboot_en, 0x20);

enum {
	/* GPIO0B_IOMUX */
	GPIO0B_SEL_SHIFT		= 0x0,
	GPIO0B_SEL_MASK			= 0x3 << GPIO0B_SEL_SHIFT,

	/* GPIO1D_IOMUX */
	GPIO1D1_SEL_SHIFT		= 2,
	GPIO1D1_SEL_MASK		= 0x3 << GPIO1D1_SEL_SHIFT,
	GPIO1D1_SEL_UART1_TX		= 1,
	GPIO1D0_SEL_SHIFT		= 0,
	GPIO1D0_SEL_MASK		= 0x3 << GPIO1D0_SEL_SHIFT,
	GPIO1D1_SEL_UART1_RX		= 1,

	/* GPIO2A_IOMUX */
	GPIO2A1_SEL_SHIFT		= 2,
	GPIO2A1_SEL_MASK		= 0x3 << GPIO2A1_SEL_SHIFT,
	GPIO2A1_SEL_UART0_TX		= 1,
	GPIO2A0_SEL_SHIFT		= 0,
	GPIO2A0_SEL_MASK		= 0x3 << GPIO2A0_SEL_SHIFT,
	GPIO2A0_SEL_UART0_RX		= 1,

	/* GPIO3B_IOMUX */
	GPIO3B5_SEL_SHIFT		= 12,
	GPIO3B5_SEL_MASK		= 0xf << GPIO3B5_SEL_SHIFT,
	GPIO3B5_SEL_UART3_TX		= 4,
	GPIO3B4_SEL_SHIFT		= 8,
	GPIO3B4_SEL_MASK		= 0xf << GPIO3B4_SEL_SHIFT,
	GPIO3B4_SEL_UART3_RX		= 4,

	/* GPIO4B_IOMUX */
	GPIO4B1_SEL_SHIFT		= 2,
	GPIO4B1_SEL_MASK		= 0x3 << GPIO4B1_SEL_SHIFT,
	GPIO4B1_SEL_UART4_TX		= 1,
	GPIO4B0_SEL_SHIFT		= 0,
	GPIO4B0_SEL_MASK		= 0x3 << GPIO4B0_SEL_SHIFT,
	GPIO4B0_SEL_UART4_RX		= 1,

	/* GPIO4D_IOMUX */
	GPIO4D3_SEL_SHIFT		= 6,
	GPIO4D3_SEL_MASK		= 0x3 << GPIO4D3_SEL_SHIFT,
	GPIO4D3_SEL_UART2_TXM1		= 2,
	GPIO4D2_SEL_SHIFT		= 4,
	GPIO4D2_SEL_MASK		= 0x3 << GPIO4D2_SEL_SHIFT,
	GPIO4D2_SEL_UART2_RXM1		= 2,

	/* PVTM_CON0 */
	PVTM_PMU_OSC_EN_SHIFT		= 1,
	PVTM_PMU_OSC_EN_MASK		= 0x1 << PVTM_PMU_OSC_EN_SHIFT,
	PVTM_PMU_OSC_EN			= 1,

	PVTM_PMU_START_SHIFT		= 0,
	PVTM_PMU_START_MASK		= 0x1 << PVTM_PMU_START_SHIFT,
	PVTM_PMU_START			= 1,

	/* PVTM_CON1 */
	PVTM_PMU_CAL_CNT		= 0x1234,

	/* PVTM_STATUS0 */
	PVTM_PMU_FREQ_DONE_SHIFT	= 0,
	PVTM_PMU_FREQ_DONE_MASK		= 0x1 << PVTM_PMU_FREQ_DONE_SHIFT,

	/* UPCTL_CON0 */
	CYSYREQ_UPCTL_DDRSTDBY_SHIFT	= 5,
	CYSYREQ_UPCTL_DDRSTDBY_MASK	= 1 << CYSYREQ_UPCTL_DDRSTDBY_SHIFT,
	CYSYREQ_UPCTL_DDRSTDBY_EN	= 1,
	GRF_DDR_16BIT_EN_SHIFT		= 0,
	GRF_DDR_16BIT_EN_MASK		= 1 << GRF_DDR_16BIT_EN_SHIFT,
	GRF_DDR_16BIT_EN		= 1,

	/* UPCTL_STATUS0 */
	DFI_SCRAMBLE_KEY_READY_SHIFT	= 21,
	DFI_SCRAMBLE_KEY_READY_MASK	= 0x1 << DFI_SCRAMBLE_KEY_READY_SHIFT,

	/* SOC_CON5 */
	UART2_MULTI_IOFUNC_SEL_SHIFT	= 2,
	UART2_MULTI_IOFUNC_SEL_MASK	= 0x3 << UART2_MULTI_IOFUNC_SEL_SHIFT,
	UART2_MULTI_IOFUNC_SEL_M1	= 1,

	/* SOC_CON12 */
	NOC_MSCH_MAIN_PARTIAL_SHIFT	= 1,
	NOC_MSCH_MAIN_PARTIAL_MASK	= 0x1 << NOC_MSCH_MAIN_PARTIAL_SHIFT,
	NOC_MSCH_MAIN_PARTIAL_EN	= 1,
	NOC_MSCH_MAINDDR3_SHIFT		= 0,
	NOC_MSCH_MAINDDR3_MASK		= 0x1 << NOC_MSCH_MAINDDR3_SHIFT,
	NOC_MSCH_MAINDDR3_EN		= 1,
	NOC_MSCH_MAINDDR3_DIS		= 0,
};

enum { /* SGRF_CON0 */
	DDR_DFI_SCRAMBLE_EN_SHIFT	= 13,
	DDR_DFI_SCRAMBLE_EN_MASK	= 0x1 << DDR_DFI_SCRAMBLE_EN_SHIFT,
	DDR_DFI_SCRAMBLE_EN		= 1,
};
#endif
