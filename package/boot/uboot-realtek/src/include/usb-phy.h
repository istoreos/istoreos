/* Define USB PHY API */

#pragma once

struct usb2_phy;
struct usb3_phy;

int usb2_phy_init(struct usb2_phy *usb2phy);
int usb3_phy_init(struct usb3_phy *usb3phy);

int usb2_phy_switch_to_device(struct usb2_phy *usb2phy);
int usb2_phy_switch_to_host(struct usb2_phy *usb2phy);
