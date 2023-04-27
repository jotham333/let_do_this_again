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

#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3


#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_;
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
imple_shell_history"
#define HIST_MAX 4096

extern char **environ;


/**
 *  * struct liststring - is a singly linked list
 *   * @num: the number field
 *    * @str: a string
 *     * @next: points to the next node
 *      */
typedef struct liststring
{
	int num;
	char *str;
	struct liststring *next;
} list_t;


typedef struct builtin
{
	char *type;
	int (*func)(info_t *)
}builtin_table;



typedef struct info_s {
        int readfd;
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num
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



#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL,\ 0, 0, 0}


/* atoi */
int interact(info_t *info);
int contains(char c, char delim[]);
int _isalpha(int ch);
int _atoi(char *str);




/*shell_builtin.c*/
int exit_shell(info_t *info);
int change_direct(char *path);
int display_help(info_t *info);


/*1-shell_builtin.c*/
int _history(info_t *info);
int unset_alias(info_t *info, char *s);
int set_alias(info_t *info, char *str);
int _print_alias(list_t *alias_node);
int my_alias(info_t *info);vi


/*mj_env.c*/
int my_env(info_t *info);
char *_getenv(shell_info_t *shell_info, const char *var_name);
int my_setenv(shell_info_t *shell_info);
int mu_unsetenv(shell_info_t *shell_info);
int populate_env_list(shell_info_t *shell_info);


/*error.c*/
void _eputs(char *str);
int _eputchar(char c);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);


/*util_error.c*/
int _erratoi(char *s);
void print_error(info_t *info, char *estr);
int print_d(int input, int fd);
char *convert_number(long int num, int base, int flags);
void remove_comments(char *buf);

/*string.c*/
:wint _strlen(char *str);
int _strcmp(char *str1, char *str2);
char *start_with(const char *haystack, const char *needle);
char *_strcat(char *dest, char *src);


/*string1.c*/
char *_strcpy(char *dest, const char *src);
char *_strdup(const char *str);
int _putchar(char c);
void _puts(char *str);


/*split_str.c*/
char **split_string(char *str, char *delim);
char **split_string2(char *str, char delim);


/*find_hist.c*/
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);



/*parser.c*/
int _iscmd(info_t *imfo, char *path);
char *_dup_chars(char *pathstr, int start, int stop);
char *search_path(info_t *info, char *pathstr, char *cmd);




/*rm_list.c*/
list_t *add_node(list_t **head, const char *str, int num);
list_t *add_node_end(list_t **head, const char *str, int num);
size_t print_list_str(const list_t *head);
int delete_node_at_index(list_t **head, unsigned int index);
void free_list(list_t **heavoid print_error(info_t *info, char *estr);


/*free_mem.c*/
int _free(void **ptr);


/*find_list.c*/
size_t list_len(const list_t *head);
char **list_to_strings(list_t *head);
size_t print_list(const list_t *head);
list_t *node_starts_with_prefix(list_t *node, char *prefix, char next_char);
ssize_t get_node_index(list_t *head, list_t *node);


/*mj_exit.c*/
char *_strchr(char *str, char target);
char *_strncpy(char *destination, char *source, int num_chars);
char *_strncat(char *destination, char *source, int num_chars);



/*shell_looper.c*/
int hsh(info_t *info, char **args);
int find_builtin(info_t *info);
void find_cmd(info_t *info);
void fork_cmd(info_t *info);


/*realloc.c*/
char *_memset(char *str, char b, unsigned int n);
void free_str(char **s);
void *_realloc(void *, unsigned int, unsigned int);


/*manip_info_t.c*/
void clear_info(info_t *info);
void set_info(info_t *info, char **av);
void free_info(info_t *info, int all);


/*mj_getline.c*/
ssize_t input_buf(info_t *info, char **buf, size_t *len);
ssize_t get_input(info_t *info);
ssize_t read_buf(info_t *info, char *buf, size_t *i);
int _getline(info_t *info, char **ptr, size_t *length);
void sigintHandler(__attribute__((unused))int sig_num);


/* mj_getenv.c */
char **_getenv(info_t *info);
int _unsetenv(info_t *info, char *var);
int _setenv(info_t *info, char *var, char *value);


/* init_prog.c */
int main(int ac, char **av);

/* variables */
int replace_string(char **old, char *new);
int detect_chain(info_t *info, char *buff, size_t *ptr);
void check_pipeline(info_t *info, char *buff, size_t *ptr, size_t i, size_t len);
int alias_replace(info_t *info);
int replace_vars(info_t *info);


#endif /*SHELL_H*/
