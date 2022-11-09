// SPDX-License-Identifier: GPL-2.0
/*
 * (C) Copyright 2018 Rockchip Electronics Co., Ltd.
 */

#include <common.h>
#include <ram.h>
#include <asm/io.h>
#include <asm/arch-rockchip/sdram.h>
#include <asm/arch-rockchip/sdram_common.h>
#include <asm/arch-rockchip/sdram_phy_px30.h>

static void sdram_phy_dll_bypass_set(void __iomem *phy_base, u32 freq)
{
	u32 tmp;
	u32 i, j;
	u32 dqs_dll_freq;

	setbits_le32(PHY_REG(phy_base, 0x13), 1 << 4);
	clrbits_le32(PHY_REG(phy_base, 0x14), 1 << 3);
	for (i = 0; i < 4; i++) {
		j = 0x26 + i * 0x10;
		setbits_le32(PHY_REG(phy_base, j), 1 << 4);
		clrbits_le32(PHY_REG(phy_base, j + 0x1), 1 << 3);
	}

	if (freq <= 400)
		/* DLL bypass */
		setbits_le32(PHY_REG(phy_base, 0xa4), 0x1f);
	else
		clrbits_le32(PHY_REG(phy_base, 0xa4), 0x1f);

	#ifdef CONFIG_ROCKCHIP_RK3328
	dqs_dll_freq = 680;
	#else
	dqs_dll_freq = 801;
	#endif

	if (freq <= dqs_dll_freq)
		tmp = 2;
	else
		tmp = 1;

	for (i = 0; i < 4; i++) {
		j = 0x28 + i * 0x10;
		writel(tmp, PHY_REG(phy_base, j));
	}
}

static void sdram_phy_set_ds_odt(void __iomem *phy_base,
				 u32 dram_type)
{
	u32 cmd_drv, clk_drv, dqs_drv, dqs_odt;
	u32 i, j;

	if (dram_type == DDR3) {
		cmd_drv = PHY_DDR3_RON_RTT_34ohm;
		clk_drv = PHY_DDR3_RON_RTT_45ohm;
		dqs_drv = PHY_DDR3_RON_RTT_34ohm;
		dqs_odt = PHY_DDR3_RON_RTT_225ohm;
	} else {
		cmd_drv = PHY_DDR4_LPDDR3_RON_RTT_34ohm;
		clk_drv = PHY_DDR4_LPDDR3_RON_RTT_43ohm;
		dqs_drv = PHY_DDR4_LPDDR3_RON_RTT_34ohm;
		if (dram_type == LPDDR2)
			dqs_odt = PHY_DDR4_LPDDR3_RON_RTT_DISABLE;
		else
			dqs_odt = PHY_DDR4_LPDDR3_RON_RTT_240ohm;
	}
	/* DS */
	writel(cmd_drv, PHY_REG(phy_base, 0x11));
	clrsetbits_le32(PHY_REG(phy_base, 0x12), 0x1f << 3, cmd_drv << 3);
	writel(clk_drv, PHY_REG(phy_base, 0x16));
	writel(clk_drv, PHY_REG(phy_base, 0x18));

	for (i = 0; i < 4; i++) {
		j = 0x20 + i * 0x10;
		writel(dqs_drv, PHY_REG(phy_base, j));
		writel(dqs_drv, PHY_REG(phy_base, j + 0xf));
		/* ODT */
		writel(dqs_odt, PHY_REG(phy_base, j + 0x1));
		writel(dqs_odt, PHY_REG(phy_base, j + 0xe));
	}
}

void phy_soft_reset(void __iomem *phy_base)
{
	clrbits_le32(PHY_REG(phy_base, 0), 0x3 << 2);
	udelay(1);
	setbits_le32(PHY_REG(phy_base, 0), ANALOG_DERESET);
	udelay(5);
	setbits_le32(PHY_REG(phy_base, 0), DIGITAL_DERESET);
	udelay(1);
}

void phy_dram_set_bw(void __iomem *phy_base, u32 bw)
{
	if (bw == 2) {
		clrsetbits_le32(PHY_REG(phy_base, 0), 0xf << 4, 0xf << 4);
		setbits_le32(PHY_REG(phy_base, 0x46), 1 << 3);
		setbits_le32(PHY_REG(phy_base, 0x56), 1 << 3);
	} else if (bw == 1) {
		clrsetbits_le32(PHY_REG(phy_base, 0), 0xf << 4, 3 << 4);
		clrbits_le32(PHY_REG(phy_base, 0x46), 1 << 3);
		clrbits_le32(PHY_REG(phy_base, 0x56), 1 << 3);
	} else if (bw == 0) {
		clrsetbits_le32(PHY_REG(phy_base, 0), 0xf << 4, 1 << 4);
		clrbits_le32(PHY_REG(phy_base, 0x36), 1 << 3);
		clrbits_le32(PHY_REG(phy_base, 0x46), 1 << 3);
		clrbits_le32(PHY_REG(phy_base, 0x56), 1 << 3);
	}

	phy_soft_reset(phy_base);
}

