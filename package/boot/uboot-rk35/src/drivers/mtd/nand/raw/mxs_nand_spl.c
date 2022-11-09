/*
 * Copyright (C) 2014 Gateworks Corporation
 * Author: Tim Harvey <tharvey@gateworks.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#include <common.h>
#include <nand.h>
#include <malloc.h>
#include "mxs_nand.h"

static struct mtd_info *mtd;
static struct nand_chip nand_chip;

static void mxs_nand_command(struct mtd_info *mtd, unsigned int command,
			     int column, int page_addr)
{
	register struct nand_chip *chip = mtd_to_nand(mtd);
	u32 timeo, time_start;

	/* write out the command to the device */
	chip->cmd_ctrl(mtd, command, NAND_CLE);

	/* Serially input address */
	if (column != -1) {
		chip->cmd_ctrl(mtd, column, NAND_ALE);
		chip->cmd_ctrl(mtd, column >> 8, NAND_ALE);
	}
	if (page_addr != -1) {
		chip->cmd_ctrl(mtd, page_addr, NAND_ALE);
		chip->cmd_ctrl(mtd, page_addr >> 8, NAND_ALE);
		/* One more address cycle for devices > 128MiB */
		if (chip->chipsize > (128 << 20))
			chip->cmd_ctrl(mtd, page_addr >> 16, NAND_ALE);
	}
	chip->cmd_ctrl(mtd, NAND_CMD_NONE, 0);

	if (command == NAND_CMD_READ0) {
		chip->cmd_ctrl(mtd, NAND_CMD_READSTART, NAND_CLE);
		chip->cmd_ctrl(mtd, NAND_CMD_NONE, 0);
	}

	/* wait for nand ready */
	ndelay(100);
	timeo = (CONFIG_SYS_HZ * 20) / 1000;
	time_start = get_timer(0);
	while (get_timer(time_start) < timeo) {
		if (chip->dev_ready(mtd))
			break;
	}
}

#if defined (CONFIG_SPL_NAND_IDENT)

/* Trying to detect the NAND flash using ONFi, JEDEC, and (extended) IDs */
static int mxs_flash_full_ident(struct mtd_info *mtd)
{
	int nand_maf_id, nand_dev_id;
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct nand_flash_dev *type;

	type = nand_get_flash_type(mtd, chip, &nand_maf_id, &nand_dev_id, NULL);

	if (IS_ERR(type)) {
		chip->select_chip(mtd, -1);
		return PTR_ERR(type);
	}

	return 0;
}

#else

/* Trying to detect the NAND flash using ONFi only */
static int mxs_flash_onfi_ident(struct mtd_info *mtd)
{
	register struct nand_chip *chip = mtd_to_nand(mtd);
	int i;
	u8 mfg_id, dev_id;
	u8 id_data[8];
	struct nand_onfi_params *p = &chip->onfi_params;

	/* Reset the chip */
	chip->cmdfunc(mtd, NAND_CMD_RESET, -1, -1);

	/* Send the command for reading device ID */
	chip->cmdfunc(mtd, NAND_CMD_READID, 0x00, -1);

	/* Read manufacturer and device IDs */
	mfg_id = chip->read_byte(mtd);
	dev_id = chip->read_byte(mtd);

	/* Try again to make sure */
	chip->cmdfunc(mtd, NAND_CMD_READID, 0x00, -1);
	for (i = 0; i < 8; i++)
		id_data[i] = chip->read_byte(mtd);
	if (id_data[0] != mfg_id || id_data[1] != dev_id) {
		printf("second ID read did not match");
		return -1;
	}
	debug("0x%02x:0x%02x ", mfg_id, dev_id);

	/* read ONFI */
	chip->onfi_version = 0;
	chip->cmdfunc(mtd, NAND_CMD_READID, 0x20, -1);
	if (chip->read_byte(mtd) != 'O' || chip->read_byte(mtd) != 'N' ||
	    chip->read_byte(mtd) != 'F' || chip->read_byte(mtd) != 'I') {
		return -2;
	}

	/* we have ONFI, probe it */
	chip->cmdfunc(mtd, NAND_CMD_PARAM, 0, -1);
	chip->read_buf(mtd, (uint8_t *)p, sizeof(*p));
	mtd->name = p->model;
	mtd->writesize = le32_to_cpu(p->byte_per_page);
	mtd->erasesize = le32_to_cpu(p->pages_per_block) * mtd->writesize;
	mtd->oobsize = le16_to_cpu(p->spare_bytes_per_page);
	chip->chipsize = le32_to_cpu(p->blocks_per_lun);
	chip->chipsize *= (uint64_t)mtd->erasesize * p->lun_count;
	/* Calculate the address shift from the page size */
	chip->page_shift = ffs(mtd->writesize) - 1;
	chip->phys_erase_shift = ffs(mtd->erasesize) - 1;
	/* Convert chipsize to number of pages per chip -1 */
	chip->pagemask = (chip->chipsize >> chip->page_shift) - 1;
	chip->badblockbits = 8;

	debug("erasesize=%d (>>%d)\n", mtd->erasesize, chip->phys_erase_shift);
	debug("writesize=%d (>>%d)\n", mtd->writesize, chip->page_shift);
	debug("oobsize=%d\n", mtd->oobsize);
	debug("chipsize=%lld\n", chip->chipsize);

	return 0;
}

