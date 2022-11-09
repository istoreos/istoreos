/*
 * (C) Copyright 2017 Rockchip Electronics Co., Ltd
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */
#ifndef __ROCKCHIP_IR_H__
#define __ROCKCHIP_IR_H__

#include <linux/bitops.h>

/* Registers */
/* High polarity cycles */
#define PWM_HPR_REG	0x04

/* Low polarity cycles */
#define PWM_LPR_REG	0x08

/* PWM Control */
#define PWM_CTL_REG	0x0c
/* Enable */
#define REG_CTL_EN	BIT(0)
/* capture mode */
#define REG_CTL_MD	BIT(2)

/* Interrupt Status */
#define PWM_STA_REG(id)	((4 - (id)) * 0x10)
#define PWM_CH_POL(id)	BIT(id + 8)

/* Interrupt Enable */
#define PWM_INT_REG(id)	((4 - (id)) * 0x14)
#define PWM_CH_INT(id)	BIT(id)

/* NEC IR Pulse/Space protocol */
#define NEC_NBITS		32
#define NEC_UNIT		562500	/* ns */
#define NEC_HEADER_PULSE	(16 * NEC_UNIT)
#define NEC_HEADER_SPACE	(8  * NEC_UNIT)
#define NEC_BIT_PULSE		(1  * NEC_UNIT)
#define NEC_BIT_0_SPACE		(1  * NEC_UNIT)
#define NEC_BIT_1_SPACE		(3  * NEC_UNIT)

#define TO_US(duration)		((duration) / 1000)
#define TO_STR(is_pulse)	((is_pulse) ? "pulse" : "space")

#define MAX_NUM_KEYS	60

enum nec_state {
	STATE_INACTIVE,
	STATE_HEADER_SPACE,
	STATE_BIT_PULSE,
	STATE_BIT_SPACE,
};

struct rockchip_ir_priv {
	fdt_addr_t base;
	ulong freq;
	ulong period;
	int id;
	int num;
	int keycode;
	int repeat;
};

struct ir_raw_event {
	u32 duration;
	unsigned pulse:1;
};

struct nec_dec {
	int state;
	unsigned count;
	u32 bits;
};

struct rc_map_table {
	u32 scancode;
	u32 keycode;
};

struct rc_map {
	u32 usercode;
	u32 nbuttons;
	struct rc_map_table scan[MAX_NUM_KEYS];
};

/* macros for IR decoders */
static inline bool eq_margin(unsigned d1, unsigned d2, unsigned margin)
{
	return ((d1 > (d2 - margin)) && (d1 < (d2 + margin)));
}

#endif /* __ROCKCHIP_IR_H__ */
