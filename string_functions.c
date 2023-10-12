#include "main.h"
/**
 * _strcpy - copies string pointed by src including '\0'
 * to buffer pointed by dest
 * @dest: destination to copy pointed string
 * @src: source where string is pointed
 *
 * Return: pointer to destination (dest)
 */

char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i] != '\0'; i++)
	{
		dest[i] = src[i];

		if (src[i + 1] == '\0')
			dest[i + 1] = '\0';
	}
	return (dest);
}
/**
 * _strdup - returns a pointer to a newly allocated space in memory
 * which contains a copy of the string given as a parameter
 * @str: string to copy
 *
 * Return: pointer to the duplicated string, NULL if insufficent memory
 */
char *_strdup(char *str)
{
	char *s;
	unsigned int i, len = 0;

	if (str == NULL)
		return (NULL);

	while (str[len] != '\0')
	{
		len++;
	}
	s = malloc((len + 1) * (sizeof(char)));

	if (s == NULL)
		return (NULL);

	for (i = 0; i <= len; i++)
		s[i] = str[i];
	return (s);
}
/**
 * _strspn - gets the length of a prefix substring
 * @s: string to examine for prefix
 * @accept: bytes that are looked for in intial segement
 * of 's'
 *
 * Return: Length of prefix sub string
 */
unsigned int _strspn(char *s, char *accept)
{
	int i, j, count;

	count = 0;

	for (i = 0; s[i] != '\0'; i++)
	{
		for (j = 0; accept[j] != '\0'; j++)
		{
			if (s[i] == accept[j])
			{
				count++;
				break;
			}
			else if (accept[j + 1] == '\0')
				return (count);
		}
	}
	return (count);
}
/**
 * _strpbrk - locates the first occurence in the string 's'
 * of any of the bytes in the string 'accept'
 * @s: string to be looked at
 * @accept: string we are looking for in 's'
 *
 * Return: pointer 's' or NULL
 */
char *_strpbrk(char *s, char *accept)
{
	int i, j;

	for (i = 0; s[i] != '\0'; i++)
	{
		for (j = 0; accept[j] != '\0'; j++)
		{
			if (s[i] == accept[j])
			{
				return ((s + i));
			}
		}
	}
	return ('\0');
}
/**
 * _strstr - finds the first occurrence of the substring 'needle'
 * in string haystack
 * @haystack: string where 'needle' is searched
 * @needle: string we are looking to find in 'haystack'
 *
 * Return: pointer where 'needle' is located
 */
char *_strstr(char *haystack, char *needle)
{
	int i, j, flag_index = -1;

	if (*needle == 0)
		return (haystack);
	for (i = 0, j = 0; haystack[j] != '\0' && needle[i] != '\0';)
	{
		if (haystack[j] == needle[i])
		{
			if (i == 0)
				flag_index = j;
			i++;
			j++;
		}
		else
		{
			flag_index = -1;
			i = 0;
			j++;
		}
		if (needle[i + 1] == '\0' && flag_index != -1)
			return ((haystack + flag_index));
	}
	return ('\0');
}
