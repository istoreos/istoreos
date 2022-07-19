#include <common.h>
//#include <string.h>
#include "pmic.h"

static int show_usage(void);
#define CMD_RET_USAGE show_usage()
#define CMD_PMIC_ERR -1
#define PMIC_SHOW_OK  0x1

static const struct cmd_pmic_data *gd;
static const unsigned int *regfields;
static int num_regfields;
static struct reg_info *regs;
static int num_regs;
static const char * const *col;
static int num_col;
static const char * const *row;
static int num_row;

static int tbl_val_to_str(const char * const tbl[], int tbl_size, int val, char *buf)
{
	if (val >= tbl_size)
		return CMD_PMIC_ERR;

	strcpy(buf, tbl[val]);
	return 0;
}
static int tbl_str_to_val(const char * const tbl[], int tbl_size, const char *str, int *val)
{
	int i;

	for (i = 0; i < tbl_size; i++)
		if (!strcmp(tbl[i], str)) {
			*val = i;
			return 0;
		}
	return CMD_PMIC_ERR;
}

static int verify_reg_val(const struct reg_info *reg, int val)
{
	int max = _BIT(PMIC_GET_SIZE(reg->info));
	if (0 <= val && val < max)
		return 0;
	return CMD_PMIC_ERR;
}

static const char *val_to_str(const struct reg_info *reg, int val, char *buf)
{
	if (verify_reg_val(reg, val)) {
		strcpy(buf, "out_of_range");
	} else if (tbl_val_to_str(reg->tbl, reg->tbl_size, val, buf)) {
		strcpy(buf, "val_to_str_fail");
	} 

	return buf;
}

static struct reg_info *get_reg_info_by_name(const char *name)
{
	int i;
	
	for (i = 0; i < num_regs; i++)
		if (strcmp(regs[i].name, name) == 0)
			return &regs[i];

	return NULL;
}

static void show_info(void)
{
	int i, j;
	
	pmic_init();

	for (i = 0; i < num_regs; i++)
		regs[i].flags &= ~PMIC_SHOW_OK;

	printf("%-5s", "");
	for (j = 0; j < num_col; j++)
		printf(" | %-15s", col[j]);
	printf("\n");

	for (i = 0; i < num_row; i++)
	{
		printf("%-5s", row[i]);
		for (j = 0; j < num_col; j++)
		{
			char name[20];
			struct reg_info *reg;

			sprintf(name, "%s_%s", row[i], col[j]);
			reg = get_reg_info_by_name(name);

			if (reg) {
			    unsigned char val;
			    char val_str[20];

			    pmic_get(reg->info, &val);
			    printf(" | %02x > %-10s", val, val_to_str(reg, val, val_str));
			    reg->flags |= PMIC_SHOW_OK;

			} else {
			    printf(" | --   %-10s", "");
			}
		}

		printf("\n");
	}

	printf("--\n");
	for (i = 0; i < num_regs; i++)
		if ((regs[i].flags & PMIC_SHOW_OK) == 0) {
			unsigned char val;
			char val_str[20];

			pmic_get(regs[i].info, &val);
			printf("%-12s - %02x > %s\n", regs[i].name, val, val_to_str(&regs[i], val, val_str));
		}

	pmic_exit();
}

static void show_list(void)
{
	int i;

	for (i = 0; i < num_regs; i++)
		printf("%s%s", i == 0 ? "" : " ", regs[i].name);
	printf("\n");
}

static void reg_access(const char *name, const char *new_val_str)
{
	struct reg_info *reg;
	unsigned char val;
	char val_str[100];

	if (!name || !name[0]) {
		printf("ERROR: empty name\n");
		return;
	}

	reg = get_reg_info_by_name(name);
	if (!reg) {
		printf("ERROR: invalid name: name = %s\n", name);
		return;
	}

	printf("%s [0x%02x: shift: %d length: %d]\n", reg->name, PMIC_GET_REG(reg->info),
		PMIC_GET_SHIFT(reg->info), PMIC_GET_SIZE(reg->info));

	pmic_init();
	pmic_get(reg->info, &val);
	pmic_exit();

	printf("cur_val: [0x%02x] %s\n", (unsigned char)val, val_to_str(reg, val, val_str));

	if (new_val_str) {
		int new_val;

		if (tbl_str_to_val(reg->tbl, reg->tbl_size, new_val_str, &new_val)) {
			printf("ERROR: failed to parse input: input = %s\n", new_val_str);
			return;
		}

		if (verify_reg_val(reg, new_val)) {
			printf("ERROR: val out of range: val = %d\n", new_val);
			return;
		}

		printf("new_val: [0x%02x] %s\n", new_val, val_to_str(reg, new_val, val_str));

		pmic_init();
		pmic_set(reg->info, new_val);
		pmic_exit();
	}
}

static void show_reg_voptions(const char *name)
{
	const struct reg_info *reg;
	char val_str[100];
	int i, max;

	if (!name || !name[0]) {
		printf("ERROR: empty name\n");
		return;
	}

	reg = get_reg_info_by_name(name);
	if (!reg) {
		printf("ERROR: invalid name: name = %s\n", name);
		return;
	}

	max = _BIT(PMIC_GET_SIZE(reg->info));
	printf("%s", val_to_str(reg, 0, val_str));
	for (i = 1; i < max; i++)
		printf(" %s", val_to_str(reg, i, val_str));
	printf("\n");
}

static int __init = 0;
static void cmd_pmic_init(void);

static int do_pmic(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	if (!__init) {
		cmd_pmic_init();
	}
	__init = 1;

	if (!gd) {
		printf("PMIC commands are not supported\n");
		return 0;
	}

	if (argc < 2)
		return CMD_RET_USAGE;

	switch (argv[1][0]) {
	case 'i':
		show_info();
		break;

	case 'l':
		show_list();
		break;

	case 'g':
		if (argc < 3)
			return CMD_RET_USAGE;

		reg_access(argv[2], NULL);
		break;

	case 's':
		if (argc < 4)
			return CMD_RET_USAGE;

		reg_access(argv[2], argv[3]);
		break;

	case 'o':
		if (argc < 3)
			return CMD_RET_USAGE;

		show_reg_voptions(argv[2]);
		break;

	default:
		return CMD_RET_USAGE;
	}
	return 0;
}

static int show_usage(void)
{
	printf("PMIC commands for %s\n"
		"pmic info               - show the values of all items\n"
		"pmic list               - list item names\n"
		"pmic get <item>         - get <item> value\n"
		"pmic option <item>      - list <item> value option\n"
		"pmic set <item> <val>   - set <item> with <val>\n",
		pmic_get_name()
	);
	return 0;
}

static void cmd_pmic_init(void)
{
	int i;

	gd = pmic_get_cmd_data();
	if (!gd)
		return;

	regfields = gd->regfields;
	num_regfields = gd->num_regfields;
	regs = gd->regs;
	num_regs = gd->num_regs;
	row = gd->row;
	num_row = gd->num_row;
	col = gd->col;
	num_col = gd->num_col;

	/* common */
	for (i = 0; i < num_regs; i++) {
		regs[i].info = regfields[regs[i].id];
	}

}

void cmd_pmic_entry(void)
{
	pmic_setup_pmic();
}


U_BOOT_CMD(pmic, 5, 0, do_pmic,
	"PMIC commands",
	"<cmd> [...]\n"
	"pmic info               - show the values of all items\n"
	"pmic list               - list item names\n"
	"pmic get <item>         - get <item> value\n"
	"pmic option <item>      - list <item> value option\n"
	"pmic set <item> <val>   - set <item> with <val>\n"
);

