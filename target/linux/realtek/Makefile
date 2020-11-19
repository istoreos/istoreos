# Copyright (C) 2018 OpenWrt.org
#
include $(TOPDIR)/rules.mk

ARCH:=aarch64
BOARD:=realtek
BOARDNAME:=Realtek SoC
SUBTARGETS:=rtd129x
FEATURES:=fpu usb pci pcie gpio nand squashfs ramdisk
MAINTAINER:=william.lee <william.lee@realtek.com>

KERNEL_PATCHVER:=4.9

define Target/Description
	Build firmware images for RTD1xxx based boards.
endef

include $(INCLUDE_DIR)/target.mk
DEFAULT_PACKAGES += e2fsprogs 


$(eval $(call BuildTarget))
