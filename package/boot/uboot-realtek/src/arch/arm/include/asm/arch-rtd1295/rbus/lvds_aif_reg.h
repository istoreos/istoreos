/**************************************************************
// Spec Version                  : 1.0.6
// Parser Version                : DVR_Parser_6.11(120105)
// CModelGen Version             : 5.1 2012.01.05
// Naming Rule                   :  Register_Name
// Naming Rule                   : Module_Register_Name_reg
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2015/7/13 15:33:15
***************************************************************/


#ifndef _COMBO_AIF_REG_H_INCLUDED_
#define _COMBO_AIF_REG_H_INCLUDED_
#ifdef  _COMBO_AIF_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     REG_EDP_DBG_SEL:2;
unsigned int     reserved_1:2;
unsigned int     REG_ISO_EN:1;
unsigned int     REG_EDP_MODE:1;
unsigned int     REG_TSTA_SEL:4;
unsigned int     REG_TSTD_SEL:4;
unsigned int     reserved_2:1;
unsigned int     REG_IBHN_SEL:3;
unsigned int     reserved_3:1;
unsigned int     REG_IBHX_SEL:3;
unsigned int     reserved_4:7;
unsigned int     REG_BIAS_POW:1;
}AIF_MISC;

typedef struct 
{
unsigned int     REG_EDP_SLEW:8;
unsigned int     REG_EDP_SHAPE:8;
unsigned int     reserved_0:12;
unsigned int     REG_EDP_EN:4;
}AIF_EDP_1;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     REG_EDP_EMPH_EN:4;
unsigned int     REG_EDP_EMP2X_SEL:4;
unsigned int     REG_EDP_EMPH_SEL:16;
}AIF_EDP_2;

typedef struct 
{
unsigned int     REG_EDP_IBNX_SEL:1;
unsigned int     reserved_0:1;
unsigned int     REG_VG_SEL:2;
unsigned int     REG_EDP_DRV2X_SEL:4;
unsigned int     REG_EDP_PREDRV_SEL:8;
unsigned int     REG_EDP_DRV_SEL:16;
}AIF_EDP_3;

typedef struct 
{
unsigned int     REG_EDP_R50_SEL:16;
unsigned int     REG_EDP_RESERVED:16;
}AIF_EDP_4;

typedef struct 
{
unsigned int     reserved_0:5;
unsigned int     REG_VCM_SEL:3;
unsigned int     reserved_1:3;
unsigned int     REG_LVDS_TSTSEL:1;
unsigned int     reserved_2:2;
unsigned int     REG_LVDS_SER_SEL:2;
unsigned int     reserved_3:3;
unsigned int     REG_LVDS_DLAG:5;
unsigned int     reserved_4:3;
unsigned int     REG_LVDS_POW:5;
}AIF_LVDS_1;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     REG_IBTX_SEL:2;
unsigned int     reserved_1:3;
unsigned int     REG_LVDS_RTONL:5;
unsigned int     REG_LVDS_DRV_SEL:20;
}AIF_LVDS_2;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     REG_LVDS_SLEW:10;
unsigned int     reserved_1:1;
unsigned int     REG_LVDS_SHAPE:15;
}AIF_LVDS_3;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     REG_LVDS_PRE_SR_SEL:1;
unsigned int     REG_LVDS_PRE_EN:1;
unsigned int     REG_LVDS_PRE_SEL:20;
}AIF_LVDS_4;

typedef struct 
{
unsigned int     dummy_lvds:32;
}DUMMY_LVDS;

typedef struct 
{
unsigned int     dummy_edp:32;
}DUMMY_EDP;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     YUV422_mode:1;
unsigned int     ColorTrans_EN:1;
}CT_CTRL;

typedef struct 
{
unsigned int     ColorTrans_C1:16;
unsigned int     ColorTrans_C2:16;
}CT_COE_1;

typedef struct 
{
unsigned int     ColorTrans_C3:16;
unsigned int     ColorTrans_C4:16;
}CT_COE_2;

typedef struct 
{
unsigned int     ColorTrans_C5:16;
unsigned int     ColorTrans_C6:16;
}CT_COE_3;

typedef struct 
{
unsigned int     ColorTrans_C7:16;
unsigned int     ColorTrans_C8:16;
}CT_COE_4;

typedef struct 
{
unsigned int     ColorTrans_C9:16;
unsigned int     ColorTrans_K1:16;
}CT_COE_5;

typedef struct 
{
unsigned int     ColorTrans_K2:16;
unsigned int     ColorTrans_K3:16;
}CT_COE_6;

#endif

