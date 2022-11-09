/*
 * (C) Copyright 2019 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include "test-rockchip.h"

#ifdef CONFIG_CMD_GO
static int do_test_brom(cmd_tbl_t *cmdtp, int flag,
			int argc, char *const argv[])
{
	return run_command("rbrom", 0);
}
#endif

#ifdef CONFIG_CMD_FASTBOOT
static int do_test_fastboot(cmd_tbl_t *cmdtp, int flag,
			    int argc, char *const argv[])
{
	return run_command("fastboot usb 0", 0);
}
#endif

#ifdef CONFIG_CMD_ROCKUSB
static int do_test_rockusb(cmd_tbl_t *cmdtp, int flag,
			   int argc, char *const argv[])
{
	return run_command("rockusb 0 ${devtype} ${devnum}", 0);
}
#endif

#ifdef CONFIG_CMD_NET
static int do_test_tftp(cmd_tbl_t *cmdtp, int flag,
			int argc, char *const argv[])
{
	char load_cmd[64];
	char serverip_cmd[64];
	int ret = 0;

	if (argc != 3)
		return CMD_RET_USAGE;

	snprintf(serverip_cmd, 64, "env set serverip %s", argv[1]);
	snprintf(load_cmd, 64, "tftp %s", argv[2]);
	ret |= run_command(serverip_cmd, 0);
	ret |= run_command("dhcp", 0);
	ret |= run_command(load_cmd, 0);

	if (ret)
		ut_err("tftp: failed to download file\n");

	return ret;
}
#endif

static cmd_tbl_t sub_cmd[] = {
#ifdef CONFIG_CMD_GO
	UNIT_CMD_ATTR_DEFINE(brom, 0, CMD_FLG_NORETURN),
#endif
#ifdef CONFIG_CMD_FASTBOOT
	UNIT_CMD_ATTR_DEFINE(fastboot, 0, CMD_FLG_NORETURN),
#endif
#ifdef CONFIG_CMD_ROCKUSB
	UNIT_CMD_ATTR_DEFINE(rockusb, 0, CMD_FLG_NORETURN),
#endif
#ifdef CONFIG_CMD_NET
	UNIT_CMD_ATTR_DEFINE(tftp, 0, CMD_FLG_NORETURN),
#endif
};

static const char sub_cmd_help[] =
#ifdef CONFIG_CMD_GO
"    [n] rktest brom                        - test bootrom, enter download mode\n"
#endif
#ifdef CONFIG_CMD_FASTBOOT
"    [n] rktest fastboot                    - test fastboot, enter download mode\n"
#endif
#ifdef CONFIG_CMD_ROCKUSB
"    [n] rktest rockusb                     - test rockusb, enter download mode\n"
#endif
#ifdef CONFIG_CMD_NET
"    [.] rktest tftp [serverip] [file]      - test tftp download\n"
#endif
;

const struct cmd_group cmd_grp_download = {
	.id	= TEST_ID_DOWNLOAD,
	.help	= sub_cmd_help,
	.cmd	= sub_cmd,
	.cmd_n	= ARRAY_SIZE(sub_cmd),
};
