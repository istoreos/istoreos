/*
 * LPC32xx SLC NAND flash controller driver
 *
 * (C) Copyright 2015-2018 Vladimir Zapolskiy <vz@mleia.com>
 * Copyright (c) 2015 Tyco Fire Protection Products.
 *
 * Hardware ECC support original source code
 * Copyright (C) 2008 by NXP Semiconductors
 * Author: Kevin Wells
 */

#include <common.h>
#include <nand.h>
#include <linux/mtd/nand_ecc.h>
#include <linux/errno.h>
#include <asm/io.h>
#include <asm/arch/config.h>
#include <asm/arch/clk.h>
#include <asm/arch/sys_proto.h>
#include <asm/arch/dma.h>
#include <asm/arch/cpu.h>

struct lpc32xx_nand_slc_regs {
	u32 data;
	u32 addr;
	u32 cmd;
	u32 stop;
	u32 ctrl;
	u32 cfg;
	u32 stat;
	u32 int_stat;
	u32 ien;
	u32 isr;
	u32 icr;
	u32 tac;
	u32 tc;
	u32 ecc;
	u32 dma_data;
};

/* CFG register */
#define CFG_CE_LOW		(1 << 5)
#define CFG_DMA_ECC		(1 << 4) /* Enable DMA ECC bit */
#define CFG_ECC_EN		(1 << 3) /* ECC enable bit */
#define CFG_DMA_BURST		(1 << 2) /* DMA burst bit */
#define CFG_DMA_DIR		(1 << 1) /* DMA write(0)/read(1) bit */

/* CTRL register */
#define CTRL_SW_RESET		(1 << 2)
#define CTRL_ECC_CLEAR		(1 << 1) /* Reset ECC bit */
#define CTRL_DMA_START		(1 << 0) /* Start DMA channel bit */

/* STAT register */
#define STAT_DMA_FIFO		(1 << 2) /* DMA FIFO has data bit */
#define STAT_NAND_READY		(1 << 0)

/* INT_STAT register */
#define INT_STAT_TC		(1 << 1)
#define INT_STAT_RDY		(1 << 0)

/* TAC register bits, be aware of overflows */
#define TAC_W_RDY(n)		(max_t(uint32_t, (n), 0xF) << 28)
#define TAC_W_WIDTH(n)		(max_t(uint32_t, (n), 0xF) << 24)
#define TAC_W_HOLD(n)		(max_t(uint32_t, (n), 0xF) << 20)
#define TAC_W_SETUP(n)		(max_t(uint32_t, (n), 0xF) << 16)
#define TAC_R_RDY(n)		(max_t(uint32_t, (n), 0xF) << 12)
#define TAC_R_WIDTH(n)		(max_t(uint32_t, (n), 0xF) << 8)
#define TAC_R_HOLD(n)		(max_t(uint32_t, (n), 0xF) << 4)
#define TAC_R_SETUP(n)		(max_t(uint32_t, (n), 0xF) << 0)

/* NAND ECC Layout for small page NAND devices
 * Note: For large page devices, the default layouts are used. */
static struct nand_ecclayout lpc32xx_nand_oob_16 = {
	.eccbytes = 6,
	.eccpos = { 10, 11, 12, 13, 14, 15, },
	.oobfree = {
		{ .offset = 0, .length = 4, },
		{ .offset = 6, .length = 4, },
	}
};

#if defined(CONFIG_DMA_LPC32XX) && !defined(CONFIG_SPL_BUILD)
#define ECCSTEPS	(CONFIG_SYS_NAND_PAGE_SIZE / CONFIG_SYS_NAND_ECCSIZE)

/*
 * DMA Descriptors
 * For Large Block: 17 descriptors = ((16 Data and ECC Read) + 1 Spare Area)
 * For Small Block: 5 descriptors = ((4 Data and ECC Read) + 1 Spare Area)
 */
static struct lpc32xx_dmac_ll dmalist[ECCSTEPS * 2 + 1];
static u32 ecc_buffer[8]; /* MAX ECC size */
static unsigned int dmachan = (unsigned int)-1; /* Invalid channel */

/*
 * Helper macro for the DMA client (i.e. NAND SLC):
 * - to write the next DMA linked list item address
 *   (see arch/include/asm/arch-lpc32xx/dma.h).
 * - to assign the DMA data register to DMA source or destination address.
 * - to assign the ECC register to DMA source or destination address.
 */
