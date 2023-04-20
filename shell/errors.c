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
      while (str[count] != '\0')  /* Loop through each character of the input string */
        {
	  _eputchar(str[count]);  /* Print the current character to standard error using _eputchar */
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
 * returns the number of characters printed (always 1).
 */
int _eputchar(char c)
{
  static int count = 0;  /* Initialize a static counter variable to 0 */
    static char buffer[WRITE_BUF_SIZE];  /* Initialize a static character buffer of size WRITE_BUF_SIZE */

    if (c != BUF_FLUSH)  /* If the input character is not BUF_FLUSH, add it to the buffer */
    {
        buffer[count] = c;
        count++;
    }

    if ((c == BUF_FLUSH) || (count >= WRITE_BUF_SIZE))  /* If the input character is BUF_FLUSH or the buffer is full */
    {  
        write(STDERR_FILENO, buffer, count);  /* Write the contents of the buffer to standard error using write */
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
 * function returns the number of characters printed (always 1).
 */
int _putfd(char c, int fd)
{
  static int count = 0;  /* Initialize a static counter variable to 0 */
    static char buffer[WRITE_BUF_SIZE];  /* Initialize a static character buffer of size WRITE_BUF_SIZE */

    if (c != BUF_FLUSH)  /* If the input character is not BUF_FLUSH, add it to the buffer */
    {
        buffer[count] = c;
        count++;
    }

    if (count >= WRITE_BUF_SIZE && c != BUF_FLUSH)  /* If the buffer is full or the input character is BUF_FLUSH */
    {
      write(fd, buffer, count);  /* Write the contents of the buffer to the given file descriptor using write */
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
 * The function returns the number of characters printed.
 */
int _putsfd(char *str, int fd)
{
  /* Initialize a counter variable to keep track of the number of characters printed */
	int count = 0;

	/* Check if the input string is NULL */
	if (!str)
		return (0);

	/* Loop through each character of the input string */
	while (*str)
	{
	  /* Call _putfd to write the current character to the given file descriptor and increment the counter */
		count += _putfd(*str++, fd);
	} 

	/* Return the number of characters printed */
	return (count);
}
