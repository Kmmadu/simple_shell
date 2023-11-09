#include "shell.h"
#include <stdlib.h>

/**
 * is_delim - Check if a character is a delimiter.
 * @c: The character to check.
 * @delim: The string of delimiters.
 *
 * Return: 1 if the character is a delimiter, 0 otherwise.
 */
int is_delim(char c, char *delim)
{
	while (*delim)
	{
		if (c == *delim)
			return (1);
		delim++;
	}
	return (0);
}

/**
 * customStringSplit - Split a string into words using a single delimiter.
 * @str: The input string to be split.
 * @d: The delimiter character.
 *
 * Return: A pointer to an array of strings, or NULL on failure.
 */
char **customStringSplit(char *str, char d)
{
	int i, j, k, numwords = 0, m;
	char **s;

	if (str == NULL || str[0] == '\0')
		return (NULL);

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] != d && (str[i + 1] == d || str[i + 1] == '\0'))
			numwords++;
	}

	if (numwords == 0)
		return (NULL);
	s = malloc((numwords + 1) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] != '\0')
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (m = 0; m < j; m++)
				free(s[m]);
			free(s);
			return (NULL);
		}

		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][k] = '\0';
	}
	s[numwords] = NULL;
	return (s);
}

/**
 * customStringSplitWithDelimiters - Split a string into
 * words using specified delimiters.
 * @str: The input string to be split.
 * @d: The delimiter string containing all possible delimiters.
 *
 * Return: A dynamically allocated array of strings, each representing a word
 *         from the input string. Returns NULL on failure or when no words are
 *         found.
 */
char **customStringSplitWithDelimiters(char *str, char *d)
{
	int numwords = 0, i, k, m, j;
	char **s;

	if (str == NULL || str[0] == '\0')
		return (NULL);
	if (!d)
		d = " ";

	for (i = 0; str[i] != '\0';)
	{
		while (is_delim(str[i], d))
			i++;
		if (str[i] != '\0')
			numwords++;
		while (str[i] && !is_delim(str[i], d))
			i++;
	}
	if (numwords == 0)
		return (NULL);
	s = malloc((numwords + 1) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(str[i], d))
			i++;
		for (k = 0; str[i + k] && !is_delim(str[i + k], d); )
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (m = 0; m < j; m++)
				free(s[m]);
			free(s);
			return (NULL);
		}
		strncpy(s[j], str + i, k), s[j][k] = '\0', i += k;
	}
	s[numwords] = NULL;
	return (s);
}

