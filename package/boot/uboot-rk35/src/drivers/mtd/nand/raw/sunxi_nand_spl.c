/*
 * Copyright (c) 2014-2015, Antmicro Ltd <www.antmicro.com>
 * Copyright (c) 2015, AW-SOM Technologies <www.aw-som.com>
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <asm/arch/clock.h>
#include <asm/io.h>
#include <common.h>
#include <config.h>
#include <nand.h>
#include <linux/ctype.h>

/* registers */
#define NFC_CTL                    0x00000000
#define NFC_ST                     0x00000004
#define NFC_INT                    0x00000008
#define NFC_TIMING_CTL             0x0000000C
#define NFC_TIMING_CFG             0x00000010
#define NFC_ADDR_LOW               0x00000014
#define NFC_ADDR_HIGH              0x00000018
#define NFC_SECTOR_NUM             0x0000001C
#define NFC_CNT                    0x00000020
#define NFC_CMD                    0x00000024
#define NFC_RCMD_SET               0x00000028
#define NFC_WCMD_SET               0x0000002C
#define NFC_IO_DATA                0x00000030
#define NFC_ECC_CTL                0x00000034
#define NFC_ECC_ST                 0x00000038
#define NFC_DEBUG                  0x0000003C
#define NFC_ECC_CNT0               0x00000040
#define NFC_ECC_CNT1               0x00000044
#define NFC_ECC_CNT2               0x00000048
#define NFC_ECC_CNT3               0x0000004C
#define NFC_USER_DATA_BASE         0x00000050
#define NFC_EFNAND_STATUS          0x00000090
#define NFC_SPARE_AREA             0x000000A0
#define NFC_PATTERN_ID             0x000000A4
#define NFC_RAM0_BASE              0x00000400
#define NFC_RAM1_BASE              0x00000800

#define NFC_CTL_EN                 (1 << 0)
#define NFC_CTL_RESET              (1 << 1)
#define NFC_CTL_RAM_METHOD         (1 << 14)
#define NFC_CTL_PAGE_SIZE_MASK     (0xf << 8)
#define NFC_CTL_PAGE_SIZE(a)       ((fls(a) - 11) << 8)


#define NFC_ECC_EN                 (1 << 0)
#define NFC_ECC_PIPELINE           (1 << 3)
#define NFC_ECC_EXCEPTION          (1 << 4)
#define NFC_ECC_BLOCK_SIZE         (1 << 5)
#define NFC_ECC_RANDOM_EN          (1 << 9)
#define NFC_ECC_RANDOM_DIRECTION   (1 << 10)


#define NFC_ADDR_NUM_OFFSET        16
#define NFC_SEND_ADDR              (1 << 19)
#define NFC_ACCESS_DIR             (1 << 20)
#define NFC_DATA_TRANS             (1 << 21)
#define NFC_SEND_CMD1              (1 << 22)
#define NFC_WAIT_FLAG              (1 << 23)
#define NFC_SEND_CMD2              (1 << 24)
#define NFC_SEQ                    (1 << 25)
#define NFC_DATA_SWAP_METHOD       (1 << 26)
#define NFC_ROW_AUTO_INC           (1 << 27)
#define NFC_SEND_CMD3              (1 << 28)
#define NFC_SEND_CMD4              (1 << 29)
#define NFC_RAW_CMD                (0 << 30)
#define NFC_ECC_CMD                (1 << 30)
#define NFC_PAGE_CMD               (2 << 30)

#define NFC_ST_CMD_INT_FLAG        (1 << 1)
#define NFC_ST_DMA_INT_FLAG        (1 << 2)
#define NFC_ST_CMD_FIFO_STAT       (1 << 3)

#define NFC_READ_CMD_OFFSET         0
#define NFC_RANDOM_READ_CMD0_OFFSET 8
#define NFC_RANDOM_READ_CMD1_OFFSET 16

#define NFC_CMD_RNDOUTSTART        0xE0
#define NFC_CMD_RNDOUT             0x05
#define NFC_CMD_READSTART          0x30

struct nfc_config {
	int page_size;
	int ecc_strength;
	int ecc_size;
	int addr_cycles;
	int nseeds;
	bool randomize;
	bool valid;
};

