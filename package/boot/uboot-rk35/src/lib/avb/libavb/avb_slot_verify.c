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
#include <common.h>
#include <sysmem.h>
#include <android_avb/avb_slot_verify.h>
#include <android_avb/avb_chain_partition_descriptor.h>
#include <android_avb/avb_cmdline.h>
#include <android_avb/avb_footer.h>
#include <android_avb/avb_hash_descriptor.h>
#include <android_avb/avb_hashtree_descriptor.h>
#include <android_avb/avb_kernel_cmdline_descriptor.h>
#include <android_avb/avb_sha.h>
#include <android_avb/avb_util.h>
#include <android_avb/avb_vbmeta_image.h>
#include <android_avb/avb_version.h>

/* Maximum number of partitions that can be loaded with avb_slot_verify(). */
#define MAX_NUMBER_OF_LOADED_PARTITIONS 32

/* Maximum number of vbmeta images that can be loaded with avb_slot_verify(). */
#define MAX_NUMBER_OF_VBMETA_IMAGES 32

/* Maximum size of a vbmeta image - 64 KiB. */
#define VBMETA_MAX_SIZE (64 * 1024)

static AvbSlotVerifyResult initialize_persistent_digest(
    AvbOps* ops,
    const char* part_name,
    const char* persistent_value_name,
    size_t digest_size,
    const uint8_t* initial_digest,
    uint8_t* out_digest);

/* Helper function to see if we should continue with verification in
 * allow_verification_error=true mode if something goes wrong. See the
 * comments for the avb_slot_verify() function for more information.
 */
static inline bool result_should_continue(AvbSlotVerifyResult result) {
  switch (result) {
    case AVB_SLOT_VERIFY_RESULT_ERROR_OOM:
    case AVB_SLOT_VERIFY_RESULT_ERROR_IO:
    case AVB_SLOT_VERIFY_RESULT_ERROR_INVALID_METADATA:
    case AVB_SLOT_VERIFY_RESULT_ERROR_UNSUPPORTED_VERSION:
    case AVB_SLOT_VERIFY_RESULT_ERROR_INVALID_ARGUMENT:
      return false;

    case AVB_SLOT_VERIFY_RESULT_OK:
    case AVB_SLOT_VERIFY_RESULT_ERROR_VERIFICATION:
    case AVB_SLOT_VERIFY_RESULT_ERROR_ROLLBACK_INDEX:
    case AVB_SLOT_VERIFY_RESULT_ERROR_PUBLIC_KEY_REJECTED:
      return true;
  }

  return false;
}

static AvbSlotVerifyResult load_full_partition(AvbOps* ops,
                                               const char* part_name,
                                               uint64_t image_size,
                                               uint8_t** out_image_buf,
                                               bool* out_image_preloaded,
                                               int allow_verification_error) {
  size_t part_num_read;
  AvbIOResult io_ret;

  /* Make sure that we do not overwrite existing data. */
  avb_assert(*out_image_buf == NULL);
  avb_assert(!*out_image_preloaded);

  /* We are going to implicitly cast image_size from uint64_t to size_t in the
   * following code, so we need to make sure that the cast is safe. */
  if (image_size != (size_t)(image_size)) {
    avb_errorv(part_name, ": Partition size too large to load.\n", NULL);
    return AVB_SLOT_VERIFY_RESULT_ERROR_INVALID_METADATA;
  }

  /* Try use a preloaded one. */
  if (ops->get_preloaded_partition != NULL) {
    io_ret = ops->get_preloaded_partition(
        ops, part_name, image_size, out_image_buf, &part_num_read,
	allow_verification_error);
    if (io_ret == AVB_IO_RESULT_ERROR_OOM) {
      return AVB_SLOT_VERIFY_RESULT_ERROR_OOM;
    } else if (io_ret != AVB_IO_RESULT_OK) {
      avb_errorv(part_name, ": Error loading data from partition.\n", NULL);
      return AVB_SLOT_VERIFY_RESULT_ERROR_IO;
    }

    if (*out_image_buf != NULL) {
      if (part_num_read != image_size) {
        avb_errorv(part_name, ": Read incorrect number of bytes.\n", NULL);
        return AVB_SLOT_VERIFY_RESULT_ERROR_IO;
      }
      *out_image_preloaded = true;
    }
  }

  /* Allocate and copy the partition. */
  if (!*out_image_preloaded) {
    *out_image_buf = sysmem_alloc(MEM_AVB_ANDROID, image_size);
    if (*out_image_buf == NULL) {
      return AVB_SLOT_VERIFY_RESULT_ERROR_OOM;
    }

    io_ret = ops->read_from_partition(ops,
                                      part_name,
                                      0 /* offset */,
                                      image_size,
                                      *out_image_buf,
                                      &part_num_read);
    if (io_ret == AVB_IO_RESULT_ERROR_OOM) {
      return AVB_SLOT_VERIFY_RESULT_ERROR_OOM;
    } else if (io_ret != AVB_IO_RESULT_OK) {
      avb_errorv(part_name, ": Error loading data from partition.\n", NULL);
      return AVB_SLOT_VERIFY_RESULT_ERROR_IO;
    }
    if (part_num_read != image_size) {
      avb_errorv(part_name, ": Read incorrect number of bytes.\n", NULL);
      return AVB_SLOT_VERIFY_RESULT_ERROR_IO;
    }
  }

  return AVB_SLOT_VERIFY_RESULT_OK;
}

/* Reads a persistent digest stored as a named persistent value corresponding to
 * the given |part_name|. The value is returned in |out_digest| which must point
 * to |expected_digest_size| bytes. If there is no digest stored for |part_name|
 * it can be initialized by providing a non-NULL |initial_digest| of length
 * |expected_digest_size|. This automatic initialization will only occur if the
 * device is currently locked. The |initial_digest| may be NULL.
 *
 * Returns AVB_SLOT_VERIFY_RESULT_OK on success, otherwise returns an
 * AVB_SLOT_VERIFY_RESULT_ERROR_* error code.
 *
 * If the value does not exist, is not supported, or is not populated, and
 * |initial_digest| is NULL, returns
 * AVB_SLOT_VERIFY_RESULT_ERROR_INVALID_METADATA. If |expected_digest_size| does
 * not match the stored digest size, also returns
 * AVB_SLOT_VERIFY_RESULT_ERROR_INVALID_METADATA.
 */
static AvbSlotVerifyResult read_persistent_digest(AvbOps* ops,
                                                  const char* part_name,
                                                  size_t expected_digest_size,
                                                  const uint8_t* initial_digest,
                                                  uint8_t* out_digest) {
  char* persistent_value_name = NULL;
  AvbIOResult io_ret = AVB_IO_RESULT_OK;
  size_t stored_digest_size = 0;

  if (ops->read_persistent_value == NULL) {
    avb_errorv(part_name, ": Persistent values are not implemented.\n", NULL);
    return AVB_SLOT_VERIFY_RESULT_ERROR_INVALID_METADATA;
  }
  persistent_value_name =
      avb_strdupv(AVB_NPV_PERSISTENT_DIGEST_PREFIX, part_name, NULL);
  if (persistent_value_name == NULL) {
    return AVB_SLOT_VERIFY_RESULT_ERROR_OOM;
  }

  io_ret = ops->read_persistent_value(ops,
                                      persistent_value_name,
                                      expected_digest_size,
                                      out_digest,
                                      &stored_digest_size);

  // If no such named persistent value exists and an initial digest value was
  // given, initialize the named persistent value with the given digest. If
  // initialized successfully, this will recurse into this function but with a
  // NULL initial_digest.
  if (io_ret == AVB_IO_RESULT_ERROR_NO_SUCH_VALUE && initial_digest) {
    AvbSlotVerifyResult ret =
        initialize_persistent_digest(ops,
                                     part_name,
                                     persistent_value_name,
                                     expected_digest_size,
                                     initial_digest,
                                     out_digest);
    avb_free(persistent_value_name);
    return ret;
  }
  avb_free(persistent_value_name);

  if (io_ret == AVB_IO_RESULT_ERROR_OOM) {
    return AVB_SLOT_VERIFY_RESULT_ERROR_OOM;
  } else if (io_ret == AVB_IO_RESULT_ERROR_NO_SUCH_VALUE) {
    // Treat a missing persistent value as a verification error, which is
    // ignoreable, rather than a metadata error which is not.
    avb_errorv(part_name, ": Persistent digest does not exist.\n", NULL);
    return AVB_SLOT_VERIFY_RESULT_ERROR_VERIFICATION;
  } else if (io_ret == AVB_IO_RESULT_ERROR_INVALID_VALUE_SIZE ||
             io_ret == AVB_IO_RESULT_ERROR_INSUFFICIENT_SPACE) {
    avb_errorv(
        part_name, ": Persistent digest is not of expected size.\n", NULL);
    return AVB_SLOT_VERIFY_RESULT_ERROR_INVALID_METADATA;
  } else if (io_ret != AVB_IO_RESULT_OK) {
    avb_errorv(part_name, ": Error reading persistent digest.\n", NULL);
    return AVB_SLOT_VERIFY_RESULT_ERROR_IO;
  } else if (expected_digest_size != stored_digest_size) {
    avb_errorv(
        part_name, ": Persistent digest is not of expected size.\n", NULL);
    return AVB_SLOT_VERIFY_RESULT_ERROR_INVALID_METADATA;
  }
  return AVB_SLOT_VERIFY_RESULT_OK;
}

