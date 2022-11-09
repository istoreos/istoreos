/* SPDX-License-Identifier:     GPL-2.0+ */
/*
 * Copyright (C) 2020 Rockchip Electronics Co., Ltd
 */

#ifndef __ROCKCHIP_DRAM_SPEC_TIMING_H__
#define __ROCKCHIP_DRAM_SPEC_TIMING_H__

enum ddr3_speed_rate {
	/* 5-5-5 */
	DDR3_800D = 0,
	/* 6-6-6 */
	DDR3_800E = 1,
	/* 6-6-6 */
	DDR3_1066E = 2,
	/* 7-7-7 */
	DDR3_1066F = 3,
	/* 8-8-8 */
	DDR3_1066G = 4,
	/* 7-7-7 */
	DDR3_1333F = 5,
	/* 8-8-8 */
	DDR3_1333G = 6,
	/* 9-9-9 */
	DDR3_1333H = 7,
	/* 10-10-10 */
	DDR3_1333J = 8,
	/* 8-8-8 */
	DDR3_1600G = 9,
	/* 9-9-9 */
	DDR3_1600H = 10,
	/* 10-10-10 */
	DDR3_1600J = 11,
	/* 11-11-11 */
	DDR3_1600K = 12,
	/* 10-10-10 */
	DDR3_1866J = 13,
	/* 11-11-11 */
	DDR3_1866K = 14,
	/* 12-12-12 */
	DDR3_1866L = 15,
	/* 13-13-13 */
	DDR3_1866M = 16,
	/* 11-11-11 */
	DDR3_2133K = 17,
	/* 12-12-12 */
	DDR3_2133L = 18,
	/* 13-13-13 */
	DDR3_2133M = 19,
	/* 14-14-14 */
	DDR3_2133N = 20,
	DDR3_DEFAULT = 21,
};

enum ddr4_speed_rate {
	/* DDR4_1600J (10-10-10) */
	DDR4_1600J = 0,
	/* DDR4_1600K (11-11-11) */
	DDR4_1600K = 1,
	/* DDR4_1600L (12-12-12) */
	DDR4_1600L = 2,
	/* DDR4_1800L (12-12-12) */
	DDR4_1866L = 3,
	/* DDR4_1800M (13-13-13) */
	DDR4_1866M = 4,
	/* DDR4_1800N (14-14-14) */
	DDR4_1866N = 5,
	/* DDR4_2133N (14-14-14) */
	DDR4_2133N = 6,
	/* DDR4_2133P (15-15-15) */
	DDR4_2133P = 7,
	/* DDR4_2133R (16-16-16) */
	DDR4_2133R = 8,
	/* DDR4_2400P (15-15-15) */
	DDR4_2400P = 9,
	/* DDR4_2400R (16-16-16) */
	DDR4_2400R = 10,
	/* DDR4_2400U (18-18-18) */
	DDR4_2400U = 11,
	/* DEFAULT */
	DDR4_DEFAULT = 12,
};

/* mr0 for ddr3 */
#define DDR3_BL8		(0)
#define DDR3_BC4_8		(1)
#define DDR3_BC4		(2)
#define DDR3_CL(n)		(((((n) - 4) & 0x7) << 4)\
				| ((((n) - 4) & 0x8) >> 1))
#define DDR3_WR(n)		(((n) & 0x7) << 9)
#define DDR3_DLL_RESET		(1 << 8)
#define DDR3_DLL_DERESET	(0 << 8)

/* mr1 for ddr3 */
#define DDR3_DLL_ENABLE		(0)
#define DDR3_DLL_DISABLE	(1)
#define DDR3_MR1_AL(n)		(((n) & 0x3) << 3)

#define DDR3_DS_40		(0)
#define DDR3_DS_34		BIT(1)
#define DDR3_DS_MASK		((1 << 1) | (1 << 5))
#define DDR3_RTT_NOM_MASK	((1 << 2) | (1 << 6) | (1 << 9))
#define DDR3_RTT_NOM_DIS	(0)
#define DDR3_RTT_NOM_60		BIT(2)
#define DDR3_RTT_NOM_120	BIT(6)
#define DDR3_RTT_NOM_40		((1 << 2) | (1 << 6))
#define DDR3_TDQS		BIT(11)

