// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2016-2017 Google, Inc
 *
 * Fairchild FUSB302 Type-C Chip Driver
 */

#include <dm.h>
#include <i2c.h>
#include <asm/gpio.h>
#include <power/power_delivery/tcpm.h>
#include <power/power_delivery/power_delivery.h>
#include "fusb302_reg.h"

/*
 * When the device is SNK, BC_LVL interrupt is used to monitor cc pins
 * for the current capability offered by the SRC. As FUSB302 chip fires
 * the BC_LVL interrupt on PD signalings, cc lvl should be handled after
 * a delay to avoid measuring on PD activities. The delay is slightly
 * longer than PD_T_PD_DEBPUNCE (10-20ms).
 */
#define T_BC_LVL_DEBOUNCE_DELAY_MS 30
#define msleep(a)	udelay(a * 1000)
#define usleep_range(a, b) udelay((b))

enum toggling_mode {
	TOGGLING_MODE_OFF,
	TOGGLING_MODE_DRP,
	TOGGLING_MODE_SNK,
	TOGGLING_MODE_SRC,
};

enum src_current_status {
	SRC_CURRENT_DEFAULT,
	SRC_CURRENT_MEDIUM,
	SRC_CURRENT_HIGH,
};

static const u8 ra_mda_value[] = {
	[SRC_CURRENT_DEFAULT] = 4,	/* 210mV */
	[SRC_CURRENT_MEDIUM] = 9,	/* 420mV */
	[SRC_CURRENT_HIGH] = 18,	/* 798mV */
};

static const u8 rd_mda_value[] = {
	[SRC_CURRENT_DEFAULT] = 38,	/* 1638mV */
	[SRC_CURRENT_MEDIUM] = 38,	/* 1638mV */
	[SRC_CURRENT_HIGH] = 61,	/* 2604mV */
};

#define LOG_BUFFER_ENTRIES	1024
#define LOG_BUFFER_ENTRY_SIZE	128

struct fusb302_chip {
	struct udevice *udev;
	struct udevice *vbus_regulator;
	struct ofnode *child_node;
	struct tcpm_port *tcpm_port;
	struct tcpc_dev tcpc_dev;
	struct gpio_desc gpio_cc_int;

	int irq;

	enum toggling_mode toggling_mode;
	enum src_current_status src_current_status;
	bool intr_togdone;
	bool intr_bc_lvl;
	bool intr_comp_chng;

	/* port status */
	bool vconn_on;
	bool vbus_on;
	bool charge_on;
	bool vbus_present;
	bool gpio_cc_int_present;
	enum typec_cc_polarity cc_polarity;
	enum typec_cc_status cc1;
	enum typec_cc_status cc2;
};

static int fusb302_i2c_write(struct fusb302_chip *chip,
			     u8 address, u8 data)
{
	int ret = 0;

	ret = dm_i2c_write(chip->udev, address, &data, 1);
	if (ret)
		printf("%s: cannot write 0x%02x to 0x%02x, ret=%d\n",
			__func__, data, address, ret);

	return ret;
}

static int fusb302_i2c_block_write(struct fusb302_chip *chip, u8 address,
				   u8 length, const u8 *data)
{
	int ret = 0;

	if (length <= 0)
		return ret;

	ret = dm_i2c_write(chip->udev, address, data, length);
	if (ret)
		printf("%s: cannot block write 0x%02x, len=%d, ret=%d\n",
			__func__, address, length, ret);

	return ret;
}

static int fusb302_i2c_read(struct fusb302_chip *chip,
			    u8 address, u8 *data)
{
	int ret = 0;

	ret = dm_i2c_read(chip->udev, address, data, 1);
	if (ret)
		printf("%s: cannot read %02x, ret=%d\n",
			__func__, address, ret);

	return ret;
}

static int fusb302_i2c_block_read(struct fusb302_chip *chip, u8 address,
				  u8 length, u8 *data)
{
	int ret = 0;

	if (length <= 0)
		return ret;

	ret = dm_i2c_read(chip->udev, address, data, length);
	if (ret)
		printf("%s: cannot block read 0x%02x, len=%d, ret=%d\n",
			__func__, address, length, ret);
	return ret;
}

static int fusb302_i2c_mask_write(struct fusb302_chip *chip, u8 address,
				  u8 mask, u8 value)
{
	int ret = 0;
	u8 data;

	ret = fusb302_i2c_read(chip, address, &data);
	if (ret)
		return ret;
	data &= ~mask;
	data |= value;
	ret = fusb302_i2c_write(chip, address, data);
	if (ret)
		return ret;

	return ret;
}

static int fusb302_i2c_set_bits(struct fusb302_chip *chip, u8 address,
				u8 set_bits)
{
	return fusb302_i2c_mask_write(chip, address, 0x00, set_bits);
}

static int fusb302_i2c_clear_bits(struct fusb302_chip *chip, u8 address,
				  u8 clear_bits)
{
	return fusb302_i2c_mask_write(chip, address, clear_bits, 0x00);
}

static int fusb302_sw_reset(struct fusb302_chip *chip)
{
	int ret = 0;

	ret = fusb302_i2c_write(chip, FUSB_REG_RESET,
				FUSB_REG_RESET_SW_RESET);
	if (ret)
		printf("cannot sw reset the fusb302(%d)\n", ret);
	else
		debug("fusb302 sw reset finished\n");

	return ret;
}

static int fusb302_enable_tx_auto_retries(struct fusb302_chip *chip, u8 retry_count)
{
	int ret = 0;

	ret = fusb302_i2c_set_bits(chip, FUSB_REG_CONTROL3, retry_count |
				   FUSB_REG_CONTROL3_AUTO_RETRY);

	return ret;
}

/*
 * mask all interrupt on the chip
 */
static int fusb302_mask_interrupt(struct fusb302_chip *chip)
{
	int ret = 0;

	ret = fusb302_i2c_write(chip, FUSB_REG_MASK, 0xFF);
	if (ret)
		return ret;
	ret = fusb302_i2c_write(chip, FUSB_REG_MASKA, 0xFF);
	if (ret)
		return ret;
	ret = fusb302_i2c_write(chip, FUSB_REG_MASKB, 0xFF);
	if (ret)
		return ret;
	ret = fusb302_i2c_set_bits(chip, FUSB_REG_CONTROL0,
				   FUSB_REG_CONTROL0_INT_MASK);
		return ret;
}

/*
 * initialize interrupt on the chip
 * - unmasked interrupt: VBUS_OK
 */
static int fusb302_init_interrupt(struct fusb302_chip *chip)
{
	int ret = 0;

	ret = fusb302_i2c_write(chip, FUSB_REG_MASK,
				0xFF & ~FUSB_REG_MASK_VBUSOK);
	if (ret)
		return ret;
	ret = fusb302_i2c_write(chip, FUSB_REG_MASKA, 0xFF);
	if (ret)
		return ret;
	ret = fusb302_i2c_write(chip, FUSB_REG_MASKB, 0xFF);
	if (ret)
		return ret;
	ret = fusb302_i2c_clear_bits(chip, FUSB_REG_CONTROL0,
				     FUSB_REG_CONTROL0_INT_MASK);
	return ret;
}

