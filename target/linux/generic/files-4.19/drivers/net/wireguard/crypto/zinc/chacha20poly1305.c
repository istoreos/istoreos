// SPDX-License-Identifier: GPL-2.0 OR MIT
/*
 * Copyright (C) 2015-2019 Jason A. Donenfeld <Jason@zx2c4.com>. All Rights Reserved.
 *
 * This is an implementation of the ChaCha20Poly1305 AEAD construction.
 *
 * Information: https://tools.ietf.org/html/rfc8439
 */

#include <zinc/chacha20poly1305.h>
#include <zinc/chacha20.h>
#include <zinc/poly1305.h>
#include "selftest/run.h"

#include <asm/unaligned.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <crypto/scatterwalk.h> // For blkcipher_walk.

static const u8 pad0[CHACHA20_BLOCK_SIZE] = { 0 };

static inline void
__chacha20poly1305_encrypt(u8 *dst, const u8 *src, const size_t src_len,
			   const u8 *ad, const size_t ad_len, const u64 nonce,
			   const u8 key[CHACHA20POLY1305_KEY_SIZE],
			   simd_context_t *simd_context)
{
	struct poly1305_ctx poly1305_state;
	struct chacha20_ctx chacha20_state;
	union {
		u8 block0[POLY1305_KEY_SIZE];
		__le64 lens[2];
	} b = { { 0 } };

	chacha20_init(&chacha20_state, key, nonce);
	chacha20(&chacha20_state, b.block0, b.block0, sizeof(b.block0),
		 simd_context);
	poly1305_init(&poly1305_state, b.block0);

	poly1305_update(&poly1305_state, ad, ad_len, simd_context);
	poly1305_update(&poly1305_state, pad0, (0x10 - ad_len) & 0xf,
			simd_context);

	chacha20(&chacha20_state, dst, src, src_len, simd_context);

	poly1305_update(&poly1305_state, dst, src_len, simd_context);
	poly1305_update(&poly1305_state, pad0, (0x10 - src_len) & 0xf,
			simd_context);

	b.lens[0] = cpu_to_le64(ad_len);
	b.lens[1] = cpu_to_le64(src_len);
	poly1305_update(&poly1305_state, (u8 *)b.lens, sizeof(b.lens),
			simd_context);

	poly1305_final(&poly1305_state, dst + src_len, simd_context);

	memzero_explicit(&chacha20_state, sizeof(chacha20_state));
	memzero_explicit(&b, sizeof(b));
}

void chacha20poly1305_encrypt(u8 *dst, const u8 *src, const size_t src_len,
			      const u8 *ad, const size_t ad_len,
			      const u64 nonce,
			      const u8 key[CHACHA20POLY1305_KEY_SIZE])
{
	simd_context_t simd_context;

	simd_get(&simd_context);
	__chacha20poly1305_encrypt(dst, src, src_len, ad, ad_len, nonce, key,
				   &simd_context);
	simd_put(&simd_context);
}

