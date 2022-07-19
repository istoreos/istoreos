#include <common.h>
#include <asm/arch/io.h>
#include <asm/arch/panelConfigParameter.h>
#include <asm/arch/fw_info.h>

#include <asm/arch/platform_lib/board/pcb_mgr.h>
#include <asm/arch/platform_lib/board/gpio.h>
#include <asm/arch/rtkemmc.h>
#include <asm/arch/rbus/crt_reg.h>

void pcb_gen_kernel_cmd_line(char *buffer, PCB_ENUM_T *ppcb_enum) {
#if 0
	int i;
	char tmp[256];
//	unsigned long long k=0x1234567890;
	unsigned int value;
	i = 0;
	if (ppcb_enum == NULL) {
		ppcb_enum = pcb_enum;
	}
	buffer[0] = 0;
	do {
		if(ppcb_enum[i].name == NULL) break;
		if(ppcb_enum[i].name[0] == 0) break;
		//printf("IO Config = %s@%llx\n", ppcb_enum[i].name, ppcb_enum[i].info);
		sprintf(tmp, "pcb_enum=%s,0x", ppcb_enum[i].name);
		strcat(buffer, tmp);
		value = (unsigned int) (ppcb_enum[i].info >> 32);
		sprintf(tmp,"%08x", value);
		//printf("%s\n", tmp);
		strcat(buffer, tmp);
		value = (unsigned int) (ppcb_enum[i].info & 0xFFFFFFFF);
		sprintf(tmp,"%08x ", value);
		//printf("%s\n", tmp);
		strcat(buffer, tmp);

		//printf("%s\n", buffer);

		i ++;
	} while(1);

#ifdef ENABLE_PCBENUM_PANEL_ACTIVE_SIZE
	if ((&default_panel_parameter)->iCONFIG_DISP_ACT_END_HPOS == 1366) {
		sprintf(tmp, "pcb_enum=%s,0x0123456789abcdef ", "IS_1366X768");
		strcat(buffer, tmp);
	}
	else {
		sprintf(tmp, "pcb_enum=%s,0x0123456789abcdef ", "IS_1920X1080");
		strcat(buffer, tmp);
	}
#endif
#ifdef HISENSE_OPEN_CELL_PANEL
		sprintf(tmp, "pcb_enum=%s,0x0123456789abcdef ", "HISENSE_OPEN_CELL_PANEL");
		strcat(buffer, tmp);
#endif
#endif
}
extern BOOT_FLASH_T boot_flash_type;
unsigned int pcb_get_boot_flash_type(void)
{
#if defined(CONFIG_SYS_RTK_SPI_FLASH)
		return boot_flash_type=BOOT_NOR_SERIAL;	 // 0
#elif defined(CONFIG_SYS_RTK_SD_FLASH)
		return boot_flash_type=BOOT_SD;	 // 3
#elif defined(CONFIG_SYS_RTK_NAND_FLASH)
		rtd_outl(SYS_muxpad0,0x55555554);
		return boot_flash_type=BOOT_NAND; // 1
#else //emmc
		rtd_maskl(SYS_muxpad0, ~0xFFFF0FFF, 0xaaaa0aa8);			
		return boot_flash_type=BOOT_EMMC; // 2
#endif
}

char *pcb_get_boot_flash_type_string(void)
{
	BOOT_FLASH_T cur_boot_flash_type = FLASH_TYPE_UNKNOWN;

	cur_boot_flash_type = pcb_get_boot_flash_type();

	switch(cur_boot_flash_type) {
		case BOOT_NOR_SERIAL:
			return FLASH_TYPE_SPI_STRING;

		case BOOT_NAND:
			return FLASH_TYPE_NAND_STRING;

		case BOOT_EMMC:
			return FLASH_TYPE_EMMC_STRING;

		case BOOT_SATA:
			return FLASH_TYPE_SATA_STRING;

		case BOOT_SD:
			return FLASH_TYPE_SD_STRING;

		default:
			return FLASH_TYPE_UNKNOWN_STRING;
	}

	return FLASH_TYPE_UNKNOWN_STRING;
}

