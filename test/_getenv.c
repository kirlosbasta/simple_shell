#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct list_t
{
	char *str;
	struct list_t *next;
} list_t;

char *_strcpy(char *dest, char *src);
int _strlen(const char *s);
char *_getenv(const char *name, char **environ);
void print_path(char *path);
char *_strdup(const char *str);
list_t *add_node_end(list_t **head, const char *str);
char *str_concat(char *s1, char *s2);

/**
 * _getenv - get the value of enviroment name
 * @name: pointer to the name of the varible
 * @environ: Enviromental variavles
 *
 * Return: pointer to the value in success or NULL in failure 
 */

char *_getenv(const char *name, char **environ)
{
	char *value;
	int i, j;

	for (i = 0; environ[i] != NULL; i++)
	{
		for (j = 0; name[j] != '\0'; j++)
		{
			if (name[j] != environ[i][j])
			{
				break;
			}
		}
		if (name[j] == '\0')
		{
			value = environ[i] + j + 1;
			return (value);
		}
	}
	return (NULL);
}

/**
 * print_path - Print the direcatory of the PATH
 * @path: pointer to the value of the path
 *
 * Return: Nothing
 */

void print_path(char *path)
{
	char *path_cpy, *dir;

	path_cpy = malloc(sizeof(char) * (_strlen(path) + 1));
	path_cpy = _strcpy(path_cpy, path);
	dir = strtok(path_cpy, ":");
	printf("%s\n", dir);
	while (dir != NULL)
	{
		dir = strtok(NULL, ":");
		if (dir != NULL)
		{
			printf("%s\n", dir);
		}
	}
	free(path_cpy);
}

/**
 * path_linked_list - Create a linked list for all directory in the PATH
 * @path: Path
 *
 * Return: Pointer to the head of the list
 */

list_t *path_linked_list(char *path)
{
	char *path_dup = _strdup(path);
	char *dir;
	list_t *head;

	dir = strtok(path_dup, ":");
	head = NULL;
	add_node_end(&head, dir);
	while (dir != NULL)
	{
		dir = strtok(NULL, ":");
		if (dir != NULL)
		{
			add_node_end(&head, dir);
		}
	}
	free(path_dup);
	return (head);
}

/**
 * _strlen - Count the length of string
 * @s: Pointer to string
 *
 * Return: The length of the string
 */

int _strlen(const char *s)
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
/**
 * _strdup - return a copy of a string to newly allocated space in memory
 * @str: pointer to string
 *
 * Return: Pointer of the duplicated string in success
 * and NULL if insufficient memory was available
 */

char *_strdup(const char *str)
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
 * add_node_end - Add str and it's length to a list
 * @head: The address of the head
 * @str: String to be added to the new node
 *
 * Return: pointer to the new node
 */

list_t *add_node_end(list_t **head, const char *str)
{
	list_t *node = malloc(sizeof(list_t));
	list_t *current = *head;
	char *dup_str;

	if (node == NULL)
	{
		return (NULL);
	}
	dup_str = _strdup(str);
	if (dup_str == NULL)
	{
		free(node);
		return (NULL);
	}
	node->str = dup_str;
	if (current == NULL)
	{
		*head = node;
		node->next = NULL;
		return (node);
	}
	node->next = NULL;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = node;
	return (node);
}

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

char *_setenv_helper(char *name, char *value)
{
	char *new_var;
	int name_len, value_len;

	if (name_value_check((char *)name, (char *)value))
		return (NULL);
	name_len = _strlen((char *)name);
	value_len = _strlen((char *) value);
	new_var = malloc(sizeof(char) * (name_len + value_len + 2));
	if (new_var == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	return (new_var);
}

/**
 * _setenv - set a vairable to the enviroment
 * @name: Name of the vairable
 * @value: the value to be assigined to the name
 * @overwrite: 0 to indicate that if a variable exist don't change it's value
 * and nonezero to overwrite
 *
 * Return: 0 on success and 1 on failure
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
 * _printenv - Print the enviroment variable
 *
 * Return: Nothing
 */

void _printenv(void)
{
	extern char **environ;
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		printf("%s\n", environ[i]);
	}
}

/**
 * command_exist - Check if a command exist and is executable
 * @name: Name of the command
 * @environ: Enviromental variables
 *
 * Return: pointer to pathname or NULL
 */

char *command_exist(char **environ)
{
	char *path = _getenv("PATH", environ);
	char *command = "/ls", *dir;
	list_t *head = path_linked_list(path);
	list_t *current = head;

	while (current != NULL)
	{
		dir = str_concat(current->str, command);
		if (access(dir, X_OK) == 0)
		{
			return (dir);
		}
		free(dir);
		current = current->next;
	}
	return (NULL);
}

int main(void)
{
	extern char **environ;

	_setenv("KOKO", "COOL", 1, environ);
	_printenv();
	free(*environ);
	return (0);
}