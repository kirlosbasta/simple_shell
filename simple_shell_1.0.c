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
	int read, status;
	size_t n = 0;
	char *buf = NULL;
	char **argv = NULL;
	pid_t child_pid;

	while (1)
	{
		argv = NULL;
		if (isatty(0))
			write(STDOUT_FILENO, "$ ", 3);
		read = getline(&buf, &n, stdin);
		if (read == -1 || (_strcmp("exit\n", buf) == 0))
		{
			free(buf);
			if (read == -1 && isatty(0))
				write(STDOUT_FILENO, "\n", 2);
			exit(0);
		}
		argv = create_list_of_arg(buf);
		child_pid = fork();
		if (child_pid == -1)
			perror("Fork Error\n");
		if (child_pid == 0)
		{
			if (_strcmp("env", argv[0]) == 0)
			{
				printenv(environ);
				return (0);
			}
			if (execve(argv[0], argv, environ) == -1)
			{
				execve_error(av, argv, buf);
				return (1);
			}
		}
		else
		{
			wait(&status);
			free(argv);
		}
	}
	return (0);
}
