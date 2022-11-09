// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2015-2017 Google, Inc
 *
 * USB Type-C Port Controller Interface.
 */

#include <dm.h>
#include <i2c.h>
#include <asm/gpio.h>
#include <power/power_delivery/pd.h>
#include <power/power_delivery/tcpm.h>
#include <power/power_delivery/typec.h>
#include <power/power_delivery/power_delivery.h>

#include "tcpci.h"

#define PD_RETRY_COUNT 3

#define tcpc_presenting_cc1_rd(reg) \
	(!(TCPC_ROLE_CTRL_DRP & (reg)) && \
	 (((reg) & (TCPC_ROLE_CTRL_CC1_MASK << TCPC_ROLE_CTRL_CC1_SHIFT)) == \
	  (TCPC_ROLE_CTRL_CC_RD << TCPC_ROLE_CTRL_CC1_SHIFT)))
#define tcpc_presenting_cc2_rd(reg) \
	(!(TCPC_ROLE_CTRL_DRP & (reg)) && \
	 (((reg) & (TCPC_ROLE_CTRL_CC2_MASK << TCPC_ROLE_CTRL_CC2_SHIFT)) == \
	  (TCPC_ROLE_CTRL_CC_RD << TCPC_ROLE_CTRL_CC2_SHIFT)))

struct tcpci {
	struct udevice *dev;

	struct tcpm_port *port;

	bool controls_vbus;
	bool gpio_cc_int_present;

	struct tcpc_dev tcpc;
	struct tcpci_data *data;
	struct gpio_desc gpio_cc_int;
};

struct tcpci_chip {
	struct udevice *udev;
	struct tcpci *tcpci;
	struct tcpci_data data;
};

static inline struct tcpci *tcpc_to_tcpci(struct tcpc_dev *tcpc)
{
	return container_of(tcpc, struct tcpci, tcpc);
}

static int tcpci_read16(struct tcpci *tcpci, unsigned int reg, u16 *val)
{
	int ret = 0;
	u8 buffer[2];

	ret = dm_i2c_read(tcpci->dev, reg, buffer, 2);
	if (ret) {
		printf("%s: cannot read %02x, ret=%d\n",
			__func__, reg, ret);
		return ret;
	}

	*val = ((buffer[1] << 8) & 0xFF00) | (buffer[0] & 0xFF);

	return ret;
}

static int tcpci_block_read(struct tcpci *tcpci, unsigned int reg,
			    u8 *data, u8 length)
{
	int ret = 0;

	ret = dm_i2c_read(tcpci->dev, reg, data, length);
	if (ret)
		printf("%s: cannot block read 0x%02x, len=%d, ret=%d\n",
			__func__, reg, length, ret);

	return ret;
}

static int tcpci_write16(struct tcpci *tcpci, unsigned int reg, u16 val)
{
	int ret = 0;
	u8 buffer[2];

	buffer[0] = val & 0xFF;
	buffer[1] = (val >> 8) & 0xFF;
	ret = dm_i2c_write(tcpci->dev, reg, buffer, 2);
	if (ret)
		printf("%s: cannot write 0x%02x, ret=%d\n",
			__func__, reg, ret);

	return ret;
}

static int tcpci_block_write(struct tcpci *tcpci, unsigned int reg,
			     u8 *data, u8 length)
{
	int ret = 0;

	ret = dm_i2c_write(tcpci->dev, reg, data, length);
	if (ret)
		printf("%s: cannot block write 0x%02x, len=%d, ret=%d\n",
			__func__, reg, length, ret);

	return ret;
}

