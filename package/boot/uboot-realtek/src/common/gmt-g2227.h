/*
 * gmt-g2227.h - definition for gmt-g2227 PMIC
 *
 * Copyright (C) 2016, Realtek Semiconductor Corporation
 * Cheng-Yu Lee <cylee12@realtek.com>
 */
#ifndef __GMT_G2227_H__
#define __GMT_G2227_H__

#define G2227_OK    0
#define G2227_ERR  -1

/********************************************************************************
 * helper macros 
 ********************************************************************************/
#define _BIT(_n)      (1 << (_n))
#define G2227_SET_REG(_v)   (((_v) & 0xff) << 0)
#define G2227_SET_SIZE(_v)  (((_v) & 0xf) << 8)
#define G2227_SET_SHIFT(_v) (((_v) & 0xf) << 12)
#define G2227_GET_REG(_v)   (((_v) >> 0) & 0xff)
#define G2227_GET_SIZE(_v)  (((_v) >> 8) & 0xf)
#define G2227_GET_SHIFT(_v) (((_v) >> 12) & 0xf)
#define G2227_GET_MASK(_v)  ((_BIT(G2227_GET_SIZE(_v)) - 1) << G2227_GET_SHIFT(_v))

#define G2227_DEF_ITEM(_r, _s, _sh) \
    (G2227_SET_REG(_r) | G2227_SET_SIZE(_s) | G2227_SET_SHIFT(_sh))

/********************************************************************************
 * command definition 
 ********************************************************************************/
/*
 * Power Keys
 *
 * PWRKEY_ALL: after read reg, all bit will be clear, so returns all bits
 *             for handling PWRKEY
 */
#define PWRKEY_ALL     G2227_DEF_ITEM(0x00, 3, 3)
#define PWRKEY         G2227_DEF_ITEM(0x00, 1, 5)
#define PWRKEY_LP      G2227_DEF_ITEM(0x00, 1, 4)
#define PWRKEY_IT      G2227_DEF_ITEM(0x00, 1, 3)

/* Power Keys selection */
enum {
    KEY_NOT_PRESSED = 0,
    KEY_PRESSED     = 1,
};

#define LPOFF_TO_DO     G2227_DEF_ITEM(0x02, 1, 7)
#define ENLPOFF         G2227_DEF_ITEM(0x02, 1, 6)
#define TIME_IT         G2227_DEF_ITEM(0x02, 2, 4)
#define TIME_LP         G2227_DEF_ITEM(0x02, 2, 2)
#define TIME_LPOFF      G2227_DEF_ITEM(0x02, 2, 0)

enum {
    LPOFF_TO_DO_ACT1, /* Remain in shutdown mode */
    LPOFF_TO_DO_ACT2, /* Re-startup by sequence */
};

enum {
    ENLPOFF_NO  = 0,
    ENLPOFF_YES = 1,
};

enum {
    TIME_IT_0128_ms = 0,
    TIME_IT_0500_ms = 1,
    TIME_IT_1000_ms = 2,
    TIME_IT_1500_ms = 3,
};

enum {
    TIME_LP_01_s = 0,
    TIME_LP_02_s = 1,
    TIME_LP_03_s = 2,
    TIME_LP_04_s = 3,
};

enum {
    TIME_LPOFF_06_s = 0,
    TIME_LPOFF_07_s = 1,
    TIME_LPOFF_08_s = 2,
    TIME_LPOFF_10_s = 3,
};

#define SOFTOFF         G2227_DEF_ITEM(0x04, 1, 7)

enum {
    SOFTOFF_POWER_ON  = 0,
    SOFTOFF_POWER_OFF = 1,
};

#define ERRDC1          G2227_DEF_ITEM(0x05, 1, 7)
#define ERRDC2          G2227_DEF_ITEM(0x05, 1, 6)
#define ERRDC3          G2227_DEF_ITEM(0x05, 1, 5)
#define ERRDC4          G2227_DEF_ITEM(0x05, 1, 4)
#define ERRDC5          G2227_DEF_ITEM(0x05, 1, 3)
#define ERRDC6          G2227_DEF_ITEM(0x05, 1, 2)
#define ERRLDO2         G2227_DEF_ITEM(0x05, 1, 1)
#define ERRLDO3         G2227_DEF_ITEM(0x05, 1, 0)

enum {
    ERR_NO  = 0,
    ERR_YES = 1,
};

#define DCDC1_ONOFF     G2227_DEF_ITEM(0x05, 1, 7)
#define DCDC2_ONOFF     G2227_DEF_ITEM(0x05, 1, 6)
#define DCDC3_ONOFF     G2227_DEF_ITEM(0x05, 1, 5)
#define DCDC4_ONOFF     G2227_DEF_ITEM(0x05, 1, 4)
#define DCDC5_ONOFF     G2227_DEF_ITEM(0x05, 1, 3)
#define DCDC6_ONOFF     G2227_DEF_ITEM(0x05, 1, 2)
#define LDO2_ONOFF      G2227_DEF_ITEM(0x05, 1, 1)
#define LDO3_ONOFF      G2227_DEF_ITEM(0x05, 1, 0)

