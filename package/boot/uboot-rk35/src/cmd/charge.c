/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <command.h>
#include <dm.h>
#include <power/charge_display.h>
#include <power/charge_animation.h>

static int do_charge_display(cmd_tbl_t *cmdtp, int flag, int argc,
			     char *const argv[])
{

	struct charge_animation_pdata *pdata;
	struct udevice *dev;
	int screen_voltage;
	int on_voltage;
	int on_soc;
	int save[3];
	int ret;

	if (argc != 4 && argc != 1)
		return CMD_RET_USAGE;

	ret = uclass_get_device(UCLASS_CHARGE_DISPLAY, 0, &dev);
	if (ret) {
		if (ret != -ENODEV) {
			printf("Get UCLASS CHARGE DISPLAY failed: %d\n", ret);
			return ret;
		}

		return 0;
	}

	if (argc == 4) {
		pdata = dev_get_platdata(dev);
		save[0] = pdata->exit_charge_level;
		save[1] = pdata->exit_charge_voltage;
		save[2] = pdata->screen_on_voltage;

		on_soc = simple_strtoul(argv[1], NULL, 0);
		on_voltage = simple_strtoul(argv[2], NULL, 0);
		screen_voltage = simple_strtoul(argv[3], NULL, 0);
		debug("new: on_soc=%d, on_voltage=%d, screen_voltage=%d\n",
		      on_soc, on_voltage, screen_voltage);

		pdata->exit_charge_level = on_soc;
		pdata->exit_charge_voltage = on_voltage;
		pdata->screen_on_voltage = screen_voltage;

		charge_display_show(dev);

		pdata->exit_charge_level = save[0];
		pdata->exit_charge_voltage = save[1];
		pdata->screen_on_voltage = save[2];
	} else if (argc == 1) {
		charge_display_show(dev);
	} else {
		return CMD_RET_USAGE;
	}

	return 0;
}

U_BOOT_CMD(charge, 4, 0, do_charge_display,
	   "Charge display",
	   "-charge\n"
	   "-charge <power on soc> <power on voltage> <screen on voltage>"
);
