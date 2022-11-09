/*
 * LPC32xx MLC NAND flash controller driver
 *
 * (C) Copyright 2014 3ADEV <http://3adev.com>
 * Written by Albert ARIBAUD <albert.aribaud@3adev.fr>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 *
 * NOTE:
 *
 * The MLC NAND flash controller provides hardware Reed-Solomon ECC
 * covering in- and out-of-band data together. Therefore, in- and out-
 * of-band data must be written together in order to have a valid ECC.
 *
 * Consequently, pages with meaningful in-band data are written with
 * blank (all-ones) out-of-band data and a valid ECC, and any later
 * out-of-band data write will void the ECC.
 *
 * Therefore, code which reads such late-written out-of-band data
 * should not rely on the ECC validity.
 */

#include <common.h>
#include <nand.h>
#include <linux/errno.h>
#include <asm/io.h>
#include <nand.h>
#include <asm/arch/clk.h>
#include <asm/arch/sys_proto.h>

/*
 * MLC NAND controller registers.
 */
struct lpc32xx_nand_mlc_registers {
	u8 buff[32768]; /* controller's serial data buffer */
	u8 data[32768]; /* NAND's raw data buffer */
	u32 cmd;
	u32 addr;
	u32 ecc_enc_reg;
	u32 ecc_dec_reg;
	u32 ecc_auto_enc_reg;
	u32 ecc_auto_dec_reg;
	u32 rpr;
	u32 wpr;
	u32 rubp;
	u32 robp;
	u32 sw_wp_add_low;
	u32 sw_wp_add_hig;
	u32 icr;
	u32 time_reg;
	u32 irq_mr;
	u32 irq_sr;
	u32 lock_pr;
	u32 isr;
	u32 ceh;
};

/* LOCK_PR register defines */
#define LOCK_PR_UNLOCK_KEY 0x0000A25E  /* Magic unlock value */

/* ICR defines */
#define ICR_LARGE_BLOCKS 0x00000004	/* configure for 2KB blocks */
#define ICR_ADDR4        0x00000002	/* configure for 4-word addrs */

/* CEH defines */
#define CEH_NORMAL_CE  0x00000001	/* do not force CE ON */

/* ISR register defines */
#define ISR_NAND_READY        0x00000001
#define ISR_CONTROLLER_READY  0x00000002
#define ISR_ECC_READY         0x00000004
#define ISR_DECODER_ERRORS(s) ((((s) >> 4) & 3)+1)
#define ISR_DECODER_FAILURE   0x00000040
#define ISR_DECODER_ERROR     0x00000008

/* time-out for NAND chip / controller loops, in us */
#define LPC32X_NAND_TIMEOUT 5000

/*
 * There is a single instance of the NAND MLC controller
 */

static struct lpc32xx_nand_mlc_registers __iomem *lpc32xx_nand_mlc_registers
	= (struct lpc32xx_nand_mlc_registers __iomem *)MLC_NAND_BASE;

#if !defined(CONFIG_SYS_MAX_NAND_CHIPS)
#define CONFIG_SYS_MAX_NAND_CHIPS	1
#endif

#define clkdiv(v, w, o) (((1+(clk/v)) & w) << o)

/**
 * OOB data in each small page are 6 'free' then 10 ECC bytes.
 * To make things easier, when reading large pages, the four pages'
 * 'free' OOB bytes are grouped in the first 24 bytes of the OOB buffer,
 * while the the four ECC bytes are groupe in its last 40 bytes.
 *
 * The struct below represents how free vs ecc oob bytes are stored
 * in the buffer.
 *
 * Note: the OOB bytes contain the bad block marker at offsets 0 and 1.
 */

struct lpc32xx_oob {
	struct {
		uint8_t free_oob_bytes[6];
	} free[4];
	struct {
		uint8_t ecc_oob_bytes[10];
	} ecc[4];
};

/*
 * Initialize the controller
 */

