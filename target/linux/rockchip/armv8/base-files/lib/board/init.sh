#!/bin/sh
. /lib/functions.sh

NPROCS="$(grep -c "^processor.*:" /proc/cpuinfo)"
PROC_MASK="$(( (1 << $NPROCS) - 1 ))"

set_iface_cpumask() {
    local core_mask="$1"
    local interface="$2"
    local device="$3"
    local queue_mask="$4"
    local irq
    local seconds

    [ -z "${device}" ] && device="$interface"
    [ -z "${queue_mask}" ] && {
        queue_mask=$(( $PROC_MASK ^ 0x${core_mask} ))
        queue_mask="$(printf %x "$queue_mask")"
    }

    ip link set dev "$interface" up

    for seconds in $(seq 0 2); do
        irq=$(grep -m1 " ${device}\$" /proc/interrupts | sed -n -e 's/^ *\([^ :]\+\):.*$/\1/p')
        if [ -n "${irq}" ]; then
            echo "${core_mask}" > /proc/irq/${irq}/smp_affinity
            echo "${queue_mask}" > /sys/class/net/$interface/queues/rx-0/rps_cpus
            echo "${queue_mask}" > /sys/class/net/$interface/queues/tx-0/xps_cpus
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

board_fixup_broken_usb() {
    case $(board_name) in
    friendlyarm,nanopi-r2s)
        # yes, disable tx rx on gmac, not the usb-net
        # ethtool -K eth0 tx off rx off
        ethtool -K eth1 tx-scatter-gather-fraglist off
        ;;
    esac
}

board_set_iface_smp_affinity() {
    case $(board_name) in
    friendlyarm,nanopi-r2s)
        set_iface_cpumask 2 "eth0" "" 5
        set_iface_cpumask 8 "eth1" "xhci-hcd:usb3" 5
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

board_fixup_broken_usb

board_set_iface_smp_affinity
