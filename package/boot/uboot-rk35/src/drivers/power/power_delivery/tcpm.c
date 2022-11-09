// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2015-2017 Google, Inc
 *
 * USB Power Delivery protocol stack.
 */

#include <asm/io.h>
#include <common.h>
#include <dm.h>
#include <asm/gpio.h>
#include <irq-generic.h>
#include <rk_timer_irq.h>
#include <power/power_delivery/tcpm.h>
#include <power/power_delivery/pd_vdo.h>

#define FOREACH_STATE(S)			\
	S(INVALID_STATE),			\
	S(TOGGLING),			\
	S(SRC_UNATTACHED),			\
	S(SRC_ATTACH_WAIT),			\
	S(SRC_ATTACHED),			\
	S(SRC_STARTUP),				\
	S(SRC_SEND_CAPABILITIES),		\
	S(SRC_SEND_CAPABILITIES_TIMEOUT),	\
	S(SRC_NEGOTIATE_CAPABILITIES),		\
	S(SRC_TRANSITION_SUPPLY),		\
	S(SRC_READY),				\
	S(SRC_WAIT_NEW_CAPABILITIES),		\
						\
	S(SNK_UNATTACHED),			\
	S(SNK_ATTACH_WAIT),			\
	S(SNK_DEBOUNCED),			\
	S(SNK_ATTACHED),			\
	S(SNK_STARTUP),				\
	S(SNK_DISCOVERY),			\
	S(SNK_DISCOVERY_DEBOUNCE),		\
	S(SNK_DISCOVERY_DEBOUNCE_DONE),		\
	S(SNK_WAIT_CAPABILITIES),		\
	S(SNK_NEGOTIATE_CAPABILITIES),		\
	S(SNK_NEGOTIATE_PPS_CAPABILITIES),	\
	S(SNK_TRANSITION_SINK),			\
	S(SNK_TRANSITION_SINK_VBUS),		\
	S(SNK_READY),				\
						\
	S(ACC_UNATTACHED),			\
	S(DEBUG_ACC_ATTACHED),			\
	S(AUDIO_ACC_ATTACHED),			\
	S(AUDIO_ACC_DEBOUNCE),			\
						\
	S(HARD_RESET_SEND),			\
	S(HARD_RESET_START),			\
	S(SRC_HARD_RESET_VBUS_OFF),		\
	S(SRC_HARD_RESET_VBUS_ON),		\
	S(SNK_HARD_RESET_SINK_OFF),		\
	S(SNK_HARD_RESET_WAIT_VBUS),		\
	S(SNK_HARD_RESET_SINK_ON),		\
						\
	S(SOFT_RESET),				\
	S(SRC_SOFT_RESET_WAIT_SNK_TX),		\
	S(SNK_SOFT_RESET),			\
	S(SOFT_RESET_SEND),			\
						\
	S(DR_SWAP_ACCEPT),			\
	S(DR_SWAP_SEND),			\
	S(DR_SWAP_SEND_TIMEOUT),		\
	S(DR_SWAP_CANCEL),			\
	S(DR_SWAP_CHANGE_DR),			\
						\
	S(PR_SWAP_ACCEPT),			\
	S(PR_SWAP_SEND),			\
	S(PR_SWAP_SEND_TIMEOUT),		\
	S(PR_SWAP_CANCEL),			\
	S(PR_SWAP_START),			\
	S(PR_SWAP_SRC_SNK_TRANSITION_OFF),	\
	S(PR_SWAP_SRC_SNK_SOURCE_OFF),		\
	S(PR_SWAP_SRC_SNK_SOURCE_OFF_CC_DEBOUNCED), \
	S(PR_SWAP_SRC_SNK_SINK_ON),		\
	S(PR_SWAP_SNK_SRC_SINK_OFF),		\
	S(PR_SWAP_SNK_SRC_SOURCE_ON),		\
	S(PR_SWAP_SNK_SRC_SOURCE_ON_VBUS_RAMPED_UP),    \
						\
	S(VCONN_SWAP_ACCEPT),			\
	S(VCONN_SWAP_SEND),			\
	S(VCONN_SWAP_SEND_TIMEOUT),		\
	S(VCONN_SWAP_CANCEL),			\
	S(VCONN_SWAP_START),			\
	S(VCONN_SWAP_WAIT_FOR_VCONN),		\
	S(VCONN_SWAP_TURN_ON_VCONN),		\
	S(VCONN_SWAP_TURN_OFF_VCONN),		\
						\
	S(FR_SWAP_SEND),			\
	S(FR_SWAP_SEND_TIMEOUT),		\
	S(FR_SWAP_SNK_SRC_TRANSITION_TO_OFF),			\
	S(FR_SWAP_SNK_SRC_NEW_SINK_READY),		\
	S(FR_SWAP_SNK_SRC_SOURCE_VBUS_APPLIED),	\
	S(FR_SWAP_CANCEL),			\
						\
	S(SNK_TRY),				\
	S(SNK_TRY_WAIT),			\
	S(SNK_TRY_WAIT_DEBOUNCE),               \
	S(SNK_TRY_WAIT_DEBOUNCE_CHECK_VBUS),    \
	S(SRC_TRYWAIT),				\
	S(SRC_TRYWAIT_DEBOUNCE),		\
	S(SRC_TRYWAIT_UNATTACHED),		\
						\
	S(SRC_TRY),				\
	S(SRC_TRY_WAIT),                        \
	S(SRC_TRY_DEBOUNCE),			\
	S(SNK_TRYWAIT),				\
	S(SNK_TRYWAIT_DEBOUNCE),		\
	S(SNK_TRYWAIT_VBUS),			\
	S(BIST_RX),				\
						\
	S(GET_STATUS_SEND),			\
	S(GET_STATUS_SEND_TIMEOUT),		\
	S(GET_PPS_STATUS_SEND),			\
	S(GET_PPS_STATUS_SEND_TIMEOUT),		\
						\
	S(GET_SINK_CAP),			\
	S(GET_SINK_CAP_TIMEOUT),		\
						\
	S(ERROR_RECOVERY),			\
	S(PORT_RESET),				\
	S(PORT_RESET_WAIT_OFF),			\
						\
	S(AMS_START),				\
	S(CHUNK_NOT_SUPP)

#define FOREACH_AMS(S)				\
	S(NONE_AMS),				\
	S(POWER_NEGOTIATION),			\
	S(GOTOMIN),				\
	S(SOFT_RESET_AMS),			\
	S(HARD_RESET),				\
	S(CABLE_RESET),				\
	S(GET_SOURCE_CAPABILITIES),		\
	S(GET_SINK_CAPABILITIES),		\
	S(POWER_ROLE_SWAP),			\
	S(FAST_ROLE_SWAP),			\
	S(DATA_ROLE_SWAP),			\
	S(VCONN_SWAP),				\
	S(SOURCE_ALERT),			\
	S(GETTING_SOURCE_EXTENDED_CAPABILITIES),\
	S(GETTING_SOURCE_SINK_STATUS),		\
	S(GETTING_BATTERY_CAPABILITIES),	\
	S(GETTING_BATTERY_STATUS),		\
	S(GETTING_MANUFACTURER_INFORMATION),	\
	S(SECURITY),				\
	S(FIRMWARE_UPDATE),			\
	S(DISCOVER_IDENTITY),			\
	S(SOURCE_STARTUP_CABLE_PLUG_DISCOVER_IDENTITY),	\
	S(DISCOVER_SVIDS),			\
	S(DISCOVER_MODES),			\
	S(DFP_TO_UFP_ENTER_MODE),		\
	S(DFP_TO_UFP_EXIT_MODE),		\
	S(DFP_TO_CABLE_PLUG_ENTER_MODE),	\
	S(DFP_TO_CABLE_PLUG_EXIT_MODE),		\
	S(ATTENTION),				\
	S(BIST),				\
	S(UNSTRUCTURED_VDMS),			\
	S(STRUCTURED_VDMS),			\
	S(COUNTRY_INFO),			\
	S(COUNTRY_CODES)

#define GENERATE_ENUM(e)	e
#define GENERATE_STRING(s)	#s
#define TCPM_POLL_EVENT_TIME_OUT 2000

enum tcpm_state {
	FOREACH_STATE(GENERATE_ENUM)
};

static const char * const tcpm_states[] = {
	FOREACH_STATE(GENERATE_STRING)
};

enum tcpm_ams {
	FOREACH_AMS(GENERATE_ENUM)
};

static const char * const tcpm_ams_str[] = {
	FOREACH_AMS(GENERATE_STRING)
};

enum vdm_states {
	VDM_STATE_ERR_BUSY = -3,
	VDM_STATE_ERR_SEND = -2,
	VDM_STATE_ERR_TMOUT = -1,
	VDM_STATE_DONE = 0,
	/* Anything >0 represents an active state */
	VDM_STATE_READY = 1,
	VDM_STATE_BUSY = 2,
	VDM_STATE_WAIT_RSP_BUSY = 3,
	VDM_STATE_SEND_MESSAGE = 4,
};

enum pd_msg_request {
	PD_MSG_NONE = 0,
	PD_MSG_CTRL_REJECT,
	PD_MSG_CTRL_WAIT,
	PD_MSG_CTRL_NOT_SUPP,
	PD_MSG_DATA_SINK_CAP,
	PD_MSG_DATA_SOURCE_CAP,
};

enum adev_actions {
	ADEV_NONE = 0,
	ADEV_NOTIFY_USB_AND_QUEUE_VDM,
	ADEV_QUEUE_VDM,
	ADEV_QUEUE_VDM_SEND_EXIT_MODE_ON_FAIL,
	ADEV_ATTENTION,
};

/*
 * Initial current capability of the new source when vSafe5V is applied during PD3.0 Fast Role Swap.
 * Based on "Table 6-14 Fixed Supply PDO - Sink" of "USB Power Delivery Specification Revision 3.0,
 * Version 1.2"
 */
enum frs_typec_current {
	FRS_NOT_SUPPORTED,
	FRS_DEFAULT_POWER,
	FRS_5V_1P5A,
	FRS_5V_3A,
};

/* Events from low level driver */

#define TCPM_CC_EVENT		BIT(0)
#define TCPM_VBUS_EVENT		BIT(1)
#define TCPM_RESET_EVENT	BIT(2)
#define TCPM_FRS_EVENT		BIT(3)
#define TCPM_SOURCING_VBUS	BIT(4)

#define LOG_BUFFER_ENTRIES	1024
#define LOG_BUFFER_ENTRY_SIZE	128

/* Alternate mode support */

#define SVID_DISCOVERY_MAX	16
#define ALTMODE_DISCOVERY_MAX	(SVID_DISCOVERY_MAX * MODE_DISCOVERY_MAX)

#define GET_SINK_CAP_RETRY_MS	100
#define SEND_DISCOVER_RETRY_MS	100

/*
 * @min_volt: Actual min voltage at the local port
 * @req_min_volt: Requested min voltage to the port partner
 * @max_volt: Actual max voltage at the local port
 * @req_max_volt: Requested max voltage to the port partner
 * @max_curr: Actual max current at the local port
 * @req_max_curr: Requested max current of the port partner
 * @req_out_volt: Requested output voltage to the port partner
 * @req_op_curr: Requested operating current to the port partner
 * @supported: Parter has atleast one APDO hence supports PPS
 * @active: PPS mode is active
 */
struct pd_pps_data {
	u32 min_volt;
	u32 req_min_volt;
	u32 max_volt;
	u32 req_max_volt;
	u32 max_curr;
	u32 req_max_curr;
	u32 req_out_volt;
	u32 req_op_curr;
	bool supported;
	bool active;
};

enum power_supply_usb_type {
	POWER_SUPPLY_USB_TYPE_UNKNOWN = 0,
	POWER_SUPPLY_USB_TYPE_SDP,              /* Standard Downstream Port */
	POWER_SUPPLY_USB_TYPE_DCP,              /* Dedicated Charging Port */
	POWER_SUPPLY_USB_TYPE_CDP,              /* Charging Downstream Port */
	POWER_SUPPLY_USB_TYPE_ACA,              /* Accessory Charger Adapters */
	POWER_SUPPLY_USB_TYPE_C,                /* Type C Port */
	POWER_SUPPLY_USB_TYPE_PD,               /* Power Delivery Port */
	POWER_SUPPLY_USB_TYPE_PD_DRP,           /* PD Dual Role Port */
	POWER_SUPPLY_USB_TYPE_PD_PPS,           /* PD Programmable Power Supply */
	POWER_SUPPLY_USB_TYPE_APPLE_BRICK_ID,   /* Apple Charging Method */
};

struct tcpm_port {
	struct udevice *dev;
	struct typec_capability typec_caps;
	struct tcpc_dev	*tcpc;

	enum typec_role vconn_role;
	enum typec_role pwr_role;
	enum typec_data_role data_role;
	enum typec_pwr_opmode pwr_opmode;

	struct usb_pd_identity partner_ident;
	struct typec_partner_desc partner_desc;
	struct typec_partner *partner;

	enum typec_cc_status cc_req;

	enum typec_cc_status cc1;
	enum typec_cc_status cc2;
	enum typec_cc_polarity polarity;

	bool attached;
	bool connected;
	int poll_event_cnt;
	enum typec_port_type port_type;

	/*
	 * Set to true when vbus is greater than VSAFE5V min.
	 * Set to false when vbus falls below vSinkDisconnect max threshold.
	 */
	bool vbus_present;

	/*
	 * Set to true when vbus is less than VSAFE0V max.
	 * Set to false when vbus is greater than VSAFE0V max.
	 */
	bool vbus_vsafe0v;

	bool vbus_never_low;
	bool vbus_source;
	bool vbus_charge;

	/* Set to true when Discover_Identity Command is expected to be sent in Ready states. */
	bool send_discover;
	bool op_vsafe5v;

	int try_role;
	int try_snk_count;
	int try_src_count;

	enum pd_msg_request queued_message;

	enum tcpm_state enter_state;
	enum tcpm_state prev_state;
	enum tcpm_state state;
	enum tcpm_state delayed_state;
	unsigned long delay_ms;

	spinlock_t pd_event_lock;
	u32 pd_events;

	bool state_machine_running;
	/* Set to true when VDM State Machine has following actions. */
	bool vdm_sm_running;

	bool tx_complete;
	enum tcpm_transmit_status tx_status;

	struct mutex swap_lock;		/* swap command lock */
	bool swap_pending;
	bool non_pd_role_swap;
	int swap_status;

	unsigned int negotiated_rev;
	unsigned int message_id;
	unsigned int caps_count;
	unsigned int hard_reset_count;
	bool pd_capable;
	bool explicit_contract;
	unsigned int rx_msgid;

	/* Partner capabilities/requests */
	u32 sink_request;
	u32 source_caps[PDO_MAX_OBJECTS];
	unsigned int nr_source_caps;
	u32 sink_caps[PDO_MAX_OBJECTS];
	unsigned int nr_sink_caps;

	/*
	 * whether to wait for the Type-C device to send the DR_SWAP Message flag
	 * For Type-C device with Dual-Role Power and Dual-Role Data, the port side
	 * is used as sink + ufp, then the tcpm framework needs to wait for Type-C
	 * device to initiate DR_swap Message.
	 */
	bool wait_dr_swap_Message;

	/* Local capabilities */
	u32 src_pdo[PDO_MAX_OBJECTS];
	unsigned int nr_src_pdo;
	u32 snk_pdo[PDO_MAX_OBJECTS];
	unsigned int nr_snk_pdo;
	u32 snk_vdo_v1[VDO_MAX_OBJECTS];
	unsigned int nr_snk_vdo_v1;
	u32 snk_vdo[VDO_MAX_OBJECTS];
	unsigned int nr_snk_vdo;

	unsigned int operating_snk_mw;
	bool update_sink_caps;

	/* Requested current / voltage to the port partner */
	u32 req_current_limit;
	u32 req_supply_voltage;
	/* Actual current / voltage limit of the local port */
	u32 current_limit;
	u32 supply_voltage;

