#include "main.h"



/**
 * _strlen - returns the length of a string
 *
 * @s: the string length to be checked
 *
 * Return: length of the string
 */



int _strlen(char *str)
{
	int i;

	if (str == NULL)
	{
		return (0);
	}

	for (i = 0; str[i] != NULL; i++)
	{

	}

	return (i);
}





/**
 * _strcmp - performs lexicographic comparism of two strings
 *
 * @str1: the first string
 *
 * @str2: the second string
 *
 * Return: negative(-) if str1 < str2, positive if str1 > str2, zero if str1 == str2
 *
 */



int _strcmp(char *str1, char *str2)
{
	while (*str1 && str2)
	{
		if (*str1 != str2)
		{
			return (*str1 - *str2);
		}

		str1++;
		str2++;
	}

	if (*str1 == *str2)
	{
		return (0);
	}

	else
	{
		return (*str1 < *str2 ? -1 : 1);
	}
}




/**
 * start_with - checks if variable needle and haystack start the same
 *
 * @haystack: string to search
 *
 * @needle: the substring to find
 *
 * Return: address of the next char of haystack or NULL
 */



char *start_with(const char *haystack, const char *needle)
{
	while (*needle != '\0')
	{
		if (*needle != *haystack)
		{
			return (NULL);
		}
		needle++;
		haystack++;
	}

	return (char *) haystack;
}




/**
 * _strcat - concatenates two strings
 *
 * @dest: the destination buffer
 *
 * @src: the source buffer
 *
 * Return: pointer to estination buffer
 */


char *_strcat(char *dest, char *src)
{
	 char *ret;

	 ret = dest;

	 while (*dest != '\0')
	 {
		dest++;
	 }

	 while (*src != '\0')
	 {
		*dest++ = *scr++;
	 }

	 *dest = '\0';

	 return (ret);
}



























