#include "../include/osi_include_int.h"
#include "../include/osi_include_ext.h"

#ifndef MEMORY_STATIC_ALLOC
#define MEMORY_STATIC_ALLOC FALSE
#endif

#if MEMORY_STATIC_ALLOC
#define SMALL_NUM   3
#define MEDIUM_NUM  3
#define BIG_NUM     3

static memory_small memory_sm[SMALL_NUM];
static memory_medium memory_med[MEDIUM_NUM];
static memory_big memory4_big[BIG_NUM];
#endif

void *osi_malloc(u32 size)
{
    void *ptr = NULL;
#if MEMORY_STATIC_ALLOC
    int i;
    if(size < (SMA_MAXSIZE+1)) {
        for(i = 0; i < SMALL_NUM; i++) {
            if(!memory_sm[i].in_use) {
                osi_memset(memory_sm[i].data, 0, SMA_MAXSIZE);
                memory_sm[i].in_use = TRUE;
                return memory_sm[i].data;
            }
        }
    }
    else if(size > SMA_MAXSIZE && size < (MED_MAXSIZE +1)) {
        for(i = 0; i < MEDIUM_NUM; i++) {
            if(!memory_med[i].in_use) {
                osi_memset(memory_sm[i].data, 0, MED_MAXSIZE);
                memory_sm[i].in_use = TRUE;
                return memory_med[i].data;
            }
        }
    }
    else if(size > MED_MAXSIZE && size < (BIG_MAXSIZE +1)) {
        for(i = 0; i < BIG_NUM; i++) {
            if(!memory4_big[i].in_use) {
                osi_memset(memory_sm[i].data, 0, BIG_MAXSIZE);
                memory_sm[i].in_use = TRUE;
                return memory4_big[i].data;
            }
        }
    }
    return NULL;
#else
    ptr = malloc(size);
    osi_memset(ptr, 0, size);
    return ptr;
#endif
}

void *osi_memset(void *s, s32 ch, u32 n)
{
    return memset(s, ch, n);
}

void osi_free(void *ptr)
{
#if MEMORY_STATIC_ALLOC
    int i;

    for(i = 0; i < SMALL_NUM; i++) {
        if(memory_sm[i].data == ptr) {
            memory_sm[i].in_use = FALSE;
            return;
        }
    }

    for(i = 0; i < MEDIUM_NUM; i++) {
        if(memory_med[i].data == ptr) {
            memory_med[i].in_use = FALSE;
            return;
        }
    }

    for(i = 0; i < BIG_NUM; i++) {
        if(memory4_big[i].data == ptr) {
            memory4_big[i].in_use = FALSE;
            return;
        }
    }
    return;
#else
    free(ptr);
    return;
#endif
}

void *osi_memcpy(void *dest, const void *src, u32 n)
{
    return memcpy(dest, src, n);
}

int osi_memcmp(void *dest, const void *src, u32 n)
{
    return memcmp(dest, src, n);
}

void osi_rtk_ndelay(u64 nsecs)
{
    //UNUSED(nsecs);
    //ndelay(nsecs);
}

void osi_rtk_udelay(u64 usecs)
{
    udelay(usecs);
}

void osi_rtk_mdelay(u64 msecs)
{
    mdelay(msecs);
}

void osi_buff_init(void)
{
#if MEMORY_STATIC_ALLOC
    osi_memset(memory_sm, 0, sizeof(memory_small));
    osi_memset(memory_med, 0, sizeof(memory_medium));
    osi_memset(memory4_big, 0, sizeof(memory_big));
#endif
}