	enum power_supply_usb_type usb_type;

	u32 bist_request;

	/* PD state for Vendor Defined Messages */
	enum vdm_states vdm_state;
	u32 vdm_retries;
	/* next Vendor Defined Message to send */
	u32 vdo_data[VDO_MAX_SIZE];
	u8 vdo_count;
	/* VDO to retry if UFP responder replied busy */
	u32 vdo_retry;

	/* PPS */
	struct pd_pps_data pps_data;
	bool pps_pending;
	int pps_status;

	/* Deadline in jiffies to exit src_try_wait state */
	unsigned long max_wait;

	/* port belongs to a self powered device */
	bool self_powered;

	/* Sink FRS */
	enum frs_typec_current new_source_frs_current;

	/* Sink caps have been queried */
	bool sink_cap_done;

	/* Port is still in tCCDebounce */
	bool debouncing;

	/* Collision Avoidance and Atomic Message Sequence */
	enum tcpm_state upcoming_state;
	enum tcpm_ams ams;
	enum tcpm_ams next_ams;
	bool in_ams;

	/* Auto vbus discharge status */
	bool auto_vbus_discharge_enabled;

	/*
	 * When set, port requests PD_P_SNK_STDBY_MW upon entering SNK_DISCOVERY and
	 * the actual currrent limit after RX of PD_CTRL_PSRDY for PD link,
	 * SNK_READY for non-pd link.
	 */
	bool slow_charger_loop;
#ifdef CONFIG_DEBUG_FS
	struct dentry *dentry;
	struct mutex logbuffer_lock;	/* log buffer access lock */
	int logbuffer_head;
	int logbuffer_tail;
	u8 *logbuffer[LOG_BUFFER_ENTRIES];
#endif
};

struct pd_rx_event {
	struct tcpm_port *port;
	struct pd_message msg;
};

static const char * const pd_rev[] = {
	[PD_REV10]		= "rev1",
	[PD_REV20]		= "rev2",
	[PD_REV30]		= "rev3",
};

#define tcpm_cc_is_sink(cc) \
	((cc) == TYPEC_CC_RP_DEF || (cc) == TYPEC_CC_RP_1_5 || \
	 (cc) == TYPEC_CC_RP_3_0)

#define tcpm_port_is_sink(port) \
	((tcpm_cc_is_sink((port)->cc1) && !tcpm_cc_is_sink((port)->cc2)) || \
	 (tcpm_cc_is_sink((port)->cc2) && !tcpm_cc_is_sink((port)->cc1)))

#define tcpm_cc_is_source(cc) ((cc) == TYPEC_CC_RD)
#define tcpm_cc_is_audio(cc) ((cc) == TYPEC_CC_RA)
#define tcpm_cc_is_open(cc) ((cc) == TYPEC_CC_OPEN)

#define tcpm_port_is_source(port) \
	((tcpm_cc_is_source((port)->cc1) && \
	 !tcpm_cc_is_source((port)->cc2)) || \
	 (tcpm_cc_is_source((port)->cc2) && \
	  !tcpm_cc_is_source((port)->cc1)))

#define tcpm_port_is_debug(port) \
	(tcpm_cc_is_source((port)->cc1) && tcpm_cc_is_source((port)->cc2))

#define tcpm_port_is_audio(port) \
	(tcpm_cc_is_audio((port)->cc1) && tcpm_cc_is_audio((port)->cc2))

#define tcpm_port_is_audio_detached(port) \
	((tcpm_cc_is_audio((port)->cc1) && tcpm_cc_is_open((port)->cc2)) || \
	 (tcpm_cc_is_audio((port)->cc2) && tcpm_cc_is_open((port)->cc1)))

#define tcpm_try_snk(port) \
	((port)->try_snk_count == 0 && (port)->try_role == TYPEC_SINK && \
	(port)->port_type == TYPEC_PORT_DRP)

#define tcpm_try_src(port) \
	((port)->try_src_count == 0 && (port)->try_role == TYPEC_SOURCE && \
	(port)->port_type == TYPEC_PORT_DRP)

#define tcpm_data_role_for_source(port) \
	((port)->typec_caps.data == TYPEC_PORT_UFP ? \
	TYPEC_DEVICE : TYPEC_HOST)

#define tcpm_data_role_for_sink(port) \
	((port)->typec_caps.data == TYPEC_PORT_DFP ? \
	TYPEC_HOST : TYPEC_DEVICE)

static enum tcpm_state tcpm_default_state(struct tcpm_port *port)
{
	if (port->port_type == TYPEC_PORT_DRP) {
		if (port->try_role == TYPEC_SINK)
			return SNK_UNATTACHED;
		else if (port->try_role == TYPEC_SOURCE)
			return SRC_UNATTACHED;
		/* Fall through to return SRC_UNATTACHED */
	} else if (port->port_type == TYPEC_PORT_SNK) {
		return SNK_UNATTACHED;
	}
	return SRC_UNATTACHED;
}

static bool tcpm_port_is_disconnected(struct tcpm_port *port)
{
	return (!port->attached && port->cc1 == TYPEC_CC_OPEN &&
		port->cc2 == TYPEC_CC_OPEN) ||
	       (port->attached && ((port->polarity == TYPEC_POLARITY_CC1 &&
				    port->cc1 == TYPEC_CC_OPEN) ||
				   (port->polarity == TYPEC_POLARITY_CC2 &&
				    port->cc2 == TYPEC_CC_OPEN)));
}

static void tcpm_set_cc(struct tcpm_port *port, enum typec_cc_status cc)
{
	debug("%s: cc = %d", __func__, cc);
	port->cc_req = cc;
	port->tcpc->set_cc(port->tcpc, cc);
}

/*
 * Determine RP value to set based on maximum current supported
 * by a port if configured as source.
 * Returns CC value to report to link partner.
 */
static enum typec_cc_status tcpm_rp_cc(struct tcpm_port *port)
{
	const u32 *src_pdo = port->src_pdo;
	int nr_pdo = port->nr_src_pdo;
	int i;

	/*
	 * Search for first entry with matching voltage.
	 * It should report the maximum supported current.
	 */
	for (i = 0; i < nr_pdo; i++) {
		const u32 pdo = src_pdo[i];

		if (pdo_type(pdo) == PDO_TYPE_FIXED &&
		    pdo_fixed_voltage(pdo) == 5000) {
			unsigned int curr = pdo_max_current(pdo);

			if (curr >= 3000)
				return TYPEC_CC_RP_3_0;
			else if (curr >= 1500)
				return TYPEC_CC_RP_1_5;
			return TYPEC_CC_RP_DEF;
		}
	}

	return TYPEC_CC_RP_DEF;
}

static int tcpm_pd_transmit(struct tcpm_port *port,
			    enum tcpm_transmit_type type,
			    const struct pd_message *msg)
{
	int ret;
	int timeout = PD_T_TCPC_TX_TIMEOUT;

	if (msg)
		debug("PD TX, header: %#x\n", le16_to_cpu(msg->header));
	else
		debug("PD TX, type: %#x\n", type);

	port->tx_complete = false;
	ret = port->tcpc->pd_transmit(port->tcpc, type, msg, port->negotiated_rev);
	if (ret < 0)
		return ret;

	while ((timeout > 0) && (!port->tx_complete)) {
		port->tcpc->poll_event(port->tcpc);
		udelay(1000);
		timeout--;
	}

	if (!timeout) {
		printf("%s: pd transmit data timeout\n", __func__);
		return -ETIMEDOUT;
	}

	switch (port->tx_status) {
	case TCPC_TX_SUCCESS:
		port->message_id = (port->message_id + 1) & PD_HEADER_ID_MASK;
		break;
	case TCPC_TX_DISCARDED:
		ret = -EAGAIN;
		break;
	case TCPC_TX_FAILED:
	default:
		ret = -EIO;
		break;
	}

	return ret;
}

void tcpm_pd_transmit_complete(struct tcpm_port *port,
			       enum tcpm_transmit_status status)
{
	debug("%s: PD TX complete, status: %u\n", __func__, status);
	port->poll_event_cnt = 0;
	port->tx_status = status;
	port->tx_complete = true;
}
EXPORT_SYMBOL_GPL(tcpm_pd_transmit_complete);

static int tcpm_set_polarity(struct tcpm_port *port,
			     enum typec_cc_polarity polarity)
{
	int ret;

	debug("%s: polarity %d\n", __func__, polarity);

	ret = port->tcpc->set_polarity(port->tcpc, polarity);
	if (ret < 0)
		return ret;

	port->polarity = polarity;

	return 0;
}

static int tcpm_set_vconn(struct tcpm_port *port, bool enable)
{
	int ret;

	debug("%s: vconn = %d\n", __func__, enable);

	ret = port->tcpc->set_vconn(port->tcpc, enable);
	if (!ret)
		port->vconn_role = enable ? TYPEC_SOURCE : TYPEC_SINK;

	return ret;
}

static u32 tcpm_get_current_limit(struct tcpm_port *port)
{
	enum typec_cc_status cc;
	u32 limit;

	cc = port->polarity ? port->cc2 : port->cc1;
	switch (cc) {
	case TYPEC_CC_RP_1_5:
		limit = 1500;
		break;
	case TYPEC_CC_RP_3_0:
		limit = 3000;
		break;
	case TYPEC_CC_RP_DEF:
	default:
		if (port->tcpc->get_current_limit)
			limit = port->tcpc->get_current_limit(port->tcpc);
		else
			limit = 0;
		break;
	}

	return limit;
}

static int tcpm_set_current_limit(struct tcpm_port *port, u32 max_ma, u32 mv)
{
	int ret = -EOPNOTSUPP;

	debug("Setting voltage/current limit %u mV %u mA\n", mv, max_ma);

	port->supply_voltage = mv;
	port->current_limit = max_ma;

	if (port->tcpc->set_current_limit)
		ret = port->tcpc->set_current_limit(port->tcpc, max_ma, mv);

	return ret;
}

static int tcpm_set_attached_state(struct tcpm_port *port, bool attached)
{
	return port->tcpc->set_roles(port->tcpc, attached, port->pwr_role,
				     port->data_role);
}

static int tcpm_set_roles(struct tcpm_port *port, bool attached,
			  enum typec_role role, enum typec_data_role data)
{
#if 0
	enum typec_orientation orientation;
	enum usb_role usb_role;
#endif
	int ret;

#if 0
	if (port->polarity == TYPEC_POLARITY_CC1)
		orientation = TYPEC_ORIENTATION_NORMAL;
	else
		orientation = TYPEC_ORIENTATION_REVERSE;

	if (data == TYPEC_HOST)
		usb_role = USB_ROLE_HOST;
	else
		usb_role = USB_ROLE_DEVICE;

	ret = tcpm_mux_set(port, TYPEC_STATE_USB, usb_role, orientation);
	if (ret < 0)
		return ret;
#endif

	ret = port->tcpc->set_roles(port->tcpc, attached, role, data);
	if (ret < 0)
		return ret;

	port->pwr_role = role;
	port->data_role = data;
#if 0
	typec_set_data_role(port->typec_port, data);
	typec_set_pwr_role(port->typec_port, role);
#endif

	return 0;
}

static int tcpm_pd_send_source_caps(struct tcpm_port *port)
{
	struct pd_message msg;
	int i;

	memset(&msg, 0, sizeof(msg));

	if (!port->nr_src_pdo) {
		/* No source capabilities defined, sink only */
		msg.header = PD_HEADER_LE(PD_CTRL_REJECT,
					  port->pwr_role,
					  port->data_role,
					  port->negotiated_rev,
					  port->message_id, 0);
	} else {
		msg.header = PD_HEADER_LE(PD_DATA_SOURCE_CAP,
					  port->pwr_role,
					  port->data_role,
					  port->negotiated_rev,
					  port->message_id,
					  port->nr_src_pdo);
	}

	for (i = 0; i < port->nr_src_pdo; i++)
		msg.payload[i] = cpu_to_le32(port->src_pdo[i]);

	return tcpm_pd_transmit(port, TCPC_TX_SOP, &msg);
}

static int tcpm_pd_send_sink_caps(struct tcpm_port *port)
{
	struct pd_message msg;
	unsigned int i;

	memset(&msg, 0, sizeof(msg));

	if (!port->nr_snk_pdo) {
		/* No sink capabilities defined, source only */
		msg.header = PD_HEADER_LE(PD_CTRL_REJECT,
					  port->pwr_role,
					  port->data_role,
					  port->negotiated_rev,
					  port->message_id, 0);
	} else {
		msg.header = PD_HEADER_LE(PD_DATA_SINK_CAP,
					  port->pwr_role,
					  port->data_role,
					  port->negotiated_rev,
					  port->message_id,
					  port->nr_snk_pdo);
	}

	for (i = 0; i < port->nr_snk_pdo; i++)
		msg.payload[i] = cpu_to_le32(port->snk_pdo[i]);

	return tcpm_pd_transmit(port, TCPC_TX_SOP, &msg);
}

static void tcpm_state_machine(struct tcpm_port *port);
static void tcpm_timer_uninit(struct tcpm_port *port);
static void tcpm_timer_irq(int irq, void *data)
{
	struct tcpm_port *port = data;

	writel(TIMER_CLR_INT, TIMER_BASE + TIMER_INTSTATUS);
	tcpm_timer_uninit(port);
	tcpm_state_machine(port);
}

static void tcpm_timer_init(struct tcpm_port *port, uint32_t ms)
{
	uint64_t period = 24000ULL * ms;

	/* Disable before conifg */
	writel(0, TIMER_BASE + TIMER_CTRL);

	/* Config */
	writel((uint32_t)period, TIMER_BASE + TIMER_LOAD_COUNT0);
	writel((uint32_t)(period >> 32), TIMER_BASE + TIMER_LOAD_COUNT1);
	writel(TIMER_CLR_INT, TIMER_BASE + TIMER_INTSTATUS);
	writel(TIMER_EN | TIMER_INT_EN, TIMER_BASE + TIMER_CTRL);

	/* IRQ */
	irq_install_handler(TIMER_IRQ,
			   (interrupt_handler_t *)tcpm_timer_irq, port);
	irq_handler_enable(TIMER_IRQ);
}

static void tcpm_timer_uninit(struct tcpm_port *port)
{
	writel(0, TIMER_BASE + TIMER_CTRL);

	irq_handler_disable(TIMER_IRQ);
	irq_free_handler(TIMER_IRQ);
}

static void mod_tcpm_delayed_work(struct tcpm_port *port, unsigned int delay_ms)
{
	if (delay_ms) {
		tcpm_timer_init(port, delay_ms);
	} else {
		tcpm_timer_uninit(port);
		tcpm_state_machine(port);
	}
}

static void tcpm_set_state(struct tcpm_port *port, enum tcpm_state state,
			   unsigned int delay_ms)
{
	debug("%s: line = %d, delay_ms = %d, set state = %s\n",
		 __func__, __LINE__, delay_ms, tcpm_states[state]);

	if (delay_ms) {
		debug("pending state change %s -> %s @ %u ms [%s]\n",
			 tcpm_states[port->state], tcpm_states[state], delay_ms,
			 pd_rev[port->negotiated_rev]);
		port->delayed_state = state;
		mod_tcpm_delayed_work(port, delay_ms);
		port->delay_ms = delay_ms;
	} else {
		debug("state change %s -> %s\n",
			 tcpm_states[port->state], tcpm_states[state]);
		port->delayed_state = INVALID_STATE;
		port->prev_state = port->state;
		port->state = state;
		/*
		 * Don't re-queue the state machine work item if we're currently
		 * in the state machine and we're immediately changing states.
		 * tcpm_state_machine_work() will continue running the state
		 * machine.
		 */
		if (!port->state_machine_running)
			mod_tcpm_delayed_work(port, 0);
	}
}

