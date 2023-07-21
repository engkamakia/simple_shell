#ifndef _SHELL_H_
#define _SHELL_H_

/* header files */
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>





extern char **environ;


#define BUFSIZE 256
#define FAIL (-1)
#define NEUTRAL (0)
#define PRINT(c) (write(STDOUT_FILENO, c, _strlen(c)))
#define PROMPT "$ "
#define SUCCESS (1)
#define TOKENSIZE 64




typedef struct shell_data
{
	char *line;
	char **args;
	char *cmd;
	char *error_msg;
	char *oldpwd;
	unsigned long int index;
	char *env;
} shell_t;

typedef struct built_in
{
	char *cmd;
	int (*f)(shell_t *data);
} builtin_t;
/* ----------Process prototype------------*/
int read_line(shell_t *);
int split_line(shell_t *);
int parse_line(shell_t *);
int process_cmd(shell_t *);

/* ----------String prototype------------*/
char *_strdup(char *str);
char *_strcat(char *first, char *second);
int _strlen(char *str);
char *_strchr(char *str, char c);
int _strcmp(char *s1, char *s2);

/* ----------More String prototype-------*/
char *_strcpy(char *dest, char *source);

/* ----------Memory prototype------------*/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_memset(char *s, char byt, unsigned int n);
char *_memcpy(char *dest, char *src, unsigned int n);
int free_data(shell_t *);

/* ----------Tools prototype-------------*/
void *fill_an_array(void *a, int el, unsigned int len);
void signal_handler(int signo);
char *_getenv(char *path_name);
void index_cmd(shell_t *data);
void array_rev(char *arr, int len);

/* ----------More tools prototype--------*/
char *_itoa(unsigned int n);
int intlen(int num);
int _atoi(char *c);
int print_error(shell_t *data);
int write_history(shell_t *data);
int _isalpha(int c);

/* -------------Builtins-----------------*/
int abort_prg(shell_t *data);
int change_dir(shell_t *data);
int display_help(shell_t *data);
int handle_builtin(shell_t *data);
int check_builtin(shell_t *data);

/* -------------Parse-----------------*/
int is_path_form(shell_t *data);
void is_short_form(shell_t *data);
int is_builtin(shell_t *data);

#endif