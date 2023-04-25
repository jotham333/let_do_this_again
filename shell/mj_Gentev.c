#include "shell.h"

/**
* get_env_copy - returns a copy of the environment variables as a string array
* @info: Structure containing potential arguments. Used to maintain
*        constant function prototype.
* Return: Returns NULL on failure or copied env variables as a string array.
*/
char **get_env_copy(info_t *info)
{
char **env_copy;

/* If env_var is NULL or env_changed_flag is not zero, generate new env_copy */
if (info->env_var == NULL || info->env_changed_flag != 0)
{
env_copy = list_to_strings(info->env_list);
if (env_copy == NULL)
return (NULL);

/* Update env_var with env_copy and reset env_changed_flag */
info->env_var = env_copy;
info->env_changed_flag = 0;
}

return (info->env_var);
}

/**
* unset_env_var - Remove an environment variable
* @info: Structure containing potential arguments. Used to maintain
*        constant function prototype.
* @var: the string env var property
* Return: Returns 1 if the variable is deleted, 0 otherwise
*/
int unset_env_var(info_t *info, char *var)
{
list_t *node;
char *p;
size_t index;

/* If env_list is NULL or var is NULL, return 0 indicating failure */
if (info->env_list == NULL || var == NULL)
return (0);

node = info->env_list;
index = 0;

/* Traverse the env_list and delete the node that contains the matching var */
while (node != NULL)
{
p = starts_with(node->str, var);
if (p != NULL && *p == '=')
{
info->env_changed_flag = delete_node_at_index(&(info->env_list), index);

/* Reset index and node for next iteration */
index = 0;
node = info->env_list;
continue;
}
node = node->next;
index++;
}

/* Return 1 to indicate successful deletion */
return (info->env_changed_flag);
}

/**
* set_env_var - Init a new environment variable, or modify an existing one
* @info: Structure containing potential arguments. Used to maintain
*        constant function prototype.
* @var: the string env var property
* @value: the string env var value
* Return: Returns 0 on success, otherwise 1
*/
int set_env_var(info_t *info, char *var, char *value)
{
char *buf;
list_t *node;
char *p;

/* If var or value is NULL, return 0 indicating failure */
if (var == NULL || value == NULL)
return (0);

buf = malloc(_strlen(var) + _strlen(value) + 2);
if (buf == NULL)
return (1);

/* Concatenate var, "=", and value to create a new string for the env_list */
_strcpy(buf, var);
_strcat(buf, "=");
_strcat(buf, value);

node = info->env_list;

/* Traverse the env_list and modify the node that contains the matching var */
while (node != NULL)
{
p = starts_with(node->str, var);
if (p != NULL && *p == '=')
{
free(node->str);
node->str = buf;
info->env_changed_flag = 1;
return (0);
}
node = node->next;
}

/* If the var is not found in env_list, add it */
