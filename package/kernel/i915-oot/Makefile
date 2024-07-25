
include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=i915-oot

PKG_VERSION:=23.6.37
PKG_RELEASE:=2
PKG_SOURCE_URL:=https://github.com/intel-gpu/intel-gpu-i915-backports/archive/refs/tags/
PKG_HASH:=0e962a0c656b365649262dbba317f8bbe9cad5357bc906a45b3a982600092321

I915_TAG:=I915_23WW35.5_682.20_23.6.28_230425.37
PKG_SOURCE_URL_FILE:=$(I915_TAG).tar.gz
PKG_SOURCE:=intel-gpu-i915-backports-$(PKG_SOURCE_URL_FILE)

PKG_BUILD_PARALLEL:=1

PKG_MAINTAINER:=jjm2473 <jjm2473@gmail.com>

include $(INCLUDE_DIR)/package.mk

TAR_OPTIONS+= --strip-components 1
TAR_CMD=$(HOST_TAR) -C $(1) $(TAR_OPTIONS)

config_package=$(if $(CONFIG_PACKAGE_kmod-$(1)),m)

config-y:= \
	DRM_I915_CAPTURE_ERROR \
	DRM_I915_COMPRESS_ERROR \
	DRM_I915_USERPTR \
	DRM_I915_DEBUGGER \
	DRM_I915_GVT \
	DRM_I915_LOW_LEVEL_TRACEPOINTS \


config-$(call config_package,drm-i915-oot) += \
	DRM_I915 \
	DRM_I915_GVT_KVMGT \
	DRM_I915_INTEL_FABRIC \


define KernelPackage/drm-i915-oot
  SUBMENU:=Video Support
  URL:=https://github.com/intel-gpu/intel-gpu-i915-backports
  MAINTAINER:=jjm2473 <jjm2473@gmail.com>
  TITLE:=Intel i915 backports
  DEPENDS+=@TARGET_x86 +i915-oot-firmware +kmod-drm-kms-helper +kmod-kvm-x86 +kmod-lib-crc32c +kmod-vfio-mdev
  CONFLICTS:=kmod-drm-i915
  ABI_VERSION:=$(PKG_VERSION)-$(PKG_RELEASE)
  FILES:= \
	$(PKG_BUILD_DIR)/compat/i915-compat.ko \
	$(PKG_BUILD_DIR)/drivers/gpu/drm/i915/i915.ko \
	$(PKG_BUILD_DIR)/drivers/gpu/drm/i915/gvt/kvmgt.ko \
	$(PKG_BUILD_DIR)/drivers/gpu/drm/i915/fabric/iaf.ko
  AUTOLOAD:=$(call AutoProbe,i915)
  MODPARAMS.i915:=enable_guc=3 max_vfs=7 enable_gvt=1 force_probe=*
endef

define KernelPackage/drm-i915-oot/description
Backported Intel i915 driver
endef

define KernelPackage/drm-i915-coex
  $(call KernelPackage/drm-i915-oot)
  TITLE:=Intel i915 backports (coexist)
  DEPENDS+=kmod-drm-i915
  CONFLICTS:=kmod-drm-i915-oot
endef

define KernelPackage/drm-i915-coex/description
Backported Intel i915 driver (coexist with drm-i915)
endef

define KernelPackage/drm-i915-coex/install
	mv $(1)/$(MODULES_SUBDIR) $(1)/i915-oot
	mv $(1)/etc/modules.d/$(filter-out 0-,$(word 1,$(AUTOLOAD))-)$$(NAME) $(1)/i915-oot/drm-i915
	rm -rf $(1)/etc/modules.d
	$(INSTALL_DIR) $(1)/$(MODULES_SUBDIR)
	mv $(1)/i915-oot $(1)/$(MODULES_SUBDIR)/
	mv $(1)/$(MODULES_SUBDIR)/i915-oot/i915-compat.ko $(1)/$(MODULES_SUBDIR)/

	$(INSTALL_DIR) $(1)/etc/modules-pending.d
	touch $(1)/etc/modules-pending.d/i915-oot

	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/i915_oot.init $(1)/etc/init.d/i915_oot
	$(INSTALL_BIN) ./files/i915_oot_done.init $(1)/etc/init.d/i915_oot_done
endef

MAKE_OPTS:= -C "$(PKG_BUILD_DIR)" \
	$(KERNEL_MAKE_FLAGS) \
	EXTRA_CFLAGS="-I$(PKG_BUILD_DIR)/include $(IREMAP_CFLAGS)" \
	KLIB_BUILD="$(LINUX_DIR)" \
	MODPROBE=true \
	KLIB=$(TARGET_MODULES_DIR) \
	KERNEL_SUBLEVEL=$(lastword $(subst ., ,$(KERNEL_PATCHVER))) \
	KBUILD_LDFLAGS_MODULE_PREREQ=

define ConfigVars
$(subst $(space),,$(foreach opt,$(config-$(1)),CPTCFG_$(opt)=$(1)
))
endef

define i915_config
$(call ConfigVars,m)$(call ConfigVars,y)
endef
$(eval $(call shexport,i915_config))

define Build/Configure
	$(SH_FUNC) var2file "$(call shvar,i915_config)" $(PKG_BUILD_DIR)/.config
	$(MAKE) $(MAKE_OPTS) olddefconfig
endef

define Build/Compile/kmod
	rm -rf $(PKG_BUILD_DIR)/modules
	+$(MAKE) $(PKG_JOBS) $(MAKE_OPTS) modules
endef

define Build/Compile
	$(call Build/Compile/kmod)
endef

define KernelPackage/drm-i915-oot/install
endef

$(eval $(call KernelPackage,drm-i915-oot))
$(eval $(call KernelPackage,drm-i915-coex))
