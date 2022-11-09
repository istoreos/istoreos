// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <command.h>
#include <crypto.h>
#include <dm.h>
#include <u-boot/md5.h>
#include <u-boot/sha1.h>
#include <u-boot/sha256.h>
#include <u-boot/sha512.h>
#include <rockchip/crypto_fix_test_data.h>

#define PERF_TOTAL_SIZE			(128 * 1024 * 1024)
#define PERF_BUFF_SIZE			(4 * 1024 * 1024)

#define CALC_RATE_MPBS(bytes, ms)	(((bytes) / 1024) / (ms))

struct hash_test_data {
	const char	*algo_name;
	const char	*mode_name;
	u32		algo;
	const u8	*data;
	u32		data_len;
	const u8	*hash;
	u32		hash_len;
	const u8	*key;
	u32		key_len;
};

struct cipher_test_data {
	const char	*algo_name;
	const char	*mode_name;
	u32		algo;
	u32		mode;
	const u8	*key;
	const u8	*twk_key;
	u32		key_len;
	const u8	*iv;
	u32		iv_len;
	const u8	*plain;
	u32		plain_len;
	const u8	*cipher;
	u32		cipher_len;
	const u8	*aad;
	u32		aad_len;
	const u8	*tag;
	u32		tag_len;
};

struct rsa_test_data {
	const char	*algo_name;
	const char	*mode_name;
	u32		algo;
	const u8	*n;
	u32		n_len;
	const u8	*e;
	u32		e_len;
	const u8	*d;
	u32		d_len;
	const u8	*c;
	u32		c_len;
	const u8	*sign_in;
	u32		sign_in_len;
	const u8	*sign_out;
	u32		sign_out_len;
};

#define IS_MAC_MODE(mode)	((mode) == RK_MODE_CBC_MAC || \
				 (mode) == RK_MODE_CMAC)

#define IS_AE_MODE(mode)	((mode) == RK_MODE_CCM || \
				 (mode) == RK_MODE_GCM)
#define HASH_TEST(algo_type, data_in, hash_val) {\
	.algo_name = "HASH", \
	.mode_name = #algo_type, \
	.algo      = CRYPTO_##algo_type, \
	.data      = (data_in),\
	.data_len  = sizeof(data_in), \
	.hash      = (hash_val), \
	.hash_len  = sizeof(hash_val) \
}

#define HMAC_TEST(algo_type, data_in, hash_val, hmac_key) {\
	.algo_name = "HMAC", \
	.mode_name = #algo_type, \
	.algo      = CRYPTO_HMAC_##algo_type, \
	.data      = (data_in),\
	.data_len  = sizeof(data_in), \
	.hash      = (hash_val), \
	.hash_len  = sizeof(hash_val), \
	.key       = (hmac_key), \
	.key_len   = sizeof(hmac_key)\
}

#define CIPHER_XTS_TEST(algo_type, mode_type, key1, key2, iv_val, in, out) { \
	.algo_name  = #algo_type, \
	.mode_name  = #mode_type, \
	.algo       = CRYPTO_##algo_type,\
	.mode       = RK_MODE_##mode_type, \
	.key        = (key1), \
	.twk_key    = (key2), \
	.key_len    = sizeof(key1), \
	.iv         = (iv_val), \
	.iv_len     = sizeof(iv_val), \
	.plain      = (in), \
	.plain_len  = sizeof(in), \
	.cipher     = (out), \
	.cipher_len = sizeof(out) \
}

#define CIPHER_TEST(algo, mode, key, iv, plain, cipher) \
		CIPHER_XTS_TEST(algo, mode, key, NULL, iv, plain, cipher)

#define CIPHER_AE_TEST(algo_type, mode_type, key_val, iv_val, \
		       in, out, aad_val, tag_val) { \
	.algo_name  = #algo_type, \
	.mode_name  = #mode_type, \
	.algo       = CRYPTO_##algo_type,\
	.mode       = RK_MODE_##mode_type, \
	.key        = (key_val), \
	.key_len    = sizeof(key_val), \
	.iv         = (iv_val), \
	.iv_len     = sizeof(iv_val), \
	.plain      = (in), \
	.plain_len  = sizeof(in), \
	.cipher     = (out), \
	.cipher_len = sizeof(out), \
	.aad        = (aad_val), \
	.aad_len    = sizeof(aad_val), \
	.tag        = (tag_val), \
	.tag_len    = sizeof(tag_val), \
}

