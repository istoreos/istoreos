/*
 * Freescale i.MX28 NAND flash driver
 *
 * Copyright (C) 2011 Marek Vasut <marek.vasut@gmail.com>
 * on behalf of DENX Software Engineering GmbH
 *
 * Based on code from LTIB:
 * Freescale GPMI NFC NAND Flash Driver
 *
 * Copyright (C) 2010 Freescale Semiconductor, Inc.
 * Copyright (C) 2008 Embedded Alley Solutions, Inc.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <dm.h>
#include <linux/mtd/rawnand.h>
#include <linux/sizes.h>
#include <linux/types.h>
#include <malloc.h>
#include <linux/errno.h>
#include <asm/io.h>
#include <asm/arch/clock.h>
#include <asm/arch/imx-regs.h>
#include <asm/mach-imx/regs-bch.h>
#include <asm/mach-imx/regs-gpmi.h>
#include <asm/arch/sys_proto.h>
#include "mxs_nand.h"

#define	MXS_NAND_DMA_DESCRIPTOR_COUNT		4

#if (defined(CONFIG_MX6) || defined(CONFIG_MX7))
#define	MXS_NAND_CHUNK_DATA_CHUNK_SIZE_SHIFT	2
#else
#define	MXS_NAND_CHUNK_DATA_CHUNK_SIZE_SHIFT	0
#endif
#define	MXS_NAND_METADATA_SIZE			10
#define	MXS_NAND_BITS_PER_ECC_LEVEL		13

#if !defined(CONFIG_SYS_CACHELINE_SIZE) || CONFIG_SYS_CACHELINE_SIZE < 32
#define	MXS_NAND_COMMAND_BUFFER_SIZE		32
#else
#define	MXS_NAND_COMMAND_BUFFER_SIZE		CONFIG_SYS_CACHELINE_SIZE
#endif

#define	MXS_NAND_BCH_TIMEOUT			10000

struct nand_ecclayout fake_ecc_layout;

/*
 * Cache management functions
 */
#ifndef	CONFIG_SYS_DCACHE_OFF
static void mxs_nand_flush_data_buf(struct mxs_nand_info *info)
{
	uint32_t addr = (uint32_t)info->data_buf;

	flush_dcache_range(addr, addr + info->data_buf_size);
}

static void mxs_nand_inval_data_buf(struct mxs_nand_info *info)
{
	uint32_t addr = (uint32_t)info->data_buf;

	invalidate_dcache_range(addr, addr + info->data_buf_size);
}

static void mxs_nand_flush_cmd_buf(struct mxs_nand_info *info)
{
	uint32_t addr = (uint32_t)info->cmd_buf;

	flush_dcache_range(addr, addr + MXS_NAND_COMMAND_BUFFER_SIZE);
}
#else
static inline void mxs_nand_flush_data_buf(struct mxs_nand_info *info) {}
static inline void mxs_nand_inval_data_buf(struct mxs_nand_info *info) {}
static inline void mxs_nand_flush_cmd_buf(struct mxs_nand_info *info) {}
#endif

static struct mxs_dma_desc *mxs_nand_get_dma_desc(struct mxs_nand_info *info)
{
	struct mxs_dma_desc *desc;

	if (info->desc_index >= MXS_NAND_DMA_DESCRIPTOR_COUNT) {
		printf("MXS NAND: Too many DMA descriptors requested\n");
		return NULL;
	}

	desc = info->desc[info->desc_index];
	info->desc_index++;

	return desc;
}

static void mxs_nand_return_dma_descs(struct mxs_nand_info *info)
{
	int i;
	struct mxs_dma_desc *desc;

	for (i = 0; i < info->desc_index; i++) {
		desc = info->desc[i];
		memset(desc, 0, sizeof(struct mxs_dma_desc));
		desc->address = (dma_addr_t)desc;
	}

	info->desc_index = 0;
}

static uint32_t mxs_nand_aux_status_offset(void)
{
	return (MXS_NAND_METADATA_SIZE + 0x3) & ~0x3;
}

static inline int mxs_nand_calc_mark_offset(struct bch_geometry *geo,
					    uint32_t page_data_size)
{
	uint32_t chunk_data_size_in_bits = geo->ecc_chunk_size * 8;
	uint32_t chunk_ecc_size_in_bits = geo->ecc_strength * geo->gf_len;
	uint32_t chunk_total_size_in_bits;
	uint32_t block_mark_chunk_number;
	uint32_t block_mark_chunk_bit_offset;
	uint32_t block_mark_bit_offset;

	chunk_total_size_in_bits =
			chunk_data_size_in_bits + chunk_ecc_size_in_bits;

	/* Compute the bit offset of the block mark within the physical page. */
	block_mark_bit_offset = page_data_size * 8;

	/* Subtract the metadata bits. */
	block_mark_bit_offset -= MXS_NAND_METADATA_SIZE * 8;

	/*
	 * Compute the chunk number (starting at zero) in which the block mark
	 * appears.
	 */
	block_mark_chunk_number =
			block_mark_bit_offset / chunk_total_size_in_bits;

	/*
	 * Compute the bit offset of the block mark within its chunk, and
	 * validate it.
	 */
	block_mark_chunk_bit_offset = block_mark_bit_offset -
			(block_mark_chunk_number * chunk_total_size_in_bits);

	if (block_mark_chunk_bit_offset > chunk_data_size_in_bits)
		return -EINVAL;

	/*
	 * Now that we know the chunk number in which the block mark appears,
	 * we can subtract all the ECC bits that appear before it.
	 */
	block_mark_bit_offset -=
		block_mark_chunk_number * chunk_ecc_size_in_bits;

	geo->block_mark_byte_offset = block_mark_bit_offset >> 3;
	geo->block_mark_bit_offset = block_mark_bit_offset & 0x7;

	return 0;
}

