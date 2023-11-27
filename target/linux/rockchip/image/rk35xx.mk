define Device/rk3568
  SOC := rk3568
  DEVICE_DTS_DIR := ../dts/rk3568
  DEVICE_DTS = $$(SOC)-$$(lastword $$(subst _, ,$$(DEVICE_NAME)))
  UBOOT_DEVICE_NAME := easepi-rk3568
  IMAGE/sysupgrade.img.gz := boot-common | boot-script rk3568 | pine64-img | gzip | append-metadata
endef

define Device/rk3568_combined
  IMAGE/combined.img.gz := boot-combined | boot-script rk3568-cb | pine64-img | gzip | append-metadata
  IMAGES := combined.img.gz
endef

define Device/rk3568_combined_fastrhino
  IMAGE/combined.img.gz := boot-combined | boot-script rk3568-fastrhino | pine64-img | gzip | append-metadata
  IMAGES := combined.img.gz
endef

define Device/rk3568_combined_friendlyelec
  IMAGE/combined.img.gz := boot-combined | boot-script rk3568-friendlyelec | pine64-img | gzip | append-metadata
  IMAGES := combined.img.gz
endef

define Device/rk3568_combined_hinlink
  IMAGE/combined.img.gz := boot-combined | boot-script rk3568-hinlink | pine64-img | gzip | append-metadata
  IMAGES := combined.img.gz
endef

define Device/rk3568_combined_nlnet
  IMAGE/combined.img.gz := boot-combined | boot-script rk3568-nlnet | pine64-img | gzip | append-metadata
  IMAGES := combined.img.gz
endef

define Device/rk3588
  SOC := rk3588
  DEVICE_DTS_DIR := ../dts/rk3588
  DEVICE_DTS = $$(SOC)-$$(lastword $$(subst _, ,$$(DEVICE_NAME)))
  UBOOT_DEVICE_NAME := easepi-rk3588
  IMAGE/sysupgrade.img.gz := boot-common | boot-script rk3588 | pine64-img | gzip | append-metadata
endef

define Device/rk3588_combined
  IMAGE/combined.img.gz := boot-combined | boot-script rk3588-cb | pine64-img | gzip | append-metadata
  IMAGES := combined.img.gz
endef

define Device/rk3588_combined_friendlyelec
  IMAGE/combined.img.gz := boot-combined | boot-script rk3588-friendlyelec | pine64-img | gzip | append-metadata
  IMAGES := combined.img.gz
endef

define Device/rk3588_combined_hinlink
  IMAGE/combined.img.gz := boot-combined | boot-script rk3588-hinlink | pine64-img | gzip | append-metadata
  IMAGES := combined.img.gz
endef

define Device/rk3528
  SOC := rk3528
  DEVICE_DTS_DIR := ../dts/rk3528
  DEVICE_DTS = $$(SOC)-$$(lastword $$(subst _, ,$$(DEVICE_NAME)))
  UBOOT_DEVICE_NAME := easepi-rk3528
  IMAGE/sysupgrade.img.gz := boot-common | boot-script rk3528 | pine64-img | gzip | append-metadata
endef

define Device/rk3566
$(call Device/rk3568)
  SOC := rk3566
endef

define Device/fastrhino_common
$(call Device/rk3568)
  DEVICE_VENDOR := FastRhino
  DEVICE_PACKAGES := kmod-r8125
endef

define Device/fastrhino_r66s
$(call Device/fastrhino_common)
  DEVICE_MODEL := R66S
endef
TARGET_DEVICES += fastrhino_r66s

define Device/fastrhino_r68s
$(call Device/fastrhino_common)
  DEVICE_MODEL := R68S
endef
TARGET_DEVICES += fastrhino_r68s

define Device/fastrhino_r6xs
$(call Device/fastrhino_common)
$(call Device/rk3568_combined_fastrhino)
  DEVICE_MODEL := R68s/R66s combined
  SUPPORTED_DEVICES += fastrhino,r66s fastrhino,r68s
  DEVICE_DTS := rk3568-r66s rk3568-r68s
endef
TARGET_DEVICES += fastrhino_r6xs

define Device/hinlink_common
$(call Device/rk3568)
  DEVICE_VENDOR := HINLINK
  DEVICE_PACKAGES := kmod-r8125 kmod-nvme kmod-scsi-core
endef

define Device/hinlink_opc-h6xk
$(call Device/hinlink_common)
$(call Device/rk3568_combined_hinlink)
  DEVICE_MODEL := OPC-H69K/H68K/H66K combined
  SUPPORTED_DEVICES += hinlink,opc-h66k hinlink,opc-h68k hinlink,opc-h69k
  DEVICE_DTS := rk3568-opc-h66k rk3568-opc-h68k rk3568-opc-h69k
endef
TARGET_DEVICES += hinlink_opc-h6xk

define Device/hinlink_hnas
$(call Device/hinlink_common)
  DEVICE_MODEL := HNAS
  SUPPORTED_DEVICES += hinlink,hnas
endef
TARGET_DEVICES += hinlink_hnas

define Device/friendlyarm_nanopi-r5s
$(call Device/rk3568)
$(call Device/rk3568_combined_friendlyelec)
  DEVICE_VENDOR := FriendlyARM
  DEVICE_MODEL := NanoPi R5S/R5C combined
  SUPPORTED_DEVICES += friendlyelec,nanopi-r5s friendlyarm,nanopi-r5s friendlyelec,nanopi-r5c
  DEVICE_DTS := rk3568-nanopi-r5s rk3568-nanopi-r5c
  DEVICE_PACKAGES := kmod-r8125 kmod-nvme kmod-scsi-core kmod-hwmon-pwmfan kmod-thermal
