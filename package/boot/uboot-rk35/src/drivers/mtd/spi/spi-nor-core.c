// SPDX-License-Identifier: GPL-2.0
/*
 * Based on m25p80.c, by Mike Lavender (mike@steroidmicros.com), with
 * influence from lart.c (Abraham Van Der Merwe) and mtd_dataflash.c
 *
 * Copyright (C) 2005, Intec Automation Inc.
 * Copyright (C) 2014, Freescale Semiconductor, Inc.
 *
 * Synced from Linux v4.19
 */

#include <common.h>
#include <linux/err.h>
#include <linux/errno.h>
#include <linux/log2.h>
#include <linux/math64.h>
#include <linux/sizes.h>

#include <linux/mtd/mtd.h>
#include <linux/mtd/spi-nor.h>
#include <spi-mem.h>
#include <spi.h>

#include "sf_internal.h"

/* Define max times to check status register before we give up. */

/*
 * For everything but full-chip erase; probably could be much smaller, but kept
 * around for safety for now
 */

#define HZ					CONFIG_SYS_HZ

#define DEFAULT_READY_WAIT_JIFFIES		(40UL * HZ)

static int spi_nor_read_write_reg(struct spi_nor *nor, struct spi_mem_op
		*op, void *buf)
{
	if (op->data.dir == SPI_MEM_DATA_IN)
		op->data.buf.in = buf;
	else
		op->data.buf.out = buf;
	return spi_mem_exec_op(nor->spi, op);
}

static int spi_nor_read_reg(struct spi_nor *nor, u8 code, u8 *val, int len)
{
	struct spi_mem_op op = SPI_MEM_OP(SPI_MEM_OP_CMD(code, 1),
					  SPI_MEM_OP_NO_ADDR,
					  SPI_MEM_OP_NO_DUMMY,
					  SPI_MEM_OP_DATA_IN(len, NULL, 1));
	int ret;

	ret = spi_nor_read_write_reg(nor, &op, val);
	if (ret < 0)
		dev_dbg(&flash->spimem->spi->dev, "error %d reading %x\n", ret,
			code);

	return ret;
}

static int spi_nor_write_reg(struct spi_nor *nor, u8 opcode, u8 *buf, int len)
{
	struct spi_mem_op op = SPI_MEM_OP(SPI_MEM_OP_CMD(opcode, 1),
					  SPI_MEM_OP_NO_ADDR,
					  SPI_MEM_OP_NO_DUMMY,
					  SPI_MEM_OP_DATA_OUT(len, NULL, 1));

	return spi_nor_read_write_reg(nor, &op, buf);
}

static ssize_t spi_nor_read_data(struct spi_nor *nor, loff_t from, size_t len,
				 u_char *buf)
{
	struct spi_mem_op op =
			SPI_MEM_OP(SPI_MEM_OP_CMD(nor->read_opcode, 1),
				   SPI_MEM_OP_ADDR(nor->addr_width, from, 1),
				   SPI_MEM_OP_DUMMY(nor->read_dummy, 1),
				   SPI_MEM_OP_DATA_IN(len, buf, 1));
	size_t remaining = len;
	int ret;

	/* get transfer protocols. */
	op.cmd.buswidth = spi_nor_get_protocol_inst_nbits(nor->read_proto);
	op.addr.buswidth = spi_nor_get_protocol_addr_nbits(nor->read_proto);
	op.dummy.buswidth = op.addr.buswidth;
	op.data.buswidth = spi_nor_get_protocol_data_nbits(nor->read_proto);

	/* convert the dummy cycles to the number of bytes */
	op.dummy.nbytes = (nor->read_dummy * op.dummy.buswidth) / 8;

	while (remaining) {
		op.data.nbytes = remaining < UINT_MAX ? remaining : UINT_MAX;
		ret = spi_mem_adjust_op_size(nor->spi, &op);
		if (ret)
			return ret;

		ret = spi_mem_exec_op(nor->spi, &op);
		if (ret)
			return ret;

		op.addr.val += op.data.nbytes;
		remaining -= op.data.nbytes;
		op.data.buf.in += op.data.nbytes;
	}

	return len;
}

static ssize_t spi_nor_write_data(struct spi_nor *nor, loff_t to, size_t len,
				  const u_char *buf)
{
	struct spi_mem_op op =
			SPI_MEM_OP(SPI_MEM_OP_CMD(nor->program_opcode, 1),
				   SPI_MEM_OP_ADDR(nor->addr_width, to, 1),
				   SPI_MEM_OP_NO_DUMMY,
				   SPI_MEM_OP_DATA_OUT(len, buf, 1));
	int ret;

	/* get transfer protocols. */
	op.cmd.buswidth = spi_nor_get_protocol_inst_nbits(nor->write_proto);
	op.addr.buswidth = spi_nor_get_protocol_addr_nbits(nor->write_proto);
	op.data.buswidth = spi_nor_get_protocol_data_nbits(nor->write_proto);

	if (nor->program_opcode == SPINOR_OP_AAI_WP && nor->sst_write_second)
		op.addr.nbytes = 0;

	ret = spi_mem_adjust_op_size(nor->spi, &op);
	if (ret)
		return ret;
	op.data.nbytes = len < op.data.nbytes ? len : op.data.nbytes;

	ret = spi_mem_exec_op(nor->spi, &op);
	if (ret)
		return ret;

	return op.data.nbytes;
}

/*
 * Read the status register, returning its value in the location
 * Return the status register value.
 * Returns negative if error occurred.
 */
static int read_sr(struct spi_nor *nor)
{
	int ret;
	u8 val;

	ret = nor->read_reg(nor, SPINOR_OP_RDSR, &val, 1);
	if (ret < 0) {
		pr_debug("error %d reading SR\n", (int)ret);
		return ret;
	}

	return val;
}

/*
 * Read the flag status register, returning its value in the location
 * Return the status register value.
 * Returns negative if error occurred.
 */
static int read_fsr(struct spi_nor *nor)
{
	int ret;
	u8 val;

	ret = nor->read_reg(nor, SPINOR_OP_RDFSR, &val, 1);
	if (ret < 0) {
		pr_debug("error %d reading FSR\n", ret);
		return ret;
	}

	return val;
}

/*
 * Read configuration register, returning its value in the
 * location. Return the configuration register value.
 * Returns negative if error occurred.
 */
#if defined(CONFIG_SPI_FLASH_SPANSION) || defined(CONFIG_SPI_FLASH_WINBOND)
static int read_cr(struct spi_nor *nor)
{
	int ret;
	u8 val;

	ret = nor->read_reg(nor, SPINOR_OP_RDCR, &val, 1);
	if (ret < 0) {
		dev_dbg(nor->dev, "error %d reading CR\n", ret);
		return ret;
	}

	return val;
}
#endif

/*
 * Write status register 1 byte
 * Returns negative if error occurred.
 */
static int write_sr(struct spi_nor *nor, u8 val)
{
	nor->cmd_buf[0] = val;
	return nor->write_reg(nor, SPINOR_OP_WRSR, nor->cmd_buf, 1);
}

/*
 * Set write enable latch with Write Enable command.
 * Returns negative if error occurred.
 */
static int write_enable(struct spi_nor *nor)
{
	return nor->write_reg(nor, SPINOR_OP_WREN, NULL, 0);
}

/*
 * Send write disable instruction to the chip.
 */
static int write_disable(struct spi_nor *nor)
{
	return nor->write_reg(nor, SPINOR_OP_WRDI, NULL, 0);
}

static struct spi_nor *mtd_to_spi_nor(struct mtd_info *mtd)
{
	return mtd->priv;
}

#ifndef CONFIG_SPI_FLASH_BAR
static u8 spi_nor_convert_opcode(u8 opcode, const u8 table[][2], size_t size)
{
	size_t i;

	for (i = 0; i < size; i++)
		if (table[i][0] == opcode)
			return table[i][1];

	/* No conversion found, keep input op code. */
	return opcode;
}

static u8 spi_nor_convert_3to4_read(u8 opcode)
{
	static const u8 spi_nor_3to4_read[][2] = {
		{ SPINOR_OP_READ,	SPINOR_OP_READ_4B },
		{ SPINOR_OP_READ_FAST,	SPINOR_OP_READ_FAST_4B },
		{ SPINOR_OP_READ_1_1_2,	SPINOR_OP_READ_1_1_2_4B },
		{ SPINOR_OP_READ_1_2_2,	SPINOR_OP_READ_1_2_2_4B },
		{ SPINOR_OP_READ_1_1_4,	SPINOR_OP_READ_1_1_4_4B },
		{ SPINOR_OP_READ_1_4_4,	SPINOR_OP_READ_1_4_4_4B },
		{ SPINOR_OP_READ_1_1_8,	SPINOR_OP_READ_1_1_8_4B },
		{ SPINOR_OP_READ_1_8_8,	SPINOR_OP_READ_1_8_8_4B },

		{ SPINOR_OP_READ_1_1_1_DTR,	SPINOR_OP_READ_1_1_1_DTR_4B },
		{ SPINOR_OP_READ_1_2_2_DTR,	SPINOR_OP_READ_1_2_2_DTR_4B },
		{ SPINOR_OP_READ_1_4_4_DTR,	SPINOR_OP_READ_1_4_4_DTR_4B },
	};

	return spi_nor_convert_opcode(opcode, spi_nor_3to4_read,
				      ARRAY_SIZE(spi_nor_3to4_read));
}

static u8 spi_nor_convert_3to4_program(u8 opcode)
{
	static const u8 spi_nor_3to4_program[][2] = {
		{ SPINOR_OP_PP,		SPINOR_OP_PP_4B },
		{ SPINOR_OP_PP_1_1_4,	SPINOR_OP_PP_1_1_4_4B },
		{ SPINOR_OP_PP_1_4_4,	SPINOR_OP_PP_1_4_4_4B },
		{ SPINOR_OP_PP_1_1_8,	SPINOR_OP_PP_1_1_8_4B },
		{ SPINOR_OP_PP_1_8_8,	SPINOR_OP_PP_1_8_8_4B },
	};

	return spi_nor_convert_opcode(opcode, spi_nor_3to4_program,
				      ARRAY_SIZE(spi_nor_3to4_program));
}

static u8 spi_nor_convert_3to4_erase(u8 opcode)
{
	static const u8 spi_nor_3to4_erase[][2] = {
		{ SPINOR_OP_BE_4K,	SPINOR_OP_BE_4K_4B },
		{ SPINOR_OP_BE_32K,	SPINOR_OP_BE_32K_4B },
		{ SPINOR_OP_SE,		SPINOR_OP_SE_4B },
	};

	return spi_nor_convert_opcode(opcode, spi_nor_3to4_erase,
				      ARRAY_SIZE(spi_nor_3to4_erase));
}

static void spi_nor_set_4byte_opcodes(struct spi_nor *nor,
				      const struct flash_info *info)
{
	/* Do some manufacturer fixups first */
	switch (JEDEC_MFR(info)) {
	case SNOR_MFR_SPANSION:
		/* No small sector erase for 4-byte command set */
		nor->erase_opcode = SPINOR_OP_SE;
		nor->mtd.erasesize = info->sector_size;
		break;

	default:
		break;
	}

	nor->read_opcode = spi_nor_convert_3to4_read(nor->read_opcode);
	nor->program_opcode = spi_nor_convert_3to4_program(nor->program_opcode);
	nor->erase_opcode = spi_nor_convert_3to4_erase(nor->erase_opcode);
}
#endif /* !CONFIG_SPI_FLASH_BAR */

