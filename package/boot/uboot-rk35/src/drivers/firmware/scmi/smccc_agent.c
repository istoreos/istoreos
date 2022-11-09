// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2020 Linaro Limited.
 */

#include <common.h>
#include <dm.h>
#include <errno.h>
#include <scmi_agent.h>
#include <scmi_agent-uclass.h>
#include <dm/device-internal.h>
#include <dm/read.h>
#include <linux/arm-smccc.h>
#include <linux/compat.h>

#include "smt.h"

#define SMCCC_RET_NOT_SUPPORTED         ((unsigned long)-1)

/**
 * struct scmi_smccc_channel - Description of an SCMI SMCCC transport
 * @func_id:	SMCCC function ID used by the SCMI transport
 * @smt:	Shared memory buffer
 */
struct scmi_smccc_channel {
	ulong func_id;
	struct scmi_smt smt;
};

#ifndef CONFIG_SPL_BUILD
static int scmi_smccc_process_msg(struct udevice *dev, struct scmi_msg *msg)
{
	struct scmi_smccc_channel *chan = dev_get_priv(dev);
	struct arm_smccc_res res;
	int ret;

	ret = scmi_write_msg_to_smt(dev, &chan->smt, msg);
	if (ret)
		return ret;

	arm_smccc_smc(chan->func_id, 0, 0, 0, 0, 0, 0, 0, &res);
	if (res.a0 == SMCCC_RET_NOT_SUPPORTED)
		ret = -ENXIO;
	else
		ret = scmi_read_resp_from_smt(dev, &chan->smt, msg);

	scmi_clear_smt_channel(&chan->smt);

	return ret;
}

static int scmi_smccc_probe(struct udevice *dev)
{
	struct scmi_smccc_channel *chan = dev_get_priv(dev);
	u32 func_id;
	int ret;

	func_id = dev_read_u32_default(dev, "arm,smc-id", -ENODATA);
	if (func_id == -ENODATA) {
		dev_err(dev, "Missing property func-id\n");
		return -EINVAL;
	}

	chan->func_id = func_id;

	ret = scmi_dt_get_smt_buffer(dev, &chan->smt);
	if (ret) {
		dev_err(dev, "Failed to get smt resources: %d\n", ret);
		return ret;
	}

	return 0;
}

static const struct scmi_agent_ops scmi_smccc_ops = {
	.process_msg = scmi_smccc_process_msg,
};
#endif

static const struct udevice_id scmi_smccc_ids[] = {
	{ .compatible = "arm,scmi-smc" },
	{ }
};

U_BOOT_DRIVER(scmi_smccc) = {
	.name		= "scmi-over-smccc",
	.id		= UCLASS_SCMI_AGENT,
	.of_match	= scmi_smccc_ids,
	.priv_auto_alloc_size = sizeof(struct scmi_smccc_channel),
#ifndef CONFIG_SPL_BUILD
	.probe		= scmi_smccc_probe,
	.ops		= &scmi_smccc_ops,
#endif
};
