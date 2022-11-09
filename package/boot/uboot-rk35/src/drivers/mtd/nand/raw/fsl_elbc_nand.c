/* Freescale Enhanced Local Bus Controller FCM NAND driver
 *
 * Copyright (c) 2006-2008 Freescale Semiconductor
 *
 * Authors: Nick Spence <nick.spence@freescale.com>,
 *          Scott Wood <scottwood@freescale.com>
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

#ifdef VERBOSE_DEBUG
#define DEBUG_ELBC
#define vdbg(format, arg...) printf("DEBUG: " format, ##arg)
#else
#define vdbg(format, arg...) do {} while (0)
#endif

/* Can't use plain old DEBUG because the linux mtd
 * headers define it as a macro.
 */
#ifdef DEBUG_ELBC
#define dbg(format, arg...) printf("DEBUG: " format, ##arg)
#else
#define dbg(format, arg...) do {} while (0)
#endif

#define MAX_BANKS 8
#define ERR_BYTE 0xFF /* Value returned for read bytes when read failed */

#define LTESR_NAND_MASK (LTESR_FCT | LTESR_PAR | LTESR_CC)

struct fsl_elbc_ctrl;

/* mtd information per set */

struct fsl_elbc_mtd {
	struct nand_chip chip;
	struct fsl_elbc_ctrl *ctrl;

	struct device *dev;
	int bank;               /* Chip select bank number           */
	u8 __iomem *vbase;      /* Chip select base virtual address  */
	int page_size;          /* NAND page size (0=512, 1=2048)    */
	unsigned int fmr;       /* FCM Flash Mode Register value     */
};

/* overview of the fsl elbc controller */

struct fsl_elbc_ctrl {
	struct nand_hw_control controller;
	struct fsl_elbc_mtd *chips[MAX_BANKS];

	/* device info */
	fsl_lbc_t *regs;
	u8 __iomem *addr;        /* Address of assigned FCM buffer        */
	unsigned int page;       /* Last page written to / read from      */
	unsigned int read_bytes; /* Number of bytes read during command   */
	unsigned int column;     /* Saved column from SEQIN               */
	unsigned int index;      /* Pointer to next byte to 'read'        */
	unsigned int status;     /* status read from LTESR after last op  */
	unsigned int mdr;        /* UPM/FCM Data Register value           */
	unsigned int use_mdr;    /* Non zero if the MDR is to be set      */
	unsigned int oob;        /* Non zero if operating on OOB data     */
};

/* These map to the positions used by the FCM hardware ECC generator */

/* Small Page FLASH with FMR[ECCM] = 0 */
static struct nand_ecclayout fsl_elbc_oob_sp_eccm0 = {
	.eccbytes = 3,
	.eccpos = {6, 7, 8},
	.oobfree = { {0, 5}, {9, 7} },
};

/* Small Page FLASH with FMR[ECCM] = 1 */
static struct nand_ecclayout fsl_elbc_oob_sp_eccm1 = {
	.eccbytes = 3,
	.eccpos = {8, 9, 10},
	.oobfree = { {0, 5}, {6, 2}, {11, 5} },
};

/* Large Page FLASH with FMR[ECCM] = 0 */
static struct nand_ecclayout fsl_elbc_oob_lp_eccm0 = {
	.eccbytes = 12,
	.eccpos = {6, 7, 8, 22, 23, 24, 38, 39, 40, 54, 55, 56},
	.oobfree = { {1, 5}, {9, 13}, {25, 13}, {41, 13}, {57, 7} },
};

/* Large Page FLASH with FMR[ECCM] = 1 */
static struct nand_ecclayout fsl_elbc_oob_lp_eccm1 = {
	.eccbytes = 12,
	.eccpos = {8, 9, 10, 24, 25, 26, 40, 41, 42, 56, 57, 58},
	.oobfree = { {1, 7}, {11, 13}, {27, 13}, {43, 13}, {59, 5} },
};

/*
 * fsl_elbc_oob_lp_eccm* specify that LP NAND's OOB free area starts at offset
 * 1, so we have to adjust bad block pattern. This pattern should be used for
 * x8 chips only. So far hardware does not support x16 chips anyway.
 */
static u8 scan_ff_pattern[] = { 0xff, };

static struct nand_bbt_descr largepage_memorybased = {
	.options = 0,
	.offs = 0,
	.len = 1,
	.pattern = scan_ff_pattern,
};

