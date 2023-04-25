#include "shell.h"

/**
* input_buf - Reads input from stdin, buffering chained commands if necessary.
* @info: parameter struct containing information about the current shell state.
* @buf: Address of buffer to store the input.
* @len: Address of size_t variable to store the length of the input.
* Return: Number of bytes read from stdin.
*/
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
/* Init variables to hold number of bytes read and length of the input. */
ssize_t num_read = 0;
size_t len_p = 0;
/* If there is no input left in the buffer, fill it. */
if (!*len)
{
/* Free any memory allocated to the buffer. */
free(*buf);
*buf = NULL;
/* Set up signal handler to catch SIGINT signals. */
signal(SIGINT, sigintHandler);
/* Read input from stdin using getline() func or a custom implementation. */
#if USE_GETLINE
num_read = getline(buf, &len_p, stdin);
#else
num_read = _getline(info, buf, &len_p);
#endif
/* If there was input, remove any trailing newline and process comments. */
if (num_read > 0)
{
if ((*buf)[num_read - 1] == '\n')
{
(*buf)[num_read - 1] = '\0';
num_read--;
}
info->linecount_flag = 1;
remove_comments(*buf);
build_history_list(info, *buf, info->histcount++);

/* If the input contains a semicolon, it is a command chain. */
if (_strchr(*buf, ';'))
{
/* Save the input buffer and length for later use. */
*len = num_read;
info->cmd_buf = buf;
}
}
}

return (num_read);
}

/**
* get_input - Retrieves the next command or chained command from stdin.
* @info: Parameter struct containing information about the current shell state.
* Return: The length of the command or chained command retrieved from stdin.
*/
ssize_t get_input(info_t *info)
{
/* Init var to hold the command buffer and its position in the input buffer. */
static char *buf;
static size_t i, j, len;
size_t num_read = 0;
char **buf_p = &(info->arg), *p;
/* Flush the output buffer to ensure all output is displayed to the user. */
_putchar(BUF_FLUSH);
/* Read input from stdin to buffer, buffering chain commands if necessary. */
num_read = input_buf(info, &buf, &len);
/* If EOF was encountered, return -1 to indicate the end of input. */
if (num_read == -1)
return (-1);
/* If commands left in the buffer from a chained command, process them. */
if (len > 0)
{
/* Initialize a new iterator to the current position in the buffer. */
j = i;
/* Get a pointer to the start of the current command. */
p = buf + i;
/* Check if the current command is part of a command chain. */
check_chain(info, buf, &j, i, len);
while (j < len) /* Iterate to the next semicolon or end of buffer. */
{
if (is_chain(info, buf, &j))
break;
j++;
}
i = j + 1; /* increment past nulled ';'' */
if (i >= len) /* reached end of buffer? */
{
i = len = 0; /* reset position and length */
info->cmd_buf_type = CMD_NORM;
}
*buf_p = p; /* pass back pointer to current command position */
return (_strlen(p)); /* return length of current command */
}
*buf_p = buf; /* no chain detected, pass back buffer from _getline() */
return (num_read); /* return length of buffer from _getline() */
}

/**
* read_buf - reads a buffer
* @info: parameter struct
* @buf: buffer
* @i: size
*
* Return: num_read
*/
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
ssize_t num_read = 0;
if (*i >= READ_BUF_SIZE)
*i = 0;
num_read = read(info->readfd, buf, READ_BUF_SIZE - *i);
if (num_read >= 0)
*i += num_read;
return (num_read);
}

/**
* _getline - gets the next line of input from STDIN
* @info: parameter struct
* @ptr: address of pointer to buffer, preallocated or NULL
* @length: size of preallocated ptr buffer if not NULL
* Return: s
*/
int _getline(info_t *info, char **ptr, size_t *length)
{
static char buf[READ_BUF_SIZE];
static size_t i, len;
size_t k = 0;
ssize_t num_read = 0, s = 0;
char *p = NULL, *new_p = NULL, *c;
p = *ptr;
if (p != NULL && length > 0)
s = *length;
if (i >= len)
i = len = 0;
num_read = read_buf(info, buf, &len);
if (num_read == -1 || (num_read == 0 && len == 0))
return (-1);
c = _strchr(buf + i, '\n');
k = c ? 1 + (unsigned int)(c - buf) : len;
new_p = _realloc(p, s, s ? s + k : k + 1);
if (!new_p)
{ /* MALLOC FAILURE! */
if (p != NULL)
free(p);
return (-1);
if (s)
_strncat(new_p, buf + i, k - i);
else
_strncpy(new_p, buf + i, k - i + 1);
s += k - i;
i = k;
p = new_p;
if (length != NULL)
*length = s;
*ptr = p;
return (s);
}
}
/**
* sigintHandler - blocks ctrl-C
* @sig_num: the signal number
*
* Return: void
*/
void sigintHandler(__attribute__((unused))int sig_num)
{
_puts("\n");
_puts("$ ");
_putchar(BUF_FLUSH);
}
