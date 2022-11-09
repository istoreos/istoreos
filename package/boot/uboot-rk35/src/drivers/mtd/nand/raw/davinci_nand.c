/*
 * NAND driver for TI DaVinci based boards.
 *
 * Copyright (C) 2007 Sergey Kubushyn <ksi@koi8.net>
 *
 * Based on Linux DaVinci NAND driver by TI. Original copyright follows:
 */

/*
 *
 * linux/drivers/mtd/nand/raw/nand_davinci.c
 *
 * NAND Flash Driver
 *
 * Copyright (C) 2006 Texas Instruments.
 *
 * ----------------------------------------------------------------------------
 *
 * SPDX-License-Identifier:	GPL-2.0+
 *
 * ----------------------------------------------------------------------------
 *
 *  Overview:
 *   This is a device driver for the NAND flash device found on the
 *   DaVinci board which utilizes the Samsung k9k2g08 part.
 *
 Modifications:
 ver. 1.0: Feb 2005, Vinod/Sudhakar
 -
 */

#include <common.h>
#include <asm/io.h>
#include <nand.h>
#include <asm/ti-common/davinci_nand.h>

/* Definitions for 4-bit hardware ECC */
#define NAND_TIMEOUT			10240
#define NAND_ECC_BUSY			0xC
#define NAND_4BITECC_MASK		0x03FF03FF
#define EMIF_NANDFSR_ECC_STATE_MASK  	0x00000F00
#define ECC_STATE_NO_ERR		0x0
#define ECC_STATE_TOO_MANY_ERRS		0x1
#define ECC_STATE_ERR_CORR_COMP_P	0x2
#define ECC_STATE_ERR_CORR_COMP_N	0x3

/*
 * Exploit the little endianness of the ARM to do multi-byte transfers
 * per device read. This can perform over twice as quickly as individual
 * byte transfers when buffer alignment is conducive.
 *
 * NOTE: This only works if the NAND is not connected to the 2 LSBs of
 * the address bus. On Davinci EVM platforms this has always been true.
 */
static void nand_davinci_read_buf(struct mtd_info *mtd, uint8_t *buf, int len)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	const u32 *nand = chip->IO_ADDR_R;

	/* Make sure that buf is 32 bit aligned */
	if (((int)buf & 0x3) != 0) {
		if (((int)buf & 0x1) != 0) {
			if (len) {
				*buf = readb(nand);
				buf += 1;
				len--;
			}
		}

		if (((int)buf & 0x3) != 0) {
			if (len >= 2) {
				*(u16 *)buf = readw(nand);
				buf += 2;
				len -= 2;
			}
		}
	}

	/* copy aligned data */
	while (len >= 4) {
		*(u32 *)buf = __raw_readl(nand);
		buf += 4;
		len -= 4;
	}

	/* mop up any remaining bytes */
	if (len) {
		if (len >= 2) {
			*(u16 *)buf = readw(nand);
			buf += 2;
			len -= 2;
		}

		if (len)
			*buf = readb(nand);
	}
}

static void nand_davinci_write_buf(struct mtd_info *mtd, const uint8_t *buf,
				   int len)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	const u32 *nand = chip->IO_ADDR_W;

	/* Make sure that buf is 32 bit aligned */
	if (((int)buf & 0x3) != 0) {
		if (((int)buf & 0x1) != 0) {
			if (len) {
				writeb(*buf, nand);
				buf += 1;
				len--;
			}
		}

		if (((int)buf & 0x3) != 0) {
			if (len >= 2) {
				writew(*(u16 *)buf, nand);
				buf += 2;
				len -= 2;
			}
		}
	}

	/* copy aligned data */
	while (len >= 4) {
		__raw_writel(*(u32 *)buf, nand);
		buf += 4;
		len -= 4;
	}

	/* mop up any remaining bytes */
	if (len) {
		if (len >= 2) {
			writew(*(u16 *)buf, nand);
			buf += 2;
			len -= 2;
		}

		if (len)
			writeb(*buf, nand);
	}
}

