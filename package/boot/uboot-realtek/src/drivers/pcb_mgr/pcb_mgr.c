#include <common.h>

#define __PCB_ENUM__
#include <platform_lib/board/pcb.h>
#include <platform_lib/board/pcb_mgr.h>

/*
  * Function: pcb_mgr_show_pin_enum_info
  *
  *	Description:
  *			if pcb enum is "PIN" enum
  *  			then this function can interpret PIN's value  into PIN's information such that PIN_TYPE....
  *
  *
  *	return :   -1 : means unkwon pin type ...
  *			0: success
  *
*/
//extern unsigned char boot_ac_on;

int pcb_mgr_show_pin_enum_info(unsigned long long pin) {

	PCB_PIN_TYPE_T type;
	int index;
	int param1, param2, param3, param4;
	int result = 0;
	char *gpio_type[3] = {
			"INPUT",
			"OUTPUT",
			"TRI_IO",
	};
	type = GET_PIN_TYPE(pin);
	index = GET_PIN_INDEX(pin);

	printf("\n============================================\n");

	switch (type) {

	case PCB_PIN_TYPE_UNUSED:
		printf("Unused pin\n");
		break;

	case PCB_PIN_TYPE_LSADC:
			param1 = GET_LSADC_TYPE(pin);
			param2 = GET_LSADC_HITVALUE(pin);
			param3  = GET_LSADC_TOLERANCE(pin);
			printf("LSADC%d %s \nHitvalue = %d \ntolerance=%d\n", index, param1 == PCB_LSADC_TYPE_VOLTAGE ? "VOLTAGE" : "CURRENT", param2, param3);
	break;
	case PCB_PIN_TYPE_EMCU_GPIO:
			param1 = GET_GPIO_TYPE(pin);
			param2 = GET_GPIO_INVERT(pin);
			param3  = GET_GPIO_INIT_VALUE(pin);
			if (param1 > PCB_GPIO_TYPE_TRI_IO)  {
				printf("wrong EMCU GPIO type\n");
				result = -1;
				break;
			}
			if (param1 != PCB_GPIO_TYPE_INPUT) {
				printf("EMCU_GPIO_%d \nType = %s \nInvert=%d \ninit_value = %d\n", index, gpio_type[param1], param2, param3);
			} else {
				printf("EMCU_GPIO_%d \nType = %s \nInvert=%d\n", index, gpio_type[param1], param2);
			}
	break;
	case PCB_PIN_TYPE_GPIO:
			param1 = GET_GPIO_TYPE(pin);
			param2 = GET_GPIO_INVERT(pin);
			param3  = GET_GPIO_INIT_VALUE(pin);
			if (param1 > PCB_GPIO_TYPE_TRI_IO)  {
				printf("wrong GPIO type\n");
				result = -1;
				break;
			}
			if (param1 != PCB_GPIO_TYPE_INPUT) {
				printf("GPIO_%d \nType = %s \nInvert=%d \ninit_value = %d\n", index, gpio_type[param1], param2, param3);
			} else {
				printf("GPIO_%d \nType = %s \nInvert=%d\n", index, gpio_type[param1], param2);
			}
	break;
	case PCB_PIN_TYPE_ISO_GPIO:
			param1 = GET_GPIO_TYPE(pin);
			param2 = GET_GPIO_INVERT(pin);
			param3  = GET_GPIO_INIT_VALUE(pin);
			if (param1 > PCB_GPIO_TYPE_TRI_IO)  {
				printf("wrong ISO_GPIO type\n");
				result = -1;
				break;
			}
			if (param1 != PCB_GPIO_TYPE_INPUT) {
				printf("ISO_GPIO_%d \nType = %s \nInvert=%d \ninit_value = %d\n", index, gpio_type[param1], param2, param3);
			} else {
				printf("ISO_GPIO_%d \nType = %s \nInvert=%d\n", index, gpio_type[param1], param2);
			}
	break;
	case PCB_PIN_TYPE_UNIPWM:
			param1 = GET_UNIPWM_INVERT(pin);
			param2  = GET_UNIPWM_FREQ(pin);
			param3  = GET_UNIPWM_INIT_DUTY(pin);
			param4  = GET_UNIPWM_PWM_NUM(pin);
			printf("UNIPWM_%d \npwm_num=%d, Invert=%d \nfreq = %d\ninit_value = %d\n", index, param4, param1, param2, param3);
	break;
	case PCB_PIN_TYPE_ISO_UNIPWM:
			param1 = GET_UNIPWM_INVERT(pin);
			param2  = GET_UNIPWM_FREQ(pin);
			param3  = GET_UNIPWM_INIT_DUTY(pin);
			param4  = GET_UNIPWM_PWM_NUM(pin);
			printf("ISO_UNIPWM_%d \npwm_num=%d, Invert=%d \nfreq = %d\ninit_value = %d\n", index, param4, param1, param2, param3);
	break;
	case PCB_PIN_TYPE_PWM:
			param1 = GET_PWM_INVERT(pin);
			param2  = GET_PWM_FREQ(pin);
			param3  = GET_PWM_INIT_DUTY(pin);
			printf("PWM_%d \nInvert=%d \nfreq = %d\ninit_value = %d\n", index, param1, param2, param3);

	break;
	case PCB_PIN_TYPE_ISO_PWM:
			param1 = GET_PWM_INVERT(pin);
			param2  = GET_PWM_FREQ(pin);
			param3  = GET_PWM_INIT_DUTY(pin);
			printf("ISO_PWM_%d \nInvert=%d \nfreq = %d\ninit_value = %d\n", index, param1, param2, param3);
	break;
	default:
		printf("undefined pin type !!!!!!!!\n");
		result = -1;
	break;


	}


	printf("============================================\n");
	return result;

}


