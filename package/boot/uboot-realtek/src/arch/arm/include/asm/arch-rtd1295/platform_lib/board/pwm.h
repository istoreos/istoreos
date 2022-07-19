#ifndef __PWM_H__
#define __PWM_H__
#ifdef __cplusplus
extern "C" {
#endif

#include <asm/arch/rbus/iso_reg.h>

#define PWM0_TIMING_CTRL_reg		0xB801BC88
#define PWM0_DUTY_SET_reg			0xB801BC8C
#define PWM0_CTRL_reg				0xB801BC84

//TODO: fix for phoenix
#define ISO_PWM0_CTRL_reg			(MIS_PWM0_CTRL_reg)
#define ISO_PWM0_TIMING_CTRL_reg	(MIS_PWM0_TIMING_CTRL_reg)
#define ISO_PWM0_DUTY_SET_reg		(MIS_PWM0_DUTY_SET_reg)

#ifndef LITTLE_ENDIAN	// apply BIG_ENDIAN

typedef union
{
	unsigned int	regValue;
	struct
	{
		unsigned int     pwm0l:1;
		unsigned int     pwm0_ck:1;
		unsigned int     pwm0_en:1;
		unsigned int     pwm0_vs_rst_en:1;
		unsigned int     pwm0_dut_8b:1;
		unsigned int     reserved_0:22;
		unsigned int     reserved_1:4;
		unsigned int     pwm_width_sel:1;
	};
}pwm0_ctrl_RBUS;

typedef union
{
	unsigned int	regValue;
	struct
	{
		unsigned int     pwm0_cnt_mode:1;
		unsigned int     pwm0_ck_sel_hs:1;
		unsigned int     pwm0_ck_sel:1;
		unsigned int     reserved_0:1;
		unsigned int     pwm0_cycle_max:4;
		unsigned int     reserved_1:10;
		unsigned int     pwm0_m:2;
		unsigned int     pwm0_n:12;
	};
}pwm0_timing_ctrl_RBUS;


typedef union
{
	unsigned int	regValue;
	struct
	{
		unsigned int     reserved_0:4;
		unsigned int     pwm0_dut:12;
		unsigned int     reserved_1:4;
		unsigned int     pwm0_totalcnt:12;
	};
}pwm0_duty_set_RBUS;

#else	// apply LITTLE_ENDIAN

typedef union
{
	unsigned int	regValue;
	struct
	{
		unsigned int     pwm_width_sel:1;
		unsigned int     reserved_1:4;
		unsigned int     reserved_0:22;
		unsigned int     pwm0_dut_8b:1;
		unsigned int     pwm0_vs_rst_en:1;
		unsigned int     pwm0_en:1;
		unsigned int     pwm0_ck:1;
		unsigned int     pwm0l:1;
	};
}pwm0_ctrl_RBUS;

typedef union
{
	unsigned int	regValue;
	struct
	{
		unsigned int     pwm0_n:12;
		unsigned int     pwm0_m:2;
		unsigned int     reserved_1:10;
		unsigned int     pwm0_cycle_max:4;
		unsigned int     reserved_0:1;
		unsigned int     pwm0_ck_sel:1;
		unsigned int     pwm0_ck_sel_hs:1;
		unsigned int	 pwm0_cnt_mode:1;
	};
}pwm0_timing_ctrl_RBUS;


typedef union
{
	unsigned int	regValue;
	struct
	{
		unsigned int     pwm0_totalcnt:12;
		unsigned int     reserved_1:4;
		unsigned int     pwm0_dut:12;
		unsigned int     reserved_0:4;
	};
}pwm0_duty_set_RBUS;

#endif

extern int pwm_init(int index, int pwm_freq_hz, int duty_max, int duty, int invert);
extern int iso_pwm_init(int index, int pwm_freq_hz, int duty_max, int duty, int invert);
extern int pwm_set(int index, int duty);
extern int iso_pwm_set(int index, int duty);
extern int unipwm_init(int unimux_index , int index, int pwm_freq_hz, int duty_max, int duty, int invert);
extern int iso_unipwm_init(int unimux_index , int index, int pwm_freq_hz, int duty_max, int duty, int invert);
extern int unipwm_set(int index, int duty);
extern int iso_unipwm_set(int index, int duty);

#ifdef __cplusplus
}
#endif
#endif
