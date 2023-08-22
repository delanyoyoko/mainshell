#include "mainshell.h"

/**
 * string_len - determines the length of a string
 * @strng: the string to check its length
 *
 * Return: int - length of string
 */
int string_len(char *strng)
{
	int idx = 0;

	if (!strng)
		return (0);

	while (*strng++)
		idx++;
	return (idx);
}

/**
 * string_cmp - compares two strangs.
 * @strng1: first string
 * @strng2: second string
 *
 * Return: negative if strng1 < strng2,
 * positive if strng1 > strng2, zero if strng1 == strng2
 */
int string_cmp(char *strng1, char *strng2)
{
	while (*strng1 && *strng2)
	{
		if (*strng1 != *strng2)
			return (*strng1 - *strng2);
		strng1++;
		strng2++;
	}
	if (*strng1 == *strng2)
		return (0);
	else
		return (*strng1 < *strng2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * string_cat - merges two strings
 * @destbuf: the destination buffer
 * @srcbuf: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *string_cat(char *destbuf, char *srcbuf)
{
	char *retbuf = destbuf;

	while (*destbuf)
		destbuf++;
	while (*srcbuf)
		*destbuf++ = *srcbuf++;
	*destbuf = *srcbuf;
	return (retbuf);
}
