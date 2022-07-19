/******************************************************************************
 * $Id: rtk_nand.c 337905 2010-10-18 01:32:27Z alexchang2131 $
 * drivers/mtd/nand/rtk_nand.c
 * Overview: Realtek NAND Flash Controller Driver
 * Copyright (c) 2008 Realtek Semiconductor Corp. All Rights Reserved.
 * Modification History:
 *    #000 2010-07-02 AlexChang   create file
 *
 *
 *******************************************************************************/

#include <common.h>
#include <linux/mtd/rtk_nand.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/partitions.h>
//#include <linux/slab.h>
//#include <linux/sysctl.h>
//#include <linux/sched.h>
#include <linux/list.h>
//#include <linux/pm.h>
#include <asm/io.h>
//#include <linux/mtd/rtk_nand_reg.h>
//#include <linux/mtd/rtk_nand.h>
#include <linux/bitops.h>
#include <mtd/mtd-abi.h>
//#include <asm/r4kcache.h>
//#include <linux/jiffies.h>
//#include <linux/delay.h>
#include <linux/time.h>
//#include <linux/proc_fs.h>
#include <linux/string.h>

//#include <asm/mach-rtk_dmp/platform.h>
#include <asm/arch/rbus/nand_reg.h>
#include <asm/arch/platform_lib/board/gpio.h>

//#include <linux/platform_device.h>
//#include <linux/interrupt.h>


//#include <stdlib.h>
//#include <linux/mtd/rtk_cp_reg.h>
//#include <linux/mtd/rtk_mcp_reg.h>
//#define RTK_NAND_INTERRUPT (0)


#define BANNER  "Realtek NAND Flash Driver"
#define VERSION  "$Id: rtk_nand.c 337905 2010-10-18 01:32:27Z alexchang2131 $"
#define RTK_NAND_INTERRUPT	(0)
#define MTDSIZE	(sizeof (struct mtd_info) + sizeof (struct nand_chip))
#define MAX_PARTITIONS	16
#define BOOTCODE	16*1024*1024	//16MB
#define FACT_PARAM_SIZE 4*1024*1024 //4MB for TV factory parameter use.
#define DRIVER_NAME "rtkNF"
#define NF_INIT	(0)
#define NF_READ_TRIGGER 	(1)
#define NF_WRITE_TRIGGER 	(2)
#define NF_ERASE_TRIGGER 	(3)
#define NF_POLL_STATUS 	(4)
#define NF_WAKE_UP	(5)

#define NF_AUTO_IRQ_MASK	(0x08)
#define NF_DMA_IRQ_MASK		(0x10)
#define NF_POLL_IRQ_MASK	(0x80)
#define NF_XFER_IRQ_MASK	(0x04)
#define NF_IRQ_MASK	(NF_XFER_IRQ_MASK|NF_AUTO_IRQ_MASK|NF_DMA_IRQ_MASK|NF_POLL_IRQ_MASK)

#define NF_RESET_IRQ	REG_WRITE_U32(REG_NAND_ISREN,(0xff<<1|0x00));\
						REG_WRITE_U32(REG_NAND_ISR,(0xff<<1|0x00))

//#define NF_RESET_IRQ	NULL

#define NF_ENABLE_IRQ(mask)	REG_WRITE_U32(REG_NAND_ISREN,(mask|0x01))


#if RTK_NAND_INTERRUPT
static int g_nfFlag = NF_INIT ;
#endif

#define CLR_REG_NAND_ISR REG_WRITE_U32(REG_NAND_ISR,(0xFF<<1))

#define ISR_EN_READ (0x10)
#define ISR_EN_WRITE (0x08)

//#define MODULE_AUTHOR(x)	/* x */
//#define MODULE_DESCRIPTION(x)	/* x */

#define OTP_K_S                 2048
#define OTP_K_H					2304
#define OTP_K_N                 2560

//static struct semaphore sem_NF_CARDREADER;

static int g_id_chain = 0;
static int g_enReadRetrial = 0;
//static unsigned char regVal1=0;
//static unsigned char regVal2=0;
//static unsigned char regVal3=0;
//static unsigned char regVal4=0;

static int read_retry_toshiba_cnt[]={0x00, 0x00, 0x04, 0x7c, 0x78, 0x74, 0x08};

static int read_retry_toshiba_cnt_new[8][5]={
        {0x00, 0x00, 0x00, 0x00, 0x00},
        {0x04, 0x04, 0x7c, 0x7e, 0x00},
        {0x00, 0x7c, 0x78, 0x78, 0x00},
        {0x7c, 0x76, 0x74, 0x72, 0x00},
        {0x08, 0x08, 0x00, 0x00, 0x00},
        {0x0b, 0x7e, 0x76, 0x74, 0x00},
        {0x10, 0x76, 0x72, 0x70, 0x00},
        {0x02, 0x7c, 0x7e, 0x70, 0x00}
};

//static unsigned char nRun=0;
//static unsigned char nInc=0;

//static int  rtk_nand_init (void);
//static void rtk_xfer_GetParameter(void);
//static void rtk_xfer_SetParameter(unsigned char val1,unsigned char val2,unsigned char val3,unsigned char val4);
static void rtk_set_feature_micron(int P1);

//static void rtk_SetVal( char val1, char val2, char val3, char val4);
//static void rtk_SetReadRetrialMode(unsigned int run);
//static int rtk_read_ecc_page_reTrial (struct mtd_info *mtd, u16 chipnr, unsigned int page, u_char *data_buf, u_char *oob_buf);

extern int pcb_mgr_get_enum_info_byname(char *enum_name, unsigned long long *value);
//extern platform_info_t platform_info;

extern int add_mtd_partitions(struct mtd_info *master, const struct mtd_partition *parts, int nbparts);
extern int parse_mtd_partitions(struct mtd_info *master, const char **types, struct mtd_partition **pparts, struct mtd_part_parser_data *data);
extern int add_mtd_device(struct mtd_info *mtd);

#ifdef CONFIG_CMD_KEY_BURNING
extern int OTP_Get_Byte(int offset, unsigned char *ptr, unsigned int cnt);
#endif
extern int swap_endian(unsigned int input);
//extern int del_mtd_partitions(struct mtd_info *master);
extern int AES_ECB_encrypt(unsigned char * src_addr, unsigned int length, unsigned char * dst_addr, unsigned int key[4]);
#if RTK_NAND_INTERRUPT
static wait_queue_head_t	g_irq_waitq;

//#define RTK_WAIT_EVENT wait_event_interruptible(g_host->irq_waitq,g_nfFlag==NF_WAKE_UP)
#define RTK_WAIT_EVENT wait_event_interruptible(g_irq_waitq,g_nfFlag==NF_WAKE_UP)

#define CHECK_IRQ(flag,reg,mask,value) ((g_nfFlag==flag)&&((REG_READ_U32(reg)&mask)==value))
#define CHECK_REG(reg,mask,value) (REG_READ_U32(reg)&mask==value)
//#define CLEAR_IRQ(reg,mask)	(REG_WRITE_U32(reg,(REG_READ_U32(reg)|mask)&0xfffffffe))
#define CLEAR_IRQ(reg,mask)	(REG_WRITE_U32(reg,mask))
#define NF_AUTO_TRIG_ISR	(0x08)
#define NF_DMA_ISR	(0x10)
#define NF_POLL_STATUS_ISR	(0x80)
#endif

//#define RETRY_COUNT	(0x20)

//Add for GPIO Setting
#define BIT(x) (1 << (x))
#define SETBITS(x,y) ((x) |= (y))
#define CLEARBITS(x,y) ((x) &= (~(y)))
#define SETBIT(x,y) SETBITS((x), (BIT((y))))
#define CLEARBIT(x,y) CLEARBITS((x), (BIT((y))))
#if RTK_NAND_INTERRUPT
static struct rtk_nand_host *g_host;
#endif

#define NF_GPIO_OUT	(1)
#define NF_GPIO_IN	(0)
//#define NF_WP_ENABLE	(0)
//#define NF_WP_DISABLE	(1)

static unsigned int g_BootcodeSize = 0;
static unsigned int g_Factory_param_size = 0;
//static int g_WP_en = 0;
unsigned int g_NF_pageSize = 0;
unsigned char g_isRandomize = 0;

#define NF_OOB_SIZE 512

const char *ptypes[] = {"cmdlinepart", NULL};

/* nand driver low-level functions */
static int rtk_read_oob(struct mtd_info *mtd, u16 chipnr, int page, int len, u_char *buf);
static int rtk_read_ecc_page(struct mtd_info *mtd, u16 chipnr, unsigned int page,
			u_char *data, struct mtd_oob_ops *ops, u16 cp_mode, u16 cp_first, size_t cp_len);
static int rtk_write_oob(struct mtd_info *mtd, u16 chipnr, int page, int len, const u_char *buf);
static int rtk_write_ecc_page(struct mtd_info *mtd, u16 chipnr, unsigned int page,
			const u_char *data, struct mtd_oob_ops *ops, int isBBT);
static int rtk_erase_block(struct mtd_info *mtd, u16 chipnr, int page);

/* Global Variables */
struct mtd_info *rtk_mtd;
//static DECLARE_MUTEX (sem);


static int page_size, oob_size, ppb;
static int RBA_PERCENT = 5;
char rtknand_info[128] = {0};

//static unsigned int u32CP_mode = 0;
//static unsigned int cpSel = 0;
//static unsigned int *regKey0;
//static unsigned int *regKey1;
//static unsigned int *regKey2;
//static unsigned int *regKey3;

//DECLARE_MUTEX (sem_NF_CARDREADER);
//EXPORT_SYMBOL(sem_NF_CARDREADER);

#if RTK_ARD_ALGORITHM //Variable declartion
	#define TOTAL_BLK_NUM	8192
	const unsigned int g_RecBlkStart = 64;
	const unsigned int g_RecBlkEnd   = 7389;

	const unsigned int g_PorcWindowSize = 64;
	const unsigned int g_ReadCntThrshld = 0x200000;
	//const unsigned int g_ReadCntThrshld = 0x400000;

	const unsigned int g_MaxMinDist = 8192;
	const unsigned int g_DistInc = 1;

	const unsigned int g_WinTrigThrshld = 8192;
	static unsigned int g_WinTrigCnt = 0;

	static unsigned int g_RecArray[8192]={0};

	static unsigned int g_u32WinStart = 0;
	static unsigned int g_u32WinEnd = 0;

	int whichBlk= 0;
	int pagePerBlk = 0;

#endif
struct rtk_nand_host {
	struct mtd_info		mtd;
	struct nand_chip	nand;
	struct mtd_partition	*parts;
	struct device		*dev;

	void			*spare0;
	void			*main_area0;
	void			*main_area1;

	void __iomem		*base;
	void __iomem		*regs;
	int			status_request;
	struct clk		*clk;
	int			clk_act;
	int			irq;

#if RTK_NAND_INTERRUPT
	wait_queue_head_t	irq_waitq;
#endif
	uint8_t			*data_buf;
	unsigned int		buf_start;
	int			spare_len;
};

void syncPageRead(void)
{
    CP15DMB;
    //REG32(0x1801a020) = 0x0;
    REG_WRITE_U32(0x1801a020, 0x0);
    CP15DMB;
}

static void writeNFKey(unsigned int data[4])
{

	REG_WRITE_U32(CP_NF_KEY_0, data[0]);
	REG_WRITE_U32(CP_NF_KEY_1, data[1]);
	REG_WRITE_U32(CP_NF_KEY_2, data[2]);
	REG_WRITE_U32(CP_NF_KEY_3, data[3]);

}

static unsigned int OTP_JUDGE_BIT(unsigned int offset)
{
    unsigned int div_n=0, rem_n=0;
    unsigned int align_rem_n=0, real_n=0;
    phys_addr_t align_n=0;

    rem_n = offset%8;
    div_n = offset/8;

    align_n = div_n & ~0x3;
    align_rem_n = div_n & 0x3;

    real_n = REG_READ_U32(OTP_REG_BASE + align_n);
    return(((real_n >>(align_rem_n*8)) >> rem_n)&1);
}

//----------------------------------------------------------------------------
unsigned int getGPIOBit(unsigned int nGPIOBase, unsigned int nGPIOnum)
{
        phys_addr_t whichReg = 0;
        unsigned int whichBit = 0;
        unsigned int ret=0;
        whichReg = nGPIOBase+4*(nGPIOnum/32);
        whichBit = nGPIOnum%32;
        ret = REG_READ_U32(whichReg);
        ret>>=whichBit;
        ret&=(0x1);
        return ret;
}
//----------------------------------------------------------------------------

unsigned int getGPIORegVal(unsigned int nGPIOBase, unsigned int nGPIOnum)
{
        phys_addr_t whichReg = 0;
//        unsigned int whichBit = 0;
        whichReg = nGPIOBase+4*(nGPIOnum/32);
		//printk("\tgetRegister 0x%x\n",whichReg);
        return REG_READ_U32(whichReg);
}

//----------------------------------------------------------------------------
int is_jupiter_cpu(void)
{
	return 0;
}
//----------------------------------------------------------------------------
int is_saturn_cpu(void)
{
	return 1;
}

//----------------------------------------------------------------------------
int is_darwin_cpu(void)
{
	return 0;
}

//----------------------------------------------------------------------------

int is_macarthur_cpu(void)
{
	return 0;
}

//----------------------------------------------------------------------------
int is_nike_cpu(void)
{
	return 0;
}

//----------------------------------------------------------------------------
int is_venus_cpu(void)
{
	return 0;
}

//----------------------------------------------------------------------------
int is_neptune_cpu(void)
{
	return 0;
}

//----------------------------------------------------------------------------
int is_mars_cpu(void)
{
	return 0;
}

