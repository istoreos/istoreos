// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2018 Texas Instruments Incorporated - http://www.ti.com/
 */

#include <spi.h>
#include <spi-mem.h>

int spi_mem_exec_op(struct spi_slave *slave,
		    const struct spi_mem_op *op)
{
	unsigned int pos = 0;
	const u8 *tx_buf = NULL;
	u8 *rx_buf = NULL;
	u8 *op_buf;
	int op_len;
	u32 flag;
	int ret;
	int i;

	if (op->data.nbytes) {
		if (op->data.dir == SPI_MEM_DATA_IN)
			rx_buf = op->data.buf.in;
		else
			tx_buf = op->data.buf.out;
	}

	op_len = sizeof(op->cmd.opcode) + op->addr.nbytes + op->dummy.nbytes;
	op_buf = calloc(1, op_len);

	ret = spi_claim_bus(slave);
	if (ret < 0)
		return ret;

	op_buf[pos++] = op->cmd.opcode;

	if (op->addr.nbytes) {
		for (i = 0; i < op->addr.nbytes; i++)
			op_buf[pos + i] = op->addr.val >>
				(8 * (op->addr.nbytes - i - 1));

		pos += op->addr.nbytes;
	}

	if (op->dummy.nbytes)
		memset(op_buf + pos, 0xff, op->dummy.nbytes);

	/* 1st transfer: opcode + address + dummy cycles */
	flag = SPI_XFER_BEGIN;
	/* Make sure to set END bit if no tx or rx data messages follow */
	if (!tx_buf && !rx_buf)
		flag |= SPI_XFER_END;

	ret = spi_xfer(slave, op_len * 8, op_buf, NULL, flag);
	if (ret)
		return ret;

	/* 2nd transfer: rx or tx data path */
	if (tx_buf || rx_buf) {
		ret = spi_xfer(slave, op->data.nbytes * 8, tx_buf,
			       rx_buf, SPI_XFER_END);
		if (ret)
			return ret;
	}

	spi_release_bus(slave);

	for (i = 0; i < pos; i++)
		debug("%02x ", op_buf[i]);
	debug("| [%dB %s] ",
	      tx_buf || rx_buf ? op->data.nbytes : 0,
	      tx_buf || rx_buf ? (tx_buf ? "out" : "in") : "-");
	for (i = 0; i < op->data.nbytes; i++)
		debug("%02x ", tx_buf ? tx_buf[i] : rx_buf[i]);
	debug("[ret %d]\n", ret);

	free(op_buf);

	if (ret < 0)
		return ret;

	return 0;
}

int spi_mem_adjust_op_size(struct spi_slave *slave,
			   struct spi_mem_op *op)
{
	unsigned int len;

	len = sizeof(op->cmd.opcode) + op->addr.nbytes + op->dummy.nbytes;
	if (slave->max_write_size && len > slave->max_write_size)
		return -EINVAL;

	if (op->data.dir == SPI_MEM_DATA_IN && slave->max_read_size)
		op->data.nbytes = min(op->data.nbytes,
				      slave->max_read_size);
	else if (slave->max_write_size)
		op->data.nbytes = min(op->data.nbytes,
				      slave->max_write_size - len);

	if (!op->data.nbytes)
		return -EINVAL;

	return 0;
}
