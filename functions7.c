#include "main.h"

/**
 * check_char - check if a string conatian any charcter
 * @s: pointer to string
 *
 * Return: 0 if no character found and 1 on failure
 */

int check_char(char *s)
{
	int i;

	for (i = 0; s[i] != '\0'; i++)
	{
		if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
		{
			return (1);
		}
	}
	return (0);
}
