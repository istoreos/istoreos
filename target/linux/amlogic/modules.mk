define Package/brcmfmac-firmware-43455-sdio-phicomm-n1
  SECTION:=firmware
  CATEGORY:=Firmware
  TITLE:=Broadcom BCM43455 firmware for Phicomm N1
  VERSION:=1.0.0
  DEPENDS:=+brcmfmac-firmware-43455-sdio +brcmfmac-firmware-43455-sdio-rpi-4b
endef

define Package/brcmfmac-firmware-43455-sdio-phicomm-n1/install
	$(INSTALL_DIR) $(1)/lib/firmware/brcm
	$(LN) brcmfmac43455-sdio.raspberrypi,4-model-b.txt $(1)/lib/firmware/brcm/brcmfmac43455-sdio.phicomm,n1.txt
	$(LN) brcmfmac43455-sdio.bin $(1)/lib/firmware/brcm/brcmfmac43455-sdio.phicomm,n1.bin
	$(LN) brcmfmac43455-sdio.clm_blob $(1)/lib/firmware/brcm/brcmfmac43455-sdio.phicomm,n1.clm_blob
endef
$(eval $(call BuildPackage,brcmfmac-firmware-43455-sdio-phicomm-n1))

define KernelPackage/drm-amlogic-meson
  SUBMENU:=$(VIDEO_MENU)
  DEPENDS:=@TARGET_amlogic_meson +kmod-drm +kmod-drm-kms-helper +kmod-meson-canvas
  TITLE:=DRM for Amlogic meson
  KCONFIG:=\
	CONFIG_DRM_MESON \
	CONFIG_DRM_DW_HDMI \
	CONFIG_DRM_DW_HDMI_CEC
  FILES:=\
	$(LINUX_DIR)/drivers/gpu/drm/meson/meson-drm.ko \
	$(LINUX_DIR)/drivers/gpu/drm/bridge/synopsys/dw-hdmi.ko \
	$(LINUX_DIR)/drivers/gpu/drm/bridge/synopsys/dw-hdmi-cec.ko \
	$(LINUX_DIR)/drivers/media/cec/cec.ko@lt5.10 \
	$(LINUX_DIR)/drivers/media/cec/core/cec.ko@ge5.10
  AUTOLOAD:=$(call AutoLoad,80,dw-hdmi-cec meson-drm)
endef

define KernelPackage/drm-amlogic-meson/description
  DRM for Amlogic meson
endef

$(eval $(call KernelPackage,drm-amlogic-meson))


define KernelPackage/drm-amlogic-meson-hdmitx
  SUBMENU:=$(VIDEO_MENU)
  DEPENDS:=kmod-drm-amlogic-meson
  TITLE:=Meson HDMI TX
  KCONFIG:=\
	CONFIG_DRM_MESON_DW_HDMI
  FILES:=\
	$(LINUX_DIR)/drivers/gpu/drm/meson/meson_dw_hdmi.ko
  AUTOLOAD:=$(call AutoLoad,70,meson_dw_hdmi)
endef

define KernelPackage/drm-amlogic-meson-hdmitx/description
  Support HDMI TX on meson
endef

$(eval $(call KernelPackage,drm-amlogic-meson-hdmitx))

define KernelPackage/meson-canvas
  SUBMENU:=$(VIDEO_MENU)
  DEPENDS:=@TARGET_amlogic_meson
  TITLE:=Amlogic Meson Canvas driver
  HIDDEN:=1
  KCONFIG:=\
	CONFIG_MESON_CANVAS
  FILES:=\
	$(LINUX_DIR)/drivers/soc/amlogic/meson-canvas.ko
endef

$(eval $(call KernelPackage,meson-canvas))
