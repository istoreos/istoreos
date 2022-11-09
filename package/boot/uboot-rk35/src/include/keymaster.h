// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
 */

#ifndef KEYMASTER_H_
#define KEYMASTER_H_

#include <optee_include/tee_client_api.h>

/*
 * read data from rk_keymaster
 *
 * @felename:           the filename of the saved data to read
 * @filename_size:      size of filename
 * @data:               the buffer used to read data from rk_keymaster
 * @data_size:          buffer size of the data
 *
 * @return a positive number in case of error, or 0 on success.
 */
TEEC_Result read_from_keymaster(uint8_t *filename,
				uint32_t filename_size,
				uint8_t *data,
				uint32_t data_size);

/*
 * write data to rk_keymaster
 *
 * @felename:           the filename of the saved data to read
 * @filename_size:      size of filename
 * @data:               the buffer used to read data from rk_keymaster
 * @data_size:          buffer size of the data
 *
 * @return a positive number in case of error, or 0 on success.
 */
TEEC_Result write_to_keymaster(uint8_t *filename,
			       uint32_t filename_size,
			       uint8_t *data,
			       uint32_t data_size);

/*
 * read oem unlock status from rk_keymaster
 *
 * @unlock:used to read oem unlock status code,0:locked,1:unlocked
 *
 * @return a positive number in case of error, or 0 on success.
 */
TEEC_Result trusty_read_oem_unlock(uint8_t *unlock);

/*
 * update oem unlock status to rk_keymaster
 *
 * @unlock: oem unlock status code,0:locked,1:unlocked
 *
 * @return a positive number in case of error, or 0 on success.
 */
TEEC_Result trusty_write_oem_unlock(uint8_t unlock);

#endif  //KEYMASTER_H_
