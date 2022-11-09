// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <clk.h>
#include <crypto.h>
#include <dm.h>
#include <asm/io.h>
#include <asm/arch-rockchip/hardware.h>
#include <asm/arch-rockchip/clock.h>
#include <rockchip/crypto_hash_cache.h>
#include <rockchip/crypto_v2.h>
#include <rockchip/crypto_v2_pka.h>

#define	RK_HASH_CTX_MAGIC		0x1A1A1A1A

#ifdef DEBUG
#define IMSG(format, ...) printf("[%s, %05d]-trace: " format "\n", \
				 __func__, __LINE__, ##__VA_ARGS__)
#else
#define IMSG(format, ...)
#endif

struct crypto_lli_desc {
	u32 src_addr;
	u32 src_len;
	u32 dst_addr;
	u32 dst_len;
	u32 user_define;
	u32 reserve;
	u32 dma_ctrl;
	u32 next_addr;
};

struct rk_hash_ctx {
	struct crypto_lli_desc		data_lli;	/* lli desc */
	struct crypto_hash_cache	*hash_cache;
	u32				magic;		/* to check ctx */
	u32				algo;		/* hash algo */
	u8				digest_size;	/* hash out length */
	u8				reserved[3];
};

struct rk_crypto_soc_data {
	u32 capability;
	u32 (*dynamic_cap)(void);
};

struct rockchip_crypto_priv {
	fdt_addr_t			reg;
	u32				frequency;
	char				*clocks;
	u32				*frequencies;
	u32				nclocks;
	u32				length;
	struct rk_hash_ctx		*hw_ctx;
	struct rk_crypto_soc_data	*soc_data;
};

#define LLI_ADDR_ALIGN_SIZE	8
#define DATA_ADDR_ALIGN_SIZE	8
#define DATA_LEN_ALIGN_SIZE	64

/* crypto timeout 500ms, must support more than 32M data per times*/
#define HASH_UPDATE_LIMIT	(32 * 1024 * 1024)
#define RK_CRYPTO_TIMEOUT	500000

#define RK_POLL_TIMEOUT(condition, timeout) \
({ \
	int time_out = timeout; \
	while (condition) { \
		if (--time_out <= 0) { \
			debug("[%s] %d: time out!\n", __func__,\
				__LINE__); \
			break; \
		} \
		udelay(1); \
	} \
	(time_out <= 0) ? -ETIMEDOUT : 0; \
})

#define WAIT_TAG_VALID(channel, timeout) ({ \
	u32 tag_mask = CRYPTO_CH0_TAG_VALID << (channel);\
	int ret;\
	ret = RK_POLL_TIMEOUT(!(crypto_read(CRYPTO_TAG_VALID) & tag_mask),\
			      timeout);\
	crypto_write(crypto_read(CRYPTO_TAG_VALID) & tag_mask, CRYPTO_TAG_VALID);\
	ret;\
})

#define virt_to_phys(addr)		(((unsigned long)addr) & 0xffffffff)
#define phys_to_virt(addr, area)	((unsigned long)addr)

#define align_malloc(bytes, alignment)	memalign(alignment, bytes)
#define align_free(addr)		do {if (addr) free(addr);} while (0)

#define ROUNDUP(size, alignment)	round_up(size, alignment)
#define cache_op_inner(type, addr, size) \
					crypto_flush_cacheline((ulong)addr, size)

#define IS_NEED_IV(rk_mode) ((rk_mode) != RK_MODE_ECB && \
			     (rk_mode) != RK_MODE_CMAC && \
			     (rk_mode) != RK_MODE_CBC_MAC)

#define IS_NEED_TAG(rk_mode) ((rk_mode) == RK_MODE_CMAC || \
			      (rk_mode) == RK_MODE_CBC_MAC || \
			      (rk_mode) == RK_MODE_CCM || \
			      (rk_mode) == RK_MODE_GCM)

#define IS_MAC_MODE(rk_mode) ((rk_mode) == RK_MODE_CMAC || \
			      (rk_mode) == RK_MODE_CBC_MAC)

#define IS_AE_MODE(rk_mode) ((rk_mode) == RK_MODE_CCM || \
			     (rk_mode) == RK_MODE_GCM)

fdt_addr_t crypto_base;

static inline void word2byte_be(u32 word, u8 *ch)
{
	ch[0] = (word >> 24) & 0xff;
	ch[1] = (word >> 16) & 0xff;
	ch[2] = (word >> 8) & 0xff;
	ch[3] = (word >> 0) & 0xff;
}

static inline u32 byte2word_be(const u8 *ch)
{
	return (*ch << 24) + (*(ch + 1) << 16) + (*(ch + 2) << 8) + *(ch + 3);
}

static inline void clear_regs(u32 base, u32 words)
{
	int i;

	/*clear out register*/
	for (i = 0; i < words; i++)
		crypto_write(0, base + 4 * i);
}

static inline void clear_hash_out_reg(void)
{
	clear_regs(CRYPTO_HASH_DOUT_0, 16);
}

static inline void clear_key_regs(void)
{
	clear_regs(CRYPTO_CH0_KEY_0, CRYPTO_KEY_CHANNEL_NUM * 4);
}

static inline void read_regs(u32 base, u8 *data, u32 data_len)
{
	u8 tmp_buf[4];
	u32 i;

	for (i = 0; i < data_len / 4; i++)
		word2byte_be(crypto_read(base + i * 4),
			     data + i * 4);

	if (data_len % 4) {
		word2byte_be(crypto_read(base + i * 4), tmp_buf);
		memcpy(data + i * 4, tmp_buf, data_len % 4);
	}
}

static inline void write_regs(u32 base, const u8 *data, u32 data_len)
{
	u8 tmp_buf[4];
	u32 i;

	for (i = 0; i < data_len / 4; i++, base += 4)
		crypto_write(byte2word_be(data + i * 4), base);

	if (data_len % 4) {
		memset(tmp_buf, 0x00, sizeof(tmp_buf));
		memcpy((u8 *)tmp_buf, data + i * 4, data_len % 4);
		crypto_write(byte2word_be(tmp_buf), base);
	}
}

static inline void write_key_reg(u32 chn, const u8 *key, u32 key_len)
{
	write_regs(CRYPTO_CH0_KEY_0 + chn * 0x10, key, key_len);
}

static inline void set_iv_reg(u32 chn, const u8 *iv, u32 iv_len)
{
	u32 base_iv;

	base_iv = CRYPTO_CH0_IV_0 + chn * 0x10;

	/* clear iv */
	clear_regs(base_iv, 4);

	if (!iv || iv_len == 0)
		return;

	write_regs(base_iv, iv, iv_len);

	crypto_write(iv_len, CRYPTO_CH0_IV_LEN_0 + 4 * chn);
}

static inline void get_iv_reg(u32 chn, u8 *iv, u32 iv_len)
{
	u32 base_iv;

	base_iv = CRYPTO_CH0_IV_0 + chn * 0x10;

	read_regs(base_iv, iv, iv_len);
}

static inline void get_tag_from_reg(u32 chn, u8 *tag, u32 tag_len)
{
	u32 i;
	u32 chn_base = CRYPTO_CH0_TAG_0 + 0x10 * chn;

	for (i = 0; i < tag_len / 4; i++, chn_base += 4)
		word2byte_be(crypto_read(chn_base), tag + 4 * i);
}

