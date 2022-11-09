/*
 * Copyright (c) 2011 The Chromium OS Authors.
 * (C) Copyright 2011 NVIDIA Corporation <www.nvidia.com>
 * (C) Copyright 2006 Detlev Zundel, dzu@denx.de
 * (C) Copyright 2006 DENX Software Engineering
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <asm/io.h>
#include <memalign.h>
#include <nand.h>
#include <asm/arch/clock.h>
#include <asm/arch/funcmux.h>
#include <asm/arch-tegra/clk_rst.h>
#include <linux/errno.h>
#include <asm/gpio.h>
#include <fdtdec.h>
#include <bouncebuf.h>
#include <dm.h>
#include "tegra_nand.h"

DECLARE_GLOBAL_DATA_PTR;

#define NAND_CMD_TIMEOUT_MS		10

#define SKIPPED_SPARE_BYTES		4

/* ECC bytes to be generated for tag data */
#define TAG_ECC_BYTES			4

static const struct udevice_id tegra_nand_dt_ids[] = {
	{
		.compatible = "nvidia,tegra20-nand",
	},
	{ /* sentinel */ }
};

/* 64 byte oob block info for large page (== 2KB) device
 *
 * OOB flash layout for Tegra with Reed-Solomon 4 symbol correct ECC:
 *      Skipped bytes(4)
 *      Main area Ecc(36)
 *      Tag data(20)
 *      Tag data Ecc(4)
 *
 * Yaffs2 will use 16 tag bytes.
 */
static struct nand_ecclayout eccoob = {
	.eccbytes = 36,
	.eccpos = {
		4,  5,  6,  7,  8,  9,  10, 11, 12,
		13, 14, 15, 16, 17, 18, 19, 20, 21,
		22, 23, 24, 25, 26, 27, 28, 29, 30,
		31, 32, 33, 34, 35, 36, 37, 38, 39,
	},
	.oobavail = 20,
	.oobfree = {
			{
			.offset = 40,
			.length = 20,
			},
	}
};

enum {
	ECC_OK,
	ECC_TAG_ERROR = 1 << 0,
	ECC_DATA_ERROR = 1 << 1
};

/* Timing parameters */
enum {
	FDT_NAND_MAX_TRP_TREA,
	FDT_NAND_TWB,
	FDT_NAND_MAX_TCR_TAR_TRR,
	FDT_NAND_TWHR,
	FDT_NAND_MAX_TCS_TCH_TALS_TALH,
	FDT_NAND_TWH,
	FDT_NAND_TWP,
	FDT_NAND_TRH,
	FDT_NAND_TADL,

	FDT_NAND_TIMING_COUNT
};

/* Information about an attached NAND chip */
struct fdt_nand {
	struct nand_ctlr *reg;
	int enabled;		/* 1 to enable, 0 to disable */
	struct gpio_desc wp_gpio;	/* write-protect GPIO */
	s32 width;		/* bit width, normally 8 */
	u32 timing[FDT_NAND_TIMING_COUNT];
};

struct nand_drv {
	struct nand_ctlr *reg;
	struct fdt_nand config;
};

struct tegra_nand_info {
	struct udevice *dev;
	struct nand_drv nand_ctrl;
	struct nand_chip nand_chip;
};

/**
 * Wait for command completion
 *
 * @param reg	nand_ctlr structure
 * @return
 *	1 - Command completed
 *	0 - Timeout
 */
static int nand_waitfor_cmd_completion(struct nand_ctlr *reg)
{
	u32 reg_val;
	int running;
	int i;

	for (i = 0; i < NAND_CMD_TIMEOUT_MS * 1000; i++) {
		if ((readl(&reg->command) & CMD_GO) ||
				!(readl(&reg->status) & STATUS_RBSY0) ||
				!(readl(&reg->isr) & ISR_IS_CMD_DONE)) {
			udelay(1);
			continue;
		}
		reg_val = readl(&reg->dma_mst_ctrl);
		/*
		 * If DMA_MST_CTRL_EN_A_ENABLE or DMA_MST_CTRL_EN_B_ENABLE
		 * is set, that means DMA engine is running.
		 *
		 * Then we have to wait until DMA_MST_CTRL_IS_DMA_DONE
		 * is cleared, indicating DMA transfer completion.
		 */
		running = reg_val & (DMA_MST_CTRL_EN_A_ENABLE |
				DMA_MST_CTRL_EN_B_ENABLE);
		if (!running || (reg_val & DMA_MST_CTRL_IS_DMA_DONE))
			return 1;
		udelay(1);
	}
	return 0;
}

