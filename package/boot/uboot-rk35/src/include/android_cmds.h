/*
 * Copyright (C) 2017 The Android Open Source Project
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef __ANDROID_CMDS_H
#define __ANDROID_CMDS_H

#include <common.h>

/**
 * part_get_info_by_dev_and_name_or_num - Parse a device number and partition
 * description (either name or number) in the form of device number plus
 * partition name separated by a ";" (like "device_num;partition_name") or
 * a device number plus a partition number separated by a ":". For example both
 * "0;misc" and "0:1" can be valid partition descriptions for a given interface.
 * If the partition is found, sets dev_desc and part_info accordingly with the
 * information of the partition.
 *
 * @dev_iface:		Device interface.
 * @dev_part_str:	Input partition description, like "0;misc" or "0:1".
 * @dev_desc:		Place to store the device description pointer.
 * @part_info:		Place to store the partition information.
 * @return 0 on success, or -1 on error
 */
int part_get_info_by_dev_and_name_or_num(const char *dev_iface,
					 const char *dev_part_str,
					 struct blk_desc **dev_desc,
					 disk_partition_t *part_info);

#endif
