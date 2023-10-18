#include "main.h"

/**
 * cmd_separator - checks if inputs have command separator ';' and executes
 * commands one by one
 * @line: string input
 * @p_name: program name being ran
 * @line_countptr: pointer to the line counter
 * @exit_ptr: pointer to the exit status
 * Return: 0 if it finds command separators, 1 otherwise
 */
int cmd_separator(char *line, char *p_name, int *line_countptr, int *exit_ptr)
{
	int index1 = 0, index2 = 0 /* , index3 = 0, *cmd_indexptr = &index3 */;
	char *command[100], /*  *cmd_brk[100],  */ *token, *delimiter = ";";

	for (; line[index1] != '\0'; index1++)
	{
		if (line[index1] == ';')
		{
			if (_is_semi_colons(line))
			{
				handle_syntax_errors(p_name, line_countptr, ";");
				free(line);
				return (0);
			}
			token = _strtok(line, delimiter);
			for (; token != NULL; index2++)
			{
				command[index2] = malloc(_strlen(token) + 1);
				_strcpy(command[index2], token);
				token = _strtok(NULL, delimiter);
			}
			command[index2] = NULL;
			support_command_sep(command, p_name, line_countptr, exit_ptr);
			for (index2 = 0; command[index2] != NULL; index2++)
				free(command[index2]);
			free(line);
			return (0);
		}
	}
	return (1);
}

/**
 * support_logical_and - function to execute commands for separator function
 * @command: an array of string commands
 * @p_name: program name running
 * @line_countptr: pointer to the line counter
 * @exit_ptr: pointer to the exit status
 * Return: void
 */
void support_command_sep(char *command[], char *p_name,
						 int *line_countptr, int *exit_ptr)
{
	char *token, *cmd_brk[100];
	int index1 = 0, index2 = 0, *cmd_indexptr = &index2;

	/*iterates through semi colion separated commands*/
	for (index1 = 0; command[index1] != NULL; index1++)
	{
		if (_is_semi_colons(command[index1]))
		{
			handle_syntax_errors(p_name, line_countptr, ";");
			break;
		}
		if (_is_space(command[index1]))
			continue;
		{
			token = _strtok(command[index1], " ");
			for (index2 = 0; token != NULL; index2++)
			{
				cmd_brk[index2] = malloc(_strlen(token) + 1);
				_strcpy(cmd_brk[index2], token);
				token = _strtok(NULL, " ");
			}
			cmd_brk[index2] = NULL;
			handle_var_rp(cmd_brk, exit_ptr);
			execute_commands(cmd_brk, cmd_indexptr, p_name, line_countptr, exit_ptr);
			free(cmd_brk[index2]);
			cmd_brk[index2] = NULL;
		}
	}
}

/**
 * _is_semi_colons - checks if string is filled with semi colons only
 * @str: string to be checked
 * Return: 0 if not all spaces, 1 otherwise
 */
int _is_semi_colons(char *str)
{
	int index = 0;

	if (_strcmp(str, ";") == 0)
		return (1);
	while (str[index] != '\0')
	{
		if (str[index] != ' ' && str[index] != '\t' && str[index] != ';')
			return (0);
		index++;
	}
	return (1);
}

/**
 * handle_syntax_errors - prints error mesasge along with associated program
 * name, line number and command passed to the terminal
 * @p_name: program name
 * @line_counter: pointer to the number of line counter
 * @syntax: wrong syntax passed to the terminal
 * Return: void.
 */
void handle_syntax_errors(char *p_name, int *line_counter, char *syntax)
{
	print_to_terminal(p_name);
	print_to_terminal(": ");
	print_number(*line_counter);
	print_to_terminal(": ");
	print_to_terminal("Syntax error");
	print_to_terminal(": \"");
	print_to_terminal(syntax);
	print_to_terminal("\" unexpected");
	print_to_terminal("\n");
	}
