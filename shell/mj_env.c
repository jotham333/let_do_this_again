#include "shell.h"

/**
* print_environment - prints the current environment variables
*
* This function iterates over the linked list of environment variables
* stored in the shell_info_t structure and prints each variable to stdout.
*
* @shell_info: Pointer to the shell_info_t structure which contains the
*              environment variables to print.
*
* Return: Always 0.
*/
int print_environment(shell_info_t *shell_info)
/* Check if shell_info and env_vars are not NULL */
{
 if (shell_info == NULL || shell_info->env_vars == NULL)
	{
		return (1);
	}

	/* Iterate over each node in the linked list and print the variable */
	list_t *current_node = shell_info->env_vars;
	while (current_node != NULL)
	{
		print_string(current_node->str);
		current_node = current_node->next;
	}

	return (0);
}

/**
 * get_env_variable - gets the value of an environment variable
 *
 * This function searches for an environment variable in the linked list
 * of variables stored in the shell_info_t structure. It returns the value
 * of the variable if it exists, or NULL otherwise.
 *
 * @shell_info: Pointer to the shell_info_t structure which contains the
 *              environment variables to search.
 * @var_name: The name of the variable to search for.
 *
 * Return: The value of the variable if it exists, or NULL otherwise.
 */
char *get_env_variable(shell_info_t *shell_info, const char *var_name)
/* Declare a node pointer and a char pointer */
{
	list_t *node = shell_info->get_env_variable;
	char *p;

	if (node == NULL)
		return (NULL);

	/* Iterate over each node in the linked list and search for the variable */
	do {
		p = starts_with(node->str, var_name);
		if (p && *p)
			return (p);
		node = node->next;
	} while (node != NULL);

	return (NULL);
}

/**
 * set_env_variable - Initializes a new environment variable,
 *                    or modifies an existing one
 *
 * This function creates or modifies an environment variable in the
 * linked list of variables stored in the shell_info_t structure. It
 * expects two arguments: the name of the variable to create/modify,
 * and the value to assign to the variable. If the variable already
 * exists, its value will be modified. If it does not exist, a new
 * variable will be created.
 *
 * @shell_info: Pointer to the shell_info_t structure which contains the
 *              environment variables to modify.
 *
 * Return: Always 0.
 */
int set_env_variable(shell_info_t *shell_info)
/* Check if shell info and argc are not NULL, and  argc is 3 */
{
	if (shell_info == NULL || shell_info->argc != 3)
 	{
		return (1);
	}

	/* Call _set_env_variable to actually create or modify the variable */
	if (_set_env_variable(shell_info, shell_info->argv[1], shell_info->argv[2]) != 0)
	{
		return (1);
	}

	return (0);
}

/**
 * unset_env_variable - Remove an environment variable
 *
 * This function removes one or more environment variables from the
 * linked list of variables stored in the shell_info_t structure. It
 * expects one or more arguments, each representing the name of a
 * variable to remove.
 *
 * @shell_info: Pointer to the shell_info_t structure which contains the
 *              environment variables to modify.
 *
 * Return: Always 0.
 */
int unset_env_variable(shell_info_t *shell_info)
/* Check if shell_info and argc are not NULL, and argc is greater than 1 */
{
	if (shell_info == NULL || shell_info->argc == 1)
	{
		return (1);
	}

	/* Iterate through the argv array and remove each specified variable */	
for (int i = 1; i <= shell_info->argc; i++)
    {
        _unset_env_variable(shell_info, shell_info->argv[i]);
    }

    return (0);
}
/**
* populate_env_var_list - populates the env_vars linked list by iterating
* through the environment variables stored in the environ global variable.
* Each environment variable is added to the end of the linked list using the
* add_node_end function. The env_vars pointer in the shell_info struct
* is updated to point to the head of the linked list.
* @shell_info: A pointer to the shell_info_t struct containing potential arguments
* Return: Always returns 0.
*/
int populate_env_var_list(shell_info_t *shell_info)
{
if (shell_info == NULL)
{
return (1);
}

list_t *current_node = NULL;
size_t i;

/* Iterate through the environment variables in environ and add them to the */
/* end of the linked list using the add_node_end function. */
for (i = 0; environ[i] != NULL; i++)
{
add_node_end(&current_node, environ[i], 0);
}
/* Update the env_vars pointer in the shell_info struct to point to the */
   /* head of the linked list. */
shell_info->env_vars = current_node;

/* Always return 0 to indicate success. */
return (0);
}
