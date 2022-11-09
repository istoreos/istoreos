/* SPDX-License-Identifier:     GPL-2.0+ */
/*
 * Copyright (C) 2020 Rockchip Electronics Co., Ltd
 */

#ifndef _ASM_ARCH_SDRAM_RK1126_H
#define _ASM_ARCH_SDRAM_RK1126_H

#include <asm/arch/dram_spec_timing.h>
#include <asm/arch/sdram.h>
#include <asm/arch/sdram_common.h>
#include <asm/arch/sdram_msch.h>
#include <asm/arch/sdram_pctl_px30.h>
#include <asm/arch/sdram_phy_rv1126.h>

#define AGINGX0_VAL			(4)
#define AGING_CPU_VAL			(0xff)
#define AGING_NPU_VAL			(0xff)
#define AGING_OTHER_VAL			(0x33)

#define PATTERN				(0x5aa5f00f)

#define PHY_DDR3_RON_DISABLE		(0)
#define PHY_DDR3_RON_455ohm		(1)
#define PHY_DDR3_RON_230ohm		(2)
#define PHY_DDR3_RON_153ohm		(3)
#define PHY_DDR3_RON_115ohm		(4)
#define PHY_DDR3_RON_91ohm		(5)
#define PHY_DDR3_RON_76ohm		(6)
#define PHY_DDR3_RON_65ohm		(7)
#define PHY_DDR3_RON_57ohm		(16)
#define PHY_DDR3_RON_51ohm		(17)
#define PHY_DDR3_RON_46ohm		(18)
#define PHY_DDR3_RON_41ohm		(19)
#define PHY_DDR3_RON_38ohm		(20)
#define PHY_DDR3_RON_35ohm		(21)
#define PHY_DDR3_RON_32ohm		(22)
#define PHY_DDR3_RON_30ohm		(23)
#define PHY_DDR3_RON_28ohm		(24)
#define PHY_DDR3_RON_27ohm		(25)
#define PHY_DDR3_RON_25ohm		(26)
#define PHY_DDR3_RON_24ohm		(27)
#define PHY_DDR3_RON_23ohm		(28)
#define PHY_DDR3_RON_22ohm		(29)
#define PHY_DDR3_RON_21ohm		(30)
#define PHY_DDR3_RON_20ohm		(31)

#define PHY_DDR3_RTT_DISABLE		(0)
#define PHY_DDR3_RTT_561ohm		(1)
#define PHY_DDR3_RTT_282ohm		(2)
#define PHY_DDR3_RTT_188ohm		(3)
#define PHY_DDR3_RTT_141ohm		(4)
#define PHY_DDR3_RTT_113ohm		(5)
#define PHY_DDR3_RTT_94ohm		(6)
#define PHY_DDR3_RTT_81ohm		(7)
#define PHY_DDR3_RTT_72ohm		(16)
#define PHY_DDR3_RTT_64ohm		(17)
#define PHY_DDR3_RTT_58ohm		(18)
#define PHY_DDR3_RTT_52ohm		(19)
#define PHY_DDR3_RTT_48ohm		(20)
#define PHY_DDR3_RTT_44ohm		(21)
#define PHY_DDR3_RTT_41ohm		(22)
#define PHY_DDR3_RTT_38ohm		(23)
#define PHY_DDR3_RTT_37ohm		(24)
#define PHY_DDR3_RTT_34ohm		(25)
#define PHY_DDR3_RTT_32ohm		(26)
#define PHY_DDR3_RTT_31ohm		(27)
#define PHY_DDR3_RTT_29ohm		(28)
#define PHY_DDR3_RTT_28ohm		(29)
#define PHY_DDR3_RTT_27ohm		(30)
#define PHY_DDR3_RTT_25ohm		(31)

