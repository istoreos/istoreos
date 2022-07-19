#include <common.h>

#if 1 /*def __NO_PLI__*/
static inline void __rtd_outl(unsigned int x, unsigned int y) {
	((*(volatile unsigned int *)(x)) = (y));
}
static inline unsigned int __rtd_inl(unsigned int x) {
	return (*(volatile unsigned int *)(x));
}

#else

#include <OSAL/PLI.h>
#include <assert.h>
static inline void __rtd_outl(unsigned int x, unsigned int y) {
	((*(volatile unsigned int *)( pli_getIOAddress(x))) = (y));
}
static inline unsigned int __rtd_inl(unsigned int x) {
	return (*(volatile unsigned int *)( pli_getIOAddress(x)));
}
#endif

//#include <stdio.h>
//#include <sysdefs.h>
//#include <pcb.h>
#include <platform_lib/board/pcb_mgr.h>
#include <platform_lib/board/pwm.h>
#include <platform_lib/board/gpio.h>
#include <platform_lib/board/lsadc.h>

#define printf(fmt,args...)


#ifndef CONFIG_REALTEK_PWM
#define pwm_init(a0,a1,a2,a3,a4)			do {} while(0)
#define pwm_set(a0,a1)						do {} while(0)
#define iso_pwm_init(a0,a1,a2,a3,a4)		do {} while(0)
#define iso_pwm_set(a0,a1)					do {} while(0)
#endif

#define unipwm_init(a0,a1,a2,a3,a4,a5)		do {} while(0)
#define unipwm_set(a0,a1)					do {} while(0)
#define iso_unipwm_init(a0,a1,a2,a3,a4,a5)	do {} while(0)
#define iso_unipwm_set(a0,a1)				do {} while(0)

#ifndef CONFIG_REALTEK_LSADC
#define lsadc_init(x,y)						do {} while(0)
#define lsdac_get(x)						(x=x)
#endif

#ifndef CONFIG_REALTEK_GPIO
#define setGPIO(x,y)						do {} while(0)
#define setISOGPIO(x,y)						do {} while(0)
#define getGPIO(x)							(x=x)
#define getISOGPIO(x)						(x=x)
#endif

/*
  * Function: IO_PWM_SetFreq
  *
  *	Description:
  *			given some "PIN_XX"'s value then setup pwm frequency
  *
  *   param:
  *		   pin : the value corresponding to some "PIN_XXX"
  *		   freq_hz: PWM frequency
  *	return :   -1 : means unkwon pin type ...
  *			0: success
  *
*/
int IO_PWM_SetFreq(unsigned long long pin, int freq_hz) {
	PCB_PIN_TYPE_T type;
	int index;
	int param1, /*param2,*/ param3, param4, param5;
	type = GET_PIN_TYPE(pin);
	index = GET_PIN_INDEX(pin);
	switch (type) {

	case PCB_PIN_TYPE_ISO_UNIPWM:
	case PCB_PIN_TYPE_UNIPWM:
	{
			param1 = GET_UNIPWM_INVERT(pin);
			param3 = GET_UNIPWM_DUTY_MAX(pin);
			param4  = GET_UNIPWM_INIT_DUTY(pin);
			param5  = GET_UNIPWM_PWM_NUM(pin);
			if (type == PCB_PIN_TYPE_UNIPWM) {
				unipwm_init(index, param5, freq_hz, param3, param4, param1);
			} else {
				iso_unipwm_init(index, param5, freq_hz, param3, param4, param1);
			}
	}
	break;
	case PCB_PIN_TYPE_PWM:
	case PCB_PIN_TYPE_ISO_PWM:
	{
			param1 = GET_PWM_INVERT(pin);
			param3 = GET_PWM_DUTY_MAX(pin);
			param4  = GET_PWM_INIT_DUTY(pin);
			if (type == PCB_PIN_TYPE_PWM) {
				pwm_init(index, freq_hz, param3, param4, param1);
			} else {
				iso_pwm_init(index, freq_hz, param3, param4, param1);
			}

	}
	break;

	case PCB_PIN_TYPE_UNUSED:
	case PCB_PIN_TYPE_LSADC:
	case PCB_PIN_TYPE_EMCU_GPIO:
	case PCB_PIN_TYPE_GPIO:
	case PCB_PIN_TYPE_ISO_GPIO:
	break;
	default:
	break;


	}

	return 0;


}

