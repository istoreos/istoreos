/*
 *  Overview:
 *   This is the generic MTD driver for NAND flash devices. It should be
 *   capable of working with almost all NAND chips currently available.
 *
 *	Additional technical information is available on
 *	http://www.linux-mtd.infradead.org/doc/nand.html
 *
 *  Copyright (C) 2000 Steven J. Hill (sjhill@realitydiluted.com)
 *		  2002-2006 Thomas Gleixner (tglx@linutronix.de)
 *
 *  Credits:
 *	David Woodhouse for adding multichip support
 *
 *	Aleph One Ltd. and Toby Churchill Ltd. for supporting the
 *	rework for 2K page size chips
 *
 *  TODO:
 *	Enable cached programming for 2k page size chips
 *	Check, if mtd->ecctype should be set to MTD_ECC_HW
 *	if we have HW ECC support.
 *	BBT table is not serialized, has to be fixed
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt
#include <common.h>
#if CONFIG_IS_ENABLED(OF_CONTROL)
#include <fdtdec.h>
#endif
#include <malloc.h>
#include <watchdog.h>
#include <linux/err.h>
#include <linux/compat.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/rawnand.h>
#include <linux/mtd/nand_ecc.h>
#include <linux/mtd/nand_bch.h>
#ifdef CONFIG_MTD_PARTITIONS
#include <linux/mtd/partitions.h>
#endif
#include <asm/io.h>
#include <linux/errno.h>

/* Define default oob placement schemes for large and small page devices */
#ifndef CONFIG_SYS_NAND_DRIVER_ECC_LAYOUT
static struct nand_ecclayout nand_oob_8 = {
	.eccbytes = 3,
	.eccpos = {0, 1, 2},
	.oobfree = {
		{.offset = 3,
		 .length = 2},
		{.offset = 6,
		 .length = 2} }
};

static struct nand_ecclayout nand_oob_16 = {
	.eccbytes = 6,
	.eccpos = {0, 1, 2, 3, 6, 7},
	.oobfree = {
		{.offset = 8,
		 . length = 8} }
};

static struct nand_ecclayout nand_oob_64 = {
	.eccbytes = 24,
	.eccpos = {
		   40, 41, 42, 43, 44, 45, 46, 47,
		   48, 49, 50, 51, 52, 53, 54, 55,
		   56, 57, 58, 59, 60, 61, 62, 63},
	.oobfree = {
		{.offset = 2,
		 .length = 38} }
};

static struct nand_ecclayout nand_oob_128 = {
	.eccbytes = 48,
	.eccpos = {
		   80, 81, 82, 83, 84, 85, 86, 87,
		   88, 89, 90, 91, 92, 93, 94, 95,
		   96, 97, 98, 99, 100, 101, 102, 103,
		   104, 105, 106, 107, 108, 109, 110, 111,
		   112, 113, 114, 115, 116, 117, 118, 119,
		   120, 121, 122, 123, 124, 125, 126, 127},
	.oobfree = {
		{.offset = 2,
		 .length = 78} }
};
#endif

static int nand_get_device(struct mtd_info *mtd, int new_state);

static int nand_do_write_oob(struct mtd_info *mtd, loff_t to,
			     struct mtd_oob_ops *ops);

/*
 * For devices which display every fart in the system on a separate LED. Is
 * compiled away when LED support is disabled.
 */
DEFINE_LED_TRIGGER(nand_led_trigger);

static int check_offs_len(struct mtd_info *mtd,
					loff_t ofs, uint64_t len)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	int ret = 0;

	/* Start address must align on block boundary */
	if (ofs & ((1ULL << chip->phys_erase_shift) - 1)) {
		pr_debug("%s: unaligned address\n", __func__);
		ret = -EINVAL;
	}

	/* Length must align on block boundary */
	if (len & ((1ULL << chip->phys_erase_shift) - 1)) {
		pr_debug("%s: length not block aligned\n", __func__);
		ret = -EINVAL;
	}

	return ret;
}

/**
 * nand_release_device - [GENERIC] release chip
 * @mtd: MTD device structure
 *
 * Release chip lock and wake up anyone waiting on the device.
 */
static void nand_release_device(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd_to_nand(mtd);

	/* De-select the NAND device */
	chip->select_chip(mtd, -1);
}

/**
 * nand_read_byte - [DEFAULT] read one byte from the chip
 * @mtd: MTD device structure
 *
 * Default read function for 8bit buswidth
 */
uint8_t nand_read_byte(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	return readb(chip->IO_ADDR_R);
}

/**
 * nand_read_byte16 - [DEFAULT] read one byte endianness aware from the chip
 * @mtd: MTD device structure
 *
 * Default read function for 16bit buswidth with endianness conversion.
 *
 */
static uint8_t nand_read_byte16(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	return (uint8_t) cpu_to_le16(readw(chip->IO_ADDR_R));
}

/**
 * nand_read_word - [DEFAULT] read one word from the chip
 * @mtd: MTD device structure
 *
 * Default read function for 16bit buswidth without endianness conversion.
 */
static u16 nand_read_word(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	return readw(chip->IO_ADDR_R);
}

/**
 * nand_select_chip - [DEFAULT] control CE line
 * @mtd: MTD device structure
 * @chipnr: chipnumber to select, -1 for deselect
 *
 * Default select function for 1 chip devices.
 */
static void nand_select_chip(struct mtd_info *mtd, int chipnr)
{
	struct nand_chip *chip = mtd_to_nand(mtd);

	switch (chipnr) {
	case -1:
		chip->cmd_ctrl(mtd, NAND_CMD_NONE, 0 | NAND_CTRL_CHANGE);
		break;
	case 0:
		break;

	default:
		BUG();
	}
}

/**
 * nand_write_byte - [DEFAULT] write single byte to chip
 * @mtd: MTD device structure
 * @byte: value to write
 *
 * Default function to write a byte to I/O[7:0]
 */
static void nand_write_byte(struct mtd_info *mtd, uint8_t byte)
{
	struct nand_chip *chip = mtd_to_nand(mtd);

	chip->write_buf(mtd, &byte, 1);
}

/**
 * nand_write_byte16 - [DEFAULT] write single byte to a chip with width 16
 * @mtd: MTD device structure
 * @byte: value to write
 *
 * Default function to write a byte to I/O[7:0] on a 16-bit wide chip.
 */
static void nand_write_byte16(struct mtd_info *mtd, uint8_t byte)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	uint16_t word = byte;

	/*
	 * It's not entirely clear what should happen to I/O[15:8] when writing
	 * a byte. The ONFi spec (Revision 3.1; 2012-09-19, Section 2.16) reads:
	 *
	 *    When the host supports a 16-bit bus width, only data is
	 *    transferred at the 16-bit width. All address and command line
	 *    transfers shall use only the lower 8-bits of the data bus. During
	 *    command transfers, the host may place any value on the upper
	 *    8-bits of the data bus. During address transfers, the host shall
	 *    set the upper 8-bits of the data bus to 00h.
	 *
	 * One user of the write_byte callback is nand_onfi_set_features. The
	 * four parameters are specified to be written to I/O[7:0], but this is
	 * neither an address nor a command transfer. Let's assume a 0 on the
	 * upper I/O lines is OK.
	 */
	chip->write_buf(mtd, (uint8_t *)&word, 2);
}

static void iowrite8_rep(void *addr, const uint8_t *buf, int len)
{
	int i;

	for (i = 0; i < len; i++)
		writeb(buf[i], addr);
}
static void ioread8_rep(void *addr, uint8_t *buf, int len)
{
	int i;

	for (i = 0; i < len; i++)
		buf[i] = readb(addr);
}

static void ioread16_rep(void *addr, void *buf, int len)
{
	int i;
 	u16 *p = (u16 *) buf;

	for (i = 0; i < len; i++)
		p[i] = readw(addr);
}

static void iowrite16_rep(void *addr, void *buf, int len)
{
	int i;
        u16 *p = (u16 *) buf;

        for (i = 0; i < len; i++)
                writew(p[i], addr);
}

/**
 * nand_write_buf - [DEFAULT] write buffer to chip
 * @mtd: MTD device structure
 * @buf: data buffer
 * @len: number of bytes to write
 *
 * Default write function for 8bit buswidth.
 */
void nand_write_buf(struct mtd_info *mtd, const uint8_t *buf, int len)
{
	struct nand_chip *chip = mtd_to_nand(mtd);

	iowrite8_rep(chip->IO_ADDR_W, buf, len);
}

/**
 * nand_read_buf - [DEFAULT] read chip data into buffer
 * @mtd: MTD device structure
 * @buf: buffer to store date
 * @len: number of bytes to read
 *
 * Default read function for 8bit buswidth.
 */
void nand_read_buf(struct mtd_info *mtd, uint8_t *buf, int len)
{
	struct nand_chip *chip = mtd_to_nand(mtd);

	ioread8_rep(chip->IO_ADDR_R, buf, len);
}

/**
 * nand_write_buf16 - [DEFAULT] write buffer to chip
 * @mtd: MTD device structure
 * @buf: data buffer
 * @len: number of bytes to write
 *
 * Default write function for 16bit buswidth.
 */
void nand_write_buf16(struct mtd_info *mtd, const uint8_t *buf, int len)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	u16 *p = (u16 *) buf;

	iowrite16_rep(chip->IO_ADDR_W, p, len >> 1);
}

/**
 * nand_read_buf16 - [DEFAULT] read chip data into buffer
 * @mtd: MTD device structure
 * @buf: buffer to store date
 * @len: number of bytes to read
 *
 * Default read function for 16bit buswidth.
 */
void nand_read_buf16(struct mtd_info *mtd, uint8_t *buf, int len)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	u16 *p = (u16 *) buf;

	ioread16_rep(chip->IO_ADDR_R, p, len >> 1);
}

/**
 * nand_block_bad - [DEFAULT] Read bad block marker from the chip
 * @mtd: MTD device structure
 * @ofs: offset from device start
 *
 * Check, if the block is bad.
 */
static int nand_block_bad(struct mtd_info *mtd, loff_t ofs)
{
	int page, res = 0, i = 0;
	struct nand_chip *chip = mtd_to_nand(mtd);
	u16 bad;

	if (chip->bbt_options & NAND_BBT_SCANLASTPAGE)
		ofs += mtd->erasesize - mtd->writesize;

	page = (int)(ofs >> chip->page_shift) & chip->pagemask;

	do {
		if (chip->options & NAND_BUSWIDTH_16) {
			chip->cmdfunc(mtd, NAND_CMD_READOOB,
					chip->badblockpos & 0xFE, page);
			bad = cpu_to_le16(chip->read_word(mtd));
			if (chip->badblockpos & 0x1)
				bad >>= 8;
			else
				bad &= 0xFF;
		} else {
			chip->cmdfunc(mtd, NAND_CMD_READOOB, chip->badblockpos,
					page);
			bad = chip->read_byte(mtd);
		}

		if (likely(chip->badblockbits == 8))
			res = bad != 0xFF;
		else
			res = hweight8(bad) < chip->badblockbits;
		ofs += mtd->writesize;
		page = (int)(ofs >> chip->page_shift) & chip->pagemask;
		i++;
	} while (!res && i < 2 && (chip->bbt_options & NAND_BBT_SCAN2NDPAGE));

	return res;
}

/**
 * nand_default_block_markbad - [DEFAULT] mark a block bad via bad block marker
 * @mtd: MTD device structure
 * @ofs: offset from device start
 *
 * This is the default implementation, which can be overridden by a hardware
 * specific driver. It provides the details for writing a bad block marker to a
 * block.
 */
static int nand_default_block_markbad(struct mtd_info *mtd, loff_t ofs)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct mtd_oob_ops ops;
	uint8_t buf[2] = { 0, 0 };
	int ret = 0, res, i = 0;

	memset(&ops, 0, sizeof(ops));
	ops.oobbuf = buf;
	ops.ooboffs = chip->badblockpos;
	if (chip->options & NAND_BUSWIDTH_16) {
		ops.ooboffs &= ~0x01;
		ops.len = ops.ooblen = 2;
	} else {
		ops.len = ops.ooblen = 1;
	}
	ops.mode = MTD_OPS_PLACE_OOB;

	/* Write to first/last page(s) if necessary */
	if (chip->bbt_options & NAND_BBT_SCANLASTPAGE)
		ofs += mtd->erasesize - mtd->writesize;
	do {
		res = nand_do_write_oob(mtd, ofs, &ops);
		if (!ret)
			ret = res;

		i++;
		ofs += mtd->writesize;
	} while ((chip->bbt_options & NAND_BBT_SCAN2NDPAGE) && i < 2);

	return ret;
}

/**
 * nand_block_markbad_lowlevel - mark a block bad
 * @mtd: MTD device structure
 * @ofs: offset from device start
 *
 * This function performs the generic NAND bad block marking steps (i.e., bad
 * block table(s) and/or marker(s)). We only allow the hardware driver to
 * specify how to write bad block markers to OOB (chip->block_markbad).
 *
 * We try operations in the following order:
 *  (1) erase the affected block, to allow OOB marker to be written cleanly
 *  (2) write bad block marker to OOB area of affected block (unless flag
 *      NAND_BBT_NO_OOB_BBM is present)
 *  (3) update the BBT
 * Note that we retain the first error encountered in (2) or (3), finish the
 * procedures, and dump the error in the end.
*/
static int nand_block_markbad_lowlevel(struct mtd_info *mtd, loff_t ofs)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	int res, ret = 0;

	if (!(chip->bbt_options & NAND_BBT_NO_OOB_BBM)) {
		struct erase_info einfo;

		/* Attempt erase before marking OOB */
		memset(&einfo, 0, sizeof(einfo));
		einfo.mtd = mtd;
		einfo.addr = ofs;
		einfo.len = 1ULL << chip->phys_erase_shift;
		nand_erase_nand(mtd, &einfo, 0);

		/* Write bad block marker to OOB */
		nand_get_device(mtd, FL_WRITING);
		ret = chip->block_markbad(mtd, ofs);
		nand_release_device(mtd);
	}

	/* Mark block bad in BBT */
	if (chip->bbt) {
		res = nand_markbad_bbt(mtd, ofs);
		if (!ret)
			ret = res;
	}

	if (!ret)
		mtd->ecc_stats.badblocks++;

	return ret;
}

/**
 * nand_check_wp - [GENERIC] check if the chip is write protected
 * @mtd: MTD device structure
 *
 * Check, if the device is write protected. The function expects, that the
 * device is already selected.
 */
static int nand_check_wp(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	u8 status;
	int ret;

	/* Broken xD cards report WP despite being writable */
	if (chip->options & NAND_BROKEN_XD)
		return 0;

	/* Check the WP bit */
	ret = nand_status_op(chip, &status);
	if (ret)
		return ret;

	return status & NAND_STATUS_WP ? 0 : 1;
}

/**
 * nand_block_isreserved - [GENERIC] Check if a block is marked reserved.
 * @mtd: MTD device structure
 * @ofs: offset from device start
 *
 * Check if the block is marked as reserved.
 */
static int nand_block_isreserved(struct mtd_info *mtd, loff_t ofs)
{
	struct nand_chip *chip = mtd_to_nand(mtd);

	if (!chip->bbt)
		return 0;
	/* Return info from the table */
	return nand_isreserved_bbt(mtd, ofs);
}

/**
 * nand_block_checkbad - [GENERIC] Check if a block is marked bad
 * @mtd: MTD device structure
 * @ofs: offset from device start
 * @allowbbt: 1, if its allowed to access the bbt area
 *
 * Check, if the block is bad. Either by reading the bad block table or
 * calling of the scan function.
 */
static int nand_block_checkbad(struct mtd_info *mtd, loff_t ofs, int allowbbt)
{
	struct nand_chip *chip = mtd_to_nand(mtd);

	if (!(chip->options & NAND_SKIP_BBTSCAN) &&
	    !(chip->options & NAND_BBT_SCANNED)) {
		chip->options |= NAND_BBT_SCANNED;
		chip->scan_bbt(mtd);
	}

	if (!chip->bbt)
		return chip->block_bad(mtd, ofs);

	/* Return info from the table */
	return nand_isbad_bbt(mtd, ofs, allowbbt);
}

/**
 * nand_wait_ready - [GENERIC] Wait for the ready pin after commands.
 * @mtd: MTD device structure
 *
 * Wait for the ready pin after a command, and warn if a timeout occurs.
 */
void nand_wait_ready(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	u32 timeo = (CONFIG_SYS_HZ * 400) / 1000;
	u32 time_start;

	time_start = get_timer(0);
	/* Wait until command is processed or timeout occurs */
	while (get_timer(time_start) < timeo) {
		if (chip->dev_ready)
			if (chip->dev_ready(mtd))
				break;
	}

	if (!chip->dev_ready(mtd))
		pr_warn("timeout while waiting for chip to become ready\n");
}
EXPORT_SYMBOL_GPL(nand_wait_ready);

/**
 * nand_wait_status_ready - [GENERIC] Wait for the ready status after commands.
 * @mtd: MTD device structure
 * @timeo: Timeout in ms
 *
 * Wait for status ready (i.e. command done) or timeout.
 */
static void nand_wait_status_ready(struct mtd_info *mtd, unsigned long timeo)
{
	register struct nand_chip *chip = mtd_to_nand(mtd);
	u32 time_start;
	int ret;

	timeo = (CONFIG_SYS_HZ * timeo) / 1000;
	time_start = get_timer(0);
	while (get_timer(time_start) < timeo) {
		u8 status;

		ret = nand_read_data_op(chip, &status, sizeof(status), true);
		if (ret)
			return;

		if (status & NAND_STATUS_READY)
			break;
		WATCHDOG_RESET();
	}
};

/**
 * nand_command - [DEFAULT] Send command to NAND device
 * @mtd: MTD device structure
 * @command: the command to be sent
 * @column: the column address for this command, -1 if none
 * @page_addr: the page address for this command, -1 if none
 *
 * Send command to NAND device. This function is used for small page devices
 * (512 Bytes per page).
 */
static void nand_command(struct mtd_info *mtd, unsigned int command,
			 int column, int page_addr)
{
	register struct nand_chip *chip = mtd_to_nand(mtd);
	int ctrl = NAND_CTRL_CLE | NAND_CTRL_CHANGE;

	/* Write out the command to the device */
	if (command == NAND_CMD_SEQIN) {
		int readcmd;

		if (column >= mtd->writesize) {
			/* OOB area */
			column -= mtd->writesize;
			readcmd = NAND_CMD_READOOB;
		} else if (column < 256) {
			/* First 256 bytes --> READ0 */
			readcmd = NAND_CMD_READ0;
		} else {
			column -= 256;
			readcmd = NAND_CMD_READ1;
		}
		chip->cmd_ctrl(mtd, readcmd, ctrl);
		ctrl &= ~NAND_CTRL_CHANGE;
	}
	chip->cmd_ctrl(mtd, command, ctrl);

	/* Address cycle, when necessary */
	ctrl = NAND_CTRL_ALE | NAND_CTRL_CHANGE;
	/* Serially input address */
	if (column != -1) {
		/* Adjust columns for 16 bit buswidth */
		if (chip->options & NAND_BUSWIDTH_16 &&
				!nand_opcode_8bits(command))
			column >>= 1;
		chip->cmd_ctrl(mtd, column, ctrl);
		ctrl &= ~NAND_CTRL_CHANGE;
	}
	if (page_addr != -1) {
		chip->cmd_ctrl(mtd, page_addr, ctrl);
		ctrl &= ~NAND_CTRL_CHANGE;
		chip->cmd_ctrl(mtd, page_addr >> 8, ctrl);
		if (chip->options & NAND_ROW_ADDR_3)
			chip->cmd_ctrl(mtd, page_addr >> 16, ctrl);
	}
	chip->cmd_ctrl(mtd, NAND_CMD_NONE, NAND_NCE | NAND_CTRL_CHANGE);

	/*
	 * Program and erase have their own busy handlers status and sequential
	 * in needs no delay
	 */
	switch (command) {

	case NAND_CMD_PAGEPROG:
	case NAND_CMD_ERASE1:
	case NAND_CMD_ERASE2:
	case NAND_CMD_SEQIN:
	case NAND_CMD_STATUS:
	case NAND_CMD_READID:
	case NAND_CMD_SET_FEATURES:
		return;

	case NAND_CMD_RESET:
		if (chip->dev_ready)
			break;
		udelay(chip->chip_delay);
		chip->cmd_ctrl(mtd, NAND_CMD_STATUS,
			       NAND_CTRL_CLE | NAND_CTRL_CHANGE);
		chip->cmd_ctrl(mtd,
			       NAND_CMD_NONE, NAND_NCE | NAND_CTRL_CHANGE);
		/* EZ-NAND can take upto 250ms as per ONFi v4.0 */
		nand_wait_status_ready(mtd, 250);
		return;

		/* This applies to read commands */
	default:
		/*
		 * If we don't have access to the busy pin, we apply the given
		 * command delay
		 */
		if (!chip->dev_ready) {
			udelay(chip->chip_delay);
			return;
		}
	}
	/*
	 * Apply this short delay always to ensure that we do wait tWB in
	 * any case on any machine.
	 */
	ndelay(100);

	nand_wait_ready(mtd);
}

