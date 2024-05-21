#!/bin/sh
# author jjm2473

mirrors() {
    local url="$1"
    case "$url" in
        https://fw0.koolcenter.com/iStoreOS/*|\
        https://fw.koolcenter.com/iStoreOS/*)
            local path=$(echo "$url" | sed -E 's#^https?://[^/]+/(.*)#\1#')
            # echo "https://dl2.istoreos.com/$path"
            echo "https://dl.istoreos.com/$path"
        ;;
    esac
    echo "$url"
    return 0
}

if [ -f /lib/upgrade/ota.sh ]; then
    . /lib/upgrade/ota.sh
    export_ota_url
fi

if [ -z "$OTA_URL_BASE" ]; then
    echo "Unsupported device." >&2
    exit 255
fi

WRLOCK=/var/lock/ota_background.lock
STLOCK=/var/lock/ota_status.lock

action=${1}
shift

sha256() {
    sha256sum $1 | cut -d' ' -f1
}

alias fcurl='curl -L --fail --show-error'

download() {
    local img=$1
    local sum=$2
    exec 300>$STLOCK
    flock 300
    touch /tmp/firmware.img.part
    echo >/tmp/firmware.img.progress
    rm -f /tmp/firmware.img.sha256sum
    flock -u 300
    if [ -f /tmp/firmware.img ]; then
        echo "Checking existed firmware.img..." >> /tmp/firmware.img.progress
        if [ "`sha256 /tmp/firmware.img`" = "$sum" ]; then
            flock 300
            echo $sum > /tmp/firmware.img.sha256sum;
            rm -f /tmp/firmware.img.part
            rm -f /tmp/firmware.img.progress
            flock -u 300
            return 0;
        else
            echo "Check failed, redownload" >> /tmp/firmware.img.progress
            rm -f /tmp/firmware.img
        fi
    fi
    local pid url
    mirrors "$OTA_URL_BASE/$img" | while read; do
        url="$REPLY"
        echo "Try $url" >>/tmp/firmware.img.progress
        flock 300
        echo "#=#=#" >>/tmp/firmware.img.progress
        fcurl --connect-timeout 5 --progress-bar -o /tmp/firmware.img.part "$url" 2>>/tmp/firmware.img.progress &
        pid="$!"
        echo "$pid" > /var/run/ota/download.pid
        flock -u 300
        if wait $pid; then
            rm -f /var/run/ota/download.pid
            echo "Checking new firmware.img.part..." > /tmp/firmware.img.progress
            if [ "`sha256 /tmp/firmware.img.part`" = "$sum" ]; then
                flock 300
                mv /tmp/firmware.img.part /tmp/firmware.img && echo $sum > /tmp/firmware.img.sha256sum
                rm -f /tmp/firmware.img.progress
                flock -u 300
                return 0
            else
                echo "Checksum failed!" >>/tmp/firmware.img.progress
            fi
        else
            # on Terminated $? == 143, on Timeout $? == 28
            local ecode=$?
            echo >>/tmp/firmware.img.progress
            if [ $ecode -eq 143 ]; then
                echo "Canceled!" >> /tmp/firmware.img.progress
                break
            fi
        fi
        flock 300
        sed -i '/\r/d' /tmp/firmware.img.progress
        flock -u 300
    done
    rm -f /var/run/ota/download.pid
    rm -f /tmp/firmware.img.part
    return 1
}

lock_download() {
    local lock="$WRLOCK"
    exec 200>$lock
    flock -n 200 || return
    download $1 $2
    flock -u 200
}

