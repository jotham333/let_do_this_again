#include "shell.h"

/**
 * clear_info - initializes info_t struct by setting all its fields to NULL
 * @info: struct address
 */
void clear_info(info_t *info)
{
    char *empty_str = NULL;

    if (!info) {
        return;
    }

    info->arg = empty_str; /* set arg field to NULL */
    info->argv = empty_str; /* set argv field to NULL */
    info->path = empty_str; /* set path field to NULL */
    info->argc = 0; /* set argc field to 0 */
}

/**
 * set_info - initializes info_t struct with given argument vector and sets argv and argc fields
 * @info: struct address
 * @av: argument vector
 */
void set_info(info_t *info, char **av)
{
    int arg_count = 0;
    char **arg_arr = NULL;

    if (!info) {
        return;
    }

    info->fname = av[0]; /* set fname field to first argument in argument vector */
    if (info->arg != NULL && *info->arg != '\0') /* check if arg field is not NULL and not an empty string */
    {
      arg_arr = strtow(info->arg, " \t"); /* split arg string into array of strings using whitespace as delimiter */
        if (arg_arr == NULL)
        {
	  arg_arr = malloc(sizeof(char *) * 2); /* allocate memory for array of size 2 */
            if (arg_arr)
            {
	      arg_arr[0] = _strdup(info->arg); /* duplicate arg string and store in first element of array */
	      arg_arr[1] = NULL; /* set second element to NULL */
            }
        }
        for (int i = 0; arg_arr != NULL && arg_arr[i]; i++) /* count the number of elements in array */
            arg_count++;
        info->argc = arg_count; /* set argc field to number of arguments */

        replace_alias(info); /* replace any aliases in argument array with their corresponding command strings */
        replace_vars(info); /* replace any variable references in argument array with their corresponding values */
    }
    info->argv = arg_arr; /* set argv field to argument array */
}

/**
 * free_info - frees all or some of the fields of info_t struct
 * @info: struct address
 * @all: true if freeing all fields, false otherwise
 */
void free_info(info_t *info, int all)
{
    if (!info) {
        return;
    }

    ffree(info->argv); /* free memory allocated for argument array */
    info->argv = NULL; /* set argv field to NULL */
    info->path = NULL; /* set path field to NULL */
    if (all)
    {
        char *empty_str = NULL;
        free(info->cmd_buf); /* free memory allocated for command buffer */
        if (info->cmd_buf == NULL)
	free(info->arg); /* free memory allocated for arg string if command buffer is also NULL */
        if (info->env)
	free_list(&(info->env)); /* free memory allocated for environment variables linked list */
        if (info->history)
	free_list(&(info->history)); /* free memory allocated for command history linked list */
        if (info->alias)
	free_list(&(info->alias)); /* free memory allocated for alias linked list */
	    ffree(info->environ); /* free memory allocated for environment variables array */
        info->environ = NULL; /* set environ field to NULL */
        free(info->cmd_buf); /* free memory allocated for command buffer again */
