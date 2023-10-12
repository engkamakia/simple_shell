#include "shell.h"
/**
 * _strtok - this function separates strings with delimiters
 * @line: pointes to array we receive.
 * @delim: the characters we mark off string in parts.
 * Return: pointer to the created token
*/
char *_strtok(char *line, char *delim)
{
	int y;
	static char *str;
	char *string_copy;

	if (line != NULL)
		str = line;
	for (; *str != '\0'; str++)
	{
		for (y = 0; delim[y] != '\0'; y++)
		{
			if (*str == delim[y])
			break;
		}
		if (delim[y] == '\0')
			break;
	}
	string_copy = str;
	if (*string_copy == '\0')
		return (NULL);
	for (; *str != '\0'; str++)
	{
		for (y = 0; delim[y] != '\0'; y++)
		{
			if (*str == delim[y])
			{
				*str = '\0';
				str++;
				return (string_copy);
			}
		}
	}
	return (string_copy);
}
