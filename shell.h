#ifndef SHELL_H
#define SHELL_H

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

/* for reading and writing buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for the command chainnig */
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* for converting numbers */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* for using system getline */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

extern char **environ;
/**
 * struct lists - singly linked list
 * @num: the number 
 * @str: a string
 * @next: pointer that point to the next mode
 */
typedef struct lists
{
	int num;
	char *str;
	struct lists *next;
} list_t;
/**
 * struct pass_info - contains prototypes arguenents to pass in a func
 * @arg: a string from getline containing arguments
 * @argv: array of strings from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exiting
 * @linecount_flag: the line of count if on input
 * @filename: the program filename
 * @env: linked list of environ
 * @environ: the modified copy of env
 * @history: the history node
 * @alias: the alias name
 * @env_changed: it on if environ was changed
 * @status: the return status of the last command of exced
 * @cmd_bf_type: cmd type OR, AND, semicolon
 * @cmd_buf: address of pointer to cmd buf
 * @readfd: the file descriptor that read from line input
 * @histcount: the history line number count
 */
typedef struct pass_info
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *filename;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char *cmd_buf; /* pointer to cmd, the chain buffer, for memory management */
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT\
{NULL, NULL,0,0,0,0, NULL, NULL, NULL, NULL, NULL, 0,0,0, NULL,\
	0,0,0}
/**
 * struct built_in - a struct that contain built-in string and other func
 * @type: the built-in flag
 * @func: the functions
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t*);
} builtin_table;

/* prototypes for the vars.c */
int is_chain(info_t *info, char *buf, size_t *p);
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len);
int replace_alias(info_t *info);
int replace_vars(info_t *info);
int replace_string(char **old, char *neww);

/* prototypes for the tokenizer file */
char **strtow(char *str, char *d);

/* prototypes for string_1.c file */
char *_strcpy(char *dest, const char *src);
char *_strdup(const char *str);
void _puts(const char *str);
int _putchar(char c);

/* prototypes for string.c */
size_t _strlen(const char *s);
int _strcmp(const char *s1, const char *s2);
const char *starts_with(const char *haystack, const char *needle);
char *_strcat(char *dest, const char *src);

/* prototypes for shell_loop.c file* */
int hsh(info_t *info, char **av);
int find_buitin(info_t *info);
void find_cmd(info_t *info);
void fork_cmd(info_t *info);

/* prototypes of realloc.c file */
char *_memset(char *s, char b);
void ffree(char **pp);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* prototypes of parser.c file */
int is_cmd(info_t *info, char *path);

/* prototypes of memory.c file */
int bfree(void **ptr);

/* prototypes of list1.c file*/
size_t list_len(const list_t *h);
char **list_to_strings(list_t *head);
size_t print_list(const list_t *h);
list_t *node_starts_with(list_t *node, const char *prefix, char c);
ssize_t get_node_index(list_t *head, list_t *node);

/* prototypes of lists.c file */
list_create_node(const char *str, int num);
list_t *add_node(list_t **head, const char *str, int num);
size_t print_list_str(const list_t *h);
int delete_node_at_index(list_t **head, unsigned int index);
void free_list(list_t **head_ptr);

/* prototypes of history.c file */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, cost char *buf, int linecount);
int renumber_history(info_t *info);

/* prototypes of get_info.c */
void clear_info(info_t *info);
void set_info(info_t *info, char **av);
void free_info(info_t *info, int all);

/* getenv.c files prototypes */
char **get_environ(info_t *info);
int _unsetenv(info_t *info, char *var);
int _setenv(info_t *info, char *var, char *value);

/* getline.c file prototypes */
ssize_t get_input(info_t *info);
ssize_t read_buf(info_t *info, char *buf, size_t len);
int _getline(info_t *info, char **ptr, size_t *lenght);
void sigintHandler(int sig_num);

/* prototypes of exits.c file */
char *_strncpy(char *dest, const char *src, size_t n);
char *_strncat(char *destr, const char *src, size_t n);
char *_strchr(const char *s, int c);

/* prototypes error1.c file */
int erratoi(const char *s);
void print_error(const info_t *info, const char *estr);
int print_d(int input, int fd);
char *convert_number(long int num, int base, int flags);
void remove_comments(char *buf);

/* prototypes for errors.c file */
void my_puts(char *str);
int my_putchar(char c);
int my_putfd(char c, int fd);
int my_putsfd(char *str, int fd);

/* prototypes for environ.c file */
int print_environment(const list_t *env);
char *get_environment_variable(const list_t *env, const char *name);
int set_environment_variable(list_t **env, const char *name,
const char *value);
int unset_environment_variable(list_t **env, const char *name);
int populate_environment_list(list_t **env);

/* prototypes for builtin1.c file */
int display_history(info_t *info);
int unset_alias(info_t *info, char *str);
int set_alias(info_t *info, char *str);
int print_alias(alias_t *alias);
int manage_alias(info_t *info);

/* prototyes for builtin.c file */
int exist_shell(info_t *info);
int change_direectory(info_t *info);
int display_help(info_t *info);

/* prototypes for atoi.c file */
int interactive(info_t *info);
int is_delim(char c, char *delim);
int _isalpha(int c);
int _atoi(char *s);

#endif
