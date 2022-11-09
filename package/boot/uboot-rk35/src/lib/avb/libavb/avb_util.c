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

#include <android_avb/avb_util.h>

#include <stdarg.h>

uint32_t avb_be32toh(uint32_t in) {
  uint8_t* d = (uint8_t*)&in;
  uint32_t ret;
  ret = ((uint32_t)d[0]) << 24;
  ret |= ((uint32_t)d[1]) << 16;
  ret |= ((uint32_t)d[2]) << 8;
  ret |= ((uint32_t)d[3]);
  return ret;
}

uint64_t avb_be64toh(uint64_t in) {
  uint8_t* d = (uint8_t*)&in;
  uint64_t ret;
  ret = ((uint64_t)d[0]) << 56;
  ret |= ((uint64_t)d[1]) << 48;
  ret |= ((uint64_t)d[2]) << 40;
  ret |= ((uint64_t)d[3]) << 32;
  ret |= ((uint64_t)d[4]) << 24;
  ret |= ((uint64_t)d[5]) << 16;
  ret |= ((uint64_t)d[6]) << 8;
  ret |= ((uint64_t)d[7]);
  return ret;
}

/* Converts a 32-bit unsigned integer from host to big-endian byte order. */
uint32_t avb_htobe32(uint32_t in) {
  union {
    uint32_t word;
    uint8_t bytes[4];
  } ret;
  ret.bytes[0] = (in >> 24) & 0xff;
  ret.bytes[1] = (in >> 16) & 0xff;
  ret.bytes[2] = (in >> 8) & 0xff;
  ret.bytes[3] = in & 0xff;
  return ret.word;
}

/* Converts a 64-bit unsigned integer from host to big-endian byte order. */
uint64_t avb_htobe64(uint64_t in) {
  union {
    uint64_t word;
    uint8_t bytes[8];
  } ret;
  ret.bytes[0] = (in >> 56) & 0xff;
  ret.bytes[1] = (in >> 48) & 0xff;
  ret.bytes[2] = (in >> 40) & 0xff;
  ret.bytes[3] = (in >> 32) & 0xff;
  ret.bytes[4] = (in >> 24) & 0xff;
  ret.bytes[5] = (in >> 16) & 0xff;
  ret.bytes[6] = (in >> 8) & 0xff;
  ret.bytes[7] = in & 0xff;
  return ret.word;
}

int avb_safe_memcmp(const void* s1, const void* s2, size_t n) {
  const unsigned char* us1 = s1;
  const unsigned char* us2 = s2;
  int result = 0;

  if (0 == n) {
    return 0;
  }

  /*
   * Code snippet without data-dependent branch due to Nate Lawson
   * (nate@root.org) of Root Labs.
   */
  while (n--) {
    result |= *us1++ ^ *us2++;
  }

  return result != 0;
}

bool avb_safe_add_to(uint64_t* value, uint64_t value_to_add) {
  uint64_t original_value;

  avb_assert(value != NULL);

  original_value = *value;

  *value += value_to_add;
  if (*value < original_value) {
    avb_error("Overflow when adding values.\n");
    return false;
  }

  return true;
}

bool avb_safe_add(uint64_t* out_result, uint64_t a, uint64_t b) {
  uint64_t dummy;
  if (out_result == NULL) {
    out_result = &dummy;
  }
  *out_result = a;
  return avb_safe_add_to(out_result, b);
}

bool avb_validate_utf8(const uint8_t* data, size_t num_bytes) {
  size_t n;
  unsigned int num_cc;

  for (n = 0, num_cc = 0; n < num_bytes; n++) {
    uint8_t c = data[n];

    if (num_cc > 0) {
      if ((c & (0x80 | 0x40)) == 0x80) {
        /* 10xx xxxx */
      } else {
        goto fail;
      }
      num_cc--;
    } else {
      if (c < 0x80) {
        num_cc = 0;
      } else if ((c & (0x80 | 0x40 | 0x20)) == (0x80 | 0x40)) {
        /* 110x xxxx */
        num_cc = 1;
      } else if ((c & (0x80 | 0x40 | 0x20 | 0x10)) == (0x80 | 0x40 | 0x20)) {
        /* 1110 xxxx */
        num_cc = 2;
      } else if ((c & (0x80 | 0x40 | 0x20 | 0x10 | 0x08)) ==
                 (0x80 | 0x40 | 0x20 | 0x10)) {
        /* 1111 0xxx */
        num_cc = 3;
      } else {
        goto fail;
      }
    }
  }

  if (num_cc != 0) {
    goto fail;
  }

  return true;

fail:
  return false;
}

bool avb_str_concat(char* buf,
                    size_t buf_size,
                    const char* str1,
                    size_t str1_len,
                    const char* str2,
                    size_t str2_len) {
  uint64_t combined_len;

  if (!avb_safe_add(&combined_len, str1_len, str2_len)) {
    avb_error("Overflow when adding string sizes.\n");
    return false;
  }

  if (combined_len > buf_size - 1) {
    avb_error("Insufficient buffer space.\n");
    return false;
  }

  avb_memcpy(buf, str1, str1_len);
  avb_memcpy(buf + str1_len, str2, str2_len);
  buf[combined_len] = '\0';

  return true;
}

void* avb_malloc(size_t size) {
  void* ret = avb_malloc_(size);
  if (ret == NULL) {
    avb_error("Failed to allocate memory.\n");
    return NULL;
  }
  return ret;
}

void* avb_calloc(size_t size) {
  void* ret = avb_malloc(size);
  if (ret == NULL) {
    return NULL;
  }

  avb_memset(ret, '\0', size);
  return ret;
}

