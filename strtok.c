#include "shell.h"
/**
 * _strtok - A function that separates strings with delimiters.
 *
 * @received_line: a pointer to  char array that we receive.
 * @delimita: a spacing for strings.
 *
 * Return: returns a pointer to the created token.
*/
char *_strtok(char *received_line, char *delimita)
{
int j;
static char *stringg;
char *copystring;

if (received_line != NULL)
stringg = received_line;
for (; *stringg != '\0'; stringg++)
{
for (j = 0; delimita[j] != '\0'; j++)
{
if (*stringg == delimita[j])
break;
}
if (delimita[j] == '\0')
break;
}
copystring = stringg;
if (*copystring == '\0')
return (NULL);
for (; *stringg != '\0'; stringg++)
{
for (j = 0; delimita[j] != '\0'; j++)
{
if (*stringg == delimita[j])
{
*stringg = '\0';
stringg++;
return (copystring);
}
}
}
return (copystring);
}

