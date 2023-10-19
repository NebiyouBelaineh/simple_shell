#include "main.h"

void handle_cd_err(char **arr_token, char *p_name, int *line_counter);
/**
* _is_cd - handles change directory commands
* @arr_token: an array of strings with commands passed to the terminal
* @p_name: program name
* @line_counter: pointer to the number of line counter
* Return: 0 for success, -1 for error
*/
int _is_cd(char **arr_token, char *p_name, int *line_counter)
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
		if (chdir(arr_token[1]) == -1)
		{
			handle_cd_err(arr_token, p_name, line_counter);
			free(cwd);
			free(pwd);
			return (2);
		}
		free(cwd);
		free(pwd);
		return (0);
	}
}

/**
 * handle_cd_err - prints error mesasge along with associated program name,
 * line number and command passed to the terminal
 * @arr_token: an array of string commands
 * @p_name: program name
 * @line_counter: pointer to the number of line counter
 * Return: void.
 */
void handle_cd_err(char **arr_token, char *p_name, int *line_counter)
{
			print_to_stderr(p_name);
			print_to_stderr(": ");
			print_num_err(*line_counter);
			print_to_stderr(": ");
			print_to_stderr(arr_token[0]);
			print_to_stderr(": ");
			print_to_stderr("can't cd to ");
			print_to_stderr(arr_token[1]);
			if (isatty(_fileno(stdin)))
				print_to_stderr("\n");
}
