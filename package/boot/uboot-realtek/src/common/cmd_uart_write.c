#include <common.h>
#include <command.h>
#include <asm/arch/factorylib.h>

static int do_uart_w(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[]);
static int do_uart_w_mac(const char *mac_value);
static int do_uart_w_sn(const char *addr, int len);

static int do_uart_w(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{
	int length = 0, option = 0, bRes = 1;
	char *addr = NULL;
	char *mac_value = NULL;
	char *cmd = argv[0];
	if (strcmp(cmd, "uart_write"))
	{
		printf("Unknown command '%s' - try 'help'\n", cmd);
		return bRes;
	}
	printf("argc :%d \n", argc);

	if ((argc > 4) || (argc == 1))
	{
		printf("argc :%d ,error!\n", argc);
		cmd_usage(cmdtp);
		return bRes;
	}
	else if (argc == 2)
	{
		option = 0;
		mac_value = argv[1];
	}
	else if (argc == 3)
	{
		addr = (char *)simple_strtoul(argv[1], NULL, 16);
		length = (unsigned int)simple_strtoul(argv[2], NULL, 16);
		printf("length :%d\n", length);
		printf("addr :%s\n", addr);
		option = 1;
	}
	else if (argc == 4)
	{
		mac_value = argv[1];
		addr = (char *)simple_strtoul(argv[2], NULL, 16);
		length = (unsigned int)simple_strtoul(argv[3], NULL, 16);
		printf("length :%d\n", length);
		printf("addr :%s\n", addr);
		option = 2;
	}

	switch (option)
	{
	case 0:
		bRes = do_uart_w_mac(mac_value);
		if (bRes != 0)
		{
			printf("only write mac fail!\n");
		}
		break;
	case 1:
		bRes = do_uart_w_sn(addr, length);
		if (bRes != 0)
		{
			printf("only write sn fail!\n");
		}
		break;
	case 2:
		bRes = do_uart_w_mac(mac_value);
		if (bRes != 0)
		{
			printf("write mac fail!\n");
		}
		else
		{
			bRes = do_uart_w_sn(addr, length);
			if (bRes != 0)
			{
				printf("write sn fail!\n");
			}
		}
		break;
	default:
		printf("option fail !\n");
		break;
	}

	if (bRes != 0)
	{
		printf("***** FAILFAIL *****\n");
		printf("***** FAILFAIL *****\n");
		printf("***** FAILFAIL *****\n");
	}
	else
	{
		printf("***** OKOK *****\n");
		printf("***** OKOK *****\n");
		printf("***** OKOK *****\n");
	}
	return bRes;
}

static int do_uart_w_mac(const char *mac_value)
{

	int bRe = 1, num = 0;
	char *mac_check;

	printf("ethaddr:%s\n", mac_value);
	setenv("ethaddr", mac_value);
	if ((mac_check = getenv("ethaddr")) == NULL)
	{
		printf("getenv ethaddr fail !\n");
		printf("***** FAILFAIL *****\n");
		printf("***** FAILFAIL *****\n");
		printf("***** FAILFAIL *****\n");
	}
	else
	{

		for (num = 0; num < 2; num++)
		{
			//Removed by Aaron==>bRe=saveenv();
#ifdef CONFIG_ENV_IS_IN_FACTORY
			bRe = saveenv();
#endif
			if (bRe != 0)
			{
				printf("mac envsave fail!\n");
				break;
			}
		}
		if (bRe == 0)
		{
			if ((strncmp(mac_value, mac_check, 17)) != 0)
			{
				printf("compare mac fail !\n");
				printf("***** FAILFAIL *****\n");
				printf("***** FAILFAIL *****\n");
				printf("***** FAILFAIL *****\n");
				bRe = 1;
			}
			else
			{
				bRe = 0;
			}
		}
	}
	return bRe;
}

static int do_uart_w_sn(const char *addr, int len)
{

	int bRe = 1, num = 0;

	for (num = 0; num < 2; num++)
	{
		bRe = factory_write("tmp/factory/sn.txt", (char *)addr, len);
		if (bRe != 0)
		{
			break;
		}
		bRe = factory_save();
		if (bRe != 0)
		{
			break;
		}
	}

	return bRe;
}
U_BOOT_CMD(
	uart_write, 4, 0, do_uart_w,
	"for uart mp tool burn mac and sn key",
	"\nonly write mac : uart_writ [mac] \n"
	"only write sn  : uart_writ [load addr] [file lenght(hex)]\n"
	"both           : uart_writ [mac] [load addr] [file lenght(hex)]\n");
