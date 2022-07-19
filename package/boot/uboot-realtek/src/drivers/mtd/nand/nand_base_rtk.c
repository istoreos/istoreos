/******************************************************************************
 * $Id: nand_base_rtk.c 317223 2010-06-01 07:38:49Z alexchang2131 $
 * drivers/mtd/nand/nand_base_rtk.c
 * Overview: Realtek MTD NAND Driver
 * Copyright (c) 2008 Realtek Semiconductor Corp. All Rights Reserved.
 * Modification History:
 *    #000 2008-06-10 Ken-Yu   create file
 *    #001 2008-09-10 Ken-Yu   add BBT and BB management
 *    #002 2008-09-28 Ken-Yu   change r/w from single to multiple pages
 *    #003 2008-10-09 Ken-Yu   support single nand with multiple dies
 *    #004 2008-10-23 Ken-Yu   support multiple nands
 *
 *******************************************************************************/
//#include <linux/delay.h>
//#include <linux/errno.h>
//#include <linux/sched.h>
#include <linux/types.h>
#include <linux/mtd/mtd.h>
//#include <linux/interrupt.h>
//#include <linux/slab.h>
#include <asm/io.h>
#include <linux/bitops.h>
//#include <linux/parser.h>
// Ken-Yu
#include <mtd/mtd-abi.h>
//#include <linux/mtd/rtk_nand_reg.h>
#include <linux/mtd/rtk_nand.h>
//#include <asm/r4kcache.h>
//#include <asm/page.h>
//#include <linux/jiffies.h>
//#include <asm/mach-venus/platform.h>
//#include <asm/mach-rtk_dmp/platform.h>

#include <common.h>
#include <asm/arch/rbus/nand_reg.h>
//#include <linux/bitops.h>
//#include <linux/string.h>
//#include <linux/kernel.h>
//#include <linux/proc_fs.h>


#ifdef CONFIG_NAND_MULTI_READ_FOR_CARDREADER
	#define NAND_POWEROFF_CARDREADER_WITH_MULTI_READ	(1)//add for fixing card reader share pin bug. alexchang 0831-2010
#else
	#define NAND_POWEROFF_CARDREADER_WITH_MULTI_READ	(0)//add for fixing card reader share pin bug. alexchang 0831-2010
#endif

#ifdef CONFIG_NAND_READ_SKIP_UPDATE_BBT
	#define NAND_READ_SKIP_UPDATE_BBT		(1)//add for fixing card reader share pin bug. alexchang 0901-2010
#else
	#define NAND_READ_SKIP_UPDATE_BBT		(0)//add for fixing card reader share pin bug. alexchang 0901-2010
#endif
//#ifdef CONFIG_NAND_BBT_NEW_MECHANISM
//	#define NAND_BBT_NEW_MECHANISM		(1)//add for fixing card reader share pin bug. alexchang 1026-2010
//	static struct semaphore nf_BBT_sem;
//#else
//	#define NAND_BBT_NEW_MECHANISM		(0)//add for fixing card reader share pin bug. alexchang 1026-2010
//#endif

//static DECLARE_MUTEX (sem_rd);
//static DECLARE_MUTEX (sem_wte);
//static DECLARE_MUTEX (sem_bbt);
//static struct semaphore sem_rd;
//static struct semaphore sem_wte;
//static struct semaphore sem_bbt;



static unsigned char g_isSysSecure = 0;
extern unsigned char g_isRandomize;
extern char rtknand_info[128];
#define Nand_Block_Isbad_Slow_Version 0
#define MTD_SEM_RETRY_COUNT	(0x40)
#define NOTALIGNED(mtd, x) (x & (mtd->writesize-1)) != 0
#define NAND_CP_RW_DISABLE (0xFFFFFFFF)

#define check_end(mtd, addr, len)					\
do {									\
	if (mtd->size == 0) 						\
		return -ENODEV;						\
	else								\
	if ((addr + len) > mtd->size) {					\
		printk (				\
			"%s: attempt access past end of device\n",	\
			__FUNCTION__);					\
		return -EINVAL;						\
	}								\
} while(0)

#define check_page_align(mtd, addr)					\
do {									\
	if (addr & (mtd->writesize - 1)) {				\
		printk (				\
			"%s: attempt access non-page-aligned data\n",	\
			__FUNCTION__);					\
		printk (				\
			"%s: mtd->writesize = 0x%x\n",			\
			__FUNCTION__,mtd->writesize);			\
		return -EINVAL;						\
	}								\
} while (0)

#define check_block_align(mtd, addr)					\
do {									\
	if (addr & (mtd->erasesize - 1)) {				\
		printk (				\
			"%s: attempt access non-block-aligned data\n",	\
			__FUNCTION__);					\
		return -EINVAL;						\
	}								\
} while (0)

#define check_len_align(mtd,len)					\
do {									\
	if (len & (512 - 1)) {          	 			\
		printk (				\
               	      "%s: attempt access non-512bytes-aligned mem\n",	\
			__FUNCTION__);					\
		return -EINVAL;						\
	}								\
} while (0)

//static DECLARE_MUTEX (mtd_sem);
extern char *rtkNF_parse_token(const char *parsed_string, const char *token);
extern unsigned int rtkNF_getBootcodeSize(void);
extern unsigned int rtkNF_getFactParaSize(void);
extern int is_jupiter_cpu(void);
extern int is_saturn_cpu(void);
extern int is_darwin_cpu(void);
extern int is_macarthur_cpu(void);
extern int is_nike_cpu(void);
extern int is_venus_cpu(void);
extern int is_neptune_cpu(void);
extern int is_mars_cpu(void);
#ifdef NAS_ENABLE
extern int rtk_plat_get_fw_desc_table_start(void);
#endif

unsigned int g_mtd_BootcodeSize = 0;

#if NAND_POWEROFF_CARDREADER_WITH_MULTI_READ
/*
	parse_token can parse a string and extract the value of designated token.
		parsed_string: The string to be parsed.
		token: the name of the token
		return value: If return value is NULL, it means that the token is not found.
			If return value is "non zero", it means that the token is found, and return value will be a string that contains the value of that token.
			If the token doesn't have a value, return value will be a string that contains empty string ("\0").
			If return value is "non zero", "BE SURE" TO free it after you donot need it.

		Exp:
			char *value=parse_token("A1 A2=222 A3=\"333 333\"", "A0");
				=> value=NULL
			char *value=parse_token("A1 A2=222 A3=\"333 333\"", "A1");
				=> value points to a string of "\0"
			char *value=parse_token("A1 A2=222 A3=\"333 333\"", "A2");
				=> value points to a string of "222"
			char *value=parse_token("A1 A2=222 A3=\"333 333\"", "A3");
				=> value points to a string of "333 333"
*/
static char *NF_parse_token(const char *parsed_string, const char *token)
{
	const char *ptr = parsed_string;
	const char *start, *end, *value_start, *value_end;
	char *ret_str;

	while(1) {
		value_start = value_end = 0;
		for(;*ptr == ' ' || *ptr == '\t'; ptr++)	;
		if(*ptr == '\0')	break;
		start = ptr;
		for(;*ptr != ' ' && *ptr != '\t' && *ptr != '=' && *ptr != '\0'; ptr++) ;
		end = ptr;
		if(*ptr == '=') {
			ptr++;
			if(*ptr == '"') {
				ptr++;
				value_start = ptr;
				for(; *ptr != '"' && *ptr != '\0'; ptr++)	;
				if(*ptr != '"' || (*(ptr+1) != '\0' && *(ptr+1) != ' ' && *(ptr+1) != '\t')) {
					printk("system_parameters error! Check your parameters.");
					break;
				}
			} else {
				value_start = ptr;
				for(;*ptr != ' ' && *ptr != '\t' && *ptr != '\0' && *ptr != '"'; ptr++) ;
				if(*ptr == '"') {
					printk("system_parameters error! Check your parameters.");
					break;
				}
			}
			value_end = ptr;
		}

		if(!strncmp(token, start, end-start)) {
			if(value_start) {
				ret_str = kmalloc(value_end-value_start+1, GFP_KERNEL);
				strncpy(ret_str, value_start, value_end-value_start);
				ret_str[value_end-value_start] = '\0';
				return ret_str;
			} else {
				ret_str = kmalloc(1, GFP_KERNEL);
				strcpy(ret_str, "");
				return ret_str;
			}
		}
	}

	return (char*)NULL;
}
#endif

#if NAND_POWEROFF_CARDREADER_WITH_MULTI_READ
u32 NF_rtk_power_gpio=0;
u32 NF_rtk_power_bits=0;
void NF_rtkcr_card_power(u8 status)
{
    void __iomem *mmio = (void __iomem *) NF_rtk_power_gpio;
    if(status==0){ //power on
        printk("Card Power on\n");
        writel(readl(mmio) & ~(1<<NF_rtk_power_bits),mmio);
    }else{          //power off
        printk("Card Power off\n");
        writel(readl(mmio) | (1<<NF_rtk_power_bits),mmio);
    }
}
void NF_rtkcr_chk_param(u32 *pparam, u32 len, u8 *ptr)
{
    unsigned int value,i;
    for(i=0;i<len;i++){
        value = ptr[i] - '0';
        if((value >= 0) && (value <=9))
        {
            *pparam+=value<<(4*(len-1-i));
            continue;
        }
        value = ptr[i] - 'a';
        if((value >= 0) && (value <=5))
        {
            value+=10;
            *pparam+=value<<(4*(len-1-i));
            continue;
        }
        value = ptr[i] - 'A';
        if((value >= 0) && (value <=5))
        {
            value+=10;
            *pparam+=value<<(4*(len-1-i));
            continue;
        }
    }
}
int NF_rtkcr_get_gpio(void)
{
    unsigned char *cr_param;
    void __iomem *mmio;
//    cr_param=(char *)NF_parse_token(platform_info.system_parameters,"cr_pw");
    if(cr_param){
        NF_rtkcr_chk_param(&NF_rtk_power_gpio,4,cr_param);
        NF_rtkcr_chk_param(&NF_rtk_power_bits,2,cr_param+5);

        mmio = (void __iomem *) (NF_rtk_power_gpio+0xb8010000);
        writel(readl(mmio) | (1<<NF_rtk_power_bits),mmio); //enable GPIO output

        if((NF_rtk_power_gpio & 0xf00) ==0x100){
            NF_rtk_power_gpio+=0xb8010010;
        }else if((NF_rtk_power_gpio & 0xf00) ==0xd00){
            NF_rtk_power_gpio+=0xb8010004;
        }else{
            printk(KERN_ERR "wrong GPIO of card's power.\n");
            return -1;
        }
        printk("power_gpio = 0x%x\n",NF_rtk_power_gpio);
        printk("power_bits = %d\n",NF_rtk_power_bits);
        return 0;
    }
    printk(KERN_ERR "Can't find GPIO of card's power.\n");
    return -1;

}

#endif

int check_buffer_all_one(char* buf, int len) {
	int i = 0;
	int ret = 1;
	
	for (i=0 ; i<len ; i++) 
	{
		if ( *(buf+i) != 0xff ) {
			ret = 0;
			break;
		}
	}
	
	return ret;
}

/* Realtek supports nand chip types */
/* Micorn */
#define MT29F2G08AAD	0x2CDA8095	//SLC, 256 MB, 1 dies
#define MT29F2G08ABAE	0x2CDA9095  //SLC, 256MB, 1 dies
#define MT29F1G08ABADA  0x2CF18095  //SLC, 128MB, 1 dies
#define MT29F4G08ABADA  0x2CDC9095  //SLC, 512MB, 1 dies
#define MT29F32G08CBACA  0x2C68044A  //MLC, 4GB, 1 dies
#define MT29F64G08CBAAA  0x2C88044B //MLC, 8GB, 1dies
#define MT29F8G08ABABA   0x2C380026  //Micron 1GB   (SLC single die)
#define MT29F4G08ABAEA	 0x2CDC90A6	// Micron 4Gb  (SLC single die)
#define MT29F64G08CBABA	 0x2C64444B	// Micron 64G	(MLC) 
#define MT29F32G08CBADA	 0x2C44444B	// Micron 32Gb (MLC)

