#include "main.h"
int _isdigit(int c);
/**
 * _atoi - converts strings in to integers
 * @s: string to be converted to numbers
 *
 * Return: Integers converted if present, 0 otherwise
 */
int _atoi(char *s)
{
	int index;
	int len;
	unsigned int num;
	int n_cnt;

	len = _strlen(s);
	num = 0;
	n_cnt = 0;

	for (index = 0; index < len; index++)
	{
		if (s[index] == '-')
			n_cnt++;
		if (s[index] >= '0' && s[index] <= '9')
		{
			num = num * 10 + s[index] - '0';
			if ((s[index + 1] < '0') || (s[index + 1] > '9'))
				break;
		}
	}
	if (num > 0)
	{
		if (n_cnt % 2)
			return (-1 * num);
		else
			return (num);
	}

	return (0);
}

/**
 * _isdigit - checks for digits (0 through 9)
 * @c: integer argument for _isdigit function
 * Return: 1 if 'c' is a digit and 0 otherwise
 */
int _isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}
/**
 * _is_number - checks if a string is a number
 * @str: string to be checked
 * Return: 1 if str is a number, 0 otherwise
 */
int _is_number(char *str)
{
	int index;

	for (index = 0; str[index] != '\0'; index++)
	{
		if (_isdigit(str[index]) == '\0')
			return (0);
	}
	return (1);
}
