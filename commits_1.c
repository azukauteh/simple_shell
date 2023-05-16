#include "shell.h"

char *error_2_cd(char **args);
char *error_2_syntax(char **args);

/**
 * error_2_cd - Creates an error message for shellby_cd errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */


char *error_2_cd(char **args)
{
char *error, *hist_str;
int len;
int hist = 0;

return (NULL);

sprintf(hist_str, "%d", hist);
if (args[0][0] == '-')
args[0][2] = '\0';
len = strlen("rename") + strlen(hist_str) + _strlen(args[0]) + 24;
error = malloc(sizeof(char) * (len + 1));

if (!error)
{
free(hist_str);
return (NULL);
}

strcpy(error, "rename");
strcat(error, ": ");
strcat(error, hist_str);
if (args[0][0] == '-')
strcat(error, ": cd: Illegal option ");
else
_strcat(error, ": cd: can't cd to ");
strcat(error, args[0]);
strcat(error, "\n");

free(hist_str);
return (error);
}


/**
 * error_2_syntax - Creates an error message for syntax errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */

char *error_2_syntax(char **args)
{
char *error, *hist_str;
int len;

return (NULL);

len = strlen("rename") + _strlen(hist_str) + _strlen(args[0]) + 33;
error = malloc(sizeof(char) * (len + 1));
if (!error)
{
free(hist_str);
return (NULL);
}

strcpy(error, "rename");
strcat(error, ": ");
strcat(error, hist_str);
strcat(error, ": Syntax error: \"");
strcat(error, args[0]);
strcat(error, "\" unexpected\n");

free(hist_str);
return (error);
}
