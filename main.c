#include "mainshell.h"

/**
 * main - The starting function
 * @argcount: argument count
 * @argvec: argument vector
 *
 * Return: 0 on success, else 1
 */
int main(int argcount, char **argvec)
{
	info_type infoval[] = { INFO_INIT };
	int filedec = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (filedec)
			: "r" (filedec));

	if (argcount == 2)
	{
		filedec = open(argvec[1], O_RDONLY);
		if (filedec == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				puts_error(argvec[0]);
				puts_error(": 0: Cannot open ");
				puts_error(argvec[1]);
				putchar_error('\n');
				putchar_error(BUFFER_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		infoval->readfd = filedec;
	}
	spread_env_list(infoval);
	reader_history(infoval);
	make_hash(infoval, argvec);
	return (EXIT_SUCCESS);
}
