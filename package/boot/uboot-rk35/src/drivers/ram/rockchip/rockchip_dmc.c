// SPDX-License-Identifier: GPL-2.0
/*
 * (C) Copyright 2018 Rockchip Electronics Co., Ltd
 */
#include <asm/arch-rockchip/rockchip_smccc.h>
#include <asm/arch-rockchip/rockchip_dmc.h>
#include <asm/io.h>
#include <asm/psci.h>
#include <common.h>
#include <clk.h>
#include <dm.h>
#include <dm/of_access.h>
#include <dt-structs.h>
#include <linux/arm-smccc.h>
#include <linux/err.h>
#include <linux/errno.h>
#include <ram.h>
#include <regmap.h>

#define DTS_PAR_OFFSET		(4096)

struct share_params {
	u32 hz;
	u32 lcdc_type;
	u32 vop;
	u32 vop_dclk_mode;
	u32 sr_idle_en;
	u32 addr_mcu_el3;
	/*
	 * 1: need to wait flag1
	 * 0: never wait flag1
	 */
	u32 wait_flag1;
	/*
	 * 1: need to wait flag1
	 * 0: never wait flag1
	 */
	u32 wait_flag0;
	u32 complt_hwirq;
	/* if need, add parameter after */
};

static struct share_params *ddr_psci_param;

/* hope this define can adapt all future platfor */
static const char * const rk3328_dts_timing[] = {
	"ddr3_speed_bin",
	"ddr4_speed_bin",
	"pd_idle",
	"sr_idle",
	"sr_mc_gate_idle",
	"srpd_lite_idle",
	"standby_idle",

	"auto_pd_dis_freq",
	"auto_sr_dis_freq",
	"ddr3_dll_dis_freq",
	"ddr4_dll_dis_freq",
	"phy_dll_dis_freq",

	"ddr3_odt_dis_freq",
	"phy_ddr3_odt_dis_freq",
	"ddr3_drv",
	"ddr3_odt",
	"phy_ddr3_ca_drv",
	"phy_ddr3_ck_drv",
	"phy_ddr3_dq_drv",
	"phy_ddr3_odt",

	"lpddr3_odt_dis_freq",
	"phy_lpddr3_odt_dis_freq",
	"lpddr3_drv",
	"lpddr3_odt",
	"phy_lpddr3_ca_drv",
	"phy_lpddr3_ck_drv",
	"phy_lpddr3_dq_drv",
	"phy_lpddr3_odt",

	"lpddr4_odt_dis_freq",
	"phy_lpddr4_odt_dis_freq",
	"lpddr4_drv",
	"lpddr4_dq_odt",
	"lpddr4_ca_odt",
	"phy_lpddr4_ca_drv",
	"phy_lpddr4_ck_cs_drv",
	"phy_lpddr4_dq_drv",
	"phy_lpddr4_odt",

	"ddr4_odt_dis_freq",
	"phy_ddr4_odt_dis_freq",
	"ddr4_drv",
	"ddr4_odt",
	"phy_ddr4_ca_drv",
	"phy_ddr4_ck_drv",
	"phy_ddr4_dq_drv",
	"phy_ddr4_odt",
};

static const char * const px30_dts_timing[] = {
	"ddr2_speed_bin",
	"ddr3_speed_bin",
	"ddr4_speed_bin",
	"pd_idle",
	"sr_idle",
	"sr_mc_gate_idle",
	"srpd_lite_idle",
	"standby_idle",

	"auto_pd_dis_freq",
	"auto_sr_dis_freq",
	"ddr2_dll_dis_freq",
	"ddr3_dll_dis_freq",
	"ddr4_dll_dis_freq",
	"phy_dll_dis_freq",

	"ddr2_odt_dis_freq",
	"phy_ddr2_odt_dis_freq",
	"ddr2_drv",
	"ddr2_odt",
	"phy_ddr2_ca_drv",
	"phy_ddr2_ck_drv",
	"phy_ddr2_dq_drv",
	"phy_ddr2_odt",

	"ddr3_odt_dis_freq",
	"phy_ddr3_odt_dis_freq",
	"ddr3_drv",
	"ddr3_odt",
	"phy_ddr3_ca_drv",
	"phy_ddr3_ck_drv",
	"phy_ddr3_dq_drv",
	"phy_ddr3_odt",

	"phy_lpddr2_odt_dis_freq",
	"lpddr2_drv",
	"phy_lpddr2_ca_drv",
	"phy_lpddr2_ck_drv",
	"phy_lpddr2_dq_drv",
	"phy_lpddr2_odt",

	"lpddr3_odt_dis_freq",
	"phy_lpddr3_odt_dis_freq",
	"lpddr3_drv",
	"lpddr3_odt",
	"phy_lpddr3_ca_drv",
	"phy_lpddr3_ck_drv",
	"phy_lpddr3_dq_drv",
	"phy_lpddr3_odt",

	"lpddr4_odt_dis_freq",
	"phy_lpddr4_odt_dis_freq",
	"lpddr4_drv",
	"lpddr4_dq_odt",
	"lpddr4_ca_odt",
	"phy_lpddr4_ca_drv",
	"phy_lpddr4_ck_cs_drv",
	"phy_lpddr4_dq_drv",
	"phy_lpddr4_odt",

	"ddr4_odt_dis_freq",
	"phy_ddr4_odt_dis_freq",
	"ddr4_drv",
	"ddr4_odt",
	"phy_ddr4_ca_drv",
	"phy_ddr4_ck_drv",
	"phy_ddr4_dq_drv",
	"phy_ddr4_odt",
};

