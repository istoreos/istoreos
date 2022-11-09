/*
 * (c) 2009 Magnus Lilja <lilja.magnus@gmail.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __MXC_NAND_H
#define __MXC_NAND_H

/*
 * Register map and bit definitions for the Freescale NAND Flash Controller
 * present in various i.MX devices.
 *
 * MX31 and MX27 have version 1, which has:
 *	4 512-byte main buffers and
 *	4 16-byte spare buffers
 *	to support up to 2K byte pagesize nand.
 *	Reading or writing a 2K page requires 4 FDI/FDO cycles.
 *
 * MX25 and MX35 have version 2.1, and MX51 and MX53 have version 3.2, which
 * have:
 *	8 512-byte main buffers and
 *	8 64-byte spare buffers
 *	to support up to 4K byte pagesize nand.
 *	Reading or writing a 2K or 4K page requires only 1 FDI/FDO cycle.
 *	Also some of registers are moved and/or changed meaning as seen below.
 */
#if defined(CONFIG_MX27) || defined(CONFIG_MX31)
#define MXC_NFC_V1
#define is_mxc_nfc_1()		1
#define is_mxc_nfc_21()		0
#define is_mxc_nfc_32()		0
#elif defined(CONFIG_MX25) || defined(CONFIG_MX35)
#define MXC_NFC_V2_1
#define is_mxc_nfc_1()		0
#define is_mxc_nfc_21()		1
#define is_mxc_nfc_32()		0
#elif defined(CONFIG_MX51) || defined(CONFIG_MX53)
#define MXC_NFC_V3
#define MXC_NFC_V3_2
#define is_mxc_nfc_1()		0
#define is_mxc_nfc_21()		0
#define is_mxc_nfc_32()		1
#else
#error "MXC NFC implementation not supported"
#endif
#define is_mxc_nfc_3()		is_mxc_nfc_32()

#if defined(MXC_NFC_V1)
#define NAND_MXC_NR_BUFS		4
#define NAND_MXC_SPARE_BUF_SIZE		16
#define NAND_MXC_REG_OFFSET		0xe00
#define NAND_MXC_2K_MULTI_CYCLE
#elif defined(MXC_NFC_V2_1) || defined(MXC_NFC_V3_2)
#define NAND_MXC_NR_BUFS		8
#define NAND_MXC_SPARE_BUF_SIZE		64
#define NAND_MXC_REG_OFFSET		0x1e00
#endif

struct mxc_nand_regs {
	u8 main_area[NAND_MXC_NR_BUFS][0x200];
	u8 spare_area[NAND_MXC_NR_BUFS][NAND_MXC_SPARE_BUF_SIZE];
	/*
	 * reserved size is offset of nfc registers
	 * minus total main and spare sizes
	 */
	u8 reserved1[NAND_MXC_REG_OFFSET
		- NAND_MXC_NR_BUFS * (512 + NAND_MXC_SPARE_BUF_SIZE)];
#if defined(MXC_NFC_V1)
	u16 buf_size;
	u16 reserved2;
	u16 buf_addr;
	u16 flash_addr;
	u16 flash_cmd;
	u16 config;
	u16 ecc_status_result;
	u16 rsltmain_area;
	u16 rsltspare_area;
	u16 wrprot;
	u16 unlockstart_blkaddr;
	u16 unlockend_blkaddr;
	u16 nf_wrprst;
	u16 config1;
	u16 config2;
#elif defined(MXC_NFC_V2_1)
	u16 reserved2[2];
	u16 buf_addr;
	u16 flash_addr;
	u16 flash_cmd;
	u16 config;
	u32 ecc_status_result;
	u16 spare_area_size;
	u16 wrprot;
	u16 reserved3[2];
	u16 nf_wrprst;
	u16 config1;
	u16 config2;
	u16 reserved4;
	u16 unlockstart_blkaddr;
	u16 unlockend_blkaddr;
	u16 unlockstart_blkaddr1;
	u16 unlockend_blkaddr1;
	u16 unlockstart_blkaddr2;
	u16 unlockend_blkaddr2;
	u16 unlockstart_blkaddr3;
	u16 unlockend_blkaddr3;
#elif defined(MXC_NFC_V3_2)
	u32 flash_cmd;
	u32 flash_addr[12];
	u32 config1;
	u32 ecc_status_result;
	u32 status_sum;
	u32 launch;
#endif
};

#ifdef MXC_NFC_V3_2
struct mxc_nand_ip_regs {
	u32 wrprot;
	u32 wrprot_unlock_blkaddr[8];
	u32 config2;
	u32 config3;
	u32 ipc;
	u32 err_addr;
	u32 delay_line;
};
#endif

