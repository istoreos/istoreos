
export_ota_url() {
    local partition_type=`blkid -o value -s PTTYPE $(lsblk -s -r -p $(blkid -L "kernel")| grep disk | cut -d' ' -f1)`
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
