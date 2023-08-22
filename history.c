#include "mainshell.h"

/**
 * load_history_file - loads the history file
 * @infoval: struct involving arguments. Used to maintain
 * constant function prototype.
 *
 * Return: a string containg history file
 */

char *load_history_file(info_type *infoval)
{
	char *buffered;
	char *dirr;

	dirr = get_env(infoval, "HOME=");
	if (!dirr)
		return (NULL);
	buffered = malloc(sizeof(char) * (string_len(dirr) +
		string_len(HISTORY_FILE) + 2));
	if (!buffered)
		return (NULL);
	buffered[0] = 0;
	string_copy(buffered, dirr);
	string_cat(buffered, "/");
	string_cat(buffered, HISTORY_FILE);
	return (buffered);
}

/**
 * compose_history - creates a history file, or appends 
 * to an existing file
 * @infoval: struct involving arguments. Used to maintain
 * constant function prototype.
 *
 * Return: 1 on success, otherwise -1
 */
int compose_history(info_type *infoval)
{
	ssize_t file_dec;
	char *filename = load_history_file(infoval);
	list_type *nodeval = NULL;

	if (!filename)
		return (-1);

	file_dec = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (file_dec == -1)
		return (-1);
	for (nodeval = infoval->history; nodeval;
		nodeval = nodeval->next)
	{
		put_files_dec(nodeval->str, file_dec);
		put_file_dec('\n', file_dec);
	}
	put_file_dec(BUFFER_FLUSH, file_dec);
	close(file_dec);
	return (1);
}

/**
 * reader_history - reads history from a file
 * @infoval: struct involving arguments. Used to maintain
 * constant function prototype.
 *
 * Return: history count on success, else 0
 */
int reader_history(info_type *infoval)
{
	int idx, last_count = 0, line_count = 0;
	ssize_t file_dec, read_len, file_size = 0;
	struct stat _stat;
	char *buffered = NULL, *filename = load_history_file(infoval);

	if (!filename)
		return (0);

	file_dec = open(filename, O_RDONLY);
	free(filename);
	if (file_dec == -1)
		return (0);
	if (!fstat(file_dec, &_stat))
		file_size = _stat.st_size;
	if (file_size < 2)
		return (0);
	buffered = malloc(sizeof(char) * (file_size + 1));
	if (!buffered)
		return (0);
	read_len = read(file_dec, buffered, file_size);
	buffered[file_size] = 0;
	if (read_len <= 0)
		return (free(buffered), 0);
	close(file_dec);
	for (idx = 0; idx < file_size; idx++)
		if (buffered[idx] == '\n')
		{
			buffered[idx] = 0;
			compose_history_list(infoval, buffered +
				last_count, line_count++);
			last_count = idx + 1;
		}
	if (last_count != idx)
		compose_history_list(infoval, buffered +
			last_count, line_count++);
	free(buffered);
	infoval->histcount = line_count;
	while (infoval->histcount-- >= HISTORY_MAX)
		del_node_at_index(&(infoval->history), 0);
	nominate_history(infoval);
	return (infoval->histcount);
}

/**
 * compose_history_list - adds an entry to a history 
 * linked list
 * @infoval: struct involving arguments. Used to maintain
 * constant function prototype.
 * @buffered: a buffer
 * @line_count: the history line_count, histcount
 *
 * Return: Always 0
 */
int compose_history_list(info_type *infoval,
char *buffered, int line_count)
{
	list_type *nodeval = NULL;

	if (infoval->history)
		nodeval = infoval->history;
	prepend_node(&nodeval, buffered, line_count);

	if (!infoval->history)
		infoval->history = nodeval;
	return (0);
}

/**
 * nominate_history - re-numbers the history linked list after
 * some changes
 * @infoval: struct involving arguments. Used to maintain
 * constant function prototype.
 *
 * Return: the new history count
 */
int nominate_history(info_type *infoval)
{
	list_type *nodeval = infoval->history;
	int idx = 0;

	while (nodeval)
	{
		nodeval->num = idx++;
		nodeval = nodeval->next;
	}
	return (infoval->histcount = idx);
}

