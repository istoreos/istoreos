// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2021 Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <crypto.h>

static void dump_hash(const char *label, void *hash,
		      u32 nbits, char *addr, int len)
{
	char *buf;
	int i;

	printf("%s for %08lx ... %08lx ==> ", label, (ulong)addr, (ulong)addr + len);
	buf = hash;
	for (i = 0; i < BITS2BYTE(nbits); i++)
		printf("%02x", buf[i]);

	printf("\n\n");
}

static int do_crypto_csum(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	sha_context csha_ctx;
	struct udevice *dev;
	char *input_data;
	int input_len;
	u8 hash[256];
	u32 cap;

	if (argc != 4)
		return CMD_RET_USAGE;

	if (!strcmp(argv[1], "md5"))
		cap = CRYPTO_MD5;
	else if (!strcmp(argv[1], "sha1"))
		cap = CRYPTO_SHA1;
	else if (!strcmp(argv[1], "sha256"))
		cap = CRYPTO_SHA256;
	else if (!strcmp(argv[1], "sha512"))
		cap = CRYPTO_SHA512;
	else
		return CMD_RET_USAGE;

	input_data = (char *)simple_strtoul(argv[2], NULL, 16);
	input_len = simple_strtoul(argv[3], NULL, 16);

	dev = crypto_get_device(cap);
	if (!dev) {
		printf("Can't find crypto device for %s\n", argv[1]);
		return -ENODEV;
	}

	if (cap == CRYPTO_MD5) {
		csha_ctx.algo = CRYPTO_MD5;
		csha_ctx.length = input_len;
		memset(hash, 0, sizeof(hash));
		crypto_sha_csum(dev, &csha_ctx, input_data, input_len, hash);
		dump_hash("md5", hash, crypto_algo_nbits(csha_ctx.algo),
			  input_data, input_len);
	} else if (cap == CRYPTO_SHA1) {
		csha_ctx.algo = CRYPTO_SHA1;
		csha_ctx.length = input_len;
		memset(hash, 0, sizeof(hash));
		crypto_sha_csum(dev, &csha_ctx, input_data, input_len, hash);
		dump_hash("sha1", hash, crypto_algo_nbits(csha_ctx.algo),
			  input_data, input_len);
	} else if (cap == CRYPTO_SHA256) {
		csha_ctx.algo = CRYPTO_SHA256;
		csha_ctx.length = input_len;
		memset(hash, 0, sizeof(hash));
		crypto_sha_csum(dev, &csha_ctx, input_data, input_len, hash);
		dump_hash("sha256", hash, crypto_algo_nbits(csha_ctx.algo),
			  input_data, input_len);
	} else if (cap == CRYPTO_SHA512) {
		csha_ctx.algo = CRYPTO_SHA512;
		csha_ctx.length = input_len;
		memset(hash, 0, sizeof(hash));
		crypto_sha_csum(dev, &csha_ctx, input_data, input_len, hash);
		dump_hash("sha512", hash, crypto_algo_nbits(csha_ctx.algo),
			  input_data, input_len);
	}

	return 0;
}

U_BOOT_CMD(
	crypto_sum,	4,	1,	do_crypto_csum,
	"crypto checksum engine",
	"[md5|sha1|sha256|sha512] [addr] [length]"
);

