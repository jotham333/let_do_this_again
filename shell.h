#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>

#define INPUT_BUFF_SIZE 1024
#define OUT_BUFF_SIZE 1024
#define BUFF_FLUSH -1


/**
 * struct liststring - is a singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststring
{
	int num;
	char *str;
	struct liststring *next;
} list_t;






typedef struct info_s {
        int readfd;
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf; 
	int cmd_buf_type; 
	int histcount;
} info_t;

/* 0-builtin functions prototype */

int my_exit(info_t *info);
int my_cd(char *path);
int my_help(info_t *info);

/* 1-builtin functions prototype */

int _history(info_t *info);
int unset_alias(info_t *info, char *s);
int set_alias(info_t *info, char *str);
int _print_alias(list_t *alias_node);
int my_alias(info_t *info);














/* atoi */

int interact(info_t *info);
int contains(char c, char delim[]);
int _isalpha(int ch);
int _atoi(char *str);

















#endif /*SHELL_H*/
