#ifndef __FLASH_SPI_LIST_H__
#define __FLASH_SPI_LIST_H__

/* hcy modified as forwarding type */

#define MX_4Mbit                    0xc22013    //  0x1320c2 
#define MX_25L8006E_8Mbit	    0xc22014	
#define MX_25L1605_16Mbit           0xc22015    //  0x1520c2
#define MX_25L3206E_32Mbit          0xc22016    //  0x1620c2
#define MX_25L6405D_64Mbit          0xc22017    //  0x1720c2
#define MX_25L12805D_128Mbit        0xc22018    //  0x1820c2
#define MX_25L25635E_256Mbit        0xc22019
#define MX_25L6455E_64Mbit          0xc22617
#define MX_25L12855E_128Mbit        0xc22618
#define MX_25L25655F_256Mbit        0xc22619

#define PMC_4Mbit                   0x7f9d7e    //  0x7e9d7f

#define SPANSION_16Mbit             0x010214    //  0x140201
#define SPANSION_32Mbit             0x010215    //  0x150201
#define SPANSION_64Mbit             0x010216    //  0x160201
#define SPANSION_128Mbit            0x012018    //  0x182001
#define SPANSION_128Mbit_64s        0x0301      //  0x0103
#define SPANSION_128Mbit_256s       0x0300      //  0x0003
#define S25FL129P_64s               0x4d01      //  uniform  64KB sector
#define S25FL129P_256s              0x4d00      //  uniform 256KB sector
#define S25FL064K_4s                0xef4017     
#define S25FL016K_4s                0xef4015
#define SPANSION_S25FL164K	     	0x014017
#define SPANSION_S25FL216K			0x014015

#define SST_8Mbit                   0xbf80      //  0x80bf
#define SST_4Mbit                   0xbf258d    //  0x8d25bf
#define SST_16Mbit                  0xbf2541    //  0x4125bf

#define STM_64Mbit                  0x202017    //  0x172020
#define STM_128Mbit                 0x202018    //  0x182020
#define STM_N25Q_128Mbit            0x20ba18
#define STM_N25Q064_64Mbit          0x20ba17

#define EON_EN25QH16_16Mbit         0x1c7015    //  0x15701c
#define EON_EN25QH16128A_16Mbit	    0x1c7018    // 	0x18701c
#define EON_EN25Q32B_32Mbit         0x1c3016    //  0x16301c
#define EON_EN25Q64_64Mbit          0x1c3017    //  0x17301c
#define EON_EN25F16_16Mbit          0x1c3115
#define EON_EN25Q128_128Mbit        0x1c3018
#define EON_EN25B64_64Mbit          0x1c2017

#define WINBOND_W25Q80BV_8Mbit	    0xef4014
#define WINBOND_W325Q128BV_128Mbit  0xef4018

#define ESMT_F25L32PA_32Mbit        0x8c1620

#define GD25Q16B_16Mbit             0xc84015
#define GD25Q64B_64Mbit             0xc84017
#define GD25Q128B_128Mbit           0xc84018
#define GD25Q256D_256Mbit           0xc84019

#define A25L040_32Mbit              0x373013

#define IS25LQ080B_8Mbit            0x9d4014
#define IS25LQ016B_16Mbit           0x9d4015
#define IS25LQ032B_32Mbit           0x9d4016
#define IS25LP128_128Mbit           0x9d6018

#define BY25D20_2Mbit               0x684012
#define BY25D40_4Mbit               0x684013
#define BY25D16_16Mbit              0x684015
#define BY25Q32BS_32Mbit            0x684016
#define BY25Q64AS_64Mbit            0x684017
#define BY25Q128AS_128Mbit          0x684018

typedef struct 
{
    unsigned int    id ;
    unsigned char   sec_256k_en ;
    unsigned char   sec_64k_en ;
    unsigned char   sec_32k_en ;
    unsigned char   sec_4k_en ;
    unsigned char   page_program ;
    unsigned int    size;
    unsigned char   *string;
} s_device_type;