static void nand_davinci_hwcontrol(struct mtd_info *mtd, int cmd,
		unsigned int ctrl)
{
	struct		nand_chip *this = mtd_to_nand(mtd);
	u_int32_t	IO_ADDR_W = (u_int32_t)this->IO_ADDR_W;

	if (ctrl & NAND_CTRL_CHANGE) {
		IO_ADDR_W &= ~(MASK_ALE|MASK_CLE);

		if (ctrl & NAND_CLE)
			IO_ADDR_W |= MASK_CLE;
		if (ctrl & NAND_ALE)
			IO_ADDR_W |= MASK_ALE;
		this->IO_ADDR_W = (void __iomem *) IO_ADDR_W;
	}

	if (cmd != NAND_CMD_NONE)
		writeb(cmd, IO_ADDR_W);
}

#ifdef CONFIG_SYS_NAND_HW_ECC

static u_int32_t nand_davinci_readecc(struct mtd_info *mtd)
{
	u_int32_t	ecc = 0;

	ecc = __raw_readl(&(davinci_emif_regs->nandfecc[
				CONFIG_SYS_NAND_CS - 2]));

	return ecc;
}

static void nand_davinci_enable_hwecc(struct mtd_info *mtd, int mode)
{
	u_int32_t	val;

	/* reading the ECC result register resets the ECC calculation */
	nand_davinci_readecc(mtd);

	val = __raw_readl(&davinci_emif_regs->nandfcr);
	val |= DAVINCI_NANDFCR_NAND_ENABLE(CONFIG_SYS_NAND_CS);
	val |= DAVINCI_NANDFCR_1BIT_ECC_START(CONFIG_SYS_NAND_CS);
	__raw_writel(val, &davinci_emif_regs->nandfcr);
}

static int nand_davinci_calculate_ecc(struct mtd_info *mtd, const u_char *dat,
		u_char *ecc_code)
{
	u_int32_t		tmp;

	tmp = nand_davinci_readecc(mtd);

	/* Squeeze 4 bytes ECC into 3 bytes by removing RESERVED bits
	 * and shifting. RESERVED bits are 31 to 28 and 15 to 12. */
	tmp = (tmp & 0x00000fff) | ((tmp & 0x0fff0000) >> 4);

	/* Invert so that erased block ECC is correct */
	tmp = ~tmp;

	*ecc_code++ = tmp;
	*ecc_code++ = tmp >>  8;
	*ecc_code++ = tmp >> 16;

	/* NOTE:  the above code matches mainline Linux:
	 *	.PQR.stu ==> ~PQRstu
	 *
	 * MontaVista/TI kernels encode those bytes differently, use
	 * complicated (and allegedly sometimes-wrong) correction code,
	 * and usually shipped with U-Boot that uses software ECC:
	 *	.PQR.stu ==> PsQRtu
	 *
	 * If you need MV/TI compatible NAND I/O in U-Boot, it should
	 * be possible to (a) change the mangling above, (b) reverse
	 * that mangling in nand_davinci_correct_data() below.
	 */

	return 0;
}

static int nand_davinci_correct_data(struct mtd_info *mtd, u_char *dat,
		u_char *read_ecc, u_char *calc_ecc)
{
	struct nand_chip *this = mtd_to_nand(mtd);
	u_int32_t ecc_nand = read_ecc[0] | (read_ecc[1] << 8) |
					  (read_ecc[2] << 16);
	u_int32_t ecc_calc = calc_ecc[0] | (calc_ecc[1] << 8) |
					  (calc_ecc[2] << 16);
	u_int32_t diff = ecc_calc ^ ecc_nand;

	if (diff) {
		if ((((diff >> 12) ^ diff) & 0xfff) == 0xfff) {
			/* Correctable error */
			if ((diff >> (12 + 3)) < this->ecc.size) {
				uint8_t find_bit = 1 << ((diff >> 12) & 7);
				uint32_t find_byte = diff >> (12 + 3);

				dat[find_byte] ^= find_bit;
				pr_debug("Correcting single "
					 "bit ECC error at offset: %d, bit: "
					 "%d\n", find_byte, find_bit);
				return 1;
			} else {
				return -EBADMSG;
			}
		} else if (!(diff & (diff - 1))) {
			/* Single bit ECC error in the ECC itself,
			   nothing to fix */
			pr_debug("Single bit ECC error in " "ECC.\n");
			return 1;
		} else {
			/* Uncorrectable error */
			pr_debug("ECC UNCORRECTED_ERROR 1\n");
			return -EBADMSG;
		}
	}
	return 0;
}
#endif /* CONFIG_SYS_NAND_HW_ECC */

