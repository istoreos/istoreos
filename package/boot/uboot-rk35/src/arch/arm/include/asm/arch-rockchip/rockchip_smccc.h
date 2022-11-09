/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#ifndef __ROCKCHIP_SMCCC_H__
#define __ROCKCHIP_SMCCC_H__

#include <linux/arm-smccc.h>

/* Rockchip platform SiP call ID */
#define SIP_ATF_VERSION			0x82000001
#define SIP_ACCESS_REG			0x82000002
#define SIP_SUSPEND_MODE		0x82000003
#define SIP_PENDING_CPUS		0x82000004
#define SIP_UARTDBG_CFG			0x82000005
#define SIP_UARTDBG_CFG64		0xc2000005
#define SIP_MCU_EL3FIQ_CFG		0x82000006
#define SIP_ACCESS_CHIP_STATE64		0xc2000006
#define SIP_SECURE_MEM_CONFIG		0x82000007
#define SIP_ACCESS_CHIP_EXTRA_STATE64	0xc2000007
#define SIP_DRAM_CONFIG			0x82000008
#define SIP_SHARE_MEM			0x82000009
#define SIP_SIP_VERSION			0x8200000a
#define SIP_REMOTECTL_CFG		0x8200000b
#define SIP_VPU_RESET			0x8200000c
#define SIP_SOC_BUS_DIV			0x8200000d
#define SIP_LAST_LOG			0x8200000e
#define SIP_AMP_CFG			0x82000022
#define SIP_HDCP_CONFIG			0x82000025

#define ROCKCHIP_SIP_CONFIG_DRAM_INIT		0x00
#define ROCKCHIP_SIP_CONFIG_DRAM_SET_RATE	0x01
#define ROCKCHIP_SIP_CONFIG_DRAM_ROUND_RATE	0x02
#define ROCKCHIP_SIP_CONFIG_DRAM_SET_AT_SR	0x03
#define ROCKCHIP_SIP_CONFIG_DRAM_GET_BW		0x04
#define ROCKCHIP_SIP_CONFIG_DRAM_GET_RATE	0x05
#define ROCKCHIP_SIP_CONFIG_DRAM_CLR_IRQ	0x06
#define ROCKCHIP_SIP_CONFIG_DRAM_SET_PARAM	0x07
#define ROCKCHIP_SIP_CONFIG_DRAM_GET_VERSION	0x08
#define ROCKCHIP_SIP_CONFIG_DRAM_POST_SET_RATE	0x09
#define ROCKCHIP_SIP_CONFIG_DRAM_SET_NOC_RL	0x0a
#define ROCKCHIP_SIP_CONFIG_DRAM_DEBUG		0x0b
#define ROCKCHIP_SIP_CONFIG_DRAM_MCU_START	0x0c
#define ROCKCHIP_SIP_CONFIG_DRAM_ECC		0x0d
#define ROCKCHIP_SIP_CONFIG_DRAM_GET_FREQ_INFO	0x0e
#define ROCKCHIP_SIP_CONFIG_DRAM_FSP_INIT	0x0f

/* Rockchip Sip version */
#define SIP_IMPLEMENT_V1                (1)
#define SIP_IMPLEMENT_V2                (2)

/* Error return code */
#define IS_SIP_ERROR(x)			(!!(x))

#define SIP_RET_SUCCESS			0
#define SIP_RET_SMC_UNKNOWN		-1
#define SIP_RET_NOT_SUPPORTED		-2
#define SIP_RET_INVALID_PARAMS		-3
#define SIP_RET_INVALID_ADDRESS		-4
#define SIP_RET_DENIED			-5

/* SIP_ACCESS_REG: read or write */
#define SECURE_REG_RD			0x0
#define SECURE_REG_WR			0x1

/* SIP_AMP_CFG */
#define AMP_PE_STATE			0x0
#define AMP_BOOT_ARG01			0x1
#define AMP_BOOT_ARG23			0x2

