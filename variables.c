#include "shell.h"






/**
 * replace_string - string replacement
 *
 * @old: address of the old string
 *
 * @new: the new string
 *
 * Return: 1 if replaced, 0 otherwise
 */

int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

/**
 * detect_chain - checks if the current buffer is a chain delimeter
 *
 * @info: the parameter struct
 *
 * @buff: the char buffer
 *
 * @ptr: addresses current position of buffer
 *
 *
 * Return: 1 if chain delimeter and 0 otherwise
 */



int detect_chain(info_t *info, char *buff, size_t *ptr)
{
	size_t m = *ptr;

	if (buff[m] == '|' && buff[m + 1] == '|')
	{
		buff[m] = 0;
		m++;
		info->cmd_buff_type = CMD_OR;
	}
	else if (buff[m] == '&' && buff[m + 1] == '&')
	{
		buff[m] = 0;
		m++;
		info->cmd_buff_type = CMD_AND;
	}
	else if (buff[m] == ';')
	{
		buff[m] = 0;
		info->cmd_buff_type = CMD_CHAIN;
	}
	else
		return (0);
	*ptr = m;
	return (1);
}



/**
 * check_pipeline - checks is we should continue piping based on last status
 *
 * @info: the parameter struct
 *
 * @buff:the character buffer
 * 
 * @ptr: address of the current posintion in buuffer
 *
 * @i: starting position on buff
 *
 * @len: length of buffer
 *
 * Retuen: void to the function
 */




void check_pipeline(info_t *info, char *buff, size_t *ptr, size_t i, size_t len)
{
	size_t m;

	m = *ptr;

	if (info->cmd_buff_type == CMD_AND)
	{
		if (info->status)
		{
			buff[i] = 0;
			m = len;
		}
	}
	if (info->cmd_buff_type == CMD_OR)
	{
		if (info->status == 0)
		{
			buff[i] = 0;
			m = len;
		}
	}
	*ptr = m;
}


/**
 * alias-replace - replaces an alias in the tikenized string
 *
 * @info:the parametr
 *
 * Return: 1 if replaced and 0 otherwise
 */

int alias_replace(info_t *info)
{
	int i;
	list_t *node;
	char *ptr;

	i = 0;
	while (i < 10)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (node == NULL)
			return (0);
		free(info->argv[0]);
		ptr = _strchr(node->str, '=');
		if (ptr == NULL)
			return (0);
		ptr = _strdup(ptr + 1);
		if (ptr == NULL)
			return (0);
		info->argv[0] = ptr;
		i++;
	}
	return (1);
}



/**
 * replace_vars - replace vars in the tokenized dtring
 *
 * @info:the parameter struct
 *
 * Return: 1 if replaved and 0 otherwise
 */

int replace_vars(info_t *info)
{
	int i;
	list_t *node;

	i = 0;
	while (info->argv[i])
	{
		if (!(info->argv[i][0] == '$' && info->argv[i][1] != '\0'))
		{
			i++;
			continue;
		}
		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
					_strdup(convert_number(info->status, 10, 0)));
			i++;
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
					_strdup(convert_number(getpid(), 10, 0)));
			i++;
			continue;
		}

		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
					_strdup(_strchr(node->str, '=') + 1));
			i++;
			continue;
		}
		replace_string(&info->argv[i], _strdup(""));
		i++;
	}
	return (0);
}
