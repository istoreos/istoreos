/*
 * Renesas RCar Gen3 RPC Hyperflash driver
 *
 * Copyright (C) 2016 Renesas Electronics Corporation
 * Copyright (C) 2016 Cogent Embedded, Inc.
 * Copyright (C) 2017 Marek Vasut <marek.vasut@gmail.com>
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#include <common.h>
#include <asm/io.h>
#include <clk.h>
#include <dm.h>
#include <dm/of_access.h>
#include <errno.h>
#include <fdt_support.h>
#include <flash.h>
#include <mtd.h>
#include <wait_bit.h>
#include <mtd/cfi_flash.h>

#define RPC_CMNCR		0x0000	/* R/W */
#define RPC_CMNCR_MD		BIT(31)
#define RPC_CMNCR_MOIIO0(val)	(((val) & 0x3) << 16)
#define RPC_CMNCR_MOIIO1(val)	(((val) & 0x3) << 18)
#define RPC_CMNCR_MOIIO2(val)	(((val) & 0x3) << 20)
#define RPC_CMNCR_MOIIO3(val)	(((val) & 0x3) << 22)
#define RPC_CMNCR_MOIIO_HIZ	(RPC_CMNCR_MOIIO0(3) | RPC_CMNCR_MOIIO1(3) | \
				 RPC_CMNCR_MOIIO2(3) | RPC_CMNCR_MOIIO3(3))
#define RPC_CMNCR_IO0FV(val)	(((val) & 0x3) << 8)
#define RPC_CMNCR_IO2FV(val)	(((val) & 0x3) << 12)
#define RPC_CMNCR_IO3FV(val)	(((val) & 0x3) << 14)
#define RPC_CMNCR_IOFV_HIZ	(RPC_CMNCR_IO0FV(3) | RPC_CMNCR_IO2FV(3) | \
				 RPC_CMNCR_IO3FV(3))
#define RPC_CMNCR_BSZ(val)	(((val) & 0x3) << 0)

#define RPC_SSLDR		0x0004	/* R/W */
#define RPC_SSLDR_SPNDL(d)	(((d) & 0x7) << 16)
#define RPC_SSLDR_SLNDL(d)	(((d) & 0x7) << 8)
#define RPC_SSLDR_SCKDL(d)	(((d) & 0x7) << 0)

#define RPC_DRCR		0x000C	/* R/W */
#define RPC_DRCR_SSLN		BIT(24)
#define RPC_DRCR_RBURST(v)	(((v) & 0x1F) << 16)
#define RPC_DRCR_RCF		BIT(9)
#define RPC_DRCR_RBE		BIT(8)
#define RPC_DRCR_SSLE		BIT(0)

#define RPC_DRCMR		0x0010	/* R/W */
#define RPC_DRCMR_CMD(c)	(((c) & 0xFF) << 16)
#define RPC_DRCMR_OCMD(c)	(((c) & 0xFF) << 0)

#define RPC_DREAR		0x0014	/* R/W */
#define RPC_DREAR_EAV(v)	(((v) & 0xFF) << 16)
#define RPC_DREAR_EAC(v)	(((v) & 0x7) << 0)

#define RPC_DROPR		0x0018	/* R/W */
#define RPC_DROPR_OPD3(o)	(((o) & 0xFF) << 24)
#define RPC_DROPR_OPD2(o)	(((o) & 0xFF) << 16)
#define RPC_DROPR_OPD1(o)	(((o) & 0xFF) << 8)
#define RPC_DROPR_OPD0(o)	(((o) & 0xFF) << 0)

#define RPC_DRENR		0x001C	/* R/W */
#define RPC_DRENR_CDB(o)	(u32)((((o) & 0x3) << 30))
#define RPC_DRENR_OCDB(o)	(((o) & 0x3) << 28)
#define RPC_DRENR_ADB(o)	(((o) & 0x3) << 24)
#define RPC_DRENR_OPDB(o)	(((o) & 0x3) << 20)
#define RPC_DRENR_SPIDB(o)	(((o) & 0x3) << 16)
#define RPC_DRENR_DME		BIT(15)
#define RPC_DRENR_CDE		BIT(14)
#define RPC_DRENR_OCDE		BIT(12)
#define RPC_DRENR_ADE(v)	(((v) & 0xF) << 8)
#define RPC_DRENR_OPDE(v)	(((v) & 0xF) << 4)