/* Enable/disable 4-byte addressing mode. */
static int set_4byte(struct spi_nor *nor, const struct flash_info *info,
		     int enable)
{
	int status;
	bool need_wren = false;
	u8 cmd;

	switch (JEDEC_MFR(info)) {
	case SNOR_MFR_ST:
	case SNOR_MFR_MICRON:
		/* Some Micron need WREN command; all will accept it */
		need_wren = true;
	case SNOR_MFR_MACRONIX:
	case SNOR_MFR_WINBOND:
		if (need_wren)
			write_enable(nor);

		cmd = enable ? SPINOR_OP_EN4B : SPINOR_OP_EX4B;
		status = nor->write_reg(nor, cmd, NULL, 0);
		if (need_wren)
			write_disable(nor);

		if (!status && !enable &&
		    JEDEC_MFR(info) == SNOR_MFR_WINBOND) {
			/*
			 * On Winbond W25Q256FV, leaving 4byte mode causes
			 * the Extended Address Register to be set to 1, so all
			 * 3-byte-address reads come from the second 16M.
			 * We must clear the register to enable normal behavior.
			 */
			write_enable(nor);
			nor->cmd_buf[0] = 0;
			nor->write_reg(nor, SPINOR_OP_WREAR, nor->cmd_buf, 1);
			write_disable(nor);
		}

		return status;
	default:
		/* Spansion style */
		nor->cmd_buf[0] = enable << 7;
		return nor->write_reg(nor, SPINOR_OP_BRWR, nor->cmd_buf, 1);
	}
}

static int spi_nor_sr_ready(struct spi_nor *nor)
{
	int sr = read_sr(nor);

	if (sr < 0)
		return sr;

	if (nor->flags & SNOR_F_USE_CLSR && sr & (SR_E_ERR | SR_P_ERR)) {
		if (sr & SR_E_ERR)
			dev_dbg(nor->dev, "Erase Error occurred\n");
		else
			dev_dbg(nor->dev, "Programming Error occurred\n");

		nor->write_reg(nor, SPINOR_OP_CLSR, NULL, 0);
		return -EIO;
	}

	return !(sr & SR_WIP);
}

static int spi_nor_fsr_ready(struct spi_nor *nor)
{
	int fsr = read_fsr(nor);

	if (fsr < 0)
		return fsr;

	if (fsr & (FSR_E_ERR | FSR_P_ERR)) {
		if (fsr & FSR_E_ERR)
			dev_err(nor->dev, "Erase operation failed.\n");
		else
			dev_err(nor->dev, "Program operation failed.\n");

		if (fsr & FSR_PT_ERR)
			dev_err(nor->dev,
				"Attempted to modify a protected sector.\n");

		nor->write_reg(nor, SPINOR_OP_CLFSR, NULL, 0);
		return -EIO;
	}

	return fsr & FSR_READY;
}

static int spi_nor_ready(struct spi_nor *nor)
{
	int sr, fsr;

	sr = spi_nor_sr_ready(nor);
	if (sr < 0)
		return sr;
	fsr = nor->flags & SNOR_F_USE_FSR ? spi_nor_fsr_ready(nor) : 1;
	if (fsr < 0)
		return fsr;
	return sr && fsr;
}

/*
 * Service routine to read status register until ready, or timeout occurs.
 * Returns non-zero if error.
 */
static int spi_nor_wait_till_ready_with_timeout(struct spi_nor *nor,
						unsigned long timeout)
{
	unsigned long timebase;
	int ret;

	timebase = get_timer(0);

	while (get_timer(timebase) < timeout) {
		ret = spi_nor_ready(nor);
		if (ret < 0)
			return ret;
		if (ret)
			return 0;
	}

	dev_err(nor->dev, "flash operation timed out\n");

	return -ETIMEDOUT;
}

static int spi_nor_wait_till_ready(struct spi_nor *nor)
{
	return spi_nor_wait_till_ready_with_timeout(nor,
						    DEFAULT_READY_WAIT_JIFFIES);
}

#ifdef CONFIG_SPI_FLASH_BAR
/*
 * This "clean_bar" is necessary in a situation when one was accessing
 * spi flash memory > 16 MiB by using Bank Address Register's BA24 bit.
 *
 * After it the BA24 bit shall be cleared to allow access to correct
 * memory region after SW reset (by calling "reset" command).
 *
 * Otherwise, the BA24 bit may be left set and then after reset, the
 * ROM would read/write/erase SPL from 16 MiB * bank_sel address.
 */
static int clean_bar(struct spi_nor *nor)
{
	u8 cmd, bank_sel = 0;

	if (nor->bank_curr == 0)
		return 0;
	cmd = nor->bank_write_cmd;
	nor->bank_curr = 0;
	write_enable(nor);

	return nor->write_reg(nor, cmd, &bank_sel, 1);
}

static int write_bar(struct spi_nor *nor, u32 offset)
{
	u8 cmd, bank_sel;
	int ret;

	bank_sel = offset / SZ_16M;
	if (bank_sel == nor->bank_curr)
		goto bar_end;

	cmd = nor->bank_write_cmd;
	write_enable(nor);
	ret = nor->write_reg(nor, cmd, &bank_sel, 1);
	if (ret < 0) {
		debug("SF: fail to write bank register\n");
		return ret;
	}

bar_end:
	nor->bank_curr = bank_sel;
	return nor->bank_curr;
}

static int read_bar(struct spi_nor *nor, const struct flash_info *info)
{
	u8 curr_bank = 0;
	int ret;

	switch (JEDEC_MFR(info)) {
	case SNOR_MFR_SPANSION:
		nor->bank_read_cmd = SPINOR_OP_BRRD;
		nor->bank_write_cmd = SPINOR_OP_BRWR;
		break;
	default:
		nor->bank_read_cmd = SPINOR_OP_RDEAR;
		nor->bank_write_cmd = SPINOR_OP_WREAR;
	}

	ret = nor->read_reg(nor, nor->bank_read_cmd,
				    &curr_bank, 1);
	if (ret) {
		debug("SF: fail to read bank addr register\n");
		return ret;
	}
	nor->bank_curr = curr_bank;

	return 0;
}
#endif

/*
 * Initiate the erasure of a single sector
 */
static int spi_nor_erase_sector(struct spi_nor *nor, u32 addr)
{
	struct spi_mem_op op =
		SPI_MEM_OP(SPI_MEM_OP_CMD(nor->erase_opcode, 1),
			   SPI_MEM_OP_ADDR(nor->addr_width, addr, 1),
			   SPI_MEM_OP_NO_DUMMY,
			   SPI_MEM_OP_NO_DATA);

	if (nor->erase)
		return nor->erase(nor, addr);

	/*
	 * Default implementation, if driver doesn't have a specialized HW
	 * control
	 */
	return spi_mem_exec_op(nor->spi, &op);
}

/*
 * Erase an address range on the nor chip.  The address range may extend
 * one or more erase sectors.  Return an error is there is a problem erasing.
 */
static int spi_nor_erase(struct mtd_info *mtd, struct erase_info *instr)
{
	struct spi_nor *nor = mtd_to_spi_nor(mtd);
	u32 addr, len, rem;
	int ret;

	dev_dbg(nor->dev, "at 0x%llx, len %lld\n", (long long)instr->addr,
		(long long)instr->len);

	div_u64_rem(instr->len, mtd->erasesize, &rem);
	if (rem)
		return -EINVAL;

	addr = instr->addr;
	len = instr->len;

	while (len) {
#ifdef CONFIG_SPI_FLASH_BAR
		ret = write_bar(nor, addr);
		if (ret < 0)
			return ret;
#endif
		write_enable(nor);

		ret = spi_nor_erase_sector(nor, addr);
		if (ret)
			goto erase_err;

		addr += mtd->erasesize;
		len -= mtd->erasesize;

		ret = spi_nor_wait_till_ready(nor);
		if (ret)
			goto erase_err;
	}

erase_err:
#ifdef CONFIG_SPI_FLASH_BAR
	ret = clean_bar(nor);
#endif
	write_disable(nor);

	return ret;
}

#if defined(CONFIG_SPI_FLASH_STMICRO) || defined(CONFIG_SPI_FLASH_SST)
/* Write status register and ensure bits in mask match written values */
static int write_sr_and_check(struct spi_nor *nor, u8 status_new, u8 mask)
{
	int ret;

	write_enable(nor);
	ret = write_sr(nor, status_new);
	if (ret)
		return ret;

	ret = spi_nor_wait_till_ready(nor);
	if (ret)
		return ret;

	ret = read_sr(nor);
	if (ret < 0)
		return ret;

	return ((ret & mask) != (status_new & mask)) ? -EIO : 0;
}

static void stm_get_locked_range(struct spi_nor *nor, u8 sr, loff_t *ofs,
				 uint64_t *len)
{
	struct mtd_info *mtd = &nor->mtd;
	u8 mask = SR_BP2 | SR_BP1 | SR_BP0;
	int shift = ffs(mask) - 1;
	int pow;

	if (!(sr & mask)) {
		/* No protection */
		*ofs = 0;
		*len = 0;
	} else {
		pow = ((sr & mask) ^ mask) >> shift;
		*len = mtd->size >> pow;
		if (nor->flags & SNOR_F_HAS_SR_TB && sr & SR_TB)
			*ofs = 0;
		else
			*ofs = mtd->size - *len;
	}
}

/*
 * Return 1 if the entire region is locked (if @locked is true) or unlocked (if
 * @locked is false); 0 otherwise
 */
static int stm_check_lock_status_sr(struct spi_nor *nor, loff_t ofs, u64 len,
				    u8 sr, bool locked)
{
	loff_t lock_offs;
	uint64_t lock_len;

	if (!len)
		return 1;

	stm_get_locked_range(nor, sr, &lock_offs, &lock_len);

	if (locked)
		/* Requested range is a sub-range of locked range */
		return (ofs + len <= lock_offs + lock_len) && (ofs >= lock_offs);
	else
		/* Requested range does not overlap with locked range */
		return (ofs >= lock_offs + lock_len) || (ofs + len <= lock_offs);
}

static int stm_is_locked_sr(struct spi_nor *nor, loff_t ofs, uint64_t len,
			    u8 sr)
{
	return stm_check_lock_status_sr(nor, ofs, len, sr, true);
}

static int stm_is_unlocked_sr(struct spi_nor *nor, loff_t ofs, uint64_t len,
			      u8 sr)
{
	return stm_check_lock_status_sr(nor, ofs, len, sr, false);
}

/*
 * Lock a region of the flash. Compatible with ST Micro and similar flash.
 * Supports the block protection bits BP{0,1,2} in the status register
 * (SR). Does not support these features found in newer SR bitfields:
 *   - SEC: sector/block protect - only handle SEC=0 (block protect)
 *   - CMP: complement protect - only support CMP=0 (range is not complemented)
 *
 * Support for the following is provided conditionally for some flash:
 *   - TB: top/bottom protect
 *
 * Sample table portion for 8MB flash (Winbond w25q64fw):
 *
 *   SEC  |  TB   |  BP2  |  BP1  |  BP0  |  Prot Length  | Protected Portion
 *  --------------------------------------------------------------------------
 *    X   |   X   |   0   |   0   |   0   |  NONE         | NONE
 *    0   |   0   |   0   |   0   |   1   |  128 KB       | Upper 1/64
 *    0   |   0   |   0   |   1   |   0   |  256 KB       | Upper 1/32
 *    0   |   0   |   0   |   1   |   1   |  512 KB       | Upper 1/16
 *    0   |   0   |   1   |   0   |   0   |  1 MB         | Upper 1/8
 *    0   |   0   |   1   |   0   |   1   |  2 MB         | Upper 1/4
 *    0   |   0   |   1   |   1   |   0   |  4 MB         | Upper 1/2
 *    X   |   X   |   1   |   1   |   1   |  8 MB         | ALL
 *  ------|-------|-------|-------|-------|---------------|-------------------
 *    0   |   1   |   0   |   0   |   1   |  128 KB       | Lower 1/64
 *    0   |   1   |   0   |   1   |   0   |  256 KB       | Lower 1/32
 *    0   |   1   |   0   |   1   |   1   |  512 KB       | Lower 1/16
 *    0   |   1   |   1   |   0   |   0   |  1 MB         | Lower 1/8
 *    0   |   1   |   1   |   0   |   1   |  2 MB         | Lower 1/4
 *    0   |   1   |   1   |   1   |   0   |  4 MB         | Lower 1/2
 *
 * Returns negative on errors, 0 on success.
 */
