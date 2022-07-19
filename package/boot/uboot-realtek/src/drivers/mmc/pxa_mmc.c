/*
 * (C) Copyright 2003
 * Kyle Harris, Nexus Technologies, Inc. kharris@nexus-tech.net
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <config.h>
#include <common.h>
#include <mmc.h>
#include <asm/errno.h>
#include <asm/arch/hardware.h>
#include <part.h>
#include <asm/io.h>

#include "pxa_mmc.h"

extern int fat_register_device(block_dev_desc_t * dev_desc, int part_no);

static block_dev_desc_t mmc_dev;

block_dev_desc_t *mmc_get_dev(int dev)
{
	return ((block_dev_desc_t *) & mmc_dev);
}

/*
 * FIXME needs to read cid and csd info to determine block size
 * and other parameters
 */
static uchar mmc_buf[MMC_BLOCK_SIZE];
static uchar spec_ver;
static int mmc_ready = 0;
static int wide = 0;

static uint32_t *
/****************************************************/
mmc_cmd(ushort cmd, ushort argh, ushort argl, ushort cmdat)
/****************************************************/
{
	static uint32_t resp[4], a, b, c;
	uint32_t status;
	int i;

	debug("mmc_cmd %u 0x%04x 0x%04x 0x%04x\n", cmd, argh, argl,
	      cmdat | wide);
	writel(MMC_STRPCL_STOP_CLK, MMC_STRPCL);
	writel(~MMC_I_MASK_CLK_IS_OFF, MMC_I_MASK);
	while (!(readl(MMC_I_REG) & MMC_I_REG_CLK_IS_OFF))
		;
	writel(cmd, MMC_CMD);
	writel(argh, MMC_ARGH);
	writel(argl, MMC_ARGL);
	writel(cmdat | wide, MMC_CMDAT);
	writel(~MMC_I_MASK_END_CMD_RES, MMC_I_MASK);
	writel(MMC_STRPCL_START_CLK, MMC_STRPCL);
	while (!(readl(MMC_I_REG) & MMC_I_REG_END_CMD_RES))
		;

	status = readl(MMC_STAT);
	debug("MMC status 0x%08x\n", status);
	if (status & MMC_STAT_TIME_OUT_RESPONSE) {
		return 0;
	}

	/* Linux says:
	 * Did I mention this is Sick.  We always need to
	 * discard the upper 8 bits of the first 16-bit word.
	 */
	a = (readl(MMC_RES) & 0xffff);
	for (i = 0; i < 4; i++) {
		b = (readl(MMC_RES) & 0xffff);
		c = (readl(MMC_RES) & 0xffff);
		resp[i] = (a << 24) | (b << 8) | (c >> 8);
		a = c;
		debug("MMC resp[%d] = %#08x\n", i, resp[i]);
	}

	return resp;
}

int
/****************************************************/
mmc_block_read(uchar * dst, uint32_t src, int len)
/****************************************************/
{
	ushort argh, argl;
	ulong status;

	if (len == 0) {
		return 0;
	}

	debug("mmc_block_rd dst %p src %08x len %d\n", dst, src, len);

	argh = len >> 16;
	argl = len & 0xffff;

	/* set block len */
	mmc_cmd(MMC_CMD_SET_BLOCKLEN, argh, argl, MMC_CMDAT_R1);

	/* send read command */
	argh = src >> 16;
	argl = src & 0xffff;
	writel(MMC_STRPCL_STOP_CLK, MMC_STRPCL);
	writel(0xffff, MMC_RDTO);
	writel(1, MMC_NOB);
	writel(len, MMC_BLKLEN);
	mmc_cmd(MMC_CMD_READ_SINGLE_BLOCK, argh, argl,
		MMC_CMDAT_R1 | MMC_CMDAT_READ | MMC_CMDAT_BLOCK |
		MMC_CMDAT_DATA_EN);

	writel(~MMC_I_MASK_RXFIFO_RD_REQ, MMC_I_MASK);
	while (len) {
		if (readl(MMC_I_REG) & MMC_I_REG_RXFIFO_RD_REQ) {
#if defined(CONFIG_CPU_PXA27X) || defined(CONFIG_CPU_MONAHANS)
			int i;
			for (i = min(len, 32); i; i--) {
				*dst++ = readb(MMC_RXFIFO);
				len--;
			}
#else
			*dst++ = readb(MMC_RXFIFO);
			len--;
#endif
		}
		status = readl(MMC_STAT);
		if (status & MMC_STAT_ERRORS) {
			printf("MMC_STAT error %lx\n", status);
			return -1;
		}
	}
	writel(~MMC_I_MASK_DATA_TRAN_DONE, MMC_I_MASK);
	while (!(readl(MMC_I_REG) & MMC_I_REG_DATA_TRAN_DONE))
		;
	status = readl(MMC_STAT);
	if (status & MMC_STAT_ERRORS) {
		printf("MMC_STAT error %lx\n", status);
		return -1;
	}
	return 0;
}

