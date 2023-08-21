#include "mainshell.h"

/**
 * puts_error - prints an error input string
 * @strng: the string to be printed
 *
 * Return: Nothing
 */
void puts_error(char *strng)
{
	int idx = 0;

	if (!strng)
		return;
	while (strng[idx] != '\0')
	{
		putchar_error(strng[idx]);
		idx++;
	}
}

/**
 * putchar_error - writes the character cter to stderr
 * @cter: The character to print as error
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set accordingly.
 */
int putchar_error(char cter)
{
	static int idx;
	static char buffered[WRITE_BUFFER_SIZE];

	if (cter == BUFFER_FLUSH || idx >= WRITE_BUFFER_SIZE)
	{
		write(2, buffered, idx);
		idx = 0;
	}
	if (cter != BUFFER_FLUSH)
		buffered[idx++] = cter;
	return (1);
}

/**
 * put_file_dec - writes the character cter to a given
 * file
 * @cter: The character to write
 * @file_dec: file filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set accordingly.
 */
int put_file_dec(char cter, int file_dec)
{
	static int idx;
	static char buffered[WRITE_BUFFER_SIZE];

	if (cter == BUFFER_FLUSH || idx >= WRITE_BUFFER_SIZE)
	{
		write(file_dec, buffered, idx);
		idx = 0;
	}
	if (cter != BUFFER_FLUSH)
		buffered[idx++] = cter;
	return (1);
}

/**
 * put_files_dec - writes an input string
 * @strng: the string to be written
 * @file_dec: file filedescriptor to write to
 *
 * Return: the number of characters put
 */
int put_files_dec(char *strng, int file_dec)
{
	int idx = 0;

	if (!strng)
		return (0);
	while (*strng)
	{
		idx += put_file_dec(*strng++, file_dec);
	}
	return (idx);
}