//----------------------------------------------------------------------------










#if RTK_ARD_ALGORITHM //function declartion
//----------------------------------------------------------------------------
void RTK_ARD_DumpProcWin(int nStartBlk, int nSize)
{
	int i=0;
	unsigned int nSysStartBlk = g_RecBlkStart;
	for(i=0;i<nSize;i++)
	{
		if(nStartBlk<=g_RecBlkEnd)
		{
			printk("[%u] %u \n",nStartBlk,g_RecArray[nStartBlk]);
			nStartBlk++;
		}
		else
		{
			printk("[%u] %u \n",nSysStartBlk,g_RecArray[nSysStartBlk]);
			nSysStartBlk++;
		}
	}
}
//----------------------------------------------------------------------------
void slideProcWindowPtr()
{
	int tmp=0;
	g_u32WinStart = g_u32WinEnd;
	if(((g_u32WinEnd+g_PorcWindowSize-1)>g_RecBlkEnd))//reverse
	{
		tmp =  g_RecBlkEnd - g_u32WinEnd+1;
		g_u32WinEnd = g_RecBlkStart + (g_PorcWindowSize - tmp)-1;
	}
	else
	{
		g_u32WinEnd+=(g_PorcWindowSize-1);
	}
}
//----------------------------------------------------------------------------
void resetBlock(int nBlkNo)
{
	static unsigned int tmpCnt = 0;
//Reser block....TBD...
////////////////////////////
	tmpCnt++;

printk("\n");
printk("\t[AT]Reset block [%u] : %u\n",nBlkNo,g_RecArray[nBlkNo]);
printk("\t[AT]Total reset %u blocks\n",tmpCnt);
	g_RecArray[nBlkNo]=0;

}
//----------------------------------------------------------------------------
void travelProcWindow()//When WinTrigCnt > WinTrigThrshld
{
	int maxVal[2];
	int minVal[2];
	int i=0;
	int idx=g_u32WinStart;

	if(g_RecArray[g_u32WinEnd] > g_RecArray[g_u32WinStart])
	{
		minVal[0]=g_u32WinStart;
		minVal[1]=g_RecArray[g_u32WinStart];
		maxVal[0]=g_u32WinEnd;
		maxVal[1]=g_RecArray[g_u32WinEnd];
	}
	else
	{
		maxVal[0]=g_u32WinStart;
		maxVal[1]=g_RecArray[g_u32WinStart];
		minVal[0]=g_u32WinEnd;
		minVal[1]=g_RecArray[g_u32WinEnd];
	}

	printk("++++Before Travel++++\n");
	printk("minVal[%u] %u, maxVal[%u] %u\n",minVal[0],minVal[1],maxVal[0],maxVal[1]);
	RTK_ARD_DumpProcWin(g_u32WinStart,g_PorcWindowSize);
	for(i=0;i<g_PorcWindowSize;i++)
	{
		if(g_RecArray[idx]>=g_ReadCntThrshld)
			resetBlock(idx);
		if(idx<=g_RecBlkEnd)
		{
			if(g_RecArray[idx]<minVal[1])//Process minimun value
			{
				minVal[0]=idx;
				minVal[1]=g_RecArray[idx];
			}
			if(g_RecArray[idx]>maxVal[1])//Process maximun value
			{
				maxVal[0]=idx;
				maxVal[1]=g_RecArray[idx];
			}
			if(idx==g_RecBlkEnd)
				idx = g_RecBlkStart;
			else
				idx++;
		}

	}
	printk("----After Travel w/o Grouping ----\n");
	printk("minVal[%u] %u, maxVal[%u] %u\n",minVal[0],minVal[1],maxVal[0],maxVal[1]);

	//Grouping
	g_RecArray[minVal[0]] += g_DistInc;
	if((maxVal[1]-minVal[1]) < g_MaxMinDist)
	{
		g_RecArray[maxVal[0]] += g_MaxMinDist;
	}

	RTK_ARD_DumpProcWin(g_u32WinStart,g_PorcWindowSize);
	slideProcWindowPtr();
	g_WinTrigCnt = 0; //Reset windows trigger count
}
#endif
//----------------------------------------------------------------------------

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
 char *rtkNF_parse_token(const char *parsed_string, const char *token)
{
	const char *ptr = parsed_string;
	const char *start, *end, *value_start, *value_end;
	char *ret_str = NULL;

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
				if(ret_str)
				{
					strncpy(ret_str, value_start, value_end-value_start);
					ret_str[value_end-value_start] = '\0';
				}
				return ret_str;
			} else {
				if(ret_str)
				{
					ret_str = kmalloc(1, GFP_KERNEL);
					strcpy(ret_str, "");
				}
				return ret_str;
			}
		}
	}

	return (char*)NULL;
}

//----------------------------------------------------------------------------

unsigned int rtkNF_getBootcodeSize(void)
{
    char *param = NULL;
	unsigned int retBootcodeSize = -1 ;
    //param=(char *)rtkNF_parse_token(platform_info.system_parameters,"nand_boot_size");

    if(param)
		retBootcodeSize = simple_strtoul(param, (char**)&retBootcodeSize, 16);
    return retBootcodeSize;
}
//----------------------------------------------------------------------------
unsigned int rtkNF_getFactParaSize(void)
{
    char *param = NULL;
	unsigned int retFactParaSize = -1 ;
  //  param=(char *)rtkNF_parse_token(platform_info.system_parameters,"factory_size");

    if(param)
		retFactParaSize = simple_strtoul(param, (char**)&retFactParaSize, 16);
    return retFactParaSize;
}

//----------------------------------------------------------------------------
unsigned int rtkNF_getRBAPercent(void)
{
    char *param = NULL;
	unsigned int retRbaPercent = -1 ;
//    param=(char *)rtkNF_parse_token(platform_info.system_parameters,"rba_percent");

    if(param)
		retRbaPercent = simple_strtoul(param, (char**)&retRbaPercent, 16);
    return retRbaPercent;
}

//----------------------------------------------------------------------------

void WAIT_DONE(unsigned int addr_int, phys_addr_t  mask, unsigned int value)
{
        int timeout = 0;
	void *addr = (void*)(uintptr_t)addr_int;

	while ( (REG_READ_U32(addr) & mask) != value )
	{

                if(timeout++>100000){
                    //printk("[%s]timeout..%d\n",__FUNCTION__, timeout);
                    return;
                 }
    
		asm("nop");
	}
}
//----------------------------------------------------------------------------
static void rtk_read_oob_from_SRAM(struct mtd_info *mtd, __u8 *r_oobbuf)
{
	unsigned int reg_oob, reg_num;
	int i;
	//printk("mtd->ecctype 0x%x\n",mtd->ecctype);
//	if ( mtd->ecctype == MTD_ECC_NONE )
//	if ( mtd->ecctype == MTD_ECC_NONE ||(mtd->ecctype!=MTD_ECC_RTK_HW))
	if (1)
	{
		reg_num = REG_NF_BASE_ADDR;
		reg_oob = REG_READ_U32(reg_num);
		r_oobbuf[0] = reg_oob & 0xff;
		r_oobbuf[1] = (reg_oob >> 8) & 0xff;
		r_oobbuf[2] = (reg_oob >> 16) & 0xff;
		r_oobbuf[3] = (reg_oob >> 24) & 0xff;

		reg_num = REG_NF_BASE_ADDR+4;
		reg_oob = REG_READ_U32(reg_num);
		r_oobbuf[4] = reg_oob & 0xff;

		reg_num = REG_NF_BASE_ADDR+16;
		reg_oob = REG_READ_U32(reg_num);
		r_oobbuf[5] = reg_oob & 0xff;
		r_oobbuf[6] = (reg_oob >> 8) & 0xff;
		r_oobbuf[7] = (reg_oob >> 16) & 0xff;
		r_oobbuf[8] = (reg_oob >> 24) & 0xff;

		reg_num = REG_NF_BASE_ADDR+16*2;
		reg_oob = REG_READ_U32(reg_num);
		r_oobbuf[9] = reg_oob & 0xff;
		r_oobbuf[10] = (reg_oob >> 8) & 0xff;
		r_oobbuf[11] = (reg_oob >> 16) & 0xff;
		r_oobbuf[12] = (reg_oob >> 24) & 0xff;

		reg_num = REG_NF_BASE_ADDR+16*3;
		reg_oob = REG_READ_U32(reg_num);
		r_oobbuf[13] = reg_oob & 0xff;
		r_oobbuf[14] = (reg_oob >> 8) & 0xff;
		r_oobbuf[15] = (reg_oob >> 16) & 0xff;
		r_oobbuf[16] = (reg_oob >> 24) & 0xff;

	}
	else
	{
		for ( i=0; i < 16; i++)
			{
				reg_num = REG_NF_BASE_ADDR + i*4;
				reg_oob = REG_READ_U32(reg_num);
				r_oobbuf[i*4+0] = reg_oob & 0xff;
				r_oobbuf[i*4+1] = (reg_oob >> 8) & 0xff;
				r_oobbuf[i*4+2] = (reg_oob >> 16) & 0xff;
				r_oobbuf[i*4+3] = (reg_oob >> 24) & 0xff;
			}
	}
}

//----------------------------------------------------------------------------
static void rtk_nand_read_id(struct mtd_info *mtd, u_char id[6])
{
#define XFER_MODE
	int id_chain;
	//printk("rtk_nand_read_id \n");
	//Set SRAM path and access mode
#ifdef XFER_MODE
	REG_WRITE_U32(REG_DATA_TL0,NF_DATA_TL0_length0(0x06));
	REG_WRITE_U32(REG_DATA_TL1,NF_DATA_TL1_access_mode(0x01));

	//Set PP
	REG_WRITE_U32(REG_READ_BY_PP,NF_READ_BY_PP_read_by_pp(0x0));

	REG_WRITE_U32(REG_PP_CTL0,NF_PP_CTL0_pp_enable(0x01));
	REG_WRITE_U32(REG_PP_CTL1,NF_PP_CTL1_pp_start_addr(0));

	//Set command
	REG_WRITE_U32(REG_ND_CMD,NF_ND_CMD_cmd(CMD_READ_ID));
	REG_WRITE_U32(REG_ND_CTL,NF_ND_CTL_xfer(0x01));
	WAIT_DONE(REG_ND_CTL,0x80,0);

	//Set address
	REG_WRITE_U32(REG_ND_PA0, 0);
	REG_WRITE_U32(REG_ND_PA1, 0);
	REG_WRITE_U32(REG_ND_PA2,NF_ND_PA2_addr_mode(0x07));

	REG_WRITE_U32(REG_ND_CTL,NF_ND_CTL_xfer(1)|NF_ND_CTL_tran_mode(1));
	WAIT_DONE(REG_ND_CTL,0x80,0);
	//Enable XFER mode
	REG_WRITE_U32(REG_ND_CTL,NF_ND_CTL_xfer(1)|NF_ND_CTL_tran_mode(4));
	WAIT_DONE(REG_ND_CTL,0x80,0);

	//Reset PP
	REG_WRITE_U32(REG_PP_CTL0,NF_PP_CTL0_pp_reset(1));

	//Move data to DRAM from SRAM
	REG_WRITE_U32(REG_SRAM_CTL,NF_SRAM_CTL_map_sel(1)|NF_SRAM_CTL_access_en(1)|NF_SRAM_CTL_mem_region(0));

	id_chain = REG_READ_U32(REG_ND_PA0);
	//printk("id_chain 1 = 0x%x \n", id_chain);
	id[0] = id_chain & 0xff;
	id[1] = (id_chain >> 8) & 0xff;
	id[2] = (id_chain >> 16) & 0xff;
	id[3] = (id_chain >> 24) & 0xff;

	g_id_chain = id_chain;
	//if(id_chain==0xDA94D7AD)
	//{
		//printk("Detect H27UBG8T2B and enable read-retrial mode...\n");
		//g_enReadRetrial = 1;
		//g_isRandomize = 1;
		//printk("Enable Read-retrial mode...\n");
		//printk("Enable Randomized mechanism\n");
	//}
	if(id_chain == 0x4b44642c)
	{
		printk("Detect MT29F64G08CBABA and enable read-retrial mode...\n");
		g_enReadRetrial = 1;
	}else if(id_chain == 0x4b44442c)
	{
		printk("Detect MT29F32G08CBADA and enable read-retrial mode\n");
		g_enReadRetrial = 1;
	}else if(id_chain == 0x9384d798){
		printk("Detect TC58TEG5DCJT and enable read-retrial mode...\n");
		g_enReadRetrial = 1;
        }else if(id_chain == 0x9384de98){
		printk("Detect TC58TEG6DCJT and enable read-retrial mode...\n");
		g_enReadRetrial = 1;
        }else if(id_chain == 0x9394de98){
		printk("Detect TC58TEG6DDK and enable read-retrial mode...\n");
		g_enReadRetrial = 1;
        }


	id_chain = REG_READ_U32(REG_ND_PA1);
	//printk("id_chain 2 = 0x%x \n", id_chain);
	id[4] = id_chain & 0xff;
	id[5] = (id_chain >> 8) & 0xff;

	REG_WRITE_U32(REG_SRAM_CTL,0x0);	//# no omitted
#else
	REG_WRITE_U32(REG_PP_CTL0,NF_PP_CTL0_pp_reset(0x01));
	REG_WRITE_U32(REG_DATA_TL0,NF_DATA_TL0_length0(0x00));
	REG_WRITE_U32(REG_DATA_TL1,NF_DATA_TL1_access_mode(0x01)|NF_DATA_TL1_length1(0x2));

	//Set page length at auto mode 
	REG_WRITE_U32(REG_PAGE_LEN, 0x1);
	REG_WRITE_U32(REG_READ_BY_PP,NF_READ_BY_PP_read_by_pp(0x1));

	REG_WRITE_U32(REG_PP_CTL0,NF_PP_CTL0_pp_enable(0x01));
	REG_WRITE_U32(REG_PP_CTL1,NF_PP_CTL1_pp_start_addr(0));

	//Set command
	REG_WRITE_U32(REG_ND_CMD,NF_ND_CMD_cmd(CMD_READ_ID));

	//Set address
	REG_WRITE_U32(REG_ND_PA0, 0);
	REG_WRITE_U32(REG_ND_PA1, 0);
	REG_WRITE_U32(REG_ND_PA2,NF_ND_PA2_addr_mode(0x07));
	
	//Set ECC	
	REG_WRITE_U32(REG_MULTI_CHNL_MODE, NF_MULTI_CHNL_MODE_ecc_no_check(1) | NF_MULTI_CHNL_MODE_ecc_pass(1));	//Set HW no check ECC	
	REG_WRITE_U32(REG_ECC_STOP, NF_ECC_STOP_ecc_n_stop(0x1));	//Set ECC no stop
	//Set DMA	
	REG_WRITE_U32(REG_DMA_CTL1, id);	//Set DRAM start address
	REG_WRITE_U32(REG_DMA_CTL2, 0x1);	//Transfer length (Unit = 512B)	
	REG_WRITE_U32(REG_DMA_CTL3, NF_DMA_CTL3_ddr_wr(1) | NF_DMA_CTL3_dma_xfer(1));	//Set DMA direction and enable DMA transfer 
	//Enable Auto mode
	REG_WRITE_U32(REG_AUTO_TRIG,NF_AUTO_TRIG_auto_trig(1)|NF_AUTO_TRIG_spec_auto_case(1)| NF_AUTO_TRIG_auto_case(0));
	WAIT_DONE(REG_AUTO_TRIG,0x80,0);
	//Enable Auto mode
	REG_WRITE_U32(REG_AUTO_TRIG,NF_AUTO_TRIG_auto_trig(1)|NF_AUTO_TRIG_spec_auto_case(0)| NF_AUTO_TRIG_auto_case(4));
	WAIT_DONE(REG_AUTO_TRIG,0x80,0);
	//Wait DMA done	
	WAIT_DONE(REG_DMA_CTL3, 0x01, 0x00);	
#endif

}
//----------------------------------------------------------------------------
// add read-retry for TOSHIBA
void rtk_set_terminate_toshiba(void){


	printk("[%s] enter\n", __FUNCTION__);

	//Set command
	REG_WRITE_U32(REG_ND_CMD, NF_ND_CMD_cmd(0xff));	//Set CMD1
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0x0) | NF_ND_CTL_tran_mode(0x0));	//Enable Xfer, eanble ECC and set transfer mode 
	WAIT_DONE(REG_ND_CTL, 0x80, 0x00);	//Wait xfer done

}

