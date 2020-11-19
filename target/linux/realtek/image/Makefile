#
# Copyright (C) 2020 jjm2473 <jjm2473@gmail.com>
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/image.mk

define Build/mbr
	dd if=/dev/zero of=$@.mbr bs=512 count=1 >/dev/null
	ptgen -v -o $@.mbr -h 16 -s 63 -l 1024 -t 83 -p 131072@131072 -t 83 -p 7340032
endef

define Build/install.img
	rm -rf $@.install
	mkdir -p $@.install
	$(CP) ./config/config.txt $@.install/
	$(CP) ./blob/install_a $@.install/
	$(CP) $(IMAGE_KERNEL) $@.install/Image
	$(CP) $(KDIR)/image-$(firstword $(DEVICE_DTS)).dtb $@.install/rtd-129x.dtb
	$(CP) $(IMAGE_ROOTFS) $@.install/rootfs.bin

	$(TAR) -cf $@.install.img -C $@.install .
endef

define Build/install.img.zip
	rm -rf $@.release
	mkdir -p $@.release
	$(CP) ./blob/emmc.uImage $@.release/
	$(CP) ./blob/rescue.emmc.dtb $@.release/
	$(CP) ./blob/rescue.root.emmc.cpio.gz_pad.img $@.release/
	$(CP) $@.install.img $@.release/install.img

	zip -j -X -r $@ $@.release
endef

define Device/Default
	KERNEL := kernel-bin
	DTS_DIR := $(DTS_DIR)/realtek
	IMAGE_NAME = $$(IMAGE_PREFIX)-$$(1).$$(2)
	FILESYSTEMS := squashfs
	IMAGES := install.img.zip
	IMAGE/install.img.zip := install.img | install.img.zip
endef

ifeq ($(SUBTARGET),rtd129x)

define Device/rtd129x
	$(call Device/Default)
endef

define Device/bpi-w2
	$(call Device/rtd129x)
	DEVICE_TITLE := Bananapi W2
	DEVICE_DTS := rtd-1296-bananapi-w2-2GB-HDMI
endef
TARGET_DEVICES += bpi-w2

SQUASHFSCOMP := xz

endif

$(eval $(call BuildImage))