static void tcpm_set_state_cond(struct tcpm_port *port, enum tcpm_state state,
				unsigned int delay_ms)
{
	if (port->enter_state == port->state)
		tcpm_set_state(port, state, delay_ms);
	else
		debug("skipped %sstate change %s -> %s [%u ms], context state %s [%s %s]\n",
			delay_ms ? "delayed " : "",
			tcpm_states[port->state], tcpm_states[state],
			delay_ms, tcpm_states[port->enter_state],
			pd_rev[port->negotiated_rev], tcpm_ams_str[port->ams]);
}

static void tcpm_queue_message(struct tcpm_port *port,
			       enum pd_msg_request message)
{
	port->queued_message = message;
	mod_tcpm_delayed_work(port, 0);
}

#if 0
static void tcpm_pd_handle_msg(struct tcpm_port *port,
			       enum pd_msg_request message,
			       enum tcpm_ams ams);
#endif

enum pdo_err {
	PDO_NO_ERR,
	PDO_ERR_NO_VSAFE5V,
	PDO_ERR_VSAFE5V_NOT_FIRST,
	PDO_ERR_PDO_TYPE_NOT_IN_ORDER,
	PDO_ERR_FIXED_NOT_SORTED,
	PDO_ERR_VARIABLE_BATT_NOT_SORTED,
	PDO_ERR_DUPE_PDO,
	PDO_ERR_PPS_APDO_NOT_SORTED,
	PDO_ERR_DUPE_PPS_APDO,
};

static const char * const pdo_err_msg[] = {
	[PDO_ERR_NO_VSAFE5V] =
	" err: source/sink caps should atleast have vSafe5V",
	[PDO_ERR_VSAFE5V_NOT_FIRST] =
	" err: vSafe5V Fixed Supply Object Shall always be the first object",
	[PDO_ERR_PDO_TYPE_NOT_IN_ORDER] =
	" err: PDOs should be in the following order: Fixed; Battery; Variable",
	[PDO_ERR_FIXED_NOT_SORTED] =
	" err: Fixed supply pdos should be in increasing order of their fixed voltage",
	[PDO_ERR_VARIABLE_BATT_NOT_SORTED] =
	" err: Variable/Battery supply pdos should be in increasing order of their minimum voltage",
	[PDO_ERR_DUPE_PDO] =
	" err: Variable/Batt supply pdos cannot have same min/max voltage",
	[PDO_ERR_PPS_APDO_NOT_SORTED] =
	" err: Programmable power supply apdos should be in increasing order of their maximum voltage",
	[PDO_ERR_DUPE_PPS_APDO] =
	" err: Programmable power supply apdos cannot have same min/max voltage and max current",
};

static enum pdo_err tcpm_caps_err(struct tcpm_port *port, const u32 *pdo,
				  unsigned int nr_pdo)
{
	unsigned int i;

	/* Should at least contain vSafe5v */
	if (nr_pdo < 1)
		return PDO_ERR_NO_VSAFE5V;

	/* The vSafe5V Fixed Supply Object Shall always be the first object */
	if (pdo_type(pdo[0]) != PDO_TYPE_FIXED ||
	    pdo_fixed_voltage(pdo[0]) != VSAFE5V)
		return PDO_ERR_VSAFE5V_NOT_FIRST;

	for (i = 1; i < nr_pdo; i++) {
		if (pdo_type(pdo[i]) < pdo_type(pdo[i - 1])) {
			return PDO_ERR_PDO_TYPE_NOT_IN_ORDER;
		} else if (pdo_type(pdo[i]) == pdo_type(pdo[i - 1])) {
			enum pd_pdo_type type = pdo_type(pdo[i]);

			switch (type) {
			/*
			 * The remaining Fixed Supply Objects, if
			 * present, shall be sent in voltage order;
			 * lowest to highest.
			 */
			case PDO_TYPE_FIXED:
				if (pdo_fixed_voltage(pdo[i]) <=
				    pdo_fixed_voltage(pdo[i - 1]))
					return PDO_ERR_FIXED_NOT_SORTED;
				break;
			/*
			 * The Battery Supply Objects and Variable
			 * supply, if present shall be sent in Minimum
			 * Voltage order; lowest to highest.
			 */
			case PDO_TYPE_VAR:
			case PDO_TYPE_BATT:
				if (pdo_min_voltage(pdo[i]) <
				    pdo_min_voltage(pdo[i - 1]))
					return PDO_ERR_VARIABLE_BATT_NOT_SORTED;
				else if ((pdo_min_voltage(pdo[i]) ==
					  pdo_min_voltage(pdo[i - 1])) &&
					 (pdo_max_voltage(pdo[i]) ==
					  pdo_max_voltage(pdo[i - 1])))
					return PDO_ERR_DUPE_PDO;
				break;
			/*
			 * The Programmable Power Supply APDOs, if present,
			 * shall be sent in Maximum Voltage order;
			 * lowest to highest.
			 */
			case PDO_TYPE_APDO:
				if (pdo_apdo_type(pdo[i]) != APDO_TYPE_PPS)
					break;

				if (pdo_pps_apdo_max_voltage(pdo[i]) <
				    pdo_pps_apdo_max_voltage(pdo[i - 1]))
					return PDO_ERR_PPS_APDO_NOT_SORTED;
				else if (pdo_pps_apdo_min_voltage(pdo[i]) ==
					  pdo_pps_apdo_min_voltage(pdo[i - 1]) &&
					 pdo_pps_apdo_max_voltage(pdo[i]) ==
					  pdo_pps_apdo_max_voltage(pdo[i - 1]) &&
					 pdo_pps_apdo_max_current(pdo[i]) ==
					  pdo_pps_apdo_max_current(pdo[i - 1]))
					return PDO_ERR_DUPE_PPS_APDO;
				break;
			default:
				printf("%s: Unknown pdo type\n", __func__);
			}
		}
	}

	return PDO_NO_ERR;
}

static int tcpm_validate_caps(struct tcpm_port *port, const u32 *pdo,
			      unsigned int nr_pdo)
{
	enum pdo_err err_index = tcpm_caps_err(port, pdo, nr_pdo);

	if (err_index != PDO_NO_ERR) {
		printf("%s", pdo_err_msg[err_index]);
		return -EINVAL;
	}

	return 0;
}

/*
 * PD (data, control) command handling functions
 */
static inline enum tcpm_state ready_state(struct tcpm_port *port)
{
	if (port->pwr_role == TYPEC_SOURCE)
		return SRC_READY;
	else
		return SNK_READY;
}

static int tcpm_pd_send_control(struct tcpm_port *port,
				enum pd_ctrl_msg_type type);

#if 0
static void tcpm_pd_handle_msg(struct tcpm_port *port,
			       enum pd_msg_request message,
			       enum tcpm_ams ams)
{
	switch (port->state) {
	case SRC_READY:
	case SNK_READY:
		port->ams = ams;
		tcpm_queue_message(port, message);
		break;
	/* PD 3.0 Spec 8.3.3.4.1.1 and 6.8.1 */
	case SNK_TRANSITION_SINK:
	case SNK_TRANSITION_SINK_VBUS:
	case SRC_TRANSITION_SUPPLY:
		tcpm_set_state(port, HARD_RESET_SEND, 0);
		break;
	default:
		if (!tcpm_ams_interruptible(port)) {
			tcpm_set_state(port, port->pwr_role == TYPEC_SOURCE ?
				       SRC_SOFT_RESET_WAIT_SNK_TX :
				       SNK_SOFT_RESET,
				       0);
		} else {
			port->next_ams = ams;
			tcpm_set_state(port, ready_state(port), 0);
			/* 6.8.1 process the Message */
			tcpm_queue_message(port, message);
		}
		break;
	}
}
#endif

static void tcpm_pd_data_request(struct tcpm_port *port,
				 const struct pd_message *msg)
{
	enum pd_data_msg_type type = pd_header_type_le(msg->header);
	unsigned int cnt = pd_header_cnt_le(msg->header);
	unsigned int rev = pd_header_rev_le(msg->header);
	unsigned int i;

	switch (type) {
	case PD_DATA_SOURCE_CAP:
		for (i = 0; i < cnt; i++)
			port->source_caps[i] = le32_to_cpu(msg->payload[i]);

		port->nr_source_caps = cnt;

		tcpm_validate_caps(port, port->source_caps,
				   port->nr_source_caps);

		/*
		 * Adjust revision in subsequent message headers, as required,
		 * to comply with 6.2.1.1.5 of the USB PD 3.0 spec. We don't
		 * support Rev 1.0 so just do nothing in that scenario.
		 */
		if (rev == PD_REV10) {
			break;
		}

		if (rev < PD_MAX_REV)
			port->negotiated_rev = rev;

		if ((pdo_type(port->source_caps[0]) == PDO_TYPE_FIXED) &&
		     (port->source_caps[0] & PDO_FIXED_DUAL_ROLE) &&
		     (port->source_caps[0] & PDO_FIXED_DATA_SWAP)) {
			/* Dual role power and data, eg: self-powered Type-C */
			port->wait_dr_swap_Message = true;
		} else {
			/* Non-Dual role power, eg: adapter */
			port->wait_dr_swap_Message = false;
		}

		/*
		 * This message may be received even if VBUS is not
		 * present. This is quite unexpected; see USB PD
		 * specification, sections 8.3.3.6.3.1 and 8.3.3.6.3.2.
		 * However, at the same time, we must be ready to
		 * receive this message and respond to it 15ms after
		 * receiving PS_RDY during power swap operations, no matter
		 * if VBUS is available or not (USB PD specification,
		 * section 6.5.9.2).
		 * So we need to accept the message either way,
		 * but be prepared to keep waiting for VBUS after it was
		 * handled.
		 */
		tcpm_set_state(port, SNK_NEGOTIATE_CAPABILITIES, 0);
		break;
	case PD_DATA_REQUEST:
		/*
		 * Adjust revision in subsequent message headers, as required,
		 * to comply with 6.2.1.1.5 of the USB PD 3.0 spec. We don't
		 * support Rev 1.0 so just reject in that scenario.
		 */
		if (rev == PD_REV10) {
			tcpm_queue_message(port, PD_MSG_CTRL_REJECT);
			break;
		}

		if (rev < PD_MAX_REV)
			port->negotiated_rev = rev;

		port->sink_request = le32_to_cpu(msg->payload[0]);

		tcpm_set_state(port, SRC_NEGOTIATE_CAPABILITIES, 0);
		break;
	case PD_DATA_SINK_CAP:
		/* We don't do anything with this at the moment... */
		for (i = 0; i < cnt; i++)
			port->sink_caps[i] = le32_to_cpu(msg->payload[i]);

		port->nr_sink_caps = cnt;
		break;
	default:
		break;
	}
}

static void tcpm_pd_ctrl_request(struct tcpm_port *port,
				 const struct pd_message *msg)
{
	enum pd_ctrl_msg_type type = pd_header_type_le(msg->header);
	enum tcpm_state next_state;

	switch (type) {
	case PD_CTRL_GOOD_CRC:
	case PD_CTRL_PING:
		break;
	case PD_CTRL_GET_SOURCE_CAP:
		switch (port->state) {
		case SRC_READY:
		case SNK_READY:
			tcpm_queue_message(port, PD_MSG_DATA_SOURCE_CAP);
			break;
		default:
			tcpm_queue_message(port, PD_MSG_CTRL_REJECT);
			break;
		}
		break;
	case PD_CTRL_GET_SINK_CAP:
		switch (port->state) {
		case SRC_READY:
		case SNK_READY:
			tcpm_queue_message(port, PD_MSG_DATA_SINK_CAP);
			break;
		default:
			tcpm_queue_message(port, PD_MSG_CTRL_REJECT);
			break;
		}
		break;
	case PD_CTRL_GOTO_MIN:
		break;
	case PD_CTRL_PS_RDY:
		switch (port->state) {
		case SNK_TRANSITION_SINK:
			if (port->vbus_present) {
				tcpm_set_current_limit(port,
						       port->req_current_limit,
						       port->req_supply_voltage);
				port->explicit_contract = true;
				tcpm_set_state(port, SNK_READY, 0);
			} else {
				/*
				 * Seen after power swap. Keep waiting for VBUS
				 * in a transitional state.
				 */
				tcpm_set_state(port,
					       SNK_TRANSITION_SINK_VBUS, 0);
			}
			break;
		default:
			break;
		}
		break;
	case PD_CTRL_REJECT:
	case PD_CTRL_WAIT:
	case PD_CTRL_NOT_SUPP:
		switch (port->state) {
		case SNK_NEGOTIATE_CAPABILITIES:
			/* USB PD specification, Figure 8-43 */
			if (port->explicit_contract)
				next_state = SNK_READY;
			else
				next_state = SNK_WAIT_CAPABILITIES;

			tcpm_set_state(port, next_state, 0);
			break;
		case SNK_NEGOTIATE_PPS_CAPABILITIES:
			/* Revert data back from any requested PPS updates */
			port->pps_data.req_out_volt = port->supply_voltage;
			port->pps_data.req_op_curr = port->current_limit;
			port->pps_status = (type == PD_CTRL_WAIT ?
					    -EAGAIN : -EOPNOTSUPP);
			tcpm_set_state(port, SNK_READY, 0);
			break;
		default:
			break;
		}
		break;
	case PD_CTRL_ACCEPT:
		switch (port->state) {
		case SNK_NEGOTIATE_CAPABILITIES:
			port->pps_data.active = false;
			tcpm_set_state(port, SNK_TRANSITION_SINK, 0);
			break;
		case SNK_NEGOTIATE_PPS_CAPABILITIES:
			port->pps_data.active = true;
			/* ???? */
			port->pps_data.min_volt = port->pps_data.req_min_volt;
			port->pps_data.max_volt = port->pps_data.req_max_volt;
			port->pps_data.max_curr = port->pps_data.req_max_curr;
			port->req_supply_voltage = port->pps_data.req_out_volt;
			port->req_current_limit = port->pps_data.req_op_curr;
			tcpm_set_state(port, SNK_TRANSITION_SINK, 0);
			break;
		case SOFT_RESET_SEND:
			port->message_id = 0;
			port->rx_msgid = -1;
			if (port->pwr_role == TYPEC_SOURCE)
				next_state = SRC_SEND_CAPABILITIES;
			else
				next_state = SNK_WAIT_CAPABILITIES;
			tcpm_set_state(port, next_state, 0);
			break;
		default:
			break;
		}
		break;
	case PD_CTRL_SOFT_RESET:
		tcpm_set_state(port, SOFT_RESET, 0);
		break;
	case PD_CTRL_DR_SWAP:
		if (port->port_type != TYPEC_PORT_DRP) {
			tcpm_queue_message(port, PD_MSG_CTRL_REJECT);
			break;
		}
		/*
		 * XXX
		 * 6.3.9: If an alternate mode is active, a request to swap
		 * alternate modes shall trigger a port reset.
		 */
		switch (port->state) {
		case SRC_READY:
		case SNK_READY:
#if 0
			if (port->vdm_sm_running) {
				tcpm_queue_message(port, PD_MSG_CTRL_WAIT);
				break;
			}
#endif
			tcpm_set_state(port, DR_SWAP_ACCEPT, 0);
			break;
		default:
			tcpm_queue_message(port, PD_MSG_CTRL_WAIT);
			break;
		}
		break;
	case PD_CTRL_PR_SWAP:
	case PD_CTRL_VCONN_SWAP:
	case PD_CTRL_GET_SOURCE_CAP_EXT:
	case PD_CTRL_GET_STATUS:
	case PD_CTRL_FR_SWAP:
	case PD_CTRL_GET_PPS_STATUS:
	case PD_CTRL_GET_COUNTRY_CODES:
		/* Currently not supported */
		printf("Currently not supported type %#x \n", type);
		tcpm_queue_message(port, PD_MSG_CTRL_NOT_SUPP);
		break;
	default:
		printf("Unrecognized ctrl message type %#x\n", type);
		break;
	}
}

