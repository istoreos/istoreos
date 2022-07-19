/*
 * @author jjm2473
 * @since 2021-03-19
 */

#include <stdio.h>
#include <string.h>
#include "env.h"

int do_set_env(const char* key, const char* value) {
	int ret;
	if (env_init()) {
		return -1;
	}
	ret = set_env(key, value) || save_env();
	env_deinit();
	return ret;
}

int do_list_env() {
	if (env_init()) {
		return -1;
	}
	print_env();
	env_deinit();
	return 0;
}

int main(int argc, char *argv[]) {
	if (argc > 1) {
		if (strcmp("set", argv[1]) == 0) {
			if (argc != 4) {
				fprintf(stderr, "please provide key and value\n");
				return -1;
			}
			return do_set_env(argv[2], argv[3]);
		} else if (strcmp("list", argv[1]) == 0) {
			return do_list_env();
		}
	} else {
		printf("Usage: %s <CMD>\n\
CMD:\n\
\tset <KEY> <VALUE>\tSet Environment\n\
\tlist\tPrint Environment\n\
", argv[0]);

	}
	return -1;
}