static u32 crypto_v3_dynamic_cap(void)
{
	u32 capability = 0;
	u32 ver_reg, i;
	struct cap_map {
		u32 ver_offset;
		u32 mask;
		u32 cap_bit;
	};
	const struct cap_map cap_tbl[] = {
	{CRYPTO_HASH_VERSION, CRYPTO_HASH_MD5_FLAG,    CRYPTO_MD5},
	{CRYPTO_HASH_VERSION, CRYPTO_HASH_SHA1_FLAG,   CRYPTO_SHA1},
	{CRYPTO_HASH_VERSION, CRYPTO_HASH_SHA256_FLAG, CRYPTO_SHA256},
	{CRYPTO_HASH_VERSION, CRYPTO_HASH_SHA512_FLAG, CRYPTO_SHA512},
	{CRYPTO_HASH_VERSION, CRYPTO_HASH_SM3_FLAG,    CRYPTO_SM3},

	{CRYPTO_HMAC_VERSION, CRYPTO_HMAC_MD5_FLAG,    CRYPTO_HMAC_MD5},
	{CRYPTO_HMAC_VERSION, CRYPTO_HMAC_SHA1_FLAG,   CRYPTO_HMAC_SHA1},
	{CRYPTO_HMAC_VERSION, CRYPTO_HMAC_SHA256_FLAG, CRYPTO_HMAC_SHA256},
	{CRYPTO_HMAC_VERSION, CRYPTO_HMAC_SHA512_FLAG, CRYPTO_HMAC_SHA512},
	{CRYPTO_HMAC_VERSION, CRYPTO_HMAC_SM3_FLAG,    CRYPTO_HMAC_SM3},

	{CRYPTO_AES_VERSION,  CRYPTO_AES256_FLAG,      CRYPTO_AES},
	{CRYPTO_DES_VERSION,  CRYPTO_TDES_FLAG,        CRYPTO_DES},
	{CRYPTO_SM4_VERSION,  CRYPTO_ECB_FLAG,         CRYPTO_SM4},
	};

	/* rsa */
	capability = CRYPTO_RSA512 |
		     CRYPTO_RSA1024 |
		     CRYPTO_RSA2048 |
		     CRYPTO_RSA3072 |
		     CRYPTO_RSA4096;

	for (i = 0; i < ARRAY_SIZE(cap_tbl); i++) {
		ver_reg = crypto_read(cap_tbl[i].ver_offset);

		if ((ver_reg & cap_tbl[i].mask) == cap_tbl[i].mask)
			capability |= cap_tbl[i].cap_bit;
	}

	return capability;
}

static int hw_crypto_reset(void)
{
	u32 val = 0, mask = 0;
	int ret;

	val = CRYPTO_SW_PKA_RESET | CRYPTO_SW_CC_RESET;
	mask = val << CRYPTO_WRITE_MASK_SHIFT;

	/* reset pka and crypto modules*/
	crypto_write(val | mask, CRYPTO_RST_CTL);

	/* wait reset compelete */
	ret = RK_POLL_TIMEOUT(crypto_read(CRYPTO_RST_CTL), RK_CRYPTO_TIMEOUT);

	return ret;
}

static void hw_hash_clean_ctx(struct rk_hash_ctx *ctx)
{
	/* clear hash status */
	crypto_write(CRYPTO_WRITE_MASK_ALL | 0, CRYPTO_HASH_CTL);

	assert(ctx);
	assert(ctx->magic == RK_HASH_CTX_MAGIC);

	crypto_hash_cache_free(ctx->hash_cache);

	memset(ctx, 0x00, sizeof(*ctx));
}

static int rk_hash_init(void *hw_ctx, u32 algo)
{
	struct rk_hash_ctx *tmp_ctx = (struct rk_hash_ctx *)hw_ctx;
	u32 reg_ctrl = 0;
	int ret;

	if (!tmp_ctx)
		return -EINVAL;

	reg_ctrl = CRYPTO_SW_CC_RESET;
	crypto_write(reg_ctrl | (reg_ctrl << CRYPTO_WRITE_MASK_SHIFT),
		     CRYPTO_RST_CTL);

	/* wait reset compelete */
	ret = RK_POLL_TIMEOUT(crypto_read(CRYPTO_RST_CTL),
			      RK_CRYPTO_TIMEOUT);

	reg_ctrl = 0;
	tmp_ctx->algo = algo;
	switch (algo) {
	case CRYPTO_MD5:
	case CRYPTO_HMAC_MD5:
		reg_ctrl |= CRYPTO_MODE_MD5;
		tmp_ctx->digest_size = 16;
		break;
	case CRYPTO_SHA1:
	case CRYPTO_HMAC_SHA1:
		reg_ctrl |= CRYPTO_MODE_SHA1;
		tmp_ctx->digest_size = 20;
		break;
	case CRYPTO_SHA256:
	case CRYPTO_HMAC_SHA256:
		reg_ctrl |= CRYPTO_MODE_SHA256;
		tmp_ctx->digest_size = 32;
		break;
	case CRYPTO_SHA512:
	case CRYPTO_HMAC_SHA512:
		reg_ctrl |= CRYPTO_MODE_SHA512;
		tmp_ctx->digest_size = 64;
		break;
	case CRYPTO_SM3:
	case CRYPTO_HMAC_SM3:
		reg_ctrl |= CRYPTO_MODE_SM3;
		tmp_ctx->digest_size = 32;
		break;
	default:
		ret = -EINVAL;
		goto exit;
	}

	clear_hash_out_reg();

	/* enable hardware padding */
	reg_ctrl |= CRYPTO_HW_PAD_ENABLE;
	crypto_write(reg_ctrl | CRYPTO_WRITE_MASK_ALL, CRYPTO_HASH_CTL);

	/* FIFO input and output data byte swap */
	/* such as B0, B1, B2, B3 -> B3, B2, B1, B0 */
	reg_ctrl = CRYPTO_DOUT_BYTESWAP | CRYPTO_DOIN_BYTESWAP;
	crypto_write(reg_ctrl | CRYPTO_WRITE_MASK_ALL, CRYPTO_FIFO_CTL);

	/* enable src_item_done interrupt */
	crypto_write(0, CRYPTO_DMA_INT_EN);

	tmp_ctx->magic = RK_HASH_CTX_MAGIC;

	return 0;
exit:
	/* clear hash setting if init failed */
	crypto_write(CRYPTO_WRITE_MASK_ALL | 0, CRYPTO_HASH_CTL);

	return ret;
}

