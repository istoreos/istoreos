#!/bin/sh
# based on https://github.com/6ang996/istoreos-rk356x/blob/rk356x/target/linux/rk356x/armv8/base-files/etc/init.d/rename_iface

. /lib/functions.sh

rename_iface() {
    ip link set $1 down && ip link set $1 name $2
}

get_iface_device() {
    basename $(readlink /sys/class/net/$1/device)
}

fixup_iface_name() {
    local device
    case $(board_name) in
    fastrhino,r66s)
        device="$(get_iface_device eth0)"
        if [[ "$device" != "0002:21:00.0" ]]; then
            rename_iface eth0 lan1
            rename_iface eth1 eth0
            rename_iface lan1 eth1
        fi
        ;;
    fastrhino,r68s)
        device="$(get_iface_device eth0)"
        if [[ "$device" != "fe010000.ethernet" ]]; then
            rename_iface eth0 wan
            rename_iface eth1 eth0
            rename_iface wan eth1
        fi
        device="$(get_iface_device eth2)"
        if [[ "$device" != "0002:21:00.0" ]]; then
            rename_iface eth2 lan3
            rename_iface eth3 eth2
            rename_iface lan3 eth3
        fi
        ;;
    friendlyelec,nanopi-r5s)
        device="$(get_iface_device eth1)"
        # r5s lan1 is under pcie2x1
        if [[ "$device" != "0000:01:00.0" ]]; then
            rename_iface eth1 lan2
            rename_iface eth2 eth1
            rename_iface lan2 eth2
        fi
        ;;
    esac
}

fixup_iface_name
