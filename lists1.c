#include "mainshell.h"

/**
 * get_listlen - gets the length of linked list
 * @headval: pointer address to first node
 *
 * Return: size of list
 */
size_t get_listlen(const list_type *headval)
{
	size_t idx = 0;

	while (headval)
	{
		headval = headval->next;
		idx++;
	}
	return (idx);
}

/**
 * list_stringify - determines an array of strings of the list->str
 * @headval: pointer to first node
 *
 * Return: array of strings
 */
char **list_stringify(list_type *headval)
{
	list_type *nodeval = headval;
	size_t idx = get_listlen(headval);
	size_t jdx;
	char **strngs;
	char *strng;

	if (!headval || !idx)
		return (NULL);
	strngs = malloc(sizeof(char *) * (idx + 1));
	if (!strngs)
		return (NULL);
	for (idx = 0; nodeval; nodeval = nodeval->next, idx++)
	{
		strng = malloc(string_len(nodeval->str) + 1);
		if (!strng)
		{
			for (jdx = 0; jdx < idx; jdx++)
				free(strngs[jdx]);
			free(strngs);
			return (NULL);
		}

		strng = string_copy(strng, nodeval->str);
		strngs[idx] = strng;
	}
	strngs[idx] = NULL;
	return (strngs);
}


/**
 * print_node_list - prints all members of a list_type
 * @headval: pointer to first node
 *
 * Return: size of list
 */
size_t print_node_list(const list_type *headval)
{
	size_t idx = 0;

	while (headval)
	{
		_puts(convert_num(headval->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(headval->str ? headval->str : "(nil)");
		_puts("\n");
		headval = headval->next;
		idx++;
	}
	return (idx);
}

/**
 * node_startsWith - gets a node whose string starts with prefix
 * @nodeval: pointer to list head
 * @prefix: string to match
 * @cter: the next character after prefix to match
 *
 * Return: match node or null
 */
list_type *node_startsWith(list_type *nodeval,
char *prefix, char cter)
{
	char *ppr = NULL;

	while (nodeval)
	{
		ppr = starts_with(nodeval->str, prefix);
		if (ppr && ((cter == -1) || (*ppr == cter)))
			return (nodeval);
		nodeval = nodeval->next;
	}
	return (NULL);
}

/**
 * get_nodeIndex - determines the index of a node
 * @headval: pointer to list head
 * @nodeval: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_nodeIndex(list_type *headval, list_type *nodeval)
{
	size_t idx = 0;

	while (headval)
	{
		if (headval == nodeval)
			return (idx);
		headval = headval->next;
		idx++;
	}
	return (-1);
}
