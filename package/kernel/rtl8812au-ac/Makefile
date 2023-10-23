include $(TOPDIR)/rules.mk

PKG_NAME:=rtl8812au-ac
PKG_VERSION:=2023-01-23
PKG_RELEASE:=2

PKG_SOURCE_VERSION:=e72dacdc4af7cf421484ce9567ef2cc995a16f3a
PKG_HASH:=a59d204f2fb56c2e230b1446eb8a71fe03035679f84c35afe260120be1e40aa9
PKG_SOURCE_URL_FILE:=$(PKG_SOURCE_VERSION).tar.gz
PKG_SOURCE:=rtl8812au-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://github.com/aircrack-ng/rtl8812au/archive/

PKG_LICENSE:=GPL-2.0-only
PKG_LICENSE_FILES:=LICENSE
# PKG_MAINTAINER:=

PKG_BUILD_PARALLEL:=1

STAMP_CONFIGURED_DEPENDS := $(STAGING_DIR)/usr/include/mac80211-backport/backport/autoconf.h

include $(INCLUDE_DIR)/kernel.mk
include $(INCLUDE_DIR)/package.mk

TAR_OPTIONS+= --strip-components 1
TAR_CMD=$(HOST_TAR) -C $(1) $(TAR_OPTIONS)

define KernelPackage/rtl8812au-ac
  SUBMENU:=Wireless Drivers
  TITLE:=Realtek RTL8812AU/21AU wireless drivers
  DEPENDS:=+kmod-cfg80211 +kmod-usb-core +@DRIVER_11AC_SUPPORT
  FILES:=$(PKG_BUILD_DIR)/rtl8812au.ko
  AUTOLOAD:=$(call AutoProbe,rtl8812au)
  CONFLICTS:=kmod-rtl8812au-ct
endef

NOSTDINC_FLAGS:= \
	$(KERNEL_NOSTDINC_FLAGS) \
	-I$(PKG_BUILD_DIR) \
	-I$(PKG_BUILD_DIR)/include \
	-I$(STAGING_DIR)/usr/include/mac80211-backport \
	-I$(STAGING_DIR)/usr/include/mac80211-backport/uapi \
	-I$(STAGING_DIR)/usr/include/mac80211 \
	-I$(STAGING_DIR)/usr/include/mac80211/uapi \
	-include backport/autoconf.h \
	-include backport/backport.h

NOSTDINC_FLAGS+= \
	-DRTW_SINGLE_WIPHY \
	-DRTW_USE_CFG80211_STA_EVENT \
	-DCONFIG_IOCTL_CFG80211 \
	-DBUILD_OPENWRT

ifeq ($(CONFIG_BIG_ENDIAN),y)
NOSTDINC_FLAGS+= -DCONFIG_BIG_ENDIAN
else
NOSTDINC_FLAGS+= -DCONFIG_LITTLE_ENDIAN
endif

define Build/Compile
	+$(KERNEL_MAKE) $(PKG_JOBS) \
		M="$(PKG_BUILD_DIR)" \
		NOSTDINC_FLAGS="$(NOSTDINC_FLAGS)" \
		CONFIG_88XXAU=m \
		USER_MODULE_NAME=rtl8812au \
		modules
endef

$(eval $(call KernelPackage,rtl8812au-ac))
