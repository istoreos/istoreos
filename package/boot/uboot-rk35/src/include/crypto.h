/* SPDX-License-Identifier:     GPL-2.0+ */
/*
 * (C) Copyright 2019 Rockchip Electronics Co., Ltd
 */

#ifndef _CORE_CRYPTO_H_
#define _CORE_CRYPTO_H_

#include <common.h>
#include <dm.h>
#include <image.h>
#include <u-boot/sha1.h>

/* Algorithms/capability of crypto, works together with crypto_algo_nbits() */
#define CRYPTO_MD5		BIT(0)
#define CRYPTO_SHA1		BIT(1)
#define CRYPTO_SHA256		BIT(2)
#define CRYPTO_SHA512		BIT(3)
#define CRYPTO_SM3		BIT(4)

#define CRYPTO_RSA512		BIT(10)
#define CRYPTO_RSA1024		BIT(11)
#define CRYPTO_RSA2048		BIT(12)
#define CRYPTO_RSA3072		BIT(13)
#define CRYPTO_RSA4096		BIT(14)

#define CRYPTO_DES		BIT(20)
#define CRYPTO_AES		BIT(21)
#define CRYPTO_SM4		BIT(22)

#define CRYPTO_HMAC_MD5		BIT(25)
#define CRYPTO_HMAC_SHA1	BIT(26)
#define CRYPTO_HMAC_SHA256	BIT(27)
#define CRYPTO_HMAC_SHA512	BIT(28)
#define CRYPTO_HMAC_SM3		BIT(29)

#define BYTE2WORD(bytes)	((bytes) / 4)
#define BITS2BYTE(nbits)	((nbits) / 8)
#define BITS2WORD(nbits)	((nbits) / 32)

enum RK_CRYPTO_MODE {
	RK_MODE_ECB = 0,
	RK_MODE_CBC,
	RK_MODE_CTS,
	RK_MODE_CTR,
	RK_MODE_CFB,
	RK_MODE_OFB,
	RK_MODE_XTS,
	RK_MODE_CCM,
	RK_MODE_GCM,
	RK_MODE_CMAC,
	RK_MODE_CBC_MAC,
	RK_MODE_MAX
};

typedef struct {
	u32 algo;	/* Algorithm: CRYPTO_MD5/CRYPTO_SHA1/CRYPTO_RSA2048... */
	u32 length;	/* Data total length */

} sha_context;

typedef struct {
	u32 algo;	/* Algorithm: CRYPTO_MD5/CRYPTO_SHA1/CRYPTO_RSA2048... */
	u32 *n;		/* Public key factor N */
	u32 *e;		/* Public key factor E */
	u32 *c;		/* Optional, a accelerate factor for some crypto */
} rsa_key;

typedef struct {
	u32		algo;
	u32		mode;
	const u8	*key;
	const u8	*twk_key;
	u32		key_len;
	const u8	*iv;
	u32		iv_len;
} cipher_context;

struct dm_crypto_ops {
	/* Hardware algorithm capability */
	u32 (*capability)(struct udevice *dev);

	/* SHA init/update/final */
	int (*sha_init)(struct udevice *dev, sha_context *ctx);
	int (*sha_update)(struct udevice *dev, u32 *input, u32 len);
	int (*sha_final)(struct udevice *dev, sha_context *ctx, u8 *output);

	/* RSA verify */
	int (*rsa_verify)(struct udevice *dev, rsa_key *ctx,
			  u8 *sign, u8 *output);
	/* HMAC init/update/final */
	int (*hmac_init)(struct udevice *dev, sha_context *ctx,
			 u8 *key, u32 key_len);
	int (*hmac_update)(struct udevice *dev, u32 *input, u32 len);
	int (*hmac_final)(struct udevice *dev, sha_context *ctx, u8 *output);

	/* cipher encryption and decryption */
	int (*cipher_crypt)(struct udevice *dev, cipher_context *ctx,
			    const u8 *in, u8 *out, u32 len, bool enc);

	/* cipher mac cmac&cbc_mac */
	int (*cipher_mac)(struct udevice *dev, cipher_context *ctx,
			  const u8 *in, u32 len, u8 *tag);

	/* cipher aes ccm&gcm */
	int (*cipher_ae)(struct udevice *dev, cipher_context *ctx,
			 const u8 *in, u32 len, const u8 *aad, u32 aad_len,
			 u8 *out, u8 *tag);

};

/**
 * crypto_algo_nbits() - Get algorithm bits accroding to algorithm
 * @capability: expected algorithm capability, eg. CRYPTO_MD5/RSA2048...
 *
 * @return algorithm bits
 */