static AvbSlotVerifyResult initialize_persistent_digest(
    AvbOps* ops,
    const char* part_name,
    const char* persistent_value_name,
    size_t digest_size,
    const uint8_t* initial_digest,
    uint8_t* out_digest) {
  AvbSlotVerifyResult ret;
  AvbIOResult io_ret = AVB_IO_RESULT_OK;
  bool is_device_unlocked = true;

  io_ret = ops->read_is_device_unlocked(ops, &is_device_unlocked);
  if (io_ret == AVB_IO_RESULT_ERROR_OOM) {
    return AVB_SLOT_VERIFY_RESULT_ERROR_OOM;
  } else if (io_ret != AVB_IO_RESULT_OK) {
    avb_error("Error getting device lock state.\n");
    return AVB_SLOT_VERIFY_RESULT_ERROR_IO;
  }

  if (is_device_unlocked) {
    avb_debugv(part_name,
               ": Digest does not exist, device unlocked so not initializing "
               "digest.\n",
               NULL);
    return AVB_SLOT_VERIFY_RESULT_ERROR_VERIFICATION;
  }

  // Device locked; initialize digest with given initial value.
  avb_debugv(part_name,
             ": Digest does not exist, initializing persistent digest.\n",
             NULL);
  io_ret = ops->write_persistent_value(
      ops, persistent_value_name, digest_size, initial_digest);
  if (io_ret == AVB_IO_RESULT_ERROR_OOM) {
    return AVB_SLOT_VERIFY_RESULT_ERROR_OOM;
  } else if (io_ret != AVB_IO_RESULT_OK) {
    avb_errorv(part_name, ": Error initializing persistent digest.\n", NULL);
    return AVB_SLOT_VERIFY_RESULT_ERROR_IO;
  }

  // To ensure that the digest value was written successfully - and avoid a
  // scenario where the digest is simply 'initialized' on every verify - recurse
  // into read_persistent_digest to read back the written value. The NULL
  // initial_digest ensures that this will not recurse again.
  ret = read_persistent_digest(ops, part_name, digest_size, NULL, out_digest);
  if (ret != AVB_SLOT_VERIFY_RESULT_OK) {
    avb_errorv(part_name,
               ": Reading back initialized persistent digest failed!\n",
               NULL);
  }
  return ret;
}

static AvbSlotVerifyResult load_and_verify_hash_partition(
    AvbOps* ops,
    const char* const* requested_partitions,
    const char* ab_suffix,
    bool allow_verification_error,
    const AvbDescriptor* descriptor,
    AvbSlotVerifyData* slot_data) {
  AvbHashDescriptor hash_desc;
  const uint8_t* desc_partition_name = NULL;
  const uint8_t* desc_salt;
  const uint8_t* desc_digest;
  char part_name[AVB_PART_NAME_MAX_SIZE];
  AvbSlotVerifyResult ret;
  AvbIOResult io_ret;
  uint8_t* image_buf = NULL;
  bool image_preloaded = false;
  uint8_t* digest;
  size_t digest_len;
  const char* found;
  uint64_t image_size;
  size_t expected_digest_len = 0;
  uint8_t expected_digest_buf[AVB_SHA512_DIGEST_SIZE];
  const uint8_t* expected_digest = NULL;

  if (!avb_hash_descriptor_validate_and_byteswap(
          (const AvbHashDescriptor*)descriptor, &hash_desc)) {
    ret = AVB_SLOT_VERIFY_RESULT_ERROR_INVALID_METADATA;
    goto out;
  }

  desc_partition_name =
      ((const uint8_t*)descriptor) + sizeof(AvbHashDescriptor);
  desc_salt = desc_partition_name + hash_desc.partition_name_len;
  desc_digest = desc_salt + hash_desc.salt_len;

  if (!avb_validate_utf8(desc_partition_name, hash_desc.partition_name_len)) {
    avb_error("Partition name is not valid UTF-8.\n");
    ret = AVB_SLOT_VERIFY_RESULT_ERROR_INVALID_METADATA;
    goto out;
  }

  /* Don't bother loading or validating unless the partition was
   * requested in the first place.
   */
  found = avb_strv_find_str(requested_partitions,
                            (const char*)desc_partition_name,
                            hash_desc.partition_name_len);
  if (found == NULL) {
    ret = AVB_SLOT_VERIFY_RESULT_OK;
    goto out;
  }

  if ((hash_desc.flags & AVB_HASH_DESCRIPTOR_FLAGS_DO_NOT_USE_AB) != 0) {
    /* No ab_suffix, just copy the partition name as is. */
    if (hash_desc.partition_name_len >= AVB_PART_NAME_MAX_SIZE) {
      avb_error("Partition name does not fit.\n");
      ret = AVB_SLOT_VERIFY_RESULT_ERROR_INVALID_METADATA;
      goto out;
    }
    avb_memcpy(part_name, desc_partition_name, hash_desc.partition_name_len);
    part_name[hash_desc.partition_name_len] = '\0';
  } else if (hash_desc.digest_len == 0 && avb_strlen(ab_suffix) != 0) {
    /* No ab_suffix allowed for partitions without a digest in the descriptor
     * because these partitions hold data unique to this device and are not
     * updated using an A/B scheme.
     */
    avb_error("Cannot use A/B with a persistent digest.\n");
    ret = AVB_SLOT_VERIFY_RESULT_ERROR_INVALID_METADATA;
    goto out;
  } else {
    /* Add ab_suffix to the partition name. */
    if (!avb_str_concat(part_name,
                        sizeof part_name,
                        (const char*)desc_partition_name,
                        hash_desc.partition_name_len,
                        ab_suffix,
                        avb_strlen(ab_suffix))) {
      avb_error("Partition name and suffix does not fit.\n");
      ret = AVB_SLOT_VERIFY_RESULT_ERROR_INVALID_METADATA;
      goto out;
    }
  }

  /* If we're allowing verification errors then hash_desc.image_size
   * may no longer match what's in the partition... so in this case
   * just load the entire partition.
   *
   * For example, this can happen if a developer does 'fastboot flash
   * boot /path/to/new/and/bigger/boot.img'. We want this to work
   * since it's such a common workflow.
   */
  image_size = hash_desc.image_size;
  if (allow_verification_error) {
    io_ret = ops->get_size_of_partition(ops, part_name, &image_size);
    if (io_ret == AVB_IO_RESULT_ERROR_OOM) {
      ret = AVB_SLOT_VERIFY_RESULT_ERROR_OOM;
      goto out;
    } else if (io_ret != AVB_IO_RESULT_OK) {
      avb_errorv(part_name, ": Error determining partition size.\n", NULL);
      ret = AVB_SLOT_VERIFY_RESULT_ERROR_IO;
      goto out;
    }
    avb_debugv(part_name, ": Loading entire partition.\n", NULL);
  }

  ret = load_full_partition(
      ops, part_name, image_size, &image_buf, &image_preloaded,
      allow_verification_error);
  if (ret != AVB_SLOT_VERIFY_RESULT_OK) {
    goto out;
  } else if (image_preloaded) {
    goto out;
  }

  // Although only one of the type might be used, we have to defined the
  // structure here so that they would live outside the 'if/else' scope to be
  // used later.
  AvbSHA256Ctx sha256_ctx;
  AvbSHA512Ctx sha512_ctx;
  size_t image_size_to_hash = hash_desc.image_size;
  // If we allow verification error and the whole partition is smaller than
  // image size in hash descriptor, we just hash the whole partition.
  if (image_size_to_hash > image_size) {
    image_size_to_hash = image_size;
  }
  if (avb_strcmp((const char*)hash_desc.hash_algorithm, "sha256") == 0) {
    sha256_ctx.tot_len = hash_desc.salt_len + image_size_to_hash;
    avb_sha256_init(&sha256_ctx);
    avb_sha256_update(&sha256_ctx, desc_salt, hash_desc.salt_len);
    avb_sha256_update(&sha256_ctx, image_buf, image_size_to_hash);
    digest = avb_sha256_final(&sha256_ctx);
    digest_len = AVB_SHA256_DIGEST_SIZE;
  } else if (avb_strcmp((const char*)hash_desc.hash_algorithm, "sha512") == 0) {
    sha512_ctx.tot_len = hash_desc.salt_len + image_size_to_hash;
    avb_sha512_init(&sha512_ctx);
    avb_sha512_update(&sha512_ctx, desc_salt, hash_desc.salt_len);
    avb_sha512_update(&sha512_ctx, image_buf, image_size_to_hash);
    digest = avb_sha512_final(&sha512_ctx);
    digest_len = AVB_SHA512_DIGEST_SIZE;
  } else {
    avb_errorv(part_name, ": Unsupported hash algorithm.\n", NULL);
    ret = AVB_SLOT_VERIFY_RESULT_ERROR_INVALID_METADATA;
    goto out;
  }

  if (hash_desc.digest_len == 0) {
    /* Expect a match to a persistent digest. */
    avb_debugv(part_name, ": No digest, using persistent digest.\n", NULL);
    expected_digest_len = digest_len;
    expected_digest = expected_digest_buf;
    avb_assert(expected_digest_len <= sizeof(expected_digest_buf));
    /* Pass |digest| as the |initial_digest| so devices not yet initialized get
     * initialized to the current partition digest.
     */
    ret = read_persistent_digest(
        ops, part_name, digest_len, digest, expected_digest_buf);
    if (ret != AVB_SLOT_VERIFY_RESULT_OK) {
      goto out;
    }
  } else {
    /* Expect a match to the digest in the descriptor. */
    expected_digest_len = hash_desc.digest_len;
    expected_digest = desc_digest;
  }

  if (digest_len != expected_digest_len) {
    avb_errorv(
        part_name, ": Digest in descriptor not of expected size.\n", NULL);
    ret = AVB_SLOT_VERIFY_RESULT_ERROR_INVALID_METADATA;
    goto out;
  }

  if (avb_safe_memcmp(digest, expected_digest, digest_len) != 0) {
    avb_errorv(part_name,
               ": Hash of data does not match digest in descriptor.\n",
               NULL);
    ret = AVB_SLOT_VERIFY_RESULT_ERROR_VERIFICATION;
    goto out;
  }

  ret = AVB_SLOT_VERIFY_RESULT_OK;

out:

  /* If it worked and something was loaded, copy to slot_data. */
  if ((ret == AVB_SLOT_VERIFY_RESULT_OK || result_should_continue(ret)) &&
      image_buf != NULL) {
    AvbPartitionData* loaded_partition;
    if (slot_data->num_loaded_partitions == MAX_NUMBER_OF_LOADED_PARTITIONS) {
      avb_errorv(part_name, ": Too many loaded partitions.\n", NULL);
      ret = AVB_SLOT_VERIFY_RESULT_ERROR_OOM;
      goto fail;
    }
    loaded_partition =
        &slot_data->loaded_partitions[slot_data->num_loaded_partitions++];
    loaded_partition->partition_name = avb_strdup(found);
    loaded_partition->data_size = image_size;
    loaded_partition->data = image_buf;
    loaded_partition->preloaded = image_preloaded;
    image_buf = NULL;
  }

fail:
  if (image_buf != NULL && !image_preloaded) {
    sysmem_free((phys_addr_t)image_buf);
  }
  return ret;
}