//----------------------------------------------------------------------------
// add read-retry for TOSHIBA
void rtk_set_pre_condition_toshiba(void){


	printk("[%s] enter\n", __FUNCTION__);

	//Set command
	REG_WRITE_U32(REG_ND_CMD, NF_ND_CMD_cmd(0x5C));	//Set CMD1
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0x0) | NF_ND_CTL_tran_mode(0x0));	//Enable Xfer, eanble ECC and set transfer mode 
	WAIT_DONE(REG_ND_CTL, 0x80, 0x00);	//Wait xfer done

	//Set command
	REG_WRITE_U32(REG_ND_CMD, NF_ND_CMD_cmd(0xC5));	//Set CMD2
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0x0) | NF_ND_CTL_tran_mode(0x0));	//Enable Xfer, eanble ECC and set transfer mode 
	WAIT_DONE(REG_ND_CTL, 0x80, 0x00);	//Wait xfer done


}

//----------------------------------------------------------------------------
// add read-retry for TOSHIBA
void rtk_set_ext_feature_toshiba(void){


	printk("[%s] enter\n", __FUNCTION__);

	//Set command
	REG_WRITE_U32(REG_ND_CMD, NF_ND_CMD_cmd(0x26));	//Set CMD1
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0x0) | NF_ND_CTL_tran_mode(0x0));	//Enable Xfer, eanble ECC and set transfer mode 
	WAIT_DONE(REG_ND_CTL, 0x80, 0x00);	//Wait xfer done

	//Set command
	REG_WRITE_U32(REG_ND_CMD, NF_ND_CMD_cmd(0x5d));	//Set CMD2
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0x0) | NF_ND_CTL_tran_mode(0x0));	//Enable Xfer, eanble ECC and set transfer mode 
	WAIT_DONE(REG_ND_CTL, 0x80, 0x00);	//Wait xfer done


}

//----------------------------------------------------------------------------
// add read-retry for TOSHIBA
void rtk_set_feature_toshiba(int P1){

        int i = 0;

	printk("[%s] set slow timer, cnt=0x%x\n", __FUNCTION__, P1);

	REG_WRITE_U32(0x18000038, 0xf);		//432/(N+1)	
	REG_WRITE_U32(REG_TIME_PARA3,  NF_TIME_PARA3_T3(0x1));			//Set flash timming T3	
	REG_WRITE_U32(REG_TIME_PARA2,  NF_TIME_PARA2_T2(0x1));			//Set flash timming T2	
	REG_WRITE_U32(REG_TIME_PARA1,  NF_TIME_PARA1_T1(0x1));			//Set flash timming T1

    for(i=4;i<8;i++){
        printk("[%s] enter set REG_DATA_TL0 to 0x1, addr=0x%x\n", __FUNCTION__, i);
	//REG_WRITE_U32(REG_DATA_TL0, 0x1);	//Set data transfer count[7:0]
	//REG_WRITE_U32(REG_DATA_TL1, NF_DATA_TL1_access_mode(0x1) | NF_DATA_TL1_length1(0x0));	//Set data transfer count[13:8], SRAM path and access mode 

	//Set PP
	//REG_WRITE_U32(REG_READ_BY_PP, NF_READ_BY_PP_read_by_pp(0)); //Data read to 	DRAM from NAND through PP		
	//REG_WRITE_U32(REG_PP_CTL0, NF_PP_CTL0_pp_start_addr(0x0) | NF_PP_CTL0_pp_reset(0x0) | NF_PP_CTL0_pp_enable(0x1));	//Set PP starting address[9:8], PP reset and PP enable
	//REG_WRITE_U32(REG_PP_CTL1, 0x0);	//Set PP starting assdress[7:0]

	//Set command
	REG_WRITE_U32(REG_ND_CMD, NF_ND_CMD_cmd(0x55));	//Set CMD1
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0x0) | NF_ND_CTL_tran_mode(0x0));	//Enable Xfer, eanble ECC and set transfer mode 
	WAIT_DONE(REG_ND_CTL, 0x80, 0x00);	//Wait xfer done

	//Set address, 
	REG_WRITE_U32(REG_ND_PA0, i);	//Set PA[7:0]
	REG_WRITE_U32(REG_ND_PA2, NF_ND_PA2_addr_mode(0x7));	//Set address mode & PA[20:16]		
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0x0) | NF_ND_CTL_tran_mode(0x1));	//Enable Xfer, eanble ECC and set transfer mode 
	WAIT_DONE(REG_ND_CTL, 0x80, 0x00);	//Wait xfer done
	
	//Reset PP
	REG_WRITE_U32(REG_READ_BY_PP, NF_READ_BY_PP_read_by_pp(0)); //Data read to 	DRAM from NAND through PP		
	REG_WRITE_U32(REG_PP_CTL0, NF_PP_CTL0_pp_start_addr(0x0) | NF_PP_CTL0_pp_reset(0x1) | NF_PP_CTL0_pp_enable(0x0));	//Set PP starting address[9:8], PP reset and PP enable

	//Set data
	REG_WRITE_U32(REG_SRAM_CTL,NF_SRAM_CTL_map_sel(1)|NF_SRAM_CTL_access_en(0x1) | NF_SRAM_CTL_mem_region(0x0));	//Enable direct access SRAM
	REG_WRITE_U32(REG_ND_PA0, P1);	//Set data
	REG_WRITE_U32(REG_SRAM_CTL, NF_SRAM_CTL_access_en(0x0));	//Disable direct access SRAM
	//Set PP
	REG_WRITE_U32(REG_DATA_TL0, 0x1);	//Set data transfer count[7:0]
	REG_WRITE_U32(REG_DATA_TL1, NF_DATA_TL1_access_mode(0x1) | NF_DATA_TL1_length1(0x0));	//Set data transfer count[13:8], SRAM path and access mode 
	REG_WRITE_U32(REG_PP_CTL0, NF_PP_CTL0_pp_start_addr(0x0) | NF_PP_CTL0_pp_reset(0) | NF_PP_CTL0_pp_enable(1));	//Set PP starting address[9:8], PP reset and PP enable
	//REG_WRITE_U32(REG_PP_CTL0, NF_PP_CTL0_pp_start_addr(0x0));				//Set PP starting address[9:8]
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x3));	//Enable Xfer, eanble ECC and set transfer mode 	
	WAIT_DONE(REG_ND_CTL, 0xc0, 0x40);	//Wait xfer done
        }

        printk("[%s] close slow timer, cnt=0x%x\n", __FUNCTION__, P1);

	REG_WRITE_U32(0x18000038, 0x4);		//432/(N+1)	
	REG_WRITE_U32(REG_TIME_PARA3,  NF_TIME_PARA3_T3(0x0));			//Set flash timming T3	
	REG_WRITE_U32(REG_TIME_PARA2,  NF_TIME_PARA2_T2(0x0));			//Set flash timming T2	
	REG_WRITE_U32(REG_TIME_PARA1,  NF_TIME_PARA1_T1(0x0));			//Set flash timming T1
    
}	

//----------------------------------------------------------------------------
// add read-retry for TOSHIBA
void rtk_set_feature_toshiba_new(int P1){

        int i = 0;

	printk("[%s] set slow timer, cnt=0x%x\n", __FUNCTION__, P1);

	REG_WRITE_U32(0x18000038, 0xf);		//432/(N+1)	
	REG_WRITE_U32(REG_TIME_PARA3,  NF_TIME_PARA3_T3(0x1));			//Set flash timming T3	
	REG_WRITE_U32(REG_TIME_PARA2,  NF_TIME_PARA2_T2(0x1));			//Set flash timming T2	
	REG_WRITE_U32(REG_TIME_PARA1,  NF_TIME_PARA1_T1(0x1));			//Set flash timming T1

    for(i=4;i<9;i++){
        printk("[%s] enter set REG_DATA_TL0 to 0x1, addr=0x%x, data: 0x%x\n", __FUNCTION__, i,read_retry_toshiba_cnt_new[P1][i-4]);
	//REG_WRITE_U32(REG_DATA_TL0, 0x1);	//Set data transfer count[7:0]
	//REG_WRITE_U32(REG_DATA_TL1, NF_DATA_TL1_access_mode(0x1) | NF_DATA_TL1_length1(0x0));	//Set data transfer count[13:8], SRAM path and access mode 

	//Set PP
	//REG_WRITE_U32(REG_READ_BY_PP, NF_READ_BY_PP_read_by_pp(0)); //Data read to 	DRAM from NAND through PP		
	//REG_WRITE_U32(REG_PP_CTL0, NF_PP_CTL0_pp_start_addr(0x0) | NF_PP_CTL0_pp_reset(0x0) | NF_PP_CTL0_pp_enable(0x1));	//Set PP starting address[9:8], PP reset and PP enable
	//REG_WRITE_U32(REG_PP_CTL1, 0x0);	//Set PP starting assdress[7:0]

	//Set command
	REG_WRITE_U32(REG_ND_CMD, NF_ND_CMD_cmd(0x55));	//Set CMD1
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0x0) | NF_ND_CTL_tran_mode(0x0));	//Enable Xfer, eanble ECC and set transfer mode 
	WAIT_DONE(REG_ND_CTL, 0x80, 0x00);	//Wait xfer done

	//Set address, 

        if(i==8)
            REG_WRITE_U32(REG_ND_PA0, 0x0d);	//Set PA[7:0]
        else
	    REG_WRITE_U32(REG_ND_PA0, i);	//Set PA[7:0]
	REG_WRITE_U32(REG_ND_PA2, NF_ND_PA2_addr_mode(0x7));	//Set address mode & PA[20:16]		
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0x0) | NF_ND_CTL_tran_mode(0x1));	//Enable Xfer, eanble ECC and set transfer mode 
	WAIT_DONE(REG_ND_CTL, 0x80, 0x00);	//Wait xfer done
	
	//Reset PP
	REG_WRITE_U32(REG_READ_BY_PP, NF_READ_BY_PP_read_by_pp(0)); //Data read to 	DRAM from NAND through PP		
	REG_WRITE_U32(REG_PP_CTL0, NF_PP_CTL0_pp_start_addr(0x0) | NF_PP_CTL0_pp_reset(0x1) | NF_PP_CTL0_pp_enable(0x0));	//Set PP starting address[9:8], PP reset and PP enable

	//Set data
	REG_WRITE_U32(REG_SRAM_CTL,NF_SRAM_CTL_map_sel(1)|NF_SRAM_CTL_access_en(0x1) | NF_SRAM_CTL_mem_region(0x0));	//Enable direct access SRAM
	REG_WRITE_U32(REG_ND_PA0, read_retry_toshiba_cnt_new[P1][i-4]);	//Set data
	REG_WRITE_U32(REG_SRAM_CTL, NF_SRAM_CTL_access_en(0x0));	//Disable direct access SRAM
	//Set PP
	REG_WRITE_U32(REG_DATA_TL0, 0x1);	//Set data transfer count[7:0]
	REG_WRITE_U32(REG_DATA_TL1, NF_DATA_TL1_access_mode(0x1) | NF_DATA_TL1_length1(0x0));	//Set data transfer count[13:8], SRAM path and access mode 
	REG_WRITE_U32(REG_PP_CTL0, NF_PP_CTL0_pp_start_addr(0x0) | NF_PP_CTL0_pp_reset(0) | NF_PP_CTL0_pp_enable(1));	//Set PP starting address[9:8], PP reset and PP enable
	//REG_WRITE_U32(REG_PP_CTL0, NF_PP_CTL0_pp_start_addr(0x0));				//Set PP starting address[9:8]
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x3));	//Enable Xfer, eanble ECC and set transfer mode 	
	WAIT_DONE(REG_ND_CTL, 0xc0, 0x40);	//Wait xfer done
        }

        printk("[%s] close slow timer, cnt=0x%x\n", __FUNCTION__, P1);

	REG_WRITE_U32(0x18000038, 0x4);		//432/(N+1)	
	REG_WRITE_U32(REG_TIME_PARA3,  NF_TIME_PARA3_T3(0x0));			//Set flash timming T3	
	REG_WRITE_U32(REG_TIME_PARA2,  NF_TIME_PARA2_T2(0x0));			//Set flash timming T2	
	REG_WRITE_U32(REG_TIME_PARA1,  NF_TIME_PARA1_T1(0x0));			//Set flash timming T1

        if(P1==4){
        	printk("[%s] enter 4th retry send 0xb3 command\n", __FUNCTION__);

        	//Set command
        	REG_WRITE_U32(REG_ND_CMD, NF_ND_CMD_cmd(0xb3));	//Set CMD1
        	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0x0) | NF_ND_CTL_tran_mode(0x0));	//Enable Xfer, eanble ECC and set transfer mode 
        	WAIT_DONE(REG_ND_CTL, 0x80, 0x00);	//Wait xfer done
        }
    
}	

