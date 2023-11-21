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
	var_inf var;
	int status = 0;
	size_t n = 0;

	var.count = 0, var.status = &status;
	var.argv = NULL, var.buf = NULL, var.environ = environ, var.av = av;
	var.dir = NULL;
	var.head = NULL;
	while (1)
	{
		var.count++;
		var.argv = NULL;
		if (isatty(0))
			write(STDOUT_FILENO, "$ ", 3);
		var.read = getline(&var.buf, &n, stdin);
		if (var.read == -1)
			exit_shell(&var);
		if (var.read > 1)
		{
			var.argv = create_list_of_arg(var.buf);
			check_comment(var.argv);
			if (check_builtin(&var))
				continue;
			var.dir = command_exist(var.argv[0], environ);
			if (var.dir == NULL)
			{
				*var.status = 127;
				execve_error(&var, ": not found\n");
				continue;
			}
			fork_child(&var);
		}
	}
	return (0);
}
