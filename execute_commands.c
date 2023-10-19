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

	if (_strncmp(arr_token[0], "exit", _strlen("exit")) == 0)
	{
		if (arr_token[1] == NULL)
		{
			free_mem(index_ptr, arr_token);
			exit(EXIT_SUCCESS);
		}
		else if (_is_number(arr_token[1]))
		{
			exit_status = _atoi(arr_token[1]);
			if (exit_status > 256)
				exit_status = exit_status % 256;
			free_mem(index_ptr, arr_token);
			exit(exit_status);
		}
		else
		{
			print_to_stderr(p_name);
			print_to_stderr(": ");
			print_num_err(*line_counter);
			print_to_stderr(": ");
			print_to_stderr(arr_token[0]);
			print_to_stderr(": ");
			print_to_stderr("Illegal number");
			print_to_stderr(": ");
			print_to_stderr(arr_token[1]);
			print_to_stderr("\n");
			free_mem(index_ptr, arr_token);
			return (2);
		}
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
	print_to_stderr(p_name);
	print_to_stderr(": ");
	print_num_err(*line_counter);
	print_to_stderr(": ");
	print_to_stderr(command);
	print_to_stderr(": ");
	print_to_stderr("not found");
	print_to_stderr("\n");
}
/**
 * execute_commands - executes builtin commands
 * @arr_token: an array of strings that are to be executed
 * @index_ptr: pointer to the index of arr_token
 * @p_name: program name that is running
 * @line_counter: counts the number of lines the terminal has been used for
 * @exit_ptr: pointer to the exit status
 * Return: 0 for success, 1 for error.
 */
int execute_commands(char *arr_token[], int *index_ptr, char *p_name,
					 int *line_counter, int *exit_ptr)
{
	if (_strncmp(arr_token[0], "exit", _strlen("exit")) == 0 &&
		_strlen(arr_token[0]) == _strlen("exit"))
	if (_isexit(arr_token, index_ptr, p_name, line_counter) == 1)
		return (0);
	if (_strncmp("env", arr_token[0], _strlen("env")) == 0 &&
		_strlen(arr_token[0]) == _strlen("env"))
	{
		_printenv();
		free_mem(index_ptr, arr_token);
		*exit_ptr = 0;
		return (*exit_ptr);
	}
	if (_strcmp(arr_token[0], "setenv") == 0 && (_strlen(arr_token[0]) ==
												 _strlen("setenv")))
	{
		*exit_ptr = _setenv(arr_token[1], arr_token[2], OVERWRITE);
		/*Error already handled and printed in _setenv*/
		free_mem(index_ptr, arr_token);
		return (*exit_ptr);
	}
	if (_strcmp(arr_token[0], "unsetenv") == 0 && (_strlen(arr_token[0]) ==
												   _strlen("unsetenv")))
	{
		*exit_ptr = _unsetenv(arr_token[1]);
		/*Error already handled and printed in _unsetenv*/
		free_mem(index_ptr, arr_token);
		return (*exit_ptr);
	}
	if (_strcmp(arr_token[0], "cd") == 0)
	{
		*exit_ptr = _is_cd(arr_token, p_name, line_counter);
		free_mem(index_ptr, arr_token);
		return (*exit_ptr);
	}
	return (execute_process(arr_token, index_ptr, p_name, line_counter,
	exit_ptr));
}
/**
 * execute_process- uses execve to execute commands passed as arguments
 * @arr_token: an array of strings that are to be executed
 * @index_ptr: pointer to the index of arr_token
 * @p_name: program name that is running
 * @line_counter: counts the number of lines the terminal has been used for
 * @exit_ptr: pointer to the exit status
 * Return: 0 for success, 1 for error.
 */
int execute_process(char *arr_token[], int *index_ptr, char *p_name,
					int *line_counter, int *exit_ptr)
{
	int wstatus, flag_command = 0;
	char *command_path;
	pid_t child_process;

	command_path = find_command(arr_token[0]);
	if (command_path == NULL)
	{
		handle_errors(p_name, line_counter, arr_token[0]);
		free_mem(index_ptr, arr_token);
			return (127);
	}
	if (_strcmp(command_path, arr_token[0]) == 0)
		flag_command = 1;
	child_process = fork();
	if (child_process == -1)
	{
		perror("Error");
		free_mem(index_ptr, arr_token);
		return (1);
	}
	else if (child_process == 0)
	{
		if ((execve(command_path, arr_token, __environ)) == -1)
		{
			perror(" "); /*MEMORY FREED AFTER ERROR*/
			free_mem(index_ptr, arr_token);
			return (1);
		}
		exit(0); /*exits if there is no error executing command*/
	}
	else
	{
		waitpid(child_process, &wstatus, 0);
		free_mem_exec(arr_token, index_ptr, flag_command, command_path);
		*exit_ptr = wstatus;
		if (wstatus == 0)
			return (wstatus); /*Normal termination*/
		else
			return (wstatus); /*Abnormal termination*/
	}
}

