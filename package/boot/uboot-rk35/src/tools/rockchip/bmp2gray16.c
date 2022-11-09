/*
 * (C) Copyright 2020 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 * Author: Wenping Zhang <wenping.zhang@rock-chips.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <rk_eink.h>

struct  bmp_header {
	/* Header */
	char signature[2];
	uint32_t	file_size;
	uint32_t	reserved;
	uint32_t	data_offset;
	/* InfoHeader */
	uint32_t	size;
	uint32_t	width;
	uint32_t	height;
	uint16_t	planes;
	uint16_t	bit_count;
	uint32_t	compression;
	uint32_t	image_size;
	uint32_t	x_pixels_per_m;
	uint32_t	y_pixels_per_m;
	uint32_t	colors_used;
	uint32_t	colors_important;
	/* ColorTable */
} __attribute__((packed));

struct bmp_image {
	struct bmp_header hdr;
	uint8_t color_table[0];
};

struct pixel_u16 {
	uint16_t blue  : 4,
		green : 4,
		red   : 4,
		alpha : 4;
} __attribute__((packed));

struct pixel_u24 {
	uint8_t blue;
	uint8_t green;
	uint8_t red;
} __attribute__((packed));

struct pixel_u32 {
	uint8_t blue;
	uint8_t green;
	uint8_t red;
	uint8_t alpha;
} __attribute__((packed));

//logo partition Header, 64byte
struct logo_part_header {
	char magic[4]; /* must be "RKEL" */
	uint32_t  totoal_size;
	uint32_t  screen_width;
	uint32_t  screen_height;
	uint32_t  logo_count;
	char  version[4];
	uint32_t  rsv[10];
} __attribute__((packed));

// logo image header,32 byte
struct grayscale_header {
	char magic[4]; /* must be "GR04" */
	uint16_t x;
	uint16_t y;
	uint16_t w;
	uint16_t h;
	uint32_t logo_type;
	uint32_t data_offset; /* image offset in byte */
	uint32_t data_size; /* image size in byte */
	uint32_t rsv[2];
} __attribute__((packed));

/*
 * The start address of logo image in logo.img must be aligned
 * in 512 bytes,so the header size must be times of 512 bytes.
 * Here we fix the size to 512 bytes, so the count of logo image
 * can only support up to 14.
 */
struct logo_info {
	struct logo_part_header part_hdr;
	struct grayscale_header img_hdr[14];
} __attribute__((packed));

struct input_img_info {
	char path[256];
	int logo_type;
};

/*
 * Every part of logo.img must be aligned in RK_BLK_SIZE,
 * use macro aligned_in_blk to calculate the the real size
 */
#define RK_BLK_SIZE 512
#define ALIGN(x, y)	(((x) + (y) - 1) & ~((y) - 1))

struct input_img_info in_img_info[16];
uint32_t screen_w;
uint32_t screen_h;
static const char version[4] = "1.00";
static const char *PROG;

static const char *fix_path(const char *path)
{
	if (!memcmp(path, "./", 2))
		return path + 2;
	return path;
}

static void print_version(void)
{
	printf("Version %s (zwp@rock-chips.com)\n", version);
}

void usage(void)
{
	printf("Usage: %s [options] [arguments]\n\n", PROG);
	print_version();
	printf("\t --uboot-logo path");
	printf("\t\t\t Pack uboot logo to logo.img from given path\n");
	printf("\t --charge-logo path");
	printf("\t\t\t Pack charge logo to logo.img from given path\n");
	printf("\t --lowpower-logo path");
	printf("\t\t\t Pack low power logo to logo.img from given path\n");
	printf("\t --kernel-logo path");
	printf("\t\t\t Pack low power logo to logo.img from given path\n");
	printf("\t --poweroff-logo path");
	printf("\t\t\t Pack power off logo to logo.img from given path\n");
	printf("\t --output path");
	printf("\t\t\t Output the grayscale image to path\n");
}

static inline int size_of_header(void)
{
	return ALIGN(sizeof(struct logo_info), RK_BLK_SIZE);
}

static inline int size_of_one_image(void)
{
	return ALIGN((screen_w * screen_h) >> 1, RK_BLK_SIZE);
}

