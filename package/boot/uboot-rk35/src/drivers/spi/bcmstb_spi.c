// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2018  Cisco Systems, Inc.
 *
 * Author: Thomas Fitzsimmons <fitzsim@fitzsim.org>
 */

#include <asm/io.h>
#include <command.h>
#include <config.h>
#include <dm.h>
#include <errno.h>
#include <fdtdec.h>
#include <linux/bitops.h>
#include <linux/delay.h>
#include <log.h>
#include <malloc.h>
#include <spi.h>
#include <time.h>

DECLARE_GLOBAL_DATA_PTR;

#define SPBR_MIN		8
#define BITS_PER_WORD		8

#define NUM_TXRAM		32
#define NUM_RXRAM		32
#define NUM_CDRAM		16

/* hif_mspi register structure. */
struct bcmstb_hif_mspi_regs {
	u32 spcr0_lsb;		/* 0x000 */
	u32 spcr0_msb;		/* 0x004 */
	u32 spcr1_lsb;		/* 0x008 */
	u32 spcr1_msb;		/* 0x00c */
	u32 newqp;		/* 0x010 */
	u32 endqp;		/* 0x014 */
	u32 spcr2;		/* 0x018 */
	u32 reserved0;		/* 0x01c */
	u32 mspi_status;	/* 0x020 */
	u32 cptqp;		/* 0x024 */
	u32 spcr3;		/* 0x028 */
	u32 revision;		/* 0x02c */
	u32 reserved1[4];	/* 0x030 */
	u32 txram[NUM_TXRAM];	/* 0x040 */
	u32 rxram[NUM_RXRAM];	/* 0x0c0 */
	u32 cdram[NUM_CDRAM];	/* 0x140 */
	u32 write_lock;		/* 0x180 */
};

/* hif_mspi masks. */
#define HIF_MSPI_SPCR2_CONT_AFTER_CMD_MASK	0x00000080
#define HIF_MSPI_SPCR2_SPE_MASK			0x00000040
#define HIF_MSPI_SPCR2_SPIFIE_MASK		0x00000020
#define HIF_MSPI_WRITE_LOCK_WRITE_LOCK_MASK	0x00000001

/* bspi offsets. */
#define BSPI_MAST_N_BOOT_CTRL			0x008

/* bspi_raf is not used in this driver. */

/* hif_spi_intr2 offsets and masks. */
#define HIF_SPI_INTR2_CPU_CLEAR			0x08
#define HIF_SPI_INTR2_CPU_MASK_SET		0x10
#define HIF_SPI_INTR2_CPU_MASK_CLEAR		0x14
#define HIF_SPI_INTR2_CPU_SET_MSPI_DONE_MASK	0x00000020

/* SPI transfer timeout in milliseconds. */
#define HIF_MSPI_WAIT				10

enum bcmstb_base_type {
	HIF_MSPI,
	BSPI,
	HIF_SPI_INTR2,
	CS_REG,
	BASE_LAST,
};

struct bcmstb_spi_platdata {
	void *base[4];
};

struct bcmstb_spi_priv {
	struct bcmstb_hif_mspi_regs *regs;
	void *bspi;
	void *hif_spi_intr2;
	void *cs_reg;
	int default_cs;
	int curr_cs;
	uint tx_slot;
	uint rx_slot;
	u8 saved_cmd[NUM_CDRAM];
	uint saved_cmd_len;
	void *saved_din_addr;
};

static int bcmstb_spi_ofdata_to_platdata(struct udevice *bus)
{
	struct bcmstb_spi_platdata *plat = dev_get_platdata(bus);
	const void *fdt = gd->fdt_blob;
	int node = dev_of_offset(bus);
	int ret = 0;
	int i = 0;
	struct fdt_resource resource = { 0 };
	char *names[BASE_LAST] = { "hif_mspi", "bspi", "hif_spi_intr2",
				   "cs_reg" };
	const phys_addr_t defaults[BASE_LAST] = { BCMSTB_HIF_MSPI_BASE,
						  BCMSTB_BSPI_BASE,
						  BCMSTB_HIF_SPI_INTR2,
						  BCMSTB_CS_REG };

	for (i = 0; i < BASE_LAST; i++) {
		plat->base[i] = (void *)defaults[i];

		ret = fdt_get_named_resource(fdt, node, "reg", "reg-names",
					     names[i], &resource);
		if (ret) {
			printf("%s: Assuming BCMSTB SPI %s address 0x0x%p\n",
			       __func__, names[i], (void *)defaults[i]);
		} else {
			plat->base[i] = (void *)resource.start;
			debug("BCMSTB SPI %s address: 0x0x%p\n",
			      names[i], (void *)plat->base[i]);
		}
	}

	return 0;
}

