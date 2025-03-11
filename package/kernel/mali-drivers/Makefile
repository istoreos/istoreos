
include $(TOPDIR)/rules.mk

PKG_NAME:=mali-drivers
PKG_VERSION:=24.11.1
PKG_RELEASE:=4

PKG_HASH:=2fe6146c141639eea4a2625be073387b8de3b8f3d9384ce495c411c7bbd6da61
PKG_SOURCE_URL_FILE:=v$(PKG_VERSION).tar.gz
PKG_SOURCE:=mali-drivers-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://github.com/jjm2473/mali-drivers/archive/refs/tags/

PKG_BUILD_DEPENDS:=rockchip-drivers
PKG_BUILD_PARALLEL:=1

PKG_MAINTAINER:=jjm2473 <jjm2473@gmail.com>

include $(INCLUDE_DIR)/kernel.mk
include $(INCLUDE_DIR)/package.mk

TAR_OPTIONS+= --strip-components 1
TAR_CMD=$(HOST_TAR) -C $(1) $(TAR_OPTIONS)

define KernelPackage/rkgpu-bifrost
  SUBMENU:=Other modules
  DEPENDS:=@TARGET_rockchip +kmod-dma-buf +kmod-rockchip-system-monitor
  VARIANT:=normal
  TITLE:=Rockchip GPU Mali bifrost driver
  FILES:=$(PKG_BUILD_DIR)/drivers/gpu/arm/bifrost/bifrost_kbase.ko
  AUTOLOAD:=$(call AutoLoad,85,bifrost_kbase)
endef

define KernelPackage/rkgpu-bifrost/description
  Support Rockchip GPU Mali bifrost (RK356x, etc.)
endef

define KernelPackage/rkgpu-mali400
  SUBMENU:=Other modules
  DEPENDS:=@TARGET_rockchip +kmod-dma-buf +kmod-rockchip-system-monitor
  VARIANT:=normal
  TITLE:=Rockchip GPU Mali 400 driver
  FILES:=$(PKG_BUILD_DIR)/drivers/gpu/arm/mali400/mali/mali.ko
  AUTOLOAD:=$(call AutoLoad,85,mali)
endef

define KernelPackage/rkgpu-mali400/description
  Support Rockchip GPU Mali 400 (450/470) (RK3528, etc.)
endef

define KernelPackage/rkgpu-bifrost-csf
$(call KernelPackage/rkgpu-bifrost)
  TITLE:=Rockchip RK3588 GPU driver
  DEPENDS+= +mali-csf-firmware
  VARIANT:=csf
  CONFLICTS:=kmod-rkgpu-bifrost
endef

define KernelPackage/rkgpu-bifrost-csf/description
  Support Rockchip GPU Mali bifrost (CSF, RK3588 only)
endef

define KernelPackage/rkgpu-bifrost-csf-coex
$(call KernelPackage/rkgpu-bifrost-csf)
  TITLE:=Rockchip RK3588/RK356x GPU driver (coexist)
  DEPENDS+= +kmod-rkgpu-bifrost
  CONFLICTS:=
endef

define KernelPackage/rkgpu-bifrost-csf-coex/description
  Support Rockchip RK3588/RK356x GPU (coexist with rkgpu-bifrost)
endef

define KernelPackage/rkgpu-bifrost-csf-coex/install
	$(INSTALL_DIR) $(1)/$(MODULES_SUBDIR)/bifrost-csf
	mv $(1)/$(MODULES_SUBDIR)/bifrost_kbase.ko $(1)/$(MODULES_SUBDIR)/bifrost-csf/
	mv $(1)/etc/modules.d/$(filter-out 0-,$(word 1,$(AUTOLOAD))-)$$(NAME) $(1)/$(MODULES_SUBDIR)/bifrost-csf/rkgpu-bifrost
	rm -rf $(1)/etc/modules.d

	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/bifrost_csf.init $(1)/etc/init.d/bifrost_csf
endef

config-y:= CPU_RK3568 \
	CPU_RK3588 \
	CPU_RK3528 \
	CPU_RK3576 \
	CPU_RK3562 \
	CPU_RK3368
config-m:= ROCKCHIP_PVTM \
	ROCKCHIP_IPA \
	ROCKCHIP_SYSTEM_MONITOR \
	ROCKCHIP_OPP

ifeq ($(BUILD_VARIANT),csf)
  BUILD_MALI_BIFROST:=y
  config-y += MALI_CSF_SUPPORT
else
ifdef CONFIG_PACKAGE_kmod-rkgpu-bifrost
  BUILD_MALI_BIFROST:=y
endif
endif

ifdef BUILD_MALI_BIFROST
  config-m += MALI_BIFROST
  config-y += MALI_REAL_HW \
	MALI_BIFROST_DEVFREQ \
	MALI_BIFROST_GATOR_SUPPORT \
	MALI_BIFROST_EXPERT \
	MALI_BIFROST_DEBUG \
	MALI_PRFCNT_SET_PRIMARY \
	MALI_PWRSOFT_765 \

endif

ifeq ($(BUILD_VARIANT),normal)
ifdef CONFIG_PACKAGE_kmod-rkgpu-mali400
  config-m += MALI400
  config-y += MALI450 \
	MALI470 \
	MALI_DMA_BUF_MAP_ON_ATTACH \
	MALI_SHARED_INTERRUPTS \
	MALI_DT \
	MALI_DEVFREQ \

endif
endif

EXTRA_CFLAGS:=-I$(PKG_BUILD_DIR)/include -DBUILD_OPENWRT

EXTRA_CFLAGS+=$(foreach opt,$(config-y),-DCONFIG_$(opt)=1)
PKG_MAKE_FLAGS+=$(foreach opt,$(config-y),CONFIG_$(opt)=y)

EXTRA_CFLAGS+=$(foreach opt,$(config-m),-DCONFIG_$(opt)_MODULE=1)
PKG_MAKE_FLAGS+=$(foreach opt,$(config-m),CONFIG_$(opt)=m)

ifdef BUILD_MALI_BIFROST
EXTRA_CFLAGS+= -DCONFIG_MALI_PLATFORM_NAME="rk"
PKG_MAKE_FLAGS+= CONFIG_MALI_PLATFORM_NAME="rk"
endif

define Build/Compile
	+$(MAKE) $(PKG_JOBS) -C "$(LINUX_DIR)" \
		$(KERNEL_MAKE_FLAGS) \
		$(PKG_MAKE_FLAGS) \
		M="$(PKG_BUILD_DIR)/drivers/gpu/arm" \
		EXTRA_CFLAGS="$(EXTRA_CFLAGS)" \
		modules
endef

$(eval $(call KernelPackage,rkgpu-bifrost))
$(eval $(call KernelPackage,rkgpu-bifrost-csf))
$(eval $(call KernelPackage,rkgpu-bifrost-csf-coex))
$(eval $(call KernelPackage,rkgpu-mali400))