/* STMicorn */
#define NAND01GW3B2B	0x20F1801D	//SLC, 128 MB, 1 dies
#define NAND01GW3B2C	0x20F1001D	//SLC, 128 MB, 1 dies, son of NAND01GW3B2B
#define NAND02GW3B2D	0x20DA1095	//SLC, 256 MB, 1 dies
#define NAND04GW3B2B	0x20DC8095	//SLC, 512 MB, 1 dies
#define NAND04GW3B2D	0x20DC1095	//SLC, 512 MB, 1 dies
#define NAND04GW3C2B	0x20DC14A5	//MLC, 512 MB, 1 dies
#define NAND08GW3C2B	0x20D314A5	//MLC, 1GB, 1 dies

/* Hynix Nand */
#define HY27UF081G2A	0xADF1801D	//SLC, 128 MB, 1 dies
#define HY27UF081G2B	0xADF1801D	//SLC, 128 MB, 1 dies

#define HY27UF082G2A	0xADDA801D	//SLC, 256 MB, 1 dies
#define HY27UF082G2B	0xADDA1095	//SLC, 256 MB, 1 dies
#define HY27UF084G2B	0xADDC1095	//SLC, 512 MB, 1 dies
#define HY27UF084G2M	0xADDC8095	//SLC, 512 MB, 1 dies
	/* HY27UT084G2M speed is slower, we have to decrease T1, T2 and T3 */
#define HY27UT084G2M	0xADDC8425	//MLC, 512 MB, 1 dies, BB check at last page, SLOW nand
#define HY27UT084G2A	0xADDC14A5	//MLC, 512 MB, 1 dies
#define H27U4G8T2B		0xADDC14A5	//MLC, 512 MB, 1 dies
#define HY27UT088G2A	0xADD314A5	//MLC, 1GB, 1 dies, BB check at last page
#define HY27UG088G5M	0xADDC8095	//SLC, 1GB, 2 dies
#define HY27UG088G5B	0xADDC1095	//SLC, 1GB, 2 dies
#define H27U8G8T2B		0xADD314B6	//MLC, 1GB, 1 dies, 4K page
#define H27UAG8T2A		0xADD59425	//MLC, 2GB, 1 dies, 4K page
#define H27UAG8T2B		0xADD5949A	//MLC, 2GB, 1 dies, 8K page
#define H27U2G8F2C		0xADDA9095	//SLC, 256 MB, 1 dies, 2K page
#define H27U4G8F2D      0xADDC9095  //SLC, 512MB, 1dies, 2K page
#define H27U1G8F2B      0xADF1001D	//SLC, 128MB, 1dies, 2K page
#define H27UBG8T2A		0xADD7949A	//MLC, 4GB, 1 dies, 8K page
#define H27UBG8T2B		0xADD794DA	//MLC, 4GB, 1 dies, 8K page
#define H27UBG8T2C		0xADD79491	// Hynix 32Gb	(MLC)
#define H27UCG8T2B		0xADDE94EB	// Hynix 64Gb

/* Samsung Nand */
#define K9F1G08U0E	0xECF10095	//SLC, 128 MB, 1 dies
#define K9F1G08U0D	0xECF10015	//SLC, 128 MB, 1 dies
#define K9F2G08U0B	0xECDA1095	//SLC, 256 MB, 1 dies
#define K9G4G08U0A	0xECDC1425	//MLC, 512 MB, 1 dies, BB check at last page
#define K9G4G08U0B	0xECDC14A5	//MLC, 512 MB, 1 dies, BB check at last page
#define K9F4G08U0B	0xECDC1095	//SLC, 512 MB, 1 dies
#define K9G8G08U0A	0xECD314A5	//MLC, 1GB, 1 dies, BB check at last page
#define K9G8G08U0M	0xECD31425	//MLC, 1GB, 1 dies, BB check at last page
#define K9K8G08U0A	0xECD35195	//SLC, 1GB, 1 dies
#define K9F8G08U0M	0xECD301A6	//SLC, 1GB, 1 dies, 4K page
#define K9K8G08U0D	0xECD31195  //SLC, 1GB, 1 dies

/* Toshiba */
#define TC58NVG0S3C	0x98F19095	//128 MB, 1 dies
#define TC58NVG0S3E	0x98D19015	//128 MB, 1 dies
#define TC58NVG1S3C	0x98DA9095	//256 MB, 1 dies
#define TC58NVG1S3E	0x98DA9015	//256 MB, 1 dies
#define TC58NVG2S3E	0x98DC9015	//512 MB, 1 dies
#define TC58NVG2S0HTA00	0x98DC9026	//512 MB, 1 dies
#define TC58NVG5D2F	0x98D79432	//MLC, 4GB, 1 dies, 8K page
#define TC58NVG4D2E 0x98D59432  //MLC, 2GB, 1 dies, 8K page
#define TC58NVG2S0F 0x98DC9026  //SLC,512MB 1 dies,4K page
#define TC58NVG2S0FTA00	0x98D39026	// Toshiba 4Gb  (SLC single die)
#define TC58NVG5D2H 0x98D79432
#define TC58BVG0S3H     0x98F18015	//SLC, 1GB, 1 dies
#define TC58BVG1S3H     0x98DA9015	//SLC, 2GB, 1 dies
#define TC58NVG0S3H     0x98F18015	//SLC, 1GB, 1 dies
#define TC58NVG1S3H     0x98DA9015	//SLC, 2GB, 1 dies
#define TC58TEG5DCJT	0x98D78493	// Toshiba 32Gb (MLC)
#define TC58TEG6DCJT	0x98DE8493	// Toshiba 64Gb (MLC)

#define TC58TEG6DDK     0x98DE9493
//#define TH58TEG7DDK     0x98DE9493
//#define TH58TEG8DDK     0x983A9593

/* Macronix */
#define MX30LF4G18AC 0xC2DC9095 // 512 MB, 1 dies
#define MX30LF2G18AC 0xC2DA9095 // 256 MB, 1 dies
#define MX30LF1G18AC 0xC2F18095 // 128 MB, 1 dies
#define MX30LF1G08AM 0xC2F1801D // 128 MB, 1 dies
#define MX30LF1208AA 0xC2F0801D // 64MB, 1 dies

#define EN27LN4G08  0xC8DC9095

/*Winbond*/
#define W29N01GV 0xEFF18095
#define W29N02GV 0xEFDA9095
#define W29N01HV 0xEFF10095

/* ESMT */
#define F59L1G81MA  0xC8D18095
#define F59L1G81A  0x92F18095
#define F59L2G81A  0xC8DA9095

/*MIRA*/
//#define PSU2GA30AT 0X7F7F7F7F
#define PSU2GA30BT    0xC8DA9095
#define PSU4GA30AT    0xC8DC9095

/*Spansion*/
#define S34ML01G1	        0x01F1001D
#define S34ML02G1	        0x01DA9095

