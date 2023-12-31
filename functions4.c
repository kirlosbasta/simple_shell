#include "main.h"

/**
 * str_concat - concatenates two strings
 * @s1: pointer to string
 * @s2: pointer to string
 *
 * Return: pointer to the concatenated string in success
 * and NULL on failure
 */

char *str_concat(char *s1, char *s2)
{
	int len1, len2, i = 0, j = 0;
	char *s;

	len1 = _strlen(s1);
	len2 = _strlen(s2);
	s = malloc(sizeof(char) * (len1 + len2 + 1));
	if (s == NULL)
	{
		return (NULL);
	}
	if (len1 != 0)
	{
		for (i = 0; s1[i] != 0; i++)
		{
			s[i] = s1[i];
		}
	}
	if (len2 != 0)
	{
		for (j = 0; s2[j] != 0; j++, i++)
		{
			s[i] = s2[j];
		}
	}
	s[i] = '\0';
	return (s);
}

/**
 * _unsetenv - unset an enviromental variable
 * @name: Name of the variable
 * @environ: enviroment variables
 *
 * Return: 0 on success and -1 on failure
 */

int _unsetenv(char *name, char **environ)
{
	char **env_ptr;

	if (name == NULL)
	{
		return (-1);
	}
	env_ptr = var_name_check(name, environ);
	if (env_ptr == NULL)
	{
		return (0);
	}
	else
	{
		while (*env_ptr != NULL)
		{
			*env_ptr = *(env_ptr + 1);
			env_ptr++;
		}
		return (0);
	}

}

/**
 * var_name_check - check if a name exist inside environ
 * @name: Name of the variable
 * @environ: List of variables
 *
 * Return: pointer to the enviromenal variable in success or null not found
 */

char **var_name_check(char *name, char **environ)
{
	int i, j;

	for (i = 0; environ[i] != NULL; i++)
	{
		for (j = 0; name != NULL; j++)
		{
			if (name[j] != environ[i][j])
			{
				break;
			}
		}
		if (name[j] == '\0')
		{
			return (&environ[i]);
		}
	}
	return (NULL);
}

/**
 * name_value_check - check if the name and value of setenv is valid
 * @name: Name of the variable
 * @value: Name's value
 *
 * Return: 0 if valid and 1 if not
 */

int name_value_check(char *name, char *value)
{
	if (name == NULL || value == NULL)
	{
		perror("usage setenv VARIABLE VALUE");
		return (1);
	}
	if (check_delim((char *) name, "="))
	{
		perror("The name sould not contain = sign");
		return (1);
	}
	else
	{
		return (0);
	}

}

/**
 * check_builtin - Check if the command called is a builtin command and execute
 * @var: pointer to struct contain collection of variables
 *
 * Return: 1 if it's builtin and 0 if not
 */

int check_builtin(var_inf *var)
{
	if (*var->argv == NULL)
	{
		free(var->argv);
		return (1);
	}
	if (_strcmp("exit", var->argv[0]) == 0)
	{
		exit_shell(var);
		return (1);
	}
	if (_strcmp("setenv", var->argv[0]) == 0)
	{
		var->head = _setenv(var->argv[1], var->argv[2], 1, var->environ, &var->head);
		free(var->argv);
		return (1);
	}
	if (_strcmp("unsetenv", var->argv[0]) == 0)
	{
		_unsetenv(var->argv[1], var->environ);
		free(var->argv);
		return (1);
	}
	if (_strcmp("env", var->argv[0]) == 0)
	{
		printenv(var->environ);
		free(var->argv);
		return (1);
	}
	if (_strcmp("cd", var->argv[0]) == 0)
	{
		cd(var);
		free(var->argv);
		return (1);
	}
	return (0);
}
