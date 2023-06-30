ARCH:=aarch64
CPU_TYPE:=cortex-a53
BOARDNAME:=RK3568/RK3588 boards (64 bit)

DEFAULT_PACKAGES+=kmod-r8125 ethtool

define Target/Description
	Build firmware image for Rockchip RK3568/RK3588 devices.
	This firmware features a 64 bit kernel.
endef