/* RTK Nand Chip ID list */
static device_type_t nand_device[] =
{
 {"MT29F2G08AAD", MT29F2G08AAD, 0x10000000, 0x10000000, 2048, 64*2048, 64, 1, 0, 0xff, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"MT29F2G08ABAE", MT29F2G08ABAE, 0x10000000, 0x10000000, 2048, 64*2048, 64, 1, 0, 0x6, 0xff, 0xff,0x01, 0x01, 0x01, 0x00},
 {"MT29F1G08ABADA", MT29F1G08ABADA, 0x8000000, 0x8000000, 2048, 64*2048, 64, 1, 0, 0xff, 0xff, 0xff,0x01, 0x01, 0x01, 0x00},
 {"MT29F4G08ABADA", MT29F4G08ABADA, 0x20000000, 0x20000000, 2048, 64*2048, 64, 1, 0, 0xff, 0xff, 0xff,0x01, 0x01, 0x01, 0x00},
 {"MT29F32G08CBACA", MT29F32G08CBACA, 0x100000000, 0x100000000, 4096, 256*4096, 224, 1, 0, 0xa9, 0xff, 0x18,0x01, 0x01, 0x01, 0x18},
 {"MT29F64G08CBAAA", MT29F64G08CBAAA, 0x200000000, 0x200000000, 8192, 256*8192, 448, 1, 0, 0xff, 0xff, 0x18,0x00, 0x00, 0x00, 0x18},
 {"MT29F64G08CBABA", MT29F64G08CBABA, 0x200000000, 0x200000000, 8192, 256*8192, 448, 1, 0, 0xa9, 0xff, 0x28,0x01, 0x01, 0x01, 0x28},
 {"MT29F8G08ABABA", MT29F8G08ABABA, 0x40000000, 0x40000000, 4096, 128*4096, 224, 1, 0, 0x85, 0xff, 0xff,0x01, 0x01, 0x01, 0x00},
 //{"MT29F4G08ABAEA", MT29F4G08ABAEA, 0x10000000, 0x10000000, 2048, 128*1024, 64, 1, 0, 0x54, 0xff, 0xff,0x01, 0x01, 0x01, 0x00},  //20161206cloud mark for data wrong
{"MT29F4G08ABAEA", MT29F4G08ABAEA, 0x20000000, 0x20000000, 4096, 256*1024, 64, 1, 0, 0x54, 0xff, 0xff,0x01, 0x01, 0x01, 0x00},
 {"MT29F32G08CBADA", MT29F32G08CBADA, 0x100000000, 0x100000000, 8192, 256*8192, 744, 1, 0, 0xa9, 0xff, 0x28,0x00, 0x00, 0x00, 0x28},

 {"NAND01GW3B2B", NAND01GW3B2B, 0x8000000, 0x8000000, 2048, 64*2048, 64, 1, 0, 0xff, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"NAND01GW3B2C", NAND01GW3B2C, 0x8000000, 0x8000000, 2048, 64*2048, 64, 1, 0, 0xff, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"NAND02GW3B2D", NAND02GW3B2D, 0x10000000, 0x10000000, 2048, 64*2048, 64, 1, 0, 0x44, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"NAND04GW3B2B", NAND04GW3B2B, 0x20000000, 0x20000000, 2048, 64*2048, 64, 1, 0, 0x20, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"NAND04GW3B2D", NAND04GW3B2D, 0x20000000, 0x20000000, 2048, 64*2048, 64, 1, 0, 0x54, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"NAND04GW3C2B", NAND04GW3C2B, 0x20000000, 0x20000000, 2048, 128*2048, 64, 1, 1, 0x24, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"NAND08GW3C2B", NAND08GW3C2B, 0x40000000, 0x40000000, 2048, 128*2048, 64, 1, 1, 0x34, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"HY27UF081G2A", HY27UF081G2A, 0x8000000, 0x8000000, 2048, 64*2048, 64, 1, 0, 0xff, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"HY27UF081G2B", HY27UF081G2B, 0x8000000, 0x8000000, 2048, 64*2048, 64, 1, 0, 0xff, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"HY27UF082G2A", HY27UF082G2A, 0x10000000, 0x10000000, 2048, 64*2048, 64, 1, 0, 0x00, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"HY27UF082G2B", HY27UF082G2B, 0x10000000, 0x10000000, 2048, 64*2048, 64, 1, 0, 0x44, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"HY27UF084G2B", HY27UF084G2B, 0x20000000, 0x20000000, 2048, 64*2048, 64, 1, 0, 0x54, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"HY27UT084G2A", HY27UT084G2A, 0x20000000, 0x20000000, 2048, 128*2048, 64, 1, 1, 0x24, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"H27U4G8T2B", H27U4G8T2B, 0x20000000, 0x20000000, 2048, 128*2048, 64, 1, 1, 0x24, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"HY27UT088G2A", HY27UT088G2A, 0x40000000, 0x40000000, 2048, 128*2048, 64, 1, 1, 0x34, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"HY27UF084G2M", HY27UF084G2M, 0x20000000, 0x20000000, 2048, 64*2048, 64, 1, 0, 0xff, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"HY27UT084G2M", HY27UT084G2M, 0x20000000, 0x20000000, 2048, 128*2048, 64, 1, 1, 0xff, 0xff, 0xff, 0x04, 0x04, 0x04, 0x00},
 {"HY27UG088G5M", HY27UG088G5M, 0x40000000, 0x20000000, 2048, 64*2048, 64, 2, 0, 0xff, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"HY27UG088G5B", HY27UG088G5B, 0x40000000, 0x20000000, 2048, 64*2048, 64, 2, 0, 0x54, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"H27U8G8T2B", H27U8G8T2B, 0x40000000, 0x40000000, 4096, 128*4096, 128, 1, 1, 0x34, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"H27UAG8T2A", H27UAG8T2A, 0x80000000, 0x80000000, 4096, 128*4096, 224, 1, 1, 0x44, 0x41, 0x18, 0x01, 0x01, 0x01, 0x0c},
 {"H27UAG8T2B", H27UAG8T2B, 0x80000000, 0x80000000, 8192, 256*8192, 448, 1, 1, 0x74, 0x42, 0x18, 0x01, 0x01, 0x01, 0x18},
 {"H27U2G8F2C", H27U2G8F2C, 0x10000000, 0x10000000, 2048, 64*2048, 64, 1, 1, 0x44, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"H27U4G8F2D", H27U4G8F2D, 0x20000000, 0x20000000, 2048, 64*2048, 64, 1, 1, 0x54, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"H27U1G8F2B", H27U1G8F2B, 0x8000000, 0x8000000, 2048, 64*2048, 64, 1, 0, 0xff, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"H27UBG8T2A", H27UBG8T2A, 0x100000000, 0x100000000, 8192, 256*8192, 448, 1, 1, 0x74, 0x42, 0x18, 0x01, 0x01, 0x01, 0x18},
 {"H27UBG8T2B", H27UBG8T2B, 0x100000000, 0x100000000, 8192, 256*8192, 448, 1, 1, 0x74, 0xc3, 0x18, 0x01, 0x01, 0x01, 0x18},
 {"H27UBG8T2C", H27UBG8T2C, 0x100000000, 0x100000000, 8192, 256*8192, 640, 1, 0, 0x60, 0x44, 0x28, 0x01, 0x01, 0x01, 0x28},
 {"H27UCG8T2B", H27UCG8T2B, 0x200000000, 0x200000000, 16384, 256*16384, 1280, 1, 0, 0x74, 0x44, 0x28, 0x01, 0x01, 0x01, 0x28},
 {"K9F1G08U0E", K9F1G08U0E, 0x8000000, 0x8000000, 2048, 64*2048, 64, 1, 0, 0x41, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"K9F1G08U0D", K9F1G08U0D, 0x8000000, 0x8000000, 2048, 64*2048, 64, 1, 0, 0x40, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"K9F2G08U0B", K9F2G08U0B, 0x10000000, 0x10000000, 2048, 64*2048, 64, 1, 0, 0x44, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"K9G4G08U0A", K9G4G08U0A, 0x20000000, 0x20000000, 2048, 128*2048, 64, 1, 1, 0x54, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"K9G4G08U0B", K9G4G08U0B, 0x20000000, 0x20000000, 2048, 128*2048, 64, 1, 1, 0x54, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"K9F4G08U0B", K9F4G08U0B, 0x20000000, 0x20000000, 2048, 64*2048, 64, 1, 0, 0x54, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"K9G8G08U0A", K9G8G08U0A, 0x40000000, 0x40000000, 2048, 128*2048, 64, 1, 1, 0x64, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"K9G8G08U0M", K9G8G08U0M, 0x40000000, 0x40000000, 2048, 128*2048, 64, 1, 1, 0x64, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"K9K8G08U0A", K9K8G08U0A, 0x40000000, 0x40000000, 2048, 64*2048, 64, 1, 0, 0x58, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"K9F8G08U0M", K9F8G08U0M, 0x40000000, 0x40000000, 4096, 64*4096, 128, 1, 0, 0x64, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"K9K8G08U0D", K9K8G08U0D, 0x40000000, 0x40000000, 2048, 64*2048, 64, 1, 0, 0x58, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"TC58NVG0S3C", TC58NVG0S3C, 0x8000000, 0x8000000, 2048, 64*2048, 64, 1, 0, 0xff, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"TC58NVG0S3E", TC58NVG0S3E, 0x8000000, 0x8000000, 2048, 64*2048, 64, 1, 0, 0x76, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"TC58NVG1S3C", TC58NVG1S3C, 0x10000000, 0x10000000, 2048, 64*2048, 64, 1, 0, 0xff, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"TC58NVG1S3E", TC58NVG1S3E, 0x10000000, 0x10000000, 2048, 64*2048, 64, 1, 0, 0x76, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"TC58NVG2S3E", TC58NVG2S3E, 0x20000000, 0x20000000, 2048, 64*2048, 64, 1, 0, 0x76, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"TC58NVG2S0HTA00", TC58NVG2S0HTA00, 0x20000000, 0x20000000, 4096, 128*2048, 64, 1, 0, 0x76, 0xff, 0xff, 0x01, 0x01, 0x01, 0x0c},
 {"TC58NVG5D2F", TC58NVG5D2F, 0x100000000, 0x100000000, 8192, 128*8192, 448, 1, 1, 0x76, 0x55, 0x18, 0x01, 0x01, 0x01, 0x18},
 {"TC58NVG4D2E", TC58NVG4D2E, 0x80000000, 0x80000000, 8192, 128*8192, 448, 1, 1, 0x76, 0x55, 0x18, 0x01, 0x01, 0x01, 0x18},
 {"TC58NVG2S0F", TC58NVG2S0F, 0x20000000, 0x20000000, 4096, 64*4096, 128, 1, 0, 0x76, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"TC58NVG2S0FTA00", TC58NVG2S0F, 0x20000000, 0x20000000, 4096, 64*4096, 128, 1, 0, 0x76, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"TC58TEG5DCJT", TC58TEG5DCJT, 0x100000000, 0x100000000, 16384, 256*16384, 1280, 1, 0, 0x72, 0x57, 0x28, 0x01, 0x01, 0x01, 0x28},
 {"TC58TEG6DCJT", TC58TEG6DCJT, 0x200000000, 0x200000000, 16384, 256*16384, 1280, 1, 0, 0x72, 0x57, 0x28, 0x01, 0x01, 0x01, 0x28},
 {"TC58TEG6DDK", TC58TEG6DDK, 0x200000000, 0x200000000, 16384, 256*16384, 1280, 1, 0, 0x76, 0x50, 0x28, 0x01, 0x01, 0x01, 0x28},

 {"TC58NVG5D2H", TC58NVG5D2H, 0x20000000, 0x20000000, 8192, 128*8192, 80, 1, 0, 0x76, 0x56, 0x18, 0x01, 0x01, 0x01, 0x18},
 {"TC58BVG0S3H", TC58BVG0S3H, 0x8000000, 0x8000000, 2048, 64*2048, 64, 1, 0, 0xF2, 0x16, 0xff, 0x01, 0x01, 0x01, 0x0c},
 {"TC58BVG1S3H", TC58BVG1S3H, 0x10000000, 0x10000000, 2048, 64*2048, 64, 1, 0, 0xF6, 0x16, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"TC58NVG0S3H", TC58NVG0S3H, 0x8000000, 0x8000000, 2048, 64*2048, 128, 1, 0, 0x72, 0x16, 0xff, 0x01, 0x01, 0x01, 0x0c},
 {"TC58NVG1S3H", TC58NVG1S3H, 0x10000000, 0x10000000, 2048, 64*2048, 128, 1, 0, 0x76, 0x16, 0xff, 0x01, 0x01, 0x01, 0x0c},
 {"MX30LF4G18AC", MX30LF4G18AC, 0x20000000, 0x20000000, 2048,  64*2048, 64, 1, 0, 0x56, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"MX30LF2G18AC", MX30LF2G18AC, 0x10000000, 0x10000000, 2048,  64*2048, 64, 1, 0, 0x06, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"MX30LF1G18AC", MX30LF1G18AC, 0x8000000, 0x8000000, 2048,  64*2048, 64, 1, 0, 0x02, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"MX30LF1G08AM", MX30LF1G08AM, 0x8000000, 0x8000000, 2048,  64*2048, 64, 1, 0, 0xff, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"W29N01GV", W29N01GV, 0x8000000, 0x8000000, 2048,  64*2048, 64, 1, 0, 0x0, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"W29N02GV", W29N02GV, 0x10000000, 0x10000000, 2048,  64*2048, 64, 1, 0, 0x4, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"W29N01HV", W29N01HV, 0x8000000, 0x8000000, 2048,  64*2048, 64, 1, 0, 0x00, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"MX30LF1208AA", MX30LF1208AA, 0x4000000, 0x4000000, 2048,  64*2048, 64, 1, 0, 0xff, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"EN27LN4G08", EN27LN4G08, 0x20000000, 0x20000000, 2048,  64*2048, 64, 1, 0, 0x54, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"F59L1G81MA", F59L1G81MA, 0x8000000, 0x8000000, 2048,  64*2048, 64, 1, 0, 0x40, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"F59L1G81A", F59L1G81A, 0x8000000, 0x8000000, 2048,  64*2048, 64, 1, 0, 0x40, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"F59L2G81A", F59L2G81A, 0x10000000, 0x10000000, 2048,  64*2048, 64, 1, 0, 0x44, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
// {"PSU2GA30AT", PSU2GA30AT, 0x10000000, 0x10000000, 2048, 64*2048, 64, 1, 0, 0xC8, 0xDA, 0xff, 0x00, 0x00, 0x00, 0x00},
 {"S34ML01G1",S34ML01G1 , 0x8000000, 0x8000000, 2048,  64*2048, 64, 1, 0, 0xff, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {"S34ML02G1",S34ML02G1, 0x10000000, 0x10000000, 2048,  64*2048, 64, 1, 0, 0x44, 0xff, 0xff, 0x01, 0x01, 0x01, 0x00},
 {NULL, }
};

/* NAND low-level MTD interface functions */
static int nand_read (struct mtd_info *mtd, loff_t from, size_t len, size_t *retlen, u_char *buf);
static int nand_read_ecc (struct mtd_info *mtd, loff_t from, size_t len, size_t *retlen, u_char *buf,
			struct mtd_oob_ops *ops);
static int nand_write (struct mtd_info *mtd, loff_t to, size_t len, size_t *retlen, const u_char *buf);
static int nand_write_ecc (struct mtd_info *mtd, loff_t to, size_t len, size_t *retlen, const u_char * buf,
			struct mtd_oob_ops *ops);
static int nand_erase (struct mtd_info *mtd, struct erase_info *instr);
static int nand_erase_nand (struct mtd_info *mtd, struct erase_info *instr, int allowbbt);
static void nand_sync (struct mtd_info *mtd);
static int nand_read_oob (struct mtd_info *mtd, loff_t from, struct mtd_oob_ops *ops);
static int nand_read_oob_ext (struct mtd_info *mtd, loff_t from, size_t len, size_t *retlen, u_char *oob_buf);

static int nand_write_oob (struct mtd_info *mtd, loff_t to, struct mtd_oob_ops *ops);

/* YAFFS2 */

static int nand_block_isbad (struct mtd_info *mtd, loff_t ofs);
static int nand_block_markbad (struct mtd_info *mtd, loff_t ofs);

/////////////////////////////////////////
static int rtk_update_bbt (struct mtd_info *mtd, struct mtd_oob_ops *ops, BB_t *bbt);



/* Global Variables */
int RBA=0;
static int oob_size, ppb, isLastPage;
static int ppb_shift;
static int page_size = 0;
//CMYu:, 20090415
//extern platform_info_t platform_info;
char *mp_erase_nand;
int mp_erase_flag = 0;
//CMYu:, 20090512
char *mp_time_para;
int mp_time_para_value = 0;
char *nf_clock;
int nf_clock_value = 0;
//CMYu:, 20090720
char *mcp;

//===========================================================================
#if 0
static void NF_CKSEL(char *PartNum, unsigned int value)
{
	REG_WRITE_U32( 0xb800000c,REG_READ_U32(0xb800000c)& (~0x00800000));
	REG_WRITE_U32( 0xb8000034,value);
	REG_WRITE_U32(0xb800000c,REG_READ_U32(0xb800000c)| (0x00800000));
	printk("[%s] %s is set to nf clock: 0x%x\n", __FUNCTION__, PartNum, value);
}
#endif
//------------------------------------------------------------------------------------------------

static unsigned int rtk_find_real_blk(struct mtd_info *mtd, unsigned int blk, int *chipnr_remap)
{
    struct nand_chip *this = (struct nand_chip *) mtd->priv;
    unsigned int i;
    unsigned int real_blk = blk;

    for ( i=0; i<RBA; i++){
        if ( this->bbt[i].bad_block != BB_INIT ){
            if ( real_blk == this->bbt[i].bad_block ){
                real_blk = this->bbt[i].remap_block;
                //printk("Remap ...... [%d] to [%d]\n", blk, real_blk);
                *chipnr_remap = this->bbt[i].RB_die;
                blk = real_blk;
            }
        }
    }
    if ( this->active_chip != *chipnr_remap ){
        this->active_chip = *chipnr_remap;
        this->select_chip(mtd, *chipnr_remap);
    }

    return real_blk;
}

static int  check_BBT(struct mtd_info *mtd, unsigned int blk)
{
	struct nand_chip *this = (struct nand_chip *) mtd->priv;
	printk("[%s]..\n", __FUNCTION__);
	int i;
	//int BBs=0;

	for ( i=0; i<RBA; i++)
	{
		if ( this->bbt[i].bad_block == blk )
		{
			printk("blk 0x%x exist\n",blk);
			return -1;
		}
	}

	return 0;
}

//------------------------------------------------------------------------------------------------

static void dump_BBT(struct mtd_info *mtd)
{

	struct nand_chip *this = (struct nand_chip *) mtd->priv;
	int i;
	int BBs=0;
	printk("[%s] Nand BBT Content\n", __FUNCTION__);
	for ( i=0; i<RBA; i++){
		if ( i==0 && this->bbt[i].BB_die == BB_DIE_INIT && this->bbt[i].bad_block == BB_INIT ){
			printk("Congratulation!! No BBs in this Nand.\n");
			break;
		}
		if ( this->bbt[i].bad_block != BB_INIT ){
			printk("[%d] (%d, %u, %d, %u)\n", i, this->bbt[i].BB_die, this->bbt[i].bad_block,
				this->bbt[i].RB_die, this->bbt[i].remap_block);
			BBs++;
		}
	}
	this->BBs = BBs;
}
#if 0//NAND_BBT_NEW_MECHANISM
int rtk_GetRemapBlk(struct mtd_info *mtd, int chipnr_remap, int block )
{
	struct nand_chip *this = mtd->priv;
	int i=0;
	int retBlk = -1;
	for ( i=0; i<RBA; i++){
	if ( this->bbt[i].bad_block != BB_INIT ){
		if ( this->active_chip == this->bbt[i].BB_die && block == this->bbt[i].bad_block ){
			retBlk = this->bbt[i].remap_block;
			if ( this->bbt[i].BB_die != this->bbt[i].RB_die ){
				this->active_chip = chipnr_remap = this->bbt[i].RB_die;
				this->select_chip(mtd, chipnr_remap);
			}
		}
	}else
		break;
	}
	return retBlk;
}
//-------------------------------------------------------------------------------------------------
int rtk_BadBlkRemapping(struct mtd_info *mtd, int chipnr, int chipnr_remap, int badblock, int* err_chipnr_remap  )
{
	struct nand_chip *this = mtd->priv;
	int i=0;
	int retBlk = -1;
	while (down_interruptible (&nf_BBT_sem)) {
		printk("%s : Retry\n",__FUNCTION__);
		//return -ERESTARTSYS;
	}
	for( i=0; i<RBA; i++){
		if(this->bbt[i].bad_block==badblock)
		{
			up(&nf_BBT_sem);
			return -1;
		}
	}
	for( i=0; i<RBA; i++){
		if ( this->bbt[i].bad_block == BB_INIT && this->bbt[i].remap_block != RB_INIT){
			if ( chipnr != chipnr_remap)
				this->bbt[i].BB_die = chipnr_remap;
			else
				this->bbt[i].BB_die = chipnr;
			this->bbt[i].bad_block = badblock;
			if(err_chipnr_remap)
				*err_chipnr_remap = this->bbt[i].RB_die;
			retBlk = this->bbt[i].remap_block;
			break;
		}
	}
	up(&nf_BBT_sem);
	if ( retBlk == -1 ){
		printk("[%s] RBA do not have free remap block\n", __FUNCTION__);
		return -1;
	}
	dump_BBT(mtd);
	return retBlk;
}
#endif


/*static void reverse_to_Yaffs2Tags(__u8 *r_oobbuf)
{
	int k;
	int cpBits=0;
	if(page_size==2048)
		cpBits=16;
	else
		cpBits=32;
	for ( k=0; k<cpBits; k++ ){
//	for ( k=0; k<oob_size; k++ ){
		r_oobbuf[k]  = r_oobbuf[1+k];
	}
}*/


 static int rtk_block_isbad(struct mtd_info *mtd, u16 chipnr, loff_t ofs)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	unsigned int page, block;
	unsigned char block_status_p1;
#if Nand_Block_Isbad_Slow_Version
	unsigned char block_status_p2;
#endif

	//unsigned char buf[oob_size] __attribute__((__aligned__(4)));

	this->active_chip=chipnr=0;
	page = ofs >> this->page_shift;
	block = page >> ppb_shift;
	
	if ( isLastPage ){
		page = block*ppb + (ppb-1);
		if ( this->read_oob (mtd, chipnr, page, oob_size, this->ops.oobbuf) ){
			printk ("%s: read_oob page=%d failed\n", __FUNCTION__, page);
			return 1;
		}
		block_status_p1 = this->ops.oobbuf[0];
#if Nand_Block_Isbad_Slow_Version
		page = block*ppb + (ppb-2);
		if ( this->read_oob (mtd, chipnr, page, oob_size, this->ops.oobbuf) ){
			printk ("%s: read_oob page=%d failed\n", __FUNCTION__, page);
			return 1;
		}
		block_status_p2 = this->ops.oobbuf[0];
		//debug_nand("[1]block_status_p1=0x%x, block_status_p2=0x%x\n", block_status_p1, block_status_p2);
#endif
	}else{
		if ( this->read_oob (mtd, chipnr, page, oob_size, this->ops.oobbuf) ){
			printk ("%s: read_oob page=%d failed\n", __FUNCTION__, page);
			return 1;
		}
		block_status_p1 = this->ops.oobbuf[0];
#if Nand_Block_Isbad_Slow_Version
		if ( this->read_oob (mtd, chipnr, page+1, oob_size, this->ops.oobbuf) ){
			printk ("%s: read_oob page+1=%d failed\n", __FUNCTION__, page+1);
			return 1;
		}
		block_status_p2 = this->ops.oobbuf[0];
		//debug_nand("[2]block_status_p1=0x%x, block_status_p2=0x%x\n", block_status_p1, block_status_p2);
#endif
	}
	
#if Nand_Block_Isbad_Slow_Version
	if ( (block_status_p1 != 0xff) && (block_status_p2 != 0xff) ){
#else
	if ( block_status_p1 != 0xff){
#endif
		printk ("WARNING: Die %d: block=%d is bad, block_status_p1=0x%x\n", chipnr, block, block_status_p1);
		return -1;
	}

	return 0;
}


static int nand_block_isbad (struct mtd_info *mtd, loff_t ofs)
{
	return 0;
}


static int nand_block_markbad (struct mtd_info *mtd, loff_t ofs)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	unsigned int page, block, page_offset;
	int i;
	int rc = 0;
	unsigned char buf[oob_size] __attribute__((__aligned__(4)));
	int chipnr, chipnr_remap;

	page = ofs >> this->page_shift;
	this->active_chip = chipnr = chipnr_remap = (int)(ofs >> this->chip_shift);
	page_offset = page & (ppb-1);
	block = page >> ppb_shift;

	this->active_chip=chipnr=chipnr_remap=0;
	this->select_chip(mtd, chipnr);

	for ( i=0; i<RBA; i++){
		if ( this->bbt[i].bad_block != BB_INIT ){
			if ( chipnr == this->bbt[i].BB_die && block == this->bbt[i].bad_block ){
				block = this->bbt[i].remap_block;
				if ( this->bbt[i].BB_die != this->bbt[i].RB_die ){
					this->active_chip = chipnr_remap = this->bbt[i].RB_die;
					this->select_chip(mtd, chipnr_remap);
				}
			}
		}else
			break;
	}
	page = block*ppb + page_offset;

	buf[0]=0x00;
	rc = this->write_oob (mtd, this->active_chip, page, oob_size, buf);
	if (rc) {
			//DEBUG (MTD_DEBUG_LEVEL0, "%s: write_oob failed\n", __FUNCTION__);
			return -1;
	}
	return 0;
}

//----------------------------------------------------------------------------------------------------
//add by alexchang 0928-2010

//----------------------------------------------------------------------------------------------------

static int nand_read_oob_ext (struct mtd_info *mtd, loff_t from, size_t len, size_t *retlen,
			u_char *oob_buf)
{
	struct nand_chip *this = mtd->priv;
	unsigned int page, realpage;
	int oob_len = 0, thislen;
	int rc=0;
	int old_page, page_offset, block;
	int chipnr, chipnr_remap;
	int i;

	if ((from + len) > mtd->size) {
		printk ("nand_read_oob: Attempt read beyond end of device\n");
		*retlen = 0;
		return -EINVAL;
	}


	if (NOTALIGNED (mtd, from)) {
		printk (KERN_NOTICE "%s: Attempt to read not page aligned data\n", __func__);
		return -EINVAL;
	}

	realpage = (int)(from >> this->page_shift);
	this->active_chip = chipnr = chipnr_remap = (int)(from >> this->chip_shift);
	old_page = page = realpage & this->pagemask;
	page_offset = page & (ppb-1);
	block = page >> ppb_shift;
	this->active_chip=chipnr=chipnr_remap=0;
	this->select_chip(mtd, chipnr);


	if ( retlen )
		*retlen = 0;
	thislen = oob_size;

	while (oob_len < len) {
		if (thislen > (len - oob_len))
			thislen = (len - oob_len);

		for ( i=0; i<RBA; i++){
			if ( this->bbt[i].bad_block != BB_INIT ){
				if ( this->active_chip == this->bbt[i].BB_die && block == this->bbt[i].bad_block ){
					block = this->bbt[i].remap_block;
					if ( this->bbt[i].BB_die != this->bbt[i].RB_die ){
						this->active_chip = chipnr_remap = this->bbt[i].RB_die;
						this->select_chip(mtd, chipnr_remap);
					}
				}
			}else
				break;
		}

		page = block*ppb + page_offset;

		rc = this->read_oob (mtd, this->active_chip, page, thislen, &oob_buf[oob_len]);
		if (rc < 0) {
			if (rc == -1){
				printk ("%s: read_oob: Un-correctable HW ECC\n", __FUNCTION__);
				if(check_BBT(mtd,page >> ppb_shift)==0)
				{

				for( i=0; i<RBA; i++){
					if ( this->bbt[i].bad_block == BB_INIT && this->bbt[i].remap_block != RB_INIT){
						if ( chipnr != chipnr_remap)	//remap block is bad
							this->bbt[i].BB_die = chipnr_remap;
						else
							this->bbt[i].BB_die = chipnr;
						this->bbt[i].bad_block = page >> ppb_shift;
						break;
					}
				}

				dump_BBT(mtd);

				if ( rtk_update_bbt (mtd, &this->ops, this->bbt) ){
					printk("[%s] rtk_update_bbt() fails\n", __FUNCTION__);
					return -1;
					}
				}

				this->ops.oobbuf[0] = 0x00;
				if ( isLastPage ){
					this->erase_block (mtd, this->active_chip, block*ppb);
					this->write_oob(mtd, this->active_chip, block*ppb+ppb-1, oob_size, this->ops.oobbuf);
					this->write_oob(mtd, this->active_chip, block*ppb+ppb-2, oob_size, this->ops.oobbuf);
				}else{
					this->erase_block (mtd, this->active_chip, block*ppb);
					this->write_oob(mtd, this->active_chip, block*ppb, oob_size, this->ops.oobbuf);
					this->write_oob(mtd, this->active_chip, block*ppb+1, oob_size, this->ops.oobbuf);
				}
				printk("rtk_read_oob: Un-correctable HW ECC Error at page=%d\n", page);
			}else{
				printk ("%s: rtk_read_oob: semphore failed\n", __FUNCTION__);
				return -1;
			}
		}

		oob_len += thislen;

		old_page++;
		page_offset = old_page & (ppb-1);
		if ( oob_len<len && !(old_page & this->pagemask)) {
			old_page &= this->pagemask;
			chipnr++;
			this->active_chip = chipnr;
			this->select_chip(mtd, chipnr);
		}
		block = old_page >> ppb_shift;
	}

	if ( retlen ){
		if ( oob_len == len )
			*retlen = oob_len;
		else{
			printk("[%s] error: oob_len %d != len %zu\n", __FUNCTION__, oob_len, len);
			return -1;
		}
	}

	return 0;
}


static int nand_read (struct mtd_info *mtd, loff_t from, size_t len, size_t * retlen, u_char * buf)
{
	int rc=0;

	//printk("[%s]scramble 0x%x\n",__FUNCTION__,mtd->isScramble);

	//printk("[%s] mtd->writesize =%u\n", __FUNCTION__, mtd->writesize);
	rc = nand_read_ecc (mtd, from, len, retlen, buf, NULL);
	if(g_isSysSecure||g_isRandomize)
        {
		//printk("[%s] done \n",__FUNCTION__);
		//mtd->isScramble= 0;

	}

	return rc;
}

static int nand_read_oob (struct mtd_info *mtd, loff_t from, struct mtd_oob_ops *ops)
{
	int rc = 0;
	//printk("[%s] mtd->writesize =%u\n", __FUNCTION__, mtd->writesize);
	//printk("[%s]scramble 0x%x\n",__FUNCTION__,mtd->isScramble);
	if(!ops->len && ops->ooblen)
		 rc = nand_read_oob_ext(mtd, from, ops->ooblen, &ops->oobretlen,ops->oobbuf);
	else
	{

		 rc = nand_read_ecc(mtd, from, ops->len, &ops->retlen,ops->datbuf, ops);
	}

	if(g_isSysSecure||g_isRandomize)
        {
//		printk("[%s] done \n",__FUNCTION__);
		//mtd->isScramble= 0;


	}

	return rc;
}
static int nand_read_ecc (struct mtd_info *mtd, loff_t from, size_t len,
			size_t *retlen, u_char *buf, struct mtd_oob_ops *ops)
{
	struct nand_chip *this = mtd->priv;
	unsigned long long  page, realpage,page_ppb;
	int data_len;
	int rc = 0;
	unsigned int old_page, page_offset, block, real_block;
	int chipnr, chipnr_remap;
	int i;
	unsigned int max_bitflips = 0;

	//int from_tmp = from;
	debug("[%s] from:0x%08llx, len:0x%08zx, buf:%p \n", __func__, from, len, buf);

	if ((from + len) > mtd->size) {
		printk ("nand_read_ecc: Attempt read beyond end of device\n");
		*retlen = 0;
		return -EINVAL;
	}
	//printk("[%s] NOTALIGNED (mtd, from) 0x%x, NOTALIGNED(mtd, len)0x%x\n",__FUNCTION__,NOTALIGNED (mtd, from),NOTALIGNED(mtd, len));

	if (NOTALIGNED (mtd, from) || NOTALIGNED(mtd, len)) {
		printk (KERN_NOTICE "%s: Attempt to read not page aligned data\n",__func__);
		return -EINVAL;
	}

	realpage = (int)(from >> this->page_shift);
	this->active_chip = chipnr = chipnr_remap = (int)(from >> this->chip_shift);
	old_page = page = realpage & this->pagemask;
	page_offset = page & (ppb-1);
	//block = page/ppb;
	page_ppb = page;
	do_div(page_ppb,ppb);
	block = (unsigned int)page_ppb;
	debug("\t\tReady to READ blk:%u, page:%u, len:%zu, page_size:%d, oob_size:%d\n",block,page_offset,len,page_size,oob_size);

	this->select_chip(mtd, chipnr);

	if ( retlen )
		*retlen = 0;

	data_len = 0;
	if(ops)
		ops->oobretlen = 0;

	while (data_len < len) {
		real_block = rtk_find_real_blk(mtd, block, &chipnr_remap);
		page = real_block*ppb + page_offset;
		rc = this->read_ecc_page (mtd, this->active_chip, page, &buf[data_len], ops, CP_NF_NONE,0,0);
		if (rc < 0) {
			#if	0
			printk("[%s]Try again..\n",__FUNCTION__);
			NF_rtkcr_card_power(1);//power off card reader.
			rc = this->read_ecc_page (mtd, this->active_chip, page, &buf[data_len], &oob_buf[oob_len]);
			if(rc<0)
			{
			#if NAND_READ_SKIP_UPDATE_BBT
				return -1;
			#endif
			}
			#endif
			if (rc == -1){
				printk ("%s: read_ecc_page: Un-correctable HW ECC\n", __FUNCTION__);
				//continue;

				//update BBT
				if(check_BBT(mtd,page_ppb)==0)
				{

				for( i=0; i<RBA; i++){
					if ( this->bbt[i].bad_block == BB_INIT && this->bbt[i].remap_block != RB_INIT){
						if ( chipnr != chipnr_remap)	//remap block is bad
							this->bbt[i].BB_die = chipnr_remap;
						else
							this->bbt[i].BB_die = chipnr;
						this->bbt[i].bad_block = page_ppb;
						break;
					}
				}

				dump_BBT(mtd);

				if ( rtk_update_bbt (mtd, &this->ops, this->bbt) ){
					printk("[%s] rtk_update_bbt() fails\n", __FUNCTION__);
					return -1;
					}
				}

				this->ops.oobbuf[0] = 0x00;
				block = page_ppb;
				if ( isLastPage){
					this->erase_block (mtd, this->active_chip, block*ppb);
					this->write_oob(mtd, this->active_chip, block*ppb+ppb-1, oob_size, this->ops.oobbuf);
					this->write_oob(mtd, this->active_chip, block*ppb+ppb-2, oob_size, this->ops.oobbuf);
				}else{
					this->erase_block (mtd, this->active_chip, block*ppb);
					this->write_oob(mtd, this->active_chip, block*ppb, oob_size, this->ops.oobbuf);
					this->write_oob(mtd, this->active_chip, block*ppb+1, oob_size, this->ops.oobbuf);
				}
				printk("rtk_read_ecc_page: Un-correctable HW ECC Error at page=0x%llx\n", page);
			}else{
				printk ("%s: read_ecc_page:  semphore failed\n", __FUNCTION__);
				return -1;
			}
		}
		else
			max_bitflips = max_t(unsigned int, max_bitflips, rc);
		data_len += page_size;

		if(ops)//add by alexchang 0524-2010
			ops->oobretlen += oob_size;

		old_page++;
		page_offset = old_page & (ppb-1);
		if ( data_len<len && !(old_page & this->pagemask)) {
			old_page &= this->pagemask;
			chipnr++;
			this->active_chip = chipnr;
			this->select_chip(mtd, chipnr);
		}
		block = old_page >> ppb_shift;
	}

	if ( retlen ){
		if ( data_len == len )
			*retlen = data_len;
		else{
				printk("[%s] error: data_len %d != len %zu\n", __FUNCTION__, data_len, len);
				return -1;
		}
	}
	if(rc < 0)
		return rc;

	return max_bitflips;
}


static int nand_write (struct mtd_info *mtd, loff_t to, size_t len, size_t *retlen, const u_char *buf)
{
	int rc = 0;
	rc = (nand_write_ecc (mtd, to, len, retlen, buf, NULL));

	return rc;
}

static int nand_write_oob (struct mtd_info *mtd, loff_t to, struct mtd_oob_ops *ops)//for 2.6.34 YAFFS-->mtd
{
	int rc = 0;
	rc =  nand_write_ecc (mtd, to, ops->len, &ops->retlen,ops->datbuf, ops);
	return rc;
}

static int nand_write_ecc (struct mtd_info *mtd, loff_t to, size_t len, size_t *retlen,
			const u_char * buf, struct mtd_oob_ops *ops)
{
	struct nand_chip *this = mtd->priv;
	unsigned long long page, realpage,page_ppb;
	int data_len, oob_len;
	int rc;
	unsigned int i, old_page, page_offset, block, real_block;
	int chipnr, chipnr_remap, err_chipnr = 0, err_chipnr_remap = 1;
	//int backup_offset;
	int block_remap=0x12345678;
	if ((to + len) > mtd->size) {
		printk ("nand_write_ecc: Attempt write beyond end of device\n");
		*retlen = 0;
		return -EINVAL;
	}
	if (NOTALIGNED (mtd, to) || NOTALIGNED(mtd, len)) {
		printk (KERN_NOTICE "%s: Attempt to write not page aligned data\n", __func__);
		return -EINVAL;
	}
//printk("[%s] to 0x%llx\n",__FUNCTION__,to);
	realpage = (unsigned long long)(to >> this->page_shift);
//	printk("realpage 0x%llx, to 0x%llx\n",realpage,to);
	this->active_chip = chipnr = chipnr_remap = (int)(to >> this->chip_shift);
	old_page = page = realpage & this->pagemask;
//	printk("pagemask 0x%llx\n",this->pagemask);
	page_offset = page & (ppb-1);
	//block = page/ppb;
	page_ppb = page;
	do_div(page_ppb,ppb);
	block = (unsigned int)page_ppb;
//printk("READY write to block 0x%x",block);
    //printk("Ready to write blk:%u, page:%u, len:%u, page_size:%d, oob_size:%d\n",page/ppb,page%ppb,len,page_size,oob_size);
	//CMYu, 20091030

	this->select_chip(mtd, chipnr);

	if ( retlen )
		*retlen = 0;

	data_len = oob_len = 0;

	while ( data_len < len) {
		real_block = rtk_find_real_blk(mtd, block, &chipnr_remap);
		page = real_block*ppb + page_offset;
		rc = this->write_ecc_page (mtd, this->active_chip, page, &buf[data_len], ops, 0);
		if (rc < 0) {
			if ( rc == -1){
				//printk ("%s: write_ecc_page:  write blk:%u, page:%u failed\n", __FUNCTION__,page/ppb,page%ppb);


			if(check_BBT(mtd,page_ppb)==0)
			{

				/* update BBT */
				for( i=0; i<RBA; i++){
					if ( this->bbt[i].bad_block == BB_INIT && this->bbt[i].remap_block != RB_INIT){
						if ( chipnr != chipnr_remap)	//remap block is bad
							err_chipnr = chipnr_remap;
						else
							err_chipnr = chipnr;
						this->bbt[i].BB_die = err_chipnr;
						this->bbt[i].bad_block = page_ppb;
						err_chipnr_remap = this->bbt[i].RB_die;
						block_remap = this->bbt[i].remap_block;
						break;
					}
				}

				if ( block_remap == 0x12345678 ){
					printk("[%s] RBA do not have free remap block\n", __FUNCTION__);
					return -1;
				}
			}

				dump_BBT(mtd);

				if ( rtk_update_bbt (mtd, &this->ops, this->bbt) ){
					printk("[%s] rtk_update_bbt() fails\n", __FUNCTION__);
					return -1;
				}

				//backup_offset = page&(ppb-1);
				this->select_chip(mtd, err_chipnr_remap);
				this->erase_block (mtd, err_chipnr_remap, block_remap*ppb);
#if 0
				printk("[%s] Start to Backup old_page from %d to %d\n", __FUNCTION__, block*ppb, block*ppb+backup_offset-1);

				for ( i=0; i<backup_offset; i++){
					if ( err_chipnr != err_chipnr_remap ){
						this->active_chip = err_chipnr;
						this->select_chip(mtd, err_chipnr);
					}
					this->read_ecc_page(mtd, this->active_chip, (page/ppb)*ppb+i, this->ops.datbuf, this->ops.oobbuf);
					if ( this->ops.oobbuf )
						reverse_to_Yaffs2Tags(this->ops.oobbuf);
					if ( err_chipnr != err_chipnr_remap ){
						this->active_chip = err_chipnr_remap;
						this->select_chip(mtd, err_chipnr_remap);
					}
					this->write_ecc_page(mtd, this->active_chip, block_remap*ppb+i, this->ops.datbuf, this->ops.oobbuf, 0);
				}
				this->write_ecc_page (mtd, this->active_chip, block_remap*ppb+backup_offset, &buf[data_len], &oob_buf[oob_len], 0);
				printk("[%s] write failure page = %d to %d\n", __FUNCTION__, page, block_remap*ppb+backup_offset);
#endif
				if ( err_chipnr != err_chipnr_remap ){
					this->active_chip = err_chipnr;
					this->select_chip(mtd, err_chipnr);
				}

				this->ops.oobbuf[0] = 0x00;
				block = page_ppb;
				if ( isLastPage ){
					this->erase_block (mtd, err_chipnr, block*ppb);
					this->write_oob(mtd, this->active_chip, block*ppb+ppb-1, oob_size, this->ops.oobbuf);
					this->write_oob(mtd, this->active_chip, block*ppb+ppb-2, oob_size, this->ops.oobbuf);
				}else{
					this->erase_block (mtd, err_chipnr, block*ppb);
					this->write_oob(mtd, this->active_chip, block*ppb, oob_size, this->ops.oobbuf);
					this->write_oob(mtd, this->active_chip, block*ppb+1, oob_size, this->ops.oobbuf);
				}
			}else{
				printk ("%s: write_ecc_page:  rc=%d\n", __FUNCTION__, rc);
				return -1;
			}
		}
		//else
			//printk("Confirm to write blk:%u, page:%u Succeed!!\n",page/ppb,page%ppb);
		data_len += page_size;
		oob_len += oob_size;

		old_page++;
		page_offset = old_page & (ppb-1);
		if ( data_len<len && !(old_page & this->pagemask)) {
			old_page &= this->pagemask;
			chipnr++;
			this->active_chip = chipnr;
			this->select_chip(mtd, chipnr);
		}
		block = old_page >> ppb_shift;
	}

	if ( retlen ){

		if ( data_len == len )
			*retlen = data_len;
		else{
			printk("[%s] error: data_len %d != len %zu\n", __FUNCTION__, data_len, len);
			return -1;
		}
	}
	return 0;
}


static int nand_erase (struct mtd_info *mtd, struct erase_info *instr)
{

	return nand_erase_nand (mtd, instr, 0);
}


static int nand_erase_nand (struct mtd_info *mtd, struct erase_info *instr, int allowbbt)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	u_int64_t addr = instr->addr;
	u_int64_t len = instr->len;
	int old_page, page, chipnr;
	int block, real_block;
	u_int64_t elen = 0;
	int rc = 0;
	int realpage, chipnr_remap, block_remap=0x12345678;

	check_end (mtd, addr, len);
	check_block_align (mtd, addr);

	 instr->fail_addr = 0xffffffff;

	realpage = addr >> this->page_shift;
	this->active_chip = chipnr = chipnr_remap = addr >> this->chip_shift;
	old_page= page = realpage & this->pagemask;
	block = page >> ppb_shift;

	this->active_chip=chipnr=chipnr_remap=0;
	this->select_chip(mtd, chipnr);

	instr->state = MTD_ERASING;
	while (elen < len) {
		int i;
		real_block = rtk_find_real_blk(mtd, block, &chipnr_remap);
		page = real_block*ppb;
		rc = this->erase_block (mtd, this->active_chip, page);
		if (rc) {
			printk ("%s: block erase failed at page address=%llu\n", __FUNCTION__, addr);
			instr->fail_addr = (page << this->page_shift);
			if(check_BBT(mtd,page >> ppb_shift)==0)
			{

				for( i=0; i<RBA; i++){
					if ( this->bbt[i].bad_block == BB_INIT && this->bbt[i].remap_block != RB_INIT)
						{
							if ( chipnr != chipnr_remap)
								this->bbt[i].BB_die = chipnr_remap;
							else
								this->bbt[i].BB_die = chipnr;
						this->bbt[i].bad_block = page >> ppb_shift;
						block_remap = this->bbt[i].remap_block;
						break;
					}
				}

				if ( block_remap == 0x12345678 ){
					printk("[%s] RBA do not have free remap block[%d]\n", __FUNCTION__,RBA);
					return -1;
				}
			}

			dump_BBT(mtd);

			if ( rtk_update_bbt (mtd, &this->ops, this->bbt) ){
				printk("[%s] rtk_update_bbt() fails\n", __FUNCTION__);
				return -1;
			}

			this->ops.oobbuf[0] = 0x00;
			if ( isLastPage ){
				this->write_oob(mtd, chipnr, page+ppb-1, oob_size, this->ops.oobbuf);
				this->write_oob(mtd, chipnr, page+ppb-2, oob_size, this->ops.oobbuf);
			}else{
				this->write_oob(mtd, chipnr, page, oob_size, this->ops.oobbuf);
				this->write_oob(mtd, chipnr, page+1, oob_size, this->ops.oobbuf);
			}

			rc = this->erase_block(mtd, chipnr_remap, block_remap*ppb);
		}
		//else
			//printk("confirm to Erase blk %u  succeed!!\n",page/ppb);

		if ( chipnr != chipnr_remap )
			this->select_chip(mtd, chipnr);

		elen += mtd->erasesize;

		old_page += ppb;

		if ( elen<len && !(old_page & this->pagemask)) {
			old_page &= this->pagemask;
			chipnr++;
			this->active_chip = chipnr;
			this->select_chip(mtd, chipnr);
		}

		block = old_page >> ppb_shift;
	}
	instr->state = MTD_ERASE_DONE;

	return rc;
}


