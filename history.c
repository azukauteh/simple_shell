#include "shell.h"
char *get_location(char *command);
char *fill_path_dir(char *path);
list_t *get_path_dir(char *path);
list_t *get_path_dir(char *path);

/**
 * fill_path_dir - Copies path but also replaces leading/sandwiched/trailing
 *		   colons (:) with current working directory.
 * @path: The colon-separated list of directories.
 *
 * Return: A copy of path with any leading/sandwiched/trailing colons replaced
 *	   with the current working directory.
 */

char *fill_path_dir(char *path)
{
int i, length = 0;
char *path_copy, *pwd;

pwd = (char *)(getenv("PWD") + 4);

for (i = 0; path[i]; i++)
{
if (path[i] == ':')
{
if (path[i + 1] == ':' || path[i + 1] == 0 || path[i + 1] == '\0')
length += _strlen(pwd) + 1;

else
length++;
}

else
length++;
}
path_copy = malloc(sizeof(char) * (length + 1));
if (!path_copy)
return (NULL);
path_copy[0] = '\0';
for (i = 0; path[i]; i++)
{
if (path[i] == ':')
{
if (i == 0)
{	strcat(path_copy, pwd);
	strcat(path_copy, ":");
}
else if (path[i + 1] == ':'
|| path[i + 1] == '\0')
{	strcat(path_copy, ":");
	strcat(path_copy, pwd);
}
else
strcat(path_copy, ":");
}
else
{	strncat(path_copy, &path[i], 1);
}
}
return (path_copy);
}

/**
 * get_path_dir - Tokenizes a colon-separated list of
 *                directories into a list_s linked list.
 * @path: The colon-separated list of directories.
 *
 * Return: A pointer to the initialized linked list.
 */

list_t *get_path_dir(char *path)
{
int index;
char **dirs;
list_t *head = NULL;
char *path_copy = NULL;
if (!path)
return (NULL);
path_copy = strdup(path);
if (!path_copy)
return (NULL);
dirs = malloc(sizeof(char *));
if (!dirs)
{
free(path_copy);
return (NULL);
}
dirs[0] = strtok(path_copy, ":");
index = 1;
while (dirs[index - 1])
{
char *dir = strtok(NULL, ":");
dirs = realloc(dirs, sizeof(char *) * (index + 1));
if (!dirs)
{	free(path_copy);
	return (NULL);
}
dirs[index] = dir;
index++;
}
for (index = 0; dirs[index]; index++)
{
if (add_node_end(&head, dirs[index]) == NULL)
{	free(dirs);
	free(path_copy);
	return (NULL);
}
}
free(dirs);
free(path_copy);
return (head);
}
