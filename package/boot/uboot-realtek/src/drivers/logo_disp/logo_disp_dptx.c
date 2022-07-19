#include <common.h>
#include <asm/arch/fw_info.h>
#include <asm/arch/system.h>
#include <asm/arch/io.h>
#include <asm/arch/rbus/iso_reg.h>
#include <asm/arch/rbus/crt_reg.h>
#include <asm/arch/rbus/edp_reg.h>
#include <asm/arch/rbus/lvds_aif_reg.h>
#include <asm/arch/rbus/lvds_pif_reg.h>
#include <asm/arch/platform_lib/board/gpio.h>
#include <asm/arch/factorylib.h>

#include "rtk_rpc.h"
#include "rtk_edid.h"

#define CRT_BASE 0x98000000
#define VO_BASE 0x98005000
#define LVDS_BASE 0x98009400
//#define VO_EN

#define EDID_LENGTH 128
//#define mdelay(_msec)      spin((_msec) * 1000)
//#define udelay(_usec)      spin(_usec)

#define BOOT_TVSYSTEM_FILE_NAME		FACTORY_HEADER_FILE_NAME"video_rpc.bin"
#define BOOT_CHECKSUM_FILE_NAME		FACTORY_HEADER_FILE_NAME"edid_checksum.bin"

extern int add_cea_modes(struct edid *edid);

uchar checksum_blk0=0;
uchar checksum_blk1=0;
enum
{
	DP_FORMAT_1024_768 = 0,
	DP_FORMAT_720P_60,
	DP_FORMAT_1080P_60,
	DP_FORMAT_2160P_30,
	DP_FORMAT_2160P_60,
};

struct VIDEO_FORMAT_CONVERTER vid_support_map[]=
{	
	{VO_STANDARD_HDTV_720P_60, DP_FORMAT_720P_60},  //720
	{VO_STANDARD_HDTV_1080I_60, DP_FORMAT_1080P_60},  //1080i
	{VO_STANDARD_HDTV_1080P_60, DP_FORMAT_1080P_60}//1080p
};

enum
{
	_DP_ONE_LANE = 1,
	_DP_TWO_LANE = 2,
	_DP_FOUR_LANE = 4,
};


enum
{
	_DP_TX_TRAINING_NO_RESULT = 0x00,
	_DP_TX_TRAINING_PATTERN1_FAIL,
	_DP_TX_TRAINING_PATTERN2_FAIL,
	_DP_TX_TRAINING_PATTERN1_ADJUST_FAIL,
	_DP_TX_TRAINING_PATTERN2_ADJUST_FAIL,
	_DP_TX_TRAINING_PATTERN1_PASS,
	_DP_TX_TRAINING_PATTERN2_PASS,
	_DP_TX_TRAINING_PASS,
	_DP_TX_TRAINING_FAIL,
};

unsigned char tDPTX_DRV_TABLE[48] =
{
	// Pre-emphasis->        0                    1                    2                    3
	// VoltageSwing
	/*    0    */      0x00, 0x00, 0x03,    0x00, 0x07, 0x05,    0x00, 0x0C, 0x05,    0x01, 0x09, 0x06,
	/*    1    */      0x00, 0x00, 0x05,    0x00, 0x07, 0x05,    0x00, 0x0C, 0x05,    0x00, 0x0C, 0x05,
	/*    2    */      0x00, 0x00, 0x09,    0x00, 0x0C, 0x09,    0x00, 0x0C, 0x09,    0x00, 0x0C, 0x09,
	/*    3    */      0x00, 0x00, 0x0E,    0x00, 0x00, 0x0E,    0x00, 0x00, 0x0E,    0x00, 0x00, 0x0E,
};

struct dptx_laneX_status
{
	unsigned char ucLane0Adjust;
	unsigned char ucLane1Adjust;
	unsigned char ucLane2Adjust;
	unsigned char ucLane3Adjust;
	unsigned char ucLane01LTStatus;
	unsigned char ucLane23LTStatus;
	unsigned char ucAdjustReqLane01;
	unsigned char ucAdjustReqLane23;
};

struct dptx_info
{
	unsigned char resolution;
	unsigned char lanecount;
	unsigned char bandwidth;
	unsigned char ssc_en;
	unsigned short ltp1_check;
	unsigned short ltp2_check;

	unsigned short clock;
};

struct dptx_laneX_status laneX;
struct dptx_info dpinfo;
unsigned char dptx_edid[EDID_LENGTH*2];
unsigned int LT_RESAULT;
unsigned int resolution;

static int dptx_write(unsigned int addr, unsigned char length, unsigned char *data)
{
	unsigned char ucAddrH, ucAddrM, ucAddrL;
	int i;

	ucAddrH = (addr>>16) & 0xFF;
	ucAddrM = (addr>>8) & 0xFF;
	ucAddrL = addr & 0xFF;

	set_AUX_FIFO_CTRL_reg(get_AUX_FIFO_CTRL_reg | 0x3);
	set_AUX_IRQ_EVENT_reg(0x3F);
	set_AUXTX_REQ_CMD_reg(ucAddrH);
	set_AUXTX_REQ_ADDR_M_reg(ucAddrM);
	set_AUXTX_REQ_ADDR_L_reg(ucAddrL);
	set_AUXTX_REQ_LEN_reg(((length > 0) ? (length - 1) : 0));
	for(i=0; i<length; i++)
		set_AUXTX_REQ_DATA_reg(data[i]);

	set_AUXTX_TRAN_CTRL_reg(get_AUXTX_TRAN_CTRL_reg | 0x1);
	udelay(400);

	for(i=0; i<25; i++) {
		mdelay(5);
		if((get_AUX_IRQ_EVENT_reg & _BIT5) == _BIT5) {
			set_AUX_IRQ_EVENT_reg(0x3F);
			set_AUX_FIFO_CTRL_reg(get_AUX_FIFO_CTRL_reg | 0x3);
			return 0;
		} else if((get_AUX_IRQ_EVENT_reg & _BIT1) == _BIT1) {
			set_AUX_IRQ_EVENT_reg(0x3F);
			set_AUX_FIFO_CTRL_reg(get_AUX_FIFO_CTRL_reg | 0x3);
			printf("aux write fail\n");
			return -1;
		}
	}
	set_AUX_IRQ_EVENT_reg(0x3F);
	set_AUX_FIFO_CTRL_reg(get_AUX_FIFO_CTRL_reg | 0x3);
	printf("aux write fail\n");
	return -1;
}

