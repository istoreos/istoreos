/*
 * Copyright (c) 2017 Yifeng Zhao <yifeng.zhao@rock-chips.com>
 * Copyright (c) 2017 Paweł Jarosz <paweljarosz3691@gmail.com>
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <dm.h>
#include <fdtdec.h>
#include <inttypes.h>
#include <nand.h>
#include <linux/io.h>
#include <linux/ioport.h>
#include <linux/kernel.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/nand.h>
#include <linux/mtd/partitions.h>

DECLARE_GLOBAL_DATA_PTR;

#ifdef CONFIG_ROCKCHIP_RK3568
#define NANDC_V9_BOOTROM_ECC	16
#else
#define NANDC_V9_BOOTROM_ECC	70
#endif
#define NANDC_V9_NUM_BANKS	4
#define NANDC_V9_DEF_TIMEOUT	20000
#define NANDC_V9_READ		0
#define NANDC_V9_WRITE		1
#define NANDC_REG_V9_FMCTL	0x00
#define NANDC_REG_V9_FMWAIT	0x04
#define NANDC_REG_V9_FLCTL	0x10
#define NANDC_REG_V9_BCHCTL	0x20
#define NANDC_REG_V9_DMA_CFG	0x30
#define NANDC_REG_V9_DMA_BUF0	0x34
#define NANDC_REG_V9_DMA_BUF1	0x38
#define NANDC_REG_V9_DMA_ST	0x40
#define NANDC_REG_V9_VER	0x80
#define NANDC_REG_V9_INTEN	0x120
#define NANDC_REG_V9_INTCLR	0x124
#define NANDC_REG_V9_INTST	0x128
#define NANDC_REG_V9_BCHST	0x150
#define NANDC_REG_V9_SPARE0	0x200
#define NANDC_REG_V9_SPARE1	0x204
#define NANDC_REG_V9_RANDMZ	0x208
#define NANDC_REG_V9_BANK0	0x800
#define NANDC_REG_V9_SRAM0	0x1000
#define NANDC_REG_V9_SRAM_SIZE	0x400

#define NANDC_REG_V9_DATA	0x00
#define NANDC_REG_V9_ADDR	0x04
#define NANDC_REG_V9_CMD	0x08

/* FMCTL */
#define NANDC_V9_FM_WP		BIT(8)
#define NANDC_V9_FM_CE_SEL_M	0xFF
#define NANDC_V9_FM_CE_SEL(x)	(1 << (x))
#define NANDC_V9_FM_FREADY	BIT(9)

/* FLCTL */
#define NANDC_V9_FL_RST		BIT(0)
#define NANDC_V9_FL_DIR_S	0x1
#define NANDC_V9_FL_XFER_START	BIT(2)
#define NANDC_V9_FL_XFER_EN	BIT(3)
#define NANDC_V9_FL_ST_BUF_S	0x4
#define NANDC_V9_FL_XFER_COUNT	BIT(5)
#define NANDC_V9_FL_ACORRECT	BIT(10)
#define NANDC_V9_FL_XFER_READY	BIT(20)
#define NANDC_V9_FL_ASYNC_TOG_MIX	BIT(29)

/* BCHCTL */
#define NAND_V9_BCH_MODE_S	25
#define NAND_V9_BCH_MODE_M	0x7

/* BCHST */
#define NANDC_V9_BCH0_ST_ERR	BIT(2)
#define NANDC_V9_BCH1_ST_ERR	BIT(18)
#define NANDC_V9_ECC_ERR_CNT0(x) (((x) & (0x7F << 3)) >> 3)
#define NANDC_V9_ECC_ERR_CNT1(x) (((x) & (0x7F << 19)) >> 19)

struct rk_nand {
	uint32_t banks[NANDC_V9_NUM_BANKS];
	struct nand_hw_control controller;
	uint32_t ecc_strength;
	struct mtd_info mtd;
	bool bootromblocks;
	void __iomem *regs;
	int selected_bank;
	struct udevice *dev;
};

