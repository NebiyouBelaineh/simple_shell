#include "main.h"

/**
 * tokenize_by_delim - takes user input and breaks down the arguments into
 * tokens using delim
 * @str: string entered into the shell prompt
 * @arr_token: an array of strings to contain each token string
 * @index_ptr: pointer to the index used for arr_token
 * @delim: the delimiter string we use to break str to tokens
 * Return: the string separated by the delimiter
 */

int tokenize_by_delim(char *str, char *arr_token[], int *index_ptr,
char *delim)
{
	int index = 0;
	char *token;

	if (str[0] == '\n')
		return (1);
	token = _strtok(str, delim);
	while (token != NULL) /**/
	{
		arr_token[index] = malloc((_strlen(token) * sizeof(char)) + 1);
		if (arr_token[index] == NULL)
		{
			perror("Error: malloc:");
			for (index = 0; index < *index_ptr; index++)
			{
				free(arr_token[index]);
				arr_token[index] = NULL;
			}
			free(str);
		}
		_strcpy(arr_token[index], token);
		token = _strtok(NULL, delim);
		*index_ptr = index;
		index++;
	}
	arr_token[index] = NULL;
	*index_ptr = index;
	return (0);
}
