/*
 * (C) Copyright 2009
 * Marvell Semiconductor <www.marvell.com>
 * Written-by: Prafulla Wadaskar <prafulla@marvell.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <asm/io.h>
#include <asm/arch/soc.h>
#include <asm/arch/mpp.h>
#include <nand.h>

/* NAND Flash Soc registers */
struct kwnandf_registers {
	u32 rd_params;	/* 0x10418 */
	u32 wr_param;	/* 0x1041c */
	u8  pad[0x10470 - 0x1041c - 4];
	u32 ctrl;	/* 0x10470 */
};

static struct kwnandf_registers *nf_reg =
	(struct kwnandf_registers *)KW_NANDF_BASE;

static u32 nand_mpp_backup[9] = { 0 };

/*
 * hardware specific access to control-lines/bits
 */
#define NAND_ACTCEBOOT_BIT		0x02

static void kw_nand_hwcontrol(struct mtd_info *mtd, int cmd,
			      unsigned int ctrl)
{
	struct nand_chip *nc = mtd_to_nand(mtd);
	u32 offs;

	if (cmd == NAND_CMD_NONE)
		return;

	if (ctrl & NAND_CLE)
		offs = (1 << 0);	/* Commands with A[1:0] == 01 */
	else if (ctrl & NAND_ALE)
		offs = (1 << 1);	/* Addresses with A[1:0] == 10 */
	else
		return;

	writeb(cmd, nc->IO_ADDR_W + offs);
}

void kw_nand_select_chip(struct mtd_info *mtd, int chip)
{
	u32 data;
	static const u32 nand_config[] = {
		MPP0_NF_IO2,
		MPP1_NF_IO3,
		MPP2_NF_IO4,
		MPP3_NF_IO5,
		MPP4_NF_IO6,
		MPP5_NF_IO7,
		MPP18_NF_IO0,
		MPP19_NF_IO1,
		0
	};

	if (chip >= 0)
		kirkwood_mpp_conf(nand_config, nand_mpp_backup);
	else
		kirkwood_mpp_conf(nand_mpp_backup, NULL);

	data = readl(&nf_reg->ctrl);
	data |= NAND_ACTCEBOOT_BIT;
	writel(data, &nf_reg->ctrl);
}

int board_nand_init(struct nand_chip *nand)
{
	nand->options = NAND_COPYBACK | NAND_CACHEPRG | NAND_NO_PADDING;
#if defined(CONFIG_SYS_NAND_NO_SUBPAGE_WRITE)
	nand->options |= NAND_NO_SUBPAGE_WRITE;
#endif
#if defined(CONFIG_NAND_ECC_BCH)
	nand->ecc.mode = NAND_ECC_SOFT_BCH;
#else
	nand->ecc.mode = NAND_ECC_SOFT;
#endif
	nand->cmd_ctrl = kw_nand_hwcontrol;
	nand->chip_delay = 40;
	nand->select_chip = kw_nand_select_chip;
	return 0;
}
