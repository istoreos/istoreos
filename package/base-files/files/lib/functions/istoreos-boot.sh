# > getbootdisk
# mmcblk0
_getbootdisk()
{
    local rootpart=`grep -Fm1 ' - squashfs /dev/root ' /proc/self/mountinfo | cut -d' ' -f3`
    [ -z "$rootpart" ] && return 1
    local devpath=`readlink /sys/dev/block/$rootpart`
    [ -z "$devpath" ] && return 1
    rootpart="${devpath##*/}"
    devpath="${devpath%%/$rootpart}"
    local rootdisk="${devpath##*/}"
    echo $rootdisk
}

# > getpartofdisk sda 3
# sda3
# > getpartofdisk mmcblk0 3
# mmcblk0p3
_getpartofdisk()
{
    local disk="$1"
    local part="$2"
    local dev="`cat /sys/block/$disk/dev`"
    [ -z "$dev" ] && return 1
    local major="${dev%%:*}"
    local minor="${dev##*:}"
    local devpath=`readlink /sys/dev/block/$major:$(($minor + $part))`
    [ -z "$devpath" ] && return 1
    echo "${devpath##*/}"
}

_get_overlay_partition_default()
{
	local bootdisk="`_getbootdisk`"
	[ -z "$bootdisk" ] && return 1
	cat /sys/block/$bootdisk/uevent > /tmp/.bootdisk
	local overlay_dev="`_getpartofdisk $bootdisk 3`"
	[ -z "$overlay_dev" ] && return 1
	OVERLAY_DEV="/dev/$overlay_dev"
	return 0
}

get_overlay_partition()
{
	_get_overlay_partition_default || {
		log "Unable to determine overlay partition"
		return 1
	}
	return 0
}
