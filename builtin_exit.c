#include "shell.h"
#include <stdlib.h>
/**
 * main - function
 * @argc: element
 * @argv: element
 * Return: exit
 */

int main(int argc, char *argv[])
{
	int status;/*status is int value used to exit shell*/

	if (argc != 2)
	{
		return (1);
	}
	/*to conv char string to int value*/
	status = atoi(argv[1]);
	exit(status);
}
