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
#if !defined(AVB_INSIDE_LIBAVB_AB_H) && !defined(AVB_COMPILATION)
#error \
    "Never include this file directly, include libavb_ab/libavb_ab.h instead."
#endif
*/

#ifndef AVB_AB_FLOW_H_
#define AVB_AB_FLOW_H_

#include <android_avb/avb_ab_ops.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Magic for the A/B struct when serialized. */
#define AVB_AB_MAGIC "\0AB0"
#define AVB_AB_MAGIC_LEN 4

/* Versioning for the on-disk A/B metadata - keep in sync with avbtool. */
#define AVB_AB_MAJOR_VERSION 1
#define AVB_AB_MINOR_VERSION 0

/* Size of AvbABData struct. */
#define AVB_AB_DATA_SIZE 32

/* Maximum values for slot data */
#define AVB_AB_MAX_PRIORITY 15
#define AVB_AB_MAX_TRIES_REMAINING 7

/* Struct used for recording per-slot metadata.
 *
 * When serialized, data is stored in network byte-order.
 */
typedef struct AvbABSlotData {
  /* Slot priority. Valid values range from 0 to AVB_AB_MAX_PRIORITY,
   * both inclusive with 1 being the lowest and AVB_AB_MAX_PRIORITY
   * being the highest. The special value 0 is used to indicate the
   * slot is unbootable.
   */
  uint8_t priority;

  /* Number of times left attempting to boot this slot ranging from 0
   * to AVB_AB_MAX_TRIES_REMAINING.
   */
  uint8_t tries_remaining;

  /* Non-zero if this slot has booted successfully, 0 otherwise. */
  uint8_t successful_boot;

  /* Reserved for future use. */
  uint8_t reserved[1];
} AVB_ATTR_PACKED AvbABSlotData;

/* Struct used for recording A/B metadata.
 *
 * When serialized, data is stored in network byte-order.
 */
typedef struct AvbABData {
  /* Magic number used for identification - see AVB_AB_MAGIC. */
  uint8_t magic[AVB_AB_MAGIC_LEN];

  /* Version of on-disk struct - see AVB_AB_{MAJOR,MINOR}_VERSION. */
  uint8_t version_major;
  uint8_t version_minor;

  /* Padding to ensure |slots| field start eight bytes in. */
  uint8_t reserved1[2];

  /* Per-slot metadata. */
  AvbABSlotData slots[2];

  /* Reserved for future use. */
  uint8_t last_boot;
  uint8_t reserved2[11];

  /* CRC32 of all 28 bytes preceding this field. */
  uint32_t crc32;
} AVB_ATTR_PACKED AvbABData;

/* Copies |src| to |dest|, byte-swapping fields in the
 * process. Returns false if the data is invalid (e.g. wrong magic,
 * wrong CRC32 etc.), true otherwise.
 */
bool avb_ab_data_verify_and_byteswap(const AvbABData* src, AvbABData* dest);

/* Copies |src| to |dest|, byte-swapping fields in the process. Also
 * updates the |crc32| field in |dest|.
 */
void avb_ab_data_update_crc_and_byteswap(const AvbABData* src, AvbABData* dest);

/* Initializes |data| such that it has two slots and both slots have
 * maximum tries remaining. The CRC is not set.
 */
void avb_ab_data_init(AvbABData* data);

/* Reads A/B metadata from the 'misc' partition using |ops|. Returned
 * data is properly byteswapped. Returns AVB_IO_RESULT_OK on
 * success, error code otherwise.
 *
 * If the data read from disk is invalid (e.g. wrong magic or CRC
 * checksum failure), the metadata will be reset using
 * avb_ab_data_init() and then written to disk.
 */
AvbIOResult avb_ab_data_read(AvbABOps* ab_ops, AvbABData* data);

/* Writes A/B metadata to the 'misc' partition using |ops|. This will
 * byteswap and update the CRC as needed. Returns AVB_IO_RESULT_OK on
 * success, error code otherwise.
 */
AvbIOResult avb_ab_data_write(AvbABOps* ab_ops, const AvbABData* data);

/* Return codes used in avb_ab_flow(), see that function for
 * documentation of each value.
 */
typedef enum {
  AVB_AB_FLOW_RESULT_OK,
  AVB_AB_FLOW_RESULT_OK_WITH_VERIFICATION_ERROR,
  AVB_AB_FLOW_RESULT_ERROR_OOM,
  AVB_AB_FLOW_RESULT_ERROR_IO,
  AVB_AB_FLOW_RESULT_ERROR_NO_BOOTABLE_SLOTS,
  AVB_AB_FLOW_RESULT_ERROR_INVALID_ARGUMENT
} AvbABFlowResult;

/* Get a textual representation of |result|. */
const char* avb_ab_flow_result_to_string(AvbABFlowResult result);

