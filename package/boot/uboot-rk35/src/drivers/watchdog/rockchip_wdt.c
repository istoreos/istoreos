/*
 * Copyright (C) 2019 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <asm/io.h>
#include <asm/utils.h>
#include <clk.h>
#include <dm.h>
#include <reset.h>
#include <wdt.h>

#define WDT_CR			0x00
#define WDT_TORR		0x04
#define WDT_CRR			0x0C
#define WDT_EN_MASK		0x01
#define WDT_MODE_MASK		0x02
#define WDT_CRR_RESTART_VAL	0x76

DECLARE_GLOBAL_DATA_PTR;

struct rockchip_wdt_priv {
	void __iomem *base;
	struct clk clk;
	unsigned long rate;
	struct reset_ctl rst;
};

/*
 * Set the watchdog time interval.
 * Counter is 32 bit.
 */
static int rockchip_wdt_settimeout(u64 timeout,
				   struct rockchip_wdt_priv *priv)
{
	signed int i;

	/* calculate the timeout range value */
	i = log_2_n_round_up(timeout * priv->rate / 1000) - 16;
	if (i > 15)
		i = 15;
	if (i < 0)
		i = 0;

	writel((i | (i << 4)), priv->base + WDT_TORR);

	return 0;
}

static void rockchip_wdt_enable(struct rockchip_wdt_priv *priv)
{
	u32 val = readl(priv->base + WDT_CR);

	/* Disable interrupt mode; always perform system reset. */
	val &= ~WDT_MODE_MASK;
	/* Enable watchdog. */
	val |= WDT_EN_MASK;

	writel(val, priv->base + WDT_CR);
}

static unsigned int rockchip_wdt_is_enabled(struct rockchip_wdt_priv *priv)
{
	unsigned long val;

	val = readl(priv->base + WDT_CR);

	return val & WDT_EN_MASK;
}

static int rockchip_wdt_reset(struct udevice *dev)
{
	struct rockchip_wdt_priv *priv = dev_get_priv(dev);

	if (rockchip_wdt_is_enabled(priv))
		/* restart the watchdog counter */
		writel(WDT_CRR_RESTART_VAL, priv->base + WDT_CRR);

	return 0;
}

static int rockchip_wdt_start(struct udevice *dev, u64 timeout, ulong flags)
{
	struct rockchip_wdt_priv *priv = dev_get_priv(dev);

	printf("Rockchip watchdog timeout: %lld sec\n", timeout / 1000);

	reset_deassert(&priv->rst);

	rockchip_wdt_reset(dev);
	rockchip_wdt_settimeout(timeout, priv);
	rockchip_wdt_enable(priv);
	rockchip_wdt_reset(dev);

	return 0;
}

static int rockchip_wdt_stop(struct udevice *dev)
{
	struct rockchip_wdt_priv *priv = dev_get_priv(dev);

	reset_assert(&priv->rst);
	reset_deassert(&priv->rst);

	printf("Rockchip watchdog stop\n");

	return 0;
}

static const struct wdt_ops rockchip_wdt_ops = {
	.start = rockchip_wdt_start,
	.reset = rockchip_wdt_reset,
	.stop = rockchip_wdt_stop,
};

static int rockchip_wdt_ofdata_to_platdata(struct udevice *dev)
{
	struct rockchip_wdt_priv *priv = dev_get_priv(dev);

	priv->base = dev_read_addr_ptr(dev);
	if (!priv->base)
		return -ENOENT;

	return 0;
}

static int rockchip_wdt_probe(struct udevice *dev)
{
	struct rockchip_wdt_priv *priv = dev_get_priv(dev);
	int ret;

	ret = reset_get_by_name(dev, "reset", &priv->rst);
	if (ret) {
		pr_err("reset_get_by_name(reset) failed: %d\n", ret);
		return ret;
	}

	ret = clk_get_by_index(dev, 0, &priv->clk);
	if (ret < 0)
		return ret;

	/* Need clk framework support */
	priv->rate = clk_get_rate(&priv->clk);
	if (priv->rate < 0)
		return -EINVAL;

	return 0;
}

static const struct udevice_id rockchip_wdt_ids[] = {
	{ .compatible = "snps,dw-wdt" },
	{}
};

U_BOOT_DRIVER(rockchip_wdt) = {
	.name = "rockchip_wdt",
	.id = UCLASS_WDT,
	.of_match = rockchip_wdt_ids,
	.probe = rockchip_wdt_probe,
	.priv_auto_alloc_size = sizeof(struct rockchip_wdt_priv),
	.ofdata_to_platdata = rockchip_wdt_ofdata_to_platdata,
	.ops = &rockchip_wdt_ops,
};
