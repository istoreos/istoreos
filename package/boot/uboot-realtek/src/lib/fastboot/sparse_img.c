#include <common.h>
#include <malloc.h>
#include <sparse_format.h>
#include <errno.h>

#include <asm/arch/fw_info.h>

#define TRACEF(str, x...) \
do { \
	printf("%s:%d: " str, __func__, __LINE__, ## x); \
} while (0)

#define LTRACEF debug

#define CACHE_LINE CONFIG_SYS_CACHELINE_SIZE
#define ROUNDUP(x, y)   (((x) + ((y) - 1)) & ~((y) - 1))

#ifndef FASTBOOT_SPARSE_IMAGE_ADDR
#define FASTBOOT_SPARSE_IMAGE_ADDR     CONFIG_SYS_LOAD_ADDR
#endif
#ifndef FASTBOOT_SPARSE_IMAGE_MAX_SIZE
#define FASTBOOT_SPARSE_IMAGE_MAX_SIZE  0x1400000
#endif

static int dump_memory(void *buffer)
{
	int i = 0;
	int *ptr = NULL;

	ptr = (int *)buffer;

	if (buffer == NULL) {
		TRACEF("[ERR] buffer addr is NULL\n");
		return -1;
	}

	LTRACEF("** dump_memory@%p **\n", buffer);

	for(i = 512; i > 0; i -= 16) {
		LTRACEF("0x%08x: 0x%08x 0x%08x 0x%08x 0x%08x\n",
			i,
			*(ptr - i / 4),
			*(ptr - i / 4 + 1),
			*(ptr - i / 4 + 2),
			*(ptr - i / 4 + 3)
		);
	}

	for(i = 0;i < 512;i += 16) {
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

bool is_sparse_img(void *data, size_t size)
{
	sparse_header_t *sparse_header = (sparse_header_t *) data;

	return (sparse_header->magic != SPARSE_HEADER_MAGIC);
}

static unsigned int sparse_get_chunk_data_size(sparse_header_t *sparse,
		chunk_header_t *chunk)
{
	return chunk->total_sz - sparse->chunk_hdr_sz;
}

static sparse_header_t *parse_sparse_header_and_shift(void **data)
{
	/* Read and skip over sparse image header */
	sparse_header_t *sparse_header = (sparse_header_t *) *data;

	if (sparse_header->magic != SPARSE_HEADER_MAGIC) {
		return NULL;
	}

	*data += sparse_header->file_hdr_sz;

	LTRACEF("=== Sparse Image Header ===\n");
	LTRACEF("magic: 0x%x\n", sparse_header->magic);
	LTRACEF("major_version: 0x%x\n", sparse_header->major_version);
	LTRACEF("minor_version: 0x%x\n", sparse_header->minor_version);
	LTRACEF("file_hdr_sz: %d\n", sparse_header->file_hdr_sz);
	LTRACEF("chunk_hdr_sz: %d\n", sparse_header->chunk_hdr_sz);
	LTRACEF("blk_sz: %d\n", sparse_header->blk_sz);
	LTRACEF("total_blks: %d\n", sparse_header->total_blks);
	LTRACEF("total_chunks: %d\n", sparse_header->total_chunks);

	return sparse_header;
}

static chunk_header_t *parse_sparse_chunk_and_shift(sparse_header_t *sparse,
		void **image)
{
	chunk_header_t *chunk = (chunk_header_t *) *image;
	unsigned int chunk_data_sz;

	LTRACEF("=== Chunk Header ===\n");
	LTRACEF("chunk_type: 0x%x\n", chunk->chunk_type);
	LTRACEF("chunk_data_sz: 0x%x\n", chunk->chunk_sz);
	LTRACEF("total_size: 0x%x\n", chunk->total_sz);

	switch (chunk->chunk_type) {
	case CHUNK_TYPE_RAW:
		chunk_data_sz = sparse_get_chunk_data_size(sparse, chunk);
		/* Check if the data size is a multiple of the main block size */
		if (chunk_data_sz % sparse->blk_sz)
			return NULL;
		/* Check that the chunk size is consistent */
		if ((chunk_data_sz / sparse->blk_sz) != chunk->chunk_sz)
			return NULL;
		break;

	case CHUNK_TYPE_FILL:
		chunk_data_sz = sparse_get_chunk_data_size(sparse, chunk);
		if (chunk_data_sz != sizeof(uint32_t))
			return NULL;
		break;

	case CHUNK_TYPE_DONT_CARE:
	case CHUNK_TYPE_CRC32:
		LTRACEF("Ignoring chunk\n");
		break;

	default:
		TRACEF("Unknown chunk type: %x\n",
		       chunk->chunk_type);
		dump_memory((void *)chunk);
		return NULL;
	}

	*image += sparse->chunk_hdr_sz;

	return chunk;
}

int parse_sparse_image(const char *arg, void *buffer, size_t sz,
		int (*flash_image)(const char *arg, uint64_t file_size, uint64_t offset,
			void *buffer, unsigned size))
{
	unsigned int chunk;
	sparse_header_t *sparse_header;
	chunk_header_t *chunk_header;
	uint64_t image_sz;
	uint64_t buffer_sz = sz;
	unsigned int chunk_data_sz;
	uint64_t offset;
	uint32_t total_blocks = 0;
	int ret;

	sparse_header = parse_sparse_header_and_shift(&buffer);
	if (!sparse_header) {
		TRACEF("Not sparse image, pass to flash_image\n");
		ret = flash_image(arg, 0, 0, buffer, sz);
		return ret;
	}

	image_sz = sparse_header->total_blks * sparse_header->blk_sz;
	buffer_sz -= sizeof(sparse_header_t);

	for (chunk = 1; chunk <= sparse_header->total_chunks; chunk++) {
		chunk_header = parse_sparse_chunk_and_shift(sparse_header, &buffer);
		if (!chunk_header) {
			TRACEF("chunk #%d/%d Unknown type buffer@%p\n",
					chunk, sparse_header->total_chunks, buffer);
			return -1;
		}
		chunk_data_sz = sparse_header->blk_sz * chunk_header->chunk_sz;
		buffer_sz -= sizeof(chunk_header_t);

		switch (chunk_header->chunk_type) {
		case CHUNK_TYPE_RAW:
			if (chunk_header->total_sz
					!= sparse_header->chunk_hdr_sz + chunk_data_sz) {
				TRACEF("chunk #%d/%d CHUNK_TYPE_RAW: ERROR!! "
						"total_sz %d != %d\n",
						chunk, sparse_header->total_chunks,
						chunk_header->total_sz,
						sparse_header->chunk_hdr_sz + chunk_data_sz);
				return -1;
			}
			//uint32_t *raw_buf = (uint32_t *)memalign(CACHE_LINE,
			//		ROUNDUP(chunk_data_sz, CACHE_LINE));
			uint32_t *raw_buf = (uint32_t *)FASTBOOT_SPARSE_IMAGE_ADDR;
			if (chunk_data_sz > FASTBOOT_SPARSE_IMAGE_MAX_SIZE) {
				TRACEF("ERROR %s Check chunk_data_sz 0x%x > "
					    "FASTBOOT_SPARSE_IMAGE_MAX_SIZE (0x%x)\n",
					    __func__, chunk_data_sz,
					    FASTBOOT_SPARSE_IMAGE_MAX_SIZE);
			}
			if (!raw_buf) {
				TRACEF("ERROR %s: No Memory!!\n", __func__);
				return -ENOMEM;
			}
			memcpy(raw_buf, buffer, chunk_data_sz);

			flush_cache((unsigned long)raw_buf, chunk_data_sz);
			offset = total_blocks * sparse_header->blk_sz;

			LTRACEF("chunk #%d/%d CHUNK_TYPE_RAW: At sparse buffer size 0x%x "
					"remainder size 0x%llx/0x%llx buffer@%p\n",
					chunk, sparse_header->total_chunks, (int)chunk_data_sz,
					buffer_sz - chunk_data_sz, (int64_t)sz, buffer);
			LTRACEF("chunk #%d At overall image: size 0x%x, offset 0x%llx "
				    "remainder size 0x%llx/0x%llx\n",
					chunk, (int)chunk_data_sz,
					offset, image_sz - offset - chunk_data_sz, image_sz);

			flash_image(arg, 0, offset, raw_buf, chunk_data_sz);

			total_blocks += chunk_header->chunk_sz;
			buffer += chunk_data_sz;
			buffer_sz -= chunk_data_sz;
			//free(raw_buf);
			break;

		case CHUNK_TYPE_FILL:
			if (chunk_header->total_sz
					!= sparse_header->chunk_hdr_sz + sizeof(uint32_t)) {
				TRACEF("chunk #%d/%d CHUNK_TYPE_FILL: ERROR~~ "
						"total_sz %d != %ld\n",
						chunk, sparse_header->total_chunks,
						chunk_header->total_sz,
						sparse_header->chunk_hdr_sz + sizeof(uint32_t));
				return -1;
			}
			size_t i;
			uint32_t *fill_buf = NULL;
			uint32_t fill_val;
			int fill_count = 1024;
			size_t max_fill_size = sparse_header->blk_sz * fill_count;
			int chunk_count = 0;

			//fill_buf = (uint32_t *)memalign(CACHE_LINE,
			//		ROUNDUP(max_fill_size, CACHE_LINE));
			fill_buf = (uint32_t *)FASTBOOT_SPARSE_IMAGE_ADDR;
			if (max_fill_size > FASTBOOT_SPARSE_IMAGE_MAX_SIZE) {
				TRACEF("ERROR %s Check max_fill_size 0x%lx > "
					    "FASTBOOT_SPARSE_IMAGE_MAX_SIZE (0x%x)\n",
					    __func__, max_fill_size,
					    FASTBOOT_SPARSE_IMAGE_MAX_SIZE);
			}

			if (!fill_buf) {
				TRACEF("ERROR %s: No Memory!!\n", __func__);
				return -ENOMEM;
			}
			fill_val = *(uint32_t *)buffer;

			for (i = 0; i < (max_fill_size / sizeof(fill_val)); i++) {
				fill_buf[i] = fill_val;
			}

			flush_cache((unsigned long)fill_buf, max_fill_size);

			LTRACEF("chunk #%d/%d CHUNK_TYPE_FILL: At sparse buffer size 0x%x "
				    "remainder size 0x%llx/0x%llx buffer@%p\n",
				    chunk, sparse_header->total_chunks, (int)sizeof(uint32_t),
				    (int64_t)(buffer_sz - sizeof(uint32_t)), (int64_t)sz,
				    buffer);
			LTRACEF("chunk #%d At overall image: size 0x%x offset 0x%llx "
				    "remainder size 0x%llx/0x%llx\n",
				    chunk, (int)chunk_data_sz,
				    (int64_t)(total_blocks * sparse_header->blk_sz),
				    (int64_t)(image_sz - total_blocks * sparse_header->blk_sz
				     - chunk_data_sz), image_sz);

			chunk_count = chunk_header->chunk_sz;
			while (chunk_count) {
				int count;
				size_t fill_size;
				offset = total_blocks * sparse_header->blk_sz;

				count = (fill_count < chunk_count)?fill_count:chunk_count;
				fill_size = count * sparse_header->blk_sz;

				LTRACEF("chunk #%d CHUNK_TYPE_FILL: fill "
					    "size 0x%lx (Overall image offset 0x%llx remainder "
					    "size 0x%llx/0x%llx)\n",
					    chunk, fill_size, offset,
					    image_sz - offset - fill_size, image_sz);
				/* write back by 4096 size*/
				flash_image(arg, 0, offset, fill_buf, fill_size);

				chunk_count -= count;
				total_blocks += count;

				LTRACEF("chunk #%d count %d remainder chunk_count "
						"%d(@chunk_sz %d) total_blocks %d\n",
						chunk, count, chunk_count, chunk_header->chunk_sz,
						total_blocks);
			}

			//free(fill_buf);

			buffer += sizeof(uint32_t);
			buffer_sz -= sizeof(uint32_t);
			break;

		case CHUNK_TYPE_CRC32:
			if(chunk_header->total_sz != sparse_header->chunk_hdr_sz) {
				//fastboot_fail("Bogus chunk size for chunk type Dont Care");
				return -1;
			}
			offset = total_blocks * sparse_header->blk_sz;
			LTRACEF("chunk #%d/%d CHUNK_TYPE_CRC32: At sparse buffer "
					"size 0x%x remainder size 0x%llx/0x%llx buffer@%p\n",
				    chunk, sparse_header->total_chunks,
				    (int)chunk_data_sz,
				    buffer_sz - chunk_data_sz, (int64_t)sz, buffer);

			LTRACEF("chunk #%d At overall image: skip size 0x%x "
					"offset 0x%llx remainder size 0x%llx/0x%llx\n",
					chunk, (int)chunk_data_sz,
					offset, image_sz - offset - chunk_data_sz, image_sz);

			total_blocks += chunk_header->chunk_sz;
			buffer += chunk_data_sz;
			buffer_sz -= chunk_data_sz;
			break;

		case CHUNK_TYPE_DONT_CARE:
			offset = total_blocks * sparse_header->blk_sz;
			LTRACEF("chunk #%d/%d CHUNK_TYPE_DONT_CARE: At sparse buffer "
					"size 0x%x remainder size 0x%llx/0x%llx buffer@%p\n",
				    chunk, sparse_header->total_chunks,
				    0, buffer_sz, (int64_t)sz, buffer);
			LTRACEF("chunk #%d At overall image: skip size 0x%x "
					"offset 0x%llx remainder size 0x%llx/0x%llx\n",
					chunk, (int)chunk_data_sz,
					offset, image_sz - offset - chunk_data_sz, image_sz);

			if (chunk > 1 && chunk < sparse_header->total_chunks)
				flash_image(arg, 0, offset, NULL, chunk_data_sz);

			total_blocks += chunk_header->chunk_sz;
			break;

		default:
			TRACEF("chunk #%d/%d Unkown chunk type: %x\n",
					chunk, sparse_header->total_chunks,
					chunk_header->chunk_type);
			dump_memory((void *)chunk_header);
			//fastboot_fail("Unknown chunk type");
			return -1;

		}
	}

	LTRACEF("Write %d blocks, expected to write %d blocks "
			"(image_sz=0x%llx)\n",
			total_blocks, sparse_header->total_blks, image_sz);

	if (total_blocks != sparse_header->total_blks) {
		TRACEF("sparse image write failure\n");
		//fastboot_fail("sparse image write failure");
		return -1;
	}

	return 0;
}