static int tcpci_set_cc(struct tcpc_dev *tcpc, enum typec_cc_status cc)
{
	struct tcpci *tcpci = tcpc_to_tcpci(tcpc);
	unsigned int reg;
	int ret;

	switch (cc) {
	case TYPEC_CC_RA:
		reg = (TCPC_ROLE_CTRL_CC_RA << TCPC_ROLE_CTRL_CC1_SHIFT) |
			(TCPC_ROLE_CTRL_CC_RA << TCPC_ROLE_CTRL_CC2_SHIFT);
		break;
	case TYPEC_CC_RD:
		reg = (TCPC_ROLE_CTRL_CC_RD << TCPC_ROLE_CTRL_CC1_SHIFT) |
			(TCPC_ROLE_CTRL_CC_RD << TCPC_ROLE_CTRL_CC2_SHIFT);
		break;
	case TYPEC_CC_RP_DEF:
		reg = (TCPC_ROLE_CTRL_CC_RP << TCPC_ROLE_CTRL_CC1_SHIFT) |
			(TCPC_ROLE_CTRL_CC_RP << TCPC_ROLE_CTRL_CC2_SHIFT) |
			(TCPC_ROLE_CTRL_RP_VAL_DEF <<
			 TCPC_ROLE_CTRL_RP_VAL_SHIFT);
		break;
	case TYPEC_CC_RP_1_5:
		reg = (TCPC_ROLE_CTRL_CC_RP << TCPC_ROLE_CTRL_CC1_SHIFT) |
			(TCPC_ROLE_CTRL_CC_RP << TCPC_ROLE_CTRL_CC2_SHIFT) |
			(TCPC_ROLE_CTRL_RP_VAL_1_5 <<
			 TCPC_ROLE_CTRL_RP_VAL_SHIFT);
		break;
	case TYPEC_CC_RP_3_0:
		reg = (TCPC_ROLE_CTRL_CC_RP << TCPC_ROLE_CTRL_CC1_SHIFT) |
			(TCPC_ROLE_CTRL_CC_RP << TCPC_ROLE_CTRL_CC2_SHIFT) |
			(TCPC_ROLE_CTRL_RP_VAL_3_0 <<
			 TCPC_ROLE_CTRL_RP_VAL_SHIFT);
		break;
	case TYPEC_CC_OPEN:
	default:
		reg = (TCPC_ROLE_CTRL_CC_OPEN << TCPC_ROLE_CTRL_CC1_SHIFT) |
			(TCPC_ROLE_CTRL_CC_OPEN << TCPC_ROLE_CTRL_CC2_SHIFT);
		break;
	}

	ret = dm_i2c_reg_write(tcpci->dev, TCPC_ROLE_CTRL, reg);
	if (ret)
		return ret;

	return 0;
}

static int tcpci_start_toggling(struct tcpc_dev *tcpc,
				enum typec_port_type port_type,
				enum typec_cc_status cc)
{
	int ret;
	struct tcpci *tcpci = tcpc_to_tcpci(tcpc);
	unsigned int reg = TCPC_ROLE_CTRL_DRP;

	if (port_type != TYPEC_PORT_DRP)
		return -EOPNOTSUPP;

	/* Handle vendor drp toggling */
	if (tcpci->data->start_drp_toggling) {
		ret = tcpci->data->start_drp_toggling(tcpci, tcpci->data, cc);
		if (ret < 0)
			return ret;
	}

	switch (cc) {
	default:
	case TYPEC_CC_RP_DEF:
		reg |= (TCPC_ROLE_CTRL_RP_VAL_DEF <<
			TCPC_ROLE_CTRL_RP_VAL_SHIFT);
		break;
	case TYPEC_CC_RP_1_5:
		reg |= (TCPC_ROLE_CTRL_RP_VAL_1_5 <<
			TCPC_ROLE_CTRL_RP_VAL_SHIFT);
		break;
	case TYPEC_CC_RP_3_0:
		reg |= (TCPC_ROLE_CTRL_RP_VAL_3_0 <<
			TCPC_ROLE_CTRL_RP_VAL_SHIFT);
		break;
	}

	if (cc == TYPEC_CC_RD)
		reg |= (TCPC_ROLE_CTRL_CC_RD << TCPC_ROLE_CTRL_CC1_SHIFT) |
			   (TCPC_ROLE_CTRL_CC_RD << TCPC_ROLE_CTRL_CC2_SHIFT);
	else
		reg |= (TCPC_ROLE_CTRL_CC_RP << TCPC_ROLE_CTRL_CC1_SHIFT) |
			   (TCPC_ROLE_CTRL_CC_RP << TCPC_ROLE_CTRL_CC2_SHIFT);
	ret = dm_i2c_reg_write(tcpci->dev, TCPC_ROLE_CTRL, reg);
	if (ret < 0)
		return ret;
	return dm_i2c_reg_write(tcpci->dev, TCPC_COMMAND,
				TCPC_CMD_LOOK4CONNECTION);
}