/* Set FCMD to 1, rest to 0 for Command operation */
#define NFC_CMD				0x1

/* Set FADD to 1, rest to 0 for Address operation */
#define NFC_ADDR			0x2

/* Set FDI to 1, rest to 0 for Input operation */
#define NFC_INPUT			0x4

/* Set FDO to 001, rest to 0 for Data Output operation */
#define NFC_OUTPUT			0x8

/* Set FDO to 010, rest to 0 for Read ID operation */
#define NFC_ID				0x10

/* Set FDO to 100, rest to 0 for Read Status operation */
#define NFC_STATUS			0x20

#if defined(MXC_NFC_V1) || defined(MXC_NFC_V2_1)
#define NFC_CONFIG1_SP_EN		(1 << 2)
#define NFC_CONFIG1_RST			(1 << 6)
#define NFC_CONFIG1_CE			(1 << 7)
#elif defined(MXC_NFC_V3_2)
#define NFC_CONFIG1_SP_EN		(1 << 0)
#define NFC_CONFIG1_CE			(1 << 1)
#define NFC_CONFIG1_RST			(1 << 2)
#endif
#define NFC_V1_V2_CONFIG1_ECC_EN	(1 << 3)
#define NFC_V1_V2_CONFIG1_INT_MSK	(1 << 4)
#define NFC_V1_V2_CONFIG1_BIG		(1 << 5)
#define NFC_V2_CONFIG1_ECC_MODE_4	(1 << 0)
#define NFC_V2_CONFIG1_ONE_CYCLE	(1 << 8)
#define NFC_V2_CONFIG1_FP_INT		(1 << 11)
#define NFC_V3_CONFIG1_RBA_MASK		(0x7 << 4)
#define NFC_V3_CONFIG1_RBA(x)		(((x) & 0x7) << 4)

#define NFC_V1_V2_CONFIG2_INT		(1 << 15)
#define NFC_V3_CONFIG2_PS_MASK		(0x3 << 0)
#define NFC_V3_CONFIG2_PS_512		(0 << 0)
#define NFC_V3_CONFIG2_PS_2048		(1 << 0)
#define NFC_V3_CONFIG2_PS_4096		(2 << 0)
#define NFC_V3_CONFIG2_ONE_CYCLE	(1 << 2)
#define NFC_V3_CONFIG2_ECC_EN		(1 << 3)
#define NFC_V3_CONFIG2_2CMD_PHASES	(1 << 4)
#define NFC_V3_CONFIG2_NUM_ADDR_PH0	(1 << 5)
#define NFC_V3_CONFIG2_ECC_MODE_8	(1 << 6)
#define NFC_V3_CONFIG2_PPB_MASK		(0x3 << 7)
#define NFC_V3_CONFIG2_PPB(x)		(((x) & 0x3) << 7)
#define NFC_V3_CONFIG2_EDC_MASK		(0x7 << 9)
#define NFC_V3_CONFIG2_EDC(x)		(((x) & 0x7) << 9)
#define NFC_V3_CONFIG2_NUM_ADDR_PH1(x)	(((x) & 0x3) << 12)
#define NFC_V3_CONFIG2_INT_MSK		(1 << 15)
#define NFC_V3_CONFIG2_SPAS_MASK	(0xff << 16)
#define NFC_V3_CONFIG2_SPAS(x)		(((x) & 0xff) << 16)
#define NFC_V3_CONFIG2_ST_CMD_MASK	(0xff << 24)
#define NFC_V3_CONFIG2_ST_CMD(x)	(((x) & 0xff) << 24)

#define NFC_V3_CONFIG3_ADD_OP(x)	(((x) & 0x3) << 0)
#define NFC_V3_CONFIG3_FW8		(1 << 3)
#define NFC_V3_CONFIG3_SBB(x)		(((x) & 0x7) << 8)
#define NFC_V3_CONFIG3_NUM_OF_DEVS(x)	(((x) & 0x7) << 12)
#define NFC_V3_CONFIG3_RBB_MODE		(1 << 15)
#define NFC_V3_CONFIG3_NO_SDMA		(1 << 20)

#define NFC_V3_WRPROT_UNLOCK		(1 << 2)
#define NFC_V3_WRPROT_BLS_UNLOCK	(2 << 6)

#define NFC_V3_IPC_CREQ			(1 << 0)
#define NFC_V3_IPC_INT			(1 << 31)

#if defined(MXC_NFC_V1) || defined(MXC_NFC_V2_1)
#define operation	config2
#define readnfc		readw
#define writenfc	writew
#elif defined(MXC_NFC_V3_2)
#define operation	launch
#define readnfc		readl
#define writenfc	writel
#endif

#endif /* __MXC_NAND_H */
