#ifndef _SHELL_H_
#define _SHELL_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
void _print(char *str);
void display_prompt(void);
void command_exec(char *cmd);
void read_cmd(char *cmd, size_t size);
char **tokenize_cmd(char *cmd, char *delim, int *num_tokens);
int _strlen(char *str);
#endif
