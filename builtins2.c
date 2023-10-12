#include "shell.h"

/**
 * builtin_exit - A function to exit program with the status
 * @data: A struct for the programme
 * Return: 0 on success, otherwise an error_code.
 */
int builtin_exit(programme_data *data)
{
	int x;

	if (data->tokens[1] != NULL)
	{/*if exists arg for exit, check if is a number*/
		for (x = 0; data->tokens[1][x]; x++)
			if ((data->tokens[1][x] < '0' || data->tokens[1][x] > '9')
				&& data->tokens[1][x] != '+')
			{/*if is not a number*/
				errno = 2;
				return (2);
			}
		errno = _atoi(data->tokens[1]);
	}
	free_all_data(data);
	exit(errno);
}

/**
 * builtin_cd - function to change the current directory
 * @data: A struct for the programme
 * Return: 0 on success, otherwise an error_code.
 */
int builtin_cd(programme_data *data)
{
	char *home_directory = env_get_key("HOME", data), *dir_old = NULL;
	char previous_directory[128] = {0};
	int code_error = 0;

	if (data->tokens[1])
	{
		if (str_compare(data->tokens[1], "-", 0))
		{
			dir_old = env_get_key("OLDPWD", data);
			if (dir_old)
				code_error = set_work_directory(data, dir_old);
			_print(env_get_key("PWD", data));
			_print("\n");

			return (code_error);
		}
		else
		{
			return (set_work_directory(data, data->tokens[1]));
		}
	}
	else
	{
		if (!home_directory)
			home_directory = getcwd(previous_directory, 128);

		return (set_work_directory(data, home_directory));
	}
	return (0);
}

/**
 * set_work_directory - A function to set the work directory
 * @data: A struct for the programme
 * @new_dir: path to be set
 * Return: 0 on success, otherwise an error_code.
 */
int set_work_directory(programme_data *data, char *new_dir)
{
	char previous_directory[128] = {0};
	int err_code = 0;

	getcwd(previous_directory, 128);

	if (!str_compare(previous_directory, new_dir, 0))
	{
		err_code = chdir(new_dir);
		if (err_code == -1)
		{
			errno = 2;
			return (3);
		}
		env_set_key("PWD", new_dir, data);
	}
	env_set_key("OLDPWD", previous_directory, data);
	return (0);
}

/**
 * builtin_help - function that shows the environment ofshell
 * @data: A struct for the programme
 * Return: 0 on success, otherwise an error_code.
 */
int builtin_help(programme_data *data)
{
	int i, length = 0;
	char *mensajes[6] = {NULL};

	mensajes[0] = HELP_MSG;

	/* validate args */
	if (data->tokens[1] == NULL)
	{
		_print(mensajes[0] + 6);
		return (1);
	}
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->command_name);
		return (5);
	}
	mensajes[1] = HELP_EXIT_MSG;
	mensajes[2] = HELP_ENV_MSG;
	mensajes[3] = HELP_SETENV_MSG;
	mensajes[4] = HELP_UNSETENV_MSG;
	mensajes[5] = HELP_CD_MSG;

	for (i = 0; mensajes[i]; i++)
	{
		length = str_length(data->tokens[1]);
		if (str_compare(data->tokens[1], mensajes[i], length))
		{
			_print(mensajes[i] + length + 1);
			return (1);
		}
	}
	/*if there is no match, print error and return -1 */
	errno = EINVAL;
	perror(data->command_name);
	return (0);
}

/**
 * builtin_alias - function to add, remove or show aliases
 * @data: A struct for the programme
 * Return: 0 on success, otherwise an error_code.
 */
int builtin_alias(programme_data *data)
{
	int i = 0;

	/* if there are no arguments, print all environment */
	if (data->tokens[1] == NULL)
		return (print_alias(data, NULL));

	while (data->tokens[++i])
	{/* if there are arguments, set or print each env variable*/
		if (count_characters(data->tokens[i], "="))
			set_alias(data->tokens[i], data);
		else
			print_alias(data, data->tokens[i]);
	}

	return (0);
}
