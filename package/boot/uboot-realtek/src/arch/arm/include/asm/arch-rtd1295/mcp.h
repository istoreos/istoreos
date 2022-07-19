/************************************************************************
 *
 *  mcp.h
 *
 *  Public header file for CP module
 *
 ************************************************************************/

#ifndef __MCP_H__
#define __MCP_H__

#include "system.h"
/************************************************************************
 *  Memory usage
 ************************************************************************/
#define SECURE_IMAGE2HASH_BUF		(UBOOT_SECURE_MCP_MEMORY_ADDR)
#define SECURE_SIGN2HASH_BUF		(UBOOT_SECURE_MCP_MEMORY_ADDR + 0x200)
#define SECURE_SIGN2HASH_TEMP_BUF   	(UBOOT_SECURE_MCP_MEMORY_ADDR + 0x800)
#define SECURE_MAX_ALLOC_SIZE		(UBOOT_SECURE_MCP_MEMORY_SIZE)	// (32UL << 20)
#define SECURE_MALLOC_BASE 		SECURE_SIGN2HASH_TEMP_BUF

/************************************************************************
 *  Definition
 ************************************************************************/
#define  DEFAULT_KEY_PTR			NULL // Kh_key_default
#define  CP_REG_BASE		0x98015000
#define  TP_REG_BASE            0x98014000
#define  RSA_REG_BASE		0x9804cf00
#define  CP_OTP_LOAD		(CP_REG_BASE + 0x19c)

//For SCPU
/* MCP General Registers */
#define  MCP_CTRL		(CP_REG_BASE + 0x100)
#define  MCP_STATUS		(CP_REG_BASE + 0x104)
#define  MCP_EN			(CP_REG_BASE + 0x108)

/* MCP Ring-Buffer Registers */
#define  MCP_BASE		(CP_REG_BASE + 0x10c)
#define  MCP_LIMIT		(CP_REG_BASE + 0x110)
#define  MCP_RDPTR		(CP_REG_BASE + 0x114)
#define  MCP_WRPTR		(CP_REG_BASE + 0x118)
#define  MCP_DES_COUNT		(CP_REG_BASE + 0x134)
#define  MCP_DES_COMPARE	(CP_REG_BASE + 0x138)

/* MCP Ini_Key Registers */
#define  MCP_DES_INI_KEY	(CP_REG_BASE + 0x11C)
#define  MCP_AES_INI_KEY	(CP_REG_BASE + 0x124)

//For SWC
/* MCP General Registers */
#define  K_MCP_CTRL             (CP_REG_BASE + 0x900)
#define  K_MCP_STATUS       	(CP_REG_BASE + 0x904)
#define  K_MCP_EN               (CP_REG_BASE + 0x908)

/* MCP Ring-Buffer Registers */
#define  K_MCP_BASE             (CP_REG_BASE + 0x90c)
#define  K_MCP_LIMIT            (CP_REG_BASE + 0x910)
#define  K_MCP_RDPTR            (CP_REG_BASE + 0x914)
#define  K_MCP_WRPTR            (CP_REG_BASE + 0x918)
#define  K_MCP_DES_COUNT        (CP_REG_BASE + 0x934)
#define  K_MCP_DES_COMPARE      (CP_REG_BASE + 0x938)

/* MCP Ini_Key Registers */
#define  K_MCP_DES_INI_KEY      (CP_REG_BASE + 0x91C)
#define  K_MCP_AES_INI_KEY      (CP_REG_BASE + 0x924)

/* FIXME : change to dynamic address */
#define CP_DESCRIPTOR_ADDR		(0x013fff00)	/* CP descriptor address */
#define CP_DSCPT_POOL_BASE_ADDR		(0x01400000)	/* CP descriptor pool base address */
#define CP_OUT_BASE_ADDR		(0x01500000)	/* CP descriptor pool base address */
#define CP_DSCPT_POOL_SIZE		0x800		/* CP descriptor pool size */
#define CP_DSCPT_POOL_MAX_ADDR		(CP_DSCPT_POOL_BASE_ADDR + CP_DSCPT_POOL_SIZE)

/* RSA */
#define RSA_CTRL3		(RSA_REG_BASE + 0x08)
#define RSA_SEC_CTRL1		(RSA_REG_BASE + 0x80)
#define RSA_SEC_CTRL3		(RSA_REG_BASE + 0x84)
#define RSA_SEC_CTRL4		(RSA_REG_BASE + 0x88)

typedef struct mcp_descriptor
{
    unsigned int mode;
    unsigned int key[6];
    unsigned int ini_key[4];
    unsigned int src_addr;
    unsigned int dst_addr;
    unsigned int length;
} t_mcp_descriptor ;