static int dptx_read(unsigned int addr, unsigned char length, unsigned char *data)
{
	unsigned char ucAddrH, ucAddrM, ucAddrL;
	int i;

	ucAddrH = (addr>>16) & 0xFF;
	ucAddrM = (addr>>8) & 0xFF;
	ucAddrL = addr & 0xFF;
	
	set_AUX_FIFO_CTRL_reg(get_AUX_FIFO_CTRL_reg | 0x3);
	set_AUX_IRQ_EVENT_reg(0x3F);
	set_AUXTX_REQ_CMD_reg(ucAddrH);
	set_AUXTX_REQ_ADDR_M_reg(ucAddrM);
	set_AUXTX_REQ_ADDR_L_reg(ucAddrL);
	set_AUXTX_REQ_LEN_reg(((length > 0) ? (length - 1) : 0));
	set_AUXTX_TRAN_CTRL_reg(get_AUXTX_TRAN_CTRL_reg | 0x1);

	udelay(400);

	for(i=0; i<25; i++) {
		mdelay(1);
		if((get_AUX_IRQ_EVENT_reg & _BIT5) == _BIT5) {
			set_AUX_IRQ_EVENT_reg(0x3F);
			set_AUX_FIFO_CTRL_reg(get_AUX_FIFO_CTRL_reg | 0x3);
			for(i=0; i<length; i++)
				data[i] = get_AUX_REPLY_DATA_reg;
			return 0;
		} else if((get_AUX_IRQ_EVENT_reg & _BIT1) == _BIT1) {
			set_AUX_IRQ_EVENT_reg(0x3F);
			set_AUX_FIFO_CTRL_reg(get_AUX_FIFO_CTRL_reg | 0x3);
			printf("aux read fail\n");
			return -1;
		}
	}
	set_AUX_IRQ_EVENT_reg(0x3F);
	set_AUX_FIFO_CTRL_reg(get_AUX_FIFO_CTRL_reg | 0x3);
	printf("aux read fail\n");
	return -1;
}

static int dptx_aux_write(unsigned int addr, unsigned char length, unsigned char *data)
{
	addr = addr | (0x80 << 16);
	return dptx_write(addr, length, data);
}

static int dptx_aux_read(unsigned int addr, unsigned char length, unsigned char *data)
{
	addr = addr | (0x90 << 16);
	return dptx_read(addr, length, data);
}

static int dptx_i2c_write(unsigned char addr, unsigned char length, unsigned char *data, unsigned char bMOT)
{
	unsigned int ucAddr;

	ucAddr = ((0x00 | bMOT<<6) << 16) | 0x00 << 8 | addr;

	return dptx_write(ucAddr, length, data);
}

static int dptx_i2c_read(unsigned char addr, unsigned char length, unsigned char *data, unsigned char bMOT)
{
	unsigned int ucAddr;

	ucAddr = ((0x10 | bMOT<<6) << 16) | 0x00 << 8 | addr;

	return dptx_read(ucAddr, length, data);
}

static void dptx_read_edid(unsigned char *data, int length)
{
	int i;//, j;
	for(i=0; i<length; i++)
		data[i] = 0;
	dptx_i2c_write(0x50, 1, data, 0);

	dptx_i2c_write(0x50, 1, data, 1);
	for(i=0; i<length/16; i++) {
		dptx_i2c_read(0x50, 16, (data+i*16), 1);
//		for(j=0; j<16; j++)
//			printf("0x%x, ", data[i*16+j]);
//		printf("\n");
	}
}

static void dptx_set_signallevel(unsigned char lane, unsigned char swing, unsigned char emphasis)
{
	unsigned int val;
	unsigned char *tbl, idx;

	tbl = tDPTX_DRV_TABLE;
	
	if(swing + emphasis > 3) {
		if(swing < 4) {
			emphasis = 3 - swing;
		} else {
			swing = 3;
			emphasis = 0;
		}
	}
	idx = (swing * 4 + emphasis) * 3;

	val = get_AIF_EDP_2_reg;
	val = val & ~(0x100000 | 0xF<<(lane*4));
	val = val | tbl[idx]<<16 | tbl[idx+1]<<(lane*4) | 0x00f00000;
	set_AIF_EDP_2_reg(val);

	val = get_AIF_EDP_3_reg;
	val = val & ~(0xF<<(lane*4)) & ~0xFF000000;
	val = val | tbl[idx+2]<<(lane*4) | 0x1F000000;
	set_AIF_EDP_3_reg(val);
}

