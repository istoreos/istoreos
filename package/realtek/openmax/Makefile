#
# Copyright (C) 2016 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=openmax
ifeq ($(KERNEL_PATCHVER), 4.9)
PKG_VERSION:=1.3.1
else
PKG_VERSION:=2016
endif
PKG_RELEASE:=1

PKG_FLAGS:=nonshared

PKG_SOURCE_URL:=https://github.com/jjm2473/rtd1296_prebuilt_target/releases/download/v1.0

ifeq ($(CONFIG_LIBC_USE_GLIBC),y)
PKG_SOURCE:=$(PKG_NAME)_glibc_$(PKG_VERSION)-$(PKG_RELEASE).tar.gz
PKG_HASH:=dfbdba4756a3ad72c710205136ea3033e2061ef7ac8705a5c378975acde725c8
else
PKG_SOURCE:=$(PKG_NAME)_$(PKG_VERSION)-$(PKG_RELEASE).tar.gz
ifeq ($(KERNEL_PATCHVER), 4.9)
PKG_HASH:=a809663f57fb04ec91e6af7ee0fee7171c0c67a0a30e6695d98b3c63a74abbd2
else
PKG_HASH:=bcccbf7d2cfff4cf5151e489db0312bc4f68d59c852ea7dc9da6ae133308c85e
endif
endif

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)_$(PKG_VERSION)-$(PKG_RELEASE)

include $(INCLUDE_DIR)/package.mk

define Package/openmax
  SECTION:=multimedia
  CATEGORY:=Multimedia
  SUBMENU:=Realtek
  TITLE:=Realtek OpenMAX libraries
  DEPENDS:=@TARGET_realtek_rtd129x +libstdcpp +libpthread
  DEPENDS+= +kmod-openmax
endef
define Package/openmax/description
 Realtek OpenMAX libraries and various daemons
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)/root
	tar -xzvf $(DL_DIR)/$(PKG_SOURCE) -C $(PKG_BUILD_DIR)/root
endef
define Build/Compile
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/lib
	$(CP) $(PKG_BUILD_DIR)/root/usr/lib $(1)/usr/
endef

define Package/openmax/install
	$(CP) $(PKG_BUILD_DIR)/root/* $(1)/
endef

$(eval $(call BuildPackage,openmax))

