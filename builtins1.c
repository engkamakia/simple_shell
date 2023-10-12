#include "shell.h"

/**
 * builtins_list - function to search a match and execute the associate builtin
 * @data: A struct for the programme
 * Return: 0 on success, otherwise an error_code.
 **/
int builtins_list(programme_data *data)
{
	int repeat;
	builtins options[] = {
		{"exit", builtin_exit},
		{"help", builtin_help},
		{"cd", builtin_cd},
		{"alias", builtin_alias},
		{"env", builtin_env},
		{"setenv", builtin_set_env},
		{"unsetenv", builtin_unset_env},
		{NULL, NULL}
	};

/*walk through the structure*/
	for (repeat = 0; options[repeat].builtin != NULL; repeat++)
	{
/*if there is a match between the given command and a builtin,*/
		if (str_compare(options[repeat].builtin, data->command_name, 0))
		{
/*execute the function, and return the return value of the function*/
			return (options[repeat].function(data));
		}
/*if there is no match return -1 */
	}
	return (-1);
}
