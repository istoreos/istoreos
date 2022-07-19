#ifndef _SB2_REG_H_
#define _SB2_REG_H_

#define SB2_WRAPPER_CTRL		0x9801a018
#define SB2_SFC_BASE			0x9801a800
#define SB2_BASE_ADDR           0x98010000
#define SB2_SFC_OPCODE			(SB2_SFC_BASE+0x00)
#define SB2_SFC_CTL				(SB2_SFC_BASE+0x04)
#define SB2_SFC_SCK				(SB2_SFC_BASE+0x08)
#define SB2_SFC_CE				(SB2_SFC_BASE+0x0C)
#define SB2_SFC_WP				(SB2_SFC_BASE+0x10)
#define SB2_SFC_POS_LATCH		(SB2_SFC_BASE+0x14)
#define SB2_SFC_WAIT_WR			(SB2_SFC_BASE+0x18)
#define SB2_SFC_EN_WR			(SB2_SFC_BASE+0x1C)
#define SB2_SFC_FAST_RD			(SB2_SFC_BASE+0x20)
#define SB2_SFC_SCK_TAP			(SB2_SFC_BASE+0x24)

#define SB2_INV_INTEN			(SB2_BASE_ADDR+0xa004)
#define SB2_REQ_MASK            (SB2_BASE_ADDR+0xa138)
#define SB2_CHIP_INFO           (SB2_BASE_ADDR+0xa204)
#define SB2_DUMMY0              (SB2_BASE_ADDR+0xa600)
#define SB2_DUMMY1              (SB2_BASE_ADDR+0xa604)
#define SB2_DUMMY2              (SB2_BASE_ADDR+0xa608)
#define SB2_DUMMY3              (SB2_BASE_ADDR+0xa60c)



#define SYS_muxpad0				(0x98012600)	//mux for nand and emmc
#define SYS_muxpad1				(0x98012604)	//mux for sdio and sd card

#define SYS_muxpad2                             (SB2_BASE_ADDR+ 0xa908) //mux for arm,lextra ej-tag
#define SYS_muxpad3                             (SB2_BASE_ADDR+ 0xa90c) //mux for arm,lextra ej-tag
#define SYS_muxpad4                             (SB2_BASE_ADDR+ 0xa910) //mux for ej-tag
#define SYS_muxpad5                             (SB2_BASE_ADDR+ 0xa914) //sf_en = 1, force gpio0-3 mux to spi pins

#define RTD129x_CHIP_REVISION_A00 (0x00000000) 
#define RTD129x_CHIP_REVISION_A01 (0x00010000)
#define RTD129x_CHIP_REVISION_B00 (0x00020000)

///////////kilopass OTP//////////////
#define OTP_EF_CTRL_ST_BUSY     (1<<16)

#endif /* _SB2_REG_H_ */