static int fusb302_set_power_mode(struct fusb302_chip *chip, u8 power_mode)
{
	int ret = 0;

	ret = fusb302_i2c_write(chip, FUSB_REG_POWER, power_mode);

	return ret;
}

static int tcpm_init(struct tcpc_dev *dev)
{
	struct fusb302_chip *chip = container_of(dev, struct fusb302_chip,
						 tcpc_dev);
	int ret = 0;
	u8 data;

	ret = fusb302_sw_reset(chip);
	if (ret)
		return ret;
	ret = fusb302_enable_tx_auto_retries(chip, FUSB_REG_CONTROL3_N_RETRIES_3);
	if (ret)
		return ret;
	ret = fusb302_init_interrupt(chip);
	if (ret)
		return ret;
	ret = fusb302_set_power_mode(chip, FUSB_REG_POWER_PWR_ALL);
	if (ret)
		return ret;
	ret = fusb302_i2c_read(chip, FUSB_REG_STATUS0, &data);
	if (ret)
		return ret;
	chip->vbus_present = !!(data & FUSB_REG_STATUS0_VBUSOK);
	ret = fusb302_i2c_read(chip, FUSB_REG_DEVICE_ID, &data);
	if (ret)
		return ret;
	printf("fusb302 device ID: 0x%02x\n", data);

	return ret;
}

static int tcpm_get_vbus(struct tcpc_dev *dev)
{
	struct fusb302_chip *chip = container_of(dev, struct fusb302_chip,
						 tcpc_dev);
	return chip->vbus_present ? 1 : 0;
}

#if 0
static int tcpm_get_current_limit(struct tcpc_dev *dev)
{

	struct fusb302_chip *chip = container_of(dev, struct fusb302_chip,
						 tcpc_dev);
	int current_limit = 0;
	unsigned long timeout;

	if (!chip->extcon)
		return 0;

	/*
	 * USB2 Charger detection may still be in progress when we get here,
	 * this can take upto 600ms, wait 800ms max.
	 */
	timeout = jiffies + msecs_to_jiffies(800);
	do {
		if (extcon_get_state(chip->extcon, EXTCON_CHG_USB_SDP) == 1)
			current_limit = 500;

		if (extcon_get_state(chip->extcon, EXTCON_CHG_USB_CDP) == 1 ||
		    extcon_get_state(chip->extcon, EXTCON_CHG_USB_ACA) == 1)
			current_limit = 1500;

		if (extcon_get_state(chip->extcon, EXTCON_CHG_USB_DCP) == 1)
			current_limit = 2000;

		msleep(50);
	} while (current_limit == 0 && time_before(jiffies, timeout));

	return current_limit;
}
#endif

static int fusb302_set_src_current(struct fusb302_chip *chip,
				   enum src_current_status status)
{
	int ret = 0;

	chip->src_current_status = status;
	switch (status) {
	case SRC_CURRENT_DEFAULT:
		ret = fusb302_i2c_mask_write(chip, FUSB_REG_CONTROL0,
					     FUSB_REG_CONTROL0_HOST_CUR_MASK,
					     FUSB_REG_CONTROL0_HOST_CUR_DEF);
		break;
	case SRC_CURRENT_MEDIUM:
		ret = fusb302_i2c_mask_write(chip, FUSB_REG_CONTROL0,
					     FUSB_REG_CONTROL0_HOST_CUR_MASK,
					     FUSB_REG_CONTROL0_HOST_CUR_MED);
		break;
	case SRC_CURRENT_HIGH:
		ret = fusb302_i2c_mask_write(chip, FUSB_REG_CONTROL0,
					     FUSB_REG_CONTROL0_HOST_CUR_MASK,
					     FUSB_REG_CONTROL0_HOST_CUR_HIGH);
		break;
	default:
		break;
	}

	return ret;
}

static int fusb302_set_toggling(struct fusb302_chip *chip,
				enum toggling_mode mode)
{
	int ret = 0;

	/* first disable toggling */
	ret = fusb302_i2c_clear_bits(chip, FUSB_REG_CONTROL2,
				     FUSB_REG_CONTROL2_TOGGLE);
	if (ret)
		return ret;
	/* mask interrupts for SRC or SNK */
	ret = fusb302_i2c_set_bits(chip, FUSB_REG_MASK,
				   FUSB_REG_MASK_BC_LVL |
				   FUSB_REG_MASK_COMP_CHNG);
	if (ret)
		return ret;
	chip->intr_bc_lvl = false;
	chip->intr_comp_chng = false;
	/* configure toggling mode: none/snk/src/drp */
	switch (mode) {
	case TOGGLING_MODE_OFF:
		ret = fusb302_i2c_mask_write(chip, FUSB_REG_CONTROL2,
					     FUSB_REG_CONTROL2_MODE_MASK,
					     FUSB_REG_CONTROL2_MODE_NONE);
		break;
	case TOGGLING_MODE_SNK:
		ret = fusb302_i2c_mask_write(chip, FUSB_REG_CONTROL2,
					     FUSB_REG_CONTROL2_MODE_MASK,
					     FUSB_REG_CONTROL2_MODE_UFP);
		break;
	case TOGGLING_MODE_SRC:
		ret = fusb302_i2c_mask_write(chip, FUSB_REG_CONTROL2,
					     FUSB_REG_CONTROL2_MODE_MASK,
					     FUSB_REG_CONTROL2_MODE_DFP);
		break;
	case TOGGLING_MODE_DRP:
		ret = fusb302_i2c_mask_write(chip, FUSB_REG_CONTROL2,
					     FUSB_REG_CONTROL2_MODE_MASK,
					     FUSB_REG_CONTROL2_MODE_DRP);
		break;
	default:
		break;
	}

	if (ret)
		return ret;

	if (mode == TOGGLING_MODE_OFF) {
		/* mask TOGDONE interrupt */
		ret = fusb302_i2c_set_bits(chip, FUSB_REG_MASKA,
					   FUSB_REG_MASKA_TOGDONE);
		if (ret)
			return ret;
		chip->intr_togdone = false;
	} else {
		/* Datasheet says vconn MUST be off when toggling */
		if (chip->vconn_on)
			printf("%s: Vconn is on during toggle start\n", __func__);
		/* unmask TOGDONE interrupt */
		ret = fusb302_i2c_clear_bits(chip, FUSB_REG_MASKA,
					     FUSB_REG_MASKA_TOGDONE);
		if (ret)
			return ret;
		chip->intr_togdone = true;
		/* start toggling */
		ret = fusb302_i2c_set_bits(chip, FUSB_REG_CONTROL2,
					   FUSB_REG_CONTROL2_TOGGLE);
		if (ret)
			return ret;
		/* during toggling, consider cc as Open */
		chip->cc1 = TYPEC_CC_OPEN;
		chip->cc2 = TYPEC_CC_OPEN;
	}
	chip->toggling_mode = mode;

	return ret;
}

static const char * const typec_cc_status_name[] = {
	[TYPEC_CC_OPEN]		= "Open",
	[TYPEC_CC_RA]		= "Ra",
	[TYPEC_CC_RD]		= "Rd",
	[TYPEC_CC_RP_DEF]	= "Rp-def",
	[TYPEC_CC_RP_1_5]	= "Rp-1.5",
	[TYPEC_CC_RP_3_0]	= "Rp-3.0",
};

