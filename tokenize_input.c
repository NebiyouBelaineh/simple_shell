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
	char *token;

	if (line[0] == '\n' || line[0] == '\0')
	{
		free(line);
		return (1);
	}
	line[_strcspn(line, "\n")] = 0;

	if ((_strcmp(line, "env") == 0) && (_strlen(line) == _strlen("env")))
	{
		_printenv();
		free(line);
		return (1);
	}
	else if ((_strcmp(line, "exit") == 0)  && (_strlen(line) == _strlen("exit")))
	{
		free(line);
		exit(EXIT_SUCCESS);
	}
	token = _strtok(line, " ");
	for (index = 0; token != NULL; index++)
	{
		arr_token[index] = malloc((_strlen(token) * sizeof(char)) + 1);
		if (arr_token[index] == NULL)
		{
			perror("Error: malloc:");
			free_mem(index_ptr, arr_token);
			free(line);
			exit(EXIT_FAILURE);
		}
		_strcpy(arr_token[index], token);
		token = _strtok(NULL, " ");
		*index_ptr = index;
	}
	arr_token[index] = NULL;
	*index_ptr = index;
	free(line);
	return (0);
}
