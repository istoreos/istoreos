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

#ifndef AVB_OPS_H_
#define AVB_OPS_H_

#include <android_avb/avb_sysdeps.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Well-known names of named persistent values. */
#define AVB_NPV_PERSISTENT_DIGEST_PREFIX "avb.persistent_digest."
#define AVB_NPV_MANAGED_VERITY_MODE "avb.managed_verity_mode"

/* Return codes used for I/O operations.
 *
 * AVB_IO_RESULT_OK is returned if the requested operation was
 * successful.
 *
 * AVB_IO_RESULT_ERROR_IO is returned if the underlying hardware (disk
 * or other subsystem) encountered an I/O error.
 *
 * AVB_IO_RESULT_ERROR_OOM is returned if unable to allocate memory.
 *
 * AVB_IO_RESULT_ERROR_NO_SUCH_PARTITION is returned if the requested
 * partition does not exist.
 *
 * AVB_IO_RESULT_ERROR_RANGE_OUTSIDE_PARTITION is returned if the
 * range of bytes requested to be read or written is outside the range
 * of the partition.
 *
 * AVB_IO_RESULT_ERROR_NO_SUCH_VALUE is returned if a named persistent value
 * does not exist.
 *
 * AVB_IO_RESULT_ERROR_INVALID_VALUE_SIZE is returned if a named persistent
 * value size is not supported or does not match the expected size.
 *
 * AVB_IO_RESULT_ERROR_INSUFFICIENT_SPACE is returned if a buffer is too small
 * for the requested operation.
 */
typedef enum {
  AVB_IO_RESULT_OK,
  AVB_IO_RESULT_ERROR_OOM,
  AVB_IO_RESULT_ERROR_IO,
  AVB_IO_RESULT_ERROR_NO_SUCH_PARTITION,
  AVB_IO_RESULT_ERROR_RANGE_OUTSIDE_PARTITION,
  AVB_IO_RESULT_ERROR_NO_SUCH_VALUE,
  AVB_IO_RESULT_ERROR_INVALID_VALUE_SIZE,
  AVB_IO_RESULT_ERROR_INSUFFICIENT_SPACE,
} AvbIOResult;

struct AvbOps;
typedef struct AvbOps AvbOps;

/* Forward-declaration of operations in libavb_ab. */
struct AvbABOps;

/* Forward-declaration of operations in libavb_atx. */
struct AvbAtxOps;

/* High-level operations/functions/methods that are platform
 * dependent.
 *
 * Operations may be added in the future so when implementing it
 * always make sure to zero out sizeof(AvbOps) bytes of the struct to
 * ensure that unimplemented operations are set to NULL.
 */
struct AvbOps {
  /* This pointer can be used by the application/bootloader using
   * libavb and is typically used in each operation to get a pointer
   * to platform-specific resources. It cannot be used by libraries.
   */
  void* user_data;

  /* If libavb_ab is used, this should point to the
   * AvbABOps. Otherwise it must be set to NULL.
   */
  struct AvbABOps* ab_ops;

  /* If libavb_atx is used, this should point to the
   * AvbAtxOps. Otherwise it must be set to NULL.
   */
  struct AvbAtxOps* atx_ops;

  /* Reads |num_bytes| from offset |offset| from partition with name
   * |partition| (NUL-terminated UTF-8 string). If |offset| is
   * negative, its absolute value should be interpreted as the number
   * of bytes from the end of the partition.
   *
   * This function returns AVB_IO_RESULT_ERROR_NO_SUCH_PARTITION if
   * there is no partition with the given name,
   * AVB_IO_RESULT_ERROR_RANGE_OUTSIDE_PARTITION if the requested
   * |offset| is outside the partition, and AVB_IO_RESULT_ERROR_IO if
   * there was an I/O error from the underlying I/O subsystem.  If the
   * operation succeeds as requested AVB_IO_RESULT_OK is returned and
   * the data is available in |buffer|.
   *
   * The only time partial I/O may occur is if reading beyond the end
   * of the partition. In this case the value returned in
   * |out_num_read| may be smaller than |num_bytes|.
   */
  AvbIOResult (*read_from_partition)(AvbOps* ops,
                                     const char* partition,
                                     int64_t offset,
                                     size_t num_bytes,
                                     void* buffer,
                                     size_t* out_num_read);