static int stm_lock(struct spi_nor *nor, loff_t ofs, uint64_t len)
{
	struct mtd_info *mtd = &nor->mtd;
	int status_old, status_new;
	u8 mask = SR_BP2 | SR_BP1 | SR_BP0;
	u8 shift = ffs(mask) - 1, pow, val;
	loff_t lock_len;
	bool can_be_top = true, can_be_bottom = nor->flags & SNOR_F_HAS_SR_TB;
	bool use_top;

	status_old = read_sr(nor);
	if (status_old < 0)
		return status_old;

	/* If nothing in our range is unlocked, we don't need to do anything */
	if (stm_is_locked_sr(nor, ofs, len, status_old))
		return 0;

	/* If anything below us is unlocked, we can't use 'bottom' protection */
	if (!stm_is_locked_sr(nor, 0, ofs, status_old))
		can_be_bottom = false;

	/* If anything above us is unlocked, we can't use 'top' protection */
	if (!stm_is_locked_sr(nor, ofs + len, mtd->size - (ofs + len),
			      status_old))
		can_be_top = false;

	if (!can_be_bottom && !can_be_top)
		return -EINVAL;

	/* Prefer top, if both are valid */
	use_top = can_be_top;

	/* lock_len: length of region that should end up locked */
	if (use_top)
		lock_len = mtd->size - ofs;
	else
		lock_len = ofs + len;

	/*
	 * Need smallest pow such that:
	 *
	 *   1 / (2^pow) <= (len / size)
	 *
	 * so (assuming power-of-2 size) we do:
	 *
	 *   pow = ceil(log2(size / len)) = log2(size) - floor(log2(len))
	 */
	pow = ilog2(mtd->size) - ilog2(lock_len);
	val = mask - (pow << shift);
	if (val & ~mask)
		return -EINVAL;
	/* Don't "lock" with no region! */
	if (!(val & mask))
		return -EINVAL;

	status_new = (status_old & ~mask & ~SR_TB) | val;

	/* Disallow further writes if WP pin is asserted */
	status_new |= SR_SRWD;

	if (!use_top)
		status_new |= SR_TB;

	/* Don't bother if they're the same */
	if (status_new == status_old)
		return 0;

	/* Only modify protection if it will not unlock other areas */
	if ((status_new & mask) < (status_old & mask))
		return -EINVAL;

	return write_sr_and_check(nor, status_new, mask);
}

/*
 * Unlock a region of the flash. See stm_lock() for more info
 *
 * Returns negative on errors, 0 on success.
 */
static int stm_unlock(struct spi_nor *nor, loff_t ofs, uint64_t len)
{
	struct mtd_info *mtd = &nor->mtd;
	int status_old, status_new;
	u8 mask = SR_BP2 | SR_BP1 | SR_BP0;
	u8 shift = ffs(mask) - 1, pow, val;
	loff_t lock_len;
	bool can_be_top = true, can_be_bottom = nor->flags & SNOR_F_HAS_SR_TB;
	bool use_top;

	status_old = read_sr(nor);
	if (status_old < 0)
		return status_old;

	/* If nothing in our range is locked, we don't need to do anything */
	if (stm_is_unlocked_sr(nor, ofs, len, status_old))
		return 0;

	/* If anything below us is locked, we can't use 'top' protection */
	if (!stm_is_unlocked_sr(nor, 0, ofs, status_old))
		can_be_top = false;

	/* If anything above us is locked, we can't use 'bottom' protection */
	if (!stm_is_unlocked_sr(nor, ofs + len, mtd->size - (ofs + len),
				status_old))
		can_be_bottom = false;

	if (!can_be_bottom && !can_be_top)
		return -EINVAL;

	/* Prefer top, if both are valid */
	use_top = can_be_top;

	/* lock_len: length of region that should remain locked */
	if (use_top)
		lock_len = mtd->size - (ofs + len);
	else
		lock_len = ofs;

	/*
	 * Need largest pow such that:
	 *
	 *   1 / (2^pow) >= (len / size)
	 *
	 * so (assuming power-of-2 size) we do:
	 *
	 *   pow = floor(log2(size / len)) = log2(size) - ceil(log2(len))
	 */
	pow = ilog2(mtd->size) - order_base_2(lock_len);
	if (lock_len == 0) {
		val = 0; /* fully unlocked */
	} else {
		val = mask - (pow << shift);
		/* Some power-of-two sizes are not supported */
		if (val & ~mask)
			return -EINVAL;
	}

	status_new = (status_old & ~mask & ~SR_TB) | val;

	/* Don't protect status register if we're fully unlocked */
	if (lock_len == 0)
		status_new &= ~SR_SRWD;

	if (!use_top)
		status_new |= SR_TB;

	/* Don't bother if they're the same */
	if (status_new == status_old)
		return 0;

	/* Only modify protection if it will not lock other areas */
	if ((status_new & mask) > (status_old & mask))
		return -EINVAL;

	return write_sr_and_check(nor, status_new, mask);
}

/*
 * Check if a region of the flash is (completely) locked. See stm_lock() for
 * more info.
 *
 * Returns 1 if entire region is locked, 0 if any portion is unlocked, and
 * negative on errors.
 */
static int stm_is_locked(struct spi_nor *nor, loff_t ofs, uint64_t len)
{
	int status;

	status = read_sr(nor);
	if (status < 0)
		return status;

	return stm_is_locked_sr(nor, ofs, len, status);
}
#endif /* CONFIG_SPI_FLASH_STMICRO */

static const struct flash_info *spi_nor_read_id(struct spi_nor *nor)
{
	int			tmp;
	u8			id[SPI_NOR_MAX_ID_LEN];
	const struct flash_info	*info;

	tmp = nor->read_reg(nor, SPINOR_OP_RDID, id, SPI_NOR_MAX_ID_LEN);
	if (tmp < 0) {
		dev_dbg(nor->dev, "error %d reading JEDEC ID\n", tmp);
		return ERR_PTR(tmp);
	}

	info = spi_nor_ids;
	for (; info->name; info++) {
		if (info->id_len) {
			if (!memcmp(info->id, id, info->id_len))
				return info;
		}
	}

	dev_err(nor->dev, "unrecognized JEDEC id bytes: %02x, %02x, %02x\n",
		id[0], id[1], id[2]);
	return ERR_PTR(-ENODEV);
}

static int spi_nor_read(struct mtd_info *mtd, loff_t from, size_t len,
			size_t *retlen, u_char *buf)
{
	struct spi_nor *nor = mtd_to_spi_nor(mtd);
	int ret;

	dev_dbg(nor->dev, "from 0x%08x, len %zd\n", (u32)from, len);

	while (len) {
		loff_t addr = from;
		size_t read_len = len;

#ifdef CONFIG_SPI_FLASH_BAR
		u32 remain_len;

		ret = write_bar(nor, addr);
		if (ret < 0)
			return log_ret(ret);
		remain_len = (SZ_16M * (nor->bank_curr + 1)) - addr;

		if (len < remain_len)
			read_len = len;
		else
			read_len = remain_len;
#endif

		ret = nor->read(nor, addr, read_len, buf);
		if (ret == 0) {
			/* We shouldn't see 0-length reads */
			ret = -EIO;
			goto read_err;
		}
		if (ret < 0)
			goto read_err;

		*retlen += ret;
		buf += ret;
		from += ret;
		len -= ret;
	}
	ret = 0;

read_err:
#ifdef CONFIG_SPI_FLASH_BAR
	ret = clean_bar(nor);
#endif
	return ret;
}

#ifdef CONFIG_SPI_FLASH_SST
/*
 * sst26 flash series has its own block protection implementation:
 * 4x   - 8  KByte blocks - read & write protection bits - upper addresses
 * 1x   - 32 KByte blocks - write protection bits
 * rest - 64 KByte blocks - write protection bits
 * 1x   - 32 KByte blocks - write protection bits
 * 4x   - 8  KByte blocks - read & write protection bits - lower addresses
 *
 * We'll support only per 64k lock/unlock so lower and upper 64 KByte region
 * will be treated as single block.
 */
#define SST26_BPR_8K_NUM		4
#define SST26_MAX_BPR_REG_LEN		(18 + 1)
#define SST26_BOUND_REG_SIZE		((32 + SST26_BPR_8K_NUM * 8) * SZ_1K)

enum lock_ctl {
	SST26_CTL_LOCK,
	SST26_CTL_UNLOCK,
	SST26_CTL_CHECK
};

static bool sst26_process_bpr(u32 bpr_size, u8 *cmd, u32 bit, enum lock_ctl ctl)
{
	switch (ctl) {
	case SST26_CTL_LOCK:
		cmd[bpr_size - (bit / 8) - 1] |= BIT(bit % 8);
		break;
	case SST26_CTL_UNLOCK:
		cmd[bpr_size - (bit / 8) - 1] &= ~BIT(bit % 8);
		break;
	case SST26_CTL_CHECK:
		return !!(cmd[bpr_size - (bit / 8) - 1] & BIT(bit % 8));
	}

	return false;
}

/*
 * Lock, unlock or check lock status of the flash region of the flash (depending
 * on the lock_ctl value)
 */
