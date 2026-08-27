REQUIRE_IMAGE_METADATA=1
RAMFS_COPY_BIN='fitblk fit_check_sign'

platform_do_upgrade() {
	local board=$(board_name)

	case "$board" in
		gemtek,w1700k-ubi)
			fit_do_upgrade "$1"
			;;
		econet,xr1710g-ubi)
			IGNORE_ROOTFS_DATA_MAX=1 \
			CI_REMOVE_UBIVOLS="config log" \
			fit_do_upgrade "$1"
			;;
		*)
			nand_do_upgrade "$1"
			;;
	esac
}

platform_check_image() {
	return 0
}
