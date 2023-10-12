#include "main.h"
/**
* _strcmp - compares two strings
* @s1: string 1
* @s2: string 2
*
* Return: integer that is less than 0, 0,  or more than 0, respectively,
* if string 1 is less, matches
* or is more than string 2
*/
int _strcmp(char *s1, char *s2)
{
	int i;

	int flag;

	flag = 0;

	for (i = 0; s1[i] != '\0' && s2[i] != '\0'; i++)
	{
		if (s1[i] == s2[i])
		{
			continue;
		}
		else if (s1[i] > s2[i])
		{
			flag += s1[i] - s2[i];
			return (flag);
		}
		else
		{
			flag -= s2[i] - s1[i];
			return (flag);
		}
	}
	return (0);
}

/**
* _strlen - returns the length of the string str
* @s: string argument(pointer)
*
* Return: string length
*/
int _strlen(char *s)
{
	unsigned int index;

	for (index = 0; s[index] != '\0';)
		index++;

	return (index); /* i - 1 since we don't count the '\0' character*/
}

/**
* _strtok - divides a string to tokens based on the delimeters
* @str: string to be divided
* @delimiters: delimiters used to break the string to tokens
* Return: pointer to the tokens each time and NULL when there are no more
* tokens
*/
char *_strtok(char *str, const char *delimiters)
{
	static char *next_str = NULL, *remaining_str;

	if (str == NULL)
		str = next_str;

	if (str == NULL)
		return (NULL);

	/* str += strspn(str, delimiters); */

	if (*str == '\0')
	{
		next_str = str;
		return (NULL);
	}
	remaining_str = strpbrk(str, delimiters);

	if (remaining_str == NULL)
	{
		remaining_str = str + strlen(str);
		next_str = remaining_str;
		return (str);
	}

	*remaining_str = '\0';
	next_str = remaining_str + 1;

	return (str);
}

/**
* _strcspn - gets the length of a prefix substring
* @s: string to examine for prefix
* @reject: bytes that are to be rejected from intial segement
* of 's'
*
* Return: returns the number of bytes in the initial segment
* of s which are not in the string reject.
*/
unsigned int _strcspn(char *s, char *reject)
{
	unsigned int i, j;

	for (i = 0; s[i]; i++)
	{
		for (j = 0; reject[j]; j++)
		{
			if (s[i] == reject[j])
				return (i);
		}
	}
	return (i);
}

/**
 * str_concat - concatenates strings s1, s2 and s3. Newly formed string memory
 * is allocated using malloc.
 * @s1: string one
 * @s2: string two
 * @s3: string three
 * Return: pointer to the newly allocated memory of the concatenated string,
 * or NULL on failure.
 */
char *str_concat(char *s1, char *s2, char *s3)
{
	int i = 0, len1 = 0, len2 = 0, len3 = 0;
	char *str;

	if (s1 == NULL)
		s1 = "";
	if (s2 == NULL)
		s2 = "";
	if (s3 == NULL)
		s3 = "";

	while (s1[len1] != '\0')
		len1++;
	while (s2[len2] != '\0')
		len2++;
	while (s3[len3] != '\0')
		len3++;

	str = malloc((len1 + len2 + len3 + 1) * (sizeof(char)));

	if (str == NULL)
		return (NULL);

	for (i = 0; i < len1; i++)
		str[i] = s1[i];
	for (i = 0; i < len2; i++)
		str[len1 + i] = s2[i];
	for (i = 0; i < len3; i++)
		str[len1 + len2 + i] = s3[i];

	str[len1 + len2 + i] = '\0';

	return (str);
}