prepare_check() {
    local line
    local release=`grep 'DISTRIB_RELEASE=' /etc/openwrt_release | sed -E "s/.*'(.+)'.*/\1/"`
    local revision=`grep 'DISTRIB_REVISION=' /etc/openwrt_release | sed -E "s/.*'(.+)'.*/\1/" | cut -d'-' -f1`
    local current="$release-$revision"
    local latest=0
    cat /dev/null > /var/run/ota/ota.log
    fcurl --connect-timeout 5 -o /var/run/ota/ota.latest "$OTA_URL_BASE/version.latest" || { rm -f /var/run/ota/ota.latest ; return 255; }
    if head -1 /var/run/ota/ota.latest | grep -Fq "$current"; then
        latest=1
        current=""
    fi
    fcurl --connect-timeout 5 -o /var/run/ota/ota.index "$OTA_URL_BASE/version.index" || return 255;
    head -5 /var/run/ota/ota.index | while read line; do
        if [ -z "$line" -o "$line" = "$current" ]; then
            break
        fi
        echo "<h3>`echo $line | sed 's/-/ /'`</h3><pre>" >> /var/run/ota/ota.log
        fcurl --connect-timeout 1 "$OTA_URL_BASE/log/$line.log" >> /var/run/ota/ota.log 2>/dev/null
        echo "</pre>" >> /var/run/ota/ota.log
    done
    [ "`wc -l /var/run/ota/ota.log | cut -d' ' -f1`" -eq 0 ] && return 1
    [ "`wc -l /var/run/ota/ota.index | cut -d' ' -f1`" -gt 5 ] && echo "<a href=\"$OTA_URL_BASE/\" onclick=\"void(0)\" target=\"_blank\">More</a>" >> /var/run/ota/ota.log
    fcurl --connect-timeout 1 "$OTA_URL_BASE/ota.footer.html" >> /var/run/ota/ota.log 2>/dev/null
    return $latest
}

# 0: found newer fw, 1: already newest fw, 2: found running task, *: err
do_check() {
    local ret=0
    local lock="$WRLOCK"
    exec 200>$lock
    if flock -n 200; then
        prepare_check
        ret=$?
        flock -u 200 >/dev/null 2>&1
    elif [ -f /tmp/firmware.img.progress -o -f /tmp/firmware.img.sha256sum ]; then
        ret=2
    else
        echo "lock failed!" >&2
        return 255
    fi

    if [ "$ret" -eq 0 -o "$ret" -eq 2 ]; then
        # output
        echo "<pre>"
        sed -E '1 s/^\[.*\]\((.+)\)\s*$/\1/' /var/run/ota/ota.latest
        echo "</pre>"
        echo "<br><h2>ChangeLog:</h2>"
    fi
    [ "$ret" -eq 0 -o "$ret" -eq 1 -o "$ret" -eq 2 ] && cat /var/run/ota/ota.log
    return $ret
}

# async download
do_download(){
    local img=`head -1 /var/run/ota/ota.latest | sed -E 's/.*\((.+)\).*/\1/'`
    local sum=`head -3 /var/run/ota/ota.latest | grep '^SHA256: ' | cut -d' ' -f2`
    [ -z "$img" -o -z "$sum" ] && { echo "do check first" >&2 ; return 254; }
    lock_download $img $sum &
    return 0
}

# 0: done, 1: downloading, 2: failed, 254: wrong state, *: err
do_progress() {
    local sum=`head -3 /var/run/ota/ota.latest | grep '^SHA256: ' | cut -d' ' -f2`
    [ -z "$sum" ] && { echo "do check first" >&2 ; return 254; }
    [ -f /tmp/firmware.img.sha256sum ] && [ "`cat /tmp/firmware.img.sha256sum`" = "$sum" ] && return 0
    [ -f /tmp/firmware.img.progress ] || { echo "download not in progress" >&2 ; return 254; }
    [ -f /tmp/firmware.img.part ] && { cat /tmp/firmware.img.progress | tr '\r' '\n' | tail -n1; return 1; }
    tail -1 /tmp/firmware.img.progress | grep -Fq 'Canceled!' && { echo "Canceled"; return 2; }
    cat /tmp/firmware.img.progress | tr '\r' '\n' | grep -v '^$' | tail -n1 >&2
    return 3
}

do_progress_locked() {
    local ret
    exec 300>$STLOCK
    flock -s 300
    do_progress
    ret=$?
    flock -u 300
    return $ret
}

do_cancel() {
    if [ -f /var/run/ota/download.pid ]; then
        local pid=`cat /var/run/ota/download.pid`
        if [ -n "$pid" ]; then
            kill -TERM $pid;
            while kill -0 $pid >/dev/null 2>&1; do
                if ! sleep 1; then
                    break
                fi
            done
        fi
    fi
    return 0
}

ota_init(){
    mkdir -p /var/run/ota >/dev/null 2>&1 || true
}

usage() {
    echo "usage: ota sub-command"
    echo "where sub-command is one of:"
    echo "      check                  Check firmware upgrade"
    echo "      download               Download latest firmware"
    echo "      progress               Download progress"
    echo "      cancel                 Cancel download"
}

ota_init || exit 255

case $action in
    "check")
        do_check
    ;;
    "download")
        do_download
    ;;
    "progress")
        do_progress_locked
    ;;
    "cancel")
        do_cancel
    ;;
    *)
        usage
    ;;
esac