/*
 * ELBC may use HW ECC, so that OOB offsets, that NAND core uses for bbt,
 * interfere with ECC positions, that's why we implement our own descriptors.
 * OOB {11, 5}, works for both SP and LP chips, with ECCM = 1 and ECCM = 0.
 */
static u8 bbt_pattern[] = {'B', 'b', 't', '0' };
static u8 mirror_pattern[] = {'1', 't', 'b', 'B' };

static struct nand_bbt_descr bbt_main_descr = {
	.options = NAND_BBT_LASTBLOCK | NAND_BBT_CREATE | NAND_BBT_WRITE |
		   NAND_BBT_2BIT | NAND_BBT_VERSION,
	.offs =	11,
	.len = 4,
	.veroffs = 15,
	.maxblocks = 4,
	.pattern = bbt_pattern,
};

static struct nand_bbt_descr bbt_mirror_descr = {
	.options = NAND_BBT_LASTBLOCK | NAND_BBT_CREATE | NAND_BBT_WRITE |
		   NAND_BBT_2BIT | NAND_BBT_VERSION,
	.offs =	11,
	.len = 4,
	.veroffs = 15,
	.maxblocks = 4,
	.pattern = mirror_pattern,
};

/*=================================*/

/*
 * Set up the FCM hardware block and page address fields, and the fcm
 * structure addr field to point to the correct FCM buffer in memory
 */
static void set_addr(struct mtd_info *mtd, int column, int page_addr, int oob)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct fsl_elbc_mtd *priv = nand_get_controller_data(chip);
	struct fsl_elbc_ctrl *ctrl = priv->ctrl;
	fsl_lbc_t *lbc = ctrl->regs;
	int buf_num;

	ctrl->page = page_addr;

	if (priv->page_size) {
		out_be32(&lbc->fbar, page_addr >> 6);
		out_be32(&lbc->fpar,
			 ((page_addr << FPAR_LP_PI_SHIFT) & FPAR_LP_PI) |
			 (oob ? FPAR_LP_MS : 0) | column);
		buf_num = (page_addr & 1) << 2;
	} else {
		out_be32(&lbc->fbar, page_addr >> 5);
		out_be32(&lbc->fpar,
			 ((page_addr << FPAR_SP_PI_SHIFT) & FPAR_SP_PI) |
			 (oob ? FPAR_SP_MS : 0) | column);
		buf_num = page_addr & 7;
	}

	ctrl->addr = priv->vbase + buf_num * 1024;
	ctrl->index = column;

	/* for OOB data point to the second half of the buffer */
	if (oob)
		ctrl->index += priv->page_size ? 2048 : 512;

	vdbg("set_addr: bank=%d, ctrl->addr=0x%p (0x%p), "
	     "index %x, pes %d ps %d\n",
	     buf_num, ctrl->addr, priv->vbase, ctrl->index,
	     chip->phys_erase_shift, chip->page_shift);
}

/*
 * execute FCM command and wait for it to complete
 */
static int fsl_elbc_run_command(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct fsl_elbc_mtd *priv = nand_get_controller_data(chip);
	struct fsl_elbc_ctrl *ctrl = priv->ctrl;
	fsl_lbc_t *lbc = ctrl->regs;
	u32 timeo = (CONFIG_SYS_HZ * 10) / 1000;
	u32 time_start;
	u32 ltesr;

	/* Setup the FMR[OP] to execute without write protection */
	out_be32(&lbc->fmr, priv->fmr | 3);
	if (ctrl->use_mdr)
		out_be32(&lbc->mdr, ctrl->mdr);

	vdbg("fsl_elbc_run_command: fmr=%08x fir=%08x fcr=%08x\n",
	     in_be32(&lbc->fmr), in_be32(&lbc->fir), in_be32(&lbc->fcr));
	vdbg("fsl_elbc_run_command: fbar=%08x fpar=%08x "
	     "fbcr=%08x bank=%d\n",
	     in_be32(&lbc->fbar), in_be32(&lbc->fpar),
	     in_be32(&lbc->fbcr), priv->bank);

	/* execute special operation */
	out_be32(&lbc->lsor, priv->bank);

	/* wait for FCM complete flag or timeout */
	time_start = get_timer(0);

	ltesr = 0;
	while (get_timer(time_start) < timeo) {
		ltesr = in_be32(&lbc->ltesr);
		if (ltesr & LTESR_CC)
			break;
	}

	ctrl->status = ltesr & LTESR_NAND_MASK;
	out_be32(&lbc->ltesr, ctrl->status);
	out_be32(&lbc->lteatr, 0);

	/* store mdr value in case it was needed */
	if (ctrl->use_mdr)
		ctrl->mdr = in_be32(&lbc->mdr);

	ctrl->use_mdr = 0;

	vdbg("fsl_elbc_run_command: stat=%08x mdr=%08x fmr=%08x\n",
	     ctrl->status, ctrl->mdr, in_be32(&lbc->fmr));

	/* returns 0 on success otherwise non-zero) */
	return ctrl->status == LTESR_CC ? 0 : -EIO;
}

