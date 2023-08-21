#include "mainshell.h"

/**
 * atoi_error - converts an error string to an integer
 * @strng: string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int atoi_error(char *strng)
{
	int idx = 0;
	unsigned long int res = 0;

	if (*strng == '+')
		strng++; 
	for (idx = 0;  strng[idx] != '\0'; idx++)
	{
		if (strng[idx] >= '0' && strng[idx] <= '9')
		{
			res *= 10;
			res += (strng[idx] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * print_err - prints an error message
 * @infoval: the parameter & return infoval struct
 * @errstrng: a string involving specified the error type
 * Return: void if no numbers in string, converted number
 * otherwise -1 on error
 */
void print_err(info_type *infoval, char *errstrng)
{
	puts_error(infoval->fname);
	puts_error(": ");
	print_deci(infoval->line_count, STDERR_FILENO);
	puts_error(": ");
	puts_error(infoval->argv[0]);
	puts_error(": ");
	puts_error(errstrng);
}

/**
 * print_deci - prints a decimal int number in base 10
 * @inputval: the inputval value
 * @file_dec: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_deci(int inputval, int file_dec)
{
	int (*_put_char)(char) = _putchar;
	int idx;
	int count_val = 0;
	unsigned int _abs_val;
	unsigned int current_val;

	if (file_dec == STDERR_FILENO)
		_put_char = putchar_error;
	if (inputval < 0)
	{
		_abs_val = -inputval;
		_put_char('-');
		count_val++;
	}
	else
		_abs_val = inputval;
	current_val = _abs_val;
	for (idx = 1000000000; idx > 1; idx /= 10)
	{
		if (_abs_val / idx)
		{
			_put_char('0' + current_val / idx);
			count_val++;
		}
		current_val %= idx;
	}
	_put_char('0' + current_val);
	count_val++;

	return (count_val);
}

/**
 * convert_num - number converter, itoa clone
 * @num: the number to convert
 * @base_val: the number base
 * @arg_flags: argument flags
 *
 * Return: string
 */
char *convert_num(long int num, int base_val, int arg_flags)
{
	static char *list_val;
	static char buffered[50];
	char sign_val = 0;
	char *ptr_val;
	unsigned long n = num;

	if (!(arg_flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign_val = '-';

	}
	list_val = arg_flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr_val = &buffered[49];
	*ptr_val = '\0';

	do	{
		*--ptr_val = list_val[n % base_val];
		n /= base_val;
	} while (n != 0);

	if (sign_val)
		*--ptr_val = sign_val;
	return (ptr_val);
}

/**
 * strip_comments - replaces first instance of '#' with '\0'
 * @buffered: address of the string to rectify
 *
 * Return: Always 0;
 */
void strip_comments(char *buffered)
{
	int idx;

	for (idx = 0; buffered[idx] != '\0'; idx++)
		if (buffered[idx] == '#' && (!idx || buffered[idx - 1] == ' '))
		{
			buffered[idx] = '\0';
			break;
		}
}

