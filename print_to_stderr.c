#include "main.h"

/**
* print_to_stderr - prints string to standard error
*
* @str: string passed to be printed
*
* Return: void
*/
void print_to_stderr(char *str)
{
	write(STDERR_FILENO, str, _strlen(str));
}
