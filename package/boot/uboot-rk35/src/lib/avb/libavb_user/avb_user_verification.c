/*
 * Copyright (C) 2017 The Android Open Source Project
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

#include <android_avb/avb_user_verification.h>

/* Maximum allow length (in bytes) of a partition name, including
 * ab_suffix.
 */
#define AVB_PART_NAME_MAX_SIZE 32

/* Loads the toplevel AvbVBMetaImageHeader from the slot denoted by
 * |ab_suffix| into |vbmeta_image|. No validation, verification, or
 * byteswapping is performed.
 *
 * If successful, |true| is returned and the partition it was loaded
 * from is returned in |out_partition_name| and the offset on said
 * partition is returned in |out_vbmeta_offset|.
 */
static bool load_top_level_vbmeta_header(
    AvbOps* ops,
    const char* ab_suffix,
    uint8_t vbmeta_image[AVB_VBMETA_IMAGE_HEADER_SIZE],
    char out_partition_name[AVB_PART_NAME_MAX_SIZE],
    uint64_t* out_vbmeta_offset) {
  uint64_t vbmeta_offset = 0;
  size_t num_read;
  bool ret = false;
  AvbIOResult io_res;

  /* Construct full partition name. */
  if (!avb_str_concat(out_partition_name,
                      AVB_PART_NAME_MAX_SIZE,
                      "vbmeta",
                      6,
                      ab_suffix,
                      avb_strlen(ab_suffix))) {
    avb_error("Partition name and suffix does not fit.\n");
    goto out;
  }

  /* Only read the header, not the entire struct. */
  io_res = ops->read_from_partition(ops,
                                    out_partition_name,
                                    vbmeta_offset,
                                    AVB_VBMETA_IMAGE_HEADER_SIZE,
                                    vbmeta_image,
                                    &num_read);
  if (io_res == AVB_IO_RESULT_ERROR_NO_SUCH_PARTITION) {
    AvbFooter footer;

    /* Try looking for the vbmeta struct in 'boot' via the footer. */
    if (!avb_str_concat(out_partition_name,
                        AVB_PART_NAME_MAX_SIZE,
                        "boot",
                        4,
                        ab_suffix,
                        avb_strlen(ab_suffix))) {
      avb_error("Partition name and suffix does not fit.\n");
      goto out;
    }
    io_res = ops->read_from_partition(ops,
                                      out_partition_name,
                                      -AVB_FOOTER_SIZE,
                                      AVB_FOOTER_SIZE,
                                      &footer,
                                      &num_read);
    if (io_res != AVB_IO_RESULT_OK) {
      avb_errorv("Error loading footer from partition '",
                 out_partition_name,
                 "'\n",
                 NULL);
      goto out;
    }

    if (avb_memcmp(footer.magic, AVB_FOOTER_MAGIC, AVB_FOOTER_MAGIC_LEN) != 0) {
      avb_errorv("Data from '",
                 out_partition_name,
                 "' does not look like a vbmeta footer.\n",
                 NULL);
      goto out;
    }

    vbmeta_offset = avb_be64toh(footer.vbmeta_offset);
    io_res = ops->read_from_partition(ops,
                                      out_partition_name,
                                      vbmeta_offset,
                                      AVB_VBMETA_IMAGE_HEADER_SIZE,
                                      vbmeta_image,
                                      &num_read);
  }

  if (io_res != AVB_IO_RESULT_OK) {
    avb_errorv(
        "Error loading from partition '", out_partition_name, "'\n", NULL);
    goto out;
  }

  if (out_vbmeta_offset != NULL) {
    *out_vbmeta_offset = vbmeta_offset;
  }

  ret = true;

out:
  return ret;
}

bool avb_user_verification_get(AvbOps* ops,
                               const char* ab_suffix,
                               bool* out_verification_enabled) {
  uint8_t vbmeta_image[AVB_VBMETA_IMAGE_HEADER_SIZE]; /* 256 bytes. */
  char partition_name[AVB_PART_NAME_MAX_SIZE];        /* 32 bytes. */
  AvbVBMetaImageHeader* header;
  uint32_t flags;
  bool ret = false;

  if (!load_top_level_vbmeta_header(
          ops, ab_suffix, vbmeta_image, partition_name, NULL)) {
    goto out;
  }

  if (avb_memcmp(vbmeta_image, AVB_MAGIC, AVB_MAGIC_LEN) != 0) {
    avb_errorv("Data from '",
               partition_name,
               "' does not look like a vbmeta header.\n",
               NULL);
    goto out;
  }

  /* Set/clear the VERIFICATION_DISABLED bit, as requested. */
  header = (AvbVBMetaImageHeader*)vbmeta_image;
  flags = avb_be32toh(header->flags);

  if (out_verification_enabled != NULL) {
    *out_verification_enabled =
        !(flags & AVB_VBMETA_IMAGE_FLAGS_VERIFICATION_DISABLED);
  }

  ret = true;

out:
  return ret;
}

bool avb_user_verification_set(AvbOps* ops,
                               const char* ab_suffix,
                               bool enable_verification) {
  uint8_t vbmeta_image[AVB_VBMETA_IMAGE_HEADER_SIZE]; /* 256 bytes. */
  char partition_name[AVB_PART_NAME_MAX_SIZE];        /* 32 bytes. */
  uint64_t vbmeta_offset;
  AvbIOResult io_res;
  AvbVBMetaImageHeader* header;
  uint32_t flags;
  bool ret = false;

  if (!load_top_level_vbmeta_header(
          ops, ab_suffix, vbmeta_image, partition_name, &vbmeta_offset)) {
    goto out;
  }

  if (avb_memcmp(vbmeta_image, AVB_MAGIC, AVB_MAGIC_LEN) != 0) {
    avb_errorv("Data from '",
               partition_name,
               "' does not look like a vbmeta header.\n",
               NULL);
    goto out;
  }

  /* Set/clear the VERIFICATION_DISABLED bit, as requested. */
  header = (AvbVBMetaImageHeader*)vbmeta_image;
  flags = avb_be32toh(header->flags);
  flags &= ~AVB_VBMETA_IMAGE_FLAGS_VERIFICATION_DISABLED;
  if (!enable_verification) {
    flags |= AVB_VBMETA_IMAGE_FLAGS_VERIFICATION_DISABLED;
  }
  header->flags = avb_htobe32(flags);

  /* Write the header. */
  io_res = ops->write_to_partition(ops,
                                   partition_name,
                                   vbmeta_offset,
                                   AVB_VBMETA_IMAGE_HEADER_SIZE,
                                   vbmeta_image);
  if (io_res != AVB_IO_RESULT_OK) {
    avb_errorv("Error writing to partition '", partition_name, "'\n", NULL);
    goto out;
  }

  ret = true;

out:
  return ret;
}
