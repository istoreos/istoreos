#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_VERSION:=2017.09-20230725
PKG_RELEASE:=$(AUTORELEASE)

PKG_SOURCE_PROTO:=default
PKG_SOURCE:=rkuboot-$(PKG_VERSION).tar.gz
PKG_SOURCE_VERSION:=32640b0ada9344f91e7a407576568782907161cd
PKG_SOURCE_URL_FILE:=$(PKG_SOURCE_VERSION).tar.gz
PKG_SOURCE_URL:=https://github.com/rockchip-linux/u-boot/archive/
PKG_HASH:=c69a0d6acf20c06ada15e1a82666297ddb3dda208fedbc52d3d1385fc93218fb

PKG_MAINTAINER:=jjm2473

include $(INCLUDE_DIR)/u-boot.mk
include $(INCLUDE_DIR)/package.mk
include ../arm-trusted-firmware-rockchip-vendor/atf-version.mk

TAR_OPTIONS:=--strip-components 1 $(TAR_OPTIONS)
TAR_CMD=$(HOST_TAR) -C $(1) $(TAR_OPTIONS)

define U-Boot/Default
  BUILD_TARGET:=rockchip
  UENV:=default
  HIDDEN:=1
  BUILD_SUBTARGET:=rk35xx
  DEFAULT:=y
  PKG_BUILD_DEPENDS:=arm-trusted-firmware-rockchip-vendor
endef

# RK3308 boards
define U-Boot/easepi-rk3308
  NAME:=RK3308 Generic
  DEPENDS:=+PACKAGE_u-boot-$(1):trusted-firmware-a-rk3308
  ATF:=$(RK3308_ATF)
  DDR:=$(RK3308_DDR_UART2)
  SOC:=rk3308
  BUILD_SUBTARGET:=
endef

# RK3528 boards
define U-Boot/easepi-rk3528
  NAME:=RK3528 Generic
  DEPENDS:=+PACKAGE_u-boot-$(1):trusted-firmware-a-rk3528
  ATF:=$(RK3528_ATF)
  DDR:=$(RK3528_DDR)
  SOC:=rk3528
endef

# RK3568 boards
define U-Boot/easepi-rk3568
  NAME:=RK3568 Generic
  DEPENDS:=+PACKAGE_u-boot-$(1):trusted-firmware-a-rk3568
  ATF:=$(RK3568_ATF)
  DDR:=$(RK3568_DDR)
  SOC:=rk3568
endef

define U-Boot/xgp-rk3568
  NAME:=RK3568 xgp board
  DEPENDS:=+PACKAGE_u-boot-$(1):trusted-firmware-a-rk3568
  ATF:=$(RK3568_ATF)
  DDR:=$(RK3568_DDR)
  SOC:=rk3568
endef

# RK3588 boards
define U-Boot/easepi-rk3588
  NAME:=RK3588 Generic
  DEPENDS:=+PACKAGE_u-boot-$(1):trusted-firmware-a-rk3588
  ATF:=$(RK3588_ATF)
  DDR:=$(RK3588_DDR)
  SOC:=rk3588
endef

UBOOT_TARGETS := easepi-rk3568 easepi-rk3588 easepi-rk3528 xgp-rk3568 \
	easepi-rk3308

UBOOT_CONFIGURE_VARS += USE_PRIVATE_LIBGCC=yes

UBOOT_MAKE_FLAGS += \
  IDB_SOC=$(SOC) \
  TPL_BIN=$(STAGING_DIR_IMAGE)/$(DDR) \
  u-boot.itb idbloader.img

define Build/Configure
	$(call Build/Configure/U-Boot)

	$(SED) 's/CONFIG_TOOLS_LIBCRYPTO=y/# CONFIG_TOOLS_LIBCRYPTO is not set/' $(PKG_BUILD_DIR)/.config
	$(SED) 's#CONFIG_MKIMAGE_DTC_PATH=.*#CONFIG_MKIMAGE_DTC_PATH="$(PKG_BUILD_DIR)/scripts/dtc/dtc"#g' $(PKG_BUILD_DIR)/.config
	echo 'CONFIG_IDENT_STRING=" OpenWrt"' >> $(PKG_BUILD_DIR)/.config
	$(CP) $(STAGING_DIR_IMAGE)/$(ATF) $(PKG_BUILD_DIR)/bl31.elf
endef

define Build/InstallDev
	$(INSTALL_DIR) $(STAGING_DIR_IMAGE)
	$(CP) $(PKG_BUILD_DIR)/idbloader.img $(STAGING_DIR_IMAGE)/$(BUILD_VARIANT)-idbloader.img
	$(CP) $(PKG_BUILD_DIR)/u-boot.itb $(STAGING_DIR_IMAGE)/$(BUILD_VARIANT)-u-boot.itb
endef

define Package/u-boot/install/default
endef

$(eval $(call BuildPackage/U-Boot))