static const enum src_current_status cc_src_current[] = {
	[TYPEC_CC_OPEN]		= SRC_CURRENT_DEFAULT,
	[TYPEC_CC_RA]		= SRC_CURRENT_DEFAULT,
	[TYPEC_CC_RD]		= SRC_CURRENT_DEFAULT,
	[TYPEC_CC_RP_DEF]	= SRC_CURRENT_DEFAULT,
	[TYPEC_CC_RP_1_5]	= SRC_CURRENT_MEDIUM,
	[TYPEC_CC_RP_3_0]	= SRC_CURRENT_HIGH,
};

static int tcpm_set_cc(struct tcpc_dev *dev, enum typec_cc_status cc)
{
	struct fusb302_chip *chip = container_of(dev, struct fusb302_chip,
						 tcpc_dev);
	u8 switches0_mask = FUSB_REG_SWITCHES0_CC1_PU_EN |
			    FUSB_REG_SWITCHES0_CC2_PU_EN |
			    FUSB_REG_SWITCHES0_CC1_PD_EN |
			    FUSB_REG_SWITCHES0_CC2_PD_EN;
	u8 rd_mda, switches0_data = 0x00;
	int ret = 0;

	switch (cc) {
	case TYPEC_CC_OPEN:
		break;
	case TYPEC_CC_RD:
		switches0_data |= FUSB_REG_SWITCHES0_CC1_PD_EN |
				  FUSB_REG_SWITCHES0_CC2_PD_EN;
		break;
	case TYPEC_CC_RP_DEF:
	case TYPEC_CC_RP_1_5:
	case TYPEC_CC_RP_3_0:
		switches0_data |= (chip->cc_polarity == TYPEC_POLARITY_CC1) ?
				  FUSB_REG_SWITCHES0_CC1_PU_EN :
				  FUSB_REG_SWITCHES0_CC2_PU_EN;
		break;
	default:
		printf("%s: unsupported cc value %s\n",
			__func__, typec_cc_status_name[cc]);
		ret = -EINVAL;
		goto done;
	}

	ret = fusb302_set_toggling(chip, TOGGLING_MODE_OFF);
	if (ret) {
		printf("%s: cannot set toggling mode(%d)\n", __func__, ret);
		goto done;
	}

	ret = fusb302_i2c_mask_write(chip, FUSB_REG_SWITCHES0,
				     switches0_mask, switches0_data);
	if (ret) {
		printf("%s: cannot set pull-up/-down(%d)\n", __func__, ret);
		goto done;
	}
	/* reset the cc status */
	chip->cc1 = TYPEC_CC_OPEN;
	chip->cc2 = TYPEC_CC_OPEN;

	/* adjust current for SRC */
	ret = fusb302_set_src_current(chip, cc_src_current[cc]);
	if (ret) {
		printf("%s: cannot set src current %s(%d)\n",
			__func__, typec_cc_status_name[cc], ret);
		goto done;
	}

	/* enable/disable interrupts, BC_LVL for SNK and COMP_CHNG for SRC */
	switch (cc) {
	case TYPEC_CC_RP_DEF:
	case TYPEC_CC_RP_1_5:
	case TYPEC_CC_RP_3_0:
		rd_mda = rd_mda_value[cc_src_current[cc]];
		ret = fusb302_i2c_write(chip, FUSB_REG_MEASURE, rd_mda);
		if (ret) {
			printf("%s: cannot set SRC measure value(%d)\n",
				__func__, ret);
			goto done;
		}
		ret = fusb302_i2c_mask_write(chip, FUSB_REG_MASK,
					     FUSB_REG_MASK_BC_LVL |
					     FUSB_REG_MASK_COMP_CHNG,
					     FUSB_REG_MASK_BC_LVL);
		if (ret) {
			printf("%s: cannot set SRC interrupt(%d)\n",
				__func__, ret);
			goto done;
		}
		chip->intr_comp_chng = true;
		break;
	case TYPEC_CC_RD:
		ret = fusb302_i2c_mask_write(chip, FUSB_REG_MASK,
					     FUSB_REG_MASK_BC_LVL |
					     FUSB_REG_MASK_COMP_CHNG,
					     FUSB_REG_MASK_COMP_CHNG);
		if (ret) {
			printf("%s: cannot set SRC interrupt(%d)\n",
				__func__, ret);
			goto done;
		}
		chip->intr_bc_lvl = true;
		break;
	default:
		break;
	}
done:
	return ret;
}

static int tcpm_get_cc(struct tcpc_dev *dev, enum typec_cc_status *cc1,
		       enum typec_cc_status *cc2)
{
	struct fusb302_chip *chip = container_of(dev, struct fusb302_chip,
						 tcpc_dev);

	*cc1 = chip->cc1;
	*cc2 = chip->cc2;
	debug("get cc1 = %s, cc2 = %s\n", typec_cc_status_name[*cc1],
	       typec_cc_status_name[*cc2]);

	return 0;
}

static int tcpm_set_polarity(struct tcpc_dev *dev,
			     enum typec_cc_polarity polarity)
{
	return 0;
}

static int tcpm_set_vconn(struct tcpc_dev *dev, bool on)
{
	struct fusb302_chip *chip = container_of(dev, struct fusb302_chip,
						 tcpc_dev);
	int ret = 0;
	u8 switches0_data = 0x00;
	u8 switches0_mask = FUSB_REG_SWITCHES0_VCONN_CC1 |
			    FUSB_REG_SWITCHES0_VCONN_CC2;

	if (chip->vconn_on == on) {
		printf("vconn is already %s\n", on ? "On" : "Off");
		goto done;
	}
	if (on) {
		switches0_data = (chip->cc_polarity == TYPEC_POLARITY_CC1) ?
				 FUSB_REG_SWITCHES0_VCONN_CC2 :
				 FUSB_REG_SWITCHES0_VCONN_CC1;
	}
	ret = fusb302_i2c_mask_write(chip, FUSB_REG_SWITCHES0,
				     switches0_mask, switches0_data);
	if (ret)
		goto done;
	debug("%s: vconn := %s\n", __func__, on ? "On" : "Off");
done:
	return ret;
}

static int tcpm_set_vbus(struct tcpc_dev *dev, bool on, bool charge)
{
#if 0
	struct fusb302_chip *chip = container_of(dev, struct fusb302_chip,
						 tcpc_dev);
	int ret = 0;

	mutex_lock(&chip->lock);
	if (chip->vbus_on == on) {
		printf("%s: vbus is already %s\n", __func__, on ? "On" : "Off");
	} else {
		if (on)
			ret = regulator_enable(chip->vbus);
		else
			ret = regulator_disable(chip->vbus);
		if (ret < 0) {
			printf("%s: cannot %s vbus regulator(%d)\n",
				__func__, on ? "enable" : "disable", ret);
			goto done;
		}
		chip->vbus_on = on;
		debug("%s: vbus := %s\n", __func__, on ? "On" : "Off");
	}
	if (chip->charge_on == charge)
		debug("%s: charge is already %s\n",
			__func__, charge ? "On" : "Off");
	else
		chip->charge_on = charge;

done:
	mutex_unlock(&chip->lock);
#endif

	return 0;
}

