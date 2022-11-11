
type 'board_name' >/dev/null 2>/dev/null || . /lib/functions.sh

export_ota_url() {
    local board="$(board_name)"
	case "$board" in
	friendlyarm,nanopi-r2s|\
	friendlyarm,nanopi-r4s|\
	friendlyarm,nanopi-r4se)
		export -n OTA_URL_BASE="https://fw.koolcenter.com/iStoreOS/${board##*-}"
		;;
	*)
		return 1
		;;
	esac
}
