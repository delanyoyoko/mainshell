#include "mainshell.h"

/**
 * string_copy - copies a string to memory
 * @destbuff: the destination buffer
 * @srcbuff: the source buffer
 *
 * Return: pointer to destination
 */
char *string_copy(char *destbuff, char *srcbuff)
{
	int idx = 0;

	if (destbuff == srcbuff || srcbuff == 0)
		return (destbuff);
	while (srcbuff[idx])
	{
		destbuff[idx] = srcbuff[idx];
		idx++;
	}
	destbuff[idx] = 0;
	return (destbuff);
}

/**
 * dup_string - duplicates a string into memory
 * @strng: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *dup_string(const char *strng)
{
	int lenval = 0;
	char *retval;

	if (strng == NULL)
		return (NULL);
	while (*strng++)
		lenval++;
	retval = malloc(sizeof(char) * (lenval + 1));
	if (!retval)
		return (NULL);
	for (lenval++; lenval--;)
		retval[lenval] = *--strng;
	return (retval);
}

/**
 * _puts - prints an input string
 * @strng: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *strng)
{
	int idx = 0;

	if (!strng)
		return;
	while (strng[idx] != '\0')
	{
		_putchar(strng[idx]);
		idx++;
	}
}

/**
 * _putchar - writes the character cter to stdout
 * @cter: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set accordingly.
 */
int _putchar(char cter)
{
	static int idx;
	static char buffered[WRITE_BUFFER_SIZE];

	if (cter == BUFFER_FLUSH || idx >= WRITE_BUFFER_SIZE)
	{
		write(1, buffered, idx);
		idx = 0;
	}
	if (cter != BUFFER_FLUSH)
		buffered[idx++] = cter;
	return (1);
}
