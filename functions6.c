#include "main.h"

/**
 * cd - Change the current working directory
 * @var: pointer to struct contain collection of variables
 *
 * Return: 0 on success and -1 on failure
 */

int cd(var_inf *var)
{
	char *tmp = NULL, *home, *oldpwd, *temp;

	tmp = getcwd(tmp, 0);
	if (var->argv[1] != NULL)
	{
		if (_strcmp(var->argv[1], "-") == 0)
		{
			oldpwd = _getenv("OLDPWD", var->environ);
			if (oldpwd == NULL)
				oldpwd = tmp;
			chdir(oldpwd);
			write(STDOUT_FILENO, oldpwd, _strlen(oldpwd));
			write(STDOUT_FILENO, "\n", 1);
			_setenv("PWD", oldpwd, 1, var->environ, &var->head);
		}
		else if (chdir(var->argv[1]) == -1)
		{
			temp = var->argv[1];
			execve_error(var, ": can't cd to ");
			write(STDERR_FILENO, temp, _strlen(temp));
			write(STDERR_FILENO, "\n", 1);
			return (-1);
		}
		_setenv("PWD", var->argv[1], 1, var->environ, &var->head);
	}
	else
	{
		home = _getenv("HOME", var->environ);
		if (home == NULL)
			home = tmp;
		chdir(home);
		_setenv("PWD", home, 1, var->environ, &var->head);
	}
	_setenv("OLDPWD", tmp, 1, var->environ, &var->head);
	free(tmp);
	return (0);
}

/**
 * add_node - Add str and it's length to a list
 * @head: The address of the head
 * @str: String to be added to the new node
 *
 * Return: pointer to the new node
 */

list_t *add_node(list_t **head, const char *str)
{
	list_t *node = malloc(sizeof(list_t));

	if (node == NULL)
	{
		return (NULL);
	}
	node->str = (char *) str;
	node->next = *head;
	*head = node;
	return (node);
}

/**
 * check_comment - check if one of the arument is a comment
 * @argv: list of argument
 *
 * Return: 1 if present and 0 if not
 */

int check_comment(char **argv)
{
	while (*argv != NULL)
	{
		if (_strcmp(*argv, "#") == 0)
		{
			*argv = NULL;
			return (1);
		}
		argv++;
	}
	return (0);
}

/**
 * num_to_str - convert a number to string
 * @num: Number
 *
 * Return: string
 */

char *num_to_str(int num)
{
	char *str = malloc(sizeof(char) * 6);
	int i = 0;

	while (num > 0)
	{
		str[i++] = (num % 10) + '0';
		num /= 10;
	}
	str[i] = '\0';
	rev_string(str);
	return (str);
}

/**
 * rev_string - printthe string and it reverse
 * @s: Poiinter to string
 * Return: Nothing
 */

void rev_string(char *s)
{
	int len = _strlen(s);
	int i;

	for (i = 0; i < len / 2; i++)
	{
		char temp = s[i];

		s[i] = s[len - 1 - i];
		s[len - 1 - i] = temp;
	}
}
