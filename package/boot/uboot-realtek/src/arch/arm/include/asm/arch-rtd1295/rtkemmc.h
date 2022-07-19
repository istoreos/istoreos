#ifndef __RTKEMMC_H__
#define __RTKEMMC_H__

#include <asm/arch/rbus/sb2_reg.h>
/************************************************************************
 * DEBUG CONTROL
*************************************************************************/
#define UINT8   unsigned char
#define UINT16  unsigned short
#define UINT32  unsigned int
#define UINT64  unsigned long
#define INT8    char
#define INT16   short
#define INT32   int
#define INT64	long

#define REG8( addr )		  (*(volatile UINT8 *) (addr))
#define REG16( addr )		  (*(volatile UINT16 *)(addr))
#define REG32( addr )		  (*(volatile UINT32 *)(addr))
#define REG64( addr )		  (*(volatile UINT64 *)(addr))

#define __align16__ __attribute__((aligned (16)))

#define S_EXT_CSD_ADDR        0xa00000
#define EXT_CSD_BUFFER_SIZE   0x200
#define S_RSP17_ADDR          (S_EXT_CSD_ADDR+EXT_CSD_BUFFER_SIZE)
#define EMMC_BLK_SIZE         0x200
#define MAX_CMD_RETRY_COUNT    4

//#define MMC_DEBUG		//mmc debug msg
//#define FORCE_CHIP_REVB		//for 1195 rev.A chip, run at rev.B 1.8v case
#define FORCE_CHG_SDR50_MODE	//pretend ddr/sd30 fail, change to sdr20 by read blk #0x9999
#ifdef MMC_DEBUG
#define MMCCMDPRINTF(fmt, args...)   printf(fmt,## args)
#define MMCPRINTF(fmt, args...)   printf(fmt,## args)
#define RDPRINTF(fmt, args...)   printf(fmt,## args)  //r/w
#define MPRINTF(fmt, args...)   printf(fmt,## args)   //micron disable standy procedure
#else
#define RDPRINTF(fmt, args...)
#define MMCPRINTF(fmt, args...)
#define MPRINTF(fmt, args...)
#endif
#define FORCE_SECTOR_MODE
/************************************************************************
 * DEBUG CONTROL
*************************************************************************/
#define EMMC_DEBUG
//#define EMMC_DEBUG_SHOWCMD
//#define EMMC_SHOW_CSD
//#define EMMC_SHOW_CID
//#define EMMC_SHOW_EXTCSD
#define EMMC_SPLIT_BLK

/************************************************************************
 * CLOCK CONTROL
*************************************************************************/
#define EMMC_SOURCE_CLK			CARD_SWITCHCLOCK_49MHZ
#define EMMC_SOURCE_CLK_HI		CARD_SWITCHCLOCK_49MHZ
#define EMMC_INIT_CLOCK_DIV		EMMC_CLOCK_DIV_128
#define EMMC_NORMAL_CLOCK_DIV	EMMC_CLOCK_DIV_NON

/************************************************************************
 * PRINT MESSAGE CONTROL
*************************************************************************/
//#define THIS_IS_FLASH_WRITE_U_ENV