/**
 * nand_command_lp - [DEFAULT] Send command to NAND large page device
 * @mtd: MTD device structure
 * @command: the command to be sent
 * @column: the column address for this command, -1 if none
 * @page_addr: the page address for this command, -1 if none
 *
 * Send command to NAND device. This is the version for the new large page
 * devices. We don't have the separate regions as we have in the small page
 * devices. We must emulate NAND_CMD_READOOB to keep the code compatible.
 */
static void nand_command_lp(struct mtd_info *mtd, unsigned int command,
			    int column, int page_addr)
{
	register struct nand_chip *chip = mtd_to_nand(mtd);

	/* Emulate NAND_CMD_READOOB */
	if (command == NAND_CMD_READOOB) {
		column += mtd->writesize;
		command = NAND_CMD_READ0;
	}

	/* Command latch cycle */
	chip->cmd_ctrl(mtd, command, NAND_NCE | NAND_CLE | NAND_CTRL_CHANGE);

	if (column != -1 || page_addr != -1) {
		int ctrl = NAND_CTRL_CHANGE | NAND_NCE | NAND_ALE;

		/* Serially input address */
		if (column != -1) {
			/* Adjust columns for 16 bit buswidth */
			if (chip->options & NAND_BUSWIDTH_16 &&
					!nand_opcode_8bits(command))
				column >>= 1;
			chip->cmd_ctrl(mtd, column, ctrl);
			ctrl &= ~NAND_CTRL_CHANGE;
			chip->cmd_ctrl(mtd, column >> 8, ctrl);
		}
		if (page_addr != -1) {
			chip->cmd_ctrl(mtd, page_addr, ctrl);
			chip->cmd_ctrl(mtd, page_addr >> 8,
				       NAND_NCE | NAND_ALE);
			if (chip->options & NAND_ROW_ADDR_3)
				chip->cmd_ctrl(mtd, page_addr >> 16,
					       NAND_NCE | NAND_ALE);
		}
	}
	chip->cmd_ctrl(mtd, NAND_CMD_NONE, NAND_NCE | NAND_CTRL_CHANGE);

	/*
	 * Program and erase have their own busy handlers status, sequential
	 * in and status need no delay.
	 */
	switch (command) {

	case NAND_CMD_CACHEDPROG:
	case NAND_CMD_PAGEPROG:
	case NAND_CMD_ERASE1:
	case NAND_CMD_ERASE2:
	case NAND_CMD_SEQIN:
	case NAND_CMD_RNDIN:
	case NAND_CMD_STATUS:
	case NAND_CMD_READID:
	case NAND_CMD_SET_FEATURES:
		return;

	case NAND_CMD_RESET:
		if (chip->dev_ready)
			break;
		udelay(chip->chip_delay);
		chip->cmd_ctrl(mtd, NAND_CMD_STATUS,
			       NAND_NCE | NAND_CLE | NAND_CTRL_CHANGE);
		chip->cmd_ctrl(mtd, NAND_CMD_NONE,
			       NAND_NCE | NAND_CTRL_CHANGE);
		/* EZ-NAND can take upto 250ms as per ONFi v4.0 */
		nand_wait_status_ready(mtd, 250);
		return;

	case NAND_CMD_RNDOUT:
		/* No ready / busy check necessary */
		chip->cmd_ctrl(mtd, NAND_CMD_RNDOUTSTART,
			       NAND_NCE | NAND_CLE | NAND_CTRL_CHANGE);
		chip->cmd_ctrl(mtd, NAND_CMD_NONE,
			       NAND_NCE | NAND_CTRL_CHANGE);
		return;

	case NAND_CMD_READ0:
		chip->cmd_ctrl(mtd, NAND_CMD_READSTART,
			       NAND_NCE | NAND_CLE | NAND_CTRL_CHANGE);
		chip->cmd_ctrl(mtd, NAND_CMD_NONE,
			       NAND_NCE | NAND_CTRL_CHANGE);

		/* This applies to read commands */
	default:
		/*
		 * If we don't have access to the busy pin, we apply the given
		 * command delay.
		 */
		if (!chip->dev_ready) {
			udelay(chip->chip_delay);
			return;
		}
	}

	/*
	 * Apply this short delay always to ensure that we do wait tWB in
	 * any case on any machine.
	 */
	ndelay(100);

	nand_wait_ready(mtd);
}

/**
 * panic_nand_get_device - [GENERIC] Get chip for selected access
 * @chip: the nand chip descriptor
 * @mtd: MTD device structure
 * @new_state: the state which is requested
 *
 * Used when in panic, no locks are taken.
 */
static void panic_nand_get_device(struct nand_chip *chip,
		      struct mtd_info *mtd, int new_state)
{
	/* Hardware controller shared among independent devices */
	chip->controller->active = chip;
	chip->state = new_state;
}

/**
 * nand_get_device - [GENERIC] Get chip for selected access
 * @mtd: MTD device structure
 * @new_state: the state which is requested
 *
 * Get the device and lock it for exclusive access
 */
static int
nand_get_device(struct mtd_info *mtd, int new_state)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	chip->state = new_state;
	return 0;
}

/**
 * panic_nand_wait - [GENERIC] wait until the command is done
 * @mtd: MTD device structure
 * @chip: NAND chip structure
 * @timeo: timeout
 *
 * Wait for command done. This is a helper function for nand_wait used when
 * we are in interrupt context. May happen when in panic and trying to write
 * an oops through mtdoops.
 */
static void panic_nand_wait(struct mtd_info *mtd, struct nand_chip *chip,
			    unsigned long timeo)
{
	int i;
	for (i = 0; i < timeo; i++) {
		if (chip->dev_ready) {
			if (chip->dev_ready(mtd))
				break;
		} else {
			int ret;
			u8 status;

			ret = nand_read_data_op(chip, &status, sizeof(status),
						true);
			if (ret)
				return;

			if (status & NAND_STATUS_READY)
				break;
		}
		mdelay(1);
	}
}

/**
 * nand_wait - [DEFAULT] wait until the command is done
 * @mtd: MTD device structure
 * @chip: NAND chip structure
 *
 * Wait for command done. This applies to erase and program only.
 */
static int nand_wait(struct mtd_info *mtd, struct nand_chip *chip)
{
	unsigned long timeo = 400;
	u8 status;
	int ret;

	led_trigger_event(nand_led_trigger, LED_FULL);

	/*
	 * Apply this short delay always to ensure that we do wait tWB in any
	 * case on any machine.
	 */
	ndelay(100);

	ret = nand_status_op(chip, NULL);
	if (ret)
		return ret;

 	u32 timer = (CONFIG_SYS_HZ * timeo) / 1000;
 	u32 time_start;
 
 	time_start = get_timer(0);
 	while (get_timer(time_start) < timer) {
		if (chip->dev_ready) {
			if (chip->dev_ready(mtd))
				break;
		} else {
			ret = nand_read_data_op(chip, &status,
						sizeof(status), true);
			if (ret)
				return ret;

			if (status & NAND_STATUS_READY)
				break;
		}
	}
	led_trigger_event(nand_led_trigger, LED_OFF);

	ret = nand_read_data_op(chip, &status, sizeof(status), true);
	if (ret)
		return ret;

	/* This can happen if in case of timeout or buggy dev_ready */
	WARN_ON(!(status & NAND_STATUS_READY));
	return status;
}

/**
 * nand_reset_data_interface - Reset data interface and timings
 * @chip: The NAND chip
 * @chipnr: Internal die id
 *
 * Reset the Data interface and timings to ONFI mode 0.
 *
 * Returns 0 for success or negative error code otherwise.
 */
static int nand_reset_data_interface(struct nand_chip *chip, int chipnr)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	const struct nand_data_interface *conf;
	int ret;

	if (!chip->setup_data_interface)
		return 0;

	/*
	 * The ONFI specification says:
	 * "
	 * To transition from NV-DDR or NV-DDR2 to the SDR data
	 * interface, the host shall use the Reset (FFh) command
	 * using SDR timing mode 0. A device in any timing mode is
	 * required to recognize Reset (FFh) command issued in SDR
	 * timing mode 0.
	 * "
	 *
	 * Configure the data interface in SDR mode and set the
	 * timings to timing mode 0.
	 */

	conf = nand_get_default_data_interface();
	ret = chip->setup_data_interface(mtd, chipnr, conf);
	if (ret)
		pr_err("Failed to configure data interface to SDR timing mode 0\n");

	return ret;
}

/**
 * nand_setup_data_interface - Setup the best data interface and timings
 * @chip: The NAND chip
 * @chipnr: Internal die id
 *
 * Find and configure the best data interface and NAND timings supported by
 * the chip and the driver.
 * First tries to retrieve supported timing modes from ONFI information,
 * and if the NAND chip does not support ONFI, relies on the
 * ->onfi_timing_mode_default specified in the nand_ids table.
 *
 * Returns 0 for success or negative error code otherwise.
 */
static int nand_setup_data_interface(struct nand_chip *chip, int chipnr)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	int ret;

	if (!chip->setup_data_interface || !chip->data_interface)
		return 0;

	/*
	 * Ensure the timing mode has been changed on the chip side
	 * before changing timings on the controller side.
	 */
	if (chip->onfi_version) {
		u8 tmode_param[ONFI_SUBFEATURE_PARAM_LEN] = {
			chip->onfi_timing_mode_default,
		};

		ret = chip->onfi_set_features(mtd, chip,
				ONFI_FEATURE_ADDR_TIMING_MODE,
				tmode_param);
		if (ret)
			goto err;
	}

	ret = chip->setup_data_interface(mtd, chipnr, chip->data_interface);
err:
	return ret;
}

/**
 * nand_init_data_interface - find the best data interface and timings
 * @chip: The NAND chip
 *
 * Find the best data interface and NAND timings supported by the chip
 * and the driver.
 * First tries to retrieve supported timing modes from ONFI information,
 * and if the NAND chip does not support ONFI, relies on the
 * ->onfi_timing_mode_default specified in the nand_ids table. After this
 * function nand_chip->data_interface is initialized with the best timing mode
 * available.
 *
 * Returns 0 for success or negative error code otherwise.
 */
static int nand_init_data_interface(struct nand_chip *chip)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	int modes, mode, ret;

	if (!chip->setup_data_interface)
		return 0;

	/*
	 * First try to identify the best timings from ONFI parameters and
	 * if the NAND does not support ONFI, fallback to the default ONFI
	 * timing mode.
	 */
	modes = onfi_get_async_timing_mode(chip);
	if (modes == ONFI_TIMING_MODE_UNKNOWN) {
		if (!chip->onfi_timing_mode_default)
			return 0;

		modes = GENMASK(chip->onfi_timing_mode_default, 0);
	}

	chip->data_interface = kzalloc(sizeof(*chip->data_interface),
				       GFP_KERNEL);
	if (!chip->data_interface)
		return -ENOMEM;

	for (mode = fls(modes) - 1; mode >= 0; mode--) {
		ret = onfi_init_data_interface(chip, chip->data_interface,
					       NAND_SDR_IFACE, mode);
		if (ret)
			continue;

		/* Pass -1 to only */
		ret = chip->setup_data_interface(mtd,
						 NAND_DATA_IFACE_CHECK_ONLY,
						 chip->data_interface);
		if (!ret) {
			chip->onfi_timing_mode_default = mode;
			break;
		}
	}

	return 0;
}

static void __maybe_unused nand_release_data_interface(struct nand_chip *chip)
{
	kfree(chip->data_interface);
}

/**
 * nand_read_page_op - Do a READ PAGE operation
 * @chip: The NAND chip
 * @page: page to read
 * @offset_in_page: offset within the page
 * @buf: buffer used to store the data
 * @len: length of the buffer
 *
 * This function issues a READ PAGE operation.
 * This function does not select/unselect the CS line.
 *
 * Returns 0 on success, a negative error code otherwise.
 */
int nand_read_page_op(struct nand_chip *chip, unsigned int page,
		      unsigned int offset_in_page, void *buf, unsigned int len)
{
	struct mtd_info *mtd = nand_to_mtd(chip);

	if (len && !buf)
		return -EINVAL;

	if (offset_in_page + len > mtd->writesize + mtd->oobsize)
		return -EINVAL;

	chip->cmdfunc(mtd, NAND_CMD_READ0, offset_in_page, page);
	if (len)
		chip->read_buf(mtd, buf, len);

	return 0;
}
EXPORT_SYMBOL_GPL(nand_read_page_op);

/**
 * nand_read_param_page_op - Do a READ PARAMETER PAGE operation
 * @chip: The NAND chip
 * @page: parameter page to read
 * @buf: buffer used to store the data
 * @len: length of the buffer
 *
 * This function issues a READ PARAMETER PAGE operation.
 * This function does not select/unselect the CS line.
 *
 * Returns 0 on success, a negative error code otherwise.
 */
static int nand_read_param_page_op(struct nand_chip *chip, u8 page, void *buf,
				   unsigned int len)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	unsigned int i;
	u8 *p = buf;

	if (len && !buf)
		return -EINVAL;

	chip->cmdfunc(mtd, NAND_CMD_PARAM, page, -1);
	for (i = 0; i < len; i++)
		p[i] = chip->read_byte(mtd);

	return 0;
}

/**
 * nand_change_read_column_op - Do a CHANGE READ COLUMN operation
 * @chip: The NAND chip
 * @offset_in_page: offset within the page
 * @buf: buffer used to store the data
 * @len: length of the buffer
 * @force_8bit: force 8-bit bus access
 *
 * This function issues a CHANGE READ COLUMN operation.
 * This function does not select/unselect the CS line.
 *
 * Returns 0 on success, a negative error code otherwise.
 */
int nand_change_read_column_op(struct nand_chip *chip,
			       unsigned int offset_in_page, void *buf,
			       unsigned int len, bool force_8bit)
{
	struct mtd_info *mtd = nand_to_mtd(chip);

	if (len && !buf)
		return -EINVAL;

	if (offset_in_page + len > mtd->writesize + mtd->oobsize)
		return -EINVAL;

	chip->cmdfunc(mtd, NAND_CMD_RNDOUT, offset_in_page, -1);
	if (len)
		chip->read_buf(mtd, buf, len);

	return 0;
}
EXPORT_SYMBOL_GPL(nand_change_read_column_op);

/**
 * nand_read_oob_op - Do a READ OOB operation
 * @chip: The NAND chip
 * @page: page to read
 * @offset_in_oob: offset within the OOB area
 * @buf: buffer used to store the data
 * @len: length of the buffer
 *
 * This function issues a READ OOB operation.
 * This function does not select/unselect the CS line.
 *
 * Returns 0 on success, a negative error code otherwise.
 */
int nand_read_oob_op(struct nand_chip *chip, unsigned int page,
		     unsigned int offset_in_oob, void *buf, unsigned int len)
{
	struct mtd_info *mtd = nand_to_mtd(chip);

	if (len && !buf)
		return -EINVAL;

	if (offset_in_oob + len > mtd->oobsize)
		return -EINVAL;

	chip->cmdfunc(mtd, NAND_CMD_READOOB, offset_in_oob, page);
	if (len)
		chip->read_buf(mtd, buf, len);

	return 0;
}
EXPORT_SYMBOL_GPL(nand_read_oob_op);

/**
 * nand_prog_page_begin_op - starts a PROG PAGE operation
 * @chip: The NAND chip
 * @page: page to write
 * @offset_in_page: offset within the page
 * @buf: buffer containing the data to write to the page
 * @len: length of the buffer
 *
 * This function issues the first half of a PROG PAGE operation.
 * This function does not select/unselect the CS line.
 *
 * Returns 0 on success, a negative error code otherwise.
 */
int nand_prog_page_begin_op(struct nand_chip *chip, unsigned int page,
			    unsigned int offset_in_page, const void *buf,
			    unsigned int len)
{
	struct mtd_info *mtd = nand_to_mtd(chip);

	if (len && !buf)
		return -EINVAL;

	if (offset_in_page + len > mtd->writesize + mtd->oobsize)
		return -EINVAL;

	chip->cmdfunc(mtd, NAND_CMD_SEQIN, offset_in_page, page);

	if (buf)
		chip->write_buf(mtd, buf, len);

	return 0;
}
EXPORT_SYMBOL_GPL(nand_prog_page_begin_op);

/**
 * nand_prog_page_end_op - ends a PROG PAGE operation
 * @chip: The NAND chip
 *
 * This function issues the second half of a PROG PAGE operation.
 * This function does not select/unselect the CS line.
 *
 * Returns 0 on success, a negative error code otherwise.
 */
int nand_prog_page_end_op(struct nand_chip *chip)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	int status;

	chip->cmdfunc(mtd, NAND_CMD_PAGEPROG, -1, -1);

	status = chip->waitfunc(mtd, chip);
	if (status & NAND_STATUS_FAIL)
		return -EIO;

	return 0;
}
EXPORT_SYMBOL_GPL(nand_prog_page_end_op);

/**
 * nand_prog_page_op - Do a full PROG PAGE operation
 * @chip: The NAND chip
 * @page: page to write
 * @offset_in_page: offset within the page
 * @buf: buffer containing the data to write to the page
 * @len: length of the buffer
 *
 * This function issues a full PROG PAGE operation.
 * This function does not select/unselect the CS line.
 *
 * Returns 0 on success, a negative error code otherwise.
 */
int nand_prog_page_op(struct nand_chip *chip, unsigned int page,
		      unsigned int offset_in_page, const void *buf,
		      unsigned int len)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	int status;

	if (!len || !buf)
		return -EINVAL;

	if (offset_in_page + len > mtd->writesize + mtd->oobsize)
		return -EINVAL;

	chip->cmdfunc(mtd, NAND_CMD_SEQIN, offset_in_page, page);
	chip->write_buf(mtd, buf, len);
	chip->cmdfunc(mtd, NAND_CMD_PAGEPROG, -1, -1);

	status = chip->waitfunc(mtd, chip);
	if (status & NAND_STATUS_FAIL)
		return -EIO;

	return 0;
}
EXPORT_SYMBOL_GPL(nand_prog_page_op);

/**
 * nand_change_write_column_op - Do a CHANGE WRITE COLUMN operation
 * @chip: The NAND chip
 * @offset_in_page: offset within the page
 * @buf: buffer containing the data to send to the NAND
 * @len: length of the buffer
 * @force_8bit: force 8-bit bus access
 *
 * This function issues a CHANGE WRITE COLUMN operation.
 * This function does not select/unselect the CS line.
 *
 * Returns 0 on success, a negative error code otherwise.
 */
int nand_change_write_column_op(struct nand_chip *chip,
				unsigned int offset_in_page,
				const void *buf, unsigned int len,
				bool force_8bit)
{
	struct mtd_info *mtd = nand_to_mtd(chip);

	if (len && !buf)
		return -EINVAL;

	if (offset_in_page + len > mtd->writesize + mtd->oobsize)
		return -EINVAL;

	chip->cmdfunc(mtd, NAND_CMD_RNDIN, offset_in_page, -1);
	if (len)
		chip->write_buf(mtd, buf, len);

	return 0;
}
EXPORT_SYMBOL_GPL(nand_change_write_column_op);

/**
 * nand_readid_op - Do a READID operation
 * @chip: The NAND chip
 * @addr: address cycle to pass after the READID command
 * @buf: buffer used to store the ID
 * @len: length of the buffer
 *
 * This function sends a READID command and reads back the ID returned by the
 * NAND.
 * This function does not select/unselect the CS line.
 *
 * Returns 0 on success, a negative error code otherwise.
 */
int nand_readid_op(struct nand_chip *chip, u8 addr, void *buf,
		   unsigned int len)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	unsigned int i;
	u8 *id = buf;

	if (len && !buf)
		return -EINVAL;

	chip->cmdfunc(mtd, NAND_CMD_READID, addr, -1);

	for (i = 0; i < len; i++)
		id[i] = chip->read_byte(mtd);

	return 0;
}
EXPORT_SYMBOL_GPL(nand_readid_op);

/**
 * nand_status_op - Do a STATUS operation
 * @chip: The NAND chip
 * @status: out variable to store the NAND status
 *
 * This function sends a STATUS command and reads back the status returned by
 * the NAND.
 * This function does not select/unselect the CS line.
 *
 * Returns 0 on success, a negative error code otherwise.
 */
int nand_status_op(struct nand_chip *chip, u8 *status)
{
	struct mtd_info *mtd = nand_to_mtd(chip);

	chip->cmdfunc(mtd, NAND_CMD_STATUS, -1, -1);
	if (status)
		*status = chip->read_byte(mtd);

	return 0;
}
EXPORT_SYMBOL_GPL(nand_status_op);

/**
 * nand_exit_status_op - Exit a STATUS operation
 * @chip: The NAND chip
 *
 * This function sends a READ0 command to cancel the effect of the STATUS
 * command to avoid reading only the status until a new read command is sent.
 *
 * This function does not select/unselect the CS line.
 *
 * Returns 0 on success, a negative error code otherwise.
 */
