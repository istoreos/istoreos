#ifndef _REALTEK_DDR_H_
#define _REALTEK_DDR_H_

#define MAX_DC_COUNT		2 // DC0 & DC1

// DQ MODE
#define FULL_DQ			0x1
#define HALF_DQ			0x2
#define HYBR_DQ			0x4

//DDR TYPE
#define TYPE_LPDDR3		(0xB) //1011
#define TYPE_DDR3		(0x3) //0011
#define TYPE_DDR4		(0x4) //0100

//DRAM USED
typedef enum {
	DRAM_USED_1Gb = 0x0,
	DRAM_USED_2Gb,
	DRAM_USED_4Gb,
	DRAM_USED_8Gb,
	DRAM_USED_16Gb,
	DRAM_USED_UNDEF,
} t_DRAM_USED;

//DRAM MODE
typedef enum {
	DRAM_MODE_x8 = 0x0,
	DRAM_MODE_x16,
	DRAM_MODE_x32,
	DRAM_MODE_UNDEF,
} t_DRAM_MODE;

//DRAM CELL
typedef enum {
	DRAM_CELL_1 = 0x0,
	DRAM_CELL_2,
	DRAM_CELL_4,
	DRAM_CELL_UNDEF,
} t_DRAM_CELL;

#define DC_INFO			0x980081f0
#define DC_INFO_DRAM_SIZE_SHIFT		16
#define DC_INFO_DRAM_SIZE_MASK		(0x000f0000)
#define DC_INFO_DRAM_SIZE_GET(d)	(((d) & DC_INFO_DRAM_SIZE_MASK) >> DC_INFO_DRAM_SIZE_SHIFT)
#define DC_INFO_DRAM_CELL_SHIFT		14
#define DC_INFO_DRAM_CELL_MASK		(0x0000c000)
#define DC_INFO_DRAM_CELL_GET(d)	(((d) & DC_INFO_DRAM_CELL_MASK) >> DC_INFO_DRAM_CELL_SHIFT)
#define DC_INFO_DRAM_MODE_SHIFT		12
#define DC_INFO_DRAM_MODE_MASK		(0x00003000)
#define DC_INFO_DRAM_MODE_GET(d)	(((d) & DC_INFO_DRAM_MODE_MASK) >> DC_INFO_DRAM_MODE_SHIFT)
#define DC_INFO_DRAM_USED_SHIFT		8
#define DC_INFO_DRAM_USED_MASK		(0x00000700)
#define DC_INFO_DRAM_USED_GET(d)	(((d) & DC_INFO_DRAM_USED_MASK) >> DC_INFO_DRAM_USED_SHIFT)
#define DC_INFO_DQ_MODE_SHIFT		4
#define DC_INFO_DQ_MODE_MASK		(0x000000f0)
#define DC_INFO_DQ_MODE_GET(d)		(((d) & DC_INFO_DQ_MODE_MASK) >> DC_INFO_DQ_MODE_SHIFT)
#define DC_INFO_DRAM_TYPE_SHIFT		0
#define DC_INFO_DRAM_TYPE_MASK		(0x0000000f)
#define DC_INFO_DRAM_TYPE_GET(d)	(((d) & DC_INFO_DRAM_TYPE_MASK) >> DC_INFO_DRAM_TYPE_SHIFT)

/*
#define DC1_INFO			0x980081f4
#define DC1_INFO_DRAM_SIZE_SHIFT	(16)
#define DC1_INFO_DRAM_SIZE_MASK		(0x000f0000)
#define DC1_INFO_DRAM_SIZE_GET(d)	(((d) & DC_INFO_DRAM_SIZE_MASK) >> DC_INFO_DRAM_SIZE_SHIFT)
#define DC1_INFO_DRAM_CELL_SHIFT	(14)
#define DC1_INFO_DRAM_CELL_MASK		(0x0000c000)
#define DC1_INFO_DRAM_CELL_GET(d)	(((d) & DC_INFO_DRAM_CELL_MASK) >> DC_INFO_DRAM_CELL_SHIFT)
#define DC1_INFO_DRAM_MODE_SHIFT	(12)
#define DC1_INFO_DRAM_MODE_MASK		(0x00003000)
#define DC1_INFO_DRAM_MODE_GET(d)	(((d) & DC_INFO_DRAM_MODE_MASK) >> DC_INFO_DRAM_MODE_SHIFT)
#define DC1_INFO_DRAM_USED_SHIFT	(8)
#define DC1_INFO_DRAM_USED_MASK		(0x00000700)
#define DC1_INFO_DRAM_USED_GET(d)	(((d) & DC_INFO_DRAM_USED_MASK) >> DC_INFO_DRAM_USED_SHIFT)
#define DC1_INFO_DQ_MODE_SHIFT		(4)
#define DC1_INFO_DQ_MODE_MASK		(0x000000f0)
#define DC1_INFO_DQ_MODE_GET(d)		(((d) & DC_INFO_DQ_MODE_MASK) >> DC_INFO_DQ_MODE_SHIFT)
#define DC1_INFO_DRAM_TYPE_SHIFT	(0)
#define DC1_INFO_DRAM_TYPE_MASK		(0x0000000f)
#define DC1_INFO_DRAM_TYPE_GET(d)	(((d) & DC_INFO_DRAM_TYPE_MASK) >> DC_INFO_DRAM_TYPE_SHIFT)
*/

#define DC_SYS_MISC				0x98008004
#define DC_SYS_MISC_OUT_TO_PHY_SEL_SHIFT	(21)
#define DC_SYS_MISC_OUT_TO_PHY_SEL_MASK		(0x00200000)
#define DC_SYS_MISC_OUT_TO_PHY_SEL_GET(d)	(((d) & DC_SYS_MISC_OUT_TO_PHY_SEL_MASK) >> DC_SYS_MISC_OUT_TO_PHY_SEL_SHIFT)
#define DC_SYS_MISC_TWO_DCSYS_EN_SHIFT		(0)
#define DC_SYS_MISC_TWO_DCSYS_EN_MASK		(0x00000001)
#define DC_SYS_MISC_TWO_DCSYS_EN_GET(d)		(((d) & DC_SYS_MISC_TWO_DCSYS_EN_MASK) >> DC_SYS_MISC_TWO_DCSYS_EN_SHIFT)

const char *get_dram_type_str(int dc_sel);
const char *get_dram_used_str(int dc_sel, int div_2);
const char *get_dram_mode_str(int dc_sel);
const char *get_dram_cell_str(int dc_sel, int div_2);
const char *get_dram_size_str(int dc_sel);
int get_dq_mode(int dc_sel);
unsigned int get_dc_size(int dc_sel);
unsigned int get_total_ddr_size(void);
void print_ddr_info(char * info_dc0, char * info_dc1);

#endif /* _REALTEK_DDR_H_ */
