#include "shell.h"


/**
 * exit_shell - this function exit the shell
 *
 * @info: structure containing potential arguement used to
 *	maintain functions prototype
 *
 * Return: exit with a given exit status (0) if info.argv[0] != "exit"
 */




int exit_shell(info_t *info)
{
	int check_exit;
	char *error_msg;

	error_msg = "Invalid number: ";

	if (info->argv[1])
	{
		check_exit = _erratoi(info->argv[1]);
		if (check_exit == -1)
		{
			info->status = 2;
			write(STDERR_FILENO, error_msg, _strlen(error_msg));
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}

		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}




/**
 * _cd - the function changes between directories
 *
 * @info: the path specified by the user to chnage to
 *
 * Return: 0 always
 */



int _cd(info_t *info)
{
	char *home_dir, *prev_dir;
	char buff[1024];
	int chdir_ret;

	home_dir = getcwd(buff, 1024);
	if (!home_dir)
		_puts("TODO: >>getcwd failure<<\n");
	if (!info->argv[1])
	{
		prev_dir = _getenv(info, "HOME=");
		if (!prev_dir)
			chdir_ret = chdir((prev_dir = _getenv(info, "PWD=")) ? prev_dir : "/");
		else
			chdir_ret = chdir(prev_dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(home_dir), _putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD="));
		_putchar('\n');
		chdir_ret = chdir((prev_dir = _getenv(info, "OLDPWD=")) ? prev_dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't change directory to ");
		_eputs(info->argv[1]);
		_eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buff, 1024));
	}
	return (0);
}



/**
 * display_help - this function changes the current directory of the process
 *
 * @info: Structure containing potential arguements
 * Used to maintain constant function proto
 *
 * Return: Always return 0
 */

int display_help(info_t *info)
{
	char **arg_arr;

	arg_arr = info->argv;
	_puts("help command called. But function not yet implemented\n");

	if (0)
	{
		_puts(*arg_arr);
	}

	return (0);
}
