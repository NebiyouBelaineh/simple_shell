#include "main.h"
/**
* _printenv - prints the enviornment variables
* Return: void
*/
void _printenv(void)
{
	unsigned int index = 0;

	while ((__environ[index]) != NULL)
	{
		print_to_terminal(__environ[index]);
		print_to_terminal("\n");
		index++;
	}
}
