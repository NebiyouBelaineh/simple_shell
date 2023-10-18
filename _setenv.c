#include "main.h"

int _setenv(char *name, char *value, int overwrite);
/**
 * _setenv - adds env variable if it does not exist.
 * @name: name of the enviornment variable to add
 * @value: value of teh enviornment variable to add
 * @overwrite: condition to overwrite exisiting enviornment variable.
 * if non-zero, overwrites, other wise does nothing.
 * Return: 0 for success, -1 for error
 */
int _setenv(char *name, char *value, int overwrite)
{
	char *new_env, *env_var;
	unsigned int index = 0;

	if (name == NULL || _strlen(name) == 0 || _strpbrk(name, "=") != NULL)
	{
		errno =  EINVAL;
		perror("Error");
		return (-1);
	}

	env_var = _getenv(name);
	if (env_var != NULL) /*Case where the environment variable exisits*/
	{
		if (overwrite != 0)
		{
			while (__environ[index] != NULL)
			{
				if (_strstr(__environ[index], env_var) != NULL)
				{
					new_env = str_concat(name, "=", value);
					_strcpy(__environ[index], new_env);
					free(new_env);
				}
				index++;
			}
		}
		free(env_var);
		return (0);
	}
	/*Case where the environment variable does not exist*/
	index = 0;
	while (__environ[index] != NULL)
		index++;
	new_env = str_concat(name, "=", value);
	__environ[index] = malloc(_strlen(new_env) + 1);
	if (__environ[index] == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (-1);
	}
	_strcpy(__environ[index], new_env);
	__environ[index + 1] = NULL;
	free(new_env);
	free(env_var);

	return (0);
}
