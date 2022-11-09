/*
 * Copyright (C) 2017 The Android Open Source Project
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <android_cmds.h>

#include <common.h>
#include <part.h>

/**
 * part_get_info_by_dev_and_name - Parse a device number and partition name
 * string in the form of "device_num;partition_name", for example "0;misc".
 * If the partition is found, sets dev_desc and part_info accordingly with the
 * information of the partition with the given partition_name.
 *
 * @dev_iface:		Device interface.
 * @dev_part_str:	Input string argument, like "0;misc".
 * @dev_desc:		Place to store the device description pointer.
 * @part_info:		Place to store the partition information.
 * @return 0 on success, or -1 on error
 */
static int part_get_info_by_dev_and_name(const char *dev_iface,
					 const char *dev_part_str,
					 struct blk_desc **dev_desc,
					 disk_partition_t *part_info)
{
	char *ep;
	const char *part_str;
	int dev_num;

	part_str = strchr(dev_part_str, ';');
	if (!part_str || part_str == dev_part_str)
		return -1;

	dev_num = simple_strtoul(dev_part_str, &ep, 16);
	if (ep != part_str) {
		/* Not all the first part before the ; was parsed. */
		return -1;
	}
	part_str++;

	*dev_desc = blk_get_dev(dev_iface, dev_num);
	if (!*dev_desc) {
		printf("Could not find %s %d\n", dev_iface, dev_num);
		return -1;
	}
	if (part_get_info_by_name(*dev_desc, part_str, part_info) < 0) {
		printf("Could not find \"%s\" partition\n", part_str);
		return -1;
	}
	return 0;
}

int part_get_info_by_dev_and_name_or_num(const char *dev_iface,
					 const char *dev_part_str,
					 struct blk_desc **dev_desc,
					 disk_partition_t *part_info) {
	/* Split the part_name if passed as "$dev_num;part_name". */
	if (!part_get_info_by_dev_and_name(dev_iface, dev_part_str,
					   dev_desc, part_info))
		return 0;
	/* Couldn't lookup by name, try looking up the partition description
	 * directly.
	 */
	if (blk_get_device_part_str(dev_iface, dev_part_str,
				    dev_desc, part_info, 1) < 0) {
		printf("Couldn't find partition %s %s\n",
		       dev_iface, dev_part_str);
		return -1;
	}
	return 0;
}
