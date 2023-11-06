#include "main.h"

/**
 * execve_error - Handle execve error
 * @av: List of main command line argument
 * @argv: List of arguments
 * @buf: buffer
 *
 * Return: Nothing
 */

void execve_error(char **av, char **argv, char *buf)
{
	write(STDERR_FILENO, av[0], _strlen(av[0]));
	write(STDERR_FILENO, ": ", 3);
	write(STDERR_FILENO, argv[0], _strlen(argv[0]));
	perror(" ");
	free(buf);
	free(argv);
}
