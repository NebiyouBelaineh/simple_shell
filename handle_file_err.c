#include "main.h"

/**
 * handle_file_err - prints error mesasge along with associated program name,
 * line number and command passed to the terminal
 * @p_name: program name
 * @line_counter: pointer to the number of line counter
 * @filename: filename passed to the terminal
 * Return: void.
 */
void handle_file_err(char *p_name, int *line_counter, char *filename)
{
	print_to_stderr(p_name);
	print_to_stderr(": ");
	if (isatty(_fileno(stdin)))
		print_to_stderr("0");
	else
		print_num_err(*line_counter);
	print_to_stderr(": ");
	print_to_stderr("cannot open ");
	print_to_stderr(filename);
	print_to_stderr(": No such file");
	if (isatty(_fileno(stdin)))
		print_to_stderr("\n");
}