//----------------------------------------------------------------------------
// add read-retry for Micron
void rtk_set_feature_micron(int P1){

	printk("[%s] enter \n", __FUNCTION__);
	
	REG_WRITE_U32(REG_DATA_TL0, 0x4);	//Set data transfer count[7:0]
	REG_WRITE_U32(REG_DATA_TL1, NF_DATA_TL1_access_mode(0x1) | NF_DATA_TL1_length1(0x0));	//Set data transfer count[13:8], SRAM path and access mode 

	//Set PP
	REG_WRITE_U32(REG_READ_BY_PP, NF_READ_BY_PP_read_by_pp(0)); //Data read to 	DRAM from NAND through PP		
	REG_WRITE_U32(REG_PP_CTL0, NF_PP_CTL0_pp_start_addr(0x0) | NF_PP_CTL0_pp_reset(0x0) | NF_PP_CTL0_pp_enable(0x1));	//Set PP starting address[9:8], PP reset and PP enable
	REG_WRITE_U32(REG_PP_CTL1, 0x0);	//Set PP starting assdress[7:0]

	//Set command
	REG_WRITE_U32(REG_ND_CMD, NF_ND_CMD_cmd(0xef));	//Set CMD1
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0x0) | NF_ND_CTL_tran_mode(0x0));	//Enable Xfer, eanble ECC and set transfer mode 
	WAIT_DONE(REG_ND_CTL, 0x80, 0x00);	//Wait xfer done

	//Set address, 
	REG_WRITE_U32(REG_ND_PA0, 0x89);	//Set PA[7:0]
	REG_WRITE_U32(REG_ND_PA2, NF_ND_PA2_addr_mode(0x7));	//Set address mode & PA[20:16]		
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0x0) | NF_ND_CTL_tran_mode(0x1));	//Enable Xfer, eanble ECC and set transfer mode 
	WAIT_DONE(REG_ND_CTL, 0x80, 0x00);	//Wait xfer done
	
	//Reset PP
	REG_WRITE_U32(REG_READ_BY_PP, NF_READ_BY_PP_read_by_pp(0)); //Data read to 	DRAM from NAND through PP		
	REG_WRITE_U32(REG_PP_CTL0, NF_PP_CTL0_pp_start_addr(0x0) | NF_PP_CTL0_pp_reset(0x1) | NF_PP_CTL0_pp_enable(0x0));	//Set PP starting address[9:8], PP reset and PP enable

	//Set data
	REG_WRITE_U32(REG_SRAM_CTL,NF_SRAM_CTL_map_sel(1)|NF_SRAM_CTL_access_en(0x1) | NF_SRAM_CTL_mem_region(0x0));	//Enable direct access SRAM
	REG_WRITE_U32(REG_ND_PA0, P1);	//Set data
	REG_WRITE_U32(REG_SRAM_CTL, NF_SRAM_CTL_access_en(0x0));	//Disable direct access SRAM
	//Set PP
	REG_WRITE_U32(REG_PP_CTL0, NF_PP_CTL0_pp_start_addr(0x0) | NF_PP_CTL0_pp_reset(0) | NF_PP_CTL0_pp_enable(1));	//Set PP starting address[9:8], PP reset and PP enable
	REG_WRITE_U32(REG_PP_CTL0, NF_PP_CTL0_pp_start_addr(0x0));				//Set PP starting address[9:8]
	REG_WRITE_U32(REG_ND_CTL, NF_ND_CTL_xfer(1) | NF_ND_CTL_ecc_enable(0) | NF_ND_CTL_tran_mode(0x3));	//Enable Xfer, eanble ECC and set transfer mode 	
	WAIT_DONE(REG_ND_CTL, 0xc0, 0x40);	//Wait xfer done
}	

//----------------------------------------------------------------------------


static int rtk_erase_block(struct mtd_info *mtd, u16 chipnr, int page)
{
	//struct nand_chip *this = NULL;
	page_size = mtd->writesize;
	oob_size = mtd->oobsize;
	ppb = mtd->erasesize/mtd->writesize;

	//this = (struct nand_chip *) mtd->priv;
//	printk("AT[%s]:page %d, ppb %d, mtd->erasesize %u, mtd->writesize %u\n",__FUNCTION__,page,ppb,mtd->erasesize,mtd->writesize);
	if ( page & (ppb-1) ){
		printk("%s: page %d is not block alignment !!\n", __FUNCTION__, page);
		//up (&sem_NF_CARDREADER);
		return -1;
	}

#if RTK_NAND_INTERRUPT
	g_nfFlag = NF_ERASE_TRIGGER;
	NF_RESET_IRQ;
#endif

	//REG_WRITE_U32(0x01,0xb801032c);	//Enable NAND/CardReader arbitrator add by alexchang 0303-2010
	REG_WRITE_U32( REG_MULTI_CHNL_MODE,NF_MULTI_CHNL_MODE_no_wait_busy(1)|NF_MULTI_CHNL_MODE_edo(1));

	REG_WRITE_U32( REG_ND_CMD,NF_ND_CMD_cmd(CMD_BLK_ERASE_C1) );
	REG_WRITE_U32( REG_CMD2,NF_CMD2_cmd2(CMD_BLK_ERASE_C2) );
	REG_WRITE_U32( REG_CMD3,NF_CMD3_cmd3(CMD_BLK_ERASE_C3) );

	REG_WRITE_U32( REG_ND_PA0,NF_ND_PA0_page_addr0(page) );
	REG_WRITE_U32( REG_ND_PA1,NF_ND_PA1_page_addr1(page>>8) );
	REG_WRITE_U32( REG_ND_PA2,NF_ND_PA2_addr_mode(0x04)|NF_ND_PA2_page_addr2(page>>16) );
	REG_WRITE_U32( REG_ND_PA3,NF_ND_PA3_page_addr3((page>> 21)&0x7) );

	REG_WRITE_U32( REG_AUTO_TRIG,NF_AUTO_TRIG_auto_trig(1)|NF_AUTO_TRIG_spec_auto_case(1)|NF_AUTO_TRIG_auto_case(2) );
	WAIT_DONE(REG_AUTO_TRIG,0x80,0);

#if RTK_NAND_INTERRUPT
	NF_RESET_IRQ;
	NF_ENABLE_IRQ(NF_POLL_IRQ_MASK);
	g_nfFlag = NF_ERASE_TRIGGER;
	REG_WRITE_U32(REG_POLL_FSTS,NF_POLL_FSTS_bit_sel(6)|NF_POLL_FSTS_trig_poll(1) );
	RTK_WAIT_EVENT;
	NF_RESET_IRQ;
	NF_ENABLE_IRQ(NF_IRQ_MASK);
#else
	REG_WRITE_U32(REG_POLL_FSTS,NF_POLL_FSTS_bit_sel(6)|NF_POLL_FSTS_trig_poll(1) );
	WAIT_DONE(REG_POLL_FSTS,0x01,0x0);
	WAIT_DONE(REG_ND_CTL,0x40,0x40);//add by alexchang 0416-2010
#endif

	if ( REG_READ_U32(REG_ND_DAT) & 0x01 ){
		//up (&sem_NF_CARDREADER);
		printk("[%s] erasure is not completed at block %d\n", __FUNCTION__, page/ppb);
		if ( chipnr == 0 && page >= 0 && page < g_BootcodeSize/page_size )
			return 0;
		else
			return -1;
	}

	//printk("[AT]Erase block : %u  \n",page/ppb);
	//up (&sem_NF_CARDREADER);
#if RTK_ARD_ALGORITHM
	g_RecArray[page/ppb]=0;
//	printk("[AT]Erase block : %u  \n",page/ppb);
#endif
	return 0;
}
//----------------------------------------------------------------------------
unsigned char *malloc_aligned(size_t size,phys_addr_t alignment)
{
   unsigned char *ptr = kmalloc(size + alignment-1,GFP_KERNEL);
   if (!ptr) return NULL;
   ptr = (unsigned char *)(((phys_addr_t)(ptr) + alignment-1) & ~alignment);
   return ptr;
}
//----------------------------------------------------------------------------

