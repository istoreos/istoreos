#!/bin/sh

uci -q batch <<-EOF >/dev/null
	delete ucitrack.@grub[-1]
	add ucitrack grub
	set ucitrack.@grub[-1].init=grub
	commit ucitrack
EOF

exit 0