static void lpc32xx_nand_init(void)
{
	unsigned int clk;

	/* Configure controller for no software write protection, x8 bus
	   width, large block device, and 4 address words */

	/* unlock controller registers with magic key */
	writel(LOCK_PR_UNLOCK_KEY,
	       &lpc32xx_nand_mlc_registers->lock_pr);

	/* enable large blocks and large NANDs */
	writel(ICR_LARGE_BLOCKS | ICR_ADDR4,
	       &lpc32xx_nand_mlc_registers->icr);

	/* Make sure MLC interrupts are disabled */
	writel(0, &lpc32xx_nand_mlc_registers->irq_mr);

	/* Normal chip enable operation */
	writel(CEH_NORMAL_CE,
	       &lpc32xx_nand_mlc_registers->ceh);

	/* Setup NAND timing */
	clk = get_hclk_clk_rate();

	writel(
		clkdiv(CONFIG_LPC32XX_NAND_MLC_TCEA_DELAY, 0x03, 24) |
		clkdiv(CONFIG_LPC32XX_NAND_MLC_BUSY_DELAY, 0x1F, 19) |
		clkdiv(CONFIG_LPC32XX_NAND_MLC_NAND_TA,    0x07, 16) |
		clkdiv(CONFIG_LPC32XX_NAND_MLC_RD_HIGH,    0x0F, 12) |
		clkdiv(CONFIG_LPC32XX_NAND_MLC_RD_LOW,     0x0F, 8) |
		clkdiv(CONFIG_LPC32XX_NAND_MLC_WR_HIGH,    0x0F, 4) |
		clkdiv(CONFIG_LPC32XX_NAND_MLC_WR_LOW,     0x0F, 0),
		&lpc32xx_nand_mlc_registers->time_reg);
}

#if !defined(CONFIG_SPL_BUILD)

/**
 * lpc32xx_cmd_ctrl - write command to either cmd or data register
 */

static void lpc32xx_cmd_ctrl(struct mtd_info *mtd, int cmd,
				   unsigned int ctrl)
{
	if (cmd == NAND_CMD_NONE)
		return;

	if (ctrl & NAND_CLE)
		writeb(cmd & 0Xff, &lpc32xx_nand_mlc_registers->cmd);
	else if (ctrl & NAND_ALE)
		writeb(cmd & 0Xff, &lpc32xx_nand_mlc_registers->addr);
}

/**
 * lpc32xx_read_byte - read a byte from the NAND
 * @mtd:	MTD device structure
 */

static uint8_t lpc32xx_read_byte(struct mtd_info *mtd)
{
	return readb(&lpc32xx_nand_mlc_registers->data);
}

/**
 * lpc32xx_dev_ready - test if NAND device (actually controller) is ready
 * @mtd:	MTD device structure
 * @mode:	mode to set the ECC HW to.
 */

static int lpc32xx_dev_ready(struct mtd_info *mtd)
{
	/* means *controller* ready for us */
	int status = readl(&lpc32xx_nand_mlc_registers->isr);
	return status & ISR_CONTROLLER_READY;
}

/**
 * ECC layout -- this is needed whatever ECC mode we are using.
 * In a 2KB (4*512B) page, R/S codes occupy 40 (4*10) bytes.
 * To make U-Boot's life easier, we pack 'useable' OOB at the
 * front and R/S ECC at the back.
 */

static struct nand_ecclayout lpc32xx_largepage_ecclayout = {
	.eccbytes = 40,
	.eccpos = {24, 25, 26, 27, 28, 29, 30, 31, 32, 33,
		   34, 35, 36, 37, 38, 39, 40, 41, 42, 43,
		   44, 45, 46, 47, 48, 48, 50, 51, 52, 53,
		   54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
		   },
	.oobfree = {
		/* bytes 0 and 1 are used for the bad block marker */
		{
			.offset = 2,
			.length = 22
		},
	}
};

/**
 * lpc32xx_read_page_hwecc - read in- and out-of-band data with ECC
 * @mtd: mtd info structure
 * @chip: nand chip info structure
 * @buf: buffer to store read data
 * @oob_required: caller requires OOB data read to chip->oob_poi
 * @page: page number to read
 *
 * Use large block Auto Decode Read Mode(1) as described in User Manual
 * section 8.6.2.1.
 *
 * The initial Read Mode and Read Start commands are sent by the caller.
 *
 * ECC will be false if out-of-band data has been updated since in-band
 * data was initially written.
 */