static void fsl_elbc_do_read(struct nand_chip *chip, int oob)
{
	struct fsl_elbc_mtd *priv = nand_get_controller_data(chip);
	struct fsl_elbc_ctrl *ctrl = priv->ctrl;
	fsl_lbc_t *lbc = ctrl->regs;

	if (priv->page_size) {
		out_be32(&lbc->fir,
			 (FIR_OP_CW0 << FIR_OP0_SHIFT) |
			 (FIR_OP_CA  << FIR_OP1_SHIFT) |
			 (FIR_OP_PA  << FIR_OP2_SHIFT) |
			 (FIR_OP_CW1 << FIR_OP3_SHIFT) |
			 (FIR_OP_RBW << FIR_OP4_SHIFT));

		out_be32(&lbc->fcr, (NAND_CMD_READ0 << FCR_CMD0_SHIFT) |
				    (NAND_CMD_READSTART << FCR_CMD1_SHIFT));
	} else {
		out_be32(&lbc->fir,
			 (FIR_OP_CW0 << FIR_OP0_SHIFT) |
			 (FIR_OP_CA  << FIR_OP1_SHIFT) |
			 (FIR_OP_PA  << FIR_OP2_SHIFT) |
			 (FIR_OP_RBW << FIR_OP3_SHIFT));

		if (oob)
			out_be32(&lbc->fcr,
				 NAND_CMD_READOOB << FCR_CMD0_SHIFT);
		else
			out_be32(&lbc->fcr, NAND_CMD_READ0 << FCR_CMD0_SHIFT);
	}
}

