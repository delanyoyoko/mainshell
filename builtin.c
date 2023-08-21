#include "mainshell.h"

/**
 * shell_exit - helps to exits the shell
 * @infoval: struct involving arguments. Used to maintain
 * constant function prototype.
 * Return: exits the shell with a given exit status code
 * (0) if info.argv[0] is not equal to  "exit"
 */
int shell_exit(info_type *infoval)
{
	int check_exit;

	if (infoval->argv[1])
	{
		check_exit = atoi_error(infoval->argv[1]);
		if (check_exit == -1)
		{
			infoval->status = 2;
			print_err(infoval, "Illegal number: ");
			puts_error(infoval->argv[1]);
			putchar_error('\n');
			return (1);
		}
		infoval->err_num = atoi_error(infoval->argv[1]);
		return (-2);
	}
	infoval->err_num = -1;
	return (-2);
}

/**
 * shell_cd - changes the current working directory or folder
 * @infoval: struct involving arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int shell_cd(info_type *infoval)
{
	char *shll;
	char *fold;
	char buffered[1024];
	int ch_dir_ret;

	shll = getcwd(buffered, 1024);
	if (!shll)
		_puts("Failed to get current working directory.\n");
	if (!infoval->argv[1])
	{
		fold = get_env(infoval, "HOME=");
		if (!fold)
			ch_dir_ret = 
				chdir((fold = get_env(infoval, "PWD=")) ? fold : "/");
		else
			ch_dir_ret = chdir(fold);
	}
	else if (string_cmp(infoval->argv[1], "-") == 0)
	{
		if (!get_env(infoval, "OLDPWD="))
		{
			_puts(shll);
			_putchar('\n');
			return (1);
		}
		_puts(get_env(infoval, "OLDPWD=")), _putchar('\n');
		ch_dir_ret = 
			chdir((fold = get_env(infoval, "OLDPWD=")) ? fold : "/");
	}
	else
		ch_dir_ret = chdir(infoval->argv[1]);
	if (ch_dir_ret == -1)
	{
		print_err(infoval, "can't cd to dir");
		puts_error(infoval->argv[1]), putchar_error('\n');
	}
	else
	{
		set_shell_env(infoval, "OLDPWD", get_env(infoval, "PWD="));
		set_shell_env(infoval, "PWD", getcwd(buffered, 1024));
	}
	return (0);
}

/**
 * shell_help - changes the current working directory of the process
 * @infoval: struct involving arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int shell_help(info_type *infoval)
{
	char **arg_list;

	arg_list = infoval->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_list);
	return (0);
}

