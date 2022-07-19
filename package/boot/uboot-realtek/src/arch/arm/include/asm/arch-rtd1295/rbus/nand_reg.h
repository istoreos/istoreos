/******************************************************************************
 * 
 * Overview: Realtek Nand Flash HW Controller Register Map
 * Copyright (c) 2008 Realtek Semiconductor Corp. All Rights Reserved.
 * Modification History:
 *    #000 2012-12-07  AlexChang   create file
 * 
 *******************************************************************************/
#ifndef __NAND_REG_H
#define __NAND_REG_H
//========================================================================

//CRT registers for NAND driver
#define REG_CLOCK_ENABLE1			(0x9800000c)		// 23: Clock enable bit for NAND
//#define REG_MUXPAD7				(0xb800036c)
#define REG_NF_CKSEL				(0x98000038)

//===================================================================
//NAND flash register definition
//#define REG_DDR_BASE_ADDR				(0x80000000)
#define REG_NF_BASE_ADDR				(0x98010000)

#define REG_ND_PA0						( REG_NF_BASE_ADDR + 0 ) 		//Page address 0 [7:0]
#define	REG_ND_PA1						( REG_NF_BASE_ADDR + 0x4 )		//Page address 1 [15:8]
#define	REG_ND_PA2						( REG_NF_BASE_ADDR + 0x8 )		//Page address 2 [20:16]
#define	REG_ND_CA0				  		( REG_NF_BASE_ADDR + 0xc )		//Column address 0 [7:0]
#define	REG_ND_CMD						( REG_NF_BASE_ADDR + 0x10 )		//Command [7:0]
#define	REG_ND_DAT						( REG_NF_BASE_ADDR + 0x14 )		//NAND Data[7:0](Status_0)
#define	REG_ND_CTL						( REG_NF_BASE_ADDR + 0x18 )		//NAND control register
#define	REG_CMD3						( REG_NF_BASE_ADDR + 0x28 )		//CMD3 is the third command that would be transfer out by auto mode case 0/1/2
#define	REG_ND_PA3						( REG_NF_BASE_ADDR + 0x2c )		//Page address 3 [23:21]
#define REG_POLL_FSTS					( REG_NF_BASE_ADDR + 0x30 )		//Polling nand flash status
#define REG_BLANK_CHK					( REG_NF_BASE_ADDR + 0x34 )		//Enable blank check function
#define REG_ND_ECC						( REG_NF_BASE_ADDR + 0x38 )		//Indicate ECC status
#define	REG_ND_CA1						( REG_NF_BASE_ADDR + 0x3c )		//Column address [15:8]
#define	REG_DATA_TL0					( REG_NF_BASE_ADDR + 0x100 )	//Data transfer count [7:0]...
#define	REG_DATA_TL1					( REG_NF_BASE_ADDR + 0x104 )	//Data transfer count [13:8]...
#define REG_DMA1_CTL					( REG_NF_BASE_ADDR + 0x10c )	//DMA1 control register
#define REG_PP_CTL0						( REG_NF_BASE_ADDR + 0x110 )	//Ping-Pong buffer control register
#define REG_ECC_SEL						( REG_NF_BASE_ADDR + 0x128 )
#define REG_PP_CTL1						( REG_NF_BASE_ADDR + 0x12c )	//PP starting address [7:0], this filedspecifies the starting address of the Ping-Pong buffer to put the data
#define	REG_PD							( REG_NF_BASE_ADDR + 0x130 )	//PDx. Flash Chip Enable Output
#define REG_DUMMY_NF1					( REG_NF_BASE_ADDR + 0x158 )	//NF clock dummy bit
#define REG_DUMMY_NF2					( REG_NF_BASE_ADDR + 0x15c )	//NF clock dummy bit
#define REG_DUMMY_NF3					( REG_NF_BASE_ADDR + 0x160 )	//NF clock dummy bit
#define REG_DUMMY_NF4					( REG_NF_BASE_ADDR + 0x164 )	//NF clock dummy bit
#define REG_AUTO_TRIG					( REG_NF_BASE_ADDR + 0x200 )	//Auto trigger register control
#define REG_RSECC_NUM					( REG_NF_BASE_ADDR + 0x204 )	//ECC_NUM RS ECC error symbol count.
#define REG_READ_BY_PP					( REG_NF_BASE_ADDR + 0x228 )	//Setting data read to DRAM from NAND through by PP or not
#define REG_MAX_ECC_NUM					( REG_NF_BASE_ADDR + 0x22c )	//Auto mode(Mode 000) read status 
#define REG_TIME_PARA3					( REG_NF_BASE_ADDR + 0x234 )	//NAND flash AC timming setting
#define REG_TIME_PARA2					( REG_NF_BASE_ADDR + 0x238 )	//NAND flash AC timming setting
#define REG_TIME_PARA1					( REG_NF_BASE_ADDR + 0x23c )	//NAND flash AC timming setting
#define REG_PIN_MUX_STOP				( REG_NF_BASE_ADDR + 0x25c )	//Enable Pin_Mux_Stop function
#define REG_DELAY_CTL					( REG_NF_BASE_ADDR + 0x260 )    //Flash timing delay clock number control
#define	REG_ECC_STOP					( REG_NF_BASE_ADDR + 0x264 )	//Data read from NAND to SRAM don't stop transfer when ECC error occurs 
#define	REG_ECC_PAGE					( REG_NF_BASE_ADDR + 0x268 )	//Used in data reading from NAND flash to TBRAM, and ECC_N_STOP was set.
#define	REG_PAGE_CNT					( REG_NF_BASE_ADDR + 0x26c )	//Data page count that had been transferred.
#define	REG_PAGE_LEN					( REG_NF_BASE_ADDR + 0x270 )	//Set the data length would be transferred by auto mode.
#define	REG_CMD2						( REG_NF_BASE_ADDR + 0x274 )	//This is the secone command that would be transfer out by auto mode case 0/1/2.
#define	REG_MULTI_CHNL_MODE				( REG_NF_BASE_ADDR + 0x27c )	//Multi-channel control register
#define REG_SRAM_CTL					( REG_NF_BASE_ADDR + 0x300 )	//SRAM control register
#define	REG_DMA_CTL1					( REG_NF_BASE_ADDR + 0x304 )	//DRAM start address for DMA transfer.
#define	REG_DMA_CTL2					( REG_NF_BASE_ADDR + 0x308 )    //Transfer length for DMA transfer between DMA buffer and DDR.(512B Unit)
#define	REG_DMA_CTL3					( REG_NF_BASE_ADDR + 0x30c )	//Set to control data transfer between DRAM and DMA buffer.
#define	REG_NAND_ISR					( REG_NF_BASE_ADDR + 0x324 )	//NAND ISR status register
#define	REG_NAND_ISREN					( REG_NF_BASE_ADDR + 0x328 )	//NAND ISR enable register
#define	REG_DUMMY_SYS					( REG_NF_BASE_ADDR + 0x32c )	//Dummy
#define	REG_DBG							( REG_NF_BASE_ADDR + 0x344 )	
#define	REG_SPR_DDR_CTL					( REG_NF_BASE_ADDR + 0x348 )	
#define	REG_CP_LEN						( REG_NF_BASE_ADDR + 0x34C )	

