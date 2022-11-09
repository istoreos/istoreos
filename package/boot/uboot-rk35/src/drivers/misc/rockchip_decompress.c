// SPDX-License-Identifier:     GPL-2.0+
/*
 * Copyright (C) 2019 Rockchip Electronics Co., Ltd
 */
#include <common.h>
#include <asm/io.h>
#include <clk.h>
#include <dm.h>
#include <linux/bitops.h>
#include <misc.h>
#include <irq-generic.h>
#include <reset.h>

DECLARE_GLOBAL_DATA_PTR;

#define DECOM_CTRL		0x0
#define DECOM_ENR		0x4
#define DECOM_RADDR		0x8
#define DECOM_WADDR		0xc
#define DECOM_UDDSL		0x10
#define DECOM_UDDSH		0x14
#define DECOM_TXTHR		0x18
#define DECOM_RXTHR		0x1c
#define DECOM_SLEN		0x20
#define DECOM_STAT		0x24
#define DECOM_ISR		0x28
#define DECOM_IEN		0x2c
#define DECOM_AXI_STAT		0x30
#define DECOM_TSIZEL		0x34
#define DECOM_TSIZEH		0x38
#define DECOM_MGNUM		0x3c
#define DECOM_FRAME		0x40
#define DECOM_DICTID		0x44
#define DECOM_CSL		0x48
#define DECOM_CSH		0x4c
#define DECOM_LMTSL             0x50
#define DECOM_LMTSH             0x54

#define LZ4_HEAD_CSUM_CHECK_EN	BIT(1)
#define LZ4_BLOCK_CSUM_CHECK_EN	BIT(2)
#define LZ4_CONT_CSUM_CHECK_EN	BIT(3)

#define DSOLIEN			BIT(19)
#define ZDICTEIEN		BIT(18)
#define GCMEIEN			BIT(17)
#define GIDEIEN			BIT(16)
#define CCCEIEN			BIT(15)
#define BCCEIEN			BIT(14)
#define HCCEIEN			BIT(13)
#define CSEIEN			BIT(12)
#define DICTEIEN		BIT(11)
#define VNEIEN			BIT(10)
#define WNEIEN			BIT(9)
#define RDCEIEN			BIT(8)
#define WRCEIEN			BIT(7)
#define DISEIEN			BIT(6)
#define LENEIEN			BIT(5)
#define LITEIEN			BIT(4)
#define SQMEIEN			BIT(3)
#define SLCIEN			BIT(2)
#define HDEIEN			BIT(1)
#define DSIEN			BIT(0)

#define DECOM_STOP		BIT(0)
#define DECOM_COMPLETE		BIT(0)
#define DECOM_GZIP_MODE		BIT(4)
#define DECOM_ZLIB_MODE		BIT(5)
#define DECOM_DEFLATE_MODE	BIT(0)
#define DECOM_AXI_IDLE		BIT(4)
#define DECOM_LZ4_MODE		0

#define DECOM_ENABLE		0x1
#define DECOM_DISABLE		0x0

#define DECOM_IRQ		0xffff /* fixme */

#define DECOM_INT_MASK \
	(DSOLIEN | ZDICTEIEN | GCMEIEN | GIDEIEN | \
	CCCEIEN | BCCEIEN | HCCEIEN | CSEIEN | \
	DICTEIEN | VNEIEN | WNEIEN | RDCEIEN | WRCEIEN | \
	DISEIEN | LENEIEN | LITEIEN | SQMEIEN | SLCIEN | \
	HDEIEN | DSIEN)

#define DCLK_DECOM		400 * 1000 * 1000

struct rockchip_decom_priv {
	struct reset_ctl rst;
	void __iomem *base;
	bool idle_check_once;
	bool done;
	struct clk dclk;
	int cached; /* 1: access the data through dcache; 0: no dcache */
};

static int rockchip_decom_start(struct udevice *dev, void *buf)
{
	struct rockchip_decom_priv *priv = dev_get_priv(dev);
	struct decom_param *param = (struct decom_param *)buf;
	unsigned int limit_lo = param->size_dst & 0xffffffff;
	unsigned int limit_hi = param->size_dst >> 32;

#if CONFIG_IS_ENABLED(DM_RESET)
	reset_assert(&priv->rst);
	udelay(10);
	reset_deassert(&priv->rst);
#endif
	/*
	 * Purpose:
	 *    src: clean dcache to get the real compressed data from ddr.
	 *    dst: invalidate dcache.
	 *
	 * flush_dcache_all() operating on set/way is faster than
	 * flush_cache() and invalidate_dcache_range() operating
	 * on virtual address.
	 */
	if (!priv->cached)
		flush_dcache_all();

	priv->done = false;

	if (param->mode == DECOM_LZ4)
		writel(LZ4_CONT_CSUM_CHECK_EN |
		       LZ4_HEAD_CSUM_CHECK_EN |
		       LZ4_BLOCK_CSUM_CHECK_EN |
		       DECOM_LZ4_MODE,
		       priv->base + DECOM_CTRL);
	else if (param->mode == DECOM_GZIP)
		writel(DECOM_DEFLATE_MODE | DECOM_GZIP_MODE,
		       priv->base + DECOM_CTRL);
	else if (param->mode == DECOM_ZLIB)
		writel(DECOM_DEFLATE_MODE | DECOM_ZLIB_MODE,
		       priv->base + DECOM_CTRL);

	writel(param->addr_src, priv->base + DECOM_RADDR);
	writel(param->addr_dst, priv->base + DECOM_WADDR);

	writel(limit_lo, priv->base + DECOM_LMTSL);
	writel(limit_hi, priv->base + DECOM_LMTSH);

	writel(DECOM_ENABLE, priv->base + DECOM_ENR);

	priv->idle_check_once = true;

	return 0;
}