/*
  * Function: IO_PWM_SetDuty
  *
  *	Description:
  *			given some "PIN_XX"'s value then setup pwm duty
  *
  *   param:
  *		   pin : the value corresponding to some "PIN_XXX"
  *			    pin include duty_max function
  *		   freq_hz: PWM frequency
  *	return :   -1 : means unkwon pin type ...
  *			0: success
  *
*/

int IO_PWM_SetDuty(unsigned long long pin, int duty) {

	PCB_PIN_TYPE_T type;
	int index;
/*	int param1, param2, param3, param4, param5;	*/
	type = GET_PIN_TYPE(pin);
	index = GET_PIN_INDEX(pin);
	switch (type) {

	case PCB_PIN_TYPE_ISO_UNIPWM:
	case PCB_PIN_TYPE_UNIPWM:
	{
			if (type == PCB_PIN_TYPE_UNIPWM) {
				unipwm_set(index, duty);
			} else {
				iso_unipwm_set(index, duty);
			}
	}
	break;
	case PCB_PIN_TYPE_PWM:
	case PCB_PIN_TYPE_ISO_PWM:
	{
			if (type == PCB_PIN_TYPE_PWM) {
				pwm_set(index, duty);
			} else {
				iso_pwm_set(index, duty);
			}

	}
	break;

	case PCB_PIN_TYPE_UNUSED:
	case PCB_PIN_TYPE_LSADC:
	case PCB_PIN_TYPE_EMCU_GPIO:
	case PCB_PIN_TYPE_GPIO:
	case PCB_PIN_TYPE_ISO_GPIO:
	break;
	default:
	break;


	}

	return 0;





}

/*
  * Function: IO_Set
  *
  *	Description:
  *			given some "PIN_XX"'s value then setup IO value
  *                  if IO is pwm, then setup pwm duty
  *                  if IO is GPO, then setup high low
  *
  *
  *   param:
  *		   pin : the value corresponding to some "PIN_XXX"
  *
  *	return :   -1 : means unkwon pin type ...
  *			0: success
  *
*/

int IO_Set(unsigned long long pin, int value) {
	PCB_PIN_TYPE_T type;
	int index;
	int param1, param2, param3;

	//printf("IO_Set: pin 0x%llx value 0x%x\n", pin, value);
	type = GET_PIN_TYPE(pin);
	index = GET_PIN_INDEX(pin);
	//printf("IO_Set: type 0x%x index 0x%x\n", type, index);
	switch (type) {

	case PCB_PIN_TYPE_UNUSED:
		return 0;

	case PCB_PIN_TYPE_LSADC:
			param1 = GET_LSADC_TYPE(pin);
			param2 = GET_LSADC_HITVALUE(pin);
			param3  = GET_LSADC_TOLERANCE(pin);
			return 0;
	break;
	case PCB_PIN_TYPE_EMCU_GPIO:
			param1 = GET_GPIO_TYPE(pin);
			param2 = GET_GPIO_INVERT(pin);
			param3  = GET_GPIO_INIT_VALUE(pin);
			if (param1 > PCB_GPIO_TYPE_TRI_IO)  {
				printf("wrong EMCU GPIO type\n");
				return -1;
				break;
			}
	break;
	case PCB_PIN_TYPE_GPIO:
			param1 = GET_GPIO_TYPE(pin);
			param2 = GET_GPIO_INVERT(pin);
			param3  = GET_GPIO_INIT_VALUE(pin);
			//printf("IO_Set: param1 0x%x param2 0x%x param3 0x%x\n", param1, param2, param3);
			if (param1 == PCB_GPIO_TYPE_INPUT) {
				getGPIO(index);
			} else if (param1 == PCB_GPIO_TYPE_OUPUT ){
				if (param2 != 0) {// invert init value
					if (value) {
						value = 0;
					} else {
						value =1 ;
					}
				}
				setGPIO(index, value != 0);
			} else if (param1 == PCB_GPIO_TYPE_TRI_IO){
				if (param2 != 0) {// invert init value
					if (value) {
						value = 0;
					} else {
						value =1 ;
					}
				}
				if (value) {
					setGPIO(index, 1);
					getGPIO(index);
				} else {
					setGPIO(index, 0);
				}

			} else {
				printf("wrong GPIO type\n");
				return -1;
			}
	break;
	case PCB_PIN_TYPE_ISO_GPIO:
			param1 = GET_GPIO_TYPE(pin);
			param2 = GET_GPIO_INVERT(pin);
			param3  = GET_GPIO_INIT_VALUE(pin);
			//printf("IO_Set: param1 0x%x param2 0x%x param3 0x%x\n", param1, param2, param3);
			if (param1 == PCB_GPIO_TYPE_INPUT) {
				getISOGPIO(index);
			} else if (param1 == PCB_GPIO_TYPE_OUPUT ){
				if (param2 != 0) {// invert init value
					if (value) {
						value = 0;
					} else {
						value =1 ;
					}
				}
				setISOGPIO(index, value != 0);
			} else if (param1 == PCB_GPIO_TYPE_TRI_IO){
				if (param2 != 0) {// invert init value
					if (value) {
						value = 0;
					} else {
						value =1 ;
					}
				}
				if (value) {
					setISOGPIO(index, 1);
					getISOGPIO(index);
				} else {
					setISOGPIO(index, 0);
				}

			} else {
				printf("wrong GPIO type\n");
				return -1;
			}
	break;
	case PCB_PIN_TYPE_ISO_UNIPWM:
	case PCB_PIN_TYPE_UNIPWM:
			if (type == PCB_PIN_TYPE_UNIPWM) {
				unipwm_set(index, value);
			} else {
				iso_unipwm_set(index, value);
			}

	break;
	case PCB_PIN_TYPE_PWM:
	case PCB_PIN_TYPE_ISO_PWM:
	{
		if (type == PCB_PIN_TYPE_PWM) {
				pwm_set(index, value);
			} else {
				iso_pwm_set(index, value);
			}
	}
	break;

	default:
	break;

	}

	return 0;
}


