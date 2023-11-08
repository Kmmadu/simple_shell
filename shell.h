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

/* Constants for buffer sizes and command chaining */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1
#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2
#define USE_GETLINE 0
#define USE_STRTOK 0
#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

extern char **environ;

/* Struct for singly linked list of strings */
typedef struct liststr
{
    int num;
    char *str;
    struct liststr *next;
} list_t;

/* Struct for passing arguments and information into functions */
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
    char **cmd_buf;
    int cmd_buf_type;
    int readfd;
    int histcount;
} info_t;

#define INFO_INIT \
    {NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, 0, 0, 0}

/* Struct for built-in command information */
typedef struct builtin
{
    char *type;
    int (*func)(info_t *);
} builtin_table;

/* Function Declarations */
int show_help(info_t *info);
int change_directory(info_t *info);
int exit_shell(info_t *info);
void _print(const char *str);
char **tokenize_cmd(const char *cmd, const char *delim, int *num_tokens);
int _strlen(const char *str);
int check_interactive(info_t *info);
int is_delimiter(char c, char *delim);
int is_alpha(int c);
int custom_atoi(char *s);
void display_prompt(void);
void command_exec(char *cmd);
void read_cmd(char *cmd, size_t size);
int unset_alias_by_name(info_t *info, char *alias_name);
int add_alias(info_t *info, char *str);
int display_history(info_t *info);
int handle_alias(info_t *info);
int print_alias_entry(list_t *node);
int main_shell_loop(info_t *info, char **av);
int find_builtin_command(info_t *info);
void find_external_command(info_t *info);
void _putchar(char c);
void _puts(char *str);

#endif