static enum typec_cc_status tcpci_to_typec_cc(unsigned int cc, bool sink)
{
	switch (cc) {
	case 0x1:
		return sink ? TYPEC_CC_RP_DEF : TYPEC_CC_RA;
	case 0x2:
		return sink ? TYPEC_CC_RP_1_5 : TYPEC_CC_RD;
	case 0x3:
		if (sink)
			return TYPEC_CC_RP_3_0;
		/* fall through */
	case 0x0:
	default:
		return TYPEC_CC_OPEN;
	}
}

static int tcpci_get_cc(struct tcpc_dev *tcpc,
			enum typec_cc_status *cc1, enum typec_cc_status *cc2)
{
	struct tcpci *tcpci = tcpc_to_tcpci(tcpc);
	unsigned int reg, role_control;

	role_control = dm_i2c_reg_read(tcpci->dev, TCPC_ROLE_CTRL);
	if (role_control < 0)
		return role_control;

	reg = dm_i2c_reg_read(tcpci->dev, TCPC_CC_STATUS);
	if (reg < 0)
		return reg;

	*cc1 = tcpci_to_typec_cc((reg >> TCPC_CC_STATUS_CC1_SHIFT) &
				 TCPC_CC_STATUS_CC1_MASK,
				 reg & TCPC_CC_STATUS_TERM ||
				 tcpc_presenting_cc1_rd(role_control));
	*cc2 = tcpci_to_typec_cc((reg >> TCPC_CC_STATUS_CC2_SHIFT) &
				 TCPC_CC_STATUS_CC2_MASK,
				 reg & TCPC_CC_STATUS_TERM ||
				 tcpc_presenting_cc2_rd(role_control));

	return 0;
}

static int tcpci_set_polarity(struct tcpc_dev *tcpc,
			      enum typec_cc_polarity polarity)
{
	struct tcpci *tcpci = tcpc_to_tcpci(tcpc);
	unsigned int reg;
	int ret;
	enum typec_cc_status cc1, cc2;

	/* Obtain Rp setting from role control */
	reg = dm_i2c_reg_read(tcpci->dev, TCPC_ROLE_CTRL);
	if (reg < 0)
		return reg;

	ret = tcpci_get_cc(tcpc, &cc1, &cc2);
	if (ret < 0)
		return ret;

	/*
	 * When port has drp toggling enabled, ROLE_CONTROL would only have the initial
	 * terminations for the toggling and does not indicate the final cc
	 * terminations when ConnectionResult is 0 i.e. drp toggling stops and
	 * the connection is resolbed. Infer port role from TCPC_CC_STATUS based on the
	 * terminations seen. The port role is then used to set the cc terminations.
	 */
	if (reg & TCPC_ROLE_CTRL_DRP) {
		/* Disable DRP for the OPEN setting to take effect */
		reg = reg & ~TCPC_ROLE_CTRL_DRP;

		if (polarity == TYPEC_POLARITY_CC2) {
			reg &= ~(TCPC_ROLE_CTRL_CC2_MASK << TCPC_ROLE_CTRL_CC2_SHIFT);
			/* Local port is source */
			if (cc2 == TYPEC_CC_RD)
				/* Role control would have the Rp setting when DRP was enabled */
				reg |= TCPC_ROLE_CTRL_CC_RP << TCPC_ROLE_CTRL_CC2_SHIFT;
			else
				reg |= TCPC_ROLE_CTRL_CC_RD << TCPC_ROLE_CTRL_CC2_SHIFT;
		} else {
			reg &= ~(TCPC_ROLE_CTRL_CC1_MASK << TCPC_ROLE_CTRL_CC1_SHIFT);
			/* Local port is source */
			if (cc1 == TYPEC_CC_RD)
				/* Role control would have the Rp setting when DRP was enabled */
				reg |= TCPC_ROLE_CTRL_CC_RP << TCPC_ROLE_CTRL_CC1_SHIFT;
			else
				reg |= TCPC_ROLE_CTRL_CC_RD << TCPC_ROLE_CTRL_CC1_SHIFT;
		}
	}

	if (polarity == TYPEC_POLARITY_CC2)
		reg |= TCPC_ROLE_CTRL_CC_OPEN << TCPC_ROLE_CTRL_CC1_SHIFT;
	else
		reg |= TCPC_ROLE_CTRL_CC_OPEN << TCPC_ROLE_CTRL_CC2_SHIFT;
	ret = dm_i2c_reg_write(tcpci->dev, TCPC_ROLE_CTRL, reg);
	if (ret < 0)
		return ret;

