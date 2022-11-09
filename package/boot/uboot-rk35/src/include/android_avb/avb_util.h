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

#ifndef AVB_UTIL_H_
#define AVB_UTIL_H_

#include <android_avb/avb_sysdeps.h>

#ifdef __cplusplus
extern "C" {
#endif

#define AVB_STRINGIFY(x) #x
#define AVB_TO_STRING(x) AVB_STRINGIFY(x)

#ifdef AVB_ENABLE_DEBUG
/* Aborts the program if |expr| is false.
 *
 * This has no effect unless AVB_ENABLE_DEBUG is defined.
 */
#define avb_assert(expr)                     \
  do {                                       \
    if (!(expr)) {                           \
      avb_fatal("assert fail: " #expr "\n"); \
    }                                        \
  } while (0)
#else
#define avb_assert(expr)
#endif

/* Aborts the program if reached.
 *
 * This has no effect unless AVB_ENABLE_DEBUG is defined.
 */
#ifdef AVB_ENABLE_DEBUG
#define avb_assert_not_reached()         \
  do {                                   \
    avb_fatal("assert_not_reached()\n"); \
  } while (0)
#else
#define avb_assert_not_reached()
#endif

/* Aborts the program if |addr| is not word-aligned.
 *
 * This has no effect unless AVB_ENABLE_DEBUG is defined.
 */
#define avb_assert_aligned(addr) \
  avb_assert((((uintptr_t)addr) & (AVB_ALIGNMENT_SIZE - 1)) == 0)

#ifdef AVB_ENABLE_DEBUG
/* Print functions, used for diagnostics.
 *
 * These have no effect unless AVB_ENABLE_DEBUG is defined.
 */
#define avb_debug(message)              \
  do {                                  \
    avb_printv(avb_basename(__FILE__),  \
               ":",                     \
               AVB_TO_STRING(__LINE__), \
               ": DEBUG: ",             \
               message,                 \
               NULL);                   \
  } while (0)
#define avb_debugv(message, ...)        \
  do {                                  \
    avb_printv(avb_basename(__FILE__),  \
               ":",                     \
               AVB_TO_STRING(__LINE__), \
               ": DEBUG: ",             \
               message,                 \
               ##__VA_ARGS__);          \
  } while (0)
#else
#define avb_debug(message)
#define avb_debugv(message, ...)
#endif

/* Prints out a message. This is typically used if a runtime-error
 * occurs.
 */
#define avb_error(message)              \
  do {                                  \
    avb_printv(avb_basename(__FILE__),  \
               ":",                     \
               AVB_TO_STRING(__LINE__), \
               ": ERROR: ",             \
               message,                 \
               NULL);                   \
  } while (0)
#define avb_errorv(message, ...)        \
  do {                                  \
    avb_printv(avb_basename(__FILE__),  \
               ":",                     \
               AVB_TO_STRING(__LINE__), \
               ": ERROR: ",             \
               message,                 \
               ##__VA_ARGS__);          \
  } while (0)

/* Prints out a message and calls avb_abort().
 */
#define avb_fatal(message)              \
  do {                                  \
    avb_printv(avb_basename(__FILE__),  \
               ":",                     \
               AVB_TO_STRING(__LINE__), \
               ": FATAL: ",             \
               message,                 \
               NULL);                   \
    avb_abort();                        \
  } while (0)
#define avb_fatalv(message, ...)        \
  do {                                  \
    avb_printv(avb_basename(__FILE__),  \
               ":",                     \
               AVB_TO_STRING(__LINE__), \
               ": FATAL: ",             \
               message,                 \
               ##__VA_ARGS__);          \
    avb_abort();                        \
  } while (0)

/* Converts a 32-bit unsigned integer from big-endian to host byte order. */
uint32_t avb_be32toh(uint32_t in) AVB_ATTR_WARN_UNUSED_RESULT;

/* Converts a 64-bit unsigned integer from big-endian to host byte order. */
uint64_t avb_be64toh(uint64_t in) AVB_ATTR_WARN_UNUSED_RESULT;

/* Converts a 32-bit unsigned integer from host to big-endian byte order. */
uint32_t avb_htobe32(uint32_t in) AVB_ATTR_WARN_UNUSED_RESULT;

/* Converts a 64-bit unsigned integer from host to big-endian byte order. */
uint64_t avb_htobe64(uint64_t in) AVB_ATTR_WARN_UNUSED_RESULT;

/* Compare |n| bytes starting at |s1| with |s2| and return 0 if they
 * match, 1 if they don't.  Returns 0 if |n|==0, since no bytes
 * mismatched.
 *
 * Time taken to perform the comparison is only dependent on |n| and
 * not on the relationship of the match between |s1| and |s2|.
 *
 * Note that unlike avb_memcmp(), this only indicates inequality, not
 * whether |s1| is less than or greater than |s2|.
 */
int avb_safe_memcmp(const void* s1,
                    const void* s2,
                    size_t n) AVB_ATTR_WARN_UNUSED_RESULT;

/* Adds |value_to_add| to |value| with overflow protection.
 *
 * Returns false if the addition overflows, true otherwise. In either
 * case, |value| is always modified.
 */
bool avb_safe_add_to(uint64_t* value,
                     uint64_t value_to_add) AVB_ATTR_WARN_UNUSED_RESULT;

/* Adds |a| and |b| with overflow protection, returning the value in
 * |out_result|.
 *
 * It's permissible to pass NULL for |out_result| if you just want to
 * check that the addition would not overflow.
 *
 * Returns false if the addition overflows, true otherwise.
 */
bool avb_safe_add(uint64_t* out_result,
                  uint64_t a,
                  uint64_t b) AVB_ATTR_WARN_UNUSED_RESULT;

/* Checks if |num_bytes| data at |data| is a valid UTF-8
 * string. Returns true if valid UTF-8, false otherwise.
 */
bool avb_validate_utf8(const uint8_t* data,
                       size_t num_bytes) AVB_ATTR_WARN_UNUSED_RESULT;

/* Concatenates |str1| (of |str1_len| bytes) and |str2| (of |str2_len|
 * bytes) and puts the result in |buf| which holds |buf_size|
 * bytes. The result is also guaranteed to be NUL terminated. Fail if
 * there is not enough room in |buf| for the resulting string plus
 * terminating NUL byte.
 *
 * Returns true if the operation succeeds, false otherwise.
 */
bool avb_str_concat(char* buf,
                    size_t buf_size,
                    const char* str1,
                    size_t str1_len,
                    const char* str2,
                    size_t str2_len);

/* Like avb_malloc_() but prints a error using avb_error() if memory
 * allocation fails.
 */
void* avb_malloc(size_t size) AVB_ATTR_WARN_UNUSED_RESULT;

/* Like avb_malloc() but sets the memory with zeroes. */
void* avb_calloc(size_t size) AVB_ATTR_WARN_UNUSED_RESULT;

/* Duplicates a NUL-terminated string. Returns NULL on OOM. */
char* avb_strdup(const char* str) AVB_ATTR_WARN_UNUSED_RESULT;

/* Duplicates a NULL-terminated array of NUL-terminated strings by
 * concatenating them. The returned string will be
 * NUL-terminated. Returns NULL on OOM.
 */
char* avb_strdupv(const char* str,
                  ...) AVB_ATTR_WARN_UNUSED_RESULT AVB_ATTR_SENTINEL;

/* Finds the first occurrence of |needle| in the string |haystack|
 * where both strings are NUL-terminated strings. The terminating NUL
 * bytes are not compared.
 *
 * Returns NULL if not found, otherwise points into |haystack| for the
 * first occurrence of |needle|.
 */
const char* avb_strstr(const char* haystack,
                       const char* needle) AVB_ATTR_WARN_UNUSED_RESULT;

/* Finds the first occurrence of |str| in the NULL-terminated string
 * array |strings|. Each element in |strings| must be
 * NUL-terminated. The string given by |str| need not be
 * NUL-terminated but its size must be given in |str_size|.
 *
 * Returns NULL if not found, otherwise points into |strings| for the
 * first occurrence of |str|.
 */
const char* avb_strv_find_str(const char* const* strings,
                              const char* str,
                              size_t str_size);

/* Replaces all occurrences of |search| with |replace| in |str|.
 *
 * Returns a newly allocated string or NULL if out of memory.
 */
char* avb_replace(const char* str,
                  const char* search,
                  const char* replace) AVB_ATTR_WARN_UNUSED_RESULT;

/* Calculates the CRC-32 for data in |buf| of size |buf_size|. */
uint32_t avb_crc32(const uint8_t* buf, size_t buf_size);

/* Returns the basename of |str|. This is defined as the last path
 * component, assuming the normal POSIX separator '/'. If there are no
 * separators, returns |str|.
 */
const char* avb_basename(const char* str);

/* Converts any ascii lowercase characters in |str| to uppercase in-place.
 * |str| must be NUL-terminated and valid UTF-8.
 */
void avb_uppercase(char* str);

/* Converts |data_len| bytes of |data| to hex and returns the result. Returns
 * NULL on OOM. Caller must free the returned string with avb_free.
 */
char* avb_bin2hex(const uint8_t* data, size_t data_len);

#ifdef __cplusplus
}
#endif

#endif /* AVB_UTIL_H_ */
