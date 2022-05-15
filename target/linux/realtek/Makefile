# Copyright (C) 2018 OpenWrt.org
#
include $(TOPDIR)/rules.mk

BOARD:=realtek
BOARDNAME:=Realtek SoC
SUBTARGETS:=rtd129x
FEATURES:=fpu usb pci pcie gpio squashfs dt
MAINTAINER:=william.lee <william.lee@realtek.com>

KERNEL_PATCHVER:=4.9

define Target/Description
	Build firmware images for RTD1xxx based boards.
endef

include $(INCLUDE_DIR)/target.mk
DEFAULT_PACKAGES += e2fsprogs 
DEFAULT_PACKAGES:= $(filter-out kmod-ipt-offload,$(DEFAULT_PACKAGES))
DEFAULT_PACKAGES:= $(filter-out libustream-wolfssl,$(DEFAULT_PACKAGES)) libustream-openssl

$(eval $(call BuildTarget))
