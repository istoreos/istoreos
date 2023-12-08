
include $(TOPDIR)/rules.mk

PKG_NAME:=mali-csf-firmware
PKG_VERSION:=g17p0-01eac0
PKG_RELEASE:=1

PKG_SOURCE_VERSION:=488f49467f5b4adb8ae944221698e9a4f9acb0ed
PKG_HASH:=c1f0896b9e2f0d4154406acd650f6c946fdd80cfc32381fb5072e9952933367a
PKG_SOURCE_URL_FILE:=mali_csffw.bin
PKG_SOURCE:=mali_csffw-$(PKG_VERSION).bin
PKG_SOURCE_URL:=https://raw.githubusercontent.com/JeffyCN/mirrors/$(PKG_SOURCE_VERSION)/firmware/g610/

PKG_MAINTAINER:=jjm2473 <jjm2473@gmail.com>

include $(INCLUDE_DIR)/package.mk

define Package/mali-csf-firmware
  SECTION:=firmware
  CATEGORY:=Firmware
  TITLE:=Mali CSF firmware
  DEPENDS:=@TARGET_rockchip_rk35xx
  HIDDEN:=1
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
endef

define Build/Compile

endef

define Package/mali-csf-firmware/install
	$(INSTALL_DIR) $(1)/lib/firmware
	$(INSTALL_DATA) $(DL_DIR)/$(PKG_SOURCE) $(1)/lib/firmware/$(PKG_SOURCE_URL_FILE)
endef

$(eval $(call BuildPackage,mali-csf-firmware))
