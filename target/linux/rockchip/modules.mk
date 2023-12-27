
define KernelPackage/drm-rockchip-rk35xx
  SUBMENU:=$(VIDEO_MENU)
  DEPENDS:=@TARGET_rockchip_rk35xx +kmod-drm +kmod-drm-kms-helper
  TITLE:=DRM for rockchip RK35xx
  KCONFIG:=\
	CONFIG_DRM_ROCKCHIP \
	CONFIG_DRM_DW_HDMI \
	CONFIG_DRM_DW_HDMI_CEC \
	CONFIG_DRM_FBDEV_EMULATION=y \
	CONFIG_DRM_FBDEV_OVERALLOC=100 \
	CONFIG_DRM_ROCKCHIP_VVOP=y \
	CONFIG_ROCKCHIP_VOP2=y
  FILES:=\
	$(LINUX_DIR)/drivers/gpu/drm/rockchip/rockchipdrm.ko \
	$(LINUX_DIR)/drivers/gpu/drm/bridge/synopsys/dw-hdmi.ko \
	$(LINUX_DIR)/drivers/gpu/drm/bridge/synopsys/dw-hdmi-hdcp.ko \
	$(LINUX_DIR)/drivers/gpu/drm/bridge/synopsys/dw-hdmi-qp.ko \
	$(LINUX_DIR)/drivers/gpu/drm/bridge/synopsys/dw-hdmi-cec.ko \
	$(LINUX_DIR)/drivers/gpu/drm/bridge/synopsys/dw-hdmi-qp-cec.ko \
	$(LINUX_DIR)/drivers/media/cec/cec.ko@lt5.10 \
	$(LINUX_DIR)/drivers/media/cec/core/cec.ko@ge5.10
  AUTOLOAD:=$(call AutoLoad,80,dw-hdmi-cec dw-hdmi-hdcp dw-hdmi-qp-cec rockchipdrm)
endef

define KernelPackage/drm-rockchip-rk35xx/description
  DRM for rockchip RK35xx
endef

$(eval $(call KernelPackage,drm-rockchip-rk35xx))

define KernelPackage/drm-rockchip-rk35xx-hdmitx
  SUBMENU:=$(VIDEO_MENU)
  DEPENDS:=kmod-drm-rockchip-rk35xx
  TITLE:=RK35xx HDMI TX
  KCONFIG:=\
	CONFIG_PHY_ROCKCHIP_SAMSUNG_HDPTX_HDMI \
	CONFIG_ROCKCHIP_DW_HDCP2 \
	CONFIG_ROCKCHIP_DW_HDMI=y
  FILES:=\
	$(LINUX_DIR)/drivers/phy/rockchip/phy-rockchip-samsung-hdptx-hdmi.ko \
	$(LINUX_DIR)/drivers/gpu/drm/rockchip/dw_hdcp2.ko
  AUTOLOAD:=$(call AutoLoad,70,dw_hdcp2 phy-rockchip-samsung-hdptx-hdmi)
endef

define KernelPackage/drm-rockchip-rk35xx-hdmitx/description
  Support HDMI TX on RK35xx
endef

$(eval $(call KernelPackage,drm-rockchip-rk35xx-hdmitx))

define KernelPackage/drm-rockchip-rk35xx-hdmi-audio
  SUBMENU:=$(VIDEO_MENU)
  DEPENDS:=kmod-drm-rockchip-rk35xx +kmod-sound-soc-rockchip
  TITLE:=RK35xx HDMI Audio
  KCONFIG:=\
	CONFIG_DRM_DW_HDMI_I2S_AUDIO \
	CONFIG_SND_SOC_ROCKCHIP_HDMI \
	CONFIG_SND_SOC_HDMI_CODEC=y
  FILES:=\
	$(LINUX_DIR)/drivers/gpu/drm/bridge/synopsys/dw-hdmi-i2s-audio.ko \
	$(LINUX_DIR)/drivers/gpu/drm/bridge/synopsys/dw-hdmi-qp-i2s-audio.ko \
	$(LINUX_DIR)/sound/soc/rockchip/snd-soc-rockchip-hdmi.ko
  AUTOLOAD:=$(call AutoLoad,81,snd-soc-rockchip-hdmi dw-hdmi-i2s-audio dw-hdmi-qp-i2s-audio)
endef

define KernelPackage/drm-rockchip-rk35xx-hdmi-audio/description
  Support HDMI Audio on RK35xx
endef

$(eval $(call KernelPackage,drm-rockchip-rk35xx-hdmi-audio))

