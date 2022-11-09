#!/bin/bash
#
# Copyright (c) 2020 Rockchip Electronics Co., Ltd
#
# SPDX-License-Identifier: GPL-2.0
#
set -e

FRAGMENT_CONFIG=$1

if [ -z "${FRAGMENT_CONFIG}" ]; then
	echo
	echo "Usage: a script to sync/add config fragment."
	echo
	echo "Command:"
	echo "      $0  [config fragment]"
	echo "Example:"
	echo "      $0 ./configs/rv1109.config       -- add or sync rv1109.config"
	echo
	exit 1
fi

if [ ! -f .config ]; then
	echo "ERROR: No .config"
	exit 1
fi

BASE_DEFCONFIG1=`sed -n "/CONFIG_BASE_DEFCONFIG=/s/CONFIG_BASE_DEFCONFIG=//p" .config | tr -d '\r' | tr -d '"'`
if [ -z "${BASE_DEFCONFIG1}" ]; then
	echo "ERROR: No base defconfig assigned by BASE_DEFCONFIG1=..."
	exit 1
fi

if [ ! -f configs/${BASE_DEFCONFIG1} ]; then
	echo "ERROR: No base defconfig \"${BASE_DEFCONFIG1}\""
	exit 1
fi

BASE_DEFCONFIG0=`sed -n "/CONFIG_BASE_DEFCONFIG=/s/CONFIG_BASE_DEFCONFIG=//p" configs/${BASE_DEFCONFIG1} | tr -d '\r' | tr -d '"'`

if [ ! -f ${FRAGMENT_CONFIG} ]; then
	MSG_NEW_FILE="New config fragment: ${FRAGMENT_CONFIG}"
fi

cp .config fragment.config
make ${BASE_DEFCONFIG0} ${BASE_DEFCONFIG1}
./scripts/diffconfig -m .config fragment.config | sort > ${FRAGMENT_CONFIG}
mv fragment.config .config

echo "$MSG_NEW_FILE"
echo "Sync ${FRAGMENT_CONFIG} ... OK."
echo

