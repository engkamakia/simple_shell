#include "shell.h"
/**
 * execute - funtion to execute a command with its entire path variables.
 * @data: pointer pointing to the program's data
 * Return: 0 on success, otherwise an error_code.
 */
int execute(programme_data *data)
{
	int _value = 0, status;
	pid_t p;

	/* check for program in built ins */
	_value = builtins_list(data);
	if (_value != -1)/* if program was found in built ins */
		return (_value);

	/* check for program file system */
	_value = find_program(data);
	if (_value)
	{/* if program not found */
		return (_value);
	}
	else
	{/* if program was found */
		p = fork(); /* create a child process */
		if (p == -1)
		{ /* if the fork call failed */
			perror(data->command_name);
			exit(EXIT_FAILURE);
		}
		if (p == 0)
		{/* I am the child process, I execute the program*/
			_value = execve(data->tokens[0], data->tokens, data->env);
			if (_value == -1) /* if error when execve*/
				perror(data->command_name), exit(EXIT_FAILURE);
		}
		else
		{/* I am the father, I wait and check the exit status of the child */
			wait(&status);
			if (WIFEXITED(status))
				errno = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				errno = 128 + WTERMSIG(status);
		}
	}
	return (0);
}

