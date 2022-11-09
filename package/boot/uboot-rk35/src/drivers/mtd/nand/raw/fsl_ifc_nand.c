/* Integrated Flash Controller NAND Machine Driver
 *
 * Copyright (c) 2012 Freescale Semiconductor, Inc
 *
 * Authors: Dipen Dudhat <Dipen.Dudhat@freescale.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <malloc.h>
#include <nand.h>

#include <linux/mtd/mtd.h>
#include <linux/mtd/rawnand.h>
#include <linux/mtd/nand_ecc.h>

#include <asm/io.h>
#include <linux/errno.h>
#include <fsl_ifc.h>

#ifndef CONFIG_SYS_FSL_IFC_BANK_COUNT
#define CONFIG_SYS_FSL_IFC_BANK_COUNT	4
#endif

#define MAX_BANKS	CONFIG_SYS_FSL_IFC_BANK_COUNT
#define ERR_BYTE	0xFF /* Value returned for read bytes
				when read failed */

struct fsl_ifc_ctrl;

/* mtd information per set */
struct fsl_ifc_mtd {
	struct nand_chip chip;
	struct fsl_ifc_ctrl *ctrl;

	struct device *dev;
	int bank;               /* Chip select bank number                */
	unsigned int bufnum_mask; /* bufnum = page & bufnum_mask */
	u8 __iomem *vbase;      /* Chip select base virtual address       */
};

/* overview of the fsl ifc controller */
struct fsl_ifc_ctrl {
	struct nand_hw_control controller;
	struct fsl_ifc_mtd *chips[MAX_BANKS];

	/* device info */
	struct fsl_ifc regs;
	void __iomem *addr;      /* Address of assigned IFC buffer        */
	unsigned int page;       /* Last page written to / read from      */
	unsigned int read_bytes; /* Number of bytes read during command   */
	unsigned int column;     /* Saved column from SEQIN               */
	unsigned int index;      /* Pointer to next byte to 'read'        */
	unsigned int status;     /* status read from NEESR after last op  */
	unsigned int oob;        /* Non zero if operating on OOB data     */
	unsigned int eccread;    /* Non zero for a full-page ECC read     */
};

static struct fsl_ifc_ctrl *ifc_ctrl;

/* 512-byte page with 4-bit ECC, 8-bit */
static struct nand_ecclayout oob_512_8bit_ecc4 = {
	.eccbytes = 8,
	.eccpos = {8, 9, 10, 11, 12, 13, 14, 15},
	.oobfree = { {0, 5}, {6, 2} },
};

/* 512-byte page with 4-bit ECC, 16-bit */
static struct nand_ecclayout oob_512_16bit_ecc4 = {
	.eccbytes = 8,
	.eccpos = {8, 9, 10, 11, 12, 13, 14, 15},
	.oobfree = { {2, 6}, },
};

/* 2048-byte page size with 4-bit ECC */
static struct nand_ecclayout oob_2048_ecc4 = {
	.eccbytes = 32,
	.eccpos = {
		8, 9, 10, 11, 12, 13, 14, 15,
		16, 17, 18, 19, 20, 21, 22, 23,
		24, 25, 26, 27, 28, 29, 30, 31,
		32, 33, 34, 35, 36, 37, 38, 39,
	},
	.oobfree = { {2, 6}, {40, 24} },
};

/* 4096-byte page size with 4-bit ECC */
static struct nand_ecclayout oob_4096_ecc4 = {
	.eccbytes = 64,
	.eccpos = {
		8, 9, 10, 11, 12, 13, 14, 15,
		16, 17, 18, 19, 20, 21, 22, 23,
		24, 25, 26, 27, 28, 29, 30, 31,
		32, 33, 34, 35, 36, 37, 38, 39,
		40, 41, 42, 43, 44, 45, 46, 47,
		48, 49, 50, 51, 52, 53, 54, 55,
		56, 57, 58, 59, 60, 61, 62, 63,
		64, 65, 66, 67, 68, 69, 70, 71,
	},
	.oobfree = { {2, 6}, {72, 56} },
};

/* 4096-byte page size with 8-bit ECC -- requires 218-byte OOB */
static struct nand_ecclayout oob_4096_ecc8 = {
	.eccbytes = 128,
	.eccpos = {
		8, 9, 10, 11, 12, 13, 14, 15,
		16, 17, 18, 19, 20, 21, 22, 23,
		24, 25, 26, 27, 28, 29, 30, 31,
		32, 33, 34, 35, 36, 37, 38, 39,
		40, 41, 42, 43, 44, 45, 46, 47,
		48, 49, 50, 51, 52, 53, 54, 55,
		56, 57, 58, 59, 60, 61, 62, 63,
		64, 65, 66, 67, 68, 69, 70, 71,
		72, 73, 74, 75, 76, 77, 78, 79,
		80, 81, 82, 83, 84, 85, 86, 87,
		88, 89, 90, 91, 92, 93, 94, 95,
		96, 97, 98, 99, 100, 101, 102, 103,
		104, 105, 106, 107, 108, 109, 110, 111,
		112, 113, 114, 115, 116, 117, 118, 119,
		120, 121, 122, 123, 124, 125, 126, 127,
		128, 129, 130, 131, 132, 133, 134, 135,
	},
	.oobfree = { {2, 6}, {136, 82} },
};