/* cmdfunc send commands to the FCM */
static void fsl_elbc_cmdfunc(struct mtd_info *mtd, unsigned int command,
			     int column, int page_addr)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct fsl_elbc_mtd *priv = nand_get_controller_data(chip);
	struct fsl_elbc_ctrl *ctrl = priv->ctrl;
	fsl_lbc_t *lbc = ctrl->regs;

	ctrl->use_mdr = 0;

	/* clear the read buffer */
	ctrl->read_bytes = 0;
	if (command != NAND_CMD_PAGEPROG)
		ctrl->index = 0;

	switch (command) {
	/* READ0 and READ1 read the entire buffer to use hardware ECC. */
	case NAND_CMD_READ1:
		column += 256;

	/* fall-through */
	case NAND_CMD_READ0:
		vdbg("fsl_elbc_cmdfunc: NAND_CMD_READ0, page_addr:"
		     " 0x%x, column: 0x%x.\n", page_addr, column);

		out_be32(&lbc->fbcr, 0); /* read entire page to enable ECC */
		set_addr(mtd, 0, page_addr, 0);

		ctrl->read_bytes = mtd->writesize + mtd->oobsize;
		ctrl->index += column;

		fsl_elbc_do_read(chip, 0);
		fsl_elbc_run_command(mtd);
		return;

	/* READOOB reads only the OOB because no ECC is performed. */
	case NAND_CMD_READOOB:
		vdbg("fsl_elbc_cmdfunc: NAND_CMD_READOOB, page_addr:"
		     " 0x%x, column: 0x%x.\n", page_addr, column);

		out_be32(&lbc->fbcr, mtd->oobsize - column);
		set_addr(mtd, column, page_addr, 1);

		ctrl->read_bytes = mtd->writesize + mtd->oobsize;

		fsl_elbc_do_read(chip, 1);
		fsl_elbc_run_command(mtd);

		return;

	/* READID must read all 5 possible bytes while CEB is active */
	case NAND_CMD_READID:
	case NAND_CMD_PARAM:
		vdbg("fsl_elbc_cmdfunc: NAND_CMD 0x%x.\n", command);

		out_be32(&lbc->fir, (FIR_OP_CW0 << FIR_OP0_SHIFT) |
				    (FIR_OP_UA  << FIR_OP1_SHIFT) |
				    (FIR_OP_RBW << FIR_OP2_SHIFT));
		out_be32(&lbc->fcr, command << FCR_CMD0_SHIFT);
		/*
		 * although currently it's 8 bytes for READID, we always read
		 * the maximum 256 bytes(for PARAM)
		 */
		out_be32(&lbc->fbcr, 256);
		ctrl->read_bytes = 256;
		ctrl->use_mdr = 1;
		ctrl->mdr = column;
		set_addr(mtd, 0, 0, 0);
		fsl_elbc_run_command(mtd);
		return;

	/* ERASE1 stores the block and page address */
	case NAND_CMD_ERASE1:
		vdbg("fsl_elbc_cmdfunc: NAND_CMD_ERASE1, "
		     "page_addr: 0x%x.\n", page_addr);
		set_addr(mtd, 0, page_addr, 0);
		return;

	/* ERASE2 uses the block and page address from ERASE1 */
	case NAND_CMD_ERASE2:
		vdbg("fsl_elbc_cmdfunc: NAND_CMD_ERASE2.\n");

		out_be32(&lbc->fir,
			 (FIR_OP_CW0 << FIR_OP0_SHIFT) |
			 (FIR_OP_PA  << FIR_OP1_SHIFT) |
			 (FIR_OP_CM1 << FIR_OP2_SHIFT));

		out_be32(&lbc->fcr,
			 (NAND_CMD_ERASE1 << FCR_CMD0_SHIFT) |
			 (NAND_CMD_ERASE2 << FCR_CMD1_SHIFT));

		out_be32(&lbc->fbcr, 0);
		ctrl->read_bytes = 0;

		fsl_elbc_run_command(mtd);
		return;

	/* SEQIN sets up the addr buffer and all registers except the length */
	case NAND_CMD_SEQIN: {
		u32 fcr;
		vdbg("fsl_elbc_cmdfunc: NAND_CMD_SEQIN/PAGE_PROG, "
		     "page_addr: 0x%x, column: 0x%x.\n",
		     page_addr, column);

		ctrl->column = column;
		ctrl->oob = 0;

		if (priv->page_size) {
			fcr = (NAND_CMD_SEQIN << FCR_CMD0_SHIFT) |
			      (NAND_CMD_PAGEPROG << FCR_CMD1_SHIFT);

			out_be32(&lbc->fir,
				 (FIR_OP_CW0 << FIR_OP0_SHIFT) |
				 (FIR_OP_CA  << FIR_OP1_SHIFT) |
				 (FIR_OP_PA  << FIR_OP2_SHIFT) |
				 (FIR_OP_WB  << FIR_OP3_SHIFT) |
				 (FIR_OP_CW1 << FIR_OP4_SHIFT));
		} else {
			fcr = (NAND_CMD_PAGEPROG << FCR_CMD1_SHIFT) |
			      (NAND_CMD_SEQIN << FCR_CMD2_SHIFT);

			out_be32(&lbc->fir,
				 (FIR_OP_CW0 << FIR_OP0_SHIFT) |
				 (FIR_OP_CM2 << FIR_OP1_SHIFT) |
				 (FIR_OP_CA  << FIR_OP2_SHIFT) |
				 (FIR_OP_PA  << FIR_OP3_SHIFT) |
				 (FIR_OP_WB  << FIR_OP4_SHIFT) |
				 (FIR_OP_CW1 << FIR_OP5_SHIFT));

			if (column >= mtd->writesize) {
				/* OOB area --> READOOB */
				column -= mtd->writesize;
				fcr |= NAND_CMD_READOOB << FCR_CMD0_SHIFT;
				ctrl->oob = 1;
			} else if (column < 256) {
				/* First 256 bytes --> READ0 */
				fcr |= NAND_CMD_READ0 << FCR_CMD0_SHIFT;
			} else {
				/* Second 256 bytes --> READ1 */
				fcr |= NAND_CMD_READ1 << FCR_CMD0_SHIFT;
			}
		}

		out_be32(&lbc->fcr, fcr);
		set_addr(mtd, column, page_addr, ctrl->oob);
		return;
	}

	/* PAGEPROG reuses all of the setup from SEQIN and adds the length */
	case NAND_CMD_PAGEPROG: {
		vdbg("fsl_elbc_cmdfunc: NAND_CMD_PAGEPROG "
		     "writing %d bytes.\n", ctrl->index);

		/* if the write did not start at 0 or is not a full page
		 * then set the exact length, otherwise use a full page
		 * write so the HW generates the ECC.
		 */
		if (ctrl->oob || ctrl->column != 0 ||
		    ctrl->index != mtd->writesize + mtd->oobsize)
			out_be32(&lbc->fbcr, ctrl->index);
		else
			out_be32(&lbc->fbcr, 0);

		fsl_elbc_run_command(mtd);

		return;
	}

	/* CMD_STATUS must read the status byte while CEB is active */
	/* Note - it does not wait for the ready line */
	case NAND_CMD_STATUS:
		out_be32(&lbc->fir,
			 (FIR_OP_CM0 << FIR_OP0_SHIFT) |
			 (FIR_OP_RBW << FIR_OP1_SHIFT));
		out_be32(&lbc->fcr, NAND_CMD_STATUS << FCR_CMD0_SHIFT);
		out_be32(&lbc->fbcr, 1);
		set_addr(mtd, 0, 0, 0);
		ctrl->read_bytes = 1;

		fsl_elbc_run_command(mtd);

		/* The chip always seems to report that it is
		 * write-protected, even when it is not.
		 */
		out_8(ctrl->addr, in_8(ctrl->addr) | NAND_STATUS_WP);
		return;

	/* RESET without waiting for the ready line */
	case NAND_CMD_RESET:
		dbg("fsl_elbc_cmdfunc: NAND_CMD_RESET.\n");
		out_be32(&lbc->fir, FIR_OP_CM0 << FIR_OP0_SHIFT);
		out_be32(&lbc->fcr, NAND_CMD_RESET << FCR_CMD0_SHIFT);
		fsl_elbc_run_command(mtd);
		return;

	default:
		printf("fsl_elbc_cmdfunc: error, unsupported command 0x%x.\n",
			command);
	}
}

