
get_overlay_partition()
{

	for item in `cat /proc/cmdline`; do
		case $item in
			overlay=*)		OVERLAY_DEV=${item:8};;
			overlayfs=*)	OVERLAY_FS=${item:10};;
		esac
	done

	if [ -z "$OVERLAY_DEV" ]; then
		OVERLAY_DEV=`blkid -L $OVERLAY_LABEL | grep /mmcblk0p`
		[ -z "$OVERLAY_DEV" ] || log "overlay dev not define by cmdline, fine $OVERLAY_LABEL got $OVERLAY_DEV"
	fi

	if [ -z "$OVERLAY_DEV" ]; then
		if dd if=/dev/mmcblk0p2 bs=5 count=1 2>/dev/null | grep -qF RESET; then
			OVERLAY_DEV=/dev/mmcblk0p2
			FSTYPE=RESET
			log "overlay not found by cmdline or label, but we found $OVERLAY_DEV marked as RESET, format later"
		fi
	fi

	if [ -z "$OVERLAY_DEV" ]; then
		log "Unable to determine overlay partition"
		return 1
	fi

	return 0
}
