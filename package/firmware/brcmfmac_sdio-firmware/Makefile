
include $(TOPDIR)/rules.mk

PKG_NAME:=brcmfmac_sdio-firmware
PKG_VERSION:=2025.12.11
PKG_RELEASE:=1

PKG_SOURCE_VERSION:=5091684cb177ccc5098b24e1bc9a8912d77994fb
PKG_HASH:=b78c3071350c470a9fd83c44453e58bd64fb1871d6e6645a1e7bfa876549042c
PKG_SOURCE_URL_FILE:=$(PKG_SOURCE_VERSION).tar.gz
PKG_SOURCE:=brcmfmac_sdio-firmware-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://github.com/LibreELEC/brcmfmac_sdio-firmware/archive/

PKG_MAINTAINER:=jjm2473 <jjm2473@gmail.com>

include $(INCLUDE_DIR)/package.mk

TAR_OPTIONS+= --strip-components 1
TAR_CMD=$(HOST_TAR) -C $(1) $(TAR_OPTIONS)

define Package/brcmfmac_sdio-firmware/default
  SECTION:=firmware
  CATEGORY:=Firmware
  URL:=https://github.com/LibreELEC/brcmfmac_sdio-firmware/
endef

define Package/brcmfmac-firmware-43455-sdio
  $(Package/brcmfmac_sdio-firmware/default)
  TITLE:=Broadcom BCM43455 SDIO firmware
endef

define Package/brcmfmac-nvram-43455-sdio-generic
  $(Package/brcmfmac_sdio-firmware/default)
  TITLE:=Broadcom BCM43455 SDIO NVRAM (Generic)
endef

define Build/Compile

endef

define Package/brcmfmac-firmware-43455-sdio/install
	$(INSTALL_DIR) $(1)/lib/firmware/brcm
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/brcmfmac43455-sdio.bin $(1)/lib/firmware/brcm/
endef

define Package/brcmfmac-nvram-43455-sdio-generic/install
	$(INSTALL_DIR) $(1)/lib/firmware/brcm
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/brcmfmac43455-sdio.txt $(1)/lib/firmware/brcm/
endef

$(eval $(call BuildPackage,brcmfmac-firmware-43455-sdio))
$(eval $(call BuildPackage,brcmfmac-nvram-43455-sdio-generic))
