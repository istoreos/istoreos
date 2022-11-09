/*
 * (C) Copyright 2010
 * Vipin Kumar, ST Microelectronics, vipin.kumar@st.com.
 *
 * (C) Copyright 2012
 * Amit Virdi, ST Microelectronics, amit.virdi@st.com.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <nand.h>
#include <asm/io.h>
#include <linux/bitops.h>
#include <linux/err.h>
#include <linux/mtd/nand_ecc.h>
#include <linux/mtd/fsmc_nand.h>
#include <asm/arch/hardware.h>

static u32 fsmc_version;
static struct fsmc_regs *const fsmc_regs_p = (struct fsmc_regs *)
	CONFIG_SYS_FSMC_BASE;

/*
 * ECC4 and ECC1 have 13 bytes and 3 bytes of ecc respectively for 512 bytes of
 * data. ECC4 can correct up to 8 bits in 512 bytes of data while ECC1 can
 * correct 1 bit in 512 bytes
 */

static struct nand_ecclayout fsmc_ecc4_lp_layout = {
	.eccbytes = 104,
	.eccpos = {  2,   3,   4,   5,   6,   7,   8,
		9,  10,  11,  12,  13,  14,
		18,  19,  20,  21,  22,  23,  24,
		25,  26,  27,  28,  29,  30,
		34,  35,  36,  37,  38,  39,  40,
		41,  42,  43,  44,  45,  46,
		50,  51,  52,  53,  54,  55,  56,
		57,  58,  59,  60,  61,  62,
		66,  67,  68,  69,  70,  71,  72,
		73,  74,  75,  76,  77,  78,
		82,  83,  84,  85,  86,  87,  88,
		89,  90,  91,  92,  93,  94,
		98,  99, 100, 101, 102, 103, 104,
		105, 106, 107, 108, 109, 110,
		114, 115, 116, 117, 118, 119, 120,
		121, 122, 123, 124, 125, 126
	},
	.oobfree = {
		{.offset = 15, .length = 3},
		{.offset = 31, .length = 3},
		{.offset = 47, .length = 3},
		{.offset = 63, .length = 3},
		{.offset = 79, .length = 3},
		{.offset = 95, .length = 3},
		{.offset = 111, .length = 3},
		{.offset = 127, .length = 1}
	}
};

/*
 * ECC4 layout for NAND of pagesize 4096 bytes & OOBsize 224 bytes. 13*8 bytes
 * of OOB size is reserved for ECC, Byte no. 0 & 1 reserved for bad block & 118
 * bytes are free for use.
 */
static struct nand_ecclayout fsmc_ecc4_224_layout = {
	.eccbytes = 104,
	.eccpos = {  2,   3,   4,   5,   6,   7,   8,
		9,  10,  11,  12,  13,  14,
		18,  19,  20,  21,  22,  23,  24,
		25,  26,  27,  28,  29,  30,
		34,  35,  36,  37,  38,  39,  40,
		41,  42,  43,  44,  45,  46,
		50,  51,  52,  53,  54,  55,  56,
		57,  58,  59,  60,  61,  62,
		66,  67,  68,  69,  70,  71,  72,
		73,  74,  75,  76,  77,  78,
		82,  83,  84,  85,  86,  87,  88,
		89,  90,  91,  92,  93,  94,
		98,  99, 100, 101, 102, 103, 104,
		105, 106, 107, 108, 109, 110,
		114, 115, 116, 117, 118, 119, 120,
		121, 122, 123, 124, 125, 126
	},
	.oobfree = {
		{.offset = 15, .length = 3},
		{.offset = 31, .length = 3},
		{.offset = 47, .length = 3},
		{.offset = 63, .length = 3},
		{.offset = 79, .length = 3},
		{.offset = 95, .length = 3},
		{.offset = 111, .length = 3},
		{.offset = 127, .length = 97}
	}
};

/*
 * ECC placement definitions in oobfree type format
 * There are 13 bytes of ecc for every 512 byte block and it has to be read
 * consecutively and immediately after the 512 byte data block for hardware to
 * generate the error bit offsets in 512 byte data
 * Managing the ecc bytes in the following way makes it easier for software to
 * read ecc bytes consecutive to data bytes. This way is similar to
 * oobfree structure maintained already in u-boot nand driver
 */