#if 0
static void tcpm_pd_ext_msg_request(struct tcpm_port *port,
				    const struct pd_message *msg)
{
	enum pd_ext_msg_type type = pd_header_type_le(msg->header);
	unsigned int data_size = pd_ext_header_data_size_le(msg->ext_msg.header);

	if (!(le16_to_cpu(msg->ext_msg.header) & PD_EXT_HDR_CHUNKED)) {
		tcpm_pd_handle_msg(port, PD_MSG_CTRL_NOT_SUPP, NONE_AMS);
		printf("Unchunked extended messages unsupported\n");
		return;
	}

	if (data_size > PD_EXT_MAX_CHUNK_DATA) {
		tcpm_pd_handle_state(port, CHUNK_NOT_SUPP, NONE_AMS, PD_T_CHUNK_NOT_SUPP);
		printf("Chunk handling not yet supported\n");
		return;
	}

	switch (type) {
	case PD_EXT_STATUS:
	case PD_EXT_PPS_STATUS:
			tcpm_set_state(port, ready_state(port), 0);
		}
		break;
	case PD_EXT_SOURCE_CAP_EXT:
	case PD_EXT_GET_BATT_CAP:
	case PD_EXT_GET_BATT_STATUS:
	case PD_EXT_BATT_CAP:
	case PD_EXT_GET_MANUFACTURER_INFO:
	case PD_EXT_MANUFACTURER_INFO:
	case PD_EXT_SECURITY_REQUEST:
	case PD_EXT_SECURITY_RESPONSE:
	case PD_EXT_FW_UPDATE_REQUEST:
	case PD_EXT_FW_UPDATE_RESPONSE:
	case PD_EXT_COUNTRY_INFO:
	case PD_EXT_COUNTRY_CODES:
		tcpm_pd_handle_msg(port, PD_MSG_CTRL_NOT_SUPP, NONE_AMS);
		break;
	default:
		tcpm_pd_handle_msg(port, PD_MSG_CTRL_NOT_SUPP, NONE_AMS);
		printf("Unrecognized extended message type %#x\n", type);
		break;
	}
}
#endif

static void tcpm_pd_rx_handler(struct tcpm_port *port,
			       struct pd_rx_event *event)
{
	const struct pd_message *msg = &event->msg;
	unsigned int cnt = pd_header_cnt_le(msg->header);

	debug("PD RX, header: %#x [%d]\n", le16_to_cpu(msg->header),
	      port->attached);

	if (port->attached) {
		enum pd_ctrl_msg_type type = pd_header_type_le(msg->header);
		unsigned int msgid = pd_header_msgid_le(msg->header);

		/*
		 * USB PD standard, 6.6.1.2:
		 * "... if MessageID value in a received Message is the
		 * same as the stored value, the receiver shall return a
		 * GoodCRC Message with that MessageID value and drop
		 * the Message (this is a retry of an already received
		 * Message). Note: this shall not apply to the Soft_Reset
		 * Message which always has a MessageID value of zero."
		 */
		if (msgid == port->rx_msgid && type != PD_CTRL_SOFT_RESET)
			goto done;
		port->rx_msgid = msgid;

		/*
		 * If both ends believe to be DFP/host, we have a data role
		 * mismatch.
		 */
		if (!!(le16_to_cpu(msg->header) & PD_HEADER_DATA_ROLE) ==
		    (port->data_role == TYPEC_HOST)) {
			printf("Data role mismatch, initiating error recovery\n");
			tcpm_set_state(port, ERROR_RECOVERY, 0);
		} else {
			if (cnt)
				tcpm_pd_data_request(port, msg);
			else
				tcpm_pd_ctrl_request(port, msg);
		}
	}

done:
	kfree(event);
}

void tcpm_pd_receive(struct tcpm_port *port, const struct pd_message *msg)
{
	struct pd_rx_event *event;

	port->poll_event_cnt = 0;
	event = kzalloc(sizeof(*event), GFP_ATOMIC);
	if (!event)
		return;

	event->port = port;
	memcpy(&event->msg, msg, sizeof(*msg));
	tcpm_pd_rx_handler(port, event);
}
EXPORT_SYMBOL_GPL(tcpm_pd_receive);

static int tcpm_pd_send_control(struct tcpm_port *port,
				enum pd_ctrl_msg_type type)
{
	struct pd_message msg;

	memset(&msg, 0, sizeof(msg));
	msg.header = PD_HEADER_LE(type, port->pwr_role,
				  port->data_role,
				  port->negotiated_rev,
				  port->message_id, 0);

	return tcpm_pd_transmit(port, TCPC_TX_SOP, &msg);
}

/*
 * Send queued message without affecting state.
 * Return true if state machine should go back to sleep,
 * false otherwise.
 */
static bool tcpm_send_queued_message(struct tcpm_port *port)
{
	enum pd_msg_request queued_message;

	do {
		queued_message = port->queued_message;
		port->queued_message = PD_MSG_NONE;

		switch (queued_message) {
		case PD_MSG_CTRL_WAIT:
			tcpm_pd_send_control(port, PD_CTRL_WAIT);
			break;
		case PD_MSG_CTRL_REJECT:
			tcpm_pd_send_control(port, PD_CTRL_REJECT);
			break;
		case PD_MSG_CTRL_NOT_SUPP:
			tcpm_pd_send_control(port, PD_CTRL_NOT_SUPP);
			break;
		case PD_MSG_DATA_SINK_CAP:
			tcpm_pd_send_sink_caps(port);
			break;
		case PD_MSG_DATA_SOURCE_CAP:
			tcpm_pd_send_source_caps(port);
			break;
		default:
			break;
		}
	} while (port->queued_message != PD_MSG_NONE);

#if 0
	/* ??? */
	if (port->delayed_state != INVALID_STATE) {
		if (ktime_after(port->delayed_runtime, ktime_get())) {
			mod_tcpm_delayed_work(port, ktime_to_ms(ktime_sub(port->delayed_runtime,
									  ktime_get())));
			return true;
		}
		port->delayed_state = INVALID_STATE;
	}
#endif
	return false;
}

static int tcpm_pd_check_request(struct tcpm_port *port)
{
	u32 pdo, rdo = port->sink_request;
	unsigned int max, op, pdo_max, index;
	enum pd_pdo_type type;

	index = rdo_index(rdo);
	if (!index || index > port->nr_src_pdo)
		return -EINVAL;

	pdo = port->src_pdo[index - 1];
	type = pdo_type(pdo);
	switch (type) {
	case PDO_TYPE_FIXED:
	case PDO_TYPE_VAR:
		max = rdo_max_current(rdo);
		op = rdo_op_current(rdo);
		pdo_max = pdo_max_current(pdo);

		if (op > pdo_max)
			return -EINVAL;
		if (max > pdo_max && !(rdo & RDO_CAP_MISMATCH))
			return -EINVAL;

		if (type == PDO_TYPE_FIXED)
			debug("Requested %u mV, %u mA for %u / %u mA\n",
			      pdo_fixed_voltage(pdo), pdo_max, op, max);
		else
			debug("Requested %u -> %u mV, %u mA for %u / %u mA\n",
			      pdo_min_voltage(pdo), pdo_max_voltage(pdo),
			      pdo_max, op, max);
		break;
	case PDO_TYPE_BATT:
		max = rdo_max_power(rdo);
		op = rdo_op_power(rdo);
		pdo_max = pdo_max_power(pdo);

		if (op > pdo_max)
			return -EINVAL;
		if (max > pdo_max && !(rdo & RDO_CAP_MISMATCH))
			return -EINVAL;
		printf("Requested %u -> %u mV, %u mW for %u / %u mW\n",
		       pdo_min_voltage(pdo), pdo_max_voltage(pdo),
		       pdo_max, op, max);
		break;
	default:
		return -EINVAL;
	}

	port->op_vsafe5v = index == 1;

	return 0;
}

#define min_power(x, y) min(pdo_max_power(x), pdo_max_power(y))
#define min_current(x, y) min(pdo_max_current(x), pdo_max_current(y))

static int tcpm_pd_select_pdo(struct tcpm_port *port, int *sink_pdo,
			      int *src_pdo)
{
	unsigned int i, j, max_src_mv = 0, min_src_mv = 0, max_mw = 0,
		     max_mv = 0, src_mw = 0, src_ma = 0, max_snk_mv = 0,
		     min_snk_mv = 0;
	int ret = -EINVAL;

	port->pps_data.supported = false;
	port->usb_type = POWER_SUPPLY_USB_TYPE_PD;

	/*
	 * Select the source PDO providing the most power which has a
	 * matchig sink cap.
	 */
	for (i = 0; i < port->nr_source_caps; i++) {
		u32 pdo = port->source_caps[i];
		enum pd_pdo_type type = pdo_type(pdo);

		switch (type) {
		case PDO_TYPE_FIXED:
			max_src_mv = pdo_fixed_voltage(pdo);
			min_src_mv = max_src_mv;
			break;
		case PDO_TYPE_BATT:
		case PDO_TYPE_VAR:
			max_src_mv = pdo_max_voltage(pdo);
			min_src_mv = pdo_min_voltage(pdo);
			break;
		case PDO_TYPE_APDO:
			if (pdo_apdo_type(pdo) == APDO_TYPE_PPS) {
				port->pps_data.supported = true;
				port->usb_type =
					POWER_SUPPLY_USB_TYPE_PD_PPS;
			}
			continue;
		default:
			printf("Invalid source PDO type, ignoring\n");
			continue;
		}

		switch (type) {
		case PDO_TYPE_FIXED:
		case PDO_TYPE_VAR:
			src_ma = pdo_max_current(pdo);
			src_mw = src_ma * min_src_mv / 1000;
			break;
		case PDO_TYPE_BATT:
			src_mw = pdo_max_power(pdo);
			break;
		case PDO_TYPE_APDO:
			continue;
		default:
			printf("Invalid source PDO type, ignoring\n");
			continue;
		}

		for (j = 0; j < port->nr_snk_pdo; j++) {
			pdo = port->snk_pdo[j];

			switch (pdo_type(pdo)) {
			case PDO_TYPE_FIXED:
				max_snk_mv = pdo_fixed_voltage(pdo);
				min_snk_mv = max_snk_mv;
				break;
			case PDO_TYPE_BATT:
			case PDO_TYPE_VAR:
				max_snk_mv = pdo_max_voltage(pdo);
				min_snk_mv = pdo_min_voltage(pdo);
				break;
			case PDO_TYPE_APDO:
				continue;
			default:
				printf("Invalid sink PDO type, ignoring\n");
				continue;
			}

			if (max_src_mv <= max_snk_mv &&
				min_src_mv >= min_snk_mv) {
				/* Prefer higher voltages if available */
				if ((src_mw == max_mw && min_src_mv > max_mv) ||
							src_mw > max_mw) {
					*src_pdo = i;
					*sink_pdo = j;
					max_mw = src_mw;
					max_mv = min_src_mv;
					ret = 0;
				}
			}
		}
	}

	return ret;
}

#define min_pps_apdo_current(x, y)	\
	min(pdo_pps_apdo_max_current(x), pdo_pps_apdo_max_current(y))

static unsigned int tcpm_pd_select_pps_apdo(struct tcpm_port *port)
{
	unsigned int i, j, max_mw = 0, max_mv = 0;
	unsigned int min_src_mv, max_src_mv, src_ma, src_mw;
	unsigned int min_snk_mv, max_snk_mv;
	unsigned int max_op_mv;
	u32 pdo, src, snk;
	unsigned int src_pdo = 0, snk_pdo = 0;

	/*
	 * Select the source PPS APDO providing the most power while staying
	 * within the board's limits. We skip the first PDO as this is always
	 * 5V 3A.
	 */
	for (i = 1; i < port->nr_source_caps; ++i) {
		pdo = port->source_caps[i];

		switch (pdo_type(pdo)) {
		case PDO_TYPE_APDO:
			if (pdo_apdo_type(pdo) != APDO_TYPE_PPS) {
				printf("Not PPS APDO (source), ignoring\n");
				continue;
			}

			min_src_mv = pdo_pps_apdo_min_voltage(pdo);
			max_src_mv = pdo_pps_apdo_max_voltage(pdo);
			src_ma = pdo_pps_apdo_max_current(pdo);
			src_mw = (src_ma * max_src_mv) / 1000;

			/*
			 * Now search through the sink PDOs to find a matching
			 * PPS APDO. Again skip the first sink PDO as this will
			 * always be 5V 3A.
			 */
			for (j = 1; j < port->nr_snk_pdo; j++) {
				pdo = port->snk_pdo[j];

				switch (pdo_type(pdo)) {
				case PDO_TYPE_APDO:
					if (pdo_apdo_type(pdo) != APDO_TYPE_PPS) {
						printf("Not PPS APDO (sink), ignoring\n");
						continue;
					}

					min_snk_mv =
						pdo_pps_apdo_min_voltage(pdo);
					max_snk_mv =
						pdo_pps_apdo_max_voltage(pdo);
					break;
				default:
					printf("Not APDO type (sink), ignoring\n");
					continue;
				}

				if (min_src_mv <= max_snk_mv &&
				    max_src_mv >= min_snk_mv) {
					max_op_mv = min(max_src_mv, max_snk_mv);
					src_mw = (max_op_mv * src_ma) / 1000;
					/* Prefer higher voltages if available */
					if ((src_mw == max_mw &&
					     max_op_mv > max_mv) ||
					    src_mw > max_mw) {
						src_pdo = i;
						snk_pdo = j;
						max_mw = src_mw;
						max_mv = max_op_mv;
					}
				}
			}

			break;
		default:
			printf("Not APDO type (source), ignoring\n");
			continue;
		}
	}

	if (src_pdo) {
		src = port->source_caps[src_pdo];
		snk = port->snk_pdo[snk_pdo];

		port->pps_data.req_min_volt = max(pdo_pps_apdo_min_voltage(src),
						  pdo_pps_apdo_min_voltage(snk));
		port->pps_data.req_max_volt = min(pdo_pps_apdo_max_voltage(src),
						  pdo_pps_apdo_max_voltage(snk));
		port->pps_data.req_max_curr = min_pps_apdo_current(src, snk);
		port->pps_data.req_out_volt = min(port->pps_data.req_max_volt,
						  max(port->pps_data.req_min_volt,
						      port->pps_data.req_out_volt));
		port->pps_data.req_op_curr = min(port->pps_data.req_max_curr,
						 port->pps_data.req_op_curr);
	}

	return src_pdo;
}

static int tcpm_pd_build_request(struct tcpm_port *port, u32 *rdo)
{
	unsigned int mv, ma, mw, flags;
	unsigned int max_ma, max_mw;
	enum pd_pdo_type type;
	u32 pdo, matching_snk_pdo;
	int src_pdo_index = 0;
	int snk_pdo_index = 0;
	int ret;

	ret = tcpm_pd_select_pdo(port, &snk_pdo_index, &src_pdo_index);
	if (ret < 0)
		return ret;

	pdo = port->source_caps[src_pdo_index];
	matching_snk_pdo = port->snk_pdo[snk_pdo_index];
	type = pdo_type(pdo);

	switch (type) {
	case PDO_TYPE_FIXED:
		mv = pdo_fixed_voltage(pdo);
		break;
	case PDO_TYPE_BATT:
	case PDO_TYPE_VAR:
		mv = pdo_min_voltage(pdo);
		break;
	default:
		printf("Invalid PDO selected!\n");
		return -EINVAL;
	}

	/* Select maximum available current within the sink pdo's limit */
	if (type == PDO_TYPE_BATT) {
		mw = min_power(pdo, matching_snk_pdo);
		ma = 1000 * mw / mv;
	} else {
		ma = min_current(pdo, matching_snk_pdo);
		mw = ma * mv / 1000;
	}

	flags = RDO_USB_COMM | RDO_NO_SUSPEND;

	/* Set mismatch bit if offered power is less than operating power */
	max_ma = ma;
	max_mw = mw;
	if (mw < port->operating_snk_mw) {
		flags |= RDO_CAP_MISMATCH;
		if (type == PDO_TYPE_BATT &&
		    (pdo_max_power(matching_snk_pdo) > pdo_max_power(pdo)))
			max_mw = pdo_max_power(matching_snk_pdo);
		else if (pdo_max_current(matching_snk_pdo) >
			 pdo_max_current(pdo))
			max_ma = pdo_max_current(matching_snk_pdo);
	}

	debug("cc=%d cc1=%d cc2=%d vbus=%d vconn=%s polarity=%d\n",
	      port->cc_req, port->cc1, port->cc2, port->vbus_source,
	      port->vconn_role == TYPEC_SOURCE ? "source" : "sink",
	      port->polarity);

	if (type == PDO_TYPE_BATT) {
		*rdo = RDO_BATT(src_pdo_index + 1, mw, max_mw, flags);

		printf("Requesting PDO %d: %u mV, %u mW%s\n",
		       src_pdo_index, mv, mw,
		       flags & RDO_CAP_MISMATCH ? " [mismatch]" : "");
	} else {
		*rdo = RDO_FIXED(src_pdo_index + 1, ma, max_ma, flags);

		printf("Requesting PDO %d: %u mV, %u mA%s\n",
			src_pdo_index, mv, ma,
			flags & RDO_CAP_MISMATCH ? " [mismatch]" : "");
	}

	port->req_current_limit = ma;
	port->req_supply_voltage = mv;

	return 0;
}

