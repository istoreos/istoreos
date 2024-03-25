# SPDX-License-Identifier: GPL-2.0-only
#
# Copyright (C) 2024 jjm2473 <jjm2473@gmail.com>

include $(TOPDIR)/rules.mk

BOARD:=amlogic
BOARDNAME:=Amlogic
FEATURES:=ext4 audio usb usbgadget display gpio fpu pci pcie squashfs
SUBTARGETS:=meson

KERNEL_PATCHVER:=5.10

include $(INCLUDE_DIR)/target.mk

DEFAULT_PACKAGES += mkf2fs e2fsprogs

$(eval $(call BuildTarget))