static int sst26_lock_ctl(struct spi_nor *nor, loff_t ofs, uint64_t len, enum lock_ctl ctl)
{
	struct mtd_info *mtd = &nor->mtd;
	u32 i, bpr_ptr, rptr_64k, lptr_64k, bpr_size;
	bool lower_64k = false, upper_64k = false;
	u8 bpr_buff[SST26_MAX_BPR_REG_LEN] = {};
	int ret;

	/* Check length and offset for 64k alignment */
	if ((ofs & (SZ_64K - 1)) || (len & (SZ_64K - 1))) {
		dev_err(nor->dev, "length or offset is not 64KiB allighned\n");
		return -EINVAL;
	}

	if (ofs + len > mtd->size) {
		dev_err(nor->dev, "range is more than device size: %#llx + %#llx > %#llx\n",
			ofs, len, mtd->size);
		return -EINVAL;
	}

	/* SST26 family has only 16 Mbit, 32 Mbit and 64 Mbit IC */
	if (mtd->size != SZ_2M &&
	    mtd->size != SZ_4M &&
	    mtd->size != SZ_8M)
		return -EINVAL;

	bpr_size = 2 + (mtd->size / SZ_64K / 8);

	ret = nor->read_reg(nor, SPINOR_OP_READ_BPR, bpr_buff, bpr_size);
	if (ret < 0) {
		dev_err(nor->dev, "fail to read block-protection register\n");
		return ret;
	}

	rptr_64k = min_t(u32, ofs + len, mtd->size - SST26_BOUND_REG_SIZE);
	lptr_64k = max_t(u32, ofs, SST26_BOUND_REG_SIZE);

	upper_64k = ((ofs + len) > (mtd->size - SST26_BOUND_REG_SIZE));
	lower_64k = (ofs < SST26_BOUND_REG_SIZE);

	/* Lower bits in block-protection register are about 64k region */
	bpr_ptr = lptr_64k / SZ_64K - 1;

	/* Process 64K blocks region */
	while (lptr_64k < rptr_64k) {
		if (sst26_process_bpr(bpr_size, bpr_buff, bpr_ptr, ctl))
			return EACCES;

		bpr_ptr++;
		lptr_64k += SZ_64K;
	}

	/* 32K and 8K region bits in BPR are after 64k region bits */
	bpr_ptr = (mtd->size - 2 * SST26_BOUND_REG_SIZE) / SZ_64K;

	/* Process lower 32K block region */
	if (lower_64k)
		if (sst26_process_bpr(bpr_size, bpr_buff, bpr_ptr, ctl))
			return EACCES;

	bpr_ptr++;

	/* Process upper 32K block region */
	if (upper_64k)
		if (sst26_process_bpr(bpr_size, bpr_buff, bpr_ptr, ctl))
			return EACCES;

	bpr_ptr++;

	/* Process lower 8K block regions */
	for (i = 0; i < SST26_BPR_8K_NUM; i++) {
		if (lower_64k)
			if (sst26_process_bpr(bpr_size, bpr_buff, bpr_ptr, ctl))
				return EACCES;

		/* In 8K area BPR has both read and write protection bits */
		bpr_ptr += 2;
	}

	/* Process upper 8K block regions */
	for (i = 0; i < SST26_BPR_8K_NUM; i++) {
		if (upper_64k)
			if (sst26_process_bpr(bpr_size, bpr_buff, bpr_ptr, ctl))
				return EACCES;

		/* In 8K area BPR has both read and write protection bits */
		bpr_ptr += 2;
	}

	/* If we check region status we don't need to write BPR back */
	if (ctl == SST26_CTL_CHECK)
		return 0;

	ret = nor->write_reg(nor, SPINOR_OP_WRITE_BPR, bpr_buff, bpr_size);
	if (ret < 0) {
		dev_err(nor->dev, "fail to write block-protection register\n");
		return ret;
	}

	return 0;
}

static int sst26_unlock(struct spi_nor *nor, loff_t ofs, uint64_t len)
{
	return sst26_lock_ctl(nor, ofs, len, SST26_CTL_UNLOCK);
}

static int sst26_lock(struct spi_nor *nor, loff_t ofs, uint64_t len)
{
	return sst26_lock_ctl(nor, ofs, len, SST26_CTL_LOCK);
}

/*
 * Returns EACCES (positive value) if region is locked, 0 if region is unlocked,
 * and negative on errors.
 */
static int sst26_is_locked(struct spi_nor *nor, loff_t ofs, uint64_t len)
{
	/*
	 * is_locked function is used for check before reading or erasing flash
	 * region, so offset and length might be not 64k allighned, so adjust
	 * them to be 64k allighned as sst26_lock_ctl works only with 64k
	 * allighned regions.
	 */
	ofs -= ofs & (SZ_64K - 1);
	len = len & (SZ_64K - 1) ? (len & ~(SZ_64K - 1)) + SZ_64K : len;

	return sst26_lock_ctl(nor, ofs, len, SST26_CTL_CHECK);
}

static int sst_write_byteprogram(struct spi_nor *nor, loff_t to, size_t len,
				 size_t *retlen, const u_char *buf)
{
	size_t actual;
	int ret = 0;

	for (actual = 0; actual < len; actual++) {
		nor->program_opcode = SPINOR_OP_BP;

		write_enable(nor);
		/* write one byte. */
		ret = nor->write(nor, to, 1, buf + actual);
		if (ret < 0)
			goto sst_write_err;
		ret = spi_nor_wait_till_ready(nor);
		if (ret)
			goto sst_write_err;
		to++;
	}

sst_write_err:
	write_disable(nor);
	return ret;
}

static int sst_write(struct mtd_info *mtd, loff_t to, size_t len,
		     size_t *retlen, const u_char *buf)
{
	struct spi_nor *nor = mtd_to_spi_nor(mtd);
	struct spi_slave *spi = nor->spi;
	size_t actual;
	int ret;

	dev_dbg(nor->dev, "to 0x%08x, len %zd\n", (u32)to, len);
	if (spi->mode & SPI_TX_BYTE)
		return sst_write_byteprogram(nor, to, len, retlen, buf);

	write_enable(nor);

	nor->sst_write_second = false;

	actual = to % 2;
	/* Start write from odd address. */
	if (actual) {
		nor->program_opcode = SPINOR_OP_BP;

		/* write one byte. */
		ret = nor->write(nor, to, 1, buf);
		if (ret < 0)
			goto sst_write_err;
		ret = spi_nor_wait_till_ready(nor);
		if (ret)
			goto sst_write_err;
	}
	to += actual;

	/* Write out most of the data here. */
	for (; actual < len - 1; actual += 2) {
		nor->program_opcode = SPINOR_OP_AAI_WP;

		/* write two bytes. */
		ret = nor->write(nor, to, 2, buf + actual);
		if (ret < 0)
			goto sst_write_err;
		ret = spi_nor_wait_till_ready(nor);
		if (ret)
			goto sst_write_err;
		to += 2;
		nor->sst_write_second = true;
	}
	nor->sst_write_second = false;

	write_disable(nor);
	ret = spi_nor_wait_till_ready(nor);
	if (ret)
		goto sst_write_err;

	/* Write out trailing byte if it exists. */
	if (actual != len) {
		write_enable(nor);

		nor->program_opcode = SPINOR_OP_BP;
		ret = nor->write(nor, to, 1, buf + actual);
		if (ret < 0)
			goto sst_write_err;
		ret = spi_nor_wait_till_ready(nor);
		if (ret)
			goto sst_write_err;
		write_disable(nor);
		actual += 1;
	}
sst_write_err:
	*retlen += actual;
	return ret;
}
#endif
/*
 * Write an address range to the nor chip.  Data must be written in
 * FLASH_PAGESIZE chunks.  The address range may be any size provided
 * it is within the physical boundaries.
 */
static int spi_nor_write(struct mtd_info *mtd, loff_t to, size_t len,
	size_t *retlen, const u_char *buf)
{
	struct spi_nor *nor = mtd_to_spi_nor(mtd);
	size_t page_offset, page_remain, i;
	ssize_t ret;

	dev_dbg(nor->dev, "to 0x%08x, len %zd\n", (u32)to, len);

	for (i = 0; i < len; ) {
		ssize_t written;
		loff_t addr = to + i;

		/*
		 * If page_size is a power of two, the offset can be quickly
		 * calculated with an AND operation. On the other cases we
		 * need to do a modulus operation (more expensive).
		 * Power of two numbers have only one bit set and we can use
		 * the instruction hweight32 to detect if we need to do a
		 * modulus (do_div()) or not.
		 */
		if (hweight32(nor->page_size) == 1) {
			page_offset = addr & (nor->page_size - 1);
		} else {
			u64 aux = addr;

			page_offset = do_div(aux, nor->page_size);
		}
		/* the size of data remaining on the first page */
		page_remain = min_t(size_t,
				    nor->page_size - page_offset, len - i);

#ifdef CONFIG_SPI_FLASH_BAR
		ret = write_bar(nor, addr);
		if (ret < 0)
			return ret;
#endif
		write_enable(nor);
		ret = nor->write(nor, addr, page_remain, buf + i);
		if (ret < 0)
			goto write_err;
		written = ret;

		ret = spi_nor_wait_till_ready(nor);
		if (ret)
			goto write_err;
		*retlen += written;
		i += written;
	}

write_err:
#ifdef CONFIG_SPI_FLASH_BAR
	ret = clean_bar(nor);
#endif
	return ret;
}

#ifdef CONFIG_SPI_FLASH_MACRONIX
/**
 * macronix_quad_enable() - set QE bit in Status Register.
 * @nor:	pointer to a 'struct spi_nor'
 *
 * Set the Quad Enable (QE) bit in the Status Register.
 *
 * bit 6 of the Status Register is the QE bit for Macronix like QSPI memories.
 *
 * Return: 0 on success, -errno otherwise.
 */
static int macronix_quad_enable(struct spi_nor *nor)
{
	int ret, val;

	val = read_sr(nor);
	if (val < 0)
		return val;
	if (val & SR_QUAD_EN_MX)
		return 0;

	write_enable(nor);

	write_sr(nor, val | SR_QUAD_EN_MX);

	ret = spi_nor_wait_till_ready(nor);
	if (ret)
		return ret;

	ret = read_sr(nor);
	if (!(ret > 0 && (ret & SR_QUAD_EN_MX))) {
		dev_err(nor->dev, "Macronix Quad bit not set\n");
		return -EINVAL;
	}

	return 0;
}
#endif

#if defined(CONFIG_SPI_FLASH_SPANSION) || defined(CONFIG_SPI_FLASH_WINBOND)
/*
 * Write status Register and configuration register with 2 bytes
 * The first byte will be written to the status register, while the
 * second byte will be written to the configuration register.
 * Return negative if error occurred.
 */
static int write_sr_cr(struct spi_nor *nor, u8 *sr_cr)
{
	int ret;

	write_enable(nor);

	ret = nor->write_reg(nor, SPINOR_OP_WRSR, sr_cr, 2);
	if (ret < 0) {
		dev_dbg(nor->dev,
			"error while writing configuration register\n");
		return -EINVAL;
	}

	ret = spi_nor_wait_till_ready(nor);
	if (ret) {
		dev_dbg(nor->dev,
			"timeout while writing configuration register\n");
		return ret;
	}

	return 0;
}

/**
 * spansion_read_cr_quad_enable() - set QE bit in Configuration Register.
 * @nor:	pointer to a 'struct spi_nor'
 *
 * Set the Quad Enable (QE) bit in the Configuration Register.
 * This function should be used with QSPI memories supporting the Read
 * Configuration Register (35h) instruction.
 *
 * bit 1 of the Configuration Register is the QE bit for Spansion like QSPI
 * memories.
 *
 * Return: 0 on success, -errno otherwise.
 */
static int spansion_read_cr_quad_enable(struct spi_nor *nor)
{
	u8 sr_cr[2];
	int ret;

	/* Check current Quad Enable bit value. */
	ret = read_cr(nor);
	if (ret < 0) {
		dev_dbg(dev, "error while reading configuration register\n");
		return -EINVAL;
	}

	if (ret & CR_QUAD_EN_SPAN)
		return 0;

	sr_cr[1] = ret | CR_QUAD_EN_SPAN;

	/* Keep the current value of the Status Register. */
	ret = read_sr(nor);
	if (ret < 0) {
		dev_dbg(dev, "error while reading status register\n");
		return -EINVAL;
	}
	sr_cr[0] = ret;

	ret = write_sr_cr(nor, sr_cr);
	if (ret)
		return ret;

	/* Read back and check it. */
	ret = read_cr(nor);
	if (!(ret > 0 && (ret & CR_QUAD_EN_SPAN))) {
		dev_dbg(nor->dev, "Spansion Quad bit not set\n");
		return -EINVAL;
	}

	return 0;
}

