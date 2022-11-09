// SPDX-License-Identifier:     GPL-2.0+
/*
 * (C) Copyright 2021, Rockchip Electronics Co., Ltd
 *
 * Rockchip SARADC driver for U-Boot
 */

#include <common.h>
#include <adc.h>
#include <clk.h>
#include <dm.h>
#include <errno.h>
#include <asm/io.h>
#include <reset.h>

#define SARADC2_EN_END_INT		BIT(0)
#define SARADC2_START			BIT(4)
#define SARADC2_SINGLE_MODE		BIT(5)

#define SARADC_TIMEOUT			(100 * 1000)

struct rockchip_saradc_regs {
	u32 conv_con;
	u32 t_pd_soc;
	u32 t_as_soc;
	u32 t_das_soc;
	u32 t_sel_soc;
	u32 high_comp0;
	u32 high_comp1;
	u32 high_comp2;
	u32 high_comp3;
	u32 high_comp4;
	u32 high_comp5;
	u32 reserved0044;
	u32 high_comp7;
	u32 high_comp8;
	u32 high_comp9;
	u32 high_comp10;
	u32 high_comp11;
	u32 high_comp12;
	u32 high_comp13;
	u32 high_comp14;
	u32 high_comp15;
	u32 low_comp0;
	u32 low_comp1;
	u32 low_comp2;
	u32 low_comp3;
	u32 low_comp4;
	u32 low_comp5;
	u32 low_comp6;
	u32 low_comp7;
	u32 low_comp8;
	u32 low_comp9;
	u32 low_comp10;
	u32 low_comp11;
	u32 low_comp12;
	u32 low_comp13;
	u32 low_comp14;
	u32 low_comp15;
	u32 debounce;
	u32 ht_int_en;
	u32 lt_int_en;
	u32 reserved0160[24];
	u32 mt_int_en;
	u32 end_int_en;
	u32 st_con;
	u32 status;
	u32 end_int_st;
	u32 ht_int_st;
	u32 lt_int_st;
	u32 mt_int_st;
	u32 data0;
	u32 data1;
	u32 data2;
	u32 data3;
	u32 data4;
	u32 data5;
	u32 data6;
	u32 data7;
	u32 data8;
	u32 data9;
	u32 data10;
	u32 data11;
	u32 data12;
	u32 data13;
	u32 data14;
	u32 data15;
	u32 auto_ch_en;
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
	struct reset_ctl			rst;
};

static int rockchip_saradc_channel_data(struct udevice *dev, int channel,
					unsigned int *data)
{
	struct rockchip_saradc_priv *priv = dev_get_priv(dev);
	struct adc_uclass_platdata *uc_pdata = dev_get_uclass_platdata(dev);

	if (channel != priv->active_channel) {
		pr_err("Requested channel is not active!");
		return -EINVAL;
	}

	/* Clear irq */
	writel(0x1, &priv->regs->end_int_st);

	*data = readl(&priv->regs->data0 + priv->active_channel);
	*data &= uc_pdata->data_mask;

	return 0;
}

static int rockchip_saradc_start_channel(struct udevice *dev, int channel)
{
	struct rockchip_saradc_priv *priv = dev_get_priv(dev);
	int val;

	if (channel < 0 || channel >= priv->data->num_channels) {
		pr_err("Requested channel is invalid!");
		return -EINVAL;
	}

#if CONFIG_IS_ENABLED(DM_RESET)
	reset_assert(&priv->rst);
	udelay(10);
	reset_deassert(&priv->rst);
#endif
	writel(0x20, &priv->regs->t_pd_soc);
	writel(0xc, &priv->regs->t_das_soc);
	val = SARADC2_EN_END_INT << 16 | SARADC2_EN_END_INT;
	writel(val, &priv->regs->end_int_en);
	val = SARADC2_START | SARADC2_SINGLE_MODE | channel;
	writel(val << 16 | val, &priv->regs->conv_con);

	udelay(100);

	priv->active_channel = channel;

	return 0;
}

static int rockchip_saradc_stop(struct udevice *dev)
{
	struct rockchip_saradc_priv *priv = dev_get_priv(dev);

	priv->active_channel = -1;

	return 0;
}

static int rockchip_saradc_probe(struct udevice *dev)
{
	struct rockchip_saradc_priv *priv = dev_get_priv(dev);
	struct clk clk;
	int ret;

#if CONFIG_IS_ENABLED(DM_RESET)
	ret = reset_get_by_name(dev, "saradc-apb", &priv->rst);
	if (ret) {
		debug("reset_get_by_name() failed: %d\n", ret);
		return ret;
	}
#endif

	ret = clk_get_by_index(dev, 0, &clk);
	if (ret)
		return ret;

	ret = clk_set_rate(&clk, priv->data->clk_rate);
	if (IS_ERR_VALUE(ret))
		return ret;

	priv->active_channel = -1;

	return 0;
}

static int rockchip_saradc_ofdata_to_platdata(struct udevice *dev)
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
	uc_pdata->data_mask = (1 << priv->data->num_bits) - 1;
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

static const struct rockchip_saradc_data rk3588_saradc_data = {
	.num_bits = 12,
	.num_channels = 8,
	.clk_rate = 1000000,
};

static const struct udevice_id rockchip_saradc_ids[] = {
	{ .compatible = "rockchip,rk3588-saradc",
	  .data = (ulong)&rk3588_saradc_data },
	{ }
};

U_BOOT_DRIVER(rockchip_saradc_v2) = {
	.name		= "rockchip_saradc_v2",
	.id		= UCLASS_ADC,
	.of_match	= rockchip_saradc_ids,
	.ops		= &rockchip_saradc_ops,
	.probe		= rockchip_saradc_probe,
	.ofdata_to_platdata = rockchip_saradc_ofdata_to_platdata,
	.priv_auto_alloc_size = sizeof(struct rockchip_saradc_priv),
};
