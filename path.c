#include "shell.h"

int check_file(char *full_path);

/**
 * find_program - A function to find a program in path
 * @data: pointer pointing to the program's data
 * Return: 0 if success, otherwise error_code
 */

int find_program(programme_data *data)
{
	int x = 0, rate = 0;
	char **folders;

	if (!data->command_name)
		return (2);

	/**if is a full_path or an executable in the same path */
	if (data->command_name[0] == '/' || data->command_name[0] == '.')
		return (check_file(data->command_name));

	free(data->tokens[0]);
	data->tokens[0] = str_concat(str_duplicate("/"), data->command_name);
	if (!data->tokens[0])
		return (2);

	folders = tokenize_path(data);/* search in the PATH */

	if (!folders || !folders[0])
	{
		errno = 127;
		return (127);
	}
	for (x = 0; folders[x]; x++)
	{/* appends the function_name to path */
		folders[x] = str_concat(folders[x], data->tokens[0]);
		rate = check_file(folders[x]);
		if (rate == 0 || rate == 126)
		{/* the file was found, is not a directory and has execute permisions*/
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = str_duplicate(folders[x]);
			free_array_of_pointers(folders);
			return (rate);
		}
	}
	free(data->tokens[0]);
	data->tokens[0] = NULL;
	free_array_of_pointers(folders);
	return (rate);
}

/**
 * tokenize_path - A function to tokenize the path in folders
 * @data: pointer  pointing to the program's data
 * Return: an array of path folder's
 */

char **tokenize_path(programme_data *data)
{
	int x = 0;
	int no_of_folders = 2;
	char **tokens = NULL;
	char *PATH;

	/* get the PATH value*/
	PATH = env_get_key("PATH", data);
	if ((PATH == NULL) || PATH[0] == '\0')
	{/*path not found*/
		return (NULL);
	}

	PATH = str_duplicate(PATH);

	/* find the number of folders in the PATH */
	for (x = 0; PATH[x]; x++)
	{
		if (PATH[x] == ':')
			no_of_folders++;
	}

	/* reserve space for the array of pointers */
	tokens = malloc(sizeof(char *) * no_of_folders);

	/*tokenize and duplicate each token of path*/
	x = 0;
	tokens[x] = str_duplicate(_strtok(PATH, ":"));
	while (tokens[x++])
	{
		tokens[x] = str_duplicate(_strtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (tokens);

}

/**
 * check_file - A function to check if file exists, if not a directory and
 * if it has excecution permisions .
 * @full_path: pointer pointing to the full file name
 * Return: 0 on success, otherwise an error_code.
 */

int check_file(char *full_path)
{
	struct stat sb;

	if (stat(full_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) ||  access(full_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	/*if not exit the file*/
	errno = 127;
	return (127);
}