static int tcpm_pd_send_request(struct tcpm_port *port)
{
	struct pd_message msg;
	int ret;
	u32 rdo;

	ret = tcpm_pd_build_request(port, &rdo);
	if (ret < 0)
		return ret;

	memset(&msg, 0, sizeof(msg));
	msg.header = PD_HEADER_LE(PD_DATA_REQUEST,
				  port->pwr_role,
				  port->data_role,
				  port->negotiated_rev,
				  port->message_id, 1);
	msg.payload[0] = cpu_to_le32(rdo);

	return tcpm_pd_transmit(port, TCPC_TX_SOP, &msg);
}

static int tcpm_pd_build_pps_request(struct tcpm_port *port, u32 *rdo)
{
	unsigned int out_mv, op_ma, op_mw, max_mv, max_ma, flags;
	enum pd_pdo_type type;
	unsigned int src_pdo_index;
	u32 pdo;

	src_pdo_index = tcpm_pd_select_pps_apdo(port);
	if (!src_pdo_index)
		return -EOPNOTSUPP;

	pdo = port->source_caps[src_pdo_index];
	type = pdo_type(pdo);

	switch (type) {
	case PDO_TYPE_APDO:
		if (pdo_apdo_type(pdo) != APDO_TYPE_PPS) {
			printf("Invalid APDO selected!\n");
			return -EINVAL;
		}
		max_mv = port->pps_data.req_max_volt;
		max_ma = port->pps_data.req_max_curr;
		out_mv = port->pps_data.req_out_volt;
		op_ma = port->pps_data.req_op_curr;
		break;
	default:
		printf("Invalid PDO selected!\n");
		return -EINVAL;
	}

	flags = RDO_USB_COMM | RDO_NO_SUSPEND;

	op_mw = (op_ma * out_mv) / 1000;
	if (op_mw < port->operating_snk_mw) {
		/*
		 * Try raising current to meet power needs. If that's not enough
		 * then try upping the voltage. If that's still not enough
		 * then we've obviously chosen a PPS APDO which really isn't
		 * suitable so abandon ship.
		 */
		op_ma = (port->operating_snk_mw * 1000) / out_mv;
		if ((port->operating_snk_mw * 1000) % out_mv)
			++op_ma;
		op_ma += RDO_PROG_CURR_MA_STEP - (op_ma % RDO_PROG_CURR_MA_STEP);

		if (op_ma > max_ma) {
			op_ma = max_ma;
			out_mv = (port->operating_snk_mw * 1000) / op_ma;
			if ((port->operating_snk_mw * 1000) % op_ma)
				++out_mv;
			out_mv += RDO_PROG_VOLT_MV_STEP -
				  (out_mv % RDO_PROG_VOLT_MV_STEP);

			if (out_mv > max_mv) {
				printf("Invalid PPS APDO selected!\n");
				return -EINVAL;
			}
		}
	}

	debug("cc=%d cc1=%d cc2=%d vbus=%d vconn=%s polarity=%d\n",
	      port->cc_req, port->cc1, port->cc2, port->vbus_source,
	      port->vconn_role == TYPEC_SOURCE ? "source" : "sink",
	      port->polarity);

	*rdo = RDO_PROG(src_pdo_index + 1, out_mv, op_ma, flags);

	printf("Requesting APDO %d: %u mV, %u mA\n",
	       src_pdo_index, out_mv, op_ma);

	port->pps_data.req_op_curr = op_ma;
	port->pps_data.req_out_volt = out_mv;

	return 0;
}

static int tcpm_pd_send_pps_request(struct tcpm_port *port)
{
	struct pd_message msg;
	int ret;
	u32 rdo;

	ret = tcpm_pd_build_pps_request(port, &rdo);
	if (ret < 0)
		return ret;

	memset(&msg, 0, sizeof(msg));
	msg.header = PD_HEADER_LE(PD_DATA_REQUEST,
				  port->pwr_role,
				  port->data_role,
				  port->negotiated_rev,
				  port->message_id, 1);
	msg.payload[0] = cpu_to_le32(rdo);

	return tcpm_pd_transmit(port, TCPC_TX_SOP, &msg);
}

static int tcpm_set_vbus(struct tcpm_port *port, bool enable)
{
	int ret;

	if (enable && port->vbus_charge)
		return -EINVAL;

	debug("vbus = %d charge = %d\n", enable, port->vbus_charge);

	ret = port->tcpc->set_vbus(port->tcpc, enable, port->vbus_charge);
	if (ret < 0)
		return ret;

	port->vbus_source = enable;
	return 0;
}

static int tcpm_set_charge(struct tcpm_port *port, bool charge)
{
	int ret;

	if (charge && port->vbus_source)
		return -EINVAL;

	if (charge != port->vbus_charge) {
		debug("vbus = %d charge = %d\n", port->vbus_source, charge);
		ret = port->tcpc->set_vbus(port->tcpc, port->vbus_source,
					   charge);
		if (ret < 0)
			return ret;
	}
	port->vbus_charge = charge;
	return 0;
}

static bool tcpm_start_toggling(struct tcpm_port *port, enum typec_cc_status cc)
{
	int ret;

	if (!port->tcpc->start_toggling)
		return false;

	printf("Start toggling\n");
	ret = port->tcpc->start_toggling(port->tcpc, port->port_type, cc);
	return ret == 0;
}

static int tcpm_init_vbus(struct tcpm_port *port)
{
	int ret;

	ret = port->tcpc->set_vbus(port->tcpc, false, false);
	port->vbus_source = false;
	port->vbus_charge = false;
	return ret;
}

static int tcpm_init_vconn(struct tcpm_port *port)
{
	int ret;

	ret = port->tcpc->set_vconn(port->tcpc, false);
	port->vconn_role = TYPEC_SINK;
	return ret;
}

static void tcpm_typec_connect(struct tcpm_port *port)
{
	if (!port->connected) {
		port->connected = true;
	}
}

static int tcpm_src_attach(struct tcpm_port *port)
{
	enum typec_cc_polarity polarity =
				port->cc2 == TYPEC_CC_RD ? TYPEC_POLARITY_CC2
							 : TYPEC_POLARITY_CC1;
	int ret;

	if (port->attached)
		return 0;

	ret = tcpm_set_polarity(port, polarity);
	if (ret < 0)
		return ret;

	ret = tcpm_set_roles(port, true, TYPEC_SOURCE, TYPEC_HOST);
	if (ret < 0)
		return ret;

	ret = port->tcpc->set_pd_rx(port->tcpc, true);
	if (ret < 0)
		goto out_disable_mux;

	/*
	 * USB Type-C specification, version 1.2,
	 * chapter 4.5.2.2.8.1 (Attached.SRC Requirements)
	 * Enable VCONN only if the non-RD port is set to RA.
	 */
	if ((polarity == TYPEC_POLARITY_CC1 && port->cc2 == TYPEC_CC_RA) ||
	    (polarity == TYPEC_POLARITY_CC2 && port->cc1 == TYPEC_CC_RA)) {
		ret = tcpm_set_vconn(port, true);
		if (ret < 0)
			goto out_disable_pd;
	}

	ret = tcpm_set_vbus(port, true);
	if (ret < 0)
		goto out_disable_vconn;

	port->pd_capable = false;

	port->partner = NULL;

	port->attached = true;
	port->debouncing = false;
	//port->send_discover = true;

	return 0;

out_disable_vconn:
	tcpm_set_vconn(port, false);
out_disable_pd:
	port->tcpc->set_pd_rx(port->tcpc, false);
out_disable_mux:
	printf("CC connected in %s as DFP\n",
		polarity ? "CC2" : "CC1");
	return 0;
}

static void tcpm_typec_disconnect(struct tcpm_port *port)
{
	if (port->connected) {
		port->partner = NULL;
		port->connected = false;
	}
}

static void tcpm_reset_port(struct tcpm_port *port)
{
	tcpm_timer_uninit(port);
	tcpm_typec_disconnect(port);
	port->poll_event_cnt = 0;
	port->wait_dr_swap_Message = false;
	port->attached = false;
	port->pd_capable = false;
	port->pps_data.supported = false;

	/*
	 * First Rx ID should be 0; set this to a sentinel of -1 so that
	 * we can check tcpm_pd_rx_handler() if we had seen it before.
	 */
	port->rx_msgid = -1;

	port->tcpc->set_pd_rx(port->tcpc, false);
	tcpm_init_vbus(port);	/* also disables charging */
	tcpm_init_vconn(port);
	tcpm_set_current_limit(port, 0, 0);
	tcpm_set_polarity(port, TYPEC_POLARITY_CC1);
	tcpm_set_attached_state(port, false);
	port->usb_type = POWER_SUPPLY_USB_TYPE_C;
	port->nr_sink_caps = 0;
	port->sink_cap_done = false;
}

static void tcpm_detach(struct tcpm_port *port)
{
	if (tcpm_port_is_disconnected(port))
		port->hard_reset_count = 0;

	if (!port->attached)
		return;

	tcpm_reset_port(port);
}

static void tcpm_src_detach(struct tcpm_port *port)
{
	tcpm_detach(port);
}

static int tcpm_snk_attach(struct tcpm_port *port)
{
	int ret;

	if (port->attached)
		return 0;

	ret = tcpm_set_polarity(port, port->cc2 != TYPEC_CC_OPEN ?
				TYPEC_POLARITY_CC2 : TYPEC_POLARITY_CC1);
	if (ret < 0)
		return ret;

	ret = tcpm_set_roles(port, true, TYPEC_SINK, TYPEC_DEVICE);
	if (ret < 0)
		return ret;

	port->pd_capable = false;

	port->partner = NULL;

	port->attached = true;
	port->debouncing = false;
	printf("CC connected in %s as UFP\n",
		port->cc1 != TYPEC_CC_OPEN ? "CC1" : "CC2");

	return 0;
}

static void tcpm_snk_detach(struct tcpm_port *port)
{
	tcpm_detach(port);
}

static int tcpm_acc_attach(struct tcpm_port *port)
{
	int ret;

	if (port->attached)
		return 0;

	ret = tcpm_set_roles(port, true, TYPEC_SOURCE, TYPEC_HOST);
	if (ret < 0)
		return ret;

	port->partner = NULL;

	tcpm_typec_connect(port);

	port->attached = true;

	dev_info(port->dev, "CC connected as Audio Accessory\n");

	return 0;
}

static void tcpm_acc_detach(struct tcpm_port *port)
{
	tcpm_detach(port);
}

static inline enum tcpm_state hard_reset_state(struct tcpm_port *port)
{
	if (port->hard_reset_count < PD_N_HARD_RESET_COUNT)
		return HARD_RESET_SEND;
	if (port->pd_capable)
		return ERROR_RECOVERY;
	if (port->pwr_role == TYPEC_SOURCE)
		return SRC_UNATTACHED;
	if (port->state == SNK_WAIT_CAPABILITIES)
		return SNK_READY;
	return SNK_UNATTACHED;
}

static inline enum tcpm_state unattached_state(struct tcpm_port *port)
{
	if (port->port_type == TYPEC_PORT_DRP) {
		if (port->pwr_role == TYPEC_SOURCE)
			return SRC_UNATTACHED;
		else
			return SNK_UNATTACHED;
	} else if (port->port_type == TYPEC_PORT_SRC) {
		return SRC_UNATTACHED;
	}

	return SNK_UNATTACHED;
}

bool tcpm_is_toggling(struct tcpm_port *port)
{
	if (port->port_type == TYPEC_PORT_DRP)
		return port->state == SRC_UNATTACHED || port->state == SNK_UNATTACHED ||
			port->state == TOGGLING;

	return false;
}
EXPORT_SYMBOL_GPL(tcpm_is_toggling);