static void bcmstb_spi_hw_set_parms(struct bcmstb_spi_priv *priv)
{
	writel(SPBR_MIN, &priv->regs->spcr0_lsb);
	writel(BITS_PER_WORD << 2 | SPI_MODE_3, &priv->regs->spcr0_msb);
}

static void bcmstb_spi_enable_interrupt(void *base, u32 mask)
{
	void *reg = base + HIF_SPI_INTR2_CPU_MASK_CLEAR;

	writel(readl(reg) | mask, reg);
	readl(reg);
}

static void bcmstb_spi_disable_interrupt(void *base, u32 mask)
{
	void *reg = base + HIF_SPI_INTR2_CPU_MASK_SET;

	writel(readl(reg) | mask, reg);
	readl(reg);
}

static void bcmstb_spi_clear_interrupt(void *base, u32 mask)
{
	void *reg = base + HIF_SPI_INTR2_CPU_CLEAR;

	writel(readl(reg) | mask, reg);
	readl(reg);
}

static int bcmstb_spi_probe(struct udevice *bus)
{
	struct bcmstb_spi_platdata *plat = dev_get_platdata(bus);
	struct bcmstb_spi_priv *priv = dev_get_priv(bus);

	priv->regs = plat->base[HIF_MSPI];
	priv->bspi = plat->base[BSPI];
	priv->hif_spi_intr2 = plat->base[HIF_SPI_INTR2];
	priv->cs_reg = plat->base[CS_REG];
	priv->default_cs = 0;
	priv->curr_cs = -1;
	priv->tx_slot = 0;
	priv->rx_slot = 0;
	memset(priv->saved_cmd, 0, NUM_CDRAM);
	priv->saved_cmd_len = 0;
	priv->saved_din_addr = NULL;

	debug("spi_xfer: tx regs: 0x%p\n", &priv->regs->txram[0]);
	debug("spi_xfer: rx regs: 0x%p\n", &priv->regs->rxram[0]);

	/* Disable BSPI. */
	writel(1, priv->bspi + BSPI_MAST_N_BOOT_CTRL);
	readl(priv->bspi + BSPI_MAST_N_BOOT_CTRL);

	/* Set up interrupts. */
	bcmstb_spi_disable_interrupt(priv->hif_spi_intr2, 0xffffffff);
	bcmstb_spi_clear_interrupt(priv->hif_spi_intr2, 0xffffffff);
	bcmstb_spi_enable_interrupt(priv->hif_spi_intr2,
				    HIF_SPI_INTR2_CPU_SET_MSPI_DONE_MASK);

	/* Set up control registers. */
	writel(0, &priv->regs->spcr1_lsb);
	writel(0, &priv->regs->spcr1_msb);
	writel(0, &priv->regs->newqp);
	writel(0, &priv->regs->endqp);
	writel(HIF_MSPI_SPCR2_SPIFIE_MASK, &priv->regs->spcr2);
	writel(0, &priv->regs->spcr3);

	bcmstb_spi_hw_set_parms(priv);

	return 0;
}