#define PHY_DDR4_LPDDR3_RON_DISABLE	(0)
#define PHY_DDR4_LPDDR3_RON_482ohm	(1)
#define PHY_DDR4_LPDDR3_RON_244ohm	(2)
#define PHY_DDR4_LPDDR3_RON_162ohm	(3)
#define PHY_DDR4_LPDDR3_RON_122ohm	(4)
#define PHY_DDR4_LPDDR3_RON_97ohm	(5)
#define PHY_DDR4_LPDDR3_RON_81ohm	(6)
#define PHY_DDR4_LPDDR3_RON_69ohm	(7)
#define PHY_DDR4_LPDDR3_RON_61ohm	(16)
#define PHY_DDR4_LPDDR3_RON_54ohm	(17)
#define PHY_DDR4_LPDDR3_RON_48ohm	(18)
#define PHY_DDR4_LPDDR3_RON_44ohm	(19)
#define PHY_DDR4_LPDDR3_RON_40ohm	(20)
#define PHY_DDR4_LPDDR3_RON_37ohm	(21)
#define PHY_DDR4_LPDDR3_RON_34ohm	(22)
#define PHY_DDR4_LPDDR3_RON_32ohm	(23)
#define PHY_DDR4_LPDDR3_RON_30ohm	(24)
#define PHY_DDR4_LPDDR3_RON_28ohm	(25)
#define PHY_DDR4_LPDDR3_RON_27ohm	(26)
#define PHY_DDR4_LPDDR3_RON_25ohm	(27)
#define PHY_DDR4_LPDDR3_RON_24ohm	(28)
#define PHY_DDR4_LPDDR3_RON_23ohm	(29)
#define PHY_DDR4_LPDDR3_RON_22ohm	(30)
#define PHY_DDR4_LPDDR3_RON_21ohm	(31)

#define PHY_DDR4_LPDDR3_RTT_DISABLE	(0)
#define PHY_DDR4_LPDDR3_RTT_586ohm	(1)
#define PHY_DDR4_LPDDR3_RTT_294ohm	(2)
#define PHY_DDR4_LPDDR3_RTT_196ohm	(3)
#define PHY_DDR4_LPDDR3_RTT_148ohm	(4)
#define PHY_DDR4_LPDDR3_RTT_118ohm	(5)
#define PHY_DDR4_LPDDR3_RTT_99ohm	(6)
#define PHY_DDR4_LPDDR3_RTT_85ohm	(7)
#define PHY_DDR4_LPDDR3_RTT_76ohm	(16)
#define PHY_DDR4_LPDDR3_RTT_67ohm	(17)
#define PHY_DDR4_LPDDR3_RTT_60ohm	(18)
#define PHY_DDR4_LPDDR3_RTT_55ohm	(19)
#define PHY_DDR4_LPDDR3_RTT_50ohm	(20)
#define PHY_DDR4_LPDDR3_RTT_46ohm	(21)
#define PHY_DDR4_LPDDR3_RTT_43ohm	(22)
#define PHY_DDR4_LPDDR3_RTT_40ohm	(23)
#define PHY_DDR4_LPDDR3_RTT_38ohm	(24)
#define PHY_DDR4_LPDDR3_RTT_36ohm	(25)
#define PHY_DDR4_LPDDR3_RTT_34ohm	(26)
#define PHY_DDR4_LPDDR3_RTT_32ohm	(27)
#define PHY_DDR4_LPDDR3_RTT_31ohm	(28)
#define PHY_DDR4_LPDDR3_RTT_29ohm	(29)
#define PHY_DDR4_LPDDR3_RTT_28ohm	(30)
#define PHY_DDR4_LPDDR3_RTT_27ohm	(31)

#define PHY_LPDDR4_RON_DISABLE		(0)
#define PHY_LPDDR4_RON_501ohm		(1)
#define PHY_LPDDR4_RON_253ohm		(2)
#define PHY_LPDDR4_RON_168ohm		(3)
#define PHY_LPDDR4_RON_126ohm		(4)
#define PHY_LPDDR4_RON_101ohm		(5)
#define PHY_LPDDR4_RON_84ohm		(6)
#define PHY_LPDDR4_RON_72ohm		(7)
#define PHY_LPDDR4_RON_63ohm		(16)
#define PHY_LPDDR4_RON_56ohm		(17)
#define PHY_LPDDR4_RON_50ohm		(18)
#define PHY_LPDDR4_RON_46ohm		(19)
#define PHY_LPDDR4_RON_42ohm		(20)
#define PHY_LPDDR4_RON_38ohm		(21)
#define PHY_LPDDR4_RON_36ohm		(22)
#define PHY_LPDDR4_RON_33ohm		(23)
#define PHY_LPDDR4_RON_31ohm		(24)
#define PHY_LPDDR4_RON_29ohm		(25)
#define PHY_LPDDR4_RON_28ohm		(26)
#define PHY_LPDDR4_RON_26ohm		(27)
#define PHY_LPDDR4_RON_25ohm		(28)
#define PHY_LPDDR4_RON_24ohm		(29)
#define PHY_LPDDR4_RON_23ohm		(30)
#define PHY_LPDDR4_RON_22ohm		(31)

