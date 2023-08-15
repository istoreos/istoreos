#!/bin/sh
# Copyright (C) 2022 jjm2473@gmail.com
action=${1}
shift

disable_if_sandbox()
{
	local enabled
	local target
	config_get target $1 "target" "/tmp/null"
	[ "$target" = "/overlay" ] || return
	config_get_bool enabled $1 "enabled" "0"
	[ "$enabled" = 1 ] && uci_set fstab $1 "enabled" "0"
}

disable_all_sandbox()
{
	. /lib/functions.sh
	uci_load "fstab"
	config_foreach disable_if_sandbox mount
	uci_commit "fstab"
}

exit_sandbox()
{
	UCI_CONFIG_DIR=/overlay/upper/etc/config disable_all_sandbox
}

reset_sandbox()
{
	touch /ext_overlay/.reset && sync /ext_overlay
}

commit_sandbox()
{
	touch /ext_overlay/.commit && sync /ext_overlay
}

usage() {
    echo "Usage: sandbox sub-command"
    echo "where sub-command is one of:"
    echo "      reset              Reset sandbox"
    echo "      commit             Commit sandbox"
    echo "      exit               Exit sandbox"
}

if grep '^overlayfs:/overlay / ' /proc/mounts | grep -Fq 'upperdir=/ext_overlay/upper'; then
	case $action in
		"reset")
			reset_sandbox
		;;
		"commit")
			commit_sandbox
		;;
		"exit")
			exit_sandbox
		;;
		"status")
			exit 0
		;;
		*)
			usage >&2
			exit 1
		;;
	esac
else
	echo "Not sandbox environment" >&2
	exit 1
fi
