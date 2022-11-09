// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2020, Linaro Limited
 *
 * Tests scmi_agent uclass and the SCMI drivers implemented in other
 * uclass devices probe when a SCMI server exposes resources.
 *
 * Note in test.dts the protocol@10 node in agent 1. Protocol 0x10 is not
 * implemented in U-Boot SCMI components but the implementation is exepected
 * to not complain on unknown protocol IDs, as long as it is not used. Note
 * in test.dts tests that SCMI drivers probing does not fail for such an
 * unknown SCMI protocol ID.
 */

#include <common.h>
#include <dm.h>
#include <asm/scmi_test.h>
#include <dm/device-internal.h>
#include <dm/test.h>
#include <test/ut.h>

/*
 * Test SCMI states when loading and releasing resources
 * related to SCMI drivers.
 */
static int dm_test_scmi_sandbox_agent(struct unit_test_state *uts)
{
	struct sandbox_scmi_service *scmi_ctx = sandbox_scmi_service_ctx();

	ut_assertnonnull(scmi_ctx);
	ut_asserteq(2, scmi_ctx->agent_count);
	ut_assertnull(scmi_ctx->agent[0]);
	ut_assertnull(scmi_ctx->agent[1]);

	return 0;
}

DM_TEST(dm_test_scmi_sandbox_agent, UT_TESTF_SCAN_FDT);
