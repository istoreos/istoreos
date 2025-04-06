#!/bin/sh
# based on https://github.com/6ang996/istoreos-rk356x/blob/rk356x/target/linux/rk356x/armv8/base-files/etc/init.d/rename_iface

. /lib/functions.sh

NPROCS="$(grep -c "^processor.*:" /proc/cpuinfo)"
PROC_MASK="$(( (1 << $NPROCS) - 1 ))"
PROC_MASK="$(printf %x "$PROC_MASK")"

rename_iface() {
	ip link set $1 down && ip link set $1 name $2
}

get_iface_device() {
	basename $(readlink /sys/class/net/$1/device)
}

device_to_iface() {
	local device=$1
	if [[ $device = *-*:* ]]; then
		#usb
		ls /sys/bus/usb/devices/$device/net/ | head -1
	elif [[ $device = *:*:* ]]; then
		#pci
		ls /sys/bus/pci/devices/$device/net/ | head -1
	else
		#platform
		ls /sys/devices/platform/$device/net/ | head -1
	fi
}

reorder_eth() {
	local index=0
	local iface toiface
	while [[ -n "$1" ]]; do
		toiface="eth$index"
		iface=$(device_to_iface $1)
		if [[ -n "$iface" && "$iface" != "$toiface" ]]; then
			rename_iface $toiface rename_tmp 2>/dev/null
			rename_iface $iface $toiface
			rename_iface rename_tmp $iface 2>/dev/null
		fi
		index=$(( $index + 1 ))
		shift
	done
}

set_iface_cpumask() {
	local core_mask="$1"
	local interface="$2"
	local device="$3"
	local irq
	local seconds
	local mq
	local q
	local queue_mask=$(( 0x${PROC_MASK} ^ 0x${core_mask} ))
	queue_mask="$(printf %x "$queue_mask")"
	local mq_mask="$4"

	[[ -d "/sys/class/net/${interface}" ]] || return 1

	[[ -n "${device}" && "${device}" = "${interface}-*" ]] && mq=1

	[[ -z "${mq}" || "${device}" = "${interface}-0" ]] && ip link set dev "${interface}" up

	[[ -z "${device}" ]] && device="$interface"

	for seconds in $(seq 0 1); do
		[[ ${seconds} = 0 ]] || sleep 1
		irq=$(grep -m1 " ${device}\$" /proc/interrupts | sed -n -e 's/^ *\([^ :]\+\):.*$/\1/p')
		if [[ -n "${irq}" ]]; then
			echo "${core_mask}" > /proc/irq/${irq}/smp_affinity
			if [[ -z "${mq}" ]]; then
				echo "${queue_mask}" > /sys/class/net/$interface/queues/rx-0/rps_cpus
				echo "${queue_mask}" > /sys/class/net/$interface/queues/tx-0/xps_cpus
			elif [[ "${device}" = "${interface}-0" ]]; then
				[[ -n "$mq_mask" ]] || mq_mask="${queue_mask}"
				for q in /sys/class/net/$interface/queues/rx-*; do
					echo "$mq_mask" > "$q/rps_cpus"
				done
				# for q in /sys/class/net/$interface/queues/tx-*; do
				#     echo "$mq_mask" > "$q/xps_cpus"
				# done
			fi
			return 0
		elif [[ -n "${mq}" && "${device}" != "${interface}-0" ]]; then
			break
		fi
	done
	return 1
}