static int fusb302_pd_tx_flush(struct fusb302_chip *chip)
{
	return fusb302_i2c_set_bits(chip, FUSB_REG_CONTROL0,
				    FUSB_REG_CONTROL0_TX_FLUSH);
}

static int fusb302_pd_rx_flush(struct fusb302_chip *chip)
{
	return fusb302_i2c_set_bits(chip, FUSB_REG_CONTROL1,
				    FUSB_REG_CONTROL1_RX_FLUSH);
}

static int fusb302_pd_set_auto_goodcrc(struct fusb302_chip *chip, bool on)
{
	if (on)
		return fusb302_i2c_set_bits(chip, FUSB_REG_SWITCHES1,
					    FUSB_REG_SWITCHES1_AUTO_GCRC);
	return fusb302_i2c_clear_bits(chip, FUSB_REG_SWITCHES1,
					    FUSB_REG_SWITCHES1_AUTO_GCRC);
}

static int fusb302_pd_set_interrupts(struct fusb302_chip *chip, bool on)
{
	int ret = 0;
	u8 mask_interrupts = FUSB_REG_MASK_COLLISION;
	u8 maska_interrupts = FUSB_REG_MASKA_RETRYFAIL |
			      FUSB_REG_MASKA_HARDSENT |
			      FUSB_REG_MASKA_TX_SUCCESS |
			      FUSB_REG_MASKA_HARDRESET;
	u8 maskb_interrupts = FUSB_REG_MASKB_GCRCSENT;

	ret = on ?
		fusb302_i2c_clear_bits(chip, FUSB_REG_MASK, mask_interrupts) :
		fusb302_i2c_set_bits(chip, FUSB_REG_MASK, mask_interrupts);
	if (ret)
		return ret;
	ret = on ?
		fusb302_i2c_clear_bits(chip, FUSB_REG_MASKA, maska_interrupts) :
		fusb302_i2c_set_bits(chip, FUSB_REG_MASKA, maska_interrupts);
	if (ret)
		return ret;
	ret = on ?
		fusb302_i2c_clear_bits(chip, FUSB_REG_MASKB, maskb_interrupts) :
		fusb302_i2c_set_bits(chip, FUSB_REG_MASKB, maskb_interrupts);
	return ret;
}

static int tcpm_set_pd_rx(struct tcpc_dev *dev, bool on)
{
	struct fusb302_chip *chip = container_of(dev, struct fusb302_chip,
						 tcpc_dev);
	int ret = 0;

	ret = fusb302_pd_rx_flush(chip);
	if (ret) {
		printf("%s: cannot flush pd rx buffer(%d)\n", __func__, ret);
		goto done;
	}
	ret = fusb302_pd_tx_flush(chip);
	if (ret) {
		printf("%s: cannot flush pd tx buffer(%d)\n", __func__, ret);
		goto done;
	}
	ret = fusb302_pd_set_auto_goodcrc(chip, on);
	if (ret) {
		printf("%s: cannot turn %s auto GCRC(%d)\n",
			__func__, on ? "on" : "off", ret);
		goto done;
	}
	ret = fusb302_pd_set_interrupts(chip, on);
	if (ret) {
		printf("%s: cannot turn %s pd interrupts(%d)\n",
			__func__, on ? "on" : "off", ret);
		goto done;
	}
	debug("%s: pd := %s\n", __func__, on ? "on" : "off");
done:
	return ret;
}

static const char * const typec_role_name[] = {
	[TYPEC_SINK]		= "Sink",
	[TYPEC_SOURCE]		= "Source",
};

static const char * const typec_data_role_name[] = {
	[TYPEC_DEVICE]		= "Device",
	[TYPEC_HOST]		= "Host",
};

static int tcpm_set_roles(struct tcpc_dev *dev, bool attached,
			  enum typec_role pwr, enum typec_data_role data)
{
	struct fusb302_chip *chip = container_of(dev, struct fusb302_chip,
						 tcpc_dev);
	int ret = 0;
	u8 switches1_mask = FUSB_REG_SWITCHES1_POWERROLE |
			    FUSB_REG_SWITCHES1_DATAROLE;
	u8 switches1_data = 0x00;

	if (pwr == TYPEC_SOURCE)
		switches1_data |= FUSB_REG_SWITCHES1_POWERROLE;
	if (data == TYPEC_HOST)
		switches1_data |= FUSB_REG_SWITCHES1_DATAROLE;
	ret = fusb302_i2c_mask_write(chip, FUSB_REG_SWITCHES1,
				     switches1_mask, switches1_data);
	if (ret) {
		printf("unable to set pd header %s, %s, ret= %d\n",
			typec_role_name[pwr], typec_data_role_name[data], ret);
		goto done;
	}
	debug("%s: pd header : %s, %s\n", __func__, typec_role_name[pwr],
		typec_data_role_name[data]);
done:

	return ret;
}

static int tcpm_start_toggling(struct tcpc_dev *dev,
			       enum typec_port_type port_type,
			       enum typec_cc_status cc)
{
	struct fusb302_chip *chip = container_of(dev, struct fusb302_chip,
						 tcpc_dev);
	enum toggling_mode mode = TOGGLING_MODE_OFF;
	int ret = 0;

	switch (port_type) {
	case TYPEC_PORT_SRC:
		mode = TOGGLING_MODE_SRC;
		break;
	case TYPEC_PORT_SNK:
		mode = TOGGLING_MODE_SNK;
		break;
	case TYPEC_PORT_DRP:
		mode = TOGGLING_MODE_DRP;
		break;
	}

	ret = fusb302_set_src_current(chip, cc_src_current[cc]);
	if (ret) {
		printf("%s: unable to set src current %s, ret=%d",
			__func__, typec_cc_status_name[cc], ret);
		goto done;
	}
	ret = fusb302_set_toggling(chip, mode);
	if (ret) {
		printf("%s: unable to start drp toggling(%d)\n", __func__, ret);
		goto done;
	}
	printf("fusb302 start drp toggling\n");
done:

	return ret;
}

static int fusb302_pd_send_message(struct fusb302_chip *chip,
				   const struct pd_message *msg)
{
	int ret = 0;
	u8 buf[40];
	u8 pos = 0;
	int len;

	/* SOP tokens */
	buf[pos++] = FUSB302_TKN_SYNC1;
	buf[pos++] = FUSB302_TKN_SYNC1;
	buf[pos++] = FUSB302_TKN_SYNC1;
	buf[pos++] = FUSB302_TKN_SYNC2;

	len = pd_header_cnt_le(msg->header) * 4;
	/* plug 2 for header */
	len += 2;
	if (len > 0x1F) {
		printf("PD message too long %d (incl. header)", len);
		return -EINVAL;
	}
	/* packsym tells the FUSB302 chip that the next X bytes are payload */
	buf[pos++] = FUSB302_TKN_PACKSYM | (len & 0x1F);
	memcpy(&buf[pos], &msg->header, sizeof(msg->header));
	pos += sizeof(msg->header);

	len -= 2;
	memcpy(&buf[pos], msg->payload, len);
	pos += len;

	/* CRC */
	buf[pos++] = FUSB302_TKN_JAMCRC;
	/* EOP */
	buf[pos++] = FUSB302_TKN_EOP;
	/* turn tx off after sending message */
	buf[pos++] = FUSB302_TKN_TXOFF;
	/* start transmission */
	buf[pos++] = FUSB302_TKN_TXON;

	ret = fusb302_i2c_block_write(chip, FUSB_REG_FIFOS, pos, buf);
	if (ret)
		return ret;
	debug("sending PD message header: %x\n", msg->header);
	debug("sending PD message len: %d\n", len);

	return ret;
}

