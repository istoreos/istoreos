/*
 * Copyright (C) 2011 Andes Technology Corporation
 * Macpaul Lin, Andes Technology Corporation <macpaul@andestech.com>
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

#include <asm/io.h>
#include <faraday/ftsdc010.h>

/*
 * supported mmc hosts
 * setting the number CONFIG_FTSDC010_NUMBER in your configuration file.
 */
static struct mmc ftsdc010_dev[CONFIG_FTSDC010_NUMBER];
static struct mmc_host ftsdc010_host[CONFIG_FTSDC010_NUMBER];

static struct ftsdc010_mmc *ftsdc010_get_base_mmc(int dev_index)
{
	return (struct ftsdc010_mmc *)CONFIG_FTSDC010_BASE + dev_index;
}

#ifdef DEBUG
static void ftsdc010_dump_reg(struct mmc_host *host)
{
	debug("cmd: %08x\n",		readl(&host->reg->cmd));
	debug("argu: %08x\n",		readl(&host->reg->argu));
	debug("rsp0: %08x\n",		readl(&host->reg->rsp0));
	debug("rsp1: %08x\n",		readl(&host->reg->rsp1));
	debug("rsp2: %08x\n",		readl(&host->reg->rsp2));
	debug("rsp3: %08x\n",		readl(&host->reg->rsp3));
	debug("rsp_cmd: %08x\n",	readl(&host->reg->rsp_cmd));
	debug("dcr: %08x\n",		readl(&host->reg->dcr));
	debug("dtr: %08x\n",		readl(&host->reg->dtr));
	debug("dlr: %08x\n",		readl(&host->reg->dlr));
	debug("status: %08x\n",		readl(&host->reg->status));
	debug("clr: %08x\n",		readl(&host->reg->clr));
	debug("int_mask: %08x\n",	readl(&host->reg->int_mask));
	debug("pcr: %08x\n",		readl(&host->reg->pcr));
	debug("ccr: %08x\n",		readl(&host->reg->ccr));
	debug("bwr: %08x\n",		readl(&host->reg->bwr));
	debug("dwr: %08x\n",		readl(&host->reg->dwr));
	debug("feature: %08x\n",	readl(&host->reg->feature));
	debug("rev: %08x\n",		readl(&host->reg->rev));
}
#endif

static unsigned int enable_imask(struct ftsdc010_mmc *reg, unsigned int imask)
{
	unsigned int newmask;

	newmask = readl(&reg->int_mask);
	newmask |= imask;

	writel(newmask, &reg->int_mask);

	return newmask;
}

static void ftsdc010_pio_read(struct mmc_host *host, char *buf, unsigned int size)
{
	unsigned int fifo;
	unsigned int fifo_words;
	unsigned int *ptr;
	unsigned int status;
	unsigned int retry = 0;

	/* get_data_buffer */
	ptr = (unsigned int *)buf;

	while (size) {
		status = readl(&host->reg->status);
		debug("%s: size: %08x\n", __func__, size);

		if (status & FTSDC010_STATUS_FIFO_ORUN) {

			debug("%s: FIFO OVERRUN: sta: %08x\n",
					__func__, status);

			fifo = host->fifo_len > size ?
				size : host->fifo_len;

			size -= fifo;

			fifo_words = fifo >> 2;

			while (fifo_words--)
				*ptr++ = readl(&host->reg->dwr);

			/*
			 * for adding some delays for SD card to put
			 * data into FIFO again
			 */
			udelay(4*FTSDC010_DELAY_UNIT);

#ifdef CONFIG_FTSDC010_SDIO
			/* sdio allow non-power-of-2 blksz */
			if (fifo & 3) {
				unsigned int n = fifo & 3;
				unsigned int data = readl(&host->reg->dwr);

				unsigned char *p = (unsigned char *)ptr;

				while (n--) {
					*p++ = data;
					data >>= 8;
				}
			}
#endif
		} else {
			udelay(1);
			if (++retry >= FTSDC010_PIO_RETRY) {
				debug("%s: PIO_RETRY timeout\n", __func__);
				return;
			}
		}
	}
}

static void ftsdc010_pio_write(struct mmc_host *host, const char *buf,
			unsigned int size)
{
	unsigned int fifo;
	unsigned int *ptr;
	unsigned int status;
	unsigned int retry = 0;

	/* get data buffer */
	ptr = (unsigned int *)buf;

	while (size) {
		status = readl(&host->reg->status);

		if (status & FTSDC010_STATUS_FIFO_URUN) {
			fifo = host->fifo_len > size ?
				size : host->fifo_len;

			size -= fifo;

			fifo = (fifo + 3) >> 2;

			while (fifo--) {
				writel(*ptr, &host->reg->dwr);
				ptr++;
			}
		} else {
			udelay(1);
			if (++retry >= FTSDC010_PIO_RETRY) {
				debug("%s: PIO_RETRY timeout\n", __func__);
				return;
			}
		}
	}
}