static const s_device_type s_device[] = 
{
    {SST_4Mbit,                    0, 1, 1, 1, 0, 0x00080000, (unsigned char *)"SST 4Mbit"}, 
    {SST_8Mbit,                    0, 0, 1, 1, 0, 0x00100000, (unsigned char *)"SST 8Mbit"},   
    {SST_16Mbit,                   0, 1, 1, 1, 0, 0x00200000, (unsigned char *)"SST 16Mbit"}, 

    {PMC_4Mbit,                    0, 1, 0, 1, 0, 0x00080000, (unsigned char *)"PMC 4Mbit"},  

    {MX_4Mbit,                     0, 1, 0, 0, 0, 0x00080000, (unsigned char *)"MX 4Mbit"},
    {MX_25L8006E_8Mbit,            0, 1, 0, 1, 1, 0x00100000, (unsigned char *)"MX 8Mbit"},
    {MX_25L1605_16Mbit,            0, 1, 0, 0, 0, 0x00200000, (unsigned char *)"MX 16Mbit"},
    {MX_25L3206E_32Mbit,           0, 1, 0, 1, 1, 0x00400000, (unsigned char *)"MX 32Mbit"},
    {MX_25L6405D_64Mbit,           0, 1, 0, 0, 1, 0x00800000, (unsigned char *)"MX 64Mbit"},
    {MX_25L12805D_128Mbit,         0, 1, 0, 0, 1, 0x01000000, (unsigned char *)"MX 128Mbit"},
    {MX_25L25635E_256Mbit,         0, 1, 1, 1, 1, 0x02000000, (unsigned char *)"MX 256Mbit"},
    {MX_25L6455E_64Mbit,           0, 1, 1, 1, 1, 0x00800000, (unsigned char *)"MX 64Mbit"},
    {MX_25L12855E_128Mbit,         0, 1, 1, 1, 1, 0x01000000, (unsigned char *)"MX 128Mbit"},
    {MX_25L25655F_256Mbit,         0, 1, 1, 1, 1, 0x02000000, (unsigned char *)"MX 256Mbit"},

    {SPANSION_16Mbit,              0, 1, 0, 0, 1, 0x00200000, (unsigned char *)"SPANSION 16Mbit"},
    {SPANSION_32Mbit,              0, 1, 0, 0, 0, 0x00400000, (unsigned char *)"SPANSION 32Mbit"},
    {SPANSION_64Mbit,              0, 1, 0, 0, 1, 0x00800000, (unsigned char *)"SPANSION_64Mbit"},
    {SPANSION_128Mbit,             0, 1, 0, 0, 0, 0x01000000, (unsigned char *)"SPANSION_128Mbit"},
    {SPANSION_128Mbit_64s,         0, 1, 0, 0, 1, 0x01000000, (unsigned char *)"SPANSION_128Mbit_s64"},
    {SPANSION_128Mbit_256s,        1, 0, 0, 0, 1, 0x01000000, (unsigned char *)"SPANSION_128Mbit_s256"},
    {S25FL129P_64s,                0, 1, 0, 0, 1, 0x01000000, (unsigned char *)"SPANSION_128Mbit_s64"},
    {S25FL129P_256s,               1, 0, 0, 0, 1, 0x01000000, (unsigned char *)"SPANSION_128Mbit_s256"},
    {S25FL064K_4s,                 0, 1, 1, 1, 1, 0x00800000, (unsigned char *)"S25FL064K_4s"},
    {S25FL016K_4s,                 0, 1, 1, 1, 1, 0x00200000, (unsigned char *)"S25FL016K_4s"},
    {SPANSION_S25FL164K,           0, 1, 0, 1, 1 ,0x00800000, (unsigned char *)"SPANSION_S25FL164K_64Mbit"} , 
	{SPANSION_S25FL216K,           0, 1, 0, 1, 1 ,0x01000000, (unsigned char *)"SPANSION_S25FL216K"}, 
	
    {STM_64Mbit,                   0, 1, 0, 0, 1, 0x00800000, (unsigned char *)"STMicron_64Mbit"} ,
    {STM_128Mbit,                  1, 1, 0, 0, 1, 0x01000000, (unsigned char *)"STMicron_128Mbit"},
    {STM_N25Q_128Mbit,             0, 1, 0, 0, 1, 0x01000000, (unsigned char *)"STMicron_N25Q_128Mbit"},
    {STM_N25Q064_64Mbit,           0, 1, 0, 1, 1, 0x00800000, (unsigned char *)"STMicron_N25Q064_64Mbit"},

    {EON_EN25QH16_16Mbit,          0, 1, 0, 1, 1, 0x00200000, (unsigned char *)"EON_EN25QH16_16Mbit"} ,
    {EON_EN25QH16128A_16Mbit,      0, 1, 1, 1, 1 ,0x01000000, (unsigned char *)"EON_EN25QH16_16Mbit"} ,
    {EON_EN25Q32B_32Mbit,          0, 1, 0, 1, 1, 0x00400000, (unsigned char *)"EON_EN25Q32B_32Mbit"} ,
    {EON_EN25Q64_64Mbit,           0, 1, 0, 0, 1, 0x00800000, (unsigned char *)"EON_EN25Q64_64Mbit"} ,
    {EON_EN25F16_16Mbit,           0, 1, 0, 0, 1, 0x00200000, (unsigned char *)"EON_EN25F16_16Mbit"},
    {EON_EN25Q128_128Mbit,         0, 1, 0, 0, 1, 0x01000000, (unsigned char *)"EON_EN25Q128_128Mbit"},
    {EON_EN25B64_64Mbit,           0, 1, 0, 0, 1, 0x00800000, (unsigned char *)"EON_EN25B64_64Mbit"},

    {WINBOND_W25Q80BV_8Mbit,	   0, 1, 1, 1, 1, 0x00100000, (unsigned char *)"WINBOND_W25Q80BV_8Mbit"},
    {WINBOND_W325Q128BV_128Mbit,   0, 1, 1, 1, 1, 0x01000000, (unsigned char *)"WINBOND_W325Q128BV_128Mbit"},

    {ESMT_F25L32PA_32Mbit,         0, 1, 0, 1, 1, 0x00400000, (unsigned char *)"ESMT_F25L32PA_32Mbit"} ,

    {GD25Q16B_16Mbit,              0, 1, 1, 1, 1, 0x00200000, (unsigned char *)"GD25Q16B_16Mbit"} ,
    {GD25Q64B_64Mbit,              0, 1, 1, 1, 1, 0x00800000, (unsigned char *)"GD25Q64B_64Mbit"} ,
    {GD25Q128B_128Mbit,            0, 1, 1, 1, 1, 0x01000000, (unsigned char *)"GD25Q128B_128Mbit"} ,
    {GD25Q256D_256Mbit,            0, 1, 1, 1, 1, 0x02000000, (unsigned char *)"GD25Q256D_256Mbit"} ,

    {A25L040_32Mbit,               0, 1, 0, 1, 1, 0x00400000, (unsigned char *)"AMIC 32Mbit"} ,

    {IS25LQ080B_8Mbit,             0, 1, 1, 1, 1, 0x00100000, (unsigned char *)"IS25LQ080B_8Mbit"} ,
    {IS25LQ016B_16Mbit,            0, 1, 1, 1, 1, 0x00200000, (unsigned char *)"IS25LQ016B_16Mbit"} ,
    {IS25LQ032B_32Mbit,            0, 1, 1, 1, 1, 0x00400000, (unsigned char *)"IS25LQ032B_32Mbit"} ,
    {IS25LP128_128Mbit,            0, 1, 1, 1, 1, 0x01000000, (unsigned char *)"IS25LP128_128Mbit"} ,

    {BY25D20_2Mbit,                0, 1, 1, 1, 1, 0x00040000, (unsigned char *)"BY25D20_2Mbit"} ,
    {BY25D40_4Mbit,                0, 1, 1, 1, 1, 0x00080000, (unsigned char *)"BY25D40_4Mbit"} ,
    {BY25D16_16Mbit,               0, 1, 1, 1, 1, 0x00200000, (unsigned char *)"BY25D20_16Mbit"} ,
    {BY25Q32BS_32Mbit,             0, 1, 1, 1, 1, 0x00400000, (unsigned char *)"BY25Q32BS_32Mbit"} ,
    {BY25Q64AS_64Mbit,             0, 1, 1, 1, 1, 0x00800000, (unsigned char *)"BY25Q64AS_64Mbit"} ,
    {BY25Q128AS_128Mbit,           0, 1, 1, 1, 1, 0x01000000, (unsigned char *)"BY25Q128AS_128Mbit"} ,
} ; 

#define DEV_SIZE_S  (sizeof(s_device)/sizeof(s_device_type))

#endif /* __FLASH_SPI_LIST_H__ */
