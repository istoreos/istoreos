
type 'board_name' >/dev/null 2>/dev/null || . /lib/functions.sh

export_ota_url() {
	local board="$(board_name)"
	case "$board" in
	raspberrypi,400 |\
	raspberrypi,4-compute-module |\
	raspberrypi,4-model-b)
		export -n OTA_URL_BASE="https://fw.koolcenter.com/iStoreOS/rpi4"
		;;
	*)
		return 1
		;;
	esac
}