enum {
    ONOFF_SHUTDOWN  = 0,
    ONOFF_OPERATION = 1,
};

#define DCDC1_ENABLE_DISCHARGE G2227_DEF_ITEM(0x06, 1, 7)
#define DCDC2_ENABLE_DISCHARGE G2227_DEF_ITEM(0x06, 1, 6)
#define DCDC3_ENABLE_DISCHARGE G2227_DEF_ITEM(0x06, 1, 5)
#define DCDC4_ENABLE_DISCHARGE G2227_DEF_ITEM(0x06, 1, 4)
#define DCDC5_ENABLE_DISCHARGE G2227_DEF_ITEM(0x06, 1, 3)
#define DCDC6_ENABLE_DISCHARGE G2227_DEF_ITEM(0x06, 1, 2)
#define LDO2_ENABLE_DISCHARGE  G2227_DEF_ITEM(0x06, 1, 1)
#define LDO3_ENABLE_DISCHARGE  G2227_DEF_ITEM(0x06, 1, 0)

enum {
    ENDIS_DISABLE = 0,
    ENDIS_ENABLE  = 1,
};

/*
 * DCDCx Normal/Sleep Mode Control
 */
#define DCDC1_NRMMODE   G2227_DEF_ITEM(0x07, 2, 6)
#define DCDC1_SLPMODE   G2227_DEF_ITEM(0x07, 2, 4)
#define DCDC2_NRMMODE   G2227_DEF_ITEM(0x07, 2, 2)
#define DCDC2_SLPMODE   G2227_DEF_ITEM(0x07, 2, 0)
#define DCDC3_NRMMODE   G2227_DEF_ITEM(0x08, 2, 6)
#define DCDC3_SLPMODE   G2227_DEF_ITEM(0x08, 2, 4)
#define DCDC4_NRMMODE   G2227_DEF_ITEM(0x08, 2, 2)
#define DCDC4_SLPMODE   G2227_DEF_ITEM(0x08, 2, 0)
#define DCDC5_NRMMODE   G2227_DEF_ITEM(0x09, 2, 6)
#define DCDC5_SLPMODE   G2227_DEF_ITEM(0x09, 2, 4)
#define DCDC6_NRMMODE   G2227_DEF_ITEM(0x09, 2, 2)
#define DCDC6_SLPMODE   G2227_DEF_ITEM(0x09, 2, 0)

/* DCDCx Normal mode selection */
enum {
    DCDC_NRMMODE_AUTO         = 0,
    DCDC_NRMMODE_FORCE_PWM    = 2,
    DCDC_NRMMODE_AUTO_WO_ECO  = 3,
};

/* DCDCx Sleep mode selection */
enum {
    DCDC_SLPMODE_AUTO_WO_ECO  = 0,
    DCDC_SLPMODE_AUTO         = 1, /* for DCDC4 */
    DCDC_SLPMODE_AUTO_NRM_OUT = 1,
    DCDC_SLPMODE_AUTO_SPL_OUT = 2,
    DCDC_SLPMODE_SHUTDOWN     = 3,
};

/*
 * LDOx Mode Control
 */
#define LDO2_NRMMODE   G2227_DEF_ITEM(0x0A, 2, 6)
#define LDO2_SLPMODE   G2227_DEF_ITEM(0x0A, 2, 4)
#define LDO3_NRMMODE   G2227_DEF_ITEM(0x0A, 2, 2)
#define LDO3_SLPMODE   G2227_DEF_ITEM(0x0A, 2, 0)

enum {
    LDO_NRMMODE_NORMAL = 0,
    LDO_NRMMODE_ECO    = 2,
};

enum {
    LDO_SLPMODE_NRM_OUT  = 0,
    LOD_SLPMODE_SPL_OUT  = 1,
    LDO_SLPMODE_ECO      = 2,
    LDO_SLPMODE_SHUTDOWN = 3,
};

/*
 * Normal/Sleep Volatge Output
 */
#define DCDC2_NRM_VOL_OUT   G2227_DEF_ITEM(0x10, 6, 0)
#define DCDC3_NRM_VOL_OUT   G2227_DEF_ITEM(0x11, 6, 0)
#define DCDC5_NRM_VOL_OUT   G2227_DEF_ITEM(0x12, 6, 0)
#define DCDC1_NRM_VOL_OUT   G2227_DEF_ITEM(0x13, 2, 6)
#define DCDC6_NRM_VOL_OUT   G2227_DEF_ITEM(0x13, 6, 0)
#define LDO2_NRM_VOL_OUT    G2227_DEF_ITEM(0x14, 4, 4)
#define LDO3_NRM_VOL_OUT    G2227_DEF_ITEM(0x14, 4, 0)
#define DCDC2_SLP_VOL_OUT   G2227_DEF_ITEM(0x15, 6, 0)
#define DCDC3_SLP_VOL_OUT   G2227_DEF_ITEM(0x16, 6, 0)
#define DCDC5_SLP_VOL_OUT   G2227_DEF_ITEM(0x17, 6, 0)
#define DCDC1_SLP_VOL_OUT   G2227_DEF_ITEM(0x18, 2, 6)
#define DCDC6_SLP_VOL_OUT   G2227_DEF_ITEM(0x18, 6, 0)
#define LDO2_SLP_VOL_OUT    G2227_DEF_ITEM(0x19, 4, 4)
#define LDO3_SLP_VOL_OUT    G2227_DEF_ITEM(0x19, 4, 0)


