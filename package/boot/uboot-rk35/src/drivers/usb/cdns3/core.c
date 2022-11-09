// SPDX-License-Identifier: GPL-2.0
/*
 * Cadence USBSS DRD Driver.
 *
 * Copyright (C) 2018-2019 Cadence.
 * Copyright (C) 2017-2018 NXP
 * Copyright (C) 2019 Texas Instruments
 *
 * Author: Peter Chen <peter.chen@nxp.com>
 *         Pawel Laszczak <pawell@cadence.com>
 *         Roger Quadros <rogerq@ti.com>
 */

#include <common.h>
#include <dm.h>
#include <dm/device-internal.h>
#include <dm/lists.h>
#include <linux/kernel.h>
#include <linux/io.h>
#include <usb.h>
#include <usb/xhci.h>

#include "core.h"
#include "host-export.h"
#include "gadget-export.h"
#include "drd.h"

static int cdns3_idle_init(struct cdns3 *cdns);

struct cdns3_host_priv {
	struct xhci_ctrl xhci_ctrl;
	struct cdns3 cdns;
};

struct cdns3_gadget_priv {
	struct cdns3 cdns;
};

static inline
struct cdns3_role_driver *cdns3_get_current_role_driver(struct cdns3 *cdns)
{
	WARN_ON(!cdns->roles[cdns->role]);
	return cdns->roles[cdns->role];
}

static int cdns3_role_start(struct cdns3 *cdns, enum usb_role role)
{
	int ret;

	if (WARN_ON(role > USB_ROLE_DEVICE))
		return 0;

	mutex_lock(&cdns->mutex);
	cdns->role = role;
	mutex_unlock(&cdns->mutex);

	if (!cdns->roles[role])
		return -ENXIO;

	if (cdns->roles[role]->state == CDNS3_ROLE_STATE_ACTIVE)
		return 0;

	mutex_lock(&cdns->mutex);
	ret = cdns->roles[role]->start(cdns);
	if (!ret)
		cdns->roles[role]->state = CDNS3_ROLE_STATE_ACTIVE;
	mutex_unlock(&cdns->mutex);

	return ret;
}

static void cdns3_role_stop(struct cdns3 *cdns)
{
	enum usb_role role = cdns->role;

	if (WARN_ON(role > USB_ROLE_DEVICE))
		return;

	if (cdns->roles[role]->state == CDNS3_ROLE_STATE_INACTIVE)
		return;

	mutex_lock(&cdns->mutex);
	cdns->roles[role]->stop(cdns);
	cdns->roles[role]->state = CDNS3_ROLE_STATE_INACTIVE;
	mutex_unlock(&cdns->mutex);
}

static void cdns3_exit_roles(struct cdns3 *cdns)
{
	cdns3_role_stop(cdns);
	cdns3_drd_exit(cdns);
}

static enum usb_role cdsn3_hw_role_state_machine(struct cdns3 *cdns);

/**
 * cdns3_core_init_role - initialize role of operation
 * @cdns: Pointer to cdns3 structure
 *
 * Returns 0 on success otherwise negative errno
 */
static int cdns3_core_init_role(struct cdns3 *cdns)
{
	struct udevice *dev = cdns->dev;
	enum usb_dr_mode best_dr_mode;
	enum usb_dr_mode dr_mode;
	int ret = 0;

	dr_mode = usb_get_dr_mode(dev->node);
	cdns->role = USB_ROLE_NONE;

	/*
	 * If driver can't read mode by means of usb_get_dr_mode function then
	 * chooses mode according with Kernel configuration. This setting
	 * can be restricted later depending on strap pin configuration.
	 */
	if (dr_mode == USB_DR_MODE_UNKNOWN) {
		if (IS_ENABLED(CONFIG_USB_CDNS3_HOST) &&
		    IS_ENABLED(CONFIG_USB_CDNS3_GADGET))
			dr_mode = USB_DR_MODE_OTG;
		else if (IS_ENABLED(CONFIG_USB_CDNS3_HOST))
			dr_mode = USB_DR_MODE_HOST;
		else if (IS_ENABLED(CONFIG_USB_CDNS3_GADGET))
			dr_mode = USB_DR_MODE_PERIPHERAL;
	}

	/*
	 * At this point cdns->dr_mode contains strap configuration.
	 * Driver try update this setting considering kernel configuration
	 */
	best_dr_mode = cdns->dr_mode;

	ret = cdns3_idle_init(cdns);
	if (ret)
		return ret;

	if (dr_mode == USB_DR_MODE_OTG) {
		best_dr_mode = cdns->dr_mode;
	} else if (cdns->dr_mode == USB_DR_MODE_OTG) {
		best_dr_mode = dr_mode;
	} else if (cdns->dr_mode != dr_mode) {
		dev_err(dev, "Incorrect DRD configuration\n");
		return -EINVAL;
	}

	dr_mode = best_dr_mode;

#if defined(CONFIG_SPL_USB_HOST_SUPPORT) || !defined(CONFIG_SPL_BUILD)
	if (dr_mode == USB_DR_MODE_OTG || dr_mode == USB_DR_MODE_HOST) {
		ret = cdns3_host_init(cdns);
		if (ret) {
			dev_err(dev, "Host initialization failed with %d\n",
				ret);
			goto err;
		}
	}
#endif

#if CONFIG_IS_ENABLED(DM_USB_GADGET)
	if (dr_mode == USB_DR_MODE_OTG || dr_mode == USB_DR_MODE_PERIPHERAL) {
		ret = cdns3_gadget_init(cdns);
		if (ret) {
			dev_err(dev, "Device initialization failed with %d\n",
				ret);
			goto err;
		}
	}
#endif

	cdns->dr_mode = dr_mode;

	ret = cdns3_drd_update_mode(cdns);
	if (ret)
		goto err;

	if (cdns->dr_mode != USB_DR_MODE_OTG) {
		ret = cdns3_hw_role_switch(cdns);
		if (ret)
			goto err;
	}

	return ret;
err:
	cdns3_exit_roles(cdns);
	return ret;
}

