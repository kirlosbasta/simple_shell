#include "main.h"

/**
 * check_char - check if a string conatian any charcter
 * @s: pointer to string
 *
 * Return: 0 if no character found and 1 on failure
 */

int check_char(char *s)
{
	int i;

	for (i = 0; s[i] != '\0'; i++)
	{
		if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
		{
			return (1);
		}
	}
	return (0);
}

/**
 * check_semicolon - check for semicolon in argv
 * @var: list of variables
 *
 * Return: 1 if ; found and 0 if not
 */

int check_semicolon(var_inf *var)
{
	int i;
	list_t *head = NULL, *current;
	char **tmp, **tmp2;

	arrange_argv(var, ";");
	tmp = var->argv, tmp2 = tmp;
	for (i = 0; var->argv[i] != NULL; i++)
	{
		if (!_strcmp(var->argv[i], ";"))
		{
			var->argv[i] = NULL;
			add_node_end_argv(&head, tmp);
			tmp = var->argv + i + 1;
		}

	}
	if (head == NULL)
	{
		return (0);
	}
	else
	{
		current = head;
		if (*tmp != NULL)
			add_node_end_argv(&head, tmp);
		while (head != NULL)
		{
			var->argv = head->argv;
			if (check_builtin(var))
			{
				head = head->next;
				continue;
			}
			var->dir = command_exist(var->argv[0], var->environ);
			if (var->dir == NULL)
			{
				*var->status = 127;
				execve_error(var, ": not found\n");
				head = head->next;
				continue;
			}
			fork_child(var);
			head = head->next;
		}
	}
	free_single_list_argv(current);
	free(tmp2);
	return (1);
}

/**
 * add_node_end_argv - Add str and it's length to a list
 * @head: The address of the head
 * @str: Pointer to string to be added to the new node
 *
 * Return: pointer to the new node
 */

list_t *add_node_end_argv(list_t **head, char **str)
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
 * free_single_list_argv - free a single linked list
 * @head: head of the list
 *
 * Return: Nothing
 */

void free_single_list_argv(list_t *head)
{
	list_t *tmp;

	while (head != NULL)
	{
		tmp = head;
		if (head->argv != NULL)
			free(head->argv);
		head = head->next;
		free(tmp);
	}
	free(head);
}

/**
 * arrange_argv - Reshape the argument to seperate the delim
 * @var: List of variables
 * @delim: the delimter
 *
 * Return: Noting
 */

void arrange_argv(var_inf *var, char *delim)
{
	int i = 0, argv_len;
	char **old_argv, **new_argv;

	argv_len = length_argv(var->argv);
	for (i = 0; var->argv[i] != NULL; i++)
	{
		if (check_delim(var->argv[i], delim))
		{
			if (_strlen(var->argv[i]) > _strlen(delim))
			{
				new_argv = malloc(sizeof(char *) * (argv_len + 2));
				copy_list(var->argv, new_argv);
				old_argv = var->argv;
				var->argv = new_argv;
				free(old_argv);
				argv_len += 2;
				var->argv[i] = strtok(var->argv[i], delim);
				shiftToRight(var->argv + i);
				var->argv[++i] = delim;
				shiftToRight(var->argv + i);
				var->argv[++i] = strtok(NULL, delim);
			}
		}
	}
}
