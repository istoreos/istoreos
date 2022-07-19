#ifndef __RTK_I2C_RTD1395_H__
#define __RTK_I2C_RTD1395_H__

#include "asm/arch/rbus/mis_reg.h"
#include "asm/arch/rbus/misc_reg.h"
#include "asm/arch/rbus/iso_reg.h"

#define RTK_I2C_CNT               5 // I2C1 for HDMITx

/*
#define IC0_SDA_DEL                     0x18007084
#define IC0_CON                 		0x18007D00
#define IC0_TAR                 		0x18007D04
#define IC0_SAR                 		0x18007D08
#define IC0_HS_MADDR            		0x18007D0C
#define IC0_DATA_CMD            		0x18007D10
#define IC0_SS_SCL_HCNT         		0x18007D14
#define IC0_SS_SCL_LCNT         		0x18007D18
#define IC0_FS_SCL_HCNT         		0x18007D1C
#define IC0_FS_SCL_LCNT         		0x18007D20
#define IC0_INTR_STAT           		0x18007D2C
#define IC0_INTR_MASK           		0x18007D30
#define IC0_RAW_INTR_STAT       		0x18007D34
#define IC0_RX_TL               		0x18007D38
#define IC0_TX_TL               		0x18007D3C
#define IC0_CLR_INTR            		0x18007D40
#define IC0_CLR_RX_UNDER       		    0x18007D44
#define IC0_CLR_RX_OVER         		0x18007D48
#define IC0_CLR_TX_OVER         		0x18007D4C
#define IC0_CLR_RD_REQ          		0x18007D50
#define IC0_CLR_TX_ABRT         		0x18007D54
#define IC0_CLR_RX_DONE         		0x18007D58
#define IC0_CLR_ACTIVITY       		    0x18007D5C
#define IC0_CLR_STOP_DET        		0x18007D60
#define IC0_CLR_START_DET       		0x18007D64
#define IC0_CLR_GEN_CALL        		0x18007D68
#define IC0_ENABLE              		0x18007D6C
#define IC0_STATUS              		0x18007D70
#define IC0_TXFLR               		0x18007D74
#define IC0_RXFLR               		0x18007D78
#define IC0_TX_ABRT_SOURCE      		0x18007D80
#define IC0_DMA_CR              		0x18007D88
#define IC0_DMA_TDLR            		0x18007D8C
#define IC0_DMA_RDLR            		0x18007D90
#define IC0_COMP_PARAM_1       		    0x18007DF4
#define IC0_COMP_VERSION        		0x18007DF8
#define IC0_COMP_TYPE           		0x18007DFC
//#define IC0_SDA_OUTPUT_DELAY_CTRL 	    0x1801B318

#define IC1_SDA_DEL                     0x1801B088
#define IC1_TAR                 		0x1801B304
#define IC1_SAR                 		0x1801B308
#define IC1_HS_MADDR            		0x1801B30C
#define IC1_DATA_CMD            		0x1801B310
#define IC1_SS_SCL_HCNT         		0x1801B314
#define IC1_SS_SCL_LCNT         		0x1801B318
#define IC1_FS_SCL_HCNT         		0x1801B31C
#define IC1_FS_SCL_LCNT         		0x1801B320
#define IC1_INTR_STAT           		0x1801B32C
#define IC1_INTR_MASK           		0x1801B330
#define IC1_RAW_INTR_STAT       		0x1801B334
#define IC1_RX_TL               		0x1801B338
#define IC1_TX_TL               		0x1801B33C
#define IC1_CLR_INTR            		0x1801B340
#define IC1_CLR_RX_UNDER       		    0x1801B344
#define IC1_CLR_RX_OVER         		0x1801B348
#define IC1_CLR_TX_OVER         		0x1801B34C
#define IC1_CLR_RD_REQ          		0x1801B350
#define IC1_CLR_TX_ABRT         		0x1801B354
#define IC1_CLR_RX_DONE         		0x1801B358
#define IC1_CLR_ACTIVITY       		    0x1801B35C
#define IC1_CLR_STOP_DET        		0x1801B360
#define IC1_CLR_START_DET       		0x1801B364
#define IC1_CLR_GEN_CALL        		0x1801B368
#define IC1_ENABLE              		0x1801B36C
#define IC1_STATUS              		0x1801B370
#define IC1_TXFLR               		0x1801B374
#define IC1_RXFLR               		0x1801B378
#define IC1_TX_ABRT_SOURCE      		0x1801B380
#define IC1_DMA_CR              		0x1801B388
#define IC1_DMA_TDLR            		0x1801B38C
#define IC1_DMA_RDLR            		0x1801B390
#define IC1_COMP_PARAM_1       		    0x1801B3F4
#define IC1_COMP_VERSION        		0x1801B3F8
#define IC1_COMP_TYPE           		0x1801B3FC
//#define IC0_SDA_OUTPUT_DELAY_CTRL 	    0x1801B318
*/

