/*
 * Arasan NAND Flash Controller Driver
 *
 * Copyright (C) 2014 - 2015 Xilinx, Inc.
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <malloc.h>
#include <asm/io.h>
#include <linux/errno.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/rawnand.h>
#include <linux/mtd/partitions.h>
#include <linux/mtd/nand_ecc.h>
#include <asm/arch/hardware.h>
#include <asm/arch/sys_proto.h>
#include <nand.h>

struct arasan_nand_info {
	void __iomem *nand_base;
	u32 page;
	bool on_die_ecc_enabled;
};

struct nand_regs {
	u32 pkt_reg;
	u32 memadr_reg1;
	u32 memadr_reg2;
	u32 cmd_reg;
	u32 pgm_reg;
	u32 intsts_enr;
	u32 intsig_enr;
	u32 intsts_reg;
	u32 rdy_busy;
	u32 cms_sysadr_reg;
	u32 flash_sts_reg;
	u32 tmg_reg;
	u32 buf_dataport;
	u32 ecc_reg;
	u32 ecc_errcnt_reg;
	u32 ecc_sprcmd_reg;
	u32 errcnt_1bitreg;
	u32 errcnt_2bitreg;
	u32 errcnt_3bitreg;
	u32 errcnt_4bitreg;
	u32 dma_sysadr0_reg;
	u32 dma_bufbdry_reg;
	u32 cpu_rls_reg;
	u32 errcnt_5bitreg;
	u32 errcnt_6bitreg;
	u32 errcnt_7bitreg;
	u32 errcnt_8bitreg;
	u32 data_if_reg;
};

#define arasan_nand_base ((struct nand_regs __iomem *)ARASAN_NAND_BASEADDR)

struct arasan_nand_command_format {
	u8 cmd1;
	u8 cmd2;
	u8 addr_cycles;
	u32 pgm;
};

#define ONDIE_ECC_FEATURE_ADDR			0x90
#define ENABLE_ONDIE_ECC			0x08

#define ARASAN_PROG_RD_MASK			0x00000001
#define ARASAN_PROG_BLK_ERS_MASK		0x00000004
#define ARASAN_PROG_RD_ID_MASK			0x00000040
#define ARASAN_PROG_RD_STS_MASK			0x00000008
#define ARASAN_PROG_PG_PROG_MASK		0x00000010
#define ARASAN_PROG_RD_PARAM_PG_MASK		0x00000080
#define ARASAN_PROG_RST_MASK			0x00000100
#define ARASAN_PROG_GET_FTRS_MASK		0x00000200
#define ARASAN_PROG_SET_FTRS_MASK		0x00000400
#define ARASAN_PROG_CHNG_ROWADR_END_MASK	0x00400000

#define ARASAN_NAND_CMD_ECC_ON_MASK		0x80000000
#define ARASAN_NAND_CMD_CMD12_MASK		0xFFFF
#define ARASAN_NAND_CMD_PG_SIZE_MASK		0x3800000
#define ARASAN_NAND_CMD_PG_SIZE_SHIFT		23
#define ARASAN_NAND_CMD_CMD2_SHIFT		8
#define ARASAN_NAND_CMD_ADDR_CYCL_MASK		0x70000000
#define ARASAN_NAND_CMD_ADDR_CYCL_SHIFT		28

#define ARASAN_NAND_MEM_ADDR1_PAGE_MASK		0xFFFF0000
#define ARASAN_NAND_MEM_ADDR1_COL_MASK		0xFFFF
#define ARASAN_NAND_MEM_ADDR1_PAGE_SHIFT	16
#define ARASAN_NAND_MEM_ADDR2_PAGE_MASK		0xFF
#define ARASAN_NAND_MEM_ADDR2_CS_MASK		0xC0000000
#define ARASAN_NAND_MEM_ADDR2_CS0_MASK         (0x3 << 30)
#define ARASAN_NAND_MEM_ADDR2_CS1_MASK         (0x1 << 30)
#define ARASAN_NAND_MEM_ADDR2_BCH_MASK		0xE000000
#define ARASAN_NAND_MEM_ADDR2_BCH_SHIFT		25

#define ARASAN_NAND_INT_STS_ERR_EN_MASK		0x10
#define ARASAN_NAND_INT_STS_MUL_BIT_ERR_MASK	0x08
#define ARASAN_NAND_INT_STS_BUF_RD_RDY_MASK	0x02
#define ARASAN_NAND_INT_STS_BUF_WR_RDY_MASK	0x01
#define ARASAN_NAND_INT_STS_XFR_CMPLT_MASK	0x04

#define ARASAN_NAND_PKT_REG_PKT_CNT_MASK	0xFFF000
#define ARASAN_NAND_PKT_REG_PKT_SIZE_MASK	0x7FF
#define ARASAN_NAND_PKT_REG_PKT_CNT_SHFT	12

#define ARASAN_NAND_ROW_ADDR_CYCL_MASK		0x0F
#define ARASAN_NAND_COL_ADDR_CYCL_MASK		0xF0
#define ARASAN_NAND_COL_ADDR_CYCL_SHIFT		4

#define ARASAN_NAND_ECC_SIZE_SHIFT		16
#define ARASAN_NAND_ECC_BCH_SHIFT		27

#define ARASAN_NAND_PKTSIZE_1K			1024
#define ARASAN_NAND_PKTSIZE_512			512

#define ARASAN_NAND_POLL_TIMEOUT		1000000
#define ARASAN_NAND_INVALID_ADDR_CYCL		0xFF

#define ERR_ADDR_CYCLE				-1
#define READ_BUFF_SIZE				0x4000

static struct arasan_nand_command_format *curr_cmd;

enum addr_cycles {
	NAND_ADDR_CYCL_NONE,
	NAND_ADDR_CYCL_ONE,
	NAND_ADDR_CYCL_ROW,
	NAND_ADDR_CYCL_COL,
	NAND_ADDR_CYCL_BOTH,
};

static struct arasan_nand_command_format arasan_nand_commands[] = {
	{NAND_CMD_READ0, NAND_CMD_READSTART, NAND_ADDR_CYCL_BOTH,
	 ARASAN_PROG_RD_MASK},
	{NAND_CMD_RNDOUT, NAND_CMD_RNDOUTSTART, NAND_ADDR_CYCL_COL,
	 ARASAN_PROG_RD_MASK},
	{NAND_CMD_READID, NAND_CMD_NONE, NAND_ADDR_CYCL_ONE,
	 ARASAN_PROG_RD_ID_MASK},
	{NAND_CMD_STATUS, NAND_CMD_NONE, NAND_ADDR_CYCL_NONE,
	 ARASAN_PROG_RD_STS_MASK},
	{NAND_CMD_SEQIN, NAND_CMD_PAGEPROG, NAND_ADDR_CYCL_BOTH,
	 ARASAN_PROG_PG_PROG_MASK},
	{NAND_CMD_RNDIN, NAND_CMD_NONE, NAND_ADDR_CYCL_COL,
	 ARASAN_PROG_CHNG_ROWADR_END_MASK},
	{NAND_CMD_ERASE1, NAND_CMD_ERASE2, NAND_ADDR_CYCL_ROW,
	 ARASAN_PROG_BLK_ERS_MASK},
	{NAND_CMD_RESET, NAND_CMD_NONE, NAND_ADDR_CYCL_NONE,
	 ARASAN_PROG_RST_MASK},
	{NAND_CMD_PARAM, NAND_CMD_NONE, NAND_ADDR_CYCL_ONE,
	 ARASAN_PROG_RD_PARAM_PG_MASK},
	{NAND_CMD_GET_FEATURES, NAND_CMD_NONE, NAND_ADDR_CYCL_ONE,
	 ARASAN_PROG_GET_FTRS_MASK},
	{NAND_CMD_SET_FEATURES, NAND_CMD_NONE, NAND_ADDR_CYCL_ONE,
	 ARASAN_PROG_SET_FTRS_MASK},
	{NAND_CMD_NONE, NAND_CMD_NONE, NAND_ADDR_CYCL_NONE, 0},
};

struct arasan_ecc_matrix {
	u32 pagesize;
	u32 ecc_codeword_size;
	u8 eccbits;
	u8 bch;
	u8 bchval;
	u16 eccaddr;
	u16 eccsize;
};

static const struct arasan_ecc_matrix ecc_matrix[] = {
	{512, 512, 1, 0, 0, 0x20D, 0x3},
	{512, 512, 4, 1, 3, 0x209, 0x7},
	{512, 512, 8, 1, 2, 0x203, 0xD},
	/*
	 * 2K byte page
	 */
	{2048, 512, 1, 0, 0, 0x834, 0xC},
	{2048, 512, 4, 1, 3, 0x826, 0x1A},
	{2048, 512, 8, 1, 2, 0x80c, 0x34},
	{2048, 512, 12, 1, 1, 0x822, 0x4E},
	{2048, 512, 16, 1, 0, 0x808, 0x68},
	{2048, 1024, 24, 1, 4, 0x81c, 0x54},
	/*
	 * 4K byte page
	 */
	{4096, 512, 1, 0, 0, 0x1068, 0x18},
	{4096, 512, 4, 1, 3, 0x104c, 0x34},
	{4096, 512, 8, 1, 2, 0x1018, 0x68},
	{4096, 512, 12, 1, 1, 0x1044, 0x9C},
	{4096, 512, 16, 1, 0, 0x1010, 0xD0},
	{4096, 1024, 24, 1, 4, 0x1038, 0xA8},
	/*
	 * 8K byte page
	 */
	{8192, 512, 1, 0, 0, 0x20d0, 0x30},
	{8192, 512, 4, 1, 3, 0x2098, 0x68},
	{8192, 512, 8, 1, 2, 0x2030, 0xD0},
	{8192, 512, 12, 1, 1, 0x2088, 0x138},
	{8192, 512, 16, 1, 0, 0x2020, 0x1A0},
	{8192, 1024, 24, 1, 4, 0x2070, 0x150},
	/*
	 * 16K byte page
	 */
	{16384, 512, 1, 0, 0, 0x4460, 0x60},
	{16384, 512, 4, 1, 3, 0x43f0, 0xD0},
	{16384, 512, 8, 1, 2, 0x4320, 0x1A0},
	{16384, 512, 12, 1, 1, 0x4250, 0x270},
	{16384, 512, 16, 1, 0, 0x4180, 0x340},
	{16384, 1024, 24, 1, 4, 0x4220, 0x2A0}
};

