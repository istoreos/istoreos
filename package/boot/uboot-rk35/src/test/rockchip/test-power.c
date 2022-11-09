/*
 * (C) Copyright 2019 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>
#include <console.h>
#include <dm.h>
#include <thermal.h>
#include <wdt.h>
#include <asm/io.h>
#include <power/pmic.h>
#include <power/regulator.h>
#include "test-rockchip.h"

#ifdef CONFIG_DM_REGULATOR
static int regulator_change_voltage(struct udevice *dev)
{
	struct dm_regulator_uclass_platdata *uc_pdata;
	int uV, save_uV, step_uV = 12500;
	int i, ret;

	uc_pdata = dev_get_uclass_platdata(dev);

	/* Only voltage changeable regulator will be tested! */
	if ((uc_pdata->max_uV == uc_pdata->min_uV) ||
	    !regulator_get_enable(dev) || strncmp("DCDC", dev->name, 4))
		return 0;

	/* Test get/set() */
	save_uV = regulator_get_value(dev);
	if (save_uV < 0) {
		ut_err("regulator: failed to get volt, ret=%d\n", save_uV);
		return save_uV;
	}

	ret = regulator_set_value(dev, save_uV);
	if (ret < 0) {
		ut_err("regulator: failed to set volt, ret=%d\n", ret);
		return ret;
	}

	for (i = 1; i < 4; i++) {
		uV = regulator_get_value(dev);
		regulator_set_value(dev, uV + step_uV * i);
		printf("%s@%s: set %d uV -> %d uV; read back %d uV\n",
		       dev->name, uc_pdata->name, uV, uV + step_uV * i,
		       regulator_get_value(dev));

		if ((uV + step_uV * i) != regulator_get_value(dev)) {
			ut_err("regulator: %s@%s failed to set volt\n",
			       dev->name, uc_pdata->name);
			ret = -EINVAL;
			break;
		}
	}

	regulator_set_value(dev, save_uV);

	return ret;
}

static int do_test_regulator(cmd_tbl_t *cmdtp, int flag,
			     int argc, char *const argv[])
{
	struct udevice *dev;
	struct uclass *uc;
	int ret;

	ret = uclass_get(UCLASS_REGULATOR, &uc);
	if (ret) {
		ut_err("regulator: failed to get uclass, ret=%d\n", ret);
		return ret;
	}

	for (uclass_first_device(UCLASS_REGULATOR, &dev);
	     dev;
	     uclass_next_device(&dev)) {
		ret = regulator_change_voltage(dev);
		if (ret) {
			ut_err("regulator: failed to change volt, ret=%d\n", ret);
			return ret;
		}
	}

	return 0;
}
#endif

#ifdef CONFIG_DM_RESET
static int do_test_reset(cmd_tbl_t *cmdtp, int flag,
			 int argc, char *const argv[])
{
	return run_command("reset", 0);
}
#endif

#ifdef CONFIG_CMD_DVFS
static int do_test_dvfs(cmd_tbl_t *cmdtp, int flag,
			int argc, char *const argv[])
{
	return run_command("dvfs", 0);
}
#endif

#if defined(CONFIG_WDT)
static int do_test_wdt(cmd_tbl_t *cmdtp, int flag,
		       int argc, char *const argv[])
{
	struct udevice *dev;
	int ret;
	int i;

	ret = uclass_get_device(UCLASS_WDT, 0, &dev);
	if (ret) {
		if (ret != -ENODEV)
			ut_err("wdt: failed to get device, ret=%d\n", ret);
		return ret;
	}

	wdt_start(dev, 5000, 0);

	for (i = 0; i < 5; i++) {
		printf("%s, Ping\n", dev->name);
		wdt_reset(dev);
		mdelay(1000);
	}

	printf("Watchdog would reset system 5s later\n");
	printf("Wait reboot");
	while(1){
		printf(".");
		mdelay(500);
	}

	return 0;
}
#endif