/**
 * Read one byte from the chip
 *
 * @param mtd	MTD device structure
 * @return	data byte
 *
 * Read function for 8bit bus-width
 */
static uint8_t read_byte(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct nand_drv *info;

	info = (struct nand_drv *)nand_get_controller_data(chip);

	writel(CMD_GO | CMD_PIO | CMD_RX | CMD_CE0 | CMD_A_VALID,
	       &info->reg->command);
	if (!nand_waitfor_cmd_completion(info->reg))
		printf("Command timeout\n");

	return (uint8_t)readl(&info->reg->resp);
}

/**
 * Read len bytes from the chip into a buffer
 *
 * @param mtd	MTD device structure
 * @param buf	buffer to store data to
 * @param len	number of bytes to read
 *
 * Read function for 8bit bus-width
 */
static void read_buf(struct mtd_info *mtd, uint8_t *buf, int len)
{
	int i, s;
	unsigned int reg;
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct nand_drv *info = (struct nand_drv *)nand_get_controller_data(chip);

	for (i = 0; i < len; i += 4) {
		s = (len - i) > 4 ? 4 : len - i;
		writel(CMD_PIO | CMD_RX | CMD_A_VALID | CMD_CE0 |
			((s - 1) << CMD_TRANS_SIZE_SHIFT) | CMD_GO,
			&info->reg->command);
		if (!nand_waitfor_cmd_completion(info->reg))
			puts("Command timeout during read_buf\n");
		reg = readl(&info->reg->resp);
		memcpy(buf + i, &reg, s);
	}
}

/**
 * Check NAND status to see if it is ready or not
 *
 * @param mtd	MTD device structure
 * @return
 *	1 - ready
 *	0 - not ready
 */
static int nand_dev_ready(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	int reg_val;
	struct nand_drv *info;

	info = (struct nand_drv *)nand_get_controller_data(chip);

	reg_val = readl(&info->reg->status);
	if (reg_val & STATUS_RBSY0)
		return 1;
	else
		return 0;
}

/* Dummy implementation: we don't support multiple chips */
static void nand_select_chip(struct mtd_info *mtd, int chipnr)
{
	switch (chipnr) {
	case -1:
	case 0:
		break;

	default:
		BUG();
	}
}

/**
 * Clear all interrupt status bits
 *
 * @param reg	nand_ctlr structure
 */
static void nand_clear_interrupt_status(struct nand_ctlr *reg)
{
	u32 reg_val;

	/* Clear interrupt status */
	reg_val = readl(&reg->isr);
	writel(reg_val, &reg->isr);
}

/**
 * Send command to NAND device
 *
 * @param mtd		MTD device structure
 * @param command	the command to be sent
 * @param column	the column address for this command, -1 if none
 * @param page_addr	the page address for this command, -1 if none
 */
