#
# Copyright (C) 2020 jjm2473 <jjm2473@gmail.com>
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=rtk-rescue-firmware
PKG_VERSION:=2
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)_$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://github.com/jjm2473/rtd1296_prebuilt_target/releases/download/v1.0/
PKG_HASH:=3da5865a7d11679a65bee1948a6cf4d3adeb1ad5afcf7642501f6db0eb8848fd

PKG_LICENSE:=CC0-1.0
PKG_MAINTAINER:=jjm2473 <jjm2473@gmail.com>

PKG_TARGETS:=bin
PKG_FLAGS:=nonshared

include $(INCLUDE_DIR)/package.mk

define Package/rtk-rescue-firmware
  CATEGORY:=Boot Loaders
  SECTION:=boot
  TITLE:=realtek rescue system
  MAINTAINER:=jjm2473 <jjm2473@gmail.com>
  DEPENDS:=@TARGET_realtek
  DEFAULT:= y if TARGET_realtek_rtd129x
  HIDDEN:=y
endef

define Package/rtk-rescue-firmware/description
 This package contains realtek rescue system.
endef

define Build/Prepare
	$(TAR) -C $(PKG_BUILD_DIR) -xzf $(DL_DIR)/$(PKG_SOURCE)
endef

define Build/Configure
endef

define Build/Compile
endef

define Build/InstallDev
	$(INSTALL_DIR) $(STAGING_DIR_IMAGE)
	$(CP) $(PKG_BUILD_DIR)/rescue.* $(STAGING_DIR_IMAGE)/
endef

define Package/rtk-rescue-firmware/install
endef

$(eval $(call BuildPackage,rtk-rescue-firmware))
