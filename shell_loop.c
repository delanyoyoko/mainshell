#include "mainshell.h"

/**
 * make_hash - shell loop for main entry point
 * @infoval: the parameter value for info struct
 * @argvec: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, else the error code
 */
int make_hash(info_type *infoval, char **argvec)
{
	ssize_t ret = 0;
	int builtin_ret = 0;

	while (ret != -1 && builtin_ret != -2)
	{
		clear_info(infoval);
		if (get_interactive(infoval))
			_puts("$ ");
		putchar_error(BUFFER_FLUSH);
		ret = accept_input(infoval);
		if (ret != -1)
		{
			set_info(infoval, argvec);
			builtin_ret = find_builtin(infoval);
			if (builtin_ret == -1)
				find_cmd(infoval);
		}
		else if (get_interactive(infoval))
			_putchar('\n');
		free_info(infoval, 0);
	}
	compose_history(infoval);
	free_info(infoval, 1);
	if (!get_interactive(infoval) && infoval->status)
		exit(infoval->status);
	if (builtin_ret == -2)
	{
		if (infoval->err_num == -1)
			exit(infoval->status);
		exit(infoval->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin exec command
 * @infoval: the parameter & return infoval struct
 *
 * Return: -1 if builtin not found,
 * 	0 if builtin executed successfully,
 * 	1 if builtin found but not successful,
 * 	2 if builtin signals exit()
 */
int find_builtin(info_type *infoval)
{
	int idx, builtin_ret = -1;
	builtin_table builtintable[] = {
		{"exit", shell_exit},
		{"env", shell_env},
		{"help", shell_help},
		{"history", shell_history},
		{"setenv", shell_setenv},
		{"unsetenv", shell_unsetenv},
		{"cd", shell_cd},
		{"alias", shell_alias},
		{NULL, NULL}
	};

	for (idx = 0; builtintable[idx].type; idx++)
		if (string_cmp(infoval->argv[0],
			builtintable[idx].type) == 0)
		{
			infoval->line_count++;
			builtin_ret = builtintable[idx].func(infoval);
			break;
		}
	return (builtin_ret);
}

/**
 * find_cmd - determines a command in PATH
 * @infoval: the parameter & return infoval struct
 *
 * Return: void
 */
void find_cmd(info_type *infoval)
{
	char *pathstrng = NULL;
	int idx, kdx;

	infoval->path = infoval->argv[0];
	if (infoval->linecount_flag == 1)
	{
		infoval->line_count++;
		infoval->linecount_flag = 0;
	}
	for (idx = 0, kdx = 0; infoval->arg[idx]; idx++)
		if (!is_delimitor(infoval->arg[idx], " \t\n"))
			kdx++;
	if (!kdx)
		return;

	pathstrng = find_path(infoval, get_env(infoval, "PATH="),
		infoval->argv[0]);
	if (pathstrng)
	{
		infoval->path = pathstrng;
		fork_cmd(infoval);
	}
	else
	{
		if ((get_interactive(infoval) || get_env(infoval, "PATH=")
					|| infoval->argv[0][0] == '/') && is_cmd(infoval,
			infoval->argv[0]))
			fork_cmd(infoval);
		else if (*(infoval->arg) != '\n')
		{
			infoval->status = 127;
			print_err(infoval, "NOT FOUND\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec command thread to run cmd
 * @infoval: the parameter & return infoval struct
 *
 * Return: void
 */
void fork_cmd(info_type *infoval)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(infoval->path, infoval->argv,
			get_shell_env(infoval)) == -1)
		{
			free_info(infoval, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(infoval->status));
		if (WIFEXITED(infoval->status))
		{
			infoval->status = WEXITSTATUS(infoval->status);
			if (infoval->status == 126)
				print_err(infoval, "Permission denied\n");
		}
	}
}
