#include "mainshell.h"

/**
 * isChain - determines if current char in buffer
 * is a chain delimeter
 * @infoval: the info parameter struct
 * @buffered: the char in buffer
 * @ppr: address of current position in buffered
 *
 * Return: 1 if chain delimeter, else 0
 */
int isChain(info_type *infoval, char *buffered,
size_t *ppr)
{
	size_t jdx = *ppr;

	if (buffered[jdx] == '|' && buffered[jdx + 1] == '|')
	{
		buffered[jdx] = 0;
		jdx++;
		infoval->cmd_buf_type = CMD_OR;
	}
	else if (buffered[jdx] == '&' && buffered[jdx + 1] == '&')
	{
		buffered[jdx] = 0;
		jdx++;
		infoval->cmd_buf_type = CMD_AND;
	}
	else if (buffered[jdx] == ';')
	{
		buffered[jdx] = 0;
		infoval->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*ppr = jdx;
	return (1);
}

/**
 * look_chain - checks whether to should continue
 * chaining based on previous status
 * @infoval: the info parameter struct
 * @buffered: the char in buffer
 * @ppr: address of current position in buffered
 * @idx: starting position in buffered
 * @lenval: length of buffered
 *
 * Return: Void
 */
void look_chain(info_type *infoval, char *buffered,
size_t *ppr, size_t idx, size_t lenval)
{
	size_t jdx = *ppr;

	if (infoval->cmd_buf_type == CMD_AND)
	{
		if (infoval->status)
		{
			buffered[idx] = 0;
			jdx = lenval;
		}
	}
	if (infoval->cmd_buf_type == CMD_OR)
	{
		if (!infoval->status)
		{
			buffered[idx] = 0;
			jdx = lenval;
		}
	}

	*ppr = jdx;
}

/**
 * change_alias - changes an alias in the tokenized string
 * @infoval: the parameter struct
 *
 * Return: 1 if replaced, else 0
 */
int change_alias(info_type *infoval)
{
	int idx;
	list_type *nodeval;
	char *ppr;

	for (idx = 0; idx < 10; idx++)
	{
		nodeval = node_startsWith(infoval->alias,
			infoval->argv[0], '=');
		if (!nodeval)
			return (0);
		free(infoval->argv[0]);
		ppr = char_string(nodeval->str, '=');
		if (!ppr)
			return (0);
		ppr = dup_string(ppr + 1);
		if (!ppr)
			return (0);
		infoval->argv[0] = ppr;
	}
	return (1);
}

/**
 * change_vars - changes vars in the tokenized string
 * @infoval: the info parameter struct
 *
 * Return: 1 if replaced, else 0
 */
int change_vars(info_type *infoval)
{
	int idx = 0;
	list_type *nodeval;

	for (idx = 0; infoval->argv[idx]; idx++)
	{
		if (infoval->argv[idx][0] != '$' || !infoval->argv[idx][1])
			continue;

		if (!string_cmp(infoval->argv[idx], "$?"))
		{
			change_string(&(infoval->argv[idx]),
					dup_string(convert_num(infoval->status, 10, 0)));
			continue;
		}
		if (!string_cmp(infoval->argv[idx], "$$"))
		{
			change_string(&(infoval->argv[idx]),
					dup_string(convert_num(getpid(), 10, 0)));
			continue;
		}
		nodeval = node_startsWith(infoval->env, &infoval->argv[idx][1], '=');
		if (nodeval)
		{
			change_string(&(infoval->argv[idx]),
					dup_string(char_string(nodeval->str, '=') + 1));
			continue;
		}
		change_string(&infoval->argv[idx], dup_string(""));

	}
	return (0);
}

/**
 * change_string - changes a string
 * @oldStrng: address of old string
 * @newStrng: new string
 *
 * Return: 1 if replaced, else 0
 */
int change_string(char **oldStrng, char *newStrng)
{
	free(*oldStrng);
	*oldStrng = newStrng;
	return (1);
}
