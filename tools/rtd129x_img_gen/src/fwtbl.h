#ifndef __FWTBL_H__
#define __FWTBL_H__

#include <stdint.h>
#include <stddef.h>

typedef struct {
	unsigned char	signature[8];
	uint32_t	checksum;
	unsigned char	version;
	unsigned char	seqnum;
	unsigned char	reserved[6];
	uint32_t	paddings;
	uint32_t	part_list_len;
	uint32_t	fw_list_len;
} __attribute__((packed)) fw_desc_table_v1_t;

typedef struct {
	unsigned char	type;
	unsigned char	reserved:6,
			lzma:1,
			ro:1;
	uint32_t	version;
	uint32_t	target_addr;
	uint64_t	offset;
	uint32_t	length;
	uint32_t	paddings;
	unsigned char	sha_hash[32];
	unsigned char	reserved_1[6];
} __attribute__((packed)) fw_desc_entry_v2_t;

typedef struct {
   unsigned char type;
   unsigned char reserved:7,
   ro:1; 
   uint64_t  length;
   unsigned char   fw_count;
   unsigned char   fw_type;
   unsigned char   partIdx;
   unsigned char   reserved_1[3];
   char   mount_point[32];
} __attribute__((packed)) part_desc_entry_v1_t;

typedef enum {
   FS_TYPE_JFFS2 = 0,
   FS_TYPE_YAFFS2,
   FS_TYPE_SQUASH,
   FS_TYPE_RAWFILE,
   FS_TYPE_EXT4,
   FS_TYPE_UBIFS,
   FS_TYPE_NONE,
   FS_TYPE_UNKNOWN
} fs_type_code_e;

typedef enum {
	FW_TYPE_RESERVED = 0,
	FW_TYPE_BOOTCODE,
	FW_TYPE_KERNEL,
	FW_TYPE_RESCUE_DT,
	FW_TYPE_KERNEL_DT,
	FW_TYPE_RESCUE_ROOTFS, //5
	FW_TYPE_KERNEL_ROOTFS,
	FW_TYPE_AUDIO,
	FW_TYPE_AUDIO_FILE,
	FW_TYPE_VIDEO_FILE,
	FW_TYPE_EXT4, //10
	FW_TYPE_UBIFS,
	FW_TYPE_SQUASH,
	FW_TYPE_EXT3,
	FW_TYPE_ODD,
	FW_TYPE_YAFFS2, //15
	FW_TYPE_ISO,
	FW_TYPE_SWAP,
	FW_TYPE_NTFS,
	FW_TYPE_JFFS2,
	FW_TYPE_IMAGE_FILE, //20
	FW_TYPE_IMAGE_FILE1,
	FW_TYPE_IMAGE_FILE2,
	FW_TYPE_AUDIO_FILE1,
	FW_TYPE_AUDIO_FILE2,
	FW_TYPE_VIDEO_FILE1, //25
	FW_TYPE_VIDEO_FILE2,
	FW_TYPE_VIDEO,
	FW_TYPE_VIDEO2,
	FW_TYPE_ECPU,
	FW_TYPE_SCS, //30
	FW_TYPE_PCPU,
	FW_TYPE_TEE,
	FW_TYPE_GOLD_KERNEL,
	FW_TYPE_GOLD_RESCUE_DT,
	FW_TYPE_GOLD_RESCUE_ROOTFS, //35
	FW_TYPE_GOLD_AUDIO,
	FW_TYPE_GOLD_TEE,
	FW_TYPE_KERNEL_2,
	FW_TYPE_RESCUE_DT_2,
	FW_TYPE_RESCUE_ROOTFS_2, //40
	FW_TYPE_AUDIO_2,
	FW_TYPE_PCPU_2,
	FW_TYPE_TEE_2,
	FW_TYPE_CONFIG,
	FW_TYPE_UBOOT, //45
	FW_TYPE_BL31,
	FW_TYPE_XEN,
	FW_TYPE_GOLD_BL31,
	FW_TYPE_BL31_2,
	FW_TYPE_RSA_KEY_FW, //50
	FW_TYPE_RSA_KEY_TEE,
	FW_TYPE_FSBL_VM,
	FW_TYPE_GOLD_IMAGE,
	FW_TYPE_BOOT_IMAGE,
	FW_TYPE_BOOT_IMAGE_2, //55
	FW_TYPE_RESCUE_IMAGE,
	FW_TYPE_RESCUE_IMAGE_2,
	FW_TYPE_XEN_2,
    FW_TYPE_TRUST_AREA1,
    FW_TYPE_TRUST_AREA2,
	FW_TYPE_UNKNOWN
} fw_type_code_e;

#define FIRMWARE_DESCRIPTION_TABLE_SIGNATURE	"VERONA__" /* 8 bytes signature. */

#define FW_DESC_TABLE_V1_T_VERSION_1		0x1
#define FW_DESC_TABLE_V1_T_VERSION_11		0x11
#define FW_DESC_TABLE_V1_T_VERSION_21		0x21

#define FW_DESC_TABLE_V2_T_VERSION_2		0x2
#define FW_DESC_TABLE_V2_T_VERSION_12		0x12
#define FW_DESC_TABLE_V2_T_VERSION_22		0x22

inline unsigned long long SIZE_ALIGN_BOUNDARY_LESS(unsigned long long len, unsigned long long size)
{
	return ((len) & ~((size) - 1));
}

inline unsigned long long SIZE_ALIGN_BOUNDARY_MORE(unsigned long long len, unsigned long long size)
{
	return (((len - 1) & ~((size) - 1)) + size);
}
#endif
