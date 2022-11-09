// SPDX-License-Identifier: GPL-2.0
/*
 * Amlogic G12A DWC3 Glue layer
 *
 * Copyright (C) 2019 BayLibre, SAS
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 */

#include <common.h>
#include <asm-generic/io.h>
#include <dm.h>
#include <dm/device-internal.h>
#include <dm/lists.h>
#include <dwc3-uboot.h>
#include <generic-phy.h>
#include <linux/usb/ch9.h>
#include <linux/usb/gadget.h>
#include <malloc.h>
#include <regmap.h>
#include <usb.h>
#include "core.h"
#include "gadget.h"
#include <reset.h>
#include <clk.h>
#include <power/regulator.h>
#include <linux/bitfield.h>
#include <linux/bitops.h>
#include <linux/compat.h>

/* USB2 Ports Control Registers */

#define U2P_REG_SIZE						0x20

#define U2P_R0							0x0
	#define U2P_R0_HOST_DEVICE				BIT(0)
	#define U2P_R0_POWER_OK					BIT(1)
	#define U2P_R0_HAST_MODE				BIT(2)
	#define U2P_R0_POWER_ON_RESET				BIT(3)
	#define U2P_R0_ID_PULLUP				BIT(4)
	#define U2P_R0_DRV_VBUS					BIT(5)

#define U2P_R1							0x4
	#define U2P_R1_PHY_READY				BIT(0)
	#define U2P_R1_ID_DIG					BIT(1)
	#define U2P_R1_OTG_SESSION_VALID			BIT(2)
	#define U2P_R1_VBUS_VALID				BIT(3)

/* USB Glue Control Registers */

#define USB_R0							0x80
	#define USB_R0_P30_LANE0_TX2RX_LOOPBACK			BIT(17)
	#define USB_R0_P30_LANE0_EXT_PCLK_REQ			BIT(18)
	#define USB_R0_P30_PCS_RX_LOS_MASK_VAL_MASK		GENMASK(28, 19)
	#define USB_R0_U2D_SS_SCALEDOWN_MODE_MASK		GENMASK(30, 29)
	#define USB_R0_U2D_ACT					BIT(31)

#define USB_R1							0x84
	#define USB_R1_U3H_BIGENDIAN_GS				BIT(0)
	#define USB_R1_U3H_PME_ENABLE				BIT(1)
	#define USB_R1_U3H_HUB_PORT_OVERCURRENT_MASK		GENMASK(4, 2)
	#define USB_R1_U3H_HUB_PORT_PERM_ATTACH_MASK		GENMASK(9, 7)
	#define USB_R1_U3H_HOST_U2_PORT_DISABLE_MASK		GENMASK(13, 12)
	#define USB_R1_U3H_HOST_U3_PORT_DISABLE			BIT(16)
	#define USB_R1_U3H_HOST_PORT_POWER_CONTROL_PRESENT	BIT(17)
	#define USB_R1_U3H_HOST_MSI_ENABLE			BIT(18)
	#define USB_R1_U3H_FLADJ_30MHZ_REG_MASK			GENMASK(24, 19)
	#define USB_R1_P30_PCS_TX_SWING_FULL_MASK		GENMASK(31, 25)

#define USB_R2							0x88
	#define USB_R2_P30_PCS_TX_DEEMPH_3P5DB_MASK		GENMASK(25, 20)
	#define USB_R2_P30_PCS_TX_DEEMPH_6DB_MASK		GENMASK(31, 26)

#define USB_R3							0x8c
	#define USB_R3_P30_SSC_ENABLE				BIT(0)
	#define USB_R3_P30_SSC_RANGE_MASK			GENMASK(3, 1)
	#define USB_R3_P30_SSC_REF_CLK_SEL_MASK			GENMASK(12, 4)
	#define USB_R3_P30_REF_SSP_EN				BIT(13)

#define USB_R4							0x90
	#define USB_R4_P21_PORT_RESET_0				BIT(0)
	#define USB_R4_P21_SLEEP_M0				BIT(1)
	#define USB_R4_MEM_PD_MASK				GENMASK(3, 2)
	#define USB_R4_P21_ONLY					BIT(4)

