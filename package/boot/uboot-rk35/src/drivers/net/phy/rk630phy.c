// SPDX-License-Identifier: GPL-2.0+
/**
 *
 * Driver for ROCKCHIP RK630 Ethernet PHYs
 *
 * Copyright (c) 2020, Fuzhou Rockchip Electronics Co., Ltd
 *
 * David Wu <david.wu@rock-chips.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 */

#include <config.h>
#include <common.h>
#include <phy.h>

#define RK630_PHY_ID				0x00441400

/* PAGE 0 */
#define REG_INTERRUPT_STATUS			0X10
#define REG_INTERRUPT_MASK			0X11
#define REG_GLOBAL_CONFIGURATION		0X13
#define REG_MAC_ADDRESS0			0x16
#define REG_MAC_ADDRESS1			0x17
#define REG_MAC_ADDRESS2			0x18

#define REG_PAGE_SEL				0x1F

/* PAGE 1 */
#define REG_PAGE1_APS_CTRL			0x12
#define REG_PAGE1_UAPS_CONFIGURE		0X13
#define REG_PAGE1_EEE_CONFIGURE			0x17

/* PAGE 2 */
#define REG_PAGE2_AFE_CTRL			0x18

/* PAGE 6 */
#define REG_PAGE6_ADC_ANONTROL			0x10
#define REG_PAGE6_GAIN_ANONTROL			0x12
#define REG_PAGE6_AFE_RX_CTRL			0x13
#define REG_PAGE6_AFE_TX_CTRL			0x14
#define REG_PAGE6_AFE_DRIVER2			0x15
#define REG_PAGE6_CP_CURRENT			0x17
#define REG_PAGE6_ADC_OP_BIAS			0x18
#define REG_PAGE6_RX_DECTOR			0x19
#define REG_PAGE6_AFE_PDCW			0x1c

/* PAGE 8 */
#define REG_PAGE8_AFE_CTRL			0x18
#define REG_PAGE8_AUTO_CAL			0x1d

/*
 * Fixed address:
 * Addr: 1 --- RK630@S40
 *       2 --- RV1106@T22
 */
#define PHY_ADDR_S40 1
#define PHY_ADDR_T22 2

static int rk630_phy_startup(struct phy_device *phydev)
{
	int ret;

	/* Read the Status (2x to make sure link is right) */
	ret = genphy_update_link(phydev);
	if (ret)
		return ret;
	/* Read the Status (2x to make sure link is right) */
	phy_read(phydev, MDIO_DEVAD_NONE, MII_BMSR);

	return genphy_parse_link(phydev);
}

static void rk630_phy_s40_config_init(struct phy_device *phydev)
{
	phy_write(phydev, 0, MDIO_DEVAD_NONE,
		  phy_read(phydev, MDIO_DEVAD_NONE, 0) & ~BIT(13));

	/* Switch to page 1 */
	phy_write(phydev, MDIO_DEVAD_NONE, REG_PAGE_SEL, 0x0100);
	/* Disable APS */
	phy_write(phydev, MDIO_DEVAD_NONE, REG_PAGE1_APS_CTRL, 0x4824);
	/* Switch to page 2 */
	phy_write(phydev, MDIO_DEVAD_NONE, REG_PAGE_SEL, 0x0200);
	/* PHYAFE TRX optimization */
	phy_write(phydev, MDIO_DEVAD_NONE, REG_PAGE2_AFE_CTRL, 0x0000);
	/* Switch to page 6 */
	phy_write(phydev, MDIO_DEVAD_NONE, REG_PAGE_SEL, 0x0600);
	/* PHYAFE TX optimization */
	phy_write(phydev, MDIO_DEVAD_NONE, REG_PAGE6_AFE_TX_CTRL, 0x708f);
	/* PHYAFE RX optimization */
	phy_write(phydev, MDIO_DEVAD_NONE, REG_PAGE6_AFE_RX_CTRL, 0xf000);
	phy_write(phydev, MDIO_DEVAD_NONE, REG_PAGE6_AFE_DRIVER2, 0x1530);

	/* Switch to page 8 */
	phy_write(phydev, MDIO_DEVAD_NONE, REG_PAGE_SEL, 0x0800);
	/* PHYAFE TRX optimization */
	phy_write(phydev, MDIO_DEVAD_NONE, REG_PAGE8_AFE_CTRL, 0x00bc);

	/* Switch to page 0 */
	phy_write(phydev, MDIO_DEVAD_NONE, REG_PAGE_SEL, 0x0000);
}

