/*
 * Copyright (C) 2017 The Android Open Source Project
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <android_cmds.h>
#include <android_ab.h>
#include <common.h>
#include <command.h>

static int do_android_ab_select(cmd_tbl_t *cmdtp, int flag, int argc,
				char * const argv[])
{
	int ret;
	struct blk_desc *dev_desc;
	disk_partition_t part_info;
	char slot[2];

	if (argc != 4)
		return CMD_RET_USAGE;

	/* Lookup the "misc" partition from argv[2] and argv[3] */
	if (part_get_info_by_dev_and_name_or_num(argv[2], argv[3],
						 &dev_desc, &part_info) < 0) {
		return CMD_RET_FAILURE;
	}

	ret = android_ab_select(dev_desc, &part_info);
	if (ret < 0) {
		printf("Android boot failed, error %d.\n", ret);
		return CMD_RET_FAILURE;
	}

	/* Android standard slot names are 'a', 'b', ... */
	slot[0] = ANDROID_BOOT_SLOT_NAME(ret);
	slot[1] = '\0';
	env_set(argv[1], slot);
	printf("ANDROID: Booting slot: %s\n", slot);
	return CMD_RET_SUCCESS;
}

U_BOOT_CMD(
	android_ab_select, 4, 0, do_android_ab_select,
	"Select the slot used to boot from and register the boot attempt.",
	"<slot_var_name> <interface> <dev[:part|;part_name]>\n"
	"    - Load the slot metadata from the partition 'part' on\n"
	"      device type 'interface' instance 'dev' and store the active\n"
	"      slot in the 'slot_var_name' variable. This also updates the\n"
	"      Android slot metadata with a boot attempt, which can cause\n"
	"      successive calls to this function to return a different result\n"
	"      if the returned slot runs out of boot attempts.\n"
	"    - If 'part_name' is passed, preceded with a ; instead of :, the\n"
	"      partition name whose label is 'part_name' will be looked up in\n"
	"      the partition table. This is commonly the \"misc\" partition.\n"
);
