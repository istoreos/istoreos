/******************************************************************************
 * include/linux/mtd/rtk_nand.h
 * Overview: Realtek Nand Flash HW Controller Register Map
 * Copyright (c) 2008 Realtek Semiconductor Corp. All Rights Reserved.
 * Modification History:
 *    #000 2010-07-02  AlexChang   create file
 * 
 *******************************************************************************/
#ifndef __RTK_NAND_H
#define __RTK_NAND_H

//#include <linux/config.h>
//#include <linux/sched.h>
#include <linux/mtd/mtd.h>
#include <asm-generic/errno.h>
//#include <asm/r4kcache.h>

#define DBG_SHOW_MSG_ENABLE		(0)		//define if show debug message;
#define DBG_MODE_ENABLE			(0)   	//Enable debug mode or not;
#define TEST_NF_DRIVER			(0)   	//Enable test procedure for NAND flash driver 
#define RTK_NAND_TEST (0) 		//+alexchang add 0702-2010
#define RTK_ARD_ALGORITHM (0)	//Enable Avoid Read Disturbance Algorithm or not
#define RTK_CP_DISABLE	(0)		//Enable content protection for NAND driver or not

#define ERESTARTSYS	(512)

//static spinlock_t	 lock_NF_CARDREADER;

/* 
define mars read/write NAND HW registers
use them because standard readb/writeb have warning msgs in our gcc 2.96
ex: passing arg 2 of `writeb' makes pointer from integer without a cast
*/
#define REG_READ_U8(register)         		(*(volatile unsigned char *)(register))
#define REG_READ_U16(register)         		(*(volatile unsigned short *)(register))
//#define REG_READ_U32(register)         		(*(volatile unsigned long *)(register))
#define REG_READ_U32(register)         		(readl((volatile const unsigned int*)(uintptr_t)(register)))

#define REG_WRITE_U8(register, value)    		(*(volatile unsigned char *)(register) = value)
#define REG_WRITE_U16(register, value)    		(*(volatile unsigned short *)(register) = value)
//#define REG_WRITE_U32(register, value)    		(*(volatile unsigned long *)(register) = value)
#define REG_WRITE_U32(register, value)    		(writel(value,(volatile unsigned int*)(uintptr_t)(register)))

#define MTDSIZE	(sizeof (struct mtd_info) + sizeof (struct nand_chip))
#define MAX_PARTITIONS	16
#define BOOTCODE	16*1024*1024	//16MB
//#define GFP_KERNEL			0

//1295 + armv7 implies armv8 aarch32 mode
//#ifdef __ARM_ARCH_8A__
#if 1
#define CP15ISB	asm volatile ("ISB SY" : : : "memory")
#define CP15DSB	asm volatile ("DSB SY" : : : "memory")
#define CP15DMB	asm volatile ("DMB SY" : : : "memory")
#else
#define CP15ISB	asm volatile ("mcr     p15, 0, %0, c7, c5, 4" : : "r" (0))
#define CP15DSB	asm volatile ("mcr     p15, 0, %0, c7, c10, 4" : : "r" (0))
#define CP15DMB	asm volatile ("mcr     p15, 0, %0, c7, c10, 5" : : "r" (0))
#endif

/*
 * Searches for a NAND device
 */
extern int rtk_nand_scan (struct mtd_info *mtd, int maxchips);


//========================================================================

/* Reserve Block Area usage */
#define	BB_INIT	0xFFFE
#define	RB_INIT	0xFFFD
#define	BBT_TAG	0xBB
#define TAG_FACTORY_PARAM	(0x82)
#define BB_DIE_INIT	0xEEEE
#define RB_DIE_INIT	BB_DIE_INIT
typedef struct /*__attribute__ ((__packed__))*/{
    u16 BB_die;
    u16 bad_block;
    u16 RB_die;
    u16 remap_block;
}BB_t;
typedef struct /*__attribute__ ((__packed__))*/{
    const char  *name;
    unsigned int id;
    uint64_t 	 size;	//nand total size
    uint64_t	 chipsize;	//die size
    unsigned int PageSize;
    unsigned int BlockSize;
    unsigned short OobSize;
    unsigned char num_chips;
    unsigned char isLastPage;	//page position of block to check BB
    unsigned char CycleID5th; //If CycleID5th do not exist, set it to 0xff
    unsigned char CycleID6th; //If CycleID6th do not exist, set it to 0xff
    unsigned short ecc_num;
    unsigned char T1;
    unsigned char T2;
    unsigned char T3;
	unsigned short eccSelect;//Ecc ability select:   add by alexchang 0319-2010 
} device_type_t;

