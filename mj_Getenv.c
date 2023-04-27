#include "shell.h"


/**
 * get_environ - returns a copy of the environment variables as a string array
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Returns NULL on failure or the copied
 * environment variables as a string array.
 */
char **get_environ(info_t *info)
{
	while (!info->environ || info->env_changed)
	{
	info->environ = list_to_strings(info->env);
	info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * Return: Returns 1 if the variable is deleted, 0 otherwise
 */
int _unsetenv(info_t *info, char *var)
{
	size_t i;
	list_t *nd = info->env;
	char *ptr;

	if (!nd || !var)
		return (0);
	for (i = 0; nd != NULL; i++, nd = nd->next)
	{
		ptr = start_with(nd->str, var);
		if (ptr && *ptr == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = -1;
			nd = info->env;
		}
	}
	return (info->env_changed);
}


/**
* _setenv - Initialize a new environment variable, or modify an existing one
* @info: Structure containing potential arguments. Used to maintain
*        constant function prototype.
* @var: the string env var property
* @value: the string env var value
* Return: Returns 0 on success, otherwise 1
*/

int _setenv(info_t *info, char *var, char *value)
{
char *buf = NULL;
list_t *node;
char *p;

if (var == NULL || !value)
return (0);

buf = malloc(_strlen(var) + _strlen(value) + 2);
if (!buf)
return (1);
_strcpy(buf, var);
_strcat(buf, "=");
_strcat(buf, value);

for (node = info->env; node; node = node->next)
{
p = start_with(node->str, var);
if (p && *p == '=')
{
free(node->str);
node->str = buf;
info->env_changed = 1;
return (0);
}
}

add_node_end(&(info->env), buf, 0);
free(buf);
info->env_changed = 1;
return (0);
}
