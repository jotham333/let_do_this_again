#include "shell.h"



/**
 * _strcpy - copies the content of one string to another
 *
 * @dest: the destination to copy the file into
 *
 * @src: the source to copy the content from
 *
 * Return: pointer to the destination
 */


char *_strcpy(char *dest, const char *src)
{
	int i;

	if (dest == src || src == NULL || dest == NULL)
		return (NULL);

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}

	dest[i] = '\0';

	return (dest);
}





/**
 * _strdup - it duplicate a string
 *
 * @str: the string to be duplicated
 *
 * Return: pointer to the duplicated string
 */



char *_strdup(const char *str)
{
	int length, i;
	char *ret;

	length = 0;
	if (str == NULL)
	{
		return (NULL);
	}

	while (str[length] != '\0')
	{
		length++;
	}

	ret = malloc(sizeof(char) * (length + 1));
	if (ret == NULL)
	{
		return (NULL);
	}

	for (i = 0; i < length; i++)
	{
		ret[length - 1 - i] = str[length - 1 - i];
	}

	ret[length] = '\0';

	return (ret);
}



/**
 * _putchar - it write the character c to stdout
 *
 * @c: the character to print
 *
 * Return: 1 on success and -1 if error occurred
 */

int _putchar(char c)
{
	static int i;
	static char buff[OUT_BUFF_SIZE];

	if (c == BUFF_FLUSH || i >= OUT_BUFF_SIZE)
	{
		write(1, buff, i);
		i = 0;
	}

	if (c != BUFF_FLUSH)
	{
		buff[i++] = c;
	}

	return (1);
}




/**
 * _puts - prints an input string
 *
 * @str: the string to be printed
 *
 * Return: Nothing
 */

void _puts(char *str)
{
	int i = 0;

	if (str == NULL)
	{
		return;
	}

	for (; str[i] != '\0'; i++)
	{
		_putchar(str[i]);
	}
}