int phy_data_training(void __iomem *phy_base, u32 cs, u32 dramtype)
{
	u32 ret;
	u32 odt_val;
	u32 i, j;

	odt_val = readl(PHY_REG(phy_base, 0x2e));

	for (i = 0; i < 4; i++) {
		j = 0x20 + i * 0x10;
		writel(PHY_DDR3_RON_RTT_225ohm, PHY_REG(phy_base, j + 0x1));
		writel(0, PHY_REG(phy_base, j + 0xe));
	}

	if (dramtype == DDR4) {
		clrsetbits_le32(PHY_REG(phy_base, 0x29), 0x3, 0);
		clrsetbits_le32(PHY_REG(phy_base, 0x39), 0x3, 0);
		clrsetbits_le32(PHY_REG(phy_base, 0x49), 0x3, 0);
		clrsetbits_le32(PHY_REG(phy_base, 0x59), 0x3, 0);
	}
	/* choose training cs */
	clrsetbits_le32(PHY_REG(phy_base, 2), 0x33, (0x20 >> cs));
	/* enable gate training */
	clrsetbits_le32(PHY_REG(phy_base, 2), 0x33, (0x20 >> cs) | 1);
	udelay(50);
	ret = readl(PHY_REG(phy_base, 0xff));
	/* disable gate training */
	clrsetbits_le32(PHY_REG(phy_base, 2), 0x33, (0x20 >> cs) | 0);
	#ifndef CONFIG_ROCKCHIP_RK3328
	clrbits_le32(PHY_REG(phy_base, 2), 0x30);
	#endif

	if (dramtype == DDR4) {
		clrsetbits_le32(PHY_REG(phy_base, 0x29), 0x3, 0x2);
		clrsetbits_le32(PHY_REG(phy_base, 0x39), 0x3, 0x2);
		clrsetbits_le32(PHY_REG(phy_base, 0x49), 0x3, 0x2);
		clrsetbits_le32(PHY_REG(phy_base, 0x59), 0x3, 0x2);
	}

	if (ret & 0x10) {
		ret = -1;
	} else {
		ret = (ret & 0xf) ^ (readl(PHY_REG(phy_base, 0)) >> 4);
		ret = (ret == 0) ? 0 : -1;
	}

	for (i = 0; i < 4; i++) {
		j = 0x20 + i * 0x10;
		writel(odt_val, PHY_REG(phy_base, j + 0x1));
		writel(odt_val, PHY_REG(phy_base, j + 0xe));
	}
	return ret;
}

void phy_cfg(void __iomem *phy_base,
	     struct ddr_phy_regs *phy_regs, struct ddr_phy_skew *skew,
	     struct sdram_base_params *base, u32 bw)
{
	u32 i;

	sdram_phy_dll_bypass_set(phy_base, base->ddr_freq);
	for (i = 0; phy_regs->phy[i][0] != 0xFFFFFFFF; i++) {
		writel(phy_regs->phy[i][1],
		       phy_base + phy_regs->phy[i][0]);
	}
	if (bw == 2) {
		clrsetbits_le32(PHY_REG(phy_base, 0), 0xf << 4, 0xf << 4);
	} else if (bw == 1) {
		clrsetbits_le32(PHY_REG(phy_base, 0), 0xf << 4, 3 << 4);
		/* disable DQS2,DQS3 tx dll  for saving power */
		clrbits_le32(PHY_REG(phy_base, 0x46), 1 << 3);
		clrbits_le32(PHY_REG(phy_base, 0x56), 1 << 3);
	} else {
		clrsetbits_le32(PHY_REG(phy_base, 0), 0xf << 4, 1 << 4);
		/* disable DQS2,DQS3 tx dll  for saving power */
		clrbits_le32(PHY_REG(phy_base, 0x36), 1 << 3);
		clrbits_le32(PHY_REG(phy_base, 0x46), 1 << 3);
		clrbits_le32(PHY_REG(phy_base, 0x56), 1 << 3);
	}
	sdram_phy_set_ds_odt(phy_base, base->dramtype);

	/* deskew */
	setbits_le32(PHY_REG(phy_base, 2), 8);
	sdram_copy_to_reg(PHY_REG(phy_base, 0xb0),
			  &skew->a0_a1_skew[0], 15 * 4);
	sdram_copy_to_reg(PHY_REG(phy_base, 0x70),
			  &skew->cs0_dm0_skew[0], 44 * 4);
	sdram_copy_to_reg(PHY_REG(phy_base, 0xc0),
			  &skew->cs1_dm0_skew[0], 44 * 4);
}

