#include "shell.h"

#define SETOWD(V) (V = strduplicate(getenviron("OLDPWD")))
/**
 * cd - changes directory
 * @data: a pointer to the data structure
 *
 * Return: (Success) 0 is returned
 * ------- (Fail) negative number will returned
 */
int cd(shell_t *data)
{
char *home;

home = getenviron("HOME");
if (data->args[1] == NULL)
{
SETOWD(data->oldpwd);
if (chdir(home) < 0)
return (FAIL);
return (SUCCESS);
}
if (strcompare(data->args[1], "-") == 0)
{
if (data->oldpwd == 0)
{
SETOWD(data->oldpwd);
if (chdir(home) < 0)
return (FAIL);
}
else
{
SETOWD(data->oldpwd);
if (chdir(data->oldpwd) < 0)
return (FAIL);
}
}
else
{
SETOWD(data->oldpwd);
if (chdir(data->args[1]) < 0)
return (FAIL);
}
return (SUCCESS);
}
#undef GETCWD
/**
 * abort - exit the program
 * @data: a pointer to the data structure
 *
 * Return: (Success) 0 is returned
 * ------- (Fail) negative number will returned
 */
int abort(shell_t *data __attribute__((unused)))
{
int code, i = 0;

if (data->args[1] == NULL)
{
clrmem(data);
exit(errno);
}
while (data->args[1][i])
{
if (alphabet(data->args[1][i++]) < 0)
{
data->error_msg = strduplicate("Illegal number\n");
return (FAIL);
}
}
code = alphatoint(data->args[1]);
clrmem(data);
exit(code);
}
/**
 * help_menu - display the help menu
 * @data: a pointer to the data structure
 *
 * Return: (Success) 0 is returned
 * ------- (Fail) negative number will returned
 */
int help_menu(shell_t *data)
{
int fd, fw, rd = 1;
char c;

fd = open(data->args[1], O_RDONLY);
if (fd < 0)
{
data->error_msg = strduplicate("no help topics match\n");
return (FAIL);
}
while (rd > 0)
{
rd = read(fd, &c, 1);
fw = write(STDOUT_FILENO, &c, rd);
if (fw < 0)
{
data->error_msg = strduplicate("cannot write: permission denied\n");
return (FAIL);
}
}
PRINT("\n");
return (SUCCESS);
}
/**
 * builtin_handler - handle and manage the builtins cmd
 * @data: a pointer to the data structure
 *
 * Return: (Success) 0 is returned
 * ------- (Fail) negative number will returned
 */
int builtin_handler(shell_t *data)
{
built_t arr[] = {
{"cd", cd},
{"exit", abort},
{"help", help_menu},
{NULL, NULL}
};
int i = 0;

while ((arr + i)->cmd)
{
if (strcompare(data->args[0], (arr + i)->cmd) == 0)
return ((arr + i)->f(data));
i++;
}
return (FAIL);
}