static AvbSlotVerifyResult load_requested_partitions(
    AvbOps* ops,
    const char* const* requested_partitions,
    const char* ab_suffix,
    AvbSlotVerifyData* slot_data) {
  AvbSlotVerifyResult ret;
  uint8_t* image_buf = NULL;
  bool image_preloaded = false;
  size_t n;

  for (n = 0; requested_partitions[n] != NULL; n++) {
    char part_name[AVB_PART_NAME_MAX_SIZE];
    AvbIOResult io_ret;
    uint64_t image_size;
    AvbPartitionData* loaded_partition;

    if (!avb_str_concat(part_name,
                        sizeof part_name,
                        requested_partitions[n],
                        avb_strlen(requested_partitions[n]),
                        ab_suffix,
                        avb_strlen(ab_suffix))) {
      avb_error("Partition name and suffix does not fit.\n");
      ret = AVB_SLOT_VERIFY_RESULT_ERROR_INVALID_METADATA;
      goto out;
    }

    io_ret = ops->get_size_of_partition(ops, part_name, &image_size);
    if (io_ret == AVB_IO_RESULT_ERROR_OOM) {
      ret = AVB_SLOT_VERIFY_RESULT_ERROR_OOM;
      goto out;
    } else if (io_ret != AVB_IO_RESULT_OK) {
      avb_errorv(part_name, ": Error determining partition size.\n", NULL);
      ret = AVB_SLOT_VERIFY_RESULT_ERROR_IO;
      goto out;
    }
    avb_debugv(part_name, ": Loading entire partition.\n", NULL);

    ret = load_full_partition(
        ops, part_name, image_size, &image_buf, &image_preloaded, 1);
    if (ret != AVB_SLOT_VERIFY_RESULT_OK) {
      goto out;
    }

    /* Move to slot_data. */
    if (slot_data->num_loaded_partitions == MAX_NUMBER_OF_LOADED_PARTITIONS) {
      avb_errorv(part_name, ": Too many loaded partitions.\n", NULL);
      ret = AVB_SLOT_VERIFY_RESULT_ERROR_OOM;
      goto out;
    }
    loaded_partition =
        &slot_data->loaded_partitions[slot_data->num_loaded_partitions++];
    loaded_partition->partition_name = avb_strdup(requested_partitions[n]);
    if (loaded_partition->partition_name == NULL) {
      ret = AVB_SLOT_VERIFY_RESULT_ERROR_OOM;
      goto out;
    }
    loaded_partition->data_size = image_size;
    loaded_partition->data = image_buf; /* Transferring the owner. */
    loaded_partition->preloaded = image_preloaded;
    image_buf = NULL;
    image_preloaded = false;
  }

  ret = AVB_SLOT_VERIFY_RESULT_OK;

out:
  /* Free the current buffer if any. */
  if (image_buf != NULL && !image_preloaded) {
    sysmem_free((phys_addr_t)image_buf);
  }
  /* Buffers that are already saved in slot_data will be handled by the caller
   * even on failure. */
  return ret;
}

