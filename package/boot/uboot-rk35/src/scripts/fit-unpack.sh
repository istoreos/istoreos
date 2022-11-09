#!/bin/bash
#
# Copyright (c) 2020 Fuzhou Rockchip Electronics Co., Ltd
#
# SPDX-License-Identifier: GPL-2.0
#
set -e

function usage()
{
	echo
	echo "usage:"
	echo "    $0 -f [fit/itb] -o [out]"
	echo
}

function args_process()
{
	if [ $# -ne 4 -a $# -ne 2 ]; then
		usage
		exit 1
	fi

	while [ $# -gt 0 ]; do
		case $1 in
			-f)
				ITB=$2
				shift 2
				;;
			-o)
				OUT=$2
				shift 2
				;;
			*)
				usage
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
	fi

	if [ -z ${OUT} ]; then
		OUT="out"
	fi
}

unpack_itb()
{
	mkdir -p ${OUT}
	echo "Unpack to directory ${OUT}:"

	for NAME in `fdtget -l ${ITB} /images`
	do
		# generate ITB
		NODE="/images/${NAME}"
		OFFS=`fdtget -ti ${ITB} ${NODE} data-position`
		SIZE=`fdtget -ti ${ITB} ${NODE} data-size`
		if [ -z ${OFFS} ]; then
			continue;
		fi

		if [ ${SIZE} -ne 0 ]; then
			dd if=${ITB} of=${OUT}/${NAME} bs=${SIZE} count=1 skip=${OFFS} iflag=skip_bytes >/dev/null 2>&1
		else
			touch ${OUT}/${NAME}
		fi

		# hash verify
		ALGO=`fdtget -ts ${ITB} ${NODE}/hash algo`
		if [ -z ${ALGO} ]; then
			printf "    %-20s: %d bytes" ${NAME} ${SIZE}
		else
			VALUE=`fdtget -tx ${ITB} ${NODE}/hash value`
			VALUE=`echo " "${VALUE} | sed "s/ / 0x/g"`
			CSUM=`"${ALGO}"sum ${OUT}/${NAME} | awk '{ print $1}'`

			HASH=""
			for((i=1;;i++));
			do
				HEX=`echo ${VALUE} | awk -v idx=$i '{ print $idx }'`
				if [ -z ${HEX} ]; then
					break;
				fi

				HEX=`printf "%08x" ${HEX}`
				HASH="${HASH}${HEX}"
			done

			printf "  %-20s: %d bytes... %s" ${NAME} ${SIZE} ${ALGO}
			if [ "${CSUM}" == "${HASH}" -o ${SIZE} -eq 0 ]; then
				echo "+"
			else
				echo "-"
			fi
		fi
	done
	echo
}

function gen_its()
{
	ITS=${OUT}/image.its
	TMP_ITB=${OUT}/image.tmp

	# add placeholder
	cp -a ${ITB} ${TMP_ITB}
	for NAME in `fdtget -l ${ITB} /images`; do
		fdtput -t s ${TMP_ITB} /images/${NAME} data "/INCBIN/(${NAME})"
	done
	dtc -I dtb -O dts ${TMP_ITB} -o ${ITS}
	rm -f ${TMP_ITB}

	# fixup placeholder: data = "/INCBIN/(...)"; -> data = /incbin/("...");
	sed -i "s/\"\/INCBIN\/(\(.*\))\"/\/incbin\/(\"\1\")/" ${ITS}

	# remove
	sed -i "/memreserve/d"		${ITS}
	sed -i "/timestamp/d"		${ITS}
	sed -i "/data-size/d"		${ITS}
	sed -i "/data-position/d"	${ITS}
	sed -i "/value/d"		${ITS}
	sed -i "/hashed-strings/d"	${ITS}
	sed -i "/hashed-nodes/d"	${ITS}
	sed -i "/signer-version/d"	${ITS}
	sed -i "/signer-name/d"		${ITS}
}

args_process $*
unpack_itb
gen_its

