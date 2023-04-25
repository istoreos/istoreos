# > getbootdisk
# mmcblk0
_getbootdisk()
{
	local rootpart="`grep -Fm1 ' - squashfs /dev/root ' /proc/self/mountinfo | cut -d' ' -f3`"
	[ -z "$rootpart" ] && return 1
	local devpath="`readlink /sys/dev/block/$rootpart`"
	[ -z "$devpath" ] && return 1
	rootpart="${devpath##*/}"
	devpath="${devpath%%/$rootpart}"
	local rootdisk="${devpath##*/}"
	echo "$rootdisk"
}

# > getbootdisk_lvm
# dm-0
_getbootdisk_lvm()
{
	local rootpart
	if [ -e /rom/note ]; then
		rootpart="`grep -Fm1 ' / / ' /proc/self/mountinfo | grep -F ' - squashfs ' | cut -d' ' -f3`"
	else
		rootpart="`grep -Fm1 ' / /rom ' /proc/self/mountinfo | grep -F ' - squashfs ' | cut -d' ' -f3`"
	fi
	[ -z "$rootpart" ] && return 1
	local major=${rootpart%%:*}
	local minor=${rootpart##*:}
	minor="$(( $minor & 0xfffc ))"
	local devpath="`readlink /sys/dev/block/$major:$minor`"
	[ -z "$devpath" ] && return 1
	local rootdisk="${devpath##*/}"
	echo "$rootdisk"
}

# > getpartofdisk sda 3
# sda3
# > getpartofdisk mmcblk0 3
# mmcblk0p3
_getpartofdisk()
{
	local disk="$1" offset="$2" part
	if [[ "$offset" = 0 ]]; then
		echo "$disk"
	else
		part="$disk"
		echo "$part" | grep -q '^.*\d$' && part="${part}p"
		part="${part}"$(( ${offset} ))
		if [ ! -b "/dev/$part" ]; then
			# lvm
			local line
			local MAJOR MINOR DEVNAME DEVTYPE
			while read line; do
				export -n "$line"
			done < "/sys/block/$disk/uevent"
			local devpath="`readlink /sys/dev/block/$MAJOR:$(($MINOR + $offset))`"
			if [ -n "$devpath" ]; then
				part="${devpath##*/}"
			fi
		fi
		echo "$part"
	fi
	return 0
}

_get_overlay_partition_default()
{
	local bootdisk="`_getbootdisk`"
	[ -z "$bootdisk" ] && {
		log "getbootdisk failed, try lvm"
		bootdisk="`_getbootdisk_lvm`"
	}
	[ -z "$bootdisk" ] && {
		log "getbootdisk_lvm failed"
		return 1
	}
	if [ ! -e "/sys/block/$bootdisk/uevent" ]; then
		log "/sys/block/$bootdisk/uevent does not exist"
		return 1
	fi
	if [ -e /rom/note ]; then
		# we are in mount_root if /rom/note exists
		cat "/sys/block/$bootdisk/uevent" > /tmp/.bootdisk
	fi
	local overlay_dev="`_getpartofdisk $bootdisk 3`"
	[ -z "$overlay_dev" ] && {
		log "getpartofdisk $bootdisk 3 failed"
		return 1
	}
	OVERLAY_DEV="/dev/$overlay_dev"
	return 0
}

_get_overlay_partition_fallback()
{
	log "get_overlay_partition_fallback"
	rm -f /tmp/.bootdisk >/dev/null 2>&1
	local overlay_dev=$(
		. /lib/upgrade/common.sh
		export_bootdevice && export_partdevice overlay_dev 3 && echo $overlay_dev
	)
	[ -z "$overlay_dev" ] && return 1
	OVERLAY_DEV="/dev/$overlay_dev"
	return 0
}

get_overlay_partition()
{
	_get_overlay_partition_default || _get_overlay_partition_fallback || {
		log "Unable to determine overlay partition"
		return 1
	}
	return 0
}
