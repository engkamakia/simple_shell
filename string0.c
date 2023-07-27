#include "shell.h"

/**
 * conc_str - A function that concatenates two string.
 * @a: given destination.
 * @b: given source.
 *
 * Return: (Success) to the newly string and (Fail) if it failed.
 */
char *conc_str(char *a, char *b)
{
char *output;
int  i = 0, j = 0, lengthOne, lengthTwo;

lengthOne = _strlen(a);
lengthTwo = _strlen(b);
output = malloc((lengthOne + lengthTwo + 2) * sizeof(char));
if (!output)
return (NULL);
*output = '\0';
while (a[j])
output[i++] = a[j++];
output[i++] = '/';
j = 0;
while (b[j])
output[i++] = b[j++];
output[i] = '\0';
return (output);
}
/**
 * _strlen - A function that finds the length of a given string.
 * @s: the given string
 *
 * Return: (Success) the length of the string and if it (Fail) negative value.
 */
int _strlen(char *s)
{
int i;

for (i = 0; s[i]; i++)
;
return (i);
}
/**
 * strcompare - A function that compares two strings.
 * @str1: string one.
 * @str2: string two.
 *
 * Return: (Success) a positive number and if it (Fail) a negative number.
 */
int strcompare(char *str1, char *str2)
{
int compare = 0, a;

if (str1 == NULL || str2 == NULL)
return (1);
for (a = 0; str1[a]; a++)
{
if (str1[a] != str2[a])
{
compare = str1[a] - str2[a];
break;
}
else
continue;
}
return (compare);
}
/**
 * _strchr - A function that locates a character in a given string.
 * @str1: string one.
 * @str2: string two.
 *
 * Return: on (Success) a pointer pointing  to str2
 * and if a (Fail) returns a null pointer.
 */
char *_strchr(char *str1, char str2)
{
char *pointa;

if (str1 == NULL)
return (NULL);
for (pointa = str1; *pointa; pointa++)
if (*pointa == str2)
return (pointa);
return (NULL);
}
/**
 * strduplicate - A function that dupicates a string.
 * @c: the string.
 *
 * Return: on (Success) a pointer pointing  to str2
 * and if a (Fail) returns a null pointer.
 */
char *strduplicate(char *c)
{
char *duplicate;

if (c == NULL)
return (NULL);
duplicate = malloc(_strlen(c) + 1);
if (duplicate == NULL)
return (NULL);
copy_str(duplicate, c);
return (duplicate);
}

