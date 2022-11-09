/* SPDX-License-Identifier:     GPL-2.0+ */
/*
 * (C) Copyright 2019 Rockchip Electronics Co., Ltd
 */

#ifndef _ROCKCHIP_CRYPTO_V1_H_
#define _ROCKCHIP_CRYPTO_V1_H_

struct rk_crypto_reg {
	u32 crypto_intsts;
	u32 crypto_intena;
	u32 crypto_ctrl;
	u32 crypto_conf;
	u32 crypto_brdmas;
	u32 crypto_btdmas;
	u32 crypto_brdmal;
	u32 crypto_hrdmas;
	u32 crypto_hrdmal;
	u32 reserved0[(0x80 - 0x24) / 4];

	u32 crypto_aes_ctrl;
	u32 crypto_aes_sts;
	u32 crypto_aes_din[4];
	u32 crypto_aes_dout[4];
	u32 crypto_aes_iv[4];
	u32 crypto_aes_key[8];
	u32 crypto_aes_cnt[4];
	u32 reserved1[(0x100 - 0xe8) / 4];

	u32 crypto_tdes_ctrl;
	u32 crypto_tdes_sts;
	u32 crypto_tdes_din[2];
	u32 crypto_tdes_dout[2];
	u32 crypto_tdes_iv[2];
	u32 crypto_tdes_key1[2];
	u32 crypto_tdes_key2[2];
	u32 crypto_tdes_key3[2];
	u32 reserved2[(0x180 - 0x138) / 4];

	u32 crypto_hash_ctrl;
	u32 crypto_hash_sts;
	u32 crypto_hash_msg_len;
	u32 crypto_hash_dout[8];
	u32 crypto_hash_seed[5];
	u32 reserved3[(0x200 - 0x1c0) / 4];

	u32 crypto_trng_ctrl;
	u32 crypto_trng_dout[8];
	u32 reserved4[(0x280 - 0x224) / 4];

	u32 crypto_pka_ctrl;
	u32 reserved5[(0x400 - 0x284) / 4];

	u32 crypto_pka_m[(0x500 - 0x400) / 4];
	u32 crypto_pka_c[(0x600 - 0x500) / 4];
	u32 crypto_pka_n[(0x700 - 0x600) / 4];
	u32 crypto_pka_e;
};

check_member(rk_crypto_reg, crypto_pka_e, 0x700);

/************************ Register bits definition ****************************/
/* CRYPTO_HASH_CTRL */
#define ENGINE_SELECTION_SHA1		0x0
#define ENGINE_SELECTION_MD5		0x1
#define ENGINE_SELECTION_SHA256		0x2
#define HASH_SWAP_DO			0x8

/* CRYPTO_CONF */
#define HR_ADDR_MODE			BIT(8)
#define BT_ADDR_MODE			BIT(7)
#define BR_ADDR_MODE			BIT(6)
#define BYTESWAP_HRFIFO			BIT(5)
#define BYTESWAP_BTFIFO			BIT(4)
#define BYTESWAP_BRFIFO			BIT(3)
#define DESSEL				BIT(2)

/* CRYPTO_CTRL */
#define TRNG_FLUSH			BIT(9)
#define TRNG_START			BIT(8)
#define PKA_FLUSH			BIT(7)
#define HASH_FLUSH			BIT(6)
#define BLOCK_FLUSH			BIT(5)
#define PKA_START			BIT(4)
#define HASH_START			BIT(3)
#define BLOCK_START			BIT(2)
#define TDES_START			BIT(1)
#define AES_START			BIT(0)
#define PKA_HASH_CTRL			(PKA_FLUSH | HASH_FLUSH)
#define PKA_CTRL			(PKA_FLUSH | PKA_START)

/* CRYPTO_INTSTS */
#define PKA_DONE_INT			BIT(5)
#define HASH_DONE_INT			BIT(4)
#define HRDMA_ERR_INT			BIT(3)
#define HRDMA_DONE_INT			BIT(2)
#define BCDMA_ERR_INT			BIT(1)
#define BCDMA_DONE_INT			BIT(0)

/* CRYPTO_PKA_CTRL */
#define PKA_BLOCK_SIZE_512		0
#define PKA_BLOCK_SIZE_1024		1
#define PKA_BLOCK_SIZE_2048		2

#endif
