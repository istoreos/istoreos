/*
 * (C) Copyright 2009
 * Magnus Lilja <lilja.magnus@gmail.com>
 *
 * (C) Copyright 2008
 * Maxim Artamonov, <scn1874 at yandex.ru>
 *
 * (C) Copyright 2006-2008
 * Stefan Roese, DENX Software Engineering, sr at denx.de.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <nand.h>
#include <asm/arch/imx-regs.h>
#include <asm/io.h>
#include "mxc_nand.h"

#if defined(MXC_NFC_V1) || defined(MXC_NFC_V2_1)
static struct mxc_nand_regs *const nfc = (void *)NFC_BASE_ADDR;
#elif defined(MXC_NFC_V3_2)
static struct mxc_nand_regs *const nfc = (void *)NFC_BASE_ADDR_AXI;
static struct mxc_nand_ip_regs *const nfc_ip = (void *)NFC_BASE_ADDR;
#endif

static void nfc_wait_ready(void)
{
	uint32_t tmp;

#if defined(MXC_NFC_V1) || defined(MXC_NFC_V2_1)
	while (!(readnfc(&nfc->config2) & NFC_V1_V2_CONFIG2_INT))
		;

	/* Reset interrupt flag */
	tmp = readnfc(&nfc->config2);
	tmp &= ~NFC_V1_V2_CONFIG2_INT;
	writenfc(tmp, &nfc->config2);
#elif defined(MXC_NFC_V3_2)
	while (!(readnfc(&nfc_ip->ipc) & NFC_V3_IPC_INT))
		;

	/* Reset interrupt flag */
	tmp = readnfc(&nfc_ip->ipc);
	tmp &= ~NFC_V3_IPC_INT;
	writenfc(tmp, &nfc_ip->ipc);
#endif
}

static void nfc_nand_init(void)
{
#if defined(MXC_NFC_V3_2)
	int ecc_per_page = CONFIG_SYS_NAND_PAGE_SIZE / 512;
	int tmp;

	tmp = (readnfc(&nfc_ip->config2) & ~(NFC_V3_CONFIG2_SPAS_MASK |
			NFC_V3_CONFIG2_EDC_MASK | NFC_V3_CONFIG2_PS_MASK)) |
		NFC_V3_CONFIG2_SPAS(CONFIG_SYS_NAND_OOBSIZE / 2) |
		NFC_V3_CONFIG2_INT_MSK | NFC_V3_CONFIG2_ECC_EN |
		NFC_V3_CONFIG2_ONE_CYCLE;
	if (CONFIG_SYS_NAND_PAGE_SIZE == 4096)
		tmp |= NFC_V3_CONFIG2_PS_4096;
	else if (CONFIG_SYS_NAND_PAGE_SIZE == 2048)
		tmp |= NFC_V3_CONFIG2_PS_2048;
	else if (CONFIG_SYS_NAND_PAGE_SIZE == 512)
		tmp |= NFC_V3_CONFIG2_PS_512;
	/*
	 * if spare size is larger that 16 bytes per 512 byte hunk
	 * then use 8 symbol correction instead of 4
	 */
	if (CONFIG_SYS_NAND_OOBSIZE / ecc_per_page > 16)
		tmp |= NFC_V3_CONFIG2_ECC_MODE_8;
	else
		tmp &= ~NFC_V3_CONFIG2_ECC_MODE_8;
	writenfc(tmp, &nfc_ip->config2);

	tmp = NFC_V3_CONFIG3_NUM_OF_DEVS(0) |
			NFC_V3_CONFIG3_NO_SDMA |
			NFC_V3_CONFIG3_RBB_MODE |
			NFC_V3_CONFIG3_SBB(6) | /* Reset default */
			NFC_V3_CONFIG3_ADD_OP(0);
#ifndef CONFIG_SYS_NAND_BUSWIDTH_16
	tmp |= NFC_V3_CONFIG3_FW8;
#endif
	writenfc(tmp, &nfc_ip->config3);

	writenfc(0, &nfc_ip->delay_line);
#elif defined(MXC_NFC_V2_1)
	int ecc_per_page = CONFIG_SYS_NAND_PAGE_SIZE / 512;
	int config1;

	writenfc(CONFIG_SYS_NAND_OOBSIZE / 2, &nfc->spare_area_size);

	/* unlocking RAM Buff */
	writenfc(0x2, &nfc->config);

	/* hardware ECC checking and correct */
	config1 = readnfc(&nfc->config1) | NFC_V1_V2_CONFIG1_ECC_EN |
			NFC_V1_V2_CONFIG1_INT_MSK | NFC_V2_CONFIG1_ONE_CYCLE |
			NFC_V2_CONFIG1_FP_INT;
	/*
	 * if spare size is larger that 16 bytes per 512 byte hunk
	 * then use 8 symbol correction instead of 4
	 */
	if (CONFIG_SYS_NAND_OOBSIZE / ecc_per_page > 16)
		config1 &= ~NFC_V2_CONFIG1_ECC_MODE_4;
	else
		config1 |= NFC_V2_CONFIG1_ECC_MODE_4;
	writenfc(config1, &nfc->config1);
#elif defined(MXC_NFC_V1)
	/* unlocking RAM Buff */
	writenfc(0x2, &nfc->config);

	/* hardware ECC checking and correct */
	writenfc(NFC_V1_V2_CONFIG1_ECC_EN | NFC_V1_V2_CONFIG1_INT_MSK,
			&nfc->config1);
#endif
}

