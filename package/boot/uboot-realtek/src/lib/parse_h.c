
/************************************************************************
 *
 *  parse_h.c
 *
 *  parse defined value in .h file .
 *
 *
 *
 * ######################################################################
 *
 * mips_start_of_legal_notice
 *
 * Copyright (c) 2003 MIPS Technologies, Inc. All rights reserved.
 *
 *
 * Unpublished rights (if any) reserved under the copyright laws of the
 * United States of America and other countries.
 *
 * This code is proprietary to MIPS Technologies, Inc. ("MIPS
 * Technologies"). Any copying, reproducing, modifying or use of this code
 * (in whole or in part) that is not expressly permitted in writing by MIPS
 * Technologies or an authorized third party is strictly prohibited. At a
 * minimum, this code is protected under unfair competition and copyright
 * laws. Violations thereof may result in criminal penalties and fines.
 *
 * MIPS Technologies reserves the right to change this code to improve
 * function, design or otherwise. MIPS Technologies does not assume any
 * liability arising out of the application or use of this code, or of any
 * error or omission in such code. Any warranties, whether express,
 * statutory, implied or otherwise, including but not limited to the implied
 * warranties of merchantability or fitness for a particular purpose, are
 * excluded. Except as expressly provided in any written license agreement
 * from MIPS Technologies or an authorized third party, the furnishing of
 * this code does not give recipient any license to any intellectual
 * property rights, including any patent rights, that cover this code.
 *
 * This code shall not be exported or transferred for the purpose of
 * reexporting in violation of any U.S. or non-U.S. regulation, treaty,
 * Executive Order, law, statute, amendment or supplement thereto.
 *
 * This code constitutes one or more of the following: commercial computer
 * software, commercial computer software documentation or other commercial
 * items. If the user of this code, or any related documentation of any
 * kind, including related technical data or manuals, is an agency,
 * department, or other entity of the United States government
 * ("Government"), the use, duplication, reproduction, release,
 * modification, disclosure, or transfer of this code, or any related
 * documentation of any kind, is restricted in accordance with Federal
 * Acquisition Regulation 12.212 for civilian agencies and Defense Federal
 * Acquisition Regulation Supplement 227.7202 for military agencies. The use
 * of this code by the Government is further restricted in accordance with
 * the terms of the license agreement(s) and/or applicable contract terms
 * and conditions covering this code from MIPS Technologies or an authorized
 * third party.
 *
 *
 * mips_end_of_legal_notice
 *
 *
 ************************************************************************/


/************************************************************************
 *  Include files
 ************************************************************************/
#include <linux/ctype.h>
#include <linux/string.h>
#include <linux/stddef.h>
#include <common.h>
#include <asm/arch/panelConfigParameter.h>

/************************************************************************
 *  Definitions
 ************************************************************************/
/* State event machine states */

#define  ST_START										0
#define  ST_GET_DEFINE									1
#define  ST_GET_STRING									2	// for parse_h

#ifdef PANEL_CONFIG_FROM_FACTORY_PANEL_HEADER
#define  ST_GET_CONFIG_DISPLAY_PORT						2	// for parse_main
#define  ST_GET_CONFIG_DISPLAY_COLOR_BITS				3
#define  ST_GET_CONFIG_DISPLAY_EVEN_RSV1_BIT			4
#define  ST_GET_CONFIG_DISPLAY_ODD_RSV1_BIT				5
#define  ST_GET_CONFIG_DISPLAY_BITMAPPING_TABLE			6
#define  ST_GET_CONFIG_DISPLAY_PORTAB_SWAP				7
#define  ST_GET_CONFIG_DISPLAY_RED_BLUE_SWAP			8
#define  ST_GET_CONFIG_DISPLAY_MSB_LSB_SWAP				9
#define  ST_GET_CONFIG_DISPLAY_SKEW_DATA_OUTPUT 		10
#define  ST_GET_CONFIG_DISPLAY_OUTPUT_INVERSE			11
#define  ST_GET_CONFIG_DISPLAY_VERTICAL_SYNC_NORMAL		12
#define  ST_GET_CONFIG_DISPLAY_HORIZONTAL_SYNC_NORMAL	13
#define  ST_GET_CONFIG_DISPLAY_RATIO_4X3				14
#define  ST_GET_CONFIG_DISPLAY_CLOCK_MAX				15
#define  ST_GET_CONFIG_DISPLAY_CLOCK_MIN				16
#define  ST_GET_CONFIG_DISPLAY_REFRESH_RATE				17
#define  ST_GET_CONFIG_DISPLAY_CLOCK_TYPICAL 			18
#define  ST_GET_CONFIG_DISP_HORIZONTAL_TOTAL 			19
#define  ST_GET_CONFIG_DISP_VERTICAL_TOTAL				20
#define  ST_GET_CONFIG_DISP_HSYNC_WIDTH					21
#define  ST_GET_CONFIG_DISP_VSYNC_LENGTH				22
#define  ST_GET_CONFIG_DISP_DEN_STA_HPOS				23
#define  ST_GET_CONFIG_DISP_DEN_END_HPOS				24
#define  ST_GET_CONFIG_DISP_DEN_STA_VPOS				25
#define  ST_GET_CONFIG_DISP_DEN_END_VPOS				26
#define  ST_GET_CONFIG_DISP_ACT_STA_HPOS				27
#define  ST_GET_CONFIG_DISP_ACT_END_HPOS				28
#define  ST_GET_CONFIG_DISP_ACT_STA_VPOS				29
#define  ST_GET_CONFIG_DISP_ACT_END_VPOS				30
#define  ST_GET_CONFIG_DISP_HSYNC_LASTLINE				31
#define  ST_GET_CONFIG_DISP_DCLK_DELAY					32
#define  ST_GET__CONFIG_DISP_ACT_STA_BIOS				33
#define  ST_GET_CONFIG_DEFAULT_DPLL_M_DIVIDER			34
#define  ST_GET_CONFIG_DEFAULT_DPLL_N_DIVIDER			35
#define  ST_GET_PANEL_TO_LVDS_ON_ms						36
#define	 ST_GET_LVDS_TO_LIGHT_ON_ms						37
#define  ST_GET_LIGHT_TO_LDVS_OFF_ms					38
#define  ST_GET_LVDS_TO_PANEL_OFF_ms					39
#define  ST_GET_PANEL_OFF_TO_ON_ms						40
#define  ST_GET_CONFIG_BACKLIGHT_PWM_FREQ				41
#define  ST_GET_CONFIG_BACKLIGHT_PWM_DUTY				42
#define  ST_GET_FIX_LAST_LINE_ENABLE					43
#define  ST_GET_FIX_LAST_LINE_4X_ENABLE					44
#define  ST_GET_CONFIG_VFLIP_ON							45
#define  ST_GET_CONFIG_PICASSO_CONTROL_ON				46
#define  ST_GET_CONFIG_3D_DISPLAY_SUPPORT_ON			47
#define  ST_GET_CONFIG_3D_LINE_ALTERNATIVE_ON			48
#define  ST_GET_CONFIG_3D_PR_OUTPUT_LR_SWAP				49
#define  ST_GET_CONFIG_3D_SG_OUTPUT_120HZ_ON			50
#define  ST_GET_CONFIG_3D_SG_24HZ_OUTPUT_FHD_ON			51
#define  ST_GET_CONFIG_SCALER_2D_3D_CVT_HWSHIFT_ON		52
#define  ST_GET_CONFIG_LVDS_4_PORTS_INDEX				53
#define  ST_GET_CONFIG_DISP_VERTICAL_TOTAL_50Hz_MIN		54
#define  ST_GET_CONFIG_DISP_VERTICAL_TOTAL_50Hz_MAX		55
#define  ST_GET_CONFIG_DISP_VERTICAL_TOTAL_60Hz_MIN		56
#define  ST_GET_CONFIG_DISP_VERTICAL_TOTAL_60Hz_MAX		57
#define  ST_GET_CONFIG_LVDS_PN_SWAP						58
#define  ST_GET_CONFIG_LVDS_MIRROR						59
#endif

