/*
 * @author jjm2473
 * @since 2021-03-19
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <errno.h>
#include "io.h"
#include "search.h"
#include "crc32.h"

#define FACTORY_HEADER_FILE_NAME "tmp/factory/"

#define ENV_FILENAME_IN_FACTORY FACTORY_HEADER_FILE_NAME"env.txt"

#define CONFIG_ENV_SIZE (128 << 10)

#define ENV_HEADER_SIZE (sizeof(uint32_t))

#define ENV_SIZE (CONFIG_ENV_SIZE - ENV_HEADER_SIZE)

typedef struct environment_s {
	uint32_t	crc;		/* CRC32 over data bytes	*/
	unsigned char	data[ENV_SIZE]; /* Environment data		*/
} env_t;

struct hsearch_data env_htab;

int env_init(void)
{
	char buf[CONFIG_ENV_SIZE];
	env_t *env_ptr;
	if (fullread(ENV_FILENAME_IN_FACTORY, buf, CONFIG_ENV_SIZE) <= 0) {
		fprintf(stderr, "read %s failed!", ENV_FILENAME_IN_FACTORY);
		return -1;
	}
	env_ptr = (env_t *)buf;
	if (env_ptr->crc != crc32(0, env_ptr->data, ENV_SIZE)) {
		fprintf(stderr, "Environment import failed: crc32 error\n");
		return -1;
	}
	if (himport_r(&env_htab, env_ptr->data, ENV_SIZE, '\0', 0, 1, 0, NULL) == 0) {
		fprintf(stderr, "Environment import failed: errno = %d\n", errno);
		return -1;
	}
	return 0;
}

void print_env()
{
	char *res = NULL;
	ssize_t len;

	/* print whole list */
	len = hexport_r(&env_htab, '\n', 0, &res, 0, 0, NULL);

	if (len > 0) {
		puts(res);
		free(res);
	}
}

int set_env(const char* key, const char* value) {
	ENTRY e, *ep;
	e.key = key;
	e.data = value;
	hsearch_r(e, ENTER, &ep, &env_htab, 0);
	if (!ep) {
		fprintf(stderr, "## Error inserting \"%s\" variable, errno=%d\n",
			key, errno);
		return 1;
	}
	return 0;
}

int save_env(void)
{
	ssize_t	len;

	env_t env_new;
	unsigned char* res = env_new.data;

	len = hexport_r(&env_htab, '\0', 0, &res, ENV_SIZE, 0, NULL);
	if (len < 0) {
		fprintf(stderr, "Cannot export environment: errno = %d\n", errno);
		return 1;
	}
	env_new.crc = crc32(0, res, ENV_SIZE);

	if (fullwrite(ENV_FILENAME_IN_FACTORY, &env_new, CONFIG_ENV_SIZE)) {
		fprintf(stderr, "write %s failed!\n", ENV_FILENAME_IN_FACTORY);
		return 1;
	}

	return 0;
}

void env_deinit() {
	hdestroy_r(&env_htab);
}