#!/bin/sh /etc/rc.common

START=00

boot() {
	if [ -e /sys/class/rtc/rtc1/device/modalias ]; then
		grep -q 'rk808-rtc' /sys/class/rtc/rtc1/device/modalias || ln -s rtc1 /dev/rtc
	fi
}