	return dm_i2c_reg_write(tcpci->dev, TCPC_TCPC_CTRL,
			(polarity == TYPEC_POLARITY_CC2) ?
			 TCPC_TCPC_CTRL_ORIENTATION : 0);
}

static int tcpci_set_vconn(struct tcpc_dev *tcpc, bool enable)
{
	struct tcpci *tcpci = tcpc_to_tcpci(tcpc);
	int ret;
	unsigned int reg;

	/* Handle vendor set vconn */
	if (tcpci->data->set_vconn) {
		ret = tcpci->data->set_vconn(tcpci, tcpci->data, enable);
		if (ret < 0)
			return ret;
	}

	reg = dm_i2c_reg_read(tcpci->dev, TCPC_POWER_CTRL);
	if (reg)
		return reg;
	reg &= ~TCPC_POWER_CTRL_VCONN_ENABLE;
	reg |= enable ? TCPC_POWER_CTRL_VCONN_ENABLE : 0;
	return dm_i2c_reg_write(tcpci->dev, TCPC_POWER_CTRL, reg);
}

static int tcpci_set_roles(struct tcpc_dev *tcpc, bool attached,
			   enum typec_role role, enum typec_data_role data)
{
	struct tcpci *tcpci = tcpc_to_tcpci(tcpc);
	unsigned int reg;
	int ret;

	reg = PD_REV20 << TCPC_MSG_HDR_INFO_REV_SHIFT;
	if (role == TYPEC_SOURCE)
		reg |= TCPC_MSG_HDR_INFO_PWR_ROLE;
	if (data == TYPEC_HOST)
		reg |= TCPC_MSG_HDR_INFO_DATA_ROLE;
	ret = dm_i2c_reg_write(tcpci->dev, TCPC_MSG_HDR_INFO, reg);
	if (ret < 0)
		return ret;

	return 0;
}

static int tcpci_set_pd_rx(struct tcpc_dev *tcpc, bool enable)
{
	struct tcpci *tcpci = tcpc_to_tcpci(tcpc);
	unsigned int reg = 0;
	int ret;

	if (enable)
		reg = TCPC_RX_DETECT_SOP | TCPC_RX_DETECT_HARD_RESET;
	ret = dm_i2c_reg_write(tcpci->dev, TCPC_RX_DETECT, reg);
	if (ret < 0)
		return ret;

	return 0;
}

static int tcpci_get_vbus(struct tcpc_dev *tcpc)
{
	struct tcpci *tcpci = tcpc_to_tcpci(tcpc);
	unsigned int reg;

	reg = dm_i2c_reg_read(tcpci->dev, TCPC_POWER_STATUS);
	if (reg < 0)
		return reg;

	return !!(reg & TCPC_POWER_STATUS_VBUS_PRES);
}

static int tcpci_set_vbus(struct tcpc_dev *tcpc, bool source, bool sink)
{
	struct tcpci *tcpci = tcpc_to_tcpci(tcpc);
	int ret;

	/* Disable both source and sink first before enabling anything */

	if (!source) {
		ret = dm_i2c_reg_write(tcpci->dev, TCPC_COMMAND,
				       TCPC_CMD_DISABLE_SRC_VBUS);
		if (ret < 0)
			return ret;
	}

	if (!sink) {
		ret = dm_i2c_reg_write(tcpci->dev, TCPC_COMMAND,
				       TCPC_CMD_DISABLE_SINK_VBUS);
		if (ret < 0)
			return ret;
	}

	if (source) {
		ret = dm_i2c_reg_write(tcpci->dev, TCPC_COMMAND,
				       TCPC_CMD_SRC_VBUS_DEFAULT);
		if (ret < 0)
			return ret;
	}

	if (sink) {
		ret = dm_i2c_reg_write(tcpci->dev, TCPC_COMMAND,
				       TCPC_CMD_SINK_VBUS);
		if (ret < 0)
			return ret;
	}

	return 0;
}