static struct fsmc_eccplace fsmc_eccpl_lp = {
	.eccplace = {
		{.offset = 2, .length = 13},
		{.offset = 18, .length = 13},
		{.offset = 34, .length = 13},
		{.offset = 50, .length = 13},
		{.offset = 66, .length = 13},
		{.offset = 82, .length = 13},
		{.offset = 98, .length = 13},
		{.offset = 114, .length = 13}
	}
};

static struct nand_ecclayout fsmc_ecc4_sp_layout = {
	.eccbytes = 13,
	.eccpos = { 0,  1,  2,  3,  6,  7, 8,
		9, 10, 11, 12, 13, 14
	},
	.oobfree = {
		{.offset = 15, .length = 1},
	}
};

static struct fsmc_eccplace fsmc_eccpl_sp = {
	.eccplace = {
		{.offset = 0, .length = 4},
		{.offset = 6, .length = 9}
	}
};

static struct nand_ecclayout fsmc_ecc1_layout = {
	.eccbytes = 24,
	.eccpos = {2, 3, 4, 18, 19, 20, 34, 35, 36, 50, 51, 52,
		66, 67, 68, 82, 83, 84, 98, 99, 100, 114, 115, 116},
	.oobfree = {
		{.offset = 8, .length = 8},
		{.offset = 24, .length = 8},
		{.offset = 40, .length = 8},
		{.offset = 56, .length = 8},
		{.offset = 72, .length = 8},
		{.offset = 88, .length = 8},
		{.offset = 104, .length = 8},
		{.offset = 120, .length = 8}
	}
};

/* Count the number of 0's in buff upto a max of max_bits */
static int count_written_bits(uint8_t *buff, int size, int max_bits)
{
	int k, written_bits = 0;

	for (k = 0; k < size; k++) {
		written_bits += hweight8(~buff[k]);
		if (written_bits > max_bits)
			break;
	}

	return written_bits;
}

static void fsmc_nand_hwcontrol(struct mtd_info *mtd, int cmd, uint ctrl)
{
	struct nand_chip *this = mtd_to_nand(mtd);
	ulong IO_ADDR_W;

	if (ctrl & NAND_CTRL_CHANGE) {
		IO_ADDR_W = (ulong)this->IO_ADDR_W;

		IO_ADDR_W &= ~(CONFIG_SYS_NAND_CLE | CONFIG_SYS_NAND_ALE);
		if (ctrl & NAND_CLE)
			IO_ADDR_W |= CONFIG_SYS_NAND_CLE;
		if (ctrl & NAND_ALE)
			IO_ADDR_W |= CONFIG_SYS_NAND_ALE;

		if (ctrl & NAND_NCE) {
			writel(readl(&fsmc_regs_p->pc) |
					FSMC_ENABLE, &fsmc_regs_p->pc);
		} else {
			writel(readl(&fsmc_regs_p->pc) &
					~FSMC_ENABLE, &fsmc_regs_p->pc);
		}
		this->IO_ADDR_W = (void *)IO_ADDR_W;
	}

	if (cmd != NAND_CMD_NONE)
		writeb(cmd, this->IO_ADDR_W);
}

