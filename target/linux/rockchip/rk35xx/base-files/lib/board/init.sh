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
		irq=$(grep -m1 " ${device}\$" /proc/interrupts | sed -n -e 's/^ *\([^ :]\+\):.*$/\1/p')
		if [ -n "${irq}" ]; then
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
		fi
		sleep 1
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
	friendlyelec,nanopi-r5s)
		device="$(get_iface_device eth2)"
		# r5s lan1 is under pcie2x1
		if [[ "$device" = "0000:01:00.0" ]]; then
			rename_iface eth1 lan2
			rename_iface eth2 eth1
			rename_iface lan2 eth2
		fi
		;;
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
	esac
}

board_set_iface_smp_affinity() {
	case $(board_name) in
	firefly,rk3568-roc-pc)
		set_iface_cpumask 2 eth0
		set_iface_cpumask 4 eth1
		;;
	hinlink,opc-h69k|\
	friendlyelec,nanopi-r5s)
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
			set_iface_cpumask 2 "eth2" "eth2-18" && \
			set_iface_cpumask 8 "eth3" "eth3-0" && \
			set_iface_cpumask 8 "eth3" "eth3-18" && \
			set_iface_cpumask 1 "eth3" "eth3-16"
		fi
		;;
	jsy,h1|\
	yyy,h1|\
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
	hlink,h28k)
		set_iface_cpumask c eth0
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

set_gpio() {
	# ref package/base-files/files/etc/init.d/gpio_switch
	local gpio_pin="$1"
	local value="$2"

	[ -z "$gpio_pin" ] &&  return 1

	local gpio_path
	if [ -n "$(echo "$gpio_pin" | grep -E "^[0-9]+$")" ]; then
		gpio_path="/sys/class/gpio/gpio${gpio_pin}"

		# export GPIO pin for access
		[ -d "$gpio_path" ] || {
			echo "$gpio_pin" >/sys/class/gpio/export
			# we need to wait a bit until the GPIO appears
			[ -d "$gpio_path" ] || sleep 1
		}

		# direction attribute only exists if the kernel supports changing the
		# direction of a GPIO
		if [ -e "${gpio_path}/direction" ]; then
			# set the pin to output with high or low pin value
			{ [ "$value" = "0" ] && echo "low" || echo "high"; } \
				>"$gpio_path/direction"
		else
			{ [ "$value" = "0" ] && echo "0" || echo "1"; } \
				>"$gpio_path/value"
		fi
	fi
}

board_gpio_defaults() {
	case $(board_name) in
	hinlink,hnas)
		# set GPIO4_A7 to high, deassert SATA PM chip
		set_gpio 135
		sleep 2
	;;
	esac
}

board_otg_defaults() {
	case $(board_name) in
	jsy,h1|\
	yyy,h1|\
	idiskk,h1|\
	fastrhino,r66s|\
	fastrhino,r68s)
		echo host >/sys/kernel/debug/usb/fcc00000.dwc3/mode
	;;
	esac
}

board_gpio_defaults

board_otg_defaults

board_fixup_iface_name

board_set_iface_smp_affinity

board_wait_wifi