static inline int mxs_nand_calc_ecc_layout_by_info(struct bch_geometry *geo,
						   struct mtd_info *mtd,
						   unsigned int ecc_strength,
						   unsigned int ecc_step)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct mxs_nand_info *nand_info = nand_get_controller_data(chip);

	switch (ecc_step) {
	case SZ_512:
		geo->gf_len = 13;
		break;
	case SZ_1K:
		geo->gf_len = 14;
		break;
	default:
		return -EINVAL;
	}

	geo->ecc_chunk_size = ecc_step;
	geo->ecc_strength = round_up(ecc_strength, 2);

	/* Keep the C >= O */
	if (geo->ecc_chunk_size < mtd->oobsize)
		return -EINVAL;

	if (geo->ecc_strength > nand_info->max_ecc_strength_supported)
		return -EINVAL;

	geo->ecc_chunk_count = mtd->writesize / geo->ecc_chunk_size;

	return 0;
}

static inline int mxs_nand_calc_ecc_layout(struct bch_geometry *geo,
					   struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct mxs_nand_info *nand_info = nand_get_controller_data(chip);

	/* The default for the length of Galois Field. */
	geo->gf_len = 13;

	/* The default for chunk size. */
	geo->ecc_chunk_size = 512;

	if (geo->ecc_chunk_size < mtd->oobsize) {
		geo->gf_len = 14;
		geo->ecc_chunk_size *= 2;
	}

	if (mtd->oobsize > geo->ecc_chunk_size) {
		printf("Not support the NAND chips whose oob size is larger then %d bytes!\n",
		       geo->ecc_chunk_size);
		return -EINVAL;
	}

	geo->ecc_chunk_count = mtd->writesize / geo->ecc_chunk_size;

	/*
	 * Determine the ECC layout with the formula:
	 *	ECC bits per chunk = (total page spare data bits) /
	 *		(bits per ECC level) / (chunks per page)
	 * where:
	 *	total page spare data bits =
	 *		(page oob size - meta data size) * (bits per byte)
	 */
	geo->ecc_strength = ((mtd->oobsize - MXS_NAND_METADATA_SIZE) * 8)
			/ (geo->gf_len * geo->ecc_chunk_count);

	geo->ecc_strength = min(round_down(geo->ecc_strength, 2),
				nand_info->max_ecc_strength_supported);

	return 0;
}

/*
 * Wait for BCH complete IRQ and clear the IRQ
 */
static int mxs_nand_wait_for_bch_complete(struct mxs_nand_info *nand_info)
{
	int timeout = MXS_NAND_BCH_TIMEOUT;
	int ret;

	ret = mxs_wait_mask_set(&nand_info->bch_regs->hw_bch_ctrl_reg,
		BCH_CTRL_COMPLETE_IRQ, timeout);

	writel(BCH_CTRL_COMPLETE_IRQ, &nand_info->bch_regs->hw_bch_ctrl_clr);

	return ret;
}

/*
 * This is the function that we install in the cmd_ctrl function pointer of the
 * owning struct nand_chip. The only functions in the reference implementation
 * that use these functions pointers are cmdfunc and select_chip.
 *
 * In this driver, we implement our own select_chip, so this function will only
 * be called by the reference implementation's cmdfunc. For this reason, we can
 * ignore the chip enable bit and concentrate only on sending bytes to the NAND
 * Flash.
 */
static void mxs_nand_cmd_ctrl(struct mtd_info *mtd, int data, unsigned int ctrl)
{
	struct nand_chip *nand = mtd_to_nand(mtd);
	struct mxs_nand_info *nand_info = nand_get_controller_data(nand);
	struct mxs_dma_desc *d;
	uint32_t channel = MXS_DMA_CHANNEL_AHB_APBH_GPMI0 + nand_info->cur_chip;
	int ret;

	/*
	 * If this condition is true, something is _VERY_ wrong in MTD
	 * subsystem!
	 */
	if (nand_info->cmd_queue_len == MXS_NAND_COMMAND_BUFFER_SIZE) {
		printf("MXS NAND: Command queue too long\n");
		return;
	}

	/*
	 * Every operation begins with a command byte and a series of zero or
	 * more address bytes. These are distinguished by either the Address
	 * Latch Enable (ALE) or Command Latch Enable (CLE) signals being
	 * asserted. When MTD is ready to execute the command, it will
	 * deasert both latch enables.
	 *
	 * Rather than run a separate DMA operation for every single byte, we
	 * queue them up and run a single DMA operation for the entire series
	 * of command and data bytes.
	 */
	if (ctrl & (NAND_ALE | NAND_CLE)) {
		if (data != NAND_CMD_NONE)
			nand_info->cmd_buf[nand_info->cmd_queue_len++] = data;
		return;
	}

	/*
	 * If control arrives here, MTD has deasserted both the ALE and CLE,
	 * which means it's ready to run an operation. Check if we have any
	 * bytes to send.
	 */
	if (nand_info->cmd_queue_len == 0)
		return;

	/* Compile the DMA descriptor -- a descriptor that sends command. */
	d = mxs_nand_get_dma_desc(nand_info);
	d->cmd.data =
		MXS_DMA_DESC_COMMAND_DMA_READ | MXS_DMA_DESC_IRQ |
		MXS_DMA_DESC_CHAIN | MXS_DMA_DESC_DEC_SEM |
		MXS_DMA_DESC_WAIT4END | (3 << MXS_DMA_DESC_PIO_WORDS_OFFSET) |
		(nand_info->cmd_queue_len << MXS_DMA_DESC_BYTES_OFFSET);

	d->cmd.address = (dma_addr_t)nand_info->cmd_buf;

	d->cmd.pio_words[0] =
		GPMI_CTRL0_COMMAND_MODE_WRITE |
		GPMI_CTRL0_WORD_LENGTH |
		(nand_info->cur_chip << GPMI_CTRL0_CS_OFFSET) |
		GPMI_CTRL0_ADDRESS_NAND_CLE |
		GPMI_CTRL0_ADDRESS_INCREMENT |
		nand_info->cmd_queue_len;

	mxs_dma_desc_append(channel, d);

	/* Flush caches */
	mxs_nand_flush_cmd_buf(nand_info);

	/* Execute the DMA chain. */
	ret = mxs_dma_go(channel);
	if (ret)
		printf("MXS NAND: Error sending command\n");

	mxs_nand_return_dma_descs(nand_info);

	/* Reset the command queue. */
	nand_info->cmd_queue_len = 0;
}

