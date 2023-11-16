#include "main.h"

/**
 * remove_space - Removes space in the begining of string if found
 * @buf : the table of characters in question
 */

void remove_space(char buf[])
{
	if (buf[0] == ' ')
	{
		for (int i=1; buf[i] != '\0'; i++)
		{
			buf[i] = buf[i-1];
		}
	}
}

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
	int read, count = 0;
	size_t n = 0;
	char *buf = NULL, **argv = NULL, *dir, **multi_buf = NULL;
	list_t *head = NULL;
	int a = 0, b = 0, c = 0;
	char x=NULL;

	while (1)
	{
		count++;
		argv = NULL;
		if (isatty(0))
			write(STDOUT_FILENO, "$ ", 3);
		read = getline(&buf, &n, stdin);
		if (read == -1)
			exit_shell(argv, buf, &head, read);
		if (read > 1)
		{
			a = check_delim(buf, "&");
			b = check_delim(buf, "||");
			c = check_delim(buf, ";");
			if ( a || b || c)
			{
				if ( a != 0)
					x = '&';
				if ( b != 0)
					x = '|';
				if (c != 0)
					x = ';';
				multi_buf = _strtok(buf , x);
				while (multi_buf)
				{
					remove_space(multi_buf);
					argv = create_list_of_arg(multi_buf);
					check_comment(argv);
					if (check_builtin(argv, multi_buf, &head, environ, read, av):
						continue;
					dir = command_exist(argv[0], environ);
					if (dir == NULL)
					{
						execve_error(av, argv, multi_buf, dir, count);
						continue;
					}
					fork_child(dir, argv, environ, av, multi_buf, count);
					multi_buf = _strtok(NULL, x);
				}
			}
			argv = create_list_of_arg(buf);
			check_comment(argv);
			if (check_builtin(argv, buf, &head, environ, read, av))
				continue;
			dir = command_exist(argv[0], environ);
			if (dir == NULL)
			{
				execve_error(av, argv, buf, dir, count);
				continue;
			}
			fork_child(dir, argv, environ, av, buf, count);
		}
	}
	return (0);
}
