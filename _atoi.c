#include "mainshell.h"

/**
 * get_interactive - determines whether shell is in interactive mode
 * @info: a struct address
 *
 * Return: 0 if shell not in interactive mode, or 1 if otherwise
 */
int get_interactive(info_type *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delimitor - checks whether character is a delimetor
 * @c: the character to check
 * @delimitor: the delimetor string
 * Return: 0 if not a delimitor, otherwise 1 for true
 */
int is_delimitor(char c, char *delimitor)
{
	while (*delimitor)
		if (*delimitor++ == c)
			return (1);
	return (0);
}

/**
 * is_alpha - determines an alphabetic character
 * @c: The character to determine
 * Return: 0 if character is not alphabetic, 1 otherwise
 */

int is_alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - string to an integer convertion
 * @s: the string to be converted
 * Return: converted number or 0 if no number in the string
 */

int _atoi(char *s)
{
	int idx;
	int indication = 1;
	int signal = 0;
	int outstage;
	unsigned int res = 0;

	for (idx = 0; s[idx] != '\0' && signal != 2; idx++)
	{
		if (s[idx] == '-')
			indication *= -1;

		if (s[idx] >= '0' && s[idx] <= '9')
		{
			signal = 1;
			res *= 10;
			res += (s[idx] - '0');
		}
		else if (signal == 1)
			signal = 2;
	}

	if (indication == -1)
		outstage = -res;
	else
		outstage = res;

	return (outstage);
}

