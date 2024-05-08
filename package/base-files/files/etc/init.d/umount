#!/bin/sh /etc/rc.common
# Copyright (C) 2006 OpenWrt.org

STOP=90

shutdown() {
	if [ ! -f /rom/rom/note ]; then
		sync /overlay
		umount /overlay
		sync /ext_overlay
		umount /ext_overlay
	else
		# pivot
		mount --make-private / 2>&-
		mount --make-private /tmp 2>&-
		mount --make-private /mnt 2>&-
		mount --make-private /overlay 2>&-
		mount --make-private /ext_overlay 2>&-
		mount --move /dev /rom/dev
		mount --move /tmp /rom/tmp
		mount --move /sys /rom/sys
		mount --move /ext_overlay /rom/ext_overlay
		mount --move /overlay /rom/overlay
		mount --move /proc /rom/proc
		if pivot_root /rom /rom/mnt; then
			echo "<1>umount: pivot_root success" >/dev/kmsg
			sync
			/usr/bin/umount -R -d /mnt
			sync /mnt
			umount /mnt
			sync /overlay
			umount /overlay
			sync /ext_overlay
			umount /ext_overlay
		else
			echo "<1>umount: pivot_root failed!" >/rom/dev/kmsg
			mount --move /rom/proc /proc
			mount --move /rom/dev /dev
			mount --move /rom/tmp /tmp
			mount --move /rom/sys /sys
			mount --move /rom/ext_overlay /ext_overlay
			mount --move /rom/overlay /overlay
			sync
		fi
	fi
	sync
	echo 2 > /proc/sys/vm/drop_caches
	/bin/umount -a -d -r
}