static int ftsdc010_check_rsp(struct mmc *mmc, struct mmc_cmd *cmd,
			struct mmc_data *data)
{
	struct mmc_host *host = mmc->priv;
	unsigned int sta, clear;

	sta = readl(&host->reg->status);
	debug("%s: sta: %08x cmd %d\n", __func__, sta, cmd->cmdidx);

	/* check RSP TIMEOUT or FAIL */
	if (sta & FTSDC010_STATUS_RSP_TIMEOUT) {
		/* RSP TIMEOUT */
		debug("%s: RSP timeout: sta: %08x\n", __func__, sta);

		clear |= FTSDC010_CLR_RSP_TIMEOUT;
		writel(clear, &host->reg->clr);

		return TIMEOUT;
	} else if (sta & FTSDC010_STATUS_RSP_CRC_FAIL) {
		/* clear response fail bit */
		debug("%s: RSP CRC FAIL: sta: %08x\n", __func__, sta);

		clear |= FTSDC010_CLR_RSP_CRC_FAIL;
		writel(clear, &host->reg->clr);

		return COMM_ERR;
	} else if (sta & FTSDC010_STATUS_RSP_CRC_OK) {

		/* clear response CRC OK bit */
		clear |= FTSDC010_CLR_RSP_CRC_OK;
	}

	writel(clear, &host->reg->clr);
	return 0;
}

static int ftsdc010_check_data(struct mmc *mmc, struct mmc_cmd *cmd,
			struct mmc_data *data)
{
	struct mmc_host *host = mmc->priv;
	unsigned int sta, clear;

	sta = readl(&host->reg->status);
	debug("%s: sta: %08x cmd %d\n", __func__, sta, cmd->cmdidx);

	/* check DATA TIMEOUT or FAIL */
	if (data) {

		/* Transfer Complete */
		if (sta & FTSDC010_STATUS_DATA_END)
			clear |= FTSDC010_STATUS_DATA_END;

		/* Data CRC_OK */
		if (sta & FTSDC010_STATUS_DATA_CRC_OK)
			clear |= FTSDC010_STATUS_DATA_CRC_OK;

		/* DATA TIMEOUT or DATA CRC FAIL */
		if (sta & FTSDC010_STATUS_DATA_TIMEOUT) {
			/* DATA TIMEOUT */
			debug("%s: DATA TIMEOUT: sta: %08x\n", __func__, sta);

			clear |= FTSDC010_STATUS_DATA_TIMEOUT;
			writel(clear, &host->reg->clr);

			return TIMEOUT;
		} else if (sta & FTSDC010_STATUS_DATA_CRC_FAIL) {
			/* DATA CRC FAIL */
			debug("%s: DATA CRC FAIL: sta: %08x\n", __func__, sta);

			clear |= FTSDC010_STATUS_DATA_CRC_FAIL;
			writel(clear, &host->reg->clr);

			return COMM_ERR;
		}
		writel(clear, &host->reg->clr);
	}
	return 0;
}

static int ftsdc010_send_cmd(struct mmc *mmc, struct mmc_cmd *cmd,
			struct mmc_data *data)
{
	struct mmc_host *host = mmc->priv;

#ifdef CONFIG_FTSDC010_SDIO
	unsigned int scon;
#endif
	unsigned int ccon;
	unsigned int mask, tmpmask;
	unsigned int ret;
	unsigned int sta, i;

	ret = 0;

	if (data)
		mask = FTSDC010_INT_MASK_RSP_TIMEOUT;
	else if (cmd->flags & MMC_RSP_PRESENT)
		mask = FTSDC010_INT_MASK_RSP_TIMEOUT;
	else
		mask = FTSDC010_INT_MASK_CMD_SEND;

	/* write argu reg */
	debug("%s: argu: %08x\n", __func__, host->reg->argu);
	writel(cmd->cmdarg, &host->reg->argu);

	/* setup commnad */
	ccon = FTSDC010_CMD_IDX(cmd->cmdidx);

	/* setup command flags */
	ccon |= FTSDC010_CMD_CMD_EN;

