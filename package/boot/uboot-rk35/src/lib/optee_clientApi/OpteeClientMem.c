/*
 * Copyright 2017, Rockchip Electronics Co., Ltd
 * hisping lin, <hisping.lin@rock-chips.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#include <common.h>
#include <stdlib.h>
#include <optee_include/OpteeClientMem.h>
#include <optee_include/OpteeClientRPC.h>
#include <optee_include/teesmc.h>
#include <optee_include/teesmc_optee.h>
#include <optee_include/teesmc_v2.h>

void *my_mem_start;
uint32_t my_count;
uint8_t *my_flag = NULL;
typedef struct {
	void *addrBlock;
	uint32_t sizeBlock;
	uint8_t used;
} ALLOC_FLAG;
ALLOC_FLAG alloc_flags[50];

int my_malloc_init(void *start, uint32_t size)
{
	if (start == NULL || size == 0) {
		printf("TEEC: malloc init fail!\n");
		return -1;
	}
	memset(start, 0, size);
	my_mem_start = start;
	my_count = size/4096;
	if (my_flag == NULL) {
		my_flag = malloc(size/4096);
		if (my_flag == NULL) {
			printf("TEEC: malloc fail!\n");
			return -1;
		}
	}
	memset(my_flag, 0, size/4096);
	memset(alloc_flags, 0, 50 * sizeof(ALLOC_FLAG));
	return 0;
}

void write_usedblock(void *addr, uint32_t size)
{
	uint8_t k;
	for (k = 0; k < 50; k++) {
		if (alloc_flags[k].used == 0) {
			alloc_flags[k].used = 1;
			alloc_flags[k].addrBlock = addr;
			alloc_flags[k].sizeBlock = size;
			break;
		}
	}
}

uint32_t find_sizeblock(void *addr)
{
	uint8_t k;
	for (k = 0; k < 50; k++)
		if (alloc_flags[k].used == 1 &&
				alloc_flags[k].addrBlock == addr)
			return alloc_flags[k].sizeBlock;

	return 0;
}

void free_usedblock(void *addr)
{
	uint8_t k;
	for (k = 0; k < 50; k++) {
		if (alloc_flags[k].used == 1 &&
				alloc_flags[k].addrBlock == addr) {
			alloc_flags[k].used = 0;
			alloc_flags[k].addrBlock = 0;
			alloc_flags[k].sizeBlock = 0;
			break;
		}
	}
}

void *my_malloc(uint32_t size)
{
	uint32_t i, j, k, num;

	num = (size - 1) / 4096 + 1;
	if (my_count < num)
		return 0;
	for (i = 0; i < my_count - num; i++) {
		if (*(my_flag + i) == 0) {
			for (j = 0; j < num; j++) {
				if (*(my_flag + i + j) != 0)
					break;
			}
			if (j == num) {
				for (k = 0; k < num; k++) {
					*(my_flag + i + k) = 1;
					memset(my_mem_start +
						(i + k) * 4096, 0, 4096);
				}
				debug("TEEC: malloc is: 0x%X  0x%X\n",
					(int)i, (int)num);
				write_usedblock((my_mem_start + i * 4096),
					num * 4096);

				return my_mem_start + (i * 4096);
			}
		}
	}

	return 0;
}

void my_free(void *ptr)
{
	uint32_t i, j, num, size;

	if (ptr < my_mem_start)
		return;

	i = (ptr - my_mem_start) / 4096;
	size = find_sizeblock(ptr);
	free_usedblock(ptr);
	if (size == 0)
		return;

	num = (size-1)/4096+1;
	debug("TEEC: free is: 0x%X  0x%X\n", i, num);

	for (j = 0; j < num; j++) {
		*(my_flag + i + j) = 0;
		memset(my_mem_start + (i + j) * 4096, 0, 4096);
	}
}

/*
 * Initlialize the memory component, for example providing the
 * containing drivers handle.
 */
int OpteeClientMemInit(void)
{
	ARM_SMC_ARGS ArmSmcArgs = {0};

	ArmSmcArgs.Arg0 = OPTEE_SMC_GET_SHM_CONFIG_V2;

	tee_smc_call(&ArmSmcArgs);

	debug("TEEC: get share memory, arg0=0x%x arg1=0x%x arg2=0x%x arg3=0x%x\n",
	      ArmSmcArgs.Arg0, ArmSmcArgs.Arg1, ArmSmcArgs.Arg2, ArmSmcArgs.Arg3);

	return my_malloc_init((void *)(size_t)ArmSmcArgs.Arg1, ArmSmcArgs.Arg2);
}

/*
 * Allocate a page aligned block of memory from the TrustZone
 * shared memory block.
 */
void *OpteeClientMemAlloc(uint32_t length)
{
	return my_malloc(length);
}

/*
 * Free a block of memory previously allocated using the
 * OpteeClientMemAlloc function.
 */
void OpteeClientMemFree(void *mem)
{
	my_free(mem);
}