int nand_exit_status_op(struct nand_chip *chip)
{
	struct mtd_info *mtd = nand_to_mtd(chip);

	chip->cmdfunc(mtd, NAND_CMD_READ0, -1, -1);

	return 0;
}
EXPORT_SYMBOL_GPL(nand_exit_status_op);

/**
 * nand_erase_op - Do an erase operation
 * @chip: The NAND chip
 * @eraseblock: block to erase
 *
 * This function sends an ERASE command and waits for the NAND to be ready
 * before returning.
 * This function does not select/unselect the CS line.
 *
 * Returns 0 on success, a negative error code otherwise.
 */
int nand_erase_op(struct nand_chip *chip, unsigned int eraseblock)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	unsigned int page = eraseblock <<
			    (chip->phys_erase_shift - chip->page_shift);
	int status;

	chip->cmdfunc(mtd, NAND_CMD_ERASE1, -1, page);
	chip->cmdfunc(mtd, NAND_CMD_ERASE2, -1, -1);

	status = chip->waitfunc(mtd, chip);
	if (status < 0)
		return status;

	if (status & NAND_STATUS_FAIL)
		return -EIO;

	return 0;
}
EXPORT_SYMBOL_GPL(nand_erase_op);

/**
 * nand_set_features_op - Do a SET FEATURES operation
 * @chip: The NAND chip
 * @feature: feature id
 * @data: 4 bytes of data
 *
 * This function sends a SET FEATURES command and waits for the NAND to be
 * ready before returning.
 * This function does not select/unselect the CS line.
 *
 * Returns 0 on success, a negative error code otherwise.
 */
static int nand_set_features_op(struct nand_chip *chip, u8 feature,
				const void *data)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	const u8 *params = data;
	int i, status;

	chip->cmdfunc(mtd, NAND_CMD_SET_FEATURES, feature, -1);
	for (i = 0; i < ONFI_SUBFEATURE_PARAM_LEN; ++i)
		chip->write_byte(mtd, params[i]);

	status = chip->waitfunc(mtd, chip);
	if (status & NAND_STATUS_FAIL)
		return -EIO;

	return 0;
}

/**
 * nand_get_features_op - Do a GET FEATURES operation
 * @chip: The NAND chip
 * @feature: feature id
 * @data: 4 bytes of data
 *
 * This function sends a GET FEATURES command and waits for the NAND to be
 * ready before returning.
 * This function does not select/unselect the CS line.
 *
 * Returns 0 on success, a negative error code otherwise.
 */
static int nand_get_features_op(struct nand_chip *chip, u8 feature,
				void *data)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	u8 *params = data;
	int i;

	chip->cmdfunc(mtd, NAND_CMD_GET_FEATURES, feature, -1);
	for (i = 0; i < ONFI_SUBFEATURE_PARAM_LEN; ++i)
		params[i] = chip->read_byte(mtd);

	return 0;
}

/**
 * nand_reset_op - Do a reset operation
 * @chip: The NAND chip
 *
 * This function sends a RESET command and waits for the NAND to be ready
 * before returning.
 * This function does not select/unselect the CS line.
 *
 * Returns 0 on success, a negative error code otherwise.
 */
int nand_reset_op(struct nand_chip *chip)
{
	struct mtd_info *mtd = nand_to_mtd(chip);

	chip->cmdfunc(mtd, NAND_CMD_RESET, -1, -1);

	return 0;
}
EXPORT_SYMBOL_GPL(nand_reset_op);

/**
 * nand_read_data_op - Read data from the NAND
 * @chip: The NAND chip
 * @buf: buffer used to store the data
 * @len: length of the buffer
 * @force_8bit: force 8-bit bus access
 *
 * This function does a raw data read on the bus. Usually used after launching
 * another NAND operation like nand_read_page_op().
 * This function does not select/unselect the CS line.
 *
 * Returns 0 on success, a negative error code otherwise.
 */
int nand_read_data_op(struct nand_chip *chip, void *buf, unsigned int len,
		      bool force_8bit)
{
	struct mtd_info *mtd = nand_to_mtd(chip);

	if (!len || !buf)
		return -EINVAL;

	if (force_8bit) {
		u8 *p = buf;
		unsigned int i;

		for (i = 0; i < len; i++)
			p[i] = chip->read_byte(mtd);
	} else {
		chip->read_buf(mtd, buf, len);
	}

	return 0;
}
EXPORT_SYMBOL_GPL(nand_read_data_op);

/**
 * nand_write_data_op - Write data from the NAND
 * @chip: The NAND chip
 * @buf: buffer containing the data to send on the bus
 * @len: length of the buffer
 * @force_8bit: force 8-bit bus access
 *
 * This function does a raw data write on the bus. Usually used after launching
 * another NAND operation like nand_write_page_begin_op().
 * This function does not select/unselect the CS line.
 *
 * Returns 0 on success, a negative error code otherwise.
 */
int nand_write_data_op(struct nand_chip *chip, const void *buf,
		       unsigned int len, bool force_8bit)
{
	struct mtd_info *mtd = nand_to_mtd(chip);

	if (!len || !buf)
		return -EINVAL;

	if (force_8bit) {
		const u8 *p = buf;
		unsigned int i;

		for (i = 0; i < len; i++)
			chip->write_byte(mtd, p[i]);
	} else {
		chip->write_buf(mtd, buf, len);
	}

	return 0;
}
EXPORT_SYMBOL_GPL(nand_write_data_op);

/**
 * nand_reset - Reset and initialize a NAND device
 * @chip: The NAND chip
 * @chipnr: Internal die id
 *
 * Returns 0 for success or negative error code otherwise
 */
int nand_reset(struct nand_chip *chip, int chipnr)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	int ret;

	ret = nand_reset_data_interface(chip, chipnr);
	if (ret)
		return ret;

	/*
	 * The CS line has to be released before we can apply the new NAND
	 * interface settings, hence this weird ->select_chip() dance.
	 */
	chip->select_chip(mtd, chipnr);
	ret = nand_reset_op(chip);
	chip->select_chip(mtd, -1);
	if (ret)
		return ret;

	chip->select_chip(mtd, chipnr);
	ret = nand_setup_data_interface(chip, chipnr);
	chip->select_chip(mtd, -1);
	if (ret)
		return ret;

	return 0;
}

/**
 * nand_check_erased_buf - check if a buffer contains (almost) only 0xff data
 * @buf: buffer to test
 * @len: buffer length
 * @bitflips_threshold: maximum number of bitflips
 *
 * Check if a buffer contains only 0xff, which means the underlying region
 * has been erased and is ready to be programmed.
 * The bitflips_threshold specify the maximum number of bitflips before
 * considering the region is not erased.
 * Note: The logic of this function has been extracted from the memweight
 * implementation, except that nand_check_erased_buf function exit before
 * testing the whole buffer if the number of bitflips exceed the
 * bitflips_threshold value.
 *
 * Returns a positive number of bitflips less than or equal to
 * bitflips_threshold, or -ERROR_CODE for bitflips in excess of the
 * threshold.
 */
static int nand_check_erased_buf(void *buf, int len, int bitflips_threshold)
{
	const unsigned char *bitmap = buf;
	int bitflips = 0;
	int weight;

	for (; len && ((uintptr_t)bitmap) % sizeof(long);
	     len--, bitmap++) {
		weight = hweight8(*bitmap);
		bitflips += BITS_PER_BYTE - weight;
		if (unlikely(bitflips > bitflips_threshold))
			return -EBADMSG;
	}

	for (; len >= 4; len -= 4, bitmap += 4) {
		weight = hweight32(*((u32 *)bitmap));
		bitflips += 32 - weight;
		if (unlikely(bitflips > bitflips_threshold))
			return -EBADMSG;
	}

	for (; len > 0; len--, bitmap++) {
		weight = hweight8(*bitmap);
		bitflips += BITS_PER_BYTE - weight;
		if (unlikely(bitflips > bitflips_threshold))
			return -EBADMSG;
	}

	return bitflips;
}

/**
 * nand_check_erased_ecc_chunk - check if an ECC chunk contains (almost) only
 *				 0xff data
 * @data: data buffer to test
 * @datalen: data length
 * @ecc: ECC buffer
 * @ecclen: ECC length
 * @extraoob: extra OOB buffer
 * @extraooblen: extra OOB length
 * @bitflips_threshold: maximum number of bitflips
 *
 * Check if a data buffer and its associated ECC and OOB data contains only
 * 0xff pattern, which means the underlying region has been erased and is
 * ready to be programmed.
 * The bitflips_threshold specify the maximum number of bitflips before
 * considering the region as not erased.
 *
 * Note:
 * 1/ ECC algorithms are working on pre-defined block sizes which are usually
 *    different from the NAND page size. When fixing bitflips, ECC engines will
 *    report the number of errors per chunk, and the NAND core infrastructure
 *    expect you to return the maximum number of bitflips for the whole page.
 *    This is why you should always use this function on a single chunk and
 *    not on the whole page. After checking each chunk you should update your
 *    max_bitflips value accordingly.
 * 2/ When checking for bitflips in erased pages you should not only check
 *    the payload data but also their associated ECC data, because a user might
 *    have programmed almost all bits to 1 but a few. In this case, we
 *    shouldn't consider the chunk as erased, and checking ECC bytes prevent
 *    this case.
 * 3/ The extraoob argument is optional, and should be used if some of your OOB
 *    data are protected by the ECC engine.
 *    It could also be used if you support subpages and want to attach some
 *    extra OOB data to an ECC chunk.
 *
 * Returns a positive number of bitflips less than or equal to
 * bitflips_threshold, or -ERROR_CODE for bitflips in excess of the
 * threshold. In case of success, the passed buffers are filled with 0xff.
 */
int nand_check_erased_ecc_chunk(void *data, int datalen,
				void *ecc, int ecclen,
				void *extraoob, int extraooblen,
				int bitflips_threshold)
{
	int data_bitflips = 0, ecc_bitflips = 0, extraoob_bitflips = 0;

	data_bitflips = nand_check_erased_buf(data, datalen,
					      bitflips_threshold);
	if (data_bitflips < 0)
		return data_bitflips;

	bitflips_threshold -= data_bitflips;

	ecc_bitflips = nand_check_erased_buf(ecc, ecclen, bitflips_threshold);
	if (ecc_bitflips < 0)
		return ecc_bitflips;

	bitflips_threshold -= ecc_bitflips;

	extraoob_bitflips = nand_check_erased_buf(extraoob, extraooblen,
						  bitflips_threshold);
	if (extraoob_bitflips < 0)
		return extraoob_bitflips;

	if (data_bitflips)
		memset(data, 0xff, datalen);

	if (ecc_bitflips)
		memset(ecc, 0xff, ecclen);

	if (extraoob_bitflips)
		memset(extraoob, 0xff, extraooblen);

	return data_bitflips + ecc_bitflips + extraoob_bitflips;
}
EXPORT_SYMBOL(nand_check_erased_ecc_chunk);

/**
 * nand_read_page_raw - [INTERN] read raw page data without ecc
 * @mtd: mtd info structure
 * @chip: nand chip info structure
 * @buf: buffer to store read data
 * @oob_required: caller requires OOB data read to chip->oob_poi
 * @page: page number to read
 *
 * Not for syndrome calculating ECC controllers, which use a special oob layout.
 */
static int nand_read_page_raw(struct mtd_info *mtd, struct nand_chip *chip,
			      uint8_t *buf, int oob_required, int page)
{
	int ret;

	ret = nand_read_data_op(chip, buf, mtd->writesize, false);
	if (ret)
		return ret;

	if (oob_required) {
		ret = nand_read_data_op(chip, chip->oob_poi, mtd->oobsize,
					false);
		if (ret)
			return ret;
	}

	return 0;
}

/**
 * nand_read_page_raw_syndrome - [INTERN] read raw page data without ecc
 * @mtd: mtd info structure
 * @chip: nand chip info structure
 * @buf: buffer to store read data
 * @oob_required: caller requires OOB data read to chip->oob_poi
 * @page: page number to read
 *
 * We need a special oob layout and handling even when OOB isn't used.
 */
static int nand_read_page_raw_syndrome(struct mtd_info *mtd,
				       struct nand_chip *chip, uint8_t *buf,
				       int oob_required, int page)
{
	int eccsize = chip->ecc.size;
	int eccbytes = chip->ecc.bytes;
	uint8_t *oob = chip->oob_poi;
	int steps, size, ret;

	for (steps = chip->ecc.steps; steps > 0; steps--) {
		ret = nand_read_data_op(chip, buf, eccsize, false);
		if (ret)
			return ret;

		buf += eccsize;

		if (chip->ecc.prepad) {
			ret = nand_read_data_op(chip, oob, chip->ecc.prepad,
						false);
			if (ret)
				return ret;

			oob += chip->ecc.prepad;
		}

		ret = nand_read_data_op(chip, oob, eccbytes, false);
		if (ret)
			return ret;

		oob += eccbytes;

		if (chip->ecc.postpad) {
			ret = nand_read_data_op(chip, oob, chip->ecc.postpad,
						false);
			if (ret)
				return ret;

			oob += chip->ecc.postpad;
		}
	}

	size = mtd->oobsize - (oob - chip->oob_poi);
	if (size) {
		ret = nand_read_data_op(chip, oob, size, false);
		if (ret)
			return ret;
	}

	return 0;
}

/**
 * nand_read_page_swecc - [REPLACEABLE] software ECC based page read function
 * @mtd: mtd info structure
 * @chip: nand chip info structure
 * @buf: buffer to store read data
 * @oob_required: caller requires OOB data read to chip->oob_poi
 * @page: page number to read
 */
static int nand_read_page_swecc(struct mtd_info *mtd, struct nand_chip *chip,
				uint8_t *buf, int oob_required, int page)
{
	int i, eccsize = chip->ecc.size;
	int eccbytes = chip->ecc.bytes;
	int eccsteps = chip->ecc.steps;
	uint8_t *p = buf;
	uint8_t *ecc_calc = chip->buffers->ecccalc;
	uint8_t *ecc_code = chip->buffers->ecccode;
	uint32_t *eccpos = chip->ecc.layout->eccpos;
	unsigned int max_bitflips = 0;

	chip->ecc.read_page_raw(mtd, chip, buf, 1, page);

	for (i = 0; eccsteps; eccsteps--, i += eccbytes, p += eccsize)
		chip->ecc.calculate(mtd, p, &ecc_calc[i]);

	for (i = 0; i < chip->ecc.total; i++)
		ecc_code[i] = chip->oob_poi[eccpos[i]];

	eccsteps = chip->ecc.steps;
	p = buf;

	for (i = 0 ; eccsteps; eccsteps--, i += eccbytes, p += eccsize) {
		int stat;

		stat = chip->ecc.correct(mtd, p, &ecc_code[i], &ecc_calc[i]);
		if (stat < 0) {
			mtd->ecc_stats.failed++;
		} else {
			mtd->ecc_stats.corrected += stat;
			max_bitflips = max_t(unsigned int, max_bitflips, stat);
		}
	}
	return max_bitflips;
}

/**
 * nand_read_subpage - [REPLACEABLE] ECC based sub-page read function
 * @mtd: mtd info structure
 * @chip: nand chip info structure
 * @data_offs: offset of requested data within the page
 * @readlen: data length
 * @bufpoi: buffer to store read data
 * @page: page number to read
 */
static int nand_read_subpage(struct mtd_info *mtd, struct nand_chip *chip,
			uint32_t data_offs, uint32_t readlen, uint8_t *bufpoi,
			int page)
{
	int start_step, end_step, num_steps;
	uint32_t *eccpos = chip->ecc.layout->eccpos;
	uint8_t *p;
	int data_col_addr, i, gaps = 0;
	int datafrag_len, eccfrag_len, aligned_len, aligned_pos;
	int busw = (chip->options & NAND_BUSWIDTH_16) ? 2 : 1;
	int index;
	unsigned int max_bitflips = 0;
	int ret;

	/* Column address within the page aligned to ECC size (256bytes) */
	start_step = data_offs / chip->ecc.size;
	end_step = (data_offs + readlen - 1) / chip->ecc.size;
	num_steps = end_step - start_step + 1;
	index = start_step * chip->ecc.bytes;

	/* Data size aligned to ECC ecc.size */
	datafrag_len = num_steps * chip->ecc.size;
	eccfrag_len = num_steps * chip->ecc.bytes;

	data_col_addr = start_step * chip->ecc.size;
	/* If we read not a page aligned data */
	if (data_col_addr != 0)
		chip->cmdfunc(mtd, NAND_CMD_RNDOUT, data_col_addr, -1);

	p = bufpoi + data_col_addr;
	ret = nand_read_data_op(chip, p, datafrag_len, false);
	if (ret)
		return ret;

	/* Calculate ECC */
	for (i = 0; i < eccfrag_len ; i += chip->ecc.bytes, p += chip->ecc.size)
		chip->ecc.calculate(mtd, p, &chip->buffers->ecccalc[i]);

	/*
	 * The performance is faster if we position offsets according to
	 * ecc.pos. Let's make sure that there are no gaps in ECC positions.
	 */
	for (i = 0; i < eccfrag_len - 1; i++) {
		if (eccpos[i + index] + 1 != eccpos[i + index + 1]) {
			gaps = 1;
			break;
		}
	}
	if (gaps) {
		ret = nand_change_read_column_op(chip, mtd->writesize,
						 chip->oob_poi, mtd->oobsize,
						 false);
		if (ret)
			return ret;
	} else {
		/*
		 * Send the command to read the particular ECC bytes take care
		 * about buswidth alignment in read_buf.
		 */
		aligned_pos = eccpos[index] & ~(busw - 1);
		aligned_len = eccfrag_len;
		if (eccpos[index] & (busw - 1))
			aligned_len++;
		if (eccpos[index + (num_steps * chip->ecc.bytes)] & (busw - 1))
			aligned_len++;

		ret = nand_change_read_column_op(chip,
						 mtd->writesize + aligned_pos,
						 &chip->oob_poi[aligned_pos],
						 aligned_len, false);
		if (ret)
			return ret;
	}

	for (i = 0; i < eccfrag_len; i++)
		chip->buffers->ecccode[i] = chip->oob_poi[eccpos[i + index]];

	p = bufpoi + data_col_addr;
	for (i = 0; i < eccfrag_len ; i += chip->ecc.bytes, p += chip->ecc.size) {
		int stat;

		stat = chip->ecc.correct(mtd, p,
			&chip->buffers->ecccode[i], &chip->buffers->ecccalc[i]);
		if (stat == -EBADMSG &&
		    (chip->ecc.options & NAND_ECC_GENERIC_ERASED_CHECK)) {
			/* check for empty pages with bitflips */
			stat = nand_check_erased_ecc_chunk(p, chip->ecc.size,
						&chip->buffers->ecccode[i],
						chip->ecc.bytes,
						NULL, 0,
						chip->ecc.strength);
		}

		if (stat < 0) {
			mtd->ecc_stats.failed++;
		} else {
			mtd->ecc_stats.corrected += stat;
			max_bitflips = max_t(unsigned int, max_bitflips, stat);
		}
	}
	return max_bitflips;
}

/**
 * nand_read_page_hwecc - [REPLACEABLE] hardware ECC based page read function
 * @mtd: mtd info structure
 * @chip: nand chip info structure
 * @buf: buffer to store read data
 * @oob_required: caller requires OOB data read to chip->oob_poi
 * @page: page number to read
 *
 * Not for syndrome calculating ECC controllers which need a special oob layout.
 */
static int nand_read_page_hwecc(struct mtd_info *mtd, struct nand_chip *chip,
				uint8_t *buf, int oob_required, int page)
{
	int i, eccsize = chip->ecc.size;
	int eccbytes = chip->ecc.bytes;
	int eccsteps = chip->ecc.steps;
	uint8_t *p = buf;
	uint8_t *ecc_calc = chip->buffers->ecccalc;
	uint8_t *ecc_code = chip->buffers->ecccode;
	uint32_t *eccpos = chip->ecc.layout->eccpos;
	unsigned int max_bitflips = 0;
	int ret;

	for (i = 0; eccsteps; eccsteps--, i += eccbytes, p += eccsize) {
		chip->ecc.hwctl(mtd, NAND_ECC_READ);

		ret = nand_read_data_op(chip, p, eccsize, false);
		if (ret)
			return ret;

		chip->ecc.calculate(mtd, p, &ecc_calc[i]);
	}

	ret = nand_read_data_op(chip, chip->oob_poi, mtd->oobsize, false);
	if (ret)
		return ret;

	for (i = 0; i < chip->ecc.total; i++)
		ecc_code[i] = chip->oob_poi[eccpos[i]];

	eccsteps = chip->ecc.steps;
	p = buf;

	for (i = 0 ; eccsteps; eccsteps--, i += eccbytes, p += eccsize) {
		int stat;

		stat = chip->ecc.correct(mtd, p, &ecc_code[i], &ecc_calc[i]);
		if (stat == -EBADMSG &&
		    (chip->ecc.options & NAND_ECC_GENERIC_ERASED_CHECK)) {
			/* check for empty pages with bitflips */
			stat = nand_check_erased_ecc_chunk(p, eccsize,
						&ecc_code[i], eccbytes,
						NULL, 0,
						chip->ecc.strength);
		}

		if (stat < 0) {
			mtd->ecc_stats.failed++;
		} else {
			mtd->ecc_stats.corrected += stat;
			max_bitflips = max_t(unsigned int, max_bitflips, stat);
		}
	}
	return max_bitflips;
}

