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

#include <android_avb/avb_property_descriptor.h>
#include <android_avb/avb_util.h>

bool avb_property_descriptor_validate_and_byteswap(
    const AvbPropertyDescriptor* src, AvbPropertyDescriptor* dest) {
  uint64_t expected_size;

  avb_memcpy(dest, src, sizeof(AvbPropertyDescriptor));

  if (!avb_descriptor_validate_and_byteswap((const AvbDescriptor*)src,
                                            (AvbDescriptor*)dest))
    return false;

  if (dest->parent_descriptor.tag != AVB_DESCRIPTOR_TAG_PROPERTY) {
    avb_error("Invalid tag for property descriptor.\n");
    return false;
  }

  dest->key_num_bytes = avb_be64toh(dest->key_num_bytes);
  dest->value_num_bytes = avb_be64toh(dest->value_num_bytes);

  /* Check that key and value are fully contained. */
  expected_size = sizeof(AvbPropertyDescriptor) - sizeof(AvbDescriptor) + 2;
  if (!avb_safe_add_to(&expected_size, dest->key_num_bytes) ||
      !avb_safe_add_to(&expected_size, dest->value_num_bytes)) {
    avb_error("Overflow while adding up sizes.\n");
    return false;
  }
  if (expected_size > dest->parent_descriptor.num_bytes_following) {
    avb_error("Descriptor payload size overflow.\n");
    return false;
  }

  return true;
}

typedef struct {
  const char* key;
  size_t key_size;
  const char* ret_value;
  size_t ret_value_size;
} PropertyIteratorData;

static bool property_lookup_desc_foreach(const AvbDescriptor* header,
                                         void* user_data) {
  PropertyIteratorData* data = (PropertyIteratorData*)user_data;
  AvbPropertyDescriptor prop_desc;
  const uint8_t* p;
  bool ret = true;

  if (header->tag != AVB_DESCRIPTOR_TAG_PROPERTY) {
    goto out;
  }

  if (!avb_property_descriptor_validate_and_byteswap(
          (const AvbPropertyDescriptor*)header, &prop_desc)) {
    goto out;
  }

  p = (const uint8_t*)header;
  if (p[sizeof(AvbPropertyDescriptor) + prop_desc.key_num_bytes] != 0) {
    avb_error("No terminating NUL byte in key.\n");
    goto out;
  }

  if (data->key_size == prop_desc.key_num_bytes) {
    if (avb_memcmp(p + sizeof(AvbPropertyDescriptor),
                   data->key,
                   data->key_size) == 0) {
      data->ret_value = (const char*)(p + sizeof(AvbPropertyDescriptor) +
                                      prop_desc.key_num_bytes + 1);
      data->ret_value_size = prop_desc.value_num_bytes;
      /* Stop iterating. */
      ret = false;
      goto out;
    }
  }

out:
  return ret;
}

const char* avb_property_lookup(const uint8_t* image_data,
                                size_t image_size,
                                const char* key,
                                size_t key_size,
                                size_t* out_value_size) {
  PropertyIteratorData data;

  if (key_size == 0) {
    key_size = avb_strlen(key);
  }

  data.key = key;
  data.key_size = key_size;

  if (avb_descriptor_foreach(
          image_data, image_size, property_lookup_desc_foreach, &data) == 0) {
    if (out_value_size != NULL) {
      *out_value_size = data.ret_value_size;
    }
    return data.ret_value;
  }

  if (out_value_size != NULL) {
    *out_value_size = 0;
  }
  return NULL;
}

bool avb_property_lookup_uint64(const uint8_t* image_data,
                                size_t image_size,
                                const char* key,
                                size_t key_size,
                                uint64_t* out_value) {
  const char* value;
  bool ret = false;
  uint64_t parsed_val;
  int base;
  int n;

  value = avb_property_lookup(image_data, image_size, key, key_size, NULL);
  if (value == NULL) {
    goto out;
  }

  base = 10;
  if (avb_memcmp(value, "0x", 2) == 0) {
    base = 16;
    value += 2;
  }

  parsed_val = 0;
  for (n = 0; value[n] != '\0'; n++) {
    int c = value[n];
    int digit;

    parsed_val *= base;

    if (c >= '0' && c <= '9') {
      digit = c - '0';
    } else if (base == 16 && c >= 'a' && c <= 'f') {
      digit = c - 'a' + 10;
    } else if (base == 16 && c >= 'A' && c <= 'F') {
      digit = c - 'A' + 10;
    } else {
      avb_error("Invalid digit.\n");
      goto out;
    }

    parsed_val += digit;
  }

  ret = true;
  if (out_value != NULL) {
    *out_value = parsed_val;
  }

out:
  return ret;
}
