#!/bin/bash

function md5(){
	md5sum $1 | head -c 32
}
function sha256(){
	sha256sum $1 | head -c 64
}
function thead(){
	echo '| Filename | sha256sum | md5sum |'
	echo '| :--- | :---: | :---: |'
}
function item(){
	echo '| ['"$1"']('"$1"') | ' `sha256 $1` '|' `md5 $1` '|'
}
function list(){
	for i in *
	do
		item $i
	done
}
function md_tail(){
	echo '## Image Files'
	thead
	grep '.install.img\]' tmp/.distlist | sort -r

	echo

	echo '## Supplementary Files'
	thead
	grep -v '.install.img\]' tmp/.distlist
}

TARGET_DIR_SRC=bin/targets/realtek/rtd129x
TARGET_DIR_DEST=bin/dist

mkdir -p $TARGET_DIR_DEST

VERSION=`cat $TARGET_DIR_SRC/version.buildinfo`

cp -a $TARGET_DIR_SRC/version.buildinfo \
    $TARGET_DIR_SRC/openwrt-*-$VERSION-realtek-*-ars2* \
    $TARGET_DIR_SRC/openwrt-imagebuilder-* \
    $TARGET_DIR_SRC/openwrt-sdk-* \
    $TARGET_DIR_DEST/

mkdir tmp
cp template/README.md tmp/

rm $TARGET_DIR_DEST/README.md

(cd $TARGET_DIR_DEST && list) > tmp/.distlist

md_tail >> tmp/README.md

cp tmp/README.md $TARGET_DIR_DEST/
