#!/bin/bash
#
# Copyright (c) 2020 Rockchip Electronics Co., Ltd
#
# SPDX-License-Identifier: GPL-2.0
#

srctree=$PWD

function help()
{
	echo
	echo "Description:"
	echo "    Process args for all rockchip fit generator script, and providing variables for it's caller"
	echo
	echo "Usage:"
	echo "    $0 [args]"
	echo
	echo "[args]:"
	echo "--------------------------------------------------------------------------------------------"
	echo "    arg                 type       output variable       description"
	echo "--------------------------------------------------------------------------------------------"
	echo "    -c [comp]     ==>   <string>   COMPRESSION           set compression: \"none\", \"gzip\""
	echo "    -m0 [offset]  ==>   <hex>      MCU0_LOAD_ADDR        set mcu0.bin load address"
	echo "    -m1 [offset]  ==>   <hex>      MCU1_LOAD_ADDR        set mcu1.bin load address"
	echo "    -m2 [offset]  ==>   <hex>      MCU2_LOAD_ADDR        set mcu2.bin load address"
	echo "    -m3 [offset]  ==>   <hex>      MCU3_LOAD_ADDR        set mcu3.bin load address"
	echo "    -m4 [offset]  ==>   <hex>      MCU4_LOAD_ADDR        set mcu4.bin load address"
	echo "    -l0 [offset]  ==>   <hex>      LOAD0_LOAD_ADDR       set load0.bin load address"
	echo "    -l1 [offset]  ==>   <hex>      LOAD1_LOAD_ADDR       set load1.bin load address"
	echo "    -l2 [offset]  ==>   <hex>      LOAD2_LOAD_ADDR       set load2.bin load address"
	echo "    -l3 [offset]  ==>   <hex>      LOAD3_LOAD_ADDR       set load3.bin load address"
	echo "    -l4 [offset]  ==>   <hex>      LOAD4_LOAD_ADDR       set load4.bin load address"
	echo "    -t [offset]   ==>   <hex>      TEE_LOAD_ADDR         set tee.bin load address"
	echo "    (none)        ==>   <hex>      UBOOT_LOAD_ADDR       set U-Boot load address"
	echo "    (none)        ==>   <string>   ARCH                  set arch: \"arm\", \"arm64\""
	echo
}

if [ $# -eq 1 ]; then
	# default
	TEE_OFFSET=0x08400000
else
	# args
	while [ $# -gt 0 ]; do
		case $1 in
			--help|-help|help|--h|-h)
				help
				exit
				;;
			-c)
				COMPRESSION=$2
				shift 2
				;;
			-m0)
				MCU0_OFFSET=$2
				shift 2
				;;
			-m1)
				MCU1_OFFSET=$2
				shift 2
				;;
			-m2)
				MCU2_OFFSET=$2
				shift 2
				;;
			-m3)
				MCU3_OFFSET=$2
				shift 2
				;;
			-m4)
				MCU4_OFFSET=$2
				shift 2
				;;
			-l0)
				LOAD0_OFFSET=$2
				shift 2
				;;
			-l1)
				LOAD1_OFFSET=$2
				shift 2
				;;
			-l2)
				LOAD2_OFFSET=$2
				shift 2
				;;
			-l3)
				LOAD3_OFFSET=$2
				shift 2
				;;
			-l4)
				LOAD4_OFFSET=$2
				shift 2
				;;
			-t)
				TEE_OFFSET=$2
				shift 2
				;;
			*)
				echo "Invalid arg: $1"
				help
				exit 1
				;;
		esac
	done
fi

# Base
DARM_BASE=`sed -n "/CONFIG_SYS_SDRAM_BASE=/s/CONFIG_SYS_SDRAM_BASE=//p" ${srctree}/include/autoconf.mk|tr -d '\r'`
UBOOT_LOAD_ADDR=`sed -n "/CONFIG_SYS_TEXT_BASE=/s/CONFIG_SYS_TEXT_BASE=//p" ${srctree}/include/autoconf.mk|tr -d '\r'`