int get_logo_resolution(char *in_path, uint32_t *logo_width,
			uint32_t *logo_height)
{
	struct bmp_header bmp_hdr;
	FILE *file;
	int size;
	int ret = 0;

	if (!in_path)
		fprintf(stderr, "Invalid bmp file path.\n");

	file = fopen(in_path, "rb");
	if (!file) {
		fprintf(stderr, "File %s open failed.\n", in_path);
		return -1;
	}
	size = sizeof(struct bmp_header);
	if (size != fread(&bmp_hdr, 1, size, file)) {
		fprintf(stderr, "Incomplete read of file %s.\n", in_path);
		ret = -1;
		goto out;
	}
	if (!(bmp_hdr.signature[0] == 'B' &&
	      bmp_hdr.signature[1] == 'M')) {
		printf("cat not find bmp file\n");
		ret = -1;
		goto out;
	}
	*logo_width = bmp_hdr.width;
	*logo_height = bmp_hdr.height;
	fprintf(stderr, "logo resolution is %d x %d.\n",
		*logo_width, *logo_height);
out:
	fclose(file);
	return ret;
}

/*
 * The bmp pixel is scan from left-bottom to right-top
 */
int convert_bmp_idx_to_gray_idx(int idx, uint32_t w, uint32_t h)
{
	int row = h - (idx / w) - 1;

	return (row * w + idx % w) / 2;
}

int convert_one_image(char *in_path, void *out_buf, uint32_t offset,
		      struct grayscale_header *gr_hdr, int type)
{
	struct bmp_image *bmp;
	struct bmp_header *bmp_hdr;
	FILE *file;
	void *bmp_buf;
	int size;
	int ret = -1;
	uint8_t *gr16_data = (uint8_t *)out_buf;

	if (!out_buf || !in_path) {
		fprintf(stderr, "in_path or out_buf is NULL.\n");
		return -1;
	}

	file = fopen(in_path, "rb");
	if (!file) {
		fprintf(stderr, "File %s open failed.\n", in_path);
		return -1;
	}

	fseek(file, 0, SEEK_END);
	size = ftell(file);
	fseek(file, 0, SEEK_SET);

	bmp_buf = calloc(1, size);
	if (!bmp_buf) {
		fprintf(stderr, "Allocate memory of %d bytes failed.\n", size);
		fclose(file);
		return -1;
	}
	if (size != fread(bmp_buf, 1, size, file)) {
		fprintf(stderr, "Incomplete read of file %s.\n", in_path);
		goto out;
	}

	bmp = (struct bmp_image *)bmp_buf;
	bmp_hdr = &bmp->hdr;
	if (!(bmp_hdr->signature[0] == 'B' &&
	      bmp_hdr->signature[1] == 'M')) {
		printf("cat not find bmp file\n");
		goto out;
	}

	if (size != le32_to_cpu(bmp_hdr->file_size)) {
		fprintf(stderr, "Invalid BMP file size %d.\n",
			le32_to_cpu(bmp_hdr->file_size));
		goto out;
	}
	printf("bmp_hdr->width=%d, bmp_hdr->height=%d\n",
	       bmp_hdr->width, bmp_hdr->height);
	printf("screen_w=%d, screen_h=%d\n", screen_w, screen_h);
	if (le32_to_cpu(bmp_hdr->width) != screen_w ||
	    le32_to_cpu(bmp_hdr->height) != screen_h) {
		fprintf(stderr, "The image size must same with others.\n");
		goto out;
	}
	//write header
	gr_hdr->magic[0] = 'G';
	gr_hdr->magic[1] = 'R';
	gr_hdr->magic[2] = '0';
	gr_hdr->magic[3] = '4';
	gr_hdr->x = 0;
	gr_hdr->y = 0;
	gr_hdr->w = screen_w;
	gr_hdr->h = screen_h;
	gr_hdr->logo_type = type;
	gr_hdr->data_offset = offset;
	gr_hdr->data_size = screen_w * screen_h / 2;

