#include "mainshell.h"

/**
 * input_buffered - buffer inputs chained commands
 * @infoval: the parameter struct
 * @buffered: the buffer address
 * @len: address length of var
 *
 * Return: bytes reads
 */
ssize_t input_buffered(info_type *infoval, char **buffered, size_t *len)
{
	ssize_t bytreads = 0;
	size_t len_pp = 0;

	if (!*len)
	{
		/*bfree((void **)infoval->cmd_buf);*/
		free(*buffered);
		*buffered = NULL;
		signal(SIGINT, handleSigint);
#if USE_GETLINE
		bytreads = getline(buffered, &len_pp, stdin);
#else
		bytreads = get_line(infoval, buffered, &len_pp);
#endif
		if (bytreads > 0)
		{
			if ((*buffered)[bytreads - 1] == '\n')
			{
				(*buffered)[bytreads - 1] = '\0';
				bytreads--;
			}
			infoval->linecount_flag = 1;
			remove_comments(*buffered);
			build_history_list(infoval, *buffered, infoval->histcount++);
			
			{
				*len = bytreads;
				infoval->cmd_buf = buffered;
			}
		}
	}
	return (bytreads);
}

/**
 * accept_input - gets a line without the newline
 * @infoval: parameter struct
 *
 * Return: bytes reads
 */
ssize_t accept_input(info_type *infoval)
{
	static char *buffered;
	static size_t idx;
	static size_t jdx;
	static size_t lenval;
	ssize_t bytreads = 0;
	char **buffered_p = &(infoval->arg), *ppr;

	_putchar(BUFFER_FLUSH);
	bytreads = input_buffered(infoval, &buffered, &lenval);
	if (bytreads == -1) /* End of file */
		return (-1);
	if (lenval) /* commands remain in the chain buffer */
	{
		jdx = idx;
		ppr = buffered + idx;

		check_chain(infoval, buffered, &jdx, idx, lenval);
		while (jdx < lenval)
		{
			if (isChain(infoval, buffered, &jdx))
				break;
			jdx++;
		}

		idx = jdx + 1;
		if (idx >= lenval)
		{
			idx = lenval = 0;
			infoval->cmd_buf_type = CMD_NORM;
		}

		*buffered_p = ppr;
		return (string_len(ppr));
	}

	*buffered_p = buffered;
	return (bytreads);
}

/**
 * read_buffered - reads a buffer to memory
 * @infoval: the parameter struct
 * @buffered: buffer
 * @sz: size
 *
 * Return: r - bytes reads
 */
ssize_t read_buffered(info_type *infoval, char *buffered, size_t *sz)
{
	ssize_t bytreads = 0;

	if (*sz)
		return (0);
	bytreads = read(infoval->readfd, buffered, READ_BUFFER_SIZE);
	if (bytreads >= 0)
		*sz = bytreads;
	return (bytreads);
}

/**
 * get_line - gets the next new line of input from STDIN
 * @infoval: the parameter struct
 * @ptra: address of pointer to buffer, preallocated or NULL
 * @_len: size of preallocated ptra buffer if not NULL
 *
 * Return: strng
 */
int get_line(info_type *infoval, char **ptra, size_t *_len)
{
	static char buffered[READ_BUFFER_SIZE];
	static size_t idx;
	static size_t lenval;
	size_t kdx;
	ssize_t bytreads = 0;
	ssize_t strng = 0;
	char *ppr = NULL;
	char *new_ppr = NULL;
	char *cter;

	ppr = *ptra;
	if (ppr && _len)
		strng = *_len;
	if (idx == lenval)
		idx = lenval = 0;

	bytreads = read_buffered(infoval, buffered, &lenval);
	if (bytreads == -1 || (bytreads == 0 && lenval == 0))
		return (-1);

	cter = char_string(buffered + idx, '\n');
	kdx = cter ? 1 + (unsigned int)(cter - buffered) : lenval;
	new_ppr = _realloc(ppr, strng, strng ? strng + kdx : kdx + 1);
	if (!new_ppr)
		return (ppr ? free(ppr), -1 : -1);

	if (strng)
		cat_string(new_ppr, buffered + idx, kdx - idx);
	else
		copy_string(new_ppr, buffered + idx, kdx - idx + 1);

	strng += kdx - idx;
	idx = kdx;
	ppr = new_ppr;

	if (_len)
		*_len = strng;
	*ptra = ppr;
	return (strng);
}

/**
 * handleSigint - blocks ctrl-C - coppying
 * @sig_number: the signal number for action
 *
 * Return: void
 */
void handleSigint(__attribute__((unused))int sig_number)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFFER_FLUSH);
}