#define AIF_MISC                                                                     0x98009400
#define AIF_MISC_reg_addr                                                            "0x98009400"
#define AIF_MISC_reg                                                                 0x98009400
#define set_AIF_MISC_reg(data)   (*((volatile unsigned int*) AIF_MISC_reg)=data)
#define get_AIF_MISC_reg   (*((volatile unsigned int*) AIF_MISC_reg))
#define AIF_MISC_inst_adr                                                            "0x0000"
#define AIF_MISC_inst                                                                0x0000
#define AIF_MISC_REG_EDP_DBG_SEL_shift                                               (28)
#define AIF_MISC_REG_EDP_DBG_SEL_mask                                                (0x30000000)
#define AIF_MISC_REG_EDP_DBG_SEL(data)                                               (0x30000000&((data)<<28))
#define AIF_MISC_REG_EDP_DBG_SEL_src(data)                                           ((0x30000000&(data))>>28)
#define AIF_MISC_get_REG_EDP_DBG_SEL(data)                                           ((0x30000000&(data))>>28)
#define AIF_MISC_REG_ISO_EN_shift                                                    (25)
#define AIF_MISC_REG_ISO_EN_mask                                                     (0x02000000)
#define AIF_MISC_REG_ISO_EN(data)                                                    (0x02000000&((data)<<25))
#define AIF_MISC_REG_ISO_EN_src(data)                                                ((0x02000000&(data))>>25)
#define AIF_MISC_get_REG_ISO_EN(data)                                                ((0x02000000&(data))>>25)
#define AIF_MISC_REG_EDP_MODE_shift                                                  (24)
#define AIF_MISC_REG_EDP_MODE_mask                                                   (0x01000000)
#define AIF_MISC_REG_EDP_MODE(data)                                                  (0x01000000&((data)<<24))
#define AIF_MISC_REG_EDP_MODE_src(data)                                              ((0x01000000&(data))>>24)
#define AIF_MISC_get_REG_EDP_MODE(data)                                              ((0x01000000&(data))>>24)
#define AIF_MISC_REG_TSTA_SEL_shift                                                  (20)
#define AIF_MISC_REG_TSTA_SEL_mask                                                   (0x00F00000)
#define AIF_MISC_REG_TSTA_SEL(data)                                                  (0x00F00000&((data)<<20))
#define AIF_MISC_REG_TSTA_SEL_src(data)                                              ((0x00F00000&(data))>>20)
#define AIF_MISC_get_REG_TSTA_SEL(data)                                              ((0x00F00000&(data))>>20)
#define AIF_MISC_REG_TSTD_SEL_shift                                                  (16)
#define AIF_MISC_REG_TSTD_SEL_mask                                                   (0x000F0000)
#define AIF_MISC_REG_TSTD_SEL(data)                                                  (0x000F0000&((data)<<16))
#define AIF_MISC_REG_TSTD_SEL_src(data)                                              ((0x000F0000&(data))>>16)
#define AIF_MISC_get_REG_TSTD_SEL(data)                                              ((0x000F0000&(data))>>16)
#define AIF_MISC_REG_IBHN_SEL_shift                                                  (12)
#define AIF_MISC_REG_IBHN_SEL_mask                                                   (0x00007000)
#define AIF_MISC_REG_IBHN_SEL(data)                                                  (0x00007000&((data)<<12))
#define AIF_MISC_REG_IBHN_SEL_src(data)                                              ((0x00007000&(data))>>12)
#define AIF_MISC_get_REG_IBHN_SEL(data)                                              ((0x00007000&(data))>>12)
#define AIF_MISC_REG_IBHX_SEL_shift                                                  (8)
#define AIF_MISC_REG_IBHX_SEL_mask                                                   (0x00000700)
#define AIF_MISC_REG_IBHX_SEL(data)                                                  (0x00000700&((data)<<8))
#define AIF_MISC_REG_IBHX_SEL_src(data)                                              ((0x00000700&(data))>>8)
#define AIF_MISC_get_REG_IBHX_SEL(data)                                              ((0x00000700&(data))>>8)
#define AIF_MISC_REG_BIAS_POW_shift                                                  (0)
#define AIF_MISC_REG_BIAS_POW_mask                                                   (0x00000001)
#define AIF_MISC_REG_BIAS_POW(data)                                                  (0x00000001&((data)<<0))
#define AIF_MISC_REG_BIAS_POW_src(data)                                              ((0x00000001&(data))>>0)
#define AIF_MISC_get_REG_BIAS_POW(data)                                              ((0x00000001&(data))>>0)


#define AIF_EDP_1                                                                    0x98009440
#define AIF_EDP_1_reg_addr                                                           "0x98009440"
#define AIF_EDP_1_reg                                                                0x98009440
#define set_AIF_EDP_1_reg(data)   (*((volatile unsigned int*) AIF_EDP_1_reg)=data)
#define get_AIF_EDP_1_reg   (*((volatile unsigned int*) AIF_EDP_1_reg))
#define AIF_EDP_1_inst_adr                                                           "0x0010"
#define AIF_EDP_1_inst                                                               0x0010
#define AIF_EDP_1_REG_EDP_SLEW_shift                                                 (24)
#define AIF_EDP_1_REG_EDP_SLEW_mask                                                  (0xFF000000)
#define AIF_EDP_1_REG_EDP_SLEW(data)                                                 (0xFF000000&((data)<<24))
#define AIF_EDP_1_REG_EDP_SLEW_src(data)                                             ((0xFF000000&(data))>>24)
#define AIF_EDP_1_get_REG_EDP_SLEW(data)                                             ((0xFF000000&(data))>>24)
#define AIF_EDP_1_REG_EDP_SHAPE_shift                                                (16)
#define AIF_EDP_1_REG_EDP_SHAPE_mask                                                 (0x00FF0000)
#define AIF_EDP_1_REG_EDP_SHAPE(data)                                                (0x00FF0000&((data)<<16))
#define AIF_EDP_1_REG_EDP_SHAPE_src(data)                                            ((0x00FF0000&(data))>>16)
#define AIF_EDP_1_get_REG_EDP_SHAPE(data)                                            ((0x00FF0000&(data))>>16)
#define AIF_EDP_1_REG_EDP_EN_shift                                                   (0)
#define AIF_EDP_1_REG_EDP_EN_mask                                                    (0x0000000F)
#define AIF_EDP_1_REG_EDP_EN(data)                                                   (0x0000000F&((data)<<0))
#define AIF_EDP_1_REG_EDP_EN_src(data)                                               ((0x0000000F&(data))>>0)
#define AIF_EDP_1_get_REG_EDP_EN(data)                                               ((0x0000000F&(data))>>0)


