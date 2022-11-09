// SPDX-License-Identifier: GPL-2.0-only
/*
 * Rockchip Serial Flash Controller Driver
 *
 * Copyright (c) 2017-2021, Rockchip Inc.
 * Author: Shawn Lin <shawn.lin@rock-chips.com>
 *	   Chris Morgan <macromorgan@hotmail.com>
 *	   Jon Lin <Jon.lin@rock-chips.com>
 */

#include <asm/io.h>
#include <bouncebuf.h>
#include <clk.h>
#include <dm.h>
#include <linux/bitops.h>
#include <linux/delay.h>
#include <linux/iopoll.h>
#include <spi.h>
#include <spi-mem.h>

/* System control */
#define SFC_CTRL			0x0
#define  SFC_CTRL_PHASE_SEL_NEGETIVE	BIT(1)
#define  SFC_CTRL_CMD_BITS_SHIFT	8
#define  SFC_CTRL_ADDR_BITS_SHIFT	10
#define  SFC_CTRL_DATA_BITS_SHIFT	12

/* Interrupt mask */
#define SFC_IMR				0x4
#define  SFC_IMR_RX_FULL		BIT(0)
#define  SFC_IMR_RX_UFLOW		BIT(1)
#define  SFC_IMR_TX_OFLOW		BIT(2)
#define  SFC_IMR_TX_EMPTY		BIT(3)
#define  SFC_IMR_TRAN_FINISH		BIT(4)
#define  SFC_IMR_BUS_ERR		BIT(5)
#define  SFC_IMR_NSPI_ERR		BIT(6)
#define  SFC_IMR_DMA			BIT(7)

/* Interrupt clear */
#define SFC_ICLR			0x8
#define  SFC_ICLR_RX_FULL		BIT(0)
#define  SFC_ICLR_RX_UFLOW		BIT(1)
#define  SFC_ICLR_TX_OFLOW		BIT(2)
#define  SFC_ICLR_TX_EMPTY		BIT(3)
#define  SFC_ICLR_TRAN_FINISH		BIT(4)
#define  SFC_ICLR_BUS_ERR		BIT(5)
#define  SFC_ICLR_NSPI_ERR		BIT(6)
#define  SFC_ICLR_DMA			BIT(7)

/* FIFO threshold level */
#define SFC_FTLR			0xc
#define  SFC_FTLR_TX_SHIFT		0
#define  SFC_FTLR_TX_MASK		0x1f
#define  SFC_FTLR_RX_SHIFT		8
#define  SFC_FTLR_RX_MASK		0x1f

/* Reset FSM and FIFO */
#define SFC_RCVR			0x10
#define  SFC_RCVR_RESET			BIT(0)

/* Enhanced mode */
#define SFC_AX				0x14

/* Address Bit number */
#define SFC_ABIT			0x18

/* Interrupt status */
#define SFC_ISR				0x1c
#define  SFC_ISR_RX_FULL_SHIFT		BIT(0)
#define  SFC_ISR_RX_UFLOW_SHIFT		BIT(1)
#define  SFC_ISR_TX_OFLOW_SHIFT		BIT(2)
#define  SFC_ISR_TX_EMPTY_SHIFT		BIT(3)
#define  SFC_ISR_TX_FINISH_SHIFT	BIT(4)
#define  SFC_ISR_BUS_ERR_SHIFT		BIT(5)
#define  SFC_ISR_NSPI_ERR_SHIFT		BIT(6)
#define  SFC_ISR_DMA_SHIFT		BIT(7)

/* FIFO status */
#define SFC_FSR				0x20
#define  SFC_FSR_TX_IS_FULL		BIT(0)
#define  SFC_FSR_TX_IS_EMPTY		BIT(1)
#define  SFC_FSR_RX_IS_EMPTY		BIT(2)
#define  SFC_FSR_RX_IS_FULL		BIT(3)
#define  SFC_FSR_TXLV_MASK		GENMASK(12, 8)
#define  SFC_FSR_TXLV_SHIFT		8
#define  SFC_FSR_RXLV_MASK		GENMASK(20, 16)
#define  SFC_FSR_RXLV_SHIFT		16