static int rk_hash_direct_calc(void *hw_data, const u8 *data,
			       u32 data_len, u8 *started_flag, u8 is_last)
{
	struct rockchip_crypto_priv *priv = hw_data;
	struct rk_hash_ctx *hash_ctx = priv->hw_ctx;
	struct crypto_lli_desc *lli = &hash_ctx->data_lli;
	int ret = -EINVAL;
	u32 tmp = 0, mask = 0;

	assert(IS_ALIGNED((ulong)data, DATA_ADDR_ALIGN_SIZE));
	assert(is_last || IS_ALIGNED(data_len, DATA_LEN_ALIGN_SIZE));

	debug("%s: data = %p, len = %u, s = %x, l = %x\n",
	      __func__, data, data_len, *started_flag, is_last);

	memset(lli, 0x00, sizeof(*lli));
	lli->src_addr = (u32)virt_to_phys(data);
	lli->src_len = data_len;
	lli->dma_ctrl = LLI_DMA_CTRL_SRC_DONE;

	if (is_last) {
		lli->user_define |= LLI_USER_STRING_LAST;
		lli->dma_ctrl |= LLI_DMA_CTRL_LAST;
	} else {
		lli->next_addr = (u32)virt_to_phys(lli);
		lli->dma_ctrl |= LLI_DMA_CTRL_PAUSE;
	}

	if (!(*started_flag)) {
		lli->user_define |=
			(LLI_USER_STRING_START | LLI_USER_CPIHER_START);
		crypto_write((u32)virt_to_phys(lli), CRYPTO_DMA_LLI_ADDR);
		crypto_write((CRYPTO_HASH_ENABLE << CRYPTO_WRITE_MASK_SHIFT) |
			     CRYPTO_HASH_ENABLE, CRYPTO_HASH_CTL);
		tmp = CRYPTO_DMA_START;
		*started_flag = 1;
	} else {
		tmp = CRYPTO_DMA_RESTART;
	}

	/* flush cache */
	crypto_flush_cacheline((ulong)lli, sizeof(*lli));
	crypto_flush_cacheline((ulong)data, data_len);

	/* start calculate */
	crypto_write(tmp << CRYPTO_WRITE_MASK_SHIFT | tmp,
		     CRYPTO_DMA_CTL);

	/* mask CRYPTO_SYNC_LOCKSTEP_INT_ST flag */
	mask = ~(mask | CRYPTO_SYNC_LOCKSTEP_INT_ST);

	/* wait calc ok */
	ret = RK_POLL_TIMEOUT(!(crypto_read(CRYPTO_DMA_INT_ST) & mask),
			      RK_CRYPTO_TIMEOUT);

	/* clear interrupt status */
	tmp = crypto_read(CRYPTO_DMA_INT_ST);
	crypto_write(tmp, CRYPTO_DMA_INT_ST);

	if ((tmp & mask) != CRYPTO_SRC_ITEM_DONE_INT_ST &&
	    (tmp & mask) != CRYPTO_ZERO_LEN_INT_ST) {
		ret = -EFAULT;
		debug("[%s] %d: CRYPTO_DMA_INT_ST = 0x%x\n",
		      __func__, __LINE__, tmp);
		goto exit;
	}

	priv->length += data_len;
exit:
	return ret;
}

int rk_hash_update(void *ctx, const u8 *data, u32 data_len)
{
	struct rk_hash_ctx *tmp_ctx = (struct rk_hash_ctx *)ctx;
	int ret = -EINVAL;

	debug("\n");
	if (!tmp_ctx || !data)
		goto exit;

	if (tmp_ctx->digest_size == 0 || tmp_ctx->magic != RK_HASH_CTX_MAGIC)
		goto exit;

	ret = crypto_hash_update_with_cache(tmp_ctx->hash_cache,
					    data, data_len);

exit:
	/* free lli list */
	if (ret)
		hw_hash_clean_ctx(tmp_ctx);

	return ret;
}

int rk_hash_final(void *ctx, u8 *digest, size_t len)
{
	struct rk_hash_ctx *tmp_ctx = (struct rk_hash_ctx *)ctx;
	int ret = -EINVAL;

	if (!digest)
		goto exit;

	if (!tmp_ctx ||
	    tmp_ctx->digest_size == 0 ||
	    len > tmp_ctx->digest_size ||
	    tmp_ctx->magic != RK_HASH_CTX_MAGIC) {
		goto exit;
	}

	/* wait hash value ok */
	ret = RK_POLL_TIMEOUT(!crypto_read(CRYPTO_HASH_VALID),
			      RK_CRYPTO_TIMEOUT);

	read_regs(CRYPTO_HASH_DOUT_0, digest, len);

	/* clear hash status */
	crypto_write(CRYPTO_HASH_IS_VALID, CRYPTO_HASH_VALID);
	crypto_write(CRYPTO_WRITE_MASK_ALL | 0, CRYPTO_HASH_CTL);

exit:

	return ret;
}

static u32 rockchip_crypto_capability(struct udevice *dev)
{
	struct rockchip_crypto_priv *priv = dev_get_priv(dev);
	u32 capability, mask = 0;

	capability = priv->soc_data->capability;

#if !(CONFIG_IS_ENABLED(ROCKCHIP_CIPHER))
	mask |= (CRYPTO_DES | CRYPTO_AES | CRYPTO_SM4);
#endif

#if !(CONFIG_IS_ENABLED(ROCKCHIP_HMAC))
	mask |= (CRYPTO_HMAC_MD5 | CRYPTO_HMAC_SHA1 | CRYPTO_HMAC_SHA256 |
			 CRYPTO_HMAC_SHA512 | CRYPTO_HMAC_SM3);
#endif

#if !(CONFIG_IS_ENABLED(ROCKCHIP_RSA))
	mask |= (CRYPTO_RSA512 | CRYPTO_RSA1024 | CRYPTO_RSA2048 |
			 CRYPTO_RSA3072 | CRYPTO_RSA4096);
#endif

	return capability & (~mask);
}

static int rockchip_crypto_sha_init(struct udevice *dev, sha_context *ctx)
{
	struct rockchip_crypto_priv *priv = dev_get_priv(dev);
	struct rk_hash_ctx *hash_ctx = priv->hw_ctx;

	if (!ctx)
		return -EINVAL;

	memset(hash_ctx, 0x00, sizeof(*hash_ctx));

	priv->length = 0;

	hash_ctx->hash_cache = crypto_hash_cache_alloc(rk_hash_direct_calc,
						       priv, ctx->length,
						       DATA_ADDR_ALIGN_SIZE,
						       DATA_LEN_ALIGN_SIZE);
	if (!hash_ctx->hash_cache)
		return -EFAULT;

	return rk_hash_init(hash_ctx, ctx->algo);
}

static int rockchip_crypto_sha_update(struct udevice *dev,
				      u32 *input, u32 len)
{
	struct rockchip_crypto_priv *priv = dev_get_priv(dev);
	int ret, i;
	u8 *p;

	if (!len)
		return -EINVAL;

	p = (u8 *)input;

	for (i = 0; i < len / HASH_UPDATE_LIMIT; i++, p += HASH_UPDATE_LIMIT) {
		ret = rk_hash_update(priv->hw_ctx, p, HASH_UPDATE_LIMIT);
		if (ret)
			goto exit;
	}

	if (len % HASH_UPDATE_LIMIT)
		ret = rk_hash_update(priv->hw_ctx, p, len % HASH_UPDATE_LIMIT);

exit:
	return ret;
}

static int rockchip_crypto_sha_final(struct udevice *dev,
				     sha_context *ctx, u8 *output)
{
	struct rockchip_crypto_priv *priv = dev_get_priv(dev);
	u32 nbits;
	int ret;

	nbits = crypto_algo_nbits(ctx->algo);

	if (priv->length != ctx->length) {
		printf("total length(0x%08x) != init length(0x%08x)!\n",
		       priv->length, ctx->length);
		ret = -EIO;
		goto exit;
	}

	ret = rk_hash_final(priv->hw_ctx, (u8 *)output, BITS2BYTE(nbits));

exit:
	hw_hash_clean_ctx(priv->hw_ctx);
	return ret;
}

