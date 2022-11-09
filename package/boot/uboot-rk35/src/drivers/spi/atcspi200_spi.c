/*
 * Andestech ATCSPI200 SPI controller driver.
 *
 * Copyright 2017 Andes Technology, Inc.
 * Author: Rick Chen (rick@andestech.com)
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <clk.h>
#include <common.h>
#include <malloc.h>
#include <spi.h>
#include <asm/io.h>
#include <dm.h>

DECLARE_GLOBAL_DATA_PTR;

#define MAX_TRANSFER_LEN	512
#define CHUNK_SIZE		1
#define SPI_TIMEOUT		0x100000
#define SPI0_BUS		0
#define SPI1_BUS		1
#define SPI0_BASE		0xf0b00000
#define SPI1_BASE		0xf0f00000
#define NSPI_MAX_CS_NUM		1

struct atcspi200_spi_regs {
	u32	rev;
	u32	reserve1[3];
	u32	format;		/* 0x10 */
#define DATA_LENGTH(x)	((x-1)<<8)
	u32	pio;
	u32	reserve2[2];
	u32	tctrl;		/* 0x20 */
#define TRAMODE_OFFSET	24
#define TRAMODE_MASK	(0x0F<<TRAMODE_OFFSET)
#define TRAMODE_WR_SYNC	(0<<TRAMODE_OFFSET)
#define TRAMODE_WO	(1<<TRAMODE_OFFSET)
#define TRAMODE_RO	(2<<TRAMODE_OFFSET)
#define TRAMODE_WR	(3<<TRAMODE_OFFSET)
#define TRAMODE_RW	(4<<TRAMODE_OFFSET)
#define TRAMODE_WDR	(5<<TRAMODE_OFFSET)
#define TRAMODE_RDW	(6<<TRAMODE_OFFSET)
#define TRAMODE_NONE	(7<<TRAMODE_OFFSET)
#define TRAMODE_DW	(8<<TRAMODE_OFFSET)
#define TRAMODE_DR	(9<<TRAMODE_OFFSET)
#define WCNT_OFFSET	12
#define WCNT_MASK	(0x1FF<<WCNT_OFFSET)
#define RCNT_OFFSET	0
#define RCNT_MASK	(0x1FF<<RCNT_OFFSET)
	u32	cmd;
	u32	addr;
	u32	data;
	u32	ctrl;		/* 0x30 */
#define TXFTH_OFFSET	16
#define RXFTH_OFFSET	8
#define TXDMAEN		(1<<4)
#define RXDMAEN		(1<<3)
#define TXFRST		(1<<2)
#define RXFRST		(1<<1)
#define SPIRST		(1<<0)
	u32	status;
#define TXFFL		(1<<23)
#define TXEPTY		(1<<22)
#define TXFVE_MASK	(0x1F<<16)
#define RXFEM		(1<<14)
#define RXFVE_OFFSET	(8)
#define RXFVE_MASK	(0x1F<<RXFVE_OFFSET)
#define SPIBSY		(1<<0)
	u32	inten;
	u32	intsta;
	u32	timing;		/* 0x40 */
#define SCLK_DIV_MASK	0xFF
};

struct nds_spi_slave {
	volatile struct atcspi200_spi_regs *regs;
	int		to;
	unsigned int	freq;
	ulong		clock;
	unsigned int	mode;
	u8 		num_cs;
	unsigned int	mtiming;
	size_t		cmd_len;
	u8		cmd_buf[16];
	size_t		data_len;
	size_t		tran_len;
	u8		*din;
	u8		*dout;
	unsigned int    max_transfer_length;
};

static int __atcspi200_spi_set_speed(struct nds_spi_slave *ns)
{
	u32 tm;
	u8 div;
	tm = ns->regs->timing;
	tm &= ~SCLK_DIV_MASK;

	if(ns->freq >= ns->clock)
		div =0xff;
	else{
		for (div = 0; div < 0xff; div++) {
			if (ns->freq >= ns->clock / (2 * (div + 1)))
				break;
		}
	}

	tm |= div;
	ns->regs->timing = tm;

	return 0;

}

static int __atcspi200_spi_claim_bus(struct nds_spi_slave *ns)
{
		unsigned int format=0;
		ns->regs->ctrl |= (TXFRST|RXFRST|SPIRST);
		while((ns->regs->ctrl &(TXFRST|RXFRST|SPIRST))&&(ns->to--))
			if(!ns->to)
				return -EINVAL;

		ns->cmd_len = 0;
		format = ns->mode|DATA_LENGTH(8);
		ns->regs->format = format;
		__atcspi200_spi_set_speed(ns);

		return 0;
}