static struct nand_ecclayout ondie_nand_oob_64 = {
	.eccbytes = 32,

	.eccpos = {
		8, 9, 10, 11, 12, 13, 14, 15,
		24, 25, 26, 27, 28, 29, 30, 31,
		40, 41, 42, 43, 44, 45, 46, 47,
		56, 57, 58, 59, 60, 61, 62, 63
	},

	.oobfree = {
		{ .offset = 4, .length = 4 },
		{ .offset = 20, .length = 4 },
		{ .offset = 36, .length = 4 },
		{ .offset = 52, .length = 4 }
	}
};

/*
 * bbt decriptors for chips with on-die ECC and
 * chips with 64-byte OOB
 */
static u8 bbt_pattern[] = {'B', 'b', 't', '0' };
static u8 mirror_pattern[] = {'1', 't', 'b', 'B' };

static struct nand_bbt_descr bbt_main_descr = {
	.options = NAND_BBT_LASTBLOCK | NAND_BBT_CREATE | NAND_BBT_WRITE |
		NAND_BBT_2BIT | NAND_BBT_VERSION | NAND_BBT_PERCHIP,
	.offs = 4,
	.len = 4,
	.veroffs = 20,
	.maxblocks = 4,
	.pattern = bbt_pattern
};

static struct nand_bbt_descr bbt_mirror_descr = {
	.options = NAND_BBT_LASTBLOCK | NAND_BBT_CREATE | NAND_BBT_WRITE |
		NAND_BBT_2BIT | NAND_BBT_VERSION | NAND_BBT_PERCHIP,
	.offs = 4,
	.len = 4,
	.veroffs = 20,
	.maxblocks = 4,
	.pattern = mirror_pattern
};

static u8 buf_data[READ_BUFF_SIZE];
static u32 buf_index;

static struct nand_ecclayout nand_oob;

static struct nand_chip nand_chip[CONFIG_SYS_MAX_NAND_DEVICE];

static void arasan_nand_select_chip(struct mtd_info *mtd, int chip)
{
	u32 reg_val;

	reg_val = readl(&arasan_nand_base->memadr_reg2);
	if (chip == 0) {
		reg_val &= ~ARASAN_NAND_MEM_ADDR2_CS0_MASK;
		writel(reg_val, &arasan_nand_base->memadr_reg2);
	} else if (chip == 1) {
		reg_val |= ARASAN_NAND_MEM_ADDR2_CS1_MASK;
		writel(reg_val, &arasan_nand_base->memadr_reg2);
	}
}

static void arasan_nand_enable_ecc(void)
{
	u32 reg_val;

	reg_val = readl(&arasan_nand_base->cmd_reg);
	reg_val |= ARASAN_NAND_CMD_ECC_ON_MASK;

	writel(reg_val, &arasan_nand_base->cmd_reg);
}

