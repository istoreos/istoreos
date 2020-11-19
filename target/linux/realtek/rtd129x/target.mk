
include $(TOPDIR)/rules.mk

ARCH:=aarch64
BOARDNAME:=RTD129x NAS
CPU_TYPE:=cortex-a53
FEATURES+=ext4
DEFAULT_PACKAGES+=e2fsprogs ethtool mkf2fs partx-utils

KERNELNAME:=Image dtbs

KERNEL_PATCHVER:=4.4

define Target/Description
	Build NAS firmware image for Realtek RTD129x SoC boards.
endef
