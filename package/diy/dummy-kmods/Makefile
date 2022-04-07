#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=dummy-kmods
PKG_RELEASE:=1

PKG_MAINTAINER:=

include $(INCLUDE_DIR)/package.mk

define KernelPackage/inet-diag
  SECTION:=kernel
  CATEGORY:=Kernel modules
  SUBMENU:=Network Support
  TITLE:=Dummy inet-diag modules
  DEPENDS:=+kmod-netlink-diag
endef

define KernelPackage/inet-diag/description
  Dummy inet-diag modules
endef

define Build/Compile
endef

$(eval $(call KernelPackage,inet-diag))