static AvbSlotVerifyResult load_and_verify_vbmeta(
    AvbOps* ops,
    const char* const* requested_partitions,
    const char* ab_suffix,
    AvbSlotVerifyFlags flags,
    bool allow_verification_error,
    AvbVBMetaImageFlags toplevel_vbmeta_flags,
    int rollback_index_location,
    const char* partition_name,
    size_t partition_name_len,
    const uint8_t* expected_public_key,
    size_t expected_public_key_length,
    AvbSlotVerifyData* slot_data,
    AvbAlgorithmType* out_algorithm_type,
    AvbCmdlineSubstList* out_additional_cmdline_subst) {
  char full_partition_name[AVB_PART_NAME_MAX_SIZE];
  AvbSlotVerifyResult ret;
  AvbIOResult io_ret;
  uint64_t vbmeta_offset;
  size_t vbmeta_size;
  uint8_t* vbmeta_buf = NULL;
  size_t vbmeta_num_read;
  AvbVBMetaVerifyResult vbmeta_ret;
  const uint8_t* pk_data;
  size_t pk_len;
  AvbVBMetaImageHeader vbmeta_header;
  uint64_t stored_rollback_index;
  const AvbDescriptor** descriptors = NULL;
  size_t num_descriptors;
  size_t n;
  bool is_main_vbmeta;
  bool look_for_vbmeta_footer;
  AvbVBMetaData* vbmeta_image_data = NULL;

  ret = AVB_SLOT_VERIFY_RESULT_OK;

  avb_assert(slot_data != NULL);

  /* Since we allow top-level vbmeta in 'boot', use
   * rollback_index_location to determine whether we're the main
   * vbmeta struct.
   */
  is_main_vbmeta = false;
  if (rollback_index_location == 0) {
    if ((flags & AVB_SLOT_VERIFY_FLAGS_NO_VBMETA_PARTITION) == 0) {
      is_main_vbmeta = true;
    }
  }

  /* Don't use footers for vbmeta partitions ('vbmeta' or
   * 'vbmeta_<partition_name>').
   */
  look_for_vbmeta_footer = true;
  if (avb_strncmp(partition_name, "vbmeta", avb_strlen("vbmeta")) == 0) {
    look_for_vbmeta_footer = false;
  }

  if (!avb_validate_utf8((const uint8_t*)partition_name, partition_name_len)) {
    avb_error("Partition name is not valid UTF-8.\n");
    ret = AVB_SLOT_VERIFY_RESULT_ERROR_INVALID_METADATA;
    goto out;
  }

  /* Construct full partition name e.g. system_a. */
  if (!avb_str_concat(full_partition_name,
                      sizeof full_partition_name,
                      partition_name,
                      partition_name_len,
                      ab_suffix,
                      avb_strlen(ab_suffix))) {
    avb_error("Partition name and suffix does not fit.\n");
    ret = AVB_SLOT_VERIFY_RESULT_ERROR_INVALID_METADATA;
    goto out;
  }

  /* If we're loading from the main vbmeta partition, the vbmeta struct is in
   * the beginning. Otherwise we may have to locate it via a footer... if no
   * footer is found, we look in the beginning to support e.g. vbmeta_<org>
   * partitions holding data for e.g. super partitions (b/80195851 for
   * rationale).
   */
  vbmeta_offset = 0;
  vbmeta_size = VBMETA_MAX_SIZE;
  if (look_for_vbmeta_footer) {
    uint8_t footer_buf[AVB_FOOTER_SIZE];
    size_t footer_num_read;
    AvbFooter footer;

    io_ret = ops->read_from_partition(ops,
                                      full_partition_name,
                                      -AVB_FOOTER_SIZE,
                                      AVB_FOOTER_SIZE,
                                      footer_buf,
                                      &footer_num_read);
    if (io_ret == AVB_IO_RESULT_ERROR_OOM) {
      ret = AVB_SLOT_VERIFY_RESULT_ERROR_OOM;
      goto out;
    } else if (io_ret != AVB_IO_RESULT_OK) {
      avb_errorv(full_partition_name, ": Error loading footer.\n", NULL);
      ret = AVB_SLOT_VERIFY_RESULT_ERROR_IO;
      goto out;
    }
    avb_assert(footer_num_read == AVB_FOOTER_SIZE);

    if (!avb_footer_validate_and_byteswap((const AvbFooter*)footer_buf,
                                          &footer)) {
      avb_debugv(full_partition_name, ": No footer detected.\n", NULL);
    } else {
      /* Basic footer sanity check since the data is untrusted. */
      if (footer.vbmeta_size > VBMETA_MAX_SIZE) {
        avb_errorv(
            full_partition_name, ": Invalid vbmeta size in footer.\n", NULL);
      } else {
        vbmeta_offset = footer.vbmeta_offset;
        vbmeta_size = footer.vbmeta_size;
      }
    }
  }

  vbmeta_buf = avb_malloc(vbmeta_size);
  if (vbmeta_buf == NULL) {
    ret = AVB_SLOT_VERIFY_RESULT_ERROR_OOM;
    goto out;
  }

  if (vbmeta_offset != 0) {
    avb_debugv("Loading vbmeta struct in footer from partition '",
               full_partition_name,
               "'.\n",
               NULL);
  } else {
    avb_debugv("Loading vbmeta struct from partition '",
               full_partition_name,
               "'.\n",
               NULL);
  }

  io_ret = ops->read_from_partition(ops,
                                    full_partition_name,
                                    vbmeta_offset,
                                    vbmeta_size,
                                    vbmeta_buf,
                                    &vbmeta_num_read);
  if (io_ret == AVB_IO_RESULT_ERROR_OOM) {
    ret = AVB_SLOT_VERIFY_RESULT_ERROR_OOM;
    goto out;
  } else if (io_ret != AVB_IO_RESULT_OK) {
    /* If we're looking for 'vbmeta' but there is no such partition,
     * go try to get it from the boot partition instead.
     */
    if (is_main_vbmeta && io_ret == AVB_IO_RESULT_ERROR_NO_SUCH_PARTITION &&
        !look_for_vbmeta_footer) {
      avb_debugv(full_partition_name,
                 ": No such partition. Trying 'boot' instead.\n",
                 NULL);
      ret = load_and_verify_vbmeta(ops,
                                   requested_partitions,
                                   ab_suffix,
                                   flags,
                                   allow_verification_error,
                                   0 /* toplevel_vbmeta_flags */,
                                   0 /* rollback_index_location */,
                                   "boot",
                                   avb_strlen("boot"),
                                   NULL /* expected_public_key */,
                                   0 /* expected_public_key_length */,
                                   slot_data,
                                   out_algorithm_type,
                                   out_additional_cmdline_subst);
      goto out;
    } else {
      avb_errorv(full_partition_name, ": Error loading vbmeta data.\n", NULL);
      ret = AVB_SLOT_VERIFY_RESULT_ERROR_IO;
      goto out;
    }
  }
  avb_assert(vbmeta_num_read <= vbmeta_size);

  /* Check if the image is properly signed and get the public key used
   * to sign the image.
   */
  vbmeta_ret =
      avb_vbmeta_image_verify(vbmeta_buf, vbmeta_num_read, &pk_data, &pk_len);
  switch (vbmeta_ret) {
    case AVB_VBMETA_VERIFY_RESULT_OK:
      avb_assert(pk_data != NULL && pk_len > 0);
      break;

    case AVB_VBMETA_VERIFY_RESULT_OK_NOT_SIGNED:
    case AVB_VBMETA_VERIFY_RESULT_HASH_MISMATCH:
    case AVB_VBMETA_VERIFY_RESULT_SIGNATURE_MISMATCH:
      ret = AVB_SLOT_VERIFY_RESULT_ERROR_VERIFICATION;
      avb_errorv(full_partition_name,
                 ": Error verifying vbmeta image: ",
                 avb_vbmeta_verify_result_to_string(vbmeta_ret),
                 "\n",
                 NULL);
      if (!allow_verification_error) {
        goto out;
      }
      break;

    case AVB_VBMETA_VERIFY_RESULT_INVALID_VBMETA_HEADER:
      /* No way to continue this case. */
      ret = AVB_SLOT_VERIFY_RESULT_ERROR_INVALID_METADATA;
      avb_errorv(full_partition_name,
                 ": Error verifying vbmeta image: invalid vbmeta header\n",
                 NULL);
      goto out;

    case AVB_VBMETA_VERIFY_RESULT_UNSUPPORTED_VERSION:
      /* No way to continue this case. */
      ret = AVB_SLOT_VERIFY_RESULT_ERROR_UNSUPPORTED_VERSION;
      avb_errorv(full_partition_name,
                 ": Error verifying vbmeta image: unsupported AVB version\n",
                 NULL);
      goto out;
  }

  /* Byteswap the header. */
  avb_vbmeta_image_header_to_host_byte_order((AvbVBMetaImageHeader*)vbmeta_buf,
                                             &vbmeta_header);

  /* If we're the toplevel, assign flags so they'll be passed down. */
  if (is_main_vbmeta) {
    toplevel_vbmeta_flags = (AvbVBMetaImageFlags)vbmeta_header.flags;
  } else {
    if (vbmeta_header.flags != 0) {
      ret = AVB_SLOT_VERIFY_RESULT_ERROR_INVALID_METADATA;
      avb_errorv(full_partition_name,
                 ": chained vbmeta image has non-zero flags\n",
                 NULL);
      goto out;
    }
  }

  uint32_t rollback_index_location_to_use = rollback_index_location;

  /* Check if key used to make signature matches what is expected. */
  if (pk_data != NULL) {
    if (expected_public_key != NULL) {
      avb_assert(!is_main_vbmeta);
      if (expected_public_key_length != pk_len ||
          avb_safe_memcmp(expected_public_key, pk_data, pk_len) != 0) {
        avb_errorv(full_partition_name,
                   ": Public key used to sign data does not match key in chain "
                   "partition descriptor.\n",
                   NULL);
        ret = AVB_SLOT_VERIFY_RESULT_ERROR_PUBLIC_KEY_REJECTED;
        if (!allow_verification_error) {
          goto out;
        }
      }
    } else {
      bool key_is_trusted = false;
      const uint8_t* pk_metadata = NULL;
      size_t pk_metadata_len = 0;

      if (vbmeta_header.public_key_metadata_size > 0) {
        pk_metadata = vbmeta_buf + sizeof(AvbVBMetaImageHeader) +
                      vbmeta_header.authentication_data_block_size +
                      vbmeta_header.public_key_metadata_offset;
        pk_metadata_len = vbmeta_header.public_key_metadata_size;
      }

      // If we're not using a vbmeta partition, need to use another AvbOps...
      if (flags & AVB_SLOT_VERIFY_FLAGS_NO_VBMETA_PARTITION) {
        io_ret = ops->validate_public_key_for_partition(
            ops,
            full_partition_name,
            pk_data,
            pk_len,
            pk_metadata,
            pk_metadata_len,
            &key_is_trusted,
            &rollback_index_location_to_use);
      } else {
        avb_assert(is_main_vbmeta);
        io_ret = ops->validate_vbmeta_public_key(ops,
                                                 pk_data,
                                                 pk_len,
                                                 pk_metadata,
                                                 pk_metadata_len,
                                                 &key_is_trusted);
      }

      if (io_ret == AVB_IO_RESULT_ERROR_OOM) {
        ret = AVB_SLOT_VERIFY_RESULT_ERROR_OOM;
        goto out;
      } else if (io_ret != AVB_IO_RESULT_OK) {
        avb_errorv(full_partition_name,
                   ": Error while checking public key used to sign data.\n",
                   NULL);
        ret = AVB_SLOT_VERIFY_RESULT_ERROR_IO;
        goto out;
      }
      if (!key_is_trusted) {
        avb_errorv(full_partition_name,
                   ": Public key used to sign data rejected.\n",
                   NULL);
        ret = AVB_SLOT_VERIFY_RESULT_ERROR_PUBLIC_KEY_REJECTED;
        if (!allow_verification_error) {
          goto out;
        }
      }
    }
  }

  /* Check rollback index. */
  io_ret = ops->read_rollback_index(
      ops, rollback_index_location_to_use, &stored_rollback_index);
  if (io_ret == AVB_IO_RESULT_ERROR_OOM) {
    ret = AVB_SLOT_VERIFY_RESULT_ERROR_OOM;
    goto out;
  } else if (io_ret != AVB_IO_RESULT_OK) {
    avb_errorv(full_partition_name,
               ": Error getting rollback index for location.\n",
               NULL);
    ret = AVB_SLOT_VERIFY_RESULT_ERROR_IO;
    goto out;
  }
  if (vbmeta_header.rollback_index < stored_rollback_index) {
    avb_errorv(
        full_partition_name,
        ": Image rollback index is less than the stored rollback index.\n",
        NULL);
    ret = AVB_SLOT_VERIFY_RESULT_ERROR_ROLLBACK_INDEX;
    if (!allow_verification_error) {
      goto out;
    }
  }

  /* Copy vbmeta to vbmeta_images before recursing. */
  if (is_main_vbmeta) {
    avb_assert(slot_data->num_vbmeta_images == 0);
  } else {
    if (!(flags & AVB_SLOT_VERIFY_FLAGS_NO_VBMETA_PARTITION)) {
      avb_assert(slot_data->num_vbmeta_images > 0);
    }
  }
  if (slot_data->num_vbmeta_images == MAX_NUMBER_OF_VBMETA_IMAGES) {
    avb_errorv(full_partition_name, ": Too many vbmeta images.\n", NULL);
    ret = AVB_SLOT_VERIFY_RESULT_ERROR_OOM;
    goto out;
  }
  vbmeta_image_data = &slot_data->vbmeta_images[slot_data->num_vbmeta_images++];
  vbmeta_image_data->partition_name = avb_strdup(partition_name);
  vbmeta_image_data->vbmeta_data = vbmeta_buf;
  /* Note that |vbmeta_buf| is actually |vbmeta_num_read| bytes long
   * and this includes data past the end of the image. Pass the
   * actual size of the vbmeta image. Also, no need to use
   * avb_safe_add() since the header has already been verified.
   */
  vbmeta_image_data->vbmeta_size =
      sizeof(AvbVBMetaImageHeader) +
      vbmeta_header.authentication_data_block_size +
      vbmeta_header.auxiliary_data_block_size;
  vbmeta_image_data->verify_result = vbmeta_ret;

  /* If verification has been disabled by setting a bit in the image,
   * we're done... except that we need to load the entirety of the
   * requested partitions.
   */
  if (vbmeta_header.flags & AVB_VBMETA_IMAGE_FLAGS_VERIFICATION_DISABLED) {
    AvbSlotVerifyResult sub_ret;
    avb_debugv(
        full_partition_name, ": VERIFICATION_DISABLED bit is set.\n", NULL);
    /* If load_requested_partitions() fail it is always a fatal
     * failure (e.g. ERROR_INVALID_ARGUMENT, ERROR_OOM, etc.) rather
     * than recoverable (e.g. one where result_should_continue()
     * returns true) and we want to convey that error.
     */
    sub_ret = load_requested_partitions(
        ops, requested_partitions, ab_suffix, slot_data);
    if (sub_ret != AVB_SLOT_VERIFY_RESULT_OK) {
      ret = sub_ret;
    }
    goto out;
  }

  /* Now go through all descriptors and take the appropriate action:
   *
   * - hash descriptor: Load data from partition, calculate hash, and
   *   checks that it matches what's in the hash descriptor.
   *
   * - hashtree descriptor: Do nothing since verification happens
   *   on-the-fly from within the OS. (Unless the descriptor uses a
   *   persistent digest, in which case we need to find it).
   *
   * - chained partition descriptor: Load the footer, load the vbmeta
   *   image, verify vbmeta image (includes rollback checks, hash
   *   checks, bail on chained partitions).
   */
  descriptors =
      avb_descriptor_get_all(vbmeta_buf, vbmeta_num_read, &num_descriptors);
  for (n = 0; n < num_descriptors; n++) {
    AvbDescriptor desc;

    if (!avb_descriptor_validate_and_byteswap(descriptors[n], &desc)) {
      avb_errorv(full_partition_name, ": Descriptor is invalid.\n", NULL);
      ret = AVB_SLOT_VERIFY_RESULT_ERROR_INVALID_METADATA;
      goto out;
    }

    switch (desc.tag) {
      case AVB_DESCRIPTOR_TAG_HASH: {
        AvbSlotVerifyResult sub_ret;
        sub_ret = load_and_verify_hash_partition(ops,
                                                 requested_partitions,
                                                 ab_suffix,
                                                 allow_verification_error,
                                                 descriptors[n],
                                                 slot_data);
        if (sub_ret != AVB_SLOT_VERIFY_RESULT_OK) {
          ret = sub_ret;
          if (!allow_verification_error || !result_should_continue(ret)) {
            goto out;
          }
        }
      } break;

      case AVB_DESCRIPTOR_TAG_CHAIN_PARTITION: {
        AvbSlotVerifyResult sub_ret;
        AvbChainPartitionDescriptor chain_desc;
        const uint8_t* chain_partition_name;
        const uint8_t* chain_public_key;

        /* Only allow CHAIN_PARTITION descriptors in the main vbmeta image. */
        if (!is_main_vbmeta) {
          avb_errorv(full_partition_name,
                     ": Encountered chain descriptor not in main image.\n",
                     NULL);
          ret = AVB_SLOT_VERIFY_RESULT_ERROR_INVALID_METADATA;
          goto out;
        }

        if (!avb_chain_partition_descriptor_validate_and_byteswap(
                (AvbChainPartitionDescriptor*)descriptors[n], &chain_desc)) {
          avb_errorv(full_partition_name,
                     ": Chain partition descriptor is invalid.\n",
                     NULL);
          ret = AVB_SLOT_VERIFY_RESULT_ERROR_INVALID_METADATA;
          goto out;
        }

        if (chain_desc.rollback_index_location == 0) {
          avb_errorv(full_partition_name,
                     ": Chain partition has invalid "
                     "rollback_index_location field.\n",
                     NULL);
          ret = AVB_SLOT_VERIFY_RESULT_ERROR_INVALID_METADATA;
          goto out;
        }

        chain_partition_name = ((const uint8_t*)descriptors[n]) +
                               sizeof(AvbChainPartitionDescriptor);
        chain_public_key = chain_partition_name + chain_desc.partition_name_len;

        sub_ret =
            load_and_verify_vbmeta(ops,
                                   requested_partitions,
                                   ab_suffix,
                                   flags,
                                   allow_verification_error,
                                   toplevel_vbmeta_flags,
                                   chain_desc.rollback_index_location,
                                   (const char*)chain_partition_name,
                                   chain_desc.partition_name_len,
                                   chain_public_key,
                                   chain_desc.public_key_len,
                                   slot_data,
                                   NULL, /* out_algorithm_type */
                                   NULL /* out_additional_cmdline_subst */);
        if (sub_ret != AVB_SLOT_VERIFY_RESULT_OK) {
          ret = sub_ret;
          if (!result_should_continue(ret)) {
            goto out;
          }
        }
      } break;

      case AVB_DESCRIPTOR_TAG_KERNEL_CMDLINE: {
        const uint8_t* kernel_cmdline;
        AvbKernelCmdlineDescriptor kernel_cmdline_desc;
        bool apply_cmdline;

        if (!avb_kernel_cmdline_descriptor_validate_and_byteswap(
                (AvbKernelCmdlineDescriptor*)descriptors[n],
                &kernel_cmdline_desc)) {
          avb_errorv(full_partition_name,
                     ": Kernel cmdline descriptor is invalid.\n",
                     NULL);
          ret = AVB_SLOT_VERIFY_RESULT_ERROR_INVALID_METADATA;
          goto out;
        }

        kernel_cmdline = ((const uint8_t*)descriptors[n]) +
                         sizeof(AvbKernelCmdlineDescriptor);

        if (!avb_validate_utf8(kernel_cmdline,
                               kernel_cmdline_desc.kernel_cmdline_length)) {
          avb_errorv(full_partition_name,
                     ": Kernel cmdline is not valid UTF-8.\n",
                     NULL);
          ret = AVB_SLOT_VERIFY_RESULT_ERROR_INVALID_METADATA;
          goto out;
        }

        /* Compare the flags for top-level VBMeta struct with flags in
         * the command-line descriptor so command-line snippets only
         * intended for a certain mode (dm-verity enabled/disabled)
         * are skipped if applicable.
         */
        apply_cmdline = true;
        if (toplevel_vbmeta_flags & AVB_VBMETA_IMAGE_FLAGS_HASHTREE_DISABLED) {
          if (kernel_cmdline_desc.flags &
              AVB_KERNEL_CMDLINE_FLAGS_USE_ONLY_IF_HASHTREE_NOT_DISABLED) {
            apply_cmdline = false;
          }
        } else {
          if (kernel_cmdline_desc.flags &
              AVB_KERNEL_CMDLINE_FLAGS_USE_ONLY_IF_HASHTREE_DISABLED) {
            apply_cmdline = false;
          }
        }

        if (apply_cmdline) {
          if (slot_data->cmdline == NULL) {
            slot_data->cmdline =
                avb_calloc(kernel_cmdline_desc.kernel_cmdline_length + 1);
            if (slot_data->cmdline == NULL) {
              ret = AVB_SLOT_VERIFY_RESULT_ERROR_OOM;
              goto out;
            }
            avb_memcpy(slot_data->cmdline,
                       kernel_cmdline,
                       kernel_cmdline_desc.kernel_cmdline_length);
          } else {
            /* new cmdline is: <existing_cmdline> + ' ' + <newcmdline> + '\0' */
            size_t orig_size = avb_strlen(slot_data->cmdline);
            size_t new_size =
                orig_size + 1 + kernel_cmdline_desc.kernel_cmdline_length + 1;
            char* new_cmdline = avb_calloc(new_size);
            if (new_cmdline == NULL) {
              ret = AVB_SLOT_VERIFY_RESULT_ERROR_OOM;
              goto out;
            }
            avb_memcpy(new_cmdline, slot_data->cmdline, orig_size);
            new_cmdline[orig_size] = ' ';
            avb_memcpy(new_cmdline + orig_size + 1,
                       kernel_cmdline,
                       kernel_cmdline_desc.kernel_cmdline_length);
            avb_free(slot_data->cmdline);
            slot_data->cmdline = new_cmdline;
          }
        }
      } break;

      case AVB_DESCRIPTOR_TAG_HASHTREE: {
        AvbHashtreeDescriptor hashtree_desc;

        if (!avb_hashtree_descriptor_validate_and_byteswap(
                (AvbHashtreeDescriptor*)descriptors[n], &hashtree_desc)) {
          avb_errorv(
              full_partition_name, ": Hashtree descriptor is invalid.\n", NULL);
          ret = AVB_SLOT_VERIFY_RESULT_ERROR_INVALID_METADATA;
          goto out;
        }

        /* We only need to continue when there is no digest in the descriptor.
         * This is because the only processing here is to find the digest and
         * make it available on the kernel command line.
         */
        if (hashtree_desc.root_digest_len == 0) {
          char part_name[AVB_PART_NAME_MAX_SIZE];
          size_t digest_len = 0;
          uint8_t digest_buf[AVB_SHA512_DIGEST_SIZE];
          const uint8_t* desc_partition_name =
              ((const uint8_t*)descriptors[n]) + sizeof(AvbHashtreeDescriptor);

          if (!avb_validate_utf8(desc_partition_name,
                                 hashtree_desc.partition_name_len)) {
            avb_error("Partition name is not valid UTF-8.\n");
            ret = AVB_SLOT_VERIFY_RESULT_ERROR_INVALID_METADATA;
            goto out;
          }

          /* No ab_suffix for partitions without a digest in the descriptor
           * because these partitions hold data unique to this device and are
           * not updated using an A/B scheme.
           */
          if ((hashtree_desc.flags &
               AVB_HASHTREE_DESCRIPTOR_FLAGS_DO_NOT_USE_AB) == 0 &&
              avb_strlen(ab_suffix) != 0) {
            avb_error("Cannot use A/B with a persistent root digest.\n");
            ret = AVB_SLOT_VERIFY_RESULT_ERROR_INVALID_METADATA;
            goto out;
          }
          if (hashtree_desc.partition_name_len >= AVB_PART_NAME_MAX_SIZE) {
            avb_error("Partition name does not fit.\n");
            ret = AVB_SLOT_VERIFY_RESULT_ERROR_INVALID_METADATA;
            goto out;
          }
          avb_memcpy(
              part_name, desc_partition_name, hashtree_desc.partition_name_len);
          part_name[hashtree_desc.partition_name_len] = '\0';

          /* Determine the expected digest size from the hash algorithm. */
          if (avb_strcmp((const char*)hashtree_desc.hash_algorithm, "sha1") ==
              0) {
            digest_len = AVB_SHA1_DIGEST_SIZE;
          } else if (avb_strcmp((const char*)hashtree_desc.hash_algorithm,
                                "sha256") == 0) {
            digest_len = AVB_SHA256_DIGEST_SIZE;
          } else if (avb_strcmp((const char*)hashtree_desc.hash_algorithm,
                                "sha512") == 0) {
            digest_len = AVB_SHA512_DIGEST_SIZE;
          } else {
            avb_errorv(part_name, ": Unsupported hash algorithm.\n", NULL);
            ret = AVB_SLOT_VERIFY_RESULT_ERROR_INVALID_METADATA;
            goto out;
          }

          ret = read_persistent_digest(ops,
                                       part_name,
                                       digest_len,
                                       NULL /* initial_digest */,
                                       digest_buf);
          if (ret != AVB_SLOT_VERIFY_RESULT_OK) {
            goto out;
          }

          if (out_additional_cmdline_subst) {
            ret =
                avb_add_root_digest_substitution(part_name,
                                                 digest_buf,
                                                 digest_len,
                                                 out_additional_cmdline_subst);
            if (ret != AVB_SLOT_VERIFY_RESULT_OK) {
              goto out;
            }
          }
        }
      } break;

      case AVB_DESCRIPTOR_TAG_PROPERTY:
        /* Do nothing. */
        break;
    }
  }

  if (rollback_index_location < 0 ||
      rollback_index_location >= AVB_MAX_NUMBER_OF_ROLLBACK_INDEX_LOCATIONS) {
    avb_errorv(
        full_partition_name, ": Invalid rollback_index_location.\n", NULL);
    ret = AVB_SLOT_VERIFY_RESULT_ERROR_INVALID_METADATA;
    goto out;
  }

  slot_data->rollback_indexes[rollback_index_location] =
      vbmeta_header.rollback_index;

  if (out_algorithm_type != NULL) {
    *out_algorithm_type = (AvbAlgorithmType)vbmeta_header.algorithm_type;
  }

out:
  /* If |vbmeta_image_data| isn't NULL it means that it adopted
   * |vbmeta_buf| so in that case don't free it here.
   */
  if (vbmeta_image_data == NULL) {
    if (vbmeta_buf != NULL) {
      avb_free(vbmeta_buf);
    }
  }
  if (descriptors != NULL) {
    avb_free(descriptors);
  }
  return ret;
}