#define lpc32xx_dmac_next_lli(x)	((u32)x)
#define lpc32xx_dmac_set_dma_data()	((u32)&lpc32xx_nand_slc_regs->dma_data)
#define lpc32xx_dmac_set_ecc()		((u32)&lpc32xx_nand_slc_regs->ecc)
#endif

static struct lpc32xx_nand_slc_regs __iomem *lpc32xx_nand_slc_regs
	= (struct lpc32xx_nand_slc_regs __iomem *)SLC_NAND_BASE;

static void lpc32xx_nand_init(void)
{
	uint32_t hclk = get_hclk_clk_rate();

	/* Reset SLC NAND controller */
	writel(CTRL_SW_RESET, &lpc32xx_nand_slc_regs->ctrl);

	/* 8-bit bus, no DMA, no ECC, ordinary CE signal */
	writel(0, &lpc32xx_nand_slc_regs->cfg);

	/* Interrupts disabled and cleared */
	writel(0, &lpc32xx_nand_slc_regs->ien);
	writel(INT_STAT_TC | INT_STAT_RDY,
	       &lpc32xx_nand_slc_regs->icr);

	/* Configure NAND flash timings */
	writel(TAC_W_RDY(CONFIG_LPC32XX_NAND_SLC_WDR_CLKS) |
	       TAC_W_WIDTH(hclk / CONFIG_LPC32XX_NAND_SLC_WWIDTH) |
	       TAC_W_HOLD(hclk / CONFIG_LPC32XX_NAND_SLC_WHOLD) |
	       TAC_W_SETUP(hclk / CONFIG_LPC32XX_NAND_SLC_WSETUP) |
	       TAC_R_RDY(CONFIG_LPC32XX_NAND_SLC_RDR_CLKS) |
	       TAC_R_WIDTH(hclk / CONFIG_LPC32XX_NAND_SLC_RWIDTH) |
	       TAC_R_HOLD(hclk / CONFIG_LPC32XX_NAND_SLC_RHOLD) |
	       TAC_R_SETUP(hclk / CONFIG_LPC32XX_NAND_SLC_RSETUP),
	       &lpc32xx_nand_slc_regs->tac);
}

static void lpc32xx_nand_cmd_ctrl(struct mtd_info *mtd,
				  int cmd, unsigned int ctrl)
{
	debug("ctrl: 0x%08x, cmd: 0x%08x\n", ctrl, cmd);

	if (ctrl & NAND_NCE)
		setbits_le32(&lpc32xx_nand_slc_regs->cfg, CFG_CE_LOW);
	else
		clrbits_le32(&lpc32xx_nand_slc_regs->cfg, CFG_CE_LOW);

	if (cmd == NAND_CMD_NONE)
		return;

	if (ctrl & NAND_CLE)
		writel(cmd & 0xFF, &lpc32xx_nand_slc_regs->cmd);
	else if (ctrl & NAND_ALE)
		writel(cmd & 0xFF, &lpc32xx_nand_slc_regs->addr);
}

static int lpc32xx_nand_dev_ready(struct mtd_info *mtd)
{
	return readl(&lpc32xx_nand_slc_regs->stat) & STAT_NAND_READY;
}

#if defined(CONFIG_DMA_LPC32XX) && !defined(CONFIG_SPL_BUILD)
/*
 * Prepares DMA descriptors for NAND RD/WR operations
 * If the size is < 256 Bytes then it is assumed to be
 * an OOB transfer
 */