#if CONFIG_IS_ENABLED(SPI_FLASH_SFDP_SUPPORT)
/**
 * spansion_no_read_cr_quad_enable() - set QE bit in Configuration Register.
 * @nor:	pointer to a 'struct spi_nor'
 *
 * Set the Quad Enable (QE) bit in the Configuration Register.
 * This function should be used with QSPI memories not supporting the Read
 * Configuration Register (35h) instruction.
 *
 * bit 1 of the Configuration Register is the QE bit for Spansion like QSPI
 * memories.
 *
 * Return: 0 on success, -errno otherwise.
 */
static int spansion_no_read_cr_quad_enable(struct spi_nor *nor)
{
	u8 sr_cr[2];
	int ret;

	/* Keep the current value of the Status Register. */
	ret = read_sr(nor);
	if (ret < 0) {
		dev_dbg(nor->dev, "error while reading status register\n");
		return -EINVAL;
	}
	sr_cr[0] = ret;
	sr_cr[1] = CR_QUAD_EN_SPAN;

	return write_sr_cr(nor, sr_cr);
}

#endif /* CONFIG_SPI_FLASH_SFDP_SUPPORT */
#endif /* CONFIG_SPI_FLASH_SPANSION */

struct spi_nor_read_command {
	u8			num_mode_clocks;
	u8			num_wait_states;
	u8			opcode;
	enum spi_nor_protocol	proto;
};

struct spi_nor_pp_command {
	u8			opcode;
	enum spi_nor_protocol	proto;
};

enum spi_nor_read_command_index {
	SNOR_CMD_READ,
	SNOR_CMD_READ_FAST,
	SNOR_CMD_READ_1_1_1_DTR,

	/* Dual SPI */
	SNOR_CMD_READ_1_1_2,
	SNOR_CMD_READ_1_2_2,
	SNOR_CMD_READ_2_2_2,
	SNOR_CMD_READ_1_2_2_DTR,

	/* Quad SPI */
	SNOR_CMD_READ_1_1_4,
	SNOR_CMD_READ_1_4_4,
	SNOR_CMD_READ_4_4_4,
	SNOR_CMD_READ_1_4_4_DTR,

	/* Octo SPI */
	SNOR_CMD_READ_1_1_8,
	SNOR_CMD_READ_1_8_8,
	SNOR_CMD_READ_8_8_8,
	SNOR_CMD_READ_1_8_8_DTR,

	SNOR_CMD_READ_MAX
};

enum spi_nor_pp_command_index {
	SNOR_CMD_PP,

	/* Quad SPI */
	SNOR_CMD_PP_1_1_4,
	SNOR_CMD_PP_1_4_4,
	SNOR_CMD_PP_4_4_4,

	/* Octo SPI */
	SNOR_CMD_PP_1_1_8,
	SNOR_CMD_PP_1_8_8,
	SNOR_CMD_PP_8_8_8,

	SNOR_CMD_PP_MAX
};

struct spi_nor_flash_parameter {
	u64				size;
	u32				page_size;

	struct spi_nor_hwcaps		hwcaps;
	struct spi_nor_read_command	reads[SNOR_CMD_READ_MAX];
	struct spi_nor_pp_command	page_programs[SNOR_CMD_PP_MAX];

	int (*quad_enable)(struct spi_nor *nor);
};

static void
spi_nor_set_read_settings(struct spi_nor_read_command *read,
			  u8 num_mode_clocks,
			  u8 num_wait_states,
			  u8 opcode,
			  enum spi_nor_protocol proto)
{
	read->num_mode_clocks = num_mode_clocks;
	read->num_wait_states = num_wait_states;
	read->opcode = opcode;
	read->proto = proto;
}

static void
spi_nor_set_pp_settings(struct spi_nor_pp_command *pp,
			u8 opcode,
			enum spi_nor_protocol proto)
{
	pp->opcode = opcode;
	pp->proto = proto;
}

#if CONFIG_IS_ENABLED(SPI_FLASH_SFDP_SUPPORT)
/*
 * Serial Flash Discoverable Parameters (SFDP) parsing.
 */

/**
 * spi_nor_read_sfdp() - read Serial Flash Discoverable Parameters.
 * @nor:	pointer to a 'struct spi_nor'
 * @addr:	offset in the SFDP area to start reading data from
 * @len:	number of bytes to read
 * @buf:	buffer where the SFDP data are copied into (dma-safe memory)
 *
 * Whatever the actual numbers of bytes for address and dummy cycles are
 * for (Fast) Read commands, the Read SFDP (5Ah) instruction is always
 * followed by a 3-byte address and 8 dummy clock cycles.
 *
 * Return: 0 on success, -errno otherwise.
 */
static int spi_nor_read_sfdp(struct spi_nor *nor, u32 addr,
			     size_t len, void *buf)
{
	u8 addr_width, read_opcode, read_dummy;
	int ret;

	read_opcode = nor->read_opcode;
	addr_width = nor->addr_width;
	read_dummy = nor->read_dummy;

	nor->read_opcode = SPINOR_OP_RDSFDP;
	nor->addr_width = 3;
	nor->read_dummy = 8;

	while (len) {
		ret = nor->read(nor, addr, len, (u8 *)buf);
		if (!ret || ret > len) {
			ret = -EIO;
			goto read_err;
		}
		if (ret < 0)
			goto read_err;

		buf += ret;
		addr += ret;
		len -= ret;
	}
	ret = 0;

read_err:
	nor->read_opcode = read_opcode;
	nor->addr_width = addr_width;
	nor->read_dummy = read_dummy;

	return ret;
}

struct sfdp_parameter_header {
	u8		id_lsb;
	u8		minor;
	u8		major;
	u8		length; /* in double words */
	u8		parameter_table_pointer[3]; /* byte address */
	u8		id_msb;
};

#define SFDP_PARAM_HEADER_ID(p)	(((p)->id_msb << 8) | (p)->id_lsb)
#define SFDP_PARAM_HEADER_PTP(p) \
	(((p)->parameter_table_pointer[2] << 16) | \
	 ((p)->parameter_table_pointer[1] <<  8) | \
	 ((p)->parameter_table_pointer[0] <<  0))

#define SFDP_BFPT_ID		0xff00	/* Basic Flash Parameter Table */
#define SFDP_SECTOR_MAP_ID	0xff81	/* Sector Map Table */

#define SFDP_SIGNATURE		0x50444653U
#define SFDP_JESD216_MAJOR	1
#define SFDP_JESD216_MINOR	0
#define SFDP_JESD216A_MINOR	5
#define SFDP_JESD216B_MINOR	6

struct sfdp_header {
	u32		signature; /* Ox50444653U <=> "SFDP" */
	u8		minor;
	u8		major;
	u8		nph; /* 0-base number of parameter headers */
	u8		unused;

	/* Basic Flash Parameter Table. */
	struct sfdp_parameter_header	bfpt_header;
};

/* Basic Flash Parameter Table */

/*
 * JESD216 rev B defines a Basic Flash Parameter Table of 16 DWORDs.
 * They are indexed from 1 but C arrays are indexed from 0.
 */
#define BFPT_DWORD(i)		((i) - 1)
#define BFPT_DWORD_MAX		16

/* The first version of JESB216 defined only 9 DWORDs. */
#define BFPT_DWORD_MAX_JESD216			9

/* 1st DWORD. */
#define BFPT_DWORD1_FAST_READ_1_1_2		BIT(16)
#define BFPT_DWORD1_ADDRESS_BYTES_MASK		GENMASK(18, 17)
#define BFPT_DWORD1_ADDRESS_BYTES_3_ONLY	(0x0UL << 17)
#define BFPT_DWORD1_ADDRESS_BYTES_3_OR_4	(0x1UL << 17)
#define BFPT_DWORD1_ADDRESS_BYTES_4_ONLY	(0x2UL << 17)
#define BFPT_DWORD1_DTR				BIT(19)
#define BFPT_DWORD1_FAST_READ_1_2_2		BIT(20)
#define BFPT_DWORD1_FAST_READ_1_4_4		BIT(21)
#define BFPT_DWORD1_FAST_READ_1_1_4		BIT(22)

/* 5th DWORD. */
#define BFPT_DWORD5_FAST_READ_2_2_2		BIT(0)
#define BFPT_DWORD5_FAST_READ_4_4_4		BIT(4)

/* 11th DWORD. */
#define BFPT_DWORD11_PAGE_SIZE_SHIFT		4
#define BFPT_DWORD11_PAGE_SIZE_MASK		GENMASK(7, 4)

/* 15th DWORD. */

/*
 * (from JESD216 rev B)
 * Quad Enable Requirements (QER):
 * - 000b: Device does not have a QE bit. Device detects 1-1-4 and 1-4-4
 *         reads based on instruction. DQ3/HOLD# functions are hold during
 *         instruction phase.
 * - 001b: QE is bit 1 of status register 2. It is set via Write Status with
 *         two data bytes where bit 1 of the second byte is one.
 *         [...]
 *         Writing only one byte to the status register has the side-effect of
 *         clearing status register 2, including the QE bit. The 100b code is
 *         used if writing one byte to the status register does not modify
 *         status register 2.
 * - 010b: QE is bit 6 of status register 1. It is set via Write Status with
 *         one data byte where bit 6 is one.
 *         [...]
 * - 011b: QE is bit 7 of status register 2. It is set via Write status
 *         register 2 instruction 3Eh with one data byte where bit 7 is one.
 *         [...]
 *         The status register 2 is read using instruction 3Fh.
 * - 100b: QE is bit 1 of status register 2. It is set via Write Status with
 *         two data bytes where bit 1 of the second byte is one.
 *         [...]
 *         In contrast to the 001b code, writing one byte to the status
 *         register does not modify status register 2.
 * - 101b: QE is bit 1 of status register 2. Status register 1 is read using
 *         Read Status instruction 05h. Status register2 is read using
 *         instruction 35h. QE is set via Writ Status instruction 01h with
 *         two data bytes where bit 1 of the second byte is one.
 *         [...]
 */
#define BFPT_DWORD15_QER_MASK			GENMASK(22, 20)
#define BFPT_DWORD15_QER_NONE			(0x0UL << 20) /* Micron */
#define BFPT_DWORD15_QER_SR2_BIT1_BUGGY		(0x1UL << 20)
#define BFPT_DWORD15_QER_SR1_BIT6		(0x2UL << 20) /* Macronix */
#define BFPT_DWORD15_QER_SR2_BIT7		(0x3UL << 20)
#define BFPT_DWORD15_QER_SR2_BIT1_NO_RD		(0x4UL << 20)
#define BFPT_DWORD15_QER_SR2_BIT1		(0x5UL << 20) /* Spansion */

struct sfdp_bfpt {
	u32	dwords[BFPT_DWORD_MAX];
};

/* Fast Read settings. */

static void
spi_nor_set_read_settings_from_bfpt(struct spi_nor_read_command *read,
				    u16 half,
				    enum spi_nor_protocol proto)
{
	read->num_mode_clocks = (half >> 5) & 0x07;
	read->num_wait_states = (half >> 0) & 0x1f;
	read->opcode = (half >> 8) & 0xff;
	read->proto = proto;
}

struct sfdp_bfpt_read {
	/* The Fast Read x-y-z hardware capability in params->hwcaps.mask. */
	u32			hwcaps;

	/*
	 * The <supported_bit> bit in <supported_dword> BFPT DWORD tells us
	 * whether the Fast Read x-y-z command is supported.
	 */
	u32			supported_dword;
	u32			supported_bit;

	/*
	 * The half-word at offset <setting_shift> in <setting_dword> BFPT DWORD
	 * encodes the op code, the number of mode clocks and the number of wait
	 * states to be used by Fast Read x-y-z command.
	 */
	u32			settings_dword;
	u32			settings_shift;

