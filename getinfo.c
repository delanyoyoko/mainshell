#include "shell.h"

/**
 * clear_info - init info_type struct
 * @infoval: infoval struct address
 */
void clear_info(info_type *infoval)
{
	infoval->arg = NULL;
	infoval->argv = NULL;
	infoval->path = NULL;
	infoval->argc = 0;
}

/**
 * set_info - init info_type struct
 * @infoval: infoval struct address
 * @arg_vec: argument vector
 */
void set_info(info_type *infoval, char **arg_vec)
{
	int idx = 0;

	infoval->fname = arg_vec[0];
	if (infoval->arg)
	{
		infoval->argv = tokenize_string(infoval->arg, " \t");
		if (!infoval->argv)
		{
			infoval->argv = malloc(sizeof(char *) * 2);
			if (infoval->argv)
			{
				infoval->argv[0] = dup_string(infoval->arg);
				infoval->argv[1] = NULL;
			}
		}
		for (idx = 0; infoval->argv && infoval->argv[idx]; idx++)
			;
		infoval->argc = idx;

		change_alias(infoval);
		change_vars(infoval);
	}
}

/**
 * free_info - frees info_type struct fields
 * @infoval: infoval struct address
 * @all_fields: sets true if freeing all_fields fields
 */
void free_info(info_type *infoval, int all_fields)
{
	ffree(infoval->argv);
	infoval->argv = NULL;
	infoval->path = NULL;
	if (all_fields)
	{
		if (!infoval->cmd_buf)
			free(infoval->arg);
		if (infoval->env)
			free_list(&(infoval->env));
		if (infoval->history)
			free_list(&(infoval->history));
		if (infoval->alias)
			free_list(&(infoval->alias));
		ffree(infoval->environ);
			infoval->environ = NULL;
		bfree((void **)infoval->cmd_buf);
		if (infoval->readfd > 2)
			close(infoval->readfd);
		_putchar(BUFFER_FLUSH);
	}
}