// I2C
unsigned int IC_SDA_DEL[]         = {ISO_I2C0_SDA_DEL       , ISO_I2C1_SDA_DEL       , MIS_I2C2_SDA_DEL       , MIS_I2C3_SDA_DEL       , MIS_I2C4_SDA_DEL       };
unsigned int IC_CON[]             = {ISO_IC0_CON            , ISO_IC1_CON            , MIS_IC2_CON            , MIS_IC3_CON            , MIS_IC4_CON            };
unsigned int IC_TAR[]             = {ISO_IC0_TAR            , ISO_IC1_TAR            , MIS_IC2_TAR            , MIS_IC3_TAR            , MIS_IC4_TAR            };
unsigned int IC_SAR[]             = {ISO_IC0_SAR            , ISO_IC1_SAR            , MIS_IC2_SAR            , MIS_IC3_SAR            , MIS_IC4_SAR            };
unsigned int IC_HS_MADDR[]        = {ISO_IC0_HS_MADDR       , ISO_IC1_HS_MADDR       , MIS_IC2_HS_MADDR       , MIS_IC3_HS_MADDR       , MIS_IC4_HS_MADDR       };
unsigned int IC_DATA_CMD[]        = {ISO_IC0_DATA_CMD       , ISO_IC1_DATA_CMD       , MIS_IC2_DATA_CMD       , MIS_IC3_DATA_CMD       , MIS_IC4_DATA_CMD       };
unsigned int IC_SS_SCL_HCNT[]     = {ISO_IC0_SS_SCL_HCNT    , ISO_IC1_SS_SCL_HCNT    , MIS_IC2_SS_SCL_HCNT    , MIS_IC3_SS_SCL_HCNT    , MIS_IC4_SS_SCL_HCNT    };
unsigned int IC_SS_SCL_LCNT[]     = {ISO_IC0_SS_SCL_LCNT    , ISO_IC1_SS_SCL_LCNT    , MIS_IC2_SS_SCL_LCNT    , MIS_IC3_SS_SCL_LCNT    , MIS_IC4_SS_SCL_LCNT    };
unsigned int IC_FS_SCL_HCNT[]     = {ISO_IC0_FS_SCL_HCNT    , ISO_IC1_FS_SCL_HCNT    , MIS_IC2_FS_SCL_HCNT    , MIS_IC3_FS_SCL_HCNT    , MIS_IC4_FS_SCL_HCNT    };
unsigned int IC_FS_SCL_LCNT[]     = {ISO_IC0_FS_SCL_LCNT    , ISO_IC1_FS_SCL_LCNT    , MIS_IC2_FS_SCL_LCNT    , MIS_IC3_FS_SCL_LCNT    , MIS_IC4_FS_SCL_LCNT    };
unsigned int IC_INTR_STAT[]       = {ISO_IC0_INTR_STAT      , ISO_IC1_INTR_STAT      , MIS_IC2_INTR_STAT      , MIS_IC3_INTR_STAT      , MIS_IC4_INTR_STAT      };
unsigned int IC_INTR_MASK[]       = {ISO_IC0_INTR_MASK      , ISO_IC1_INTR_MASK      , MIS_IC2_INTR_MASK      , MIS_IC3_INTR_MASK      , MIS_IC4_INTR_MASK      };
unsigned int IC_RAW_INTR_STAT[]   = {ISO_IC0_RAW_INTR_STAT  , ISO_IC1_RAW_INTR_STAT  , MIS_IC2_RAW_INTR_STAT  , MIS_IC3_RAW_INTR_STAT  , MIS_IC4_RAW_INTR_STAT  };
unsigned int IC_RX_TL[]           = {ISO_IC0_RX_TL          , ISO_IC1_RX_TL          , MIS_IC2_RX_TL          , MIS_IC3_RX_TL          , MIS_IC4_RX_TL          };
unsigned int IC_TX_TL[]           = {ISO_IC0_TX_TL          , ISO_IC1_TX_TL          , MIS_IC2_TX_TL          , MIS_IC3_TX_TL          , MIS_IC4_TX_TL          };
unsigned int IC_CLR_INTR[]        = {ISO_IC0_CLR_INTR       , ISO_IC1_CLR_INTR       , MIS_IC2_CLR_INTR       , MIS_IC3_CLR_INTR       , MIS_IC4_CLR_INTR       };
unsigned int IC_CLR_RX_UNDER[]    = {ISO_IC0_CLR_RX_UNDER   , ISO_IC1_CLR_RX_UNDER   , MIS_IC2_CLR_RX_UNDER   , MIS_IC3_CLR_RX_UNDER   , MIS_IC4_CLR_RX_UNDER   };
unsigned int IC_CLR_RX_OVER[]     = {ISO_IC0_CLR_RX_OVER    , ISO_IC1_CLR_RX_OVER    , MIS_IC2_CLR_RX_OVER    , MIS_IC3_CLR_RX_OVER    , MIS_IC4_CLR_RX_OVER    };
unsigned int IC_CLR_TX_OVER[]     = {ISO_IC0_CLR_TX_OVER    , ISO_IC1_CLR_TX_OVER    , MIS_IC2_CLR_TX_OVER    , MIS_IC3_CLR_TX_OVER    , MIS_IC4_CLR_TX_OVER    };
unsigned int IC_CLR_RD_REQ[]      = {ISO_IC0_CLR_RD_REQ     , ISO_IC1_CLR_RD_REQ     , MIS_IC2_CLR_RD_REQ     , MIS_IC3_CLR_RD_REQ     , MIS_IC4_CLR_RD_REQ     };
unsigned int IC_CLR_TX_ABRT[]     = {ISO_IC0_CLR_TX_ABRT    , ISO_IC1_CLR_TX_ABRT    , MIS_IC2_CLR_TX_ABRT    , MIS_IC3_CLR_TX_ABRT    , MIS_IC4_CLR_TX_ABRT    };
unsigned int IC_CLR_RX_DONE[]     = {ISO_IC0_CLR_RX_DONE    , ISO_IC1_CLR_RX_DONE    , MIS_IC2_CLR_RX_DONE    , MIS_IC3_CLR_RX_DONE    , MIS_IC4_CLR_RX_DONE    };
unsigned int IC_CLR_ACTIVITY[]    = {ISO_IC0_CLR_ACTIVITY   , ISO_IC1_CLR_ACTIVITY   , MIS_IC2_CLR_ACTIVITY   , MIS_IC3_CLR_ACTIVITY   , MIS_IC4_CLR_ACTIVITY   };
unsigned int IC_CLR_STOP_DET[]    = {ISO_IC0_CLR_STOP_DET   , ISO_IC1_CLR_STOP_DET   , MIS_IC2_CLR_STOP_DET   , MIS_IC3_CLR_STOP_DET   , MIS_IC4_CLR_STOP_DET   };
unsigned int IC_CLR_START_DET[]   = {ISO_IC0_CLR_START_DET  , ISO_IC1_CLR_START_DET  , MIS_IC2_CLR_START_DET  , MIS_IC3_CLR_START_DET  , MIS_IC4_CLR_START_DET  };
unsigned int IC_CLR_GEN_CALL[]    = {ISO_IC0_CLR_GEN_CALL   , ISO_IC1_CLR_GEN_CALL   , MIS_IC2_CLR_GEN_CALL   , MIS_IC3_CLR_GEN_CALL   , MIS_IC4_CLR_GEN_CALL   };
unsigned int IC_ENABLE[]          = {ISO_IC0_ENABLE         , ISO_IC1_ENABLE         , MIS_IC2_ENABLE         , MIS_IC3_ENABLE         , MIS_IC4_ENABLE         };
unsigned int IC_STATUS[]          = {ISO_IC0_STATUS         , ISO_IC1_STATUS         , MIS_IC2_STATUS         , MIS_IC3_STATUS         , MIS_IC4_STATUS         };
unsigned int IC_TXFLR[]           = {ISO_IC0_TXFLR          , ISO_IC1_TXFLR          , MIS_IC2_TXFLR          , MIS_IC3_TXFLR          , MIS_IC4_TXFLR          };
unsigned int IC_RXFLR[]           = {ISO_IC0_RXFLR          , ISO_IC1_RXFLR          , MIS_IC2_RXFLR          , MIS_IC3_RXFLR          , MIS_IC4_RXFLR          };
unsigned int IC_TX_ABRT_SOURCE[]  = {ISO_IC0_TX_ABRT_SOURCE , ISO_IC1_TX_ABRT_SOURCE , MIS_IC2_TX_ABRT_SOURCE , MIS_IC3_TX_ABRT_SOURCE , MIS_IC4_TX_ABRT_SOURCE };
unsigned int IC_DMA_CR[]          = {ISO_IC0_DMA_CR         , ISO_IC1_DMA_CR         , MIS_IC2_DMA_CR         , MIS_IC3_DMA_CR         , MIS_IC4_DMA_CR         };
unsigned int IC_DMA_TDLR[]        = {ISO_IC0_DMA_TDLR       , ISO_IC1_DMA_TDLR       , MIS_IC2_DMA_TDLR       , MIS_IC3_DMA_TDLR       , MIS_IC4_DMA_TDLR       };
unsigned int IC_DMA_RDLR[]        = {ISO_IC0_DMA_RDLR       , ISO_IC1_DMA_RDLR       , MIS_IC2_DMA_RDLR       , MIS_IC3_DMA_RDLR       , MIS_IC4_DMA_RDLR       };
unsigned int IC_COMP_PARAM_1[]    = {ISO_IC0_COMP_PARAM_1   , ISO_IC1_COMP_PARAM_1   , MIS_IC2_COMP_PARAM_1   , MIS_IC3_COMP_PARAM_1   , MIS_IC4_COMP_PARAM_1   };
unsigned int IC_COMP_VERSION[]    = {ISO_IC0_COMP_VERSION   , ISO_IC1_COMP_VERSION   , MIS_IC2_COMP_VERSION   , MIS_IC3_COMP_VERSION   , MIS_IC4_COMP_VERSION   };
unsigned int IC_COMP_TYPE[]       = {ISO_IC0_COMP_TYPE      , ISO_IC1_COMP_TYPE      , MIS_IC2_COMP_TYPE      , MIS_IC3_COMP_TYPE      , MIS_IC4_COMP_TYPE      };



