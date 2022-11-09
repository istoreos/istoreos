/*
 * This file provides ECC correction for more than 1 bit per block of data,
 * using binary BCH codes. It relies on the generic BCH library lib/bch.c.
 *
 * Copyright © 2011 Ivan Djelic <ivan.djelic@parrot.com>
 *
  * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
/*#include <asm/io.h>*/
#include <linux/types.h>

#include <linux/bitops.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/rawnand.h>
#include <linux/mtd/nand_bch.h>
#include <linux/bch.h>
#include <malloc.h>

/**
 * struct nand_bch_control - private NAND BCH control structure
 * @bch:       BCH control structure
 * @ecclayout: private ecc layout for this BCH configuration
 * @errloc:    error location array
 * @eccmask:   XOR ecc mask, allows erased pages to be decoded as valid
 */
struct nand_bch_control {
	struct bch_control   *bch;
	struct nand_ecclayout ecclayout;
	unsigned int         *errloc;
	unsigned char        *eccmask;
};

/**
 * nand_bch_calculate_ecc - [NAND Interface] Calculate ECC for data block
 * @mtd:	MTD block structure
 * @buf:	input buffer with raw data
 * @code:	output buffer with ECC
 */
int nand_bch_calculate_ecc(struct mtd_info *mtd, const unsigned char *buf,
			   unsigned char *code)
{
	const struct nand_chip *chip = mtd_to_nand(mtd);
	struct nand_bch_control *nbc = chip->ecc.priv;
	unsigned int i;

	memset(code, 0, chip->ecc.bytes);
	encode_bch(nbc->bch, buf, chip->ecc.size, code);

	/* apply mask so that an erased page is a valid codeword */
	for (i = 0; i < chip->ecc.bytes; i++)
		code[i] ^= nbc->eccmask[i];

	return 0;
}

/**
 * nand_bch_correct_data - [NAND Interface] Detect and correct bit error(s)
 * @mtd:	MTD block structure
 * @buf:	raw data read from the chip
 * @read_ecc:	ECC from the chip
 * @calc_ecc:	the ECC calculated from raw data
 *
 * Detect and correct bit errors for a data byte block
 */
int nand_bch_correct_data(struct mtd_info *mtd, unsigned char *buf,
			  unsigned char *read_ecc, unsigned char *calc_ecc)
{
	const struct nand_chip *chip = mtd_to_nand(mtd);
	struct nand_bch_control *nbc = chip->ecc.priv;
	unsigned int *errloc = nbc->errloc;
	int i, count;

	count = decode_bch(nbc->bch, NULL, chip->ecc.size, read_ecc, calc_ecc,
			   NULL, errloc);
	if (count > 0) {
		for (i = 0; i < count; i++) {
			if (errloc[i] < (chip->ecc.size*8))
				/* error is located in data, correct it */
				buf[errloc[i] >> 3] ^= (1 << (errloc[i] & 7));
			/* else error in ecc, no action needed */

			pr_debug("%s: corrected bitflip %u\n",
				 __func__, errloc[i]);
		}
	} else if (count < 0) {
		printk(KERN_ERR "ecc unrecoverable error\n");
		count = -EBADMSG;
	}
	return count;
}

/**
 * nand_bch_init - [NAND Interface] Initialize NAND BCH error correction
 * @mtd:	MTD block structure
 *
 * Returns:
 *  a pointer to a new NAND BCH control structure, or NULL upon failure
 *
 * Initialize NAND BCH error correction. Parameters @eccsize and @eccbytes
 * are used to compute BCH parameters m (Galois field order) and t (error
 * correction capability). @eccbytes should be equal to the number of bytes
 * required to store m*t bits, where m is such that 2^m-1 > @eccsize*8.
 *
 * Example: to configure 4 bit correction per 512 bytes, you should pass
 * @eccsize = 512  (thus, m=13 is the smallest integer such that 2^m-1 > 512*8)
 * @eccbytes = 7   (7 bytes are required to store m*t = 13*4 = 52 bits)
 */