static const char * const rk3328_dts_ca_timing[] = {
	"ddr3a1_ddr4a9_de-skew",
	"ddr3a0_ddr4a10_de-skew",
	"ddr3a3_ddr4a6_de-skew",
	"ddr3a2_ddr4a4_de-skew",
	"ddr3a5_ddr4a8_de-skew",
	"ddr3a4_ddr4a5_de-skew",
	"ddr3a7_ddr4a11_de-skew",
	"ddr3a6_ddr4a7_de-skew",
	"ddr3a9_ddr4a0_de-skew",
	"ddr3a8_ddr4a13_de-skew",
	"ddr3a11_ddr4a3_de-skew",
	"ddr3a10_ddr4cs0_de-skew",
	"ddr3a13_ddr4a2_de-skew",
	"ddr3a12_ddr4ba1_de-skew",
	"ddr3a15_ddr4odt0_de-skew",
	"ddr3a14_ddr4a1_de-skew",
	"ddr3ba1_ddr4a15_de-skew",
	"ddr3ba0_ddr4bg0_de-skew",
	"ddr3ras_ddr4cke_de-skew",
	"ddr3ba2_ddr4ba0_de-skew",
	"ddr3we_ddr4bg1_de-skew",
	"ddr3cas_ddr4a12_de-skew",
	"ddr3ckn_ddr4ckn_de-skew",
	"ddr3ckp_ddr4ckp_de-skew",
	"ddr3cke_ddr4a16_de-skew",
	"ddr3odt0_ddr4a14_de-skew",
	"ddr3cs0_ddr4act_de-skew",
	"ddr3reset_ddr4reset_de-skew",
	"ddr3cs1_ddr4cs1_de-skew",
	"ddr3odt1_ddr4odt1_de-skew",
};