static void fsl_elbc_select_chip(struct mtd_info *mtd, int chip)
{
	/* The hardware does not seem to support multiple
	 * chips per bank.
	 */
}

/*
 * Write buf to the FCM Controller Data Buffer
 */
static void fsl_elbc_write_buf(struct mtd_info *mtd, const u8 *buf, int len)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct fsl_elbc_mtd *priv = nand_get_controller_data(chip);
	struct fsl_elbc_ctrl *ctrl = priv->ctrl;
	unsigned int bufsize = mtd->writesize + mtd->oobsize;

	if (len <= 0) {
		printf("write_buf of %d bytes", len);
		ctrl->status = 0;
		return;
	}

	if ((unsigned int)len > bufsize - ctrl->index) {
		printf("write_buf beyond end of buffer "
		       "(%d requested, %u available)\n",
		       len, bufsize - ctrl->index);
		len = bufsize - ctrl->index;
	}

	memcpy_toio(&ctrl->addr[ctrl->index], buf, len);
	/*
	 * This is workaround for the weird elbc hangs during nand write,
	 * Scott Wood says: "...perhaps difference in how long it takes a
	 * write to make it through the localbus compared to a write to IMMR
	 * is causing problems, and sync isn't helping for some reason."
	 * Reading back the last byte helps though.
	 */
	in_8(&ctrl->addr[ctrl->index] + len - 1);

	ctrl->index += len;
}

/*
 * read a byte from either the FCM hardware buffer if it has any data left
 * otherwise issue a command to read a single byte.
 */
static u8 fsl_elbc_read_byte(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct fsl_elbc_mtd *priv = nand_get_controller_data(chip);
	struct fsl_elbc_ctrl *ctrl = priv->ctrl;

	/* If there are still bytes in the FCM, then use the next byte. */
	if (ctrl->index < ctrl->read_bytes)
		return in_8(&ctrl->addr[ctrl->index++]);

	printf("read_byte beyond end of buffer\n");
	return ERR_BYTE;
}

/*
 * Read from the FCM Controller Data Buffer
 */
