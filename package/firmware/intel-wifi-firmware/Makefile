#
# Copyright (C) 2014 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=intel-wifi-firmware
PKG_VERSION:=20230117
PKG_RELEASE:=1

PKG_SOURCE_URL:=@KERNEL/linux/kernel/firmware
PKG_SOURCE:=linux-firmware-$(PKG_VERSION).tar.xz
PKG_HASH:=df11e25ba2fb4d5343473757e17a3b4cef599250a26b1f7e0f038850f0cb3d64

PKG_MAINTAINER:=Felix Fietkau <nbd@nbd.name>

PKG_BUILD_DIR:=$(BUILD_DIR)/linux-firmware-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

RSTRIP:=:
STRIP:=:

define Package/firmware-default
  SECTION:=firmware
  CATEGORY:=Firmware
  URL:=http://git.kernel.org/cgit/linux/kernel/git/firmware/linux-firmware.git
  TITLE:=$(1)
  DEPENDS:=$(2)
endef

define Build/Compile

endef

Package/iwlwifi-firmware-ax201 = $(call Package/firmware-default,Intel AX201 firmware)
define Package/iwlwifi-firmware-ax201/install
	$(INSTALL_DIR) $(1)/lib/firmware
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/iwlwifi-QuZ-a0-hr-b0-66.ucode $(1)/lib/firmware
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/iwlwifi-so-a0-hr-b0-64.ucode $(1)/lib/firmware
endef
$(eval $(call BuildPackage,iwlwifi-firmware-ax201))

Package/iwlwifi-firmware-ax211 = $(call Package/firmware-default,Intel AX211 firmware)
define Package/iwlwifi-firmware-ax211/install
	$(INSTALL_DIR) $(1)/lib/firmware
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/iwlwifi-so-a0-gf-a0-64.ucode $(1)/lib/firmware
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/iwlwifi-so-a0-gf-a0.pnvm $(1)/lib/firmware
endef
$(eval $(call BuildPackage,iwlwifi-firmware-ax211))