/* 8192-byte page size with 4-bit ECC */
static struct nand_ecclayout oob_8192_ecc4 = {
	.eccbytes = 128,
	.eccpos = {
		8, 9, 10, 11, 12, 13, 14, 15,
		16, 17, 18, 19, 20, 21, 22, 23,
		24, 25, 26, 27, 28, 29, 30, 31,
		32, 33, 34, 35, 36, 37, 38, 39,
		40, 41, 42, 43, 44, 45, 46, 47,
		48, 49, 50, 51, 52, 53, 54, 55,
		56, 57, 58, 59, 60, 61, 62, 63,
		64, 65, 66, 67, 68, 69, 70, 71,
		72, 73, 74, 75, 76, 77, 78, 79,
		80, 81, 82, 83, 84, 85, 86, 87,
		88, 89, 90, 91, 92, 93, 94, 95,
		96, 97, 98, 99, 100, 101, 102, 103,
		104, 105, 106, 107, 108, 109, 110, 111,
		112, 113, 114, 115, 116, 117, 118, 119,
		120, 121, 122, 123, 124, 125, 126, 127,
		128, 129, 130, 131, 132, 133, 134, 135,
	},
	.oobfree = { {2, 6}, {136, 208} },
};

/* 8192-byte page size with 8-bit ECC -- requires 218-byte OOB */
static struct nand_ecclayout oob_8192_ecc8 = {
	.eccbytes = 256,
	.eccpos = {
		8, 9, 10, 11, 12, 13, 14, 15,
		16, 17, 18, 19, 20, 21, 22, 23,
		24, 25, 26, 27, 28, 29, 30, 31,
		32, 33, 34, 35, 36, 37, 38, 39,
		40, 41, 42, 43, 44, 45, 46, 47,
		48, 49, 50, 51, 52, 53, 54, 55,
		56, 57, 58, 59, 60, 61, 62, 63,
		64, 65, 66, 67, 68, 69, 70, 71,
		72, 73, 74, 75, 76, 77, 78, 79,
		80, 81, 82, 83, 84, 85, 86, 87,
		88, 89, 90, 91, 92, 93, 94, 95,
		96, 97, 98, 99, 100, 101, 102, 103,
		104, 105, 106, 107, 108, 109, 110, 111,
		112, 113, 114, 115, 116, 117, 118, 119,
		120, 121, 122, 123, 124, 125, 126, 127,
		128, 129, 130, 131, 132, 133, 134, 135,
		136, 137, 138, 139, 140, 141, 142, 143,
		144, 145, 146, 147, 148, 149, 150, 151,
		152, 153, 154, 155, 156, 157, 158, 159,
		160, 161, 162, 163, 164, 165, 166, 167,
		168, 169, 170, 171, 172, 173, 174, 175,
		176, 177, 178, 179, 180, 181, 182, 183,
		184, 185, 186, 187, 188, 189, 190, 191,
		192, 193, 194, 195, 196, 197, 198, 199,
		200, 201, 202, 203, 204, 205, 206, 207,
		208, 209, 210, 211, 212, 213, 214, 215,
		216, 217, 218, 219, 220, 221, 222, 223,
		224, 225, 226, 227, 228, 229, 230, 231,
		232, 233, 234, 235, 236, 237, 238, 239,
		240, 241, 242, 243, 244, 245, 246, 247,
		248, 249, 250, 251, 252, 253, 254, 255,
		256, 257, 258, 259, 260, 261, 262, 263,
	},
	.oobfree = { {2, 6}, {264, 80} },
};

/*
 * Generic flash bbt descriptors
 */
static u8 bbt_pattern[] = {'B', 'b', 't', '0' };
static u8 mirror_pattern[] = {'1', 't', 'b', 'B' };

static struct nand_bbt_descr bbt_main_descr = {
	.options = NAND_BBT_LASTBLOCK | NAND_BBT_CREATE | NAND_BBT_WRITE |
		   NAND_BBT_2BIT | NAND_BBT_VERSION,
	.offs =	2, /* 0 on 8-bit small page */
	.len = 4,
	.veroffs = 6,
	.maxblocks = 4,
	.pattern = bbt_pattern,
};

static struct nand_bbt_descr bbt_mirror_descr = {
	.options = NAND_BBT_LASTBLOCK | NAND_BBT_CREATE | NAND_BBT_WRITE |
		   NAND_BBT_2BIT | NAND_BBT_VERSION,
	.offs =	2, /* 0 on 8-bit small page */
	.len = 4,
	.veroffs = 6,
	.maxblocks = 4,
	.pattern = mirror_pattern,
};

/*
 * Set up the IFC hardware block and page address fields, and the ifc nand
 * structure addr field to point to the correct IFC buffer in memory
 */
static void set_addr(struct mtd_info *mtd, int column, int page_addr, int oob)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct fsl_ifc_mtd *priv = nand_get_controller_data(chip);
	struct fsl_ifc_ctrl *ctrl = priv->ctrl;
	struct fsl_ifc_runtime *ifc = ctrl->regs.rregs;
	int buf_num;

	ctrl->page = page_addr;

	/* Program ROW0/COL0 */
	ifc_out32(&ifc->ifc_nand.row0, page_addr);
	ifc_out32(&ifc->ifc_nand.col0, (oob ? IFC_NAND_COL_MS : 0) | column);

	buf_num = page_addr & priv->bufnum_mask;

	ctrl->addr = priv->vbase + buf_num * (mtd->writesize * 2);
	ctrl->index = column;

	/* for OOB data point to the second half of the buffer */
	if (oob)
		ctrl->index += mtd->writesize;
}

/* returns nonzero if entire page is blank */
static int check_read_ecc(struct mtd_info *mtd, struct fsl_ifc_ctrl *ctrl,
			  u32 eccstat, unsigned int bufnum)
{
	return (eccstat >> ((3 - bufnum % 4) * 8)) & 15;
}