static void nand_command(struct mtd_info *mtd, unsigned int command,
	int column, int page_addr)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct nand_drv *info;

	info = (struct nand_drv *)nand_get_controller_data(chip);

	/*
	 * Write out the command to the device.
	 *
	 * Only command NAND_CMD_RESET or NAND_CMD_READID will come
	 * here before mtd->writesize is initialized.
	 */

	/* Emulate NAND_CMD_READOOB */
	if (command == NAND_CMD_READOOB) {
		assert(mtd->writesize != 0);
		column += mtd->writesize;
		command = NAND_CMD_READ0;
	}

	/* Adjust columns for 16 bit bus-width */
	if (column != -1 && (chip->options & NAND_BUSWIDTH_16))
		column >>= 1;

	nand_clear_interrupt_status(info->reg);

	/* Stop DMA engine, clear DMA completion status */
	writel(DMA_MST_CTRL_EN_A_DISABLE
		| DMA_MST_CTRL_EN_B_DISABLE
		| DMA_MST_CTRL_IS_DMA_DONE,
		&info->reg->dma_mst_ctrl);

	/*
	 * Program and erase have their own busy handlers
	 * status and sequential in needs no delay
	 */
	switch (command) {
	case NAND_CMD_READID:
		writel(NAND_CMD_READID, &info->reg->cmd_reg1);
		writel(column & 0xFF, &info->reg->addr_reg1);
		writel(CMD_GO | CMD_CLE | CMD_ALE | CMD_CE0,
		       &info->reg->command);
		break;
	case NAND_CMD_PARAM:
		writel(NAND_CMD_PARAM, &info->reg->cmd_reg1);
		writel(column & 0xFF, &info->reg->addr_reg1);
		writel(CMD_GO | CMD_CLE | CMD_ALE | CMD_CE0,
			&info->reg->command);
		break;
	case NAND_CMD_READ0:
		writel(NAND_CMD_READ0, &info->reg->cmd_reg1);
		writel(NAND_CMD_READSTART, &info->reg->cmd_reg2);
		writel((page_addr << 16) | (column & 0xFFFF),
			&info->reg->addr_reg1);
		writel(page_addr >> 16, &info->reg->addr_reg2);
		return;
	case NAND_CMD_SEQIN:
		writel(NAND_CMD_SEQIN, &info->reg->cmd_reg1);
		writel(NAND_CMD_PAGEPROG, &info->reg->cmd_reg2);
		writel((page_addr << 16) | (column & 0xFFFF),
			&info->reg->addr_reg1);
		writel(page_addr >> 16,
			&info->reg->addr_reg2);
		return;
	case NAND_CMD_PAGEPROG:
		return;
	case NAND_CMD_ERASE1:
		writel(NAND_CMD_ERASE1, &info->reg->cmd_reg1);
		writel(NAND_CMD_ERASE2, &info->reg->cmd_reg2);
		writel(page_addr, &info->reg->addr_reg1);
		writel(CMD_GO | CMD_CLE | CMD_ALE |
			CMD_SEC_CMD | CMD_CE0 | CMD_ALE_BYTES3,
			&info->reg->command);
		break;
	case NAND_CMD_ERASE2:
		return;
	case NAND_CMD_STATUS:
		writel(NAND_CMD_STATUS, &info->reg->cmd_reg1);
		writel(CMD_GO | CMD_CLE | CMD_PIO | CMD_RX
			| ((1 - 0) << CMD_TRANS_SIZE_SHIFT)
			| CMD_CE0,
			&info->reg->command);
		break;
	case NAND_CMD_RESET:
		writel(NAND_CMD_RESET, &info->reg->cmd_reg1);
		writel(CMD_GO | CMD_CLE | CMD_CE0,
			&info->reg->command);
		break;
	case NAND_CMD_RNDOUT:
	default:
		printf("%s: Unsupported command %d\n", __func__, command);
		return;
	}
	if (!nand_waitfor_cmd_completion(info->reg))
		printf("Command 0x%02X timeout\n", command);
}

/**
 * Check whether the pointed buffer are all 0xff (blank).
 *
 * @param buf	data buffer for blank check
 * @param len	length of the buffer in byte
 * @return
 *	1 - blank
 *	0 - non-blank
 */
static int blank_check(u8 *buf, int len)
{
	int i;

	for (i = 0; i < len; i++)
		if (buf[i] != 0xFF)
			return 0;
	return 1;
}

/**
 * After a DMA transfer for read, we call this function to see whether there
 * is any uncorrectable error on the pointed data buffer or oob buffer.
 *
 * @param reg		nand_ctlr structure
 * @param databuf	data buffer
 * @param a_len		data buffer length
 * @param oobbuf	oob buffer
 * @param b_len		oob buffer length
 * @return
 *	ECC_OK - no ECC error or correctable ECC error
 *	ECC_TAG_ERROR - uncorrectable tag ECC error
 *	ECC_DATA_ERROR - uncorrectable data ECC error
 *	ECC_DATA_ERROR + ECC_TAG_ERROR - uncorrectable data+tag ECC error
 */
static int check_ecc_error(struct nand_ctlr *reg, u8 *databuf,
	int a_len, u8 *oobbuf, int b_len)
{
	int return_val = ECC_OK;
	u32 reg_val;

	if (!(readl(&reg->isr) & ISR_IS_ECC_ERR))
		return ECC_OK;

	/*
	 * Area A is used for the data block (databuf). Area B is used for
	 * the spare block (oobbuf)
	 */
	reg_val = readl(&reg->dec_status);
	if ((reg_val & DEC_STATUS_A_ECC_FAIL) && databuf) {
		reg_val = readl(&reg->bch_dec_status_buf);
		/*
		 * If uncorrectable error occurs on data area, then see whether
		 * they are all FF. If all are FF, it's a blank page.
		 * Not error.
		 */
		if ((reg_val & BCH_DEC_STATUS_FAIL_SEC_FLAG_MASK) &&
				!blank_check(databuf, a_len))
			return_val |= ECC_DATA_ERROR;
	}

	if ((reg_val & DEC_STATUS_B_ECC_FAIL) && oobbuf) {
		reg_val = readl(&reg->bch_dec_status_buf);
		/*
		 * If uncorrectable error occurs on tag area, then see whether
		 * they are all FF. If all are FF, it's a blank page.
		 * Not error.
		 */
		if ((reg_val & BCH_DEC_STATUS_FAIL_TAG_MASK) &&
				!blank_check(oobbuf, b_len))
			return_val |= ECC_TAG_ERROR;
	}

	return return_val;
}

