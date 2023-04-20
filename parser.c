#include "shell.h"



/**
 * is_cmd - checks if a file is executable or not
 *
 * @info:the info structure
 *
 * @path: the file path
 *
 *  Rerturn: 1 if true and 0 otherwise
 */



int is_cmd(info_t *imfo, char *path)
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
 *
 *
 *
 *
 *
 *
 */



int 





