static struct nand_ecclayout nand_oob_fix = {
	.eccbytes = 24,
	.eccpos = {
		4, 5, 6, 7, 8, 9, 10
	},
	.oobfree = {
		{
			.offset = 0,
			.length = 4
		}
	}
};

static inline struct rk_nand *to_rknand(struct nand_hw_control *ctrl)
{
	return container_of(ctrl, struct rk_nand, controller);
}

static void rockchip_nand_init(struct rk_nand *rknand)
{
	writel(0, rknand->regs + NANDC_REG_V9_RANDMZ);
	writel(0, rknand->regs + NANDC_REG_V9_DMA_CFG);
	writel(0, rknand->regs + NANDC_REG_V9_BCHCTL);
	writel(NANDC_V9_FM_WP, rknand->regs + NANDC_REG_V9_FMCTL);
	writel(0x1081, rknand->regs + NANDC_REG_V9_FMWAIT);
}

static void rockchip_nand_select_chip(struct mtd_info *mtd, int chipnr)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct rk_nand *rknand = to_rknand(chip->controller);
	void __iomem *bank_base;
	uint32_t reg;
	int banknr;

	reg = readl(rknand->regs + NANDC_REG_V9_FMCTL);
	reg &= ~NANDC_V9_FM_CE_SEL_M;

	if (chipnr == -1) {
		banknr = -1;
	} else {
		banknr = rknand->banks[chipnr];
		bank_base = rknand->regs + NANDC_REG_V9_BANK0 + banknr * 0x100;

		chip->IO_ADDR_R = bank_base;
		chip->IO_ADDR_W = bank_base;

		reg |= 1 << banknr;
	}
	writel(reg, rknand->regs + NANDC_REG_V9_FMCTL);

	rknand->selected_bank = banknr;
}

static void rockchip_nand_cmd_ctrl(struct mtd_info *mtd,
				   int dat,
				   unsigned int ctrl)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct rk_nand *rknand = to_rknand(chip->controller);
	void __iomem *bank_base = rknand->regs + NANDC_REG_V9_BANK0
				+ rknand->selected_bank * 0x100;

	if (ctrl & NAND_CTRL_CHANGE) {
		if (ctrl & NAND_ALE)
			bank_base += NANDC_REG_V9_ADDR;
		else if (ctrl & NAND_CLE)
			bank_base += NANDC_REG_V9_CMD;
		chip->IO_ADDR_W = bank_base;
	}

	if (dat != NAND_CMD_NONE)
		writeb(dat & 0xFF, chip->IO_ADDR_W);
}

static void rockchip_nand_read_buf(struct mtd_info *mtd,
				   uint8_t *buf,
				   int len)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct rk_nand *rknand = to_rknand(chip->controller);
	int offs = 0;
	void __iomem *bank_base = rknand->regs + NANDC_REG_V9_BANK0
				+ rknand->selected_bank * 0x100;

	for (offs = 0; offs < len; offs++)
		buf[offs] = readb(bank_base);
}

static void rockchip_nand_write_buf(struct mtd_info *mtd,
				    const uint8_t *buf,
				    int len)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct rk_nand *rknand = to_rknand(chip->controller);
	int offs = 0;
	void __iomem *bank_base = rknand->regs + NANDC_REG_V9_BANK0
				+ rknand->selected_bank * 0x100;

	for (offs = 0; offs < len; offs++)
		writeb(buf[offs], bank_base);
}

static uint8_t rockchip_nand_read_byte(struct mtd_info *mtd)
{
	uint8_t ret;

	rockchip_nand_read_buf(mtd, &ret, 1);

	return ret;
}

static int rockchip_nand_dev_ready(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct rk_nand *rknand = to_rknand(chip->controller);

	if (readl(rknand->regs + NANDC_REG_V9_FMCTL) & NANDC_V9_FM_FREADY)
		return 1;

	return 0;
}