#define USB_R5							0x94
	#define USB_R5_ID_DIG_SYNC				BIT(0)
	#define USB_R5_ID_DIG_REG				BIT(1)
	#define USB_R5_ID_DIG_CFG_MASK				GENMASK(3, 2)
	#define USB_R5_ID_DIG_EN_0				BIT(4)
	#define USB_R5_ID_DIG_EN_1				BIT(5)
	#define USB_R5_ID_DIG_CURR				BIT(6)
	#define USB_R5_ID_DIG_IRQ				BIT(7)
	#define USB_R5_ID_DIG_TH_MASK				GENMASK(15, 8)
	#define USB_R5_ID_DIG_CNT_MASK				GENMASK(23, 16)

enum {
	USB2_HOST_PHY = 0,
	USB2_OTG_PHY,
	USB3_HOST_PHY,
	PHY_COUNT,
};

static const char *phy_names[PHY_COUNT] = {
	"usb2-phy0", "usb2-phy1", "usb3-phy0",
};

struct dwc3_meson_g12a {
	struct udevice		*dev;
	struct regmap           *regmap;
	struct clk		clk;
	struct reset_ctl	reset;
	struct phy		phys[PHY_COUNT];
	enum usb_dr_mode	otg_mode;
	enum usb_dr_mode	otg_phy_mode;
	unsigned int		usb2_ports;
	unsigned int		usb3_ports;
#if CONFIG_IS_ENABLED(DM_REGULATOR)
	struct udevice		*vbus_supply;
#endif
};

#define U2P_REG_SIZE						0x20
#define USB_REG_OFFSET						0x80

static void dwc3_meson_g12a_usb2_set_mode(struct dwc3_meson_g12a *priv,
					  int i, enum usb_dr_mode mode)
{
	switch (mode) {
	case USB_DR_MODE_HOST:
	case USB_DR_MODE_OTG:
	case USB_DR_MODE_UNKNOWN:
		regmap_update_bits(priv->regmap, U2P_R0 + (U2P_REG_SIZE * i),
				U2P_R0_HOST_DEVICE,
				U2P_R0_HOST_DEVICE);
		break;

	case USB_DR_MODE_PERIPHERAL:
		regmap_update_bits(priv->regmap, U2P_R0 + (U2P_REG_SIZE * i),
				U2P_R0_HOST_DEVICE, 0);
		break;
	}
}

static int dwc3_meson_g12a_usb2_init(struct dwc3_meson_g12a *priv)
{
	int i;

	if (priv->otg_mode == USB_DR_MODE_PERIPHERAL)
		priv->otg_phy_mode = USB_DR_MODE_PERIPHERAL;
	else
		priv->otg_phy_mode = USB_DR_MODE_HOST;

	for (i = 0 ; i < USB3_HOST_PHY ; ++i) {
		if (!priv->phys[i].dev)
			continue;

		regmap_update_bits(priv->regmap, U2P_R0 + (U2P_REG_SIZE * i),
				   U2P_R0_POWER_ON_RESET,
				   U2P_R0_POWER_ON_RESET);

		if (i == USB2_OTG_PHY) {
			regmap_update_bits(priv->regmap,
					   U2P_R0 + (U2P_REG_SIZE * i),
					   U2P_R0_ID_PULLUP | U2P_R0_DRV_VBUS,
					   U2P_R0_ID_PULLUP | U2P_R0_DRV_VBUS);

			dwc3_meson_g12a_usb2_set_mode(priv, i,
						      priv->otg_phy_mode);
		} else
			dwc3_meson_g12a_usb2_set_mode(priv, i,
						      USB_DR_MODE_HOST);

		regmap_update_bits(priv->regmap, U2P_R0 + (U2P_REG_SIZE * i),
				   U2P_R0_POWER_ON_RESET, 0);
	}

	return 0;
}

