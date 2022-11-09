/* SPDX-License-Identifier:     GPL-2.0+ */
/*
 * (C) Copyright 2019 Rockchip Electronics Co., Ltd
 */

#ifndef _ROCKCHIP_CRYPTO_V2_UTIL_H_
#define _ROCKCHIP_CRYPTO_V2_UTIL_H_

#ifdef __cplusplus
extern "C"
{
#endif

/************************ Defines ******************************/

/* invers the bytes on a word- used for output from HASH */
#ifdef BIG__ENDIAN
#define UTIL_INVERSE_UINT32_BYTES(val)	(val)
#else
#define UTIL_INVERSE_UINT32_BYTES(val) \
	(((val) >> 24) | (((val) & 0x00FF0000) >> 8) | \
	(((val) & 0x0000FF00) << 8) | (((val) & 0x000000FF) << 24))
#endif

/* invers the bytes on a word - used for input data for HASH */
#ifdef BIG__ENDIAN
#define UTIL_REVERT_UINT32_BYTES(val) \
	(((val) >> 24) | (((val) & 0x00FF0000) >> 8) | \
	(((val) & 0x0000FF00) << 8) | (((val) & 0x000000FF) << 24))
#else
#define UTIL_REVERT_UINT32_BYTES(val)	(val)
#endif

/* the minimum and maximum macros */
#undef min
#define min(a, b) (((a) < (b)) ? (a) : (b))

#undef max
#define max(a, b) (((a) > (b)) ? (a) : (b))

/* MACRO to count one bits */
#define COUNT_ONE_BITS(number, bit_count) \
do { \
	u32 tmp_num = number; \
	bit_count = 0; \
	while (tmp_num) { \
		tmp_num = tmp_num & (tmp_num - 1); \
	bit_count = bit_count + 1; \
	} \
} while (0)

/* ------------------------------------------------------------
 **
 * @brief This function executes a reversed words copy on a specified buffer.
 *
 *        on a 6 words byffer:
 *
 *        buff[5] <---> buff[0]
 *        buff[4] <---> buff[1]
 *        buff[3] <---> buff[2]
 *
 * @param[in] dst_ptr - The counter buffer.
 * @param[in] size    - The counter size in words.
 *
 */
void util_reverse_words_buff(u32 *buff_ptr, u32 size_words);

/* ------------------------------------------------------------
 **
 * @brief This function executes a reversed byte copy on a specified buffer.
 *
 *        on a 6 byte byffer:
 *
 *        buff[5] <---> buff[0]
 *        buff[4] <---> buff[1]
 *        buff[3] <---> buff[2]
 *
 * @param[in] dst_ptr - The counter buffer.
 * @param[in] src_ptr - The counter size in bytes.
 *
 */
void util_reverse_buff(u8 *buff_ptr, u32 size);

/* ------------------------------------------------------------
 **
 * @brief This function executes a memory copy between 2 buffers.
 *
 * @param[in] dst_ptr - The first counter buffer.
 * @param[in] src_ptr - The second counter buffer.
 * @param[in] size    - The counter size in words.
 *
 */
void util_word_memcpy(u32 *dst_ptr, u32 *src_ptr, u32 size);

/* ------------------------------------------------------------
 **
 * @brief This function executes a memory set operation on a buffer.
 *
 * @param[in] buff_ptr - the buffer.
 * @param[in] val		- The value to set the buffer.
 * @param[in] size		- the buffers size in words.
 *
 */
void util_word_memset(u32 *buff_ptr, u32 val, u32 size);

/* ------------------------------------------------------------
 **
 * @brief This function executes a reverse bytes copying from one buffer
 *	  to another buffer.
 *
 * @param[in] dst_ptr - The pointer to destination buffer.
 * @param[in] src_ptr - The pointer to source buffer.
 * @param[in] size    - The size in words.
 *
 */
void util_reverse_word_memcpy(u32 *dst_ptr, u32 *src_ptr, u32 size);

/* ------------------------------------------------------------
 **
 * @brief This function executes a reverse bytes copying from one buffer
 *	  to another buffer.
 *
 * @param[in] dst_ptr - The pointer to destination buffer.
 * @param[in] src_ptr - The pointer to source buffer.
 * @param[in] size    - The size in bytes.
 *
 */
void util_reverse_memcpy(u8 *dst_ptr, const u8 *src_ptr, u32 size);

#ifdef __cplusplus
}
#endif

#endif

