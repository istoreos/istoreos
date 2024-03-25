# SPDX-License-Identifier: GPL-2.0-only

define Device/phicomm_n1
  DEVICE_VENDOR := Phicomm
  DEVICE_MODEL := N1
  SOC := meson-gxl-s905d
  UBOOT_DEVICE_NAME := phicomm-n1
  IMAGE/sysupgrade.img.gz := boot-common | boot-script | aml-img | gzip | append-metadata
  DEVICE_PACKAGES := kmod-usb-net-rtl8152 ethtool
  DEVICE_PACKAGES += kmod-brcmfmac brcmfmac-firmware-43455-sdio-phicomm-n1
endef
TARGET_DEVICES += phicomm_n1