/* mr2 for ddr3 */
#define DDR3_MR2_CWL(n)		((((n) - 5) & 0x7) << 3)
#define DDR3_RTT_WR_DIS		(0)
#define DDR3_RTT_WR_60		(1 << 9)
#define DDR3_RTT_WR_120		(2 << 9)

/*
 * MR0 (Device Information)
 * 0:DAI complete, 1:DAI still in progress
 */
#define LPDDR2_DAI		(0x1)
/* 0:S2 or S4 SDRAM, 1:NVM */
#define LPDDR2_DI		(0x1 << 1)
/* 0:DNV not supported, 1:DNV supported */
#define LPDDR2_DNVI		(0x1 << 2)
#define LPDDR2_RZQI		(0x3 << 3)

/*
 * 00:RZQ self test not supported,
 * 01:ZQ-pin may connect to VDDCA or float
 * 10:ZQ-pin may short to GND.
 * 11:ZQ-pin self test completed, no error condition detected.
 */

/* MR1 (Device Feature) */
#define LPDDR2_BL4		(0x2)
#define LPDDR2_BL8		(0x3)
#define LPDDR2_BL16		(0x4)
#define LPDDR2_N_WR(n)		(((n) - 2) << 5)

/* MR2 (Device Feature 2) */
#define LPDDR2_RL3_WL1		(0x1)
#define LPDDR2_RL4_WL2		(0x2)
#define LPDDR2_RL5_WL2		(0x3)
#define LPDDR2_RL6_WL3		(0x4)
#define LPDDR2_RL7_WL4		(0x5)
#define LPDDR2_RL8_WL4		(0x6)

/* MR3 (IO Configuration 1) */
#define LPDDR2_DS_34		(0x1)
#define LPDDR2_DS_40		(0x2)
#define LPDDR2_DS_48		(0x3)
#define LPDDR2_DS_60		(0x4)
#define LPDDR2_DS_80		(0x6)
/* optional */
#define LPDDR2_DS_120		(0x7)

/* MR4 (Device Temperature) */
#define LPDDR2_TREF_MASK	(0x7)
#define LPDDR2_4_TREF		(0x1)
#define LPDDR2_2_TREF		(0x2)
#define LPDDR2_1_TREF		(0x3)
#define LPDDR2_025_TREF		(0x5)
#define LPDDR2_025_TREF_DERATE	(0x6)

#define LPDDR2_TUF		(0x1 << 7)

/* MR8 (Basic configuration 4) */
#define LPDDR2_S4		(0x0)
#define LPDDR2_S2		(0x1)
#define LPDDR2_N		(0x2)
/* Unit:MB */
#define LPDDR2_DENSITY(mr8)	(8 << (((mr8) >> 2) & 0xf))
#define LPDDR2_IO_WIDTH(mr8)	(32 >> (((mr8) >> 6) & 0x3))

/* MR10 (Calibration) */
#define LPDDR2_ZQINIT		(0xff)
#define LPDDR2_ZQCL		(0xab)
#define LPDDR2_ZQCS		(0x56)
#define LPDDR2_ZQRESET		(0xc3)

/* MR16 (PASR Bank Mask), S2 SDRAM Only */
#define LPDDR2_PASR_FULL	(0x0)
#define LPDDR2_PASR_1_2		(0x1)
#define LPDDR2_PASR_1_4		(0x2)
#define LPDDR2_PASR_1_8		(0x3)

/*
 * MR0 (Device Information)
 * 0:DAI complete,
 * 1:DAI still in progress
 */
#define LPDDR3_DAI		(0x1)
/*
 * 00:RZQ self test not supported,
 * 01:ZQ-pin may connect to VDDCA or float
 * 10:ZQ-pin may short to GND.
 * 11:ZQ-pin self test completed, no error condition detected.
 */
#define LPDDR3_RZQI		(0x3 << 3)
/*
 * 0:DRAM does not support WL(Set B),
 * 1:DRAM support WL(Set B)
 */
