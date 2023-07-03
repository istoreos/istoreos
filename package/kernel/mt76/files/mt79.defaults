#!/bin/sh
# Copyright (C) 2023 jjm2473@gmail.com

[ -f /lib/wifi/mac80211.sh ] || exit 0

. /lib/functions.sh
DRIVERS=
. /lib/wifi/mac80211.sh

patch_if_mt79()
{
    local type
    local path
    local module
    config_get type "$1" "type"
    [[ "$type" = "mac80211" ]] || return 0

	local device="$1"
    local phy=
    lookup_phy
    [[ -n "$phy" ]] || return 0
    [ -h "/sys/class/ieee80211/$phy/device/driver" ] || return 0

    path="$(readlink "/sys/class/ieee80211/$phy/device/driver")"
    module="${path##*/}"
    [[ "$module" = "mt79*" ]] || return 0

    local country
    config_get country "$1" "country"

    [[ -n "$country" ]] || uci_set "wireless" "$1" country "CN"
}

patch_all_config()
{
    config_load "wireless"
    config_foreach patch_if_mt79 wifi-device
    uci_commit "wireless"
}

if [ -f /etc/config/wireless ]; then
    sleep 1
    patch_all_config
fi

exit 0
