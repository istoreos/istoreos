/*
#endif
 *  This is a driver for the eMMC controller found in Realtek RTD1195
 *  SoCs.
 *
 *  Copyright (C) 2013 Realtek Semiconductors, All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#include <asm/arch/rtkemmc.h>
#include <asm/arch/platform_lib/board/gpio.h>
#include <asm/arch/rbus/crt_reg.h>
#include <asm/arch/cpu.h>
#define __RTKEMMC_C__


#define MAX_DESCRIPTOR_NUM    8
#define	EMMC_MAX_SCRIPT_BLK   8   

#define EMMC_MAX_XFER_BLKCNT MAX_DESCRIPTOR_NUM * EMMC_MAX_SCRIPT_BLK

unsigned char * dummy_512B;

unsigned char* ext_csd = NULL;
static u8 HS200_PHASE_INHERITED = 1;
static unsigned int savedVP0 = 0xff, savedVP1 = 0xff;
unsigned int emmc_cid[4]={0};
char *mmc_name = "RTD1295 eMMC";

void wait_done(volatile UINT32 *addr, UINT32 mask, UINT32 value){
	int n = 0;
	while (((*addr) &mask) != value)
	{
		if(n++ > 3000)
		{
			printf("Time out \n");
			return;      
	 	}   
		mdelay(1);
	}
}


//emmc descriptor must be 8 byte aligned
unsigned int* rw_descriptor __attribute__ ((aligned(8))) =  (unsigned int *) 0x00300000;

/* mmc spec definition */
const unsigned int tran_exp[] = {
    10000, 100000, 1000000, 10000000,
    0,     0,      0,       0
};

const unsigned char tran_mant[] = {
    0,  10, 12, 13, 15, 20, 25, 30,
    35, 40, 45, 50, 55, 60, 70, 80,
};

const unsigned int tacc_exp[] = {
    1, 10, 100, 1000, 10000, 100000, 1000000, 10000000,
};

const unsigned int tacc_mant[] = {
    0,  10, 12, 13, 15, 20, 25, 30,
    35, 40, 45, 50, 55, 60, 70, 80,
};

const char *const state_tlb[9] = {
    "STATE_IDLE",
    "STATE_READY",
    "STATE_IDENT",
    "STATE_STBY",
    "STATE_TRAN",
    "STATE_DATA",
    "STATE_RCV",
    "STATE_PRG",
    "STATE_DIS"
};
const char *const bit_tlb[4] = {
    "1bit",
    "4bits",
    "8bits",
    "unknow"
};

const char *const clk_tlb[8] = {
    "30MHz",
    "40MHz",
    "49MHz",
    "49MHz",
    "15MHz",
    "20MHz",
    "24MHz",
    "24MHz"
};

/************************************************************************
 *  global variable
 ************************************************************************/
unsigned cr_int_status_reg;
unsigned char * sys_ext_csd_addr;
unsigned int rtkemmc_debug_msg;
unsigned int rtkemmc_off_error_msg_in_init_flow;
static e_device_type emmc_card;
static unsigned int sys_rsp17_addr;
static unsigned char* ptr_ext_csd;
static volatile struct backupRegs gRegTbl;
//static volatile UINT8 g_cmd[6]={0};
extern int mmc_ready_to_use;
int swap_endian(UINT32 input);
int gCurrentBootDeviceType=0;
volatile unsigned int gCurrentBootMode=MODE_SD20;

static int realErrTuning = 0;
void card_stop(void);
void rtkemmc_host_reset(void);
int rtkemmc_stop_transmission( e_device_type * card , int bIgnore);
int rtkemmc_Stream( unsigned int cmd_idx,UINT32 blk_addr, UINT32 dma_addr, UINT32 dma_length, int bIgnore);
int rtkemmc_SendCMDGetRSP( struct rtk_cmd_info * cmd_info, unsigned int bIgnore);
int sample_ctl_switch(int cmd_idx);
void rtkemmc_set_pad_driving(unsigned int clk_drv, unsigned int cmd_drv, unsigned int data_drv, unsigned int ds_drv);
int polling_to_tran_state(int cmd_idx, int bIgnore);


/**************************************************************************************
 * kylin mmc driver
 **************************************************************************************/
/*******************************************************
 *
 *******************************************************/

UINT32 check_error(int bIgnore){
	UINT32 error;
	error = cr_readl(CR_EMMC_RINTSTS);
	CP15ISB;
	sync();

	if ((error&CR_EMMC_EBE)==CR_EMMC_EBE)
	{
		if (!bIgnore)
		printf("EMMC ERROR ---------> End bit error \n");
		return CR_EMMC_EBE;
	}
	else if ((error&CR_EMMC_SBE)==CR_EMMC_SBE)
	{
		if (!bIgnore)
		printf("EMMC ERROR ---------> Start bit error \n");
		return CR_EMMC_SBE;
	}
	else if ((error&CR_EMMC_HLE)==CR_EMMC_HLE)
	{
		if (!bIgnore)
		printf("EMMC ERROR ---------> Hardware locked write error \n");
		return CR_EMMC_HLE;
	}
	else if ((error&CR_EMMC_FRUN)==CR_EMMC_FRUN)
	{
		if (!bIgnore)
		printf("EMMC ERROR ---------> FIFO underrun/overrun error \n");
		return CR_EMMC_FRUN;
	}
	else if ((error&CR_EMMC_HTO)==CR_EMMC_HTO)
	{
		if (!bIgnore)
		printf("EMMC ERROR ---------> Data starvation by host timeout\n");
		return CR_EMMC_HTO;
	}
	else if ((error&CR_EMMC_DRTO)==CR_EMMC_DRTO)
	{
		if (!bIgnore)
		printf("EMMC ERROR ---------> Data read timeout\n");
		return CR_EMMC_DRTO;
		}
	else if ((error&CR_EMMC_RTO)==CR_EMMC_RTO)
	{
		if (!bIgnore)
		printf("EMMC ERROR ---------> Response timeout\n");
		return CR_EMMC_RTO;
	}
	else if ((error&CR_EMMC_DCRC)==CR_EMMC_DCRC)
	{
		if (!bIgnore)
		printf("EMMC ERROR ---------> Data CRC error\n");
		return CR_EMMC_DCRC;
	}
	else if ((error&CR_EMMC_RCRC)==CR_EMMC_RCRC)
	{
		if (!bIgnore)
		printf("EMMC ERROR ---------> Response CRC error\n");
		return CR_EMMC_RCRC;
	}
	else if ((error&CR_EMMC_RE)==CR_EMMC_RE)
	{
		if (!bIgnore)
		printf("EMMC ERROR ---------> Response error\n");		
		return CR_EMMC_RE;
	}
	else 
	{
		return 0;
	}	
	return 0;
	sync();
}

void setRandomMemory(unsigned long dmaddr, unsigned int length)
{
	int i=0;
        for(i=0;i<(length/4);i++)
        {
                *(u64 *)(dmaddr+(i*4)) = (u64)((i+0x78*0x80)*0x13579bdf);
                sync();
        }
	flush_cache(dmaddr, length);
        sync();
}

