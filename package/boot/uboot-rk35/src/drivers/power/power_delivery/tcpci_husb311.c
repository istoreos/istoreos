// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2021 Rockchip Co.,Ltd.
 * Author: Wang Jie <dave.wang@rock-chips.com>
 *
 * Hynetek Husb311 Type-C Chip Driver
 */

#include <dm.h>
#include <i2c.h>
#include <asm/gpio.h>
#include <power/power_delivery/tcpm.h>
#include <power/power_delivery/power_delivery.h>
#include "tcpci.h"

#define HUSB311_VID		0x2E99
#define HUSB311_PID		0x0311
#define HUSB311_TCPC_I2C_RESET	0x9E
#define HUSB311_TCPC_SOFTRESET	0xA0
#define HUSB311_TCPC_FILTER	0xA1
#define HUSB311_TCPC_TDRP	0xA2
#define HUSB311_TCPC_DCSRCDRP	0xA3
#define HUSB311_I2C_RETRY_MAX_CNT 3

struct husb311_chip {
	struct udevice *udev;
	struct tcpci_data data;
	struct tcpci *tcpci;
};

static int husb311_read16(struct husb311_chip *chip, unsigned int reg)
{
	int ret = 0;
	u8 buffer[2];

	ret = dm_i2c_read(chip->udev, reg, buffer, 2);
	if (ret < 0) {
		printf("%s: cannot read %02x, ret=%d\n",
			__func__, reg, ret);
		return ret;
	}
	ret = ((buffer[1] << 8) & 0xFF00) + (buffer[0] & 0xFF);

	return ret;
}

static int husb311_write8(struct husb311_chip *chip, unsigned int reg, u8 val)
{
	int ret = 0;
	int i;

	for (i = 0; i < HUSB311_I2C_RETRY_MAX_CNT; i++) {
		ret = dm_i2c_write(chip->udev, reg, &val, 1);
		if (!ret)
			break;
		else
			udelay(200);
	}

	if (ret)
		printf("%s: cannot write 0x%02x to 0x%02x, ret=%d\n",
			__func__, val, reg, ret);

	return ret;
}

static int husb311_write16(struct husb311_chip *chip, unsigned int reg, u16 val)
{
	int ret = 0;
	u8 buffer[2];

	buffer[0] = val & 0xFF;
	buffer[1] = (val >> 8) & 0xFF;
	ret = dm_i2c_write(chip->udev, reg, buffer, 2);
	if (ret)
		printf("%s: cannot write 0x%02x, len=%d, ret=%d\n",
			__func__, reg, 2, ret);

	return ret;
}

static struct husb311_chip *tdata_to_husb311(struct tcpci_data *tdata)
{
	return container_of(tdata, struct husb311_chip, data);
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

	/* I2C reset : (val + 1) * 12.5ms */
	ret = husb311_write8(chip, HUSB311_TCPC_I2C_RESET, 0x8F);
	/* tTCPCfilter : (26.7 * val) us */
	ret |= husb311_write8(chip, HUSB311_TCPC_FILTER, 0x0F);
	/* tDRP : (51.2 + 6.4 * val) ms */
	ret |= husb311_write8(chip, HUSB311_TCPC_TDRP, 0x04);
	/* dcSRC.DRP : 33% */
	ret |= husb311_write16(chip, HUSB311_TCPC_DCSRCDRP, 330);

	if (ret)
		printf("%s: fail to init registers(%d)\n", __func__, ret);

	return ret;
}

static int husb311_check_revision(struct husb311_chip *chip)
{
	int ret;

	ret = husb311_read16(chip, TCPC_VENDOR_ID);
	if (ret < 0) {
		printf("%s: fail to read Vendor id(%d)\n", __func__, ret);
		return ret;
	}

	if (ret != HUSB311_VID) {
		printf("%s: vid is not correct, 0x%04x\n", __func__, ret);
		return -ENODEV;
	}

	ret = husb311_read16(chip, TCPC_PRODUCT_ID);
	if (ret < 0) {
		printf("%s: fail to read Product id(%d)\n", __func__, ret);
		return ret;
	}

	if (ret != HUSB311_PID) {
		printf("%s: pid is not correct, 0x%04x\n", __func__, ret);
		return -ENODEV;
	}

	return 0;
}

static int husb311_probe(struct udevice *dev)
{
	int ret;
	struct husb311_chip *chip = dev_get_priv(dev);

	chip->udev = dev;

	ret = husb311_check_revision(chip);
	if (ret < 0) {
		printf("%s: check vid/pid fail(%d)\n", __func__, ret);
		return ret;
	}

	ret = husb311_sw_reset(chip);
	if (ret) {
		printf("%s: fail to soft reset, ret = %d\n", __func__, ret);
		return ret;
	}

	chip->data.init = husb311_init;
	chip->tcpci = tcpci_register_port(chip->udev, &chip->data);
	if (IS_ERR(chip->tcpci))
		return PTR_ERR(chip->tcpci);

	return 0;
}

static int husb311_remove(struct udevice *dev)
{
	struct husb311_chip *chip = dev_get_priv(dev);
	int ret = 0;

	printf("PD chip husb311 remove\n");
	/* Disable chip interrupts before unregistering port */
	ret = husb311_write16(chip, TCPC_ALERT_MASK, 0);
	if (ret < 0)
		return ret;

	tcpci_unregister_port(chip->tcpci);

	return 0;
}

static int husb311_get_voltage(struct udevice *dev)
{
	struct husb311_chip *chip = dev_get_priv(dev);

	return tcpci_get_voltage_fun(chip->tcpci);
}

static int husb311_get_current(struct udevice *dev)
{
	struct husb311_chip *chip = dev_get_priv(dev);

	return tcpci_get_current_fun(chip->tcpci);
}

static int husb311_get_online(struct udevice *dev)
{
	struct husb311_chip *chip = dev_get_priv(dev);

	return tcpci_get_online_fun(chip->tcpci);
}

static struct dm_power_delivery_ops husb311_ops = {
	.get_voltage = husb311_get_voltage,
	.get_current = husb311_get_current,
	.get_online = husb311_get_online,
};

static const struct udevice_id husb311_ids[] = {
	{ .compatible = "hynetek,husb311" },
	{},
};

U_BOOT_DRIVER(husb311) = {
	.name = "husb311",
	.id = UCLASS_PD,
	.of_match = husb311_ids,
	.ops = &husb311_ops,
	.probe = husb311_probe,
	.remove = husb311_remove,
	.priv_auto_alloc_size = sizeof(struct husb311_chip),
};

MODULE_AUTHOR("Wang Jie <dave.wang@rock-chips.com>");
MODULE_DESCRIPTION("Husb311 USB Type-C Port Controller Interface Driver");
MODULE_LICENSE("GPL v2");
