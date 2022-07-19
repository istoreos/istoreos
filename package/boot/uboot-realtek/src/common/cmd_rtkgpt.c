/*
 * (C) Copyright 2000-2003
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
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
#include <sata.h>
#include <rtkgpt.h>
#include <part_efi.h>

#define PRINT_W_INFO2(INFO,A,B,C)\
    printf("%s %03d: %s, lba 0x%lx, cnt 0x%lx, buffer 0x%lx\n", __FUNCTION__, __LINE__, INFO, (ulong)A, (ulong)B, (ulong)C);

#define RTKGPT_DEBUG(fmt, args...) \
    { \
        if ( debug_mode ) { \
            printf("%s %03d: " fmt "\n", __FUNCTION__, __LINE__, ##args); \
        } \
    }

#ifdef CONFIG_CMD_SATA
  extern int sata_curr_device;
  extern block_dev_desc_t sata_dev_desc[CONFIG_SYS_SATA_MAX_DEVICE];
#else
  #ifndef CONFIG_SYS_SATA_MAX_DEVICE
    #define CONFIG_SYS_SATA_MAX_DEVICE 1
  #endif
  int sata_curr_device;
  block_dev_desc_t sata_dev_desc[CONFIG_SYS_SATA_MAX_DEVICE];
#endif

extern unsigned int get_checksum(uchar *p, uint len);

DECLARE_GLOBAL_DATA_PTR;

static int debug;

#define RTKGPT "rtkgpt"

/*
static void rtkgpt_hexdump( const char * str, unsigned int start_address, unsigned int length )
{
    unsigned int i, j, rows, count;
    unsigned char * ptmp = (unsigned char *)(ulong)start_address;
    printf("======================================================\n");
    printf("%s(base=0x%08x)\n", str, start_address);
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

void fill_one_pte(gpt_entry * pte_curr,
    int idx,
    unsigned long long start_lba,
    unsigned long long end_lba,
    const char * desc)
{
    unsigned short * pu16Name;
    int i, desc_len;
    desc_len = strlen(desc);
    //printf(">>> %s len is %d\n", desc, desc_len);
    memcpy(pte_curr, myPTE, sizeof(myPTE));
    pte_curr->starting_lba = start_lba;
    pte_curr->ending_lba   = end_lba;
    pte_curr->unique_partition_guid.b[15] = (char)idx;
    pu16Name = pte_curr->partition_name;
    if (desc_len < 16) {
        for( i = 0; i < desc_len; i++ ) {
            pu16Name[i] = desc[i];
        }
    }
}

void fill_GPT_PTES_5D01_GPT_X(gpt_entry * pte_curr, unsigned long long disk_size, unsigned long long start_lba)
{
    unsigned long long blk_size;
    int gpt_idx;
    gpt_idx = 0;

    // GPT PTE0
    blk_size = ((128ULL<<20)>>9);;
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "FAT");pte_curr++;
    // GPT PTE1
    start_lba += blk_size;
    blk_size = (disk_size-4)-start_lba;
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "DISKVOLUME0");pte_curr++;
}

void fill_GPT_PTES_160926_GPT24(gpt_entry * pte_curr, unsigned long long disk_size, unsigned long long start_lba)
{
    unsigned long long blk_size;
    int gpt_idx;
    gpt_idx = 0;

    // GPT PTE0
    blk_size = 2014ULL;
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "FW_TABLE");pte_curr++;
    // --------------------------
    // GPT PTE1 KERNEL A
    start_lba += blk_size;
    blk_size = ((32ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "KERNEL_A");pte_curr++;
    // GPT PTE2 ROOTFS A
    start_lba += blk_size;
    blk_size = ((32ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "ROOTFS_A");pte_curr++;
    // GPT PTE3 ROOTFS RESCUE
    start_lba += blk_size;
    blk_size = ((32ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "ROOTFS_B");pte_curr++;
    // GPT PTE4 FDT A
    start_lba += blk_size;
    blk_size = ((1ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "FDT_A");pte_curr++;
    // GPT PTE5 FDT RESCUE
    start_lba += blk_size;
    blk_size = ((1ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "FDT_B");pte_curr++;
    // GPT PTE6
    start_lba += blk_size;
    blk_size = ((4ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "AFW_A");pte_curr++;
    // --------------------------
    // GPT PTE7 KERNEL B
    start_lba += blk_size;
    blk_size = ((32ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "KERNEL_B");pte_curr++;
    // GPT PTE8 ROOTFS B
    start_lba += blk_size;
    blk_size = ((32ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "ROOTFS_GOLD");pte_curr++;
    // GPT PTE9 FDT B
    start_lba += blk_size;
    blk_size = ((1ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "FDT_GOLD");pte_curr++;
    // GPT PTE10
    start_lba += blk_size;
    blk_size = ((4ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "AFW_B");pte_curr++;
    // --------------------------
    // GPT PTE11
    start_lba += blk_size;
    blk_size = ((1ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "BOOTCODE32");pte_curr++;
    // GPT PTE12
    start_lba += blk_size;
    blk_size = ((1ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "BOOTCODE64");pte_curr++;
    // GPT PTE13
    start_lba += blk_size;
    blk_size = ((1ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "BL31");pte_curr++;
    // GPT PTE14
    start_lba += blk_size;
    blk_size = ((1ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "BL32");pte_curr++;
    // GPT PTE15
    start_lba += blk_size;
    blk_size = ((32ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "KERNEL_GOLD");pte_curr++;
    // GPT PTE16
    start_lba += blk_size;
    blk_size = ((4ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "AFW_GOLD");pte_curr++;
    // GPT PTE17 CONFIG
    start_lba += blk_size;
    blk_size = ((32ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "CONFIG");pte_curr++;
    // --------------------------
    // GPT PTE18 SYSTEM A
    start_lba += blk_size;
    blk_size = ((800ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "SYSTEM_A");pte_curr++;
    // --------------------------
    // GPT PTE19 SYSTEM B
    start_lba += blk_size;
    blk_size = ((800ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "SYSTEM_B");pte_curr++;
    // GPT PTE20
    start_lba += blk_size;
    blk_size = ((800ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "CACHE");pte_curr++;
    // GPT PTE21
    start_lba += blk_size;
    blk_size = ((2048ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "DATA");pte_curr++;
    // GPT PTE22 reservered 2G swap partition
    start_lba += blk_size;
    blk_size = ((2048ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "SWAP");pte_curr++;
    // GPT PTE23
    start_lba += blk_size;
    blk_size = (disk_size-4)-start_lba;
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "DISKVOLUME1");pte_curr++;
}

void fill_GPT_PTES_V3_GPT24(gpt_entry * pte_curr, unsigned long long disk_size, unsigned long long start_lba)
{
    unsigned long long blk_size;
    int gpt_idx;
    gpt_idx = 0;

    // GPT PTE0
    blk_size = 2014ULL;
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "FW_TABLE");pte_curr++;
    // --------------------------
    // GPT PTE1 KERNEL A
    start_lba += blk_size;
    blk_size = ((32ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "KERNEL_A");pte_curr++;
    // GPT PTE2 ROOTFS A
    start_lba += blk_size;
    blk_size = ((32ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "ROOTFS_A");pte_curr++;
    // GPT PTE3 ROOTFS RESCUE
    start_lba += blk_size;
    blk_size = ((32ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "ROOTFS_B");pte_curr++;
    // GPT PTE4 FDT A
    start_lba += blk_size;
    blk_size = ((1ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "FDT_A");pte_curr++;
    // GPT PTE5 FDT RESCUE
    start_lba += blk_size;
    blk_size = ((1ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "FDT_B");pte_curr++;
    // GPT PTE6
    start_lba += blk_size;
    blk_size = ((4ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "AFW_A");pte_curr++;
    // --------------------------
    // GPT PTE7 KERNEL B
    start_lba += blk_size;
    blk_size = ((32ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "KERNEL_B");pte_curr++;
    // GPT PTE8 ROOTFS B
    start_lba += blk_size;
    blk_size = ((32ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "ROOTFS_GOLD");pte_curr++;
    // GPT PTE9 FDT B
    start_lba += blk_size;
    blk_size = ((1ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "FDT_GOLD");pte_curr++;
    // GPT PTE10
    start_lba += blk_size;
    blk_size = ((4ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "AFW_B");pte_curr++;
    // --------------------------
    // GPT PTE11
    start_lba += blk_size;
    blk_size = ((1ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "BOOTCODE32");pte_curr++;
    // GPT PTE12
    start_lba += blk_size;
    blk_size = ((1ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "BOOTCODE64");pte_curr++;
    // GPT PTE13
    start_lba += blk_size;
    blk_size = ((1ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "BL31");pte_curr++;
    // GPT PTE14
    start_lba += blk_size;
    blk_size = ((1ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "BL32");pte_curr++;
    // GPT PTE15
    start_lba += blk_size;
    blk_size = ((32ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "KERNEL_GOLD");pte_curr++;
    // GPT PTE16
    start_lba += blk_size;
    blk_size = ((4ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "AFW_GOLD");pte_curr++;
    // GPT PTE17 CONFIG
    start_lba += blk_size;
    blk_size = ((32ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "CONFIG");pte_curr++;
    // --------------------------
    // GPT PTE18 SYSTEM A
    start_lba += blk_size;
    blk_size = ((800ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "SYSTEM_A");pte_curr++;
    // --------------------------
    // GPT PTE19 SYSTEM B
    start_lba += blk_size;
    blk_size = ((800ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "SYSTEM_B");pte_curr++;
    // GPT PTE20
    start_lba += blk_size;
    blk_size = ((800ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "CACHE");pte_curr++;
    // GPT PTE21
    start_lba += blk_size;
    blk_size = ((2048ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "DATA");pte_curr++;
    // GPT PTE22 reservered 2G swap partition
    start_lba += blk_size;
    blk_size = ((2048ULL<<20)>>9);
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "SWAP");pte_curr++;
    // GPT PTE23
    start_lba += blk_size;
    blk_size = (disk_size-4)-start_lba;
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "DISKVOLUME1");pte_curr++;
}

void fill_GPT_PTES_one_only(gpt_entry * pte_curr, unsigned long long disk_size, unsigned long long start_lba)
{
    unsigned long long blk_size;
    int gpt_idx;

    gpt_idx = 0;
    // GPT PTE0
    blk_size = (disk_size-4)-start_lba;
    fill_one_pte(pte_curr, gpt_idx++, start_lba, (start_lba+blk_size-1), "SYSTEM");pte_curr++;
}

unsigned int rtkgpt_gen(DEVICE_SEL_T device_sel, int gpt_ver)
{
    int dev;
    block_dev_desc_t * dev_desc;
    size_t count, pad_count;
    gpt_entry * pte;
    unsigned long long disk_size;
    unsigned long long cur_lba;
    unsigned long long cur_blkcnt;
    unsigned int header_crc32;
    unsigned int pte_crc32;
    unsigned long long first_usable_lba;

    dev = 0;
    dev_desc = NULL;

    first_usable_lba = 64; // default

    if( device_sel == DEVICE_SEL_SATA ) {
#ifdef CONFIG_CMD_SATA
        if( sata_curr_device < 0 ) {
            printf("%s %03d: sata_curr_device %d\n", __FUNCTION__, __LINE__,
                sata_curr_device);
            printf("%s %03d: please init SATA first\n", __FUNCTION__, __LINE__);
            return -1;
        }
        dev_desc = &sata_dev_desc[dev];
        first_usable_lba = 34;
#endif
    }
    if( device_sel == DEVICE_SEL_SD ) {
#ifdef CONFIG_CMD_SD
        extern block_dev_desc_t *sd_get_dev(int dev);
        dev_desc = sd_get_dev(dev);
        first_usable_lba = 2048;
#endif
    }
    if( dev_desc == NULL ) {
        printf("%s %03d: No block device exist\n", __FUNCTION__, __LINE__);
        return -2;
    }

    pte = NULL;

#if 0
    disk_size = 1953525168;// WD10JPVX 1.0TB
#else
    disk_size = dev_desc->lba;
#endif

    // show info
    printf("%s %03d: dev %d, dev blksz 0x%lx\n", __FUNCTION__, __LINE__, dev, dev_desc->blksz);

    // MBR
    ALLOC_CACHE_ALIGN_BUFFER_PAD(legacy_mbr, legacymbr, 1, dev_desc->blksz);
    memcpy(legacymbr, myMBR, sizeof(myMBR));
    //rtkgpt_hexdump("legacymbr", (unsigned int)legacymbr, dev_desc->blksz);

    // GPT header
    ALLOC_CACHE_ALIGN_BUFFER_PAD(gpt_header, gpt_head, 1, dev_desc->blksz);
    ALLOC_CACHE_ALIGN_BUFFER_PAD(gpt_header, gpt_head_alt, 1, dev_desc->blksz);
    memcpy(gpt_head, myGPTheader, sizeof(myGPTheader));
    memcpy(gpt_head_alt, myGPTheader_alt, sizeof(myGPTheader));
    //rtkgpt_hexdump("gpt_head", (unsigned int)gpt_head, dev_desc->blksz);
    gpt_head->header_crc32 = 0;
    gpt_head->my_lba = 1;
    gpt_head->alternate_lba = disk_size-1;
    gpt_head->first_usable_lba = first_usable_lba;
    gpt_head->last_usable_lba = disk_size-4-1;
    gpt_head->partition_entry_lba = 2;
    gpt_head->partition_entry_array_crc32 = 0;

    gpt_head_alt->header_crc32 = 0;
    gpt_head_alt->my_lba = disk_size-1;
    gpt_head_alt->alternate_lba = 1;
    gpt_head_alt->first_usable_lba = first_usable_lba;
    gpt_head_alt->last_usable_lba = disk_size-4-1;
    gpt_head_alt->partition_entry_lba = 2;
    gpt_head_alt->partition_entry_array_crc32 = 0;

    // Partition alignment
    //printf("%s %03d: gpt_head->num_partition_entries 0x%08x\n", __FUNCTION__, __LINE__,  le32_to_cpu(gpt_head->num_partition_entries));
    //printf("%s %03d: gpt_head->sizeof_partition_entry 0x%08x\n", __FUNCTION__, __LINE__, le32_to_cpu(gpt_head->sizeof_partition_entry));

    count = le32_to_cpu(gpt_head->num_partition_entries) *
            le32_to_cpu(gpt_head->sizeof_partition_entry);

    pad_count = PAD_TO_BLOCKSIZE(count, dev_desc);

    //printf("%s %03d: count 0x%08x, pad_count 0x%08x\n", __FUNCTION__, __LINE__, count, pad_count);


    /* Allocate memory for PTE, remember to FREE */
    if (count != 0) {
        pte = memalign(ARCH_DMA_MINALIGN,
                   pad_count /*PAD_TO_BLOCKSIZE(count, dev_desc)*/);
        memset(pte, 0, pad_count);
    }

    // update PTE first
    if( gpt_ver == 0x5D01 )
        fill_GPT_PTES_5D01_GPT_X(pte, disk_size, first_usable_lba);
    else if( gpt_ver == 0x160926 )
        fill_GPT_PTES_160926_GPT24(pte, disk_size, first_usable_lba);
    else if( gpt_ver == 0x3 )
        fill_GPT_PTES_V3_GPT24(pte, disk_size, first_usable_lba);
    else if( gpt_ver == 0xF001 )
        fill_GPT_PTES_one_only(pte, disk_size, first_usable_lba);

    // update crc32
    pte_crc32 = crc32(0, (unsigned char *)pte, pad_count);

    // update MBR
    cur_lba = 0;
    cur_blkcnt = 1;
    PRINT_W_INFO2("update MBR", cur_lba, cur_blkcnt, legacymbr);
    if ((dev_desc->block_write(dev_desc->dev, cur_lba, cur_blkcnt, (ulong *)legacymbr) != cur_blkcnt)) {
        printf("%s %03d: write MBR fail\n", __FUNCTION__, __LINE__);
        return -1;
    }

    // update GPT header and alternate GPT header
    cur_lba = 1;
    cur_blkcnt = 1;
    gpt_head->partition_entry_array_crc32 = pte_crc32;
    header_crc32 = crc32(0, (unsigned char *)gpt_head, 0x5C);
    gpt_head->header_crc32 = header_crc32;
    PRINT_W_INFO2("update GPT header", cur_lba, cur_blkcnt, gpt_head);
    if ((dev_desc->block_write(dev_desc->dev, cur_lba, cur_blkcnt, (ulong *)gpt_head) != cur_blkcnt)) {
        printf("%s %03d: write gpt_head fail\n", __FUNCTION__, __LINE__);
        return -1;
    }
    // update alternated GPT header
    cur_lba = disk_size-1;
    cur_blkcnt = 1;
    gpt_head_alt->partition_entry_array_crc32 = pte_crc32;
    header_crc32 = crc32(0, (unsigned char *)gpt_head_alt, 0x5C);
    gpt_head_alt->header_crc32 = header_crc32;
    PRINT_W_INFO2("update alternate GPT header", cur_lba, cur_blkcnt, gpt_head_alt);
    if ((dev_desc->block_write(dev_desc->dev, cur_lba, cur_blkcnt, (ulong *)gpt_head_alt) != cur_blkcnt)) {
        printf("%s %03d: write gpt_head_alt fail\n", __FUNCTION__, __LINE__);
        return -1;
    }

    // update PTE
    cur_lba = 2;
    cur_blkcnt = 32;
    PRINT_W_INFO2("update PTE", cur_lba, cur_blkcnt, pte);
    if ((dev_desc->block_write(dev_desc->dev, cur_lba, cur_blkcnt, (ulong *)pte) != cur_blkcnt)) {
        printf("%s %03d: write PTE fail\n", __FUNCTION__, __LINE__);
        return -1;
    }

    return 0;
}

