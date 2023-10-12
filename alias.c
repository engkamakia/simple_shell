#include "shell.h"

/**
 * print_alias - function to add, remove or show aliases
 * @data: A struct for the programme
 * @alias: aliases to be printed
 * Return: 0 on success, otherwise an error_code.
 */
int print_alias(programme_data *data, char *alias)
{
	int x, j, length_alias;
	char buffer[250] = {'\0'};

	if (data->alias_list)
	{
		length_alias = str_length(alias);
		for (x = 0; data->alias_list[x]; x++)
		{
			if (!alias || (str_compare(data->alias_list[x], alias, length_alias)
				&&	data->alias_list[x][length_alias] == '='))
			{
				for (j = 0; data->alias_list[x][j]; j++)
				{
					buffer[j] = data->alias_list[x][j];
					if (data->alias_list[x][j] == '=')
						break;
				}
				buffer[j + 1] = '\0';
				buffer_add(buffer, "'");
				buffer_add(buffer, data->alias_list[x] + j + 1);
				buffer_add(buffer, "'\n");
				_print(buffer);
			}
		}
	}

	return (0);
}

/**
 * get_alias - function to add, remove or show aliases
 * @data: struct for the programme
 * @name: requested aliases.
 * Return: 0 on success, otherwise an error_code.
 */
char *get_alias(programme_data *data, char *name)
{
	int x, length_alias;

	/* validate the arguments */
	if (name == NULL || data->alias_list == NULL)
		return (NULL);

	length_alias = str_length(name);

	for (x = 0; data->alias_list[x]; x++)
	{/* Iterates through the environ and check for coincidence of the varname */
		if (str_compare(name, data->alias_list[x], length_alias) &&
			data->alias_list[x][length_alias] == '=')
		{/* returns the value of the key NAME=  when find it */
			return (data->alias_list[x] + length_alias + 1);
		}
	}
	/* returns NULL if did not find it */
	return (NULL);

}

/**
 * set_alias - function to add, or override an alias
 * @alias_string: alias to be set
 * @data: struct for the programme
 * Return: 0 on success, otherwise an error_code.
 */
int set_alias(char *alias_string, programme_data *data)
{
	int i, y;
	char buffer[250] = {'0'}, *temp = NULL;

	/* validate the arguments */
	if (alias_string == NULL ||  data->alias_list == NULL)
		return (1);
	/* Iterates alias to find = char */
	for (i = 0; alias_string[i]; i++)
		if (alias_string[i] != '=')
			buffer[i] = alias_string[i];
		else
		{/* search if the value of the alias is another alias */
			temp = get_alias(data, alias_string + i + 1);
			break;
		}

	/* Iterates through the alias list and check for coincidence of the varname */
	for (y = 0; data->alias_list[y]; y++)
		if (str_compare(buffer, data->alias_list[y], i) &&
			data->alias_list[y][i] == '=')
		{/* if the alias alredy exist */
			free(data->alias_list[y]);
			break;
		}

	/* add the alias */
	if (temp)
	{/* if the alias already exist */
		buffer_add(buffer, "=");
		buffer_add(buffer, temp);
		data->alias_list[y] = str_duplicate(buffer);
	}
	else /* if the alias does not exist */
		data->alias_list[y] = str_duplicate(alias_string);
	return (0);
}
