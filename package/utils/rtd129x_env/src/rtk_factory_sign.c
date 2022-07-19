/*
 * @author jjm2473
 * @since 2021-03-19
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
#include "tar.h"
#include "io.h"

unsigned int fill_sign(unsigned char* buf, unsigned int len) {
	posix_header *p_start = (posix_header *)buf;
	if (strncmp("RTK", p_start->rtk_signature, 3) == 0) {
		p_start->rtk_seqnum = 0;
		tar_fill_checksum((char *)p_start);
		return p_start->rtk_tarsize;
	}
	p_start->rtk_signature[0] = 'R';
	p_start->rtk_signature[1] = 'T';
	p_start->rtk_signature[2] = 'K';
	p_start->rtk_signature[3] = 0;
	p_start->rtk_tarsize = (unsigned int)len;
	p_start->rtk_seqnum = 0;
	tar_fill_checksum((char *)p_start);
	return len;
}

int main(int argc, char *argv[]) {
	unsigned char buf[512];
	off_t tarlen;
	int fd;
	int ret = 0;
	if (argc != 2) {
		printf("Usage: %s <factory.tar>\n", argv[0]);
		return -1;
	}
	fd = open(argv[1], O_RDWR);
	if (fd < 0) {
		fprintf(stderr, "cannot open %s\n", argv[1]);
		return 1;
	}
	if (syncread(fd, buf, 512) == 512) {
		tarlen = lseek(fd, 0, SEEK_END);
		if (tarlen > 0) {
			tarlen = fill_sign(buf, tarlen);
			lseek(fd, 0, SEEK_SET);
			write(fd, buf, 512);
			lseek(fd, tarlen, SEEK_SET);
			write(fd, buf, 512);
			memset(buf, 0, 512);
			write(fd, buf, 512);
			write(fd, buf, 512);
		} else {
			fprintf(stderr, "lseek failed, errno=%d\n", errno);
			ret = 1;
		}
	} else {
		fprintf(stderr, "%s is not a regular tarball file\n", argv[1]);
		ret = 1;
	}
	close(fd);
	return ret;
}