#ifndef _SHELL_H_
#define _SHELL_H_

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

/* Read/Write to temporarily hold data in buffers */
#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUF_FLUSH -1

/* for chaining of commands */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() method */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* if using system getline(): 1 */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HISTORY_FILE	".main_shell_history"
#define HISTORY_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: a prop number field
 * @str: a prop string of characters
 * @next: a pointer to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_type;

/**
 * struct passinfo - contains shadow arguements for passing into a function,
 * allowing uniform prototype for function struct pointer
 * @arg: a string containing arguements returned by getline
 * @argv: an array of strings obtained from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()
 * @linecount_flag: if on count check this line of input
 * @fname: filename for the program
 * @env: a local copy of environ in linked list
 * @environ: custom modified copy of environ from LL env
 * @history: a history of nodes
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the file descriptor from which to read line input
 * @histcount: a history of line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_type *env;
	list_type *history;
	list_type *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chained buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_type;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - holds a builtin string and related functions
 * @type: the builtin command flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_type *);
} builtin_table;


/* in the _shloop.c file*/
int make_hash(info_type *, char **);
int find_builtin(info_type *);
void find_cmd(info_type *);
void fork_cmd(info_type *);

/* in the _parser.c file*/
int is_cmd(info_type *, char *);
char *duplicate_chars(char *, int, int);
char *find_path(info_type *, char *, char *);

/* loophsh.c */
int loop_hash(char **);

/* in the _errors.c */
void puts_error(char *);
int putchar_error(char);
int put_file_dec(char c, int fd);
int put_files_dec(char *str, int fd);

/* in the _string.c */
int string_len(char *);
int string_cmp(char *, char *);
char *starts_with(const char *, const char *);
char *string_cat(char *, char *);

/* in the _string1.c file*/
char *string_copy(char *, char *);
char *duplicate_string(const char *);
void _puts(char *);
int _putchar(char);

/* in the _exits.c file*/
char *copy_string(char *, char *, int);
char *cat_string(char *, char *, int);
char *char_string(char *, char);

/* in the _tokenizer.c */
char **tokenize_string(char *, char *);
char **strtow2(char *, char);

/* in the _realloc.c file*/
char *set_mem(char *, char, unsigned int);
void free_mem(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* in the _memory.c */
int free_buffer(void **);

/* in the _atoi.c file*/
int get_interactive(info_type *);
int is_delimitor(char, char *);
int is_alpha(int);
int _atoi(char *);

/* in the _errors1.c file*/
int atoi_error(char *);
void print_err(info_type *, char *);
int print_deci(int, int);
char *convert_num(long int, int, int);
void strip_comments(char *);

/* in the _builtin.c */
int shell_exit(info_type *);
int shell_cd(info_type *);
int shell_help(info_type *);

/* in the _builtin1.c */
int shell_history(info_type *);
int shell_alias(info_type *);

/*in the _getline.c */
ssize_t accept_input(info_type *);
int get_line(info_type *, char **, size_t *);
void handle_sigint(int);

/* in the _getinfo.c */
void clear_info(info_type *);
void set_info(info_type *, char **);
void free_info(info_type *, int);

/* in the _environ.c */
char *get_env(info_type *, const char *);
int shell_env(info_type *);
int shell_setenv(info_type *);
int shell_unsetenv(info_type *);
int spread_env_list(info_type *);

/* in the _getenv.c */
char **get_shell_env(info_type *);
int unset_shell_env(info_type *, char *);
int set_shell_env(info_type *, char *, char *);

/* in the _history.c */
char *load_history_file(info_type *info);
int compose_history(info_type *info);
int reader_history(info_type *info);
int compose_history_list(info_type *info, char *buf, int linecount);
int nominate_history(info_type *info);

/* in the _lists.c */
list_type *add_node_at_index(list_type **, const char *, int);
list_type *add_node_at_end(list_type **, const char *, int);
size_t print_list_string(const list_type *);
int del_node_at_index(list_type **, unsigned int);
void free_mem_list(list_type **);

/* in the _lists1.c */
size_t get_list_len(const list_type *);
char **list_stringify(list_type *);
size_t print_node_list(const list_type *);
list_type *node_startsWith(list_type *, char *, char);
ssize_t get_nodeIndex(list_type *, list_type *);

/* in the _vars.c */
int isChain(info_type *, char *, size_t *);
void look_chain(info_type *, char *, size_t *, size_t, size_t);
int change_alias(info_type *);
int change_vars(info_type *);
int change_string(char **, char *);

#endif