#define	REG_RND_CMD1					(REG_NF_BASE_ADDR + 0x208)
#define	REG_RND_CMD2					(REG_NF_BASE_ADDR + 0x20c)
#define	REG_RND_DATA_STR_COL_H			(REG_NF_BASE_ADDR + 0x210)
#define	REG_RND_SPR_STR_COL_H			(REG_NF_BASE_ADDR + 0x214)
#define	REG_RND_SPR_STR_COL_L			(REG_NF_BASE_ADDR + 0x218)
#define	REG_RND_EN						(REG_NF_BASE_ADDR + 0x21c)

#define REG_RMZ_CTRL					(REG_NF_BASE_ADDR + 0x240)
#define REG_RMZ_SEED_L					(REG_NF_BASE_ADDR + 0x244)
#define REG_RMZ_SEED_H					(REG_NF_BASE_ADDR + 0x248)


/*
 * Defines for the CP.
 */
#define REG_CP_BASE_ADDR				(0x18015000)
#define REG_MCP_CTRL					(REG_CP_BASE_ADDR+0x100)
#define REG_MCP_STATUS					(REG_CP_BASE_ADDR+0x104)
#define REG_MCP_EN						(REG_CP_BASE_ADDR+0x108)
#define REG_MCP_CTRL1					(REG_CP_BASE_ADDR+0x198)
#define REG_MCP_BASE					(REG_CP_BASE_ADDR+0x10C)
#define REG_MCP_LIMIT					(REG_CP_BASE_ADDR+0x110)
#define REG_MCP_RDPTR					(REG_CP_BASE_ADDR+0x114)
#define REG_MCP_WRPTR					(REG_CP_BASE_ADDR+0x118)
#define REG_MCP_DES_COUNT				(REG_CP_BASE_ADDR+0x134)
#define REG_MCP_DES_COMPARE				(REG_CP_BASE_ADDR+0x138)
#define REG_MCP_DES_INI_KEY				(REG_CP_BASE_ADDR+0x11C)
#define REG_MCP_AES_INI_KEY				(REG_CP_BASE_ADDR+0x124)
#define REG_MCP_MULTI2_SYS_KEY			(REG_CP_BASE_ADDR+0x178)
#define REG_OTP_LOAD					(REG_CP_BASE_ADDR+0x19C)
#define REG_K_MCP_CTRL					(REG_CP_BASE_ADDR+0x900)
#define REG_K_MCP_STATUS				(REG_CP_BASE_ADDR+0x904)
#define REG_K_MCP_EN					(REG_CP_BASE_ADDR+0x908)
#define REG_K_MCP_CTRL1					(REG_CP_BASE_ADDR+0x998)
#define REG_K_MCP_BASE					(REG_CP_BASE_ADDR+0x90C)
#define REG_K_MCP_LIMIT					(REG_CP_BASE_ADDR+0x910)
#define REG_K_MCP_RDPTR					(REG_CP_BASE_ADDR+0x914)
#define REG_K_MCP_WRPTR					(REG_CP_BASE_ADDR+0x918)
#define REG_K_MCP_DES_COUNT				(REG_CP_BASE_ADDR+0x934)
#define REG_K_MCP_DES_COMPARE			(REG_CP_BASE_ADDR+0x938)
#define REG_K_MCP_DES_INI_KEY			(REG_CP_BASE_ADDR+0x91C)
#define REG_K_MCP_AES_INI_KEY			(REG_CP_BASE_ADDR+0x924)
#define REG_K_MCP_MULTI2_SYS_KEY		(REG_CP_BASE_ADDR+0x978)
#define REG_CP_REG_KEY					(REG_CP_BASE_ADDR+0x034)
#define REG_CP_REG_DATAIN				(REG_CP_BASE_ADDR+0x044)	
#define REG_CP_REG_DATAOUT				(REG_CP_BASE_ADDR+0x054)
#define REG_CP_REG_IV					(REG_CP_BASE_ADDR+0x064)
#define REG_CP_REG_SET					(REG_CP_BASE_ADDR+0x074)
#define REG_CP_REG_SET1					(REG_CP_BASE_ADDR+0x078)
#define REG_CP_REG_SET2					(REG_CP_BASE_ADDR+0x07C)
#define REG_TP_KEY_INFO					(0x18014058)
#define REG_TP_KEY_CTRL					(0x18014060)
#define REG_CP_SCTCH					(REG_CP_BASE_ADDR+0x080)
#define REG_CP_NF_KEY					(REG_CP_BASE_ADDR+0x084)
#define REG_CP_NF_INI_KEY				(REG_CP_BASE_ADDR+0x094)
#define REG_CP_NF_SET					(REG_CP_BASE_ADDR+0x0A4)
#define REG_CP_MD_KEY					(REG_CP_BASE_ADDR+0x0A8)
#define REG_CP_MD_INI_KEY				(REG_CP_BASE_ADDR+0x0B8)
#define REG_CP_MD_SET					(REG_CP_BASE_ADDR+0x0C8)
#define REG_K_CP_REG_KEY				(REG_CP_BASE_ADDR+0x834)
#define REG_K_CP_REG_DATAIN				(REG_CP_BASE_ADDR+0x844)
#define REG_K_CP_REG_DATAOUT			(REG_CP_BASE_ADDR+0x854)
#define REG_K_CP_REG_IV					(REG_CP_BASE_ADDR+0x864)
#define REG_K_CP_REG_SET				(REG_CP_BASE_ADDR+0x874)
#define REG_K_CP_REG_SET1				(REG_CP_BASE_ADDR+0x878)
#define REG_K_CP_REG_SET2				(REG_CP_BASE_ADDR+0x87C)
#define REG_CP_DBG						(REG_CP_BASE_ADDR+0x0CC)
#define REG_MCP_ST						(REG_CP_BASE_ADDR+0x1A0)