static u8 arasan_nand_get_addrcycle(struct mtd_info *mtd)
{
	u8 addrcycles;
	struct nand_chip *chip = mtd_to_nand(mtd);

	switch (curr_cmd->addr_cycles) {
	case NAND_ADDR_CYCL_NONE:
		addrcycles = 0;
		break;
	case NAND_ADDR_CYCL_ONE:
		addrcycles = 1;
		break;
	case NAND_ADDR_CYCL_ROW:
		addrcycles = chip->onfi_params.addr_cycles &
			     ARASAN_NAND_ROW_ADDR_CYCL_MASK;
		break;
	case NAND_ADDR_CYCL_COL:
		addrcycles = (chip->onfi_params.addr_cycles &
			      ARASAN_NAND_COL_ADDR_CYCL_MASK) >>
			      ARASAN_NAND_COL_ADDR_CYCL_SHIFT;
		break;
	case NAND_ADDR_CYCL_BOTH:
		addrcycles = chip->onfi_params.addr_cycles &
			     ARASAN_NAND_ROW_ADDR_CYCL_MASK;
		addrcycles += (chip->onfi_params.addr_cycles &
			       ARASAN_NAND_COL_ADDR_CYCL_MASK) >>
			       ARASAN_NAND_COL_ADDR_CYCL_SHIFT;
		break;
	default:
		addrcycles = ARASAN_NAND_INVALID_ADDR_CYCL;
		break;
	}
	return addrcycles;
}

static int arasan_nand_read_page(struct mtd_info *mtd, u8 *buf, u32 size)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct arasan_nand_info *nand = nand_get_controller_data(chip);
	u32 reg_val, i, pktsize, pktnum;
	u32 *bufptr = (u32 *)buf;
	u32 timeout;
	u32  rdcount = 0;
	u8 addr_cycles;

	if (chip->ecc_step_ds >= ARASAN_NAND_PKTSIZE_1K)
		pktsize = ARASAN_NAND_PKTSIZE_1K;
	else
		pktsize = ARASAN_NAND_PKTSIZE_512;

	if (size % pktsize)
		pktnum = size/pktsize + 1;
	else
		pktnum = size/pktsize;

	reg_val = readl(&arasan_nand_base->intsts_enr);
	reg_val |= ARASAN_NAND_INT_STS_ERR_EN_MASK |
		   ARASAN_NAND_INT_STS_MUL_BIT_ERR_MASK;
	writel(reg_val, &arasan_nand_base->intsts_enr);

	reg_val = readl(&arasan_nand_base->pkt_reg);
	reg_val &= ~(ARASAN_NAND_PKT_REG_PKT_CNT_MASK |
		     ARASAN_NAND_PKT_REG_PKT_SIZE_MASK);
	reg_val |= (pktnum << ARASAN_NAND_PKT_REG_PKT_CNT_SHFT) |
		    pktsize;
	writel(reg_val, &arasan_nand_base->pkt_reg);

	if (!nand->on_die_ecc_enabled) {
		arasan_nand_enable_ecc();
		addr_cycles = arasan_nand_get_addrcycle(mtd);
		if (addr_cycles == ARASAN_NAND_INVALID_ADDR_CYCL)
			return ERR_ADDR_CYCLE;

		writel((NAND_CMD_RNDOUTSTART << ARASAN_NAND_CMD_CMD2_SHIFT) |
		       NAND_CMD_RNDOUT | (addr_cycles <<
		       ARASAN_NAND_CMD_ADDR_CYCL_SHIFT),
		       &arasan_nand_base->ecc_sprcmd_reg);
	}
	writel(curr_cmd->pgm, &arasan_nand_base->pgm_reg);

	while (rdcount < pktnum) {
		timeout = ARASAN_NAND_POLL_TIMEOUT;
		while (!(readl(&arasan_nand_base->intsts_reg) &
			ARASAN_NAND_INT_STS_BUF_RD_RDY_MASK) && timeout) {
			udelay(1);
			timeout--;
		}
		if (!timeout) {
			puts("arasan_read_page: timedout:Buff RDY\n");
			return -ETIMEDOUT;
		}

		rdcount++;

		if (pktnum == rdcount) {
			reg_val = readl(&arasan_nand_base->intsts_enr);
			reg_val |= ARASAN_NAND_INT_STS_XFR_CMPLT_MASK;
			writel(reg_val, &arasan_nand_base->intsts_enr);
		} else {
			reg_val = readl(&arasan_nand_base->intsts_enr);
			writel(reg_val | ARASAN_NAND_INT_STS_BUF_RD_RDY_MASK,
			       &arasan_nand_base->intsts_enr);
		}
		reg_val = readl(&arasan_nand_base->intsts_reg);
		writel(reg_val | ARASAN_NAND_INT_STS_BUF_RD_RDY_MASK,
		       &arasan_nand_base->intsts_reg);

		for (i = 0; i < pktsize/4; i++)
			bufptr[i] = readl(&arasan_nand_base->buf_dataport);


		bufptr += pktsize/4;

		if (rdcount >= pktnum)
			break;

		writel(ARASAN_NAND_INT_STS_BUF_RD_RDY_MASK,
		       &arasan_nand_base->intsts_enr);
	}

	timeout = ARASAN_NAND_POLL_TIMEOUT;

	while (!(readl(&arasan_nand_base->intsts_reg) &
		ARASAN_NAND_INT_STS_XFR_CMPLT_MASK) && timeout) {
		udelay(1);
		timeout--;
	}
	if (!timeout) {
		puts("arasan rd_page timedout:Xfer CMPLT\n");
		return -ETIMEDOUT;
	}

	reg_val = readl(&arasan_nand_base->intsts_enr);
	writel(reg_val | ARASAN_NAND_INT_STS_XFR_CMPLT_MASK,
	       &arasan_nand_base->intsts_enr);
	reg_val = readl(&arasan_nand_base->intsts_reg);
	writel(reg_val | ARASAN_NAND_INT_STS_XFR_CMPLT_MASK,
	       &arasan_nand_base->intsts_reg);

	if (!nand->on_die_ecc_enabled) {
		if (readl(&arasan_nand_base->intsts_reg) &
		    ARASAN_NAND_INT_STS_MUL_BIT_ERR_MASK) {
			printf("arasan rd_page:sbiterror\n");
			return -1;
		}

		if (readl(&arasan_nand_base->intsts_reg) &
		    ARASAN_NAND_INT_STS_ERR_EN_MASK) {
			mtd->ecc_stats.failed++;
			printf("arasan rd_page:multibiterror\n");
			return -1;
		}
	}

	return 0;
}

static int arasan_nand_read_page_hwecc(struct mtd_info *mtd,
		struct nand_chip *chip, u8 *buf, int oob_required, int page)
{
	int status;

	status = arasan_nand_read_page(mtd, buf, (mtd->writesize));

	if (oob_required)
		chip->ecc.read_oob(mtd, chip, page);

	return status;
}

