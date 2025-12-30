ARCH:=aarch64
CPU_TYPE:=cortex-a53
BOARDNAME:=Meson S905x boards (64 bit)

DEFAULT_PACKAGES+=ethtool parted kmod-fb

define Target/Description
	Build firmware image for Amlogic S905x devices.
	This firmware features a 64 bit kernel.
endef
