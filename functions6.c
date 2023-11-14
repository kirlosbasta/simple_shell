#include "main.h"

/**
 * cd - Change the current working directory
 * @environ: Enviromental variables
 * @argv: Argument lis
 * @av: command line argument
 *
 * Return: 0 on success and -1 on failure
 */

int cd(char **argv, char **environ, char **av)
{
	char *tmp = NULL, *home, *oldpwd;

	tmp = getcwd(tmp, 0);
	if (argv[1] != NULL)
	{
		if (_strcmp(argv[1], "-") == 0)
		{
			oldpwd = _getenv("OLDPWD", environ);
			chdir(oldpwd);
			_setenv("PWD", oldpwd, 1, environ);
		}
		else if (chdir(argv[1]) == -1)
		{
			write(STDERR_FILENO, av[0], _strlen(av[0]));
			write(STDERR_FILENO, ": ", 3);
			write(STDERR_FILENO, argv[0], _strlen(argv[0]));
			write(STDERR_FILENO, ": can't cd to ", 15);
			write(STDERR_FILENO, argv[1], _strlen(argv[1]));
			perror(" ");
			return (-1);
		}
		_setenv("PWD", argv[1], 1, environ);
	}
	else
	{
		home = _getenv("HOME", environ);
		chdir(home);
		_setenv("PWD", home, 1, environ);
	}
	_setenv("OLDPWD", tmp, 1, environ);
	free(tmp);
	return (0);
}
