#include "mainshell.h"

/**
 * free_buffer - frees a buffer pointer and NULL the address
 * @pptr: address of the pointer to free
 *
 * Return: 1 if freed, else 0.
 */
int free_buffer(void **pptr)
{
	if (pptr && *pptr)
	{
		free(*pptr);
		*pptr = NULL;
		return (1);
	}
	return (0);
}
