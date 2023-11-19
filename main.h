#ifndef MAIN_H
#define MAIN_H

#define UNUSED __attribute__((unused))
#define BUF_SIZE 1024

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
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
void execve_error(char **av, char **argv, char *buf, char *dir, int count);
int _strcmp(char *s1, char *s2);
char *_strdup(char *str);
char *_strcpy(char *dest, char *src);
char *str_concat(char *s1, char *s2);
void printenv(char **env);
list_t *_setenv(const char *name, const char *value, int overwrite,
char **environ, list_t **head);
int _unsetenv(char *name, char **environ);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
char *_strtok(char *str, const char *delim);
int _atoi(char *s);
void exit_shell(char **argv, char *buf, list_t **env_var,
				int read, int *status);
char **var_name_check(char *name, char **environ);
int name_value_check(char *name, char *value);
int check_builtin(char **argv,  char *buf, list_t **head,
					char **environ, int read, char **av, int *status);
int fork_child(char *dir, char **argv, char **environ, char **av,
				char *buf, int count, int *status);
char *command_exist(char *name, char **environ);
list_t *add_node_end(list_t **head, const char *str);
list_t *add_node(list_t **head, const char *str);
list_t *path_linked_list(char *path);
char *_getenv(const char *name, char **environ);
void free_single_list(list_t *head);
char *_setenv_helper(char *name, char *value);
int cd(char **argv, char **environ, char **av, list_t **head);
int check_comment(char **argv);

#endif
