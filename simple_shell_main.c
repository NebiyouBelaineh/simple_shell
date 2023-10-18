#include "main.h"
void handle_file_err(char *p_name, int *line_counter, char *filename);
/**
 * main - simple shell takes commands and arguments and
 * executes the commands
 * @ac: argument count
 * @av: argument vector
 * Return: 0 for success
 */
int main(int ac, char *av[])
{
	char *line = NULL, *prompt = "$ ", *p_name = av[0], *arr_tok[100],
	*f_name = av[1];
	int token_ret = 0, index, env_count = 0, *index_ptr = &index,
	status = 0, *exit_ptr = &status;
	static int line_counter = 0, *l_count = &line_counter;
	size_t len = 0;
	ssize_t nread = 0;

	while (__environ[env_count] != NULL)
		env_count++;
	if (ac >= 2)
	{
		return (handle_file(f_name, arr_tok, index_ptr, p_name, l_count,
		exit_ptr));
	}
	while (1)
	{
		if (isatty(_fileno(stdin)))
			print_to_terminal(prompt);
		nread = _getline(&line, &len, stdin);
		if (nread == -1)
			handle_EOF(line, env_count);
		line_counter++;
		line[_strcspn(line, "\n")] = 0;
		if (!cmd_separator(line, p_name, l_count, exit_ptr))
			continue;
		if (!handle_logical_and(line, p_name, l_count, exit_ptr))
			continue;
		if (!handle_logical_or(line, p_name, l_count, exit_ptr))
			continue;
		token_ret = tokenize_input(line, arr_tok, index_ptr);
		if (token_ret)
			free(line);
		else if (token_ret == 0)
		{
			free(line);
			handle_var_rp(arr_tok, exit_ptr);
			execute_commands(arr_tok, index_ptr, p_name, l_count, exit_ptr);
		}
	}
	return (0);
}
/**
 * handle_file - handles file input to the shell
 * @filename: file to be read and input to the shell
 * @arr_token: an array of strings containing commands and their arguments
 * @index_ptr: pointer to the index of arr_token
 * @p_name: name of the program running
 * @line_countptr: pointer to the terminal line counter
 * @exit_ptr: pointer to the exit status
 * Return: 0 if it succeeds reading the file, 1 otherwise
 */
int handle_file(char *filename, char **arr_token,
int *index_ptr, char *p_name, int *line_countptr, int *exit_ptr)
{
	char file_con[10000], *line_cmd[100];
	int index1, index2, fd, *index_ptr1 = &index1, token_ret, b_read;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		handle_file_err(p_name, line_countptr, filename);
		return (1);
	}
	b_read = read(fd, file_con, sizeof(file_con));
	if (b_read == -1)
	{
		perror("Error:read");
		return (1);
	}
	file_con[b_read] = '\0';
	tokenize_by_delim(file_con, line_cmd, index_ptr1, "\n");
	for (index2 = 0; line_cmd[index2] != NULL; index2++)
	{
		line_cmd[index2][_strcspn(line_cmd[index2], "\n")] = 0;
		if (!cmd_separator(line_cmd[index2], p_name, line_countptr, exit_ptr))
			continue;
		if (!handle_logical_and(line_cmd[index2], p_name, line_countptr, exit_ptr))
			continue;
		if (!handle_logical_or(line_cmd[index2], p_name, line_countptr, exit_ptr))
			continue;
		token_ret = tokenize_input(line_cmd[index2], arr_token, index_ptr);
		if (token_ret)
			free(line_cmd[index2]);
		else if (token_ret == 0)
		{
			free(line_cmd[index2]);
			handle_var_rp(arr_token, exit_ptr);
			execute_commands(arr_token, index_ptr, p_name, line_countptr, exit_ptr);
		}
	}
	close(fd);
	return (0);
}
/**
 * handle_EOF - handles the case if EOF is reached
 * @line: string read from _getline
 * @env_count: number environment variables at the start of program
 * Return: void.
 */
void handle_EOF(char *line, int env_count)
{
	int index = 0;

	if (isatty(_fileno(stdin)))
		print_to_terminal("\n");
	free(line);
	line = NULL;
	while (__environ[index] != NULL)
		index++;
	if (env_count < index)
		while (env_count < index)
		{
			free(__environ[env_count]);
			env_count++;
		}
	exit(EXIT_SUCCESS);
}

/**
 * handle_var_rp - handles variable replacement inputs
 * @arr_token: array of strings input from terminal
 * @exit_ptr: pointer to the exit status
 * Return: input string expanded variable
 */
int handle_var_rp(char **arr_token, int *exit_ptr)
{
	unsigned int index = 0, exit_status, pid;
	char *replacement;

	pid = getpid();
	/* char *replacement; */

	for (index = 0; arr_token[index] != NULL; index++)
	{
		if (_strcmp(arr_token[index], "$$") == 0)
		{
			replacement = num_to_string(pid);
			free(arr_token[index]);
			arr_token[index] = malloc(_strlen(replacement) * sizeof(char) + 1);
			_strcpy(arr_token[index], replacement);
			free(replacement);
			return (1);
		}
		else if (_strcmp(arr_token[index], "$?") == 0)
		{
			if (__WIFEXITED(*exit_ptr))
				exit_status = __WEXITSTATUS(*exit_ptr);
			replacement = num_to_string(exit_status);
			free(arr_token[index]);
			arr_token[index] = malloc(_strlen(replacement) * sizeof(char) + 1);
			_strcpy(arr_token[index], replacement);
			if (exit_status)
				free(replacement);
			return (1);
		}
		else if (*arr_token[index] == '$')
		{
			support_var_rp(arr_token, index);
		}
	}
	return (1);
}

/**
 * support_var_rp - supports variable replacement function
 * @arr_token: an array of string commands
 * @index: index of arr_token
 * Return: void
 */
void support_var_rp(char **arr_token, int index)
{
	char *copy, *replacement, *env_var;
	int index2;

	copy = malloc(_strlen(arr_token[index]) + 1);
	if (copy == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		exit(EXIT_FAILURE);
	}
	_strcpy(copy, arr_token[index]);
	replacement = _strpbrk(copy, "$");

	for (index2 = 0; replacement[index2] != '\0'; index2++)
		replacement[index2] = replacement[index2 + 1];
	replacement[index2] = '\0';
	env_var = _getenv(replacement);

	free(arr_token[index]);
	arr_token[index] = malloc(_strlen(env_var) * sizeof(char) + 1);
	_strcpy(arr_token[index], env_var);
	free(env_var);
	free(copy);
}