struct nand_bch_control *nand_bch_init(struct mtd_info *mtd)
{
	struct nand_chip *nand = mtd_to_nand(mtd);
	unsigned int m, t, eccsteps, i;
	struct nand_ecclayout *layout = nand->ecc.layout;
	struct nand_bch_control *nbc = NULL;
	unsigned char *erased_page;
	unsigned int eccsize = nand->ecc.size;
	unsigned int eccbytes = nand->ecc.bytes;
	unsigned int eccstrength = nand->ecc.strength;

	if (!eccbytes && eccstrength) {
		eccbytes = DIV_ROUND_UP(eccstrength * fls(8 * eccsize), 8);
		nand->ecc.bytes = eccbytes;
	}

	if (!eccsize || !eccbytes) {
		printk(KERN_WARNING "ecc parameters not supplied\n");
		goto fail;
	}

	m = fls(1+8*eccsize);
	t = (eccbytes*8)/m;

	nbc = kzalloc(sizeof(*nbc), GFP_KERNEL);
	if (!nbc)
		goto fail;

	nbc->bch = init_bch(m, t, 0);
	if (!nbc->bch)
		goto fail;

	/* verify that eccbytes has the expected value */
	if (nbc->bch->ecc_bytes != eccbytes) {
		printk(KERN_WARNING "invalid eccbytes %u, should be %u\n",
		       eccbytes, nbc->bch->ecc_bytes);
		goto fail;
	}

	eccsteps = mtd->writesize/eccsize;

	/* if no ecc placement scheme was provided, build one */
	if (!layout) {

		/* handle large page devices only */
		if (mtd->oobsize < 64) {
			printk(KERN_WARNING "must provide an oob scheme for "
			       "oobsize %d\n", mtd->oobsize);
			goto fail;
		}

		layout = &nbc->ecclayout;
		layout->eccbytes = eccsteps*eccbytes;

		/* reserve 2 bytes for bad block marker */
		if (layout->eccbytes+2 > mtd->oobsize) {
			printk(KERN_WARNING "no suitable oob scheme available "
			       "for oobsize %d eccbytes %u\n", mtd->oobsize,
			       eccbytes);
			goto fail;
		}
		/* put ecc bytes at oob tail */
		for (i = 0; i < layout->eccbytes; i++)
			layout->eccpos[i] = mtd->oobsize-layout->eccbytes+i;

		layout->oobfree[0].offset = 2;
		layout->oobfree[0].length = mtd->oobsize-2-layout->eccbytes;

		nand->ecc.layout = layout;
	}

	/* sanity checks */
	if (8*(eccsize+eccbytes) >= (1 << m)) {
		printk(KERN_WARNING "eccsize %u is too large\n", eccsize);
		goto fail;
	}
	if (layout->eccbytes != (eccsteps*eccbytes)) {
		printk(KERN_WARNING "invalid ecc layout\n");
		goto fail;
	}

	nbc->eccmask = kmalloc(eccbytes, GFP_KERNEL);
	nbc->errloc = kmalloc(t*sizeof(*nbc->errloc), GFP_KERNEL);
	if (!nbc->eccmask || !nbc->errloc)
		goto fail;
	/*
	 * compute and store the inverted ecc of an erased ecc block
	 */
	erased_page = kmalloc(eccsize, GFP_KERNEL);
	if (!erased_page)
		goto fail;

	memset(erased_page, 0xff, eccsize);
	memset(nbc->eccmask, 0, eccbytes);
	encode_bch(nbc->bch, erased_page, eccsize, nbc->eccmask);
	kfree(erased_page);

	for (i = 0; i < eccbytes; i++)
		nbc->eccmask[i] ^= 0xff;

	if (!eccstrength)
		nand->ecc.strength = (eccbytes * 8) / fls(8 * eccsize);

	return nbc;
fail:
	nand_bch_free(nbc);
	return NULL;
}

/**
 * nand_bch_free - [NAND Interface] Release NAND BCH ECC resources
 * @nbc:	NAND BCH control structure
 */
void nand_bch_free(struct nand_bch_control *nbc)
{
	if (nbc) {
		free_bch(nbc->bch);
		kfree(nbc->errloc);
		kfree(nbc->eccmask);
		kfree(nbc);
	}
}
