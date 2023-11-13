#!/bin/sh

has_lcd_backlight() {
	local platform_path=$(cat /proc/device-tree/aliases/lcd-backlight 2>/dev/null)
	[ -n "$platform_path" ] || return 1
	local sys_device="/sys/devices/platform$platform_path"
	[ -d "$sys_device" ] || return 1
	BL_DEVPATH=$platform_path
	return 0
}

toggle_backlight() {
	local bl
	for bl in $(ls /sys/class/backlight/); do
		local devpath="$(grep '^OF_FULLNAME=' "/sys/class/backlight/$bl/device/uevent" | cut -d= -f2)"
		if [ "$devpath" = "$BL_DEVPATH" ]; then
			local old=$(cat "/sys/class/backlight/$bl/bl_power")
			echo "$(( 1 - $old ))" >"/sys/class/backlight/$bl/bl_power"
			return 0
		fi
	done
	return 1
}

if has_lcd_backlight; then
	case "$ACTION" in
	pressed)
		return 3
	;;
	timeout)
		. /etc/diag.sh
		set_state failsafe
	;;
	released)
		if [ "$SEEN" -lt 1 ]
		then
			toggle_backlight
		elif [ "$SEEN" -ge 3 ]
		then
			exec /sbin/poweroff
		fi
	;;
	esac

	return 0
fi

[ "${ACTION}" = "released" ] || exit 0

exec /sbin/poweroff

return 0
