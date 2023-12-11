#!/bin/sh /etc/rc.common

START=09

boot() {
	if grep -qFw rockchip,rk3588 /proc/device-tree/compatible ; then
		local kmod
		local release="$(uname -r)"
		[[ -n "$release" ]] || return 0
		ls /lib/modules/$release/bifrost-csf/ 2>/dev/null | while read kmod; do
			if [[ "$kmod" = "*.ko" ]]; then
				[[ -f /lib/modules/$release/$kmod ]] || continue
				mount --bind /lib/modules/$release/bifrost-csf/$kmod /lib/modules/$release/$kmod
			else
				if [[ -f /etc/modules.d/$kmod ]]; then
					mount --bind /lib/modules/$release/bifrost-csf/$kmod /etc/modules.d/$kmod
				else
					local target=$(ls /etc/modules.d/ 2>/dev/null | grep "^[0-9_-]*-$kmod\$" | head -1)
					[[ -n "$target" ]] || continue
					mount --bind /lib/modules/$release/bifrost-csf/$kmod /etc/modules.d/$target
				fi
			fi
		done
	fi
}
