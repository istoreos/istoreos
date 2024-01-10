#!/bin/sh

mdadm_hack() {
	[ -f /proc/mdstat ] || modprobe md_mod
	mount --bind /dev/full /sys/module/md_mod/parameters/new_array
}

mdadm_hack