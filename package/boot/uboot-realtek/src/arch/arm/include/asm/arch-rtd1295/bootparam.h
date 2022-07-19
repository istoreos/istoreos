#ifndef __BOOT_PARAM_H__
#define __BOOT_PARAM_H__

typedef enum {
	POWER_STATE_OFF = 0,
	POWER_STATE_ON,
} POWER_STATE_T;

typedef struct {
	unsigned int prev_power_state;
	unsigned int boot_logo_enable;
	unsigned int boot_music_enable;
	unsigned int backlight_value;
	unsigned int custom_video1_leng;
	unsigned int custom_video2_leng;
	unsigned int custom_audio1_leng;
	unsigned int custom_audio2_leng;
} bootparam_t;

void get_bootparam(void);
void get_layout(void);
int get_one_step_info(void);

extern bootparam_t bootparam;

#endif /* #define __BOOT_PARAM_H__ */

