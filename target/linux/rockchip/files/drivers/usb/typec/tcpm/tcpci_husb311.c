// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2021 Rockchip Electronics Co., Ltd.
 * Author: Wang Jie <dave.wang@rock-chips.com>
 *
 * Hynetek Husb311 Type-C Chip Driver
 */

#include <linux/gpio/consumer.h>
#include <linux/i2c.h>
#include <linux/interrupt.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/regmap.h>
#include <linux/regulator/consumer.h>
#include <linux/usb/tcpci.h>
#include <linux/usb/tcpm.h>

#define HUSB311_VID		0x2E99
#define HUSB311_PID		0x0311
#define HUSB311_TCPC_POWER	0x90
#define HUSB311_TCPC_SOFTRESET	0xA0
#define HUSB311_TCPC_FILTER	0xA1
#define HUSB311_TCPC_TDRP	0xA2
#define HUSB311_TCPC_DCSRCDRP	0xA3

#define HUSB311_PM_DELAY_S	(3 * HZ)

struct husb311_chip {
	struct tcpci_data data;
	struct tcpci *tcpci;
	struct device *dev;
	struct regulator *vbus;
	struct mutex lock; /* lock for sharing chip states */
	struct delayed_work pm_work;
	bool vbus_on;
	bool charge_on;
	bool suspended;
	bool wakeup;
};

static int husb311_read8(struct husb311_chip *chip, unsigned int reg, u8 *val)
{
	return regmap_raw_read(chip->data.regmap, reg, val, sizeof(u8));
}

static int husb311_write8(struct husb311_chip *chip, unsigned int reg, u8 val)
{
	return regmap_raw_write(chip->data.regmap, reg, &val, sizeof(u8));
}

static int husb311_write16(struct husb311_chip *chip, unsigned int reg, u16 val)
{
	return regmap_raw_write(chip->data.regmap, reg, &val, sizeof(u16));
}

static const struct regmap_config husb311_regmap_config = {
	.reg_bits = 8,
	.val_bits = 8,
	.max_register = 0xFF, /* 0x80 .. 0xFF are vendor defined */
};

static struct husb311_chip *tdata_to_husb311(struct tcpci_data *tdata)
{
	return container_of(tdata, struct husb311_chip, data);
}

static int husb311_disable_osc24m(struct husb311_chip *chip)
{
	int ret = 0;
	u8 pwr;

	/*
	 * Disable 24M oscillator to save power consumption, and it will be
	 * enabled automatically when INT occurs.
	 */
	ret = husb311_read8(chip, HUSB311_TCPC_POWER, &pwr);
	if (ret < 0)
		return ret;

	pwr &= ~BIT(0);
	ret = husb311_write8(chip, HUSB311_TCPC_POWER, pwr);
	if (ret < 0)
		return ret;

	return 0;
}

static void husb311_pm_work(struct work_struct *work)
{
	struct husb311_chip *chip =
		container_of(work, struct husb311_chip, pm_work.work);

	mutex_lock(&chip->lock);

	if (!chip->vbus_on && !chip->charge_on) {
		if (chip->suspended)
			goto exit;

		husb311_disable_osc24m(chip);
		chip->suspended = 1;
	} else {
		if (chip->suspended)
			chip->suspended = 0;
	}

exit:
	mutex_unlock(&chip->lock);
}

static int husb311_sw_reset(struct husb311_chip *chip)
{
	/* soft reset */
	return husb311_write8(chip, HUSB311_TCPC_SOFTRESET, 0x01);
}

static int husb311_init(struct tcpci *tcpci, struct tcpci_data *tdata)
{
	int ret;
	struct husb311_chip *chip = tdata_to_husb311(tdata);

	/* tTCPCfilter : (26.7 * val) us */
	ret = husb311_write8(chip, HUSB311_TCPC_FILTER, 0x0F);
	/* tDRP : (51.2 + 6.4 * val) ms */
	ret |= husb311_write8(chip, HUSB311_TCPC_TDRP, 0x04);
	/* dcSRC.DRP : 33% */
	ret |= husb311_write16(chip, HUSB311_TCPC_DCSRCDRP, 330);

	if (ret < 0)
		dev_err(chip->dev, "fail to init registers(%d)\n", ret);

	return ret;
}

static int husb311_set_vbus(struct tcpci *tcpci, struct tcpci_data *tdata,
			    bool on, bool charge)
{
	struct husb311_chip *chip = tdata_to_husb311(tdata);
	int ret = 0;

	mutex_lock(&chip->lock);

	if (chip->vbus_on == on) {
		dev_dbg(chip->dev, "vbus is already %s", on ? "On" : "Off");
	} else {
		if (on)
			ret = regulator_enable(chip->vbus);
		else
			ret = regulator_disable(chip->vbus);
		if (ret < 0) {
			dev_err(chip->dev, "cannot %s vbus regulator, ret=%d",
				on ? "enable" : "disable", ret);
			goto done;
		}

		chip->vbus_on = on;
		dev_dbg(chip->dev, "vbus := %s", on ? "On" : "Off");
	}

	if (chip->charge_on == charge)
		dev_dbg(chip->dev, "charge is already %s",
			charge ? "On" : "Off");
	else
		chip->charge_on = charge;

	queue_delayed_work(system_freezable_wq, &chip->pm_work, HUSB311_PM_DELAY_S);

done:
	mutex_unlock(&chip->lock);
	return ret;
}