/*
 * execute IFC NAND command and wait for it to complete
 */
static int fsl_ifc_run_command(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct fsl_ifc_mtd *priv = nand_get_controller_data(chip);
	struct fsl_ifc_ctrl *ctrl = priv->ctrl;
	struct fsl_ifc_runtime *ifc = ctrl->regs.rregs;
	u32 timeo = (CONFIG_SYS_HZ * 10) / 1000;
	u32 time_start;
	u32 eccstat;
	int i;

	/* set the chip select for NAND Transaction */
	ifc_out32(&ifc->ifc_nand.nand_csel, priv->bank << IFC_NAND_CSEL_SHIFT);

	/* start read/write seq */
	ifc_out32(&ifc->ifc_nand.nandseq_strt,
		  IFC_NAND_SEQ_STRT_FIR_STRT);

	/* wait for NAND Machine complete flag or timeout */
	time_start = get_timer(0);

	while (get_timer(time_start) < timeo) {
		ctrl->status = ifc_in32(&ifc->ifc_nand.nand_evter_stat);

		if (ctrl->status & IFC_NAND_EVTER_STAT_OPC)
			break;
	}

	ifc_out32(&ifc->ifc_nand.nand_evter_stat, ctrl->status);

	if (ctrl->status & IFC_NAND_EVTER_STAT_FTOER)
		printf("%s: Flash Time Out Error\n", __func__);
	if (ctrl->status & IFC_NAND_EVTER_STAT_WPER)
		printf("%s: Write Protect Error\n", __func__);

	if (ctrl->eccread) {
		int errors;
		int bufnum = ctrl->page & priv->bufnum_mask;
		int sector_start = bufnum * chip->ecc.steps;
		int sector_end = sector_start + chip->ecc.steps - 1;
		u32 *eccstat_regs;

		eccstat_regs = ifc->ifc_nand.nand_eccstat;
		eccstat = ifc_in32(&eccstat_regs[sector_start / 4]);

		for (i = sector_start; i <= sector_end; i++) {
			if ((i != sector_start) && !(i % 4))
				eccstat = ifc_in32(&eccstat_regs[i / 4]);

			errors = check_read_ecc(mtd, ctrl, eccstat, i);

			if (errors == 15) {
				/*
				 * Uncorrectable error.
				 * We'll check for blank pages later.
				 *
				 * We disable ECCER reporting due to erratum
				 * IFC-A002770 -- so report it now if we
				 * see an uncorrectable error in ECCSTAT.
				 */
				ctrl->status |= IFC_NAND_EVTER_STAT_ECCER;
				continue;
			}

			mtd->ecc_stats.corrected += errors;
		}

		ctrl->eccread = 0;
	}

	/* returns 0 on success otherwise non-zero) */
	return ctrl->status == IFC_NAND_EVTER_STAT_OPC ? 0 : -EIO;
}

static void fsl_ifc_do_read(struct nand_chip *chip,
			    int oob,
			    struct mtd_info *mtd)
{
	struct fsl_ifc_mtd *priv = nand_get_controller_data(chip);
	struct fsl_ifc_ctrl *ctrl = priv->ctrl;
	struct fsl_ifc_runtime *ifc = ctrl->regs.rregs;

	/* Program FIR/IFC_NAND_FCR0 for Small/Large page */
	if (mtd->writesize > 512) {
		ifc_out32(&ifc->ifc_nand.nand_fir0,
			  (IFC_FIR_OP_CW0 << IFC_NAND_FIR0_OP0_SHIFT) |
			  (IFC_FIR_OP_CA0 << IFC_NAND_FIR0_OP1_SHIFT) |
			  (IFC_FIR_OP_RA0 << IFC_NAND_FIR0_OP2_SHIFT) |
			  (IFC_FIR_OP_CMD1 << IFC_NAND_FIR0_OP3_SHIFT) |
			  (IFC_FIR_OP_RBCD << IFC_NAND_FIR0_OP4_SHIFT));
		ifc_out32(&ifc->ifc_nand.nand_fir1, 0x0);

		ifc_out32(&ifc->ifc_nand.nand_fcr0,
			  (NAND_CMD_READ0 << IFC_NAND_FCR0_CMD0_SHIFT) |
			  (NAND_CMD_READSTART << IFC_NAND_FCR0_CMD1_SHIFT));
	} else {
		ifc_out32(&ifc->ifc_nand.nand_fir0,
			  (IFC_FIR_OP_CW0 << IFC_NAND_FIR0_OP0_SHIFT) |
			  (IFC_FIR_OP_CA0 << IFC_NAND_FIR0_OP1_SHIFT) |
			  (IFC_FIR_OP_RA0  << IFC_NAND_FIR0_OP2_SHIFT) |
			  (IFC_FIR_OP_RBCD << IFC_NAND_FIR0_OP3_SHIFT));

		if (oob)
			ifc_out32(&ifc->ifc_nand.nand_fcr0,
				  NAND_CMD_READOOB << IFC_NAND_FCR0_CMD0_SHIFT);
		else
			ifc_out32(&ifc->ifc_nand.nand_fcr0,
				  NAND_CMD_READ0 << IFC_NAND_FCR0_CMD0_SHIFT);
	}
}