#define CP_NF_SET		(REG_NF_BASE_ADDR + 0x50a4)

#define CP_NF_INI_KEY_0	(REG_NF_BASE_ADDR + 0x5094)
#define CP_NF_INI_KEY_1	(REG_NF_BASE_ADDR + 0x5098)
#define CP_NF_INI_KEY_2	(REG_NF_BASE_ADDR + 0x509c)
#define CP_NF_INI_KEY_3	(REG_NF_BASE_ADDR + 0x50a0)

#define CP_NF_KEY_0		(REG_NF_BASE_ADDR + 0x5084)
#define CP_NF_KEY_1		(REG_NF_BASE_ADDR + 0x5088)
#define CP_NF_KEY_2		(REG_NF_BASE_ADDR + 0x508c)
#define CP_NF_KEY_3		(REG_NF_BASE_ADDR + 0x5090)

#define CP_NF_NONE       0
#define CP_NF_AES_ECB_128        1
#define CP_NF_AES_CBC_128        2

/***************************************************/
/* kylin otp register definition                                          */
/***************************************************/
#define OTP_REG_BASE    	 	0x98017000
//regs
#define OTP_EF_CTRL				(OTP_REG_BASE+0x400)
#define OTP_EF_CTRL_ST			(OTP_REG_BASE+0x404)
#define OTP_EF_RD_DONE			(OTP_REG_BASE+0x410)
#define OTP_DATA				(OTP_REG_BASE + 0)
//efuse bit
#define OTP_K_RSA				0
#define OTP_K_S                 2048
#define OTP_K_H					2304
#define OTP_K_N                 2560
#define OTP_CHIPID      		3360
#define OTP_BIT_SECUREBOOT		3494
#define OTP_OFST_KEYSEL_0		3488
#define OTP_OFST_KEYSEL_1		3489
#define OTP_RMA_ENABLE0			3507
#define OTP_RMA_ENABLE1			3508
#define OTP_RMA_ENABLE2			3509
#define OTP_RMA_ENABLE3			3510
#define OTP_BOOT_ENC			3515
#define OTP_USB2SRAM			3522
#define OTP_RESV_MP_TEST2       3594
#define OTP_HWSET_CHK_0         3595
#define OTP_HWSET_CHK_1         3596
#define OTP_LOAD_SECURE_OS      3598
#define OTP_DIS_ONE_CORE        3599
#define OTP_BIT_KDBG			2816
#define OTP_DUMMY_RD_REG        4064