static void lpc32xx_nand_dma_configure(struct nand_chip *chip,
				       const u8 *buffer, int size,
				       int read)
{
	u32 i, dmasrc, ctrl, ecc_ctrl, oob_ctrl, dmadst;
	struct lpc32xx_dmac_ll *dmalist_cur;
	struct lpc32xx_dmac_ll *dmalist_cur_ecc;

	/*
	 * CTRL descriptor entry for reading ECC
	 * Copy Multiple times to sync DMA with Flash Controller
	 */
	ecc_ctrl = 0x5 |
			DMAC_CHAN_SRC_BURST_1 |
			DMAC_CHAN_DEST_BURST_1 |
			DMAC_CHAN_SRC_WIDTH_32 |
			DMAC_CHAN_DEST_WIDTH_32 |
			DMAC_CHAN_DEST_AHB1;

	/* CTRL descriptor entry for reading/writing Data */
	ctrl = (CONFIG_SYS_NAND_ECCSIZE / 4) |
			DMAC_CHAN_SRC_BURST_4 |
			DMAC_CHAN_DEST_BURST_4 |
			DMAC_CHAN_SRC_WIDTH_32 |
			DMAC_CHAN_DEST_WIDTH_32 |
			DMAC_CHAN_DEST_AHB1;

	/* CTRL descriptor entry for reading/writing Spare Area */
	oob_ctrl = (CONFIG_SYS_NAND_OOBSIZE / 4) |
			DMAC_CHAN_SRC_BURST_4 |
			DMAC_CHAN_DEST_BURST_4 |
			DMAC_CHAN_SRC_WIDTH_32 |
			DMAC_CHAN_DEST_WIDTH_32 |
			DMAC_CHAN_DEST_AHB1;

	if (read) {
		dmasrc = lpc32xx_dmac_set_dma_data();
		dmadst = (u32)buffer;
		ctrl |= DMAC_CHAN_DEST_AUTOINC;
	} else {
		dmadst = lpc32xx_dmac_set_dma_data();
		dmasrc = (u32)buffer;
		ctrl |= DMAC_CHAN_SRC_AUTOINC;
	}

	/*
	 * Write Operation Sequence for Small Block NAND
	 * ----------------------------------------------------------
	 * 1. X'fer 256 bytes of data from Memory to Flash.
	 * 2. Copy generated ECC data from Register to Spare Area
	 * 3. X'fer next 256 bytes of data from Memory to Flash.
	 * 4. Copy generated ECC data from Register to Spare Area.
	 * 5. X'fer 16 byets of Spare area from Memory to Flash.
	 * Read Operation Sequence for Small Block NAND
	 * ----------------------------------------------------------
	 * 1. X'fer 256 bytes of data from Flash to Memory.
	 * 2. Copy generated ECC data from Register to ECC calc Buffer.
	 * 3. X'fer next 256 bytes of data from Flash to Memory.
	 * 4. Copy generated ECC data from Register to ECC calc Buffer.
	 * 5. X'fer 16 bytes of Spare area from Flash to Memory.
	 * Write Operation Sequence for Large Block NAND
	 * ----------------------------------------------------------
	 * 1. Steps(1-4) of Write Operations repeate for four times
	 * which generates 16 DMA descriptors to X'fer 2048 bytes of
	 * data & 32 bytes of ECC data.
	 * 2. X'fer 64 bytes of Spare area from Memory to Flash.
	 * Read Operation Sequence for Large Block NAND
	 * ----------------------------------------------------------
	 * 1. Steps(1-4) of Read Operations repeate for four times
	 * which generates 16 DMA descriptors to X'fer 2048 bytes of
	 * data & 32 bytes of ECC data.
	 * 2. X'fer 64 bytes of Spare area from Flash to Memory.
	 */

	for (i = 0; i < size/CONFIG_SYS_NAND_ECCSIZE; i++) {
		dmalist_cur = &dmalist[i * 2];
		dmalist_cur_ecc = &dmalist[(i * 2) + 1];

		dmalist_cur->dma_src = (read ? (dmasrc) : (dmasrc + (i*256)));
		dmalist_cur->dma_dest = (read ? (dmadst + (i*256)) : dmadst);
		dmalist_cur->next_lli = lpc32xx_dmac_next_lli(dmalist_cur_ecc);
		dmalist_cur->next_ctrl = ctrl;

		dmalist_cur_ecc->dma_src = lpc32xx_dmac_set_ecc();
		dmalist_cur_ecc->dma_dest = (u32)&ecc_buffer[i];
		dmalist_cur_ecc->next_lli =
			lpc32xx_dmac_next_lli(&dmalist[(i * 2) + 2]);
		dmalist_cur_ecc->next_ctrl = ecc_ctrl;
	}

	if (i) { /* Data only transfer */
		dmalist_cur_ecc = &dmalist[(i * 2) - 1];
		dmalist_cur_ecc->next_lli = 0;
		dmalist_cur_ecc->next_ctrl |= DMAC_CHAN_INT_TC_EN;
		return;
	}

	/* OOB only transfer */
	if (read) {
		dmasrc = lpc32xx_dmac_set_dma_data();
		dmadst = (u32)buffer;
		oob_ctrl |= DMAC_CHAN_DEST_AUTOINC;
	} else {
		dmadst = lpc32xx_dmac_set_dma_data();
		dmasrc = (u32)buffer;
		oob_ctrl |= DMAC_CHAN_SRC_AUTOINC;
	}

	/* Read/ Write Spare Area Data To/From Flash */
	dmalist_cur = &dmalist[i * 2];
	dmalist_cur->dma_src = dmasrc;
	dmalist_cur->dma_dest = dmadst;
	dmalist_cur->next_lli = 0;
	dmalist_cur->next_ctrl = (oob_ctrl | DMAC_CHAN_INT_TC_EN);
}

