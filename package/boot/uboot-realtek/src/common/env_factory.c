/*
 * (C) Copyright 2008-2011 Freescale Semiconductor, Inc.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/* #define DEBUG */

#include <common.h>

#include <command.h>
#include <environment.h>
#include <linux/stddef.h>
#include <malloc.h>
#include <search.h>
#include <errno.h>
#include <asm/arch/fw_info.h>
#include <asm/arch/system.h>
#include <asm/arch/factorylib.h>

#define ENV_FILENAME_IN_FACTORY	FACTORY_HEADER_FILE_NAME"env.txt"

char *env_name_spec = "FACTORY";

#ifdef ENV_IS_EMBEDDED
env_t *env_ptr = &environment;
#else /* ! ENV_IS_EMBEDDED */
env_t *env_ptr;
#endif /* ENV_IS_EMBEDDED */

DECLARE_GLOBAL_DATA_PTR;

int env_init(void)
{
	/* use default */
	gd->env_addr	= (ulong)&default_environment[0];
	gd->env_valid	= 1;

	return 0;
}

#ifdef CONFIG_CMD_SAVEENV
static inline int write_env(unsigned long size, const void *buffer)
{
	int ret = 0;

#ifdef CONFIG_SYS_FACTORY
	ret = factory_write(ENV_FILENAME_IN_FACTORY, (char *)buffer, size);
	if (ret != 0) { // failed case
		printf("[ENV] write_env failed\n");
	}
	else {
		ret = factory_save(); // sync data to flash
	}
#else
	printf("[ENV][WARN] CONFIG_SYS_FACTORY is not defined.\n");
#endif

	return ret;
}

int saveenv(void)
{
	ssize_t	len;
	char	*res;

	env_t *env_new = NULL;

	env_new = (env_t *)TEMP_BUFFER_FOR_FLASH_DATA_ADDR;

	res = (char *)&env_new->data;
	len = hexport_r(&env_htab, '\0', 0, &res, ENV_SIZE, 0, NULL);
	if (len < 0) {
		error("Cannot export environment: errno = %d\n", errno);
		return 1;
	}

	env_new->crc = crc32(0, &env_new->data[0], ENV_SIZE);

	printf("[ENV] Writing to Factory... \n");

	if (write_env(CONFIG_ENV_SIZE, (u_char *)env_new)) {
		puts("failed\n");
		return 1;
	}

	puts("done\n");
	return 0;
}
#endif /* CONFIG_CMD_SAVEENV */

static inline int read_env(unsigned long maxsize, const void **buffer)
{
	int ret = 0;

#ifdef CONFIG_SYS_FACTORY
	int env_length = 0;
	ret = factory_read((char *)ENV_FILENAME_IN_FACTORY, (char **)buffer, &env_length);
	if (ret != 0) { // failed case
		printf("[ENV] read_env from factory failed\n");
	}
	else {
		if (env_length > maxsize) {
			printf("[ENV] too large. (env_length=0x%x, maxsize=0x%lx)\n", env_length, maxsize);
		}
	}
#else
	printf("[ENV][WARN] CONFIG_SYS_FACTORY is not defined\n");
#endif

	return ret;
}

void delete_env(void)
{
	factory_delete(ENV_FILENAME_IN_FACTORY);
	factory_save();
}

void env_relocate_spec(void)
{
#if !defined(ENV_IS_EMBEDDED)
	char *buf = NULL;

	if (read_env((unsigned long)CONFIG_ENV_SIZE, (const void **)&buf)){
		set_default_env(NULL);
#ifdef NAS_ENABLE
		saveenv();
#endif
    }

	env_import(buf, 1);

#endif
}

