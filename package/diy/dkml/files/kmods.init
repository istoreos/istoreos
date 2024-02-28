#!/bin/sh /etc/rc.common

START=09

enable_kmod() {
	local kmod="$1"
	sed -i "/^blacklist $kmod\$/d" /etc/modules.conf
}

disable_kmod() {
	local kmod="$1"
	grep -q "^blacklist $kmod\$" /etc/modules.conf || {
		[ -n "$(tail -c1 /etc/modules.conf)" ] && echo >> /etc/modules.conf
		echo "blacklist $kmod" >> /etc/modules.conf
	}
}

boot() {
	local info kmod action p1 ignore
	local enable="$( uci -q get kmods.kmods.enable )"
	ls /etc/modules-pending.d/ 2>/dev/null | while read info; do
		if echo "$enable" | grep -qFw "$info" ; then
			action=enable_kmod
		else
			action=disable_kmod
		fi
		echo "$action.group $info" >>/dev/kmsg
		while read p1 ignore; do
			kmod=$(echo "$p1" | grep -o '^[^#]*')
			if [[ -n "$kmod" ]]; then
				echo "$action $kmod" >>/dev/kmsg
				$action $kmod
			fi
		done < "/etc/modules-pending.d/$info"
	done
}
