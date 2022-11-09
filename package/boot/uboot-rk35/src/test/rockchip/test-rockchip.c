/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <console.h>
#include "test-rockchip.h"

extern struct cmd_group cmd_grp_boot;
extern struct cmd_group cmd_grp_download;
#ifdef CONFIG_RKIMG_BOOTLOADER
extern struct cmd_group cmd_grp_display;
extern struct cmd_group cmd_grp_misc;
#endif
extern struct cmd_group cmd_grp_net;
extern struct cmd_group cmd_grp_power;
extern struct cmd_group cmd_grp_storage;

enum {
	TEST_SKIP_UNK,
	TEST_SKIP_NORETURN,
	TEST_SKIP_INTERACTIVE,
	TEST_SKIP_NORETURN_INTERACTIVE,
	TEST_SKIP_MAX,
};

static const char *cmd_grp_name[] = {
	[TEST_ID_UNK]		= "UNK",
	[TEST_ID_BOOT]		= "BOOT",
	[TEST_ID_DISPLAY]	= "DISPLAY",
	[TEST_ID_DOWNLOAD]	= "DOWNLOAD",
	[TEST_ID_MISC]		= "MISC",
	[TEST_ID_NET]		= "NET",
	[TEST_ID_POWER]		= "POWER",
	[TEST_ID_STORAGE]	= "STORAGE",
	[TEST_ID_USB]		= "USB",
	[TEST_ID_MAX]		= "MAX",
};

static const struct cmd_group *cmd_groups[] = {
	&cmd_grp_download,
	&cmd_grp_boot,
	&cmd_grp_storage,
	&cmd_grp_power,
	&cmd_grp_net,
#ifdef CONFIG_RKIMG_BOOTLOADER
	&cmd_grp_misc,
	&cmd_grp_display,
#endif
};

static int cmd_groups_help(void)
{
	int i;

	printf("* Test Case:\n");
	printf("    -.: normal item\n");
	printf("    -n: noreturn item\n");
	printf("    -i: interactive item\n\n");

	printf("* ALL:\n");
	printf("    [.] rktest all                         - test all\n");
	printf("    [.] rktest all v1                      - test all, ignore noreturn items\n");
	printf("    [.] rktest all v2                      - test all, ignore interactive items\n");
	printf("    [.] rktest all v3                      - test all, ignore interactive and noreturn items\n");
	printf("    [.] rktest storage			   - test all storage\n");
	printf("    [.] rktest power			   - test all power\n");
	printf("    [.] rktest misc			   - test all misc\n");
	printf("    [.] rktest net			   - test all net\n");
	printf("    [.] rktest display			   - test all display\n");

	for (i = 0; i < ARRAY_SIZE(cmd_groups); i++) {
		printf("* %s:\n", cmd_grp_name[cmd_groups[i]->id]);
		printf("%s", cmd_groups[i]->help);
	}

	return 0;
}