static int fsmc_bch8_correct_data(struct mtd_info *mtd, u_char *dat,
		u_char *read_ecc, u_char *calc_ecc)
{
	/* The calculated ecc is actually the correction index in data */
	u32 err_idx[8];
	u32 num_err, i;
	u32 ecc1, ecc2, ecc3, ecc4;

	num_err = (readl(&fsmc_regs_p->sts) >> 10) & 0xF;

	if (likely(num_err == 0))
		return 0;

	if (unlikely(num_err > 8)) {
		/*
		 * This is a temporary erase check. A newly erased page read
		 * would result in an ecc error because the oob data is also
		 * erased to FF and the calculated ecc for an FF data is not
		 * FF..FF.
		 * This is a workaround to skip performing correction in case
		 * data is FF..FF
		 *
		 * Logic:
		 * For every page, each bit written as 0 is counted until these
		 * number of bits are greater than 8 (the maximum correction
		 * capability of FSMC for each 512 + 13 bytes)
		 */

		int bits_ecc = count_written_bits(read_ecc, 13, 8);
		int bits_data = count_written_bits(dat, 512, 8);

		if ((bits_ecc + bits_data) <= 8) {
			if (bits_data)
				memset(dat, 0xff, 512);
			return bits_data + bits_ecc;
		}

		return -EBADMSG;
	}

	ecc1 = readl(&fsmc_regs_p->ecc1);
	ecc2 = readl(&fsmc_regs_p->ecc2);
	ecc3 = readl(&fsmc_regs_p->ecc3);
	ecc4 = readl(&fsmc_regs_p->sts);

	err_idx[0] = (ecc1 >> 0) & 0x1FFF;
	err_idx[1] = (ecc1 >> 13) & 0x1FFF;
	err_idx[2] = (((ecc2 >> 0) & 0x7F) << 6) | ((ecc1 >> 26) & 0x3F);
	err_idx[3] = (ecc2 >> 7) & 0x1FFF;
	err_idx[4] = (((ecc3 >> 0) & 0x1) << 12) | ((ecc2 >> 20) & 0xFFF);
	err_idx[5] = (ecc3 >> 1) & 0x1FFF;
	err_idx[6] = (ecc3 >> 14) & 0x1FFF;
	err_idx[7] = (((ecc4 >> 16) & 0xFF) << 5) | ((ecc3 >> 27) & 0x1F);

	i = 0;
	while (i < num_err) {
		err_idx[i] ^= 3;

		if (err_idx[i] < 512 * 8)
			__change_bit(err_idx[i], dat);

		i++;
	}

	return num_err;
}

static int fsmc_read_hwecc(struct mtd_info *mtd,
			const u_char *data, u_char *ecc)
{
	u_int ecc_tmp;
	int timeout = CONFIG_SYS_HZ;
	ulong start;

	switch (fsmc_version) {
	case FSMC_VER8:
		start = get_timer(0);
		while (get_timer(start) < timeout) {
			/*
			 * Busy waiting for ecc computation
			 * to finish for 512 bytes
			 */
			if (readl(&fsmc_regs_p->sts) & FSMC_CODE_RDY)
				break;
		}

		ecc_tmp = readl(&fsmc_regs_p->ecc1);
		ecc[0] = (u_char) (ecc_tmp >> 0);
		ecc[1] = (u_char) (ecc_tmp >> 8);
		ecc[2] = (u_char) (ecc_tmp >> 16);
		ecc[3] = (u_char) (ecc_tmp >> 24);

		ecc_tmp = readl(&fsmc_regs_p->ecc2);
		ecc[4] = (u_char) (ecc_tmp >> 0);
		ecc[5] = (u_char) (ecc_tmp >> 8);
		ecc[6] = (u_char) (ecc_tmp >> 16);
		ecc[7] = (u_char) (ecc_tmp >> 24);

		ecc_tmp = readl(&fsmc_regs_p->ecc3);
		ecc[8] = (u_char) (ecc_tmp >> 0);
		ecc[9] = (u_char) (ecc_tmp >> 8);
		ecc[10] = (u_char) (ecc_tmp >> 16);
		ecc[11] = (u_char) (ecc_tmp >> 24);

		ecc_tmp = readl(&fsmc_regs_p->sts);
		ecc[12] = (u_char) (ecc_tmp >> 16);
		break;

	default:
		ecc_tmp = readl(&fsmc_regs_p->ecc1);
		ecc[0] = (u_char) (ecc_tmp >> 0);
		ecc[1] = (u_char) (ecc_tmp >> 8);
		ecc[2] = (u_char) (ecc_tmp >> 16);
		break;
	}

	return 0;
}

void fsmc_enable_hwecc(struct mtd_info *mtd, int mode)
{
	writel(readl(&fsmc_regs_p->pc) & ~FSMC_ECCPLEN_256,
			&fsmc_regs_p->pc);
	writel(readl(&fsmc_regs_p->pc) & ~FSMC_ECCEN,
			&fsmc_regs_p->pc);
	writel(readl(&fsmc_regs_p->pc) | FSMC_ECCEN,
			&fsmc_regs_p->pc);
}

