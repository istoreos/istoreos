#include <common.h>
#include <asm/io.h>
#include <asm/arch/system.h>
#include <asm/arch/io.h>
#include <asm/arch/ddr.h>

DECLARE_GLOBAL_DATA_PTR;

static char default_fail[] = "UnKnown";

const char *get_dram_type_str(int dc_sel)
{
	void *dc_info = NULL;
	unsigned int dram_type;

	if (dc_sel > MAX_DC_COUNT -1)
		return default_fail;

	dc_info = (void*)(uintptr_t)(DC_INFO + (dc_sel * 4));
	dram_type = DC_INFO_DRAM_TYPE_GET(rtd_inl(dc_info));

	switch (dram_type) {
		case TYPE_LPDDR3:	return "LPDDR3";	break;
		case TYPE_DDR3:		return "DDR3";		break;
		case TYPE_DDR4:		return "DDR4";		break;
		default:		return "Unknown";	break;
	}

	return default_fail;
}

const char *get_dram_used_str(int dc_sel, int div_2)
{
	void *dc_info = NULL;
	t_DRAM_USED dram_used;
	static char ret_str[16] = "";

	if (dc_sel > MAX_DC_COUNT - 1)
		return default_fail;

	dc_info = (void*)(uintptr_t)(DC_INFO + (dc_sel * 4));
	dram_used = DC_INFO_DRAM_USED_GET(rtd_inl(dc_info));
	snprintf(ret_str, 16, "%dGb", div_2 ? (1 << dram_used) / 2 : 1 << dram_used);

	return ret_str;
}

const char *get_dram_mode_str(int dc_sel)
{
	void *dc_info = NULL;
	t_DRAM_MODE dram_mode;
	static char ret_str[16] = "";

	if (dc_sel > MAX_DC_COUNT - 1)
		return default_fail;

	dc_info = (void*)(uintptr_t)(DC_INFO + (dc_sel * 4));
	dram_mode = DC_INFO_DRAM_MODE_GET(rtd_inl(dc_info));
	snprintf(ret_str, 16, "x%d", 8 << dram_mode);

	return ret_str;
}

const char *get_dram_cell_str(int dc_sel, int div_2)
{
	void *dc_info = NULL;
	t_DRAM_CELL dram_cell;
	static char ret_str[16] = "";

	if (dc_sel > MAX_DC_COUNT - 1)
		return default_fail;

	dc_info = (void*)(uintptr_t)(DC_INFO + (dc_sel * 4));
	dram_cell = DC_INFO_DRAM_CELL_GET(rtd_inl(dc_info));
	snprintf(ret_str, 16, "%d", div_2 ? (1 << dram_cell) / 2 : 1 << dram_cell);

	return ret_str;
}

const char *get_dram_size_str(int dc_sel)
{
	void *dc_info = NULL;
	unsigned int dram_size;
	static char ret_str[16] = "";

	if (dc_sel > MAX_DC_COUNT - 1)
		return default_fail;

	dc_info = (void*)(uintptr_t)(DC_INFO + (dc_sel * 4));
	dram_size = DC_INFO_DRAM_SIZE_GET(rtd_inl(dc_info));
	snprintf(ret_str, 16, "%dGb", 1 + dram_size);

	return ret_str;
}

int get_dq_mode(int dc_sel)
{
	void *dc_info = NULL;

	if (dc_sel > MAX_DC_COUNT - 1)
		return -1;

	dc_info = (void*)(uintptr_t)(DC_INFO + (dc_sel * 4));
	return DC_INFO_DQ_MODE_GET(rtd_inl(dc_info));
}

/* return UNIT Gb */
unsigned int get_dc_size(int dc_sel)
{
	void *dc_info = NULL;

	if (dc_sel > MAX_DC_COUNT - 1)
		return 0;

	dc_info = (void*)(uintptr_t)(DC_INFO + (dc_sel * 4));
	return DC_INFO_DRAM_SIZE_GET(rtd_inl(dc_info)) + 1;
}

/* unit in Gb */
unsigned int get_total_ddr_size(void)
{
	unsigned int size = 0;
	unsigned int dc_sys_misc = rtd_inl(DC_SYS_MISC);

	if (DC_SYS_MISC_TWO_DCSYS_EN_GET(dc_sys_misc)) {
		size = DC_INFO_DRAM_SIZE_GET(rtd_inl(DC_INFO)) + DC_INFO_DRAM_SIZE_GET(rtd_inl(DC_INFO + 4)) + 2;
	} else {
		if (DC_SYS_MISC_OUT_TO_PHY_SEL_GET(dc_sys_misc))
			size = DC_INFO_DRAM_SIZE_GET(rtd_inl(DC_INFO + 4)) + 1;
		else
			size = DC_INFO_DRAM_SIZE_GET(rtd_inl(DC_INFO)) + 1;
	}

	return size;
}

void print_ddr_info(char * info_dc0, char * info_dc1)
{
	int dc_enable[MAX_DC_COUNT] = {0};
	unsigned int dc_sys_misc = rtd_inl(DC_SYS_MISC);
	int i;

	if (DC_SYS_MISC_TWO_DCSYS_EN_GET(dc_sys_misc)) {
		dc_enable[0] = 1;
		dc_enable[1] = 1;
	} else { // DC_SYS_MISC_TWO_DCSYS_EN not set, check DC0 or DC1 used
		if (DC_SYS_MISC_OUT_TO_PHY_SEL_GET(dc_sys_misc))
			dc_enable[1] = 1;
		else
			dc_enable[0] = 1;
	}

	for (i = 0 ; i < MAX_DC_COUNT ; i++) {
		if (!dc_enable[i])
			continue;
		if (get_dq_mode(i) == HYBR_DQ) {
			printf("%s", info_dc0);
			printf("DC%d %s, total size is %s(%s)x%s + %s(%s)x%s=%s\n",
				i, get_dram_type_str(i),
				get_dram_used_str(i, 0), get_dram_mode_str(i), get_dram_cell_str(i, 1),
				get_dram_used_str(i, 1), get_dram_mode_str(i), get_dram_cell_str(i, 1),
				get_dram_size_str(i));
		} else { // FULL_DQ & HALF_DQ
			if ( i==0 )
				printf("%s", info_dc0);
			else
				printf("%s", info_dc1);
			printf("DC%d %s, total size is %s(%s)x%s=%s\n",
				i, get_dram_type_str(i), get_dram_used_str(i, 0), get_dram_mode_str(i),
				get_dram_cell_str(i, 0), get_dram_size_str(i));
		}
	}
}
