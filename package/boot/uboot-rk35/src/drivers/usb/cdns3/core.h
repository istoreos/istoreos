/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Cadence USBSS DRD Header File.
 *
 * Copyright (C) 2017-2018 NXP
 * Copyright (C) 2018-2019 Cadence.
 *
 * Authors: Peter Chen <peter.chen@nxp.com>
 *          Pawel Laszczak <pawell@cadence.com>
 */
#include <linux/compiler.h>
#include <linux/types.h>
#include <linux/usb/otg.h>
#include <generic-phy.h>

#ifndef __LINUX_CDNS3_CORE_H
#define __LINUX_CDNS3_CORE_H

enum usb_role {
	USB_ROLE_NONE,
	USB_ROLE_HOST,
	USB_ROLE_DEVICE,
};

struct cdns3;

/**
 * struct cdns3_role_driver - host/gadget role driver
 * @start: start this role
 * @stop: stop this role
 * @suspend: suspend callback for this role
 * @resume: resume callback for this role
 * @irq: irq handler for this role
 * @name: role name string (host/gadget)
 * @state: current state
 */
struct cdns3_role_driver {
	int (*start)(struct cdns3 *cdns);
	void (*stop)(struct cdns3 *cdns);
	int (*suspend)(struct cdns3 *cdns, bool do_wakeup);
	int (*resume)(struct cdns3 *cdns, bool hibernated);
	const char *name;
#define CDNS3_ROLE_STATE_INACTIVE	0
#define CDNS3_ROLE_STATE_ACTIVE		1
	int state;
};

#define CDNS3_XHCI_RESOURCES_NUM	2
/**
 * struct cdns3 - Representation of Cadence USB3 DRD controller.
 * @dev: pointer to Cadence device struct
 * @xhci_regs: pointer to base of xhci registers
 * @dev_regs: pointer to base of dev registers
 * @otg_v0_regs: pointer to base of v0 otg registers
 * @otg_v1_regs: pointer to base of v1 otg registers
 * @otg_regs: pointer to base of otg registers
 * @otg_irq: irq number for otg controller
 * @dev_irq: irq number for device controller
 * @roles: array of supported roles for this controller
 * @role: current role
 * @host_dev: the child host device pointer for cdns3 core
 * @gadget_dev: the child gadget device pointer for cdns3 core
 * @usb2_phy: pointer to USB2 PHY
 * @usb3_phy: pointer to USB3 PHY
 * @mutex: the mutex for concurrent code at driver
 * @dr_mode: supported mode of operation it can be only Host, only Device
 *           or OTG mode that allow to switch between Device and Host mode.
 *           This field based on firmware setting, kernel configuration
 *           and hardware configuration.
 * @role_sw: pointer to role switch object.
 * @role_override: set 1 if role rely on SW.
 */
struct cdns3 {
	struct udevice			*dev;
	void __iomem			*xhci_regs;
	struct cdns3_usb_regs __iomem	*dev_regs;

	struct cdns3_otg_legacy_regs	*otg_v0_regs;
	struct cdns3_otg_regs		*otg_v1_regs;
	struct cdns3_otg_common_regs	*otg_regs;
#define CDNS3_CONTROLLER_V0	0
#define CDNS3_CONTROLLER_V1	1
	u32				version;

	int				otg_irq;
	int				dev_irq;
	struct cdns3_role_driver	*roles[USB_ROLE_DEVICE + 1];
	enum usb_role			role;
	struct cdns3_device		*gadget_dev;
	struct phy			usb2_phy;
	struct phy			usb3_phy;
	/* mutext used in workqueue*/
	struct mutex			mutex;
	enum usb_dr_mode		dr_mode;
	int				role_override;
};

int cdns3_hw_role_switch(struct cdns3 *cdns);

/**
 * cdns3_bind - generic bind function
 * @parent - pointer to parent udevice of which cdns3 USB controller
 *           node is child of
 *
 * return 0 on success, negative errno otherwise
 */
int cdns3_bind(struct udevice *dev);
#endif /* __LINUX_CDNS3_CORE_H */
