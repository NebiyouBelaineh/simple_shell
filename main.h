#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

#include <fcntl.h>

#define OVERWRITE 1
#define PATH "PATH"
#define HOME "/home"

/**
 * struct alias - structure for alias
 * @name: the name of the aliases
 * @value: the value of the aliases
 */
typedef struct alias
{
	char *name;
	char *value;
} alias_t;

/*Environment Variable*/
extern char **__environ;

int tokenize_input(char *str, char *arr_token[], int *index_ptr);

int execute_commands(char *arr_token[], int *index_ptr, char *p_name,
					 int *line_counter, int *exit_ptr);
int execute_process(char *arr_token[], int *index_ptr, char *p_name,
					int *line_counter, int *exit_ptr);

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

int _setenv(char *name, char *value, int overwrite);
int _unsetenv(char *name);

/*String Manuplilation custom functions*/
char *_strcpy(char *dest, char *src);
char *_strdup(char *str);
unsigned int _strspn(char *s, char *accept);
char *_strpbrk(char *s, const char *accept);
char *_strstr(char *haystack, char *needle);
int _strcmp(char *s1, char *s2);
int _strlen(char *s);
char *_strtok(char *str, char *delimiters);
unsigned int _strcspn(char *s, char *reject);
char *str_concat(char *s1, char *s2, char *s3);
int _strncmp(char *s1, char *s2, int n);

int cmd_separator(char *line, char *p_name, int *line_countptr, int *exit_ptr);
int handle_logical_and(char *line, char *p_name, int *line_countptr,
int *exit_ptr);
int handle_logical_or(char *line, char *p_name, int *line_countptr,
int *exit_ptr);
int support_logical_and(char *command[], char *p_name, int *line_countptr,
int *exit_ptr);
int support_logical_or(char *command[], char *p_name, int *line_countptr,
int *exit_ptr);
void support_command_sep(char *command[], char *p_name, int *line_countptr,
int *exit_ptr);

int _is_space(char *str);
int _is_cd(char **arr_token);

void handle_EOF(char *line, int env_count);

void handle_syntax_errors(char *p_name, int *line_counter, char *syntax);
int _is_semi_colons(char *str);

/* functions to handle alias */
int is_alias(char **arr_token);
void print_alias_by_name(char **arr_token, alias_t *aliases);
void def_alias(char *name, char *value, alias_t *aliases, int *count_alias);
void prints_aliases(alias_t *aliases);

void free_mem_exec(char **arr_token, int *index_ptr, int flag_command,
char *command_path);

int tokenize_by_delim(char *str, char *arr_token[], int *index_ptr,
					  char *delim);
int handle_file(char *filename, char **arr_token, int *index_ptr, char *p_name,
int *line_countptr, int *exit_ptr);
void _getppid(void);
int handle_var_rp(char **arr_token, int *exit_ptr);
char *num_to_string(int number);
void support_var_rp(char **arr_token, int index);


size_t _getline_support(size_t *length, char buff[],
char **lineptr);
int _fileno(FILE *stream);

#endif /*MAIN_H*/
