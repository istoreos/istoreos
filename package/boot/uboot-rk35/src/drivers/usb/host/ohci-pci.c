// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2019
 * Heiko Schocher, DENX Software Engineering, hs@denx.de.
 *
 */

#include <common.h>
#include <dm.h>
#include <errno.h>
#include <pci.h>
#include <usb.h>
#include <asm/io.h>

#include "ohci.h"

static int ohci_pci_probe(struct udevice *dev)
{
	struct ohci_regs *regs;

	regs = dm_pci_map_bar(dev, PCI_BASE_ADDRESS_0, PCI_REGION_MEM);
	return ohci_register(dev, regs);
}

static int ohci_pci_remove(struct udevice *dev)
{
	return ohci_deregister(dev);
}

static const struct udevice_id ohci_pci_ids[] = {
	{ .compatible = "ohci-pci" },
	{ }
};

U_BOOT_DRIVER(ohci_pci) = {
	.name	= "ohci_pci",
	.id	= UCLASS_USB,
	.probe = ohci_pci_probe,
	.remove = ohci_pci_remove,
	.of_match = ohci_pci_ids,
	.ops	= &ohci_usb_ops,
	.platdata_auto_alloc_size = sizeof(struct usb_platdata),
	.priv_auto_alloc_size = sizeof(ohci_t),
	.flags	= DM_FLAG_ALLOC_PRIV_DMA,
};

static struct pci_device_id ohci_pci_supported[] = {
	{ PCI_DEVICE_CLASS(PCI_CLASS_SERIAL_USB_OHCI, ~0) },
	{},
};

U_BOOT_PCI_DEVICE(ohci_pci, ohci_pci_supported);
