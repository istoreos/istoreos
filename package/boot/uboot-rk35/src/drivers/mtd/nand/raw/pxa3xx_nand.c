/*
 * drivers/mtd/nand/raw/pxa3xx_nand.c
 *
 * Copyright © 2005 Intel Corporation
 * Copyright © 2006 Marvell International Ltd.
 *
 * SPDX-License-Identifier:	GPL-2.0
 */

#include <common.h>
#include <malloc.h>
#include <fdtdec.h>
#include <nand.h>
#include <linux/errno.h>
#include <asm/io.h>
#include <asm/arch/cpu.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/rawnand.h>
#include <linux/types.h>

#include "pxa3xx_nand.h"

DECLARE_GLOBAL_DATA_PTR;

#define TIMEOUT_DRAIN_FIFO	5	/* in ms */
#define	CHIP_DELAY_TIMEOUT	200
#define NAND_STOP_DELAY		40

/*
 * Define a buffer size for the initial command that detects the flash device:
 * STATUS, READID and PARAM.
 * ONFI param page is 256 bytes, and there are three redundant copies
 * to be read. JEDEC param page is 512 bytes, and there are also three
 * redundant copies to be read.
 * Hence this buffer should be at least 512 x 3. Let's pick 2048.
 */
#define INIT_BUFFER_SIZE	2048

/* registers and bit definitions */
#define NDCR		(0x00) /* Control register */
#define NDTR0CS0	(0x04) /* Timing Parameter 0 for CS0 */
#define NDTR1CS0	(0x0C) /* Timing Parameter 1 for CS0 */
#define NDSR		(0x14) /* Status Register */
#define NDPCR		(0x18) /* Page Count Register */
#define NDBDR0		(0x1C) /* Bad Block Register 0 */
#define NDBDR1		(0x20) /* Bad Block Register 1 */
#define NDECCCTRL	(0x28) /* ECC control */
#define NDDB		(0x40) /* Data Buffer */
#define NDCB0		(0x48) /* Command Buffer0 */
#define NDCB1		(0x4C) /* Command Buffer1 */
#define NDCB2		(0x50) /* Command Buffer2 */

#define NDCR_SPARE_EN		(0x1 << 31)
#define NDCR_ECC_EN		(0x1 << 30)
#define NDCR_DMA_EN		(0x1 << 29)
#define NDCR_ND_RUN		(0x1 << 28)
#define NDCR_DWIDTH_C		(0x1 << 27)
#define NDCR_DWIDTH_M		(0x1 << 26)
#define NDCR_PAGE_SZ		(0x1 << 24)
#define NDCR_NCSX		(0x1 << 23)
#define NDCR_ND_MODE		(0x3 << 21)
#define NDCR_NAND_MODE		(0x0)
#define NDCR_CLR_PG_CNT		(0x1 << 20)
#define NFCV1_NDCR_ARB_CNTL	(0x1 << 19)
#define NDCR_RD_ID_CNT_MASK	(0x7 << 16)
#define NDCR_RD_ID_CNT(x)	(((x) << 16) & NDCR_RD_ID_CNT_MASK)

#define NDCR_RA_START		(0x1 << 15)
#define NDCR_PG_PER_BLK		(0x1 << 14)
#define NDCR_ND_ARB_EN		(0x1 << 12)
#define NDCR_INT_MASK           (0xFFF)

#define NDSR_MASK		(0xfff)
#define NDSR_ERR_CNT_OFF	(16)
#define NDSR_ERR_CNT_MASK       (0x1f)
#define NDSR_ERR_CNT(sr)	((sr >> NDSR_ERR_CNT_OFF) & NDSR_ERR_CNT_MASK)
#define NDSR_RDY                (0x1 << 12)
#define NDSR_FLASH_RDY          (0x1 << 11)
#define NDSR_CS0_PAGED		(0x1 << 10)
#define NDSR_CS1_PAGED		(0x1 << 9)
#define NDSR_CS0_CMDD		(0x1 << 8)
#define NDSR_CS1_CMDD		(0x1 << 7)
#define NDSR_CS0_BBD		(0x1 << 6)
#define NDSR_CS1_BBD		(0x1 << 5)
#define NDSR_UNCORERR		(0x1 << 4)
#define NDSR_CORERR		(0x1 << 3)
#define NDSR_WRDREQ		(0x1 << 2)
#define NDSR_RDDREQ		(0x1 << 1)
#define NDSR_WRCMDREQ		(0x1)

#define NDCB0_LEN_OVRD		(0x1 << 28)
#define NDCB0_ST_ROW_EN         (0x1 << 26)
#define NDCB0_AUTO_RS		(0x1 << 25)
#define NDCB0_CSEL		(0x1 << 24)
#define NDCB0_EXT_CMD_TYPE_MASK	(0x7 << 29)
#define NDCB0_EXT_CMD_TYPE(x)	(((x) << 29) & NDCB0_EXT_CMD_TYPE_MASK)
#define NDCB0_CMD_TYPE_MASK	(0x7 << 21)
#define NDCB0_CMD_TYPE(x)	(((x) << 21) & NDCB0_CMD_TYPE_MASK)
#define NDCB0_NC		(0x1 << 20)
#define NDCB0_DBC		(0x1 << 19)
#define NDCB0_ADDR_CYC_MASK	(0x7 << 16)
#define NDCB0_ADDR_CYC(x)	(((x) << 16) & NDCB0_ADDR_CYC_MASK)
#define NDCB0_CMD2_MASK		(0xff << 8)
#define NDCB0_CMD1_MASK		(0xff)
#define NDCB0_ADDR_CYC_SHIFT	(16)

#define EXT_CMD_TYPE_DISPATCH	6 /* Command dispatch */
#define EXT_CMD_TYPE_NAKED_RW	5 /* Naked read or Naked write */
#define EXT_CMD_TYPE_READ	4 /* Read */
#define EXT_CMD_TYPE_DISP_WR	4 /* Command dispatch with write */
#define EXT_CMD_TYPE_FINAL	3 /* Final command */
#define EXT_CMD_TYPE_LAST_RW	1 /* Last naked read/write */
#define EXT_CMD_TYPE_MONO	0 /* Monolithic read/write */

/*
 * This should be large enough to read 'ONFI' and 'JEDEC'.
 * Let's use 7 bytes, which is the maximum ID count supported
 * by the controller (see NDCR_RD_ID_CNT_MASK).
 */
#define READ_ID_BYTES		7

/* macros for registers read/write */
#define nand_writel(info, off, val)	\
	writel((val), (info)->mmio_base + (off))

#define nand_readl(info, off)		\
	readl((info)->mmio_base + (off))

/* error code and state */
enum {
	ERR_NONE	= 0,
	ERR_DMABUSERR	= -1,
	ERR_SENDCMD	= -2,
	ERR_UNCORERR	= -3,
	ERR_BBERR	= -4,
	ERR_CORERR	= -5,
};

enum {
	STATE_IDLE = 0,
	STATE_PREPARED,
	STATE_CMD_HANDLE,
	STATE_DMA_READING,
	STATE_DMA_WRITING,
	STATE_DMA_DONE,
	STATE_PIO_READING,
	STATE_PIO_WRITING,
	STATE_CMD_DONE,
	STATE_READY,
};

enum pxa3xx_nand_variant {
	PXA3XX_NAND_VARIANT_PXA,
	PXA3XX_NAND_VARIANT_ARMADA370,
};

struct pxa3xx_nand_host {
	struct nand_chip	chip;
	void			*info_data;

	/* page size of attached chip */
	int			use_ecc;
	int			cs;

	/* calculated from pxa3xx_nand_flash data */
	unsigned int		col_addr_cycles;
	unsigned int		row_addr_cycles;
};

struct pxa3xx_nand_info {
	struct nand_hw_control	controller;
	struct pxa3xx_nand_platform_data *pdata;

	struct clk		*clk;
	void __iomem		*mmio_base;
	unsigned long		mmio_phys;
	int			cmd_complete, dev_ready;

	unsigned int		buf_start;
	unsigned int		buf_count;
	unsigned int		buf_size;
	unsigned int		data_buff_pos;
	unsigned int		oob_buff_pos;

	unsigned char		*data_buff;
	unsigned char		*oob_buff;

	struct pxa3xx_nand_host *host[NUM_CHIP_SELECT];
	unsigned int		state;

	/*
	 * This driver supports NFCv1 (as found in PXA SoC)
	 * and NFCv2 (as found in Armada 370/XP SoC).
	 */
	enum pxa3xx_nand_variant variant;

	int			cs;
	int			use_ecc;	/* use HW ECC ? */
	int			force_raw;	/* prevent use_ecc to be set */
	int			ecc_bch;	/* using BCH ECC? */
	int			use_spare;	/* use spare ? */
	int			need_wait;

