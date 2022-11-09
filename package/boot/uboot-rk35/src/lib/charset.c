/*
 *  charset conversion utils
 *
 *  Copyright (c) 2017 Rob Clark
 *
 *  SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <charset.h>
#include <malloc.h>

/*
 * utf8/utf16 conversion mostly lifted from grub
 */

size_t utf16_strlen(const uint16_t *in)
{
	size_t i;
	for (i = 0; in[i]; i++);
	return i;
}

size_t utf16_strnlen(const uint16_t *in, size_t count)
{
	size_t i;
	for (i = 0; count-- && in[i]; i++);
	return i;
}

uint16_t *utf16_strcpy(uint16_t *dest, const uint16_t *src)
{
	uint16_t *tmp = dest;

	while ((*dest++ = *src++) != '\0')
		/* nothing */;
	return tmp;

}

uint16_t *utf16_strdup(const uint16_t *s)
{
	uint16_t *new;
	if (!s || !(new = malloc((utf16_strlen(s) + 1) * 2)))
		return NULL;
	utf16_strcpy(new, s);
	return new;
}

/* Convert UTF-16 to UTF-8.  */
uint8_t *utf16_to_utf8(uint8_t *dest, const uint16_t *src, size_t size)
{
	uint32_t code_high = 0;

	while (size--) {
		uint32_t code = *src++;

		if (code_high) {
			if (code >= 0xDC00 && code <= 0xDFFF) {
				/* Surrogate pair.  */
				code = ((code_high - 0xD800) << 10) + (code - 0xDC00) + 0x10000;

				*dest++ = (code >> 18) | 0xF0;
				*dest++ = ((code >> 12) & 0x3F) | 0x80;
				*dest++ = ((code >> 6) & 0x3F) | 0x80;
				*dest++ = (code & 0x3F) | 0x80;
			} else {
				/* Error...  */
				*dest++ = '?';
				/* *src may be valid. Don't eat it.  */
				src--;
			}

			code_high = 0;
		} else {
			if (code <= 0x007F) {
				*dest++ = code;
			} else if (code <= 0x07FF) {
				*dest++ = (code >> 6) | 0xC0;
				*dest++ = (code & 0x3F) | 0x80;
			} else if (code >= 0xD800 && code <= 0xDBFF) {
				code_high = code;
				continue;
			} else if (code >= 0xDC00 && code <= 0xDFFF) {
				/* Error... */
				*dest++ = '?';
			} else if (code < 0x10000) {
				*dest++ = (code >> 12) | 0xE0;
				*dest++ = ((code >> 6) & 0x3F) | 0x80;
				*dest++ = (code & 0x3F) | 0x80;
			} else {
				*dest++ = (code >> 18) | 0xF0;
				*dest++ = ((code >> 12) & 0x3F) | 0x80;
				*dest++ = ((code >> 6) & 0x3F) | 0x80;
				*dest++ = (code & 0x3F) | 0x80;
			}
		}
	}

	return dest;
}
