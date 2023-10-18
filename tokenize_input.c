#include "main.h"

/**
 * tokenize_input - takes user input and breaks down the arguments into
 * tokens
 *
 * @line: string entered into the shell prompt
 * @arr_token: an array of strings to contain each token string
 * @index_ptr: pointer to the index used for arr_token
 * Return: 0 for success, 1 for error
 */

int tokenize_input(char *line, char *arr_token[], int *index_ptr)
{
	int index;
	char *token, *delimiter = " \t";

	if (line[0] == '\n')
		return (1);
	if (_is_space(line))
		return (1);
	if (line[0] == '#')
		return (1);
	token = _strtok(line, delimiter);
	for (index = 0; token != NULL; index++)
	{
		/*Handles comments*/
		if (_strcmp(token, "#") == 0)
			break;
		arr_token[index] = malloc((_strlen(token) * sizeof(char)) + 1);
		if (arr_token[index] == NULL)
		{
			errno = ENOMEM;
			perror("Error");
			free_mem(index_ptr, arr_token);
			free(line);
			exit(EXIT_FAILURE);
		}
		_strcpy(arr_token[index], token);
		*index_ptr = index;
		token = _strtok(NULL, delimiter);
	}
	arr_token[index] = NULL;
	*index_ptr = index;
	return (0);
}

/**
 * _is_space - checks if string is filled with space only
 * @str: string to be checked
 * Return: 0 if not all spaces, 1 otherwise
*/
int _is_space(char *str)
{
	int index = 0;

	while (str[index] != '\0')
	{
		if (str[index] != ' ' && str[index] != '\t')
			return (0);
		index++;
	}
	return (1);
}