static const char * const rk3328_dts_cs0_timing[] = {
	"cs0_dm0_rx_de-skew",
	"cs0_dm0_tx_de-skew",
	"cs0_dq0_rx_de-skew",
	"cs0_dq0_tx_de-skew",
	"cs0_dq1_rx_de-skew",
	"cs0_dq1_tx_de-skew",
	"cs0_dq2_rx_de-skew",
	"cs0_dq2_tx_de-skew",
	"cs0_dq3_rx_de-skew",
	"cs0_dq3_tx_de-skew",
	"cs0_dq4_rx_de-skew",
	"cs0_dq4_tx_de-skew",
	"cs0_dq5_rx_de-skew",
	"cs0_dq5_tx_de-skew",
	"cs0_dq6_rx_de-skew",
	"cs0_dq6_tx_de-skew",
	"cs0_dq7_rx_de-skew",
	"cs0_dq7_tx_de-skew",
	"cs0_dqs0_rx_de-skew",
	"cs0_dqs0p_tx_de-skew",
	"cs0_dqs0n_tx_de-skew",

	"cs0_dm1_rx_de-skew",
	"cs0_dm1_tx_de-skew",
	"cs0_dq8_rx_de-skew",
	"cs0_dq8_tx_de-skew",
	"cs0_dq9_rx_de-skew",
	"cs0_dq9_tx_de-skew",
	"cs0_dq10_rx_de-skew",
	"cs0_dq10_tx_de-skew",
	"cs0_dq11_rx_de-skew",
	"cs0_dq11_tx_de-skew",
	"cs0_dq12_rx_de-skew",
	"cs0_dq12_tx_de-skew",
	"cs0_dq13_rx_de-skew",
	"cs0_dq13_tx_de-skew",
	"cs0_dq14_rx_de-skew",
	"cs0_dq14_tx_de-skew",
	"cs0_dq15_rx_de-skew",
	"cs0_dq15_tx_de-skew",
	"cs0_dqs1_rx_de-skew",
	"cs0_dqs1p_tx_de-skew",
	"cs0_dqs1n_tx_de-skew",

	"cs0_dm2_rx_de-skew",
	"cs0_dm2_tx_de-skew",
	"cs0_dq16_rx_de-skew",
	"cs0_dq16_tx_de-skew",
	"cs0_dq17_rx_de-skew",
	"cs0_dq17_tx_de-skew",
	"cs0_dq18_rx_de-skew",
	"cs0_dq18_tx_de-skew",
	"cs0_dq19_rx_de-skew",
	"cs0_dq19_tx_de-skew",
	"cs0_dq20_rx_de-skew",
	"cs0_dq20_tx_de-skew",
	"cs0_dq21_rx_de-skew",
	"cs0_dq21_tx_de-skew",
	"cs0_dq22_rx_de-skew",
	"cs0_dq22_tx_de-skew",
	"cs0_dq23_rx_de-skew",
	"cs0_dq23_tx_de-skew",
	"cs0_dqs2_rx_de-skew",
	"cs0_dqs2p_tx_de-skew",
	"cs0_dqs2n_tx_de-skew",

	"cs0_dm3_rx_de-skew",
	"cs0_dm3_tx_de-skew",
	"cs0_dq24_rx_de-skew",
	"cs0_dq24_tx_de-skew",
	"cs0_dq25_rx_de-skew",
	"cs0_dq25_tx_de-skew",
	"cs0_dq26_rx_de-skew",
	"cs0_dq26_tx_de-skew",
	"cs0_dq27_rx_de-skew",
	"cs0_dq27_tx_de-skew",
	"cs0_dq28_rx_de-skew",
	"cs0_dq28_tx_de-skew",
	"cs0_dq29_rx_de-skew",
	"cs0_dq29_tx_de-skew",
	"cs0_dq30_rx_de-skew",
	"cs0_dq30_tx_de-skew",
	"cs0_dq31_rx_de-skew",
	"cs0_dq31_tx_de-skew",
	"cs0_dqs3_rx_de-skew",
	"cs0_dqs3p_tx_de-skew",
	"cs0_dqs3n_tx_de-skew",
};

