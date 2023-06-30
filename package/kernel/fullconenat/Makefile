#
# Copyright (C) 2018 Chion Tang <tech@chionlab.moe>
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=fullconenat
PKG_VERSION:=2022-02-13
PKG_RELEASE:=6

PKG_SOURCE_VERSION:=108a36cbdca17e68c9e6e7fd5e26156a88f738e8
PKG_HASH:=529bad01c03fac7c1356f78222314278e5b5f16e5e40beaf738ad4372bb435c1
PKG_SOURCE_URL_FILE:=$(PKG_SOURCE_VERSION).tar.gz
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://github.com/llccd/netfilter-full-cone-nat/archive/

PKG_LICENSE:=GPL-2.0
PKG_LICENSE_FILES:=LICENSE

include $(INCLUDE_DIR)/package.mk

TAR_OPTIONS+= --strip-components 1
TAR_CMD=$(HOST_TAR) -C $(1) $(TAR_OPTIONS)

define Package/iptables-mod-fullconenat
  SUBMENU:=Firewall
  SECTION:=net
  CATEGORY:=Network
  TITLE:=FULLCONENAT iptables extension
  DEPENDS:=+iptables +kmod-ipt-fullconenat
  MAINTAINER:=Chion Tang <tech@chionlab.moe>
endef

define Package/iptables-mod-fullconenat/install
	$(INSTALL_DIR) $(1)/usr/lib/iptables
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/libipt_FULLCONENAT.so $(1)/usr/lib/iptables
endef

define KernelPackage/ipt-fullconenat
  SUBMENU:=Netfilter Extensions
  TITLE:=FULLCONENAT netfilter module
  DEPENDS:=+kmod-nf-ipt +kmod-nf-nat
  MAINTAINER:=Chion Tang <tech@chionlab.moe>
  KCONFIG:=  \
	CONFIG_NF_CONNTRACK_EVENTS=y \
	CONFIG_NF_CONNTRACK_CHAIN_EVENTS=y
  FILES:=$(PKG_BUILD_DIR)/xt_FULLCONENAT.ko
endef

include $(INCLUDE_DIR)/kernel-defaults.mk

define Build/Prepare
	$(call Build/Prepare/Default)
	$(CP) ./files/Makefile $(PKG_BUILD_DIR)/
endef

define Build/Compile
	+$(MAKE) $(PKG_JOBS) -C "$(LINUX_DIR)" \
        CROSS_COMPILE="$(TARGET_CROSS)" \
        ARCH="$(LINUX_KARCH)" \
        M="$(PKG_BUILD_DIR)" \
        EXTRA_CFLAGS="$(BUILDFLAGS)" \
        modules
	$(call Build/Compile/Default)
endef

$(eval $(call BuildPackage,iptables-mod-fullconenat))
$(eval $(call KernelPackage,ipt-fullconenat))