#define RSA_TEST(nbits, bn, be, bc, bd, in, out) { \
	.algo_name    = "RSA", \
	.mode_name    = #nbits, \
	.algo         = CRYPTO_RSA##nbits, \
	.n            = (bn), \
	.n_len        = sizeof(bn), \
	.e            = (be), \
	.e_len        = sizeof(be), \
	.d            = (bd), \
	.d_len        = sizeof(bd), \
	.c            = (bc), \
	.c_len        = sizeof(bc), \
	.sign_in      = (in), \
	.sign_in_len  = sizeof(in), \
	.sign_out     = (out), \
	.sign_out_len = sizeof(out) \
}

#define EMPTY_TEST() {}

const struct hash_test_data hash_data_set[] = {
	HASH_TEST(MD5,    foo_data, hash_md5),
	HASH_TEST(SHA1,   foo_data, hash_sha1),
	HASH_TEST(SHA256, foo_data, hash_sha256),
	HASH_TEST(SHA512, foo_data, hash_sha512),
	HASH_TEST(SM3,    foo_data, hash_sm3),

#if CONFIG_IS_ENABLED(ROCKCHIP_HMAC)
	EMPTY_TEST(),
	HMAC_TEST(MD5,    foo_data, hmac_md5,    hmac_key),
	HMAC_TEST(SHA1,   foo_data, hmac_sha1,   hmac_key),
	HMAC_TEST(SHA256, foo_data, hmac_sha256, hmac_key),
	HMAC_TEST(SHA512, foo_data, hmac_sha512, hmac_key),
	HMAC_TEST(SM3,    foo_data, hmac_sm3,    hmac_key),
#endif
};