/* cmdfunc send commands to the IFC NAND Machine */
static void fsl_ifc_cmdfunc(struct mtd_info *mtd, unsigned int command,
			     int column, int page_addr)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct fsl_ifc_mtd *priv = nand_get_controller_data(chip);
	struct fsl_ifc_ctrl *ctrl = priv->ctrl;
	struct fsl_ifc_runtime *ifc = ctrl->regs.rregs;

	/* clear the read buffer */
	ctrl->read_bytes = 0;
	if (command != NAND_CMD_PAGEPROG)
		ctrl->index = 0;

	switch (command) {
	/* READ0 read the entire buffer to use hardware ECC. */
	case NAND_CMD_READ0: {
		ifc_out32(&ifc->ifc_nand.nand_fbcr, 0);
		set_addr(mtd, 0, page_addr, 0);

		ctrl->read_bytes = mtd->writesize + mtd->oobsize;
		ctrl->index += column;

		if (chip->ecc.mode == NAND_ECC_HW)
			ctrl->eccread = 1;

		fsl_ifc_do_read(chip, 0, mtd);
		fsl_ifc_run_command(mtd);
		return;
	}

	/* READOOB reads only the OOB because no ECC is performed. */
	case NAND_CMD_READOOB:
		ifc_out32(&ifc->ifc_nand.nand_fbcr, mtd->oobsize - column);
		set_addr(mtd, column, page_addr, 1);

		ctrl->read_bytes = mtd->writesize + mtd->oobsize;

		fsl_ifc_do_read(chip, 1, mtd);
		fsl_ifc_run_command(mtd);

		return;

	/* READID must read all possible bytes while CEB is active */
	case NAND_CMD_READID:
	case NAND_CMD_PARAM: {
		int timing = IFC_FIR_OP_RB;
		if (command == NAND_CMD_PARAM)
			timing = IFC_FIR_OP_RBCD;

		ifc_out32(&ifc->ifc_nand.nand_fir0,
			  (IFC_FIR_OP_CW0 << IFC_NAND_FIR0_OP0_SHIFT) |
			  (IFC_FIR_OP_UA  << IFC_NAND_FIR0_OP1_SHIFT) |
			  (timing << IFC_NAND_FIR0_OP2_SHIFT));
		ifc_out32(&ifc->ifc_nand.nand_fcr0,
			  command << IFC_NAND_FCR0_CMD0_SHIFT);
		ifc_out32(&ifc->ifc_nand.row3, column);

		/*
		 * although currently it's 8 bytes for READID, we always read
		 * the maximum 256 bytes(for PARAM)
		 */
		ifc_out32(&ifc->ifc_nand.nand_fbcr, 256);
		ctrl->read_bytes = 256;

		set_addr(mtd, 0, 0, 0);
		fsl_ifc_run_command(mtd);
		return;
	}

	/* ERASE1 stores the block and page address */
	case NAND_CMD_ERASE1:
		set_addr(mtd, 0, page_addr, 0);
		return;

	/* ERASE2 uses the block and page address from ERASE1 */
	case NAND_CMD_ERASE2:
		ifc_out32(&ifc->ifc_nand.nand_fir0,
			  (IFC_FIR_OP_CW0 << IFC_NAND_FIR0_OP0_SHIFT) |
			  (IFC_FIR_OP_RA0 << IFC_NAND_FIR0_OP1_SHIFT) |
			  (IFC_FIR_OP_CMD1 << IFC_NAND_FIR0_OP2_SHIFT));

		ifc_out32(&ifc->ifc_nand.nand_fcr0,
			  (NAND_CMD_ERASE1 << IFC_NAND_FCR0_CMD0_SHIFT) |
			  (NAND_CMD_ERASE2 << IFC_NAND_FCR0_CMD1_SHIFT));

		ifc_out32(&ifc->ifc_nand.nand_fbcr, 0);
		ctrl->read_bytes = 0;
		fsl_ifc_run_command(mtd);
		return;

	/* SEQIN sets up the addr buffer and all registers except the length */
	case NAND_CMD_SEQIN: {
		u32 nand_fcr0;
		ctrl->column = column;
		ctrl->oob = 0;

		if (mtd->writesize > 512) {
			nand_fcr0 =
				(NAND_CMD_SEQIN << IFC_NAND_FCR0_CMD0_SHIFT) |
				(NAND_CMD_STATUS << IFC_NAND_FCR0_CMD1_SHIFT) |
				(NAND_CMD_PAGEPROG << IFC_NAND_FCR0_CMD2_SHIFT);

			ifc_out32(&ifc->ifc_nand.nand_fir0,
				  (IFC_FIR_OP_CW0 << IFC_NAND_FIR0_OP0_SHIFT) |
				  (IFC_FIR_OP_CA0 << IFC_NAND_FIR0_OP1_SHIFT) |
				  (IFC_FIR_OP_RA0 << IFC_NAND_FIR0_OP2_SHIFT) |
				  (IFC_FIR_OP_WBCD  <<
						IFC_NAND_FIR0_OP3_SHIFT) |
				  (IFC_FIR_OP_CMD2 << IFC_NAND_FIR0_OP4_SHIFT));
			ifc_out32(&ifc->ifc_nand.nand_fir1,
				  (IFC_FIR_OP_CW1 << IFC_NAND_FIR1_OP5_SHIFT) |
				  (IFC_FIR_OP_RDSTAT <<
					IFC_NAND_FIR1_OP6_SHIFT) |
				  (IFC_FIR_OP_NOP << IFC_NAND_FIR1_OP7_SHIFT));
		} else {
			nand_fcr0 = ((NAND_CMD_PAGEPROG <<
					IFC_NAND_FCR0_CMD1_SHIFT) |
				    (NAND_CMD_SEQIN <<
					IFC_NAND_FCR0_CMD2_SHIFT) |
				    (NAND_CMD_STATUS <<
					IFC_NAND_FCR0_CMD3_SHIFT));

			ifc_out32(&ifc->ifc_nand.nand_fir0,
				  (IFC_FIR_OP_CW0 << IFC_NAND_FIR0_OP0_SHIFT) |
				  (IFC_FIR_OP_CMD2 << IFC_NAND_FIR0_OP1_SHIFT) |
				  (IFC_FIR_OP_CA0 << IFC_NAND_FIR0_OP2_SHIFT) |
				  (IFC_FIR_OP_RA0 << IFC_NAND_FIR0_OP3_SHIFT) |
				  (IFC_FIR_OP_WBCD << IFC_NAND_FIR0_OP4_SHIFT));
			ifc_out32(&ifc->ifc_nand.nand_fir1,
				  (IFC_FIR_OP_CMD1 << IFC_NAND_FIR1_OP5_SHIFT) |
				  (IFC_FIR_OP_CW3 << IFC_NAND_FIR1_OP6_SHIFT) |
				  (IFC_FIR_OP_RDSTAT <<
					IFC_NAND_FIR1_OP7_SHIFT) |
				  (IFC_FIR_OP_NOP << IFC_NAND_FIR1_OP8_SHIFT));

			if (column >= mtd->writesize)
				nand_fcr0 |=
				NAND_CMD_READOOB << IFC_NAND_FCR0_CMD0_SHIFT;
			else
				nand_fcr0 |=
				NAND_CMD_READ0 << IFC_NAND_FCR0_CMD0_SHIFT;
		}

		if (column >= mtd->writesize) {
			/* OOB area --> READOOB */
			column -= mtd->writesize;
			ctrl->oob = 1;
		}
		ifc_out32(&ifc->ifc_nand.nand_fcr0, nand_fcr0);
		set_addr(mtd, column, page_addr, ctrl->oob);
		return;
	}

	/* PAGEPROG reuses all of the setup from SEQIN and adds the length */
	case NAND_CMD_PAGEPROG:
		if (ctrl->oob)
			ifc_out32(&ifc->ifc_nand.nand_fbcr,
				  ctrl->index - ctrl->column);
		else
			ifc_out32(&ifc->ifc_nand.nand_fbcr, 0);

		fsl_ifc_run_command(mtd);
		return;

	case NAND_CMD_STATUS:
		ifc_out32(&ifc->ifc_nand.nand_fir0,
			  (IFC_FIR_OP_CW0 << IFC_NAND_FIR0_OP0_SHIFT) |
			  (IFC_FIR_OP_RB << IFC_NAND_FIR0_OP1_SHIFT));
		ifc_out32(&ifc->ifc_nand.nand_fcr0,
			  NAND_CMD_STATUS << IFC_NAND_FCR0_CMD0_SHIFT);
		ifc_out32(&ifc->ifc_nand.nand_fbcr, 1);
		set_addr(mtd, 0, 0, 0);
		ctrl->read_bytes = 1;

		fsl_ifc_run_command(mtd);

		/*
		 * The chip always seems to report that it is
		 * write-protected, even when it is not.
		 */
		if (chip->options & NAND_BUSWIDTH_16)
			ifc_out16(ctrl->addr,
				  ifc_in16(ctrl->addr) | NAND_STATUS_WP);
		else
			out_8(ctrl->addr, in_8(ctrl->addr) | NAND_STATUS_WP);
		return;

	case NAND_CMD_RESET:
		ifc_out32(&ifc->ifc_nand.nand_fir0,
			  IFC_FIR_OP_CW0 << IFC_NAND_FIR0_OP0_SHIFT);
		ifc_out32(&ifc->ifc_nand.nand_fcr0,
			  NAND_CMD_RESET << IFC_NAND_FCR0_CMD0_SHIFT);
		fsl_ifc_run_command(mtd);
		return;

	default:
		printf("%s: error, unsupported command 0x%x.\n",
			__func__, command);
	}
}

