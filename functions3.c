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
 * @env_var: pointer to allocated memory in setenv
 * @read: the result of read function
 *
 * Return: Nothing
 */

void exit_shell(char **argv, char *buf, char *env_var, int read)
{
	int status;

	if (env_var != NULL)
		free(env_var);
	if (isatty(0) && read == -1)
		write(STDOUT_FILENO, "\n", 2);
	if (read != -1 && argv[1] != NULL)
	{
		status = _atoi(argv[1]);
		free(buf);
		free(argv);
		exit(status);
	}
	free(argv);
	free(buf);
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

/**
 * _setenv - set a vairable to the enviroment
 * @name: Name of the vairable
 * @value: the value to be assigined to the name
 * @overwrite: 0 to indicate that if a variable exist don't change it's value
 * and nonezero to overwrite
 * @environ: List of enviromental variable
 *
 * Return: pointer to the allocated memory in succes and NULL in failure
 */

char *_setenv(const char *name, const char *value, int overwrite,
			char **environ)
{
	char *new_var, *tmp;
	int i, j;

	new_var = _setenv_helper((char *) name, (char *) value);
	if (new_var == NULL)
		return (NULL);
	new_var = _strcpy(new_var, (char *) name);
	tmp = str_concat(new_var, "=");
	free(new_var);
	new_var = str_concat(tmp, (char *) value);
	free(tmp);
	for (i = 0; environ[i] != NULL; i++)
	{
		for (j = 0; new_var[j] != '='; j++)
		{
			if (environ[i][j] != new_var[j])
				break;
		}
		if (new_var[j] == '=')
		{
			if (overwrite != 0)
			{
				environ[i] = new_var;
				return (new_var);
			}
			else
			{
				free(new_var);
				return (NULL);
			}
		}
	}
	environ[i] = new_var;
	environ[i + 1] = NULL;
	return (new_var);
}

/**
 * *_strcpy - copy the content of src to dest
 * @dest: pointer to the destination
 * @src: pointer to source
 * Return: Pointer to dest
 */

char *_strcpy(char *dest, char *src)
{
	char *destptr = dest;
	char *srcptr = src;

	while (*srcptr != '\0')
	{
		*destptr = *srcptr;
		destptr++;
		srcptr++;
	}
	*destptr = '\0';
	return (dest);
}