	printf("bmp depth is %d\n", bmp_hdr->bit_count);
	//convert rgb to gray data, and write to output buffer
	// the used algorithm please refer to below url:
	// https://www.cnblogs.com/zhangjiansheng/p/6925722.html
	// we use below algorithm:
	// Gray = (R*19595 + G*38469 + B*7472) >> 16
	switch (bmp_hdr->bit_count) {
	case 16:{
		struct pixel_u16 *color_u16;
		int i;

		color_u16 = (struct pixel_u16 *)bmp->color_table;
		for (i = 0; i < screen_w * screen_h / 2; i++) {
			struct pixel_u16 *pix1 = &color_u16[2 * i];
			struct pixel_u16 *pix2 = &color_u16[2 * i + 1];
			int j = convert_bmp_idx_to_gray_idx(2 * i, screen_w,
							    screen_h);
			/*
			 * the rgb value of pixel_u16 is 4 bits,
			 * so the counted grayscale value is 4bit
			 */
			uint32_t gray_px1 = (pix1->red * 19595 +
					     pix1->green * 38469 +
					     pix1->blue * 7472) >> 16;
			uint32_t gray_px2 = (pix2->red * 19595 +
					     pix2->green * 38469 +
					     pix2->blue * 7472) >> 16;
			gr16_data[j] = gray_px1 | (gray_px2 << 4);
		}
	}
	break;
	case 24: {
		struct pixel_u24 *color_u24;
		int i;

		color_u24 = (struct pixel_u24 *)bmp->color_table;
		for (i = 0; i < screen_w * screen_h / 2; i++) {
			struct pixel_u24 *pix1 = &color_u24[2 * i];
			struct pixel_u24 *pix2 = &color_u24[2 * i + 1];
			int j = convert_bmp_idx_to_gray_idx(2 * i, screen_w,
							    screen_h);
			/*
			 * The rgb value of pixel_u24 is 8 bits,
			 * so the counted grayscale
			 * value need to divide into 16
			 */
			uint32_t gray_px1 = ((pix1->red * 19595 +
					      pix1->green * 38469 +
					      pix1->blue * 7472) >> 16) >> 4;
			uint32_t gray_px2 = ((pix2->red * 19595 +
					      pix2->green * 38469 +
					      pix2->blue * 7472) >> 16) >> 4;

			gr16_data[j] = gray_px1 | (gray_px2 << 4);
		}
	}
	break;
	case 32: {
		struct pixel_u32 *color_u32;
		int i;

		color_u32 = (struct pixel_u32 *)bmp->color_table;
		for (i = 0; i < screen_w * screen_h / 2; i++) {
			struct pixel_u32 *pix1 = &color_u32[2 * i];
			struct pixel_u32 *pix2 = &color_u32[2 * i + 1];
			int j = convert_bmp_idx_to_gray_idx(2 * i, screen_w,
							    screen_h);
			/*
			 * The rgb value of pixel_u32 is 8 bits,
			 * so the counted grayscale
			 * value need to divide into 16
			 */
			uint32_t gray_px1 = ((pix1->red * 19595 +
					      pix1->green * 38469 +
					      pix1->blue * 7472) >> 16) >> 4;
			uint32_t gray_px2 = ((pix2->red * 19595 +
					      pix2->green * 38469 +
					      pix2->blue * 7472) >> 16) >> 4;
			gr16_data[j] = gray_px1 | (gray_px2 << 4);
		}
	}
	break;
	default:
		ret = -1;
		printf("Invalid bit count[%d],only support 16/24/32 bpp bmp\n",
		       bmp_hdr->bit_count);
	break;
	}

	fprintf(stderr, "Convert image success\n");
	ret = 0;
out:
	free(bmp_buf);
	fclose(file);
	return ret;
}

void *init_grayscale_logo_buf(int logo_count, uint32_t size_one_image)
{
	int size;
	void *out_buf;

	if (!logo_count) {
		fprintf(stderr, "No input logo!\n");
		return NULL;
	}
	size = size_of_header();
	fprintf(stderr, "size of header in logo.img is %d\n", size);
	//every pixel of the grayscale image is 4 bits
	size += logo_count * size_one_image;
	out_buf = calloc(1, size);

	return out_buf;
}

void deinit_grayscale_logo_buf(void *buf)
{
	if (buf) {
		free(buf);
		buf = NULL;
	}
}

