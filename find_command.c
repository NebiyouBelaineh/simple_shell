#include "main.h"

/**
 * find_command - looks for commands in the PATH directory
 * @command: command string to be searched in PATH
 * Return: full path name if found, otherwise command itself
 */
char *find_command(char *command)
{
	unsigned int index = 0 /* , found_flag = 0 */;
	struct stat st;
	char *path_dir, *path_var, *token;

	if (stat(command, &st) == 0)
	{
		return (command);
	}
	if (command[0] == '.' && command[1] == '/')
		return (NULL);
	/*if not full path command, execute the below*/
	path_var = _getenv(PATH);
	token = _strtok(path_var, ":");

	while (token != NULL)
	{
		path_dir = str_concat(token, "/", command);
		/*if it finds the command, it will free path_var and return*/
		if (stat(path_dir, &st) == 0)
		{
			free(path_var);
			return (path_dir);
		}
		free(path_dir);
		path_dir = NULL;
		token = _strtok(NULL, ":");
		index++;
	}
	/*if it does not find the command, it will free path_var and path_dir*/
	/* and return*/
	free(path_var);
	free(path_dir);
	return (NULL);
}
