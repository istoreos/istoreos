# 
# Copyright (C) 2006-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=rtd129x_env
PKG_VERSION:=1.1
PKG_REVISION:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/${PKG_NAME}-$(PKG_VERSION)

PKG_FLAGS:=nonshared

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/rtd129x_env
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=RTD129x Factory tools
  URL:=
  DEPENDS:=@TARGET_realtek_rtd129x +busybox
endef

define Package/rtd129x_env/description
 RTD129x Factory tools
endef

define Package/rtd129x_env/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/rtd129x_env $(1)/usr/sbin/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/rtk_factory_sign $(1)/usr/sbin/
	$(INSTALL_BIN) ./files/factory $(1)/usr/sbin/
endef

$(eval $(call BuildPackage,rtd129x_env))