	/* Amount of real data per full chunk */
	unsigned int		chunk_size;

	/* Amount of spare data per full chunk */
	unsigned int		spare_size;

	/* Number of full chunks (i.e chunk_size + spare_size) */
	unsigned int            nfullchunks;

	/*
	 * Total number of chunks. If equal to nfullchunks, then there
	 * are only full chunks. Otherwise, there is one last chunk of
	 * size (last_chunk_size + last_spare_size)
	 */
	unsigned int            ntotalchunks;

	/* Amount of real data in the last chunk */
	unsigned int		last_chunk_size;

	/* Amount of spare data in the last chunk */
	unsigned int		last_spare_size;

	unsigned int		ecc_size;
	unsigned int		ecc_err_cnt;
	unsigned int		max_bitflips;
	int			retcode;

	/*
	 * Variables only valid during command
	 * execution. step_chunk_size and step_spare_size is the
	 * amount of real data and spare data in the current
	 * chunk. cur_chunk is the current chunk being
	 * read/programmed.
	 */
	unsigned int		step_chunk_size;
	unsigned int		step_spare_size;
	unsigned int            cur_chunk;

	/* cached register value */
	uint32_t		reg_ndcr;
	uint32_t		ndtr0cs0;
	uint32_t		ndtr1cs0;

	/* generated NDCBx register values */
	uint32_t		ndcb0;
	uint32_t		ndcb1;
	uint32_t		ndcb2;
	uint32_t		ndcb3;
};

static struct pxa3xx_nand_timing timing[] = {
	/*
	 * tCH	Enable signal hold time
	 * tCS	Enable signal setup time
	 * tWH	ND_nWE high duration
	 * tWP	ND_nWE pulse time
	 * tRH	ND_nRE high duration
	 * tRP	ND_nRE pulse width
	 * tR	ND_nWE high to ND_nRE low for read
	 * tWHR	ND_nWE high to ND_nRE low for status read
	 * tAR	ND_ALE low to ND_nRE low delay
	 */
	/*ch  cs  wh  wp   rh  rp   r      whr  ar */
	{ 40, 80, 60, 100, 80, 100, 90000, 400, 40, },
	{ 10,  0, 20,  40, 30,  40, 11123, 110, 10, },
	{ 10, 25, 15,  25, 15,  30, 25000,  60, 10, },
	{ 10, 35, 15,  25, 15,  25, 25000,  60, 10, },
	{  5, 20, 10,  12, 10,  12, 25000,  60, 10, },
};

static struct pxa3xx_nand_flash builtin_flash_types[] = {
	/*
	 * chip_id
	 * flash_width	Width of Flash memory (DWIDTH_M)
	 * dfc_width	Width of flash controller(DWIDTH_C)
	 * *timing
	 * http://www.linux-mtd.infradead.org/nand-data/nanddata.html
	 */
	{ 0x46ec, 16, 16, &timing[1] },
	{ 0xdaec,  8,  8, &timing[1] },
	{ 0xd7ec,  8,  8, &timing[1] },
	{ 0xa12c,  8,  8, &timing[2] },
	{ 0xb12c, 16, 16, &timing[2] },
	{ 0xdc2c,  8,  8, &timing[2] },
	{ 0xcc2c, 16, 16, &timing[2] },
	{ 0xba20, 16, 16, &timing[3] },
	{ 0xda98,  8,  8, &timing[4] },
};

#ifdef CONFIG_SYS_NAND_USE_FLASH_BBT
static u8 bbt_pattern[] = {'M', 'V', 'B', 'b', 't', '0' };
static u8 bbt_mirror_pattern[] = {'1', 't', 'b', 'B', 'V', 'M' };

static struct nand_bbt_descr bbt_main_descr = {
	.options = NAND_BBT_LASTBLOCK | NAND_BBT_CREATE | NAND_BBT_WRITE
		| NAND_BBT_2BIT | NAND_BBT_VERSION,
	.offs =	8,
	.len = 6,
	.veroffs = 14,
	.maxblocks = 8,		/* Last 8 blocks in each chip */
	.pattern = bbt_pattern
};

static struct nand_bbt_descr bbt_mirror_descr = {
	.options = NAND_BBT_LASTBLOCK | NAND_BBT_CREATE | NAND_BBT_WRITE
		| NAND_BBT_2BIT | NAND_BBT_VERSION,
	.offs =	8,
	.len = 6,
	.veroffs = 14,
	.maxblocks = 8,		/* Last 8 blocks in each chip */
	.pattern = bbt_mirror_pattern
};
#endif

static struct nand_ecclayout ecc_layout_2KB_bch4bit = {
	.eccbytes = 32,
	.eccpos = {
		32, 33, 34, 35, 36, 37, 38, 39,
		40, 41, 42, 43, 44, 45, 46, 47,
		48, 49, 50, 51, 52, 53, 54, 55,
		56, 57, 58, 59, 60, 61, 62, 63},
	.oobfree = { {2, 30} }
};

static struct nand_ecclayout ecc_layout_2KB_bch8bit = {
	.eccbytes = 64,
	.eccpos = {
		32, 33, 34, 35, 36, 37, 38, 39,
		40, 41, 42, 43, 44, 45, 46, 47,
		48, 49, 50, 51, 52, 53, 54, 55,
		56, 57, 58, 59, 60, 61, 62, 63,
		64, 65, 66, 67, 68, 69, 70, 71,
		72, 73, 74, 75, 76, 77, 78, 79,
		80, 81, 82, 83, 84, 85, 86, 87,
		88, 89, 90, 91, 92, 93, 94, 95},
	.oobfree = { {1, 4}, {6, 26} }
};

static struct nand_ecclayout ecc_layout_4KB_bch4bit = {
	.eccbytes = 64,
	.eccpos = {
		32,  33,  34,  35,  36,  37,  38,  39,
		40,  41,  42,  43,  44,  45,  46,  47,
		48,  49,  50,  51,  52,  53,  54,  55,
		56,  57,  58,  59,  60,  61,  62,  63,
		96,  97,  98,  99,  100, 101, 102, 103,
		104, 105, 106, 107, 108, 109, 110, 111,
		112, 113, 114, 115, 116, 117, 118, 119,
		120, 121, 122, 123, 124, 125, 126, 127},
	/* Bootrom looks in bytes 0 & 5 for bad blocks */
	.oobfree = { {6, 26}, { 64, 32} }
};

static struct nand_ecclayout ecc_layout_8KB_bch4bit = {
	.eccbytes = 128,
	.eccpos = {
		32,  33,  34,  35,  36,  37,  38,  39,
		40,  41,  42,  43,  44,  45,  46,  47,
		48,  49,  50,  51,  52,  53,  54,  55,
		56,  57,  58,  59,  60,  61,  62,  63,

		96,  97,  98,  99,  100, 101, 102, 103,
		104, 105, 106, 107, 108, 109, 110, 111,
		112, 113, 114, 115, 116, 117, 118, 119,
		120, 121, 122, 123, 124, 125, 126, 127,

		160, 161, 162, 163, 164, 165, 166, 167,
		168, 169, 170, 171, 172, 173, 174, 175,
		176, 177, 178, 179, 180, 181, 182, 183,
		184, 185, 186, 187, 188, 189, 190, 191,

		224, 225, 226, 227, 228, 229, 230, 231,
		232, 233, 234, 235, 236, 237, 238, 239,
		240, 241, 242, 243, 244, 245, 246, 247,
		248, 249, 250, 251, 252, 253, 254, 255},

	/* Bootrom looks in bytes 0 & 5 for bad blocks */
	.oobfree = { {1, 4}, {6, 26}, { 64, 32}, {128, 32}, {192, 32} }
};

static struct nand_ecclayout ecc_layout_4KB_bch8bit = {
	.eccbytes = 128,
	.eccpos = {
		32,  33,  34,  35,  36,  37,  38,  39,
		40,  41,  42,  43,  44,  45,  46,  47,
		48,  49,  50,  51,  52,  53,  54,  55,
		56,  57,  58,  59,  60,  61,  62,  63},
	.oobfree = { }
};

static struct nand_ecclayout ecc_layout_8KB_bch8bit = {
	.eccbytes = 256,
	.eccpos = {},
	/* HW ECC handles all ECC data and all spare area is free for OOB */
	.oobfree = {{0, 160} }
};

#define NDTR0_tCH(c)	(min((c), 7) << 19)
#define NDTR0_tCS(c)	(min((c), 7) << 16)
#define NDTR0_tWH(c)	(min((c), 7) << 11)
#define NDTR0_tWP(c)	(min((c), 7) << 8)
#define NDTR0_tRH(c)	(min((c), 7) << 3)
#define NDTR0_tRP(c)	(min((c), 7) << 0)