/**
 * cdsn3_hw_role_state_machine - role switch state machine based on hw events
 * @cdns: Pointer to controller structure.
 *
 * Returns next role to be entered based on hw events.
 */
static enum usb_role cdsn3_hw_role_state_machine(struct cdns3 *cdns)
{
	enum usb_role role;
	int id, vbus;

	if (cdns->dr_mode != USB_DR_MODE_OTG)
		goto not_otg;

	id = cdns3_get_id(cdns);
	vbus = cdns3_get_vbus(cdns);

	/*
	 * Role change state machine
	 * Inputs: ID, VBUS
	 * Previous state: cdns->role
	 * Next state: role
	 */
	role = cdns->role;

	switch (role) {
	case USB_ROLE_NONE:
		/*
		 * Driver treats USB_ROLE_NONE synonymous to IDLE state from
		 * controller specification.
		 */
		if (!id)
			role = USB_ROLE_HOST;
		else if (vbus)
			role = USB_ROLE_DEVICE;
		break;
	case USB_ROLE_HOST: /* from HOST, we can only change to NONE */
		if (id)
			role = USB_ROLE_NONE;
		break;
	case USB_ROLE_DEVICE: /* from GADGET, we can only change to NONE*/
		if (!vbus)
			role = USB_ROLE_NONE;
		break;
	}

	dev_dbg(cdns->dev, "role %d -> %d\n", cdns->role, role);

	return role;

not_otg:
	if (cdns3_is_host(cdns))
		role = USB_ROLE_HOST;
	if (cdns3_is_device(cdns))
		role = USB_ROLE_DEVICE;

	return role;
}

static int cdns3_idle_role_start(struct cdns3 *cdns)
{
	return 0;
}

static void cdns3_idle_role_stop(struct cdns3 *cdns)
{
	/* Program Lane swap and bring PHY out of RESET */
	generic_phy_reset(&cdns->usb3_phy);
}

static int cdns3_idle_init(struct cdns3 *cdns)
{
	struct cdns3_role_driver *rdrv;

	rdrv = devm_kzalloc(cdns->dev, sizeof(*rdrv), GFP_KERNEL);
	if (!rdrv)
		return -ENOMEM;

	rdrv->start = cdns3_idle_role_start;
	rdrv->stop = cdns3_idle_role_stop;
	rdrv->state = CDNS3_ROLE_STATE_INACTIVE;
	rdrv->suspend = NULL;
	rdrv->resume = NULL;
	rdrv->name = "idle";

	cdns->roles[USB_ROLE_NONE] = rdrv;

	return 0;
}

/**
 * cdns3_hw_role_switch - switch roles based on HW state
 * @cdns3: controller
 */
int cdns3_hw_role_switch(struct cdns3 *cdns)
{
	enum usb_role real_role, current_role;
	int ret = 0;

	/* Do nothing if role based on syfs. */
	if (cdns->role_override)
		return 0;

	current_role = cdns->role;
	real_role = cdsn3_hw_role_state_machine(cdns);

	/* Do nothing if nothing changed */
	if (current_role == real_role)
		goto exit;

	cdns3_role_stop(cdns);

	dev_dbg(cdns->dev, "Switching role %d -> %d", current_role, real_role);

	ret = cdns3_role_start(cdns, real_role);
	if (ret) {
		/* Back to current role */
		dev_err(cdns->dev, "set %d has failed, back to %d\n",
			real_role, current_role);
		ret = cdns3_role_start(cdns, current_role);
		if (ret)
			dev_err(cdns->dev, "back to %d failed too\n",
				current_role);
	}
exit:
	return ret;
}