const struct cipher_test_data cipher_data_set[] = {
#if CONFIG_IS_ENABLED(ROCKCHIP_CIPHER)
	CIPHER_TEST(DES, ECB, des_key, des_iv, foo_data, des_ecb_cipher),
	CIPHER_TEST(DES, CBC, des_key, des_iv, foo_data, des_cbc_cipher),
	CIPHER_TEST(DES, CFB, des_key, des_iv, foo_data, des_cfb_cipher),
	CIPHER_TEST(DES, OFB, des_key, des_iv, foo_data, des_ofb_cipher),

	EMPTY_TEST(),
	CIPHER_TEST(DES, ECB, tdes_key, tdes_iv, foo_data, tdes_ecb_cipher),
	CIPHER_TEST(DES, CBC, tdes_key, tdes_iv, foo_data, tdes_cbc_cipher),
	CIPHER_TEST(DES, CFB, tdes_key, tdes_iv, foo_data, tdes_cfb_cipher),
	CIPHER_TEST(DES, OFB, tdes_key, tdes_iv, foo_data, tdes_ofb_cipher),

	EMPTY_TEST(),
	CIPHER_TEST(AES, ECB, aes_key, aes_iv, foo_data, aes_ecb_cipher),
	CIPHER_TEST(AES, CBC, aes_key, aes_iv, foo_data, aes_cbc_cipher),
	CIPHER_TEST(AES, CFB, aes_key, aes_iv, foo_data, aes_cfb_cipher),
	CIPHER_TEST(AES, OFB, aes_key, aes_iv, foo_data, aes_ofb_cipher),
	CIPHER_TEST(AES, CTS, aes_key, aes_iv, foo_data, aes_cts_cipher),
	CIPHER_TEST(AES, CTR, aes_key, aes_iv, foo_data, aes_ctr_cipher),
	CIPHER_XTS_TEST(AES, XTS, aes_key, aes_twk_key,
			aes_iv, foo_data, aes_xts_cipher),
	CIPHER_TEST(AES, CBC_MAC, aes_key, aes_iv, foo_data, aes_cbc_mac),
	CIPHER_TEST(AES, CMAC, aes_key, aes_iv, foo_data, aes_cmac),
	CIPHER_AE_TEST(AES, CCM, aes_key, aes_ccm_iv, foo_data, aes_ccm_cipher,
		       ad_data, aes_ccm_tag),
	CIPHER_AE_TEST(AES, GCM, aes_key, aes_iv, foo_data, aes_gcm_cipher,
		       ad_data, aes_gcm_tag),

	EMPTY_TEST(),
	CIPHER_TEST(SM4, ECB, sm4_key, sm4_iv, foo_data, sm4_ecb_cipher),
	CIPHER_TEST(SM4, CBC, sm4_key, sm4_iv, foo_data, sm4_cbc_cipher),
	CIPHER_TEST(SM4, CFB, sm4_key, sm4_iv, foo_data, sm4_cfb_cipher),
	CIPHER_TEST(SM4, OFB, sm4_key, sm4_iv, foo_data, sm4_ofb_cipher),
	CIPHER_TEST(SM4, CTS, sm4_key, sm4_iv, foo_data, sm4_cts_cipher),
	CIPHER_TEST(SM4, CTR, sm4_key, sm4_iv, foo_data, sm4_ctr_cipher),
	CIPHER_XTS_TEST(SM4, XTS, sm4_key, sm4_twk_key,
			sm4_iv, foo_data, sm4_xts_cipher),
	CIPHER_TEST(SM4, CBC_MAC, sm4_key, sm4_iv, foo_data, sm4_cbc_mac),
	CIPHER_TEST(SM4, CMAC, sm4_key, sm4_iv, foo_data, sm4_cmac),
	CIPHER_AE_TEST(SM4, CCM, sm4_key, sm4_ccm_iv, foo_data, sm4_ccm_cipher,
		       ad_data, sm4_ccm_tag),
	CIPHER_AE_TEST(SM4, GCM, sm4_key, sm4_iv, foo_data, sm4_gcm_cipher,
		       ad_data, sm4_gcm_tag),
#else
	EMPTY_TEST(),
#endif
};

const struct rsa_test_data rsa_data_set[] = {
#if CONFIG_IS_ENABLED(ROCKCHIP_RSA)

#ifdef CONFIG_ROCKCHIP_CRYPTO_V1
	RSA_TEST(2048, rsa2048_n, rsa2048_e, rsa2048_c, rsa2048_d,
		 rsa2048_sign_in, rsa2048_sign_out),
#else
	RSA_TEST(4096, rsa4096_n, rsa4096_e, NULL, rsa4096_d,
		 rsa4096_sign_in, rsa4096_sign_out),
#endif

#else
	EMPTY_TEST(),
#endif
};

static void dump_hex(const char *name, const u8 *array, u32 len)
{
	int i;

	printf("[%s]: %uByte", name, len);
	for (i = 0; i < len; i++) {
		if (i % 32 == 0)
			printf("\n");
		printf("%02x ", array[i]);
	}
	printf("\n");
}

static inline void print_result_MBps(const char *algo_name,
				     const char *mode_name,
				     const char *crypt, ulong MBps,
				     const u8 *expect, const u8 *actual,
				     u32 len)
{
	if (memcmp(expect, actual, len) == 0) {
		printf("[%s] %-8s%-8s PASS    (%luMBps)\n",
		       algo_name, mode_name, crypt, MBps);
	} else {
		printf("[%s] %-8s%-8s FAIL\n",
		       algo_name, mode_name, crypt);
		dump_hex("expect", expect, len);
		dump_hex("actual", actual, len);
	}
}

static inline void print_result_ms(const char *algo_name, const char *mode_name,
				   const char *crypt, ulong time_cost,
				   const u8 *expect, const u8 *actual, u32 len)
{
	if (memcmp(expect, actual, len) == 0) {
		printf("[%s] %-8s%-8s PASS    (%lums)\n",
		       algo_name, mode_name, crypt, time_cost);
	} else {
		printf("[%s] %-8s%-8s FAIL\n",
		       algo_name, mode_name, crypt);
		dump_hex("expect", expect, len);
		dump_hex("actual", actual, len);
	}
}

