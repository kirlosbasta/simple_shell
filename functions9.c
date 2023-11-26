#include "main.h"

/**
 * add_node_end_argv_int - Add str and it's length to a list
 * @head: The address of the head
 * @str: Pointer to string to be added to the new node
 * @logical: the logical status
 *
 * Return: pointer to the new node
 */

list_t *add_node_end_argv_int(list_t **head, char **str, int logical)
{
	list_t *node = malloc(sizeof(list_t));
	list_t *current = *head;
	char **str_cpy;
	int i = 0;

	if (node == NULL)
	{
		return (NULL);
	}
	while (str[i] != NULL)
	{
		i++;
	}
	str_cpy = malloc(sizeof(char *) * (i + 1));
	for (i = 0; str[i] != NULL; i++)
	{
		str_cpy[i] = str[i];
	}
	str_cpy[i] = NULL;
	node->argv = str_cpy;
	node->logic = logical;
	if (current == NULL)
	{
		*head = node;
		node->next = NULL;
		return (node);
	}
	node->next = NULL;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = node;
	return (node);
}
