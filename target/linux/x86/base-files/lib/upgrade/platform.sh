# modified by jjm2473
# 1. keep overlay partition when upgrade
# 2. reset rom uuid in ext_overlay (aka sandbox mode) when upgrade (stage2:istoreos_pre_upgrade)

RAMFS_COPY_BIN='grub-bios-setup readlink'

platform_check_image() {
	local diskdev partdev diff
	[ "$#" -gt 1 ] && return 1

	case "$(get_magic_word "$1")" in
		eb48|eb63) ;;
		*)
			v "Invalid image type"
			return 1
		;;
	esac

	export_bootdevice && export_partdevice diskdev 0 || {
		v "Unable to determine upgrade device"
		return 1
	}

	# EFI non match will break grub
	if part_magic_efi "/dev/$diskdev"; then
		if ! part_magic_efi "$1"; then
			v "Flashing a non EFI image to EFI system!"
			return 1
		fi
	else
		if part_magic_efi "$1"; then
			v "Flashing a EFI image to non EFI system!"
			return 1
		fi
	fi

	[ "$SAVE_CONFIG" -eq 1 ] && return 0

	get_partitions "/dev/$diskdev" bootdisk

	v "Extract boot sector from the image"
	get_image_dd "$1" of=/tmp/image.bs count=63 bs=512b

	get_partitions /tmp/image.bs image

	#compare tables
	diff="$(grep -F -x -v -f /tmp/partmap.bootdisk /tmp/partmap.image)"

	rm -f /tmp/image.bs /tmp/partmap.bootdisk /tmp/partmap.image

	if [ -n "$diff" ]; then
		v "Partition layout has changed. Full image will be written."
		ask_bool 0 "Abort" && exit 1
		return 0
	fi
}

platform_do_bootloader_upgrade() {
	local bootpart parttable=msdos
	local diskdev="$1"

	if export_partdevice bootpart 1; then
		mkdir -p /tmp/boot
		mount -o rw,noatime "/dev/$bootpart" /tmp/boot
		echo "(hd0) /dev/$diskdev" > /tmp/device.map
		part_magic_efi "/dev/$diskdev" && parttable=gpt

		v "Upgrading bootloader on /dev/$diskdev..."
		grub-bios-setup \
			-m "/tmp/device.map" \
			-d "/tmp/boot/boot/grub" \
			-r "hd0,${parttable}1" \
			"/dev/$diskdev" \
		&& touch /tmp/boot/boot/grub/upgraded

		umount /tmp/boot
	fi
}

platform_do_upgrade() {
	local diskdev partdev diff

	export_bootdevice && export_partdevice diskdev 0 || {
		v "Unable to determine upgrade device"
		return 1
	}

	sync

	if [ "$UPGRADE_OPT_SAVE_PARTITIONS" = "1" -o -n "$UPGRADE_BACKUP" ]; then
		[ -n "$UPGRADE_BACKUP" ] || get_partitions "/dev/$diskdev" bootdisk

		v "Extract boot sector from the image"
		get_image_dd "$1" of=/tmp/image.bs count=63 bs=512b

		get_partitions /tmp/image.bs image

		if [ -n "$UPGRADE_BACKUP" ]; then
			#keep overlay partition when upgrade
			diff=
		else
			#compare tables
			diff="$(grep -F -x -v -f /tmp/partmap.bootdisk /tmp/partmap.image)"
		fi
	else
		diff=1
	fi

	if [ -n "$diff" ]; then
		grep /overlay /proc/mounts > /dev/null && {
			/bin/mount -o noatime,remount,ro /overlay
			/usr/bin/umount -R -d -l /overlay 2>/dev/null || /bin/umount -l /overlay
		}

		get_image_dd "$1" of="/dev/$diskdev" bs=4096 conv=fsync

		# Separate removal and addtion is necessary; otherwise, partition 1
		# will be missing if it overlaps with the old partition 2
		partx -d - "/dev/$diskdev"
		partx -a - "/dev/$diskdev"

		return 0
	fi

	#iterate over each partition from the image and write it to the boot disk
	while read part start size; do
		if [ -n "$UPGRADE_BACKUP" -a "$part" -ge 3 ]; then
			v "Skip partition $part >= 3 when upgrading"
			continue
		fi
		if export_partdevice partdev $part; then
			v "Writing image to /dev/$partdev..."
			if [ "$part" -eq 3 ]; then
				echo "RESET000" | dd of="/dev/$partdev" bs=512 count=1 conv=sync,fsync 2>/dev/null
			else
				get_image_dd "$1" of="/dev/$partdev" ibs=512 obs=1M skip="$start" count="$size" conv=fsync
			fi
		else
			v "Unable to find partition $part device, skipped."
		fi
	done < /tmp/partmap.image

	v "Writing new UUID to /dev/$diskdev..."
	get_image_dd "$1" of="/dev/$diskdev" bs=1 skip=440 count=4 seek=440 conv=fsync

	platform_do_bootloader_upgrade "$diskdev"
	local parttype=ext4
	part_magic_efi "/dev/$diskdev" || return 0

	if export_partdevice partdev 1; then
		part_magic_fat "/dev/$partdev" && parttype=vfat
		mount -t $parttype -o rw,noatime "/dev/$partdev" /mnt
		set -- $(dd if="/dev/$diskdev" bs=1 skip=1168 count=16 2>/dev/null | hexdump -v -e '8/1 "%02x "" "2/1 "%02x""-"6/1 "%02x"')
		sed -i "s/\(PARTUUID=\)[a-f0-9-]\+/\1$4$3$2$1-$6$5-$8$7-$9/ig" /mnt/boot/grub/grub.cfg
		umount /mnt
	fi
}
