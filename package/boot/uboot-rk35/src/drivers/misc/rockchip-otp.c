// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <asm/arch-rockchip/cpu.h>
#include <asm/io.h>
#include <command.h>
#include <dm.h>
#include <linux/bitops.h>
#include <linux/delay.h>
#include <linux/iopoll.h>
#include <misc.h>
#include <rockchip-otp.h>

struct otp_data {
	int (*init)(struct udevice *dev);
	int (*read)(struct udevice *dev, int offset, void *buf, int size);
};

static int rockchip_otp_wait_status(struct rockchip_otp_platdata *otp,
				    u32 flag)
{
	int delay = OTPC_TIMEOUT;

	while (!(readl(otp->base + OTPC_INT_STATUS) & flag)) {
		udelay(1);
		delay--;
		if (delay <= 0) {
			printf("%s: wait init status timeout\n", __func__);
			return -ETIMEDOUT;
		}
	}

	/* clean int status */
	writel(flag, otp->base + OTPC_INT_STATUS);

	return 0;
}

static int rockchip_otp_ecc_enable(struct rockchip_otp_platdata *otp,
				   bool enable)
{
	int ret = 0;

	writel(SBPI_DAP_ADDR_MASK | (SBPI_DAP_ADDR << SBPI_DAP_ADDR_SHIFT),
	       otp->base + OTPC_SBPI_CTRL);

	writel(SBPI_CMD_VALID_MASK | 0x1, otp->base + OTPC_SBPI_CMD_VALID_PRE);
	writel(SBPI_DAP_CMD_WRF | SBPI_DAP_REG_ECC,
	       otp->base + OTPC_SBPI_CMD0_OFFSET);
	if (enable)
		writel(SBPI_ECC_ENABLE, otp->base + OTPC_SBPI_CMD1_OFFSET);
	else
		writel(SBPI_ECC_DISABLE, otp->base + OTPC_SBPI_CMD1_OFFSET);

	writel(SBPI_ENABLE_MASK | SBPI_ENABLE, otp->base + OTPC_SBPI_CTRL);

	ret = rockchip_otp_wait_status(otp, OTPC_SBPI_DONE);
	if (ret < 0)
		printf("%s timeout during ecc_enable\n", __func__);

	return ret;
}

static int rockchip_px30_otp_read(struct udevice *dev, int offset,
				  void *buf, int size)
{
	struct rockchip_otp_platdata *otp = dev_get_platdata(dev);
	u8 *buffer = buf;
	int ret = 0;

	ret = rockchip_otp_ecc_enable(otp, false);
	if (ret < 0) {
		printf("%s rockchip_otp_ecc_enable err\n", __func__);
		return ret;
	}

	writel(OTPC_USE_USER | OTPC_USE_USER_MASK, otp->base + OTPC_USER_CTRL);
	udelay(5);
	while (size--) {
		writel(offset++ | OTPC_USER_ADDR_MASK,
		       otp->base + OTPC_USER_ADDR);
		writel(OTPC_USER_FSM_ENABLE | OTPC_USER_FSM_ENABLE_MASK,
		       otp->base + OTPC_USER_ENABLE);
		ret = rockchip_otp_wait_status(otp, OTPC_USER_DONE);
		if (ret < 0) {
			printf("%s timeout during read setup\n", __func__);
			goto read_end;
		}
		*buffer++ = readb(otp->base + OTPC_USER_Q);
	}

read_end:
	writel(0x0 | OTPC_USE_USER_MASK, otp->base + OTPC_USER_CTRL);

	return ret;
}

static int rk3308bs_otp_wait_status(struct rockchip_otp_platdata *otp, u32 flag)
{
	int delay = OTPC_TIMEOUT;

	while (!(readl(otp->base + OTPC_IRQ_ST) & flag)) {
		udelay(1);
		delay--;
		if (delay <= 0) {
			printf("%s: wait init status timeout\n", __func__);
			return -ETIMEDOUT;
		}
	}

	/* clean int status */
	writel(flag, otp->base + OTPC_IRQ_ST);

	return 0;
}