/* Share mem page types */
typedef enum {
	SHARE_PAGE_TYPE_INVALID = 0,
	SHARE_PAGE_TYPE_UARTDBG,
	SHARE_PAGE_TYPE_DDR,
	SHARE_PAGE_TYPE_DDRDBG,
	SHARE_PAGE_TYPE_DDRECC,
	SHARE_PAGE_TYPE_DDRFSP,
	SHARE_PAGE_TYPE_DDR_ADDRMAP,
	SHARE_PAGE_TYPE_LAST_LOG,
	SHARE_PAGE_TYPE_HDCP,
	SHARE_PAGE_TYPE_MAX,
} share_page_type_t;

/* hdcp config func */
typedef enum {
	HDCP_FUNC_STORAGE_ENCRYPT = 1,
	HDCP_FUNC_KEY_DECRYPT,
	HDCP_FUNC_KEY_LOAD,
	HDCP_FUNC_ENCRYPT_MODE
} sip_hdcp_func_t;

/*
 * sip_smc_set_suspend_mode() - Set U-Boot system suspend state before trap to trust.
 *
 * see kernel-4.4: drivers/soc/rockchip/rockchip_pm_config.c
 */
int sip_smc_set_suspend_mode(unsigned long ctrl,
			     unsigned long config1,
			     unsigned long config2);

/*
 * sip_smc_amp_cfg() - config AMP
 */
int sip_smc_amp_cfg(unsigned long func, unsigned long arg0, unsigned long arg1,
		    unsigned long arg2);

/*
 * sip_smc_dram() - Set dram configure for trust.
 *
 * see: ./drivers/ram/rockchip/rockchip_dmc.c
 */
struct arm_smccc_res sip_smc_dram(unsigned long arg0,
				  unsigned long arg1,
				  unsigned long arg2);

/*
 * sip_smc_request_share_mem() - Request share memory from trust.
 *
 * @page_num:	page numbers
 * @page_type:  page type, see: share_page_type_t
 *
 * @return arm_smccc_res structure, res.a0 equals 0 on success(res.a1 contains
 *  share memory base address), otherwise failed.
 */
struct arm_smccc_res sip_smc_request_share_mem(unsigned long page_num,
					       share_page_type_t page_type);

/*
 * sip_smc_secure_reg_read() - Read secure info(ddr/register...) from trust.
 *
 * @addr_phy:	address to read
 *
 * @return arm_smccc_res structure, res.a0 equals 0 on success(res.a1 contains
 *  valid data), otherwise failed.
 */
struct arm_smccc_res sip_smc_secure_reg_read(unsigned long addr_phy);

/*
 * sip_smc_secure_reg_write() - Write data to trust secure info(ddr/register...).
 *
 * @addr_phy:	address to write
 * @val:	value to write
 *
 * @return 0 on success, otherwise failed.
 */
int sip_smc_secure_reg_write(unsigned long addr_phy, unsigned long val);

/*
 * sip_smc_set_sip_version() - Set sip version to trust.
 *
 * @return 0 on success, otherwise failed.
 */
int sip_smc_set_sip_version(unsigned long version);

/*
 * sip_smc_get_sip_version() - Get sip version to trust.
 *
 * @return arm_smccc_res structure, res.a0 equals 0 on success(res.a1 contains
 *  sip version), otherwise failed.
 */
struct arm_smccc_res sip_smc_get_sip_version(void);

/*
 * sip_smc_hdcp_config() - handle hdcp.
 *
 * @return  0 on success, otherwise failed.
 */
int sip_smc_hdcp_config(unsigned long func,
			unsigned long arg1, unsigned long arg2);

/*
 * psci_cpu_on() - Standard ARM PSCI cpu on call.
 *
 * @cpuid:		cpu id
 * @entry_point:	boot entry point
 *
 * @return 0 on success, otherwise failed.
 */
int psci_cpu_on(unsigned long cpuid, unsigned long entry_point);

#ifdef CONFIG_ARM_CPU_SUSPEND
/*
 * psci_system_suspend() - Standard ARM PSCI system suspend call.
 *
 * @unused:		unused now, always 0 recommend
 *
 * @return 0 on success, otherwise failed.
 */
int psci_system_suspend(unsigned long unused);
#endif

#endif