/* 128 bit of AES_H initial vector(h0) */
#define AES_H_IV_0		        0x2dc2df39
#define AES_H_IV_1		        0x420321d0
#define AES_H_IV_2		        0xcef1fe23
#define AES_H_IV_3		        0x74029d95

/* 160 bit SHA1 initial vector */
#ifndef SHA1_IV_0
    #define SHA1_IV_0		        0x67452301
    #define SHA1_IV_1		        0xEFCDAB89
    #define SHA1_IV_2		        0x98BADCFE
    #define SHA1_IV_3		        0x10325476
    #define SHA1_IV_4		        0xC3D2E1F0
#endif

#define SHA1_SIZE			20

/* 256 bit SHA256 initial vector */
#define SHA256_H0					0x6A09E667
#define SHA256_H1					0xBB67AE85
#define SHA256_H2					0x3C6EF372
#define SHA256_H3					0xA54FF53A
#define SHA256_H4					0x510E527F
#define SHA256_H5					0x9B05688C
#define SHA256_H6					0x1F83D9AB
#define SHA256_H7					0x5BE0CD19


#define SHA256_SIZE					32

#define SECURE_KH_KEY_STR           "ad0d8175a0d732c0e56ef350c53ce48b"
#define SECURE_KH_KEY0 				0xad0d8175
#define SECURE_KH_KEY1 				0xa0d732c0
#define SECURE_KH_KEY2 				0xe56ef350
#define SECURE_KH_KEY3 				0xc53ce48b

#define NP_INV32_LENGTH			    4   /* np_inv length (32bits) */
#define RSA_SIGNATURE_LENGTH		256

#define PHYS(addr)              	((uint)(addr))

#define AES_KEY_SIZE                    16
#define RSA_KEY_SIZE                    256

//SRAM key position
#define KEY_SRAM_ADDR                   (0x80006A00)
#define KC_P_SRAM_ADDR                  (KEY_SRAM_ADDR)
#define KH_P_SRAM_ADDR                  (KC_P_SRAM_ADDR + AES_KEY_SIZE)
#define KX_P_SRAM_ADDR                  (KH_P_SRAM_ADDR + AES_KEY_SIZE)
#define KSS_P_SRAM_ADDR                 (KX_P_SRAM_ADDR + AES_KEY_SIZE)
#define KHT_P_SRAM_ADDR                 (KSS_P_SRAM_ADDR + AES_KEY_SIZE)
#define KIMG_SRAM_ADDR                  (KHT_P_SRAM_ADDR + AES_KEY_SIZE)
#define RSA_KEY_FW_SRAM_ADDR            (KIMG_SRAM_ADDR + AES_KEY_SIZE)
#define RSA_KEY_TEE_SRAM_ADDR           (RSA_KEY_FW_SRAM_ADDR + RSA_KEY_SIZE)

//#define MCP_DEBUG
/************************************************************************
 *  Public functions
 ************************************************************************/
int AES_CBC_decrypt(unsigned char * src_addr, unsigned int length, unsigned char * dst_addr, unsigned int key[4]);
int AES_CBC_encrypt(unsigned char * src_addr, unsigned int length, unsigned char * dst_addr, unsigned int key[4]);
int AES_ECB_decrypt(unsigned char * src_addr, unsigned int length, unsigned char * dst_addr, unsigned int key[4]);
int AES_ECB_encrypt(unsigned char * src_addr, unsigned int length, unsigned char * dst_addr, unsigned int key[4]);
int AES_hash_one(unsigned char * src_addr, unsigned int length, unsigned char * dst_addr);
int AES_hash(unsigned char * src_addr, unsigned int length, unsigned char * dst_addr, unsigned int block_size);
int SHA1_hash(unsigned char * src_addr, unsigned int length, unsigned char * dst_addr, unsigned int iv[5]);
int SHA256_hash(unsigned char * src_addr, unsigned int length, unsigned char *dst_addr, unsigned int iv[8]);
int Verify_SHA256_hash( unsigned char * src_addr, unsigned int length, unsigned char * ref_sha256, unsigned int do_recovery, unsigned char * rsa_key_addr);
void rtk_hexdump( const char * str, unsigned char * pcBuf, unsigned int length );
void reverse_signature( unsigned char * pSignature );
void copy_memory(void *dst, void *src, unsigned int size);
void set_memory_mcp(void *dst, unsigned char value, unsigned int size);
int swap_endian(unsigned int input);

#endif // __MCP_H__
