/*
 * FSL UPM NAND driver
 *
 * Copyright (C) 2007 MontaVista Software, Inc.
 *                    Anton Vorontsov <avorontsov@ru.mvista.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <config.h>
#include <common.h>
#include <asm/io.h>
#include <linux/errno.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/fsl_upm.h>
#include <nand.h>

static void fsl_upm_start_pattern(struct fsl_upm *upm, u32 pat_offset)
{
	clrsetbits_be32(upm->mxmr, MxMR_MAD_MSK, MxMR_OP_RUNP | pat_offset);
	(void)in_be32(upm->mxmr);
}

static void fsl_upm_end_pattern(struct fsl_upm *upm)
{
	clrbits_be32(upm->mxmr, MxMR_OP_RUNP);

	while (in_be32(upm->mxmr) & MxMR_OP_RUNP)
		eieio();
}

static void fsl_upm_run_pattern(struct fsl_upm *upm, int width,
				void __iomem *io_addr, u32 mar)
{
	out_be32(upm->mar, mar);
	(void)in_be32(upm->mar);
	switch (width) {
	case 8:
		out_8(io_addr, 0x0);
		break;
	case 16:
		out_be16(io_addr, 0x0);
		break;
	case 32:
		out_be32(io_addr, 0x0);
		break;
	}
}

static void fun_wait(struct fsl_upm_nand *fun)
{
	if (fun->dev_ready) {
		while (!fun->dev_ready(fun->chip_nr))
			debug("unexpected busy state\n");
	} else {
		/*
		 * If the R/B pin is not connected,
		 * a short delay is necessary.
		 */
		udelay(1);
	}
}

#if CONFIG_SYS_NAND_MAX_CHIPS > 1
static void fun_select_chip(struct mtd_info *mtd, int chip_nr)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct fsl_upm_nand *fun = nand_get_controller_data(chip);

	if (chip_nr >= 0) {
		fun->chip_nr = chip_nr;
		chip->IO_ADDR_R = chip->IO_ADDR_W =
			fun->upm.io_addr + fun->chip_offset * chip_nr;
	} else if (chip_nr == -1) {
		chip->cmd_ctrl(mtd, NAND_CMD_NONE, 0 | NAND_CTRL_CHANGE);
	}
}
#endif

static void fun_cmd_ctrl(struct mtd_info *mtd, int cmd, unsigned int ctrl)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct fsl_upm_nand *fun = nand_get_controller_data(chip);
	void __iomem *io_addr;
	u32 mar;

	if (!(ctrl & fun->last_ctrl)) {
		fsl_upm_end_pattern(&fun->upm);

		if (cmd == NAND_CMD_NONE)
			return;

		fun->last_ctrl = ctrl & (NAND_ALE | NAND_CLE);
	}

	if (ctrl & NAND_CTRL_CHANGE) {
		if (ctrl & NAND_ALE)
			fsl_upm_start_pattern(&fun->upm, fun->upm_addr_offset);
		else if (ctrl & NAND_CLE)
			fsl_upm_start_pattern(&fun->upm, fun->upm_cmd_offset);
	}

	mar = cmd << (32 - fun->width);
	io_addr = fun->upm.io_addr;
#if CONFIG_SYS_NAND_MAX_CHIPS > 1
	if (fun->chip_nr > 0) {
		io_addr += fun->chip_offset * fun->chip_nr;
		if (fun->upm_mar_chip_offset)
			mar |= fun->upm_mar_chip_offset * fun->chip_nr;
	}
#endif
	fsl_upm_run_pattern(&fun->upm, fun->width, io_addr, mar);

	/*
	 * Some boards/chips needs this.  At least the MPC8360E-RDK
	 * needs it.  Probably weird chip, because I don't see any
	 * need for this on MPC8555E + Samsung K9F1G08U0A.  Usually
	 * here are 0-2 unexpected busy states per block read.
	 */
	if (fun->wait_flags & FSL_UPM_WAIT_RUN_PATTERN)
		fun_wait(fun);
}

static u8 upm_nand_read_byte(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd_to_nand(mtd);

	return in_8(chip->IO_ADDR_R);
}

static void upm_nand_write_buf(struct mtd_info *mtd, const u_char *buf, int len)
{
	int i;
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct fsl_upm_nand *fun = nand_get_controller_data(chip);

	for (i = 0; i < len; i++) {
		out_8(chip->IO_ADDR_W, buf[i]);
		if (fun->wait_flags & FSL_UPM_WAIT_WRITE_BYTE)
			fun_wait(fun);
	}

	if (fun->wait_flags & FSL_UPM_WAIT_WRITE_BUFFER)
		fun_wait(fun);
}

static void upm_nand_read_buf(struct mtd_info *mtd, u_char *buf, int len)
{
	int i;
	struct nand_chip *chip = mtd_to_nand(mtd);

	for (i = 0; i < len; i++)
		buf[i] = in_8(chip->IO_ADDR_R);
}

static int nand_dev_ready(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct fsl_upm_nand *fun = nand_get_controller_data(chip);

	return fun->dev_ready(fun->chip_nr);
}

int fsl_upm_nand_init(struct nand_chip *chip, struct fsl_upm_nand *fun)
{
	if (fun->width != 8 && fun->width != 16 && fun->width != 32)
		return -ENOSYS;

	fun->last_ctrl = NAND_CLE;

	nand_set_controller_data(chip, fun);
	chip->chip_delay = fun->chip_delay;
	chip->ecc.mode = NAND_ECC_SOFT;
	chip->cmd_ctrl = fun_cmd_ctrl;
#if CONFIG_SYS_NAND_MAX_CHIPS > 1
	chip->select_chip = fun_select_chip;
#endif
	chip->read_byte = upm_nand_read_byte;
	chip->read_buf = upm_nand_read_buf;
	chip->write_buf = upm_nand_write_buf;
	if (fun->dev_ready)
		chip->dev_ready = nand_dev_ready;

	return 0;
}
