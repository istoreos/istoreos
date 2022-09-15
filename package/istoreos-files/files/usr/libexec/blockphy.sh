#!/bin/sh

DEVNAME=${1#/dev/}
[ -z "$DEVNAME" ] && exit 1

getusb() {
    if [ "$2" = "1" ]; then
        echo "/$1/"
        return 0
    fi
    echo "/$1_$2/"
}

getdisk() {
    local DISK=$1
    local path=`readlink /sys/block/$DISK`
    local usb=`echo "$path" | grep -oE '/usb[0-9]+/'`
    if [ -n "$usb" ]; then
        usb=${usb#/}
        usb=${usb%/}
        getusb `echo "$path" | grep -oE "/$usb/${usb#usb}-[0-9]+/" | sed -r "s#^/($usb)/${usb#usb}-([0-9]+)/\\\$#\\1 \\2#g"`
        return 0
    fi
    case "$DISK" in
        sd*)
            echo "$path" | grep -oE '/ata[0-9]+/' | sed 's/ata/sata/g' ;;
        mmcblk*)
            echo "$path" | grep -oE '/mmc[0-9]+/' ;;
        nvme*)
            echo "/$DISK/" ;;
    esac
    return 0
}

getphy() {
    [ -e /sys/block/$1 ] || return 1
    local disk=`getdisk $1`
    disk=${disk#/}
    echo "${disk%/}-${2:-0}"
}

# sd[a-z]+([0-9]+)?
# mmcblk[0-9]+(p[0-9]+)?
# nvme[0-9]+n[0-9]+(p[0-9]+)?

case "$DEVNAME" in
    sd*)
        getphy `echo "$DEVNAME" | sed -r 's/^(sd[a-z]+)([0-9]+)?$/\1 \2/g'` ;;
    mmcblk*)
        getphy `echo "$DEVNAME" | sed -r 's/^(mmcblk[0-9]+)(p([0-9]+))?$/\1 \3/g'` ;;
    nvme*)
        getphy `echo "$DEVNAME" | sed -r 's/^(nvme[0-9]+n[0-9]+)(p([0-9]+))?$/\1 \3/g'` ;;
    *)
        exit 1;
esac
