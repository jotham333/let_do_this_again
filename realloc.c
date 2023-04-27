#include "shell.h"



/**
 * _memset - functions fill memory with a constant byte b
 *
 * @str: the pointer to the memory
 *
 * @b: the byte to be filled into *str
 *
 * @n: quantity of bytes to be filled
 *
 * Return: a pointer to str memory
 */


char *_memset(char *str, char b, unsigned int n)
{
	unsigned int i;

	i = 0;

	while(i < n)
	{
		str[i] = b;
		i++;
	}

	return (str);
}




/**
 * free_str - frees a string from strings
 *
 * @s: string from te strings
 */

void free_str(char **s)
{
	char **m;
	int i;

	i = 0;
	m = s;

	if (s == NULL)
	{
		return;
	}

	while((*s)[i] != NULL)
	{
		free((*s)[i]);
		i++;
	}
	free (m);

}




/**
 * _realoc - reallocates a blcok of memory
 *
 * @ptr: pointer to previuse malloc block
 *
 * @old_size: byte size of previous block
 *
 * @new_size: byte size of new_block
 *
 * Return: pointer to p
 */




void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;
	unsigned int size;

	if (ptr == NULL)
	{
		return (malloc(new_size));
	}

	if (new_size == 0)
	{
		return (free(ptr), NULL);
	}

	if (new_size == old_size)
	{
		return (ptr);
	}

	p = malloc(new_size);
	if (p == NULL)
	{
		return (NULL);
	}

	size = old_size < new_size ? old_size : new_size;

	while (size--)
	{
		p[size] = ((char *) ptr)[size];
	}
	free(ptr);

	return (p);
}
