#ifndef __IO_H__
#define __IO_H__

ssize_t syncread(int fd, void *buf, size_t nbytes);
ssize_t fullread(const char * fn, void * buf, size_t nbytes);
int calc_size_sha256(const char* name, size_t *length, unsigned char *hash);

#endif