static const char * const rk3328_dts_cs1_timing[] = {
	"cs1_dm0_rx_de-skew",
	"cs1_dm0_tx_de-skew",
	"cs1_dq0_rx_de-skew",
	"cs1_dq0_tx_de-skew",
	"cs1_dq1_rx_de-skew",
	"cs1_dq1_tx_de-skew",
	"cs1_dq2_rx_de-skew",
	"cs1_dq2_tx_de-skew",
	"cs1_dq3_rx_de-skew",
	"cs1_dq3_tx_de-skew",
	"cs1_dq4_rx_de-skew",
	"cs1_dq4_tx_de-skew",
	"cs1_dq5_rx_de-skew",
	"cs1_dq5_tx_de-skew",
	"cs1_dq6_rx_de-skew",
	"cs1_dq6_tx_de-skew",
	"cs1_dq7_rx_de-skew",
	"cs1_dq7_tx_de-skew",
	"cs1_dqs0_rx_de-skew",
	"cs1_dqs0p_tx_de-skew",
	"cs1_dqs0n_tx_de-skew",

	"cs1_dm1_rx_de-skew",
	"cs1_dm1_tx_de-skew",
	"cs1_dq8_rx_de-skew",
	"cs1_dq8_tx_de-skew",
	"cs1_dq9_rx_de-skew",
	"cs1_dq9_tx_de-skew",
	"cs1_dq10_rx_de-skew",
	"cs1_dq10_tx_de-skew",
	"cs1_dq11_rx_de-skew",
	"cs1_dq11_tx_de-skew",
	"cs1_dq12_rx_de-skew",
	"cs1_dq12_tx_de-skew",
	"cs1_dq13_rx_de-skew",
	"cs1_dq13_tx_de-skew",
	"cs1_dq14_rx_de-skew",
	"cs1_dq14_tx_de-skew",
	"cs1_dq15_rx_de-skew",
	"cs1_dq15_tx_de-skew",
	"cs1_dqs1_rx_de-skew",
	"cs1_dqs1p_tx_de-skew",
	"cs1_dqs1n_tx_de-skew",

	"cs1_dm2_rx_de-skew",
	"cs1_dm2_tx_de-skew",
	"cs1_dq16_rx_de-skew",
	"cs1_dq16_tx_de-skew",
	"cs1_dq17_rx_de-skew",
	"cs1_dq17_tx_de-skew",
	"cs1_dq18_rx_de-skew",
	"cs1_dq18_tx_de-skew",
	"cs1_dq19_rx_de-skew",
	"cs1_dq19_tx_de-skew",
	"cs1_dq20_rx_de-skew",
	"cs1_dq20_tx_de-skew",
	"cs1_dq21_rx_de-skew",
	"cs1_dq21_tx_de-skew",
	"cs1_dq22_rx_de-skew",
	"cs1_dq22_tx_de-skew",
	"cs1_dq23_rx_de-skew",
	"cs1_dq23_tx_de-skew",
	"cs1_dqs2_rx_de-skew",
	"cs1_dqs2p_tx_de-skew",
	"cs1_dqs2n_tx_de-skew",

	"cs1_dm3_rx_de-skew",
	"cs1_dm3_tx_de-skew",
	"cs1_dq24_rx_de-skew",
	"cs1_dq24_tx_de-skew",
	"cs1_dq25_rx_de-skew",
	"cs1_dq25_tx_de-skew",
	"cs1_dq26_rx_de-skew",
	"cs1_dq26_tx_de-skew",
	"cs1_dq27_rx_de-skew",
	"cs1_dq27_tx_de-skew",
	"cs1_dq28_rx_de-skew",
	"cs1_dq28_tx_de-skew",
	"cs1_dq29_rx_de-skew",
	"cs1_dq29_tx_de-skew",
	"cs1_dq30_rx_de-skew",
	"cs1_dq30_tx_de-skew",
	"cs1_dq31_rx_de-skew",
	"cs1_dq31_tx_de-skew",
	"cs1_dqs3_rx_de-skew",
	"cs1_dqs3p_tx_de-skew",
	"cs1_dqs3n_tx_de-skew",
};

struct rk3328_ddr_dts_config_timing {
	unsigned int ddr3_speed_bin;
	unsigned int ddr4_speed_bin;
	unsigned int pd_idle;
	unsigned int sr_idle;
	unsigned int sr_mc_gate_idle;
	unsigned int srpd_lite_idle;
	unsigned int standby_idle;

	unsigned int auto_pd_dis_freq;
	unsigned int auto_sr_dis_freq;
	/* for ddr3 only */
	unsigned int ddr3_dll_dis_freq;
	/* for ddr4 only */
	unsigned int ddr4_dll_dis_freq;
	unsigned int phy_dll_dis_freq;

	unsigned int ddr3_odt_dis_freq;
	unsigned int phy_ddr3_odt_dis_freq;
	unsigned int ddr3_drv;
	unsigned int ddr3_odt;
	unsigned int phy_ddr3_ca_drv;
	unsigned int phy_ddr3_ck_drv;
	unsigned int phy_ddr3_dq_drv;
	unsigned int phy_ddr3_odt;

	unsigned int lpddr3_odt_dis_freq;
	unsigned int phy_lpddr3_odt_dis_freq;
	unsigned int lpddr3_drv;
	unsigned int lpddr3_odt;
	unsigned int phy_lpddr3_ca_drv;
	unsigned int phy_lpddr3_ck_drv;
	unsigned int phy_lpddr3_dq_drv;
	unsigned int phy_lpddr3_odt;

	unsigned int lpddr4_odt_dis_freq;
	unsigned int phy_lpddr4_odt_dis_freq;
	unsigned int lpddr4_drv;
	unsigned int lpddr4_dq_odt;
	unsigned int lpddr4_ca_odt;
	unsigned int phy_lpddr4_ca_drv;
	unsigned int phy_lpddr4_ck_cs_drv;
	unsigned int phy_lpddr4_dq_drv;
	unsigned int phy_lpddr4_odt;

	unsigned int ddr4_odt_dis_freq;
	unsigned int phy_ddr4_odt_dis_freq;
	unsigned int ddr4_drv;
	unsigned int ddr4_odt;
	unsigned int phy_ddr4_ca_drv;
	unsigned int phy_ddr4_ck_drv;
	unsigned int phy_ddr4_dq_drv;
	unsigned int phy_ddr4_odt;