static void fsl_elbc_read_buf(struct mtd_info *mtd, u8 *buf, int len)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct fsl_elbc_mtd *priv = nand_get_controller_data(chip);
	struct fsl_elbc_ctrl *ctrl = priv->ctrl;
	int avail;

	if (len < 0)
		return;

	avail = min((unsigned int)len, ctrl->read_bytes - ctrl->index);
	memcpy_fromio(buf, &ctrl->addr[ctrl->index], avail);
	ctrl->index += avail;

	if (len > avail)
		printf("read_buf beyond end of buffer "
		       "(%d requested, %d available)\n",
		       len, avail);
}

/* This function is called after Program and Erase Operations to
 * check for success or failure.
 */
static int fsl_elbc_wait(struct mtd_info *mtd, struct nand_chip *chip)
{
	struct fsl_elbc_mtd *priv = nand_get_controller_data(chip);
	struct fsl_elbc_ctrl *ctrl = priv->ctrl;
	fsl_lbc_t *lbc = ctrl->regs;

	if (ctrl->status != LTESR_CC)
		return NAND_STATUS_FAIL;

	/* Use READ_STATUS command, but wait for the device to be ready */
	ctrl->use_mdr = 0;
	out_be32(&lbc->fir,
		 (FIR_OP_CW0 << FIR_OP0_SHIFT) |
		 (FIR_OP_RBW << FIR_OP1_SHIFT));
	out_be32(&lbc->fcr, NAND_CMD_STATUS << FCR_CMD0_SHIFT);
	out_be32(&lbc->fbcr, 1);
	set_addr(mtd, 0, 0, 0);
	ctrl->read_bytes = 1;

	fsl_elbc_run_command(mtd);

	if (ctrl->status != LTESR_CC)
		return NAND_STATUS_FAIL;

	/* The chip always seems to report that it is
	 * write-protected, even when it is not.
	 */
	out_8(ctrl->addr, in_8(ctrl->addr) | NAND_STATUS_WP);
	return fsl_elbc_read_byte(mtd);
}

static int fsl_elbc_read_page(struct mtd_info *mtd, struct nand_chip *chip,
			      uint8_t *buf, int oob_required, int page)
{
	fsl_elbc_read_buf(mtd, buf, mtd->writesize);
	fsl_elbc_read_buf(mtd, chip->oob_poi, mtd->oobsize);

	if (fsl_elbc_wait(mtd, chip) & NAND_STATUS_FAIL)
		mtd->ecc_stats.failed++;

	return 0;
}

/* ECC will be calculated automatically, and errors will be detected in
 * waitfunc.
 */
static int fsl_elbc_write_page(struct mtd_info *mtd, struct nand_chip *chip,
				const uint8_t *buf, int oob_required,
				int page)
{
	fsl_elbc_write_buf(mtd, buf, mtd->writesize);
	fsl_elbc_write_buf(mtd, chip->oob_poi, mtd->oobsize);

	return 0;
}

static struct fsl_elbc_ctrl *elbc_ctrl;

/* ECC will be calculated automatically, and errors will be detected in
 * waitfunc.
 */
static int fsl_elbc_write_subpage(struct mtd_info *mtd, struct nand_chip *chip,
				uint32_t offset, uint32_t data_len,
				const uint8_t *buf, int oob_required, int page)
{
	fsl_elbc_write_buf(mtd, buf, mtd->writesize);
	fsl_elbc_write_buf(mtd, chip->oob_poi, mtd->oobsize);

	return 0;
}

static void fsl_elbc_ctrl_init(void)
{
	elbc_ctrl = kzalloc(sizeof(*elbc_ctrl), GFP_KERNEL);
	if (!elbc_ctrl)
		return;

	elbc_ctrl->regs = LBC_BASE_ADDR;

	/* clear event registers */
	out_be32(&elbc_ctrl->regs->ltesr, LTESR_NAND_MASK);
	out_be32(&elbc_ctrl->regs->lteatr, 0);

	/* Enable interrupts for any detected events */
	out_be32(&elbc_ctrl->regs->lteir, LTESR_NAND_MASK);

	elbc_ctrl->read_bytes = 0;
	elbc_ctrl->index = 0;
	elbc_ctrl->addr = NULL;
}