#ifdef CONFIG_DM_THERMAL
static int do_test_thermal(cmd_tbl_t *cmdtp, int flag,
			   int argc, char *const argv[])
{
	struct udevice *dev;
	int ret, temp;

	ret = uclass_get_device(UCLASS_THERMAL, 0, &dev);
	if (ret) {
		ut_err("thermal: failed to get device, ret=%d\n", ret);
		return ret;
	}

	ret = thermal_get_temp(dev, &temp);
	if (ret) {
		ut_err("thermal: failed to get temperature, ret=%d\n", ret);
		return ret;
	}

	printf("Get temperature: %d'c\n", temp);

	return 0;
}
#endif

#ifdef CONFIG_CMD_PMIC
static int do_test_pmic(cmd_tbl_t *cmdtp, int flag,
			int argc, char *const argv[])
{
	struct udevice *dev;
	struct uclass *uc;
	int ret;

	ret = uclass_get(UCLASS_PMIC, &uc);
	if (ret)
		return ret;

	for (uclass_first_device(UCLASS_PMIC, &dev);
	     dev;
	     uclass_next_device(&dev)) {
		env_set("this_pmic", dev->name);
		run_command("pmic dev $this_pmic", 0);
		ret = run_command("pmic dump", 0);
		if (ret) {
			ut_err("pmic: failed to dump register, ret=%d\n", ret);
			goto out;
		}
	}

out:
	env_set("this_pmic", NULL);

	return ret;
}
#endif

#ifdef CONFIG_DM_CHARGE_DISPLAY
static int do_test_charge(cmd_tbl_t *cmdtp, int flag,
			  int argc, char *const argv[])
{
	/* TODO */
	return 0;
}
#endif

static cmd_tbl_t sub_cmd[] = {
#ifdef CONFIG_CMD_CHARGE_DISPLAY
	UNIT_CMD_ATTR_DEFINE(charge, 0, CMD_FLG_NORETURN),
#endif
#ifdef CONFIG_CMD_DVFS
	UNIT_CMD_DEFINE(dvfs, 0),
#endif
#ifdef CONFIG_CMD_PMIC
	UNIT_CMD_DEFINE(pmic, 0),
#endif
#ifdef CONFIG_DM_RESET
	UNIT_CMD_ATTR_DEFINE(reset, 0, CMD_FLG_NORETURN),
#endif
#ifdef CONFIG_DM_REGULATOR
	UNIT_CMD_ATTR_DEFINE(regulator, 0, CMD_FLG_INTERACTIVE),
#endif
#ifdef CONFIG_DM_THERMAL
	UNIT_CMD_DEFINE(thermal, 0),
#endif
#if defined(CONFIG_WDT)
	UNIT_CMD_DEFINE(wdt, 0),
#endif
#ifdef CONFIG_DM_CHARGE_DISPLAY
	UNIT_CMD_DEFINE(charge, 0),
#endif
};

static char sub_cmd_help[] =
#ifdef CONFIG_CMD_CHARGE_DISPLAY
"    [i] rktest charge                      - test charge animation\n"
#endif
#ifdef CONFIG_CMD_DVFS
"    [.] rktest dvfs                        - test rockchip wide temperature dvfs\n"
#endif
#ifdef CONFIG_CMD_PMIC
"    [.] rktest pmic                        - test pmic, dump registers\n"
#endif
#ifdef CONFIG_DM_RESET
"    [n] rktest reset                       - test sysreset\n"
#endif
#ifdef CONFIG_DM_REGULATOR
"    [i] rktest regulator                   - test regulator set and show\n"
#endif
#ifdef CONFIG_DM_THERMAL
"    [.] rktest thermal                     - test thermal, getting temperature\n"
#endif
;

const struct cmd_group cmd_grp_power = {
	.id	= TEST_ID_POWER,
	.help	= sub_cmd_help,
	.cmd	= sub_cmd,
	.cmd_n	= ARRAY_SIZE(sub_cmd),
};
