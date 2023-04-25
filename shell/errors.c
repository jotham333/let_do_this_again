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
int count = 0;  /* Initialize a counter variable to 0 */

if (str)  /* Check if the input string is NULL */
{
while (str[count] != '\0')  /* Loop through each character of input string */
{
/* Print current character to std error using _eputchar */
_eputchar(str[count]);
count++;  /* Move to the next character */
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
* Return: number of characters printed (always 1).
*/
int _eputchar(char c)
{
static int count;
/* Initialize a static character buffer of size WRITE_BUF_SIZE */
static char buffer[WRITE_BUF_SIZE];

if (c != BUF_FLUSH) /* If input character is not BUF_FLUSH, add it to buffer */
{
buffer[count] = c;
count++;
}
/* If the input character is BUF_FLUSH or the buffer is full */
if ((c == BUF_FLUSH) || (count >= WRITE_BUF_SIZE))
{
/* Write the contents of the buffer to standard error using write */
write(STDERR_FILENO, buffer, count);
count = 0;  /* Reset the counter variable to 0 */
}

return (1);  /* Return the number of characters printed (always 1) */
}

/**
* _putfd - writes the character c to given file descriptor
* @c: The character to print
* @fd: The file descriptor to write to
*
* This function writes input character to a buffer. If buffer is full
* or input character is BUF_FLUSH, it flushes buffer by writing its
* contents to given file descriptor using write system call.
* Return: the number of characters printed (always 1).
*/
int _putfd(char c, int fd)
{
static int count;
/* Initialize a static character buffer of size WRITE_BUF_SIZE */
static char buffer[WRITE_BUF_SIZE];

if (c != BUF_FLUSH) /* If input character is not BUF_FLUSH, add it to buffer */
{
buffer[count] = c;
count++;
}
/* IF THE BUFFER IS FULL OR THE INPUT CHARACTER IS BUF_FLUSH */
if (count >= WRITE_BUF_SIZE && c != BUF_FLUSH)
{
write(fd, buffer, count); /* Write content of buffer to file descriptor */
count = 0;  /* Reset the counter variable to 0 */
}

return (1);  /* Return number of characters printed (always 1) */
}

/**
* _putsfd - prints an input string to given file descriptor
* @str: the string to be printed
* @fd: the file descriptor to write to
*
* This function prints each character of input string to given file
* descriptor using _putfd. If input string is NULL, nothing is printed.
* Return: the number of characters printed.
*/
int _putsfd(char *str, int fd)
{
/* Init a counter variable to keep track of number of characters printed */
int count = 0;

/* Check if the input string is NULL */
if (!str)
return (0);

/* Loop through each character of the input string */
while (*str)
{
/* Call _putfd to write the current character to the given file descriptor */
count += _putfd(*str++, fd);
}

/* Return the number of characters printed */
return (count);
}
