#include "shell.h"


/**
 * _history - this display the history list, one command by line, preceded
 * with line number and starting at 0
 *
 * @info: a struct containing potenrial arguments. used to maintain
 * constant function prototype
 *
 * Return: Always 0;
 */



int _history(info_t *info)
{
	print_list_str(info->history);
	return (0);
}



/**
 * unset_alias - it sets alias to strings
 *
 * @info: parameter structure
 *
 * @s: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */


int unset_alias(info_t *info, char *s)
{
	char *equal_sign_pos, c;
	int nreturn;

	equal_sign_pos = _strchr(s, '=');
	if (equal_sign_pos == NULL)
	{
		return (1);
	}

	c = *equal_sign_pos;
	*equal_sign_pos = 0;
	nreturn = delete_node_at_index(&(info->alias), get_node_index(info->alias,
				node_starts_with(info->alias, s, -1)));

	*equal_sign_pos = c;

	return (nreturn);
}




/**
 * set_alias - set an alias to string
 *
 * @info: parameter structure
 *
 * @str: string alias
 *
 * Return: Always 0 when successful ans 1 on error
 */


int set_alias(info_t *info, char *str)
{
	char *equal_sign_pos;

	equal_sign_pos = _strchr(str, '=');
	if (equal_sign_pos == NULL)
	{
		return (1);
	}

	if (*(equal_sign_pos + 1) == '\0')
	{
		return (unset_alias(info, str));
	}

	unset_alias(info, str);

	if (add_node_end(&(info->alias), str, 0) == NULL)
	{
		return (1);
	}

	return (0);
}



/**
 * _print_alias - prints an alias string
 *
 * @alias_node: alias node
 *
 * Return: Always return 0 on success and 1 on error
 */


int _print_alias(list_t *alias_node)
{
	char *equal_sign, *c;

	equal_sign = NULL;
	c = NULL;

	if (alias_node == NULL)
	{
		return (1);
	}

	equal_sign = _strchr(alias_node->str, '=');

	for (c = alias_node->str; c <= equal_sign; c++)
	{
		_putchar(*c);
	}

	_putchar('\'');
	_puts(equal_sign + 1);
	_puts("\n");

	return (0);
}




/**
 * my_alias - create an alias
 *
 * @info: struct containing arguments
 * used to maintain constant function prototype
 *
 * Return: 0 always
 */


int my_alias(info_t *info)
{
	int i;
	char *equal_char;
	list_t *alias_node;

	i = 0;
	equal_char = NULL;
	alias_node = NULL;

	if (info->argc == 1)
	{
		alias_node = info->alias;
		while (alias_node != NULL)
		{
			_print_alias(alias_node);
			alias_node = alias_node->next;
		}
		return (0);
	}

	for (i = 1; info->argv[i] != NULL; i++)
	{
		equal_char = _strchr(info->argv[i], '=');
		if (equal_char != NULL)
		{
			set_alias(info, info->argv[i]);
		}
		else
		{
			_print_alias(node_starts_with(info->alias, info->argv[i], '='));
		}
	}

	return (0);
}