char* avb_strdup(const char* str) {
  size_t len = avb_strlen(str);
  char* ret = avb_malloc(len + 1);
  if (ret == NULL) {
    return NULL;
  }

  avb_memcpy(ret, str, len);
  ret[len] = '\0';

  return ret;
}

const char* avb_strstr(const char* haystack, const char* needle) {
  size_t n, m;

  /* Look through |haystack| and check if the first character of
   * |needle| matches. If so, check the rest of |needle|.
   */
  for (n = 0; haystack[n] != '\0'; n++) {
    if (haystack[n] != needle[0]) {
      continue;
    }

    for (m = 1;; m++) {
      if (needle[m] == '\0') {
        return haystack + n;
      }

      if (haystack[n + m] != needle[m]) {
        break;
      }
    }
  }

  return NULL;
}

const char* avb_strv_find_str(const char* const* strings,
                              const char* str,
                              size_t str_size) {
  size_t n;
  for (n = 0; strings[n] != NULL; n++) {
    if (avb_strlen(strings[n]) == str_size &&
        avb_memcmp(strings[n], str, str_size) == 0) {
      return strings[n];
    }
  }
  return NULL;
}

char* avb_replace(const char* str, const char* search, const char* replace) {
  char* ret = NULL;
  size_t ret_len = 0;
  size_t search_len, replace_len;
  const char* str_after_last_replace;

  search_len = avb_strlen(search);
  replace_len = avb_strlen(replace);

  str_after_last_replace = str;
  while (*str != '\0') {
    const char* s;
    size_t num_before;
    size_t num_new;

    s = avb_strstr(str, search);
    if (s == NULL) {
      break;
    }

    num_before = s - str;

    if (ret == NULL) {
      num_new = num_before + replace_len + 1;
      ret = avb_malloc(num_new);
      if (ret == NULL) {
        goto out;
      }
      avb_memcpy(ret, str, num_before);
      avb_memcpy(ret + num_before, replace, replace_len);
      ret[num_new - 1] = '\0';
      ret_len = num_new - 1;
    } else {
      char* new_str;
      num_new = ret_len + num_before + replace_len + 1;
      new_str = avb_malloc(num_new);
      if (new_str == NULL) {
        goto out;
      }
      avb_memcpy(new_str, ret, ret_len);
      avb_memcpy(new_str + ret_len, str, num_before);
      avb_memcpy(new_str + ret_len + num_before, replace, replace_len);
      new_str[num_new - 1] = '\0';
      avb_free(ret);
      ret = new_str;
      ret_len = num_new - 1;
    }

    str = s + search_len;
    str_after_last_replace = str;
  }

  if (ret == NULL) {
    ret = avb_strdup(str_after_last_replace);
    if (ret == NULL) {
      goto out;
    }
  } else {
    size_t num_remaining = avb_strlen(str_after_last_replace);
    size_t num_new = ret_len + num_remaining + 1;
    char* new_str = avb_malloc(num_new);
    if (new_str == NULL) {
      goto out;
    }
    avb_memcpy(new_str, ret, ret_len);
    avb_memcpy(new_str + ret_len, str_after_last_replace, num_remaining);
    new_str[num_new - 1] = '\0';
    avb_free(ret);
    ret = new_str;
    ret_len = num_new - 1;
  }

out:
  return ret;
}

/* We only support a limited amount of strings in avb_strdupv(). */
#define AVB_STRDUPV_MAX_NUM_STRINGS 32

char* avb_strdupv(const char* str, ...) {
  va_list ap;
  const char* strings[AVB_STRDUPV_MAX_NUM_STRINGS];
  size_t lengths[AVB_STRDUPV_MAX_NUM_STRINGS];
  size_t num_strings, n;
  uint64_t total_length;
  char *ret = NULL, *dest;

  num_strings = 0;
  total_length = 0;
  va_start(ap, str);
  do {
    size_t str_len = avb_strlen(str);
    strings[num_strings] = str;
    lengths[num_strings] = str_len;
    if (!avb_safe_add_to(&total_length, str_len)) {
      avb_fatal("Overflow while determining total length.\n");
      break;
    }
    num_strings++;
    if (num_strings == AVB_STRDUPV_MAX_NUM_STRINGS) {
      avb_fatal("Too many strings passed.\n");
      break;
    }
    str = va_arg(ap, const char*);
  } while (str != NULL);
  va_end(ap);

  ret = avb_malloc(total_length + 1);
  if (ret == NULL) {
    goto out;
  }

  dest = ret;
  for (n = 0; n < num_strings; n++) {
    avb_memcpy(dest, strings[n], lengths[n]);
    dest += lengths[n];
  }
  *dest = '\0';
  avb_assert(dest == ret + total_length);

out:
  return ret;
}

const char* avb_basename(const char* str) {
  int64_t n;
  size_t len;

  len = avb_strlen(str);
  if (len >= 2) {
    for (n = len - 2; n >= 0; n--) {
      if (str[n] == '/') {
        return str + n + 1;
      }
    }
  }
  return str;
}

void avb_uppercase(char* str) {
  size_t i;
  for (i = 0; str[i] != '\0'; ++i) {
    if (str[i] <= 0x7A && str[i] >= 0x61) {
      str[i] -= 0x20;
    }
  }
}

char* avb_bin2hex(const uint8_t* data, size_t data_len) {
  const char hex_digits[17] = "0123456789abcdef";
  char* hex_data;
  size_t n;

  hex_data = avb_malloc(data_len * 2 + 1);
  if (hex_data == NULL) {
    return NULL;
  }

  for (n = 0; n < data_len; n++) {
    hex_data[n * 2] = hex_digits[data[n] >> 4];
    hex_data[n * 2 + 1] = hex_digits[data[n] & 0x0f];
  }
  hex_data[n * 2] = '\0';
  return hex_data;
}
