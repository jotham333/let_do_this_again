#include "shell.h"


/**
 * hsh - main shell loop
 *
 * @info:the parameter & return info structure
 *
 * @args: the argument vector from main()
 *
 * Return: 0 when successful and 1 when error occurs
 */



int hsh(info_t *info, char **args)
{
	ssize_t input_res = 0;
	int builtin_res = 0;

	while (input_res != -1 && builtin_res != -2)
	{
		clear_info(info);
		if (interact(info))
			_puts("$ ");
		_eputchar(BUFF_FLUSH);
		input_res = get_input(info);
		if (input_res != -1)
		{
			set_info(info, args);
			builtin_res = find_builtin(info);
			if (builtin_res == -1)
				find_cmd(info);
		}
		else if (interact(info))
			_putchar('\n');
		free_info(info, 0);
	}

	write_history(info);
	free_info(info, 1);
	if (!interact(info) && info->status)
		exit(info->status);
	if (builtin_res == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_res);
}



/**
 * find_builtin - finds a builtin command
 *
 * @info: the parameter & return Info structure
 *
 * Return: -1 if builtin was not found,
 *		0 if builtin was executed successfully,
 *		1 if builtin found but noy successful,
 *		-2 if builtin signals exit()
 */



int find_builtin(info_t *info)
{
	int i, builtin_in_ret = -1;
	builtin_table builtintnbl[] = {
		{"exit", exit_shell},
		{"env", my_env},
		{"help", display_help},
		{"history", _history},
		{"setenv", my_setenv},
		{"unsetenv", my_unsetenv},
		{"cd", _cd},
		{"alias", my_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintnbl[i].type; i++)
	{
		if (_strcmp(info->argv[0], builtintnbl[i].type) == 0)
		{
			info->line_count++;
			builtin_in_ret = builtintnbl[i].func(info);
			break;
		}
	}

	return (builtin_in_ret);
}




/**
 * find_cmd - finds a command in PATH
 *
 * @info: the parameter & return info structure
 *
 * Return: void
 */


void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, j;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, j = 0; info->arg[i]; i++)
	{
		if (contains(info->arg[i], "\t\n"))
			j++;
	}
	if (!j)
		return;

	path = search_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interact(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && _iscmd(info, info->argv[0]))
		{
			fork_cmd(info);
		}
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}




/**
 * fork_cmd - forks an exec thread to run cmd
 *
 * @info: the parameter & return info struct
 *
 * Return: void
 */


void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));

			if (WIFEXITED(info->status))
			{
				info->status = WEXITSTATUS(info->status);
				if (info->status == 126)
					print_error(info, "permmission denied\n");
			}
	}
}
