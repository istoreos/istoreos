#!/bin/sh

DETECT=0

if [ -z "$ACTION" ]; then
log() {
    echo "$*" >&2
}
else
log() {
    logger -t "blockmount" "$*"
}
fi

# uci_section UUID LABEL DEVICE MOUNTPOINT
check_mount() {
    local uuid
    local label
    local device
    local target
    config_get uuid $1 uuid
    config_get label $1 label
    config_get device $1 device
    config_get target $1 target

    if [ "$DEVICE_CONFIGURED" = "0" -a \( "$uuid" = "$2" -o "$device" = "$4" -o "$target" = "$5" -o \( -n "$3" -a "$3" = "$label" \) \) ]; then
        export -n DEVICE_CONFIGURED=1
        [ -z "$ACTION" ] && log "found $1 ($uuid, $label, $device, $target) matches ($2, $3, $4, $5)"
    fi
}

# UUID LABEL DEVICE MOUNTPOINT
check_configured() {
    local DEVICE_CONFIGURED=0
    config_foreach check_mount mount "$1" "$2" "$3" "$4"
    return $DEVICE_CONFIGURED
}

handle_part() {
    [ -z "$ACTION" ] && log "$1 UUID=$UUID TYPE=$TYPE LABEL=$LABEL MOUNT=$MOUNT"
    [ -n "$1" ] || return 1

    # ignore mounted device, unknown fs type, swap or raid member
    [ -z "$UUID" -o -z "$TYPE" \
        -o "$TYPE" = "swap" \
        -o "$TYPE" = "linux_raid_member" \
    ] && return 0

    if [ "$DETECT" = "1" ]; then
        [ -z "$MOUNT" ] && return 0
        # in this case, only add mounted device: boot,root,overlayfs, and disable them
        log "add mount $UUID => $MOUNT"
        uci -q batch <<-EOF >/dev/null
            add fstab mount
            set fstab.@mount[-1].uuid=$UUID
            set fstab.@mount[-1].target=$MOUNT
            set fstab.@mount[-1].enabled=0
EOF
    elif [ -z "$MOUNT" ]; then
        local DEVICENAME="${1#/dev/}"
        local candidate="`/usr/libexec/blockphy.sh "$DEVICENAME"`"
        [ -z "$candidate" ] && return 0
        candidate="/mnt/$candidate"

        # check if candidate mount point is busy
        mountpoint -q "$candidate" && return 0

        # check if configured
        check_configured "$UUID" "$LABEL" "$1" "$candidate" || return 0

        # log "add mount $UUID => $candidate"
        mkdir -p "$candidate" && mount "$1" "$candidate"
    fi

}

scan_all() {
    local line
    block info | while read; do
        line="$REPLY"
        eval "${line##*: } handle_part ${line%%: *}"
    done
}

if [ "$1" = "detect" ]; then
    DETECT=1
    cat <<-EOF >/etc/config/fstab
config global
	option anon_swap '0'
	option anon_mount '0'
	option auto_swap '1'
	option auto_mount '1'
	option delay_root '5'
	option check_fs '0'

EOF
fi

. /lib/functions.sh

config_load fstab

scan_all

if [ "$DETECT" = "1" ]; then
    uci commit fstab
    sleep 2
    uci -q batch <<-EOF >/dev/null
        set fstab.@global[0].anon_mount=1
        commit fstab
EOF
fi
