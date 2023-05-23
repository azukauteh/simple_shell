#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 80 /* The maximum length command */
/**
 * main - handle logic operators
 * Return: 0
 */
int main(void)
{
	char *args[MAX_LINE / 2 + 1]; /* command line arguments */
	int should_run = 1; /* flag to determine when to exit program */
	char input[MAX_LINE];
	int a, status;
	pid_t pid;

	while (should_run)
	{	printf("osh>");
		fflush(stdout);
		fgets(input, MAX_LINE, stdin);
		input[strlen(input) - 1] = '\0';
		a = 0;
		args[a] = strtok(input, " ");
	while (args[a] != NULL)
	{	a++;
		args[a] = strtok(NULL, " ");
	} args[a] = NULL;
	if (strcmp(args[0], "exit") == 0)
	{	should_run = 0;
		break;
	} pid = fork();
	if (pid < 0)
	{	printf("Fork failed.\n");
		exit(1);
	} else if (pid == 0)
	{	if (strcmp(args[a - 1], "&") == 0)/* Child process */
		{	args[a - 1] = NULL;
		}
	 execvp(args[0], args);
	 printf("Command not found.\n");
	 exit(1);
	}
	else
	{	if (strcmp(args[a - 1], "&") != 0)/* Parent process */
		{	waitpid(pid, &status, 0);
		}
	}
}
return (0);
}