static void run_state_machine(struct tcpm_port *port)
{
	int ret;

	port->enter_state = port->state;
	switch (port->state) {
	case TOGGLING:
		break;
	/* SRC states */
	case SRC_UNATTACHED:
		tcpm_src_detach(port);
		if (tcpm_start_toggling(port, tcpm_rp_cc(port))) {
			tcpm_set_state(port, TOGGLING, 0);
			break;
		}
		tcpm_set_cc(port, tcpm_rp_cc(port));
		if (port->port_type == TYPEC_PORT_DRP)
			tcpm_set_state(port, SNK_UNATTACHED, PD_T_DRP_SNK);
		break;
	case SRC_ATTACH_WAIT:
		if (tcpm_port_is_debug(port))
			tcpm_set_state(port, DEBUG_ACC_ATTACHED,
				       PD_T_CC_DEBOUNCE);
		else if (tcpm_port_is_audio(port))
			tcpm_set_state(port, AUDIO_ACC_ATTACHED,
				       PD_T_CC_DEBOUNCE);
		else if (tcpm_port_is_source(port))
			tcpm_set_state(port, SRC_ATTACHED, PD_T_CC_DEBOUNCE);
		break;

	case SRC_ATTACHED:
		ret = tcpm_src_attach(port);
		/*
		 * Currently, vbus control is not implemented,
		 * and the SRC detection process cannot be fully implemented.
		 */
		tcpm_set_state(port, SRC_READY, 0);
#if 0
		tcpm_set_state(port, SRC_UNATTACHED,
			       ret < 0 ? 0 : PD_T_PS_SOURCE_ON);
#endif
		break;
	case SRC_STARTUP:
		port->caps_count = 0;
		port->negotiated_rev = PD_MAX_REV;
		port->message_id = 0;
		port->rx_msgid = -1;
		port->explicit_contract = false;
		tcpm_set_state(port, SRC_SEND_CAPABILITIES, 0);
		break;
	case SRC_SEND_CAPABILITIES:
		port->caps_count++;
		if (port->caps_count > PD_N_CAPS_COUNT) {
			tcpm_set_state(port, SRC_READY, 0);
			break;
		}
		ret = tcpm_pd_send_source_caps(port);
		if (ret < 0) {
			tcpm_set_state(port, SRC_SEND_CAPABILITIES,
				       PD_T_SEND_SOURCE_CAP);
		} else {
			/*
			 * Per standard, we should clear the reset counter here.
			 * However, that can result in state machine hang-ups.
			 * Reset it only in READY state to improve stability.
			 */
			/* port->hard_reset_count = 0; */
			port->caps_count = 0;
			port->pd_capable = true;
			tcpm_set_state_cond(port, SRC_SEND_CAPABILITIES_TIMEOUT,
					    PD_T_SEND_SOURCE_CAP);
		}
		break;
	case SRC_SEND_CAPABILITIES_TIMEOUT:
		/*
		 * Error recovery for a PD_DATA_SOURCE_CAP reply timeout.
		 *
		 * PD 2.0 sinks are supposed to accept src-capabilities with a
		 * 3.0 header and simply ignore any src PDOs which the sink does
		 * not understand such as PPS but some 2.0 sinks instead ignore
		 * the entire PD_DATA_SOURCE_CAP message, causing contract
		 * negotiation to fail.
		 *
		 * After PD_N_HARD_RESET_COUNT hard-reset attempts, we try
		 * sending src-capabilities with a lower PD revision to
		 * make these broken sinks work.
		 */
		if (port->hard_reset_count < PD_N_HARD_RESET_COUNT) {
			tcpm_set_state(port, HARD_RESET_SEND, 0);
		} else if (port->negotiated_rev > PD_REV20) {
			port->negotiated_rev--;
			port->hard_reset_count = 0;
			tcpm_set_state(port, SRC_SEND_CAPABILITIES, 0);
		} else {
			tcpm_set_state(port, hard_reset_state(port), 0);
		}
		break;
	case SRC_NEGOTIATE_CAPABILITIES:
		ret = tcpm_pd_check_request(port);
		if (ret < 0) {
			tcpm_pd_send_control(port, PD_CTRL_REJECT);
			if (!port->explicit_contract) {
				tcpm_set_state(port,
					       SRC_WAIT_NEW_CAPABILITIES, 0);
			} else {
				tcpm_set_state(port, SRC_READY, 0);
			}
		} else {
			tcpm_pd_send_control(port, PD_CTRL_ACCEPT);
			tcpm_set_state(port, SRC_TRANSITION_SUPPLY,
				       PD_T_SRC_TRANSITION);
		}
		break;
	case SRC_TRANSITION_SUPPLY:
		/* XXX: regulator_set_voltage(vbus, ...) */
		tcpm_pd_send_control(port, PD_CTRL_PS_RDY);
		port->explicit_contract = true;
		tcpm_set_state_cond(port, SRC_READY, 0);
		break;
	case SRC_READY:
#if 1
		port->hard_reset_count = 0;
#endif
		port->try_src_count = 0;

		tcpm_typec_connect(port);
		break;
	case SRC_WAIT_NEW_CAPABILITIES:
		/* Nothing to do... */
		break;

	/* SNK states */
	case SNK_UNATTACHED:
		tcpm_snk_detach(port);
		if (tcpm_start_toggling(port, TYPEC_CC_RD)) {
			tcpm_set_state(port, TOGGLING, 0);
			break;
		}
		tcpm_set_cc(port, TYPEC_CC_RD);
		if (port->port_type == TYPEC_PORT_DRP)
			tcpm_set_state(port, SRC_UNATTACHED, PD_T_DRP_SRC);
		break;
	case SNK_ATTACH_WAIT:
		if ((port->cc1 == TYPEC_CC_OPEN &&
		     port->cc2 != TYPEC_CC_OPEN) ||
		    (port->cc1 != TYPEC_CC_OPEN &&
		     port->cc2 == TYPEC_CC_OPEN))
			tcpm_set_state(port, SNK_DEBOUNCED,
				       PD_T_CC_DEBOUNCE);
		else if (tcpm_port_is_disconnected(port))
			tcpm_set_state(port, SNK_UNATTACHED,
				       PD_T_CC_DEBOUNCE);
		break;
	case SNK_DEBOUNCED:
		if (tcpm_port_is_disconnected(port)) {
			tcpm_set_state(port, SNK_UNATTACHED,
				       PD_T_PD_DEBOUNCE);
		} else if (port->vbus_present)
			tcpm_set_state(port, SNK_ATTACHED, 0);
		else
			/* Wait for VBUS, but not forever */
			tcpm_set_state(port, PORT_RESET, PD_T_PS_SOURCE_ON);
		break;

	case SNK_ATTACHED:
		ret = tcpm_snk_attach(port);
		if (ret < 0)
			tcpm_set_state(port, SNK_UNATTACHED, 0);
		else
			tcpm_set_state(port, SNK_STARTUP, 0);
		break;
	case SNK_STARTUP:
		port->negotiated_rev = PD_MAX_REV;
		port->message_id = 0;
		port->rx_msgid = -1;
		port->explicit_contract = false;
		tcpm_set_state(port, SNK_DISCOVERY, 0);
		break;
	case SNK_DISCOVERY:
		if (port->vbus_present) {
			tcpm_set_current_limit(port,
					       tcpm_get_current_limit(port),
					       5000);
			tcpm_set_charge(port, true);
			tcpm_set_state(port, SNK_WAIT_CAPABILITIES, 0);
			break;
		}
		/*
		 * For DRP, timeouts differ. Also, handling is supposed to be
		 * different and much more complex (dead battery detection;
		 * see USB power delivery specification, section 8.3.3.6.1.5.1).
		 */
		tcpm_set_state(port, hard_reset_state(port),
			       port->port_type == TYPEC_PORT_DRP ?
					PD_T_DB_DETECT : PD_T_NO_RESPONSE);
		break;
	case SNK_DISCOVERY_DEBOUNCE:
		tcpm_set_state(port, SNK_DISCOVERY_DEBOUNCE_DONE,
			       PD_T_CC_DEBOUNCE);
		break;
	case SNK_DISCOVERY_DEBOUNCE_DONE:
#if 0
		if (!tcpm_port_is_disconnected(port) &&
		    tcpm_port_is_sink(port) &&
		    ktime_after(port->delayed_runtime, ktime_get())) {
			tcpm_set_state(port, SNK_DISCOVERY,
				       ktime_to_ms(ktime_sub(port->delayed_runtime, ktime_get())));
			break;
		}
#endif
		tcpm_set_state(port, unattached_state(port), 0);
		break;
	case SNK_WAIT_CAPABILITIES:
		ret = port->tcpc->set_pd_rx(port->tcpc, true);
		if (ret < 0) {
			tcpm_set_state(port, SNK_READY, 0);
			break;
		}
		/*
		 * If VBUS has never been low, and we time out waiting
		 * for source cap, try a soft reset first, in case we
		 * were already in a stable contract before this boot.
		 * Do this only once.
		 */
		if (port->vbus_never_low) {
			port->vbus_never_low = false;
			tcpm_set_state(port, SOFT_RESET_SEND,
				       PD_T_SINK_WAIT_CAP);
		} else {
			tcpm_set_state(port, hard_reset_state(port),
				       PD_T_SINK_WAIT_CAP);
		}
		break;
	case SNK_NEGOTIATE_CAPABILITIES:
		port->pd_capable = true;
		port->hard_reset_count = 0;
		ret = tcpm_pd_send_request(port);
		if (ret < 0) {
			/* Let the Source send capabilities again. */
			tcpm_set_state(port, SNK_WAIT_CAPABILITIES, 0);
		} else {
			tcpm_set_state_cond(port, hard_reset_state(port),
					    PD_T_SENDER_RESPONSE);
		}
		break;
	case SNK_NEGOTIATE_PPS_CAPABILITIES:
		ret = tcpm_pd_send_pps_request(port);
		if (ret < 0) {
			port->pps_status = ret;
			/*
			 * If this was called due to updates to sink
			 * capabilities, and pps is no longer valid, we should
			 * safely fall back to a standard PDO.
			 */
			if (port->update_sink_caps)
				tcpm_set_state(port, SNK_NEGOTIATE_CAPABILITIES, 0);
			else
				tcpm_set_state(port, SNK_READY, 0);
		} else {
			tcpm_set_state_cond(port, hard_reset_state(port),
					    PD_T_SENDER_RESPONSE);
		}
		break;
	case SNK_TRANSITION_SINK:
	case SNK_TRANSITION_SINK_VBUS:
		tcpm_set_state(port, hard_reset_state(port),
			       PD_T_PS_TRANSITION);
		break;
	case SNK_READY:
		port->try_snk_count = 0;
		port->update_sink_caps = false;
		tcpm_typec_connect(port);
		/*
		 * Here poll_event_cnt is cleared, waiting for self-powered Type-C devices
		 * to send DR_swap Messge until 1s (TCPM_POLL_EVENT_TIME_OUT * 500us)timeout
		 */
		if (port->wait_dr_swap_Message)
			port->poll_event_cnt = 0;

		break;

	/* Accessory states */
	case ACC_UNATTACHED:
		tcpm_acc_detach(port);
		tcpm_set_state(port, SRC_UNATTACHED, 0);
		break;
	case DEBUG_ACC_ATTACHED:
	case AUDIO_ACC_ATTACHED:
		ret = tcpm_acc_attach(port);
		if (ret < 0)
			tcpm_set_state(port, ACC_UNATTACHED, 0);
		break;
	case AUDIO_ACC_DEBOUNCE:
		tcpm_set_state(port, ACC_UNATTACHED, PD_T_CC_DEBOUNCE);
		break;

	/* Hard_Reset states */
	case HARD_RESET_SEND:
		tcpm_pd_transmit(port, TCPC_TX_HARD_RESET, NULL);
		tcpm_set_state(port, HARD_RESET_START, 0);
		port->wait_dr_swap_Message = false;
		break;
	case HARD_RESET_START:
		port->hard_reset_count++;
		port->tcpc->set_pd_rx(port->tcpc, false);
		port->nr_sink_caps = 0;
		port->send_discover = true;
		if (port->pwr_role == TYPEC_SOURCE)
			tcpm_set_state(port, SRC_HARD_RESET_VBUS_OFF,
				       PD_T_PS_HARD_RESET);
		else
			tcpm_set_state(port, SNK_HARD_RESET_SINK_OFF, 0);
		break;
	case SRC_HARD_RESET_VBUS_OFF:
		tcpm_set_vconn(port, true);
		tcpm_set_vbus(port, false);
		tcpm_set_roles(port, port->self_powered, TYPEC_SOURCE,
			       TYPEC_HOST);
		tcpm_set_state(port, SRC_HARD_RESET_VBUS_ON, PD_T_SRC_RECOVER);
		break;
	case SRC_HARD_RESET_VBUS_ON:
		tcpm_set_vconn(port, true);
		tcpm_set_vbus(port, true);
		port->tcpc->set_pd_rx(port->tcpc, true);
		tcpm_set_attached_state(port, true);
		tcpm_set_state(port, SRC_UNATTACHED, PD_T_PS_SOURCE_ON);
		break;
	case SNK_HARD_RESET_SINK_OFF:
		memset(&port->pps_data, 0, sizeof(port->pps_data));
		tcpm_set_vconn(port, false);
		if (port->pd_capable)
			tcpm_set_charge(port, false);
		tcpm_set_roles(port, port->self_powered, TYPEC_SINK,
			       TYPEC_DEVICE);
		/*
		 * VBUS may or may not toggle, depending on the adapter.
		 * If it doesn't toggle, transition to SNK_HARD_RESET_SINK_ON
		 * directly after timeout.
		 */
		tcpm_set_state(port, SNK_HARD_RESET_SINK_ON, PD_T_SAFE_0V);
		break;
	case SNK_HARD_RESET_WAIT_VBUS:
		/* Assume we're disconnected if VBUS doesn't come back. */
		tcpm_set_state(port, SNK_UNATTACHED,
			       PD_T_SRC_RECOVER_MAX + PD_T_SRC_TURN_ON);
		break;
	case SNK_HARD_RESET_SINK_ON:
		/* Note: There is no guarantee that VBUS is on in this state */
		/*
		 * XXX:
		 * The specification suggests that dual mode ports in sink
		 * mode should transition to state PE_SRC_Transition_to_default.
		 * See USB power delivery specification chapter 8.3.3.6.1.3.
		 * This would mean to to
		 * - turn off VCONN, reset power supply
		 * - request hardware reset
		 * - turn on VCONN
		 * - Transition to state PE_Src_Startup
		 * SNK only ports shall transition to state Snk_Startup
		 * (see chapter 8.3.3.3.8).
		 * Similar, dual-mode ports in source mode should transition
		 * to PE_SNK_Transition_to_default.
		 */
		if (port->pd_capable) {
			tcpm_set_current_limit(port,
					       tcpm_get_current_limit(port),
					       5000);
			tcpm_set_charge(port, true);
		}
		tcpm_set_attached_state(port, true);
		tcpm_set_state(port, SNK_STARTUP, 0);
		break;

	/* Soft_Reset states */
	case SOFT_RESET:
		port->message_id = 0;
		port->rx_msgid = -1;
		tcpm_pd_send_control(port, PD_CTRL_ACCEPT);
		if (port->pwr_role == TYPEC_SOURCE) {
			tcpm_set_state(port, SRC_SEND_CAPABILITIES, 0);
		} else {
			tcpm_set_state(port, SNK_WAIT_CAPABILITIES, 0);
		}
		break;
	case SOFT_RESET_SEND:
		port->message_id = 0;
		port->rx_msgid = -1;
		if (tcpm_pd_send_control(port, PD_CTRL_SOFT_RESET))
			tcpm_set_state_cond(port, hard_reset_state(port), 0);
		else
			tcpm_set_state_cond(port, hard_reset_state(port),
					    PD_T_SENDER_RESPONSE);
		break;

	/* DR_Swap states */
	case DR_SWAP_SEND:
		tcpm_pd_send_control(port, PD_CTRL_DR_SWAP);
		tcpm_set_state_cond(port, DR_SWAP_SEND_TIMEOUT,
				    PD_T_SENDER_RESPONSE);
		break;
	case DR_SWAP_ACCEPT:
		tcpm_pd_send_control(port, PD_CTRL_ACCEPT);
#if 0
		/* Set VDM state machine running flag ASAP */
		if (port->data_role == TYPEC_DEVICE && port->send_discover)
			port->vdm_sm_running = true;
#endif
		tcpm_set_state_cond(port, DR_SWAP_CHANGE_DR, 0);
		break;
	case DR_SWAP_SEND_TIMEOUT:
		//tcpm_swap_complete(port, -ETIMEDOUT);
		tcpm_set_state(port, ready_state(port), 0);
		break;
	case DR_SWAP_CHANGE_DR:
		if (port->data_role == TYPEC_HOST) {
			//tcpm_unregister_altmodes(port);
			tcpm_set_roles(port, true, port->pwr_role,
				       TYPEC_DEVICE);
		} else {
			tcpm_set_roles(port, true, port->pwr_role,
				       TYPEC_HOST);
			//port->send_discover = true;
		}
		/* DR_swap process complete, wait_dr_swap_Message is cleared */
		port->wait_dr_swap_Message = false;
		tcpm_set_state(port, ready_state(port), 0);
		break;

#if 0

	/* PR_Swap states */
	case PR_SWAP_ACCEPT:
		tcpm_pd_send_control(port, PD_CTRL_ACCEPT);
		tcpm_set_state(port, PR_SWAP_START, 0);
		break;
	case PR_SWAP_SEND:
		tcpm_pd_send_control(port, PD_CTRL_PR_SWAP);
		tcpm_set_state_cond(port, PR_SWAP_SEND_TIMEOUT,
				    PD_T_SENDER_RESPONSE);
		break;
	case PR_SWAP_SEND_TIMEOUT:
		tcpm_set_state(port, ready_state(port), 0);
		break;
	case PR_SWAP_START:
		tcpm_apply_rc(port);
		if (port->pwr_role == TYPEC_SOURCE)
			tcpm_set_state(port, PR_SWAP_SRC_SNK_TRANSITION_OFF,
				       PD_T_SRC_TRANSITION);
		else
			tcpm_set_state(port, PR_SWAP_SNK_SRC_SINK_OFF, 0);
		break;
	case PR_SWAP_SRC_SNK_TRANSITION_OFF:
		/*
		 * Prevent vbus discharge circuit from turning on during PR_SWAP
		 * as this is not a disconnect.
		 */
		tcpm_set_vbus(port, false);
		port->explicit_contract = false;
		/* allow time for Vbus discharge, must be < tSrcSwapStdby */
		tcpm_set_state(port, PR_SWAP_SRC_SNK_SOURCE_OFF,
			       PD_T_SRCSWAPSTDBY);
		break;
	case PR_SWAP_SRC_SNK_SOURCE_OFF:
		timer_val_msecs = PD_T_CC_DEBOUNCE;
		trace_android_vh_typec_tcpm_get_timer(tcpm_states[PR_SWAP_SRC_SNK_SOURCE_OFF],
						      CC_DEBOUNCE, &timer_val_msecs);
		tcpm_set_cc(port, TYPEC_CC_RD);
		/* allow CC debounce */
		tcpm_set_state(port, PR_SWAP_SRC_SNK_SOURCE_OFF_CC_DEBOUNCED,
			       timer_val_msecs);
		break;
	case PR_SWAP_SRC_SNK_SOURCE_OFF_CC_DEBOUNCED:
		/*
		 * USB-PD standard, 6.2.1.4, Port Power Role:
		 * "During the Power Role Swap Sequence, for the initial Source
		 * Port, the Port Power Role field shall be set to Sink in the
		 * PS_RDY Message indicating that the initial Source’s power
		 * supply is turned off"
		 */
		tcpm_set_pwr_role(port, TYPEC_SINK);
		if (tcpm_pd_send_control(port, PD_CTRL_PS_RDY)) {
			tcpm_set_state(port, ERROR_RECOVERY, 0);
			break;
		}
		tcpm_set_state(port, ERROR_RECOVERY, PD_T_PS_SOURCE_ON_PRS);
		break;
	case PR_SWAP_SRC_SNK_SINK_ON:
		tcpm_enable_auto_vbus_discharge(port, true);
		/* Set the vbus disconnect threshold for implicit contract */
		tcpm_set_auto_vbus_discharge_threshold(port, TYPEC_PWR_MODE_USB, false, VSAFE5V);
		tcpm_set_state(port, SNK_STARTUP, 0);
		break;
	case PR_SWAP_SNK_SRC_SINK_OFF:
		timer_val_msecs = PD_T_PS_SOURCE_OFF;
		trace_android_vh_typec_tcpm_get_timer(tcpm_states[PR_SWAP_SNK_SRC_SINK_OFF],
						      SOURCE_OFF, &timer_val_msecs);
		/*
		 * Prevent vbus discharge circuit from turning on during PR_SWAP
		 * as this is not a disconnect.
		 */
		tcpm_set_auto_vbus_discharge_threshold(port, TYPEC_PWR_MODE_USB,
						       port->pps_data.active, 0);
		tcpm_set_charge(port, false);
		tcpm_set_state(port, hard_reset_state(port), timer_val_msecs);
		break;
	case PR_SWAP_SNK_SRC_SOURCE_ON:
		tcpm_enable_auto_vbus_discharge(port, true);
		tcpm_set_cc(port, tcpm_rp_cc(port));
		tcpm_set_vbus(port, true);
		/*
		 * allow time VBUS ramp-up, must be < tNewSrc
		 * Also, this window overlaps with CC debounce as well.
		 * So, Wait for the max of two which is PD_T_NEWSRC
		 */
		tcpm_set_state(port, PR_SWAP_SNK_SRC_SOURCE_ON_VBUS_RAMPED_UP,
			       PD_T_NEWSRC);
		break;
	case PR_SWAP_SNK_SRC_SOURCE_ON_VBUS_RAMPED_UP:
		/*
		 * USB PD standard, 6.2.1.4:
		 * "Subsequent Messages initiated by the Policy Engine,
		 * such as the PS_RDY Message sent to indicate that Vbus
		 * is ready, will have the Port Power Role field set to
		 * Source."
		 */
		tcpm_set_pwr_role(port, TYPEC_SOURCE);
		tcpm_pd_send_control(port, PD_CTRL_PS_RDY);
		tcpm_set_state(port, SRC_STARTUP, PD_T_SWAP_SRC_START);
		break;
#endif
	case GET_STATUS_SEND:
		tcpm_pd_send_control(port, PD_CTRL_GET_STATUS);
		tcpm_set_state(port, GET_STATUS_SEND_TIMEOUT,
			       PD_T_SENDER_RESPONSE);
		break;
	case GET_STATUS_SEND_TIMEOUT:
		tcpm_set_state(port, ready_state(port), 0);
		break;
	case GET_PPS_STATUS_SEND:
		tcpm_pd_send_control(port, PD_CTRL_GET_PPS_STATUS);
		tcpm_set_state(port, GET_PPS_STATUS_SEND_TIMEOUT,
			       PD_T_SENDER_RESPONSE);
		break;
	case GET_PPS_STATUS_SEND_TIMEOUT:
		tcpm_set_state(port, ready_state(port), 0);
		break;
	case GET_SINK_CAP:
		tcpm_pd_send_control(port, PD_CTRL_GET_SINK_CAP);
		tcpm_set_state(port, GET_SINK_CAP_TIMEOUT, PD_T_SENDER_RESPONSE);
		break;
	case GET_SINK_CAP_TIMEOUT:
		tcpm_set_state(port, ready_state(port), 0);
		break;
	case ERROR_RECOVERY:
		tcpm_set_state(port, PORT_RESET, 0);
		break;
	case PORT_RESET:
		tcpm_reset_port(port);
		tcpm_set_cc(port, TYPEC_CC_OPEN);
		tcpm_set_state(port, PORT_RESET_WAIT_OFF,
			       PD_T_ERROR_RECOVERY);
		break;
	case PORT_RESET_WAIT_OFF:
		tcpm_set_state(port,
			       tcpm_default_state(port),
			       port->vbus_present ? PD_T_PS_SOURCE_OFF : 0);
		break;
	default:
		printf("Unexpected port state %d\n", port->state);
		break;
	}
}