#ifdef CONFIG_SYS_NAND_4BIT_HW_ECC_OOBFIRST
static struct nand_ecclayout nand_davinci_4bit_layout_oobfirst = {
#if defined(CONFIG_SYS_NAND_PAGE_2K)
	.eccbytes = 40,
#ifdef CONFIG_NAND_6BYTES_OOB_FREE_10BYTES_ECC
	.eccpos = {
		6,   7,  8,  9, 10,	11, 12, 13, 14, 15,
		22, 23, 24, 25, 26,	27, 28, 29, 30, 31,
		38, 39, 40, 41, 42,	43, 44, 45, 46, 47,
		54, 55, 56, 57, 58,	59, 60, 61, 62, 63,
	},
	.oobfree = {
		{2, 4}, {16, 6}, {32, 6}, {48, 6},
	},
#else
	.eccpos = {
		24, 25, 26, 27, 28,
		29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
		39, 40, 41, 42, 43, 44, 45, 46, 47, 48,
		49, 50, 51, 52, 53, 54, 55, 56, 57, 58,
		59, 60, 61, 62, 63,
		},
	.oobfree = {
		{.offset = 2, .length = 22, },
	},
#endif	/* #ifdef CONFIG_NAND_6BYTES_OOB_FREE_10BYTES_ECC */
#elif defined(CONFIG_SYS_NAND_PAGE_4K)
	.eccbytes = 80,
	.eccpos = {
		48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
		58, 59, 60, 61, 62, 63,	64, 65, 66, 67,
		68, 69, 70, 71, 72, 73, 74, 75, 76, 77,
		78, 79,	80, 81, 82, 83,	84, 85, 86, 87,
		88, 89, 90, 91, 92, 93,	94, 95, 96, 97,
		98, 99, 100, 101, 102, 103, 104, 105, 106, 107,
		108, 109, 110, 111, 112, 113, 114, 115, 116, 117,
		118, 119, 120, 121, 122, 123, 124, 125, 126, 127,
		},
	.oobfree = {
		{.offset = 2, .length = 46, },
	},
#endif
};

#if defined CONFIG_KEYSTONE_RBL_NAND
static struct nand_ecclayout nand_keystone_rbl_4bit_layout_oobfirst = {
#if defined(CONFIG_SYS_NAND_PAGE_2K)
	.eccbytes = 40,
	.eccpos = {
		6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
		22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
		38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
		54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
	},
	.oobfree = {
		{.offset = 2, .length = 4, },
		{.offset = 16, .length = 6, },
		{.offset = 32, .length = 6, },
		{.offset = 48, .length = 6, },
	},
#elif defined(CONFIG_SYS_NAND_PAGE_4K)
	.eccbytes = 80,
	.eccpos = {
		6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
		22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
		38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
		54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
		70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
		86, 87, 88, 89, 90, 91, 92, 93, 94, 95,
		102, 103, 104, 105, 106, 107, 108, 109, 110, 111,
		118, 119, 120, 121, 122, 123, 124, 125, 126, 127,
	},
	.oobfree = {
		{.offset = 2, .length = 4, },
		{.offset = 16, .length = 6, },
		{.offset = 32, .length = 6, },
		{.offset = 48, .length = 6, },
		{.offset = 64, .length = 6, },
		{.offset = 80, .length = 6, },
		{.offset = 96, .length = 6, },
		{.offset = 112, .length = 6, },
	},
#endif
};

#ifdef CONFIG_SYS_NAND_PAGE_2K
#define CONFIG_KEYSTONE_NAND_MAX_RBL_PAGE	CONFIG_KEYSTONE_NAND_MAX_RBL_SIZE >> 11
#elif defined(CONFIG_SYS_NAND_PAGE_4K)
#define CONFIG_KEYSTONE_NAND_MAX_RBL_PAGE	CONFIG_KEYSTONE_NAND_MAX_RBL_SIZE >> 12
#endif

/**
 * nand_davinci_write_page - write one page
 * @mtd: MTD device structure
 * @chip: NAND chip descriptor
 * @buf: the data to write
 * @oob_required: must write chip->oob_poi to OOB
 * @page: page number to write
 * @raw: use _raw version of write_page
 */
