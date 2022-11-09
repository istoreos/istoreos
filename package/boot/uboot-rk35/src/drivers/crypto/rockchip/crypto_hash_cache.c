// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2020 Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <clk.h>
#include <crypto.h>

#include <rockchip/crypto_hash_cache.h>

static int hash_cache_calc(struct crypto_hash_cache *hash_cache, const u8 *data,
			   u32 data_len, u8 is_last)
{
	crypto_hash_calc direct_calc = hash_cache->direct_calc;
	int ret = 0;

	if (!hash_cache->cache) {
		hash_cache->cache = (u8 *)memalign(CONFIG_SYS_CACHELINE_SIZE,
						   HASH_CACHE_SIZE);
		if (!hash_cache->cache)
			goto error;

		hash_cache->cache_size = 0;
	}

	while (1) {
		u32 tmp_len = 0;

		if (hash_cache->cache_size + data_len <= HASH_CACHE_SIZE) {
			/* copy to cache */
			debug("%s, %d: copy to cache %u\n",
			      __func__, __LINE__, data_len);
			memcpy(hash_cache->cache + hash_cache->cache_size, data,
			       data_len);
			hash_cache->cache_size += data_len;

			/* if last one calc cache immediately */
			if (is_last) {
				debug("%s, %d: last one calc cache %u\n",
				      __func__, __LINE__,
				      hash_cache->cache_size);

				ret = direct_calc(hash_cache->user_data,
						  hash_cache->cache,
						  hash_cache->cache_size,
						  &hash_cache->is_started,
						  is_last);
				if (ret)
					goto error;
			}
			break;
		}

		/* 1. make cache be full */
		/* 2. calc cache */
		tmp_len = HASH_CACHE_SIZE - hash_cache->cache_size;
		debug("%s, %d: make cache be full %u\n",
		      __func__, __LINE__, tmp_len);
		memcpy(hash_cache->cache + hash_cache->cache_size,
		       data, tmp_len);

		ret = direct_calc(hash_cache->user_data, hash_cache->cache,
				  HASH_CACHE_SIZE, &hash_cache->is_started, 0);
		if (ret)
			goto error;

		data += tmp_len;
		data_len -= tmp_len;
		hash_cache->cache_size = 0;
	}

	return ret;
error:
	return -EINVAL;
}

void crypto_flush_cacheline(ulong addr, ulong size)
{
	ulong alignment = CONFIG_SYS_CACHELINE_SIZE;
	ulong aligned_input, aligned_len;

	if (!addr || !size)
		return;

	/* Must flush dcache before crypto DMA fetch data region */
	aligned_input = round_down(addr, alignment);
	aligned_len = round_up(size + (addr - aligned_input), alignment);
	flush_cache(aligned_input, aligned_len);
}

struct crypto_hash_cache *crypto_hash_cache_alloc(crypto_hash_calc direct_calc,
						  void *user_data, u32 total,
						  u32 data_align, u32 len_align)
{
	struct crypto_hash_cache *hash_cache = NULL;

	if (!direct_calc)
		return NULL;

	hash_cache = malloc(sizeof(struct crypto_hash_cache));
	if (!hash_cache)
		return NULL;

	memset(hash_cache, 0x00, sizeof(*hash_cache));

	hash_cache->direct_calc = direct_calc;
	hash_cache->user_data   = user_data;
	hash_cache->data_align  = data_align;
	hash_cache->len_align   = len_align;
	hash_cache->left_len	= total;

	return hash_cache;
}

void crypto_hash_cache_free(struct crypto_hash_cache *hash_cache)
{
	if (!hash_cache)
		return;

	if (hash_cache->cache)
		free(hash_cache->cache);

	free(hash_cache);
}

int crypto_hash_update_with_cache(struct crypto_hash_cache *hash_cache,
				  const u8 *data, u32 data_len)
{
	crypto_hash_calc direct_calc = hash_cache->direct_calc;
	const u8 *direct_data = NULL, *cache_data = NULL;
	u32 direct_data_len = 0, cache_data_len = 0;
	u8 is_last = 0;
	int ret = 0;

	if (hash_cache->left_len < data_len)
		goto error;

	is_last = hash_cache->left_len == data_len ? 1 : 0;

	if (!hash_cache->use_cache &&
	    IS_ALIGNED((ulong)data, hash_cache->data_align)) {
		direct_data = data;
		if (IS_ALIGNED(data_len, hash_cache->len_align) || is_last) {
			/* calc all directly */
			debug("%s, %d: calc all directly\n",
			      __func__, __LINE__);
			direct_data_len = data_len;
		} else {
			/* calc some directly calc some in cache */
			debug("%s, %d: calc some directly calc some in cache\n",
			      __func__, __LINE__);
			direct_data_len = round_down((ulong)data_len,
						     hash_cache->len_align);
			cache_data = direct_data + direct_data_len;
			cache_data_len = data_len % hash_cache->len_align;
			hash_cache->use_cache = 1;
		}
	} else {
		/* calc all in cache */
		debug("%s, %d: calc all in cache\n", __func__, __LINE__);
		cache_data = data;
		cache_data_len = data_len;
		hash_cache->use_cache = 1;
	}

	if (direct_data_len) {
		debug("%s, %d: calc direct data %u\n",
		      __func__, __LINE__, direct_data_len);
		ret = direct_calc(hash_cache->user_data,
				  direct_data, direct_data_len,
				  &hash_cache->is_started, is_last);
		if (ret)
			goto error;
		hash_cache->left_len -= direct_data_len;
	}

	if (cache_data_len) {
		debug("%s, %d: calc cache data %u\n",
		      __func__, __LINE__, cache_data_len);
		ret = hash_cache_calc(hash_cache, cache_data,
				      cache_data_len, is_last);
		if (ret)
			goto error;
		hash_cache->left_len -= cache_data_len;
	}

	return 0;
error:
	if (hash_cache->cache) {
		free(hash_cache->cache);
		hash_cache->cache = NULL;
	}

	return -EINVAL;
}
