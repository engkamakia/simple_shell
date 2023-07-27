#include "shell.h"
/**
 * path - A function that checks if the given filenname is a path.
 * @data: the data struct pointer.
 *
 * Return: (Success) and (Fail) otherwise.
 */
int path(shell_t *data)
{
if (_strchr(data->args[0], '/') != 0)
{
data->cmd = strduplicate(data->args[0]);
return (SUCCESS);
}
return (FAIL);
}
#define DELIMITER ":"
/**
 * short_form - A function that checks if the given filenname is short form.
 * @data: the data struct pointer.
 *
 * Return: (Success) and (Fail) otherwise.
 */
void short_form(shell_t *data)
{
char *path, *t, *p;
int flag = 0;
struct stat s;

path = get_environ("PATH");
p = strduplicate(path);
t = strtok(p, DELIMITER);
while (t)
{
data->cmd = conc_str(t, data->args[0]);
if (stat(data->cmd, &s) == 0)
{
flag += 1;
break;
}
free(data->cmd);
t = strtok(NULL, DELIMITER);
}
if (flag == 0)
{
data->cmd = strduplicate(data->args[0]);
}
free(p);
}
#undef DELIMITER
/**
 * built_in - A function that checks if the command is builtin.
 * @data: a pointer pointing to the data structure.
 *
 * Return: (Success) and (Fail) otherwise.
 */
int built_in(shell_t *data)
{
built_t arr[] = {
{"exit", abort},
{"cd", cd},
{"help", help_menu},
{NULL, NULL}
};
int a = 0;

while ((arr + a)->cmd)
{
if (strcompare(data->args[0], (arr + a)->cmd) == 0)
return (SUCCESS);
a++;
}
return (NEUTRAL);
}