#define RPC_SMCR		0x0020	/* R/W */
#define RPC_SMCR_SSLKP		BIT(8)
#define RPC_SMCR_SPIRE		BIT(2)
#define RPC_SMCR_SPIWE		BIT(1)
#define RPC_SMCR_SPIE		BIT(0)

#define RPC_SMCMR		0x0024	/* R/W */
#define RPC_SMCMR_CMD(c)	(((c) & 0xFF) << 16)
#define RPC_SMCMR_OCMD(c)	(((c) & 0xFF) << 0)

#define RPC_SMADR		0x0028	/* R/W */
#define RPC_SMOPR		0x002C	/* R/W */
#define RPC_SMOPR_OPD0(o)	(((o) & 0xFF) << 0)
#define RPC_SMOPR_OPD1(o)	(((o) & 0xFF) << 8)
#define RPC_SMOPR_OPD2(o)	(((o) & 0xFF) << 16)
#define RPC_SMOPR_OPD3(o)	(((o) & 0xFF) << 24)

#define RPC_SMENR		0x0030	/* R/W */
#define RPC_SMENR_CDB(o)	(((o) & 0x3) << 30)
#define RPC_SMENR_OCDB(o)	(((o) & 0x3) << 28)
#define RPC_SMENR_ADB(o)	(((o) & 0x3) << 24)
#define RPC_SMENR_OPDB(o)	(((o) & 0x3) << 20)
#define RPC_SMENR_SPIDB(o)	(((o) & 0x3) << 16)
#define RPC_SMENR_DME		BIT(15)
#define RPC_SMENR_CDE		BIT(14)
#define RPC_SMENR_OCDE		BIT(12)
#define RPC_SMENR_ADE(v)	(((v) & 0xF) << 8)
#define RPC_SMENR_OPDE(v)	(((v) & 0xF) << 4)
#define RPC_SMENR_SPIDE(v)	(((v) & 0xF) << 0)

#define RPC_SMRDR0		0x0038	/* R */
#define RPC_SMRDR1		0x003C	/* R */
#define RPC_SMWDR0		0x0040	/* R/W */
#define RPC_SMWDR1		0x0044	/* R/W */
#define RPC_CMNSR		0x0048	/* R */
#define RPC_CMNSR_SSLF		BIT(1)
#define	RPC_CMNSR_TEND		BIT(0)

#define RPC_DRDMCR		0x0058	/* R/W */
#define RPC_DRDMCR_DMCYC(v)	(((v) & 0xF) << 0)

#define RPC_DRDRENR		0x005C	/* R/W */
#define RPC_DRDRENR_HYPE	(0x5 << 12)
#define RPC_DRDRENR_ADDRE	BIT(8)
#define RPC_DRDRENR_OPDRE	BIT(4)
#define RPC_DRDRENR_DRDRE	BIT(0)

#define RPC_SMDMCR		0x0060	/* R/W */
#define RPC_SMDMCR_DMCYC(v)	(((v) & 0xF) << 0)

#define RPC_SMDRENR		0x0064	/* R/W */
#define RPC_SMDRENR_HYPE	(0x5 << 12)
#define RPC_SMDRENR_ADDRE	BIT(8)
#define RPC_SMDRENR_OPDRE	BIT(4)
#define RPC_SMDRENR_SPIDRE	BIT(0)

#define RPC_PHYCNT		0x007C	/* R/W */
#define RPC_PHYCNT_CAL		BIT(31)
#define PRC_PHYCNT_OCTA_AA	BIT(22)
#define PRC_PHYCNT_OCTA_SA	BIT(23)
#define PRC_PHYCNT_EXDS		BIT(21)
#define RPC_PHYCNT_OCT		BIT(20)
#define RPC_PHYCNT_WBUF2	BIT(4)
#define RPC_PHYCNT_WBUF		BIT(2)
#define RPC_PHYCNT_MEM(v)	(((v) & 0x3) << 0)

#define RPC_PHYINT		0x0088	/* R/W */
#define RPC_PHYINT_RSTEN	BIT(18)
#define RPC_PHYINT_WPEN		BIT(17)
#define RPC_PHYINT_INTEN	BIT(16)
#define RPC_PHYINT_RST		BIT(2)
#define RPC_PHYINT_WP		BIT(1)
#define RPC_PHYINT_INT		BIT(0)

#define RPC_WBUF		0x8000	/* R/W size=4/8/16/32/64Bytes */
#define RPC_WBUF_SIZE		0x100