#define NDTR1_tR(c)	(min((c), 65535) << 16)
#define NDTR1_tWHR(c)	(min((c), 15) << 4)
#define NDTR1_tAR(c)	(min((c), 15) << 0)

/* convert nano-seconds to nand flash controller clock cycles */
#define ns2cycle(ns, clk)	(int)((ns) * (clk / 1000000) / 1000)

static enum pxa3xx_nand_variant pxa3xx_nand_get_variant(void)
{
	/* We only support the Armada 370/XP/38x for now */
	return PXA3XX_NAND_VARIANT_ARMADA370;
}

static void pxa3xx_nand_set_timing(struct pxa3xx_nand_host *host,
				   const struct pxa3xx_nand_timing *t)
{
	struct pxa3xx_nand_info *info = host->info_data;
	unsigned long nand_clk = mvebu_get_nand_clock();
	uint32_t ndtr0, ndtr1;

	ndtr0 = NDTR0_tCH(ns2cycle(t->tCH, nand_clk)) |
		NDTR0_tCS(ns2cycle(t->tCS, nand_clk)) |
		NDTR0_tWH(ns2cycle(t->tWH, nand_clk)) |
		NDTR0_tWP(ns2cycle(t->tWP, nand_clk)) |
		NDTR0_tRH(ns2cycle(t->tRH, nand_clk)) |
		NDTR0_tRP(ns2cycle(t->tRP, nand_clk));

	ndtr1 = NDTR1_tR(ns2cycle(t->tR, nand_clk)) |
		NDTR1_tWHR(ns2cycle(t->tWHR, nand_clk)) |
		NDTR1_tAR(ns2cycle(t->tAR, nand_clk));

	info->ndtr0cs0 = ndtr0;
	info->ndtr1cs0 = ndtr1;
	nand_writel(info, NDTR0CS0, ndtr0);
	nand_writel(info, NDTR1CS0, ndtr1);
}

static void pxa3xx_nand_set_sdr_timing(struct pxa3xx_nand_host *host,
				       const struct nand_sdr_timings *t)
{
	struct pxa3xx_nand_info *info = host->info_data;
	struct nand_chip *chip = &host->chip;
	unsigned long nand_clk = mvebu_get_nand_clock();
	uint32_t ndtr0, ndtr1;

	u32 tCH_min = DIV_ROUND_UP(t->tCH_min, 1000);
	u32 tCS_min = DIV_ROUND_UP(t->tCS_min, 1000);
	u32 tWH_min = DIV_ROUND_UP(t->tWH_min, 1000);
	u32 tWP_min = DIV_ROUND_UP(t->tWC_min - t->tWH_min, 1000);
	u32 tREH_min = DIV_ROUND_UP(t->tREH_min, 1000);
	u32 tRP_min = DIV_ROUND_UP(t->tRC_min - t->tREH_min, 1000);
	u32 tR = chip->chip_delay * 1000;
	u32 tWHR_min = DIV_ROUND_UP(t->tWHR_min, 1000);
	u32 tAR_min = DIV_ROUND_UP(t->tAR_min, 1000);

	/* fallback to a default value if tR = 0 */
	if (!tR)
		tR = 20000;

	ndtr0 = NDTR0_tCH(ns2cycle(tCH_min, nand_clk)) |
		NDTR0_tCS(ns2cycle(tCS_min, nand_clk)) |
		NDTR0_tWH(ns2cycle(tWH_min, nand_clk)) |
		NDTR0_tWP(ns2cycle(tWP_min, nand_clk)) |
		NDTR0_tRH(ns2cycle(tREH_min, nand_clk)) |
		NDTR0_tRP(ns2cycle(tRP_min, nand_clk));

	ndtr1 = NDTR1_tR(ns2cycle(tR, nand_clk)) |
		NDTR1_tWHR(ns2cycle(tWHR_min, nand_clk)) |
		NDTR1_tAR(ns2cycle(tAR_min, nand_clk));

	info->ndtr0cs0 = ndtr0;
	info->ndtr1cs0 = ndtr1;
	nand_writel(info, NDTR0CS0, ndtr0);
	nand_writel(info, NDTR1CS0, ndtr1);
}

static int pxa3xx_nand_init_timings(struct pxa3xx_nand_host *host)
{
	const struct nand_sdr_timings *timings;
	struct nand_chip *chip = &host->chip;
	struct pxa3xx_nand_info *info = host->info_data;
	const struct pxa3xx_nand_flash *f = NULL;
	struct mtd_info *mtd = nand_to_mtd(&host->chip);
	int mode, id, ntypes, i;

	mode = onfi_get_async_timing_mode(chip);
	if (mode == ONFI_TIMING_MODE_UNKNOWN) {
		ntypes = ARRAY_SIZE(builtin_flash_types);

		chip->cmdfunc(mtd, NAND_CMD_READID, 0x00, -1);

		id = chip->read_byte(mtd);
		id |= chip->read_byte(mtd) << 0x8;

		for (i = 0; i < ntypes; i++) {
			f = &builtin_flash_types[i];

			if (f->chip_id == id)
				break;
		}

		if (i == ntypes) {
			dev_err(&info->pdev->dev, "Error: timings not found\n");
			return -EINVAL;
		}

		pxa3xx_nand_set_timing(host, f->timing);

		if (f->flash_width == 16) {
			info->reg_ndcr |= NDCR_DWIDTH_M;
			chip->options |= NAND_BUSWIDTH_16;
		}

		info->reg_ndcr |= (f->dfc_width == 16) ? NDCR_DWIDTH_C : 0;
	} else {
		mode = fls(mode) - 1;
		if (mode < 0)
			mode = 0;

		timings = onfi_async_timing_mode_to_sdr_timings(mode);
		if (IS_ERR(timings))
			return PTR_ERR(timings);

		pxa3xx_nand_set_sdr_timing(host, timings);
	}

	return 0;
}

/**
 * NOTE: it is a must to set ND_RUN first, then write
 * command buffer, otherwise, it does not work.
 * We enable all the interrupt at the same time, and
 * let pxa3xx_nand_irq to handle all logic.
 */
static void pxa3xx_nand_start(struct pxa3xx_nand_info *info)
{
	uint32_t ndcr;

	ndcr = info->reg_ndcr;

	if (info->use_ecc) {
		ndcr |= NDCR_ECC_EN;
		if (info->ecc_bch)
			nand_writel(info, NDECCCTRL, 0x1);
	} else {
		ndcr &= ~NDCR_ECC_EN;
		if (info->ecc_bch)
			nand_writel(info, NDECCCTRL, 0x0);
	}

	ndcr &= ~NDCR_DMA_EN;

	if (info->use_spare)
		ndcr |= NDCR_SPARE_EN;
	else
		ndcr &= ~NDCR_SPARE_EN;

	ndcr |= NDCR_ND_RUN;

	/* clear status bits and run */
	nand_writel(info, NDSR, NDSR_MASK);
	nand_writel(info, NDCR, 0);
	nand_writel(info, NDCR, ndcr);
}

static void disable_int(struct pxa3xx_nand_info *info, uint32_t int_mask)
{
	uint32_t ndcr;

	ndcr = nand_readl(info, NDCR);
	nand_writel(info, NDCR, ndcr | int_mask);
}

static void drain_fifo(struct pxa3xx_nand_info *info, void *data, int len)
{
	if (info->ecc_bch && !info->force_raw) {
		u32 ts;

		/*
		 * According to the datasheet, when reading from NDDB
		 * with BCH enabled, after each 32 bytes reads, we
		 * have to make sure that the NDSR.RDDREQ bit is set.
		 *
		 * Drain the FIFO 8 32 bits reads at a time, and skip
		 * the polling on the last read.
		 */
		while (len > 8) {
			readsl(info->mmio_base + NDDB, data, 8);

			ts = get_timer(0);
			while (!(nand_readl(info, NDSR) & NDSR_RDDREQ)) {
				if (get_timer(ts) > TIMEOUT_DRAIN_FIFO) {
					dev_err(&info->pdev->dev,
						"Timeout on RDDREQ while draining the FIFO\n");
					return;
				}
			}

			data += 32;
			len -= 8;
		}
	}

	readsl(info->mmio_base + NDDB, data, len);
}

