# RK3328

define Device/Legacy/rk3328
$(call Device/Legacy,$(1))
  SOC := rk3328
  DEVICE_PACKAGES := kmod-iio-rockchip-saradc
endef

# avoid using upstream dts
define Device/friendlyarm_nanopi-r2c
$(call Device/Legacy/rk3328,$(1))
  DEVICE_VENDOR := FriendlyARM
  DEVICE_MODEL := NanoPi R2C | Plus
  DEVICE_PACKAGES += kmod-usb-net-rtl8152 ethtool
endef

define Device/friendlyarm_nanopi-r2s
$(call Device/friendlyarm_nanopi-r2c,$(1))
  DEVICE_MODEL := NanoPi R2S/R2C | Plus
  SUPPORTED_DEVICES += friendlyarm,nanopi-r2s friendlyarm,nanopi-r2c
  DEVICE_DTS := rk3328/rk3328-nanopi-r2s rk3328/rk3328-nanopi-r2c
  BOOT_SCRIPT := rk3328-friendlyelec
endef


# RK3528

define Device/Legacy/rk3528
$(call Device/Legacy,$(1))
  SOC := rk3528
  UBOOT_DEVICE_NAME := easepi-rk3528
  BOOT_SCRIPT := rk3528
  DEVICE_PACKAGES := kmod-rga3 kmod-rk_vcodec kmod-iio-rockchip-saradc
endef

define Device/Legacy/rk3528_rtl8111h
$(call Device/Legacy/rk3528,$(1))
  DEVICE_PACKAGES += kmod-r8169 kmod-thermal
endef

define Device/hlink_h28k
$(call Device/Legacy/rk3528_rtl8111h,$(1))
  DEVICE_VENDOR := Hlink
  DEVICE_MODEL := H28K
endef
TARGET_DEVICES += hlink_h28k

define Device/radxa_e20c
$(call Device/Legacy/rk3528_rtl8111h,$(1))
  DEVICE_VENDOR := Radxa
  DEVICE_MODEL := E20C
endef
TARGET_DEVICES += radxa_e20c

define Device/radxa_e24c
$(call Device/Legacy/rk3528,$(1))
  DEVICE_VENDOR := Radxa
  DEVICE_MODEL := E24C
  DEVICE_PACKAGES += kmod-nvme kmod-hwmon-pwmfan kmod-thermal kmod-switch-rtl8367b swconfig
endef
TARGET_DEVICES += radxa_e24c


# RK3568

define Device/Legacy/rk3568
$(call Device/Legacy,$(1))
  SOC := rk3568
  UBOOT_DEVICE_NAME := easepi-rk3568
  BOOT_SCRIPT := rk3568
  DEVICE_PACKAGES := kmod-rga3 kmod-rk_vcodec kmod-rkgpu-bifrost kmod-rknpu kmod-iio-rockchip-saradc
endef

define Device/Legacy/rk3566
$(call Device/Legacy/rk3568,$(1))
  SOC := rk3566
  DEVICE_DTS = rk3568/$$(SOC)-$(lastword $(subst _, ,$(1)))
endef

define Device/easepi_r1
$(call Device/Legacy/rk3568,$(1))
  DEVICE_VENDOR := EasePi
  DEVICE_MODEL := R1
  DEVICE_DTS := rk3568/rk3568-easepi-r1
  DEVICE_PACKAGES += kmod-r8169 kmod-nvme
endef
TARGET_DEVICES += easepi_r1

define Device/easepi_r1-lite
$(call Device/Legacy/rk3568,$(1))
  DEVICE_VENDOR := EasePi
  DEVICE_MODEL := R1 (4xGbE)
  DEVICE_DTS := rk3568/rk3568-easepi-r1-lite
  DEVICE_PACKAGES += kmod-r8169 kmod-nvme
endef
TARGET_DEVICES += easepi_r1-lite

define Device/easepi_ars4
$(call Device/Legacy/rk3568,$(1))
  DEVICE_VENDOR := EasePi
  DEVICE_MODEL := ARS4
  DEVICE_PACKAGES += kmod-r8169 kmod-ata-ahci-dwc kmod-hwmon-pwmfan kmod-thermal
