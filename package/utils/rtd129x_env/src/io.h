#ifndef __IO_H__
#define __IO_H__

/*
* retry when errno=EAGAIN
* RETURN same as read(2)
*/
ssize_t syncread(int fd, void *buf, size_t nbytes);

/*
* read a file to buffer
* RETURN -1 if real size bigger than nbytes or other errors, readed size otherwise.
*/
ssize_t fullread(const char * fn, void * buf, size_t nbytes);

int fullwrite(const char * fn, void * buf, size_t nbytes);

#endif