#include "main.h"

/**
 * _setenv_helper - Help setenv
 * @name: name of the variable
 * @value: value of the variable
 *
 * Return: pointer to newly allocated merory on success and null on failure
 */

char *_setenv_helper(char *name, char *value)
{
	char *new_var;
	int name_len, value_len;

	if (name_value_check((char *)name, (char *)value))
		return (NULL);
	name_len = _strlen((char *)name);
	value_len = _strlen((char *) value);
	new_var = malloc(sizeof(char) * (name_len + value_len + 2));
	if (new_var == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	return (new_var);
}

/**
 * fork_child - Fork helper
 * @var: pointer to struct contain collection of variables
 *
 * Return: 0 in success and 1 in failure
 */

int fork_child(var_inf *var)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
		perror("Fork Error\n");
	if (child_pid == 0)
	{
		if (execve(var->dir, var->argv, var->environ) == -1)
		{
			execve_error(var, ": not found\n");
			return (1);
		}
	}
	else
	{
		wait(var->status);
		*var->status = WEXITSTATUS(*var->status);
		free(var->argv);
		if (var->dir != NULL)
			free(var->dir);
		var->dir = NULL;
		var->argv = NULL;
	}
	return (0);
}

/**
 * semicolon_wrapper - Shorten the code into functions
 * @var: list of variables
 * @head: head of list
 *
 * Return: Nothing
 */

void semicolon_wrapper(var_inf *var, list_t *head)
{
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
			head->argv = NULL;
			head = head->next;
			continue;
		}
		fork_child(var);
		head->argv = NULL;
		head = head->next;
	}
}

/**
 * logical_wrapper - Shorten the code into functions
 * @var: list of variables
 * @head: head of list
 *
 * Return: Nothing
 */

void logical_wrapper(var_inf *var, list_t *head)
{
	int logic;

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
				continue;
			else if (*var->status && logic == 1)
				break;
		}
		fork_child(var);
		head->argv = NULL;
		head = head->next;
		if (!*var->status && logic == 2)
			break;
		else if (!*var->status && logic == 1)
			continue;
		else if (*var->status && logic == 2)
			continue;
		else if (*var->status && logic == 1)
			break;
	}
}