static int rtk_read_oob (struct mtd_info *mtd, u16 chipnr, int page, int len, u_char *oob_buf)
{
	struct nand_chip *this = (struct nand_chip *) mtd->priv;
	int rc = 0;
	int dram_sa, dma_len, spare_dram_sa;
	int page_len;
	uint8_t auto_trigger_mode = 2;
	uint8_t addr_mode = 1;
	uint8_t	bChkAllOne = 0;
	
	page_size = mtd->writesize;
	oob_size = mtd->oobsize;
	ppb = mtd->erasesize/mtd->writesize;

	if ( len>oob_size || !oob_buf ){
		printk("[%s] error: len>oob_size OR oob_buf is NULL\n", __FUNCTION__);
		//up (&sem_NF_CARDREADER);
		return -1;
	}

	while (1)
	{
		REG_WRITE_U32(REG_DATA_TL0,NF_DATA_TL0_length0(0));
		if(this->ecc_select >= 0x18)
		{
			if (bChkAllOne) {
				// enable randomizer
				REG_WRITE_U32(REG_RMZ_CTRL, 0);
				REG_WRITE_U32(REG_BLANK_CHK,NF_BLANK_CHK_read_ecc_xnor_ena(1));
			}
			else {
				// enable randomizer
				REG_WRITE_U32(REG_RMZ_CTRL, 1);
				REG_WRITE_U32(REG_BLANK_CHK,NF_BLANK_CHK_read_ecc_xnor_ena(0));
			}
			page_len = page_size >> 10;
			REG_WRITE_U32(REG_DATA_TL1,NF_DATA_TL1_access_mode(1)|NF_DATA_TL1_length1(4));
		}
		else
		{
			// set random read			
			REG_WRITE_U32(REG_RND_EN, 1);
			REG_WRITE_U32(REG_RND_CMD1, 0x5);
			REG_WRITE_U32(REG_RND_CMD2, 0xe0);
			REG_WRITE_U32(REG_RND_DATA_STR_COL_H, 0);	// data start address MSB (always 0)
			REG_WRITE_U32(REG_RND_SPR_STR_COL_H, page_size >> 8);	// spare start address MSB
			REG_WRITE_U32(REG_RND_SPR_STR_COL_L, page_size & 0xff);	// spare start address LSB
		
			page_len = page_size >> 9;
			REG_WRITE_U32(REG_DATA_TL1,NF_DATA_TL1_access_mode(1)|NF_DATA_TL1_length1(2));
		}
		
		REG_WRITE_U32(REG_PAGE_LEN,NF_PAGE_LEN_page_len(page_len));

		//Set PP
		REG_WRITE_U32(REG_READ_BY_PP,NF_READ_BY_PP_read_by_pp(1));
		REG_WRITE_U32(REG_PP_CTL1,NF_PP_CTL1_pp_start_addr(0));
		REG_WRITE_U32(REG_PP_CTL0,0);

		// enable blank check
		REG_WRITE_U32(REG_BLANK_CHK,NF_BLANK_CHK_blank_ena(1) );

		//Set command
		REG_WRITE_U32(REG_ND_CMD,NF_ND_CMD_cmd(CMD_PG_READ_C1));
		REG_WRITE_U32(REG_CMD2,NF_CMD2_cmd2(CMD_PG_READ_C2));
		REG_WRITE_U32(REG_CMD3,NF_CMD3_cmd3(CMD_PG_READ_C3));
		
		//Set address
		REG_WRITE_U32( REG_ND_PA0,NF_ND_PA0_page_addr0( 0xff&page ));
		REG_WRITE_U32( REG_ND_PA1,NF_ND_PA1_page_addr1( 0xff&(page>>8) ));
		REG_WRITE_U32( REG_ND_PA2,NF_ND_PA2_addr_mode(addr_mode)|NF_ND_PA2_page_addr2( 0x1f&(page>>16) ));
		REG_WRITE_U32( REG_ND_PA3,NF_ND_PA3_page_addr3( 0x7&(page>>21) ));

		REG_WRITE_U32(REG_ND_CA0, 0);
		REG_WRITE_U32(REG_ND_CA1, 0);

		//Set ECC
		REG_WRITE_U32( REG_MULTI_CHNL_MODE,NF_MULTI_CHNL_MODE_edo(1));//add by alexchang0205-2010
		REG_WRITE_U32( REG_ECC_STOP,NF_ECC_STOP_ecc_n_stop(0x01));

		switch(this->ecc_select) {
			case 6:
				REG_WRITE_U32(REG_ECC_SEL, 0x0);
				break;
			case 12:
				REG_WRITE_U32(REG_ECC_SEL, 0x1);
				break;
			case 16:
				REG_WRITE_U32(REG_ECC_SEL, 0xe);
				break;
			case 24:
				REG_WRITE_U32(REG_ECC_SEL, 0xa);
				break;
			case 40:
				REG_WRITE_U32(REG_ECC_SEL, 0x2);
				break;
			case 43:
				REG_WRITE_U32(REG_ECC_SEL, 0x4);
				break;
			case 65:
				REG_WRITE_U32(REG_ECC_SEL, 0x6);
				break;
			case 72:
				REG_WRITE_U32(REG_ECC_SEL, 0x8);
				break;
			default:
				REG_WRITE_U32(REG_ECC_SEL, 0x0);
				break;
		}

		dram_sa = ( (phys_addr_t)this->ops.datbuf >> 3);
		REG_WRITE_U32(REG_DMA_CTL1,NF_DMA_CTL1_dram_sa(dram_sa));
		dma_len = page_size >> 9;
		REG_WRITE_U32(REG_DMA_CTL2,NF_DMA_CTL2_dma_len(dma_len));

		spare_dram_sa = ( (phys_addr_t)oob_buf >> 3);
		REG_WRITE_U32( REG_SPR_DDR_CTL,NF_SPR_DDR_CTL_spare_ddr_ena(1)|NF_SPR_DDR_CTL_per_2k_spr_ena(0)|NF_SPR_DDR_CTL_spare_dram_sa(spare_dram_sa));

		// flush cache.
		RTK_FLUSH_CACHE(oob_buf, oob_size);

		REG_WRITE_U32(REG_DMA_CTL3,NF_DMA_CTL3_ddr_wr(1)|NF_DMA_CTL3_dma_xfer(1));
		REG_WRITE_U32( REG_AUTO_TRIG,NF_AUTO_TRIG_auto_trig(1)|NF_AUTO_TRIG_spec_auto_case(0)| NF_AUTO_TRIG_auto_case(auto_trigger_mode));
		WAIT_DONE(REG_AUTO_TRIG,0x80,0);

		WAIT_DONE(REG_AUTO_TRIG,0x80,0);
		WAIT_DONE(REG_DMA_CTL3,0x01,0);

		if(oob_buf)	{
			REG_WRITE_U32(REG_READ_BY_PP,0x00);
			REG_WRITE_U32(REG_SRAM_CTL, 0x30 | 0x04);
			rtk_read_oob_from_SRAM(mtd, oob_buf);
			REG_WRITE_U32(REG_SRAM_CTL, 0x00);
			REG_WRITE_U32(REG_READ_BY_PP,0x80);
		}

		// return OK if all data bit is 1 (page is not written yet)
		if (REG_READ_U32(REG_BLANK_CHK) & 0x2){
			//printk("[%s] page(0x%x) data all one\n", __FUNCTION__, page);
			return 0;
		}
		else if (REG_READ_U32(REG_ND_ECC) & 0x8) {
			if (!bChkAllOne && this->ecc_select>=0x18) {
				bChkAllOne = 1;
				continue;
			}
			printk("[%s] page(0x%x) ecc error\n", __FUNCTION__, page);
			return -1;	// ECC not correctable
		}
		else {
			//printk("[%s] page(0x%x) oob= 0x%x\n", __FUNCTION__, page, *oob_buf);
			return 0;
		}
	}
	return rc;
}
//----------------------------------------------------------------------------
static int rtk_read_ecc_page (struct mtd_info *mtd, u16 chipnr, unsigned int page, u_char *data_buf, struct mtd_oob_ops *ops, u16 cp_mode, u16 cp_first, size_t cp_len)
{
//static unsigned int eccReadCnt = 0;
	struct nand_chip *this = NULL;
	int rc = 0;
	int dram_sa, dma_len, spare_dram_sa;
	int page_len;

	uint8_t	auto_trigger_mode = 2;
	uint8_t	addr_mode = 1;
	uint8_t	bChkAllOne = 0;
	uint8_t read_retry_cnt = 0;
	uint8_t max_read_retry_cnt = 0;

        volatile unsigned int data;
	u_char *oob_buf = NULL;
	this = (struct nand_chip *) mtd->priv;
	page_size = mtd->writesize;
	ppb = mtd->erasesize/mtd->writesize;


        unsigned char ks[16];
        unsigned char kh[16];
        unsigned char dest[16];
        unsigned int *intPTR;

	if(ops){
		oob_buf = &ops->oobbuf[ops->oobretlen];
		oob_size = ops->ooblen;
	}
	else
	oob_size = mtd->oobsize;

    if (((phys_addr_t)data_buf&0x7)!=0) {
            printk("[%s]data_buf must 8 byte alignmemt!!\n",__FUNCTION__);
            BUG();
    }

	if (g_enReadRetrial) {
		switch(g_id_chain)
		{
			case 0x4b44642c:
				max_read_retry_cnt = 7;
				break;
			case 0x4b44442c:
				max_read_retry_cnt = 7;
				break;
			case 0x9384d798:
                                max_read_retry_cnt = 6;
				break;
                       case 0x9384de98:
                                max_read_retry_cnt = 6;
				break;
                       case 0x9394de98:
                                max_read_retry_cnt = 7;
				break;            
			default:
				break;
				
		}
	}

	while (1) 
	{                   
			if (g_enReadRetrial) {
				if (read_retry_cnt !=0) {   //set extra feature before retry read page. ex. toshiba 0x26&0x5D
					switch(g_id_chain)
					{
						case 0x9384d798:
							printk("TC58TEG5DCJT read-retrial rtk_set_ext_feature_toshiba ...read_retry_cnt: %d\n", read_retry_cnt);
                                                        rtk_set_ext_feature_toshiba();
							break;
                            			case 0x9384de98:
							printk("TC58TEG6DCJT read-retrial rtk_set_ext_feature_toshiba ...read_retry_cnt: %d\n", read_retry_cnt);
                                                        rtk_set_ext_feature_toshiba();
							break;
                                                case 0x9394de98:
							printk("TC58TEG6DDK read-retrial rtk_set_ext_feature_toshiba ...read_retry_cnt: %d\n", read_retry_cnt);
                                                        rtk_set_ext_feature_toshiba();
							break;
						default:
							break;
							
					}
				}
			}
    
		REG_WRITE_U32(REG_DATA_TL0,NF_DATA_TL0_length0(0));
		if(this->ecc_select >= 0x18)
		{
			if (bChkAllOne) {
				// enable randomizer
				REG_WRITE_U32(REG_RMZ_CTRL, 0);
				REG_WRITE_U32(REG_BLANK_CHK,NF_BLANK_CHK_blank_ena(1)|NF_BLANK_CHK_read_ecc_xnor_ena(1));
                                //printk("[DBG]ecc error, set xnor and blank to 1, REG_BLANK_CHK reg: 0x%x\n", REG_READ_U32(REG_BLANK_CHK));
			}
			else {
				// enable randomizer
				REG_WRITE_U32(REG_RMZ_CTRL, 1);
				REG_WRITE_U32(REG_BLANK_CHK,NF_BLANK_CHK_blank_ena(1)|NF_BLANK_CHK_read_ecc_xnor_ena(0));
                                //printk("[DBG]set xnor to 0, REG_BLANK_CHK reg: 0x%x\n", REG_READ_U32(REG_BLANK_CHK));
			}
			
			page_len = page_size >> 10;
			REG_WRITE_U32(REG_DATA_TL1,NF_DATA_TL1_access_mode(1)|NF_DATA_TL1_length1(4));
		}
		else
		{
			// set random read
			REG_WRITE_U32(REG_RND_EN, 1);
			REG_WRITE_U32(REG_RND_CMD1, 0x5);
			REG_WRITE_U32(REG_RND_CMD2, 0xe0);
			REG_WRITE_U32(REG_RND_DATA_STR_COL_H, 0);	// data start address MSB (always 0)
			REG_WRITE_U32(REG_RND_SPR_STR_COL_H, page_size >> 8);	// spare start address MSB
			REG_WRITE_U32(REG_RND_SPR_STR_COL_L, page_size & 0xff);	// spare start address LSB
			
			page_len = page_size >> 9;
			REG_WRITE_U32(REG_DATA_TL1,NF_DATA_TL1_access_mode(1)|NF_DATA_TL1_length1(2));
		}
		
		REG_WRITE_U32(REG_PAGE_LEN,NF_PAGE_LEN_page_len(page_len));

		//Set PP
		REG_WRITE_U32(REG_READ_BY_PP,NF_READ_BY_PP_read_by_pp(1));
		REG_WRITE_U32(REG_PP_CTL1,NF_PP_CTL1_pp_start_addr(0));
		REG_WRITE_U32(REG_PP_CTL0,0);

		// enable blank check
		//REG_WRITE_U32(REG_BLANK_CHK,NF_BLANK_CHK_blank_ena(1) );


                if(cp_mode == CP_NF_AES_ECB_128||(cp_mode==CP_NF_AES_CBC_128 && cp_first==1)){
#ifdef CONFIG_NAND_ON_THE_FLY_TEST_KEY

                    if(cp_mode==CP_NF_AES_CBC_128){
            		    REG_WRITE_U32(CP_NF_INI_KEY_0,0x0);
			    REG_WRITE_U32(CP_NF_INI_KEY_1,0x0);
			    REG_WRITE_U32(CP_NF_INI_KEY_2,0x0);
			    REG_WRITE_U32(CP_NF_INI_KEY_3,0x0);
			}

			REG_WRITE_U32(CP_NF_KEY_0,0xad0d8175);
			REG_WRITE_U32(CP_NF_KEY_1,0xa0d732c0);
			REG_WRITE_U32(CP_NF_KEY_2,0xe56ef350);
			REG_WRITE_U32(CP_NF_KEY_3,0xc53ce48b);
        	        // set CP register.

                        if(cp_mode == CP_NF_AES_ECB_128){
        	                REG_WRITE_U32(CP_NF_SET, 0x200);				// sel=0, cw_entry=0, bcm=1, aes_mode=0. Its ECB mode.
                        }
                        else{
                                REG_WRITE_U32(CP_NF_SET, 0x0);				// sel=0, cw_entry=0, bcm=0, aes_mode=0. Its CBC mode.
                        }       
            
#else
        	        // set CP register.

                        if(cp_mode == CP_NF_AES_ECB_128){
        	                //REG_WRITE_U32(CP_NF_SET, 0x200);				// sel=0, cw_entry=0, bcm=1, aes_mode=0. Its ECB mode.
                                    if (!OTP_JUDGE_BIT(OTP_BIT_SECUREBOOT)) 
                                      REG_WRITE_U32(CP_NF_SET, 0x202); // key from kn
                                    else if (OTP_JUDGE_BIT(OTP_BIT_SECUREBOOT)){

#ifdef CONFIG_CMD_KEY_BURNING
                                        OTP_Get_Byte(OTP_K_S, ks, 16);
                                        OTP_Get_Byte(OTP_K_H, kh, 16);
#endif
                                        AES_ECB_encrypt(ks, 16, dest, (unsigned int*)kh);

					intPTR = (unsigned int*)dest;
					intPTR[0] = swap_endian(intPTR[0]);
					intPTR[1] = swap_endian(intPTR[1]);
					intPTR[2] = swap_endian(intPTR[2]);
					intPTR[3] = swap_endian(intPTR[3]);

                                        writeNFKey((unsigned int*)dest);

                                        memset(ks, 0, 16);
                                        memset(kh, 0, 16);
                                        memset(dest, 0, 16);

                                        REG_WRITE_U32(CP_NF_SET, 0x200);				// sel=0, cw_entry=0, bcm=1, aes_mode=0. Its ECB mode.
                                      //REG_WRITE_U32(CP_NF_SET, 0x2202); // key from kh

                                    }
                        }
                        else{
                                //REG_WRITE_U32(CP_NF_SET, 0x0);				// sel=0, cw_entry=0, bcm=0, aes_mode=0. Its CBC mode.
                                    if (!OTP_JUDGE_BIT(OTP_BIT_SECUREBOOT)) 
                                      REG_WRITE_U32(CP_NF_SET, 0x002); // key from kn
                                    else if (OTP_JUDGE_BIT(OTP_BIT_SECUREBOOT)){

                            		REG_WRITE_U32(CP_NF_INI_KEY_0,0x0);
                			REG_WRITE_U32(CP_NF_INI_KEY_1,0x0);
                			REG_WRITE_U32(CP_NF_INI_KEY_2,0x0);
                			REG_WRITE_U32(CP_NF_INI_KEY_3,0x0);

#ifdef CONFIG_CMD_KEY_BURNING
                                        OTP_Get_Byte(OTP_K_S, ks, 16);
                                        OTP_Get_Byte(OTP_K_H, kh, 16);
#endif
                                        AES_ECB_encrypt(ks, 16, dest, (unsigned int*)kh);
					
					intPTR = (unsigned int*)dest;
					intPTR[0] = swap_endian(intPTR[0]);
					intPTR[1] = swap_endian(intPTR[1]);
					intPTR[2] = swap_endian(intPTR[2]);
					intPTR[3] = swap_endian(intPTR[3]);

                                        writeNFKey((unsigned int*)dest);

                                        memset(ks, 0, 16);
                                        memset(kh, 0, 16);
                                        memset(dest, 0, 16);

                                        REG_WRITE_U32(CP_NF_SET, 0x0);				// sel=0, cw_entry=0, bcm=0, aes_mode=0. Its CBC mode.
                                      //REG_WRITE_U32(CP_NF_SET, 0x2002); // key from kh

                                    }

                        }        
#endif                          
                        //printk("[DBG]set cp mode...............cp_len: 0x%x\n", cp_len);

                        if(cp_mode == CP_NF_AES_CBC_128 )
                            REG_WRITE_U32(REG_CP_LEN, (cp_len / 0x200) << 9);		// integer multiple of dma_len.
                        else
                            REG_WRITE_U32(REG_CP_LEN, (page_size / 0x200) << 9);		// integer multiple of dma_len.
                            
                        syncPageRead();
                        //printk("[DBG]set cp mode...............REG_READ_U32(REG_CP_LEN): 0x%x\n", REG_READ_U32(REG_CP_LEN));
                }

		//Set command
		REG_WRITE_U32(REG_ND_CMD,NF_ND_CMD_cmd(CMD_PG_READ_C1));
		REG_WRITE_U32(REG_CMD2,NF_CMD2_cmd2(CMD_PG_READ_C2));
		REG_WRITE_U32(REG_CMD3,NF_CMD3_cmd3(CMD_PG_READ_C3));
		
		//Set address
		REG_WRITE_U32( REG_ND_PA0,NF_ND_PA0_page_addr0( 0xff&page ));
		REG_WRITE_U32( REG_ND_PA1,NF_ND_PA1_page_addr1( 0xff&(page>>8) ));
		REG_WRITE_U32( REG_ND_PA2,NF_ND_PA2_addr_mode(addr_mode)|NF_ND_PA2_page_addr2( 0x1f&(page>>16) ));
		REG_WRITE_U32( REG_ND_PA3,NF_ND_PA3_page_addr3( 0x7&(page>>21) ));

		REG_WRITE_U32(REG_ND_CA0, 0);
		REG_WRITE_U32(REG_ND_CA1, 0);

		//Set ECC
		REG_WRITE_U32( REG_MULTI_CHNL_MODE,NF_MULTI_CHNL_MODE_edo(1));//add by alexchang0205-2010
		REG_WRITE_U32( REG_ECC_STOP,NF_ECC_STOP_ecc_n_stop(0x01));

		switch(this->ecc_select) {
			case 6:
				REG_WRITE_U32(REG_ECC_SEL, 0x0);
				break;
			case 12:
				REG_WRITE_U32(REG_ECC_SEL, 0x1);
				break;
			case 16:
				REG_WRITE_U32(REG_ECC_SEL, 0xe);
				break;
			case 24:
				REG_WRITE_U32(REG_ECC_SEL, 0xa);
				break;
			case 40:
				REG_WRITE_U32(REG_ECC_SEL, 0x2);
				break;
			case 43:
				REG_WRITE_U32(REG_ECC_SEL, 0x4);
				break;
			case 65:
				REG_WRITE_U32(REG_ECC_SEL, 0x6);
				break;
			case 72:
				REG_WRITE_U32(REG_ECC_SEL, 0x8);
				break;
			default:
				REG_WRITE_U32(REG_ECC_SEL, 0x0);
				break;
		}

		if (oob_buf) {
			spare_dram_sa = ( (phys_addr_t)oob_buf >> 3);
		}
		else {
			spare_dram_sa = ( (phys_addr_t)this->ops.oobbuf >> 3);
		}

		REG_WRITE_U32( REG_SPR_DDR_CTL,NF_SPR_DDR_CTL_spare_ddr_ena(1)|NF_SPR_DDR_CTL_per_2k_spr_ena(0)|NF_SPR_DDR_CTL_spare_dram_sa(spare_dram_sa));



		dram_sa = ( (phys_addr_t)data_buf >> 3);
		REG_WRITE_U32(REG_DMA_CTL1,NF_DMA_CTL1_dram_sa(dram_sa));
		dma_len = page_size >> 9;
		REG_WRITE_U32(REG_DMA_CTL2,NF_DMA_CTL2_dma_len(dma_len));
		//REG_WRITE_U32(REG_DMA_CTL3,NF_DMA_CTL3_ddr_wr(1)|NF_DMA_CTL3_dma_xfer(1));

                if(cp_mode==CP_NF_AES_CBC_128){
                    if(cp_first == 1)
                        REG_WRITE_U32(REG_DMA_CTL3,NF_DMA_CTL3_cp_enable(1)|NF_DMA_CTL3_cp_first(1)|NF_DMA_CTL3_ddr_wr(1)|NF_DMA_CTL3_dma_xfer(1));
                    else
		        REG_WRITE_U32(REG_DMA_CTL3,NF_DMA_CTL3_cp_enable(1)|NF_DMA_CTL3_cp_first(0)|NF_DMA_CTL3_ddr_wr(1)|NF_DMA_CTL3_dma_xfer(1));
                }else if(cp_mode == CP_NF_AES_ECB_128){
                        REG_WRITE_U32(REG_DMA_CTL3,NF_DMA_CTL3_cp_enable(1)|NF_DMA_CTL3_cp_first(1)|NF_DMA_CTL3_ddr_wr(1)|NF_DMA_CTL3_dma_xfer(1));
                }else{
                        REG_WRITE_U32(REG_DMA_CTL3,NF_DMA_CTL3_ddr_wr(1)|NF_DMA_CTL3_dma_xfer(1));
                }
		
		// flush cache.
		RTK_FLUSH_CACHE(data_buf, page_size);
		RTK_FLUSH_CACHE(oob_buf, oob_size);


		//Enable Auto mode
		REG_WRITE_U32( REG_AUTO_TRIG,NF_AUTO_TRIG_auto_trig(1)|NF_AUTO_TRIG_spec_auto_case(0)| NF_AUTO_TRIG_auto_case(auto_trigger_mode));

		WAIT_DONE(REG_AUTO_TRIG,0x80,0);
		WAIT_DONE(REG_DMA_CTL3,0x01,0);

		if(oob_buf)	{
#if 0
			REG_WRITE_U32(REG_READ_BY_PP,0x00);
			REG_WRITE_U32(REG_SRAM_CTL, 0x30 | 0x04);
			rtk_read_oob_from_SRAM(mtd, oob_buf);
			REG_WRITE_U32(REG_SRAM_CTL, 0x00);
			REG_WRITE_U32(REG_READ_BY_PP,0x80);
#endif
                        syncPageRead();

    		        data = (REG_READ_U32(REG_SPR_DDR_CTL) & 0x0fffffff) << 3;	// physical address
    		         //printk("data==> 0x%x\n",data);
		        oob_buf[0] = REG_READ_U32(data + 0x0) & 0xff;
                        //printk("oob_buf[0]==> 0x%x, page=0x%x\n",oob_buf[0],page);           
		}

		//rtk_hexdump("data_buf : ", data_buf, page_size);
		//rtk_hexdump("oob_buf : ", oob_buf, oob_size);
                //if(REG_READ_U32(REG_ND_ECC) & 0x4)
                    //printk("page: 0x%x, MAX_ECC_NUM: 0x%x\n", page, REG_MAX_ECC_NUM_max_ecc_num(REG_READ_U32(REG_MAX_ECC_NUM)));

                //syncPageRead();
		// return OK if all data bit is 1 (page is not written yet)
		if (REG_READ_U32(REG_BLANK_CHK) & 0x2){
			//printk("data all one \n");
			if (g_enReadRetrial) {
				if (read_retry_cnt !=0) {
					switch(g_id_chain)
					{
						case 0x4b44642c:
							printk("MT29F64G08CBABA read-retrial rtk_set_feature_micron ...reset to 0\n");
							rtk_set_feature_micron(0);
							break;
                            			case 0x4b44442c:
							printk("MT29F32G08CBADA read-retrial rtk_set_feature_micron ...reset to 0\n");
							rtk_set_feature_micron(0);
							break;
						case 0x9384d798:
							printk("TC58TEG5DCJT read-retrial rtk_set_feature_toshiba ...reset to 0\n");
							rtk_set_feature_toshiba(0);
                                                        rtk_set_terminate_toshiba();
							break;
                            			case 0x9384de98:
							printk("TC58TEG6DCJT read-retrial rtk_set_feature_toshiba ...reset to 0\n");
							rtk_set_feature_toshiba(0);
                                                        rtk_set_terminate_toshiba();
							break;
                                                case 0x9394de98:
							printk("TC58TEG6DDK read-retrial rtk_set_feature_toshiba ...reset to 0\n");
							rtk_set_feature_toshiba_new(0);
                                                        rtk_set_terminate_toshiba();
							break;
                            
						default:
							break;
							
					}
				}
			}
			REG_WRITE_U32(REG_BLANK_CHK,NF_BLANK_CHK_blank_ena(1)|NF_BLANK_CHK_read_ecc_xnor_ena(0));
			return 0;
		}
		else if (REG_READ_U32(REG_ND_ECC) & 0x8) {
			if (!bChkAllOne && this->ecc_select>=0x18) {
                                //printk("[DBG]bChkAllOne this->ecc_select: 0x%x\n", this->ecc_select);
				bChkAllOne = 1;
				continue;
			}
			if (g_enReadRetrial) {
				bChkAllOne = 0;
                                if(read_retry_cnt == 0){    //set pre condition
					switch(g_id_chain)
					{
						case 0x9384d798:
							printk("TC58TEG5DCJT read-retrial rtk_set_pre_condition_toshiba\n");
							rtk_set_pre_condition_toshiba();
							break;
                            			case 0x9384de98:
							printk("TC58TEG6DCJT read-retrial rtk_set_pre_condition_toshiba\n");
							rtk_set_pre_condition_toshiba();
							break;       
                                                case 0x9394de98:
							printk("TC58TEG6DDK read-retrial rtk_set_pre_condition_toshiba\n");
							rtk_set_pre_condition_toshiba();
							break;    
						default:
							break;							
					}
                                }              
				read_retry_cnt ++;
				if (read_retry_cnt <= max_read_retry_cnt) {
					switch(g_id_chain)
					{
						case 0x4b44642c:
							printk("MT29F64G08CBABA read-retrial rtk_set_feature_micron ...read_retry_cnt: %d\n", read_retry_cnt);
							rtk_set_feature_micron(read_retry_cnt);
							break;
						case 0x4b44442c:
							printk("MT29F32G08CBADA read-retrial rtk_set_feature_micron ...read_retry_cnt: %d\n", read_retry_cnt);
							rtk_set_feature_micron(read_retry_cnt);
							break;	
						case 0x9384d798:
							printk("TC58TEG5DCJT read-retrial rtk_set_feature_toshiba ...read_retry_cnt: %d, data: 0x%x\n", read_retry_cnt, read_retry_toshiba_cnt[read_retry_cnt]);
							rtk_set_feature_toshiba(read_retry_toshiba_cnt[read_retry_cnt]);
							break;
                            			case 0x9384de98:
							printk("TC58TEG6DCJT read-retrial rtk_set_feature_toshiba ...read_retry_cnt: %d, data: 0x%x\n", read_retry_cnt, read_retry_toshiba_cnt[read_retry_cnt]);
							rtk_set_feature_toshiba(read_retry_toshiba_cnt[read_retry_cnt]);
                            				break;
                            			case 0x9394de98:
							printk("TC58TEG6DDK read-retrial rtk_set_feature_toshiba ...read_retry_cnt: %d\n", read_retry_cnt);
							rtk_set_feature_toshiba_new(read_retry_cnt);
							break;
                            
						default:
							break;
							
					}
					continue;
				}
			}
			printk("[DBG]ecc error... page=0x%x, REG_BLANK_CHK reg: 0x%x \n", page, REG_READ_U32(REG_BLANK_CHK));
			if (g_enReadRetrial) {
				if (read_retry_cnt !=0) {
					switch(g_id_chain)
					{
						case 0x4b44642c:
							printk("MT29F64G08CBABA read-retrial rtk_set_feature_micron ...reset to 0\n");
							rtk_set_feature_micron(0);
							break;
                            			case 0x4b44442c:
							printk("MT29F32G08CBADA read-retrial rtk_set_feature_micron ...reset to 0\n");
							rtk_set_feature_micron(0);
							break;
						case 0x9384d798:
							printk("TC58TEG5DCJT read-retrial rtk_set_feature_toshiba ...reset to 0\n");
							rtk_set_feature_toshiba(0);
                                                        rtk_set_terminate_toshiba();
							break;
                            			case 0x9384de98:
							printk("TC58TEG6DCJT read-retrial rtk_set_feature_toshiba ...reset to 0\n");
							rtk_set_feature_toshiba(0);
                                                        rtk_set_terminate_toshiba();
							break;
                                                case 0x9394de98:
							printk("TC58TEG6DDK read-retrial rtk_set_feature_toshiba ...reset to 0\n");
							rtk_set_feature_toshiba_new(0);
                                                        rtk_set_terminate_toshiba();
							break;
						default:
                            
							break;
							
					}
				}
			}
                        REG_WRITE_U32(REG_BLANK_CHK,NF_BLANK_CHK_blank_ena(1)|NF_BLANK_CHK_read_ecc_xnor_ena(0));
                        return -1;	// ECC not correctable
		}
		else {
			if (g_enReadRetrial) {
				if (read_retry_cnt !=0) {
					switch(g_id_chain)
					{
						case 0x4b44642c:
							printk("MT29F64G08CBABA read-retrial rtk_set_feature_micron ...reset to 0\n");
							rtk_set_feature_micron(0);
							break;
                            			case 0x4b44442c:
							printk("MT29F32G08CBADA read-retrial rtk_set_feature_micron ...reset to 0\n");
							rtk_set_feature_micron(0);
							break;
                            			case 0x9384d798:
							printk("TC58TEG5DCJT read-retrial rtk_set_feature_toshiba ...reset to 0\n");
							rtk_set_feature_toshiba(0);
                                                        rtk_set_terminate_toshiba();
							break;
                            			case 0x9384de98:
							printk("TC58TEG6DCJT read-retrial rtk_set_feature_toshiba ...reset to 0\n");
							rtk_set_feature_toshiba(0);
                                                        rtk_set_terminate_toshiba();
							break;
                                                case 0x9394de98:
							printk("TC58TEG6DDK read-retrial rtk_set_feature_toshiba ...reset to 0\n");
							rtk_set_feature_toshiba_new(0);
                                                        rtk_set_terminate_toshiba();
							break;
						default:
							break;
							
					}
				}
			}            
                        REG_WRITE_U32(REG_BLANK_CHK,NF_BLANK_CHK_blank_ena(1)|NF_BLANK_CHK_read_ecc_xnor_ena(0));
			return 0;
		}
	}

	return rc;
}
//----------------------------------------------------------------------------
static int rtk_write_oob(struct mtd_info *mtd, u16 chipnr, int page, int len, const u_char *oob_buf)
{
	struct nand_chip *this = (struct nand_chip *) mtd->priv;
	int rc = 0;
	uint8_t	auto_trigger_mode = 1;
	uint8_t	addr_mode = 1;
	unsigned int page_len, dram_sa, dma_len, spare_dram_sa;
	//unsigned char oob_1stB;
	memset(this->ops.datbuf, 0xff, page_size);

	page_size = mtd->writesize;
	oob_size = mtd->oobsize;
	ppb = mtd->erasesize/mtd->writesize;

	if ( chipnr == 0 && page >= 0 && page < g_BootcodeSize/page_size ){
		printk("[%s] You have no permission to write this page %d\n", __FUNCTION__, page);
		//up (&sem_NF_CARDREADER);
		return -2;
	}

	if ( len>oob_size || !oob_buf ){
		printk("[%s] error: len>oob_size OR oob_buf is NULL\n", __FUNCTION__);
		//up (&sem_NF_CARDREADER);
		return -1;
	}

	/*if ( page == ppb || page == ppb+1|| page == ppb*2 || page == ppb*2+1 )
		oob_1stB = BBT_TAG;
	else if(( page>=g_BootcodeSize/page_size )&&(page<(g_BootcodeSize+g_Factory_param_size)/page_size))
		oob_1stB = TAG_FACTORY_PARAM;
	else
		oob_1stB = 0xFF;*/
//end of alexchang 0208-2010
	//REG_WRITE_U32(0x01,0xb801032c);	//Enable NAND/CardReader arbitrator add by alexchang 0303-2010
	REG_WRITE_U32(REG_SRAM_CTL,0x00);//add by alexchang 0208-2010
	REG_WRITE_U32(REG_DATA_TL0,NF_DATA_TL0_length0(0));
 	if(this->ecc_select >= 0x18)
	{
		page_len = page_size >> 10;
		REG_WRITE_U32(REG_DATA_TL1,NF_DATA_TL1_length1(4));
	}
	else
	{
		page_len = page_size >> 9;
		REG_WRITE_U32(REG_DATA_TL1,NF_DATA_TL1_length1(2));
	}

	REG_WRITE_U32(REG_READ_BY_PP,NF_READ_BY_PP_read_by_pp(0));//add by alexchang 0208-2010
	REG_WRITE_U32(REG_PP_CTL1,NF_PP_CTL1_pp_start_addr(0));//add by alexchang 0208-2010
	REG_WRITE_U32(REG_PP_CTL0,0);//add by alexchang 0208-2010

	REG_WRITE_U32( REG_PAGE_LEN,NF_PAGE_LEN_page_len(page_len));

 	REG_WRITE_U32(REG_ND_CMD,NF_ND_CMD_cmd(CMD_PG_WRITE_C1));
	REG_WRITE_U32(REG_CMD2,NF_CMD2_cmd2(CMD_PG_WRITE_C2));
	REG_WRITE_U32(REG_CMD3,NF_CMD3_cmd3(CMD_PG_WRITE_C3));

	REG_WRITE_U32( REG_ND_PA0,NF_ND_PA0_page_addr0(page));
	REG_WRITE_U32( REG_ND_PA1,NF_ND_PA1_page_addr1(page>>8));
	REG_WRITE_U32( REG_ND_PA2,NF_ND_PA2_addr_mode(addr_mode)|NF_ND_PA2_page_addr2(page>>16));
	REG_WRITE_U32( REG_ND_PA3,NF_ND_PA3_page_addr3((page>>21)&0x7));
	REG_WRITE_U32(REG_MULTI_CHNL_MODE,NF_MULTI_CHNL_MODE_edo(1));//add by alexchang0205-2010

	switch(this->ecc_select) {
		case 6:
			REG_WRITE_U32(REG_ECC_SEL, 0x0);
			break;
		case 12:
			REG_WRITE_U32(REG_ECC_SEL, 0x1);
			break;
		case 16:
			REG_WRITE_U32(REG_ECC_SEL, 0xe);
			break;
		case 24:
			REG_WRITE_U32(REG_ECC_SEL, 0xa);
			break;
		case 40:
			REG_WRITE_U32(REG_ECC_SEL, 0x2);
			break;
		case 43:
			REG_WRITE_U32(REG_ECC_SEL, 0x4);
			break;
		case 65:
			REG_WRITE_U32(REG_ECC_SEL, 0x6);
			break;
		case 72:
			REG_WRITE_U32(REG_ECC_SEL, 0x8);
			break;
		default:
			REG_WRITE_U32(REG_ECC_SEL, 0x0);
			break;
	}

	dram_sa = ( (phys_addr_t)this->ops.datbuf >> 3);
	REG_WRITE_U32(REG_DMA_CTL1,NF_DMA_CTL1_dram_sa(dram_sa));
	dma_len = page_size >> 9;
	REG_WRITE_U32(REG_DMA_CTL2,NF_DMA_CTL2_dma_len(dma_len));	

	spare_dram_sa = ( (phys_addr_t)oob_buf >> 3);
	REG_WRITE_U32( REG_SPR_DDR_CTL,NF_SPR_DDR_CTL_spare_ddr_ena(1)|NF_SPR_DDR_CTL_per_2k_spr_ena(1)|NF_SPR_DDR_CTL_spare_dram_sa(spare_dram_sa));
	REG_WRITE_U32(REG_DMA_CTL3,NF_DMA_CTL3_ddr_wr(1)|NF_DMA_CTL3_dma_xfer(1));
	REG_WRITE_U32( REG_AUTO_TRIG,NF_AUTO_TRIG_auto_trig(1)|NF_AUTO_TRIG_spec_auto_case(0)| NF_AUTO_TRIG_auto_case(auto_trigger_mode));

//#if RTK_NAND_INTERRUPT
//	RTK_WAIT_EVENT;
//	NF_RESET_IRQ;
//	NF_ENABLE_IRQ(NF_POLL_IRQ_MASK);
//	g_nfFlag = NF_WRITE_TRIGGER;
//	REG_WRITE_U32(REG_POLL_FSTS,NF_POLL_FSTS_bit_sel(6)|NF_POLL_FSTS_trig_poll(1) );
//	RTK_WAIT_EVENT;
//#else
	WAIT_DONE(REG_AUTO_TRIG,0x80,0);
	WAIT_DONE(REG_DMA_CTL3,0x01,0);
	REG_WRITE_U32(REG_POLL_FSTS,NF_POLL_FSTS_bit_sel(6)|NF_POLL_FSTS_trig_poll(1) );
	WAIT_DONE(REG_POLL_FSTS,0x01,0x0);
	WAIT_DONE(REG_ND_CTL,0x40,0x40);//add by alexchang 0416-2010
//#endif

	return 0;


	if ( REG_READ_U32(REG_ND_DAT) & 0x01 ){
		//up (&sem_NF_CARDREADER);
		printk("[%s] write oob is not completed at page %d\n", __FUNCTION__, page);

		return -1;
	}

	//printk("[AT]WO block : %u ,page : %d  \n",page/ppb,page%ppb);
	//up (&sem_NF_CARDREADER);
//int k= 0;
//for(k=0;k<32;k++)
//printk("[WO][%u,%u][%d]0x%x\n",page/ppb,page%ppb,k,oob_buf[k]);
//printk("----------------------------\n");

	return rc;
}