static AvbIOResult avb_manage_hashtree_error_mode(
    AvbOps* ops,
    AvbSlotVerifyFlags flags,
    AvbSlotVerifyData* data,
    AvbHashtreeErrorMode* out_hashtree_error_mode) {
  AvbHashtreeErrorMode ret = AVB_HASHTREE_ERROR_MODE_RESTART;
  AvbIOResult io_ret = AVB_IO_RESULT_OK;
  uint8_t vbmeta_digest_sha256[AVB_SHA256_DIGEST_SIZE];
  uint8_t stored_vbmeta_digest_sha256[AVB_SHA256_DIGEST_SIZE];
  size_t num_bytes_read;

  avb_assert(out_hashtree_error_mode != NULL);
  avb_assert(ops->read_persistent_value != NULL);
  avb_assert(ops->write_persistent_value != NULL);

  // If we're rebooting because of dm-verity corruption, make a note of
  // the vbmeta hash so we can stay in 'eio' mode until things change.
  if (flags & AVB_SLOT_VERIFY_FLAGS_RESTART_CAUSED_BY_HASHTREE_CORRUPTION) {
    avb_debug(
        "Rebooting because of dm-verity corruption - "
        "recording OS instance and using 'eio' mode.\n");
    avb_slot_verify_data_calculate_vbmeta_digest(
        data, AVB_DIGEST_TYPE_SHA256, vbmeta_digest_sha256);
    io_ret = ops->write_persistent_value(ops,
                                         AVB_NPV_MANAGED_VERITY_MODE,
                                         AVB_SHA256_DIGEST_SIZE,
                                         vbmeta_digest_sha256);
    if (io_ret != AVB_IO_RESULT_OK) {
      avb_error("Error writing to " AVB_NPV_MANAGED_VERITY_MODE ".\n");
      goto out;
    }
    ret = AVB_HASHTREE_ERROR_MODE_EIO;
    io_ret = AVB_IO_RESULT_OK;
    goto out;
  }

  // See if we're in 'eio' mode.
  io_ret = ops->read_persistent_value(ops,
                                      AVB_NPV_MANAGED_VERITY_MODE,
                                      AVB_SHA256_DIGEST_SIZE,
                                      stored_vbmeta_digest_sha256,
                                      &num_bytes_read);
  if (io_ret == AVB_IO_RESULT_ERROR_NO_SUCH_VALUE ||
      (io_ret == AVB_IO_RESULT_OK && num_bytes_read == 0)) {
    // This is the usual case ('eio' mode not set).
    avb_debug("No dm-verity corruption - using in 'restart' mode.\n");
    ret = AVB_HASHTREE_ERROR_MODE_RESTART;
    io_ret = AVB_IO_RESULT_OK;
    goto out;
  } else if (io_ret != AVB_IO_RESULT_OK) {
    avb_error("Error reading from " AVB_NPV_MANAGED_VERITY_MODE ".\n");
    goto out;
  }
  if (num_bytes_read != AVB_SHA256_DIGEST_SIZE) {
    avb_error(
        "Unexpected number of bytes read from " AVB_NPV_MANAGED_VERITY_MODE
        ".\n");
    io_ret = AVB_IO_RESULT_ERROR_IO;
    goto out;
  }

  // OK, so we're currently in 'eio' mode and the vbmeta digest of the OS
  // that caused this is in |stored_vbmeta_digest_sha256| ... now see if
  // the OS we're dealing with now is the same.
  avb_slot_verify_data_calculate_vbmeta_digest(
      data, AVB_DIGEST_TYPE_SHA256, vbmeta_digest_sha256);
  if (avb_memcmp(vbmeta_digest_sha256,
                 stored_vbmeta_digest_sha256,
                 AVB_SHA256_DIGEST_SIZE) == 0) {
    // It's the same so we're still in 'eio' mode.
    avb_debug("Same OS instance detected - staying in 'eio' mode.\n");
    ret = AVB_HASHTREE_ERROR_MODE_EIO;
    io_ret = AVB_IO_RESULT_OK;
  } else {
    // It did change!
    avb_debug(
        "New OS instance detected - changing from 'eio' to 'restart' mode.\n");
    io_ret =
        ops->write_persistent_value(ops,
                                    AVB_NPV_MANAGED_VERITY_MODE,
                                    0,  // This clears the persistent property.
                                    vbmeta_digest_sha256);
    if (io_ret != AVB_IO_RESULT_OK) {
      avb_error("Error clearing " AVB_NPV_MANAGED_VERITY_MODE ".\n");
      goto out;
    }
    ret = AVB_HASHTREE_ERROR_MODE_RESTART;
    io_ret = AVB_IO_RESULT_OK;
  }

out:
  *out_hashtree_error_mode = ret;
  return io_ret;
}

