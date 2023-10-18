#include "main.h"

/**
 * _strncmp - compares two strings
 * @s1: string 1
 * @s2: string 2
 * @n: number of bytes we want to compare
 * Return: integer that is less than 0, 0,  or more than 0, respectively,
 * if string 1 is less, matches or is more than string 2
 */
int _strncmp(char *s1, char *s2, int n)
{
	int index, flag = 0;

	for (index = 0; (s1[index] != '\0' && s2[index] != '\0') &&
					index < n;
		 index++)
	{
		if (s1[index] == s2[index])
		{
			continue;
		}
		else if (s1[index] > s2[index])
		{
			flag += s1[index] - s2[index];
			return (flag);
		}
		else
		{
			flag -= s2[index] - s1[index];
			return (flag);
		}
	}
	return (0);
}

/**
 * _strcat - concatenates two strings/
 * @dest: string to append src to
 * @src: string to be appended to dest
 * Return: appended string or NULL if it fails
 */
char *_strcat(char *dest, char *src)
{
	char *dest_end;

	if (dest == NULL)
		return (NULL);

	dest_end = dest + strlen(dest);

	while (*src != '\0')
		*dest_end++ = *src++;

	*dest_end = ' ';

	return (dest);
}