static int lpc32xx_read_page_hwecc(struct mtd_info *mtd,
	struct nand_chip *chip, uint8_t *buf, int oob_required,
	int page)
{
	unsigned int i, status, timeout, err, max_bitflips = 0;
	struct lpc32xx_oob *oob = (struct lpc32xx_oob *)chip->oob_poi;

	/* go through all four small pages */
	for (i = 0; i < 4; i++) {
		/* start auto decode (reads 528 NAND bytes) */
		writel(0, &lpc32xx_nand_mlc_registers->ecc_auto_dec_reg);
		/* wait for controller to return to ready state */
		for (timeout = LPC32X_NAND_TIMEOUT; timeout; timeout--) {
			status = readl(&lpc32xx_nand_mlc_registers->isr);
			if (status & ISR_CONTROLLER_READY)
				break;
			udelay(1);
		}
		/* if decoder failed, return failure */
		if (status & ISR_DECODER_FAILURE)
			return -1;
		/* keep count of maximum bitflips performed */
		if (status & ISR_DECODER_ERROR) {
			err = ISR_DECODER_ERRORS(status);
			if (err > max_bitflips)
				max_bitflips = err;
		}
		/* copy first 512 bytes into buffer */
		memcpy(buf+512*i, lpc32xx_nand_mlc_registers->buff, 512);
		/* copy next 6 bytes at front of OOB buffer */
		memcpy(&oob->free[i], lpc32xx_nand_mlc_registers->buff, 6);
		/* copy last 10 bytes (R/S ECC) at back of OOB buffer */
		memcpy(&oob->ecc[i], lpc32xx_nand_mlc_registers->buff, 10);
	}
	return max_bitflips;
}

/**
 * lpc32xx_read_page_raw - read raw (in-band, out-of-band and ECC) data
 * @mtd: mtd info structure
 * @chip: nand chip info structure
 * @buf: buffer to store read data
 * @oob_required: caller requires OOB data read to chip->oob_poi
 * @page: page number to read
 *
 * Read NAND directly; can read pages with invalid ECC.
 */

static int lpc32xx_read_page_raw(struct mtd_info *mtd,
	struct nand_chip *chip, uint8_t *buf, int oob_required,
	int page)
{
	unsigned int i, status, timeout;
	struct lpc32xx_oob *oob = (struct lpc32xx_oob *)chip->oob_poi;

	/* when we get here we've already had the Read Mode(1) */

	/* go through all four small pages */
	for (i = 0; i < 4; i++) {
		/* wait for NAND to return to ready state */
		for (timeout = LPC32X_NAND_TIMEOUT; timeout; timeout--) {
			status = readl(&lpc32xx_nand_mlc_registers->isr);
			if (status & ISR_NAND_READY)
				break;
			udelay(1);
		}
		/* if NAND stalled, return failure */
		if (!(status & ISR_NAND_READY))
			return -1;
		/* copy first 512 bytes into buffer */
		memcpy(buf+512*i, lpc32xx_nand_mlc_registers->data, 512);
		/* copy next 6 bytes at front of OOB buffer */
		memcpy(&oob->free[i], lpc32xx_nand_mlc_registers->data, 6);
		/* copy last 10 bytes (R/S ECC) at back of OOB buffer */
		memcpy(&oob->ecc[i], lpc32xx_nand_mlc_registers->data, 10);
	}
	return 0;
}

/**
 * lpc32xx_read_oob - read out-of-band data
 * @mtd: mtd info structure
 * @chip: nand chip info structure
 * @page: page number to read
 *
 * Read out-of-band data. User Manual section 8.6.4 suggests using Read
 * Mode(3) which the controller will turn into a Read Mode(1) internally
 * but nand_base.c will turn Mode(3) into Mode(0), so let's use Mode(0)
 * directly.
 *
 * ECC covers in- and out-of-band data and was written when out-of-band
 * data was blank. Therefore, if the out-of-band being read here is not
 * blank, then the ECC will be false and the read will return bitflips,
 * even in case of ECC failure where we will return 5 bitflips. The
 * caller should be prepared to handle this.
 */

