#!/bin/sh

idb="$1"
uboot="$2"
dest="$3"

[ -z "$idb" -o -z "$uboot" -o -z "$dest" ] && {
	echo "Merge rockchip idb and uboot into single continuous image."
	echo "Usage: $0 <idb_file> <uboot_file> <output_file>"
	exit 1
}

tmpfile=$(mktemp /tmp/rkuboot-merge-XXXXXX) || exit 1

dd if=/dev/zero "of=$tmpfile" bs=512 seek=0 count=16320
dd "if=$idb" "of=$tmpfile" bs=512 seek=0 conv=notrunc
dd "if=$uboot" "of=$tmpfile" bs=512 seek=16320 conv=sync
cat "$tmpfile" > "$dest"
rm -f "$tmpfile"