	/*
	 * This hardware didn't support specific commands for mapping
	 * MMC_RSP_BUSY and MMC_RSP_OPCODE. Hence we don't deal with it.
	 */
	if (cmd->flags & MMC_RSP_PRESENT) {
		ccon |= FTSDC010_CMD_NEED_RSP;
		mask |= FTSDC010_INT_MASK_RSP_CRC_OK |
			FTSDC010_INT_MASK_RSP_CRC_FAIL;
	}

	if (cmd->flags & MMC_RSP_136)
		ccon |= FTSDC010_CMD_LONG_RSP;

	/* In Linux driver, MMC_CMD_APP_CMD is checked in last_opcode */
	if (host->last_opcode == MMC_CMD_APP_CMD)
		ccon |= FTSDC010_CMD_APP_CMD;

#ifdef CONFIG_FTSDC010_SDIO
	scon = readl(&host->reg->sdio_ctrl1);
	if (host->card_type == MMC_TYPE_SDIO)
		scon |= FTSDC010_SDIO_CTRL1_SDIO_ENABLE;
	else
		scon &= ~FTSDC010_SDIO_CTRL1_SDIO_ENABLE;
	writel(scon, &host->reg->sdio_ctrl1);
#endif

	/* record last opcode for specifing the command type to hardware */
	host->last_opcode = cmd->cmdidx;

	/* write int_mask reg */
	tmpmask = readl(&host->reg->int_mask);
	tmpmask |= mask;
	writel(tmpmask, &host->reg->int_mask);

	/* write cmd reg */
	debug("%s: ccon: %08x\n", __func__, ccon);
	writel(ccon, &host->reg->cmd);

	/* check CMD_SEND */
	for (i = 0; i < FTSDC010_CMD_RETRY; i++) {
		/*
		 * If we read status register too fast
		 * will lead hardware error and the RSP_TIMEOUT
		 * flag will be raised incorrectly.
		 */
		udelay(16*FTSDC010_DELAY_UNIT);
		sta = readl(&host->reg->status);

		/* Command Complete */
		/*
		 * Note:
		 *	Do not clear FTSDC010_CLR_CMD_SEND flag.
		 *	(by writing FTSDC010_CLR_CMD_SEND bit to clear register)
		 *	It will make the driver becomes very slow.
		 *	If the operation hasn't been finished, hardware will
		 *	clear this bit automatically.
		 *	In origin, the driver will clear this flag if there is
		 *	no data need to be read.
		 */
		if (sta & FTSDC010_STATUS_CMD_SEND)
			break;
	}

	if (i > FTSDC010_CMD_RETRY) {
		printf("%s: send command timeout\n", __func__);
		return TIMEOUT;
	}

	/* check rsp status */
	ret = ftsdc010_check_rsp(mmc, cmd, data);
	if (ret)
		return ret;

	/* read response if we have RSP_OK */
	if (ccon & FTSDC010_CMD_LONG_RSP) {
		cmd->resp[0] = readl(&host->reg->rsp3);
		cmd->resp[1] = readl(&host->reg->rsp2);
		cmd->resp[2] = readl(&host->reg->rsp1);
		cmd->resp[3] = readl(&host->reg->rsp0);
	} else {
		cmd->resp[0] = readl(&host->reg->rsp0);
	}

	/* read/write data */
	if (data && (data->flags & MMC_DATA_READ)) {
		ftsdc010_pio_read(host, data->dest,
				data->blocksize * data->blocks);
	} else if (data && (data->flags & MMC_DATA_WRITE)) {
		ftsdc010_pio_write(host, data->src,
				data->blocksize * data->blocks);
	}

	/* check data status */
	if (data) {
		ret = ftsdc010_check_data(mmc, cmd, data);
		if (ret)
			return ret;
	}

	udelay(FTSDC010_DELAY_UNIT);
	return ret;
}

static unsigned int cal_blksz(unsigned int blksz)
{
	unsigned int blksztwo = 0;

	while (blksz >>= 1)
		blksztwo++;

	return blksztwo;
}