static bool has_system_partition(AvbOps* ops, const char* ab_suffix) {
  char part_name[AVB_PART_NAME_MAX_SIZE];
  char* system_part_name = "system";
  char guid_buf[37];
  AvbIOResult io_ret;

  if (!avb_str_concat(part_name,
                      sizeof part_name,
                      system_part_name,
                      avb_strlen(system_part_name),
                      ab_suffix,
                      avb_strlen(ab_suffix))) {
    avb_error("System partition name and suffix does not fit.\n");
    return false;
  }

  io_ret = ops->get_unique_guid_for_partition(
      ops, part_name, guid_buf, sizeof guid_buf);
  if (io_ret == AVB_IO_RESULT_ERROR_NO_SUCH_PARTITION) {
    avb_debug("No system partition.\n");
    return false;
  } else if (io_ret != AVB_IO_RESULT_OK) {
    avb_error("Error getting unique GUID for system partition.\n");
    return false;
  }

  return true;
}

AvbSlotVerifyResult avb_slot_verify(AvbOps* ops,
                                    const char* const* requested_partitions,
                                    const char* ab_suffix,
                                    AvbSlotVerifyFlags flags,
                                    AvbHashtreeErrorMode hashtree_error_mode,
                                    AvbSlotVerifyData** out_data) {
  AvbSlotVerifyResult ret = 0;
  AvbSlotVerifyData* slot_data = NULL;
  AvbAlgorithmType algorithm_type = AVB_ALGORITHM_TYPE_NONE;
  bool using_boot_for_vbmeta = false;
  AvbVBMetaImageHeader toplevel_vbmeta;
  bool allow_verification_error =
      (flags & AVB_SLOT_VERIFY_FLAGS_ALLOW_VERIFICATION_ERROR);
  AvbCmdlineSubstList* additional_cmdline_subst = NULL;

  /* Fail early if we're missing the AvbOps needed for slot verification. */
  avb_assert(ops->read_is_device_unlocked != NULL);
  avb_assert(ops->read_from_partition != NULL);
  avb_assert(ops->get_size_of_partition != NULL);
  avb_assert(ops->read_rollback_index != NULL);
  avb_assert(ops->get_unique_guid_for_partition != NULL);

  if (out_data != NULL) {
    *out_data = NULL;
  }

  /* Allowing dm-verity errors defeats the purpose of verified boot so
   * only allow this if set up to allow verification errors
   * (e.g. typically only UNLOCKED mode).
   */
  if (hashtree_error_mode == AVB_HASHTREE_ERROR_MODE_LOGGING &&
      !allow_verification_error) {
    ret = AVB_SLOT_VERIFY_RESULT_ERROR_INVALID_ARGUMENT;
    goto fail;
  }

  /* Make sure passed-in AvbOps support persistent values if
   * asking for libavb to manage verity state.
   */
  if (hashtree_error_mode == AVB_HASHTREE_ERROR_MODE_MANAGED_RESTART_AND_EIO) {
    if (ops->read_persistent_value == NULL ||
        ops->write_persistent_value == NULL) {
      avb_error(
          "Persistent values required for "
          "AVB_HASHTREE_ERROR_MODE_MANAGED_RESTART_AND_EIO "
          "but are not implemented in given AvbOps.\n");
      ret = AVB_SLOT_VERIFY_RESULT_ERROR_INVALID_ARGUMENT;
      goto fail;
    }
  }

  /* Make sure passed-in AvbOps support verifying public keys and getting
   * rollback index location if not using a vbmeta partition.
   */
  if (flags & AVB_SLOT_VERIFY_FLAGS_NO_VBMETA_PARTITION) {
    if (ops->validate_public_key_for_partition == NULL) {
      avb_error(
          "AVB_SLOT_VERIFY_FLAGS_NO_VBMETA_PARTITION was passed but the "
          "validate_public_key_for_partition() operation isn't implemented.\n");
      ret = AVB_SLOT_VERIFY_RESULT_ERROR_INVALID_ARGUMENT;
      goto fail;
    }
  } else {
    avb_assert(ops->validate_vbmeta_public_key != NULL);
  }

  slot_data = avb_calloc(sizeof(AvbSlotVerifyData));
  if (slot_data == NULL) {
    ret = AVB_SLOT_VERIFY_RESULT_ERROR_OOM;
    goto fail;
  }
  slot_data->vbmeta_images =
      avb_calloc(sizeof(AvbVBMetaData) * MAX_NUMBER_OF_VBMETA_IMAGES);
  if (slot_data->vbmeta_images == NULL) {
    ret = AVB_SLOT_VERIFY_RESULT_ERROR_OOM;
    goto fail;
  }
  slot_data->loaded_partitions =
      avb_calloc(sizeof(AvbPartitionData) * MAX_NUMBER_OF_LOADED_PARTITIONS);
  if (slot_data->loaded_partitions == NULL) {
    ret = AVB_SLOT_VERIFY_RESULT_ERROR_OOM;
    goto fail;
  }

  additional_cmdline_subst = avb_new_cmdline_subst_list();
  if (additional_cmdline_subst == NULL) {
    ret = AVB_SLOT_VERIFY_RESULT_ERROR_OOM;
    goto fail;
  }

  if (flags & AVB_SLOT_VERIFY_FLAGS_NO_VBMETA_PARTITION) {
    if (requested_partitions == NULL || requested_partitions[0] == NULL) {
      avb_fatal(
          "Requested partitions cannot be empty when using "
          "AVB_SLOT_VERIFY_FLAGS_NO_VBMETA_PARTITION");
      ret = AVB_SLOT_VERIFY_RESULT_ERROR_INVALID_ARGUMENT;
      goto fail;
    }

    /* No vbmeta partition, go through each of the requested partitions... */
    for (size_t n = 0; requested_partitions[n] != NULL; n++) {
      ret = load_and_verify_vbmeta(ops,
                                   requested_partitions,
                                   ab_suffix,
                                   flags,
                                   allow_verification_error,
                                   0 /* toplevel_vbmeta_flags */,
                                   0 /* rollback_index_location */,
                                   requested_partitions[n],
                                   avb_strlen(requested_partitions[n]),
                                   NULL /* expected_public_key */,
                                   0 /* expected_public_key_length */,
                                   slot_data,
                                   &algorithm_type,
                                   additional_cmdline_subst);
      if (!allow_verification_error && ret != AVB_SLOT_VERIFY_RESULT_OK) {
        goto fail;
      }
    }

  } else {
    /* Usual path, load "vbmeta"... */
    ret = load_and_verify_vbmeta(ops,
                                 requested_partitions,
                                 ab_suffix,
                                 flags,
                                 allow_verification_error,
                                 0 /* toplevel_vbmeta_flags */,
                                 0 /* rollback_index_location */,
                                 "vbmeta",
                                 avb_strlen("vbmeta"),
                                 NULL /* expected_public_key */,
                                 0 /* expected_public_key_length */,
                                 slot_data,
                                 &algorithm_type,
                                 additional_cmdline_subst);
    if (!allow_verification_error && ret != AVB_SLOT_VERIFY_RESULT_OK) {
      goto fail;
    }
  }

  if (!result_should_continue(ret)) {
    goto fail;
  }

  /* If things check out, mangle the kernel command-line as needed. */
  if (!(flags & AVB_SLOT_VERIFY_FLAGS_NO_VBMETA_PARTITION)) {
    if (avb_strcmp(slot_data->vbmeta_images[0].partition_name, "vbmeta") != 0) {
      avb_assert(
          avb_strcmp(slot_data->vbmeta_images[0].partition_name, "boot") == 0);
      using_boot_for_vbmeta = true;
    }
  }

  /* Byteswap top-level vbmeta header since we'll need it below. */
  avb_vbmeta_image_header_to_host_byte_order(
      (const AvbVBMetaImageHeader*)slot_data->vbmeta_images[0].vbmeta_data,
      &toplevel_vbmeta);

  /* Fill in |ab_suffix| field. */
  slot_data->ab_suffix = avb_strdup(ab_suffix);
  if (slot_data->ab_suffix == NULL) {
    ret = AVB_SLOT_VERIFY_RESULT_ERROR_OOM;
    goto fail;
  }

  /* If verification is disabled, we are done ... we specifically
   * don't want to add any androidboot.* options since verification
   * is disabled.
   */
  if (toplevel_vbmeta.flags & AVB_VBMETA_IMAGE_FLAGS_VERIFICATION_DISABLED) {
    /* Since verification is disabled we didn't process any
     * descriptors and thus there's no cmdline... so set root= such
     * that the system partition is mounted.
     */
    avb_assert(slot_data->cmdline == NULL);
    // Devices with dynamic partitions won't have system partition.
    // Instead, it has a large super partition to accommodate *.img files.
    // See b/119551429 for details.
    if (has_system_partition(ops, ab_suffix)) {
      slot_data->cmdline =
          avb_strdup("root=PARTUUID=$(ANDROID_SYSTEM_PARTUUID)");
    } else {
      // The |cmdline| field should be a NUL-terminated string.
      slot_data->cmdline = avb_strdup("");
    }
    if (slot_data->cmdline == NULL) {
      ret = AVB_SLOT_VERIFY_RESULT_ERROR_OOM;
      goto fail;
    }
  } else {
    /* If requested, manage dm-verity mode... */
    AvbHashtreeErrorMode resolved_hashtree_error_mode = hashtree_error_mode;
    if (hashtree_error_mode ==
        AVB_HASHTREE_ERROR_MODE_MANAGED_RESTART_AND_EIO) {
      AvbIOResult io_ret;
      io_ret = avb_manage_hashtree_error_mode(
          ops, flags, slot_data, &resolved_hashtree_error_mode);
      if (io_ret != AVB_IO_RESULT_OK) {
        ret = AVB_SLOT_VERIFY_RESULT_ERROR_IO;
        if (io_ret == AVB_IO_RESULT_ERROR_OOM) {
          ret = AVB_SLOT_VERIFY_RESULT_ERROR_OOM;
        }
        goto fail;
      }
    }
    slot_data->resolved_hashtree_error_mode = resolved_hashtree_error_mode;

    /* Add options... */
    AvbSlotVerifyResult sub_ret;
    sub_ret = avb_append_options(ops,
                                 flags,
                                 slot_data,
                                 &toplevel_vbmeta,
                                 algorithm_type,
                                 hashtree_error_mode,
                                 resolved_hashtree_error_mode);
    if (sub_ret != AVB_SLOT_VERIFY_RESULT_OK) {
      ret = sub_ret;
      goto fail;
    }
  }

  /* Substitute $(ANDROID_SYSTEM_PARTUUID) and friends. */
  if (slot_data->cmdline != NULL && avb_strlen(slot_data->cmdline) != 0) {
    char* new_cmdline;
    new_cmdline = avb_sub_cmdline(ops,
                                  slot_data->cmdline,
                                  ab_suffix,
                                  using_boot_for_vbmeta,
                                  additional_cmdline_subst);
    if (new_cmdline != slot_data->cmdline) {
      if (new_cmdline == NULL) {
        ret = AVB_SLOT_VERIFY_RESULT_ERROR_OOM;
        goto fail;
      }
      avb_free(slot_data->cmdline);
      slot_data->cmdline = new_cmdline;
    }
  }

  if (out_data != NULL) {
    *out_data = slot_data;
  } else {
    avb_slot_verify_data_free(slot_data);
  }

  avb_free_cmdline_subst_list(additional_cmdline_subst);
  additional_cmdline_subst = NULL;

  if (!allow_verification_error) {
    avb_assert(ret == AVB_SLOT_VERIFY_RESULT_OK);
  }

  return ret;

fail:
  if (slot_data != NULL) {
    avb_slot_verify_data_free(slot_data);
  }
  if (additional_cmdline_subst != NULL) {
    avb_free_cmdline_subst_list(additional_cmdline_subst);
  }
  return ret;
}