static int rockchip_decom_stop(struct udevice *dev)
{
	struct rockchip_decom_priv *priv = dev_get_priv(dev);

	writel(DECOM_DISABLE, priv->base + DECOM_ENR);

	return 0;
}

/* Caller must call this function to check if decompress done */
static int rockchip_decom_done_poll(struct udevice *dev)
{
	struct rockchip_decom_priv *priv = dev_get_priv(dev);

	/*
	 * Test the decom is idle first time.
	 */
	if (!priv->idle_check_once)
		return !(readl(priv->base + DECOM_AXI_STAT) & DECOM_AXI_IDLE);

	return !(readl(priv->base + DECOM_STAT) & DECOM_COMPLETE);
}

static int rockchip_decom_capability(u32 *buf)
{
	*buf = DECOM_GZIP | DECOM_LZ4;

	return 0;
}

static int rockchip_decom_data_size(struct udevice *dev, u64 *buf)
{
	struct rockchip_decom_priv *priv = dev_get_priv(dev);
	struct decom_param *param = (struct decom_param *)buf;
	u32 sizel, sizeh;

	sizel = readl(priv->base + DECOM_TSIZEL);
	sizeh = readl(priv->base + DECOM_TSIZEH);
	param->size_dst = sizel | ((u64)sizeh << 32);

	return 0;
}

/* Caller must fill in param @buf which represent struct decom_param */
static int rockchip_decom_ioctl(struct udevice *dev, unsigned long request,
				void *buf)
{
	int ret = -EINVAL;

	switch (request) {
	case IOCTL_REQ_START:
		ret = rockchip_decom_start(dev, buf);
		break;
	case IOCTL_REQ_POLL:
		ret = rockchip_decom_done_poll(dev);
		break;
	case IOCTL_REQ_STOP:
		ret = rockchip_decom_stop(dev);
		break;
	case IOCTL_REQ_CAPABILITY:
		ret = rockchip_decom_capability(buf);
		break;
	case IOCTL_REQ_DATA_SIZE:
		ret = rockchip_decom_data_size(dev, buf);
		break;
	default:
		printf("Unsupported ioctl: %ld\n", (ulong)request);
		break;
	}

	return ret;
}

static const struct misc_ops rockchip_decom_ops = {
	.ioctl = rockchip_decom_ioctl,
};

static int rockchip_decom_ofdata_to_platdata(struct udevice *dev)
{
	struct rockchip_decom_priv *priv = dev_get_priv(dev);

	priv->base = dev_read_addr_ptr(dev);
	if (!priv->base)
		return -ENOENT;

	priv->cached = dev_read_u32_default(dev, "data-cached", 0);

	return 0;
}

static int rockchip_decom_probe(struct udevice *dev)
{
	struct rockchip_decom_priv *priv = dev_get_priv(dev);
	int ret;

#if CONFIG_IS_ENABLED(DM_RESET)
	ret = reset_get_by_name(dev, "dresetn", &priv->rst);
	if (ret) {
		debug("reset_get_by_name() failed: %d\n", ret);
		return ret;
	}
#endif

	ret = clk_get_by_index(dev, 1, &priv->dclk);
	if (ret < 0)
		return ret;

	ret = clk_set_rate(&priv->dclk, DCLK_DECOM);
	if (ret < 0)
		return ret;

	return 0;
}

static const struct udevice_id rockchip_decom_ids[] = {
	{ .compatible = "rockchip,hw-decompress" },
	{}
};

U_BOOT_DRIVER(rockchip_hw_decompress) = {
	.name = "rockchip_hw_decompress",
	.id = UCLASS_MISC,
	.of_match = rockchip_decom_ids,
	.probe = rockchip_decom_probe,
	.ofdata_to_platdata = rockchip_decom_ofdata_to_platdata,
	.priv_auto_alloc_size = sizeof(struct rockchip_decom_priv),
	.ops = &rockchip_decom_ops,
};
