#!/bin/sh
#
# Copyright (c) 2019 Fuzhou Rockchip Electronics Co., Ltd
#
# SPDX-License-Identifier: GPL-2.0
#

RSCE_OLD=$1
RSCE_NEW=resource.img

BOOT_OLD=$1
BOOT_NEW=boot.img

TOOL=../rkbin/tools/resource_tool
IMAGES=./tools/images/
TMP_DIR=.resource_tmp
TMP_DIR2=.boot_tmp

usage()
{
	echo "Usage:"
	echo "  ./pack_resource <input resource.img>"
}

prepare()
{
	echo
	if [ "${RSCE_OLD}" = '--help' -o "${RSCE_OLD}" = '-h' -o "${RSCE_OLD}" = '--h' ]; then
		usage
		exit 0
	elif [ ! -d "${IMAGES}" ];then
		echo "ERROR: No ${RESOURCE}"
		exit 1
	elif [ -z "${RSCE_OLD}" ];then
		usage
		exit 1
	elif [ ! -f "${RSCE_OLD}" ];then
		echo "ERROR: No ${RSCE_OLD}"
		exit 1
	fi
}

append_images_to_resource()
{
	rm -rf ${TMP_DIR} && mkdir -p ${TMP_DIR}

	echo "Pack ${IMAGES} & ${RSCE_OLD} to ${RSCE_NEW} ..."
	if [ -f "${RSCE_OLD}" ];then
		echo "Unpacking old image(${RSCE_OLD}):"
		${TOOL} --unpack --verbose --image=${RSCE_OLD} ${TMP_DIR} 2>&1 | grep entry | sed "s/^.*://" | xargs echo
	fi

	if [ -d "${IMAGES}" ];then
		cp -r ${IMAGES}/* ${TMP_DIR}
	else
		cp -r ${IMAGES}   ${TMP_DIR}
	fi
	${TOOL} --pack --root=${TMP_DIR} --image=${RSCE_NEW} `find ${TMP_DIR} -type f|sort`

	echo
	echo "Packed resources:"
	${TOOL} --unpack --verbose --image=${RSCE_NEW} ${TMP_DIR} 2>&1 | grep entry | sed "s/^.*://" | xargs echo

	rm -rf ${TMP_DIR}
	echo
	echo "./resource.img with battery images is ready"
}

append_images_to_android_img()
{
	./scripts/unpack_bootimg --boot_img ${BOOT_OLD} --out ${TMP_DIR2}/
	RSCE_OLD="${TMP_DIR2}/second"
	append_images_to_resource
	./scripts/repack-bootimg --boot_img ${BOOT_OLD} --second ${RSCE_NEW} -o ${BOOT_NEW}
	rm -rf ${TMP_DIR2}
}

append_images_to_fit_img()
{
	./scripts/fit-unpack.sh -f ${BOOT_OLD} -o ${TMP_DIR2}/
	RSCE_OLD="${TMP_DIR2}/resource"
	append_images_to_resource
	rm -rf ${TMP_DIR2}/*
	mv ${RSCE_NEW} ${TMP_DIR2}/resource
	 ./scripts/fit-repack.sh -f ${BOOT_OLD} -d ${TMP_DIR2}
	rm -rf ${TMP_DIR2}
}

prepare
if file ${RSCE_OLD} | grep 'Android bootimg' >/dev/null 2>&1 ; then
	append_images_to_android_img
elif file ${RSCE_OLD} | grep 'Device Tree Blob' >/dev/null 2>&1 ; then
	append_images_to_fit_img
elif strings ${RSCE_OLD} | grep "RSCE" >/dev/null 2>&1 ; then
	append_images_to_resource
fi