static int rk3308bs_otp_active(struct rockchip_otp_platdata *otp)
{
	int ret = 0;
	u32 mode;

	mode = readl(otp->base + OTPC_MODE_CTRL);

	switch (mode) {
	case OTPC_DEEP_STANDBY:
		writel(OTPC_STANDBY, otp->base + OTPC_MODE_CTRL);
		ret = rk3308bs_otp_wait_status(otp, OTPC_DP2STB_IRQ_ST);
		if (ret < 0) {
			dev_err(otp->dev, "timeout during wait dp2stb\n");
			return ret;
		}
	case OTPC_STANDBY:
		writel(OTPC_ACTIVE, otp->base + OTPC_MODE_CTRL);
		ret = rk3308bs_otp_wait_status(otp, OTPC_STB2ACT_IRQ_ST);
		if (ret < 0) {
			dev_err(otp->dev, "timeout during wait stb2act\n");
			return ret;
		}
		break;
	default:
		break;
	}

	return ret;
}

static int rk3308bs_otp_standby(struct rockchip_otp_platdata *otp)
{
	int ret = 0;
	u32 mode;

	mode = readl(otp->base + OTPC_MODE_CTRL);

	switch (mode) {
	case OTPC_ACTIVE:
		writel(OTPC_STANDBY, otp->base + OTPC_MODE_CTRL);
		ret = rk3308bs_otp_wait_status(otp, OTPC_ACT2STB_IRQ_ST);
		if (ret < 0) {
			dev_err(otp->dev, "timeout during wait act2stb\n");
			return ret;
		}
	case OTPC_STANDBY:
		writel(OTPC_DEEP_STANDBY, otp->base + OTPC_MODE_CTRL);
		ret = rk3308bs_otp_wait_status(otp, OTPC_STB2DP_IRQ_ST);
		if (ret < 0) {
			dev_err(otp->dev, "timeout during wait stb2dp\n");
			return ret;
		}
		break;
	default:
		break;
	}

	return ret;
}

static int rockchip_rk3308bs_otp_read(struct udevice *dev, int offset,
				      void *buf, int size)
{
	struct rockchip_otp_platdata *otp = dev_get_platdata(dev);
	unsigned int addr_start, addr_end, addr_offset, addr_len;
	u32 out_value;
	u8 *buffer;
	int ret = 0, i = 0;

	if (offset > RK3308BS_MAX_BYTES - 1)
		return -ENOMEM;
	if (offset + size > RK3308BS_MAX_BYTES)
		size = RK3308BS_MAX_BYTES - offset;

	ret = rk3308bs_otp_active(otp);
	if (ret)
		goto out;

	addr_start = rounddown(offset, RK3308BS_NBYTES) / RK3308BS_NBYTES;
	addr_end = roundup(offset + size, RK3308BS_NBYTES) / RK3308BS_NBYTES;
	addr_offset = offset % RK3308BS_NBYTES;
	addr_len = addr_end - addr_start;

	buffer = calloc(1, sizeof(*buffer) * addr_len * RK3308BS_NBYTES);
	if (!buffer) {
		ret = -ENOMEM;
		goto read_end;
	}

	while (addr_len--) {
		writel(OTPC_TRANS_NUM, otp->base + OTPC_REPR_RD_TRANS_NUM);
		writel(addr_start++, otp->base + OTPC_ACCESS_ADDR);
		writel(OTPC_READ_ACCESS, otp->base + OTPC_MODE_CTRL);
		ret = rk3308bs_otp_wait_status(otp, OTPC_RDM_IRQ_ST);
		if (ret < 0) {
			printf("timeout during wait rd\n");
			goto read_end;
		}
		out_value = readl(otp->base + OTPC_RD_DATA);
		memcpy(&buffer[i], &out_value, RK3308BS_NBYTES);
		i += RK3308BS_NBYTES;
	}
	memcpy(buf, buffer + addr_offset, size);

read_end:
	kfree(buffer);
	rk3308bs_otp_standby(otp);
out:
	return ret;
}