static int __atcspi200_spi_release_bus(struct nds_spi_slave *ns)
{
	/* do nothing */
	return 0;
}

static int __atcspi200_spi_start(struct nds_spi_slave *ns)
{
	int i,olen=0;
	int tc = ns->regs->tctrl;

	tc &= ~(WCNT_MASK|RCNT_MASK|TRAMODE_MASK);
	if ((ns->din)&&(ns->cmd_len))
		tc |= TRAMODE_WR;
	else if (ns->din)
		tc |= TRAMODE_RO;
	else
		tc |= TRAMODE_WO;

	if(ns->dout)
		olen = ns->tran_len;
	tc |= (ns->cmd_len+olen-1) << WCNT_OFFSET;

	if(ns->din)
		tc |= (ns->tran_len-1) << RCNT_OFFSET;

	ns->regs->tctrl = tc;
	ns->regs->cmd = 1;

	for (i=0;i<ns->cmd_len;i++)
		ns->regs->data = ns->cmd_buf[i];

	return 0;
}

static int __atcspi200_spi_stop(struct nds_spi_slave *ns)
{
	ns->regs->timing = ns->mtiming;
	while ((ns->regs->status & SPIBSY)&&(ns->to--))
		if (!ns->to)
			return -EINVAL;

	return 0;
}

static void __nspi_espi_tx(struct nds_spi_slave *ns, const void *dout)
{
	ns->regs->data = *(u8 *)dout;
}

static int __nspi_espi_rx(struct nds_spi_slave *ns, void *din, unsigned int bytes)
{
	*(u8 *)din = ns->regs->data;
	return bytes;
}


static int __atcspi200_spi_xfer(struct nds_spi_slave *ns,
		unsigned int bitlen,  const void *data_out, void *data_in,
		unsigned long flags)
{
		unsigned int event, rx_bytes;
		const void *dout = NULL;
		void *din = NULL;
		int num_blks, num_chunks, max_tran_len, tran_len;
		int num_bytes;
		u8 *cmd_buf = ns->cmd_buf;
		size_t cmd_len = ns->cmd_len;
		size_t data_len = bitlen / 8;
		int rf_cnt;
		int ret = 0;

		max_tran_len = ns->max_transfer_length;
		switch (flags) {
		case SPI_XFER_BEGIN:
			cmd_len = ns->cmd_len = data_len;
			memcpy(cmd_buf, data_out, cmd_len);
			return 0;

		case 0:
		case SPI_XFER_END:
			if (bitlen == 0) {
				return 0;
			}
			ns->data_len = data_len;
			ns->din = (u8 *)data_in;
			ns->dout = (u8 *)data_out;
			break;

		case SPI_XFER_BEGIN | SPI_XFER_END:
			ns->data_len = 0;
			ns->din = 0;
			ns->dout = 0;
			cmd_len = ns->cmd_len = data_len;
			memcpy(cmd_buf, data_out, cmd_len);
			data_out = 0;
			data_len = 0;
			__atcspi200_spi_start(ns);
			break;
		}
		debug("spi_xfer: data_out %08X(%p) data_in %08X(%p) data_len %u\n",
		      *(uint *)data_out, data_out, *(uint *)data_in, data_in, data_len);
		num_chunks = DIV_ROUND_UP(data_len, max_tran_len);
		din = data_in;
		dout = data_out;
		while (num_chunks--) {
			tran_len = min(data_len, (size_t)max_tran_len);
			ns->tran_len = tran_len;
			num_blks = DIV_ROUND_UP(tran_len , CHUNK_SIZE);
			num_bytes = (tran_len) % CHUNK_SIZE;
			if(num_bytes == 0)
				num_bytes = CHUNK_SIZE;
			__atcspi200_spi_start(ns);

			while (num_blks) {
				event = in_le32(&ns->regs->status);
				if ((event & TXEPTY) && (data_out)) {
					__nspi_espi_tx(ns, dout);
					num_blks -= CHUNK_SIZE;
					dout += CHUNK_SIZE;
				}

				if ((event & RXFVE_MASK) && (data_in)) {
					rf_cnt = ((event & RXFVE_MASK)>> RXFVE_OFFSET);
					if (rf_cnt >= CHUNK_SIZE)
						rx_bytes = CHUNK_SIZE;
					else if (num_blks == 1 && rf_cnt == num_bytes)
						rx_bytes = num_bytes;
					else
						continue;

					if (__nspi_espi_rx(ns, din, rx_bytes) == rx_bytes) {
						num_blks -= CHUNK_SIZE;
						din = (unsigned char *)din + rx_bytes;
					}
				}
			}

			data_len -= tran_len;
			if(data_len)
			{
				ns->cmd_buf[1] += ((tran_len>>16)&0xff);
				ns->cmd_buf[2] += ((tran_len>>8)&0xff);
				ns->cmd_buf[3] += ((tran_len)&0xff);
				ns->data_len = data_len;
			}
			ret = __atcspi200_spi_stop(ns);
		}
		ret = __atcspi200_spi_stop(ns);

		return ret;
}