//IC_CON
#define IC_SLAVE_DISABLE    0x0040
#define IC_RESTART_EN       0x0020
#define IC_10BITADDR_MASTER 0x0010
#define IC_10BITADDR_SLAVE  0x0008
#define IC_MASTER_MODE      0x0001

#define IC_SPEED            0x0006
#define SPEED_SS            0x0002
#define SPEED_FS            0x0004
#define SPEED_HS            0x0006

//ID_DATA
#define READ_CMD            0x0100

// INT
#define GEN_CALL_BIT        0x800
#define START_DET_BIT       0x400
#define STOP_DET_BIT        0x200
#define ACTIVITY_BIT        0x100
#define RX_DONE_BIT         0x080
#define TX_ABRT_BIT         0x040
#define RD_REQ_BIT          0x020
#define TX_EMPTY_BIT        0x010
#define TX_OVER_BIT         0x008
#define RX_FULL_BIT         0x004
#define RX_OVER_BIT         0x002
#define RX_UNDER_BIT        0x001

// STATUS
#define ST_RFF_BIT          0x10
#define ST_RFNE_BIT         0x08
#define ST_TFE_BIT          0x04
#define ST_TFNF_BIT         0x02
#define ST_ACTIVITY_BIT     0x01

/*DELAY*/
#define I2C_SDA_DEL_MASK 0x1FF
#define I2C_SDA_DEL_EN		(0x00000001<<8)
#define I2C_SDA_DEL_SEL(x)	((x & 0x1F)) /* Delay time: (unit 518ns)*/
#define SDA_DEL_518NS		1



// MIS_ISR
#define I2C0_INT                    (0x00000001<<4)
#define I2C1_INT                    (0x00000001<<26)

// IC_TX_ABRT_SOURCE
#define ABRT_SLVRD_INTX             0x8000
#define ABRT_SLV_ARB_LOST           0x4000
#define ABRT_SLV_FLUSH_TX_FIFO      0x2000
#define ABRT_ARB_LOST               0x1000
#define ABR_MASTER_DIS              0x0800
#define ABRT_10B_RD_NORSTRT         0x0400
#define ABRT_SBYTE_NORSTRT          0x0200
#define ABRT_HS_NORSTRT             0x0100
#define ABRT_SBYTE_ACKDET           0x0080
#define ABRT_HS_ACKDET              0x0040
#define ABRT_GCALL_READ             0x0020
#define ABRT_GCALL_NOACK            0x0010
#define ABRT_TXDATA_NOACK           0x0008
#define ABRT_10ADDR2_NOACK          0x0004
#define ABRT_10ADDR1_NOACK          0x0002
#define ABRT_7ADDR_NOACK            0x0001

#endif
