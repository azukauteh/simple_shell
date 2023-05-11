#include "shell.h"

int execute(char **args, char **front);
void sig_handler(int sig);

/**
 * sig_handler - Prints a new prompt (simple_shell) upon a signal.
 * @sig: The signal.
 */
void sig_handler(int sig)
{
char *simple_shell = "\n$ ";
(void)sig;

/* handle the “end of file” condition (Ctrl+D)*/
signal(SIGINT, sig_handler);
write(STDIN_FILENO, simple_shell, 3);
}



/**
 * execute - Executes a command in a child process.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - a corresponding error code.
 *         O/w - The exit value of the last executed command.
 */


int execute(char **args, char **front)
{
pid_t child_pid;
int status, flag = 0, ret = 0;
char *command = args[0];

if (command[0] != '/' && command[0] != '.')
{
flag = 1;
command = get_location(command);
}

if (!command || (access(command, F_OK) == -1))
{
if (errno == EACCES)
ret = (create_error(args, 126));
else
ret = (create_error(args, 127));
}
else
{
child_pid = fork();
if (child_pid == -1)
{
if (flag)
free(command);
perror("Error child:");
return (1);
}
if (child_pid == 0)
{
int execute(char **args, char **front);
if (errno == EACCES)
ret = (create_error(args, 126));
free_env();
free_args(args, front);
free_alias_list();
_exit(ret);
}
else
{
wait(&status);
ret = WEXITSTATUS(status);
}
}
if (flag)
free(command);
return (ret);
}

/**
 * main - Runs a simple UNIX command interpreter.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: The return value of the last executed command.
 */

int main(int argc, char *argv[])
{
int ret = 0, retn;
int *exe_ret = &retn;
char *simple_shell = "$ ";
char *new_line = "\n";

char *rename;
int hist;
char **environ;
char **aliases;

rename = argv[0];
hist = 1;
aliases = NULL;
signal(SIGINT, sig_handler);
*exe_ret = 0;
environ = NULL;

if (!environ)
exit(-100);

if (argc != 1)
{
ret = proc_file_commands(argv[1], exe_ret);
free_env();
free_alias_list(aliases);
return (*exe_ret);
}

if (!isatty(STDIN_FILENO))
{
while (ret != END_OF_FILE && ret != EXIT)
ret = handle_args(exe_ret);
free_env();
free_alias_list(aliases);
return (*exe_ret);
}
printf("hist: %d\n", hist);
puts(rename);
puts(new_line);
puts(simple_shell);
return (0);
}
