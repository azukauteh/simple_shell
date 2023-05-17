#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/**
 * main - funtion
 * Return: 0
 */
int main(void)
{
	char *path = "/home/user/new_directory";

	if (chdir(path) != 0)
	{
		perror("chdir() error");
	}
	char cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd() error");
		exit(EXIT_FAILURE);
	}
	setenv("PWD", cwd, 1);
	return (0);
}