endef
TARGET_DEVICES += easepi_ars4

define Device/fastrhino_r6xs
$(call Device/Legacy/rk3568,$(1))
  DEVICE_VENDOR := FastRhino
  DEVICE_MODEL := R68s/R66s combined
  SUPPORTED_DEVICES += lunzn,fastrhino-r66s lunzn,fastrhino-r68s
  SUPPORTED_DEVICES += fastrhino,r66s fastrhino,r68s
  DEVICE_DTS := rk3568/rk3568-fastrhino-r66s rk3568/rk3568-fastrhino-r68s
  BOOT_SCRIPT := rk3568-fastrhino
  DEVICE_PACKAGES += kmod-r8169
endef
TARGET_DEVICES += fastrhino_r6xs

define Device/friendlyarm_nanopi-r3s
$(call Device/Legacy/rk3566,$(1))
  DEVICE_VENDOR := FriendlyARM
  DEVICE_MODEL := NanoPi R3S
  SUPPORTED_DEVICES += friendlyelec,nanopi-r3s friendlyarm,nanopi-r3s
  DEVICE_PACKAGES += kmod-r8169
endef

define Device/firefly_station-m2
$(call Device/Legacy/rk3566,$(1))
  DEVICE_VENDOR := Firefly
  DEVICE_MODEL := Station M2 / RK3566 ROC PC
  DEVICE_DTS := rk3568/rk3566-roc-pc
  SUPPORTED_DEVICES += firefly,rk3566-roc-pc firefly,station-m2
  DEVICE_PACKAGES := kmod-nvme kmod-scsi-core
endef
TARGET_DEVICES += firefly_station-m2

define Device/friendlyarm_nanopi-r5c
$(call Device/Legacy/rk3568,$(1))
  DEVICE_VENDOR := FriendlyARM
  DEVICE_MODEL := NanoPi R5C
  DEVICE_PACKAGES += kmod-r8169 kmod-rtw88-8822ce rtl8822ce-firmware wpad-basic-mbedtls
endef

define Device/friendlyarm_nanopi-r5s
$(call Device/friendlyarm_nanopi-r5c,$(1))
  DEVICE_MODEL := NanoPi R5S/R5C combined
  SUPPORTED_DEVICES += friendlyarm,nanopi-r5s friendlyarm,nanopi-r5c
  SUPPORTED_DEVICES += friendlyelec,nanopi-r5s friendlyelec,nanopi-r5c  friendlyelec,nanopi-r5s-c1
  DEVICE_DTS := rk3568/rk3568-nanopi-r5s rk3568/rk3568-nanopi-r5c rk3568/rk3568-nanopi-r5s-lts rk3568/rk3568-nanopi-r5s-c1
  BOOT_SCRIPT := rk3568-friendlyelec
endef


define Device/rk3568/hinlink
$(call Device/Legacy/rk3568,$(1))
  DEVICE_VENDOR := HINLINK
  DEVICE_PACKAGES += kmod-r8169 kmod-ata-ahci-dwc kmod-hwmon-pwmfan kmod-thermal
endef

define Device/hinlink_opc-h6xk
$(call Device/rk3568/hinlink,$(1))
  DEVICE_MODEL := OPC-H69K/H68K/H66K combined
  SUPPORTED_DEVICES += hinlink,opc-h66k hinlink,opc-h68k hinlink,opc-h69k
  DEVICE_DTS := rk3568/rk3568-opc-h66k rk3568/rk3568-opc-h68k rk3568/rk3568-opc-h69k
  BOOT_SCRIPT := rk3568-hinlink
endef
TARGET_DEVICES += hinlink_opc-h6xk

define Device/hinlink_hnas
$(call Device/rk3568/hinlink,$(1))
  DEVICE_MODEL := HNAS
  DEVICE_PACKAGES += kmod-aic8800s
endef
TARGET_DEVICES += hinlink_hnas

define Device/lyt_t68m
$(call Device/Legacy/rk3568,$(1))
  DEVICE_VENDOR := LYT
  DEVICE_MODEL := T68M
  DEVICE_PACKAGES := kmod-r8169 kmod-nvme kmod-ata-ahci-dwc
endef
TARGET_DEVICES += lyt_t68m


