
export_ota_url() {
    local partition_type=$(. /lib/upgrade/common.sh; export_bootdevice && export_partdevice diskdev 0 || exit 0; blkid -o value -s PTTYPE /dev/$diskdev)
    case "$partition_type" in
    "gpt")
        export -n OTA_URL_BASE="https://fw0.koolcenter.com/iStoreOS/x86_64_efi"
    ;;
    "dos")
        export -n OTA_URL_BASE="https://fw0.koolcenter.com/iStoreOS/x86_64"
    ;;
    *)
        return 1
    ;;
    esac
}