/**
 * nand_read_page_hwecc_oob_first - [REPLACEABLE] hw ecc, read oob first
 * @mtd: mtd info structure
 * @chip: nand chip info structure
 * @buf: buffer to store read data
 * @oob_required: caller requires OOB data read to chip->oob_poi
 * @page: page number to read
 *
 * Hardware ECC for large page chips, require OOB to be read first. For this
 * ECC mode, the write_page method is re-used from ECC_HW. These methods
 * read/write ECC from the OOB area, unlike the ECC_HW_SYNDROME support with
 * multiple ECC steps, follows the "infix ECC" scheme and reads/writes ECC from
 * the data area, by overwriting the NAND manufacturer bad block markings.
 */
static int nand_read_page_hwecc_oob_first(struct mtd_info *mtd,
	struct nand_chip *chip, uint8_t *buf, int oob_required, int page)
{
	int i, eccsize = chip->ecc.size;
	int eccbytes = chip->ecc.bytes;
	int eccsteps = chip->ecc.steps;
	uint8_t *p = buf;
	uint8_t *ecc_code = chip->buffers->ecccode;
	uint32_t *eccpos = chip->ecc.layout->eccpos;
	uint8_t *ecc_calc = chip->buffers->ecccalc;
	unsigned int max_bitflips = 0;
	int ret;

	/* Read the OOB area first */
	ret = nand_read_oob_op(chip, page, 0, chip->oob_poi, mtd->oobsize);
	if (ret)
		return ret;

	ret = nand_read_page_op(chip, page, 0, NULL, 0);
	if (ret)
		return ret;

	for (i = 0; i < chip->ecc.total; i++)
		ecc_code[i] = chip->oob_poi[eccpos[i]];

	for (i = 0; eccsteps; eccsteps--, i += eccbytes, p += eccsize) {
		int stat;

		chip->ecc.hwctl(mtd, NAND_ECC_READ);

		ret = nand_read_data_op(chip, p, eccsize, false);
		if (ret)
			return ret;

		chip->ecc.calculate(mtd, p, &ecc_calc[i]);

		stat = chip->ecc.correct(mtd, p, &ecc_code[i], NULL);
		if (stat == -EBADMSG &&
		    (chip->ecc.options & NAND_ECC_GENERIC_ERASED_CHECK)) {
			/* check for empty pages with bitflips */
			stat = nand_check_erased_ecc_chunk(p, eccsize,
						&ecc_code[i], eccbytes,
						NULL, 0,
						chip->ecc.strength);
		}

		if (stat < 0) {
			mtd->ecc_stats.failed++;
		} else {
			mtd->ecc_stats.corrected += stat;
			max_bitflips = max_t(unsigned int, max_bitflips, stat);
		}
	}
	return max_bitflips;
}

/**
 * nand_read_page_syndrome - [REPLACEABLE] hardware ECC syndrome based page read
 * @mtd: mtd info structure
 * @chip: nand chip info structure
 * @buf: buffer to store read data
 * @oob_required: caller requires OOB data read to chip->oob_poi
 * @page: page number to read
 *
 * The hw generator calculates the error syndrome automatically. Therefore we
 * need a special oob layout and handling.
 */
static int nand_read_page_syndrome(struct mtd_info *mtd, struct nand_chip *chip,
				   uint8_t *buf, int oob_required, int page)
{
	int ret, i, eccsize = chip->ecc.size;
	int eccbytes = chip->ecc.bytes;
	int eccsteps = chip->ecc.steps;
	int eccpadbytes = eccbytes + chip->ecc.prepad + chip->ecc.postpad;
	uint8_t *p = buf;
	uint8_t *oob = chip->oob_poi;
	unsigned int max_bitflips = 0;

	for (i = 0; eccsteps; eccsteps--, i += eccbytes, p += eccsize) {
		int stat;

		chip->ecc.hwctl(mtd, NAND_ECC_READ);

		ret = nand_read_data_op(chip, p, eccsize, false);
		if (ret)
			return ret;

		if (chip->ecc.prepad) {
			ret = nand_read_data_op(chip, oob, chip->ecc.prepad,
						false);
			if (ret)
				return ret;

			oob += chip->ecc.prepad;
		}

		chip->ecc.hwctl(mtd, NAND_ECC_READSYN);

		ret = nand_read_data_op(chip, oob, eccbytes, false);
		if (ret)
			return ret;

		stat = chip->ecc.correct(mtd, p, oob, NULL);

		oob += eccbytes;

		if (chip->ecc.postpad) {
			ret = nand_read_data_op(chip, oob, chip->ecc.postpad,
						false);
			if (ret)
				return ret;

			oob += chip->ecc.postpad;
		}

		if (stat == -EBADMSG &&
		    (chip->ecc.options & NAND_ECC_GENERIC_ERASED_CHECK)) {
			/* check for empty pages with bitflips */
			stat = nand_check_erased_ecc_chunk(p, chip->ecc.size,
							   oob - eccpadbytes,
							   eccpadbytes,
							   NULL, 0,
							   chip->ecc.strength);
		}

		if (stat < 0) {
			mtd->ecc_stats.failed++;
		} else {
			mtd->ecc_stats.corrected += stat;
			max_bitflips = max_t(unsigned int, max_bitflips, stat);
		}
	}

	/* Calculate remaining oob bytes */
	i = mtd->oobsize - (oob - chip->oob_poi);
	if (i) {
		ret = nand_read_data_op(chip, oob, i, false);
		if (ret)
			return ret;
	}

	return max_bitflips;
}

/**
 * nand_transfer_oob - [INTERN] Transfer oob to client buffer
 * @chip: nand chip structure
 * @oob: oob destination address
 * @ops: oob ops structure
 * @len: size of oob to transfer
 */
static uint8_t *nand_transfer_oob(struct nand_chip *chip, uint8_t *oob,
				  struct mtd_oob_ops *ops, size_t len)
{
	switch (ops->mode) {

	case MTD_OPS_PLACE_OOB:
	case MTD_OPS_RAW:
		memcpy(oob, chip->oob_poi + ops->ooboffs, len);
		return oob + len;

	case MTD_OPS_AUTO_OOB: {
		struct nand_oobfree *free = chip->ecc.layout->oobfree;
		uint32_t boffs = 0, roffs = ops->ooboffs;
		size_t bytes = 0;

		for (; free->length && len; free++, len -= bytes) {
			/* Read request not from offset 0? */
			if (unlikely(roffs)) {
				if (roffs >= free->length) {
					roffs -= free->length;
					continue;
				}
				boffs = free->offset + roffs;
				bytes = min_t(size_t, len,
					      (free->length - roffs));
				roffs = 0;
			} else {
				bytes = min_t(size_t, len, free->length);
				boffs = free->offset;
			}
			memcpy(oob, chip->oob_poi + boffs, bytes);
			oob += bytes;
		}
		return oob;
	}
	default:
		BUG();
	}
	return NULL;
}

/**
 * nand_setup_read_retry - [INTERN] Set the READ RETRY mode
 * @mtd: MTD device structure
 * @retry_mode: the retry mode to use
 *
 * Some vendors supply a special command to shift the Vt threshold, to be used
 * when there are too many bitflips in a page (i.e., ECC error). After setting
 * a new threshold, the host should retry reading the page.
 */
static int nand_setup_read_retry(struct mtd_info *mtd, int retry_mode)
{
	struct nand_chip *chip = mtd_to_nand(mtd);

	pr_debug("setting READ RETRY mode %d\n", retry_mode);

	if (retry_mode >= chip->read_retries)
		return -EINVAL;

	if (!chip->setup_read_retry)
		return -EOPNOTSUPP;

	return chip->setup_read_retry(mtd, retry_mode);
}

/**
 * nand_do_read_ops - [INTERN] Read data with ECC
 * @mtd: MTD device structure
 * @from: offset to read from
 * @ops: oob ops structure
 *
 * Internal function. Called with chip held.
 */
static int nand_do_read_ops(struct mtd_info *mtd, loff_t from,
			    struct mtd_oob_ops *ops)
{
	int chipnr, page, realpage, col, bytes, aligned, oob_required;
	struct nand_chip *chip = mtd_to_nand(mtd);
	int ret = 0;
	uint32_t readlen = ops->len;
	uint32_t oobreadlen = ops->ooblen;
	uint32_t max_oobsize = mtd_oobavail(mtd, ops);

	uint8_t *bufpoi, *oob, *buf;
	int use_bufpoi;
	unsigned int max_bitflips = 0;
	int retry_mode = 0;
	bool ecc_fail = false;

	chipnr = (int)(from >> chip->chip_shift);
	chip->select_chip(mtd, chipnr);

	realpage = (int)(from >> chip->page_shift);
	page = realpage & chip->pagemask;

	col = (int)(from & (mtd->writesize - 1));

	buf = ops->datbuf;
	oob = ops->oobbuf;
	oob_required = oob ? 1 : 0;

	while (1) {
		unsigned int ecc_failures = mtd->ecc_stats.failed;

		WATCHDOG_RESET();
		bytes = min(mtd->writesize - col, readlen);
		aligned = (bytes == mtd->writesize);

		if (!aligned)
			use_bufpoi = 1;
		else if (chip->options & NAND_USE_BOUNCE_BUFFER)
			use_bufpoi = !IS_ALIGNED((unsigned long)buf,
						 chip->buf_align);
		else
			use_bufpoi = 0;

		/* Is the current page in the buffer? */
		if (realpage != chip->pagebuf || oob) {
			bufpoi = use_bufpoi ? chip->buffers->databuf : buf;

			if (use_bufpoi && aligned)
				pr_debug("%s: using read bounce buffer for buf@%p\n",
						 __func__, buf);

read_retry:
			if (nand_standard_page_accessors(&chip->ecc)) {
				ret = nand_read_page_op(chip, page, 0, NULL, 0);
				if (ret)
					break;
			}

			/*
			 * Now read the page into the buffer.  Absent an error,
			 * the read methods return max bitflips per ecc step.
			 */
			if (unlikely(ops->mode == MTD_OPS_RAW))
				ret = chip->ecc.read_page_raw(mtd, chip, bufpoi,
							      oob_required,
							      page);
			else if (!aligned && NAND_HAS_SUBPAGE_READ(chip) &&
				 !oob)
				ret = chip->ecc.read_subpage(mtd, chip,
							col, bytes, bufpoi,
							page);
			else
				ret = chip->ecc.read_page(mtd, chip, bufpoi,
							  oob_required, page);
			if (ret < 0) {
				if (use_bufpoi)
					/* Invalidate page cache */
					chip->pagebuf = -1;
				break;
			}

			max_bitflips = max_t(unsigned int, max_bitflips, ret);

			/* Transfer not aligned data */
			if (use_bufpoi) {
				if (!NAND_HAS_SUBPAGE_READ(chip) && !oob &&
				    !(mtd->ecc_stats.failed - ecc_failures) &&
				    (ops->mode != MTD_OPS_RAW)) {
					chip->pagebuf = realpage;
					chip->pagebuf_bitflips = ret;
				} else {
					/* Invalidate page cache */
					chip->pagebuf = -1;
				}
				memcpy(buf, chip->buffers->databuf + col, bytes);
			}

			if (unlikely(oob)) {
				int toread = min(oobreadlen, max_oobsize);

				if (toread) {
					oob = nand_transfer_oob(chip,
						oob, ops, toread);
					oobreadlen -= toread;
				}
			}

			if (chip->options & NAND_NEED_READRDY) {
				/* Apply delay or wait for ready/busy pin */
				if (!chip->dev_ready)
					udelay(chip->chip_delay);
				else
					nand_wait_ready(mtd);
			}

			if (mtd->ecc_stats.failed - ecc_failures) {
				if (retry_mode + 1 < chip->read_retries) {
					retry_mode++;
					ret = nand_setup_read_retry(mtd,
							retry_mode);
					if (ret < 0)
						break;

					/* Reset failures; retry */
					mtd->ecc_stats.failed = ecc_failures;
					goto read_retry;
				} else {
					/* No more retry modes; real failure */
					ecc_fail = true;
				}
			}

			buf += bytes;
		} else {
			memcpy(buf, chip->buffers->databuf + col, bytes);
			buf += bytes;
			max_bitflips = max_t(unsigned int, max_bitflips,
					     chip->pagebuf_bitflips);
		}

		readlen -= bytes;

		/* Reset to retry mode 0 */
		if (retry_mode) {
			ret = nand_setup_read_retry(mtd, 0);
			if (ret < 0)
				break;
			retry_mode = 0;
		}

		if (!readlen)
			break;

		/* For subsequent reads align to page boundary */
		col = 0;
		/* Increment page address */
		realpage++;

		page = realpage & chip->pagemask;
		/* Check, if we cross a chip boundary */
		if (!page) {
			chipnr++;
			chip->select_chip(mtd, -1);
			chip->select_chip(mtd, chipnr);
		}
	}
	chip->select_chip(mtd, -1);

	ops->retlen = ops->len - (size_t) readlen;
	if (oob)
		ops->oobretlen = ops->ooblen - oobreadlen;

	if (ret < 0)
		return ret;

	if (ecc_fail)
		return -EBADMSG;

	return max_bitflips;
}

/**
 * nand_read_oob_std - [REPLACEABLE] the most common OOB data read function
 * @mtd: mtd info structure
 * @chip: nand chip info structure
 * @page: page number to read
 */
static int nand_read_oob_std(struct mtd_info *mtd, struct nand_chip *chip,
			     int page)
{
	return nand_read_oob_op(chip, page, 0, chip->oob_poi, mtd->oobsize);
}

/**
 * nand_read_oob_syndrome - [REPLACEABLE] OOB data read function for HW ECC
 *			    with syndromes
 * @mtd: mtd info structure
 * @chip: nand chip info structure
 * @page: page number to read
 */
static int nand_read_oob_syndrome(struct mtd_info *mtd, struct nand_chip *chip,
				  int page)
{
	int length = mtd->oobsize;
	int chunk = chip->ecc.bytes + chip->ecc.prepad + chip->ecc.postpad;
	int eccsize = chip->ecc.size;
	uint8_t *bufpoi = chip->oob_poi;
	int i, toread, sndrnd = 0, pos, ret;

	ret = nand_read_page_op(chip, page, chip->ecc.size, NULL, 0);
	if (ret)
		return ret;

	for (i = 0; i < chip->ecc.steps; i++) {
		if (sndrnd) {
			int ret;

			pos = eccsize + i * (eccsize + chunk);
			if (mtd->writesize > 512)
				ret = nand_change_read_column_op(chip, pos,
								 NULL, 0,
								 false);
			else
				ret = nand_read_page_op(chip, page, pos, NULL,
							0);

			if (ret)
				return ret;
		} else
			sndrnd = 1;
		toread = min_t(int, length, chunk);

		ret = nand_read_data_op(chip, bufpoi, toread, false);
		if (ret)
			return ret;

		bufpoi += toread;
		length -= toread;
	}
	if (length > 0) {
		ret = nand_read_data_op(chip, bufpoi, length, false);
		if (ret)
			return ret;
	}

	return 0;
}

/**
 * nand_write_oob_std - [REPLACEABLE] the most common OOB data write function
 * @mtd: mtd info structure
 * @chip: nand chip info structure
 * @page: page number to write
 */
static int nand_write_oob_std(struct mtd_info *mtd, struct nand_chip *chip,
			      int page)
{
	return nand_prog_page_op(chip, page, mtd->writesize, chip->oob_poi,
				 mtd->oobsize);
}

/**
 * nand_write_oob_syndrome - [REPLACEABLE] OOB data write function for HW ECC
 *			     with syndrome - only for large page flash
 * @mtd: mtd info structure
 * @chip: nand chip info structure
 * @page: page number to write
 */
static int nand_write_oob_syndrome(struct mtd_info *mtd,
				   struct nand_chip *chip, int page)
{
	int chunk = chip->ecc.bytes + chip->ecc.prepad + chip->ecc.postpad;
	int eccsize = chip->ecc.size, length = mtd->oobsize;
	int ret, i, len, pos, sndcmd = 0, steps = chip->ecc.steps;
	const uint8_t *bufpoi = chip->oob_poi;

	/*
	 * data-ecc-data-ecc ... ecc-oob
	 * or
	 * data-pad-ecc-pad-data-pad .... ecc-pad-oob
	 */
	if (!chip->ecc.prepad && !chip->ecc.postpad) {
		pos = steps * (eccsize + chunk);
		steps = 0;
	} else
		pos = eccsize;

	ret = nand_prog_page_begin_op(chip, page, pos, NULL, 0);
	if (ret)
		return ret;

	for (i = 0; i < steps; i++) {
		if (sndcmd) {
			if (mtd->writesize <= 512) {
				uint32_t fill = 0xFFFFFFFF;

				len = eccsize;
				while (len > 0) {
					int num = min_t(int, len, 4);

					ret = nand_write_data_op(chip, &fill,
								 num, false);
					if (ret)
						return ret;

					len -= num;
				}
			} else {
				pos = eccsize + i * (eccsize + chunk);
				ret = nand_change_write_column_op(chip, pos,
								  NULL, 0,
								  false);
				if (ret)
					return ret;
			}
		} else
			sndcmd = 1;
		len = min_t(int, length, chunk);

		ret = nand_write_data_op(chip, bufpoi, len, false);
		if (ret)
			return ret;

		bufpoi += len;
		length -= len;
	}
	if (length > 0) {
		ret = nand_write_data_op(chip, bufpoi, length, false);
		if (ret)
			return ret;
	}

	return nand_prog_page_end_op(chip);
}

/**
 * nand_do_read_oob - [INTERN] NAND read out-of-band
 * @mtd: MTD device structure
 * @from: offset to read from
 * @ops: oob operations description structure
 *
 * NAND read out-of-band data from the spare area.
 */
static int nand_do_read_oob(struct mtd_info *mtd, loff_t from,
			    struct mtd_oob_ops *ops)
{
	int page, realpage, chipnr;
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct mtd_ecc_stats stats;
	int readlen = ops->ooblen;
	int len;
	uint8_t *buf = ops->oobbuf;
	int ret = 0;

	pr_debug("%s: from = 0x%08Lx, len = %i\n",
			__func__, (unsigned long long)from, readlen);

	stats = mtd->ecc_stats;

	len = mtd_oobavail(mtd, ops);

	if (unlikely(ops->ooboffs >= len)) {
		pr_debug("%s: attempt to start read outside oob\n",
				__func__);
		return -EINVAL;
	}

	/* Do not allow reads past end of device */
	if (unlikely(from >= mtd->size ||
		     ops->ooboffs + readlen > ((mtd->size >> chip->page_shift) -
					(from >> chip->page_shift)) * len)) {
		pr_debug("%s: attempt to read beyond end of device\n",
				__func__);
		return -EINVAL;
	}

	chipnr = (int)(from >> chip->chip_shift);
	chip->select_chip(mtd, chipnr);

	/* Shift to get page */
	realpage = (int)(from >> chip->page_shift);
	page = realpage & chip->pagemask;

	while (1) {
		WATCHDOG_RESET();

		if (ops->mode == MTD_OPS_RAW)
			ret = chip->ecc.read_oob_raw(mtd, chip, page);
		else
			ret = chip->ecc.read_oob(mtd, chip, page);

		if (ret < 0)
			break;

		len = min(len, readlen);
		buf = nand_transfer_oob(chip, buf, ops, len);

		if (chip->options & NAND_NEED_READRDY) {
			/* Apply delay or wait for ready/busy pin */
			if (!chip->dev_ready)
				udelay(chip->chip_delay);
			else
				nand_wait_ready(mtd);
		}

		readlen -= len;
		if (!readlen)
			break;

		/* Increment page address */
		realpage++;

		page = realpage & chip->pagemask;
		/* Check, if we cross a chip boundary */
		if (!page) {
			chipnr++;
			chip->select_chip(mtd, -1);
			chip->select_chip(mtd, chipnr);
		}
	}
	chip->select_chip(mtd, -1);

	ops->oobretlen = ops->ooblen - readlen;

	if (ret < 0)
		return ret;

	if (mtd->ecc_stats.failed - stats.failed)
		return -EBADMSG;

	return  mtd->ecc_stats.corrected - stats.corrected ? -EUCLEAN : 0;
}

/**
 * nand_read_oob - [MTD Interface] NAND read data and/or out-of-band
 * @mtd: MTD device structure
 * @from: offset to read from
 * @ops: oob operation description structure
 *
 * NAND read data and/or out-of-band data.
 */
