
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "io.h"

static char *xstrdup(const char *s)
{
	char *t;

	if (s == NULL)
		return NULL;

	t = strdup(s);

	if (t == NULL)
		exit(1);

	return t;
}

struct bootentry {
	const char* target;
	const char* src;
	size_t size;
	size_t entsize;
	unsigned char sha_hash[32];
};

enum entryorder {
	HW_SETTING = 0,
	UBOOT,
	FSBL,
	FSBL_OS,
	BL31,

	MAX_ENTRY,
};

static struct bootentry entries[] = {
	{"hw_setting.bin", NULL},
	{"uboot.bin", NULL},
	{"fsbl.bin", NULL},
	{"tee.bin", NULL}, // fsbl_os
	{"bl31.bin", NULL},
};

static struct option long_options[] = {
	{"hw-setting", required_argument, 0, 'h'},
	{"uboot", required_argument, 0, 'u'},
	{"fsbl", required_argument, 0, 'f'},
	{"fsbl-os", required_argument, 0, 'o'},
	{"bl31", required_argument, 0, 'b'},

	{"dest", required_argument, 0, 'd'},
};

char* dest=NULL;

static void args_parse(int argc, char *argv[])
{
	int c;
	int option_index = 0;
	while (1) {
		c = getopt_long_only(argc, argv, "h:u:f:o:b:d:",
				     long_options, &option_index);
		if (c == -1)
			break;

		switch (c) {
		case 'h':
			entries[HW_SETTING].src = xstrdup(optarg);
			break;
		case 'u':
			entries[UBOOT].src = xstrdup(optarg);
			break;
		case 'f':
			entries[FSBL].src = xstrdup(optarg);
			break;
		case 'o':
			entries[FSBL_OS].src = xstrdup(optarg);
			break;
		case 'b':
			entries[BL31].src = xstrdup(optarg);
			break;
		case 'd':
			dest = xstrdup(optarg);
			break;
		case ':':
			break;
		case '?':
			break;
		default:
			printf("Confusion: getopt_long returned %d\n", c);
		}
	}
}

static void usage() {
	printf("usage: bootcode_gen options...\n");
	printf("\nOptions:\n");
	printf("\t-h <path>\n");
	printf("\t--hw-setting <path>		* hw settings path\n\n");
	printf("\t-u <path>\n");
	printf("\t--uboot <path>			uboot path\n\n");
	printf("\t-f <path>\n");
	printf("\t--fsbl <path>			fsbl path\n\n");
	printf("\t-o <path>\n");
	printf("\t--fsbl-os <path>		fsbl-os path\n\n");
	printf("\t-b <path>\n");
	printf("\t--bl31 <path>			bl31 path\n\n");
	printf("\t-d <path>\n");
	printf("\t--dest <path>			* destination dir, i.e. the output dir\n\n");
	printf("\n");
	printf("* means that must be specified\n");
}

static int write_header(FILE *f) {
	for (int i=0; i<(0x60>>2); ++i) {
		if (i<MAX_ENTRY && entries[i].src) {
			if (fwrite(&entries[i].entsize, 4, 1, f) != 1) {
				return 1;
			}
		} else {
			if (fwrite("\0\0\0\0", 4, 1, f) != 1) {
				return 1;
			}
		}
	}
	return 0;
}

static int copyto(const char *src, FILE *f) {
	int ret = 0;
	char buf[512];
	size_t s;
	FILE *sf = fopen(src, "r");
	if (sf == NULL) {
		fprintf(stderr, "could not open %s\n", src);
		return 1;
	}
	while((s = fread(buf, 1, 512, sf)) > 0) {
		if (fwrite(buf, s, 1, f) != 1) {
			ret = 1;
			break;
		}
	}
	if (!ret && !feof(sf))
		ret = 1;
	fclose(sf);
	return ret;
}

static int write_entry(struct bootentry *ent, FILE *f) {
	if (fwrite("\x80", 1, 1, f) != 1) {
		return 1;
	}
	for (int i = 0; i < ent->entsize - ent->size - 9; ++i) {
		if (fwrite("\0", 1, 1, f) != 1) {
			return 1;
		}
	}
	uint64_t sizeinbits = ent->size << 3;
	uint32_t part = htonl(sizeinbits >> 32);
	if (fwrite(&part, 4, 1, f) != 1) {
		return 1;
	}
	part = htonl(sizeinbits & 0xFFFFFFFF);
	if (fwrite(&part, 4, 1, f) != 1) {
		return 1;
	}
	if (fwrite(ent->sha_hash, 32, 1, f) != 1) {
		return 1;
	}
	return 0;
}

static FILE * save_at(int dirfd, const char *path) {
	int fd = openat(dirfd, path, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
	return fd < 0 ? NULL : fdopen(fd, "w");
}

int main(int argc, char *argv[]) {
	args_parse(argc, argv);
	if (argc <= 1) {
		usage();
		return 1;
	}
	if (!entries[HW_SETTING].src || !dest) {
		fprintf(stderr, "hwsetting and destination must be specified!\n");
		return 1;
	}
	int dest_dir = open(dest, O_RDONLY);
	if (dest_dir < 0) {
		fprintf(stderr, "can not open destination directory to %s\n", dest);
		return 1;
	}
	for (int i=0;i<MAX_ENTRY;++i) {
		if (entries[i].src) {
			if (calc_size_sha256(entries[i].src, &entries[i].size, entries[i].sha_hash)) {
				fprintf(stderr, "read %s failed!\n", entries[i].src);
				return 1;
			}
			entries[i].entsize = (entries[i].size + 9 + 0x40 - 1) / 0x40 * 0x40;
		}
	}

	FILE *f;
	for (int i=0;i<MAX_ENTRY;++i) {
		if (entries[i].src) {
			f = save_at(dest_dir, entries[i].target);
			if (f == NULL) {
				fprintf(stderr, "could not open %s\n", entries[i].target);
				return 1;
			}
			if (i == HW_SETTING && write_header(f)) {
				fprintf(stderr, "write_header failed!\n");
				break;
			}
			if (copyto(entries[i].src, f)) {
				fprintf(stderr, "copy %s to output stream failed!\n", entries[i].src);
				break;
			}
			if (write_entry(entries + i, f)) {
				fprintf(stderr, "write_entry failed!\n");
				break;
			}
			fclose(f);
			f = NULL;
		}
	}
	if (f) {
		fclose(f);
		return 1;
	}
	return 0;
}
