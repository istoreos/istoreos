/*
 * Copyright (c) 2017 Yifeng Zhao <yifeng.zhao@rock-chips.com>
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <dm.h>
#include <fdtdec.h>
#include <fdt_support.h>
#include <inttypes.h>
#include <nand.h>
#include <linux/io.h>
#include <linux/kernel.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/nand.h>
#include <linux/mtd/partitions.h>

DECLARE_GLOBAL_DATA_PTR;

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

/* BCHCTL */
#define NAND_V9_BCH_MODE_S	25
#define NAND_V9_BCH_MODE_M	0x7

/* BCHST */
#define NANDC_V9_BCH0_ST_ERR	BIT(2)
#define NANDC_V9_BCH1_ST_ERR	BIT(18)
#define NANDC_V9_ECC_ERR_CNT0(x) (((x) & (0x7F << 3)) >> 3)
#define NANDC_V9_ECC_ERR_CNT1(x) (((x) & (0x7F << 19)) >> 19)

struct rk_nand {
	void __iomem *regs;
	u8 chipnr;
	u8 id[5];
	u8 *databuf;
	struct udevice *dev;
	struct mtd_info *mtd;
};

static struct rk_nand *g_rk_nand;
static u32 nand_page_size;
static u32 nand_page_num;
static u32 nand_block_num;

static void nandc_init(struct rk_nand *rknand)
{
	writel(0, rknand->regs + NANDC_REG_V9_RANDMZ);
	writel(0, rknand->regs + NANDC_REG_V9_DMA_CFG);
	writel(0x02000001, rknand->regs + NANDC_REG_V9_BCHCTL);
	writel(0x1081, rknand->regs + NANDC_REG_V9_FMWAIT);
}

static void rockchip_nand_wait_dev_ready(void __iomem *regs)
{
	u32 reg;
	u32 timeout = NANDC_V9_DEF_TIMEOUT;

	while (timeout--) {
		udelay(1);
		reg = readl(regs + NANDC_REG_V9_FMCTL);

		if (reg & NANDC_V9_FM_FREADY)
			break;
	}
}

static void rockchip_nand_select_chip(void __iomem *regs, int chipnr)
{
	u32 reg;

	reg = readl(regs + NANDC_REG_V9_FMCTL);
	reg &= ~NANDC_V9_FM_CE_SEL_M;
	if (chipnr != -1)
		reg |= 1 << chipnr;
	writel(reg, regs + NANDC_REG_V9_FMCTL);
}

static void rockchip_nand_read_page(void __iomem *regs,
				    int page, int col)
{
	void __iomem *bank_base = regs + NANDC_REG_V9_BANK0;

	writeb(0x00, bank_base + NANDC_REG_V9_CMD);
	writeb(col, bank_base + NANDC_REG_V9_ADDR);
	writeb(col >> 8, bank_base + NANDC_REG_V9_ADDR);
	writeb(page, bank_base + NANDC_REG_V9_ADDR);
	writeb(page >> 8, bank_base + NANDC_REG_V9_ADDR);
	writeb(page >> 16, bank_base + NANDC_REG_V9_ADDR);
	writeb(0x30, bank_base + NANDC_REG_V9_CMD);
}

