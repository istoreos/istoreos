/************************************************************************
 *
 *  logo_disp_api.h
 *
 *  Public header file for logo_disp module
 *
 ************************************************************************/

#ifndef __LOGO_DISP_API_H__
#define __LOGO_DISP_API_H__

/************************************************************************
 *  Include files
 ************************************************************************/
#include <asm/arch/extern_param.h>

#ifdef Logo_Rotate_Interval
#define LOGO_SET_CNT            Logo_Rotate_Interval
#else
#define LOGO_SET_CNT            0x30
#endif

#define LOGO_SET_CNT_ADDR		0x000017f8
#define LOGO_MAGIC_ADDR			0x000017fc

#define LOGO_CHG_CNT_ADDR		0x00001800
#define LOGO_NO_ADDR            0x00001804
#define LOGO1_START_ADDR        0x00001808
#define LOGO1_END_ADDR          0x0000180c
#define LOGO2_START_ADDR        0x00001810
#define LOGO2_END_ADDR          0x00001814
#define LOGO3_START_ADDR        0x00001818
#define LOGO3_END_ADDR          0x0000181c
#define LOGO4_START_ADDR        0x00001820
#define LOGO4_END_ADDR          0x00001824
#define LOGO5_START_ADDR        0x00001828
#define LOGO5_END_ADDR          0x0000182c
#define LOGO6_START_ADDR        0x00001830
#define LOGO6_END_ADDR          0x00001834
#define LOGO7_START_ADDR        0x00001838
#define LOGO7_END_ADDR          0x0000183c
#define LOGO8_START_ADDR        0x00001840
#define LOGO8_END_ADDR          0x00001844

#define LOGO1_CLUT_ADDR			0x00001880
#define LOGO2_CLUT_ADDR			0x00001890
#define LOGO3_CLUT_ADDR			0x000018a0
#define LOGO4_CLUT_ADDR			0x000018b0
#define LOGO5_CLUT_ADDR			0x000018c0
#define LOGO6_CLUT_ADDR			0x000018d0
#define LOGO7_CLUT_ADDR			0x000018e0
#define LOGO8_CLUT_ADDR			0x000018f0

#define LOGO_CLUT_ADDR			LOGO1_CLUT_ADDR


/************************************************************************
 *  Public functions
 ************************************************************************/
int LOGO_DISP_init(void);
void LOGO_DISP_change(uint logo_no);

#endif /* #ifndef __LOGO_DISP_API_H__ */