#define LPDDR3_WL_SUPOT		BIT(6)
/*
 * 0:DRAM does not support RL=3,nWR=3,WL=1;
 * 1:DRAM supports RL=3,nWR=3,WL=1 for frequencies <=166
 */
#define LPDDR3_RL3_SUPOT	BIT(7)

/* MR1 (Device Feature) */
#define LPDDR3_BL8		(0x3)
#define LPDDR3_N_WR(n)		((n) << 5)

/* MR2 (Device Feature 2), WL Set A,default */
/* <=166MHz,optional*/
#define LPDDR3_RL3_WL1		(0x1)
/* <=400MHz*/
#define LPDDR3_RL6_WL3		(0x4)
/* <=533MHz*/
#define LPDDR3_RL8_WL4		(0x6)
/* <=600MHz*/
#define LPDDR3_RL9_WL5		(0x7)
/* <=667MHz,default*/
#define LPDDR3_RL10_WL6		(0x8)
/* <=733MHz*/
#define LPDDR3_RL11_WL6		(0x9)
/* <=800MHz*/
#define LPDDR3_RL12_WL6		(0xa)
/* <=933MHz*/
#define LPDDR3_RL14_WL8		(0xc)
/* <=1066MHz*/
#define LPDDR3_RL16_WL8		(0xe)

/* WL Set B, optional */
/* <=667MHz,default*/
#define LPDDR3_RL10_WL8		(0x8)
/* <=733MHz*/
#define LPDDR3_RL11_WL9		(0x9)
/* <=800MHz*/
#define LPDDR3_RL12_WL9		(0xa)
/* <=933MHz*/
#define LPDDR3_RL14_WL11	(0xc)
/* <=1066MHz*/
#define LPDDR3_RL16_WL13	(0xe)

/* 1:enable nWR programming > 9(default)*/
#define LPDDR3_N_WRE		BIT(4)
/* 1:Select WL Set B*/
#define LPDDR3_WL_S		BIT(6)
/* 1:enable*/
#define LPDDR3_WR_LEVEL		BIT(7)

/* MR3 (IO Configuration 1) */
#define LPDDR3_DS_34		(0x1)
#define LPDDR3_DS_40		(0x2)
#define LPDDR3_DS_48		(0x3)
#define LPDDR3_DS_60		(0x4)
#define LPDDR3_DS_80		(0x6)
#define LPDDR3_DS_34D_40U	(0x9)
#define LPDDR3_DS_40D_48U	(0xa)
#define LPDDR3_DS_34D_48U	(0xb)

/* MR4 (Device Temperature) */
#define LPDDR3_TREF_MASK	(0x7)
/* SDRAM Low temperature operating limit exceeded */
#define LPDDR3_LT_EXED		(0x0)
#define LPDDR3_4_TREF		(0x1)
#define LPDDR3_2_TREF		(0x2)
#define LPDDR3_1_TREF		(0x3)
#define LPDDR3_05_TREF		(0x4)
#define LPDDR3_025_TREF		(0x5)
#define LPDDR3_025_TREF_DERATE	(0x6)
/* SDRAM High temperature operating limit exceeded */
#define LPDDR3_HT_EXED		(0x7)

/* 1:value has changed since last read of MR4 */
#define LPDDR3_TUF		(0x1 << 7)

/* MR8 (Basic configuration 4) */
#define LPDDR3_S8		(0x3)
#define LPDDR3_DENSITY(mr8)	(8 << (((mr8) >> 2) & 0xf))
#define LPDDR3_IO_WIDTH(mr8)	(32 >> (((mr8) >> 6) & 0x3))

/* MR10 (Calibration) */
#define LPDDR3_ZQINIT		(0xff)
#define LPDDR3_ZQCL		(0xab)
#define LPDDR3_ZQCS		(0x56)
#define LPDDR3_ZQRESET		(0xc3)

/* MR11 (ODT Control) */
#define LPDDR3_ODT_60		(1)
#define LPDDR3_ODT_120		(2)
#define LPDDR3_ODT_240		(3)
#define LPDDR3_ODT_DIS		(0)

