/*
 * (C) Copyright 2003
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

/*
 * Boot support
 */
#include <common.h>
#include <command.h>
#include <linux/compiler.h>
#include <asm/arch/rbus/crt_reg.h>
#include <asm/arch/rbus/crt_sys_reg.h>
#include <asm/arch/fw_info.h>
#include <asm/arch/io.h>
#include <asm/arch/ddr.h>
#include <asm/arch/cpu.h>

DECLARE_GLOBAL_DATA_PTR;
extern BOOT_FLASH_T boot_flash_type;

__maybe_unused
static void print_num(const char *name, ulong value)
{
	printf("%-12s= 0x%08lX\n", name, value);
}

__maybe_unused
static void print_eth(int idx)
{
	char name[10], *val;
	if (idx)
		sprintf(name, "eth%iaddr", idx);
	else
		strcpy(name, "ethaddr");
	val = getenv(name);
	if (!val)
		val = "(not set)";
	printf("%-12s= %s\n", name, val);
}

#if defined(CONFIG_ARM)

static int ddr_mhz = 0;

/*
 * get_accessible_ddr_size()
 */

unsigned long get_accessible_ddr_size(int unit)
{
#ifdef CONFIG_BOARD_FPGA
	return CONFIG_SYS_RAM_DCU1_SIZE;
#else
	unsigned long ddr_size = (get_total_ddr_size() * 1024) / 8;

	if(unit == UNIT_MEGABYTE)
		return ddr_size;
	else
		return (ddr_size * 0x100000);

	return 0;
#endif //CONFIG_BOARD_FPGA
}

#define DC0_DPI_DLL_CRT_SSC3_reg	0x9800E028
#define DC1_DPI_DLL_CRT_SSC3_reg	0x9800F028
#define DCPHY_DPI_DLL_CRT_SSC3_get_DPI_N_CODE_T(data)   ((0x0000FF00&(data))>>8)

static int do_bdinfo_ddr(void)
{
	char info_dc0[50], info_dc1[50];
	int i;
	printf("---- DDR information ----\n");

#if defined(CONFIG_RTD1395)
	for( i = 0; i < MAX_DC_COUNT; i++){
		uint ddr_speed_setting;
		if( i == 0 )
			ddr_speed_setting = DCPHY_DPI_DLL_CRT_SSC3_get_DPI_N_CODE_T(rtd_inl(DC0_DPI_DLL_CRT_SSC3_reg));
		else
			ddr_speed_setting = DCPHY_DPI_DLL_CRT_SSC3_get_DPI_N_CODE_T(rtd_inl(DC1_DPI_DLL_CRT_SSC3_reg));
		
		char range_exceed[16] = "";

		switch (ddr_speed_setting) {
			case 0x2a ... 0xff:
				ddr_mhz = 2400;
				strcpy(range_exceed, "OVER");
				break;
			case 0x25 ... 0x29:
				ddr_mhz = 2400;
				break;
			case 0x20 ... 0x24:
				ddr_mhz = 2133;
				break;
			case 0x1b ... 0x1f:
				ddr_mhz = 1866;
				break;
			case 0x16 ... 0x1a:
				ddr_mhz = 1600;
				break;
			case 0x15:
				ddr_mhz = 1333;
				break;
			case 0x0 ... 0x14 :
				ddr_mhz = 1333;
				strcpy(range_exceed, "UNDER");
				break;
			default:	ddr_mhz = 0;	break;
		}
		
		if( i == 0 )
			sprintf(info_dc0, "DDR        = %s %u MT/s (0x%02x)\n",range_exceed, ddr_mhz, ddr_speed_setting);
		else
			sprintf(info_dc1, "DDR        = %s %u MT/s (0x%02x)\n",range_exceed, ddr_mhz, ddr_speed_setting);
	}

#endif
	
	print_ddr_info(info_dc0,info_dc1);

	return 0;
}