static int rockchip_nand_hw_ecc_setup(struct mtd_info *mtd,
				      struct nand_ecc_ctrl *ecc,
				      uint32_t strength)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct rk_nand *rknand = to_rknand(chip->controller);
	u32 reg;

	ecc->strength = strength;
	ecc->bytes = DIV_ROUND_UP(ecc->strength * 14, 8);
	ecc->bytes = ALIGN(ecc->bytes, 2);

	switch (ecc->strength) {
	case 70:
		reg = 0x00000001;
		break;
	case 60:
		reg = 0x06000001;
		break;
	case 40:
		reg = 0x04000001;
		break;
	case 16:
		reg = 0x02000001;
		break;
	default:
		return -EINVAL;
	}
	writel(reg, rknand->regs + NANDC_REG_V9_BCHCTL);

	return 0;
}

static void rockchip_nand_pio_xfer_start(struct rk_nand *rknand,
					 u8 dir,
					 u8 st_buf)
{
	u32 reg;

	reg = (dir << NANDC_V9_FL_DIR_S) | (st_buf << NANDC_V9_FL_ST_BUF_S) |
	      NANDC_V9_FL_XFER_EN | NANDC_V9_FL_XFER_COUNT |
	      NANDC_V9_FL_ACORRECT | NANDC_V9_FL_ASYNC_TOG_MIX;
	writel(reg, rknand->regs + NANDC_REG_V9_FLCTL);

	reg |= NANDC_V9_FL_XFER_START;
	writel(reg, rknand->regs + NANDC_REG_V9_FLCTL);
}

static int rockchip_nand_wait_pio_xfer_done(struct rk_nand *rknand)
{
	int timeout = NANDC_V9_DEF_TIMEOUT;
	int reg;

	while (timeout--) {
		reg = readl(rknand->regs + NANDC_REG_V9_FLCTL);

		if ((reg & NANDC_V9_FL_XFER_READY)  != 0)
			break;

		udelay(1);
	}

	if (timeout == 0)
		return -1;

	return 0;
}

static void rockchip_nand_read_extra_oob(struct mtd_info *mtd, u8 *oob)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct nand_ecc_ctrl *ecc = &chip->ecc;
	int offset = ((ecc->bytes + ecc->prepad) * ecc->steps);
	int len = mtd->oobsize - offset;

	if (len <= 0)
		return;

	chip->cmdfunc(mtd, NAND_CMD_RNDOUT, offset + mtd->writesize, -1);

	rockchip_nand_read_buf(mtd, oob + offset, len);
}

static void rockchip_nand_write_extra_oob(struct mtd_info *mtd, u8 *oob)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct nand_ecc_ctrl *ecc = &chip->ecc;
	int offset = ((ecc->bytes + ecc->prepad) * ecc->steps);
	int len = mtd->oobsize - offset;

	if (len <= 0)
		return;

	chip->cmdfunc(mtd, NAND_CMD_RNDIN, offset + mtd->writesize, -1);

	rockchip_nand_write_buf(mtd, oob + offset, len);
}

