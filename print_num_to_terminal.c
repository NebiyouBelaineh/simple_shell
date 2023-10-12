#include "main.h"

/**
* print_num - writes the character c to stdout
* @c: The character to print
* Return: On success 1.
* On error, -1 is returned, and errno is set appropriately.
*/
int print_num(char c)
{
	return (write(STDOUT_FILENO, &c, 1));
}
/**
* print_number - prints integer 'n' using _putchar()
* @n: integer argument passed to _putchar()
* Return: void
*/
void print_number(int n)
{
	unsigned int num;

	if (n < 0)
	{
		num = -n;
		print_to_terminal("-");
	}
	else
	{
		num = n;
	}

	if (num >= 10)
	{
		print_number(num / 10);
	}

	print_num((num % 10) + '0');
}
