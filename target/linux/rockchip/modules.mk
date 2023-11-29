
define KernelPackage/drm-rockchip-rk35xx
  SUBMENU:=$(VIDEO_MENU)
  DEPENDS:=@TARGET_rockchip_rk35xx +kmod-drm
  TITLE:=DRM for rockchip RK35xx
  KCONFIG:=\
	CONFIG_DRM_ROCKCHIP \
	CONFIG_DRM_DW_HDMI \
	CONFIG_DRM_DW_HDMI_CEC \
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
  AUTOLOAD:=$(call AutoProbe,dw-hdmi-cec dw-hdmi-hdcp dw-hdmi-qp-cec rockchipdrm)
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
  AUTOLOAD:=$(call AutoProbe,dw_hdcp2 phy-rockchip-samsung-hdptx-hdmi)
endef

define KernelPackage/drm-rockchip-rk35xx-hdmitx/description
  Support HDMI TX on RK35xx
endef

$(eval $(call KernelPackage,drm-rockchip-rk35xx-hdmitx))

define KernelPackage/drm-rockchip-rk35xx-vvop
  SUBMENU:=$(VIDEO_MENU)
  DEPENDS:=@TARGET_rockchip_rk35xx +kmod-drm @!PACKAGE_kmod-drm-rockchip-rk35xx
  TITLE:=Rockchip virtual VOP drm driver
  KCONFIG:=\
	CONFIG_DRM_ROCKCHIP \
	CONFIG_DRM_ROCKCHIP_VVOP=y
  FILES:=$(LINUX_DIR)/drivers/gpu/drm/rockchip/rockchipdrm.ko
  AUTOLOAD:=$(call AutoProbe,rockchipdrm)
endef

define KernelPackage/drm-rockchip-rk35xx-vvop/description
  If you want use some module of rockchip drm, but
  don't need a real vop driver(et: you just want rockchip drm
  gem driver to allocate memory).
endef

$(eval $(call KernelPackage,drm-rockchip-rk35xx-vvop))
