#!/bin/bash
#
# Copyright (c) 2021 Rockchip Electronics Co., Ltd
# SPDX-License-Identifier: GPL-2.0
#
# The script to generate splited image and update.hdr for TFTP image upgrade.
# 1. U-Boot have limited tftp download buffer, we have to split images into pieces for download
# 2. Use FIT mechanism to record image pieces information in update.hdr: order, hash, signature, etc.
# 3. The TFTP client download update.hdr and verify it (if need)
# 4. The TFTP client download => verify => flash image pieces accorrding to update.hdr.
#

set -e

HDR_SIZE=0x10000 # 64KB
ARG_VERSION=0
ARG_ROLLBACK_IDX=0
ARG_FORCE_UPDATE=0
SUFFIX=".part.img"
GPT="gpt_env.txt"

function help()
{
	echo
	echo "Usage:"
	echo "    $0 --image <dir> --size-MB <size> [optional args]"
	echo
	echo "    Mandory args:"
	echo "        --image <dir>:    directory of image to upgrade"
	echo "        --size-MB <size>: MB size unit for image to split into pieces. In Decimal integer: 1, 2, 3 ..."
	echo
	echo "    Optional args:"
	echo "        --sign:           sign firmware with RSA key-pair in \"./keys\" directory"
	echo "        --rollback-index <index>: rollback index in Decimal integer. It depends on \"--sign\""
	echo "        --force-update:   enable force upgrade"
	echo "        --config <file>:  config file"
	echo "        --version <ver>:  firmware version in Decimal integer"
	echo "        --clean:          clean generated files"
	echo
}

function check_decimal()
{
	if [ -z $1 ]; then
		help
		exit 1
	fi

	DECIMAL=`echo $1 |sed 's/[0-9]//g'`
	if [ ! -z ${DECIMAL} ]; then
		echo "ERROR: $1 is not decimal integer"
		help
		exit 1
	fi
}

function process_args()
{
	while [ $# -gt 0 ]; do
		case $1 in
			--help|-help|help|--h|-h)
				help
				exit
				;;
			--force-update)
				ARG_FORCE_UPDATE="1"
				shift 1
				;;
			--image)
				ARG_IMAGE_DIR=$2
				OUTPUT_DIR=${ARG_IMAGE_DIR}/output
				shift 2
				;;
			--config)
				ARG_CONFIG_FILE=$2
				if [ ! -f ${ARG_CONFIG_FILE} ]; then
					echo "ERROR: No ${ARG_CONFIG_FILE}"
					exit 1
				fi
				shift 2
				;;
			--rollback-index)
				ARG_ROLLBACK_IDX=$2
				check_decimal $2
				shift 2
				;;
			--sign)
				ARG_SIGN="y"
				shift 1
				;;
			--size-MB)
				ARG_IMG_MB=$2
				check_decimal $2
				shift 2
				;;
			--version)
				ARG_VERSION=$2
				check_decimal $2
				shift 2
				;;
			--clean)
				rm -f *${SUFFIX} *.itb *.its *.dtb *.dts data2sign* *.hdr *.hash orderlist.txt
				exit 0
				;;
			*)
				echo "Invalid arg: $1"
				help
				exit 1
				;;
		esac
	done

	if [ -z ${ARG_IMG_MB} ]; then
		help
		exit 1
	elif [ -z ${ARG_IMAGE_DIR} ]; then
		help
		exit 1
	elif [ ! -d ${ARG_IMAGE_DIR} ]; then
		echo "ERROR: No directory ${ARG_IMAGE_DIR}"
		exit 1
	fi

	if [ "${ARG_SIGN}" == "y" ]; then
		if [ ! -f keys/dev.key ]; then
			echo "ERROR: No keys/dev.key"
			exit 1
		elif [ ! -f keys/dev.crt ]; then
			echo "ERROR: No keys/dev.crt"
			exit 1
		fi
	else
		ARG_ROLLBACK_IDX=0
	fi
}