/* minimal "boot0" style NAND support for Allwinner A20 */

/* random seed used by linux */
const uint16_t random_seed[128] = {
	0x2b75, 0x0bd0, 0x5ca3, 0x62d1, 0x1c93, 0x07e9, 0x2162, 0x3a72,
	0x0d67, 0x67f9, 0x1be7, 0x077d, 0x032f, 0x0dac, 0x2716, 0x2436,
	0x7922, 0x1510, 0x3860, 0x5287, 0x480f, 0x4252, 0x1789, 0x5a2d,
	0x2a49, 0x5e10, 0x437f, 0x4b4e, 0x2f45, 0x216e, 0x5cb7, 0x7130,
	0x2a3f, 0x60e4, 0x4dc9, 0x0ef0, 0x0f52, 0x1bb9, 0x6211, 0x7a56,
	0x226d, 0x4ea7, 0x6f36, 0x3692, 0x38bf, 0x0c62, 0x05eb, 0x4c55,
	0x60f4, 0x728c, 0x3b6f, 0x2037, 0x7f69, 0x0936, 0x651a, 0x4ceb,
	0x6218, 0x79f3, 0x383f, 0x18d9, 0x4f05, 0x5c82, 0x2912, 0x6f17,
	0x6856, 0x5938, 0x1007, 0x61ab, 0x3e7f, 0x57c2, 0x542f, 0x4f62,
	0x7454, 0x2eac, 0x7739, 0x42d4, 0x2f90, 0x435a, 0x2e52, 0x2064,
	0x637c, 0x66ad, 0x2c90, 0x0bad, 0x759c, 0x0029, 0x0986, 0x7126,
	0x1ca7, 0x1605, 0x386a, 0x27f5, 0x1380, 0x6d75, 0x24c3, 0x0f8e,
	0x2b7a, 0x1418, 0x1fd1, 0x7dc1, 0x2d8e, 0x43af, 0x2267, 0x7da3,
	0x4e3d, 0x1338, 0x50db, 0x454d, 0x764d, 0x40a3, 0x42e6, 0x262b,
	0x2d2e, 0x1aea, 0x2e17, 0x173d, 0x3a6e, 0x71bf, 0x25f9, 0x0a5d,
	0x7c57, 0x0fbe, 0x46ce, 0x4939, 0x6b17, 0x37bb, 0x3e91, 0x76db,
};

#define DEFAULT_TIMEOUT_US	100000

static int check_value_inner(int offset, int expected_bits,
			     int timeout_us, int negation)
{
	do {
		int val = readl(offset) & expected_bits;
		if (negation ? !val : val)
			return 1;
		udelay(1);
	} while (--timeout_us);

	return 0;
}

static inline int check_value(int offset, int expected_bits,
			      int timeout_us)
{
	return check_value_inner(offset, expected_bits, timeout_us, 0);
}

static inline int check_value_negated(int offset, int unexpected_bits,
				      int timeout_us)
{
	return check_value_inner(offset, unexpected_bits, timeout_us, 1);
}

static int nand_wait_cmd_fifo_empty(void)
{
	if (!check_value_negated(SUNXI_NFC_BASE + NFC_ST, NFC_ST_CMD_FIFO_STAT,
				 DEFAULT_TIMEOUT_US)) {
		printf("nand: timeout waiting for empty cmd FIFO\n");
		return -ETIMEDOUT;
	}

	return 0;
}

static int nand_wait_int(void)
{
	if (!check_value(SUNXI_NFC_BASE + NFC_ST, NFC_ST_CMD_INT_FLAG,
			 DEFAULT_TIMEOUT_US)) {
		printf("nand: timeout waiting for interruption\n");
		return -ETIMEDOUT;
	}

	return 0;
}

static int nand_exec_cmd(u32 cmd)
{
	int ret;

	ret = nand_wait_cmd_fifo_empty();
	if (ret)
		return ret;

	writel(NFC_ST_CMD_INT_FLAG, SUNXI_NFC_BASE + NFC_ST);
	writel(cmd, SUNXI_NFC_BASE + NFC_CMD);

	return nand_wait_int();
}

