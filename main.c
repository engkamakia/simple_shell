#include "shell.h"
/**
 * main - function that initializes the variables of the program
 * @argc: number of values received as arguments from cmd
 * @argv: values received as arguments from cmd
 * @env: number of values received from the command line
 * Return: 0 on success, otherwise an error_code.
 */
int main(int argc, char *argv[], char *env[])
{
	programme_data data_struct = {NULL}, *data = &data_struct;
	char *mssg_prompt = "";

	initialize_data(data, argc, argv, env);

	signal(SIGINT, handle_ctrl_c);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{/* We are in the terminal, interactive mode */
		errno = 2;/*???????*/
		mssg_prompt = PROMPT_MSG;
	}
	errno = 0;
	sisifo(mssg_prompt, data);
	return (0);
}

/**
 * handle_ctrl_c - A function to print the mssg_prompt in a new line
 * @UNUSED: option of the prototype
 */
void handle_ctrl_c(int opr UNUSED)
{
	_print("\n");
	_print(PROMPT_MSG);
}

/**
 * initialize_data - A function to initialize the struct with the info
 * @data: pointer pointing to the structure of data
 * @argv: array of arguments passed to program via cmd
 * @env: environment passed to the program
 * @argc: number of values received as arguments from cmd
 */
void initialize_data(programme_data *data, int argc, char *argv[], char **env)
{
	int x = 0;

	data->program_name = argv[0];
	data->input_line = NULL;
	data->command_name = NULL;
	data->exec_counter = 0;
	/* define the file descriptor to be readed*/
	if (argc == 1)
		data->file_descriptor = STDIN_FILENO;
	else
	{
		data->file_descriptor = open(argv[1], O_RDONLY);
		if (data->file_descriptor == -1)
		{
			_printe(data->program_name);
			_printe(": 0: Can't open ");
			_printe(argv[1]);
			_printe("\n");
			exit(127);
		}
	}
	data->tokens = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[x]; x++)
		{
			data->env[x] = str_duplicate(env[x]);
		}
	}
	data->env[x] = NULL;
	env = data->env;

	data->alias_list = malloc(sizeof(char *) * 20);
	for (x = 0; x < 20; x++)
	{
		data->alias_list[x] = NULL;
	}
}
/**
 * sisifo - an infinite loop to shows the message prompt
 * @mssg_prompt: message prompt to be printed
 * @data: infinite loop that shows the message prompt
 */
void sisifo(char *mssg_prompt, programme_data *data)
{
	int code_error = 0, length_of_string = 0;

	while (++(data->exec_counter))
	{
		_print(mssg_prompt);
		code_error = length_of_string = _getline(data);

		if (code_error == EOF)
		{
			free_all_data(data);
			exit(errno); /* if EOF is the fisrt Char of string, exit*/
		}
		if (length_of_string >= 1)
		{
			expand_alias(data);
			expand_variables(data);
			tokenize(data);
			if (data->tokens[0])
			{ /* if a text is given to mssg_prompt, execute */
				code_error = execute(data);
				if (code_error != 0)
					_print_error(code_error, data);
			}
			free_recurrent_data(data);
		}
	}
}