#define PHY_LPDDR4_RTT_DISABLE		(0)
#define PHY_LPDDR4_RTT_604ohm		(1)
#define PHY_LPDDR4_RTT_303ohm		(2)
#define PHY_LPDDR4_RTT_202ohm		(3)
#define PHY_LPDDR4_RTT_152ohm		(4)
#define PHY_LPDDR4_RTT_122ohm		(5)
#define PHY_LPDDR4_RTT_101ohm		(6)
#define PHY_LPDDR4_RTT_87ohm		(7)
#define PHY_LPDDR4_RTT_78ohm		(16)
#define PHY_LPDDR4_RTT_69ohm		(17)
#define PHY_LPDDR4_RTT_62ohm		(18)
#define PHY_LPDDR4_RTT_56ohm		(19)
#define PHY_LPDDR4_RTT_52ohm		(20)
#define PHY_LPDDR4_RTT_48ohm		(21)
#define PHY_LPDDR4_RTT_44ohm		(22)
#define PHY_LPDDR4_RTT_41ohm		(23)
#define PHY_LPDDR4_RTT_39ohm		(24)
#define PHY_LPDDR4_RTT_37ohm		(25)
#define PHY_LPDDR4_RTT_35ohm		(26)
#define PHY_LPDDR4_RTT_33ohm		(27)
#define PHY_LPDDR4_RTT_32ohm		(28)
#define PHY_LPDDR4_RTT_30ohm		(29)
#define PHY_LPDDR4_RTT_29ohm		(30)
#define PHY_LPDDR4_RTT_27ohm		(31)

#define ADD_CMD_CA			(0x150)
#define ADD_GROUP_CS0_A			(0x170)
#define ADD_GROUP_CS0_B			(0x1d0)
#define ADD_GROUP_CS1_A			(0x1a0)
#define ADD_GROUP_CS1_B			(0x200)

/* PMUGRF */
#define PMUGRF_OS_REG0			(0x200)
#define PMUGRF_OS_REG(n)		(PMUGRF_OS_REG0 + (n) * 4)
#define PMUGRF_CON_DDRPHY_BUFFEREN_MASK		(0x3 << (12 + 16))
#define PMUGRF_CON_DDRPHY_BUFFEREN_EN		(0x1 << 12)
#define PMUGRF_CON_DDRPHY_BUFFEREN_DIS	(0x2 << 12)

/* DDR GRF */
#define DDR_GRF_CON(n)			(0 + (n) * 4)
#define DDR_GRF_STATUS_BASE		(0X100)
#define DDR_GRF_STATUS(n)		(DDR_GRF_STATUS_BASE + (n) * 4)
#define DDR_GRF_LP_CON			(0x20)

#define SPLIT_MODE_32_L16_VALID		(0)
#define SPLIT_MODE_32_H16_VALID		(1)
#define SPLIT_MODE_16_L8_VALID		(2)
#define SPLIT_MODE_16_H8_VALID		(3)

#define DDR_GRF_SPLIT_CON		(0x10)
#define SPLIT_MODE_MASK			(0x3)
#define SPLIT_MODE_OFFSET		(9)
#define SPLIT_BYPASS_MASK		(1)
#define SPLIT_BYPASS_OFFSET		(8)
#define SPLIT_SIZE_MASK			(0xff)
#define SPLIT_SIZE_OFFSET		(0)

/* SGRF SOC_CON13 */
#define UPCTL2_ASRSTN_REQ(n)		(((0x1 << 0) << 16) | ((n) << 0))
#define UPCTL2_PSRSTN_REQ(n)		(((0x1 << 1) << 16) | ((n) << 1))
#define UPCTL2_SRSTN_REQ(n)		(((0x1 << 2) << 16) | ((n) << 2))

/* CRU define */
/* CRU_PLL_CON0 */
#define PB(n)				((0x1 << (15 + 16)) | ((n) << 15))
#define POSTDIV1(n)			((0x7 << (12 + 16)) | ((n) << 12))
#define FBDIV(n)			((0xFFF << 16) | (n))