void run_rtkgpt_gen(DEVICE_SEL_T device_sel, int gpt_ver)
{
    unsigned int ret_val;

    switch( gpt_ver ) {
        case 0x5D01:
        case 0x160926:
        case 0x3:
        case 0xF001:
            ret_val = rtkgpt_gen(device_sel, gpt_ver);
            break;
        default:
            printf("Please give gpt ver. 190926 or F001. curr input is %08x\n", gpt_ver );
            ret_val = -1;
    }
    printf("ret val = 0x%08x(%s)\n", ret_val, ret_val == 0 ? "OK" : "FAIL" );
}

unsigned int rtkgpt_fwtable(int debug_mode)
{
#if 1
    DDDDRED("!!!!! Under construction !!!!!\n");
#else
    int dev, i;
    block_dev_desc_t * dev_desc;
    //size_t count, pad_count;
    //gpt_entry * pte;
    //unsigned long long disk_size;
    unsigned long long cur_lba;
    unsigned long long cur_blkcnt;
    //unsigned int header_crc32;
    //unsigned int pte_crc32;
    //block_dev_desc_t *pdev = &(sata_dev_desc[dev]);
    unsigned int fw_desc_table_base;
    fw_desc_table_v1_t * pfw_desc_table_v1;
    part_desc_entry_v1_t * ppart_entry;
    //part_desc_entry_v1_t * ppart_entry_curr;
    fw_desc_entry_v1_t * pfw_entry;
    fw_desc_entry_v1_t * pfw_entry_curr;
    unsigned int part_entry_num;
    unsigned int fw_entry_num;
    unsigned int fw_desc_table_checksum;

    if( sata_curr_device < 0 ) {
        printf("%s %03d: sata_curr_device %d\n", __FUNCTION__, __LINE__, sata_curr_device);
        printf("%s %03d: please init SATA first\n", __FUNCTION__, __LINE__);
        return -1;
    }

    dev = 0;
    dev_desc = &sata_dev_desc[dev];

    // show info
    printf("%s %03d: dev %d, dev blksz 0x%lx\n", __FUNCTION__, __LINE__, dev, dev_desc->blksz);

    // create fw table
    fw_desc_table_base = FIRMWARE_DESCRIPTION_TABLE_ADDR; /* 0x06400000 */
    memcpy( (void*)(ulong)fw_desc_table_base, myFWTLB, sizeof(myFWTLB));

    // (1)
    pfw_desc_table_v1 = (fw_desc_table_v1_t *)(ulong)fw_desc_table_base;
    pfw_desc_table_v1->checksum = 0xF1F2F3F4;

    // (2)
    ppart_entry = (part_desc_entry_v1_t *)(fw_desc_table_base+sizeof(fw_desc_table_v1_t));
    part_entry_num = pfw_desc_table_v1->part_list_len / sizeof(part_desc_entry_v1_t);
    RTKGPT_DEBUG("ppart_entry ptr %p, part_entry_num = %d", ppart_entry, part_entry_num);

    // (3)
    pfw_entry = (fw_desc_entry_v1_t *)(fw_desc_table_base+sizeof(fw_desc_table_v1_t)+pfw_desc_table_v1->part_list_len);
    fw_entry_num = pfw_desc_table_v1->fw_list_len / sizeof(fw_desc_entry_v1_t);
    RTKGPT_DEBUG("fw_entry_num = %d", fw_entry_num);

    for( i = 0; i < fw_entry_num; i++ ) {
        pfw_entry_curr = &pfw_entry[i];
        printf("i = %02x, type 0x%02x: ",  i, pfw_entry_curr->type);
        switch(pfw_entry_curr->type)
        {
        case FW_TYPE_KERNEL: /* 2 */
            printf("Normal Kernel:\n");
            pfw_entry_curr->offset = (2048<<9);     // offset in byte ( LBA_addr * 512 )
            break;

        case FW_TYPE_RESCUE_DT: /* 3 */
            printf("Rescue DT:\n");
            pfw_entry_curr->offset = (200704<<9);   // offset in byte ( LBA_addr * 512 )
            break;

        case FW_TYPE_KERNEL_DT: /* 4 */
            printf("Normal DT:\n");
            pfw_entry_curr->offset = (198656<<9);   // offset in byte ( LBA_addr * 512 )
            break;

        case FW_TYPE_RESCUE_ROOTFS: /* 5 */
            printf("Rescue rootfs:\n");
            pfw_entry_curr->offset = (133120<<9);   // offset in byte ( LBA_addr * 512 )
            break;

        case FW_TYPE_KERNEL_ROOTFS: /* 6 */
            printf("Normal rootfs:\n");
            pfw_entry_curr->offset = (67584<<9);    // offset in byte ( LBA_addr * 512 )
            break;

        case FW_TYPE_AUDIO: /* 7 */
            printf("Normal AFW:\n");
            pfw_entry_curr->offset = (202752<<9);   // offset in byte ( LBA_addr * 512 )
            break;

        case FW_TYPE_GOLD_KERNEL: /* 31 (0x1F)*/
            printf("Golden Kernel:\n");
            pfw_entry_curr->offset = (210944<<9);   // offset in byte ( LBA_addr * 512 )
            break;

        case FW_TYPE_GOLD_RESCUE_DT: /* 32 (0x20) */
            printf("Golden Rescue DT:\n");
            pfw_entry_curr->offset = (409600<<9);   // offset in byte ( LBA_addr * 512 )
            break;

        case FW_TYPE_GOLD_RESCUE_ROOTFS: /* 33 (0x21) */
            printf("Golden Rescue rootfs:\n");
            pfw_entry_curr->offset = (342016<<9);   // offset in byte ( LBA_addr * 512 )
            break;

        case FW_TYPE_GOLD_AUDIO: /* 34 (0x22) */
            printf("Golden AFW:\n");
            pfw_entry_curr->offset = (411648<<9);   // offset in byte ( LBA_addr * 512 )
            break;

        case FW_TYPE_UBOOT: /* 37 (0x25)*/
            printf("Support BootCode64\n");
            pfw_entry_curr->offset = 0;             // offset in byte ( LBA_addr * 512 )
            break;

        default:
            printf("Unknown\n");
        }// end switch
    } // end for-loop

    // update the checksum of fw_desc_table
    fw_desc_table_checksum = get_checksum(  (uchar*)(ulong)fw_desc_table_base +
                                            offsetof(fw_desc_table_v1_t, version),
                                            sizeof(fw_desc_table_v1_t) -
                                            offsetof(fw_desc_table_v1_t, version) +
                                            pfw_desc_table_v1->part_list_len +
                                            pfw_desc_table_v1->fw_list_len);
    pfw_desc_table_v1->checksum = fw_desc_table_checksum;

    // write fw table
    cur_lba = 34;
    cur_blkcnt = 2;
    PRINT_W_INFO2("update fw table", cur_lba, cur_blkcnt, fw_desc_table_base);
    if ((dev_desc->block_write(dev_desc->dev, cur_lba, cur_blkcnt, (ulong *)(ulong)fw_desc_table_base) != cur_blkcnt)) {
        printf("%s %03d: fw table fail\n", __FUNCTION__, __LINE__);
        return -1;
    }

    // write golden fw table
    cur_lba = 1024;
    cur_blkcnt = 2;
    PRINT_W_INFO2("update golden fw table", cur_lba, cur_blkcnt, fw_desc_table_base);
    if ((dev_desc->block_write(dev_desc->dev, cur_lba, cur_blkcnt, (ulong *)(ulong)fw_desc_table_base) != cur_blkcnt)) {
        printf("%s %03d: golden fw table fail\n", __FUNCTION__, __LINE__);
        return -1;
    }
#endif
    return 0;
}

