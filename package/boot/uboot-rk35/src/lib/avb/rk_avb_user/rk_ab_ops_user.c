/*
 * (C) Copyright 2020 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */
#include <common.h>
#include <malloc.h>
#include <mapmem.h>
#include <errno.h>
#include <command.h>
#include <blk.h>
#include <part.h>
#include <boot_rkimg.h>
#include <android_avb/rk_avb_ops_user.h>

static int safe_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char *us1 = s1;
	const unsigned char *us2 = s2;
	int result = 0;

	if (0 == n)
		return 0;

	/*
	 * Code snippet without data-dependent branch due to Nate Lawson
	 * (nate@root.org) of Root Labs.
	 */
	while (n--)
		result |= *us1++ ^ *us2++;

	return result != 0;
}

static uint32_t htobe32(uint32_t in)
{
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

static uint32_t be32toh(uint32_t in)
{
	uint8_t *d = (uint8_t *)&in;
	uint32_t ret;

	ret = ((uint32_t)d[0]) << 24;
	ret |= ((uint32_t)d[1]) << 16;
	ret |= ((uint32_t)d[2]) << 8;
	ret |= ((uint32_t)d[3]);

	return ret;
}

static void slot_set_unbootable(AvbABSlotData* slot)
{
        slot->priority = 0;
        slot->tries_remaining = 0;
        slot->successful_boot = 0;
}

/* Ensure all unbootable and/or illegal states are marked as the
 * canonical 'unbootable' state, e.g. priority=0, tries_remaining=0,
 * and successful_boot=0.
 */
static void slot_normalize(AvbABSlotData* slot)
{
        if (slot->priority > 0) {
                if (slot->tries_remaining == 0 && !slot->successful_boot) {
                /* We've exhausted all tries -> unbootable. */
                slot_set_unbootable(slot);
        }
        if (slot->tries_remaining > 0 && slot->successful_boot) {
                /* Illegal state - avb_ab_mark_slot_successful() will clear
                 * tries_remaining when setting successful_boot.
                 */
                slot_set_unbootable(slot);
        }
        } else {
                slot_set_unbootable(slot);
        }
}

/* Writes A/B metadata to disk only if it has changed - returns
 * AVB_IO_RESULT_OK on success, error code otherwise.
 */
AvbIOResult save_metadata_if_changed(AvbABOps* ab_ops,
                                     AvbABData* ab_data,
                                     AvbABData* ab_data_orig)
{
        if (safe_memcmp(ab_data, ab_data_orig, sizeof(AvbABData)) != 0) {
                debug("Writing A/B metadata to disk.\n");
                return ab_ops->write_ab_metadata(ab_ops, ab_data);
        }
        return AVB_IO_RESULT_OK;
}

bool avb_ab_data_verify_and_byteswap(const AvbABData* src, AvbABData* dest) {
        /* Ensure magic is correct. */
        if (safe_memcmp(src->magic, AVB_AB_MAGIC, AVB_AB_MAGIC_LEN) != 0) {
                printf("Magic is incorrect.\n");
                return false;
        }

        memcpy(dest, src, sizeof(AvbABData));
        dest->crc32 = be32toh(dest->crc32);

        /* Ensure we don't attempt to access any fields if the major version
         * is not supported.
         */
        if (dest->version_major > AVB_AB_MAJOR_VERSION) {
                printf("No support for given major version.\n");
                return false;
        }

        /* Bail if CRC32 doesn't match. */
        if (dest->crc32 !=
                crc32(0, (const uint8_t*)dest, sizeof(AvbABData) - sizeof(uint32_t))) {
                printf("CRC32 does not match.\n");
                return false;
        }

        return true;
}

void avb_ab_data_update_crc_and_byteswap(const AvbABData* src,
                                         AvbABData* dest)
{
        memcpy(dest, src, sizeof(AvbABData));
        dest->crc32 = htobe32(crc32(0, (const uint8_t*)dest, sizeof(AvbABData) - sizeof(uint32_t)));
}

void avb_ab_data_init(AvbABData* data)
{
        memset(data, '\0', sizeof(AvbABData));
        memcpy(data->magic, AVB_AB_MAGIC, AVB_AB_MAGIC_LEN);
        data->version_major = AVB_AB_MAJOR_VERSION;
        data->version_minor = AVB_AB_MINOR_VERSION;
        data->last_boot = 0;
        data->slots[0].priority = AVB_AB_MAX_PRIORITY;
        data->slots[0].tries_remaining = AVB_AB_MAX_TRIES_REMAINING;
        data->slots[0].successful_boot = 0;
        data->slots[1].priority = AVB_AB_MAX_PRIORITY - 1;
        data->slots[1].tries_remaining = AVB_AB_MAX_TRIES_REMAINING;
        data->slots[1].successful_boot = 0;
}

/* The AvbABData struct is stored 2048 bytes into the 'misc' partition
 * following the 'struct bootloader_message' field. The struct is
 * compatible with the guidelines in bootable/recovery/bootloader.h -
 * e.g. it is stored in the |slot_suffix| field, starts with a
 * NUL-byte, and is 32 bytes long.
 */
#define AB_METADATA_MISC_PARTITION_OFFSET 2048

AvbIOResult avb_ab_data_read(AvbABOps* ab_ops, AvbABData* data)
{
        AvbOps* ops = ab_ops->ops;
        AvbABData serialized;
        AvbIOResult io_ret;
        size_t num_bytes_read;

        io_ret = ops->read_from_partition(ops,
                                          "misc",
                                          AB_METADATA_MISC_PARTITION_OFFSET,
                                          sizeof(AvbABData),
                                          &serialized,
                                          &num_bytes_read);
        if (io_ret == AVB_IO_RESULT_ERROR_OOM) {
                return AVB_IO_RESULT_ERROR_OOM;
        } else if (io_ret != AVB_IO_RESULT_OK ||
                  num_bytes_read != sizeof(AvbABData)) {
                printf("Error reading A/B metadata.\n");
                return AVB_IO_RESULT_ERROR_IO;
        }

        if (!avb_ab_data_verify_and_byteswap(&serialized, data)) {
                printf("Error validating A/B metadata from disk. "
                          "Resetting and writing new A/B metadata to disk.\n");
                avb_ab_data_init(data);
                return avb_ab_data_write(ab_ops, data);
        }

        return AVB_IO_RESULT_OK;
}

AvbIOResult avb_ab_data_write(AvbABOps* ab_ops, const AvbABData* data)
{
        AvbOps* ops = ab_ops->ops;
        AvbABData serialized;
        AvbIOResult io_ret;

        avb_ab_data_update_crc_and_byteswap(data, &serialized);
        io_ret = ops->write_to_partition(ops,
                                         "misc",
                                         AB_METADATA_MISC_PARTITION_OFFSET,
                                         sizeof(AvbABData),
                                         &serialized);
        if (io_ret == AVB_IO_RESULT_ERROR_OOM) {
                return AVB_IO_RESULT_ERROR_OOM;
        } else if (io_ret != AVB_IO_RESULT_OK) {
                printf("Error writing A/B metadata.\n");
                return AVB_IO_RESULT_ERROR_IO;
        }
        return AVB_IO_RESULT_OK;
}

/* Helper function to load metadata - returns AVB_IO_RESULT_OK on
 * success, error code otherwise.
 */
AvbIOResult load_metadata(AvbABOps* ab_ops,
                          AvbABData* ab_data,
                          AvbABData* ab_data_orig) {
        AvbIOResult io_ret;

        io_ret = ab_ops->read_ab_metadata(ab_ops, ab_data);
        if (io_ret != AVB_IO_RESULT_OK) {
                printf("I/O error while loading A/B metadata.\n");
                return io_ret;
        }
        *ab_data_orig = *ab_data;

        /* Ensure data is normalized, e.g. illegal states will be marked as
         * unbootable and all unbootable states are represented with
         * (priority=0, tries_remaining=0, successful_boot=0).
         */
        slot_normalize(&ab_data->slots[0]);
        slot_normalize(&ab_data->slots[1]);
        return AVB_IO_RESULT_OK;
}

int rk_avb_read_slot_count(char *slot_count)
{
	*slot_count = SLOT_NUM;

	return 0;
}

int rk_avb_read_slot_suffixes(char *slot_suffixes)
{
	memcpy(slot_suffixes, CURR_SYSTEM_SLOT_SUFFIX,
	       strlen(CURR_SYSTEM_SLOT_SUFFIX));

	return 0;
}

AvbIOResult avb_ab_mark_slot_active(AvbABOps* ab_ops,
                                    unsigned int slot_number)
{
        AvbABData ab_data, ab_data_orig;
        unsigned int other_slot_number;
        AvbIOResult ret;

        avb_assert(slot_number < 2);

        ret = load_metadata(ab_ops, &ab_data, &ab_data_orig);
        if (ret != AVB_IO_RESULT_OK) {
                goto out;
        }

        /* Make requested slot top priority, unsuccessful, and with max tries. */
        ab_data.slots[slot_number].priority = AVB_AB_MAX_PRIORITY;
        ab_data.slots[slot_number].tries_remaining = AVB_AB_MAX_TRIES_REMAINING;
        ab_data.slots[slot_number].successful_boot = 0;

        /* Ensure other slot doesn't have as high a priority. */
        other_slot_number = 1 - slot_number;
        if (ab_data.slots[other_slot_number].priority == AVB_AB_MAX_PRIORITY) {
                ab_data.slots[other_slot_number].priority = AVB_AB_MAX_PRIORITY - 1;
        }

        ret = AVB_IO_RESULT_OK;

out:
        if (ret == AVB_IO_RESULT_OK) {
                ret = save_metadata_if_changed(ab_ops, &ab_data, &ab_data_orig);
        }
        return ret;
}

int rk_avb_set_slot_active(unsigned int *slot_number)
{
	AvbOps* ops;
	ops = avb_ops_user_new();
	int ret = 0;

	if (ops == NULL) {
		printf("avb_ops_user_new() failed!\n");
		return -1;
	}

	debug("set_slot_active\n");
	if (avb_ab_mark_slot_active(ops->ab_ops, *slot_number) != 0) {
		printf("set_slot_active error!\n");
		ret = -1;
	}

	avb_ops_user_free(ops);
	return ret;
}

static bool slot_is_bootable(AvbABSlotData* slot) {
	return (slot->priority > 0) && 
	       (slot->successful_boot || (slot->tries_remaining > 0));
}

AvbABFlowResult rk_avb_ab_slot_select(AvbABOps* ab_ops,char* select_slot)
{
	AvbABFlowResult ret = AVB_AB_FLOW_RESULT_OK;
	AvbIOResult io_ret = AVB_IO_RESULT_OK;
	AvbABData ab_data;
	size_t slot_index_to_boot;
	static int last_slot_index = -1;

	io_ret = ab_ops->read_ab_metadata(ab_ops, &ab_data);
	if (io_ret != AVB_IO_RESULT_OK) {
		printf("I/O error while loading A/B metadata.\n");
		ret = AVB_AB_FLOW_RESULT_ERROR_IO;
		goto out;
	}
	if (slot_is_bootable(&ab_data.slots[0]) && slot_is_bootable(&ab_data.slots[1])) {
		if (ab_data.slots[1].priority > ab_data.slots[0].priority) {
			slot_index_to_boot = 1;
		} else {
			slot_index_to_boot = 0;
		}
	} else if(slot_is_bootable(&ab_data.slots[0])) {
		slot_index_to_boot = 0;
	} else if(slot_is_bootable(&ab_data.slots[1])) {
		slot_index_to_boot = 1;
	} else {
		printf("No bootable slots found.\n");
		ret = AVB_AB_FLOW_RESULT_ERROR_NO_BOOTABLE_SLOTS;
		goto out;
	}

	if (slot_index_to_boot == 0) {
		strcpy(select_slot, "_a");
	} else if(slot_index_to_boot == 1) {
		strcpy(select_slot, "_b");
	}

	if (last_slot_index != slot_index_to_boot) {
		last_slot_index = slot_index_to_boot;
		printf("A/B-slot: %s, successful: %d, tries-remain: %d\n",
		       select_slot,
		       ab_data.slots[slot_index_to_boot].successful_boot,
		       ab_data.slots[slot_index_to_boot].tries_remaining);
	}
out:
	return ret;
}

AvbIOResult avb_ab_mark_slot_unbootable(AvbABOps* ab_ops,
                                        unsigned int slot_number)
{
        AvbABData ab_data, ab_data_orig;
        AvbIOResult ret;

        avb_assert(slot_number < 2);

        ret = load_metadata(ab_ops, &ab_data, &ab_data_orig);
        if (ret != AVB_IO_RESULT_OK) {
                goto out;
        }

        slot_set_unbootable(&ab_data.slots[slot_number]);

        ret = AVB_IO_RESULT_OK;

out:
        if (ret == AVB_IO_RESULT_OK) {
                ret = save_metadata_if_changed(ab_ops, &ab_data, &ab_data_orig);
        }
        return ret;
}

AvbIOResult avb_ab_mark_slot_successful(AvbABOps* ab_ops,
                                        unsigned int slot_number)
{
        AvbABData ab_data, ab_data_orig;
        AvbIOResult ret;

        avb_assert(slot_number < 2);

        ret = load_metadata(ab_ops, &ab_data, &ab_data_orig);
        if (ret != AVB_IO_RESULT_OK) {
                goto out;
        }

        if (!slot_is_bootable(&ab_data.slots[slot_number])) {
                printf("Cannot mark unbootable slot as successful.\n");
                ret = AVB_IO_RESULT_OK;
                goto out;
        }

        ab_data.slots[slot_number].tries_remaining = 0;
        ab_data.slots[slot_number].successful_boot = 1;

        ret = AVB_IO_RESULT_OK;

out:
        if (ret == AVB_IO_RESULT_OK) {
                ret = save_metadata_if_changed(ab_ops, &ab_data, &ab_data_orig);
        }
        return ret;
}

int rk_get_lastboot(void)
{

	AvbIOResult io_ret = AVB_IO_RESULT_OK;
	AvbABData ab_data;
	int lastboot = -1;
	AvbOps* ops;

	ops = avb_ops_user_new();
	if (ops == NULL) {
		printf("avb_ops_user_new() failed!\n");
		return -1;
	}

	io_ret = ops->ab_ops->read_ab_metadata(ops->ab_ops, &ab_data);
	if (io_ret != AVB_IO_RESULT_OK) {
		printf("I/O error while loading A/B metadata.\n");
		goto out;
	}

	lastboot = ab_data.last_boot;
out:
	avb_ops_user_free(ops);

	return lastboot;
}

int rk_avb_get_current_slot(char *select_slot)
{
	AvbOps* ops;
	int ret = 0;

	ops = avb_ops_user_new();
	if (ops == NULL) {
		printf("avb_ops_user_new() failed!\n");
		return -1;
	}

	if (rk_avb_ab_slot_select(ops->ab_ops, select_slot) != 0) {
#ifndef CONFIG_ANDROID_AVB
		printf("###There is no bootable slot, bring up last_boot!###\n");
		if (rk_get_lastboot() == 1)
			memcpy(select_slot, "_b", 2);
		else if(rk_get_lastboot() == 0)
			memcpy(select_slot, "_a", 2);
		else
#endif
			return -1;
		ret = 0;
	}

	avb_ops_user_free(ops);
	return ret;
}

bool rk_avb_ab_have_bootable_slot(void)
{
	char slot[3] = {0};

	if (rk_avb_get_current_slot(slot))
		return false;
	else
		return true;
}

int rk_avb_append_part_slot(const char *part_name, char *new_name)
{
	char slot_suffix[3] = {0};

	if (!strcmp(part_name, "misc")) {
		strcat(new_name, part_name);
		return 0;
	}

	if (rk_avb_get_current_slot(slot_suffix)) {
		printf("%s: failed to get slot suffix !\n", __func__);
		return -1;
	}

	strcpy(new_name, part_name);
	strcat(new_name, slot_suffix);

	return 0;
}
