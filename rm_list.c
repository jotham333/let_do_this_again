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
* delete_node_at_index- delete node at agiven index
* @head: address of pointerto first node
* @temp: temp for node while transversing
* @index: cue index for node to delete
* If the index is 0, the first node is deleted, and the head 
* pointer is updated to point to the second node in the list. 
* Then, the memory allocated to the deleted node is freed, 
* Return: 1 (success).
*/
int delete_node_at_index(list_t **head, unsigned int index)
{
if (head == NULL || *head == NULL)
return 0;
if (index == 0)
{
list_t *temp = *head;
*head = (*head)->next;
free(temp->str);
free(temp);
return 1;
}
else
{
unsigned int i = 1;
list_t *prev_node = *head;
while (prev_node != NULL && i != index)
{
prev_node = prev_node->next;
i++;
}
if (prev_node == NULL || prev_node->next == NULL)
return 0;
list_t *next_node = prev_node->next->next;
free(prev_node->next->str);
free(prev_node->next);
prev_node->next = next_node;
return 1;
}
}

/**
* free_list - frees all nodes of a linked list
* @head_ptr: address of pointer to head node
* It take a double pointer to head of the list (head_ptr) and returns void.
* Return: void
*/
void free_list(list_t **head_ptr)
{
list_t *node, *next_node, *head;

if (head_ptr == NULL)
return;
head = *head_ptr;
if (head == NULL)
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