/* MR2 (Device Feature 2) */
/* RL & nRTP for DBI-RD Disabled */
#define LPDDR4_RL6_NRTP8	(0x0)
#define LPDDR4_RL10_NRTP8	(0x1)
#define LPDDR4_RL14_NRTP8	(0x2)
#define LPDDR4_RL20_NRTP8	(0x3)
#define LPDDR4_RL24_NRTP10	(0x4)
#define LPDDR4_RL28_NRTP12	(0x5)
#define LPDDR4_RL32_NRTP14	(0x6)
#define LPDDR4_RL36_NRTP16	(0x7)
/* RL & nRTP for DBI-RD Disabled */
#define LPDDR4_RL12_NRTP8	(0x1)
#define LPDDR4_RL16_NRTP8	(0x2)
#define LPDDR4_RL22_NRTP8	(0x3)
#define LPDDR4_RL28_NRTP10	(0x4)
#define LPDDR4_RL32_NRTP12	(0x5)
#define LPDDR4_RL36_NRTP14	(0x6)
#define LPDDR4_RL40_NRTP16	(0x7)
/* WL Set A,default */
#define LPDDR4_A_WL4		(0x0 << 3)
#define LPDDR4_A_WL6		(0x1 << 3)
#define LPDDR4_A_WL8		(0x2 << 3)
#define LPDDR4_A_WL10		(0x3 << 3)
#define LPDDR4_A_WL12		(0x4 << 3)
#define LPDDR4_A_WL14		(0x5 << 3)
#define LPDDR4_A_WL16		(0x6 << 3)
#define LPDDR4_A_WL18		(0x7 << 3)
/* WL Set B, optional */
#define LPDDR4_B_WL4		(0x0 << 3)
#define LPDDR4_B_WL8		(0x1 << 3)
#define LPDDR4_B_WL12		(0x2 << 3)
#define LPDDR4_B_WL18		(0x3 << 3)
#define LPDDR4_B_WL22		(0x4 << 3)
#define LPDDR4_B_WL26		(0x5 << 3)
#define LPDDR4_B_WL30		(0x6 << 3)
#define LPDDR4_B_WL34		(0x7 << 3)
/* 1:Select WL Set B*/
#define LPDDR4_WL_B		BIT(6)
/* 1:enable*/
#define LPDDR4_WR_LEVEL		BIT(7)

/* MR3 */
#define LPDDR4_VDDQ_2_5		(0)
#define LPDDR4_VDDQ_3		(1)
#define LPDDR4_PU_CAL_MASK	(1)
#define LPDDR4_WRPST_0_5_TCK	(0 << 1)
#define LPDDR4_WRPST_1_5_TCK	(1 << 1)
#define LPDDR4_PPR_EN		(1 << 2)
/* PDDS */
#define LPDDR4_PDDS_MASK	(0x7 << 3)
#define LPDDR4_PDDS_SHIFT	(3)
#define LPDDR4_PDDS_240		(0x1 << 3)
#define LPDDR4_PDDS_120		(0x2 << 3)
#define LPDDR4_PDDS_80		(0x3 << 3)
#define LPDDR4_PDDS_60		(0x4 << 3)
#define LPDDR4_PDDS_48		(0x5 << 3)
#define LPDDR4_PDDS_40		(0x6 << 3)
#define LPDDR4_DBI_RD_EN	BIT(6)
#define LPDDR4_DBI_WR_EN	BIT(7)

/* MR11 (ODT Control) */
#define LPDDR4_DQODT_MASK	(0x7)
#define LPDDR4_DQODT_SHIFT	(0x0)
#define LPDDR4_DQODT_240	(1)
#define LPDDR4_DQODT_120	(2)
#define LPDDR4_DQODT_80		(3)
#define LPDDR4_DQODT_60		(4)
#define LPDDR4_DQODT_48		(5)
#define LPDDR4_DQODT_40		(6)
#define LPDDR4_DQODT_DIS	(0)
#define LPDDR4_CAODT_MASK	(0x7 << 4)
#define LPDDR4_CAODT_SHIFT	(4)
#define LPDDR4_CAODT_240	(1 << 4)
#define LPDDR4_CAODT_120	(2 << 4)
#define LPDDR4_CAODT_80		(3 << 4)
#define LPDDR4_CAODT_60		(4 << 4)
#define LPDDR4_CAODT_48		(5 << 4)
#define LPDDR4_CAODT_40		(6 << 4)
#define LPDDR4_CAODT_DIS	(0 << 4)

