// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2020 Linaro Limited.
 */

#include <common.h>
#include <dm.h>
#include <dm/device_compat.h>
#include <errno.h>
#include <mailbox.h>
#include <scmi_agent.h>
#include <scmi_agent-uclass.h>
#include <dm/devres.h>
#include <linux/compat.h>

#include "smt.h"

#define TIMEOUT_US_10MS			10000

/**
 * struct scmi_mbox_channel - Description of an SCMI mailbox transport
 * @smt:	Shared memory buffer
 * @mbox:	Mailbox channel description
 * @timeout_us:	Timeout in microseconds for the mailbox transfer
 */
struct scmi_mbox_channel {
	struct scmi_smt smt;
	struct mbox_chan mbox;
	ulong timeout_us;
};

static int scmi_mbox_process_msg(struct udevice *dev, struct scmi_msg *msg)
{
	struct scmi_mbox_channel *chan = dev_get_priv(dev);
	int ret;

	ret = scmi_write_msg_to_smt(dev, &chan->smt, msg);
	if (ret)
		return ret;

	/* Give shm addr to mbox in case it is meaningful */
	ret = mbox_send(&chan->mbox, chan->smt.buf);
	if (ret) {
		dev_err(dev, "Message send failed: %d\n", ret);
		goto out;
	}

	/* Receive the response */
	ret = mbox_recv(&chan->mbox, chan->smt.buf, chan->timeout_us);
	if (ret) {
		dev_err(dev, "Response failed: %d, abort\n", ret);
		goto out;
	}

	ret = scmi_read_resp_from_smt(dev, &chan->smt, msg);

out:
	scmi_clear_smt_channel(&chan->smt);

	return ret;
}

int scmi_mbox_probe(struct udevice *dev)
{
	struct scmi_mbox_channel *chan = dev_get_priv(dev);
	int ret;

	chan->timeout_us = TIMEOUT_US_10MS;

	ret = mbox_get_by_index(dev, 0, &chan->mbox);
	if (ret) {
		dev_err(dev, "Failed to find mailbox: %d\n", ret);
		goto out;
	}

	ret = scmi_dt_get_smt_buffer(dev, &chan->smt);
	if (ret)
		dev_err(dev, "Failed to get shm resources: %d\n", ret);

out:
	if (ret)
		devm_kfree(dev, chan);

	return ret;
}

static const struct udevice_id scmi_mbox_ids[] = {
	{ .compatible = "arm,scmi" },
	{ }
};

static const struct scmi_agent_ops scmi_mbox_ops = {
	.process_msg = scmi_mbox_process_msg,
};

U_BOOT_DRIVER(scmi_mbox) = {
	.name		= "scmi-over-mailbox",
	.id		= UCLASS_SCMI_AGENT,
	.of_match	= scmi_mbox_ids,
	.priv_auto_alloc_size = sizeof(struct scmi_mbox_channel),
	.probe		= scmi_mbox_probe,
	.ops		= &scmi_mbox_ops,
};