  /* Gets the starting pointer of a partition that is pre-loaded in memory, and
   * save it to |out_pointer|. The preloaded partition is expected to be
   * |num_bytes|, where the actual preloaded byte count is returned in
   * |out_num_bytes_preloaded|. |out_num_bytes_preloaded| must be no larger than
   * |num_bytes|.
   *
   * This provides an alternative way to access a partition that is preloaded
   * into memory without a full memory copy. When this function pointer is not
   * set (has value NULL), or when the |out_pointer| is set to NULL as a result,
   * |read_from_partition| will be used as the fallback. This function is mainly
   * used for accessing the entire partition content to calculate its hash.
   *
   * Preloaded partition data must outlive the lifespan of the
   * |AvbSlotVerifyData| structure that |avb_slot_verify| outputs.
   */
  AvbIOResult (*get_preloaded_partition)(AvbOps* ops,
                                         const char* partition,
                                         size_t num_bytes,
                                         uint8_t** out_pointer,
                                         size_t* out_num_bytes_preloaded,
                                         int allow_verification_error);

  /* Writes |num_bytes| from |bffer| at offset |offset| to partition
   * with name |partition| (NUL-terminated UTF-8 string). If |offset|
   * is negative, its absolute value should be interpreted as the
   * number of bytes from the end of the partition.
   *
   * This function returns AVB_IO_RESULT_ERROR_NO_SUCH_PARTITION if
   * there is no partition with the given name,
   * AVB_IO_RESULT_ERROR_RANGE_OUTSIDE_PARTITION if the requested
   * byterange goes outside the partition, and AVB_IO_RESULT_ERROR_IO
   * if there was an I/O error from the underlying I/O subsystem.  If
   * the operation succeeds as requested AVB_IO_RESULT_OK is
   * returned.
   *
   * This function never does any partial I/O, it either transfers all
   * of the requested bytes or returns an error.
   */
  AvbIOResult (*write_to_partition)(AvbOps* ops,
                                    const char* partition,
                                    int64_t offset,
                                    size_t num_bytes,
                                    const void* buffer);

  /* Checks if the given public key used to sign the 'vbmeta'
   * partition is trusted. Boot loaders typically compare this with
   * embedded key material generated with 'avbtool
   * extract_public_key'.
   *
   * The public key is in the array pointed to by |public_key_data|
   * and is of |public_key_length| bytes.
   *
   * If there is no public key metadata (set with the avbtool option
   * --public_key_metadata) then |public_key_metadata| will be set to
   * NULL. Otherwise this field points to the data which is
   * |public_key_metadata_length| bytes long.
   *
   * If AVB_IO_RESULT_OK is returned then |out_is_trusted| is set -
   * true if trusted or false if untrusted.
   *
   * NOTE: If AVB_SLOT_VERIFY_FLAGS_NO_VBMETA_PARTITION is passed to
   * avb_slot_verify() then this operation is never used. Instead, the
   * validate_public_key_for_partition() operation is used
   */
  AvbIOResult (*validate_vbmeta_public_key)(AvbOps* ops,
                                            const uint8_t* public_key_data,
                                            size_t public_key_length,
                                            const uint8_t* public_key_metadata,
                                            size_t public_key_metadata_length,
                                            bool* out_is_trusted);

  /* Gets the rollback index corresponding to the location given by
   * |rollback_index_location|. The value is returned in
   * |out_rollback_index|. Returns AVB_IO_RESULT_OK if the rollback
   * index was retrieved, otherwise an error code.
   *
   * A device may have a limited amount of rollback index locations (say,
   * one or four) so may error out if |rollback_index_location| exceeds
   * this number.
   */
  AvbIOResult (*read_rollback_index)(AvbOps* ops,
                                     size_t rollback_index_location,
                                     uint64_t* out_rollback_index);

  /* Sets the rollback index corresponding to the location given by
   * |rollback_index_location| to |rollback_index|. Returns
   * AVB_IO_RESULT_OK if the rollback index was set, otherwise an
   * error code.
   *
   * A device may have a limited amount of rollback index locations (say,
   * one or four) so may error out if |rollback_index_location| exceeds
   * this number.
   */
  AvbIOResult (*write_rollback_index)(AvbOps* ops,
                                      size_t rollback_index_location,
                                      uint64_t rollback_index);

  /* Gets whether the device is unlocked. The value is returned in
   * |out_is_unlocked| (true if unlocked, false otherwise). Returns
   * AVB_IO_RESULT_OK if the state was retrieved, otherwise an error
   * code.
   */
  AvbIOResult (*read_is_device_unlocked)(AvbOps* ops, bool* out_is_unlocked);

  /* write the device lock flag. Returns
   * AVB_IO_RESULT_OK if the state was retrieved, otherwise an error
   * code.
   */
  AvbIOResult (*write_is_device_unlocked)(AvbOps* ops, bool* out_is_unlocked);
  