static int lpc32xx_read_oob(struct mtd_info *mtd, struct nand_chip *chip,
	int page)
{
	unsigned int i, status, timeout, err, max_bitflips = 0;
	struct lpc32xx_oob *oob = (struct lpc32xx_oob *)chip->oob_poi;

	/* No command was sent before calling read_oob() so send one */

	chip->cmdfunc(mtd, NAND_CMD_READ0, 0, page);

	/* go through all four small pages */
	for (i = 0; i < 4; i++) {
		/* start auto decode (reads 528 NAND bytes) */
		writel(0, &lpc32xx_nand_mlc_registers->ecc_auto_dec_reg);
		/* wait for controller to return to ready state */
		for (timeout = LPC32X_NAND_TIMEOUT; timeout; timeout--) {
			status = readl(&lpc32xx_nand_mlc_registers->isr);
			if (status & ISR_CONTROLLER_READY)
				break;
			udelay(1);
		}
		/* if decoder failure, count 'one too many' bitflips */
		if (status & ISR_DECODER_FAILURE)
			max_bitflips = 5;
		/* keep count of maximum bitflips performed */
		if (status & ISR_DECODER_ERROR) {
			err = ISR_DECODER_ERRORS(status);
			if (err > max_bitflips)
				max_bitflips = err;
		}
		/* set read pointer to OOB area */
		writel(0, &lpc32xx_nand_mlc_registers->robp);
		/* copy next 6 bytes at front of OOB buffer */
		memcpy(&oob->free[i], lpc32xx_nand_mlc_registers->buff, 6);
		/* copy next 10 bytes (R/S ECC) at back of OOB buffer */
		memcpy(&oob->ecc[i], lpc32xx_nand_mlc_registers->buff, 10);
	}
	return max_bitflips;
}

/**
 * lpc32xx_write_page_hwecc - write in- and out-of-band data with ECC
 * @mtd: mtd info structure
 * @chip: nand chip info structure
 * @buf: data buffer
 * @oob_required: must write chip->oob_poi to OOB
 *
 * Use large block Auto Encode as per User Manual section 8.6.4.
 *
 * The initial Write Serial Input and final Auto Program commands are
 * sent by the caller.
 */

static int lpc32xx_write_page_hwecc(struct mtd_info *mtd,
	struct nand_chip *chip, const uint8_t *buf, int oob_required,
	int page)
{
	unsigned int i, status, timeout;
	struct lpc32xx_oob *oob = (struct lpc32xx_oob *)chip->oob_poi;

	/* when we get here we've already had the SEQIN */
	for (i = 0; i < 4; i++) {
		/* start encode (expects 518 writes to buff) */
		writel(0, &lpc32xx_nand_mlc_registers->ecc_enc_reg);
		/* copy first 512 bytes from buffer */
		memcpy(&lpc32xx_nand_mlc_registers->buff, buf+512*i, 512);
		/* copy next 6 bytes from OOB buffer -- excluding ECC */
		memcpy(&lpc32xx_nand_mlc_registers->buff, &oob->free[i], 6);
		/* wait for ECC to return to ready state */
		for (timeout = LPC32X_NAND_TIMEOUT; timeout; timeout--) {
			status = readl(&lpc32xx_nand_mlc_registers->isr);
			if (status & ISR_ECC_READY)
				break;
			udelay(1);
		}
		/* if ECC stalled, return failure */
		if (!(status & ISR_ECC_READY))
			return -1;
		/* Trigger auto encode (writes 528 bytes to NAND) */
		writel(0, &lpc32xx_nand_mlc_registers->ecc_auto_enc_reg);
		/* wait for controller to return to ready state */
		for (timeout = LPC32X_NAND_TIMEOUT; timeout; timeout--) {
			status = readl(&lpc32xx_nand_mlc_registers->isr);
			if (status & ISR_CONTROLLER_READY)
				break;
			udelay(1);
		}
		/* if controller stalled, return error */
		if (!(status & ISR_CONTROLLER_READY))
			return -1;
	}
	return 0;
}

/**
 * lpc32xx_write_page_raw - write raw (in-band, out-of-band and ECC) data
 * @mtd: mtd info structure
 * @chip: nand chip info structure
 * @buf: buffer to store read data
 * @oob_required: caller requires OOB data read to chip->oob_poi
 * @page: page number to read
 *
 * Use large block write but without encode.
 *
 * The initial Write Serial Input and final Auto Program commands are
 * sent by the caller.
 *
 * This function will write the full out-of-band data, including the
 * ECC area. Therefore, it can write pages with valid *or* invalid ECC.
 */

