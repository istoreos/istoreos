
include $(TOPDIR)/rules.mk

PKG_NAME:=rockchip-drivers
PKG_VERSION:=25.9.1
PKG_RELEASE:=1

PKG_HASH:=27741f54bb17542ade1a0d6a0118591e2a678f5759394a0f29fab39d5b5edc0d
PKG_SOURCE_URL_FILE:=v$(PKG_VERSION).tar.gz
PKG_SOURCE:=rockchip-drivers-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://github.com/jjm2473/rockchip-drivers/archive/refs/tags/

PKG_BUILD_PARALLEL:=1
PKG_EXTMOD_SUBDIRS:=drivers

PKG_MAINTAINER:=jjm2473 <jjm2473@gmail.com>

include $(INCLUDE_DIR)/kernel.mk
include $(INCLUDE_DIR)/package.mk

TAR_OPTIONS+= --strip-components 1
TAR_CMD=$(HOST_TAR) -C $(1) $(TAR_OPTIONS)

define KernelPackage/rockchip-sip
  TITLE:=Rockchip SIP interface
  HIDDEN:=1
  FILES:= \
	$(PKG_BUILD_DIR)/drivers/firmware/rockchip_sip.ko
endef

define KernelPackage/rockchip-pvtm
  TITLE:=Rockchip PVTM support
  HIDDEN:=1
  FILES:= \
	$(PKG_BUILD_DIR)/drivers/soc/rockchip/rockchip_pvtm.ko
  AUTOLOAD:=$(call AutoLoad,79,rockchip_pvtm)
endef

define KernelPackage/rockchip-opp-select
  TITLE:=Rockchip OPP select support
  HIDDEN:=1
  DEPENDS:=+kmod-rockchip-pvtm +kmod-rockchip-sip
  KCONFIG:=CONFIG_PM_DEVFREQ=y
  FILES:= \
	$(PKG_BUILD_DIR)/drivers/soc/rockchip/rockchip_opp_select.ko
endef

define KernelPackage/rockchip-system-monitor
  TITLE:=Rockchip system monitor support
  DEPENDS:=+kmod-rockchip-opp-select
  HIDDEN:=1
  FILES:= \
	$(PKG_BUILD_DIR)/drivers/soc/rockchip/rockchip_system_monitor.ko
  AUTOLOAD:=$(call AutoLoad,78,rockchip_system_monitor)
endef

# rockchip-ipa is only for linux before 6.1.0
define KernelPackage/rockchip-ipa
  TITLE:=Rockchip IPA support
  DEPENDS:=+kmod-rockchip-opp-select
  HIDDEN:=1
  FILES:= \
	$(PKG_BUILD_DIR)/drivers/soc/rockchip/rockchip_ipa.ko
endef

define KernelPackage/rga2
  SUBMENU:=Video Support
  TITLE:=RK RGA2
  DEPENDS:=@TARGET_rockchip

  FILES:= \
	$(PKG_BUILD_DIR)/drivers/video/rockchip/rga2/rga2.ko
  AUTOLOAD:=$(call AutoProbe,rga2)
endef

define KernelPackage/rga2/description
  RGA2
endef

define KernelPackage/rga3
  SUBMENU:=Video Support
  TITLE:=RK MULTI_RGA (RGA3)
  DEPENDS:=@TARGET_rockchip
  KCONFIG:=CONFIG_SYNC_FILE=y
  FILES:= \
	$(PKG_BUILD_DIR)/drivers/video/rockchip/rga3/rga3.ko
  AUTOLOAD:=$(call AutoProbe,rga3)
endef

define KernelPackage/rga3/description
  RGA3
endef

define KernelPackage/rk_vcodec
  SUBMENU:=Video Support
  TITLE:=RK mpp service framework (rk_vcodec)
  DEPENDS:=@TARGET_rockchip +kmod-rockchip-system-monitor
  FILES:= \
	$(PKG_BUILD_DIR)/drivers/video/rockchip/mpp/rk_vcodec.ko
  AUTOLOAD:=$(call AutoProbe,rk_vcodec)
endef

define KernelPackage/rk_vcodec/description
  RKMPP
endef

define KernelPackage/rknpu
  SUBMENU:=Other modules
  TITLE:=Rockchip RKNPU driver
  DEPENDS:=@TARGET_rockchip +kmod-drm +kmod-rockchip-system-monitor
  KCONFIG:=CONFIG_SYNC_FILE=y
  FILES:= \
	$(PKG_BUILD_DIR)/drivers/rknpu/rknpu.ko
  AUTOLOAD:=$(call AutoProbe,rknpu)
endef

define KernelPackage/rknpu/description
  Support Rockchip RKNPU
endef

define KernelPackage/rknpu/install
	$(INSTALL_DIR) $(1)/etc/modules-pending.d
	$(LN) ../modules.d/$(filter-out 0-,$(word 1,$(AUTOLOAD))-)$$(NAME) $(1)/etc/modules-pending.d/$$(NAME)
endef

