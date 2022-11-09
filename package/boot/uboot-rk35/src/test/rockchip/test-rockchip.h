/*
 * (C) Copyright 2019 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef _TEST_ROCKCHIP_H
#define _TEST_ROCKCHIP_H

#include <common.h>

#define CMD_FLG_NORMAL			"normal"
#define CMD_FLG_NORETURN		"noreturn"
#define CMD_FLG_INTERACTIVE		"interactive"
#define CMD_FLG_ENABLED(cmd, mode)	(!strcmp((cmd)->usage, mode))
#define CMD_MODE_V1			"v1"
#define CMD_MODE_V2			"v2"
#define CMD_MODE_V3			"v3"

enum test_id {
	TEST_ID_UNK,
	TEST_ID_BOOT,
	TEST_ID_DISPLAY,
	TEST_ID_DOWNLOAD,
	TEST_ID_MISC,
	TEST_ID_NET,
	TEST_ID_POWER,
	TEST_ID_STORAGE,
	TEST_ID_USB,
	TEST_ID_SCSI,
	TEST_ID_MAX,
};

#define UNIT_CMD(_name, _maxargs, _usage)		\
	U_BOOT_CMD_MKENT(_name, _maxargs, 1, do_test_##_name, _usage, "")

#define UNIT_CMD_DEFINE(_name, _maxargs)		\
	UNIT_CMD(_name, _maxargs, "")

#define UNIT_CMD_ATTR_DEFINE(_name, _maxargs, _flag)	\
	UNIT_CMD(_name, _maxargs, _flag)

struct cmd_group {
	int id;
	const char *help;
	cmd_tbl_t *cmd;
	u32 cmd_n;
};

#ifdef CONFIG_LAVA_INFO
#define lava_info(fmt, ...) \
	printf(fmt, ##__VA_ARGS__)
#else
#define lava_info(fmt, ...)
#endif

/* Unit test error message */
#define ut_err(fmt, args...)	printf("[UT-ERROR]: "fmt, ##args)

#endif /* _TEST_ROCKCHIP_H */