/* FSM status */
#define SFC_SR				0x24
#define  SFC_SR_IS_IDLE			0x0
#define  SFC_SR_IS_BUSY			0x1

/* Raw interrupt status */
#define SFC_RISR			0x28
#define  SFC_RISR_RX_FULL		BIT(0)
#define  SFC_RISR_RX_UNDERFLOW		BIT(1)
#define  SFC_RISR_TX_OVERFLOW		BIT(2)
#define  SFC_RISR_TX_EMPTY		BIT(3)
#define  SFC_RISR_TRAN_FINISH		BIT(4)
#define  SFC_RISR_BUS_ERR		BIT(5)
#define  SFC_RISR_NSPI_ERR		BIT(6)
#define  SFC_RISR_DMA			BIT(7)

/* Version */
#define SFC_VER				0x2C
#define  SFC_VER_3			0x3
#define  SFC_VER_4			0x4
#define  SFC_VER_5			0x5
#define  SFC_VER_6			0x6

/* Delay line controller resiter */
#define SFC_DLL_CTRL0			0x3C
#define SFC_DLL_CTRL0_SCLK_SMP_DLL	BIT(15)
#define SFC_DLL_CTRL0_DLL_MAX_VER4	0xFFU
#define SFC_DLL_CTRL0_DLL_MAX_VER5	0x1FFU

/* Master trigger */
#define SFC_DMA_TRIGGER			0x80
#define SFC_DMA_TRIGGER_START		1

/* Src or Dst addr for master */
#define SFC_DMA_ADDR			0x84

/* Length control register extension 32GB */
#define SFC_LEN_CTRL			0x88
#define SFC_LEN_CTRL_TRB_SEL		1
#define SFC_LEN_EXT			0x8C

/* Command */
#define SFC_CMD				0x100
#define  SFC_CMD_IDX_SHIFT		0
#define  SFC_CMD_DUMMY_SHIFT		8
#define  SFC_CMD_DIR_SHIFT		12
#define  SFC_CMD_DIR_RD			0
#define  SFC_CMD_DIR_WR			1
#define  SFC_CMD_ADDR_SHIFT		14
#define  SFC_CMD_ADDR_0BITS		0
#define  SFC_CMD_ADDR_24BITS		1
#define  SFC_CMD_ADDR_32BITS		2
#define  SFC_CMD_ADDR_XBITS		3
#define  SFC_CMD_TRAN_BYTES_SHIFT	16
#define  SFC_CMD_CS_SHIFT		30

/* Address */
#define SFC_ADDR			0x104

/* Data */
#define SFC_DATA			0x108

/* The controller and documentation reports that it supports up to 4 CS
 * devices (0-3), however I have only been able to test a single CS (CS 0)
 * due to the configuration of my device.
 */
#define SFC_MAX_CHIPSELECT_NUM		4

/* The SFC can transfer max 16KB - 1 at one time
 * we set it to 15.5KB here for alignment.
 */
#define SFC_MAX_IOSIZE_VER3		(512 * 31)

#define SFC_MAX_IOSIZE_VER4		(0xFFFFFFFFU)

/* DMA is only enabled for large data transmission */
#define SFC_DMA_TRANS_THRETHOLD		(0x40)

/* Maximum clock values from datasheet suggest keeping clock value under
 * 150MHz. No minimum or average value is suggested.
 */
#define SFC_MAX_SPEED		(150 * 1000 * 1000)
#define SFC_DLL_THRESHOLD_RATE	(50 * 1000 * 1000)

#define SFC_DLL_TRANING_STEP		10		/* Training step */
#define SFC_DLL_TRANING_VALID_WINDOW	80		/* Training Valid DLL winbow */