	unsigned int ca_skew[15];
	unsigned int cs0_skew[44];
	unsigned int cs1_skew[44];

	unsigned int available;
};

struct px30_ddr_dts_config_timing {
	unsigned int ddr2_speed_bin;
	unsigned int ddr3_speed_bin;
	unsigned int ddr4_speed_bin;
	unsigned int pd_idle;
	unsigned int sr_idle;
	unsigned int sr_mc_gate_idle;
	unsigned int srpd_lite_idle;
	unsigned int standby_idle;

	unsigned int auto_pd_dis_freq;
	unsigned int auto_sr_dis_freq;
	/* for ddr2 only */
	unsigned int ddr2_dll_dis_freq;
	/* for ddr3 only */
	unsigned int ddr3_dll_dis_freq;
	/* for ddr4 only */
	unsigned int ddr4_dll_dis_freq;
	unsigned int phy_dll_dis_freq;

	unsigned int ddr2_odt_dis_freq;
	unsigned int phy_ddr2_odt_dis_freq;
	unsigned int ddr2_drv;
	unsigned int ddr2_odt;
	unsigned int phy_ddr2_ca_drv;
	unsigned int phy_ddr2_ck_drv;
	unsigned int phy_ddr2_dq_drv;
	unsigned int phy_ddr2_odt;

	unsigned int ddr3_odt_dis_freq;
	unsigned int phy_ddr3_odt_dis_freq;
	unsigned int ddr3_drv;
	unsigned int ddr3_odt;
	unsigned int phy_ddr3_ca_drv;
	unsigned int phy_ddr3_ck_drv;
	unsigned int phy_ddr3_dq_drv;
	unsigned int phy_ddr3_odt;

	unsigned int phy_lpddr2_odt_dis_freq;
	unsigned int lpddr2_drv;
	unsigned int phy_lpddr2_ca_drv;
	unsigned int phy_lpddr2_ck_drv;
	unsigned int phy_lpddr2_dq_drv;
	unsigned int phy_lpddr2_odt;

	unsigned int lpddr3_odt_dis_freq;
	unsigned int phy_lpddr3_odt_dis_freq;
	unsigned int lpddr3_drv;
	unsigned int lpddr3_odt;
	unsigned int phy_lpddr3_ca_drv;
	unsigned int phy_lpddr3_ck_drv;
	unsigned int phy_lpddr3_dq_drv;
	unsigned int phy_lpddr3_odt;

	unsigned int lpddr4_odt_dis_freq;
	unsigned int phy_lpddr4_odt_dis_freq;
	unsigned int lpddr4_drv;
	unsigned int lpddr4_dq_odt;
	unsigned int lpddr4_ca_odt;
	unsigned int phy_lpddr4_ca_drv;
	unsigned int phy_lpddr4_ck_cs_drv;
	unsigned int phy_lpddr4_dq_drv;
	unsigned int phy_lpddr4_odt;

	unsigned int ddr4_odt_dis_freq;
	unsigned int phy_ddr4_odt_dis_freq;
	unsigned int ddr4_drv;
	unsigned int ddr4_odt;
	unsigned int phy_ddr4_ca_drv;
	unsigned int phy_ddr4_ck_drv;
	unsigned int phy_ddr4_dq_drv;
	unsigned int phy_ddr4_odt;

	unsigned int ca_skew[15];
	unsigned int cs0_skew[44];
	unsigned int cs1_skew[44];

	unsigned int available;
};

struct rk3328_ddr_de_skew_setting {
	unsigned int ca_de_skew[30];
	unsigned int cs0_de_skew[84];
	unsigned int cs1_de_skew[84];
};

static void
rk3328_de_skew_setting_2_register(struct rk3328_ddr_de_skew_setting *de_skew,
				  struct rk3328_ddr_dts_config_timing *tim)
{
	u32 n;
	u32 offset;
	u32 shift;

	memset_io(tim->ca_skew, 0, sizeof(tim->ca_skew));
	memset_io(tim->cs0_skew, 0, sizeof(tim->cs0_skew));
	memset_io(tim->cs1_skew, 0, sizeof(tim->cs1_skew));

	/* CA de-skew */
	for (n = 0; n < ARRAY_SIZE(de_skew->ca_de_skew); n++) {
		offset = n / 2;
		shift = n % 2;
		/* 0 => 4; 1 => 0 */
		shift = (shift == 0) ? 4 : 0;
		tim->ca_skew[offset] &= ~(0xf << shift);
		tim->ca_skew[offset] |= (de_skew->ca_de_skew[n] << shift);
	}

