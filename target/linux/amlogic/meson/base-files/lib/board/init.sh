#!/bin/sh

. /lib/functions.sh

board_wait_wifi() {
	local seconds=0
	case $(board_name) in
	phicomm,n1)
		for seconds in $(seq 0 2); do
			[[ -d /sys/devices/platform/soc/d0000000.apb/d0070000.mmc/mmc_host/mmc2/mmc2:0001/mmc2:0001:1/net ]] && break
			sleep 1
		done
		echo "board: wifi ready after $seconds seconds" >/dev/kmsg
		sleep 1
	;;
	esac
}

board_wait_wifi