static int fusb302_pd_send_hardreset(struct fusb302_chip *chip)
{
	return fusb302_i2c_set_bits(chip, FUSB_REG_CONTROL3,
				    FUSB_REG_CONTROL3_SEND_HARDRESET);
}

static const char * const transmit_type_name[] = {
	[TCPC_TX_SOP]			= "SOP",
	[TCPC_TX_SOP_PRIME]		= "SOP'",
	[TCPC_TX_SOP_PRIME_PRIME]	= "SOP''",
	[TCPC_TX_SOP_DEBUG_PRIME]	= "DEBUG'",
	[TCPC_TX_SOP_DEBUG_PRIME_PRIME]	= "DEBUG''",
	[TCPC_TX_HARD_RESET]		= "HARD_RESET",
	[TCPC_TX_CABLE_RESET]		= "CABLE_RESET",
	[TCPC_TX_BIST_MODE_2]		= "BIST_MODE_2",
};

static int tcpm_pd_transmit(struct tcpc_dev *dev, enum tcpm_transmit_type type,
			    const struct pd_message *msg, unsigned int negotiated_rev)
{
	struct fusb302_chip *chip = container_of(dev, struct fusb302_chip,
						 tcpc_dev);
	int ret = 0;

	switch (type) {
	case TCPC_TX_SOP:
		/* nRetryCount 3 in P2.0 spec, whereas 2 in PD3.0 spec */
		ret = fusb302_enable_tx_auto_retries(chip, negotiated_rev > PD_REV20 ?
						     FUSB_REG_CONTROL3_N_RETRIES_2 :
						     FUSB_REG_CONTROL3_N_RETRIES_3);
		if (ret)
			printf("%s: Cannot update retry count(%d)\n",
				__func__, ret);

		ret = fusb302_pd_send_message(chip, msg);
		if (ret)
			printf("%s: cannot send PD message(%d)\n",
				__func__, ret);
		break;
	case TCPC_TX_HARD_RESET:
		ret = fusb302_pd_send_hardreset(chip);
		if (ret)
			printf("%s: cannot send hardreset(%d)\n",
				__func__, ret);
		break;
	default:
		printf("%s: type %s not supported",
			__func__, transmit_type_name[type]);
		ret = -EINVAL;
	}

	return ret;
}

static enum typec_cc_status fusb302_bc_lvl_to_cc(u8 bc_lvl)
{
	if (bc_lvl == FUSB_REG_STATUS0_BC_LVL_1230_MAX)
		return TYPEC_CC_RP_3_0;
	if (bc_lvl == FUSB_REG_STATUS0_BC_LVL_600_1230)
		return TYPEC_CC_RP_1_5;
	if (bc_lvl == FUSB_REG_STATUS0_BC_LVL_200_600)
		return TYPEC_CC_RP_DEF;
	return TYPEC_CC_OPEN;
}

static void fusb302_bc_lvl_handler(struct fusb302_chip *chip)
{
	int ret = 0;
	u8 status0;
	u8 bc_lvl;
	enum typec_cc_status cc_status;

	if (!chip->intr_bc_lvl) {
		printf("BC_LVL interrupt is turned off, abort\n");
		goto done;
	}
	ret = fusb302_i2c_read(chip, FUSB_REG_STATUS0, &status0);
	if (ret)
		goto done;

	debug("BC_LVL handler, status0 = 0x%02x\n", status0);
	if (status0 & FUSB_REG_STATUS0_ACTIVITY)
		printf("CC activities detected, delay handling\n");
	bc_lvl = status0 & FUSB_REG_STATUS0_BC_LVL_MASK;
	cc_status = fusb302_bc_lvl_to_cc(bc_lvl);
	if (chip->cc_polarity == TYPEC_POLARITY_CC1) {
		if (chip->cc1 != cc_status) {
			debug("cc1: %s -> %s\n",
				typec_cc_status_name[chip->cc1],
				typec_cc_status_name[cc_status]);
			chip->cc1 = cc_status;
			tcpm_cc_change(chip->tcpm_port);
		}
	} else {
		if (chip->cc2 != cc_status) {
			debug("cc2: %s -> %s\n",
				typec_cc_status_name[chip->cc2],
				typec_cc_status_name[cc_status]);
			chip->cc2 = cc_status;
			tcpm_cc_change(chip->tcpm_port);
		}
	}

done:
	return;
}

static void fusb302_interrupt_handle(struct fusb302_chip *chip);
static void fusb302_poll_event(struct tcpc_dev *dev)
{
	struct fusb302_chip *chip = container_of(dev, struct fusb302_chip,
						 tcpc_dev);

	fusb302_interrupt_handle(chip);
}

static int fusb302_enter_low_power_mode(struct tcpc_dev *dev,
					bool attached, bool pd_capable)
{
	struct fusb302_chip *chip = container_of(dev, struct fusb302_chip,
						 tcpc_dev);
	int ret = 0;
	unsigned int reg;

	ret = fusb302_mask_interrupt(chip);
	if (ret)
		return ret;
	if (attached && pd_capable)
		reg = FUSB_REG_POWER_PWR_MEDIUM;
	else if (attached)
		reg = FUSB_REG_POWER_PWR_LOW;
	else
		reg = 0;

	return fusb302_set_power_mode(chip, reg);
}

static void init_tcpc_dev(struct tcpc_dev *fusb302_tcpc_dev)
{
	fusb302_tcpc_dev->init = tcpm_init;
	fusb302_tcpc_dev->get_vbus = tcpm_get_vbus;
	//fusb302_tcpc_dev->get_current_limit = tcpm_get_current_limit;
	fusb302_tcpc_dev->set_cc = tcpm_set_cc;
	fusb302_tcpc_dev->get_cc = tcpm_get_cc;
	fusb302_tcpc_dev->set_polarity = tcpm_set_polarity;
	fusb302_tcpc_dev->set_vconn = tcpm_set_vconn;
	fusb302_tcpc_dev->set_vbus = tcpm_set_vbus;
	fusb302_tcpc_dev->set_pd_rx = tcpm_set_pd_rx;
	fusb302_tcpc_dev->set_roles = tcpm_set_roles;
	fusb302_tcpc_dev->start_toggling = tcpm_start_toggling;
	fusb302_tcpc_dev->pd_transmit = tcpm_pd_transmit;
	fusb302_tcpc_dev->poll_event = fusb302_poll_event;
	fusb302_tcpc_dev->enter_low_power_mode = fusb302_enter_low_power_mode;
}

static const char * const cc_polarity_name[] = {
	[TYPEC_POLARITY_CC1]	= "Polarity_CC1",
	[TYPEC_POLARITY_CC2]	= "Polarity_CC2",
};

