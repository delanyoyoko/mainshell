#include "mainshell.h"

/**
 * append_node - appends a node to a list
 * @headval: address value of pointer to head node
 * @strng: the string prop of node
 * @idx: the index of the node used by history
 *
 * Return: size of list
 */
list_type *append_node(list_type **headval,
const char *strng, int idx)
{
	list_type *new_headval;

	if (!headval)
		return (NULL);
	new_headval = malloc(sizeof(list_type));
	if (!new_headval)
		return (NULL);
	set_mem((void *)new_headval, 0, sizeof(list_type));
	new_headval->num = idx;
	if (strng)
	{
		new_headval->str = dup_string(strng);
		if (!new_headval->str)
		{
			free(new_headval);
			return (NULL);
		}
	}
	new_headval->next = *headval;
	*headval = new_headval;
	return (new_headval);
}

/**
 * prepend_node - prepends a node to a list
 * @headval: address value of pointer to head node
 * @strng: string proprerty of node
 * @idx: the node index used by history
 *
 * Return: size of list
 */
list_type *prepend_node(list_type **headval,
const char *strng, int idx)
{
	list_type *new_nodeval;
	list_type *nodeval;

	if (!headval)
		return (NULL);

	nodeval = *headval;
	new_nodeval = malloc(sizeof(list_type));
	if (!new_nodeval)
		return (NULL);
	set_mem((void *)new_nodeval, 0, sizeof(list_type));
	new_nodeval->num = idx;
	if (strng)
	{
		new_nodeval->str = dup_string(strng);
		if (!new_nodeval->str)
		{
			free(new_nodeval);
			return (NULL);
		}
	}
	if (nodeval)
	{
		while (nodeval->next)
			nodeval = nodeval->next;
		nodeval->next = new_nodeval;
	}
	else
		*headval = new_nodeval;
	return (new_nodeval);
}

/**
 * print_list_string - prints only the string field of a
 * list_type linked list
 * @headval: pointer to first node value
 *
 * Return: the size of linked list
 */
size_t print_list_string(const list_type *headval)
{
	size_t idx = 0;

	while (headval)
	{
		_puts(headval->str ? headval->str : "(nil)");
		_puts("\n");
		headval = headval->next;
		idx++;
	}
	return (idx);
}

/**
 * del_node_at_index - filter out a node at a given index
 * @headval: address value of pointer to first node
 * @index: index of node to filter out
 *
 * Return: 1 on success, 0 on failure
 */
int del_node_at_index(list_type **headval,
unsigned int index)
{
	list_type *nodeval;
	list_type *prev_nodeval;
	unsigned int idx = 0;

	if (!headval || !*headval)
		return (0);

	if (!index)
	{
		nodeval = *headval;
		*headval = (*headval)->next;
		free(nodeval->str);
		free(nodeval);
		return (1);
	}
	nodeval = *headval;
	while (nodeval)
	{
		if (idx == index)
		{
			prev_nodeval->next = nodeval->next;
			free(nodeval->str);
			free(nodeval);
			return (1);
		}
		idx++;
		prev_nodeval = nodeval;
		nodeval = nodeval->next;
	}
	return (0);
}

/**
 * free_mem_list - releases free all nodes of a list
 * @head_ptrval: the head node address pointer
 *
 * Return: void
 */
void free_mem_list(list_type **head_ptrval)
{
	list_type *nodeval;
	list_type *next_nodeval;
	list_type *headval;

	if (!head_ptrval || !*head_ptrval)
		return;
	headval = *head_ptrval;
	nodeval = headval;
	while (nodeval)
	{
		next_nodeval = nodeval->next;
		free(nodeval->str);
		free(nodeval);
		nodeval = next_nodeval;
	}
	*head_ptrval = NULL;
}
