#include "mainshell.h"

/**
 * **tokenize_string - splits a string into words as tokens.
 * Repeat delimiters are ignored
 * @strng: the input string
 * @delim: the delimeter string
 * Return: pointer to an array of strings, or NULL on failure
 */

char **tokenize_string(char *strng, char *delim)
{
	int idx, jdx, kdx, mdx, numWords = 0;
	char **strngs;

	if (strng == NULL || strng[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (idx = 0; strng[idx] != '\0'; idx++)
		if (!is_delimitor(strng[idx], delim) &&
			(is_delimitor(strng[idx + 1], delim) || !strng[idx + 1]))
			numWords++;

	if (numWords == 0)
		return (NULL);
	strngs = malloc((1 + numWords) * sizeof(char *));
	if (!strngs)
		return (NULL);
	for (idx = 0, jdx = 0; jdx < numWords; jdx++)
	{
		while (is_delimitor(strng[idx], delim))
			idx++;
		kdx = 0;
		while (!is_delimitor(strng[idx + kdx], delim) && strng[idx + kdx])
			kdx++;
		strngs[jdx] = malloc((kdx + 1) * sizeof(char));
		if (!strngs[jdx])
		{
			for (kdx = 0; kdx < jdx; kdx++)
				free(strngs[kdx]);
			free(strngs);
			return (NULL);
		}
		for (mdx = 0; mdx < kdx; mdx++)
			strngs[jdx][mdx] = strng[idx++];
		strngs[jdx][mdx] = 0;
	}
	strngs[jdx] = NULL;
	return (strngs);
}

/**
 * **tokenize_string2 - splits a string into words
 * @strng: the input string
 * @delim: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **tokenize_string2(char *strng, char delim)
{
	int idx, jdx, kdx, mdx, numWords = 0;
	char **strngs;

	if (strng == NULL || strng[0] == 0)
		return (NULL);
	for (idx = 0; strng[idx] != '\0'; idx++)
		if ((strng[idx] != delim && strng[idx + 1] == delim) ||
				    (strng[idx] != delim && !strng[idx + 1]) ||
			strng[idx + 1] == delim)
			numWords++;
	if (numWords == 0)
		return (NULL);
	strngs = malloc((1 + numWords) * sizeof(char *));
	if (!strngs)
		return (NULL);
	for (idx = 0, jdx = 0; jdx < numWords; jdx++)
	{
		while (strng[idx] == delim && strng[idx] != delim)
			idx++;
		kdx = 0;
		while (strng[idx + kdx] != delim && strng[idx + kdx] &&
			strng[idx + kdx] != delim)
			kdx++;
		strngs[jdx] = malloc((kdx + 1) * sizeof(char));
		if (!strngs[jdx])
		{
			for (kdx = 0; kdx < jdx; kdx++)
				free(strngs[kdx]);
			free(strngs);
			return (NULL);
		}
		for (mdx = 0; mdx < kdx; mdx++)
			strngs[jdx][mdx] = strng[idx++];
		strngs[jdx][mdx] = 0;
	}
	strngs[jdx] = NULL;
	return (strngs);
}