#define set_SYS_PLL_reg(reg,data)   (*((volatile unsigned int*) reg)=data)
#define get_SYS_PLL_reg(reg)   (*((volatile unsigned int*) reg))
#define PLLBUS 		0x98000424
#define PLLDCSB		0x98000428
#define PLLACPU		0x9800042C
#define PLLDDSA		0x98000430
#define PLLDDSB		0x98000434
#define PLLGPU 		0x98000438
#define PLLVCPU 	0x9800043C
#define PLLVCPU_2 	0x98000440
#define PLLSCPU		0x9801D700

unsigned int get_pll_frequency(unsigned int reg)
{
	int wait_count = 0; /*For getting pll frequency*/
	unsigned int val, freq_pll = 0;
	set_SYS_PLL_reg((uintptr_t)reg,0x0); //reset all	 
	set_SYS_PLL_reg((uintptr_t)reg,0x1); //reg_rstn=1
	set_SYS_PLL_reg((uintptr_t)reg,0x3); //reg_rstn_count_en=1
	while(wait_count < 10000){
		val = get_SYS_PLL_reg((uintptr_t)reg);
		/*Wait reg[30] =1*/
		if ( (val & 0x40000000) == 0x40000000){
			freq_pll = ( (val >> 13) & 0x0001FFFF ) / 10;
			/*Read reg[29:13] value and divide 10*/
			wait_count = 0;
			break;
		}
		wait_count++;
	}
	return freq_pll;
}

unsigned int get_scpu_pll_frequency(unsigned int reg)
{
	int wait_count = 0; /*For getting pll frequency*/
	unsigned int val, freq_pll = 0;
	set_SYS_PLL_reg((uintptr_t)reg,0x0); //reset all	 
	set_SYS_PLL_reg((uintptr_t)reg,0x20000); //reg_rstn_b=1
	set_SYS_PLL_reg((uintptr_t)reg,0x30000); //reg_rstn_counter_b=1
	while(wait_count < 10000){
		val = get_SYS_PLL_reg((uintptr_t)(reg+0x8));
		/*Wait (reg+8)[0] =1*/
		if ( (val & 0x1) == 0x1){
			freq_pll = ( (val >> 1) & 0x0001FFFF ) / 10;
			/*Read (reg+8)[17:1] value and divide 10*/
			wait_count = 0;
			break;
		}
		wait_count++;
	}
	return freq_pll;
}

int get_divide_freq(unsigned int pll_div)
{
	switch(pll_div)
	{
		case 3:
			return 4;
		case 2:
			return 2;
		case 1:
		case 0:
			return 1;
		default:
			return 1;
	}
}

int get_acpu_divide_freq(unsigned int pll_div)
{
	switch(pll_div)
	{
		case 0x1F:
			return 32;
		case 0xF:
			return 16;
		default:
			if((pll_div & 0xF) == 0x7)
				return 8;
			else if((pll_div & 0x7) == 0x3)
				return 4;
			else if((pll_div & 0x3) == 0x1)
				return 2;
			else if((pll_div & 0x1) == 0x0)
				return 1;
			else
				return 1;
	}
}

int get_scpu_divide_freq(unsigned int pll_div)
{
	unsigned int tmp_pll_div = (pll_div & 0xFC);
	switch(tmp_pll_div)
	{
		case 0xB4:
			return 13;
		case 0xA8:
			return 10;
		case 0xA0:
			return 8;
		case 0x9C:
			return 7;
		case 0x98:
			return 6;
		case 0x94:
			return 5;
		case 0x8C:
			return 3;
		default:
			tmp_pll_div = (pll_div & 0x83);
			if (tmp_pll_div == 0x3)
				return 4;
			else if (tmp_pll_div == 0x2)
				return 2;
			else if (tmp_pll_div == 0)
				return 1;
			else
				return 1;
	}
}

