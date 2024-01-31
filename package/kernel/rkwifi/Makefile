
include $(TOPDIR)/rules.mk

PKG_NAME:=rkwifi
PKG_VERSION:=2023-12-06
PKG_RELEASE:=3

PKG_SOURCE_VERSION:=4af9d98084735bb1e221f037119fd6edf186caf7
PKG_HASH:=7c07b20f42f31d8f349d2235e6f899055d352dd55cf8f3feda019b2c97a5e836
PKG_SOURCE_URL_FILE:=$(PKG_SOURCE_VERSION).tar.gz
PKG_SOURCE:=rkwifi-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://github.com/jjm2473/rockchip_wlan/archive/

PKG_BUILD_PARALLEL:=1

PKG_MAINTAINER:=jjm2473 <jjm2473@gmail.com>

STAMP_CONFIGURED_DEPENDS := $(STAGING_DIR)/usr/include/mac80211-backport/backport/autoconf.h

include $(INCLUDE_DIR)/kernel.mk
include $(INCLUDE_DIR)/package.mk

TAR_OPTIONS+= --strip-components 1
TAR_CMD=$(HOST_TAR) -C $(1) $(TAR_OPTIONS)

define KernelPackage/rkwifi-bcmdhd
  SUBMENU:=Wireless Drivers
  TITLE:=RK Wifi AP6xxx wireless cards support (SDIO)
  DEPENDS:=@TARGET_rockchip +kmod-mmc +kmod-mac80211 \
	+@DRIVER_11N_SUPPORT +@DRIVER_11AC_SUPPORT
  KCONFIG:=\
	CONFIG_RFKILL_RK=y
  FILES:= \
	$(PKG_BUILD_DIR)/rkwifi/bcmdhd/dhdsdio.ko
  AUTOLOAD:=$(call AutoProbe,dhdsdio)
  VARIANT:=sdio
endef

define KernelPackage/rkwifi-bcmdhd/description
  Support for sdio wireless adapters based on Broadcom AP6xxx(bcmdhd) chipset on Rockchip platform.
endef

define KernelPackage/rkwifi-bcmdhd-pcie
  SUBMENU:=Wireless Drivers
  TITLE:=RK Wifi AP6xxx wireless cards support (PCIe)
  DEPENDS:=@TARGET_rockchip @PCI_SUPPORT +kmod-mac80211 \
	+@DRIVER_11N_SUPPORT +@DRIVER_11AC_SUPPORT
  KCONFIG:=\
	CONFIG_RFKILL_RK=y
  FILES:= \
	$(PKG_BUILD_DIR)/rkwifi/bcmdhd/dhdpcie.ko
  AUTOLOAD:=$(call AutoProbe,dhdpcie)
  VARIANT:=pcie
endef

define KernelPackage/rkwifi-bcmdhd-pcie/description
  Support for pcie wireless adapters based on Broadcom AP6xxx(bcmdhd) chipset on Rockchip platform.
endef

NOSTDINC_FLAGS := \
	$(KERNEL_NOSTDINC_FLAGS) \
	-I$(PKG_BUILD_DIR)/rkwifi/bcmdhd/include \
	-I$(PKG_BUILD_DIR)/rkwifi/bcmdhd \
	-I$(STAGING_DIR)/usr/include/mac80211-backport \
	-I$(STAGING_DIR)/usr/include/mac80211-backport/uapi \
	-I$(STAGING_DIR)/usr/include/mac80211 \
	-I$(STAGING_DIR)/usr/include/mac80211/uapi \
	-include backport/autoconf.h \
	-include backport/backport.h

NOSTDINC_FLAGS+=-DBUILD_OPENWRT

PKG_MAKE_FLAGS+= CONFIG_BCMDHD=m CONFIG_BCMDHD_MULTIPLE_DRIVER=y \
	CONFIG_CFG80211=y CONFIG_WIRELESS_EXT=

ifeq ($(BUILD_VARIANT),sdio)
  PKG_MAKE_FLAGS+= CONFIG_BCMDHD_SDIO=y
endif

ifeq ($(BUILD_VARIANT),pcie)
  PKG_MAKE_FLAGS+= CONFIG_BCMDHD_PCIE=y
endif

define Build/Compile
	+$(MAKE) $(PKG_JOBS) -C "$(LINUX_DIR)" \
		$(KERNEL_MAKE_FLAGS) \
		$(PKG_MAKE_FLAGS) \
		M="$(PKG_BUILD_DIR)/rkwifi/bcmdhd" \
		NOSTDINC_FLAGS="$(NOSTDINC_FLAGS)" \
		modules
endef

$(eval $(call KernelPackage,rkwifi-bcmdhd))
$(eval $(call KernelPackage,rkwifi-bcmdhd-pcie))