static int nand_read_oob(struct mtd_info *mtd, loff_t from,
			 struct mtd_oob_ops *ops)
{
	int ret = -ENOTSUPP;

	ops->retlen = 0;

	/* Do not allow reads past end of device */
	if (ops->datbuf && (from + ops->len) > mtd->size) {
		pr_debug("%s: attempt to read beyond end of device\n",
				__func__);
		return -EINVAL;
	}

	nand_get_device(mtd, FL_READING);

	switch (ops->mode) {
	case MTD_OPS_PLACE_OOB:
	case MTD_OPS_AUTO_OOB:
	case MTD_OPS_RAW:
		break;

	default:
		goto out;
	}

	if (!ops->datbuf)
		ret = nand_do_read_oob(mtd, from, ops);
	else
		ret = nand_do_read_ops(mtd, from, ops);

out:
	nand_release_device(mtd);
	return ret;
}


/**
 * nand_write_page_raw - [INTERN] raw page write function
 * @mtd: mtd info structure
 * @chip: nand chip info structure
 * @buf: data buffer
 * @oob_required: must write chip->oob_poi to OOB
 * @page: page number to write
 *
 * Not for syndrome calculating ECC controllers, which use a special oob layout.
 */
static int nand_write_page_raw(struct mtd_info *mtd, struct nand_chip *chip,
			       const uint8_t *buf, int oob_required, int page)
{
	int ret;

	ret = nand_write_data_op(chip, buf, mtd->writesize, false);
	if (ret)
		return ret;

	if (oob_required) {
		ret = nand_write_data_op(chip, chip->oob_poi, mtd->oobsize,
					 false);
		if (ret)
			return ret;
	}

	return 0;
}

/**
 * nand_write_page_raw_syndrome - [INTERN] raw page write function
 * @mtd: mtd info structure
 * @chip: nand chip info structure
 * @buf: data buffer
 * @oob_required: must write chip->oob_poi to OOB
 * @page: page number to write
 *
 * We need a special oob layout and handling even when ECC isn't checked.
 */
static int nand_write_page_raw_syndrome(struct mtd_info *mtd,
					struct nand_chip *chip,
					const uint8_t *buf, int oob_required,
					int page)
{
	int eccsize = chip->ecc.size;
	int eccbytes = chip->ecc.bytes;
	uint8_t *oob = chip->oob_poi;
	int steps, size, ret;

	for (steps = chip->ecc.steps; steps > 0; steps--) {
		ret = nand_write_data_op(chip, buf, eccsize, false);
		if (ret)
			return ret;

		buf += eccsize;

		if (chip->ecc.prepad) {
			ret = nand_write_data_op(chip, oob, chip->ecc.prepad,
						 false);
			if (ret)
				return ret;

			oob += chip->ecc.prepad;
		}

		ret = nand_write_data_op(chip, oob, eccbytes, false);
		if (ret)
			return ret;

		oob += eccbytes;

		if (chip->ecc.postpad) {
			ret = nand_write_data_op(chip, oob, chip->ecc.postpad,
						 false);
			if (ret)
				return ret;

			oob += chip->ecc.postpad;
		}
	}

	size = mtd->oobsize - (oob - chip->oob_poi);
	if (size) {
		ret = nand_write_data_op(chip, oob, size, false);
		if (ret)
			return ret;
	}

	return 0;
}
/**
 * nand_write_page_swecc - [REPLACEABLE] software ECC based page write function
 * @mtd: mtd info structure
 * @chip: nand chip info structure
 * @buf: data buffer
 * @oob_required: must write chip->oob_poi to OOB
 * @page: page number to write
 */
static int nand_write_page_swecc(struct mtd_info *mtd, struct nand_chip *chip,
				 const uint8_t *buf, int oob_required,
				 int page)
{
	int i, eccsize = chip->ecc.size;
	int eccbytes = chip->ecc.bytes;
	int eccsteps = chip->ecc.steps;
	uint8_t *ecc_calc = chip->buffers->ecccalc;
	const uint8_t *p = buf;
	uint32_t *eccpos = chip->ecc.layout->eccpos;

	/* Software ECC calculation */
	for (i = 0; eccsteps; eccsteps--, i += eccbytes, p += eccsize)
		chip->ecc.calculate(mtd, p, &ecc_calc[i]);

	for (i = 0; i < chip->ecc.total; i++)
		chip->oob_poi[eccpos[i]] = ecc_calc[i];

	return chip->ecc.write_page_raw(mtd, chip, buf, 1, page);
}

/**
 * nand_write_page_hwecc - [REPLACEABLE] hardware ECC based page write function
 * @mtd: mtd info structure
 * @chip: nand chip info structure
 * @buf: data buffer
 * @oob_required: must write chip->oob_poi to OOB
 * @page: page number to write
 */
static int nand_write_page_hwecc(struct mtd_info *mtd, struct nand_chip *chip,
				  const uint8_t *buf, int oob_required,
				  int page)
{
	int i, eccsize = chip->ecc.size;
	int eccbytes = chip->ecc.bytes;
	int eccsteps = chip->ecc.steps;
	uint8_t *ecc_calc = chip->buffers->ecccalc;
	const uint8_t *p = buf;
	uint32_t *eccpos = chip->ecc.layout->eccpos;
	int ret;

	for (i = 0; eccsteps; eccsteps--, i += eccbytes, p += eccsize) {
		chip->ecc.hwctl(mtd, NAND_ECC_WRITE);

		ret = nand_write_data_op(chip, p, eccsize, false);
		if (ret)
			return ret;

		chip->ecc.calculate(mtd, p, &ecc_calc[i]);
	}

	for (i = 0; i < chip->ecc.total; i++)
		chip->oob_poi[eccpos[i]] = ecc_calc[i];

	ret = nand_write_data_op(chip, chip->oob_poi, mtd->oobsize, false);
	if (ret)
		return ret;

	return 0;
}


/**
 * nand_write_subpage_hwecc - [REPLACEABLE] hardware ECC based subpage write
 * @mtd:	mtd info structure
 * @chip:	nand chip info structure
 * @offset:	column address of subpage within the page
 * @data_len:	data length
 * @buf:	data buffer
 * @oob_required: must write chip->oob_poi to OOB
 * @page: page number to write
 */
static int nand_write_subpage_hwecc(struct mtd_info *mtd,
				struct nand_chip *chip, uint32_t offset,
				uint32_t data_len, const uint8_t *buf,
				int oob_required, int page)
{
	uint8_t *oob_buf  = chip->oob_poi;
	uint8_t *ecc_calc = chip->buffers->ecccalc;
	int ecc_size      = chip->ecc.size;
	int ecc_bytes     = chip->ecc.bytes;
	int ecc_steps     = chip->ecc.steps;
	uint32_t *eccpos  = chip->ecc.layout->eccpos;
	uint32_t start_step = offset / ecc_size;
	uint32_t end_step   = (offset + data_len - 1) / ecc_size;
	int oob_bytes       = mtd->oobsize / ecc_steps;
	int step, i;
	int ret;

	for (step = 0; step < ecc_steps; step++) {
		/* configure controller for WRITE access */
		chip->ecc.hwctl(mtd, NAND_ECC_WRITE);

		/* write data (untouched subpages already masked by 0xFF) */
		ret = nand_write_data_op(chip, buf, ecc_size, false);
		if (ret)
			return ret;

		/* mask ECC of un-touched subpages by padding 0xFF */
		if ((step < start_step) || (step > end_step))
			memset(ecc_calc, 0xff, ecc_bytes);
		else
			chip->ecc.calculate(mtd, buf, ecc_calc);

		/* mask OOB of un-touched subpages by padding 0xFF */
		/* if oob_required, preserve OOB metadata of written subpage */
		if (!oob_required || (step < start_step) || (step > end_step))
			memset(oob_buf, 0xff, oob_bytes);

		buf += ecc_size;
		ecc_calc += ecc_bytes;
		oob_buf  += oob_bytes;
	}

	/* copy calculated ECC for whole page to chip->buffer->oob */
	/* this include masked-value(0xFF) for unwritten subpages */
	ecc_calc = chip->buffers->ecccalc;
	for (i = 0; i < chip->ecc.total; i++)
		chip->oob_poi[eccpos[i]] = ecc_calc[i];

	/* write OOB buffer to NAND device */
	ret = nand_write_data_op(chip, chip->oob_poi, mtd->oobsize, false);
	if (ret)
		return ret;

	return 0;
}


/**
 * nand_write_page_syndrome - [REPLACEABLE] hardware ECC syndrome based page write
 * @mtd: mtd info structure
 * @chip: nand chip info structure
 * @buf: data buffer
 * @oob_required: must write chip->oob_poi to OOB
 * @page: page number to write
 *
 * The hw generator calculates the error syndrome automatically. Therefore we
 * need a special oob layout and handling.
 */
static int nand_write_page_syndrome(struct mtd_info *mtd,
				    struct nand_chip *chip,
				    const uint8_t *buf, int oob_required,
				    int page)
{
	int i, eccsize = chip->ecc.size;
	int eccbytes = chip->ecc.bytes;
	int eccsteps = chip->ecc.steps;
	const uint8_t *p = buf;
	uint8_t *oob = chip->oob_poi;
	int ret;

	for (i = 0; eccsteps; eccsteps--, i += eccbytes, p += eccsize) {
		chip->ecc.hwctl(mtd, NAND_ECC_WRITE);

		ret = nand_write_data_op(chip, p, eccsize, false);
		if (ret)
			return ret;

		if (chip->ecc.prepad) {
			ret = nand_write_data_op(chip, oob, chip->ecc.prepad,
						 false);
			if (ret)
				return ret;

			oob += chip->ecc.prepad;
		}

		chip->ecc.calculate(mtd, p, oob);

		ret = nand_write_data_op(chip, oob, eccbytes, false);
		if (ret)
			return ret;

		oob += eccbytes;

		if (chip->ecc.postpad) {
			ret = nand_write_data_op(chip, oob, chip->ecc.postpad,
						 false);
			if (ret)
				return ret;

			oob += chip->ecc.postpad;
		}
	}

	/* Calculate remaining oob bytes */
	i = mtd->oobsize - (oob - chip->oob_poi);
	if (i) {
		ret = nand_write_data_op(chip, oob, i, false);
		if (ret)
			return ret;
	}

	return 0;
}

/**
 * nand_write_page - [REPLACEABLE] write one page
 * @mtd: MTD device structure
 * @chip: NAND chip descriptor
 * @offset: address offset within the page
 * @data_len: length of actual data to be written
 * @buf: the data to write
 * @oob_required: must write chip->oob_poi to OOB
 * @page: page number to write
 * @raw: use _raw version of write_page
 */
static int nand_write_page(struct mtd_info *mtd, struct nand_chip *chip,
		uint32_t offset, int data_len, const uint8_t *buf,
		int oob_required, int page, int raw)
{
	int status, subpage;

	if (!(chip->options & NAND_NO_SUBPAGE_WRITE) &&
		chip->ecc.write_subpage)
		subpage = offset || (data_len < mtd->writesize);
	else
		subpage = 0;

	if (nand_standard_page_accessors(&chip->ecc)) {
		status = nand_prog_page_begin_op(chip, page, 0, NULL, 0);
		if (status)
			return status;
	}

	if (unlikely(raw))
		status = chip->ecc.write_page_raw(mtd, chip, buf,
						  oob_required, page);
	else if (subpage)
		status = chip->ecc.write_subpage(mtd, chip, offset, data_len,
						 buf, oob_required, page);
	else
		status = chip->ecc.write_page(mtd, chip, buf, oob_required,
					      page);

	if (status < 0)
		return status;

	if (nand_standard_page_accessors(&chip->ecc))
		return nand_prog_page_end_op(chip);

	return 0;
}

/**
 * nand_fill_oob - [INTERN] Transfer client buffer to oob
 * @mtd: MTD device structure
 * @oob: oob data buffer
 * @len: oob data write length
 * @ops: oob ops structure
 */
static uint8_t *nand_fill_oob(struct mtd_info *mtd, uint8_t *oob, size_t len,
			      struct mtd_oob_ops *ops)
{
	struct nand_chip *chip = mtd_to_nand(mtd);

	/*
	 * Initialise to all 0xFF, to avoid the possibility of left over OOB
	 * data from a previous OOB read.
	 */
	memset(chip->oob_poi, 0xff, mtd->oobsize);

	switch (ops->mode) {

	case MTD_OPS_PLACE_OOB:
	case MTD_OPS_RAW:
		memcpy(chip->oob_poi + ops->ooboffs, oob, len);
		return oob + len;

	case MTD_OPS_AUTO_OOB: {
		struct nand_oobfree *free = chip->ecc.layout->oobfree;
		uint32_t boffs = 0, woffs = ops->ooboffs;
		size_t bytes = 0;

		for (; free->length && len; free++, len -= bytes) {
			/* Write request not from offset 0? */
			if (unlikely(woffs)) {
				if (woffs >= free->length) {
					woffs -= free->length;
					continue;
				}
				boffs = free->offset + woffs;
				bytes = min_t(size_t, len,
					      (free->length - woffs));
				woffs = 0;
			} else {
				bytes = min_t(size_t, len, free->length);
				boffs = free->offset;
			}
			memcpy(chip->oob_poi + boffs, oob, bytes);
			oob += bytes;
		}
		return oob;
	}
	default:
		BUG();
	}
	return NULL;
}

#define NOTALIGNED(x)	((x & (chip->subpagesize - 1)) != 0)

/**
 * nand_do_write_ops - [INTERN] NAND write with ECC
 * @mtd: MTD device structure
 * @to: offset to write to
 * @ops: oob operations description structure
 *
 * NAND write with ECC.
 */
static int nand_do_write_ops(struct mtd_info *mtd, loff_t to,
			     struct mtd_oob_ops *ops)
{
	int chipnr, realpage, page, column;
	struct nand_chip *chip = mtd_to_nand(mtd);
	uint32_t writelen = ops->len;

	uint32_t oobwritelen = ops->ooblen;
	uint32_t oobmaxlen = mtd_oobavail(mtd, ops);

	uint8_t *oob = ops->oobbuf;
	uint8_t *buf = ops->datbuf;
	int ret;
	int oob_required = oob ? 1 : 0;

	ops->retlen = 0;
	if (!writelen)
		return 0;

	/* Reject writes, which are not page aligned */
	if (NOTALIGNED(to)) {
		pr_notice("%s: attempt to write non page aligned data\n",
			   __func__);
		return -EINVAL;
	}

	column = to & (mtd->writesize - 1);

	chipnr = (int)(to >> chip->chip_shift);
	chip->select_chip(mtd, chipnr);

	/* Check, if it is write protected */
	if (nand_check_wp(mtd)) {
		ret = -EIO;
		goto err_out;
	}

	realpage = (int)(to >> chip->page_shift);
	page = realpage & chip->pagemask;

	/* Invalidate the page cache, when we write to the cached page */
	if (to <= ((loff_t)chip->pagebuf << chip->page_shift) &&
	    ((loff_t)chip->pagebuf << chip->page_shift) < (to + ops->len))
		chip->pagebuf = -1;

	/* Don't allow multipage oob writes with offset */
	if (oob && ops->ooboffs && (ops->ooboffs + ops->ooblen > oobmaxlen)) {
		ret = -EINVAL;
		goto err_out;
	}

	while (1) {
		int bytes = mtd->writesize;
		uint8_t *wbuf = buf;
		int use_bufpoi;
		int part_pagewr = (column || writelen < mtd->writesize);

		if (part_pagewr)
			use_bufpoi = 1;
		else if (chip->options & NAND_USE_BOUNCE_BUFFER)
			use_bufpoi = !IS_ALIGNED((unsigned long)buf,
						 chip->buf_align);
		else
			use_bufpoi = 0;

		WATCHDOG_RESET();
		/* Partial page write?, or need to use bounce buffer */
		if (use_bufpoi) {
			pr_debug("%s: using write bounce buffer for buf@%p\n",
					 __func__, buf);
			if (part_pagewr)
				bytes = min_t(int, bytes - column, writelen);
			chip->pagebuf = -1;
			memset(chip->buffers->databuf, 0xff, mtd->writesize);
			memcpy(&chip->buffers->databuf[column], buf, bytes);
			wbuf = chip->buffers->databuf;
		}

		if (unlikely(oob)) {
			size_t len = min(oobwritelen, oobmaxlen);
			oob = nand_fill_oob(mtd, oob, len, ops);
			oobwritelen -= len;
		} else {
			/* We still need to erase leftover OOB data */
			memset(chip->oob_poi, 0xff, mtd->oobsize);
		}
		ret = chip->write_page(mtd, chip, column, bytes, wbuf,
					oob_required, page,
					(ops->mode == MTD_OPS_RAW));
		if (ret)
			break;

		writelen -= bytes;
		if (!writelen)
			break;

		column = 0;
		buf += bytes;
		realpage++;

		page = realpage & chip->pagemask;
		/* Check, if we cross a chip boundary */
		if (!page) {
			chipnr++;
			chip->select_chip(mtd, -1);
			chip->select_chip(mtd, chipnr);
		}
	}

	ops->retlen = ops->len - writelen;
	if (unlikely(oob))
		ops->oobretlen = ops->ooblen;

err_out:
	chip->select_chip(mtd, -1);
	return ret;
}

/**
 * panic_nand_write - [MTD Interface] NAND write with ECC
 * @mtd: MTD device structure
 * @to: offset to write to
 * @len: number of bytes to write
 * @retlen: pointer to variable to store the number of written bytes
 * @buf: the data to write
 *
 * NAND write with ECC. Used when performing writes in interrupt context, this
 * may for example be called by mtdoops when writing an oops while in panic.
 */
static int panic_nand_write(struct mtd_info *mtd, loff_t to, size_t len,
			    size_t *retlen, const uint8_t *buf)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct mtd_oob_ops ops;
	int ret;

	/* Wait for the device to get ready */
	panic_nand_wait(mtd, chip, 400);

	/* Grab the device */
	panic_nand_get_device(chip, mtd, FL_WRITING);

	memset(&ops, 0, sizeof(ops));
	ops.len = len;
	ops.datbuf = (uint8_t *)buf;
	ops.mode = MTD_OPS_PLACE_OOB;

	ret = nand_do_write_ops(mtd, to, &ops);

	*retlen = ops.retlen;
	return ret;
}

/**
 * nand_do_write_oob - [MTD Interface] NAND write out-of-band
 * @mtd: MTD device structure
 * @to: offset to write to
 * @ops: oob operation description structure
 *
 * NAND write out-of-band.
 */
static int nand_do_write_oob(struct mtd_info *mtd, loff_t to,
			     struct mtd_oob_ops *ops)
{
	int chipnr, page, status, len;
	struct nand_chip *chip = mtd_to_nand(mtd);

	pr_debug("%s: to = 0x%08x, len = %i\n",
			 __func__, (unsigned int)to, (int)ops->ooblen);

	len = mtd_oobavail(mtd, ops);

	/* Do not allow write past end of page */
	if ((ops->ooboffs + ops->ooblen) > len) {
		pr_debug("%s: attempt to write past end of page\n",
				__func__);
		return -EINVAL;
	}

	if (unlikely(ops->ooboffs >= len)) {
		pr_debug("%s: attempt to start write outside oob\n",
				__func__);
		return -EINVAL;
	}

	/* Do not allow write past end of device */
	if (unlikely(to >= mtd->size ||
		     ops->ooboffs + ops->ooblen >
			((mtd->size >> chip->page_shift) -
			 (to >> chip->page_shift)) * len)) {
		pr_debug("%s: attempt to write beyond end of device\n",
				__func__);
		return -EINVAL;
	}

	chipnr = (int)(to >> chip->chip_shift);

	/*
	 * Reset the chip. Some chips (like the Toshiba TC5832DC found in one
	 * of my DiskOnChip 2000 test units) will clear the whole data page too
	 * if we don't do this. I have no clue why, but I seem to have 'fixed'
	 * it in the doc2000 driver in August 1999.  dwmw2.
	 */
	nand_reset(chip, chipnr);

	chip->select_chip(mtd, chipnr);

	/* Shift to get page */
	page = (int)(to >> chip->page_shift);

	/* Check, if it is write protected */
	if (nand_check_wp(mtd)) {
		chip->select_chip(mtd, -1);
		return -EROFS;
	}

	/* Invalidate the page cache, if we write to the cached page */
	if (page == chip->pagebuf)
		chip->pagebuf = -1;

	nand_fill_oob(mtd, ops->oobbuf, ops->ooblen, ops);

	if (ops->mode == MTD_OPS_RAW)
		status = chip->ecc.write_oob_raw(mtd, chip, page & chip->pagemask);
	else
		status = chip->ecc.write_oob(mtd, chip, page & chip->pagemask);

	chip->select_chip(mtd, -1);

	if (status)
		return status;

	ops->oobretlen = ops->ooblen;

	return 0;
}