int
/****************************************************/
mmc_block_write(ulong dst, uchar * src, int len)
/****************************************************/
{
	ushort argh, argl;
	ulong status;

	if (len == 0) {
		return 0;
	}

	debug("mmc_block_wr dst %lx src %lx len %d\n", dst, (ulong) src, len);

	argh = len >> 16;
	argl = len & 0xffff;

	/* set block len */
	mmc_cmd(MMC_CMD_SET_BLOCKLEN, argh, argl, MMC_CMDAT_R1);

	/* send write command */
	argh = dst >> 16;
	argl = dst & 0xffff;
	writel(MMC_STRPCL_STOP_CLK, MMC_STRPCL);
	writel(1, MMC_NOB);
	writel(len, MMC_BLKLEN);
	mmc_cmd(MMC_CMD_WRITE_SINGLE_BLOCK, argh, argl,
		MMC_CMDAT_R1 | MMC_CMDAT_WRITE | MMC_CMDAT_BLOCK |
		MMC_CMDAT_DATA_EN);

	writel(~MMC_I_MASK_TXFIFO_WR_REQ, MMC_I_MASK);
	while (len) {
		if (readl(MMC_I_REG) & MMC_I_REG_TXFIFO_WR_REQ) {
			int i, bytes = min(32, len);

			for (i = 0; i < bytes; i++) {
				writel(*src++, MMC_TXFIFO);
			}
			if (bytes < 32) {
				writel(MMC_PRTBUF_BUF_PART_FULL, MMC_PRTBUF);
			}
			len -= bytes;
		}
		status = readl(MMC_STAT);
		if (status & MMC_STAT_ERRORS) {
			printf("MMC_STAT error %lx\n", status);
			return -1;
		}
	}
	writel(~MMC_I_MASK_DATA_TRAN_DONE, MMC_I_MASK);
	while (!(readl(MMC_I_REG) & MMC_I_REG_DATA_TRAN_DONE))
		;
	writel(~MMC_I_MASK_PRG_DONE, MMC_I_MASK);
	while (!(readl(MMC_I_REG) & MMC_I_REG_PRG_DONE))
		;
	status = readl(MMC_STAT);
	if (status & MMC_STAT_ERRORS) {
		printf("MMC_STAT error %lx\n", status);
		return -1;
	}
	return 0;
}

