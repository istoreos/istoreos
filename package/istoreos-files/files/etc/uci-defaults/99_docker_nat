#!/bin/sh

uci -q get firewall.docker_nat >/dev/null || uci -q batch <<-EOF
	set firewall.docker_nat=nat
	set firewall.docker_nat.name='DockerNAT'
	set firewall.docker_nat.proto='all'
	set firewall.docker_nat.src='lan'
	set firewall.docker_nat.target='MASQUERADE'
	set firewall.docker_nat.extra='-i docker0'
	commit firewall
EOF

exit 0