static int fusb302_set_cc_polarity_and_pull(struct fusb302_chip *chip,
					    enum typec_cc_polarity cc_polarity,
					    bool pull_up, bool pull_down)
{
	int ret = 0;
	u8 switches0_data = 0x00;
	u8 switches1_mask = FUSB_REG_SWITCHES1_TXCC1_EN |
			    FUSB_REG_SWITCHES1_TXCC2_EN;
	u8 switches1_data = 0x00;

	if (pull_down)
		switches0_data |= FUSB_REG_SWITCHES0_CC1_PD_EN |
				  FUSB_REG_SWITCHES0_CC2_PD_EN;

	if (cc_polarity == TYPEC_POLARITY_CC1) {
		switches0_data |= FUSB_REG_SWITCHES0_MEAS_CC1;
		if (chip->vconn_on)
			switches0_data |= FUSB_REG_SWITCHES0_VCONN_CC2;
		if (pull_up)
			switches0_data |= FUSB_REG_SWITCHES0_CC1_PU_EN;
		switches1_data = FUSB_REG_SWITCHES1_TXCC1_EN;
	} else {
		switches0_data |= FUSB_REG_SWITCHES0_MEAS_CC2;
		if (chip->vconn_on)
			switches0_data |= FUSB_REG_SWITCHES0_VCONN_CC1;
		if (pull_up)
			switches0_data |= FUSB_REG_SWITCHES0_CC2_PU_EN;
		switches1_data = FUSB_REG_SWITCHES1_TXCC2_EN;
	}
	ret = fusb302_i2c_write(chip, FUSB_REG_SWITCHES0, switches0_data);
	if (ret)
		return ret;
	ret = fusb302_i2c_mask_write(chip, FUSB_REG_SWITCHES1,
				     switches1_mask, switches1_data);
	if (ret)
		return ret;
	chip->cc_polarity = cc_polarity;

	return ret;
}

static int fusb302_handle_togdone_snk(struct fusb302_chip *chip,
				      u8 togdone_result)
{
	int ret = 0;
	u8 status0;
	u8 bc_lvl;
	enum typec_cc_polarity cc_polarity;
	enum typec_cc_status cc_status_active, cc1, cc2;

	/* set polarity and pull_up, pull_down */
	cc_polarity = (togdone_result == FUSB_REG_STATUS1A_TOGSS_SNK1) ?
		      TYPEC_POLARITY_CC1 : TYPEC_POLARITY_CC2;
	ret = fusb302_set_cc_polarity_and_pull(chip, cc_polarity, false, true);
	if (ret) {
		printf("cannot set cc polarity %s, ret = %d\n",
			cc_polarity_name[cc_polarity], ret);
		return ret;
	}
	/* fusb302_set_cc_polarity() has set the correct measure block */
	ret = fusb302_i2c_read(chip, FUSB_REG_STATUS0, &status0);
	if (ret < 0)
		return ret;
	bc_lvl = status0 & FUSB_REG_STATUS0_BC_LVL_MASK;
	cc_status_active = fusb302_bc_lvl_to_cc(bc_lvl);
	/* restart toggling if the cc status on the active line is OPEN */
	if (cc_status_active == TYPEC_CC_OPEN) {
		printf("restart toggling as CC_OPEN detected\n");
		ret = fusb302_set_toggling(chip, chip->toggling_mode);
		return ret;
	}
	/* update tcpm with the new cc value */
	cc1 = (cc_polarity == TYPEC_POLARITY_CC1) ?
	      cc_status_active : TYPEC_CC_OPEN;
	cc2 = (cc_polarity == TYPEC_POLARITY_CC2) ?
	      cc_status_active : TYPEC_CC_OPEN;
	if ((chip->cc1 != cc1) || (chip->cc2 != cc2)) {
		chip->cc1 = cc1;
		chip->cc2 = cc2;
		tcpm_cc_change(chip->tcpm_port);
	}
	/* turn off toggling */
	ret = fusb302_set_toggling(chip, TOGGLING_MODE_OFF);
	if (ret) {
		printf("cannot set toggling mode off, ret=%d\n", ret);
		return ret;
	}
	/* unmask bc_lvl interrupt */
	ret = fusb302_i2c_clear_bits(chip, FUSB_REG_MASK, FUSB_REG_MASK_BC_LVL);
	if (ret) {
		printf("cannot unmask bc_lcl interrupt, ret=%d\n", ret);
		return ret;
	}
	chip->intr_bc_lvl = true;
	debug("detected cc1=%s, cc2=%s\n",
		typec_cc_status_name[cc1],
		typec_cc_status_name[cc2]);

	return ret;
}

/* On error returns < 0, otherwise a typec_cc_status value */
static int fusb302_get_src_cc_status(struct fusb302_chip *chip,
				     enum typec_cc_polarity cc_polarity,
				     enum typec_cc_status *cc)
{
	u8 ra_mda = ra_mda_value[chip->src_current_status];
	u8 rd_mda = rd_mda_value[chip->src_current_status];
	u8 switches0_data, status0;
	int ret;

	/* Step 1: Set switches so that we measure the right CC pin */
	switches0_data = (cc_polarity == TYPEC_POLARITY_CC1) ?
		FUSB_REG_SWITCHES0_CC1_PU_EN | FUSB_REG_SWITCHES0_MEAS_CC1 :
		FUSB_REG_SWITCHES0_CC2_PU_EN | FUSB_REG_SWITCHES0_MEAS_CC2;
	ret = fusb302_i2c_write(chip, FUSB_REG_SWITCHES0, switches0_data);
	if (ret < 0)
		return ret;

	fusb302_i2c_read(chip, FUSB_REG_SWITCHES0, &status0);
	debug("get_src_cc_status switches: 0x%0x", status0);

	/* Step 2: Set compararator volt to differentiate between Open and Rd */
	ret = fusb302_i2c_write(chip, FUSB_REG_MEASURE, rd_mda);
	if (ret)
		return ret;

	usleep_range(50, 100);
	ret = fusb302_i2c_read(chip, FUSB_REG_STATUS0, &status0);
	if (ret)
		return ret;

	debug("get_src_cc_status rd_mda status0: 0x%0x", status0);
	if (status0 & FUSB_REG_STATUS0_COMP) {
		*cc = TYPEC_CC_OPEN;
		return 0;
	}

	/* Step 3: Set compararator input to differentiate between Rd and Ra. */
	ret = fusb302_i2c_write(chip, FUSB_REG_MEASURE, ra_mda);
	if (ret)
		return ret;

	usleep_range(50, 100);
	ret = fusb302_i2c_read(chip, FUSB_REG_STATUS0, &status0);
	if (ret)
		return ret;

	debug("get_src_cc_status ra_mda status0: 0x%0x", status0);
	if (status0 & FUSB_REG_STATUS0_COMP)
		*cc = TYPEC_CC_RD;
	else
		*cc = TYPEC_CC_RA;

	return 0;
}

