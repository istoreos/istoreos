#!/bin/sh /etc/rc.common
# 2022 jjm2473

START=99

boot() {
	# tune printk level after success boot, avoid noise in console
	echo '4 5 1 7' > /proc/sys/kernel/printk

	# notify console system is ready
	sleep 1
	if pgrep -P 1 askfirst >/dev/null; then
		echo "iStoreOS is ready!" >/dev/console
		echo "Please press Enter to activate this console." >/dev/console
	fi
}
