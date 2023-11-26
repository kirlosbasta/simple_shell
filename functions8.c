#include "main.h"

/**
 * length_argv - Length of argument in argv
 * @argv: List of argument
 *
 * Return: Number of argument
 */

int length_argv(char **argv)
{
	int i = 0;

	while (argv[i] != NULL)
	{
		i++;
	}
	return (i + 1);
}

/**
 * shiftToRight - shitf a list to the right
 * @argv: pointer to the list
 *
 * Return: Nothing
 */

void shiftToRight(char **argv)
{
	int i = 0;

	while (argv[i] != NULL)
	{
		i++;
	}
	for (; argv[i] != *argv; i--)
	{
		argv[i + 1] = argv[i];
	}
}

/**
 * copy_list - copy list from one to another
 * @old: old list
 * @new: new list
 *
 * Return: Nothing
 */
void copy_list(char **old, char **new)
{
	while (*old != NULL)
	{
		*new = *old;
		new++;
		old++;
	}
	*new = NULL;
}
/**
 * print_list - print list of argument
 * @argv: list of argument
 *
 * Return: Nothing
 */

void print_list(char **argv)
{
	int i;

	for (i = 0; argv[i] != NULL; i++)
	{
		printf("%s ", argv[i]);
	}
	printf("\nlength = %d\n", i + 1);
}

/**
 * check_logical - checkc the logical AND && , OR ||
 * @var: list of variables
 *
 * Return: 1 in success and 0 in failure
 */

int check_logical(var_inf *var)
{
	int i, logic;
	list_t *head = NULL, *current;
	char **tmp, **tmp2;

	arrange_argv(var, "||");
	arrange_argv(var, "&&");
	tmp = var->argv, tmp2 = tmp;
	for (i = 0; var->argv[i] != NULL; i++)
	{
		if (!_strcmp(var->argv[i], "&&"))
		{
			logic = 1;
			var->argv[i] = NULL;
			add_node_end_argv_int(&head, tmp, logic);
			tmp = var->argv + i + 1;
			continue;
		}
		if (!_strcmp(var->argv[i], "||"))
		{
			logic = 2;
			var->argv[i] = NULL;
			add_node_end_argv_int(&head, tmp, logic);
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
			add_node_end_argv_int(&head, tmp, 0);
		while (head != NULL)
		{
			logic = head->logic;
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
				head->argv = NULL;
				head = head->next;
				if (*var->status && logic == 2)
				{
					continue;
				}
				else if (*var->status && logic == 1)
				{
					break;
				}
			}
			fork_child(var);
			head->argv = NULL;
			head = head->next;
			if (!*var->status && logic == 2)
			{
				break;
			}
			else if (!*var->status && logic == 1)
			{
				continue;
			}
			else if (*var->status && logic == 2)
			{
				continue;
			}
			else if (*var->status && logic == 1)
			{
				break;
			}
		}
	}
	free_single_list_argv(current);
	free(tmp2);
	return (1);
}
