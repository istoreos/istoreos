
define KernelPackage/iio-rockchip-saradc
  TITLE:= Rockchip SARADC driver
  DEPENDS:=@TARGET_rockchip
  KCONFIG:=CONFIG_ROCKCHIP_SARADC
  FILES:=$(LINUX_DIR)/drivers/iio/adc/rockchip_saradc.ko
  AUTOLOAD:=$(call AutoProbe,rockchip_saradc)
  $(call AddDepends/iio,+kmod-industrialio-triggered-buffer)
endef
define KernelPackage/iio-rockchip-saradc/description
 Driver for the Rockchip SARADC.
endef

$(eval $(call KernelPackage,iio-rockchip-saradc))


define KernelPackage/drm-rockchip
  SUBMENU:=$(VIDEO_MENU)
  TITLE:=Rockchip DRM support
  DEPENDS:=@TARGET_rockchip +kmod-backlight +kmod-drm-display-helper \
	+kmod-drm-dma-helper
  KCONFIG:= \
	CONFIG_DRM_ROCKCHIP \
	CONFIG_DRM_LOAD_EDID_FIRMWARE=y \
	CONFIG_DRM_FBDEV_EMULATION=y \
	CONFIG_DRM_FBDEV_OVERALLOC=100 \
	CONFIG_DRM_BRIDGE=y \
	CONFIG_DRM_DISPLAY_CONNECTOR \
	CONFIG_HDMI=y \
	CONFIG_DRM_DW_HDMI \
	CONFIG_DRM_DW_HDMI_CEC \
	CONFIG_DRM_DW_HDMI_GP_AUDIO=n \
	CONFIG_ROCKCHIP_ANALOGIX_DP=n \
	CONFIG_ROCKCHIP_CDN_DP=n \
	CONFIG_ROCKCHIP_DW_HDMI=y \
	CONFIG_ROCKCHIP_DW_MIPI_DSI=n \
	CONFIG_ROCKCHIP_INNO_HDMI=n \
	CONFIG_ROCKCHIP_LVDS=n \
	CONFIG_ROCKCHIP_RGB=n \
	CONFIG_ROCKCHIP_RK3066_HDMI=n \
	CONFIG_ROCKCHIP_VOP=n \
	CONFIG_ROCKCHIP_VOP2=y \
	CONFIG_DRM_PANEL=y \
	CONFIG_DRM_PANEL_BRIDGE=y
  FILES:= \
	$(LINUX_DIR)/drivers/gpu/drm/bridge/synopsys/dw-hdmi.ko \
	$(LINUX_DIR)/drivers/gpu/drm/bridge/synopsys/dw-hdmi-cec.ko \
	$(LINUX_DIR)/drivers/gpu/drm/bridge/display-connector.ko \
	$(LINUX_DIR)/drivers/gpu/drm/rockchip/rockchipdrm.ko \
	$(LINUX_DIR)/drivers/media/cec/core/cec.ko
  AUTOLOAD:=$(call AutoLoad,80,dw-hdmi-cec rockchipdrm display-connector)
endef

define KernelPackage/drm-rockchip/description
  Direct Rendering Manager (DRM) support for Rockchip
endef

$(eval $(call KernelPackage,drm-rockchip))