static void nfc_nand_command(unsigned short command)
{
	writenfc(command, &nfc->flash_cmd);
	writenfc(NFC_CMD, &nfc->operation);
	nfc_wait_ready();
}

static void nfc_nand_address(unsigned short address)
{
	writenfc(address, &nfc->flash_addr);
	writenfc(NFC_ADDR, &nfc->operation);
	nfc_wait_ready();
}

static void nfc_nand_page_address(unsigned int page_address)
{
	unsigned int page_count;

	nfc_nand_address(0x00);

	/* code only for large page flash */
	if (CONFIG_SYS_NAND_PAGE_SIZE > 512)
		nfc_nand_address(0x00);

	page_count = CONFIG_SYS_NAND_SIZE / CONFIG_SYS_NAND_PAGE_SIZE;

	if (page_address <= page_count) {
		page_count--; /* transform 0x01000000 to 0x00ffffff */
		do {
			nfc_nand_address(page_address & 0xff);
			page_address = page_address >> 8;
			page_count = page_count >> 8;
		} while (page_count);
	}

	nfc_nand_address(0x00);
}

static void nfc_nand_data_output(void)
{
#ifdef NAND_MXC_2K_MULTI_CYCLE
	int i;
#endif

#if defined(MXC_NFC_V1) || defined(MXC_NFC_V2_1)
	writenfc(0, &nfc->buf_addr);
#elif defined(MXC_NFC_V3_2)
	int config1 = readnfc(&nfc->config1);
	config1 &= ~NFC_V3_CONFIG1_RBA_MASK;
	writenfc(config1, &nfc->config1);
#endif
	writenfc(NFC_OUTPUT, &nfc->operation);
	nfc_wait_ready();
#ifdef NAND_MXC_2K_MULTI_CYCLE
	/*
	 * This NAND controller requires multiple input commands
	 * for pages larger than 512 bytes.
	 */
	for (i = 1; i < CONFIG_SYS_NAND_PAGE_SIZE / 512; i++) {
		writenfc(i, &nfc->buf_addr);
		writenfc(NFC_OUTPUT, &nfc->operation);
		nfc_wait_ready();
	}
#endif
}

static int nfc_nand_check_ecc(void)
{
#if defined(MXC_NFC_V1)
	u16 ecc_status = readw(&nfc->ecc_status_result);
	return (ecc_status & 0x3) == 2 || (ecc_status >> 2) == 2;
#elif defined(MXC_NFC_V2_1) || defined(MXC_NFC_V3_2)
	u32 ecc_status = readl(&nfc->ecc_status_result);
	int ecc_per_page = CONFIG_SYS_NAND_PAGE_SIZE / 512;
	int err_limit = CONFIG_SYS_NAND_OOBSIZE / ecc_per_page > 16 ? 8 : 4;
	int subpages = CONFIG_SYS_NAND_PAGE_SIZE / 512;

	do {
		if ((ecc_status & 0xf) > err_limit)
			return 1;
		ecc_status >>= 4;
	} while (--subpages);

	return 0;
#endif
}

