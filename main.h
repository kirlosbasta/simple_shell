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
 * @argv: pointer to pointer to char
 * @logic: int
 * @next: pointer to next node
 */

typedef struct list_t
{
	char *str;
	char **argv;
	int logic;
	struct list_t *next;
} list_t;

/**
 * struct var_inf - Collection of variables needed
 *
 * @buf: Buffer that holds the input
 * @argv: List of argument
 * @av: Command line argument
 * @dir: Path to command
 * @environ: Enviromental variables
 * @count: Number of command so far
 * @head: list of allocated memory by setenv and cd
 * @read: Number of bytes read by read
 * @status: Exit status of the child proccess
 */

typedef struct var_inf
{
	char *buf;
	char **argv;
	char **av;
	char *dir;
	char **environ;
	int count;
	list_t *head;
	int read;
	int *status;
} var_inf;


int _strlen(char *s);
int check_delim(char *s, char *delim);
char **create_list_of_arg(char *buf);
void *_memcpy(char *dest, char *src, unsigned int n);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void free_list(char **argv);
void execve_error(var_inf *var, char *str);
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
void exit_shell(var_inf *var);
char **var_name_check(char *name, char **environ);
int name_value_check(char *name, char *value);
int check_builtin(var_inf *var);
int fork_child(var_inf *var);
char *command_exist(char *name, char **environ);
list_t *add_node_end(list_t **head, const char *str);
list_t *add_node(list_t **head, const char *str);
list_t *path_linked_list(char *path);
char *_getenv(const char *name, char **environ);
void free_single_list(list_t *head);
char *_setenv_helper(char *name, char *value);
int cd(var_inf *var);
int check_comment(char **argv);
void rev_string(char *s);
char *num_to_str(int num);
int check_char(char *s);
list_t *add_node_end_argv(list_t **head, char **str);
int check_semicolon(var_inf *var);
void free_single_list_argv(list_t *head);
int length_argv(char **argv);
void shiftToRight(char **argv);
void copy_list(char **old, char **new);
void arrange_argv(var_inf *var, char *delim);
void print_list(char **argv);
list_t *add_node_end_argv_int(list_t **head, char **str, int logical);
int check_logical(var_inf *var);
void semicolon_wrapper(var_inf *var, list_t *head);
void logical_wrapper(var_inf *var, list_t *head);
list_t *variable_repalcement(var_inf *var);
int checks(var_inf *var);

#endif
