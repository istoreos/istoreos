// SPDX-License-Identifier: GPL-2.0
/*
 * Cadence USBSS DRD Driver - host side
 *
 * Copyright (C) 2018-2019 Cadence Design Systems.
 * Copyright (C) 2017-2018 NXP
 *
 * Authors: Peter Chen <peter.chen@nxp.com>
 *          Pawel Laszczak <pawell@cadence.com>
 */
#include <dm.h>
#include <linux/compat.h>
#include <usb.h>
#include <usb/xhci.h>

#include "core.h"
#include "drd.h"

static int __cdns3_host_init(struct cdns3 *cdns)
{
	struct xhci_hcor *hcor;
	struct xhci_hccr *hccr;

	cdns3_drd_switch_host(cdns, 1);

	hccr = (struct xhci_hccr *)cdns->xhci_regs;
	hcor = (struct xhci_hcor *)(cdns->xhci_regs +
			HC_LENGTH(xhci_readl(&(hccr)->cr_capbase)));

	return xhci_register(cdns->dev, hccr, hcor);
}

static void cdns3_host_exit(struct cdns3 *cdns)
{
	xhci_deregister(cdns->dev);
	cdns3_drd_switch_host(cdns, 0);
}

int cdns3_host_init(struct cdns3 *cdns)
{
	struct cdns3_role_driver *rdrv;

	rdrv = devm_kzalloc(cdns->dev, sizeof(*rdrv), GFP_KERNEL);
	if (!rdrv)
		return -ENOMEM;

	rdrv->start	= __cdns3_host_init;
	rdrv->stop	= cdns3_host_exit;
	rdrv->state	= CDNS3_ROLE_STATE_INACTIVE;
	rdrv->name	= "host";

	cdns->roles[USB_ROLE_HOST] = rdrv;

	return 0;
}
