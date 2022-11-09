/* SPDX-License-Identifier:     GPL-2.0+ */
/*
 * Copyright (C) 2018 Rockchip Electronics Co., Ltd
 */

#ifndef _ASM_ARCH_SDRAM_PHY_PX30_H
#define _ASM_ARCH_SDRAM_PHY_PX30_H
#include <asm/arch/sdram_common.h>
#include <asm/arch/sdram_phy_ron_rtt_px30.h>

struct ddr_phy_regs {
	u32 phy[5][2];
};

#define PHY_REG(base, n)		((base) + 4 * (n))

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
#define PHY_BL_4			(0 << 2)
#define PHY_BL_8			BIT(2)

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

struct ddr_phy_skew {
	u32 a0_a1_skew[15];
	u32 cs0_dm0_skew[11];
	u32 cs0_dm1_skew[11];
	u32 cs0_dm2_skew[11];
	u32 cs0_dm3_skew[11];
	u32 cs1_dm0_skew[11];
	u32 cs1_dm1_skew[11];
	u32 cs1_dm2_skew[11];
	u32 cs1_dm3_skew[11];
};

void phy_soft_reset(void __iomem *phy_base);
void phy_dram_set_bw(void __iomem *phy_base, u32 bw);
void phy_cfg(void __iomem *phy_base,
	     struct ddr_phy_regs *phy_regs, struct ddr_phy_skew *skew,
	     struct sdram_base_params *base, u32 bw);
int phy_data_training(void __iomem *phy_base, u32 cs, u32 dramtype);

#endif
