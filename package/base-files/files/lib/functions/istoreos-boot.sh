
get_overlay_partition_fallback()
{
	local cmdline rootpart overlay_dev class
	local MAJOR MINOR
	if read cmdline < /proc/cmdline; then
		case "$cmdline" in
			*root=*)
				rootpart="${cmdline##*root=}"
				rootpart="${rootpart%% *}"
			;;
		esac
		case "$rootpart" in
			PARTUUID=[a-f0-9][a-f0-9][a-f0-9][a-f0-9][a-f0-9][a-f0-9][a-f0-9][a-f0-9]-02)
				overlay_dev=`blkid -l -o device -t "${rootpart%-02}-03"`
			;;
			PARTUUID=????????-????-????-????-??????????02)
				overlay_dev=`blkid -l -o device -t "${rootpart%02}03"`
			;;
			/dev/*)
				overlay_dev="${rootpart%2}3"
			;;
			0x[a-f0-9][a-f0-9][a-f0-9] | 0x[a-f0-9][a-f0-9][a-f0-9][a-f0-9] | \
			[a-f0-9][a-f0-9][a-f0-9] | [a-f0-9][a-f0-9][a-f0-9][a-f0-9])
				rootpart=0x${rootpart#0x}
				for class in /sys/class/block/*; do
					while read line; do
						export -n "$line"
					done < "$class/uevent"
					if [ $((rootpart/256)) = $MAJOR -a $(((rootpart%256) + 1)) = $MINOR ]; then
						overlay_dev="/dev/${class#/sys/class/block/}"
						break
					fi
				done
			;;
		esac
		[ -z "$overlay_dev" ] && return 1
		OVERLAY_DEV="$overlay_dev"
		return 0
	fi
	return 1
}

. /lib/upgrade/common.sh

get_overlay_partition_default()
{
	local overlay_dev
	export_bootdevice && export_partdevice overlay_dev 3 || return 1
	[ -z "$overlay_dev" ] && return 1
	OVERLAY_DEV="/dev/$overlay_dev"
	return 0
}

get_overlay_partition()
{
	get_overlay_partition_default || get_overlay_partition_fallback || {
		log "Unable to determine overlay partition"
		return 1
	}
	return 0
}