static int ftsdc010_setup_data(struct mmc *mmc, struct mmc_data *data)
{
	struct mmc_host *host = mmc->priv;
	unsigned int dcon, newmask;

	/* configure data transfer paramter */
	if (!data)
		return 0;

	if (((data->blocksize - 1) & data->blocksize) != 0) {
		printf("%s: can't do non-power-of 2 sized block transfers"
			" (blksz %d)\n", __func__, data->blocksize);
		return -1;
	}

	/*
	 * We cannot deal with unaligned blocks with more than
	 * one block being transfered.
	 */
	if ((data->blocksize <= 2) && (data->blocks > 1)) {
			printf("%s: can't do non-word sized block transfers"
				" (blksz %d)\n", __func__, data->blocksize);
			return -1;
	}

	/* data length */
	dcon = data->blocksize * data->blocks;
	writel(dcon, &host->reg->dlr);

	/* write data control */
	dcon = cal_blksz(data->blocksize);

	/* add to IMASK register */
	newmask = (FTSDC010_STATUS_RSP_CRC_FAIL | FTSDC010_STATUS_DATA_TIMEOUT);

	/*
	 * enable UNDERRUN will trigger interrupt immediatedly
	 * So setup it when rsp is received successfully
	 */
	if (data->flags & MMC_DATA_WRITE) {
		dcon |= FTSDC010_DCR_DATA_WRITE;
	} else {
		dcon &= ~FTSDC010_DCR_DATA_WRITE;
		newmask |= FTSDC010_STATUS_FIFO_ORUN;
	}
	enable_imask(host->reg, newmask);

#ifdef CONFIG_FTSDC010_SDIO
	/* always reset fifo since last transfer may fail */
	dcon |= FTSDC010_DCR_FIFO_RST;

	if (data->blocks > 1)
		dcon |= FTSDC010_SDIO_CTRL1_SDIO_BLK_MODE;
#endif

	/* enable data transfer which will be pended until cmd is send */
	dcon |= FTSDC010_DCR_DATA_EN;
	writel(dcon, &host->reg->dcr);

	return 0;
}

static int ftsdc010_send_request(struct mmc *mmc, struct mmc_cmd *cmd,
			struct mmc_data *data)
{
	int ret;

	if (data) {
		ret = ftsdc010_setup_data(mmc, data);

		if (ret) {
			printf("%s: setup data error\n", __func__);
			return -1;
		}

		if ((data->flags & MMC_DATA_BOTH_DIR) == MMC_DATA_BOTH_DIR) {
			printf("%s: data is both direction\n", __func__);
			return -1;
		}
	}

	/* Send command */
	ret = ftsdc010_send_cmd(mmc, cmd, data);
	return ret;
}

static int ftsdc010_card_detect(struct mmc *mmc)
{
	struct mmc_host *host = mmc->priv;
	unsigned int sta;

	sta = readl(&host->reg->status);
	debug("%s: card status: %08x\n", __func__, sta);

	return (sta & FTSDC010_STATUS_CARD_DETECT) ? 0 : 1;
}

static int ftsdc010_request(struct mmc *mmc, struct mmc_cmd *cmd,
			struct mmc_data *data)
{
	int ret;

	if (ftsdc010_card_detect(mmc) == 0) {
		printf("%s: no medium present\n", __func__);
		return -1;
	} else {
		ret = ftsdc010_send_request(mmc, cmd, data);
		return ret;
	}
}

static void ftsdc010_set_clk(struct mmc *mmc)
{
	struct mmc_host *host = mmc->priv;
	unsigned char clk_div;
	unsigned int real_rate;
	unsigned int clock;

	debug("%s: mmc_set_clock: %x\n", __func__, mmc->clock);
	clock = readl(&host->reg->ccr);

	if (mmc->clock == 0) {
		real_rate = 0;
		clock |= FTSDC010_CCR_CLK_DIS;
	} else {
		debug("%s, mmc->clock: %08x, origin clock: %08x\n",
			 __func__, mmc->clock, clock);

		for (clk_div = 0; clk_div <= 127; clk_div++) {
			real_rate = (CONFIG_SYS_CLK_FREQ / 2) /
					(2 * (clk_div + 1));

			if (real_rate <= mmc->clock)
				break;
		}

		debug("%s: computed real_rate: %x, clk_div: %x\n",
			 __func__, real_rate, clk_div);

		if (clk_div > 127)
			debug("%s: no match clock rate, %x\n",
				__func__, mmc->clock);

		clock = (clock & ~FTSDC010_CCR_CLK_DIV(0x7f)) |
				FTSDC010_CCR_CLK_DIV(clk_div);

		clock &= ~FTSDC010_CCR_CLK_DIS;
	}

	debug("%s, set clock: %08x\n", __func__, clock);
	writel(clock, &host->reg->ccr);
}