static int tcpci_pd_transmit(struct tcpc_dev *tcpc,
			     enum tcpm_transmit_type type,
			     const struct pd_message *msg,
			     unsigned int negotiated_rev)
{
	struct tcpci *tcpci = tcpc_to_tcpci(tcpc);
	u16 header = msg ? le16_to_cpu(msg->header) : 0;
	unsigned int reg, cnt;
	int ret;

	cnt = msg ? pd_header_cnt(header) * 4 : 0;
	ret = dm_i2c_reg_write(tcpci->dev, TCPC_TX_BYTE_CNT, cnt + 2);
	if (ret < 0)
		return ret;

	ret = tcpci_write16(tcpci, TCPC_TX_HDR, header);
	if (ret < 0)
		return ret;

	if (cnt > 0) {
		ret = tcpci_block_write(tcpci, TCPC_TX_DATA,
				       (u8 *)&msg->payload, cnt);
		if (ret < 0)
			return ret;
	}

	reg = (PD_RETRY_COUNT << TCPC_TRANSMIT_RETRY_SHIFT) |
		(type << TCPC_TRANSMIT_TYPE_SHIFT);
	ret = dm_i2c_reg_write(tcpci->dev, TCPC_TRANSMIT, reg);
	if (ret < 0)
		return ret;

	return 0;
}

static int tcpci_init(struct tcpc_dev *tcpc)
{
	struct tcpci *tcpci = tcpc_to_tcpci(tcpc);
	unsigned int timeout = 0; /* XXX */
	unsigned int reg;
	int ret;

	while (timeout < 100) {
		reg = dm_i2c_reg_read(tcpci->dev, TCPC_POWER_STATUS);
		if (reg < 0)
			return reg;
		if (!(reg & TCPC_POWER_STATUS_UNINIT))
			break;
		timeout++;
		udelay(200);
	}
	if (timeout >= 100)
		return -ETIMEDOUT;

	/* Handle vendor init */
	if (tcpci->data->init) {
		ret = tcpci->data->init(tcpci, tcpci->data);
		if (ret < 0)
			return ret;
	}

	/* Clear all events */
	ret = tcpci_write16(tcpci, TCPC_ALERT, 0xffff);
	if (ret < 0)
		return ret;

	if (tcpci->controls_vbus)
		reg = TCPC_POWER_STATUS_VBUS_PRES;
	else
		reg = 0;
	ret = dm_i2c_reg_write(tcpci->dev, TCPC_POWER_STATUS_MASK, reg);
	if (ret < 0)
		return ret;

	/* Enable Vbus detection */
	ret = dm_i2c_reg_write(tcpci->dev, TCPC_COMMAND,
			       TCPC_CMD_ENABLE_VBUS_DETECT);
	if (ret < 0)
		return ret;

	reg = TCPC_ALERT_TX_SUCCESS | TCPC_ALERT_TX_FAILED |
		TCPC_ALERT_TX_DISCARDED | TCPC_ALERT_RX_STATUS |
		TCPC_ALERT_RX_HARD_RST | TCPC_ALERT_CC_STATUS;
	if (tcpci->controls_vbus)
		reg |= TCPC_ALERT_POWER_STATUS;
	return tcpci_write16(tcpci, TCPC_ALERT_MASK, reg);
}

