#include "main.h"

/**
 * _strtok - Replica of strtok function
 * @str: pointer to string
 * @delim: pointer to set of character
 *
 * Return: pointer to start of the string before delim
 */

char *_strtok(char *str, const char *delim)
{
	static char *str_cpy = (char *) 0;
	char *tmp;

	if (str != NULL)
	{
		str_cpy = str;
	}
	tmp = str_cpy;
	while (*str_cpy != '\0')
	{
		if (*str_cpy == *delim)
		{
			*str_cpy = '\0';
			str_cpy++;
			return (tmp);
		}
		else
		{
			str_cpy++;
		}
	}
	if (*tmp != '\0')
	{
		return (tmp);
	}
	return (NULL);
}

/**
 * exit_shell - Exit the shell with a given status if provided
 * @argv: List of argument
 * @buf: pointer to the buffer to be freed
 *
 * Return: Nothing
 */

void exit_shell(char **argv, char *buf)
{
	int status;

	if (argv[1] != NULL)
	{
		status = _atoi(argv[1]);
		free(buf);
		free(argv);
		exit(status);
	}
	exit(0);
}

/**
 * _atoi - convert string to an integer
 * @s: pointer to string
 * Return: integer of the string
 */

int _atoi(char *s)
{
	int i, digit;
	int check = 0;
	int sign = 1;
	unsigned int res = 0;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == '-')
		{
			sign *= -1;
		}
		if (s[i] >= '0' && s[i] <= '9')
		{
			digit = s[i] - '0';
			res = res * 10 + digit;
			check++;
			if (s[i + 1] < '0' || s[i + 1] > '9')
			{
				break;
			}
		}
	}
	if (check == 0)
	{
		return (0);
	}
	return (res * sign);
}
