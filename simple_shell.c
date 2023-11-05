#include "main.h"

/**
 * main - Entry for simple_shell
 * 
 * @return int 
 */
int main(void)
{
	extern char **environ;
	int read, status;
	size_t n = 0;
	char *buf = NULL;
	char *argv[2];
	pid_t child_pid;

	while (1)
	{
		write(STDOUT_FILENO, "#cisfun$ ", 10);
		read = getline(&buf, &n, stdin);
		if (read == -1)
		{
			perror("Getline Error\n");
		}
		argv[0] = strtok(buf, "\n");
		argv[1] = NULL;
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Fork Error\n");
		}
		if (child_pid == 0)
		{
			if (execve(argv[0], argv, environ) == -1)
			{
				perror("Execve Error");
			}
		}
		else
		{
			wait(&status);
		}
	}
	return (0);
}
