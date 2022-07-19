
/***********************************************************************
 *
 *  md.c
 *
 *  Implementation of MD module
 *
 * 
 *
 ************************************************************************/


/************************************************************************
 *  Include files
 ************************************************************************/
#include <common.h>
#include <asm/io.h>
#include <asm/arch/rbus/md_reg.h>
#include <malloc.h>
#include <asm/arch/md.h>



/************************************************************************
 *  Definitions
 ************************************************************************/
#define SS_BLK_LENGTH              (1024*1024)
#define rtd_ini(offset)           	(*(volatile unsigned int *)(offset))
#define rtd_inl(offset)           	(*(volatile unsigned long *)(offset))
#define rtd_outi(offset,val)		(*(volatile unsigned int *)(offset) = val)
#define rtd_outl(offset,val)		(*(volatile unsigned long *)(offset) = val)

/************************************************************************
 *  Public variables
 ************************************************************************/


/************************************************************************
 *  Static variables
 ************************************************************************/


/************************************************************************
 *  Static function prototypes
 ************************************************************************/
unsigned int *allocat_md_cmd(unsigned int num_of_cmd);
#define CACHELINE_SIZE CONFIG_SYS_CACHELINE_SIZE

/************************************************************************
 *  Implementation : Public functions
 ************************************************************************/
int md_memcpy(void *dst, void *src, unsigned int len)
{
	unsigned int *cmd;
	unsigned int num_of_cmd = len / SS_BLK_LENGTH + 1;
	unsigned int i, ith_len;
	unsigned int ith_dst = (unsigned int)(uintptr_t)dst;
	unsigned int ith_src = (unsigned int)(uintptr_t)src;

	if ((cmd = allocat_md_cmd(num_of_cmd)) == NULL) {
		
		if( (int)(uintptr_t)dst < ARM_ROMCODE_SIZE )
			printf("Using MD failed.");			
		else
			memcpy(dst, src, len);	// use memcpy instead...		
		return 0;
	}	
      
	for (i = 0; i < num_of_cmd; i++) {
		
		ith_len = (len > SS_BLK_LENGTH ? SS_BLK_LENGTH : len);	
		cmd[i*4]   = 0x5;
		cmd[i*4+1] = ith_dst;
		cmd[i*4+2] = ith_src;
		cmd[i*4+3] = ith_len;
		ith_dst += ith_len;
		ith_src += ith_len;
		len -= ith_len;		
	}
	sync();
	flush_cache( (unsigned long)(uintptr_t)cmd,4* sizeof(unsigned int)*num_of_cmd);

	rtd_outi(MD_KMQ_CNTL,0x6);
	rtd_outi(MD_KMQ_INT_STATUS,0x3e);
	rtd_outi(MD_KMQBASE , (unsigned int)(uintptr_t)cmd);
	rtd_outi(MD_KMQRDPTR, (unsigned int)(uintptr_t)cmd);
	rtd_outi(MD_KMQWRPTR,(unsigned int)(uintptr_t)cmd + num_of_cmd * sizeof(unsigned int) * 4);
	rtd_outi(MD_KMQLIMIT,(rtd_ini(MD_KMQWRPTR) + sizeof(unsigned int) * 4));

	rtd_outi(MD_KMQ_CNTL, 0x7);
	i = 100000;
	while (i--) {
		// check idle
		if (rtd_ini(MD_KMQ_CNTL) & 0x8)
			return 0;
		
		// check error
		if (rtd_ini(MD_KMQ_INT_STATUS) & 0x2) {
			printf("[ERROR] opcode error\n");
			return -1;
		}

		if (rtd_ini(MD_KMQ_INT_STATUS) & 0x4) {
			printf("[ERROR] length error\n");
			return -2;
		}
	}
	printf("[ERROR] MD no response\n");

	return -1;
}
/*
void md_flash2mem(void *dst, void *src, UINT32 len)
{
	unsigned int remain = len & 0x3;
	
	// use memcpy instead if not word-aligned addres
	if (((UINT32)dst & 0x3) || ((UINT32)src & 0x3)) {
		memcpy(dst, src, len);
		return;
	}
	
	//printf("[DEBUG] %s(0x%x, 0x%x, 0x%x)\n", __FUNCTION__, (UINT32)dst, (UINT32)src, len);
	// flush cache before DMA
	sys_dcache_flush_all();

	// 1. copy with word-aligned
	REG32(MD_FDMA_DDR_SADDR) = (UINT32)dst;
	REG32(MD_FDMA_FL_SADDR) = (UINT32)src;
	REG32(MD_FDMA_CTRL2) = 0x3c000000 | ((len - remain) & 0x1ffffff);
	sys_sync();
	REG32(MD_FDMA_CTRL1) = 3;	// go
	while ((REG32(MD_FDMA_CTRL1) & 0x1) != 0);
	
	// 2. copy remain
	if (remain)
		memcpy(dst + (len - remain), src + (len - remain), remain);
}*/

unsigned int *allocat_md_cmd(unsigned int num_of_cmd)
{
	unsigned int *cmd;
	unsigned int num_of_bytes = 4 * sizeof(unsigned int) * num_of_cmd;
        
                	
        cmd = (unsigned int*)memalign(16,num_of_bytes); 
        if (!cmd) {
            printf("Can not allocate memory of MD\n");
            free(cmd);
            return NULL;
        }               
        
	memset(cmd, 0, num_of_bytes);
	
	return cmd;
}
