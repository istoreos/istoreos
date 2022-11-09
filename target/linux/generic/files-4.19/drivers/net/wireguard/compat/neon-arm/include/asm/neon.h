#ifndef _ARCH_ARM_ASM_NEON
#define _ARCH_ARM_ASM_NEON
#define kernel_neon_begin() \
	BUILD_BUG_ON_MSG(1, "This kernel does not support ARM NEON")
#define kernel_neon_end() \
	BUILD_BUG_ON_MSG(1, "This kernel does not support ARM NEON")
#endif