static int lpc32xx_write_page_raw(struct mtd_info *mtd,
	struct nand_chip *chip, const uint8_t *buf, int oob_required,
	int page)
{
	unsigned int i;
	struct lpc32xx_oob *oob = (struct lpc32xx_oob *)chip->oob_poi;

	/* when we get here we've already had the Read Mode(1) */
	for (i = 0; i < 4; i++) {
		/* copy first 512 bytes from buffer */
		memcpy(lpc32xx_nand_mlc_registers->buff, buf+512*i, 512);
		/* copy next 6 bytes into OOB buffer -- excluding ECC */
		memcpy(lpc32xx_nand_mlc_registers->buff, &oob->free[i], 6);
		/* copy next 10 bytes into OOB buffer -- that is 'ECC' */
		memcpy(lpc32xx_nand_mlc_registers->buff, &oob->ecc[i], 10);
	}
	return 0;
}

/**
 * lpc32xx_write_oob - write out-of-band data
 * @mtd: mtd info structure
 * @chip: nand chip info structure
 * @page: page number to read
 *
 * Since ECC covers in- and out-of-band data, writing out-of-band data
 * with ECC will render the page ECC wrong -- or, if the page was blank,
 * then it will produce a good ECC but a later in-band data write will
 * render it wrong.
 *
 * Therefore, do not compute or write any ECC, and always return success.
 *
 * This implies that we do four writes, since non-ECC out-of-band data
 * are not contiguous in a large page.
 */

static int lpc32xx_write_oob(struct mtd_info *mtd, struct nand_chip *chip,
	int page)
{
	/* update oob on all 4 subpages in sequence */
	unsigned int i, status, timeout;
	struct lpc32xx_oob *oob = (struct lpc32xx_oob *)chip->oob_poi;

	for (i = 0; i < 4; i++) {
		/* start data input */
		chip->cmdfunc(mtd, NAND_CMD_SEQIN, 0x200+0x210*i, page);
		/* copy 6 non-ECC out-of-band bytes directly into NAND */
		memcpy(lpc32xx_nand_mlc_registers->data, &oob->free[i], 6);
		/* program page */
		chip->cmdfunc(mtd, NAND_CMD_PAGEPROG, -1, -1);
		/* wait for NAND to return to ready state */
		for (timeout = LPC32X_NAND_TIMEOUT; timeout; timeout--) {
			status = readl(&lpc32xx_nand_mlc_registers->isr);
			if (status & ISR_NAND_READY)
				break;
			udelay(1);
		}
		/* if NAND stalled, return error */
		if (!(status & ISR_NAND_READY))
			return -1;
	}
	return 0;
}

/**
 * lpc32xx_waitfunc - wait until a command is done
 * @mtd: MTD device structure
 * @chip: NAND chip structure
 *
 * Wait for controller and FLASH to both be ready.
 */

static int lpc32xx_waitfunc(struct mtd_info *mtd, struct nand_chip *chip)
{
	int status;
	unsigned int timeout;
	/* wait until both controller and NAND are ready */
	for (timeout = LPC32X_NAND_TIMEOUT; timeout; timeout--) {
		status = readl(&lpc32xx_nand_mlc_registers->isr);
		if ((status & (ISR_CONTROLLER_READY || ISR_NAND_READY))
		    == (ISR_CONTROLLER_READY || ISR_NAND_READY))
			break;
		udelay(1);
	}
	/* if controller or NAND stalled, return error */
	if ((status & (ISR_CONTROLLER_READY || ISR_NAND_READY))
	    != (ISR_CONTROLLER_READY || ISR_NAND_READY))
		return -1;
	/* write NAND status command */
	writel(NAND_CMD_STATUS, &lpc32xx_nand_mlc_registers->cmd);
	/* read back status and return it */
	return readb(&lpc32xx_nand_mlc_registers->data);
}

/*
 * We are self-initializing, so we need our own chip struct
 */

static struct nand_chip lpc32xx_chip;

/*
 * Initialize the controller
 */