static void tcpm_state_machine(struct tcpm_port *port)
{
	enum tcpm_state prev_state;

	mutex_lock(&port->lock);
	port->state_machine_running = true;

	if (port->queued_message && tcpm_send_queued_message(port))
		goto done;

	/* If we were queued due to a delayed state change, update it now */
	if (port->delayed_state) {
		debug("state change %s -> %s [delayed %ld ms]\n",
			 tcpm_states[port->state],
			 tcpm_states[port->delayed_state], port->delay_ms);
		port->prev_state = port->state;
		port->state = port->delayed_state;
		port->delayed_state = INVALID_STATE;
	}

	/*
	 * Continue running as long as we have (non-delayed) state changes
	 * to make.
	 */
	do {
		prev_state = port->state;
		run_state_machine(port);
		if (port->queued_message)
			tcpm_send_queued_message(port);
	} while (port->state != prev_state && !port->delayed_state);

done:
	port->state_machine_running = false;
	mutex_unlock(&port->lock);
}

static void _tcpm_cc_change(struct tcpm_port *port, enum typec_cc_status cc1,
			    enum typec_cc_status cc2)
{
	enum typec_cc_status old_cc1, old_cc2;
	enum tcpm_state new_state;

	old_cc1 = port->cc1;
	old_cc2 = port->cc2;
	port->cc1 = cc1;
	port->cc2 = cc2;

	debug("CC1: %u -> %u, CC2: %u -> %u [state %s, polarity %d, %s]\n",
	      old_cc1, cc1, old_cc2, cc2, tcpm_states[port->state],
	      port->polarity,
	      tcpm_port_is_disconnected(port) ? "disconnected" : "connected");

	switch (port->state) {
	case TOGGLING:
		if (tcpm_port_is_debug(port) || tcpm_port_is_audio(port) ||
		    tcpm_port_is_source(port))
			tcpm_set_state(port, SRC_ATTACH_WAIT, 0);
		else if (tcpm_port_is_sink(port))
			tcpm_set_state(port, SNK_ATTACH_WAIT, 0);
		break;
	case SRC_UNATTACHED:
	case ACC_UNATTACHED:
		if (tcpm_port_is_debug(port) || tcpm_port_is_audio(port) ||
		    tcpm_port_is_source(port))
			tcpm_set_state(port, SRC_ATTACH_WAIT, 0);
		break;
	case SRC_ATTACH_WAIT:
		if (tcpm_port_is_disconnected(port) ||
		    tcpm_port_is_audio_detached(port))
			tcpm_set_state(port, SRC_UNATTACHED, 0);
		else if (cc1 != old_cc1 || cc2 != old_cc2)
			tcpm_set_state(port, SRC_ATTACH_WAIT, 0);
		break;
	case SRC_ATTACHED:
	case SRC_SEND_CAPABILITIES:
	case SRC_READY:
		if (tcpm_port_is_disconnected(port) ||
		    !tcpm_port_is_source(port))
			tcpm_set_state(port, SRC_UNATTACHED, 0);
		break;
	case SNK_UNATTACHED:
		if (tcpm_port_is_sink(port))
			tcpm_set_state(port, SNK_ATTACH_WAIT, 0);
		break;
	case SNK_ATTACH_WAIT:
		if ((port->cc1 == TYPEC_CC_OPEN &&
		     port->cc2 != TYPEC_CC_OPEN) ||
		    (port->cc1 != TYPEC_CC_OPEN &&
		     port->cc2 == TYPEC_CC_OPEN))
			new_state = SNK_DEBOUNCED;
		else if (tcpm_port_is_disconnected(port))
			new_state = SNK_UNATTACHED;
		else
			break;
		if (new_state != port->delayed_state)
			tcpm_set_state(port, SNK_ATTACH_WAIT, 0);
		break;
	case SNK_DEBOUNCED:
		if (tcpm_port_is_disconnected(port))
			new_state = SNK_UNATTACHED;
		else if (port->vbus_present)
			new_state = tcpm_try_src(port) ? SRC_TRY : SNK_ATTACHED;
		else
			new_state = SNK_UNATTACHED;
		if (new_state != port->delayed_state)
			tcpm_set_state(port, SNK_DEBOUNCED, 0);
		break;
	case SNK_READY:
		if (tcpm_port_is_disconnected(port))
			tcpm_set_state(port, unattached_state(port), 0);
		else if (!port->pd_capable &&
			 (cc1 != old_cc1 || cc2 != old_cc2))
			tcpm_set_current_limit(port,
					       tcpm_get_current_limit(port),
					       5000);
		break;

	case AUDIO_ACC_ATTACHED:
		if (cc1 == TYPEC_CC_OPEN || cc2 == TYPEC_CC_OPEN)
			tcpm_set_state(port, AUDIO_ACC_DEBOUNCE, 0);
		break;
	case AUDIO_ACC_DEBOUNCE:
		if (tcpm_port_is_audio(port))
			tcpm_set_state(port, AUDIO_ACC_ATTACHED, 0);
		break;

	case DEBUG_ACC_ATTACHED:
		if (cc1 == TYPEC_CC_OPEN || cc2 == TYPEC_CC_OPEN)
			tcpm_set_state(port, ACC_UNATTACHED, 0);
		break;

	case SNK_TRY:
		/* Do nothing, waiting for timeout */
		break;

	case SNK_DISCOVERY:
		/* CC line is unstable, wait for debounce */
		if (tcpm_port_is_disconnected(port))
			tcpm_set_state(port, SNK_DISCOVERY_DEBOUNCE, 0);
		break;
	case SNK_DISCOVERY_DEBOUNCE:
		break;

	case SRC_TRYWAIT:
		/* Hand over to state machine if needed */
		if (!port->vbus_present && tcpm_port_is_source(port))
			tcpm_set_state(port, SRC_TRYWAIT_DEBOUNCE, 0);
		break;
	case SRC_TRYWAIT_DEBOUNCE:
		if (port->vbus_present || !tcpm_port_is_source(port))
			tcpm_set_state(port, SRC_TRYWAIT, 0);
		break;
	case SNK_TRY_WAIT_DEBOUNCE:
		if (!tcpm_port_is_sink(port)) {
			port->max_wait = 0;
			tcpm_set_state(port, SRC_TRYWAIT, 0);
		}
		break;
	case SRC_TRY_WAIT:
		if (tcpm_port_is_source(port))
			tcpm_set_state(port, SRC_TRY_DEBOUNCE, 0);
		break;
	case SRC_TRY_DEBOUNCE:
		tcpm_set_state(port, SRC_TRY_WAIT, 0);
		break;
	case SNK_TRYWAIT_DEBOUNCE:
		if (tcpm_port_is_sink(port))
			tcpm_set_state(port, SNK_TRYWAIT_VBUS, 0);
		break;
	case SNK_TRYWAIT_VBUS:
		if (!tcpm_port_is_sink(port))
			tcpm_set_state(port, SNK_TRYWAIT_DEBOUNCE, 0);
		break;
	case SNK_TRYWAIT:
		/* Do nothing, waiting for tCCDebounce */
		break;
	case PR_SWAP_SNK_SRC_SINK_OFF:
	case PR_SWAP_SRC_SNK_TRANSITION_OFF:
	case PR_SWAP_SRC_SNK_SOURCE_OFF:
	case PR_SWAP_SRC_SNK_SOURCE_OFF_CC_DEBOUNCED:
	case PR_SWAP_SNK_SRC_SOURCE_ON:
		/*
		 * CC state change is expected in PR_SWAP
		 * Ignore it.
		 */
		break;

	case PORT_RESET:
	case PORT_RESET_WAIT_OFF:
		/*
		 * State set back to default mode once the timer completes.
		 * Ignore CC changes here.
		 */
		break;
	default:
		/*
		 * While acting as sink and auto vbus discharge is enabled, Allow disconnect
		 * to be driven by vbus disconnect.
		 */
		if (tcpm_port_is_disconnected(port))
			tcpm_set_state(port, unattached_state(port), 0);
		break;
	}
}

static void _tcpm_pd_vbus_on(struct tcpm_port *port)
{
	debug("%s: VBUS on\n", __func__);
	port->vbus_present = true;
	/*
	 * When vbus_present is true i.e. Voltage at VBUS is greater than VSAFE5V implicitly
	 * states that vbus is not at VSAFE0V, hence clear the vbus_vsafe0v flag here.
	 */
	port->vbus_vsafe0v = false;

	switch (port->state) {
	case SNK_TRANSITION_SINK_VBUS:
		port->explicit_contract = true;
		tcpm_set_state(port, SNK_READY, 0);
		break;
	case SNK_DISCOVERY:
		tcpm_set_state(port, SNK_DISCOVERY, 0);
		break;
	case SNK_DEBOUNCED:
		tcpm_set_state(port, SNK_ATTACHED, 0);
		break;
	case SNK_HARD_RESET_WAIT_VBUS:
		tcpm_set_state(port, SNK_HARD_RESET_SINK_ON, 0);
		break;
	case SRC_ATTACHED:
		tcpm_set_state(port, SRC_STARTUP, 0);
		break;
	case SRC_HARD_RESET_VBUS_ON:
		tcpm_set_state(port, SRC_STARTUP, 0);
		break;

	case SNK_TRY:
		/* Do nothing, waiting for timeout */
		break;
	case SRC_TRYWAIT:
		/* Do nothing, Waiting for Rd to be detected */
		break;
	case SRC_TRYWAIT_DEBOUNCE:
		tcpm_set_state(port, SRC_TRYWAIT, 0);
		break;
	case SNK_TRY_WAIT_DEBOUNCE:
		/* Do nothing, waiting for PD_DEBOUNCE to do be done */
		break;
	case SNK_TRYWAIT:
		/* Do nothing, waiting for tCCDebounce */
		break;
	case SNK_TRYWAIT_VBUS:
		if (tcpm_port_is_sink(port))
			tcpm_set_state(port, SNK_ATTACHED, 0);
		break;
	case SNK_TRYWAIT_DEBOUNCE:
		/* Do nothing, waiting for Rp */
		break;
	case SRC_TRY_WAIT:
	case SRC_TRY_DEBOUNCE:
		/* Do nothing, waiting for sink detection */
		break;

	case PORT_RESET:
	case PORT_RESET_WAIT_OFF:
		/*
		 * State set back to default mode once the timer completes.
		 * Ignore vbus changes here.
		 */
		break;

	default:
		break;
	}
}

