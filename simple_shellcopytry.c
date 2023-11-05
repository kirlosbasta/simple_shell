#include "main.h"

/*
 *main - Entry point to the shell
 *
 *
 *Return 0 if no error
 */

int main()
{
	extern char **environ;
	int read, status;
	size_t n = 0;
	size_t size=1;
	char *buf = NULL;
	char *line=NULL;
	char **argv=(char**)malloc(sizeof(char*));
	pid_t child_pid;

	while (1)
	{
		write(STDOUT_FILENO, "#cisfun$ ", 10);
		read = getline(&buf, &n, stdin);
		if (read == -1)
		{
			perror("Getline Error");
			break;
		}
		else if (read > 1)
		{
			argv[0]=strdup(strtok(buf, " "));
			while(buf != NULL)
			{	
				argv=(char**)realloc(argv,(size+1)*sizeof(char*));
				line= strtok(NULL, " \n");

				argv[size]=strdup(line);
				size++;
			}
			argv[size]=NULL;

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
	}
	return (0);
}
