#include "shell.h"

int handle_args(int *exe_ret);
int check_args(char **args);


/**
 * handle_args - Gets, calls, and runs the execution of a command.
 * @exe_ret: The return value of the parent process' last executed command.
 *
 * Return: If an end-of-file is read - END_OF_FILE (-2).
 *         If the input cannot be tokenized - -1.
 *         Otherwise - The exit value of the last executed command.
 */

int handle_args(int *exe_ret)
{
int ret = 0, index;
char **args = NULL, *line = NULL, **front;

line = get_args(line, exe_ret);
if (!line)
return (END_OF_FILE);

free(line);
if (!args)
return (ret);

if (check_args(args) != 0)
{
*exe_ret = 2;
free_args(args, args);

return (*exe_ret);
}
front = args;

for (index = 0; args[index]; index++)
{
if (_strncmp(args[index], ";", 1) == 0)
{
free(args[index]);
args[index] = NULL;
ret = call_args(args, front, exe_ret);
args = &args[++index];
index = 0;
}
}
if (args)
ret = call_args(args, front, exe_ret);

free(front);

return (ret);
}

/**
 * check_args - Checks if there are any leading ';', ';;', '&&', or '||'.
 * @args: 2D pointer to tokenized commands and arguments.
 *
 * Return: If a ';', '&&', or '||' is placed at an invalid position - 2.
 *	   Otherwise - 0.
 */
int check_args(char **args)
{
size_t i;
char *cur, *nex;

for (i = 0; args[i]; i++)
{
cur = args[i];
if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
{
if (i == 0 || cur[1] == ';')
return (create_error(&args[i], 2));
nex = args[i + 1];
if (nex && (nex[0] == ';' || nex[0] == '&' || nex[0] == '|'))
return (create_error(&args[i + 1], 2));
}
}
return (0);
}
