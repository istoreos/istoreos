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
	echo '| ['"$1"']('"$1"') | ' `sha256 "$1"` '|' `md5 "$1"` '|'
}
function list(){
	local line
	ls | while read line; do
		item "$line"
	done
}

function merge_log(){
	local line
	while read line; do
		if [ -n "$line" ]; then
			echo "## `echo $line | sed 's/-/ /'`"
			cat template/log/$line.log
			echo
		fi
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
    $TARGET_DIR_SRC/openwrt-*-$VERSION-realtek-rtd129x.manifest \
    $TARGET_DIR_SRC/openwrt-*-$VERSION-realtek-rtd129x-ars2* \
    $TARGET_DIR_SRC/openwrt-imagebuilder-* \
    $TARGET_DIR_SRC/openwrt-sdk-* \
    $TARGET_DIR_DEST/

mkdir tmp
cp template/README.md tmp/

rm -f $TARGET_DIR_DEST/README.md
rm -f $TARGET_DIR_DEST/version.index
rm -f $TARGET_DIR_DEST/version.latest
rm -rf $TARGET_DIR_DEST/log

(cd $TARGET_DIR_DEST && list) > tmp/.distlist

grep '.install.img\]' tmp/.distlist | sort -r | head -1 | sed 's/|/ /g' | \
    xargs sh -c 'echo $0;echo SHA256: $1;echo MD5: $2' > tmp/.newest

cat tmp/.newest >> tmp/README.md

(cd template/log && ls) | sort -r | grep -F '.log' | sed 's/.log$//' > tmp/.loglist

cat template/README.log.head.md >> tmp/README.md
cat tmp/.loglist | merge_log >> tmp/README.md

cat template/README.files.head.md >> tmp/README.md
md_tail >> tmp/README.md

cp tmp/README.md $TARGET_DIR_DEST/
cp -a template/log $TARGET_DIR_DEST/
cp tmp/.newest $TARGET_DIR_DEST/version.latest
cp tmp/.loglist $TARGET_DIR_DEST/version.index