bool chacha20poly1305_encrypt_sg_inplace(struct scatterlist *src,
					 const size_t src_len,
					 const u8 *ad, const size_t ad_len,
					 const u64 nonce,
					 const u8 key[CHACHA20POLY1305_KEY_SIZE],
					 simd_context_t *simd_context)
{
	struct poly1305_ctx poly1305_state;
	struct chacha20_ctx chacha20_state;
	struct sg_mapping_iter miter;
	size_t partial = 0;
	ssize_t sl;
	union {
		u8 chacha20_stream[CHACHA20_BLOCK_SIZE];
		u8 block0[POLY1305_KEY_SIZE];
		u8 mac[POLY1305_MAC_SIZE];
		__le64 lens[2];
	} b __aligned(16) = { { 0 } };

	if (WARN_ON(src_len > INT_MAX))
		return false;

	chacha20_init(&chacha20_state, key, nonce);
	chacha20(&chacha20_state, b.block0, b.block0, sizeof(b.block0),
		 simd_context);
	poly1305_init(&poly1305_state, b.block0);

	poly1305_update(&poly1305_state, ad, ad_len, simd_context);
	poly1305_update(&poly1305_state, pad0, (0x10 - ad_len) & 0xf,
			simd_context);

	sg_miter_start(&miter, src, sg_nents(src), SG_MITER_TO_SG | SG_MITER_ATOMIC);
	for (sl = src_len; sl > 0 && sg_miter_next(&miter); sl -= miter.length) {
		u8 *addr = miter.addr;
		size_t length = min_t(size_t, sl, miter.length);

		if (unlikely(partial)) {
			size_t l = min(length, CHACHA20_BLOCK_SIZE - partial);

			crypto_xor(addr, b.chacha20_stream + partial, l);
			partial = (partial + l) & (CHACHA20_BLOCK_SIZE - 1);

			addr += l;
			length -= l;
		}

		if (likely(length >= CHACHA20_BLOCK_SIZE || length == sl)) {
			size_t l = length;

			if (unlikely(length < sl))
				l &= ~(CHACHA20_BLOCK_SIZE - 1);
			chacha20(&chacha20_state, addr, addr, l, simd_context);
			addr += l;
			length -= l;
		}

		if (unlikely(length > 0)) {
			chacha20(&chacha20_state, b.chacha20_stream, pad0,
				 CHACHA20_BLOCK_SIZE, simd_context);
			crypto_xor(addr, b.chacha20_stream, length);
			partial = length;
		}

		poly1305_update(&poly1305_state, miter.addr,
				min_t(size_t, sl, miter.length), simd_context);

		simd_relax(simd_context);
	}

	poly1305_update(&poly1305_state, pad0, (0x10 - src_len) & 0xf,
			simd_context);

	b.lens[0] = cpu_to_le64(ad_len);
	b.lens[1] = cpu_to_le64(src_len);
	poly1305_update(&poly1305_state, (u8 *)b.lens, sizeof(b.lens),
			simd_context);

	if (likely(sl <= -POLY1305_MAC_SIZE))
		poly1305_final(&poly1305_state, miter.addr + miter.length + sl,
			       simd_context);

	sg_miter_stop(&miter);

	if (unlikely(sl > -POLY1305_MAC_SIZE)) {
		poly1305_final(&poly1305_state, b.mac, simd_context);
		scatterwalk_map_and_copy(b.mac, src, src_len, sizeof(b.mac), 1);
	}

	memzero_explicit(&chacha20_state, sizeof(chacha20_state));
	memzero_explicit(&b, sizeof(b));
	return true;
}

static inline bool
__chacha20poly1305_decrypt(u8 *dst, const u8 *src, const size_t src_len,
			   const u8 *ad, const size_t ad_len, const u64 nonce,
			   const u8 key[CHACHA20POLY1305_KEY_SIZE],
			   simd_context_t *simd_context)
{
	struct poly1305_ctx poly1305_state;
	struct chacha20_ctx chacha20_state;
	int ret;
	size_t dst_len;
	union {
		u8 block0[POLY1305_KEY_SIZE];
		u8 mac[POLY1305_MAC_SIZE];
		__le64 lens[2];
	} b = { { 0 } };

	if (unlikely(src_len < POLY1305_MAC_SIZE))
		return false;

	chacha20_init(&chacha20_state, key, nonce);
	chacha20(&chacha20_state, b.block0, b.block0, sizeof(b.block0),
		 simd_context);
	poly1305_init(&poly1305_state, b.block0);

	poly1305_update(&poly1305_state, ad, ad_len, simd_context);
	poly1305_update(&poly1305_state, pad0, (0x10 - ad_len) & 0xf,
			simd_context);

	dst_len = src_len - POLY1305_MAC_SIZE;
	poly1305_update(&poly1305_state, src, dst_len, simd_context);
	poly1305_update(&poly1305_state, pad0, (0x10 - dst_len) & 0xf,
			simd_context);

	b.lens[0] = cpu_to_le64(ad_len);
	b.lens[1] = cpu_to_le64(dst_len);
	poly1305_update(&poly1305_state, (u8 *)b.lens, sizeof(b.lens),
			simd_context);

	poly1305_final(&poly1305_state, b.mac, simd_context);

	ret = crypto_memneq(b.mac, src + dst_len, POLY1305_MAC_SIZE);
	if (likely(!ret))
		chacha20(&chacha20_state, dst, src, dst_len, simd_context);

	memzero_explicit(&chacha20_state, sizeof(chacha20_state));
	memzero_explicit(&b, sizeof(b));

	return !ret;
}

