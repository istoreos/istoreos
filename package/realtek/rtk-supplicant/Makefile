
# Copyright (C) 2017 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=rtk-supplicant
ifeq ($(KERNEL_PATCHVER), 4.9)
PKG_VERSION:=1.3.1
else
PKG_VERSION:=1
endif
PKG_RELEASE:=2
PKG_FLAGS:=nonshared
PKG_BUILD_DEPENDS:=openmax

PKG_SOURCE_URL:=https://github.com/jjm2473/rtd1296_prebuilt_target/releases/download/v1.0

ifeq ($(CONFIG_LIBC_USE_GLIBC),y)
PKG_SOURCE:=$(PKG_NAME)_glibc_$(PKG_VERSION).tar.gz
PKG_HASH:=e2c1c0b5560bd35bb16f7c7e3e9fdfe5b9fae0d124f0831846eec56bb6eb92b4
else
PKG_SOURCE:=$(PKG_NAME)_$(PKG_VERSION).tar.gz
ifeq ($(KERNEL_PATCHVER), 4.9)
PKG_HASH:=d7b8f911b4e3e2bfd3d4317f6c0361b16ba2dfe11c378e8d41da97ba6d38dcee
else
PKG_HASH:=ef95bd998f68c3eeca850a4c2322a4908fd79fac56efcfc5fbb806155ff51cea
endif
endif

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)_$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/rtk-supplicant
  SECTION:=multimedia
  CATEGORY:=Multimedia
  SUBMENU:=Realtek
  TITLE:=Realtek bluecore Supplicant
  DEPENDS:=@TARGET_realtek_rtd129x +openmax
endef

define Package/rtk-supplicant/description
 This package activates Realtek bluecore Supplicant
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)/root
	tar -xzvf $(DL_DIR)/$(PKG_SOURCE) -C $(PKG_BUILD_DIR)/root
endef
define Build/Compile
endef

define Package/rtk-supplicant/install
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) ./files/rtk-supplicant.init $(1)/etc/init.d/rtk-supplicant
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/root/usr/bin/ALSADaemon $(1)/usr/bin/rtk-supplicant
endef

$(eval $(call BuildPackage,rtk-supplicant))
