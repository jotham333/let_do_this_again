#include "shell.h"



/**
 * _iscmd - checks if a file is executable or not
 *
 * @info:the info structure
 *
 * @path: the file path
 *
 *  Rerturn: 1 if true and 0 otherwise
 */



int _iscmd(info_t *imfo, char *path)
{
	struct stat filestat;

	(void)info;

	if (path == NULL || stat(path, &filestat) != 0)
	{
		return (0);
	}

	if (S_ISREG(filestat.st_mode))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}



/**
 * _dup_chars - the function duplicate characters
 *
 * @pathstr: this is the PATH string
 *
 * @start: the starting point(index)
 *
 * @stop: the stopping point(index)
 */



char *_dup_chars(char *pathstr, int start, int stop)
{
	int i, j;
	char *result = NULL;

	result = malloc((stop - start + 1) * sizeof(char));

	for (i = start, j = 0; i < stop; i++)
	{
		if (pathstr[i] != ':')
		{
			result[j] = pathstr[i];
			j++;
		}
	}

	result[j] = '\0';

	return (result);
}



/**
 * search_path - searches this cmd in the PATH string
 *
 * @info: the info structure
 *
 * @pathstr: thr PATH string
 *
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or not
 *
 */



char *search_path(info_t *info, char *pathstr, char *cmd)
{
	int i, current_pos;
	char *path;

	i = 0;
	current_pos = 0;

	if (pathstr == NULL)
	{
		return (NULL);
	}

	if ((_stelen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (_iscmd(info, cmd))
			return (cmd);
	}

	while (1)
	{

		if (pathstr == NULL || pathstr[i] == ':')
		{
			path = _dup_chars(pathstr, current_pos, i);
			if (path[0] == '\0')
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (_iscmd(info, path))
				return (path);
			if (pathstr[i] == '\0')
				break;
			current_pos = i;
		}
		i++;
	}
	return (NULL);
}























