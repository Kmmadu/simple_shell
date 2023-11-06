#include "_shell.h"

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * _print - print a string to the standard output
 * @str: input string
 */
void _print(const char *str)
{
	size_t len = 0;
	const char *p = str;

	while (*p++)
		len++;

	write(STDOUT_FILENO, str, len);
}

/**
 * tokenize_cmd - tokenize a command
 * @cmd: command to tokenize
 * @delim: delimiter
 * @num_tokens: number of tokens
 *
 * Return: the array of tokens
 */
char **tokenize_cmd(const char *cmd, const char *delim, int *num_tokens)
{
	const char *cmd_ptr = cmd;
	char **tokens = NULL;
	char *token;
	int max_tokens = 10;
	int i = 0;

	tokens = malloc(max_tokens * sizeof(char *));
	if (!tokens)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	token = strtok((char *)cmd_ptr, delim);
	while (token != NULL)
	{
		if (i == max_tokens - 1)
		{
			max_tokens *= 2;
			tokens = realloc(tokens, max_tokens * sizeof(char *));
			if (!tokens)
			{
				perror("realloc");
				exit(EXIT_FAILURE);
			}
		}

		tokens[i] = strdup(token);
		if (!tokens[i])
		{
			perror("strdup");
			exit(EXIT_FAILURE);
		}
		i++;
		token = strtok(NULL, delim);
	}
	tokens[i] = NULL;
	*num_tokens = i;
	return (tokens);
}

/**
 * _strlen - compute the size of a string
 * @str: input string
 *
 * Return: length of the str
 */
int _strlen(const char *str)
{
	int len = 0;

	while (str[len] != '\0')
	{
		len++;
	}
	return (len);
}