#define AIF_EDP_2                                                                    0x98009444
#define AIF_EDP_2_reg_addr                                                           "0x98009444"
#define AIF_EDP_2_reg                                                                0x98009444
#define set_AIF_EDP_2_reg(data)   (*((volatile unsigned int*) AIF_EDP_2_reg)=data)
#define get_AIF_EDP_2_reg   (*((volatile unsigned int*) AIF_EDP_2_reg))
#define AIF_EDP_2_inst_adr                                                           "0x0011"
#define AIF_EDP_2_inst                                                               0x0011
#define AIF_EDP_2_REG_EDP_EMPH_EN_shift                                              (20)
#define AIF_EDP_2_REG_EDP_EMPH_EN_mask                                               (0x00F00000)
#define AIF_EDP_2_REG_EDP_EMPH_EN(data)                                              (0x00F00000&((data)<<20))
#define AIF_EDP_2_REG_EDP_EMPH_EN_src(data)                                          ((0x00F00000&(data))>>20)
#define AIF_EDP_2_get_REG_EDP_EMPH_EN(data)                                          ((0x00F00000&(data))>>20)
#define AIF_EDP_2_REG_EDP_EMP2X_SEL_shift                                            (16)
#define AIF_EDP_2_REG_EDP_EMP2X_SEL_mask                                             (0x000F0000)
#define AIF_EDP_2_REG_EDP_EMP2X_SEL(data)                                            (0x000F0000&((data)<<16))
#define AIF_EDP_2_REG_EDP_EMP2X_SEL_src(data)                                        ((0x000F0000&(data))>>16)
#define AIF_EDP_2_get_REG_EDP_EMP2X_SEL(data)                                        ((0x000F0000&(data))>>16)
#define AIF_EDP_2_REG_EDP_EMPH_SEL_shift                                             (0)
#define AIF_EDP_2_REG_EDP_EMPH_SEL_mask                                              (0x0000FFFF)
#define AIF_EDP_2_REG_EDP_EMPH_SEL(data)                                             (0x0000FFFF&((data)<<0))
#define AIF_EDP_2_REG_EDP_EMPH_SEL_src(data)                                         ((0x0000FFFF&(data))>>0)
#define AIF_EDP_2_get_REG_EDP_EMPH_SEL(data)                                         ((0x0000FFFF&(data))>>0)


#define AIF_EDP_3                                                                    0x98009448
#define AIF_EDP_3_reg_addr                                                           "0x98009448"
#define AIF_EDP_3_reg                                                                0x98009448
#define set_AIF_EDP_3_reg(data)   (*((volatile unsigned int*) AIF_EDP_3_reg)=data)
#define get_AIF_EDP_3_reg   (*((volatile unsigned int*) AIF_EDP_3_reg))
#define AIF_EDP_3_inst_adr                                                           "0x0012"
#define AIF_EDP_3_inst                                                               0x0012
#define AIF_EDP_3_REG_EDP_IBNX_SEL_shift                                             (31)
#define AIF_EDP_3_REG_EDP_IBNX_SEL_mask                                              (0x80000000)
#define AIF_EDP_3_REG_EDP_IBNX_SEL(data)                                             (0x80000000&((data)<<31))
#define AIF_EDP_3_REG_EDP_IBNX_SEL_src(data)                                         ((0x80000000&(data))>>31)
#define AIF_EDP_3_get_REG_EDP_IBNX_SEL(data)                                         ((0x80000000&(data))>>31)
#define AIF_EDP_3_REG_VG_SEL_shift                                                   (28)
#define AIF_EDP_3_REG_VG_SEL_mask                                                    (0x30000000)
#define AIF_EDP_3_REG_VG_SEL(data)                                                   (0x30000000&((data)<<28))
#define AIF_EDP_3_REG_VG_SEL_src(data)                                               ((0x30000000&(data))>>28)
#define AIF_EDP_3_get_REG_VG_SEL(data)                                               ((0x30000000&(data))>>28)
#define AIF_EDP_3_REG_EDP_DRV2X_SEL_shift                                            (24)
#define AIF_EDP_3_REG_EDP_DRV2X_SEL_mask                                             (0x0F000000)
#define AIF_EDP_3_REG_EDP_DRV2X_SEL(data)                                            (0x0F000000&((data)<<24))
#define AIF_EDP_3_REG_EDP_DRV2X_SEL_src(data)                                        ((0x0F000000&(data))>>24)
#define AIF_EDP_3_get_REG_EDP_DRV2X_SEL(data)                                        ((0x0F000000&(data))>>24)
#define AIF_EDP_3_REG_EDP_PREDRV_SEL_shift                                           (16)
#define AIF_EDP_3_REG_EDP_PREDRV_SEL_mask                                            (0x00FF0000)
#define AIF_EDP_3_REG_EDP_PREDRV_SEL(data)                                           (0x00FF0000&((data)<<16))
#define AIF_EDP_3_REG_EDP_PREDRV_SEL_src(data)                                       ((0x00FF0000&(data))>>16)
#define AIF_EDP_3_get_REG_EDP_PREDRV_SEL(data)                                       ((0x00FF0000&(data))>>16)
#define AIF_EDP_3_REG_EDP_DRV_SEL_shift                                              (0)
#define AIF_EDP_3_REG_EDP_DRV_SEL_mask                                               (0x0000FFFF)
#define AIF_EDP_3_REG_EDP_DRV_SEL(data)                                              (0x0000FFFF&((data)<<0))
#define AIF_EDP_3_REG_EDP_DRV_SEL_src(data)                                          ((0x0000FFFF&(data))>>0)
#define AIF_EDP_3_get_REG_EDP_DRV_SEL(data)                                          ((0x0000FFFF&(data))>>0)