static int nand_davinci_write_page(struct mtd_info *mtd, struct nand_chip *chip,
				   uint32_t offset, int data_len,
				   const uint8_t *buf, int oob_required,
				   int page, int raw)
{
	int status;
	int ret = 0;
	struct nand_ecclayout *saved_ecc_layout;

	/* save current ECC layout and assign Keystone RBL ECC layout */
	if (page < CONFIG_KEYSTONE_NAND_MAX_RBL_PAGE) {
		saved_ecc_layout = chip->ecc.layout;
		chip->ecc.layout = &nand_keystone_rbl_4bit_layout_oobfirst;
		mtd->oobavail = chip->ecc.layout->oobavail;
	}

	chip->cmdfunc(mtd, NAND_CMD_SEQIN, 0x00, page);

	if (unlikely(raw)) {
		status = chip->ecc.write_page_raw(mtd, chip, buf,
						  oob_required, page);
	} else {
		status = chip->ecc.write_page(mtd, chip, buf,
					      oob_required, page);
	}

	if (status < 0) {
		ret = status;
		goto err;
	}

	chip->cmdfunc(mtd, NAND_CMD_PAGEPROG, -1, -1);
	status = chip->waitfunc(mtd, chip);

	if (status & NAND_STATUS_FAIL) {
		ret = -EIO;
		goto err;
	}

err:
	/* restore ECC layout */
	if (page < CONFIG_KEYSTONE_NAND_MAX_RBL_PAGE) {
		chip->ecc.layout = saved_ecc_layout;
		mtd->oobavail = saved_ecc_layout->oobavail;
	}

	return ret;
}

/**
 * nand_davinci_read_page_hwecc - hardware ECC based page read function
 * @mtd: mtd info structure
 * @chip: nand chip info structure
 * @buf: buffer to store read data
 * @oob_required: caller requires OOB data read to chip->oob_poi
 * @page: page number to read
 *
 * Not for syndrome calculating ECC controllers which need a special oob layout.
 */
static int nand_davinci_read_page_hwecc(struct mtd_info *mtd, struct nand_chip *chip,
				uint8_t *buf, int oob_required, int page)
{
	int i, eccsize = chip->ecc.size;
	int eccbytes = chip->ecc.bytes;
	int eccsteps = chip->ecc.steps;
	uint32_t *eccpos;
	uint8_t *p = buf;
	uint8_t *ecc_code = chip->buffers->ecccode;
	uint8_t *ecc_calc = chip->buffers->ecccalc;
	struct nand_ecclayout *saved_ecc_layout = chip->ecc.layout;

	/* save current ECC layout and assign Keystone RBL ECC layout */
	if (page < CONFIG_KEYSTONE_NAND_MAX_RBL_PAGE) {
		chip->ecc.layout = &nand_keystone_rbl_4bit_layout_oobfirst;
		mtd->oobavail = chip->ecc.layout->oobavail;
	}

	eccpos = chip->ecc.layout->eccpos;

	/* Read the OOB area first */
	chip->cmdfunc(mtd, NAND_CMD_READOOB, 0, page);
	chip->read_buf(mtd, chip->oob_poi, mtd->oobsize);
	chip->cmdfunc(mtd, NAND_CMD_READ0, 0, page);

	for (i = 0; i < chip->ecc.total; i++)
		ecc_code[i] = chip->oob_poi[eccpos[i]];

	for (i = 0; eccsteps; eccsteps--, i += eccbytes, p += eccsize) {
		int stat;

		chip->ecc.hwctl(mtd, NAND_ECC_READ);
		chip->read_buf(mtd, p, eccsize);
		chip->ecc.calculate(mtd, p, &ecc_calc[i]);

		stat = chip->ecc.correct(mtd, p, &ecc_code[i], NULL);
		if (stat < 0)
			mtd->ecc_stats.failed++;
		else
			mtd->ecc_stats.corrected += stat;
	}

	/* restore ECC layout */
	if (page < CONFIG_KEYSTONE_NAND_MAX_RBL_PAGE) {
		chip->ecc.layout = saved_ecc_layout;
		mtd->oobavail = saved_ecc_layout->oobavail;
	}

	return 0;
}
#endif /* CONFIG_KEYSTONE_RBL_NAND */