static void dwc3_meson_g12a_usb3_init(struct dwc3_meson_g12a *priv)
{
	regmap_update_bits(priv->regmap, USB_R3,
			USB_R3_P30_SSC_RANGE_MASK |
			USB_R3_P30_REF_SSP_EN,
			USB_R3_P30_SSC_ENABLE |
			FIELD_PREP(USB_R3_P30_SSC_RANGE_MASK, 2) |
			USB_R3_P30_REF_SSP_EN);
	udelay(2);

	regmap_update_bits(priv->regmap, USB_R2,
			USB_R2_P30_PCS_TX_DEEMPH_3P5DB_MASK,
			FIELD_PREP(USB_R2_P30_PCS_TX_DEEMPH_3P5DB_MASK, 0x15));

	regmap_update_bits(priv->regmap, USB_R2,
			USB_R2_P30_PCS_TX_DEEMPH_6DB_MASK,
			FIELD_PREP(USB_R2_P30_PCS_TX_DEEMPH_6DB_MASK, 0x20));

	udelay(2);

	regmap_update_bits(priv->regmap, USB_R1,
			USB_R1_U3H_HOST_PORT_POWER_CONTROL_PRESENT,
			USB_R1_U3H_HOST_PORT_POWER_CONTROL_PRESENT);

	regmap_update_bits(priv->regmap, USB_R1,
			USB_R1_P30_PCS_TX_SWING_FULL_MASK,
			FIELD_PREP(USB_R1_P30_PCS_TX_SWING_FULL_MASK, 127));
}

static void dwc3_meson_g12a_usb_init_mode(struct dwc3_meson_g12a *priv)
{
	if (priv->otg_phy_mode == USB_DR_MODE_PERIPHERAL) {
		regmap_update_bits(priv->regmap, USB_R0,
				USB_R0_U2D_ACT, USB_R0_U2D_ACT);
		regmap_update_bits(priv->regmap, USB_R0,
				USB_R0_U2D_SS_SCALEDOWN_MODE_MASK, 0);
		regmap_update_bits(priv->regmap, USB_R4,
				USB_R4_P21_SLEEP_M0, USB_R4_P21_SLEEP_M0);
	} else {
		regmap_update_bits(priv->regmap, USB_R0,
				USB_R0_U2D_ACT, 0);
		regmap_update_bits(priv->regmap, USB_R4,
				USB_R4_P21_SLEEP_M0, 0);
	}
}

static int dwc3_meson_g12a_usb_init(struct dwc3_meson_g12a *priv)
{
	int ret;

	ret = dwc3_meson_g12a_usb2_init(priv);
	if (ret)
		return ret;

	regmap_update_bits(priv->regmap, USB_R1,
			USB_R1_U3H_FLADJ_30MHZ_REG_MASK,
			FIELD_PREP(USB_R1_U3H_FLADJ_30MHZ_REG_MASK, 0x20));

	regmap_update_bits(priv->regmap, USB_R5,
			USB_R5_ID_DIG_EN_0,
			USB_R5_ID_DIG_EN_0);
	regmap_update_bits(priv->regmap, USB_R5,
			USB_R5_ID_DIG_EN_1,
			USB_R5_ID_DIG_EN_1);
	regmap_update_bits(priv->regmap, USB_R5,
			USB_R5_ID_DIG_TH_MASK,
			FIELD_PREP(USB_R5_ID_DIG_TH_MASK, 0xff));

	/* If we have an actual SuperSpeed port, initialize it */
	if (priv->usb3_ports)
		dwc3_meson_g12a_usb3_init(priv);

	dwc3_meson_g12a_usb_init_mode(priv);

	return 0;
}

int dwc3_meson_g12a_force_mode(struct udevice *dev, enum usb_dr_mode mode)
{
	struct dwc3_meson_g12a *priv = dev_get_platdata(dev);

	if (!priv)
		return -EINVAL;

	if (mode != USB_DR_MODE_HOST && mode != USB_DR_MODE_PERIPHERAL)
		return -EINVAL;

	if (!priv->phys[USB2_OTG_PHY].dev)
		return -EINVAL;

	if (mode == priv->otg_mode)
		return 0;

	if (mode == USB_DR_MODE_HOST)
		debug("%s: switching to Host Mode\n", __func__);
	else
		debug("%s: switching to Device Mode\n", __func__);

#if CONFIG_IS_ENABLED(DM_REGULATOR)
	if (priv->vbus_supply) {
		int ret = regulator_set_enable(priv->vbus_supply,
					(mode == USB_DR_MODE_PERIPHERAL));
		if (ret)
			return ret;
	}
#endif
	priv->otg_phy_mode = mode;

	dwc3_meson_g12a_usb2_set_mode(priv, USB2_OTG_PHY, mode);

	dwc3_meson_g12a_usb_init_mode(priv);

	return 0;
}