/* DCDC1 Voltage Table in Normal/Sleep mode */
enum {
    DCDC_VOL_TBL_1_3000000_uV = 0,
    DCDC_VOL_TBL_1_3100000_uV = 1,
    DCDC_VOL_TBL_1_3200000_uV = 2,
    DCDC_VOL_TBL_1_3300000_uV = 3,
};

/* DCDC2/DCDC3/DCDC5/DCDC6 Voltage Table in Normal/Sleep mode */
enum {
    DCDC_VOL_TBL_2_0800000_uV = 0x00,
    DCDC_VOL_TBL_2_0812500_uV = 0x01,
    DCDC_VOL_TBL_2_0825000_uV = 0x02,
    DCDC_VOL_TBL_2_0837500_uV = 0x03,

    DCDC_VOL_TBL_2_0850000_uV = 0x04,
    DCDC_VOL_TBL_2_0862500_uV = 0x05,
    DCDC_VOL_TBL_2_0875000_uV = 0x06,
    DCDC_VOL_TBL_2_0887500_uV = 0x07,

    DCDC_VOL_TBL_2_0900000_uV = 0x08,
    DCDC_VOL_TBL_2_0912500_uV = 0x09,
    DCDC_VOL_TBL_2_0925000_uV = 0x0a,
    DCDC_VOL_TBL_2_0937500_uV = 0x0b,

    DCDC_VOL_TBL_2_0950000_uV = 0x0c,
    DCDC_VOL_TBL_2_0962500_uV = 0x0d,
    DCDC_VOL_TBL_2_0975000_uV = 0x0e,
    DCDC_VOL_TBL_2_0987500_uV = 0x0f,

    DCDC_VOL_TBL_2_1000000_uV = 0x10,
    DCDC_VOL_TBL_2_1012500_uV = 0x11,
    DCDC_VOL_TBL_2_1025000_uV = 0x12,
    DCDC_VOL_TBL_2_1037500_uV = 0x13,

    DCDC_VOL_TBL_2_1050000_uV = 0x14,
    DCDC_VOL_TBL_2_1062500_uV = 0x15,
    DCDC_VOL_TBL_2_1075000_uV = 0x16,
    DCDC_VOL_TBL_2_1087500_uV = 0x17,

    DCDC_VOL_TBL_2_1100000_uV = 0x18,
    DCDC_VOL_TBL_2_1112500_uV = 0x19,
    DCDC_VOL_TBL_2_1125000_uV = 0x1a,
    DCDC_VOL_TBL_2_1137500_uV = 0x1b,

    DCDC_VOL_TBL_2_1150000_uV = 0x1c,
    DCDC_VOL_TBL_2_1162500_uV = 0x1d,
    DCDC_VOL_TBL_2_1175000_uV = 0x1e,
    DCDC_VOL_TBL_2_1187500_uV = 0x1f,
};

/* LDOx Voltage Table in Normal/Sleep mode */
enum {
    LDO_VOL_TBL_0800000_uV = 0x0,
    LDO_VOL_TBL_0850000_uV = 0x1,
    LDO_VOL_TBL_0900000_uV = 0x2,
    LDO_VOL_TBL_0950000_uV = 0x3,

    LDO_VOL_TBL_1000000_uV = 0x4,
    LDO_VOL_TBL_1100000_uV = 0x5,
    LDO_VOL_TBL_1200000_uV = 0x6,
    LDO_VOL_TBL_1300000_uV = 0x7,

    LDO_VOL_TBL_1500000_uV = 0x8,
    LDO_VOL_TBL_1600000_uV = 0x9,
    LDO_VOL_TBL_1800000_uV = 0xa,
    LDO_VOL_TBL_1900000_uV = 0xb,

    LDO_VOL_TBL_2500000_uV = 0xc,
    LDO_VOL_TBL_2600000_uV = 0xd,
    LDO_VOL_TBL_3000000_uV = 0xe,
    LDO_VOL_TBL_3100000_uV = 0xf,    
};

#define G2227_CHIP_ID    G2227_DEF_ITEM(0x20, 5, 3)
#define G2227_VERSION    G2227_DEF_ITEM(0x20, 3, 0)
#define GMT_TESTING      G2227_DEF_ITEM(0xf1, 5, 0)

int g2227_init(void);
void g2227_exit(void);
int g2227_read_reg(unsigned char reg, unsigned char *val);
int g2227_write_reg(unsigned char reg, unsigned char val);
int g2227_get(unsigned int cmd, unsigned char *val);
int g2227_set(unsigned int cmd, unsigned char val);

#endif /* __GMT_G2227_H__ */ 