int test_hash_perf(struct udevice *dev, u32 algo,
		   const u8 *key, u32 key_len, ulong *MBps)
{
	u32 total_size = PERF_TOTAL_SIZE;
	u32 data_size = PERF_BUFF_SIZE;
	sha_context ctx;
	u8 *data = NULL;
	u8 hash_out[64];
	int ret, i;

	*MBps = 0;

	ctx.algo = algo;
	ctx.length = total_size;

	data = (u8 *)memalign(CONFIG_SYS_CACHELINE_SIZE, data_size);
	if (!data) {
		printf("%s, %d: memalign %u error!\n",
		       __func__, __LINE__, data_size);
		return -EINVAL;
	}

	memset(data, 0xab, data_size);

	ulong start = get_timer(0);

	if (key)
		ret = crypto_hmac_init(dev, &ctx, (u8 *)key, key_len);
	else
		ret = crypto_sha_init(dev, &ctx);

	if (ret) {
		printf("crypto_sha_init error ret = %d!\n", ret);
		goto exit;
	}

	for (i = 0; i < total_size / data_size; i++) {
		ret = crypto_sha_update(dev, (u32 *)data, data_size);
		if (ret) {
			printf("crypto_sha_update error!\n");
			goto exit;
		}
	}

	ret = crypto_sha_final(dev, &ctx, hash_out);
	if (ret) {
		printf("crypto_sha_final error ret = %d!\n", ret);
		goto exit;
	}

	ulong time_cost = get_timer(start);

	*MBps = CALC_RATE_MPBS(total_size, time_cost);

exit:
	free(data);

	return ret;
}

int test_cipher_perf(struct udevice *dev, cipher_context *ctx,
		     ulong *MBps, bool enc)
{
	u32 total_size = PERF_TOTAL_SIZE;
	u32 data_size = PERF_BUFF_SIZE;
	u8 *plain = NULL, *cipher = NULL;
	u8 aad[128], tag[16];
	int ret = 0, i;

	*MBps = 0;

	plain = (u8 *)memalign(CONFIG_SYS_CACHELINE_SIZE, data_size);
	if (!plain) {
		printf("%s, %d: memalign %u error!\n",
		       __func__, __LINE__, data_size);
		return -EINVAL;
	}

	cipher = (u8 *)memalign(CONFIG_SYS_CACHELINE_SIZE, data_size);
	if (!cipher) {
		printf("%s, %d: memalign %u error!\n",
		       __func__, __LINE__, data_size);
		free(plain);
		return -EINVAL;
	}

	memset(plain, 0xab, data_size);
	memset(aad, 0xcb, sizeof(aad));

	ulong start = get_timer(0);

	for (i = 0; i < total_size / data_size; i++) {
		if (IS_MAC_MODE(ctx->mode))
			ret = crypto_mac(dev, ctx, plain, data_size, cipher);
		else if (IS_AE_MODE(ctx->mode))
			ret = crypto_ae(dev, ctx, plain, data_size,
					aad, sizeof(aad), cipher, tag);
		else
			ret = crypto_cipher(dev, ctx, plain, cipher,
					    data_size, enc);
		if (ret) {
			printf("%s, %d:crypto calc error! ret = %d\n",
			       __func__, __LINE__, ret);
			goto exit;
		}
	}

	ulong time_cost = get_timer(start);

	*MBps = CALC_RATE_MPBS(total_size, time_cost);
exit:
	free(plain);
	free(cipher);

	return ret;
}

