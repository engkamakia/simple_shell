#ifndef _SHELL_H_
#define _SHELL_H_

/* header files */
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


extern char **environ;

/* Macros */
#define BUFSIZE 256
#define FAIL (-1)
#define NEUTRAL (0)
#define PRINT(c) (write(STDOUT_FILENO, c, _strlen(c)))
#define PROMPT "$ "
#define SUCCESS (1)
#define TOKENSIZE 64

/* Struct */

/**
 * struct sh_data - Global data structure
 * @line: the line input
 * @args: the arguments token
 * @error_msg: the global path
 * @cmd: the parsed command
 * @index: the command index
 * @oldpwd: the old path visited
 * @env: the environnment
 *
 * Description: A structure contains all the variables needed to manage
 * the program, memory and accessability
 */
typedef struct sh_data
{
	char *line;
	char **args;
	char *cmd;
	char *error_msg;
	char *oldpwd;
	unsigned long int index;
	char *env;
} shell_t;

/**
 * struct builtin - struct to manage the builtin functions.
 * @cmd: command line on the string form.
 * @f: function associated with struct.
 *
 * Description: A struct made to manage the builtins cmd's.
 */
typedef struct builtin
{
	char *cmd;
	int (*f)(shell_t *data);
} built_t;
/* -------mainshell.c---------*/
int line_reader(shell_t *data);
int line_splitter(shell_t *);
int line_parser(shell_t *data);
int processor(shell_t *data);

/* -------String0.c-----------*/


/* -------String1.c-------*/
char *copy_str(char *destination, char *s);

/* -------Mem.c-------*/
void *allocator(void *pointa, unsigned int prevSize, unsigned int size_n);
char *setmem(char *str, char c, unsigned int j);
char *copier(char *destination, char *source, unsigned int j);
int clrmem(shell_t *data);

/* -------Tools0.c------*/
void *arr_fill(void *arr, int elements, unsigned int length);
void signal_handler(int sgn);
char *get_environ(char *name);
void indexing(shell_t *data);
void reversed_arr(char *a, int length);

/* -------tools1.c-------*/
char *int_converter(unsigned int ui);
int lenFinder(int i);
int array_converter(char *arr);
int error(shell_t *data);
int history(shell_t *data __attribute__((unused)));
int alphabet(int c);

/* --------Builtins0.c----------*/
int abort(shell_t *data __attribute__((unused)));
int cd(shell_t *data);
int help_menu(shell_t *data);
int builtin_handler(shell_t *data);
int builtin_checker(shell_t *data);

/* ------Parse.c---------*/
int path(shell_t *data);
void short_form(shell_t *data);
int built_in(shell_t *data);

#endif /* SHELL_H */
