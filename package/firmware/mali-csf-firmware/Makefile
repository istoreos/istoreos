
include $(TOPDIR)/rules.mk

PKG_NAME:=mali-csf-firmware
PKG_VERSION:=g25p0-00eac0
PKG_RELEASE:=1

PKG_SOURCE_VERSION:=d1b62d2e45b49ef7792d43a660d048d8618dee46
PKG_HASH:=befd23b9279b26010ebf35c835cc3aa7d0f50758930c7306ff4f5abbe5218624
PKG_SOURCE_URL_FILE:=mali_csffw.bin
PKG_SOURCE:=mali_csffw-$(PKG_VERSION).bin
PKG_SOURCE_URL:=https://raw.githubusercontent.com/rockchip-linux/kernel/$(PKG_SOURCE_VERSION)/drivers/gpu/arm/bifrost/

PKG_MAINTAINER:=jjm2473 <jjm2473@gmail.com>

include $(INCLUDE_DIR)/package.mk

define Package/mali-csf-firmware
  SECTION:=firmware
  CATEGORY:=Firmware
  TITLE:=Mali CSF firmware
  DEPENDS:=@TARGET_rockchip
  HIDDEN:=1
  VERSION:=$(subst -,~,$(subst p,.,$(subst g,,$(PKG_VERSION))))-r$(PKG_RELEASE)
  ABI_VERSION:=$(PKG_VERSION)
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
endef

define Build/Compile

endef

define Package/mali-csf-firmware/install
	$(INSTALL_DIR) $(1)/lib/firmware
	$(INSTALL_DATA) $(DL_DIR)/$(PKG_SOURCE) $(1)/lib/firmware/$(PKG_VERSION).$(PKG_SOURCE_URL_FILE)
endef

$(eval $(call BuildPackage,mali-csf-firmware))