void run_rtkgpt_fwtable(int debug_mode)
{
    unsigned int reg_val;

    reg_val = rtkgpt_fwtable(debug_mode);

    printf("ret val = 0x%08x(%s)\n", reg_val, reg_val == 0 ? "OK" : "FAIL" );
}

int do_rtkgpt(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
    int cmd;
    DEVICE_SEL_T device_sel;
    int gpt_ver;

    cmd = -1;
    debug = 0;
    gpt_ver = 0;
    device_sel = DEVICE_SEL_NONE;

    // parse command
    if( argc > 1 ) {
        if( strncmp( argv[1], "gen", 3 ) == 0 ) {
            cmd = 0;
            gpt_ver = 0;
            if( argc > 2 ) {
                if( strncmp( argv[2], "sata", 4 ) == 0  ) {
                    device_sel = DEVICE_SEL_SATA;
                }
                else if( strncmp( argv[2], "sd", 2 ) == 0  ) {
                    device_sel = DEVICE_SEL_SD;
                }
            }
            if( argc > 3 ) {
                if( strncmp( argv[3], "sdcard_V1", 9 ) == 0  ) {
                    gpt_ver = 0x5D01; // SD V01
                }
                else if( strncmp( argv[3], "160926", 6 ) == 0  ) {
                    gpt_ver = 0x160926; // date code
                }
                else if( strncmp( argv[3], "V3", 2 ) == 0  ) {
                    gpt_ver = 0x3; // customized
                }
                else if( strncmp( argv[3], "F001", 4 ) == 0  ) {
                    gpt_ver = 0xF001; // special case - one GPT partition only
                }
            }
            if( argc > 4 ) {
                if( strncmp( argv[4], "debug", 5 ) == 0  ) {
                    debug = 1;
                }
            }
            if( (device_sel==DEVICE_SEL_NONE) || !gpt_ver ) {
                cmd = -1;
            }
        }
        if( strncmp( argv[1], "fwtable", 3 ) == 0 ) {
            cmd = 1;
            if( argc > 2 ) {
                if( strncmp( argv[2], "debug", 5 ) == 0  ) {
                    debug = 1;
                }
            }
        }
    }

    if( cmd < 0 ) {
        printf("Error: command %s error\n", argv[1]);
        return -1;
    }

    do {
        if( cmd == 0 ) {
            run_rtkgpt_gen(device_sel, gpt_ver);
            return 0;
        }
        if( cmd == 1 ) {
            run_rtkgpt_fwtable(debug);
            return 0;
        }
    }
    while(0);

    return -1;
}

U_BOOT_CMD(
    rtkgpt, 5, 0,   do_rtkgpt,
    "rtkgpt utility",
    "\n(1)rtkgpt gen [sata|sd] [sdcard_V1|160926|V3|F001] [debug]"
    "\n(2)rtkgpt fwtable [debug]"
    "\n-------------------------------------------"
    "\nsdcard_V1: sd card layout V1, total 10 GPT partitions"
    "\n160926   : monarch layout, total 24 GPT partitions"
    "\nV3       : monarch layout, total 24 GPT partitions"
    "\nF001     : 1 GPT partition"
);
