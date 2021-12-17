
ifeq ($(SUBTARGET),rtd129x)

define Image/Prepare
	$(foreach dts,$(patsubst %.dts,%,$(notdir $(wildcard ../dts-uboot/*.dts))),
		$(call Image/BuildDTB,../dts-uboot/$(dts).dts,$(KDIR)/image-uboot-$(dts).dtb)
	)
endef

define Build/append-uboot-dtb
	cat $@ $(KDIR)/image-uboot-$(firstword $(UBOOT_DTS)).dtb > $@.tmp
	rm -f $@
	mv $@.tmp $@
endef

define Device/rtd129x
	FILESYSTEMS := squashfs
	IMAGES := install.img
	IMAGE/install.img := append-uboot | pad-to 8 | append-uboot-dtb | bootloader.tar | install.img
	IMAGE/install.img.zip := append-uboot | pad-to 8 | append-uboot-dtb | bootloader.tar | install.img | install.img.zip

	DEVICE_PACKAGES := rtk-init rtd129x_env blkid mount-utils e2fsprogs tune2fs resize2fs mkf2fs busybox openssl-util curl
# network device
	DEVICE_PACKAGES += kmod-ifb kmod-macvlan kmod-tun kmod-veth kmod-pppoe
# storage
	DEVICE_PACKAGES += kmod-usb-storage-uas kmod-ata-ahci ntfs-3g-utils
# ssl
	DEVICE_PACKAGES += libustream-openssl ca-bundle ca-certificates
	DEVICE_PACKAGES += luci-lib-ipkg ipset
	UBOOT_DTS := ars2
endef

define Device/ars2
	$(call Device/rtd129x)
	DEVICE_TITLE := ARS2 4GB
	DEVICE_DTS := ars2
	HWSETTING := RTD1296_hwsetting_BOOT_4DDR4_8Gb_s1866
# button
	DEVICE_PACKAGES += kmod-input-gpio-keys kmod-input-gpio-keys-polled kmod-gpio-button-hotplug
# fan
	DEVICE_PACKAGES += kmod-hwmon-gpiofan
# led
	DEVICE_PACKAGES += kmod-leds-gpio
	DEVICE_PACKAGES += luci-theme-material luci-app-arpbind luci-app-cifs-mount luci-app-cpufreq luci-app-diskman luci-app-dockerman docker luci-app-filetransfer luci-app-hd-idle luci-app-samba4 luci-app-sqm luci-app-ttyd
	DEVICE_PACKAGES += luci-i18n-base-zh-cn luci-i18n-firewall-zh-cn luci-i18n-ramfree-zh-cn luci-i18n-wol-zh-cn luci-i18n-upnp-zh-cn luci-i18n-ddns-zh-cn luci-i18n-vlmcsd-zh-cn luci-i18n-timecontrol-zh-cn
	DEVICE_PACKAGES += luci-i18n-arpbind-zh-cn luci-i18n-cifs-mount-zh-cn luci-i18n-cpufreq-zh-cn luci-i18n-dockerman-zh-cn luci-i18n-filetransfer-zh-cn luci-i18n-hd-idle-zh-cn luci-i18n-samba4-zh-cn luci-i18n-ttyd-zh-cn
endef
TARGET_DEVICES += ars2

define Device/bpi-w2
	$(call Device/rtd129x)
	DEVICE_TITLE := Bananapi W2
	UBOOT_DTS := w2
	DEVICE_DTS := rtd-1296-bananapi-w2-2GB-HDMI
	HWSETTING := RTD1295_hwsetting_BOOT_2DDR4_8Gb_s2133
# button
	DEVICE_PACKAGES += kmod-input-gpio-keys kmod-input-gpio-keys-polled kmod-gpio-button-hotplug
# fan
	DEVICE_PACKAGES += kmod-hwmon-gpiofan
endef
TARGET_DEVICES += bpi-w2

include rescue.mk

endif