int
/****************************************************/
pxa_mmc_read(long src, uchar * dst, int size)
/****************************************************/
{
	ulong end, part_start, part_end, part_len, aligned_start, aligned_end;
	ulong mmc_block_size, mmc_block_address;

	if (size == 0) {
		return 0;
	}

	if (!mmc_ready) {
		printf("Please initial the MMC first\n");
		return -1;
	}

	mmc_block_size = MMC_BLOCK_SIZE;
	mmc_block_address = ~(mmc_block_size - 1);

	src -= CONFIG_SYS_MMC_BASE;
	end = src + size;
	part_start = ~mmc_block_address & src;
	part_end = ~mmc_block_address & end;
	aligned_start = mmc_block_address & src;
	aligned_end = mmc_block_address & end;

	/* all block aligned accesses */
	debug
	    ("src %lx dst %lx end %lx pstart %lx pend %lx astart %lx aend %lx\n",
	     src, (ulong) dst, end, part_start, part_end, aligned_start,
	     aligned_end);
	if (part_start) {
		part_len = mmc_block_size - part_start;
		debug
		    ("ps src %lx dst %lx end %lx pstart %lx pend %lx astart %lx aend %lx\n",
		     src, (ulong) dst, end, part_start, part_end, aligned_start,
		     aligned_end);
		if ((mmc_block_read(mmc_buf, aligned_start, mmc_block_size)) <
		    0) {
			return -1;
		}
		memcpy(dst, mmc_buf + part_start, part_len);
		dst += part_len;
		src += part_len;
	}
	debug
	    ("src %lx dst %lx end %lx pstart %lx pend %lx astart %lx aend %lx\n",
	     src, (ulong) dst, end, part_start, part_end, aligned_start,
	     aligned_end);
	for (; src < aligned_end; src += mmc_block_size, dst += mmc_block_size) {
		debug
		    ("al src %lx dst %lx end %lx pstart %lx pend %lx astart %lx aend %lx\n",
		     src, (ulong) dst, end, part_start, part_end, aligned_start,
		     aligned_end);
		if ((mmc_block_read((uchar *) (dst), src, mmc_block_size)) < 0) {
			return -1;
		}
	}
	debug
	    ("src %lx dst %lx end %lx pstart %lx pend %lx astart %lx aend %lx\n",
	     src, (ulong) dst, end, part_start, part_end, aligned_start,
	     aligned_end);
	if (part_end && src < end) {
		debug
		    ("pe src %lx dst %lx end %lx pstart %lx pend %lx astart %lx aend %lx\n",
		     src, (ulong) dst, end, part_start, part_end, aligned_start,
		     aligned_end);
		if ((mmc_block_read(mmc_buf, aligned_end, mmc_block_size)) < 0) {
			return -1;
		}
		memcpy(dst, mmc_buf, part_end);
	}
	return 0;
}

int
/****************************************************/
pxa_mmc_write(uchar * src, uint32_t dst, int size)
/****************************************************/
{
	ulong end, part_start, part_end, part_len, aligned_start, aligned_end;
	ulong mmc_block_size, mmc_block_address;

	if (size == 0) {
		return 0;
	}

	if (!mmc_ready) {
		printf("Please initial the MMC first\n");
		return -1;
	}

	mmc_block_size = MMC_BLOCK_SIZE;
	mmc_block_address = ~(mmc_block_size - 1);

	dst -= CONFIG_SYS_MMC_BASE;
	end = dst + size;
	part_start = ~mmc_block_address & dst;
	part_end = ~mmc_block_address & end;
	aligned_start = mmc_block_address & dst;
	aligned_end = mmc_block_address & end;

	/* all block aligned accesses */
	debug
	    ("src %p dst %08x end %lx pstart %lx pend %lx astart %lx aend %lx\n",
	     src, dst, end, part_start, part_end, aligned_start,
	     aligned_end);
	if (part_start) {
		part_len = mmc_block_size - part_start;
		debug
		    ("ps src %p dst %08x end %lx pstart %lx pend %lx astart %lx aend %lx\n",
		     src, dst, end, part_start, part_end, aligned_start,
		     aligned_end);
		if ((mmc_block_read(mmc_buf, aligned_start, mmc_block_size)) <
		    0) {
			return -1;
		}
		memcpy(mmc_buf + part_start, src, part_len);
		if ((mmc_block_write(aligned_start, mmc_buf, mmc_block_size)) <
		    0) {
			return -1;
		}
		dst += part_len;
		src += part_len;
	}
	debug
	    ("src %p dst %08x end %lx pstart %lx pend %lx astart %lx aend %lx\n",
	     src, dst, end, part_start, part_end, aligned_start,
	     aligned_end);
	for (; dst < aligned_end; src += mmc_block_size, dst += mmc_block_size) {
		debug
		    ("al src %p dst %08x end %lx pstart %lx pend %lx astart %lx aend %lx\n",
		     src, dst, end, part_start, part_end, aligned_start,
		     aligned_end);
		if ((mmc_block_write(dst, (uchar *) src, mmc_block_size)) < 0) {
			return -1;
		}
	}
	debug
	    ("src %p dst %08x end %lx pstart %lx pend %lx astart %lx aend %lx\n",
	     src, dst, end, part_start, part_end, aligned_start,
	     aligned_end);
	if (part_end && dst < end) {
		debug
		    ("pe src %p dst %08x end %lx pstart %lx pend %lx astart %lx aend %lx\n",
		     src, dst, end, part_start, part_end, aligned_start,
		     aligned_end);
		if ((mmc_block_read(mmc_buf, aligned_end, mmc_block_size)) < 0) {
			return -1;
		}
		memcpy(mmc_buf, src, part_end);
		if ((mmc_block_write(aligned_end, mmc_buf, mmc_block_size)) < 0) {
			return -1;
		}
	}
	return 0;
}