/*
 * Write buf to the IFC NAND Controller Data Buffer
 */
static void fsl_ifc_write_buf(struct mtd_info *mtd, const u8 *buf, int len)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct fsl_ifc_mtd *priv = nand_get_controller_data(chip);
	struct fsl_ifc_ctrl *ctrl = priv->ctrl;
	unsigned int bufsize = mtd->writesize + mtd->oobsize;

	if (len <= 0) {
		printf("%s of %d bytes", __func__, len);
		ctrl->status = 0;
		return;
	}

	if ((unsigned int)len > bufsize - ctrl->index) {
		printf("%s beyond end of buffer "
		       "(%d requested, %u available)\n",
			__func__, len, bufsize - ctrl->index);
		len = bufsize - ctrl->index;
	}

	memcpy_toio(ctrl->addr + ctrl->index, buf, len);
	ctrl->index += len;
}

/*
 * read a byte from either the IFC hardware buffer if it has any data left
 * otherwise issue a command to read a single byte.
 */
static u8 fsl_ifc_read_byte(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct fsl_ifc_mtd *priv = nand_get_controller_data(chip);
	struct fsl_ifc_ctrl *ctrl = priv->ctrl;
	unsigned int offset;

	/*
	 * If there are still bytes in the IFC buffer, then use the
	 * next byte.
	 */
	if (ctrl->index < ctrl->read_bytes) {
		offset = ctrl->index++;
		return in_8(ctrl->addr + offset);
	}

	printf("%s beyond end of buffer\n", __func__);
	return ERR_BYTE;
}

/*
 * Read two bytes from the IFC hardware buffer
 * read function for 16-bit buswith
 */
