#include "mainshell.h"

/**
 **copy_string - copies a string to memory
 *@des: the destination string to be copied to
 *@source: the source string to copy
 *@num: the number of characters to be copied
 *Return: the concatenated string
 */
char *copy_string(char *des, char *source, int num)
{
	int idx;
	int jdx;
	char *strng = des;

	idx = 0;
	while (source[idx] != '\0' && idx < num - 1)
	{
		des[idx] = source[idx];
		idx++;
	}
	if (idx < num)
	{
		jdx = idx;
		while (jdx < num)
		{
			des[jdx] = '\0';
			jdx++;
		}
	}
	return (strng);
}

/**
 **cat_string - to concatenates two strings
 *@_first: the first string
 *@_second: the second string
 *@num: the amount of bytes to be max used
 *Return: the combined concatenated string
 */
char *cat_string(char *_first, char *_second, int num)
{
	int idx;
	int jdx;
	char *strng = _first;

	idx = 0;
	jdx = 0;
	while (_first[idx] != '\0')
		idx++;
	while (_second[jdx] != '\0' && jdx < num)
	{
		_first[idx] = _second[jdx];
		idx++;
		jdx++;
	}
	if (jdx < num)
		_first[idx] = '\0';
	return (strng);
}

/**
 **char_string - to locates a character in a string
 *@strng: the string to be parsed
 *@cter: the character to look for
 *Return: (strng) a pointer to the memory area of strng
 */
char *char_string(char *strng, char cter)
{
	do {
		if (*strng == cter)
			return (strng);
	} while (*strng++ != '\0');

	return (NULL);
}