static void lpc32xx_nand_xfer(struct mtd_info *mtd, const u8 *buf,
			      int len, int read)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	u32 config;
	int ret;

	/* DMA Channel Configuration */
	config = (read ? DMAC_CHAN_FLOW_D_P2M : DMAC_CHAN_FLOW_D_M2P) |
		(read ? DMAC_DEST_PERIP(0) : DMAC_DEST_PERIP(DMA_PERID_NAND1)) |
		(read ? DMAC_SRC_PERIP(DMA_PERID_NAND1) : DMAC_SRC_PERIP(0)) |
		DMAC_CHAN_ENABLE;

	/* Prepare DMA descriptors */
	lpc32xx_nand_dma_configure(chip, buf, len, read);

	/* Setup SLC controller and start transfer */
	if (read)
		setbits_le32(&lpc32xx_nand_slc_regs->cfg, CFG_DMA_DIR);
	else  /* NAND_ECC_WRITE */
		clrbits_le32(&lpc32xx_nand_slc_regs->cfg, CFG_DMA_DIR);
	setbits_le32(&lpc32xx_nand_slc_regs->cfg, CFG_DMA_BURST);

	/* Write length for new transfers */
	if (!((readl(&lpc32xx_nand_slc_regs->stat) & STAT_DMA_FIFO) |
	      readl(&lpc32xx_nand_slc_regs->tc))) {
		int tmp = (len != mtd->oobsize) ? mtd->oobsize : 0;
		writel(len + tmp, &lpc32xx_nand_slc_regs->tc);
	}

	setbits_le32(&lpc32xx_nand_slc_regs->ctrl, CTRL_DMA_START);

	/* Start DMA transfers */
	ret = lpc32xx_dma_start_xfer(dmachan, dmalist, config);
	if (unlikely(ret < 0))
		BUG();

	/* Wait for NAND to be ready */
	while (!lpc32xx_nand_dev_ready(mtd))
		;

	/* Wait till DMA transfer is DONE */
	if (lpc32xx_dma_wait_status(dmachan))
		pr_err("NAND DMA transfer error!\r\n");

	/* Stop DMA & HW ECC */
	clrbits_le32(&lpc32xx_nand_slc_regs->ctrl, CTRL_DMA_START);
	clrbits_le32(&lpc32xx_nand_slc_regs->cfg,
		     CFG_DMA_DIR | CFG_DMA_BURST | CFG_ECC_EN | CFG_DMA_ECC);
}

static u32 slc_ecc_copy_to_buffer(u8 *spare, const u32 *ecc, int count)
{
	int i;
	for (i = 0; i < (count * CONFIG_SYS_NAND_ECCBYTES);
	     i += CONFIG_SYS_NAND_ECCBYTES) {
		u32 ce = ecc[i / CONFIG_SYS_NAND_ECCBYTES];
		ce = ~(ce << 2) & 0xFFFFFF;
		spare[i+2] = (u8)(ce & 0xFF); ce >>= 8;
		spare[i+1] = (u8)(ce & 0xFF); ce >>= 8;
		spare[i]   = (u8)(ce & 0xFF);
	}
	return 0;
}

static int lpc32xx_ecc_calculate(struct mtd_info *mtd, const uint8_t *dat,
				 uint8_t *ecc_code)
{
	return slc_ecc_copy_to_buffer(ecc_code, ecc_buffer, ECCSTEPS);
}

/*
 * Enables and prepares SLC NAND controller
 * for doing data transfers with H/W ECC enabled.
 */
static void lpc32xx_hwecc_enable(struct mtd_info *mtd, int mode)
{
	/* Clear ECC */
	writel(CTRL_ECC_CLEAR, &lpc32xx_nand_slc_regs->ctrl);

	/* Setup SLC controller for H/W ECC operations */
	setbits_le32(&lpc32xx_nand_slc_regs->cfg, CFG_ECC_EN | CFG_DMA_ECC);
}