static ulong
/****************************************************/
mmc_bread(int dev_num, ulong blknr, lbaint_t blkcnt, void *dst)
/****************************************************/
{
	int mmc_block_size = MMC_BLOCK_SIZE;
	ulong src = blknr * mmc_block_size + CONFIG_SYS_MMC_BASE;

	pxa_mmc_read(src, (uchar *) dst, blkcnt * mmc_block_size);
	return blkcnt;
}

#ifdef __GNUC__
#define likely(x)       __builtin_expect(!!(x), 1)
#define unlikely(x)     __builtin_expect(!!(x), 0)
#else
#define likely(x)	(x)
#define unlikely(x)	(x)
#endif

#define UNSTUFF_BITS(resp,start,size)					\
	({								\
		const int __size = size;				\
		const uint32_t __mask = (__size < 32 ? 1 << __size : 0) - 1;	\
		const int32_t __off = 3 - ((start) / 32);			\
		const int32_t __shft = (start) & 31;			\
		uint32_t __res;						\
									\
		__res = resp[__off] >> __shft;				\
		if (__size + __shft > 32)				\
			__res |= resp[__off-1] << ((32 - __shft) % 32);	\
		__res & __mask;						\
	})

/*
 * Given the decoded CSD structure, decode the raw CID to our CID structure.
 */
