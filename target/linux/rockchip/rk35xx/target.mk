ARCH:=aarch64
CPU_TYPE:=cortex-a53
BOARDNAME:=RK35xx boards (64 bit)
FEATURES+=pwm

DEFAULT_PACKAGES+=kmod-r8125 ethtool

define Target/Description
	Build firmware image for Rockchip RK3528/RK3566/RK3568/RK3588 devices.
	This firmware features a 64 bit kernel.
endef