static int fsl_elbc_chip_init(int devnum, u8 *addr)
{
	struct mtd_info *mtd;
	struct nand_chip *nand;
	struct fsl_elbc_mtd *priv;
	uint32_t br = 0, or = 0;
	int ret;

	if (!elbc_ctrl) {
		fsl_elbc_ctrl_init();
		if (!elbc_ctrl)
			return -1;
	}

	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->ctrl = elbc_ctrl;
	priv->vbase = addr;

	/* Find which chip select it is connected to.  It'd be nice
	 * if we could pass more than one datum to the NAND driver...
	 */
	for (priv->bank = 0; priv->bank < MAX_BANKS; priv->bank++) {
		phys_addr_t phys_addr = virt_to_phys(addr);

		br = in_be32(&elbc_ctrl->regs->bank[priv->bank].br);
		or = in_be32(&elbc_ctrl->regs->bank[priv->bank].or);

		if ((br & BR_V) && (br & BR_MSEL) == BR_MS_FCM &&
		    (br & or & BR_BA) == BR_PHYS_ADDR(phys_addr))
			break;
	}

	if (priv->bank >= MAX_BANKS) {
		printf("fsl_elbc_nand: address did not match any "
		       "chip selects\n");
		kfree(priv);
		return -ENODEV;
	}

	nand = &priv->chip;
	mtd = nand_to_mtd(nand);

	elbc_ctrl->chips[priv->bank] = priv;

	/* fill in nand_chip structure */
	/* set up function call table */
	nand->read_byte = fsl_elbc_read_byte;
	nand->write_buf = fsl_elbc_write_buf;
	nand->read_buf = fsl_elbc_read_buf;
	nand->select_chip = fsl_elbc_select_chip;
	nand->cmdfunc = fsl_elbc_cmdfunc;
	nand->waitfunc = fsl_elbc_wait;

	/* set up nand options */
	nand->bbt_td = &bbt_main_descr;
	nand->bbt_md = &bbt_mirror_descr;

  	/* set up nand options */
	nand->options = NAND_NO_SUBPAGE_WRITE;
	nand->bbt_options = NAND_BBT_USE_FLASH;

	nand->controller = &elbc_ctrl->controller;
	nand_set_controller_data(nand, priv);

	nand->ecc.read_page = fsl_elbc_read_page;
	nand->ecc.write_page = fsl_elbc_write_page;
	nand->ecc.write_subpage = fsl_elbc_write_subpage;

	priv->fmr = (15 << FMR_CWTO_SHIFT) | (2 << FMR_AL_SHIFT);

	/* If CS Base Register selects full hardware ECC then use it */
	if ((br & BR_DECC) == BR_DECC_CHK_GEN) {
		nand->ecc.mode = NAND_ECC_HW;

		nand->ecc.layout = (priv->fmr & FMR_ECCM) ?
				   &fsl_elbc_oob_sp_eccm1 :
				   &fsl_elbc_oob_sp_eccm0;

		nand->ecc.size = 512;
		nand->ecc.bytes = 3;
		nand->ecc.steps = 1;
		nand->ecc.strength = 1;
	} else {
		/* otherwise fall back to software ECC */
#if defined(CONFIG_NAND_ECC_BCH)
		nand->ecc.mode = NAND_ECC_SOFT_BCH;
#else
		nand->ecc.mode = NAND_ECC_SOFT;
#endif
	}

	ret = nand_scan_ident(mtd, 1, NULL);
	if (ret)
		return ret;

	/* Large-page-specific setup */
	if (mtd->writesize == 2048) {
		setbits_be32(&elbc_ctrl->regs->bank[priv->bank].or,
			     OR_FCM_PGS);
		in_be32(&elbc_ctrl->regs->bank[priv->bank].or);

		priv->page_size = 1;
		nand->badblock_pattern = &largepage_memorybased;

		/*
		 * Hardware expects small page has ECCM0, large page has
		 * ECCM1 when booting from NAND, and we follow that even
		 * when not booting from NAND.
		 */
		priv->fmr |= FMR_ECCM;

		/* adjust ecc setup if needed */
		if ((br & BR_DECC) == BR_DECC_CHK_GEN) {
			nand->ecc.steps = 4;
			nand->ecc.layout = (priv->fmr & FMR_ECCM) ?
					   &fsl_elbc_oob_lp_eccm1 :
					   &fsl_elbc_oob_lp_eccm0;
		}
	} else if (mtd->writesize == 512) {
		clrbits_be32(&elbc_ctrl->regs->bank[priv->bank].or,
			     OR_FCM_PGS);
		in_be32(&elbc_ctrl->regs->bank[priv->bank].or);
	} else {
		return -ENODEV;
	}

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
		fsl_elbc_chip_init(i, (u8 *)base_address[i]);
}
