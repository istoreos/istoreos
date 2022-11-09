/* SPDX-License-Identifier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (c) 2015-2019, Arm Limited and Contributors. All rights reserved.
 * Copyright (C) 2019-2020, Linaro Limited
 */
#ifndef _SCMI_PROTOCOLS_H
#define _SCMI_PROTOCOLS_H

#include <linux/bitops.h>
#include <asm/types.h>

/*
 * Subset the SCMI protocols definition
 * based on SCMI specification v2.0 (DEN0056B)
 * https://developer.arm.com/docs/den0056/b
 */

enum scmi_std_protocol {
	SCMI_PROTOCOL_ID_BASE = 0x10,
	SCMI_PROTOCOL_ID_POWER_DOMAIN = 0x11,
	SCMI_PROTOCOL_ID_SYSTEM = 0x12,
	SCMI_PROTOCOL_ID_PERF = 0x13,
	SCMI_PROTOCOL_ID_CLOCK = 0x14,
	SCMI_PROTOCOL_ID_SENSOR = 0x15,
	SCMI_PROTOCOL_ID_RESET_DOMAIN = 0x16,
};

enum scmi_status_code {
	SCMI_SUCCESS =  0,
	SCMI_NOT_SUPPORTED = -1,
	SCMI_INVALID_PARAMETERS = -2,
	SCMI_DENIED = -3,
	SCMI_NOT_FOUND = -4,
	SCMI_OUT_OF_RANGE = -5,
	SCMI_BUSY = -6,
	SCMI_COMMS_ERROR = -7,
	SCMI_GENERIC_ERROR = -8,
	SCMI_HARDWARE_ERROR = -9,
	SCMI_PROTOCOL_ERROR = -10,
};

/*
 * SCMI Clock Protocol
 */

enum scmi_clock_message_id {
	SCMI_CLOCK_RATE_SET = 0x5,
	SCMI_CLOCK_RATE_GET = 0x6,
	SCMI_CLOCK_CONFIG_SET = 0x7,
};

#define SCMI_CLK_RATE_ASYNC_NOTIFY	BIT(0)
#define SCMI_CLK_RATE_ASYNC_NORESP	(BIT(0) | BIT(1))
#define SCMI_CLK_RATE_ROUND_DOWN	0
#define SCMI_CLK_RATE_ROUND_UP		BIT(2)
#define SCMI_CLK_RATE_ROUND_CLOSEST	BIT(3)

/**
 * struct scmi_clk_state_in - Message payload for CLOCK_CONFIG_SET command
 * @clock_id:	SCMI clock ID
 * @attributes:	Attributes of the targets clock state
 */
struct scmi_clk_state_in {
	u32 clock_id;
	u32 attributes;
};

/**
 * struct scmi_clk_state_out - Response payload for CLOCK_CONFIG_SET command
 * @status:	SCMI command status
 */
struct scmi_clk_state_out {
	s32 status;
};

/**
 * struct scmi_clk_state_in - Message payload for CLOCK_RATE_GET command
 * @clock_id:	SCMI clock ID
 * @attributes:	Attributes of the targets clock state
 */
struct scmi_clk_rate_get_in {
	u32 clock_id;
};

/**
 * struct scmi_clk_rate_get_out - Response payload for CLOCK_RATE_GET command
 * @status:	SCMI command status
 * @rate_lsb:	32bit LSB of the clock rate in Hertz
 * @rate_msb:	32bit MSB of the clock rate in Hertz
 */
struct scmi_clk_rate_get_out {
	s32 status;
	u32 rate_lsb;
	u32 rate_msb;
};

/**
 * struct scmi_clk_state_in - Message payload for CLOCK_RATE_SET command
 * @clock_id:	SCMI clock ID
 * @flags:	Flags for the clock rate set request
 * @rate_lsb:	32bit LSB of the clock rate in Hertz
 * @rate_msb:	32bit MSB of the clock rate in Hertz
 */
struct scmi_clk_rate_set_in {
	u32 flags;
	u32 clock_id;
	u32 rate_lsb;
	u32 rate_msb;
};

/**
 * struct scmi_clk_rate_set_out - Response payload for CLOCK_RATE_SET command
 * @status:	SCMI command status
 */
struct scmi_clk_rate_set_out {
	s32 status;
};

/*
 * SCMI Reset Domain Protocol
 */

enum scmi_reset_domain_message_id {
	SCMI_RESET_DOMAIN_ATTRIBUTES = 0x3,
	SCMI_RESET_DOMAIN_RESET = 0x4,
};

#define SCMI_RD_NAME_LEN		16

#define SCMI_RD_ATTRIBUTES_FLAG_ASYNC	BIT(31)
#define SCMI_RD_ATTRIBUTES_FLAG_NOTIF	BIT(30)

#define SCMI_RD_RESET_FLAG_ASYNC	BIT(2)
#define SCMI_RD_RESET_FLAG_ASSERT	BIT(1)
#define SCMI_RD_RESET_FLAG_CYCLE	BIT(0)

/**
 * struct scmi_rd_attr_in - Payload for RESET_DOMAIN_ATTRIBUTES message
 * @domain_id:	SCMI reset domain ID
 */
struct scmi_rd_attr_in {
	u32 domain_id;
};

/**
 * struct scmi_rd_attr_out - Payload for RESET_DOMAIN_ATTRIBUTES response
 * @status:	SCMI command status
 * @attributes:	Retrieved attributes of the reset domain
 * @latency:	Reset cycle max lantency
 * @name:	Reset domain name
 */
struct scmi_rd_attr_out {
	s32 status;
	u32 attributes;
	u32 latency;
	char name[SCMI_RD_NAME_LEN];
};

/**
 * struct scmi_rd_reset_in - Message payload for RESET command
 * @domain_id:		SCMI reset domain ID
 * @flags:		Flags for the reset request
 * @reset_state:	Reset target state
 */
struct scmi_rd_reset_in {
	u32 domain_id;
	u32 flags;
	u32 reset_state;
};

/**
 * struct scmi_rd_reset_out - Response payload for RESET command
 * @status:	SCMI command status
 */
struct scmi_rd_reset_out {
	s32 status;
};

#endif /* _SCMI_PROTOCOLS_H */
