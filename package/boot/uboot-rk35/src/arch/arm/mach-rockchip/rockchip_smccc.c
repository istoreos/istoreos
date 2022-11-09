/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <asm/arch-rockchip/rockchip_smccc.h>
#include <asm/io.h>
#include <asm/psci.h>
#include <asm/suspend.h>
#include <linux/io.h>

#ifdef CONFIG_ARM64
#define ARM_PSCI_1_0_SYSTEM_SUSPEND	ARM_PSCI_1_0_FN64_SYSTEM_SUSPEND
#define ARM_PSCI_0_2_CPU_ON		ARM_PSCI_0_2_FN64_CPU_ON
#else
#define ARM_PSCI_1_0_SYSTEM_SUSPEND	ARM_PSCI_1_0_FN_SYSTEM_SUSPEND
#define ARM_PSCI_0_2_CPU_ON		ARM_PSCI_0_2_FN_CPU_ON
#endif

#define SIZE_PAGE(n)	((n) << 12)

static struct arm_smccc_res __invoke_sip_fn_smc(unsigned long function_id,
						unsigned long arg0,
						unsigned long arg1,
						unsigned long arg2)
{
	struct arm_smccc_res res;

	arm_smccc_smc(function_id, arg0, arg1, arg2, 0, 0, 0, 0, &res);
	return res;
}

int psci_cpu_on(unsigned long cpuid, unsigned long entry_point)
{
	struct arm_smccc_res res;

	res = __invoke_sip_fn_smc(ARM_PSCI_0_2_CPU_ON, cpuid, entry_point, 0);

	return res.a0;
}

#ifdef CONFIG_ARM_CPU_SUSPEND
int psci_system_suspend(unsigned long unused)
{
	struct arm_smccc_res res;

	res = __invoke_sip_fn_smc(ARM_PSCI_1_0_SYSTEM_SUSPEND,
				  virt_to_phys(cpu_resume), 0, 0);
	return res.a0;
}
#endif

int sip_smc_set_suspend_mode(unsigned long ctrl,
			     unsigned long config1,
			     unsigned long config2)
{
	struct arm_smccc_res res;

	res = __invoke_sip_fn_smc(SIP_SUSPEND_MODE, ctrl, config1, config2);
	return res.a0;
}

int sip_smc_amp_cfg(unsigned long func, unsigned long arg0, unsigned long arg1,
		    unsigned long arg2)
{
	struct arm_smccc_res res;

	arm_smccc_smc(SIP_AMP_CFG, func, arg0, arg1, arg2, 0, 0, 0, &res);
	return res.a0;
}

struct arm_smccc_res sip_smc_dram(unsigned long arg0,
				  unsigned long arg1,
				  unsigned long arg2)
{
	return __invoke_sip_fn_smc(SIP_DRAM_CONFIG, arg0, arg1, arg2);
}

struct arm_smccc_res sip_smc_request_share_mem(unsigned long page_num,
					       share_page_type_t page_type)
{
	struct arm_smccc_res res;
	unsigned long share_mem_phy;

	res = __invoke_sip_fn_smc(SIP_SHARE_MEM, page_num, page_type, 0);
	if (IS_SIP_ERROR(res.a0))
		goto error;

	share_mem_phy = res.a1;
	res.a1 = (unsigned long)ioremap(share_mem_phy, SIZE_PAGE(page_num));

error:
	return res;
}

struct arm_smccc_res sip_smc_secure_reg_read(unsigned long addr_phy)
{
	struct arm_smccc_res res;

	res = __invoke_sip_fn_smc(SIP_ACCESS_REG, 0, addr_phy, SECURE_REG_RD);
	return res;
}

int sip_smc_secure_reg_write(unsigned long addr_phy, unsigned long val)
{
	struct arm_smccc_res res;

	res = __invoke_sip_fn_smc(SIP_ACCESS_REG, val, addr_phy, SECURE_REG_WR);
	return res.a0;
}

int sip_smc_hdcp_config(unsigned long func, unsigned long arg1, unsigned long arg2)
{
	struct arm_smccc_res res;

	res = __invoke_sip_fn_smc(SIP_HDCP_CONFIG, func, arg1, arg2);
	return res.a0;
}

struct arm_smccc_res sip_smc_get_sip_version(void)
{
	return __invoke_sip_fn_smc(SIP_SIP_VERSION, 0, 0, 0);
}

/*
 * OP-TEE works both for kernel 3.10 and 4.4, and these two kernels have
 * different sip implement that 3.10 uses SIP_IMPLEMENT_V1 and 4.4 uses
 * SIP_IMPLEMENT_V2. So we should tell OP-TEE the current rockchip sip
 * version(default SIP_IMPLEMENT_V1) before use.
 */
int sip_smc_set_sip_version(unsigned long version)
{
	struct arm_smccc_res res;

	res = __invoke_sip_fn_smc(SIP_SIP_VERSION, version, SECURE_REG_WR, 0);
	if (IS_SIP_ERROR(res.a0)) {
		printf("%s: set rockchip sip version v%ld failed\n",
		       __func__, version);
		return res.a0;
	}

	return 0;
}