#define AIF_EDP_4                                                                    0x9800944C
#define AIF_EDP_4_reg_addr                                                           "0x9800944C"
#define AIF_EDP_4_reg                                                                0x9800944C
#define set_AIF_EDP_4_reg(data)   (*((volatile unsigned int*) AIF_EDP_4_reg)=data)
#define get_AIF_EDP_4_reg   (*((volatile unsigned int*) AIF_EDP_4_reg))
#define AIF_EDP_4_inst_adr                                                           "0x0013"
#define AIF_EDP_4_inst                                                               0x0013
#define AIF_EDP_4_REG_EDP_R50_SEL_shift                                              (16)
#define AIF_EDP_4_REG_EDP_R50_SEL_mask                                               (0xFFFF0000)
#define AIF_EDP_4_REG_EDP_R50_SEL(data)                                              (0xFFFF0000&((data)<<16))
#define AIF_EDP_4_REG_EDP_R50_SEL_src(data)                                          ((0xFFFF0000&(data))>>16)
#define AIF_EDP_4_get_REG_EDP_R50_SEL(data)                                          ((0xFFFF0000&(data))>>16)
#define AIF_EDP_4_REG_EDP_RESERVED_shift                                             (0)
#define AIF_EDP_4_REG_EDP_RESERVED_mask                                              (0x0000FFFF)
#define AIF_EDP_4_REG_EDP_RESERVED(data)                                             (0x0000FFFF&((data)<<0))
#define AIF_EDP_4_REG_EDP_RESERVED_src(data)                                         ((0x0000FFFF&(data))>>0)
#define AIF_EDP_4_get_REG_EDP_RESERVED(data)                                         ((0x0000FFFF&(data))>>0)


#define AIF_LVDS_1                                                                   0x98009480
#define AIF_LVDS_1_reg_addr                                                          "0x98009480"
#define AIF_LVDS_1_reg                                                               0x98009480
#define set_AIF_LVDS_1_reg(data)   (*((volatile unsigned int*) AIF_LVDS_1_reg)=data)
#define get_AIF_LVDS_1_reg   (*((volatile unsigned int*) AIF_LVDS_1_reg))
#define AIF_LVDS_1_inst_adr                                                          "0x0020"
#define AIF_LVDS_1_inst                                                              0x0020
#define AIF_LVDS_1_REG_VCM_SEL_shift                                                 (24)
#define AIF_LVDS_1_REG_VCM_SEL_mask                                                  (0x07000000)
#define AIF_LVDS_1_REG_VCM_SEL(data)                                                 (0x07000000&((data)<<24))
#define AIF_LVDS_1_REG_VCM_SEL_src(data)                                             ((0x07000000&(data))>>24)
#define AIF_LVDS_1_get_REG_VCM_SEL(data)                                             ((0x07000000&(data))>>24)
#define AIF_LVDS_1_REG_LVDS_TSTSEL_shift                                             (20)
#define AIF_LVDS_1_REG_LVDS_TSTSEL_mask                                              (0x00100000)
#define AIF_LVDS_1_REG_LVDS_TSTSEL(data)                                             (0x00100000&((data)<<20))
#define AIF_LVDS_1_REG_LVDS_TSTSEL_src(data)                                         ((0x00100000&(data))>>20)
#define AIF_LVDS_1_get_REG_LVDS_TSTSEL(data)                                         ((0x00100000&(data))>>20)
#define AIF_LVDS_1_REG_LVDS_SER_SEL_shift                                            (16)
#define AIF_LVDS_1_REG_LVDS_SER_SEL_mask                                             (0x00030000)
#define AIF_LVDS_1_REG_LVDS_SER_SEL(data)                                            (0x00030000&((data)<<16))
#define AIF_LVDS_1_REG_LVDS_SER_SEL_src(data)                                        ((0x00030000&(data))>>16)
#define AIF_LVDS_1_get_REG_LVDS_SER_SEL(data)                                        ((0x00030000&(data))>>16)
#define AIF_LVDS_1_REG_LVDS_DLAG_shift                                               (8)
#define AIF_LVDS_1_REG_LVDS_DLAG_mask                                                (0x00001F00)
#define AIF_LVDS_1_REG_LVDS_DLAG(data)                                               (0x00001F00&((data)<<8))
#define AIF_LVDS_1_REG_LVDS_DLAG_src(data)                                           ((0x00001F00&(data))>>8)
#define AIF_LVDS_1_get_REG_LVDS_DLAG(data)                                           ((0x00001F00&(data))>>8)
#define AIF_LVDS_1_REG_LVDS_POW_shift                                                (0)
#define AIF_LVDS_1_REG_LVDS_POW_mask                                                 (0x0000001F)
#define AIF_LVDS_1_REG_LVDS_POW(data)                                                (0x0000001F&((data)<<0))
#define AIF_LVDS_1_REG_LVDS_POW_src(data)                                            ((0x0000001F&(data))>>0)
#define AIF_LVDS_1_get_REG_LVDS_POW(data)                                            ((0x0000001F&(data))>>0)