static int rockchip_rk3568_otp_read(struct udevice *dev, int offset, void *buf,
				    int size)
{
	struct rockchip_otp_platdata *otp = dev_get_platdata(dev);
	unsigned int addr_start, addr_end, addr_offset, addr_len;
	u32 out_value;
	u8 *buffer;
	int ret = 0, i = 0;

	addr_start = rounddown(offset, RK3568_NBYTES) / RK3568_NBYTES;
	addr_end = roundup(offset + size, RK3568_NBYTES) / RK3568_NBYTES;
	addr_offset = offset % RK3568_NBYTES;
	addr_len = addr_end - addr_start;

	buffer = calloc(1, sizeof(*buffer) * addr_len * RK3568_NBYTES);
	if (!buffer)
		return -ENOMEM;

	ret = rockchip_otp_ecc_enable(otp, false);
	if (ret < 0) {
		printf("%s rockchip_otp_ecc_enable err\n", __func__);
		return ret;
	}

	writel(OTPC_USE_USER | OTPC_USE_USER_MASK, otp->base + OTPC_USER_CTRL);
	udelay(5);
	while (addr_len--) {
		writel(addr_start++ | OTPC_USER_ADDR_MASK,
		       otp->base + OTPC_USER_ADDR);
		writel(OTPC_USER_FSM_ENABLE | OTPC_USER_FSM_ENABLE_MASK,
		       otp->base + OTPC_USER_ENABLE);
		ret = rockchip_otp_wait_status(otp, OTPC_USER_DONE);
		if (ret < 0) {
			printf("%s timeout during read setup\n", __func__);
			goto read_end;
		}
		out_value = readl(otp->base + OTPC_USER_Q);
		memcpy(&buffer[i], &out_value, RK3568_NBYTES);
		i += RK3568_NBYTES;
	}

	memcpy(buf, buffer + addr_offset, size);

read_end:
	writel(0x0 | OTPC_USE_USER_MASK, otp->base + OTPC_USER_CTRL);

	kfree(buffer);

	return ret;
}

static int rockchip_rk3588_otp_read(struct udevice *dev, int offset, void *buf,
				    int size)
{
	struct rockchip_otp_platdata *otp = dev_get_platdata(dev);
	unsigned int addr_start, addr_end, addr_offset, addr_len;
	int ret = 0, i = 0;
	u32 out_value, st = 0;
	u8 *buffer;

	if (offset > RK3588_MAX_BYTES - 1)
		return -ENOMEM;
	if (offset + size > RK3588_MAX_BYTES)
		size = RK3588_MAX_BYTES - offset;

	addr_start = rounddown(offset, RK3588_NBYTES) / RK3588_NBYTES;
	addr_end = roundup(offset + size, RK3588_NBYTES) / RK3588_NBYTES;
	addr_offset = offset % RK3588_NBYTES;
	addr_len = addr_end - addr_start;
	addr_start += RK3588_NO_SECURE_OFFSET;

	buffer = calloc(1, sizeof(*buffer) * addr_len * RK3588_NBYTES);
	if (!buffer)
		return -ENOMEM;

	while (addr_len--) {
		writel((addr_start << RK3588_ADDR_SHIFT) |
		       (RK3588_BURST_NUM << RK3588_BURST_SHIFT),
		       otp->base + RK3588_OTPC_AUTO_CTRL);
		writel(RK3588_AUTO_EN, otp->base + RK3588_OTPC_AUTO_EN);
		ret = readl_poll_timeout(otp->base + RK3588_OTPC_INT_ST, st,
					 st & RK3588_RD_DONE, OTPC_TIMEOUT);
		if (ret < 0) {
			printf("%s timeout during read setup\n", __func__);
			goto read_end;
		}
		writel(RK3588_RD_DONE, otp->base + RK3588_OTPC_INT_ST);

		out_value = readl(otp->base + RK3588_OTPC_DOUT0);
		memcpy(&buffer[i], &out_value, RK3588_NBYTES);
		i += RK3588_NBYTES;
		addr_start++;
	}

	memcpy(buf, buffer + addr_offset, size);

read_end:
	kfree(buffer);

	return ret;
}

