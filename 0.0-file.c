#include "shell.h"


/**
 * interact - checks if shell is in interactive mode
 *
 * @info: structure address
 *
 *  Return: 1 if in interactive mode and 0 otherwise
 */


int interact(info_t *info)
{
	return(isatty(STDIN_FILENO) && info -> readfd <= 2);
}



/**
 * contains - checks if character is a delimeter
 *
 * @c: the character to check
 *
 * @delim: the delimeter string to check
 *
 * Return: 1 if delimeter is ound and 0 otherwise
 */


int contains(char c, char delim[])
{
	int i;

	for (i = 0; delim[i] != '\0'; i++)
	{
		if (delim[i] == c)
		{
			return(1);
		}
	}
	return (0);
}



/**
 * _isalpha - chacks for alphabet character in a string
 *
 * @ch: the character to search for
 *
 * Return: 1 if ch is alphabet and 0 otherwise
 */


int _isalpha(int ch)
{
	if ((ch >= 'a' && <= 'z') || (ch >= 'A' && <= 'Z'))
	{
		return(1);
	}

	else
	{
		return(0);
	}
}


/**
 * _atoi - converts a string to an integer
 *
 * @str: string to be converted
 *
 *  Return: output to the function
 */


int _atoi(char *str)
{
	int i, sign, output, flag;
	unsigned int result;

	sign = 1;
	result = 0;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == '-')
		{
			sign = -1;
		}


		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			result = result * 10 + (str[i] - '0');
		}

		else if (flag == 1)
		{
			break;
		}
	}

	output = result * sign;

	return(output);
}
