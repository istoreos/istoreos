#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_VERSION:=2017.09.20241018
PKG_RELEASE:=$(AUTORELEASE)

PKG_SOURCE_PROTO:=default
PKG_SOURCE:=rkuboot-$(PKG_VERSION).tar.gz
PKG_SOURCE_VERSION:=2687dce2617032930f2c43fef349bdea694c6f68
PKG_SOURCE_URL_FILE:=$(PKG_SOURCE_VERSION).tar.gz
PKG_SOURCE_URL:=https://github.com/rockchip-linux/u-boot/archive/
PKG_HASH:=6c723ebd3f0732472e707ac3317847e038e606e7632d5a686f8278d333e5ef78

PKG_MAINTAINER:=jjm2473

include $(INCLUDE_DIR)/u-boot.mk
include $(INCLUDE_DIR)/package.mk

TAR_OPTIONS:=--strip-components 1 $(TAR_OPTIONS)
TAR_CMD=$(HOST_TAR) -C $(1) $(TAR_OPTIONS)

define U-Boot/Default
  BUILD_TARGET:=rockchip
  UENV:=default
  HIDDEN:=1
  BUILD_SUBTARGET:=armv8
  DEFAULT:=y
  PKG_BUILD_DEPENDS:=rkbin
endef

# RK3528 boards
define U-Boot/easepi-rk3528
  NAME:=RK3528 Generic
  DEPENDS:=+PACKAGE_u-boot-$(1):trusted-firmware-a-rk3528
  ATF:=rk3528_bl31_v1.17.elf
  TPL:=rk3528_ddr_1056MHz_v1.09.bin
  SOC:=rk3528
endef

# RK3576 boards
define U-Boot/easepi-rk3576
  NAME:=RK3576 Generic
  DEPENDS:=+PACKAGE_u-boot-$(1):trusted-firmware-a-rk3576
  ATF:=rk3576_bl31_v1.15.elf
  TPL:=rk3576_ddr_lp4_2112MHz_lp5_2736MHz_v1.09.bin
  SOC:=rk3576
  IDB:=$$(IDB_FILE)
endef


UBOOT_TARGETS := easepi-rk3528 easepi-rk3576

UBOOT_CONFIGURE_VARS += USE_PRIVATE_LIBGCC=yes

UBOOT_MAKE_FLAGS += \
  IDB_SOC=$(SOC) \
  TPL_BIN=$(STAGING_DIR_IMAGE)/$(TPL) \
  u-boot.itb $(if $(IDB),,idbloader.img)

ifeq ($(BUILD_VARIANT),easepi-rk3576)
# The idbloader.img built from uboot cannot boot from sd card, so use the pre-built one
  IDB_FILE:=easepi-rk3576-idbloader_v1.09.107.img
  define Download/rk3576-idbloader
    FILE:=$(IDB_FILE)
    URL:=https://github.com/jjm2473/uboot-nanopi/releases/download/rk3576-v1.0/
    HASH:=c55404e27f595942be438a52e1e6b58eb9c577b25615c7d9b68202d4af390971
  endef

  define Build/Prepare
	$(eval $(call Download,rk3576-idbloader))
	$(call Build/Prepare/Default)

  endef
endif

define Build/Configure
	$(call Build/Configure/U-Boot)

	$(SED) 's/CONFIG_TOOLS_LIBCRYPTO=y/# CONFIG_TOOLS_LIBCRYPTO is not set/' $(PKG_BUILD_DIR)/.config
	$(SED) 's#CONFIG_MKIMAGE_DTC_PATH=.*#CONFIG_MKIMAGE_DTC_PATH="$(PKG_BUILD_DIR)/scripts/dtc/dtc"#g' $(PKG_BUILD_DIR)/.config
	echo 'CONFIG_IDENT_STRING=" OpenWrt"' >> $(PKG_BUILD_DIR)/.config
	$(CP) $(STAGING_DIR_IMAGE)/$(ATF) $(PKG_BUILD_DIR)/bl31.elf
ifneq ($(IDB),)
	$(CP) $(DL_DIR)/$(IDB) $(PKG_BUILD_DIR)/idbloader.img
endif
endef

define Build/InstallDev
	$(INSTALL_DIR) $(STAGING_DIR_IMAGE)
	dd if=/dev/zero of=$(PKG_BUILD_DIR)/u-boot-rockchip.bin bs=512 count=16320
	dd if=$(PKG_BUILD_DIR)/idbloader.img of=$(PKG_BUILD_DIR)/u-boot-rockchip.bin conv=notrunc
	dd if=$(PKG_BUILD_DIR)/u-boot.itb of=$(PKG_BUILD_DIR)/u-boot-rockchip.bin seek=16320 conv=notrunc
	$(CP) $(PKG_BUILD_DIR)/u-boot-rockchip.bin $(STAGING_DIR_IMAGE)/$(BUILD_VARIANT)-u-boot-rockchip.bin
endef

define Package/u-boot/install/default
endef

$(eval $(call BuildPackage/U-Boot))