# ARCH
U_ARCH="arm"
if grep -q '^CONFIG_ARM64=y' .config ; then
	ARCH="arm64"
	U_ARCH="arm64"
elif grep -q '^CONFIG_ARM64_BOOT_AARCH32=y' .config ; then
	ARCH="arm64"
else
	ARCH="arm"
fi

# tee
if [ ! -z "${TEE_OFFSET}" ]; then
	TEE_LOAD_ADDR=$((DARM_BASE+TEE_OFFSET))
	TEE_LOAD_ADDR=$(echo "obase=16;${TEE_LOAD_ADDR}"|bc)
fi

# mcu
if [ ! -z "${MCU0_OFFSET}" ]; then
	MCU0_LOAD_ADDR=$((DARM_BASE+$MCU0_OFFSET))
	MCU0_LOAD_ADDR=$(echo "obase=16;${MCU0_LOAD_ADDR}"|bc)
fi
if [ ! -z "${MCU1_OFFSET}" ]; then
	MCU1_LOAD_ADDR=$((DARM_BASE+$MCU1_OFFSET))
	MCU1_LOAD_ADDR=$(echo "obase=16;${MCU1_LOAD_ADDR}"|bc)
fi
if [ ! -z "${MCU2_OFFSET}" ]; then
	MCU2_LOAD_ADDR=$((DARM_BASE+$MCU2_OFFSET))
	MCU2_LOAD_ADDR=$(echo "obase=16;${MCU2_LOAD_ADDR}"|bc)
fi
if [ ! -z "${MCU3_OFFSET}" ]; then
	MCU3_LOAD_ADDR=$((DARM_BASE+$MCU3_OFFSET))
	MCU3_LOAD_ADDR=$(echo "obase=16;${MCU3_LOAD_ADDR}"|bc)
fi
if [ ! -z "${MCU4_OFFSET}" ]; then
	MCU4_LOAD_ADDR=$((DARM_BASE+$MCU4_OFFSET))
	MCU4_LOAD_ADDR=$(echo "obase=16;${MCU4_LOAD_ADDR}"|bc)
fi

# loadables
if [ ! -z "${LOAD0_OFFSET}" ]; then
	LOAD0_LOAD_ADDR=$((DARM_BASE+$LOAD0_OFFSET))
	LOAD0_LOAD_ADDR=$(echo "obase=16;${LOAD0_LOAD_ADDR}"|bc)
fi
if [ ! -z "${LOAD1_OFFSET}" ]; then
	LOAD1_LOAD_ADDR=$((DARM_BASE+$LOAD1_OFFSET))
	LOAD1_LOAD_ADDR=$(echo "obase=16;${LOAD1_LOAD_ADDR}"|bc)
fi
if [ ! -z "${LOAD2_OFFSET}" ]; then
	LOAD2_LOAD_ADDR=$((DARM_BASE+$LOAD2_OFFSET))
	LOAD2_LOAD_ADDR=$(echo "obase=16;${LOAD2_LOAD_ADDR}"|bc)
fi
if [ ! -z "${LOAD3_OFFSET}" ]; then
	LOAD3_LOAD_ADDR=$((DARM_BASE+$LOAD3_OFFSET))
	LOAD3_LOAD_ADDR=$(echo "obase=16;${LOAD3_LOAD_ADDR}"|bc)
fi
if [ ! -z "${LOAD4_OFFSET}" ]; then
	LOAD4_LOAD_ADDR=$((DARM_BASE+$LOAD4_OFFSET))
	LOAD4_LOAD_ADDR=$(echo "obase=16;${LOAD4_LOAD_ADDR}"|bc)
fi
# echo " ## $DARM_BASE, $UBOOT_LOAD_ADDR, $TEE_LOAD_ADDR, $MCU0_LOAD_ADDR, $MCU1_LOAD_ADDR, $MCU2_LOAD_ADDR, $MCU3_LOAD_ADDR, $MCU4_LOAD_ADDR"