/*
 * Test if the NAND flash is ready.
 */
static int mxs_nand_device_ready(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct mxs_nand_info *nand_info = nand_get_controller_data(chip);
	uint32_t tmp;

	tmp = readl(&nand_info->gpmi_regs->hw_gpmi_stat);
	tmp >>= (GPMI_STAT_READY_BUSY_OFFSET + nand_info->cur_chip);

	return tmp & 1;
}

/*
 * Select the NAND chip.
 */
static void mxs_nand_select_chip(struct mtd_info *mtd, int chip)
{
	struct nand_chip *nand = mtd_to_nand(mtd);
	struct mxs_nand_info *nand_info = nand_get_controller_data(nand);

	nand_info->cur_chip = chip;
}

/*
 * Handle block mark swapping.
 *
 * Note that, when this function is called, it doesn't know whether it's
 * swapping the block mark, or swapping it *back* -- but it doesn't matter
 * because the the operation is the same.
 */
static void mxs_nand_swap_block_mark(struct bch_geometry *geo,
				     uint8_t *data_buf, uint8_t *oob_buf)
{
	uint32_t bit_offset = geo->block_mark_bit_offset;
	uint32_t buf_offset = geo->block_mark_byte_offset;

	uint32_t src;
	uint32_t dst;

	/*
	 * Get the byte from the data area that overlays the block mark. Since
	 * the ECC engine applies its own view to the bits in the page, the
	 * physical block mark won't (in general) appear on a byte boundary in
	 * the data.
	 */
	src = data_buf[buf_offset] >> bit_offset;
	src |= data_buf[buf_offset + 1] << (8 - bit_offset);

	dst = oob_buf[0];

	oob_buf[0] = src;

	data_buf[buf_offset] &= ~(0xff << bit_offset);
	data_buf[buf_offset + 1] &= 0xff << bit_offset;

	data_buf[buf_offset] |= dst << bit_offset;
	data_buf[buf_offset + 1] |= dst >> (8 - bit_offset);
}

/*
 * Read data from NAND.
 */
static void mxs_nand_read_buf(struct mtd_info *mtd, uint8_t *buf, int length)
{
	struct nand_chip *nand = mtd_to_nand(mtd);
	struct mxs_nand_info *nand_info = nand_get_controller_data(nand);
	struct mxs_dma_desc *d;
	uint32_t channel = MXS_DMA_CHANNEL_AHB_APBH_GPMI0 + nand_info->cur_chip;
	int ret;

	if (length > NAND_MAX_PAGESIZE) {
		printf("MXS NAND: DMA buffer too big\n");
		return;
	}

	if (!buf) {
		printf("MXS NAND: DMA buffer is NULL\n");
		return;
	}

	/* Compile the DMA descriptor - a descriptor that reads data. */
	d = mxs_nand_get_dma_desc(nand_info);
	d->cmd.data =
		MXS_DMA_DESC_COMMAND_DMA_WRITE | MXS_DMA_DESC_IRQ |
		MXS_DMA_DESC_DEC_SEM | MXS_DMA_DESC_WAIT4END |
		(1 << MXS_DMA_DESC_PIO_WORDS_OFFSET) |
		(length << MXS_DMA_DESC_BYTES_OFFSET);

	d->cmd.address = (dma_addr_t)nand_info->data_buf;

	d->cmd.pio_words[0] =
		GPMI_CTRL0_COMMAND_MODE_READ |
		GPMI_CTRL0_WORD_LENGTH |
		(nand_info->cur_chip << GPMI_CTRL0_CS_OFFSET) |
		GPMI_CTRL0_ADDRESS_NAND_DATA |
		length;

	mxs_dma_desc_append(channel, d);

	/*
	 * A DMA descriptor that waits for the command to end and the chip to
	 * become ready.
	 *
	 * I think we actually should *not* be waiting for the chip to become
	 * ready because, after all, we don't care. I think the original code
	 * did that and no one has re-thought it yet.
	 */
	d = mxs_nand_get_dma_desc(nand_info);
	d->cmd.data =
		MXS_DMA_DESC_COMMAND_NO_DMAXFER | MXS_DMA_DESC_IRQ |
		MXS_DMA_DESC_NAND_WAIT_4_READY | MXS_DMA_DESC_DEC_SEM |
		MXS_DMA_DESC_WAIT4END | (1 << MXS_DMA_DESC_PIO_WORDS_OFFSET);

	d->cmd.address = 0;

	d->cmd.pio_words[0] =
		GPMI_CTRL0_COMMAND_MODE_WAIT_FOR_READY |
		GPMI_CTRL0_WORD_LENGTH |
		(nand_info->cur_chip << GPMI_CTRL0_CS_OFFSET) |
		GPMI_CTRL0_ADDRESS_NAND_DATA;

	mxs_dma_desc_append(channel, d);

	/* Invalidate caches */
	mxs_nand_inval_data_buf(nand_info);

	/* Execute the DMA chain. */
	ret = mxs_dma_go(channel);
	if (ret) {
		printf("MXS NAND: DMA read error\n");
		goto rtn;
	}

	/* Invalidate caches */
	mxs_nand_inval_data_buf(nand_info);

	memcpy(buf, nand_info->data_buf, length);

rtn:
	mxs_nand_return_dma_descs(nand_info);
}

/*
 * Write data to NAND.
 */