static void mmc_decode_cid(uint32_t * resp)
{
	if (IF_TYPE_SD == mmc_dev.if_type) {
		/*
		 * SD doesn't currently have a version field so we will
		 * have to assume we can parse this.
		 */
		sprintf((char *)mmc_dev.vendor,
			"Man %02x OEM %c%c \"%c%c%c%c%c\" Date %02u/%04u",
			UNSTUFF_BITS(resp, 120, 8), UNSTUFF_BITS(resp, 112, 8),
			UNSTUFF_BITS(resp, 104, 8), UNSTUFF_BITS(resp, 96, 8),
			UNSTUFF_BITS(resp, 88, 8), UNSTUFF_BITS(resp, 80, 8),
			UNSTUFF_BITS(resp, 72, 8), UNSTUFF_BITS(resp, 64, 8),
			UNSTUFF_BITS(resp, 8, 4), UNSTUFF_BITS(resp, 12,
							       8) + 2000);
		sprintf((char *)mmc_dev.revision, "%d.%d",
			UNSTUFF_BITS(resp, 60, 4), UNSTUFF_BITS(resp, 56, 4));
		sprintf((char *)mmc_dev.product, "%u",
			UNSTUFF_BITS(resp, 24, 32));
	} else {
		/*
		 * The selection of the format here is based upon published
		 * specs from sandisk and from what people have reported.
		 */
		switch (spec_ver) {
		case 0:	/* MMC v1.0 - v1.2 */
		case 1:	/* MMC v1.4 */
			sprintf((char *)mmc_dev.vendor,
				"Man %02x%02x%02x \"%c%c%c%c%c%c%c\" Date %02u/%04u",
				UNSTUFF_BITS(resp, 120, 8), UNSTUFF_BITS(resp,
									 112,
									 8),
				UNSTUFF_BITS(resp, 104, 8), UNSTUFF_BITS(resp,
									 96, 8),
				UNSTUFF_BITS(resp, 88, 8), UNSTUFF_BITS(resp,
									80, 8),
				UNSTUFF_BITS(resp, 72, 8), UNSTUFF_BITS(resp,
									64, 8),
				UNSTUFF_BITS(resp, 56, 8), UNSTUFF_BITS(resp,
									48, 8),
				UNSTUFF_BITS(resp, 12, 4), UNSTUFF_BITS(resp, 8,
									4) +
				1997);
			sprintf((char *)mmc_dev.revision, "%d.%d",
				UNSTUFF_BITS(resp, 44, 4), UNSTUFF_BITS(resp,
									40, 4));
			sprintf((char *)mmc_dev.product, "%u",
				UNSTUFF_BITS(resp, 16, 24));
			break;

		case 2:	/* MMC v2.0 - v2.2 */
		case 3:	/* MMC v3.1 - v3.3 */
		case 4:	/* MMC v4 */
			sprintf((char *)mmc_dev.vendor,
				"Man %02x OEM %04x \"%c%c%c%c%c%c\" Date %02u/%04u",
				UNSTUFF_BITS(resp, 120, 8), UNSTUFF_BITS(resp,
									 104,
									 16),
				UNSTUFF_BITS(resp, 96, 8), UNSTUFF_BITS(resp,
									88, 8),
				UNSTUFF_BITS(resp, 80, 8), UNSTUFF_BITS(resp,
									72, 8),
				UNSTUFF_BITS(resp, 64, 8), UNSTUFF_BITS(resp,
									56, 8),
				UNSTUFF_BITS(resp, 12, 4), UNSTUFF_BITS(resp, 8,
									4) +
				1997);
			sprintf((char *)mmc_dev.product, "%u",
				UNSTUFF_BITS(resp, 16, 32));
			sprintf((char *)mmc_dev.revision, "N/A");
			break;

		default:
			printf("MMC card has unknown MMCA version %d\n",
			       spec_ver);
			break;
		}
	}
	printf("%s card.\nVendor: %s\nProduct: %s\nRevision: %s\n",
	       (IF_TYPE_SD == mmc_dev.if_type) ? "SD" : "MMC", mmc_dev.vendor,
	       mmc_dev.product, mmc_dev.revision);
}

/*
 * Given a 128-bit response, decode to our card CSD structure.
 */
static void mmc_decode_csd(uint32_t * resp)
{
	unsigned int mult, csd_struct;

	if (IF_TYPE_SD == mmc_dev.if_type) {
		csd_struct = UNSTUFF_BITS(resp, 126, 2);
		if (csd_struct != 0) {
			printf("SD: unrecognised CSD structure version %d\n",
			       csd_struct);
			return;
		}
	} else {
		/*
		 * We only understand CSD structure v1.1 and v1.2.
		 * v1.2 has extra information in bits 15, 11 and 10.
		 */
		csd_struct = UNSTUFF_BITS(resp, 126, 2);
		if (csd_struct != 1 && csd_struct != 2) {
			printf("MMC: unrecognised CSD structure version %d\n",
			       csd_struct);
			return;
		}

		spec_ver = UNSTUFF_BITS(resp, 122, 4);
		mmc_dev.if_type = IF_TYPE_MMC;
	}

	mult = 1 << (UNSTUFF_BITS(resp, 47, 3) + 2);
	mmc_dev.lba = (1 + UNSTUFF_BITS(resp, 62, 12)) * mult;
	mmc_dev.blksz = 1 << UNSTUFF_BITS(resp, 80, 4);

	/* FIXME: The following just makes assumes that's the partition type -- should really read it */
	mmc_dev.part_type = PART_TYPE_DOS;
	mmc_dev.dev = 0;
	mmc_dev.lun = 0;
	mmc_dev.type = DEV_TYPE_HARDDISK;
	mmc_dev.removable = 0;
	mmc_dev.block_read = mmc_bread;

	printf("Detected: %lu blocks of %lu bytes (%luMB) ",
		mmc_dev.lba,
		mmc_dev.blksz,
		mmc_dev.lba * mmc_dev.blksz / (1024 * 1024));
}

