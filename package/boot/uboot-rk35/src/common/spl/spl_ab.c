// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <blk.h>
#include <spl_ab.h>

int safe_memcmp(const void *s1, const void *s2, size_t n)
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

static bool spl_ab_data_verify_and_byteswap(const AvbABData *src,
					    AvbABData *dest)
{
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
		crc32(0, (const uint8_t *)dest,
		      sizeof(AvbABData) - sizeof(uint32_t))) {
		printf("CRC32 does not match.\n");
		return false;
	}

	return true;
}

static void spl_ab_data_update_crc_and_byteswap(const AvbABData *src,
						AvbABData *dest)
{
	memcpy(dest, src, sizeof(AvbABData));
	dest->crc32 = htobe32(crc32(0, (const uint8_t *)dest,
			    sizeof(AvbABData) - sizeof(uint32_t)));
}

static void spl_ab_data_init(AvbABData *data)
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

static int spl_read_ab_metadata(struct blk_desc *dev_desc, AvbABData *ab_data,
				char *partition)
{
	disk_partition_t part_info;
	char temp[512];
	int ret;

	if (!dev_desc || !partition || !ab_data)
		return -EFAULT;

	if (part_get_info_by_name(dev_desc, partition, &part_info) < 0)
		return -ENOENT;

	ret = blk_dread(dev_desc, part_info.start + AB_METADATA_OFFSET, 1,
			temp);
	if (ret != 1)
		return -ENODEV;

	if (sizeof(AvbABData) > 512)
		return -ENOMEM;

	memcpy(ab_data, temp, sizeof(AvbABData));

	return 0;
}

static int spl_write_ab_metadata(struct blk_desc *dev_desc, AvbABData *ab_data,
				 char *partition)
{
	disk_partition_t part_info;
	char temp[512];
	int ret;

	if (!dev_desc || !partition || !ab_data)
		return -EFAULT;

	if (sizeof(AvbABData) > 512)
		return -ENOMEM;

	memcpy(temp, ab_data, sizeof(AvbABData));
	if (part_get_info_by_name(dev_desc, partition, &part_info) < 0)
		return -ENOENT;

	ret = blk_dwrite(dev_desc, part_info.start + AB_METADATA_OFFSET, 1,
			 temp);
	if (ret != 1)
		return -ENODEV;

	return 0;
}

static int spl_ab_data_write(struct blk_desc *dev_desc, AvbABData *ab_data,
			     char *partition)
{
	AvbABData serialized;

	spl_ab_data_update_crc_and_byteswap(ab_data, &serialized);

	return spl_write_ab_metadata(dev_desc, &serialized, partition);
}

static int spl_ab_data_read(struct blk_desc *dev_desc, AvbABData *ab_data,
			    char *partition)
{
	int ret;
	AvbABData serialized;

	ret = spl_read_ab_metadata(dev_desc, &serialized, partition);
	if (ret)
		return ret;

	if (!spl_ab_data_verify_and_byteswap(&serialized, ab_data)) {
		printf("Error validating A/B metadata from disk. "
		       "Resetting and writing new A/B metadata to disk.\n");
		spl_ab_data_init(ab_data);
		spl_ab_data_write(dev_desc, ab_data, partition);
	}

	return 0;
}

static bool spl_slot_is_bootable(AvbABSlotData *slot)
{
	return slot->priority > 0 &&
		(slot->successful_boot || (slot->tries_remaining > 0));
}

static int spl_get_lastboot(AvbABData *ab_data)
{
	return ab_data->last_boot;
}

int spl_get_current_slot(struct blk_desc *dev_desc, char *partition, char *slot)
{
	static int last_slot_index = -1;
	size_t slot_index_to_boot;
	AvbABData ab_data;
	int ret;

	ret = spl_ab_data_read(dev_desc, &ab_data, partition);
	if (ret)
		return ret;

	if (spl_slot_is_bootable(&ab_data.slots[0]) &&
	    spl_slot_is_bootable(&ab_data.slots[1])) {
		if (ab_data.slots[1].priority > ab_data.slots[0].priority)
			slot_index_to_boot = 1;
		else
			slot_index_to_boot = 0;
	} else if (spl_slot_is_bootable(&ab_data.slots[0])) {
		slot_index_to_boot = 0;
	} else if (spl_slot_is_bootable(&ab_data.slots[1])) {
		slot_index_to_boot = 1;
	} else {
		printf("No bootable slots found, use lastboot.\n");
		if (spl_get_lastboot(&ab_data) == 0) {
			memcpy(slot, "_a", 2);
			goto out;
		} else if (spl_get_lastboot(&ab_data) == 1) {
			memcpy(slot, "_b", 2);
			goto out;
		} else {
			return -ENODEV;
		}
	}

	if (slot_index_to_boot == 0)
		memcpy(slot, "_a", 2);
	else if (slot_index_to_boot == 1)
		memcpy(slot, "_b", 2);

	if (last_slot_index != slot_index_to_boot) {
		last_slot_index = slot_index_to_boot;
		printf("SPL: A/B-slot: %s, successful: %d, tries-remain: %d\n",
		       slot,
		       ab_data.slots[slot_index_to_boot].successful_boot,
		       ab_data.slots[slot_index_to_boot].tries_remaining);
	}

out:
	return 0;
}

int spl_ab_append_part_slot(struct blk_desc *dev_desc,
			    const char *part_name,
			    char *new_name)
{
	char slot_suffix[3] = {0};

	if (!strcmp(part_name, "misc")) {
		strcat(new_name, part_name);
		return 0;
	}

	if (spl_get_current_slot(dev_desc, "misc", slot_suffix)) {
		printf("No misc partition\n");
		strcat(new_name, part_name);
		return 0;
	}

	strcpy(new_name, part_name);
	strcat(new_name, slot_suffix);

	return 0;
}

static int spl_save_metadata_if_changed(struct blk_desc *dev_desc,
					AvbABData *ab_data,
					AvbABData *ab_data_orig)
{
	if (safe_memcmp(ab_data, ab_data_orig, sizeof(AvbABData)))
		return spl_ab_data_write(dev_desc, ab_data, "misc");

	return 0;
}

/* If verify fail in a/b system, then decrease 1. */
int spl_ab_decrease_tries(struct blk_desc *dev_desc)
{
	AvbABData ab_data, ab_data_orig;
	size_t slot_index = 0;
	char slot_suffix[3] = {0};
	int ret = -1;

	ret = spl_get_current_slot(dev_desc, "misc", slot_suffix);
	if (ret)
		goto out;

	if (!strncmp(slot_suffix, "_a", 2))
		slot_index = 0;
	else if (!strncmp(slot_suffix, "_b", 2))
		slot_index = 1;
	else
		slot_index = 0;

	ret = spl_ab_data_read(dev_desc, &ab_data, "misc");
	if (ret)
		goto out;

	memcpy(&ab_data_orig, &ab_data, sizeof(AvbABData));

	/* ... and decrement tries remaining, if applicable. */
	if (!ab_data.slots[slot_index].successful_boot &&
	    ab_data.slots[slot_index].tries_remaining > 0)
		ab_data.slots[slot_index].tries_remaining -= 1;

	ret = spl_save_metadata_if_changed(dev_desc, &ab_data, &ab_data_orig);

out:
	return ret;
}