static void rockchip_nand_pio_xfer_start(struct rk_nand *rknand,
					 u8 dir,
					 u8 st_buf)
{
	u32 reg;

	reg = (dir << NANDC_V9_FL_DIR_S) | (st_buf << NANDC_V9_FL_ST_BUF_S) |
	      NANDC_V9_FL_XFER_EN | NANDC_V9_FL_XFER_COUNT |
	      NANDC_V9_FL_ACORRECT;
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

static int nandc_read_page(unsigned int page, uint8_t *buf)
{
	void __iomem *sram_base = g_rk_nand->regs + NANDC_REG_V9_SRAM0;
	unsigned int max_bitflips = 0;
	int ret, step, bch_st, ecc_step;

	ecc_step = nand_page_size / 1024;
	rockchip_nand_select_chip(g_rk_nand->regs, 0);
	rockchip_nand_read_page(g_rk_nand->regs, page, 0);
	rockchip_nand_wait_dev_ready(g_rk_nand->regs);
	rockchip_nand_pio_xfer_start(g_rk_nand, NANDC_V9_READ, 0);

	for (step = 0; step < ecc_step; step++) {
		int data_off = step * 1024;
		u8 *data = buf + data_off;

		ret = rockchip_nand_wait_pio_xfer_done(g_rk_nand);
		if (ret)
			return ret;

		bch_st = readl(g_rk_nand->regs + NANDC_REG_V9_BCHST);

		if (bch_st & NANDC_V9_BCH0_ST_ERR) {
			max_bitflips = -1;
		} else {
			ret = NANDC_V9_ECC_ERR_CNT0(bch_st);
			max_bitflips = max_t(unsigned int, max_bitflips, ret);
		}

		if ((step + 1) < ecc_step)
			rockchip_nand_pio_xfer_start(g_rk_nand, NANDC_V9_READ,
						     (step + 1) & 0x1);

		memcpy_fromio(data, sram_base + NANDC_REG_V9_SRAM_SIZE *
			      (step & 1), 1024);
	}
	rockchip_nand_select_chip(g_rk_nand->regs, -1);

	return max_bitflips;
}

static int is_badblock(unsigned int page)
{
	int res = 0, i;
	u16 bad = 0xff;
	void __iomem *regs = g_rk_nand->regs;
	void __iomem *bank_base = regs + NANDC_REG_V9_BANK0;

	if (nandc_read_page(page, g_rk_nand->databuf) == -1) {
		rockchip_nand_select_chip(regs, 0);
		rockchip_nand_read_page(regs, page, nand_page_size);
		rockchip_nand_wait_dev_ready(regs);
		for (i = 0; i < 8; i++) {
			bad = readb(bank_base);
			if (bad)
				break;
		}
		if (i >= 8)
			res = 1;
		rockchip_nand_select_chip(regs, 0);
	}
	if (res)
		printf("%s 0x%x %x %x\n", __func__, page, res, bad);
	return res;
}

static void read_flash_id(struct rk_nand *rknand, uint8_t *id)
{
	void __iomem *bank_base = rknand->regs + NANDC_REG_V9_BANK0;

	rockchip_nand_wait_dev_ready(g_rk_nand->regs);
	writeb(0x90, bank_base + NANDC_REG_V9_CMD);
	writeb(0x00, bank_base + NANDC_REG_V9_ADDR);
	udelay(1);
	id[0] = readb(bank_base);
	id[1] = readb(bank_base);
	id[2] = readb(bank_base);
	id[3] = readb(bank_base);
	id[4] = readb(bank_base);
	rockchip_nand_select_chip(rknand->regs, -1);
	if (id[0] != 0xFF && id[0] != 0x00)
		printf("NAND:%x %x\n", id[0], id[1]);
}

#ifdef CONFIG_NAND_ROCKCHIP_DT
static const struct udevice_id rockchip_nandc_ids[] = {
	{ .compatible = "rockchip,rk-nandc" },
	{ }
};

static int spl_nand_block_isbad(struct mtd_info *mtd, loff_t ofs)
{
	return is_badblock((u32)ofs / nand_page_size);
}

static int spl_nand_read_page(struct mtd_info *mtd, loff_t from, size_t len,
			      size_t *retlen, u_char *buf)
{
	int read_size, offset, read_len;
	unsigned int page;
	unsigned int max_pages = nand_page_num * nand_block_num;

	/* Convert to page number */
	page = (u32)from / nand_page_size;
	offset = from & (nand_page_size - 1);
	read_len = len;
	*retlen = 0;

	while (read_len) {
		read_size = nand_page_size - offset;
		if (read_size > read_len)
			read_size = read_len;
		if (offset || read_size < nand_page_size) {
			if (nandc_read_page(page, g_rk_nand->databuf) < 0)
				return -EIO;
			memcpy(buf, g_rk_nand->databuf + offset, read_size);
			offset = 0;
		} else {
			if (nandc_read_page(page, buf) < 0)
				return -EIO;
		}
		page++;
		read_len -= read_size;
		buf += read_size;
		if (page >= max_pages)
			return -EIO;
	}

	*retlen = len;

	return 0;
}

static int rockchip_nandc_probe(struct udevice *dev)
{
	const void *blob = gd->fdt_blob;
	struct rk_nand *rknand = dev_get_priv(dev);
	struct mtd_info *mtd = dev_get_uclass_priv(dev);
	fdt_addr_t regs;
	int ret = -ENODEV;
	int node;
	u8 *id;

	g_rk_nand = rknand;
	rknand->dev = dev;

	node = fdtdec_next_compatible(blob, 0, COMPAT_ROCKCHIP_NANDC);

	if (node < 0) {
		printf("Nand node not found\n");
		return -ENODEV;
	}

	if (!fdtdec_get_is_enabled(blob, node)) {
		debug("Nand disabled in device tree\n");
		return -ENODEV;
	}

	regs = fdt_get_base_address(blob, node);
	if (!regs) {
		debug("Nand address not found\n");
		return -ENODEV;
	}

	rknand->regs = (void *)regs;

	nandc_init(g_rk_nand);
	read_flash_id(g_rk_nand, g_rk_nand->id);

	id = g_rk_nand->id;
	if (id[0] == id[1])
		return -ENODEV;

	if (id[1] == 0xA1 || id[1] == 0xF1 ||
	    id[1] == 0xD1 || id[1] == 0xAA ||
	    id[1] == 0xDA || id[1] == 0xAC ||
	    id[1] == 0xDC || id[1] == 0xA3 ||
	    id[1] == 0xD3 || id[1] == 0x95 ||
	    id[1] == 0x48 || id[1] == 0xD7) {
		nand_page_size = 2048;
		nand_page_num = 64;
		nand_block_num = 1024;
		if (id[1] == 0xDC) {
			if ((id[0] == 0x2C && id[3] == 0xA6) ||
			    (id[0] == 0xC2 && id[3] == 0xA2)) {
				nand_page_size = 4096;
				nand_block_num = 2048;
			} else if (id[0] == 0x98 && id[3] == 0x26) {
				nand_page_size = 4096;
				nand_block_num = 2048;
			} else {
				nand_block_num = 4096;
			}
		} else if (id[1] == 0xDA) {
			nand_block_num = 2048;
		} else if (id[1] == 0x48) {
			nand_page_size = 4096;
			nand_page_num = 128;
			nand_block_num = 4096;
		} else if (id[1] == 0xD3) {
			if ((id[2] == 0xD1 && id[4] == 0x5a) || /* S34ML08G2 */
			    (id[3] == 0x05 && id[4] == 0x04)) { /* S34ML08G3 */
				nand_block_num = 8192;
			} else {
				nand_page_size = 4096;
				nand_block_num = 4096;
			}
		} else if (id[1] == 0xd7 && id[3] == 0x32) { /* TC58NVG5H2HTAI0 */
			nand_page_size = 8192;
			nand_page_num = 128;
			nand_block_num = 4096;
		}
		g_rk_nand->chipnr = 1;
		g_rk_nand->databuf = kzalloc(nand_page_size, GFP_KERNEL);
		if (!g_rk_nand)
			return -ENOMEM;
		mtd->_block_isbad = spl_nand_block_isbad;
		mtd->_read = spl_nand_read_page;
		mtd->size = (size_t)nand_page_size * nand_page_num *
			    nand_block_num;
		mtd->writesize = nand_page_size;
		mtd->erasesize = nand_page_size * nand_page_num;
		mtd->erasesize_shift = ffs(mtd->erasesize) - 1;
		mtd->erasesize_mask = (1 << mtd->erasesize_shift) - 1;
		mtd->type = MTD_NANDFLASH;
		mtd->dev = rknand->dev;
		mtd->priv = rknand;
		add_mtd_device(mtd);
		rknand->mtd = mtd;
		ret = 0;
	}

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

int nand_spl_load_image(u32 offs, u32 size, void *buf)
{
	return -EIO;
}

void nand_init(void){};

int rk_nand_init(void)
{
	return -ENODEV;
}

#else
void board_nand_init(void)
{
	const void *blob = gd->fdt_blob;
	static int initialized;
	fdt_addr_t regs;
	int node;

	if (initialized)
		return;

	initialized = 1;
	nand_page_size = CONFIG_SYS_NAND_PAGE_SIZE;
	nand_page_num = CONFIG_SYS_NAND_PAGE_COUNT;

	if (g_rk_nand)
		return;

	node = fdtdec_next_compatible(blob, 0, COMPAT_ROCKCHIP_NANDC);

	if (node < 0) {
		printf("Nand node not found\n");
		return;
	}

	if (!fdtdec_get_is_enabled(blob, node)) {
		debug("Nand disabled in device tree\n");
		return;
	}

	regs = fdt_get_base_address(blob, node);
	if (!regs) {
		debug("Nand address not found\n");
		return;
	}

	g_rk_nand = kzalloc(sizeof(*g_rk_nand), GFP_KERNEL);
	g_rk_nand->regs = (void *)regs;
	g_rk_nand->databuf = kzalloc(nand_page_size, GFP_KERNEL);
	nandc_init(g_rk_nand);
	read_flash_id(g_rk_nand, g_rk_nand->id);

	if (g_rk_nand->id[0] == g_rk_nand->id[1])
		goto err;

	if (g_rk_nand->id[1] == 0xA1 || g_rk_nand->id[1] == 0xF1 ||
	    g_rk_nand->id[1] == 0xD1 || g_rk_nand->id[1] == 0xAA ||
	    g_rk_nand->id[1] == 0xDA || g_rk_nand->id[1] == 0xAC ||
	    g_rk_nand->id[1] == 0xDC || g_rk_nand->id[1] == 0xA3 ||
	    g_rk_nand->id[1] == 0xD3 || g_rk_nand->id[1] == 0x95 ||
	    g_rk_nand->id[1] == 0x48 || g_rk_nand->id[1] == 0xD7) {
		g_rk_nand->chipnr = 1;
		return;
	}

err:
	kfree(g_rk_nand->databuf);
	kfree(g_rk_nand);
	g_rk_nand = NULL;
}

int nand_spl_load_image(u32 offs, u32 size, void *buf)
{
	int i;
	unsigned int page;
	unsigned int maxpages = CONFIG_SYS_NAND_SIZE /
				nand_page_size;

	/* Convert to page number */
	page = offs / nand_page_size;
	i = 0;

	size = roundup(size, nand_page_size);
	while (i < size / nand_page_size) {
		/*
		 * Check if we have crossed a block boundary, and if so
		 * check for bad block.
		 */
		if (!(page % nand_page_num)) {
			/*
			 * Yes, new block. See if this block is good. If not,
			 * loop until we find a good block.
			 */
			while (is_badblock(page)) {
				page = page + nand_page_num;
				/* Check i we've reached the end of flash. */
				if (page >= maxpages)
					return -EIO;
			}
		}

		if (nandc_read_page(page, buf) < 0)
			return -EIO;

		page++;
		i++;
		buf = buf + nand_page_size;
	}
	return 0;
}

void nand_init(void)
{
	board_nand_init();
}

int rk_nand_init(void)
{
	board_nand_init();
	if (g_rk_nand && g_rk_nand->chipnr)
		return 0;
	else
		return -ENODEV;
}
#endif

void nand_deselect(void) {}