/* CRU_PLL_CON1 */
#define RSTMODE(n)			((0x1 << (15 + 16)) | ((n) << 15))
#define RST(n)				((0x1 << (14 + 16)) | ((n) << 14))
#define PD(n)				((0x1 << (13 + 16)) | ((n) << 13))
#define DSMPD(n)			((0x1 << (12 + 16)) | ((n) << 12))
#define LOCK(n)				(((n) >> 10) & 0x1)
#define POSTDIV2(n)			((0x7 << (6 + 16)) | ((n) << 6))
#define REFDIV(n)			((0x3F << 16) | (n))

/* CRU_PLL_CON3 */
#define SSMOD_SPREAD(n)			((0x1f << (8 + 16)) | ((n) << 8))
#define SSMOD_DIVVAL(n)			((0xf << (4 + 16)) | ((n) << 4))
#define SSMOD_DOWNSPREAD(n)		((0x1 << (3 + 16)) | ((n) << 3))
#define SSMOD_RESET(n)			((0x1 << (2 + 16)) | ((n) << 2))
#define SSMOD_DIS_SSCG(n)		((0x1 << (1 + 16)) | ((n) << 1))
#define SSMOD_BP(n)			((0x1 << (0 + 16)) | ((n) << 0))

/* CRU_MODE */
#define CLOCK_FROM_XIN_OSC		(0)
#define CLOCK_FROM_PLL			(1)
#define CLOCK_FROM_RTC_32K		(2)
#define DPLL_MODE(n)			((0x3 << (2 + 16)) | ((n) << 2))

/* CRU_SOFTRESET_CON1 */
#define DDRPHY_PSRSTN_REQ(n)		(((0x1 << 14) << 16) | ((n) << 14))
#define DDRPHY_SRSTN_REQ(n)		(((0x1 << 15) << 16) | ((n) << 15))
/* CRU_CLKGATE_CON2 */
#define DDR_MSCH_EN_MASK		((0x1 << 10) << 16)
#define DDR_MSCH_EN_SHIFT		(10)

/* CRU register */
#define CRU_PLL_CON(pll_id, n)		((pll_id)  * 0x20 + (n) * 4)
#define CRU_MODE			(0xa0)
#define CRU_GLB_CNT_TH			(0xb0)
#define CRU_CLKSEL_CON_BASE		0x100
#define CRU_CLKSELS_CON(i)		(CRU_CLKSEL_CON_BASE + ((i) * 4))
#define CRU_CLKGATE_CON_BASE		0x230
#define CRU_CLKGATE_CON(i)		(CRU_CLKGATE_CON_BASE + ((i) * 4))
#define CRU_CLKSFTRST_CON_BASE		0x300
#define CRU_CLKSFTRST_CON(i)		(CRU_CLKSFTRST_CON_BASE + ((i) * 4))

/* SGRF_SOC_CON2 */
#define MSCH_AXI_BYPASS_ALL_MASK	(1)
#define MSCH_AXI_BYPASS_ALL_SHIFT	(15)

/* SGRF_SOC_CON12 */
#define CLK_DDR_UPCTL_EN_MASK		((0x1 << 2) << 16)
#define CLK_DDR_UPCTL_EN_SHIFT		(2)
#define ACLK_DDR_UPCTL_EN_MASK		((0x1 << 0) << 16)
#define ACLK_DDR_UPCTL_EN_SHIFT		(0)

/* DDRGRF DDR CON2 */
#define DFI_FREQ_CHANGE_ACK		BIT(10)
/* DDRGRF status8 */
#define DFI_FREQ_CHANGE_REQ		BIT(19)

struct rv1126_ddrgrf {
	u32 ddr_grf_con[4];
	u32 grf_ddrsplit_con;
	u32 reserved1[(0x20 - 0x10) / 4 - 1];
	u32 ddr_grf_lp_con;
	u32 reserved2[(0x40 - 0x20) / 4 - 1];
	u32 grf_ddrphy_con[6];
	u32 reserved3[(0x100 - 0x54) / 4 - 1];
	u32 ddr_grf_status[18];
	u32 reserved4[(0x150 - 0x144) / 4 - 1];
	u32 grf_ddrhold_status;
	u32 reserved5[(0x160 - 0x150) / 4 - 1];
	u32 grf_ddrphy_status[2];
};

struct rv1126_ddr_phy_regs {
	u32 phy[8][2];
};

