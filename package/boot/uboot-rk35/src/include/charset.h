/*
 *  charset conversion utils
 *
 *  Copyright (c) 2017 Rob Clark
 *
 *  SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef __CHARSET_H_
#define __CHARSET_H_

#define MAX_UTF8_PER_UTF16 4

/**
 * utf16_strlen() - Get the length of an utf16 string
 *
 * Returns the number of 16 bit characters in an utf16 string, not
 * including the terminating NULL character.
 *
 * @in     the string to measure
 * @return the string length
 */
size_t utf16_strlen(const uint16_t *in);

/**
 * utf16_strnlen() - Get the length of a fixed-size utf16 string.
 *
 * Returns the number of 16 bit characters in an utf16 string,
 * not including the terminating NULL character, but at most
 * 'count' number of characters.  In doing this, utf16_strnlen()
 * looks at only the first 'count' characters.
 *
 * @in     the string to measure
 * @count  the maximum number of characters to count
 * @return the string length, up to a maximum of 'count'
 */
size_t utf16_strnlen(const uint16_t *in, size_t count);

/**
 * utf16_strcpy() - UTF16 equivalent of strcpy()
 */
uint16_t *utf16_strcpy(uint16_t *dest, const uint16_t *src);

/**
 * utf16_strdup() - UTF16 equivalent of strdup()
 */
uint16_t *utf16_strdup(const uint16_t *s);

/**
 * utf16_to_utf8() - Convert an utf16 string to utf8
 *
 * Converts 'size' characters of the utf16 string 'src' to utf8
 * written to the 'dest' buffer.
 *
 * NOTE that a single utf16 character can generate up to 4 utf8
 * characters.  See MAX_UTF8_PER_UTF16.
 *
 * @dest   the destination buffer to write the utf8 characters
 * @src    the source utf16 string
 * @size   the number of utf16 characters to convert
 * @return the pointer to the first unwritten byte in 'dest'
 */
uint8_t *utf16_to_utf8(uint8_t *dest, const uint16_t *src, size_t size);

#endif /* __CHARSET_H_ */
