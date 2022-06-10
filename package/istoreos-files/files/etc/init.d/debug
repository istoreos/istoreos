#!/bin/sh /etc/rc.common
# Copyright (C) 2006 OpenWrt.org

STOP=00

shutdown() {
	logger -s -t "DEBUG" "System Shutting Down"
	logger -t "DEBUG" "System Shutting Down"

	# blink led
	. /etc/diag.sh
	[ -n "$running" ] && {
		status_led="$running"
		status_led_blink_preinit_regular
	}
}