/*
 * lpc32xx_correct_data - [NAND Interface] Detect and correct bit error(s)
 * mtd:	MTD block structure
 * dat:	raw data read from the chip
 * read_ecc:	ECC from the chip
 * calc_ecc:	the ECC calculated from raw data
 *
 * Detect and correct a 1 bit error for 256 byte block
 */
int lpc32xx_correct_data(struct mtd_info *mtd, u_char *dat,
			 u_char *read_ecc, u_char *calc_ecc)
{
	unsigned int i;
	int ret1, ret2 = 0;
	u_char *r = read_ecc;
	u_char *c = calc_ecc;
	u16 data_offset = 0;

	for (i = 0 ; i < ECCSTEPS ; i++) {
		r += CONFIG_SYS_NAND_ECCBYTES;
		c += CONFIG_SYS_NAND_ECCBYTES;
		data_offset += CONFIG_SYS_NAND_ECCSIZE;

		ret1 = nand_correct_data(mtd, dat + data_offset, r, c);
		if (ret1 < 0)
			return -EBADMSG;
		else
			ret2 += ret1;
	}

	return ret2;
}

static void lpc32xx_dma_read_buf(struct mtd_info *mtd, uint8_t *buf, int len)
{
	lpc32xx_nand_xfer(mtd, buf, len, 1);
}

static void lpc32xx_dma_write_buf(struct mtd_info *mtd, const uint8_t *buf,
				  int len)
{
	lpc32xx_nand_xfer(mtd, buf, len, 0);
}

/* Reuse the logic from "nand_read_page_hwecc()" */
static int lpc32xx_read_page_hwecc(struct mtd_info *mtd, struct nand_chip *chip,
				uint8_t *buf, int oob_required, int page)
{
	int i;
	int stat;
	uint8_t *p = buf;
	uint8_t *ecc_calc = chip->buffers->ecccalc;
	uint8_t *ecc_code = chip->buffers->ecccode;
	uint32_t *eccpos = chip->ecc.layout->eccpos;
	unsigned int max_bitflips = 0;

	/*
	 * As per the "LPC32x0 and LPC32x0/01 User manual" table 173 notes
	 * and section 9.7, the NAND SLC & DMA allowed single DMA transaction
	 * of a page size using DMA controller scatter/gather mode through
	 * linked list; the ECC read is done without any software intervention.
	 */

	lpc32xx_hwecc_enable(mtd, NAND_ECC_READ);
	lpc32xx_dma_read_buf(mtd, p, chip->ecc.size * chip->ecc.steps);
	lpc32xx_ecc_calculate(mtd, p, &ecc_calc[0]);
	lpc32xx_dma_read_buf(mtd, chip->oob_poi, mtd->oobsize);

	for (i = 0; i < chip->ecc.total; i++)
		ecc_code[i] = chip->oob_poi[eccpos[i]];

	stat = chip->ecc.correct(mtd, p, &ecc_code[0], &ecc_calc[0]);
	if (stat < 0)
		mtd->ecc_stats.failed++;
	else {
		mtd->ecc_stats.corrected += stat;
		max_bitflips = max_t(unsigned int, max_bitflips, stat);
	}

	return max_bitflips;
}

/* Reuse the logic from "nand_write_page_hwecc()" */
static int lpc32xx_write_page_hwecc(struct mtd_info *mtd,
				    struct nand_chip *chip,
				    const uint8_t *buf, int oob_required,
				    int page)
{
	int i;
	uint8_t *ecc_calc = chip->buffers->ecccalc;
	const uint8_t *p = buf;
	uint32_t *eccpos = chip->ecc.layout->eccpos;

	/*
	 * As per the "LPC32x0 and LPC32x0/01 User manual" table 173 notes
	 * and section 9.7, the NAND SLC & DMA allowed single DMA transaction
	 * of a page size using DMA controller scatter/gather mode through
	 * linked list; the ECC read is done without any software intervention.
	 */

	lpc32xx_hwecc_enable(mtd, NAND_ECC_WRITE);
	lpc32xx_dma_write_buf(mtd, p, chip->ecc.size * chip->ecc.steps);
	lpc32xx_ecc_calculate(mtd, p, &ecc_calc[0]);

	for (i = 0; i < chip->ecc.total; i++)
		chip->oob_poi[eccpos[i]] = ecc_calc[i];

	lpc32xx_dma_write_buf(mtd, chip->oob_poi, mtd->oobsize);

	return 0;
}
#else
static void lpc32xx_read_buf(struct mtd_info *mtd, uint8_t *buf, int len)
{
	while (len-- > 0)
		*buf++ = readl(&lpc32xx_nand_slc_regs->data);
}