static void arasan_nand_fill_tx(const u8 *buf, int len)
{
	u32 __iomem *nand = &arasan_nand_base->buf_dataport;

	if (((unsigned long)buf & 0x3) != 0) {
		if (((unsigned long)buf & 0x1) != 0) {
			if (len) {
				writeb(*buf, nand);
				buf += 1;
				len--;
			}
		}

		if (((unsigned long)buf & 0x3) != 0) {
			if (len >= 2) {
				writew(*(u16 *)buf, nand);
				buf += 2;
				len -= 2;
			}
		}
	}

	while (len >= 4) {
		writel(*(u32 *)buf, nand);
		buf += 4;
		len -= 4;
	}

	if (len) {
		if (len >= 2) {
			writew(*(u16 *)buf, nand);
			buf += 2;
			len -= 2;
		}

		if (len)
			writeb(*buf, nand);
	}
}

static int arasan_nand_write_page_hwecc(struct mtd_info *mtd,
		struct nand_chip *chip, const u8 *buf, int oob_required,
		int page)
{
	u32 reg_val, i, pktsize, pktnum;
	const u32 *bufptr = (const u32 *)buf;
	u32 timeout = ARASAN_NAND_POLL_TIMEOUT;
	u32 size = mtd->writesize;
	u32 rdcount = 0;
	u8 column_addr_cycles;
	struct arasan_nand_info *nand = nand_get_controller_data(chip);

	if (chip->ecc_step_ds >= ARASAN_NAND_PKTSIZE_1K)
		pktsize = ARASAN_NAND_PKTSIZE_1K;
	else
		pktsize = ARASAN_NAND_PKTSIZE_512;

	if (size % pktsize)
		pktnum = size/pktsize + 1;
	else
		pktnum = size/pktsize;

	reg_val = readl(&arasan_nand_base->pkt_reg);
	reg_val &= ~(ARASAN_NAND_PKT_REG_PKT_CNT_MASK |
		     ARASAN_NAND_PKT_REG_PKT_SIZE_MASK);
	reg_val |= (pktnum << ARASAN_NAND_PKT_REG_PKT_CNT_SHFT) | pktsize;
	writel(reg_val, &arasan_nand_base->pkt_reg);

	if (!nand->on_die_ecc_enabled) {
		arasan_nand_enable_ecc();
		column_addr_cycles = (chip->onfi_params.addr_cycles &
				      ARASAN_NAND_COL_ADDR_CYCL_MASK) >>
				      ARASAN_NAND_COL_ADDR_CYCL_SHIFT;
		writel((NAND_CMD_RNDIN | (column_addr_cycles << 28)),
		       &arasan_nand_base->ecc_sprcmd_reg);
	}
	writel(curr_cmd->pgm, &arasan_nand_base->pgm_reg);

	while (rdcount < pktnum) {
		timeout = ARASAN_NAND_POLL_TIMEOUT;
		while (!(readl(&arasan_nand_base->intsts_reg) &
			ARASAN_NAND_INT_STS_BUF_WR_RDY_MASK) && timeout) {
			udelay(1);
			timeout--;
		}

		if (!timeout) {
			puts("arasan_write_page: timedout:Buff RDY\n");
			return -ETIMEDOUT;
		}

		rdcount++;

		if (pktnum == rdcount) {
			reg_val = readl(&arasan_nand_base->intsts_enr);
			reg_val |= ARASAN_NAND_INT_STS_XFR_CMPLT_MASK;
			writel(reg_val, &arasan_nand_base->intsts_enr);
		} else {
			reg_val = readl(&arasan_nand_base->intsts_enr);
			writel(reg_val | ARASAN_NAND_INT_STS_BUF_WR_RDY_MASK,
			       &arasan_nand_base->intsts_enr);
		}

		reg_val = readl(&arasan_nand_base->intsts_reg);
		writel(reg_val | ARASAN_NAND_INT_STS_BUF_WR_RDY_MASK,
		       &arasan_nand_base->intsts_reg);

		for (i = 0; i < pktsize/4; i++)
			writel(bufptr[i], &arasan_nand_base->buf_dataport);

		bufptr += pktsize/4;

		if (rdcount >= pktnum)
			break;

		writel(ARASAN_NAND_INT_STS_BUF_WR_RDY_MASK,
		       &arasan_nand_base->intsts_enr);
	}

	timeout = ARASAN_NAND_POLL_TIMEOUT;

	while (!(readl(&arasan_nand_base->intsts_reg) &
		ARASAN_NAND_INT_STS_XFR_CMPLT_MASK) && timeout) {
		udelay(1);
		timeout--;
	}
	if (!timeout) {
		puts("arasan write_page timedout:Xfer CMPLT\n");
		return -ETIMEDOUT;
	}

	reg_val = readl(&arasan_nand_base->intsts_enr);
	writel(reg_val | ARASAN_NAND_INT_STS_XFR_CMPLT_MASK,
	       &arasan_nand_base->intsts_enr);
	reg_val = readl(&arasan_nand_base->intsts_reg);
	writel(reg_val | ARASAN_NAND_INT_STS_XFR_CMPLT_MASK,
	       &arasan_nand_base->intsts_reg);

	if (oob_required)
		chip->ecc.write_oob(mtd, chip, nand->page);

	return 0;
}

static int arasan_nand_read_oob(struct mtd_info *mtd, struct nand_chip *chip,
				int page)
{
	chip->cmdfunc(mtd, NAND_CMD_READOOB, 0, page);
	chip->read_buf(mtd, chip->oob_poi, (mtd->oobsize));

	return 0;
}

static int arasan_nand_write_oob(struct mtd_info *mtd, struct nand_chip *chip,
				 int page)
{
	int status = 0;
	const u8 *buf = chip->oob_poi;

	chip->cmdfunc(mtd, NAND_CMD_SEQIN, mtd->writesize, page);
	chip->write_buf(mtd, buf, mtd->oobsize);

	return status;
}

static int arasan_nand_reset(struct arasan_nand_command_format *curr_cmd)
{
	u32 timeout = ARASAN_NAND_POLL_TIMEOUT;
	u32 cmd_reg = 0;

	writel(ARASAN_NAND_INT_STS_XFR_CMPLT_MASK,
	       &arasan_nand_base->intsts_enr);
	cmd_reg = readl(&arasan_nand_base->cmd_reg);
	cmd_reg &= ~ARASAN_NAND_CMD_CMD12_MASK;

	cmd_reg |= curr_cmd->cmd1 |
		  (curr_cmd->cmd2 << ARASAN_NAND_CMD_CMD2_SHIFT);
	writel(cmd_reg, &arasan_nand_base->cmd_reg);
	writel(curr_cmd->pgm, &arasan_nand_base->pgm_reg);

	while (!(readl(&arasan_nand_base->intsts_reg) &
		ARASAN_NAND_INT_STS_XFR_CMPLT_MASK) && timeout) {
		udelay(1);
		timeout--;
	}
	if (!timeout) {
		printf("ERROR:%s timedout\n", __func__);
		return -ETIMEDOUT;
	}

	writel(ARASAN_NAND_INT_STS_XFR_CMPLT_MASK,
	       &arasan_nand_base->intsts_enr);

	writel(ARASAN_NAND_INT_STS_XFR_CMPLT_MASK,
	       &arasan_nand_base->intsts_reg);

	return 0;
}

