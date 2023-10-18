#include "main.h"

/**
* _is_cd - handles change directory commands
* @arr_token: an array of strings with commands passed to the terminal
* Return: 0 for success, -1 for error
*/
int _is_cd(char **arr_token)
{
	char *pwd, *cwd;

	if (arr_token[1] == NULL)
	{
		pwd = _getenv("PWD");
		cwd = getcwd(NULL, 0);
		_setenv("PWD", cwd, OVERWRITE);
		chdir(HOME);
		free(cwd);
		free(pwd);
		return (0);
	}
	if (_strcmp(arr_token[1], "-") == 0)
	{
		pwd = _getenv("PWD");
		cwd = getcwd(NULL, 0);
		_setenv("PWD", cwd, OVERWRITE);

		print_to_terminal(pwd);
		print_to_terminal("\n");
		chdir(pwd);

		free(pwd);
		free(cwd);
		return (0);
	}
	else
	{
		pwd = _getenv("PWD");
		cwd = getcwd(NULL, 0);
		_setenv("PWD", cwd, OVERWRITE);
		/*Need to handle error on invalid directories and errors*/
		chdir(arr_token[1]);
		free(cwd);
		free(pwd);
	}
	return (1);
}
