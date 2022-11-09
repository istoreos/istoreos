/* SPDX-License-Identifier:     GPL-2.0+ */
/*
 * Copyright (C) 2020 Rockchip Electronics Co., Ltd
 */

#ifndef _ASM_ARCH_SDRAM_RK1126_PHY_H
#define _ASM_ARCH_SDRAM_RK1126_PHY_H

/* PHY_REG0 */
#define DIGITAL_DERESET			BIT(3)
#define ANALOG_DERESET			BIT(2)
#define DIGITAL_RESET			(0 << 3)
#define ANALOG_RESET			(0 << 2)

/* PHY_REG1 */
#define PHY_DDR2			(0)
#define PHY_LPDDR2			(1)
#define PHY_DDR3			(2)
#define PHY_LPDDR3			(3)
#define PHY_DDR4			(4)
#define PHY_DDR5			(5)
#define PHY_BL_4			(0 << 3)
#define PHY_BL_8_OR_16			BIT(3)

/* PHY_REG2 */
#define PHY_DTT_EN			BIT(0)
#define PHY_DTT_DISB			(0 << 0)
#define PHY_WRITE_LEVELING_EN		BIT(2)
#define PHY_WRITE_LEVELING_DISB		(0 << 2)
#define PHY_SELECT_CS0			(2)
#define PHY_SELECT_CS1			(1)
#define PHY_SELECT_CS0_1		(0)
#define PHY_WRITE_LEVELING_SELECTCS(n)	((n) << 6)
#define PHY_DATA_TRAINING_SELECTCS(n)	((n) << 4)

/* PHY_REGf */
#define PHY_DQ_WIDTH_MASK		(0xf)

/* PHY_REG51 */
#define PHY_PBDIV_BIT9_MASK		BIT(0)
#define PHY_PBDIV_BIT9_SHIFT	(0)
#define PHY_POSTDIV_EN_MASK		BIT(7)
#define PHY_POSTDIV_EN_SHIFT	(7)

/* PHY_REG52 */
#define PHY_PREDIV_MASK			(0x1F)
#define PHY_PREDIV_SHIFT		(0)

/* PHY_REG53*/
#define PHY_POSTDIV_MASK		(0x7)
#define PHY_POSTDIV_SHIFT		(5)
#define PHY_PD_DISB			BIT(3)

/* PHY_REG90 */
#define PHY_PLL_LOCK			BIT(2)

struct ca_skew {
	u32 a0_a3_a3_cke1_a_de_skew;
	u32 a1_ba1_null_cke0_b_de_skew;
	u32 a2_a9_a9_a4_a_de_skew;
	u32 a3_a15_null_a5_b_de_skew;
	u32 a4_a6_a6_ck_a_de_skew;
	u32 a5_a12_null_odt0_b_de_skew;
	u32 a6_ba2_null_a0_a_de_skew;
	u32 a7_a4_a4_odt0_a_de_skew;
	u32 a8_a1_a1_cke0_a_de_skew;
	u32 a9_a5_a5_a5_a_de_skew;
	u32 a10_a8_a8_clkb_a_de_skew;
	u32 a11_a7_a7_ca2_a_de_skew;
	u32 a12_rasn_null_ca1_a_de_skew;
	u32 a13_a13_null_ca3_a_de_skew;
	u32 a14_a14_null_csb1_b_de_skew;
	u32 a15_a10_null_ca0_b_de_skew;
	u32 a16_a11_null_csb0_b_de_skew;
	u32 a17_null_null_null_de_skew;
	u32 ba0_csb1_csb1_csb0_a_de_skew;
	u32 ba1_wen_null_cke1_b_de_skew;
	u32 bg0_odt1_odt1_csb1_a_de_skew;
	u32 bg1_a2_a2_odt1_a_de_skew;
	u32 cke0_casb_null_ca1_b_de_skew;
	u32 ck_ck_ck_ck_b_de_skew;
	u32 ckb_ckb_ckb_ckb_b_de_skew;
	u32 csb0_odt0_odt0_ca2_b_de_skew;
	u32 odt0_csb0_csb0_ca4_b_de_skew;
	u32 resetn_resetn_null_resetn_de_skew;
	u32 actn_cke_cke_ca3_b_de_skew;
	u32 null_null_null_null_de_skew;
	u32 csb1_ba0_null_null_de_skew;
	u32 odt1_a0_a0_odt1_b_de_skew;
};

#define PHY_REG(base, n)		((base) + 4 * (n))
#endif /* _ASM_ARCH_SDRAM_RK1126_PHY_H */
