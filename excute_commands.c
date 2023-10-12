#include "main.h"

/**
 * _isexit()- checks if 'exit' or 'exit status' mesage is passed to terminal
 * @arr_token: string of arrays containing tokens from the terminal input
 * @index_ptr: pointer to the index of arr_token array
 * @p_name: program name
 * @line_counter: pointer to the number of line counter
 * Return: void
 */
int _isexit(char **arr_token, int *index_ptr, char *p_name, int *line_counter)
{
	int exit_status;

	if (_strcmp(arr_token[0], "exit") == 0)
	{ /*change atoi to custom*/
		if (_is_number(arr_token[1]))
		{
			exit_status = _atoi(arr_token[1]);
			free_mem(index_ptr, arr_token);
			exit(exit_status);
		}
		else
		{
			print_to_terminal(p_name);
			print_to_terminal(": ");
			print_number(*line_counter);
			print_to_terminal(": ");
			print_to_terminal(arr_token[0]);
			print_to_terminal(": ");
			print_to_terminal("Illegal number");
			print_to_terminal(": ");
			print_to_terminal(arr_token[1]);
			print_to_terminal("\n");
			free_mem(index_ptr, arr_token);
			return (1);
		}
		/*What if atoi is passed a non integer*/
	}
	return (0);
}

/**
 * free_mem - frees memory for an array of strings
 * @index_ptr: pointer to the index of the array
 * @ptr: an array of strings to have its memory free'd
 * Return: void.
 */
void free_mem(int *index_ptr, char **ptr)
{
	int index;

	for (index = 0; index < *index_ptr; index++)
	{
		free(ptr[index]);
		ptr[index] = NULL;
	}
}

/**
 * handle_errors - prints error mesasge along with associated program name,
 * line number and command passed to the terminal
 * @p_name: program name
 * @line_counter: pointer to the number of line counter
 * @command: command passed to the terminal
 * Return: void.
 */
void handle_errors(char *p_name, int *line_counter, char *command)
{
	/*/bin/sh: 1: qwerty: not found*/
	print_to_terminal(p_name);
	print_to_terminal(": ");
	print_number(*line_counter);
	print_to_terminal(": ");
	print_to_terminal(command);
	print_to_terminal(": ");
	print_to_terminal("not found");
	print_to_terminal("\n");
}
/**
 * execute_commands - uses execve to execute commands passed as arguments
 *
 * @arr_token: an array of strings that are to be executed
 * @index_ptr: pointer to the index of arr_token
 * @p_name: program name that is running
 * @line_counter: counts the number of lines the terminal has been used for
 * Return: 0 for success, 1 for error.
 */
int execute_commands(char *arr_token[], int *index_ptr, char *p_name,
					 int *line_counter)
{
	int exec_status, wstatus, isexit_ret;
	char *command_path;
	pid_t child_process;

	isexit_ret = _isexit(arr_token, index_ptr, p_name, line_counter);
	if (isexit_ret == 1)
		return (1);
	command_path = find_command(arr_token[0]);
	if (command_path == arr_token[0])
	{
		handle_errors(p_name, line_counter, arr_token[0]);
		free_mem(index_ptr, arr_token);
		return (1);
	}
	child_process = fork();
	if (child_process == -1)
	{
		perror("Error: fork");
		/*MEMORY FREED AFTER ERROR*/
		free_mem(index_ptr, arr_token);
		return (1);
	}
	else if (child_process == 0)
	{
		exec_status = execve(command_path, arr_token, __environ);
		if (exec_status == -1)
		{
			print_to_terminal(p_name);
			perror(" ");
			free_mem(index_ptr, arr_token);
		}
		exit(0); /*exits if there is no error executing command*/
	}
	else
	{
		wait(&wstatus);
		free_mem(index_ptr, arr_token);
		free(command_path);
	}
	return (0);
}