static void rk630_phy_t22_config_init(struct phy_device *phydev)
{
	/* Switch to page 1 */
	phy_write(phydev, MDIO_DEVAD_NONE, REG_PAGE_SEL, 0x0100);
	/* Disable APS */
	phy_write(phydev, MDIO_DEVAD_NONE, REG_PAGE1_APS_CTRL, 0x4824);
	/* Switch to page 2 */
	phy_write(phydev, MDIO_DEVAD_NONE, REG_PAGE_SEL, 0x0200);
	/* PHYAFE TRX optimization */
	phy_write(phydev, MDIO_DEVAD_NONE, REG_PAGE2_AFE_CTRL, 0x0000);
	/* Switch to page 6 */
	phy_write(phydev, MDIO_DEVAD_NONE, REG_PAGE_SEL, 0x0600);
	/* PHYAFE ADC optimization */
	phy_write(phydev, MDIO_DEVAD_NONE, REG_PAGE6_ADC_ANONTROL, 0x5540);
	/* PHYAFE Gain optimization */
	phy_write(phydev, MDIO_DEVAD_NONE, REG_PAGE6_GAIN_ANONTROL, 0x0400);
	/* PHYAFE EQ optimization */
	phy_write(phydev, MDIO_DEVAD_NONE, REG_PAGE6_AFE_TX_CTRL, 0x1088);
	/* PHYAFE TX optimization */
	phy_write(phydev, MDIO_DEVAD_NONE, REG_PAGE6_AFE_DRIVER2, 0x3030);
	/* PHYAFE CP current optimization */
	phy_write(phydev, MDIO_DEVAD_NONE, REG_PAGE6_CP_CURRENT, 0x0575);
	/* ADC OP BIAS optimization */
	phy_write(phydev, MDIO_DEVAD_NONE, REG_PAGE6_ADC_OP_BIAS, 0x0000);
	/* Rx signal detctor level optimization */
	phy_write(phydev, MDIO_DEVAD_NONE, REG_PAGE6_RX_DECTOR, 0x0408);
	/* PHYAFE PDCW optimization */
	phy_write(phydev, MDIO_DEVAD_NONE, REG_PAGE6_AFE_PDCW, 0x8880);

	/* Switch to page 8 */
	phy_write(phydev, MDIO_DEVAD_NONE, REG_PAGE_SEL, 0x0800);
	/* Disable auto-cal */
	phy_write(phydev, MDIO_DEVAD_NONE, REG_PAGE8_AUTO_CAL, 0x0844);

	/* Switch to page 0 */
	phy_write(phydev, MDIO_DEVAD_NONE, REG_PAGE_SEL, 0x0000);
}
static int rk630_phy_config_init(struct phy_device *phydev)
{
	switch (phydev->addr) {
	case PHY_ADDR_S40:
		rk630_phy_s40_config_init(phydev);
		break;
	case PHY_ADDR_T22:
		rk630_phy_t22_config_init(phydev);
		break;
	default:
		printf("Unsupported address for current phy: %d\n",
		       phydev->addr);
		return -EINVAL;
	}

	return 0;
}

static struct phy_driver RK630_driver = {
	.name = "Rockchip RK630",
	.uid = RK630_PHY_ID,
	.mask = 0xffffff,
	.features = PHY_BASIC_FEATURES,
	.config = &rk630_phy_config_init,
	.startup = &rk630_phy_startup,
};

int phy_rk630_init(void)
{
	phy_register(&RK630_driver);
	return 0;
}