struct rockchip_sfc {
	struct udevice *dev;
	void __iomem *regbase;
	struct clk hclk;
	struct clk clk;
	u32 max_freq;
	u32 speed;
	bool use_dma;
	u32 max_iosize;
	u16 version;

	u32 last_async_size;
	u32 async;
	u32 dll_cells;
	u32 max_dll_cells;
};

static int rockchip_sfc_reset(struct rockchip_sfc *sfc)
{
	int err;
	u32 status;

	writel(SFC_RCVR_RESET, sfc->regbase + SFC_RCVR);

	err = readl_poll_timeout(sfc->regbase + SFC_RCVR, status,
				 !(status & SFC_RCVR_RESET),
				 1000000);
	if (err)
		printf("SFC reset never finished\n");

	/* Still need to clear the masked interrupt from RISR */
	writel(0xFFFFFFFF, sfc->regbase + SFC_ICLR);

	return err;
}

static u16 rockchip_sfc_get_version(struct rockchip_sfc *sfc)
{
	return  (u16)(readl(sfc->regbase + SFC_VER) & 0xffff);
}

static u32 rockchip_sfc_get_max_iosize(struct rockchip_sfc *sfc)
{
	if (rockchip_sfc_get_version(sfc) >= SFC_VER_4)
		return SFC_MAX_IOSIZE_VER4;

	return SFC_MAX_IOSIZE_VER3;
}

static u32 rockchip_sfc_get_max_dll_cells(struct rockchip_sfc *sfc)
{
	switch (rockchip_sfc_get_version(sfc)) {
	case SFC_VER_6:
	case SFC_VER_5:
		return SFC_DLL_CTRL0_DLL_MAX_VER5;
	case SFC_VER_4:
		return SFC_DLL_CTRL0_DLL_MAX_VER4;
	default:
		return 0;
	}
}

static __maybe_unused void rockchip_sfc_set_delay_lines(struct rockchip_sfc *sfc, u16 cells)
{
	u16 cell_max = (u16)rockchip_sfc_get_max_dll_cells(sfc);
	u32 val = 0;

	if (cells > cell_max)
		cells = cell_max;

	if (cells)
		val = SFC_DLL_CTRL0_SCLK_SMP_DLL | cells;

	writel(val, sfc->regbase + SFC_DLL_CTRL0);
}

static int rockchip_sfc_init(struct rockchip_sfc *sfc)
{
	writel(0, sfc->regbase + SFC_CTRL);
	if (rockchip_sfc_get_version(sfc) >= SFC_VER_4)
		writel(SFC_LEN_CTRL_TRB_SEL, sfc->regbase + SFC_LEN_CTRL);

	return 0;
}

static int rockchip_sfc_ofdata_to_platdata(struct udevice *bus)
{
	struct rockchip_sfc *sfc = dev_get_platdata(bus);

	sfc->regbase = dev_read_addr_ptr(bus);
	if (ofnode_read_bool(dev_ofnode(bus), "sfc-no-dma"))
		sfc->use_dma = false;
	else
		sfc->use_dma = true;
#if CONFIG_IS_ENABLED(CLK)
	int ret;

	ret = clk_get_by_index(bus, 0, &sfc->clk);
	if (ret < 0) {
		printf("Could not get clock for %s: %d\n", bus->name, ret);
		return ret;
	}

	ret = clk_get_by_index(bus, 1, &sfc->hclk);
	if (ret < 0) {
		printf("Could not get ahb clock for %s: %d\n", bus->name, ret);
		return ret;
	}
#endif

	return 0;
}

