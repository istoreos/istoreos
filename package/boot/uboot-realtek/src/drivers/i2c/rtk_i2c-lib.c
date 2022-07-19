#include <common.h>
#include "rtk_i2c-api.h"
#include "rtk_i2c-lib.h"
#include "rtk_i2c-pow.h"

/*#include "rtk_i2c-recover.h"*/

#include <asm/arch/io.h>
#include <asm/arch/rbus/iso_reg.h>
#include <asm/arch/rbus/sb2_reg.h>

unsigned char i2c_init_rdy[RTK_I2C_CNT] = {0};
unsigned int  spd;
unsigned int i2c_current_speed[RTK_I2C_CNT] = {0};

#define FIFO_THRESHOLD                   4
#define DEFAULT_SPEED                    100	/*must use 400KHz, then NETWORK ping ok, and AMP, YAMAHA will ok too, gene@20110714*/


#ifdef CONFIG_RTD1395

#define I2C0_REG		0x9804E004
#define I2C0_MUX_MASK	~(0x00000003|0x0000000C)
#define I2C0_MUX_EN		(0x00000003&((0x1)<<0))|(0x0000000C&((0x1)<<2))

#define I2C1_REG		0x9804E004
#define I2C1_MUX_MASK	~(0x00000300|0x00000C00)
#define I2C1_MUX_EN		(0x00000300&((0x1)<<8))|(0x00000C00&((0x1)<<10))

#define I2C5_REG		0x9804E014
#define I2C5_MUX_MASK	~(0x00000003|0x000000C0)
#define I2C5_MUX_EN		(0x00000003&((0x10)<<0))|(0x000000C0&((0x10)<<6))

#elif defined(CONFIG_RTD1295)

#define I2C0_REG		ISO_MUXPAD0_reg
#define I2C0_MUX_MASK	~(ISO_MUXPAD0_i2c_sda_0_mask|ISO_MUXPAD0_i2c_scl_0_mask)
#define I2C0_MUX_EN		ISO_MUXPAD0_i2c_sda_0(0x1)|ISO_MUXPAD0_i2c_scl_0(0x1)

#define I2C1_REG		ISO_MUXPAD1_reg
#define I2C1_MUX_MASK	~(ISO_MUXPAD1_i2c_sda_1_mask|ISO_MUXPAD1_i2c_scl_1_mask)
#define I2C1_MUX_EN		ISO_MUXPAD1_i2c_sda_1(0x1)|ISO_MUXPAD1_i2c_scl_1(0x1)

#define I2C5_REG		SB2_MUXPAD3_reg
#define I2C5_MUX_MASK	~(SB2_MUXPAD3_i2c_sda_5_mask | SB2_MUXPAD3_i2c_scl_5_mask)
#define I2C5_MUX_EN		SB2_MUXPAD3_i2c_sda_5(0x1)|SB2_MUXPAD3_i2c_scl_5(0x1)

#endif



#define i2c_print(fmt, args...)	/*printf(fmt,## args)*/
#define i2c_pprint(fmt, args...)	/*printf(fmt,## args)*/
#define i2c_ppprint(fmt, args...)	/*printf(fmt,## args)*/

/*======================================================================
 * Func : I2CN_Init
 *
 * Desc : Init I2CN
 *
 * Parm : Bus ID
 *
 * Retn : N/A
 *======================================================================*/