static phys_addr_t rpc_base;

enum rpc_hf_size {
	RPC_HF_SIZE_16BIT = RPC_SMENR_SPIDE(0x8),
	RPC_HF_SIZE_32BIT = RPC_SMENR_SPIDE(0xC),
	RPC_HF_SIZE_64BIT = RPC_SMENR_SPIDE(0xF),
};

static int rpc_hf_wait_tend(void)
{
	void __iomem *reg = (void __iomem *)rpc_base + RPC_CMNSR;
	return wait_for_bit_le32(reg, RPC_CMNSR_TEND, true, 1000, 0);
}

static int rpc_hf_mode(bool man)
{
	int ret;

	ret = rpc_hf_wait_tend();
	if (ret)
		return ret;

	clrsetbits_le32(rpc_base + RPC_PHYCNT,
		 RPC_PHYCNT_WBUF | RPC_PHYCNT_WBUF2 |
		 RPC_PHYCNT_CAL | RPC_PHYCNT_MEM(3),
		 RPC_PHYCNT_CAL | RPC_PHYCNT_MEM(3));

	clrsetbits_le32(rpc_base + RPC_CMNCR,
		 RPC_CMNCR_MD | RPC_CMNCR_BSZ(3),
		 RPC_CMNCR_MOIIO_HIZ | RPC_CMNCR_IOFV_HIZ |
		 (man ? RPC_CMNCR_MD : 0) | RPC_CMNCR_BSZ(1));

	if (man)
		return 0;

	writel(RPC_DRCR_RBURST(0x1F) | RPC_DRCR_RCF | RPC_DRCR_RBE,
	       rpc_base + RPC_DRCR);

	writel(RPC_DRCMR_CMD(0xA0), rpc_base + RPC_DRCMR);
	writel(RPC_DRENR_CDB(2) | RPC_DRENR_OCDB(2) | RPC_DRENR_ADB(2) |
	       RPC_DRENR_SPIDB(2) | RPC_DRENR_CDE | RPC_DRENR_OCDE |
	       RPC_DRENR_ADE(4), rpc_base + RPC_DRENR);
	writel(RPC_DRDMCR_DMCYC(0xE), rpc_base + RPC_DRDMCR);
	writel(RPC_DRDRENR_HYPE | RPC_DRDRENR_ADDRE | RPC_DRDRENR_DRDRE,
	       rpc_base + RPC_DRDRENR);

	/* Dummy read */
	readl(rpc_base + RPC_DRCR);

	return 0;
}

static int rpc_hf_xfer(void *addr, u64 wdata, u64 *rdata,
		       enum rpc_hf_size size, bool write)
{
	int ret;
	u32 val;

	ret = rpc_hf_mode(1);
	if (ret)
		return ret;

	/* Submit HF address, SMCMR CMD[7] ~= CA Bit# 47 (R/nW) */
	writel(write ? 0 : RPC_SMCMR_CMD(0x80), rpc_base + RPC_SMCMR);
	writel((uintptr_t)addr >> 1, rpc_base + RPC_SMADR);
	writel(0x0, rpc_base + RPC_SMOPR);

	writel(RPC_SMDRENR_HYPE | RPC_SMDRENR_ADDRE | RPC_SMDRENR_SPIDRE,
	       rpc_base + RPC_SMDRENR);

	val = RPC_SMENR_CDB(2) | RPC_SMENR_OCDB(2) |
	      RPC_SMENR_ADB(2) | RPC_SMENR_SPIDB(2) |
	      RPC_SMENR_CDE | RPC_SMENR_OCDE | RPC_SMENR_ADE(4) | size;

	if (write) {
		writel(val, rpc_base + RPC_SMENR);

		if (size == RPC_HF_SIZE_64BIT)
			writeq(cpu_to_be64(wdata), rpc_base + RPC_SMWDR0);
		else
			writel(cpu_to_be32(wdata), rpc_base + RPC_SMWDR0);

		writel(RPC_SMCR_SPIWE | RPC_SMCR_SPIE, rpc_base + RPC_SMCR);
	} else {
		val |= RPC_SMENR_DME;

		writel(RPC_SMDMCR_DMCYC(0xE), rpc_base + RPC_SMDMCR);

		writel(val, rpc_base + RPC_SMENR);

		writel(RPC_SMCR_SPIRE | RPC_SMCR_SPIE, rpc_base + RPC_SMCR);

		ret = rpc_hf_wait_tend();
		if (ret)
			return ret;

		if (size == RPC_HF_SIZE_64BIT)
			*rdata = be64_to_cpu(readq(rpc_base + RPC_SMRDR0));
		else
			*rdata = be32_to_cpu(readl(rpc_base + RPC_SMRDR0));
	}