static int rockchip_sfc_probe(struct udevice *bus)
{
	struct rockchip_sfc *sfc = dev_get_platdata(bus);
	int ret;

#if CONFIG_IS_ENABLED(CLK)
	ret = clk_enable(&sfc->hclk);
	if (ret)
		dev_dbg(sfc->dev, "sfc Enable ahb clock fail %s: %d\n", bus->name, ret);

	ret = clk_enable(&sfc->clk);
	if (ret)
		dev_dbg(sfc->dev, "sfc Enable clock fail for %s: %d\n", bus->name, ret);
#endif

	ret = rockchip_sfc_init(sfc);
	if (ret)
		goto err_init;

	sfc->max_iosize = rockchip_sfc_get_max_iosize(sfc);
	sfc->version = rockchip_sfc_get_version(sfc);
	sfc->max_freq = SFC_MAX_SPEED;
	sfc->dev = bus;

	return 0;

err_init:
#if CONFIG_IS_ENABLED(CLK)
	clk_disable(&sfc->clk);
	clk_disable(&sfc->hclk);
#endif

	return ret;
}

static int rockchip_sfc_wait_txfifo_ready(struct rockchip_sfc *sfc, u32 timeout_us)
{
	int ret = 0;
	u32 status;

	ret = readl_poll_timeout(sfc->regbase + SFC_FSR, status,
				 status & SFC_FSR_TXLV_MASK,
				 timeout_us);
	if (ret) {
		dev_dbg(sfc->dev, "sfc wait tx fifo timeout\n");

		return -ETIMEDOUT;
	}

	return (status & SFC_FSR_TXLV_MASK) >> SFC_FSR_TXLV_SHIFT;
}

static int rockchip_sfc_wait_rxfifo_ready(struct rockchip_sfc *sfc, u32 timeout_us)
{
	int ret = 0;
	u32 status;

	ret = readl_poll_timeout(sfc->regbase + SFC_FSR, status,
				 status & SFC_FSR_RXLV_MASK,
				 timeout_us);
	if (ret) {
		dev_dbg(sfc->dev, "sfc wait rx fifo timeout\n");

		return -ETIMEDOUT;
	}

	return (status & SFC_FSR_RXLV_MASK) >> SFC_FSR_RXLV_SHIFT;
}

static void rockchip_sfc_adjust_op_work(struct spi_mem_op *op)
{
	if (unlikely(op->dummy.nbytes && !op->addr.nbytes)) {
		/*
		 * SFC not support output DUMMY cycles right after CMD cycles, so
		 * treat it as ADDR cycles.
		 */
		op->addr.nbytes = op->dummy.nbytes;
		op->addr.buswidth = op->dummy.buswidth;
		op->addr.val = 0xFFFFFFFFF;

		op->dummy.nbytes = 0;
	}
}

static int rockchip_sfc_wait_for_dma_finished(struct rockchip_sfc *sfc, int timeout)
{
	unsigned long tbase;

	/* Wait for the DMA interrupt status */
	tbase = get_timer(0);
	while (!(readl(sfc->regbase + SFC_RISR) & SFC_RISR_DMA)) {
		if (get_timer(tbase) > timeout) {
			printf("dma timeout\n");
			rockchip_sfc_reset(sfc);

			return -ETIMEDOUT;
		}

		udelay(1);
	}

	writel(0xFFFFFFFF, sfc->regbase + SFC_ICLR);

	return 0;
}