static int rockchip_rv1126_otp_init(struct udevice *dev)
{
	struct rockchip_otp_platdata *otp = dev_get_platdata(dev);
	u32 status = 0;
	int ret;

	writel(0x0, otp->base + RV1126_OTP_NVM_CEB);
	ret = readl_poll_timeout(otp->base + RV1126_OTP_NVM_ST, status,
				 status & 0x1, OTPC_TIMEOUT);
	if (ret < 0) {
		printf("%s timeout during set ceb\n", __func__);
		return ret;
	}

	writel(0x1, otp->base + RV1126_OTP_NVM_RSTB);
	ret = readl_poll_timeout(otp->base + RV1126_OTP_NVM_ST, status,
				 status & 0x4, OTPC_TIMEOUT);
	if (ret < 0) {
		printf("%s timeout during set rstb\n", __func__);
		return ret;
	}

	return 0;
}

static int rockchip_rv1126_otp_read(struct udevice *dev, int offset, void *buf,
				    int size)
{
	struct rockchip_otp_platdata *otp = dev_get_platdata(dev);
	u32 status = 0;
	u8 *buffer = buf;
	int ret = 0;

	while (size--) {
		writel(offset++, otp->base + RV1126_OTP_NVM_RADDR);
		writel(0x1, otp->base + RV1126_OTP_NVM_RSTART);
		ret = readl_poll_timeout(otp->base + RV1126_OTP_READ_ST,
					 status, status == 0, OTPC_TIMEOUT);
		if (ret < 0) {
			printf("%s timeout during read setup\n", __func__);
			return ret;
		}

		*buffer++ = readb(otp->base + RV1126_OTP_NVM_RDATA);
	}

	return 0;
}

static int rockchip_otp_read(struct udevice *dev, int offset,
			     void *buf, int size)
{
	struct otp_data *data;

	data = (struct otp_data *)dev_get_driver_data(dev);
	if (!data)
		return -ENOSYS;

	if (soc_is_rk3308bs() || soc_is_px30s())
		return rockchip_rk3308bs_otp_read(dev, offset, buf, size);

	return data->read(dev, offset, buf, size);
}

static const struct misc_ops rockchip_otp_ops = {
	.read = rockchip_otp_read,
};

static int rockchip_otp_ofdata_to_platdata(struct udevice *dev)
{
	struct rockchip_otp_platdata *otp = dev_get_platdata(dev);

	otp->base = dev_read_addr_ptr(dev);

	return 0;
}

static int rockchip_otp_probe(struct udevice *dev)
{
	struct otp_data *data;

	data = (struct otp_data *)dev_get_driver_data(dev);
	if (!data)
		return -EINVAL;

	if (data->init)
		return data->init(dev);

	return 0;
}

static const struct otp_data px30_data = {
	.read = rockchip_px30_otp_read,
};

static const struct otp_data rk3308bs_data = {
	.read = rockchip_rk3308bs_otp_read,
};

static const struct otp_data rk3568_data = {
	.read = rockchip_rk3568_otp_read,
};

static const struct otp_data rk3588_data = {
	.read = rockchip_rk3588_otp_read,
};

static const struct otp_data rv1126_data = {
	.init = rockchip_rv1126_otp_init,
	.read = rockchip_rv1126_otp_read,
};

static const struct udevice_id rockchip_otp_ids[] = {
	{
		.compatible = "rockchip,px30-otp",
		.data = (ulong)&px30_data,
	},
	{
		.compatible = "rockchip,px30s-otp",
		.data = (ulong)&rk3308bs_data,
	},
	{
		.compatible = "rockchip,rk3308-otp",
		.data = (ulong)&px30_data,
	},
	{
		.compatible = "rockchip,rk3308bs-otp",
		.data = (ulong)&rk3308bs_data,
	},
	{
		.compatible = "rockchip,rk3568-otp",
		.data = (ulong)&rk3568_data,
	},
	{
		.compatible = "rockchip,rk3588-otp",
		.data = (ulong)&rk3588_data,
	},
	{
		.compatible = "rockchip,rv1126-otp",
		.data = (ulong)&rv1126_data,
	},
	{}
};

U_BOOT_DRIVER(rockchip_otp) = {
	.name = "rockchip_otp",
	.id = UCLASS_MISC,
	.of_match = rockchip_otp_ids,
	.ops = &rockchip_otp_ops,
	.ofdata_to_platdata = rockchip_otp_ofdata_to_platdata,
	.platdata_auto_alloc_size = sizeof(struct rockchip_otp_platdata),
	.probe = rockchip_otp_probe,
};