static void mxs_nand_write_buf(struct mtd_info *mtd, const uint8_t *buf,
				int length)
{
	struct nand_chip *nand = mtd_to_nand(mtd);
	struct mxs_nand_info *nand_info = nand_get_controller_data(nand);
	struct mxs_dma_desc *d;
	uint32_t channel = MXS_DMA_CHANNEL_AHB_APBH_GPMI0 + nand_info->cur_chip;
	int ret;

	if (length > NAND_MAX_PAGESIZE) {
		printf("MXS NAND: DMA buffer too big\n");
		return;
	}

	if (!buf) {
		printf("MXS NAND: DMA buffer is NULL\n");
		return;
	}

	memcpy(nand_info->data_buf, buf, length);

	/* Compile the DMA descriptor - a descriptor that writes data. */
	d = mxs_nand_get_dma_desc(nand_info);
	d->cmd.data =
		MXS_DMA_DESC_COMMAND_DMA_READ | MXS_DMA_DESC_IRQ |
		MXS_DMA_DESC_DEC_SEM | MXS_DMA_DESC_WAIT4END |
		(1 << MXS_DMA_DESC_PIO_WORDS_OFFSET) |
		(length << MXS_DMA_DESC_BYTES_OFFSET);

	d->cmd.address = (dma_addr_t)nand_info->data_buf;

	d->cmd.pio_words[0] =
		GPMI_CTRL0_COMMAND_MODE_WRITE |
		GPMI_CTRL0_WORD_LENGTH |
		(nand_info->cur_chip << GPMI_CTRL0_CS_OFFSET) |
		GPMI_CTRL0_ADDRESS_NAND_DATA |
		length;

	mxs_dma_desc_append(channel, d);

	/* Flush caches */
	mxs_nand_flush_data_buf(nand_info);

	/* Execute the DMA chain. */
	ret = mxs_dma_go(channel);
	if (ret)
		printf("MXS NAND: DMA write error\n");

	mxs_nand_return_dma_descs(nand_info);
}

/*
 * Read a single byte from NAND.
 */
static uint8_t mxs_nand_read_byte(struct mtd_info *mtd)
{
	uint8_t buf;
	mxs_nand_read_buf(mtd, &buf, 1);
	return buf;
}

/*
 * Read a page from NAND.
 */
static int mxs_nand_ecc_read_page(struct mtd_info *mtd, struct nand_chip *nand,
					uint8_t *buf, int oob_required,
					int page)
{
	struct mxs_nand_info *nand_info = nand_get_controller_data(nand);
	struct bch_geometry *geo = &nand_info->bch_geometry;
	struct mxs_dma_desc *d;
	uint32_t channel = MXS_DMA_CHANNEL_AHB_APBH_GPMI0 + nand_info->cur_chip;
	uint32_t corrected = 0, failed = 0;
	uint8_t	*status;
	int i, ret;

	/* Compile the DMA descriptor - wait for ready. */
	d = mxs_nand_get_dma_desc(nand_info);
	d->cmd.data =
		MXS_DMA_DESC_COMMAND_NO_DMAXFER | MXS_DMA_DESC_CHAIN |
		MXS_DMA_DESC_NAND_WAIT_4_READY | MXS_DMA_DESC_WAIT4END |
		(1 << MXS_DMA_DESC_PIO_WORDS_OFFSET);

	d->cmd.address = 0;

	d->cmd.pio_words[0] =
		GPMI_CTRL0_COMMAND_MODE_WAIT_FOR_READY |
		GPMI_CTRL0_WORD_LENGTH |
		(nand_info->cur_chip << GPMI_CTRL0_CS_OFFSET) |
		GPMI_CTRL0_ADDRESS_NAND_DATA;

	mxs_dma_desc_append(channel, d);

	/* Compile the DMA descriptor - enable the BCH block and read. */
	d = mxs_nand_get_dma_desc(nand_info);
	d->cmd.data =
		MXS_DMA_DESC_COMMAND_NO_DMAXFER | MXS_DMA_DESC_CHAIN |
		MXS_DMA_DESC_WAIT4END |	(6 << MXS_DMA_DESC_PIO_WORDS_OFFSET);

	d->cmd.address = 0;

	d->cmd.pio_words[0] =
		GPMI_CTRL0_COMMAND_MODE_READ |
		GPMI_CTRL0_WORD_LENGTH |
		(nand_info->cur_chip << GPMI_CTRL0_CS_OFFSET) |
		GPMI_CTRL0_ADDRESS_NAND_DATA |
		(mtd->writesize + mtd->oobsize);
	d->cmd.pio_words[1] = 0;
	d->cmd.pio_words[2] =
		GPMI_ECCCTRL_ENABLE_ECC |
		GPMI_ECCCTRL_ECC_CMD_DECODE |
		GPMI_ECCCTRL_BUFFER_MASK_BCH_PAGE;
	d->cmd.pio_words[3] = mtd->writesize + mtd->oobsize;
	d->cmd.pio_words[4] = (dma_addr_t)nand_info->data_buf;
	d->cmd.pio_words[5] = (dma_addr_t)nand_info->oob_buf;

	mxs_dma_desc_append(channel, d);

	/* Compile the DMA descriptor - disable the BCH block. */
	d = mxs_nand_get_dma_desc(nand_info);
	d->cmd.data =
		MXS_DMA_DESC_COMMAND_NO_DMAXFER | MXS_DMA_DESC_CHAIN |
		MXS_DMA_DESC_NAND_WAIT_4_READY | MXS_DMA_DESC_WAIT4END |
		(3 << MXS_DMA_DESC_PIO_WORDS_OFFSET);

	d->cmd.address = 0;

	d->cmd.pio_words[0] =
		GPMI_CTRL0_COMMAND_MODE_WAIT_FOR_READY |
		GPMI_CTRL0_WORD_LENGTH |
		(nand_info->cur_chip << GPMI_CTRL0_CS_OFFSET) |
		GPMI_CTRL0_ADDRESS_NAND_DATA |
		(mtd->writesize + mtd->oobsize);
	d->cmd.pio_words[1] = 0;
	d->cmd.pio_words[2] = 0;

	mxs_dma_desc_append(channel, d);

	/* Compile the DMA descriptor - deassert the NAND lock and interrupt. */
	d = mxs_nand_get_dma_desc(nand_info);
	d->cmd.data =
		MXS_DMA_DESC_COMMAND_NO_DMAXFER | MXS_DMA_DESC_IRQ |
		MXS_DMA_DESC_DEC_SEM;

	d->cmd.address = 0;

	mxs_dma_desc_append(channel, d);

	/* Invalidate caches */
	mxs_nand_inval_data_buf(nand_info);

	/* Execute the DMA chain. */
	ret = mxs_dma_go(channel);
	if (ret) {
		printf("MXS NAND: DMA read error\n");
		goto rtn;
	}

	ret = mxs_nand_wait_for_bch_complete(nand_info);
	if (ret) {
		printf("MXS NAND: BCH read timeout\n");
		goto rtn;
	}

	/* Invalidate caches */
	mxs_nand_inval_data_buf(nand_info);

	/* Read DMA completed, now do the mark swapping. */
	mxs_nand_swap_block_mark(geo, nand_info->data_buf, nand_info->oob_buf);

	/* Loop over status bytes, accumulating ECC status. */
	status = nand_info->oob_buf + mxs_nand_aux_status_offset();
	for (i = 0; i < geo->ecc_chunk_count; i++) {
		if (status[i] == 0x00)
			continue;

		if (status[i] == 0xff)
			continue;

		if (status[i] == 0xfe) {
			failed++;
			continue;
		}

		corrected += status[i];
	}

	/* Propagate ECC status to the owning MTD. */
	mtd->ecc_stats.failed += failed;
	mtd->ecc_stats.corrected += corrected;

	/*
	 * It's time to deliver the OOB bytes. See mxs_nand_ecc_read_oob() for
	 * details about our policy for delivering the OOB.
	 *
	 * We fill the caller's buffer with set bits, and then copy the block
	 * mark to the caller's buffer. Note that, if block mark swapping was
	 * necessary, it has already been done, so we can rely on the first
	 * byte of the auxiliary buffer to contain the block mark.
	 */
	memset(nand->oob_poi, 0xff, mtd->oobsize);

	nand->oob_poi[0] = nand_info->oob_buf[0];

	memcpy(buf, nand_info->data_buf, mtd->writesize);

rtn:
	mxs_nand_return_dma_descs(nand_info);

	return ret;
}