u32 crypto_algo_nbits(u32 algo);

/**
 * crypto_get_device() - Get crypto device by capability
 * @capability: expected algorithm capability, eg. CRYPTO_MD5/RSA2048...
 *
 * @return dev on success, otherwise NULL
 */
struct udevice *crypto_get_device(u32 capability);

/**
 * crypto_sha_init() - Crypto sha init
 *
 * @dev: crypto device
 * @ctx: sha context
 *
 * @return 0 on success, otherwise failed
 */
int crypto_sha_init(struct udevice *dev, sha_context *ctx);

/**
 * crypto_sha_update() - Crypto sha update
 *
 * @dev: crypto device
 * @input: input data buffer
 * @len: input data length
 *
 * @return 0 on success, otherwise failed
 */
int crypto_sha_update(struct udevice *dev, u32 *input, u32 len);

/**
 * crypto_sha_final() - Crypto sha finish and get result
 *
 * @dev: crypto device
 * @ctx: sha context
 * @output: output hash data
 *
 * @return 0 on success, otherwise failed
 */
int crypto_sha_final(struct udevice *dev, sha_context *ctx, u8 *output);

/**
 * crypto_sha_csum() - Crypto sha hash for one data block only
 *
 * @dev: crypto device
 * @ctx: sha context
 * @input: input data buffer
 * @input_len: input data length
 * @output: output hash data
 *
 * @return 0 on success, otherwise failed
 */
int crypto_sha_csum(struct udevice *dev, sha_context *ctx,
		    char *input, u32 input_len, u8 *output);

/**
 * crypto_sha_regions_csum() - Crypto sha hash for multi data blocks
 *
 * @dev: crypto device
 * @ctx: sha context
 * @region: regions buffer
 * @region_count: regions count
 * @output: output hash data
 *
 * @return 0 on success, otherwise failed
 */
int crypto_sha_regions_csum(struct udevice *dev, sha_context *ctx,
			    const struct image_region region[],
			    int region_count, u8 *output);

/**
 * crypto_rsa_verify() - Crypto rsa verify
 *
 * @dev: crypto device
 * @ctx: rsa key context
 * @sign: signature
 * @output: output hash data buffer
 *
 * @return 0 on success, otherwise failed
 */
int crypto_rsa_verify(struct udevice *dev, rsa_key *ctx, u8 *sign, u8 *output);

/**
 * crypto_hmac_init() - Crypto hmac init
 *
 * @dev: crypto device
 * @ctx: sha context
 *
 * @return 0 on success, otherwise failed
 */
int crypto_hmac_init(struct udevice *dev, sha_context *ctx,
		     u8 *key, u32 key_len);

/**
 * crypto_hmac_update() - Crypto hmac update
 *
 * @dev: crypto device
 * @input: input data buffer
 * @len: input data length
 *
 * @return 0 on success, otherwise failed
 */
int crypto_hmac_update(struct udevice *dev, u32 *input, u32 len);

/**
 * crypto_sha_final() - Crypto hmac finish and get result
 *
 * @dev: crypto device
 * @ctx: sha context
 * @output: output hash data
 *
 * @return 0 on success, otherwise failed
 */
int crypto_hmac_final(struct udevice *dev, sha_context *ctx, u8 *output);

/**
 * crypto_cipher() - Crypto cipher crypt
 *
 * @dev: crypto device
 * @ctx: cipher context
 * @in: input data buffer
 * @out: output data buffer
 * @len: input data length
 * @enc: true for encrypt, false for decrypt
 * @return 0 on success, otherwise failed
 */
int crypto_cipher(struct udevice *dev, cipher_context *ctx,
		  const u8 *in, u8 *out, u32 len, bool enc);

/**
 * crypto_mac() - Crypto cipher mac
 *
 * @dev: crypto device
 * @ctx: cipher context
 * @in: input data buffer
 * @len: input data length
 * @tag: output data buffer
 * @return 0 on success, otherwise failed
 */
int crypto_mac(struct udevice *dev, cipher_context *ctx,
	       const u8 *in, u32 len, u8 *tag);

/**
 * crypto_ae() - Crypto cipher authorization and encryption
 *
 * @dev: crypto device
 * @ctx: cipher context
 * @in: input data buffer
 * @len: input data length
 * @aad: associated data buffer
 * @aad_len: associated data length
 * @out: output data buffer
 * @tag: tag buffer
 * @return 0 on success, otherwise failed
 */
int crypto_ae(struct udevice *dev, cipher_context *ctx,
	      const u8 *in, u32 len, const u8 *aad, u32 aad_len,
	      u8 *out, u8 *tag);

#endif