static int rockchip_nand_hw_syndrome_pio_read_page(struct mtd_info *mtd,
						   struct nand_chip *chip,
						   uint8_t *buf,
						   int oob_required,
						   int page)
{
	struct rk_nand *rknand = to_rknand(chip->controller);
	struct nand_ecc_ctrl *ecc = &chip->ecc;
	void __iomem *sram_base = rknand->regs + NANDC_REG_V9_SRAM0;
	unsigned int max_bitflips = 0;
	int ret, step, bch_st;
	int offset = page * mtd->writesize;

	if (rknand->bootromblocks && (offset < (4 * mtd->erasesize)))
		rockchip_nand_hw_ecc_setup(mtd, ecc, NANDC_V9_BOOTROM_ECC);

	rockchip_nand_pio_xfer_start(rknand, NANDC_V9_READ, 0);

	for (step = 0; step < ecc->steps; step++) {
		int data_off = step * ecc->size;
		int oob_off = step * (ecc->bytes + ecc->prepad);
		u8 *data = buf + data_off;
		u8 *oob = chip->oob_poi + oob_off;

		ret = rockchip_nand_wait_pio_xfer_done(rknand);
		if (ret)
			return ret;

		bch_st = readl(rknand->regs + NANDC_REG_V9_BCHST);

		if (bch_st & NANDC_V9_BCH0_ST_ERR) {
			mtd->ecc_stats.failed++;
			max_bitflips = -1;
		} else {
			ret = NANDC_V9_ECC_ERR_CNT0(bch_st);
			mtd->ecc_stats.corrected += ret;
			max_bitflips = max_t(unsigned int, max_bitflips, ret);
		}

		if ((step + 1) < ecc->steps)
			rockchip_nand_pio_xfer_start(rknand, NANDC_V9_READ,
					      		(step + 1) & 0x1);

		memcpy_fromio(data, sram_base + NANDC_REG_V9_SRAM_SIZE *
			     				(step & 1), ecc->size);

		if (step & 1)
			memcpy_fromio(oob, rknand->regs + NANDC_REG_V9_SPARE1, 4);
		else
			memcpy_fromio(oob, rknand->regs + NANDC_REG_V9_SPARE0, 4);
	}

	rockchip_nand_read_extra_oob(mtd, chip->oob_poi);

	if (rknand->bootromblocks)
		rockchip_nand_hw_ecc_setup(mtd, ecc, rknand->ecc_strength);

	return max_bitflips;
}

static uint32_t rockchip_nand_make_bootrom_compat(struct mtd_info *mtd,
						  int page,
						  const u8 *oob,
						  bool bootromblocks)
{
	int pages_per_block = mtd->erasesize / mtd->writesize;
	int offset = page * mtd->writesize;

	if ((offset < (2 * mtd->erasesize)) || !(page % 2) ||
	    (offset >= (7 * mtd->erasesize)) || !bootromblocks)
		return oob[3] | (oob[2] << 8) | (oob[1] << 16) | (oob[0] << 24);

	return (page % pages_per_block + 1) * 4;
}

static int rockchip_nand_hw_syndrome_pio_write_page(struct mtd_info *mtd,
						    struct nand_chip *chip,
						    const uint8_t *buf,
						    int oob_required,
						    int page)
{
	struct rk_nand *rknand = to_rknand(chip->controller);
	struct nand_ecc_ctrl *ecc = &chip->ecc;
	void __iomem *sram_base = rknand->regs + NANDC_REG_V9_SRAM0;
	int ret, index, step = 0;
	int offset = page * mtd->writesize;
	int data_off = step * ecc->size;
	int oob_off = step * (ecc->bytes + ecc->prepad);
	const u8 *data = buf + data_off;
	const u8 *oob = chip->oob_poi + oob_off;

	if (rknand->bootromblocks && (offset < (7 * mtd->erasesize)))
		rockchip_nand_hw_ecc_setup(mtd, ecc, NANDC_V9_BOOTROM_ECC);

	index = rockchip_nand_make_bootrom_compat(mtd, page, oob,
					   rknand->bootromblocks);

	memcpy_toio(sram_base, data, ecc->size);
	memcpy_toio(rknand->regs + NANDC_REG_V9_SPARE0, &index, ecc->prepad);

	for (step = 1; step <= ecc->steps; step++) {
		rockchip_nand_pio_xfer_start(rknand, NANDC_V9_WRITE,
					     (step - 1) & 0x1);
		data_off = step * ecc->size;
		oob_off = step * (ecc->bytes + ecc->prepad);
		data = buf + data_off;
		oob = chip->oob_poi + oob_off;

		if (step < ecc->steps) {
			memcpy_toio(sram_base + NANDC_REG_V9_SRAM_SIZE *
				    (step & 1), data, ecc->size);
			if (step & 1)
				memcpy_toio(rknand->regs + NANDC_REG_V9_SPARE1,
					    oob, ecc->prepad);
			else
				memcpy_toio(rknand->regs + NANDC_REG_V9_SPARE0,
					    oob, ecc->prepad);
		}

		ret = rockchip_nand_wait_pio_xfer_done(rknand);
		if (ret)
			return ret;
	}

	rockchip_nand_write_extra_oob(mtd, chip->oob_poi);

	if (rknand->bootromblocks)
		rockchip_nand_hw_ecc_setup(mtd, ecc, rknand->ecc_strength);

	return 0;
}

