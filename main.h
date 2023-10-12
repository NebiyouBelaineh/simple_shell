#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define ARG_MAX 1000

/*Environment Variable*/
extern char **__environ;

int tokenize_input(char *str, char *arr_token[], int *index_ptr);
/* int execute_commands(char *arr_token[], int *index_ptr, char *p_name); */
int execute_commands(char *arr_token[], int *index_ptr, char *p_name,
int *line_counter);
ssize_t _getline(char **lineptr, size_t *length, FILE *stream);
size_t _getline_support(size_t *length, char buff[], char **lineptr);

/*Printing functions*/
void print_to_terminal(char *str);
int print_num(char c);
void print_number(int n);

void handle_errors(char *p_name, int *line_counter, char *command);
char *find_command(char *command);
void free_mem(int *index_ptr, char **ptr);
int _isexit(char **arr_token, int *index_ptr, char *p_name,
int *line_counter);

int _atoi(char *s);
int _isdigit(int c);
int _is_number(char *str);


/*Environment variable functions*/
char *_getenv(char *name);
void _printenv(void);


/*String Manuplilation custom functions*/
char *_strcpy(char *dest, char *src);
char *_strdup(char *str);
unsigned int _strspn(char *s, char *accept);
char *_strpbrk(char *s, char *accept);
char *_strstr(char *haystack, char *needle);
int _strcmp(char *s1, char *s2);
int _strlen(char *s);
char *_strtok(char *str, const char *delimiters);
unsigned int _strcspn(char *s, char *reject);
char *str_concat(char *s1, char *s2, char *s3);

#endif/*MAIN_H*/
