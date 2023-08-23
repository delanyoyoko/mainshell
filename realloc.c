#include "mainshell.h"

/**
 * set_mem - sets a memory with a constant byte
 * @area: the pointer to the memory area
 * @membyte: byte to fill *area with in memory
 * @num: amount of bytes to be filled
 * Return: (area) a pointer to the memory area
 */
char *set_mem(char *area, char membyte, unsigned int num)
{
	unsigned int idx;

	for (idx = 0; idx < num; idx++)
		area[idx] = membyte;
	return (area);
}

/**
 * free_mem -  sets free a string of strings
 * @pps: string of strings
 */
void free_mem(char **pps)
{
	char **ppr = pps;

	if (!pps)
		return;
	while (*pps)
		free(*pps++);
	free(ppr);
}

/**
 * _realloc - reallocates a block of memory
 * @pter: pointer to previous mallocated block
 * @oldsize: byte size of previous block
 * @newsize: byte size of new block
 *
 * Return: a pointer of memory.
 */
void *_realloc(void *pter, unsigned int oldsize, unsigned int newsize)
{
	char *ppr;

	if (!pter)
		return (malloc(newsize));
	if (!newsize)
		return (free(pter), NULL);
	if (newsize == oldsize)
		return (pter);

	ppr = malloc(newsize);
	if (!ppr)
		return (NULL);

	oldsize = oldsize < newsize ? oldsize : newsize;
	while (oldsize--)
		ppr[oldsize] = ((char *)pter)[oldsize];
	free(pter);
	return (ppr);
}
