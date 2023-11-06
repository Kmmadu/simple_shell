#include "_shell.h"

/**
 * _print - print a string
 * str: input string
 *
 * Return: always void
 */
void _print(char *str)
{
        write(STDOUT_FILENO, str, strlen(str));
}

/**
 * tokenize_cmd - tokenize a command
 * @cmd: command to tokenize
 * @delim: delimiter
 * @num_tokens: number of tokens
 *
 * Return: the array of tokens
 */
char **tokenize_cmd(char *cmd, char *delim, int *num_tokens)
{
        char **tokens;
        char *token;
        int i, max_tokens;

        max_tokens = _strlen(cmd) / 2 + 1;
        tokens = malloc(max_tokens * sizeof(char *));
        i = 0;
        token = strtok(cmd, delim);

        while (token != NULL && i < max_tokens)
        {
                tokens[i] = malloc((strlen(token) + 1) * sizeof(char));
                strcpy(tokens[i], token);
                i++;
                token = strtok(NULL, delim);
        }
        tokens[i] = NULL;
        *num_tokens = i;
        return tokens;
}

/*
 * _strlen - compute the size of a string
 * @str: input string
 *
 * Return: length of the str
 */
int _strlen(char *str)
{
        int len;

        len = 0;
        while (str[len] != '\0')
        {
                len++;
        }
        return len;
}
