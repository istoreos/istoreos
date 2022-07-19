#include <common.h>
#include <command.h>
#include <asm/types.h>

#define MAX_CHUNK_SIZE		1024
#define INITIAL_CHUNK_SIZE	16
#define	TOP_ADDR		0X17000000
#define	INITIAL_ADDR		0X10000000
#define	ADDR_STEP_SIZE		0X100

enum {
	CACHE_NOTFLUSH,
	CACHE_FLUSH,
};

enum {
	WRITE_THROUGH,
	WRITE_BACK,
};

u32 memtest_chunk_size = INITIAL_CHUNK_SIZE;
phys_addr_t memtest_addr = INITIAL_ADDR;
u8 base_pattern = 0;
u8 memtest_pattern = 0xf;


void update_test_condition(void)
{
	memtest_chunk_size = (memtest_chunk_size + 1 > MAX_CHUNK_SIZE) ? INITIAL_CHUNK_SIZE : memtest_chunk_size + 1 ;
	memtest_addr = (memtest_addr + ADDR_STEP_SIZE > TOP_ADDR) ? INITIAL_ADDR : memtest_addr + ADDR_STEP_SIZE ;
	base_pattern++;
	memtest_pattern++;
}

void set_memory(phys_addr_t start, phys_size_t size, u8 pattern)
{
	u8 *src = (u8 *)start;
	int i;

	for (i=0; i<size; i++)
		src[i] = pattern++;
}

void reset_memory_region(phys_addr_t start, phys_size_t size, u8 pattern)
{
	memset((void*)start, pattern, size);
	flush_dcache_all();
}

int validate_memory(phys_addr_t start, phys_size_t size, u8 start_pattern, u8 base_pattern, int cache_flushed)
{
	u8 *src = (u8 *)start;
	int i, ret=0;

	for (i=0; i<size; i++) {
		if(cache_flushed) {
			if(src[i] != start_pattern++) {
				printf("Fail!!\n\tmemory error at %08lx:%02x, expect:%02x\n",
					start+i, src[i], start_pattern - 1);
				ret = 1;
			}
		} else {
			if(src[i] != base_pattern) {
				printf("FAIL!!\n\tmemory error at %08lx:%02x, expect base pattern:%02x\n",
					start+i, src[i], base_pattern);
				ret = 1;
			}
		}
	}

	if(!ret)
		printf("Success\n");

	return ret;
}

int test_basic_copy(int cache_config)
{
	int ret = 0;

	printf("%s:%d ADDR:0x%08lx, CHUNK:%u, TEST_PATTERN:0x%02x, BASE_PATTERN:0x%02x ",
		__FUNCTION__, cache_config, memtest_addr, memtest_chunk_size, memtest_pattern, base_pattern);

	reset_memory_region(memtest_addr, memtest_chunk_size, base_pattern);
	set_memory(memtest_addr, memtest_chunk_size, memtest_pattern);

	ret = validate_memory(memtest_addr, memtest_chunk_size, memtest_pattern, base_pattern, CACHE_FLUSH);
	update_test_condition();

	return ret;
}

int test_no_flush(int cache_config)
{
	int ret = 0;

	printf("%s:%d ADDR:0x%08lx, CHUNK:%u, TEST_PATTERN:0x%02x, BASE_PATTERN:0x%02x ",
		__FUNCTION__, cache_config, memtest_addr, memtest_chunk_size, memtest_pattern, base_pattern);

	reset_memory_region(memtest_addr, memtest_chunk_size, base_pattern);
	set_memory(memtest_addr, memtest_chunk_size, memtest_pattern);

	dcache_disable_no_flush();

	if(cache_config == WRITE_BACK) {
		ret = validate_memory(memtest_addr, memtest_chunk_size, memtest_pattern, base_pattern, CACHE_NOTFLUSH);
		invalidate_dcache_all();
		dcache_enable();
	} else if(cache_config == WRITE_THROUGH) {
		ret = validate_memory(memtest_addr, memtest_chunk_size, memtest_pattern, base_pattern, CACHE_FLUSH);
		invalidate_dcache_all();
		dcache_enable_wt();
	} else {
		printf("Error cache_config %d\n", cache_config);
		ret = 1;
	}

	update_test_condition();

	return ret;
}

int test_flush_range(int cache_config)
{
	int ret = 0;

	printf("%s:%d ADDR:0x%08lx, CHUNK:%u, TEST_PATTERN:0x%02x, BASE_PATTERN:0x%02x ",
		__FUNCTION__, cache_config, memtest_addr, memtest_chunk_size, memtest_pattern, base_pattern);

	reset_memory_region(memtest_addr, memtest_chunk_size, base_pattern);
	set_memory(memtest_addr, memtest_chunk_size, memtest_pattern);
	flush_dcache_range(memtest_addr, memtest_addr + memtest_chunk_size);

	dcache_disable_no_flush();

	ret = validate_memory(memtest_addr, memtest_chunk_size, memtest_pattern, base_pattern, CACHE_FLUSH);

	invalidate_dcache_all();

	if(cache_config == WRITE_BACK) {
		dcache_enable();
	} else if (cache_config == WRITE_THROUGH) {
		dcache_enable_wt();
	} else {
		printf("Error cache_config %d\n", cache_config);
		ret = 1;
	}

	update_test_condition();

	return ret;
}

int test_flush_all(int cache_config)
{
	int ret = 0;

	printf("%s:%d ADDR:0x%08lx, CHUNK:%u, TEST_PATTERN:0x%02x, BASE_PATTERN:0x%02x ",
		__FUNCTION__, cache_config, memtest_addr, memtest_chunk_size, memtest_pattern, base_pattern);

	reset_memory_region(memtest_addr, memtest_chunk_size, base_pattern);
	set_memory(memtest_addr, memtest_chunk_size, memtest_pattern);
	flush_dcache_all();

	dcache_disable_no_flush();

	ret = validate_memory(memtest_addr, memtest_chunk_size, memtest_pattern, base_pattern, CACHE_FLUSH);

	invalidate_dcache_all();

	if(cache_config == WRITE_BACK) {
		dcache_enable();
	} else if (cache_config == WRITE_THROUGH) {
		dcache_enable_wt();
	} else {
		printf("Error cache_config %d\n", cache_config);
		ret = 1;
	}

	update_test_condition();

	return ret;
}

static int do_cachetest(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int i = 0;

	for(i = 0 ; i <= 0x70000000 ; i++) {
		/* cache write-back test */
		reset_cache_write_back();
		if(test_basic_copy(WRITE_BACK))
			break;
		if(test_no_flush(WRITE_BACK))
			break;
		if(test_flush_range(WRITE_BACK))
			break;
		if(test_flush_all(WRITE_BACK))
			break;

		/* cache write-through test */
		reset_cache_write_through();
		if(test_basic_copy(WRITE_THROUGH))
			break;
		if(test_no_flush(WRITE_THROUGH))
			break;
		if(test_flush_range(WRITE_THROUGH))
			break;
		if(test_flush_all(WRITE_THROUGH))
			break;
	}

	reset_cache_write_back();

	return 0;
}

U_BOOT_CMD(
	cachetest, 1, 0, do_cachetest,
	"Stress cache operation",
	"ADDR"
);
