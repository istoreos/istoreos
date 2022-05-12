#!/bin/sh
#
# Copyright (C) 2018 OpenWrt.org
#

. /lib/functions/uci-defaults.sh

board_config_update

ucidef_set_hostname "iStoreOS"

ucidef_set_ntpserver "0.cn.pool.ntp.org" "1.cn.pool.ntp.org" "2.cn.pool.ntp.org" "3.cn.pool.ntp.org"

board_config_flush

exit 0