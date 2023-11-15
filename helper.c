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
 * @dir: Essenstial parameter
 * @argv: Essenstial parameter
 * @environ: Essenstial parameter
 * @av: Essenstial parameter
 * @buf: Essenstial parameter
 * @count: number of commands so far
 *
 * Return: 0 in success and 1 in failure
 */

int fork_child(char *dir, char **argv, char **environ, char **av,
				char *buf, int count)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
		perror("Fork Error\n");
	if (child_pid == 0)
	{
		if (execve(dir, argv, environ) == -1)
		{
			execve_error(av, argv, buf, dir, count);
			return (1);
		}
	}
	else
	{
		wait(&status);
		free(argv);
		if (dir != NULL)
			free(dir);
	}
	return (0);
}