/* NAND Flash Command Sets */
#define CMD_READ_ID				0x90
#define CMD_READ_STATUS		0x70

#define CMD_PG_READ_C1		0x00
#define CMD_PG_READ_C2		0x30
#define CMD_PG_READ_C3		CMD_READ_STATUS

#define CMD_PG_WRITE_C1		0x80
#define CMD_PG_WRITE_C2		0x10
#define CMD_PG_WRITE_C3		CMD_READ_STATUS

#define CMD_BLK_ERASE_C1		0x60	//Auto Block Erase Setup command
#define CMD_BLK_ERASE_C2		0xd0	//CMD_ERASE_START
#define CMD_BLK_ERASE_C3		CMD_READ_STATUS	//CMD_STATUS_READ

#define CMD_RESET                 0xff
#define CMD_RANDOM_DATA_INPUT     0x85    /* RANDOM DATA write */ 

#define CMD_RANDOM_DATA_OUTPUT_C1 0x05    /* RANDOM DATA read */
#define CMD_RANDOM_DATA_OUTPUT_C2 0xe0 

#define NAND_ISR_XFER_MODE_DONE	(1 << 2)
#define NAND_ISR_AUTO_MODE_DONE	(1 << 3)
#define NAND_ISR_DMA_DONE	(1 << 4)
#define NAND_ISR_PFS_DONE	(1 << 7)	//polling flash status busy = 1

#define MCP_NONE	0
#define MCP_AES_ECB	1
#define MCP_AES_CBC	2
#define MCP_AES_CTR	3
//========================================================================
/* The maximum number of NAND chips in an array */
#define NAND_MAX_CHIPS		8
struct NAND_Info_st {
	unsigned int U32NFDrvVer;//The version number of NF Driver
	unsigned int U32ReadIDBytes;//Determine bytes for readID command need.
	
	unsigned int U32BlkCnt;// Number of blocks
	unsigned int U32PageSize;//Page size
	unsigned int U32PagePerBlk;//page count per block

	unsigned int U32BlkCntShift;
	unsigned int U32PageSizeShift;
	unsigned int U32PagePerBlkShift;
};


/*
	macro RTK_FLUSH_CACHE is to flush the cache at address "addr", 
	the length is "len"
*/
#if 0
#define RTK_FLUSH_CACHE(addr, len)		\
do {								\
	unsigned long dc_lsize = current_cpu_data.dcache.linesz;	\
	unsigned long end, a;								\
	a = (unsigned long ) addr & ~(dc_lsize - 1);		\
	end = ((unsigned long )addr + len - 1) & ~(dc_lsize - 1);	\
	while (1) {		\
		flush_dcache_line(a);   /* Hit_Writeback_Inv_D */	\
		if (a == end)	\
			break;	\
		a += dc_lsize;	\
	}	\
} while (0)
#else
#define RTK_FLUSH_CACHE(addr, len) flush_cache((unsigned long)addr, len)
#endif

//===================================================================
/*
 * nand_state_t - chip states
 * Enumeration for NAND flash chip state
 */

typedef enum {
	RTK_FL_READY,
	RTK_FL_READING,
	RTK_FL_WRITING,
	RTK_FL_ERASING,
	RTK_FL_SYNCING,
	RTK_FL_CACHEDPRG,
} nand_state_t;

//=============================================================================


//=============================================================================

/**
 * struct nand_hw_control - Control structure for hardware controller (e.g ECC generator) shared among independend devices
 * @lock:               protection lock  
 * @active:		the mtd device which holds the controller currently
 * @wq:			wait queue to sleep on if a NAND operation is in progress
 *                      used instead of the per chip wait queue when a hw controller is available
 */
struct nand_hw_control {
	//spinlock_t	 lock;
	struct nand_chip *active;
	//wait_queue_head_t wq;
};
//=============================================================================