void I2CN_Init(int Bus_ID)
{
	int i = Bus_ID;
	unsigned char rx_fifo_depth;

	rtk_i2c_set_pow(Bus_ID);

	if (Bus_ID >= RTK_I2C_CNT)
		return;
	if (i2c_init_rdy[i] == 1)
		return;

	/*Set I2C pinmux*/
	switch (Bus_ID) {
	case 0:
		rtd_maskl(I2C0_REG, I2C0_MUX_MASK, I2C0_MUX_EN);
		break;
	case 1:
		rtd_maskl(I2C1_REG, I2C1_MUX_MASK, I2C1_MUX_EN);
		break;
	case 2:
		rtd_maskl(SB2_MUXPAD2_reg, ~(SB2_MUXPAD2_tp1_clk_mask | SB2_MUXPAD2_tp1_sync_mask),
				SB2_MUXPAD2_tp1_clk(0x3) | SB2_MUXPAD2_tp1_sync(0x3));
		break;
	case 3:
		rtd_maskl(SB2_MUXPAD2_reg, ~(SB2_MUXPAD2_tp1_valid_mask | SB2_MUXPAD2_tp1_data_mask),
				SB2_MUXPAD2_tp1_valid(0x3) | SB2_MUXPAD2_tp1_data(0x3));
		break;
	case 4:
		rtd_maskl(SB2_MUXPAD3_reg, ~(SB2_MUXPAD3_i2c_sda_4_mask | SB2_MUXPAD3_i2c_scl_4_mask),
				SB2_MUXPAD3_i2c_sda_4(0x1) | SB2_MUXPAD3_i2c_scl_4(0x1));
		break;
	case 5:
		rtd_maskl(I2C5_REG, I2C1_MUX_MASK, I2C5_MUX_EN);
		break;
	default:
		break;
	}

	rx_fifo_depth = ((GET_IC_COMP_PARAM_1(Bus_ID) >>  8) & 0xFF) + 1;
	SET_IC_ENABLE(Bus_ID, 0);
	SET_IC_INTR_MASK(Bus_ID, 0);                /* disable all interrupt*/
	SET_IC_CON(Bus_ID, IC_SLAVE_DISABLE | IC_RESTART_EN | SPEED_SS | IC_MASTER_MODE);
	SET_IC_TX_TL(Bus_ID, FIFO_THRESHOLD);
	SET_IC_RX_TL(Bus_ID, rx_fifo_depth - FIFO_THRESHOLD);
	if (!i2c_current_speed[Bus_ID])
		i2c_current_speed[Bus_ID] = DEFAULT_SPEED;

	I2C_SetSpeed(Bus_ID, i2c_current_speed[Bus_ID]);

	SET_IC_SDA_DEL(Bus_ID, 0xff000101);	/*adjust I2c timing.*/

	i2c_init_rdy[Bus_ID] = 1;
}

/*======================================================================
 * Func : I2C_Init
 *
 * Desc : Init I2C
 *
 * Parm : N/A
 *
 * Retn : N/A
 *======================================================================*/
void I2C_Init(void)
{
	int i;

	for (i = 0; i < RTK_I2C_CNT; i++) {
		i2c_current_speed[i] = 0;
		I2CN_Init(i);
	}
}

/*======================================================================
 * Func : I2CN_UnInit
 *
 * Desc : Uninit I2CN
 *
 * Parm : Bus_ID
 *
 * Retn : N/A
 *======================================================================*/
void I2CN_UnInit(int Bus_ID)
{
	if (Bus_ID >= RTK_I2C_CNT)
		return;

	if (i2c_init_rdy[Bus_ID] == 0)
		return;

	SET_IC_ENABLE(Bus_ID, 0);
	SET_IC_INTR_MASK(Bus_ID, 0);

	/*Set I2C pinmux*/
	switch (Bus_ID) {
	case 0:
		rtd_maskl(I2C0_REG, I2C0_MUX_MASK, 0);
		break;
	case 1:
		rtd_maskl(I2C1_REG, I2C1_MUX_MASK, 0);
		break;
	case 2:
		rtd_maskl(SB2_MUXPAD2_reg, ~(SB2_MUXPAD2_tp1_clk_mask | SB2_MUXPAD2_tp1_sync_mask),
				SB2_MUXPAD2_tp1_clk(0x0) | SB2_MUXPAD2_tp1_sync(0x0));
		break;
	case 3:
		rtd_maskl(SB2_MUXPAD2_reg, ~(SB2_MUXPAD2_tp1_valid_mask | SB2_MUXPAD2_tp1_data_mask),
				SB2_MUXPAD2_tp1_valid(0x0) | SB2_MUXPAD2_tp1_data(0x0));
		break;
	case 4:
		rtd_maskl(SB2_MUXPAD3_reg, ~(SB2_MUXPAD3_i2c_sda_4_mask | SB2_MUXPAD3_i2c_scl_4_mask),
				SB2_MUXPAD3_i2c_sda_4(0x0) | SB2_MUXPAD3_i2c_scl_4(0x0));
		break;
	case 5:
		rtd_maskl(I2C5_REG, I2C1_MUX_MASK, 0);
		break;
	default:
		break;
	}

	i2c_init_rdy[Bus_ID] = 0;
}

/*======================================================================
 * Func : I2C_UnInit
 *
 * Desc : Uninit I2C
 *
 * Parm : N/A
 *
 * Retn : N/A
 *======================================================================*/
