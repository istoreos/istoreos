/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright 2011 Freescale Semiconductor, Inc.
 *	Andy Fleming <afleming@gmail.com>
 *
 * This file pretty much stolen from Linux's mii.h/ethtool.h/phy.h
 */

#ifndef _PHY_INTERFACE_H
#define _PHY_INTERFACE_H

typedef enum {
	PHY_INTERFACE_MODE_MII,
	PHY_INTERFACE_MODE_GMII,
	PHY_INTERFACE_MODE_SGMII,
	PHY_INTERFACE_MODE_SGMII_2500,
	PHY_INTERFACE_MODE_QSGMII,
	PHY_INTERFACE_MODE_TBI,
	PHY_INTERFACE_MODE_RMII,
	PHY_INTERFACE_MODE_RGMII,
	PHY_INTERFACE_MODE_RGMII_ID,
	PHY_INTERFACE_MODE_RGMII_RXID,
	PHY_INTERFACE_MODE_RGMII_TXID,
	PHY_INTERFACE_MODE_RTBI,
	PHY_INTERFACE_MODE_XGMII,
	PHY_INTERFACE_MODE_XAUI,
	PHY_INTERFACE_MODE_RXAUI,
	PHY_INTERFACE_MODE_SFI,
	PHY_INTERFACE_MODE_INTERNAL,
	PHY_INTERFACE_MODE_NONE,	/* Must be last */

	PHY_INTERFACE_MODE_COUNT,
} phy_interface_t;

static const char * const phy_interface_strings[] = {
	[PHY_INTERFACE_MODE_MII]		= "mii",
	[PHY_INTERFACE_MODE_GMII]		= "gmii",
	[PHY_INTERFACE_MODE_SGMII]		= "sgmii",
	[PHY_INTERFACE_MODE_SGMII_2500]		= "sgmii-2500",
	[PHY_INTERFACE_MODE_QSGMII]		= "qsgmii",
	[PHY_INTERFACE_MODE_TBI]		= "tbi",
	[PHY_INTERFACE_MODE_RMII]		= "rmii",
	[PHY_INTERFACE_MODE_RGMII]		= "rgmii",
	[PHY_INTERFACE_MODE_RGMII_ID]		= "rgmii-id",
	[PHY_INTERFACE_MODE_RGMII_RXID]		= "rgmii-rxid",
	[PHY_INTERFACE_MODE_RGMII_TXID]		= "rgmii-txid",
	[PHY_INTERFACE_MODE_RTBI]		= "rtbi",
	[PHY_INTERFACE_MODE_XGMII]		= "xgmii",
	[PHY_INTERFACE_MODE_XAUI]		= "xaui",
	[PHY_INTERFACE_MODE_RXAUI]		= "rxaui",
	[PHY_INTERFACE_MODE_SFI]		= "sfi",
	[PHY_INTERFACE_MODE_INTERNAL]		= "internal",
	[PHY_INTERFACE_MODE_NONE]		= "",
};

static inline const char *phy_string_for_interface(phy_interface_t i)
{
	/* Default to unknown */
	if (i > PHY_INTERFACE_MODE_NONE)
		i = PHY_INTERFACE_MODE_NONE;

	return phy_interface_strings[i];
}

#endif /* _PHY_INTERFACE_H */