static void handle_data_pio(struct pxa3xx_nand_info *info)
{
	int data_len = info->step_chunk_size;

	/*
	 * In raw mode, include the spare area and the ECC bytes that are not
	 * consumed by the controller in the data section. Do not reorganize
	 * here, do it in the ->read_page_raw() handler instead.
	 */
	if (info->force_raw)
		data_len += info->step_spare_size + info->ecc_size;

	switch (info->state) {
	case STATE_PIO_WRITING:
		if (info->step_chunk_size)
			writesl(info->mmio_base + NDDB,
				info->data_buff + info->data_buff_pos,
				DIV_ROUND_UP(data_len, 4));

		if (info->step_spare_size)
			writesl(info->mmio_base + NDDB,
				info->oob_buff + info->oob_buff_pos,
				DIV_ROUND_UP(info->step_spare_size, 4));
		break;
	case STATE_PIO_READING:
		if (info->step_chunk_size)
			drain_fifo(info,
				   info->data_buff + info->data_buff_pos,
				   DIV_ROUND_UP(data_len, 4));

		if (info->force_raw)
			break;

		if (info->step_spare_size)
			drain_fifo(info,
				   info->oob_buff + info->oob_buff_pos,
				   DIV_ROUND_UP(info->step_spare_size, 4));
		break;
	default:
		dev_err(&info->pdev->dev, "%s: invalid state %d\n", __func__,
				info->state);
		BUG();
	}

	/* Update buffer pointers for multi-page read/write */
	info->data_buff_pos += data_len;
	info->oob_buff_pos += info->step_spare_size;
}

static void pxa3xx_nand_irq_thread(struct pxa3xx_nand_info *info)
{
	handle_data_pio(info);

	info->state = STATE_CMD_DONE;
	nand_writel(info, NDSR, NDSR_WRDREQ | NDSR_RDDREQ);
}

static irqreturn_t pxa3xx_nand_irq(struct pxa3xx_nand_info *info)
{
	unsigned int status, is_completed = 0, is_ready = 0;
	unsigned int ready, cmd_done;
	irqreturn_t ret = IRQ_HANDLED;

	if (info->cs == 0) {
		ready           = NDSR_FLASH_RDY;
		cmd_done        = NDSR_CS0_CMDD;
	} else {
		ready           = NDSR_RDY;
		cmd_done        = NDSR_CS1_CMDD;
	}

	/* TODO - find out why we need the delay during write operation. */
	ndelay(1);

	status = nand_readl(info, NDSR);

	if (status & NDSR_UNCORERR)
		info->retcode = ERR_UNCORERR;
	if (status & NDSR_CORERR) {
		info->retcode = ERR_CORERR;
		if (info->variant == PXA3XX_NAND_VARIANT_ARMADA370 &&
		    info->ecc_bch)
			info->ecc_err_cnt = NDSR_ERR_CNT(status);
		else
			info->ecc_err_cnt = 1;

		/*
		 * Each chunk composing a page is corrected independently,
		 * and we need to store maximum number of corrected bitflips
		 * to return it to the MTD layer in ecc.read_page().
		 */
		info->max_bitflips = max_t(unsigned int,
					   info->max_bitflips,
					   info->ecc_err_cnt);
	}
	if (status & (NDSR_RDDREQ | NDSR_WRDREQ)) {
		info->state = (status & NDSR_RDDREQ) ?
			STATE_PIO_READING : STATE_PIO_WRITING;
		/* Call the IRQ thread in U-Boot directly */
		pxa3xx_nand_irq_thread(info);
		return 0;
	}
	if (status & cmd_done) {
		info->state = STATE_CMD_DONE;
		is_completed = 1;
	}
	if (status & ready) {
		info->state = STATE_READY;
		is_ready = 1;
	}

	/*
	 * Clear all status bit before issuing the next command, which
	 * can and will alter the status bits and will deserve a new
	 * interrupt on its own. This lets the controller exit the IRQ
	 */
	nand_writel(info, NDSR, status);

	if (status & NDSR_WRCMDREQ) {
		status &= ~NDSR_WRCMDREQ;
		info->state = STATE_CMD_HANDLE;

		/*
		 * Command buffer registers NDCB{0-2} (and optionally NDCB3)
		 * must be loaded by writing directly either 12 or 16
		 * bytes directly to NDCB0, four bytes at a time.
		 *
		 * Direct write access to NDCB1, NDCB2 and NDCB3 is ignored
		 * but each NDCBx register can be read.
		 */
		nand_writel(info, NDCB0, info->ndcb0);
		nand_writel(info, NDCB0, info->ndcb1);
		nand_writel(info, NDCB0, info->ndcb2);

		/* NDCB3 register is available in NFCv2 (Armada 370/XP SoC) */
		if (info->variant == PXA3XX_NAND_VARIANT_ARMADA370)
			nand_writel(info, NDCB0, info->ndcb3);
	}

	if (is_completed)
		info->cmd_complete = 1;
	if (is_ready)
		info->dev_ready = 1;

	return ret;
}

static inline int is_buf_blank(uint8_t *buf, size_t len)
{
	for (; len > 0; len--)
		if (*buf++ != 0xff)
			return 0;
	return 1;
}

static void set_command_address(struct pxa3xx_nand_info *info,
		unsigned int page_size, uint16_t column, int page_addr)
{
	/* small page addr setting */
	if (page_size < info->chunk_size) {
		info->ndcb1 = ((page_addr & 0xFFFFFF) << 8)
				| (column & 0xFF);

		info->ndcb2 = 0;
	} else {
		info->ndcb1 = ((page_addr & 0xFFFF) << 16)
				| (column & 0xFFFF);

		if (page_addr & 0xFF0000)
			info->ndcb2 = (page_addr & 0xFF0000) >> 16;
		else
			info->ndcb2 = 0;
	}
}

static void prepare_start_command(struct pxa3xx_nand_info *info, int command)
{
	struct pxa3xx_nand_host *host = info->host[info->cs];
	struct mtd_info *mtd = nand_to_mtd(&host->chip);

	/* reset data and oob column point to handle data */
	info->buf_start		= 0;
	info->buf_count		= 0;
	info->data_buff_pos	= 0;
	info->oob_buff_pos	= 0;
	info->step_chunk_size   = 0;
	info->step_spare_size   = 0;
	info->cur_chunk         = 0;
	info->use_ecc		= 0;
	info->use_spare		= 1;
	info->retcode		= ERR_NONE;
	info->ecc_err_cnt	= 0;
	info->ndcb3		= 0;
	info->need_wait		= 0;

	switch (command) {
	case NAND_CMD_READ0:
	case NAND_CMD_READOOB:
	case NAND_CMD_PAGEPROG:
		if (!info->force_raw)
			info->use_ecc = 1;
		break;
	case NAND_CMD_PARAM:
		info->use_spare = 0;
		break;
	default:
		info->ndcb1 = 0;
		info->ndcb2 = 0;
		break;
	}

	/*
	 * If we are about to issue a read command, or about to set
	 * the write address, then clean the data buffer.
	 */
	if (command == NAND_CMD_READ0 ||
	    command == NAND_CMD_READOOB ||
	    command == NAND_CMD_SEQIN) {
		info->buf_count = mtd->writesize + mtd->oobsize;
		memset(info->data_buff, 0xFF, info->buf_count);
	}
}