static int skip_this_cmd(cmd_tbl_t *cp, int skip_mode)
{
	bool is_interactive = CMD_FLG_ENABLED(cp, CMD_FLG_INTERACTIVE);
	bool is_noreturn = CMD_FLG_ENABLED(cp, CMD_FLG_NORETURN);

	switch (skip_mode) {
	case TEST_SKIP_NORETURN:
		return is_noreturn;
	case TEST_SKIP_INTERACTIVE:
		return is_interactive;
	case TEST_SKIP_NORETURN_INTERACTIVE:
		return is_noreturn || is_interactive;
	}

	return 0;
}
static int do_rockchip_test(cmd_tbl_t *cmdtp, int flag,
			    int argc, char *const argv[])
{
	ulong ms_start = 0, ms = 0, sec = 0;
	int grp_test_id = TEST_ID_UNK;
	int okay = 0, fail = 0;
	int ret, i, j;
	int skip_mode = 0;
	cmd_tbl_t *cp;

	if (argc == 1)
		return cmd_groups_help();

	/* Drop initial "rktest" arg */
	argc--;
	argv++;

	if (!strcmp(argv[0], "all")) {
		/* Test all skip_mode: v1, v2, v3... */
		if (argv[1]) {
			if (!strcmp(argv[1], CMD_MODE_V1))
				skip_mode = TEST_SKIP_NORETURN;
			else if (!strcmp(argv[1], CMD_MODE_V2))
				skip_mode = TEST_SKIP_INTERACTIVE;
			else if (!strcmp(argv[1], CMD_MODE_V3))
				skip_mode = TEST_SKIP_NORETURN_INTERACTIVE;
		}
		/* rktest all has no valid parameter */
		argc = 1;
		goto all_test;
	} else {
		if (!strcmp(argv[0], "storage"))
			grp_test_id = TEST_ID_STORAGE;
		else if (!strcmp(argv[0], "power"))
			grp_test_id = TEST_ID_POWER;
		else if (!strcmp(argv[0], "misc"))
			grp_test_id = TEST_ID_MISC;
		else if (!strcmp(argv[0], "net"))
			grp_test_id = TEST_ID_NET;
		else if (!strcmp(argv[0], "display"))
			grp_test_id = TEST_ID_DISPLAY;

		if (grp_test_id != TEST_ID_UNK) {
			skip_mode = TEST_SKIP_NORETURN; /* Skip noreturn item */
			goto all_test;
		}
	}

/* item_test: */
	for (i = 0; i < ARRAY_SIZE(cmd_groups); i++) {
		cp = find_cmd_tbl(argv[0],
				  cmd_groups[i]->cmd,
				  cmd_groups[i]->cmd_n);
		if (cp) {
			ret = cp->cmd(cmdtp, flag, argc, argv);
			printf("\n### [%s] test done, result: <%s>..\n",
			       cp->name, ret ? "FAILED" : "OKAY");

			return ret;
		}
	}

	printf("Unknown cmd: rktest %s (Not enabled ?)\n", argv[0]);
	goto finish;

all_test:
	lava_info("<LAVA_SIGNAL_STARTRUN u-boot-function 0>\n");
	ms_start = get_timer(0);
	for (i = 0; i < ARRAY_SIZE(cmd_groups); i++) {
		/*
		 * If 'grp_test_id != TEST_ID_UNK', now is group test, find
		 * the grp cmd.
		 */
		if (grp_test_id != TEST_ID_UNK &&
		    grp_test_id != cmd_groups[i]->id)
			continue;

		/* Run all commands in 'this' grp */
		for (j = 0, cp = cmd_groups[i]->cmd;
		     j < cmd_groups[i]->cmd_n;
		     j++, cp++) {
			/* Skip this ignored cmd */
			if (skip_this_cmd(cp, skip_mode)) {
				printf("### Skip  [%s]\n", cp->name);
				lava_info("<LAVA_SIGNAL_TESTCASE TEST_CASE_ID=%s RESULT=skip>\n", cp->name);
				continue;
			}

			printf("### Start [%s]\n", cp->name);
#ifdef CONFIG_RKIMG_BOOTLOADER
			/* Flush console */
			if (cmd_groups[i]->id == TEST_ID_DOWNLOAD)
				flushc();
#endif
			/* Execute command */
			ret = cp->cmd(cmdtp, flag, argc, argv);
			if (ret) {
				lava_info("<LAVA_SIGNAL_TESTCASE TEST_CASE_ID=%s RESULT=fail>\n", cp->name);
				fail++;
			} else {
				lava_info("<LAVA_SIGNAL_TESTCASE TEST_CASE_ID=%s RESULT=pass>\n", cp->name);
				okay++;
			}

			/* Result */
			printf("### Finish, result: <%s>\n\n",
			       ret ? "FAILED" : "PASS");

			if (ctrlc()) {
				printf("Exit board test by ctrl+c\n");
				break;
			}
		}
	}

	/* Total time and report */
	ms = get_timer(ms_start);
	if (ms >= 1000) {
		sec = ms / 1000;
		ms = ms % 1000;
	}
	printf("[=== SUM: pass: %d; failed: %d; total: %lu.%lus ===]\n\n\n",
	       okay, fail, sec, ms);
/*
 * LAVA result with meansure data
 * lava_info("<LAVA_SIGNAL_TESTCASE TEST_CASE_ID=dd-write-mean RESULT=pass UNITS=MB/s MEASUREMENT=37.42>");
 */
	lava_info("<LAVA_SIGNAL_ENDRUN u-boot-function 0>\n");
	lava_info("<LAVA_TEST_RUNNER>: exiting u-boot-function\n");

finish:
	return 0;
}

U_BOOT_CMD(
	rktest, 10, 0, do_rockchip_test,
	"Rockchip board modules test",
	NULL
);
