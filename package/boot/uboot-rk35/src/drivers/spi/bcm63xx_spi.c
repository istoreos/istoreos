/*
 * Copyright (C) 2017 Álvaro Fernández Rojas <noltari@gmail.com>
 *
 * Derived from linux/drivers/spi/spi-bcm63xx.c:
 *	Copyright (C) 2009-2012 Florian Fainelli <florian@openwrt.org>
 *	Copyright (C) 2010 Tanguy Bouzeloc <tanguy.bouzeloc@efixo.com>
 *
 * SPDX-License-Identifier: GPL-2.0+
 */

#include <common.h>
#include <clk.h>
#include <dm.h>
#include <spi.h>
#include <reset.h>
#include <wait_bit.h>
#include <asm/io.h>

DECLARE_GLOBAL_DATA_PTR;

/* BCM6348 SPI core */
#define SPI_6348_CLK			0x06
#define SPI_6348_CMD			0x00
#define SPI_6348_CTL			0x40
#define SPI_6348_CTL_SHIFT		6
#define SPI_6348_FILL			0x07
#define SPI_6348_IR_MASK		0x04
#define SPI_6348_IR_STAT		0x02
#define SPI_6348_RX			0x80
#define SPI_6348_RX_SIZE		0x3f
#define SPI_6348_TX			0x41
#define SPI_6348_TX_SIZE		0x3f

/* BCM6358 SPI core */
#define SPI_6358_CLK			0x706
#define SPI_6358_CMD			0x700
#define SPI_6358_CTL			0x000
#define SPI_6358_CTL_SHIFT		14
#define SPI_6358_FILL			0x707
#define SPI_6358_IR_MASK		0x702
#define SPI_6358_IR_STAT		0x704
#define SPI_6358_RX			0x400
#define SPI_6358_RX_SIZE		0x220
#define SPI_6358_TX			0x002
#define SPI_6358_TX_SIZE		0x21e

/* SPI Clock register */
#define SPI_CLK_SHIFT		0
#define SPI_CLK_20MHZ		(0 << SPI_CLK_SHIFT)
#define SPI_CLK_0_391MHZ	(1 << SPI_CLK_SHIFT)
#define SPI_CLK_0_781MHZ	(2 << SPI_CLK_SHIFT)
#define SPI_CLK_1_563MHZ	(3 << SPI_CLK_SHIFT)
#define SPI_CLK_3_125MHZ	(4 << SPI_CLK_SHIFT)
#define SPI_CLK_6_250MHZ	(5 << SPI_CLK_SHIFT)
#define SPI_CLK_12_50MHZ	(6 << SPI_CLK_SHIFT)
#define SPI_CLK_25MHZ		(7 << SPI_CLK_SHIFT)
#define SPI_CLK_MASK		(7 << SPI_CLK_SHIFT)
#define SPI_CLK_SSOFF_SHIFT	3
#define SPI_CLK_SSOFF_2		(2 << SPI_CLK_SSOFF_SHIFT)
#define SPI_CLK_SSOFF_MASK	(7 << SPI_CLK_SSOFF_SHIFT)
#define SPI_CLK_BSWAP_SHIFT	7
#define SPI_CLK_BSWAP_MASK	(1 << SPI_CLK_BSWAP_SHIFT)

/* SPI Command register */
#define SPI_CMD_OP_SHIFT	0
#define SPI_CMD_OP_START	(0x3 << SPI_CMD_OP_SHIFT)
#define SPI_CMD_SLAVE_SHIFT	4
#define SPI_CMD_SLAVE_MASK	(0xf << SPI_CMD_SLAVE_SHIFT)
#define SPI_CMD_PREPEND_SHIFT	8
#define SPI_CMD_PREPEND_BYTES	0xf
#define SPI_CMD_3WIRE_SHIFT	12
#define SPI_CMD_3WIRE_MASK	(1 << SPI_CMD_3WIRE_SHIFT)

/* SPI Control register */
#define SPI_CTL_TYPE_FD_RW	0
#define SPI_CTL_TYPE_HD_W	1
#define SPI_CTL_TYPE_HD_R	2

