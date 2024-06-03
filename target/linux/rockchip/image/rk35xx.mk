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

define Device/armsom_sige1
$(call Device/rk3528)
  DEVICE_VENDOR := ArmSoM
  DEVICE_MODEL := sige1
  SUPPORTED_DEVICES += armsom,sige1 armsom,sige1-v1 armsom,sige1-v1.0
  DEVICE_PACKAGES := kmod-r8125 kmod-thermal
endef
TARGET_DEVICES += armsom_sige1

define Device/armsom_sige7-v1
$(call Device/rk3588)
  DEVICE_VENDOR := ArmSoM
  DEVICE_MODEL := sige7
  SUPPORTED_DEVICES += armsom,sige7-v1
  DEVICE_DTS := rk3588-sige7-v1-1 rk3588-sige7-v1
  DEVICE_PACKAGES := kmod-r8125 kmod-nvme kmod-hwmon-pwmfan kmod-thermal kmod-rkwifi-bcmdhd-pcie rkwifi-firmware-ap6275p
  IMAGE/sysupgrade.img.gz := boot-combined | boot-script rk3588 | pine64-img | gzip | append-metadata
endef
TARGET_DEVICES += armsom_sige7-v1

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
  DEVICE_PACKAGES := kmod-r8125 kmod-nvme kmod-scsi-core kmod-hwmon-pwmfan kmod-thermal
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

define Device/easepi_ars4
$(call Device/rk3568)
  DEVICE_VENDOR := EasePi
  DEVICE_MODEL := ARS4
  SUPPORTED_DEVICES += easepi,ars4
  DEVICE_PACKAGES := kmod-r8125 kmod-nvme kmod-scsi-core kmod-hwmon-pwmfan kmod-thermal
endef
TARGET_DEVICES += easepi_ars4

define Device/friendlyarm_nanopi-r5s
$(call Device/rk3568)
$(call Device/rk3568_combined_friendlyelec)
  DEVICE_VENDOR := FriendlyARM
  DEVICE_MODEL := NanoPi R5S/R5C combined
  SUPPORTED_DEVICES += friendlyelec,nanopi-r5s friendlyarm,nanopi-r5s friendlyelec,nanopi-r5c friendlyelec,nanopi-r5s-c1
  DEVICE_DTS := rk3568-nanopi-r5s rk3568-nanopi-r5c rk3568-nanopi-r5s-lts rk3568-nanopi-r5s-c1
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

define Device/rk3528_rtl8111h
$(call Device/rk3528)
  DEVICE_PACKAGES := kmod-r8168 kmod-thermal
endef

define Device/hlink_h28k
$(call Device/rk3528_rtl8111h)
  DEVICE_VENDOR := Hlink
  DEVICE_MODEL := H28K
  SUPPORTED_DEVICES += hlink,h28k
endef
TARGET_DEVICES += hlink_h28k

define Device/inspur_ihec301
$(call Device/rk3588)
  DEVICE_VENDOR := Inspur
  DEVICE_MODEL := IHEC301
  DEVICE_PACKAGES := kmod-scsi-core kmod-hwmon-pwmfan kmod-thermal kmod-switch-rtl8367b swconfig
endef
TARGET_DEVICES += inspur_ihec301

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
  DEVICE_VENDOR := JianPian
  DEVICE_MODEL := TV Box
  DEVICE_DTS := rk3566-jp-tvbox
  SUPPORTED_DEVICES += jp,tvbox
  DEVICE_PACKAGES := kmod-scsi-core
endef
TARGET_DEVICES += jp_tvbox

define Device/panther_x2
$(call Device/rk3566)
  DEVICE_VENDOR := Panther
  DEVICE_MODEL := X2
  DEVICE_DTS := rk3566-panther-x2
  SUPPORTED_DEVICES += panther,x2
endef
TARGET_DEVICES += panther_x2

define Device/le_hes30
$(call Device/rk3566)
  DEVICE_VENDOR := LE
  DEVICE_MODEL := HES30
  DEVICE_DTS := rk3566-hes30
  SUPPORTED_DEVICES += le,hes30
  DEVICE_PACKAGES := kmod-scsi-core kmod-thermal kmod-hwmon-pwmfan
endef
TARGET_DEVICES += le_hes30

define Device/mangopi_m28k
$(call Device/rk3528_rtl8111h)
  DEVICE_VENDOR := MangoPi
  DEVICE_MODEL := M28K
  SUPPORTED_DEVICES := mangopi,m28k
endef
TARGET_DEVICES += mangopi_m28k

define Device/radxa_e20c
$(call Device/rk3528_rtl8111h)
  DEVICE_VENDOR := Radxa
  DEVICE_MODEL := E20C
  SUPPORTED_DEVICES += radxa,e20c
endef
TARGET_DEVICES += radxa_e20c

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

define Device/rk_demo-rtl8367s
$(call Device/rk3568)
  DEVICE_VENDOR := Rockchip
  DEVICE_MODEL := Demo RTL8367S
  DEVICE_PACKAGES := kmod-scsi-core kmod-hwmon-pwmfan kmod-thermal kmod-switch-rtl8367b swconfig
endef
# TARGET_DEVICES += rk_demo-rtl8367s


define Device/rk3308
  SOC := rk3308
  DEVICE_DTS_DIR := ../dts/rk3308
  DEVICE_DTS = $$(SOC)-$$(lastword $$(subst _, ,$$(DEVICE_NAME)))
  UBOOT_DEVICE_NAME := easepi-rk3308
  IMAGE/sysupgrade.img.gz := boot-common | boot-script rk3308-uart2 | pine64-img | gzip | append-metadata
endef

define Device/armsom_p2-pro
$(call Device/rk3308)
  DEVICE_VENDOR := ArmSoM
  DEVICE_MODEL := P2 Pro
  SUPPORTED_DEVICES := armsom,p2pro armsom,p2-pro
  DEVICE_PACKAGES := kmod-usb-net-rtl8152 ethtool kmod-rkwifi-bcmdhd rkwifi-firmware-ap6256 kmod-sound-soc-rk3308
endef
# TARGET_DEVICES += armsom_p2-pro