static void nand_sync (struct mtd_info *mtd)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	this->state = RTK_FL_READY;
}


static void nand_select_chip(struct mtd_info *mtd, int chip)
{
	switch(chip) {
		case -1:
			REG_WRITE_U32(REG_PD,0xff);
			break;
		case 0:
		case 1:
		case 2:
		case 3:
			REG_WRITE_U32(REG_PD, ~(1 << chip));
			break;
		default:
			REG_WRITE_U32(REG_PD, ~(1 << 0));
	}
}


static int scan_last_die_BB(struct mtd_info *mtd)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	__u32 start_page = 0;
	uint64_t addr;
	int block_num = this->block_num;
	int block_size = 1 << this->phys_erase_shift;
	int table_index=0;
	int remap_block[RBA];
	int remap_count = 0;
	int i, j;
	int numchips = this->numchips;
	uint64_t chip_size = this->chipsize;
	int rc = 0;
	__u8 *block_status = NULL;

	g_mtd_BootcodeSize = rtkNF_getBootcodeSize();
	if(g_mtd_BootcodeSize == -1)
	{
#ifdef NAS_ENABLE
		g_mtd_BootcodeSize = rtk_plat_get_fw_desc_table_start();
		if (g_mtd_BootcodeSize <= 0)
#endif
			g_mtd_BootcodeSize = 62*1024*1024;
	}
	if ( numchips>1 ){
		start_page = 0x00000000;
		printk("multi-chip is not supported yet!!\n");
		return -1;
	}else{
		//start_page = 0x01000000;
		start_page = g_mtd_BootcodeSize;
	}

	printk("[%s] numchips(%x), start_page(%x), ppb(%x)\n", __FUNCTION__, numchips, start_page, ppb);
	// skip the first 0x3e blocks.
	//start_page = block_size * 0x3e;//for fsbl, tee...

	this->active_chip = numchips-1;
	this->select_chip(mtd, numchips-1);

	block_status = kmalloc( block_num, GFP_KERNEL );
	if ( !block_status ){
		printk("%s: Error, no enough memory for block_status\n",__FUNCTION__);
		rc = -ENOMEM;
		goto EXIT;
	}
	memset ( (__u32 *)block_status, 0, block_num );

	printk("chip_size(%llu), block_size(%d), this->phys_erase_shift(%d)\n", chip_size, block_size, this->phys_erase_shift);

	for( addr=start_page; addr<chip_size; addr+=block_size ){
		if ( rtk_block_isbad(mtd, numchips-1, addr) ){
			int bb = addr >> this->phys_erase_shift;
			block_status[bb] = 0xff;
		}
	}

	for ( i=0; i<RBA; i++){
		if ( block_status[(block_num-1)-i] == 0x00){
			remap_block[remap_count] = (block_num-1)-i;
			remap_count++;
		}
	}

	if (remap_count<RBA+1){
		for (j=remap_count+1; j<RBA+1; j++)
			remap_block[j-1] = RB_INIT;
	}

	for ( i=0; i<(block_num-RBA); i++){
		if (table_index >= RBA) {
			printk("BB number exceeds RBA. \n");
			break;
		}
		if (block_status[i] == 0xff){
			this->bbt[table_index].bad_block = i;
			this->bbt[table_index].BB_die = numchips-1;
			this->bbt[table_index].remap_block = remap_block[table_index];
			this->bbt[table_index].RB_die = numchips-1;
			table_index++;
		}
	}

	for( i=table_index; table_index<RBA; table_index++){
		this->bbt[table_index].bad_block = BB_INIT;
		this->bbt[table_index].BB_die = BB_DIE_INIT;
		this->bbt[table_index].remap_block = remap_block[table_index];
		this->bbt[table_index].RB_die = numchips-1;
	}

	RTK_FLUSH_CACHE((unsigned long) this->bbt, sizeof(BB_t)*RBA);

