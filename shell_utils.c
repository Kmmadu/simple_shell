#include "shell.h"

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
char **tokenize_cmd(char *cmd, const char *delim, int *num_tokens)
{
	char **tokens, *token;
	int max_tokens, i;

	max_tokens = _strlen(cmd) / 2 + 1;
	tokens = malloc(max_tokens * sizeof(char *));
	i = 0;
	if (!tokens)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	token = strtok(cmd, delim);
	while (token != NULL && i < max_tokens)
	{
		tokens[i] = malloc((_strlen(token) + 1) * sizeof(char));
		if (!tokens[i])
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}

		_strcpy(tokens[i], token);
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

/**
 * _strcpy - copy string from src to dest
 *
 * @src: pointer to the source string
 * @dest: pointer containing the resulting copied string
 *
 * Return: pointer to dest
 */
char *_strcpy(char *dest, char *src)
{
	char *cpy;
	int index;

	index = 0;
	for (index = 0; src[index] != '\0'; index++)
	{
		dest[index] = src[index];
	}
	dest[index] = '\0';
	cpy = dest;
	return (cpy);
}

/**
 * _strcat - conactenates two strings and return a pointer to that
 *
 * @dest: pointer to the string to be appended
 * @src: pointer to the string to append
 *
 * Return: pointer to the conacatenated string
 */
char *_strcat(char *dest, char *src)
{
	unsigned int len, index;

	len = 0;
	index = 0;
	while (dest[len] != '\0')
	{
		len++;
	}
	while (src[index] != '\0')
	{
		dest[len] = src[index];
		len++;
		index++;
	}
	dest[len] = '\0';
	return (dest);
}
