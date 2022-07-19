#include <common.h>
#include <malloc.h>
#include <errno.h>
#include <tar.h>

#define TAR_BLOCK_SIZE 0x200 //512 byte

#define TRACEF(str, x...) \
do { \
	printf("%s:%d: " str, __func__, __LINE__, ## x); \
} while (0)

#define LTRACEF debug

#define ROUNDUP(x, y)   (((x) + ((y) - 1)) & ~((y) - 1))

struct process_image_info {
	char *process_file_name;
	uint64_t file_size;
	uint64_t processed_size;

	void *buffer;
	uint64_t buffer_offset;
	uint64_t buffer_sz;
};

#ifdef FASTBOOT_TAR_BUFFER_ADDR
#define CUR_IMG_BUFFER_ADDR FASTBOOT_TAR_BUFFER_ADDR
#else
#define CUR_IMG_BUFFER_ADDR       0x3C800000
#endif
#ifdef FASTBOOT_TAR_BUFFER_SIZE
#define CUR_IMG_BUFFER_SIZE FASTBOOT_TAR_BUFFER_SIZE
#else
#define CUR_IMG_BUFFER_SIZE       4*1024*1024
#endif

static struct process_image_info cur_img;

/*
static int dump_memory(void *buffer, size_t len)
{
	int i = 0;
	int *ptr = NULL;

	ptr = (int *)buffer;

	if (buffer == NULL) {
		TRACEF("[ERR] buffer addr is NULL\n");
		return -1;
	}

	LTRACEF("** dump_memory@%p **\n", buffer);

	for(i = 0;i < (int)len + 16;i += 16) {
		LTRACEF("0x%08x: 0x%08x 0x%08x 0x%08x 0x%08x\n",
			i,
			*(ptr + i / 4),
			*(ptr + i / 4 + 1),
			*(ptr + i / 4 + 2),
			*(ptr + i / 4 + 3)
		);
	}

	return 0;
}
*/

void flash_tmp_buffer_data(
		int (*flash_image)(const char *arg, uint64_t file_sz, uint64_t offset,
				void *data, unsigned size))
{
	char *arg;
	uint64_t file_sz = 0;
	if (cur_img.buffer_sz) {
		arg = cur_img.process_file_name;
		file_sz = cur_img.file_size;
		LTRACEF("flash TMP data by flash_image %s continue ... "
			    "data size 0x%llx buffer_offset 0x%llx "
			    "@(0x%llx/0x%llx bytes)\n",
			    cur_img.process_file_name, cur_img.buffer_sz,
			    cur_img.buffer_offset,
			    cur_img.processed_size, cur_img.file_size);
		flash_image(arg, file_sz,
			    cur_img.buffer_offset,
			    cur_img.buffer, cur_img.buffer_sz);
		cur_img.buffer_sz = 0;
		memset(cur_img.buffer, 0, CUR_IMG_BUFFER_SIZE);
		cur_img.buffer_offset = 0;
	}
}

size_t process_no_data_case(size_t len,
		int (*flash_image)(const char *arg, uint64_t file_sz, uint64_t offset,
				void *data, unsigned size))
{
	uint64_t data_sz = 0;
	LTRACEF("NO data case: len 0x%lx\n", len);
	if (cur_img.process_file_name) {
		data_sz = cur_img.file_size - cur_img.processed_size;
		if (data_sz >= len)
			data_sz = len;

		LTRACEF("flash_image continue skip data length 0x%llx file %s"
				"@(0x%llx/0x%llx bytes)\n",
				data_sz, cur_img.process_file_name,
				cur_img.processed_size, cur_img.file_size);

		cur_img.processed_size += data_sz;

		if (cur_img.processed_size == cur_img.file_size) {
			flash_tmp_buffer_data(flash_image);
			/* clear cur_img */
			free(cur_img.process_file_name);
			cur_img.process_file_name = NULL;
			cur_img.file_size = 0;
			cur_img.processed_size = 0;
			//free(cur_img.buffer);
			cur_img.buffer = NULL;
		}
	}
	len -= data_sz;
	return len;
}

size_t process_not_tar_case(void **data, size_t len,
		int (*flash_image)(const char *arg, uint64_t file_sz, uint64_t offset,
				void *data, unsigned size))
{
		char *arg;
		uint64_t file_sz = 0;
		uint64_t data_sz = 0;
		uint64_t offset = 0;

	if (cur_img.process_file_name) {
		arg = cur_img.process_file_name;
		file_sz = cur_img.file_size;
		offset = cur_img.processed_size;
		data_sz = cur_img.file_size - cur_img.processed_size;
		if (data_sz >= len)
			data_sz = len;

		if (data_sz > CUR_IMG_BUFFER_SIZE) {
			flash_tmp_buffer_data(flash_image);
			LTRACEF("write flash_image %s continue data size 0x%llx "
				    "@(0x%llx/0x%llx bytes)\n",
				    cur_img.process_file_name, data_sz,
				    cur_img.processed_size, cur_img.file_size);
			flash_image(arg, file_sz, offset, *data, data_sz);
		} else {
			if (data_sz > CUR_IMG_BUFFER_SIZE - cur_img.buffer_sz) {
				flash_tmp_buffer_data(flash_image);
			}
			if (cur_img.buffer_sz == 0) {
				cur_img.buffer_offset = offset;
			}

			LTRACEF("save TMP data continue ... "
				    "data size 0x%llx to buffer@(0x%llx/0x%x bytes) "
				    "%s@(0x%llx/0x%llx bytes)\n",
				    data_sz, cur_img.buffer_sz, CUR_IMG_BUFFER_SIZE,
				    cur_img.process_file_name,
				    cur_img.processed_size, cur_img.file_size);
			memcpy(cur_img.buffer + cur_img.buffer_sz, *data, data_sz);
			cur_img.buffer_sz += data_sz;
		}

		cur_img.processed_size += data_sz;

		if (cur_img.processed_size == cur_img.file_size) {
			flash_tmp_buffer_data(flash_image);
			/* clear cur_img */
			free(cur_img.process_file_name);
			cur_img.process_file_name = NULL;
			cur_img.file_size = 0;
			cur_img.processed_size = 0;
			//free(cur_img.buffer);
			cur_img.buffer = NULL;
		}

		if (data_sz < ROUNDUP(data_sz, TAR_BLOCK_SIZE)) {
			*data += ROUNDUP(data_sz, TAR_BLOCK_SIZE);
			len -= ROUNDUP(data_sz, TAR_BLOCK_SIZE);
		} else {
			*data += data_sz;
			len -= data_sz;
		}
	} else {
		LTRACEF("ERROR!! Not tar header!! "
				"data@%p len 0x%lx\n", *data, len);
		return 0;
//		if (LOCAL_TRACE >= INFO)
//			tar_dump_posix_header(header);
	}
	return len;
}

int process_tar_image(void *data, size_t sz,
		int (*flash_image)(const char *arg, uint64_t file_sz, uint64_t offset,
				void *data, unsigned size))
{
	posix_header *header = NULL;  //512 bytes
	size_t len = sz;

	LTRACEF("process data@%p size 0x%lx\n", data, sz);
	while (len > 0) {
		char *arg;
		uint64_t file_sz = 0;
		uint64_t data_sz = 0;
		uint64_t offset = 0;

		header = (posix_header *)data;

		LTRACEF("processing... data@%p len 0x%lx\n", data, len);

		if (data == NULL && len > 0) {
			len = process_no_data_case(len, flash_image);
			continue;
		}

		if (tar_check_header((char *)header) < 0) {
			len = process_not_tar_case(&data, len, flash_image);
			continue;
		}

		data += sizeof(posix_header);
		len -= sizeof(posix_header);

		file_sz = simple_strtol(header->size ,0,8);

		TRACEF("processing file: %s size 0x%llx (data@%p)\n",
				header->name, file_sz, data);

		if (file_sz > len) {
			/* save cur_img */
			LTRACEF("%s is a split image (data len %ld / file size %lld)\n",
					header->name, len, file_sz);
			cur_img.process_file_name = malloc(sizeof(header->name));
			if (!cur_img.process_file_name) {
				TRACEF("ERROR %s: NO memory!!\n", __func__);
				return -ENOMEM;
			}
			memcpy(cur_img.process_file_name,
					header->name, sizeof(header->name));
			cur_img.file_size = file_sz;
			cur_img.processed_size = len;

			//cur_img.buffer =  memalign(CACHE_LINE,
			//		ROUNDUP(CUR_IMG_BUFFER_SIZE, CACHE_LINE));
			cur_img.buffer = (void *)CUR_IMG_BUFFER_ADDR;
			cur_img.buffer_offset = 0;
			cur_img.buffer_sz = 0;

			data_sz = len;
		} else {
			data_sz = file_sz;
		}

		arg = header->name;
		offset = 0;

		LTRACEF("write flash_image %s data length 0x%llx @(0x%llx/0x%llx)\n",
				header->name, data_sz, offset, file_sz);
		flash_image(arg, file_sz, offset, data, data_sz);

		if (len > ROUNDUP(data_sz, TAR_BLOCK_SIZE)) {
			data += ROUNDUP(data_sz, TAR_BLOCK_SIZE);
			len -= ROUNDUP(data_sz, TAR_BLOCK_SIZE);
		} else {
			data += data_sz;
			len -= data_sz;
		}
		LTRACEF("Next remainder data %p len 0x%lx\n", data, len);
	}

	LTRACEF("process OK ...\n");
	return 0;
}