static void bcmstb_spi_submit(struct bcmstb_spi_priv *priv, bool done)
{
	debug("WR NEWQP: %d\n", 0);
	writel(0, &priv->regs->newqp);

	debug("WR ENDQP: %d\n", priv->tx_slot - 1);
	writel(priv->tx_slot - 1, &priv->regs->endqp);

	if (done) {
		debug("WR CDRAM[%d]: %02x\n", priv->tx_slot - 1,
		      readl(&priv->regs->cdram[priv->tx_slot - 1]) & ~0x80);
		writel(readl(&priv->regs->cdram[priv->tx_slot - 1]) & ~0x80,
		       &priv->regs->cdram[priv->tx_slot - 1]);
	}

	/* Force chip select first time. */
	if (priv->curr_cs != priv->default_cs) {
		debug("spi_xfer: switching chip select to %d\n",
		      priv->default_cs);
		writel((readl(priv->cs_reg) & ~0xff) | (1 << priv->default_cs),
		       priv->cs_reg);
		readl(priv->cs_reg);
		udelay(10);
		priv->curr_cs = priv->default_cs;
	}

	debug("WR WRITE_LOCK: %02x\n", 1);
	writel((readl(&priv->regs->write_lock) &
		~HIF_MSPI_WRITE_LOCK_WRITE_LOCK_MASK) | 1,
	       &priv->regs->write_lock);
	readl(&priv->regs->write_lock);

	debug("WR SPCR2: %02x\n",
	      HIF_MSPI_SPCR2_SPIFIE_MASK |
	      HIF_MSPI_SPCR2_SPE_MASK |
	      HIF_MSPI_SPCR2_CONT_AFTER_CMD_MASK);
	writel(HIF_MSPI_SPCR2_SPIFIE_MASK |
	       HIF_MSPI_SPCR2_SPE_MASK |
	       HIF_MSPI_SPCR2_CONT_AFTER_CMD_MASK,
	       &priv->regs->spcr2);
}

static int bcmstb_spi_wait(struct bcmstb_spi_priv *priv)
{
	u32 start_time = get_timer(0);
	u32 status = readl(&priv->regs->mspi_status);

	while (!(status & 1)) {
		if (get_timer(start_time) > HIF_MSPI_WAIT)
			return -ETIMEDOUT;
		status = readl(&priv->regs->mspi_status);
	}

	writel(readl(&priv->regs->mspi_status) & ~1, &priv->regs->mspi_status);
	bcmstb_spi_clear_interrupt(priv->hif_spi_intr2,
				   HIF_SPI_INTR2_CPU_SET_MSPI_DONE_MASK);

	return 0;
}

