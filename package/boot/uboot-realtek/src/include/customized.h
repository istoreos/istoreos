#ifndef __CUSTOMIZED_H_
#define __CUSTOMIZED_H_

#include <asm/arch/rbus/iso_reg.h>

#ifdef CONFIG_CUSTOMIZE_BOOTFLOW_1
#define ACPU_BOOT_NOTIFY       (ISO_NORST_0)
int customize_check_normal_boot(void);
#else // CONFIG_CUSTOMIZE_BOOTFLOW_1
int customize_check_normal_boot(void) {return 1;}
#endif

#endif //__CUSTOMIZED_H_