/* High-level function to select a slot to boot. The following
 * algorithm is used:
 *
 * 1. A/B metadata is loaded and validated using the
 * read_ab_metadata() operation. Typically this means it's read from
 * the 'misc' partition and if it's invalid then it's reset using
 * avb_ab_data_init() and this reset metadata is returned.
 *
 * 2. All bootable slots listed in the A/B metadata are verified using
 * avb_slot_verify(). If a slot is invalid or if it fails verification
 * (and AVB_SLOT_VERIFY_FLAGS_ALLOW_VERIFICATION_ERROR is not set, see
 * below), it will be marked as unbootable in the A/B metadata and the
 * metadata will be saved to disk before returning.
 *
 * 3. If there are no bootable slots, the value
 * AVB_AB_FLOW_RESULT_ERROR_NO_BOOTABLE_SLOTS is returned.
 *
 * 4. For each bootable slot, the Stored Rollback Indexes are updated
 * such that for each rollback index location, the Stored Rollback
 * Index is the largest number smaller than or equal to the Rollback
 * Index of each slot.
 *
 * 5. The bootable slot with the highest priority is selected and
 * returned in |out_data|. If this slot is already marked as
 * successful, the A/B metadata is not modified. However, if the slot
 * is not marked as bootable its |tries_remaining| count is
 * decremented and the A/B metadata is saved to disk before returning.
 * In either case the value AVB_AB_FLOW_RESULT_OK is returning.
 *
 * The partitions to load is given in |requested_partitions| as a
 * NULL-terminated array of NUL-terminated strings. Typically the
 * |requested_partitions| array only contains a single item for the
 * boot partition, 'boot'.
 *
 * If the device is unlocked (and _only_ if it's unlocked), the
 * AVB_SLOT_VERIFY_FLAGS_ALLOW_VERIFICATION_ERROR flag should be set
 * in the |flags| parameter. This will allow considering slots as
 * verified even when avb_slot_verify() returns
 * AVB_SLOT_VERIFY_RESULT_ERROR_PUBLIC_KEY_REJECTED,
 * AVB_SLOT_VERIFY_RESULT_ERROR_VERIFICATION, or
 * AVB_SLOT_VERIFY_RESULT_ERROR_ROLLBACK_INDEX for the slot in
 * question.
 *
 * Note that neither androidboot.slot_suffix nor androidboot.slot are
 * set in the |cmdline| field in |AvbSlotVerifyData| - you will have
 * to pass these yourself.
 *
 * If a slot was selected and it verified then AVB_AB_FLOW_RESULT_OK
 * is returned.
 *
 * If a slot was selected but it didn't verify then
 * AVB_AB_FLOW_RESULT_OK_WITH_VERIFICATION_ERROR is returned. This can
 * only happen when the AVB_SLOT_VERIFY_FLAGS_ALLOW_VERIFICATION_ERROR
 * flag is set.
 *
 * If an I/O operation - such as loading/saving metadata or checking
 * rollback indexes - fail, the value AVB_AB_FLOW_RESULT_ERROR_IO is
 * returned.
 *
 * If memory allocation fails, AVB_AB_FLOW_RESULT_ERROR_OOM is
 * returned.
 *
 * If invalid arguments are passed,
 * AVB_AB_FLOW_RESULT_ERROR_INVALID_ARGUMENT is returned. For example
 * this can happen if using AVB_HASHTREE_ERROR_MODE_LOGGING without
 * AVB_SLOT_VERIFY_FLAGS_ALLOW_VERIFICATION_ERROR.
 *
 * Reasonable behavior for handling AVB_AB_FLOW_RESULT_ERROR_NO_BOOTABLE_SLOTS
 * is to initiate device repair (which is device-dependent).
 */
AvbABFlowResult avb_ab_flow(AvbABOps* ab_ops,
                            const char* const* requested_partitions,
                            AvbSlotVerifyFlags flags,
                            AvbHashtreeErrorMode hashtree_error_mode,
                            AvbSlotVerifyData** out_data);

/* Marks the slot with the given slot number as active. Returns
 * AVB_IO_RESULT_OK on success, error code otherwise.
 *
 * This function is typically used by the OS updater when completing
 * an update. It can also used by the firmware for implementing the
 * "set_active" command.
 */
AvbIOResult avb_ab_mark_slot_active(AvbABOps* ab_ops, unsigned int slot_number);

/* Marks the slot with the given slot number as unbootable. Returns
 * AVB_IO_RESULT_OK on success, error code otherwise.
 *
 * This function is typically used by the OS updater before writing to
 * a slot.
 */
AvbIOResult avb_ab_mark_slot_unbootable(AvbABOps* ab_ops,
                                        unsigned int slot_number);

/* Marks the slot with the given slot number as having booted
 * successfully. Returns AVB_IO_RESULT_OK on success, error code
 * otherwise.
 *
 * Calling this on an unbootable slot is an error - AVB_IO_RESULT_OK
 * will be returned yet the function will have no side-effects.
 *
 * This function is typically used by the OS updater after having
 * confirmed that the slot works as intended.
 */
AvbIOResult avb_ab_mark_slot_successful(AvbABOps* ab_ops,
                                        unsigned int slot_number);

/*
 * Load metadata.
 */
AvbIOResult load_metadata(AvbABOps* ab_ops,
			  AvbABData* ab_data,
			  AvbABData* ab_data_orig);

/* Writes A/B metadata to disk only if it has changed - returns
 * AVB_IO_RESULT_OK on success, error code otherwise.
 */
AvbIOResult save_metadata_if_changed(AvbABOps* ab_ops,
				     AvbABData* ab_data,
				     AvbABData* ab_data_orig);

#ifdef __cplusplus
}
#endif

#endif /* AVB_AB_FLOW_H_ */
