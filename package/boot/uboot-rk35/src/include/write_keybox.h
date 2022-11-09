/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
 */

#ifndef WRITE_KEYBOX_H_
#define	WRITE_KEYBOX_H_

#include <common.h>
#include <optee_include/tee_client_api.h>

#if defined CONFIG_ANDROID_WRITE_KEYBOX && defined CONFIG_ANDROID_KEYMASTER_CA
/*
 * write_keybox_to_secure_storage
 *
 * @received_data:	the data received from usb
 * @len:		size of received_data
 *
 * @return a negative number in case of error, or 0 on success.
 */
uint32_t write_keybox_to_secure_storage(uint8_t *received_data, uint32_t len);

/*
 * write_to_secure_storage
 *
 * @is_use_rpmb:	0, write data to security patition
 *			1, write data to rpmb
 * @filename:		the file name of data written to secure storage
 * @filename_size:	size of filename
 * @data:		the data want to write to secure storage
 * @data_size:		size of data
 *
 * @return a nonzero number in case of error, or 0 on success.
 */
TEEC_Result write_to_security_storage(uint8_t is_use_rpmb,
				      uint8_t *filename,
				      uint32_t filename_size,
				      uint8_t *data,
				      uint32_t data_size);
/*
 * read_raw_data_from_secure_storege
 *
 * @raw_data:	the data read from secure storage
 * @data_size:	size of raw data
 *
 * @return size of raw_data in case of success, or 0 on fail
 */
uint32_t read_raw_data_from_secure_storage(uint8_t *received_data,
					   uint32_t len);
char *new_strstr(const char *s1, const char *s2, uint32_t l1);
#else
inline uint32_t write_keybox_to_secure_storage(uint8_t *raw_data,
					       uint32_t data_size)
{
	return -EPERM;
}

inline uint32_t read_raw_data_from_secure_storage(uint8_t *received_data,
						  uint32_t len)
{
	return -EPERM;
}
#endif
#endif