static void dptx_mlphy_set(void)
{
	unsigned char swing, emphasis;
	
	swing = laneX.ucLane0Adjust & 0x3;
	emphasis = (laneX.ucLane0Adjust & 0x18) >> 3;
	dptx_set_signallevel(0, swing, emphasis);

	swing = laneX.ucLane1Adjust & 0x3;
	emphasis = (laneX.ucLane1Adjust & 0x18) >> 3;
	dptx_set_signallevel(1, swing, emphasis);
}

int dptx_link_config(void)
{
//	unsigned char data[16];

/*	data[0] = 0x4C;
	data[1] = 0xE0;
	data[2] = 0x00;

	ret = dptx_aux_write(0x300, 3, data);
	if(ret)
		return ret;
	ret = dptx_aux_read(0, 16, data);
	if(ret)
		return ret;*/

	LT_RESAULT = _DP_TX_TRAINING_NO_RESULT;
	
	laneX.ucLane0Adjust = 0;
	laneX.ucLane1Adjust = 0;
	dptx_mlphy_set();

	return 0;
}

static int dptx_train_pattern1(void)
{
	unsigned char data[10];
	int i;

	if(LT_RESAULT == _DP_TX_TRAINING_NO_RESULT) {
		set_DPTX_ML_PAT_SEL_reg(0x10);
		set_DPTX_ML_PAT_SEL_reg(0x11);
		data[0] = 0x21;
		data[1] = laneX.ucLane0Adjust;
		data[2] = laneX.ucLane1Adjust;
		data[3] = data[4] = 0;
		dptx_aux_write(0x102, 5, data);
	} else {
		dptx_mlphy_set();
		data[0] = laneX.ucLane0Adjust;
		data[1] = laneX.ucLane1Adjust;
		data[2] = data[3] = 0;
		dptx_aux_write(0x103, 4, data);
	}

	mdelay(5);
	dptx_aux_read(0x202, 6, data);
	
	laneX.ucAdjustReqLane01 = data[4];
	laneX.ucAdjustReqLane23 = data[5];
	laneX.ucLane0Adjust = (data[4] & 0x3) | (data[4] & 0xc) << 1;
	laneX.ucLane1Adjust = (data[4] & 0x30)>>4 | (data[4] & 0xC0)>>3;
	printf("adjust : 0x%x, 0x%x\n", laneX.ucLane0Adjust, laneX.ucLane1Adjust);

	printf("pattern1 : ");
	for(i=0; i<5; i++)
		printf("0x%x ", data[i]);
	printf("\n");

	if((data[0] | data[1]<<8)==dpinfo.ltp1_check)
		return _DP_TX_TRAINING_PATTERN1_PASS;
	else
		return _DP_TX_TRAINING_PATTERN1_FAIL;
}

static int dptx_train_pattern2(void)
{
	unsigned char data[10];
	int i;

	if(LT_RESAULT == _DP_TX_TRAINING_PATTERN1_PASS) {
		set_DPTX_ML_PAT_SEL_reg(0x20);
		set_DPTX_ML_PAT_SEL_reg(0x21);
		data[0] = 0x22;
		data[1] = laneX.ucLane0Adjust;
		data[2] = laneX.ucLane1Adjust;
		data[3] = data[4] = 0;
		dptx_aux_write(0x102, 5, data);
	} else {
		dptx_mlphy_set();
		data[0] = laneX.ucLane0Adjust;
		data[1] = laneX.ucLane1Adjust;
		data[2] = data[3] = 0;
		dptx_aux_write(0x103, 4, data);
	}
	
	mdelay(5);
	dptx_aux_read(0x202, 6, data);
	laneX.ucAdjustReqLane01 = data[4];
	laneX.ucAdjustReqLane23 = data[5];
	laneX.ucLane0Adjust = (data[4] & 0x3) | (data[4] & 0xc) << 1;
	laneX.ucLane1Adjust = (data[4] & 0x30)>>4 | (data[4] & 0xC0)>>3;
	printf("adjust : 0x%x, 0x%x\n", laneX.ucLane0Adjust, laneX.ucLane1Adjust);

	printf("pattern2 : ");
	for(i=0; i<5; i++)
		printf("0x%x ", data[i]);
	printf("\n");
	
	if((data[0] | data[1]<<8)==dpinfo.ltp2_check)
		return _DP_TX_TRAINING_PATTERN2_PASS;
	else
		return _DP_TX_TRAINING_PATTERN2_FAIL;
}

void dptx_train_patternend(void)
{
	unsigned char data[10];

	data[0] = 0;
	dptx_aux_write(0x102, 1, data);

}

int dptx_link_training(void)
{
	unsigned char data[10];
	int ret, i;

	ret = dptx_link_config();
	if(ret)
		return ret;
	
	// Power up Downstream
	data[0] = 1;
	dptx_aux_write(0x600, 1, data);
	data[0] = 0xa; 
	dptx_aux_write(0x100, 1, data);
	data[0] = 0x80 | dpinfo.lanecount; 
	dptx_aux_write(0x101, 1, data);

	for(i=0; i<5; i++) {
		LT_RESAULT = dptx_train_pattern1();
		if(LT_RESAULT == _DP_TX_TRAINING_PATTERN1_PASS) {
//			dptx_train_patternend();
			break;
//			return -1;
		}
	}
	if(LT_RESAULT != _DP_TX_TRAINING_PATTERN1_PASS)
		return -1;
	for(i=0; i<5; i++) {
		LT_RESAULT = dptx_train_pattern2();
		if(LT_RESAULT == _DP_TX_TRAINING_PATTERN2_PASS)
			break;
		mdelay(100);
		printf("Train pattern 2 fail\n");
	}
	dptx_train_patternend();
	if(LT_RESAULT == _DP_TX_TRAINING_PATTERN2_PASS)
		return 0;
	else
		return -1;

}

