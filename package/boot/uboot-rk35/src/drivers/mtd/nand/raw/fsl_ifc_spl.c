/*
 * NAND boot for Freescale Integrated Flash Controller, NAND FCM
 *
 * Copyright 2011 Freescale Semiconductor, Inc.
 * Author: Dipen Dudhat <dipen.dudhat@freescale.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <asm/io.h>
#include <fsl_ifc.h>
#include <linux/mtd/rawnand.h>
#ifdef CONFIG_CHAIN_OF_TRUST
#include <fsl_validate.h>
#endif

static inline int is_blank(uchar *addr, int page_size)
{
	int i;

	for (i = 0; i < page_size; i++) {
		if (__raw_readb(&addr[i]) != 0xff)
			return 0;
	}

	/*
	 * For the SPL, don't worry about uncorrectable errors
	 * where the main area is all FFs but shouldn't be.
	 */
	return 1;
}

/* returns nonzero if entire page is blank */
static inline int check_read_ecc(uchar *buf, u32 *eccstat,
				 unsigned int bufnum, int page_size)
{
	u32 reg = eccstat[bufnum / 4];
	int errors = (reg >> ((3 - bufnum % 4) * 8)) & 0xf;

	if (errors == 0xf) { /* uncorrectable */
		/* Blank pages fail hw ECC checks */
		if (is_blank(buf, page_size))
			return 1;

		puts("ecc error\n");
		for (;;)
			;
	}

	return 0;
}

static inline struct fsl_ifc_runtime *runtime_regs_address(void)
{
	struct fsl_ifc regs = {(void *)CONFIG_SYS_IFC_ADDR, NULL};
	int ver = 0;

	ver = ifc_in32(&regs.gregs->ifc_rev);
	if (ver >= FSL_IFC_V2_0_0)
		regs.rregs = (void *)CONFIG_SYS_IFC_ADDR + IFC_RREGS_64KOFFSET;
	else
		regs.rregs = (void *)CONFIG_SYS_IFC_ADDR + IFC_RREGS_4KOFFSET;

	return regs.rregs;
}

static inline void nand_wait(uchar *buf, int bufnum, int page_size)
{
	struct fsl_ifc_runtime *ifc = runtime_regs_address();
	u32 status;
	u32 eccstat[8];
	int bufperpage = page_size / 512;
	int bufnum_end, i;

	bufnum *= bufperpage;
	bufnum_end = bufnum + bufperpage - 1;

	do {
		status = ifc_in32(&ifc->ifc_nand.nand_evter_stat);
	} while (!(status & IFC_NAND_EVTER_STAT_OPC));

	if (status & IFC_NAND_EVTER_STAT_FTOER) {
		puts("flash time out error\n");
		for (;;)
			;
	}

	for (i = bufnum / 4; i <= bufnum_end / 4; i++)
		eccstat[i] = ifc_in32(&ifc->ifc_nand.nand_eccstat[i]);

	for (i = bufnum; i <= bufnum_end; i++) {
		if (check_read_ecc(buf, eccstat, i, page_size))
			break;
	}

	ifc_out32(&ifc->ifc_nand.nand_evter_stat, status);
}

static inline int bad_block(uchar *marker, int port_size)
{
	if (port_size == 8)
		return __raw_readb(marker) != 0xff;
	else
		return __raw_readw((u16 *)marker) != 0xffff;
}

