
# bins for install_a
RAMFS_COPY_BIN="/usr/bin/cat /usr/bin/chmod /usr/bin/cp /usr/bin/dd \
/usr/bin/echo /usr/bin/mkdir /usr/bin/rm /usr/bin/umount"

platform_check_image() {
	echo "platform_check_image"
	echo "image path/url: $1"

	if [ "$KEEP_ALIVE" -ne 0 ]; then
		get_image "$@" | tar -Ox config.txt | grep rootfs || return 1
	fi

	return 0
}

platform_pre_upgrade() {
	if [ -n "$UPGRADE_BACKUP" ]; then
		if [ -e /ext_overlay/etc ]; then
			rm -f /ext_overlay/etc/.extroot-uuid
			rm -f /ext_overlay/upper/usr/lib/opkg/.upgrading
			sync /ext_overlay
		fi
		touch /overlay/upper/usr/lib/opkg/.upgrading && sync /overlay
	fi
}

platform_do_upgrade() {
	grep /ext_overlay /proc/mounts > /dev/null && {
		/bin/mount -o noatime,remount,ro /ext_overlay
		/usr/bin/umount -R -d -l /ext_overlay || /bin/umount -l /ext_overlay
	}

	# $1: image path/url
	echo "platform_do_upgrade start"
	echo "image path/url: $1"

	[ -n "$UPGRADE_BACKUP" ] && OPT="-o UPGR____ -r" || OPT="-r"

	cd /\
		&& tar -C /tmp -xvf $1 install_a \
		&& echo "/tmp/install_a $OPT $1" \
		&& /tmp/install_a $OPT $1

	echo "platform_do_upgrade end"
}

platform_copy_config() {
	echo "platform_copy_config: nothing to do"
}
