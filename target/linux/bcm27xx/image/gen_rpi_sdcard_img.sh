#!/bin/sh

set -e -x

if [ $# -ne 5 ]; then
    echo "SYNTAX: $0 <file> <bootfs image> <rootfs image> <bootfs size> <rootfs size>"
    exit 1
fi

OUTPUT="$1"
BOOTFS="$2"
ROOTFS="$3"
BOOTFSSIZE="$4"
ROOTFSSIZE="$5"
USERDATASIZE="2048"

align=4096
head=4
kernel_type=c
rootfs_type=83
sect=63

set $(ptgen -o $OUTPUT -h $head -s $sect -l $align -t $kernel_type -p ${BOOTFSSIZE}M -t $rootfs_type -p ${ROOTFSSIZE}M -p ${USERDATASIZE}M ${SIGNATURE:+-S 0x$SIGNATURE})

BOOTOFFSET="$(($1 / 512))"
ROOTFSOFFSET="$(($3 / 512))"
USERDATAOFFSET="$(($5 / 512))"

echo "PREVENT \"SMART\" PARTED FROM MODIFYING MBR DISKID" | dd of="$OUTPUT" bs=440 conv=notrunc,sync count=1

dd bs=512 if="$BOOTFS" of="$OUTPUT" seek="$BOOTOFFSET" conv=notrunc
dd bs=512 if="$ROOTFS" of="$OUTPUT" seek="$ROOTFSOFFSET" conv=notrunc
echo "RESET000" | dd of="$OUTPUT" bs=512 seek="$USERDATAOFFSET" conv=notrunc,sync count=1