int nand_spl_load_image(uint32_t offs, unsigned int uboot_size, void *vdst)
{
	struct fsl_ifc_fcm *gregs = (void *)CONFIG_SYS_IFC_ADDR;
	struct fsl_ifc_runtime *ifc = NULL;
	uchar *buf = (uchar *)CONFIG_SYS_NAND_BASE;
	int page_size;
	int port_size;
	int pages_per_blk;
	int blk_size;
	int bad_marker = 0;
	int bufnum_mask, bufnum, ver = 0;

	int csor, cspr;
	int pos = 0;
	int j = 0;

	int sram_addr;
	int pg_no;
	uchar *dst = vdst;

	ifc = runtime_regs_address();

	/* Get NAND Flash configuration */
	csor = CONFIG_SYS_NAND_CSOR;
	cspr = CONFIG_SYS_NAND_CSPR;

	port_size = (cspr & CSPR_PORT_SIZE_16) ? 16 : 8;

	if ((csor & CSOR_NAND_PGS_MASK) == CSOR_NAND_PGS_8K) {
		page_size = 8192;
		bufnum_mask = 0x0;
	} else if ((csor & CSOR_NAND_PGS_MASK) == CSOR_NAND_PGS_4K) {
		page_size = 4096;
		bufnum_mask = 0x1;
	} else if ((csor & CSOR_NAND_PGS_MASK) == CSOR_NAND_PGS_2K) {
		page_size = 2048;
		bufnum_mask = 0x3;
	} else {
		page_size = 512;
		bufnum_mask = 0xf;

		if (port_size == 8)
			bad_marker = 5;
	}

	ver = ifc_in32(&gregs->ifc_rev);
	if (ver >= FSL_IFC_V2_0_0)
		bufnum_mask = (bufnum_mask * 2) + 1;

	pages_per_blk =
		32 << ((csor & CSOR_NAND_PB_MASK) >> CSOR_NAND_PB_SHIFT);

	blk_size = pages_per_blk * page_size;

	/* Open Full SRAM mapping for spare are access */
	ifc_out32(&ifc->ifc_nand.ncfgr, 0x0);

	/* Clear Boot events */
	ifc_out32(&ifc->ifc_nand.nand_evter_stat, 0xffffffff);

	/* Program FIR/FCR for Large/Small page */
	if (page_size > 512) {
		ifc_out32(&ifc->ifc_nand.nand_fir0,
			  (IFC_FIR_OP_CW0 << IFC_NAND_FIR0_OP0_SHIFT) |
			  (IFC_FIR_OP_CA0 << IFC_NAND_FIR0_OP1_SHIFT) |
			  (IFC_FIR_OP_RA0 << IFC_NAND_FIR0_OP2_SHIFT) |
			  (IFC_FIR_OP_CMD1 << IFC_NAND_FIR0_OP3_SHIFT) |
			  (IFC_FIR_OP_BTRD << IFC_NAND_FIR0_OP4_SHIFT));
		ifc_out32(&ifc->ifc_nand.nand_fir1, 0x0);

		ifc_out32(&ifc->ifc_nand.nand_fcr0,
			  (NAND_CMD_READ0 << IFC_NAND_FCR0_CMD0_SHIFT) |
			  (NAND_CMD_READSTART << IFC_NAND_FCR0_CMD1_SHIFT));
	} else {
		ifc_out32(&ifc->ifc_nand.nand_fir0,
			  (IFC_FIR_OP_CW0 << IFC_NAND_FIR0_OP0_SHIFT) |
			  (IFC_FIR_OP_CA0 << IFC_NAND_FIR0_OP1_SHIFT) |
			  (IFC_FIR_OP_RA0  << IFC_NAND_FIR0_OP2_SHIFT) |
			  (IFC_FIR_OP_BTRD << IFC_NAND_FIR0_OP3_SHIFT));
		ifc_out32(&ifc->ifc_nand.nand_fir1, 0x0);

		ifc_out32(&ifc->ifc_nand.nand_fcr0,
			  NAND_CMD_READ0 << IFC_NAND_FCR0_CMD0_SHIFT);
	}

	/* Program FBCR = 0 for full page read */
	ifc_out32(&ifc->ifc_nand.nand_fbcr, 0);

	/* Read and copy u-boot on SDRAM from NAND device, In parallel
	 * check for Bad block if found skip it and read continue to
	 * next Block
	 */
	while (pos < uboot_size) {
		int i = 0;
		do {
			pg_no = offs / page_size;
			bufnum = pg_no & bufnum_mask;
			sram_addr = bufnum * page_size * 2;

			ifc_out32(&ifc->ifc_nand.row0, pg_no);
			ifc_out32(&ifc->ifc_nand.col0, 0);
			/* start read */
			ifc_out32(&ifc->ifc_nand.nandseq_strt,
				  IFC_NAND_SEQ_STRT_FIR_STRT);

			/* wait for read to complete */
			nand_wait(&buf[sram_addr], bufnum, page_size);

			/*
			 * If either of the first two pages are marked bad,
			 * continue to the next block.
			 */
			if (i++ < 2 &&
			    bad_block(&buf[sram_addr + page_size + bad_marker],
				      port_size)) {
				puts("skipping\n");
				offs = (offs + blk_size) & ~(blk_size - 1);
				pos &= ~(blk_size - 1);
				break;
			}

			for (j = 0; j < page_size; j++)
				dst[pos + j] = __raw_readb(&buf[sram_addr + j]);

			pos += page_size;
			offs += page_size;
		} while ((offs & (blk_size - 1)) && (pos < uboot_size));
	}

	return 0;
}