	/* The SPI protocol for this Fast Read x-y-z command. */
	enum spi_nor_protocol	proto;
};

static const struct sfdp_bfpt_read sfdp_bfpt_reads[] = {
	/* Fast Read 1-1-2 */
	{
		SNOR_HWCAPS_READ_1_1_2,
		BFPT_DWORD(1), BIT(16),	/* Supported bit */
		BFPT_DWORD(4), 0,	/* Settings */
		SNOR_PROTO_1_1_2,
	},

	/* Fast Read 1-2-2 */
	{
		SNOR_HWCAPS_READ_1_2_2,
		BFPT_DWORD(1), BIT(20),	/* Supported bit */
		BFPT_DWORD(4), 16,	/* Settings */
		SNOR_PROTO_1_2_2,
	},

	/* Fast Read 2-2-2 */
	{
		SNOR_HWCAPS_READ_2_2_2,
		BFPT_DWORD(5),  BIT(0),	/* Supported bit */
		BFPT_DWORD(6), 16,	/* Settings */
		SNOR_PROTO_2_2_2,
	},

	/* Fast Read 1-1-4 */
	{
		SNOR_HWCAPS_READ_1_1_4,
		BFPT_DWORD(1), BIT(22),	/* Supported bit */
		BFPT_DWORD(3), 16,	/* Settings */
		SNOR_PROTO_1_1_4,
	},

	/* Fast Read 1-4-4 */
	{
		SNOR_HWCAPS_READ_1_4_4,
		BFPT_DWORD(1), BIT(21),	/* Supported bit */
		BFPT_DWORD(3), 0,	/* Settings */
		SNOR_PROTO_1_4_4,
	},

	/* Fast Read 4-4-4 */
	{
		SNOR_HWCAPS_READ_4_4_4,
		BFPT_DWORD(5), BIT(4),	/* Supported bit */
		BFPT_DWORD(7), 16,	/* Settings */
		SNOR_PROTO_4_4_4,
	},
};

struct sfdp_bfpt_erase {
	/*
	 * The half-word at offset <shift> in DWORD <dwoard> encodes the
	 * op code and erase sector size to be used by Sector Erase commands.
	 */
	u32			dword;
	u32			shift;
};

static const struct sfdp_bfpt_erase sfdp_bfpt_erases[] = {
	/* Erase Type 1 in DWORD8 bits[15:0] */
	{BFPT_DWORD(8), 0},

	/* Erase Type 2 in DWORD8 bits[31:16] */
	{BFPT_DWORD(8), 16},

	/* Erase Type 3 in DWORD9 bits[15:0] */
	{BFPT_DWORD(9), 0},

	/* Erase Type 4 in DWORD9 bits[31:16] */
	{BFPT_DWORD(9), 16},
};

static int spi_nor_hwcaps_read2cmd(u32 hwcaps);

/**
 * spi_nor_parse_bfpt() - read and parse the Basic Flash Parameter Table.
 * @nor:		pointer to a 'struct spi_nor'
 * @bfpt_header:	pointer to the 'struct sfdp_parameter_header' describing
 *			the Basic Flash Parameter Table length and version
 * @params:		pointer to the 'struct spi_nor_flash_parameter' to be
 *			filled
 *
 * The Basic Flash Parameter Table is the main and only mandatory table as
 * defined by the SFDP (JESD216) specification.
 * It provides us with the total size (memory density) of the data array and
 * the number of address bytes for Fast Read, Page Program and Sector Erase
 * commands.
 * For Fast READ commands, it also gives the number of mode clock cycles and
 * wait states (regrouped in the number of dummy clock cycles) for each
 * supported instruction op code.
 * For Page Program, the page size is now available since JESD216 rev A, however
 * the supported instruction op codes are still not provided.
 * For Sector Erase commands, this table stores the supported instruction op
 * codes and the associated sector sizes.
 * Finally, the Quad Enable Requirements (QER) are also available since JESD216
 * rev A. The QER bits encode the manufacturer dependent procedure to be
 * executed to set the Quad Enable (QE) bit in some internal register of the
 * Quad SPI memory. Indeed the QE bit, when it exists, must be set before
 * sending any Quad SPI command to the memory. Actually, setting the QE bit
 * tells the memory to reassign its WP# and HOLD#/RESET# pins to functions IO2
 * and IO3 hence enabling 4 (Quad) I/O lines.
 *
 * Return: 0 on success, -errno otherwise.
 */
static int spi_nor_parse_bfpt(struct spi_nor *nor,
			      const struct sfdp_parameter_header *bfpt_header,
			      struct spi_nor_flash_parameter *params)
{
	struct mtd_info *mtd = &nor->mtd;
	struct sfdp_bfpt bfpt;
	size_t len;
	int i, cmd, err;
	u32 addr;
	u16 half;

	/* JESD216 Basic Flash Parameter Table length is at least 9 DWORDs. */
	if (bfpt_header->length < BFPT_DWORD_MAX_JESD216)
		return -EINVAL;

	/* Read the Basic Flash Parameter Table. */
	len = min_t(size_t, sizeof(bfpt),
		    bfpt_header->length * sizeof(u32));
	addr = SFDP_PARAM_HEADER_PTP(bfpt_header);
	memset(&bfpt, 0, sizeof(bfpt));
	err = spi_nor_read_sfdp(nor,  addr, len, &bfpt);
	if (err < 0)
		return err;

	/* Fix endianness of the BFPT DWORDs. */
	for (i = 0; i < BFPT_DWORD_MAX; i++)
		bfpt.dwords[i] = le32_to_cpu(bfpt.dwords[i]);

	/* Number of address bytes. */
	switch (bfpt.dwords[BFPT_DWORD(1)] & BFPT_DWORD1_ADDRESS_BYTES_MASK) {
	case BFPT_DWORD1_ADDRESS_BYTES_3_ONLY:
		nor->addr_width = 3;
		break;

	case BFPT_DWORD1_ADDRESS_BYTES_4_ONLY:
		nor->addr_width = 4;
		break;

	default:
		break;
	}

	/* Flash Memory Density (in bits). */
	params->size = bfpt.dwords[BFPT_DWORD(2)];
	if (params->size & BIT(31)) {
		params->size &= ~BIT(31);

		/*
		 * Prevent overflows on params->size. Anyway, a NOR of 2^64
		 * bits is unlikely to exist so this error probably means
		 * the BFPT we are reading is corrupted/wrong.
		 */
		if (params->size > 63)
			return -EINVAL;

		params->size = 1ULL << params->size;
	} else {
		params->size++;
	}
	params->size >>= 3; /* Convert to bytes. */

	/* Fast Read settings. */
	for (i = 0; i < ARRAY_SIZE(sfdp_bfpt_reads); i++) {
		const struct sfdp_bfpt_read *rd = &sfdp_bfpt_reads[i];
		struct spi_nor_read_command *read;

		if (!(bfpt.dwords[rd->supported_dword] & rd->supported_bit)) {
			params->hwcaps.mask &= ~rd->hwcaps;
			continue;
		}

		params->hwcaps.mask |= rd->hwcaps;
		cmd = spi_nor_hwcaps_read2cmd(rd->hwcaps);
		read = &params->reads[cmd];
		half = bfpt.dwords[rd->settings_dword] >> rd->settings_shift;
		spi_nor_set_read_settings_from_bfpt(read, half, rd->proto);
	}

	/* Sector Erase settings. */
	for (i = 0; i < ARRAY_SIZE(sfdp_bfpt_erases); i++) {
		const struct sfdp_bfpt_erase *er = &sfdp_bfpt_erases[i];
		u32 erasesize;
		u8 opcode;

		half = bfpt.dwords[er->dword] >> er->shift;
		erasesize = half & 0xff;

		/* erasesize == 0 means this Erase Type is not supported. */
		if (!erasesize)
			continue;

		erasesize = 1U << erasesize;
		opcode = (half >> 8) & 0xff;
#ifdef CONFIG_SPI_FLASH_USE_4K_SECTORS
		if (erasesize == SZ_4K) {
			nor->erase_opcode = opcode;
			mtd->erasesize = erasesize;
			break;
		}
#endif
		if (!mtd->erasesize || mtd->erasesize < erasesize) {
			nor->erase_opcode = opcode;
			mtd->erasesize = erasesize;
		}
	}

	/* Stop here if not JESD216 rev A or later. */
	if (bfpt_header->length < BFPT_DWORD_MAX)
		return 0;

	/* Page size: this field specifies 'N' so the page size = 2^N bytes. */
	params->page_size = bfpt.dwords[BFPT_DWORD(11)];
	params->page_size &= BFPT_DWORD11_PAGE_SIZE_MASK;
	params->page_size >>= BFPT_DWORD11_PAGE_SIZE_SHIFT;
	params->page_size = 1U << params->page_size;

	/* Quad Enable Requirements. */
	switch (bfpt.dwords[BFPT_DWORD(15)] & BFPT_DWORD15_QER_MASK) {
	case BFPT_DWORD15_QER_NONE:
		params->quad_enable = NULL;
		break;
#if defined(CONFIG_SPI_FLASH_SPANSION) || defined(CONFIG_SPI_FLASH_WINBOND)
	case BFPT_DWORD15_QER_SR2_BIT1_BUGGY:
	case BFPT_DWORD15_QER_SR2_BIT1_NO_RD:
		params->quad_enable = spansion_no_read_cr_quad_enable;
		break;
#endif
#ifdef CONFIG_SPI_FLASH_MACRONIX
	case BFPT_DWORD15_QER_SR1_BIT6:
		params->quad_enable = macronix_quad_enable;
		break;
#endif
#if defined(CONFIG_SPI_FLASH_SPANSION) || defined(CONFIG_SPI_FLASH_WINBOND)
	case BFPT_DWORD15_QER_SR2_BIT1:
		params->quad_enable = spansion_read_cr_quad_enable;
		break;
#endif
	default:
		return -EINVAL;
	}

	return 0;
}

/**
 * spi_nor_parse_sfdp() - parse the Serial Flash Discoverable Parameters.
 * @nor:		pointer to a 'struct spi_nor'
 * @params:		pointer to the 'struct spi_nor_flash_parameter' to be
 *			filled
 *
 * The Serial Flash Discoverable Parameters are described by the JEDEC JESD216
 * specification. This is a standard which tends to supported by almost all
 * (Q)SPI memory manufacturers. Those hard-coded tables allow us to learn at
 * runtime the main parameters needed to perform basic SPI flash operations such
 * as Fast Read, Page Program or Sector Erase commands.
 *
 * Return: 0 on success, -errno otherwise.
 */
static int spi_nor_parse_sfdp(struct spi_nor *nor,
			      struct spi_nor_flash_parameter *params)
{
	const struct sfdp_parameter_header *param_header, *bfpt_header;
	struct sfdp_parameter_header *param_headers = NULL;
	struct sfdp_header header;
	size_t psize;
	int i, err;

	/* Get the SFDP header. */
	err = spi_nor_read_sfdp(nor, 0, sizeof(header), &header);
	if (err < 0)
		return err;

	/* Check the SFDP header version. */
	if (le32_to_cpu(header.signature) != SFDP_SIGNATURE ||
	    header.major != SFDP_JESD216_MAJOR)
		return -EINVAL;

	/*
	 * Verify that the first and only mandatory parameter header is a
	 * Basic Flash Parameter Table header as specified in JESD216.
	 */
	bfpt_header = &header.bfpt_header;
	if (SFDP_PARAM_HEADER_ID(bfpt_header) != SFDP_BFPT_ID ||
	    bfpt_header->major != SFDP_JESD216_MAJOR)
		return -EINVAL;