#define OTP_PRO_EFUSE_ST        (1<<16)
#define EF_Rd_done_bit			(1<<1)
#define OTP_REG_ADDR(x)			(OTP_REG_BASE+x)

//#define REG32( addr )		  (*(volatile unsigned int *)(addr))

//===================================================================
//#define REG_ND_PA0					( REG_NF_BASE_ADDR + 0 ) 		//Page address 0 [7:0]
#define NF_ND_PA0_page_addr0(value)  (0x000000FF&((value)<<0))

//#define	REG_ND_PA1					( REG_NF_BASE_ADDR + 0x4 )		//Page address 1 [15:8]
#define NF_ND_PA1_page_addr1(value)  (0x000000FF&((value)<<0))

//#define	REG_ND_PA2					( REG_NF_BASE_ADDR + 0x8 )		//Page address 2 [20:16]
#define NF_ND_PA2_addr_mode(value)    (0x000000E0&((value)<<5))
#define NF_ND_PA2_page_addr2(value)   (0x0000001F&((value)<<0))

//#define	REG_ND_CA0				    ( REG_NF_BASE_ADDR + 0xc )		//Column address 0 [7:0]
#define NF_ND_CA0_col_addr0(value)   (0x000000FF&((value)<<0))

//#define	REG_ND_CMD					( REG_NF_BASE_ADDR + 0x10 )		//Command [7:0]
#define NF_ND_CMD_cmd(value)         (0x000000FF&((value)<<0))

