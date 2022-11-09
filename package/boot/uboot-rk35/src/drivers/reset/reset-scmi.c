// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2019-2020 Linaro Limited
 */
#include <common.h>
#include <dm.h>
#include <errno.h>
#include <reset-uclass.h>
#include <scmi_agent.h>
#include <scmi_protocols.h>
#include <asm/types.h>

static int scmi_reset_set_level(struct reset_ctl *rst, bool assert_not_deassert)
{
	struct scmi_rd_reset_in in = {
		.domain_id = rst->id,
		.flags = assert_not_deassert ? SCMI_RD_RESET_FLAG_ASSERT : 0,
		.reset_state = 0,
	};
	struct scmi_rd_reset_out out;
	struct scmi_msg msg = SCMI_MSG_IN(SCMI_PROTOCOL_ID_RESET_DOMAIN,
					  SCMI_RESET_DOMAIN_RESET,
					  in, out);
	int ret;

	ret = devm_scmi_process_msg(rst->dev->parent, &msg);
	if (ret)
		return ret;

	return scmi_to_linux_errno(out.status);
}

static int scmi_reset_assert(struct reset_ctl *rst)
{
	return scmi_reset_set_level(rst, true);
}

static int scmi_reset_deassert(struct reset_ctl *rst)
{
	return scmi_reset_set_level(rst, false);
}

static int scmi_reset_request(struct reset_ctl *rst)
{
	struct scmi_rd_attr_in in = {
		.domain_id = rst->id,
	};
	struct scmi_rd_attr_out out;
	struct scmi_msg msg = SCMI_MSG_IN(SCMI_PROTOCOL_ID_RESET_DOMAIN,
					  SCMI_RESET_DOMAIN_ATTRIBUTES,
					  in, out);
	int ret;

	/*
	 * We don't really care about the attribute, just check
	 * the reset domain exists.
	 */
	ret = devm_scmi_process_msg(rst->dev->parent, &msg);
	if (ret)
		return ret;

	return scmi_to_linux_errno(out.status);
}

static int scmi_reset_rfree(struct reset_ctl *rst)
{
	return 0;
}

static const struct reset_ops scmi_reset_domain_ops = {
	.request	= scmi_reset_request,
	.rfree		= scmi_reset_rfree,
	.rst_assert	= scmi_reset_assert,
	.rst_deassert	= scmi_reset_deassert,
};

U_BOOT_DRIVER(scmi_reset_domain) = {
	.name = "scmi_reset_domain",
	.id = UCLASS_RESET,
	.ops = &scmi_reset_domain_ops,
};