static void nfc_nand_read_page(unsigned int page_address)
{
	/* read in first 0 buffer */
#if defined(MXC_NFC_V1) || defined(MXC_NFC_V2_1)
	writenfc(0, &nfc->buf_addr);
#elif defined(MXC_NFC_V3_2)
	int config1 = readnfc(&nfc->config1);
	config1 &= ~NFC_V3_CONFIG1_RBA_MASK;
	writenfc(config1, &nfc->config1);
#endif
	nfc_nand_command(NAND_CMD_READ0);
	nfc_nand_page_address(page_address);

	if (CONFIG_SYS_NAND_PAGE_SIZE > 512)
		nfc_nand_command(NAND_CMD_READSTART);

	nfc_nand_data_output(); /* fill the main buffer 0 */
}

static int nfc_read_page(unsigned int page_address, unsigned char *buf)
{
	int i;
	u32 *src;
	u32 *dst;

	nfc_nand_read_page(page_address);

	if (nfc_nand_check_ecc())
		return -EBADMSG;

	src = (u32 *)&nfc->main_area[0][0];
	dst = (u32 *)buf;

	/* main copy loop from NAND-buffer to SDRAM memory */
	for (i = 0; i < CONFIG_SYS_NAND_PAGE_SIZE / 4; i++) {
		writel(readl(src), dst);
		src++;
		dst++;
	}

	return 0;
}

static int is_badblock(int pagenumber)
{
	int page = pagenumber;
	u32 badblock;
	u32 *src;

	/* Check the first two pages for bad block markers */
	for (page = pagenumber; page < pagenumber + 2; page++) {
		nfc_nand_read_page(page);

		src = (u32 *)&nfc->spare_area[0][0];

		/*
		 * IMPORTANT NOTE: The nand flash controller uses a non-
		 * standard layout for large page devices. This can
		 * affect the position of the bad block marker.
		 */
		/* Get the bad block marker */
		badblock = readl(&src[CONFIG_SYS_NAND_BAD_BLOCK_POS / 4]);
		badblock >>= 8 * (CONFIG_SYS_NAND_BAD_BLOCK_POS % 4);
		badblock &= 0xff;

		/* bad block marker verify */
		if (badblock != 0xff)
			return 1; /* potential bad block */
	}

	return 0;
}

int nand_spl_load_image(uint32_t from, unsigned int size, void *buf)
{
	int i;
	unsigned int page;
	unsigned int maxpages = CONFIG_SYS_NAND_SIZE /
				CONFIG_SYS_NAND_PAGE_SIZE;

	nfc_nand_init();

	/* Convert to page number */
	page = from / CONFIG_SYS_NAND_PAGE_SIZE;
	i = 0;

	size = roundup(size, CONFIG_SYS_NAND_PAGE_SIZE);
	while (i < size / CONFIG_SYS_NAND_PAGE_SIZE) {
		if (nfc_read_page(page, buf) < 0)
			return -1;

		page++;
		i++;
		buf = buf + CONFIG_SYS_NAND_PAGE_SIZE;

		/*
		 * Check if we have crossed a block boundary, and if so
		 * check for bad block.
		 */
		if (!(page % CONFIG_SYS_NAND_PAGE_COUNT)) {
			/*
			 * Yes, new block. See if this block is good. If not,
			 * loop until we find a good block.
			 */
			while (is_badblock(page)) {
				page = page + CONFIG_SYS_NAND_PAGE_COUNT;
				/* Check i we've reached the end of flash. */
				if (page >= maxpages)
					return -1;
			}
		}
	}

	return 0;
}

#ifndef CONFIG_SPL_FRAMEWORK
/*
 * The main entry for NAND booting. It's necessary that SDRAM is already
 * configured and available since this code loads the main U-Boot image
 * from NAND into SDRAM and starts it from there.
 */
void nand_boot(void)
{
	__attribute__((noreturn)) void (*uboot)(void);

	/*
	 * CONFIG_SYS_NAND_U_BOOT_OFFS and CONFIG_SYS_NAND_U_BOOT_SIZE must
	 * be aligned to full pages
	 */
	if (!nand_spl_load_image(CONFIG_SYS_NAND_U_BOOT_OFFS,
			CONFIG_SYS_NAND_U_BOOT_SIZE,
			(uchar *)CONFIG_SYS_NAND_U_BOOT_DST)) {
		/* Copy from NAND successful, start U-Boot */
		uboot = (void *)CONFIG_SYS_NAND_U_BOOT_START;
		uboot();
	} else {
		/* Unrecoverable error when copying from NAND */
		hang();
	}
}
#endif

void nand_init(void) {}
void nand_deselect(void) {}
