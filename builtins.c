#include "shell.h"

/**
 * builtin_env - function that shows the environment of shell.
 * @data: A struct for the programme
 * Return: 0 on success, otherwise an error_code.
 */
int builtin_env(programme_data *data)
{
	int x;
	char copy_name[50] = {'\0'};
	char *cpy_variable = NULL;

	/* if not arguments */
	if (data->tokens[1] == NULL)
		print_environ(data);
	else
	{
		for (x = 0; data->tokens[1][x]; x++)
		{/* checks if exists a char = */
			if (data->tokens[1][x] == '=')
			{/* checks if exists a var with the same name and change its value*/
			/* temporally */
				cpy_variable = str_duplicate(env_get_key(copy_name, data));
				if (cpy_variable != NULL)
					env_set_key(copy_name, data->tokens[1] + x + 1, data);

				/* print the environ */
				print_environ(data);
				if (env_get_key(copy_name, data) == NULL)
				{/* print the variable if it does not exist in the environ */
					_print(data->tokens[1]);
					_print("\n");
				}
				else
				{/* returns the old value of the var*/
					env_set_key(copy_name, cpy_variable, data);
					free(cpy_variable);
				}
				return (0);
			}
			copy_name[x] = data->tokens[1][x];
		}
		errno = 2;
		perror(data->command_name);
		errno = 127;
	}
	return (0);
}

/**
 * builtin_set_env - function that sets the environment of shell.
 * @data: @data: A struct for the programme
 * Return: 0 on success, otherwise an error_code.
 */
int builtin_set_env(programme_data *data)
{
	/* validate args */
	if (data->tokens[1] == NULL || data->tokens[2] == NULL)
		return (0);
	if (data->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}

	env_set_key(data->tokens[1], data->tokens[2], data);

	return (0);
}

/**
 * builtin_unset_env - function that unsets the environment of shell.
 * @data: @data: A struct for the programme
 * Return: 0 on success, otherwise an error_code.
 */
int builtin_unset_env(programme_data *data)
{
	/* validate args */
	if (data->tokens[1] == NULL)
		return (0);
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	env_remove_key(data->tokens[1], data);

	return (0);
}