static int prepare_set_command(struct pxa3xx_nand_info *info, int command,
		int ext_cmd_type, uint16_t column, int page_addr)
{
	int addr_cycle, exec_cmd;
	struct pxa3xx_nand_host *host;
	struct mtd_info *mtd;

	host = info->host[info->cs];
	mtd = nand_to_mtd(&host->chip);
	addr_cycle = 0;
	exec_cmd = 1;

	if (info->cs != 0)
		info->ndcb0 = NDCB0_CSEL;
	else
		info->ndcb0 = 0;

	if (command == NAND_CMD_SEQIN)
		exec_cmd = 0;

	addr_cycle = NDCB0_ADDR_CYC(host->row_addr_cycles
				    + host->col_addr_cycles);

	switch (command) {
	case NAND_CMD_READOOB:
	case NAND_CMD_READ0:
		info->buf_start = column;
		info->ndcb0 |= NDCB0_CMD_TYPE(0)
				| addr_cycle
				| NAND_CMD_READ0;

		if (command == NAND_CMD_READOOB)
			info->buf_start += mtd->writesize;

		if (info->cur_chunk < info->nfullchunks) {
			info->step_chunk_size = info->chunk_size;
			info->step_spare_size = info->spare_size;
		} else {
			info->step_chunk_size = info->last_chunk_size;
			info->step_spare_size = info->last_spare_size;
		}

		/*
		 * Multiple page read needs an 'extended command type' field,
		 * which is either naked-read or last-read according to the
		 * state.
		 */
		if (info->force_raw) {
			info->ndcb0 |= NDCB0_DBC | (NAND_CMD_READSTART << 8) |
				       NDCB0_LEN_OVRD |
				       NDCB0_EXT_CMD_TYPE(ext_cmd_type);
			info->ndcb3 = info->step_chunk_size +
				      info->step_spare_size + info->ecc_size;
		} else if (mtd->writesize == info->chunk_size) {
			info->ndcb0 |= NDCB0_DBC | (NAND_CMD_READSTART << 8);
		} else if (mtd->writesize > info->chunk_size) {
			info->ndcb0 |= NDCB0_DBC | (NAND_CMD_READSTART << 8)
					| NDCB0_LEN_OVRD
					| NDCB0_EXT_CMD_TYPE(ext_cmd_type);
			info->ndcb3 = info->step_chunk_size +
				info->step_spare_size;
		}

		set_command_address(info, mtd->writesize, column, page_addr);
		break;

	case NAND_CMD_SEQIN:

		info->buf_start = column;
		set_command_address(info, mtd->writesize, 0, page_addr);

		/*
		 * Multiple page programming needs to execute the initial
		 * SEQIN command that sets the page address.
		 */
		if (mtd->writesize > info->chunk_size) {
			info->ndcb0 |= NDCB0_CMD_TYPE(0x1)
				| NDCB0_EXT_CMD_TYPE(ext_cmd_type)
				| addr_cycle
				| command;
			exec_cmd = 1;
		}
		break;

	case NAND_CMD_PAGEPROG:
		if (is_buf_blank(info->data_buff,
				 (mtd->writesize + mtd->oobsize))) {
			exec_cmd = 0;
			break;
		}

		if (info->cur_chunk < info->nfullchunks) {
			info->step_chunk_size = info->chunk_size;
			info->step_spare_size = info->spare_size;
		} else {
			info->step_chunk_size = info->last_chunk_size;
			info->step_spare_size = info->last_spare_size;
		}

		/* Second command setting for large pages */
		if (mtd->writesize > info->chunk_size) {
			/*
			 * Multiple page write uses the 'extended command'
			 * field. This can be used to issue a command dispatch
			 * or a naked-write depending on the current stage.
			 */
			info->ndcb0 |= NDCB0_CMD_TYPE(0x1)
					| NDCB0_LEN_OVRD
					| NDCB0_EXT_CMD_TYPE(ext_cmd_type);
			info->ndcb3 = info->step_chunk_size +
				      info->step_spare_size;

			/*
			 * This is the command dispatch that completes a chunked
			 * page program operation.
			 */
			if (info->cur_chunk == info->ntotalchunks) {
				info->ndcb0 = NDCB0_CMD_TYPE(0x1)
					| NDCB0_EXT_CMD_TYPE(ext_cmd_type)
					| command;
				info->ndcb1 = 0;
				info->ndcb2 = 0;
				info->ndcb3 = 0;
			}
		} else {
			info->ndcb0 |= NDCB0_CMD_TYPE(0x1)
					| NDCB0_AUTO_RS
					| NDCB0_ST_ROW_EN
					| NDCB0_DBC
					| (NAND_CMD_PAGEPROG << 8)
					| NAND_CMD_SEQIN
					| addr_cycle;
		}
		break;

	case NAND_CMD_PARAM:
		info->buf_count = INIT_BUFFER_SIZE;
		info->ndcb0 |= NDCB0_CMD_TYPE(0)
				| NDCB0_ADDR_CYC(1)
				| NDCB0_LEN_OVRD
				| command;
		info->ndcb1 = (column & 0xFF);
		info->ndcb3 = INIT_BUFFER_SIZE;
		info->step_chunk_size = INIT_BUFFER_SIZE;
		break;

	case NAND_CMD_READID:
		info->buf_count = READ_ID_BYTES;
		info->ndcb0 |= NDCB0_CMD_TYPE(3)
				| NDCB0_ADDR_CYC(1)
				| command;
		info->ndcb1 = (column & 0xFF);

		info->step_chunk_size = 8;
		break;
	case NAND_CMD_STATUS:
		info->buf_count = 1;
		info->ndcb0 |= NDCB0_CMD_TYPE(4)
				| NDCB0_ADDR_CYC(1)
				| command;

		info->step_chunk_size = 8;
		break;

	case NAND_CMD_ERASE1:
		info->ndcb0 |= NDCB0_CMD_TYPE(2)
				| NDCB0_AUTO_RS
				| NDCB0_ADDR_CYC(3)
				| NDCB0_DBC
				| (NAND_CMD_ERASE2 << 8)
				| NAND_CMD_ERASE1;
		info->ndcb1 = page_addr;
		info->ndcb2 = 0;

		break;
	case NAND_CMD_RESET:
		info->ndcb0 |= NDCB0_CMD_TYPE(5)
				| command;

		break;

	case NAND_CMD_ERASE2:
		exec_cmd = 0;
		break;

	default:
		exec_cmd = 0;
		dev_err(&info->pdev->dev, "non-supported command %x\n",
			command);
		break;
	}

	return exec_cmd;
}

static void nand_cmdfunc(struct mtd_info *mtd, unsigned command,
			 int column, int page_addr)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct pxa3xx_nand_host *host = nand_get_controller_data(chip);
	struct pxa3xx_nand_info *info = host->info_data;
	int exec_cmd;

	/*
	 * if this is a x16 device ,then convert the input
	 * "byte" address into a "word" address appropriate
	 * for indexing a word-oriented device
	 */
	if (info->reg_ndcr & NDCR_DWIDTH_M)
		column /= 2;

	/*
	 * There may be different NAND chip hooked to
	 * different chip select, so check whether
	 * chip select has been changed, if yes, reset the timing
	 */
	if (info->cs != host->cs) {
		info->cs = host->cs;
		nand_writel(info, NDTR0CS0, info->ndtr0cs0);
		nand_writel(info, NDTR1CS0, info->ndtr1cs0);
	}

	prepare_start_command(info, command);

	info->state = STATE_PREPARED;
	exec_cmd = prepare_set_command(info, command, 0, column, page_addr);

	if (exec_cmd) {
		u32 ts;

		info->cmd_complete = 0;
		info->dev_ready = 0;
		info->need_wait = 1;
		pxa3xx_nand_start(info);

		ts = get_timer(0);
		while (1) {
			u32 status;

			status = nand_readl(info, NDSR);
			if (status)
				pxa3xx_nand_irq(info);

			if (info->cmd_complete)
				break;

			if (get_timer(ts) > CHIP_DELAY_TIMEOUT) {
				dev_err(&info->pdev->dev, "Wait timeout!!!\n");
				return;
			}
		}
	}
	info->state = STATE_IDLE;
}

static void nand_cmdfunc_extended(struct mtd_info *mtd,
				  const unsigned command,
				  int column, int page_addr)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct pxa3xx_nand_host *host = nand_get_controller_data(chip);
	struct pxa3xx_nand_info *info = host->info_data;
	int exec_cmd, ext_cmd_type;

	/*
	 * if this is a x16 device then convert the input
	 * "byte" address into a "word" address appropriate
	 * for indexing a word-oriented device
	 */
	if (info->reg_ndcr & NDCR_DWIDTH_M)
		column /= 2;

	/*
	 * There may be different NAND chip hooked to
	 * different chip select, so check whether
	 * chip select has been changed, if yes, reset the timing
	 */
	if (info->cs != host->cs) {
		info->cs = host->cs;
		nand_writel(info, NDTR0CS0, info->ndtr0cs0);
		nand_writel(info, NDTR1CS0, info->ndtr1cs0);
	}

	/* Select the extended command for the first command */
	switch (command) {
	case NAND_CMD_READ0:
	case NAND_CMD_READOOB:
		ext_cmd_type = EXT_CMD_TYPE_MONO;
		break;
	case NAND_CMD_SEQIN:
		ext_cmd_type = EXT_CMD_TYPE_DISPATCH;
		break;
	case NAND_CMD_PAGEPROG:
		ext_cmd_type = EXT_CMD_TYPE_NAKED_RW;
		break;
	default:
		ext_cmd_type = 0;
		break;
	}

	prepare_start_command(info, command);

	/*
	 * Prepare the "is ready" completion before starting a command
	 * transaction sequence. If the command is not executed the
	 * completion will be completed, see below.
	 *
	 * We can do that inside the loop because the command variable
	 * is invariant and thus so is the exec_cmd.
	 */
	info->need_wait = 1;
	info->dev_ready = 0;

	do {
		u32 ts;

		info->state = STATE_PREPARED;
		exec_cmd = prepare_set_command(info, command, ext_cmd_type,
					       column, page_addr);
		if (!exec_cmd) {
			info->need_wait = 0;
			info->dev_ready = 1;
			break;
		}

		info->cmd_complete = 0;
		pxa3xx_nand_start(info);

		ts = get_timer(0);
		while (1) {
			u32 status;

			status = nand_readl(info, NDSR);
			if (status)
				pxa3xx_nand_irq(info);

			if (info->cmd_complete)
				break;

			if (get_timer(ts) > CHIP_DELAY_TIMEOUT) {
				dev_err(&info->pdev->dev, "Wait timeout!!!\n");
				return;
			}
		}

		/* Only a few commands need several steps */
		if (command != NAND_CMD_PAGEPROG &&
		    command != NAND_CMD_READ0    &&
		    command != NAND_CMD_READOOB)
			break;

		info->cur_chunk++;

		/* Check if the sequence is complete */
		if (info->cur_chunk == info->ntotalchunks &&
		    command != NAND_CMD_PAGEPROG)
			break;

		/*
		 * After a splitted program command sequence has issued
		 * the command dispatch, the command sequence is complete.
		 */
		if (info->cur_chunk == (info->ntotalchunks + 1) &&
		    command == NAND_CMD_PAGEPROG &&
		    ext_cmd_type == EXT_CMD_TYPE_DISPATCH)
			break;

		if (command == NAND_CMD_READ0 || command == NAND_CMD_READOOB) {
			/* Last read: issue a 'last naked read' */
			if (info->cur_chunk == info->ntotalchunks - 1)
				ext_cmd_type = EXT_CMD_TYPE_LAST_RW;
			else
				ext_cmd_type = EXT_CMD_TYPE_NAKED_RW;

		/*
		 * If a splitted program command has no more data to transfer,
		 * the command dispatch must be issued to complete.
		 */
		} else if (command == NAND_CMD_PAGEPROG &&
			   info->cur_chunk == info->ntotalchunks) {
				ext_cmd_type = EXT_CMD_TYPE_DISPATCH;
		}
	} while (1);

	info->state = STATE_IDLE;
}

