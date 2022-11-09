#ifndef _COMPAT_ASM_SIMD_H
#define _COMPAT_ASM_SIMD_H

#if defined(CONFIG_X86_64)
#include <asm/fpu/api.h>
#endif

static __must_check inline bool may_use_simd(void)
{
#if defined(CONFIG_X86_64)
	return irq_fpu_usable();
#elif defined(CONFIG_ARM64) && defined(CONFIG_KERNEL_MODE_NEON)
	return true;
#elif defined(CONFIG_ARM) && defined(CONFIG_KERNEL_MODE_NEON)
	return !in_nmi() && !in_irq() && !in_serving_softirq();
#else
	return false;
#endif
}

#endif