/**
 * Set GO bit to send command to device
 *
 * @param reg	nand_ctlr structure
 */
static void start_command(struct nand_ctlr *reg)
{
	u32 reg_val;

	reg_val = readl(&reg->command);
	reg_val |= CMD_GO;
	writel(reg_val, &reg->command);
}

/**
 * Clear command GO bit, DMA GO bit, and DMA completion status
 *
 * @param reg	nand_ctlr structure
 */
static void stop_command(struct nand_ctlr *reg)
{
	/* Stop command */
	writel(0, &reg->command);

	/* Stop DMA engine and clear DMA completion status */
	writel(DMA_MST_CTRL_GO_DISABLE
		| DMA_MST_CTRL_IS_DMA_DONE,
		&reg->dma_mst_ctrl);
}

/**
 * Set up NAND bus width and page size
 *
 * @param info		nand_info structure
 * @param *reg_val	address of reg_val
 * @return 0 if ok, -1 on error
 */
static int set_bus_width_page_size(struct mtd_info *our_mtd,
				   struct fdt_nand *config, u32 *reg_val)
{
	if (config->width == 8)
		*reg_val = CFG_BUS_WIDTH_8BIT;
	else if (config->width == 16)
		*reg_val = CFG_BUS_WIDTH_16BIT;
	else {
		debug("%s: Unsupported bus width %d\n", __func__,
		      config->width);
		return -1;
	}

	if (our_mtd->writesize == 512)
		*reg_val |= CFG_PAGE_SIZE_512;
	else if (our_mtd->writesize == 2048)
		*reg_val |= CFG_PAGE_SIZE_2048;
	else if (our_mtd->writesize == 4096)
		*reg_val |= CFG_PAGE_SIZE_4096;
	else {
		debug("%s: Unsupported page size %d\n", __func__,
		      our_mtd->writesize);
		return -1;
	}

	return 0;
}

/**
 * Page read/write function
 *
 * @param mtd		mtd info structure
 * @param chip		nand chip info structure
 * @param buf		data buffer
 * @param page		page number
 * @param with_ecc	1 to enable ECC, 0 to disable ECC
 * @param is_writing	0 for read, 1 for write
 * @return	0 when successfully completed
 *		-EIO when command timeout
 */
