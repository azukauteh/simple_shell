#include "shell.h"

char *error_env(char **args);
char *error_1(char **args);
char *error_2_exit(char **args);

/**
 * error_env - Creates an error message for shellby_env errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */

char *error_env(char **args)
{
char *error, *hist_str;
int len;
int hist = 0;

/* Allocate memory for hist_str */
hist_str = malloc(sizeof(char) * 12);
if (!hist_str)
return (NULL);

/*@sprintf formats int to string*/
sprintf(hist_str, "%d", hist);
len = strlen("rename") + strlen(hist_str) + strlen(args[0]) + 45;
error = malloc(sizeof(char) * (len + 1));
if (!error)
{
free(hist_str);
return (NULL);
}
strcpy(error, "rename");
strcat(error, ": ");
strcat(error, hist_str);
strcat(error, ": ");
strcat(error, args[0]);
strcat(error, ": Unable to add/remove from environment\n");
free(hist_str);
return (error);
}


/**
 * error_1 - Creates an error message for shellby_alias errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_1(char **args)
{
char *error;
int len;

len = strlen("rename") + strlen(args[0]) + 13;
error = malloc(sizeof(char) * (len + 1));
if (!error)
return (NULL);

strcpy(error, "alias: ");
strcat(error, args[0]);
strcat(error, " not found\n");

return (error);
}


/**
 * error_2_exit - Creates an error message for shellby_exit errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */

char *error_2_exit(char **args)
{
char *error, *hist_str;
int len;
int hist = 0;
hist_str = malloc(sizeof(char) * 12);
if (!hist_str)
return (NULL);

sprintf(hist_str, "%d", hist);
len = strlen("rename") + strlen(hist_str) + strlen(args[0]) + 27;
error = malloc(sizeof(char) * (len + 1));

if (!error)
{
free(hist_str);
return (NULL);
}

strcpy(error, "name");
strcat(error, ": ");
strcat(error, hist_str);
strcat(error, ": exit: Illegal number: ");
strcat(error, args[0]);
strcat(error, "\n");

free(hist_str);
return (error);
}