static int dwc3_meson_g12a_get_phys(struct dwc3_meson_g12a *priv)
{
	int i, ret;

	for (i = 0 ; i < PHY_COUNT ; ++i) {
		ret = generic_phy_get_by_name(priv->dev, phy_names[i],
					      &priv->phys[i]);
		if (ret == -ENOENT)
			continue;

		if (ret)
			return ret;

		if (i == USB3_HOST_PHY)
			priv->usb3_ports++;
		else
			priv->usb2_ports++;
	}

	debug("%s: usb2 ports: %d\n", __func__, priv->usb2_ports);
	debug("%s: usb3 ports: %d\n", __func__, priv->usb3_ports);

	return 0;
}

static int dwc3_meson_g12a_reset_init(struct dwc3_meson_g12a *priv)
{
	int ret;

	ret = reset_get_by_index(priv->dev, 0, &priv->reset);
	if (ret)
		return ret;

	ret = reset_assert(&priv->reset);
	udelay(1);
	ret |= reset_deassert(&priv->reset);
	if (ret) {
		reset_free(&priv->reset);
		return ret;
	}

	return 0;
}

static int dwc3_meson_g12a_clk_init(struct dwc3_meson_g12a *priv)
{
	int ret;

	ret = clk_get_by_index(priv->dev, 0, &priv->clk);
	if (ret)
		return ret;

#if CONFIG_IS_ENABLED(CLK)
	ret = clk_enable(&priv->clk);
	if (ret) {
		clk_free(&priv->clk);
		return ret;
	}
#endif

	return 0;
}

static int dwc3_meson_g12a_probe(struct udevice *dev)
{
	struct dwc3_meson_g12a *priv = dev_get_platdata(dev);
	int ret, i;

	priv->dev = dev;

	ret = regmap_init_mem(dev_ofnode(dev), &priv->regmap);
	if (ret)
		return ret;

	ret = dwc3_meson_g12a_clk_init(priv);
	if (ret)
		return ret;

	ret = dwc3_meson_g12a_reset_init(priv);
	if (ret)
		return ret;

	ret = dwc3_meson_g12a_get_phys(priv);
	if (ret)
		return ret;

#if CONFIG_IS_ENABLED(DM_REGULATOR)
	ret = device_get_supply_regulator(dev, "vbus-supply",
					  &priv->vbus_supply);
	if (ret && ret != -ENOENT) {
		pr_err("Failed to get PHY regulator\n");
		return ret;
	}

	if (priv->vbus_supply) {
		ret = regulator_set_enable(priv->vbus_supply, true);
		if (ret)
			return ret;
	}
#endif

	priv->otg_mode = usb_get_dr_mode(dev->node);

	ret = dwc3_meson_g12a_usb_init(priv);
	if (ret)
		return ret;

	for (i = 0 ; i < PHY_COUNT ; ++i) {
		if (!priv->phys[i].dev)
			continue;

		ret = generic_phy_init(&priv->phys[i]);
		if (ret)
			goto err_phy_init;
	}

	return 0;

err_phy_init:
	for (i = 0 ; i < PHY_COUNT ; ++i) {
		if (!priv->phys[i].dev)
			continue;

		 generic_phy_exit(&priv->phys[i]);
	}

	return ret;
}

static int dwc3_meson_g12a_remove(struct udevice *dev)
{
	struct dwc3_meson_g12a *priv = dev_get_platdata(dev);
	int i;

	reset_release_all(&priv->reset, 1);

	clk_release_all(&priv->clk, 1);

	for (i = 0 ; i < PHY_COUNT ; ++i) {
		if (!priv->phys[i].dev)
			continue;

		 generic_phy_exit(&priv->phys[i]);
	}

	return dm_scan_fdt_dev(dev);
}

static const struct udevice_id dwc3_meson_g12a_ids[] = {
	{ .compatible = "amlogic,meson-g12a-usb-ctrl" },
	{ }
};

U_BOOT_DRIVER(dwc3_generic_wrapper) = {
	.name	= "dwc3-meson-g12a",
	.id	= UCLASS_SIMPLE_BUS,
	.of_match = dwc3_meson_g12a_ids,
	.probe = dwc3_meson_g12a_probe,
	.remove = dwc3_meson_g12a_remove,
	.platdata_auto_alloc_size = sizeof(struct dwc3_meson_g12a),

};
