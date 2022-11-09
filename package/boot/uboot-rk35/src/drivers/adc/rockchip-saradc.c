/*
 * (C) Copyright 2017, Fuzhou Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:	GPL-2.0+
 *
 * Rockchip SARADC driver for U-Boot
 */

#include <common.h>
#include <adc.h>
#include <clk.h>
#include <dm.h>
#include <errno.h>
#include <asm/io.h>

#define SARADC_CTRL_CHN_MASK		GENMASK(2, 0)
#define SARADC_CTRL_POWER_CTRL		BIT(3)
#define SARADC_CTRL_IRQ_ENABLE		BIT(5)
#define SARADC_CTRL_IRQ_STATUS		BIT(6)

#define SARADC_TIMEOUT			(100 * 1000)

struct rockchip_saradc_regs {
	unsigned int data;
	unsigned int stas;
	unsigned int ctrl;
	unsigned int dly_pu_soc;
};

struct rockchip_saradc_data {
	int				num_bits;
	int				num_channels;
	unsigned long			clk_rate;
};

struct rockchip_saradc_priv {
	struct rockchip_saradc_regs		*regs;
	int					active_channel;
	const struct rockchip_saradc_data	*data;
};

int rockchip_saradc_channel_data(struct udevice *dev, int channel,
				 unsigned int *data)
{
	struct rockchip_saradc_priv *priv = dev_get_priv(dev);
	struct adc_uclass_platdata *uc_pdata = dev_get_uclass_platdata(dev);

	if (channel != priv->active_channel) {
		pr_err("Requested channel is not active!");
		return -EINVAL;
	}

	if ((readl(&priv->regs->ctrl) & SARADC_CTRL_IRQ_STATUS) !=
	    SARADC_CTRL_IRQ_STATUS)
		return -EBUSY;

	/* Read value */
	*data = readl(&priv->regs->data);
	*data &= uc_pdata->data_mask;

	/* Power down adc */
	writel(0, &priv->regs->ctrl);

	return 0;
}

int rockchip_saradc_start_channel(struct udevice *dev, int channel)
{
	struct rockchip_saradc_priv *priv = dev_get_priv(dev);

	if (channel < 0 || channel >= priv->data->num_channels) {
		pr_err("Requested channel is invalid!");
		return -EINVAL;
	}

	/* 8 clock periods as delay between power up and start cmd */
	writel(8, &priv->regs->dly_pu_soc);

	/* Select the channel to be used and trigger conversion */
	writel(SARADC_CTRL_POWER_CTRL | (channel & SARADC_CTRL_CHN_MASK) |
	       SARADC_CTRL_IRQ_ENABLE, &priv->regs->ctrl);

	priv->active_channel = channel;

	return 0;
}

int rockchip_saradc_stop(struct udevice *dev)
{
	struct rockchip_saradc_priv *priv = dev_get_priv(dev);

	/* Power down adc */
	writel(0, &priv->regs->ctrl);

	priv->active_channel = -1;

	return 0;
}

int rockchip_saradc_probe(struct udevice *dev)
{
	struct rockchip_saradc_priv *priv = dev_get_priv(dev);
	struct clk clk;
	int ret;

	ret = clk_get_by_index(dev, 0, &clk);
	if (ret)
		return ret;

	ret = clk_set_rate(&clk, priv->data->clk_rate);
	if (IS_ERR_VALUE(ret))
		return ret;

	priv->active_channel = -1;

	return 0;
}

int rockchip_saradc_ofdata_to_platdata(struct udevice *dev)
{
	struct adc_uclass_platdata *uc_pdata = dev_get_uclass_platdata(dev);
	struct rockchip_saradc_priv *priv = dev_get_priv(dev);
	struct rockchip_saradc_data *data;

	data = (struct rockchip_saradc_data *)dev_get_driver_data(dev);
	priv->regs = (struct rockchip_saradc_regs *)dev_read_addr(dev);
	if (priv->regs == (struct rockchip_saradc_regs *)FDT_ADDR_T_NONE) {
		pr_err("Dev: %s - can't get address!", dev->name);
		return -ENODATA;
	}

	priv->data = data;
	uc_pdata->data_mask = (1 << priv->data->num_bits) - 1;;
	uc_pdata->data_format = ADC_DATA_FORMAT_BIN;
	uc_pdata->data_timeout_us = SARADC_TIMEOUT / 5;
	uc_pdata->channel_mask = (1 << priv->data->num_channels) - 1;

	return 0;
}

static const struct adc_ops rockchip_saradc_ops = {
	.start_channel = rockchip_saradc_start_channel,
	.channel_data = rockchip_saradc_channel_data,
	.stop = rockchip_saradc_stop,
};

static const struct rockchip_saradc_data saradc_data = {
	.num_bits = 10,
	.num_channels = 3,
	.clk_rate = 1000000,
};

static const struct rockchip_saradc_data rk3066_tsadc_data = {
	.num_bits = 12,
	.num_channels = 2,
	.clk_rate = 50000,
};

static const struct rockchip_saradc_data rk3399_saradc_data = {
	.num_bits = 10,
	.num_channels = 6,
	.clk_rate = 1000000,
};

static const struct udevice_id rockchip_saradc_ids[] = {
	{ .compatible = "rockchip,saradc",
	  .data = (ulong)&saradc_data },
	{ .compatible = "rockchip,rk3066-tsadc",
	  .data = (ulong)&rk3066_tsadc_data },
	{ .compatible = "rockchip,rk3399-saradc",
	  .data = (ulong)&rk3399_saradc_data },
	{ }
};

U_BOOT_DRIVER(rockchip_saradc) = {
	.name		= "rockchip_saradc",
	.id		= UCLASS_ADC,
	.of_match	= rockchip_saradc_ids,
	.ops		= &rockchip_saradc_ops,
	.probe		= rockchip_saradc_probe,
	.ofdata_to_platdata = rockchip_saradc_ofdata_to_platdata,
	.priv_auto_alloc_size = sizeof(struct rockchip_saradc_priv),
};