/*
 * fsmc_read_page_hwecc
 * @mtd:	mtd info structure
 * @chip:	nand chip info structure
 * @buf:	buffer to store read data
 * @oob_required:	caller expects OOB data read to chip->oob_poi
 * @page:	page number to read
 *
 * This routine is needed for fsmc verison 8 as reading from NAND chip has to be
 * performed in a strict sequence as follows:
 * data(512 byte) -> ecc(13 byte)
 * After this read, fsmc hardware generates and reports error data bits(upto a
 * max of 8 bits)
 */
static int fsmc_read_page_hwecc(struct mtd_info *mtd, struct nand_chip *chip,
				 uint8_t *buf, int oob_required, int page)
{
	struct fsmc_eccplace *fsmc_eccpl;
	int i, j, s, stat, eccsize = chip->ecc.size;
	int eccbytes = chip->ecc.bytes;
	int eccsteps = chip->ecc.steps;
	uint8_t *p = buf;
	uint8_t *ecc_calc = chip->buffers->ecccalc;
	uint8_t *ecc_code = chip->buffers->ecccode;
	int off, len, group = 0;
	uint8_t oob[13] __attribute__ ((aligned (2)));

	/* Differentiate between small and large page ecc place definitions */
	if (mtd->writesize == 512)
		fsmc_eccpl = &fsmc_eccpl_sp;
	else
		fsmc_eccpl = &fsmc_eccpl_lp;

	for (i = 0, s = 0; s < eccsteps; s++, i += eccbytes, p += eccsize) {

		chip->cmdfunc(mtd, NAND_CMD_READ0, s * eccsize, page);
		chip->ecc.hwctl(mtd, NAND_ECC_READ);
		chip->read_buf(mtd, p, eccsize);

		for (j = 0; j < eccbytes;) {
			off = fsmc_eccpl->eccplace[group].offset;
			len = fsmc_eccpl->eccplace[group].length;
			group++;

			/*
			 * length is intentionally kept a higher multiple of 2
			 * to read at least 13 bytes even in case of 16 bit NAND
			 * devices
			 */
			if (chip->options & NAND_BUSWIDTH_16)
				len = roundup(len, 2);
			chip->cmdfunc(mtd, NAND_CMD_READOOB, off, page);
			chip->read_buf(mtd, oob + j, len);
			j += len;
		}

		memcpy(&ecc_code[i], oob, 13);
		chip->ecc.calculate(mtd, p, &ecc_calc[i]);

		stat = chip->ecc.correct(mtd, p, &ecc_code[i],
				&ecc_calc[i]);
		if (stat < 0)
			mtd->ecc_stats.failed++;
		else
			mtd->ecc_stats.corrected += stat;
	}

	return 0;
}

#ifndef CONFIG_SPL_BUILD
/*
 * fsmc_nand_switch_ecc - switch the ECC operation between different engines
 *
 * @eccstrength		- the number of bits that could be corrected
 *			  (1 - HW, 4 - SW BCH4)
 */
int fsmc_nand_switch_ecc(uint32_t eccstrength)
{
	struct nand_chip *nand;
	struct mtd_info *mtd;
	int err;

	/*
	 * This functions is only called on SPEAr600 platforms, supporting
	 * 1 bit HW ECC. The BCH8 HW ECC (FSMC_VER8) from the ST-Ericsson
	 * Nomadik SoC is currently supporting this fsmc_nand_switch_ecc()
	 * function, as it doesn't need to switch to a different ECC layout.
	 */
	mtd = get_nand_dev_by_index(nand_curr_device);
	nand = mtd_to_nand(mtd);

	/* Setup the ecc configurations again */
	if (eccstrength == 1) {
		nand->ecc.mode = NAND_ECC_HW;
		nand->ecc.bytes = 3;
		nand->ecc.strength = 1;
		nand->ecc.layout = &fsmc_ecc1_layout;
		nand->ecc.calculate = fsmc_read_hwecc;
		nand->ecc.correct = nand_correct_data;
	} else if (eccstrength == 4) {
		/*
		 * .calculate .correct and .bytes will be set in
		 * nand_scan_tail()
		 */
		nand->ecc.mode = NAND_ECC_SOFT_BCH;
		nand->ecc.strength = 4;
		nand->ecc.layout = NULL;
	} else {
		printf("Error: ECC strength %d not supported!\n", eccstrength);
	}

	/* Update NAND handling after ECC mode switch */
	err = nand_scan_tail(mtd);

	return err;
}
#endif /* CONFIG_SPL_BUILD */

