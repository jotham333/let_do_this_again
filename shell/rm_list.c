#include "shell.h"

/**
* add_node - adds a node to the start of the list
* @head: address of pointer to head node
* @str: str field of node
* @num: node index used by history
* It takes as input a double pointer to the head of the list (head),
* a string to be stored in the new node (str), and an
* integer index to be stored in the new node (num).
* Return: size of list
*/
list_t *add_node(list_t **head, const char *str, int num)
{
list_t *new_node;

if (head == NULL)
{
return (NULL);
}
new_head = malloc(sizeof(list_t));
if (new_node == NULL)
{
return (NULL);
}
_memset((void *)new_node, 0, sizeof(list_t));
new_head->num = num;

if (str != NULL)
{
new_node->str = _strdup(str);
if (new_node->str == NULL)
{
free(new_node);
return (NULL);
}
}
else
{
new_node->str = NULL;
}

if (*head != NULL)
{
new_node->next = *head;
*head = new_node;
}
else
{
new_node->next = NULL;
*head = new_node;
}

return (new_node);
}
/**
* add_node_end - adds a node to the end of the list
* @head: address of pointer to head node
* @str: str field of node
* @num: node index used by history
* It takes the same input as add_node and returns a pointer to the new node
* Return: size of list
*/

list_t *add_node_end(list_t **head, const char *str, int num)
{
list_t *new_node, *current_node;

if (head == NULL)
return (NULL);

new_node = malloc(sizeof(list_t));
if (new_node == NULL)
return (NULL);
_memset((void *)new_node, 0, sizeof(list_t));
new_node->num = num;
if (str != NULL)
{
new_node->str = _strdup(str);
if (new_node->str == NULL)
{
free(new_node);
return (NULL);
}
}

current_node = *head;
if (current_node != NULL)
{
while (current_node->next != NULL)
{
current_node = current_node->next;
}
current_node->next = new_node;
}
else
{
*head = new_node;
}

return (new_node);
}
/**
* print_list_str - prints only the str element of a list_t linked list
* @head: pointer to first node
* The function print string in each node, or "(nil)" if the str field is NULL,
* Return: size of list
*/
size_t print_list_str(const list_t *head)
{
size_t size = 0;

while (head)
{
_puts(head->str ? head->str : "(nil)");
_puts("\n");
head = head->next;
size++;
}
return (size);
}
/**
* delete_node_at_index - deletes node at given index
* @head: address of pointer to first node
* @index: index of node to delete
* It takes a double pointer to the head of the list (head)
* and an index (index) and returns 1 on success or 0 on failure.
* Return: 1 on success, 0 on failure
*/
int delete_node_at_index(list_t **head, unsigned int index)
{
if (!head || !*head)
return (0);

if (index == 0)
{
list_t *current_node = *head;
*head = (*head)->next;
free(current_node->str);
free(current_node);
return (1);
}
else
{
list_t *previous_node = *head;
list_t *current_node = (*head)->next;
unsigned int i = 1;

while (i < index && current_node)
{
previous_node = current_node;
current_node = current_node->next;
i++;
}

if (i == index && current_node)
{
previous_node->next = current_node->next;
free(current_node->str);
free(current_node);
return (1);
}
}

return (0);
}
/**
* free_list - frees all nodes of a list
* @head_ptr: address of pointer to head node
* It take a double pointer to head of the list (head_ptr) and returns void.
* Return: void
*/
void free_list(list_t **head_ptr)
{
list_t *node, *next_node, *head;

if (!head_ptr)
return;
head = *head_ptr;
if (!head)
return;
node = head;
while (node)
{
next_node = node->next;
if (node->str)
free(node->str);
free(node);
node = next_node;
}
*head_ptr = NULL;
}
