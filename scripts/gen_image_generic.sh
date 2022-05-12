#!/bin/sh
# Copyright (C) 2006-2012 OpenWrt.org
set -e -x
if [ $# -ne 5 ] && [ $# -ne 6 ]; then
    echo "SYNTAX: $0 <file> <kernel size> <kernel directory> <rootfs size> <rootfs image> [<align>]"
    exit 1
fi

OUTPUT="$1"
KERNELSIZE="$2"
KERNELDIR="$3"
ROOTFSSIZE="$4"
ROOTFSIMAGE="$5"
ALIGN="$6"
USERDATASIZE="2048"

rm -f "$OUTPUT"

head=16
sect=63

# create partition table
set $(ptgen -o "$OUTPUT" -h $head -s $sect ${GUID:+-g} -p "${KERNELSIZE}m" -p "${ROOTFSSIZE}m" -p "${USERDATASIZE}m" ${ALIGN:+-l $ALIGN} ${SIGNATURE:+-S 0x$SIGNATURE} ${GUID:+-G $GUID})

KERNELOFFSET="$(($1 / 512))"
KERNELSIZE="$2"
ROOTFSOFFSET="$(($3 / 512))"
ROOTFSSIZE="$(($4 / 512))"
USERDATAOFFSET="$(($5 / 512))"
USERDATASIZE="$(($6 / 512))"

dd if=/dev/zero of="$OUTPUT" bs=512 seek="$ROOTFSOFFSET" conv=notrunc count="$ROOTFSSIZE"
dd if="$ROOTFSIMAGE" of="$OUTPUT" bs=512 seek="$ROOTFSOFFSET" conv=notrunc

[ -n "$PADDING" ] && dd if=/dev/zero of="$OUTPUT" bs=512 seek="$USERDATAOFFSET" conv=notrunc count="$USERDATASIZE"
echo "RESET000" | dd of="$OUTPUT" bs=512 seek="$USERDATAOFFSET" conv=notrunc,sync count=1

if [ -n "$GUID" ]; then
    [ -n "$PADDING" ] && dd if=/dev/zero of="$OUTPUT" bs=512 seek="$((USERDATAOFFSET + USERDATASIZE))" conv=notrunc count="$sect"
    mkfs.fat -n kernel -C "$OUTPUT.kernel" -S 512 "$((KERNELSIZE / 1024))"
    mcopy -s -i "$OUTPUT.kernel" "$KERNELDIR"/* ::/
else
    make_ext4fs -J -L kernel -l "$KERNELSIZE" "$OUTPUT.kernel" "$KERNELDIR"
fi

dd if="$OUTPUT.kernel" of="$OUTPUT" bs=512 seek="$KERNELOFFSET" conv=notrunc
rm -f "$OUTPUT.kernel"
