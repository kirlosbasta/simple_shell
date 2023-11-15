#include "main.h"

/**
 * execve_error - Handle execve error
 * @av: List of main command line argument
 * @argv: List of arguments
 * @buf: buffer
 * @dir: pointer to direcory
 * @count: Number of commands so far
 *
 * Return: Nothing
 */

void execve_error(char **av, char **argv, UNUSED char *buf,
				char *dir, UNUSED int count)
{
	char *num = "1";

	write(STDERR_FILENO, av[0], _strlen(av[0]));
	write(STDERR_FILENO, ": ", 3);
	write(STDERR_FILENO, num, 2);
	write(STDERR_FILENO, ": ", 3);
	write(STDERR_FILENO, argv[0], _strlen(argv[0]));
	write(STDERR_FILENO, ": not found\n", 13);
	if (dir != NULL)
		free(dir);
	free(argv);
	argv = NULL;
	dir = NULL;
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

/**
 * printenv - print Enviromnetal variables
 * @env: Enviromental variables
 *
 * Return: Nothing
 */

void printenv(char **env)
{
	int i;

	for (i = 0; env[i] != NULL; i++)
	{
		write(STDOUT_FILENO, env[i], _strlen(env[i]));
		write(STDOUT_FILENO, "\n", 2);
	}
}

/**
 * _strdup - return a copy of a string to newly allocated space in memory
 * @str: pointer to string
 *
 * Return: Pointer of the duplicated string in success
 * and NULL if insufficient memory was available
 */

char *_strdup(char *str)
{
	int i, len = 0;
	char *s;

	if (str == NULL)
	{
		return (NULL);
	}
	while (str[len] != '\0')
	{
		len++;
	}
	s = malloc(sizeof(char) * (len + 1));

	if (s == NULL)
	{
		return (NULL);
	}
	for (i = 0; str[i] != 0; i++)
	{
		s[i] = str[i];
	}
	s[i] = '\0';
	return (s);
}

/**
 * _getline - Read a line from a file stream
 * @lineptr: the address of pointer to char
 * @n: The size of lineptr
 * @stream: File stream
 *
 * Return: Number of bytes read from stream
 */

ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	int b_read, b_read_tmp = 0, fd;
	ssize_t bytes = 0;

	fd = stream->_fileno;
	fflush(stdout);
	if (*lineptr == NULL && *n == 0)
	{
		*lineptr = malloc(sizeof(char) * BUF_SIZE);
		*n = BUF_SIZE;
		if (*lineptr == NULL)
		{
			return (-1);
		}
	}
	b_read = read(fd, *lineptr, *n);
	if (b_read == 0)
		return (-1);
	if (b_read < (int) *n)
	{
		*(*lineptr + b_read) = '\0';
		bytes = b_read;
		return (bytes);
	}
	else if (b_read == (int) *n)
	{
		while (b_read == BUF_SIZE)
		{
			b_read_tmp += b_read;
			*lineptr = _realloc(*lineptr, b_read_tmp, (b_read_tmp + BUF_SIZE));
			if (*lineptr == NULL)
				return (-1);
			b_read = read(fd, *lineptr + b_read_tmp, BUF_SIZE);
		}
		b_read_tmp += b_read;
		*(*lineptr + b_read_tmp) = '\0';
		bytes = b_read_tmp;
		return (bytes);
	}
	return (bytes);
}
