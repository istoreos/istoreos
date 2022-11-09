/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2019-2020 Linaro Limited.
 */
#ifndef _SCMI_AGENT_UCLASS_H
#define _SCMI_AGENT_UCLASS_H

struct udevice;
struct scmi_msg;

/**
 * struct scmi_transport_ops - The functions that a SCMI transport layer must implement.
 */
struct scmi_agent_ops {
	/*
	 * process_msg - Request transport to get the SCMI message processed
	 *
	 * @agent:		Agent using the transport
	 * @msg:		SCMI message to be transmitted
	 */
	int (*process_msg)(struct udevice *dev, struct scmi_msg *msg);
};

#endif /* _SCMI_TRANSPORT_UCLASS_H */