EXIT:

	if (block_status) {
		kfree(block_status);
	}

	return rc;
}

#if 0
static int scan_other_die_BB(struct mtd_info *mtd)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	__u32 start_page;
	uint64_t addr;
	int block_size = 1 << this->phys_erase_shift;
	int j, k;
	int numchips = this->numchips;
	uint64_t chip_size = this->chipsize;

	g_mtd_BootcodeSize = rtkNF_getBootcodeSize();
	if(g_mtd_BootcodeSize == -1)
	{
		if(is_darwin_cpu()||is_saturn_cpu()||is_nike_cpu())
			g_mtd_BootcodeSize = 12*1024*1024;
		else
			g_mtd_BootcodeSize = 16*1024*1024;
	}
	for( k=0; k<numchips-1; k++ ){
		this->active_chip = k;
		this->select_chip(mtd, k);
		if( k==0 ){
			// start_page = g_mtd_BootcodeSize;
			// skip the first 0x12 blocks.
			//start_page = ppb * 0x12;
			printk("[%s] skip the first 0x3e blocks !!\n", __FUNCTION__);
			start_page = ppb * 0x3e;
		}else{
			start_page = 0x00000000;
		}

		for( addr=start_page; addr<chip_size; addr+=block_size ){
			if ( rtk_block_isbad(mtd, k, addr) ){
				for( j=0; j<RBA; j++){
					if ( this->bbt[j].bad_block == BB_INIT && this->bbt[j].remap_block != RB_INIT){
						this->bbt[j].bad_block = addr >> this->phys_erase_shift;
						this->bbt[j].BB_die = k;
						this->bbt[j].RB_die = numchips-1;
						break;
					}
				}
			}
		}
	}

	RTK_FLUSH_CACHE((unsigned long) this->bbt, sizeof(BB_t)*RBA);

	return 0;
}
#endif

