#
# Copyright (C) 2017 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=rtw88-usb
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

define KernelPackage/rtw88-default
  SUBMENU:=Wireless Drivers
  TITLE:=Realtek rtw88 family usb driver
  DEPENDS:=+kmod-mac80211 +kmod-usb-core \
	+@DRIVER_11N_SUPPORT +@DRIVER_11AC_SUPPORT
endef

define KernelPackage/rtw88-usb
  $(KernelPackage/rtw88-default)
  HIDDEN:=1
  FILES:= \
	$(PKG_BUILD_DIR)/rtw_core.ko \
	$(PKG_BUILD_DIR)/rtw_usb.ko
endef

define KernelPackage/rtl8723du
  $(KernelPackage/rtw88-default)
  TITLE:=Realtek RTL8723DU support
  DEPENDS+=+kmod-rtw88-usb +rtl8723du-firmware
  FILES:= \
	$(PKG_BUILD_DIR)/rtw_8723d.ko \
	$(PKG_BUILD_DIR)/rtw_8723du.ko
  AUTOLOAD:=$(call AutoProbe,rtw_8723du)
endef

define KernelPackage/rtl8821cu
  $(KernelPackage/rtw88-default)
  TITLE:=Realtek RTL8821CU support
  DEPENDS+=+kmod-rtw88-usb +rtl8821ce-firmware
  FILES:= \
	$(PKG_BUILD_DIR)/rtw_8821c.ko \
	$(PKG_BUILD_DIR)/rtw_8821cu.ko
  AUTOLOAD:=$(call AutoProbe,rtw_8821cu)
endef

define KernelPackage/rtl8822bu
  $(KernelPackage/rtw88-default)
  TITLE:=Realtek RTL8822BU support
  DEPENDS+=+kmod-rtw88-usb +rtl8822be-firmware
  FILES:= \
	$(PKG_BUILD_DIR)/rtw_8822b.ko \
	$(PKG_BUILD_DIR)/rtw_8822bu.ko
  AUTOLOAD:=$(call AutoProbe,rtw_8822bu)
endef

define KernelPackage/rtl8822cu
  $(KernelPackage/rtw88-default)
  TITLE:=Realtek RTL8822CU support
  DEPENDS+=+kmod-rtw88-usb +rtl8822ce-firmware
  FILES:= \
	$(PKG_BUILD_DIR)/rtw_8822c.ko \
	$(PKG_BUILD_DIR)/rtw_8822cu.ko
  AUTOLOAD:=$(call AutoProbe,rtw_8822cu)
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

$(eval $(call KernelPackage,rtw88-usb))
$(eval $(call KernelPackage,rtl8723du))
$(eval $(call KernelPackage,rtl8821cu))
$(eval $(call KernelPackage,rtl8822bu))
$(eval $(call KernelPackage,rtl8822cu))