static int rockchip_sfc_xfer_setup(struct rockchip_sfc *sfc,
				   struct spi_slave *mem,
				   const struct spi_mem_op *op,
				   u32 len)
{
	struct dm_spi_slave_platdata *plat = dev_get_platdata(sfc->dev);
	u32 ctrl = 0, cmd = 0;

	/* set CMD */
	cmd = op->cmd.opcode;
	ctrl |= ((op->cmd.buswidth >> 1) << SFC_CTRL_CMD_BITS_SHIFT);

	/* set ADDR */
	if (op->addr.nbytes) {
		if (op->addr.nbytes == 4) {
			cmd |= SFC_CMD_ADDR_32BITS << SFC_CMD_ADDR_SHIFT;
		} else if (op->addr.nbytes == 3) {
			cmd |= SFC_CMD_ADDR_24BITS << SFC_CMD_ADDR_SHIFT;
		} else {
			cmd |= SFC_CMD_ADDR_XBITS << SFC_CMD_ADDR_SHIFT;
			writel(op->addr.nbytes * 8 - 1, sfc->regbase + SFC_ABIT);
		}

		ctrl |= ((op->addr.buswidth >> 1) << SFC_CTRL_ADDR_BITS_SHIFT);
	}

	/* set DUMMY */
	if (op->dummy.nbytes) {
		if (op->dummy.buswidth == 4)
			cmd |= op->dummy.nbytes * 2 << SFC_CMD_DUMMY_SHIFT;
		else if (op->dummy.buswidth == 2)
			cmd |= op->dummy.nbytes * 4 << SFC_CMD_DUMMY_SHIFT;
		else
			cmd |= op->dummy.nbytes * 8 << SFC_CMD_DUMMY_SHIFT;
	}

	/* set DATA */
	if (sfc->version >= SFC_VER_4) /* Clear it if no data to transfer */
		writel(len, sfc->regbase + SFC_LEN_EXT);
	else
		cmd |= len << SFC_CMD_TRAN_BYTES_SHIFT;
	if (len) {
		if (op->data.dir == SPI_MEM_DATA_OUT)
			cmd |= SFC_CMD_DIR_WR << SFC_CMD_DIR_SHIFT;

		ctrl |= ((op->data.buswidth >> 1) << SFC_CTRL_DATA_BITS_SHIFT);
	}
	if (!len && op->addr.nbytes)
		cmd |= SFC_CMD_DIR_WR << SFC_CMD_DIR_SHIFT;

	/* set the Controller */
	ctrl |= SFC_CTRL_PHASE_SEL_NEGETIVE;
	cmd |= plat->cs << SFC_CMD_CS_SHIFT;

	dev_dbg(sfc->dev, "sfc addr.nbytes=%x(x%d) dummy.nbytes=%x(x%d)\n",
		op->addr.nbytes, op->addr.buswidth,
		op->dummy.nbytes, op->dummy.buswidth);
	dev_dbg(sfc->dev, "sfc ctrl=%x cmd=%x addr=%llx len=%x\n",
		ctrl, cmd, op->addr.val, len);

	writel(ctrl, sfc->regbase + SFC_CTRL);
	writel(cmd, sfc->regbase + SFC_CMD);
	if (op->addr.nbytes)
		writel(op->addr.val, sfc->regbase + SFC_ADDR);

	return 0;
}

static int rockchip_sfc_write_fifo(struct rockchip_sfc *sfc, const u8 *buf, int len)
{
	u8 bytes = len & 0x3;
	u32 dwords;
	int tx_level;
	u32 write_words;
	u32 tmp = 0;

	dwords = len >> 2;
	while (dwords) {
		tx_level = rockchip_sfc_wait_txfifo_ready(sfc, 1000);
		if (tx_level < 0)
			return tx_level;
		write_words = min_t(u32, tx_level, dwords);
		writesl(sfc->regbase + SFC_DATA, buf, write_words);
		buf += write_words << 2;
		dwords -= write_words;
	}

	/* write the rest non word aligned bytes */
	if (bytes) {
		tx_level = rockchip_sfc_wait_txfifo_ready(sfc, 1000);
		if (tx_level < 0)
			return tx_level;
		memcpy(&tmp, buf, bytes);
		writel(tmp, sfc->regbase + SFC_DATA);
	}

	return len;
}

