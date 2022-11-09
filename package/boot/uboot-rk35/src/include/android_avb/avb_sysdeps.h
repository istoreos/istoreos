/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*
#if !defined(AVB_INSIDE_LIBAVB_H) && !defined(AVB_COMPILATION)
#error "Never include this file directly, include libavb.h instead."
#endif
*/

#ifndef AVB_SYSDEPS_H_
#define AVB_SYSDEPS_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Change these includes to match your platform to bring in the
 * equivalent types available in a normal C runtime. At least things
 * like uint8_t, uint64_t, and bool (with |false|, |true| keywords)
 * must be present.
 */
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#ifdef CONFIG_USE_STDINT
/* Provided by gcc. */
#include <stdint.h>
#else
/* Type for `void *' pointers. */
typedef unsigned long int uintptr_t;
#endif

/* If you don't have gcc or clang, these attribute macros may need to
 * be adjusted.
 */
#define AVB_ATTR_WARN_UNUSED_RESULT __attribute__((warn_unused_result))
#define AVB_ATTR_PACKED __attribute__((packed))
#define AVB_ATTR_NO_RETURN __attribute__((noreturn))
#define AVB_ATTR_SENTINEL __attribute__((__sentinel__))

/* Size in bytes used for alignment. */
#ifdef __LP64__
#define AVB_ALIGNMENT_SIZE 8
#else
#define AVB_ALIGNMENT_SIZE 4
#endif

/* Compare |n| bytes in |src1| and |src2|.
 *
 * Returns an integer less than, equal to, or greater than zero if the
 * first |n| bytes of |src1| is found, respectively, to be less than,
 * to match, or be greater than the first |n| bytes of |src2|. */
int avb_memcmp(const void* src1,
               const void* src2,
               size_t n) AVB_ATTR_WARN_UNUSED_RESULT;

/* Compare two strings.
 *
 * Return an integer less than, equal to, or greater than zero if |s1|
 * is found, respectively, to be less than, to match, or be greater
 * than |s2|.
 */
int avb_strcmp(const char* s1, const char* s2);

/* Compare |n| bytes in two strings.
 *
 * Return an integer less than, equal to, or greater than zero if the
 * first |n| bytes of |s1| is found, respectively, to be less than,
 * to match, or be greater than the first |n| bytes of |s2|.
 */
int avb_strncmp(const char* s1, const char* s2, size_t n);

/* Copy |n| bytes from |src| to |dest|. */
void* avb_memcpy(void* dest, const void* src, size_t n);

/* Set |n| bytes starting at |s| to |c|.  Returns |dest|. */
void* avb_memset(void* dest, const int c, size_t n);

/* Prints out a message. The string passed must be a NUL-terminated
 * UTF-8 string.
 */
void avb_print(const char* message);

/* Prints out a vector of strings. Each argument must point to a
 * NUL-terminated UTF-8 string and NULL should be the last argument.
 */
void avb_printv(const char* message, ...) AVB_ATTR_SENTINEL;

/* Aborts the program or reboots the device. */
void avb_abort(void);

/* Allocates |size| bytes. Returns NULL if no memory is available,
 * otherwise a pointer to the allocated memory.
 *
 * The memory is not initialized.
 *
 * The pointer returned is guaranteed to be word-aligned.
 *
 * The memory should be freed with avb_free() when you are done with it.
 */
void* avb_malloc_(size_t size) AVB_ATTR_WARN_UNUSED_RESULT;

/* Frees memory previously allocated with avb_malloc(). */
void avb_free(void* ptr);

/* Returns the lenght of |str|, excluding the terminating NUL-byte. */
size_t avb_strlen(const char* str) AVB_ATTR_WARN_UNUSED_RESULT;

/* Divide the |dividend| by 10 and saves back to the pointer. Return the
 * remainder. */
uint32_t avb_div_by_10(uint64_t* dividend);

#ifdef __cplusplus
}
#endif

#endif /* AVB_SYSDEPS_H_ */
