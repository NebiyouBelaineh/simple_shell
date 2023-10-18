#include "main.h"

/**
 * _unsetenv - deletes the variable name from the enviornment variables
 * @name: name of the enviornment variable we want to deleter
 * Return: 0 for success(when it deletes the name or can not find it), -1
 * for error
 */
int _unsetenv(char *name)
{
	unsigned int index, index2;

	if (name == NULL || _strlen(name) == 0 || _strpbrk(name, "="))
	{
		errno =  EINVAL;
		perror("Error");
		return (-1);
	}

	for (index = 0; __environ[index] != NULL; index++)
	{
		if (_strcmp(__environ[index], name) == 0)
		{
			for (index2 = index; __environ[index2 + 1] != NULL; index2++)
				__environ[index2] = __environ[index2 + 1];
			/* free(__environ[index2]); */ /*needed for newly set env_vars*/
			__environ[index2] = NULL;
			return (0);
		}
	}
	return (0);
}