static uint8_t fsl_ifc_read_byte16(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct fsl_ifc_mtd *priv = nand_get_controller_data(chip);
	struct fsl_ifc_ctrl *ctrl = priv->ctrl;
	uint16_t data;

	/*
	 * If there are still bytes in the IFC buffer, then use the
	 * next byte.
	 */
	if (ctrl->index < ctrl->read_bytes) {
		data = ifc_in16(ctrl->addr + ctrl->index);
		ctrl->index += 2;
		return (uint8_t)data;
	}

	printf("%s beyond end of buffer\n", __func__);
	return ERR_BYTE;
}

/*
 * Read from the IFC Controller Data Buffer
 */
static void fsl_ifc_read_buf(struct mtd_info *mtd, u8 *buf, int len)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct fsl_ifc_mtd *priv = nand_get_controller_data(chip);
	struct fsl_ifc_ctrl *ctrl = priv->ctrl;
	int avail;

	if (len < 0)
		return;

	avail = min((unsigned int)len, ctrl->read_bytes - ctrl->index);
	memcpy_fromio(buf, ctrl->addr + ctrl->index, avail);
	ctrl->index += avail;

	if (len > avail)
		printf("%s beyond end of buffer "
		       "(%d requested, %d available)\n",
		       __func__, len, avail);
}

/* This function is called after Program and Erase Operations to
 * check for success or failure.
 */
static int fsl_ifc_wait(struct mtd_info *mtd, struct nand_chip *chip)
{
	struct fsl_ifc_mtd *priv = nand_get_controller_data(chip);
	struct fsl_ifc_ctrl *ctrl = priv->ctrl;
	struct fsl_ifc_runtime *ifc = ctrl->regs.rregs;
	u32 nand_fsr;
	int status;

	if (ctrl->status != IFC_NAND_EVTER_STAT_OPC)
		return NAND_STATUS_FAIL;

	/* Use READ_STATUS command, but wait for the device to be ready */
	ifc_out32(&ifc->ifc_nand.nand_fir0,
		  (IFC_FIR_OP_CW0 << IFC_NAND_FIR0_OP0_SHIFT) |
		  (IFC_FIR_OP_RDSTAT << IFC_NAND_FIR0_OP1_SHIFT));
	ifc_out32(&ifc->ifc_nand.nand_fcr0, NAND_CMD_STATUS <<
		  IFC_NAND_FCR0_CMD0_SHIFT);
	ifc_out32(&ifc->ifc_nand.nand_fbcr, 1);
	set_addr(mtd, 0, 0, 0);
	ctrl->read_bytes = 1;

	fsl_ifc_run_command(mtd);

	if (ctrl->status != IFC_NAND_EVTER_STAT_OPC)
		return NAND_STATUS_FAIL;

	nand_fsr = ifc_in32(&ifc->ifc_nand.nand_fsr);
	status = nand_fsr >> 24;

	/* Chip sometimes reporting write protect even when it's not */
	return status | NAND_STATUS_WP;
}

/*
 * The controller does not check for bitflips in erased pages,
 * therefore software must check instead.
 */
static int
check_erased_page(struct nand_chip *chip, u8 *buf, struct mtd_info *mtd)
{
	u8 *ecc = chip->oob_poi;
	const int ecc_size = chip->ecc.bytes;
	const int pkt_size = chip->ecc.size;
	int i, res, bitflips;

	/* IFC starts ecc bytes at offset 8 in the spare area. */
	ecc += 8;
	bitflips = 0;
	for (i = 0; i < chip->ecc.steps; i++) {
		res = nand_check_erased_ecc_chunk(buf, pkt_size, ecc, ecc_size,
						  NULL, 0, chip->ecc.strength);

		if (res < 0) {
			printf("fsl-ifc: NAND Flash ECC Uncorrectable Error\n");
			mtd->ecc_stats.failed++;
		} else if (res > 0) {
			mtd->ecc_stats.corrected += res;
		}
		bitflips = max(res, bitflips);
		buf += pkt_size;
		ecc += ecc_size;
	}

	return bitflips;
}

static int fsl_ifc_read_page(struct mtd_info *mtd, struct nand_chip *chip,
			     uint8_t *buf, int oob_required, int page)
{
	struct fsl_ifc_mtd *priv = nand_get_controller_data(chip);
	struct fsl_ifc_ctrl *ctrl = priv->ctrl;

	fsl_ifc_read_buf(mtd, buf, mtd->writesize);
	fsl_ifc_read_buf(mtd, chip->oob_poi, mtd->oobsize);

	if (ctrl->status & IFC_NAND_EVTER_STAT_ECCER)
		return check_erased_page(chip, buf, mtd);

	if (ctrl->status != IFC_NAND_EVTER_STAT_OPC)
		mtd->ecc_stats.failed++;

	return 0;
}

/* ECC will be calculated automatically, and errors will be detected in
 * waitfunc.
 */
static int fsl_ifc_write_page(struct mtd_info *mtd, struct nand_chip *chip,
			       const uint8_t *buf, int oob_required, int page)
{
	fsl_ifc_write_buf(mtd, buf, mtd->writesize);
	fsl_ifc_write_buf(mtd, chip->oob_poi, mtd->oobsize);

	return 0;
}

