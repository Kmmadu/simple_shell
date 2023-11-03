#ifndef _SIMPLE_SHELL_H_
#define _SIMPLE_SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* Buffer Sizes */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* Command Chaining Types */
#define CMD_NORMAL 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

/* Convert Number Flags */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* Using system getline */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HISTORY_FILE ".simple_shell_history"
#define HISTORY_MAX 4096

extern char **environ;

/**
 * Singly Linked List Structure
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * Structure to Pass Information to Functions
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
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* Pointer to command chaining buffer */
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT {NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, 0, 0, 0}

/**
 * Structure to Define Builtin Commands and Functions
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* Function Declarations */

int shell_loop(info_t *, char **);
int find_builtin_command(info_t *);
void find_command(info_t *);
void fork_command(info_t *);

int is_command(info_t *, char *);
char *duplicate_chars(char *, int, int);
char *find_command_path(info_t *, char *, char *);

int main_loop(char **);

void error_puts(char *);
int error_putchar(char);
int put_fd(char c, int fd);
int puts_fd(char *str, int fd);

int string_length(char *);
int string_compare(char *, char *);
char *starts_with(const char *, const char *);
char *string_concatenate(char *, char *);

char *string_copy(char *, char *);
char *string_duplicate(const char *);
void custom_puts(char *);
int custom_putchar(char);

char *string_copy_n(char *, char *, int);
char *string_concatenate_n(char *, char *, int);
char *string_find_char(char *, char);

char **string_tokenize(char *, char *);
char **string_tokenize_v2(char *, char);

char *memory_set(char *, char, unsigned int);
void free_strings(char **);
void *custom_realloc(void *, unsigned int, unsigned int);

int batch_free(void **);

int is_chain_command(info_t *, char *, size_t *);
void check_chain_commands(info_t *, char *, size_t *, size_t, size_t);
int replace_alias_command(info_t *);
int replace_variables(info_t *);
int replace_string_array(char **, char *);

#endif

