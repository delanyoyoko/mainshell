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
	list_t *nodeval = infoval->env;
	size_t idx = 0;
	char *ppr;

	if (!nodeval || !varr)
		return (0);

	while (nodeval)
	{
		ppr = startsWith(node->str, varr);
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
 * @varprop: the string env var property
 * @varval: the string env var value
 *  Return: Always 0
 */
int set_shell_env(info_type *infoval, char *varprop, char *varval)
{
	char *buffered = NULL;
	list_t *nodeval;
	char *ppr;

	if (!varprop || !varval)
		return (0);

	buffered = malloc(_strlen(var) + _strlen(varval) + 2);
	if (!buffered)
		return (1);
	string_copy(buffered, varprop);
	string_cat(buffered, "=");
	string_cat(buffered, varval);
	node = infoval->env;
	while (nodeval)
	{
		p = startsWith(nodeval->str, varprop);
		if (p && *p == '=')
		{
			free(nodeval->str);
			nodeval->str = buffered;
			infoval->env_changed = 1;
			return (0);
		}
		nodeval = nodeval->next;
	}
	add_node_at_end(&(infoval->env), buffered, 0);
	free(buffered);
	infoval->env_changed = 1;
	return (0);
}