#define AIF_LVDS_2                                                                   0x98009484
#define AIF_LVDS_2_reg_addr                                                          "0x98009484"
#define AIF_LVDS_2_reg                                                               0x98009484
#define set_AIF_LVDS_2_reg(data)   (*((volatile unsigned int*) AIF_LVDS_2_reg)=data)
#define get_AIF_LVDS_2_reg   (*((volatile unsigned int*) AIF_LVDS_2_reg))
#define AIF_LVDS_2_inst_adr                                                          "0x0021"
#define AIF_LVDS_2_inst                                                              0x0021
#define AIF_LVDS_2_REG_IBTX_SEL_shift                                                (28)
#define AIF_LVDS_2_REG_IBTX_SEL_mask                                                 (0x30000000)
#define AIF_LVDS_2_REG_IBTX_SEL(data)                                                (0x30000000&((data)<<28))
#define AIF_LVDS_2_REG_IBTX_SEL_src(data)                                            ((0x30000000&(data))>>28)
#define AIF_LVDS_2_get_REG_IBTX_SEL(data)                                            ((0x30000000&(data))>>28)
#define AIF_LVDS_2_REG_LVDS_RTONL_shift                                              (20)
#define AIF_LVDS_2_REG_LVDS_RTONL_mask                                               (0x01F00000)
#define AIF_LVDS_2_REG_LVDS_RTONL(data)                                              (0x01F00000&((data)<<20))
#define AIF_LVDS_2_REG_LVDS_RTONL_src(data)                                          ((0x01F00000&(data))>>20)
#define AIF_LVDS_2_get_REG_LVDS_RTONL(data)                                          ((0x01F00000&(data))>>20)
#define AIF_LVDS_2_REG_LVDS_DRV_SEL_shift                                            (0)
#define AIF_LVDS_2_REG_LVDS_DRV_SEL_mask                                             (0x000FFFFF)
#define AIF_LVDS_2_REG_LVDS_DRV_SEL(data)                                            (0x000FFFFF&((data)<<0))
#define AIF_LVDS_2_REG_LVDS_DRV_SEL_src(data)                                        ((0x000FFFFF&(data))>>0)
#define AIF_LVDS_2_get_REG_LVDS_DRV_SEL(data)                                        ((0x000FFFFF&(data))>>0)


#define AIF_LVDS_3                                                                   0x98009488
#define AIF_LVDS_3_reg_addr                                                          "0x98009488"
#define AIF_LVDS_3_reg                                                               0x98009488
#define set_AIF_LVDS_3_reg(data)   (*((volatile unsigned int*) AIF_LVDS_3_reg)=data)
#define get_AIF_LVDS_3_reg   (*((volatile unsigned int*) AIF_LVDS_3_reg))
#define AIF_LVDS_3_inst_adr                                                          "0x0022"
#define AIF_LVDS_3_inst                                                              0x0022
#define AIF_LVDS_3_REG_LVDS_SLEW_shift                                               (16)
#define AIF_LVDS_3_REG_LVDS_SLEW_mask                                                (0x03FF0000)
#define AIF_LVDS_3_REG_LVDS_SLEW(data)                                               (0x03FF0000&((data)<<16))
#define AIF_LVDS_3_REG_LVDS_SLEW_src(data)                                           ((0x03FF0000&(data))>>16)
#define AIF_LVDS_3_get_REG_LVDS_SLEW(data)                                           ((0x03FF0000&(data))>>16)
#define AIF_LVDS_3_REG_LVDS_SHAPE_shift                                              (0)
#define AIF_LVDS_3_REG_LVDS_SHAPE_mask                                               (0x00007FFF)
#define AIF_LVDS_3_REG_LVDS_SHAPE(data)                                              (0x00007FFF&((data)<<0))
#define AIF_LVDS_3_REG_LVDS_SHAPE_src(data)                                          ((0x00007FFF&(data))>>0)
#define AIF_LVDS_3_get_REG_LVDS_SHAPE(data)                                          ((0x00007FFF&(data))>>0)