static int nand_rw_page(struct mtd_info *mtd, struct nand_chip *chip,
	uint8_t *buf, int page, int with_ecc, int is_writing)
{
	u32 reg_val;
	int tag_size;
	struct nand_oobfree *free = chip->ecc.layout->oobfree;
	/* 4*128=512 (byte) is the value that our HW can support. */
	ALLOC_CACHE_ALIGN_BUFFER(u32, tag_buf, 128);
	char *tag_ptr;
	struct nand_drv *info;
	struct fdt_nand *config;
	unsigned int bbflags;
	struct bounce_buffer bbstate, bbstate_oob;

	if ((uintptr_t)buf & 0x03) {
		printf("buf %p has to be 4-byte aligned\n", buf);
		return -EINVAL;
	}

	info = (struct nand_drv *)nand_get_controller_data(chip);
	config = &info->config;
	if (set_bus_width_page_size(mtd, config, &reg_val))
		return -EINVAL;

	/* Need to be 4-byte aligned */
	tag_ptr = (char *)tag_buf;

	stop_command(info->reg);

	if (is_writing)
		bbflags = GEN_BB_READ;
	else
		bbflags = GEN_BB_WRITE;

	bounce_buffer_start(&bbstate, (void *)buf, 1 << chip->page_shift,
			    bbflags);
	writel((1 << chip->page_shift) - 1, &info->reg->dma_cfg_a);
	writel(virt_to_phys(bbstate.bounce_buffer), &info->reg->data_block_ptr);

	/* Set ECC selection, configure ECC settings */
	if (with_ecc) {
		if (is_writing)
			memcpy(tag_ptr, chip->oob_poi + free->offset,
			       chip->ecc.layout->oobavail + TAG_ECC_BYTES);
		tag_size = chip->ecc.layout->oobavail + TAG_ECC_BYTES;
		reg_val |= (CFG_SKIP_SPARE_SEL_4
			| CFG_SKIP_SPARE_ENABLE
			| CFG_HW_ECC_CORRECTION_ENABLE
			| CFG_ECC_EN_TAG_DISABLE
			| CFG_HW_ECC_SEL_RS
			| CFG_HW_ECC_ENABLE
			| CFG_TVAL4
			| (tag_size - 1));

		if (!is_writing)
			tag_size += SKIPPED_SPARE_BYTES;
		bounce_buffer_start(&bbstate_oob, (void *)tag_ptr, tag_size,
				    bbflags);
	} else {
		tag_size = mtd->oobsize;
		reg_val |= (CFG_SKIP_SPARE_DISABLE
			| CFG_HW_ECC_CORRECTION_DISABLE
			| CFG_ECC_EN_TAG_DISABLE
			| CFG_HW_ECC_DISABLE
			| (tag_size - 1));
		bounce_buffer_start(&bbstate_oob, (void *)chip->oob_poi,
				    tag_size, bbflags);
	}
	writel(reg_val, &info->reg->config);
	writel(virt_to_phys(bbstate_oob.bounce_buffer), &info->reg->tag_ptr);
	writel(BCH_CONFIG_BCH_ECC_DISABLE, &info->reg->bch_config);
	writel(tag_size - 1, &info->reg->dma_cfg_b);

	nand_clear_interrupt_status(info->reg);

	reg_val = CMD_CLE | CMD_ALE
		| CMD_SEC_CMD
		| (CMD_ALE_BYTES5 << CMD_ALE_BYTE_SIZE_SHIFT)
		| CMD_A_VALID
		| CMD_B_VALID
		| (CMD_TRANS_SIZE_PAGE << CMD_TRANS_SIZE_SHIFT)
		| CMD_CE0;
	if (!is_writing)
		reg_val |= (CMD_AFT_DAT_DISABLE | CMD_RX);
	else
		reg_val |= (CMD_AFT_DAT_ENABLE | CMD_TX);
	writel(reg_val, &info->reg->command);

	/* Setup DMA engine */
	reg_val = DMA_MST_CTRL_GO_ENABLE
		| DMA_MST_CTRL_BURST_8WORDS
		| DMA_MST_CTRL_EN_A_ENABLE
		| DMA_MST_CTRL_EN_B_ENABLE;

	if (!is_writing)
		reg_val |= DMA_MST_CTRL_DIR_READ;
	else
		reg_val |= DMA_MST_CTRL_DIR_WRITE;

	writel(reg_val, &info->reg->dma_mst_ctrl);

	start_command(info->reg);

	if (!nand_waitfor_cmd_completion(info->reg)) {
		if (!is_writing)
			printf("Read Page 0x%X timeout ", page);
		else
			printf("Write Page 0x%X timeout ", page);
		if (with_ecc)
			printf("with ECC");
		else
			printf("without ECC");
		printf("\n");
		return -EIO;
	}

	bounce_buffer_stop(&bbstate_oob);
	bounce_buffer_stop(&bbstate);

	if (with_ecc && !is_writing) {
		memcpy(chip->oob_poi, tag_ptr,
			SKIPPED_SPARE_BYTES);
		memcpy(chip->oob_poi + free->offset,
			tag_ptr + SKIPPED_SPARE_BYTES,
			chip->ecc.layout->oobavail);
		reg_val = (u32)check_ecc_error(info->reg, (u8 *)buf,
			1 << chip->page_shift,
			(u8 *)(tag_ptr + SKIPPED_SPARE_BYTES),
			chip->ecc.layout->oobavail);
		if (reg_val & ECC_TAG_ERROR)
			printf("Read Page 0x%X tag ECC error\n", page);
		if (reg_val & ECC_DATA_ERROR)
			printf("Read Page 0x%X data ECC error\n",
				page);
		if (reg_val & (ECC_DATA_ERROR | ECC_TAG_ERROR))
			return -EIO;
	}
	return 0;
}

/**
 * Hardware ecc based page read function
 *
 * @param mtd	mtd info structure
 * @param chip	nand chip info structure
 * @param buf	buffer to store read data
 * @param page	page number to read
 * @return	0 when successfully completed
 *		-EIO when command timeout
 */