	/*
	 * Allocate memory then read all parameter headers with a single
	 * Read SFDP command. These parameter headers will actually be parsed
	 * twice: a first time to get the latest revision of the basic flash
	 * parameter table, then a second time to handle the supported optional
	 * tables.
	 * Hence we read the parameter headers once for all to reduce the
	 * processing time. Also we use kmalloc() instead of devm_kmalloc()
	 * because we don't need to keep these parameter headers: the allocated
	 * memory is always released with kfree() before exiting this function.
	 */
	if (header.nph) {
		psize = header.nph * sizeof(*param_headers);

		param_headers = kmalloc(psize, GFP_KERNEL);
		if (!param_headers)
			return -ENOMEM;

		err = spi_nor_read_sfdp(nor, sizeof(header),
					psize, param_headers);
		if (err < 0) {
			dev_err(dev, "failed to read SFDP parameter headers\n");
			goto exit;
		}
	}

	/*
	 * Check other parameter headers to get the latest revision of
	 * the basic flash parameter table.
	 */
	for (i = 0; i < header.nph; i++) {
		param_header = &param_headers[i];

		if (SFDP_PARAM_HEADER_ID(param_header) == SFDP_BFPT_ID &&
		    param_header->major == SFDP_JESD216_MAJOR &&
		    (param_header->minor > bfpt_header->minor ||
		     (param_header->minor == bfpt_header->minor &&
		      param_header->length > bfpt_header->length)))
			bfpt_header = param_header;
	}

	err = spi_nor_parse_bfpt(nor, bfpt_header, params);
	if (err)
		goto exit;

	/* Parse other parameter headers. */
	for (i = 0; i < header.nph; i++) {
		param_header = &param_headers[i];

		switch (SFDP_PARAM_HEADER_ID(param_header)) {
		case SFDP_SECTOR_MAP_ID:
			dev_info(dev, "non-uniform erase sector maps are not supported yet.\n");
			break;

		default:
			break;
		}

		if (err)
			goto exit;
	}

exit:
	kfree(param_headers);
	return err;
}
#else
static int spi_nor_parse_sfdp(struct spi_nor *nor,
			      struct spi_nor_flash_parameter *params)
{
	return -EINVAL;
}
#endif /* SPI_FLASH_SFDP_SUPPORT */

static int spi_nor_init_params(struct spi_nor *nor,
			       const struct flash_info *info,
			       struct spi_nor_flash_parameter *params)
{
	/* Set legacy flash parameters as default. */
	memset(params, 0, sizeof(*params));

	/* Set SPI NOR sizes. */
	params->size = info->sector_size * info->n_sectors;
	params->page_size = info->page_size;

	/* (Fast) Read settings. */
	params->hwcaps.mask |= SNOR_HWCAPS_READ;
	spi_nor_set_read_settings(&params->reads[SNOR_CMD_READ],
				  0, 0, SPINOR_OP_READ,
				  SNOR_PROTO_1_1_1);

	if (!(info->flags & SPI_NOR_NO_FR)) {
		params->hwcaps.mask |= SNOR_HWCAPS_READ_FAST;
		spi_nor_set_read_settings(&params->reads[SNOR_CMD_READ_FAST],
					  0, 8, SPINOR_OP_READ_FAST,
					  SNOR_PROTO_1_1_1);
	}

	if (info->flags & SPI_NOR_DUAL_READ) {
		params->hwcaps.mask |= SNOR_HWCAPS_READ_1_1_2;
		spi_nor_set_read_settings(&params->reads[SNOR_CMD_READ_1_1_2],
					  0, 8, SPINOR_OP_READ_1_1_2,
					  SNOR_PROTO_1_1_2);
	}

	if (info->flags & SPI_NOR_QUAD_READ) {
		params->hwcaps.mask |= SNOR_HWCAPS_READ_1_1_4;
		spi_nor_set_read_settings(&params->reads[SNOR_CMD_READ_1_1_4],
					  0, 8, SPINOR_OP_READ_1_1_4,
					  SNOR_PROTO_1_1_4);
	}

	if (info->flags & SPI_NOR_OCTAL_READ) {
		params->hwcaps.mask |= SNOR_HWCAPS_READ_1_1_8;
		spi_nor_set_read_settings(&params->reads[SNOR_CMD_READ_1_1_8],
					  0, 8, SPINOR_OP_READ_1_1_8,
					  SNOR_PROTO_1_1_8);
	}

	/* Page Program settings. */
	params->hwcaps.mask |= SNOR_HWCAPS_PP;
	spi_nor_set_pp_settings(&params->page_programs[SNOR_CMD_PP],
				SPINOR_OP_PP, SNOR_PROTO_1_1_1);

	if (info->flags & SPI_NOR_QUAD_READ) {
		params->hwcaps.mask |= SNOR_HWCAPS_PP_1_1_4;
		spi_nor_set_pp_settings(&params->page_programs[SNOR_CMD_PP_1_1_4],
					SPINOR_OP_PP_1_1_4, SNOR_PROTO_1_1_4);
	}

	/* Select the procedure to set the Quad Enable bit. */
	if (params->hwcaps.mask & (SNOR_HWCAPS_READ_QUAD |
				   SNOR_HWCAPS_PP_QUAD)) {
		switch (JEDEC_MFR(info)) {
#ifdef CONFIG_SPI_FLASH_MACRONIX
		case SNOR_MFR_MACRONIX:
			params->quad_enable = macronix_quad_enable;
			break;
#endif
		case SNOR_MFR_ST:
		case SNOR_MFR_MICRON:
			break;

		default:
#if defined(CONFIG_SPI_FLASH_SPANSION) || defined(CONFIG_SPI_FLASH_WINBOND)
			/* Kept only for backward compatibility purpose. */
			params->quad_enable = spansion_read_cr_quad_enable;
#endif
			break;
		}
	}

	/* Override the parameters with data read from SFDP tables. */
	nor->addr_width = 0;
	nor->mtd.erasesize = 0;
	if ((info->flags & (SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ)) &&
	    !(info->flags & SPI_NOR_SKIP_SFDP)) {
		struct spi_nor_flash_parameter sfdp_params;

		memcpy(&sfdp_params, params, sizeof(sfdp_params));
		if (spi_nor_parse_sfdp(nor, &sfdp_params)) {
			nor->addr_width = 0;
			nor->mtd.erasesize = 0;
		} else {
			memcpy(params, &sfdp_params, sizeof(*params));
		}
	}

	return 0;
}

static int spi_nor_hwcaps2cmd(u32 hwcaps, const int table[][2], size_t size)
{
	size_t i;

	for (i = 0; i < size; i++)
		if (table[i][0] == (int)hwcaps)
			return table[i][1];

	return -EINVAL;
}

static int spi_nor_hwcaps_read2cmd(u32 hwcaps)
{
	static const int hwcaps_read2cmd[][2] = {
		{ SNOR_HWCAPS_READ,		SNOR_CMD_READ },
		{ SNOR_HWCAPS_READ_FAST,	SNOR_CMD_READ_FAST },
		{ SNOR_HWCAPS_READ_1_1_1_DTR,	SNOR_CMD_READ_1_1_1_DTR },
		{ SNOR_HWCAPS_READ_1_1_2,	SNOR_CMD_READ_1_1_2 },
		{ SNOR_HWCAPS_READ_1_2_2,	SNOR_CMD_READ_1_2_2 },
		{ SNOR_HWCAPS_READ_2_2_2,	SNOR_CMD_READ_2_2_2 },
		{ SNOR_HWCAPS_READ_1_2_2_DTR,	SNOR_CMD_READ_1_2_2_DTR },
		{ SNOR_HWCAPS_READ_1_1_4,	SNOR_CMD_READ_1_1_4 },
		{ SNOR_HWCAPS_READ_1_4_4,	SNOR_CMD_READ_1_4_4 },
		{ SNOR_HWCAPS_READ_4_4_4,	SNOR_CMD_READ_4_4_4 },
		{ SNOR_HWCAPS_READ_1_4_4_DTR,	SNOR_CMD_READ_1_4_4_DTR },
		{ SNOR_HWCAPS_READ_1_1_8,	SNOR_CMD_READ_1_1_8 },
		{ SNOR_HWCAPS_READ_1_8_8,	SNOR_CMD_READ_1_8_8 },
		{ SNOR_HWCAPS_READ_8_8_8,	SNOR_CMD_READ_8_8_8 },
		{ SNOR_HWCAPS_READ_1_8_8_DTR,	SNOR_CMD_READ_1_8_8_DTR },
	};

	return spi_nor_hwcaps2cmd(hwcaps, hwcaps_read2cmd,
				  ARRAY_SIZE(hwcaps_read2cmd));
}

static int spi_nor_hwcaps_pp2cmd(u32 hwcaps)
{
	static const int hwcaps_pp2cmd[][2] = {
		{ SNOR_HWCAPS_PP,		SNOR_CMD_PP },
		{ SNOR_HWCAPS_PP_1_1_4,		SNOR_CMD_PP_1_1_4 },
		{ SNOR_HWCAPS_PP_1_4_4,		SNOR_CMD_PP_1_4_4 },
		{ SNOR_HWCAPS_PP_4_4_4,		SNOR_CMD_PP_4_4_4 },
		{ SNOR_HWCAPS_PP_1_1_8,		SNOR_CMD_PP_1_1_8 },
		{ SNOR_HWCAPS_PP_1_8_8,		SNOR_CMD_PP_1_8_8 },
		{ SNOR_HWCAPS_PP_8_8_8,		SNOR_CMD_PP_8_8_8 },
	};

	return spi_nor_hwcaps2cmd(hwcaps, hwcaps_pp2cmd,
				  ARRAY_SIZE(hwcaps_pp2cmd));
}

static int spi_nor_select_read(struct spi_nor *nor,
			       const struct spi_nor_flash_parameter *params,
			       u32 shared_hwcaps)
{
	int cmd, best_match = fls(shared_hwcaps & SNOR_HWCAPS_READ_MASK) - 1;
	const struct spi_nor_read_command *read;

	if (best_match < 0)
		return -EINVAL;

	cmd = spi_nor_hwcaps_read2cmd(BIT(best_match));
	if (cmd < 0)
		return -EINVAL;

	read = &params->reads[cmd];
	nor->read_opcode = read->opcode;
	nor->read_proto = read->proto;

	/*
	 * In the spi-nor framework, we don't need to make the difference
	 * between mode clock cycles and wait state clock cycles.
	 * Indeed, the value of the mode clock cycles is used by a QSPI
	 * flash memory to know whether it should enter or leave its 0-4-4
	 * (Continuous Read / XIP) mode.
	 * eXecution In Place is out of the scope of the mtd sub-system.
	 * Hence we choose to merge both mode and wait state clock cycles
	 * into the so called dummy clock cycles.
	 */
	nor->read_dummy = read->num_mode_clocks + read->num_wait_states;
	return 0;
}

static int spi_nor_select_pp(struct spi_nor *nor,
			     const struct spi_nor_flash_parameter *params,
			     u32 shared_hwcaps)
{
	int cmd, best_match = fls(shared_hwcaps & SNOR_HWCAPS_PP_MASK) - 1;
	const struct spi_nor_pp_command *pp;

	if (best_match < 0)
		return -EINVAL;

	cmd = spi_nor_hwcaps_pp2cmd(BIT(best_match));
	if (cmd < 0)
		return -EINVAL;

	pp = &params->page_programs[cmd];
	nor->program_opcode = pp->opcode;
	nor->write_proto = pp->proto;
	return 0;
}

