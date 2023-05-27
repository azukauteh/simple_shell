#include "shell.h"

/**
 * history_file - function that will get file history
 * @info: parameter
 * Return: string history file
 */

char *history_file(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - function that add/create file
 * @info: parameter
 * Return: 1 if successful otherwise -1
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - function that will read history from a file
 * @info: structure
 * Return: histcnt if successful otherwise
 */
int read_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			list_history(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		list_history(info, buf + last, linecount++);
	free(buf);
	info->histcnt = linecount;
	while (info->histcnt-- >= HIST_MAX)
		d_ind(&(info->history), 0);
	renum_history(info);
	return (info->histcnt);
}

/**
 * list_history - function that will add entry list
 * @info: structure
 * @buf: buffer
 * @linecount: linecount
 * Return: 0
 */
int list_history(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	end_anode(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renum_history - Will re-number
 * @info: struct
 * Return: histcnt
 */
int renum_history(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcnt = i);
}