	/* CS0 data de-skew */
	for (n = 0; n < ARRAY_SIZE(de_skew->cs0_de_skew); n++) {
		offset = ((n / 21) * 11) + ((n % 21) / 2);
		shift = ((n % 21) % 2);
		if ((n % 21) == 20)
			shift = 0;
		else
			/* 0 => 4; 1 => 0 */
			shift = (shift == 0) ? 4 : 0;
		tim->cs0_skew[offset] &= ~(0xf << shift);
		tim->cs0_skew[offset] |= (de_skew->cs0_de_skew[n] << shift);
	}

	/* CS1 data de-skew */
	for (n = 0; n < ARRAY_SIZE(de_skew->cs1_de_skew); n++) {
		offset = ((n / 21) * 11) + ((n % 21) / 2);
		shift = ((n % 21) % 2);
		if ((n % 21) == 20)
			shift = 0;
		else
			/* 0 => 4; 1 => 0 */
			shift = (shift == 0) ? 4 : 0;
		tim->cs1_skew[offset] &= ~(0xf << shift);
		tim->cs1_skew[offset] |= (de_skew->cs1_de_skew[n] << shift);
	}
}

static void px30_de_skew_set_2_reg(struct rk3328_ddr_de_skew_setting *de_skew,
				   struct px30_ddr_dts_config_timing *tim)
{
	u32 n;
	u32 offset;
	u32 shift;

	memset_io(tim->ca_skew, 0, sizeof(tim->ca_skew));
	memset_io(tim->cs0_skew, 0, sizeof(tim->cs0_skew));
	memset_io(tim->cs1_skew, 0, sizeof(tim->cs1_skew));

	/* CA de-skew */
	for (n = 0; n < ARRAY_SIZE(de_skew->ca_de_skew); n++) {
		offset = n / 2;
		shift = n % 2;
		/* 0 => 4; 1 => 0 */
		shift = (shift == 0) ? 4 : 0;
		tim->ca_skew[offset] &= ~(0xf << shift);
		tim->ca_skew[offset] |= (de_skew->ca_de_skew[n] << shift);
	}

	/* CS0 data de-skew */
	for (n = 0; n < ARRAY_SIZE(de_skew->cs0_de_skew); n++) {
		offset = ((n / 21) * 11) + ((n % 21) / 2);
		shift = ((n % 21) % 2);
		if ((n % 21) == 20)
			shift = 0;
		else
			/* 0 => 4; 1 => 0 */
			shift = (shift == 0) ? 4 : 0;
		tim->cs0_skew[offset] &= ~(0xf << shift);
		tim->cs0_skew[offset] |= (de_skew->cs0_de_skew[n] << shift);
	}

	/* CS1 data de-skew */
	for (n = 0; n < ARRAY_SIZE(de_skew->cs1_de_skew); n++) {
		offset = ((n / 21) * 11) + ((n % 21) / 2);
		shift = ((n % 21) % 2);
		if ((n % 21) == 20)
			shift = 0;
		else
			/* 0 => 4; 1 => 0 */
			shift = (shift == 0) ? 4 : 0;
		tim->cs1_skew[offset] &= ~(0xf << shift);
		tim->cs1_skew[offset] |= (de_skew->cs1_de_skew[n] << shift);
	}
}

static void of_get_rk3328_timings(struct udevice *dev, uint32_t *timing)
{
	struct device_node *np_tim;
	u32 *p;
	struct rk3328_ddr_dts_config_timing *dts_timing;
	struct rk3328_ddr_de_skew_setting *de_skew;
	int ret = 0;
	u32 i;

	dts_timing =
		(struct rk3328_ddr_dts_config_timing *)(timing +
							DTS_PAR_OFFSET / 4);

	np_tim = of_parse_phandle(ofnode_to_np(dev_ofnode(dev)),
				  "ddr_timing", 0);
	if (!np_tim) {
		ret = -EINVAL;
		goto end;
	}
	de_skew = malloc(sizeof(*de_skew));
	if (!de_skew) {
		ret = -ENOMEM;
		goto end;
	}
	p = (u32 *)dts_timing;
	for (i = 0; i < ARRAY_SIZE(rk3328_dts_timing); i++)
		ret |= ofnode_read_u32(np_to_ofnode(np_tim),
				       rk3328_dts_timing[i], p + i);

	p = (u32 *)de_skew->ca_de_skew;
	for (i = 0; i < ARRAY_SIZE(rk3328_dts_ca_timing); i++)
		ret |= ofnode_read_u32(np_to_ofnode(np_tim),
				       rk3328_dts_ca_timing[i], p + i);
	p = (u32 *)de_skew->cs0_de_skew;
	for (i = 0; i < ARRAY_SIZE(rk3328_dts_cs0_timing); i++)
		ret |= ofnode_read_u32(np_to_ofnode(np_tim),
				       rk3328_dts_cs0_timing[i], p + i);
	p = (u32 *)de_skew->cs1_de_skew;
	for (i = 0; i < ARRAY_SIZE(rk3328_dts_cs1_timing); i++)
		ret |= ofnode_read_u32(np_to_ofnode(np_tim),
				       rk3328_dts_cs1_timing[i], p + i);

	if (!ret)
		rk3328_de_skew_setting_2_register(de_skew, dts_timing);
	free(de_skew);
end:
	if (!ret) {
		dts_timing->available = 1;
	} else {
		dts_timing->available = 0;
		printf("of_get_ddr_timings: fail\n");
	}
}

