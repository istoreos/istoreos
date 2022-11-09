/*
 * Copyright 2018, Rockchip Electronics Co., Ltd
 * qiujian, <qiujian@rock-chips.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef ATTESTATION_KEY_H_
#define ATTESTATION_KEY_H_

#include <common.h>

typedef enum {
	ATAP_RESULT_OK,
	ATAP_RESULT_ERROR_DEVICE_NOT_FOUND,
	ATAP_RESULT_ERROR_PARTITION_NOT_FOUND,
	ATAP_RESULT_ERROR_BLOCK_READ,
	ATAP_RESULT_ERROR_BLOCK_WRITE,
	ATAP_RESULT_ERROR_INVALID_HEAD,
	ATAP_RESULT_ERROR_INVALID_BLOCK_NUM,
	ATAP_RESULT_ERROR_INVALID_DEVICE_ID,
	ATAP_RESULT_ERROR_BUF_COPY,
	ATAP_RESULT_ERROR_STORAGE,
} atap_result;

/* load attestation key from misc partition. */
atap_result load_attestation_key(struct blk_desc *dev_desc,
				disk_partition_t *misc_partition);
atap_result read_key_data(uint8_t **key_buf, uint8_t *key_data,
			  uint32_t *key_data_length);
/*
 * write attestation key to secure storage.
 * @received_data: received data from usb
 * @len: the size of received_data
 * @return ATAP_RESULT_OK if ok, or ATAP_RESULT_ERROR_* on error
 */
atap_result write_attestation_key_to_secure_storage(uint8_t *received_data,
						    uint32_t len);
#endif	//ATTESTATION_KEY_H_
