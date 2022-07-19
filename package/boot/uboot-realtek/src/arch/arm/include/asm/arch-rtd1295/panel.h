/************************************************************************
 *
 *  panel.h
 *
 ************************************************************************/

#ifndef PANEL_API_H
#define PANEL_API_H

#define S_OK	0
#define S_FALSE -1
/************************************************************************
 *  Include files
 ************************************************************************/


/************************************************************************
 *  Public functions
 ************************************************************************/

void panel_init_1st(void);
void panel_init_2nd(void);
int panel_init(void);
void disable_force_bg(void);

void PA168_i2c_cmd(void);
typedef enum {
	P_LVDS_2K1K,	//VDS output 2k1k timing only
	P_VBY1_4K2K,	//V By 1	 output 4k2k timing only
	P_LVDS_4K_2K,	//LVDS output 4k2k and 2k1k timing
	P_RESERVED
}PANEL_TYPE;

typedef enum {
	VBY_ONE_PANEL_CHINA_STAR_4K2K_VBY1,
	VBY_ONE_PANEL_CMI_V500_4K2K_VBY1,
	VBY_ONE_PANEL_CMI_60_4K2K_VBY1,
	VBY_ONE_PANEL_RESERVED
}VBY_ONE_PANEL_TYPE; //VBY1 PANEL_CUSTOM_INDEX;

typedef enum {
	P_NO_DEFINED,
	P_M3_CMI_55,	// Millet3 + CMI 4k2k panel
	P_PA168_AU_55,	// PA168 + AU 55" 4k2k panel
	P_M3_CMI_55_P1032
}LVDS_4K2K_PANEL_INDEX; //LVDS 4K2K PANEL_CUSTOM_INDEX;

/************************************************************************
 *  Private functions
 ************************************************************************/

#endif /* #ifndef PANEL_API_H */