void nand_init(void)
{
	uint32_t val;

	board_nand_init();

	val = readl(SUNXI_NFC_BASE + NFC_CTL);
	/* enable and reset CTL */
	writel(val | NFC_CTL_EN | NFC_CTL_RESET,
	       SUNXI_NFC_BASE + NFC_CTL);

	if (!check_value_negated(SUNXI_NFC_BASE + NFC_CTL,
				 NFC_CTL_RESET, DEFAULT_TIMEOUT_US)) {
		printf("Couldn't initialize nand\n");
	}

	/* reset NAND */
	nand_exec_cmd(NFC_SEND_CMD1 | NFC_WAIT_FLAG | NAND_CMD_RESET);
}

static void nand_apply_config(const struct nfc_config *conf)
{
	u32 val;

	nand_wait_cmd_fifo_empty();

	val = readl(SUNXI_NFC_BASE + NFC_CTL);
	val &= ~NFC_CTL_PAGE_SIZE_MASK;
	writel(val | NFC_CTL_RAM_METHOD | NFC_CTL_PAGE_SIZE(conf->page_size),
	       SUNXI_NFC_BASE + NFC_CTL);
	writel(conf->ecc_size, SUNXI_NFC_BASE + NFC_CNT);
	writel(conf->page_size, SUNXI_NFC_BASE + NFC_SPARE_AREA);
}

static int nand_load_page(const struct nfc_config *conf, u32 offs)
{
	int page = offs / conf->page_size;

	writel((NFC_CMD_RNDOUTSTART << NFC_RANDOM_READ_CMD1_OFFSET) |
	       (NFC_CMD_RNDOUT << NFC_RANDOM_READ_CMD0_OFFSET) |
	       (NFC_CMD_READSTART << NFC_READ_CMD_OFFSET),
	       SUNXI_NFC_BASE + NFC_RCMD_SET);
	writel(((page & 0xFFFF) << 16), SUNXI_NFC_BASE + NFC_ADDR_LOW);
	writel((page >> 16) & 0xFF, SUNXI_NFC_BASE + NFC_ADDR_HIGH);

	return nand_exec_cmd(NFC_SEND_CMD1 | NFC_SEND_CMD2 | NFC_RAW_CMD |
			     NFC_SEND_ADDR | NFC_WAIT_FLAG |
			     ((conf->addr_cycles - 1) << NFC_ADDR_NUM_OFFSET));
}

static int nand_change_column(u16 column)
{
	int ret;

	writel((NFC_CMD_RNDOUTSTART << NFC_RANDOM_READ_CMD1_OFFSET) |
	       (NFC_CMD_RNDOUT << NFC_RANDOM_READ_CMD0_OFFSET) |
	       (NFC_CMD_RNDOUTSTART << NFC_READ_CMD_OFFSET),
	       SUNXI_NFC_BASE + NFC_RCMD_SET);
	writel(column, SUNXI_NFC_BASE + NFC_ADDR_LOW);

	ret = nand_exec_cmd(NFC_SEND_CMD1 | NFC_SEND_CMD2 | NFC_RAW_CMD |
			    (1 << NFC_ADDR_NUM_OFFSET) | NFC_SEND_ADDR |
			    NFC_CMD_RNDOUT);
	if (ret)
		return ret;

	/* Ensure tCCS has passed before reading data */
	udelay(1);

	return 0;
}

static const int ecc_bytes[] = {32, 46, 54, 60, 74, 88, 102, 110, 116};