static int dptx_hpd(void)
{
	int ret=0;
#ifdef CONFIG_DPTX_HPD_IGPIO_NUM
	ret = getISOGPIO(CONFIG_DPTX_HPD_IGPIO_NUM);
	return ret;
#else
	return ret;
#endif
}

static void dptx_sst_msa_setting(int res)
{
	set_DP_RESET_CTRL_reg(get_DP_RESET_CTRL_reg | _BIT6);
	set_DP_RESET_CTRL_reg(get_DP_RESET_CTRL_reg & ~(_BIT6));

	if(res == DP_FORMAT_720P_60) {
		set_MN_STRM_ATTR_HTT_M_reg(0x6);
		set_MN_STRM_ATTR_HTT_L_reg(0x72);
		set_MN_STRM_ATTR_HST_M_reg(0x01);
		set_MN_STRM_ATTR_HST_L_reg(0x05);
		set_MN_STRM_ATTR_HWD_M_reg(0x5);
		set_MN_STRM_ATTR_HWD_L_reg(0x00);
		set_MN_STRM_ATTR_HSW_M_reg(0x0);
		set_MN_STRM_ATTR_HSW_L_reg(0x28);
		set_MN_STRM_ATTR_VTTE_M_reg(0x2);
		set_MN_STRM_ATTR_VTTE_L_reg(0xee);
		set_MN_STRM_ATTR_VST_L_reg(0x1a);
		set_MN_STRM_ATTR_VHT_M_reg(0x2);
		set_MN_STRM_ATTR_VHT_L_reg(0xd0);
		set_MN_STRM_ATTR_VSW_M_reg(0x0);
		set_MN_STRM_ATTR_VSW_L_reg(0x5);
	} else if(res == DP_FORMAT_1080P_60) {
		set_MN_STRM_ATTR_HTT_M_reg(0x8);
		set_MN_STRM_ATTR_HTT_L_reg(0x98);
		set_MN_STRM_ATTR_HST_M_reg(0x00);
		set_MN_STRM_ATTR_HST_L_reg(0xC1);
		set_MN_STRM_ATTR_HWD_M_reg(0x7);
		set_MN_STRM_ATTR_HWD_L_reg(0x80);
		set_MN_STRM_ATTR_HSW_M_reg(0x0);
		set_MN_STRM_ATTR_HSW_L_reg(0x2C);
		set_MN_STRM_ATTR_VTTE_M_reg(0x4);
		set_MN_STRM_ATTR_VTTE_L_reg(0x65);
		set_MN_STRM_ATTR_VST_L_reg(0x2a);
		set_MN_STRM_ATTR_VHT_M_reg(0x4);
		set_MN_STRM_ATTR_VHT_L_reg(0x38);
		set_MN_STRM_ATTR_VSW_M_reg(0x0);
		set_MN_STRM_ATTR_VSW_L_reg(0x5);
	} else if(res == DP_FORMAT_1024_768 ) {
		set_MN_STRM_ATTR_HTT_M_reg(0x5);
		set_MN_STRM_ATTR_HTT_L_reg(0x40);
		set_MN_STRM_ATTR_HST_M_reg(0x1);
		set_MN_STRM_ATTR_HST_L_reg(0x29);
		set_MN_STRM_ATTR_HWD_M_reg(0x4);
		set_MN_STRM_ATTR_HWD_L_reg(0x0);
		set_MN_STRM_ATTR_HSW_M_reg(0x80);
		set_MN_STRM_ATTR_HSW_L_reg(0x88);
		set_MN_STRM_ATTR_VTTE_M_reg(0x3);
		set_MN_STRM_ATTR_VTTE_L_reg(0x26);
		set_MN_STRM_ATTR_VST_L_reg(0x24);
		set_MN_STRM_ATTR_VHT_M_reg(0x3);
		set_MN_STRM_ATTR_VHT_L_reg(0x0);
		set_MN_STRM_ATTR_VSW_M_reg(0x80);
		set_MN_STRM_ATTR_VSW_L_reg(0x6);
	} else if(res == DP_FORMAT_2160P_30 ) {
		set_MN_STRM_ATTR_HTT_M_reg(0x13);
		set_MN_STRM_ATTR_HTT_L_reg(0x30);
		set_MN_STRM_ATTR_HST_M_reg(0x1);
		set_MN_STRM_ATTR_HST_L_reg(0x81);
		set_MN_STRM_ATTR_HWD_M_reg(0xf);
		set_MN_STRM_ATTR_HWD_L_reg(0x0);
		set_MN_STRM_ATTR_HSW_M_reg(0x0);
		set_MN_STRM_ATTR_HSW_L_reg(0x58);
		set_MN_STRM_ATTR_VTTE_M_reg(0x8);
		set_MN_STRM_ATTR_VTTE_L_reg(0xca);
		set_MN_STRM_ATTR_VST_L_reg(0x53);
		set_MN_STRM_ATTR_VHT_M_reg(0x8);
		set_MN_STRM_ATTR_VHT_L_reg(0x70);
		set_MN_STRM_ATTR_VSW_M_reg(0x0);
		set_MN_STRM_ATTR_VSW_L_reg(0xa);
	} else if(res == DP_FORMAT_2160P_60) {
		set_MN_STRM_ATTR_HTT_M_reg(0xf);
		set_MN_STRM_ATTR_HTT_L_reg(0x50);
		set_MN_STRM_ATTR_HST_L_reg(0x49);
		set_MN_STRM_ATTR_HWD_M_reg(0xf);
		set_MN_STRM_ATTR_HWD_L_reg(0x00);
		set_MN_STRM_ATTR_HSW_M_reg(0x0);
		set_MN_STRM_ATTR_HSW_L_reg(0x20);
		set_MN_STRM_ATTR_VTTE_M_reg(0x8);
		set_MN_STRM_ATTR_VTTE_L_reg(0xae);
		set_MN_STRM_ATTR_VST_L_reg(0xf);
		set_MN_STRM_ATTR_VHT_M_reg(0x8);
		set_MN_STRM_ATTR_VHT_L_reg(0x70);
		set_MN_STRM_ATTR_VSW_M_reg(0x0);
		set_MN_STRM_ATTR_VSW_L_reg(0x8);
	}

	set_MSA_MISC0_reg(0x20);
	set_MSA_CTRL_reg(get_MSA_CTRL_reg | _BIT7);
}