static int rtk_create_bbt(struct mtd_info *mtd, int page)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;

	int rc = 0;
	u8 *temp_BBT = 0;
	u8 mem_page_num, page_counter=0;
	
	if(page==ppb)
		printk("[%s] nand driver creates B1 !!\n", __FUNCTION__);
	else if(page==(ppb<<1))
		printk("[%s] nand driver creates B2 !!\n", __FUNCTION__);
	else {
		printk("[%s] abort creating BB on page %x !!\n", __FUNCTION__, page);
		return -1;
	}

	if ( scan_last_die_BB(mtd) ){
		printk("[%s] scan_last_die_BB() error !!\n", __FUNCTION__);
		return -1;
	}

	if ( this->numchips >1 ){
		//if ( scan_other_die_BB(mtd) ){
			printk("[%s] scan_last_die() error !!\n", __FUNCTION__);
			return -1;
		//}
	}

	mem_page_num = (sizeof(BB_t)*RBA + page_size-1 )/page_size;
	temp_BBT = kmalloc( mem_page_num*page_size, GFP_KERNEL );
	if ( !temp_BBT ){
		printk("%s: Error, no enough memory for temp_BBT\n",__FUNCTION__);
		return -ENOMEM;
	}
	memset( temp_BBT, 0xff, mem_page_num*page_size);
	this->select_chip(mtd, 0);
	if ( this->erase_block(mtd, 0, page) ){
		printk("[%s]erase block %d failure !!\n", __FUNCTION__, page >> ppb_shift);
		rc =  -1;
		goto EXIT;
	}
	this->ops.oobbuf[0] = BBT_TAG;

	memcpy( temp_BBT, this->bbt, sizeof(BB_t)*RBA );
	while( mem_page_num>0 ){
		if ( this->write_ecc_page(mtd, 0, page+page_counter, temp_BBT+page_counter*page_size,
			&this->ops, 1) ){
				printk("[%s] write BBT B%d page %d failure!!\n", __FUNCTION__,
					page ==0?0:1, page+page_counter);
				rc =  -1;
				goto EXIT;
		}
		page_counter++;
		mem_page_num--;
	}

EXIT:
	if (temp_BBT)
		kfree(temp_BBT);
	
	return rc;
}