#if CONFIG_IS_ENABLED(ROCKCHIP_HMAC)
int rk_hmac_init(void *hw_ctx, u32 algo, u8 *key, u32 key_len)
{
	u32 reg_ctrl = 0;
	int ret;

	if (!key || !key_len || key_len > 64)
		return -EINVAL;

	clear_key_regs();

	write_key_reg(0, key, key_len);

	ret = rk_hash_init(hw_ctx, algo);
	if (ret)
		return ret;

	reg_ctrl = crypto_read(CRYPTO_HASH_CTL) | CRYPTO_HMAC_ENABLE;
	crypto_write(reg_ctrl | CRYPTO_WRITE_MASK_ALL, CRYPTO_HASH_CTL);

	return ret;
}

static int rockchip_crypto_hmac_init(struct udevice *dev,
				     sha_context *ctx, u8 *key, u32 key_len)
{
	struct rockchip_crypto_priv *priv = dev_get_priv(dev);
	struct rk_hash_ctx *hash_ctx = priv->hw_ctx;

	if (!ctx)
		return -EINVAL;

	memset(hash_ctx, 0x00, sizeof(*hash_ctx));

	priv->length = 0;

	hash_ctx->hash_cache = crypto_hash_cache_alloc(rk_hash_direct_calc,
						       priv, ctx->length,
						       DATA_ADDR_ALIGN_SIZE,
						       DATA_LEN_ALIGN_SIZE);
	if (!hash_ctx->hash_cache)
		return -EFAULT;

	return rk_hmac_init(priv->hw_ctx, ctx->algo, key, key_len);
}

static int rockchip_crypto_hmac_update(struct udevice *dev,
				       u32 *input, u32 len)
{
	return rockchip_crypto_sha_update(dev, input, len);
}

static int rockchip_crypto_hmac_final(struct udevice *dev,
				      sha_context *ctx, u8 *output)
{
	return rockchip_crypto_sha_final(dev, ctx, output);
}

#endif

#if CONFIG_IS_ENABLED(ROCKCHIP_CIPHER)
static u8 g_key_chn;

static const u32 rk_mode2bc_mode[RK_MODE_MAX] = {
	[RK_MODE_ECB] = CRYPTO_BC_ECB,
	[RK_MODE_CBC] = CRYPTO_BC_CBC,
	[RK_MODE_CTS] = CRYPTO_BC_CTS,
	[RK_MODE_CTR] = CRYPTO_BC_CTR,
	[RK_MODE_CFB] = CRYPTO_BC_CFB,
	[RK_MODE_OFB] = CRYPTO_BC_OFB,
	[RK_MODE_XTS] = CRYPTO_BC_XTS,
	[RK_MODE_CCM] = CRYPTO_BC_CCM,
	[RK_MODE_GCM] = CRYPTO_BC_GCM,
	[RK_MODE_CMAC] = CRYPTO_BC_CMAC,
	[RK_MODE_CBC_MAC] = CRYPTO_BC_CBC_MAC,
};

static inline void set_pc_len_reg(u32 chn, u64 pc_len)
{
	u32 chn_base = CRYPTO_CH0_PC_LEN_0 + chn * 0x08;

	crypto_write(pc_len & 0xffffffff, chn_base);
	crypto_write(pc_len >> 32, chn_base + 4);
}

static inline void set_aad_len_reg(u32 chn, u64 pc_len)
{
	u32 chn_base = CRYPTO_CH0_AAD_LEN_0 + chn * 0x08;

	crypto_write(pc_len & 0xffffffff, chn_base);
	crypto_write(pc_len >> 32, chn_base + 4);
}

static inline bool is_des_mode(u32 rk_mode)
{
	return (rk_mode == RK_MODE_ECB ||
		rk_mode == RK_MODE_CBC ||
		rk_mode == RK_MODE_CFB ||
		rk_mode == RK_MODE_OFB);
}

static void dump_crypto_state(struct crypto_lli_desc *desc,
			      u32 tmp, u32 expt_int,
			      const u8 *in, const u8 *out,
			      u32 len, int ret)
{
	IMSG("%s\n", ret == -ETIME ? "timeout" : "dismatch");

	IMSG("CRYPTO_DMA_INT_ST = %08x, expect_int = %08x\n",
	     tmp, expt_int);
	IMSG("data desc		= %p\n", desc);
	IMSG("\taddr_in		= [%08x <=> %08x]\n",
	     desc->src_addr, (u32)virt_to_phys(in));
	IMSG("\taddr_out	= [%08x <=> %08x]\n",
	     desc->dst_addr, (u32)virt_to_phys(out));
	IMSG("\tsrc_len		= [%08x <=> %08x]\n",
	     desc->src_len, (u32)len);
	IMSG("\tdst_len		= %08x\n", desc->dst_len);
	IMSG("\tdma_ctl		= %08x\n", desc->dma_ctrl);
	IMSG("\tuser_define	= %08x\n", desc->user_define);

	IMSG("\n\nDMA CRYPTO_DMA_LLI_ADDR status = %08x\n",
	     crypto_read(CRYPTO_DMA_LLI_ADDR));
	IMSG("DMA CRYPTO_DMA_ST status = %08x\n",
	     crypto_read(CRYPTO_DMA_ST));
	IMSG("DMA CRYPTO_DMA_STATE status = %08x\n",
	     crypto_read(CRYPTO_DMA_STATE));
	IMSG("DMA CRYPTO_DMA_LLI_RADDR status = %08x\n",
	     crypto_read(CRYPTO_DMA_LLI_RADDR));
	IMSG("DMA CRYPTO_DMA_SRC_RADDR status = %08x\n",
	     crypto_read(CRYPTO_DMA_SRC_RADDR));
	IMSG("DMA CRYPTO_DMA_DST_RADDR status = %08x\n",
	     crypto_read(CRYPTO_DMA_DST_RADDR));
	IMSG("DMA CRYPTO_CIPHER_ST status = %08x\n",
	     crypto_read(CRYPTO_CIPHER_ST));
	IMSG("DMA CRYPTO_CIPHER_STATE status = %08x\n",
	     crypto_read(CRYPTO_CIPHER_STATE));
	IMSG("DMA CRYPTO_TAG_VALID status = %08x\n",
	     crypto_read(CRYPTO_TAG_VALID));
	IMSG("LOCKSTEP status = %08x\n\n",
	     crypto_read(0x618));

	IMSG("dst %dbyte not transferred\n",
	     desc->dst_addr + desc->dst_len -
	     crypto_read(CRYPTO_DMA_DST_RADDR));
}

static int ccm128_set_iv_reg(u32 chn, const u8 *nonce, u32 nlen)
{
	u8 iv_buf[AES_BLOCK_SIZE];
	u32 L;

	memset(iv_buf, 0x00, sizeof(iv_buf));

	L = 15 - nlen;
	iv_buf[0] = ((u8)(L - 1) & 7);

	/* the L parameter */
	L = iv_buf[0] & 7;

	/* nonce is too short */
	if (nlen < (14 - L))
		return -EINVAL;

	/* clear aad flag */
	iv_buf[0] &= ~0x40;
	memcpy(&iv_buf[1], nonce, 14 - L);

	set_iv_reg(chn, iv_buf, AES_BLOCK_SIZE);

	return 0;
}