/**
 * nand_write_oob - [MTD Interface] NAND write data and/or out-of-band
 * @mtd: MTD device structure
 * @to: offset to write to
 * @ops: oob operation description structure
 */
static int nand_write_oob(struct mtd_info *mtd, loff_t to,
			  struct mtd_oob_ops *ops)
{
	int ret = -ENOTSUPP;

	ops->retlen = 0;

	/* Do not allow writes past end of device */
	if (ops->datbuf && (to + ops->len) > mtd->size) {
		pr_debug("%s: attempt to write beyond end of device\n",
				__func__);
		return -EINVAL;
	}

	nand_get_device(mtd, FL_WRITING);

	switch (ops->mode) {
	case MTD_OPS_PLACE_OOB:
	case MTD_OPS_AUTO_OOB:
	case MTD_OPS_RAW:
		break;

	default:
		goto out;
	}

	if (!ops->datbuf)
		ret = nand_do_write_oob(mtd, to, ops);
	else
		ret = nand_do_write_ops(mtd, to, ops);

out:
	nand_release_device(mtd);
	return ret;
}

/**
 * single_erase - [GENERIC] NAND standard block erase command function
 * @mtd: MTD device structure
 * @page: the page address of the block which will be erased
 *
 * Standard erase command for NAND chips. Returns NAND status.
 */
static int single_erase(struct mtd_info *mtd, int page)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	unsigned int eraseblock;

	/* Send commands to erase a block */
	eraseblock = page >> (chip->phys_erase_shift - chip->page_shift);

	return nand_erase_op(chip, eraseblock);
}

/**
 * nand_erase - [MTD Interface] erase block(s)
 * @mtd: MTD device structure
 * @instr: erase instruction
 *
 * Erase one ore more blocks.
 */
static int nand_erase(struct mtd_info *mtd, struct erase_info *instr)
{
	return nand_erase_nand(mtd, instr, 0);
}

/**
 * nand_erase_nand - [INTERN] erase block(s)
 * @mtd: MTD device structure
 * @instr: erase instruction
 * @allowbbt: allow erasing the bbt area
 *
 * Erase one ore more blocks.
 */
int nand_erase_nand(struct mtd_info *mtd, struct erase_info *instr,
		    int allowbbt)
{
	int page, status, pages_per_block, ret, chipnr;
	struct nand_chip *chip = mtd_to_nand(mtd);
	loff_t len;

	pr_debug("%s: start = 0x%012llx, len = %llu\n",
			__func__, (unsigned long long)instr->addr,
			(unsigned long long)instr->len);

	if (check_offs_len(mtd, instr->addr, instr->len))
		return -EINVAL;

	/* Grab the lock and see if the device is available */
	nand_get_device(mtd, FL_ERASING);

	/* Shift to get first page */
	page = (int)(instr->addr >> chip->page_shift);
	chipnr = (int)(instr->addr >> chip->chip_shift);

	/* Calculate pages in each block */
	pages_per_block = 1 << (chip->phys_erase_shift - chip->page_shift);

	/* Select the NAND device */
	chip->select_chip(mtd, chipnr);

	/* Check, if it is write protected */
	if (nand_check_wp(mtd)) {
		pr_debug("%s: device is write protected!\n",
				__func__);
		instr->state = MTD_ERASE_FAILED;
		goto erase_exit;
	}

	/* Loop through the pages */
	len = instr->len;

	instr->state = MTD_ERASING;

	while (len) {
		WATCHDOG_RESET();

		/* Check if we have a bad block, we do not erase bad blocks! */
		if (!instr->scrub && nand_block_checkbad(mtd, ((loff_t) page) <<
					chip->page_shift, allowbbt)) {
			pr_warn("%s: attempt to erase a bad block at page 0x%08x\n",
				    __func__, page);
			instr->state = MTD_ERASE_FAILED;
			goto erase_exit;
		}

		/*
		 * Invalidate the page cache, if we erase the block which
		 * contains the current cached page.
		 */
		if (page <= chip->pagebuf && chip->pagebuf <
		    (page + pages_per_block))
			chip->pagebuf = -1;

		status = chip->erase(mtd, page & chip->pagemask);

		/* See if block erase succeeded */
		if (status & NAND_STATUS_FAIL) {
			pr_debug("%s: failed erase, page 0x%08x\n",
					__func__, page);
			instr->state = MTD_ERASE_FAILED;
			instr->fail_addr =
				((loff_t)page << chip->page_shift);
			goto erase_exit;
		}

		/* Increment page address and decrement length */
		len -= (1ULL << chip->phys_erase_shift);
		page += pages_per_block;

		/* Check, if we cross a chip boundary */
		if (len && !(page & chip->pagemask)) {
			chipnr++;
			chip->select_chip(mtd, -1);
			chip->select_chip(mtd, chipnr);
		}
	}
	instr->state = MTD_ERASE_DONE;

erase_exit:

	ret = instr->state == MTD_ERASE_DONE ? 0 : -EIO;

	/* Deselect and wake up anyone waiting on the device */
	chip->select_chip(mtd, -1);
	nand_release_device(mtd);

	/* Do call back function */
	if (!ret)
		mtd_erase_callback(instr);

	/* Return more or less happy */
	return ret;
}

/**
 * nand_sync - [MTD Interface] sync
 * @mtd: MTD device structure
 *
 * Sync is actually a wait for chip ready function.
 */
static void nand_sync(struct mtd_info *mtd)
{
	pr_debug("%s: called\n", __func__);

	/* Grab the lock and see if the device is available */
	nand_get_device(mtd, FL_SYNCING);
	/* Release it and go back */
	nand_release_device(mtd);
}

/**
 * nand_block_isbad - [MTD Interface] Check if block at offset is bad
 * @mtd: MTD device structure
 * @offs: offset relative to mtd start
 */
static int nand_block_isbad(struct mtd_info *mtd, loff_t offs)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	int chipnr = (int)(offs >> chip->chip_shift);
	int ret;

	/* Select the NAND device */
	nand_get_device(mtd, FL_READING);
	chip->select_chip(mtd, chipnr);

	ret = nand_block_checkbad(mtd, offs, 0);

	chip->select_chip(mtd, -1);
	nand_release_device(mtd);

	return ret;
}

/**
 * nand_block_markbad - [MTD Interface] Mark block at the given offset as bad
 * @mtd: MTD device structure
 * @ofs: offset relative to mtd start
 */
static int nand_block_markbad(struct mtd_info *mtd, loff_t ofs)
{
	int ret;

	ret = nand_block_isbad(mtd, ofs);
	if (ret) {
		/* If it was bad already, return success and do nothing */
		if (ret > 0)
			return 0;
		return ret;
	}

	return nand_block_markbad_lowlevel(mtd, ofs);
}

/**
 * nand_onfi_set_features- [REPLACEABLE] set features for ONFI nand
 * @mtd: MTD device structure
 * @chip: nand chip info structure
 * @addr: feature address.
 * @subfeature_param: the subfeature parameters, a four bytes array.
 */
static int nand_onfi_set_features(struct mtd_info *mtd, struct nand_chip *chip,
			int addr, uint8_t *subfeature_param)
{
#ifdef CONFIG_SYS_NAND_ONFI_DETECTION
	if (!chip->onfi_version ||
	    !(le16_to_cpu(chip->onfi_params.opt_cmd)
	      & ONFI_OPT_CMD_SET_GET_FEATURES))
		return -ENOTSUPP;
#endif

	return nand_set_features_op(chip, addr, subfeature_param);
}

/**
 * nand_onfi_get_features- [REPLACEABLE] get features for ONFI nand
 * @mtd: MTD device structure
 * @chip: nand chip info structure
 * @addr: feature address.
 * @subfeature_param: the subfeature parameters, a four bytes array.
 */
static int nand_onfi_get_features(struct mtd_info *mtd, struct nand_chip *chip,
			int addr, uint8_t *subfeature_param)
{
#ifdef CONFIG_SYS_NAND_ONFI_DETECTION
	if (!chip->onfi_version ||
	    !(le16_to_cpu(chip->onfi_params.opt_cmd)
	      & ONFI_OPT_CMD_SET_GET_FEATURES))
		return -ENOTSUPP;
#endif

	return nand_get_features_op(chip, addr, subfeature_param);
}

/* Set default functions */
static void nand_set_defaults(struct nand_chip *chip, int busw)
{
	/* check for proper chip_delay setup, set 20us if not */
	if (!chip->chip_delay)
		chip->chip_delay = 20;

	/* check, if a user supplied command function given */
	if (chip->cmdfunc == NULL)
		chip->cmdfunc = nand_command;

	/* check, if a user supplied wait function given */
	if (chip->waitfunc == NULL)
		chip->waitfunc = nand_wait;

	if (!chip->select_chip)
		chip->select_chip = nand_select_chip;

	/* set for ONFI nand */
	if (!chip->onfi_set_features)
		chip->onfi_set_features = nand_onfi_set_features;
	if (!chip->onfi_get_features)
		chip->onfi_get_features = nand_onfi_get_features;

	/* If called twice, pointers that depend on busw may need to be reset */
	if (!chip->read_byte || chip->read_byte == nand_read_byte)
		chip->read_byte = busw ? nand_read_byte16 : nand_read_byte;
	if (!chip->read_word)
		chip->read_word = nand_read_word;
	if (!chip->block_bad)
		chip->block_bad = nand_block_bad;
	if (!chip->block_markbad)
		chip->block_markbad = nand_default_block_markbad;
	if (!chip->write_buf || chip->write_buf == nand_write_buf)
		chip->write_buf = busw ? nand_write_buf16 : nand_write_buf;
	if (!chip->write_byte || chip->write_byte == nand_write_byte)
		chip->write_byte = busw ? nand_write_byte16 : nand_write_byte;
	if (!chip->read_buf || chip->read_buf == nand_read_buf)
		chip->read_buf = busw ? nand_read_buf16 : nand_read_buf;
	if (!chip->scan_bbt)
		chip->scan_bbt = nand_default_bbt;

	if (!chip->controller) {
		chip->controller = &chip->hwcontrol;
		spin_lock_init(&chip->controller->lock);
		init_waitqueue_head(&chip->controller->wq);
	}

	if (!chip->buf_align)
		chip->buf_align = 1;
}

/* Sanitize ONFI strings so we can safely print them */
static void sanitize_string(char *s, size_t len)
{
	ssize_t i;

	/* Null terminate */
	s[len - 1] = 0;

	/* Remove non printable chars */
	for (i = 0; i < len - 1; i++) {
		if (s[i] < ' ' || s[i] > 127)
			s[i] = '?';
	}

	/* Remove trailing spaces */
	strim(s);
}

static u16 onfi_crc16(u16 crc, u8 const *p, size_t len)
{
	int i;
	while (len--) {
		crc ^= *p++ << 8;
		for (i = 0; i < 8; i++)
			crc = (crc << 1) ^ ((crc & 0x8000) ? 0x8005 : 0);
	}

	return crc;
}

#ifdef CONFIG_SYS_NAND_ONFI_DETECTION
/* Parse the Extended Parameter Page. */
static int nand_flash_detect_ext_param_page(struct mtd_info *mtd,
		struct nand_chip *chip, struct nand_onfi_params *p)
{
	struct onfi_ext_param_page *ep;
	struct onfi_ext_section *s;
	struct onfi_ext_ecc_info *ecc;
	uint8_t *cursor;
	int ret;
	int len;
	int i;

	len = le16_to_cpu(p->ext_param_page_length) * 16;
	ep = kmalloc(len, GFP_KERNEL);
	if (!ep)
		return -ENOMEM;

	/* Send our own NAND_CMD_PARAM. */
	ret = nand_read_param_page_op(chip, 0, NULL, 0);
	if (ret)
		goto ext_out;

	/* Use the Change Read Column command to skip the ONFI param pages. */
	ret = nand_change_read_column_op(chip,
					 sizeof(*p) * p->num_of_param_pages,
					 ep, len, true);
	if (ret)
		goto ext_out;

	ret = -EINVAL;
	if ((onfi_crc16(ONFI_CRC_BASE, ((uint8_t *)ep) + 2, len - 2)
		!= le16_to_cpu(ep->crc))) {
		pr_debug("fail in the CRC.\n");
		goto ext_out;
	}

	/*
	 * Check the signature.
	 * Do not strictly follow the ONFI spec, maybe changed in future.
	 */
	if (strncmp((char *)ep->sig, "EPPS", 4)) {
		pr_debug("The signature is invalid.\n");
		goto ext_out;
	}

	/* find the ECC section. */
	cursor = (uint8_t *)(ep + 1);
	for (i = 0; i < ONFI_EXT_SECTION_MAX; i++) {
		s = ep->sections + i;
		if (s->type == ONFI_SECTION_TYPE_2)
			break;
		cursor += s->length * 16;
	}
	if (i == ONFI_EXT_SECTION_MAX) {
		pr_debug("We can not find the ECC section.\n");
		goto ext_out;
	}

	/* get the info we want. */
	ecc = (struct onfi_ext_ecc_info *)cursor;

	if (!ecc->codeword_size) {
		pr_debug("Invalid codeword size\n");
		goto ext_out;
	}

	chip->ecc_strength_ds = ecc->ecc_bits;
	chip->ecc_step_ds = 1 << ecc->codeword_size;
	ret = 0;

ext_out:
	kfree(ep);
	return ret;
}

static int nand_setup_read_retry_micron(struct mtd_info *mtd, int retry_mode)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	uint8_t feature[ONFI_SUBFEATURE_PARAM_LEN] = {retry_mode};

	return chip->onfi_set_features(mtd, chip, ONFI_FEATURE_ADDR_READ_RETRY,
			feature);
}

/*
 * Configure chip properties from Micron vendor-specific ONFI table
 */
static void nand_onfi_detect_micron(struct nand_chip *chip,
		struct nand_onfi_params *p)
{
	struct nand_onfi_vendor_micron *micron = (void *)p->vendor;

	if (le16_to_cpu(p->vendor_revision) < 1)
		return;

	chip->read_retries = micron->read_retry_options;
	chip->setup_read_retry = nand_setup_read_retry_micron;
}

/*
 * Check if the NAND chip is ONFI compliant, returns 1 if it is, 0 otherwise.
 */
static int nand_flash_detect_onfi(struct mtd_info *mtd, struct nand_chip *chip,
					int *busw)
{
	struct nand_onfi_params *p = &chip->onfi_params;
	char id[4];
	int i, ret, val;

	/* Try ONFI for unknown chip or LP */
	ret = nand_readid_op(chip, 0x20, id, sizeof(id));
	if (ret || strncmp(id, "ONFI", 4))
		return 0;

	ret = nand_read_param_page_op(chip, 0, NULL, 0);
	if (ret)
		return 0;

	for (i = 0; i < 3; i++) {
		ret = nand_read_data_op(chip, p, sizeof(*p), true);
		if (ret)
			return 0;

		if (onfi_crc16(ONFI_CRC_BASE, (uint8_t *)p, 254) ==
				le16_to_cpu(p->crc)) {
			break;
		}
	}

	if (i == 3) {
		pr_err("Could not find valid ONFI parameter page; aborting\n");
		return 0;
	}

	/* Check version */
	val = le16_to_cpu(p->revision);
	if (val & (1 << 5))
		chip->onfi_version = 23;
	else if (val & (1 << 4))
		chip->onfi_version = 22;
	else if (val & (1 << 3))
		chip->onfi_version = 21;
	else if (val & (1 << 2))
		chip->onfi_version = 20;
	else if (val & (1 << 1))
		chip->onfi_version = 10;

	if (!chip->onfi_version) {
		pr_info("unsupported ONFI version: %d\n", val);
		return 0;
	}

	sanitize_string(p->manufacturer, sizeof(p->manufacturer));
	sanitize_string(p->model, sizeof(p->model));
	if (!mtd->name)
		mtd->name = p->model;

	mtd->writesize = le32_to_cpu(p->byte_per_page);

	/*
	 * pages_per_block and blocks_per_lun may not be a power-of-2 size
	 * (don't ask me who thought of this...). MTD assumes that these
	 * dimensions will be power-of-2, so just truncate the remaining area.
	 */
	mtd->erasesize = 1 << (fls(le32_to_cpu(p->pages_per_block)) - 1);
	mtd->erasesize *= mtd->writesize;

	mtd->oobsize = le16_to_cpu(p->spare_bytes_per_page);

	/* See erasesize comment */
	chip->chipsize = 1 << (fls(le32_to_cpu(p->blocks_per_lun)) - 1);
	chip->chipsize *= (uint64_t)mtd->erasesize * p->lun_count;
	chip->bits_per_cell = p->bits_per_cell;

	if (onfi_feature(chip) & ONFI_FEATURE_16_BIT_BUS)
		*busw = NAND_BUSWIDTH_16;
	else
		*busw = 0;

	if (p->ecc_bits != 0xff) {
		chip->ecc_strength_ds = p->ecc_bits;
		chip->ecc_step_ds = 512;
	} else if (chip->onfi_version >= 21 &&
		(onfi_feature(chip) & ONFI_FEATURE_EXT_PARAM_PAGE)) {

		/*
		 * The nand_flash_detect_ext_param_page() uses the
		 * Change Read Column command which maybe not supported
		 * by the chip->cmdfunc. So try to update the chip->cmdfunc
		 * now. We do not replace user supplied command function.
		 */
		if (mtd->writesize > 512 && chip->cmdfunc == nand_command)
			chip->cmdfunc = nand_command_lp;

		/* The Extended Parameter Page is supported since ONFI 2.1. */
		if (nand_flash_detect_ext_param_page(mtd, chip, p))
			pr_warn("Failed to detect ONFI extended param page\n");
	} else {
		pr_warn("Could not retrieve ONFI ECC requirements\n");
	}

	if (p->jedec_id == NAND_MFR_MICRON)
		nand_onfi_detect_micron(chip, p);

	return 1;
}
#else
static int nand_flash_detect_onfi(struct mtd_info *mtd, struct nand_chip *chip,
					int *busw)
{
	return 0;
}
#endif

/*
 * Check if the NAND chip is JEDEC compliant, returns 1 if it is, 0 otherwise.
 */
static int nand_flash_detect_jedec(struct mtd_info *mtd, struct nand_chip *chip,
					int *busw)
{
	struct nand_jedec_params *p = &chip->jedec_params;
	struct jedec_ecc_info *ecc;
	char id[5];
	int i, val, ret;

	/* Try JEDEC for unknown chip or LP */
	ret = nand_readid_op(chip, 0x40, id, sizeof(id));
	if (ret || strncmp(id, "JEDEC", sizeof(id)))
		return 0;

	ret = nand_read_param_page_op(chip, 0x40, NULL, 0);
	if (ret)
		return 0;

	for (i = 0; i < 3; i++) {
		ret = nand_read_data_op(chip, p, sizeof(*p), true);
		if (ret)
			return 0;

		if (onfi_crc16(ONFI_CRC_BASE, (uint8_t *)p, 510) ==
				le16_to_cpu(p->crc))
			break;
	}

	if (i == 3) {
		pr_err("Could not find valid JEDEC parameter page; aborting\n");
		return 0;
	}

	/* Check version */
	val = le16_to_cpu(p->revision);
	if (val & (1 << 2))
		chip->jedec_version = 10;
	else if (val & (1 << 1))
		chip->jedec_version = 1; /* vendor specific version */

	if (!chip->jedec_version) {
		pr_info("unsupported JEDEC version: %d\n", val);
		return 0;
	}

	sanitize_string(p->manufacturer, sizeof(p->manufacturer));
	sanitize_string(p->model, sizeof(p->model));
	if (!mtd->name)
		mtd->name = p->model;

	mtd->writesize = le32_to_cpu(p->byte_per_page);

	/* Please reference to the comment for nand_flash_detect_onfi. */
	mtd->erasesize = 1 << (fls(le32_to_cpu(p->pages_per_block)) - 1);
	mtd->erasesize *= mtd->writesize;

	mtd->oobsize = le16_to_cpu(p->spare_bytes_per_page);

	/* Please reference to the comment for nand_flash_detect_onfi. */
	chip->chipsize = 1 << (fls(le32_to_cpu(p->blocks_per_lun)) - 1);
	chip->chipsize *= (uint64_t)mtd->erasesize * p->lun_count;
	chip->bits_per_cell = p->bits_per_cell;

	if (jedec_feature(chip) & JEDEC_FEATURE_16_BIT_BUS)
		*busw = NAND_BUSWIDTH_16;
	else
		*busw = 0;

	/* ECC info */
	ecc = &p->ecc_info[0];

	if (ecc->codeword_size >= 9) {
		chip->ecc_strength_ds = ecc->ecc_bits;
		chip->ecc_step_ds = 1 << ecc->codeword_size;
	} else {
		pr_warn("Invalid codeword size\n");
	}

	return 1;
}

/*
 * nand_id_has_period - Check if an ID string has a given wraparound period
 * @id_data: the ID string
 * @arrlen: the length of the @id_data array
 * @period: the period of repitition
 *
 * Check if an ID string is repeated within a given sequence of bytes at
 * specific repetition interval period (e.g., {0x20,0x01,0x7F,0x20} has a
 * period of 3). This is a helper function for nand_id_len(). Returns non-zero
 * if the repetition has a period of @period; otherwise, returns zero.
 */