#define EMMC_DRVNAME "emmc:"
#ifdef THIS_IS_FLASH_WRITE_U_ENV
	#include "sysdefs.h"
	#include "dvrboot_inc/util.h"
	#define UPRINTF(fmt, args...)			\
				if( rtprintf ) {			\
					rtprintf(fmt,## args);	\
				}
	#define EXT_CSD_CMD_SET_NORMAL		(1 << 0)
	#define EXT_CSD_CMD_SET_SECURE		(1 << 1)
	#define EXT_CSD_CMD_SET_CPSECURE	(1 << 2)
	#define EXT_CSD_CARD_TYPE_26		(1 << 0)
	#define EXT_CSD_CARD_TYPE_52		(1 << 1)
	#define EXT_CSD_BUS_WIDTH_1			0
	#define EXT_CSD_BUS_WIDTH_4			1
	#define EXT_CSD_BUS_WIDTH_8			2
#else
	#include <common.h>
	#include <command.h>
	#include <mmc.h>
	#include <part.h>
	#include <malloc.h>
	#include <asm/errno.h>
	#include <asm/io.h>
	#define UPRINTF(fmt, args...)			\
				printf(fmt,## args)
#endif

#ifdef EMMC_DEBUG
    #define mmcinfo(fmt, args...) \
               UPRINTF(EMMC_DRVNAME fmt,## args)
#else
    #define mmcinfo(fmt, args...)
#endif

#ifdef EMMC_DEBUG_SHOWCMD
	#define mmcinfo_cmd(fmt, args...) \
				UPRINTF(EMMC_DRVNAME fmt,## args)
#else
	#define mmcinfo_cmd(fmt, args...)
#endif

/************************************************************************
 * MMC BIT DATA READING
*************************************************************************/
#define UNSTUFF_BITS(resp,start,size)                   						\
    ({                              											\
        const int __size = size;                								\
        const unsigned short __mask = (unsigned short)(__size < 32 ? 1 << __size : 0) - 1; 		\
        const int __off = 3 - ((start) / 32);           						\
        const int __shft = (start) & 31;            							\
        unsigned short __res;                      								\
                                    											\
        __res = resp[__off] >> __shft;              							\
        if (__size + __shft > 32)               								\
            __res |= resp[__off-1] << ((32 - __shft) % 32); 					\
        __res & __mask;                     									\
    })

/************************************************************************
 * REALTEK CONTROL REGISTER ACCESSING METHOD
*************************************************************************/
#define cr_writel(value,addr)   	(*(volatile unsigned int *)(addr) = (value))
#define cr_writeb(value,addr)   	(*(volatile unsigned char *)(addr) = (value))
#define cr_readl(addr)          	REG32(addr)
#define cr_readb(addr)          	REG8(addr)

#define SWAP_32(x) \
    (((uint32_t)(x) << 24) | (((uint32_t)(x) & 0xff00) << 8) |(((uint32_t)(x) & 0x00ff0000) >> 8) | ((uint32_t)(x) >> 24))


#define __ARM_ARCH_8A__ 1
//1295 + armv7 implies armv8 aarch32 mode
#ifdef __ARM_ARCH_8A__
#define CP15ISB	asm volatile ("ISB SY" : : : "memory")
#define CP15DSB	asm volatile ("DSB SY" : : : "memory")
#define CP15DMB	asm volatile ("DMB SY" : : : "memory")
#else
#define CP15ISB	asm volatile ("mcr     p15, 0, %0, c7, c5, 4" : : "r" (0))
#define CP15DSB	asm volatile ("mcr     p15, 0, %0, c7, c10, 4" : : "r" (0))
#define CP15DMB	asm volatile ("mcr     p15, 0, %0, c7, c10, 5" : : "r" (0))
#endif


/************************************************************************
 *
*************************************************************************/

//1295 emmc error
#define CR_EMMC_EBE				0x8000
#define CR_EMMC_SBE				0x2000
#define CR_EMMC_HLE				0x1000
#define CR_EMMC_FRUN			0x0800
#define CR_EMMC_HTO				0x0400
#define CR_EMMC_DRTO			0x0200
#define CR_EMMC_RTO				0x0100
#define CR_EMMC_DCRC			0x0080
#define CR_EMMC_RCRC			0x0040
#define CR_EMMC_RE				0x0002


//error
#define CR_TRANSFER_FAIL            0x4
#define CR_TRANSFER_TO              0x1
#define CR_BUF_FULL_TO              0x2
#define CR_DMA_FAIL                 0x3

#define ERR_EMMC_SEND_STATUS_RETRY_FAIL 0x60
#define ERR_EMMC_SEND_RW_CMD_RETRY_FAIL 0x61
#define ERR_EMMC_CMD3_FAIL          0x63    /* mmc cmd3 fail present initial process fail */
#define ERR_EMMC_CMD7_FAIL          0x64    /* mmc cmd4 fail present initial process fail */
#define EMMC_MAX_CMD_SEND_RETRY_CNT 20
#define EMMC_MAX_STOP_CMD_RETRY_CNT 10
#define ERR_EMMC_SRAM_DMA_TIME      0x51

#define EMMC_VDD_1_8                0x80        /* VDD voltage 1.8         */
#define EMMC_VDD_30_31  			0x00040000  /* VDD voltage 3.0 ~ 3.1 */
#define EMMC_VDD_31_32  			0x00080000  /* VDD voltage 3.1 ~ 3.2 */
#define EMMC_VDD_32_33  			0x00100000  /* VDD voltage 3.2 ~ 3.3 */
#define EMMC_VDD_33_34  			0x00200000  /* VDD voltage 3.3 ~ 3.4 */
#define EMMC_VDD_34_35  			0x00400000  /* VDD voltage 3.4 ~ 3.5 */
#define EMMC_VDD_35_36  			0x00800000  /* VDD voltage 3.5 ~ 3.6 */
#define MMC_CARD_READY   			0x80000000  /* Card Power up status bit */
#define MMC_SECTOR_ADDR  			0x40000000

#define EMMC_VDD_REQ    			EMMC_VDD_35_36|EMMC_VDD_34_35|EMMC_VDD_33_34|EMMC_VDD_32_33|EMMC_VDD_31_32|EMMC_VDD_30_31

//0x18012080 , CPU_ACC
#define CPU_MODE_EN                 (0x00000001)
#define BUF_SW_RENEW                (0x00000001<<1)
#define BUF_FULL                    (0x00000001<<2)

/* MMC configure1, for SD_CONFIGURE1 */
#define SD30_FIFO_RST               (1<<4)
//#define SD1_R0                      (SDCLK_DIV | SDCLK_DIV_256 | RST_RDWR_FIFO)
#define SD1_R0                      (RST_RDWR_FIFO)

/* MMC configure3 , for SD_CONFIGURE3 */
#define SD30_CLK_STOP               (1<<4)
#define SD2_R0                      (RESP_TIMEOUT_EN | ADDR_BYTE_MODE)

#define RESP_TIMEOUT            	(0x00000001<<3)
#define RESP_TIMEOUT_EN         	(0x00000001)
#define ADDR_BYTE_MODE              (0x00000001<<1) //byte mode

#define SRAM_BASE_ADDR              0x80000000
#define SRAM_SIZE                   (32*1024)
#define IS_SRAM_ADDR(addr)          ((addr>=SRAM_BASE_ADDR)&&(addr<SRAM_BASE_ADDR+SRAM_SIZE))
/* MMC response type, for SD_CONFIGURE2 */
#define SD_R0                   	RESP_TYPE_NON|CRC7_CHK_DIS|WR_CRC_ERR_DIS
#define SD_R1                   	RESP_TYPE_6B
#define SD_R1b                  	RESP_TYPE_6B
#define SD_R2                   	RESP_TYPE_17B|CRC16_CAL_DIS
#define SD_R3                   	RESP_TYPE_6B
#define SD_R4                   	RESP_TYPE_6B
#define SD_R5                   	RESP_TYPE_6B

/* send status event */
#define STATE_IDLE      			0
#define STATE_READY     			1
#define STATE_IDENT     			2
#define STATE_STBY      			3
#define STATE_TRAN      			4
#define STATE_DATA      			5
#define STATE_RCV       			6
#define STATE_PRG       			7
#define STATE_DIS       			8
#define STATE_BTST      			9
#define STATE_SLP       			10

/* eMMC control register definition */
#define CR_BASE_ADDR             	0x98012000
#define PLL_EMMC1					0x980001f0
#define PLL_EMMC2					0x980001f4
#define PLL_EMMC3					0x980001f8
#define PLL_EMMC4					0x980001fc
#define SYS_NF_CKSEL				0x98000038



//1295 emmc register
#define CR_EMMC_CTRL 				( CR_BASE_ADDR)
#define CR_EMMC_PWREN 				( CR_BASE_ADDR + 0x004)
#define CR_EMMC_CLKDIV 				( CR_BASE_ADDR + 0x008)
#define CR_EMMC_CLKSRC 				( CR_BASE_ADDR + 0x00C)
#define CR_EMMC_CLKENA				( CR_BASE_ADDR + 0x010)
#define CR_EMMC_TMOUT				( CR_BASE_ADDR + 0x014)
#define CR_EMMC_CTYPE				( CR_BASE_ADDR + 0x018)
#define CR_EMMC_BLKSIZ				( CR_BASE_ADDR + 0x01C)
#define CR_EMMC_BYTCNT              ( CR_BASE_ADDR + 0x020)

#define CR_EMMC_INTMASK 			( CR_BASE_ADDR + 0x024)
#define CR_EMMC_CMDARG              ( CR_BASE_ADDR + 0x028)
#define CR_EMMC_CMD 				( CR_BASE_ADDR + 0x02C)
#define CR_EMMC_RESP0               ( CR_BASE_ADDR + 0x030)
#define CR_EMMC_RESP1               ( CR_BASE_ADDR + 0x034)
#define CR_EMMC_RESP2               ( CR_BASE_ADDR + 0x038)
#define CR_EMMC_RESP3               ( CR_BASE_ADDR + 0x03C)
#define CR_EMMC_MINTSTS             ( CR_BASE_ADDR + 0x040)


#define CR_EMMC_RINTSTS				( CR_BASE_ADDR + 0x044)
#define CR_EMMC_STATUS              ( CR_BASE_ADDR + 0x048)
#define CR_EMMC_FIFOTH				( CR_BASE_ADDR + 0x04C)


#define CR_EMMC_UHSREG				( CR_BASE_ADDR + 0x074)

#define CR_EMMC_BMOD				( CR_BASE_ADDR + 0x080)
#define CR_EMMC_DBADDR				( CR_BASE_ADDR + 0x088)
#define CR_EMMC_IDINTEN				( CR_BASE_ADDR + 0x090)
#define CR_EMMC_IDSTS               ( CR_BASE_ADDR + 0x08C)
#define CR_EMMC_CARD_THR_CTL        ( CR_BASE_ADDR + 0x100)
#define CR_EMMC_DDR_REG             ( CR_BASE_ADDR + 0x10c)

#define CR_EMMC_CP					( CR_BASE_ADDR + 0x41C)
#define CR_EMMC_ISR                 ( CR_BASE_ADDR + 0x424)
#define CR_EMMC_DUMMY_SYS           ( CR_BASE_ADDR + 0x42C)
#define CR_EMMC_PAD_CTL				( CR_BASE_ADDR + 0x474)
#define CR_EMMC_SWC_SEL				( CR_BASE_ADDR + 0x4D4)



#define CR_EMMC_DQS_CTRL1      					( CR_BASE_ADDR + 0x498 )
#define CR_EMMC_IP_DESC0						( CR_BASE_ADDR + 0x4a0)
#define CR_EMMC_IP_DESC1						( CR_BASE_ADDR + 0x4a4)
#define CR_EMMC_IP_DESC2						( CR_BASE_ADDR + 0x4a8)
#define CR_EMMC_IP_DESC3						( CR_BASE_ADDR + 0x4ac)
#define CR_EMMC_CKGEN_CTL                       ( CR_BASE_ADDR + 0x478 )


#define CR_EMMC_muxpad0                            (CR_BASE_ADDR + 0x600) //mux for nand and emmc
#define CR_EMMC_muxpad1                            (CR_BASE_ADDR + 0x604) //mux for sdio and sd card
#define CR_EMMC_PFUNC_CR                       	   (CR_BASE_ADDR + 0x610)
#define CR_EMMC_PFUNC_NF1			(CR_BASE_ADDR + 0x60c)
#define CR_EMMC_PDRIVE_NF0        ( CR_BASE_ADDR + 0x620 )
#define CR_EMMC_PDRIVE_NF1        ( CR_BASE_ADDR + 0x624 )
#define CR_EMMC_PDRIVE_NF2        ( CR_BASE_ADDR + 0x628 )
#define CR_EMMC_PDRIVE_NF3        ( CR_BASE_ADDR + 0x62c )
#define CR_EMMC_PDRIVE_NF4        ( CR_BASE_ADDR + 0x630 )

//98012048 : Status Register
#define STS_DATA_BUSY		(1<<9)
#define STS_DATA_3_STATUS	(1<<8)

//9801202c : command register
#define CMD_IDX_MASK(x)		(x & 0x3f)
#define CMD_IDX			(0x3f)
#define CMD_RSP_EXP		(1<<6)
#define CMD_RSP_LEN		(1<<7)
#define CMD_CHK_RESP_CRC	(1<<8)
#define CMD_DATA_EXP		(1<<9)
#define CMD_RD_WR		(1<<10)
#define CMD_TRANS_MODE		(1<<11)
#define CMD_SEND_AUTO_STOP	(1<<12)
#define CMD_USE_HOLD_REG	(1<<29)
#define CMD_START_CMD		(1<<31)

#define EMMC_CLOCK_DIV_NON      (0x00000000)
#define EMMC_CLOCK_DIV_2        (0x00000001)
#define EMMC_CLOCK_DIV_8        (0x00000004)
#define EMMC_CLOCK_DIV_128      (0x00000001<<6)
#define EMMC_CLOCK_DIV_256      (0x00000001<<7)


#define MASK_CLOCK_DIV          	(0x00000003<<6)

#define MASK_MODE_SELECT		(0x0c)
#define MODE_SD20			(0x01) //sdr20/50
#define MODE_DDR			(0x02) //ddr50
#define MODE_SD30			(0x03) //hs-200

#define SPEED_MOD_HIGH          	(0x00000001<<4)
#define SPEED_MOD_NORM          	(0x00000000)
#define DELAY_PHA_NORM          	(0x00000001<<3)
#define DELAY_PHA_HIGH          	(0x00000001<<2)

#define MASK_BUS_WIDTH          (0x00010001)
#define BUS_WIDTH_1             (0x00000000)
#define BUS_WIDTH_4             (0x00000001)
#define BUS_WIDTH_8             (0x00000002)
#define REG_BUS_WIDTH_1         (0x00000000)
#define REG_BUS_WIDTH_4         (0x00000001)
#define REG_BUS_WIDTH_8         (0x00010000)

#define EXT_CSD_DDR_BUS_WIDTH_4 	5       /* Card is in 4 bit DDR mode */
#define EXT_CSD_DDR_BUS_WIDTH_8 	6       /* Card is in 8 bit DDR mode */

/* SD_TRANSFER 0xb8010808 */
#define START_EN                	(0x00000001<<7)
#define END_STATE               	(0x00000001<<6)
#define IDLE_STATE               	(0x00000001<<5)
#define ERR_STATUS              	(0x00000001<<4)

#define MASK_CMD_CODE           	(0x0000000F)
#define SD_NORMALWRITE          	(0x00000000)
#define SD_AUTOWRITE3           	(0x00000001)
#define SD_AUTOWRITE4           	(0x00000002)
#define SD_AUTOREAD3            	(0x00000005)
#define SD_AUTOREAD4            	(0x00000006)
#define SD_SENDCMDGETRSP        	(0x00000008)
#define SD_AUTOWRITE1           	(0x00000009)
#define SD_AUTOWRITE2           	(0x0000000A)
#define SD_NORMALREAD           	(0x0000000C)
#define SD_AUTOREAD1            	(0x0000000D)
#define SD_AUTOREAD2            	(0x0000000E)
#define SD_TUNING			(0x0000000F)

/* SD_CONFIGURE2 0x18012180 */
#define SDCLK_DIV                   (0x00000001<<7)
#define SDCLK_NO_DIV                (0x00000000)
#define SDCLK_DIV_128               (0x00000000)
#define SDCLK_DIV_256               (0x00000001<<6)
#define NO_RST_RDWR_FIFO            (0x00000000)
#define RST_RDWR_FIFO               (0x00000001<<4)
#define BUS_WIDTH_1bit              (0x00000000)
#define BUS_WIDTH_4bit              (0x00000001)
#define BUS_WIDTH_8bit              (0x00000002)

#define BOOTDEVTYPE_SDR		    (0x1)
#define BOOTDEVTYPE_DDR		    (0x2)
#define BOOTDEVTYPE_HS200	    (0x4)

/* SD_CONFIGURE2 0x18012181 */
#define CRC7_CAL_DIS            	(0x00000001<<7)
#define CRC16_CAL_DIS           	(0x00000001<<6)
#define WAIT_BUSY_EN            	(0x00000001<<3)
#define CRC7_CHK_DIS            	(0x00000001<<2)
#define WR_CRC_ERR_DIS              (0x00000005<<4)

#define MASK_RESP_TYPE          	(0x00000003)
#define RESP_TYPE_NON           	(0x00000000)
#define RESP_TYPE_6B            	(0x00000001)
#define RESP_TYPE_17B           	(0x00000002)

/* SD_CONFIGURE3 0x18012182 */
#define RESP_TIMEOUT            	(0x00000001<<3)
#define SDCMD_RSP_CHK_EN         	(0x00000001<<2)
//#define RESP_TIMEOUT_EN         	(0x00000001<<0)
#define ADDR_BYTE_MODE              (0x00000001<<1)
//#define IGNORE_WRT_ERR          	(0x00000001<<1)
//#define CLK_TOGGLE_EN           	(0x00000001<<0)

/* DMA_CTL3 0x1801200c */
#define DMA_XFER                    (0x00000001)
#define DDR_WR                      (0x00000002)
#define RSP17_SEL                   (0x00000001 << 4)
#define DAT64_SEL                   (0x00000001 << 5)

/* SD_INT_STATUS 0xb8010848 */
#define RTKCR_INT_WRT_PROTEC    	(1<<5)
#define RTKCR_INT_CARD_DETEC    	(1<<4)
#define RTKCR_INT_DECODE_ERROR  	(1<<2)
#define RTKCR_INT_DECODE_FINISH 	(1<<1)
#define RTKCR_INT_STATUS_CHANGE 	(1<<0)
#define RTKCR_INT_CLEAR_ALL     	(RTKCR_INT_DECODE_ERROR|RTKCR_INT_DECODE_FINISH|RTKCR_INT_STATUS_CHANGE)

/* SD_STATUS1 0x18012183 */
#define CRC7_STATUS             	(0x00000001<<7)
#define CRC16_STATUS            	(0x00000001<<6)
#define WRT_ERR_BIT             	(0x00000001<<5)
#define WRT_CRC_TO_ERR             	(0x00000001<<1)
#define MASK_WRT_ERR_STA        	(0x00000007<<2)

/* SD_STATUS2 0x18012184 */
#define RSP_TIMEOUT			(0x00000001)

/* CP_CTRL 0xb8010884 */
#define BOOT_FROM_CR            	(0x00000001<<3)
#define MASK_BUFF_TIMING        	(0x00000003<<1)
#define BUFF_TIMING_0           	(0x00000000<<1)
#define BUFF_TIMING_1           	(0x00000001<<1)
#define BUFF_TIMING_2           	(0x00000002<<1)
#define BUFF_TIMING_3           	(0x00000003<<1)
#define CP_EN                   	(0x00000001)

//CRT spec(RTD299X DesignSpec-CRT)
#define SYS_CLKSEL              	0xB8000204        //0xB8000204
#define EMMC_CLKSEL_MASK        	(0x07<<12)
#define CLOCK_SPEED_GAP         	(0x03<<12)

#define CARD_SWITCHCLOCK_60MHZ  	(0x00<<12)
#define CARD_SWITCHCLOCK_80MHZ  	(0x01<<12)
#define CARD_SWITCHCLOCK_98MHZ  	(0x02<<12)
#define CARD_SWITCHCLOCK_98MHZS 	(0x03<<12)
#define CARD_SWITCHCLOCK_30MHZ  	(0x04<<12)
#define CARD_SWITCHCLOCK_40MHZ  	(0x05<<12)
#define CARD_SWITCHCLOCK_49MHZ  	(0x06<<12)
#define CARD_SWITCHCLOCK_49MHZS 	(0x07<<12)

/* Standard MMC commands (4.1)              type    argument            response */
/* class 1 */
#define MMC_GO_IDLE_STATE           0       /* bc                           */
#define MMC_SEND_OP_COND            1       /* bcr  [31:0] OCR          R3  */
#define MMC_ALL_SEND_CID            2       /* bcr                      R2  */
#define MMC_SET_RELATIVE_ADDR       3       /* ac   [31:16] RCA         R1  */
#define MMC_SET_DSR                 4       /* bc   [31:16] RCA             */
#define MMC_SLEEP_AWAKE             5       /* ac   [31:16] RCA 15:flg  R1b */
#define MMC_SWITCH                  6       /* ac   [31:0] See below    R1b */
#define MMC_SELECT_CARD             7       /* ac   [31:16] RCA         R1  */
#define MMC_SEND_EXT_CSD            8       /* adtc                     R1  */
#define MMC_SEND_CSD                9       /* ac   [31:16] RCA         R2  */
#define MMC_SEND_CID                10      /* ac   [31:16] RCA         R2  */
#define MMC_READ_DAT_UNTIL_STOP     11      /* adtc [31:0] dadr         R1  */
#define MMC_STOP_TRANSMISSION       12      /* ac                       R1b */
#define MMC_SEND_STATUS             13      /* ac   [31:16] RCA         R1  */
#define MMC_GO_INACTIVE_STATE       15      /* ac   [31:16] RCA             */
#define MMC_SPI_READ_OCR            58      /* spi                      spi_R3 */
#define MMC_SPI_CRC_ON_OFF          59      /* spi  [0:0] flag          spi_R1 */

  /* class 2 */
#define MMC_SET_BLOCKLEN            16      /* ac   [31:0] block len    R1  */
#define MMC_READ_SINGLE_BLOCK       17      /* adtc [31:0] data addr    R1  */
#define MMC_READ_MULTIPLE_BLOCK     18      /* adtc [31:0] data addr    R1  */

  /* class 3 */
#define MMC_WRITE_DAT_UNTIL_STOP    20      /* adtc [31:0] data addr    R1  */
#define MMC_TUNING		    21      /* adtc [31:0] data addr    R1  */

  /* class 4 */
#define MMC_SET_BLOCK_COUNT         23      /* adtc [31:0] data addr    R1  */
#define MMC_WRITE_BLOCK             24      /* adtc [31:0] data addr    R1  */
#define MMC_WRITE_MULTIPLE_BLOCK    25      /* adtc                     R1  */
#define MMC_PROGRAM_CID             26      /* adtc                     R1  */
#define MMC_PROGRAM_CSD             27      /* adtc                     R1  */

  /* class 6 */
#define MMC_SET_WRITE_PROT          28      /* ac   [31:0] data addr    R1b */
#define MMC_CLR_WRITE_PROT          29      /* ac   [31:0] data addr    R1b */
#define MMC_SEND_WRITE_PROT         30      /* adtc [31:0] wpdata addr  R1  */
#define MMC_SEND_WRITE_PROT_TYPE    31      /* adtc [31:0] wpdata addr  R1  */

  /* class 5 */
#define MMC_ERASE_GROUP_START       35      /* ac   [31:0] data addr    R1  */
#define MMC_ERASE_GROUP_END         36      /* ac   [31:0] data addr    R1  */
#define MMC_ERASE                   38      /* ac                       R1b */

  /* class 9 */
#define MMC_FAST_IO                 39      /* ac   <Complex>           R4  */
#define MMC_GO_IRQ_STATE            40      /* bcr                      R5  */

  /* class 7 */
#define MMC_LOCK_UNLOCK             42      /* adtc                     R1b */

  /* class 8 */
#define MMC_APP_CMD                 55      /* ac   [31:16] RCA         R1  */
#define MMC_GEN_CMD                 56      /* adtc [0] RD/WR           R1  */

#define R1_OUT_OF_RANGE         	(1 << 31)   /* er, c */
#define R1_ADDRESS_ERROR        	(1 << 30)   /* erx, c */
#define R1_BLOCK_LEN_ERROR      	(1 << 29)   /* er, c */
#define R1_ERASE_SEQ_ERROR      	(1 << 28)   /* er, c */
#define R1_ERASE_PARAM          	(1 << 27)   /* ex, c */
#define R1_WP_VIOLATION         	(1 << 26)   /* erx, c */
#define R1_CARD_IS_LOCKED       	(1 << 25)   /* sx, a */
#define R1_LOCK_UNLOCK_FAILED   	(1 << 24)   /* erx, c */
#define R1_COM_CRC_ERROR        	(1 << 23)   /* er, b */
#define R1_ILLEGAL_COMMAND      	(1 << 22)   /* er, b */
#define R1_CARD_ECC_FAILED      	(1 << 21)   /* ex, c */
#define R1_CC_ERROR             	(1 << 20)   /* erx, c */
#define R1_ERROR                	(1 << 19)   /* erx, c */
#define R1_UNDERRUN             	(1 << 18)   /* ex, c */
#define R1_OVERRUN              	(1 << 17)   /* ex, c */
#define R1_CID_CSD_OVERWRITE    	(1 << 16)   /* erx, c, CID/CSD overwrite */
#define R1_WP_ERASE_SKIP        	(1 << 15)   /* sx, c */
#define R1_CARD_ECC_DISABLED    	(1 << 14)   /* sx, a */
#define R1_ERASE_RESET          	(1 << 13)   /* sr, c */
#define R1_STATUS(x)            	(x & 0xFFFFE000)
#define R1_CURRENT_STATE(x)     	((x & 0x00001E00) >> 9) /* sx, b (4 bits) */
#define R1_READY_FOR_DATA       	(1 << 0)    /* sx, a */
#define R1_SWITCH_ERROR         	(1 << 7)    /* sx, c */
#define R1_APP_CMD              	(1 << 5)    /* sr, c */

#define R1_ERR_CUR_WINDOW       	R1_OUT_OF_RANGE         |\
                                	R1_ADDRESS_ERROR        |\
                                	R1_BLOCK_LEN_ERROR      |\
                                	R1_ERASE_SEQ_ERROR      |\
                                	R1_ERASE_PARAM          |\
                                	R1_WP_VIOLATION         |\
                                	R1_LOCK_UNLOCK_FAILED   |\
                                	R1_COM_CRC_ERROR        |\
                                	R1_ILLEGAL_COMMAND      |\
                                	R1_CARD_ECC_FAILED      |\
                                	R1_CC_ERROR             |\
                                	R1_ERROR                |\
                                	R1_UNDERRUN             |\
                                	R1_OVERRUN              |\
                                	R1_CID_CSD_OVERWRITE    |\
                                	R1_WP_ERASE_SKIP        |\
                                	R1_ERASE_RESET


#define R1_ERR_PER_WINDOW      		R1_OUT_OF_RANGE         |\
                               		R1_ADDRESS_ERROR        |\
                               		R1_ERASE_PARAM          |\
                               		R1_WP_VIOLATION         |\
                               		R1_LOCK_UNLOCK_FAILED   |\
                               		R1_CARD_ECC_FAILED      |\
                               		R1_ERROR                |\
                               		R1_UNDERRUN             |\
                               		R1_OVERRUN              |\
                               		R1_CID_CSD_OVERWRITE    |\
                               		R1_WP_ERASE_SKIP


/*
 * EXT_CSD fields
 */
#define EXT_CSD_BUS_WIDTH       	183     /* R/W */
#define EXT_CSD_HS_TIMING       	185     /* R/W */
#define EXT_CSD_CARD_TYPE       	196     /* RO */
#define EXT_CONT_CSD_VER        	194     /* RO */
#define EXT_CSD_REV             	192     /* RO */
#define EXT_CSD_SEC_CNT         	212     /* RO, 4 bytes */
#define EXT_CSD_S_A_TIMEOUT     	217

/*
 * MMC_SWITCH access modes
 */
#define MMC_SWITCH_MODE_CMD_SET     0x00    /* Change the command set */
#define MMC_SWITCH_MODE_SET_BITS    0x01    /* Set bits which are 1 in value */
#define MMC_SWITCH_MODE_CLEAR_BITS  0x02    /* Clear bits which are 1 in value */
#define MMC_SWITCH_MODE_WRITE_BYTE  0x03    /* Set target to value */


/*
 * CHIP REV. Judgment
 */
#define KYLIN_REV_A00   0x0000
#define KYLIN_REV_A01   0x0001
#define KYLIN_REV_B00   0x0002



#define CSD_ARRAY_SIZE 512
#define CHANGE_FREQ_CARD 0x1
#define CHANGE_FREQ_HOST 0x2
#define CHANGE_FREQ_TYPE 0x3

//MMC ios caps
#define MMC_IOS_LDO		0x1
#define MMC_IOS_CLK		0x2
#define MMC_IOS_BUSWIDTH	0x4
#define MMC_IOS_INIT_DIV	0x10
#define MMC_IOS_NONE_DIV	0x20
#define MMC_IOS_GET_PAD_DRV 	0x40
#define MMC_IOS_SET_PAD_DRV 	0x80
#define MMC_IOS_RESTORE_PAD_DRV	0x100

//#define MMC_IOS_GET_PAD_DRV     0x1
//#define MMC_IOS_SET_PAD_DRV     0x2
//#define MMC_IOS_RESTORE_PAD_DRV 0x4

/*register operation*/
#define PTR_U32(_p)   ((unsigned int)(unsigned long)(_p))
#define U64_PTR(_v)   ((void *)(unsigned long)(_v))
#define SYS_PLL_EMMC1    0x980001F0
#define SYS_PLL_EMMC3    0x980001F8
#define PHOENIX_REV_B   0x0001
#define GET_CHIP_REV() (REG32(SB2_CHIP_INFO)>>16)

/************************************************************************
 *  Structure
 ************************************************************************/
struct rtk_mmc_command {
    unsigned int opcode;
    unsigned int arg;
    unsigned int resp[4];
};


struct rtk_cmd_info {
    struct mmc_cmd  * 			cmd;
	struct mmc_data *			data;
	unsigned char *         	dma_buffer;
    unsigned int      		 	byte_count;
    unsigned int      		 	block_count;
    unsigned int      		 	xfer_flag;
	#define RTK_MMC_DATA_DIR_MASK   (3 << 6)    /* bit 6~7 */
	#define RTK_MMC_DATA_SRAM       (1 << 7)
	#define RTK_MMC_DATA_WRITE      (1 << 6)
	#define RTK_MMC_TUNING         (1 << 5)
	#define RTK_MMC_DATA_READ       (0 << 6)    /* can't use this flag to check status, because its value is zero */
	#define RTK_MMC_SRAM_WRITE      RTK_MMC_DATA_SRAM | RTK_MMC_DATA_WRITE
	#define RTK_MMC_SRAM_READ       RTK_MMC_DATA_SRAM | RTK_MMC_DATA_READ
	#define RTK_MMC_DATA_DIR(pkt)  (pkt->xfer_flag & RTK_MMC_DATA_DIR_MASK)
    unsigned int			cmd_para;
    unsigned int     		rsp_len;
    
};

/*
 * emmc profile
 */

struct rtk_mmc_ocr_reg {
    unsigned char lowV:1;   //1.7v to 1.95v
    unsigned char reserved1:7;
    unsigned char val1;
    unsigned char val2;
    unsigned char reserved2:5;
    unsigned char access_mode:2;
    unsigned char power_up:1;
};
struct rtk_mmc_ocr {
    unsigned char check1:6;
    unsigned char start:1;
    unsigned char transmission:1;
    unsigned char reg[4];
    unsigned char end:1;
    unsigned char check2:7;
};



struct rtk_mmc_cid {
	unsigned int					manfid;
	char			    			prod_name[8];
	unsigned int					serial;
	unsigned int					oemid;
	unsigned int					year;
	unsigned char					hwrev;
	unsigned char					fwrev;
	unsigned char					month;
};

struct rtk_mmc_csd {
	unsigned char					csd_ver;
	unsigned char					csd_ver2;// from EXT_CSD
	unsigned char					mmca_vsn;
	unsigned short					cmdclass;
	unsigned short					tacc_clks;
	unsigned int					tacc_ns;
	unsigned int					r2w_factor;
	unsigned int					max_dtr;
	unsigned int					read_blkbits;
	unsigned int					write_blkbits;
	unsigned int					capacity;
	unsigned int					read_partial:1,
				        			read_misalign:1,
				        			write_partial:1,
				        			write_misalign:1;
};

struct rtk_mmc_ext_csd {
	unsigned int 					rev;
	unsigned char					part_cfg;
	unsigned char					boot_cfg;
	unsigned char					boot_wp_sts;
	unsigned char					boot_wp;
	unsigned char					user_wp;
	unsigned char					rpmb_size_mult;
	unsigned char					partitioning_support;
	unsigned int 					boot_blk_size;
	unsigned int 					sa_timeout;
	unsigned int 					hs_max_dtr;
	unsigned int 					sectors;
};

typedef struct {
	unsigned int					sector_addressing;
	unsigned int 					curr_part_indx;
	unsigned int					rca;		    		/* relative card address of device */
	unsigned int					raw_cid[4];	            /* raw card CID */
	unsigned int					raw_csd[4];	            /* raw card CSD */
	struct rtk_mmc_ocr	    		ocr;					/* card identification */
	struct rtk_mmc_cid	    		cid;					/* card identification */
	struct rtk_mmc_csd	    		csd;					/* card specific */
	struct rtk_mmc_ext_csd  		ext_csd;				/* mmc v4 extended card specific */
} e_device_type;

struct backupRegs {
    u32                 emmc_mux_pad0;
    u32                 emmc_mux_pad1;
    u32                 emmc_pfunc_nf1;
    u32                 emmc_pdrive_nf1;
    u32                 emmc_pdrive_nf2;
    u32                 emmc_pdrive_nf3;
    u32                 emmc_ctype;
    u32                 emmc_uhsreg;
    u32                 emmc_ddr_reg;
    u32                 emmc_card_thr_ctl;
    u32                 emmc_clk_div;
    u32                 emmc_ckgen_ctl;
    u32                 emmc_dqs_ctrl1;
	unsigned int		emmc_pfunc_cr;
};

#ifdef __RTKEMMC_C__
	#define EXTERN_CALL
#else
	#define EXTERN_CALL extern
#endif

int rtkemmc_data_sync( struct mmc * mmc );

int rtkemmc_request(
			struct mmc * mmc,
			struct mmc_cmd * cmd,
			struct mmc_data * data );

void rtkemmc_init_setup( void );
void rtkemmc_set_ios(struct mmc * mmc, unsigned int ios_caps);


EXTERN_CALL void rtkemmc_set_bits( unsigned int set_bit );
EXTERN_CALL int rtk_eMMC_init( void );
EXTERN_CALL int rtk_eMMC_write( unsigned int blk_addr, unsigned int data_size, unsigned int * buffer );
EXTERN_CALL int rtk_eMMC_read( unsigned int blk_addr, unsigned int data_size, unsigned int * buffer );
//EXTERN_CALL int rtkemmc_change_to_DDR50();
EXTERN_CALL int rtkemmc_Stream_Cmd(struct rtk_cmd_info * cmd_info, unsigned int bIgnore);
void rtkemmc_set_wrapper_div( unsigned int level );
int mmc_initial( int reset_only );
int error_handling(unsigned int cmd_idx, unsigned int bIgnore);
int rtk_emmc_init(void);
void frequency(unsigned int  fre, unsigned int  div);
int emmc_send_cmd_get_rsp(unsigned int cmd_idx, unsigned int sd_arg, unsigned int rsp_con, unsigned int crc);
void switch_speed(UINT8 speed);
int switch_erase_group_def(unsigned int enable);
int emmc_read_write_ip(UINT32 cmd_idx, UINT32 blk_addr, unsigned char *dma_addr, UINT32 dma_length);
int cmd23_request(struct mmc *mmc, struct mmc_cmd *cmd, struct mmc_data *data);
int cmd25_request(struct mmc * mmc,	struct mmc_cmd * cmd,struct mmc_data * data );
int cmd18_request(struct mmc * mmc,	struct mmc_cmd * cmd,struct mmc_data * data );
UINT32 check_error(int bIgnore);
int mmc_Tuning_HS200(void);
void mmc_show_ext_csd( unsigned char * pext_csd );
void mmc_show_csd( struct mmc* card );
int mmc_decode_cid( struct mmc * rcard );
extern  unsigned int  emmc_cid[4];

#endif /* end of file */
