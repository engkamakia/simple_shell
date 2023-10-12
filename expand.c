#include "shell.h"

/**
 * expand_variables - A function to expand variables
 * @data: pointer pointing to a struct
 *
 * Return: 0 on success, otherwise an error_code.
 */
void expand_variables(programme_data *data)
{
	int x, y;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;
	buffer_add(line, data->input_line);
	for (x = 0; line[x]; x++)
		if (line[x] == '#')
			line[x--] = '\0';
		else if (line[x] == '$' && line[x + 1] == '?')
		{
			line[x] = '\0';
			long_to_string(errno, expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, data->input_line + x + 2);
		}
		else if (line[x] == '$' && line[x + 1] == '$')
		{
			line[x] = '\0';
			long_to_string(getpid(), expansion, 10);
			buffer_add(line, expansion);
			buffer_add(line, data->input_line + x + 2);
		}
		else if (line[x] == '$' && (line[x + 1] == ' ' || line[x + 1] == '\0'))
			continue;
		else if (line[x] == '$')
		{
			for (y = 1; line[x + y] && line[x + y] != ' '; y++)
				expansion[y - 1] = line[x + y];
			temp = env_get_key(expansion, data);
			line[x] = '\0', expansion[0] = '\0';
			buffer_add(expansion, line + x + y);
			temp ? buffer_add(line, temp) : 1;
			buffer_add(line, expansion);
		}
	if (!str_compare(data->input_line, line, 0))
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}

/**
 * expand_alias - A function to expand aliases
 * @data: pointer pointing to a struct of the program's data
 *
 * Return: 0 on success, otherwise an error_code.
 */
void expand_alias(programme_data *data)
{
	int x, y, expand = 0;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;

	buffer_add(line, data->input_line);

	for (x = 0; line[x]; x++)
	{
		for (y = 0; line[x + y] && line[x + y] != ' '; y++)
			expansion[y] = line[x + y];
		expansion[y] = '\0';

		temp = get_alias(data, expansion);
		if (temp)
		{
			expansion[0] = '\0';
			buffer_add(expansion, line + x + y);
			line[x] = '\0';
			buffer_add(line, temp);
			line[str_length(line)] = '\0';
			buffer_add(line, expansion);
			expand = 1;
		}
		break;
	}
	if (expand)
	{
		free(data->input_line);
		data->input_line = str_duplicate(line);
	}
}

/**
 * buffer_add - function to append string at end of buffer
 * @buffer: The buffer to be filled
 * @str_to_add: string to be copied in the buffer
 * Return: 0 on success, otherwise an error_code.
 */
int buffer_add(char *buffer, char *str_to_add)
{
	int length_of_str, x;

	length_of_str = str_length_of_str(buffer);
	for (x = 0; str_to_add[x]; x++)
	{
		buffer[length_of_str + x] = str_to_add[x];
	}
	buffer[length_of_str + x] = '\0';
	return (length_of_str + x);
}

