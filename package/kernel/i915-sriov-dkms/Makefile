
include $(TOPDIR)/rules.mk

PKG_NAME:=i915-sriov-dkms
PKG_VERSION:=2026.03.05.6
PKG_RELEASE:=1

PKG_HASH:=b3d042565f77801237fb00db78a4af248210e352a9286003e95a679eec251333
PKG_SOURCE_URL_FILE:=$(PKG_VERSION).tar.gz
PKG_SOURCE:=i915-sriov-dkms-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://github.com/strongtz/i915-sriov-dkms/archive/refs/tags/

PKG_BUILD_PARALLEL:=1

PKG_MAINTAINER:=jjm2473 <jjm2473@gmail.com>

include $(INCLUDE_DIR)/kernel.mk
include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/version.mk

TAR_OPTIONS+= --strip-components 1
TAR_CMD=$(HOST_TAR) -C $(1) $(TAR_OPTIONS)

define KernelPackage/intel-sriov-compat
  SUBMENU:=Video Support
  HIDDEN:=1
  TITLE:=Intel SR-IOV compatibility module
  DEPENDS:=+kmod-drm-display-helper +kmod-drm-gpuvm
  FILES:= \
	$(PKG_BUILD_DIR)/compat/intel_sriov_compat.ko
endef

define KernelPackage/drm-i915-sriov
  SUBMENU:=Video Support
  URL:=https://github.com/strongtz/i915-sriov-dkms
  MAINTAINER:=jjm2473 <jjm2473@gmail.com>
  TITLE:=Intel i915 driver with SR-IOV supported
  DEPENDS:=+kmod-kvm-x86 +kmod-intel-sriov-compat \
	@(TARGET_x86_64||TARGET_x86_generic||TARGET_x86_legacy) \
	@DISPLAY_SUPPORT +kmod-backlight +kmod-drm-ttm \
	+kmod-drm-ttm-helper +kmod-drm-kms-helper +kmod-i2c-algo-bit +i915-firmware \
	+kmod-drm-display-helper +kmod-drm-buddy +kmod-acpi-video \
	+kmod-drm-exec +kmod-drm-suballoc-helper
  CONFLICTS:=kmod-drm-i915
  FILES:= \
	$(PKG_BUILD_DIR)/drivers/gpu/drm/i915/i915.ko
  AUTOLOAD:=$(call AutoProbe,i915)
  MODPARAMS.i915:=enable_guc=3 max_vfs=7 enable_gvt=1 force_probe=*
endef

define KernelPackage/drm-i915-coex
  $(call KernelPackage/drm-i915-sriov)
  TITLE:=Intel i915 driver with SR-IOV supported(coexist)
  DEPENDS+=kmod-drm-i915
  CONFLICTS:=kmod-drm-i915-sriov
endef

define KernelPackage/drm-i915-coex/description
Intel i915 driver with SR-IOV supported (coexist with drm-i915)
endef

define KernelPackage/drm-i915-coex/install
	mv $(1)/$(MODULES_SUBDIR) $(1)/i915-sriov
	mv $(1)/etc/modules.d/$(filter-out 0-,$(word 1,$(AUTOLOAD))-)$$(NAME) $(1)/i915-sriov/drm-i915
	rm -rf $(1)/etc/modules.d
	$(INSTALL_DIR) $(1)/$(MODULES_SUBDIR)
	mv $(1)/i915-sriov $(1)/$(MODULES_SUBDIR)/

	$(INSTALL_DIR) $(1)/etc/modules-pending.d
	touch $(1)/etc/modules-pending.d/i915-sriov

	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/i915_sriov.init $(1)/etc/init.d/i915_sriov
	$(INSTALL_BIN) ./files/i915_sriov_done.init $(1)/etc/init.d/i915_sriov_done
endef

define KernelPackage/drm-xe-sriov
  SUBMENU:=Video Support
  URL:=https://github.com/strongtz/i915-sriov-dkms
  MAINTAINER:=jjm2473 <jjm2473@gmail.com>
  TITLE:=Intel Xe driver with SR-IOV supported
  DEPENDS:=+kmod-kvm-x86 +kmod-intel-sriov-compat +kmod-fs-configfs \
	@(TARGET_x86_64||TARGET_x86_generic||TARGET_x86_legacy) \
	@DISPLAY_SUPPORT +kmod-backlight +kmod-drm-ttm \
	+kmod-drm-ttm-helper +kmod-drm-kms-helper +kmod-i2c-algo-bit +xe-firmware \
	+kmod-drm-display-helper +kmod-drm-buddy +kmod-acpi-video \
	+kmod-drm-exec +kmod-drm-gpuvm +kmod-drm-sched +kmod-drm-suballoc-helper
  CONFLICTS:=kmod-drm-xe
  FILES:= \
	$(PKG_BUILD_DIR)/drivers/gpu/drm/xe/xe.ko
  AUTOLOAD:=$(call AutoProbe,xe)
  MODPARAMS.xe:=max_vfs=7 force_probe=*
endef

define KernelPackage/drm-xe-sriov/install
	$(INSTALL_DIR) $(1)/etc/modules-pending.d
	$(LN) ../modules.d/$(filter-out 0-,$(word 1,$(AUTOLOAD))-)$$(NAME) $(1)/etc/modules-pending.d/xe-sriov
endef

define Package/kmod-drm-xe-sriov/postinst
#!/bin/sh
[ -n "$${IPKG_INSTROOT}" ] || rm -f /etc/modules-pending.d/xe-sriov
endef

define Build/Compile
	+$(KERNEL_MAKE) $(PKG_JOBS) \
		$(PKG_MAKE_FLAGS) \
		M="$(PKG_BUILD_DIR)" \
		NOSTDINC_FLAGS="$(NOSTDINC_FLAGS)" \
		modules
endef

$(eval $(call KernelPackage,intel-sriov-compat))
$(eval $(call KernelPackage,drm-i915-sriov))
$(eval $(call KernelPackage,drm-i915-coex))
$(eval $(call KernelPackage,drm-xe-sriov))