static int nand_read_page_hwecc(struct mtd_info *mtd,
	struct nand_chip *chip, uint8_t *buf, int oob_required, int page)
{
	return nand_rw_page(mtd, chip, buf, page, 1, 0);
}

/**
 * Hardware ecc based page write function
 *
 * @param mtd	mtd info structure
 * @param chip	nand chip info structure
 * @param buf	data buffer
 */
static int nand_write_page_hwecc(struct mtd_info *mtd,
	struct nand_chip *chip, const uint8_t *buf, int oob_required,
	int page)
{
	nand_rw_page(mtd, chip, (uint8_t *)buf, page, 1, 1);
	return 0;
}


/**
 * Read raw page data without ecc
 *
 * @param mtd	mtd info structure
 * @param chip	nand chip info structure
 * @param buf	buffer to store read data
 * @param page	page number to read
 * @return	0 when successfully completed
 *		-EINVAL when chip->oob_poi is not double-word aligned
 *		-EIO when command timeout
 */
static int nand_read_page_raw(struct mtd_info *mtd,
	struct nand_chip *chip, uint8_t *buf, int oob_required, int page)
{
	return nand_rw_page(mtd, chip, buf, page, 0, 0);
}

/**
 * Raw page write function
 *
 * @param mtd	mtd info structure
 * @param chip	nand chip info structure
 * @param buf	data buffer
 */
static int nand_write_page_raw(struct mtd_info *mtd,
		struct nand_chip *chip,	const uint8_t *buf,
		int oob_required, int page)
{
	nand_rw_page(mtd, chip, (uint8_t *)buf, page, 0, 1);
	return 0;
}

/**
 * OOB data read/write function
 *
 * @param mtd		mtd info structure
 * @param chip		nand chip info structure
 * @param page		page number to read
 * @param with_ecc	1 to enable ECC, 0 to disable ECC
 * @param is_writing	0 for read, 1 for write
 * @return	0 when successfully completed
 *		-EINVAL when chip->oob_poi is not double-word aligned
 *		-EIO when command timeout
 */
static int nand_rw_oob(struct mtd_info *mtd, struct nand_chip *chip,
	int page, int with_ecc, int is_writing)
{
	u32 reg_val;
	int tag_size;
	struct nand_oobfree *free = chip->ecc.layout->oobfree;
	struct nand_drv *info;
	unsigned int bbflags;
	struct bounce_buffer bbstate_oob;

	if (((int)chip->oob_poi) & 0x03)
		return -EINVAL;
	info = (struct nand_drv *)nand_get_controller_data(chip);
	if (set_bus_width_page_size(mtd, &info->config, &reg_val))
		return -EINVAL;

	stop_command(info->reg);

	/* Set ECC selection */
	tag_size = mtd->oobsize;
	if (with_ecc)
		reg_val |= CFG_ECC_EN_TAG_ENABLE;
	else
		reg_val |= (CFG_ECC_EN_TAG_DISABLE);

	reg_val |= ((tag_size - 1) |
		CFG_SKIP_SPARE_DISABLE |
		CFG_HW_ECC_CORRECTION_DISABLE |
		CFG_HW_ECC_DISABLE);
	writel(reg_val, &info->reg->config);

	if (is_writing && with_ecc)
		tag_size -= TAG_ECC_BYTES;

	if (is_writing)
		bbflags = GEN_BB_READ;
	else
		bbflags = GEN_BB_WRITE;

	bounce_buffer_start(&bbstate_oob, (void *)chip->oob_poi, tag_size,
			    bbflags);
	writel(virt_to_phys(bbstate_oob.bounce_buffer), &info->reg->tag_ptr);

	writel(BCH_CONFIG_BCH_ECC_DISABLE, &info->reg->bch_config);

	writel(tag_size - 1, &info->reg->dma_cfg_b);

	nand_clear_interrupt_status(info->reg);

	reg_val = CMD_CLE | CMD_ALE
		| CMD_SEC_CMD
		| (CMD_ALE_BYTES5 << CMD_ALE_BYTE_SIZE_SHIFT)
		| CMD_B_VALID
		| CMD_CE0;
	if (!is_writing)
		reg_val |= (CMD_AFT_DAT_DISABLE | CMD_RX);
	else
		reg_val |= (CMD_AFT_DAT_ENABLE | CMD_TX);
	writel(reg_val, &info->reg->command);

	/* Setup DMA engine */
	reg_val = DMA_MST_CTRL_GO_ENABLE
		| DMA_MST_CTRL_BURST_8WORDS
		| DMA_MST_CTRL_EN_B_ENABLE;
	if (!is_writing)
		reg_val |= DMA_MST_CTRL_DIR_READ;
	else
		reg_val |= DMA_MST_CTRL_DIR_WRITE;

	writel(reg_val, &info->reg->dma_mst_ctrl);

	start_command(info->reg);

	if (!nand_waitfor_cmd_completion(info->reg)) {
		if (!is_writing)
			printf("Read OOB of Page 0x%X timeout\n", page);
		else
			printf("Write OOB of Page 0x%X timeout\n", page);
		return -EIO;
	}

	bounce_buffer_stop(&bbstate_oob);

	if (with_ecc && !is_writing) {
		reg_val = (u32)check_ecc_error(info->reg, 0, 0,
			(u8 *)(chip->oob_poi + free->offset),
			chip->ecc.layout->oobavail);
		if (reg_val & ECC_TAG_ERROR)
			printf("Read OOB of Page 0x%X tag ECC error\n", page);
	}
	return 0;
}

