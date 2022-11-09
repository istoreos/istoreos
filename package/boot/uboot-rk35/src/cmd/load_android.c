/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <common.h>
#include <command.h>

static int do_load_android(cmd_tbl_t *cmdtp, int flag, int argc,
			   char * const argv[])
{
	int boot_partition;
	unsigned long load_address;
	char *addr_arg_endp, *addr_str;
	struct blk_desc *dev_desc;
	disk_partition_t part_info;

	if (argc < 2)
		return CMD_RET_USAGE;
	if (argc > 4)
		return CMD_RET_USAGE;

	if (argc >= 4) {
		load_address = simple_strtoul(argv[3], &addr_arg_endp, 16);
		if (addr_arg_endp == argv[3] || *addr_arg_endp != '\0')
			return CMD_RET_USAGE;
	} else {
		addr_str = env_get("loadaddr");
		if (addr_str != NULL)
			load_address = simple_strtoul(addr_str, NULL, 16);
		else
			load_address = CONFIG_SYS_LOAD_ADDR;
	}

	boot_partition = blk_get_device_part_str(argv[1],
						 (argc >= 3) ? argv[2] : NULL,
						 &dev_desc, &part_info, 1);
	if (boot_partition < 0)
		return CMD_RET_FAILURE;

	if (android_image_load(dev_desc, &part_info, load_address, -1UL) < 0) {
		printf("Error loading Android Image from %s %d:%d to 0x%lx.\n",
		       argv[1], dev_desc->devnum, boot_partition, load_address);
		return CMD_RET_FAILURE;
	}
	return CMD_RET_SUCCESS;
}

U_BOOT_CMD(
	load_android, 4, 0, do_load_android,
	"load Android Boot image from storage.",
	"<interface> [<dev[:part]> [<addr>]]\n"
	"    - Load a binary Android Boot image from the partition 'part' on\n"
	"      device type 'interface' instance 'dev' to address 'addr'."
);
