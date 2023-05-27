#include "shell.h"

/**
 * isfree - Will free ptr
 * @ptr: ptr address
 * Return: 1 otherwise 0.
 */
int isfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
