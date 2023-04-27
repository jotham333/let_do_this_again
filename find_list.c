#include "shell.h"

/**
* list_len - determines the size of a linked list
* @head: pointer to the first node of the list
*
* Return: the size of the list
*/
size_t list_len(const list_t *head)
{
size_t count = 0;

if (head == NULL)  /* if list is empty */
return (count);

/* iterate through the list, incrementing count for each node */
do {
count++;
head = head->next;
} while (head);

return (count);
}

/**
* list_to_strings - returns an array of strings of the list->str
* @head: pointer to the first node of the list
*
* Return: an array of strings
*/
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i, j;
	char **strings;
	char *str;

	i = list_len(head);

	if (!head || !i)
	{
		return (NULL);
	}
	strings = malloc(sizeof(char *) * (i + 1));
	if (strings == NULL)
		return (NULL);
	i = 0;
	while (node != NULL)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
			{
				free(strings[j]);
			}
			free(strings);
			return (NULL);
		}
		str = _strcpy(str, node->str);
		strings[i] = str;
		i++;
		node = node->next;
	}
	strings[i] = NULL;
	return (strings);

}


/**
* print_list - prints all elements of a list_t linked list
* @head: pointer to the first node of the list
*
* Return: the size of the list
*/
size_t print_list(const list_t *head)
{
size_t count = 0;

if (head == NULL)  /* if the list is empty */
return (count);

/* iterate through the list, printing the contents of each node */
do {
/* print the node's number (converted to a string) */
_puts(convert_number(head->num, 10, 0));
_putchar(':');
_putchar(' ');
_puts(head->str ? head->str : "(nil)");
_puts("\n");
head = head->next;
count++;
} while (head);

return (count);
}

/**
* node_starts_with - finds the first node in
* linked list that starts with a given prefix
* @node: a pointer to the head node of the linked list to search
* @prefix: a pointer to a string representing the prefix to search for
* @next_char: a character to match after the prefix, or -1 if not specified
*
* Return: NULL
*/
list_t *node_starts_with(list_t *node, char *prefix, char next_char)
{
char *result;

/* if the linked list is empty, return NULL */
if (!node)
return (NULL);

/* iterate through linked list until the end is reached or */
do {
/* check if the current node's string starts with the given prefix */
result = start_with(node->str, prefix);

if (result && ((next_char == -1) || (*result == next_char)))
return (node);

/* move to the next node in the linked list */
node = node->next;
} while (node);

/* if no node matches the given prefix, return NULL */
return (NULL);
}
/**
* get_node_index - gets the index of a given node in a linked list
* @head: pointer to the head of the linked list
* @node: pointer to the node to find the index of
*
* This function traverses a linked list starting from head node and counts
* number of nodes visited until the given node is found. If node is found,
* function returns its index. If node is not found or if head or node pointers
* are NULL, the function returns -1.
*
* Return: the index of the given node or -1 if the node is not found or if
*         either the head or node pointers are NULL
*/
ssize_t get_node_index(list_t *head, list_t *node)
{
size_t index = 0;

if (!head || !node)
return (-1);

do {
if (head == node)
return (index);

head = head->next;
index++;
} while (head);

return (-1);
}
