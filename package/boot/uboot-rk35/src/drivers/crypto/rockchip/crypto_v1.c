// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <clk.h>
#include <crypto.h>
#include <dm.h>
#include <reset.h>
#include <rockchip/crypto_hash_cache.h>
#include <rockchip/crypto_v1.h>
#include <asm/io.h>
#include <asm/arch-rockchip/hardware.h>
#include <asm/arch-rockchip/clock.h>

#define CRYPTO_V1_DEFAULT_RATE		100000000
/* crypto timeout 500ms, must support more than 32M data per times*/
#define HASH_UPDATE_LIMIT	(32 * 1024 * 1024)
#define RK_CRYPTO_TIME_OUT	500000

#define LLI_ADDR_ALIGN_SIZE	8
#define DATA_ADDR_ALIGN_SIZE	8
#define DATA_LEN_ALIGN_SIZE	64

struct rockchip_crypto_priv {
	struct crypto_hash_cache	*hash_cache;
	struct rk_crypto_reg		*reg;
	struct clk			clk;
	struct reset_ctl_bulk		rsts;
	sha_context			*ctx;
	u32				frequency;
	char				*clocks;
	u32				nclocks;
	u32				length;
};

static u32 rockchip_crypto_capability(struct udevice *dev)
{
	return CRYPTO_MD5 |
	       CRYPTO_SHA1 |
	       CRYPTO_SHA256 |
	       CRYPTO_RSA512 |
	       CRYPTO_RSA1024 |
	       CRYPTO_RSA2048;
}

static int rk_hash_direct_calc(void *hw_data, const u8 *data,
			       u32 data_len, u8 *started_flag, u8 is_last)
{
	struct rockchip_crypto_priv *priv = hw_data;
	struct rk_crypto_reg *reg = priv->reg;

	if (!data_len)
		return -EINVAL;

	/* Must flush dcache before crypto DMA fetch data region */
	crypto_flush_cacheline((ulong)data, data_len);

	/* Hash Done Interrupt */
	writel(HASH_DONE_INT, &reg->crypto_intsts);

	/* Set data base and length */
	writel((u32)(ulong)data, &reg->crypto_hrdmas);
	writel((data_len + 3) >> 2, &reg->crypto_hrdmal);

	/* Write 1 to start. When finishes, the core will clear it */
	rk_setreg(&reg->crypto_ctrl, HASH_START);

	/* Wait last complete */
	do {} while (readl(&reg->crypto_ctrl) & HASH_START);

	priv->length += data_len;

	return 0;
}

static int rockchip_crypto_sha_init(struct udevice *dev, sha_context *ctx)
{
	struct rockchip_crypto_priv *priv = dev_get_priv(dev);
	struct rk_crypto_reg *reg = priv->reg;
	u32 val;

	if (!ctx)
		return -EINVAL;

	if (!ctx->length) {
		printf("Crypto-v1: require data total length for sha init\n");
		return -EINVAL;
	}

	priv->hash_cache = crypto_hash_cache_alloc(rk_hash_direct_calc,
						   priv, ctx->length,
						   DATA_ADDR_ALIGN_SIZE,
						   DATA_LEN_ALIGN_SIZE);
	if (!priv->hash_cache)
		return -EFAULT;

	priv->ctx = ctx;
	priv->length = 0;
	writel(ctx->length, &reg->crypto_hash_msg_len);
	if (ctx->algo == CRYPTO_SHA256) {
		/* Set SHA256 mode and out byte swap */
		writel(HASH_SWAP_DO | ENGINE_SELECTION_SHA256,
		       &reg->crypto_hash_ctrl);

		val = readl(&reg->crypto_conf);
		val &= ~BYTESWAP_HRFIFO;
		writel(val, &reg->crypto_conf);
	} else if (ctx->algo == CRYPTO_SHA1) {
		/* Set SHA160 input byte swap */
		val = readl(&reg->crypto_conf);
		val |= BYTESWAP_HRFIFO;
		writel(val, &reg->crypto_conf);

		/* Set SHA160 mode and out byte swap */
		writel(HASH_SWAP_DO, &reg->crypto_hash_ctrl);
	} else if (ctx->algo == CRYPTO_MD5) {
		/* Set MD5 input byte swap */
		val = readl(&reg->crypto_conf);
		val |= BYTESWAP_HRFIFO;
		writel(val, &reg->crypto_conf);

		/* Set MD5 mode and out byte swap */
		writel(HASH_SWAP_DO | ENGINE_SELECTION_MD5,
		       &reg->crypto_hash_ctrl);
	} else {
		return -EINVAL;
	}

	rk_setreg(&reg->crypto_ctrl, HASH_FLUSH);
	do {} while (readl(&reg->crypto_ctrl) & HASH_FLUSH);

	/* SHA256 needs input byte swap */
	if (ctx->algo == CRYPTO_SHA256) {
		val = readl(&reg->crypto_conf);
		val |= BYTESWAP_HRFIFO;
		writel(val, &reg->crypto_conf);
	}

	return 0;
}

