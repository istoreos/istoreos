#!/bin/sh

mediaurlbase=
theme=

if [ -d /www/luci-static/argon_light_green -a -e /proc/device-tree/chosen/default-password ]; then
    mediaurlbase=/luci-static/argon_light_green
else
    for theme in argon argon_dark material ; do
        if [ -d /www/luci-static/$theme ]; then
            mediaurlbase=/luci-static/$theme
            break
        fi
    done
fi

if [ -n "$mediaurlbase" ]; then
    uci -q batch <<-EOF >/dev/null
        set luci.main.mediaurlbase=$mediaurlbase
        commit luci
EOF
fi

exit 0