/*
  * Function: IO_Get
  *
  *	Description:
  *			given some "PIN_XX"'s value then setup IO value
  *                  if IO is lsadc then check if the ADC value hit the presetting ADC value
  *                  "PIN_XX"'s value include presetting ADC value
  *                  if IO is GPI, then get GPI high low
  *
  *
  *   param:
  *		   pin : the corresponding value  of some "PIN_XXX"
  *
  *	return :   -1 : means unkwon pin type ...
  *			0: success
  *
*/


int IO_Get(unsigned long long pin) {
	PCB_PIN_TYPE_T type;
	int index;
	int invert, subtype, value;
	int hitvalue, torrence;
	type = GET_PIN_TYPE(pin);
	index = GET_PIN_INDEX(pin);
	printf("%s %d: type 0x%x, index 0x%x\n", __FUNCTION__, __LINE__, type, index);
	switch (type) {
			case PCB_PIN_TYPE_LSADC:
			{
				hitvalue = GET_LSADC_HITVALUE(pin);
				torrence  = GET_LSADC_TOLERANCE(pin);
				value = lsdac_get(index);
				printf("value = %x\n", value);
				printf("hitvalue = %x\n", hitvalue);
				printf("torrence = %x\n", torrence);

				if (torrence < ABS(value, hitvalue)) {
					return 1;
				} else {
					return 0;
				};
			}
			break;
			case PCB_PIN_TYPE_GPIO:
			{
				subtype = GET_GPIO_TYPE(pin);
				invert = GET_GPIO_INVERT(pin);
				printf("%s %d: subtype 0x%x, invert 0x%x\n", __FUNCTION__, __LINE__, subtype, invert);
				if (subtype == PCB_GPIO_TYPE_INPUT) {
					printf("%s %d: subtype 0x%x, invert 0x%x\n", __FUNCTION__, __LINE__, subtype, invert);
					value = (getGPIO(index) != 0);
					if (invert) {
						value = (value == 0);
					}
					return value;
				} else if (subtype == PCB_GPIO_TYPE_OUPUT ){
					if (invert) {
						return 1;
					} else {
						return 0;
					}
				} else if (subtype == PCB_GPIO_TYPE_TRI_IO){
					setGPIO(index, 1);     // set GPIO to Hi-Z
					value = (getGPIO(index) != 0);
					if (invert) {
						value = (value == 0);
					}
					return value;
				} else {
					printf("wrong GPIO type\n");
					return 1;
				}
			}
			break;
			case PCB_PIN_TYPE_ISO_GPIO:
			{
				subtype = GET_GPIO_TYPE(pin);
				invert = GET_GPIO_INVERT(pin);
				printf("%s %d: subtype 0x%x, invert 0x%x\n", __FUNCTION__, __LINE__, subtype, invert);
				if (subtype == PCB_GPIO_TYPE_INPUT) {
					printf("%s %d: subtype 0x%x, invert 0x%x\n", __FUNCTION__, __LINE__, subtype, invert);
					value = (getISOGPIO(index) != 0);
					if (invert) {
						value = (value == 0);
					}
					return value;
				} else if (subtype == PCB_GPIO_TYPE_OUPUT ){
					if (invert) {
						return 1;
					} else {
						return 0;
					}
				} else if (subtype == PCB_GPIO_TYPE_TRI_IO){
					setISOGPIO(index, 1);     // set GPIO to Hi-Z
					value = (getISOGPIO(index) != 0);
					if (invert) {
						value = (value == 0);
					}
					return value;
				} else {
					printf("wrong GPIO type\n");
					return 1;
				}

			}
			break;
			case PCB_PIN_TYPE_UNIPWM:
			case PCB_PIN_TYPE_ISO_UNIPWM:
			case PCB_PIN_TYPE_PWM:
			case PCB_PIN_TYPE_ISO_PWM:
					return 0;
			default:
			case PCB_PIN_TYPE_EMCU_GPIO:
				// not implement
				return 1;
			break;
			case PCB_PIN_TYPE_UNUSED:
			return 1;

	}

}

