#include "shell.h"


int shellby_cd(char **args, char __attribute__((__unused__)) **front);
int shellby_help(char **args, char __attribute__((__unused__)) **front);

/**
 * shellby_cd - Changes the current directory of the shellby process.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If the given string is not a directory - 2.
 *         If an error occurs - -1.
 *         Otherwise - 0.
 */

int shellby_cd(char **args, char __attribute__((__unused__)) **front)
{

char **dir_info, *new_line = "\n";
char *oldpwd = NULL, *pwd = NULL;
struct stat dir;

oldpwd = getcwd(oldpwd, 0);
if (!oldpwd)
return (-1);

if  (args[0])
{
if (*(args[0]) == '-' || _strcmp(args[0], "--") == 0)
{
if ((args[0][1] == '-' && args[0][2] == '\0') || args[0][1] == '\0')
{

char *oldpwd_env = getenv("OLDPWD");
if (oldpwd_env != NULL)
{
chdir(oldpwd_env + 7);

}

else
{
free(oldpwd);

return (create_error(args, 2));
}
}
else
{
if (stat(args[0], &dir) == 0 && S_ISDIR(dir.st_mode)
&& ((dir.st_mode & S_IXUSR) != 0))
chdir(args[0]);
else
{
free(oldpwd);
return (create_error(args, 2));
}

}
}
else
{

char *home = getenv("HOME");
if (home != NULL)
chdir(home + 5);

}


pwd = getcwd(pwd, 0);
if (!pwd)
return (-1);

dir_info = malloc(sizeof(char *) * 2);
if (!dir_info)
return (-1);

dir_info[0] = "OLDPWD";
dir_info[1] = oldpwd;
if (shellby_setenv(dir_info, dir_info) == -1)

return (-1);

dir_info[0] = "PWD";
dir_info[1] = pwd;

if (shellby_setenv(dir_info, dir_info) == -1)
return (-1);

if (args[0] && args[0][0] == '-' && args[0][1] != '-')
{
write(STDOUT_FILENO, pwd, _strlen(pwd));
write(STDOUT_FILENO, new_line, 1);
}

free(oldpwd);
free(pwd);
free(dir_info);
return (0);
}
