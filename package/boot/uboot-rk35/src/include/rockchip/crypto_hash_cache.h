/* SPDX-License-Identifier:     GPL-2.0+ */
/*
 * (C) Copyright 2020 Rockchip Electronics Co., Ltd
 */

#ifndef _CRYPTO_HASH_CACHE_H_
#define _CRYPTO_HASH_CACHE_H_

#define	HASH_CACHE_SIZE		8192
#define	CIPHER_CACHE_SIZE	8192

typedef int (*crypto_hash_calc)(void *hw_data, const u8 *data, u32 data_len,
				u8 *started_flag, u8 is_last);

struct crypto_hash_cache {
	crypto_hash_calc	direct_calc;	/* hardware hash callback*/
	void			*user_data;
	void			*cache;		/* virt addr for hash src data*/
	u32			cache_size;	/* data in cached size */
	u32			data_align;
	u32			len_align;
	u32			left_len;	/* left data to calc */
	u8			is_started;	/* start or restart */
	u8			use_cache;	/* is use cache or not*/
	u8			reserved[2];
};

struct crypto_hash_cache *crypto_hash_cache_alloc(crypto_hash_calc direct_calc,
						  void *user_data, u32 total,
						  u32 data_align,
						  u32 len_align);
void crypto_hash_cache_free(struct crypto_hash_cache *hash_cache);
int crypto_hash_update_with_cache(struct crypto_hash_cache *hash_cache,
				  const u8 *data, u32 data_len);
void crypto_flush_cacheline(ulong addr, ulong size);

#endif
