/* SPDX-License-Identifier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (c) 2015-2019, Arm Limited and Contributors. All rights reserved.
 * Copyright (C) 2019-2020, Linaro Limited
 *
 * An SCMI agent device represent on communication path from a
 * device driver to the remote SCMI server which driver sends
 * messages to and receives response messages from.
 */
#ifndef SCMI_AGENT_H
#define SCMI_AGENT_H

#include <asm/types.h>

struct udevice;

/*
 * struct scmi_msg - Context of a SCMI message sent and the response received
 *
 * @protocol_id:	SCMI protocol ID
 * @message_id:		SCMI message ID for a defined protocol ID
 * @in_msg:		Pointer to the message payload sent by the driver
 * @in_msg_sz:		Byte size of the message payload sent
 * @out_msg:		Pointer to buffer to store response message payload
 * @out_msg_sz:		Byte size of the response buffer and response payload
 */
struct scmi_msg {
	unsigned int protocol_id;
	unsigned int message_id;
	u8 *in_msg;
	size_t in_msg_sz;
	u8 *out_msg;
	size_t out_msg_sz;
};

/* Helper macro to match a message on input/output array references */
#define SCMI_MSG_IN(_protocol, _message, _in_array, _out_array) \
	(struct scmi_msg){			\
		.protocol_id = (_protocol),	\
		.message_id = (_message),	\
		.in_msg = (uint8_t *)&(_in_array),	\
		.in_msg_sz = sizeof(_in_array),	\
		.out_msg = (uint8_t *)&(_out_array),	\
		.out_msg_sz = sizeof(_out_array),	\
	}

/**
 * scmi_send_and_process_msg() - send and process a SCMI message
 *
 * Send a message to a SCMI server through a target SCMI agent device.
 * Caller sets scmi_msg::out_msg_sz to the output message buffer size.
 * On return, scmi_msg::out_msg_sz stores the response payload size.
 *
 * @dev:	SCMI agent device
 * @msg:	Message structure reference
 * @return 0 on success and a negative errno on failure
 */
int devm_scmi_process_msg(struct udevice *dev, struct scmi_msg *msg);

/**
 * scmi_to_linux_errno() - Convert an SCMI error code into a Linux errno code
 *
 * @scmi_errno:	SCMI error code value
 * @return 0 for successful status and a negative errno otherwise
 */
int scmi_to_linux_errno(s32 scmi_errno);

#endif /* SCMI_H */
