#ifndef __RTKEMMC_GENERIC_H__
#define __RTKEMMC_GENERIC_H__

#include <asm/arch/rtkemmc.h>
int board_mmc_init(bd_t * bis);
int bringup_mmc_driver( void );

#ifdef __RTKEMMC_GENERIC_C__
	#define EXTERN_CALL
#else
	#define EXTERN_CALL extern
#endif

#endif // end of CONFIG_GENERIC_EMMC
