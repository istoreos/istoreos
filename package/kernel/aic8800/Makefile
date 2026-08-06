# SPDX-License-Identifier: GPL-2.0+
#
# Copyright (c) 2023-2025 AnYun
#

include $(TOPDIR)/rules.mk

PKG_NAME:=aic8800
PKG_RELEASE:=1

PKG_SOURCE_DATE:=2026-03-10
PKG_SOURCE_VERSION:=89f865b80f5f2ba6c0711c560e1d0191e87a1bf0
PKG_HASH:=a1987f531b863f48167e2f7555584f1ef8fc3bc96fc685bb8ae2bc223c714011
PKG_SOURCE_URL_FILE:=$(PKG_SOURCE_VERSION).tar.gz
PKG_SOURCE:=aic8800-$(PKG_SOURCE_DATE).tar.gz
PKG_SOURCE_URL:=https://github.com/radxa-pkg/aic8800/archive/

ifeq ($(BUILD_VARIANT),sdio)
MAKE_PATH:=src/SDIO/driver_fw/driver/aic8800
FW_PATH="/lib/firmware/aic8800/sdio"
else
MAKE_PATH:=src/USB/driver_fw/drivers/aic8800
FW_PATH="/lib/firmware/aic8800/usb"
endif

PKG_EXTMOD_SUBDIRS:=$(MAKE_PATH)

include $(INCLUDE_DIR)/kernel.mk
include $(INCLUDE_DIR)/package.mk

TAR_OPTIONS+= --strip-components 1
TAR_CMD=$(HOST_TAR) -C $(1) $(TAR_OPTIONS)

define KernelPackage/aic8800s
  SUBMENU:=Wireless Drivers
  TITLE:=AIC8800 SDIO wireless support
  DEPENDS:=+kmod-mac80211 +kmod-mmc \
	+@DRIVER_11AC_SUPPORT +@DRIVER_11AX_SUPPORT
  FILES:= \
	$(PKG_BUILD_DIR)/$(MAKE_PATH)/aic8800_bsp/aic8800_bsp.ko \
	$(PKG_BUILD_DIR)/$(MAKE_PATH)/aic8800_fdrv/aic8800_fdrv.ko
  AUTOLOAD:=$(call AutoProbe,aic8800_bsp aic8800_fdrv)
  VARIANT:=sdio
endef

define KernelPackage/aic8800u
  SUBMENU:=Wireless Drivers
  TITLE:=AIC8800 USB wireless support
  DEPENDS:=+kmod-mac80211 +kmod-usb-core @USB_SUPPORT \
	+@DRIVER_11AC_SUPPORT +@DRIVER_11AX_SUPPORT
  FILES:= \
	$(PKG_BUILD_DIR)/$(MAKE_PATH)/aic_load_fw/aic_load_fw.ko \
	$(PKG_BUILD_DIR)/$(MAKE_PATH)/aic8800_fdrv/aic8800DC_fdrv.ko
  AUTOLOAD:=$(call AutoProbe,aic_load_fw aic8800DC_fdrv)
  VARIANT:=usb
endef

NOSTDINC_FLAGS := \
	$(KERNEL_NOSTDINC_FLAGS) \
	-Wno-error=missing-prototypes \
	-Wno-error=expansion-to-defined \
	-Wno-error=attribute-warning \
	-Wno-error=unused-function \
	-Wno-error=unused-variable \
	-Wno-error=unused-label \
	-I$(PKG_BUILD_DIR) \
	-I$(STAGING_DIR)/usr/include/mac80211-backport/uapi \
	-I$(STAGING_DIR)/usr/include/mac80211-backport \
	-I$(STAGING_DIR)/usr/include/mac80211/uapi \
	-I$(STAGING_DIR)/usr/include/mac80211 \
	-include backport/backport.h

EXTRA_CFLAGS:= -DBUILD_OPENWRT

define Build/Compile
	+$(MAKE) $(PKG_JOBS) -C "$(LINUX_DIR)" \
		NOSTDINC_FLAGS="$(NOSTDINC_FLAGS)" \
		EXTRA_CFLAGS="$(EXTRA_CFLAGS)" \
		$(KERNEL_MAKE_FLAGS) \
		M="$(PKG_BUILD_DIR)/$(MAKE_PATH)/" \
		CONFIG_AIC_FW_PATH="$(FW_PATH)" \
		modules
endef

define KernelPackage/aic8800s/install
	$(INSTALL_DIR) $(1)/lib/firmware/aic8800/sdio
	$(CP) $(PKG_BUILD_DIR)/src/SDIO/driver_fw/fw/aic8800D80/* $(1)/lib/firmware/aic8800/sdio
endef

define KernelPackage/aic8800u/install
	$(INSTALL_DIR) $(1)/lib/firmware/aic8800/usb
	$(CP) $(PKG_BUILD_DIR)/src/USB/driver_fw/fw/*/* $(1)/lib/firmware/aic8800/usb
endef

$(eval $(call KernelPackage,aic8800s))
$(eval $(call KernelPackage,aic8800u))
