define Build/rescue-firmwares
	rm -rf "$@.rescue"
	mkdir -p "$@.rescue"
	( cd $(TARGET_DIR); find . | cpio -o -H newc -R root:root | gzip -9n >$@.rescue/rescue.cpio.gz )
	$(CP) $(IMAGE_KERNEL) "$@.rescue/rescue.Image"
	$(CP) $(KDIR)/image-$(firstword $(DEVICE_DTS)).dtb "$@.rescue/rescue.dtb"
	$(CP) ./blob/bluecore.audio.slim "$@.rescue/rescue.audio"

	rm -f "$@"
	cd "$@.rescue"; $(TAR) -czf "$@" `ls`
endef

define Device/rescue
	DEVICE_TITLE := Rescue Mode
	DEVICE_DTS := rtd1296-rescue
	HWSETTING := RTD1295_hwsetting_BOOT_2DDR4_8Gb_s2133
	ARTIFACTS := firmware.tar.gz
	ARTIFACT/firmware.tar.gz := rescue-firmwares
endef
TARGET_DEVICES += rescue