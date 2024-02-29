#
# Copyright (C) 2017 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=rtw89-oot
PKG_VERSION:=2024-01-19
PKG_RELEASE:=2

PKG_SOURCE_VERSION:=ebe87ac234a72a63a1b2ede911a874f1b7a6fe43
PKG_HASH:=54d70235dd2208673c0380f5ea9b9cec53a0f08b4f6e7892181cedd30a61b18e
PKG_SOURCE_URL_FILE:=$(PKG_SOURCE_VERSION).tar.gz
PKG_SOURCE:=rtw89-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://github.com/lwfinger/rtw89/archive/

PKG_BUILD_PARALLEL:=1

STAMP_CONFIGURED_DEPENDS := $(STAGING_DIR)/usr/include/mac80211-backport/backport/autoconf.h

include $(INCLUDE_DIR)/kernel.mk
include $(INCLUDE_DIR)/package.mk

TAR_OPTIONS+= --strip-components 1
TAR_CMD=$(HOST_TAR) -C $(1) $(TAR_OPTIONS)

define KernelPackage/rtw89-oot
  SUBMENU:=Wireless Drivers
  TITLE:=Realtek rtw89 family wireless driver (OOT)
  DEPENDS:=@PCI_SUPPORT +kmod-mac80211 \
	+rtl8851be-firmware +rtl8852ae-firmware +rtl8852be-firmware +rtl8852ce-firmware \
	+@DRIVER_11N_SUPPORT +@DRIVER_11AC_SUPPORT +@DRIVER_11AX_SUPPORT
  CONFLICTS:=kmod-rtw89
  FILES:= \
	$(PKG_BUILD_DIR)/rtw_8851b.ko \
	$(PKG_BUILD_DIR)/rtw_8851be.ko \
	$(PKG_BUILD_DIR)/rtw_8852a.ko \
	$(PKG_BUILD_DIR)/rtw_8852ae.ko \
	$(PKG_BUILD_DIR)/rtw_8852b.ko \
	$(PKG_BUILD_DIR)/rtw_8852be.ko \
	$(PKG_BUILD_DIR)/rtw_8852c.ko \
	$(PKG_BUILD_DIR)/rtw_8852ce.ko \
	$(PKG_BUILD_DIR)/rtw89core.ko \
	$(PKG_BUILD_DIR)/rtw89pci.ko
  AUTOLOAD:=$(call AutoProbe,rtw_8851be rtw_8852ae rtw_8852be rtw_8852ce)
endef

define KernelPackage/rtw89-oot/description
  This package contains a driver for Realtek RTL8851BE/RTL8852AE/RTL8852BE/RTL8852CE Family Controller.
endef

define KernelPackage/rtw89-oot/install
	$(INSTALL_DIR) $(1)/etc/uci-defaults
	$(INSTALL_DATA) ./files/kmods-unload.default $(1)/etc/uci-defaults/kmods-unload-rtw89
endef

NOSTDINC_FLAGS := \
	$(KERNEL_NOSTDINC_FLAGS) \
	-I$(PKG_BUILD_DIR) \
	-I$(STAGING_DIR)/usr/include/mac80211-backport/uapi \
	-I$(STAGING_DIR)/usr/include/mac80211-backport \
	-I$(STAGING_DIR)/usr/include/mac80211/uapi \
	-I$(STAGING_DIR)/usr/include/mac80211 \
	-include backport/autoconf.h \
	-include backport/backport.h

NOSTDINC_FLAGS+=-DBUILD_OPENWRT

define Build/Compile
	+$(MAKE) $(PKG_JOBS) -C "$(LINUX_DIR)" \
		$(KERNEL_MAKE_FLAGS) \
		M="$(PKG_BUILD_DIR)" \
		NOSTDINC_FLAGS="$(NOSTDINC_FLAGS)" \
		modules
endef

$(eval $(call KernelPackage,rtw89-oot))