static u8 arasan_nand_page(struct mtd_info *mtd)
{
	u8 page_val = 0;

	switch (mtd->writesize) {
	case 512:
		page_val = 0;
		break;
	case 2048:
		page_val = 1;
		break;
	case 4096:
		page_val = 2;
		break;
	case 8192:
		page_val = 3;
		break;
	case 16384:
		page_val = 4;
		break;
	case 1024:
		page_val = 5;
		break;
	default:
		printf("%s:Pagesize>16K\n", __func__);
		break;
	}

	return page_val;
}

static int arasan_nand_send_wrcmd(struct arasan_nand_command_format *curr_cmd,
			int column, int page_addr, struct mtd_info *mtd)
{
	u32 reg_val, page;
	u8 page_val, addr_cycles;

	writel(ARASAN_NAND_INT_STS_BUF_WR_RDY_MASK,
	       &arasan_nand_base->intsts_enr);
	reg_val = readl(&arasan_nand_base->cmd_reg);
	reg_val &= ~ARASAN_NAND_CMD_CMD12_MASK;
	reg_val |= curr_cmd->cmd1 |
		   (curr_cmd->cmd2 << ARASAN_NAND_CMD_CMD2_SHIFT);
	if (curr_cmd->cmd1 == NAND_CMD_SEQIN) {
		reg_val &= ~ARASAN_NAND_CMD_PG_SIZE_MASK;
		page_val = arasan_nand_page(mtd);
		reg_val |= (page_val << ARASAN_NAND_CMD_PG_SIZE_SHIFT);
	}

	reg_val &= ~ARASAN_NAND_CMD_ADDR_CYCL_MASK;
	addr_cycles = arasan_nand_get_addrcycle(mtd);

	if (addr_cycles == ARASAN_NAND_INVALID_ADDR_CYCL)
		return ERR_ADDR_CYCLE;

	reg_val |= (addr_cycles <<
		   ARASAN_NAND_CMD_ADDR_CYCL_SHIFT);
	writel(reg_val, &arasan_nand_base->cmd_reg);

	if (page_addr == -1)
		page_addr = 0;

	page = (page_addr << ARASAN_NAND_MEM_ADDR1_PAGE_SHIFT) &
		ARASAN_NAND_MEM_ADDR1_PAGE_MASK;
	column &= ARASAN_NAND_MEM_ADDR1_COL_MASK;
	writel(page|column, &arasan_nand_base->memadr_reg1);

	reg_val = readl(&arasan_nand_base->memadr_reg2);
	reg_val &= ~ARASAN_NAND_MEM_ADDR2_PAGE_MASK;
	reg_val |= (page_addr >> ARASAN_NAND_MEM_ADDR1_PAGE_SHIFT);
	writel(reg_val, &arasan_nand_base->memadr_reg2);

	return 0;
}

static void arasan_nand_write_buf(struct mtd_info *mtd, const u8 *buf, int len)
{
	u32 reg_val;
	u32 timeout = ARASAN_NAND_POLL_TIMEOUT;

	reg_val = readl(&arasan_nand_base->pkt_reg);
	reg_val &= ~(ARASAN_NAND_PKT_REG_PKT_CNT_MASK |
		     ARASAN_NAND_PKT_REG_PKT_SIZE_MASK);

	reg_val |= (1 << ARASAN_NAND_PKT_REG_PKT_CNT_SHFT) | len;
	writel(reg_val, &arasan_nand_base->pkt_reg);
	writel(curr_cmd->pgm, &arasan_nand_base->pgm_reg);

	while (!(readl(&arasan_nand_base->intsts_reg) &
		ARASAN_NAND_INT_STS_BUF_WR_RDY_MASK) && timeout) {
		udelay(1);
		timeout--;
	}

	if (!timeout)
		puts("ERROR:arasan_nand_write_buf timedout:Buff RDY\n");

	reg_val = readl(&arasan_nand_base->intsts_enr);
	reg_val |= ARASAN_NAND_INT_STS_XFR_CMPLT_MASK;
	writel(reg_val, &arasan_nand_base->intsts_enr);
	writel(reg_val | ARASAN_NAND_INT_STS_BUF_WR_RDY_MASK,
	       &arasan_nand_base->intsts_enr);
	reg_val = readl(&arasan_nand_base->intsts_reg);
	writel(reg_val | ARASAN_NAND_INT_STS_BUF_WR_RDY_MASK,
	       &arasan_nand_base->intsts_reg);

	arasan_nand_fill_tx(buf, len);

	timeout = ARASAN_NAND_POLL_TIMEOUT;
	while (!(readl(&arasan_nand_base->intsts_reg) &
		ARASAN_NAND_INT_STS_XFR_CMPLT_MASK) && timeout) {
		udelay(1);
		timeout--;
	}
	if (!timeout)
		puts("ERROR:arasan_nand_write_buf timedout:Xfer CMPLT\n");

	writel(readl(&arasan_nand_base->intsts_enr) |
	       ARASAN_NAND_INT_STS_XFR_CMPLT_MASK,
	       &arasan_nand_base->intsts_enr);
	writel(readl(&arasan_nand_base->intsts_reg) |
	       ARASAN_NAND_INT_STS_XFR_CMPLT_MASK,
	       &arasan_nand_base->intsts_reg);
}

