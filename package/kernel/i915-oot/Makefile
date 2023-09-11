
include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=i915-oot

PKG_VERSION:=23.6.24
PKG_RELEASE:=1
PKG_SOURCE_URL:=https://github.com/intel-gpu/intel-gpu-i915-backports/archive/refs/tags/
PKG_HASH:=af5752778be0334acf5aa27bd4ec6d2868c20225ea861f4a8e77b79ca5f33c4b

I915_TAG:=I915_23WW31.5_682.14_23.6.24_230425.29
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
  DEPENDS+=+i915-firmware +kmod-drm-kms-helper +kmod-kvm-x86 +kmod-lib-crc32c +kmod-vfio-mdev
  CONFLICTS:=kmod-drm-i915
  ABI_VERSION:=$(PKG_VERSION)-$(PKG_RELEASE)
  FILES:= \
	$(PKG_BUILD_DIR)/compat/i915-compat.ko \
	$(PKG_BUILD_DIR)/drivers/gpu/drm/i915/i915.ko \
	$(PKG_BUILD_DIR)/drivers/gpu/drm/i915/gvt/kvmgt.ko \
	$(PKG_BUILD_DIR)/drivers/gpu/drm/i915/fabric/iaf.ko
  AUTOLOAD:=$(call AutoProbe,i915)
  MODPARAMS.i915:=enable_guc=3 max_vfs=7 enable_gvt=1
endef

define KernelPackage/drm-i915-oot/description
Backported Intel i915 driver
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