int
/****************************************************/
mmc_legacy_init(int verbose)
/****************************************************/
{
	int retries, rc = -ENODEV;
	uint32_t cid_resp[4];
	uint32_t *resp;
	uint16_t rca = 0;

	/* Reset device interface type */
	mmc_dev.if_type = IF_TYPE_UNKNOWN;

#ifdef CONFIG_CPU_MONAHANS	/* pxa3xx */
	writel(readl(CKENA) | CKENA_12_MMC0 | CKENA_13_MMC1, CKENA);
#else	/* pxa2xx */
	writel(readl(CKEN) | CKEN12_MMC, CKEN);	/* enable MMC unit clock */
#endif
	writel(MMC_CLKRT_0_3125MHZ, MMC_CLKRT);
	writel(MMC_RES_TO_MAX, MMC_RESTO);
	writel(MMC_SPI_DISABLE, MMC_SPI);

	/* reset */
	mmc_cmd(MMC_CMD_GO_IDLE_STATE, 0, 0, MMC_CMDAT_INIT | MMC_CMDAT_R0);
	udelay(200000);
	retries = 3;
	while (retries--) {
		resp = mmc_cmd(MMC_CMD_APP_CMD, 0, 0, MMC_CMDAT_R1);
		if (!(resp[0] & 0x00000020)) {	/* Card does not support APP_CMD */
			debug("Card does not support APP_CMD\n");
			break;
		}

		/* Select 3.2-3.3V and 3.3-3.4V */
		resp = mmc_cmd(SD_CMD_APP_SEND_OP_COND, 0x0030, 0x0000,
				MMC_CMDAT_R3 | (retries < 2 ? 0
					: MMC_CMDAT_INIT));
		if (resp[0] & 0x80000000) {
			mmc_dev.if_type = IF_TYPE_SD;
			debug("Detected SD card\n");
			break;
		}
		udelay(200000);
	}

	if (retries <= 0 || !(IF_TYPE_SD == mmc_dev.if_type)) {
		debug("Failed to detect SD Card, trying MMC\n");
		resp =
		    mmc_cmd(MMC_CMD_SEND_OP_COND, 0x00ff, 0x8000, MMC_CMDAT_R3);

		retries = 10;
		while (retries-- && resp && !(resp[0] & 0x80000000)) {
			udelay(200000);
			resp =
			    mmc_cmd(MMC_CMD_SEND_OP_COND, 0x00ff, 0x8000,
				    MMC_CMDAT_R3);
		}
	}

	/* try to get card id */
	resp =
	    mmc_cmd(MMC_CMD_ALL_SEND_CID, 0, 0, MMC_CMDAT_R2 | MMC_CMDAT_BUSY);
	if (resp) {
		memcpy(cid_resp, resp, sizeof(cid_resp));

		/* MMC exists, get CSD too */
		resp = mmc_cmd(MMC_CMD_SET_RELATIVE_ADDR, 0, 0, MMC_CMDAT_R1);
		if (IF_TYPE_SD == mmc_dev.if_type)
			rca = ((resp[0] & 0xffff0000) >> 16);
		resp = mmc_cmd(MMC_CMD_SEND_CSD, rca, 0, MMC_CMDAT_R2);
		if (resp) {
			mmc_decode_csd(resp);
			rc = 0;
			mmc_ready = 1;
		}

		mmc_decode_cid(cid_resp);
	}

	writel(0, MMC_CLKRT);		/* 20 MHz */
	resp = mmc_cmd(MMC_CMD_SELECT_CARD, rca, 0, MMC_CMDAT_R1);

#if defined(CONFIG_CPU_PXA27X) || defined(CONFIG_CPU_MONAHANS)
	if (IF_TYPE_SD == mmc_dev.if_type) {
		resp = mmc_cmd(MMC_CMD_APP_CMD, rca, 0, MMC_CMDAT_R1);
		resp = mmc_cmd(SD_CMD_APP_SET_BUS_WIDTH, 0, 2, MMC_CMDAT_R1);
		wide = MMC_CMDAT_SD_4DAT;
	}
#endif

	fat_register_device(&mmc_dev, 1);	/* partitions start counting with 1 */

	return rc;
}