static int rtk_update_bbt (struct mtd_info *mtd, struct mtd_oob_ops *ops, BB_t *bbt)
{
	int rc = 0;
	struct nand_chip *this = mtd->priv;
	unsigned char active_chip = this->active_chip;
	u8 *temp_BBT = 0;
	__u8 *data_buf = ops->datbuf;
	__u8 *oob_buf = ops->oobbuf;

	oob_buf[0] = BBT_TAG;

	this->select_chip(mtd, 0);

	if ( sizeof(BB_t)*RBA <= page_size){
		memcpy( data_buf, bbt, sizeof(BB_t)*RBA );
	}else{
		temp_BBT = kmalloc( 2*page_size, GFP_KERNEL );
		if ( !(temp_BBT) ){
			printk("%s: Error, no enough memory for temp_BBT\n",__FUNCTION__);
			return -ENOMEM;
		}
		memset(temp_BBT, 0xff, 2*page_size);
		memcpy(temp_BBT, bbt, sizeof(BB_t)*RBA );
		memcpy(data_buf, temp_BBT, page_size);
	}

	if ( this->erase_block(mtd, 0, ppb) ){
		printk("[%s]error: erase block 1 failure\n", __FUNCTION__);
	}

	if ( this->write_ecc_page(mtd, 0, ppb, data_buf, ops, 1) ){
		printk("[%s]update BBT B1 page 0 failure\n", __FUNCTION__);
	}else{
		if ( sizeof(BB_t)*RBA > page_size){
			memset(data_buf, 0xff, page_size);
			memcpy( data_buf, temp_BBT+page_size, sizeof(BB_t)*RBA - page_size );
			if ( this->write_ecc_page(mtd, 0, ppb+1, data_buf, ops, 1) ){
				printk("[%s]update BBT B1 page 1 failure\n", __FUNCTION__);
			}
			memcpy(data_buf, temp_BBT, page_size);//add by alexchang 0906-2010
		}
	}
	//-----------------------------------------------------------------------
	if ( this->erase_block(mtd, 0, ppb<<1) ){
		printk("[%s]error: erase block 1 failure\n", __FUNCTION__);
		return -1;
	}

	if ( this->write_ecc_page(mtd, 0, ppb<<1, data_buf, ops, 1) ){
		printk("[%s]update BBT B2 failure\n", __FUNCTION__);
		return -1;
	}else{
		if ( sizeof(BB_t)*RBA > page_size){
			memset(data_buf, 0xff, page_size);
			memcpy( data_buf, temp_BBT+page_size, sizeof(BB_t)*RBA - page_size );
			if ( this->write_ecc_page(mtd, 0, 2*ppb+1, data_buf, ops, 1) ){
				printk("[%s]error: erase block 2 failure\n", __FUNCTION__);
				return -1;
			}
		}
	}

	this->select_chip(mtd, active_chip);

	if (temp_BBT)
		kfree(temp_BBT);

	return rc;
}


static int rtk_nand_scan_bbt(struct mtd_info *mtd)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	int rc = 0;
	__u8 isbbt_b1, isbbt_b2;
	u8 *temp_BBT=0;
	u8 mem_page_num, page_counter=0;

	RTK_FLUSH_CACHE((unsigned long) this->bbt, sizeof(BB_t)*RBA);
	mem_page_num = (sizeof(BB_t)*RBA + page_size-1 )/page_size;
	temp_BBT = kmalloc( mem_page_num*page_size, GFP_KERNEL );
	if ( !temp_BBT ){
		printk("%s: Error, no enough memory for temp_BBT\n",__FUNCTION__);
		return -ENOMEM;
	}
	memset( temp_BBT, 0xff, mem_page_num*page_size);
	
	rc = this->read_ecc_page(mtd, 0, ppb, this->ops.datbuf, &this->ops, CP_NF_NONE,0,0);
	//printk("read_ecc_page rc = %x , oob = 0x%x\n", rc, this->ops.oobbuf[0]);

	isbbt_b1 = this->ops.oobbuf[0];
	if ( !rc ){
		if ( isbbt_b1 == BBT_TAG ){
			printk("[%s] have created bbt B1, just loads it !!\n", __FUNCTION__);
			memcpy( temp_BBT, this->ops.datbuf, page_size );
			page_counter++;
			mem_page_num--;

			while( mem_page_num>0 ){
				if ( this->read_ecc_page(mtd, 0, ppb+page_counter, this->ops.datbuf, &this->ops, CP_NF_NONE,0,0) ){
					printk("[%s] load bbt B1 error!!\n", __FUNCTION__);
					kfree(temp_BBT);
					return -1;
				}
				memcpy( temp_BBT+page_counter*page_size, this->ops.datbuf, page_size );
				page_counter++;
				mem_page_num--;
			}
			memcpy( this->bbt, temp_BBT, sizeof(BB_t)*RBA );
		}
		else{
			printk("[%s] read BBT B1 tags fails, try to load BBT B2\n", __FUNCTION__);
			rc = this->read_ecc_page(mtd, 0, ppb<<1, this->ops.datbuf, &this->ops, CP_NF_NONE,0,0);
			printk("read_ecc_page rc = %x , oob = 0x%x\n", rc, this->ops.oobbuf[0]);
			isbbt_b2 = this->ops.oobbuf[0];
			if ( !rc ){
				if ( isbbt_b2 == BBT_TAG ){
					printk("[%s] have created bbt B2, just loads it !!\n", __FUNCTION__);
					memcpy( temp_BBT, this->ops.datbuf, page_size );
					page_counter++;
					mem_page_num--;

					while( mem_page_num>0 ){
						if ( this->read_ecc_page(mtd, 0, 2*ppb+page_counter, this->ops.datbuf, &this->ops, CP_NF_NONE,0,0) ){
							printk("[%s] load bbt B2 error!!\n", __FUNCTION__);
							kfree(temp_BBT);
							return -1;
						}
						memcpy( temp_BBT+page_counter*page_size, this->ops.datbuf, page_size );
						page_counter++;
						mem_page_num--;
					}
					memcpy( this->bbt, temp_BBT, sizeof(BB_t)*RBA );
				}else{
					printk("[%s] read BBT B2 tags fails, nand driver will creat BBT B1 and B2\n", __FUNCTION__);
					rtk_create_bbt(mtd, ppb);
					rtk_create_bbt(mtd, ppb<<1);
				}
			}else{
				printk("[%s] read BBT B2 with HW ECC fails, nand driver will creat BBT B1\n", __FUNCTION__);
				rtk_create_bbt(mtd, ppb);
			}
		}
	}else{
		printk("[%s] read BBT B1 with HW ECC error, try to load BBT B2\n", __FUNCTION__);
		rc = this->read_ecc_page(mtd, 0, ppb<<1, this->ops.datbuf, &this->ops, CP_NF_NONE,0,0);
		isbbt_b2 = this->ops.oobbuf[0];
		if ( !rc ){
			if ( isbbt_b2 == BBT_TAG ){
				printk("[%s] have created bbt B1, just loads it !!\n", __FUNCTION__);
				memcpy( temp_BBT, this->ops.datbuf, page_size );
				page_counter++;
				mem_page_num--;

				while( mem_page_num>0 ){
					if ( this->read_ecc_page(mtd, 0, 2*ppb+page_counter, this->ops.datbuf, &this->ops, CP_NF_NONE,0,0) ){
						printk("[%s] load bbt B2 error!!\n", __FUNCTION__);
						kfree(temp_BBT);
						return -1;
					}
					memcpy( temp_BBT+page_counter*page_size, this->ops.datbuf, page_size );
					page_counter++;
					mem_page_num--;
				}
				memcpy( this->bbt, temp_BBT, sizeof(BB_t)*RBA );
			}else{
				printk("[%s] read BBT B2 tags fails, nand driver will creat BBT B2\n", __FUNCTION__);
				rtk_create_bbt(mtd, ppb<<1);
			}
		}else{
			printk("[%s] read BBT B1 and B2 with HW ECC fails\n", __FUNCTION__);
			kfree(temp_BBT);
			return -1;
		}
	}

	dump_BBT(mtd);

	if (temp_BBT)
		kfree(temp_BBT);

	return rc;
}


int rtk_nand_scan(struct mtd_info *mtd, int maxchips)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	unsigned char id[6];
	unsigned int device_size=0;
	unsigned int i;
	unsigned int nand_type_id ;
	int rtk_lookup_table_flag=0;
	unsigned char maker_code;
	unsigned char device_code;
	unsigned char B5th;
	unsigned char B6th;
	unsigned int block_size;
	unsigned int num_chips = 1;
	uint64_t chip_size=0;
	unsigned int num_chips_probe = 1;
	uint64_t result = 0;
	uint64_t div_res = 0;
	unsigned int num_coding_blk = 0;

	if ( !this->select_chip )
		this->select_chip = nand_select_chip;
	if ( !this->scan_bbt )
		this->scan_bbt = rtk_nand_scan_bbt;

	this->active_chip = 0;
	this->select_chip(mtd, 0);
#if 0
	if(platform_info.secure_boot)
		g_isSysSecure = 1;
#endif
//printk("nand_base_rtk version:0824-2011\n");
        //if(is_macarthur_cpu())
        //{
        //        if((REG_READ_U32(0xb8060008)&0x01)!=1)
        //       {
        //                printk("[%s]Doesn't support NAND boot for macathur\n",__FUNCTION__);
        //                return -1;
        //        }
        //}
	mtd->name = "rtk_nand";
#if		NAND_POWEROFF_CARDREADER_WITH_MULTI_READ
	NF_rtkcr_get_gpio();
	printk("(V)NAND_POWEROFF_CARDREADER_WITH_MULTI_READ\n");
#else
	printk("(X)NAND_POWEROFF_CARDREADER_WITH_MULTI_READ\n");
#endif

#if NAND_READ_SKIP_UPDATE_BBT
		printk("(V)NAND_READ_SKIP_UPDATE_BBT\n");
#else
		printk("(X)NAND_READ_SKIP_UPDATE_BBT\n");
