#include "shell.h"

/**
 * int_converter - A function that converts integer to array.
 * @ui: given number as param.
 *
 * Return: a pointer pointing to the null terminated string.
 */
char *int_converter(unsigned int ui)
{
char *str;
int length = 0, i = 0;

length = lenFinder(ui);
str = malloc(length + 1);
if (!str)
return (NULL);
*str = '\0';
while (ui / 10)
{
str[i] = (ui % 10) + '0';
ui /= 10;
i++;
}
str[i] = (ui % 10) + '0';
reversed_arr(str, length);
str[i + 1] = '\0';
return (str);
}
/**
 * array_converter - A function that converts character to integer.
 * @arr: given array as param.
 *
 * Return: An integer.
 */
int array_converter(char *arr)
{
int s = 1;
unsigned int ui = 0;


if (arr == NULL)
return (0);
while (*arr)
{
if (*arr == '-')
s *= (-1);
else
ui = (ui * 10) + (*arr - '0');
arr++;
}
return (s *ui);
}

/**
 * lenFinder - A function that determine the number of digit int integer.
 * @i: given int as param.
 *
 * Return: the length of the integer
 */
int lenFinder(int i)
{
int length = 0;

while (i != 0)
{
length++;
i /= 10;
}
return (length);
}
/**
 * error - A function that prints the error.
 * @data: A pointer to the data structure.
 *
 * Return: (Success) a positive number and (Fail) if its a negative number.
 */
int error(shell_t *data)
{
char *c = int_converter(data->index);

PRINT("hsh: ");
PRINT(c);
PRINT(": ");
PRINT(data->args[0]);
PRINT(": ");
PRINT(data->error_msg);
free(c);
return (0);
}

/**
 * history - A function that prints an error.
 * @data:  A pointer to the data structure.
 *
 * Return:(Success) a positive number and (Fail) if its a negative number.
 */
int history(shell_t *data __attribute__((unused)))
{
int i;
char *fn = "history";
char *hl = "this is a line of history";
ssize_t writer, fileDesc;


if (!fn)
return (-1);
fileDesc = open(fn, O_RDWR | O_APPEND);
if (fileDesc < 0)
return (-1);
if (hl)
{
while (hl[i])
i++;
writer = write(fileDesc, hl, i);
if (writer < 0)
return (-1);
}
return (1);
}