board_fixup_iface_name() {
	local device
	case $(board_name) in
	friendlyelec,nanopi-r5c|\
	fastrhino,r66s)
		device="$(get_iface_device eth0)"
		if [[ "$device" = "0001:11:00.0" ]]; then
			rename_iface eth0 lan1
			rename_iface eth1 eth0
			rename_iface lan1 eth1
		fi
		;;
	easepi,ars4|\
	jsy,h1|\
	hinlink,hnas|\
	hinlink,opc-h66k)
		device="$(get_iface_device eth1)"
		if [[ "$device" = "0001:11:00.0" ]]; then
			rename_iface eth0 lan1
			rename_iface eth1 eth0
			rename_iface lan1 eth1
		fi
		;;
	lyt,t68m|\
	fastrhino,r68s)
		device="$(get_iface_device eth0)"
		if [[ "$device" = "fe010000.ethernet" ]]; then
			rename_iface eth0 wan
			rename_iface eth1 eth0
			rename_iface wan eth1
		fi
		device="$(get_iface_device eth3)"
		if [[ "$device" = "0002:21:00.0" ]]; then
			rename_iface eth2 lan3
			rename_iface eth3 eth2
			rename_iface lan3 eth3
		fi
		;;
	firefly,rk3568-roc-pc)
		device="$(get_iface_device eth0)"
		if [[ "$device" = "fe010000.ethernet" ]]; then
			rename_iface eth0 wan
			rename_iface eth1 eth0
			rename_iface wan eth1
		fi
		;;
	friendlyelec,nanopi-r5s|friendlyelec,nanopi-r5s-c1)
		device="$(get_iface_device eth2)"
		# r5s lan1 is under pcie2x1
		if [[ "$device" = "0000:01:00.0" ]]; then
			rename_iface eth1 lan2
			rename_iface eth2 eth1
			rename_iface lan2 eth2
		fi
		;;
	easepi,r1|easepi,r1-lite|\
	hinlink,opc-h68k)
		device="$(get_iface_device eth1)"
		if [[ "$device" = "fe010000.ethernet" ]]; then
			rename_iface eth0 wan
			rename_iface eth1 eth0
			rename_iface wan eth1
		fi
		device="$(get_iface_device eth3)"
		if [[ "$device" = "0001:11:00.0" ]]; then
			rename_iface eth2 lan3
			rename_iface eth3 eth2
			rename_iface lan3 eth3
		fi
		;;
	hinlink,opc-h69k)
		device="$(get_iface_device eth2)"
		if [[ "$device" = "0001:11:00.0" ]]; then
			rename_iface eth1 lan2
			rename_iface eth2 eth1
			rename_iface lan2 eth2
		fi
		;;
	hinlink,h88k-v3|\
	friendlyelec,nanopi-r6s)
		device="$(get_iface_device eth1)"
		if [[ "$device" = "0004:41:00.0" ]]; then
			rename_iface eth1 lan2
			rename_iface eth2 eth1
			rename_iface lan2 eth2
		fi
		;;
	cyber,cyber3588-aib)
		device="$(get_iface_device eth1)"
		if [[ "$device" = "0004:41:00.0" ]]; then
			rename_iface eth1 lan2
			rename_iface eth2 eth1
			rename_iface lan2 eth2
		fi
		;;
	armsom,sige7-v1)
		device="$(get_iface_device eth1)"
		if [[ "$device" = "0004:41:00.0" ]]; then
			rename_iface eth1 wan
			rename_iface eth0 eth1
			rename_iface wan eth0
		fi
		;;
	radxa,e52c)
		device="$(get_iface_device eth0)"
		if [[ "$device" = "0004:41:00.0" ]]; then
			rename_iface eth1 wan
			rename_iface eth0 eth1
			rename_iface wan eth0
		fi
		;;
	inspur,ihec301)
		device="$(get_iface_device eth1)"
		if [[ "$device" = "fe1b0000.ethernet" ]]; then
			rename_iface eth0 lan
			rename_iface eth1 eth0
			rename_iface lan eth1
		fi
		;;
	*)
		if [[ -s /proc/device-tree/eth_order ]]; then
			reorder_eth $(cat /proc/device-tree/eth_order | tr ',' ' ' )
		fi
		;;
	esac
}