/**
 * struct nand_chip - NAND Private Flash Chip Data
 * @IO_ADDR_R:		[BOARDSPECIFIC] address to read the 8 I/O lines of the flash device 
 * @IO_ADDR_W:		[BOARDSPECIFIC] address to write the 8 I/O lines of the flash device 
 * @read_byte:		[REPLACEABLE] read one byte from the chip
 * @write_byte:		[REPLACEABLE] write one byte to the chip
 * @read_word:		[REPLACEABLE] read one word from the chip
 * @write_word:		[REPLACEABLE] write one word to the chip
 * @write_buf:		[REPLACEABLE] write data from the buffer to the chip
 * @read_buf:		[REPLACEABLE] read data from the chip into the buffer
 * @verify_buf:		[REPLACEABLE] verify buffer contents against the chip data
 * @select_chip:	[REPLACEABLE] select chip nr
 * @block_bad:		[REPLACEABLE] check, if the block is bad
 * @block_markbad:	[REPLACEABLE] mark the block bad
 * @hwcontrol:		[BOARDSPECIFIC] hardwarespecific function for accesing control-lines
 * @dev_ready:		[BOARDSPECIFIC] hardwarespecific function for accesing device ready/busy line
 *			If set to NULL no access to ready/busy is available and the ready/busy information
 *			is read from the chip status register
 * @cmdfunc:		[REPLACEABLE] hardwarespecific function for writing commands to the chip
 * @waitfunc:		[REPLACEABLE] hardwarespecific function for wait on ready
 * @calculate_ecc: 	[REPLACEABLE] function for ecc calculation or readback from ecc hardware
 * @correct_data:	[REPLACEABLE] function for ecc correction, matching to ecc generator (sw/hw)
 * @enable_hwecc:	[BOARDSPECIFIC] function to enable (reset) hardware ecc generator. Must only
 *			be provided if a hardware ECC is available
 * @erase_cmd:		[INTERN] erase command write function, selectable due to AND support
 * @scan_bbt:		[REPLACEABLE] function to scan bad block table
 * @eccmode:		[BOARDSPECIFIC] mode of ecc, see defines 
 * @eccsize: 		[INTERN] databytes used per ecc-calculation
 * @eccbytes: 		[INTERN] number of ecc bytes per ecc-calculation step
 * @eccsteps:		[INTERN] number of ecc calculation steps per page
 * @chip_delay:		[BOARDSPECIFIC] chip dependent delay for transfering data from array to read regs (tR)
 * @chip_lock:		[INTERN] spinlock used to protect access to this structure and the chip
 * @wq:			[INTERN] wait queue to sleep on if a NAND operation is in progress
 * @state: 		[INTERN] the current state of the NAND device
 * @page_shift:		[INTERN] number of address bits in a page (column address bits)
 * @phys_erase_shift:	[INTERN] number of address bits in a physical eraseblock
 * @bbt_erase_shift:	[INTERN] number of address bits in a bbt entry
 * @chip_shift:		[INTERN] number of address bits in one chip
 * @data_buf:		[INTERN] internal buffer for one page + oob 
 * @oob_buf:		[INTERN] oob buffer for one eraseblock
 * @oobdirty:		[INTERN] indicates that oob_buf must be reinitialized
 * @data_poi:		[INTERN] pointer to a data buffer
 * @options:		[BOARDSPECIFIC] various chip options. They can partly be set to inform nand_scan about
 *			special functionality. See the defines for further explanation
 * @badblockpos:	[INTERN] position of the bad block marker in the oob area
 * @numchips:		[INTERN] number of physical chips
 * @chipsize:		[INTERN] the size of one chip for multichip arrays
 * @pagemask:		[INTERN] page number mask = number of (pages / chip) - 1
 * @pagebuf:		[INTERN] holds the pagenumber which is currently in data_buf
 * @autooob:		[REPLACEABLE] the default (auto)placement scheme
 * @bbt:		[INTERN] bad block table pointer
 * @bbt_td:		[REPLACEABLE] bad block table descriptor for flash lookup
 * @bbt_md:		[REPLACEABLE] bad block table mirror descriptor
 * @badblock_pattern:	[REPLACEABLE] bad block scan pattern used for initial bad block scan 
 * @controller:		[OPTIONAL] a pointer to a hardware controller structure which is shared among multiple independend devices
 * @priv:		[OPTIONAL] pointer to private chip date
 * @errstat:		[OPTIONAL] hardware specific function to perform additional error status checks 
 *			(determine if errors are correctable)
 */
 
