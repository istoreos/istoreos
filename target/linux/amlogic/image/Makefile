# SPDX-License-Identifier: GPL-2.0-only

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/image.mk

DEVICE_VARS += UBOOT_DEVICE_NAME

### Image scripts ###
define Build/boot-common
	# This creates a new folder copies the dtb (as amlogic.dtb) 
	# and the kernel image (as kernel.img)
	rm -fR $@.boot
	mkdir -p $@.boot

	$(CP) $(KDIR)/image-$(firstword $(DEVICE_DTS)).dtb $@.boot/amlogic.dtb
	$(CP) $(IMAGE_KERNEL) $@.boot/kernel.img
	$(CP) "$(STAGING_DIR_IMAGE)"/$(UBOOT_DEVICE_NAME)-u-boot-overlay.bin $@.boot/u-boot.emmc
endef

define Build/boot-combined
	# This creates a new folder copies the dtbs (as amlogic*.dtb) 
	# and the kernel image (as kernel.img)
	rm -fR $@.boot
	mkdir -p $@.boot

	i=0; \
	for dts in $(DEVICE_DTS); do \
		$(CP) $(KDIR)/image-$${dts}.dtb $@.boot/amlogic$$(perl -e 'printf "%b\n",'$$i).dtb; \
		let i+=1; \
	done
	$(CP) $(IMAGE_KERNEL) $@.boot/kernel.img
	$(CP) "$(STAGING_DIR_IMAGE)"/$(UBOOT_DEVICE_NAME)-u-boot-overlay.bin $@.boot/u-boot.emmc
endef

define Build/boot-script
	# Make an U-boot image and copy it to the boot partition
	mkimage -A arm -O linux -T script -C none -a 0 -e 0 -d aml_autoscript.cmd $@.boot/aml_autoscript
	mkimage -A arm -O linux -T script -C none -a 0 -e 0 -d emmc_autoscript.cmd $@.boot/emmc_autoscript
	mkimage -A arm -O linux -T script -C none -a 0 -e 0 -d s905_autoscript.cmd $@.boot/s905_autoscript
	mkimage -A arm -O linux -T script -C none -a 0 -e 0 -d $(if $(1),$(1),amlogic).bootscript $@.boot/boot.scr
endef

define Build/aml-img
	# Creates the final SD/eMMC images, 
	# combining boot partition, root partition as well as the u-boot bootloader

	./gen_amlogic_image.sh \
		$@ \
		$(CONFIG_TARGET_KERNEL_PARTSIZE) $@.boot \
		$(CONFIG_TARGET_ROOTFS_PARTSIZE) $(IMAGE_ROOTFS) \
		2048

	# Write vendor uboot to 0x200
	dd if="$(STAGING_DIR_IMAGE)"/$(UBOOT_DEVICE_NAME)-u-boot.bin of="$@" skip=1 seek=1 conv=notrunc
endef

### Devices ###
define Device/Default
  PROFILES := Default
  KERNEL := kernel-bin
  IMAGES := sysupgrade.img.gz
  DEVICE_DTS_DIR := $(DTS_DIR)/amlogic
  DEVICE_DTS = $$(SOC)-$(subst _,-,$(1))
endef

include $(SUBTARGET).mk

$(eval $(call BuildImage))