/* SPI Interrupt registers */
#define SPI_IR_DONE_SHIFT	0
#define SPI_IR_DONE_MASK	(1 << SPI_IR_DONE_SHIFT)
#define SPI_IR_RXOVER_SHIFT	1
#define SPI_IR_RXOVER_MASK	(1 << SPI_IR_RXOVER_SHIFT)
#define SPI_IR_TXUNDER_SHIFT	2
#define SPI_IR_TXUNDER_MASK	(1 << SPI_IR_TXUNDER_SHIFT)
#define SPI_IR_TXOVER_SHIFT	3
#define SPI_IR_TXOVER_MASK	(1 << SPI_IR_TXOVER_SHIFT)
#define SPI_IR_RXUNDER_SHIFT	4
#define SPI_IR_RXUNDER_MASK	(1 << SPI_IR_RXUNDER_SHIFT)
#define SPI_IR_CLEAR_MASK	(SPI_IR_DONE_MASK |\
				 SPI_IR_RXOVER_MASK |\
				 SPI_IR_TXUNDER_MASK |\
				 SPI_IR_TXOVER_MASK |\
				 SPI_IR_RXUNDER_MASK)

enum bcm63xx_regs_spi {
	SPI_CLK,
	SPI_CMD,
	SPI_CTL,
	SPI_CTL_SHIFT,
	SPI_FILL,
	SPI_IR_MASK,
	SPI_IR_STAT,
	SPI_RX,
	SPI_RX_SIZE,
	SPI_TX,
	SPI_TX_SIZE,
};

struct bcm63xx_spi_priv {
	const unsigned long *regs;
	void __iomem *base;
	size_t tx_bytes;
	uint8_t num_cs;
};

#define SPI_CLK_CNT		8
static const unsigned bcm63xx_spi_freq_table[SPI_CLK_CNT][2] = {
	{ 25000000, SPI_CLK_25MHZ },
	{ 20000000, SPI_CLK_20MHZ },
	{ 12500000, SPI_CLK_12_50MHZ },
	{  6250000, SPI_CLK_6_250MHZ },
	{  3125000, SPI_CLK_3_125MHZ },
	{  1563000, SPI_CLK_1_563MHZ },
	{   781000, SPI_CLK_0_781MHZ },
	{   391000, SPI_CLK_0_391MHZ }
};

static int bcm63xx_spi_cs_info(struct udevice *bus, uint cs,
			   struct spi_cs_info *info)
{
	struct bcm63xx_spi_priv *priv = dev_get_priv(bus);

	if (cs >= priv->num_cs) {
		printf("no cs %u\n", cs);
		return -ENODEV;
	}

	return 0;
}

static int bcm63xx_spi_set_mode(struct udevice *bus, uint mode)
{
	struct bcm63xx_spi_priv *priv = dev_get_priv(bus);
	const unsigned long *regs = priv->regs;

	if (mode & SPI_LSB_FIRST)
		setbits_8(priv->base + regs[SPI_CLK], SPI_CLK_BSWAP_MASK);
	else
		clrbits_8(priv->base + regs[SPI_CLK], SPI_CLK_BSWAP_MASK);

	return 0;
}

static int bcm63xx_spi_set_speed(struct udevice *bus, uint speed)
{
	struct bcm63xx_spi_priv *priv = dev_get_priv(bus);
	const unsigned long *regs = priv->regs;
	uint8_t clk_cfg;
	int i;

	/* default to lowest clock configuration */
	clk_cfg = SPI_CLK_0_391MHZ;

	/* find the closest clock configuration */
	for (i = 0; i < SPI_CLK_CNT; i++) {
		if (speed >= bcm63xx_spi_freq_table[i][0]) {
			clk_cfg = bcm63xx_spi_freq_table[i][1];
			break;
		}
	}

	/* write clock configuration */
	clrsetbits_8(priv->base + regs[SPI_CLK],
		     SPI_CLK_SSOFF_MASK | SPI_CLK_MASK,
		     clk_cfg | SPI_CLK_SSOFF_2);

	return 0;
}

/*
 * BCM63xx SPI driver doesn't allow keeping CS active between transfers since
 * they are HW controlled.
 * However, it provides a mechanism to prepend write transfers prior to read
 * transfers (with a maximum prepend of 15 bytes), which is usually enough for
 * SPI-connected flashes since reading requires prepending a write transfer of
 * 5 bytes.
 *
 * This implementation takes advantage of the prepend mechanism and combines
 * multiple transfers into a single one where possible (single/multiple write
 * transfer(s) followed by a final read/write transfer).
 * However, it's not possible to buffer reads, which means that read transfers
 * should always be done as the final ones.
 * On the other hand, take into account that combining write transfers into
 * a single one is just buffering and doesn't require prepend mechanism.
 */
