/*
 * Copyright 2017, Rockchip Electronics Co., Ltd
 * hisping lin, <hisping.lin@rock-chips.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#ifndef _OPTEECLIENTTEST_H_
#define _OPTEECLIENTTEST_H_

#include <optee_include/tee_client_api.h>

enum RK_OEM_OTP_KEYID {
	RK_OEM_OTP_KEY0 = 0,
	RK_OEM_OTP_KEY1 = 1,
	RK_OEM_OTP_KEY2 = 2,
	RK_OEM_OTP_KEY3 = 3,
	RK_OEM_OTP_KEY_FW = 10,	//keyid of fw_encryption_key
	RK_OEM_OTP_KEYMAX
};

/* Crypto mode */
enum RK_CIPIHER_MODE {
	RK_CIPHER_MODE_ECB = 0,
	RK_CIPHER_MODE_CBC = 1,
	RK_CIPHER_MODE_CTS = 2,
	RK_CIPHER_MODE_CTR = 3,
	RK_CIPHER_MODE_CFB = 4,
	RK_CIPHER_MODE_OFB = 5,
	RK_CIPHER_MODE_XTS = 6,
	RK_CIPHER_MODE_CCM = 7,
	RK_CIPHER_MODE_GCM = 8,
	RK_CIPHER_MODE_CMAC = 9,
	RK_CIPHER_MODE_CBC_MAC = 10,
	RK_CIPHER_MODE_MAX
};

/* Crypto algorithm */
enum RK_CRYPTO_ALGO {
	RK_ALGO_AES = 1,
	RK_ALGO_DES,
	RK_ALGO_TDES,
	RK_ALGO_SM4,
	RK_ALGO_ALGO_MAX
};

typedef struct {
	uint32_t	algo;
	uint32_t	mode;
	uint32_t	operation;
	uint8_t		key[64];
	uint32_t	key_len;
	uint8_t		iv[16];
	void		*reserved;
} rk_cipher_config;

/* Crypto operation */
#define RK_MODE_ENCRYPT			1
#define RK_MODE_DECRYPT			0

#define AES_BLOCK_SIZE			16
#define SM4_BLOCK_SIZE			16
#define RK_CRYPTO_MAX_DATA_LEN		(1 * 1024 * 1024)

#define ATAP_HEX_UUID_LEN 32
#define ATTEST_DH_SIZE     8
#define ATTEST_UUID_SIZE     (ATAP_HEX_UUID_LEN+1)
#define ATTEST_CA_OUT_SIZE     256

uint32_t trusty_read_rollback_index(uint32_t slot, uint64_t *value);
uint32_t trusty_write_rollback_index(uint32_t slot, uint64_t value);
uint32_t trusty_read_permanent_attributes(uint8_t *attributes, uint32_t size);
uint32_t trusty_write_permanent_attributes(uint8_t *attributes, uint32_t size);
uint32_t trusty_read_permanent_attributes_cer(uint8_t *attributes,
					      uint32_t size);
uint32_t trusty_write_permanent_attributes_cer(uint8_t *attributes,
					       uint32_t size);
uint32_t trusty_read_lock_state(uint8_t *lock_state);
uint32_t trusty_write_lock_state(uint8_t lock_state);
uint32_t trusty_read_flash_lock_state(uint8_t *flash_lock_state);
uint32_t trusty_write_flash_lock_state(uint8_t flash_lock_state);

uint32_t trusty_read_attribute_hash(uint32_t *buf, uint32_t length);
uint32_t trusty_write_attribute_hash(uint32_t *buf, uint32_t length);
uint32_t trusty_notify_optee_uboot_end(void);
uint32_t trusty_read_vbootkey_hash(uint32_t *buf, uint32_t length);
uint32_t trusty_write_vbootkey_hash(uint32_t *buf, uint32_t length);
uint32_t trusty_read_vbootkey_enable_flag(uint8_t *flag);
uint32_t trusty_write_ta_encryption_key(uint32_t *buf, uint32_t length);
uint32_t trusty_check_security_level_flag(uint8_t flag);
uint32_t trusty_write_oem_huk(uint32_t *buf, uint32_t length);
void trusty_select_security_level(void);
uint32_t trusty_read_permanent_attributes_flag(uint8_t *attributes);
uint32_t trusty_write_permanent_attributes_flag(uint8_t attributes);
uint32_t trusty_write_oem_ns_otp(uint32_t byte_off, uint8_t *byte_buf, uint32_t byte_len);
uint32_t trusty_read_oem_ns_otp(uint32_t byte_off, uint8_t *byte_buf, uint32_t byte_len);
uint32_t trusty_write_oem_otp_key(enum RK_OEM_OTP_KEYID key_id,
				  uint8_t *byte_buf, uint32_t byte_len);
uint32_t trusty_oem_otp_key_is_written(enum RK_OEM_OTP_KEYID key_id, uint8_t *value);
uint32_t trusty_set_oem_hr_otp_read_lock(enum RK_OEM_OTP_KEYID key_id);
uint32_t trusty_oem_otp_key_cipher(enum RK_OEM_OTP_KEYID key_id, rk_cipher_config *config,
				   uint32_t src_phys_addr, uint32_t dst_phys_addr,
				   uint32_t len);
uint32_t trusty_attest_dh(uint8_t *dh, uint32_t *dh_size);
uint32_t trusty_attest_uuid(uint8_t *uuid, uint32_t *uuid_size);
uint32_t trusty_attest_get_ca
	(uint8_t *operation_start, uint32_t *operation_size,
	 uint8_t *out, uint32_t *out_len);
uint32_t trusty_attest_set_ca(uint8_t *ca_response, uint32_t *ca_response_size);

#endif