static int do_bdinfo_pll(void)
{
#define __print_pll() \
    printf("%-12s = %4d MHz\n", name, freq);
#define __print_pll_div(freq_div) \
    printf("%-12s = %4d MHz (div %d)\n", name, freq, freq_div);

    const char *name;
	int divide_freg;
    unsigned int freq;

    printf("---- PLL information ----\n");

	name = "BUS PLL";
	freq = get_pll_frequency(PLLBUS);
	__print_pll();
	
	name = "BUS";
	divide_freg = get_divide_freq((get_SYS_PLL_reg(SYS_PLL_DIV_reg) & 0x3));
	freq = freq / divide_freg;
	__print_pll_div(divide_freg);
	
	name = "DCSB PLL";
	freq = get_pll_frequency(PLLDCSB);
	__print_pll();
	
	name = "DCSB";
	divide_freg = get_divide_freq(((get_SYS_PLL_reg(SYS_PLL_DIV_reg) >> 2) & 0x3));
	freq = freq / divide_freg;
	__print_pll_div(divide_freg);
	
	name = "ACPU PLL";
	freq = get_pll_frequency(PLLACPU);
	__print_pll();
	
	name = "ACPU";
	divide_freg = get_acpu_divide_freq(((get_SYS_PLL_reg(SYS_PLL_DIV_reg) >> 22) & 0x1F));
	freq = freq / divide_freg;
	__print_pll_div(divide_freg);
	
	name = "DDSA PLL";
	freq = get_pll_frequency(PLLDDSA);
	__print_pll();
	
	name = "DDSB PLL";
	freq = get_pll_frequency(PLLDDSB);
	__print_pll();
	
	name = "GPU PLL";
	freq = get_pll_frequency(PLLGPU);
	__print_pll();
	
	name = "VCPU PLL";
	freq = get_pll_frequency(PLLVCPU);
	__print_pll();
	
	name = "VCPU_2 PLL";
	freq = get_pll_frequency(PLLVCPU_2);
	__print_pll();
	
	name = "SCPU PLL";
	freq = get_scpu_pll_frequency(PLLSCPU);
	__print_pll();
	
	name = "SCPU";
	divide_freg = get_scpu_divide_freq(((get_SYS_PLL_reg(SYS_PLL_DIV_reg) >> 6) & 0xFF));
	freq = freq / divide_freg;
	__print_pll_div(divide_freg);

	return 0;
}

static void do_bdinfo_flash(void)
{
    printf("---- Flash information ----\n");

    if (boot_flash_type == BOOT_NOR_SERIAL) {
        printf("%-12s = %s\n", "boot_flash", "spi");
    } else if (boot_flash_type == BOOT_NAND) {
        printf("%-12s = %s\n", "boot_flash", "nand");
    } else if (boot_flash_type == BOOT_EMMC) {
        printf("%-12s = %s\n", "boot_flash", "emmc");
    } else {
        printf("%-12s = %s\n", "boot flash", "error");
    }
}

static const char *get_cpu_id_str(void)
{
	if (get_cpu_id() == RTK1395_CPU_ID)
		return "Hercules 1395";
	else if (get_cpu_id() == RTK1355_CPU_ID)
		return "Hercules 1355";
	return "Unrecognized";
}

static const char *get_chip_rev_str(void)
{
	switch(get_rtd139x_cpu_revision())
    {
        case RTD139x_CHIP_REVISION_A00:
            return "A00";
        case RTD139x_CHIP_REVISION_A01:
            return "A01";
        case RTD139x_CHIP_REVISION_B00:
            return "B00";
        default:
            return "Unrecognized";
    }
}

static void print_bdinfo(void)
{    
    printf("---- Hercules Rev. %s ----\n", get_chip_rev_str());
    printf("%-11s = %s\n", "cpu_id", get_cpu_id_str()); 

#if defined(CONFIG_CMD_NET)
	print_eth(0);
	printf("ip_addr     = %s\n", getenv("ipaddr"));
#endif
	printf("baudrate    = %d bps\n", gd->baudrate);
#if !(defined(CONFIG_SYS_ICACHE_OFF) && defined(CONFIG_SYS_DCACHE_OFF))
	print_num("TLB addr", gd->arch.tlb_addr);
#endif

}

int do_bdinfo(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	print_bdinfo();
	do_bdinfo_pll();
	do_bdinfo_ddr();
	do_bdinfo_flash();

	return 0;
}

#else
 #error "a case for this architecture does not exist!"
#endif

/* -------------------------------------------------------------------- */

U_BOOT_CMD(
	bdinfo,	1,	1,	do_bdinfo,
	"print Board Info structure",
	""
);
