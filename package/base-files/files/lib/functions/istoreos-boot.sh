
. /lib/upgrade/common.sh

get_overlay_partition()
{
	local overlay_dev
	export_bootdevice && export_partdevice overlay_dev 3 || {
		log "Unable to determine overlay partition"
		return 1
	}
	if [ -z "$overlay_dev" ]; then
		log "Unable to determine overlay partition"
		return 1
	fi
	OVERLAY_DEV="/dev/$overlay_dev"

}
