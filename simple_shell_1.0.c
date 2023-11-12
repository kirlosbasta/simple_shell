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
	char *buf = NULL, *env_var = NULL, **argv = NULL;
	pid_t child_pid;

	while (1)
	{
		argv = NULL;
		if (isatty(0))
			write(STDOUT_FILENO, "$ ", 3);
		read = _getline(&buf, &n, stdin);
		if (read == -1)
			exit_shell(argv, buf, env_var, read);
		argv = create_list_of_arg(buf);
		if (check_builtin(argv, buf, env_var, environ, read))
			continue;
		child_pid = fork();
		if (child_pid == -1)
			perror("Fork Error\n");
		if (child_pid == 0)
		{
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
