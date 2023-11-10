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