struct nand_chip {
	u_char oob_shift;
	void (*read_id) (struct mtd_info *mtd, unsigned char id[5]);
	int (*read_ecc_page) (struct mtd_info *mtd, u16 chipnr, unsigned int page, u_char *data, 
		struct mtd_oob_ops *ops, u16 cp_mode, u16 cp_first, size_t cp_len);
	int (*read_oob) (struct mtd_info *mtd, u16 chipnr, int page, int len, u_char *buf);
	int (*write_ecc_page) (struct mtd_info *mtd, u16 chipnr, unsigned int page, const u_char *data,
		struct mtd_oob_ops *ops, int isBBT);
	int (*write_oob) (struct mtd_info *mtd, u16 chipnr, int page, int len, const u_char *buf);
	int (*erase_block) (struct mtd_info *mtd, u16 chipnr, int page);
	void (*sync) (struct mtd_info *mtd);

	void (*suspend) (struct mtd_info *mtd);
	void (*resume) (struct mtd_info *mtd);

	void (*select_chip) (struct mtd_info *mtd, int chip);
	void	(*read_buf)(struct mtd_info *mtd, u_char *buf, int len);
	void 	(*cmdfunc)(struct mtd_info *mtd, unsigned command, int column, int page_addr);
	int  (*dev_ready)(struct mtd_info *mtd);
	int (*scan_bbt)(struct mtd_info *mtd);
	int		eccmode;
	int		eccsize;
	int		eccbytes;
	int		eccsteps;
	int 		chip_delay;
	//spinlock_t	chip_lock;
	//wait_queue_head_t wq;
	nand_state_t 	state;
	uint64_t 		page_shift;
	int		phys_erase_shift;
	int		bbt_erase_shift;
	int		chip_shift;
	struct mtd_oob_ops	ops;
	int		oobdirty;
	u_char		*data_poi;
	unsigned int	options;
	int		badblockpos;
	int		numchips;
	uint64_t chipsize;

	uint64_t device_size;
	uint64_t		pagemask;
	int		pagebuf;
	struct nand_oobinfo	*autooob;

	struct nand_bbt_descr	*bbt_td;
	struct nand_bbt_descr	*bbt_md;
	struct nand_bbt_descr	*badblock_pattern;	
	struct nand_hw_control  *controller;
	void		*priv;

	unsigned char maker_code;	
	unsigned char device_code; 
	unsigned int ppb;	//page per block
	unsigned int oob_size;	//spare area size
	unsigned int block_num;
	unsigned int page_num;
	BB_t *bbt;
	unsigned int RBA;
	unsigned int RBA_PERCENT;
	__u32 *erase_page_flag;
	unsigned char active_chip;
	unsigned int BBs;

	unsigned int mcp;
	unsigned short ecc_select;	//modify unsigned char to unsigned short by alexchang 0319-2010	
};
//=============================================================================


extern int nand_scan_bbt (struct mtd_info *mtd, struct nand_bbt_descr *bd);
extern int nand_update_bbt (struct mtd_info *mtd, loff_t offs);
extern int nand_default_bbt (struct mtd_info *mtd);
extern int nand_isbad_bbt (struct mtd_info *mtd, loff_t offs, int allowbbt);
//extern int nand_erase_nand (struct mtd_info *mtd, struct erase_info *instr, int allowbbt);
extern int nand_do_read_ecc (struct mtd_info *mtd, loff_t from, size_t len,
                             size_t * retlen, u_char * buf, u_char * oob_buf,
                             struct nand_oobinfo *oobsel, int flags);

extern int nand_read_on_the_fly (struct mtd_info *mtd, loff_t from, size_t len, size_t * retlen, u_char * buf, u16 cp_mode);
extern int nand_read_ecc_on_the_fly (struct mtd_info *mtd, loff_t from, size_t len,size_t *retlen, u_char *buf, struct mtd_oob_ops *ops,u16 cp_mode);

#endif

