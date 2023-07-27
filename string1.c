#include "shell.h"
/**
 * copy_str - A function that copies a string from s to destination.
 * @s: the source string.
 * @destination: the destination of the string.
 *
 * Return: the pointer pointing to the destination.
 */
char *copy_str(char *destination, char *s)
{
int a;

for (a = 0; s[a] != '\0'; a++)
{
destination[a] = s[a];
}
destination[a] = '\0';
return (destination);
}
/**
 * alphabet - A function that checks if the input is a letter.
 * @i: character to be checked.
 *
 * Return: 1 if letter and 0 if otherwise.
 */
int alphabet(int i)
{
if ((i >= 65 && i <= 90) || (i >= 97 && i <= 122))
{
return (SUCCESS);
}
return (FAIL);
}