static int cdns3_probe(struct cdns3 *cdns)
{
	struct udevice *dev = cdns->dev;
	int ret;

	cdns->xhci_regs = dev_remap_addr_name(dev, "xhci");
	if (!cdns->xhci_regs)
		return -EINVAL;

	cdns->dev_regs = dev_remap_addr_name(dev, "dev");
	if (!cdns->dev_regs)
		return -EINVAL;

	mutex_init(&cdns->mutex);

	ret = generic_phy_get_by_name(dev, "cdns3,usb2-phy", &cdns->usb2_phy);
	if (ret)
		dev_warn(dev, "Unable to get USB2 phy (ret %d)\n", ret);

	ret = generic_phy_init(&cdns->usb2_phy);
	if (ret)
		return ret;

	ret = generic_phy_get_by_name(dev, "cdns3,usb3-phy", &cdns->usb3_phy);
	if (ret)
		dev_warn(dev, "Unable to get USB3 phy (ret %d)\n", ret);

	ret = generic_phy_init(&cdns->usb3_phy);
	if (ret)
		return ret;

	ret = generic_phy_power_on(&cdns->usb2_phy);
	if (ret)
		return ret;

	ret = generic_phy_power_on(&cdns->usb3_phy);
	if (ret)
		return ret;

	ret = cdns3_drd_init(cdns);
	if (ret)
		return ret;

	ret = cdns3_core_init_role(cdns);
	if (ret)
		return ret;

	dev_dbg(dev, "Cadence USB3 core: probe succeed\n");

	return 0;
}

static int cdns3_remove(struct cdns3 *cdns)
{
	cdns3_exit_roles(cdns);
	generic_phy_power_off(&cdns->usb2_phy);
	generic_phy_power_off(&cdns->usb3_phy);
	generic_phy_exit(&cdns->usb2_phy);
	generic_phy_exit(&cdns->usb3_phy);
	return 0;
}

static const struct udevice_id cdns3_ids[] = {
	{ .compatible = "cdns,usb3" },
	{ },
};

int cdns3_bind(struct udevice *parent)
{
	enum usb_dr_mode dr_mode;
	struct udevice *dev;
	const char *driver;
	const char *name;
	ofnode node;
	int ret;

	node = ofnode_by_compatible(parent->node, "cdns,usb3");
	if (!ofnode_valid(node)) {
		ret = -ENODEV;
		goto fail;
	}

	name = ofnode_get_name(node);
	dr_mode = usb_get_dr_mode(node);

	switch (dr_mode) {
#if defined(CONFIG_SPL_USB_HOST_SUPPORT) || \
	(!defined(CONFIG_SPL_BUILD) && defined(CONFIG_USB_HOST))
	case USB_DR_MODE_HOST:
		debug("%s: dr_mode: HOST\n", __func__);
		driver = "cdns-usb3-host";
		break;
#endif
#if CONFIG_IS_ENABLED(DM_USB_GADGET)
	case USB_DR_MODE_PERIPHERAL:
		debug("%s: dr_mode: PERIPHERAL\n", __func__);
		driver = "cdns-usb3-peripheral";
		break;
#endif
	default:
		printf("%s: unsupported dr_mode\n", __func__);
		ret = -ENODEV;
		goto fail;
	};

	ret = device_bind_driver_to_node(parent, driver, name, node, &dev);
	if (ret) {
		printf("%s: not able to bind usb device mode\n",
		       __func__);
		goto fail;
	}

	return 0;

fail:
	/* do not return an error: failing to bind would hang the board */
	return 0;
}

#if CONFIG_IS_ENABLED(DM_USB_GADGET)
static int cdns3_gadget_probe(struct udevice *dev)
{
	struct cdns3_gadget_priv *priv = dev_get_priv(dev);
	struct cdns3 *cdns = &priv->cdns;

	cdns->dev = dev;

	return cdns3_probe(cdns);
}

static int cdns3_gadget_remove(struct udevice *dev)
{
	struct cdns3_gadget_priv *priv = dev_get_priv(dev);
	struct cdns3 *cdns = &priv->cdns;

	return cdns3_remove(cdns);
}

U_BOOT_DRIVER(cdns_usb3_peripheral) = {
	.name	= "cdns-usb3-peripheral",
	.id	= UCLASS_USB_GADGET_GENERIC,
	.of_match = cdns3_ids,
	.probe = cdns3_gadget_probe,
	.remove = cdns3_gadget_remove,
	.priv_auto_alloc_size = sizeof(struct cdns3_gadget_priv),
	.flags = DM_FLAG_ALLOC_PRIV_DMA,
};
#endif

#if defined(CONFIG_SPL_USB_HOST_SUPPORT) || \
	(!defined(CONFIG_SPL_BUILD) && defined(CONFIG_USB_HOST))
static int cdns3_host_probe(struct udevice *dev)
{
	struct cdns3_host_priv *priv = dev_get_priv(dev);
	struct cdns3 *cdns = &priv->cdns;

	cdns->dev = dev;

	return cdns3_probe(cdns);
}

static int cdns3_host_remove(struct udevice *dev)
{
	struct cdns3_host_priv *priv = dev_get_priv(dev);
	struct cdns3 *cdns = &priv->cdns;

	return cdns3_remove(cdns);
}

U_BOOT_DRIVER(cdns_usb3_host) = {
	.name	= "cdns-usb3-host",
	.id	= UCLASS_USB,
	.of_match = cdns3_ids,
	.probe = cdns3_host_probe,
	.remove = cdns3_host_remove,
	.priv_auto_alloc_size = sizeof(struct cdns3_host_priv),
	.ops = &xhci_usb_ops,
	.flags = DM_FLAG_ALLOC_PRIV_DMA,
};
#endif
