#!/bin/sh

CFG="${CFG:-/etc/board.json}"

. /lib/functions/uci-defaults.sh

board_config_update

if json_is_a network object; then
    [ "$1" = "-k" ] && exit 0
    # Create new network object
    json_add_object "network"
    json_close_object
    # Fix duplicate "network" in jshn.sh's K_J_V, which generates invalid network object
    _json_get_var FIELDS K_J_V
    _json_set_var K_J_V "$(echo $FIELDS | sed 's/ network//g' ) network"
    unset FIELDS
fi

INTERFACES=$(ls /sys/class/net/ | grep eth)
ETHNUM=$(echo $INTERFACES | wc -w)
[ $ETHNUM -eq 0 ] && exit 0

if [ $ETHNUM -eq 1 ]; then
    ucidef_set_interface_lan 'eth0' 'dhcp'
else
    ucidef_set_interface_wan 'eth0'
    lan_interface=""
    for eth_interface in $INTERFACES; do
        [ "$eth_interface" = "eth0" ] || lan_interface="$lan_interface $eth_interface"
    done
    [ -n "$lan_interface" ] && ucidef_set_interface_lan "$lan_interface"
fi

board_config_flush

[ -s $CFG ] || {
    echo "Board config file $CFG is empty!" >&2
    exit 1
}

dhcp_default_duid=$(uci -q get network.globals.dhcp_default_duid)
ula_prefix=$(uci -q get network.globals.ula_prefix)

rm -f /etc/config/network

/bin/config_generate >/dev/null || exit 1

if [ -n "$dhcp_default_duid" ]; then
    uci -q set network.globals.dhcp_default_duid="$dhcp_default_duid"
fi

if [ -n "$ula_prefix" ]; then
    uci -q set network.globals.ula_prefix="$ula_prefix"
fi
uci -q commit network

[ "$1" = "-k" ] || /etc/init.d/network reload