void avb_slot_verify_data_free(AvbSlotVerifyData* data) {
  if (data->ab_suffix != NULL) {
    avb_free(data->ab_suffix);
  }
  if (data->cmdline != NULL) {
    avb_free(data->cmdline);
  }
  if (data->vbmeta_images != NULL) {
    size_t n;
    for (n = 0; n < data->num_vbmeta_images; n++) {
      AvbVBMetaData* vbmeta_image = &data->vbmeta_images[n];
      if (vbmeta_image->partition_name != NULL) {
        avb_free(vbmeta_image->partition_name);
      }
      if (vbmeta_image->vbmeta_data != NULL) {
        avb_free(vbmeta_image->vbmeta_data);
      }
    }
    avb_free(data->vbmeta_images);
  }
  if (data->loaded_partitions != NULL) {
    size_t n;
    for (n = 0; n < data->num_loaded_partitions; n++) {
      AvbPartitionData* loaded_partition = &data->loaded_partitions[n];
      if (loaded_partition->partition_name != NULL) {
        avb_free(loaded_partition->partition_name);
      }
      if (loaded_partition->data != NULL && !loaded_partition->preloaded) {
        sysmem_free((phys_addr_t)loaded_partition->data);
      }
    }
    avb_free(data->loaded_partitions);
  }
  avb_free(data);
}

