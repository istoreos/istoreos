#!/bin/bash
#
# Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
#
# SPDX-License-Identifier: GPL-2.0
#

case $1 in
--help|-help|help|--h|-h|debug|'')
	echo
	echo "    0. set CONFIG_BOOTDELAY=0"
	echo "    1. lib/initcall.c debug() -> printf()"
	echo "    2. common/board_r.c and common/board_f.c debug() -> printf()"
	echo "    3. global #define DEBUG"
	echo "    4. enable CONFIG_ROCKCHIP_DEBUGGER"
	echo "    5. set CONFIG_BOOTDELAY=5"
	echo "    6. enable CONFIG_BOOTSTAGE_PRINTF_TIMESTAMP"
	echo "    7. armv7 start.S: print entry warning"
	echo "    8. armv8 start.S: print entry warning"
	echo "    9. enable CONFIG_ROCKCHIP_CRASH_DUMP"
	echo "   10. enable CONFIG_ROCKCHIP_CRC"
	echo "   11. firmware bootflow debug() -> printf()"
	echo "   12. bootstage timing report"
	echo "   13. starting kernel halt dump"
	echo
	echo "Enabled in .config: "
	grep '^CONFIG_ROCKCHIP_DEBUGGER=y' .config > /dev/null \
	&& echo "    CONFIG_ROCKCHIP_DEBUGGER"
	grep '^CONFIG_ROCKCHIP_CRC=y' .config > /dev/null \
	&& echo "    CONFIG_ROCKCHIP_CRC"
	grep '^CONFIG_BOOTSTAGE_PRINTF_TIMESTAMP=y' .config > /dev/null \
	&& echo "    CONFIG_BOOTSTAGE_PRINTF_TIMESTAMP"
	grep '^CONFIG_ROCKCHIP_CRASH_DUMP=y' .config > /dev/null \
	&& echo "    CONFIG_ROCKCHIP_CRASH_DUMP"
	;;
0)
	sed -i 's/^CONFIG_BOOTDELAY=5/CONFIG_BOOTDELAY=0/g' .config
	echo "DEBUG [0]: CONFIG_BOOTDELAY is 0s"
	;;
1)
	sed -i 's/\<debug\>/printf/g' lib/initcall.c
	sed -i 's/ifdef DEBUG/if 1/g' lib/initcall.c
	echo "DEBUG [1]: lib/initcall.c debug() -> printf()"
	;;
2)
	sed -i 's/\<debug\>/printf/g' ./common/board_f.c
	sed -i 's/\<debug\>/printf/g' ./common/board_r.c
	echo "DEBUG [2]: common/board_r.c and common/board_f.c debug() -> printf()"
	;;
3)
	sed -i '$i \#define DEBUG\' include/configs/rockchip-common.h
	echo "DEBUG [3]: global #define DEBUG"
	;;
4)
	sed -i 's/\# CONFIG_ROCKCHIP_DEBUGGER is not set/CONFIG_ROCKCHIP_DEBUGGER=y/g' .config
	echo "DEBUG [4]: CONFIG_ROCKCHIP_DEBUGGER is enabled"
	;;
5)
	sed -i 's/^CONFIG_BOOTDELAY=0/CONFIG_BOOTDELAY=5/g' .config
	echo "DEBUG [5]: CONFIG_BOOTDELAY is 5s"
	;;
6)
	sed -i 's/\# CONFIG_BOOTSTAGE_PRINTF_TIMESTAMP is not set/CONFIG_BOOTSTAGE_PRINTF_TIMESTAMP=y/g' .config
	echo "DEBUG [6]: CONFIG_BOOTSTAGE_PRINTF_TIMESTAMP is enabled"
	;;
7)
	sed -i '/save_boot_params_ret:/a\ldr r0, =CONFIG_DEBUG_UART_BASE\nmov r1, #100\nloop:\nmov r2, #0x55\nstr r2, [r0]\nsub r1, r1, #1\ncmp r1, #0\nbne loop\ndsb' \
	./arch/arm/cpu/armv7/start.S
	echo "DEBUG [7]: armv7 start.S entry warning 'UUUU...'"
	;;
8)
	sed -i '/save_boot_params_ret:/a\ldr x0, =CONFIG_DEBUG_UART_BASE\nmov x1, #100\nloop:\nmov x2, #0x55\nstr x2, [x0]\nsub x1, x1, #1\ncmp x1, #0\nb.ne loop\ndsb sy' \
	./arch/arm/cpu/armv8/start.S
	echo "DEBUG [8]: armv8 start.S entry warning 'UUUU...'"
	;;
9)
	sed -i 's/\# CONFIG_ROCKCHIP_CRASH_DUMP is not set/CONFIG_ROCKCHIP_CRASH_DUMP=y/g' .config
	echo "DEBUG [9]: CONFIG_ROCKCHIP_CRASH_DUMP is enabled"
	;;
10)
	sed -i 's/\# CONFIG_ROCKCHIP_CRC is not set/CONFIG_ROCKCHIP_CRC=y/g' .config
	echo "DEBUG [10]: CONFIG_ROCKCHIP_CRC is enabled"
	;;
11)
	sed -i 's/\<debug\>/printf/g' common/fdt_support.c
	sed -i 's/\<debug\>/printf/g' common/image-fdt.c
	sed -i 's/\<debug\>/printf/g' common/image.c
	sed -i 's/\<debug\>/printf/g' arch/arm/lib/bootm.c
	sed -i 's/\<debug\>/printf/g' common/bootm.c
	sed -i 's/\<debug\>/printf/g' common/image.c
	sed -i 's/\<debug\>/printf/g' common/image-android.c
	sed -i 's/\<debug\>/printf/g' common/android_bootloader.c
	echo "DEBUG [11]: firmware bootflow debug() -> printf()"
	;;
12)
	sed -i '$a\CONFIG_BOOTSTAGE=y\' .config
	sed -i '$a\CONFIG_BOOTSTAGE_REPORT=y\' .config
	sed -i '$a\CONFIG_CMD_BOOTSTAGE=y\' .config
	echo "DEBUG [12]: bootstage timing report"
	;;
13)
	sed -i 's/\# CONFIG_ROCKCHIP_DEBUGGER is not set/CONFIG_ROCKCHIP_DEBUGGER=y/g' .config
	sed -i '/br x4/i\b .' arch/arm/cpu/armv8/transition.S
	sed -i 's/announce_and_cleanup(fake);/if (0)announce_and_cleanup(fake);/g' arch/arm/lib/bootm.c
	sed -i '/announce_and_cleanup(fake)/a\enable_interrupts()\;' arch/arm/lib/bootm.c
	sed -i '/kernel_entry(0, machid, r2)/i\printf("#### Jump to kernel!!")\;' arch/arm/lib/bootm.c
	sed -i '/kernel_entry(0, machid, r2)/i\__asm("b .")\;' arch/arm/lib/bootm.c
	sed -i 's/\<debug\>/printf/g' arch/arm/lib/bootm.c
	echo "DEBUG [13]: starting kernel halt dump"
	;;
*)
	echo "Unknown command: $1"
esac
echo