static void nand_davinci_4bit_enable_hwecc(struct mtd_info *mtd, int mode)
{
	u32 val;

	switch (mode) {
	case NAND_ECC_WRITE:
	case NAND_ECC_READ:
		/*
		 * Start a new ECC calculation for reading or writing 512 bytes
		 * of data.
		 */
		val = __raw_readl(&davinci_emif_regs->nandfcr);
		val &= ~DAVINCI_NANDFCR_4BIT_ECC_SEL_MASK;
		val |= DAVINCI_NANDFCR_NAND_ENABLE(CONFIG_SYS_NAND_CS);
		val |= DAVINCI_NANDFCR_4BIT_ECC_SEL(CONFIG_SYS_NAND_CS);
		val |= DAVINCI_NANDFCR_4BIT_ECC_START;
		__raw_writel(val, &davinci_emif_regs->nandfcr);
		break;
	case NAND_ECC_READSYN:
		val = __raw_readl(&davinci_emif_regs->nand4bitecc[0]);
		break;
	default:
		break;
	}
}

static u32 nand_davinci_4bit_readecc(struct mtd_info *mtd, unsigned int ecc[4])
{
	int i;

	for (i = 0; i < 4; i++) {
		ecc[i] = __raw_readl(&davinci_emif_regs->nand4bitecc[i]) &
			NAND_4BITECC_MASK;
	}

	return 0;
}

static int nand_davinci_4bit_calculate_ecc(struct mtd_info *mtd,
					   const uint8_t *dat,
					   uint8_t *ecc_code)
{
	unsigned int hw_4ecc[4];
	unsigned int i;

	nand_davinci_4bit_readecc(mtd, hw_4ecc);

	/*Convert 10 bit ecc value to 8 bit */
	for (i = 0; i < 2; i++) {
		unsigned int hw_ecc_low = hw_4ecc[i * 2];
		unsigned int hw_ecc_hi = hw_4ecc[(i * 2) + 1];

		/* Take first 8 bits from val1 (count1=0) or val5 (count1=1) */
		*ecc_code++ = hw_ecc_low & 0xFF;

		/*
		 * Take 2 bits as LSB bits from val1 (count1=0) or val5
		 * (count1=1) and 6 bits from val2 (count1=0) or
		 * val5 (count1=1)
		 */
		*ecc_code++ =
		    ((hw_ecc_low >> 8) & 0x3) | ((hw_ecc_low >> 14) & 0xFC);

		/*
		 * Take 4 bits from val2 (count1=0) or val5 (count1=1) and
		 * 4 bits from val3 (count1=0) or val6 (count1=1)
		 */
		*ecc_code++ =
		    ((hw_ecc_low >> 22) & 0xF) | ((hw_ecc_hi << 4) & 0xF0);

		/*
		 * Take 6 bits from val3(count1=0) or val6 (count1=1) and
		 * 2 bits from val4 (count1=0) or  val7 (count1=1)
		 */
		*ecc_code++ =
		    ((hw_ecc_hi >> 4) & 0x3F) | ((hw_ecc_hi >> 10) & 0xC0);

		/* Take 8 bits from val4 (count1=0) or val7 (count1=1) */
		*ecc_code++ = (hw_ecc_hi >> 18) & 0xFF;
	}

	return 0;
}