static int bcm63xx_spi_xfer(struct udevice *dev, unsigned int bitlen,
		const void *dout, void *din, unsigned long flags)
{
	struct bcm63xx_spi_priv *priv = dev_get_priv(dev->parent);
	const unsigned long *regs = priv->regs;
	size_t data_bytes = bitlen / 8;

	if (flags & SPI_XFER_BEGIN) {
		/* clear prepends */
		priv->tx_bytes = 0;

		/* initialize hardware */
		writeb_be(0, priv->base + regs[SPI_IR_MASK]);
	}

	if (din) {
		/* buffering reads not possible since cs is hw controlled */
		if (!(flags & SPI_XFER_END)) {
			printf("unable to buffer reads\n");
			return -EINVAL;
		}

		/* check rx size */
		 if (data_bytes > regs[SPI_RX_SIZE]) {
			printf("max rx bytes exceeded\n");
			return -EMSGSIZE;
		}
	}

	if (dout) {
		/* check tx size */
		if (priv->tx_bytes + data_bytes > regs[SPI_TX_SIZE]) {
			printf("max tx bytes exceeded\n");
			return -EMSGSIZE;
		}

		/* copy tx data */
		memcpy_toio(priv->base + regs[SPI_TX] + priv->tx_bytes,
			    dout, data_bytes);
		priv->tx_bytes += data_bytes;
	}

	if (flags & SPI_XFER_END) {
		struct dm_spi_slave_platdata *plat =
			dev_get_parent_platdata(dev);
		uint16_t val, cmd;
		int ret;

		/* determine control config */
		if (dout && !din) {
			/* buffered write transfers */
			val = priv->tx_bytes;
			val |= (SPI_CTL_TYPE_HD_W << regs[SPI_CTL_SHIFT]);
			priv->tx_bytes = 0;
		} else {
			if (dout && din && (flags & SPI_XFER_ONCE)) {
				/* full duplex read/write */
				val = data_bytes;
				val |= (SPI_CTL_TYPE_FD_RW <<
					regs[SPI_CTL_SHIFT]);
				priv->tx_bytes = 0;
			} else {
				/* prepended write transfer */
				val = data_bytes;
				val |= (SPI_CTL_TYPE_HD_R <<
					regs[SPI_CTL_SHIFT]);
				if (priv->tx_bytes > SPI_CMD_PREPEND_BYTES) {
					printf("max prepend bytes exceeded\n");
					return -EMSGSIZE;
				}
			}
		}

		if (regs[SPI_CTL_SHIFT] >= 8)
			writew_be(val, priv->base + regs[SPI_CTL]);
		else
			writeb_be(val, priv->base + regs[SPI_CTL]);

		/* clear interrupts */
		writeb_be(SPI_IR_CLEAR_MASK, priv->base + regs[SPI_IR_STAT]);

		/* issue the transfer */
		cmd = SPI_CMD_OP_START;
		cmd |= (plat->cs << SPI_CMD_SLAVE_SHIFT) & SPI_CMD_SLAVE_MASK;
		cmd |= (priv->tx_bytes << SPI_CMD_PREPEND_SHIFT);
		if (plat->mode & SPI_3WIRE)
			cmd |= SPI_CMD_3WIRE_MASK;
		writew_be(cmd, priv->base + regs[SPI_CMD]);

		/* enable interrupts */
		writeb_be(SPI_IR_DONE_MASK, priv->base + regs[SPI_IR_MASK]);

		ret = wait_for_bit_8(priv->base + regs[SPI_IR_STAT],
				     SPI_IR_DONE_MASK, true, 1000, false);
		if (ret) {
			printf("interrupt timeout\n");
			return ret;
		}

		/* copy rx data */
		if (din)
			memcpy_fromio(din, priv->base + regs[SPI_RX],
				      data_bytes);
	}

	return 0;
}

static const struct dm_spi_ops bcm63xx_spi_ops = {
	.cs_info = bcm63xx_spi_cs_info,
	.set_mode = bcm63xx_spi_set_mode,
	.set_speed = bcm63xx_spi_set_speed,
	.xfer = bcm63xx_spi_xfer,
};

