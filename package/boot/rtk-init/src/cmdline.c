/**
 * reverse enginering of zidoo z9s 2.1.30 /etc/init (sha256sum 9b3f9648460c15d345986b3246e0471057fb7d4af17fbba0b654f856e1a13e2a)
 */
#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mount.h>

#define BUF_SIZE 0x800

char CMDLINE[BUF_SIZE+1];// 0x412348

char *get_cmdline(const char *key, char *dest, int max) {
    if (CMDLINE[0] == '\0') {
        mount("proc", "/proc", "proc", MS_NOATIME|MS_NOEXEC|MS_NODEV|MS_NOSUID, NULL);
        int fd = open("/proc/cmdline", O_RDONLY);
        ssize_t len = read(fd, CMDLINE, BUF_SIZE);
        close(fd);
        umount("/proc");
        if (len > 0) { // 0x0040148c
            // 0x40149c
            CMDLINE[len] = '\0';
        } else {
            // 0x401494
            return NULL; // 0x1548
        }
    }
    if (dest != NULL) { // 0x14a0
        // 0x14a4
        *dest = '\0';
        char *ptr = NULL;
        char *kv = strtok_r(CMDLINE, " \t\n", &ptr); // x20
        size_t maxlen = max;
        while (kv != NULL) {
            // 0x14d0
            char *ke = strchr(kv, '=');
            size_t klen = ke - kv;
            kv[strlen(kv)] = ' ';
            if (klen >= 0 && !strncmp(key, kv, klen) && !key[klen]) {
                // 0x1510
                strncpy(dest, ke + 1, maxlen); //0x151c
                dest[maxlen - 1] = '\0'; //0x1520
            }
            // 0x1524
            kv = strtok_r(NULL, " \t\n", &ptr);
            // 0x00401538 : b 0x4014cc
            //continue;
        }
        // 0x153c
        if (dest[0] != '\0') {
            return dest;
        }
        //  else {
        //     // 0x1494
        //     return NULL;
        // }
    }
    // 0x1494
    return NULL;// 0x1548
}