static int pxa3xx_nand_write_page_hwecc(struct mtd_info *mtd,
		struct nand_chip *chip, const uint8_t *buf, int oob_required,
		int page)
{
	chip->write_buf(mtd, buf, mtd->writesize);
	chip->write_buf(mtd, chip->oob_poi, mtd->oobsize);

	return 0;
}

static int pxa3xx_nand_read_page_hwecc(struct mtd_info *mtd,
		struct nand_chip *chip, uint8_t *buf, int oob_required,
		int page)
{
	struct pxa3xx_nand_host *host = nand_get_controller_data(chip);
	struct pxa3xx_nand_info *info = host->info_data;
	int bf;

	chip->read_buf(mtd, buf, mtd->writesize);
	chip->read_buf(mtd, chip->oob_poi, mtd->oobsize);

	if (info->retcode == ERR_CORERR && info->use_ecc) {
		mtd->ecc_stats.corrected += info->ecc_err_cnt;

	} else if (info->retcode == ERR_UNCORERR && info->ecc_bch) {
		/*
		 * Empty pages will trigger uncorrectable errors. Re-read the
		 * entire page in raw mode and check for bits not being "1".
		 * If there are more than the supported strength, then it means
		 * this is an actual uncorrectable error.
		 */
		chip->ecc.read_page_raw(mtd, chip, buf, oob_required, page);
		bf = nand_check_erased_ecc_chunk(buf, mtd->writesize,
						 chip->oob_poi, mtd->oobsize,
						 NULL, 0, chip->ecc.strength);
		if (bf < 0) {
			mtd->ecc_stats.failed++;
		} else if (bf) {
			mtd->ecc_stats.corrected += bf;
			info->max_bitflips = max_t(unsigned int,
						   info->max_bitflips, bf);
			info->retcode = ERR_CORERR;
		} else {
			info->retcode = ERR_NONE;
		}

	} else if (info->retcode == ERR_UNCORERR && !info->ecc_bch) {
		/* Raw read is not supported with Hamming ECC engine */
		if (is_buf_blank(buf, mtd->writesize))
			info->retcode = ERR_NONE;
		else
			mtd->ecc_stats.failed++;
	}

	return info->max_bitflips;
}

static int pxa3xx_nand_read_page_raw(struct mtd_info *mtd,
				     struct nand_chip *chip, uint8_t *buf,
				     int oob_required, int page)
{
	struct pxa3xx_nand_host *host = chip->priv;
	struct pxa3xx_nand_info *info = host->info_data;
	int chunk, ecc_off_buf;

	if (!info->ecc_bch)
		return -ENOTSUPP;

	/*
	 * Set the force_raw boolean, then re-call ->cmdfunc() that will run
	 * pxa3xx_nand_start(), which will actually disable the ECC engine.
	 */
	info->force_raw = true;
	chip->cmdfunc(mtd, NAND_CMD_READ0, 0x00, page);

	ecc_off_buf = (info->nfullchunks * info->spare_size) +
		      info->last_spare_size;
	for (chunk = 0; chunk < info->nfullchunks; chunk++) {
		chip->read_buf(mtd,
			       buf + (chunk * info->chunk_size),
			       info->chunk_size);
		chip->read_buf(mtd,
			       chip->oob_poi +
			       (chunk * (info->spare_size)),
			       info->spare_size);
		chip->read_buf(mtd,
			       chip->oob_poi + ecc_off_buf +
			       (chunk * (info->ecc_size)),
			       info->ecc_size - 2);
	}

	if (info->ntotalchunks > info->nfullchunks) {
		chip->read_buf(mtd,
			       buf + (info->nfullchunks * info->chunk_size),
			       info->last_chunk_size);
		chip->read_buf(mtd,
			       chip->oob_poi +
			       (info->nfullchunks * (info->spare_size)),
			       info->last_spare_size);
		chip->read_buf(mtd,
			       chip->oob_poi + ecc_off_buf +
			       (info->nfullchunks * (info->ecc_size)),
			       info->ecc_size - 2);
	}

	info->force_raw = false;

	return 0;
}

static int pxa3xx_nand_read_oob_raw(struct mtd_info *mtd,
				    struct nand_chip *chip, int page)
{
	/* Invalidate page cache */
	chip->pagebuf = -1;

	return chip->ecc.read_page_raw(mtd, chip, chip->buffers->databuf, true,
				       page);
}

static uint8_t pxa3xx_nand_read_byte(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct pxa3xx_nand_host *host = nand_get_controller_data(chip);
	struct pxa3xx_nand_info *info = host->info_data;
	char retval = 0xFF;

	if (info->buf_start < info->buf_count)
		/* Has just send a new command? */
		retval = info->data_buff[info->buf_start++];

	return retval;
}

static u16 pxa3xx_nand_read_word(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct pxa3xx_nand_host *host = nand_get_controller_data(chip);
	struct pxa3xx_nand_info *info = host->info_data;
	u16 retval = 0xFFFF;

	if (!(info->buf_start & 0x01) && info->buf_start < info->buf_count) {
		retval = *((u16 *)(info->data_buff+info->buf_start));
		info->buf_start += 2;
	}
	return retval;
}

static void pxa3xx_nand_read_buf(struct mtd_info *mtd, uint8_t *buf, int len)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct pxa3xx_nand_host *host = nand_get_controller_data(chip);
	struct pxa3xx_nand_info *info = host->info_data;
	int real_len = min_t(size_t, len, info->buf_count - info->buf_start);

	memcpy(buf, info->data_buff + info->buf_start, real_len);
	info->buf_start += real_len;
}

static void pxa3xx_nand_write_buf(struct mtd_info *mtd,
		const uint8_t *buf, int len)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct pxa3xx_nand_host *host = nand_get_controller_data(chip);
	struct pxa3xx_nand_info *info = host->info_data;
	int real_len = min_t(size_t, len, info->buf_count - info->buf_start);

	memcpy(info->data_buff + info->buf_start, buf, real_len);
	info->buf_start += real_len;
}

static void pxa3xx_nand_select_chip(struct mtd_info *mtd, int chip)
{
	return;
}

static int pxa3xx_nand_waitfunc(struct mtd_info *mtd, struct nand_chip *this)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct pxa3xx_nand_host *host = nand_get_controller_data(chip);
	struct pxa3xx_nand_info *info = host->info_data;

	if (info->need_wait) {
		u32 ts;

		info->need_wait = 0;

		ts = get_timer(0);
		while (1) {
			u32 status;

			status = nand_readl(info, NDSR);
			if (status)
				pxa3xx_nand_irq(info);

			if (info->dev_ready)
				break;

			if (get_timer(ts) > CHIP_DELAY_TIMEOUT) {
				dev_err(&info->pdev->dev, "Ready timeout!!!\n");
				return NAND_STATUS_FAIL;
			}
		}
	}

	/* pxa3xx_nand_send_command has waited for command complete */
	if (this->state == FL_WRITING || this->state == FL_ERASING) {
		if (info->retcode == ERR_NONE)
			return 0;
		else
			return NAND_STATUS_FAIL;
	}

	return NAND_STATUS_READY;
}

