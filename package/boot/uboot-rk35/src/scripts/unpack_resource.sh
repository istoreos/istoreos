#!/bin/sh
#
# Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
#
# SPDX-License-Identifier: GPL-2.0
#


IMAGE_FILE=$1
OUTPUT_DIR=$2
PACK_TOOL=../rkbin/tools/resource_tool

usage()
{
	echo "Usage:"
	echo "  $0 <resource.img> <output dir> "
}

prepare()
{
	echo
	if [ "$IMAGE_FILE" = '--help' -o "$IMAGE_FILE" = '-h' -o "$IMAGE_FILE" = '--h' ]; then
		usage
		exit 0
	elif [ ! -f "$PACK_TOOL" ];then
		echo "Can't find '../rkbin/' Responsity, please download it before pack image!"
		echo "How to obtain? 3 ways:"
		echo "	1. Login your Rockchip gerrit account: \"Projects\" -> \"List\" -> search \"rk/rkbin\" Responsity"
		echo "	2. Github Responsity: https://github.com/rockchip-linux/rkbin"
		echo "	3. Download full release SDK Responsity"
		exit 1
	elif [ -z "$IMAGE_FILE" ];then
		usage
		exit 1
	elif [ ! -f "$IMAGE_FILE" ];then
		echo "Can't find file: $IMAGE_FILE"
		usage
		exit 1
	elif [ -z "$OUTPUT_DIR" ];then
		echo "Missing: <output dir>"
		usage
		exit 1
	fi
}

append_resource()
{
	if [ ! -d $OUTPUT_DIR ]; then
		mkdir $OUTPUT_DIR
	fi
	echo "Unpack $IMAGE_FILE to $OUTPUT_DIR"
	$PACK_TOOL --unpack --verbose --image=$IMAGE_FILE $OUTPUT_DIR 2>&1|grep entry|sed "s/^.*://"|xargs echo
	echo
	echo "resource.img is unpacked successfully"
}

prepare
append_resource
