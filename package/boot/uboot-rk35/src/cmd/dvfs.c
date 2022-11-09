// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2018 Fuzhou Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <console.h>
#include <dvfs.h>

static int do_dvfs(cmd_tbl_t *cmdtp, int flag,
		   int argc, char *const argv[])
{
	struct udevice *dev;
	int ret;

	ret = uclass_get_device(UCLASS_DVFS, 0, &dev);
	if (ret) {
		if (ret != -ENODEV)
			printf("DVFS: Get dvfs device failed, ret=%d\n", ret);
		return ret;
	}

	if (argc == 1)
		return dvfs_apply(dev);
	else if (!strcmp(argv[1], "repeat"))
		return dvfs_repeat_apply(dev);
	else
		return CMD_RET_USAGE;

	return 0;
}

U_BOOT_CMD(
	dvfs, 2, 1, do_dvfs,
	"Start DVFS policy",
	"dvfs - apply dvfs policy once\n"
	"dvfs repeat - repeat apply dvfs policy until achieve the target temperature"
);
