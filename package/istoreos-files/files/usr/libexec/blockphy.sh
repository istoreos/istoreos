#!/bin/sh

DEVNAME=${1#/dev/}
[ -z "$DEVNAME" ] && exit 1

getdisk() {
    local DISK=$1
    local path=`readlink /sys/block/$DISK`
    local usb=`echo "$path" | grep -oE '/usb[0-9]+/[^:]+'`
    if [ -n "$usb" ]; then
        usb=${usb##*/}
        usb=${usb%%-1}
        echo usb`echo "$usb" | sed 's/[-.]/_/g'`
        return 0
    fi
    case "$DISK" in
        mmcblk*)
            echo "$path" | grep -oE '/mmc[0-9]+/'
			return 0
			;;
        nvme*)
            echo "/$DISK/"
			return 0
			;;
    esac
	# sata
    local sata=`echo "$path" | grep -oE '/ata[0-9]+/host[0-9]+/target[0-9]+:[0-9]+'`
    if [ -n "$sata" ]; then
        sata=`echo "$sata" | sed -r 's#/ata([0-9]+)/host[0-9]+/target[0-9]+:([0-9]+)#sata\1.\2#'`
        sata=${sata%%.0}
        echo "/$sata/"
        return 0
    fi
	# virtio
    sata=`echo "$path" | grep -oE '/virtio[0-9]+/host[0-9]+/target[0-9]+:[0-9]+:[0-9]+'`
    if [ -n "$sata" ]; then
        sata=`echo "$sata" | sed -r 's#/virtio([0-9]+)/host[0-9]+/target[0-9]+:[0-9]+:([0-9]+)#vio\1.\2#'`
        sata=${sata%%.0}
        echo "/$sata/"
        return 0
    fi
	# sas
    sata=`echo "$path" | grep -oE '/host[0-9]+/port-[0-9]+:[0-9]+'`
    if [ -n "$sata" ]; then
        sata=`echo "$sata" | sed -r 's#/host([0-9]+)/port-[0-9]+:([0-9]+)#sas\1.\2#'`
        sata=${sata%%.0}
        echo "/$sata/"
        return 0
    fi
	# scsi
    sata=`echo "$path" | grep -oE '/host[0-9]+/target[0-9]+:[0-9]+:[0-9]+'`
    if [ -n "$sata" ]; then
        sata=`echo "$sata" | sed -r 's#/host([0-9]+)/target[0-9]+:[0-9]+:([0-9]+)#scsi\1.\2#'`
        sata=${sata%%.0}
        echo "/$sata/"
        return 0
    fi
    echo "$path" | grep -oE '/host[0-9]+/' | sed 's/host/sata/g'
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
