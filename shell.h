#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Will handle buffer */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* Will run mulitiple commands */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* Will handle conveting num */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* getline.c */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - Will pass 'arguments'
 *@arg: argument
 *@argv: array of strings
 *@path: string path for cmd
 *@argc: argument count
 *@lin_cnt: will handle error count
 *@error_num: will return if exit fails
 *@lincnt_flag: if on count this line of input
 *@file_name: program filename
 *@env: copy of environ
 *@environ: local environ
 *@history: node
 *@alias: node
 *@env_changed: environ was changed
 *@status: return status
 *@cmd_buffer: pointer address
 *@cmd_buffer_type: will handle ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcnt: will count num of line
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int lin_cnt;
	int error_num;
	int lincnt_flag;
	char *file_name;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buffer;
	int cmd_buffer_type;
	int readfd;
	int histcnt;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - string
 *@type: cmd flag
 *@func: function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* hsh.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* handle_path.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loop */
int loophsh(char **);

/* errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* str_copy3.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* str_copy.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* str_copy1.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* handle_str.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* handle_mem.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* handle_mem1.c */
int bfree(void **);

/* interactive_shell.c*/
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* conv_str.c */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *conv_num(long int, int, int);
void rm_comments(char *);

/* builtin.c */
int cpy_exit(info_t *);
int cpy_cd(info_t *);
int _help(info_t *);

/* builtin1.c */
int cpy_hist(info_t *);
int cpy_alias(info_t *);

/* getline.c */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/*init_ info.c */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* setenv.c*/
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

/* setenv2.c */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* history.c */
char *history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int list_history(info_t *info, char *buf, int linecount);
int renum_history(info_t *info);

/* handle_str.c*/
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* handle_str1.c */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* check_chain.c */
int _chain(info_t *, char *, size_t *);
void chain_check(info_t *, char *, size_t *, size_t, size_t);
int rep_alias(info_t *);
int rep_var(info_t *);
int rep_str(char **, char *);

#endif
