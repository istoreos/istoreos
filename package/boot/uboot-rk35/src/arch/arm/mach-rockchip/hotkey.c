// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
 */

#include <common.h>
#include <bidram.h>
#include <cli.h>
#include <console.h>
#include <sysmem.h>
#include <asm/arch-rockchip/hotkey.h>

DECLARE_GLOBAL_DATA_PTR;

#define CTRL_A		0x01	/* shell(cli) on BOOTM_STATE_OS_PREP */
#define CTRL_B		0x02	/* bootrom mode */
#define CTRL_D		0x04	/* download mde */
#define CTRL_F		0x06	/* fastboot mode */
#define CTRL_I		0x09	/* inicall debug for kernel */
#define CTRL_M		0x0d	/* memory(sysmem/bidram) */
#define CTRL_P		0x10	/* parameter(cmdline) dump */
#define CTRL_R		0x12	/* regulator initial state dump */
#define CTRL_S		0x13	/* shell(cli) on BOOTM_STATE_OS_GO */
#define CTRL_T		0x14	/* print fdt */

bool is_hotkey(enum hotkey_t id)
{
	switch (id) {
	case HK_CMDLINE:
		return gd->console_evt == CTRL_P;
	case HK_INITCALL:
		return gd->console_evt == CTRL_I;
	case HK_REGULATOR:
		return gd->console_evt == CTRL_R;
	case HK_SYSMEM:
		return gd->console_evt == CTRL_M;
	case HK_BROM_DNL:
		return gd->console_evt == CTRL_B;
#ifndef CONFIG_CONSOLE_DISABLE_CLI
	case HK_ROCKUSB_DNL:
		return gd->console_evt == CTRL_D;
	case HK_FASTBOOT:
		return gd->console_evt == CTRL_F;
#endif
	default:
		break;
	}

	return false;
}

void hotkey_run(enum hotkey_t id)
{
	switch ((id)) {
	case HK_SYSMEM:
		if (gd->console_evt == CTRL_M) {
			bidram_dump();
			sysmem_dump();
		}
		break;
	case HK_CMDLINE:
		if (gd->console_evt == CTRL_P)
			printf("cmdline: %s\n", env_get("bootargs"));
		break;
	case HK_INITCALL:
		if (gd->console_evt == CTRL_I)
			env_update("bootargs", "initcall_debug debug");
		break;
	case HK_FDT:
		if (gd->console_evt == CTRL_T)
			run_command("fdt print", 0);
		break;
	case HK_CLI_OS_PRE:
		if (gd->console_evt == CTRL_A)
			cli_loop();
		break;
	case HK_CLI_OS_GO:
		if (gd->console_evt == CTRL_S)
			cli_loop();
		break;
	default:
		break;
	}
}