struct msch_regs {
	u32 coreid;
	u32 revisionid;
	u32 deviceconf;
	u32 devicesize;
	u32 ddrtiminga0;
	u32 ddrtimingb0;
	u32 ddrtimingc0;
	u32 devtodev0;
	u32 reserved1[(0x110 - 0x20) / 4];
	u32 ddrmode;
	u32 ddr4timing;
	u32 reserved2[(0x1000 - 0x118) / 4];
	u32 agingx0;
	u32 reserved3[(0x1040 - 0x1004) / 4];
	u32 aging0;
	u32 aging1;
	u32 aging2;
	u32 aging3;
};

struct sdram_msch_timings {
	union noc_ddrtiminga0 ddrtiminga0;
	union noc_ddrtimingb0 ddrtimingb0;
	union noc_ddrtimingc0 ddrtimingc0;
	union noc_devtodev_rv1126 devtodev0;
	union noc_ddrmode ddrmode;
	union noc_ddr4timing ddr4timing;
	u32 agingx0;
	u32 aging0;
	u32 aging1;
	u32 aging2;
	u32 aging3;
};

struct rv1126_sdram_channel {
	struct sdram_cap_info cap_info;
	struct sdram_msch_timings noc_timings;
};

struct rv1126_sdram_params {
	struct rv1126_sdram_channel ch;
	struct sdram_base_params base;
	struct ddr_pctl_regs pctl_regs;
	struct rv1126_ddr_phy_regs phy_regs;
};

struct rv1126_fsp_param {
	u32 flag;
	u32 freq_mhz;

	/* dram size */
	u32 dq_odt;
	u32 ca_odt;
	u32 ds_pdds;
	u32 vref_ca[2];
	u32 vref_dq[2];

	/* phy side */
	u32 wr_dq_drv;
	u32 wr_ca_drv;
	u32 wr_ckcs_drv;
	u32 rd_odt;
	u32 rd_odt_up_en;
	u32 rd_odt_down_en;
	u32 vref_inner;
	u32 vref_out;
	u32 lp4_drv_pd_en;

	struct sdram_msch_timings noc_timings;
};

#define MAX_IDX			(4)
#define FSP_FLAG		(0xfead0001)
#define SHARE_MEM_BASE		(0x100000)
/*
 * Borrow share memory space to temporarily store FSP parame.
 * In the stage of DDR init write FSP parame to this space.
 * In the stage of trust init move FSP parame to SRAM space
 * from share memory space.
 */
#define FSP_PARAM_STORE_ADDR	(SHARE_MEM_BASE)

/* store result of read and write training, for ddr_dq_eye tool in u-boot */
#define RW_TRN_RESULT_ADDR	(0x2000000 + 0x8000)	/* 32M + 32k */
#define PRINT_STEP		1

#undef FSP_NUM
#undef CS_NUM
#undef BYTE_NUM

#define FSP_NUM			4
#define CS_NUM			2
#define BYTE_NUM		4
#define RD_DESKEW_NUM		64
#define WR_DESKEW_NUM		64

#define LP4_WIDTH_REF_MHZ_H	1056
#define LP4_RD_WIDTH_REF_H	12
#define LP4_WR_WIDTH_REF_H	13

#define LP4_WIDTH_REF_MHZ_L	924
#define LP4_RD_WIDTH_REF_L	15
#define LP4_WR_WIDTH_REF_L	15

#define DDR4_WIDTH_REF_MHZ_H	1056
#define DDR4_RD_WIDTH_REF_H	13
#define DDR4_WR_WIDTH_REF_H	9

#define DDR4_WIDTH_REF_MHZ_L	924
#define DDR4_RD_WIDTH_REF_L	15
#define DDR4_WR_WIDTH_REF_L	11

#define LP3_WIDTH_REF_MHZ_H	1056
#define LP3_RD_WIDTH_REF_H	15
#define LP3_WR_WIDTH_REF_H	13

#define LP3_WIDTH_REF_MHZ_L	924
#define LP3_RD_WIDTH_REF_L	16
#define LP3_WR_WIDTH_REF_L	15

#define DDR3_WIDTH_REF_MHZ_H	1056
#define DDR3_RD_WIDTH_REF_H	14
#define DDR3_WR_WIDTH_REF_H	14

#define DDR3_WIDTH_REF_MHZ_L	924
#define DDR3_RD_WIDTH_REF_L	17
#define DDR3_WR_WIDTH_REF_L	17

#endif /* _ASM_ARCH_SDRAM_RK1126_H */