static void dptx_sst_dpformat_setting(int res)
{
	set_LFIFO_WL_SET_reg(get_LFIFO_WL_SET_reg & ~(_BIT7));
	set_DP_RESET_CTRL_reg(get_DP_RESET_CTRL_reg | _BIT7);
	set_DP_RESET_CTRL_reg(get_DP_RESET_CTRL_reg & ~(_BIT7));

	set_TU_DATA_SIZE0_reg(0x35);
	set_TU_DATA_SIZE1_reg(0);
	if(res == DP_FORMAT_720P_60) {
		set_TU_DATA_SIZE0_reg(0x35);
		set_TU_DATA_SIZE1_reg(0);
		set_V_DATA_PER_LINE0_reg(0xf);
		set_V_DATA_PER_LINE1_reg(0x00);
	} else if(res == DP_FORMAT_1080P_60) {
		set_TU_DATA_SIZE0_reg(0x35);
		set_TU_DATA_SIZE1_reg(0);
		set_V_DATA_PER_LINE0_reg(0xb);
		set_V_DATA_PER_LINE1_reg(0x40);
	} else if(res == DP_FORMAT_1024_768) {
		set_TU_DATA_SIZE0_reg(0x2e);
		set_TU_DATA_SIZE1_reg(0x1);
		set_V_DATA_PER_LINE0_reg(0xc);
		set_V_DATA_PER_LINE1_reg(0x00);
	} else if(res == DP_FORMAT_2160P_30) {
		set_TU_DATA_SIZE0_reg(0x35);
		set_TU_DATA_SIZE1_reg(0);
		set_V_DATA_PER_LINE0_reg(0xb);
		set_V_DATA_PER_LINE1_reg(0x40);
	}
	set_LFIFO_WL_SET_reg(0xc0);

	set_PG_FIFO_CTRL_reg(0xFF);
}

static void dptx_sst_setting(int res)
{
//	unsigned int pucData[6];

//	pucData[0] = 0;
//	pucData[1] = 0x8000;
//	pucData[2] = 0;
//	pucData[3] = 0;

//	pucData[0] = dpinfo.clock * pucData[1];
//	pucData[0] /= ((dpinfo.ssc_en == 1) ? (270*9975/1000))

	if(res == DP_FORMAT_720P_60) {
		set_MN_M_VID_M_reg(0x23);
		set_MN_M_VID_L_reg(0x33);
		set_MN_N_VID_M_reg(0x80);
		set_MN_N_VID_L_reg(0x00);
	} else if(res == DP_FORMAT_1080P_60) {
		set_MN_M_VID_M_reg(0x46);
		set_MN_M_VID_L_reg(0x67);
		set_MN_N_VID_M_reg(0x80);
		set_MN_N_VID_L_reg(0x00);
	} else if(res == DP_FORMAT_1024_768) {
		set_MN_M_VID_M_reg(0x1e);
		set_MN_M_VID_L_reg(0xd1);
		set_MN_N_VID_M_reg(0x80);
		set_MN_N_VID_L_reg(0x00);
	} else if(res == DP_FORMAT_2160P_30) {
		set_MN_M_VID_M_reg(0x8c);
		set_MN_M_VID_L_reg(0xce);
		set_MN_N_VID_M_reg(0x80);
		set_MN_N_VID_L_reg(0x00);
	}
	set_MSA_CTRL_reg(get_MSA_CTRL_reg & ~(_BIT6));
	set_MN_VID_AUTO_EN_1_reg(0x40);

	dptx_sst_msa_setting(res);
	dptx_sst_dpformat_setting(res);
}

