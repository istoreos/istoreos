/*
 * Copyright (C) 2017 The Android Open Source Project
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef __ANDROID_AB_H
#define __ANDROID_AB_H

#include <common.h>

/* Android standard boot slot names are 'a', 'b', 'c', ... */
#define ANDROID_BOOT_SLOT_NAME(slot_num) ('a' + (slot_num))

#define ENUM_MERGE_STATUS_NONE			(0)
#define ENUM_MERGE_STATUS_UNKNOWN		(1)
#define ENUM_MERGE_STATUS_SNAPSHOTTED		(2)
#define ENUM_MERGE_STATUS_MERGING		(3)
#define ENUM_MERGE_STATUS_CANCELLED		(4)
#define MISC_VIRTUAL_AB_MAGIC_HEADER		(0x56740AB0)

struct misc_virtual_ab_message {
	u8 version;
	u32 magic;
	u8 merge_status;
	u8 source_slot;
	u8 reserved[57];
	u8 reserved2[448];
} __packed;

/** android_ab_select - Select the slot where to boot from.
 * On Android devices with more than one boot slot (multiple copies of the
 * kernel and system images) selects which slot should be used to boot from and
 * registers the boot attempt. This is used in by the new A/B update model where
 * one slot is updated in the background while running from the other slot. If
 * the selected slot did not successfully boot in the past, a boot attempt is
 * registered before returning from this function so it isn't selected
 * indefinitely.
 *
 * @dev_desc:		Place to store the device description pointer.
 * @part_info:		Place to store the partition information.
 * @return the slot number (0-based) on success, or -1 on error.
 */
int android_ab_select(struct blk_desc *dev_desc, disk_partition_t *part_info);

/* Read or write the Virtual A/B message from 32KB offset in /misc.*/
int read_misc_virtual_ab_message(struct misc_virtual_ab_message *message);
int write_misc_virtual_ab_message(struct misc_virtual_ab_message *message);

void ab_update_root_uuid(void);
int ab_get_slot_suffix(char *slot_suffix);
int ab_is_support_dynamic_partition(struct blk_desc *dev_desc);
int ab_decrease_tries(void);
bool ab_can_find_recovery_part(void);

#endif
