// SPDX-License-Identifier:     GPL-2.0+
/*
 * (C) Copyright 2021 Rockchip Electronics Co., Ltd.
 */

#include <common.h>
#include <dm.h>
#include <syscon.h>
#include <asm/io.h>
#include <dm/of_access.h>
#include <asm/arch-rockchip/clock.h>
#include <asm/arch-rockchip/rockchip_smccc.h>
#include <asm/arch-rockchip/sdram.h>
#include <asm/arch-rockchip/sdram_common.h>

#define DDR2_PARAMS_PHANDLE_NAME		"ddr2_params"
#define DDR3_PARAMS_PHANDLE_NAME		"ddr3_params"
#define DDR4_PARAMS_PHANDLE_NAME		"ddr4_params"
#define LPDDR2_PARAMS_PHANDLE_NAME		"lpddr2_params"
#define LPDDR3_PARAMS_PHANDLE_NAME		"lpddr3_params"
#define LPDDR4_PARAMS_PHANDLE_NAME		"lpddr4_params"
#define LPDDR4X_PARAMS_PHANDLE_NAME		"lpddr4x_params"
#define LPDDR5_PARAMS_PHANDLE_NAME		"lpddr5_params"

#define DTS_PAR_OFFSET				(4096)
#define PARAMS_INVALID_VAL			(0xff00aa99)

#define PMUGRF_OS_REG(n)			(0x200 + (n) * 4)

struct rk3326_ddr_de_skew_setting {
	unsigned int ca_de_skew[30];
	unsigned int cs0_de_skew[84];
	unsigned int cs1_de_skew[84];
};

/* there is a matching relationship, modify it with caution */
static char *dmc_fsp_params[] = {
	"debug_print_level",
	"phy_de_skew_en",
	/* if need, add parameter after */
};

/* there is a matching relationship, modify it with caution */
static char *ddr_params_v1[] = {
	/* version information V1.00 */
	"version",
	"expanded_version",
	"reserved",
	/* freq info, freq_0 is final frequency, unit: MHz */
	"freq_0",
	"freq_1",
	"freq_2",
	"freq_3",
	"freq_4",
	"freq_5",
	/* power save setting */
	"pd_idle",
	"sr_idle",
	"sr_mc_gate_idle",
	"srpd_lite_idle",
	"standby_idle",
	"pd_dis_freq",
	"sr_dis_freq",
	"dram_dll_dis_freq",
	"phy_dll_dis_freq",
	/* drv when odt on */
	"phy_dq_drv_odten",
	"phy_ca_drv_odten",
	"phy_clk_drv_odten",
	"dram_dq_drv_odten",
	/* drv when odt off */
	"phy_dq_drv_odtoff",
	"phy_ca_drv_odtoff",
	"phy_clk_drv_odtoff",
	"dram_dq_drv_odtoff",
	/* odt info */
	"dram_odt",
	"phy_odt",
	"phy_odt_puup_en",
	"phy_odt_pudn_en",
	/* odt enable freq */
	"dram_dq_odt_en_freq",
	"phy_odt_en_freq",
	/* slew rate when odt enable */
	"phy_dq_sr_odten",
	"phy_ca_sr_odten",
	"phy_clk_sr_odten",
	/* slew rate when odt disable */
	"phy_dq_sr_odtoff",
	"phy_ca_sr_odtoff",
	"phy_clk_sr_odtoff",
	/* ssmod setting*/
	"ssmod_downspread",
	"ssmod_div",
	"ssmod_spread",
	/* 2T mode */
	"mode_2t",
	/* speed bin */
	"speed_bin",
	/* dram extended temperature support */
	"dram_ext_temp",
	/* byte map */
	"byte_map",
	/* dq map */
	"dq_map_cs0_dq_l",
	"dq_map_cs0_dq_h",
	"dq_map_cs1_dq_l",
	"dq_map_cs1_dq_h",
	/* for LPDDR4 and LPDDR4X */
	/* odt info */
	"lp4_ca_odt",
	"lp4_drv_pu_cal_odten",
	"lp4_drv_pu_cal_odtoff",
	"phy_lp4_drv_pulldown_en_odten",
	"phy_lp4_drv_pulldown_en_odtoff",
	/* odt enable freq */
	"lp4_ca_odt_en_freq",
	/* lp4 cs drv info and ca odt info */
	"phy_lp4_cs_drv_odten",
	"phy_lp4_cs_drv_odtoff",
	"lp4_odte_ck_en",
	"lp4_odte_cs_en",
	"lp4_odtd_ca_en",
	/* lp4 vref info when odt enable */
	"phy_lp4_dq_vref_odten",
	"lp4_dq_vref_odten",
	"lp4_ca_vref_odten",
	/* lp4 vref info when odt disable */
	"phy_lp4_dq_vref_odtoff",
	"lp4_dq_vref_odtoff",
	"lp4_ca_vref_odtoff",
	/* if need, add parameter after and change the minor version. */
};

