/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2012 by Chuck Chen <ycchen@realtek.com>
 *
 * prototype of system related functions for RTD1295
 */

#ifndef _PWM_H_
#define _PWM_H_

int pwm_get_freq(int pwm_number, unsigned int* freq);
int pwm_set_freq(int pwm_number, unsigned int freq);
int pwm_get_duty_rate(int pwm_number, unsigned int* duty_rate);
int pwm_set_duty_rate(int pwm_number, unsigned int duty_rate);
int pwm_enable(int pwm_number, unsigned int value);
int rtd129x_pwm_init(void);
int rtd129x_pwm_show(void);

#endif