static int arasan_nand_erase(struct arasan_nand_command_format *curr_cmd,
			      int column, int page_addr, struct mtd_info *mtd)
{
	u32 reg_val, page;
	u32 timeout = ARASAN_NAND_POLL_TIMEOUT;
	u8 row_addr_cycles;

	writel(ARASAN_NAND_INT_STS_XFR_CMPLT_MASK,
	       &arasan_nand_base->intsts_enr);
	reg_val = readl(&arasan_nand_base->cmd_reg);
	reg_val &= ~ARASAN_NAND_CMD_CMD12_MASK;
	reg_val |= curr_cmd->cmd1 |
		   (curr_cmd->cmd2 << ARASAN_NAND_CMD_CMD2_SHIFT);
	row_addr_cycles = arasan_nand_get_addrcycle(mtd);

	if (row_addr_cycles == ARASAN_NAND_INVALID_ADDR_CYCL)
		return ERR_ADDR_CYCLE;

	reg_val &= ~ARASAN_NAND_CMD_ADDR_CYCL_MASK;
	reg_val |= (row_addr_cycles <<
		    ARASAN_NAND_CMD_ADDR_CYCL_SHIFT);

	writel(reg_val, &arasan_nand_base->cmd_reg);

	page = (page_addr >> ARASAN_NAND_MEM_ADDR1_PAGE_SHIFT) &
		ARASAN_NAND_MEM_ADDR1_COL_MASK;
	column = page_addr & ARASAN_NAND_MEM_ADDR1_COL_MASK;
	writel(column | (page << ARASAN_NAND_MEM_ADDR1_PAGE_SHIFT),
	       &arasan_nand_base->memadr_reg1);

	reg_val = readl(&arasan_nand_base->memadr_reg2);
	reg_val &= ~ARASAN_NAND_MEM_ADDR2_PAGE_MASK;
	reg_val |= (page_addr >> ARASAN_NAND_MEM_ADDR1_PAGE_SHIFT);
	writel(reg_val, &arasan_nand_base->memadr_reg2);
	writel(curr_cmd->pgm, &arasan_nand_base->pgm_reg);

	while (!(readl(&arasan_nand_base->intsts_reg) &
		ARASAN_NAND_INT_STS_XFR_CMPLT_MASK) && timeout) {
		udelay(1);
		timeout--;
	}
	if (!timeout) {
		printf("ERROR:%s timedout:Xfer CMPLT\n", __func__);
		return -ETIMEDOUT;
	}

	reg_val = readl(&arasan_nand_base->intsts_enr);
	writel(reg_val | ARASAN_NAND_INT_STS_XFR_CMPLT_MASK,
	       &arasan_nand_base->intsts_enr);
	reg_val = readl(&arasan_nand_base->intsts_reg);
	writel(reg_val | ARASAN_NAND_INT_STS_XFR_CMPLT_MASK,
	       &arasan_nand_base->intsts_reg);

	return 0;
}

static int arasan_nand_read_status(struct arasan_nand_command_format *curr_cmd,
				int column, int page_addr, struct mtd_info *mtd)
{
	u32 reg_val;
	u32 timeout = ARASAN_NAND_POLL_TIMEOUT;
	u8 addr_cycles;

	writel(ARASAN_NAND_INT_STS_XFR_CMPLT_MASK,
	       &arasan_nand_base->intsts_enr);
	reg_val = readl(&arasan_nand_base->cmd_reg);
	reg_val &= ~ARASAN_NAND_CMD_CMD12_MASK;
	reg_val |= curr_cmd->cmd1 |
		   (curr_cmd->cmd2 << ARASAN_NAND_CMD_CMD2_SHIFT);
	addr_cycles = arasan_nand_get_addrcycle(mtd);

	if (addr_cycles == ARASAN_NAND_INVALID_ADDR_CYCL)
		return ERR_ADDR_CYCLE;

	reg_val &= ~ARASAN_NAND_CMD_ADDR_CYCL_MASK;
	reg_val |= (addr_cycles <<
		    ARASAN_NAND_CMD_ADDR_CYCL_SHIFT);

	writel(reg_val, &arasan_nand_base->cmd_reg);

	reg_val = readl(&arasan_nand_base->pkt_reg);
	reg_val &= ~(ARASAN_NAND_PKT_REG_PKT_CNT_MASK |
		     ARASAN_NAND_PKT_REG_PKT_SIZE_MASK);
	reg_val |= (1 << ARASAN_NAND_PKT_REG_PKT_CNT_SHFT) | 1;
	writel(reg_val, &arasan_nand_base->pkt_reg);

	writel(curr_cmd->pgm, &arasan_nand_base->pgm_reg);
	while (!(readl(&arasan_nand_base->intsts_reg) &
		ARASAN_NAND_INT_STS_XFR_CMPLT_MASK) && timeout) {
		udelay(1);
		timeout--;
	}

	if (!timeout) {
		printf("ERROR:%s: timedout:Xfer CMPLT\n", __func__);
		return -ETIMEDOUT;
	}

	reg_val = readl(&arasan_nand_base->intsts_enr);
	writel(reg_val | ARASAN_NAND_INT_STS_XFR_CMPLT_MASK,
	       &arasan_nand_base->intsts_enr);
	reg_val = readl(&arasan_nand_base->intsts_reg);
	writel(reg_val | ARASAN_NAND_INT_STS_XFR_CMPLT_MASK,
	       &arasan_nand_base->intsts_reg);

	return 0;
}

static int arasan_nand_send_rdcmd(struct arasan_nand_command_format *curr_cmd,
			       int column, int page_addr, struct mtd_info *mtd)
{
	u32 reg_val, addr_cycles, page;
	u8 page_val;

	reg_val = readl(&arasan_nand_base->intsts_enr);
	writel(reg_val | ARASAN_NAND_INT_STS_BUF_RD_RDY_MASK,
	       &arasan_nand_base->intsts_enr);

	reg_val = readl(&arasan_nand_base->cmd_reg);
	reg_val &= ~ARASAN_NAND_CMD_CMD12_MASK;
	reg_val |= curr_cmd->cmd1 |
		   (curr_cmd->cmd2 << ARASAN_NAND_CMD_CMD2_SHIFT);

	if (curr_cmd->cmd1 == NAND_CMD_RNDOUT ||
	    curr_cmd->cmd1 == NAND_CMD_READ0) {
		reg_val &= ~ARASAN_NAND_CMD_PG_SIZE_MASK;
		page_val = arasan_nand_page(mtd);
		reg_val |= (page_val << ARASAN_NAND_CMD_PG_SIZE_SHIFT);
	}

	reg_val &= ~ARASAN_NAND_CMD_ECC_ON_MASK;

	reg_val &= ~ARASAN_NAND_CMD_ADDR_CYCL_MASK;

	addr_cycles = arasan_nand_get_addrcycle(mtd);

	if (addr_cycles == ARASAN_NAND_INVALID_ADDR_CYCL)
		return ERR_ADDR_CYCLE;

	reg_val |= (addr_cycles << 28);
	writel(reg_val, &arasan_nand_base->cmd_reg);

	if (page_addr == -1)
		page_addr = 0;

	page = (page_addr << ARASAN_NAND_MEM_ADDR1_PAGE_SHIFT) &
		ARASAN_NAND_MEM_ADDR1_PAGE_MASK;
	column &= ARASAN_NAND_MEM_ADDR1_COL_MASK;
	writel(page | column, &arasan_nand_base->memadr_reg1);

	reg_val = readl(&arasan_nand_base->memadr_reg2);
	reg_val &= ~ARASAN_NAND_MEM_ADDR2_PAGE_MASK;
	reg_val |= (page_addr >> ARASAN_NAND_MEM_ADDR1_PAGE_SHIFT);
	writel(reg_val, &arasan_nand_base->memadr_reg2);

	buf_index = 0;

	return 0;
}

