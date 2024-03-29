#include "shell.h"

/**
* my_env - prints the current environment variables
*
* This function iterates over the linked list of environment variables
* stored in the shell_info_t structure and prints each variable to stdout.
*
* @info: Pointer to the shell_info_t structure which contains the
*              environment variables to print.
*
* Return: Always 0.
*/
int my_env(info_t *info)
/* Check if shell_info and env_vars are not NULL */
{
print_list_str(info->env);
return (0);
}

/**
* _getenv - gets the value of an environment variable
*
* This function searches for an environment variable in the linked list
* of variables stored in the shell_info_t structure. It returns the value
* of the variable if it exists, or NULL otherwise.
*
* @info: Pointer to the shell_info_t structure which contains the
*              environment variables to search.
* @name: The name of the variable to search for.
*
* Return: The value of the variable if it exists, or NULL otherwise.
*/
char *_getenv(info_t *info, const char *name)
/* Declare a node pointer and a char pointer */
{
list_t *node = info->env;
char *p;

if (node == NULL)
return (NULL);

/* Iterate over each node in the linked list and search for the variable */
do {
p = start_with(node->str, name);
if (p && *p)
return (p);
node = node->next;
} while (node != NULL);

return (NULL);
}

/**
* my_setenv - Initializes a new environment variable,
*                    or modifies an existing one
*
* This function creates or modifies an environment variable in the
* linked list of variables stored in the shell_info_t structure. It
* expects two arguments: the name of the variable to create/modify,
* and the value to assign to the variable. If the variable already
* exists, its value will be modified. If it does not exist, a new
* variable will be created.
*
* @info: Pointer to the shell_info_t structure which contains the
*              environment variables to modify.
*
* Return: Always 0.
*/
int my_setenv(info_t *info)
/* Check if info_t and argc are not NULL, and  argc is 3 */
{
if (info == NULL || info->argc != 3)
{
_eputs("Invalid number of argument\n");
return (1);
}

/* Call _mysetenv to actually create or modify the variable */
if (_setenv(info,
info->argv[1], info->argv[2]) != 0)
{
return (1);
}

return (0);
}

/**
* my_unsetenv - Remove an environment variable
*
* This function removes one or more environment variables from the
* linked list of variables stored in the shell_info_t structure. It
* expects one or more arguments, each representing the name of a
* variable to remove.
*
* @info: Pointer to the shell_info_t structure which contains the
*              environment variables to modify.
*
* Return: Always 0.
*/
int my_unsetenv(info_t *info)
/* Check if shell_info and argc are not NULL, and argc is greater than 1 */
{
int i;
if (info == NULL || info->argc == 1)
{
return (1);
}

/* Iterate through the argv array and remove each specified variable */
for (i = 1; i <= info->argc; i++)
{
_unsetenv(info, info->argv[i]);
}

return (0);
}
/**
* populate_env_list - populates the env_vars linked list by iterating
* through the environment variables stored in the environ global variable.
* Each environment variable is added to the end of the linked list using the
* add_node_end function. The env_vars pointer in the shell_info struct
* is updated to point to the head of the linked list.
* @info: A pointer to shell_info_t struct containing potential arguments
* Return: Always returns 0.
*/
int populate_env_list(info_t *info)
{
size_t i;
list_t *current_node;
if (info == NULL)
{
return (1);
}

current_node = NULL;

/* Iterate through the environment variables in environ and add them to the */
/* end of the linked list using the add_node_end function. */
for (i = 0; environ[i] != NULL; i++)
{
add_node_end(&current_node, environ[i], 0);
}

/* Update the env_vars pointer in the shell_info struct to point to the */
   /* head of the linked list. */
info->env = current_node;

/* Always return 0 to indicate success. */
return (0);
}