static int bcmstb_spi_xfer(struct udevice *dev, unsigned int bitlen,
			   const void *dout, void *din, unsigned long flags)
{
	uint len = bitlen / 8;
	uint tx_len = len;
	uint rx_len = len;
	const u8 *out_bytes = (u8 *)dout;
	u8 *in_bytes = (u8 *)din;
	struct udevice *bus = dev_get_parent(dev);
	struct bcmstb_spi_priv *priv = dev_get_priv(bus);
	struct bcmstb_hif_mspi_regs *regs = priv->regs;

	debug("spi_xfer: %d, t: 0x%p, r: 0x%p, f: %lx\n",
	      len, dout, din, flags);
	debug("spi_xfer: chip select: %x\n", readl(priv->cs_reg) & 0xff);
	debug("spi_xfer: tx addr: 0x%p\n", &regs->txram[0]);
	debug("spi_xfer: rx addr: 0x%p\n", &regs->rxram[0]);
	debug("spi_xfer: cd addr: 0x%p\n", &regs->cdram[0]);

	if (flags & SPI_XFER_END) {
		debug("spi_xfer: clearing saved din address: 0x%p\n",
		      priv->saved_din_addr);
		priv->saved_din_addr = NULL;
		priv->saved_cmd_len = 0;
		memset(priv->saved_cmd, 0, NUM_CDRAM);
	}

	if (bitlen == 0)
		return 0;

	if (bitlen % 8) {
		printf("%s: Non-byte-aligned transfer\n", __func__);
		return -EOPNOTSUPP;
	}

	if (flags & ~(SPI_XFER_BEGIN | SPI_XFER_END)) {
		printf("%s: Unsupported flags: %lx\n", __func__, flags);
		return -EOPNOTSUPP;
	}

	if (flags & SPI_XFER_BEGIN) {
		priv->tx_slot = 0;
		priv->rx_slot = 0;

		if (out_bytes && len > NUM_CDRAM) {
			printf("%s: Unable to save transfer\n", __func__);
			return -EOPNOTSUPP;
		}

		if (out_bytes && !(flags & SPI_XFER_END)) {
			/*
			 * This is the start of a transmit operation
			 * that will need repeating if the calling
			 * code polls for the result.  Save it for
			 * subsequent transmission.
			 */
			debug("spi_xfer: saving command: %x, %d\n",
			      out_bytes[0], len);
			priv->saved_cmd_len = len;
			memcpy(priv->saved_cmd, out_bytes, priv->saved_cmd_len);
		}
	}

	if (!(flags & (SPI_XFER_BEGIN | SPI_XFER_END))) {
		if (priv->saved_din_addr == din) {
			/*
			 * The caller is polling for status.  Repeat
			 * the last transmission.
			 */
			int ret = 0;

			debug("spi_xfer: Making recursive call\n");
			ret = bcmstb_spi_xfer(dev, priv->saved_cmd_len * 8,
					      priv->saved_cmd, NULL,
					      SPI_XFER_BEGIN);
			if (ret) {
				printf("%s: Recursive call failed\n", __func__);
				return ret;
			}
		} else {
			debug("spi_xfer: saving din address: 0x%p\n", din);
			priv->saved_din_addr = din;
		}
	}

	while (rx_len > 0) {
		priv->rx_slot = priv->tx_slot;

		while (priv->tx_slot < NUM_CDRAM && tx_len > 0) {
			bcmstb_spi_hw_set_parms(priv);
			debug("WR TXRAM[%d]: %02x\n", priv->tx_slot,
			      out_bytes ? out_bytes[len - tx_len] : 0xff);
			writel(out_bytes ? out_bytes[len - tx_len] : 0xff,
			       &regs->txram[priv->tx_slot << 1]);
			debug("WR CDRAM[%d]: %02x\n", priv->tx_slot, 0x8e);
			writel(0x8e, &regs->cdram[priv->tx_slot]);
			priv->tx_slot++;
			tx_len--;
			if (!in_bytes)
				rx_len--;
		}

		debug("spi_xfer: early return clauses: %d, %d, %d\n",
		      len <= NUM_CDRAM,
		      !in_bytes,
		      (flags & (SPI_XFER_BEGIN |
				SPI_XFER_END)) == SPI_XFER_BEGIN);
		if (len <= NUM_CDRAM &&
		    !in_bytes &&
		    (flags & (SPI_XFER_BEGIN | SPI_XFER_END)) == SPI_XFER_BEGIN)
			return 0;

		bcmstb_spi_submit(priv, tx_len == 0);

		if (bcmstb_spi_wait(priv) == -ETIMEDOUT) {
			printf("%s: Timed out\n", __func__);
			return -ETIMEDOUT;
		}

		priv->tx_slot %= NUM_CDRAM;

		if (in_bytes) {
			while (priv->rx_slot < NUM_CDRAM && rx_len > 0) {
				in_bytes[len - rx_len] =
					readl(&regs->rxram[(priv->rx_slot << 1)
							   + 1])
					& 0xff;
				debug("RD RXRAM[%d]: %02x\n",
				      priv->rx_slot, in_bytes[len - rx_len]);
				priv->rx_slot++;
				rx_len--;
			}
		}
	}

	if (flags & SPI_XFER_END) {
		debug("WR WRITE_LOCK: %02x\n", 0);
		writel((readl(&priv->regs->write_lock) &
			~HIF_MSPI_WRITE_LOCK_WRITE_LOCK_MASK) | 0,
		       &priv->regs->write_lock);
		readl(&priv->regs->write_lock);
	}

	return 0;
}

static int bcmstb_spi_set_speed(struct udevice *dev, uint speed)
{
	return 0;
}

static int bcmstb_spi_set_mode(struct udevice *dev, uint mode)
{
	return 0;
}

static const struct dm_spi_ops bcmstb_spi_ops = {
	.xfer		= bcmstb_spi_xfer,
	.set_speed	= bcmstb_spi_set_speed,
	.set_mode	= bcmstb_spi_set_mode,
};

static const struct udevice_id bcmstb_spi_id[] = {
	{ .compatible = "brcm,spi-brcmstb" },
	{ }
};

U_BOOT_DRIVER(bcmstb_spi) = {
	.name				= "bcmstb_spi",
	.id				= UCLASS_SPI,
	.of_match			= bcmstb_spi_id,
	.ops				= &bcmstb_spi_ops,
	.ofdata_to_platdata		= bcmstb_spi_ofdata_to_platdata,
	.probe				= bcmstb_spi_probe,
	.platdata_auto_alloc_size	= sizeof(struct bcmstb_spi_platdata),
	.priv_auto_alloc_size		= sizeof(struct bcmstb_spi_priv),
};
