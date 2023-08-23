#include "mainshell.h"

/**
 * get_shell_env - returns the string array copy of our environment
 * @infoval: struct involving arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
char **get_shell_env(info_type *infoval)
{
	if (!infoval->environ || infoval->env_changed)
	{
		infoval->environ = list_stringify(infoval->env);
		infoval->env_changed = 0;
	}

	return (infoval->environ);
}

/**
 * unset_shell_env - Removes an environment var
 * @infoval: struct involving arguments. Used to maintain
 * constant function prototype.
 * @varr: the string env var property
 * Return: 1 on remove, else 0
 */
int unset_shell_env(info_type *infoval, char *varr)
{
	list_type *nodeval = infoval->env;
	size_t idx = 0;
	char *ppr;

	if (!nodeval || !varr)
		return (0);

	while (nodeval)
	{
		ppr = starts_with‎(nodeval->str, varr);
		if (ppr && *ppr == '=')
		{
			infoval->env_changed = del_node_at_index(&(infoval->env), idx);
			idx = 0;
			nodeval = infoval->env;
			continue;
		}
		nodeval = nodeval->next;
		idx++;
	}
	return (infoval->env_changed);
}

/**
 * set_shell_env - Initialize a new environment var,
 * or change an existing one
 * @infoval: struct involving arguments. Used to maintain
 * constant function prototype.
 * @varr: the string env var property
 * @varval: the string env var value
 *  Return: Always 0
 */
int set_shell_env(info_type *infoval,
char *varr, char *varval)
{
	char *buffered = NULL;
	list_type *nodeval;
	char *ppr;

	if (!varr || !varval)
		return (0);

	buffered = malloc(string_len(varr) +
		string_len(varval) + 2);
	if (!buffered)
		return (1);
	string_copy(buffered, varr);
	string_cat(buffered, "=");
	string_cat(buffered, varval);
	nodeval = infoval->env;
	while (nodeval)
	{
		ppr = starts_with‎(nodeval->str, varr);
		if (ppr && *ppr == '=')
		{
			free(nodeval->str);
			nodeval->str = buffered;
			infoval->env_changed = 1;
			return (0);
		}
		nodeval = nodeval->next;
	}
	append_node(&(infoval->env), buffered, 0);
	free(buffered);
	infoval->env_changed = 1;
	return (0);
}