static irqreturn_t husb311_irq(int irq, void *dev_id)
{
	struct husb311_chip *chip = dev_id;
	enum typec_cc_status cc1, cc2;
	u8 reg, role_ctrl;
	u8 status;

	husb311_read8(chip, TCPC_ALERT, &status);
	dev_dbg(chip->dev, "status 0x%02x", status);

	/*
	 * If husb311 detects one of CC is Rp, let do clear the another CC
	 * status in anyway to dodge the non-standard cables that double Rp
	 * connected to VBUS which produced by Huawei and etc.
	 */
	if (status & TCPC_ALERT_CC_STATUS) {
		husb311_read8(chip, TCPC_ROLE_CTRL, &role_ctrl);
		husb311_read8(chip, TCPC_CC_STATUS, &reg);
		cc1 = tcpci_to_typec_cc((reg >> TCPC_CC_STATUS_CC1_SHIFT) &
					 TCPC_CC_STATUS_CC1_MASK,
					 reg & TCPC_CC_STATUS_TERM ||
					 tcpc_presenting_rd(role_ctrl, CC1));
		cc2 = tcpci_to_typec_cc((reg >> TCPC_CC_STATUS_CC2_SHIFT) &
					 TCPC_CC_STATUS_CC2_MASK,
					 reg & TCPC_CC_STATUS_TERM ||
					 tcpc_presenting_rd(role_ctrl, CC2));

		dev_dbg(chip->dev, "CC1 %u, CC2 %u", cc1, cc2);
		if (cc1 == TYPEC_CC_RP_DEF) {
			role_ctrl |= TCPC_ROLE_CTRL_CC_OPEN << TCPC_ROLE_CTRL_CC2_SHIFT;
			husb311_write8(chip, TCPC_ROLE_CTRL, role_ctrl);
		} else if (cc2 == TYPEC_CC_RP_DEF) {
			role_ctrl |= TCPC_ROLE_CTRL_CC_OPEN << TCPC_ROLE_CTRL_CC1_SHIFT;
			husb311_write8(chip, TCPC_ROLE_CTRL, role_ctrl);
		}
	}

	/* TCPCI Spec. Table 4-27 ResetTransmitBuffer */
	if (status & (TCPC_ALERT_TX_SUCCESS | TCPC_ALERT_TX_DISCARDED | TCPC_ALERT_TX_FAILED))
		husb311_write8(chip, TCPC_COMMAND, 0xdd);

	return tcpci_irq(chip->tcpci);
}

static int husb311_check_revision(struct i2c_client *i2c)
{
	int ret;

	ret = i2c_smbus_read_word_data(i2c, TCPC_VENDOR_ID);
	if (ret < 0) {
		dev_err(&i2c->dev, "fail to read Vendor id(%d)\n", ret);
		return ret;
	}

	if (ret != HUSB311_VID) {
		dev_err(&i2c->dev, "vid is not correct, 0x%04x\n", ret);
		return -ENODEV;
	}

	ret = i2c_smbus_read_word_data(i2c, TCPC_PRODUCT_ID);
	if (ret < 0) {
		dev_err(&i2c->dev, "fail to read Product id(%d)\n", ret);
		return ret;
	}

	if (ret != HUSB311_PID) {
		dev_err(&i2c->dev, "pid is not correct, 0x%04x\n", ret);
		return -ENODEV;
	}

	return 0;
}

static int husb311_probe(struct i2c_client *client)
{
	int ret;
	struct husb311_chip *chip;

	ret = husb311_check_revision(client);
	if (ret < 0) {
		dev_err(&client->dev, "check vid/pid fail(%d)\n", ret);
		return ret;
	}

	chip = devm_kzalloc(&client->dev, sizeof(*chip), GFP_KERNEL);
	if (!chip)
		return -ENOMEM;

	chip->data.regmap = devm_regmap_init_i2c(client,
						 &husb311_regmap_config);
	if (IS_ERR(chip->data.regmap))
		return PTR_ERR(chip->data.regmap);

	chip->dev = &client->dev;
	i2c_set_clientdata(client, chip);

	mutex_init(&chip->lock);
	INIT_DELAYED_WORK(&chip->pm_work, husb311_pm_work);

	chip->vbus = devm_regulator_get_optional(chip->dev, "vbus");
	if (IS_ERR(chip->vbus)) {
		ret = PTR_ERR(chip->vbus);
		chip->vbus = NULL;
		if (ret != -ENODEV)
			return ret;
	}

	ret = husb311_sw_reset(chip);
	if (ret < 0) {
		dev_err(chip->dev, "fail to soft reset, ret = %d\n", ret);
		return ret;
	}

	if (chip->vbus)
		chip->data.set_vbus = husb311_set_vbus;
	chip->data.init = husb311_init;
	chip->tcpci = tcpci_register_port(chip->dev, &chip->data);
	if (IS_ERR(chip->tcpci))
		return PTR_ERR(chip->tcpci);

	ret = devm_request_threaded_irq(chip->dev, client->irq, NULL,
					husb311_irq,
					IRQF_ONESHOT | IRQF_TRIGGER_LOW,
					client->name, chip);
	if (ret < 0) {
		tcpci_unregister_port(chip->tcpci);
		return ret;
	}

	chip->wakeup = device_property_read_bool(chip->dev, "wakeup-source");
	device_init_wakeup(chip->dev, true);

	return 0;
}

