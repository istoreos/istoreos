
include $(TOPDIR)/rules.mk

PKG_NAME:=i915-sriov-dkms
PKG_VERSION:=2024.10.04
PKG_RELEASE:=2

PKG_SOURCE_VERSION:=e26ce8952e465762fc0743731aa377ec0b2889ff
PKG_HASH:=f573523d54cbe30862592e9c2a34cb88683d413357f220c24be20d08592e1f2e
PKG_SOURCE_URL_FILE:=$(PKG_SOURCE_VERSION).tar.gz
PKG_SOURCE:=i915-sriov-dkms-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://github.com/strongtz/i915-sriov-dkms/archive/

PKG_BUILD_PARALLEL:=1

PKG_MAINTAINER:=jjm2473 <jjm2473@gmail.com>

include $(INCLUDE_DIR)/kernel.mk
include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/version.mk

TAR_OPTIONS+= --strip-components 1
TAR_CMD=$(HOST_TAR) -C $(1) $(TAR_OPTIONS)

define KernelPackage/drm-i915-sriov
  SUBMENU:=Video Support
  URL:=https://github.com/strongtz/i915-sriov-dkms
  MAINTAINER:=jjm2473 <jjm2473@gmail.com>
  TITLE:=Intel i915 driver with SR-IOV supported
  DEPENDS+=@TARGET_x86 +kmod-drm-kms-helper +kmod-kvm-x86 +kmod-lib-crc32c \
	+kmod-drm-buddy +kmod-drm-display-helper +kmod-acpi-video
  CONFLICTS:=kmod-drm-i915
  FILES:= \
	$(PKG_BUILD_DIR)/i915.ko
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

define Build/Compile
	+$(KERNEL_MAKE) $(PKG_JOBS) \
		$(PKG_MAKE_FLAGS) \
		M="$(PKG_BUILD_DIR)" \
		NOSTDINC_FLAGS="$(NOSTDINC_FLAGS)" \
		LSBRELEASE="$(VERSION_NUMBER)" \
		LSBRELEASE_NAME="$(VERSION_DIST)" \
		GUCFIRMWARE_MINOR=13 \
		modules
endef

$(eval $(call KernelPackage,drm-i915-sriov))
$(eval $(call KernelPackage,drm-i915-coex))