#ifndef __PCB_ENUM__
static PCB_ENUM_T *ppcb_enum = NULL;
#endif

/*
  * Function: pcb_mgr_init
  *
  *	Description:
  *			init pcb_mgr
  *
  *	return :   -1 : means error
  *			0: success
  *
*/

int pcb_mgr_init(void) {

	int i;
	i = 0;

#ifdef CONFIG_SYS_PIN_MUX
	PinMuxInit();
#endif
	
	ppcb_enum = pcb_enum;
	do {
		if(ppcb_enum[i].name == NULL)
			break;
		if(ppcb_enum[i].name[0] == 0)
			break;

		//printf("name = %s\n", ppcb_enum[i].name);
		if (strstr(ppcb_enum[i].name, "PIN") != ppcb_enum[i].name) {
			i++;
			continue;
		}

//		printf("IO Config 2= %s@%08x%08x\n", ppcb_enum[i].name, HI32(ppcb_enum[i].info) ,LO32(ppcb_enum[i].info) );
		IO_Config(ppcb_enum[i].info);

		i ++;
	} while(1);

	//assert(0);
	return 0;
};

/*
	Function: pcb_mgr_show_all_enum_info

	Description:
			list  all pcb enum in text

	return :
*/

void pcb_mgr_show_all_enum_info(void) {

	int i;
	printf("\n============================================\n");
	i = 0;
	do {
		if(ppcb_enum == NULL)
			break;
		if(ppcb_enum[i].name == NULL)
			break;
		if(ppcb_enum[i].name[0] == 0)
			break;

		printf("@name = %s@0x%llx", ppcb_enum[i].name, ppcb_enum[i].info);
		if (strstr(ppcb_enum[i].name, "PIN") == ppcb_enum[i].name) {
			pcb_mgr_show_pin_enum_info(ppcb_enum[i].info);
		}
		printf("\n");
		i ++;
	} while(1);


}

/*
	Function: pcb_mgr_get_enum_info_byname

	Description:
	  		pcb enum is a key-value pair structure,
	  		enum_name is the key and is a string
	  		the value is a unsigned long long variable
	  		pcb_mgr_get_enum_info_byname is given enum_name as the key to find corresponding value

	return :   -1 : means there is no pcb enum found
			0: success

*/
int pcb_mgr_get_enum_info_byname(char *enum_name, unsigned long long *value) {

	int i;
	i = 0;
	//printf("%s %d\n", __FUNCTION__, __LINE__);
	do {
		if(ppcb_enum[i].name == NULL)
			break;
		if(ppcb_enum[i].name[0] == 0)
			break;

		if (strcmp(enum_name, ppcb_enum[i].name) == 0) {
			printf("name=%s ppcb_enum.Name=%s, ppcb_enum.info=%llx\n", enum_name, ppcb_enum[i].name, ppcb_enum[i].info);
			*value = ppcb_enum[i].info;
			return 0;
		}
		i ++;
	} while(1);

	return -1;

}

int pcb_mgr_get_enum_info_num(int num, unsigned long long *value) {

		if(ppcb_enum[num].name == NULL)
			return -1;

		if(ppcb_enum[num].name[0] == 0)
			return -1;

		*value = ppcb_enum[num].info;
		return 0;

	return -1;

}

