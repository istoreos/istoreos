/*
 * LowLevel function for SPI NOR environment support
 *
 */
#include <common.h>
#include <command.h>
#include <environment.h>
#include <linux/stddef.h>
#include <rtkspi.h>
//#include <search.h>
#include <errno.h>

DECLARE_GLOBAL_DATA_PTR;

env_t *env_ptr;

char *env_name_spec = "SPI NOR";

void env_relocate_spec(void)
{
	uint32_t crc, new = 0;
	unsigned off;
	char buf[CONFIG_ENV_SIZE];

	/* Read old CRC */
	rtkspi_read(CONFIG_ENV_ADDR + offsetof(env_t, crc),
		       sizeof(ulong), (unsigned int*)&crc);

	/* Read whole environment */
	rtkspi_read(CONFIG_ENV_ADDR, CONFIG_ENV_SIZE, (unsigned int*)buf);

	/* Calculate the CRC */
	off = offsetof(env_t, data);
	new = crc32(new, (unsigned char *)(buf + off), ENV_SIZE);

	if (crc == new)
		env_import(buf, 1);
	else
		set_default_env("!bad CRC");
}

#ifdef CONFIG_ENV_OFFSET_REDUND
#error No support for redundant environment on dataflash yet!
#endif

#ifdef CONFIG_CMD_SAVEENV
int saveenv(void)
{
	env_t env_new;
	int ret = 0;

	if( (ret = env_export(&env_new)) \
	    || (ret = rtkspi_erase(CONFIG_ENV_ADDR, CONFIG_ENV_SIZE)) ){
		return ret;
	}
	rtkspi_write8(CONFIG_ENV_ADDR, (unsigned int)(uintptr_t)&env_new, CONFIG_ENV_SIZE);

	return ret;
}
#endif

/*
 * Initialize environment use
 *
 * We are still running from ROM, so data use is limited.
 * Use a (moderately small) buffer on the stack
 */
int env_init(void)
{
	/* use default */
	gd->env_addr = (ulong)&default_environment[0];
	gd->env_valid = 1;

	return 0;
}
