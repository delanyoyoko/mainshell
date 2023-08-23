#include "mainshell.h"

/**
 * shell_env - prints the current shell environment
 * @infoval: struct involving arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int shell_env(info_type *infoval)
{
	print_list_string(infoval->env);
	return (0);
}

/**
 * get_env - retrieves the value of an environment var
 * @infoval: struct involving arguments. Used to maintain
 * constant function prototype.
 * @var_name: environment var name
 *
 * Return: the variable's value
 */
char *get_env(info_type *infoval, const char *var_name)
{
	list_type *nodeval = infoval->env;
	char *ppr;

	while (nodeval)
	{
		ppr = starts_with(nodeval->str, var_name);
		if (ppr && *ppr)
			return (ppr);
		nodeval = nodeval->next;
	}
	return (NULL);
}

/**
 * shell_setenv - Initialize a new environment var,
 * or alter an existing one
 * @infoval: struct involving arguments. Used to maintain
 * constant function prototype.
 *  Return: Always 0
 */
int shell_setenv(info_type *infoval)
{
	if (infoval->argc != 3)
	{
		puts_error("Incorrect number of arguements\n");
		return (1);
	}
	if (set_shell_env(infoval, infoval->argv[1], infoval->argv[2]))
		return (0);
	return (1);
}

/**
 * shell_unsetenv - Removes an environment var
 * @infoval: struct involving arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int shell_unsetenv(info_type *infoval)
{
	int idx;

	if (infoval->argc == 1)
	{
		puts_error("Too few arguments.\n");
		return (1);
	}
	for (idx = 1; idx <= infoval->argc; idx++)
		unset_shell_env(infoval, infoval->argv[idx]);

	return (0);
}

/**
 * spread_env_list - spreads environment linked list
 * @infoval: struct involving arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int spread_env_list(info_type *infoval)
{
	list_type *nodeval = NULL;
	size_t idx;

	for (idx = 0; environ[idx]; idx++)
		prepend_node(&nodeval, environ[idx], 0);
	infoval->env = nodeval;
	return (0);
}