# there is not a standalone cec.ko, so use that provided by drm-rockchip
define KernelPackage/rockchip-hdmirx
  SUBMENU:=Video Support
  TITLE:=Rockchip HDMI Receiver Vendor Driver
  DEPENDS:=@TARGET_rockchip kmod-video-core +kmod-video-dma-contig +kmod-video-dv-timings \
    +kmod-rockchip-sip +kmod-rockchip-system-monitor +kmod-drm-rockchip
  FILES:= \
	$(PKG_BUILD_DIR)/drivers/media/platform/rockchip/hdmirx/rockchip-hdmirx-class.ko \
	$(PKG_BUILD_DIR)/drivers/media/platform/rockchip/hdmirx/rockchip-hdmirx.ko
  AUTOLOAD:=$(call AutoProbe,rockchip-hdmirx)
endef

config-y:= CPU_RK3568 \
	CPU_RK3588 \
	CPU_RK3528 \
	CPU_RK3576 \
	CPU_RK3562 \
	CPU_RK3368
config-m:= ROCKCHIP_PVTM \
	ROCKCHIP_IPA \
	ROCKCHIP_SIP \
	ROCKCHIP_SYSTEM_MONITOR \
	ROCKCHIP_OPP

ifdef CONFIG_PACKAGE_kmod-rga2
  config-m += ROCKCHIP_RGA2
  config-y += ROCKCHIP_RGA2_PROC_FS \
	ROCKCHIP_RGA2_DEBUG_FS \
	ROCKCHIP_RGA2_DEBUGGER
endif

ifdef CONFIG_PACKAGE_kmod-rga3
  config-m += ROCKCHIP_MULTI_RGA
  config-y += ROCKCHIP_RGA_ASYNC \
	ROCKCHIP_RGA_PROC_FS \
	ROCKCHIP_RGA_DEBUG_FS \
	ROCKCHIP_RGA_DEBUGGER
endif

ifdef CONFIG_PACKAGE_kmod-rk_vcodec
  config-m += ROCKCHIP_MPP_SERVICE
  config-y += \
	ROCKCHIP_MPP_PROC_FS \
	ROCKCHIP_MPP_RKVDEC \
	ROCKCHIP_MPP_RKVDEC2 \
	ROCKCHIP_MPP_RKVENC \
	ROCKCHIP_MPP_RKVENC2 \
	ROCKCHIP_MPP_VDPU1 \
	ROCKCHIP_MPP_VEPU1 \
	ROCKCHIP_MPP_VDPU2 \
	ROCKCHIP_MPP_VEPU2 \
	ROCKCHIP_MPP_IEP2 \
	ROCKCHIP_MPP_JPGDEC \
	ROCKCHIP_MPP_JPGENC \
	ROCKCHIP_MPP_AV1DEC \
	ROCKCHIP_MPP_VDPP
endif

ifdef CONFIG_PACKAGE_kmod-rknpu
  config-m += ROCKCHIP_RKNPU
  config-y += \
	ROCKCHIP_RKNPU_DEBUG_FS \
	ROCKCHIP_RKNPU_PROC_FS \
	ROCKCHIP_RKNPU_DRM_GEM \
	ROCKCHIP_RKNPU_FENCE
endif

ifdef CONFIG_PACKAGE_kmod-rockchip-hdmirx
  config-m += \
	VIDEO_ROCKCHIP_HDMIRX_CLASS \
	VIDEO_ROCKCHIP_HDMIRX
endif

EXTRA_CFLAGS:=-I$(PKG_BUILD_DIR)/include -DBUILD_OPENWRT

EXTRA_CFLAGS+=$(foreach opt,$(config-y),-DCONFIG_$(opt)=1)
PKG_MAKE_FLAGS+=$(foreach opt,$(config-y),CONFIG_$(opt)=y)

EXTRA_CFLAGS+=$(foreach opt,$(config-m),-DCONFIG_$(opt)_MODULE=1)
PKG_MAKE_FLAGS+=$(foreach opt,$(config-m),CONFIG_$(opt)=m)

define Build/Compile
	+$(MAKE) $(PKG_JOBS) -C "$(LINUX_DIR)" \
		$(KERNEL_MAKE_FLAGS) \
		$(PKG_MAKE_FLAGS) \
		M="$(PKG_BUILD_DIR)/drivers" \
		EXTRA_CFLAGS="$(EXTRA_CFLAGS)" \
		modules
endef

$(eval $(call KernelPackage,rockchip-sip))
$(eval $(call KernelPackage,rockchip-ipa))
$(eval $(call KernelPackage,rockchip-pvtm))
$(eval $(call KernelPackage,rockchip-opp-select))
$(eval $(call KernelPackage,rockchip-system-monitor))
#$(eval $(call KernelPackage,rga2))
$(eval $(call KernelPackage,rga3))
$(eval $(call KernelPackage,rk_vcodec))
$(eval $(call KernelPackage,rknpu))
$(eval $(call KernelPackage,rockchip-hdmirx))
