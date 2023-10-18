#include "main.h"

/**
 * handle_logical_and - handles && logical operator
 * @line: string command with potential && logical operators
 * @p_name: program name running
 * @line_countptr: pointer to the line counter
 * @exit_ptr: pointer to the exit status
 * Return: 0 for if there is && logical operator, 1 otherwise
 */
int handle_logical_and(char *line, char *p_name, int *line_countptr,
int *exit_ptr)
{
	int index1 = 0, index2 = 0;
	char *command[100], *token, *delimiter = "&&";

	for (; line[index1] != '\0'; index1++)
	{
		if (line[index1] == '&' && line[index1 + 1] == '&')
		{
			token = _strtok(line, delimiter);
			for (; token != NULL; index2++)
			{
				command[index2] = malloc(_strlen(token) + 1);
				if (command[index2] == NULL)
				{
					errno = ENOMEM;
					perror("Error");
					exit(EXIT_FAILURE);
				}
				_strcpy(command[index2], token);
				token = _strtok(NULL, delimiter);
			}
			command[index2] = NULL;
			free(line);
			if (!support_logical_and(command, p_name, line_countptr, exit_ptr))
				return (0);
			for (index2 = 0; command[index2] != NULL; index2++)
				free(command[index2]);
			return (0);
		}
	}
	return (1);
}
/**
 * support_logical_and - function to support logical AND handler function
 * @command: an array of string commands
 * @p_name: program name running
 * @line_countptr: pointer to the line counter
 * @exit_ptr: pointer to the exit status
 * Return: 1 if the command executes normally, 0 otherwise
 */
int support_logical_and(char *command[], char *p_name, int *line_countptr,
int *exit_ptr)
{
	char *token, *cmd_brk[100];
	int index1 = 0, index2 = 0, *cmd_indexptr = &index2, exec_status = 0;

	for (index1 = 0; command[index1] != NULL; index1++)
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
		exec_status = execute_commands(cmd_brk, cmd_indexptr, p_name,
									   line_countptr, exit_ptr);
		if (exec_status)
		{
			for (index1 = 0; command[index1] != NULL; index1++)
				free(command[index1]);
			return (0);
		}
		free(cmd_brk[index2]);
		cmd_brk[index2] = NULL;
	}
	return (1);
}

/**
 * handle_logical_or - handles || logical operator
 * @line: string command with potential && logical operators
 * @p_name: program name running
 * @line_countptr: pointer to the line counter
 * @exit_ptr: pointer to the exit status
 * Return: 0 for if there is || logical operator, 1 otherwise
 */
int handle_logical_or(char *line, char *p_name, int *line_countptr,
int *exit_ptr)
{
	int index1 = 0, index2 = 0;
	char *command[100], *token, *delimiter = "||";

	for (; line[index1] != '\0'; index1++)
	{
		if (line[index1] == '|' && line[index1 + 1] == '|')
		{
			token = _strtok(line, delimiter);
			for (; token != NULL; index2++)
			{
				command[index2] = malloc(_strlen(token) + 1);
				if (command[index2] == NULL)
				{
					errno = ENOMEM;
					perror("Error");
					exit(EXIT_FAILURE);
				}
				_strcpy(command[index2], token);
				token = _strtok(NULL, delimiter);
			}
			command[index2] = NULL;
			free(line);
			if (!support_logical_or(command, p_name, line_countptr, exit_ptr))
				return (0);
			for (index2 = 0; command[index2] != NULL; index2++)
				free(command[index2]);
			return (0);
		}
	}
	return (1);
}

/**
 * support_logical_or - function to support logical OR handler function
 * @command: an array of string commands
 * @p_name: program name running
 * @line_countptr: pointer to the line counter
 * @exit_ptr: pointer to the exit status
 * Return: 1 if the command executes normally, 0 otherwise
 */
int support_logical_or(char *command[], char *p_name, int *line_countptr,
int *exit_ptr)
{
	char *token, *cmd_brk[100];
	int index1 = 0, index2 = 0, *cmd_indexptr = &index2, exec_status = 0;

	for (index1 = 0; command[index1] != NULL; index1++)
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
		exec_status = execute_commands(cmd_brk, cmd_indexptr, p_name,
									   line_countptr, exit_ptr);
		if (!exec_status)
		{
			for (index1 = 0; command[index1] != NULL; index1++)
				free(command[index1]);
			return (0);
		}
		free(cmd_brk[index2]);
		cmd_brk[index2] = NULL;
	}
	return (1);
}
