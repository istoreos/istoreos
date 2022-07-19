/************************************************************************
 *  Include Header File
 ************************************************************************/
#ifndef WATCHDOG_API_H
#define WATCHDOG_API_H

#include <asm/arch/io.h>
#include <asm/arch/rbus/misc_reg.h>

//#include <sysdefs.h>
//#include <excep_api.h>
//#include <watchdog_api.h>
//#include <project_config.h>
/************************************************************************
 *  Global variables
 ************************************************************************/


/************************************************************************
 *  Definition
 ************************************************************************/
#define  MIS_TCWCR_REG          0x1801bb00
#define  MIS_TCWTR_REG          0x1801bb04
#define  MIS_TCWNMI_REG         0x1801bb08
#define  MIS_TCWOV_REG          0x1801bb0c


/************************************************************************
 *  Public functions
 ************************************************************************/
#ifdef CONFIG_REALTEK_WATCHDOG

#if 0
UINT32 WATCHDOG_enable( void )
{
      /* watchdog enable */
     REG32(KSEG1(MIS_TCWCR_REG)) = 0x0;
}

UINT32 WATCHDOG_disable( void )
{
      /* watchdog disable */
     REG32(KSEG1(MIS_TCWCR_REG)) = 0xA5;
      /* clear watchdog counter */
     REG32(KSEG1(MIS_TCWTR_REG)) = 0x1;
}

UINT32 WATCHDOG_set(UINT32 micro )
{    /* set overflow count , based on 27 MHz */
     REG32(KSEG1(MIS_TCWOV_REG)) = micro * 27;
}
#endif


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

#if 0
#define WATCHDOG_REBOOT()                             \
do {                                                                       \
    rtd_outl(TCWOV_reg, 0x02000000); /*IC  will be warm reseted after 0.3s elapsed*/  \
    while(1);       \
    //void (*jump)(void) = (void *)Board_FLASH_ADDR_BASE;
    //jump();
} while(0)
#else
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
#endif

#if 0
#define WATCHDOG_STATUS()                             \
        do {                                                                       \
                if((rtd_inl(TCWCR_reg)>>8) & 0xF)   \
                {   \
                    printf("WatchDog Debug    EPC:0x%x,SR:0x%x,Cause:%x,ECause:%x\n",    \
                              rtd_inl(AE_ACPU_EPC_VADDR),   \
                              rtd_inl(AE_ACPU_SR_VADDR),    \
                              rtd_inl(AE_ACPU_CAUSE_VADDR),    \
                              rtd_inl(AE_ACPU_ECAUSE_VADDR));    \
            \
                    pm_printf(pm_wdg_debug2,    \
                              rtd_inl(AE_ACPU_PC0_VADDR),/*? not sure*/      \
                              rtd_inl(AE_ACPU_PC1_VADDR),    \
                              rtd_inl(AE_ACPU_SP_VADDR),    \
                              rtd_inl(AE_ACPU_RA_VADDR));   \
                }   \
                else    \
                {   \
                    /*pm_printf(); */   \
                }   \
          \
                rtd_maskl(TCWCR_reg, ~0xF00, 0xF00);/*clear WDC*/    \
        } while(0)
#endif

#else
#define WATCHDOG_KICK()
#define WATCHDOG_DISABLE()                             \
do {                                                                   \
    rtd_maskl(MIS_TCWCR_reg, ~0xFF, 0xa5);                                \
} while(0)

#define WATCHDOG_ENABLE()
#define WATCHDOG_REBOOT()

#endif

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


