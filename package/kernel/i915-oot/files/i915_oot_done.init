#!/bin/sh /etc/rc.common

START=13

boot() {
	local FAILFILE=/etc/config/.i915_boot
	local enable="$( uci -q get kmods.kmods.enable )"
	if echo "$enable" | grep -qFw "i915-oot" ; then
		local count=$(cat $FAILFILE)
		[[ -n "$count" ]] || count=0
		if [[ $count -gt 2 ]]; then
			logger -t 'i915-oot' "disable i915-oot for kernel crashed $(( $count - 1 )) times"
			uci -q del_list kmods.kmods.enable=i915-oot
			uci commit kmods
		fi
	fi
	rm -f $FAILFILE
	sync /etc/config
}
