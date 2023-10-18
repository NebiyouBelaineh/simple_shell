#include "main.h"

/**
* num_to_string - converts a number to a string
* @number: integer number to be converted to string
* Return: string version of number
*/
char *num_to_string(int number)
{
	char buffer[12], temp, *num;

	int index1 = 0, index2;

	if (number == 0)
		return ("0");
	while (number > 0)
	{
		buffer[index1++] = '0' + (number % 10);
		number /= 10;
	}

	for (index2 = 0; index2 < index1 / 2; index2++)

	{
		temp = buffer[index2];
		buffer[index2] = buffer[index1 - index2 - 1];
		buffer[index1 - index2 - 1] = temp;
	}
	buffer[index1] = '\0';
	num = malloc(_strlen(buffer) * sizeof(char) + 1);
	if (num == NULL)
		return (NULL);
	_strcpy(num, buffer);
	return (num);
}