static void ccm_aad_padding(u32 aad_len, u8 *padding, u32 *padding_size)
{
	u32 i;

	i = aad_len < (0x10000 - 0x100) ? 2 : 6;

	if (i == 2) {
		padding[0] = (u8)(aad_len >> 8);
		padding[1] = (u8)aad_len;
	} else {
		padding[0] = 0xFF;
		padding[1] = 0xFE;
		padding[2] = (u8)(aad_len >> 24);
		padding[3] = (u8)(aad_len >> 16);
		padding[4] = (u8)(aad_len >> 8);
	}

	*padding_size = i;
}

static int ccm_compose_aad_iv(u8 *aad_iv, u32 data_len, u32 tag_size)
{
	aad_iv[0] |= ((u8)(((tag_size - 2) / 2) & 7) << 3);

	aad_iv[12] = (u8)(data_len >> 24);
	aad_iv[13] = (u8)(data_len >> 16);
	aad_iv[14] = (u8)(data_len >> 8);
	aad_iv[15] = (u8)data_len;

	aad_iv[0] |= 0x40;	//set aad flag

	return 0;
}

static int hw_cipher_init(u32 chn, const u8 *key, const u8 *twk_key,
			  u32 key_len, const u8 *iv, u32 iv_len,
			  u32 algo, u32 mode, bool enc)
{
	u32 rk_mode = RK_GET_RK_MODE(mode);
	u32 key_chn_sel = chn;
	u32 reg_ctrl = 0;

	IMSG("%s: key addr is %p, key_len is %d, iv addr is %p",
	     __func__, key, key_len, iv);
	if (rk_mode >= RK_MODE_MAX)
		return -EINVAL;

	switch (algo) {
	case CRYPTO_DES:
		if (key_len > DES_BLOCK_SIZE)
			reg_ctrl |= CRYPTO_BC_TDES;
		else
			reg_ctrl |= CRYPTO_BC_DES;
		break;
	case CRYPTO_AES:
		reg_ctrl |= CRYPTO_BC_AES;
		break;
	case CRYPTO_SM4:
		reg_ctrl |= CRYPTO_BC_SM4;
		break;
	default:
		return -EINVAL;
	}

	if (algo == CRYPTO_AES || algo == CRYPTO_SM4) {
		switch (key_len) {
		case AES_KEYSIZE_128:
			reg_ctrl |= CRYPTO_BC_128_bit_key;
			break;
		case AES_KEYSIZE_192:
			reg_ctrl |= CRYPTO_BC_192_bit_key;
			break;
		case AES_KEYSIZE_256:
			reg_ctrl |= CRYPTO_BC_256_bit_key;
			break;
		default:
			return -EINVAL;
		}
	}

	reg_ctrl |= rk_mode2bc_mode[rk_mode];
	if (!enc)
		reg_ctrl |= CRYPTO_BC_DECRYPT;

	/* write key data to reg */
	write_key_reg(key_chn_sel, key, key_len);

	/* write twk key for xts mode */
	if (rk_mode == RK_MODE_XTS)
		write_key_reg(key_chn_sel + 4, twk_key, key_len);

	/* set iv reg */
	if (rk_mode == RK_MODE_CCM)
		ccm128_set_iv_reg(chn, iv, iv_len);
	else
		set_iv_reg(chn, iv, iv_len);

	/* din_swap set 1, dout_swap set 1, default 1. */
	crypto_write(0x00030003, CRYPTO_FIFO_CTL);
	crypto_write(0, CRYPTO_DMA_INT_EN);

	crypto_write(reg_ctrl | CRYPTO_WRITE_MASK_ALL, CRYPTO_BC_CTL);

	return 0;
}