//#define	REG_ND_DAT					( REG_NF_BASE_ADDR + 0x14 )		//NAND Data[7:0](Status_0)
#define NF_ND_DAT_dat(value)         (0x000000FF&((value)<<0))

//#define	REG_ND_CTL					( REG_NF_BASE_ADDR + 0x18 )		//NAND control register
#define NF_ND_CTL_xfer(value)        (0x00000080&((value)<<7))
#define NF_ND_CTL_ready_busy(value)  (0x00000040&((value)<<6))
#define NF_ND_CTL_ecc_tran(value)    (0x00000020&((value)<<5))
#define NF_ND_CTL_ecc_enable(value)  (0x00000008&((value)<<3))
#define NF_ND_CTL_tran_mode(value)   (0x00000007&((value)<<0))

//#define	REG_CMD3					( REG_NF_BASE_ADDR + 0x28 )		//CMD3 is the third command that would be transfer out by auto mode case 0/1/2
#define NF_CMD3_cmd3(value)          (0x000000FF&((value)<<0))

//#define	REG_ND_PA3					( REG_NF_BASE_ADDR + 0x2c )		//Page address 3 [23:21]
#define NF_ND_PA3_page_addr3(value)  (0x000000E0&((value)<<5))

//#define REG_POLL_FSTS				   ( REG_NF_BASE_ADDR + 0x30 )		//Polling nand flash status
#define NF_POLL_FSTS_bit_sel(value)   (0x0000000E&((value)<<1))
#define NF_POLL_FSTS_trig_poll(value) (0x00000001&((value)<<0))

//#define REG_BLANK_CHK				( REG_NF_BASE_ADDR + 0x34 )		//Enable blank check function
#define NF_BLANK_CHK_read_ecc_xnor_ena(value)	(0x00000004&((value)<<2))
#define NF_BLANK_CHK_blank_all_one(value)  (0x00000002&((value)<<1))
#define NF_BLANK_CHK_blank_ena(value)      (0x00000001&((value)<<0))

//#define REG_ND_ECC			( REG_NF_BASE_ADDR + 0x38 )		//Indicate ECC status
#define NF_ND_ECC_ecc_not_clr(value)  (0x00000008&((value)<<3))
#define NF_ND_ECC_ecc_err(value)       (0x00000004&((value)<<2))

//#define	REG_ND_CA1					( REG_NF_BASE_ADDR + 0x3c )		//Column address [15:8]
#define NF_ND_CA1_col_addr1(value)   (0x000000FF&((value)<<0))

//#define	REG_DATA_TL0				( REG_NF_BASE_ADDR + 0x100 )	//Data transfer count [7:0]...
#define NF_DATA_TL0_length0(value)  (0x000000FF&((value)<<0))

