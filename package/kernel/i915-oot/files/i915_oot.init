#!/bin/sh /etc/rc.common

START=09

boot() {
	local kmod
	local enable="$( uci -q get kmods.kmods.enable )"
	if echo "$enable" | grep -qFw "i915-oot" || is_white_list; then
		local FAILFILE=/etc/config/.i915_boot
		local count=$(cat $FAILFILE)
		[[ -n "$count" ]] || count=0
		[[ $count -le 2 ]] || return 0
		count=$(( $count + 1 ))
		echo "$count" > $FAILFILE
		sync $FAILFILE
		[[ $count -le 2 ]] || return 0

		local release="$(uname -r)"
		[[ -n "$release" ]] || return 0
		ls /lib/modules/$release/i915-oot/ 2>/dev/null | while read kmod; do
			if [[ "$kmod" = "*.ko" ]]; then
				[[ -f /lib/modules/$release/$kmod ]] || continue
				mount --bind /lib/modules/$release/i915-oot/$kmod /lib/modules/$release/$kmod
			else
				if [[ -f /etc/modules.d/$kmod ]]; then
					mount --bind /lib/modules/$release/i915-oot/$kmod /etc/modules.d/$kmod
				else
					local target=$(ls /etc/modules.d/ 2>/dev/null | grep "^[0-9_-]*-$kmod\$" | head -1)
					[[ -n "$target" ]] || continue
					mount --bind /lib/modules/$release/i915-oot/$kmod /etc/modules.d/$target
				fi
			fi
		done
	fi
}

is_white_list() {
	grep -qFw 0x8086 /sys/devices/pci0000:00/0000:00:02.0/vendor || return 1
	[[ "$(($(cat /sys/devices/pci0000:00/0000:00:02.0/class) & 0xff0000 ^ 0x030000))" = "0" ]] || return 1
	white_list | grep -v '^#' | tr '[A-Z]' '[a-z]' | sed 's/^\</0x/' | \
		grep -qFf /sys/devices/pci0000:00/0000:00:02.0/device || return 1
	echo "$(cat /sys/devices/pci0000:00/0000:00:02.0/device) is in i915-oot white list" >>/dev/kmsg
	return 0
}

white_list() {
	echo '
# TGL
9A60
9A68
9A70
9A40
9A49
9A59
9A78
9AC0
9AC9
9AD9
9AF8
# RKL
4C80
4C8A
4C8B
4C8C
4C90
4C9A
# DG1
4905
4906
4907
4908
4909
# ADL-S
4680
4682
4688
468A
468B
4690
4692
4693
# ADL-P
46A0
46A1
46A2
46A3
46A6
46A8
46AA
462A
4626
4628
46B0
46B1
46B2
46B3
46C0
46C1
46C2
46C3
# ADL-N
46D0
46D1
46D2
# RPL-S
A780
A781
A782
A783
A788
A789
A78A
A78B
# RPL-P
A720
A721
A7A0
A7A1
A7A8
A7A9
# DG2
5690
5691
5692
56A0
56A1
56A2
5693
5694
5695
56A5
56A6
56B0
56B1
5696
5697
56A3
56A4
56B2
56B3
56C0
56C1
# MTL
7D40
7D60
7D45
7D55
7DD5
# PVC
0B69
0BD0
0BD5
0BD6
0BD7
0BD8
0BD9
0BDA
0BDB
'
}
