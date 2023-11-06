#ifndef MAIN_H
#define MAIN_H

#define UNUSED __attribute__((unused))

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int _strlen(char *s);
int new_line_check(char *s);
char **create_list_of_arg(char *buf);
void *_memcpy(char *dest, char *src, unsigned int n);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void free_list(char **argv);
void execve_error(char **av, char **argv, char *buf);
int _strcmp(char *s1, char *s2);
void printenv(char **env);

#endif