void I2C_UnInit(void)
{
	int i;

	for (i = 0; i < RTK_I2C_CNT; i++)
		I2CN_UnInit(i);
}

/*======================================================================
 * Func : I2C_Write_EX
 *
 * Desc : Single I2C Write Function (Extended Version)
 *
 * Parm : Id        : bus id
 *        Addr      : target address (7bits)
 *        nData     : number of bytes to write
 *        pData     : data to write
 *
 * Retn : S_OK / S_FALSE
 *======================================================================*/
int I2C_Write_EX(
	unsigned char	Id,
	unsigned short	Addr,
	unsigned short	nData,
	unsigned char	*pData,
	unsigned int	flag
)
{
	return I2C_StartXfer(Id, Addr, nData, pData, 0, NULL, flag);
}

/*======================================================================
 * Func : I2C_Read_EX
 *
 * Desc : Single I2C Read Function
 *
 * Parm : id           : bus id
 *        Addr         : Target Address (7bits)
 *        nSubAddr     : number of bytes of sub address
 *        pSubAddr     : sub address
 *        nData        : numver of bytes to read
 *        pData        : data to read
 *
 * Retn : S_OK / S_FALSE
 *======================================================================*/
int I2C_Read_EX(
	unsigned char	Id,
	unsigned short	Addr,
	unsigned short	nSubAddr,
	unsigned char	*pSubAddr,
	unsigned short	nData,
	unsigned char	*pData,
	unsigned int	flag
)
{
	return I2C_StartXfer(Id, Addr, nSubAddr, pSubAddr, nData, pData, flag);
}

/*======================================================================
 * Func : I2C_GetSpeed
 *
 * Desc : this function is used to get speed of i2c adapter
 *
 * Parm : Id           : bus id
 *
 *
 * Retn : i2c current speed
 *======================================================================*/

unsigned int I2C_GetSpeed(unsigned int ID)
{
	return i2c_current_speed[ID];
}

/*======================================================================
 * Func : I2C_SetSpeed
 *
 * Desc : this function is used to change the operation speed of i2c adapter
 *
 * Parm : Id           : bus id
 *        KHz          : operation speed
 *
 * Retn : S_OK / S_FALSE
 *======================================================================*/
int I2C_SetSpeed(unsigned int ID, unsigned int speed)
{
	unsigned int scl_time;
	unsigned int div_h;
	unsigned int div_l;
	unsigned long sda_del;

	if (speed < 10 || speed > 800) {
		printf("[I2C%d] warning, speed %d out of range,",
			ID, speed);
		printf("speed should between 10 ~ 800KHz\n");
		return -1;
	}

	scl_time = (1000000 / speed) / 2; /* the time ns need for SCL high/low */

	if (scl_time % 37) {
		if ((scl_time % 37) > 18)
			scl_time += (37 - (scl_time % 37));
		else
			scl_time -= (scl_time % 37);
	}

	/*
	 * 27MHz crystal generate one clock 37ns,
	 * for synopsys design ware ip v1.14a, SCL_LCNT need -1,
	 * SCL_HCNT need -8, 400KHz SCL Low required min 1.3 us
	 */
	if (speed < 400) {
		div_h = (scl_time / 37) - 8;
		div_l = (scl_time / 37) - 1;
	} else {
		div_h = 24;
		div_l = 34;
	}

	if (div_h >= 0xFFFF || div_h == 0 || div_l >= 0xFFFF || div_l == 0) {
		printf("[I2C%d] fatal, set speed failed : ", ID);
		printf("divider divider out of range.");
		printf("div_h = %d, div_l = %d\n", div_h, div_l);
		return -1;
	}

	SET_IC_ENABLE(ID, 0);

	if (speed <= 100) {
		SET_IC_CON(ID, (GET_IC_CON(ID) &
			(~IC_SPEED)) | SPEED_SS);
		SET_IC_SS_SCL_HCNT(ID, div_h);
		SET_IC_SS_SCL_LCNT(ID, div_l);
	} else {
		SET_IC_CON(ID, (GET_IC_CON(ID) &
			(~IC_SPEED)) | SPEED_FS);
		SET_IC_FS_SCL_HCNT(ID, div_h);
		SET_IC_FS_SCL_LCNT(ID, div_l);
	}

	i2c_current_speed[ID] = speed;

	/*Set SDA delay time */
	sda_del = GET_IC_SDA_DEL(ID) & ~I2C_SDA_DEL_MASK;
	sda_del |= I2C_SDA_DEL_EN | I2C_SDA_DEL_SEL(SDA_DEL_518NS);
	SET_IC_SDA_DEL(ID, sda_del);

	return 0;
}

