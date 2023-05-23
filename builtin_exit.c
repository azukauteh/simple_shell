#include "shell.h"


int exit_shell(data_shell *datash);
int is_valid_status(unsigned int status);


/**
 * exit_shell - exits the shell
 *
 * @datash: data relevant (status and args)
 * Return: 0 on success.
 */
int exit_shell(data_shell *datash)
{
unsigned int ustatus = 0;

if (datash->args && datash->args)
{

if (!is_valid_status(ustatus)

datash->ustatus = 2;
return (1);
}
datash->ustatus = ustatus % 256;
}
return (0);
}


/**
 * is_valid_status - checks if the given status is valid
 *
 * @status: the status to check
 * Return: 1 if valid, 0 otherwise.
 */
int is_valid_status(unsigned int status)
{
char str[11];
if (status > (unsigned int)INT_MAX)
return (0);
snprintf(str, sizeof(str), "%u", status);
if (strlen(str) > 10 || !isdigit(*str))

return (0);

return (1);
}