static int rockchip_crypto_sha_update(struct udevice *dev,
				      u32 *input, u32 len)
{
	struct rockchip_crypto_priv *priv = dev_get_priv(dev);
	int ret = -EINVAL, i;
	u8 *p;

	if (!input || !len)
		goto exit;

	p = (u8 *)input;

	for (i = 0; i < len / HASH_UPDATE_LIMIT; i++, p += HASH_UPDATE_LIMIT) {
		ret = crypto_hash_update_with_cache(priv->hash_cache, p,
						    HASH_UPDATE_LIMIT);
		if (ret)
			goto exit;
	}

	if (len % HASH_UPDATE_LIMIT)
		ret = crypto_hash_update_with_cache(priv->hash_cache, p,
						    len % HASH_UPDATE_LIMIT);

exit:
	if (ret) {
		crypto_hash_cache_free(priv->hash_cache);
		priv->hash_cache = NULL;
	}

	return ret;
}

static int rockchip_crypto_sha_final(struct udevice *dev,
				     sha_context *ctx, u8 *output)
{
	struct rockchip_crypto_priv *priv = dev_get_priv(dev);
	struct rk_crypto_reg *reg = priv->reg;
	u32 *buf = (u32 *)output;
	int ret = 0;
	u32 nbits;
	int i;

	if (priv->length != ctx->length) {
		printf("total length(0x%08x) != init length(0x%08x)!\n",
		       priv->length, ctx->length);
		ret = -EIO;
		goto exit;
	}

	/* Wait last complete */
	do {} while (readl(&reg->crypto_ctrl) & HASH_START);

	/* It is high when finish, and it will not be low until it restart */
	do {} while (!readl(&reg->crypto_hash_sts));

	/* Read hash data, per-data 32-bit */
	nbits = crypto_algo_nbits(ctx->algo);
	for (i = 0; i < BITS2WORD(nbits); i++)
		buf[i] = readl(&reg->crypto_hash_dout[i]);

exit:
	crypto_hash_cache_free(priv->hash_cache);
	priv->hash_cache = NULL;
	return ret;
}

#if CONFIG_IS_ENABLED(ROCKCHIP_RSA)
static int rockchip_crypto_rsa_verify(struct udevice *dev, rsa_key *ctx,
				      u8 *sign, u8 *output)
{
	struct rockchip_crypto_priv *priv = dev_get_priv(dev);
	struct rk_crypto_reg *reg = priv->reg;
	u32 nbits, *buf = (u32 *)output;
	int i, value;

	if (!ctx)
		return -EINVAL;

	if (ctx->algo == CRYPTO_RSA512)
		value = PKA_BLOCK_SIZE_512;
	else if (ctx->algo == CRYPTO_RSA1024)
		value = PKA_BLOCK_SIZE_1024;
	else if (ctx->algo == CRYPTO_RSA2048)
		value = PKA_BLOCK_SIZE_2048;
	else
		return -EINVAL;

	if (priv->rsts.resets && priv->rsts.count) {
		reset_assert_bulk(&priv->rsts);
		udelay(10);
		reset_deassert_bulk(&priv->rsts);
	}

	/* Specify the nbits of N in PKA calculation */
	writel(value, &reg->crypto_pka_ctrl);

	/* Flush SHA and RSA */
	rk_setreg(&reg->crypto_ctrl, PKA_HASH_CTRL);
	writel(0xffffffff, &reg->crypto_intsts);
	do {} while (readl(&reg->crypto_ctrl) & PKA_CTRL);

	/* Clean PKA done interrupt */
	writel(PKA_DONE_INT, &reg->crypto_intsts);

	/* Set m/n/e/c */
	nbits = crypto_algo_nbits(ctx->algo);
	memcpy((void *)&reg->crypto_pka_m, (void *)sign,   BITS2BYTE(nbits));
	memcpy((void *)&reg->crypto_pka_n, (void *)ctx->n, BITS2BYTE(nbits));
	memcpy((void *)&reg->crypto_pka_e, (void *)ctx->e, BITS2BYTE(nbits));
	memcpy((void *)&reg->crypto_pka_c, (void *)ctx->c, BITS2BYTE(nbits));
	do {} while (readl(&reg->crypto_ctrl) & PKA_START);

	/* Start PKA */
	rk_setreg(&reg->crypto_ctrl, PKA_START);

	/* Wait PKA done */
	do {} while (readl(&reg->crypto_ctrl) & PKA_START);

	/* Read hash data, per-data 32-bit */
	for (i = 0; i < BITS2WORD(nbits); i++)
		buf[i] = readl(&reg->crypto_pka_m[i]);

	return 0;
}
#else
static int rockchip_crypto_rsa_verify(struct udevice *dev, rsa_key *ctx,
				      u8 *sign, u8 *output)
{
	return -ENOSYS;
}
#endif
static const struct dm_crypto_ops rockchip_crypto_ops = {
	.capability = rockchip_crypto_capability,
	.sha_init   = rockchip_crypto_sha_init,
	.sha_update = rockchip_crypto_sha_update,
	.sha_final  = rockchip_crypto_sha_final,
	.rsa_verify = rockchip_crypto_rsa_verify,
};