#endif /* CONFIG_SPL_NAND_IDENT */

static int mxs_flash_ident(struct mtd_info *mtd)
{
	int ret;
#if defined (CONFIG_SPL_NAND_IDENT)
	ret = mxs_flash_full_ident(mtd);
#else
	ret = mxs_flash_onfi_ident(mtd);
#endif
	return ret;
}

static int mxs_read_page_ecc(struct mtd_info *mtd, void *buf, unsigned int page)
{
	register struct nand_chip *chip = mtd_to_nand(mtd);
	int ret;

	chip->cmdfunc(mtd, NAND_CMD_READ0, 0x0, page);
	ret = nand_chip.ecc.read_page(mtd, chip, buf, 1, page);
	if (ret < 0) {
		printf("read_page failed %d\n", ret);
		return -1;
	}
	return 0;
}

static int is_badblock(struct mtd_info *mtd, loff_t offs, int allowbbt)
{
	register struct nand_chip *chip = mtd_to_nand(mtd);
	unsigned int block = offs >> chip->phys_erase_shift;
	unsigned int page = offs >> chip->page_shift;

	debug("%s offs=0x%08x block:%d page:%d\n", __func__, (int)offs, block,
	      page);
	chip->cmdfunc(mtd, NAND_CMD_READ0, mtd->writesize, page);
	memset(chip->oob_poi, 0, mtd->oobsize);
	chip->read_buf(mtd, chip->oob_poi, mtd->oobsize);

	return chip->oob_poi[0] != 0xff;
}

/* setup mtd and nand structs and init mxs_nand driver */
void nand_init(void)
{
	/* return if already initalized */
	if (nand_chip.numchips)
		return;

	/* init mxs nand driver */
	mxs_nand_init_spl(&nand_chip);
	mtd = nand_to_mtd(&nand_chip);
	/* set mtd functions */
	nand_chip.cmdfunc = mxs_nand_command;
	nand_chip.scan_bbt = nand_default_bbt;
	nand_chip.numchips = 1;

	/* identify flash device */
	if (mxs_flash_ident(mtd)) {
		printf("Failed to identify\n");
		nand_chip.numchips = 0; /* If fail, don't use nand */
		return;
	}

	/* allocate and initialize buffers */
	nand_chip.buffers = memalign(ARCH_DMA_MINALIGN,
				     sizeof(*nand_chip.buffers));
	nand_chip.oob_poi = nand_chip.buffers->databuf + mtd->writesize;
	/* setup flash layout (does not scan as we override that) */
	mtd->size = nand_chip.chipsize;
	nand_chip.scan_bbt(mtd);
	mxs_nand_setup_ecc(mtd);
}

int nand_spl_load_image(uint32_t offs, unsigned int size, void *buf)
{
	struct nand_chip *chip;
	unsigned int page;
	unsigned int nand_page_per_block;
	unsigned int sz = 0;

	chip = mtd_to_nand(mtd);
	if (!chip->numchips)
		return -ENODEV;
	page = offs >> chip->page_shift;
	nand_page_per_block = mtd->erasesize / mtd->writesize;

	debug("%s offset:0x%08x len:%d page:%d\n", __func__, offs, size, page);

	size = roundup(size, mtd->writesize);
	while (sz < size) {
		if (mxs_read_page_ecc(mtd, buf, page) < 0)
			return -1;
		sz += mtd->writesize;
		offs += mtd->writesize;
		page++;
		buf += mtd->writesize;

		/*
		 * Check if we have crossed a block boundary, and if so
		 * check for bad block.
		 */
		if (!(page % nand_page_per_block)) {
			/*
			 * Yes, new block. See if this block is good. If not,
			 * loop until we find a good block.
			 */
			while (is_badblock(mtd, offs, 1)) {
				page = page + nand_page_per_block;
				/* Check i we've reached the end of flash. */
				if (page >= mtd->size >> chip->page_shift)
					return -ENOMEM;
			}
		}
	}

	return 0;
}

int nand_default_bbt(struct mtd_info *mtd)
{
	return 0;
}

void nand_deselect(void)
{
}