/*======================================================================
 * Func : I2C_Transfer_EX
 *
 * Desc : this function supports atomic multiple messages read/write
 *        via i2c message data structure
 *
 * Parm : Id           : bus id
 *        pMsgs       : messages
 *        nMsg        : number of messages
 *
 * Retn : S_OK / S_FALSE
 *======================================================================*/
int I2C_StartXfer(
	unsigned char	Id,
	unsigned short	Addr,
	unsigned short	nSubAddr,
	unsigned char	*pSubAddr,
	unsigned short	nData,
	unsigned char	*pData,
	unsigned int	flag
)
{
	int i = Id;
	int tx_len = 0;
	int rx_len = 0;
	int ret = S_FALSE;
	int delay_loop = 0;
	int event;

	if (i >= RTK_I2C_CNT)
		return S_FALSE;

	/*I2C_Init();*/

	SET_IC_TAR(i, Addr & 0x7F);
	SET_IC_CON(i, GET_IC_CON(i) & (~IC_10BITADDR_MASTER));
	CLR_IC_INTR(i);
	SET_IC_ENABLE(i, 1);

	tx_len = 0;

#define TxComplete()        (tx_len >= nData + nSubAddr)    /* it should add the same number of read command to tx fifo*/
#define RxComplete()        (rx_len >= nData)

	i2c_pprint("s");

	while (delay_loop++ < 10000) {
		/*check status*/
		event = GET_IC_INTR_STAT(i);

		if (event & TX_ABRT_BIT) {
			i2c_ppprint("tx abort!!!!\n");
			break;
		}
	/*	else if ( TxComplete() && (flag & NO_READ))
	 *	{
	 *		i2c_pprint("Complete!!!!\n");
	 *		ret = S_OK;
	 *		break;
	 *	}
	 */
		if ((event & STOP_DET_BIT) || (nData && RxComplete())) {
			if (RxComplete()) {
				i2c_pprint("Complete!!!!\n");
				ret = S_OK;
			} else {
				i2c_ppprint("Xmit not Complete!!!!\n");
			}
			break;
		}

		/*TX Thread*/
		while (!TxComplete() && NOT_TXFULL(i)) {
			if (tx_len < nSubAddr) {
					if (flag & NON_STOP) {
						SET_IC_DATA_CMD(i, pSubAddr[tx_len] | (0x1 << 10));

						if (nData == 0) { /*write*/
							udelay(50);
							goto done;
						}
					} else {
						if ((tx_len == (nSubAddr - 1)) && (flag & NO_READ)) {
							SET_IC_DATA_CMD(i, pSubAddr[tx_len] | (0x1 << 9));/* last byte, STOP*/
							i2c_pprint("S");
							/*udelay(90);// TX_ABRT_BIT event waiting time*/
						} else {
							SET_IC_DATA_CMD(i, pSubAddr[tx_len]);
						}
					}
				} else {
					if (tx_len == nData)
						SET_IC_DATA_CMD(i, (READ_CMD | (0x1 << 9)));
					else
						SET_IC_DATA_CMD(i, READ_CMD);  /* send read command to rx fifo*/
				}

				tx_len++;
			}
			i2c_pprint("w");
			udelay(50);
			/* RX Thread*/
			while (!RxComplete() && NOT_RXEMPTY(i)) {
				pData[rx_len++] = (unsigned char)(GET_IC_DATA_CMD(i) & 0xFF);
				udelay(50);
				i2c_pprint("r");
			}
		}

		i2c_pprint("e");

		if (ret != S_OK) {
			i2c_ppprint("[I2C%d] timeout\n", i);
#if 0
	if (i2c_bus_jam_detect(i)) {
		i2c_ppprint("[I2C%d] try to bus jam recovery\n", i);
		/*i2c_bus_jam_recover(i);   // try to recover*/
	}
#endif
	}

done:
	CLR_IC_INTR(i);
	SET_IC_ENABLE(i, 0);

	return ret;

#undef TxComplete
#undef RxComplete
}

unsigned char I2C_GetBusCount(void)
{
	return RTK_I2C_CNT;
}
