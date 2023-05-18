#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024  /* read/write buffers */
#define BUF_FLUSH -1

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2 /* for convert_number() */

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2 /* for command chaining */
#define CMD_CHAIN	3

#define USE_GETLINE 0
#define USE_STRTOK 0      /* if using system getline() */

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/* Declare the environ variable */
extern char **environ;

/* Declare command counter */
extern int cmd_count;

/**
 * struct strlist - singly list
 * @num: number field
 * @str: the string
 * @next: pointer to the next node
 *
 */
typedef struct strlist
{
	int num;
	char *str;
	struct strlist *next;
} list_t;

/**
 * struct info - struct for programs data
 * @arg: argument strings from getline
 * @argv: array of strings from arg
 * @path: string path for the current command
 * @argc: argument count
 * @fname: program filename
 * @env:  lined list local copy
 * @environ: custom modified copy of environ
 * @env_changed: if environ was changed
 * @line_ecount: the error count
 * @linecount_flag: count on line of input
 * @err_num: the error code for exit()s
 * @alias: the alias node
 * @history: the history node
 * @histcount: the history line number count
 * @status: the return status of the last executed command
 * @cmd_buf: on if chaining, address of pointer to cmd_buf
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the file discriptor from which to read line input
 *
 */

typedef struct info
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	char *fname;
	list_t *env;
	char **environ;
	int env_changed;
	unsigned int line_ecount;
	int linecount_flag;
	int err_num;
	list_t *alias;
	list_t *history;
	int histcount;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
} info_t;


/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* string.c */
size_t str_len(const char *str);
char *str_cat(char *dest, char *src);
char *str_cpy(char *dest, char *src);
char *str_dup(char *str);
int _puts(char *str);
int _putchar(char c);
int str_cmp(const char *s1, const char *s2);


/* _errors.c */
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
void _eputs(char *);
void print_error(info_t *, char *);

/* _atoi.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);









#endif /* MAIN_H */
