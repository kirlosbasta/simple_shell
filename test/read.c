#include "main.h"

int main(void)
{
	char *buf = NULL;
	size_t n = 0;
	ssize_t bytes;

	bytes = _getline(&buf, &n, stdin);
	printf("string read: %ssize: %lu\n", buf, bytes);
	return (0);
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
#define BUF_SIZE 1024
	int b_read, b_read_tmp = 0, old_size = *n, fd;
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
	old_size = *n;
	b_read = read(fd, *lineptr, *n);
	if (b_read < old_size)
	{
		*(*lineptr + b_read) = '\0';
		bytes = b_read;
		return (bytes);
	}
	else if (b_read == old_size)
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
