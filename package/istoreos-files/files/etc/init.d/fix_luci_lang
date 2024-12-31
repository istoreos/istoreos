#!/bin/sh /etc/rc.common
# Copyright (C) 2016 OpenWrt.org

START=49

list_langs() {
	cd /usr/lib/lua/luci/i18n
	ls | sed -e 's/.*\.\([^\.]*\)\.lmo/\1/g' | sort -u
}

boot() {
	local lang
	local name
	for lang in `list_langs`
	do
		if ! uci get luci.languages.${lang//-/_} >/dev/null 2>&1; then
			name=`luci18n2name $lang`
			uci set "luci.languages.${lang//-/_}=${name:-$lang}"
		fi
	done
	uci changes luci | grep -Fqm1 luci 2>/dev/null && uci commit luci >/dev/null 2>&1
}