/*
 * Write a page to NAND.
 */
static int mxs_nand_ecc_write_page(struct mtd_info *mtd,
				struct nand_chip *nand, const uint8_t *buf,
				int oob_required, int page)
{
	struct mxs_nand_info *nand_info = nand_get_controller_data(nand);
	struct bch_geometry *geo = &nand_info->bch_geometry;
	struct mxs_dma_desc *d;
	uint32_t channel = MXS_DMA_CHANNEL_AHB_APBH_GPMI0 + nand_info->cur_chip;
	int ret;

	memcpy(nand_info->data_buf, buf, mtd->writesize);
	memcpy(nand_info->oob_buf, nand->oob_poi, mtd->oobsize);

	/* Handle block mark swapping. */
	mxs_nand_swap_block_mark(geo, nand_info->data_buf, nand_info->oob_buf);

	/* Compile the DMA descriptor - write data. */
	d = mxs_nand_get_dma_desc(nand_info);
	d->cmd.data =
		MXS_DMA_DESC_COMMAND_NO_DMAXFER | MXS_DMA_DESC_IRQ |
		MXS_DMA_DESC_DEC_SEM | MXS_DMA_DESC_WAIT4END |
		(6 << MXS_DMA_DESC_PIO_WORDS_OFFSET);

	d->cmd.address = 0;

	d->cmd.pio_words[0] =
		GPMI_CTRL0_COMMAND_MODE_WRITE |
		GPMI_CTRL0_WORD_LENGTH |
		(nand_info->cur_chip << GPMI_CTRL0_CS_OFFSET) |
		GPMI_CTRL0_ADDRESS_NAND_DATA;
	d->cmd.pio_words[1] = 0;
	d->cmd.pio_words[2] =
		GPMI_ECCCTRL_ENABLE_ECC |
		GPMI_ECCCTRL_ECC_CMD_ENCODE |
		GPMI_ECCCTRL_BUFFER_MASK_BCH_PAGE;
	d->cmd.pio_words[3] = (mtd->writesize + mtd->oobsize);
	d->cmd.pio_words[4] = (dma_addr_t)nand_info->data_buf;
	d->cmd.pio_words[5] = (dma_addr_t)nand_info->oob_buf;

	mxs_dma_desc_append(channel, d);

	/* Flush caches */
	mxs_nand_flush_data_buf(nand_info);

	/* Execute the DMA chain. */
	ret = mxs_dma_go(channel);
	if (ret) {
		printf("MXS NAND: DMA write error\n");
		goto rtn;
	}

	ret = mxs_nand_wait_for_bch_complete(nand_info);
	if (ret) {
		printf("MXS NAND: BCH write timeout\n");
		goto rtn;
	}

rtn:
	mxs_nand_return_dma_descs(nand_info);
	return 0;
}

/*
 * Read OOB from NAND.
 *
 * This function is a veneer that replaces the function originally installed by
 * the NAND Flash MTD code.
 */
static int mxs_nand_hook_read_oob(struct mtd_info *mtd, loff_t from,
					struct mtd_oob_ops *ops)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct mxs_nand_info *nand_info = nand_get_controller_data(chip);
	int ret;

	if (ops->mode == MTD_OPS_RAW)
		nand_info->raw_oob_mode = 1;
	else
		nand_info->raw_oob_mode = 0;

	ret = nand_info->hooked_read_oob(mtd, from, ops);

	nand_info->raw_oob_mode = 0;

	return ret;
}

/*
 * Write OOB to NAND.
 *
 * This function is a veneer that replaces the function originally installed by
 * the NAND Flash MTD code.
 */
static int mxs_nand_hook_write_oob(struct mtd_info *mtd, loff_t to,
					struct mtd_oob_ops *ops)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct mxs_nand_info *nand_info = nand_get_controller_data(chip);
	int ret;

	if (ops->mode == MTD_OPS_RAW)
		nand_info->raw_oob_mode = 1;
	else
		nand_info->raw_oob_mode = 0;

	ret = nand_info->hooked_write_oob(mtd, to, ops);

	nand_info->raw_oob_mode = 0;

	return ret;
}

/*
 * Mark a block bad in NAND.
 *
 * This function is a veneer that replaces the function originally installed by
 * the NAND Flash MTD code.
 */
