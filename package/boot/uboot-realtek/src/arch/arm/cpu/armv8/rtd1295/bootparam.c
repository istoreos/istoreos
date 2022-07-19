#include <linux/ctype.h>
#include <linux/string.h>
#include <linux/stddef.h>
#include <asm/arch/io.h>
#include <asm/arch/system.h>

#include <common.h>
#include <parse_h.h>
#include <asm/arch/bootparam.h>
#include <asm/arch/factorylib.h>
#include <asm/arch/fw_info.h>

#define DEBUG(msg,arg...)   do { printf("[%s %3d]:", __FILE__, __LINE__); printf(msg,##arg); } while(0)
//#define DEBUG(msg,arg...)

#define BOOT_PARAM_FILE_NAME	FACTORY_HEADER_FILE_NAME"000BootParam.h"
#define BOOT_PART_FILE_NAME		FACTORY_HEADER_FILE_NAME"layout.txt"
#define BOOT_TVSYSTEM_FILE_NAME		FACTORY_HEADER_FILE_NAME"video_rpc.bin"
#define BOOT_CHECKSUM_FILE_NAME		FACTORY_HEADER_FILE_NAME"edid_checksum.bin"

extern uchar boot_logo_enable;
extern uint custom_logo_src_width;
extern uint custom_logo_src_height;
extern uint custom_logo_dst_width;
extern uint custom_logo_dst_height;

#ifdef CONFIG_SYS_AUTO_DETECT
extern uchar checksum_128;
extern uchar checksum_256;
#endif
/************************************************************************
**
** get boot info in factory area of flash
**
*************************************************************************/
void get_bootparam(void)
{
	char *dst_addr;
	char *retAddr;
	int dst_length;
	uint retVal;

	//display_evaluate_time("get_bootparam-0");

	if (factory_read(BOOT_PARAM_FILE_NAME, &dst_addr, &dst_length)) {
		printf("------------can't find %s\n", BOOT_PARAM_FILE_NAME);	
#ifdef CONFIG_NAS_ENABLE
		// Set up default values
		printf("Set up default values\n");
		boot_logo_enable = 1;
		custom_logo_src_width = 1920;
		custom_logo_src_height = 1080;
		custom_logo_dst_width = 3840;
		custom_logo_dst_height = 2160;
#endif
	}
	else {
		printf("------------%s found\n", BOOT_PARAM_FILE_NAME);
		
		/****** for logo display ******/	
		//source
		if (parse_h("BOOT_LOGO_ENABLE", dst_addr, (uint)dst_length, &retVal, &retAddr) == 0) {
			boot_logo_enable = retVal;
			debug("BOOT_LOGO_ENABLE=%d\n", retVal);
		}
		else {
			DEBUG("can't find boot_logo_enable\n");
		}
				
		if (parse_h("CUSTOM_LOGO_SRC_WIDTH", dst_addr, (uint)dst_length, &retVal, &retAddr) == 0) {
			custom_logo_src_width = retVal;
			debug("CUSTOM_LOGO_SRC_WIDTH=%d\n", retVal);
		}
		else {
			DEBUG("can't find custom_logo_src_width\n");
		}
		
		if (parse_h("CUSTOM_LOGO_SRC_HEIGHT", dst_addr, (uint)dst_length, &retVal, &retAddr) == 0) {
			custom_logo_src_height = retVal;
			debug("CUSTOM_LOGO_SRC_HEIGHT=%d\n", retVal);
		}
		else {
			DEBUG("can't find custom_logo_src_height\n");
		}
		
		//destination
		if (parse_h("CUSTOM_LOGO_DST_WIDTH", dst_addr, (uint)dst_length, &retVal, &retAddr) == 0) {
			custom_logo_dst_width = retVal;
			debug("CUSTOM_LOGO_DST_WIDTH=%d\n", retVal);
		}
		else {
			DEBUG("can't find custom_logo_dst_width\n");
		}
		
		if (parse_h("CUSTOM_LOGO_DST_HEIGHT", dst_addr, (uint)dst_length, &retVal, &retAddr) == 0) {
			custom_logo_dst_height = retVal;
			debug("CUSTOM_LOGO_DST_HEIGHT=%d\n", retVal);
		}
		else {
			DEBUG("can't find custom_logo_dst_height\n");
		}
		/****** for logo display ******/
	}
	if(boot_logo_enable)
		printf("[logo]src w/h=%d/%d dst w/h=%d/%d\n",custom_logo_src_width ,custom_logo_src_height
													,custom_logo_dst_width ,custom_logo_dst_height);
	//display_evaluate_time("get_bootparam-1");
}

/************************************************************************
**
** get video_rpc.bin in factory area of flash
**
*************************************************************************/
#ifdef CONFIG_SYS_AUTO_DETECT
int get_one_step_info(void)
{
	char *dst_addr,*dst_addr_chk;
	int dst_length,dst_length_chk;

	//printf("%s:\n", __FUNCTION__);

	if (factory_read(BOOT_TVSYSTEM_FILE_NAME, &dst_addr, &dst_length)) {
		printf("------------can't find %s\n", BOOT_TVSYSTEM_FILE_NAME);
		//printf("dst_addr=%x\n, dst_length=%d\n",dst_addr,dst_length);
		return 0;
	}
	else {
		printf("------------%s found\n", BOOT_TVSYSTEM_FILE_NAME);
				
    	rtd_outl( VO_RESOLUTION, 0xee0bdec0); /* set magic pattern in first word */
		memcpy((void *)(uintptr_t)VO_RESOLUTION+4, dst_addr ,dst_length);		
		flush_cache(VO_RESOLUTION, 4+ dst_length);
		
		
		if (factory_read(BOOT_CHECKSUM_FILE_NAME, &dst_addr_chk, &dst_length_chk)) 
		{
			printf("------------can't find %s\n", BOOT_CHECKSUM_FILE_NAME);
			//printf("dst_addr=%x\n, dst_length=%d\n",dst_addr,dst_length);
			return 0;
		}
		else
		{				
			memcpy(&checksum_128, dst_addr_chk ,sizeof(unsigned char));
			memcpy(&checksum_256, dst_addr_chk+sizeof(unsigned char),sizeof(unsigned char));	
			if(checksum_128==0 && checksum_256==0)
				return 0;			
		}
		
		return 1;
	}


}
#endif

