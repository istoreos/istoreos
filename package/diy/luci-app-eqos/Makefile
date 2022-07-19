#
# Copyright (C) 2006-2017 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=luci-app-eqos
PKG_RELEASE:=1
PKG_MAINTAINER:=Jianhui Zhao <jianhuizhao329@gmail.com> GaryPang <https://github.com/garypang13/luci-app-eqos>

LUCI_TITLE:=EQOS - LuCI interface
LUCI_DEPENDS:=+luci-base +tc +kmod-sched-core +kmod-ifb
LUCI_PKGARCH:=all

define Package/luci-app-eqos/conffiles
/etc/config/eqos
endef

include $(TOPDIR)/feeds/luci/luci.mk

# call BuildPackage - OpenWrt buildroot signature
