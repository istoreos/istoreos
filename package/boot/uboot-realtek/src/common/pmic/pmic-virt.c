#include <compiler.h>
#include <stdio.h>
#include <pmic.h>

/*
 * please implement this function in
 * your platform to return PMIC name
 */

__WEAK const char *pmic_get_name(void)
{
	return NULL;
}

__WEAK const struct cmd_pmic_data *pmic_get_cmd_data(void)
{
	return NULL;
}

__WEAK void pmic_setup_pmic(void)
{}

