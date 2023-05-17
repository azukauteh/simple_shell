#ifndef SHELL_H
#define SHELL_H

#define END_OF_FILE -2
#define EXIT -3
#include <limits.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>


/**
 * struct list_s - A new struct type defining a linked list.
 * @dir: A directory path.
 * @next: A pointer to another struct list_s.
 */
typedef struct list_s
{
char *dir;
struct list_s *next;
} list_t;


/**
 * struct builtin_s - A new struct type defining builtin commands.
 * @name: The name of the builtin command.
 * @f: A function pointer to the builtin command's function.
 */
typedef struct builtin_s
{
char *name;
int (*f)(char **argv, char **front);
} builtin_t;



/**
 * struct alias_s - A new struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another struct alias_s.
 * alias_t - Global aliases linked list
 */
typedef struct alias_s
{
char *name;
char *value;
struct alias_s *next;

} alias_t;

alias_t *aliases;

typedef struct ino_t
{
int readfd;
} my_ino_t;


typedef struct args_t
{
int args;
int diff;
char env;
} args_t;

/* interactive_shell.c */
int shell_interactive(my_ino_t *);
int is_delimiter(char, char *);
int is_alpha(int);
int string_to_int(char *);

/* getline prototype */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
ssize_t getdelim(char **lineptr, size_t *n, int delim, FILE *stream);


/*var_replacement prototypes */
int is_chain_command(ino_t *, char *, size_t *);
void check_chain_command(ino_t *, char *, size_t *, size_t, size_t);
int replace_alias_command(ino_t *);
int replace_variables(ino_t *);
int replace_string_content(char **, char *);


/*exit.c prototypes */
void help_exit(void);


/* getline.c prototype */
void handle_line(char **line, ssize_t read);


/* History.c Prototypes. */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *get_location(char *command);
list_t *get_path_dir(char *path);
int execute(char **args, char **front);
void help_history(void);

/* builtin_alias.c prototypes */
char **replace_aliases(char **args);
alias_t *add_alias_end(alias_t **head, char *name, char *value);
list_t *add_node_end(list_t **head, char *dir);
void free_alias_list(void);
void help_alias(void);

/* arg.c prototypes */
char *get_args(char *line, int *exe_ret);
int call_args(char **args, char **front, int *exe_ret);
int run_args(char **args, char **front, int *exe_ret);
int handle_args(int *exe_ret);
int check_args(char **args);
void free_args(char **args, char **front);


/* setenv.c prototypes */
int shellby_env(char **args, char __attribute__((__unused__)) **front, char **environ);
int shellby_setenv(char **args, char __attribute__((__unused__)) **front);
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front);


/* env_builtin.c prototypes */
int (*get_builtin(char *command))(char **args, char **front);
int shellby_alias(char **args, char __attribute__((__unused__)) **front);
void help_env(void);


/* builtin.c prototypes */
int shellby_cd(char **args, char __attribute__((__unused__)) **front);
int shellby_exit(char **args, char **front);
int shellby_alias(char **args, char __attribute__((__unused__)) **front);
int shellby_help(char **args, char __attribute__((__unused__)) **front);

/*commits.c (error_ Handling) */
int create_error(char **args, int err);
char *error_env(char **args);
char *error_1(char **args);
char *error_2_exit(char **args);
char *error_2_cd(char **args);
char *error_2_syntax(char **args);
char *error_126(char **args);
char *error_127(char **args);

/* String functions */
int _strlen(const char *s);
char *strcat(char *dest, const char *src);
char *strncat(char *dest, const char *src, size_t n);
char *strcpy(char *dest, const char *src);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
char **strings(char **env);

void help_all(void);
void help_cd(void);
void help_help(void);

int proc_file_commands(char *file_path, int *exe_ret);

#endif/* SHELL_H */
