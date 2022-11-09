#!/bin/bash
#
# Copyright (c) 2020 Rockchip Electronics Co., Ltd
#
# SPDX-License-Identifier: GPL-2.0
#
set -e

MKIMAGE="./tools/mkimage"
UNPACK="./scripts/fit-unpack.sh"
OFFS="0xa00"
OUT="out/repack"
ITB="out/repack/image.itb"
ITS="out/repack/image.its"

function usage_repack()
{
	echo
	echo "usage:"
	echo "    $0 -f [image] -d [data dir]"
	echo
}

function fit_repack()
{
	if [ $# -ne 4 ]; then
		usage_repack
		exit 1
	fi

	while [ $# -gt 0 ]; do
		case $1 in
			-f)
				IMAGE=$2
				shift 2
				;;
			-d)
				DATA=$2
				shift 2
				;;
			*)
				usage_repack
				exit 1
				;;
		esac
	done

	if [ ! -f ${IMAGE} ]; then
		echo "ERROR: No ${IMAGE}"
		exit 1
	elif ! file ${IMAGE} | grep 'Device Tree Blob' ; then
		echo "ERROR: ${IMAGE} is not FIT image"
		exit 1
	elif [ ! -d ${DATA} ]; then
		echo "ERROR: No input directory ${DATA}"
		exit 1
	fi

	COPIES=`strings ${IMAGE} | grep "rollback-index"  | wc -l`
	if [ ${COPIES} -eq 0 ]; then
		echo "ERROR: Invalid fit image"
		exit 1
	fi

	IMG_BS=`ls -l ${IMAGE} | awk '{ print $5 }'`
	ITB_KB=`expr ${IMG_BS} / ${COPIES} / 1024`

	rm -rf ${OUT} && mkdir -p ${OUT}
	${UNPACK} -f ${IMAGE} -o ${OUT}/
	find ${DATA}/ -maxdepth 1 -type f | xargs cp -t ${OUT}/

	if fdtget -l ${IMAGE} /images/uboot >/dev/null 2>&1 ; then
		rm -f ${IMAGE}
		${MKIMAGE} -f ${ITS} -E -p ${OFFS} ${ITB}
		for ((i = 0; i < ${COPIES}; i++));
		do
			cat ${ITB} >> ${IMAGE}
			truncate -s %${ITB_KB}K ${IMAGE}
		done
	else
		${MKIMAGE} -f ${ITS} -E -p ${OFFS} ${IMAGE}
	fi

	rm ${OUT} -rf
	echo
	echo "Image(repack):  ${IMAGE} is ready"
}

fit_repack $*

