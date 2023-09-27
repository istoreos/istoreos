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
	# METEORLAKE
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/mtl_dmc_ver2_12.bin $(1)/lib/firmware/i915/
	# DG2
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/dg2_dmc_ver2_07.bin $(1)/lib/firmware/i915/
	# ALDERLAKE_P ALDERLAKE_P_N
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/adlp_dmc_ver2_16.bin $(1)/lib/firmware/i915/
	# ALDERLAKE_S
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/adls_dmc_ver2_01.bin $(1)/lib/firmware/i915/
	# DG1
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/dg1_dmc_ver2_02.bin $(1)/lib/firmware/i915/
	# ROCKETLAKE
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/rkl_dmc_ver2_03.bin $(1)/lib/firmware/i915/
	# DISPLAY_VER >= 12
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/tgl_dmc_ver2_12.bin $(1)/lib/firmware/i915/

	# drivers/gpu/drm/i915/gt/uc/intel_uc_fw.c:INTEL_UC_FIRMWARE_DEFS
	## guc
	# METEORLAKE
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/mtl_guc_70.6.8.bin $(1)/lib/firmware/i915/
	# PONTEVECCHIO
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/pvc_guc_70.7.0.bin $(1)/lib/firmware/i915/
	# DG2
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/dg2_guc_70.7.0.bin $(1)/lib/firmware/i915/
	# XEHPSDV (skip for i915-oot driver not support yet)
	# $(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/xehpsdv_guc_70.7.0.bin $(1)/lib/firmware/i915/
	# ALDERLAKE_P
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/adlp_guc_70.7.0.bin $(1)/lib/firmware/i915/
	# ALDERLAKE_S ALDERLAKE_P_N ROCKETLAKE TIGERLAKE
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/tgl_guc_70.7.0.bin $(1)/lib/firmware/i915/
	# DG1
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/dg1_guc_70.7.0.bin $(1)/lib/firmware/i915/
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

	## huc
	# METEORLAKE
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/mtl_huc_8.3.7_gsc.bin $(1)/lib/firmware/i915/
	# PONTEVECCHIO
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/pvc_huc_7.8.7.bin $(1)/lib/firmware/i915/
	# DG2
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/dg2_huc_7.10.3_gsc.bin $(1)/lib/firmware/i915/
	# ALDERLAKE_P ALDERLAKE_P_N ALDERLAKE_S ROCKETLAKE TIGERLAKE
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/tgl_huc_7.9.3.bin $(1)/lib/firmware/i915/
	# DG1
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/dg1_huc_7.9.3.bin $(1)/lib/firmware/i915/

	## gsc
	# METEORLAKE
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/firmware/mtl_gsc_102.0.0.7366.bin $(1)/lib/firmware/i915/

endef

$(eval $(call BuildPackage,i915-oot-firmware))
