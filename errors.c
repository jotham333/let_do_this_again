#include "shell.h"

/**
* _eputs - prints an input string to standard error
* @str: the string to be printed
*
* This function prints each character of the input string to standard error.
* If the input string is NULL, nothing is printed.
*/
void _eputs(char *str)
{
	int count;
if (str)  /* Check if the input string is NULL */
{
/* Loop through each character of the input string */
for (count = 0; str[count] != '\0'; count++)
{
_eputchar(str[count]);  /* Print current char to std error using _eputchar */
}
}
}


/**
* _eputchar - writes the character c to standard error
* @c: The character to print
*
* This function writes the input character to a buffer. If the buffer is full
* or the input character is BUF_FLUSH, it flushes the buffer by writing its
* contents to standard error using the write system call. The function
* Return:(always 1).
*/
int _eputchar(char c)
{
static int count;
/*Declare a static character buffer of size WRITE_BUF_SIZE */
static char buffer[INPUT_BUFF_SIZE];
/* If the input character is not BUF_FLUSH, add it to the buffer */
if (c != BUFF_FLUSH)
{
buffer[count] = c;
count++;
}

/* If the input character is BUF_FLUSH or the buffer is full */
if ((c == BUFF_FLUSH) || (count >= INPUT_BUFF_SIZE))
{
int i = 0;
while (i < count)
{
/* Write the contents of the buffer to standard error using write */
write(STDERR_FILENO, &buffer[count], count);
i++;
}
count = 0;  /* Reset the counter variable to 0 */
}

return (1);  /* Return the number of characters printed (always 1) */
}

/**
* _putfd - writes the character c to given file descriptor
* @c: The character to print
* @fd: The file descriptor to write to
*
* This function writes the input character to a buffer. If the buffer is full
* or the input character is BUF_FLUSH, it flushes the buffer by writing its
* contents to the given file descriptor using the write system call. The
* Return: (always 1).
*/
int _putfd(char c, int fd)
{
int i;
static int count;
/* Initialize a static character buffer of size WRITE_BUF_SIZE */
static char buffer[INPUT_BUFF_SIZE];

if (c != BUFF_FLUSH) /* If input char is not BUF_FLUSH, add it to the buffer */
{
buffer[count] = c;
count++;
}

/* If the buffer is full or the input character is BUF_FLUSH */
if (count >= INPUT_BUFF_SIZE && c != BUFF_FLUSH)
{
for (i = 0; i < count; i++)
{
/* Write the contents of the buffer to the given file descriptor using write */
write(fd, &buffer, count);
}
count = 0;  /* Reset the counter variable to 0 */
}

return (1);  /* Return the number of characters printed (always 1) */
}
/**
* _putsfd - prints an input string to given file descriptor
* @str: the string to be printed
* @fd: the file descriptor to write to
*
* This function prints each character of the input string to the given file
* descriptor using _putfd. If the input string is NULL, nothing is printed.
* Return: the number of characters printed.
*/
int _putsfd(char *str, int fd)
{
/* Init a counter variable to keep track of the number of characters printed */
int count = 0;

/* Check if the input string is NULL */
if (str == NULL)
return (0);

/* Loop through each character of the input string */
do {
/* Call _putfd to write current char to given file descr and incr counter */
count += _putfd(*str++, fd);
} while (*str);

/* Return the number of characters printed */
return (count);
}
