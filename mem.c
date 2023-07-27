#include "shell.h"

/**
 * allocator - A function that reallocates the memory block.
 * @pointa: pointer pointing to the previous memory.
 * @prevSize: the previous size.
 * @size_n: the new size.
 *
 * Return: a pointer pointing to the newly allocated memory.
 */
void *allocator(void *pointa, unsigned int prevSize, unsigned int size_n)
{
void *result;

if (size_n == prevSize)
return (pointa);
if (size_n == 0 && pointa)
{
free(pointa);
return (NULL);
}
result = malloc(size_n);
if (result == NULL)
return (NULL);
if (pointa == NULL)
{
arr_fill(result, '\0', size_n);
free(pointa);
}
else
{
copier(result, pointa, prevSize);
free(pointa);
}
return (result);
}
/**
 * setmem - A function that fills a memory with constant no of byte.
 * @str: A pointer pointing to the memory area.
 * @c: first number of bytes.
 * @j: The constant byte.
 *
 * Return: returns a pointer to a character.
 */
char *setmem(char *str, char c, unsigned int j)
{
unsigned int i;

for (i = 0; i < j; i++)
{
str[i] = c;
}
return (str);
}
/**
 * clrmem - A function that frees data.
 * @data: the data structure.
 *
 * Return: (Success) positive number and (Fail) if is a negative number.
 */
int clrmem(shell_t *data)
{
free(data->line);
data->line = NULL;
free(data->args);
data->args = NULL;
free(data->cmd);
data->cmd = NULL;
free(data->error_msg);
data->error_msg = NULL;
return (0);
}
/**
 * copier - A function that copies memory area.
 * @destination: memory area of destination.
 * @source: Source of memory area to copy.
 * @j: memory size in bytes.
 *
 * Return: A pointer pointing to the destination.
 */
char *copier(char *destination, char *source, unsigned int j)
{
unsigned int i;

for (i = 0; i < j; i++)
{
destination[i] = source[i];
}
return (destination);
}
