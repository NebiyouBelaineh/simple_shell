#include "main.h"

/**
* print_to_terminal - prints string to standard output
*
* @str: string passed to be printed
*
* Return: void
*/
void print_to_terminal(char *str)
{
	write(STDOUT_FILENO, str, _strlen(str));
}
