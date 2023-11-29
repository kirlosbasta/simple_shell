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

/**
 * variable_repalcement - Handle the variables
 * @var: list of variables
 *
 * Return: Nothing
 */

list_t *variable_repalcement(var_inf *var)
{
	int i, idx;
	pid_t parent;
	list_t *head = NULL;
	char *num = NULL, *value;

	for (i = 0; var->argv[i] != NULL; i++)
	{
		idx = check_delim(var->argv[i], "$");
		if ((idx || var->argv[i][0] == '$') && _strlen(var->argv[i]) > 1)
		{
			value = _getenv(var->argv[i] + idx + 1, var->environ);
			if (var->argv[i][idx + 1] == '?')
			{
				num = num_to_str(*var->status);
				add_node(&head, num);
				var->argv[i] = num;
			}
			else if (var->argv[i][idx + 1] == '$')
			{
				parent = getpid();
				num = num_to_str((int) parent);
				add_node(&head, num);
				var->argv[i] = num;
			}
			else if (value != NULL)
			{
				var->argv[i] = value;
			}
			else
			{
				var->argv[i][idx] = '\0';
			}
		}
	}
	return (head);
}

/**
 * checks - list of builtin checks
 * @var: List of variables
 *
 * Return: 1 if found and 0 if not
 */

int checks(var_inf *var)
{
	if (check_logical(var))
		return (1);
	else if (check_semicolon(var))
		return (1);
	else if (check_builtin(var))
		return (1);
	return (0);
}
