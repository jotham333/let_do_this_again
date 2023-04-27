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
			write(STDERR_FILENO, error_msg, strlen(error_msg));
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
 * change_direct - the function changes between directories
 *
 * @path: the path specified by the user to chnage to
 *
 * Return: 0 always
 */



int change_direct(char *path)
{
	char *home_dir, *prev_dir, cwd[1024];
	int chdir_ret;
	char *err_msg, *err_msg_2;

	err_msg = "my_cd: Home environment variable not set\n";
	err_msg_2 = "my_cd: OLDPWD not set\n";
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("Failed to get cwd");
		return (1);
	if (path == NULL)
	{
		home_dir = _getenv("HOME");
		if (home_dir == NULL)
		{
			write(STDERR_FILENO, err_msg, sizeof(err_msg));
			return (1);
		}
		chdir_ret = chdir(home_dir);
	}
	else if (_strcmp(path, "-") == 0)
	{
		prev_dir = getenv("OLDPWD");
		if (prev_dir == NULL)
		{
			write(STDERR_FILENO, err_msg_2, sizeof(err_msg_2));
			return (1);
		}
		chdir_ret = chdir(prev_dir);
	}
	else
		chdir_ret = chdir(path);
	if (chdir_ret == -1)
		perror("my_cd");
		return (1);
	if (_setenv("PWD", getcwd(cwd, sizeof(cwd)), 1) == -1)
		perror("my_cd");
		return (1);
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
		_puts(*arg_array);
	}

	return (0);
}


