//----------------------------------------------------------------------------
//char bbbbb[4096];

static int rtk_write_ecc_page (struct mtd_info *mtd, u16 chipnr, unsigned int page,
			const u_char *data_buf, struct mtd_oob_ops *ops, int isBBT)
{
	unsigned int ppb = mtd->erasesize/mtd->writesize;
	struct nand_chip *this = (struct nand_chip *) mtd->priv;
	int rc = 0;
	uint8_t	auto_trigger_mode = 1;
	uint8_t	addr_mode = 1;

	unsigned int page_len, dram_sa, dma_len, spare_dram_sa;
	unsigned char oob_1stB,oob_2ndB=0xff;
	unsigned int i, count, increment;
	uint8_t spare_enable = 1;
	const  u_char *oob_buf = NULL;
	if(ops)
		oob_buf = &ops->oobbuf[ops->oobretlen];

    if(((phys_addr_t)data_buf&0x7)!=0) {
            printk("[%s]data_buf must 8 byte alignmemt!!\n",__FUNCTION__);
            BUG();
    }
    if(((phys_addr_t)oob_buf&0x7)!=0) {
            printk("[%s]oob_buf must 8 byte alignmemt!!\n",__FUNCTION__);
            BUG();
    }

	if ( page == ppb || page == ppb+1|| page == ppb*2 || page == ppb*2+1 )
		oob_1stB = BBT_TAG;
	else if(( page>=g_BootcodeSize/page_size )&&(page<(g_BootcodeSize+g_Factory_param_size)/page_size))
		oob_1stB = TAG_FACTORY_PARAM;
	//REG_WRITE_U32(0xb801032c,0x01);	//Enable NAND/CardReader arbitrator add by alexchang 0303-2010
	else
		oob_1stB = 0xFF;

	if (oob_buf)
		{
			for(i=1; i<8; i++)
			{
			oob_1stB = *(unsigned char*)(((unsigned char*)oob_buf)+0);
			oob_2ndB = *(unsigned char*)(((unsigned char*)oob_buf)+1);
			pr_debug("[LY] write oob data 1 : 0x%02x 0x%02x\n", oob_1stB, oob_2ndB);
			}
		}

	increment = (this->ecc_select == 0x18)?4:8;
	if(this->ecc_select == 0x6 || this->ecc_select == 0x0c){
		count = page_size / 512;
			}
	else{
		count = page_size / 1024;
		}

	for(i=0; i<count; i++){
		if(i*increment+2 > oob_size)
			break;
		this->ops.oobbuf[i*increment] = oob_1stB;
		this->ops.oobbuf[i*increment+1] = oob_2ndB;
        }

	//REG_WRITE_U32(REG_SRAM_CTL,0x00);//add by alexchang 0208-2010
	REG_WRITE_U32(REG_DATA_TL0,NF_DATA_TL0_length0(0));
 	if(this->ecc_select >= 0x18)
	{
		// enable randomizer
		REG_WRITE_U32(REG_RMZ_CTRL, 1);
		
		page_len = page_size >> 10;
		REG_WRITE_U32(REG_DATA_TL1,NF_DATA_TL1_length1(4));
	}
	else
	{
		// set random write
		REG_WRITE_U32(REG_RND_EN, 1);
		REG_WRITE_U32(REG_RND_CMD1, 0x85);
		REG_WRITE_U32(REG_RND_DATA_STR_COL_H, 0);	// data start address MSB (always 0)
		REG_WRITE_U32(REG_RND_SPR_STR_COL_H, page_size >> 8);	// spare start address MSB
		REG_WRITE_U32(REG_RND_SPR_STR_COL_L, page_size & 0xff);	// spare start address LSB
		
		page_len = page_size >> 9;
		REG_WRITE_U32(REG_DATA_TL1,NF_DATA_TL1_length1(2));
	}

	REG_WRITE_U32( REG_PAGE_LEN,NF_PAGE_LEN_page_len(page_len));

	//Set PP
	REG_WRITE_U32(REG_READ_BY_PP,NF_READ_BY_PP_read_by_pp(0));//add by alexchang 0208-2010
	REG_WRITE_U32(REG_PP_CTL1,NF_PP_CTL1_pp_start_addr(0));//add by alexchang 0208-2010
	REG_WRITE_U32(REG_PP_CTL0,0);//add by alexchang 0208-2010

	//Set command
 	REG_WRITE_U32(REG_ND_CMD,NF_ND_CMD_cmd(CMD_PG_WRITE_C1));
	REG_WRITE_U32(REG_CMD2,NF_CMD2_cmd2(CMD_PG_WRITE_C2));
	REG_WRITE_U32(REG_CMD3,NF_CMD3_cmd3(CMD_PG_WRITE_C3));

	//Set address
	REG_WRITE_U32( REG_ND_PA0,NF_ND_PA0_page_addr0(page));
	REG_WRITE_U32( REG_ND_PA1,NF_ND_PA1_page_addr1(page>>8));
	REG_WRITE_U32( REG_ND_PA2,NF_ND_PA2_addr_mode(addr_mode)|NF_ND_PA2_page_addr2(page>>16));
	REG_WRITE_U32( REG_ND_PA3,NF_ND_PA3_page_addr3((page>>21)&0x7));
	REG_WRITE_U32(REG_ND_CA0, 0);
	REG_WRITE_U32(REG_ND_CA1, 0);

	//Set ECC
	if (ops && ops->mode == MTD_OPS_RAW){
		REG_WRITE_U32(REG_MULTI_CHNL_MODE,NF_MULTI_CHNL_MODE_edo(1)|NF_MULTI_CHNL_MODE_ecc_pass(1));
		spare_enable = 0;
		memset(this->ops.oobbuf, 0xff, mtd->oobsize);
		printk("%s: Write with MTD_OPS_RAW. Without ECC.\n", __func__);
	}
	else
	REG_WRITE_U32(REG_MULTI_CHNL_MODE,NF_MULTI_CHNL_MODE_edo(1));//add by alexchang0205-2010
	REG_WRITE_U32( REG_ECC_STOP,NF_ECC_STOP_ecc_n_stop(0x01));

	switch(this->ecc_select) {
		case 6:
			REG_WRITE_U32(REG_ECC_SEL, 0x0);
			break;
		case 12:
			REG_WRITE_U32(REG_ECC_SEL, 0x1);
			break;
		case 16:
			REG_WRITE_U32(REG_ECC_SEL, 0xe);
			break;
		case 24:
			REG_WRITE_U32(REG_ECC_SEL, 0xa);
			break;
		case 40:
			REG_WRITE_U32(REG_ECC_SEL, 0x2);
			break;
		case 43:
			REG_WRITE_U32(REG_ECC_SEL, 0x4);
			break;
		case 65:
			REG_WRITE_U32(REG_ECC_SEL, 0x6);
			break;
		case 72:
			REG_WRITE_U32(REG_ECC_SEL, 0x8);
			break;
		default:
			REG_WRITE_U32(REG_ECC_SEL, 0x0);
			break;
	}

	// flush cache.
	RTK_FLUSH_CACHE(data_buf, page_size);
	RTK_FLUSH_CACHE(this->ops.oobbuf, oob_size);
	
	dram_sa = ( (phys_addr_t)data_buf >> 3);
	REG_WRITE_U32(REG_DMA_CTL1,NF_DMA_CTL1_dram_sa(dram_sa));
	dma_len = page_size >> 9;
	REG_WRITE_U32(REG_DMA_CTL2,NF_DMA_CTL2_dma_len(dma_len));	
	
	spare_dram_sa = ( (phys_addr_t)(this->ops.oobbuf) >> 3);
	//REG_WRITE_U32(REG_SPR_DDR_CTL,NF_SPR_DDR_CTL_spare_ddr_ena(1)|NF_SPR_DDR_CTL_per_2k_spr_ena(1)|NF_SPR_DDR_CTL_spare_dram_sa(spare_dram_sa));
	REG_WRITE_U32(REG_SPR_DDR_CTL,0x40000000|NF_SPR_DDR_CTL_spare_ddr_ena(spare_enable)|NF_SPR_DDR_CTL_spare_dram_sa(spare_dram_sa));
	REG_WRITE_U32(REG_DMA_CTL3,NF_DMA_CTL3_ddr_wr(0)|NF_DMA_CTL3_dma_xfer(1));
	REG_WRITE_U32( REG_AUTO_TRIG,NF_AUTO_TRIG_auto_trig(1)|NF_AUTO_TRIG_spec_auto_case(0)| NF_AUTO_TRIG_auto_case(auto_trigger_mode));


//#if RTK_NAND_INTERRUPT
//	RTK_WAIT_EVENT;
//	NF_RESET_IRQ;
//	NF_ENABLE_IRQ(NF_POLL_IRQ_MASK);
//	g_nfFlag = NF_WRITE_TRIGGER;
//	REG_WRITE_U32(REG_POLL_FSTS,NF_POLL_FSTS_bit_sel(6)|NF_POLL_FSTS_trig_poll(1) );
//	RTK_WAIT_EVENT;
//#else
	WAIT_DONE(REG_AUTO_TRIG,0x80,0);
	WAIT_DONE(REG_DMA_CTL3,0x01,0);
	REG_WRITE_U32(REG_POLL_FSTS,NF_POLL_FSTS_bit_sel(6)|NF_POLL_FSTS_trig_poll(1) );
	WAIT_DONE(REG_POLL_FSTS,0x01,0x0);
	WAIT_DONE(REG_ND_CTL,0x40,0x40);//add by alexchang 0416-2010
//#endif

	//while (1);
	
	return 0;

	if ( REG_READ_U32(REG_ND_DAT) & 0x01 ){
		//up (&sem_NF_CARDREADER);
		printk("[%s] write is not completed at page %d\n", __FUNCTION__, page);
		return -1;
	}


	//mtd->isCPdisable_W = 0;
	//printk("[AT]W block : %u , page: %u \n",page/ppb,page%ppb);
	//up (&sem_NF_CARDREADER);


	return rc;
}
//----------------------------------------------------------------------------
static void display_version (void)
{
	const char *revision;
	const char *date;
	char *running = (char *)VERSION;
	strsep(&running, " ");
	strsep(&running, " ");
	revision = strsep(&running, " ");
	date = strsep(&running, " ");
	printk(BANNER " Rev:%s (%s)\n", revision, date);
}
#if 1
void endian_swap(unsigned int* x)
{
	*x = (*x>>24) |((*x<<8) & 0x00FF0000) |((*x>>8) & 0x0000FF00) |(*x<<24);
}
#endif
//----------------------------------------------------------------------------
#if RTK_NAND_INTERRUPT
static irqreturn_t rtknf_irq(int irq, void *dev)
{
	//printk("++++f:%d,0x%x\n",g_nfFlag,REG_READ_U32(REG_NAND_ISR));
	//Read isr handler
	//printk("&g_irq_waitq 0x%x\n",&g_irq_waitq);
	if(CHECK_IRQ(NF_READ_TRIGGER,REG_NAND_ISR,NF_DMA_ISR,NF_DMA_ISR))
	{
		CLEAR_IRQ(REG_NAND_ISR,NF_DMA_ISR);
		g_nfFlag=NF_WAKE_UP;
		//wake_up_interruptible(&g_host->irq_waitq);
		wake_up_interruptible(&g_irq_waitq);

		return IRQ_HANDLED;
	}
	else if(CHECK_IRQ(NF_READ_TRIGGER,REG_NAND_ISR,NF_AUTO_TRIG_ISR,NF_AUTO_TRIG_ISR))
	{
		CLEAR_IRQ(REG_NAND_ISR,NF_AUTO_TRIG_ISR);
		return IRQ_HANDLED;
	}

	//Write isr handler
	if(CHECK_IRQ(NF_WRITE_TRIGGER,REG_NAND_ISR,NF_AUTO_TRIG_ISR,NF_AUTO_TRIG_ISR))
	{
		CLEAR_IRQ(REG_NAND_ISR,NF_AUTO_TRIG_ISR);
		g_nfFlag=NF_WAKE_UP;
		//wake_up_interruptible(&g_host->irq_waitq);
		wake_up_interruptible(&g_irq_waitq);
		return IRQ_HANDLED;
	}
	if(CHECK_IRQ(NF_WRITE_TRIGGER,REG_NAND_ISR,NF_POLL_STATUS_ISR,NF_POLL_STATUS_ISR))
	{
		CLEAR_IRQ(REG_NAND_ISR,NF_POLL_STATUS_ISR);
		g_nfFlag=NF_WAKE_UP;
		//wake_up_interruptible(&g_host->irq_waitq);
		wake_up_interruptible(&g_irq_waitq);
		return IRQ_HANDLED;
	}
	else if(CHECK_IRQ(NF_WRITE_TRIGGER,REG_NAND_ISR,NF_DMA_ISR,NF_DMA_ISR))
	{
		CLEAR_IRQ(REG_NAND_ISR,NF_DMA_ISR);
		return IRQ_HANDLED;
	}

	//Erase isr handler
	if(CHECK_IRQ(NF_ERASE_TRIGGER,REG_NAND_ISR,NF_POLL_STATUS_ISR,NF_POLL_STATUS_ISR))
	{
		CLEAR_IRQ(REG_NAND_ISR,NF_POLL_STATUS_ISR);
		g_nfFlag=NF_WAKE_UP;
		//wake_up_interruptible(&g_host->irq_waitq);
		wake_up_interruptible(&g_irq_waitq);
		return IRQ_HANDLED;
	}
	else if(CHECK_IRQ(NF_ERASE_TRIGGER,REG_NAND_ISR,NF_AUTO_TRIG_ISR,NF_AUTO_TRIG_ISR))
	{
		CLEAR_IRQ(REG_NAND_ISR,NF_AUTO_TRIG_ISR);
		return IRQ_HANDLED;
	}

	if((REG_READ_U32(REG_NAND_ISR)&NF_IRQ_MASK))
	{
		if((g_nfFlag==NF_ERASE_TRIGGER)||(g_nfFlag==NF_READ_TRIGGER)||(g_nfFlag==NF_READ_TRIGGER)||(g_nfFlag=NF_WAKE_UP))
		{
			//printk("+++++f:%d,0x%x\n",g_nfFlag,REG_READ_U32(REG_NAND_ISR));
			CLR_REG_NAND_ISR;
			return IRQ_HANDLED;
		}
	}
	//printk("xxxxxf:%d,0x%x\n",g_nfFlag,REG_READ_U32(REG_NAND_ISR));
	 return IRQ_NONE;
}

