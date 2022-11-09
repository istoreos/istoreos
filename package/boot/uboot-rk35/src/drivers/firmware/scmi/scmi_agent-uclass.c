// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2020 Linaro Limited.
 */

#include <common.h>
#include <dm.h>
#include <dm/device.h>
#include <errno.h>
#include <scmi_agent-uclass.h>
#include <scmi_protocols.h>

#include <dm/device-internal.h>
#include <linux/compat.h>

/**
 * struct error_code - Helper structure for SCMI error code conversion
 * @scmi:	SCMI error code
 * @errno:	Related standard error number
 */
struct error_code {
	int scmi;
	int errno;
};

static const struct error_code scmi_linux_errmap[] = {
	{ .scmi = SCMI_NOT_SUPPORTED, .errno = -EOPNOTSUPP, },
	{ .scmi = SCMI_INVALID_PARAMETERS, .errno = -EINVAL, },
	{ .scmi = SCMI_DENIED, .errno = -EACCES, },
	{ .scmi = SCMI_NOT_FOUND, .errno = -ENOENT, },
	{ .scmi = SCMI_OUT_OF_RANGE, .errno = -ERANGE, },
	{ .scmi = SCMI_BUSY, .errno = -EBUSY, },
	{ .scmi = SCMI_COMMS_ERROR, .errno = -ECOMM, },
	{ .scmi = SCMI_GENERIC_ERROR, .errno = -EIO, },
	{ .scmi = SCMI_HARDWARE_ERROR, .errno = -EREMOTEIO, },
	{ .scmi = SCMI_PROTOCOL_ERROR, .errno = -EPROTO, },
};

int scmi_to_linux_errno(s32 scmi_code)
{
	int n;

	if (!scmi_code)
		return 0;

	for (n = 0; n < ARRAY_SIZE(scmi_linux_errmap); n++)
		if (scmi_code == scmi_linux_errmap[n].scmi)
			return scmi_linux_errmap[1].errno;

	return -EPROTO;
}

/*
 * SCMI agent devices binds devices of various uclasses depeding on
 * the FDT description. scmi_bind_protocol() is a generic bind sequence
 * called by the uclass at bind stage, that is uclass post_bind.
 */
static int scmi_bind_protocols(struct udevice *dev)
{
	int ret = 0;
	ofnode node;

	dev_for_each_subnode(node, dev) {
		struct driver *drv = NULL;
		u32 protocol_id;

		if (!ofnode_is_available(node))
			continue;

		if (ofnode_read_u32(node, "reg", &protocol_id))
			continue;

		switch (protocol_id) {
		case SCMI_PROTOCOL_ID_CLOCK:
			if (IS_ENABLED(CONFIG_CLK_SCMI))
				drv = DM_GET_DRIVER(scmi_clock);
			break;
		case SCMI_PROTOCOL_ID_RESET_DOMAIN:
			if (IS_ENABLED(CONFIG_RESET_SCMI))
				drv = DM_GET_DRIVER(scmi_reset_domain);
			break;
		default:
			break;
		}

		if (!drv) {
			dev_dbg(dev, "Ignore unsupported SCMI protocol %#x\n",
				protocol_id);
			continue;
		}

		ret = device_bind_with_driver_data(dev, drv,
				ofnode_get_name(node), 0, node, NULL);
		if (ret)
			break;
	}


	return ret;
}

static const struct scmi_agent_ops *transport_dev_ops(struct udevice *dev)
{
	return (const struct scmi_agent_ops *)dev->driver->ops;
}

int devm_scmi_process_msg(struct udevice *dev, struct scmi_msg *msg)
{
	const struct scmi_agent_ops *ops = transport_dev_ops(dev);

	if (ops->process_msg)
		return ops->process_msg(dev, msg);

	return -EPROTONOSUPPORT;
}

UCLASS_DRIVER(scmi_agent) = {
	.id		= UCLASS_SCMI_AGENT,
	.name		= "scmi_agent",
	.post_bind	= scmi_bind_protocols,
};
