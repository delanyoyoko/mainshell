#include "mainshell.h"

/**
 * shell_history - shows the history list of the shell, one
 * command by line, follow by with line numbers, start at 0.
 * @infoval: struct involving arguments. Used to maintain
 * constant function prototype.
 *  Return: Always 0
 */
int shell_history(info_type *infoval)
{
	print_node_list(infoval->history);
	return (0);
}

/**
 * unset_alias - makes alias as string
 * @infoval: struct involving arguments. Used to maintain
 * constant function prototype
 * @strng: the alias string
 *
 * Return: 0 on success, 1 on error
 */
int unset_alias(info_type *infoval, char *strng)
{
	char *ppr;
	char cter;
	int retll;

	ppr = _strchr(strng, '=');
	if (!ppr)
		return (1);
	cter = *ppr;
	*ppr = 0;
	retll = del_node_at_index(&(infoval->alias),
		get_nodeIndex(infoval->alias,
		node_startsWith(infoval->alias, strng, -1)));
	*ppr = cter;
	return (retll);
}

/**
 * set_alias - makes string as alias
 * @infoval: struct involving arguments. Used to maintain
 * constant function prototype
 * @strng: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_type *infoval, char *strng)
{
	char *ppr;

	ppr = _strchr(strng, '=');
	if (!ppr)
		return (1);
	if (!*++ppr)
		return (unset_alias(infoval, strng));

	unset_alias(infoval, strng);
	return (prepend_node(&(infoval->alias), strng, 0) == NULL);
}

/**
 * print_alias - prints a string alias
 * @nodeval: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_type *nodeval)
{
	char *ppr = NULL;
	char *anod = NULL;

	if (nodeval)
	{
		ppr = _strchr(nodeval->str, '=');
		for (anod = nodeval->str; anod <= ppr; anod++)
		_putchar(*anod);
		_putchar('\'');
		_puts(ppr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * shell_alias - follows the alias builtin (man alias)
 * @infoval: struct involving arguments. Used to maintain
 * constant function prototype
 *  Return: Always 0
 */
int shell_alias(info_type *infoval)
{
	int idx = 0;
	char *ppr = NULL;
	list_type *nodeval = NULL;

	if (infoval->argc == 1)
	{
		nodeval = infoval->alias;
		while (nodeval)
		{
			print_alias(nodeval);
			nodeval = nodeval->next;
		}
		return (0);
	}
	for (idx = 1; infoval->argv[idx]; idx++)
	{
		ppr = _strchr(infoval->argv[idx], '=');
		if (ppr)
			set_alias(infoval, infoval->argv[idx]);
		else
			print_alias(node_startsWith(infoval->alias,
				infoval->argv[idx], '='));
	}

	return (0);
}

