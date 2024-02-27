#!/bin/sh /etc/rc.common
# istoreos upgrade post process
# Copyright (C) 2022 jjm2473

START=14

split_opkg_status() {
	local line
	local gap=1
	exec 3>/dev/null
	rm -rf $2
	mkdir -p $2
	cat $1 | while read; do
		line="$REPLY"
		if [ -z "$line" ]; then
			echo >&3
			exec 3>&-
			exec 3>/dev/null
			gap=1
		else
			if [[ "x1" = "x$gap" && "$line" = "Package: *" ]]; then
				exec 3>&-
				exec 3>$2/${line##Package: }
				gap=0
			fi
			echo "$line" >&3
		fi
	done
	exec 3>&-
}

split_both_status() {
	split_opkg_status /usr/lib/opkg/status /tmp/newopkgstatus &
	split_opkg_status /rom/usr/lib/opkg/status /tmp/romopkgstatus &
	wait
}

ls_all_pkgs() {
	( cd /usr/lib/opkg/info ; find . -maxdepth 1 -name '*.control' | sed -E 's#./(.*).control#\1#g' | grep -v '^kernel$' )
}

rebuild_opkg_status() {
	local line
	[ -f /tmp/romopkgstatus/kernel ] && cat /tmp/romopkgstatus/kernel
	ls_all_pkgs | while read line; do
		if [ -f /overlay/upper/usr/lib/opkg/info/$line.control -o -f /ext_overlay/upper/usr/lib/opkg/info/$line.control ]; then
			echo /tmp/newopkgstatus/$line
		else
			echo /tmp/romopkgstatus/$line
		fi
	done | xargs cat
}

clean_tmp_files() {
	rm -rf /tmp/newopkgstatus
	rm -rf /tmp/romopkgstatus
}

clean_themes() {
	local line
	local name
	local path
	uci show luci.themes | tail -n +2 | sed "s/^luci.themes.//g; s/'//g" | while read; do
		line="$REPLY"
		name=`echo "$line" | cut -d= -f 1`
		path=`echo "$line" | cut -d= -f 2`
		[ "x$path" != "x" -a -d /www$path ] || uci delete "luci.themes.$name"
	done
	uci commit luci
}

is_overlayed() {
	[ -e "/overlay/upper$1" -o -e "/ext_overlay/upper$1" ]
}

upgrade_opkg_distfeeds() {
	local newrelease=$(grep -m1 '/base$' /rom/etc/opkg/distfeeds.conf | grep -Eo '/releases/[^/]+/')
	local oldrelease=$(grep -m1 '/base$' /etc/opkg/distfeeds.conf | grep -Eo '/releases/[^/]+/')
	[ -z "$newrelease" -o -z "$oldrelease" ] && return 0
	[ "$newrelease" = "$oldrelease" ] && return 0
	sed -i -e 's#'"$oldrelease"'#'"$newrelease"'#g' /etc/opkg/distfeeds.conf
}

boot() {
	[ -f /.recovery_mode ] && return 0

	if [ -f /usr/lib/opkg/.upgrading ]; then
		rm -f /usr/lib/opkg/.upgrading
		is_overlayed /usr/lib/opkg/status && {
			split_both_status
			rebuild_opkg_status > /usr/lib/opkg/status
			clean_tmp_files
		}
		is_overlayed /etc/config/luci && {
			clean_themes
		}
		is_overlayed /etc/opkg/distfeeds.conf && {
			upgrade_opkg_distfeeds
		}
	fi
	rm -f /overlay/upper/.upgrading
}