static int mxs_nand_hook_block_markbad(struct mtd_info *mtd, loff_t ofs)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct mxs_nand_info *nand_info = nand_get_controller_data(chip);
	int ret;

	nand_info->marking_block_bad = 1;

	ret = nand_info->hooked_block_markbad(mtd, ofs);

	nand_info->marking_block_bad = 0;

	return ret;
}

/*
 * There are several places in this driver where we have to handle the OOB and
 * block marks. This is the function where things are the most complicated, so
 * this is where we try to explain it all. All the other places refer back to
 * here.
 *
 * These are the rules, in order of decreasing importance:
 *
 * 1) Nothing the caller does can be allowed to imperil the block mark, so all
 *    write operations take measures to protect it.
 *
 * 2) In read operations, the first byte of the OOB we return must reflect the
 *    true state of the block mark, no matter where that block mark appears in
 *    the physical page.
 *
 * 3) ECC-based read operations return an OOB full of set bits (since we never
 *    allow ECC-based writes to the OOB, it doesn't matter what ECC-based reads
 *    return).
 *
 * 4) "Raw" read operations return a direct view of the physical bytes in the
 *    page, using the conventional definition of which bytes are data and which
 *    are OOB. This gives the caller a way to see the actual, physical bytes
 *    in the page, without the distortions applied by our ECC engine.
 *
 * What we do for this specific read operation depends on whether we're doing
 * "raw" read, or an ECC-based read.
 *
 * It turns out that knowing whether we want an "ECC-based" or "raw" read is not
 * easy. When reading a page, for example, the NAND Flash MTD code calls our
 * ecc.read_page or ecc.read_page_raw function. Thus, the fact that MTD wants an
 * ECC-based or raw view of the page is implicit in which function it calls
 * (there is a similar pair of ECC-based/raw functions for writing).
 *
 * Since MTD assumes the OOB is not covered by ECC, there is no pair of
 * ECC-based/raw functions for reading or or writing the OOB. The fact that the
 * caller wants an ECC-based or raw view of the page is not propagated down to
 * this driver.
 *
 * Since our OOB *is* covered by ECC, we need this information. So, we hook the
 * ecc.read_oob and ecc.write_oob function pointers in the owning
 * struct mtd_info with our own functions. These hook functions set the
 * raw_oob_mode field so that, when control finally arrives here, we'll know
 * what to do.
 */
static int mxs_nand_ecc_read_oob(struct mtd_info *mtd, struct nand_chip *nand,
				int page)
{
	struct mxs_nand_info *nand_info = nand_get_controller_data(nand);

	/*
	 * First, fill in the OOB buffer. If we're doing a raw read, we need to
	 * get the bytes from the physical page. If we're not doing a raw read,
	 * we need to fill the buffer with set bits.
	 */
	if (nand_info->raw_oob_mode) {
		/*
		 * If control arrives here, we're doing a "raw" read. Send the
		 * command to read the conventional OOB and read it.
		 */
		nand->cmdfunc(mtd, NAND_CMD_READ0, mtd->writesize, page);
		nand->read_buf(mtd, nand->oob_poi, mtd->oobsize);
	} else {
		/*
		 * If control arrives here, we're not doing a "raw" read. Fill
		 * the OOB buffer with set bits and correct the block mark.
		 */
		memset(nand->oob_poi, 0xff, mtd->oobsize);

		nand->cmdfunc(mtd, NAND_CMD_READ0, mtd->writesize, page);
		mxs_nand_read_buf(mtd, nand->oob_poi, 1);
	}

	return 0;

}

/*
 * Write OOB data to NAND.
 */
static int mxs_nand_ecc_write_oob(struct mtd_info *mtd, struct nand_chip *nand,
					int page)
{
	struct mxs_nand_info *nand_info = nand_get_controller_data(nand);
	uint8_t block_mark = 0;

	/*
	 * There are fundamental incompatibilities between the i.MX GPMI NFC and
	 * the NAND Flash MTD model that make it essentially impossible to write
	 * the out-of-band bytes.
	 *
	 * We permit *ONE* exception. If the *intent* of writing the OOB is to
	 * mark a block bad, we can do that.
	 */

	if (!nand_info->marking_block_bad) {
		printf("NXS NAND: Writing OOB isn't supported\n");
		return -EIO;
	}

	/* Write the block mark. */
	nand->cmdfunc(mtd, NAND_CMD_SEQIN, mtd->writesize, page);
	nand->write_buf(mtd, &block_mark, 1);
	nand->cmdfunc(mtd, NAND_CMD_PAGEPROG, -1, -1);

	/* Check if it worked. */
	if (nand->waitfunc(mtd, nand) & NAND_STATUS_FAIL)
		return -EIO;

	return 0;
}

/*
 * Claims all blocks are good.
 *
 * In principle, this function is *only* called when the NAND Flash MTD system
 * isn't allowed to keep an in-memory bad block table, so it is forced to ask
 * the driver for bad block information.
 *
 * In fact, we permit the NAND Flash MTD system to have an in-memory BBT, so
 * this function is *only* called when we take it away.
 *
 * Thus, this function is only called when we want *all* blocks to look good,
 * so it *always* return success.
 */
static int mxs_nand_block_bad(struct mtd_info *mtd, loff_t ofs)
{
	return 0;
}

static int mxs_nand_set_geometry(struct mtd_info *mtd, struct bch_geometry *geo)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct nand_chip *nand = mtd_to_nand(mtd);
	struct mxs_nand_info *nand_info = nand_get_controller_data(nand);

	if (chip->ecc.strength > 0 && chip->ecc.size > 0)
		return mxs_nand_calc_ecc_layout_by_info(geo, mtd,
				chip->ecc.strength, chip->ecc.size);

	if (nand_info->use_minimum_ecc ||
		mxs_nand_calc_ecc_layout(geo, mtd)) {
		if (!(chip->ecc_strength_ds > 0 && chip->ecc_step_ds > 0))
			return -EINVAL;

		return mxs_nand_calc_ecc_layout_by_info(geo, mtd,
				chip->ecc_strength_ds, chip->ecc_step_ds);
	}

	return 0;
}