static void arasan_nand_read_buf(struct mtd_info *mtd, u8 *buf, int size)
{
	u32 reg_val, i;
	u32 *bufptr = (u32 *)buf;
	u32 timeout = ARASAN_NAND_POLL_TIMEOUT;

	reg_val = readl(&arasan_nand_base->pkt_reg);
	reg_val &= ~(ARASAN_NAND_PKT_REG_PKT_CNT_MASK |
		     ARASAN_NAND_PKT_REG_PKT_SIZE_MASK);
	reg_val |= (1 << ARASAN_NAND_PKT_REG_PKT_CNT_SHFT) | size;
	writel(reg_val, &arasan_nand_base->pkt_reg);

	writel(curr_cmd->pgm, &arasan_nand_base->pgm_reg);

	while (!(readl(&arasan_nand_base->intsts_reg) &
		ARASAN_NAND_INT_STS_BUF_RD_RDY_MASK) && timeout) {
		udelay(1);
		timeout--;
	}

	if (!timeout)
		puts("ERROR:arasan_nand_read_buf timedout:Buff RDY\n");

	reg_val = readl(&arasan_nand_base->intsts_enr);
	reg_val |= ARASAN_NAND_INT_STS_XFR_CMPLT_MASK;
	writel(reg_val, &arasan_nand_base->intsts_enr);

	writel(reg_val | ARASAN_NAND_INT_STS_BUF_RD_RDY_MASK,
	       &arasan_nand_base->intsts_enr);
	reg_val = readl(&arasan_nand_base->intsts_reg);
	writel(reg_val | ARASAN_NAND_INT_STS_BUF_RD_RDY_MASK,
	       &arasan_nand_base->intsts_reg);

	buf_index = 0;
	for (i = 0; i < size / 4; i++)
		bufptr[i] = readl(&arasan_nand_base->buf_dataport);

	if (size & 0x03)
		bufptr[i] = readl(&arasan_nand_base->buf_dataport);

	timeout = ARASAN_NAND_POLL_TIMEOUT;

	while (!(readl(&arasan_nand_base->intsts_reg) &
		ARASAN_NAND_INT_STS_XFR_CMPLT_MASK) && timeout) {
		udelay(1);
		timeout--;
	}

	if (!timeout)
		puts("ERROR:arasan_nand_read_buf timedout:Xfer CMPLT\n");

	reg_val = readl(&arasan_nand_base->intsts_enr);
	writel(reg_val | ARASAN_NAND_INT_STS_XFR_CMPLT_MASK,
	       &arasan_nand_base->intsts_enr);
	reg_val = readl(&arasan_nand_base->intsts_reg);
	writel(reg_val | ARASAN_NAND_INT_STS_XFR_CMPLT_MASK,
	       &arasan_nand_base->intsts_reg);
}

static u8 arasan_nand_read_byte(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd_to_nand(mtd);
	u32 size;
	u8 val;
	struct nand_onfi_params *p;

	if (buf_index == 0) {
		p = &chip->onfi_params;
		if (curr_cmd->cmd1 == NAND_CMD_READID)
			size = 4;
		else if (curr_cmd->cmd1 == NAND_CMD_PARAM)
			size = sizeof(struct nand_onfi_params);
		else if (curr_cmd->cmd1 == NAND_CMD_RNDOUT)
			size = le16_to_cpu(p->ext_param_page_length) * 16;
		else if (curr_cmd->cmd1 == NAND_CMD_GET_FEATURES)
			size = 4;
		else if (curr_cmd->cmd1 == NAND_CMD_STATUS)
			return readb(&arasan_nand_base->flash_sts_reg);
		else
			size = 8;
		chip->read_buf(mtd, &buf_data[0], size);
	}

	val = *(&buf_data[0] + buf_index);
	buf_index++;

	return val;
}

static void arasan_nand_cmd_function(struct mtd_info *mtd, unsigned int command,
				     int column, int page_addr)
{
	u32 i, ret = 0;
	struct nand_chip *chip = mtd_to_nand(mtd);
	struct arasan_nand_info *nand = nand_get_controller_data(chip);

	curr_cmd = NULL;
	writel(ARASAN_NAND_INT_STS_XFR_CMPLT_MASK,
	       &arasan_nand_base->intsts_enr);

	if ((command == NAND_CMD_READOOB) &&
	    (mtd->writesize > 512)) {
		column += mtd->writesize;
		command = NAND_CMD_READ0;
	}

	/* Get the command format */
	for (i = 0; (arasan_nand_commands[i].cmd1 != NAND_CMD_NONE ||
		     arasan_nand_commands[i].cmd2 != NAND_CMD_NONE); i++) {
		if (command == arasan_nand_commands[i].cmd1) {
			curr_cmd = &arasan_nand_commands[i];
			break;
		}
	}

	if (curr_cmd == NULL) {
		printf("Unsupported Command; 0x%x\n", command);
		return;
	}

	if (curr_cmd->cmd1 == NAND_CMD_RESET)
		ret = arasan_nand_reset(curr_cmd);

	if ((curr_cmd->cmd1 == NAND_CMD_READID) ||
	    (curr_cmd->cmd1 == NAND_CMD_PARAM) ||
	    (curr_cmd->cmd1 == NAND_CMD_RNDOUT) ||
	    (curr_cmd->cmd1 == NAND_CMD_GET_FEATURES) ||
	    (curr_cmd->cmd1 == NAND_CMD_READ0))
		ret = arasan_nand_send_rdcmd(curr_cmd, column, page_addr, mtd);

	if ((curr_cmd->cmd1 == NAND_CMD_SET_FEATURES) ||
	    (curr_cmd->cmd1 == NAND_CMD_SEQIN)) {
		nand->page = page_addr;
		ret = arasan_nand_send_wrcmd(curr_cmd, column, page_addr, mtd);
	}

	if (curr_cmd->cmd1 == NAND_CMD_ERASE1)
		ret = arasan_nand_erase(curr_cmd, column, page_addr, mtd);

	if (curr_cmd->cmd1 == NAND_CMD_STATUS)
		ret = arasan_nand_read_status(curr_cmd, column, page_addr, mtd);

	if (ret != 0)
		printf("ERROR:%s:command:0x%x\n", __func__, curr_cmd->cmd1);
}

