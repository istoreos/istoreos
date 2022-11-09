/*
 * Copyright (C) (C) Copyright 2016-2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <command.h>
#include <dm.h>
#include <rknand.h>

static int rknand_curr_dev;
static int do_rknand(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int ret;

	if (argc == 2) {
		if (strncmp(argv[1], "scan", 4) == 0) {
			ret = rknand_scan_namespace();
			if (ret)
				return CMD_RET_FAILURE;

			return ret;
		}
	}

	return blk_common_cmd(argc, argv, IF_TYPE_RKNAND, &rknand_curr_dev);
}

U_BOOT_CMD(
	rknand, 8, 1, do_rknand,
	"rockchip nand flash sub-system",
	"scan - scan Nand devices\n"
	"rknand info - show all available Nand devices\n"
	"rknand device [dev] - show or set current Nand device\n"
	"rknand part [dev] - print partition table of one or all Nand devices\n"
	"rknand read addr blk# cnt - read `cnt' blocks starting at block\n"
	"     `blk#' to memory address `addr'\n"
	"rknand write addr blk# cnt - write `cnt' blocks starting at block\n"
	"     `blk#' from memory address `addr'"
);