/*
 * Main entrypoint for NAND Boot. It's necessary that SDRAM is already
 * configured and available since this code loads the main U-Boot image
 * from NAND into SDRAM and starts from there.
 */
void nand_boot(void)
{
	__attribute__((noreturn)) void (*uboot)(void);
	/*
	 * Load U-Boot image from NAND into RAM
	 */
	nand_spl_load_image(CONFIG_SYS_NAND_U_BOOT_OFFS,
			    CONFIG_SYS_NAND_U_BOOT_SIZE,
			    (uchar *)CONFIG_SYS_NAND_U_BOOT_DST);

#ifdef CONFIG_NAND_ENV_DST
	nand_spl_load_image(CONFIG_ENV_OFFSET, CONFIG_ENV_SIZE,
			    (uchar *)CONFIG_NAND_ENV_DST);

#ifdef CONFIG_ENV_OFFSET_REDUND
	nand_spl_load_image(CONFIG_ENV_OFFSET_REDUND, CONFIG_ENV_SIZE,
			    (uchar *)CONFIG_NAND_ENV_DST + CONFIG_ENV_SIZE);
#endif
#endif
	/*
	 * Jump to U-Boot image
	 */
#ifdef CONFIG_SPL_FLUSH_IMAGE
	/*
	 * Clean d-cache and invalidate i-cache, to
	 * make sure that no stale data is executed.
	 */
	flush_cache(CONFIG_SYS_NAND_U_BOOT_DST, CONFIG_SYS_NAND_U_BOOT_SIZE);
#endif

#ifdef CONFIG_CHAIN_OF_TRUST
	/*
	 * U-Boot header is appended at end of U-boot image, so
	 * calculate U-boot header address using U-boot header size.
	 */
#define CONFIG_U_BOOT_HDR_ADDR \
		((CONFIG_SYS_NAND_U_BOOT_START + \
		  CONFIG_SYS_NAND_U_BOOT_SIZE) - \
		 CONFIG_U_BOOT_HDR_SIZE)
	spl_validate_uboot(CONFIG_U_BOOT_HDR_ADDR,
			   CONFIG_SYS_NAND_U_BOOT_START);
	/*
	 * In case of failure in validation, spl_validate_uboot would
	 * not return back in case of Production environment with ITS=1.
	 * Thus U-Boot will not start.
	 * In Development environment (ITS=0 and SB_EN=1), the function
	 * may return back in case of non-fatal failures.
	 */
#endif

	uboot = (void *)CONFIG_SYS_NAND_U_BOOT_START;
	uboot();
}

#ifndef CONFIG_SPL_NAND_INIT
void nand_init(void)
{
}

void nand_deselect(void)
{
}
#endif