static int nand_davinci_4bit_correct_data(struct mtd_info *mtd, uint8_t *dat,
					  uint8_t *read_ecc, uint8_t *calc_ecc)
{
	int i;
	unsigned int hw_4ecc[4];
	unsigned int iserror;
	unsigned short *ecc16;
	unsigned int numerrors, erroraddress, errorvalue;
	u32 val;

	/*
	 * Check for an ECC where all bytes are 0xFF.  If this is the case, we
	 * will assume we are looking at an erased page and we should ignore
	 * the ECC.
	 */
	for (i = 0; i < 10; i++) {
		if (read_ecc[i] != 0xFF)
			break;
	}
	if (i == 10)
		return 0;

	/* Convert 8 bit in to 10 bit */
	ecc16 = (unsigned short *)&read_ecc[0];

	/*
	 * Write the parity values in the NAND Flash 4-bit ECC Load register.
	 * Write each parity value one at a time starting from 4bit_ecc_val8
	 * to 4bit_ecc_val1.
	 */

	/*Take 2 bits from 8th byte and 8 bits from 9th byte */
	__raw_writel(((ecc16[4]) >> 6) & 0x3FF,
			&davinci_emif_regs->nand4biteccload);

	/* Take 4 bits from 7th byte and 6 bits from 8th byte */
	__raw_writel((((ecc16[3]) >> 12) & 0xF) | ((((ecc16[4])) << 4) & 0x3F0),
			&davinci_emif_regs->nand4biteccload);

	/* Take 6 bits from 6th byte and 4 bits from 7th byte */
	__raw_writel((ecc16[3] >> 2) & 0x3FF,
			&davinci_emif_regs->nand4biteccload);

	/* Take 8 bits from 5th byte and 2 bits from 6th byte */
	__raw_writel(((ecc16[2]) >> 8) | ((((ecc16[3])) << 8) & 0x300),
			&davinci_emif_regs->nand4biteccload);

	/*Take 2 bits from 3rd byte and 8 bits from 4th byte */
	__raw_writel((((ecc16[1]) >> 14) & 0x3) | ((((ecc16[2])) << 2) & 0x3FC),
			&davinci_emif_regs->nand4biteccload);

	/* Take 4 bits form 2nd bytes and 6 bits from 3rd bytes */
	__raw_writel(((ecc16[1]) >> 4) & 0x3FF,
			&davinci_emif_regs->nand4biteccload);

	/* Take 6 bits from 1st byte and 4 bits from 2nd byte */
	__raw_writel((((ecc16[0]) >> 10) & 0x3F) | (((ecc16[1]) << 6) & 0x3C0),
			&davinci_emif_regs->nand4biteccload);

	/* Take 10 bits from 0th and 1st bytes */
	__raw_writel((ecc16[0]) & 0x3FF,
			&davinci_emif_regs->nand4biteccload);

	/*
	 * Perform a dummy read to the EMIF Revision Code and Status register.
	 * This is required to ensure time for syndrome calculation after
	 * writing the ECC values in previous step.
	 */

	val = __raw_readl(&davinci_emif_regs->nandfsr);

	/*
	 * Read the syndrome from the NAND Flash 4-Bit ECC 1-4 registers.
	 * A syndrome value of 0 means no bit errors. If the syndrome is
	 * non-zero then go further otherwise return.
	 */
	nand_davinci_4bit_readecc(mtd, hw_4ecc);

	if (!(hw_4ecc[0] | hw_4ecc[1] | hw_4ecc[2] | hw_4ecc[3]))
		return 0;

	/*
	 * Clear any previous address calculation by doing a dummy read of an
	 * error address register.
	 */
	val = __raw_readl(&davinci_emif_regs->nanderradd1);

	/*
	 * Set the addr_calc_st bit(bit no 13) in the NAND Flash Control
	 * register to 1.
	 */
	__raw_writel(DAVINCI_NANDFCR_4BIT_CALC_START,
			&davinci_emif_regs->nandfcr);

	/*
	 * Wait for the corr_state field (bits 8 to 11) in the
	 * NAND Flash Status register to be not equal to 0x0, 0x1, 0x2, or 0x3.
	 * Otherwise ECC calculation has not even begun and the next loop might
	 * fail because of a false positive!
	 */
	i = NAND_TIMEOUT;
	do {
		val = __raw_readl(&davinci_emif_regs->nandfsr);
		val &= 0xc00;
		i--;
	} while ((i > 0) && !val);

	/*
	 * Wait for the corr_state field (bits 8 to 11) in the
	 * NAND Flash Status register to be equal to 0x0, 0x1, 0x2, or 0x3.
	 */
	i = NAND_TIMEOUT;
	do {
		val = __raw_readl(&davinci_emif_regs->nandfsr);
		val &= 0xc00;
		i--;
	} while ((i > 0) && val);

	iserror = __raw_readl(&davinci_emif_regs->nandfsr);
	iserror &= EMIF_NANDFSR_ECC_STATE_MASK;
	iserror = iserror >> 8;

	/*
	 * ECC_STATE_TOO_MANY_ERRS (0x1) means errors cannot be
	 * corrected (five or more errors).  The number of errors
	 * calculated (err_num field) differs from the number of errors
	 * searched.  ECC_STATE_ERR_CORR_COMP_P (0x2) means error
	 * correction complete (errors on bit 8 or 9).
	 * ECC_STATE_ERR_CORR_COMP_N (0x3) means error correction
	 * complete (error exists).
	 */

	if (iserror == ECC_STATE_NO_ERR) {
		val = __raw_readl(&davinci_emif_regs->nanderrval1);
		return 0;
	} else if (iserror == ECC_STATE_TOO_MANY_ERRS) {
		val = __raw_readl(&davinci_emif_regs->nanderrval1);
		return -EBADMSG;
	}

	numerrors = ((__raw_readl(&davinci_emif_regs->nandfsr) >> 16)
			& 0x3) + 1;

	/* Read the error address, error value and correct */
	for (i = 0; i < numerrors; i++) {
		if (i > 1) {
			erroraddress =
			    ((__raw_readl(&davinci_emif_regs->nanderradd2) >>
			      (16 * (i & 1))) & 0x3FF);
			erroraddress = ((512 + 7) - erroraddress);
			errorvalue =
			    ((__raw_readl(&davinci_emif_regs->nanderrval2) >>
			      (16 * (i & 1))) & 0xFF);
		} else {
			erroraddress =
			    ((__raw_readl(&davinci_emif_regs->nanderradd1) >>
			      (16 * (i & 1))) & 0x3FF);
			erroraddress = ((512 + 7) - erroraddress);
			errorvalue =
			    ((__raw_readl(&davinci_emif_regs->nanderrval1) >>
			      (16 * (i & 1))) & 0xFF);
		}
		/* xor the corrupt data with error value */
		if (erroraddress < 512)
			dat[erroraddress] ^= errorvalue;
	}

	return numerrors;
}
#endif /* CONFIG_SYS_NAND_4BIT_HW_ECC_OOBFIRST */

