/*
 * @author jjm2473
 * @since 2021-03-15
 */

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "hash.h"

ssize_t syncread(int fd, void *buf, size_t nbytes) {
  ssize_t size;
  while (1) {
    if ((size = read(fd, buf, nbytes)) >= 0 || errno != EAGAIN) {
      return size;
    }
  }
}

ssize_t fullread(const char * fn, void * buf, size_t nbytes) {
    ssize_t size0;
    char tmp;
    ssize_t size = 0;
    int fd = open(fn, O_RDONLY);
    if (fd < 0) {
      return -1;
    }
    while (nbytes > 0 && (size0 = syncread(fd, buf, nbytes)) > 0) {
      size += size0;
      buf += size0;
      nbytes -= size0;
    }
    if (size0 !=0 && syncread(fd, &tmp, 1) != 0) {
      size = -1;
      errno = EFAULT;
    }
    close(fd);
    return size;
}

int calc_size_sha256(const char* name, size_t *length, unsigned char *hash) {
  int ret;
  int fd = open(name, O_RDONLY);
  if (fd < 0) {
    return 1;
  }
  off_t length0 = lseek(fd, 0, SEEK_END);
  if (length0 >= 0 && lseek(fd, 0, SEEK_SET) >= 0) {
    ret = sha256(fd, hash);
    if (!ret) {
      *length = length0;
    }
    close(fd);
    return ret;
  }
  close(fd);
  return 1;
}