#define AIF_LVDS_4                                                                   0x9800948C
#define AIF_LVDS_4_reg_addr                                                          "0x9800948C"
#define AIF_LVDS_4_reg                                                               0x9800948C
#define set_AIF_LVDS_4_reg(data)   (*((volatile unsigned int*) AIF_LVDS_4_reg)=data)
#define get_AIF_LVDS_4_reg   (*((volatile unsigned int*) AIF_LVDS_4_reg))
#define AIF_LVDS_4_inst_adr                                                          "0x0023"
#define AIF_LVDS_4_inst                                                              0x0023
#define AIF_LVDS_4_REG_LVDS_PRE_SR_SEL_shift                                         (21)
#define AIF_LVDS_4_REG_LVDS_PRE_SR_SEL_mask                                          (0x00200000)
#define AIF_LVDS_4_REG_LVDS_PRE_SR_SEL(data)                                         (0x00200000&((data)<<21))
#define AIF_LVDS_4_REG_LVDS_PRE_SR_SEL_src(data)                                     ((0x00200000&(data))>>21)
#define AIF_LVDS_4_get_REG_LVDS_PRE_SR_SEL(data)                                     ((0x00200000&(data))>>21)
#define AIF_LVDS_4_REG_LVDS_PRE_EN_shift                                             (20)
#define AIF_LVDS_4_REG_LVDS_PRE_EN_mask                                              (0x00100000)
#define AIF_LVDS_4_REG_LVDS_PRE_EN(data)                                             (0x00100000&((data)<<20))
#define AIF_LVDS_4_REG_LVDS_PRE_EN_src(data)                                         ((0x00100000&(data))>>20)
#define AIF_LVDS_4_get_REG_LVDS_PRE_EN(data)                                         ((0x00100000&(data))>>20)
#define AIF_LVDS_4_REG_LVDS_PRE_SEL_shift                                            (0)
#define AIF_LVDS_4_REG_LVDS_PRE_SEL_mask                                             (0x000FFFFF)
#define AIF_LVDS_4_REG_LVDS_PRE_SEL(data)                                            (0x000FFFFF&((data)<<0))
#define AIF_LVDS_4_REG_LVDS_PRE_SEL_src(data)                                        ((0x000FFFFF&(data))>>0)
#define AIF_LVDS_4_get_REG_LVDS_PRE_SEL(data)                                        ((0x000FFFFF&(data))>>0)


#define DUMMY_LVDS                                                                   0x980094C0
#define DUMMY_LVDS_reg_addr                                                          "0x980094C0"
#define DUMMY_LVDS_reg                                                               0x980094C0
#define set_DUMMY_LVDS_reg(data)   (*((volatile unsigned int*) DUMMY_LVDS_reg)=data)
#define get_DUMMY_LVDS_reg   (*((volatile unsigned int*) DUMMY_LVDS_reg))
#define DUMMY_LVDS_inst_adr                                                          "0x0030"
#define DUMMY_LVDS_inst                                                              0x0030
#define DUMMY_LVDS_dummy_lvds_shift                                                  (0)
#define DUMMY_LVDS_dummy_lvds_mask                                                   (0xFFFFFFFF)
#define DUMMY_LVDS_dummy_lvds(data)                                                  (0xFFFFFFFF&((data)<<0))
#define DUMMY_LVDS_dummy_lvds_src(data)                                              ((0xFFFFFFFF&(data))>>0)
#define DUMMY_LVDS_get_dummy_lvds(data)                                              ((0xFFFFFFFF&(data))>>0)


#define DUMMY_EDP                                                                    0x980094C4
#define DUMMY_EDP_reg_addr                                                           "0x980094C4"
#define DUMMY_EDP_reg                                                                0x980094C4
#define set_DUMMY_EDP_reg(data)   (*((volatile unsigned int*) DUMMY_EDP_reg)=data)
#define get_DUMMY_EDP_reg   (*((volatile unsigned int*) DUMMY_EDP_reg))
#define DUMMY_EDP_inst_adr                                                           "0x0031"
#define DUMMY_EDP_inst                                                               0x0031
#define DUMMY_EDP_dummy_edp_shift                                                    (0)
#define DUMMY_EDP_dummy_edp_mask                                                     (0xFFFFFFFF)
#define DUMMY_EDP_dummy_edp(data)                                                    (0xFFFFFFFF&((data)<<0))
#define DUMMY_EDP_dummy_edp_src(data)                                                ((0xFFFFFFFF&(data))>>0)
#define DUMMY_EDP_get_dummy_edp(data)                                                ((0xFFFFFFFF&(data))>>0)