//#define	REG_DATA_TL1				( REG_NF_BASE_ADDR + 0x104 )	//Data transfer count [13:8]...
#define NF_DATA_TL1_access_mode(value)  (0x00000080&((value)<<7))
#define NF_DATA_TL1_sram_path(value)    (0x00000040&((value)<<6))
#define NF_DATA_TL1_length1(value)      (0x0000003F&((value)<<0))

//#define REG_DMA1_CTL				( REG_NF_BASE_ADDR + 0x10c )	//DMA1 control register
#define NF_DMA1_CTL_eot_gen(value)     (0x00000008&((value)<<3))
#define NF_DMA1_CTL_dma_max_pkt(value) (0x00000004&((value)<<2))
#define NF_DMA1_CTL_spec_pkt(value)    (0x00000002&((value)<<1))

//#define REG_PP_CTL0					( REG_NF_BASE_ADDR + 0x110 )	//Ping-Pong buffer control register
#define NF_PP_CTL0_pp_start_addr(value)    (0x00000030&((value)<<4))
#define NF_PP_CTL0_pp_busy(value)          (0x00000004&((value)<<2))
#define NF_PP_CTL0_pp_reset(value)         (0x00000002&((value)<<1))
#define NF_PP_CTL0_pp_enable(value)        (0x00000001&((value)<<0))

//#define REG_ECC_SEL					( REG_NF_BASE_ADDR + 0x128 )
#define NF_ECC_SEL_ecc_bch_24b_ena(value)        (0x00000002&((value)<<1))
#define NF_ECC_SEL_ecc_bch_12b_ena(value)        (0x00000001&((value)<<0))

//#define REG_PP_CTL1					( REG_NF_BASE_ADDR + 0x12c )	//PP starting address [7:0], this filedspecifies the starting address of the Ping-Pong buffer to put the data
#define NF_PP_CTL1_pp_start_addr(value)   (0x000000FF&((value)<<0))

//#define	REG_PD						( REG_NF_BASE_ADDR + 0x130 )	//PDx. Flash Chip Enable Output
#define NF_PD_pd(value)              (0x0000001F&((value)<<0))

//#define REG_DUMMY_NF1				( REG_NF_BASE_ADDR + 0x158 )	//NF clock dummy bit
#define NF_DUMMY_NF1_Dmy1(value)     (0x000000FF&((value)<<0))

//#define REG_DUMMY_NF2				( REG_NF_BASE_ADDR + 0x15c )	//NF clock dummy bit
#define NF_DUMMY_NF2_Dmy2(value)     (0x000000FF&((value)<<0))

//#define REG_DUMMY_NF3				( REG_NF_BASE_ADDR + 0x160 )	//NF clock dummy bit
#define NF_DUMMY_NF3_Dmy3(value)     (0x000000FF&((value)<<0))

//#define REG_DUMMY_NF4				( REG_NF_BASE_ADDR + 0x164 )	//NF clock dummy bit
#define NF_DUMMY_NF4_Dmy4(value)     (0x000000FF&((value)<<0))

//#define REG_AUTO_TRIG				( REG_NF_BASE_ADDR + 0x200 )	//Auto trigger register control
#define NF_AUTO_TRIG_auto_trig(value)        (0x00000080&((value)<<7))
#define NF_AUTO_TRIG_addr_fbd(value)         (0x00000040&((value)<<6))
#define NF_AUTO_TRIG_pp_empty(value)         (0x00000020&((value)<<5))
#define NF_AUTO_TRIG_spec_auto_case(value)   (0x00000018&((value)<<3))
#define NF_AUTO_TRIG_auto_case(value)        (0x00000007&((value)<<0))

//#define REG_RSECC_NUM				( REG_NF_BASE_ADDR + 0x204 )	//ECC_NUM RS ECC error symbol count.
#define NF_RSECC_NUM_ecc_num(value)  (0x00000001F&((value)<<0))