static const u8 strengths[] = {70, 60, 40, 16};

static int rockchip_nand_ecc_max_strength(struct mtd_info *mtd,
					  struct nand_ecc_ctrl *ecc)
{
	uint32_t max_strength, index;

	max_strength = ((mtd->oobsize / ecc->steps) - ecc->prepad) * 8 / 14;

	for (index = 0; index < ARRAY_SIZE(strengths); index++)
		if (max_strength >= strengths[index])
			break;

	if (index >= ARRAY_SIZE(strengths))
		return -ENOTSUPP;

	return strengths[index];
}

static bool rockchip_nand_strength_is_valid(int strength)
{
	uint32_t index;

	for (index = 0; index < ARRAY_SIZE(strengths); index++)
		if (strength == strengths[index])
			break;

	if (index == ARRAY_SIZE(strengths))
		return false;

	return true;
}

static int rockchip_nand_hw_ecc_ctrl_init(struct mtd_info *mtd,
					  struct nand_ecc_ctrl *ecc)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct rk_nand *rknand = to_rknand(chip->controller);
	uint32_t strength;
	int index;

	ecc->prepad = 4;
	ecc->steps = mtd->writesize / ecc->size;

	if (fdtdec_get_bool(gd->fdt_blob, chip->flash_node,
			    "rockchip,protect-bootrom-blocks"))
		rknand->bootromblocks = true;
	else
		rknand->bootromblocks = false;

	if (rockchip_nand_strength_is_valid(ecc->strength))
		strength = ecc->strength;
	else
		strength = rockchip_nand_ecc_max_strength(mtd, ecc);

	rockchip_nand_hw_ecc_setup(mtd, ecc, strength);

	rknand->ecc_strength = ecc->strength;

	nand_oob_fix.eccbytes = ecc->bytes * ecc->steps;
	for (index = 0; index < ecc->bytes; index++)
		nand_oob_fix.eccpos[index] = index + ecc->prepad;
	ecc->layout = &nand_oob_fix;

	if (mtd->oobsize < ((ecc->bytes + ecc->prepad) * ecc->steps)) {
		return -EINVAL;
	}

	return 0;
}

static int rockchip_nand_ecc_init(struct mtd_info *mtd,
				  struct nand_ecc_ctrl *ecc)
{
	int ret;

	switch (ecc->mode) {
	case NAND_ECC_HW:
	case NAND_ECC_HW_SYNDROME:
		ret = rockchip_nand_hw_ecc_ctrl_init(mtd, ecc);
		if (ret)
			return ret;
		ecc->read_page =  rockchip_nand_hw_syndrome_pio_read_page;
		ecc->write_page = rockchip_nand_hw_syndrome_pio_write_page;
		break;
	case NAND_ECC_SOFT_BCH:
	case NAND_ECC_NONE:
	case NAND_ECC_SOFT:
		break;
	default:
		return -EINVAL;
	}

	return 0;
}

