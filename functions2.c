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

/**
 * _strcmp - comapare s1 by s2
 * @s1: pointer to string
 * @s2: pointer to string
 * Return: if s1 greater than s2 the return is positive
 * if s1 less than s2 the return is negative
 * if both are the same return 0
 */

int _strcmp(char *s1, char *s2)
{
	int i = 0;
	int diff;

	while (s1[i] == s2[i] && s1[i] != '\0')
	{
		i++;
	}
	diff = s1[i] - s2[i];
	return (diff);
}