static int dptx_get_factory_info(void)
{
	struct VIDEO_RPC_VOUT_CONFIG_TV_SYSTEM tv_info;
	char *dst_addr;
	int dst_length;
	int res;
	
	if(factory_read(BOOT_TVSYSTEM_FILE_NAME, &dst_addr, &dst_length)) {
		printf("can't read video rpc factory file\n");
#ifdef CONFIG_DPTX_DEFAULT_RESOLUTION
		dpinfo.resolution = CONFIG_DPTX_DEFAULT_RESOLUTION;
		if(dpinfo.resolution == DP_FORMAT_720P_60)
			res = VO_STANDARD_DP_FORMAT_1280_720P_60;
		else if(dpinfo.resolution == DP_FORMAT_1024_768)
			res = VO_STANDARD_DP_FORMAT_1024_768P_60;
		else if(dpinfo.resolution == DP_FORMAT_1080P_60)
			res = VO_STANDARD_DP_FORMAT_1920_1080P_60;
		else {
			dpinfo.resolution = DP_FORMAT_720P_60;
			res = VO_STANDARD_DP_FORMAT_1280_720P_60;
		}
#else
		dpinfo.resolution = DP_FORMAT_720P_60;
		res = VO_STANDARD_DP_FORMAT_1280_720P_60;
#endif
		return res;
	}
	memcpy(&tv_info, dst_addr, dst_length);

	res = SWAPEND32(tv_info.videoInfo.pedType);
	if(res == VO_STANDARD_DP_FORMAT_1280_720P_60)
		dpinfo.resolution = DP_FORMAT_720P_60;
	else if(res == VO_STANDARD_DP_FORMAT_1024_768P_60)
		dpinfo.resolution = DP_FORMAT_1024_768;
	else if(res == VO_STANDARD_DP_FORMAT_1920_1080P_60)
		dpinfo.resolution = DP_FORMAT_1080P_60;
	else if(res == VO_STANDARD_DP_FORMAT_2160P_30)
		dpinfo.resolution = DP_FORMAT_2160P_30;
	else if(res == VO_STANDARD_DP_FORMAT_3840_2160P_60)
		dpinfo.resolution = DP_FORMAT_2160P_60;
	else {
		printf("can't find support resolution\n");
		dpinfo.resolution = DP_FORMAT_720P_60;
		res = VO_STANDARD_DP_FORMAT_1280_720P_60;
	}
	
	return res;
}

static int dptx_set_tv_system(int vid)
{
	struct _BOOT_TV_STD_INFO boot_info;

	memcpy(&boot_info, (unsigned char *)VO_RESOLUTION, sizeof(struct _BOOT_TV_STD_INFO) );
	
	if(boot_info.tv_sys.hdmiInfo.hdmiMode == SWAPEND32(VO_HDMI_OFF)) {
		printf("HDMI is off, DP only\n");
		boot_info.tv_sys.interfaceType = SWAPEND32(VO_DISPLAY_PORT_ONLY);
	} else {
		printf("HDMI & DP same source\n");
		boot_info.tv_sys.interfaceType = SWAPEND32(VO_HDMI_AND_DISPLAY_PORT_DIFF_SOURCE);
	}

	boot_info.dwMagicNumber = SWAPEND32(0xC0DE0BEE);
	boot_info.tv_sys.videoInfo.pedType = SWAPEND32(resolution);
	
	memcpy((unsigned char *)VO_RESOLUTION, & boot_info, sizeof(struct _BOOT_TV_STD_INFO) );
	flush_cache(VO_RESOLUTION, sizeof(struct _BOOT_TV_STD_INFO));
	
	return 0;
}

static void dptx_set_resolution(int res)
{
	if(res == DP_FORMAT_720P_60) {
		printf("resolution = 720p %d\n", res);
		set_DH_WIDTH_reg(0x28);
		set_DH_TOTAL_reg(0x6720672);
		set_DH_DEN_START_END_reg(0x0fb05fb);
		set_DV_DEN_START_END_FIELD1_reg(0x1a02ea);
		set_DV_TOTAL_reg(0x2ee);
		set_DV_VS_START_END_FIELD1_reg(0x10006);
		set_DV_SYNC_INT_reg(0x000002eb);
		
#ifdef VO_EN
		rtd_outl(VO_BASE+0x48, 0x500);
		rtd_outl(VO_BASE+0x4c, 0x500);
		rtd_outl(VO_BASE+0x68, 0x5002d0);
		rtd_outl(VO_BASE+0xd78, 0x50002d0);
#endif
		dptx_sst_setting(res);
	
		set_DP_PHY_CTRL_reg(0x14);
		set_DP_MAC_CTRL_reg(0x5);
		set_AIF_EDP_1_reg(0x1);

		set_DPTX_SFIFO_CTRL0_reg(0x80);
		set_DPTX_PHY_CTRL_reg(0x15);

	} else if(res == DP_FORMAT_1080P_60) {
		printf("resolution = 1080p\n");
		set_DH_WIDTH_reg(0x2C);
		set_DH_TOTAL_reg(0x8980898);
		set_DH_DEN_START_END_reg(0x0b70837);
		set_DV_DEN_START_END_FIELD1_reg(0x2a0462);
		set_DV_TOTAL_reg(0x465);
		set_DV_VS_START_END_FIELD1_reg(0x10006);
		set_DV_SYNC_INT_reg(0x00000463);

#ifdef VO_EN
		rtd_outl(VO_BASE+0x48, 0x780);
		rtd_outl(VO_BASE+0x4c, 0x780);
		rtd_outl(VO_BASE+0x68, 0x780438);
		rtd_outl(VO_BASE+0xd78, 0x7800438);
#endif
		dptx_sst_setting(res);
	
		set_DP_PHY_CTRL_reg(0x38);
		set_DP_MAC_CTRL_reg(0x6);
		set_AIF_EDP_1_reg(0x3);

		set_DPTX_SFIFO_CTRL0_reg(0x80);
		set_DPTX_PHY_CTRL_reg(0x15);
	} else if(res == DP_FORMAT_1024_768) {
		printf("resolution = 1024*768\n");
		set_DH_WIDTH_reg(0x88);
		set_DH_TOTAL_reg(0x5400540);
		set_DH_DEN_START_END_reg(0x11f051f);
		set_DV_DEN_START_END_FIELD1_reg(0x240324);
		set_DV_TOTAL_reg(0x326);
		set_DV_VS_START_END_FIELD1_reg(0x10007);
		set_DV_SYNC_INT_reg(0x00000325);
#ifdef VO_EN
		rtd_outl(VO_BASE+0x48, 0x400);
		rtd_outl(VO_BASE+0x4c, 0x400);
		rtd_outl(VO_BASE+0x68, 0x400300);
		rtd_outl(VO_BASE+0xd78, 0x4000300);
#endif
		dptx_sst_setting(res);
		
		set_DP_PHY_CTRL_reg(0x14);
		set_DP_MAC_CTRL_reg(0x5);
		set_AIF_EDP_1_reg(0x1);

		set_DPTX_SFIFO_CTRL0_reg(0x80);
		set_DPTX_PHY_CTRL_reg(0x15);
	} else if(res == DP_FORMAT_2160P_30) {
		printf("resolution = 2160P_30\n");
		set_DH_WIDTH_reg(0x58);
		set_DH_TOTAL_reg(0x11301130);
		set_DH_DEN_START_END_reg(0x1771077);
		set_DV_DEN_START_END_FIELD1_reg(0x5308c3);
		set_DV_TOTAL_reg(0x8ca);
		set_DV_VS_START_END_FIELD1_reg(0x1000b);
		set_DV_SYNC_INT_reg(0x000008c4);
#ifdef VO_EN
		rtd_outl(VO_BASE+0x48, 0xf00);
		rtd_outl(VO_BASE+0x4c, 0xf00);
		rtd_outl(VO_BASE+0x68, 0xf00870);
		rtd_outl(VO_BASE+0xd78, 0xf000870);
#endif
		dptx_sst_setting(res);
		
		set_DP_PHY_CTRL_reg(0xfc);
		set_DP_MAC_CTRL_reg(0x7);
		set_AIF_EDP_1_reg(0xf);

		set_DPTX_SFIFO_CTRL0_reg(0x80);
		set_DPTX_PHY_CTRL_reg(0x15);
	}
}

