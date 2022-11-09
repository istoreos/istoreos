// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2020, Linaro Limited
 */

#include <common.h>
#include <dm.h>
#include <malloc.h>
#include <scmi_agent.h>
#include <scmi_agent-uclass.h>
#include <scmi_protocols.h>
#include <asm/io.h>
#include <asm/scmi_test.h>
#include <dm/device_compat.h>

/*
 * The sandbox SCMI agent driver simulates to some extend a SCMI message
 * processing. It simulates few of the SCMI services for some of the
 * SCMI protocols embedded in U-Boot. Currently none.
 *
 * This driver simulates 2 SCMI agents for test purpose.
 *
 * This Driver exports sandbox_scmi_service_ct() for the test sequence to
 * get the state of the simulated services (clock state, rate, ...) and
 * check back-end device state reflects the request send through the
 * various uclass devices, currently nothing.
 */

#define SANDBOX_SCMI_AGENT_COUNT	2

/* The list saves to simulted end devices references for test purpose */
struct sandbox_scmi_agent *sandbox_scmi_agent_list[SANDBOX_SCMI_AGENT_COUNT];

static struct sandbox_scmi_service sandbox_scmi_service_state = {
	.agent = sandbox_scmi_agent_list,
	.agent_count = SANDBOX_SCMI_AGENT_COUNT,
};

struct sandbox_scmi_service *sandbox_scmi_service_ctx(void)
{
	return &sandbox_scmi_service_state;
}

static void debug_print_agent_state(struct udevice *dev, char *str)
{
	struct sandbox_scmi_agent *agent = dev_get_priv(dev);

	dev_dbg(dev, "Dump sandbox_scmi_agent %u: %s\n", agent->idx, str);
};

static int sandbox_scmi_test_process_msg(struct udevice *dev,
					 struct scmi_msg *msg)
{
	switch (msg->protocol_id) {
	case SCMI_PROTOCOL_ID_BASE:
	case SCMI_PROTOCOL_ID_POWER_DOMAIN:
	case SCMI_PROTOCOL_ID_SYSTEM:
	case SCMI_PROTOCOL_ID_PERF:
	case SCMI_PROTOCOL_ID_CLOCK:
	case SCMI_PROTOCOL_ID_SENSOR:
	case SCMI_PROTOCOL_ID_RESET_DOMAIN:
		*(u32 *)msg->out_msg = SCMI_NOT_SUPPORTED;
		return 0;
	default:
		break;
	}

	dev_err(dev, "%s(%s): Unhandled protocol_id %#x/message_id %#x\n",
		__func__, dev->name, msg->protocol_id, msg->message_id);

	if (msg->out_msg_sz < sizeof(u32))
		return -EINVAL;

	/* Intentionnaly report unhandled IDs through the SCMI return code */
	*(u32 *)msg->out_msg = SCMI_PROTOCOL_ERROR;
	return 0;
}

static int sandbox_scmi_test_remove(struct udevice *dev)
{
	struct sandbox_scmi_agent *agent = dev_get_priv(dev);

	debug_print_agent_state(dev, "removed");

	/* We only need to dereference the agent in the context */
	sandbox_scmi_service_ctx()->agent[agent->idx] = NULL;

	return 0;
}

static int sandbox_scmi_test_probe(struct udevice *dev)
{
	static const char basename[] = "sandbox-scmi-agent@";
	struct sandbox_scmi_agent *agent = dev_get_priv(dev);
	const size_t basename_size = sizeof(basename) - 1;

	if (strncmp(basename, dev->name, basename_size))
		return -ENOENT;

	switch (dev->name[basename_size]) {
	case '0':
		*agent = (struct sandbox_scmi_agent){
			.idx = 0,
		};
		break;
	case '1':
		*agent = (struct sandbox_scmi_agent){
			.idx = 1,
		};
		break;
	default:
		dev_err(dev, "%s(): Unexpected agent ID %s\n",
			__func__, dev->name + basename_size);
		return -ENOENT;
	}

	debug_print_agent_state(dev, "probed");

	/* Save reference for tests purpose */
	sandbox_scmi_service_ctx()->agent[agent->idx] = agent;

	return 0;
};

static const struct udevice_id sandbox_scmi_test_ids[] = {
	{ .compatible = "sandbox,scmi-agent" },
	{ }
};

struct scmi_agent_ops sandbox_scmi_test_ops = {
	.process_msg = sandbox_scmi_test_process_msg,
};

U_BOOT_DRIVER(sandbox_scmi_agent) = {
	.name = "sandbox-scmi_agent",
	.id = UCLASS_SCMI_AGENT,
	.of_match = sandbox_scmi_test_ids,
	.priv_auto_alloc_size = sizeof(struct sandbox_scmi_agent),
	.probe = sandbox_scmi_test_probe,
	.remove = sandbox_scmi_test_remove,
	.ops = &sandbox_scmi_test_ops,
};
