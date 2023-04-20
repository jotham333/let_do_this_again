#include "shell.h"





/**
 * _free - it frees a pointer and set the address to NULL
 *
 * @ptr: the address to be freed
 *
 * Return: 1 if successfully freed and 0 otherwise
 */



int _free(void **ptr)
{
	if (ptr != NULL && *ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
