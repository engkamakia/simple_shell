#include "shell.h"
/**
 * get_environ - gets the path
 * @name: a pointer to the struct of data
 *
 * Return: (Success) a positive number
 * ------- (Fail) a negative number
 */
char *get_environ(char *name)
{
char **env, *pointa_name, *pointa;

env = environ;
while (*env)
{
pointa = *env;
pointa_name = name;
while (*pointa == *pointa_name)
{
if (*pointa == '=')
break;
pointa++;
pointa_name++;
}
if ((*pointa == '=') && (*pointa_name == '\0'))
return (pointa + 1);
env++;
}
return (NULL);
}
/**
 * signal_handler - handle the process interrept signal
 * @sgn: the signal identifier
 *
 * Return: void
 */
void signal_handler(int sgn)
{
if (sgn == SIGINT)
{
PRINT("\n");
PRINT(PROMPT);
}
}
/**
 * arr_fill - fill an array with elements
 * @arr: the given array
 * @elements: the given element
 * @length: the length of the array
 *
 * Return: pointer to filled array
 */
void *arr_fill(void *arr, int elements, unsigned int length)
{
char *c = arr;
unsigned int ui = 0;

while (ui < length)
{
*c = elements;
c++;
ui++;
}
return (arr);
}

/**
 * reversed_arr - reverse array
 * @a: the given array
 * @length: the array length
 *
 * Return: void
 */
void reversed_arr(char *a, int length)
{
char c;
int i;

for (i = 0; i < (length / 2); i++)
{
c = a[i];
a[i] = a[(length - 1) - i];
a[(length - 1) - i] = c;
}
}
/**
 * indexing - indexed command
 * @data: a pointer to the data structure
 *
 * Return: void
 */
void indexing(shell_t *data)
{
data->index += 1;
}

