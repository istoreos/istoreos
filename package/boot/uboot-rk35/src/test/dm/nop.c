// SPDX-License-Identifier: GPL-2.0+
/*
 * Test for the NOP uclass
 *
 * (C) Copyright 2019 - Texas Instruments Incorporated - http://www.ti.com/
 * Jean-Jacques Hiblot <jjhiblot@ti.com>
 */

#include <common.h>
#include <dm.h>
#include <dm/ofnode.h>
#include <dm/lists.h>
#include <dm/device.h>
#include <dm/test.h>
#include <misc.h>
#include <test/ut.h>

static int noptest_bind(struct udevice *parent)
{
	ofnode ofnode = dev_read_first_subnode(parent);

	while (ofnode_valid(ofnode)) {
		struct udevice *dev;
		const char *bind_flag = ofnode_read_string(ofnode, "bind");

		if (bind_flag && (strcmp(bind_flag, "True") == 0))
			lists_bind_fdt(parent, ofnode, &dev, false);
		ofnode = dev_read_next_subnode(ofnode);
	}

	return 0;
}

static const struct udevice_id noptest1_ids[] = {
	{
		.compatible = "sandbox,nop_sandbox1",
	},
	{ }
};

U_BOOT_DRIVER(noptest_drv1) = {
	.name	= "noptest1_drv",
	.of_match	= noptest1_ids,
	.id	= UCLASS_NOP,
	.bind = noptest_bind,
};

static const struct udevice_id noptest2_ids[] = {
	{
		.compatible = "sandbox,nop_sandbox2",
	},
	{ }
};

U_BOOT_DRIVER(noptest_drv2) = {
	.name	= "noptest2_drv",
	.of_match	= noptest2_ids,
	.id	= UCLASS_NOP,
};

static int dm_test_nop(struct unit_test_state *uts)
{
	struct udevice *dev;

	ut_assertok(uclass_get_device_by_name(UCLASS_NOP, "nop-test_0", &dev));
	ut_assertok(uclass_get_device_by_name(UCLASS_NOP, "nop-test_1", &dev));
	ut_asserteq(-ENODEV,
		    uclass_get_device_by_name(UCLASS_NOP, "nop-test_2", &dev));

	return 0;
}

DM_TEST(dm_test_nop, DM_TESTF_FLAT_TREE | DM_TESTF_SCAN_FDT);
