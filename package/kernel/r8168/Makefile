include $(TOPDIR)/rules.mk

PKG_NAME:=r8168
PKG_VERSION:=8.051.02
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://codeload.github.com/mtorromeo/r8168/tar.gz/$(PKG_VERSION)?
PKG_HASH:=76f1c6f0b273d6a31bdb3e98c39a54f50a65766b99d485f9b4ddeda30dcd11d8

include $(INCLUDE_DIR)/kernel.mk
include $(INCLUDE_DIR)/package.mk

define KernelPackage/$(PKG_NAME)
  TITLE:=Driver for Realtek r8168 chipsets
  SUBMENU:=Network Devices
  VERSION:=$(LINUX_VERSION)+$(PKG_VERSION)-$(PKG_RELEASE)
  FILES:=$(PKG_BUILD_DIR)/src/r8168.ko
  AUTOLOAD:=$(call AutoProbe,r8168)
endef

define KernelPackage/$(PKG_NAME)/description
  This package contains a driver for Realtek RTL8168/RTL8111/RTL8411 PCIe GBE Family Controller.
endef

define Build/Compile
	+$(KERNEL_MAKE) M=$(PKG_BUILD_DIR)/src modules
endef

$(eval $(call KernelPackage,r8168))