static int nand_id_has_period(u8 *id_data, int arrlen, int period)
{
	int i, j;
	for (i = 0; i < period; i++)
		for (j = i + period; j < arrlen; j += period)
			if (id_data[i] != id_data[j])
				return 0;
	return 1;
}

/*
 * nand_id_len - Get the length of an ID string returned by CMD_READID
 * @id_data: the ID string
 * @arrlen: the length of the @id_data array

 * Returns the length of the ID string, according to known wraparound/trailing
 * zero patterns. If no pattern exists, returns the length of the array.
 */
static int nand_id_len(u8 *id_data, int arrlen)
{
	int last_nonzero, period;

	/* Find last non-zero byte */
	for (last_nonzero = arrlen - 1; last_nonzero >= 0; last_nonzero--)
		if (id_data[last_nonzero])
			break;

	/* All zeros */
	if (last_nonzero < 0)
		return 0;

	/* Calculate wraparound period */
	for (period = 1; period < arrlen; period++)
		if (nand_id_has_period(id_data, arrlen, period))
			break;

	/* There's a repeated pattern */
	if (period < arrlen)
		return period;

	/* There are trailing zeros */
	if (last_nonzero < arrlen - 1)
		return last_nonzero + 1;

	/* No pattern detected */
	return arrlen;
}

/* Extract the bits of per cell from the 3rd byte of the extended ID */
static int nand_get_bits_per_cell(u8 cellinfo)
{
	int bits;

	bits = cellinfo & NAND_CI_CELLTYPE_MSK;
	bits >>= NAND_CI_CELLTYPE_SHIFT;
	return bits + 1;
}

/*
 * Many new NAND share similar device ID codes, which represent the size of the
 * chip. The rest of the parameters must be decoded according to generic or
 * manufacturer-specific "extended ID" decoding patterns.
 */
static void nand_decode_ext_id(struct mtd_info *mtd, struct nand_chip *chip,
				u8 id_data[8], int *busw)
{
	int extid, id_len;
	/* The 3rd id byte holds MLC / multichip data */
	chip->bits_per_cell = nand_get_bits_per_cell(id_data[2]);
	/* The 4th id byte is the important one */
	extid = id_data[3];

	id_len = nand_id_len(id_data, 8);

	/*
	 * Field definitions are in the following datasheets:
	 * Old style (4,5 byte ID): Samsung K9GAG08U0M (p.32)
	 * New Samsung (6 byte ID): Samsung K9GAG08U0F (p.44)
	 * Hynix MLC   (6 byte ID): Hynix H27UBG8T2B (p.22)
	 *
	 * Check for ID length, non-zero 6th byte, cell type, and Hynix/Samsung
	 * ID to decide what to do.
	 */
	if (id_len == 6 && id_data[0] == NAND_MFR_SAMSUNG &&
			!nand_is_slc(chip) && id_data[5] != 0x00) {
		/* Calc pagesize */
		mtd->writesize = 2048 << (extid & 0x03);
		extid >>= 2;
		/* Calc oobsize */
		switch (((extid >> 2) & 0x04) | (extid & 0x03)) {
		case 1:
			mtd->oobsize = 128;
			break;
		case 2:
			mtd->oobsize = 218;
			break;
		case 3:
			mtd->oobsize = 400;
			break;
		case 4:
			mtd->oobsize = 436;
			break;
		case 5:
			mtd->oobsize = 512;
			break;
		case 6:
			mtd->oobsize = 640;
			break;
		case 7:
		default: /* Other cases are "reserved" (unknown) */
			mtd->oobsize = 1024;
			break;
		}
		extid >>= 2;
		/* Calc blocksize */
		mtd->erasesize = (128 * 1024) <<
			(((extid >> 1) & 0x04) | (extid & 0x03));
		*busw = 0;
	} else if (id_len == 6 && id_data[0] == NAND_MFR_HYNIX &&
			!nand_is_slc(chip)) {
		unsigned int tmp;

		/* Calc pagesize */
		mtd->writesize = 2048 << (extid & 0x03);
		extid >>= 2;
		/* Calc oobsize */
		switch (((extid >> 2) & 0x04) | (extid & 0x03)) {
		case 0:
			mtd->oobsize = 128;
			break;
		case 1:
			mtd->oobsize = 224;
			break;
		case 2:
			mtd->oobsize = 448;
			break;
		case 3:
			mtd->oobsize = 64;
			break;
		case 4:
			mtd->oobsize = 32;
			break;
		case 5:
			mtd->oobsize = 16;
			break;
		default:
			mtd->oobsize = 640;
			break;
		}
		extid >>= 2;
		/* Calc blocksize */
		tmp = ((extid >> 1) & 0x04) | (extid & 0x03);
		if (tmp < 0x03)
			mtd->erasesize = (128 * 1024) << tmp;
		else if (tmp == 0x03)
			mtd->erasesize = 768 * 1024;
		else
			mtd->erasesize = (64 * 1024) << tmp;
		*busw = 0;
	} else {
		/* Calc pagesize */
		mtd->writesize = 1024 << (extid & 0x03);
		extid >>= 2;
		/* Calc oobsize */
		mtd->oobsize = (8 << (extid & 0x01)) *
			(mtd->writesize >> 9);
		extid >>= 2;
		/* Calc blocksize. Blocksize is multiples of 64KiB */
		mtd->erasesize = (64 * 1024) << (extid & 0x03);
		extid >>= 2;
		/* Get buswidth information */
		*busw = (extid & 0x01) ? NAND_BUSWIDTH_16 : 0;

		/*
		 * Toshiba 24nm raw SLC (i.e., not BENAND) have 32B OOB per
		 * 512B page. For Toshiba SLC, we decode the 5th/6th byte as
		 * follows:
		 * - ID byte 6, bits[2:0]: 100b -> 43nm, 101b -> 32nm,
		 *                         110b -> 24nm
		 * - ID byte 5, bit[7]:    1 -> BENAND, 0 -> raw SLC
		 */
		if (id_len >= 6 && id_data[0] == NAND_MFR_TOSHIBA &&
				nand_is_slc(chip) &&
				(id_data[5] & 0x7) == 0x6 /* 24nm */ &&
				!(id_data[4] & 0x80) /* !BENAND */) {
			mtd->oobsize = 32 * mtd->writesize >> 9;
		}

	}
}

/*
 * Old devices have chip data hardcoded in the device ID table. nand_decode_id
 * decodes a matching ID table entry and assigns the MTD size parameters for
 * the chip.
 */
static void nand_decode_id(struct mtd_info *mtd, struct nand_chip *chip,
				struct nand_flash_dev *type, u8 id_data[8],
				int *busw)
{
	int maf_id = id_data[0];

	mtd->erasesize = type->erasesize;
	mtd->writesize = type->pagesize;
	mtd->oobsize = mtd->writesize / 32;
	*busw = type->options & NAND_BUSWIDTH_16;

	/* All legacy ID NAND are small-page, SLC */
	chip->bits_per_cell = 1;

	/*
	 * Check for Spansion/AMD ID + repeating 5th, 6th byte since
	 * some Spansion chips have erasesize that conflicts with size
	 * listed in nand_ids table.
	 * Data sheet (5 byte ID): Spansion S30ML-P ORNAND (p.39)
	 */
	if (maf_id == NAND_MFR_AMD && id_data[4] != 0x00 && id_data[5] == 0x00
			&& id_data[6] == 0x00 && id_data[7] == 0x00
			&& mtd->writesize == 512) {
		mtd->erasesize = 128 * 1024;
		mtd->erasesize <<= ((id_data[3] & 0x03) << 1);
	}
}

/*
 * Set the bad block marker/indicator (BBM/BBI) patterns according to some
 * heuristic patterns using various detected parameters (e.g., manufacturer,
 * page size, cell-type information).
 */
static void nand_decode_bbm_options(struct mtd_info *mtd,
				    struct nand_chip *chip, u8 id_data[8])
{
	int maf_id = id_data[0];

	/* Set the bad block position */
	if (mtd->writesize > 512 || (chip->options & NAND_BUSWIDTH_16))
		chip->badblockpos = NAND_LARGE_BADBLOCK_POS;
	else
		chip->badblockpos = NAND_SMALL_BADBLOCK_POS;

	/*
	 * Bad block marker is stored in the last page of each block on Samsung
	 * and Hynix MLC devices; stored in first two pages of each block on
	 * Micron devices with 2KiB pages and on SLC Samsung, Hynix, Toshiba,
	 * AMD/Spansion, and Macronix.  All others scan only the first page.
	 */
	if (!nand_is_slc(chip) &&
			(maf_id == NAND_MFR_SAMSUNG ||
			 maf_id == NAND_MFR_HYNIX))
		chip->bbt_options |= NAND_BBT_SCANLASTPAGE;
	else if ((nand_is_slc(chip) &&
				(maf_id == NAND_MFR_SAMSUNG ||
				 maf_id == NAND_MFR_HYNIX ||
				 maf_id == NAND_MFR_TOSHIBA ||
				 maf_id == NAND_MFR_AMD ||
				 maf_id == NAND_MFR_MACRONIX)) ||
			(mtd->writesize == 2048 &&
			 maf_id == NAND_MFR_MICRON))
		chip->bbt_options |= NAND_BBT_SCAN2NDPAGE;
}

static inline bool is_full_id_nand(struct nand_flash_dev *type)
{
	return type->id_len;
}

static bool find_full_id_nand(struct mtd_info *mtd, struct nand_chip *chip,
		   struct nand_flash_dev *type, u8 *id_data, int *busw)
{
	if (!strncmp((char *)type->id, (char *)id_data, type->id_len)) {
		mtd->writesize = type->pagesize;
		mtd->erasesize = type->erasesize;
		mtd->oobsize = type->oobsize;

		chip->bits_per_cell = nand_get_bits_per_cell(id_data[2]);
		chip->chipsize = (uint64_t)type->chipsize << 20;
		chip->options |= type->options;
		chip->ecc_strength_ds = NAND_ECC_STRENGTH(type);
		chip->ecc_step_ds = NAND_ECC_STEP(type);
		chip->onfi_timing_mode_default =
					type->onfi_timing_mode_default;

		*busw = type->options & NAND_BUSWIDTH_16;

		if (!mtd->name)
			mtd->name = type->name;

		return true;
	}
	return false;
}

/*
 * Get the flash and manufacturer id and lookup if the type is supported.
 */
struct nand_flash_dev *nand_get_flash_type(struct mtd_info *mtd,
						  struct nand_chip *chip,
						  int *maf_id, int *dev_id,
						  struct nand_flash_dev *type)
{
	int busw, ret;
	int maf_idx;
	u8 id_data[8];

	/*
	 * Reset the chip, required by some chips (e.g. Micron MT29FxGxxxxx)
	 * after power-up.
	 */
	ret = nand_reset(chip, 0);
	if (ret)
		return ERR_PTR(ret);

	/* Select the device */
	chip->select_chip(mtd, 0);

	/* Send the command for reading device ID */
	ret = nand_readid_op(chip, 0, id_data, 2);
	if (ret)
		return ERR_PTR(ret);

	/* Read manufacturer and device IDs */
	*maf_id = id_data[0];
	*dev_id = id_data[1];

	/*
	 * Try again to make sure, as some systems the bus-hold or other
	 * interface concerns can cause random data which looks like a
	 * possibly credible NAND flash to appear. If the two results do
	 * not match, ignore the device completely.
	 */

	/* Read entire ID string */
	ret = nand_readid_op(chip, 0, id_data, 8);
	if (ret)
		return ERR_PTR(ret);

	if (id_data[0] != *maf_id || id_data[1] != *dev_id) {
		pr_info("second ID read did not match %02x,%02x against %02x,%02x\n",
			*maf_id, *dev_id, id_data[0], id_data[1]);
		return ERR_PTR(-ENODEV);
	}

	if (!type)
		type = nand_flash_ids;

	for (; type->name != NULL; type++) {
		if (is_full_id_nand(type)) {
			if (find_full_id_nand(mtd, chip, type, id_data, &busw))
				goto ident_done;
		} else if (*dev_id == type->dev_id) {
			break;
		}
	}

	chip->onfi_version = 0;
	if (!type->name || !type->pagesize) {
		/* Check if the chip is ONFI compliant */
		if (nand_flash_detect_onfi(mtd, chip, &busw))
			goto ident_done;

		/* Check if the chip is JEDEC compliant */
		if (nand_flash_detect_jedec(mtd, chip, &busw))
			goto ident_done;
	}

	if (!type->name)
		return ERR_PTR(-ENODEV);

	if (!mtd->name)
		mtd->name = type->name;

	chip->chipsize = (uint64_t)type->chipsize << 20;

	if (!type->pagesize) {
		/* Decode parameters from extended ID */
		nand_decode_ext_id(mtd, chip, id_data, &busw);
	} else {
		nand_decode_id(mtd, chip, type, id_data, &busw);
	}
	/* Get chip options */
	chip->options |= type->options;

	/*
	 * Check if chip is not a Samsung device. Do not clear the
	 * options for chips which do not have an extended id.
	 */
	if (*maf_id != NAND_MFR_SAMSUNG && !type->pagesize)
		chip->options &= ~NAND_SAMSUNG_LP_OPTIONS;
ident_done:

	/* Try to identify manufacturer */
	for (maf_idx = 0; nand_manuf_ids[maf_idx].id != 0x0; maf_idx++) {
		if (nand_manuf_ids[maf_idx].id == *maf_id)
			break;
	}

	if (chip->options & NAND_BUSWIDTH_AUTO) {
		WARN_ON(chip->options & NAND_BUSWIDTH_16);
		chip->options |= busw;
		nand_set_defaults(chip, busw);
	} else if (busw != (chip->options & NAND_BUSWIDTH_16)) {
		/*
		 * Check, if buswidth is correct. Hardware drivers should set
		 * chip correct!
		 */
		pr_info("device found, Manufacturer ID: 0x%02x, Chip ID: 0x%02x\n",
			*maf_id, *dev_id);
		pr_info("%s %s\n", nand_manuf_ids[maf_idx].name, mtd->name);
		pr_warn("bus width %d instead %d bit\n",
			   (chip->options & NAND_BUSWIDTH_16) ? 16 : 8,
			   busw ? 16 : 8);
		return ERR_PTR(-EINVAL);
	}

	nand_decode_bbm_options(mtd, chip, id_data);

	/* Calculate the address shift from the page size */
	chip->page_shift = ffs(mtd->writesize) - 1;
	/* Convert chipsize to number of pages per chip -1 */
	chip->pagemask = (chip->chipsize >> chip->page_shift) - 1;

	chip->bbt_erase_shift = chip->phys_erase_shift =
		ffs(mtd->erasesize) - 1;
	if (chip->chipsize & 0xffffffff)
		chip->chip_shift = ffs((unsigned)chip->chipsize) - 1;
	else {
		chip->chip_shift = ffs((unsigned)(chip->chipsize >> 32));
		chip->chip_shift += 32 - 1;
	}

	if (chip->chip_shift - chip->page_shift > 16)
		chip->options |= NAND_ROW_ADDR_3;

	chip->badblockbits = 8;
	chip->erase = single_erase;

	/* Do not replace user supplied command function! */
	if (mtd->writesize > 512 && chip->cmdfunc == nand_command)
		chip->cmdfunc = nand_command_lp;

	pr_info("device found, Manufacturer ID: 0x%02x, Chip ID: 0x%02x\n",
		*maf_id, *dev_id);

#ifdef CONFIG_SYS_NAND_ONFI_DETECTION
	if (chip->onfi_version)
		pr_info("%s %s\n", nand_manuf_ids[maf_idx].name,
				chip->onfi_params.model);
	else if (chip->jedec_version)
		pr_info("%s %s\n", nand_manuf_ids[maf_idx].name,
				chip->jedec_params.model);
	else
		pr_info("%s %s\n", nand_manuf_ids[maf_idx].name,
				type->name);
#else
	if (chip->jedec_version)
		pr_info("%s %s\n", nand_manuf_ids[maf_idx].name,
				chip->jedec_params.model);
	else
		pr_info("%s %s\n", nand_manuf_ids[maf_idx].name,
				type->name);

	pr_info("%s %s\n", nand_manuf_ids[maf_idx].name,
		type->name);
#endif

	pr_info("%d MiB, %s, erase size: %d KiB, page size: %d, OOB size: %d\n",
		(int)(chip->chipsize >> 20), nand_is_slc(chip) ? "SLC" : "MLC",
		mtd->erasesize >> 10, mtd->writesize, mtd->oobsize);
	return type;
}
EXPORT_SYMBOL(nand_get_flash_type);

#if CONFIG_IS_ENABLED(OF_CONTROL)
DECLARE_GLOBAL_DATA_PTR;

static int nand_dt_init(struct mtd_info *mtd, struct nand_chip *chip, int node)
{
	int ret, ecc_mode = -1, ecc_strength, ecc_step;
	const void *blob = gd->fdt_blob;
	const char *str;

	ret = fdtdec_get_int(blob, node, "nand-bus-width", -1);
	if (ret == 16)
		chip->options |= NAND_BUSWIDTH_16;

	if (fdtdec_get_bool(blob, node, "nand-on-flash-bbt"))
		chip->bbt_options |= NAND_BBT_USE_FLASH;

	str = fdt_getprop(blob, node, "nand-ecc-mode", NULL);
	if (str) {
		if (!strcmp(str, "none"))
			ecc_mode = NAND_ECC_NONE;
		else if (!strcmp(str, "soft"))
			ecc_mode = NAND_ECC_SOFT;
		else if (!strcmp(str, "hw"))
			ecc_mode = NAND_ECC_HW;
		else if (!strcmp(str, "hw_syndrome"))
			ecc_mode = NAND_ECC_HW_SYNDROME;
		else if (!strcmp(str, "hw_oob_first"))
			ecc_mode = NAND_ECC_HW_OOB_FIRST;
		else if (!strcmp(str, "soft_bch"))
			ecc_mode = NAND_ECC_SOFT_BCH;
	}


	ecc_strength = fdtdec_get_int(blob, node, "nand-ecc-strength", -1);
	ecc_step = fdtdec_get_int(blob, node, "nand-ecc-step-size", -1);

	if ((ecc_step >= 0 && !(ecc_strength >= 0)) ||
	    (!(ecc_step >= 0) && ecc_strength >= 0)) {
		pr_err("must set both strength and step size in DT\n");
		return -EINVAL;
	}

	if (ecc_mode >= 0)
		chip->ecc.mode = ecc_mode;

	if (ecc_strength >= 0)
		chip->ecc.strength = ecc_strength;

	if (ecc_step > 0)
		chip->ecc.size = ecc_step;

	if (fdt_getprop(blob, node, "nand-ecc-maximize", NULL))
		chip->ecc.options |= NAND_ECC_MAXIMIZE;

	return 0;
}
#else
static int nand_dt_init(struct mtd_info *mtd, struct nand_chip *chip, int node)
{
	return 0;
}
#endif /* CONFIG_IS_ENABLED(OF_CONTROL) */

/**
 * nand_scan_ident - [NAND Interface] Scan for the NAND device
 * @mtd: MTD device structure
 * @maxchips: number of chips to scan for
 * @table: alternative NAND ID table
 *
 * This is the first phase of the normal nand_scan() function. It reads the
 * flash ID and sets up MTD fields accordingly.
 *
 */
int nand_scan_ident(struct mtd_info *mtd, int maxchips,
		    struct nand_flash_dev *table)
{
	int i, nand_maf_id, nand_dev_id;
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct nand_flash_dev *type;
	int ret;

	if (chip->flash_node) {
		ret = nand_dt_init(mtd, chip, chip->flash_node);
		if (ret)
			return ret;
	}

	/* Set the default functions */
	nand_set_defaults(chip, chip->options & NAND_BUSWIDTH_16);

	/* Read the flash type */
	type = nand_get_flash_type(mtd, chip, &nand_maf_id,
				   &nand_dev_id, table);

	if (IS_ERR(type)) {
		if (!(chip->options & NAND_SCAN_SILENT_NODEV))
			pr_warn("No NAND device found\n");
		chip->select_chip(mtd, -1);
		return PTR_ERR(type);
	}

	/* Initialize the ->data_interface field. */
	ret = nand_init_data_interface(chip);
	if (ret)
		return ret;

	/*
	 * Setup the data interface correctly on the chip and controller side.
	 * This explicit call to nand_setup_data_interface() is only required
	 * for the first die, because nand_reset() has been called before
	 * ->data_interface and ->default_onfi_timing_mode were set.
	 * For the other dies, nand_reset() will automatically switch to the
	 * best mode for us.
	 */
	ret = nand_setup_data_interface(chip, 0);
	if (ret)
		return ret;

	chip->select_chip(mtd, -1);