static void of_get_px30_timings(struct udevice *dev, uint32_t *timing)
{
	struct device_node *np_tim;
	u32 *p;
	struct px30_ddr_dts_config_timing *dts_timing;
	struct rk3328_ddr_de_skew_setting *de_skew;
	int ret = 0;
	u32 i;

	dts_timing =
		(struct px30_ddr_dts_config_timing *)(timing +
							DTS_PAR_OFFSET / 4);

	np_tim = of_parse_phandle(ofnode_to_np(dev_ofnode(dev)),
				  "ddr_timing", 0);
	if (!np_tim) {
		ret = -EINVAL;
		goto end;
	}
	de_skew = malloc(sizeof(*de_skew));
	if (!de_skew) {
		ret = -ENOMEM;
		goto end;
	}
	p = (u32 *)dts_timing;
	for (i = 0; i < ARRAY_SIZE(px30_dts_timing); i++)
		ret |= ofnode_read_u32(np_to_ofnode(np_tim), px30_dts_timing[i],
					p + i);
	p = (u32 *)de_skew->ca_de_skew;
	for (i = 0; i < ARRAY_SIZE(rk3328_dts_ca_timing); i++)
		ret |= ofnode_read_u32(np_to_ofnode(np_tim),
				       rk3328_dts_ca_timing[i], p + i);
	p = (u32 *)de_skew->cs0_de_skew;
	for (i = 0; i < ARRAY_SIZE(rk3328_dts_cs0_timing); i++)
		ret |= ofnode_read_u32(np_to_ofnode(np_tim),
				       rk3328_dts_cs0_timing[i], p + i);
	p = (u32 *)de_skew->cs1_de_skew;
	for (i = 0; i < ARRAY_SIZE(rk3328_dts_cs1_timing); i++)
		ret |= ofnode_read_u32(np_to_ofnode(np_tim),
				       rk3328_dts_cs1_timing[i], p + i);
	if (!ret)
		px30_de_skew_set_2_reg(de_skew, dts_timing);
	free(de_skew);
end:
	if (!ret) {
		dts_timing->available = 1;
	} else {
		dts_timing->available = 0;
		printf("of_get_ddr_timings: fail\n");
	}
}

static __maybe_unused int rk3328_devfreq_init(struct udevice *dev)
{
	struct arm_smccc_res res;
	u32 size;

	res = sip_smc_dram(0, 0,
			   ROCKCHIP_SIP_CONFIG_DRAM_GET_VERSION);
	printf("current ATF version 0x%lx!\n", res.a1);
	if (res.a0 || res.a1 < 0x101) {
		printf("trusted firmware need to update or is invalid!\n");
		return -ENXIO;
	}

	printf("read tf version 0x%lx!\n", res.a1);

	/*
	 * first 4KB is used for interface parameters
	 * after 4KB * N is dts parameters
	 */
	size = sizeof(struct rk3328_ddr_dts_config_timing);
	res = sip_smc_request_share_mem(DIV_ROUND_UP(size, 4096) + 1,
					SHARE_PAGE_TYPE_DDR);
	if (res.a0 != 0) {
		printf("no ATF memory for init\n");
		return -ENOMEM;
	}
	ddr_psci_param = (struct share_params *)res.a1;
	of_get_rk3328_timings(dev, (uint32_t *)ddr_psci_param);

	flush_cache((unsigned long)ddr_psci_param,
		    (DIV_ROUND_UP(size, 4096) + 1) * 0x1000);

	res = sip_smc_dram(SHARE_PAGE_TYPE_DDR, 0,
			   ROCKCHIP_SIP_CONFIG_DRAM_INIT);
	if (res.a0) {
		printf("rockchip_sip_config_dram_init error:%lx\n",
		       res.a0);
		return -ENOMEM;
	}

	return 0;
}

