/*
 * Realtek fat32 format tool
 * jinn.cheng@realtek.com
 */

/*
 * Misc boot support
 */
#include <common.h>
#include <command.h>
#include <malloc.h>
#include <asm/arch/fw_info.h>
#include <asm/arch/system.h>
#include <asm/arch/extern_param.h>
#include <asm/byteorder.h>
#include <asm/unaligned.h>
#include <part.h>
#include <usb.h>
#include <part_efi.h>
#include <fat.h>
#include <rtkmkfat.h>

#define RTKMKFAT "rtkfat:"

#define RTKFAT_DEBUG(fmt, args...) \
    { \
        if ( debug ) { \
            printf("%s %03d: " fmt, RTKMKFAT, __LINE__, ##args); \
        } \
    }
#define RTKFAT_PRINT(fmt, args...) \
    { \
        printf("%s %03d: " fmt, RTKMKFAT, __LINE__, ##args); \
    }

extern unsigned int get_checksum(uchar *p, uint len);

DECLARE_GLOBAL_DATA_PTR;

static int debug;
static DEVICE_SEL_T device_sel;
static int part_sel;
static unsigned int target_start_lba;;
static unsigned int target_szie;
static unsigned int target_cluster_szie;

/*
 *
 *
 *
 */
/*
static void rtkfat_hexdump(
	const char * str,
	unsigned long start_address,
	unsigned int length )
{
    unsigned int i, j, rows, count;
    unsigned char * ptmp = (unsigned char *)start_address;
    printf("======================================================\n");
    printf("%s(base=0x%lx)\n", str, start_address);
    count = 0;
    rows = (length+((1<<4)-1)) >> 4;
    for( i = 0; ( i < rows ) && (count < length); i++ ) {
        printf("%03x :", i<<4 );
        for( j = 0; ( j < 16 ) && (count < length); j++ ) {

            printf(" %02x",  *ptmp );
            count++;
            ptmp++;
        }
        printf("\n");
    }
}
*/

/*
 *
 *
 *
 */
int run_rtkfat_get_partinfo( 
	unsigned int dev_id,
	int part_no,
	unsigned long * pGPT_base,
	unsigned long * pGPT_szie )
{
    block_dev_desc_t *dev_desc = NULL;
    disk_partition_t cur_part_info;

    if( dev_id != 0 ) {
        RTKFAT_PRINT("Error! only support dev_id %d\n", dev_id);
        return -1;
    }

    if( part_sel < 0 ) {
        RTKFAT_PRINT("part_sel %d error\n", part_sel);
        return -2;
    }

    if( device_sel == DEVICE_SEL_SATA ) {
        dev_desc = get_dev("sata", dev_id);
        if (dev_desc == NULL) {
            RTKFAT_PRINT("Invalid SATA device\n");
            return -3;
        }
    }

    if( device_sel == DEVICE_SEL_SD ) {
        dev_desc = get_dev("sd", dev_id);
        if (dev_desc == NULL) {
            RTKFAT_PRINT("Invalid SD device\n");
            return -4;
        }
    }

    if( dev_desc == NULL ) {
        RTKFAT_PRINT("No device was selected\n");
        return -10;
    }

    /* check partition type */
    init_part(dev_desc);
    /* Read the partition table, if present */
    if (!get_partition_info(dev_desc, part_no, &cur_part_info)) {
        // find partition
    }
    else {
        RTKFAT_PRINT("Can not find partition info from part %d\n", part_no);
        return -11;
    }

    RTKFAT_DEBUG("device %x:%x start 0x%lx\n",
    	dev_id, part_no, cur_part_info.start);
    RTKFAT_DEBUG("device %x:%x size  0x%lx\n",
    	dev_id, part_no, cur_part_info.size);

    *pGPT_base = cur_part_info.start;
    *pGPT_szie = cur_part_info.size;

    return 0;
}

// cluster size = 8
// sector size 0x0010_0000
// max cluster = 0x0010_0000 * 64/513 ~ 130816
// fat size = 130816 / 128 = 1022 = 0x3FE
//
/*
 *
 *
 *
 */
int run_rtkfat_format(
	unsigned int dev_id,
	unsigned long bpa_base,
	unsigned long total_sectors,
	unsigned int cluster_size )
{
    unsigned long cur_lba;
    unsigned long cur_blkcnt;
    unsigned long blkcnt;
    unsigned long useable_size;
    unsigned int fat_size;
    unsigned int total_clusters;
    block_dev_desc_t * dev_desc;
    boot_sector * pBPB;
    fat32_fsinfo * pFSINFO;
    void * pTemp;
    ALLOC_CACHE_ALIGN_BUFFER_PAD(dummy_data_512B, pData512B, 1, 512);
    pTemp = memalign(ARCH_DMA_MINALIGN, 8192);

    dev_desc = NULL;
    // show info
    RTKFAT_DEBUG("dev %d\n", dev_id);
    RTKFAT_DEBUG("bpa_base 0x%lx\n", bpa_base);
    RTKFAT_DEBUG("total_sectors 0x%lx\n", total_sectors);
    RTKFAT_DEBUG("cluster_size 0x%x\n", cluster_size);

    if( !pTemp || !pData512B ) {
        RTKFAT_PRINT("allocate memory fail\n");
        return -1;
    }

    if( dev_id != 0 ) {
        RTKFAT_PRINT("dev_id %d\n", dev_id);
        return -3;
    }


    if( device_sel == DEVICE_SEL_SATA ) {
        dev_desc = get_dev("sata", dev_id);
        if (dev_desc == NULL) {
            RTKFAT_PRINT("Invalid SATA device\n");
            return -3;
        }
        //if( sata_curr_device < 0 ) {
        //    RTKFAT_PRINT("sata_curr_device %d\n", sata_curr_device);
        //    RTKFAT_PRINT("please init SATA first\n");
        //    return -2;
        //}
        //dev_desc = &sata_dev_desc[dev_id];
    }
    if( device_sel == DEVICE_SEL_SD ) {
        dev_desc = get_dev("sd", dev_id);
        if (dev_desc == NULL) {
            RTKFAT_PRINT("Invalid SD device\n");
            return -3;
        }
    }

    if( total_sectors < 0x00010000 ) { // at least 32MB
        RTKFAT_PRINT("dev_id %d\n", dev_id);
        RTKFAT_PRINT("The size of selected part is less than 32MB\n");
        return -10;
    }

    useable_size = total_sectors - BPB_RESERVED_SECTORS;

    if( cluster_size == 1 ||
        cluster_size == 2 ||
        cluster_size == 4 ||
        cluster_size == 8 ||
        cluster_size == 16 ||
        cluster_size == 32 ||
        cluster_size == 64 ||
        cluster_size == 128 )
    {
        total_clusters = ( useable_size * 64 ) / ( (64 * cluster_size) +1 );
    }
    else {
        RTKFAT_PRINT("cluster_size=%d error. (must be 1,2,4,8,16,32,64 or 128)\n",
        	cluster_size);
        return -11;
    }

    if( total_clusters == 0 ) {
        RTKFAT_PRINT("total_clusters=%d error\n", total_clusters);
        return -12;
    }

    fat_size = total_clusters / 128;

    // show status
    RTKFAT_DEBUG("total_clusters 0x%08x\n", total_clusters);
    RTKFAT_DEBUG("fat_size 0x%08x\n", fat_size);
    RTKFAT_DEBUG("pData512B 0x%lx\n", (ulong)pData512B);
    RTKFAT_DEBUG("pTemp 0x%lx\n", (ulong)pTemp);

    // clear partition data
    memset(pTemp, 0, 8192);
    cur_lba = bpa_base;
    blkcnt = BPB_RESERVED_SECTORS + fat_size + fat_size + cluster_size;
    RTKFAT_PRINT("clear selected partition from 0x%lx to 0x%lx (total 0x%lx)\n",
    	cur_lba, (cur_lba+blkcnt-1), blkcnt);

    while( blkcnt ) {
        if( blkcnt > 8 ) {
            cur_blkcnt = 8;
        }
        else {
            cur_blkcnt = blkcnt;
        }
        if ((dev_desc->block_write(
        		dev_desc->dev,
        		cur_lba,
        		cur_blkcnt,
        		(ulong *)pTemp) != cur_blkcnt)) {
            RTKFAT_PRINT("write LBA %ld, cnt %ld fail\n",
            	cur_lba, cur_blkcnt);
            return -100;
        }
        if( (cur_lba&0x7F)==0 ) {
            printf(".");
        }
        blkcnt -= cur_blkcnt;
        cur_lba += cur_blkcnt;
    }
    printf("\n");

    // write BPB
    memcpy(pData512B, myBPB, sizeof(myBPB));
    pBPB = (boot_sector *)pData512B;
    pBPB->cluster_size = cluster_size;
    pBPB->fat32_length = fat_size;
    pBPB->hidden = bpa_base;
    pBPB->total_sect = total_sectors;
    pBPB->reserved = BPB_RESERVED_SECTORS;
    pBPB->backup_boot = BPB_BACKUP_BOOTSECS;
    //rtkfat_hexdump("BPB", (unsigned int)pData512B, sizeof(myBPB));
    cur_lba = bpa_base;
    cur_blkcnt = 1;
    if ((dev_desc->block_write(
    		dev_desc->dev,
    		cur_lba,
    		cur_blkcnt, (ulong *)pData512B) != cur_blkcnt)) {
        RTKFAT_PRINT("write LBA %ld, cnt %ld fail\n", cur_lba, cur_blkcnt);
        return -100;
    }
    RTKFAT_DEBUG("write BPB@LBA %ld(0x%lx) done\n", cur_lba, cur_lba);

#if 1
    cur_lba = bpa_base + BPB_BACKUP_BOOTSECS;
    cur_blkcnt = 1;
    if ((dev_desc->block_write(
    		dev_desc->dev,
    		cur_lba,
    		cur_blkcnt,
    		(ulong *)pData512B) != cur_blkcnt)) {
        RTKFAT_PRINT("write LBA %ld, cnt %ld fail\n", cur_lba, cur_blkcnt);
        return -100;
    }
    RTKFAT_DEBUG("write backup BPB@LBA %ld(0x%lx) done\n", cur_lba, cur_lba);
#endif

    // write FSINFO
    memcpy(pData512B, myFS_INFO, sizeof(myFS_INFO));
    pFSINFO = (fat32_fsinfo *)pData512B;
    //pFSINFO->free_count = total_clusters-1;
#ifdef WRITE_EMPTY_FILE_IN_ROOT
    pFSINFO->next_free = 3;
#else
	pFSINFO->next_free = 2;
#endif
    //rtkfat_hexdump("FSINFO", (unsigned int)pData512B, sizeof(myFS_INFO));
    cur_lba = bpa_base + 1;
    cur_blkcnt = 1;
    if ((dev_desc->block_write(
    		dev_desc->dev,
    		cur_lba,
    		cur_blkcnt,
    		(ulong *)pData512B) != cur_blkcnt)) {
        RTKFAT_PRINT("write LBA %ld, cnt %ld fail\n", cur_lba, cur_blkcnt);
        return -100;
    }
    RTKFAT_DEBUG("write FSINFO@LBA %ld(0x%lx) done\n", cur_lba, cur_lba);

#if 1
    memcpy(pData512B, myFS_INFO, sizeof(myFS_INFO));
    pFSINFO = (fat32_fsinfo *)pData512B;
    cur_lba = bpa_base + 1 + BPB_BACKUP_BOOTSECS;
    cur_blkcnt = 1;
    if ((dev_desc->block_write(
    		dev_desc->dev,
    		cur_lba,
    		cur_blkcnt,
    		(ulong *)pData512B) != cur_blkcnt)) {
        RTKFAT_PRINT("write LBA %ld, cnt %ld fail\n", cur_lba, cur_blkcnt);
        return -100;
    }
    RTKFAT_DEBUG("write backup BPB@LBA %ld(0x%lx) done\n", cur_lba, cur_lba);
#endif

    // write dummy
    memcpy(pData512B, myFS_INFO2, sizeof(myFS_INFO2));
    //rtkfat_hexdump("FSINFO2", (unsigned int)pData512B, sizeof(myFS_INFO2));
    cur_lba = bpa_base + 2;
    cur_blkcnt = 1;
    if ((dev_desc->block_write(
    		dev_desc->dev,
    		cur_lba,
    		cur_blkcnt,
    		(ulong *)pData512B) != cur_blkcnt)) {
        RTKFAT_PRINT("write LBA %ld, cnt %ld fail\n", cur_lba, cur_blkcnt);
        return -100;
    }
    RTKFAT_DEBUG("write FSINFO2@LBA %ld(0x%lx) done\n", cur_lba, cur_lba);

#if 1
    memcpy(pData512B, myFS_INFO2, sizeof(myFS_INFO2));
    //rtkfat_hexdump("FSINFO2", (unsigned int)pData512B, sizeof(myFS_INFO2));
    cur_lba = bpa_base + 2 + BPB_BACKUP_BOOTSECS;
    cur_blkcnt = 1;
    if ((dev_desc->block_write(
    	dev_desc->dev,
    	cur_lba,
    	cur_blkcnt,
    	(ulong *)pData512B) != cur_blkcnt)) {
        RTKFAT_PRINT("write LBA %ld, cnt %ld fail\n", cur_lba, cur_blkcnt);
        return -100;
    }
    RTKFAT_DEBUG("write FSINFO2@LBA %ld(0x%lx) done\n", cur_lba, cur_lba);
#endif

    // write FAT1
    memcpy(pData512B, myFAT, sizeof(myFAT));
    //rtkfat_hexdump("FAT", (unsigned int)pData512B, sizeof(myFAT));
    cur_lba = bpa_base + BPB_RESERVED_SECTORS;
    cur_blkcnt = 1;
    if ((dev_desc->block_write(
    		dev_desc->dev,
    		cur_lba,
    		cur_blkcnt,
    		(ulong *)pData512B) != cur_blkcnt)) {
        RTKFAT_PRINT("write LBA %ld, cnt %ld fail\n", cur_lba, cur_blkcnt);
        return -100;
    }
    RTKFAT_DEBUG("write FAT1@LBA %ld(0x%lx) done\n", cur_lba, cur_lba);

    // write FAT2
    cur_lba = bpa_base + BPB_RESERVED_SECTORS + fat_size;
    cur_blkcnt = 1;
    if ((dev_desc->block_write(
    		dev_desc->dev,
    		cur_lba,
    		cur_blkcnt,
    		(ulong *)pData512B) != cur_blkcnt)) {
        RTKFAT_PRINT("write LBA %ld, cnt %ld fail\n", cur_lba, cur_blkcnt);
        return -100;
    }
    RTKFAT_DEBUG("write FAT2@LBA %ld(0x%lx) done\n", cur_lba, cur_lba);

#ifdef WRITE_EMPTY_FILE_IN_ROOT
    // init ROOT and weite 0-byte file entry
    memcpy(pData512B, myRootDir, sizeof(myRootDir));
    //rtkfat_hexdump("Root DIR", (unsigned int)pData512B, sizeof(myFAT));
    cur_lba = bpa_base + BPB_RESERVED_SECTORS + fat_size+fat_size;
    cur_blkcnt = 1;
    if ((dev_desc->block_write(
    		dev_desc->dev,
    		cur_lba,
    		cur_blkcnt,
    		(ulong *)pData512B) != cur_blkcnt)) {
        RTKFAT_PRINT("write LBA %ld, cnt %ld fail\n", cur_lba, cur_blkcnt);
        return -100;
    }
    RTKFAT_DEBUG("write rootdir@LBA %ld(0x%lx) done\n", cur_lba, cur_lba);
#endif

    return 0;
}


/*
 *
 *
 *
 */
int run_rtkfat_gen(void)
{
    int ret_val;
    unsigned long gpt_start_lba;
    unsigned long gpt_size;

    ret_val = -1;
    gpt_start_lba = 0;
    gpt_size = 0;

    do {
        if( !target_start_lba || !target_szie ) {
            // read GPT table get partition info
            ret_val = run_rtkfat_get_partinfo(
            			0, part_sel, &gpt_start_lba, &gpt_size );
            if( ret_val < 0 ) {
                break;
            }
        }
        else {
            gpt_start_lba = target_start_lba;
            gpt_size = target_szie;
        }
        ret_val = run_rtkfat_format(
        	0, gpt_start_lba, gpt_size, target_cluster_szie);
    } while(0);

    RTKFAT_PRINT("ret val = 0x%08x(%s)\n",
    	 ret_val, ret_val == 0 ? "OK" : "FAIL" );

    return ret_val;
}

/*
 *
 *
 *
 */
int do_rtkfat(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    int cmd;
    device_sel = DEVICE_SEL_NONE;
    part_sel = -1;
    target_start_lba = 0;
    target_szie = 0;
    target_cluster_szie = 0;
    cmd = -1;
    debug = 0;

    // parse command
    if( argc > 1 ) {
        if( strncmp( argv[1], "gen", 3 ) == 0 ) {
            cmd = 0;
            if( argc > 2 ) {
                if( strncmp( argv[2], "sata", 4 ) == 0  ) {
                    device_sel = DEVICE_SEL_SATA;
                }
                if( strncmp( argv[2], "sd", 2 ) == 0  ) {
                    device_sel = DEVICE_SEL_SD;
                }
                do {
                    if( device_sel == DEVICE_SEL_NONE ) {
                        break;
                    }
                    if( argc > 3 ) {
                        if( strncmp( argv[3], "auto", 4 ) == 0  ) {
                            if( argc > 4 ) {
                                part_sel = simple_strtoul(argv[4], NULL, 16);
                            }
                            if( argc > 5 ) {
                                if( strncmp( argv[5], "debug", 5 ) == 0  ) {
                                    debug = 1;
                                }
                                else {
                                    target_cluster_szie = 
                                    simple_strtoul(argv[5], NULL, 16);
                                    if( argc > 6 ) {
                                        if( strncmp( argv[6], "debug", 5 ) == 0  ) {
                                            debug = 1;
                                        }
                                    }
                                }
                            }
                        }
                        if( strncmp( argv[3], "manual", 6 ) == 0  ) {
                            if( argc > 5 ) {
                                target_start_lba = 
                                	simple_strtoul(argv[4], NULL, 16);
                                target_szie = simple_strtoul(argv[5], NULL, 16);
                            }
                            if( argc > 6 ) {
                                if( strncmp( argv[6], "debug", 5 ) == 0  ) {
                                    debug = 1;
                                }
                                else {
                                    target_cluster_szie = 
                                    	simple_strtoul(argv[6], NULL, 16);
                                    if( argc > 7 ) {
                                        if( strncmp( argv[7], "debug", 5 ) == 0  ) {
                                            debug = 1;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                while(0);
            }
        }
    }

    if( target_cluster_szie == 0 ) {
        target_cluster_szie = 1; // default
    }

    if( cmd < 0 || (device_sel == DEVICE_SEL_NONE) ) {
        RTKFAT_PRINT("Error: argu error\n");
        return -1;
    }

    if( part_sel < 0 ) {
        if( !target_start_lba || !target_szie ) {
            RTKFAT_PRINT("Error: start_lba(%d), size(%d) should not be zero if assigned\n",
            	target_start_lba, target_szie );
            return -1;
        }
    }

    run_rtkfat_gen();

    return 0;
}

U_BOOT_CMD(
    rtkfat, 8, 0,   do_rtkfat,
    "Realtek FAT32 format utility v1.0",
    "\n(1)rtkfat gen [sata|sd] auto part [cluster_size] [debug]"
    "\n(2)rtkfat gen [sata|sd] manual startlba part_size [cluster_size] [debug]"
    "\nNote:cluster_size: default 1 (capacity < 260MB)"
    "\n"
    "\nexample:"
    "\n format:  " VT100_YELLOW "rtkfat gen sata auto 12 debug" VT100_NONE
    "\n check:   " VT100_YELLOW "fatls sata 0:12" VT100_NONE
    "\nNote: input value in hex format, 12 indicates 0x12"
    "\n"
    "\nexample:"
    "\n format:  " VT100_YELLOW "rtkfat gen sd auto 1 debug" VT100_NONE
    "\n check:   " VT100_YELLOW "fatls sd 0:1" VT100_NONE
);