void board_nand_init(void)
{
	struct mtd_info *mtd = nand_to_mtd(&lpc32xx_chip);
	int ret;

	/* Set all BOARDSPECIFIC (actually core-specific) fields  */

	lpc32xx_chip.IO_ADDR_R = &lpc32xx_nand_mlc_registers->buff;
	lpc32xx_chip.IO_ADDR_W = &lpc32xx_nand_mlc_registers->buff;
	lpc32xx_chip.cmd_ctrl = lpc32xx_cmd_ctrl;
	/* do not set init_size: nand_base.c will read sizes from chip */
	lpc32xx_chip.dev_ready = lpc32xx_dev_ready;
	/* do not set setup_read_retry: this is NAND-chip-specific */
	/* do not set chip_delay: we have dev_ready defined. */
	lpc32xx_chip.options |= NAND_NO_SUBPAGE_WRITE;

	/* Set needed ECC fields */

	lpc32xx_chip.ecc.mode = NAND_ECC_HW;
	lpc32xx_chip.ecc.layout = &lpc32xx_largepage_ecclayout;
	lpc32xx_chip.ecc.size = 512;
	lpc32xx_chip.ecc.bytes = 10;
	lpc32xx_chip.ecc.strength = 4;
	lpc32xx_chip.ecc.read_page = lpc32xx_read_page_hwecc;
	lpc32xx_chip.ecc.read_page_raw = lpc32xx_read_page_raw;
	lpc32xx_chip.ecc.write_page = lpc32xx_write_page_hwecc;
	lpc32xx_chip.ecc.write_page_raw = lpc32xx_write_page_raw;
	lpc32xx_chip.ecc.read_oob = lpc32xx_read_oob;
	lpc32xx_chip.ecc.write_oob = lpc32xx_write_oob;
	lpc32xx_chip.waitfunc = lpc32xx_waitfunc;

	lpc32xx_chip.read_byte = lpc32xx_read_byte; /* FIXME: NEEDED? */

	/* BBT options: read from last two pages */
	lpc32xx_chip.bbt_options |= NAND_BBT_USE_FLASH | NAND_BBT_LASTBLOCK
		| NAND_BBT_SCANLASTPAGE | NAND_BBT_SCAN2NDPAGE
		| NAND_BBT_WRITE;

	/* Initialize NAND interface */
	lpc32xx_nand_init();

	/* identify chip */
	ret = nand_scan_ident(mtd, CONFIG_SYS_MAX_NAND_CHIPS, NULL);
	if (ret) {
		pr_err("nand_scan_ident returned %i", ret);
		return;
	}

	/* finish scanning the chip */
	ret = nand_scan_tail(mtd);
	if (ret) {
		pr_err("nand_scan_tail returned %i", ret);
		return;
	}

	/* chip is good, register it */
	ret = nand_register(0, mtd);
	if (ret)
		pr_err("nand_register returned %i", ret);
}

#else /* defined(CONFIG_SPL_BUILD) */

void nand_init(void)
{
	/* enable NAND controller */
	lpc32xx_mlc_nand_init();
	/* initialize NAND controller */
	lpc32xx_nand_init();
}

void nand_deselect(void)
{
	/* nothing to do, but SPL requires this function */
}

static int read_single_page(uint8_t *dest, int page,
	struct lpc32xx_oob *oob)
{
	int status, i, timeout, err, max_bitflips = 0;

	/* enter read mode */
	writel(NAND_CMD_READ0, &lpc32xx_nand_mlc_registers->cmd);
	/* send column (lsb then MSB) and page (lsb to MSB) */
	writel(0, &lpc32xx_nand_mlc_registers->addr);
	writel(0, &lpc32xx_nand_mlc_registers->addr);
	writel(page & 0xff, &lpc32xx_nand_mlc_registers->addr);
	writel((page>>8) & 0xff, &lpc32xx_nand_mlc_registers->addr);
	writel((page>>16) & 0xff, &lpc32xx_nand_mlc_registers->addr);
	/* start reading */
	writel(NAND_CMD_READSTART, &lpc32xx_nand_mlc_registers->cmd);

	/* large page auto decode read */
	for (i = 0; i < 4; i++) {
		/* start auto decode (reads 528 NAND bytes) */
		writel(0, &lpc32xx_nand_mlc_registers->ecc_auto_dec_reg);
		/* wait for controller to return to ready state */
		for (timeout = LPC32X_NAND_TIMEOUT; timeout; timeout--) {
			status = readl(&lpc32xx_nand_mlc_registers->isr);
			if (status & ISR_CONTROLLER_READY)
				break;
			udelay(1);
		}
		/* if controller stalled, return error */
		if (!(status & ISR_CONTROLLER_READY))
			return -1;
		/* if decoder failure, return error */
		if (status & ISR_DECODER_FAILURE)
			return -1;
		/* keep count of maximum bitflips performed */
		if (status & ISR_DECODER_ERROR) {
			err = ISR_DECODER_ERRORS(status);
			if (err > max_bitflips)
				max_bitflips = err;
		}
		/* copy first 512 bytes into buffer */
		memcpy(dest+i*512, lpc32xx_nand_mlc_registers->buff, 512);
		/* copy next 6 bytes bytes into OOB buffer */
		memcpy(&oob->free[i], lpc32xx_nand_mlc_registers->buff, 6);
	}
	return max_bitflips;
}

