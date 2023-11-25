#include "main.h"

/**
 * length_argv - Length of argument in argv
 * @argv: List of argument
 *
 * Return: Number of argument
 */

int length_argv(char **argv)
{
	int i = 0;

	while (argv[i] != NULL)
	{
		i++;
	}
	return (i + 1);
}

/**
 * shiftToRight - shitf a list to the right
 * @argv: pointer to the list
 *
 * Return: Nothing
 */

void shiftToRight(char **argv)
{
	int i = 0;

	while (argv[i] != NULL)
	{
		i++;
	}
	for (; argv[i] != *argv; i--)
	{
		argv[i + 1] = argv[i];
	}
}

/**
 * copy_list - copy list from one to another
 * @old: old list
 * @new: new list
 *
 * Return: Nothing
 */
void copy_list(char **old, char **new)
{
	while (*old != NULL)
	{
		*new = *old;
		new++;
		old++;
	}
	*new = NULL;
}
/**
 * print_list - print list of argument
 * @argv: list of argument
 *
 * Return: Nothing
 */

void print_list(char **argv)
{
	int i;

	for (i = 0; argv[i] != NULL; i++)
	{
		printf("%s ", argv[i]);
	}
	printf("\nlength = %d\n", i + 1);
}