static __maybe_unused int px30_devfreq_init(struct udevice *dev)
{
	struct arm_smccc_res res;
	u32 size;

	res = sip_smc_dram(0, 0,
			   ROCKCHIP_SIP_CONFIG_DRAM_GET_VERSION);
	printf("current ATF version 0x%lx!\n", res.a1);
	if (res.a0 || res.a1 < 0x103) {
		printf("trusted firmware need to update or is invalid!\n");
		return -ENXIO;
	}

	printf("read tf version 0x%lx!\n", res.a1);

	/*
	 * first 4KB is used for interface parameters
	 * after 4KB * N is dts parameters
	 */
	size = sizeof(struct px30_ddr_dts_config_timing);
	res = sip_smc_request_share_mem(DIV_ROUND_UP(size, 4096) + 1,
					SHARE_PAGE_TYPE_DDR);
	if (res.a0 != 0) {
		printf("no ATF memory for init\n");
		return -ENOMEM;
	}

	ddr_psci_param = (struct share_params *)res.a1;
	of_get_px30_timings(dev, (uint32_t *)ddr_psci_param);

	flush_cache((unsigned long)ddr_psci_param,
		    (DIV_ROUND_UP(size, 4096) + 1) * 0x1000);
	res = sip_smc_dram(SHARE_PAGE_TYPE_DDR, 0,
			   ROCKCHIP_SIP_CONFIG_DRAM_INIT);
	if (res.a0) {
		printf("rockchip_sip_config_dram_init error:%lx\n",
		       res.a0);
		return -ENOMEM;
	}

	return 0;
}

int rockchip_ddrclk_sip_set_rate_v2(unsigned long drate)
{
	struct share_params *p;
	struct arm_smccc_res res;

	p = ddr_psci_param;

	p->hz = drate;
	p->lcdc_type = 0;
	p->wait_flag1 = 0;
	p->wait_flag0 = 0;
	p->complt_hwirq = 105;

	flush_cache((unsigned long)ddr_psci_param, sizeof(struct share_params));
	res = sip_smc_dram(SHARE_PAGE_TYPE_DDR, 0,
			   ROCKCHIP_SIP_CONFIG_DRAM_SET_RATE);

	return res.a0;
}

unsigned long rockchip_ddrclk_sip_recalc_rate_v2(void)
{
	struct arm_smccc_res res;

	res = sip_smc_dram(SHARE_PAGE_TYPE_DDR, 0,
			   ROCKCHIP_SIP_CONFIG_DRAM_GET_RATE);
	if (!res.a0)
		return res.a1;
	else
		return 0;
}

unsigned long rockchip_ddrclk_sip_round_rate_v2(unsigned long rate)
{
	struct share_params *p;
	struct arm_smccc_res res;

	p = ddr_psci_param;

	p->hz = rate;

	flush_cache((unsigned long)ddr_psci_param, sizeof(struct share_params));

	res = sip_smc_dram(SHARE_PAGE_TYPE_DDR, 0,
			   ROCKCHIP_SIP_CONFIG_DRAM_ROUND_RATE);
	if (!res.a0)
		return res.a1;
	else
		return 0;
}

int set_ddr_freq(unsigned long freq)
{
	if (freq < MHZ)
		freq *= MHZ;
	if (freq) {
		freq = rockchip_ddrclk_sip_round_rate_v2(freq);
		rockchip_ddrclk_sip_set_rate_v2(freq);
	}
	freq = rockchip_ddrclk_sip_recalc_rate_v2();
	printf("current ddr freq:%lu Hz\n", freq);

	return freq;
}

int rockchip_dmcfreq_probe(struct udevice *dev)
{
	int ret;

#if defined(CONFIG_ROCKCHIP_PX30)
	ret = px30_devfreq_init(dev);
#elif defined(CONFIG_ROCKCHIP_RK3328)
	ret = rk3328_devfreq_init(dev);
#else
	ret = -1;
	printf("Unsupported chip type\n");
#endif
	if (ret)
		return ret;

	printf("dram freq:%ld Hz\n", rockchip_ddrclk_sip_recalc_rate_v2());

	return 0;
}
