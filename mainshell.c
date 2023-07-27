#include "shell.h"

/**
 * main - this is the main function.
 *
 * Return: (Success) 0 always
 *
 */
int main(void)
{
shell_t data;
int lp;

set_memory((void *)&data, 0, sizeof(data));
signal(SIGINT, signal_handler);
while (1)
{
indexing(&data);
if (line_reader(&data) < 0)
{
if (isatty(STDIN_FILENO))
PRINT("\n");
break;
}
if (line_splitter(&data) < 0)
{
clrmem(&data);
continue;
}
lp = line_parser(&data);
if (lp == 0)
{
clrmem(&data);
continue;
}
if (lp < 0)
{
error(&data);
continue;
}
if (processor(&data) < 0)
{
error(&data);
break;
}
clrmem(&data);
}
clrmem(&data);
exit(EXIT_SUCCESS);
}


#define DELIMITER " \n\t\r\a\v"
/**
 * line_splitter - A function that splits line into tokens.
 * @data: a pointer pointing to the struct of the data.
 *
 * Return: (Success) a positive numbe and (Fail) if a negative number.
 */
int line_splitter(shell_t *data)
{
char *t;
size_t i = 0, s = TOKENSIZE, n;

if (_strcmp(data->line, "\n") == 0)
return (FAIL);
data->args = malloc(s * sizeof(char *));
if (data->args == NULL)
return (FAIL);
t = strtok(data->line, DELIMITER);
if (t == NULL)
return (FAIL);
while (t)
{
data->args[i++] =  t;
if (i + 2 >= s)
{
n = s * 2;
data->args = _realloc(data->args, s * sizeof(char *), n * sizeof(char *));
if (data->args == NULL)
return (FAIL);
s = n;
}
t = strtok(NULL, DELIMITER);
}
data->args[i] = NULL;
return (0);
}
#undef DELIMITER

/**
 * line_reader - A function that reads a line from the standard input.
 * @data: a pointer pointing to the struct of data.
 *
 * Return: (Success) a positive number and (Fail) if is a negative number.
 */
int line_reader(shell_t *data)
{
char *pointa, c, *endPointa;
size_t size = BUFSIZE, size_n, str_read, length;

data->line = malloc(size * sizeof(char));
if (data->line == NULL)
return (FAIL);
if (isatty(STDIN_FILENO))
PRINT(PROMPT);
for (pointa = data->line, endPointa = data->line + size;;)
{
str_read = read(STDIN_FILENO, &c, 1);
if (str_read == 0)
return (FAIL);
*pointa++ = c;
if (c == '\n')
{
*pointa = '\0';
return (SUCCESS);
}
if (pointa + 2 >= endPointa)
{
size_n = size * 2;
length = pointa - data->line;
data->line = _realloc(data->line, size * sizeof(char),
size_n * sizeof(char));
if (data->line == NULL)
return (FAIL);
size = size_n;
endPointa = data->line + size;
pointa = data->line + length;
}
}
}


/**
 * processor -A function that processes command and execute process.
 * @data: a pointer pointing to the struct of data.
 *
 * Return: (Success) a positive numbe and (Fail) if a negative number.
 */
int processor(shell_t *data)
{
pid_t process_id;
int status;

process_id = fork();
if (process_id == 0)
{
signal(SIGINT, SIG_DFL);
if (execve(data->cmd, data->args, environ) < 0)
data->error_msg = _strdup("not found\n");
return (FAIL);
}
else
{
waitpid(process_id, &status, WUNTRACED);
}
return (0);
}

#define DELIMITER ":"
/**
 * line_parser - A function that parses arguments to a valid command.
 * @data: a pointer pointing to the struct of data.
 *
 * Return: (Success) a positive numbe and (Fail) if a negative number.
 */
int line_parser(shell_t *data)
{
if (path(data) > 0)
return (SUCCESS);
if (built_in(data) > 0)
{
if (builtin_handler(data) < 0)
return (FAIL);
return (NEUTRAL);
}
short_form(data);
return (SUCCESS);
}
#undef DELIMITER


