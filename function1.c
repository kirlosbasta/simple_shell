#include "main.h"

/**
 * _strlen - Count the length of string
 * @s: Pointer to string
 *
 * Return: The length of the string
 */

int _strlen(char *s)
{
	int len = 0, i = 0;

	while (s[i])
	{
		len++;
		i++;
	}
	return (len);
}

/**
 * check_delim -  check if a string conatin delim
 * @s: pointer to string
 * @delim: pointer to the character to search for
 *
 * Return: i if it contain new line and 0 if it doesn't
 */

int check_delim(char *s, char *delim)
{
	int i;

	if (s == NULL || delim == NULL)
	{
		return (0);
	}
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == *delim)
		{
			return (1);
		}
	}
	return (0);
}

/**
 * create_list_of_arg - Create list of arguments
 * @buf: Buffer containing a string of argument
 *
 * Description: Seperate each word into a seperate string and add to the list
 * Return: List of pointers
 */

char **create_list_of_arg(char *buf)
{
	int i, count = 1, j = 1;
	unsigned int basic = sizeof(char *) * 10;
	char **argv = malloc(basic);

	if (argv == NULL)
	{
		return (NULL);
	}
	i = 0;
	argv[i] = strtok(buf, " ");
	while (argv[i] != NULL)
	{
		if (count > 9)
		{
			argv = _realloc(argv, basic, sizeof(char *) * (10 + j));
			j++;
		}
		if (check_delim(argv[i], "\n") == 1)
		{
			argv[i] = strtok(argv[i], "\n");

		}
		i++;
		argv[i] = strtok(NULL, " ");
		count++;
	}
	return (argv);
}

/**
 * _realloc - reallocates a memory block
 * @ptr: pointer to the old memory
 * @old_size: The old memory size
 * @new_size: The new memory size
 *
 * Return: pointer to the new memory block in success or null in failure
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *new_ptr = NULL;

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
	{
		return (ptr);
	}
	if (ptr == NULL)
	{
		new_ptr = malloc(new_size);
		return (new_ptr);
	}

	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
	{
		return (NULL);
	}
	_memcpy(new_ptr, ptr, old_size);
	free(ptr);
	return (new_ptr);
}

/**
 * _memcpy - copies the memory area from src to dest until n is reached
 * @dest: pointer to the destination pointer
 * @src: pointer to sourc pointer
 * @n: The size of bytes to copy from src
 *
 * Return: pointer to dest
 */

void *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		*(dest + i) = *(src + i);
	}
	*(dest + i) = '\0';
	return (dest);
}