/**
 * OOB data read function
 *
 * @param mtd		mtd info structure
 * @param chip		nand chip info structure
 * @param page		page number to read
 */
static int nand_read_oob(struct mtd_info *mtd, struct nand_chip *chip,
	int page)
{
	chip->cmdfunc(mtd, NAND_CMD_READOOB, 0, page);
	nand_rw_oob(mtd, chip, page, 0, 0);
	return 0;
}

/**
 * OOB data write function
 *
 * @param mtd	mtd info structure
 * @param chip	nand chip info structure
 * @param page	page number to write
 * @return	0 when successfully completed
 *		-EINVAL when chip->oob_poi is not double-word aligned
 *		-EIO when command timeout
 */
static int nand_write_oob(struct mtd_info *mtd, struct nand_chip *chip,
	int page)
{
	chip->cmdfunc(mtd, NAND_CMD_SEQIN, mtd->writesize, page);

	return nand_rw_oob(mtd, chip, page, 0, 1);
}

/**
 * Set up NAND memory timings according to the provided parameters
 *
 * @param timing	Timing parameters
 * @param reg		NAND controller register address
 */
static void setup_timing(unsigned timing[FDT_NAND_TIMING_COUNT],
			 struct nand_ctlr *reg)
{
	u32 reg_val, clk_rate, clk_period, time_val;

	clk_rate = (u32)clock_get_periph_rate(PERIPH_ID_NDFLASH,
		CLOCK_ID_PERIPH) / 1000000;
	clk_period = 1000 / clk_rate;
	reg_val = ((timing[FDT_NAND_MAX_TRP_TREA] / clk_period) <<
		TIMING_TRP_RESP_CNT_SHIFT) & TIMING_TRP_RESP_CNT_MASK;
	reg_val |= ((timing[FDT_NAND_TWB] / clk_period) <<
		TIMING_TWB_CNT_SHIFT) & TIMING_TWB_CNT_MASK;
	time_val = timing[FDT_NAND_MAX_TCR_TAR_TRR] / clk_period;
	if (time_val > 2)
		reg_val |= ((time_val - 2) << TIMING_TCR_TAR_TRR_CNT_SHIFT) &
			TIMING_TCR_TAR_TRR_CNT_MASK;
	reg_val |= ((timing[FDT_NAND_TWHR] / clk_period) <<
		TIMING_TWHR_CNT_SHIFT) & TIMING_TWHR_CNT_MASK;
	time_val = timing[FDT_NAND_MAX_TCS_TCH_TALS_TALH] / clk_period;
	if (time_val > 1)
		reg_val |= ((time_val - 1) << TIMING_TCS_CNT_SHIFT) &
			TIMING_TCS_CNT_MASK;
	reg_val |= ((timing[FDT_NAND_TWH] / clk_period) <<
		TIMING_TWH_CNT_SHIFT) & TIMING_TWH_CNT_MASK;
	reg_val |= ((timing[FDT_NAND_TWP] / clk_period) <<
		TIMING_TWP_CNT_SHIFT) & TIMING_TWP_CNT_MASK;
	reg_val |= ((timing[FDT_NAND_TRH] / clk_period) <<
		TIMING_TRH_CNT_SHIFT) & TIMING_TRH_CNT_MASK;
	reg_val |= ((timing[FDT_NAND_MAX_TRP_TREA] / clk_period) <<
		TIMING_TRP_CNT_SHIFT) & TIMING_TRP_CNT_MASK;
	writel(reg_val, &reg->timing);