static int fusb302_handle_togdone_src(struct fusb302_chip *chip,
				      u8 togdone_result)
{
	/*
	 * - set polarity (measure cc, vconn, tx)
	 * - set pull_up, pull_down
	 * - set cc1, cc2, and update to tcpm_port
	 * - set I_COMP interrupt on
	 */
	int ret = 0;
	u8 rd_mda = rd_mda_value[chip->src_current_status];
	enum toggling_mode toggling_mode = chip->toggling_mode;
	enum typec_cc_polarity cc_polarity;
	enum typec_cc_status cc1, cc2;

	/*
	 * The toggle-engine will stop in a src state if it sees either Ra or
	 * Rd. Determine the status for both CC pins, starting with the one
	 * where toggling stopped, as that is where the switches point now.
	 */
	if (togdone_result == FUSB_REG_STATUS1A_TOGSS_SRC1)
		ret = fusb302_get_src_cc_status(chip, TYPEC_POLARITY_CC1, &cc1);
	else
		ret = fusb302_get_src_cc_status(chip, TYPEC_POLARITY_CC2, &cc2);
	if (ret)
		return ret;
	/* we must turn off toggling before we can measure the other pin */
	ret = fusb302_set_toggling(chip, TOGGLING_MODE_OFF);
	if (ret) {
		printf("cannot set toggling mode off, ret=%d\n", ret);
		return ret;
	}
	/* get the status of the other pin */
	if (togdone_result == FUSB_REG_STATUS1A_TOGSS_SRC1)
		ret = fusb302_get_src_cc_status(chip, TYPEC_POLARITY_CC2, &cc2);
	else
		ret = fusb302_get_src_cc_status(chip, TYPEC_POLARITY_CC1, &cc1);
	if (ret)
		return ret;

	/* determine polarity based on the status of both pins */
	if (cc1 == TYPEC_CC_RD &&
			(cc2 == TYPEC_CC_OPEN || cc2 == TYPEC_CC_RA)) {
		cc_polarity = TYPEC_POLARITY_CC1;
	} else if (cc2 == TYPEC_CC_RD &&
		    (cc1 == TYPEC_CC_OPEN || cc1 == TYPEC_CC_RA)) {
		cc_polarity = TYPEC_POLARITY_CC2;
	} else {
		printf("unexpected CC status cc1=%s, cc2=%s, restarting toggling\n",
			typec_cc_status_name[cc1],
			typec_cc_status_name[cc2]);
		return fusb302_set_toggling(chip, toggling_mode);
	}
	/* set polarity and pull_up, pull_down */
	ret = fusb302_set_cc_polarity_and_pull(chip, cc_polarity, true, false);
	if (ret < 0) {
		printf("cannot set cc polarity %s, ret=%d\n",
			cc_polarity_name[cc_polarity], ret);
		return ret;
	}
	/* update tcpm with the new cc value */
	if ((chip->cc1 != cc1) || (chip->cc2 != cc2)) {
		chip->cc1 = cc1;
		chip->cc2 = cc2;
		tcpm_cc_change(chip->tcpm_port);
	}
	/* set MDAC to Rd threshold, and unmask I_COMP for unplug detection */
	ret = fusb302_i2c_write(chip, FUSB_REG_MEASURE, rd_mda);
	if (ret)
		return ret;
	/* unmask comp_chng interrupt */
	ret = fusb302_i2c_clear_bits(chip, FUSB_REG_MASK,
				     FUSB_REG_MASK_COMP_CHNG);
	if (ret) {
		printf("cannot unmask comp_chng interrupt, ret=%d\n", ret);
		return ret;
	}
	chip->intr_comp_chng = true;
	debug("detected cc1=%s, cc2=%s\n",
		typec_cc_status_name[cc1],
		typec_cc_status_name[cc2]);

	return ret;
}

static int fusb302_handle_togdone(struct fusb302_chip *chip)
{
	int ret = 0;
	u8 status1a;
	u8 togdone_result;

	ret = fusb302_i2c_read(chip, FUSB_REG_STATUS1A, &status1a);
	if (ret < 0)
		return ret;
	togdone_result = (status1a >> FUSB_REG_STATUS1A_TOGSS_POS) &
			 FUSB_REG_STATUS1A_TOGSS_MASK;
	switch (togdone_result) {
	case FUSB_REG_STATUS1A_TOGSS_SNK1:
	case FUSB_REG_STATUS1A_TOGSS_SNK2:
		return fusb302_handle_togdone_snk(chip, togdone_result);
	case FUSB_REG_STATUS1A_TOGSS_SRC1:
	case FUSB_REG_STATUS1A_TOGSS_SRC2:
		return fusb302_handle_togdone_src(chip, togdone_result);
	case FUSB_REG_STATUS1A_TOGSS_AA:
		/* doesn't support */
		printf("AudioAccessory not supported\n");
		fusb302_set_toggling(chip, chip->toggling_mode);
		break;
	default:
		printf("TOGDONE with an invalid state: %d\n", togdone_result);
		fusb302_set_toggling(chip, chip->toggling_mode);
		break;
	}
	return ret;
}

static int fusb302_pd_reset(struct fusb302_chip *chip)
{
	return fusb302_i2c_set_bits(chip, FUSB_REG_RESET,
				    FUSB_REG_RESET_PD_RESET);
}

static int fusb302_pd_read_message(struct fusb302_chip *chip,
				   struct pd_message *msg)
{
	int ret = 0;
	u8 token;
	u8 crc[4];
	int len;

	/* first SOP token */
	ret = fusb302_i2c_read(chip, FUSB_REG_FIFOS, &token);
	if (ret)
		return ret;
	ret = fusb302_i2c_block_read(chip, FUSB_REG_FIFOS, 2,
				     (u8 *)&msg->header);
	if (ret)
		return ret;
	len = pd_header_cnt_le(msg->header) * 4;
	/* add 4 to length to include the CRC */
	if (len > PD_MAX_PAYLOAD * 4) {
		printf("%s: PD message too long %d\n", __func__, len);
		return -EINVAL;
	}
	if (len > 0) {
		ret = fusb302_i2c_block_read(chip, FUSB_REG_FIFOS, len,
					     (u8 *)msg->payload);
		if (ret)
			return ret;
	}
	/* another 4 bytes to read CRC out */
	ret = fusb302_i2c_block_read(chip, FUSB_REG_FIFOS, 4, crc);
	if (ret)
		return ret;
	debug("%s: PD message header: %x\n", __func__, msg->header);
	debug("%s: PD message len: %d\n", __func__, len);

	/*
	 * Check if we've read off a GoodCRC message. If so then indicate to
	 * TCPM that the previous transmission has completed. Otherwise we pass
	 * the received message over to TCPM for processing.
	 *
	 * We make this check here instead of basing the reporting decision on
	 * the IRQ event type, as it's possible for the chip to report the
	 * TX_SUCCESS and GCRCSENT events out of order on occasion, so we need
	 * to check the message type to ensure correct reporting to TCPM.
	 */
	if ((!len) && (pd_header_type_le(msg->header) == PD_CTRL_GOOD_CRC))
		tcpm_pd_transmit_complete(chip->tcpm_port, TCPC_TX_SUCCESS);
	else
		tcpm_pd_receive(chip->tcpm_port, msg);

	return ret;
}