static int rockchip_nand_block_bad(struct mtd_info *mtd, loff_t ofs)
{
	int page, res = 0;
	struct nand_chip *chip = mtd_to_nand(mtd);
	u16 bad = 0xff;
	int chipnr = (int)(ofs >> chip->chip_shift);

	page = (int)(ofs >> chip->page_shift) & chip->pagemask;
	chip->select_chip(mtd, chipnr);
	chip->cmdfunc(mtd, NAND_CMD_READ0, 0x00, page);
	if(rockchip_nand_hw_syndrome_pio_read_page(mtd,
	   chip, chip->buffers->databuf, 0, page) == -1) {
		/* first page of the block*/
		chip->cmdfunc(mtd, NAND_CMD_READOOB, chip->badblockpos, page);
		bad = chip->read_byte(mtd);
		if (bad != 0xFF)
			res = 1;
		/* second page of the block*/
		chip->cmdfunc(mtd, NAND_CMD_READOOB, chip->badblockpos,
			      page + 1);
		bad = chip->read_byte(mtd);
		if (bad != 0xFF)
			res = 1;
		/* last page of the block */
		page += ((mtd->erasesize - mtd->writesize) >> chip->chip_shift);
		page--;
		chip->cmdfunc(mtd, NAND_CMD_READOOB, chip->badblockpos, page);
		bad = chip->read_byte(mtd);
		if (bad != 0xFF)
			res = 1;
	}
	chip->select_chip(mtd, -1);
	if (res)
		printf("%s 0x%x %x %x\n", __func__, page, res, bad);
	return res;
}

static int rockchip_nand_chip_init(int node, struct rk_nand *rknand, int devnum)
{
	const void *blob = gd->fdt_blob;
	struct nand_chip *chip;
	struct mtd_info *mtd;
	int ret;

	chip = kzalloc(sizeof(*chip), GFP_KERNEL);

	chip->chip_delay = 50;
	chip->flash_node = node;
	chip->select_chip = rockchip_nand_select_chip;
	chip->cmd_ctrl = rockchip_nand_cmd_ctrl;
	chip->read_buf = rockchip_nand_read_buf;
	chip->write_buf = rockchip_nand_write_buf;
	chip->read_byte = rockchip_nand_read_byte;
	chip->dev_ready = rockchip_nand_dev_ready;
	chip->controller = &rknand->controller;
	chip->block_bad = rockchip_nand_block_bad;
	chip->bbt_options = NAND_BBT_USE_FLASH | NAND_BBT_NO_OOB;
	chip->options = NAND_NO_SUBPAGE_WRITE;

	rknand->banks[devnum] = fdtdec_get_int(blob, node, "reg", -1);

	if (rknand->banks[devnum] < 0)
		return -EINVAL;

	mtd = nand_to_mtd(chip);
	mtd->dev = rknand->dev;
	if (rknand->dev)
		rknand->dev->priv = mtd;

	ret = nand_scan_ident(mtd, 1, NULL);
	if (ret)
		return ret;

	ret = rockchip_nand_ecc_init(mtd, &chip->ecc);
	if (ret) {
		debug("rockchip_nand_ecc_init failed: %d\n", ret);
		return ret;
	}

	ret = nand_scan_tail(mtd);
	if (ret) {
		debug("nand_scan_tail failed: %d\n", ret);
		return ret;
	}

	ret = nand_register(devnum, mtd);
	if (ret) {
		debug("Failed to register mtd device: %d\n", ret);
		return ret;
	}
	memcpy(&rknand->mtd, mtd, sizeof(struct mtd_info));

	return 0;
}

static int rockchip_nand_chips_init(int node, struct rk_nand *rknand)
{
	const void *blob = gd->fdt_blob;
	int nand_node;
	int ret, i = 0;

	for (nand_node = fdt_first_subnode(blob, node); nand_node >= 0;
	     nand_node = fdt_next_subnode(blob, nand_node)) {
		ret = rockchip_nand_chip_init(nand_node, rknand, i++);
		if (ret)
			return ret;
	}

	return 0;
}

