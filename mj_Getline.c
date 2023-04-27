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
	ssize_t read = 0;
	size_t lent_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		read = _getline(buf, &lent_p, stdin);
#else
		read = _getline(info, buf, &lent_p);
#endif
		if (read > 0)
		{
			if ((*buf)[read - 1] == '\n')
			{
				(*buf)[read - 1] = '\0';
				read--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			if (_strchr(*buf, ';'))
			{
				*len = read;
				info->cmd_buf = buf;
			}
		}
	}
	return (read);

}

/**
* get_input - Retrieves the next command or chained command from stdin.
* @info: Parameter struct containing information about the current shell state.
* Return: The length of the command or chained command retrieved from stdin.
*/
ssize_t get_input(info_t *info)
{
/* Init var to hold command buffer & its position in the input buffer. */
static char *buf;
static size_t i, j, len;
ssize_t num_read = 0;
char **buf_p = &(info->arg), *p;

/* Flush the output buffer to ensure all output is displayed to the user. */
_putchar(BUFF_FLUSH);
/* Read input from stdin into buffer, buffer chained commands if necessary. */
num_read = input_buf(info, &buf, &len);
/* If EOF was encountered, return -1 to indicate the end of input. */
if (num_read == -1)
return (-1);
/* If there're command left in buffer from a chained command, process them. */
if (len > 0)
{
/* Initialize a new iterator to the current position in the buffer. */
j = i;
/* Get a pointer to the start of the current command. */
p = buf + i;
/* Check if the current command is part of a command chain. */
check_pipeline(info, buf, &j, i, len);
/* Iterate to the next semicolon or end of buffer. */
for (j = i; j < len; j++)
{
if (detect_chain(info, buf, &j))
break;
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
* @pos: size
*
* Return: num_read
*/
ssize_t read_buf(info_t *info, char *buf, size_t *pos)
{
	ssize_t bytes_read = 0;

	if (*pos > 0)
	{
		return (0);
	}

	bytes_read = read(info->readfd, buf, OUT_BUFF_SIZE);

	if (bytes_read >= 0)
	{
		*pos = (size_t)bytes_read;
	}
	return (bytes_read);
}

/**
* _getline - gets the next line of input from STDIN
* @info: parameter struct
* @ptrs: address of pointer to buffer, preallocated or NULL
* @length: size of preallocated ptr buffer if not NULL
* Return: s
*/
int _getline(info_t *info, char **ptrs, size_t *length)
{
	static char buff[OUT_BUFF_SIZE];
	static size_t i, lent;
	size_t j;
	ssize_t r, m;
	char *ptr = NULL, *new_ptr = NULL;
	char *c;

	r = 0;
	m = 0;
	ptr = *ptrs;
	if (ptr && length)
		m = *length;
	if (i == lent)
		i = lent = 0;
	r = read_buf(info, buff, &lent);
	if (r == -1 || (r == 0 && lent == 0))
		return (-1);
	c = _strchr(buff + 1, '\n');
	j = c ? 1 + (unsigned int)(c - buff) : lent;
	new_ptr = _realloc(ptr, m, m ? m + j : j + 1);
	if (new_ptr == NULL)
	{
		if (ptr != NULL)
		{
			free(ptr);
		}
		return (-1);
	}
	if (m)
		_strncat(new_ptr, buff + i, j - i);
	else
		_strncpy(new_ptr, buff + i, j - i + 1);
	m = m + j - 1;
	i = j;
	ptr = new_ptr;
	if (length)
		*length = m;
	*ptrs = ptr;
	return (m);
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
_putchar(BUFF_FLUSH);
}