static void fusb302_interrupt_handle(struct fusb302_chip *chip)
{
	int ret = 0;
	u8 interrupt;
	u8 interrupta;
	u8 interruptb;
	u8 status0;
	bool vbus_present;
	bool comp_result;
	bool intr_togdone;
	bool intr_bc_lvl;
	bool intr_comp_chng;
	struct pd_message pd_msg;

	/* grab a snapshot of intr flags */
	intr_togdone = chip->intr_togdone;
	intr_bc_lvl = chip->intr_bc_lvl;
	intr_comp_chng = chip->intr_comp_chng;

	if (chip->gpio_cc_int_present)
		if (!dm_gpio_get_value(&chip->gpio_cc_int))
			return;

	ret = fusb302_i2c_read(chip, FUSB_REG_INTERRUPT, &interrupt);
	if (ret)
		return;
	ret = fusb302_i2c_read(chip, FUSB_REG_INTERRUPTA, &interrupta);
	if (ret)
		return;
	ret = fusb302_i2c_read(chip, FUSB_REG_INTERRUPTB, &interruptb);
	if (ret)
		return;
	ret = fusb302_i2c_read(chip, FUSB_REG_STATUS0, &status0);
	if (ret)
		return;
	debug("IRQ: 0x%02x, a: 0x%02x, b: 0x%02x, status0: 0x%02x\n",
		interrupt, interrupta, interruptb, status0);

	if (interrupt & FUSB_REG_INTERRUPT_VBUSOK) {
		vbus_present = !!(status0 & FUSB_REG_STATUS0_VBUSOK);
		debug("IRQ: VBUS_OK, vbus=%s\n", vbus_present ? "On" : "Off");
		if (vbus_present != chip->vbus_present) {
			chip->vbus_present = vbus_present;
			tcpm_vbus_change(chip->tcpm_port);
		}
	}

	if ((interrupta & FUSB_REG_INTERRUPTA_TOGDONE) && intr_togdone) {
		debug("IRQ: TOGDONE\n");
		ret = fusb302_handle_togdone(chip);
		if (ret) {
			printf("%s: handle togdone error(%d)\n", __func__, ret);
			return;
		}
	}

	if ((interrupt & FUSB_REG_INTERRUPT_BC_LVL) && intr_bc_lvl) {
		debug("IRQ: BC_LVL, handler pending\n");
		/*
		 * as BC_LVL interrupt can be affected by PD activity,
		 * apply delay to for the handler to wait for the PD
		 * signaling to finish.
		 */
		//msleep(T_BC_LVL_DEBOUNCE_DELAY_MS);
		fusb302_bc_lvl_handler(chip);
	}

	if ((interrupt & FUSB_REG_INTERRUPT_COMP_CHNG) && intr_comp_chng) {
		comp_result = !!(status0 & FUSB_REG_STATUS0_COMP);
		debug("IRQ: COMP_CHNG, comp=%s\n", comp_result ? "true" : "false");
		if (comp_result) {
			/* cc level > Rd_threshold, detach */
			chip->cc1 = TYPEC_CC_OPEN;
			chip->cc2 = TYPEC_CC_OPEN;
			tcpm_cc_change(chip->tcpm_port);
		}
	}

	if (interrupt & FUSB_REG_INTERRUPT_COLLISION) {
		debug("IRQ: PD collision\n");
		tcpm_pd_transmit_complete(chip->tcpm_port, TCPC_TX_FAILED);
	}

	if (interrupta & FUSB_REG_INTERRUPTA_RETRYFAIL) {
		debug("IRQ: PD retry failed\n");
		tcpm_pd_transmit_complete(chip->tcpm_port, TCPC_TX_FAILED);
	}

	if (interrupta & FUSB_REG_INTERRUPTA_HARDSENT) {
		debug("IRQ: PD hardreset sent\n");
		ret = fusb302_pd_reset(chip);
		if (ret) {
			printf("cannot PD reset, ret=%d\n", ret);
			return;
		}
		tcpm_pd_transmit_complete(chip->tcpm_port, TCPC_TX_SUCCESS);
	}

	if (interrupta & FUSB_REG_INTERRUPTA_TX_SUCCESS) {
		debug("IRQ: PD tx success\n");
		ret = fusb302_pd_read_message(chip, &pd_msg);
		if (ret) {
			printf("cannot read in PD message, ret=%d\n", ret);
			return;
		}
	}

	if (interrupta & FUSB_REG_INTERRUPTA_HARDRESET) {
		debug("IRQ: PD received hardreset\n");
		ret = fusb302_pd_reset(chip);
		if (ret) {
			printf("cannot PD reset, ret=%d\n", ret);
			return;
		}
		tcpm_pd_hard_reset(chip->tcpm_port);
	}

	if (interruptb & FUSB_REG_INTERRUPTB_GCRCSENT) {
		debug("IRQ: PD sent good CRC\n");
		ret = fusb302_pd_read_message(chip, &pd_msg);
		if (ret) {
			printf("cannot read in PD message, ret=%d\n", ret);
			return;
		}
	}
}

static int fusb302_probe(struct udevice *dev)
{
	struct fusb302_chip *chip = dev_get_priv(dev);
	int ret = 0;

	chip->udev = dev;

#if 0
	/* get vbus regulator */
	ret = regulator_get_by_platname("vbus5v0_typec", chip->vbus_regulator);
	if (ret) {
		printf("Can get the regulator: vbus5v0_typec (err=%d)\n", ret);
		chip->vbus_regulator = NULL;
	}
#endif

	chip->tcpc_dev.connector_node = dev_read_subnode(dev, "connector");
	if (!ofnode_valid(chip->tcpc_dev.connector_node)) {
		printf("%s: 'connector' node is not found\n", __func__);
		return -ENODEV;
	}

	init_tcpc_dev(&chip->tcpc_dev);

	ret = gpio_request_by_name(dev, "int-n-gpios", 0,
				   &chip->gpio_cc_int, GPIOD_IS_IN);
	if (ret) {
		printf("%s: fail to get int GPIO: ret=%d\n", __func__, ret);
		chip->gpio_cc_int_present = false;
	} else {
		chip->gpio_cc_int_present = true;
	}

	chip->tcpm_port = tcpm_port_init(dev, &chip->tcpc_dev);
	if (IS_ERR(chip->tcpm_port)) {
		printf("%s: failed to tcpm port init\n", __func__);
		return PTR_ERR(chip->tcpm_port);
	}

	tcpm_poll_event(chip->tcpm_port);

	return 0;
}


static int fusb302_get_voltage(struct udevice *dev)
{
	struct fusb302_chip *chip = dev_get_priv(dev);

	return tcpm_get_voltage(chip->tcpm_port);
}

static int fusb302_get_current(struct udevice *dev)
{
	struct fusb302_chip *chip = dev_get_priv(dev);

	return tcpm_get_current(chip->tcpm_port);
}

static int fusb302_get_online(struct udevice *dev)
{
	struct fusb302_chip *chip = dev_get_priv(dev);

	return tcpm_get_online(chip->tcpm_port);
}

static struct dm_power_delivery_ops fusb302_ops = {
	.get_voltage = fusb302_get_voltage,
	.get_current = fusb302_get_current,
	.get_online = fusb302_get_online,
};

static const struct udevice_id fusb302_ids[] = {
	{ .compatible = "fcs,fusb302" },
	{ }
};

U_BOOT_DRIVER(fusb302) = {
	.name = "fusb302",
	.id = UCLASS_PD,
	.of_match = fusb302_ids,
	.ops = &fusb302_ops,
	.probe = fusb302_probe,
	.priv_auto_alloc_size = sizeof(struct fusb302_chip),
};
