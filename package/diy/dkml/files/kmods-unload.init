#!/bin/sh /etc/rc.common

START=25

check_driver_bond() {
	local kmod="$1"
	ls /sys/module/$kmod/drivers/*/ | grep -Fq :
}

rmmod_r() {
	local kmod="$1"
	local holder
	for holder in `ls /sys/module/$kmod/holders/`; do
		rmmod $holder
	done
	rmmod $kmod
}

auto_unload() {
	local function support keep kmod
	config_get function "$1" function
	config_get support "$1" support

	keep=0
	if [ -n "$function" ]; then
		for kmod in $function; do
			if check_driver_bond $kmod; then
				keep=1
			else
				echo "auto rmmod $kmod" >>/dev/kmsg
				rmmod_r $kmod
			fi
		done
	fi
	if [ "$keep" = "0" -a -n "$support" ]; then
		for kmod in $support; do
			rmmod $kmod 2>/dev/null
		done
	fi
}

boot() {
	config_load kmods
	config_foreach auto_unload auto_unload
}
