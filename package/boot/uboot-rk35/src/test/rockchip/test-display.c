/*
 * (C) Copyright 2019 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <video_rockchip.h>
#include "test-rockchip.h"

#ifdef CONFIG_DRM_ROCKCHIP
int do_test_display(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
	int ret = 0;

	ret |= rockchip_show_logo();
	mdelay(2000);
	ret |= rockchip_show_bmp("logo.bmp");
	mdelay(2000);
	ret |= rockchip_show_bmp("logo_kernel.bmp");
	mdelay(2000);

	ut_err("display: failed to show bmp\n");

	return ret;
}

static cmd_tbl_t sub_cmd[] = {
	UNIT_CMD_DEFINE(display, 0),
};

static const char sub_cmd_help[] =
"    [.] rktest display                     - test display\n"
;

const struct cmd_group cmd_grp_display = {
	.id	= TEST_ID_DISPLAY,
	.help	= sub_cmd_help,
	.cmd	= sub_cmd,
	.cmd_n	= ARRAY_SIZE(sub_cmd),
};
#else
const struct cmd_group cmd_grp_display = {
	.id	= TEST_ID_DISPLAY,
	.help	= NULL,
	.cmd	= NULL,
	.cmd_n	= 0,
};
#endif