const char* avb_slot_verify_result_to_string(AvbSlotVerifyResult result) {
  const char* ret = NULL;

  switch (result) {
    case AVB_SLOT_VERIFY_RESULT_OK:
      ret = "OK";
      break;
    case AVB_SLOT_VERIFY_RESULT_ERROR_OOM:
      ret = "ERROR_OOM";
      break;
    case AVB_SLOT_VERIFY_RESULT_ERROR_IO:
      ret = "ERROR_IO";
      break;
    case AVB_SLOT_VERIFY_RESULT_ERROR_VERIFICATION:
      ret = "ERROR_VERIFICATION";
      break;
    case AVB_SLOT_VERIFY_RESULT_ERROR_ROLLBACK_INDEX:
      ret = "ERROR_ROLLBACK_INDEX";
      break;
    case AVB_SLOT_VERIFY_RESULT_ERROR_PUBLIC_KEY_REJECTED:
      ret = "ERROR_PUBLIC_KEY_REJECTED";
      break;
    case AVB_SLOT_VERIFY_RESULT_ERROR_INVALID_METADATA:
      ret = "ERROR_INVALID_METADATA";
      break;
    case AVB_SLOT_VERIFY_RESULT_ERROR_UNSUPPORTED_VERSION:
      ret = "ERROR_UNSUPPORTED_VERSION";
      break;
    case AVB_SLOT_VERIFY_RESULT_ERROR_INVALID_ARGUMENT:
      ret = "ERROR_INVALID_ARGUMENT";
      break;
      /* Do not add a 'default:' case here because of -Wswitch. */
  }

  if (ret == NULL) {
    avb_error("Unknown AvbSlotVerifyResult value.\n");
    ret = "(unknown)";
  }

  return ret;
}

void avb_slot_verify_data_calculate_vbmeta_digest(AvbSlotVerifyData* data,
                                                  AvbDigestType digest_type,
                                                  uint8_t* out_digest) {
  bool ret = false;
  size_t n;

  switch (digest_type) {
    case AVB_DIGEST_TYPE_SHA256: {
      AvbSHA256Ctx ctx;

      ctx.tot_len = 0;
      for (n = 0; n < data->num_vbmeta_images; n++)
        ctx.tot_len += data->vbmeta_images[n].vbmeta_size;

      avb_sha256_init(&ctx);
      for (n = 0; n < data->num_vbmeta_images; n++) {
        avb_sha256_update(&ctx,
                          data->vbmeta_images[n].vbmeta_data,
                          data->vbmeta_images[n].vbmeta_size);
      }
      avb_memcpy(out_digest, avb_sha256_final(&ctx), AVB_SHA256_DIGEST_SIZE);
      ret = true;
    } break;

    case AVB_DIGEST_TYPE_SHA512: {
      AvbSHA512Ctx ctx;

      ctx.tot_len = 0;
      for (n = 0; n < data->num_vbmeta_images; n++)
        ctx.tot_len += data->vbmeta_images[n].vbmeta_size;

      avb_sha512_init(&ctx);
      for (n = 0; n < data->num_vbmeta_images; n++) {
        avb_sha512_update(&ctx,
                          data->vbmeta_images[n].vbmeta_data,
                          data->vbmeta_images[n].vbmeta_size);
      }
      avb_memcpy(out_digest, avb_sha512_final(&ctx), AVB_SHA512_DIGEST_SIZE);
      ret = true;
    } break;

      /* Do not add a 'default:' case here because of -Wswitch. */
  }

  if (!ret) {
    avb_fatal("Unknown digest type");
  }
}