#define CT_CTRL                                                                      0x98009500
#define CT_CTRL_reg_addr                                                             "0x98009500"
#define CT_CTRL_reg                                                                  0x98009500
#define set_CT_CTRL_reg(data)   (*((volatile unsigned int*) CT_CTRL_reg)=data)
#define get_CT_CTRL_reg   (*((volatile unsigned int*) CT_CTRL_reg))
#define CT_CTRL_inst_adr                                                             "0x0040"
#define CT_CTRL_inst                                                                 0x0040
#define CT_CTRL_YUV422_mode_shift                                                    (1)
#define CT_CTRL_YUV422_mode_mask                                                     (0x00000002)
#define CT_CTRL_YUV422_mode(data)                                                    (0x00000002&((data)<<1))
#define CT_CTRL_YUV422_mode_src(data)                                                ((0x00000002&(data))>>1)
#define CT_CTRL_get_YUV422_mode(data)                                                ((0x00000002&(data))>>1)
#define CT_CTRL_ColorTrans_EN_shift                                                  (0)
#define CT_CTRL_ColorTrans_EN_mask                                                   (0x00000001)
#define CT_CTRL_ColorTrans_EN(data)                                                  (0x00000001&((data)<<0))
#define CT_CTRL_ColorTrans_EN_src(data)                                              ((0x00000001&(data))>>0)
#define CT_CTRL_get_ColorTrans_EN(data)                                              ((0x00000001&(data))>>0)


#define CT_COE_1                                                                     0x98009508
#define CT_COE_1_reg_addr                                                            "0x98009508"
#define CT_COE_1_reg                                                                 0x98009508
#define set_CT_COE_1_reg(data)   (*((volatile unsigned int*) CT_COE_1_reg)=data)
#define get_CT_COE_1_reg   (*((volatile unsigned int*) CT_COE_1_reg))
#define CT_COE_1_inst_adr                                                            "0x0042"
#define CT_COE_1_inst                                                                0x0042
#define CT_COE_1_ColorTrans_C1_shift                                                 (16)
#define CT_COE_1_ColorTrans_C1_mask                                                  (0xFFFF0000)
#define CT_COE_1_ColorTrans_C1(data)                                                 (0xFFFF0000&((data)<<16))
#define CT_COE_1_ColorTrans_C1_src(data)                                             ((0xFFFF0000&(data))>>16)
#define CT_COE_1_get_ColorTrans_C1(data)                                             ((0xFFFF0000&(data))>>16)
#define CT_COE_1_ColorTrans_C2_shift                                                 (0)
#define CT_COE_1_ColorTrans_C2_mask                                                  (0x0000FFFF)
#define CT_COE_1_ColorTrans_C2(data)                                                 (0x0000FFFF&((data)<<0))
#define CT_COE_1_ColorTrans_C2_src(data)                                             ((0x0000FFFF&(data))>>0)
#define CT_COE_1_get_ColorTrans_C2(data)                                             ((0x0000FFFF&(data))>>0)


#define CT_COE_2                                                                     0x9800950C
#define CT_COE_2_reg_addr                                                            "0x9800950C"
#define CT_COE_2_reg                                                                 0x9800950C
#define set_CT_COE_2_reg(data)   (*((volatile unsigned int*) CT_COE_2_reg)=data)
#define get_CT_COE_2_reg   (*((volatile unsigned int*) CT_COE_2_reg))
#define CT_COE_2_inst_adr                                                            "0x0043"
#define CT_COE_2_inst                                                                0x0043
#define CT_COE_2_ColorTrans_C3_shift                                                 (16)
#define CT_COE_2_ColorTrans_C3_mask                                                  (0xFFFF0000)
#define CT_COE_2_ColorTrans_C3(data)                                                 (0xFFFF0000&((data)<<16))
#define CT_COE_2_ColorTrans_C3_src(data)                                             ((0xFFFF0000&(data))>>16)
#define CT_COE_2_get_ColorTrans_C3(data)                                             ((0xFFFF0000&(data))>>16)
#define CT_COE_2_ColorTrans_C4_shift                                                 (0)
#define CT_COE_2_ColorTrans_C4_mask                                                  (0x0000FFFF)
#define CT_COE_2_ColorTrans_C4(data)                                                 (0x0000FFFF&((data)<<0))
#define CT_COE_2_ColorTrans_C4_src(data)                                             ((0x0000FFFF&(data))>>0)
#define CT_COE_2_get_ColorTrans_C4(data)                                             ((0x0000FFFF&(data))>>0)


#define CT_COE_3                                                                     0x98009510
#define CT_COE_3_reg_addr                                                            "0x98009510"
#define CT_COE_3_reg                                                                 0x98009510
#define set_CT_COE_3_reg(data)   (*((volatile unsigned int*) CT_COE_3_reg)=data)
#define get_CT_COE_3_reg   (*((volatile unsigned int*) CT_COE_3_reg))
#define CT_COE_3_inst_adr                                                            "0x0044"
#define CT_COE_3_inst                                                                0x0044
#define CT_COE_3_ColorTrans_C5_shift                                                 (16)
#define CT_COE_3_ColorTrans_C5_mask                                                  (0xFFFF0000)
#define CT_COE_3_ColorTrans_C5(data)                                                 (0xFFFF0000&((data)<<16))
#define CT_COE_3_ColorTrans_C5_src(data)                                             ((0xFFFF0000&(data))>>16)
#define CT_COE_3_get_ColorTrans_C5(data)                                             ((0xFFFF0000&(data))>>16)
#define CT_COE_3_ColorTrans_C6_shift                                                 (0)
#define CT_COE_3_ColorTrans_C6_mask                                                  (0x0000FFFF)
#define CT_COE_3_ColorTrans_C6(data)                                                 (0x0000FFFF&((data)<<0))
#define CT_COE_3_ColorTrans_C6_src(data)                                             ((0x0000FFFF&(data))>>0)
#define CT_COE_3_get_ColorTrans_C6(data)                                             ((0x0000FFFF&(data))>>0)


