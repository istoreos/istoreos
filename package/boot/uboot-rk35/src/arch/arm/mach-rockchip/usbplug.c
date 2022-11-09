/*
 * (C) Copyright 2020 Rockchip Electronics Co., Ltd.
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <debug_uart.h>
#include <malloc.h>
#include <mmc.h>
#include <stdlib.h>

DECLARE_GLOBAL_DATA_PTR;

static char *bootdev_rockusb_cmd(void)
{
	const char *devtype, *devnum;
	const char *bootdev_list[] = {
		"mmc",		"0",
		"mtd",		"0",
		"mtd",		"1",
		"mtd",		"2",
		"rknand",	"0",
		NULL,		NULL,
	};
	char *cmd;
	int i = 0;

	devtype = bootdev_list[0];
	devnum = bootdev_list[1];
	while (devtype) {
		if (!strcmp("mmc", devtype))
			mmc_initialize(gd->bd);

		if (blk_get_devnum_by_typename(devtype, atoi(devnum)))
			break;

		i += 2;
		devtype = bootdev_list[i];
		devnum = bootdev_list[i + 1];
	}

	if (!devtype) {
		printf("No boot device\n");
		return NULL;
	}

	printf("Bootdev: %s %s\n", devtype, devnum);

	cmd = malloc(32);
	if (!cmd)
		return NULL;

	snprintf(cmd, 32, "rockusb 0 %s %s", devtype, devnum);

	return cmd;
}

int board_init(void)
{
	return run_command(bootdev_rockusb_cmd(), 0);
}

