#!/bin/sh /etc/rc.common

START=99

boot() {
	return 0
}

grub_iommu_conf() {
	local enabled cmdline
	config_get enabled iommu enabled 0
	if [ "$enabled" = 1 ]; then
		config_get cmdline iommu cmdline
		if [ -z "$cmdline" ]; then
			if grep -Fq Intel /proc/cpuinfo; then
				cmdline="intel_iommu=on iommu=pt"
			else
				cmdline="amd_iommu=on iommu=pt"
			fi
		fi
		grub-editenv - set IOMMU_CMDLINE="$cmdline"
	else
		grub-editenv - unset IOMMU_CMDLINE
	fi
}

grub_concat_cmdlines() {
	local enabled cmdline
	config_get_bool enabled "$1" enabled 0
	[ "$enabled" = 1 ] || return 0
	config_get cmdline "$1" cmdline
	[ -n "$cmdline" ] || return 0
	CUSTOM_CMDLINE="$CUSTOM_CMDLINE $cmdline"
}

start() {
	local enabled cmdline
	config_load grub
	[ -e /etc/grub.cfg.d/01-iommu.cfg ] && grub_iommu_conf
	CUSTOM_CMDLINE=""
	config_foreach grub_concat_cmdlines cmdline
	if [ -n "$CUSTOM_CMDLINE" ]; then
		grub-editenv - set CUSTOM_CMDLINE="${CUSTOM_CMDLINE## }"
	else
		grub-editenv - unset CUSTOM_CMDLINE
	fi
	update-grub || true
}