static void tcpci_poll_event(struct tcpc_dev *tcpc)
{
	u16 status;
	struct tcpci *tcpci = tcpc_to_tcpci(tcpc);

	if (tcpci->gpio_cc_int_present)
		if (!dm_gpio_get_value(&tcpci->gpio_cc_int))
			return;

	tcpci_read16(tcpci, TCPC_ALERT, &status);

	/*
	 * Clear alert status for everything except RX_STATUS, which shouldn't
	 * be cleared until we have successfully retrieved message.
	 */
	if (status & ~TCPC_ALERT_RX_STATUS)
		tcpci_write16(tcpci, TCPC_ALERT,
			      status & ~TCPC_ALERT_RX_STATUS);

	if (status & TCPC_ALERT_CC_STATUS)
		tcpm_cc_change(tcpci->port);

	if (status & TCPC_ALERT_POWER_STATUS) {
		unsigned int reg;

		reg = dm_i2c_reg_read(tcpci->dev, TCPC_POWER_STATUS_MASK);
		if (reg < 0)
			return;

		/*
		 * If power status mask has been reset, then the TCPC
		 * has reset.
		 */
		if (reg == 0xff)
			tcpm_tcpc_reset(tcpci->port);
		else
			tcpm_vbus_change(tcpci->port);
	}

	if (status & TCPC_ALERT_RX_STATUS) {
		struct pd_message msg;
		unsigned int cnt, payload_cnt;
		u16 header;

		cnt = dm_i2c_reg_read(tcpci->dev, TCPC_RX_BYTE_CNT);
		if (cnt < 0)
			return;
		/*
		 * 'cnt' corresponds to READABLE_BYTE_COUNT in section 4.4.14
		 * of the TCPCI spec [Rev 2.0 Ver 1.0 October 2017] and is
		 * defined in table 4-36 as one greater than the number of
		 * bytes received. And that number includes the header. So:
		 */
		if (cnt > 3)
			payload_cnt = cnt - (1 + sizeof(msg.header));
		else
			payload_cnt = 0;

		tcpci_read16(tcpci, TCPC_RX_HDR, &header);
		msg.header = cpu_to_le16(header);

		if (WARN_ON(payload_cnt > sizeof(msg.payload)))
			payload_cnt = sizeof(msg.payload);

		if (payload_cnt > 0)
			tcpci_block_read(tcpci, TCPC_RX_DATA,
					(u8 *)&msg.payload, payload_cnt);

		/* Read complete, clear RX status alert bit */
		tcpci_write16(tcpci, TCPC_ALERT, TCPC_ALERT_RX_STATUS);

		tcpm_pd_receive(tcpci->port, &msg);
	}

	if (status & TCPC_ALERT_RX_HARD_RST)
		tcpm_pd_hard_reset(tcpci->port);

	if (status & TCPC_ALERT_TX_SUCCESS)
		tcpm_pd_transmit_complete(tcpci->port, TCPC_TX_SUCCESS);
	else if (status & TCPC_ALERT_TX_DISCARDED)
		tcpm_pd_transmit_complete(tcpci->port, TCPC_TX_DISCARDED);
	else if (status & TCPC_ALERT_TX_FAILED)
		tcpm_pd_transmit_complete(tcpci->port, TCPC_TX_FAILED);
}

static int tcpci_enter_low_power_mode(struct tcpc_dev *tcpc,
				      bool attached, bool pd_capable)
{
	int ret;
	struct tcpci *tcpci = tcpc_to_tcpci(tcpc);
	unsigned int reg;

	/* Disable chip interrupts before unregistering port */
	ret = tcpci_write16(tcpci, TCPC_ALERT_MASK, 0);
	if (ret < 0)
		return ret;

	reg = dm_i2c_reg_read(tcpci->dev, TCPC_BMCIO_CTRL);
	if (reg < 0)
		return reg;
	/*
	 * For Type-C devices with PD capability, Only disable VBUS detect,
	 * do not diable 24M oscillator for BMC communication. Otherwise,
	 * data packets cannot be received.
	 */
	if (attached && pd_capable)
		reg &= ~TCPC_BMCIO_VBUS_DETECT_MASK;
	else
		reg &= ~(TCPC_BMCIO_VBUS_DETECT_MASK | TCPC_BMCIO_24M_OSC_MASK);
	return dm_i2c_reg_write(tcpci->dev, TCPC_BMCIO_CTRL, reg);
}

static int tcpci_parse_config(struct tcpci *tcpci)
{
	tcpci->controls_vbus = true; /* XXX */

	tcpci->tcpc.connector_node = dev_read_subnode(tcpci->dev, "connector");
	if (!ofnode_valid(tcpci->tcpc.connector_node)) {
		printf("%s: 'connector' node is not found\n", __func__);
		return -EINVAL;
	}

	return 0;
}

struct tcpci *tcpci_register_port(struct udevice *dev, struct tcpci_data *data)
{
	struct tcpci *tcpci;
	int err;

	tcpci = devm_kzalloc(dev, sizeof(*tcpci), GFP_KERNEL);
	if (!tcpci)
		return ERR_PTR(-ENOMEM);

	err = gpio_request_by_name(dev, "int-n-gpios", 0, &tcpci->gpio_cc_int, GPIOD_IS_IN);
	if (err) {
		printf("%s: fail to get int GPIO: err=%d\n", __func__, err);
		tcpci->gpio_cc_int_present = false;
	} else {
		tcpci->gpio_cc_int_present = true;
	}

	tcpci->dev = dev;
	tcpci->data = data;

