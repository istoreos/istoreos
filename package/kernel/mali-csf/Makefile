
include $(TOPDIR)/rules.mk

PKG_NAME:=mali-csf
PKG_VERSION:=g17p0-01eac0
PKG_RELEASE:=1

PKG_BUILD_PARALLEL:=1

PKG_MAINTAINER:=jjm2473 <jjm2473@gmail.com>

include $(INCLUDE_DIR)/kernel.mk
include $(INCLUDE_DIR)/package.mk

define KernelPackage/rkgpu-bifrost-csf
  SUBMENU:=Other modules
  TITLE:=Rockchip RK3588 GPU driver
  DEPENDS:=@TARGET_rockchip_rk35xx +kmod-dma-buf +mali-csf-firmware
  CONFLICTS:=kmod-rkgpu-bifrost
  FILES:= \
	$(PKG_BUILD_DIR)/bifrost/bifrost_kbase.ko
  AUTOLOAD:=$(call AutoLoad,85,bifrost_kbase)
endef

define KernelPackage/rkgpu-bifrost-csf/description
  Support Rockchip GPU Mali bifrost (CSF, RK3588 only)
endef

define KernelPackage/rkgpu-bifrost-csf-coex
  $(call KernelPackage/rkgpu-bifrost-csf)
  TITLE:=Rockchip RK3588/RK356x GPU driver (coexist)
  DEPENDS+=+kmod-rkgpu-bifrost
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

config-y:= \
	MALI_CSF_SUPPORT \
	MALI_BIFROST_EXPERT \
	MALI_BIFROST_DEBUG \
	MALI_REAL_HW \
	MALI_BIFROST_DEVFREQ \
	MALI_BIFROST_GATOR_SUPPORT \
	MALI_PRFCNT_SET_PRIMARY \


NOSTDINC_FLAGS+=$(foreach opt,$(config-y),-DCONFIG_$(opt)=1)
PKG_MAKE_FLAGS+=$(foreach opt,$(config-y),CONFIG_$(opt)=y)

PKG_MAKE_FLAGS+=CONFIG_MALI_BIFROST=m CONFIG_MALI_PLATFORM_NAME=rk

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) $(LINUX_DIR)/drivers/gpu/arm/bifrost $(PKG_BUILD_DIR)/
	@-find $(PKG_BUILD_DIR)/bifrost -name '*.o' -o -name '*.ko' | $(XARGS) rm -f
endef

define Build/Compile
	+$(MAKE) $(PKG_JOBS) -C "$(LINUX_DIR)" \
		$(KERNEL_MAKE_FLAGS) \
		$(PKG_MAKE_FLAGS) \
		M="$(PKG_BUILD_DIR)/bifrost" \
		NOSTDINC_FLAGS="$(NOSTDINC_FLAGS)" \
		modules
endef

$(eval $(call KernelPackage,rkgpu-bifrost-csf))
$(eval $(call KernelPackage,rkgpu-bifrost-csf-coex))