static void husb311_remove(struct i2c_client *client)
{
	struct husb311_chip *chip = i2c_get_clientdata(client);

	device_init_wakeup(chip->dev, false);
	disable_irq(client->irq);
	cancel_delayed_work_sync(&chip->pm_work);
	tcpci_unregister_port(chip->tcpci);
}

static void husb311_shutdown(struct i2c_client *client)
{
	struct husb311_chip *chip = i2c_get_clientdata(client);

	husb311_set_vbus(chip->tcpci, &chip->data, false, false);

	disable_irq(client->irq);
	cancel_delayed_work_sync(&chip->pm_work);
}

static int husb311_pm_suspend(struct device *dev)
{
	struct husb311_chip *chip = dev->driver_data;
	struct i2c_client *client = to_i2c_client(dev);

	if (device_may_wakeup(dev) && (!chip->vbus_on || chip->wakeup))
		enable_irq_wake(client->irq);
	else
		disable_irq(client->irq);

	if (!chip->suspended) {
		chip->suspended = 1;
		husb311_disable_osc24m(chip);
	}

	return 0;
}

static int match_fwnode(struct device *dev, void *data)
{
	return dev_fwnode(dev) == data;
}

static bool is_partner_altmode_device_registered(struct device *dev)
{
	struct device *port, *partner, *altmode;
	struct fwnode_handle *fwnode;
	char device_name[20];

	/* get typec port device */
	fwnode = device_get_named_child_node(dev, "connector");
	if (!fwnode)
		return false;

	port = device_find_child(dev, fwnode, match_fwnode);
	fwnode_handle_put(fwnode);
	if (!port)
		return false;

	/* get the partner device */
	snprintf(device_name, sizeof(device_name), "%s-partner", dev_name(port));
	partner = device_find_child_by_name(port, device_name);
	put_device(port);
	if (!partner)
		return false;

	/* get the altmode device, now only dp register */
	snprintf(device_name, sizeof(device_name), "%s.0", dev_name(partner));
	altmode = device_find_child_by_name(partner, device_name);
	put_device(partner);
	if (!altmode)
		return false;
	put_device(altmode);

	return true;
}

static int husb311_pm_resume(struct device *dev)
{
	struct husb311_chip *chip = dev->driver_data;
	struct i2c_client *client = to_i2c_client(dev);
	int ret = 0;
	u8 filter;

	if (device_may_wakeup(dev) && (!chip->vbus_on || chip->wakeup))
		disable_irq_wake(client->irq);
	else
		enable_irq(client->irq);

	/*
	 * When the power of husb311 is lost or i2c read failed in PM S/R
	 * process, we must reset the tcpm port first to ensure the devices
	 * can attach again.
	 *
	 * The TCPC_FILTER we amended its value to 0x0F in husb311_init, so if
	 * husb311 powered off in suspend, the value would reset to default.
	 */
	ret = husb311_read8(chip, HUSB311_TCPC_FILTER, &filter);
	if (filter != 0x0F || ret < 0 || is_partner_altmode_device_registered(dev)) {
		ret = husb311_sw_reset(chip);
		if (ret < 0) {
			dev_err(chip->dev, "fail to soft reset, ret = %d\n", ret);
			return ret;
		}

		tcpm_tcpc_reset(tcpci_get_tcpm_port(chip->tcpci));
	}

	return 0;
}

static const struct i2c_device_id husb311_id[] = {
	{ "husb311", 0 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, husb311_id);

#ifdef CONFIG_OF
static const struct of_device_id husb311_of_match[] = {
	{ .compatible = "hynetek,husb311" },
	{},
};
MODULE_DEVICE_TABLE(of, husb311_of_match);
#endif

static const struct dev_pm_ops husb311_pm_ops = {
	.suspend = husb311_pm_suspend,
	.resume = husb311_pm_resume,
};

static struct i2c_driver husb311_i2c_driver = {
	.driver = {
		.name = "husb311",
		.pm = &husb311_pm_ops,
		.of_match_table = of_match_ptr(husb311_of_match),
	},
	.probe = husb311_probe,
	.remove = husb311_remove,
	.shutdown = husb311_shutdown,
	.id_table = husb311_id,
};
module_i2c_driver(husb311_i2c_driver);

MODULE_AUTHOR("Wang Jie <dave.wang@rock-chips.com>");
MODULE_DESCRIPTION("Husb311 USB Type-C Port Controller Interface Driver");
MODULE_LICENSE("GPL v2");
