include $(TOPDIR)/rules.mk

PKG_NAME:=rtl88x2bu
PKG_RELEASE=1

PKG_LICENSE:=GPL
PKG_LICENSE_FILES:=

PKG_SOURCE_URL:=https://github.com/morrownr/88x2bu.git
PKG_MIRROR_HASH:=d48b0bc0825f87463bf482d4f28ea023c66573a2bfadbc98820b239d8e9492ab
PKG_SOURCE_PROTO:=git
PKG_SOURCE_DATE:=2021-04-15
PKG_SOURCE_VERSION:=5b03f62143244fdf99530c6b783bb35625c5ec56

PKG_MAINTAINER:=morrownr <https://github.com/morrownr>
PKG_BUILD_PARALLEL:=1

STAMP_CONFIGURED_DEPENDS := $(STAGING_DIR)/usr/include/mac80211-backport/backport/autoconf.h

include $(INCLUDE_DIR)/kernel.mk
include $(INCLUDE_DIR)/package.mk

define KernelPackage/rtl88x2bu
  SUBMENU:=Wireless Drivers
  TITLE:=Driver for Realtek 8812BU/8822BU devices
  DEPENDS:=+kmod-cfg80211 +kmod-usb-core +@DRIVER_11N_SUPPORT +@DRIVER_11AC_SUPPORT
  FILES:=\
	$(PKG_BUILD_DIR)/88x2bu.ko
  AUTOLOAD:=$(call AutoProbe,88x2bu)
  PROVIDES:=kmod-rtl88x2bu
endef

NOSTDINC_FLAGS = \
	-I$(PKG_BUILD_DIR) \
	-I$(PKG_BUILD_DIR)/include \
	-I$(STAGING_DIR)/usr/include/mac80211-backport \
	-I$(STAGING_DIR)/usr/include/mac80211-backport/uapi \
	-I$(STAGING_DIR)/usr/include/mac80211 \
	-I$(STAGING_DIR)/usr/include/mac80211/uapi \
	-include backport/backport.h

NOSTDINC_FLAGS+=-DCONFIG_IOCTL_CFG80211 -DRTW_USE_CFG80211_STA_EVENT -DBUILD_OPENWRT

ifneq ($(CONFIG_TARGET_realtek_rtd129x),)
  NOSTDINC_FLAGS+= -DCONFIG_USE_USB_BUFFER_ALLOC_TX
endif

define Build/Compile
	+$(MAKE) $(PKG_JOBS) -C "$(LINUX_DIR)" \
		$(KERNEL_MAKE_FLAGS) \
		SUBDIRS="$(PKG_BUILD_DIR)" \
		NOSTDINC_FLAGS="$(NOSTDINC_FLAGS)" \
		modules
endef

$(eval $(call KernelPackage,rtl88x2bu))
