#include "mainshell.h"

/**
 * is_cmd - ensures whether if a file is an executable command
 * @infoval: info structure
 * @pathstr: the path string to the file
 *
 * Return: 1 if true, else 0
 */
int is_cmd(info_type *infoval, char *pathstr)
{
	struct stat __stat;

	(void)infoval;
	if (!pathstr || stat(pathstr, &__stat))
		return (0);

	if (__stat.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicate_chars - makes a duplicate of characters
 * @path: the PATH string
 * @startIdx: starting index
 * @stopIdx: stopping index
 *
 * Return: pointer to new buffer
 */
char *duplicate_chars(char *path, int startIdx, int stopIdx)
{
	static char buffered[1024];
	int idx = 0, kdx = 0;

	for (kdx = 0, idx = startIdx; idx < stopIdx; idx++)
		if (path[idx] != ':')
			buffered[kdx++] = path[idx];
	buffered[kdx] = 0;
	return (buffered);
}

/**
 * find_path - finds an executable command in the PATH string
 * @infoval: the info structure
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_type *infoval, char *pathstr, char *cmd)
{
	int idx = 0;
	int current_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((string_len(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(infoval, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[idx] || pathstr[idx] == ':')
		{
			path = duplicate_chars(pathstr, current_pos, idx);
			if (!*path)
				string_cat(path, cmd);
			else
			{
				string_cat(path, "/");
				string_cat(path, cmd);
			}
			if (is_cmd(infoval, path))
				return (path);
			if (!pathstr[idx])
				break;
			current_pos = idx;
		}
		idx++;
	}
	return (NULL);
}