static int nand_read_page(const struct nfc_config *conf, u32 offs,
			  void *dest, int len)
{
	int nsectors = len / conf->ecc_size;
	u16 rand_seed = 0;
	int oob_chunk_sz = ecc_bytes[conf->ecc_strength];
	int page = offs / conf->page_size;
	u32 ecc_st;
	int i;

	if (offs % conf->page_size || len % conf->ecc_size ||
	    len > conf->page_size || len < 0)
		return -EINVAL;

	/* Choose correct seed if randomized */
	if (conf->randomize)
		rand_seed = random_seed[page % conf->nseeds];

	/* Retrieve data from SRAM (PIO) */
	for (i = 0; i < nsectors; i++) {
		int data_off = i * conf->ecc_size;
		int oob_off = conf->page_size + (i * oob_chunk_sz);
		u8 *data = dest + data_off;

		/* Clear ECC status and restart ECC engine */
		writel(0, SUNXI_NFC_BASE + NFC_ECC_ST);
		writel((rand_seed << 16) | (conf->ecc_strength << 12) |
		       (conf->randomize ? NFC_ECC_RANDOM_EN : 0) |
		       (conf->ecc_size == 512 ? NFC_ECC_BLOCK_SIZE : 0) |
		       NFC_ECC_EN | NFC_ECC_EXCEPTION,
		       SUNXI_NFC_BASE + NFC_ECC_CTL);

		/* Move the data in SRAM */
		nand_change_column(data_off);
		writel(conf->ecc_size, SUNXI_NFC_BASE + NFC_CNT);
		nand_exec_cmd(NFC_DATA_TRANS);

		/*
		 * Let the ECC engine consume the ECC bytes and possibly correct
		 * the data.
		 */
		nand_change_column(oob_off);
		nand_exec_cmd(NFC_DATA_TRANS | NFC_ECC_CMD);

		/* Get the ECC status */
		ecc_st = readl(SUNXI_NFC_BASE + NFC_ECC_ST);

		/* ECC error detected. */
		if (ecc_st & 0xffff)
			return -EIO;

		/*
		 * Return 1 if the first chunk is empty (needed for
		 * configuration detection).
		 */
		if (!i && (ecc_st & 0x10000))
			return 1;

		/* Retrieve the data from SRAM */
		memcpy_fromio(data, SUNXI_NFC_BASE + NFC_RAM0_BASE,
			      conf->ecc_size);

		/* Stop the ECC engine */
		writel(readl(SUNXI_NFC_BASE + NFC_ECC_CTL) & ~NFC_ECC_EN,
		       SUNXI_NFC_BASE + NFC_ECC_CTL);

		if (data_off + conf->ecc_size >= len)
			break;
	}

	return 0;
}

static int nand_max_ecc_strength(struct nfc_config *conf)
{
	int max_oobsize, max_ecc_bytes;
	int nsectors = conf->page_size / conf->ecc_size;
	int i;

	/*
	 * ECC strength is limited by the size of the OOB area which is
	 * correlated with the page size.
	 */
	switch (conf->page_size) {
	case 2048:
		max_oobsize = 64;
		break;
	case 4096:
		max_oobsize = 256;
		break;
	case 8192:
		max_oobsize = 640;
		break;
	case 16384:
		max_oobsize = 1664;
		break;
	default:
		return -EINVAL;
	}

	max_ecc_bytes = max_oobsize / nsectors;

	for (i = 0; i < ARRAY_SIZE(ecc_bytes); i++) {
		if (ecc_bytes[i] > max_ecc_bytes)
			break;
	}

	if (!i)
		return -EINVAL;

	return i - 1;
}

static int nand_detect_ecc_config(struct nfc_config *conf, u32 offs,
				  void *dest)
{
	/* NAND with pages > 4k will likely require 1k sector size. */
	int min_ecc_size = conf->page_size > 4096 ? 1024 : 512;
	int page = offs / conf->page_size;
	int ret;

	/*
	 * In most cases, 1k sectors are preferred over 512b ones, start
	 * testing this config first.
	 */
	for (conf->ecc_size = 1024; conf->ecc_size >= min_ecc_size;
	     conf->ecc_size >>= 1) {
		int max_ecc_strength = nand_max_ecc_strength(conf);

		nand_apply_config(conf);

		/*
		 * We are starting from the maximum ECC strength because
		 * most of the time NAND vendors provide an OOB area that
		 * barely meets the ECC requirements.
		 */
		for (conf->ecc_strength = max_ecc_strength;
		     conf->ecc_strength >= 0;
		     conf->ecc_strength--) {
			conf->randomize = false;
			if (nand_change_column(0))
				return -EIO;

			/*
			 * Only read the first sector to speedup detection.
			 */
			ret = nand_read_page(conf, offs, dest, conf->ecc_size);
			if (!ret) {
				return 0;
			} else if (ret > 0) {
				/*
				 * If page is empty we can't deduce anything
				 * about the ECC config => stop the detection.
				 */
				return -EINVAL;
			}

			conf->randomize = true;
			conf->nseeds = ARRAY_SIZE(random_seed);
			do {
				if (nand_change_column(0))
					return -EIO;

				if (!nand_read_page(conf, offs, dest,
						    conf->ecc_size))
					return 0;

				/*
				 * Find the next ->nseeds value that would
				 * change the randomizer seed for the page
				 * we're trying to read.
				 */
				while (conf->nseeds >= 16) {
					int seed = page % conf->nseeds;

					conf->nseeds >>= 1;
					if (seed != page % conf->nseeds)
						break;
				}
			} while (conf->nseeds >= 16);
		}
	}

	return -EINVAL;
}

