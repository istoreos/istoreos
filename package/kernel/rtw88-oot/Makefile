#
# Copyright (C) 2017 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=rtw88-oot
PKG_VERSION:=2023-06-28
PKG_RELEASE:=1

PKG_SOURCE_VERSION:=7ca1ec0e768f083e4a2116d6978021814b83bb74
PKG_HASH:=bf0315c4e76ec70ef31f986554b8b4f255758e91a06f63e507b5918ff12f1a0f
PKG_SOURCE_URL_FILE:=$(PKG_SOURCE_VERSION).tar.gz
PKG_SOURCE:=rtw88-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://github.com/lwfinger/rtw88/archive/

PKG_BUILD_PARALLEL:=1

STAMP_CONFIGURED_DEPENDS := $(STAGING_DIR)/usr/include/mac80211-backport/backport/autoconf.h

include $(INCLUDE_DIR)/kernel.mk
include $(INCLUDE_DIR)/package.mk

TAR_OPTIONS+= --strip-components 1
TAR_CMD=$(HOST_TAR) -C $(1) $(TAR_OPTIONS)

define KernelPackage/rtw88-oot
  SUBMENU:=Wireless Drivers
  TITLE:=Realtek rtw88 family wireless driver (OOT)
  DEPENDS:=@PCI_SUPPORT +kmod-mac80211 +kmod-usb-core \
	+rtl8723du-firmware +rtl8821ce-firmware \
	+rtl8822be-firmware +rtl8822ce-firmware \
	+@DRIVER_11N_SUPPORT +@DRIVER_11AC_SUPPORT
  CONFLICTS:=kmod-rtw88
  FILES:= \
	$(PKG_BUILD_DIR)/rtw_8723d.ko \
	$(PKG_BUILD_DIR)/rtw_8723du.ko \
	$(PKG_BUILD_DIR)/rtw_8723de.ko \
	$(PKG_BUILD_DIR)/rtw_8821c.ko \
	$(PKG_BUILD_DIR)/rtw_8821cu.ko \
	$(PKG_BUILD_DIR)/rtw_8821ce.ko \
	$(PKG_BUILD_DIR)/rtw_8822b.ko \
	$(PKG_BUILD_DIR)/rtw_8822bu.ko \
	$(PKG_BUILD_DIR)/rtw_8822be.ko \
	$(PKG_BUILD_DIR)/rtw_8822c.ko \
	$(PKG_BUILD_DIR)/rtw_8822cu.ko \
	$(PKG_BUILD_DIR)/rtw_8822ce.ko \
	$(PKG_BUILD_DIR)/rtw_core.ko \
	$(PKG_BUILD_DIR)/rtw_usb.ko \
	$(PKG_BUILD_DIR)/rtw_pci.ko
  AUTOLOAD:=$(call AutoProbe,rtw_8822ce rtw_8822cu rtw_8822be rtw_8822bu rtw_8821ce rtw_8821cu rtw_8723de rtw_8723du)
endef

define KernelPackage/rtw88-oot/description
  This package contains a driver for Realtek RTL8822B[EU]/RTL8822C[EU]/RTL8821C[EU]/RTL8723D[EU] Family Controller.
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

$(eval $(call KernelPackage,rtw88-oot))
