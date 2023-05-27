#include "shell.h"

/**
 * bfree - Will free ptr
 * @ptr: ptr address
 * Return: 1 otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