/*
 * At this point, the physical NAND Flash chips have been identified and
 * counted, so we know the physical geometry. This enables us to make some
 * important configuration decisions.
 *
 * The return value of this function propagates directly back to this driver's
 * board_nand_init(). Anything other than zero will cause this driver to
 * tear everything down and declare failure.
 */
int mxs_nand_setup_ecc(struct mtd_info *mtd)
{
	struct nand_chip *nand = mtd_to_nand(mtd);
	struct mxs_nand_info *nand_info = nand_get_controller_data(nand);
	struct bch_geometry *geo = &nand_info->bch_geometry;
	struct mxs_bch_regs *bch_regs = nand_info->bch_regs;
	uint32_t tmp;
	int ret;

	ret = mxs_nand_set_geometry(mtd, geo);
	if (ret)
		return ret;

	mxs_nand_calc_mark_offset(geo, mtd->writesize);

	/* Configure BCH and set NFC geometry */
	mxs_reset_block(&bch_regs->hw_bch_ctrl_reg);

	/* Configure layout 0 */
	tmp = (geo->ecc_chunk_count - 1) << BCH_FLASHLAYOUT0_NBLOCKS_OFFSET;
	tmp |= MXS_NAND_METADATA_SIZE << BCH_FLASHLAYOUT0_META_SIZE_OFFSET;
	tmp |= (geo->ecc_strength >> 1) << BCH_FLASHLAYOUT0_ECC0_OFFSET;
	tmp |= geo->ecc_chunk_size >> MXS_NAND_CHUNK_DATA_CHUNK_SIZE_SHIFT;
	tmp |= (geo->gf_len == 14 ? 1 : 0) <<
		BCH_FLASHLAYOUT0_GF13_0_GF14_1_OFFSET;
	writel(tmp, &bch_regs->hw_bch_flash0layout0);

	tmp = (mtd->writesize + mtd->oobsize)
		<< BCH_FLASHLAYOUT1_PAGE_SIZE_OFFSET;
	tmp |= (geo->ecc_strength >> 1) << BCH_FLASHLAYOUT1_ECCN_OFFSET;
	tmp |= geo->ecc_chunk_size >> MXS_NAND_CHUNK_DATA_CHUNK_SIZE_SHIFT;
	tmp |= (geo->gf_len == 14 ? 1 : 0) <<
		BCH_FLASHLAYOUT1_GF13_0_GF14_1_OFFSET;
	writel(tmp, &bch_regs->hw_bch_flash0layout1);

	/* Set *all* chip selects to use layout 0 */
	writel(0, &bch_regs->hw_bch_layoutselect);

	/* Enable BCH complete interrupt */
	writel(BCH_CTRL_COMPLETE_IRQ_EN, &bch_regs->hw_bch_ctrl_set);

	/* Hook some operations at the MTD level. */
	if (mtd->_read_oob != mxs_nand_hook_read_oob) {
		nand_info->hooked_read_oob = mtd->_read_oob;
		mtd->_read_oob = mxs_nand_hook_read_oob;
	}

	if (mtd->_write_oob != mxs_nand_hook_write_oob) {
		nand_info->hooked_write_oob = mtd->_write_oob;
		mtd->_write_oob = mxs_nand_hook_write_oob;
	}

	if (mtd->_block_markbad != mxs_nand_hook_block_markbad) {
		nand_info->hooked_block_markbad = mtd->_block_markbad;
		mtd->_block_markbad = mxs_nand_hook_block_markbad;
	}

	return 0;
}

/*
 * Allocate DMA buffers
 */
int mxs_nand_alloc_buffers(struct mxs_nand_info *nand_info)
{
	uint8_t *buf;
	const int size = NAND_MAX_PAGESIZE + NAND_MAX_OOBSIZE;

	nand_info->data_buf_size = roundup(size, MXS_DMA_ALIGNMENT);

	/* DMA buffers */
	buf = memalign(MXS_DMA_ALIGNMENT, nand_info->data_buf_size);
	if (!buf) {
		printf("MXS NAND: Error allocating DMA buffers\n");
		return -ENOMEM;
	}

	memset(buf, 0, nand_info->data_buf_size);

	nand_info->data_buf = buf;
	nand_info->oob_buf = buf + NAND_MAX_PAGESIZE;
	/* Command buffers */
	nand_info->cmd_buf = memalign(MXS_DMA_ALIGNMENT,
				MXS_NAND_COMMAND_BUFFER_SIZE);
	if (!nand_info->cmd_buf) {
		free(buf);
		printf("MXS NAND: Error allocating command buffers\n");
		return -ENOMEM;
	}
	memset(nand_info->cmd_buf, 0, MXS_NAND_COMMAND_BUFFER_SIZE);
	nand_info->cmd_queue_len = 0;

	return 0;
}

/*
 * Initializes the NFC hardware.
 */
static int mxs_nand_init_dma(struct mxs_nand_info *info)
{
	int i = 0, j, ret = 0;

	info->desc = malloc(sizeof(struct mxs_dma_desc *) *
				MXS_NAND_DMA_DESCRIPTOR_COUNT);
	if (!info->desc) {
		ret = -ENOMEM;
		goto err1;
	}

	/* Allocate the DMA descriptors. */
	for (i = 0; i < MXS_NAND_DMA_DESCRIPTOR_COUNT; i++) {
		info->desc[i] = mxs_dma_desc_alloc();
		if (!info->desc[i]) {
			ret = -ENOMEM;
			goto err2;
		}
	}

	/* Init the DMA controller. */
	mxs_dma_init();
	for (j = MXS_DMA_CHANNEL_AHB_APBH_GPMI0;
		j <= MXS_DMA_CHANNEL_AHB_APBH_GPMI7; j++) {
		ret = mxs_dma_init_channel(j);
		if (ret)
			goto err3;
	}

	/* Reset the GPMI block. */
	mxs_reset_block(&info->gpmi_regs->hw_gpmi_ctrl0_reg);
	mxs_reset_block(&info->bch_regs->hw_bch_ctrl_reg);

	/*
	 * Choose NAND mode, set IRQ polarity, disable write protection and
	 * select BCH ECC.
	 */
	clrsetbits_le32(&info->gpmi_regs->hw_gpmi_ctrl1,
			GPMI_CTRL1_GPMI_MODE,
			GPMI_CTRL1_ATA_IRQRDY_POLARITY | GPMI_CTRL1_DEV_RESET |
			GPMI_CTRL1_BCH_MODE);

	return 0;

err3:
	for (--j; j >= MXS_DMA_CHANNEL_AHB_APBH_GPMI0; j--)
		mxs_dma_release(j);
err2:
	for (--i; i >= 0; i--)
		mxs_dma_desc_free(info->desc[i]);
	free(info->desc);
err1:
	if (ret == -ENOMEM)
		printf("MXS NAND: Unable to allocate DMA descriptors\n");
	return ret;
}

