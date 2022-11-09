// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2019
 * Alex Marginean, NXP
 */

#include <common.h>
#include <dm.h>
#include <miiphy.h>
#include <dm/device-internal.h>
#include <dm/uclass-internal.h>

void dm_mdio_probe_devices(void)
{
	struct udevice *it;
	struct uclass *uc;

	uclass_get(UCLASS_MDIO, &uc);
	uclass_foreach_dev(it, uc) {
		device_probe(it);
	}
}

static int dm_mdio_post_bind(struct udevice *dev)
{
	/*
	 * MDIO command doesn't like spaces in names, don't allow them to keep
	 * it happy
	 */
	if (strchr(dev->name, ' ')) {
		debug("\nError: MDIO device name \"%s\" has a space!\n",
		      dev->name);
		return -EINVAL;
	}

	return 0;
}

/*
 * Following read/write/reset functions are registered with legacy MII code.
 * These are called for PHY operations by upper layers and we further call the
 * DM MDIO driver functions.
 */
static int mdio_read(struct mii_dev *mii_bus, int addr, int devad, int reg)
{
	struct udevice *dev = mii_bus->priv;

	return mdio_get_ops(dev)->read(dev, addr, devad, reg);
}

static int mdio_write(struct mii_dev *mii_bus, int addr, int devad, int reg,
		      u16 val)
{
	struct udevice *dev = mii_bus->priv;

	return mdio_get_ops(dev)->write(dev, addr, devad, reg, val);
}

static int mdio_reset(struct mii_dev *mii_bus)
{
	struct udevice *dev = mii_bus->priv;

	if (mdio_get_ops(dev)->reset)
		return mdio_get_ops(dev)->reset(dev);
	else
		return 0;
}

static int dm_mdio_post_probe(struct udevice *dev)
{
	struct mdio_perdev_priv *pdata = dev_get_uclass_priv(dev);

	pdata->mii_bus = mdio_alloc();
	pdata->mii_bus->read = mdio_read;
	pdata->mii_bus->write = mdio_write;
	pdata->mii_bus->reset = mdio_reset;
	pdata->mii_bus->priv = dev;
	strncpy(pdata->mii_bus->name, dev->name, MDIO_NAME_LEN);

	return mdio_register(pdata->mii_bus);
}

static int dm_mdio_pre_remove(struct udevice *dev)
{
	struct mdio_perdev_priv *pdata = dev_get_uclass_priv(dev);
	struct mdio_ops *ops = mdio_get_ops(dev);

	if (ops->reset)
		ops->reset(dev);
	mdio_unregister(pdata->mii_bus);
	mdio_free(pdata->mii_bus);

	return 0;
}

struct phy_device *dm_mdio_phy_connect(struct udevice *dev, int addr,
				       struct udevice *ethdev,
				       phy_interface_t interface)
{
	struct mdio_perdev_priv *pdata = dev_get_uclass_priv(dev);

	if (device_probe(dev))
		return 0;

	return phy_connect(pdata->mii_bus, addr, ethdev, interface);
}

UCLASS_DRIVER(mdio) = {
	.id = UCLASS_MDIO,
	.name = "mdio",
	.post_bind  = dm_mdio_post_bind,
	.post_probe = dm_mdio_post_probe,
	.pre_remove = dm_mdio_pre_remove,
	.per_device_auto_alloc_size = sizeof(struct mdio_perdev_priv),
};