static int nand_detect_config(struct nfc_config *conf, u32 offs, void *dest)
{
	if (conf->valid)
		return 0;

	/*
	 * Modern NANDs are more likely than legacy ones, so we start testing
	 * with 5 address cycles.
	 */
	for (conf->addr_cycles = 5;
	     conf->addr_cycles >= 4;
	     conf->addr_cycles--) {
		int max_page_size = conf->addr_cycles == 4 ? 2048 : 16384;

		/*
		 * Ignoring 1k pages cause I'm not even sure this case exist
		 * in the real world.
		 */
		for (conf->page_size = 2048; conf->page_size <= max_page_size;
		     conf->page_size <<= 1) {
			if (nand_load_page(conf, offs))
				return -1;

			if (!nand_detect_ecc_config(conf, offs, dest)) {
				conf->valid = true;
				return 0;
			}
		}
	}

	return -EINVAL;
}

static int nand_read_buffer(struct nfc_config *conf, uint32_t offs,
			    unsigned int size, void *dest)
{
	int first_seed = 0, page, ret;

	size = ALIGN(size, conf->page_size);
	page = offs / conf->page_size;
	if (conf->randomize)
		first_seed = page % conf->nseeds;

	for (; size; size -= conf->page_size) {
		if (nand_load_page(conf, offs))
			return -1;

		ret = nand_read_page(conf, offs, dest, conf->page_size);
		/*
		 * The ->nseeds value should be equal to the number of pages
		 * in an eraseblock. Since we don't know this information in
		 * advance we might have picked a wrong value.
		 */
		if (ret < 0 && conf->randomize) {
			int cur_seed = page % conf->nseeds;

			/*
			 * We already tried all the seed values => we are
			 * facing a real corruption.
			 */
			if (cur_seed < first_seed)
				return -EIO;

			/* Try to adjust ->nseeds and read the page again... */
			conf->nseeds = cur_seed;

			if (nand_change_column(0))
				return -EIO;

			/* ... it still fails => it's a real corruption. */
			if (nand_read_page(conf, offs, dest, conf->page_size))
				return -EIO;
		} else if (ret && conf->randomize) {
			memset(dest, 0xff, conf->page_size);
		}

		page++;
		offs += conf->page_size;
		dest += conf->page_size;
	}

	return 0;
}

int nand_spl_load_image(uint32_t offs, unsigned int size, void *dest)
{
	static struct nfc_config conf = { };
	int ret;

	ret = nand_detect_config(&conf, offs, dest);
	if (ret)
		return ret;

	return nand_read_buffer(&conf, offs, size, dest);
}

void nand_deselect(void)
{
	struct sunxi_ccm_reg *const ccm =
		(struct sunxi_ccm_reg *)SUNXI_CCM_BASE;

	clrbits_le32(&ccm->ahb_gate0, (CLK_GATE_OPEN << AHB_GATE_OFFSET_NAND0));
#ifdef CONFIG_MACH_SUN9I
	clrbits_le32(&ccm->ahb_gate1, (1 << AHB_GATE_OFFSET_DMA));
#else
	clrbits_le32(&ccm->ahb_gate0, (1 << AHB_GATE_OFFSET_DMA));
#endif
	clrbits_le32(&ccm->nand0_clk_cfg, CCM_NAND_CTRL_ENABLE | AHB_DIV_1);
}
