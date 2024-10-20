#!/bin/sh

. /lib/functions/leds.sh
. /lib/functions/uci-defaults.sh

board=$(board_name)
boardname="${board##*,}"

board_config_update

case $board in
firefly,rk3568-roc-pc)
	ucidef_set_led_timer "health" "health" "firefly:yellow:user" "200" "800"
	;;
friendlyelec,nanopi-r3s)
	ucidef_set_led_netdev "wan" "WAN" "wan_led" "eth0"
	ucidef_set_led_netdev "lan" "LAN" "lan_led" "eth1"
	;;
friendlyelec,nanopi-r5s|friendlyelec,nanopi-r5s-c1)
	ucidef_set_led_netdev "wan" "WAN" "green:wan" "eth0"
	ucidef_set_led_netdev "lan1" "LAN1" "green:lan1" "eth1"
	ucidef_set_led_netdev "lan2" "LAN2" "green:lan2" "eth2"
	;;
friendlyelec,nanopi-r6s)
	ucidef_set_led_netdev "wan" "WAN" "green:wan" "eth1"
	ucidef_set_led_netdev "lan1" "LAN1" "green:lan1" "eth2"
	ucidef_set_led_netdev "lan2" "LAN2" "green:lan2" "eth0"
	;;
friendlyelec,nanopi-r6c)
	ucidef_set_led_netdev "wan" "WAN" "green:wan" "eth0"
	ucidef_set_led_netdev "lan" "LAN" "green:lan1" "eth1"
	;;
friendlyelec,nanopi-r5c)
	ucidef_set_led_netdev "wan" "WAN" "green:wan" "eth0"
	ucidef_set_led_netdev "lan1" "LAN1" "green:lan1" "eth1"
	;;
easepi,ars4|\
hinlink,h88k-*|\
hinlink,h88k|\
hinlink,hnas|\
hinlink,opc-h69k|\
hinlink,opc-h68k|\
hinlink,opc-h66k)
	ucidef_set_led_netdev "wan" "WAN" "blue:net" "eth0"
	ucidef_set_led_ide "disk" "DISK" "yellow:disk"
	;;
hlink,h28k)
	ucidef_set_led_default "power" "POWER" "green:work" "1"
	ucidef_set_led_netdev "wan" "WAN" "yellow:led3" "eth1"
	ucidef_set_led_netdev "lan" "LAN" "blue:led4" "eth0"
	;;
lyt,t68m)
	ucidef_set_led_timer "health" "health" "t68m:red:user" "200" "800"
	;;
nlnet,xgp)
	ucidef_set_led_timer "sys" "SYS" "blue:sys" "200" "800"
	;;
radxa,e20c)
	ucidef_set_led_netdev "wan" "WAN" "green:wan" "eth1"
	ucidef_set_led_netdev "lan" "LAN" "green:lan" "eth0"
	;;
radxa,e52c)
	ucidef_set_led_netdev "wan" "WAN" "green:wan" "eth0"
	ucidef_set_led_netdev "lan" "LAN" "green:lan" "eth1"
	;;
radxa,e54c)
	ucidef_set_led_switch "wan" "wan" "green:wan" "switch0" "0x8"
	ucidef_set_led_switch "lan1" "lan1" "green:lan:1" "switch0" "0x4"
	ucidef_set_led_switch "lan2" "lan2" "green:lan:2" "switch0" "0x2"
	ucidef_set_led_switch "lan3" "lan3" "green:lan:3" "switch0" "0x1"
	;;
armsom,p2pro)
	ucidef_set_led_netdev "wlan" "WLAN" "blue:user" "wlan0"
	;;
esac

board_config_flush

exit 0
