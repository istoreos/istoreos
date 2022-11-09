/*
 * Copyright (C) 2014       Panasonic Corporation
 * Copyright (C) 2014-2015  Masahiro Yamada <yamada.masahiro@socionext.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <asm/io.h>
#include <asm/unaligned.h>
#include <linux/mtd/rawnand.h>
#include "denali.h"

#define DENALI_MAP01		(1 << 26)	/* read/write pages in PIO */
#define DENALI_MAP10		(2 << 26)	/* high-level control plane */

#define INDEX_CTRL_REG		0x0
#define INDEX_DATA_REG		0x10

#define SPARE_ACCESS		0x41
#define MAIN_ACCESS		0x42
#define PIPELINE_ACCESS		0x2000

#define BANK(x) ((x) << 24)

static void __iomem *denali_flash_mem =
			(void __iomem *)CONFIG_SYS_NAND_DATA_BASE;
static void __iomem *denali_flash_reg =
			(void __iomem *)CONFIG_SYS_NAND_REGS_BASE;

static const int flash_bank;
static int page_size, oob_size, pages_per_block;

static void index_addr(uint32_t address, uint32_t data)
{
	writel(address, denali_flash_mem + INDEX_CTRL_REG);
	writel(data, denali_flash_mem + INDEX_DATA_REG);
}

static int wait_for_irq(uint32_t irq_mask)
{
	unsigned long timeout = 1000000;
	uint32_t intr_status;

	do {
		intr_status = readl(denali_flash_reg + INTR_STATUS(flash_bank));

		if (intr_status & INTR__ECC_UNCOR_ERR) {
			debug("Uncorrected ECC detected\n");
			return -EBADMSG;
		}

		if (intr_status & irq_mask)
			break;

		udelay(1);
		timeout--;
	} while (timeout);

	if (!timeout) {
		debug("Timeout with interrupt status %08x\n", intr_status);
		return -EIO;
	}

	return 0;
}

static void read_data_from_flash_mem(uint8_t *buf, int len)
{
	int i;
	uint32_t *buf32;

	/* transfer the data from the flash */
	buf32 = (uint32_t *)buf;

	/*
	 * Let's take care of unaligned access although it rarely happens.
	 * Avoid put_unaligned() for the normal use cases since it leads to
	 * a bit performance regression.
	 */
	if ((unsigned long)buf32 % 4) {
		for (i = 0; i < len / 4; i++)
			put_unaligned(readl(denali_flash_mem + INDEX_DATA_REG),
				      buf32++);
	} else {
		for (i = 0; i < len / 4; i++)
			*buf32++ = readl(denali_flash_mem + INDEX_DATA_REG);
	}

	if (len % 4) {
		u32 tmp;

		tmp = cpu_to_le32(readl(denali_flash_mem + INDEX_DATA_REG));
		buf = (uint8_t *)buf32;
		for (i = 0; i < len % 4; i++) {
			*buf++ = tmp;
			tmp >>= 8;
		}
	}
}

int denali_send_pipeline_cmd(int page, int ecc_en, int access_type)
{
	uint32_t addr, cmd;
	static uint32_t page_count = 1;

	writel(ecc_en, denali_flash_reg + ECC_ENABLE);

	/* clear all bits of intr_status. */
	writel(0xffff, denali_flash_reg + INTR_STATUS(flash_bank));

	addr = BANK(flash_bank) | page;

	/* setup the acccess type */
	cmd = DENALI_MAP10 | addr;
	index_addr(cmd, access_type);

	/* setup the pipeline command */
	index_addr(cmd, PIPELINE_ACCESS | page_count);

	cmd = DENALI_MAP01 | addr;
	writel(cmd, denali_flash_mem + INDEX_CTRL_REG);

	return wait_for_irq(INTR__LOAD_COMP);
}

static int nand_read_oob(void *buf, int page)
{
	int ret;

	ret = denali_send_pipeline_cmd(page, 0, SPARE_ACCESS);
	if (ret < 0)
		return ret;

	read_data_from_flash_mem(buf, oob_size);

	return 0;
}

static int nand_read_page(void *buf, int page)
{
	int ret;

	ret = denali_send_pipeline_cmd(page, 1, MAIN_ACCESS);
	if (ret < 0)
		return ret;

	read_data_from_flash_mem(buf, page_size);

	return 0;
}

static int nand_block_isbad(void *buf, int block)
{
	int ret;

	ret = nand_read_oob(buf, block * pages_per_block);
	if (ret < 0)
		return ret;

	return *((uint8_t *)buf + CONFIG_SYS_NAND_BAD_BLOCK_POS) != 0xff;
}

/* nand_init() - initialize data to make nand usable by SPL */
void nand_init(void)
{
	/* access to main area */
	writel(0, denali_flash_reg + TRANSFER_SPARE_REG);

	/*
	 * These registers are expected to be already set by the hardware
	 * or earlier boot code.  So we read these values out.
	 */
	page_size = readl(denali_flash_reg + DEVICE_MAIN_AREA_SIZE);
	oob_size = readl(denali_flash_reg + DEVICE_SPARE_AREA_SIZE);
	pages_per_block = readl(denali_flash_reg + PAGES_PER_BLOCK);
}

int nand_spl_load_image(uint32_t offs, unsigned int size, void *dst)
{
	int block, page, column, readlen;
	int ret;
	int force_bad_block_check = 1;

	page = offs / page_size;
	column = offs % page_size;

	block = page / pages_per_block;
	page = page % pages_per_block;

	while (size) {
		if (force_bad_block_check || page == 0) {
			ret = nand_block_isbad(dst, block);
			if (ret < 0)
				return ret;

			if (ret) {
				block++;
				continue;
			}
		}

		force_bad_block_check = 0;

		ret = nand_read_page(dst, block * pages_per_block + page);
		if (ret < 0)
			return ret;

		readlen = min(page_size - column, (int)size);

		if (unlikely(column)) {
			/* Partial page read */
			memmove(dst, dst + column, readlen);
			column = 0;
		}

		size -= readlen;
		dst += readlen;
		page++;
		if (page == pages_per_block) {
			block++;
			page = 0;
		}
	}

	return 0;
}

void nand_deselect(void) {}