	return rpc_hf_mode(0);
}

static void rpc_hf_write_cmd(void *addr, u64 wdata, enum rpc_hf_size size)
{
	int ret;

	ret = rpc_hf_xfer(addr, wdata, NULL, size, 1);
	if (ret)
		printf("RPC: Write failed, ret=%i\n", ret);
}

static u64 rpc_hf_read_reg(void *addr, enum rpc_hf_size size)
{
	u64 rdata = 0;
	int ret;

	ret = rpc_hf_xfer(addr, 0, &rdata, size, 0);
	if (ret)
		printf("RPC: Read failed, ret=%i\n", ret);

	return rdata;
}

void flash_write8(u8 value, void *addr)
{
	rpc_hf_write_cmd(addr, value, RPC_HF_SIZE_16BIT);
}

void flash_write16(u16 value, void *addr)
{
	rpc_hf_write_cmd(addr, value, RPC_HF_SIZE_16BIT);
}

void flash_write32(u32 value, void *addr)
{
	rpc_hf_write_cmd(addr, value, RPC_HF_SIZE_32BIT);
}

void flash_write64(u64 value, void *addr)
{
	rpc_hf_write_cmd(addr, value, RPC_HF_SIZE_64BIT);
}

u8 flash_read8(void *addr)
{
	return rpc_hf_read_reg(addr, RPC_HF_SIZE_16BIT);
}

u16 flash_read16(void *addr)
{
	return rpc_hf_read_reg(addr, RPC_HF_SIZE_16BIT);
}

u32 flash_read32(void *addr)
{
	return rpc_hf_read_reg(addr, RPC_HF_SIZE_32BIT);
}

u64 flash_read64(void *addr)
{
	return rpc_hf_read_reg(addr, RPC_HF_SIZE_64BIT);
}

static int rpc_hf_bind(struct udevice *parent)
{
	const void *fdt = gd->fdt_blob;
	ofnode node;
	int ret, off;

	/*
	 * Check if there are any SPI NOR child nodes, if so, do NOT bind
	 * as this controller will be operated by the QSPI driver instead.
	 */
	dev_for_each_subnode(node, parent) {
		off = ofnode_to_offset(node);

		ret = fdt_node_check_compatible(fdt, off, "spi-flash");
		if (!ret)
			return -ENODEV;

		ret = fdt_node_check_compatible(fdt, off, "jedec,spi-nor");
		if (!ret)
			return -ENODEV;
	}

	return 0;
}

static int rpc_hf_probe(struct udevice *dev)
{
	void *blob = (void *)gd->fdt_blob;
	const fdt32_t *cell;
	int node = dev_of_offset(dev);
	int parent, addrc, sizec, len, ret;
	struct clk clk;
	phys_addr_t flash_base;

	parent = fdt_parent_offset(blob, node);
	fdt_support_default_count_cells(blob, parent, &addrc, &sizec);
	cell = fdt_getprop(blob, node, "reg", &len);
	if (!cell)
		return -ENOENT;

	if (addrc != 2 || sizec != 2)
		return -EINVAL;


	ret = clk_get_by_index(dev, 0, &clk);
	if (ret < 0) {
		dev_err(dev, "Failed to get RPC clock\n");
		return ret;
	}

	ret = clk_enable(&clk);
	clk_free(&clk);
	if (ret) {
		dev_err(dev, "Failed to enable RPC clock\n");
		return ret;
	}

	rpc_base = fdt_translate_address(blob, node, cell);
	flash_base = fdt_translate_address(blob, node, cell + addrc + sizec);

	flash_info[0].dev = dev;
	flash_info[0].base = flash_base;
	cfi_flash_num_flash_banks = 1;
	gd->bd->bi_flashstart = flash_base;

	return 0;
}

static const struct udevice_id rpc_hf_ids[] = {
	{ .compatible = "renesas,rpc" },
	{}
};

U_BOOT_DRIVER(rpc_hf) = {
	.name		= "rpc_hf",
	.id		= UCLASS_MTD,
	.of_match	= rpc_hf_ids,
	.bind		= rpc_hf_bind,
	.probe		= rpc_hf_probe,
};
