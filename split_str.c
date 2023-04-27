#include "shell.h"



/**
 * split_string - splits a string into words. Repeated delimers are ignored
 *
 * @str: the input string
 *
 * @delim: the delimter
 *
 * Return: a pointer to an array of strings, or NULL if function failed
 */


char **split_string(char *str, char *delim)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);

	if (delim == NULL)
		delim = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], delim) && (is_delim(str[i + 1], delim) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (s == NULL)
		return ( NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(str[i], delim))
			i++;
		k = 0;
		while (is_delim(str[i + k], delim) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (s[j] == 0)
		{
			for (k = 0; k < j; k++)
		       		free(s[k]);
			free(s);;
		return (NULL);	
		}

		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}





/**
 * split_string2 - splits a string into words
 *
 * @str: the input string
 *
 * @delim: the delimeter
 *
 * Return: returns a pointer to an array of strings or NULL if function fails
 */



char **split_string2(char *str, char delim)
{
	int i, j, k, m, count_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != delim && str[i +1] == delim) || (str[i] != delim && str[i + 1] == '\0')
			count_words++;
	if (count_words == 0)
		return (NULL);
	s = malloc((1 + count_words) * sizeof(char *));
	if (s == NULL)
		return (NULL);
	for (i = 0, j = 0; j < count_words; j++)
	{
		while (str[i] == delim)
		
			i++;

		k = 0;
		while (str[i + k] != delim && str[i + k] != '\0')

			k++;
		
		s[j] = malloc((k + 1) * sizeof(char));
		if (s[j] == NULL)
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
		{
			s[j][m] = str[i++];
		}
		s[j][m] = '\0';
	}
	s[j] = NULL;
	return (s);
}










































