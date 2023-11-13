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

/* Function Declarations */
char *does_path_exists(char *path);
char *construct_cmd_path(char *dir, char *cmd);
char *get_cmd_path(char *cmd);
void _print(const char *str);
char **tokenize_cmd(const char *cmd, const char *delim, int *num_tokens);
int _strlen(const char *str);
void display_prompt(void);
void command_exec(char *cmd);
void read_cmd(char *cmd, size_t size);
#endif