	tcpci->tcpc.init = tcpci_init;
	tcpci->tcpc.get_vbus = tcpci_get_vbus;
	tcpci->tcpc.set_vbus = tcpci_set_vbus;
	tcpci->tcpc.set_cc = tcpci_set_cc;
	tcpci->tcpc.get_cc = tcpci_get_cc;
	tcpci->tcpc.set_polarity = tcpci_set_polarity;
	tcpci->tcpc.set_vconn = tcpci_set_vconn;
	tcpci->tcpc.start_toggling = tcpci_start_toggling;

	tcpci->tcpc.set_pd_rx = tcpci_set_pd_rx;
	tcpci->tcpc.set_roles = tcpci_set_roles;
	tcpci->tcpc.pd_transmit = tcpci_pd_transmit;
	tcpci->tcpc.poll_event = tcpci_poll_event;
	tcpci->tcpc.enter_low_power_mode = tcpci_enter_low_power_mode;

	err = tcpci_parse_config(tcpci);
	if (err < 0)
		return ERR_PTR(err);

	tcpci->port = tcpm_port_init(tcpci->dev, &tcpci->tcpc);
	if (IS_ERR(tcpci->port)) {
		printf("%s: failed to tcpm port init\n", __func__);
		return ERR_CAST(tcpci->port);
	}

	tcpm_poll_event(tcpci->port);

	return tcpci;
}
EXPORT_SYMBOL_GPL(tcpci_register_port);

void tcpci_unregister_port(struct tcpci *tcpci)
{
	tcpm_uninit_port(tcpci->port);
}
EXPORT_SYMBOL_GPL(tcpci_unregister_port);

int tcpci_get_voltage_fun(struct tcpci *tcpci)
{
	return tcpm_get_voltage(tcpci->port);
}
EXPORT_SYMBOL_GPL(tcpci_get_voltage_fun);

int tcpci_get_current_fun(struct tcpci *tcpci)
{
	return tcpm_get_current(tcpci->port);
}
EXPORT_SYMBOL_GPL(tcpci_get_current_fun);

int tcpci_get_online_fun(struct tcpci *tcpci)
{
	return tcpm_get_online(tcpci->port);
}
EXPORT_SYMBOL_GPL(tcpci_get_online_fun);

static int tcpci_probe(struct udevice *dev)
{
	struct tcpci_chip *chip = dev_get_priv(dev);
	int err;
	u16 val = 0;

	chip->udev = dev;

	/* Disable chip interrupts before requesting irq */
	err = tcpci_write16(chip->tcpci, TCPC_ALERT_MASK, val);
	if (err < 0)
		return err;

	chip->tcpci = tcpci_register_port(chip->udev, &chip->data);
	if (IS_ERR(chip->tcpci))
		return PTR_ERR(chip->tcpci);

	return 0;
}

static int tcpci_remove(struct udevice *dev)
{
	struct tcpci_chip *chip = dev_get_priv(dev);
	int err;

	/* Disable chip interrupts before unregistering port */
	err = tcpci_write16(chip->tcpci, TCPC_ALERT_MASK, 0);
	if (err < 0)
		return err;

	tcpci_unregister_port(chip->tcpci);

	return 0;
}

static int tcpci_get_voltage(struct udevice *dev)
{
	struct tcpci_chip *chip = dev_get_priv(dev);

	return tcpm_get_voltage(chip->tcpci->port);
}

static int tcpci_get_current(struct udevice *dev)
{
	struct tcpci_chip *chip = dev_get_priv(dev);

	return tcpm_get_current(chip->tcpci->port);
}

static int tcpci_get_online(struct udevice *dev)
{
	struct tcpci_chip *chip = dev_get_priv(dev);

	return tcpm_get_online(chip->tcpci->port);
}

static struct dm_power_delivery_ops tcpci_ops = {
	.get_voltage = tcpci_get_voltage,
	.get_current = tcpci_get_current,
	.get_online = tcpci_get_online,
};

static const struct udevice_id tcpci_ids[] = {
	{ .compatible = "nxp,ptn5110", },
	{},
};

U_BOOT_DRIVER(tcpci) = {
	.name = "tcpci",
	.id = UCLASS_PD,
	.of_match = tcpci_ids,
	.ops = &tcpci_ops,
	.probe = tcpci_probe,
	.remove = tcpci_remove,
	.priv_auto_alloc_size = sizeof(struct tcpci_chip),
}

MODULE_DESCRIPTION("USB Type-C Port Controller Interface driver");
MODULE_LICENSE("GPL");
