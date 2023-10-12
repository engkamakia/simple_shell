#include "shell.h"

/**
 * env_get_key - function to get value of an environment variable
 * @key: environment variable
 * @data: A struct of the programmes
 * Return: pointer to the value of the variable or NULL
 */
char *env_get_key(char *key, programme_data *data)
{
	int x, length_of_key = 0;

	/* validate the arguments */
	if (key == NULL || data->env == NULL)
		return (NULL);

	/* obtains the leng of the variable requested */
	length_of_key = str_length(key);

	for (x = 0; data->env[x]; x++)
	{/* Iterates through the environ and check for coincidence of the vame */
		if (str_compare(key, data->env[x], length_of_key) &&
		 data->env[x][length_of_key] == '=')
		{/* returns the value of the key NAME=  when find it*/
			return (data->env[x] + length_of_key + 1);
		}
	}
	/* returns NULL if did not find it */
	return (NULL);
}

/**
 * env_set_key - function to overwrite value of the environment variable
 * or create it if does not exist.
 * @key: name of the variable
 * @value: the new value
 * @data: A struct of the programmes
 * Return: 0 on success, otherwise an error_code.
 */

int env_set_key(char *key, char *value, programme_data *data)
{
	int x, length_of_key = 0, is_new_key = 1;

	/* validate the arguments */
	if (key == NULL || value == NULL || data->env == NULL)
		return (1);

	/* obtains the leng of the variable requested */
	length_of_key = str_length(key);

	for (x = 0; data->env[x]; x++)
	{/* Iterates through the environ and check for coincidence of the vame */
		if (str_compare(key, data->env[x], length_of_key) &&
		 data->env[x][length_of_key] == '=')
		{/* If key already exists */
			is_new_key = 0;
			/* free the entire variable, it is new created below */
			free(data->env[x]);
			break;
		}
	}
	/* make an string of the form key=value */
	data->env[x] = str_concat(str_duplicate(key), "=");
	data->env[x] = str_concat(data->env[x], value);

	if (is_new_key)
	{/* if the variable is new, it is create at end of actual list and we need*/
	/* to put the NULL value in the next position */
		data->env[x + 1] = NULL;
	}
	return (0);
}

/**
 * env_remove_key - Function to remove a key from the environment
 * @key: key to be  removed
 * @data: structure of the programme
 * Return: 0 on success, otherwise an error_code.
 */
int env_remove_key(char *key, programme_data *data)
{
	int x, length_of_key = 0;

	/* validate the arguments */
	if (key == NULL || data->env == NULL)
		return (0);

	/* obtains the leng of the variable requested */
	length_of_key = str_length(key);

	for (x = 0; data->env[x]; x++)
	{/* iterates through the environ and checks for coincidences */
		if (str_compare(key, data->env[x], length_of_key) &&
		 data->env[x][length_of_key] == '=')
		{/* if key already exists, remove them */
			free(data->env[x]);

			/* move the others keys one position down */
			x++;
			for (; data->env[x]; x++)
			{
				data->env[x - 1] = data->env[x];
			}
			/* put the NULL value at the new end of the list */
			data->env[x - 1] = NULL;
			return (1);
		}
	}
	return (0);
}


/**
 * print_environ - A function that prints the current environment
 * @data: A struct for the programmes data
 * Return: nothing
 */
void print_environ(programme_data *data)
{
	int y;

	for (y = 0; data->env[y]; y++)
	{
		_print(data->env[y]);
		_print("\n");
	}
}