#define  ST_DONE										0xfe
#define  ST_ERROR										0xff

/************************************************************************
 *  Public variables
 ************************************************************************/
extern struct _PANEL_CONFIG_PARAMETER  default_panel_parameter;
extern uchar LVDS_4_PORTS_INDEX;
#ifdef PANEL_CONFIG_FROM_FACTORY_PANEL_HEADER
char panel_file_name[100]={0};
#endif

/************************************************************************
 *  Static variables
 ************************************************************************/

/************************************************************************
 *  Static function prototypes
 ************************************************************************/

/************************************************************************
 *  Implementation : Static functions
 ************************************************************************/

/************************************************************************
 *
 ************************************************************************/
//
static
int tight(char* s)
{
    int i;
    int n = 0;
    for ( i=0; s[i] ; ++i) {
    	if (strncmp(s+i, "//", 2)==0)
    		break;
    	if (strncmp(s+i, "/*", 2)==0)
    		break;
    	if (*(s+i) ==0xd || *(s+i) ==0xa)
    		break;
        if (!isspace(*(s+i)))
            s[n++] = s[i];
    }
    //s[n] = '\0';
    //printf("sn=%s \n",s);//hcy test
    return n;
}
static
int calc(int lv, char op, int rv)
{
    //printf("lv=%d , rv=%d \n", lv ,rv);//hcy test
    if (op == '+') {return lv + rv; }
    if (op == '-') {return lv - rv; }
    if (op == '*') {return lv * rv; }
    if (op == '/') {return lv / rv; }
    return 0;   // crash
}