static int hw_cipher_crypt(const u8 *in, u8 *out, u64 len,
			   const u8 *aad, u32 aad_len,
			   u8 *tag, u32 tag_len, u32 mode)
{
	struct crypto_lli_desc *data_desc = NULL, *aad_desc = NULL;
	u8 *dma_in = NULL, *dma_out = NULL, *aad_tmp = NULL;
	u32 rk_mode = RK_GET_RK_MODE(mode);
	u32 reg_ctrl = 0, tmp_len = 0;
	u32 expt_int = 0, mask = 0;
	u32 key_chn = g_key_chn;
	u32 tmp, dst_len = 0;
	int ret = -1;

	if (rk_mode == RK_MODE_CTS && len <= AES_BLOCK_SIZE) {
		printf("CTS mode length %u < 16Byte\n", (u32)len);
		return -EINVAL;
	}

	tmp_len = (rk_mode == RK_MODE_CTR) ? ROUNDUP(len, AES_BLOCK_SIZE) : len;

	data_desc = align_malloc(sizeof(*data_desc), LLI_ADDR_ALIGN_SIZE);
	if (!data_desc)
		goto exit;

	if (IS_ALIGNED((ulong)in, DATA_ADDR_ALIGN_SIZE) && tmp_len == len)
		dma_in = (void *)in;
	else
		dma_in = align_malloc(tmp_len, DATA_ADDR_ALIGN_SIZE);
	if (!dma_in)
		goto exit;

	if (out) {
		if (IS_ALIGNED((ulong)out, DATA_ADDR_ALIGN_SIZE) &&
		    tmp_len == len)
			dma_out = out;
		else
			dma_out = align_malloc(tmp_len, DATA_ADDR_ALIGN_SIZE);
		if (!dma_out)
			goto exit;
		dst_len = tmp_len;
	}

	memset(data_desc, 0x00, sizeof(*data_desc));
	if (dma_in != in)
		memcpy(dma_in, in, len);

	data_desc->src_addr    = (u32)virt_to_phys(dma_in);
	data_desc->src_len     = tmp_len;
	data_desc->dst_addr    = (u32)virt_to_phys(dma_out);
	data_desc->dst_len     = dst_len;
	data_desc->dma_ctrl    = LLI_DMA_CTRL_LAST;

	if (IS_MAC_MODE(rk_mode)) {
		expt_int = CRYPTO_LIST_DONE_INT_ST;
		data_desc->dma_ctrl |= LLI_DMA_CTRL_LIST_DONE;
	} else {
		expt_int = CRYPTO_DST_ITEM_DONE_INT_ST;
		data_desc->dma_ctrl |= LLI_DMA_CTRL_DST_DONE;
	}

	if (rk_mode == RK_MODE_CCM || rk_mode == RK_MODE_GCM) {
		u32 aad_tmp_len = 0;

		data_desc->user_define = LLI_USER_STRING_START |
					 LLI_USER_STRING_LAST |
					 (key_chn << 4);

		aad_desc = align_malloc(sizeof(*aad_desc), LLI_ADDR_ALIGN_SIZE);
		if (!aad_desc)
			goto exit;

		memset(aad_desc, 0x00, sizeof(*aad_desc));
		aad_desc->next_addr = (u32)virt_to_phys(data_desc);
		aad_desc->user_define = LLI_USER_CPIHER_START |
					 LLI_USER_STRING_START |
					 LLI_USER_STRING_LAST |
					 LLI_USER_STRING_AAD |
					 (key_chn << 4);

		if (rk_mode == RK_MODE_CCM) {
			u8 padding[AES_BLOCK_SIZE];
			u32 padding_size = 0;

			memset(padding, 0x00, sizeof(padding));
			ccm_aad_padding(aad_len, padding, &padding_size);

			aad_tmp_len = aad_len + AES_BLOCK_SIZE + padding_size;
			aad_tmp_len = ROUNDUP(aad_tmp_len, AES_BLOCK_SIZE);
			aad_tmp = align_malloc(aad_tmp_len,
					       DATA_ADDR_ALIGN_SIZE);
			if (!aad_tmp)
				goto exit;

			/* read iv data from reg */
			get_iv_reg(key_chn, aad_tmp, AES_BLOCK_SIZE);
			ccm_compose_aad_iv(aad_tmp, tmp_len, tag_len);
			memcpy(aad_tmp + AES_BLOCK_SIZE, padding, padding_size);
			memset(aad_tmp + aad_tmp_len - AES_BLOCK_SIZE,
			       0x00, AES_BLOCK_SIZE);
			memcpy(aad_tmp + AES_BLOCK_SIZE + padding_size,
			       aad, aad_len);
		} else {
			aad_tmp_len = aad_len;
			if (IS_ALIGNED((ulong)aad, DATA_ADDR_ALIGN_SIZE)) {
				aad_tmp = (void *)aad;
			} else {
				aad_tmp = align_malloc(aad_tmp_len,
						       DATA_ADDR_ALIGN_SIZE);
				if (!aad_tmp)
					goto exit;

				memcpy(aad_tmp, aad, aad_tmp_len);
			}

			set_aad_len_reg(key_chn, aad_tmp_len);
			set_pc_len_reg(key_chn, tmp_len);
		}

		aad_desc->src_addr = (u32)virt_to_phys(aad_tmp);
		aad_desc->src_len  = aad_tmp_len;
		crypto_write((u32)virt_to_phys(aad_desc), CRYPTO_DMA_LLI_ADDR);
		cache_op_inner(DCACHE_AREA_CLEAN, aad_tmp, aad_tmp_len);
		cache_op_inner(DCACHE_AREA_CLEAN, aad_desc, sizeof(*aad_desc));
	} else {
		data_desc->user_define = LLI_USER_CPIHER_START |
					 LLI_USER_STRING_START |
					 LLI_USER_STRING_LAST |
					 (key_chn << 4);
		crypto_write((u32)virt_to_phys(data_desc), CRYPTO_DMA_LLI_ADDR);
	}

	cache_op_inner(DCACHE_AREA_CLEAN, data_desc, sizeof(*data_desc));
	cache_op_inner(DCACHE_AREA_CLEAN, dma_in, tmp_len);
	cache_op_inner(DCACHE_AREA_INVALIDATE, dma_out, tmp_len);

	/* din_swap set 1, dout_swap set 1, default 1. */
	crypto_write(0x00030003, CRYPTO_FIFO_CTL);
	crypto_write(0, CRYPTO_DMA_INT_EN);

	reg_ctrl = crypto_read(CRYPTO_BC_CTL) | CRYPTO_BC_ENABLE;
	crypto_write(reg_ctrl | CRYPTO_WRITE_MASK_ALL, CRYPTO_BC_CTL);
	crypto_write(0x00010001, CRYPTO_DMA_CTL);//start

	mask = ~(mask | CRYPTO_SYNC_LOCKSTEP_INT_ST);

	/* wait calc ok */
	ret = RK_POLL_TIMEOUT(!(crypto_read(CRYPTO_DMA_INT_ST) & mask),
			      RK_CRYPTO_TIMEOUT);
	tmp = crypto_read(CRYPTO_DMA_INT_ST);
	crypto_write(tmp, CRYPTO_DMA_INT_ST);

	if ((tmp & mask) == expt_int) {
		if (out && out != dma_out)
			memcpy(out, dma_out, len);

		if (IS_NEED_TAG(rk_mode)) {
			ret = WAIT_TAG_VALID(key_chn, RK_CRYPTO_TIMEOUT);
			get_tag_from_reg(key_chn, tag, AES_BLOCK_SIZE);
		}
	} else {
		dump_crypto_state(data_desc, tmp, expt_int, in, out, len, ret);
		ret = -1;
	}

exit:
	crypto_write(0xffff0000, CRYPTO_BC_CTL);//bc_ctl disable
	align_free(data_desc);
	align_free(aad_desc);
	if (dma_in != in)
		align_free(dma_in);
	if (out && dma_out != out)
		align_free(dma_out);
	if (aad && aad != aad_tmp)
		align_free(aad_tmp);

	return ret;
}

static int hw_aes_init(u32 chn, const u8 *key, const u8 *twk_key, u32 key_len,
		       const u8 *iv, u32 iv_len, u32 mode, bool enc)
{
	u32 rk_mode = RK_GET_RK_MODE(mode);

	if (rk_mode > RK_MODE_XTS)
		return -EINVAL;

	if (iv_len > AES_BLOCK_SIZE)
		return -EINVAL;

	if (IS_NEED_IV(rk_mode)) {
		if (!iv || iv_len != AES_BLOCK_SIZE)
			return -EINVAL;
	} else {
		iv_len = 0;
	}

	if (rk_mode == RK_MODE_XTS) {
		if (key_len != AES_KEYSIZE_128 && key_len != AES_KEYSIZE_256)
			return -EINVAL;

		if (!key || !twk_key)
			return -EINVAL;
	} else {
		if (key_len != AES_KEYSIZE_128 &&
		    key_len != AES_KEYSIZE_192 &&
		    key_len != AES_KEYSIZE_256)
			return -EINVAL;
	}

	return hw_cipher_init(chn, key, twk_key, key_len, iv, iv_len,
			      CRYPTO_AES, mode, enc);
}

static int hw_sm4_init(u32  chn, const u8 *key, const u8 *twk_key, u32 key_len,
		       const u8 *iv, u32 iv_len, u32 mode, bool enc)
{
	u32 rk_mode = RK_GET_RK_MODE(mode);

	if (rk_mode > RK_MODE_XTS)
		return -EINVAL;

	if (iv_len > SM4_BLOCK_SIZE || key_len != SM4_KEYSIZE)
		return -EINVAL;

	if (IS_NEED_IV(rk_mode)) {
		if (!iv || iv_len != SM4_BLOCK_SIZE)
			return -EINVAL;
	} else {
		iv_len = 0;
	}

	if (rk_mode == RK_MODE_XTS) {
		if (!key || !twk_key)
			return -EINVAL;
	}

	return hw_cipher_init(chn, key, twk_key, key_len, iv, iv_len,
			      CRYPTO_SM4, mode, enc);
}

int rk_crypto_des(struct udevice *dev, u32 mode, const u8 *key, u32 key_len,
		  const u8 *iv, const u8 *in, u8 *out, u32 len, bool enc)
{
	u32 rk_mode = RK_GET_RK_MODE(mode);
	u8 tmp_key[24];
	int ret;

	if (!is_des_mode(rk_mode))
		return -EINVAL;

	if (key_len == DES_BLOCK_SIZE || key_len == 3 * DES_BLOCK_SIZE) {
		memcpy(tmp_key, key, key_len);
	} else if (key_len == 2 * DES_BLOCK_SIZE) {
		memcpy(tmp_key, key, 16);
		memcpy(tmp_key + 16, key, 8);
		key_len = 3 * DES_BLOCK_SIZE;
	} else {
		return -EINVAL;
	}

	ret = hw_cipher_init(0, tmp_key, NULL, key_len, iv, DES_BLOCK_SIZE,
			     CRYPTO_DES, mode, enc);
	if (ret)
		goto exit;

	ret = hw_cipher_crypt(in, out, len, NULL, 0,
			      NULL, 0, mode);

exit:
	return ret;
}

