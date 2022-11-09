/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#include <common.h>
#include <dm.h>
#include <reset-uclass.h>
#include <linux/io.h>

struct rockchip_reset_priv {
	void __iomem *base;
	unsigned int sf_reset_offset;
	unsigned int sf_reset_num;
};

static int rockchip_reset_request(struct reset_ctl *reset_ctl)
{
	struct rockchip_reset_priv *priv = dev_get_priv(reset_ctl->dev);

	debug("%s(reset_ctl=%p) (dev=%p, id=%lu) (sf_reset_num=%d)\n", __func__,
	      reset_ctl, reset_ctl->dev, reset_ctl->id, priv->sf_reset_num);

	if (reset_ctl->id / 16 >= priv->sf_reset_num)
		return -EINVAL;

	return 0;
}

static int rockchip_reset_free(struct reset_ctl *reset_ctl)
{
	debug("%s(reset_ctl=%p) (dev=%p, id=%lu)\n", __func__, reset_ctl,
	      reset_ctl->dev, reset_ctl->id);

	return 0;
}

static int rockchip_reset_assert(struct reset_ctl *reset_ctl)
{
	struct rockchip_reset_priv *priv = dev_get_priv(reset_ctl->dev);
	int bank =  reset_ctl->id / 16;
	int offset =  reset_ctl->id % 16;

	debug("%s(reset_ctl=%p) (dev=%p, id=%lu) (reg_addr=%p)\n", __func__,
	      reset_ctl, reset_ctl->dev, reset_ctl->id,
	      priv->base + (bank * 4));

	writel(BIT(offset) | (BIT(offset) << 16), priv->base + (bank * 4));

	return 0;
}

static int rockchip_reset_deassert(struct reset_ctl *reset_ctl)
{
	struct rockchip_reset_priv *priv = dev_get_priv(reset_ctl->dev);
	int bank =  reset_ctl->id / 16;
	int offset =  reset_ctl->id % 16;

	debug("%s(reset_ctl=%p) (dev=%p, id=%lu) (reg_addr=%p)\n", __func__,
	      reset_ctl, reset_ctl->dev, reset_ctl->id,
	      priv->base + (bank * 4));

	writel((BIT(offset) << 16), priv->base + (bank * 4));

	return 0;
}

struct reset_ops rockchip_reset_ops = {
	.request = rockchip_reset_request,
	.free = rockchip_reset_free,
	.rst_assert = rockchip_reset_assert,
	.rst_deassert = rockchip_reset_deassert,
};

static int rockchip_reset_probe(struct udevice *dev)
{
	struct rockchip_reset_priv *priv = dev_get_priv(dev);
	fdt_addr_t addr;
	fdt_size_t size;

	addr = dev_read_addr_size(dev, "reg", &size);
	if (addr == FDT_ADDR_T_NONE)
		return -EINVAL;

	if ((priv->sf_reset_offset == 0) && (priv->sf_reset_num == 0))
		return -EINVAL;

	addr += priv->sf_reset_offset;
	priv->base = ioremap(addr, size);

	debug("%s(base=%p) (sf_reset_offset=%x, sf_reset_num=%d)\n", __func__,
	      priv->base, priv->sf_reset_offset, priv->sf_reset_num);

	return 0;
}

U_BOOT_DRIVER(rockchip_reset) = {
	.name = "rockchip_reset",
	.id = UCLASS_RESET,
	.probe = rockchip_reset_probe,
	.ops = &rockchip_reset_ops,
	.priv_auto_alloc_size = sizeof(struct rockchip_reset_priv),
};