static void arasan_check_ondie(struct mtd_info *mtd)
{
	struct nand_chip *nand_chip = mtd_to_nand(mtd);
	struct arasan_nand_info *nand = nand_get_controller_data(nand_chip);
	u8 maf_id, dev_id;
	u8 get_feature[4];
	u8 set_feature[4] = {ENABLE_ONDIE_ECC, 0x00, 0x00, 0x00};
	u32 i;

	/* Send the command for reading device ID */
	nand_chip->cmdfunc(mtd, NAND_CMD_RESET, -1, -1);
	nand_chip->cmdfunc(mtd, NAND_CMD_READID, 0, -1);

	/* Read manufacturer and device IDs */
	maf_id = nand_chip->read_byte(mtd);
	dev_id = nand_chip->read_byte(mtd);

	if ((maf_id == NAND_MFR_MICRON) &&
	    ((dev_id == 0xf1) || (dev_id == 0xa1) || (dev_id == 0xb1) ||
	     (dev_id == 0xaa) || (dev_id == 0xba) || (dev_id == 0xda) ||
	     (dev_id == 0xca) || (dev_id == 0xac) || (dev_id == 0xbc) ||
	     (dev_id == 0xdc) || (dev_id == 0xcc) || (dev_id == 0xa3) ||
	     (dev_id == 0xb3) || (dev_id == 0xd3) || (dev_id == 0xc3))) {
		nand_chip->cmdfunc(mtd, NAND_CMD_SET_FEATURES,
				   ONDIE_ECC_FEATURE_ADDR, -1);

		nand_chip->write_buf(mtd, &set_feature[0], 4);
		nand_chip->cmdfunc(mtd, NAND_CMD_GET_FEATURES,
				   ONDIE_ECC_FEATURE_ADDR, -1);

		for (i = 0; i < 4; i++)
			get_feature[i] = nand_chip->read_byte(mtd);

		if (get_feature[0] & ENABLE_ONDIE_ECC)
			nand->on_die_ecc_enabled = true;
		else
			printf("%s: Unable to enable OnDie ECC\n", __func__);

		/* Use the BBT pattern descriptors */
		nand_chip->bbt_td = &bbt_main_descr;
		nand_chip->bbt_md = &bbt_mirror_descr;
	}
}

static int arasan_nand_ecc_init(struct mtd_info *mtd)
{
	int found = -1;
	u32 regval, eccpos_start, i, eccaddr;
	struct nand_chip *nand_chip = mtd_to_nand(mtd);

	for (i = 0; i < ARRAY_SIZE(ecc_matrix); i++) {
		if ((ecc_matrix[i].pagesize == mtd->writesize) &&
		    (ecc_matrix[i].ecc_codeword_size >=
		     nand_chip->ecc_step_ds)) {
			if (ecc_matrix[i].eccbits >=
			    nand_chip->ecc_strength_ds) {
				found = i;
				break;
			}
			found = i;
		}
	}

	if (found < 0)
		return 1;

	eccaddr = mtd->writesize + mtd->oobsize -
		  ecc_matrix[found].eccsize;

	regval = eccaddr |
		 (ecc_matrix[found].eccsize << ARASAN_NAND_ECC_SIZE_SHIFT) |
		 (ecc_matrix[found].bch << ARASAN_NAND_ECC_BCH_SHIFT);
	writel(regval, &arasan_nand_base->ecc_reg);

	if (ecc_matrix[found].bch) {
		regval = readl(&arasan_nand_base->memadr_reg2);
		regval &= ~ARASAN_NAND_MEM_ADDR2_BCH_MASK;
		regval |= (ecc_matrix[found].bchval <<
			   ARASAN_NAND_MEM_ADDR2_BCH_SHIFT);
		writel(regval, &arasan_nand_base->memadr_reg2);
	}

	nand_oob.eccbytes = ecc_matrix[found].eccsize;
	eccpos_start = mtd->oobsize - nand_oob.eccbytes;

	for (i = 0; i < nand_oob.eccbytes; i++)
		nand_oob.eccpos[i] = eccpos_start + i;

	nand_oob.oobfree[0].offset = 2;
	nand_oob.oobfree[0].length = eccpos_start - 2;

	nand_chip->ecc.size = ecc_matrix[found].ecc_codeword_size;
	nand_chip->ecc.strength = ecc_matrix[found].eccbits;
	nand_chip->ecc.bytes = ecc_matrix[found].eccsize;
	nand_chip->ecc.layout = &nand_oob;

	return 0;
}

static int arasan_nand_init(struct nand_chip *nand_chip, int devnum)
{
	struct arasan_nand_info *nand;
	struct mtd_info *mtd;
	int err = -1;

	nand = calloc(1, sizeof(struct arasan_nand_info));
	if (!nand) {
		printf("%s: failed to allocate\n", __func__);
		return err;
	}

	nand->nand_base = arasan_nand_base;
	mtd = nand_to_mtd(nand_chip);
	nand_set_controller_data(nand_chip, nand);

#ifdef CONFIG_SYS_NAND_NO_SUBPAGE_WRITE
	nand_chip->options |= NAND_NO_SUBPAGE_WRITE;
#endif

	/* Set the driver entry points for MTD */
	nand_chip->cmdfunc = arasan_nand_cmd_function;
	nand_chip->select_chip = arasan_nand_select_chip;
	nand_chip->read_byte = arasan_nand_read_byte;

	/* Buffer read/write routines */
	nand_chip->read_buf = arasan_nand_read_buf;
	nand_chip->write_buf = arasan_nand_write_buf;
	nand_chip->bbt_options = NAND_BBT_USE_FLASH;

	writel(0x0, &arasan_nand_base->cmd_reg);
	writel(0x0, &arasan_nand_base->pgm_reg);

	/* first scan to find the device and get the page size */
	if (nand_scan_ident(mtd, CONFIG_SYS_NAND_MAX_CHIPS, NULL)) {
		printf("%s: nand_scan_ident failed\n", __func__);
		goto fail;
	}

	nand_chip->ecc.mode = NAND_ECC_HW;
	nand_chip->ecc.hwctl = NULL;
	nand_chip->ecc.read_page = arasan_nand_read_page_hwecc;
	nand_chip->ecc.write_page = arasan_nand_write_page_hwecc;
	nand_chip->ecc.read_oob = arasan_nand_read_oob;
	nand_chip->ecc.write_oob = arasan_nand_write_oob;

	arasan_check_ondie(mtd);

	/*
	 * If on die supported, then give priority to on-die ecc and use
	 * it instead of controller ecc.
	 */
	if (nand->on_die_ecc_enabled) {
		nand_chip->ecc.strength = 1;
		nand_chip->ecc.size = mtd->writesize;
		nand_chip->ecc.bytes = 0;
		nand_chip->ecc.layout = &ondie_nand_oob_64;
	} else {
		if (arasan_nand_ecc_init(mtd)) {
			printf("%s: nand_ecc_init failed\n", __func__);
			goto fail;
		}
	}

	if (nand_scan_tail(mtd)) {
		printf("%s: nand_scan_tail failed\n", __func__);
		goto fail;
	}

	if (nand_register(devnum, mtd)) {
		printf("Nand Register Fail\n");
		goto fail;
	}

	return 0;
fail:
	free(nand);
	return err;
}

void board_nand_init(void)
{
	struct nand_chip *nand = &nand_chip[0];

	if (arasan_nand_init(nand, 0))
		puts("NAND init failed\n");
}