//----------------------------------------------------------------------------
static int __init rtkNF_probe(struct platform_device *pdev)
{
	struct resource *r;
	int nf_irq,ret;
	/* Allocate memory for MTD device structure and private data */
	g_host = kzalloc(sizeof(struct rtk_nand_host), GFP_KERNEL);
	if (!g_host)
		return -ENOMEM;

	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	//init_waitqueue_head(&g_host->irq_waitq);
	init_waitqueue_head(&g_irq_waitq);




	nf_irq = platform_get_irq(pdev, 0);
	ret = request_irq(nf_irq, rtknf_irq, IRQF_SHARED, DRIVER_NAME, g_host);   //rtkcr_interrupt
    if (ret)
    {
        printk(KERN_ERR "%s: cannot assign irq %d\n", DRIVER_NAME, nf_irq);
		return -1;
    }
	return 0;

}
#endif

int board_nand_init(struct nand_chip *nand)
{
	display_version();

	REG_WRITE_U32( REG_CLOCK_ENABLE1,REG_READ_U32(REG_CLOCK_ENABLE1)& (~0x00800000));
    REG_WRITE_U32( REG_NF_CKSEL, (REG_READ_U32(REG_NF_CKSEL) & (0xFFFFFFF0)) | 0x05 );
	REG_WRITE_U32( REG_CLOCK_ENABLE1,REG_READ_U32(REG_CLOCK_ENABLE1)| (0x00800000));

	// set pinmux to nand.
    REG_WRITE_U32(SYS_muxpad0, 0x55555555);

	// controller init.
	REG_WRITE_U32(REG_PD, 0x1E);
    REG_WRITE_U32(REG_TIME_PARA3, 0x2);
	REG_WRITE_U32(REG_TIME_PARA2, 0x5);
	REG_WRITE_U32(REG_TIME_PARA1, 0x2);

	//REG_WRITE_U32(REG_MULTI_CHNL_MODE, 0x20);
	REG_WRITE_U32(REG_MULTI_CHNL_MODE, 0x0);
	REG_WRITE_U32(REG_READ_BY_PP, 0x0);
	
	//REG32(REG_SPR_DDR_CTL) = 0x30000000 | (PHYS(SPARE_DMA_ADDR) >> 3);

	//REG32(REG_RMZ_SEED_L) = 0x6e;
	//REG32(REG_RMZ_SEED_H) = 0xa3;

        //REG_WRITE_U32(0x1801013c, REG_READ_U32(0x1801013c) & 0xffffffef);

	// reset nand.
	REG_WRITE_U32(REG_ND_CMD, 0xff);
	REG_WRITE_U32(REG_ND_CTL, 0x80);

	//printk("\n\n");
	//printk("0x1800011c = 0x%x \n", REG_READ_U32(0x1800011c));
	//printk("0x18000128 = 0x%x \n", REG_READ_U32(0x18000128));
	//printk("0x18000124 = 0x%x \n", REG_READ_U32(0x18000124));
	
	//printk("SYS_muxpad0:0x%x = 0x%x \n", SYS_muxpad0, REG_READ_U32(SYS_muxpad0));
	//printk("REG_PD:0x%x = 0x%x \n", REG_PD, REG_READ_U32(REG_PD));
	
	//printk("trigger... \n");
	WAIT_DONE(REG_ND_CTL,0x80,0);
	//printk("trigger xfer.\n");
	WAIT_DONE(REG_ND_CTL,0x40,0x40);
	//printk("nand ready. \n");
	//printk("\n\n");
	
	nand->read_id			= rtk_nand_read_id;
	nand->read_ecc_page 	= rtk_read_ecc_page;
	nand->read_oob 			= rtk_read_oob;
	nand->write_ecc_page	= rtk_write_ecc_page;
	nand->write_oob			= rtk_write_oob;

	nand->erase_block 	= rtk_erase_block;
	//nand->suspend		= rtk_nand_suspend;
	//nand->resume		= rtk_nand_resume;
	//nand->sync			= NULL;

	nand->RBA_PERCENT = RBA_PERCENT;
	printk("[Default]RBA percentage: %d%%\n",nand->RBA_PERCENT);

	return 0;
}

MODULE_AUTHOR("AlexChang <alexchang2131@realtek.com>");
MODULE_DESCRIPTION("Realtek NAND Flash Controller Driver");





