/*
 * Copyright (C) Copyright 2022 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <dm.h>

static int blk_curr_iftype;  /* 0: IF_TYPE_UNKNOWN */
static int blk_curr_dev = -1;

static int do_blk(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int curr_iftype;
	int curr_dev;

	if (argc < 4)
		return CMD_RET_USAGE;

	if (!strcmp(argv[1], "dev") && argc == 4) {
		curr_iftype = if_typename_to_iftype(argv[2]);
		curr_dev = simple_strtoul(argv[3], NULL, 16);
		if (!blk_show_device(curr_iftype, curr_dev)) {
			blk_curr_iftype = curr_iftype;
			blk_curr_dev = curr_dev;
			printf("... is now current device\n");
			return CMD_RET_SUCCESS;
		} else {
			return CMD_RET_FAILURE;
		}
	}

	if (!blk_curr_iftype || blk_curr_dev == -1) {
		printf("Set the `blk dev <interface> <devnum>` before other command\n\n");
		return CMD_RET_USAGE;
	}

	return blk_common_cmd(argc, argv, blk_curr_iftype, &blk_curr_dev);
}

U_BOOT_CMD(
	blk, 5, 1, do_blk,
	"Block device sub-system",
	"dev <interface> <devnum>\n"
	"blk read  <addr> <blk#> cnt\n"
	"blk write <addr> <blk#> cnt\n"
	"blk erase <blk#> cnt\n"
);

