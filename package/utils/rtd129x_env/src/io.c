/*
 * @author jjm2473
 * @since 2021-03-15
 */

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

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

int fullwrite(const char * fn, void * buf, size_t nbytes) {
	size_t remain = nbytes;
	size_t wrote = 0;
	char *p = buf;
    int fd = open(fn, O_WRONLY|O_CREAT|O_TRUNC);
    if (fd < 0) {
      return -1;
    }
	while(remain > 0) {
		wrote = write(fd, p, remain);
		if (wrote > 0) {
			p += wrote;
			remain -= wrote;
		} else if (wrote == -1) {
			if (errno != EAGAIN) {
				break;
			}
		}
	}
	close(fd);
	return remain > 0 ? -1 : 0;
}
