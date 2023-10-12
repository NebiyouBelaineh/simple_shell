#include "main.h"

/**
* _getenv - gets the enviorment variable required without using getenv()
* function
* @name: name of enviornment variable we want to find
* Return: Enviorment variable key=value string or NULL if it does not exist.
*/
char *_getenv(char *name)
{
	unsigned int index = 0;
	char *token, *temp, *result;

	if (name == NULL)
		return (NULL);

	while (__environ[index] != NULL)
	{
		temp = malloc(_strlen(__environ[index]) + 1);
		_strcpy(temp, __environ[index]);
		token = _strtok(temp, "=");

		if (_strcmp(token, name) == 0)
		{
			token = _strtok(NULL, "=");
			result = malloc(_strlen(token) + 1);
			_strcpy(result, token);
			free(temp);
			return (result);
		}
		index++;
		free(temp);
	}

	return (NULL);
}