static void lpc32xx_write_buf(struct mtd_info *mtd, const uint8_t *buf, int len)
{
	while (len-- > 0)
		writel(*buf++, &lpc32xx_nand_slc_regs->data);
}
#endif

static uint8_t lpc32xx_read_byte(struct mtd_info *mtd)
{
	return readl(&lpc32xx_nand_slc_regs->data);
}

static void lpc32xx_write_byte(struct mtd_info *mtd, uint8_t byte)
{
	writel(byte, &lpc32xx_nand_slc_regs->data);
}

/*
 * LPC32xx has only one SLC NAND controller, don't utilize
 * CONFIG_SYS_NAND_SELF_INIT to be able to reuse this function
 * both in SPL NAND and U-Boot images.
 */
int board_nand_init(struct nand_chip *lpc32xx_chip)
{
#if defined(CONFIG_DMA_LPC32XX) && !defined(CONFIG_SPL_BUILD)
	int ret;

	/* Acquire a channel for our use */
	ret = lpc32xx_dma_get_channel();
	if (unlikely(ret < 0)) {
		pr_info("Unable to get free DMA channel for NAND transfers\n");
		return -1;
	}
	dmachan = (unsigned int)ret;
#endif

	lpc32xx_chip->cmd_ctrl  = lpc32xx_nand_cmd_ctrl;
	lpc32xx_chip->dev_ready = lpc32xx_nand_dev_ready;

	/*
	 * The implementation of these functions is quite common, but
	 * they MUST be defined, because access to data register
	 * is strictly 32-bit aligned.
	 */
	lpc32xx_chip->read_byte  = lpc32xx_read_byte;
	lpc32xx_chip->write_byte = lpc32xx_write_byte;

#if defined(CONFIG_DMA_LPC32XX) && !defined(CONFIG_SPL_BUILD)
	/* Hardware ECC calculation is supported when DMA driver is selected */
	lpc32xx_chip->ecc.mode		= NAND_ECC_HW;

	lpc32xx_chip->read_buf		= lpc32xx_dma_read_buf;
	lpc32xx_chip->write_buf		= lpc32xx_dma_write_buf;

	lpc32xx_chip->ecc.calculate	= lpc32xx_ecc_calculate;
	lpc32xx_chip->ecc.correct	= lpc32xx_correct_data;
	lpc32xx_chip->ecc.hwctl		= lpc32xx_hwecc_enable;
	lpc32xx_chip->chip_delay	= 2000;

	lpc32xx_chip->ecc.read_page	= lpc32xx_read_page_hwecc;
	lpc32xx_chip->ecc.write_page	= lpc32xx_write_page_hwecc;
	lpc32xx_chip->options		|= NAND_NO_SUBPAGE_WRITE;
#else
	/*
	 * Hardware ECC calculation is not supported by the driver,
	 * because it requires DMA support, see LPC32x0 User Manual,
	 * note after SLC_ECC register description (UM10326, p.198)
	 */
	lpc32xx_chip->ecc.mode = NAND_ECC_SOFT;

	/*
	 * The implementation of these functions is quite common, but
	 * they MUST be defined, because access to data register
	 * is strictly 32-bit aligned.
	 */
	lpc32xx_chip->read_buf   = lpc32xx_read_buf;
	lpc32xx_chip->write_buf  = lpc32xx_write_buf;
#endif

	/*
	 * These values are predefined
	 * for both small and large page NAND flash devices.
	 */
	lpc32xx_chip->ecc.size     = CONFIG_SYS_NAND_ECCSIZE;
	lpc32xx_chip->ecc.bytes    = CONFIG_SYS_NAND_ECCBYTES;
	lpc32xx_chip->ecc.strength = 1;

	if (CONFIG_SYS_NAND_PAGE_SIZE != NAND_LARGE_BLOCK_PAGE_SIZE)
		lpc32xx_chip->ecc.layout = &lpc32xx_nand_oob_16;

#if defined(CONFIG_SYS_NAND_USE_FLASH_BBT)
	lpc32xx_chip->bbt_options |= NAND_BBT_USE_FLASH;
#endif

	/* Initialize NAND interface */
	lpc32xx_nand_init();

	return 0;
}