static void dptx_init(int res)
{
//	dpinfo.resolution = res;
	dpinfo.bandwidth = 0xa;
	if(res == DP_FORMAT_720P_60 || res == DP_FORMAT_1024_768) {
		dpinfo.lanecount = 1;
		dpinfo.ltp1_check = 0x1;
		dpinfo.ltp2_check = 0x7;
		dpinfo.clock = 74;
	} else if(res == DP_FORMAT_1080P_60) {
		dpinfo.lanecount = 2;
		dpinfo.ltp1_check = 0x11;
		dpinfo.ltp2_check = 0x77;
		dpinfo.clock = 148;
	} else if(res == DP_FORMAT_2160P_30) {
		dpinfo.lanecount = 4;
		dpinfo.ltp1_check = 0x1111;
		dpinfo.ltp2_check = 0x7777;
		dpinfo.clock = 297;
	} else if(res == DP_FORMAT_2160P_60) {
		dpinfo.lanecount = 4;
		dpinfo.ltp1_check = 0x1111;
		dpinfo.ltp2_check = 0x7777;
		dpinfo.clock = 522;
	}

	set_ARBITER_CTRL_reg(0x3);
	set_VBID_reg(0x6);
	set_ARBITER_SEC_END_CNT_HB_reg(0);

	dptx_set_resolution(res);

	// Enable DP Tx
/*	set_DPTX_PHY_CTRL0_reg(get_DPTX_PHY_CTRL0_reg | (_BIT7 | _BIT4));

	reg = get_DP_MAC_CTRL_reg & ~(_BIT1 | _BIT0) | _BIT1;
	set_DP_MAC_CTRL_reg(reg);
	reg = get_DP_PHY_CTRL_reg & ~(_BIT7 | _BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2) | (_BIT5 | _BIT4 | _BIT3);
	set_DP_PHY_CTRL_reg(reg);
	set_DPTX_PHY_CTRL_reg(0x4);
	
	reg = get_DPTX_PHY_CTRL1_reg & ~(_BIT3 | _BIT2 | _BIT1 | _BIT0) | (_BIT3 | _BIT2);
	set_DPTX_PHY_CTRL1_reg(reg);

	reg = get_DPTX_PHY_CTRL0_reg & ~(_BIT3 | _BIT2 | _BIT1 | _BIT0) | (_BIT1 | _BIT0);
	set_DPTX_PHY_CTRL0_reg(reg);*/
}

