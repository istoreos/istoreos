#!/bin/sh
. /lib/functions.sh

set_iface_cpumask() {
    local core_mask="$1"
    local interface="$2"
    local device="$3"
    local irq
    local seconds

    [ -z "${device}" ] && device="$interface"

    ip link set dev "$interface" up

    for seconds in $(seq 0 2); do
        irq=$(grep -m1 " ${device}\$" /proc/interrupts | sed -n -e 's/^ *\([^ :]\+\):.*$/\1/p')
        if [ -n "${irq}" ]; then
            echo "${core_mask}" > /proc/irq/${irq}/smp_affinity
            return 0
        fi
        sleep 1
    done
}

wait_for_iface() {
    local interface="$1"
    local seconds
    for seconds in $(seq 0 2); do
        [ -e "/sys/class/net/$interface" ] && return 0
        sleep 1
    done
}

board_set_iface_smp_affinity() {
    case $(board_name) in
    friendlyarm,nanopi-r2s)
        set_iface_cpumask 2 "eth0"
        set_iface_cpumask 4 "eth1" "xhci-hcd:usb3"
        ;;
    friendlyarm,nanopi-r4se|\
    friendlyarm,nanopi-r4s)
        set_iface_cpumask 10 "eth0"
        set_iface_cpumask 20 "eth1"
        ;;
    esac
}

board_name | grep -qF 'friendlyarm,nanopi-r' || exit 0

wait_for_iface eth1

board_set_iface_smp_affinity
