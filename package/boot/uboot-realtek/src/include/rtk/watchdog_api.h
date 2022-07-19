/************************************************************************
 *  Include Header File
 ************************************************************************/
#ifndef WATCHDOG_API_H
#define WATCHDOG_API_H

#include <asm/arch/io.h>
#include <asm/arch/rbus/misc_reg.h>

/************************************************************************
 *  Public functions
 ************************************************************************/
#ifdef CONFIG_REALTEK_WATCHDOG

#define WATCHDOG_KICK()                             \
do {                                                                   \
	rtd_outl(TCWTR_reg, 1);                                 \
} while(0)

#define WATCHDOG_DISABLE()                             \
do {                                                                   \
	rtd_maskl(TCWCR_reg, ~0xFF, 0xa5);                                \
} while(0)

#define WATCHDOG_ENABLE()                             \
do {                                                                       \
	rtd_outl(TCWOV_reg, 0x08000000);            /*0.621377*8=4.97  s*/  \
	rtd_outl(TCWNMI_reg, 0x07ff0000);          \
	rtd_maskl(TCWCR_reg, ~0xFF, 0x00);       /*enable WDEN*/  \
} while(0)

// 0100 0000 --> 0.621377
#define WATCHDOG_REBOOT()                             \
do {                                                                       \
	rtd_outl(TCWOV_reg, 0x08000000); /*IC  will be warm reseted after 0.3s elapsed*/  \
	rtd_outl(TCWTR_reg, 1); /*clear watchdog counter to prevent side-effect from current value*/   \
	rtd_maskl(TCWCR_reg, ~0xFF, 0x00);       /*enable WDEN*/  \
	while(1);       \
	/*void (*jump)(void) = (void *)Board_FLASH_ADDR_BASE;*/  \
	/*jump();*/  \
} while(0)

#else //CONFIG_REALTEK_WATCHDOG

#define WATCHDOG_KICK()
#define WATCHDOG_DISABLE()                             \
do {                                                                   \
	rtd_maskl(TCWCR_reg, ~0xFF, 0xa5);                                \
} while(0)

#define WATCHDOG_ENABLE()
#define WATCHDOG_REBOOT()

#endif //CONFIG_REALTEK_WATCHDOG

/************************************************************************
 *
 *                          WATCHDOG_init
 *  Description :
 *  -------------
 *  Initialize the WATCHDOG device
 *
 *
 *  Parameters :
 *  ------------
 *  -
 *
 *
 *  Return values :
 *  ---------------
 *  'OK'(=0)
 *
 ************************************************************************/

#endif /* #ifndef WATCHDOG_API_H */


