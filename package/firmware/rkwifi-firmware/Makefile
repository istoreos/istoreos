
include $(TOPDIR)/rules.mk

PKG_NAME:=rkwifi-firmware
PKG_VERSION:=2024-01-31
PKG_RELEASE:=1

PKG_SOURCE_VERSION:=63b8e59803df22cac7125878f5d7a0ee12eb09a3
PKG_HASH:=20dc54a1c8f1a0283fce9dd89d0b7fdf396311065252ed40521fba9c9a5b1e71
PKG_SOURCE_URL_FILE:=$(PKG_SOURCE_VERSION).tar.gz
PKG_SOURCE:=rkwifi-firmware-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://github.com/jjm2473/rockchip_wlan/archive/

PKG_MAINTAINER:=jjm2473 <jjm2473@gmail.com>

include $(INCLUDE_DIR)/package.mk

TAR_OPTIONS+= --strip-components 1
TAR_CMD=$(HOST_TAR) -C $(1) $(TAR_OPTIONS)

define Package/rkwifi-firmware
  SECTION:=firmware
  CATEGORY:=Firmware
  TITLE:=Rockchip wifi firmware
  DEPENDS:=@TARGET_rockchip
  HIDDEN:=1
endef

define Package/rkwifi-firmware-default
  SECTION:=firmware
  CATEGORY:=Firmware
  TITLE:=Rockchip wifi firmware $(1)
  DEPENDS:=@TARGET_rockchip +rkwifi-firmware
endef

define Build/Compile

endef

Package/rkwifi-firmware-ap6255 = $(call Package/rkwifi-firmware-default,ap6255)
define Package/rkwifi-firmware-ap6255/install
	$(INSTALL_DIR) $(1)/lib/firmware/rkwifi
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/rkwifi/fw_bcm43455c0_ag.bin $(1)/lib/firmware/rkwifi/
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/rkwifi/nvram_ap6255.txt $(1)/lib/firmware/rkwifi/
endef
$(eval $(call BuildPackage,rkwifi-firmware-ap6255))

Package/rkwifi-firmware-ap6256 = $(call Package/rkwifi-firmware-default,ap6256)
define Package/rkwifi-firmware-ap6256/install
	$(INSTALL_DIR) $(1)/lib/firmware/rkwifi
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/rkwifi/fw_bcm43456c5_ag.bin $(1)/lib/firmware/rkwifi/
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/rkwifi/nvram_ap6256.txt $(1)/lib/firmware/rkwifi/
endef
$(eval $(call BuildPackage,rkwifi-firmware-ap6256))

Package/rkwifi-firmware-ap6275s = $(call Package/rkwifi-firmware-default,ap6275s)
define Package/rkwifi-firmware-ap6275s/install
	$(INSTALL_DIR) $(1)/lib/firmware/rkwifi
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/rkwifi/fw_bcm43752a2_ag.bin $(1)/lib/firmware/rkwifi/
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/rkwifi/nvram_ap6275s.txt $(1)/lib/firmware/rkwifi/
endef
$(eval $(call BuildPackage,rkwifi-firmware-ap6275s))

Package/rkwifi-firmware-ap6275p = $(call Package/rkwifi-firmware-default,ap6275p)
define Package/rkwifi-firmware-ap6275p/install
	$(INSTALL_DIR) $(1)/lib/firmware/rkwifi
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/rkwifi/fw_bcm43752a2_pcie_ag.bin $(1)/lib/firmware/rkwifi/
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/rkwifi/clm_bcm43752a2_pcie_ag.blob $(1)/lib/firmware/rkwifi/
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/rkwifi/nvram_AP6275P.txt $(1)/lib/firmware/rkwifi/
endef
$(eval $(call BuildPackage,rkwifi-firmware-ap6275p))

Package/rkwifi-firmware-ap6356 = $(call Package/rkwifi-firmware-default,ap6356)
define Package/rkwifi-firmware-ap6356/install
	$(INSTALL_DIR) $(1)/lib/firmware/rkwifi
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/rkwifi/fw_bcm4356a2_ag.bin $(1)/lib/firmware/rkwifi/
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/rkwifi/nvram_ap6356.txt $(1)/lib/firmware/rkwifi/
endef
$(eval $(call BuildPackage,rkwifi-firmware-ap6356))

Package/rkwifi-firmware-ap6398s = $(call Package/rkwifi-firmware-default,ap6398s)
define Package/rkwifi-firmware-ap6398s/install
	$(INSTALL_DIR) $(1)/lib/firmware/rkwifi
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/rkwifi/fw_bcm4359c0_ag.bin $(1)/lib/firmware/rkwifi/
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/rkwifi/nvram_ap6398s.txt $(1)/lib/firmware/rkwifi/
endef
$(eval $(call BuildPackage,rkwifi-firmware-ap6398s))

define Package/rkwifi-firmware/install
	$(INSTALL_DIR) $(1)/lib/firmware/rkwifi
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/rkwifi/config.txt $(1)/lib/firmware/rkwifi/
endef

$(eval $(call BuildPackage,rkwifi-firmware))

