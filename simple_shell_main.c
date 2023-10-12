#include "main.h"

/**
 * main - super simple shell takes commands and arguments and
 * executes the commands
 * @ac: argument count
 * @av: argument vector
 * Return: 0 for success
 */
int main(int ac __attribute__((unused)), char *av[])
{
	char *line = NULL, *prompt = "$ ";
	char *p_name = av[0];
	char *arr_token[100];
	int token_ret = 0;
	int index = 0, *index_ptr = &index;
	static int line_counter = 0, *line_countptr = &line_counter;
	size_t len = 0;
	ssize_t nread = 0;

	while (1)
	{
		print_to_terminal(prompt);

		nread = _getline(&line, &len, stdin);

		if (nread == -1)
		{
			print_to_terminal("\n");
			free(line);
			line = NULL;
			exit(EXIT_SUCCESS);
		}
		else
		{
			if (nread != 0)
				token_ret = tokenize_input(line, arr_token, index_ptr);
			line_counter++;
			/*condition to stop from executing newline if token_ret == 1*/
			if (token_ret)
				continue;
			else if (token_ret == 0)
				execute_commands(arr_token, index_ptr, p_name, line_countptr);

		}
	}
	return (0);
}
