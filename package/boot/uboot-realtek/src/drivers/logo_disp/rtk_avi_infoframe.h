#ifndef __RTK_AVI_INFOFRAME_H__
#define __RTK_AVI_INFOFRAME_H__

#define AVI_InfoFrame_DB3_EC201_shift                                                (4)
#define AVI_InfoFrame_DB3_EC201_mask                                                 (0x70)
#define AVI_InfoFrame_DB3_EC201(data)                                                (0x70&((data)<<4))
#define AVI_InfoFrame_DB3_get_EC201(data)                                            ((0x70&(data))>>4)


#define AVI_InfoFrame_DB2_C1C0_shift                                                (6)
#define AVI_InfoFrame_DB2_C1C0_mask                                                 (0xC0)
#define AVI_InfoFrame_DB2_C1C0(data)                                                (0xC0&((data)<<6))
#define AVI_InfoFrame_DB2_get_C1C0(data)                                            ((0xC0&(data))>>6)


#define AVI_InfoFrame_DB2_M1M0_shift                                                (4)
#define AVI_InfoFrame_DB2_M1M0_mask                                                 (0x30)
#define AVI_InfoFrame_DB2_M1M0(data)                                                (0x30&((data)<<4))
#define AVI_InfoFrame_DB2_get_M1M0(data)                                            ((0x30&(data))>>4)


#define AVI_InfoFrame_DB2_R3210_shift                                             	(0)
#define AVI_InfoFrame_DB2_R3210_mask                                                (0x0F)
#define AVI_InfoFrame_DB2_R3210(data)                                               (0x0F&((data)<<0))
#define AVI_InfoFrame_DB2_get_R3210(data)                                           ((0x0F&(data))>>0)


#define AVI_InfoFrame_DB1_Y1Y0_shift                                               	(5)
#define AVI_InfoFrame_DB1_Y1Y0_mask                                                	(0x60)
#define AVI_InfoFrame_DB1_Y1Y0(data)                                              	(0x60&((data)<<5))
#define AVI_InfoFrame_DB1_get_Y1Y0(data)                                           	((0x60&(data))>>5)


#define AVI_InfoFrame_DB1_A0_shift                                               	(4)
#define AVI_InfoFrame_DB1_A0_mask                                                	(0x10)
#define AVI_InfoFrame_DB1_A0(data)                                              	(0x10&((data)<<4))
#define AVI_InfoFrame_DB1_get_A0(data)                                           	((0x10&(data))>>4)


enum AVI_InfoFrame_DB1_A0 {
     NO_ACTIVE_FORMAT_INFO 		= 0,
     ACTIVE_FORMAT_INFO_PRESENT = 1,   
};
	
enum AVI_InfoFrame_DB1_Y1Y0 {
     RGB 			= 0,
     YCBCR422 		= 1,
	 YCBCR444 		= 2,
	 Y1Y0_FUTURE 	= 3,	
};

enum AVI_InfoFrame_DB2_C1C0 {
     C1C0_NODATA 						= 0,
     SMPTE_170M	 						= 1,   
	 ITU_R_709							= 2,	
	 EXTENDED_COLORIMETRY_INFO_VALID	= 3,
};

enum AVI_InfoFrame_DB2_M1M0 {
     M1M0_NODATA 	= 0,
     _4X3	 		= 1,   
	 _16X9			= 2,	
	 M1M0_FUTURE 	= 3,
};

enum AVI_InfoFrame_DB2_R3210 {
     SAME_AS_CODED_FRAME_AR 	= 8,
     _4X3_CENTER 				= 9,   
	 _16X9_CENTER 				= 10,
	 _14X9_CENTER 				= 11,
};

enum AVI_InfoFrame_DB3_EC201 {
     xvYCC601 			 	= 0,
     xvYCC709 			 	= 1,   
	 sYCC601 			 	= 2,
	 AdobeYCC601_sYCC601 	= 3,
	 AdobeRGB 			 	= 4,
};

struct AVI_InfoFrame_Format{
	unsigned int InfoFrame_Type;
	unsigned int InfoFrame_Ver;
	unsigned int Length;
	unsigned int Data_Byte1;
	unsigned int Data_Byte2;
	unsigned int Data_Byte3;
	unsigned int Data_Byte4;
	unsigned int Data_Byte5;
};

#endif/*__RTK_AVI_INFOFRAME_H__*/