//#define REG_READ_BY_PP				( REG_NF_BASE_ADDR + 0x228 )	//Setting data read to DRAM from NAND through by PP or not
#define NF_READ_BY_PP_read_by_pp(value)  (0x00000080&((value)<<7))

//#define REG_MAX_ECC_NUM				( REG_NF_BASE_ADDR + 0x22c )	//Auto mode(Mode 000) read status 
#define REG_MAX_ECC_NUM_max_ecc_num(value)  (0x00000001F&((value)<<0))

//#define REG_TIME_PARA3				( REG_NF_BASE_ADDR + 0x234 )	//NAND flash AC timming setting
#define NF_TIME_PARA3_T3(value)      (0x000000FF&((value)<<0))

//#define REG_TIME_PARA2				( REG_NF_BASE_ADDR + 0x238 )	//NAND flash AC timming setting
#define NF_TIME_PARA2_T2(value)      (0x000000FF&((value)<<0))

//#define REG_TIME_PARA1				( REG_NF_BASE_ADDR + 0x23c )	//NAND flash AC timming setting
#define NF_TIME_PARA1_T1(value)      (0x000000FF&((value)<<0))

//#define REG_PIN_MUX_STOP			( REG_NF_BASE_ADDR + 0x25c )	//Enable Pin_Mux_Stop function
#define NF_PIN_MUX_STOP_pin_stop(value)          (0x00000004&((value)<<2))
#define NF_PIN_MUX_STOP_intlev_pin_ena(value)    (0x00000002&((value)<<1))
#define NF_PIN_MUX_STOP_pin_mux_enae(value)      (0x00000001&((value)<<0))

//#define REG_DELAY_CTL				( REG_NF_BASE_ADDR + 0x260 )    //Flash timing delay clock number control
#define NF_DELAY_CTL_T_swait_busy(value)   (0x000000C0&((value)<<6))
#define NF_DELAY_CTL_T_WHR_ADL(value)      (0x0000003F&((value)<<0))

//#define	REG_ECC_STOP				( REG_NF_BASE_ADDR + 0x264 )	//Data read from NAND to SRAM don't stop transfer when ECC error occurs 
#define NF_ECC_STOP_ecc_n_stop(value)      (0x00000080&((value)<<7))

//#define	REG_ECC_PAGE				( REG_NF_BASE_ADDR + 0x268 )	//Used in data reading from NAND flash to TBRAM, and ECC_N_STOP was set.
#define NF_ECC_PAGE_ecc_page(value)  (0x000000FF&((value)<<0))

//#define	REG_PAGE_CNT				( REG_NF_BASE_ADDR + 0x26c )	//Data page count that had been transferred.
#define NF_PAGE_CNT_page_cnt(value)  (0x000000FF&((value)<<0))

//#define	REG_PAGE_LEN				( REG_NF_BASE_ADDR + 0x270 )	//Set the data length would be transferred by auto mode.
#define NF_PAGE_LEN_page_len(value)  (0x000000FF&((value)<<0))

//#define	REG_CMD2					( REG_NF_BASE_ADDR + 0x274 )	//This is the secone command that would be transfer out by auto mode case 0/1/2.
#define NF_CMD2_cmd2(value)          (0x000000FF&((value)<<0))

//#define	REG_MULTI_CHNL_MODE			( REG_NF_BASE_ADDR + 0x27c )	//Multi-channel control register
#define NF_MULTI_CHNL_MODE_ecc_pass(value)      (0x00000080&((value)<<7))
#define NF_MULTI_CHNL_MODE_ecc_no_check(value)  (0x00000040&((value)<<6))
#define NF_MULTI_CHNL_MODE_edo(value)           (0x00000020&((value)<<5))
#define NF_MULTI_CHNL_MODE_no_wait_busy(value)  (0x00000010&((value)<<4))
#define NF_MULTI_CHNL_MODE_wait_ready(value)    (0x0000000C&((value)<<2))
#define NF_MULTI_CHNL_MODE_multi_chnl_md(value) (0x00000003&((value)<<0))