static void _tcpm_pd_vbus_off(struct tcpm_port *port)
{
	debug("%s: VBUS off\n", __func__);
	port->vbus_present = false;
	port->vbus_never_low = false;
	switch (port->state) {
	case SNK_HARD_RESET_SINK_OFF:
		tcpm_set_state(port, SNK_HARD_RESET_WAIT_VBUS, 0);
		break;
	case HARD_RESET_SEND:
		break;
	case SNK_TRY:
		/* Do nothing, waiting for timeout */
		break;
	case SRC_TRYWAIT:
		/* Hand over to state machine if needed */
		if (tcpm_port_is_source(port))
			tcpm_set_state(port, SRC_TRYWAIT_DEBOUNCE, 0);
		break;
	case SNK_TRY_WAIT_DEBOUNCE:
		/* Do nothing, waiting for PD_DEBOUNCE to do be done */
		break;
	case SNK_TRYWAIT:
	case SNK_TRYWAIT_VBUS:
	case SNK_TRYWAIT_DEBOUNCE:
		break;
	case SNK_ATTACH_WAIT:
		port->debouncing = false;
		tcpm_set_state(port, SNK_UNATTACHED, 0);
		break;

	case SNK_NEGOTIATE_CAPABILITIES:
		break;

	case PR_SWAP_SRC_SNK_TRANSITION_OFF:
		tcpm_set_state(port, PR_SWAP_SRC_SNK_SOURCE_OFF, 0);
		break;

	case PR_SWAP_SNK_SRC_SINK_OFF:
		/* Do nothing, expected */
		break;

	case PR_SWAP_SNK_SRC_SOURCE_ON:
		/*
		 * Do nothing when vbus off notification is received.
		 * TCPM can wait for PD_T_NEWSRC in PR_SWAP_SNK_SRC_SOURCE_ON
		 * for the vbus source to ramp up.
		 */
		break;

	case PORT_RESET_WAIT_OFF:
		tcpm_set_state(port, tcpm_default_state(port), 0);
		break;

	case SRC_TRY_WAIT:
	case SRC_TRY_DEBOUNCE:
		/* Do nothing, waiting for sink detection */
		break;

	case PORT_RESET:
		/*
		 * State set back to default mode once the timer completes.
		 * Ignore vbus changes here.
		 */
		break;

	default:
		if (port->pwr_role == TYPEC_SINK && port->attached)
			tcpm_set_state(port, SNK_UNATTACHED, 0);
		break;
	}
}

static void _tcpm_pd_hard_reset(struct tcpm_port *port)
{
	debug("Received hard reset\n");
	port->poll_event_cnt = 0;

	/* If a hard reset message is received during the port reset process,
	 * we should ignore it, that is, do not set port->state to HARD_RESET_START.
	 */
	if (port->state == PORT_RESET || port->state == PORT_RESET_WAIT_OFF)
		return ;

	/*
	 * If we keep receiving hard reset requests, executing the hard reset
	 * must have failed. Revert to error recovery if that happens.
	 */
	tcpm_set_state(port,
		       port->hard_reset_count < PD_N_HARD_RESET_COUNT ?
				HARD_RESET_START : ERROR_RECOVERY,
		       0);
}

#if 0
static void tcpm_pd_event_handler(struct tcpm_port *port)
{
	u32 events;

	while (port->pd_events) {
		events = port->pd_events;
		port->pd_events = 0;
		if (events & TCPM_RESET_EVENT)
			_tcpm_pd_hard_reset(port);
		if (events & TCPM_VBUS_EVENT) {
			bool vbus;

			vbus = port->tcpc->get_vbus(port->tcpc);
			if (vbus) {
				_tcpm_pd_vbus_on(port);
			} else {
				_tcpm_pd_vbus_off(port);
				/*
				 * When TCPC does not support detecting vsafe0v voltage level,
				 * treat vbus absent as vsafe0v. Else invoke is_vbus_vsafe0v
				 * to see if vbus has discharge to VSAFE0V.
				 */
				if (!port->tcpc->is_vbus_vsafe0v ||
				    port->tcpc->is_vbus_vsafe0v(port->tcpc))
					_tcpm_pd_vbus_vsafe0v(port);
			}
		}
		if (events & TCPM_CC_EVENT) {
			enum typec_cc_status cc1, cc2;

			if (port->tcpc->get_cc(port->tcpc, &cc1, &cc2) == 0)
				_tcpm_cc_change(port, cc1, cc2);
		}
		if (events & TCPM_FRS_EVENT) {
			if (port->state == SNK_READY) {
				int ret;

				port->upcoming_state = FR_SWAP_SEND;
				ret = tcpm_ams_start(port, FAST_ROLE_SWAP);
				if (ret == -EAGAIN)
					port->upcoming_state = INVALID_STATE;
			} else {
				tcpm_log(port, "Discarding FRS_SIGNAL! Not in sink ready");
			}
		}
		if (events & TCPM_SOURCING_VBUS) {
			tcpm_log(port, "sourcing vbus");
			/*
			 * In fast role swap case TCPC autonomously sources vbus. Set vbus_source
			 * true as TCPM wouldn't have called tcpm_set_vbus.
			 *
			 * When vbus is sourced on the command on TCPM i.e. TCPM called
			 * tcpm_set_vbus to source vbus, vbus_source would already be true.
			 */
			port->vbus_source = true;
			_tcpm_pd_vbus_on(port);
		}
	}
}
#endif

void tcpm_cc_change(struct tcpm_port *port)
{
	enum typec_cc_status cc1, cc2;

	port->poll_event_cnt = 0;
	if (port->tcpc->get_cc(port->tcpc, &cc1, &cc2) == 0)
		_tcpm_cc_change(port, cc1, cc2);
}
EXPORT_SYMBOL_GPL(tcpm_cc_change);

void tcpm_vbus_change(struct tcpm_port *port)
{
	bool vbus;

	port->poll_event_cnt = 0;
	vbus = port->tcpc->get_vbus(port->tcpc);
	if (vbus)
		_tcpm_pd_vbus_on(port);
	else
		_tcpm_pd_vbus_off(port);
}
EXPORT_SYMBOL_GPL(tcpm_vbus_change);

void tcpm_pd_hard_reset(struct tcpm_port *port)
{
	port->poll_event_cnt = 0;
	_tcpm_pd_hard_reset(port);
}
EXPORT_SYMBOL_GPL(tcpm_pd_hard_reset);

static void tcpm_init(struct tcpm_port *port)
{
	enum typec_cc_status cc1, cc2;

	port->tcpc->init(port->tcpc);

	tcpm_reset_port(port);

	/*
	 * XXX
	 * Should possibly wait for VBUS to settle if it was enabled locally
	 * since tcpm_reset_port() will disable VBUS.
	 */
	port->vbus_present = port->tcpc->get_vbus(port->tcpc);
	if (port->vbus_present)
		port->vbus_never_low = true;

	/*
	 * 1. When vbus_present is true, voltage on VBUS is already at VSAFE5V.
	 * So implicitly vbus_vsafe0v = false.
	 *
	 * 2. When vbus_present is false and TCPC does NOT support querying
	 * vsafe0v status, then, it's best to assume vbus is at VSAFE0V i.e.
	 * vbus_vsafe0v is true.
	 *
	 * 3. When vbus_present is false and TCPC does support querying vsafe0v,
	 * then, query tcpc for vsafe0v status.
	 */
	if (port->vbus_present)
		port->vbus_vsafe0v = false;
	else if (!port->tcpc->is_vbus_vsafe0v)
		port->vbus_vsafe0v = true;
	else
		port->vbus_vsafe0v = port->tcpc->is_vbus_vsafe0v(port->tcpc);

	tcpm_set_state(port, tcpm_default_state(port), 0);

	if (port->tcpc->get_cc(port->tcpc, &cc1, &cc2) == 0)
		_tcpm_cc_change(port, cc1, cc2);
}

void tcpm_tcpc_reset(struct tcpm_port *port)
{
	mutex_lock(&port->lock);
	/* XXX: Maintain PD connection if possible? */
	tcpm_init(port);
	mutex_unlock(&port->lock);
}
EXPORT_SYMBOL_GPL(tcpm_tcpc_reset);

static int tcpm_fw_get_caps(struct tcpm_port *port)
{
	const char *cap_str;
	ofnode node = port->tcpc->connector_node;
	int ret;
	u32 mw, frs_current;

#if 0
	/* USB data support is optional */
	cap_str = ofnode_read_string(node, "data-role");
	if (cap_str) {
		ret = typec_find_port_data_role(cap_str);
		if (ret < 0)
			return ret;
		port->typec_caps.data = ret;
	}
#endif

	cap_str = ofnode_read_string(node, "power-role");
	if (!cap_str) {
		return -EINVAL;
	} else {
		if (!strcmp("dual", cap_str))
			port->typec_caps.type = TYPEC_PORT_DRP;
		else if (!strcmp("source", cap_str))
			port->typec_caps.type = TYPEC_PORT_SRC;
		else if (!strcmp("sink", cap_str))
			port->typec_caps.type = TYPEC_PORT_SNK;
		else
			return EINVAL;
	}

	port->port_type = port->typec_caps.type;

	port->slow_charger_loop = ofnode_read_bool(node, "slow-charger-loop");
	if (port->port_type == TYPEC_PORT_SNK)
		goto sink;

	/* Get source pdos */
	ret = ofnode_read_size(node, "source-pdos") / sizeof(u32);
	if (ret <= 0)
		return -EINVAL;

	port->nr_src_pdo = min(ret, PDO_MAX_OBJECTS);
	ret = ofnode_read_u32_array(node, "source-pdos",
				    port->src_pdo, port->nr_src_pdo);
	if (ret || tcpm_validate_caps(port, port->src_pdo,
					    port->nr_src_pdo))
		return -EINVAL;

	if (port->port_type == TYPEC_PORT_SRC)
		return 0;

	/* Get the preferred power role for DRP */
	cap_str = ofnode_read_string(node, "try-power-role");
	if (!cap_str) {
		return -EINVAL;
	} else {
		if (!strcmp("sink", cap_str))
			port->typec_caps.prefer_role = TYPEC_SINK;
		else if (!strcmp("source", cap_str))
			port->typec_caps.prefer_role = TYPEC_SOURCE;
		else
			return -EINVAL;
	}
	if (port->typec_caps.prefer_role < 0)
		return -EINVAL;
sink:
	/* Get sink pdos */
	ret = ofnode_read_size(node, "sink-pdos") / sizeof(u32);
	if (ret <= 0)
		return -EINVAL;

	port->nr_snk_pdo = min(ret, PDO_MAX_OBJECTS);
	ret = ofnode_read_u32_array(node, "sink-pdos",
				    port->snk_pdo, port->nr_snk_pdo);
	if (ret || tcpm_validate_caps(port, port->snk_pdo,
					    port->nr_snk_pdo))
		return -EINVAL;

	if (ofnode_read_u32_array(node, "op-sink-microwatt", &mw, 1))
		return -EINVAL;
	port->operating_snk_mw = mw / 1000;

	port->self_powered = ofnode_read_bool(node, "self-powered");

	/* FRS can only be supported by DRP ports */
	if (port->port_type == TYPEC_PORT_DRP) {
		ret = ofnode_read_u32_array(node, "new-source-frs-typec-current",
					    &frs_current, 1);
		if (ret >= 0 && frs_current <= FRS_5V_3A)
			port->new_source_frs_current = frs_current;
	}

	/* sink-vdos is optional */
	ret = ofnode_read_size(node, "sink-vdos") / sizeof(u32);
	if (ret < 0)
		ret = 0;

	port->nr_snk_vdo = min(ret, VDO_MAX_OBJECTS);
	if (port->nr_snk_vdo) {
		ret = ofnode_read_u32_array(node, "sink-vdos",
					    port->snk_vdo, port->nr_snk_vdo);
		if (ret)
			return ret;
	}

	/* If sink-vdos is found, sink-vdos-v1 is expected for backward compatibility. */
	if (port->nr_snk_vdo) {
		ret = ofnode_read_size(node, "sink-vdos-v1") / sizeof(u32);
		if (ret < 0)
			return ret;
		else if (ret == 0)
			return -ENODATA;

		port->nr_snk_vdo_v1 = min(ret, VDO_MAX_OBJECTS);
		ret = ofnode_read_u32_array(node, "sink-vdos-v1",
					    port->snk_vdo_v1,
					    port->nr_snk_vdo_v1);
		if (ret)
			return ret;
	}

	return 0;
}

struct tcpm_port *tcpm_port_init(struct udevice *dev, struct tcpc_dev *tcpc)
{
	struct tcpm_port *port;
	int err;

	if (!dev || !tcpc ||
	    !tcpc->get_vbus || !tcpc->set_cc || !tcpc->get_cc ||
	    !tcpc->set_polarity || !tcpc->set_vconn || !tcpc->set_vbus ||
	    !tcpc->set_pd_rx || !tcpc->set_roles || !tcpc->pd_transmit)
		return ERR_PTR(-EINVAL);

	port = devm_kzalloc(dev, sizeof(*port), GFP_KERNEL);
	if (!port)
		return ERR_PTR(-ENOMEM);

	port->dev = dev;
	port->tcpc = tcpc;

	err = tcpm_fw_get_caps(port);
	if (err < 0) {
		printf("%s: please check the dts config of %s node(%d)\n",
			__func__, dev_read_name(dev), err);
		return ERR_PTR(err);
	}

	port->try_role = port->typec_caps.prefer_role;

	port->typec_caps.revision = 0x0120;	/* Type-C spec release 1.2 */
	port->typec_caps.pd_revision = 0x0300;	/* USB-PD spec release 3.0 */
	port->typec_caps.svdm_version = SVDM_VER_2_0;
	port->typec_caps.driver_data = port;
	port->typec_caps.orientation_aware = 1;

	port->port_type = port->typec_caps.type;

	tcpm_init(port);

	printf("%s: init finished\n", dev_read_name(dev));

	return port;
}
EXPORT_SYMBOL_GPL(tcpm_port_init);

void tcpm_poll_event(struct tcpm_port *port)
{
	if (!port->tcpc->get_vbus(port->tcpc))
		return ;

	while (port->poll_event_cnt < TCPM_POLL_EVENT_TIME_OUT) {
		if (!port->wait_dr_swap_Message &&
		    ((port->state == SNK_READY) ||
		    (port->state == SRC_READY) ||
		    (port->state == DEBUG_ACC_ATTACHED) ||
		    (port->state == AUDIO_ACC_ATTACHED)))
		    break;

		port->tcpc->poll_event(port->tcpc);
		port->poll_event_cnt++;
		udelay(500);
	}

	/*
	 * At this time, call the callback function of the respective pd chip
	 * to enter the low-power mode. In order to reduce the time spent on
	 * the PD chip driver as much as possible, the tcpm framework does not
	 * fully process the communication initiated by the device,so it should
	 * be noted that we can disable the internal oscillator, etc., but do
	 * not turn off the power of the transceiver module, otherwise the
	 * self-powered Type-C device will initiate a Message(eg: self-powered
	 * Type-C hub initiates a SINK capability request(PD_CTRL_GET_SINK_CAP))
	 * and the pd chip cannot reply to GoodCRC, causing the self-powered Type-C
	 * device to switch vbus to vSafe5v, or even turn off vbus.
	 */
	if (port->tcpc->enter_low_power_mode) {
		if (port->tcpc->enter_low_power_mode(port->tcpc,
						     port->attached,
						     port->pd_capable))
			printf("failed to enter low power\n");
		else
			printf("PD chip enter low power mode\n");
	}
}
EXPORT_SYMBOL_GPL(tcpm_poll_event);

int tcpm_get_voltage(struct tcpm_port *port)
{
	return port->supply_voltage * 1000;
}
EXPORT_SYMBOL_GPL(tcpm_get_voltage);

int tcpm_get_current(struct tcpm_port *port)
{
	return port->current_limit * 1000;
}
EXPORT_SYMBOL_GPL(tcpm_get_voltage);

int tcpm_get_online(struct tcpm_port *port)
{
	if (port->state == SNK_READY)
		return 1;
	else
		return 0;
}
EXPORT_SYMBOL_GPL(tcpm_get_online);

void tcpm_uninit_port(struct tcpm_port *port)
{
	tcpm_reset_port(port);
}
EXPORT_SYMBOL_GPL(tcpm_unregister_port);