int rk_crypto_aes(struct udevice *dev, u32 mode,
		  const u8 *key, const u8 *twk_key, u32 key_len,
		  const u8 *iv, u32 iv_len,
		  const u8 *in, u8 *out, u32 len, bool enc)
{
	int ret;

	/* RV1126/RV1109 do not support aes-192 */
#if defined(CONFIG_ROCKCHIP_RV1126)
	if (key_len == AES_KEYSIZE_192)
		return -EINVAL;
#endif

	ret = hw_aes_init(0, key, twk_key, key_len, iv, iv_len, mode, enc);
	if (ret)
		return ret;

	return hw_cipher_crypt(in, out, len, NULL, 0,
			       NULL, 0, mode);
}

int rk_crypto_sm4(struct udevice *dev, u32 mode,
		  const u8 *key, const u8 *twk_key, u32 key_len,
		  const u8 *iv, u32 iv_len,
		  const u8 *in, u8 *out, u32 len, bool enc)
{
	int ret;

	ret = hw_sm4_init(0, key, twk_key, key_len, iv, iv_len, mode, enc);
	if (ret)
		return ret;

	return hw_cipher_crypt(in, out, len, NULL, 0, NULL, 0, mode);
}

int rockchip_crypto_cipher(struct udevice *dev, cipher_context *ctx,
			   const u8 *in, u8 *out, u32 len, bool enc)
{
	switch (ctx->algo) {
	case CRYPTO_DES:
		return rk_crypto_des(dev, ctx->mode, ctx->key, ctx->key_len,
				     ctx->iv, in, out, len, enc);
	case CRYPTO_AES:
		return rk_crypto_aes(dev, ctx->mode,
				     ctx->key, ctx->twk_key, ctx->key_len,
				     ctx->iv, ctx->iv_len, in, out, len, enc);
	case CRYPTO_SM4:
		return rk_crypto_sm4(dev, ctx->mode,
				     ctx->key, ctx->twk_key, ctx->key_len,
				     ctx->iv, ctx->iv_len, in, out, len, enc);
	default:
		return -EINVAL;
	}
}

int rk_crypto_mac(struct udevice *dev, u32 algo, u32 mode,
		  const u8 *key, u32 key_len,
		  const u8 *in, u32 len, u8 *tag)
{
	u32 rk_mode = RK_GET_RK_MODE(mode);
	int ret;

	if (!IS_MAC_MODE(rk_mode))
		return -EINVAL;

	if (algo != CRYPTO_AES && algo != CRYPTO_SM4)
		return -EINVAL;

	/* RV1126/RV1109 do not support aes-192 */
#if defined(CONFIG_ROCKCHIP_RV1126)
	if (algo == CRYPTO_AES && key_len == AES_KEYSIZE_192)
		return -EINVAL;
#endif

	ret = hw_cipher_init(g_key_chn, key, NULL, key_len, NULL, 0,
			     algo, mode, true);
	if (ret)
		return ret;

	return hw_cipher_crypt(in, NULL, len, NULL, 0,
			       tag, AES_BLOCK_SIZE, mode);
}

int rockchip_crypto_mac(struct udevice *dev, cipher_context *ctx,
			const u8 *in, u32 len, u8 *tag)
{
	return rk_crypto_mac(dev, ctx->algo, ctx->mode,
			     ctx->key, ctx->key_len, in, len, tag);
}

int rk_crypto_ae(struct udevice *dev, u32 algo, u32 mode,
		 const u8 *key, u32 key_len, const u8 *nonce, u32 nonce_len,
		 const u8 *in, u32 len, const u8 *aad, u32 aad_len,
		 u8 *out, u8 *tag)
{
	u32 rk_mode = RK_GET_RK_MODE(mode);
	int ret;

	if (!IS_AE_MODE(rk_mode))
		return -EINVAL;

	if (algo != CRYPTO_AES && algo != CRYPTO_SM4)
		return -EINVAL;

	/* RV1126/RV1109 do not support aes-192 */
#if defined(CONFIG_ROCKCHIP_RV1126)
	if (algo == CRYPTO_AES && key_len == AES_KEYSIZE_192)
		return -EINVAL;
#endif

	ret = hw_cipher_init(g_key_chn, key, NULL, key_len, nonce, nonce_len,
			     algo, mode, true);
	if (ret)
		return ret;

	return hw_cipher_crypt(in, out, len, aad, aad_len,
			       tag, AES_BLOCK_SIZE, mode);
}

int rockchip_crypto_ae(struct udevice *dev, cipher_context *ctx,
		       const u8 *in, u32 len, const u8 *aad, u32 aad_len,
		       u8 *out, u8 *tag)

{
	return rk_crypto_ae(dev, ctx->algo, ctx->mode, ctx->key, ctx->key_len,
			    ctx->iv, ctx->iv_len, in, len,
			    aad, aad_len, out, tag);
}

#endif

#if CONFIG_IS_ENABLED(ROCKCHIP_RSA)
static int rockchip_crypto_rsa_verify(struct udevice *dev, rsa_key *ctx,
				      u8 *sign, u8 *output)
{
	struct mpa_num *mpa_m = NULL, *mpa_e = NULL, *mpa_n = NULL;
	struct mpa_num *mpa_c = NULL, *mpa_result = NULL;
	u32 n_bits, n_words;
	int ret;

	if (!ctx)
		return -EINVAL;

	if (ctx->algo != CRYPTO_RSA512 &&
	    ctx->algo != CRYPTO_RSA1024 &&
	    ctx->algo != CRYPTO_RSA2048 &&
	    ctx->algo != CRYPTO_RSA3072 &&
	    ctx->algo != CRYPTO_RSA4096)
		return -EINVAL;

	n_bits = crypto_algo_nbits(ctx->algo);
	n_words = BITS2WORD(n_bits);

	ret = rk_mpa_alloc(&mpa_m, sign, n_words);
	if (ret)
		goto exit;

	ret = rk_mpa_alloc(&mpa_e, ctx->e, n_words);
	if (ret)
		goto exit;

	ret = rk_mpa_alloc(&mpa_n, ctx->n, n_words);
	if (ret)
		goto exit;

	if (ctx->c) {
		ret = rk_mpa_alloc(&mpa_c, ctx->c, n_words);
		if (ret)
			goto exit;
	}

	ret = rk_mpa_alloc(&mpa_result, NULL, n_words);
	if (ret)
		goto exit;

	ret = rk_exptmod_np(mpa_m, mpa_e, mpa_n, mpa_c, mpa_result);
	if (!ret)
		memcpy(output, mpa_result->d, BITS2BYTE(n_bits));

exit:
	rk_mpa_free(&mpa_m);
	rk_mpa_free(&mpa_e);
	rk_mpa_free(&mpa_n);
	rk_mpa_free(&mpa_c);
	rk_mpa_free(&mpa_result);

	return ret;
}
#endif

