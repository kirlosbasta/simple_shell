#include "main.h"

/**
 * _getenv - get the value of enviroment name
 * @name: pointer to the name of the varible
 * @environ: Enviromental variavles
 *
 * Return: pointer to the value in success or NULL in failure
 */

char *_getenv(const char *name, char **environ)
{
	char *value;
	int i, j;

	for (i = 0; environ[i] != NULL; i++)
	{
		for (j = 0; name[j] != '\0'; j++)
		{
			if (name[j] != environ[i][j])
			{
				break;
			}
		}
		if (name[j] == '\0')
		{
			value = environ[i] + j + 1;
			return (value);
		}
	}
	return (NULL);
}

/**
 * path_linked_list - Create a linked list for all directory in the PATH
 * @path: Path
 *
 * Return: Pointer to the head of the list
 */

list_t *path_linked_list(char *path)
{
	char *path_dup = _strdup(path);
	char *dir;
	list_t *head;

	dir = strtok(path_dup, ":");
	head = NULL;
	add_node_end(&head, dir);
	while (dir != NULL)
	{
		dir = strtok(NULL, ":");
		if (dir != NULL)
		{
			add_node_end(&head, dir);
		}
	}
	free(path_dup);
	return (head);
}

/**
 * add_node_end - Add str and it's length to a list
 * @head: The address of the head
 * @str: String to be added to the new node
 *
 * Return: pointer to the new node
 */

list_t *add_node_end(list_t **head, const char *str)
{
	list_t *node = malloc(sizeof(list_t));
	list_t *current = *head;
	char *dup_str;

	if (node == NULL)
	{
		return (NULL);
	}
	dup_str = _strdup((char *) str);
	if (dup_str == NULL)
	{
		free(node);
		return (NULL);
	}
	node->str = dup_str;
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

/**
 * command_exist - Check if a command exist and is executable
 * @name: Name of the command
 * @environ: Enviromental variables
 *
 * Return: pointer to pathname or NULL
 */

char *command_exist(char *name, char **environ)
{
	char *path = _getenv("PATH", environ);
	char *dir, *tmp;
	list_t *head = path_linked_list(path);
	list_t *current = head;

	if (access(name, X_OK) == 0)
	{
		free_single_list(head);
		dir = _strdup(name);
		return (dir);
	}
	while (current != NULL)
	{
		tmp = str_concat(current->str, "/");
		dir = str_concat(tmp, name);
		free(tmp);
		if (access(dir, X_OK) == 0)
		{
			free_single_list(head);
			return (dir);
		}
		free(dir);
		current = current->next;
	}
	free_single_list(head);
	return (NULL);
}

/**
 * free_single_list - free a single linked list
 * @head: head of the list
 *
 * Return: Nothing
 */

void free_single_list(list_t *head)
{
	list_t *tmp;

	while (head != NULL)
	{
		free(head->str);
		tmp = head;
		head = head->next;
		free(tmp);
	}
	free(head);
}
