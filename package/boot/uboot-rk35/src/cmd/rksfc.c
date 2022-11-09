/*
 * Copyright (c) 2018 Fuzhou Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier: (GPL-2.0+ OR MIT)
 */

#include <common.h>
#include <command.h>
#include <dm.h>
#include <rksfc.h>

static int rksfc_curr_dev;
static int do_rksfc(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int ret;
	u32 dev_type = IF_TYPE_UNKNOWN;

	if (rksfc_curr_dev == 0)
		dev_type = IF_TYPE_SPINAND;
	else if (rksfc_curr_dev == 1)
		dev_type = IF_TYPE_SPINOR;

	if (argc == 2) {
		if (strncmp(argv[1], "scan", 4) == 0) {
			ret = rksfc_scan_namespace();
			if (ret)
				return CMD_RET_FAILURE;

			return ret;
		}
	}

	if (argc == 3) {
		if (strncmp(argv[1], "dev", 3) == 0) {
			if ((int)simple_strtoul(argv[2], NULL, 10) == 0)
				dev_type = IF_TYPE_SPINAND;
			else
				dev_type = IF_TYPE_SPINOR;
		}
	}

	return blk_common_cmd(argc, argv, dev_type, &rksfc_curr_dev);
}

U_BOOT_CMD(
	rksfc, 8, 1, do_rksfc,
	"rockchip sfc sub-system",
	"scan - scan Sfc devices\n"
	"rksfc info - show all available Sfc devices\n"
	"rksfc device [dev] - show or set current Sfc device\n"
	"      dev 0 - spinand\n"
	"      dev 1 - spinor\n"
	"rksfc part [dev] - print partition table of one or all Sfc devices\n"
	"rksfc read addr blk# cnt - read `cnt' blocks starting at block\n"
	"     `blk#' to memory address `addr'\n"
	"rksfc write addr blk# cnt - write `cnt' blocks starting at block\n"
	"     `blk#' from memory address `addr'"
);
