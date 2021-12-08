#
# Copyright (C) 2020 jjm2473 <jjm2473@gmail.com>
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

SQUASHFSCOMP := xz

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/image.mk

define Build/mbr
	dd if=/dev/zero of=$@.mbr bs=512 count=1 >/dev/null
	ptgen -v -o $@.mbr -h 16 -s 63 -l 1024 -t 83 -p 131072@131072 -t 83 -p 6291456
endef

define Build/bootloader.tar
	rm -rf "$@.bootloader" "$@.bootloader.tar"
	mkdir -p "$@.bootloader"
	rtd129x_encode_hwsetting "`pwd`/blob/bootloader/hw_settings/$(HWSETTING).config" "$@.bootloader.tar"
	rtd129x_bootcode_gen -h "$@.bootloader.tar" -u "$@" \
		-f "`pwd`/blob/bootloader/common/fsbl.bin" -d "$@.bootloader"

	cd "$@.bootloader"; $(TAR) -cf "$@.bootloader.tar" `ls`
endef

define Build/install.img
	rm -rf "$@.install"
	mkdir -p "$@.install/omv"
	$(CP) ./blob/install_a "$@.install/"
	$(CP) "$@.bootloader.tar" "$@.install/omv/bootloader.tar"
	$(CP) ./blob/bluecore.audio.slim "$@.install/bluecore.audio"
	$(CP) ./blob/rescue.emmc.dtb "$@.install/"
	$(CP) ./blob/rescue.root.emmc.cpio.gz_pad.img "$@.install/"
	$(CP) $(STAGING_DIR_IMAGE)/rescue.* "$@.install/"
	$(CP) $(IMAGE_KERNEL) "$@.install/Image"
	$(CP) $(KDIR)/image-$(firstword $(DEVICE_DTS)).dtb "$@.install/rtd-129x.dtb"
	$(CP) $(IMAGE_ROOTFS) "$@.install/rootfs.bin"

	echo "RESET000" | dd bs=512 count=1 conv=sync > "$@.install/etc.bin"

	rtd129x_img_gen ./config/emmc_8gb.json "$@.install"

	rm -f "$@"
	cd "$@.install"; $(TAR) -cf "$@" `ls`
endef

define Build/install.img.zip
	rm -rf "$@.release"
	mkdir -p "$@.release"
	$(CP) ./blob/emmc.uImage "$@.release/"
	$(CP) ./blob/rescue.emmc.dtb "$@.release/"
	$(CP) ./blob/rescue.root.emmc.cpio.gz_pad.img "$@.release/"
	$(CP) "$@" "$@.release/install.img"

	rm -f "$@"
	zip -j -X -r "$@" "$@.release"
endef

define Device/Default
	PROFILES := Default
	UBOOT_PATH := $(STAGING_DIR_IMAGE)/u-boot.bin
	KERNEL := kernel-bin
	DEVICE_DTS_DIR := ../dts-$(KERNEL_PATCHVER)
	IMAGE_NAME = $$(IMAGE_PREFIX)-$$(1).$$(2)
endef

DEVICE_VARS += HWSETTING UBOOT_DTS

include rtd129x.mk

$(eval $(call BuildImage))
