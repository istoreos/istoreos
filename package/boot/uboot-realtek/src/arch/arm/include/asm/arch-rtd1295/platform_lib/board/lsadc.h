#ifndef  __LSADC_H_
#define  __LSADC_H_
#ifdef __cplusplus
extern "C" {
#endif

#ifndef LITTLE_ENDIAN	// apply BIG_ENDIAN

typedef union
{
	unsigned int     regValue;
	struct
	{
		unsigned int     sel_wait:4;
		unsigned int     sel_adc_ck:4;
		unsigned int     debounce_cnt:4;
		unsigned int     reserved_0:4;
		unsigned int     dout_test_in:8;
		unsigned int     reserved_1:6;
		unsigned int     test_en:1;
		unsigned int     enable:1;
	};
}st_lsadc_ctrl_RBUS;

typedef union
{
	unsigned int     regValue;
	struct
	{
		unsigned int     reserved_0:14;
		unsigned int     jd_sbias:2;
		unsigned int     reserved_1:2;
		unsigned int     jd_adsbias:2;
		unsigned int     jd_dummy:2;
		unsigned int     reserved_2:1;
		unsigned int     jd_svr:1;
		unsigned int     reserved_3:3;
		unsigned int     jd_adcksel:1;
		unsigned int     reserved_4:3;
		unsigned int     jd_power:1;
	};
}st_lsadc_analog_ctrl_RBUS;

typedef struct
{
	unsigned int     regValue;
	struct
	{
		unsigned int     pad0_active:1;
		unsigned int     reserved_0:7;
		unsigned int     pad0_thred:8;
		unsigned int     pad0_sw:4;
		unsigned int     reserved_1:3;
		unsigned int     pad0_ctrl:1;
		unsigned int     reserved_2:2;
		unsigned int     adc_val0:6;
	};
}st_pad0_RBUS;

#else	// apply LITTLE_ENDIAN

typedef union
{
	unsigned int     regValue;
	struct
	{
		unsigned int     enable:1;
		unsigned int     test_en:1;
		unsigned int     reserved_1:6;
		unsigned int     dout_test_in:8;
		unsigned int     reserved_0:4;
		unsigned int     debounce_cnt:4;
		unsigned int     sel_adc_ck:4;
		unsigned int     sel_wait:4;
	};
}st_lsadc_ctrl_RBUS;

typedef union
{
	unsigned int     regValue;
	struct
	{
		unsigned int     jd_power:1;
		unsigned int     reserved_4:3;
		unsigned int     jd_adcksel:1;
		unsigned int     reserved_3:3;
		unsigned int     jd_svr:1;
		unsigned int     reserved_2:1;
		unsigned int     jd_dummy:2;
		unsigned int     jd_adsbias:2;
		unsigned int     reserved_1:2;
		unsigned int     jd_sbias:2;
		unsigned int     reserved_0:14;
	};
}st_lsadc_analog_ctrl_RBUS;

typedef struct
{
	unsigned int     regValue;
	struct
	{
		unsigned int     adc_val0:6;
		unsigned int     reserved_2:2;
		unsigned int     pad0_ctrl:1;
		unsigned int     reserved_1:3;
		unsigned int     pad0_sw:4;
		unsigned int     pad0_thred:8;
		unsigned int     reserved_0:7;
		unsigned int     pad0_active:1;
	};
}st_pad0_RBUS;

#endif

extern int lsadc_init(int index, int voltage_mode);
extern int lsdac_get(int index);

#ifdef __cplusplus
}
#endif
#endif

