#!/bin/sh

[ -f /etc/config/kmods ] || exit 0

uci -q batch <<-EOF >/dev/null
	delete kmods.rtw89
	set kmods.rtw89=auto_unload
	set kmods.rtw89.function="rtw_8851be rtw_8852ae rtw_8852be rtw_8852ce"
	set kmods.rtw89.support="rtw_8852c rtw_8852b rtw_8852a rtw_8851b rtw89pci rtw89core"

	commit kmods
EOF