int main(int argc, char *argv[])
{
	char out_path[256] = {0};
	void *out_buf;
	int logo_count = 0;
	int i;
	int hdr_size, one_img_size, total_size;
	int ret = -1;
	struct logo_info *logo_hdr;
	FILE *file;

	PROG = fix_path(argv[0]);

	argc--, argv++;
	while (argc > 0 && argv[0][0] == '-') {
		/* it's a opt arg. */
		const char *arg = argv[0];

		argc--, argv++;
		if (!strcmp("-h", arg)) {
			usage();
			return 0;
		}  else if (!strcmp("--charge-logo", arg)) {
			int len, i;
			/*
			 * Charge logo are located in directory
			 * u-boot/tools/images/eink/, there are 7
			 * pictures to tell user the battery capacity
			 * during charging
			 */
			for (i = 0; i < 7; i++) {
				int logo_type = EINK_LOGO_CHARGING_0 << i;

				len = strlen(argv[0]);
				if (len > 256) {
					fprintf(stderr,
						"input charging logo path %s is too long.\n",
						argv[0]);
					return -1;
				}
				printf("charge logo path %s\n", argv[0]);
				memcpy(in_img_info[logo_count].path,
				       argv[0], len);
				in_img_info[logo_count].logo_type = logo_type;
				logo_count++;
				argc--, argv++;
			}
		}  else if (!strcmp("--uboot-logo", arg)) {
			int len = strlen(argv[0]);

			if (len > 256) {
				printf("Uboot logo path %s is too long.\n",
				       argv[0]);
				return -1;
			}
			memcpy(in_img_info[logo_count].path, argv[0], len);
			in_img_info[logo_count].logo_type = EINK_LOGO_UBOOT;
			logo_count++;
			argc--, argv++;
		} else if (!strcmp("--kernel-logo", arg)) {
			int len = strlen(argv[0]);

			if (len > 256) {
				printf("Kernel logo path %s is too long\n",
				       argv[0]);
				return -1;
			}
			memcpy(in_img_info[logo_count].path, argv[0], len);
			in_img_info[logo_count].logo_type = EINK_LOGO_KERNEL;
			logo_count++;
			argc--, argv++;
		} else if (!strcmp("--poweroff-logo", arg)) {
			int len = strlen(argv[0]);

			if (len > 256) {
				printf("Poweroff logo path %s is too long\n",
				       argv[0]);
				return -1;
			}
			memcpy(in_img_info[logo_count].path, argv[0], len);
			in_img_info[logo_count].logo_type = EINK_LOGO_POWEROFF;
			logo_count++;
			argc--, argv++;
		}  else if (!strcmp("--screen-width", arg)) {
			screen_w = strtoul(argv[0], NULL, 10);
			argc--, argv++;
		}  else if (!strcmp("--screen-height", arg)) {
			screen_h = strtoul(argv[0], NULL, 10);
			argc--, argv++;
		}  else if (!strcmp("--output", arg)) {
			int len = strlen(argv[0]);

			if (len > 256) {
				printf("input output path %s is too long.\n",
				       argv[0]);
				return -1;
			}
			memcpy(out_path, argv[0], len);
			argc--, argv++;
		} else {
			fprintf(stderr, "Unknown opt:%s", arg);
			usage();
			return -1;
		}
	}

	ret = get_logo_resolution(in_img_info[0].path, &screen_w, &screen_h);
	if (ret < 0) {
		fprintf(stderr,
			"Get height and width from logo image failed.\n");
		usage();
		return -1;
	}

	if (screen_w == 0 || screen_h == 0) {
		fprintf(stderr,
			"The screen weight and screen height must be set.\n");
		usage();
		return -1;
	}

	file = fopen(out_path, "wb+");
	if (!file) {
		fprintf(stderr, "File %s open failed.\n", out_path);
		usage();
		return -1;
	}
	hdr_size = size_of_header();
	one_img_size = size_of_one_image();

	out_buf = init_grayscale_logo_buf(logo_count, one_img_size);
	if (!out_buf) {
		fprintf(stderr, "Can't malloc buffer for grayscale image.\n");
		fclose(file);
		return -1;
	}

	logo_hdr = (struct logo_info *)out_buf;
	fprintf(stderr, "logo count is %d,one_img_size=%d,size=%d.\n",
		logo_count, one_img_size, screen_w * screen_h / 2);
	for (i = 0; i < logo_count; i++) {
		char *in_path = in_img_info[i].path;
		int type = in_img_info[i].logo_type;
		void *img_buf;
		int offset = hdr_size + i *  one_img_size;

		img_buf = out_buf + offset;
		printf("image[%d] start addr=0x%p\n", i, img_buf);
		ret = convert_one_image(in_path, img_buf, offset,
					&logo_hdr->img_hdr[i], type);
		if (ret < 0) {
			printf("Convert image[%d] failed, type is %d\n",
			       i, type);
			break;
		}
	}

	if (ret == 0) {
		struct logo_part_header *part_hdr = &logo_hdr->part_hdr;

		total_size = hdr_size + (i - 1) * one_img_size +
				screen_h * screen_w / 2;

		//convert success, write header data.
		part_hdr->magic[0] = 'R';
		part_hdr->magic[1] = 'K';
		part_hdr->magic[2] = 'E';
		part_hdr->magic[3] = 'L';
		part_hdr->totoal_size = total_size;
		part_hdr->screen_width = screen_w;
		part_hdr->screen_height = screen_h;
		part_hdr->logo_count = i;
		printf("screen w=%d, h=%d, total_size=%d\n",
		       screen_w, screen_h, total_size);
		memcpy(part_hdr->version, version, 4);

		// write to output file
		ret = fwrite(out_buf, total_size, 1, file);
		if (ret != 1)
			fprintf(stderr, "write image to file %s failed\n",
				out_path);
	}

	deinit_grayscale_logo_buf(out_buf);
	ret = fclose(file);
	if (ret != 0)
		printf("Close file[%s] failed, err=%d\n", out_path, ret);
	file = NULL;
	return ret;
}