define KernelPackage/drm-rockchip-rk35xx-vvop
  SUBMENU:=$(VIDEO_MENU)
  DEPENDS:=@TARGET_rockchip_rk35xx +kmod-drm @!PACKAGE_kmod-drm-rockchip-rk35xx
  TITLE:=Rockchip virtual VOP drm driver
  KCONFIG:=\
	CONFIG_DRM_ROCKCHIP \
	CONFIG_DRM_ROCKCHIP_VVOP=y
  FILES:=$(LINUX_DIR)/drivers/gpu/drm/rockchip/rockchipdrm.ko
  AUTOLOAD:=$(call AutoLoad,80,rockchipdrm)
endef

define KernelPackage/drm-rockchip-rk35xx-vvop/description
  If you want use some module of rockchip drm, but
  don't need a real vop driver(et: you just want rockchip drm
  gem driver to allocate memory).
endef

$(eval $(call KernelPackage,drm-rockchip-rk35xx-vvop))


define KernelPackage/rknpu
  SUBMENU:=$(OTHER_MENU)
  DEPENDS:=@TARGET_rockchip_rk35xx +kmod-drm
  TITLE:=Rockchip RKNPU driver
  KCONFIG:=\
	CONFIG_ROCKCHIP_RKNPU \
	CONFIG_ROCKCHIP_RKNPU_DEBUG_FS=y \
	CONFIG_ROCKCHIP_RKNPU_DRM_GEM=y \
	CONFIG_ROCKCHIP_RKNPU_FENCE=y
  FILES:=$(LINUX_DIR)/drivers/rknpu/rknpu.ko
  AUTOLOAD:=$(call AutoLoad,90,rknpu)
endef

define KernelPackage/rknpu/description
  Support Rockchip RKNPU
endef

$(eval $(call KernelPackage,rknpu))

define KernelPackage/rkgpu-bifrost
  SUBMENU:=$(OTHER_MENU)
  DEPENDS:=@TARGET_rockchip_rk35xx +kmod-dma-buf
  TITLE:=Rockchip GPU Mali bifrost driver
  KCONFIG:=\
	CONFIG_MALI_BIFROST
  FILES:=$(LINUX_DIR)/drivers/gpu/arm/bifrost/bifrost_kbase.ko
  AUTOLOAD:=$(call AutoLoad,85,bifrost_kbase)
endef

define KernelPackage/rkgpu-bifrost/description
  Support Rockchip GPU Mali bifrost (RK356x, etc.)
endef

$(eval $(call KernelPackage,rkgpu-bifrost))

define KernelPackage/rkgpu-mali400
  SUBMENU:=$(OTHER_MENU)
  DEPENDS:=@TARGET_rockchip_rk35xx +kmod-dma-buf
  TITLE:=Rockchip GPU Mali 400 driver
  KCONFIG:=\
	CONFIG_MALI400
  FILES:=$(LINUX_DIR)/drivers/gpu/arm/mali400/mali/mali.ko
  AUTOLOAD:=$(call AutoLoad,85,mali)
endef

define KernelPackage/rkgpu-mali400/description
  Support Rockchip GPU Mali 400 (450/470) (RK3528, etc.)
endef

$(eval $(call KernelPackage,rkgpu-mali400))

define KernelPackage/sound-soc-rockchip
  SUBMENU:=$(SOUND_MENU)
  DEPENDS:=@TARGET_rockchip +kmod-sound-soc-core +kmod-iio-core
  TITLE:=Rockchip SoC Audio
  KCONFIG:=\
	CONFIG_SND_SOC_ROCKCHIP_I2S_TDM \
	CONFIG_SND_SOC_ROCKCHIP_MULTICODECS \
	CONFIG_SND_SOC_ROCKCHIP=y
  FILES:=\
	$(LINUX_DIR)/sound/soc/rockchip/snd-soc-rockchip-i2s-tdm.ko \
	$(LINUX_DIR)/sound/soc/rockchip/snd-soc-rockchip-multicodecs.ko
  AUTOLOAD:=$(call AutoLoad,80,snd-soc-rockchip-i2s-tdm snd-soc-rockchip-multicodecs)
endef

define KernelPackage/sound-soc-rockchip/description
  Support Audio on Rockchip SoC (i2s-tdm, multicodecs)
endef

$(eval $(call KernelPackage,sound-soc-rockchip))

define KernelPackage/sound-soc-rk3308
  SUBMENU:=$(SOUND_MENU)
  DEPENDS:=@TARGET_rockchip +kmod-sound-soc-rockchip
  TITLE:=RK3308 Audio
  KCONFIG:=\
	CONFIG_SND_SOC_RK3308
  FILES:=\
	$(LINUX_DIR)/sound/soc/codecs/snd-soc-rk3308.ko
  AUTOLOAD:=$(call AutoLoad,81,snd-soc-rk3308)
endef

define KernelPackage/sound-soc-rk3308/description
  Support Audio on RK3308
endef

$(eval $(call KernelPackage,sound-soc-rk3308))