int rtkemmc_data_sync( struct mmc * mmc )
{
    MMCPRINTF("*** %s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
    
    mmc->rca = emmc_card.rca;
    mmc->high_capacity = emmc_card.sector_addressing ? 1 : 0;
	return 0;
}

/*
static void rtkemmc_restore_registers()
{
    cr_writel(gRegTbl.emmc_mux_pad0, CR_EMMC_muxpad0);
    cr_writel(gRegTbl.emmc_mux_pad1, CR_EMMC_muxpad1);
    cr_writel(gRegTbl.emmc_pfunc_nf1, CR_EMMC_PFUNC_NF1);
    cr_writel(gRegTbl.emmc_pdrive_nf1, CR_EMMC_PDRIVE_NF1);
    cr_writel(gRegTbl.emmc_pdrive_nf2, CR_EMMC_PDRIVE_NF2);
    cr_writel(gRegTbl.emmc_pdrive_nf3, CR_EMMC_PDRIVE_NF3);
    cr_writel(gRegTbl.emmc_ctype, CR_EMMC_CTYPE);
    cr_writel(gRegTbl.emmc_uhsreg, CR_EMMC_UHSREG);
    cr_writel(gRegTbl.emmc_ddr_reg, CR_EMMC_DDR_REG);
    cr_writel(gRegTbl.emmc_card_thr_ctl, CR_EMMC_CARD_THR_CTL);
    cr_writel(gRegTbl.emmc_clk_div, CR_EMMC_CLKDIV);
    cr_writel(gRegTbl.emmc_ckgen_ctl, CR_EMMC_CKGEN_CTL);
    cr_writel(gRegTbl.emmc_dqs_ctrl1, CR_EMMC_DQS_CTRL1);

    sync();
    //rtkemmc_dump_registers();
}
*/

static void rtkemmc_backup_registers(void)
{
    gRegTbl.emmc_mux_pad0 = readl(CR_EMMC_muxpad0);
    gRegTbl.emmc_mux_pad1 = readl(CR_EMMC_muxpad1);
    gRegTbl.emmc_pfunc_nf1 = readl(CR_EMMC_PFUNC_NF1);
    gRegTbl.emmc_pdrive_nf1 = readl(CR_EMMC_PDRIVE_NF1);
    gRegTbl.emmc_pdrive_nf2 = readl(CR_EMMC_PDRIVE_NF2);
    gRegTbl.emmc_pdrive_nf3 = readl(CR_EMMC_PDRIVE_NF3);
    gRegTbl.emmc_ctype = readl(CR_EMMC_CTYPE);
    gRegTbl.emmc_uhsreg = readl(CR_EMMC_UHSREG);
    gRegTbl.emmc_ddr_reg = readl(CR_EMMC_DDR_REG);
    gRegTbl.emmc_card_thr_ctl = readl(CR_EMMC_CARD_THR_CTL);
    gRegTbl.emmc_clk_div = readl(CR_EMMC_CLKDIV);
    gRegTbl.emmc_ckgen_ctl = readl(CR_EMMC_CKGEN_CTL);
    gRegTbl.emmc_dqs_ctrl1 = readl(CR_EMMC_DQS_CTRL1);
}


static int wait_done_timeout(volatile u32 *addr, u32 mask, u32 value){
	int n = 0;
	while (((*addr) &mask) != value)
	{
		if(n++ > 0x10000)
		{
			printf("reg(0x%08lu) = 0x%08x \n", (uintptr_t)addr, (*addr));
			printf("mask = %08x, value = %08x \n", mask, value);
			printf("Time out \n");
			return -1;      
	 	}
		udelay(10);
		sync();
	}
	return 0;
}

static void set_cmd_info(e_device_type *card,struct mmc_cmd * cmd,
                         struct rtk_cmd_info * cmd_info,u32 opcode,u32 arg,u8 rsp_len)
{
    memset(cmd, 0, sizeof(struct mmc_cmd));
    memset(cmd_info, 0, sizeof(struct rtk_cmd_info));

    cmd->cmdidx         = opcode;
    cmd->cmdarg            = arg;
    cmd_info->cmd       = cmd;
    cmd_info->rsp_len   = rsp_len;
}


/*******************************************************
 *
 *******************************************************/
int rtkemmc_send_status(u32* resp, uint show_msg, int bIgnore)
{
    int err = 0;
	int bMalloc=0;
	e_device_type * card = NULL;

    MMCPRINTF("*** %s %s %d - rca : %08x, rca addr : %08x\n", __FILE__, __FUNCTION__, __LINE__, emmc_card.rca, &emmc_card.rca);
   
    sync(); 
	
   	struct mmc_cmd cmd;
    struct rtk_cmd_info cmd_info;

    memset(&cmd, 0, sizeof(struct mmc_cmd));
    memset(&cmd_info, 0, sizeof(struct rtk_cmd_info));

    if (card == NULL)
    {
		bMalloc=1;
		card = (e_device_type*)malloc(sizeof( e_device_type));
    }
	
    set_cmd_info(card,&cmd,&cmd_info,
                 MMC_SEND_STATUS,
                 emmc_card.rca,
                 6);
    err = rtkemmc_SendCMDGetRSP(&cmd_info,bIgnore);

    if (bMalloc)
    {
		free(card);
		card = NULL;
    }


	
    if(err){
		if((show_msg)&&(!bIgnore))
        	printf("MMC_SEND_STATUS fail\n");
    }else{
        UINT8 cur_state = R1_CURRENT_STATE(cmd.response[0]);
		*resp = cmd.response[0];
		if((show_msg)&&(!bIgnore))
		{
	            printf("get cur_state=");
	            printf(state_tlb[cur_state]);
	            printf("\n");
				printf("-------------------------\n");
				printf("R1 response 0x%08x:  \n",*resp);
				if(!((*resp) & (1<<7))){
					printf("switch ok!\n");
					}
				if((*resp) & (1<<8)){
					printf("ready for data!\n");
					}
				
				printf("-------------------------\n");
				
	            printf("\n");
		}
    }

    return err;
}

int rtkemmc_set_wp(u32 blk_addr, uint show_msg, int bIgnore)
{
    int err = 0;
	int bMalloc=0;
	e_device_type * card = NULL;
	u32 resp = 0;

    MMCPRINTF("*** %s %s %d - blk_addr : %08x\n", __FILE__, __FUNCTION__, __LINE__, blk_addr);
   
    sync(); 
	
   	struct mmc_cmd cmd;
    struct rtk_cmd_info cmd_info;

    memset(&cmd, 0, sizeof(struct mmc_cmd));
    memset(&cmd_info, 0, sizeof(struct rtk_cmd_info));

    if (card == NULL)
    {
		bMalloc=1;
		card = (e_device_type*)malloc(sizeof( e_device_type));
    }
	
    set_cmd_info(card,&cmd,&cmd_info,
                 MMC_SET_WRITE_PROT,
                 blk_addr,
                 6);
    err = rtkemmc_SendCMDGetRSP(&cmd_info,bIgnore);

    if (bMalloc)
    {
		free(card);
		card = NULL;
    }
    if(err){
		if((show_msg)&&(!bIgnore))
        	printf("MMC_SET_WRITE_PROT fail\n");
    }else{
        UINT8 cur_state = R1_CURRENT_STATE(cmd.response[0]);
		resp = cmd.response[0];
		if((show_msg)&&(!bIgnore))
		{
            printf("get cur_state=");
            printf(state_tlb[cur_state]);
            printf("\n");
		}
    }
	printf("The resp is %d.\n",resp);

    return err;
}

int rtkemmc_clr_wp(u32 blk_addr, uint show_msg, int bIgnore)
{
    int err = 0;
	int bMalloc=0;
	e_device_type * card = NULL;
	u32 resp = 0;

    MMCPRINTF("*** %s %s %d - blk_addr : %08x\n", __FILE__, __FUNCTION__, __LINE__, blk_addr);
   
    sync(); 
	
   	struct mmc_cmd cmd;
    struct rtk_cmd_info cmd_info;

    memset(&cmd, 0, sizeof(struct mmc_cmd));
    memset(&cmd_info, 0, sizeof(struct rtk_cmd_info));

    if (card == NULL)
    {
		bMalloc=1;
		card = (e_device_type*)malloc(sizeof( e_device_type));
    }
	
    set_cmd_info(card,&cmd,&cmd_info,
                 MMC_CLR_WRITE_PROT,
                 blk_addr,
                 6);
    err = rtkemmc_SendCMDGetRSP(&cmd_info,bIgnore);

    if (bMalloc)
    {
		free(card);
		card = NULL;
    }
    if(err){
		if((show_msg)&&(!bIgnore))
        	printf("MMC_CLR_WRITE_PROT fail\n");
    }else{
        UINT8 cur_state = R1_CURRENT_STATE(cmd.response[0]);
		resp = cmd.response[0];
		if((show_msg)&&(!bIgnore))
		{
            printf("get cur_state=");
            printf(state_tlb[cur_state]);
            printf("\n");
		}
    }
	printf("The resp is %d.\n",resp);

    return err;
}


int rtk_eMMC_read( unsigned int blk_addr, unsigned int data_size, unsigned int * buffer )
{
    int ret_err = 0;
    unsigned int total_blk_cont;
    unsigned int curr_xfer_blk_cont;
    unsigned int address;
    e_device_type * card = &emmc_card;
    UINT8 ret_state=0;
    UINT32 bRetry=0, resp = 0;
    UINT32 retry_cnt=0, retry_cnt1=0, retry_cnt2=0, retry_cnt3=0;
    int err1=0;

    RDPRINTF("\nemmc:%s blk_addr=0x%08x, data_size=0x%08x, buffer=0x%08x, addressing=%d\n", __FUNCTION__, blk_addr, data_size, buffer, card->sector_addressing);

    if( !mmc_ready_to_use ) {
         RDPRINTF("emmc: not ready to use\n");
    }

    total_blk_cont = data_size>>9;
    if( data_size & 0x1ff ) {
        total_blk_cont+=1;
    }

#ifndef FORCE_SECTOR_MODE
	if( card->sector_addressing ) {
		address = blk_addr;
	}
	else {
		address = blk_addr << 9;
	}
#else
    address = blk_addr;
#endif
#ifdef EMMC_SPLIT_BLK
	while( total_blk_cont ) {
		if( total_blk_cont > EMMC_MAX_XFER_BLKCNT ) {
			curr_xfer_blk_cont = EMMC_MAX_XFER_BLKCNT;
		}
		else {
			curr_xfer_blk_cont = total_blk_cont;
		}

		flush_cache((unsigned long)buffer, curr_xfer_blk_cont << 9);
        if (IS_SRAM_ADDR((uintptr_t)buffer))
        	ret_err = -1; //cannot allow r/w to sram in bootcode
        else{
			if (curr_xfer_blk_cont == 1)
        		ret_err = rtkemmc_Stream(0xa0000340|MMC_READ_SINGLE_BLOCK, address, (unsigned int)(uintptr_t)buffer, curr_xfer_blk_cont << 9,0);
			else
				ret_err = rtkemmc_Stream(0xa0001340|MMC_READ_MULTIPLE_BLOCK, address, (unsigned int)(uintptr_t)buffer, curr_xfer_blk_cont << 9,0);
        } 
		if( ret_err ) {
			return 0;
		}
		total_blk_cont -= curr_xfer_blk_cont;
		buffer += (curr_xfer_blk_cont<<(9-2));
		address += curr_xfer_blk_cont;

		CP15ISB;
		sync();

		//EXECUTE_CUSTOMIZE_FUNC(0); // insert execute customer callback at here

	}

	total_blk_cont = data_size>>9;
    if( data_size & 0x1ff ) {
        total_blk_cont+=1;
    }
	return total_blk_cont;
#else
RETRY_RD_CMD:
    flush_cache((unsigned long)buffer, data_size);

	if (IS_SRAM_ADDR((uintptr_t)buffer))
        	ret_err = -1; //cannot allow r/w to sram in bootcode
    else{
		if (total_blk_cont == 1)
    		ret_err = rtkemmc_Stream(0xa0000340|MMC_READ_SINGLE_BLOCK, address, buffer, total_blk_cont << 9,0);
		else
			ret_err = rtkemmc_Stream(0xa0001340|MMC_READ_MULTIPLE_BLOCK, address, buffer, total_blk_cont << 9,0);
    } 


    if (ret_err)
    {
        if (retry_cnt2++ < MAX_CMD_RETRY_COUNT*2)
	{
            sample_ctl_switch(-1);
            goto RETRY_RD_CMD;
	}
        return ret_err;
    }
    
    /* To wait status change complete */
    bRetry=0;
    retry_cnt=0;
    retry_cnt1=0;
    while(1)
    {
        err1 = rtkemmc_send_status(&resp,1,0);
        //1. if cmd sent error, try again
        if (err1)
        {
            sample_ctl_switch(-1);
            if (retry_cnt++ > MAX_CMD_RETRY_COUNT*2)
                return ERR_EMMC_SEND_STATUS_RETRY_FAIL;
            mdelay(1);
            continue;
        }
	ret_state = R1_CURRENT_STATE(resp);
        //2. get state
        if (ret_state != STATE_TRAN) 
        {
            bRetry = 1;
            if (retry_cnt1++ > MAX_CMD_RETRY_COUNT*2)
                return ERR_EMMC_SEND_RW_CMD_RETRY_FAIL;
            rtkemmc_stop_transmission(&emmc_card,0);
            mdelay(1000);
        }
        else
        {
            //out peaceful
            if (bRetry == 0)
                return !ret_err ?  total_blk_cont : 0;
            else
            {
                retry_cnt2 = 0;
                if (retry_cnt3++ > MAX_CMD_RETRY_COUNT*2)
                    return ERR_EMMC_SEND_RW_CMD_RETRY_FAIL;
                goto RETRY_RD_CMD;
            }
        }
    }
#endif
	printf("The err1 is %d. The retry_cnt is %d. The retry_cnt1 is %d. The retry_cnt2 is %d. The retry_cnt3 is %d.\n",err1,retry_cnt,retry_cnt1,retry_cnt2,retry_cnt3);
	printf("The ret_state, bRetry, resp are %c, %d, %d\n.",ret_state,bRetry,resp);
	printf("The card addressing=%d\n",card->sector_addressing);

    return !ret_err ?  total_blk_cont : 0;
}



/*******************************************************
 *
 *******************************************************/
int rtkemmc_wait_status(UINT8 state, int bIgnore)
{
    u32 resp = 0;
    UINT32 timeend;
    int rom_err = 0;

    timeend = 5;

    while(timeend--)
     {
        sync();
        rom_err = rtkemmc_send_status(&resp, 1, bIgnore);

        if(rom_err){
	    if (!bIgnore)
	    {
            	printf("wait ");
            	printf(state_tlb[state]);
            	printf(" fail, resp = 0x%08x\n",resp);
            	break;
	    }
        }
        else{
            UINT8 cur_state = R1_CURRENT_STATE(resp);
	    #ifdef MMC_DEBUG
            printf("cur_state=");
            printf(state_tlb[cur_state]);
            printf("\n");
	    #endif
            rom_err = -10;
            if(cur_state == state){
                if(resp & R1_READY_FOR_DATA){
                    rom_err = 0;
                    break;
                }
            }
        }
        udelay(10);
    }

    return rom_err;
}

/*******************************************************
 *
 *******************************************************/
void rtkemmc_set_div( unsigned int set_div )
{
    MMCPRINTF("rtkemmc_set_div; switch to 0x%08x\n", set_div);
    
    //disable clock
    cr_writel(0, CR_EMMC_CLKENA);
    isb();

    //EMMC Cmd
    cr_writel(0xa0202000, CR_EMMC_CMD);
    isb();
    sync();
    wait_done_timeout((volatile u32 *)CR_EMMC_CMD, 0x80000000, 0x0);
    sync();

    //set divider
    cr_writel(set_div, CR_EMMC_CLKDIV);
    isb();
    sync();

    //EMMC Cmd
    cr_writel(0xa0202000, CR_EMMC_CMD);
    isb();
    sync();
    wait_done_timeout((volatile u32 *)CR_EMMC_CMD, 0x80000000, 0x0);
    isb();
    sync();

    //enable clock
    cr_writel(0x10001, CR_EMMC_CLKENA);
    isb();
    sync();

    //EMMC Cmd
    writel(0xa0202000, CR_EMMC_CMD);
    isb();
    sync();
    wait_done_timeout((volatile u32 *)CR_EMMC_CMD, 0x80000000, 0x0);
    isb();


	MMCPRINTF("rtkemmc_set_div: set div to 0x%02x, EMMC_CLKDIV=%08x\n",
                set_div, cr_readl(CR_EMMC_CLKDIV));;
}


/*******************************************************
 *
 *******************************************************/
void rtkemmc_set_freq( unsigned int set_ldo)
{
    u32 tmp_val=0;
	MMCPRINTF("rtkemmc_set_freq; set to 0x%08x\n",set_ldo);
	
	tmp_val = (cr_readl(PLL_EMMC4) & 0x06);  
	cr_writel(tmp_val,  PLL_EMMC4);
	CP15ISB;
	sync();
	
    tmp_val = (cr_readl(PLL_EMMC3) & 0xffff)|(set_ldo<<16);
    cr_writel(tmp_val,  PLL_EMMC3);
	CP15ISB;
    sync();

	tmp_val = (cr_readl(PLL_EMMC4) | 0x01);  
	cr_writel(tmp_val,  PLL_EMMC4);
	CP15ISB;
	sync();

	wait_done_timeout((u32*)CR_EMMC_STATUS, 0x200, 0x0);          //card is not busy
	CP15ISB;
	sync();

	// [A01], if EMMC N/F code changed, toggle CR_EMMC_DUMMY_SYS bit 30
	if (get_rtd129x_cpu_revision() >= RTD129x_CHIP_REVISION_A01 ) {
		cr_writel((~cr_readl(CR_EMMC_DUMMY_SYS)) & 0x40000000, CR_EMMC_DUMMY_SYS);
		CP15ISB;
		sync();
	}
}

/*******************************************************
 *
 *******************************************************/
void rtkemmc_set_bits( unsigned int set_bit )
{
    MMCPRINTF("rtkemmc_set_bits_width; switch to 0x%08x\n",set_bit);
    cr_writel(set_bit,CR_EMMC_CTYPE);
    sync();
}

/*******************************************************
 *
 *******************************************************/
void rtkemmc_set_mode_selection( unsigned int set_bit )
{
    //tbd
    return;
}
int rtkemmc_get_mode_selection(void)
{
   //tbd
    return 0;
}


/*******************************************************
 *
 *******************************************************/
//set the other clk divider
//clk_div	[2..0]
//000: div1
//001: div2
//010: div4
//011: div8

void rtkemmc_set_wrapper_div( unsigned int level )
{

    MMCPRINTF("rtkemmc_set_wrapper_div; switch to level 0x%08x\n",level);

    switch(level)
    {
        case 0:  
            writel(0x2100, CR_EMMC_CKGEN_CTL);
            break;
        case 1:
            writel(0x2010, CR_EMMC_CKGEN_CTL);
            break;
        case 2:
			writel(0x2012, CR_EMMC_CKGEN_CTL);
            break;
		case 3:
			writel(0x2013, CR_EMMC_CKGEN_CTL);
            break;	
        default :
            printf("error wrapper div setting ! \n");
            break;          
    }
    sync();

}





/*******************************************************
 *
 *******************************************************/
unsigned int mmc_get_rsp_len( unsigned char rsp_para )
{
    switch (rsp_para & 0x3) {
	    case 0:
	        return 0; // hw bug ??
	    case 1:
	        return 6;
	    case 2:
	        return 17;
	    default:
	        return 0;
    }
}

/*******************************************************
 *
 *******************************************************/
unsigned int mmc_get_rsp_type( struct mmc_cmd * cmd )
{
    unsigned int rsp_type = 0;

    /* the marked case are used. */
    switch( cmd->cmdidx)
    {
        case 3:
        case 7:
        case 13:
        case 16:
        case 23:
        case 35:
        case 36:
        case 55:
            rsp_type |= CRC16_CAL_DIS;
        case 8:
        case 11:
        case 14:
        case 19:
        case 17:
        case 18:
        case 20:
        case 24:
        case 25:
        case 26:
        case 27:
        case 30:
        case 42:
        case 56:
	case 60:
	case 61:
            rsp_type |= SD_R1;
            break;
        case 6:
        case 12:
        case 28:
        case 29:
        case 38:
            rsp_type = SD_R1b|CRC16_CAL_DIS;
            break;
        case 2:
        case 9:
        case 10:
            rsp_type = SD_R2;
            break;
        case 1:
            rsp_type = SD_R3;
            break;
        default:
            rsp_type = SD_R0;
            break;
    }
    return rsp_type;
}



/*******************************************************
 *
 *******************************************************/
UINT32 IsAddressSRAM(UINT32 addr)
{
    if ((addr<0x80000000) || (addr > 0x80007FFF))
        //ddr address
        return 0;
    else
        //secureRam addr
        return 1;
}

void print_ip_desc(void){
	printf("EMMC IP_DESC0 = 0x%08x\n", cr_readl(CR_EMMC_IP_DESC0));
	printf("EMMC IP_DESC1 = 0x%08x\n", cr_readl(CR_EMMC_IP_DESC1));
	printf("EMMC IP_DESC2 = 0x%08x\n", cr_readl(CR_EMMC_IP_DESC2));
	printf("EMMC IP_DESC3 = 0x%08x\n", cr_readl(CR_EMMC_IP_DESC3));
}

void make_ip_des(UINT32 dma_addr, UINT32 dma_length){
    
	UINT32* des_base = rw_descriptor;
	UINT32  blk_cnt;                                                                                                                               
	UINT32  blk_cnt2;                                                                 
	UINT32  remain_blk_cnt;                                                                                                                        
                                                             
	UINT32  tmp_val;                                                                                                                                 

	flush_cache((uintptr_t)rw_descriptor, 16*MAX_DESCRIPTOR_NUM);
	
	//CMD31 only transfer 8B
	if (dma_length < 512){
		cr_writel(dma_length, CR_EMMC_BLKSIZ);
		blk_cnt = 1;
		
	}
	else{
		cr_writel(0x200, CR_EMMC_BLKSIZ);
		blk_cnt  = dma_length>>9;
	}
	
  	remain_blk_cnt  = blk_cnt;    

	CP15ISB;
	sync();
		                                                                                        
	while(remain_blk_cnt){                                                                                       
                                                                                     
		/* setting des0; transfer parameter  */                                         
		tmp_val = 0x80000000 | 0x2 | 0x10;                               
		                                                                                
		if(remain_blk_cnt == blk_cnt)                                                   
		        tmp_val |= 0x8;                                               
		                                                                                
		if(remain_blk_cnt <= EMMC_MAX_SCRIPT_BLK)                                       
		        tmp_val |= 0x4;                                               
		                                                                                
		des_base[0] = tmp_val;                                                         
		                                                                                
		/* setting des1; buffer size in byte */                                         
		if(remain_blk_cnt > EMMC_MAX_SCRIPT_BLK){                                       
		        blk_cnt2 = EMMC_MAX_SCRIPT_BLK;                                         
		}else{                                                                          
		        blk_cnt2 = remain_blk_cnt;                                              
		}

		//CMD31 only transfer 8B
		if (dma_length < 512)
		    des_base[1] = dma_length;				
		else	
			des_base[1] = (blk_cnt2<<9);                                                   
		                                                                                
		/* setting des2; Physical address to DMA to/from */                             
		des_base[2] = (dma_addr);                                                    
		                                                                                
		/* setting des3; next descrpter entry */                                        
		des_base[3] = ((unsigned long)(des_base+4));      

		CP15ISB;
		sync();
	                                                                                                                                                             
		dma_addr = dma_addr+(blk_cnt2<<9);                                    
		remain_blk_cnt -= blk_cnt2;                                             
		des_base += 4;  

		CP15ISB;
		sync();
			                                                                             
	}         
	
	flush_cache((uintptr_t)rw_descriptor, 16*MAX_DESCRIPTOR_NUM);
	CP15ISB;
	sync();
} 

/*
static char * device_status[]={
	"", //bit 0
	"",
	"",
	"",
	"",
	"APP_CMD",		
	"EXCEPTION_EVENT",
	"SWITCH_ERROR",
	"READY_FOR_DATA",	
	"CURRENT_STATE_IDLE", //bit 9
	"CURRENT_STATE_READY",
	"CURRENT_STATE_IDENT",
	"CURRENT_STATE_STBY",
	"CURRENT_STATE_TRAN",
	"CURRENT_STATE_DATA", 
	"CURRENT_STATE_RCV",  
	"CURRENT_STATE_PRG",  
	"CURRENT_STATE_DIS",  
	"CURRENT_STATE_BTST", 
	"CURRENT_STATE_SLEP", 
	"ERASE_RESET",
	"",
	"WP_ERASE_SKIP",
	"CID_OR_CSD_OVERWRITE",
	"",
	"",
	"ERROR",
	"CC_ERROR",
	"DEVICE_ECC_FAILED",
	"ILLEGAL_COMMAND",
	"COM_CRC_ERROR",
	"LOCK_UNLOCK_FAILED",
	"DEVICE_IS_LOCKED",
	"WP_VIOLATION",
	"ERASE_PARAM",
	"ERASE_SEQ_ERROR",
	"BLOCK_LEN_ERROR",
	"ADDRESS_MISALIGN",
	"ADDRESS_OUT_OF_RANGE",	
};
*/

/*
static void Print_Device_Status(unsigned int status_code){
	int i=0;
	int count =0;
	int weight =0;
	for(;i<32;i++){
		if((9 == i) ||(10 == i) ||(11 == i) || (12 == i)){
			if((status_code >>i) & (0x01)){  // 1
				count |=  (0x1<<weight);
				weight ++;
			}
			else{  //0
				count &= ~(0x1<<weight);				
				weight ++;
			}
			if(12==i){
				printf("device status is %s \n",device_status[count+9]);
				}
		}
		else if ( (status_code >>i) & (0x01)){
			if(i>11){
			  printf("device status is %s \n",device_status[i+7]);
			}
			else
		   	  printf("device status is %s \n",device_status[i]);
			}
	}
}
*/

static void rtkemmc_read_rsp(u32 *rsp, int reg_count)
{
    MMCPRINTF("rsp addr=0x%p; rsp_count=%u\n", rsp, reg_count);

    if ( reg_count==6 ){
		rsp[0] = rsp[1] = 0;
        rsp[0] = cr_readl(CR_EMMC_RESP0);
//        MMCPRINTF("rsp[0]=0x%08x\n",rsp[0]);
		//printf("rsp[0]=0x%08x\n",rsp[0]);
	//	printf("%s : Line %d: func:%s \n", __FILE__, __LINE__,__func__);
	 //   Print_Device_Status(rsp[0]);
		
    }else if(reg_count==17){

        rsp[3] = cr_readl(CR_EMMC_RESP0);
        rsp[2] = cr_readl(CR_EMMC_RESP1);
        rsp[1] = cr_readl(CR_EMMC_RESP2);
        rsp[0] = cr_readl(CR_EMMC_RESP3);
       // MMCPRINTF("rsp[0]=0x%08x, rsp[1]=0x%08x, rsp[2]=0x%08x, rsp[3]=0x%08x\n",rsp[0],rsp[1],rsp[2],rsp[3]);
       printf("rsp[0]=0x%08x, \n \
       	       rsp[1]=0x%08x, \n \
       	       rsp[2]=0x%08x, \n \
       	       rsp[3]=0x%08x\n",rsp[0],rsp[1],rsp[2],rsp[3]);
    }
    else
        MMCPRINTF("rsp[0]=0x%08x\n",rsp[0]);
}

static int rtkemmc_set_rspparam(struct rtk_cmd_info *cmd_info)
{
	switch(cmd_info->cmd->cmdidx)
	{
	case MMC_GO_IDLE_STATE:
		cmd_info->cmd_para = (CMD_START_CMD|CMD_USE_HOLD_REG);
		cmd_info->rsp_len = 6;
		cmd_info->cmd->cmdarg = 0x00000000;
		break;
	case MMC_SEND_OP_COND:
		cmd_info->cmd_para = (CMD_START_CMD|CMD_USE_HOLD_REG|CMD_RSP_EXP);
		cmd_info->cmd->cmdarg = MMC_SECTOR_ADDR|MMC_VDD_165_195;
		cmd_info->rsp_len = 6;
		break;
	case MMC_ALL_SEND_CID:
		cmd_info->cmd_para = (CMD_START_CMD|CMD_USE_HOLD_REG|CMD_CHK_RESP_CRC|CMD_RSP_LEN|CMD_RSP_EXP);
		cmd_info->rsp_len = 17;
		cmd_info->cmd->cmdarg = 0x00000000;
		break;
	case MMC_SET_RELATIVE_ADDR:
		cmd_info->cmd_para = (CMD_START_CMD|CMD_USE_HOLD_REG|CMD_CHK_RESP_CRC|CMD_RSP_EXP);
		cmd_info->cmd->cmdarg = emmc_card.rca;
		cmd_info->rsp_len = 6;
		break;
	case MMC_SEND_CSD:
	case MMC_SEND_CID:
		cmd_info->cmd_para = (CMD_START_CMD|CMD_USE_HOLD_REG|CMD_CHK_RESP_CRC|CMD_RSP_LEN|CMD_RSP_EXP);
		cmd_info->cmd->cmdarg = emmc_card.rca;
		cmd_info->rsp_len = 17;
		break;
	case MMC_SEND_EXT_CSD:
		cmd_info->cmd_para = (CMD_START_CMD|CMD_USE_HOLD_REG|CMD_DATA_EXP|CMD_CHK_RESP_CRC|CMD_RSP_EXP);
		cmd_info->cmd->cmdarg = 0;
		cmd_info->rsp_len = 6;
		break;
	case MMC_SLEEP_AWAKE:
		cmd_info->cmd_para = (CMD_START_CMD|CMD_USE_HOLD_REG|CMD_CHK_RESP_CRC|CMD_RSP_EXP);
		cmd_info->rsp_len = 6;
		cmd_info->cmd->cmdarg = 0x00000000;
		MMCPRINTF( "%s : cmd5 arg=0x%08x\n",__func__,cmd_info->cmd->cmdarg);
		break;
	case MMC_SELECT_CARD:
		MMCPRINTF( "%s : cmd7 arg : 0x%08x\n",__func__,cmd_info->cmd->cmdarg);
		cmd_info->cmd->cmdarg = emmc_card.rca;
		//printf("[sj] rca is %x\n",emmc_card.rca);
		if (cmd_info->cmd->resp_type == (MMC_RSP_NONE | MMC_CMD_AC))
		{
			MMCPRINTF( "%s : cmd7 with rsp none\n",__func__);
			cmd_info->cmd_para = (CMD_START_CMD|CMD_USE_HOLD_REG|CMD_CHK_RESP_CRC);
		}
		else
		{
			MMCPRINTF( "%s : cmd7 with rsp\n",__func__);
			cmd_info->cmd_para = (CMD_START_CMD|CMD_USE_HOLD_REG|CMD_CHK_RESP_CRC|CMD_RSP_LEN|CMD_RSP_EXP);
		}
		cmd_info->rsp_len = 6;
		break;
	case MMC_SWITCH:
		cmd_info->cmd_para = (CMD_START_CMD|CMD_USE_HOLD_REG|CMD_CHK_RESP_CRC|CMD_RSP_EXP);
		cmd_info->rsp_len = 6;
		break;
	case MMC_SEND_STATUS:
		cmd_info->cmd_para = (CMD_START_CMD|CMD_USE_HOLD_REG|CMD_CHK_RESP_CRC|CMD_RSP_EXP);
		cmd_info->cmd->cmdarg = emmc_card.rca;
		cmd_info->rsp_len = 6;
		break;
	case MMC_STOP_TRANSMISSION:
		cmd_info->cmd_para = (CMD_START_CMD|CMD_USE_HOLD_REG|CMD_CHK_RESP_CRC|CMD_RSP_EXP);
		cmd_info->rsp_len = 6;
		break;
	case MMC_READ_MULTIPLE_BLOCK:
		cmd_info->cmd_para = (CMD_START_CMD|CMD_USE_HOLD_REG|CMD_SEND_AUTO_STOP|CMD_DATA_EXP|CMD_CHK_RESP_CRC|CMD_RSP_EXP);
		cmd_info->rsp_len = 6;
		break;
	case MMC_WRITE_MULTIPLE_BLOCK:
		cmd_info->cmd_para = (CMD_START_CMD|CMD_USE_HOLD_REG|CMD_SEND_AUTO_STOP|CMD_RD_WR|CMD_DATA_EXP|CMD_CHK_RESP_CRC|CMD_RSP_EXP);
		cmd_info->rsp_len = 6;
		break;
	case MMC_READ_SINGLE_BLOCK:
		cmd_info->cmd_para = (CMD_START_CMD|CMD_USE_HOLD_REG|CMD_DATA_EXP|CMD_CHK_RESP_CRC|CMD_RSP_EXP);
		cmd_info->rsp_len = 6;
		break;
	case MMC_WRITE_BLOCK:
		cmd_info->cmd_para = (CMD_START_CMD|CMD_USE_HOLD_REG|CMD_RD_WR|CMD_DATA_EXP|CMD_CHK_RESP_CRC|CMD_RSP_EXP);
		cmd_info->rsp_len = 6;
		break;
	case MMC_SET_WRITE_PROT:
	case MMC_CLR_WRITE_PROT:
		cmd_info->cmd_para = (CMD_START_CMD|CMD_USE_HOLD_REG|CMD_CHK_RESP_CRC|CMD_RSP_EXP);
		cmd_info->rsp_len = 6;
		break;
	case MMC_SEND_WRITE_PROT_TYPE:
		cmd_info->cmd_para = (CMD_START_CMD|CMD_USE_HOLD_REG|CMD_DATA_EXP|CMD_CHK_RESP_CRC|CMD_RSP_EXP);
		cmd_info->rsp_len = 6;
		break;
	case MMC_SET_BLOCK_COUNT:
		cmd_info->cmd_para = (CMD_START_CMD|CMD_USE_HOLD_REG|CMD_CHK_RESP_CRC|CMD_RSP_EXP);
		cmd_info->rsp_len = 6;
		break;
	case MMC_CMD_ERASE_GROUP_START:
	case MMC_CMD_ERASE_GROUP_END:
	case MMC_CMD_ERASE:
		cmd_info->cmd_para = (CMD_START_CMD|CMD_USE_HOLD_REG|CMD_CHK_RESP_CRC|CMD_RSP_EXP);
		cmd_info->rsp_len = 6;
		break;
	default:
		cmd_info->cmd_para = (CMD_START_CMD|CMD_USE_HOLD_REG);
		cmd_info->rsp_len = 6;
		break;
	}
	MMCPRINTF( "%s : cmd=0x%02x rsp_len=0x%02x arg=0x%08x para=0x%08x\n","rtkemmc", cmd_info->cmd->cmdidx, cmd_info->rsp_len,cmd_info->cmd->cmdarg,cmd_info->cmd_para);
	return 0;
}




/*******************************************************
 *
 *******************************************************/
int rtkemmc_SendCMDGetRSP( struct rtk_cmd_info * cmd_info, unsigned int bIgnore)
{
    unsigned int rsp_len;
    volatile int ret_err;
	UINT32 cmd_idx = cmd_info->cmd->cmdidx;
	u32 *rsp = (u32 *)&cmd_info->cmd->response;
	

	rtkemmc_set_rspparam(cmd_info);
	cr_writel(0, CR_EMMC_SWC_SEL);
	cr_writel(0, CR_EMMC_CP);
	
	isb();
	sync();
  
//RET_CMD:
	cr_writel(0x0000ffff, CR_EMMC_RINTSTS); 		// clear all interrupt status
	CP15ISB;
	sync();
	cr_writel(0x0000ffff, CR_EMMC_INTMASK); 		// enable all interrupts					
	CP15ISB;
	sync();
	cr_writel(cmd_info->cmd->cmdarg, CR_EMMC_CMDARG);
	CP15ISB;
	sync();

	MMCPRINTF("CR_EMMC_CMD = 0x%08x \n", cmd_idx|cmd_info->cmd_para);
	cr_writel(cmd_idx|cmd_info->cmd_para, CR_EMMC_CMD);	// cmd Register
	CP15ISB;
	sync();
	wait_done_timeout((UINT32 *)CR_EMMC_RINTSTS, 0x4, 0x4); 	
	CP15ISB;
	sync();

	
	if ((ret_err = check_error(bIgnore))==0)
	{
		wait_done_timeout((UINT32 *)CR_EMMC_STATUS, 0x200, 0x0); 	
		rtkemmc_read_rsp(rsp, cmd_info->rsp_len);
		return 0;
	}
	else 
	{
		if (!bIgnore)
			wait_done_timeout((UINT32 *)CR_EMMC_STATUS, 0x200, 0x0);
		// bIgnore =1 is tuning case
		else if (cmd_info->cmd->cmdidx == MMC_SEND_STATUS && (cr_readl(CR_EMMC_RINTSTS) & 0x8180) ){
			realErrTuning = 1;
		}
		return ret_err;
	}		
    return ret_err;
	
	printf("The rsp_len is %d.\n",rsp_len);
}



/*******************************************************
 *
 *******************************************************/
int error_handling(unsigned int cmd_idx, unsigned int bIgnore)
{
	int err=0;
	struct mmc * mmc;
	e_device_type * card = &emmc_card;
	MY_CLR_ALIGN_BUFFER();	
 	MY_ALLOC_CACHE_ALIGN_BUFFER(char, g_ext_csd, CSD_ARRAY_SIZE);

		card_stop();
		
		if ((cmd_idx != MMC_CMD_READ_SINGLE_BLOCK)&&(cmd_idx != MMC_CMD_WRITE_SINGLE_BLOCK))
		{
			printf("send stop cmd\n");
			rtkemmc_stop_transmission(card,bIgnore);
		}
		
		printf("polling to trans\n");
		polling_to_tran_state(cmd_idx,1);

		if (bIgnore)
			return 0;
		//till here, we are good to go
		if(gCurrentBootMode >= MODE_DDR)
		{
			printf("change mode from %d to %d ---> \n", gCurrentBootMode,MODE_SD20);
			mmc = find_mmc_device(0);
			flush_cache((unsigned long)g_ext_csd, CSD_ARRAY_SIZE);
			#ifdef MMC_DEBUG
			mmc_show_ext_csd(g_ext_csd);
			#endif
			if (gCurrentBootMode == MODE_SD30)
//1295 not support ddr50
#if 0
			{
				//ddr50
                		err = mmc_select_ddr50(mmc,g_ext_csd);
				mmc->boot_caps &= ~MMC_MODE_HSDDR_52MHz;
			}
			else 
#endif
			{	//sdr50
                		err = mmc_select_sdr50(mmc,g_ext_csd);
				mmc->boot_caps &= ~MMC_MODE_HS200;
			}
			if (err)
				printf(" change mode result ==> fail\n");
			else
			{
				printf(" change mode result ==> successful\n");
			}
		}
		else
		{
		   MMCPRINTF("%s : gCurrentBootMode = %d\n", __func__,gCurrentBootMode);
		   #if 0
		   switch(gCurrentBootMode)
		   {
			case MODE_SD20:
				err = sample_ctl_switch(cmd_idx);
				break;	
			case MODE_DDR:
				err = mmc_Tuning_DDR50();
				break;	
			case MODE_SD30:
				err = mmc_Tuning_HS200();
				break;	
		   }
		   #else
		   err = sample_ctl_switch(cmd_idx);
		   #endif
		}
		if (err)
			printf("[LY] error handling fail\n");
	return err;
}

/*******************************************************
 *
 *******************************************************/
void mmc_show_ocr( void * ocr )
{
    struct rtk_mmc_ocr_reg *ocr_ptr;
    struct rtk_mmc_ocr *ptr = (struct rtk_mmc_ocr *) ocr;
    ocr_ptr = (struct rtk_mmc_ocr_reg *)&ptr->reg;
	

#ifdef THIS_IS_FLASH_WRITE_U_ENV
    prints("emmc: OCR\n");
    prints(" - start bit : ");
    print_val(ptr->start, 1);
    prints("\n");
    prints(" - transmission bit : ");
    print_val(ptr->transmission, 1);
    prints("\n");
    prints(" - check bits : ");
    print_val(ptr->check1, 2);
    prints("\n");
    prints(" - OCR register : \n");
    prints("   - 1.7v to 1.95v : ");
    print_val(ocr_ptr->lowV, 1);
    prints("\n   - 2.0v to 2.6v : ");
    print_val(ocr_ptr->val1, 2);
    prints("\n   - 2.7v to 3.6v : ");
    print_val(ocr_ptr->val2, 2);
    prints("\n   - access mode : ");
    print_val(ocr_ptr->access_mode, 1);
    prints("\n   - power up status : ");
    print_val(ocr_ptr->power_up, 1);
    prints("\n");
    prints(" - check bits : ");
    print_val(ptr->check2, 2);
    prints("\n");
    prints(" - end bit : ");
    print_val(ptr->end, 1);
    prints("\n");
#else
    MMCPRINTF("emmc: OCR\n");
    MMCPRINTF("- start bit : 0x%x\n", ptr->start);
    MMCPRINTF(" - transmission bit : 0x%x\n", ptr->transmission);
    MMCPRINTF(" - check bit : 0x%x\n", ptr->check1);
    MMCPRINTF(" - OCR register : \n");
    MMCPRINTF("   - 1.7v to 1.95v : 0x%x\n", ocr_ptr->lowV);
    MMCPRINTF("   - 2.0v to 2.6v : 0x%x\n", ocr_ptr->val1);
    MMCPRINTF("   - 2.7v to 3.6v : 0x%x\n", ocr_ptr->val2);
    MMCPRINTF("   - access mode : 0x%x\n", ocr_ptr->access_mode);
    MMCPRINTF("   - power up status : 0x%x\n", ocr_ptr->power_up);
    MMCPRINTF(" - check bits : 0x%x\n", ptr->check2);
    MMCPRINTF(" - end bits : 0x%x\n", ptr->end);
#endif

	printf("The power_up of ocr_ptr is 0x%x.\n",ocr_ptr->power_up);

}


/*******************************************************
 *
 *******************************************************/
int rtkemmc_stop_transmission( e_device_type * card , int bIgnore)
{
    struct mmc_cmd cmd;
    struct rtk_cmd_info cmd_info;
    int err = 0;
    int bMalloc=0;

    MMCPRINTF("%s : \n", __func__);

    memset(&cmd, 0, sizeof(struct mmc_cmd));
    memset(&cmd_info, 0, sizeof(struct rtk_cmd_info));
    
    if (card == NULL)
    {
		bMalloc=1;
		card = (e_device_type*)malloc(sizeof(e_device_type));
    }

    set_cmd_info(card,&cmd,&cmd_info,
                 MMC_STOP_TRANSMISSION,
                 0,
                 6);
    err = rtkemmc_SendCMDGetRSP(&cmd_info,bIgnore);

    if (bMalloc)
    {
		free(card);
		card = NULL;
    }
    if(err){
        MMCPRINTF( "MMC_STOP_TRANSMISSION fail !\n");
    }
    return err;
}

/*******************************************************
 *
 *******************************************************/
int rtkemmc_Stream_Cmd( struct rtk_cmd_info * cmd_info, unsigned int bIgnore )
{
	UINT32  EMMC_MAX_MULTI_BLK = EMMC_MAX_XFER_BLKCNT;
    unsigned int cmd_idx      = cmd_info->cmd->cmdidx;
    unsigned int block_count  = cmd_info->data->blocks;
    int ret_err=1;

	UINT32  remain_blk_cnt = block_count;
	UINT32  cur_blk_cnt;
	UINT32  cur_blk_addr = cmd_info->cmd->cmdarg;

	u8* data = (unsigned char *) cmd_info->data->dest;

	if (data == NULL){
		ret_err = -1;
	}

	
	rtkemmc_set_rspparam(cmd_info);
	

	while (remain_blk_cnt) {
		if (remain_blk_cnt > EMMC_MAX_MULTI_BLK) //one time to transfer
			cur_blk_cnt = EMMC_MAX_MULTI_BLK;
		else
			cur_blk_cnt = remain_blk_cnt;

		remain_blk_cnt -= cur_blk_cnt;
		MMCPRINTF("debug : cur_blk_addr = %u, cur_blk_cnt = %u \n", cur_blk_addr, cur_blk_cnt);
		ret_err = rtkemmc_Stream(cmd_idx|cmd_info->cmd_para, 
						         cur_blk_addr, 
						         (UINT32)(uintptr_t)data + ((cur_blk_addr - cmd_info->cmd->cmdarg) << 9), 
						         cur_blk_cnt << 9,
						         bIgnore);

		if ((!ret_err)&&(bIgnore)) 
		{
			return 0;
		}
		cur_blk_addr += cur_blk_cnt;
		if (ret_err ) return -1;
	}
	if (cmd_idx == MMC_SEND_EXT_CSD)
		return 0;
	else	
    	return block_count;


}

int polling_to_tran_state(int cmd_idx, int bIgnore)
{
	e_device_type * card = &emmc_card;
	int err=1, retry_cnt=5;
	int ret_state=0;
	u32 resp = 0;

                err=1;
                retry_cnt=5;
                while(retry_cnt-- && err)
                {
                        #ifdef MMC_DEBUG
                        err = rtkemmc_send_status(&resp,1,bIgnore);
			#else
                        err = rtkemmc_send_status(&resp,0,bIgnore);
			#endif
                }
		ret_state = R1_CURRENT_STATE(resp);
                if (ret_state != STATE_TRAN)
                {
                        #ifdef MMC_DEBUG
                        printf("before send stop\n");
                        #endif
			if ((cmd_idx != MMC_READ_SINGLE_BLOCK)&&(cmd_idx != MMC_CMD_WRITE_SINGLE_BLOCK))
                        	rtkemmc_stop_transmission(card,1);
                        err = rtkemmc_wait_status(STATE_TRAN,bIgnore);
                        #ifdef MMC_DEBUG
			if (err)
                        	printf("rtkemmc_wait_status fail\n",err);
                        #endif
                }
	return err;
}

void card_stop(void){
        MMCPRINTF("host_card_stop \n");
        volatile u32 reg;
        rtkemmc_backup_registers();

        //CRT reset eMMC
        reg = cr_readl(SOFT_RESET2);
		CP15ISB;
        sync();
        cr_writel(reg&0xfffff7ff, SOFT_RESET2);
		CP15ISB;
        sync();

		//[A01] 98000450[1]: reset test_mux_main2 soft reset
		if (get_rtd129x_cpu_revision() >= RTD129x_CHIP_REVISION_A01 ) {
			MMCPRINTF("reset CRT_DUMMY(0x%08x) \n", CRT_DUMMY);
			reg = cr_readl(CRT_DUMMY);
			CP15ISB;
			sync();
			cr_writel(reg&0xfffffffd, CRT_DUMMY);
			CP15ISB;
			sync();
			MMCPRINTF("reg(CRT_DUMMY) = 0x%08x \n", cr_readl(CRT_DUMMY));
		}
		
        //CRT release eMMC reset
        reg = cr_readl(SOFT_RESET2);
		CP15ISB;
        sync();
        cr_writel(reg|0x00000800, SOFT_RESET2);
		CP15ISB;
        sync();

		//[A01] 98000450[1]: release test_mux_main2 soft reset
		if (get_rtd129x_cpu_revision() >= RTD129x_CHIP_REVISION_A01 ) {
			MMCPRINTF("release CRT_DUMMY(0x%08x) \n", CRT_DUMMY);
			reg = cr_readl(CRT_DUMMY);
			CP15ISB;
			sync();
			cr_writel(reg | 0x00000002, CRT_DUMMY);
			CP15ISB;
			sync();
			MMCPRINTF("reg(CRT_DUMMY) = 0x%08x \n", cr_readl(CRT_DUMMY));
		}

		if (get_rtd129x_cpu_revision() >= RTD129x_CHIP_REVISION_A01 ) {
			cr_writel((~cr_readl(CR_EMMC_DUMMY_SYS)) & 0x40000000, CR_EMMC_DUMMY_SYS);
			CP15ISB;
			sync();
			udelay(200);
		}	

        cr_writel(gRegTbl.emmc_mux_pad0, CR_EMMC_muxpad0);
        cr_writel(gRegTbl.emmc_mux_pad1, CR_EMMC_muxpad1);
        cr_writel(gRegTbl.emmc_pfunc_nf1, CR_EMMC_PFUNC_NF1);
        cr_writel(gRegTbl.emmc_pdrive_nf1, CR_EMMC_PDRIVE_NF1);
        cr_writel(gRegTbl.emmc_pdrive_nf2, CR_EMMC_PDRIVE_NF2);
        cr_writel(gRegTbl.emmc_pdrive_nf3, CR_EMMC_PDRIVE_NF3);
        cr_writel(gRegTbl.emmc_ckgen_ctl, CR_EMMC_CKGEN_CTL);
        sync();

        rtkemmc_host_reset();

        cr_writel(gRegTbl.emmc_ctype, CR_EMMC_CTYPE);
        cr_writel(gRegTbl.emmc_uhsreg, CR_EMMC_UHSREG);
        cr_writel(gRegTbl.emmc_ddr_reg, CR_EMMC_DDR_REG);
        cr_writel(gRegTbl.emmc_card_thr_ctl, CR_EMMC_CARD_THR_CTL);
        cr_writel(gRegTbl.emmc_dqs_ctrl1, CR_EMMC_DQS_CTRL1);
        sync();

        cr_writel(0, CR_EMMC_CLKENA); // 0x10, clk enable, disable clock
        sync();

        cr_writel(0xa0202000, CR_EMMC_CMD); // 0x10, clk enable, disable clock
        sync();

        // 0x2c, wait for CIU to take the command
        wait_done_timeout((volatile u32 *)(uintptr_t)CR_EMMC_CMD, 0x80000000,0);
        cr_writel(gRegTbl.emmc_clk_div, CR_EMMC_CLKDIV);
        sync();

        cr_writel(0xa0202000, CR_EMMC_CMD);  // 0x2c = start_cmd, upd_clk_reg_only, wait_prvdata_complete
        sync();

        // 0x2c, wait for CIU to take the command
        wait_done_timeout((volatile u32 *)(uintptr_t)CR_EMMC_CMD, 0x80000000,0);

        cr_writel(0x10001, CR_EMMC_CLKENA); // 0x10, clk enable, disable clock
        sync();

        cr_writel(0xa0202000, CR_EMMC_CMD);  // 0x2c = start_cmd, upd_clk_reg_only, wait_prvdata_complete
        sync();

        // 0x2c, wait for CIU to take the command
        wait_done_timeout((volatile u32 *)(uintptr_t)CR_EMMC_CMD, 0x80000000,0);

}

int rtkemmc_send_cmd18(void)
{
	int ret_err=0;
    struct rtk_cmd_info cmd_info;
	struct mmc_cmd cmd_val;
	struct mmc_data data;
	e_device_type * card = &emmc_card;
	//int sts1_val=0;

	MY_CLR_ALIGN_BUFFER();	
	MY_ALLOC_CACHE_ALIGN_BUFFER(char, crd_tmp_buffer,  0x400);
	setRandomMemory((unsigned long)crd_tmp_buffer,0x400);
	MMCPRINTF("*** %s %s %d ***\n", __FILE__, __FUNCTION__, __LINE__);

	cmd_info.cmd= &cmd_val;
	cmd_info.data= &data;
	cmd_info.cmd->cmdarg = 0x100;
	cmd_info.cmd->cmdidx = MMC_CMD_READ_MULTIPLE_BLOCK;
	cmd_info.rsp_len	 = mmc_get_rsp_len(SD_R1);
	cmd_info.byte_count  = 0x200;
	cmd_info.block_count = 2;
	cmd_info.dma_buffer = (unsigned char *) crd_tmp_buffer;
	data.blocks = 2;
	data.dest = crd_tmp_buffer;
	cmd_info.xfer_flag	 = RTK_MMC_DATA_READ; //dma the result to ddr
	MMCPRINTF("*** %s %s %d ***, arg=0x%08x\n", __FILE__, __FUNCTION__, __LINE__,cmd_info.cmd->cmdarg);
	ret_err = rtkemmc_Stream_Cmd(&cmd_info, 1);
	MMCPRINTF("*** %s %s %d ***, arg=0x%08x\n", __FILE__, __FUNCTION__, __LINE__,cmd_info.cmd->cmdarg);
	
	if (ret_err)
	{
		//sts1_val = cr_readl(CR_EMMC_STATUS);
		//MMCPRINTF("[LY] status1 val=%02x\n", sts1_val);
		udelay(200);
		rtkemmc_stop_transmission(card,1);
		card_stop();
		polling_to_tran_state(MMC_CMD_READ_MULTIPLE_BLOCK,1);
	}
	//printf("The sts1_val is %d.\n",sts1_val);
	
	return ret_err;
}
int rtkemmc_send_cmd13(void)
{
	int ret_err=0;
	u32 sts_val=0;

	#ifdef MMC_DEBUG
	ret_err = rtkemmc_send_status(&sts_val, 1, 1);
	#else
	ret_err = rtkemmc_send_status(&sts_val, 0, 1);
	#endif
	
	return ret_err;
}
int rtkemmc_send_cmd25(void)
{
	int ret_err=0;
    struct rtk_cmd_info cmd_info;
	struct mmc_cmd cmd_val;
	struct mmc_data data;
	//int sts1_val=0;
	MY_CLR_ALIGN_BUFFER();
	MY_ALLOC_CACHE_ALIGN_BUFFER(char, crd_tmp_buffer,  0x400);
	setRandomMemory((unsigned long)crd_tmp_buffer,0x400);

	MMCPRINTF("\n %s %s %d cmdidx=0x%02x(%d), flags=0x%08x -------\n", __FILE__, __FUNCTION__, __LINE__, cmd->cmdidx, cmd->cmdidx, cmd->resp_type);
	MMCPRINTF("*** %s %s %d ***\n", __FILE__, __FUNCTION__, __LINE__);
	cmd_info.cmd= &cmd_val;
	cmd_info.data = &data;
	cmd_info.cmd->cmdarg = 0xfe;
	cmd_info.cmd->cmdidx = MMC_CMD_WRITE_MULTIPLE_BLOCK;
	cmd_info.rsp_len	 = mmc_get_rsp_len(SD_R1);
	cmd_info.byte_count  = 0x200;
	cmd_info.block_count = 2;
	data.blocks = 2;
	data.dest = crd_tmp_buffer;
	cmd_info.dma_buffer = (unsigned char *) crd_tmp_buffer;
	cmd_info.xfer_flag	 = RTK_MMC_DATA_WRITE; //dma the result to ddr

	MMCPRINTF("*** %s %s %d ***, arg=0x%08x\n", __FILE__, __FUNCTION__, __LINE__,cmd_info.cmd->cmdarg);
	ret_err = rtkemmc_Stream_Cmd(&cmd_info, 1);
	if (ret_err)
	{
		//sts1_val = cr_readl(CR_EMMC_STATUS);
		//MMCPRINTF("[LY] status1 val=%02x\n", sts1_val);
		card_stop();
		polling_to_tran_state(MMC_CMD_WRITE_MULTIPLE_BLOCK,1);
	}
	//printf("The sts1_val is %d.\n",sts1_val);
	return ret_err;
}
int rtkemmc_Stream( unsigned int cmd_idx,UINT32 blk_addr, UINT32 dma_addr, UINT32 dma_length, int bIgnore){
	UINT32 ret_error = 0;

	cr_writel(0, CR_EMMC_SWC_SEL);
    cr_writel(0, CR_EMMC_CP);

	CP15ISB;
	sync();

	MMCPRINTF("[%s:%d] cmd_idx = 0x%08x, blk_addr = 0x%08x, dma_addr = 0x%08x, dma_length = 0x%08x \n", __FILE__, __LINE__, cmd_idx, blk_addr, dma_addr, dma_length);
				   
	make_ip_des(dma_addr, dma_length);
	flush_cache(dma_addr, dma_length);
	
	CP15ISB;
	sync();

	cr_writel(dma_length, CR_EMMC_BYTCNT);
	cr_writel((uintptr_t)rw_descriptor, CR_EMMC_DBADDR);
	cr_writel(0x0000ffff, CR_EMMC_RINTSTS);
	cr_writel(0x0000ffff, CR_EMMC_INTMASK);
	cr_writel(blk_addr,CR_EMMC_CMDARG);		
	CP15ISB;
	sync();
	
	cr_writel(cmd_idx, CR_EMMC_CMD);
	CP15ISB;
	sync();

	if (!bIgnore){
		wait_done_timeout((UINT32 *)CR_EMMC_RINTSTS, 0x4, 0x4); //command done
		wait_done_timeout((UINT32 *)CR_EMMC_RINTSTS, 0x8, 0x8); //data transfer over

		CP15ISB;
		sync();

		if ((CMD_IDX_MASK(cmd_idx)==MMC_READ_MULTIPLE_BLOCK) ||(CMD_IDX_MASK(cmd_idx)==MMC_WRITE_MULTIPLE_BLOCK) ){
			wait_done_timeout((UINT32 *)CR_EMMC_RINTSTS, 0x4000, 0x4000); //auto command done (stop command done)
		}
	} 
	else
	{	//for tuning usage, fast quit method
    	if ((CMD_IDX_MASK(cmd_idx)==MMC_READ_MULTIPLE_BLOCK) ||(CMD_IDX_MASK(cmd_idx)==MMC_WRITE_MULTIPLE_BLOCK) ){
        	while ((cr_readl(CR_EMMC_RINTSTS)&0xffc2)==0);
    	}
    	else
    	{
        	while ((cr_readl(CR_EMMC_RINTSTS)&0xbfc6)==0);
    	}
	}
	

	if (!bIgnore){
		//read case : polling dma_done for safety
		if (CMD_IDX_MASK(cmd_idx)==MMC_READ_SINGLE_BLOCK || CMD_IDX_MASK(cmd_idx)==MMC_READ_MULTIPLE_BLOCK ||
			CMD_IDX_MASK(cmd_idx)==MMC_SEND_EXT_CSD || CMD_IDX_MASK(cmd_idx)==MMC_SEND_WRITE_PROT_TYPE) {

			if (dma_addr >= 0x20000 && dma_addr < 0xe0000){

				printf("panic: dma_addr = 0x%08x \n", dma_addr);
				while(1);
			}
			
			wait_done_timeout((UINT32 *)CR_EMMC_ISR, 0x2, 0x2); //dma_done_int
			cr_writel(0x2, CR_EMMC_ISR);
			CP15ISB;
			sync();
		}
	}
	//HS200 tuning case
	if (bIgnore) {
		if (check_error(bIgnore) == 0){ 
			//no error
			wait_done_timeout((UINT32 *)CR_EMMC_STATUS, 0x200, 0x0); 
			return 0;
		}
		else{
			if ((CMD_IDX_MASK(cmd_idx)==MMC_READ_MULTIPLE_BLOCK) && (cr_readl(CR_EMMC_RINTSTS) & 0xa0c0 )){
				realErrTuning = 1;
			}
			else if ((CMD_IDX_MASK(cmd_idx)==MMC_WRITE_MULTIPLE_BLOCK) && (cr_readl(CR_EMMC_RINTSTS) & 0x8180)){
				realErrTuning = 1;
			}
			return -1;
		}
	}
	 //normal case
	else{
		if ((ret_error = check_error(bIgnore))!=0){
			wait_done_timeout((UINT32 *)CR_EMMC_STATUS, 0x200, 0x0); 
			print_ip_desc();
			return ret_error;
		}
		else{
			//no error
			wait_done_timeout((UINT32 *)CR_EMMC_STATUS, 0x200, 0x0); 
			return 0;
		} 	
	}
}

/*******************************************************
 *
 *******************************************************/
void rtkemmc_show_cid( e_device_type *card )
{
	int i;
	unsigned int sn;
	unsigned char cid[16];
	for( i = 0; i < 4; i++ ) {
		cid[(i<<2)]   = ( card->raw_cid[i]>>24 ) & 0xFF;
		cid[(i<<2)+1] = ( card->raw_cid[i]>>16 ) & 0xFF;
		cid[(i<<2)+2] = ( card->raw_cid[i]>>8  ) & 0xFF;
		cid[(i<<2)+3] = ( card->raw_cid[i]     ) & 0xFF;
	}
#ifdef EMMC_SHOW_CID
    #ifdef THIS_IS_FLASH_WRITE_U_ENV
    prints("emmc:CID");
    #else
	MMCPRINTF("emmc:CID");
    #endif
	for( i = 0; i < 16; i++ ) {
        
        #ifdef THIS_IS_FLASH_WRITE_U_ENV
        print_hex(cid[i]);
        #else
		MMCPRINTF(" %02x", cid[i]);
        #endif
	}
    #ifdef THIS_IS_FLASH_WRITE_U_ENV
    prints("\n");
    #else
	MMCPRINTF("\n");
    #endif
#endif
    #ifdef THIS_IS_FLASH_WRITE_U_ENV
    prints("CID     0x");
    print_hex(cid[0]);
    prints("\n");
    #else
	MMCPRINTF("CID    0x%02x\n", cid[0]);
    #endif
	switch( (cid[1] & 0x3) ) {
		case 0:
            #ifdef THIS_IS_FLASH_WRITE_U_ENV
            prints("CBX    Card\n");
            #else
			MMCPRINTF("CBX    Card\n");
            #endif
            break;
		case 1:
            #ifdef THIS_IS_FLASH_WRITE_U_ENV
            prints("CBX    BGA\n");	
            #else
			MMCPRINTF("CBX    BGA\n");		
            #endif
            break;
		case 2:
            #ifdef THIS_IS_FLASH_WRITE_U_ENV
            prints("CBX    POP\n");
            #else
			MMCPRINTF("CBX    POP\n");		
            #endif
            break;
		case 3:
            #ifdef THIS_IS_FLASH_WRITE_U_ENV
            prints("CBX    Unknown\n");
            #else
			MMCPRINTF("CBX    Unknown\n");	
            #endif
            break;
	}
    #ifdef THIS_IS_FLASH_WRITE_U_ENV
    prints("OID    0x");
    print_val(cid[2],2);
    prints("\n");
    prints("PNM    0x");
    print_val(cid[3],2);
    print_val(cid[4],2);
    print_val(cid[5],2);
    print_val(cid[6],2);
    print_val(cid[7],2);
    print_val(cid[8],2);
    prints("\n");
    prints("PRV    0x");
    print_val((cid[9]>>4)&0xf,2);
    print_val(cid[9]&0xf,2);
    prints("\n");
    #else
	MMCPRINTF("OID    0x%02x\n", cid[2]);
	MMCPRINTF("PNM    %c%c%c%c%c%c\n", cid[3], cid[4], cid[5], cid[6], cid[7], cid[8]);
	MMCPRINTF("PRV    %d.%d\n", (cid[9]>>4)&0xf, cid[9]&0xf);
    #endif
	sn = cid[13];
	sn = (sn<<8) | cid[12];
	sn = (sn<<8) | cid[11];
	sn = (sn<<8) | cid[10];
    #ifdef THIS_IS_FLASH_WRITE_U_ENV
    prints("PSN    ");
    print_hex(sn);
    prints("\n");
    #else
	MMCPRINTF("PSN    %u(0x%08x)\n", sn, sn);
    #endif
	if( cid[9] ) {
        #ifdef THIS_IS_FLASH_WRITE_U_ENV
		prints("MDT    ");
        print_hex((cid[9]>>4)&0xf);
        print_hex((cid[14]&0xf)+1997);
        prints("\n");
        #else
		MMCPRINTF("MDT    %02d/%d)", (cid[9]>>4)&0xf, (cid[14]&0xf)+1997);
        #endif
	}
	else {
        #ifdef THIS_IS_FLASH_WRITE_U_ENV
        prints("MDT    --/----\n");
        #else
		MMCPRINTF("MDT    --/----\n", (cid[9]>>4)&0xf, (cid[14]&0xf)+1997);
        #endif
	}
}


/*******************************************************
 *
 *******************************************************/
int mmc_decode_csd( struct mmc* mmc )
{
    struct rtk_mmc_csd vcsd;
    struct rtk_mmc_csd *csd = (struct rtk_mmc_csd*)&vcsd;
    unsigned int e, m;
    unsigned int * resp = mmc->csd;
    int err = 0;

    printf("mmc_decode_csd\n");
    memset(&vcsd, 0x00, sizeof(struct rtk_mmc_csd));

  /*
     * We only understand CSD structure v1.1 and v1.2.
     * v1.2 has extra information in bits 15, 11 and 10.
     * We also support eMMC v4.4 & v4.41.
     */
    csd->csd_ver2 = 0xff;
    csd->csd_ver = UNSTUFF_BITS(resp, 126, 2);

    // 0, CSD Ver. 1.0
    // 1, CSD Ver. 1.1
    // 2, CSD Ver. 1.2, define in spec. 4.1-4.3
    // 3, CSD Ver define in EXT_CSD[194]
    //    EXT_CSD[194] 0, CSD Ver. 1.0
    //                 1, CSD Ver. 1.1
    //                 2, CSD Ver. 1.2, define in spec. 4.1-4.51
    //                 others, RSV

    csd->mmca_vsn       = UNSTUFF_BITS(resp, 122, 4);
    m = UNSTUFF_BITS(resp, 115, 4);
    e = UNSTUFF_BITS(resp, 112, 3);
    csd->tacc_ns        = (tacc_exp[e] * tacc_mant[m] + 9) / 10;
    csd->tacc_clks      = UNSTUFF_BITS(resp, 104, 8) * 100;

    m = UNSTUFF_BITS(resp, 99, 4);
    e = UNSTUFF_BITS(resp, 96, 3);
    csd->max_dtr        = tran_exp[e] * tran_mant[m];
    csd->cmdclass       = UNSTUFF_BITS(resp, 84, 12);

    m = UNSTUFF_BITS(resp, 62, 12);
    e = UNSTUFF_BITS(resp, 47, 3);
    csd->capacity       = (1 + m) << (e + 2);
    csd->read_blkbits   = UNSTUFF_BITS(resp, 80, 4);
    csd->read_partial   = UNSTUFF_BITS(resp, 79, 1);
    csd->write_misalign = UNSTUFF_BITS(resp, 78, 1);
    csd->read_misalign  = UNSTUFF_BITS(resp, 77, 1);
    csd->r2w_factor     = UNSTUFF_BITS(resp, 26, 3);
    csd->write_blkbits  = UNSTUFF_BITS(resp, 22, 4);
    csd->write_partial  = UNSTUFF_BITS(resp, 21, 1);

    printf("CSD_STRUCTURE :%02x\n", csd->csd_ver);
    printf("SPEC_VERS   :%02x\n", csd->mmca_vsn);
    printf("TRAN_SPEED  :%02x\n", UNSTUFF_BITS(resp, 96, 8));
    printf("C_SIZE      :%08x\n",m);
    printf("C_SIZE_MULT :%08x\n",e);
    printf("Block Num   :%08x\n",csd->capacity);
    printf("Block Len   :%08x\n" ,1<<csd->read_blkbits);
    printf("Total Bytes :%08x\n",csd->capacity*(1<<csd->read_blkbits));
//err_out:
    return err;
}

/*******************************************************
 *
 *******************************************************/
int mmc_decode_cid( struct mmc * rcard )
{
    e_device_type card;
    unsigned int * resp = rcard->cid;
    unsigned int * resp1 = rcard->csd;
    uint vsn = UNSTUFF_BITS(resp1, 122, 4);

    printf("mmc_decode_cid\n");
    /*
     * The selection of the format here is based upon published
     * specs from sandisk and from what people have reported.
     */
    switch (vsn) {
    case 0: /* MMC v1.0 - v1.2 */
    case 1: /* MMC v1.4 */
        card.cid.manfid        = UNSTUFF_BITS(resp, 104, 24);
        card.cid.prod_name[0]  = UNSTUFF_BITS(resp, 96, 8);
        card.cid.prod_name[1]  = UNSTUFF_BITS(resp, 88, 8);
        card.cid.prod_name[2]  = UNSTUFF_BITS(resp, 80, 8);
        card.cid.prod_name[3]  = UNSTUFF_BITS(resp, 72, 8);
        card.cid.prod_name[4]  = UNSTUFF_BITS(resp, 64, 8);
        card.cid.prod_name[5]  = UNSTUFF_BITS(resp, 56, 8);
        card.cid.prod_name[6]  = UNSTUFF_BITS(resp, 48, 8);
        card.cid.hwrev         = UNSTUFF_BITS(resp, 44, 4);
        card.cid.fwrev         = UNSTUFF_BITS(resp, 40, 4);
        card.cid.serial        = UNSTUFF_BITS(resp, 16, 24);
        card.cid.month         = UNSTUFF_BITS(resp, 12, 4);
        card.cid.year          = UNSTUFF_BITS(resp, 8,  4) + 1997;
        printf("cid v_1.0-1.4, manfid=%02x\n", card.cid.manfid);
        break;

    case 2: /* MMC v2.0 - v2.2 */
    case 3: /* MMC v3.1 - v3.3 */
    case 4: /* MMC v4 */
        card.cid.manfid        = UNSTUFF_BITS(resp, 120, 8);
        card.cid.oemid         = UNSTUFF_BITS(resp, 104, 16);
        card.cid.prod_name[0]  = UNSTUFF_BITS(resp, 96, 8);
        card.cid.prod_name[1]  = UNSTUFF_BITS(resp, 88, 8);
        card.cid.prod_name[2]  = UNSTUFF_BITS(resp, 80, 8);
        card.cid.prod_name[3]  = UNSTUFF_BITS(resp, 72, 8);
        card.cid.prod_name[4]  = UNSTUFF_BITS(resp, 64, 8);
        card.cid.prod_name[5]  = UNSTUFF_BITS(resp, 56, 8);
        card.cid.serial        = UNSTUFF_BITS(resp, 16, 32);
        card.cid.month         = UNSTUFF_BITS(resp, 12, 4);
        card.cid.year          = UNSTUFF_BITS(resp, 8, 4) + 1997;
        printf("cid v_2.0-4, manfid=%02x, cbx=%02x\n", card.cid.manfid, UNSTUFF_BITS(resp, 112, 2));
        break;

    default:
        //printf("card has unknown MMCA version %d\n",
         //       card.csd.mmca_vsn);
        return -1;
    }

    return 0;
}

/*******************************************************
 *
 *******************************************************/
void mmc_show_csd( struct mmc* card )
{
	int i;
	unsigned char csd[16];
	for( i = 0; i < 4; i++ ) {
		csd[(i<<2)]   = ( card->csd[i]>>24 ) & 0xFF;
		csd[(i<<2)+1] = ( card->csd[i]>>16 ) & 0xFF;
		csd[(i<<2)+2] = ( card->csd[i]>>8  ) & 0xFF;
		csd[(i<<2)+3] = ( card->csd[i]     ) & 0xFF;
	}
#ifdef MMC_DEBUG
	printf("emmc:CSD(hex)");
	for( i = 0; i < 16; i++ ) {
		printf(" %02x", csd[i]);
	}
	printf("\n");
#endif
	printf(" %02x", csd[0]);
	mmc_decode_csd(card);
}

/*******************************************************
 *
 *******************************************************/
void mmc_show_ext_csd( unsigned char * pext_csd )
{
	int i,j,k;
	unsigned int sec_cnt;
	unsigned int boot_size_mult;

	printf("emmc:EXT CSD\n");
	k = 0;
	for( i = 0; i < 32; i++ ) {
		printf("    : %03x", i<<4);
		for( j = 0; j < 16; j++ ) {
			printf(" %02x ", pext_csd[k++]);
		}
		printf("\n");
	}
	printf("    :k=%02x\n",k);

	boot_size_mult = pext_csd[226];
    
	printf("emmc:BOOT PART %04x ",boot_size_mult<<7);
    printf(" Kbytes(%04x)\n", boot_size_mult);
    
	sec_cnt = pext_csd[215];
	sec_cnt = (sec_cnt<<8) | pext_csd[214];
	sec_cnt = (sec_cnt<<8) | pext_csd[213];
	sec_cnt = (sec_cnt<<8) | pext_csd[212];

	printf("emmc:SEC_COUNT %04x\n", sec_cnt);
	printf(" emmc:reserve227 %02x\n", pext_csd[227]);
	printf(" emmc:reserve240 %02x\n", pext_csd[240]);
	printf(" emmc:reserve254 %02x\n", pext_csd[254]);
	printf(" emmc:reserve256 %02x\n", pext_csd[256]);
	printf(" emmc:reserve493 %02x\n", pext_csd[493]);
	printf(" emmc:reserve505 %02x\n", pext_csd[505]);
}


/*******************************************************
 *
 *******************************************************/
int mmc_read_ext_csd( e_device_type * card )
{
    struct rtk_cmd_info cmd_info;
    struct mmc_cmd cmd;
	struct mmc_data data;
    unsigned int rsp_type;
    int ret_err;

    #ifdef THIS_IS_FLASH_WRITE_U_ENV
    prints("mmc_read_ext_csd\n");
    #else
    MMCPRINTF("mmc_read_ext_csd\n");
    #endif

    cmd_info.cmd= &cmd;
	cmd_info.data= &data;
    cmd.cmdarg     = 0;
    cmd.cmdidx = MMC_SEND_EXT_CSD;
	data.blocks = 1;
	data.dest = (char *) sys_ext_csd_addr;

    rsp_type = mmc_get_rsp_type(&cmd);

    MMCPRINTF("ext_csd ptr 0x%p\n",sys_ext_csd_addr);

    cmd_info.rsp_len     = mmc_get_rsp_len(rsp_type);
    cmd_info.byte_count  = 0x200;
    cmd_info.block_count = 1;
    cmd_info.dma_buffer = sys_ext_csd_addr;
    cmd_info.xfer_flag   = RTK_MMC_DATA_READ;

	

    ret_err = rtkemmc_Stream_Cmd(&cmd_info, 0);

    if(ret_err){
        #ifdef THIS_IS_FLASH_WRITE_U_ENV
        prints("unable to read EXT_CSD(ret_err=");
        print_hex(ret_err);
        prints("\n");
        #else
        MMCPRINTF("unable to read EXT_CSD(ret_err=%d)", ret_err);
        #endif
    }
    else{
    	mmc_show_ext_csd(sys_ext_csd_addr);

		card->ext_csd.boot_blk_size = (*(ptr_ext_csd+226)<<8);
        card->csd.csd_ver2 = *(ptr_ext_csd+194);
        card->ext_csd.rev = *(ptr_ext_csd+192);
        card->ext_csd.part_cfg = *(ptr_ext_csd+179);
        card->ext_csd.boot_cfg = *(ptr_ext_csd+178);
        card->ext_csd.boot_wp_sts = *(ptr_ext_csd+174);
        card->ext_csd.boot_wp = *(ptr_ext_csd+173);
		card->curr_part_indx = card->ext_csd.part_cfg & 0x07;

        #ifdef THIS_IS_FLASH_WRITE_U_ENV
		prints("emmc:BOOT PART MULTI = 0x");
        print_hex(*(ptr_ext_csd+226));
        prints(", BP_BLKS=0x");
        print_hex(*(ptr_ext_csd+226)<<8);
        prints("\n");
		prints("emmc:BOOT PART CFG = 0x");
        print_hex(card->ext_csd.part_cfg);
        prints("(0x");
        print_hex(card->curr_part_indx);
        prints(")\n");
        #else
		MMCPRINTF("emmc:BOOT PART MULTI = 0x%02x, BP_BLKS=0x%08x\n", *(ptr_ext_csd+226), *(ptr_ext_csd+226)<<8);
		MMCPRINTF("emmc:BOOT PART CFG = 0x%02x(%d)\n", card->ext_csd.part_cfg, card->curr_part_indx);
        #endif

		if (card->ext_csd.rev > 6) {
            #ifdef THIS_IS_FLASH_WRITE_U_ENV
            prints("unrecognized EXT_CSD structure version ");
            print_hex(card->ext_csd.rev);
            prints(", please update fw\n", card->ext_csd.rev);
            #else
            MMCPRINTF("unrecognized EXT_CSD structure version %d, please update fw\n", card->ext_csd.rev);
            #endif
        }

        if (card->ext_csd.rev >= 2) {
            card->ext_csd.sectors = *((unsigned int *)(ptr_ext_csd+EXT_CSD_SEC_CNT));
        }

        switch (*(ptr_ext_csd+EXT_CSD_CARD_TYPE) & (EXT_CSD_CARD_TYPE_26|EXT_CSD_CARD_TYPE_52)) {
	        case EXT_CSD_CARD_TYPE_52 | EXT_CSD_CARD_TYPE_26:
	            card->ext_csd.hs_max_dtr = 52000000;
	            break;
	        case EXT_CSD_CARD_TYPE_26:
	            card->ext_csd.hs_max_dtr = 26000000;
	            break;
	        default:
	            /* MMC v4 spec says this cannot happen */
                #ifdef THIS_IS_FLASH_WRITE_U_ENV
                prints("card is mmc v4 but does not support any high-speed modes.\n");
                #else
	            MMCPRINTF("card is mmc v4 but doesn't " "support any high-speed modes.\n");
                #endif
        }

        if (card->ext_csd.rev >= 3) {
            unsigned int sa_shift = *(ptr_ext_csd+EXT_CSD_S_A_TIMEOUT);
            /* Sleep / awake timeout in 100ns units */
            if (sa_shift > 0 && sa_shift <= 0x17){
                card->ext_csd.sa_timeout = 1 << *(ptr_ext_csd+EXT_CSD_S_A_TIMEOUT);
            }
        }
    }

    return ret_err;
}



/*******************************************************
 *
 *******************************************************/
int rtkemmc_hw_reset_signal( void )
{
	unsigned int tmp_mux;
	unsigned int tmp_dir;
	unsigned int tmp_dat;

	#define PIN_MUX_REG		(0xb8000814UL)
	#define PIN_DIR_REG		(0xb801bc00UL)
	#define PIN_DAT_REG		(0xb801bc18UL)

	tmp_mux = cr_readl( PIN_MUX_REG );
	tmp_dir = cr_readl( PIN_DIR_REG );
	tmp_dat = cr_readl( PIN_DAT_REG );

	cr_writel( tmp_dat|(1<<20), PIN_DAT_REG );
	cr_writel( tmp_dir|(1<<20), PIN_DIR_REG );
	cr_writel( tmp_dat|(1<<20), PIN_DAT_REG ); // high

	cr_writel( tmp_mux|(0xF<<28), PIN_MUX_REG );

	cr_writel( tmp_dat&~(1<<20), PIN_DAT_REG );  // low
	udelay(10);
	cr_writel( tmp_dat|(1<<20), PIN_DAT_REG ); // high

	cr_writel( tmp_mux, PIN_MUX_REG ); // restore original status

	return 0;
}

void set_emmc_pin_mux(void)
{
        //1195
        //set default i/f to cr
        unsigned int reg_val=0;
        reg_val = REG32(SYS_muxpad0);
    	reg_val &= ~0xFFFF0C3C;
        reg_val |= 0xaaaa0828;
        REG32(SYS_muxpad0) = reg_val;
		//emmc:pfunc_nf1
		REG32(CR_EMMC_PFUNC_NF1) = 0x33333333;
		
}




int cmd23_request(struct mmc *mmc, struct mmc_cmd *cmd, struct mmc_data *data){
	int error = -1;
	unsigned int _cmd_arg = (cmd->cmdarg);
	unsigned int _cmd     =  (cmd->cmdidx);

	//printf("cmd is 0x%x\n", _cmd);
	//printf("cmd arg is 0x%x\n", _cmd_arg);
	
	cr_writel(0x0000fffe , CR_EMMC_RINTSTS); 
	cr_writel(0x00000004 , CR_EMMC_INTMASK);
	cr_writel(0x02000000 , CR_EMMC_CTRL);
	cr_writel( _cmd_arg,CR_EMMC_CMDARG); //arg
	sync();
	cr_writel( (0xa0000000 | _cmd | (1<<6) | (1<<8)), CR_EMMC_CMD);//cmd
	sync();

	cr_writel( 0x02000010,CR_EMMC_CTRL);
	while( (cr_readl(CR_EMMC_RINTSTS) & 0xffce) == 0);

	wait_done_timeout((volatile u32 *)CR_EMMC_RINTSTS , 0x4  , 0x4);
	wait_done_timeout((volatile u32 *)CR_EMMC_RINTSTS , 0x200, 0x0);	

//	printf("%s : Line %d: func:%s \n", __FILE__, __LINE__,__func__);
	error =check_error(0);
	//printf("check error value is %x\n",error);

	/*for(i=0; i<4; i++){
			printf("Rsp[%d]", i);
			printf("[0x%x]=", 0x98012030+i*4);
			printf("0x%x\n", cr_readl(((volatile u32 *)0x98012030+i*4)));
		}*/
	//	printf("%s : Line %d: func:%s \n", __FILE__, __LINE__,__func__);
	//	printf("cmd 23 resp[0] is 0x%x\n",cr_readl(CR_EMMC_RESP0));
	//	Print_Device_Status(cr_readl(CR_EMMC_RESP0));
		
	
	return error;
}


int cmd25_request(struct mmc * mmc,
						struct mmc_cmd * cmd,
						struct mmc_data * data )
{

	int error = -1;
	cr_writel(0, CR_EMMC_SWC_SEL);
    cr_writel(0, CR_EMMC_CP);

	
	make_ip_des((UINT64) data->src,0x200);

	//printf("------ cmd  25 request----------------\n");
//printf("data src address is 0x%x \n",data->src);
	//printf("descriptor address is 0x%x \n",rw_descriptor);
	//printf("------ cmd  25 request----------------\n");

	

	cr_writel(0xfffe,CR_EMMC_RINTSTS);
	
	cr_writel(0x200,CR_EMMC_BYTCNT); //BYTE COUNT
	cr_writel((uintptr_t)rw_descriptor,CR_EMMC_DBADDR); 
	cr_writel(0xffff,CR_EMMC_INTMASK); 

	cr_writel(cmd->cmdarg,CR_EMMC_CMDARG);   //cmd arg
	sync();
	
	cr_writel(cmd->cmdidx | 0xa0002740,CR_EMMC_CMD);   //cmd

	//printf("rintsts 0x%x\n",cr_readl(CR_EMMC_RINTSTS) );
	//printf("cmd arg 0x%x\n", cmd->arg );
	//printf("cmd  0x%x\n", cmd->opcode);
	//printf("rintsts 0x%x\n",cr_readl(CR_EMMC_RINTSTS) );
	//printf("intmask 0x%x\n",cr_readl(CR_EMMC_INTMASK) );
	//printf("mintsts 0x%x\n",cr_readl(CR_EMMC_MINTSTS) );

	while((cr_readl(CR_EMMC_RINTSTS) & 0xbfca) ==0);
	wait_done_timeout((unsigned int *)CR_EMMC_STATUS , 0x200 , 0x0); //date busy

	sync();

	error = check_error(0);
	
	//printf("%s : Line %d: func:%s \n", __FILE__, __LINE__,__func__);
	//printf("cmd 25 resp[0] is 0x%x\n",cr_readl(CR_EMMC_RESP0));
//	Print_Device_Status(cr_readl(CR_EMMC_RESP0));
	
	
	return error;
}

int cmd18_request(struct mmc * mmc,
						struct mmc_cmd * cmd,
						struct mmc_data * data )
{
	//printf("%s : Line %d: func:%s \n", __FILE__, __LINE__,__func__);

	int error = -1;
	cr_writel(0, CR_EMMC_SWC_SEL);
    cr_writel(0, CR_EMMC_CP);

	make_ip_des((UINT64) data->src,0x200);

	//printf("------ cmd  25 request----------------\n");
//printf("data src address is 0x%x \n",data->src);
	//printf("descriptor address is 0x%x \n",rw_descriptor);
	//printf("------ cmd  25 request----------------\n");

	

	cr_writel(0xfffe,CR_EMMC_RINTSTS);
	
	cr_writel(0X200,CR_EMMC_BYTCNT); //BYTE COUNT
	cr_writel((uintptr_t)rw_descriptor,CR_EMMC_DBADDR); 
	cr_writel(0xffff,CR_EMMC_INTMASK); 

	cr_writel(cmd->cmdarg,CR_EMMC_CMDARG);   //cmd arg
	sync();
	
	cr_writel(cmd->cmdidx | 0xa0002340,CR_EMMC_CMD);   //cmd

	//printf("rintsts 0x%x\n",cr_readl(CR_EMMC_RINTSTS) );
	//printf("cmd arg 0x%x\n", cmd->arg );
	//printf("cmd  0x%x\n", cmd->opcode);
	//printf("rintsts 0x%x\n",cr_readl(CR_EMMC_RINTSTS) );
	//printf("intmask 0x%x\n",cr_readl(CR_EMMC_INTMASK) );
	//printf("mintsts 0x%x\n",cr_readl(CR_EMMC_MINTSTS) );

	while((cr_readl(CR_EMMC_RINTSTS) & 0xbfca) ==0);
	wait_done_timeout((unsigned int *)CR_EMMC_STATUS , 0x200 , 0x0); //card busy

	wait_done_timeout((UINT32 *)CR_EMMC_ISR, 0x2, 0x2); //dma done
	sync();

//	printf("cmd 18 resp[0] is 0x%x\n",cr_readl(CR_EMMC_RESP0));
//	Print_Device_Status(cr_readl(CR_EMMC_RESP0));

	error = check_error(0);
	
	return error;
}

int rtkemmc_request(
			struct mmc * mmc,
			struct mmc_cmd * cmd,
			struct mmc_data * data )
{    
	int ret_err=0;
    volatile struct rtk_cmd_info cmd_info;

	MMCPRINTF("\n*** %s %s %d, cmdidx=0x%02x(%d), flags=0x%08x -------\n", __FILE__, __FUNCTION__, __LINE__, cmd->cmdidx, cmd->cmdidx, cmd->resp_type);


    if (data)
    {
      	MMCPRINTF("*** %s %s %d, flags=0x%08x(%s), blks=%d, blksize=%d\n", __FILE__, __FUNCTION__, __LINE__, data->flags, (data->flags&MMC_DATA_READ) ? "R" : "W", data->blocks, data->blocksize);
        cmd_info.cmd = cmd;
		cmd_info.data = data;
        ret_err = rtkemmc_Stream_Cmd( (struct rtk_cmd_info*) &cmd_info, 0);

    }
    else
    {
    	cmd_info.cmd = cmd;
		cmd_info.data = NULL;
    	ret_err = rtkemmc_SendCMDGetRSP( (struct rtk_cmd_info*) &cmd_info, 0 );
    }
	return ret_err;
}//0=success !0=fail

void rtkemmc_set_ios(struct mmc * mmc, unsigned int ios_caps)
{
	MMCPRINTF("*** %s %s %d, caps=0x%08x bw=%d, clk=%d\n", __FILE__, __FUNCTION__, __LINE__, ios_caps, mmc->bus_width, mmc->clock);

	// mmc->ldo
	
	
	// mmc->clk mode
	if(ios_caps & MMC_IOS_CLK) {
		if( mmc->mode_sel & MMC_MODE_HS200 ) {
			rtkemmc_set_mode_selection(MODE_SD30);
			rtkemmc_set_freq(0xaf);  //200Mhz
            		rtkemmc_set_div(EMMC_CLOCK_DIV_NON);
			MMCPRINTF("speed to hs200\n");
		}
		else if( mmc->mode_sel & MMC_MODE_HSDDR_52MHz ) {
			rtkemmc_set_mode_selection(MODE_DDR);
			rtkemmc_set_freq(0x57);  //10Mhz
			rtkemmc_set_div(EMMC_CLOCK_DIV_NON);
			MMCPRINTF("speed to 80\n");
		}
		else if( mmc->mode_sel & (MMC_MODE_HS|MMC_MODE_HS_52MHz)){
			rtkemmc_set_mode_selection(MODE_SD20);
			rtkemmc_set_freq(0x57);  //100Mhz
			rtkemmc_set_div(EMMC_CLOCK_DIV_2); //100MHZ /2 = 50MHZ
			MMCPRINTF("speed to 100\n");
		}
		else {
			//legacy
			rtkemmc_set_freq(0x46);  //80Mhz
			rtkemmc_set_div(EMMC_CLOCK_DIV_256);
			MMCPRINTF("speed to \n");
		}
			
	}

	// mmc->bus_width
	if(ios_caps & MMC_IOS_BUSWIDTH)
	{
		if( mmc->bus_width == 1 ) {
			rtkemmc_set_bits(REG_BUS_WIDTH_1);
		}
		else if( mmc->bus_width == 4 ) {
			rtkemmc_set_bits(REG_BUS_WIDTH_4);
		}
		else if( mmc->bus_width == 8 ) {
			rtkemmc_set_bits(REG_BUS_WIDTH_8);
		}
		else {
			UPRINTF("*** %s %s %d, ERR bw=%d, clk=%d\n", __FILE__, __FUNCTION__, __LINE__, mmc->bus_width, mmc->clock);
		}
	}

}

int rtkemmc_init(void){
	
	//Intialize
	cr_writel(0x00000081, CR_EMMC_BMOD);
	CP15ISB;
	sync();
	cr_writel(0x02000000, CR_EMMC_CTRL);
	CP15ISB;
	sync();
	cr_writel(0x00000001, CR_EMMC_PWREN);
	CP15ISB;
	sync();
	cr_writel(0x0000ffff, CR_EMMC_INTMASK);
	CP15ISB;
	sync();
	cr_writel(0xffffffff, CR_EMMC_RINTSTS);
	CP15ISB;
	sync();
	cr_writel(0x00000080, CR_EMMC_CLKDIV);
	CP15ISB;
	sync();
	cr_writel(0x00000000, CR_EMMC_CLKSRC);
	CP15ISB;
	sync();
	cr_writel(0x0001ffff, CR_EMMC_CLKENA);
	CP15ISB;
	sync();
	cr_writel(0xa0200000, CR_EMMC_CMD);
	CP15ISB;
	sync();
	cr_writel(0xffffff40, CR_EMMC_TMOUT);
	CP15ISB;
	sync();
	cr_writel(0x00000000, CR_EMMC_CTYPE);
	CP15ISB;
	sync();
	cr_writel(0x007f007f, CR_EMMC_FIFOTH);
	CP15ISB;
	sync();
	cr_writel(0x02000010, CR_EMMC_CTRL);
	CP15ISB;
	sync();
	cr_writel(0x00000080, CR_EMMC_BMOD);
	CP15ISB;
	sync();
	cr_writel(0x0000ffcf, CR_EMMC_INTMASK);
	CP15ISB;
	sync();
	//cr_writel(0x00600000, CR_EMMC_DBADDR);
	cr_writel(0x00000000, CR_EMMC_IDINTEN);
	CP15ISB;
	sync();
	cr_writel(0x0000ffff, CR_EMMC_RINTSTS);
	CP15ISB;
	sync();
	cr_writel(0x00000001, CR_EMMC_UHSREG);

	//disable SSC
	//cr_writel(0x4511893, PLL_EMMC2);
	//CP15ISB;
	//sync();

	CP15ISB;
	sync();

	
	return 0;
}


/*******************************************************
 *
 *******************************************************/
void rtkemmc_init_setup( void )
{   
    set_emmc_pin_mux();
	#ifdef MMC_DEBUG 
	printf("[LY] gCurrentBootMode =%d\n",gCurrentBootMode);
	#endif
	gCurrentBootMode = MODE_SD20;
	rtkemmc_debug_msg = 1;
	rtkemmc_off_error_msg_in_init_flow = 1;
	sys_rsp17_addr = S_RSP17_ADDR;   //set rsp buffer addr
	sys_ext_csd_addr = (unsigned char *)S_EXT_CSD_ADDR;
	ptr_ext_csd = (UINT8*)sys_ext_csd_addr;
	memset((struct backupRegs*)&gRegTbl, 0x00, sizeof(struct backupRegs));
	emmc_card.rca = 1<<16;
    emmc_card.sector_addressing = 0;

#define CONFIG_FT_TEST
#ifdef CONFIG_FT_TEST
	REG32(PLL_EMMC1) = 0x1003;              //LDO1.8V
#else
	REG32(PLL_EMMC1) = 0x83;     			 //LDO1.8V
#endif
	REG32(CR_EMMC_PAD_CTL) = 0;              //PAD to 1.8V

	rtkemmc_init();

	udelay(10000);
	
#ifdef CONFIG_FT_TEST	
	rtkemmc_set_pad_driving(0x77, 0x77,0x77,0x77);
#else
	rtkemmc_set_pad_driving(0x33, 0x33,0x33,0x33);
#endif

   	rtkemmc_set_div(EMMC_INIT_CLOCK_DIV);
	sync();
	//return 0;
}

/*******************************************************
 *
 *******************************************************/
 //emmc init flow that for fast init purpose. (for romcode)
int mmc_initial( int reset_only )
{

    if (reset_only)
    {
        rtkemmc_init_setup();
#ifdef MMC_DEBUG
    	printf("\nemmc : PLL_EMMC2 = 0x%08x",cr_readl(PLL_EMMC2));
    	printf("\nemmc : PLL_EMMC3 = 0x%08x",cr_readl(PLL_EMMC3));
    	printf("\nemmc : CR_EMMC_CLKDIV= 0x%08x",cr_readl(CR_EMMC_CLKDIV));
    	printf("\nemmc : SYS_NF_CKSEL = 0x%08x",cr_readl(SYS_NF_CKSEL));
    	printf("\nemmc : SYS_muxpad0 = 0x%08x",cr_readl(SYS_muxpad0));
#endif     
    }
	return 0;
}
void rtkemmc_set_pad_driving(unsigned int clk_drv, unsigned int cmd_drv, unsigned int data_drv, unsigned int ds_drv)
{   
    cr_writel(data_drv|(data_drv<<8)|(data_drv<<16)|(data_drv<<24), CR_EMMC_PDRIVE_NF1); //d0~d3        
    cr_writel(data_drv|(data_drv<<8)|(data_drv<<16)|(data_drv<<24), CR_EMMC_PDRIVE_NF2); //d4~d7        
    cr_writel((cr_readl(CR_EMMC_PDRIVE_NF3)&(0x00ff00ff))|(clk_drv<<8)|(cmd_drv<<24), CR_EMMC_PDRIVE_NF3); //d4~d7  
    cr_writel(ds_drv, CR_EMMC_PDRIVE_NF4); //data strobe
    sync();

    return;
}

static void
emmc_info_show(void)
{
    MMCPRINTF("%s(%u)\n",__func__,__LINE__);
    MMCPRINTF("EMMC_STATUS=0x%08x SYS_PLL_EMMC1=0x%08x SYS_PLL_EMMC2=0x%08x \nSYS_PLL_EMMC3=0x%08x SYS_PLL_EMMC4=0x%08x EMMC_RINTSTS=0x%08x \nEMMC_IDSTS=0x%08x muxpad0=0x%08x muxpad1=0x%08x \nEMMC_PFUNC_NF1=0x%08x EMMC_PDRIVE_NF1=0x%08x EMMC_PDRIVE_NF2=0x%08x \nEMMC_PDRIVE_NF3=0x%08x EMMC_CTYPE=0x%08x EMMC_UHSREG=0x%08x \nEMMC_DDR_REG=0x%08x EMMC_CARD_THR_CTL=0x%08x EMMC_CLKDIV=0x%08x \nEMMC_CKGEN_CTL=0x%08x EMMC_DQS_CTRL1=0x%08x \n",cr_readl(CR_EMMC_STATUS),cr_readl(PLL_EMMC1),cr_readl(PLL_EMMC2),cr_readl(PLL_EMMC3),cr_readl(PLL_EMMC4),cr_readl(CR_EMMC_RINTSTS), cr_readl(CR_EMMC_IDSTS), cr_readl(CR_EMMC_muxpad0),cr_readl(CR_EMMC_muxpad1),cr_readl(CR_EMMC_PFUNC_NF1),cr_readl(CR_EMMC_PDRIVE_NF1),cr_readl(CR_EMMC_PDRIVE_NF2),cr_readl(CR_EMMC_PDRIVE_NF3),cr_readl(CR_EMMC_CTYPE),cr_readl(CR_EMMC_UHSREG),cr_readl(CR_EMMC_DDR_REG),cr_readl(CR_EMMC_CARD_THR_CTL),cr_readl(CR_EMMC_CLKDIV),cr_readl(CR_EMMC_CKGEN_CTL),cr_readl(CR_EMMC_DQS_CTRL1));
}

/*
static void rtkemmc_dump_registers()
{
    printf("%s : \n", __func__);
    printf("EMMC_muxpad0 = 0x%08x \n", cr_readl(CR_EMMC_muxpad0));
    printf("EMMC_PFUNC_NF1 = 0x%08x \n", cr_readl(CR_EMMC_PFUNC_NF1));
    printf("EMMC_PDRIVE_NF1 = 0x%08x \n", cr_readl(CR_EMMC_PDRIVE_NF1));
    printf("EMMC_PDRIVE_NF2 = 0x%08x \n", cr_readl(CR_EMMC_PDRIVE_NF2));
    printf("EMMC_PDRIVE_NF3 = 0x%08x \n", cr_readl(CR_EMMC_PDRIVE_NF3));
    printf("EMMC_CTYPE = 0x%08x \n", cr_readl(CR_EMMC_CTYPE));
    printf("EMMC_UHSREG = 0x%08x \n", cr_readl(CR_EMMC_UHSREG));
    printf("EMMC_DDR_REG = 0x%08x \n", cr_readl(CR_EMMC_DDR_REG));
    printf("EMMC_CARD_THR_CTL = 0x%08x \n", cr_readl(CR_EMMC_CARD_THR_CTL));
    printf("EMMC_CLKDIV = 0x%08x \n", cr_readl(CR_EMMC_CLKDIV));
    printf("EMMC_CKGEN_CTL = 0x%08x \n", cr_readl(CR_EMMC_CKGEN_CTL));

    sync();

    return;
}
*/

#if 0
static void rtkemmc_set_ip_div(u32 set_div)
{
    unsigned long flags;
        u32 cur_div = cr_readl(CR_EMMC_CLKDIV);
        if (cur_div == set_div){
                printf("set_ip_div = cur_div(0x%08x), ignored. \n", cur_div);
                return;
        }

    //disable clock
    cr_writel(0, CR_EMMC_CLKENA);
    sync();

    //EMMC Cmd
    cr_writel(0xa0202000, CR_EMMC_CMD);
    sync();
    wait_done_timeout((u32*)CR_EMMC_CMD, 0x80000000, 0x0);
    sync();

    //set divider
    cr_writel(set_div, CR_EMMC_CLKDIV);
    sync();

    //EMMC Cmd
    cr_writel(0xa0202000, CR_EMMC_CMD);
    sync();
    wait_done_timeout((u32*)CR_EMMC_CMD, 0x80000000, 0x0);
    sync();

    //enable clock
    cr_writel(0x10001, CR_EMMC_CLKENA);
    sync();

    //EMMC Cmd
    cr_writel(0xa0202000, CR_EMMC_CMD);
    sync();
    wait_done_timeout((u32*)CR_EMMC_CMD, 0x80000000, 0x0);

    printf("set div to 0x%02x, EMMC_CLKDIV=%08x\n",
              set_div, cr_readl(CR_EMMC_CLKDIV));
}
#endif

void rtkemmc_host_reset(void)
{
    cr_writel(0x00000081, CR_EMMC_BMOD);
    sync();
    //cr_writel(0x00000001, EMMC_CTRL);
    sync();
    cr_writel(0x02000000, CR_EMMC_CTRL);
    sync();
    cr_writel(0x00000001, CR_EMMC_PWREN);
    sync();
    cr_writel(0x0000ffff, CR_EMMC_INTMASK);
    sync();
    cr_writel(0xffffffff, CR_EMMC_RINTSTS);
    sync();
    //cr_writel(0x00000010, EMMC_CTRL);
    sync();

    cr_writel(0x00000080, CR_EMMC_CLKDIV);
    sync();
    cr_writel(0x00000000, CR_EMMC_CLKSRC);
    sync();
    //cr_writel(0x0001ffff, EMMC_CLKENA);
    cr_writel(0x00010001, CR_EMMC_CLKENA);
    sync();
    cr_writel(0xa0200000, CR_EMMC_CMD);
    sync();

    MMCPRINTF("1 EMMC_TMOUT = 0x%08x \n", cr_readl(CR_EMMC_TMOUT));
    cr_writel(0xffffff40, (volatile void*)(CR_EMMC_TMOUT));
    sync();
    MMCPRINTF("2 EMMC_TMOUT = 0x%08x \n",  (volatile void*)cr_readl(CR_EMMC_TMOUT));

    cr_writel(0x00000000, CR_EMMC_CTYPE);
    sync();
    cr_writel(0x0001007f, CR_EMMC_FIFOTH);
    sync();
    cr_writel(0x02000010, CR_EMMC_CTRL);
    sync();
    cr_writel(0x00000080, CR_EMMC_BMOD);
    sync();
    cr_writel(0x0000ffcf, CR_EMMC_INTMASK);
    sync();
    cr_writel(0x00600000, CR_EMMC_DBADDR);
    sync();
    cr_writel(0x00000000, CR_EMMC_IDINTEN);
    sync();
    cr_writel(0x0000ffff, CR_EMMC_RINTSTS);
    sync();
    cr_writel(0x00000001, CR_EMMC_UHSREG);
    sync();
    cr_writel(0x01000001, CR_EMMC_CARD_THR_CTL);
    sync();

    MMCPRINTF("%s : \n", __func__);

    sync();
}

void phase(u32 VP0, u32 VP1){

        //phase selection
        if( (VP0==0xff) & (VP1==0xff)){
                MMCPRINTF("phase VP0 and VP1 no change \n");
        }
        else if( (VP0!=0xff) & (VP1==0xff)){
                MMCPRINTF("phase VP0=%x, VP1 no change \n", VP0);
                //change clock to 4MHz
                cr_writel(cr_readl(CR_EMMC_CKGEN_CTL)|0x70000, CR_EMMC_CKGEN_CTL);
                sync();
                //reset pll
                cr_writel(cr_readl(PLL_EMMC1)&0xfffffffd, PLL_EMMC1);
                sync();
                //vp0 phase:0x0~0x1f
                cr_writel( (cr_readl(PLL_EMMC1)&0xffffff07) | ((VP0<<3)), PLL_EMMC1);
                sync();
                //release reset pll
                cr_writel(cr_readl(PLL_EMMC1)|0x2, PLL_EMMC1);
                sync();
                //change clock to PLL
                cr_writel(cr_readl(CR_EMMC_CKGEN_CTL)&0xfff8ffff, CR_EMMC_CKGEN_CTL);
                sync();
        }
        else if( (VP0==0xff) & (VP1!=0xff)){
                MMCPRINTF("phase VP0 no change, VP1=0x%x \n", VP1);
                cr_writel(cr_readl(CR_EMMC_CKGEN_CTL)|0x70000, CR_EMMC_CKGEN_CTL);
                sync();
                //reset pll
                cr_writel(cr_readl(PLL_EMMC1)&0xfffffffd, PLL_EMMC1);
                sync();
                //vp1 phase:0x0~0x1f
                cr_writel( (cr_readl(PLL_EMMC1)&0xffffe0ff) | ((VP1<<8)), PLL_EMMC1);
                sync();
                //release reset pll
                cr_writel(cr_readl(PLL_EMMC1)|0x2, PLL_EMMC1);
                sync();
                //change clock to PLL
                cr_writel(cr_readl(CR_EMMC_CKGEN_CTL)&0xfff8ffff, CR_EMMC_CKGEN_CTL);
                sync();
        }
        else{
                MMCPRINTF("phase VP0=0x%x, VP1=0x%x \n", VP0, VP1);
                cr_writel(cr_readl(CR_EMMC_CKGEN_CTL)|0x70000, CR_EMMC_CKGEN_CTL);
                sync();
                //reset pll
                cr_writel(cr_readl(PLL_EMMC1)&0xfffffffd, PLL_EMMC1);
                sync();
                //vp0 phase:0x0~0x1f
                cr_writel( (cr_readl(PLL_EMMC1)&0xffffff07) | ((VP0<<3)), PLL_EMMC1);
                sync();
                //vp1 phase:0x0~0x1f
                cr_writel( (cr_readl(PLL_EMMC1)&0xffffe0ff) | ((VP1<<8)), PLL_EMMC1);
                sync();
                //release reset pll
                cr_writel(cr_readl(PLL_EMMC1)|0x2, PLL_EMMC1);
                sync();
                //change clock to PLL
                cr_writel(cr_readl(CR_EMMC_CKGEN_CTL)&0xfff8ffff, CR_EMMC_CKGEN_CTL);
                sync();
        }
        udelay(100);
        sync();
}

int search_best(u32 window, u32 range){
        u32 i, j, k, max;
        u32 window_temp[32];
        u32 window_start[32];
        u32 window_end[32];
        u32 window_max=0;
        u32 window_best=0;
        u32 parse_end=1;
        for( i=0; i<0x20; i++ ){
                window_temp[i]=0;
                window_start[i]=0;
                window_end[i]=-1;
        }
        j=1;    i=0;    k=0;    max=0;
        while((i<0x1f) && (k<0x1f)){
                parse_end=0;
                for( i=window_end[j-1]+1; i<0x20; i++ ){
                        if (((window>>i)&1)==1 ){
                                window_start[j]=i;
                                break;
                        }
                }
                if( i==0x20){
                        break;
                }
                for( k=window_start[j]+1; k<0x20; k++ ){
                        if(((window>>k)&1)==0){
                                window_end[j]=k-1;
                                parse_end=1;
                                break;
                        }
                }
                if(parse_end==0){
                        window_end[j]=0x1f;
                }
                j++;
        }
        for(i=1; i<j; i++){
                window_temp[i]= window_end[i]-window_start[i]+1;
        }
        if((((window>>(0x20-range))&1)==1)&&(((window>>0x1f)&1)==1))
        {
                window_temp[1]=window_temp[1]+window_temp[j-1];
                window_start[1]=window_start[j-1];
        }
        for(i=1; i<j; i++){
                if(window_temp[i]>window_max){
                        window_max=window_temp[i];
                        max=i;
                }
        }
        if(window==0xffffffff){
                window_best=0x10;
        }
        else if((window==0xffff0000)&&(range==0x10)){
                window_best=0x18;
        }
        else if(((((window>>(0x20-range))&1)==1)&&(((window>>0x1f)&1)==1))&&(max==1)){
                window_best=(((window_start[max]+window_end[max]+range)/2)&0x1f)|(0x20-range);
        }
        else {
                window_best=((window_start[max]+window_end[max])/2)&0x1f;
        }

        MMCPRINTF("window start=0x%x \n", window_start[max]);
        MMCPRINTF("window end=0x%x \n", window_end[max]);
        MMCPRINTF("window best=0x%x \n", window_best);
        return window_best;
}

int mmc_Tuning_HS200(void){
	volatile UINT32 TX_window=0xffffffff;
	volatile UINT32 TX1_window=0xffffffff;
	//int TX_fail_start=-1;
	//int TX_fail_end=0x20;
	//int TX_pass_start=-1;
	//int TX_pass_end=0x20;
	volatile int TX_best=0xff;	
	volatile UINT32 RX_window=0xffffffff;
	//int RX_fail_start=-1;
	//int RX_fail_end=0x20;
	//int RX_pass_start=-1;
	//int RX_pass_end=0x20;
	volatile int RX_best=0xff;	
	volatile int i=0;
	volatile int j=0;

	gCurrentBootMode= MODE_SD30;
	#ifdef MMC_DEBUG		
	printf("[LY]hs200 gCurrentBootMode =%d\n",gCurrentBootMode);
	#endif

	rtkemmc_set_freq(0xa6);
	rtkemmc_set_div(EMMC_CLOCK_DIV_NON); // 200MHZ/1 = 200MHZ
	rtkemmc_set_pad_driving(0xbb, 0xbb,0xbb,0xbb);
	phase(0, 0);	//VP0, VP1 phas	
	mdelay(5);
	emmc_info_show();
	sync();

	card_stop();
	
	#ifdef MMC_DEBUG
	MMCPRINTF("==============Start HS200 TX Tuning round 1==================\n");
	#endif
	for(i=0x0; i<0x20; i++){
		phase(i, 0xff);
		#ifdef MMC_DEBUG		
		printf("phase =0x%x \n", i);
		#endif
		realErrTuning = 0;
		if(rtkemmc_send_cmd13() != 0 && realErrTuning)
		{
			TX_window= TX_window&(~(1<<i));
		}
	}
	TX_best = search_best(TX_window,0x20);
	#ifdef MMC_DEBUG
	MMCPRINTF("TX_WINDOW= 0x%x \n", TX_window);
	//MMCPRINTF("TX phase fail from 0x%x to=0x%x \n", TX_fail_start, TX_fail_end);
	//MMCPRINTF("TX phase pass from 0x%x to=0x%x \n", TX_pass_start, TX_pass_end);
	MMCPRINTF("TX_best= 0x%x \n", TX_best);
	#endif
	printf("TEMP TX_WINDOW=0x%x, TX_best=0x%x \n",TX_window, TX_best);
	if (TX_window == 0x0)
	{
		printf("[LY] HS200 TX tuning fail \n");
		return -1;
	}
	phase(TX_best, 0xff);
	
	#ifdef MMC_DEBUG
	MMCPRINTF("++++++++++++++++++ Start HS200 RX Tuning ++++++++++++++++++\n");
	#endif
	
	for(i=0x0; i<0x20; i++){
		phase(0xff, i);
		#ifdef MMC_DEBUG		
		MMCPRINTF("phase =0x%x \n", i);
		#endif
		realErrTuning = 0;
		if(rtkemmc_send_cmd18()!=0 && realErrTuning)
		{
			RX_window= RX_window&(~(1<<i));
		}
		MMCPRINTF("%s:%u ... \n", __func__,__LINE__);
	}
	RX_best = search_best(RX_window,0x20);
	#ifdef MMC_DEBUG
	MMCPRINTF("RX_WINDOW= 0x%x \n", RX_window);
	//MMCPRINTF("RX phase fail from 0x%x to=0x%x \n", RX_fail_start, RX_fail_end);
	//MMCPRINTF("RX phase pass from 0x%x to=0x%x \n", RX_pass_start, RX_pass_end);
	MMCPRINTF("RX_best= 0x%x \n", RX_best);
	#endif
	printf("RX_WINDOW=0x%x, RX_best=0x%x \n",RX_window, RX_best);
	if (RX_window == 0x0)
	{
		printf("[LY] HS200 RX tuning fail \n");
		return -2;
	}
	phase( 0xff, RX_best);
	
	#ifdef MMC_DEBUG
	MMCPRINTF("==============Start HS200 TX Tuning round 2==================\n");
	#endif
	TX1_window=TX_window;
	for(i=0x0; i<0x20; i++){
		j=(TX_window>>i)&1;
		if(j == 1){
			phase(i, 0xff);
			#ifdef MMC_DEBUG		
			printf("phase =0x%x \n", i);
			#endif
			realErrTuning = 0;
			if(rtkemmc_send_cmd25() != 0 && realErrTuning)
			{
				TX1_window= TX1_window&(~(1<<i));
			}
		}
	}
	TX_best = search_best(TX1_window,0x20);
	printf("TX1_WINDOW=0x%x, TX_best=0x%x \n",TX1_window, TX_best);
	if (TX1_window == 0x0)
	{
		printf("[LY] HS200 TX tuning fail \n");
		return -1;
	}
	phase(TX_best, 0xff);
	
	sync();
	card_stop();
	polling_to_tran_state(MMC_CMD_WRITE_MULTIPLE_BLOCK,1);

	return 0;
}
	
int mmc_Tuning_DDR50(void){	
	volatile UINT32 TX_window=0xffffffff;
	int TX_fail_start=-1;
	int TX_fail_end=0x20;
	int TX_pass_start=-1;
	int TX_pass_end=0x20;
	volatile int TX_best=0xff;	
	volatile UINT32 RX_window=0xffffffff;
	int RX_fail_start=-1;
	int RX_fail_end=0x20;
	int RX_pass_start=-1;
	int RX_pass_end=0x20;
	volatile int RX_best=0xff;	
	volatile int i=0;
	
	printf("Some TX value is %d %d %d %d",TX_fail_start,TX_fail_end,TX_pass_start,TX_pass_end);
	printf("Some RX value is %d %d %d %d",RX_fail_start,RX_fail_end,RX_pass_start,RX_pass_end);
		
	//set current boot mode
	gCurrentBootMode = MODE_DDR;	
	#ifdef MMC_DEBUG
	printf("[LY]ddr50 gCurrentBootMode =%d\n",gCurrentBootMode);
	#endif

	rtkemmc_set_freq(0x46); //80Mhz
	sync();
	rtkemmc_set_wrapper_div(0);    //no wrapper divider
	sync();
	rtkemmc_set_pad_driving(0x33, 0x33,0x33,0x33);

	mdelay(5);
	sync();
	#ifdef MMC_DEBUG
	MMCPRINTF("==============Start DDR50 TX Tuning ==================\n");
	#endif
	for(i=0x0; i<0x20; i++){
		phase(i, 0xff);
		#ifdef MMC_DEBUG
		MMCPRINTF("phase (%d) - VP=0x%08x\n", i,REG32(PLL_EMMC1));
		#endif
		if (rtkemmc_send_cmd25()!=0)
		{
			TX_window= TX_window&(~(1<<i));
		}
	}
	TX_best = search_best(TX_window,0x20);
	#ifdef MMC_DEBUG
	MMCPRINTF("TX_WINDOW= 0x%x \n", TX_window);
	MMCPRINTF("TX phase fail from 0x%x to=0x%x \n", TX_fail_start, TX_fail_end);
	MMCPRINTF("TX phase pass from 0x%x to=0x%x \n", TX_pass_start, TX_pass_end);
	MMCPRINTF("TX_best= 0x%x \n", TX_best);
	#endif
	printf("TX_WINDOW=0x%x, TX_best=0x%x \n",TX_window,TX_best);
	if (TX_window == 0x0)
	{
		printf("[LY] DDR50 TX tuning fail \n");
		return -1;
	}
	phase(TX_best, 0xff);

	sync();
	#ifdef MMC_DEBUG
	MMCPRINTF("++++++++++++++Start DDR50 RX Tuning ++++++++++++++++++\n");
	#endif
	i=0;
	for(i=0x0; i<0x20; i++){
		phase(0xff, i);
		#ifdef MMC_DEBUG		
		MMCPRINTF("phase =0x%x \n", i);
		#endif
		if(rtkemmc_send_cmd18()!=0)
		{
			RX_window= RX_window&(~(1<<i));
		}
	}
	RX_best = search_best(RX_window,0x20);
	#ifdef MMC_DEBUG
	MMCPRINTF("RX_WINDOW= 0x%x \n", RX_window);
	MMCPRINTF("RX phase fail from 0x%x to=0x%x \n", RX_fail_start, RX_fail_end);
	MMCPRINTF("RX phase pass from 0x%x to=0x%x \n", RX_pass_start, RX_pass_end);
	MMCPRINTF("RX_best= 0x%x \n", RX_best);
	#endif
	printf("RX_WINDOW=0x%x, RX_best=0x%x \n",RX_window,RX_best);
	sync();
	if (RX_window == 0x0)
	{
		printf("[LY] DDR50 RX tuning fail \n");
		return -2;
	}
	phase( 0xff, RX_best);
	return 0;
}

int mmc_Select_SDR50_Push_Sample(void){
	volatile int err=0;

	gCurrentBootMode = MODE_SD20;
	#ifdef MMC_DEBUG
	printf("[LY]sdr gCurrentBootMode =%d\n",gCurrentBootMode);
	#endif

	rtkemmc_set_freq(0x46); //80Mhz
	rtkemmc_set_wrapper_div(0);    //no wrapper divider
    rtkemmc_set_div(EMMC_CLOCK_DIV_2); //80/2 = 40Mhz

	mdelay(5);
	sync();	
	#ifdef MMC_DEBUG
	MMCPRINTF("==============Select SDR50 Push Point ==================\n");
	#endif
	if ((err = rtkemmc_send_cmd25())==0)
	{
		MMCPRINTF("Output at FALLING edge of SDCLK \n");
	}
	else
	{
		sync();
		if ((err = rtkemmc_send_cmd25())==0)
		{
			MMCPRINTF("Output is ahead by 1/4 SDCLK period \n");		
		}
		else 
		{
			printf("sdr tuning : No good push point \n");
			return -1;			
		}
	}
	#ifdef MMC_DEBUG
	MMCPRINTF("++++++++++++++Select SDR50 Sample Point ++++++++++++++++++\n");
	#endif
	if ((err = rtkemmc_send_cmd18())==0)
	{
			MMCPRINTF("Sample at RISING edge of SDCLK \n");		
	}
	else {
		
		sync();
		if ((err = rtkemmc_send_cmd18())==0)
		{
			MMCPRINTF("sample point is delayed by 1/4 SDCLK period \n");
		}
		else {
			printf("sdr tuning : No good Sample point \n");
			return -2;					
		}
	}
	sync();

	return 0;
}

int sample_ctl_switch(int cmd_idx)
{
	int err=0;
// tbd
	return err;
}

/*******************************************************
 *
 *******************************************************/
int rtk_micron_eMMC_write( unsigned int blk_addr, unsigned int data_size, unsigned int * buffer )
{
    int ret_err = 0;
    unsigned int total_blk_cont;
    unsigned int curr_xfer_blk_cont;
    unsigned int address;
    unsigned int curr_blk_addr;
    e_device_type * card = &emmc_card;
    UINT8 ret_state=0;
    UINT32 bRetry=0, resp = 0;
    UINT32 retry_cnt=0, retry_cnt1=0, retry_cnt2=0, retry_cnt3=0;
    int err1=0;

    RDPRINTF("\nemmc:%s blk_addr=0x%08x, data_size=0x%08x, buffer=0x%08x, addressing=%d\n", __FUNCTION__, blk_addr, data_size, buffer, card->sector_addressing);

    total_blk_cont = data_size>>9;
    if(data_size & 0x1ff) {
        total_blk_cont+=1;
    }

	curr_blk_addr = blk_addr;
#ifndef FORCE_SECTOR_MODE
	if( card->sector_addressing ) {
		address = curr_blk_addr;
	}
	else {
		address = curr_blk_addr << 9;
	}
#else
    address = curr_blk_addr;
#endif

#ifdef EMMC_SPLIT_BLK
	while( total_blk_cont ) {
		if( total_blk_cont > EMMC_MAX_XFER_BLKCNT ) {
			curr_xfer_blk_cont = EMMC_MAX_XFER_BLKCNT;
		}
		else {
			curr_xfer_blk_cont = total_blk_cont;
		}

		flush_cache((unsigned long)buffer, curr_xfer_blk_cont << 9);
		ret_err = rtkemmc_Stream( address, curr_xfer_blk_cont, MMC_CMD_MICRON_60, (uintptr_t)buffer, 0 );

		if( ret_err ) {
			return 0;
		}
		total_blk_cont -= curr_xfer_blk_cont;
		buffer += (curr_xfer_blk_cont<<(9-2));
		address += curr_xfer_blk_cont;
	}

	total_blk_cont = data_size>>9;
    if( data_size & 0x1ff ) {
        total_blk_cont+=1;
    }

    return total_blk_cont;
#else
RETRY_RD_CMD:
    flush_cache((unsigned long)buffer, data_size);

    ret_err = rtkemmc_Stream( address, total_blk_cont, MMC_CMD_MICRON_60, (uintptr_t)buffer,0 );  //tbd : not verify


    if (ret_err)
    {
        if (retry_cnt2++ < MAX_CMD_RETRY_COUNT)
	{
            sample_ctl_switch(-1);
            goto RETRY_RD_CMD;
	}
        return ret_err;
    }

    /* To wait status change complete */
    bRetry=0;
    retry_cnt=0;
    retry_cnt1=0;
    while(1)
    {
        err1 = rtkemmc_send_status(&resp,1,0);
        //1. if cmd sent error, try again
        if (err1)
        {
            #ifdef THIS_IS_FLASH_WRITE_U_ENV
	        prints("retry - case 1\n");
            #else
            MMCPRINTF("retry - case 1\n");
            #endif
            sample_ctl_switch(-1);
            if (retry_cnt++ > MAX_CMD_RETRY_COUNT*2)
                return ERR_EMMC_SEND_STATUS_RETRY_FAIL;
            mdelay(1);
            continue;
        }
	ret_state = R1_CURRENT_STATE(resp);
        //2. get state
        if (ret_state != STATE_TRAN)
        {
            #ifdef THIS_IS_FLASH_WRITE_U_ENV
	        prints("retry - case 2\n");
            #else
            MMCPRINTF("retry - case 2\n");
            #endif
            bRetry = 1;
            if (retry_cnt1++ > MAX_CMD_RETRY_COUNT*2)
                return ERR_EMMC_SEND_RW_CMD_RETRY_FAIL;
            rtkemmc_stop_transmission(&emmc_card,0);
            mdelay(1000);
        }
        else
        {
            //out peaceful
            if (bRetry == 0)
            {
                #ifdef THIS_IS_FLASH_WRITE_U_ENV
	            prints("retry - case 3\n");
                #else
                MMCPRINTF("retry - case 3\n");
                #endif
                return !ret_err ?  total_blk_cont : 0;
            }
            else
            {
                #ifdef THIS_IS_FLASH_WRITE_U_ENV
	            prints("retry - case 4\n");
                #else
                MMCPRINTF("retry - case 4\n");
                #endif
                retry_cnt2 = 0;
                if (retry_cnt3++ > MAX_CMD_RETRY_COUNT*2)
                    return ERR_EMMC_SEND_RW_CMD_RETRY_FAIL;
                goto RETRY_RD_CMD;
            }
        }
    }

#endif
	printf("The err1 is %d. The retry_cnt is %d. The retry_cnt1 is %d. The retry_cnt2 is %d. The retry_cnt3 is %d.\n",err1,retry_cnt,retry_cnt1,retry_cnt2,retry_cnt3);
	printf("The ret_state, bRetry, resp are %c, %d, %d\n.",ret_state,bRetry,resp);
	printf("The card addressing=%d\n",card->sector_addressing);

    return !ret_err ?  total_blk_cont : 0;
}

/*******************************************************
 *
 *******************************************************/
int rtk_micron_eMMC_read( unsigned int blk_addr, unsigned int data_size, unsigned int * buffer )
{
    int ret_err = 0;
    unsigned int total_blk_cont;
    unsigned int curr_xfer_blk_cont;
    unsigned int address;
    e_device_type * card = &emmc_card;
    UINT8 ret_state=0;
    UINT32 bRetry=0, resp = 0;
    UINT32 retry_cnt=0, retry_cnt1=0, retry_cnt2=0, retry_cnt3=0;
    int err1=0;

    RDPRINTF("\nemmc:%s blk_addr=0x%08x, data_size=0x%08x, buffer=0x%08x, addressing=%d\n", __FUNCTION__, blk_addr, data_size, buffer, card->sector_addressing);

    total_blk_cont = data_size>>9;
    if( data_size & 0x1ff ) {
        total_blk_cont+=1;
    }

#ifndef FORCE_SECTOR_MODE
	if( card->sector_addressing ) {
		address = blk_addr;
	}
	else {
		address = blk_addr << 9;
	}
#else
    address = blk_addr;
#endif
#ifdef EMMC_SPLIT_BLK
	while( total_blk_cont ) {
		if( total_blk_cont > EMMC_MAX_XFER_BLKCNT ) {
			curr_xfer_blk_cont = EMMC_MAX_XFER_BLKCNT;
		}
		else {
			curr_xfer_blk_cont = total_blk_cont;
		}

		flush_cache((unsigned long)buffer, curr_xfer_blk_cont << 9);
        	ret_err = rtkemmc_Stream( address, curr_xfer_blk_cont, MMC_CMD_MICRON_61, (uintptr_t)buffer,0 );
        
		if( ret_err ) {
			return 0;
		}
		total_blk_cont -= curr_xfer_blk_cont;
		buffer += (curr_xfer_blk_cont<<(9-2));
		address += curr_xfer_blk_cont;

		//EXECUTE_CUSTOMIZE_FUNC(0); // insert execute customer callback at here

	}

	total_blk_cont = data_size>>9;
    if( data_size & 0x1ff ) {
        total_blk_cont+=1;
    }
	return total_blk_cont;
#else
RETRY_RD_CMD:
    flush_cache((unsigned long)buffer, data_size);

    ret_err = rtkemmc_Stream( address, total_blk_cont, MMC_CMD_MICRON_61, buffer,0 );


    if (ret_err)
    {
        if (retry_cnt2++ < MAX_CMD_RETRY_COUNT*2)
	{
            sample_ctl_switch(-1);
            goto RETRY_RD_CMD;
	}
        return ret_err;
    }
    
    /* To wait status change complete */
    bRetry=0;
    retry_cnt=0;
    retry_cnt1=0;
    while(1)
    {
        err1 = rtkemmc_send_status(&resp,1,0);
        //1. if cmd sent error, try again
        if (err1)
        {
            sample_ctl_switch(-1);
            if (retry_cnt++ > MAX_CMD_RETRY_COUNT*2)
                return ERR_EMMC_SEND_STATUS_RETRY_FAIL;
            mdelay(1);
            continue;
        }
	ret_state = R1_CURRENT_STATE(resp);
        //2. get state
        if (ret_state != STATE_TRAN) 
        {
            bRetry = 1;
            if (retry_cnt1++ > MAX_CMD_RETRY_COUNT*2)
                return ERR_EMMC_SEND_RW_CMD_RETRY_FAIL;
            rtkemmc_stop_transmission(&emmc_card,0);
            mdelay(1000);
        }
        else
        {
            //out peaceful
            if (bRetry == 0)
                return !ret_err ?  total_blk_cont : 0;
            else
            {
                retry_cnt2 = 0;
                if (retry_cnt3++ > MAX_CMD_RETRY_COUNT*2)
                    return ERR_EMMC_SEND_RW_CMD_RETRY_FAIL;
                goto RETRY_RD_CMD;
            }
        }
    }
#endif
	printf("The err1 is %d. The retry_cnt is %d. The retry_cnt1 is %d. The retry_cnt2 is %d. The retry_cnt3 is %d.\n",err1,retry_cnt,retry_cnt1,retry_cnt2,retry_cnt3);
	printf("The ret_state, bRetry, resp are %c, %d, %d\n.",ret_state,bRetry,resp);
	printf("The card addressing=%d\n",card->sector_addressing);

    return !ret_err ?  total_blk_cont : 0;
}

/*******************************************************
 *
 *******************************************************/
int rtk_eMMC_write( unsigned int blk_addr, unsigned int data_size, unsigned int * buffer )
{
    int ret_err = 0;
    unsigned int total_blk_cont;
    unsigned int curr_xfer_blk_cont;
    unsigned int address;
    unsigned int curr_blk_addr;
    e_device_type * card = &emmc_card;
    UINT8 ret_state=0;
    UINT32 bRetry=0, resp = 0;
    UINT32 retry_cnt=0, retry_cnt1=0, retry_cnt2=0, retry_cnt3=0;
    int err1=0;

    RDPRINTF("\nemmc:%s blk_addr=0x%08x, data_size=0x%08x, buffer=0x%08x, addressing=%d\n", __FUNCTION__, blk_addr, data_size, buffer, card->sector_addressing);

    if( !mmc_ready_to_use ) {
         MMCPRINTF("emmc: not ready to use\n");
    }

    total_blk_cont = data_size>>9;
    if(data_size & 0x1ff) {
        total_blk_cont+=1;
    }

	curr_blk_addr = blk_addr;
#ifndef FORCE_SECTOR_MODE
	if( card->sector_addressing ) {
		address = curr_blk_addr;
	}
	else {
		address = curr_blk_addr << 9;
	}
#else
    address = curr_blk_addr;
#endif

#ifdef EMMC_SPLIT_BLK
	while( total_blk_cont ) {
		if( total_blk_cont > EMMC_MAX_XFER_BLKCNT ) {
			curr_xfer_blk_cont = EMMC_MAX_XFER_BLKCNT;
		}
		else {
			curr_xfer_blk_cont = total_blk_cont;
		}

		flush_cache((unsigned long)buffer, curr_xfer_blk_cont << 9);

		if (IS_SRAM_ADDR((uintptr_t)buffer))
        	ret_err = -1; //cannot allow r/w to sram in bootcode
		else{
			if (curr_xfer_blk_cont == 1)
				ret_err = rtkemmc_Stream(0xa0000740|MMC_WRITE_BLOCK, address, (uintptr_t)buffer, curr_xfer_blk_cont << 9,0);
			else
				ret_err = rtkemmc_Stream(0xa0001740|MMC_WRITE_MULTIPLE_BLOCK, address, (uintptr_t)buffer, curr_xfer_blk_cont << 9,0);
		} 

		if( ret_err ) {
			return 0;
		}
		total_blk_cont -= curr_xfer_blk_cont;
		buffer += (curr_xfer_blk_cont<<(9-2));
		address += curr_xfer_blk_cont;
	}

	total_blk_cont = data_size>>9;
    if( data_size & 0x1ff ) {
        total_blk_cont+=1;
    }

    return total_blk_cont;
#else
RETRY_RD_CMD:
    flush_cache((unsigned long)buffer, data_size);


	if (IS_SRAM_ADDR((uintptr_t)buffer))
        ret_err = -1; //cannot allow r/w to sram in bootcode
	else{
		if (curr_xfer_blk_cont == 1)
			ret_err = rtkemmc_Stream(0xa0000740|MMC_WRITE_BLOCK, address, buffer, total_blk_cont << 9,0);
		else
			ret_err = rtkemmc_Stream(0xa0001740|MMC_WRITE_MULTIPLE_BLOCK, address, buffer, total_blk_cont << 9,0);
	} 

    if (ret_err)
    {
        if (retry_cnt2++ < MAX_CMD_RETRY_COUNT*2)
	{
            sample_ctl_switch(-1);
            goto RETRY_RD_CMD;
	}
        return ret_err;
    }

    /* To wait status change complete */
    bRetry=0;
    retry_cnt=0;
    retry_cnt1=0;
    while(1)
    {
        err1 = rtkemmc_send_status(&resp,1,0);
        //1. if cmd sent error, try again
        if (err1)
        {
            #ifdef THIS_IS_FLASH_WRITE_U_ENV
	        prints("retry - case 1\n");
            #else
            MMCPRINTF("retry - case 1\n");
            #endif
            sample_ctl_switch(-1);
            if (retry_cnt++ > MAX_CMD_RETRY_COUNT*2)
                return ERR_EMMC_SEND_STATUS_RETRY_FAIL;
            mdelay(1);
            continue;
        }
	ret_state = R1_CURRENT_STATE(resp);
        //2. get state
        if (ret_state != STATE_TRAN)
        {
            #ifdef THIS_IS_FLASH_WRITE_U_ENV
	        prints("retry - case 2\n");
            #else
            MMCPRINTF("retry - case 2\n");
            #endif
            bRetry = 1;
            if (retry_cnt1++ > MAX_CMD_RETRY_COUNT*2)
                return ERR_EMMC_SEND_RW_CMD_RETRY_FAIL;
            rtkemmc_stop_transmission(&emmc_card,0);
            mdelay(1000);
        }
        else
        {
            //out peaceful
            if (bRetry == 0)
            {
                #ifdef THIS_IS_FLASH_WRITE_U_ENV
	            prints("retry - case 3\n");
                #else
                MMCPRINTF("retry - case 3\n");
                #endif
                return !ret_err ?  total_blk_cont : 0;
            }
            else
            {
                #ifdef THIS_IS_FLASH_WRITE_U_ENV
	            prints("retry - case 4\n");
                #else
                MMCPRINTF("retry - case 4\n");
                #endif
                retry_cnt2 = 0;
                if (retry_cnt3++ > MAX_CMD_RETRY_COUNT*2)
                    return ERR_EMMC_SEND_RW_CMD_RETRY_FAIL;
                goto RETRY_RD_CMD;
            }
        }
    }

#endif
	printf("The err1 is %d. The retry_cnt is %d. The retry_cnt1 is %d. The retry_cnt2 is %d. The retry_cnt3 is %d.\n",err1,retry_cnt,retry_cnt1,retry_cnt2,retry_cnt3);
	printf("The ret_state, bRetry, resp are %c, %d, %d\n.",ret_state,bRetry,resp);
	printf("The card addressing=%d\n",card->sector_addressing);

    return !ret_err ?  total_blk_cont : 0;
}

/*******************************************************
 *
 *******************************************************/
int rtkemmc_send_wp_type( unsigned int blk_addr, unsigned int * buffer )
{
    int ret_err = 0;
	int i = 0, j = 0;
	unsigned int tmp = 0;
    unsigned int address;
    e_device_type * card = &emmc_card;
    UINT32 resp = 0;

    RDPRINTF("\nemmc:%s blk_addr=0x%08x, data_size=0x%08x, buffer=0x%08x, addressing=%d\n", __FUNCTION__, blk_addr, data_size, buffer, card->sector_addressing);

    if( !mmc_ready_to_use ) {
         RDPRINTF("emmc: not ready to use\n");
    }
   
#ifndef FORCE_SECTOR_MODE
	if( card->sector_addressing ) {
		address = blk_addr;
	}
	else {
		address = blk_addr << 9;
	}
#else
    address = blk_addr;
#endif

	flush_cache((unsigned long)buffer, 8);
    if (IS_SRAM_ADDR((uintptr_t)(buffer)))
    	ret_err = -1; //cannot allow r/w to sram in bootcode
    else{	
    	ret_err = rtkemmc_Stream(0xa0000340|MMC_SEND_WRITE_PROT_TYPE, address, (uintptr_t)buffer, 8,0);
		
    } 
	if( ret_err ) {
		return 0;
	}

	CP15ISB;
	sync();
	printf("00:Unprotected 01:Temporary Write Protect\n10:Power-on Write Protect 11:Permanent Write Protect\n");
	//the last 2 bits is the first addressed wp
	for (i = 1; i >= 0; i--){
		printf("0x%x\n",buffer[i]);
		#ifdef CONFIG_UBOOT_DEFAULT
		buffer[i] = swap_endian(buffer[i]);
		#else /* !CONFIG_UBOOT_DEFAULT */
		buffer[i] = (buffer[i] & 0xff000000)>>24|
					(buffer[i] & 0x00ff0000)>>8|
					(buffer[i] & 0x0000ff00)<<8|
					(buffer[i] & 0x000000ff)<<24;
		#endif /* CONFIG_UBOOT_DEFAULT */
		for (j = 0; j < 16; j++){
			tmp =  buffer[i] >> (j * 2);
			printf("%u%u ", (tmp & 2) >> 1, tmp & 1);
		}
		printf("\n");
	}

	rtkemmc_send_status(&resp,1,0);
	//workaround for 1295 a00 non-512B data transfer
	card_stop();
	printf("The card addressing=%d\n",card->sector_addressing);
	return 1;

}

/*******************************************************
 *
 *******************************************************/
int do_rtkemmc (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int ret = CMD_RET_USAGE;
	unsigned int blk_addr, byte_size;
	void * mem_addr;

	if( argc == 5 ) {
		mem_addr   = (void *)simple_strtoul(argv[2], NULL, 16);
		blk_addr   = simple_strtoul(argv[3], NULL, 16);
		byte_size  = simple_strtoul(argv[4], NULL, 16);
		if( strncmp( argv[1], "read", 4 ) == 0 ) {
			ret = rtk_eMMC_read( blk_addr, byte_size, mem_addr);
			return ((ret==0) ? 1 : 0);
		}
		else if( strncmp( argv[1], "write", 5 ) == 0 ) {
			ret = rtk_eMMC_write( blk_addr, byte_size, mem_addr);
			return ((ret==0) ? 1 : 0);
		}
	}
	if( argc == 4 ) {
		mem_addr   = (void *)simple_strtoul(argv[2], NULL, 16);
		blk_addr   = simple_strtoul(argv[3], NULL, 16);
		if( strncmp( argv[1], "send_wp_type", 12 ) == 0 ) {
			ret = rtkemmc_send_wp_type( blk_addr, mem_addr);
			return ret;
		}
	}
	if( argc == 3 ) {
		
		blk_addr   = simple_strtoul(argv[2], NULL, 16);

		if( strncmp( argv[1], "set_wp", 6 ) == 0 ) {
			ret = rtkemmc_set_wp( blk_addr, 1, 0);
			return ret;
		}
		else if( strncmp( argv[1], "clr_wp", 6 ) == 0 ) {
			ret = rtkemmc_clr_wp( blk_addr, 1, 0);
			return ret;
		}
		
	}

	return  ret;	
}

/*******************************************************
 *
 *******************************************************/
U_BOOT_CMD(
	rtkemmc, 5, 0, do_rtkemmc,
	"RTK EMMC functions",
	" - rtkemmc read/write/set_wp/clr_wp/send_wp_type\n"
	"rtkemmc read dma_addr blk_addr byte_size\n"
	"rtkemmc write dma_addr blk_addr byte_size\n"
	"rtkemmc set_wp blk_addr\n"
	"rtkemmc clr_wp blk_addr\n"
	"rtkemmc send_wp_type dma_addr blk_addr\n"
	""
);

//******************************************************
void reset_ip(void){
	cr_writel(0x00000081, CR_EMMC_BMOD); //reset
	sync();	
}	

void switch_bus(UINT8 WIDTH){
	emmc_send_cmd_get_rsp(MMC_SWITCH, 0x03b70000|(WIDTH<<8), 1, 1); //WIDTH - 0: SDR1b, 1: SDR4b, 2: SDR8b, 5: DDR4b, 6: DDR8b
	emmc_send_cmd_get_rsp(MMC_SEND_STATUS, emmc_card.rca, 1, 1);
	CP15ISB;
	if ((cr_readl(CR_EMMC_RESP0)&0x80)==0){
		printf("switch bus width to 0x");
		printf("%d",WIDTH * 4);
		printf(" bits success\n");
		switch(WIDTH)
		{
			case 0:
				cr_writel(0x00000000, CR_EMMC_CTYPE); // 1bit
				cr_writel(0x00000001, CR_EMMC_UHSREG); //non-DDR mode, SW 1.8V
				break;
			case 1:
				cr_writel(0x00000001, CR_EMMC_CTYPE); // 4bit
				cr_writel(0x00000001, CR_EMMC_UHSREG); //non-DDR mode, SW 1.8V
				break;
			case 2:
				cr_writel(0x00010000, CR_EMMC_CTYPE); // 8bit
				cr_writel(0x00000001, CR_EMMC_UHSREG); //non-DDR mode, SW 1.8V
				break;
			case 5:
				cr_writel(0x00000001, CR_EMMC_CTYPE); // 4bit
				cr_writel(0x00010001, CR_EMMC_UHSREG); //DDR mode, SW 1.8V
				break;
			case 6:
				cr_writel(0x00010000, CR_EMMC_CTYPE); // 8bit
				cr_writel(0x00010001, CR_EMMC_UHSREG); //DDR mode, SW 1.8V
				break;
			default:
				cr_writel(0x00010000, CR_EMMC_CTYPE); // 8bit
				cr_writel(0x00000001, CR_EMMC_UHSREG); //non-DDR mode, SW 1.8V
				break;
				break;			
		}
	}		
	else{
		printf("switch bus width to 0x");
		printf("%d",WIDTH * 4);
		printf(" bits fail\n");
	}	
}

int emmc_read_write_ip(UINT32 cmd_idx, UINT32 blk_addr, unsigned char *dma_addr, UINT32 dma_length){
	UINT32 ret_error = 0;

	//descriptor and dma must be in DDR
	cr_writel(0, CR_EMMC_SWC_SEL);
	cr_writel(0, CR_EMMC_CP);	


	CP15ISB;
	sync();

	make_ip_des((unsigned int)(uintptr_t)dma_addr, dma_length);
	flush_cache((unsigned int)(uintptr_t)dma_addr, dma_length);

	cr_writel(dma_length, CR_EMMC_BYTCNT);
	cr_writel((uintptr_t)rw_descriptor, CR_EMMC_DBADDR);
	cr_writel(0x0000ffff, CR_EMMC_RINTSTS);
	cr_writel(0x0000ffff, CR_EMMC_INTMASK);
	cr_writel(blk_addr,CR_EMMC_CMDARG);		
	CP15ISB;
	sync();

#ifdef DEBUG	
	prints("Emmc cmd = 0x");
	print_hex(cmd_idx);
	prints("\n");	
#endif


	/* -- eMMC CMD --
	 *  bit: name
	 *   6 : response_expect
	 *   8 : check_response_crc
	 *   9 : data_expected
	 *  10 : read/write (0 for read, 1 for write)
	 *  12 : send_auto_stop
	 */
	if (cmd_idx == MMC_READ_SINGLE_BLOCK || cmd_idx == MMC_SEND_EXT_CSD){
		cr_writel(0xa0000340|cmd_idx,CR_EMMC_CMD);		         
	}
	else if(cmd_idx==MMC_READ_MULTIPLE_BLOCK){   
		cr_writel(0xa0001340|cmd_idx,CR_EMMC_CMD);
	}
	else if(cmd_idx==MMC_WRITE_BLOCK){   
		cr_writel(0xa0000740|cmd_idx,CR_EMMC_CMD);		         
	}
	else if(cmd_idx==MMC_WRITE_MULTIPLE_BLOCK){   
		cr_writel(0xa0001740|cmd_idx,CR_EMMC_CMD);	
	}
	else{
		printf("Illegal command \n");
	}
	CP15ISB;
	sync();

	wait_done((UINT32 *)CR_EMMC_RINTSTS, 0x4, 0x4); //command done
	wait_done((UINT32 *)CR_EMMC_RINTSTS, 0x8, 0x8); //data transfer over

	CP15ISB;
	sync();

	if ((cmd_idx==MMC_READ_MULTIPLE_BLOCK) ||(cmd_idx==MMC_WRITE_MULTIPLE_BLOCK) ){
		wait_done((UINT32 *)CR_EMMC_RINTSTS, 0x4000, 0x4000); //auto command done (stop command done)
	}
	wait_done((UINT32 *)CR_EMMC_STATUS, 0x200, 0x0); 
	CP15ISB;
	sync();
	if ((ret_error = check_error(1))!=0){
		return ret_error;
	}

	else{
		return 0;
	} 	
}

#define ISO_MUXPAD      ( 0x9804e000 )
#define ISO_muxpad4     ( ISO_MUXPAD + 0x10 )
#define pfunc_emmc0     ( ISO_MUXPAD + 0x50 )
#define pfunc_emmc1     ( ISO_MUXPAD + 0x54 )
#define pfunc_emmc2     ( ISO_MUXPAD + 0x58 )
#define pfunc_emmc3     ( ISO_MUXPAD + 0x5c )
#define pfunc_emmc4     ( ISO_MUXPAD + 0x60 )
#define pfunc_emmc5     ( ISO_MUXPAD + 0x64 )

static void pad_driving(unsigned int clk_drv, unsigned int cmd_drv, unsigned int data_drv, unsigned int ds_drv)
{
	cr_writel(data_drv|(data_drv<<8)|(data_drv<<16)|(data_drv<<24), CR_EMMC_PDRIVE_NF1); //d0~d3	
	cr_writel(data_drv|(data_drv<<8)|(data_drv<<16)|(data_drv<<24), CR_EMMC_PDRIVE_NF2); //d4~d7	
	cr_writel((cr_readl(CR_EMMC_PDRIVE_NF3)&(0x00ff00ff))|(clk_drv<<8)|(cmd_drv<<24), CR_EMMC_PDRIVE_NF3); //d4~d7	
	cr_writel(ds_drv, CR_EMMC_PDRIVE_NF4); //data strobe
	CP15ISB;
    sync();
}

int kylin_cr_init(void){
	int n = 0, ret_err = 0;
	
	//Intialize
	cr_writel(0x00000081, CR_EMMC_BMOD);
	CP15ISB;
	sync();
	cr_writel(0x02000000, CR_EMMC_CTRL);
	CP15ISB;
	sync();
	cr_writel(0x00000001, CR_EMMC_PWREN);
	CP15ISB;
	sync();
	cr_writel(0x0000ffff, CR_EMMC_INTMASK);
	CP15ISB;
	sync();
	cr_writel(0xffffffff, CR_EMMC_RINTSTS);
	CP15ISB;
	sync();
	cr_writel(0x00000080, CR_EMMC_CLKDIV);
	CP15ISB;
	sync();
	cr_writel(0x00000000, CR_EMMC_CLKSRC);
	CP15ISB;
	sync();
	cr_writel(0x0001ffff, CR_EMMC_CLKENA);
	CP15ISB;
	sync();
	cr_writel(0xa0200000, CR_EMMC_CMD);
	CP15ISB;
	sync();
	cr_writel(0xffffff40, CR_EMMC_TMOUT);
	CP15ISB;
	sync();
	cr_writel(0x00000000, CR_EMMC_CTYPE);
	CP15ISB;
	sync();
	cr_writel(0x007f007f, CR_EMMC_FIFOTH);
	CP15ISB;
	sync();
	cr_writel(0x02000010, CR_EMMC_CTRL);
	CP15ISB;
	sync();
	cr_writel(0x00000080, CR_EMMC_BMOD);
	CP15ISB;
	sync();
	cr_writel(0x0000ffcf, CR_EMMC_INTMASK);
	CP15ISB;
	sync();
	//cr_writel(0x00600000, CR_EMMC_DBADDR);
	cr_writel(0x00000000, CR_EMMC_IDINTEN);
	CP15ISB;
	sync();
	cr_writel(0x0000ffff, CR_EMMC_RINTSTS);
	CP15ISB;
	sync();
	cr_writel(0x00000001, CR_EMMC_UHSREG);
	CP15ISB;
	sync();
	cr_writel(0x02000001, CR_EMMC_CARD_THR_CTL);
	CP15ISB;
	sync();
	
	
	//cr_writel(0xaaaa5aa8, 0x98012600);
	//CP15ISB;
	//sync();
	//Just for set mux to emmc mode

	//Card identification
	frequency(0x46, 0x80); //devider = 2 * 128 = 256	
	

	emmc_send_cmd_get_rsp(MMC_GO_IDLE_STATE, 0, 0, 0); //rsp_con: 0: no rsp, 1: short rsp, 3: long rsp
	emmc_send_cmd_get_rsp(MMC_GO_IDLE_STATE, 0, 0, 0); //rsp_con: 0: no rsp, 1: short rsp, 3: long rsp
	emmc_send_cmd_get_rsp(MMC_GO_IDLE_STATE, 0, 0, 0); //rsp_con: 0: no rsp, 1: short rsp, 3: long rsp
	emmc_send_cmd_get_rsp(MMC_GO_IDLE_STATE, 0, 0, 0); //rsp_con: 0: no rsp, 1: short rsp, 3: long rsp
	emmc_send_cmd_get_rsp(MMC_GO_IDLE_STATE, 0, 0, 0); //rsp_con: 0: no rsp, 1: short rsp, 3: long rsp
	CP15ISB;
	sync();
	
	ret_err = emmc_send_cmd_get_rsp(MMC_SEND_OP_COND, 0x40000080, 1, 0); //rsp_con: 0: no rsp, 1: short rsp, 3: long rsp

	CP15ISB;
	sync();

	while ((cr_readl(CR_EMMC_RESP0)&0x80000000)!=0x80000000){
		if(n++ > 0x100)
		{
			printf("CMD1 ERROR! \n");
			return ret_err;      
	 	}   
		ret_err = emmc_send_cmd_get_rsp(MMC_SEND_OP_COND, 0x40000080, 1, 0); //rsp_con: 0: no rsp, 1: short rsp, 3: long rsp
			
		CP15ISB;
		sync();
	}
	emmc_send_cmd_get_rsp(MMC_ALL_SEND_CID, 0, 3, 1); //rsp_con: 0: no rsp, 1: short rsp, 3: long rsp
	CP15ISB;
	sync();
	emmc_send_cmd_get_rsp(MMC_SET_RELATIVE_ADDR, emmc_card.rca, 1, 1); //rsp_con: 0: no rsp, 1: short rsp, 3: long rsp
	CP15ISB;
	sync();
	//Data Transfer Mode
	frequency(0x46, 0x4); //80M / 8 = 10M
	CP15ISB;
	sync();
	emmc_send_cmd_get_rsp(MMC_SEND_CSD, emmc_card.rca, 3, 1); //rsp_con: 0: no rsp, 1: short rsp, 3: long rsp
	CP15ISB;
	sync();
	emmc_send_cmd_get_rsp(MMC_SEND_CID, emmc_card.rca, 3, 1); //rsp_con: 0: no rsp, 1: short rsp, 3: long rsp
	CP15ISB;
	sync();
	emmc_send_cmd_get_rsp(MMC_SELECT_CARD, emmc_card.rca, 1, 1); //rsp_con: 0: no rsp, 1: short rsp, 3: long rsp
	CP15ISB;
	sync();
	emmc_send_cmd_get_rsp(MMC_SEND_STATUS, emmc_card.rca, 1, 1); //rsp_con: 0: no rsp, 1: short rsp, 3: long rsp
	CP15ISB;
	sync();
	printf("switch to SDR 8 bit\n");
	switch_bus(2);
	CP15ISB;
	sync();
	
//==================================================	
//Set the HS200
	
	emmc_read_write_ip(MMC_SEND_EXT_CSD, 0, ext_csd, 512);
	invalidate_dcache_range(PTR_U32(ext_csd), PTR_U32(ext_csd) + 512);
	
	/* ext_csd[196] shows weather this board supporting HS200 or not. */
	if ((ext_csd[196] & 0x10) == 0)
	{	
		HS200_PHASE_INHERITED = 0;
	}
	
	if (HS200_PHASE_INHERITED == 1)
	{
		//Data Transfer Mode @ HS200 mode: 200M
		switch_speed(2);
		cr_writel(0x2100, CR_EMMC_CKGEN_CTL);
		frequency(0xaf, 0);//divider = 1
		pad_driving(0xbb, 0xbb, 0xbb, 0x33);
		phase(savedVP0, savedVP1);
		printf("PLL_EMMC1 = 0x%08x\n", cr_readl(SYS_PLL_EMMC1));
		card_stop();
		polling_to_tran_state(MMC_CMD_READ_MULTIPLE_BLOCK,1);
		/*Preparing the environment before HS200 tuning*/
	}
	else
	{
		//switch to high speed
		switch_speed(1);
		//Data Transfer Mode @ HS mode: 50M
		frequency(0x57, 1);//divider = 2 * 1 = 2
		pad_driving(0x77, 0x77, 0x77, 0x33);
	}	
	
	#if 0
	if(get_rtd129x_cpu_revision() < RTD129x_CHIP_REVISION_B00){
		int err = 0;
		err = mmc_Tuning_HS200();
		if (err)
		{
			printf("[LY] hs200 tuning fail(%d)\n",err);
			return err;
		}
	}/*The parameters of HS200 are tuned in fsbl, when the board type is B00.*/
	#endif
	/*Tx and Rx parameters are tuned in FSBL.*/
//==================================================	
	
	return 0;
}


int rtk_eMMC_init( void )
{
    unsigned int tmp;
	int ret_err;
	int retry_counter;

	
	MY_CLR_ALIGN_BUFFER();
	MY_ALLOC_CACHE_ALIGN_BUFFER(char, dummy_buffer, 0x220);
	
	ext_csd = memalign(16, 512);
	memset(ext_csd, 0 ,512);
	rw_descriptor = memalign(8, EMMC_MAX_XFER_BLKCNT * sizeof(unsigned int) * 4);

	ret_err = -1;
	retry_counter = 3;
	rtkemmc_debug_msg = 1;
	rtkemmc_off_error_msg_in_init_flow = 1;
    sys_rsp17_addr = 0x00010000;   //rsp dma addr : 17B
    sys_ext_csd_addr = (unsigned char *)(uintptr_t)0x00180000; //ext csd dma addr : 512B
    ptr_ext_csd = (UINT8*)sys_ext_csd_addr;
    emmc_card.rca = 1<<16; 
    emmc_card.sector_addressing = 1;          

	savedVP0 = (cr_readl(SYS_PLL_EMMC1) & 0x000000f8) >> 3;
	savedVP1 = (cr_readl(SYS_PLL_EMMC1) & 0x00001f00) >> 8;
	/*Saving the tuned HS200 parameter for B00 board from SYS_PLL_EMMC1.*/

	cr_writel(0x03, SYS_PLL_EMMC1);     //LDO1.8V
	cr_writel(0, CR_EMMC_PAD_CTL);              //PAD to 1.8V
	udelay(200);

    #ifdef FOR_ICE_LOAD
    printf("\nemmc : PLL_EMMC1 = 0x");
    printf("%d",(unsigned int)REG32(SYS_PLL_EMMC1));
    #endif
    // work around for 8-byte alignment
    tmp = ((unsigned int)(uintptr_t)dummy_buffer)& 0xfffffff8;
    tmp += 0x00000008;
    dummy_512B = (unsigned char *)(uintptr_t)tmp; // 16-byte aligment

    #ifdef FOR_ICE_LOAD
    printf("\nemmc : dummy_buffer = 0x");
    printf("%d",(unsigned int)dummy_buffer);
    printf(", dummy_512B = 0x");
    printf("%d",(unsigned int)dummy_512B);
    printf("\n");
    #else
    //UPRINTF("\nemmc:%s(%d) %s %s\n", __FUNCTION__, reset_only, __DATE__, __TIME__);
    printf("\nemmc:dummy_buffer=0x%08x, dummy_512B=0x%08x\n", (unsigned int)(uintptr_t)dummy_buffer, (unsigned int)(uintptr_t)dummy_512B);
    #endif

	CP15ISB;
	sync();
    
	while( retry_counter-- ) {

		ret_err = kylin_cr_init();

		if( ret_err ) {
            #ifdef FOR_ICE_LOAD
            printf("emmc: init fail(");
            printf("%d",ret_err);
            printf(")\n");
            #else
			UPRINTF("\nemmc: init fail(%d)\n", ret_err);
            #endif
		}
		else {
			return ret_err;
		}
	}
	return ret_err;
}

void frequency(UINT32 fre, UINT32 div){
#ifndef FPGA
	cr_writel((cr_readl(SYS_PLL_EMMC3)&0xffff) | (fre << 16), SYS_PLL_EMMC3);
	CP15ISB;
	// ECO, if EMMC N/F code changed, toggle CR_EMMC_DUMMY_SYS bit 30
	cr_writel((~cr_readl(CR_EMMC_DUMMY_SYS)) & 0x40000000, CR_EMMC_DUMMY_SYS);
	CP15ISB;
	sync();
#endif
	wait_done((UINT32*)CR_EMMC_STATUS, 0x200, 0x0); 	 //card is not busy
	CP15ISB;
	sync();
	
	//disable clock
	cr_writel(0, CR_EMMC_CLKENA);
	CP15ISB;
	sync();

	//EMMC Cmd
	cr_writel(0xa0202000, CR_EMMC_CMD);
	CP15ISB;
	sync();
	wait_done((UINT32*)CR_EMMC_CMD, 0x80000000, 0x0);
	CP15ISB;
	sync();

	//set divider
	cr_writel(div, CR_EMMC_CLKDIV);
	CP15ISB;
	sync();

	//EMMC Cmd
	cr_writel(0xa0202000, CR_EMMC_CMD);
	CP15ISB;
	sync();
	wait_done((UINT32*)CR_EMMC_CMD, 0x80000000, 0x0);
	CP15ISB;
	sync();
	
	//enable clock
	cr_writel(0x10001, CR_EMMC_CLKENA);
	CP15ISB;
	sync();

	//EMMC Cmd
	cr_writel(0xa0202000, CR_EMMC_CMD);
	CP15ISB;
	sync();
	wait_done((UINT32*)CR_EMMC_CMD, 0x80000000, 0x0);
	CP15ISB;
	sync();
	

	printf("switch frequency to 0x");
	printf("%d",fre);
	printf("\n");

	printf("frequency divider is 0x");
	printf("%d",div);
	printf("\n");
		
	
}

int emmc_send_cmd_get_rsp(UINT32 cmd_idx, UINT32 sd_arg, UINT32 rsp_con, UINT32 crc){ 

	int ret_error = 0;
				
	cr_writel(0x0000ffff, CR_EMMC_RINTSTS); 		// clear all interrupt status
	CP15ISB;
	sync();
	cr_writel(0x0000ffff, CR_EMMC_INTMASK); 		// enable all interrupts					
	CP15ISB;
	sync();
	cr_writel(sd_arg, CR_EMMC_CMDARG);	// cmd argument
	CP15ISB;
	sync();

#ifdef DEBUG
	printf("Emmc cmd = 0x");
	printf("%d",cmd_idx);
	printf("\n");
#endif			
	cr_writel(0xa0000000|cmd_idx|(rsp_con<<6)|(crc<<8), CR_EMMC_CMD);	// cmd Register
	CP15ISB;
	sync();
	wait_done((UINT32 *)CR_EMMC_RINTSTS, 0x4, 0x4); 	
	wait_done((UINT32 *)CR_EMMC_STATUS, 0x200, 0x0); 	
	CP15ISB;
	sync();

#ifdef DEBUG
	printf("Emmc Resp0 = 0x");
	printf("%d",cr_readl(CR_EMMC_RESP0));
	printf("\n");
	printf("Emmc Resp1 = 0x");
	printf("%d",cr_readl(CR_EMMC_RESP1));
	printf("\n");
	printf("Emmc Resp2 = 0x");
	printf("%d",cr_readl(CR_EMMC_RESP2));
	printf("\n");
	printf("Emmc Resp3 = 0x");
	printf("%d",cr_readl(CR_EMMC_RESP3));
	printf("\n");
#endif	

	if( cmd_idx == MMC_SEND_CID ){
		emmc_cid[3] = SWAP_32(cr_readl(CR_EMMC_RESP0));
		emmc_cid[2] = SWAP_32(cr_readl(CR_EMMC_RESP1));
		emmc_cid[1] = SWAP_32(cr_readl(CR_EMMC_RESP2));
		emmc_cid[0] = SWAP_32(cr_readl(CR_EMMC_RESP3));
	}

	if ((ret_error = check_error(1))==0)
	{	
		return 0;
	}
	else 
	{
		reset_ip();
		return ret_error;
	}		
}	

void switch_speed(UINT8 speed){
	int speed_modify=speed;
	if ((speed==0 )||(speed==1)){
		speed_modify=1;
	}
	CP15ISB;
	//speed - 0, backward compatible timing, 1: High speed, 2: HS200
	emmc_send_cmd_get_rsp(MMC_SWITCH, 0x03b90000|(speed_modify<<8), 1, 1);	
	emmc_send_cmd_get_rsp(MMC_SEND_STATUS, emmc_card.rca, 1, 1);
	CP15ISB;
	if ((cr_readl(CR_EMMC_RESP0)&0x80)==0){
		printf("switch speed to 0x");
		printf("%d",speed);
		printf(" success\n");
	}	
	else{
		printf("switch speed to 0x");
		printf("%d",speed);
		printf(" fail\n");
	}	
}