static void fsl_ifc_ctrl_init(void)
{
	uint32_t ver = 0;
	ifc_ctrl = kzalloc(sizeof(*ifc_ctrl), GFP_KERNEL);
	if (!ifc_ctrl)
		return;

	ifc_ctrl->regs.gregs = IFC_FCM_BASE_ADDR;

	ver = ifc_in32(&ifc_ctrl->regs.gregs->ifc_rev);
	if (ver >= FSL_IFC_V2_0_0)
		ifc_ctrl->regs.rregs =
			(void *)CONFIG_SYS_IFC_ADDR + IFC_RREGS_64KOFFSET;
	else
		ifc_ctrl->regs.rregs =
			(void *)CONFIG_SYS_IFC_ADDR + IFC_RREGS_4KOFFSET;

	/* clear event registers */
	ifc_out32(&ifc_ctrl->regs.rregs->ifc_nand.nand_evter_stat, ~0U);
	ifc_out32(&ifc_ctrl->regs.rregs->ifc_nand.pgrdcmpl_evt_stat, ~0U);

	/* Enable error and event for any detected errors */
	ifc_out32(&ifc_ctrl->regs.rregs->ifc_nand.nand_evter_en,
		  IFC_NAND_EVTER_EN_OPC_EN |
		  IFC_NAND_EVTER_EN_PGRDCMPL_EN |
		  IFC_NAND_EVTER_EN_FTOER_EN |
		  IFC_NAND_EVTER_EN_WPER_EN);

	ifc_out32(&ifc_ctrl->regs.rregs->ifc_nand.ncfgr, 0x0);
}

static void fsl_ifc_select_chip(struct mtd_info *mtd, int chip)
{
}

static int fsl_ifc_sram_init(struct fsl_ifc_mtd *priv, uint32_t ver)
{
	struct fsl_ifc_runtime *ifc = ifc_ctrl->regs.rregs;
	uint32_t cs = 0, csor = 0, csor_8k = 0, csor_ext = 0;
	uint32_t ncfgr = 0;
	u32 timeo = (CONFIG_SYS_HZ * 10) / 1000;
	u32 time_start;

	if (ver > FSL_IFC_V1_1_0) {
		ncfgr = ifc_in32(&ifc->ifc_nand.ncfgr);
		ifc_out32(&ifc->ifc_nand.ncfgr, ncfgr | IFC_NAND_SRAM_INIT_EN);

		/* wait for  SRAM_INIT bit to be clear or timeout */
		time_start = get_timer(0);
		while (get_timer(time_start) < timeo) {
			ifc_ctrl->status =
				ifc_in32(&ifc->ifc_nand.nand_evter_stat);

			if (!(ifc_ctrl->status & IFC_NAND_SRAM_INIT_EN))
				return 0;
		}
		printf("fsl-ifc: Failed to Initialise SRAM\n");
		return 1;
	}

	cs = priv->bank;

	/* Save CSOR and CSOR_ext */
	csor = ifc_in32(&ifc_ctrl->regs.gregs->csor_cs[cs].csor);
	csor_ext = ifc_in32(&ifc_ctrl->regs.gregs->csor_cs[cs].csor_ext);

	/* chage PageSize 8K and SpareSize 1K*/
	csor_8k = (csor & ~(CSOR_NAND_PGS_MASK)) | 0x0018C000;
	ifc_out32(&ifc_ctrl->regs.gregs->csor_cs[cs].csor, csor_8k);
	ifc_out32(&ifc_ctrl->regs.gregs->csor_cs[cs].csor_ext, 0x0000400);

	/* READID */
	ifc_out32(&ifc->ifc_nand.nand_fir0,
		  (IFC_FIR_OP_CW0 << IFC_NAND_FIR0_OP0_SHIFT) |
		  (IFC_FIR_OP_UA  << IFC_NAND_FIR0_OP1_SHIFT) |
		  (IFC_FIR_OP_RB << IFC_NAND_FIR0_OP2_SHIFT));
	ifc_out32(&ifc->ifc_nand.nand_fcr0,
		  NAND_CMD_READID << IFC_NAND_FCR0_CMD0_SHIFT);
	ifc_out32(&ifc->ifc_nand.row3, 0x0);

	ifc_out32(&ifc->ifc_nand.nand_fbcr, 0x0);

	/* Program ROW0/COL0 */
	ifc_out32(&ifc->ifc_nand.row0, 0x0);
	ifc_out32(&ifc->ifc_nand.col0, 0x0);

	/* set the chip select for NAND Transaction */
	ifc_out32(&ifc->ifc_nand.nand_csel, priv->bank << IFC_NAND_CSEL_SHIFT);

	/* start read seq */
	ifc_out32(&ifc->ifc_nand.nandseq_strt, IFC_NAND_SEQ_STRT_FIR_STRT);

	time_start = get_timer(0);

	while (get_timer(time_start) < timeo) {
		ifc_ctrl->status = ifc_in32(&ifc->ifc_nand.nand_evter_stat);

		if (ifc_ctrl->status & IFC_NAND_EVTER_STAT_OPC)
			break;
	}

	if (ifc_ctrl->status != IFC_NAND_EVTER_STAT_OPC) {
		printf("fsl-ifc: Failed to Initialise SRAM\n");
		return 1;
	}

	ifc_out32(&ifc->ifc_nand.nand_evter_stat, ifc_ctrl->status);

	/* Restore CSOR and CSOR_ext */
	ifc_out32(&ifc_ctrl->regs.gregs->csor_cs[cs].csor, csor);
	ifc_out32(&ifc_ctrl->regs.gregs->csor_cs[cs].csor_ext, csor_ext);

	return 0;
}