board_set_iface_smp_affinity() {
	case $(board_name) in
	inspur,ihec301|\
	ezpro,mrkaio-m68s|\
	firefly,rk3568-roc-pc)
		set_iface_cpumask 2 eth0
		set_iface_cpumask 4 eth1
		;;
	hinlink,opc-h69k|\
	friendlyelec,nanopi-r5s|friendlyelec,nanopi-r5s-c1)
		set_iface_cpumask 2 eth0
		if ethtool -i eth1 | grep -Fq 'driver: r8169'; then
			set_iface_cpumask 4 "eth1"
			set_iface_cpumask 8 "eth2"
		else
			set_iface_cpumask 4 "eth1" "eth1-0" && \
			set_iface_cpumask 4 "eth1" "eth1-16" && \
			set_iface_cpumask 2 "eth1" "eth1-18" && \
			set_iface_cpumask 8 "eth2" "eth2-0" && \
			set_iface_cpumask 8 "eth2" "eth2-18" && \
			set_iface_cpumask 1 "eth2" "eth2-16"
		fi
		;;
	easepi,r1|easepi,r1-lite|\
	roceos,k40pro|\
	roceos,k50s|\
	lyt,t68m|\
	fastrhino,r68s|\
	hinlink,opc-h68k)
		set_iface_cpumask 1 "eth0"
		set_iface_cpumask 2 "eth1"
		if ethtool -i eth2 | grep -Fq 'driver: r8169'; then
			set_iface_cpumask 4 "eth2"
			set_iface_cpumask 8 "eth3"
		else
			set_iface_cpumask 4 "eth2" "eth2-0" && \
			set_iface_cpumask 4 "eth2" "eth2-16" && \
			set_iface_cpumask 2 "eth2" "eth2-18"
			set_iface_cpumask 8 "eth3" "eth3-0" && \
			set_iface_cpumask 8 "eth3" "eth3-18" && \
			set_iface_cpumask 1 "eth3" "eth3-16"
		fi
		;;
	jsy,h1|\
	yyy,h1|\
	armsom,sige1-v1|\
	easepi,ars4|\
	ezpro,mrkaio-m68s-plus|\
	friendlyelec,nanopi-r5c|\
	fastrhino,r66s|\
	hinlink,hnas|\
	hinlink,opc-h66k)
		if ethtool -i eth0 | grep -Fq 'driver: r8169'; then
			set_iface_cpumask 4 "eth0"
			set_iface_cpumask 8 "eth1"
		else
			set_iface_cpumask 2 "eth0" "eth0-0" && \
			set_iface_cpumask 2 "eth0" "eth0-16" && \
			set_iface_cpumask 8 "eth0" "eth0-18" && \
			set_iface_cpumask 4 "eth1" "eth1-0" && \
			set_iface_cpumask 4 "eth1" "eth1-18" && \
			set_iface_cpumask 1 "eth1" "eth1-16"
		fi
		;;
	friendlyelec,nanopi-r6s|\
	friendlyelec,nanopi-r6c)
		set_iface_cpumask 2 eth0
		if ethtool -i eth1 | grep -Fq 'driver: r8169'; then
			set_iface_cpumask 4 "eth1"
			set_iface_cpumask 8 "eth2"
		else
			set_iface_cpumask 4 "eth1" "eth1-0" f0 && \
			set_iface_cpumask 4 "eth1" "eth1-16" && \
			set_iface_cpumask 2 "eth1" "eth1-18" && \
			set_iface_cpumask 8 "eth2" "eth2-0" f0 && \
			set_iface_cpumask 8 "eth2" "eth2-18" && \
			set_iface_cpumask 1 "eth2" "eth2-16"
		fi
		;;
	armsom,sige7-v1)
		if ethtool -i eth0 | grep -Fq 'driver: r8169'; then
			set_iface_cpumask 4 "eth0"
			set_iface_cpumask 8 "eth1"
		else
			set_iface_cpumask 4 "eth0" "eth0-0" f0 && \
			set_iface_cpumask 4 "eth0" "eth0-16" && \
			set_iface_cpumask 2 "eth0" "eth0-18" && \
			set_iface_cpumask 8 "eth1" "eth1-0" f0 && \
			set_iface_cpumask 8 "eth1" "eth1-18" && \
			set_iface_cpumask 1 "eth1" "eth1-16"
		fi
		;;
	radxa,e52c)
		if ethtool -i eth0 | grep -Fq 'driver: r8169'; then
			set_iface_cpumask 4 "eth0"
			set_iface_cpumask 8 "eth1"
		else
			set_iface_cpumask 4 "eth0" "eth0-0" 30 && \
			set_iface_cpumask 4 "eth0" "eth0-16" && \
			set_iface_cpumask 2 "eth0" "eth0-18" && \
			set_iface_cpumask 8 "eth1" "eth1-0" 30 && \
			set_iface_cpumask 8 "eth1" "eth1-18" && \
			set_iface_cpumask 1 "eth1" "eth1-16"
		fi
		;;
	hinlink,h88k-*|\
	hinlink,h88k)
		set_iface_cpumask 2 eth0
		if ethtool -i eth1 | grep -Fq 'driver: r8169'; then
			set_iface_cpumask 4 "eth1"
			set_iface_cpumask 8 "eth2" && \
			set_iface_cpumask 10 "eth3" && \
			set_iface_cpumask 20 "eth4"
		else
			set_iface_cpumask 4 "eth1" "eth1-0" f0 && \
			set_iface_cpumask 4 "eth1" "eth1-16" && \
			set_iface_cpumask 2 "eth1" "eth1-18" && \
			set_iface_cpumask 8 "eth2" "eth2-0" f0 && \
			set_iface_cpumask 8 "eth2" "eth2-18" && \
			set_iface_cpumask 1 "eth2" "eth2-16" && \
			set_iface_cpumask 10 "eth3" "eth3-0" f0 && \
			set_iface_cpumask 10 "eth3" "eth3-16" && \
			set_iface_cpumask 8 "eth3" "eth3-18" && \
			set_iface_cpumask 20 "eth4" "eth4-0" f0 && \
			set_iface_cpumask 20 "eth4" "eth4-18" && \
			set_iface_cpumask 4 "eth4" "eth4-16"
		fi
		;;
	friendlyelec,nanopi-r3s|\
	radxa,e20c|\
	mangopi,m28k|\
	hlink,h28k)
		set_iface_cpumask 5 eth0
		# eth1 is rtl8111h, driven by r8169 or r8168
		if ethtool -i eth1 | grep -Fq 'driver: r8169'; then
			set_iface_cpumask b eth1
		else
			set_iface_cpumask 5 eth1 eth1-0 a
		fi
		;;
	easepi,r2|\
	ynn,nas|\
	le,hes30|\
	jp,tvbox|\
	panther,x2|\
	dg,nas-lite|\
	dg,tn3568|\
	hsa,bh2)
		set_iface_cpumask 2 "eth0"
		;;
	esac
}

board_wait_wifi() {
	local seconds
	[[ -f "/etc/uci-defaults/01-rk35xx-wifi" ]] || return 0
	case $(board_name) in
	hinlink,h88k-*|\
	hinlink,h88k|\
	hinlink,opc-h68k|\
	hinlink,opc-h69k)
		for seconds in $(seq 0 30); do
			[[ -s /etc/config/wireless ]] && break
			sleep 1
		done
		sleep 1
	;;
	esac
}

board_fixup_iface_name

board_set_iface_smp_affinity

board_wait_wifi
