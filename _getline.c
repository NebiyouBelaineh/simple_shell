#include "main.h"

/**
 * _fileno - examines the argument stream and returns the integer file
 * descriptor  used  to implement this stream.
 * @stream: FILE stream
 * Return: file descriptor number
 */
int _fileno(FILE *stream)
{
	if (stream == stdin)
		return (0);
	else if (stream == stdout)
		return (1);
	else
		return (2);
}
/**
 * _getline -  reads  an entire line from stream, storing the address of the
 * buffer containing the text into *lineptr.
 * @lineptr: pointer to the buffer where text input is stored
 * @length: length of the line to be read
 * @stream: the specifies the stream to read from
 * Return: returns the number bytes read from the line
 */
ssize_t _getline(char **lineptr, size_t *length, FILE *stream)
{
	char c;
	ssize_t nof_read;
	static char buff[10000];
	static unsigned int buff_size, buff_pos;

	*length = 0;
	while (1)
	{
		if (buff_pos >= buff_size)
		{
			nof_read = read(_fileno(stream), buff, sizeof(buff));
			if (nof_read == -1)
			{
				perror("Error");
				return (1);
			} /*checks for end of file*/
			if (nof_read == 0)
			{
				if (*length == 0)
				{
					*lineptr = NULL;
					return (-1);
				}
				else
					return (*length);
			}
			buff_size = nof_read;
			buff_pos = 0;
		}
		c = buff[buff_pos];
		buff_pos++;
		if (c == '\n')
		{
			return (_getline_support(length, buff, lineptr));
		}
		(*length)++;
	}
}
/**
 * _getline_support - supports _getline function
 * @length: length of the line to be read
 * @buff: buffer to store what is read from the line
 * @lineptr: pointer to the buffer where text input is stored
 * Return: returns the number bytes read from the line
*/
size_t _getline_support(size_t *length, char buff[], char **lineptr)
{
	size_t i;
	char *nline;

	nline = malloc(*length + 2);
	if (nline == NULL)
	{
		perror("Error");
		return (1);
	}
	for (i = 0; i < *length; i++)
		nline[i] = buff[i];
	nline[i] = '\n';
	nline[i + 1] = '\0';
	*lineptr = nline;
	(*length)++;
	return (*length);
}