static void dptx_pll_setting(int res)
{
	unsigned int reg;
	int i;

	// Pixel PLL setting
	set_PLL_HDMI_reg(0x11a);//get_PLL_HDMI_reg | 1<<3);
	for(i = 0; i < 4096 ; i++);
	set_PLL_HDMI_reg(0x1be);
	for(i = 0; i < 4096 ; i++);
	set_PLL_HDMI_reg(0xbf);
	for(i = 0; i < 4096 ; i++);

	reg = rtd_inl(CRT_BASE+0x230) & ~(1<<6);
	rtd_outl(CRT_BASE+0x230, reg);
	mdelay(1);
	if(res == DP_FORMAT_1024_768) {
		rtd_outl(CRT_BASE+0x250, 0x934701a2);
		mdelay(1);
		rtd_outl(CRT_BASE+0x250, 0x934741a2);
		mdelay(1);
		rtd_outl(CRT_BASE+0x604, 0xcf1c);
		mdelay(1);
	} else if(res == DP_FORMAT_1080P_60) {
		rtd_outl(CRT_BASE+0x250, 0x93470192);
		mdelay(1);
		rtd_outl(CRT_BASE+0x250, 0x93474192);
		mdelay(1);
		rtd_outl(CRT_BASE+0x604, 0xF000);
		mdelay(1);
	} else if(res == DP_FORMAT_720P_60) {
		rtd_outl(CRT_BASE+0x250, 0x934701a2);
		mdelay(1);
		rtd_outl(CRT_BASE+0x250, 0x934741a2);
		mdelay(1);
		rtd_outl(CRT_BASE+0x604, 0xF000);
		mdelay(1);
	} else if(res == DP_FORMAT_2160P_30) {
		rtd_outl(CRT_BASE+0x250, 0x93470182);
		mdelay(1);
		rtd_outl(CRT_BASE+0x250, 0x93474182);
		mdelay(1);
		rtd_outl(CRT_BASE+0x604, 0xF000);
		mdelay(1);
	}
	rtd_outl(CRT_BASE+0x254, 0x1e01);
	mdelay(1);
	rtd_outl(CRT_BASE+0x608, 0x00501008);
	mdelay(1);
	rtd_outl(CRT_BASE+0x600, 0xd);
	mdelay(1);

	// DISABLE ISO control
	set_DISP_PLL_DIV2_reg(0x00440000);
	mdelay(1);
	set_AIF_MISC_reg(0x01003301);
	mdelay(1);
	set_DISP_PLL_DIV2_reg(0x00420000);
	mdelay(1);

	// EDP PLL setting
	rtd_outl(CRT_BASE+0x248, 0x9A356007);
	mdelay(1);
	rtd_outl(CRT_BASE+0x24C, 0x3);
	mdelay(1);
	rtd_outl(CRT_BASE+0x5E0, 0xc);
	mdelay(1);
	rtd_outl(CRT_BASE+0x5E4, 0x00030800);
	mdelay(1);
	rtd_outl(CRT_BASE+0x5EC, 0x00030480);
	mdelay(1);
	rtd_outl(CRT_BASE+0x5F0, 0x1100);
	mdelay(1);

	rtd_outl(CRT_BASE+0x5E8, 0x00501068);
	rtd_outl(CRT_BASE+0x5E0, 0xd);
	mdelay(1);
	if(dpinfo.ssc_en) {
		rtd_outl(CRT_BASE+0x5E0, 0xc);
		rtd_outl(CRT_BASE+0x5E0, 0xe);
	}
#ifdef VO_EN
	// VO common setting
	set_PLL_VODMA1_reg(0x10C167);
	rtd_outl(CRT_BASE+0x264, 0x7);
	rtd_outl(CRT_BASE+0x264, 0x3);
	mdelay(10);
	rtd_outl(VO_BASE+0x8, 0x10);
	rtd_outl(VO_BASE, 0x3);
	rtd_outl(VO_BASE+0x4, 0x5);
	rtd_outl(VO_BASE+0x28, 0x1401);
	rtd_outl(VO_BASE+0x38, 0x2000000);
	rtd_outl(VO_BASE+0x3c, 0x3000000);
	rtd_outl(VO_BASE+0xdfc, 0x8000800);
	rtd_outl(VO_BASE+0xe00, 0x800);
	rtd_outl(VO_BASE+0xe04, 0xed83e80);
	rtd_outl(VO_BASE+0xe08, 0x3c410c99);
	rtd_outl(VO_BASE+0xe0C, 0x0);
	rtd_outl(VO_BASE+0xe10, 0x150cda);
	rtd_outl(VO_BASE+0xe14, 0xc4a);
#endif
}

static void dptx_initialize(void)
{
	unsigned int reg, i;
	int ret;
	int vid=0;//, size, res=0;
	// Enable clock source & reset
	reg = get_SOFT_RESET1_reg | SOFT_RESET1_rstn_lvds(1) | SOFT_RESET1_rstn_vo(1);
	set_SOFT_RESET1_reg(reg);
	
	reg = get_CLOCK_ENABLE1_reg | CLOCK_ENABLE1_clk_en_lvds(1) | CLOCK_ENABLE1_clk_en_vo(1);
	set_CLOCK_ENABLE1_reg(reg);
	reg = rtd_inl(CRT_BASE+0x50) | 1<<15;
	rtd_outl(CRT_BASE+0x50, reg);

	dpinfo.ssc_en = 0;
	
	resolution = dptx_get_factory_info();
	dptx_pll_setting(dpinfo.resolution);
	dptx_read_edid(dptx_edid, 256);
	vid = add_cea_modes((struct edid *)dptx_edid);

//	size = sizeof(vid_support_list)/sizeof(struct VIDEO_FORMAT_CONVERTER);
//	for(i=0; i<size; i++)
//		if(vid == vid_support_list[i].standard)
//			res = vid_support_list[i].vid; 
//	set_VBID_FW_CTL_reg(0x1);

	dptx_init(dpinfo.resolution);
#ifdef VO_EN
	rtd_outl(VO_BASE+0xec4, 0x47);
	rtd_outl(VO_BASE+0x20, 0x3);
#endif
	rtd_outl(VO_BASE+0xe78, 0x3);

	dptx_set_tv_system(vid);

	for(i=0; i<20; i++) {
		ret = dptx_link_training();
		if(!ret)
			break;
		mdelay(100);
	}
	set_DPTX_ML_PAT_SEL_reg(0x40);
	set_DPTX_ML_PAT_SEL_reg(0x41);
}

int dptx_sink_capability_handler(int set)
{
	int ret = 0;

	if(dptx_hpd()) {
		printf("==== DP detect ====\n");
		dptx_initialize();
	} else {
		printf("==== DP not detect ====\n");
	}
	
	return ret;
}