static int spi_nor_select_erase(struct spi_nor *nor,
				const struct flash_info *info)
{
	struct mtd_info *mtd = &nor->mtd;

	/* Do nothing if already configured from SFDP. */
	if (mtd->erasesize)
		return 0;

#ifdef CONFIG_SPI_FLASH_USE_4K_SECTORS
	/* prefer "small sector" erase if possible */
	if (info->flags & SECT_4K) {
		nor->erase_opcode = SPINOR_OP_BE_4K;
		mtd->erasesize = 4096;
	} else if (info->flags & SECT_4K_PMC) {
		nor->erase_opcode = SPINOR_OP_BE_4K_PMC;
		mtd->erasesize = 4096;
	} else
#endif
	{
		nor->erase_opcode = SPINOR_OP_SE;
		mtd->erasesize = info->sector_size;
	}
	return 0;
}

static int spi_nor_setup(struct spi_nor *nor, const struct flash_info *info,
			 const struct spi_nor_flash_parameter *params,
			 const struct spi_nor_hwcaps *hwcaps)
{
	u32 ignored_mask, shared_mask;
	bool enable_quad_io;
	int err;

	/*
	 * Keep only the hardware capabilities supported by both the SPI
	 * controller and the SPI flash memory.
	 */
	shared_mask = hwcaps->mask & params->hwcaps.mask;

	/* SPI n-n-n protocols are not supported yet. */
	ignored_mask = (SNOR_HWCAPS_READ_2_2_2 |
			SNOR_HWCAPS_READ_4_4_4 |
			SNOR_HWCAPS_READ_8_8_8 |
			SNOR_HWCAPS_PP_4_4_4 |
			SNOR_HWCAPS_PP_8_8_8);
	if (shared_mask & ignored_mask) {
		dev_dbg(nor->dev,
			"SPI n-n-n protocols are not supported yet.\n");
		shared_mask &= ~ignored_mask;
	}

	/* Select the (Fast) Read command. */
	err = spi_nor_select_read(nor, params, shared_mask);
	if (err) {
		dev_dbg(nor->dev,
			"can't select read settings supported by both the SPI controller and memory.\n");
		return err;
	}

	/* Select the Page Program command. */
	err = spi_nor_select_pp(nor, params, shared_mask);
	if (err) {
		dev_dbg(nor->dev,
			"can't select write settings supported by both the SPI controller and memory.\n");
		return err;
	}

	/* Select the Sector Erase command. */
	err = spi_nor_select_erase(nor, info);
	if (err) {
		dev_dbg(nor->dev,
			"can't select erase settings supported by both the SPI controller and memory.\n");
		return err;
	}

	/* Enable Quad I/O if needed. */
	enable_quad_io = (spi_nor_get_protocol_width(nor->read_proto) == 4 ||
			  spi_nor_get_protocol_width(nor->write_proto) == 4);
	if (enable_quad_io && params->quad_enable)
		nor->quad_enable = params->quad_enable;
	else
		nor->quad_enable = NULL;

	return 0;
}

static int spi_nor_init(struct spi_nor *nor)
{
	int err;

	/*
	 * Atmel, SST, Intel/Numonyx, and others serial NOR tend to power up
	 * with the software protection bits set
	 */
	if (JEDEC_MFR(nor->info) == SNOR_MFR_ATMEL ||
	    JEDEC_MFR(nor->info) == SNOR_MFR_INTEL ||
	    JEDEC_MFR(nor->info) == SNOR_MFR_SST ||
	    nor->info->flags & SPI_NOR_HAS_LOCK) {
		write_enable(nor);
		write_sr(nor, 0);
		spi_nor_wait_till_ready(nor);
	}

	if (nor->quad_enable) {
		err = nor->quad_enable(nor);
		if (err) {
			dev_dbg(nor->dev, "quad mode not supported\n");
			return err;
		}
	}

	if (nor->addr_width == 4 &&
	    (JEDEC_MFR(nor->info) != SNOR_MFR_SPANSION) &&
	    !(nor->info->flags & SPI_NOR_4B_OPCODES)) {
		/*
		 * If the RESET# pin isn't hooked up properly, or the system
		 * otherwise doesn't perform a reset command in the boot
		 * sequence, it's impossible to 100% protect against unexpected
		 * reboots (e.g., crashes). Warn the user (or hopefully, system
		 * designer) that this is bad.
		 */
		if (nor->flags & SNOR_F_BROKEN_RESET)
			printf("enabling reset hack; may not recover from unexpected reboots\n");
		set_4byte(nor, nor->info, 1);
	}

	return 0;
}

int spi_nor_scan(struct spi_nor *nor)
{
	struct spi_nor_flash_parameter params;
	const struct flash_info *info = NULL;
	struct mtd_info *mtd = &nor->mtd;
	struct spi_nor_hwcaps hwcaps = {
		.mask = SNOR_HWCAPS_READ |
			SNOR_HWCAPS_READ_FAST |
			SNOR_HWCAPS_PP,
	};
	struct spi_slave *spi = nor->spi;
	int ret;

	/* Reset SPI protocol for all commands. */
	nor->reg_proto = SNOR_PROTO_1_1_1;
	nor->read_proto = SNOR_PROTO_1_1_1;
	nor->write_proto = SNOR_PROTO_1_1_1;
	nor->read = spi_nor_read_data;
	nor->write = spi_nor_write_data;
	nor->read_reg = spi_nor_read_reg;
	nor->write_reg = spi_nor_write_reg;

	if (spi->mode & SPI_RX_OCTAL) {
		hwcaps.mask |= SNOR_HWCAPS_READ_1_1_8;

		if (spi->mode & SPI_TX_OCTAL)
			hwcaps.mask |= (SNOR_HWCAPS_READ_1_8_8 |
					SNOR_HWCAPS_PP_1_1_8 |
					SNOR_HWCAPS_PP_1_8_8);
	} else if (spi->mode & SPI_RX_QUAD) {
		hwcaps.mask |= SNOR_HWCAPS_READ_1_1_4;

		if (spi->mode & SPI_TX_QUAD)
			hwcaps.mask |= (SNOR_HWCAPS_READ_1_4_4 |
					SNOR_HWCAPS_PP_1_1_4 |
					SNOR_HWCAPS_PP_1_4_4);
	} else if (spi->mode & SPI_RX_DUAL) {
		hwcaps.mask |= SNOR_HWCAPS_READ_1_1_2;

		if (spi->mode & SPI_TX_DUAL)
			hwcaps.mask |= SNOR_HWCAPS_READ_1_2_2;
	}

	info = spi_nor_read_id(nor);
	if (IS_ERR_OR_NULL(info))
		return -ENOENT;
	/* Parse the Serial Flash Discoverable Parameters table. */
	ret = spi_nor_init_params(nor, info, &params);
	if (ret)
		return ret;

	if (!mtd->name)
		mtd->name = info->name;
	mtd->priv = nor;
	mtd->type = MTD_NORFLASH;
	mtd->writesize = 1;
	mtd->flags = MTD_CAP_NORFLASH;
	mtd->size = params.size;
	mtd->_erase = spi_nor_erase;
	mtd->_read = spi_nor_read;

#if defined(CONFIG_SPI_FLASH_STMICRO) || defined(CONFIG_SPI_FLASH_SST)
	/* NOR protection support for STmicro/Micron chips and similar */
	if (JEDEC_MFR(info) == SNOR_MFR_ST ||
	    JEDEC_MFR(info) == SNOR_MFR_MICRON ||
	    JEDEC_MFR(info) == SNOR_MFR_SST ||
			info->flags & SPI_NOR_HAS_LOCK) {
		nor->flash_lock = stm_lock;
		nor->flash_unlock = stm_unlock;
		nor->flash_is_locked = stm_is_locked;
	}
#endif

#ifdef CONFIG_SPI_FLASH_SST
	/*
	 * sst26 series block protection implementation differs from other
	 * series.
	 */
	if (info->flags & SPI_NOR_HAS_SST26LOCK) {
		nor->flash_lock = sst26_lock;
		nor->flash_unlock = sst26_unlock;
		nor->flash_is_locked = sst26_is_locked;
	}

	/* sst nor chips use AAI word program */
	if (info->flags & SST_WRITE)
		mtd->_write = sst_write;
	else
#endif
		mtd->_write = spi_nor_write;

	if (info->flags & USE_FSR)
		nor->flags |= SNOR_F_USE_FSR;
	if (info->flags & SPI_NOR_HAS_TB)
		nor->flags |= SNOR_F_HAS_SR_TB;
	if (info->flags & NO_CHIP_ERASE)
		nor->flags |= SNOR_F_NO_OP_CHIP_ERASE;
	if (info->flags & USE_CLSR)
		nor->flags |= SNOR_F_USE_CLSR;

	if (info->flags & SPI_NOR_NO_ERASE)
		mtd->flags |= MTD_NO_ERASE;

	nor->page_size = params.page_size;
	mtd->writebufsize = nor->page_size;

	/* Some devices cannot do fast-read, no matter what DT tells us */
	if ((info->flags & SPI_NOR_NO_FR) || (spi->mode & SPI_RX_SLOW))
		params.hwcaps.mask &= ~SNOR_HWCAPS_READ_FAST;

	/*
	 * Configure the SPI memory:
	 * - select op codes for (Fast) Read, Page Program and Sector Erase.
	 * - set the number of dummy cycles (mode cycles + wait states).
	 * - set the SPI protocols for register and memory accesses.
	 * - set the Quad Enable bit if needed (required by SPI x-y-4 protos).
	 */
	ret = spi_nor_setup(nor, info, &params, &hwcaps);
	if (ret)
		return ret;

	if (nor->addr_width) {
		/* already configured from SFDP */
	} else if (info->addr_width) {
		nor->addr_width = info->addr_width;
	} else if (mtd->size > SZ_16M) {
#ifndef CONFIG_SPI_FLASH_BAR
		/* enable 4-byte addressing if the device exceeds 16MiB */
		nor->addr_width = 4;
		if (JEDEC_MFR(info) == SNOR_MFR_SPANSION ||
		    info->flags & SPI_NOR_4B_OPCODES)
			spi_nor_set_4byte_opcodes(nor, info);
#else
	/* Configure the BAR - discover bank cmds and read current bank */
	nor->addr_width = 3;
	ret = read_bar(nor, info);
	if (ret < 0)
		return ret;
#endif
	} else {
		nor->addr_width = 3;
	}

	if (nor->addr_width > SPI_NOR_MAX_ADDR_WIDTH) {
		dev_dbg(dev, "address width is too large: %u\n",
			nor->addr_width);
		return -EINVAL;
	}

	/* Send all the required SPI flash commands to initialize device */
	nor->info = info;
	ret = spi_nor_init(nor);
	if (ret)
		return ret;

	nor->name = mtd->name;
	nor->size = mtd->size;
	nor->erase_size = mtd->erasesize;
	nor->sector_size = mtd->erasesize;

#ifndef CONFIG_SPL_BUILD
	printf("SF: Detected %s with page size ", nor->name);
	print_size(nor->page_size, ", erase size ");
	print_size(nor->erase_size, ", total ");
	print_size(nor->size, "");
	puts("\n");
#endif

	return 0;
}

/* U-Boot specific functions, need to extend MTD to support these */
int spi_flash_cmd_get_sw_write_prot(struct spi_nor *nor)
{
	int sr = read_sr(nor);

	if (sr < 0)
		return sr;

	return (sr >> 2) & 7;
}