static int rockchip_sfc_read_fifo(struct rockchip_sfc *sfc, u8 *buf, int len)
{
	u8 bytes = len & 0x3;
	u32 dwords;
	u8 read_words;
	int rx_level;
	int tmp;

	/* word aligned access only */
	dwords = len >> 2;
	while (dwords) {
		rx_level = rockchip_sfc_wait_rxfifo_ready(sfc, 1000);
		if (rx_level < 0)
			return rx_level;
		read_words = min_t(u32, rx_level, dwords);
		readsl(sfc->regbase + SFC_DATA, buf, read_words);
		buf += read_words << 2;
		dwords -= read_words;
	}

	/* read the rest non word aligned bytes */
	if (bytes) {
		rx_level = rockchip_sfc_wait_rxfifo_ready(sfc, 1000);
		if (rx_level < 0)
			return rx_level;
		tmp = readl(sfc->regbase + SFC_DATA);
		memcpy(buf, &tmp, bytes);
	}

	return len;
}

static int rockchip_sfc_fifo_transfer_dma(struct rockchip_sfc *sfc, dma_addr_t dma_buf, size_t len)
{
	writel(0xFFFFFFFF, sfc->regbase + SFC_ICLR);
	writel((u32)dma_buf, sfc->regbase + SFC_DMA_ADDR);
	writel(SFC_DMA_TRIGGER_START, sfc->regbase + SFC_DMA_TRIGGER);

	return len;
}

static int rockchip_sfc_xfer_data_poll(struct rockchip_sfc *sfc,
				       const struct spi_mem_op *op, u32 len)
{
	dev_dbg(sfc->dev, "sfc xfer_poll len=%x\n", len);

	if (op->data.dir == SPI_MEM_DATA_OUT)
		return rockchip_sfc_write_fifo(sfc, op->data.buf.out, len);
	else
		return rockchip_sfc_read_fifo(sfc, op->data.buf.in, len);
}

static int rockchip_sfc_xfer_data_dma(struct rockchip_sfc *sfc,
				      const struct spi_mem_op *op, u32 len)
{
	struct bounce_buffer bb;
	unsigned int bb_flags;
	void *dma_buf;
	int ret;

	dev_dbg(sfc->dev, "sfc xfer_dma len=%x\n", len);

	if (op->data.dir == SPI_MEM_DATA_OUT) {
		dma_buf = (void *)op->data.buf.out;
		bb_flags = GEN_BB_READ;
	} else {
		dma_buf = (void *)op->data.buf.in;
		bb_flags = GEN_BB_WRITE;
	}

	ret = bounce_buffer_start(&bb, dma_buf, len, bb_flags);
	if (ret)
		return ret;

	ret = rockchip_sfc_fifo_transfer_dma(sfc, (dma_addr_t)bb.bounce_buffer, len);
	rockchip_sfc_wait_for_dma_finished(sfc, len * 10);
	bounce_buffer_stop(&bb);

	return ret;
}

static int rockchip_sfc_xfer_data_dma_async(struct rockchip_sfc *sfc,
					    const struct spi_mem_op *op, u32 len)
{
	void *dma_buf;

	if (op->data.dir == SPI_MEM_DATA_OUT)
		dma_buf = (void *)op->data.buf.out;
	else
		dma_buf = (void *)op->data.buf.in;

	dev_dbg(sfc->dev, "xfer_dma_async len=%x %p\n", len, dma_buf);

	flush_dcache_range((unsigned long)dma_buf,
			   (unsigned long)dma_buf + len);

	rockchip_sfc_fifo_transfer_dma(sfc, (dma_addr_t)dma_buf, len);
	sfc->last_async_size = len;

	return 0;
}

static int rockchip_sfc_xfer_done(struct rockchip_sfc *sfc, u32 timeout_us)
{
	int ret = 0;
	u32 status;

	ret = readl_poll_timeout(sfc->regbase + SFC_SR, status,
				 !(status & SFC_SR_IS_BUSY),
				 timeout_us);
	if (ret) {
		dev_err(sfc->dev, "wait sfc idle timeout\n");
		rockchip_sfc_reset(sfc);

		ret = -EIO;
	}

	return ret;
}