#define CT_COE_4                                                                     0x98009514
#define CT_COE_4_reg_addr                                                            "0x98009514"
#define CT_COE_4_reg                                                                 0x98009514
#define set_CT_COE_4_reg(data)   (*((volatile unsigned int*) CT_COE_4_reg)=data)
#define get_CT_COE_4_reg   (*((volatile unsigned int*) CT_COE_4_reg))
#define CT_COE_4_inst_adr                                                            "0x0045"
#define CT_COE_4_inst                                                                0x0045
#define CT_COE_4_ColorTrans_C7_shift                                                 (16)
#define CT_COE_4_ColorTrans_C7_mask                                                  (0xFFFF0000)
#define CT_COE_4_ColorTrans_C7(data)                                                 (0xFFFF0000&((data)<<16))
#define CT_COE_4_ColorTrans_C7_src(data)                                             ((0xFFFF0000&(data))>>16)
#define CT_COE_4_get_ColorTrans_C7(data)                                             ((0xFFFF0000&(data))>>16)
#define CT_COE_4_ColorTrans_C8_shift                                                 (0)
#define CT_COE_4_ColorTrans_C8_mask                                                  (0x0000FFFF)
#define CT_COE_4_ColorTrans_C8(data)                                                 (0x0000FFFF&((data)<<0))
#define CT_COE_4_ColorTrans_C8_src(data)                                             ((0x0000FFFF&(data))>>0)
#define CT_COE_4_get_ColorTrans_C8(data)                                             ((0x0000FFFF&(data))>>0)


#define CT_COE_5                                                                     0x98009518
#define CT_COE_5_reg_addr                                                            "0x98009518"
#define CT_COE_5_reg                                                                 0x98009518
#define set_CT_COE_5_reg(data)   (*((volatile unsigned int*) CT_COE_5_reg)=data)
#define get_CT_COE_5_reg   (*((volatile unsigned int*) CT_COE_5_reg))
#define CT_COE_5_inst_adr                                                            "0x0046"
#define CT_COE_5_inst                                                                0x0046
#define CT_COE_5_ColorTrans_C9_shift                                                 (16)
#define CT_COE_5_ColorTrans_C9_mask                                                  (0xFFFF0000)
#define CT_COE_5_ColorTrans_C9(data)                                                 (0xFFFF0000&((data)<<16))
#define CT_COE_5_ColorTrans_C9_src(data)                                             ((0xFFFF0000&(data))>>16)
#define CT_COE_5_get_ColorTrans_C9(data)                                             ((0xFFFF0000&(data))>>16)
#define CT_COE_5_ColorTrans_K1_shift                                                 (0)
#define CT_COE_5_ColorTrans_K1_mask                                                  (0x0000FFFF)
#define CT_COE_5_ColorTrans_K1(data)                                                 (0x0000FFFF&((data)<<0))
#define CT_COE_5_ColorTrans_K1_src(data)                                             ((0x0000FFFF&(data))>>0)
#define CT_COE_5_get_ColorTrans_K1(data)                                             ((0x0000FFFF&(data))>>0)


#define CT_COE_6                                                                     0x9800951C
#define CT_COE_6_reg_addr                                                            "0x9800951C"
#define CT_COE_6_reg                                                                 0x9800951C
#define set_CT_COE_6_reg(data)   (*((volatile unsigned int*) CT_COE_6_reg)=data)
#define get_CT_COE_6_reg   (*((volatile unsigned int*) CT_COE_6_reg))
#define CT_COE_6_inst_adr                                                            "0x0047"
#define CT_COE_6_inst                                                                0x0047
#define CT_COE_6_ColorTrans_K2_shift                                                 (16)
#define CT_COE_6_ColorTrans_K2_mask                                                  (0xFFFF0000)
#define CT_COE_6_ColorTrans_K2(data)                                                 (0xFFFF0000&((data)<<16))
#define CT_COE_6_ColorTrans_K2_src(data)                                             ((0xFFFF0000&(data))>>16)
#define CT_COE_6_get_ColorTrans_K2(data)                                             ((0xFFFF0000&(data))>>16)
#define CT_COE_6_ColorTrans_K3_shift                                                 (0)
#define CT_COE_6_ColorTrans_K3_mask                                                  (0x0000FFFF)
#define CT_COE_6_ColorTrans_K3(data)                                                 (0x0000FFFF&((data)<<0))
#define CT_COE_6_ColorTrans_K3_src(data)                                             ((0x0000FFFF&(data))>>0)
#define CT_COE_6_get_ColorTrans_K3(data)                                             ((0x0000FFFF&(data))>>0)


#endif