static void ftsdc010_set_ios(struct mmc *mmc)
{
	struct mmc_host *host = mmc->priv;
	unsigned int power;
	unsigned long val;
	unsigned int bus_width;

	debug("%s: bus_width: %x, clock: %d\n",
		__func__, mmc->bus_width, mmc->clock);

	/* set pcr: power on */
	power = readl(&host->reg->pcr);
	power |= FTSDC010_PCR_POWER_ON;
	writel(power, &host->reg->pcr);

	if (mmc->clock)
		ftsdc010_set_clk(mmc);

	/* set bwr: bus width reg */
	bus_width = readl(&host->reg->bwr);
	bus_width &= ~(FTSDC010_BWR_WIDE_8_BUS | FTSDC010_BWR_WIDE_4_BUS |
			FTSDC010_BWR_SINGLE_BUS);

	if (mmc->bus_width == 8)
		bus_width |= FTSDC010_BWR_WIDE_8_BUS;
	else if (mmc->bus_width == 4)
		bus_width |= FTSDC010_BWR_WIDE_4_BUS;
	else
		bus_width |= FTSDC010_BWR_SINGLE_BUS;

	writel(bus_width, &host->reg->bwr);

	/* set fifo depth */
	val = readl(&host->reg->feature);
	host->fifo_len = FTSDC010_FEATURE_FIFO_DEPTH(val) * 4; /* 4 bytes */

	/* set data timeout register */
	val = -1;
	writel(val, &host->reg->dtr);
}

static void ftsdc010_reset(struct mmc_host *host)
{
	unsigned int timeout;
	unsigned int sta;

	/* Do SDC_RST: Software reset for all register */
	writel(FTSDC010_CMD_SDC_RST, &host->reg->cmd);

	host->clock = 0;

	/* this hardware has no reset finish flag to read */
	/* wait 100ms maximum */
	timeout = 100;

	/* hw clears the bit when it's done */
	while (readl(&host->reg->dtr) != 0) {
		if (timeout == 0) {
			printf("%s: reset timeout error\n", __func__);
			return;
		}
		timeout--;
		udelay(10*FTSDC010_DELAY_UNIT);
	}

	sta = readl(&host->reg->status);
	if (sta & FTSDC010_STATUS_CARD_CHANGE)
		writel(FTSDC010_CLR_CARD_CHANGE, &host->reg->clr);
}

static int ftsdc010_core_init(struct mmc *mmc)
{
	struct mmc_host *host = mmc->priv;
	unsigned int mask;
	unsigned int major, minor, revision;

	/* get hardware version */
	host->version = readl(&host->reg->rev);

	major = FTSDC010_REV_MAJOR(host->version);
	minor = FTSDC010_REV_MINOR(host->version);
	revision = FTSDC010_REV_REVISION(host->version);

	printf("ftsdc010 hardware ver: %d_%d_r%d\n", major, minor, revision);

	/* Interrupt MASK register init - mask all */
	writel(0x0, &host->reg->int_mask);

	mask = FTSDC010_INT_MASK_CMD_SEND |
		FTSDC010_INT_MASK_DATA_END |
		FTSDC010_INT_MASK_CARD_CHANGE;
#ifdef CONFIG_FTSDC010_SDIO
	mask |= FTSDC010_INT_MASK_CP_READY |
		FTSDC010_INT_MASK_CP_BUF_READY |
		FTSDC010_INT_MASK_PLAIN_TEXT_READY |
		FTSDC010_INT_MASK_SDIO_IRPT;
#endif

	writel(mask, &host->reg->int_mask);

	return 0;
}

int ftsdc010_mmc_init(int dev_index)
{
	struct mmc *mmc;
	struct mmc_host *host;

	mmc = &ftsdc010_dev[dev_index];

	sprintf(mmc->name, "FTSDC010 SD/MMC");
	mmc->priv = &ftsdc010_host[dev_index];
	mmc->request = ftsdc010_request;
	mmc->set_ios = ftsdc010_set_ios;
	mmc->init = ftsdc010_core_init;
	mmc->getcd = NULL;

	mmc->voltages = MMC_VDD_32_33 | MMC_VDD_33_34;

	mmc->host_caps = MMC_MODE_4BIT | MMC_MODE_8BIT;

	mmc->f_min = CONFIG_SYS_CLK_FREQ / 2 / (2*128);
	mmc->f_max = CONFIG_SYS_CLK_FREQ / 2 / 2;

	ftsdc010_host[dev_index].clock = 0;
	ftsdc010_host[dev_index].reg = ftsdc010_get_base_mmc(dev_index);
	mmc_register(mmc);

	/* reset mmc */
	host = (struct mmc_host *)mmc->priv;
	ftsdc010_reset(host);

	return 0;
}
