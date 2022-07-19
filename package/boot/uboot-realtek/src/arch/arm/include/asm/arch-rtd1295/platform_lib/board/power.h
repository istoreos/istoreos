#ifndef __POWER_H__
#define __POWER_H__

#include <config.h>

#if defined(CONFIG_BOARD_FPGA)
	#include "power/power_rtd1295_qa.h"
#elif defined(CONFIG_BOARD_QA)
	#include "power/power_rtd1295_qa.h"
#else
	#error "power-saving does not support this board."
#endif

#ifdef CONFIG_POWER_DOWN_S5
void RTK_set_power_on_S5(void);
#else
static inline void RTK_set_power_on_S5(void){return;}
#endif //CONFIG_POWER_DOWN_S5


enum _suspend_wakeup {
	eWAKEUP_ON_LAN,
	eWAKEUP_ON_IR,
	eWAKEUP_ON_GPIO,
	eWAKEUP_ON_ALARM,
	eWAKEUP_ON_TIMER,
	eWAKEUP_ON_CEC,
	eWAKEUP_ON_MAX,
};

enum _wakeup_flags {
	fWAKEUP_ON_LAN          = 0x1U << eWAKEUP_ON_LAN,
	fWAKEUP_ON_IR           = 0x1U << eWAKEUP_ON_IR,
	fWAKEUP_ON_GPIO         = 0x1U << eWAKEUP_ON_GPIO,
	fWAKEUP_ON_ALARM        = 0x1U << eWAKEUP_ON_ALARM,
	fWAKEUP_ON_TIMER        = 0x1U << eWAKEUP_ON_TIMER,
	fWAKEUP_ON_CEC          = 0x1U << eWAKEUP_ON_CEC,
};

enum _RESUME_STATE {
	RESUME_NONE     = 0,
	RESUME_UNKNOW,
	RESUME_IR,
	RESUME_GPIO,
	RESUME_LAN,
	RESUME_ALARM,
	RESUME_TIMER,
	RESUME_CEC,
	RESUME_MAX_STATE,
};

enum _GPIO_ACTIVE_STAT {
	ACTIVE_LOW = 0,
	ACTIVE_HIGH,
};

#define SETMASK(bits, pos)		(((-1U) >> (32-bits))  << (pos))
#define CLRMASK(bits, pos)		(~(SETMASK(bits, pos)))
#define SET_VAL(val,bits,pos)		((val << pos) & SETMASK(bits, pos))
#define GET_VAL(reg,bits,pos)		((reg & SETMASK(bits, pos)) >> pos)

#define SUSPEND_MAGIC_KEY			0xEA
#define SUSPEND_MAGIC_SHIFFT			24
#define SUSPEND_MAGIC_BITS			8
#define SUSPEND_MAGIC_MASK			(SUSPEND_MAGIC_KEY << SUSPEND_MAGIC_SHIFFT)
#define SUSPEND_MAGIC_GET(val)			GET_VAL(val, 8, 24)

#define WAKEUP_FLAGS_SHIFFT			0
#define WAKEUP_FLAGS_BITS			(eWAKEUP_ON_MAX)
#define WAKEUP_FLAGS_MASK(val)			SET_VAL(val, WAKEUP_FLAGS_BITS, WAKEUP_FLAGS_SHIFFT)
#define WAKEUP_FLAGS_GET(reg)			GET_VAL(reg, WAKEUP_FLAGS_BITS, WAKEUP_FLAGS_SHIFFT)

#define RESUME_STATE_SHIFFT			16
#define RESUME_STATE_BITS			8
#define RESUME_STATE_MASK(val)			SET_VAL(val, RESUME_STATE_BITS, RESUME_STATE_SHIFFT)
#define RESUME_STATE_GET(reg)			GET_VAL(reg, RESUME_STATE_BITS, RESUME_STATE_SHIFFT)

#define GPIO_WAKEUP_EN_SHIFFT			0
#define GPIO_WAKEUP_EN_BITS			24
#define GPIO_WAKEUP_EN_MASK(val)		SET_VAL(val, GPIO_WAKEUP_EN_BITS, GPIO_WAKEUP_EN_SHIFFT)
#define GPIO_WAKEUP_EN_GET(reg)			GET_VAL(reg, GPIO_WAKEUP_EN_BITS, GPIO_WAKEUP_EN_SHIFFT)

#define GPIO_WAKEUP_ACT_SHIFFT			0
#define GPIO_WAKEUP_ACT_BITS			24
#define GPIO_WAKEUP_ACT_MASK(val)		SET_VAL(val, GPIO_WAKEUP_ACT_BITS, GPIO_WAKEUP_ACT_SHIFFT)
#define GPIO_WAKEUP_ACT_GET(reg)		GET_VAL(reg, GPIO_WAKEUP_ACT_BITS, GPIO_WAKEUP_ACT_SHIFFT)

#define GPIO_WAKEUP_EN2_SHIFFT			0
#define GPIO_WAKEUP_EN2_BITS			11
#define GPIO_WAKEUP_EN2_MASK(val)		SET_VAL(val, GPIO_WAKEUP_EN_BITS, GPIO_WAKEUP_EN_SHIFFT)
#define GPIO_WAKEUP_EN2_GET(reg)		GET_VAL(reg, GPIO_WAKEUP_EN_BITS, GPIO_WAKEUP_EN_SHIFFT)

#define GPIO_WAKEUP_ACT2_SHIFFT			0
#define GPIO_WAKEUP_ACT2_BITS			11
#define GPIO_WAKEUP_ACT2_MASK(val)		SET_VAL(val, GPIO_WAKEUP_ACT_BITS, GPIO_WAKEUP_ACT_SHIFFT)
#define GPIO_WAKEUP_ACT2_GET(reg)		GET_VAL(reg, GPIO_WAKEUP_ACT_BITS, GPIO_WAKEUP_ACT_SHIFFT)

#define ACPU_BOOT_REASON(val)			RESUME_STATE_GET(val)
#define ACPU_BOOT_REASON_VALID(val) \
	((!(SUSPEND_MAGIC_GET(val) ^ SUSPEND_MAGIC_KEY)) && \
	 ((unsigned)ACPU_BOOT_REASON(val) < RESUME_MAX_STATE) \
	)


void set_suspend_wakeup_src(unsigned int val);
unsigned int get_suspend_wakeup_src(void);
int set_suspend_gpio_wakeup_src(int igpio, int activity);
void disable_soc_full_reset(void);


#endif	// __POWER_H__

