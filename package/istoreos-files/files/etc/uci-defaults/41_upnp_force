#!/bin/sh

uci -q batch <<-EOF >/dev/null
    delete upnpd.config.use_stun
    set upnpd.config.stun_host='stun.sipgate.net'
    set upnpd.config.force_forwarding='1'
    commit upnpd
EOF

exit 0
