include $(TOPDIR)/rules.mk

PKG_NAME:=intel-gpu-firmware
PKG_VERSION:=682.20
PKG_RELEASE:=1

I915_FW_TAG:=23WW35.5_682.20
PKG_SOURCE_URL_FILE:=$(I915_FW_TAG).tar.gz
PKG_SOURCE:=intel-gpu-firmware-$(PKG_SOURCE_URL_FILE)
PKG_SOURCE_URL:=https://github.com/intel-gpu/intel-gpu-firmware/archive/refs/tags/
PKG_HASH:=1ab6d68103b70b999a469f815156931463571cb1d2440e1041110b3cf9b18fc7

include $(INCLUDE_DIR)/package.mk

TAR_OPTIONS+= --strip-components 1
TAR_CMD=$(HOST_TAR) -C $(1) $(TAR_OPTIONS)

define Package/i915-oot-firmware
  SECTION:=firmware
  CATEGORY:=Firmware
  URL:=$(PKG_SOURCE_URL)
  DEPENDS:=@TARGET_x86 +i915-firmware
  TITLE:=Intel GPU firmware for i915-oot
endef

define Build/Compile

endef

define Package/i915-oot-firmware/install
	$(INSTALL_DIR) $(1)/lib/firmware/i915

	# don't include firmwares in package/firmware/linux-firmware/intel.mk:i915-firmware

	# drivers/gpu/drm/i915/display/intel_dmc.c:intel_dmc_ucode_init
	# ALDERLAKE_P ALDERLAKE_P_N
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/adlp_dmc_ver2_16.bin $(1)/lib/firmware/i915/

	# drivers/gpu/drm/i915/gt/uc/intel_uc_fw.c:INTEL_UC_FIRMWARE_DEFS
	## guc
	# ALDERLAKE_P
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/adlp_guc_70.7.0.bin $(1)/lib/firmware/i915/
	# ALDERLAKE_S ALDERLAKE_P_N ROCKETLAKE TIGERLAKE
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/tgl_guc_70.7.0.bin $(1)/lib/firmware/i915/
	# JASPERLAKE ELKHARTLAKE
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/ehl_guc_70.7.0.bin $(1)/lib/firmware/i915/
	# ICELAKE
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/icl_guc_70.7.0.bin $(1)/lib/firmware/i915/
	# COMETLAKE (REV >= 5)
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/cml_guc_70.7.0.bin $(1)/lib/firmware/i915/
	# COMETLAKE COFFEELAKE KABYLAKE
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/kbl_guc_70.7.0.bin $(1)/lib/firmware/i915/
	# GEMINILAKE
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/glk_guc_70.7.0.bin $(1)/lib/firmware/i915/
	# BROXTON
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/bxt_guc_70.7.0.bin $(1)/lib/firmware/i915/
	# SKYLAKE
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/skl_guc_70.7.0.bin $(1)/lib/firmware/i915/

endef

$(eval $(call BuildPackage,i915-oot-firmware))