#ifdef CONFIG_NAND_ROCKCHIP_DT
static const struct udevice_id rockchip_nandc_ids[] = {
	{ .compatible = "rockchip,rk-nandc" },
	{ }
};

static int rockchip_nandc_probe(struct udevice *dev)
{
	const void *blob = gd->fdt_blob;
	struct rk_nand *rknand = dev_get_priv(dev);
	struct mtd_info *mtd = dev_get_uclass_priv(dev);
	fdt_addr_t regs;
	int ret = 0, node;

	node = fdtdec_next_compatible(blob, 0, COMPAT_ROCKCHIP_NANDC);

	rknand->dev = dev;

	regs = dev_read_addr(dev);
	if (regs == FDT_ADDR_T_NONE) {
		debug("Nand address not found\n");
		return ret;
	}

	rknand->regs = (void *)regs;

	spin_lock_init(&rknand->controller.lock);
	init_waitqueue_head(&rknand->controller.wq);

	rockchip_nand_init(rknand);

	ret = rockchip_nand_chips_init(node, rknand);
	if (ret)
		debug("Failed to init nand chips\n");

	memcpy(mtd, &rknand->mtd, sizeof(struct mtd_info));

	return ret;
}

static int rockchip_nandc_bind(struct udevice *udev)
{
	int ret = 0;

#ifdef CONFIG_MTD_BLK
	struct udevice *bdev;

	ret = blk_create_devicef(udev, "mtd_blk", "blk", IF_TYPE_MTD,
				 BLK_MTD_NAND, 512, 0, &bdev);
	if (ret)
		printf("Cannot create block device\n");
#endif
	return ret;
}

U_BOOT_DRIVER(rk_nandc_v9) = {
	.name           = "rk_nandc_v9",
	.id             = UCLASS_MTD,
	.of_match       = rockchip_nandc_ids,
	.bind		= rockchip_nandc_bind,
	.probe          = rockchip_nandc_probe,
	.priv_auto_alloc_size = sizeof(struct rk_nand),
};

void board_nand_init(void)
{
	struct udevice *dev;
	int ret;

	ret = uclass_get_device_by_driver(UCLASS_MTD,
					  DM_GET_DRIVER(rk_nandc_v9),
					  &dev);
	if (ret && ret != -ENODEV)
		pr_err("Failed to initialize NAND controller. (error %d)\n",
		       ret);
}
#else

void board_nand_init(void)
{
	const void *blob = gd->fdt_blob;
	struct rk_nand *rknand;
	fdt_addr_t regs;
	int node;
	int ret;

	rknand = kzalloc(sizeof(*rknand), GFP_KERNEL);

	node = fdtdec_next_compatible(blob, 0, COMPAT_ROCKCHIP_NANDC);

	if (node < 0) {
		debug("Nand node not found\n");
		goto err;
	}

	if (!fdtdec_get_is_enabled(blob, node)) {
		debug("Nand disabled in device tree\n");
		goto err;
	}

	regs = fdt_get_base_address(blob, node);
	if (regs == FDT_ADDR_T_NONE) {
		debug("Nand address not found\n");
		goto err;
	}

	rknand->regs = (void *)regs;

	spin_lock_init(&rknand->controller.lock);
	init_waitqueue_head(&rknand->controller.wq);

	rockchip_nand_init(rknand);

	ret = rockchip_nand_chips_init(node, rknand);
	if (ret) {
		debug("Failed to init nand chips\n");
		goto err;
	}

	return;
err:
	kfree(rknand);
}

#endif

int nand_spl_load_image(uint32_t offs, unsigned int size, void *dst)
{
	struct mtd_info *mtd;
	size_t length = size;

	mtd = get_nand_dev_by_index(0);
	return nand_read_skip_bad(mtd, offs, &length, NULL, size, (u_char *)dst);
}

void nand_deselect(void) {}