//
static
int balance(char *s, int L, int R)
{
    int k;
    int c = 1;
    for (k=L+1; k<=R; ++k) {
        if (s[k] == '(') c++;
        if (s[k] == ')') c--;
        if (c == 0) return k;
    }
    return -1;
}
static
char isopera(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

//
static
int findopera(char *s, int L, int R)
{
    int k;
    for (k=L; k<=R; ++k)
        if (isopera(s[k]))
            return k;
    return -1;
}

//
static
int getnum(char *s, int L, int R)
{
    int k;
    int n = 0;
    //printf("L=%d , R=%d \n", L, R);//hcy test
    for (k=L; k<=R; ++k)
        n = n * 10 + s[k] - '0';

    //printf("n=%d \n", n);//hcy test
    return n;
}
static
int f(char *s, int L, int R)
{
    int op;
    if (s[L] == '(')
    {
        op = balance(s, L, R) + 1;
      //  printf("0 op=0x%x \n",op);//hcy test
        if (op > R) return f(s, L+1, op-2);
        return calc(f(s, L+1, op-2), s[op], f(s, op+1, R));
    }

    op = findopera(s, L, R);
    //printf("1 op=0x%x \n",op);//hcy test
    if (op != -1) return calc(f(s, L, op-1), s[op], f(s, op+1, R));
    return getnum(s, L, R);
}
static
int evaluate(char *s)
{
    int length = tight(s);
    //printf("length=%d \n",length);//hcy test
    return f(s, 0, length-1);
}

#ifdef PANEL_CONFIG_FROM_FACTORY_PANEL_HEADER
/************************************************************************
 *                          parse_main
 ************************************************************************/
uint
parse_main(
	char *src_addr,
	uint length )
{
	uint state = ST_START;
	char *fin_addr, *s= NULL;
	char raw0[128]={0},raw1[128]={0} ;
	uint final_num;
	int i;
	unsigned char* p;

	fin_addr = src_addr + length ;
	s= src_addr ;

	while( (state != ST_DONE) && (state != ST_ERROR) && (s < fin_addr) )
	{

		while(isspace(*s) && (s < fin_addr) )
			s++;

		if (s>=fin_addr)
			state = ST_DONE ;

		if (strncmp(s, "/*", 2) == 0) {
			while (( strncmp(s, "*/", 2) != 0) && (s < fin_addr) )
				s++;
			if (s>=fin_addr)
				state = ST_DONE ;
		}

		if (strncmp(s, "//", 2) == 0) {
			while((*s!= 0xd) && (s < fin_addr) )
				s++;
			if (s>=fin_addr)
				state = ST_DONE ;
			else
				state = ST_START;
		}

		if (state >= ST_GET_CONFIG_DISPLAY_PORT) {
			//printf("s=0x%x \n", (int)s);
			final_num = evaluate(s);
			//printf("final_num=%d \n", final_num);
		}

		switch( state )
		{
			case ST_START :
				if ((strncmp(s, "#define ", 8) == 0) || (strncmp(s, "#define	", 8) == 0))
				{
					state = ST_GET_DEFINE;
					s+=8;
				}
				else
					s++;
				break;

			case ST_GET_DEFINE :
				if ((strncmp(s, "CONFIG_DISPLAY_PORT", 19) == 0) &&
					isspace(*(s+19)))
				{
					state = ST_GET_CONFIG_DISPLAY_PORT ;
					s+=19;
				}
				if (strncmp(s, "CONFIG_DISPLAY_COLOR_BITS", 25) == 0) {
					state = ST_GET_CONFIG_DISPLAY_COLOR_BITS ;
					s+=25;
				}
				if (strncmp(s, "CONFIG_DISPLAY_EVEN_RSV1_BIT", 28) == 0) {
					state = ST_GET_CONFIG_DISPLAY_EVEN_RSV1_BIT ;
					s+=28;
				}
				if (strncmp(s, "CONFIG_DISPLAY_ODD_RSV1_BIT", 27) == 0) {
					state = ST_GET_CONFIG_DISPLAY_ODD_RSV1_BIT ;
					s+=27;
				}
				if (strncmp(s, "CONFIG_DISPLAY_BITMAPPING_TABLE", 31) == 0) {
					state = ST_GET_CONFIG_DISPLAY_BITMAPPING_TABLE ;
					s+=31;
				}
				if (strncmp(s, "CONFIG_DISPLAY_PORTAB_SWAP", 25) == 0) {
					state = ST_GET_CONFIG_DISPLAY_PORTAB_SWAP ;
					s+=25;
				}
				if (strncmp(s, "CONFIG_DISPLAY_RED_BLUE_SWAP", 27) == 0) {
					state = ST_GET_CONFIG_DISPLAY_RED_BLUE_SWAP ;
					s+=27;
				}
				if (strncmp(s, "CONFIG_DISPLAY_MSB_LSB_SWAP", 26) == 0) {
					state = ST_GET_CONFIG_DISPLAY_MSB_LSB_SWAP ;
					s+=26;
				}
				if (strncmp(s, "CONFIG_DISPLAY_SKEW_DATA_OUTPUT", 30) == 0) {
					state = ST_GET_CONFIG_DISPLAY_SKEW_DATA_OUTPUT ;
					s+=30;
				}
				if (strncmp(s, "CONFIG_DISPLAY_OUTPUT_INVERSE", 28) == 0) {
					state = ST_GET_CONFIG_DISPLAY_OUTPUT_INVERSE ;
					s+=28;
				}
				if (strncmp(s, "CONFIG_DISPLAY_VERTICAL_SYNC_NORMAL", 34) == 0) {
					state = ST_GET_CONFIG_DISPLAY_VERTICAL_SYNC_NORMAL ;
					s+=34;
				}
				if (strncmp(s, "CONFIG_DISPLAY_HORIZONTAL_SYNC_NORMAL", 36) == 0) {
					state = ST_GET_CONFIG_DISPLAY_HORIZONTAL_SYNC_NORMAL ;
					s+=36;
				}
				if (strncmp(s, "CONFIG_DISPLAY_RATIO_4X3", 23) == 0) {
					state = ST_GET_CONFIG_DISPLAY_RATIO_4X3 ;
					s+=23;
				}
				if (strncmp(s, "CONFIG_DISPLAY_CLOCK_MAX", 23) == 0) {
					state = ST_GET_CONFIG_DISPLAY_CLOCK_MAX ;
					s+=23;
				}
				if (strncmp(s, "CONFIG_DISPLAY_CLOCK_MIN", 23) == 0) {
					state = ST_GET_CONFIG_DISPLAY_CLOCK_MIN ;
					s+=23;
				}
				if (strncmp(s, "CONFIG_DISPLAY_REFRESH_RATE", 26) == 0) {
					state = ST_GET_CONFIG_DISPLAY_REFRESH_RATE ;
					s+=26;
				}
				if (strncmp(s, "CONFIG_DISPLAY_CLOCK_TYPICAL", 27) == 0) {
					state = ST_GET_CONFIG_DISPLAY_CLOCK_TYPICAL ;
					s+=27;
				}
				if (strncmp(s, "CONFIG_DISP_HORIZONTAL_TOTAL", 28) == 0 && strncmp(s, "CONFIG_DISP_HORIZONTAL_TOTAL_", 29) != 0) {
					state = ST_GET_CONFIG_DISP_HORIZONTAL_TOTAL ;
					s+=27;
				}
				if (strncmp(s, "CONFIG_DISP_VERTICAL_TOTAL", 26) == 0 && strncmp(s, "CONFIG_DISP_VERTICAL_TOTAL_", 27) != 0) {
					state = ST_GET_CONFIG_DISP_VERTICAL_TOTAL ;
					s+=25;
				}
				if (strncmp(s, "CONFIG_DISP_HSYNC_WIDTH", 22) == 0) {
					state = ST_GET_CONFIG_DISP_HSYNC_WIDTH ;
					s+=22;
				}
				if (strncmp(s, "CONFIG_DISP_VSYNC_LENGTH", 23) == 0) {
					state = ST_GET_CONFIG_DISP_VSYNC_LENGTH ;
					s+=23;
				}
				if (strncmp(s, "CONFIG_DISP_DEN_STA_HPOS", 23) == 0) {
					state = ST_GET_CONFIG_DISP_DEN_STA_HPOS ;
					s+=23;
				}
				if (strncmp(s, "CONFIG_DISP_DEN_END_HPOS", 23) == 0) {
					state = ST_GET_CONFIG_DISP_DEN_END_HPOS ;
					s+=23;
				}
				if (strncmp(s, "CONFIG_DISP_DEN_STA_VPOS", 23) == 0) {
					state = ST_GET_CONFIG_DISP_DEN_STA_VPOS ;
					s+=23;
				}
				if (strncmp(s, "CONFIG_DISP_DEN_END_VPOS", 23) == 0) {
					state = ST_GET_CONFIG_DISP_DEN_END_VPOS ;
					s+=23;
				}
				if (strncmp(s, "CONFIG_DISP_ACT_STA_HPOS", 23) == 0) {
					state = ST_GET_CONFIG_DISP_ACT_STA_HPOS ;
					s+=23;
				}
				if (strncmp(s, "CONFIG_DISP_ACT_END_HPOS", 23) == 0) {
					state = ST_GET_CONFIG_DISP_ACT_END_HPOS ;
					s+=23;
				}
				if (strncmp(s, "CONFIG_DISP_ACT_STA_VPOS", 23) == 0) {
					state = ST_GET_CONFIG_DISP_ACT_STA_VPOS ;
					s+=23;
				}
				if (strncmp(s, "CONFIG_DISP_ACT_END_VPOS", 23) == 0) {
					state = ST_GET_CONFIG_DISP_ACT_END_VPOS ;
					s+=23;
				}
				if (strncmp(s, "CONFIG_DISP_HSYNC_LASTLINE", 25) == 0) {
					state = ST_GET_CONFIG_DISP_HSYNC_LASTLINE ;
					s+=25;
				}
				if (strncmp(s, "CONFIG_DISP_DCLK_DELAY", 21) == 0) {
					state = ST_GET_CONFIG_DISP_DCLK_DELAY ;
					s+=21;
				}
				if (strncmp(s, "_CONFIG_DISP_ACT_STA_BIOS", 24) == 0) {
					state = ST_GET__CONFIG_DISP_ACT_STA_BIOS ;
					s+=24;
				}
				if (strncmp(s, "CONFIG_DEFAULT_DPLL_M_DIVIDER", 28) == 0) {
					state = ST_GET_CONFIG_DEFAULT_DPLL_M_DIVIDER ;
					s+=28;
				}
				if (strncmp(s, "CONFIG_DEFAULT_DPLL_N_DIVIDER", 28) == 0) {
					state = ST_GET_CONFIG_DEFAULT_DPLL_N_DIVIDER ;
					s+=28;
				}
				if (strncmp(s, "PANEL_TO_LVDS_ON_ms", 19) == 0) {
					state = ST_GET_PANEL_TO_LVDS_ON_ms ;
					s+=19;
				}
				if (strncmp(s, "LVDS_TO_LIGHT_ON_ms", 19) == 0) {
					state = ST_GET_LVDS_TO_LIGHT_ON_ms ;
					s+=19;
				}
				if (strncmp(s, "LIGHT_TO_LDVS_OFF_ms", 20) == 0) {
					state = ST_GET_LIGHT_TO_LDVS_OFF_ms ;
					s+=20;
				}
				if (strncmp(s, "LVDS_TO_PANEL_OFF_ms", 20) == 0) {
					state = ST_GET_LVDS_TO_PANEL_OFF_ms ;
					s+=20;
				}
				if (strncmp(s, "PANEL_OFF_TO_ON_ms", 18) == 0) {
					state = ST_GET_PANEL_OFF_TO_ON_ms ;
					s+=18;
				}
				if (strncmp(s, "CONFIG_BACKLIGHT_PWM_FREQ", 25) == 0) {
					state = ST_GET_CONFIG_BACKLIGHT_PWM_FREQ ;
					s+=25;
				}
				if (strncmp(s, "CONFIG_BACKLIGHT_PWM_DUTY", 25) == 0) {
					state = ST_GET_CONFIG_BACKLIGHT_PWM_DUTY ;
					s+=25;
				}
				if (strncmp(s, "FIX_LAST_LINE_ENABLE", 20) == 0) {
					state = ST_GET_FIX_LAST_LINE_ENABLE ;
					s+=20;
				}
				if (strncmp(s, "FIX_LAST_LINE_4X_ENABLE", 23) == 0) {
					state = ST_GET_FIX_LAST_LINE_4X_ENABLE ;
					s+=23;
				}
				if (strncmp(s, "CONFIG_VFLIP_ON", 15) == 0) {
					state = ST_GET_CONFIG_VFLIP_ON ;
					s+=15;
				}
				if (strncmp(s, "CONFIG_PICASSO_CONTROL_ON", 25) == 0) {
					state = ST_GET_CONFIG_PICASSO_CONTROL_ON ;
					s+=25;
				}
				if (strncmp(s, "CONFIG_3D_DISPLAY_SUPPORT_ON", 28) == 0) {
					state = ST_GET_CONFIG_3D_DISPLAY_SUPPORT_ON ;
					s+=28;
				}
				if (strncmp(s, "CONFIG_3D_LINE_ALTERNATIVE_ON", 29) == 0) {
					state = ST_GET_CONFIG_3D_LINE_ALTERNATIVE_ON ;
					s+=29;
				}
				if (strncmp(s, "CONFIG_3D_PR_OUTPUT_LR_SWAP", 27) == 0) {
					state = ST_GET_CONFIG_3D_PR_OUTPUT_LR_SWAP ;
					s+=27;
				}
				if (strncmp(s, "CONFIG_3D_SG_OUTPUT_120HZ_ON", 28) == 0) {
					state = ST_GET_CONFIG_3D_SG_OUTPUT_120HZ_ON ;
					s+=28;
				}
				if (strncmp(s, "CONFIG_3D_SG_24HZ_OUTPUT_FHD_ON", 31) == 0) {
					state = ST_GET_CONFIG_3D_SG_24HZ_OUTPUT_FHD_ON ;
					s+=31;
				}
				if (strncmp(s, "CONFIG_SCALER_2D_3D_CVT_HWSHIFT_ON", 34) == 0) {
					state = ST_GET_CONFIG_SCALER_2D_3D_CVT_HWSHIFT_ON ;
					s+=34;
				}
				if (strncmp(s, "CONFIG_LVDS_4_PORTS_INDEX", 25) == 0) {
					state = ST_GET_CONFIG_LVDS_4_PORTS_INDEX;
					s+=25;
				}
				if (strncmp(s, "CONFIG_LVDS_PN_SWAP", 19) == 0) {
					state = ST_GET_CONFIG_LVDS_PN_SWAP;
					s+=19;
				}
				if (strncmp(s, "CONFIG_LVDS_MIRROR", 18) == 0) {
					state = ST_GET_CONFIG_LVDS_MIRROR;
					s+=18;
				}
				if (strncmp(s, "CONFIG_DISP_VERTICAL_TOTAL_50Hz_MIN", 35) == 0) {
					state = ST_GET_CONFIG_DISP_VERTICAL_TOTAL_50Hz_MIN;
					s+=35;
				}
				if (strncmp(s, "CONFIG_DISP_VERTICAL_TOTAL_50Hz_MAX", 35) == 0) {
					state = ST_GET_CONFIG_DISP_VERTICAL_TOTAL_50Hz_MAX;
					s+=35;
				}
				if (strncmp(s, "CONFIG_DISP_VERTICAL_TOTAL_60Hz_MIN", 35) == 0) {
					state = ST_GET_CONFIG_DISP_VERTICAL_TOTAL_60Hz_MIN;
					s+=35;
				}
				if (strncmp(s, "CONFIG_DISP_VERTICAL_TOTAL_60Hz_MAX", 35) == 0) {
					state = ST_GET_CONFIG_DISP_VERTICAL_TOTAL_60Hz_MAX;
					s+=35;
				}
				else {
					s++ ;
				}
				break;
			case ST_GET_CONFIG_DISPLAY_PORT:
				default_panel_parameter.iCONFIG_DISPLAY_PORT = (uchar)final_num ;
				printf("set #1 %d \n", default_panel_parameter.iCONFIG_DISPLAY_PORT);
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_DISPLAY_COLOR_BITS:
				default_panel_parameter.iCONFIG_DISPLAY_COLOR_BITS = (uchar)final_num ;
				printf("set #2 %d \n", default_panel_parameter.iCONFIG_DISPLAY_COLOR_BITS);
				s++ ;
				state = ST_START;
				break;
			case ST_GET_CONFIG_DISPLAY_EVEN_RSV1_BIT:
				default_panel_parameter.iCONFIG_DISPLAY_EVEN_RSV1_BIT = (uchar)final_num ;
				printf("set #3 %d \n", default_panel_parameter.iCONFIG_DISPLAY_EVEN_RSV1_BIT);
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_DISPLAY_ODD_RSV1_BIT:
				default_panel_parameter.iCONFIG_DISPLAY_ODD_RSV1_BIT = (uchar)final_num ;
				printf("set #4 %d \n", default_panel_parameter.iCONFIG_DISPLAY_ODD_RSV1_BIT);
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_DISPLAY_BITMAPPING_TABLE:
				default_panel_parameter.iCONFIG_DISPLAY_BITMAPPING_TABLE = (uchar)final_num ;
				printf("set #5 %d \n", default_panel_parameter.iCONFIG_DISPLAY_BITMAPPING_TABLE);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_DISPLAY_PORTAB_SWAP:
				default_panel_parameter.iCONFIG_DISPLAY_PORTAB_SWAP = (uchar)final_num ;
				printf("set #6 %d \n", default_panel_parameter.iCONFIG_DISPLAY_PORTAB_SWAP);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_DISPLAY_RED_BLUE_SWAP:
				default_panel_parameter.iCONFIG_DISPLAY_RED_BLUE_SWAP = (uchar)final_num ;
				printf("set #7 %d \n", default_panel_parameter.iCONFIG_DISPLAY_RED_BLUE_SWAP);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_DISPLAY_MSB_LSB_SWAP:
				default_panel_parameter.iCONFIG_DISPLAY_MSB_LSB_SWAP = (uchar)final_num ;
				printf("set #8 %d \n", default_panel_parameter.iCONFIG_DISPLAY_MSB_LSB_SWAP);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_DISPLAY_SKEW_DATA_OUTPUT:
				default_panel_parameter.iCONFIG_DISPLAY_SKEW_DATA_OUTPUT = (uchar)final_num ;
				printf("set #9 %d \n", default_panel_parameter.iCONFIG_DISPLAY_SKEW_DATA_OUTPUT);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_DISPLAY_OUTPUT_INVERSE:
				default_panel_parameter.iCONFIG_DISPLAY_OUTPUT_INVERSE = (uchar)final_num ;
				printf("set #10 %d \n", default_panel_parameter.iCONFIG_DISPLAY_OUTPUT_INVERSE);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_DISPLAY_VERTICAL_SYNC_NORMAL:
				default_panel_parameter.iCONFIG_DISPLAY_VERTICAL_SYNC_NORMAL = (uchar)final_num ;
				printf("set #11 %d \n", default_panel_parameter.iCONFIG_DISPLAY_VERTICAL_SYNC_NORMAL);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_DISPLAY_HORIZONTAL_SYNC_NORMAL:
				default_panel_parameter.iCONFIG_DISPLAY_HORIZONTAL_SYNC_NORMAL = (uchar)final_num ;
				printf("set #12 %d \n", default_panel_parameter.iCONFIG_DISPLAY_HORIZONTAL_SYNC_NORMAL);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_DISPLAY_RATIO_4X3:
				default_panel_parameter.iCONFIG_DISPLAY_RATIO_4X3 = (uchar)final_num ;
				printf("set #13 %d \n", default_panel_parameter.iCONFIG_DISPLAY_RATIO_4X3);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_DISPLAY_CLOCK_MAX:
				default_panel_parameter.iCONFIG_DISPLAY_CLOCK_MAX = (uchar)final_num ;
				printf("set #14 %d \n", default_panel_parameter.iCONFIG_DISPLAY_CLOCK_MAX);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_DISPLAY_CLOCK_MIN:
				default_panel_parameter.iCONFIG_DISPLAY_CLOCK_MIN = (uchar)final_num ;
				printf("set #15 %d \n", default_panel_parameter.iCONFIG_DISPLAY_CLOCK_MIN);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_DISPLAY_REFRESH_RATE:
				default_panel_parameter.iCONFIG_DISPLAY_REFRESH_RATE = (uchar)final_num ;
				printf("set #16 %d \n", default_panel_parameter.iCONFIG_DISPLAY_REFRESH_RATE);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_DISPLAY_CLOCK_TYPICAL:
				default_panel_parameter.iCONFIG_DISPLAY_CLOCK_TYPICAL = (uint)final_num ;
				printf("set #17 %d \n", default_panel_parameter.iCONFIG_DISPLAY_CLOCK_TYPICAL);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_DISP_HORIZONTAL_TOTAL:
				default_panel_parameter.iCONFIG_DISP_HORIZONTAL_TOTAL = (ushort)final_num ;
				printf("set #18 %d \n", default_panel_parameter.iCONFIG_DISP_HORIZONTAL_TOTAL);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_DISP_VERTICAL_TOTAL:
				default_panel_parameter.iCONFIG_DISP_VERTICAL_TOTAL = (ushort)final_num ;
				printf("set #19 %d \n", default_panel_parameter.iCONFIG_DISP_VERTICAL_TOTAL);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_DISP_HSYNC_WIDTH:
				default_panel_parameter.iCONFIG_DISP_HSYNC_WIDTH = (uchar)final_num;
				printf("set #20 %d \n", default_panel_parameter.iCONFIG_DISP_HSYNC_WIDTH);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_DISP_VSYNC_LENGTH:
				default_panel_parameter.iCONFIG_DISP_VSYNC_LENGTH = (uchar)final_num;
				printf("set #21 %d \n", default_panel_parameter.iCONFIG_DISP_VSYNC_LENGTH);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_DISP_DEN_STA_HPOS:
				default_panel_parameter.iCONFIG_DISP_DEN_STA_HPOS = (uchar)final_num ;
				printf("set #22 %d \n", default_panel_parameter.iCONFIG_DISP_DEN_STA_HPOS);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_DISP_DEN_END_HPOS:
				default_panel_parameter.iCONFIG_DISP_DEN_END_HPOS = (ushort)final_num ;
				printf("set #23 %d \n", default_panel_parameter.iCONFIG_DISP_DEN_END_HPOS);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_DISP_DEN_STA_VPOS:
				default_panel_parameter.iCONFIG_DISP_DEN_STA_VPOS = (ushort)final_num;
				printf("set #24 %d \n", default_panel_parameter.iCONFIG_DISP_DEN_STA_VPOS);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_DISP_DEN_END_VPOS:
				default_panel_parameter.iCONFIG_DISP_DEN_END_VPOS = (ushort)final_num ;
				printf("set #25 %d \n", default_panel_parameter.iCONFIG_DISP_DEN_END_VPOS);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_DISP_ACT_STA_HPOS:
				default_panel_parameter.iCONFIG_DISP_ACT_STA_HPOS = (ushort)final_num ;
				printf("set #26 %d \n", default_panel_parameter.iCONFIG_DISP_ACT_STA_HPOS);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_DISP_ACT_END_HPOS:
				default_panel_parameter.iCONFIG_DISP_ACT_END_HPOS = (ushort)final_num ;
				printf("set #27 %d \n", default_panel_parameter.iCONFIG_DISP_ACT_END_HPOS);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_DISP_ACT_STA_VPOS:
				default_panel_parameter.iCONFIG_DISP_ACT_STA_VPOS = (ushort)final_num ;
				printf("set #28 %d \n", default_panel_parameter.iCONFIG_DISP_ACT_STA_VPOS);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_DISP_ACT_END_VPOS:
				default_panel_parameter.iCONFIG_DISP_ACT_END_VPOS = (ushort)final_num ;
				printf("set #29 %d \n", default_panel_parameter.iCONFIG_DISP_ACT_END_VPOS);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_DISP_HSYNC_LASTLINE:
				default_panel_parameter.iCONFIG_DISP_HSYNC_LASTLINE = (ushort)final_num ;
				printf("set #30 %d \n", default_panel_parameter.iCONFIG_DISP_HSYNC_LASTLINE);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_DISP_DCLK_DELAY:
				default_panel_parameter.iCONFIG_DISP_DCLK_DELAY = (uchar)final_num ;
				printf("set #31 %d \n", default_panel_parameter.iCONFIG_DISP_DCLK_DELAY);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET__CONFIG_DISP_ACT_STA_BIOS:
				default_panel_parameter._iCONFIG_DISP_ACT_STA_BIOS = (uchar)final_num;
				printf("set #32 %d \n", default_panel_parameter._iCONFIG_DISP_ACT_STA_BIOS);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_DEFAULT_DPLL_M_DIVIDER:
				default_panel_parameter.iCONFIG_DEFAULT_DPLL_M_DIVIDER = (uchar)final_num ;
				printf("set #33 %d \n", default_panel_parameter.iCONFIG_DEFAULT_DPLL_M_DIVIDER);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_DEFAULT_DPLL_N_DIVIDER:
				default_panel_parameter.iCONFIG_DEFAULT_DPLL_N_DIVIDER = (uchar)final_num ;
				printf("set #34 %d \n", default_panel_parameter.iCONFIG_DEFAULT_DPLL_N_DIVIDER);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_PANEL_TO_LVDS_ON_ms:
				default_panel_parameter.iPANEL_TO_LVDS_ON_ms = (ushort)final_num ;
				printf("set #35 %d \n", default_panel_parameter.iPANEL_TO_LVDS_ON_ms);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_LVDS_TO_LIGHT_ON_ms:
				default_panel_parameter.iLVDS_TO_LIGHT_ON_ms = (ushort)final_num ;
				printf("set #36 %d \n", default_panel_parameter.iLVDS_TO_LIGHT_ON_ms);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_LIGHT_TO_LDVS_OFF_ms:
				default_panel_parameter.iLIGHT_TO_LDVS_OFF_ms = (ushort)final_num ;
				printf("set #37 %d \n", default_panel_parameter.iLIGHT_TO_LDVS_OFF_ms);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_LVDS_TO_PANEL_OFF_ms:
				default_panel_parameter.iLVDS_TO_PANEL_OFF_ms = (ushort)final_num ;
				printf("set #38 %d \n", default_panel_parameter.iLVDS_TO_PANEL_OFF_ms);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_PANEL_OFF_TO_ON_ms:
				default_panel_parameter.iPANEL_OFF_TO_ON_ms = (ushort)final_num;
				printf("set #39 %d \n", default_panel_parameter.iPANEL_OFF_TO_ON_ms);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_BACKLIGHT_PWM_FREQ:
				default_panel_parameter.iCONFIG_BACKLIGHT_PWM_FREQ = (ushort)final_num ;
				printf("set #40 %d \n", default_panel_parameter.iCONFIG_BACKLIGHT_PWM_FREQ);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_BACKLIGHT_PWM_DUTY:
				default_panel_parameter.iCONFIG_BACKLIGHT_PWM_DUTY = (uchar)final_num;
				printf("set #41 %d \n", default_panel_parameter.iCONFIG_BACKLIGHT_PWM_DUTY);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_FIX_LAST_LINE_ENABLE:
				default_panel_parameter.iFIX_LAST_LINE_ENABLE = (uchar)final_num ;
				printf("set #42 %d \n", default_panel_parameter.iFIX_LAST_LINE_ENABLE);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_FIX_LAST_LINE_4X_ENABLE:
				default_panel_parameter.iFIX_LAST_LINE_4X_ENABLE = (uchar)final_num ;
				printf("set #43 %d \n", default_panel_parameter.iFIX_LAST_LINE_4X_ENABLE);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_VFLIP_ON:
				default_panel_parameter.iVFLIP = (uchar)final_num ;
				printf("set #44 %d \n", default_panel_parameter.iVFLIP);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_PICASSO_CONTROL_ON:
				default_panel_parameter.iPICASSO_CONTROL_ON = (uchar)final_num ;
				printf("set #45 %d \n", default_panel_parameter.iPICASSO_CONTROL_ON);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_3D_DISPLAY_SUPPORT_ON:
				default_panel_parameter.i3D_DISPLAY_SUPPORT = (uchar)final_num ;
				printf("set #46 %d \n", default_panel_parameter.i3D_DISPLAY_SUPPORT);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_3D_LINE_ALTERNATIVE_ON:
				default_panel_parameter.i3D_LINE_ALTERNATIVE_SUPPORT = (uchar)final_num ;
				printf("set #47 %d \n", default_panel_parameter.i3D_LINE_ALTERNATIVE_SUPPORT);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_3D_PR_OUTPUT_LR_SWAP:
				default_panel_parameter.i3D_PR_OUTPUT_LR_SWAP = (uchar)final_num ;
				printf("set #48 %d \n", default_panel_parameter.i3D_PR_OUTPUT_LR_SWAP);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_3D_SG_OUTPUT_120HZ_ON:
				default_panel_parameter.i3D_SG_OUTPUT_120HZ_ON = (uchar)final_num ;
				printf("set #49 %d \n", default_panel_parameter.i3D_SG_OUTPUT_120HZ_ON);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_3D_SG_24HZ_OUTPUT_FHD_ON:
				default_panel_parameter.i3D_SG_24HZ_OUTPUT_FHD_ON = (uchar)final_num ;
				printf("set #50 %d \n", default_panel_parameter.i3D_SG_24HZ_OUTPUT_FHD_ON);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_SCALER_2D_3D_CVT_HWSHIFT_ON:
				default_panel_parameter.iSCALER_2D_3D_CVT_HWSHIFT_ENABLE = (uchar)final_num ;
				printf("set #51 %d \n", default_panel_parameter.iSCALER_2D_3D_CVT_HWSHIFT_ENABLE);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_LVDS_4_PORTS_INDEX:
				default_panel_parameter.iCONFIG_LVDS_4_PORTS_INDEX = (uchar)final_num ;//CONFIG_LVDS_4_PORTS_INDEX ;
				LVDS_4_PORTS_INDEX = default_panel_parameter.iCONFIG_LVDS_4_PORTS_INDEX;
				printf("set #52 %d \n", default_panel_parameter.iCONFIG_LVDS_4_PORTS_INDEX);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_DISP_VERTICAL_TOTAL_50Hz_MIN:
				default_panel_parameter.iCONFIG_DISP_VERTICAL_TOTAL_50Hz_MIN = (ushort)final_num ;
				printf("set #53 %d \n", default_panel_parameter.iCONFIG_DISP_VERTICAL_TOTAL_50Hz_MIN);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_DISP_VERTICAL_TOTAL_50Hz_MAX:
				default_panel_parameter.iCONFIG_DISP_VERTICAL_TOTAL_50Hz_MAX = (ushort)final_num ;
				printf("set #54 %d \n", default_panel_parameter.iCONFIG_DISP_VERTICAL_TOTAL_50Hz_MAX);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_DISP_VERTICAL_TOTAL_60Hz_MIN:
				default_panel_parameter.iCONFIG_DISP_VERTICAL_TOTAL_60Hz_MIN = (ushort)final_num ;
				printf("set #55 %d \n", default_panel_parameter.iCONFIG_DISP_VERTICAL_TOTAL_60Hz_MIN);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_DISP_VERTICAL_TOTAL_60Hz_MAX:
				default_panel_parameter.iCONFIG_DISP_VERTICAL_TOTAL_60Hz_MAX = (ushort)final_num ;
				printf("set #56 %d \n", default_panel_parameter.iCONFIG_DISP_VERTICAL_TOTAL_60Hz_MAX);//hcy test
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_LVDS_PN_SWAP:
				default_panel_parameter.iCONFIG_LVDS_PN_SWAP = (uchar)final_num ;
				printf("set #57 %d \n", default_panel_parameter.iCONFIG_LVDS_PN_SWAP);
				state = ST_START;
				s++ ;
				break;
			case ST_GET_CONFIG_LVDS_MIRROR:
				default_panel_parameter.iCONFIG_LVDS_MIRROR = (uchar)final_num ;
				printf("set #58 %d \n", default_panel_parameter.iCONFIG_LVDS_MIRROR);
				state = ST_START;
				s++ ;
				break;
			default :
				break ;
		}

		if (s>=fin_addr)
			state = ST_DONE ;

	}

	if( state == ST_DONE )
	{
		for (i = 0 ; i < 50  ; i++)
			sprintf( raw0+2*i, "%.2x", *((uchar *)&default_panel_parameter+i));

		for (i = 0 ; i < sizeof(default_panel_parameter) - 50 ; i++)
			sprintf( raw1+2*i, "%.2x", *((uchar *)&default_panel_parameter+50+i));

		//sprintf( raw1+2*(sizeof(default_panel_parameter)-50), "%.2x", *((uchar *)&LVDS_4_PORTS_INDEX));	// to save 4 port index in bootcode
		//LVDS_4_PORTS_INDEX = default_panel_parameter.iCONFIG_LVDS_4_PORTS_INDEX;

		printf("sizeof(default_panel_parameter)=%d \n",sizeof(default_panel_parameter));

		if (1)
		{
			p = (unsigned char*)&default_panel_parameter ;

			for (i=0; i<sizeof(PANEL_CONFIG_PARAMETER); i++) {
				if (i%16 == 0)
					printf("\n %02x",*p++ ) ;
				else
					printf(" %02x",*p++ ) ;
				}
				printf("\n" ) ;
		}



		if (1)
		{
			p = (unsigned char*)raw0  ;

			for (i=0; i<128; i++) {
				if (i%16 == 0)
					printf("\n %02x",*p++ ) ;
				else
					printf(" %02x",*p++ ) ;
			}
			printf("\n" ) ;

		}

		if (1)
		{
			p = (unsigned char*)raw1  ;

			for (i=0; i<128; i++) {
				if (i%16 == 0)
					printf("\n %02x",*p++ ) ;
				else
					printf(" %02x",*p++ ) ;
			}
			printf("\n" ) ;
		}

		if (setenv("panel_parameter_1", raw0)) {
			return 1;
		}

		if (setenv("panel_parameter_2", raw1)) {
			return 1;
		}

		if (*panel_file_name != '\0') {
			printf(" panel_file_name =%s \n", panel_file_name);
			if (setenv("panel_file_name", panel_file_name))
			{
				return 1;
			}
			env_init();
		}

		*panel_file_name = '\0' ;
		return 0;
	}
	else
		return 1;
}
#endif

/************************************************************************
 *                          parse_h
 ************************************************************************/
uint
parse_h(
    char *target_str,
    char *src_addr,
    uint length,
    uint* pRetVal,
    char **pRetaddr)
{
    uint state       = ST_START;
    char   *fin_addr, *s= NULL;
    uint final_num = 0;

    fin_addr = src_addr + length ;
    s= src_addr ;


    while( (state != ST_DONE) && (state != ST_ERROR) && (s < fin_addr) )
    {

    	while(isspace(*s) && (s < fin_addr) )
	    	s++;

	if (s>=fin_addr)
		state = ST_DONE ;


	if (strncmp(s, "/*", 2) == 0) {
		while (( strncmp(s, "*/", 2) != 0) && (s < fin_addr) )
			s++;
		if (s>=fin_addr)
			state = ST_DONE ;
	}

    	if (strncmp(s, "//", 2) == 0) {
	    while((*s!= 0xd) && (s < fin_addr) )
	    	s++;
	    if (s>=fin_addr)
		state = ST_DONE ;
	    else
	    	state = ST_START;
	}

	if (state == ST_GET_STRING)
		final_num = evaluate(s);





        switch( state )
	{
	  case ST_START :


	    if ((strncmp(s, "#define ", 8) == 0) ||
	        (strncmp(s, "#define	", 8) == 0)
	        ) {
		state = ST_GET_DEFINE;
		s+=8;
	    }
	    else
	    	s++;

	    break;

	  case ST_GET_DEFINE :

	    if ((strncmp(s, target_str, strlen(target_str)) == 0) &&
	         isspace(*(s+strlen(target_str)))
	        ) {
	    	state = ST_GET_STRING ;
	    	s+=strlen(target_str);

	    }
	    else
	    	s++ ;

	    break;
	  case ST_GET_STRING :
	    *pRetaddr = s;
	    *pRetVal = final_num;
	    return 0; //ok
	    //return final_num ;//atoi(s) ;

	    //state = ST_START;
	    //s++ ;
	    break;

	  default :
	  	break ;

	}

	if (s>=fin_addr)
		state = ST_DONE ;



    }




    if( state == ST_DONE )
    {
        printf("%s not found \n", target_str) ;
	 return 1; //fail
    }

    return 1; //fail

}



#if 0
uint

parse_layout(
    char *target_str,
    char *src_addr,
    uint length,
    uint* pRetVal,
    char **pRetaddr)
{



}
#endif