/*
 * Only use "clocks" to parse crypto clock id and use rockchip_get_clk().
 * Because we always add crypto node in U-Boot dts, when kernel dtb enabled :
 *
 *   1. There is cru phandle mismatch between U-Boot and kernel dtb;
 *   2. CONFIG_OF_SPL_REMOVE_PROPS removes clock property;
 */
static int rockchip_crypto_ofdata_to_platdata(struct udevice *dev)
{
	struct rockchip_crypto_priv *priv = dev_get_priv(dev);
	int len;

	if (!dev_read_prop(dev, "clocks", &len)) {
		printf("Crypto-v1: can't find \"clocks\" property\n");
		return -EINVAL;
	}

	priv->clocks = malloc(len);
	if (!priv->clocks)
		return -ENOMEM;

	priv->nclocks = len / sizeof(u32);
	if (dev_read_u32_array(dev, "clocks", (u32 *)priv->clocks,
			       priv->nclocks)) {
		printf("Crypto-v1: can't read \"clocks\" property\n");
		return -EINVAL;
	}

	priv->reg = dev_read_addr_ptr(dev);
	priv->frequency = dev_read_u32_default(dev, "clock-frequency",
					       CRYPTO_V1_DEFAULT_RATE);

	memset(&priv->rsts, 0x00, sizeof(priv->rsts));
	reset_get_bulk(dev, &priv->rsts);

	return 0;
}

static int rockchip_crypto_probe(struct udevice *dev)
{
	struct rockchip_crypto_priv *priv = dev_get_priv(dev);
	u32 *clocks;
	int i, ret;

	ret = rockchip_get_clk(&priv->clk.dev);
	if (ret) {
		printf("Crypto-v1: failed to get clk device, ret=%d\n", ret);
		return ret;
	}

	clocks = (u32 *)priv->clocks;
	for (i = 1; i < priv->nclocks; i += 2) {
		priv->clk.id = clocks[i];
		ret = clk_set_rate(&priv->clk, priv->frequency);
		if (ret < 0) {
			printf("Crypto-v1: failed to set clk(%ld): ret=%d\n",
			       priv->clk.id, ret);
			return ret;
		}
	}

	return 0;
}

static const struct udevice_id rockchip_crypto_ids[] = {
	{ .compatible = "rockchip,rk3399-crypto" },
	{ .compatible = "rockchip,rk3368-crypto" },
	{ .compatible = "rockchip,rk3328-crypto" },
	{ .compatible = "rockchip,rk3288-crypto" },
	{ .compatible = "rockchip,rk322x-crypto" },
	{ .compatible = "rockchip,rk312x-crypto" },
	{ }
};

U_BOOT_DRIVER(rockchip_crypto_v1) = {
	.name		= "rockchip_crypto_v1",
	.id		= UCLASS_CRYPTO,
	.of_match	= rockchip_crypto_ids,
	.ops		= &rockchip_crypto_ops,
	.probe		= rockchip_crypto_probe,
	.ofdata_to_platdata = rockchip_crypto_ofdata_to_platdata,
	.priv_auto_alloc_size = sizeof(struct rockchip_crypto_priv),
};