static int rockchip_sfc_exec_op(struct spi_slave *mem,
				const struct spi_mem_op *op)
{
	struct rockchip_sfc *sfc = dev_get_platdata(mem->dev->parent);
	u32 len = min_t(u32, op->data.nbytes, sfc->max_iosize);
	int ret;

	/* Wait for last async transfer finished */
	if (sfc->last_async_size) {
		rockchip_sfc_wait_for_dma_finished(sfc, sfc->last_async_size);
		sfc->last_async_size = 0;
	}
	rockchip_sfc_adjust_op_work((struct spi_mem_op *)op);
	rockchip_sfc_xfer_setup(sfc, mem, op, len);
	if (len) {
		if (likely(sfc->use_dma) && len >= SFC_DMA_TRANS_THRETHOLD) {
			if (mem->mode & SPI_DMA_PREPARE)
				return rockchip_sfc_xfer_data_dma_async(sfc, op, len);
			ret = rockchip_sfc_xfer_data_dma(sfc, op, len);
		} else {
			ret = rockchip_sfc_xfer_data_poll(sfc, op, len);
		}

		if (ret != len) {
			dev_err(sfc->dev, "xfer data failed ret %d dir %d\n", ret, op->data.dir);

			return -EIO;
		}
	}

	return rockchip_sfc_xfer_done(sfc, 100000);
}

static int rockchip_sfc_adjust_op_size(struct spi_slave *mem, struct spi_mem_op *op)
{
	struct rockchip_sfc *sfc = dev_get_platdata(mem->dev->parent);

	op->data.nbytes = min(op->data.nbytes, sfc->max_iosize);

	return 0;
}

#if CONFIG_IS_ENABLED(CLK)
static int rockchip_sfc_exec_op_bypass(struct rockchip_sfc *sfc,
				       struct spi_slave *mem,
				       const struct spi_mem_op *op)
{
	u32 len = min_t(u32, op->data.nbytes, sfc->max_iosize);
	u32 ret;

	rockchip_sfc_adjust_op_work((struct spi_mem_op *)op);
	rockchip_sfc_xfer_setup(sfc, mem, op, len);
	ret = rockchip_sfc_xfer_data_poll(sfc, op, len);
	if (ret != len) {
		dev_err(sfc->dev, "xfer data failed ret %d\n", ret);

		return -EIO;
	}

	return rockchip_sfc_xfer_done(sfc, 100000);
}

static void rockchip_sfc_delay_lines_tuning(struct rockchip_sfc *sfc, struct spi_slave *mem)
{
	struct spi_mem_op op = SPI_MEM_OP(SPI_MEM_OP_CMD(0x9F, 1),
						SPI_MEM_OP_NO_ADDR,
						SPI_MEM_OP_NO_DUMMY,
						SPI_MEM_OP_DATA_IN(3, NULL, 1));
	u8 id[3], id_temp[3];
	u16 cell_max = (u16)rockchip_sfc_get_max_dll_cells(sfc);
	u16 right, left = 0;
	u16 step = SFC_DLL_TRANING_STEP;
	bool dll_valid = false;

	clk_set_rate(&sfc->clk, SFC_DLL_THRESHOLD_RATE);
	op.data.buf.in = &id;
	rockchip_sfc_exec_op_bypass(sfc, mem, &op);
	if ((0xFF == id[0] && 0xFF == id[1]) ||
	    (0x00 == id[0] && 0x00 == id[1])) {
		dev_dbg(sfc->dev, "no dev, dll by pass\n");
		clk_set_rate(&sfc->clk, sfc->speed);

		return;
	}

	clk_set_rate(&sfc->clk, sfc->speed);
	op.data.buf.in = &id_temp;
	for (right = 0; right <= cell_max; right += step) {
		int ret;

		rockchip_sfc_set_delay_lines(sfc, right);
		rockchip_sfc_exec_op_bypass(sfc, mem, &op);
		dev_dbg(sfc->dev, "dll read flash id:%x %x %x\n",
			id_temp[0], id_temp[1], id_temp[2]);

		ret = memcmp(&id, &id_temp, 3);
		if (dll_valid && ret) {
			right -= step;

			break;
		}
		if (!dll_valid && !ret)
			left = right;

		if (!ret)
			dll_valid = true;

		/* Add cell_max to loop */
		if (right == cell_max)
			break;
		if (right + step > cell_max)
			right = cell_max - step;
	}

	if (dll_valid && (right - left) >= SFC_DLL_TRANING_VALID_WINDOW) {
		if (left == 0 && right < cell_max)
			sfc->dll_cells = left + (right - left) * 2 / 5;
		else
			sfc->dll_cells = left + (right - left) / 2;
	} else {
		sfc->dll_cells = 0;
	}

	if (sfc->dll_cells) {
		dev_dbg(sfc->dev, "%d %d %d dll training success in %dMHz max_cells=%u sfc_ver=%d\n",
			left, right, sfc->dll_cells, sfc->speed,
			rockchip_sfc_get_max_dll_cells(sfc), rockchip_sfc_get_version(sfc));
		rockchip_sfc_set_delay_lines(sfc, (u16)sfc->dll_cells);
	} else {
		dev_err(sfc->dev, "%d %d dll training failed in %dMHz, reduce the speed\n",
			left, right, sfc->speed);
		rockchip_sfc_set_delay_lines(sfc, 0);
		clk_set_rate(&sfc->clk, SFC_DLL_THRESHOLD_RATE);
		sfc->speed = clk_get_rate(&sfc->clk);
	}
}