static int pxa3xx_nand_config_ident(struct pxa3xx_nand_info *info)
{
	struct pxa3xx_nand_platform_data *pdata = info->pdata;

	/* Configure default flash values */
	info->reg_ndcr = 0x0; /* enable all interrupts */
	info->reg_ndcr |= (pdata->enable_arbiter) ? NDCR_ND_ARB_EN : 0;
	info->reg_ndcr |= NDCR_RD_ID_CNT(READ_ID_BYTES);
	info->reg_ndcr |= NDCR_SPARE_EN;

	return 0;
}

static void pxa3xx_nand_config_tail(struct pxa3xx_nand_info *info)
{
	struct pxa3xx_nand_host *host = info->host[info->cs];
	struct mtd_info *mtd = nand_to_mtd(&info->host[info->cs]->chip);
	struct nand_chip *chip = mtd_to_nand(mtd);

	info->reg_ndcr |= (host->col_addr_cycles == 2) ? NDCR_RA_START : 0;
	info->reg_ndcr |= (chip->page_shift == 6) ? NDCR_PG_PER_BLK : 0;
	info->reg_ndcr |= (mtd->writesize == 2048) ? NDCR_PAGE_SZ : 0;
}

static void pxa3xx_nand_detect_config(struct pxa3xx_nand_info *info)
{
	struct pxa3xx_nand_platform_data *pdata = info->pdata;
	uint32_t ndcr = nand_readl(info, NDCR);

	/* Set an initial chunk size */
	info->chunk_size = ndcr & NDCR_PAGE_SZ ? 2048 : 512;
	info->reg_ndcr = ndcr &
		~(NDCR_INT_MASK | NDCR_ND_ARB_EN | NFCV1_NDCR_ARB_CNTL);
	info->reg_ndcr |= (pdata->enable_arbiter) ? NDCR_ND_ARB_EN : 0;
	info->ndtr0cs0 = nand_readl(info, NDTR0CS0);
	info->ndtr1cs0 = nand_readl(info, NDTR1CS0);
}

static int pxa3xx_nand_init_buff(struct pxa3xx_nand_info *info)
{
	info->data_buff = kmalloc(info->buf_size, GFP_KERNEL);
	if (info->data_buff == NULL)
		return -ENOMEM;
	return 0;
}

static int pxa3xx_nand_sensing(struct pxa3xx_nand_host *host)
{
	struct pxa3xx_nand_info *info = host->info_data;
	struct pxa3xx_nand_platform_data *pdata = info->pdata;
	struct mtd_info *mtd;
	struct nand_chip *chip;
	const struct nand_sdr_timings *timings;
	int ret;

	mtd = nand_to_mtd(&info->host[info->cs]->chip);
	chip = mtd_to_nand(mtd);

	/* configure default flash values */
	info->reg_ndcr = 0x0; /* enable all interrupts */
	info->reg_ndcr |= (pdata->enable_arbiter) ? NDCR_ND_ARB_EN : 0;
	info->reg_ndcr |= NDCR_RD_ID_CNT(READ_ID_BYTES);
	info->reg_ndcr |= NDCR_SPARE_EN; /* enable spare by default */

	/* use the common timing to make a try */
	timings = onfi_async_timing_mode_to_sdr_timings(0);
	if (IS_ERR(timings))
		return PTR_ERR(timings);

	pxa3xx_nand_set_sdr_timing(host, timings);

	chip->cmdfunc(mtd, NAND_CMD_RESET, 0, 0);
	ret = chip->waitfunc(mtd, chip);
	if (ret & NAND_STATUS_FAIL)
		return -ENODEV;

	return 0;
}

static int pxa_ecc_init(struct pxa3xx_nand_info *info,
			struct nand_ecc_ctrl *ecc,
			int strength, int ecc_stepsize, int page_size)
{
	if (strength == 1 && ecc_stepsize == 512 && page_size == 2048) {
		info->nfullchunks = 1;
		info->ntotalchunks = 1;
		info->chunk_size = 2048;
		info->spare_size = 40;
		info->ecc_size = 24;
		ecc->mode = NAND_ECC_HW;
		ecc->size = 512;
		ecc->strength = 1;

	} else if (strength == 1 && ecc_stepsize == 512 && page_size == 512) {
		info->nfullchunks = 1;
		info->ntotalchunks = 1;
		info->chunk_size = 512;
		info->spare_size = 8;
		info->ecc_size = 8;
		ecc->mode = NAND_ECC_HW;
		ecc->size = 512;
		ecc->strength = 1;

	/*
	 * Required ECC: 4-bit correction per 512 bytes
	 * Select: 16-bit correction per 2048 bytes
	 */
	} else if (strength == 4 && ecc_stepsize == 512 && page_size == 2048) {
		info->ecc_bch = 1;
		info->nfullchunks = 1;
		info->ntotalchunks = 1;
		info->chunk_size = 2048;
		info->spare_size = 32;
		info->ecc_size = 32;
		ecc->mode = NAND_ECC_HW;
		ecc->size = info->chunk_size;
		ecc->layout = &ecc_layout_2KB_bch4bit;
		ecc->strength = 16;

	} else if (strength == 4 && ecc_stepsize == 512 && page_size == 4096) {
		info->ecc_bch = 1;
		info->nfullchunks = 2;
		info->ntotalchunks = 2;
		info->chunk_size = 2048;
		info->spare_size = 32;
		info->ecc_size = 32;
		ecc->mode = NAND_ECC_HW;
		ecc->size = info->chunk_size;
		ecc->layout = &ecc_layout_4KB_bch4bit;
		ecc->strength = 16;

	} else if (strength == 4 && ecc_stepsize == 512 && page_size == 8192) {
		info->ecc_bch = 1;
		info->nfullchunks = 4;
		info->ntotalchunks = 4;
		info->chunk_size = 2048;
		info->spare_size = 32;
		info->ecc_size = 32;
		ecc->mode = NAND_ECC_HW;
		ecc->size = info->chunk_size;
		ecc->layout = &ecc_layout_8KB_bch4bit;
		ecc->strength = 16;

	/*
	 * Required ECC: 8-bit correction per 512 bytes
	 * Select: 16-bit correction per 1024 bytes
	 */
	} else if (strength == 8 && ecc_stepsize == 512 && page_size == 2048) {
		info->ecc_bch = 1;
		info->nfullchunks = 1;
		info->ntotalchunks = 2;
		info->chunk_size = 1024;
		info->spare_size = 0;
		info->last_chunk_size = 1024;
		info->last_spare_size = 32;
		info->ecc_size = 32;
		ecc->mode = NAND_ECC_HW;
		ecc->size = info->chunk_size;
		ecc->layout = &ecc_layout_2KB_bch8bit;
		ecc->strength = 16;

	} else if (strength == 8 && ecc_stepsize == 512 && page_size == 4096) {
		info->ecc_bch = 1;
		info->nfullchunks = 4;
		info->ntotalchunks = 5;
		info->chunk_size = 1024;
		info->spare_size = 0;
		info->last_chunk_size = 0;
		info->last_spare_size = 64;
		info->ecc_size = 32;
		ecc->mode = NAND_ECC_HW;
		ecc->size = info->chunk_size;
		ecc->layout = &ecc_layout_4KB_bch8bit;
		ecc->strength = 16;

	} else if (strength == 8 && ecc_stepsize == 512 && page_size == 8192) {
		info->ecc_bch = 1;
		info->nfullchunks = 8;
		info->ntotalchunks = 9;
		info->chunk_size = 1024;
		info->spare_size = 0;
		info->last_chunk_size = 0;
		info->last_spare_size = 160;
		info->ecc_size = 32;
		ecc->mode = NAND_ECC_HW;
		ecc->size = info->chunk_size;
		ecc->layout = &ecc_layout_8KB_bch8bit;
		ecc->strength = 16;

	} else {
		dev_err(&info->pdev->dev,
			"ECC strength %d at page size %d is not supported\n",
			strength, page_size);
		return -ENODEV;
	}

	return 0;
}