#endif

	while (1) {
		// read 3 times for timing issue.
		this->read_id(mtd, id);
		this->read_id(mtd, id);
		this->read_id(mtd, id);

		this->maker_code = maker_code = id[0];
		this->device_code = device_code = id[1];
		nand_type_id = maker_code<<24 | device_code<<16 | id[2]<<8 | id[3];
		B5th = id[4];
		B6th = id[5];

printk("[Phoenix]READ ID:0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\n",id[0],id[1],id[2],id[3],id[4],id[5]);

#if 0
		if(!is_macarthur_cpu()||!is_nike_cpu())
		{
		for (i=1;  i<maxchips; i++) {
			this->select_chip(mtd, i);
			this->read_id(mtd, id);
			if ( maker_code !=  id[0] ||device_code != id[1] )
				break;
		}
		}
		else
		{
			printk("[NIKE]check 1\n");
		  i=1;
		}
#endif
        i=1;


		if (i > 1){
			num_chips_probe = i;
			printk(KERN_INFO "NAND Flash Controller detects %d dies\n", num_chips_probe);
		}

		for (i = 0; nand_device[i].name; i++){

		#if 0
			//for read id debug
			if(nand_device[i].id==0xADDA9095)
			{
				printk("nand_device[%d].id:0x%x, nand_type_id:0x%x\n",i,nand_device[i].id,nand_type_id);
				printk("nand_device[%d].CycleID5th:0x%x, B5th:0x%x\n",i,nand_device[i].CycleID5th,B5th);
				printk("nand_device[%d].CycleID6th:0x%x, B6th:0x%x\n",i,nand_device[i].CycleID6th,B6th);
			}
		#endif


			if ( nand_device[i].id==nand_type_id &&
				((nand_device[i].CycleID5th==0xff)?1:(nand_device[i].CycleID5th==B5th))&&
				((nand_device[i].CycleID6th==0xff)?1:(nand_device[i].CycleID6th==B6th))){
				REG_WRITE_U32( REG_TIME_PARA1,nand_device[i].T1);
				REG_WRITE_U32( REG_TIME_PARA2,nand_device[i].T2);
				REG_WRITE_U32( REG_TIME_PARA3,nand_device[i].T3);
				if ( nand_type_id != HY27UT084G2M ){
					REG_WRITE_U32( REG_MULTI_CHNL_MODE,0x20);
				}
				if (nand_device[i].size == num_chips_probe * nand_device[i].chipsize){
					if ( num_chips_probe == nand_device[i].num_chips ){
						printk("One %s chip has %d die(s) on board with index(%d)\n",
						nand_device[i].name, nand_device[i].num_chips, i);
						
						//mtd->PartNum = nand_device[i].name;
						device_size = nand_device[i].size;
						chip_size = nand_device[i].chipsize;
						page_size = nand_device[i].PageSize;
						block_size = nand_device[i].BlockSize;
						oob_size = nand_device[i].OobSize;
						num_chips = nand_device[i].num_chips;
						isLastPage = nand_device[i].isLastPage;
						rtk_lookup_table_flag = 1;
						
						REG_WRITE_U32( REG_TIME_PARA1,nand_device[i].T1);
						REG_WRITE_U32( REG_TIME_PARA2,nand_device[i].T2);
						REG_WRITE_U32( REG_TIME_PARA3,nand_device[i].T3);

						printk("index(%d) nand part=%s, id=0x%x, device_size=0x%x, page_size=0x%x, block_size=0x%x, oob_size=0x%x, num_chips=0x%x, isLastPage=0x%x, ecc_sel=0x%x \n",
							i,
							nand_device[i].name,
							nand_device[i].id,
							device_size,
							page_size,
							block_size,
							oob_size,
							num_chips,
							isLastPage,
							nand_device[i].eccSelect);
						
						break;
					}
				}
				else{
					if ( !strcmp(nand_device[i].name, "HY27UF084G2M" ) )
						continue;
					else{
						printk("We have %d the same %s chips on board\n",
							num_chips_probe/nand_device[i].num_chips, nand_device[i].name);
						//mtd->PartNum = nand_device[i].name;
						device_size = nand_device[i].size;
						chip_size = nand_device[i].chipsize;
						page_size = nand_device[i].PageSize;
						block_size = nand_device[i].BlockSize;
						oob_size = nand_device[i].OobSize;
						num_chips = nand_device[i].num_chips;
						isLastPage = nand_device[i].isLastPage;
						rtk_lookup_table_flag = 1;
						printk("nand part=%s, id=%x, device_size=%llu, chip_size=%llu, num_chips=%d, isLastPage=%d, eccBits=%d\n",
							nand_device[i].name, nand_device[i].id, nand_device[i].size, nand_device[i].chipsize,
							nand_device[i].num_chips, nand_device[i].isLastPage, nand_device[i].eccSelect);
						break;
					}
				}
			}
		}

		if ( !rtk_lookup_table_flag ){
			printk("Warning: Lookup Table do not have this nand flash !!\n");
			printk ("%s: Manufacture ID=0x%02x, Chip ID=0x%02x, "
					"3thID=0x%02x, 4thID=0x%02x, 5thID=0x%02x, 6thID=0x%02x\n",
					mtd->name, id[0], id[1], id[2], id[3], id[4], id[5]);
			return -1;
		}

		/* prepare nand info for linux kernel */
		sprintf(rtknand_info, "nandinfo=id:%x,ds:%llu,ps:%d,bs:%d,t1:%d,t2:%d,t3:%d,eb:%d", nand_device[i].id, nand_device[i].size, nand_device[i].PageSize, nand_device[i].BlockSize, nand_device[i].T1, nand_device[i].T2, nand_device[i].T3, nand_device[i].eccSelect);

		/* attributes setup */
		this->page_shift = generic_ffs(page_size)-1;
		//this->page_idx_mask = ~((1L << this->page_shift) -1);
		this->phys_erase_shift = generic_ffs(block_size)-1;
		this->oob_shift = generic_ffs(oob_size)-1;
		ppb = this->ppb = block_size >> this->page_shift;
		ppb_shift = this->phys_erase_shift - this->page_shift;

		if (chip_size){
			this->block_num = chip_size >> this->phys_erase_shift;
			this->page_num = chip_size >> this->page_shift;
			this->chipsize = chip_size;
			this->device_size = device_size;
			this->chip_shift =  generic_ffs(this->chipsize )-1;
		}

		//printk("[%s] block_num(0x%x), phys_erase_shift(0x%x)\n", __FUNCTION__, this->block_num, this->phys_erase_shift);

		this->pagemask = (this->chipsize >> this->page_shift) - 1;

		mtd->oobsize = this->oob_size = oob_size;

		mtd->writesize = page_size;//add by alexchang 0923-2010
		mtd->erasesize = block_size;
		mtd->writebufsize = page_size;

		mtd->erasesize_shift = this->phys_erase_shift;
		mtd->writesize_shift = this->page_shift;

		this->ecc_select = nand_device[i].eccSelect;//add by alexchang 0617-2011.
		//this->eccmode = MTD_ECC_RTK_HW;

		// Default to 6 bit BCH ECC if ecc_select = 0
		mtd->ecc_strength = (this->ecc_select)?this->ecc_select:0x6;
		if(this->ecc_select>=0x10){
			/* 1KB coding block */
			num_coding_blk = mtd->writesize >> 10;
		}
		else{
			/* 512B coding block */
			num_coding_blk = mtd->writesize >> 9;
		}
		/* Need to consider the ECC error in each mini page? */
		mtd->bitflip_threshold = max(mtd->ecc_strength, 4u) >> 2;

		mtd->ecc_strength *= num_coding_blk;

		break;

	}

	this->select_chip(mtd, 0);

	if ( num_chips != num_chips_probe )
		this->numchips = num_chips_probe;
	else
		this->numchips = num_chips;
	div_res = mtd->size = this->numchips * this->chipsize;

	do_div(div_res,block_size);
	result = div_res;
	result*=this->RBA_PERCENT;
	do_div(result,100);
	RBA = this->RBA = result;
	
//	RBA = this->RBA = (mtd->size/block_size) * this->RBA_PERCENT/100;
	//if(mtd->u32RBApercentage)
		//mtd->u32RBApercentage = this->RBA_PERCENT;
	//printk("[%s],mtd->u32RBApercentage %d%\n",__FUNCTION__,mtd->u32RBApercentage);
	this->bbt = kmalloc( sizeof(BB_t)*RBA, GFP_KERNEL );

	if ( !this->bbt ){
		printk("%s: Error, no enough memory for BBT\n",__FUNCTION__);
		return -1;
	}
	memset(this->bbt, 0,  sizeof(BB_t)*RBA);

	this->ops.datbuf = kmalloc( page_size, GFP_KERNEL );
	if ( !this->ops.datbuf ){
		printk("%s: Error, no enough memory for g_databuf\n",__FUNCTION__);
		return -ENOMEM;
	}
	memset(this->ops.datbuf, 0xff, page_size);

	this->ops.oobbuf = kmalloc( oob_size, GFP_KERNEL );
	if ( !this->ops.oobbuf ){
		printk("%s: Error, no enough memory for g_oobbuf\n",__FUNCTION__);
		return -ENOMEM;
	}
	memset(this->ops.oobbuf, 0xff, oob_size);

	mtd->type			= MTD_NANDFLASH;
	mtd->flags			= MTD_CAP_NANDFLASH;
	mtd->_erase			= nand_erase;
	//mtd->_point			= NULL;
	//mtd->_unpoint		= NULL;
	mtd->_read			= nand_read;
	mtd->_write			= nand_write;
	//mtd->read_ecc		= nand_read_ecc;
	//mtd->write_ecc		= nand_write_ecc;
	mtd->_read_oob		= nand_read_oob;
	mtd->_write_oob	= 	nand_write_oob;
	//mtd->_readv			= NULL;
	//mtd->writev			= NULL;
	//mtd->_readv_ecc	= NULL;
	//mtd->_writev_ecc	= NULL;
	mtd->_sync			= nand_sync;
	mtd->_lock				= NULL;
	mtd->_unlock			= NULL;
	//mtd->owner			= THIS_MODULE;

	mtd->_block_isbad			= nand_block_isbad;
	mtd->_block_markbad	= nand_block_markbad;

	/* Ken: 20090210 */
	//mtd->reload_bbt = rtk_nand_scan_bbt;


	return this->scan_bbt (mtd);
}


/* on the fly */
int nand_read_ecc_on_the_fly (struct mtd_info *mtd, loff_t from, size_t len,
			size_t *retlen, u_char *buf, struct mtd_oob_ops *ops,u16 cp_mode)
{	
	struct nand_chip *this = mtd->priv;
	unsigned long long  page, realpage,page_ppb;
	int data_len;
	int rc;
	unsigned int old_page, page_offset, block, real_block;
	int chipnr, chipnr_remap;
	int i;


	//printk("[%s] from:0x%x, len:0x%x, buf:0x%x \n", __FUNCTION__, from, len, buf);	
	
	if ((from + len) > mtd->size) {
		printk ("nand_read_ecc: Attempt read beyond end of device\n");
		*retlen = 0;
		return -EINVAL;
	}
	//printk("[%s] NOTALIGNED (mtd, from) 0x%x, NOTALIGNED(mtd, len)0x%x\n",__FUNCTION__,NOTALIGNED (mtd, from),NOTALIGNED(mtd, len));

	if (NOTALIGNED (mtd, from) || NOTALIGNED(mtd, len)) {
		printk (KERN_NOTICE "%s: Attempt to read not page aligned data\n", __func__);
		return -EINVAL;
	}

	realpage = (int)(from >> this->page_shift);
	this->active_chip = chipnr = chipnr_remap = (int)(from >> this->chip_shift);
	old_page = page = realpage & this->pagemask;
	page_offset = page & (ppb-1);
	page_ppb = page;
	do_div(page_ppb,ppb);
	block = (unsigned int)page_ppb;
	//printk("\t\tReady to READ blk:%u, page:%u, len:%u, page_size:%d, oob_size:%d\n",page/ppb,page%ppb,len,page_size,oob_size);

	this->select_chip(mtd, chipnr);

	if ( retlen )
		*retlen = 0;

	data_len = 0;

	while (data_len < len) {
		real_block = rtk_find_real_blk(mtd, block, &chipnr_remap);
		page = real_block*ppb + page_offset;
		if(data_len==0)			
            rc = this->read_ecc_page (mtd, this->active_chip, page, &buf[data_len], ops, cp_mode,1,len);
        else
			rc = this->read_ecc_page (mtd, this->active_chip, page, &buf[data_len], ops, cp_mode,0,0);
		
		if (rc < 0) {
			
			if (rc == -1){
				printk ("%s: read_ecc_page: Un-correctable HW ECC\n", __FUNCTION__);
				//continue;

				//update BBT
				if(check_BBT(mtd,page_ppb)==0)
				{

				for( i=0; i<RBA; i++){
					if ( this->bbt[i].bad_block == BB_INIT && this->bbt[i].remap_block != RB_INIT){
						if ( chipnr != chipnr_remap)	//remap block is bad
							this->bbt[i].BB_die = chipnr_remap;
						else
							this->bbt[i].BB_die = chipnr;
						this->bbt[i].bad_block = page_ppb;
						break;
					}
				}

				dump_BBT(mtd);

				if ( rtk_update_bbt (mtd, &this->ops, this->bbt) ){
					printk("[%s] rtk_update_bbt() fails\n", __FUNCTION__);
					return -1;
					}
				}

				this->ops.oobbuf[0] = 0x00;
				block = page_ppb;
				if ( isLastPage){
					this->erase_block (mtd, this->active_chip, block*ppb);
					this->write_oob(mtd, this->active_chip, block*ppb+ppb-1, oob_size, this->ops.oobbuf);
					this->write_oob(mtd, this->active_chip, block*ppb+ppb-2, oob_size, this->ops.oobbuf);
				}else{
					this->erase_block (mtd, this->active_chip, block*ppb);
					this->write_oob(mtd, this->active_chip, block*ppb, oob_size, this->ops.oobbuf);
					this->write_oob(mtd, this->active_chip, block*ppb+1, oob_size, this->ops.oobbuf);
				}
				printk("rtk_read_ecc_page: Un-correctable HW ECC Error at page=%llx\n", page);
			}else{
				printk ("%s: read_ecc_page:  semphore failed\n", __FUNCTION__);
				return -1;
			}
		}
		//else
			//printk("\t\tConfirm to READ blk:%u, page:%u Succeed!!\n",page/ppb,page%ppb);
		data_len += page_size;

		if(ops)
			ops->oobretlen = oob_size;

		old_page++;
		page_offset = old_page & (ppb-1);
		if ( data_len<len && !(old_page & this->pagemask)) {
			old_page &= this->pagemask;
			chipnr++;
			this->active_chip = chipnr;
			this->select_chip(mtd, chipnr);
		}
		block = old_page/ppb;
	}

	if ( retlen ){
		if ( data_len == len )
			*retlen = data_len;
		else{
				printk("[%s] error: data_len %d != len %zu\n", __FUNCTION__, data_len, len);
				return -1;
		}
	}
	//printk("[%s]OK\n",__FUNCTION__);
	//rtk_hexdump("buf: ", buf, *retlen);
	
	return 0;
}

int nand_read_on_the_fly (struct mtd_info *mtd, loff_t from, size_t len, size_t * retlen, u_char * buf, u16 cp_mode)
{
	int rc=0;
	unsigned int tmp_len;

	tmp_len = len;

	rc = nand_read_ecc_on_the_fly (mtd, from, len, retlen, buf, NULL,cp_mode);

	if(*retlen == len)
		*retlen=tmp_len;
		
	return rc;
}
