// SPDX-License-Identifier: GPL-2.0
/*
 * (C) Copyright 2018 Rockchip Electronics Co., Ltd.
 */

#include <common.h>
#include <ram.h>
#include <asm/io.h>
#include <asm/arch-rockchip/sdram.h>
#include <asm/arch-rockchip/sdram_pctl_px30.h>

/*
 * rank = 1: cs0
 * rank = 2: cs1
 */
void pctl_read_mr(void __iomem *pctl_base, u32 rank, u32 mr_num)
{
	writel((rank << 4) | (1 << 0), pctl_base + DDR_PCTL2_MRCTRL0);
	writel((mr_num << 8), pctl_base + DDR_PCTL2_MRCTRL1);
	setbits_le32(pctl_base + DDR_PCTL2_MRCTRL0, 1u << 31);
	while (readl(pctl_base + DDR_PCTL2_MRCTRL0) & (1u << 31))
		continue;
	while (readl(pctl_base + DDR_PCTL2_MRSTAT) & PCTL2_MR_WR_BUSY)
		continue;
}

/* rank = 1: cs0
 * rank = 2: cs1
 * rank = 3: cs0 & cs1
 * note: be careful of keep mr original val
 */
int pctl_write_mr(void __iomem *pctl_base, u32 rank, u32 mr_num, u32 arg,
		  u32 dramtype)
{
	while (readl(pctl_base + DDR_PCTL2_MRSTAT) & PCTL2_MR_WR_BUSY)
		continue;
	if (dramtype == DDR3 || dramtype == DDR4) {
		writel((mr_num << 12) | (rank << 4) | (0 << 0),
		       pctl_base + DDR_PCTL2_MRCTRL0);
		writel(arg, pctl_base + DDR_PCTL2_MRCTRL1);
	} else {
		writel((rank << 4) | (0 << 0),
		       pctl_base + DDR_PCTL2_MRCTRL0);
		writel((mr_num << 8) | (arg & 0xff),
		       pctl_base + DDR_PCTL2_MRCTRL1);
	}

	setbits_le32(pctl_base + DDR_PCTL2_MRCTRL0, 1u << 31);
	while (readl(pctl_base + DDR_PCTL2_MRCTRL0) & (1u << 31))
		continue;
	while (readl(pctl_base + DDR_PCTL2_MRSTAT) & PCTL2_MR_WR_BUSY)
		continue;

	return 0;
}

/*
 * rank : 1:cs0, 2:cs1, 3:cs0&cs1
 * vrefrate: 4500: 45%,
 */
int pctl_write_vrefdq(void __iomem *pctl_base, u32 rank, u32 vrefrate,
		      u32 dramtype)
{
	u32 tccd_l, value;
	u32 dis_auto_zq = 0;

	if (dramtype != DDR4 || vrefrate < 4500 || vrefrate > 9250)
		return (-1);

	tccd_l = (readl(pctl_base + DDR_PCTL2_DRAMTMG4) >> 16) & 0xf;
	tccd_l = (tccd_l - 4) << 10;

	if (vrefrate > 7500) {
		/* range 1 */
		value = ((vrefrate - 6000) / 65) | tccd_l;
	} else {
		/* range 2 */
		value = ((vrefrate - 4500) / 65) | tccd_l | (1 << 6);
	}

	dis_auto_zq = pctl_dis_zqcs_aref(pctl_base);

	/* enable vrefdq calibratin */
	pctl_write_mr(pctl_base, rank, 6, value | (1 << 7), dramtype);
	udelay(1);/* tvrefdqe */
	/* write vrefdq value */
	pctl_write_mr(pctl_base, rank, 6, value | (1 << 7), dramtype);
	udelay(1);/* tvref_time */
	pctl_write_mr(pctl_base, rank, 6, value | (0 << 7), dramtype);
	udelay(1);/* tvrefdqx */

	pctl_rest_zqcs_aref(pctl_base, dis_auto_zq);

	return 0;
}

static int upctl2_update_ref_reg(void __iomem *pctl_base)
{
	u32 ret;

	ret = readl(pctl_base + DDR_PCTL2_RFSHCTL3) ^ (1 << 1);
	writel(ret, pctl_base + DDR_PCTL2_RFSHCTL3);

	return 0;
}

u32 pctl_dis_zqcs_aref(void __iomem *pctl_base)
{
	u32 dis_auto_zq = 0;

	/* disable zqcs */
	if (!(readl(pctl_base + DDR_PCTL2_ZQCTL0) &
		(1ul << 31))) {
		dis_auto_zq = 1;
		setbits_le32(pctl_base + DDR_PCTL2_ZQCTL0, 1 << 31);
	}

	/* disable auto refresh */
	setbits_le32(pctl_base + DDR_PCTL2_RFSHCTL3, 1);

	upctl2_update_ref_reg(pctl_base);

	return dis_auto_zq;
}

void pctl_rest_zqcs_aref(void __iomem *pctl_base, u32 dis_auto_zq)
{
	/* restore zqcs */
	if (dis_auto_zq)
		clrbits_le32(pctl_base + DDR_PCTL2_ZQCTL0, 1 << 31);

	/* restore auto refresh */
	clrbits_le32(pctl_base + DDR_PCTL2_RFSHCTL3, 1);

	upctl2_update_ref_reg(pctl_base);
}

u32 pctl_remodify_sdram_params(struct ddr_pctl_regs *pctl_regs,
			       struct sdram_cap_info *cap_info,
			       u32 dram_type)
{
	u32 tmp = 0, tmp_adr = 0, i;

	for (i = 0; pctl_regs->pctl[i][0] != 0xFFFFFFFF; i++) {
		if (pctl_regs->pctl[i][0] == 0) {
			tmp = pctl_regs->pctl[i][1];/* MSTR */
			tmp_adr = i;
		}
	}

	tmp &= ~((3ul << 30) | (3ul << 24) | (3ul << 12));

	switch (cap_info->dbw) {
	case 2:
		tmp |= (3ul << 30);
		break;
	case 1:
		tmp |= (2ul << 30);
		break;
	case 0:
	default:
		tmp |= (1ul << 30);
		break;
	}

	/* active_ranks always keep 2 rank for dfi monitor */
	tmp |= 3 << 24;

	tmp |= (2 - cap_info->bw) << 12;

	pctl_regs->pctl[tmp_adr][1] = tmp;

	return 0;
}

int pctl_cfg(void __iomem *pctl_base, struct ddr_pctl_regs *pctl_regs,
	     u32 sr_idle, u32 pd_idle)
{
	u32 i;

	for (i = 0; pctl_regs->pctl[i][0] != 0xFFFFFFFF; i++) {
		writel(pctl_regs->pctl[i][1],
		       pctl_base + pctl_regs->pctl[i][0]);
	}
	clrsetbits_le32(pctl_base + DDR_PCTL2_PWRTMG,
			(0xff << 16) | 0x1f,
			((sr_idle & 0xff) << 16) | (pd_idle & 0x1f));

	clrsetbits_le32(pctl_base + DDR_PCTL2_HWLPCTL,
			0xfff << 16,
			5 << 16);
	/* disable zqcs */
	setbits_le32(pctl_base + DDR_PCTL2_ZQCTL0, 1u << 31);

	return 0;
}

