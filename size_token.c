#include "shell.h"
/**
 * tokenize - A function that separates the string using a limiter
 * @data: pointer to the data
 * Return: array of the different parts of the string
 */
void tokenize(programme_data *data)
{
	char *limiter = " \t";
	int x, y, count = 2, l;

	l = str_length(data->input_line);
	if (l)
	{
		if (data->input_line[l - 1] == '\n')
			data->input_line[l - 1] = '\0';
	}

	for (x = 0; data->input_line[x]; x++)
	{
		for (y = 0; limiter[y]; y++)
		{
			if (data->input_line[x] == limiter[y])
				count++;
		}
	}

	data->tokens = malloc(count * sizeof(char *));
	if (data->tokens == NULL)
	{
		perror(data->program_name);
		exit(errno);
	}
	x = 0;
	data->tokens[x] = str_duplicate(_strtok(data->input_line, limiter));
	data->command_name = str_duplicate(data->tokens[0]);
	while (data->tokens[x++])
	{
		data->tokens[x] = str_duplicate(_strtok(NULL, limiter));
	}
}
