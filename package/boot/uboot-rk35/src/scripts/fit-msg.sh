#!/bin/bash
#
# Copyright (c) 2020 Rockchip Electronics Co., Ltd
#
# SPDX-License-Identifier: GPL-2.0
#
set -e

function usage()
{
	echo
	echo "usage:"
	echo "    $0 -f [uboot.img]"
	echo
}

function args_process()
{
	if [ $# -ne 2 ]; then
		usage
		exit 1
	fi

	while [ $# -gt 0 ]; do
		case $1 in
			-f)
				IMG=$2
				shift 2
				;;
			*)
				usage
				exit 1
				;;
		esac
	done

	if [ ! -f ${IMG} ]; then
		echo "ERROR: No ${IMG}"
		exit 1
	elif ! file ${IMG} | grep 'Device Tree Blob' ; then
		echo "ERROR: ${IMG} is not FIT image"
		exit 1
	fi
}

function image_msg()
{
	echo "[Commit version]:"
	strings ${IMG} | grep '\-g[0-9,a-f][0-9,a-f][0-9,a-f][0-9,a-f][0-9,a-f][0-9,a-f][0-9,a-f]' | sort --uniq
	strings ${IMG} | grep 'Built :' | sort --uniq
}

args_process $*
image_msg