/* the version V1.01 will add skew info */
static char *rk3326_dts_de_skew[] = {
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

static int get_atf_version(void)
{
	struct arm_smccc_res res;

	res = sip_smc_dram(0, 0, ROCKCHIP_SIP_CONFIG_DRAM_GET_VERSION);

	if (res.a0)
		return -ENOMEM;
	else
		return res.a1;
}

static int dmc_fsp_probe(struct udevice *dev)
{
	struct device_node *np_params, *np_tim;
	struct arm_smccc_res res;
	void *pmugrf_base;
	int *p = NULL;
	char *phandle_name = NULL;
	char **ddr_params;
	int ddr_params_version;
	u32 dram_type, os_reg2_val, os_reg3_val;
	u32 i = 0, count = 0, size = 0;
	u32 phy_de_skew_en;
	ulong atf_version_limit;

	atf_version_limit = dev_get_driver_data(dev);
	if (get_atf_version() < atf_version_limit) {
		printf("%s: trusted firmware need to update or is invalid!\n", __func__);
		printf("%s: current ATF version 0x%x, required version 0x%lx\n",
		       __func__, get_atf_version(), atf_version_limit);
		return 0;
	}

	pmugrf_base = syscon_get_first_range(ROCKCHIP_SYSCON_PMUGRF);
	os_reg2_val = readl(pmugrf_base + PMUGRF_OS_REG(2));
	os_reg3_val = readl(pmugrf_base + PMUGRF_OS_REG(3));
	dram_type = SYS_REG_DEC_DDRTYPE_V3(os_reg2_val, os_reg3_val);

	if (dram_type == DDR2)
		phandle_name = DDR2_PARAMS_PHANDLE_NAME;
	else if (dram_type == DDR3)
		phandle_name = DDR3_PARAMS_PHANDLE_NAME;
	else if (dram_type == DDR4)
		phandle_name = DDR4_PARAMS_PHANDLE_NAME;
	else if (dram_type == LPDDR2)
		phandle_name = LPDDR2_PARAMS_PHANDLE_NAME;
	else if (dram_type == LPDDR3)
		phandle_name = LPDDR3_PARAMS_PHANDLE_NAME;
	else if (dram_type == LPDDR4)
		phandle_name = LPDDR4_PARAMS_PHANDLE_NAME;
	else if (dram_type == LPDDR4X)
		phandle_name = LPDDR4X_PARAMS_PHANDLE_NAME;
	else if (dram_type == LPDDR5)
		phandle_name = LPDDR5_PARAMS_PHANDLE_NAME;
	else
		printf("%s: dram_type unsupported\n", __func__);

	np_params = of_parse_phandle(ofnode_to_np(dev_ofnode(dev)), phandle_name, 0);
	if (!np_params) {
		printf("%s: of_parse_phandle %s error!\n", __func__, phandle_name);
		return -EINVAL;
	}

	ddr_params_version = ofnode_read_u32_default(np_to_ofnode(np_params), "version", -1);
	if (ddr_params_version < 0) {
		printf("%s: get ddr_params_version error\n", __func__);
		return -EINVAL;
	}

	if ((ddr_params_version & 0xff00) == 0x100 &&
	    (ddr_params_version & 0xffff) <= 0x100) {
		count = ARRAY_SIZE(ddr_params_v1);
		ddr_params = ddr_params_v1;
	} else if ((ddr_params_version & 0xff00) == 0x100 &&
		   (ddr_params_version & 0xffff) <= 0x101) {
		count = ARRAY_SIZE(ddr_params_v1) + ARRAY_SIZE(rk3326_dts_de_skew);
		ddr_params = ddr_params_v1;
	} else {
		printf("%s: ddr_params_version=0x%x unsupported\n", __func__, ddr_params_version);
		return -EINVAL;
	}
	/*
	 * page 0 is used for share param
	 * page 1~N is uesd for dmc_fsp param
	 * page N + 1 is uesd for de-skew param
	 */
	size = count * 4 + 4096;
	res = sip_smc_request_share_mem(DIV_ROUND_UP(size, 4096) + 1, SHARE_PAGE_TYPE_DDRFSP);
	if (res.a0 != 0) {
		printf("%s:no share memory for init\n", __func__);
		return -ENOMEM;
	}

	/* fill share memory and pass to the atf */
	p = (int *)(res.a1);
	for (i = 0; i < ARRAY_SIZE(dmc_fsp_params); i++)
		p[i] = dev_read_u32_default(dev, dmc_fsp_params[i], PARAMS_INVALID_VAL);

	phy_de_skew_en = p[1];

	p = (int *)(res.a1 + DTS_PAR_OFFSET / 4);
	for (i = 0; i < ARRAY_SIZE(ddr_params_v1); i++) {
		p[i] = ofnode_read_u32_default(np_to_ofnode(np_params), ddr_params[i],
					       PARAMS_INVALID_VAL);
	}
	if (phy_de_skew_en) {
		phandle_name = "ddr_timing";
		np_tim = of_parse_phandle(ofnode_to_np(dev_ofnode(dev)), phandle_name, 0);
		if (!np_tim) {
			printf("%s: of_parse_phandle %s error!\n", __func__, phandle_name);
			return -EINVAL;
		}
		for (i = ARRAY_SIZE(ddr_params_v1); i < count; i++) {
			p[i] = ofnode_read_u32_default(np_to_ofnode(np_tim), rk3326_dts_de_skew[i - ARRAY_SIZE(ddr_params_v1)],
						       PARAMS_INVALID_VAL);
		}
	}

	flush_cache((unsigned long)(res.a1), (DIV_ROUND_UP(size, 4096) + 1) * 0x1000);
	res = sip_smc_dram(SHARE_PAGE_TYPE_DDRFSP, 0, ROCKCHIP_SIP_CONFIG_DRAM_FSP_INIT);
	if (res.a0) {
		printf("%s: rockchip_sip_config_dram_fsp_init error:%lx\n", __func__, res.a0);
		return -ENOMEM;
	}

	return 0;
}

static const struct udevice_id rockchip_dmc_fsp_ids[] = {
	{ .compatible = "rockchip,rk3568-dmc-fsp", .data = 0x102},
	{ .compatible = "rockchip,px30s-dmc-fsp", .data = 0x106},
	{ }
};

U_BOOT_DRIVER(dmc_fsp) = {
	.name = "rockchip_dmc_fsp",
	.id = UCLASS_DMC,
	.probe = dmc_fsp_probe,
	.of_match = rockchip_dmc_fsp_ids,
};
