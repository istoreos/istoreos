ARCH:=aarch64
CPU_TYPE:=cortex-a53
SUBTARGET:=rk3568
BOARDNAME:=RK3568 boards (64 bit)

KERNEL_PATCHVER=4.19

DEFAULT_PACKAGES+=kmod-r8125

define Target/Description
	Build firmware image for Rockchip RK3568 devices.
	This firmware features a 64 bit kernel.
endef