static int atcspi200_spi_set_speed(struct udevice *bus, uint max_hz)
{
	struct nds_spi_slave *ns = dev_get_priv(bus);

	debug("%s speed %u\n", __func__, max_hz);

	ns->freq = max_hz;
	__atcspi200_spi_set_speed(ns);

	return 0;
}

static int atcspi200_spi_set_mode(struct udevice *bus, uint mode)
{
	struct nds_spi_slave *ns = dev_get_priv(bus);

	debug("%s mode %u\n", __func__, mode);
	ns->mode = mode;

	return 0;
}

static int atcspi200_spi_claim_bus(struct udevice *dev)
{
	struct dm_spi_slave_platdata *slave_plat =
		dev_get_parent_platdata(dev);
	struct udevice *bus = dev->parent;
	struct nds_spi_slave *ns = dev_get_priv(bus);

	if (slave_plat->cs >= ns->num_cs) {
		printf("Invalid SPI chipselect\n");
		return -EINVAL;
	}

	return __atcspi200_spi_claim_bus(ns);
}

static int atcspi200_spi_release_bus(struct udevice *dev)
{
	struct nds_spi_slave *ns = dev_get_priv(dev->parent);

	return __atcspi200_spi_release_bus(ns);
}

static int atcspi200_spi_xfer(struct udevice *dev, unsigned int bitlen,
			    const void *dout, void *din,
			    unsigned long flags)
{
	struct udevice *bus = dev->parent;
	struct nds_spi_slave *ns = dev_get_priv(bus);

	return __atcspi200_spi_xfer(ns, bitlen, dout, din, flags);
}

static int atcspi200_spi_get_clk(struct udevice *bus)
{
	struct nds_spi_slave *ns = dev_get_priv(bus);
	struct clk clk;
	ulong clk_rate;
	int ret;

	ret = clk_get_by_index(bus, 0, &clk);
	if (ret)
		return -EINVAL;

	clk_rate = clk_get_rate(&clk);
	if (!clk_rate)
		return -EINVAL;

	ns->clock = clk_rate;
	clk_free(&clk);

	return 0;
}

static int atcspi200_spi_probe(struct udevice *bus)
{
	struct nds_spi_slave *ns = dev_get_priv(bus);

	ns->to = SPI_TIMEOUT;
	ns->max_transfer_length = MAX_TRANSFER_LEN;
	ns->mtiming = ns->regs->timing;
	atcspi200_spi_get_clk(bus);

	return 0;
}

static int atcspi200_ofdata_to_platadata(struct udevice *bus)
{
	struct nds_spi_slave *ns = dev_get_priv(bus);
	const void *blob = gd->fdt_blob;
	int node = dev_of_offset(bus);

	ns->regs = map_physmem(devfdt_get_addr(bus),
				 sizeof(struct atcspi200_spi_regs),
				 MAP_NOCACHE);
	if (!ns->regs) {
		printf("%s: could not map device address\n", __func__);
		return -EINVAL;
	}
	ns->num_cs = fdtdec_get_int(blob, node, "num-cs", 4);

	return 0;
}

static const struct dm_spi_ops atcspi200_spi_ops = {
	.claim_bus	= atcspi200_spi_claim_bus,
	.release_bus	= atcspi200_spi_release_bus,
	.xfer		= atcspi200_spi_xfer,
	.set_speed	= atcspi200_spi_set_speed,
	.set_mode	= atcspi200_spi_set_mode,
};

static const struct udevice_id atcspi200_spi_ids[] = {
	{ .compatible = "andestech,atcspi200" },
	{ }
};

U_BOOT_DRIVER(atcspi200_spi) = {
	.name = "atcspi200_spi",
	.id = UCLASS_SPI,
	.of_match = atcspi200_spi_ids,
	.ops = &atcspi200_spi_ops,
	.ofdata_to_platdata = atcspi200_ofdata_to_platadata,
	.priv_auto_alloc_size = sizeof(struct nds_spi_slave),
	.probe = atcspi200_spi_probe,
};