static int pxa3xx_nand_scan(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct pxa3xx_nand_host *host = nand_get_controller_data(chip);
	struct pxa3xx_nand_info *info = host->info_data;
	struct pxa3xx_nand_platform_data *pdata = info->pdata;
	int ret;
	uint16_t ecc_strength, ecc_step;

	if (pdata->keep_config) {
		pxa3xx_nand_detect_config(info);
	} else {
		ret = pxa3xx_nand_config_ident(info);
		if (ret)
			return ret;
		ret = pxa3xx_nand_sensing(host);
		if (ret) {
			dev_info(&info->pdev->dev,
				 "There is no chip on cs %d!\n",
				 info->cs);
			return ret;
		}
	}

	/* Device detection must be done with ECC disabled */
	if (info->variant == PXA3XX_NAND_VARIANT_ARMADA370)
		nand_writel(info, NDECCCTRL, 0x0);

	if (nand_scan_ident(mtd, 1, NULL))
		return -ENODEV;

	if (!pdata->keep_config) {
		ret = pxa3xx_nand_init_timings(host);
		if (ret) {
			dev_err(&info->pdev->dev,
				"Failed to set timings: %d\n", ret);
			return ret;
		}
	}

#ifdef CONFIG_SYS_NAND_USE_FLASH_BBT
	/*
	 * We'll use a bad block table stored in-flash and don't
	 * allow writing the bad block marker to the flash.
	 */
	chip->bbt_options |= NAND_BBT_USE_FLASH | NAND_BBT_NO_OOB_BBM;
	chip->bbt_td = &bbt_main_descr;
	chip->bbt_md = &bbt_mirror_descr;
#endif

	if (pdata->ecc_strength && pdata->ecc_step_size) {
		ecc_strength = pdata->ecc_strength;
		ecc_step = pdata->ecc_step_size;
	} else {
		ecc_strength = chip->ecc_strength_ds;
		ecc_step = chip->ecc_step_ds;
	}

	/* Set default ECC strength requirements on non-ONFI devices */
	if (ecc_strength < 1 && ecc_step < 1) {
		ecc_strength = 1;
		ecc_step = 512;
	}

	ret = pxa_ecc_init(info, &chip->ecc, ecc_strength,
			   ecc_step, mtd->writesize);
	if (ret)
		return ret;

	/*
	 * If the page size is bigger than the FIFO size, let's check
	 * we are given the right variant and then switch to the extended
	 * (aka split) command handling,
	 */
	if (mtd->writesize > info->chunk_size) {
		if (info->variant == PXA3XX_NAND_VARIANT_ARMADA370) {
			chip->cmdfunc = nand_cmdfunc_extended;
		} else {
			dev_err(&info->pdev->dev,
				"unsupported page size on this variant\n");
			return -ENODEV;
		}
	}

	/* calculate addressing information */
	if (mtd->writesize >= 2048)
		host->col_addr_cycles = 2;
	else
		host->col_addr_cycles = 1;

	/* release the initial buffer */
	kfree(info->data_buff);

	/* allocate the real data + oob buffer */
	info->buf_size = mtd->writesize + mtd->oobsize;
	ret = pxa3xx_nand_init_buff(info);
	if (ret)
		return ret;
	info->oob_buff = info->data_buff + mtd->writesize;

	if ((mtd->size >> chip->page_shift) > 65536)
		host->row_addr_cycles = 3;
	else
		host->row_addr_cycles = 2;

	if (!pdata->keep_config)
		pxa3xx_nand_config_tail(info);

	return nand_scan_tail(mtd);
}

static int alloc_nand_resource(struct pxa3xx_nand_info *info)
{
	struct pxa3xx_nand_platform_data *pdata;
	struct pxa3xx_nand_host *host;
	struct nand_chip *chip = NULL;
	struct mtd_info *mtd;
	int ret, cs;

	pdata = info->pdata;
	if (pdata->num_cs <= 0)
		return -ENODEV;

	info->variant = pxa3xx_nand_get_variant();
	for (cs = 0; cs < pdata->num_cs; cs++) {
		chip = (struct nand_chip *)
			((u8 *)&info[1] + sizeof(*host) * cs);
		mtd = nand_to_mtd(chip);
		host = (struct pxa3xx_nand_host *)chip;
		info->host[cs] = host;
		host->cs = cs;
		host->info_data = info;
		mtd->owner = THIS_MODULE;

		nand_set_controller_data(chip, host);
		chip->ecc.read_page	= pxa3xx_nand_read_page_hwecc;
		chip->ecc.read_page_raw	= pxa3xx_nand_read_page_raw;
		chip->ecc.read_oob_raw	= pxa3xx_nand_read_oob_raw;
		chip->ecc.write_page	= pxa3xx_nand_write_page_hwecc;
		chip->controller        = &info->controller;
		chip->waitfunc		= pxa3xx_nand_waitfunc;
		chip->select_chip	= pxa3xx_nand_select_chip;
		chip->read_word		= pxa3xx_nand_read_word;
		chip->read_byte		= pxa3xx_nand_read_byte;
		chip->read_buf		= pxa3xx_nand_read_buf;
		chip->write_buf		= pxa3xx_nand_write_buf;
		chip->options		|= NAND_NO_SUBPAGE_WRITE;
		chip->cmdfunc		= nand_cmdfunc;
	}

	/* Allocate a buffer to allow flash detection */
	info->buf_size = INIT_BUFFER_SIZE;
	info->data_buff = kmalloc(info->buf_size, GFP_KERNEL);
	if (info->data_buff == NULL) {
		ret = -ENOMEM;
		goto fail_disable_clk;
	}

	/* initialize all interrupts to be disabled */
	disable_int(info, NDSR_MASK);

	return 0;

	kfree(info->data_buff);
fail_disable_clk:
	return ret;
}

static int pxa3xx_nand_probe_dt(struct pxa3xx_nand_info *info)
{
	struct pxa3xx_nand_platform_data *pdata;
	const void *blob = gd->fdt_blob;
	int node = -1;

	pdata = kzalloc(sizeof(*pdata), GFP_KERNEL);
	if (!pdata)
		return -ENOMEM;

	/* Get address decoding nodes from the FDT blob */
	do {
		node = fdt_node_offset_by_compatible(blob, node,
						     "marvell,mvebu-pxa3xx-nand");
		if (node < 0)
			break;

		/* Bypass disabeld nodes */
		if (!fdtdec_get_is_enabled(blob, node))
			continue;

		/* Get the first enabled NAND controler base address */
		info->mmio_base =
			(void __iomem *)fdtdec_get_addr_size_auto_noparent(
					blob, node, "reg", 0, NULL, true);

		pdata->num_cs = fdtdec_get_int(blob, node, "num-cs", 1);
		if (pdata->num_cs != 1) {
			pr_err("pxa3xx driver supports single CS only\n");
			break;
		}

		if (fdtdec_get_bool(blob, node, "nand-enable-arbiter"))
			pdata->enable_arbiter = 1;

		if (fdtdec_get_bool(blob, node, "nand-keep-config"))
			pdata->keep_config = 1;

		/*
		 * ECC parameters.
		 * If these are not set, they will be selected according
		 * to the detected flash type.
		 */
		/* ECC strength */
		pdata->ecc_strength = fdtdec_get_int(blob, node,
						     "nand-ecc-strength", 0);

		/* ECC step size */
		pdata->ecc_step_size = fdtdec_get_int(blob, node,
						      "nand-ecc-step-size", 0);

		info->pdata = pdata;

		/* Currently support only a single NAND controller */
		return 0;

	} while (node >= 0);

	return -EINVAL;
}

static int pxa3xx_nand_probe(struct pxa3xx_nand_info *info)
{
	struct pxa3xx_nand_platform_data *pdata;
	int ret, cs, probe_success;

	ret = pxa3xx_nand_probe_dt(info);
	if (ret)
		return ret;

	pdata = info->pdata;

	ret = alloc_nand_resource(info);
	if (ret) {
		dev_err(&pdev->dev, "alloc nand resource failed\n");
		return ret;
	}

	probe_success = 0;
	for (cs = 0; cs < pdata->num_cs; cs++) {
		struct mtd_info *mtd = nand_to_mtd(&info->host[cs]->chip);

		/*
		 * The mtd name matches the one used in 'mtdparts' kernel
		 * parameter. This name cannot be changed or otherwise
		 * user's mtd partitions configuration would get broken.
		 */
		mtd->name = "pxa3xx_nand-0";
		info->cs = cs;
		ret = pxa3xx_nand_scan(mtd);
		if (ret) {
			dev_info(&pdev->dev, "failed to scan nand at cs %d\n",
				 cs);
			continue;
		}

		if (nand_register(cs, mtd))
			continue;

		probe_success = 1;
	}

	if (!probe_success)
		return -ENODEV;

	return 0;
}

/*
 * Main initialization routine
 */
void board_nand_init(void)
{
	struct pxa3xx_nand_info *info;
	struct pxa3xx_nand_host *host;
	int ret;

	info = kzalloc(sizeof(*info) +
		       sizeof(*host) * CONFIG_SYS_MAX_NAND_DEVICE,
		       GFP_KERNEL);
	if (!info)
		return;

	ret = pxa3xx_nand_probe(info);
	if (ret)
		return;
}