endef
TARGET_DEVICES += friendlyarm_nanopi-r5s

define Device/firefly_station-p2
$(call Device/rk3568)
  DEVICE_VENDOR := Firefly
  DEVICE_MODEL := Station P2 / ROC PC
  DEVICE_DTS := rk3568-firefly-roc-pc
  SUPPORTED_DEVICES += firefly,rk3568-roc-pc firefly,station-p2
  DEVICE_PACKAGES := kmod-r8125 kmod-nvme kmod-scsi-core
endef
TARGET_DEVICES += firefly_station-p2

define Device/friendlyarm_nanopi-r6s
$(call Device/rk3588)
$(call Device/rk3588_combined_friendlyelec)
  DEVICE_VENDOR := FriendlyARM
  DEVICE_MODEL := NanoPi R6S/R6C
  SUPPORTED_DEVICES += friendlyelec,nanopi-r6s friendlyelec,nanopi-r6c
  DEVICE_DTS := rk3588-nanopi-r6s rk3588-nanopi-r6c
  DEVICE_PACKAGES := kmod-r8125 kmod-nvme kmod-thermal
endef
TARGET_DEVICES += friendlyarm_nanopi-r6s

define Device/lyt_t68m
$(call Device/rk3568)
  DEVICE_VENDOR := LYT
  DEVICE_MODEL := T68M
  SUPPORTED_DEVICES += lyt,t68m
  DEVICE_PACKAGES := kmod-r8125 kmod-nvme kmod-scsi-core
endef
TARGET_DEVICES += lyt_t68m

define Device/hinlink_rk3588
$(call Device/rk3588)
  DEVICE_VENDOR := HINLINK
  DEVICE_PACKAGES := kmod-r8125 kmod-nvme
endef

define Device/hinlink_h88k
$(call Device/hinlink_rk3588)
$(call Device/rk3588_combined_hinlink)
  DEVICE_MODEL := H88K
  SUPPORTED_DEVICES += hinlink,h88k-v2 hinlink,h88k-v3 hinlink,h88k
  DEVICE_DTS := rk3588-h88k-v2 rk3588-h88k-v3
endef
TARGET_DEVICES += hinlink_h88k

define Device/hinlink_rk3528
$(call Device/rk3528)
  DEVICE_VENDOR := HINLINK
  DEVICE_PACKAGES := kmod-r8168 kmod-thermal
endef

define Device/hlink_h28k
$(call Device/hinlink_rk3528)
  DEVICE_VENDOR := Hlink
  DEVICE_MODEL := H28K
  SUPPORTED_DEVICES += hlink,h28k
endef
TARGET_DEVICES += hlink_h28k

define Device/jsy_h1
$(call Device/rk3568)
  DEVICE_VENDOR := JSY
  DEVICE_MODEL := H1
  DEVICE_DTS := rk3568-jsy-h1
  SUPPORTED_DEVICES += jsy,h1
  DEVICE_PACKAGES := kmod-r8125 kmod-nvme kmod-scsi-core kmod-thermal kmod-leds-pwm
endef
TARGET_DEVICES += jsy_h1

define Device/yyy_h1
$(call Device/rk3568)
  DEVICE_VENDOR := YYY
  DEVICE_MODEL := H1
  DEVICE_DTS := rk3568-yyy-h1
  SUPPORTED_DEVICES += yyy,h1
  DEVICE_PACKAGES := kmod-r8125 kmod-nvme kmod-thermal kmod-hwmon-pwmfan kmod-backlight-gpio kmod-leds-pwm
endef
TARGET_DEVICES += yyy_h1

define Device/idiskk_h1
$(call Device/rk3568)
  DEVICE_VENDOR := iDiskk
  DEVICE_MODEL := H1
  DEVICE_DTS := rk3568-idiskk-h1
  SUPPORTED_DEVICES += idiskk,h1
  DEVICE_PACKAGES := kmod-scsi-core kmod-thermal kmod-hwmon-pwmfan kmod-backlight-gpio kmod-leds-pwm
endef
TARGET_DEVICES += idiskk_h1

define Device/ynn_ynnnas
  $(call Device/rk3566)
  DEVICE_VENDOR := YingNiuNiu
  DEVICE_MODEL := NAS
  SUPPORTED_DEVICES += ynn,nas
  DEVICE_PACKAGES := kmod-scsi-core
endef
TARGET_DEVICES += ynn_ynnnas

define Device/jp_tvbox
$(call Device/rk3566)
  DEVICE_VENDOR := jp
  DEVICE_MODEL := tvbox
  DEVICE_DTS := rk3566-jp-tvbox
  SUPPORTED_DEVICES += jp,tvbox
  DEVICE_PACKAGES := kmod-r8125 kmod-nvme kmod-thermal kmod-hwmon-pwmfan kmod-backlight-gpio kmod-leds-pwm
endef
TARGET_DEVICES += jp_tvbox

define Device/nlnet_xgp
$(call Device/rk3568)
$(call Device/rk3568_combined_nlnet)
  DEVICE_VENDOR := NLnet
  DEVICE_MODEL := XiGuaPi
  UBOOT_DEVICE_NAME := xgp-rk3568
  SUPPORTED_DEVICES += nlnet,xgp
  DEVICE_PACKAGES := kmod-nvme kmod-scsi-core kmod-hwmon-pwmfan kmod-thermal
  DEVICE_DTS := rk3568-xgp rk3568-xgp-v3
endef
TARGET_DEVICES += nlnet_xgp
