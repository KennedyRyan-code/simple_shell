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
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct info
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}


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
size_t str_len(const char *);
char *str_cat(char *, char *);
char *str_cpy(char *, char *);
char *str_dup(char *);
void _puts(char *);
int _putchar(char c);
int str_cmp(const char *, const char *);
char *starts_with(const char *, const char *);

/* string_man.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* _errors/ _errors01.c */
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
void _eputs(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_num(long int, int, int);
void rm_comments(char *);
int _erratoi(char *);

/* _atoi.c */
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);


/* _getline.c*/
ssize_t _getinput(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);


/* linked_list/list.c */
size_t print_list(const list_t *);
size_t list_len(const list_t *);
ssize_t get_node_index(list_t *, list_t *);
list_t *node_starts_with(list_t *, char *, char);
char **list_to_strs(list_t *);
void free_list(list_t **);
size_t print_list_str(const list_t *);
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
int delete_node_at_index(list_t **, unsigned int);

/* builtin/builtin1.c */
int _ourhelp(info_t *);
int _ourexit(info_t *);
int _ourcd(info_t *);
int _ourhistory(info_t *);
int set_alias(info_t *info, char *);
int unset_alias(info_t *info, char *);
int _ouralias(info_t *);
int print_alias(list_t *);


/*environ*/
int _ourenv(info_t *);
char *_getenv(info_t *, const char *);
int _oursetenv(info_t *);
int _ourunsetenv(info_t *);
int populateenv_list(info_t *);

/*getenv.c*/
char **get__environ(info_t *);
int unset_env(info_t *, char *);
/*int set_env(info_t *, char *, char *);*/
int set_env(info_t *, char *, char *);

/* realloc.c */
void *_realloc(void *, unsigned int, unsigned int);
char *_memset(char *, char, unsigned int);
void ffree(char **);
int bfree(void **);

/* strtok.c */
char **strtok1(char *, char *);
char **strtok2(char *, char);

/*vars.c*/
int replace_string(char **, char *);
int replace_vars(info_t *);
int replace_alias(info_t *);
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);


/*history.c*/
int build_history_list(info_t *info, char *buf, int linecounter);
int renumber_history(info_t *info);
int read_history(info_t *info);
int write_history(info_t *info);
char *get_history_file(info_t *info);


/*shelloop.c*/
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);


/*getinfo.c*/
void free_info(info_t *info, int all);
void set_info(info_t *info, char **av);
void clear_info(info_t *info);


/* passer.c */
int is_cmd(info_t *info, char *path);
char *dup_chars(char *pathstr, int start, int stop);
char *find_path(info_t *info, char *pathstr, char *cmd);



#endif /* MAIN_H */