	reg_val = 0;
	time_val = timing[FDT_NAND_TADL] / clk_period;
	if (time_val > 2)
		reg_val = (time_val - 2) & TIMING2_TADL_CNT_MASK;
	writel(reg_val, &reg->timing2);
}

/**
 * Decode NAND parameters from the device tree
 *
 * @param dev		Driver model device
 * @param config	Device tree NAND configuration
 * @return 0 if ok, -ve on error (FDT_ERR_...)
 */
static int fdt_decode_nand(struct udevice *dev, struct fdt_nand *config)
{
	int err;

	config->reg = (struct nand_ctlr *)dev_read_addr(dev);
	config->enabled = dev_read_enabled(dev);
	config->width = dev_read_u32_default(dev, "nvidia,nand-width", 8);
	err = gpio_request_by_name(dev, "nvidia,wp-gpios", 0, &config->wp_gpio,
				   GPIOD_IS_OUT);
	if (err)
		return err;
	err = dev_read_u32_array(dev, "nvidia,timing", config->timing,
				 FDT_NAND_TIMING_COUNT);
	if (err < 0)
		return err;

	return 0;
}

static int tegra_probe(struct udevice *dev)
{
	struct tegra_nand_info *tegra = dev_get_priv(dev);
	struct nand_chip *nand = &tegra->nand_chip;
	struct nand_drv *info = &tegra->nand_ctrl;
	struct fdt_nand *config = &info->config;
	struct mtd_info *our_mtd;
	int ret;

	if (fdt_decode_nand(dev, config)) {
		printf("Could not decode nand-flash in device tree\n");
		return -1;
	}
	if (!config->enabled)
		return -1;
	info->reg = config->reg;
	nand->ecc.mode = NAND_ECC_HW;
	nand->ecc.layout = &eccoob;

	nand->options = LP_OPTIONS;
	nand->cmdfunc = nand_command;
	nand->read_byte = read_byte;
	nand->read_buf = read_buf;
	nand->ecc.read_page = nand_read_page_hwecc;
	nand->ecc.write_page = nand_write_page_hwecc;
	nand->ecc.read_page_raw = nand_read_page_raw;
	nand->ecc.write_page_raw = nand_write_page_raw;
	nand->ecc.read_oob = nand_read_oob;
	nand->ecc.write_oob = nand_write_oob;
	nand->ecc.strength = 1;
	nand->select_chip = nand_select_chip;
	nand->dev_ready  = nand_dev_ready;
	nand_set_controller_data(nand, &tegra->nand_ctrl);

	/* Disable subpage writes as we do not provide ecc->hwctl */
	nand->options |= NAND_NO_SUBPAGE_WRITE;

	/* Adjust controller clock rate */
	clock_start_periph_pll(PERIPH_ID_NDFLASH, CLOCK_ID_PERIPH, 52000000);

	/* Adjust timing for NAND device */
	setup_timing(config->timing, info->reg);

	dm_gpio_set_value(&config->wp_gpio, 1);

	our_mtd = nand_to_mtd(nand);
	ret = nand_scan_ident(our_mtd, CONFIG_SYS_NAND_MAX_CHIPS, NULL);
	if (ret)
		return ret;

	nand->ecc.size = our_mtd->writesize;
	nand->ecc.bytes = our_mtd->oobsize;

	ret = nand_scan_tail(our_mtd);
	if (ret)
		return ret;

	ret = nand_register(0, our_mtd);
	if (ret) {
		dev_err(dev, "Failed to register MTD: %d\n", ret);
		return ret;
	}

	return 0;
}

U_BOOT_DRIVER(tegra_nand) = {
	.name = "tegra-nand",
	.id = UCLASS_MTD,
	.of_match = tegra_nand_dt_ids,
	.probe = tegra_probe,
	.priv_auto_alloc_size = sizeof(struct tegra_nand_info),
};

void board_nand_init(void)
{
	struct udevice *dev;
	int ret;

	ret = uclass_get_device_by_driver(UCLASS_MTD,
					  DM_GET_DRIVER(tegra_nand), &dev);
	if (ret && ret != -ENODEV)
		pr_err("Failed to initialize %s. (error %d)\n", dev->name,
		       ret);
}
