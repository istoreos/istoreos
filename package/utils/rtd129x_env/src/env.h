#ifndef __ENV_H__
#define __ENV_H__

int env_init(void);
void print_env();
int set_env(const char* key, const char* value);
int save_env(void);
void env_deinit();

#endif