bool chacha20poly1305_decrypt(u8 *dst, const u8 *src, const size_t src_len,
			      const u8 *ad, const size_t ad_len,
			      const u64 nonce,
			      const u8 key[CHACHA20POLY1305_KEY_SIZE])
{
	simd_context_t simd_context, ret;

	simd_get(&simd_context);
	ret = __chacha20poly1305_decrypt(dst, src, src_len, ad, ad_len, nonce,
					 key, &simd_context);
	simd_put(&simd_context);
	return ret;
}

bool chacha20poly1305_decrypt_sg_inplace(struct scatterlist *src,
					 size_t src_len,
					 const u8 *ad, const size_t ad_len,
					 const u64 nonce,
					 const u8 key[CHACHA20POLY1305_KEY_SIZE],
					 simd_context_t *simd_context)
{
	struct poly1305_ctx poly1305_state;
	struct chacha20_ctx chacha20_state;
	struct sg_mapping_iter miter;
	size_t partial = 0;
	ssize_t sl;
	union {
		u8 chacha20_stream[CHACHA20_BLOCK_SIZE];
		u8 block0[POLY1305_KEY_SIZE];
		struct {
			u8 read_mac[POLY1305_MAC_SIZE];
			u8 computed_mac[POLY1305_MAC_SIZE];
		};
		__le64 lens[2];
	} b __aligned(16) = { { 0 } };
	bool ret = false;

	if (unlikely(src_len < POLY1305_MAC_SIZE || WARN_ON(src_len > INT_MAX)))
		return ret;
	src_len -= POLY1305_MAC_SIZE;

	chacha20_init(&chacha20_state, key, nonce);
	chacha20(&chacha20_state, b.block0, b.block0, sizeof(b.block0),
		 simd_context);
	poly1305_init(&poly1305_state, b.block0);

	poly1305_update(&poly1305_state, ad, ad_len, simd_context);
	poly1305_update(&poly1305_state, pad0, (0x10 - ad_len) & 0xf,
			simd_context);

	sg_miter_start(&miter, src, sg_nents(src), SG_MITER_TO_SG | SG_MITER_ATOMIC);
	for (sl = src_len; sl > 0 && sg_miter_next(&miter); sl -= miter.length) {
		u8 *addr = miter.addr;
		size_t length = min_t(size_t, sl, miter.length);

		poly1305_update(&poly1305_state, addr, length, simd_context);

		if (unlikely(partial)) {
			size_t l = min(length, CHACHA20_BLOCK_SIZE - partial);

			crypto_xor(addr, b.chacha20_stream + partial, l);
			partial = (partial + l) & (CHACHA20_BLOCK_SIZE - 1);

			addr += l;
			length -= l;
		}

		if (likely(length >= CHACHA20_BLOCK_SIZE || length == sl)) {
			size_t l = length;

			if (unlikely(length < sl))
				l &= ~(CHACHA20_BLOCK_SIZE - 1);
			chacha20(&chacha20_state, addr, addr, l, simd_context);
			addr += l;
			length -= l;
		}

		if (unlikely(length > 0)) {
			chacha20(&chacha20_state, b.chacha20_stream, pad0,
				 CHACHA20_BLOCK_SIZE, simd_context);
			crypto_xor(addr, b.chacha20_stream, length);
			partial = length;
		}

		simd_relax(simd_context);
	}

	poly1305_update(&poly1305_state, pad0, (0x10 - src_len) & 0xf,
			simd_context);

	b.lens[0] = cpu_to_le64(ad_len);
	b.lens[1] = cpu_to_le64(src_len);
	poly1305_update(&poly1305_state, (u8 *)b.lens, sizeof(b.lens),
			simd_context);

	if (likely(sl <= -POLY1305_MAC_SIZE)) {
		poly1305_final(&poly1305_state, b.computed_mac, simd_context);
		ret = !crypto_memneq(b.computed_mac,
				     miter.addr + miter.length + sl,
				     POLY1305_MAC_SIZE);
	}

	sg_miter_stop(&miter);

	if (unlikely(sl > -POLY1305_MAC_SIZE)) {
		poly1305_final(&poly1305_state, b.computed_mac, simd_context);
		scatterwalk_map_and_copy(b.read_mac, src, src_len,
					 sizeof(b.read_mac), 0);
		ret = !crypto_memneq(b.read_mac, b.computed_mac,
				     POLY1305_MAC_SIZE);

	}

	memzero_explicit(&chacha20_state, sizeof(chacha20_state));
	memzero_explicit(&b, sizeof(b));
	return ret;
}