int test_hash_result(void)
{
	const struct hash_test_data *test_data = NULL;
	sha_context csha_ctx;
	struct udevice *dev;
	unsigned int i;
	u8 out[64];
	int ret;

	printf("\n=================== hash & hmac test ===================\n");

	for (i = 0; i < ARRAY_SIZE(hash_data_set); i++) {
		test_data = &hash_data_set[i];
		if (test_data->algo == 0) {
			printf("\n");
			continue;
		}

		dev = crypto_get_device(test_data->algo);
		if (!dev) {
			printf("[%s] %-16s unsupported!!!\n",
			       test_data->algo_name,
			       test_data->mode_name);
			continue;
		}

		csha_ctx.algo   = test_data->algo;
		csha_ctx.length = test_data->data_len;

		memset(out, 0x00, sizeof(out));
		if (test_data->key) {
			ret = crypto_hmac_init(dev, &csha_ctx,
					       (u8 *)test_data->key,
					       test_data->key_len);
			ret |= crypto_hmac_update(dev, (void *)test_data->data,
						  test_data->data_len);
			ret |= crypto_hmac_final(dev, &csha_ctx, out);
			if (ret) {
				printf("hmac calc error ret = %d\n", ret);
				goto error;
			}
		} else {
			ret = crypto_sha_init(dev, &csha_ctx);
			ret |= crypto_sha_update(dev, (void *)test_data->data,
						 test_data->data_len);
			ret |= crypto_sha_final(dev, &csha_ctx, out);
			if (ret) {
				printf("hash calc error ret = %d\n", ret);
				goto error;
			}
		}

		ulong MBps = 0;

		test_hash_perf(dev, test_data->algo,
			       test_data->key, test_data->key_len, &MBps);
		print_result_MBps(test_data->algo_name, test_data->mode_name,
				  "", MBps, test_data->hash, out,
				  test_data->hash_len);
		printf("+++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	}

	return 0;
error:
	printf("%s %s test error!\n",
	       test_data->algo_name, test_data->mode_name);
	return ret;
}

int test_cipher_result(void)
{
	const struct cipher_test_data *test_data = NULL;
	struct udevice *dev;
	cipher_context ctx;
	u8 out[256], tag[16];
	int ret;
	u32 i;

	printf("\n===================== cipher test ======================\n");

	for (i = 0; i < ARRAY_SIZE(cipher_data_set); i++) {
		test_data = &cipher_data_set[i];
		if (test_data->algo == 0) {
			printf("\n");
			continue;
		}

		dev = crypto_get_device(test_data->algo);
		if (!dev) {
			printf("[%s] %-16s unsupported!!!\n",
			       test_data->algo_name, test_data->mode_name);
			continue;
		}

		memset(&ctx, 0x00, sizeof(ctx));

		ctx.algo    = test_data->algo;
		ctx.mode    = test_data->mode;
		ctx.key     = test_data->key;
		ctx.twk_key = test_data->twk_key;
		ctx.key_len = test_data->key_len;
		ctx.iv      = test_data->iv;
		ctx.iv_len  = test_data->iv_len;

		ulong MBps = 0;

		test_cipher_perf(dev, &ctx, &MBps, true);

		/* AES/SM4 mac */
		if (IS_MAC_MODE(ctx.mode))
			ret = crypto_mac(dev, &ctx, test_data->plain,
					 test_data->plain_len, out);
		else if (IS_AE_MODE(ctx.mode))
			ret = crypto_ae(dev, &ctx,
					test_data->plain, test_data->plain_len,
					test_data->aad, test_data->aad_len,
					out, tag);
		else
			ret = crypto_cipher(dev, &ctx, test_data->plain,
					    out, test_data->plain_len, true);
		if (ret)
			goto error;

		if (test_data->tag &&
		    memcmp(test_data->tag, tag, test_data->tag_len) != 0) {
			printf("tag mismatch!!!\n");
			dump_hex("expect", test_data->tag, test_data->tag_len);
			dump_hex("actual", tag, test_data->tag_len);
			goto error;
		}

		print_result_MBps(test_data->algo_name, test_data->mode_name,
				  "encrypt", MBps, test_data->cipher, out,
				  test_data->cipher_len);

		if (!IS_MAC_MODE(ctx.mode) && !IS_AE_MODE(ctx.mode)) {
			test_cipher_perf(dev, &ctx, &MBps, false);
			ret = crypto_cipher(dev, &ctx, test_data->cipher,
					    out, test_data->cipher_len, false);
			if (ret)
				goto error;

			print_result_MBps(test_data->algo_name,
					  test_data->mode_name,
					  "decrypt", MBps,
					  test_data->plain, out,
					  test_data->plain_len);
		}
		printf("+++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	}
	return 0;
error:
	printf("%s %s test error, ret = %d!\n",
	       test_data->algo_name, test_data->mode_name, ret);
	return ret;
}

int test_rsa_result(void)
{
	const struct rsa_test_data *test_data = NULL;
	u8 *hard_out = NULL, *e_tmp;
	u32 data_size = 4096 / 8;
	ulong start, time_cost;
	struct udevice *dev;
	rsa_key rsa_key;
	int ret, i;

	hard_out = (u8 *)memalign(CONFIG_SYS_CACHELINE_SIZE, data_size);
	if (!hard_out) {
		printf("%s, %d: memalign %u error!\n",
		       __func__, __LINE__, data_size);
		return -EINVAL;
	}

	e_tmp = (u8 *)memalign(CONFIG_SYS_CACHELINE_SIZE, data_size);
	if (!e_tmp) {
		printf("%s, %d: memalign %u error!\n",
		       __func__, __LINE__, data_size);
		return -EINVAL;
	}

	printf("\n====================== rsa test ========================\n");
	for (i = 0; i < ARRAY_SIZE(rsa_data_set); i++) {
		test_data = &rsa_data_set[i];
		if (test_data->algo == 0) {
			printf("\n");
			continue;
		}

		dev = crypto_get_device(test_data->algo);
		if (!dev) {
			printf("[%s] %-16s unsupported!!!\n",
			       test_data->algo_name, test_data->mode_name);
			continue;
		}

		/* sign test */
		memset(&rsa_key, 0x00, sizeof(rsa_key));
		rsa_key.algo = test_data->algo;
		rsa_key.n = (u32 *)test_data->n;
		rsa_key.e = (u32 *)test_data->d;
#ifdef CONFIG_ROCKCHIP_CRYPTO_V1
		rsa_key.c = (u32 *)test_data->c;
#endif

		start = get_timer(0);
		ret = crypto_rsa_verify(dev, &rsa_key,
					(u8 *)test_data->sign_in, hard_out);
		if (ret) {
			printf("sign test error, ret = %d\n", ret);
			goto error;
		}
		time_cost = get_timer(start);
		print_result_ms(test_data->algo_name, test_data->mode_name,
				"sign", time_cost, test_data->sign_out,
				hard_out, test_data->n_len);

		/* verify test */
		memset(&rsa_key, 0x00, sizeof(rsa_key));
		memset(e_tmp, 0x00, data_size);
		memcpy(e_tmp, test_data->e, test_data->e_len);
		rsa_key.algo = test_data->algo;
		rsa_key.n = (u32 *)test_data->n;
		rsa_key.e = (u32 *)e_tmp;
#ifdef CONFIG_ROCKCHIP_CRYPTO_V1
		rsa_key.c = (u32 *)test_data->c;
#endif

		start = get_timer(0);
		ret = crypto_rsa_verify(dev, &rsa_key,
					(u8 *)test_data->sign_out, hard_out);
		if (ret) {
			printf("verify test error, ret = %d\n", ret);
			goto error;
		}
		time_cost = get_timer(start);

		print_result_ms(test_data->algo_name, test_data->mode_name,
				"verify", time_cost, test_data->sign_in,
				hard_out, test_data->n_len);

		printf("+++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	}

	free(hard_out);
	free(e_tmp);

	return 0;
error:
	free(hard_out);
	free(e_tmp);
	printf("%s %s test error!\n",
	       test_data->algo_name, test_data->mode_name);
	return ret;
}

static int test_all_result(void)
{
	int ret = 0;

	ret = test_hash_result();
	if (ret)
		goto exit;

	ret = test_cipher_result();
	if (ret)
		goto exit;

	ret = test_rsa_result();
	if (ret)
		goto exit;

exit:
	return 0;
}

static int do_crypto(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	return test_all_result();
}

U_BOOT_CMD(
	crypto, 1, 1, do_crypto,
	"crypto test",
	""
);