/* MR22 */
#define LPDDR4_ODTE_CK_SHIFT	(3)
#define LPDDR4_ODTE_CS_SHIFT	(4)
#define LPDDR4_ODTD_CA_SHIFT	(5)
#define LPDDR4_SOC_ODT_MASK	(0x7)
#define LPDDR4_SOC_ODT_SHIFT	(0)
#define LPDDR4_SOC_ODT_240	(1)
#define LPDDR4_SOC_ODT_120	(2)
#define LPDDR4_SOC_ODT_80	(3)
#define LPDDR4_SOC_ODT_60	(4)
#define LPDDR4_SOC_ODT_48	(5)
#define LPDDR4_SOC_ODT_40	(6)
#define LPDDR4_SOC_ODT_DIS	(0)

/* LPDDR4x */
/* MR3 */
#define LPDDR4X_VDDQ_0_6	(0)
#define LPDDR4X_VDDQ_0_5	(1)

/* mr0 for ddr4 */
#define DDR4_BL8		(0)
#define DDR4_BC4_8		(1)
#define DDR4_BC4		(2)
#define DDR4_WR_RTP(n)		((n) << 9)
#define DDR4_CL(n)		((((n) & 0xe) << 3) | ((n) & 1) << 2)
#define DDR4_DLL_RESET(n)	((n) << 8)
#define DDR4_DLL_ON		BIT(0)
#define DDR4_DLL_OFF		(0 << 0)

/* mr1 for ddr4 */
#define DDR4_AL			((n) << 3)
#define DDR4_DS_34		(0)
#define DDR4_DS_48		BIT(1)
#define DDR4_DS_MASK		(0x3 << 1)
#define DDR4_RTT_NOM_MASK	(0x7 << 8)
#define DDR4_RTT_NOM_DIS	(0)
#define DDR4_RTT_NOM_60		BIT(8)
#define DDR4_RTT_NOM_120	(2 << 8)
#define DDR4_RTT_NOM_40		(0x3 << 8)
#define DDR4_RTT_NOM_240	(0x4 << 8)
#define DDR4_RTT_NOM_48		(0x5 << 8)
#define DDR4_RTT_NOM_80		(0x6 << 8)
#define DDR4_RTT_NOM_34		(0x7 << 8)

/* mr2 for ddr4 */
#define DDR4_MR2_CWL(n)		((n) << 3)
#define DDR4_RTT_WR_DIS		(0)
#define DDR4_RTT_WR_120		BIT(9)
#define DDR4_RTT_WR_240		(2 << 9)

/* mr4 for ddr4 */
#define DDR4_READ_PREAMBLE(n)	((n) << 11)
#define DDR4_WRITE_PREAMBLE(n)	((n) << 12)
#define DDR4_READ_PREAMBLE_TRAIN(n)	((n) << 10)

/* mr5 for ddr4 */
#define DDR4_RD_DBI(n)		((n) << 12)
#define DDR4_WR_DBI(n)		((n) << 11)
#define DDR4_DM(n)		((n) << 10)
#define DDR4_RTT_PARK_DIS	(0 << 6)
#define DDR4_RTT_PARK_60	(1 << 6)
#define DDR4_RTT_PARK_120	(2 << 6)
#define DDR4_RTT_PARK_40	(3 << 6)
#define DDR4_RTT_PARK_240	(4 << 6)
#define DDR4_RTT_PARK_48	(5 << 6)
#define DDR4_RTT_PARK_80	(6 << 6)
#define DDR4_RTT_PARK_34	(7 << 6)
#define DIS_ODT_PD		(1 << 5)
#define EN_ODT_PD		(0 << 5)

/* mr6 for ddr4 */
#define DDR4_TCCD_L(n)		(((n) - 4) << 10)

#define PS_2_CLK(freq, ps)	(((uint64_t)(ps) / 100 * (uint64_t)(freq) +\
				9999) / 10000)

#endif /* __ROCKCHIP_DRAM_SPEC_TIMING_H__ */