function split_image()
{
	rm -rf ${OUTPUT_DIR}

	if [ "${ARG_CONFIG_FILE}" ]; then
		cp ${ARG_CONFIG_FILE} orderlist.txt
	else
		ls ${ARG_IMAGE_DIR} > orderlist.txt
	fi

	SEQ=0
	cat orderlist.txt | while read IMAGE
	do
		if [ "${IMAGE}" == "${GPT}" ]; then
			continue;
		fi

		NAME=`echo ${IMAGE} | awk -F "." '{ print $1 }'`
		echo "=> split: ${IMAGE}"
		if [ ! -f ${ARG_IMAGE_DIR}/${IMAGE} ]; then
			echo "ERROR: No ${ARG_IMAGE_DIR}/${IMAGE}"
			exit 1
		fi

		if [ ${SEQ} -lt 10 ]; then
			SEQ_NAME="seq0${SEQ}-${NAME}"
		else
			SEQ_NAME="seq${SEQ}-${NAME}"
		fi

		split -b ${ARG_IMG_MB}M ${ARG_IMAGE_DIR}/${IMAGE} ${SEQ_NAME}- -d --additional-suffix=${SUFFIX}
		SEQ=`expr ${SEQ} + 1`
		ls ${SEQ_NAME}-*
	done
	echo
}

function gen_its()
{
cat > update.its << EOF
/*
 * Copyright (C) 2021 Rockchip Electronic Co.,Ltd
 *
 */

/dts-v1/;

/ {
	description = "FIT Image with ATF/OP-TEE/U-Boot";
	#address-cells = <1>;

	images {
EOF
	if [ -f ${ARG_IMAGE_DIR}/${GPT} ]; then
		cp ${ARG_IMAGE_DIR}/${GPT} ./
		echo "		${GPT} {
			data = /incbin/(\"./${GPT}\");
			hash {
				algo = \"sha256\";
			};
		};" >> update.its
	fi

	NUM=0
	MAX=`ls -l *part* | wc -l`
	for IMG in `ls -l *part* | awk '{ print $9 }'`
	do
		NAME=`echo ${IMG} | awk -F "." '{ print $1 }'`
			echo "		${NAME} {
			data = /incbin/(\"./${NAME}${SUFFIX}\");
			hash {
				algo = \"sha256\";
			};
		};" >> update.its

		NUM=`expr ${NUM} + 1`
		if [ ${NUM} -lt ${MAX} ]; then
			FIRMWARES=${FIRMWARES}"\"${NAME}\", "
		else
			FIRMWARES=${FIRMWARES}"\"${NAME}\""
			LAST_IMG=${NAME}
		fi
	done
cat >> update.its << EOF
	};

	configurations {
		default = "conf";
		conf {
			rollback-index = <${ARG_ROLLBACK_IDX}>;
			force-update = <${ARG_FORCE_UPDATE}>;
			image-size-MB = <${ARG_IMG_MB}>;
			firmware = ${FIRMWARES};
			signature {
				algo = "sha256,rsa2048";
				padding = "pss";
				key-name-hint = "dev";
				sign-images = "firmware";
			};
		};
	};
};
EOF
}

function gen_update_hdr()
{
	# generate itb
	if [ "${ARG_SIGN}" == "y" ]; then
		# create a temporary dtb to store public-key, just for mkimage work normal.
		SIGNED="signed"
		cp update.its key.its
		sed -i "/data =/d" key.its
		dtc -I dts -O dtb key.its -o key.dtb

		./mkimage -f update.its -k keys/ -K key.dtb -E -p ${HDR_SIZE} -r update.itb -v ${ARG_VERSION}
		./fit_check_sign -f update.itb -k key.dtb
	else
		SIGNED="no-signed"
		./mkimage -f update.its -E -p ${HDR_SIZE} update.itb -v ${ARG_VERSION}
	fi

	fdtdump update.itb > update.hdr.dts

	# validate update.hdr
	if [ "${ARG_SIGN}" == "y" ]; then
		NUM=`grep "${LAST_IMG}" update.hdr.dts  | wc -l`
		if [ ${NUM} -lt 3 ]; then
			echo "ERROR: mkimage can't makeup full \"hashed-nodes\" property list"
			exit 1
		fi
	fi

	# Remove binary from update.itb
	BYTE=`sed -n "/totalsize:/p" update.hdr.dts  | awk '{ print $4 }' | tr -d '(' | tr -d ')'`
	dd if=update.itb of=update.hdr bs=${BYTE} count=1

	# Append checksum
	openssl dgst -sha256 -binary -out update.hash update.hdr
	cat update.hash >> update.hdr

	rm -f *.itb *.its *.dtb *.dts data2sign* *.hash orderlist.txt
	mkdir -p ${OUTPUT_DIR}
	ls ${GPT} >/dev/null 2>&1 && mv ${GPT} ${OUTPUT_DIR}
	mv -f *${SUFFIX} update.hdr ${OUTPUT_DIR}

	echo
	echo "Success: [${SIGNED}] TFTP upgrade images(unit: ${ARG_IMG_MB}MB) are ready in directory: ${OUTPUT_DIR}."
	echo
}

###############################################################
process_args $*
split_image
gen_its
gen_update_hdr