static int nand_davinci_dev_ready(struct mtd_info *mtd)
{
	return __raw_readl(&davinci_emif_regs->nandfsr) & 0x1;
}

void davinci_nand_init(struct nand_chip *nand)
{
#if defined CONFIG_KEYSTONE_RBL_NAND
	int i;
	struct nand_ecclayout *layout;

	layout = &nand_keystone_rbl_4bit_layout_oobfirst;
	layout->oobavail = 0;
	for (i = 0; layout->oobfree[i].length &&
	     i < ARRAY_SIZE(layout->oobfree); i++)
		layout->oobavail += layout->oobfree[i].length;

	nand->write_page = nand_davinci_write_page;
	nand->ecc.read_page = nand_davinci_read_page_hwecc;
#endif
	nand->chip_delay  = 0;
#ifdef CONFIG_SYS_NAND_USE_FLASH_BBT
	nand->bbt_options	  |= NAND_BBT_USE_FLASH;
#endif
#ifdef CONFIG_SYS_NAND_NO_SUBPAGE_WRITE
	nand->options	  |= NAND_NO_SUBPAGE_WRITE;
#endif
#ifdef CONFIG_SYS_NAND_BUSWIDTH_16BIT
	nand->options	  |= NAND_BUSWIDTH_16;
#endif
#ifdef CONFIG_SYS_NAND_HW_ECC
	nand->ecc.mode = NAND_ECC_HW;
	nand->ecc.size = 512;
	nand->ecc.bytes = 3;
	nand->ecc.strength = 1;
	nand->ecc.calculate = nand_davinci_calculate_ecc;
	nand->ecc.correct  = nand_davinci_correct_data;
	nand->ecc.hwctl  = nand_davinci_enable_hwecc;
#else
	nand->ecc.mode = NAND_ECC_SOFT;
#endif /* CONFIG_SYS_NAND_HW_ECC */
#ifdef CONFIG_SYS_NAND_4BIT_HW_ECC_OOBFIRST
	nand->ecc.mode = NAND_ECC_HW_OOB_FIRST;
	nand->ecc.size = 512;
	nand->ecc.bytes = 10;
	nand->ecc.strength = 4;
	nand->ecc.calculate = nand_davinci_4bit_calculate_ecc;
	nand->ecc.correct = nand_davinci_4bit_correct_data;
	nand->ecc.hwctl = nand_davinci_4bit_enable_hwecc;
	nand->ecc.layout = &nand_davinci_4bit_layout_oobfirst;
#endif
	/* Set address of hardware control function */
	nand->cmd_ctrl = nand_davinci_hwcontrol;

	nand->read_buf = nand_davinci_read_buf;
	nand->write_buf = nand_davinci_write_buf;

	nand->dev_ready = nand_davinci_dev_ready;
}

int board_nand_init(struct nand_chip *chip) __attribute__((weak));

int board_nand_init(struct nand_chip *chip)
{
	davinci_nand_init(chip);
	return 0;
}
