#!/bin/bash
#
# Copyright (c) 2020 Fuzhou Rockchip Electronics Co., Ltd
#
# SPDX-License-Identifier: GPL-2.0
#
set -e

# [Keys]
#	mkdir -p keys
#	openssl genpkey -algorithm RSA -out keys/dev.key -pkeyopt rsa_keygen_bits:2048 -pkeyopt rsa_keygen_pubexp:65537
#	openssl req -batch -new -x509 -key keys/dev.key -out keys/dev.crt
#	openssl rsa -in keys/dev.key -pubout -out keys/dev.pubkey
# [Sign]
#	openssl dgst -sha256 -sign keys/dev.key -sigopt rsa_padding_mode:pss -out sha256-rsa2048.sign fit/boot.data2sign

IMG_UBOOT="uboot.img"
IMG_BOOT="boot.img"

function usage_resign()
{
	echo
	echo "usage:"
	echo "    $0 -f [itb] -s [sig]"
	echo
}

function fit_resign()
{
	if [ $# -ne 4 ]; then
		usage_resign
		exit 1
	fi

	while [ $# -gt 0 ]; do
		case $1 in
			-f)
				ITB=$2
				shift 2
				;;
			-s)
				SIG=$2
				shift 2
				;;
			*)
				usage_resign
				exit 1
				;;
		esac
	done

	if [ ! -f ${ITB} ]; then
		echo "ERROR: No ${ITB}"
		exit 1
	elif ! file ${ITB} | grep 'Device Tree Blob' ; then
		echo "ERROR: ${ITB} is not FIT image"
		exit 1
	elif [ ! -f ${SIG} ]; then
		echo "ERROR: No ${SIG}"
		exit 1
	fi

	copies=`strings ${ITB} | grep "signer-version"  | wc -l`
	if [ ${copies} -ne 1 ]; then
		echo "ERROR: ${ITB} seems not a itb but a image, ${copies}"
		exit 1
	fi

	SIG_SZ=`ls -l ${SIG} | awk '{ print $5 }'`
	LEN=`./tools/fit_info -f ${ITB} -n /configurations/conf/signature -p value | sed -n "/LEN:/p" | awk '{ print $2 }'`
	OFF=`./tools/fit_info -f ${ITB} -n /configurations/conf/signature -p value | sed -n "/OFF:/p" | awk '{ print $2 }'`
	END=`./tools/fit_info -f ${ITB} -n /configurations/conf/signature -p value | sed -n "/END:/p" | awk '{ print $2 }'`

	if [ -z ${LEN} ]; then
		echo "ERROR: No signature in ${ITB}"
		exit 1
		strings uboot.img | grep "rollback-index" | wc -l
	elif [ "${SIG_SZ}" -ne "${LEN}" ]; then
		echo "ERROR: ${SIG} size ${SIG_SZ} != ${ITB} Signature size ${LEN}"
		exit 1
	fi

	dd if=${ITB} of=${ITB}.half1 count=1 bs=${OFF}
	dd if=${ITB} of=${ITB}.half2 skip=1 ibs=${END}

	ITB_RESIGN="${ITB}.resign"
	cat ${ITB}.half1  >  ${ITB_RESIGN}
	cat ${SIG}        >> ${ITB_RESIGN}
	cat ${ITB}.half2  >> ${ITB_RESIGN}
	echo

	if fdtget -l ${ITB_RESIGN} /images/uboot >/dev/null 2>&1 ; then
		ITB_MAX_NUM=`sed -n "/SPL_FIT_IMAGE_MULTIPLE/p" .config | awk -F "=" '{ print $2 }'`
		ITB_MAX_KB=`sed  -n "/SPL_FIT_IMAGE_KB/p" .config | awk -F "=" '{ print $2 }'`
		ITB_MAX_BS=$((ITB_MAX_KB*1024))
		ITB_BS=`ls -l ${ITB} | awk '{ print $5 }'`
		if [ ${ITB_BS} -gt ${ITB_MAX_BS} ]; then
			echo "ERROR: pack ${IMG_UBOOT} failed! ${ITB} actual: ${ITB_BS} bytes, max limit: ${ITB_MAX_BS} bytes"
			exit 1
		fi

		rm -f ${IMG_UBOOT}
		for ((i = 0; i < ${ITB_MAX_NUM}; i++));
		do
			cat ${ITB_RESIGN} >> ${IMG_UBOOT}
			truncate -s %${ITB_MAX_KB}K ${IMG_UBOOT}
		done
		echo "Image(re-signed):  ${IMG_UBOOT} is ready"
	else
		cp ${ITB_RESIGN} ${IMG_BOOT}
		echo "Image(re-signed):  ${IMG_BOOT} is ready"
	fi

	rm -f ${ITB}.half1 ${ITB}.half2 ${ITB_RESIGN}
}

fit_resign $*

