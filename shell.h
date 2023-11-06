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

/* Function Declarations */

int show_help(info_t *info)
int change_directory(info_t *info)
int exit_shell(info_t *info)
void _print(const char *str)
char **tokenize_cmd(const char *cmd, const char *delim, int *num_tokens)
int _strlen(const char *str)
int check_interactive(info_t *info)
int is_delimiter(char c, char *delim)
int is_alpha(int c)
int custom_atoi(char *s)
void display_prompt(void)
void command_exec(char *cmd)
void read_cmd(char *cmd, size_t size)


#endif