#define REG_SRAM_CTL				( REG_NF_BASE_ADDR + 0x300 )	//SRAM control register
#define NF_SRAM_CTL_map_sel(value)     (0x00000020&((value)<<5))
#define NF_SRAM_CTL_access_en(value)   (0x00000010&((value)<<4))
#define NF_SRAM_CTL_mem_region(value)  (0x0000000F&((value)<<0))

//#define	REG_DMA_CTL1				( REG_NF_BASE_ADDR + 0x304 )	//DRAM start address for DMA transfer.
#define NF_DMA_CTL1_dram_sa(value)   (0x0FFFFFFF&((value)<<0))

//#define	REG_DMA_CTL2				( REG_NF_BASE_ADDR + 0x308 )    //Transfer length for DMA transfer between DMA buffer and DDR.(512B Unit)
#define NF_DMA_CTL2_dma_len(value)   (0x0000FFFF&((value)<<0))

//#define	REG_DMA_CTL3				( REG_NF_BASE_ADDR + 0x30c )	//Set to control data transfer between DRAM and DMA buffer.
#define NF_DMA_CTL3_cp_first(value)	 (0x00000008&((value)<<3))
#define NF_DMA_CTL3_cp_enable(value) (0x00000004&((value)<<2))	
#define NF_DMA_CTL3_ddr_wr(value)    (0x00000002&((value)<<1))
#define NF_DMA_CTL3_dma_xfer(value)  (0x00000001&((value)<<0))

//#define	REG_NAND_ISR				( REG_NF_BASE_ADDR + 0x324 )	//NAND ISR status register
#define NF_NAND_ISR_Int5(value)        (0x00000020&((value)<<5))
#define NF_NAND_ISR_Int4(value)        (0x00000010&((value)<<4))
#define NF_NAND_ISR_Int3(value)        (0x00000008&((value)<<3))
#define NF_NAND_ISR_Int2(value)        (0x00000004&((value)<<2))
#define NF_NAND_ISR_Int1(value)        (0x00000002&((value)<<1))
#define NF_NAND_ISR_write_data(value)  (0x00000001&((value)<<0))

//#define	REG_NAND_ISREN				( REG_NF_BASE_ADDR + 0x328 )	//NAND ISR enable register
#define NF_NAND_ISREN_Int5En(value)      (0x00000020&((value)<<5))
#define NF_NAND_ISREN_Int4En(value)      (0x00000010&((value)<<4))
#define NF_NAND_ISREN_Int3En(value)      (0x00000008&((value)<<3))
#define NF_NAND_ISREN_Int2En(value)      (0x00000004&((value)<<2))
#define NF_NAND_ISREN_Int1En(value)      (0x00000002&((value)<<1))
#define NF_NAND_ISREN_write_data(value)  (0x00000001&((value)<<0))

//#define	REG_DUMMY_SYS				( REG_NF_BASE_ADDR + 0x32c )	//Dummy
#define NF_DUMMY_SYS_dmy(value)      (0xFFFFFFFF&((value)<<0))

//#define	REG_DBG						( REG_NF_BASE_ADDR + 0x344 )	

//#define	REG_SPR_DDR_CTL					( REG_NF_BASE_ADDR + 0x348 )	
#define NF_SPR_DDR_CTL_cr_nf_hw_pinmux_ena(value)  (0x40000000&((value)<<30))
#define NF_SPR_DDR_CTL_spare_ddr_ena(value)  (0x40000000&((value)<<30))
#define NF_SPR_DDR_CTL_per_2k_spr_ena(value)  (0x20000000&((value)<<29))
#define NF_SPR_DDR_CTL_spare_dram_sa(value)  (0x0FFFFFFF&((value)<<0))

//#define	REG_CP_LEN					( REG_NF_BASE_ADDR + 0x34C )	
#define NF_CP_LEN_cp_length(value)  (0x01FFFE00&((value)<<9))



#endif

