#include "main.h"

/**
 * main - Entry point to the shell
 * @ac: Number of argument
 * @av: List of argument
 * @environ: Enviroment variables
 *
 * Return: 0 if no error
 */

int main(UNUSED int ac, UNUSED char **av, char **environ)
{
	int read;
	size_t n = 0;
	char *buf = NULL, **argv = NULL, *dir;
	list_t *head = NULL;

	while (1)
	{
		argv = NULL;
		if (isatty(0))
			write(STDOUT_FILENO, "$ ", 3);
		read = _getline(&buf, &n, stdin);
		if (read == -1)
			exit_shell(argv, buf, &head, read);
		if (read > 1)
		{
			argv = create_list_of_arg(buf);
			if (check_builtin(argv, buf, &head, environ, read, av))
				continue;
			dir = command_exist(argv[0], environ);
			if (dir == NULL)
			{
				execve_error(av, argv, buf, dir);
				continue;
			}
			fork_child(dir, argv, environ, av, buf);
		}
	}
	return (0);
}