# RK3576

define Device/Legacy/rk3576
$(call Device/Legacy,$(1))
  SOC := rk3576
  UBOOT_DEVICE_NAME := easepi-rk3576
  BOOT_SCRIPT := rk3576
  DEVICE_PACKAGES := kmod-rga3 kmod-rk_vcodec kmod-rkgpu-bifrost kmod-rknpu kmod-iio-rockchip-saradc
endef

define Device/friendlyarm_nanopi-r76s
$(call Device/Legacy/rk3576,$(1))
  DEVICE_VENDOR := FriendlyARM
  DEVICE_MODEL := NanoPi R76S
  DEVICE_PACKAGES += kmod-r8169 kmod-hwmon-pwmfan kmod-thermal
endef
TARGET_DEVICES += friendlyarm_nanopi-r76s


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

define Device/hinlink_h88k
$(call Device/Legacy/rk3588,$(1))
  DEVICE_VENDOR := HINLINK
  DEVICE_MODEL := H88K
  SUPPORTED_DEVICES += hinlink,h88k-v2 hinlink,h88k-v3 hinlink,h88k
  DEVICE_DTS := rk3588/rk3588-h88k-v2 rk3588/rk3588-h88k-v3
  BOOT_SCRIPT := rk3588-hinlink
  DEVICE_PACKAGES += kmod-r8169 kmod-nvme
endef
TARGET_DEVICES += hinlink_h88k

define Device/lyt_t88m
$(call Device/Legacy/rk3588,$(1))
  DEVICE_VENDOR := LYT
  DEVICE_MODEL := T88M
  UBOOT_DEVICE_NAME := easepi-rk3588-uart2-115200
  BOOT_SCRIPT := rk3588-uart2-115200
  DEVICE_PACKAGES := kmod-r8169 kmod-nvme kmod-ata-ahci-dwc
endef
TARGET_DEVICES += lyt_t88m

define Device/radxa_e52c
$(call Device/Legacy/rk3588s,$(1))
  DEVICE_VENDOR := Radxa
  DEVICE_MODEL := E52C
  UBOOT_DEVICE_NAME := easepi-rk3588-lp4-1866
  DEVICE_PACKAGES += kmod-r8169
endef
TARGET_DEVICES += radxa_e52c

define Device/radxa_e54c
$(call Device/Legacy/rk3588s,$(1))
  DEVICE_VENDOR := Radxa
  DEVICE_MODEL := E54C
  DEVICE_PACKAGES += kmod-nvme kmod-ata-ahci-dwc kmod-hwmon-pwmfan kmod-thermal kmod-switch-rtl8367b swconfig
endef
TARGET_DEVICES += radxa_e54c

define Device/roceos_k60pro
$(call Device/Legacy/rk3588,$(1))
  DEVICE_VENDOR := ROCEOS
  DEVICE_MODEL := K60Pro
  UBOOT_DEVICE_NAME := easepi-rk3588-uart2-115200
  BOOT_SCRIPT := rk3588-uart2-115200
  DEVICE_PACKAGES := kmod-r8169 kmod-nvme kmod-ata-ahci-dwc kmod-hwmon-pwmfan kmod-thermal 
endef
TARGET_DEVICES += roceos_k60pro

define Device/xunlong_orangepi-5-plus
$(call Device/Legacy/rk3588,$(1))
  DEVICE_VENDOR := XunLong
  DEVICE_MODEL := Orange Pi 5 Plus
  DEVICE_PACKAGES += kmod-r8169 kmod-nvme kmod-ata-ahci-dwc kmod-hwmon-pwmfan kmod-thermal kmod-rkwifi-bcmdhd-pcie rkwifi-firmware-ap6275p
endef
TARGET_DEVICES += xunlong_orangepi-5-plus

define Device/cyber_cyber3588-aib
$(call Device/Legacy/rk3588,$(1))
  DEVICE_VENDOR := Cyber
  DEVICE_MODEL := Cyber3588-AIB
  DEVICE_PACKAGES += kmod-r8169 kmod-nvme kmod-ata-ahci-dwc kmod-hwmon-pwmfan kmod-thermal 
endef
TARGET_DEVICES += cyber_cyber3588-aib