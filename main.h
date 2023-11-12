#ifndef MAIN_H
#define MAIN_H

#define UNUSED __attribute__((unused))
#define BUF_SIZE 1024

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

/**
 * struct list_t - Nodes for a singly linked list
 * @str: pointer to char
 * @next: pointer to next node
 */

typedef struct list_t
{
	char *str;
	struct list_t *next;
} list_t;

int _strlen(char *s);
int check_delim(char *s, char *delim);
char **create_list_of_arg(char *buf);
void *_memcpy(char *dest, char *src, unsigned int n);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void free_list(char **argv);
void execve_error(char **av, char **argv, char *buf);
int _strcmp(char *s1, char *s2);
char *_strdup(char *str);
char *_strcpy(char *dest, char *src);
char *str_concat(char *s1, char *s2);
void printenv(char **env);
char *_setenv(const char *name, const char *value, int overwrite,
char **environ);
int _unsetenv(char *name, char **environ);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
char *_strtok(char *str, const char *delim);
int _atoi(char *s);
void exit_shell(char **argv, char *buf, char *env_var, int read);
char **var_name_check(char *name, char **environ);
int name_value_check(char *name, char *value);
int check_builtin(char **argv,  char *buf, char *env_var,
					char **environ, int read);
char *command_exist(char *name, char **environ);
list_t *add_node_end(list_t **head, const char *str);
list_t *path_linked_list(char *path);
char *_getenv(const char *name, char **environ);

#endif
