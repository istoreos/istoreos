#
# Copyright (C) 2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_VERSION:=2015.07
PKG_RELEASE:=9

PKG_HASH:=0b48c9bd717f2c322ef791f8282e14c88be942dc7d1226df7e31a812a3af94d9

HOST_CFLAGS:= -O2
HOST_CPPFLAGS:=
HOST_LDFLAGS:=

include $(INCLUDE_DIR)/u-boot.mk
include $(INCLUDE_DIR)/package.mk

define U-Boot/Default
  BUILD_TARGET:=realtek
  HIDDEN:=y
endef

define U-Boot/rtd1296
  NAME:=RTD1296
  BUILD_SUBTARGET:=rtd129x
  DEFAULT:=y
  UBOOT_CONFIG:=rtd1296_qa_NAS
endef

UBOOT_TARGETS:=rtd1296

UBOOT_MAKE_FLAGS+= V=1

RTK_UBOOT_BIN:=rtk-uboot-binary_1.tar.gz
define Download/rtk-uboot-binary
  FILE:=$(RTK_UBOOT_BIN)
  URL:=https://github.com/jjm2473/rtd1296_prebuilt_target/releases/download/v1.0/
  HASH:=e7d15286dfaf1cde74b24ffc61194ea4955792f7afff3c8936f877e0c5c912b4
endef

define Build/Prepare
	# Download sources
	$(eval $(call Download,rtk-uboot-binary))

	$(call Build/Prepare/Default,)

	$(TAR) -C $(PKG_BUILD_DIR) -xzf $(DL_DIR)/$(RTK_UBOOT_BIN)
endef

define Build/InstallDev
	$(INSTALL_DIR) $(STAGING_DIR_IMAGE)
	$(CP) $(PKG_BUILD_DIR)/u-boot.bin $(STAGING_DIR_IMAGE)/u-boot.bin
endef

define Package/u-boot/install
endef

$(eval $(call BuildPackage/U-Boot))