	/* Check for a chip array */
	for (i = 1; i < maxchips; i++) {
		u8 id[2];

		/* See comment in nand_get_flash_type for reset */
		nand_reset(chip, i);

		chip->select_chip(mtd, i);
		/* Send the command for reading device ID */
		nand_readid_op(chip, 0, id, sizeof(id));

		/* Read manufacturer and device IDs */
		if (nand_maf_id != id[0] || nand_dev_id != id[1]) {
			chip->select_chip(mtd, -1);
			break;
		}
		chip->select_chip(mtd, -1);
	}

#ifdef DEBUG
	if (i > 1)
		pr_info("%d chips detected\n", i);
#endif

	/* Store the number of chips and calc total size for mtd */
	chip->numchips = i;
	mtd->size = i * chip->chipsize;

	return 0;
}
EXPORT_SYMBOL(nand_scan_ident);

/**
 * nand_check_ecc_caps - check the sanity of preset ECC settings
 * @chip: nand chip info structure
 * @caps: ECC caps info structure
 * @oobavail: OOB size that the ECC engine can use
 *
 * When ECC step size and strength are already set, check if they are supported
 * by the controller and the calculated ECC bytes fit within the chip's OOB.
 * On success, the calculated ECC bytes is set.
 */
int nand_check_ecc_caps(struct nand_chip *chip,
			const struct nand_ecc_caps *caps, int oobavail)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	const struct nand_ecc_step_info *stepinfo;
	int preset_step = chip->ecc.size;
	int preset_strength = chip->ecc.strength;
	int nsteps, ecc_bytes;
	int i, j;

	if (WARN_ON(oobavail < 0))
		return -EINVAL;

	if (!preset_step || !preset_strength)
		return -ENODATA;

	nsteps = mtd->writesize / preset_step;

	for (i = 0; i < caps->nstepinfos; i++) {
		stepinfo = &caps->stepinfos[i];

		if (stepinfo->stepsize != preset_step)
			continue;

		for (j = 0; j < stepinfo->nstrengths; j++) {
			if (stepinfo->strengths[j] != preset_strength)
				continue;

			ecc_bytes = caps->calc_ecc_bytes(preset_step,
							 preset_strength);
			if (WARN_ON_ONCE(ecc_bytes < 0))
				return ecc_bytes;

			if (ecc_bytes * nsteps > oobavail) {
				pr_err("ECC (step, strength) = (%d, %d) does not fit in OOB",
				       preset_step, preset_strength);
				return -ENOSPC;
			}

			chip->ecc.bytes = ecc_bytes;

			return 0;
		}
	}

	pr_err("ECC (step, strength) = (%d, %d) not supported on this controller",
	       preset_step, preset_strength);

	return -ENOTSUPP;
}
EXPORT_SYMBOL_GPL(nand_check_ecc_caps);

/**
 * nand_match_ecc_req - meet the chip's requirement with least ECC bytes
 * @chip: nand chip info structure
 * @caps: ECC engine caps info structure
 * @oobavail: OOB size that the ECC engine can use
 *
 * If a chip's ECC requirement is provided, try to meet it with the least
 * number of ECC bytes (i.e. with the largest number of OOB-free bytes).
 * On success, the chosen ECC settings are set.
 */
int nand_match_ecc_req(struct nand_chip *chip,
		       const struct nand_ecc_caps *caps, int oobavail)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	const struct nand_ecc_step_info *stepinfo;
	int req_step = chip->ecc_step_ds;
	int req_strength = chip->ecc_strength_ds;
	int req_corr, step_size, strength, nsteps, ecc_bytes, ecc_bytes_total;
	int best_step, best_strength, best_ecc_bytes;
	int best_ecc_bytes_total = INT_MAX;
	int i, j;

	if (WARN_ON(oobavail < 0))
		return -EINVAL;

	/* No information provided by the NAND chip */
	if (!req_step || !req_strength)
		return -ENOTSUPP;

	/* number of correctable bits the chip requires in a page */
	req_corr = mtd->writesize / req_step * req_strength;

	for (i = 0; i < caps->nstepinfos; i++) {
		stepinfo = &caps->stepinfos[i];
		step_size = stepinfo->stepsize;

		for (j = 0; j < stepinfo->nstrengths; j++) {
			strength = stepinfo->strengths[j];

			/*
			 * If both step size and strength are smaller than the
			 * chip's requirement, it is not easy to compare the
			 * resulted reliability.
			 */
			if (step_size < req_step && strength < req_strength)
				continue;

			if (mtd->writesize % step_size)
				continue;

			nsteps = mtd->writesize / step_size;

			ecc_bytes = caps->calc_ecc_bytes(step_size, strength);
			if (WARN_ON_ONCE(ecc_bytes < 0))
				continue;
			ecc_bytes_total = ecc_bytes * nsteps;

			if (ecc_bytes_total > oobavail ||
			    strength * nsteps < req_corr)
				continue;

			/*
			 * We assume the best is to meet the chip's requrement
			 * with the least number of ECC bytes.
			 */
			if (ecc_bytes_total < best_ecc_bytes_total) {
				best_ecc_bytes_total = ecc_bytes_total;
				best_step = step_size;
				best_strength = strength;
				best_ecc_bytes = ecc_bytes;
			}
		}
	}

	if (best_ecc_bytes_total == INT_MAX)
		return -ENOTSUPP;

	chip->ecc.size = best_step;
	chip->ecc.strength = best_strength;
	chip->ecc.bytes = best_ecc_bytes;

	return 0;
}
EXPORT_SYMBOL_GPL(nand_match_ecc_req);

/**
 * nand_maximize_ecc - choose the max ECC strength available
 * @chip: nand chip info structure
 * @caps: ECC engine caps info structure
 * @oobavail: OOB size that the ECC engine can use
 *
 * Choose the max ECC strength that is supported on the controller, and can fit
 * within the chip's OOB.  On success, the chosen ECC settings are set.
 */
int nand_maximize_ecc(struct nand_chip *chip,
		      const struct nand_ecc_caps *caps, int oobavail)
{
	struct mtd_info *mtd = nand_to_mtd(chip);
	const struct nand_ecc_step_info *stepinfo;
	int step_size, strength, nsteps, ecc_bytes, corr;
	int best_corr = 0;
	int best_step = 0;
	int best_strength, best_ecc_bytes;
	int i, j;

	if (WARN_ON(oobavail < 0))
		return -EINVAL;

	for (i = 0; i < caps->nstepinfos; i++) {
		stepinfo = &caps->stepinfos[i];
		step_size = stepinfo->stepsize;

		/* If chip->ecc.size is already set, respect it */
		if (chip->ecc.size && step_size != chip->ecc.size)
			continue;

		for (j = 0; j < stepinfo->nstrengths; j++) {
			strength = stepinfo->strengths[j];

			if (mtd->writesize % step_size)
				continue;

			nsteps = mtd->writesize / step_size;

			ecc_bytes = caps->calc_ecc_bytes(step_size, strength);
			if (WARN_ON_ONCE(ecc_bytes < 0))
				continue;

			if (ecc_bytes * nsteps > oobavail)
				continue;

			corr = strength * nsteps;

			/*
			 * If the number of correctable bits is the same,
			 * bigger step_size has more reliability.
			 */
			if (corr > best_corr ||
			    (corr == best_corr && step_size > best_step)) {
				best_corr = corr;
				best_step = step_size;
				best_strength = strength;
				best_ecc_bytes = ecc_bytes;
			}
		}
	}

	if (!best_corr)
		return -ENOTSUPP;

	chip->ecc.size = best_step;
	chip->ecc.strength = best_strength;
	chip->ecc.bytes = best_ecc_bytes;

	return 0;
}
EXPORT_SYMBOL_GPL(nand_maximize_ecc);

/*
 * Check if the chip configuration meet the datasheet requirements.

 * If our configuration corrects A bits per B bytes and the minimum
 * required correction level is X bits per Y bytes, then we must ensure
 * both of the following are true:
 *
 * (1) A / B >= X / Y
 * (2) A >= X
 *
 * Requirement (1) ensures we can correct for the required bitflip density.
 * Requirement (2) ensures we can correct even when all bitflips are clumped
 * in the same sector.
 */
static bool nand_ecc_strength_good(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct nand_ecc_ctrl *ecc = &chip->ecc;
	int corr, ds_corr;

	if (ecc->size == 0 || chip->ecc_step_ds == 0)
		/* Not enough information */
		return true;

	/*
	 * We get the number of corrected bits per page to compare
	 * the correction density.
	 */
	corr = (mtd->writesize * ecc->strength) / ecc->size;
	ds_corr = (mtd->writesize * chip->ecc_strength_ds) / chip->ecc_step_ds;

	return corr >= ds_corr && ecc->strength >= chip->ecc_strength_ds;
}

static bool invalid_ecc_page_accessors(struct nand_chip *chip)
{
	struct nand_ecc_ctrl *ecc = &chip->ecc;

	if (nand_standard_page_accessors(ecc))
		return false;

	/*
	 * NAND_ECC_CUSTOM_PAGE_ACCESS flag is set, make sure the NAND
	 * controller driver implements all the page accessors because
	 * default helpers are not suitable when the core does not
	 * send the READ0/PAGEPROG commands.
	 */
	return (!ecc->read_page || !ecc->write_page ||
		!ecc->read_page_raw || !ecc->write_page_raw ||
		(NAND_HAS_SUBPAGE_READ(chip) && !ecc->read_subpage) ||
		(NAND_HAS_SUBPAGE_WRITE(chip) && !ecc->write_subpage &&
		 ecc->hwctl && ecc->calculate));
}

/**
 * nand_scan_tail - [NAND Interface] Scan for the NAND device
 * @mtd: MTD device structure
 *
 * This is the second phase of the normal nand_scan() function. It fills out
 * all the uninitialized function pointers with the defaults and scans for a
 * bad block table if appropriate.
 */
int nand_scan_tail(struct mtd_info *mtd)
{
	int i;
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct nand_ecc_ctrl *ecc = &chip->ecc;
	struct nand_buffers *nbuf;

	/* New bad blocks should be marked in OOB, flash-based BBT, or both */
	BUG_ON((chip->bbt_options & NAND_BBT_NO_OOB_BBM) &&
			!(chip->bbt_options & NAND_BBT_USE_FLASH));

	if (invalid_ecc_page_accessors(chip)) {
		pr_err("Invalid ECC page accessors setup\n");
		return -EINVAL;
	}

	if (!(chip->options & NAND_OWN_BUFFERS)) {
		nbuf = kzalloc(sizeof(struct nand_buffers), GFP_KERNEL);
		chip->buffers = nbuf;
	} else {
		if (!chip->buffers)
			return -ENOMEM;
	}

	/* Set the internal oob buffer location, just after the page data */
	chip->oob_poi = chip->buffers->databuf + mtd->writesize;

	/*
	 * If no default placement scheme is given, select an appropriate one.
	 */
	if (!ecc->layout && (ecc->mode != NAND_ECC_SOFT_BCH)) {
		switch (mtd->oobsize) {
#ifndef CONFIG_SYS_NAND_DRIVER_ECC_LAYOUT
		case 8:
			ecc->layout = &nand_oob_8;
			break;
		case 16:
			ecc->layout = &nand_oob_16;
			break;
		case 64:
			ecc->layout = &nand_oob_64;
			break;
		case 128:
			ecc->layout = &nand_oob_128;
			break;
#endif
		default:
			pr_warn("No oob scheme defined for oobsize %d\n",
				   mtd->oobsize);
			BUG();
		}
	}

	if (!chip->write_page)
		chip->write_page = nand_write_page;

	/*
	 * Check ECC mode, default to software if 3byte/512byte hardware ECC is
	 * selected and we have 256 byte pagesize fallback to software ECC
	 */

	switch (ecc->mode) {
	case NAND_ECC_HW_OOB_FIRST:
		/* Similar to NAND_ECC_HW, but a separate read_page handle */
		if (!ecc->calculate || !ecc->correct || !ecc->hwctl) {
			pr_warn("No ECC functions supplied; hardware ECC not possible\n");
			BUG();
		}
		if (!ecc->read_page)
			ecc->read_page = nand_read_page_hwecc_oob_first;

	case NAND_ECC_HW:
		/* Use standard hwecc read page function? */
		if (!ecc->read_page)
			ecc->read_page = nand_read_page_hwecc;
		if (!ecc->write_page)
			ecc->write_page = nand_write_page_hwecc;
		if (!ecc->read_page_raw)
			ecc->read_page_raw = nand_read_page_raw;
		if (!ecc->write_page_raw)
			ecc->write_page_raw = nand_write_page_raw;
		if (!ecc->read_oob)
			ecc->read_oob = nand_read_oob_std;
		if (!ecc->write_oob)
			ecc->write_oob = nand_write_oob_std;
		if (!ecc->read_subpage)
			ecc->read_subpage = nand_read_subpage;
		if (!ecc->write_subpage && ecc->hwctl && ecc->calculate)
			ecc->write_subpage = nand_write_subpage_hwecc;

	case NAND_ECC_HW_SYNDROME:
		if ((!ecc->calculate || !ecc->correct || !ecc->hwctl) &&
		    (!ecc->read_page ||
		     ecc->read_page == nand_read_page_hwecc ||
		     !ecc->write_page ||
		     ecc->write_page == nand_write_page_hwecc)) {
			pr_warn("No ECC functions supplied; hardware ECC not possible\n");
			BUG();
		}
		/* Use standard syndrome read/write page function? */
		if (!ecc->read_page)
			ecc->read_page = nand_read_page_syndrome;
		if (!ecc->write_page)
			ecc->write_page = nand_write_page_syndrome;
		if (!ecc->read_page_raw)
			ecc->read_page_raw = nand_read_page_raw_syndrome;
		if (!ecc->write_page_raw)
			ecc->write_page_raw = nand_write_page_raw_syndrome;
		if (!ecc->read_oob)
			ecc->read_oob = nand_read_oob_syndrome;
		if (!ecc->write_oob)
			ecc->write_oob = nand_write_oob_syndrome;

		if (mtd->writesize >= ecc->size) {
			if (!ecc->strength) {
				pr_warn("Driver must set ecc.strength when using hardware ECC\n");
				BUG();
			}
			break;
		}
		pr_warn("%d byte HW ECC not possible on %d byte page size, fallback to SW ECC\n",
			ecc->size, mtd->writesize);
		ecc->mode = NAND_ECC_SOFT;

	case NAND_ECC_SOFT:
		ecc->calculate = nand_calculate_ecc;
		ecc->correct = nand_correct_data;
		ecc->read_page = nand_read_page_swecc;
		ecc->read_subpage = nand_read_subpage;
		ecc->write_page = nand_write_page_swecc;
		ecc->read_page_raw = nand_read_page_raw;
		ecc->write_page_raw = nand_write_page_raw;
		ecc->read_oob = nand_read_oob_std;
		ecc->write_oob = nand_write_oob_std;
		if (!ecc->size)
			ecc->size = 256;
		ecc->bytes = 3;
		ecc->strength = 1;
		break;

	case NAND_ECC_SOFT_BCH:
		if (!mtd_nand_has_bch()) {
			pr_warn("CONFIG_MTD_NAND_ECC_BCH not enabled\n");
			BUG();
		}
		ecc->calculate = nand_bch_calculate_ecc;
		ecc->correct = nand_bch_correct_data;
		ecc->read_page = nand_read_page_swecc;
		ecc->read_subpage = nand_read_subpage;
		ecc->write_page = nand_write_page_swecc;
		ecc->read_page_raw = nand_read_page_raw;
		ecc->write_page_raw = nand_write_page_raw;
		ecc->read_oob = nand_read_oob_std;
		ecc->write_oob = nand_write_oob_std;
		/*
		 * Board driver should supply ecc.size and ecc.strength values
		 * to select how many bits are correctable. Otherwise, default
		 * to 4 bits for large page devices.
		 */
		if (!ecc->size && (mtd->oobsize >= 64)) {
			ecc->size = 512;
			ecc->strength = 4;
		}

		/* See nand_bch_init() for details. */
		ecc->bytes = 0;
		ecc->priv = nand_bch_init(mtd);
		if (!ecc->priv) {
			pr_warn("BCH ECC initialization failed!\n");
			BUG();
		}
		break;

	case NAND_ECC_NONE:
		pr_warn("NAND_ECC_NONE selected by board driver. This is not recommended!\n");
		ecc->read_page = nand_read_page_raw;
		ecc->write_page = nand_write_page_raw;
		ecc->read_oob = nand_read_oob_std;
		ecc->read_page_raw = nand_read_page_raw;
		ecc->write_page_raw = nand_write_page_raw;
		ecc->write_oob = nand_write_oob_std;
		ecc->size = mtd->writesize;
		ecc->bytes = 0;
		ecc->strength = 0;
		break;

	default:
		pr_warn("Invalid NAND_ECC_MODE %d\n", ecc->mode);
		BUG();
	}

	/* For many systems, the standard OOB write also works for raw */
	if (!ecc->read_oob_raw)
		ecc->read_oob_raw = ecc->read_oob;
	if (!ecc->write_oob_raw)
		ecc->write_oob_raw = ecc->write_oob;

	/*
	 * The number of bytes available for a client to place data into
	 * the out of band area.
	 */
	mtd->oobavail = 0;
	if (ecc->layout) {
		for (i = 0; ecc->layout->oobfree[i].length; i++)
			mtd->oobavail += ecc->layout->oobfree[i].length;
	}

	/* ECC sanity check: warn if it's too weak */
	if (!nand_ecc_strength_good(mtd))
		pr_warn("WARNING: %s: the ECC used on your system is too weak compared to the one required by the NAND chip\n",
			mtd->name);

	/*
	 * Set the number of read / write steps for one page depending on ECC
	 * mode.
	 */
	ecc->steps = mtd->writesize / ecc->size;
	if (ecc->steps * ecc->size != mtd->writesize) {
		pr_warn("Invalid ECC parameters\n");
		BUG();
	}
	ecc->total = ecc->steps * ecc->bytes;

	/* Allow subpage writes up to ecc.steps. Not possible for MLC flash */
	if (!(chip->options & NAND_NO_SUBPAGE_WRITE) && nand_is_slc(chip)) {
		switch (ecc->steps) {
		case 2:
			mtd->subpage_sft = 1;
			break;
		case 4:
		case 8:
		case 16:
			mtd->subpage_sft = 2;
			break;
		}
	}
	chip->subpagesize = mtd->writesize >> mtd->subpage_sft;

	/* Initialize state */
	chip->state = FL_READY;

	/* Invalidate the pagebuffer reference */
	chip->pagebuf = -1;

	/* Large page NAND with SOFT_ECC should support subpage reads */
	switch (ecc->mode) {
	case NAND_ECC_SOFT:
	case NAND_ECC_SOFT_BCH:
		if (chip->page_shift > 9)
			chip->options |= NAND_SUBPAGE_READ;
		break;

	default:
		break;
	}

	/* Fill in remaining MTD driver data */
	mtd->type = nand_is_slc(chip) ? MTD_NANDFLASH : MTD_MLCNANDFLASH;
	mtd->flags = (chip->options & NAND_ROM) ? MTD_CAP_ROM :
						MTD_CAP_NANDFLASH;
	mtd->_erase = nand_erase;
	mtd->_panic_write = panic_nand_write;
	mtd->_read_oob = nand_read_oob;
	mtd->_write_oob = nand_write_oob;
	mtd->_sync = nand_sync;
	mtd->_lock = NULL;
	mtd->_unlock = NULL;
	mtd->_block_isreserved = nand_block_isreserved;
	mtd->_block_isbad = nand_block_isbad;
	mtd->_block_markbad = nand_block_markbad;
	mtd->writebufsize = mtd->writesize;

	/* propagate ecc info to mtd_info */
	mtd->ecclayout = ecc->layout;
	mtd->ecc_strength = ecc->strength;
	mtd->ecc_step_size = ecc->size;
	/*
	 * Initialize bitflip_threshold to its default prior scan_bbt() call.
	 * scan_bbt() might invoke mtd_read(), thus bitflip_threshold must be
	 * properly set.
	 */
	if (!mtd->bitflip_threshold)
		mtd->bitflip_threshold = DIV_ROUND_UP(mtd->ecc_strength * 3, 4);

	return 0;
}
EXPORT_SYMBOL(nand_scan_tail);

/**
 * nand_scan - [NAND Interface] Scan for the NAND device
 * @mtd: MTD device structure
 * @maxchips: number of chips to scan for
 *
 * This fills out all the uninitialized function pointers with the defaults.
 * The flash ID is read and the mtd/chip structures are filled with the
 * appropriate values.
 */
int nand_scan(struct mtd_info *mtd, int maxchips)
{
	int ret;

	ret = nand_scan_ident(mtd, maxchips, NULL);
	if (!ret)
		ret = nand_scan_tail(mtd);
	return ret;
}
EXPORT_SYMBOL(nand_scan);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Steven J. Hill <sjhill@realitydiluted.com>");
MODULE_AUTHOR("Thomas Gleixner <tglx@linutronix.de>");
MODULE_DESCRIPTION("Generic NAND flash driver code");