/*
 * Load U-Boot signed image.
 * This loads an image from NAND, skipping bad blocks.
 * A block is declared bad if at least one of its readable pages has
 * a bad block marker in its OOB at position 0.
 * If all pages ion a block are unreadable, the block is considered
 * bad (i.e., assumed not to be part of the image) and skipped.
 *
 * IMPORTANT NOTE:
 *
 * If the first block of the image is fully unreadable, it will be
 * ignored and skipped as if it had been marked bad. If it was not
 * actually marked bad at the time of writing the image, the resulting
 * image loaded will lack a header and magic number. It could thus be
 * considered as a raw, headerless, image and SPL might erroneously
 * jump into it.
 *
 * In order to avoid this risk, LPC32XX-based boards which use this
 * driver MUST define CONFIG_SPL_PANIC_ON_RAW_IMAGE.
 */

#define BYTES_PER_PAGE 2048
#define PAGES_PER_BLOCK 64
#define BYTES_PER_BLOCK (BYTES_PER_PAGE * PAGES_PER_BLOCK)
#define PAGES_PER_CHIP_MAX 524288

int nand_spl_load_image(uint32_t offs, unsigned int size, void *dst)
{
	int bytes_left = size;
	int pages_left = DIV_ROUND_UP(size, BYTES_PER_PAGE);
	int blocks_left = DIV_ROUND_UP(size, BYTES_PER_BLOCK);
	int block = 0;
	int page = offs / BYTES_PER_PAGE;
	/* perform reads block by block */
	while (blocks_left) {
		/* compute first page number to read */
		void *block_page_dst = dst;
		/* read at most one block, possibly less */
		int block_bytes_left = bytes_left;
		if (block_bytes_left > BYTES_PER_BLOCK)
			block_bytes_left = BYTES_PER_BLOCK;
		/* keep track of good, failed, and "bad" pages */
		int block_pages_good = 0;
		int block_pages_bad = 0;
		int block_pages_err = 0;
		/* we shall read a full block of pages, maybe less */
		int block_pages_left = pages_left;
		if (block_pages_left > PAGES_PER_BLOCK)
			block_pages_left = PAGES_PER_BLOCK;
		int block_pages = block_pages_left;
		int block_page = page;
		/* while pages are left and the block is not known as bad */
		while ((block_pages > 0) && (block_pages_bad == 0)) {
			/* we will read OOB, too, for bad block markers */
			struct lpc32xx_oob oob;
			/* read page */
			int res = read_single_page(block_page_dst, block_page,
						   &oob);
			/* count readable pages */
			if (res >= 0) {
				/* this page is good */
				block_pages_good++;
				/* this page is bad */
				if ((oob.free[0].free_oob_bytes[0] != 0xff)
				    | (oob.free[0].free_oob_bytes[1] != 0xff))
					block_pages_bad++;
			} else
				/* count errors */
				block_pages_err++;
			/* we're done with this page */
			block_page++;
			block_page_dst += BYTES_PER_PAGE;
			if (block_pages)
				block_pages--;
		}
		/* a fully unreadable block is considered bad */
		if (block_pages_good == 0)
			block_pages_bad = block_pages_err;
		/* errors are fatal only in good blocks */
		if ((block_pages_err > 0) && (block_pages_bad == 0))
			return -1;
		/* we keep reads only of good blocks */
		if (block_pages_bad == 0) {
			dst += block_bytes_left;
			bytes_left -= block_bytes_left;
			pages_left -= block_pages_left;
			blocks_left--;
		}
		/* good or bad, we're done with this block */
		block++;
		page += PAGES_PER_BLOCK;
	}

	/* report success */
	return 0;
}

#endif /* CONFIG_SPL_BUILD */