int mxs_nand_init_spl(struct nand_chip *nand)
{
	struct mxs_nand_info *nand_info;
	int err;

	nand_info = malloc(sizeof(struct mxs_nand_info));
	if (!nand_info) {
		printf("MXS NAND: Failed to allocate private data\n");
		return -ENOMEM;
	}
	memset(nand_info, 0, sizeof(struct mxs_nand_info));

	nand_info->gpmi_regs = (struct mxs_gpmi_regs *)MXS_GPMI_BASE;
	nand_info->bch_regs = (struct mxs_bch_regs *)MXS_BCH_BASE;

	if (is_mx6sx() || is_mx7())
		nand_info->max_ecc_strength_supported = 62;
	else
		nand_info->max_ecc_strength_supported = 40;

	err = mxs_nand_alloc_buffers(nand_info);
	if (err)
		return err;

	err = mxs_nand_init_dma(nand_info);
	if (err)
		return err;

	nand_set_controller_data(nand, nand_info);

	nand->options |= NAND_NO_SUBPAGE_WRITE;

	nand->cmd_ctrl		= mxs_nand_cmd_ctrl;
	nand->dev_ready		= mxs_nand_device_ready;
	nand->select_chip	= mxs_nand_select_chip;

	nand->read_byte		= mxs_nand_read_byte;
	nand->read_buf		= mxs_nand_read_buf;

	nand->ecc.read_page	= mxs_nand_ecc_read_page;

	nand->ecc.mode		= NAND_ECC_HW;

	return 0;
}

int mxs_nand_init_ctrl(struct mxs_nand_info *nand_info)
{
	struct mtd_info *mtd;
	struct nand_chip *nand;
	int err;

	nand = &nand_info->chip;
	mtd = nand_to_mtd(nand);
	err = mxs_nand_alloc_buffers(nand_info);
	if (err)
		return err;

	err = mxs_nand_init_dma(nand_info);
	if (err)
		goto err_free_buffers;

	memset(&fake_ecc_layout, 0, sizeof(fake_ecc_layout));

#ifdef CONFIG_SYS_NAND_USE_FLASH_BBT
	nand->bbt_options |= NAND_BBT_USE_FLASH | NAND_BBT_NO_OOB;
#endif

	nand_set_controller_data(nand, nand_info);
	nand->options |= NAND_NO_SUBPAGE_WRITE;

	if (nand_info->dev)
		nand->flash_node = dev_of_offset(nand_info->dev);

	nand->cmd_ctrl		= mxs_nand_cmd_ctrl;

	nand->dev_ready		= mxs_nand_device_ready;
	nand->select_chip	= mxs_nand_select_chip;
	nand->block_bad		= mxs_nand_block_bad;

	nand->read_byte		= mxs_nand_read_byte;

	nand->read_buf		= mxs_nand_read_buf;
	nand->write_buf		= mxs_nand_write_buf;

	/* first scan to find the device and get the page size */
	if (nand_scan_ident(mtd, CONFIG_SYS_MAX_NAND_DEVICE, NULL))
		goto err_free_buffers;

	if (mxs_nand_setup_ecc(mtd))
		goto err_free_buffers;

	nand->ecc.read_page	= mxs_nand_ecc_read_page;
	nand->ecc.write_page	= mxs_nand_ecc_write_page;
	nand->ecc.read_oob	= mxs_nand_ecc_read_oob;
	nand->ecc.write_oob	= mxs_nand_ecc_write_oob;

	nand->ecc.layout	= &fake_ecc_layout;
	nand->ecc.mode		= NAND_ECC_HW;
	nand->ecc.size		= nand_info->bch_geometry.ecc_chunk_size;
	nand->ecc.strength	= nand_info->bch_geometry.ecc_strength;

	/* second phase scan */
	err = nand_scan_tail(mtd);
	if (err)
		goto err_free_buffers;

	err = nand_register(0, mtd);
	if (err)
		goto err_free_buffers;

	return 0;

err_free_buffers:
	free(nand_info->data_buf);
	free(nand_info->cmd_buf);

	return err;
}

#ifndef CONFIG_NAND_MXS_DT
void board_nand_init(void)
{
	struct mxs_nand_info *nand_info;

	nand_info = malloc(sizeof(struct mxs_nand_info));
	if (!nand_info) {
		printf("MXS NAND: Failed to allocate private data\n");
			return;
	}
	memset(nand_info, 0, sizeof(struct mxs_nand_info));

	nand_info->gpmi_regs = (struct mxs_gpmi_regs *)MXS_GPMI_BASE;
	nand_info->bch_regs = (struct mxs_bch_regs *)MXS_BCH_BASE;

	/* Refer to Chapter 17 for i.MX6DQ, Chapter 18 for i.MX6SX */
	if (is_mx6sx() || is_mx7())
		nand_info->max_ecc_strength_supported = 62;
	else
		nand_info->max_ecc_strength_supported = 40;

#ifdef CONFIG_NAND_MXS_USE_MINIMUM_ECC
	nand_info->use_minimum_ecc = true;
#endif

	if (mxs_nand_init_ctrl(nand_info) < 0)
		goto err;

	return;

err:
	free(nand_info);
}
#endif