  /* Gets the unique partition GUID for a partition with name in
   * |partition| (NUL-terminated UTF-8 string). The GUID is copied as
   * a string into |guid_buf| of size |guid_buf_size| and will be NUL
   * terminated. The string must be lower-case and properly
   * hyphenated. For example:
   *
   *  527c1c6d-6361-4593-8842-3c78fcd39219
   *
   * Returns AVB_IO_RESULT_OK on success, otherwise an error code.
   */
  AvbIOResult (*get_unique_guid_for_partition)(AvbOps* ops,
                                               const char* partition,
                                               char* guid_buf,
                                               size_t guid_buf_size);

  /* Gets the size of a partition with the name in |partition|
   * (NUL-terminated UTF-8 string). Returns the value in
   * |out_size_num_bytes|.
   *
   * If the partition doesn't exist the AVB_IO_RESULT_ERROR_NO_SUCH_PARTITION
   * error code should be returned.
   *
   * Returns AVB_IO_RESULT_OK on success, otherwise an error code.
   */
  AvbIOResult (*get_size_of_partition)(AvbOps* ops,
                                       const char* partition,
                                       uint64_t* out_size_num_bytes);

  /* Reads a persistent value corresponding to the given |name|. The value is
   * returned in |out_buffer| which must point to |buffer_size| bytes. On
   * success |out_num_bytes_read| contains the number of bytes read into
   * |out_buffer|. If AVB_IO_RESULT_ERROR_INSUFFICIENT_SPACE is returned,
   * |out_num_bytes_read| contains the number of bytes that would have been read
   * which can be used to allocate a buffer.
   *
   * The |buffer_size| may be zero and the |out_buffer| may be NULL, but if
   * |out_buffer| is NULL then |buffer_size| *must* be zero.
   *
   * Returns AVB_IO_RESULT_OK on success, otherwise an error code.
   *
   * If the value does not exist, is not supported, or is not populated, returns
   * AVB_IO_RESULT_ERROR_NO_SUCH_VALUE. If |buffer_size| is smaller than the
   * size of the stored value, returns AVB_IO_RESULT_ERROR_INSUFFICIENT_SPACE.
   *
   * This operation is currently only used to support persistent digests or the
   * AVB_HASHTREE_ERROR_MODE_MANAGED_RESTART_AND_EIO hashtree error mode. If a
   * device does not use one of these features this function pointer can be set
   * to NULL.
   */
  AvbIOResult (*read_persistent_value)(AvbOps* ops,
                                       const char* name,
                                       size_t buffer_size,
                                       uint8_t* out_buffer,
                                       size_t* out_num_bytes_read);

  /* Writes a persistent value corresponding to the given |name|. The value is
   * supplied in |value| which must point to |value_size| bytes. Any existing
   * value with the same name is overwritten. If |value_size| is zero, future
   * calls to |read_persistent_value| will return
   * AVB_IO_RESULT_ERROR_NO_SUCH_VALUE.
   *
   * Returns AVB_IO_RESULT_OK on success, otherwise an error code.
   *
   * If the value |name| is not supported, returns
   * AVB_IO_RESULT_ERROR_NO_SUCH_VALUE. If the |value_size| is not supported,
   * returns AVB_IO_RESULT_ERROR_INVALID_VALUE_SIZE.
   *
   * This operation is currently only used to support persistent digests or the
   * AVB_HASHTREE_ERROR_MODE_MANAGED_RESTART_AND_EIO hashtree error mode. If a
   * device does not use one of these features this function pointer can be set
   * to NULL.
   */
  AvbIOResult (*write_persistent_value)(AvbOps* ops,
                                        const char* name,
                                        size_t value_size,
                                        const uint8_t* value);

  /* Like validate_vbmeta_public_key() but for when the flag
   * AVB_SLOT_VERIFY_FLAGS_NO_VBMETA_PARTITION is being used. The name of the
   * partition to get the public key for is passed in |partition_name|.
   *
   * Also returns the rollback index location to use for the partition, in
   * |out_rollback_index_location|.
   *
   * Returns AVB_IO_RESULT_OK on success, otherwise an error code.
   */
  AvbIOResult (*validate_public_key_for_partition)(
      AvbOps* ops,
      const char* partition,
      const uint8_t* public_key_data,
      size_t public_key_length,
      const uint8_t* public_key_metadata,
      size_t public_key_metadata_length,
      bool* out_is_trusted,
      uint32_t* out_rollback_index_location);
};

#ifdef __cplusplus
}
#endif

#endif /* AVB_OPS_H_ */
