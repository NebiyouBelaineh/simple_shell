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
	print_to_terminal(p_name);
	print_to_terminal(": ");
	print_number(*line_counter);
	print_to_terminal(": ");
	print_to_terminal("Can't open ");
	print_to_terminal(filename);
	print_to_terminal("\n");
}