static int fsl_ifc_chip_init(int devnum, u8 *addr)
{
	struct mtd_info *mtd;
	struct nand_chip *nand;
	struct fsl_ifc_mtd *priv;
	struct nand_ecclayout *layout;
	struct fsl_ifc_fcm *gregs = NULL;
	uint32_t cspr = 0, csor = 0, ver = 0;
	int ret = 0;

	if (!ifc_ctrl) {
		fsl_ifc_ctrl_init();
		if (!ifc_ctrl)
			return -1;
	}

	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->ctrl = ifc_ctrl;
	priv->vbase = addr;
	gregs = ifc_ctrl->regs.gregs;

	/* Find which chip select it is connected to.
	 */
	for (priv->bank = 0; priv->bank < MAX_BANKS; priv->bank++) {
		phys_addr_t phys_addr = virt_to_phys(addr);

		cspr = ifc_in32(&gregs->cspr_cs[priv->bank].cspr);
		csor = ifc_in32(&gregs->csor_cs[priv->bank].csor);

		if ((cspr & CSPR_V) && (cspr & CSPR_MSEL) == CSPR_MSEL_NAND &&
		    (cspr & CSPR_BA) == CSPR_PHYS_ADDR(phys_addr))
			break;
	}

	if (priv->bank >= MAX_BANKS) {
		printf("%s: address did not match any "
		       "chip selects\n", __func__);
		kfree(priv);
		return -ENODEV;
	}

	nand = &priv->chip;
	mtd = nand_to_mtd(nand);

	ifc_ctrl->chips[priv->bank] = priv;

	/* fill in nand_chip structure */
	/* set up function call table */

	nand->write_buf = fsl_ifc_write_buf;
	nand->read_buf = fsl_ifc_read_buf;
	nand->select_chip = fsl_ifc_select_chip;
	nand->cmdfunc = fsl_ifc_cmdfunc;
	nand->waitfunc = fsl_ifc_wait;

	/* set up nand options */
	nand->bbt_td = &bbt_main_descr;
	nand->bbt_md = &bbt_mirror_descr;

	/* set up nand options */
	nand->options = NAND_NO_SUBPAGE_WRITE;
	nand->bbt_options = NAND_BBT_USE_FLASH;

	if (cspr & CSPR_PORT_SIZE_16) {
		nand->read_byte = fsl_ifc_read_byte16;
		nand->options |= NAND_BUSWIDTH_16;
	} else {
		nand->read_byte = fsl_ifc_read_byte;
	}

	nand->controller = &ifc_ctrl->controller;
	nand_set_controller_data(nand, priv);

	nand->ecc.read_page = fsl_ifc_read_page;
	nand->ecc.write_page = fsl_ifc_write_page;

	/* Hardware generates ECC per 512 Bytes */
	nand->ecc.size = 512;
	nand->ecc.bytes = 8;

	switch (csor & CSOR_NAND_PGS_MASK) {
	case CSOR_NAND_PGS_512:
		if (nand->options & NAND_BUSWIDTH_16) {
			layout = &oob_512_16bit_ecc4;
		} else {
			layout = &oob_512_8bit_ecc4;

			/* Avoid conflict with bad block marker */
			bbt_main_descr.offs = 0;
			bbt_mirror_descr.offs = 0;
		}

		nand->ecc.strength = 4;
		priv->bufnum_mask = 15;
		break;

	case CSOR_NAND_PGS_2K:
		layout = &oob_2048_ecc4;
		nand->ecc.strength = 4;
		priv->bufnum_mask = 3;
		break;

	case CSOR_NAND_PGS_4K:
		if ((csor & CSOR_NAND_ECC_MODE_MASK) ==
		    CSOR_NAND_ECC_MODE_4) {
			layout = &oob_4096_ecc4;
			nand->ecc.strength = 4;
		} else {
			layout = &oob_4096_ecc8;
			nand->ecc.strength = 8;
			nand->ecc.bytes = 16;
		}

		priv->bufnum_mask = 1;
		break;

	case CSOR_NAND_PGS_8K:
		if ((csor & CSOR_NAND_ECC_MODE_MASK) ==
		    CSOR_NAND_ECC_MODE_4) {
			layout = &oob_8192_ecc4;
			nand->ecc.strength = 4;
		} else {
			layout = &oob_8192_ecc8;
			nand->ecc.strength = 8;
			nand->ecc.bytes = 16;
		}

		priv->bufnum_mask = 0;
		break;


	default:
		printf("ifc nand: bad csor %#x: bad page size\n", csor);
		return -ENODEV;
	}

	/* Must also set CSOR_NAND_ECC_ENC_EN if DEC_EN set */
	if (csor & CSOR_NAND_ECC_DEC_EN) {
		nand->ecc.mode = NAND_ECC_HW;
		nand->ecc.layout = layout;
	} else {
		nand->ecc.mode = NAND_ECC_SOFT;
	}

	ver = ifc_in32(&gregs->ifc_rev);
	if (ver >= FSL_IFC_V1_1_0)
		ret = fsl_ifc_sram_init(priv, ver);
	if (ret)
		return ret;

	if (ver >= FSL_IFC_V2_0_0)
		priv->bufnum_mask = (priv->bufnum_mask * 2) + 1;

	ret = nand_scan_ident(mtd, 1, NULL);
	if (ret)
		return ret;

	ret = nand_scan_tail(mtd);
	if (ret)
		return ret;

	ret = nand_register(devnum, mtd);
	if (ret)
		return ret;
	return 0;
}

#ifndef CONFIG_SYS_NAND_BASE_LIST
#define CONFIG_SYS_NAND_BASE_LIST { CONFIG_SYS_NAND_BASE }
#endif

static unsigned long base_address[CONFIG_SYS_MAX_NAND_DEVICE] =
	CONFIG_SYS_NAND_BASE_LIST;

void board_nand_init(void)
{
	int i;

	for (i = 0; i < CONFIG_SYS_MAX_NAND_DEVICE; i++)
		fsl_ifc_chip_init(i, (u8 *)base_address[i]);
}
