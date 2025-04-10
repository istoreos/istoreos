
# RK3588

define Device/Legacy/rk3588
$(call Device/Legacy,$(1))
  SOC := rk3588
  UBOOT_DEVICE_NAME := easepi-rk3588
  BOOT_SCRIPT := rk3588
  DEVICE_PACKAGES := kmod-rga3 kmod-rk_vcodec kmod-rkgpu-bifrost-csf-coex kmod-rknpu kmod-iio-rockchip-saradc
endef

define Device/Legacy/rk3588s
$(call Device/Legacy/rk3588,$(1))
  SOC := rk3588s
  DEVICE_DTS = rk3588/$$(SOC)-$(lastword $(subst _, ,$(1)))
endef

define Device/friendlyarm_nanopi-r6s
$(call Device/Legacy/rk3588s,$(1))
  DEVICE_VENDOR := FriendlyARM
  DEVICE_MODEL := NanoPi R6S/R6C
  SUPPORTED_DEVICES += friendlyarm,nanopi-r6s friendlyarm,nanopi-r6c
  SUPPORTED_DEVICES += friendlyelec,nanopi-r6s friendlyelec,nanopi-r6c
  DEVICE_DTS := rk3588/rk3588s-nanopi-r6s rk3588/rk3588s-nanopi-r6c
  BOOT_SCRIPT := rk3588-friendlyelec
  DEVICE_PACKAGES += kmod-r8169
endef

# avoid using upstream dts
define Device/friendlyarm_nanopi-r6c
$(call Device/Legacy/rk3588s,$(1))
  DEVICE_VENDOR := FriendlyARM
  DEVICE_MODEL := NanoPi R6C
  DEVICE_PACKAGES += kmod-r8169
endef