static const unsigned long bcm6348_spi_regs[] = {
	[SPI_CLK] = SPI_6348_CLK,
	[SPI_CMD] = SPI_6348_CMD,
	[SPI_CTL] = SPI_6348_CTL,
	[SPI_CTL_SHIFT] = SPI_6348_CTL_SHIFT,
	[SPI_FILL] = SPI_6348_FILL,
	[SPI_IR_MASK] = SPI_6348_IR_MASK,
	[SPI_IR_STAT] = SPI_6348_IR_STAT,
	[SPI_RX] = SPI_6348_RX,
	[SPI_RX_SIZE] = SPI_6348_RX_SIZE,
	[SPI_TX] = SPI_6348_TX,
	[SPI_TX_SIZE] = SPI_6348_TX_SIZE,
};

static const unsigned long bcm6358_spi_regs[] = {
	[SPI_CLK] = SPI_6358_CLK,
	[SPI_CMD] = SPI_6358_CMD,
	[SPI_CTL] = SPI_6358_CTL,
	[SPI_CTL_SHIFT] = SPI_6358_CTL_SHIFT,
	[SPI_FILL] = SPI_6358_FILL,
	[SPI_IR_MASK] = SPI_6358_IR_MASK,
	[SPI_IR_STAT] = SPI_6358_IR_STAT,
	[SPI_RX] = SPI_6358_RX,
	[SPI_RX_SIZE] = SPI_6358_RX_SIZE,
	[SPI_TX] = SPI_6358_TX,
	[SPI_TX_SIZE] = SPI_6358_TX_SIZE,
};

static const struct udevice_id bcm63xx_spi_ids[] = {
	{
		.compatible = "brcm,bcm6348-spi",
		.data = (ulong)&bcm6348_spi_regs,
	}, {
		.compatible = "brcm,bcm6358-spi",
		.data = (ulong)&bcm6358_spi_regs,
	}, { /* sentinel */ }
};

static int bcm63xx_spi_child_pre_probe(struct udevice *dev)
{
	struct bcm63xx_spi_priv *priv = dev_get_priv(dev->parent);
	const unsigned long *regs = priv->regs;
	struct spi_slave *slave = dev_get_parent_priv(dev);
	struct dm_spi_slave_platdata *plat = dev_get_parent_platdata(dev);

	/* check cs */
	if (plat->cs >= priv->num_cs) {
		printf("no cs %u\n", plat->cs);
		return -ENODEV;
	}

	/* max read/write sizes */
	slave->max_read_size = regs[SPI_RX_SIZE];
	slave->max_write_size = regs[SPI_TX_SIZE];

	return 0;
}

static int bcm63xx_spi_probe(struct udevice *dev)
{
	struct bcm63xx_spi_priv *priv = dev_get_priv(dev);
	const unsigned long *regs =
		(const unsigned long *)dev_get_driver_data(dev);
	struct reset_ctl rst_ctl;
	struct clk clk;
	fdt_addr_t addr;
	fdt_size_t size;
	int ret;

	addr = devfdt_get_addr_size_index(dev, 0, &size);
	if (addr == FDT_ADDR_T_NONE)
		return -EINVAL;

	priv->regs = regs;
	priv->base = ioremap(addr, size);
	priv->num_cs = fdtdec_get_uint(gd->fdt_blob, dev_of_offset(dev),
				       "num-cs", 8);

	/* enable clock */
	ret = clk_get_by_index(dev, 0, &clk);
	if (ret < 0)
		return ret;

	ret = clk_enable(&clk);
	if (ret < 0)
		return ret;

	ret = clk_free(&clk);
	if (ret < 0)
		return ret;

	/* perform reset */
	ret = reset_get_by_index(dev, 0, &rst_ctl);
	if (ret < 0)
		return ret;

	ret = reset_deassert(&rst_ctl);
	if (ret < 0)
		return ret;

	ret = reset_free(&rst_ctl);
	if (ret < 0)
		return ret;

	/* initialize hardware */
	writeb_be(0, priv->base + regs[SPI_IR_MASK]);

	/* set fill register */
	writeb_be(0xff, priv->base + regs[SPI_FILL]);

	return 0;
}

U_BOOT_DRIVER(bcm63xx_spi) = {
	.name = "bcm63xx_spi",
	.id = UCLASS_SPI,
	.of_match = bcm63xx_spi_ids,
	.ops = &bcm63xx_spi_ops,
	.priv_auto_alloc_size = sizeof(struct bcm63xx_spi_priv),
	.child_pre_probe = bcm63xx_spi_child_pre_probe,
	.probe = bcm63xx_spi_probe,
};