#endif

static int rockchip_sfc_set_speed(struct udevice *bus, uint speed)
{
	struct rockchip_sfc *sfc = dev_get_platdata(bus);

	if (speed > sfc->max_freq)
		speed = sfc->max_freq;

	if (speed == sfc->speed)
		return 0;

#if CONFIG_IS_ENABLED(CLK)
	int ret = clk_set_rate(&sfc->clk, speed);

	if (ret < 0) {
		dev_err(sfc->dev, "set_freq=%dHz fail, check if it's the cru support level\n",
			speed);
		return ret;
	}
	sfc->speed = speed;
	if (rockchip_sfc_get_version(sfc) >= SFC_VER_4) {
		if (clk_get_rate(&sfc->clk) > SFC_DLL_THRESHOLD_RATE)
			rockchip_sfc_delay_lines_tuning(sfc, NULL);
		else
			rockchip_sfc_set_delay_lines(sfc, 0);
	}

	dev_dbg(sfc->dev, "set_freq=%dHz real_freq=%ldHz\n",
		sfc->speed, clk_get_rate(&sfc->clk));
#else
	dev_dbg(sfc->dev, "sfc failed, CLK not support\n");
#endif
	return 0;
}

static int rockchip_sfc_set_mode(struct udevice *bus, uint mode)
{
	return 0;
}

static const struct spi_controller_mem_ops rockchip_sfc_mem_ops = {
	.adjust_op_size	= rockchip_sfc_adjust_op_size,
	.exec_op	= rockchip_sfc_exec_op,
};

static const struct dm_spi_ops rockchip_sfc_ops = {
	.mem_ops	= &rockchip_sfc_mem_ops,
	.set_speed	= rockchip_sfc_set_speed,
	.set_mode	= rockchip_sfc_set_mode,
};

static const struct udevice_id rockchip_sfc_ids[] = {
	{ .compatible = "rockchip,sfc"},
	{},
};

U_BOOT_DRIVER(rockchip_sfc_driver) = {
	.name   = "rockchip_sfc",
	.id     = UCLASS_SPI,
	.of_match = rockchip_sfc_ids,
	.ops    = &rockchip_sfc_ops,
	.ofdata_to_platdata = rockchip_sfc_ofdata_to_platdata,
	.platdata_auto_alloc_size = sizeof(struct rockchip_sfc),
	.probe  = rockchip_sfc_probe,
};