static const struct dm_crypto_ops rockchip_crypto_ops = {
	.capability   = rockchip_crypto_capability,
	.sha_init     = rockchip_crypto_sha_init,
	.sha_update   = rockchip_crypto_sha_update,
	.sha_final    = rockchip_crypto_sha_final,
#if CONFIG_IS_ENABLED(ROCKCHIP_RSA)
	.rsa_verify   = rockchip_crypto_rsa_verify,
#endif
#if CONFIG_IS_ENABLED(ROCKCHIP_HMAC)
	.hmac_init    = rockchip_crypto_hmac_init,
	.hmac_update  = rockchip_crypto_hmac_update,
	.hmac_final   = rockchip_crypto_hmac_final,
#endif
#if CONFIG_IS_ENABLED(ROCKCHIP_CIPHER)
	.cipher_crypt = rockchip_crypto_cipher,
	.cipher_mac = rockchip_crypto_mac,
	.cipher_ae  = rockchip_crypto_ae,
#endif
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
	int len, ret = -EINVAL;

	memset(priv, 0x00, sizeof(*priv));

	priv->reg = (fdt_addr_t)dev_read_addr_ptr(dev);
	if (priv->reg == FDT_ADDR_T_NONE)
		return -EINVAL;

	crypto_base = priv->reg;

	/* if there is no clocks in dts, just skip it */
	if (!dev_read_prop(dev, "clocks", &len)) {
		printf("Can't find \"clocks\" property\n");
		return 0;
	}

	memset(priv, 0x00, sizeof(*priv));
	priv->clocks = malloc(len);
	if (!priv->clocks)
		return -ENOMEM;

	priv->nclocks = len / sizeof(u32);
	if (dev_read_u32_array(dev, "clocks", (u32 *)priv->clocks,
			       priv->nclocks)) {
		printf("Can't read \"clocks\" property\n");
		ret = -EINVAL;
		goto exit;
	}

	if (!dev_read_prop(dev, "clock-frequency", &len)) {
		printf("Can't find \"clock-frequency\" property\n");
		ret = -EINVAL;
		goto exit;
	}

	priv->frequencies = malloc(len);
	if (!priv->frequencies) {
		ret = -ENOMEM;
		goto exit;
	}

	priv->nclocks = len / sizeof(u32);
	if (dev_read_u32_array(dev, "clock-frequency", priv->frequencies,
			       priv->nclocks)) {
		printf("Can't read \"clock-frequency\" property\n");
		ret = -EINVAL;
		goto exit;
	}

	return 0;
exit:
	if (priv->clocks)
		free(priv->clocks);

	if (priv->frequencies)
		free(priv->frequencies);

	return ret;
}

static int rk_crypto_set_clk(struct udevice *dev)
{
	struct rockchip_crypto_priv *priv = dev_get_priv(dev);
	struct clk clk;
	int i, ret;

	if (!priv->clocks && priv->nclocks == 0)
		return 0;

	for (i = 0; i < priv->nclocks; i++) {
		ret = clk_get_by_index(dev, i, &clk);
		if (ret < 0) {
			printf("Failed to get clk index %d, ret=%d\n", i, ret);
			return ret;
		}
		ret = clk_set_rate(&clk, priv->frequencies[i]);
		if (ret < 0) {
			printf("%s: Failed to set clk(%ld): ret=%d\n",
			       __func__, clk.id, ret);
			return ret;
		}
	}

	return 0;
}

static int rockchip_crypto_probe(struct udevice *dev)
{
	struct rockchip_crypto_priv *priv = dev_get_priv(dev);
	struct rk_crypto_soc_data *sdata;
	int ret = 0;

	sdata = (struct rk_crypto_soc_data *)dev_get_driver_data(dev);

	if (sdata->dynamic_cap)
		sdata->capability = sdata->dynamic_cap();

	priv->soc_data = sdata;

	priv->hw_ctx = memalign(LLI_ADDR_ALIGN_SIZE,
				sizeof(struct rk_hash_ctx));
	if (!priv->hw_ctx)
		return -ENOMEM;

	ret = rk_crypto_set_clk(dev);
	if (ret)
		return ret;

	hw_crypto_reset();

	return 0;
}

static const struct rk_crypto_soc_data soc_data_base = {
	.capability = CRYPTO_MD5 |
		      CRYPTO_SHA1 |
		      CRYPTO_SHA256 |
		      CRYPTO_SHA512 |
		      CRYPTO_HMAC_MD5 |
		      CRYPTO_HMAC_SHA1 |
		      CRYPTO_HMAC_SHA256 |
		      CRYPTO_HMAC_SHA512 |
		      CRYPTO_RSA512 |
		      CRYPTO_RSA1024 |
		      CRYPTO_RSA2048 |
		      CRYPTO_RSA3072 |
		      CRYPTO_RSA4096 |
		      CRYPTO_DES |
		      CRYPTO_AES,
};

static const struct rk_crypto_soc_data soc_data_base_sm = {
	.capability = CRYPTO_MD5 |
		      CRYPTO_SHA1 |
		      CRYPTO_SHA256 |
		      CRYPTO_SHA512 |
		      CRYPTO_SM3 |
		      CRYPTO_HMAC_MD5 |
		      CRYPTO_HMAC_SHA1 |
		      CRYPTO_HMAC_SHA256 |
		      CRYPTO_HMAC_SHA512 |
		      CRYPTO_HMAC_SM3 |
		      CRYPTO_RSA512 |
		      CRYPTO_RSA1024 |
		      CRYPTO_RSA2048 |
		      CRYPTO_RSA3072 |
		      CRYPTO_RSA4096 |
		      CRYPTO_DES |
		      CRYPTO_AES |
		      CRYPTO_SM4,
};

static const struct rk_crypto_soc_data soc_data_rk1808 = {
	.capability = CRYPTO_MD5 |
		      CRYPTO_SHA1 |
		      CRYPTO_SHA256 |
		      CRYPTO_HMAC_MD5 |
		      CRYPTO_HMAC_SHA1 |
		      CRYPTO_HMAC_SHA256 |
		      CRYPTO_RSA512 |
		      CRYPTO_RSA1024 |
		      CRYPTO_RSA2048 |
		      CRYPTO_RSA3072 |
		      CRYPTO_RSA4096,
};

static const struct rk_crypto_soc_data soc_data_cryptov3 = {
	.capability  = 0,
	.dynamic_cap = crypto_v3_dynamic_cap,
};

static const struct udevice_id rockchip_crypto_ids[] = {
	{
		.compatible = "rockchip,px30-crypto",
		.data = (ulong)&soc_data_base
	},
	{
		.compatible = "rockchip,rk1808-crypto",
		.data = (ulong)&soc_data_rk1808
	},
	{
		.compatible = "rockchip,rk3308-crypto",
		.data = (ulong)&soc_data_base
	},
	{
		.compatible = "rockchip,rv1126-crypto",
		.data = (ulong)&soc_data_base_sm
	},
	{
		.compatible = "rockchip,rk3568-crypto",
		.data = (ulong)&soc_data_base_sm
	},
	{
		.compatible = "rockchip,rk3588-crypto",
		.data = (ulong)&soc_data_base_sm
	},
	{
		.compatible = "rockchip,crypto-v3",
		.data = (ulong)&soc_data_cryptov3
	},
	{ }
};

U_BOOT_DRIVER(rockchip_crypto_v2) = {
	.name		= "rockchip_crypto_v2",
	.id		= UCLASS_CRYPTO,
	.of_match	= rockchip_crypto_ids,
	.ops		= &rockchip_crypto_ops,
	.probe		= rockchip_crypto_probe,
	.ofdata_to_platdata = rockchip_crypto_ofdata_to_platdata,
	.priv_auto_alloc_size = sizeof(struct rockchip_crypto_priv),
};
