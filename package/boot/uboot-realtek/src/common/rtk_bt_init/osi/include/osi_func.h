#ifndef OSI_FUNCTION_H
#define OSI_FUNCTION_H
#include "osi_data_types.h"
#include "osi_include_ext.h"

#define UNUSED(x) (void)(x)

#define SMA_MAXSIZE     (100)
#define MED_MAXSIZE     (500)
#define BIG_MAXSIZE     (0xE000*4)//56 * 4K

void osi_buff_init(void);

void *osi_malloc(u32 size);

void *osi_memset(void *s, s32 ch, u32 n);

void osi_free(void *ptr);

void *osi_memcpy(void *dest, const void *src, u32 n);

int osi_memcmp(void *dest, const void *src, u32 n);


void osi_rtk_ndelay(u64 nsecs);
void osi_rtk_udelay(u64 usecs);
void osi_rtk_mdelay(u64 msecs);


typedef struct {
	BOOLEAN in_use;
	unsigned char data[SMA_MAXSIZE];
}memory_small;

typedef struct {
	BOOLEAN in_use;
	unsigned char data[MED_MAXSIZE];
}memory_medium;

typedef struct {
	BOOLEAN in_use;
	unsigned char data[BIG_MAXSIZE];
}memory_big;

#endif