/*
  * Function: IO_Config
  *
  *	Description:
  *			given some "PIN_XX"'s value then initialze IO
  *                  if IO is lsadc then turn on LSADC and set to current mode / voltage mode
  *                  if IO is GPIO, then setup correct initial state
  *                  if IO is pwm, then setup freq and duty
  *
  *   param:
  *		   pin : the corresponding value  of some "PIN_XXX"
  *
  *	return :   -1 : means unkwon pin type ...
  *			0: success
  *
*/



int IO_Config(unsigned long long pin) {

	PCB_PIN_TYPE_T type;
	int index;
	int param1, param2, param3,param4, param5;
	type = GET_PIN_TYPE(pin);
	index = GET_PIN_INDEX(pin);
	printf("%s %d: type 0x%x, index 0x%x\n", __FUNCTION__, __LINE__, type, index);

	switch (type) {

	case PCB_PIN_TYPE_UNUSED:
		return 0;

	case PCB_PIN_TYPE_LSADC:
			param1 = GET_LSADC_TYPE(pin);
			param2 = GET_LSADC_HITVALUE(pin);
			param3  = GET_LSADC_TOLERANCE(pin);
			lsadc_init(index, param1 == 0);
	break;
	case PCB_PIN_TYPE_EMCU_GPIO:
	break;
	case PCB_PIN_TYPE_GPIO:
	case PCB_PIN_TYPE_ISO_GPIO:
			param1 = GET_GPIO_TYPE(pin);
			param3  = GET_GPIO_INIT_VALUE(pin);
			printf("%s %d: param1 0x%x, param3 0x%x\n", __FUNCTION__, __LINE__, param1, param3);
			if (param1 == PCB_GPIO_TYPE_INPUT) {
				printf("%s %d: param1 0x%x, param3 0x%x\n", __FUNCTION__, __LINE__, param1, param3);
				IO_Get(pin);
			} else if (param1 == PCB_GPIO_TYPE_OUPUT ){
				IO_Set(pin, param3);
			} else if (param1 == PCB_GPIO_TYPE_TRI_IO){
				IO_Set(pin, param3);
			} else {
				printf("wrong GPIO type\n");
				return -1;
			}
	break;
	case PCB_PIN_TYPE_UNIPWM:
	case PCB_PIN_TYPE_ISO_UNIPWM:
			param1 = GET_UNIPWM_INVERT(pin);
			param2  = GET_UNIPWM_FREQ(pin);
			param3 = GET_UNIPWM_DUTY_MAX(pin);
			param4  = GET_UNIPWM_INIT_DUTY(pin);
			param5  = GET_UNIPWM_PWM_NUM(pin);
			if (type == PCB_PIN_TYPE_UNIPWM) {
				unipwm_init(index, param5, param2, param3, param4, param1);
			} else {
				iso_unipwm_init(index, param5, param2, param3, param4, param1);
			}
	break;
	case PCB_PIN_TYPE_PWM:
	case PCB_PIN_TYPE_ISO_PWM:
			param1 = GET_PWM_INVERT(pin);
			param2  = GET_PWM_FREQ(pin);
			param3 = GET_PWM_DUTY_MAX(pin);
			param4  = GET_PWM_INIT_DUTY(pin);
			if (type == PCB_PIN_TYPE_PWM) {
				pwm_init(index, param2, param3, param4, param1);
			} else {
				iso_pwm_init(index, param2, param3, param4, param1);
			}

	break;
	break;

	default:
		break;

	}

	return 0;
}





