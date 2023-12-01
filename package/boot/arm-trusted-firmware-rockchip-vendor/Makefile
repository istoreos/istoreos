# SPDX-License-Identifier: GPL-2.0-only
#
# Copyright (C) 2021-2023 ImmortalWrt.org

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/trusted-firmware-a.mk

PKG_NAME:=rkbin
PKG_VERSION:=linux-5.10-gen-rkr4
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=https://gitlab.com/rk3588_linux/rk/rkbin/-/archive/$(PKG_VERSION)/
PKG_HASH:=06e17b198d8e77008dbe188ee9cc5ec4ca2b03a8a998c66677e0b23db0a7bed9

PKG_MAINTAINER:=Tianling Shen <cnsztl@immortalwrt.org>

include $(INCLUDE_DIR)/package.mk
include ./atf-version.mk

define Trusted-Firmware-A/Default
  NAME:=Rockchip $(1)
  BUILD_TARGET:=rockchip
endef

define Trusted-Firmware-A/rk3308
  BUILD_SUBTARGET:=armv8
  ATF:=rk33/$(RK3308_ATF)
  DDR:=rk33/$(RK3308_DDR)
  DDR1:=rk33/$(RK3308_DDR_UART2)
endef

define Trusted-Firmware-A/rk3528
  BUILD_SUBTARGET:=rk35xx
  ATF:=rk35/$(RK3528_ATF)
  DDR:=rk35/$(RK3528_DDR)
endef

define Trusted-Firmware-A/rk3568
  BUILD_SUBTARGET:=rk35xx
  ATF:=rk35/$(RK3568_ATF)
  DDR:=rk35/$(RK3568_DDR)
endef

define Trusted-Firmware-A/rk3588
  BUILD_SUBTARGET:=rk35xx
  ATF:=rk35/$(RK3588_ATF)
  DDR:=rk35/$(RK3588_DDR)
endef

TFA_TARGETS:= \
	rk3308 \
	rk3528 \
	rk3568 \
	rk3588

define Build/Compile
	# This comment is the workaround for "extraneous 'endif'" error
ifneq ($(LOADER),)
	( \
		pushd $(PKG_BUILD_DIR) ; \
		$(SED) 's,$$$$(PKG_BUILD_DIR),$(PKG_BUILD_DIR),g' trust.ini ; \
		$(SED) 's,$$$$(VARIANT),$(BUILD_VARIANT),g' trust.ini ; \
		./tools/mkimage -n $(BUILD_VARIANT) -T rksd -d bin/$(DDR) \
			$(BUILD_VARIANT)-idbloader.bin ; \
		cat bin/$(LOADER) >> $(BUILD_VARIANT)-idbloader.bin ; \
		./tools/trust_merger --replace bl31.elf bin/$(ATF) trust.ini ; \
		popd ; \
	)
endif
endef

define Package/trusted-firmware-a/install
	$(INSTALL_DIR) $(STAGING_DIR_IMAGE)

	$(CP) $(PKG_BUILD_DIR)/bin/$(ATF) $(STAGING_DIR_IMAGE)/
ifneq ($(LOADER),)
	$(CP) $(PKG_BUILD_DIR)/tools/loaderimage $(STAGING_DIR_IMAGE)/
	$(CP) $(PKG_BUILD_DIR)/$(BUILD_VARIANT)-idbloader.bin $(STAGING_DIR_IMAGE)/
	$(CP) $(PKG_BUILD_DIR)/$(BUILD_VARIANT)-trust.bin $(STAGING_DIR_IMAGE)/
else
	$(CP) $(PKG_BUILD_DIR)/bin/$(DDR) $(STAGING_DIR_IMAGE)/
ifneq ($(DDR1),)
	$(CP) $(PKG_BUILD_DIR)/bin/$(DDR1) $(STAGING_DIR_IMAGE)/
endif
endif
endef

$(eval $(call BuildPackage/Trusted-Firmware-A))