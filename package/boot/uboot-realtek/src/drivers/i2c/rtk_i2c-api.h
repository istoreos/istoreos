#ifndef __I2C__API_H__
#define __I2C_API_H__

#include "asm/arch/io.h"
#include <asm/io.h>

#ifdef CONFIG_RTD299X
#include "rtk_i2c-rtd299x.h"
#elif defined(CONFIG_RTD1195)
#include "rtk_i2c-rtd1195.h"
#elif defined(CONFIG_RTD1295)
#include "rtk_i2c-rtd1295.h"
#elif defined(CONFIG_RTD1395)
#include "rtk_i2c-rtd1395.h"
#endif

#define wr_reg(addr, val)		rtd_outl((volatile unsigned int *)(uintptr_t)addr, val)
#define rd_reg(addr)			rtd_inl((volatile unsigned int *)(uintptr_t)addr)
#define msleep(x)			sys_wait_ms(x)

#define SET_IC_SDA_DEL(i, x)		wr_reg(IC_SDA_DEL[i], x)
#define GET_IC_SDA_DEL(i)		rd_reg(IC_SDA_DEL[i])

#define SET_IC_ENABLE(i, x)		wr_reg(IC_ENABLE[i], x)
#define SET_IC_CON(i, x)		wr_reg(IC_CON[i], x)
#define GET_IC_CON(i)			rd_reg(IC_CON[i])
#define SET_IC_SAR(i, x)		wr_reg(IC_SAR[i], x)
#define SET_IC_TAR(i, x)		wr_reg(IC_TAR[i], x)
#define GET_IC_TAR(i)			rd_reg(IC_TAR[i])
#define SET_IC_DATA_CMD(i, x)		wr_reg(IC_DATA_CMD[i], x)
#define GET_IC_DATA_CMD(i)		rd_reg(IC_DATA_CMD[i])

#define SET_IC_SS_SCL_HCNT(i, x)	wr_reg(IC_SS_SCL_HCNT[i], x)
#define SET_IC_SS_SCL_LCNT(i, x)	wr_reg(IC_SS_SCL_LCNT[i], x)
#define SET_IC_FS_SCL_HCNT(i, x)	wr_reg(IC_FS_SCL_HCNT[i], x)
#define SET_IC_FS_SCL_LCNT(i, x)	wr_reg(IC_FS_SCL_LCNT[i], x)

#define GET_IC_STATUS(i)		rd_reg(IC_STATUS[i])

#define SET_IC_INTR_MASK(i, x)		wr_reg(IC_INTR_MASK[i], x)
#define GET_IC_INTR_MASK(i)		rd_reg(IC_INTR_MASK[i])

#define GET_IC_INTR_STAT(i)		rd_reg(IC_RAW_INTR_STAT[i])
#define GET_IC_RAW_INTR_STAT(i)		rd_reg(IC_RAW_INTR_STAT[i])

#define CLR_IC_INTR(i)			rd_reg(IC_CLR_INTR[i])
#define CLR_IC_RX_UNDER(i)		rd_reg(IC_CLR_RX_UNDER[i])
#define CLR_IC_TX_OVER(i)		rd_reg(IC_CLR_TX_OVER[i])
#define CLR_IC_RD_REQ(i)		rd_reg(IC_CLR_RD_REQ[i])
#define CLR_IC_RX_DONE(i)		rd_reg(IC_CLR_RX_DONE[i])
#define CLR_IC_ACTIVITY(i)		rd_reg(IC_CLR_ACTIVITY[i])
#define CLR_IC_GEN_CALL(i)		rd_reg(IC_CLR_GEN_CALL[i])
#define CLR_IC_TX_ABRT(i)		rd_reg(IC_CLR_TX_ABRT[i])
#define CLR_IC_STOP_DET(i)		rd_reg(IC_CLR_STOP_DET[i])

#define GET_IC_COMP_PARAM_1(i)		rd_reg(IC_COMP_PARAM_1[i])

#define GET_IC_TXFLR(i)			rd_reg(IC_TXFLR[i])
#define GET_IC_RXFLR(i)			rd_reg(IC_RXFLR[i])

#define GET_IC_RX_TL(i)			rd_reg(IC_RX_TL[i])
#define GET_IC_TX_TL(i)			rd_reg(IC_TX_TL[i])
#define SET_IC_RX_TL(i, x)		wr_reg(IC_RX_TL[i], x)
#define SET_IC_TX_TL(i, x)		wr_reg(IC_TX_TL[i], x)

#define GET_IC_TX_ABRT_SOURCE(i)	rd_reg(IC_TX_ABRT_SOURCE[i])

#define NOT_TXFULL(i)			(GET_IC_STATUS(i) & ST_TFNF_BIT)
#define NOT_RXEMPTY(i)			(GET_IC_STATUS(i) & ST_RFNE_BIT)
#define IS_TXEMPTY(i)			(GET_IC_STATUS(i) & TX_EMPTY_BIT)

#endif  /*__RTK_I2C_API_H__*/