int fsmc_nand_init(struct nand_chip *nand)
{
	static int chip_nr;
	struct mtd_info *mtd;
	u32 peripid2 = readl(&fsmc_regs_p->peripid2);

	fsmc_version = (peripid2 >> FSMC_REVISION_SHFT) &
		FSMC_REVISION_MSK;

	writel(readl(&fsmc_regs_p->ctrl) | FSMC_WP, &fsmc_regs_p->ctrl);

#if defined(CONFIG_SYS_FSMC_NAND_16BIT)
	writel(FSMC_DEVWID_16 | FSMC_DEVTYPE_NAND | FSMC_ENABLE | FSMC_WAITON,
			&fsmc_regs_p->pc);
#elif defined(CONFIG_SYS_FSMC_NAND_8BIT)
	writel(FSMC_DEVWID_8 | FSMC_DEVTYPE_NAND | FSMC_ENABLE | FSMC_WAITON,
			&fsmc_regs_p->pc);
#else
#error Please define CONFIG_SYS_FSMC_NAND_16BIT or CONFIG_SYS_FSMC_NAND_8BIT
#endif
	writel(readl(&fsmc_regs_p->pc) | FSMC_TCLR_1 | FSMC_TAR_1,
			&fsmc_regs_p->pc);
	writel(FSMC_THIZ_1 | FSMC_THOLD_4 | FSMC_TWAIT_6 | FSMC_TSET_0,
			&fsmc_regs_p->comm);
	writel(FSMC_THIZ_1 | FSMC_THOLD_4 | FSMC_TWAIT_6 | FSMC_TSET_0,
			&fsmc_regs_p->attrib);

	nand->options = 0;
#if defined(CONFIG_SYS_FSMC_NAND_16BIT)
	nand->options |= NAND_BUSWIDTH_16;
#endif
	nand->ecc.mode = NAND_ECC_HW;
	nand->ecc.size = 512;
	nand->ecc.calculate = fsmc_read_hwecc;
	nand->ecc.hwctl = fsmc_enable_hwecc;
	nand->cmd_ctrl = fsmc_nand_hwcontrol;
	nand->IO_ADDR_R = nand->IO_ADDR_W =
		(void  __iomem *)CONFIG_SYS_NAND_BASE;
	nand->badblockbits = 7;

	mtd = nand_to_mtd(nand);

	switch (fsmc_version) {
	case FSMC_VER8:
		nand->ecc.bytes = 13;
		nand->ecc.strength = 8;
		nand->ecc.correct = fsmc_bch8_correct_data;
		nand->ecc.read_page = fsmc_read_page_hwecc;
		if (mtd->writesize == 512)
			nand->ecc.layout = &fsmc_ecc4_sp_layout;
		else {
			if (mtd->oobsize == 224)
				nand->ecc.layout = &fsmc_ecc4_224_layout;
			else
				nand->ecc.layout = &fsmc_ecc4_lp_layout;
		}

		break;
	default:
		nand->ecc.bytes = 3;
		nand->ecc.strength = 1;
		nand->ecc.layout = &fsmc_ecc1_layout;
		nand->ecc.correct = nand_correct_data;
		break;
	}

	/* Detect NAND chips */
	if (nand_scan_ident(mtd, CONFIG_SYS_MAX_NAND_DEVICE, NULL))
		return -ENXIO;

	if (nand_scan_tail(mtd))
		return -ENXIO;

	if (nand_register(chip_nr++, mtd))
		return -ENXIO;

	return 0;
}