void xchacha20poly1305_encrypt(u8 *dst, const u8 *src, const size_t src_len,
			       const u8 *ad, const size_t ad_len,
			       const u8 nonce[XCHACHA20POLY1305_NONCE_SIZE],
			       const u8 key[CHACHA20POLY1305_KEY_SIZE])
{
	simd_context_t simd_context;
	u32 derived_key[CHACHA20_KEY_WORDS] __aligned(16);

	simd_get(&simd_context);
	hchacha20(derived_key, nonce, key, &simd_context);
	cpu_to_le32_array(derived_key, ARRAY_SIZE(derived_key));
	__chacha20poly1305_encrypt(dst, src, src_len, ad, ad_len,
				   get_unaligned_le64(nonce + 16),
				   (u8 *)derived_key, &simd_context);
	memzero_explicit(derived_key, CHACHA20POLY1305_KEY_SIZE);
	simd_put(&simd_context);
}

bool xchacha20poly1305_decrypt(u8 *dst, const u8 *src, const size_t src_len,
			       const u8 *ad, const size_t ad_len,
			       const u8 nonce[XCHACHA20POLY1305_NONCE_SIZE],
			       const u8 key[CHACHA20POLY1305_KEY_SIZE])
{
	bool ret;
	simd_context_t simd_context;
	u32 derived_key[CHACHA20_KEY_WORDS] __aligned(16);

	simd_get(&simd_context);
	hchacha20(derived_key, nonce, key, &simd_context);
	cpu_to_le32_array(derived_key, ARRAY_SIZE(derived_key));
	ret = __chacha20poly1305_decrypt(dst, src, src_len, ad, ad_len,
					 get_unaligned_le64(nonce + 16),
					 (u8 *)derived_key, &simd_context);
	memzero_explicit(derived_key, CHACHA20POLY1305_KEY_SIZE);
	simd_put(&simd_context);
	return ret;
}

#include "selftest/chacha20poly1305.c"

#ifndef COMPAT_ZINC_IS_A_MODULE
int __init chacha20poly1305_mod_init(void)
#else
static int __init mod_init(void)
#endif
{
	if (!selftest_run("chacha20poly1305", chacha20poly1305_selftest,
			  NULL, 0))
		return -ENOTRECOVERABLE;
	return 0;
}

#ifdef COMPAT_ZINC_IS_A_MODULE
static void __exit mod_exit(void)
{
}

module_init(mod_init);
module_exit(mod_exit);
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("ChaCha20Poly1305 AEAD construction");
MODULE_AUTHOR("Jason A. Donenfeld <Jason@zx2c4.com>");
#endif
